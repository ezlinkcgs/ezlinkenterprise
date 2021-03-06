#include <eztms/eztmsdriver.h>

int EzTMSDriver :: initTMSDriver( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ TMS_BITMAP_FILE_SIZE + 1 ],MerchId[ 33 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztmsdriver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
			exit( 0 );

	SetDebug( );

	trace( "^^^^^^^^^^^EzTMSDriver Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( CHANNEL_NAME_TMSDRIVER, TaskName ) < 0 )
	{
		trace( "Error in Creating [%s] Channel", CHANNEL_NAME_TMSDRIVER );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}


	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzSecurityUtil..." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( hypercom.initHypercomUtil( this, &ezdatetimeutil ) < 0 )
	{
		trace( "Error in Initializing Hypercom...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( castle8583.initCastles8583( this, &ezdatetimeutil ) < 0 )
	{
		trace( "Error in Initializing Castles8583...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initEzTMSDriverODBC( TaskName, this ) < 0 )
	{
			trace( "Error in Initializing DBUtil...." );
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
	}


	/*if( ConnectDB() < 0 )
	{
			trace( DEBUG_ERROR,"Error in Connecting the Database");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			exit( 0 );
	}
	*/

	if( initTMSDriverUtil( this ) < 0 )
	{
		trace( "Error in Initializing TMSDriverUtil...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if(  LoadTMSChannelProperty() < 0 )
	{
		trace( "Error in Loading TMSChannelProperty...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSRouteInfo() < 0 )
	{
		trace( "Error in Loading TMSRouteInfo...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSRouteSelect() < 0 )
	{
		trace( "Error in Loading TMSRouteSelect...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSMsgTranslate() < 0 )
	{
		trace( "Error in Loading TMSMsgTranslate...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSTxnRefSelect() < 0 )
	{
		trace( "Error in Loading TMSTxnRefSelect...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSInBoundProperty() < 0 )
	{
		trace( "Error in Loading TMSInBoundProperty...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSTxnRel() < 0 )
	{
		trace( "Error in Loading TMSTxnRel...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnsequtil.initTxnSeqUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnSeqUtil...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initMMSUtil( this ) < 0 )
	{
		trace( "Error in Initializing MMSUtil..." );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
	}

	TaskInit();
	initEzSigUtil( this );
}

int EzTMSDriver :: logTMSTxnInfo( char LogFlag, const char *TMSTxnRefNum, struct EzTxnMsg *tmsmsg_ptr )
{
	struct EzTMSLoggerMsg tmsloggermsg;

	memset( &tmsloggermsg, 0, sizeof( struct EzTMSLoggerMsg ) );
	strcpy( tmsloggermsg.MachineId, tmsmsg_ptr->MachineId );
	tmsloggermsg.LogFlag = LogFlag;
	tmsloggermsg.NotificationId = getpid();
	strcpy( tmsloggermsg.TMSTxnRefNum, TMSTxnRefNum );
	memcpy( &tmsloggermsg.txnmsg, tmsmsg_ptr, sizeof( struct EzTxnMsg ) );

	if( WriteChannel( TMSLOGGERCHANNEL, ( char * ) &tmsloggermsg, sizeof( struct EzTMSLoggerMsg ) ) < 0 )
	{
		trace( "Error in Writing Message to Channel[%s]...", TMSLOGGERCHANNEL );
		return -1;
	}
	return 1;
}

void EzTMSDriver :: process500( struct EzTxnMsg tmsmsg )
{
	char *endptr, TempStr[ 50 ], NewBatchId[ 13 ];
	int SaleCount, VoidCount, retval, MsgSize;
	double SaleAmount, VoidAmount, TableSaleAmount, TableVoidAmount, HostSaleAmount, HostVoidAmount;
	struct EzTerminalTotal tot_rec;
	struct EzTerminalBatchInfo termbatchinfo_rec;
	struct EzTerminalBatchInfoHist termbatchinfohist_rec;
	char SaleAmtStr[ 20 ], TableSaleAmtStr[ 20 ], VoidAmtStr[ 20 ], TableVoidAmtStr[ 20 ];

	trace( "Processing 500 Message from MachineId[%s]", mmsterminalprofile_rec.MachineId );

	trace( "Decomposing Total[%s]", tmsmsg.RsvFld2 );
	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2, 3 );
	SaleCount = atoi( TempStr );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + 3, 12 );
	SaleAmount = ( double ) atol( TempStr ) / 100;

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + 15, 3 );
	VoidCount = atoi( TempStr );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + 18, 12 );
	VoidAmount = ( double ) atol( TempStr ) / 100;

	memset( SaleAmtStr, 0, sizeof( SaleAmtStr ) );
	sprintf( SaleAmtStr, "%0.2lf", SaleAmount );
	memset( VoidAmtStr, 0, sizeof( VoidAmtStr ) );
	sprintf( VoidAmtStr, "%0.2lf", VoidAmount );

	trace( "Checking SaleCount[%d] SaleAmount[%s] VoidCount[%d] VoidAmount[%s] sent from POS[%s]...", SaleCount, SaleAmtStr, VoidCount, VoidAmtStr, mmsterminalprofile_rec.MachineId );

	if( ConnectDB() < 0 )
	{
		trace( "Error in connecting with switch database..." );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
		if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
		{
			MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing hypercom pos terminal...." );
				return;
			}
		}
		else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
		{
			MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing castles pos terminal...." );
				return;
			}
		}
		MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
		hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
		writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
		return;
	}

	memset( &tot_rec, 0, sizeof( struct EzTerminalTotal ) );
	retval = getTotals( mmsterminalprofile_rec.MachineId, mmsterminalprofile_rec.BatchId, &tot_rec );
	if( retval != 0 )
	{
		trace( "Error in Getting Totals for POSId[%s]...SqlErr[%05d]", mmsterminalprofile_rec.MachineId, retval );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
		if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
		{
			MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing hypercom pos terminal...." );
				return;
			}
		}
		else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
		{
			MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing castles pos terminal...." );
				return;
			}
		}
		MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
		hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
		writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
		CloseDB();
		return;
	}

	trace( "Read Totals with SaleCount[%d] SaleAmount[%s] VoidCount[%d] VoidAmount[%s] for POS[%s]", tot_rec.TermSaleCount, tot_rec.TermSaleAmount, tot_rec.TermVoidCount, tot_rec.TermVoidAmount, mmsterminalprofile_rec.MachineId );

	HostSaleAmount = strtod( tot_rec.SaleAmount, &endptr );
	HostVoidAmount = strtod( tot_rec.VoidAmount, &endptr );
	TableSaleAmount = strtod( tot_rec.TermSaleAmount, &endptr );
	TableVoidAmount = strtod( tot_rec.TermVoidAmount, &endptr );

	trace( "SaleAmount[%lf] TableSaleAmount[%lf] VoidAmount[%lf] TableVoidAmount[%lf]", SaleAmount, TableSaleAmount, VoidAmount, TableVoidAmount );

	//if( SaleCount != tot_rec.TermSaleCount || VoidCount != tot_rec.TermVoidCount || strcmp( tot_rec.TermSaleAmount, SaleAmtStr ) || strcmp( tot_rec.TermVoidAmount, VoidAmtStr ) )
	if( SaleCount != tot_rec.TermSaleCount || VoidCount != tot_rec.TermVoidCount || SaleAmount != TableSaleAmount || VoidAmount != TableVoidAmount )
	{
		tmsmsg.RespCode = 95;
		tmsmsg.MsgType += 10;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
		if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
		{
			MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing hypercom pos terminal...." );
				return;
			}
		}
		else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
		{
			MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing castles pos terminal...." );
				return;
			}
		}
		MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
		hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
		writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
		CloseDB();
		return;
	}

	memset( NewBatchId, 0, sizeof( NewBatchId ) );
	eztxnsequtil.genPOSBatchId( NewBatchId );

	if( updateTerminalBatchId( mmsterminalprofile_rec.MachineId, NewBatchId ) < 0 )
		trace( "Error in Updating POSBatchId in Memory..." );

	retval = updateTerminalBatchInTerminalInfo( mmsterminalprofile_rec.MachineId, NewBatchId );

	if( retval != 0 )
		trace( "Error in Updating POSBatchId in TerminalInfo Table...OraErr[%05d]", retval );

	memset( &termbatchinfohist_rec, 0, sizeof( struct EzTerminalBatchInfoHist ) );
	strcpy( termbatchinfohist_rec.BatchId, mmsterminalprofile_rec.BatchId );
	memset( termbatchinfohist_rec.TermBatchId, 0, sizeof( termbatchinfohist_rec.TermBatchId ) );
	strcpy( termbatchinfohist_rec.TermBatchId, tmsmsg.AuthNum );
	memset( termbatchinfohist_rec.NewBatchId, 0, sizeof( termbatchinfohist_rec.NewBatchId ) );
	strcpy( termbatchinfohist_rec.NewBatchId, NewBatchId );
	memset( termbatchinfohist_rec.InstId, 0, sizeof( termbatchinfohist_rec.InstId ) );
	strcpy( termbatchinfohist_rec.InstId, mmsterminalprofile_rec.InstId );
	memset( termbatchinfohist_rec.MachineId, 0, sizeof( termbatchinfohist_rec.MachineId ) );
	strcpy( termbatchinfohist_rec.MachineId, mmsterminalprofile_rec.MachineId );
	memset( termbatchinfohist_rec.Termid, 0, sizeof( termbatchinfohist_rec.Termid ) );
	strcpy( termbatchinfohist_rec.Termid, mmsterminalprofile_rec.TerminalId );
	memset( termbatchinfohist_rec.MerchantId, 0, sizeof( termbatchinfohist_rec.MerchantId ) );
	strcpy( termbatchinfohist_rec.MerchantId, mmsterminalprofile_rec.MerchantId );
	memset( termbatchinfohist_rec.CloseDate, 0, sizeof( termbatchinfohist_rec.CloseDate ) );
	sprintf( termbatchinfohist_rec.CloseDate, "%06d", ezdatetimeutil.getSysDate() );
	termbatchinfohist_rec.CloseTime = ezdatetimeutil.getSysTime();
	termbatchinfohist_rec.Source = TMS_SOURCE_TERMINAL;
	if( tot_rec.SaleCount == tot_rec.TermSaleCount && tot_rec.VoidCount == tot_rec.TermVoidCount && TableSaleAmount == HostSaleAmount && TableVoidAmount == HostVoidAmount )
		termbatchinfohist_rec.MatchFlag = TMS_TOTALS_MATCHED;
	else
		termbatchinfohist_rec.MatchFlag = TMS_TOTALS_MISMATCHED;

	termbatchinfohist_rec.HostSaleCount =  tot_rec.SaleCount;
	termbatchinfohist_rec.TermSaleCount = tot_rec.TermSaleCount;
	memset( termbatchinfohist_rec.HostSaleAmount, 0, sizeof( termbatchinfohist_rec.HostSaleAmount ) );
	strcpy( termbatchinfohist_rec.HostSaleAmount, tot_rec.SaleAmount );
	memset( termbatchinfohist_rec.TermSaleAmount, 0, sizeof( termbatchinfohist_rec.TermSaleAmount ) );
	strcpy( termbatchinfohist_rec.TermSaleAmount, tot_rec.TermSaleAmount );
	termbatchinfohist_rec.HostVoidCount =  tot_rec.VoidCount;
	termbatchinfohist_rec.TermVoidCount = tot_rec.TermVoidCount;
	memset( termbatchinfohist_rec.HostVoidAmount, 0, sizeof( termbatchinfohist_rec.HostVoidAmount ) );
	strcpy( termbatchinfohist_rec.HostVoidAmount, tot_rec.VoidAmount );
	memset( termbatchinfohist_rec.TermVoidAmount, 0, sizeof( termbatchinfohist_rec.TermVoidAmount ) );
	strcpy( termbatchinfohist_rec.TermVoidAmount, tot_rec.TermVoidAmount );

	termbatchinfohist_rec.HostAuthCount =  tot_rec.AuthCount;
	termbatchinfohist_rec.TermAuthCount = tot_rec.TermAuthCount;
	memset( termbatchinfohist_rec.HostAuthAmount, 0, sizeof( termbatchinfohist_rec.HostAuthAmount ) );
	strcpy( termbatchinfohist_rec.HostAuthAmount, "0.00" );
	memset( termbatchinfohist_rec.TermAuthAmount, 0, sizeof( termbatchinfohist_rec.TermAuthAmount ) );
	strcpy( termbatchinfohist_rec.TermAuthAmount, "0.00" );


	retval = insertTerminalBatchHist( &termbatchinfohist_rec );

	if( retval != 0 )
		trace( "Error in Inserting in TerminalBatchHist Table..OraErr[%05d]", retval );

	retval = clearTerminalBatchInfo( mmsterminalprofile_rec.MachineId, NewBatchId, termbatchinfohist_rec.CloseDate, termbatchinfohist_rec.CloseTime );

	if( retval != 0 )
		trace( "Error in Clearing TerminalBatchInfo Table..OraErr[%05d]", retval );

	retval = moveFromTerminalBatchTxnInfoToHist( mmsterminalprofile_rec.MachineId, mmsterminalprofile_rec.BatchId );
	if( retval != 0 )
		trace( "Error in Moving from POSBatchTxnInfo to Hist Table..OraErr[%05d]", retval );

	retval = deleteFromTerminalBatchTxnInfo( mmsterminalprofile_rec.MachineId, mmsterminalprofile_rec.BatchId );

	if( retval != 0 )
		trace( "Error in Deleting POSBatchTxnInfo Table..OraErr[%05d]", retval );

	tmsmsg.MsgType += 10;
	tmsmsg.RespCode = EZTMS_RC_Approved;
	memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
	sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
	if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
	{
		MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
		if( MsgSize < 0 )
		{
			trace( "Error in composing hypercom pos terminal...." );
			return;
		}
	}
	else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
	{
		MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
		if( MsgSize < 0 )
		{
			trace( "Error in composing castles pos terminal...." );
			return;
		}
	}
	MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
	hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
	writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
	CloseDB();
}

void EzTMSDriver :: process320( struct EzTxnMsg tmsmsg )
{
	struct EzTxnMsg oldtmsmsg;
	char *endptr, TMSTxnRefNum[ 151 ], AmountStr[ 20 ];
	int retval, MsgSize;
	double Amount, TableAmount;

	trace( "Processing 320 message for POSId[%s]", mmsterminalprofile_rec.MachineId );
	memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
	getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
	trace( "Got LookUp POSTxnRefNum[%s]", TMSTxnRefNum );

	ConnectDB();

	memset( &oldtmsmsg, 0, sizeof( struct EzTxnMsg ) );
	retval = searchPOSTxn( TMSTxnRefNum, &oldtmsmsg );
	if( retval == 1403 || retval == 100 )
	{
		trace( "Transaction with POSTxnRefNum[%s] BatchId[%s] POSId[%s] not found in BatchTxnInfo Table...",  TMSTxnRefNum, oldtmsmsg.BatchId, mmsterminalprofile_rec.MachineId );
		retval = insertTerminalBatchTxnInfo( mmsterminalprofile_rec.MachineId, &tmsmsg, TMSTxnRefNum, TMS_TXN_MISMATCH, TMS_TXN_REASON_NOT_FOUND );
		if( retval != 0 )
			trace( "Error in inserting PosBatchTxnInfo OraErr[%05d]", retval );
		CloseDB();
	}
	else
	{
		if( retval == 0 )
		{
			Amount = ( double ) atol( tmsmsg.Amount ) / 100;
			TableAmount = strtod( oldtmsmsg.Amount, &endptr );
			memset( AmountStr, 0, sizeof( AmountStr ) );
			sprintf( AmountStr, "%0.2lf", Amount );
			if( Amount != TableAmount )
			{
				trace( "Transaction with POSTxnRefNum[%s] BatchId[%s] POSId[%s] has a Amount MisMatch TerminalAmount != HostAmount[%s] in TerminalBatchTxnInfo Table...",  TMSTxnRefNum, tmsmsg.BatchId, mmsterminalprofile_rec.MachineId, tmsmsg.Amount, oldtmsmsg.Amount );
				retval = updateTerminalBatchTxnInfo( mmsterminalprofile_rec.MachineId, TMSTxnRefNum, AmountStr, TMS_TXN_MISMATCH, TMS_TXN_REASON_AMOUNT_MISMATCH );
				if( retval != 0 )
					trace( "Error in Updating BatchTxnInfo OraErr[%05d]", retval );
			}
		}
		else
		{

		}
		CloseDB();
	}

	tmsmsg.MsgType += 10;
	tmsmsg.RespCode = EZTMS_RC_Approved;
	memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
	sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
	if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
	{
		MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
		if( MsgSize < 0 )
		{
			trace( "Error in composing hypercom pos terminal...." );
			return;
		}
	}
	else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
	{
		MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
		if( MsgSize < 0 )
		{
			trace( "Error in composing castles pos terminal...." );
			return;
		}
	}
	MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
	hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
	writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
}


int EzTMSDriver :: searchPOSTxn( const char *POSTxnRefNum, struct EzTxnMsg *tmsmsg_ptr )
{
	return 1;
}

void EzTMSDriver :: populateOldTerminalRequest( struct EzTxnMsg *tmsmsg, struct EzTxnMsg *oldtmsmsg )
{
	memset( tmsmsg->DeviceType, 0, sizeof( tmsmsg->DeviceType ) );
	strcpy( tmsmsg->DeviceType, "POS" );
	memset( tmsmsg->m_chn, 0, sizeof( tmsmsg->m_chn ) );
	ezpadssutil.maskString( tmsmsg->chn, 6, strlen( tmsmsg->chn ) - 4, '*', tmsmsg->m_chn );
	memset( tmsmsg->OrgChannel, 0, sizeof( tmsmsg->OrgChannel ) );
	strcpy( tmsmsg->OrgChannel, GetSourceChannelName() );
	memset( tmsmsg->OrgPort, 0, sizeof( tmsmsg->OrgPort ) );
	strcpy( tmsmsg->OrgPort, GetLastSenderChannelName() );
	memset( tmsmsg->SrcPort, 0, sizeof( tmsmsg->SrcPort ) );
	strcpy( tmsmsg->SrcPort, tmsmsg->OrgPort );
	memset( tmsmsg->SrcChannel, 0, sizeof( tmsmsg->SrcChannel ) );
	strcpy( tmsmsg->SrcChannel, tmsmsg->OrgChannel );
}


int EzTMSDriver :: process800( struct EzTxnMsg *tmsmsg_ptr )
{
	char TermCommKey_LMK[ 65 ], TermCommKey_TMK[ 65 ];
	int MsgSize = 0;

	tmsmsg_ptr->MsgType += 10;

	if( tmsmsg_ptr->TxnCode == EZTMS_Txn_KeyDownload )
	{
		trace( "Processing Echo Request for MerchantId[%s] TerminalId[%s]", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );

		terminalstatusupdate_rec.MsgType = tmsmsg_ptr->MsgType;
		strcpy( terminalstatusupdate_rec.InstId, tmsmsg_ptr->AcquirerInst);
		strcpy( terminalstatusupdate_rec.MachineId, tmsmsg_ptr->MachineId);
		strcpy( terminalstatusupdate_rec.MerchantId, tmsmsg_ptr->AcceptorId);
		strcpy( terminalstatusupdate_rec.StoreId, tmsmsg_ptr->StoreId);
		strcpy( terminalstatusupdate_rec.TerminalId, tmsmsg_ptr->TerminalId);
		terminalstatusupdate_rec.LastTxnDate = tmsmsg_ptr->LocalDate;
		terminalstatusupdate_rec.LastTxnTime = tmsmsg_ptr->LocalTime;
		//retval = updateTerminalStatus( &terminalstatusupdate_rec, &sqlerr );
	/*	if( sqlerr !=0 )
		{
			trace("Terminal status update Err ora[%d]", sqlerr );
			return -1;
		}
		 trace("Terminal status update  retval[%d]", retval );*/
		memset( &terminalstatusupdate_rec, 0, sizeof( struct EzTMSTerminalProfile ));

		memset( TermCommKey_LMK, 0, sizeof( TermCommKey_LMK ) );
		memset( TermCommKey_TMK, 0, sizeof( TermCommKey_TMK ) );
		if( GenTerminalCommKey( tmsmsg_ptr->AcquirerInst, tmsmsg_ptr->MachineId, mmsterminalprofile_rec.TermMasterKey, strlen( mmsterminalprofile_rec.TermMasterKey ), TermCommKey_LMK, TermCommKey_TMK ) < 0 )
		{
			trace( "Error in Generating TerminalCommKey for InstId[%s] POSId[%s] MasterKey[%s]", tmsmsg_ptr->AcquirerInst, tmsmsg_ptr->MachineId, mmsterminalprofile_rec.TermMasterKey );

			tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			sprintf( ResponseBuffer, "%s%c", tmsmsg_ptr->RsvFld6, 0x1c );
			if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
			{
				MsgSize = hypercom.composeMsg( tmsmsg_ptr, ResponseBuffer + strlen( tmsmsg_ptr->RsvFld6 ) + 1 );
				if( MsgSize < 0 )
				{
					trace( "Error in composing hypercom pos terminal...." );
					return -1;
				}
			}
			else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
			{
				MsgSize = castle8583.composeMsg( tmsmsg_ptr, ResponseBuffer + strlen( tmsmsg_ptr->RsvFld6 ) + 1 );
				if( MsgSize < 0 )
				{
					trace( "Error in composing castles pos terminal...." );
					return -1;
				}
			}
			MsgSize += strlen( tmsmsg_ptr->RsvFld6 ) + 1;
			hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
			writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
			return -1;
		}
		trace( "Generated TermCommKey_LMK[%s] TermCommKey_TMK[%s] for InstId[%s] POSId[%s] MasterKey[%s]", TermCommKey_LMK, TermCommKey_TMK, tmsmsg_ptr->AcquirerInst, tmsmsg_ptr->MachineId, mmsterminalprofile_rec.TermMasterKey );

		if( updateTermCommKey( tmsmsg_ptr->MachineId, TermCommKey_LMK ) < 0 )
		{
			trace( "Error in updating TermCommKey[%s] for MachineId[%s] in DB", TermCommKey_LMK, tmsmsg_ptr->MachineId );
			tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
		}
		else
		{
			trace( "Updated TermCommKey[%s] for POSId[%s] in DB", TermCommKey_LMK, tmsmsg_ptr->MachineId );
		}

		if( updateTerminalPINKey( tmsmsg_ptr->MachineId, TermCommKey_LMK ) < 0 )
		{
			trace( "Error in updating TermCommKey[%s] for MachineId[%s] in Memory", TermCommKey_LMK, tmsmsg_ptr->MachineId );
			tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
		}
		else
		{
			trace( "Updated TermCommKey[%s] for POSId[%s] in Memory", TermCommKey_LMK, tmsmsg_ptr->MachineId );
		}

		memset( tmsmsg_ptr->RsvFld4, 0, sizeof( tmsmsg_ptr->RsvFld4 ) );
		strcpy( tmsmsg_ptr->RsvFld4, TermCommKey_TMK );

		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		sprintf( ResponseBuffer, "%s%c", tmsmsg_ptr->RsvFld6, 0x1c );
		if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
		{
			MsgSize = hypercom.composeMsg( tmsmsg_ptr, ResponseBuffer + strlen( tmsmsg_ptr->RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing hypercom pos terminal...." );
				return -1;
			}
		}
		else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
		{
			MsgSize = castle8583.composeMsg( tmsmsg_ptr, ResponseBuffer + strlen( tmsmsg_ptr->RsvFld6 ) + 1 );
			if( MsgSize < 0 )
			{
				trace( "Error in composing castles pos terminal...." );
				return -1;
			}
		}
		MsgSize += strlen( tmsmsg_ptr->RsvFld6 ) + 1;
		hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
		writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
	}
	return 0;
}

bool EzTMSDriver :: isValidTerminal( struct EzTxnMsg *tmsmsg_ptr )
{
	int retval;
	trace( "Validating MerchantId[%s] TerminalId[%s]", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );
	memset( &mmsterminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
	if( readTerminalProfile( tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId, &mmsterminalprofile_rec ) < 0 )
	{
		trace( "Error in Reading MerchantId[%s] TerminalId[%s] from EzTMSTerminalInfo Table....", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );
		tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
		tmsmsg_ptr->ReasonCode = EZTMS_Reason_POSTerminalInfo_Err;
		return false;
	}

	if( mmsterminalprofile_rec.TerminalStatus != '1' )
	{
		trace( "Terminal Status is not Active for MerchantId[%s] TerminalId[%s]", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );
		tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
		return false;
	}
	if( readMerchantProfile( mmsterminalprofile_rec.InstId, mmsterminalprofile_rec.MerchantId, &mmsmerchantprofile_rec ) < 0  )
	{
			trace( "Error in Reading MerchantId[%s] from EzTMSTerminalInfo Table....", tmsmsg_ptr->TerminalId );
			tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
			return false;
	}
	strcpy( tmsmsg_ptr->MachineId, mmsterminalprofile_rec.MachineId );
	strcpy( tmsmsg_ptr->AcquirerInst, mmsterminalprofile_rec.InstId );
	memset( tmsmsg_ptr->TerminalLocation, 0, sizeof( tmsmsg_ptr->TerminalLocation ) );
	strcpy( tmsmsg_ptr->TerminalLocation, mmsterminalprofile_rec.TerminalLocation );
	if( !tmsmsg_ptr->AcqCurrencyCode )
		tmsmsg_ptr->AcqCurrencyCode = atoi( mmsterminalprofile_rec.CurrCode );
	tmsmsg_ptr->MerchantType = mmsterminalprofile_rec.Mcc;
	tmsmsg_ptr->DeviceFlag = '1';

	if( strlen( tmsmsg_ptr->PINBlock ) != 0 )
	{
		strcpy( tmsmsg_ptr->PinKey, mmsterminalprofile_rec.TermPINKey );
		tmsmsg_ptr->PinVerFlg = 'Y';
		trace("Copied TermPINKey[%s]", tmsmsg_ptr->PinKey );
	}

	trace("mmsterminalprofile_rec.Mcc[%d]", mmsterminalprofile_rec.Mcc );
	if( !strlen( tmsmsg_ptr->BatchId ) )
	{
		if( !strcmp( mmsterminalprofile_rec.BatchId, TMS_STRINGINIT_VAL ) )
		{
			memset( tmsmsg_ptr->BatchId, 0, sizeof( tmsmsg_ptr->BatchId ) );
			eztxnsequtil.genPOSBatchId( tmsmsg_ptr->BatchId );
			trace( "Generated New BatchId[%s]", tmsmsg_ptr->BatchId );
			memset( mmsterminalprofile_rec.BatchId, 0, sizeof( mmsterminalprofile_rec.BatchId ) );
			strcpy( mmsterminalprofile_rec.BatchId, tmsmsg_ptr->BatchId );
			ConnectDB();
			if( updateTerminalBatchId( mmsterminalprofile_rec.MachineId, tmsmsg_ptr->BatchId ) < 0 )
				trace( "Error in Updating POSBatchId in Memory..." );

			retval = updateTerminalBatchInTerminalInfo( mmsterminalprofile_rec.MachineId, tmsmsg_ptr->BatchId);
			if( retval != 0 )
				trace( "Error in Updating POSBatchId in TerminalInfo Table...OraErr[%05d]", retval );

			CloseDB();
		}
		else
		{
			memset( tmsmsg_ptr->BatchId, 0, sizeof( tmsmsg_ptr->BatchId ) );
			strcpy( tmsmsg_ptr->BatchId, mmsterminalprofile_rec.BatchId );
		}
	}
	return true;
}

int EzTMSDriver :: writeToInternalChannel( const char *ChannelName, struct EzTxnMsg *tmsmsg )
{
	trace( "log chn[%s] m_chn[%s]", tmsmsg->chn, tmsmsg->m_chn );
        //trace(" log Amount is [%s]",tmsmsg->Amount);	
	trace( DEBUG_NORMAL, "<SEND>Channel(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", ChannelName, tmsmsg->DeviceType, tmsmsg->OrgChannel, tmsmsg->SrcChannel, tmsmsg->OrgPort, tmsmsg->SrcPort, tmsmsg->DestPort, tmsmsg->MsgType, tmsmsg->m_chn, tmsmsg->FromAccount, tmsmsg->TxnCode, tmsmsg->Amount, tmsmsg->TerminalId, tmsmsg->TraceNo, tmsmsg->TranDate, tmsmsg->TranTime, tmsmsg->LocalDate, tmsmsg->LocalTime, tmsmsg->RespCode, tmsmsg->ReasonCode, tmsmsg->RefNum, tmsmsg->NetworkId );
	if( WriteChannel( ChannelName, ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing Message to Channel[%s]", ChannelName );
		return -1;
	}
	else
	{
		trace( "Written Successfully Message to Channel[%s]", ChannelName );
		return 1;
	}
}

void EzTMSDriver :: writeToExternalChannel( char *ChannelName, char *ResponseBuffer, int MsgSize )
{
	trace( "Writing Message of %d Bytes to External Channel[%s]", MsgSize, ChannelName );
	if( WriteChannel( ChannelName, ResponseBuffer, MsgSize ) < 0 )
		trace( "Error in Writing Message to Channel[%s]", ChannelName );
}

void EzTMSDriver :: populateNewTerminalRequest( struct EzTxnMsg *tmsmsg )
{
	trace( "Populating New Request for TerminalId[%s]", tmsmsg->TerminalId );
	memset( tmsmsg->DeviceType, 0, sizeof( tmsmsg->DeviceType ) );
	strcpy( tmsmsg->DeviceType, "POS" );
	memset( tmsmsg->m_chn, 0, sizeof( tmsmsg->m_chn ) );
	ezpadssutil.maskString( tmsmsg->chn, 6, strlen( tmsmsg->chn ) - 4, '*', tmsmsg->m_chn );
	memset( tmsmsg->OrgChannel, 0, sizeof( tmsmsg->OrgChannel ) );
	strcpy( tmsmsg->OrgChannel, GetSourceChannelName() );
	memset( tmsmsg->OrgPort, 0, sizeof( tmsmsg->OrgPort ) );
	strcpy( tmsmsg->OrgPort, GetLastSenderChannelName() );
	memset( tmsmsg->SrcPort, 0, sizeof( tmsmsg->SrcPort ) );
	strcpy( tmsmsg->SrcPort, tmsmsg->OrgPort );
	memset( tmsmsg->SrcChannel, 0, sizeof( tmsmsg->SrcChannel ) );
	strcpy( tmsmsg->SrcChannel,tmsmsg->OrgChannel );

	if( !tmsmsg->TranDate )
		tmsmsg->TranDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->TranTime )
		tmsmsg->TranTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->LocalDate )
		tmsmsg->LocalDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->LocalTime )
		tmsmsg->LocalTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->CaptureDate )
		tmsmsg->CaptureDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->CaptureTime )
		tmsmsg->CaptureTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->SettlementDate )
		tmsmsg->SettlementDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->BusinessDate )
		tmsmsg->BusinessDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->TraceNo )
		tmsmsg->TraceNo = eztxnsequtil.genTraceNo();

	if( !strlen( tmsmsg->RefNum ) )
	{
		memset( tmsmsg->RefNum, 0, sizeof( tmsmsg->RefNum ) );
		eztxnsequtil.genNumericRefNum( tmsmsg->RefNum );
	}
}

void EzTMSDriver :: serviceRequest()
{
	int MsgSize, tempTxnCode, NRoutes, retval;
	struct EzTxnMsg tmsmsg, localtmsmsg;
	struct EzTMSRouteSelect tmsrouteselect_rec;
	char RouteSelectList[ 129 ], RouteSelectId[ 33 ], ChannelName[ 33 ], ConnectionRefNum[ 51 ], MerchId[ 33 ];
	bool EXTFLAG = false;
	char TermCommKey_LMK[ 49 ],TermCommKey_TMK[ 49 ];
	char TMSTxnRefNum[ 151 ], OldTMSTxnRefNum[ 151 ];
	struct EzTMSTxnMemory tmstxnmemory_rec;
	unsigned char LogFlag;
	char tempamt[15];
	while( 1 )
	{
		memset( &mmsterminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
		trace( "TMSDriver Waiting for Request to be Serviced...." );
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		if( ReadMessage( RequestBuffer, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			sleep( 1 );
			continue;
		}

		trace( "Message of size[ %d ] Received from Channel[ %s ]", MsgSize, GetLastSenderChannelName() );

		if( readTMSChannelProperty( GetLastSenderChannelName() ) < 0 )
		{
				trace( "Error in Reading ChannelName[%s] from TMSChannelProperty", GetLastSenderChannelName() );
				continue;
		}

		if( isTerminalChannel() )
		{
			trace( "Got Message from Terminal Channel[%s]", GetLastSenderChannelName() );
			memset( ConnectionRefNum, 0, sizeof( ConnectionRefNum ) );
			tkutil.getToken( RequestBuffer, ConnectionRefNum, 0x1c, 1 );
			trace( "Got ConnectionRefNum[%s]", ConnectionRefNum );

			if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
			{
				trace( "TMS Protocol Identified as HYPERCOM....");
				memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
				if( hypercom.decomposeMsg( RequestBuffer + strlen ( ConnectionRefNum ) + 1, &tmsmsg ) < 0 )
				{
					trace( "Error while decomposing message from hypercom pos terminal....." );
					continue;
				}
				trace( "Mapping Transaction Code" );
				tempTxnCode = hypercom.getTMSTxnCode( tmsmsg.TxnCode );
			}
			else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
			{
				trace( "TMS Protocol Identified as CASTLES....");
				memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
				if( castle8583.decomposeMsg( RequestBuffer + strlen ( ConnectionRefNum ) + 1, &tmsmsg ) < 0 )
				{
					trace( "Error while decomposing message from castles pos terminal....." );
					continue;
				}
				trace( "Mapping Transaction Code" );
				tempTxnCode = castle8583.getTMSTxnCode( tmsmsg.TxnCode );
			}
			else
			{
				trace( "TMS Protocol[%s] Not Supported.....", getTMSProtocol() );
				continue;
			}

			trace( "After decomposing chn[%s]", tmsmsg.chn );
			memset( tmsmsg.RsvFld6, 0, sizeof( tmsmsg.RsvFld6 ) );
			strcpy( tmsmsg.RsvFld6, ConnectionRefNum );
			memset( tmsmsg.OrgPort, 0, sizeof( tmsmsg.OrgPort ) );
			strcpy( tmsmsg.OrgPort, GetLastSenderChannelName() );
			trace( "Decomposed Successfully...." );
			trace( "Terminal TxnCode[%d] Mapped to TMS TxnCode[%d]", tmsmsg.TxnCode, tempTxnCode );
			tmsmsg.TxnCode = tempTxnCode;
			if( tmsmsg.TxnCode == 950000 )
				memcpy( tmsmsg.NewPINBlock, tmsmsg.PINBlock, sizeof( tmsmsg.PINBlock ) );
		}
		else if ( !isExternalApplication() )
		{
			memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &tmsmsg, RequestBuffer, sizeof( struct EzTxnMsg ) );
			trace( DEBUG_NORMAL, "<RECV>Channel(%s)AcqInst(%s)MerchantId(%s)TerminalId(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", GetLastSenderChannelName(), tmsmsg.AcquirerInst, tmsmsg.AcceptorId, tmsmsg.TerminalId, tmsmsg.DeviceType,tmsmsg.OrgChannel, tmsmsg.SrcChannel, tmsmsg.OrgPort, tmsmsg.SrcPort, tmsmsg.DestPort, tmsmsg.MsgType, tmsmsg.m_chn, tmsmsg.FromAccount, tmsmsg.TxnCode, tmsmsg.Amount, tmsmsg.TerminalId, tmsmsg.TraceNo, tmsmsg.TranDate, tmsmsg.TranTime, tmsmsg.LocalDate, tmsmsg.LocalTime, tmsmsg.RespCode, tmsmsg.ReasonCode, tmsmsg.RefNum, tmsmsg.NetworkId );
		}

		if( readTMSInBoundProperty( tmsmsg.MsgType, tmsmsg.TxnCode, GetLastSenderChannelName() ) < 0 )
		{
			trace( "Error in reading MsgType[%d] TxnCode[%d] ChannelName[%s] from TMSInBoundProperty....", tmsmsg.MsgType, tmsmsg.TxnCode, GetLastSenderChannelName() );
			continue;
		}

		if( isInBoundTxnMsg() )
		{
			trace( "Transaction Message Received from Channel[%s]", GetLastSenderChannelName() );
			if( !isValidTerminal( &tmsmsg ) )
			{
				trace( "Terminal with MachineId[%s] is not valid....", tmsmsg.MachineId );
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_InvalidMachineId;
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
				if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
				{
					MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
					if( MsgSize < 0 )
					{
						trace( "Error in composing hypercom pos terminal...." );
						continue;
					}
				}
				else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
				{
					MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
					if( MsgSize < 0 )
					{
						trace( "Error in composing castles pos terminal...." );
						continue;
					}
				}
				MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
				hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
				writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
				continue;
			}

			if( tmsmsg.MsgType == 800 )
			{
				trace( "calling process800" );
				process800( &tmsmsg );
				continue;
			}

			if( tmsmsg.MsgType == 500 )
			{
				trace( "calling process500" );
				process500( tmsmsg );
				continue;
			}

			if( tmsmsg.MsgType == 320 )
			{
				trace( "calling process320" );
				process320( tmsmsg );
				continue;
			}

			if( isInBoundNewTxnRequest() )
			{
				trace( "New Request Received from TerminalId[%s]", tmsmsg.TerminalId );
				populateNewTerminalRequest( &tmsmsg );
			}
			else if ( isInBoundTxnOldRequest() )
			{
				trace( "chn[%s]", tmsmsg.chn );
				trace( "Got Old Request[%d] TxnCode[%d] from Terminal[%s]", tmsmsg.MsgType, tmsmsg.TxnCode, mmsterminalprofile_rec.MachineId );
				if( (tmsmsg.MsgType==200 )&& (tmsmsg.TxnCode==620000) )
				{	
					memset(tempamt,0,sizeof(tempamt));
					strcpy(tempamt,tmsmsg.Amount);
					trace("Amount before as [%s]",tmsmsg.Amount );
					trace("Temporary Amount is [%s]",tempamt );
					strcat(tmsmsg.Amount,"0");
					trace("Amount modified as [%s]",tmsmsg.Amount );
				}
				trace("Amount outside as [%s]",tmsmsg.Amount );
				int RelTxnCode;
				char TxnCodeStr1[ 7 ], TxnCodeStr2[ 7 ];
				RelTxnCode = getRelatedTxnCode( mmsterminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
				if( RelTxnCode < 0 )
				{
						trace( "Error in Searching Relation TxnCode for TerminalType[%s] MsgType[%d] TxnCode[%d]", mmsterminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
						tmsmsg.MsgType += 10;
						tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
						memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
						sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
						if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
						{
							MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
							if( MsgSize < 0 )
							{
								trace( "Error in composing hypercom pos terminal...." );
								continue;
							}
						}
						else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
						{
							MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
							if( MsgSize < 0 )
							{
								trace( "Error in composing castles pos terminal...." );
								continue;
							}
						}

						MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
						hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
						writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
						continue;
				}

				memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
				sprintf( TxnCodeStr1, "%02d", RelTxnCode );
				memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
				sprintf( TxnCodeStr2, "%06d", tmsmsg.TxnCode );
				strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );
				tempTxnCode = tmsmsg.TxnCode;
				tmsmsg.TxnCode = atoi( TxnCodeStr1 );
				trace( "Got Relation as TxnCode[%d]", tmsmsg.TxnCode );
				trace( "Test2...chn[%s]", tmsmsg.chn );
                                
				memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum );
				trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
				if( ( tmsmsg.MsgType==200 ) && ( tmsmsg.TxnCode == 610000 ))
        			{	
					trace(" void txn Temp Amount is [%s]",tempamt);
                			memset(tmsmsg.Amount,0,sizeof(tmsmsg.Amount));
                			strcpy(tmsmsg.Amount,tempamt);
                			trace(" original  void txn Amount is [%s]",tmsmsg.Amount);
        			}	
				tmsmsg.TxnCode = atoi( TxnCodeStr2 );

				if( ConnectDB() < 0 )
				{
					trace( "Error in connecting with switch database..." );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
					memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
					sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
					if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
					{
						MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
						if( MsgSize < 0 )
						{
							trace( "Error in composing hypercom pos terminal...." );
							continue;
						}
					}
					else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
					{
						MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
						if( MsgSize < 0 )
						{
							trace( "Error in composing castles pos terminal...." );
							continue;
						}
					}
					MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
					hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
					writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
					continue;
				}
				//memset( &tmstxnmemory_rec, 0, sizeof( struct EzTMSTxnMemory ) );
				//if( readTMSTxnMemory( mmsterminalprofile_rec.MachineId, OldTMSTxnRefNum, &tmstxnmemory_rec ) < 0 )
				//{
					//trace( "Error in Locating LookUp POSTxnRefNum[%s] from Memory...Try it Database", OldTMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				retval = searchTerminalTxn( OldTMSTxnRefNum, &tmstxnmemory_rec.txnmsg );
				CloseDB();
				if( retval != 0 )
				{
					trace( "Error in Searching POSTxnRefNum[%s] from EzPOSBatchInfo...SqlErr[%05d]", OldTMSTxnRefNum, retval );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
					sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
					if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
					{
						MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
						if( MsgSize < 0 )
						{
							trace( "Error in composing hypercom pos terminal...." );
							continue;
						}
					}
					else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
					{
						MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
						if( MsgSize < 0 )
						{
							trace( "Error in composing castles pos terminal...." );
							continue;
						}
					}
					MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
					hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
					writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
					continue;
				}
				trace( "chn[%s]", tmsmsg.chn );
				populateOldTerminalRequest( &tmsmsg, &tmstxnmemory_rec.txnmsg );
				trace( "chn[%s] m_chn[%s]", tmsmsg.chn, tmsmsg.m_chn );
			}
			else if ( isInBoundTxnRevRequest() )
			{


			}
		}
		else
			trace( "Not a Transaction Message...." );

		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
		if( getTMSRouteSelectList( &tmsmsg, RouteSelectList ) < 0 )
		{
			trace( "Error in reading TMSRouteSelectList.....Dropping Message" );	
			if( isInBoundNewRequest() )
			{
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
				if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
				{
					MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
					if( MsgSize < 0 )
					{
						trace( "Error in composing hypercom pos terminal...." );
						continue;
					}
				}
				else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
				{
					MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
					if( MsgSize < 0 )
					{
						trace( "Error in composing castles pos terminal...." );
						continue;
					}
				}
				writeToExternalChannel( GetLastSenderChannelName(), ResponseBuffer, MsgSize );
				continue;
			}
		}
		
		NRoutes = tkutil.getNToken( RouteSelectList, ',' );
		for( int i = 0; i < NRoutes; i++ )
		{
			memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
			tkutil.getTokenExSpaces( RouteSelectList, RouteSelectId, ',', i + 1 );

			memset( &tmsrouteselect_rec, 0, sizeof( struct EzTMSRouteSelect ) );
			if( readTMSRouteSelect( RouteSelectId, &tmsrouteselect_rec ) < 0 )
			{
					trace( DEBUG_ERROR, "Error in Reading RouteSelectId[%s] From TMSRouteSelect...", RouteSelectId );
					continue;
			}

			trace( DEBUG_NORMAL, "Read ChannelName[%s] MsgTranslateId[%s] from TMSRouteSelect for RouteSelectId[%s]",  tmsrouteselect_rec.ChannelName, tmsrouteselect_rec.MsgTranslateId, RouteSelectId );
			
			memset( &localtmsmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &localtmsmsg, &tmsmsg, sizeof( struct EzTxnMsg ) );
			trace( "chn[%s]", tmsmsg.chn );
			if( strcmp( tmsrouteselect_rec.MsgTranslateId, "*" ) )
			{
				if( translateMsg( tmsrouteselect_rec.MsgTranslateId, &localtmsmsg ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Reading MsgTranslateId[%s] from EzTMSMsgTranslate Table", tmsrouteselect_rec.MsgTranslateId );
					continue;

				}
			}
		
			if( isInBoundTxnMsg() )
			{
				LogFlag = 0x0;

				if( tmsrouteselect_rec.LogTxnReq == 'Y' || tmsrouteselect_rec.LogTxnReq == 'y' )
					LogFlag = LogFlag | 0x1;


				if( ( tmsrouteselect_rec.LogBatchReq == 'Y' || tmsrouteselect_rec.LogBatchReq == 'y' ) && ( localtmsmsg.MsgType == 210 && localtmsmsg.RespCode == EZTMS_RC_Approved ) )
					LogFlag = LogFlag | 0x2;

				if( tmsrouteselect_rec.LogTotReq == 'Y' || tmsrouteselect_rec.LogTotReq == 'y' )
					LogFlag = LogFlag | 0x4;

				memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
				getTMSTxnRefNum( &localtmsmsg, TMSTxnRefNum );

				trace( "TxnRefNum[%s]..test ", TMSTxnRefNum );
				trace( "log chn[%s] m_chn[%s]", tmsmsg.chn, tmsmsg.m_chn );
				if( logTMSTxnInfo( LogFlag, TMSTxnRefNum, &localtmsmsg ) < 0 )
					trace( "Error in sending logging message TMSLogger Channel..." );

			}

			if( !strcmp( tmsrouteselect_rec.ChannelName, EZTMSIMF_DESTPORT ) )
			{
				EXTFLAG = true;
				if( ( !strlen( localtmsmsg.DestPort ) ) || ( !strcmp( localtmsmsg.DestPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "DestPort is NULL..Cannot Route Message to DestPort");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtmsmsg.DestPort );
			}
			if( !strcmp( tmsrouteselect_rec.ChannelName, EZTMSIMF_ORGPORT ) )
			{
				EXTFLAG = true;
				if( ( !strlen( localtmsmsg.OrgPort ) ) || ( !strcmp( localtmsmsg.OrgPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "OrgPort is NULL..Cannot Route Message to OrgPort");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtmsmsg.OrgPort );
			}
			else
			{
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, tmsrouteselect_rec.ChannelName );
				EXTFLAG = false;
			}

			if( strcmp( ChannelName, "*" ) && strcmp( ChannelName, GetSourceChannelName() ) )
			{
				trace( "log chn[%s] m_chn[%s]", tmsmsg.chn, tmsmsg.m_chn );
				if( EXTFLAG )
				{
					memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
					sprintf( ResponseBuffer, "%s%c", tmsmsg.RsvFld6, 0x1c );
					if( !strcasecmp( getTMSProtocol(), "HYPERCOM" ) )
					{
						MsgSize = hypercom.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
						if( MsgSize < 0 )
						{
							trace( "Error in composing hypercom pos terminal...." );
							continue;
						}
					}
					else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
					{
						MsgSize = castle8583.composeMsg( &tmsmsg, ResponseBuffer + strlen( tmsmsg.RsvFld6 ) + 1 );
						if( MsgSize < 0 )
						{
							trace( "Error in composing castles pos terminal...." );
							continue;
						}
					}
					MsgSize += strlen( tmsmsg.RsvFld6 ) + 1;
					writeToExternalChannel( ChannelName, ResponseBuffer, MsgSize );
				}
				else
					writeToInternalChannel( ChannelName,  &tmsmsg );
			}
		}
	}
}


int main( int argc, char **argv )
{
	EzTMSDriver eztmsdriverobj;
	eztmsdriverobj.initTMSDriver( argv[ 0 ] );
	eztmsdriverobj.serviceRequest();
	return 1;
}



	

