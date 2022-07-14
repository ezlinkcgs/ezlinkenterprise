#include <ezbusiness/ezatmcmd.h>

void *EzATMcmd :: ezatmcmdobj = 0;

EzATMcmd :: EzATMcmd()
{
        ezatmcmdobj = this;
}

EzATMcmd :: ~EzATMcmd()
{

}

int EzATMcmd :: InitEzATMcmd( )
{
    char logpath[ LOG_PATH_SIZE + 1 ];
	EzCfgUtil cfgutil;

    memset( logpath, 0, sizeof( logpath ) );
    sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezatmcmd.log" );

    if( openCmdDebug( logpath, "ezatmcmd" ) < 0 )
            exit( 0 );

	if( chutil.InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzChannelUtil"  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
	    closeDebug( );
	    TaskExit( );
	}

	if( chutil.createDummyChannel( "ezatmcmd" ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Creating Dummy Channel ezatmcmd..."  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

    if( !IsTaskRunning( "EzATMController" ) )
	{
	        trace( "Error in Creating EzATMcmd Channel" );
	        trace( "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
	        closeDebug();
	        TaskExit();
	}

	if( InitEzATMUtil( this ) < 0 )
	{
		trace( "Error in Initializing the AtmUtil" );
        trace( "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initATMMemoryUtil( this ) < 0 )
	{
		trace( "Error in Initializing the Atm Memory Util..." );
		trace( "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadFITMemory() < 0 )
	{
		trace( "Error in Loading the FIT Memory..." );
		trace( "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initODBCUtil( "ezatmcmd", this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing the EzDBUtil");
		closeDebug();
		TaskExit();
	}

	return 1;
}

void EzATMcmd :: PrintManageHelp()
{
	printf( "\n\tlistfit all");
	printf( "\n\tlistfit <instid>");
	printf( "\n\taddfit	<recordid>");
	printf( "\n\tupdatefit <recordid>");
	printf( "\n\tdeletefit <recordid>");
	printf( "\n\taddatm	<instid> <atmid>");
	printf( "\n\tupdateatm <instid> <atmid>");
	printf( "\n\tdeleteatm <instid> <atmid>");
	printf( "\n\tlistatmproperty <recordid>");
	printf( "\n\taddatmproperty <recordid>");
	printf( "\n\tupdateatmproperty <recordid>");
	printf( "\n\tdeleteatmproperty <recordid>");
	printf( "\n\tlistatmactionproperty <recordid>");
	printf( "\n\taddatmactionproperty <recordid>");
	printf( "\n\tupdateatmactionproperty <recordid>");
	printf( "\n\tdeleteatmactionproperty <recordid>");
	printf( "\n\tlistatmstatus <statuscode>");
	printf( "\n\taddatmstatus <statuscode>");
	printf( "\n\tupdateatmstatus <statuscode>");
	printf( "\n\tdeleteatmstatus <statuscode>");
}

void EzATMcmd :: PrintControlHelp()
{
	printf( "\n\t\t<<<<<<<<<<<<<<< Help For EZATMCMD - Control >>>>>>>>>>>>>>>>>\n" );
	printf( "\n\tSYNTAX 1: < DOWNLOAD/COMMAND >  < DOWNLOAD TYPE/COMMAND TYPE >  < ATM Id or AtmLogicalGroup >" );
	printf( "\n\tSYNTAX 2: < VEIW COMMANDS>  < ATM ID >" );
	printf( "\n\t\t<<<<<<<<<<<< SYNTAX 1 - DOWNLOAD/COMMAND >>>>>>>>>>>>>>>>>>>>>\n");
	printf( "\n\tDownload Type" );
	printf( "\n\t\t: all" );
	printf( "\n\t\t: state" );
	printf( "\n\t\t: screen" );
	printf( "\n\t\t: misc < Miscellaneous Data >" );
	printf( "\n\t\t: emisc < Enhanced Miscellaneous Data >" );
	printf( "\n\t\t: fit" );
	printf( "\n\t\t: key" );
	printf( "\n\t\t: configid" );
	printf( "\n\t\t: date_time < NCR ATM Only >" );
	printf( "\n\t\t: custom_icon" );
	printf( "\n\t\t: custom_date" );
	printf( "\n\t\t: celldata" );
	printf( "\n\t\t: template" );
	printf( "\n\t\t: reserved_screen < NCR ATM Only >" );
	printf( "\n\tCommand Type" );
	printf( "\n\t\t: go_in_service" );
	printf( "\n\t\t: go_out_service" );
	printf( "\n\t\t: shutdown" );
	printf( "\n\t\t: get_config_info" );
	printf( "\n\t\t: close_valid_shield" );
	printf( "\n\t\t: open_valid_shield" );
	printf( "\n\t\t: unlock_safe_door" );
	printf( "\n\t\t: lock_safe_door" );
	printf( "\n\t\t: emg" );
	printf( "\n\t\t: get_supply_counters" );
	printf( "\n\t\t: clear_supply_counters" );
	printf( "\n\t\t: get_esupply_counters" );
	printf( "\n\t\t: clear_esupply_counters" );
	printf( "\n\t\t: run_self_test" );
	printf( "\n\t\t: get_tally_info < NCR ATM Only >" );
	printf( "\n\t\t: get_errorlog < NCR ATM Only >" );
	printf( "\n\t\t: get_hw_config < NCR ATM Only >" );
	printf( "\n\t\t: get_date_time < NCR ATM Only >" );
	printf( "\n\t\t: get_ekc < NCR ATM Only >" );
	printf( "\n\t\t: set_state_idle" );
	printf( "\n\t\t<<<<<<<<<<<< SYNTAX 2 - VIEW COMMANDS >>>>>>>>>>>>>>>>>>>>>\n");
	printf( "\n\t\t: info < To View Atm Configuration Details>");
	printf( "\n\t\t: denominfo < To View the ATM Denomination( ie Cash ) Status>");
	printf( "\n\t\t: resetdenom < To Reset the ATM Denomination( ie Cash ) Status>");
	printf( "\n\t\t: status < To View the ATM Hardware Status and Special Status>");
	printf( "\n\t\t: clearstatus < To Clear the ATM Hardware Status>");
	printf( "\n\t\t: clearStaticStatus < To Clear the ATM Special Status>");
}

void EzATMcmd :: printAtmMemory( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct ATMSharedBuffer atmbuf;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}
	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	printf("\nAtmId		%s", atmmem.AtmId);
	printf("\n-----------------------------------------------------------------");
	printf("\nCurrentState			%c", atmbuf.CurrentState);
	printf("\nCurrentDownload		%d", atmbuf.CurrentDownload);
	printf("\nCurrentCommand		%d", atmbuf.CurrentCommand);
	printf("\nNextCommand			%d", atmbuf.NextCommand);
	printf("\nTotalLength			%d", atmbuf.TotalLength);
	printf("\nOffsetLength			%d", atmbuf.OffsetLength);
	printf("\nMsgCoOrdinationNo		%c", atmbuf.MsgCoOrdinationNo);
	printf("\nPrinterFlag			%c", atmbuf.PrinterFlag);
	printf("\nOARFlag				%c", atmbuf.OARFlag);
	printf("\nTxnCount				%d", atmbuf.TxnCount);
}

void EzATMcmd :: printAtmInfo( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct AtmTableInfo atminfo;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}
	memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
	memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );

	printf("\nAtmId		%s", atmmem.AtmId);
	printf("\n-------------------------------------------------------------");
	printf("\n	AtmTypeId			%s", atminfo.AtmTypeId );
	printf("\n	AtmLogicalGroup		%s", atminfo.AtmLogicalGroup );
	printf("\n	AtmLocation			%s", atminfo.AtmLocation );
	printf("\n	TerminalId			%s", atminfo.TerminalId );
	printf("\n	AcquirerInst		%s", atminfo.AcquirerInst );
	printf("\n	AcquirerBranchCode	%s", atminfo.AcquirerBranchCode );
	printf("\n	InstTerminalGroup	%s", atminfo.InstTerminalGroup );
	printf("\n	AtmConfigId			%d", atminfo.AtmConfigId);
	printf("\n	LoggingFlag			%c", atminfo.LoggingFlag );
	printf("\n	PinVerFlag			%c", atminfo.PinVerFlag );
	printf("\n	AtmStatus			%c", atminfo.AtmStatus );
	printf("\n	AtmMasterKey		%s", atminfo.AtmMasterKey );
	printf("\n	AtmCommKey			%s", atminfo.AtmCommKey );
	printf("\n	AtmKeyLen			%d", atminfo.AtmKeyLen );
	printf("\n	MaxNotesDispence	%d", atminfo.MaxNoteDisp);
	printf("\n	MaxAmountDispence	%d", atminfo.MaxAmountDisp);
	printf("\n	AtmTraceNo			%d", atminfo.TraceNum );
	printf("\n	BatchId				%s", atminfo.BatchId);
}

void EzATMcmd :: printLastTxn( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct ATMSharedBuffer atmbuf;
	struct EzTxnMsg LastTxnMsg;
	int MsgType;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
   	if( ReadAtmMemory( AtmId, &atmmem ) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}
	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	memset( &LastTxnMsg, 0, sizeof( struct EzTxnMsg ) );
	memcpy( &LastTxnMsg, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

	if( LastTxnMsg.MsgType == 6000 )
		MsgType = 210;
	else
		MsgType = LastTxnMsg.MsgType;

	printf("\nMsgType		%d", MsgType);
	printf("\nTxnCode		%d", LastTxnMsg.TxnCode);
	printf("\nTerminalId	%s", LastTxnMsg.TerminalId);
	printf("\nTraceNo		%d", LastTxnMsg.TraceNo);
	printf("\nTranDate		%d", LastTxnMsg.TranDate);
	printf("\nTranTime		%d", LastTxnMsg.TranTime);
	printf("\nRespCode		%d", LastTxnMsg.RespCode);
	printf("\nCHN			%s", LastTxnMsg.chn);
	printf("\nIssuerInst	%s", LastTxnMsg.IssuerInst);
	printf("\n");
}

void EzATMcmd :: printDenomInfo( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9],denomtemp;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );
	memcpy( &denominfo, &atmbuf.denominfo, sizeof( struct DenomInfo ) * 8 );



	printf("\n---------------------Denomination Status---------------------");
	printf("\n---------------------AtmId	[ %s ]------------------------\n", atmmem.AtmId);
	for( int i = 0; i < 8; i++ )
		printf( "Id[%c] Pos[%d] Value[%4d] Status[%c] Code[%3d] LastDispNotes[%d]\n", denominfo[ i ].DenomId, denominfo[ i ].CassPosition, denominfo[ i ].CurrencyValue, denominfo[ i ].Status, denominfo[ i ].CurrencyCode, denominfo[ i ].LastDispNotes );

	printf("\n	Note:");
	printf("\n			'@' --- Not Configured");
	printf("\n			'Y' --- Cash Available");
	printf("\n			'N' --- Cash Empty \n");
}

int EzATMcmd :: addFitRecord( const char *RecordId )
{
	struct AtmFit atmfit_rec;
	int retval;

	trace( "Processing FIT Add Request for RecordId[%s]", RecordId );

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database...." );
		printf( "\n----Error in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &atmfit_rec, 0, sizeof( struct AtmFit ) );
	retval = readEzAtmFit( RecordId, &atmfit_rec );

	if( DBClose() < 0 )
	{
		trace( "Error in Closing Switch Database" );
		printf( "\n----Error in Closing Switch Database....\n" );
		return -1;
	}

	if( retval != 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzAtmFIT Table....SqlErr[%05d]", RecordId,retval );
		printf( "\n----Error in Reading RecordId[%s] from EzAtmFIT Table....SqlErr[%05d]\n", RecordId,retval );
		return -1;
	}

	if( addFITMemory( atmfit_rec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in adding RecordId[%s] in FITMemory...", RecordId );
		printf( "\n-----Error in adding RecordId[%s] in FITMemory...already Exists\n", RecordId );
		return -1;
	}
	return 1;
}

int EzATMcmd :: updateFitRecord( const char *RecordId )
{
	struct AtmFit atmfit_rec;
	int retval;

	trace( "Processing FIT Update Request for RecordId[%s]", RecordId );

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database...." );
		printf( "\n----Error in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &atmfit_rec, 0, sizeof( struct AtmFit ) );
	retval = readEzAtmFit( RecordId, &atmfit_rec );

	if( DBClose() < 0 )
	{
		trace( "Error in Closing Switch Database" );
		printf( "\n----Error in Closing Switch Database....\n" );
		return -1;
	}

	if( retval != 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzAtmFIT Table....SqlErr[%05d]", RecordId,retval );
		printf( "\n----Error in Reading RecordId[%s] from EzAtmFIT Table....SqlErr[%05d]\n", RecordId,retval );
		return -1;
	}

	if( updateFITMemory( atmfit_rec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Updating RecordId[%s] in FITMemory...", RecordId );
		printf( "\n-----Error in Updating RecordId[%s] in FITMemory..\n", RecordId );
		return -1;
	}
	return 1;
}

int EzATMcmd :: deleteFitRecord( const char *RecordId )
{
	trace( "Processing FIT Delete Request for RecordId[%s]", RecordId );

	if( deleteFITMemory( RecordId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Deleting RecordId[%s] in FITMemory...", RecordId );
		printf( "\n-----Error in Deleting RecordId[%s] in FITMemory..\n", RecordId );
		return -1;
	}
	return 1;
}

void EzATMcmd :: resetDenomInfo( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct AtmTableInfo atminfo;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9];

	EzCfgUtil cfg;
	char FileName[ FILENAME_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], cfgsearch[ CFG_VAL_SIZE + 1 ];;
	bool found = false;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		printf( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
	memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );

	memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &denominfo, &atmbuf.denominfo, sizeof( struct DenomInfo ) * 8 );

	for( int i = 0; i < 8; i++ )
	{
		if( denominfo[i].Status == 'N' )
			denominfo[i].Status = 'Y';
	}

	memcpy( &atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 8 );
	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
	{
		printf( "Error in Reseting Denom memory for Atm[ %s ]", AtmId );
		return;
	}
	else
		printf( "Denom memory for Atm[ %s ] is Reseted", AtmId );

	printf("\n---------------------Denomination Status---------------------");
	printf("\n---------------------AtmId	[ %s ]------------------------\n", atmmem.AtmId);
	for( int i = 0; i < 8; i++ )
		    printf( "Id[%c] Pos[%d] Value[%d]\tCode[%d]\tStatus[%c] LastDispNotes[%d]\n", denominfo[ i ].DenomId, denominfo[ i ].CassPosition, denominfo[ i ].CurrencyValue, denominfo[ i ].CurrencyCode, denominfo[ i ].Status, denominfo[ i ].LastDispNotes );

	printf("\n	Note:");
	printf("\n			'@' --- Not Configured");
	printf("\n			'Y' --- Cash Available");
	printf("\n			'N' --- Cash Empty \n");
}

void EzATMcmd :: printAtmStatus( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct ATMSharedBuffer atmbuf;
	int Count = 0;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	printf("\n---------------------Hardware Status---------------------");
	printf("\n---------------------AtmId	[ %s ]------------------------\n", atmmem.AtmId);

	for( int i = 0; i < NOOFSTATUSMSG; i++ )
	{
		if( strlen( atmbuf.StatusMsg[ i ] ) != 0 )
			printf( "Sno[%d]\t---->\tStatus[ %s ]\n", i, atmbuf.StatusMsg[ i ] );
		else
			Count ++;
	}
	if( Count == NOOFSTATUSMSG )
		printf("\n---------------------No Status Reported from ATM------------------------\n", atmmem.AtmId);

	printf("\n######################################\n");
	printf("\nSpecial Status Reported		[ %s ]\n", atmbuf.StaticStatus );
}

void EzATMcmd :: clearAtmStatus( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct ATMSharedBuffer atmbuf;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	memset( atmbuf.StatusMsg, 0, sizeof( atmbuf.StatusMsg ) );

	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
	{
		printf( "Error in Reseting Denom memory for Atm[ %s ]", AtmId );
		return;
	}
	else
		printf( "Status memory for Atm[ %s ] is Cleared", AtmId );
}

void EzATMcmd :: clearAtmStaticStatus( const char *AtmId )
{
	struct AtmMemoryTable atmmem;
	struct AtmTableInfo atminfo;
	struct ATMSharedBuffer atmbuf;

	EzDateTimeUtil dtu;

	int SqlErr = 0;
	char Date[ 10 ];
	char Time[ 10 ];

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}

	memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
	memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	memset( atmbuf.StaticStatus, 0, sizeof( atmbuf.StaticStatus ) );
	strcpy( atmbuf.StaticStatus, "NONE" );

	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
	{
		printf( "Error in Clearing Status memory for Atm[ %s ]", AtmId );
		return;
	}
	else
		printf( "\n\tStatus memory for Atm[ %s ] is Cleared", AtmId );

	if( DBConnect( ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Connecting the Database");
		printf( "Error in connecting DB.. Check logfile" );
		return ;
	}

	memset( Date, 0, sizeof( Date ) );
	sprintf( Date, "%06d", dtu.getSysDate() );
	memset( Time, 0, sizeof( Time ) );
	sprintf( Time, "%06d", dtu.getSysTime() );

	SqlErr = ClearATMStaticStatus( atmbuf.StaticStatus, AtmId, Date, Time );
	if( SqlErr != 0 )
	{
		trace( DEBUG_ERROR,"Error in Updating the table ORA ERR: [%05d]", SqlErr );
		printf( "Error in Updating the table ORA ERR: [%05d]", SqlErr  );
	}
	else
	{
		printf( "\n\tStatus Table for Atm[ %s ] is Cleared", AtmId );
	}

	DBClose();
}

void EzATMcmd :: setDenomStatus( const char *AtmId, char Denom, char Status )
{
	struct AtmMemoryTable atmmem;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9],denomtemp;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );
	memcpy( &denominfo, &atmbuf.denominfo, sizeof( struct DenomInfo ) * 8 );

	for( int i = 0; i < 8; i++ )
	{
		if( denominfo[i].DenomId == Denom )
		{
			if( Status == 'Y' || Status == 'y' )
				denominfo[i].Status = 'Y';
			else if( Status == 'N' || Status == 'n' )
				denominfo[i].Status = 'N';
		}
	}

	memcpy( &atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 8 );
	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
	{
		printf( "Error in Reseting Denom memory for Atm[ %s ]", AtmId );
		return;
	}

	printf("\n---------------------Denomination Status---------------------");
	printf("\n---------------------AtmId	[ %s ]------------------------\n", atmmem.AtmId);
	for( int i = 0; i < 8; i++ )
		printf( "Id[%c] Pos[%d] Value[%4d]\tCode[%d]\tStatus[%c] LastDispNotes[%d]\n", denominfo[ i ].DenomId, denominfo[ i ].CassPosition, denominfo[ i ].CurrencyValue, denominfo[ i ].CurrencyCode, denominfo[ i ].Status, denominfo[ i ].LastDispNotes );

}

void EzATMcmd :: printAtmFit( const char *InstId )
{
	struct AtmFit atmfit_rec;

	printf("\n---------------------ATM FIT---------------------");
	printf("\nRECORDID\tINSTID\tATMLOGICALGROUP\tATMID\tSECURITYID\tFITRECORD\tINDIRECTSTATE");

	for( int i = 0; i < getMaxFits(); i++ )
	{
		memset( &atmfit_rec, 0, sizeof( struct AtmFit ) );
		if( getNextFitRecord( i, &atmfit_rec ) >= 0 )
		{
			if( !strcmp( atmfit_rec.InstId, InstId ) && strcmp( atmfit_rec.RecordId, "NOTDEFINED" ) )
				printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%c", atmfit_rec.RecordId, atmfit_rec.InstId, atmfit_rec.AtmLogicalGroup, atmfit_rec.AtmId, atmfit_rec.SecurityId, atmfit_rec.FitRecord, atmfit_rec.IndirectState );
			else if ( !strcmp( InstId, "*" ) )
			{
				if( strcmp( atmfit_rec.RecordId, "NOTDEFINED" ) )
					printf("\n\t%s\t%s\t%s\t%s\t%s\t%s\t%c", atmfit_rec.RecordId, atmfit_rec.InstId, atmfit_rec.AtmLogicalGroup, atmfit_rec.AtmId, atmfit_rec.SecurityId, atmfit_rec.FitRecord, atmfit_rec.IndirectState );
			}
		}
	}
}

void EzATMcmd :: postControllerMsg( struct EzAtmController *atmctrlmsg )
{
    if( chutil.WriteChannel( CONTROLLERCHANNEL, (char*)atmctrlmsg, sizeof( struct EzAtmController ) ) < 0 )
	{
		trace( "Failed to write msg into EzATMController Channel" );
		printf("Failed to Process the Request...");
	}
	return;
}

void EzATMcmd :: postManagerMsg( struct EzAtmMgrQMsg *atmmgrmsg )
{
    if( chutil.WriteChannel( ATMMGRCHANNEL, (char *)atmmgrmsg, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
	{
		trace( "Failed to write msg into %s Channel", ATMMGRCHANNEL );
		printf("Failed to Process the Request...");
	}
	else
		printf("Request will be Processed...");
	return;
}

int EzATMcmd :: ClearATMStaticStatus( char *StaticStatus, const char *AtmId, char *Date, char *Time )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZATMSTATUS SET \
    	STATICCODE='%s', \
		LOGDATE=to_date( '%s', 'dd-mm-yy' ), \
    	LOGTIME='%s' \
    	WHERE TRIM(ATMID)='%s';", StaticStatus, Date, Time, AtmId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzATMcmd :: readEzAtmFit( const char *I_RecordId, struct AtmFit *atmfit_ptr )
{
	char RecordId[ 17 ];
	char InstId[ 13 ];
	char AtmLogicalGroup[ 17 ];
	char AtmId[ 17 ];
	char SecurityId[ 11 ];
	char FitRecord[ 11 ];
	char IndirectState;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN odbcrt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcrt = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcrt );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
        	RTRIM(RECORDID), \
           	RTRIM(INSTID), \
			RTRIM(ATMLOGICALGROUP), \
			RTRIM(ATMID), \
			RTRIM(SECURITYID), \
			RTRIM(FITRECORD), \
			INDIRECTSTATE \
	    FROM EZATMFIT WHERE RTRIM(RECORDID)='%s';", I_RecordId );

    odbcrt = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace("SqlStmt<%s>",SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in readEzAtmFit [ %d ]", odbcrt );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
	memset( FitRecord, 0, sizeof( FitRecord ) );
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( AtmId, 0, sizeof( AtmId ) );

    odbcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(RecordId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(InstId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 3, SQL_C_CHAR, AtmLogicalGroup, sizeof(AtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(AtmLogicalGroup) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 4, SQL_C_CHAR, AtmId, sizeof(AtmId), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(AtmId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 5, SQL_C_CHAR, SecurityId, sizeof(SecurityId), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 6, SQL_C_CHAR, FitRecord, sizeof(FitRecord), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(FitRecord) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 7, SQL_C_BINARY, &IndirectState, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(IndirectState) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcrt = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( atmfit_ptr + i, 0, sizeof( struct AtmFit ) );
		strcpy( ( atmfit_ptr + i )->RecordId, RecordId );
		strcpy( ( atmfit_ptr + i )->InstId, InstId );
		strcpy( ( atmfit_ptr + i )->AtmLogicalGroup, AtmLogicalGroup );
		strcpy( ( atmfit_ptr + i )->AtmId, AtmId );
		strcpy( ( atmfit_ptr + i )->SecurityId, SecurityId );
		strcpy( ( atmfit_ptr + i )->FitRecord, FitRecord );
		( atmfit_ptr + i )->IndirectState = IndirectState;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

void EzATMcmd :: startCmdInterface( int argc, char **argv )
{
	if( argc != 2 )
	{
		printf("\n Syntax: <ezatmcmd> <manage/control>\n" );
		exit(0);
	}
	if( strcasecmp( argv[ 1 ], "manage" ) && strcasecmp( argv[ 1 ], "control" ) )
	{
		printf( "\nSyntax: <ezatmcmd> <manage/control>\n" );
		exit(0);
	}
	if( !strcasecmp( argv[ 1 ], "manage" ) )
		startManageInterface();
	else if( !strcasecmp( argv[ 1 ], "control" ) )
		startControlInterface();
	else
	{
		printf( "\nSyntax: <ezatmcmd> <manage/control>\n" );
		exit(0);
	}
}

void EzATMcmd :: startControlInterface()
{
	char command[ 100 ], InstId[ INST_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	int AtmCount = 0;
	bool GroupActivity = false;

	struct EzAtmController AtmCont;
	memset( &AtmCont, 0, sizeof( struct EzAtmController ) );

	trace("~~~~~~~~~~~~~~~~~~ezatmcmd <Control> Started ~~~~~~~~~~~~~~~~~~~~~~~~~~");
	while( 1 )
	{
		printf("\nezatmcmd-control>" );
		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;
		else
		{
			trace("Command1 < %s >", command );
			if( !strcasecmp( command, "help" ) )
				PrintControlHelp();
			else if( !strcasecmp( command, "quit" ) || !strcasecmp( command, "exit" ) )
				exit( 0 );
			else if( !strcasecmp( command, "size" ) )
			{
				printf("\nTotal Atm Memory Size[%d]", sizeof( struct AtmMemoryTable ) );
				printf("\nAtm info Size[%d]", sizeof( struct AtmTableInfo ) );
				printf("\nAtm Buffer Size[%d]", sizeof( struct ATMSharedBuffer ) );
				printf("\nTxn Msg Size[%d]", sizeof( struct EzDevMsg ));
			}
			else if( !strcasecmp( command, "download" ) )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );

				if( !strcasecmp( command, "all" ) )
					AtmCont.DownloadType = DOWNLOAD_ALL;
				else if( !strcasecmp( command, "state" ) )
					AtmCont.DownloadType = DOWNLOAD_STATE ;
				else if( !strcasecmp( command, "screen" ) )
					AtmCont.DownloadType = DOWNLOAD_SCREEN ;
				else if( !strcasecmp( command, "misc" ) )
					AtmCont.DownloadType = DOWNLOAD_MISC ;
				else if( !strcasecmp( command, "emisc" ) )
					AtmCont.DownloadType = DOWNLOAD_MISC_E ;
				else if( !strcasecmp( command, "fit" ) )
					AtmCont.DownloadType = DOWNLOAD_FIT ;
				else if( !strcasecmp( command, "key" ) )
					AtmCont.DownloadType = DOWNLOAD_KEY ;
				else if( !strcasecmp( command, "configid" ) )
					AtmCont.DownloadType = DOWNLOAD_CONFIG_ID ;
				else if( !strcasecmp( command, "date_time" ) )
					AtmCont.DownloadType = DOWNLOAD_DATE_TIME ;
				else if( !strcasecmp( command, "custom_icon" ) )
					AtmCont.DownloadType = DOWNLOAD_CUSTOM_ICON ;
				else if( !strcasecmp( command, "custom_char" ) )
					AtmCont.DownloadType = DOWNLOAD_CUSTOM_CHAR ;
				else if( !strcasecmp( command, "celldata" ) )
					AtmCont.DownloadType = DOWNLOAD_CELLDATA ;
				else if( !strcasecmp( command, "template" ) )
					AtmCont.DownloadType = DOWNLOAD_TEMPLATE ;
				else if( !strcasecmp( command, "reserved_screen" ) )
					AtmCont.DownloadType = DOWNLOAD_RESERVED_SCREEN ;
				else
				{
					printf("Invalid Download Type..type help for more\n" );
					continue;
				}

				memset( command, 0, sizeof( command ) );
				getCommand( command , 3);
				trace("Command3 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("Invalid ATM Id or AtmLogicalGroup..Verify and Try Again...\n" );
					continue;
				}

				if( VerifyAtmMemory( command ) < 0 )
				{
					AtmCount = GetAtmCount( command );
					printf( "AtmCount %d", AtmCount);
					if( AtmCount <= 0 )
					{
						trace("Error in searching AtmLogicalGroup[%s] AtmCount[%d]", command, AtmCount );
						printf("Error: Invalid ATM Id or AtmLogicalGroup..Verify and Try Again...\n" );
						continue;
					}
					else
					{
						GroupActivity = true;
						memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ));
						strcpy( AtmLogicalGroup, command );
					}
				}
				else
				{
					memset( AtmId, 0, sizeof( AtmId ));
					strcpy( AtmId, command );
				}

				AtmCont.MsgType = EZ_ATM_DOWNLOAD_REQ;
				AtmCont.DownloadId = DOWNLOAD_SINGLE;


				if( GroupActivity )
				{
					for( int i = 0; i < AtmCount; i++ )
					{
						memset( AtmCont.AtmId, 0, sizeof( AtmCont.AtmId ) );
						if( GetAtmId( AtmLogicalGroup, AtmCont.AtmId, i + 1 ) > 0 )
						{
							trace("Posting msg for ATMId[%s]", AtmCont.AtmId );
							postControllerMsg( &AtmCont );
						}
					}
				}
				else
				{
					memset( AtmCont.AtmId, 0, sizeof( AtmCont.AtmId ) );
					strcpy( AtmCont.AtmId, AtmId );
					postControllerMsg( &AtmCont );
				}
			}
			else if( !strcasecmp( command, "command" ) )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}

				if( !strcasecmp( command, "go_in_service" ) )
					AtmCont.CommandType = GO_IN_SERVICE ;
				else if( !strcasecmp( command, "go_out_service" ) )
					AtmCont.CommandType = GO_OUT_SERVICE ;
				else if( !strcasecmp( command, "shutdown" ) )
					AtmCont.CommandType = SHUTDOWN ;
				else if( !strcasecmp( command, "get_config_info" ) )
					AtmCont.CommandType = GET_CONFIG_INFO ;
				else if( !strcasecmp( command, "close_valid_shield" ) )
					AtmCont.CommandType = CLOSE_VANDAL_SHIELD ;
				else if( !strcasecmp( command, "open_valid_shield" ) )
					AtmCont.CommandType = OPEN_VANDAL_SHIELD ;
				else if( !strcasecmp( command, "unlock_safe_door" ) )
					AtmCont.CommandType = UNLOCK_SAFE_DOOR ;
				else if( !strcasecmp( command, "lock_safe_door" ) )
					AtmCont.CommandType = LOCK_SAFE_DOOR ;
				else if( !strcasecmp( command, "emg" ) )
					AtmCont.CommandType = EMG_COMMAND ;
				else if( !strcasecmp( command, "get_supply_counters" ) )
					AtmCont.CommandType = GET_SUPPLY_COUNTS ;
				else if( !strcasecmp( command, "clear_supply_counters" ) )
					AtmCont.CommandType =  CLEAR_SUPPLY_COUNTS ;
				else if( !strcasecmp( command, "get_esupply_counters" ) )
					AtmCont.CommandType = GET_ESUPPLY_COUNTS ;
				else if( !strcasecmp( command, "clear_esupply_counters" ) )
					AtmCont.CommandType =  CLEAR_ESUPPLY_COUNTS ;
				else if( !strcasecmp( command, "run_self_test" ) )
					AtmCont.CommandType = RUN_SELF_TEST ;
				else if( !strcasecmp( command, "get_tally_info" ) )
					AtmCont.CommandType = GET_TALLY_INFO ;
				else if( !strcasecmp( command, "get_errorlog" ) )
					AtmCont.CommandType = GET_ERRORLOG ;
				else if( !strcasecmp( command, "get_hw_config" ) )
					AtmCont.CommandType = GET_HW_CONF ;
				else if( !strcasecmp( command, "get_date_time" ) )
					AtmCont.CommandType = GET_DATE_TIME ;
				else if( !strcasecmp( command, "get_ekc" ) )
					AtmCont.CommandType =  GET_EKC ;
				else if( !strcasecmp( command, "set_state_idle" ) )
					AtmCont.CommandType =  SET_STATE_IDLE;
				else
				{
					printf("Invalid Command Type..type help for more\n");
					continue;
				}

				memset( command, 0, sizeof( command ) );
				getCommand( command , 3 );
				trace("Command3 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("Invalid ATM Id or AtmLogicalGroup..Verify and Try Again...\n" );
					continue;
				}

				if( VerifyAtmMemory( command ) < 0 )
				{
					AtmCount = GetAtmCount( command );
					if( AtmCount != 0 )
					{
						trace("Error in searching AtmLogicalGroup[%s] AtmCount[%d]", command, AtmCount );
						printf("Error: Invalid ATM Id or AtmLogicalGroup..Verify and Try Again...\n" );
						continue;
					}
					else
					{
						GroupActivity = true;
						memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ));
						strcpy( AtmLogicalGroup, command );
					}
				}
				else
				{
					memset( AtmId, 0, sizeof( AtmId ));
					strcpy( AtmId, command );
				}


				AtmCont.MsgType = EZ_ATM_COMMAND_REQ ;

				if( GroupActivity )
				{
					for( int i = 0; i < AtmCount; i++ )
					{
						memset( AtmCont.AtmId, 0, sizeof( AtmCont.AtmId ) );
						if( GetAtmId( AtmLogicalGroup, AtmCont.AtmId, i + 1 ) > 0 )
						{
							trace("Posting msg for ATMId[%s]", AtmCont.AtmId );
							postControllerMsg( &AtmCont );
						}
					}
				}
				else
				{
					memset( AtmCont.AtmId, 0, sizeof( AtmCont.AtmId ) );
					strcpy( AtmCont.AtmId, AtmId );
					postControllerMsg( &AtmCont );
				}

			}
			else if( !strcasecmp( command, "memory" ) || !strcasecmp( command, "m") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					printAtmMemory( command );
			}
			else if( !strcasecmp( command, "lasttxn" ) || !strcasecmp( command, "lt") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					printLastTxn( command );
			}
			else if( !strcasecmp( command, "info" ) || !strcasecmp( command, "i") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					printAtmInfo( command );
			}
			else if( !strcasecmp( command, "DenomInfo" ) || !strcasecmp( command, "DI") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					printDenomInfo( command );
			}
			else if( !strcasecmp( command, "ResetDenom" ) || !strcasecmp( command, "RD") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					resetDenomInfo( command );
			}
			else if( !strcasecmp( command, "status" ) || !strcasecmp( command, "s") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					printAtmStatus( command );
			}
			else if( !strcasecmp( command, "clearstatus" ) || !strcasecmp( command, "cs") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					clearAtmStatus( command );
			}
			else if( !strcasecmp( command, "clearStaticStatus" ) || !strcasecmp( command, "css") )
			{
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					clearAtmStaticStatus( command );
			}
			else if( !strcasecmp( command, "set" ) || !strcasecmp( command, "s") )
			{
				char Denom[3];
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 2 ) ;
				trace("Command2 < %s >", command );
				if( strlen( command ) == 0 || strlen( command ) != 1 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				else
				{
					memset( Denom, 0, sizeof( Denom ) );
					strcpy( Denom, command );
				}

				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 3 ) ;
				trace("Command3 < %s >", command );
				if( strlen( command ) == 0 || strlen( command ) != 1 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				char denomid;
				denomid = command[0];
				memset( command, 0, sizeof( command ) ) ;
				getCommand( command , 4 ) ;
				trace("Command4 < %s >", command );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( VerifyAtmMemory( command ) < 0 )
				{
					printf("Error : ATMId [ %s ] does not exist...\n", command );
					continue;
				}
				else
					setDenomStatus( command, Denom[0], denomid );
			}
			else
			{
				printf("Invalid Command.. type help for more\n");
				continue;
			}
		}
	}
}

void EzATMcmd :: startManageInterface()
{
	char command[ 100 ], InstId[ INST_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	int AtmCount = 0;
	bool GroupActivity = false;

	struct EzAtmController AtmCont;
	struct AtmFitMsg atmfitmsg;
	struct EzAtmMgrQMsg atmmgrqmsg;

	trace("~~~~~~~~~~~~~~~~~~ezatmcmd Manage Started ~~~~~~~~~~~~~~~~~~~~~~~~~~");
	while( 1 )
	{
		printf("\nezatmcmd-manage>" );
		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;
		else
		{
			trace("Command1 < %s >", command );
			if( !strcasecmp( command, "help" ) )
				PrintManageHelp();
			else if( !strcasecmp( command, "quit" ) || !strcasecmp( command, "exit" ) )
				exit( 0 );
			else if( !strcasecmp( command, "listfit" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2);
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type all or institutionid");
					continue;
				}
				if( !strcasecmp( command, "all" ) )
					printAtmFit( "*" );
				else
					printAtmFit( command );
			}
			else if( !strcasecmp( command, "addfit" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more...");
					continue;
				}
				addFitRecord( command );
			}
			else if( !strcasecmp( command, "updatefit" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more...");
					continue;
				}
				updateFitRecord( command );
			}
			else if( !strcasecmp( command, "deletefit" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more...");
					continue;
				}
				deleteFitRecord( command );
			}
			else if( !strcasecmp( command, "addatm" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Institution Id");
					continue;
				}
				else
				{
					memset( InstId, 0, sizeof( InstId ) );
					strcpy( InstId, command );
				}

				memset( command, 0, sizeof( command ) );
				getCommand( command , 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the ATM Id");
					continue;
				}
				else
				{
					if( VerifyAtmMemory( command ) < 0 )
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMINFOMEMORY;
						atmmgrqmsg.OperationCode = ADD;
						strcpy( atmmgrqmsg.AtmId, command );
						strcpy( atmmgrqmsg.SourceBuffer, InstId );

						postManagerMsg( &atmmgrqmsg );

					}
					else
						printf("Error : ATMId [ %s ]already exist...\n", command );
				}
			}
			else if( !strcasecmp( command, "updateatm" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the ATM Id");
					continue;
				}
				else
				{
					if( VerifyAtmMemory( command ) < 0 )
						printf("Error : ATMId [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMINFOMEMORY;
						atmmgrqmsg.OperationCode = UPDATE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );

					}
				}
			}
			else if( !strcasecmp( command, "deleteatm" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the ATM Id");
					continue;
				}
				else
				{
					if( VerifyAtmMemory( command ) < 0 )
						printf("Error : ATMId [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMINFOMEMORY;
						atmmgrqmsg.OperationCode = DELETE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );

					}
				}
			}
			else if( !strcasecmp( command, "listatmproperty" ) )
			{

			}
			else if( !strcasecmp( command, "addatmproperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmPropertyMemory( atoi( command ) > 0 ) )
						printf("Error : Record Id [ %s ] already exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMPROPERTY;
						atmmgrqmsg.OperationCode = ADD;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "updateatmproperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmPropertyMemory( atoi( command ) < 0 ) )
						printf("Error : Record Id [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMPROPERTY;
						atmmgrqmsg.OperationCode = UPDATE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "deleteatmproperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmPropertyMemory( atoi( command ) < 0 ) )
						printf("Error : Record Id [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMPROPERTY;
						atmmgrqmsg.OperationCode = DELETE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "listatmactionproperty" ) )
			{

			}
			else if( !strcasecmp( command, "addatmactionproperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmActionPropertyMemory( atoi( command ) > 0 ) )
						printf("Error : Record Id [ %s ] already exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMACTIONPROPERTY;
						atmmgrqmsg.OperationCode = ADD;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "updateatmactionproperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmActionPropertyMemory( atoi( command ) < 0 ) )
						printf("Error : Record Id [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMACTIONPROPERTY;
						atmmgrqmsg.OperationCode = UPDATE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "deleteatmactionproperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmActionPropertyMemory( atoi( command ) < 0 ) )
						printf("Error : Record Id [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMACTIONPROPERTY;
						atmmgrqmsg.OperationCode = DELETE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "addatmstatus" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmStatusMemory( command ) > 0 )
						printf("Error : Status Code [ %s ] already exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMSTATUS;
						atmmgrqmsg.OperationCode = ADD;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "updateatmstatus" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Record Id");
					continue;
				}
				else
				{
					if( VerifyAtmStatusMemory( command ) < 0 )
						printf("Error : Status Code [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMSTATUS;
						atmmgrqmsg.OperationCode = UPDATE;
						strcpy( atmmgrqmsg.AtmId, command );

						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else if( !strcasecmp( command, "deleteatmstatus" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command , 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type the Status Code");
					continue;
				}
				else
				{
					if( VerifyAtmStatusMemory( command ) < 0 )
						printf("Error : Status Code [ %s ] does not exist...\n", command );
					else
					{
						memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
						atmmgrqmsg.SourceType = MEMORY;
						atmmgrqmsg.CommandCode = ATMSTATUS;
						atmmgrqmsg.OperationCode = DELETE;
						strcpy( atmmgrqmsg.AtmId, command );
						postManagerMsg( &atmmgrqmsg );
					}
				}
			}
			else
			{
				printf("Invalid Command.. type help for more\n");
				continue;
			}
		}
	}
}

int main( int argc, char **argv )
{
        EzATMcmd ezatmcmdobj;
        ezatmcmdobj.InitEzATMcmd( );
        ezatmcmdobj.startCmdInterface( argc, argv );
        return 1;
}

