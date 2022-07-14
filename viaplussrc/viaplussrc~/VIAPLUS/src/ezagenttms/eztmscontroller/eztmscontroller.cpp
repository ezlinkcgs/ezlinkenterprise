#include <eztms/eztmscontroller.h>

int month_list[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int EzTMSController :: init( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztmscontroller.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
	   trace( DEBUG_ERROR,"Error in Initializing EzTaskUtil" );
	   trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
	   closeDebug( );
	   exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzChannelUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( CHANNEL_NAME_TMSCONTROLLER, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating %s Channel", CHANNEL_NAME_TMSCONTROLLER );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initTMSDriverUtil(  this ) < 0 )
	{
		trace( "Error in Initializing TMSDriver Util..." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initMMSUtil( this ) < 0 )
	{
		trace( "Error in Initializing MMSUtil..." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initSchemaInfoUtil( this ) < 0 )
	{
		trace( "Error in Initializing SchemaInfoUtil..." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this, "EZMMS" ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( SchemaType == SCHEMA_TYPE_SINGLE )
	{
		if( dbutil.DBConnect() < 0 )
		{
			trace( "Error in Connecting with MMS Database..." );
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
		}
	}

	if( ezinstprofileutil.initInstProfile( this ) < 0 )
	{
		trace( "Error in Initializing InstProfileUtil...." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eztms.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSKEY#GLOBALMASTERKEY", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching TMSKEY#GLOBALMASTERKEY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	cfgutil.cfg_close();

	memset( GlobalMasterKey, 0, sizeof( GlobalMasterKey ) );
	strcpy( GlobalMasterKey, cfgval );

	if( secobj.InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing SecurityUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
	return 1;
}

void EzTMSController :: serviceRequest()
{
	struct EzTxnMsg tmsmsg;
	int MsgSize;

	while( 1 )
	{
		/*
		if( SchemaType != SCHEMA_TYPE_SINGLE )
			CloseSchema();
		*/
		memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * ) &tmsmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from %s Channel....", GetSourceChannelName() );	
			sleep( 1 );
			continue;
		}

		memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
		if( readTerminalProfile( tmsmsg.MachineId, &terminalprofile_rec ) < 0 )
		{
			trace( "Error in Reading TerminalProfile Memory with MachineId[%s]...", tmsmsg.MachineId );
			continue;
		}
		trace( "Read TerminalId[%s]...", terminalprofile_rec.TerminalId );
		//trace("Reading fit profile instid[%s]",tmsmsg.IssuerInst );
		/*if( readFITProfile( tmsmsg.IssuerInst,&fitprofile_ptr ) < 0 )
	    {
			trace( "Error in Reading TerminalFIT..." );
			continue;
        }*/

		if( SchemaType != SCHEMA_TYPE_SINGLE )
		{
			if( ConnectSchema( terminalprofile_rec.InstId, "MMS", "*" ) < 0 )
			{
				continue;
			}
		}

		trace( "Read Controller Memory with MachineId[%s] CurrentCommand[%d]...", terminalprofile_rec.MachineId, terminalprofile_rec.CurrentCommand );

		if( tmsmsg.MsgType == EZTMS_MTYPE_DownloadRequest )
		{
			trace( "Download Request from MachineId[%s]", tmsmsg.MachineId );
			if( tmsmsg.TxnCode == 700000 )
			{
				trace( "Received Master Key Download Request from MachineId[%s]", tmsmsg.MachineId );
				processMasterKeyDownload( &tmsmsg );
			}
			else if( tmsmsg.TxnCode == 700001 )
			{
				trace( "Received Forced Download Request from MachineId[%s]", tmsmsg.MachineId );
				initTerminalProfile( tmsmsg.MachineId,MaxTerminal );
				startDownload( &tmsmsg );
			}
			else
			{
				trace( "Received Normal Download Request from MachineId[%s]", tmsmsg.MachineId );
				if( configMatch( &tmsmsg ) )
				{
					trace( "Download Configuration Matched for MachineId[%s]..No need to Send Download", tmsmsg.MachineId );
					processDownloadCompletion( &tmsmsg );
				}
				else
				{
					trace( "Download Configuration did not match for MachineId[%s]..Starting Download", tmsmsg.MachineId );
					initTerminalProfile( tmsmsg.MachineId,MaxTerminal );
					startDownload( &tmsmsg );
				}
			}
		}
		else if ( tmsmsg.MsgType == EZTMS_MTYPE_DownloadAdviceResponse )
		{
			trace( "Received Download Advice Response from MachineId[%s]", tmsmsg.MachineId );
			if( tmsmsg.RespCode != EZTMS_RC_Approved )
			{
				trace( "Bad Download Acknowledgement Received for MachineId[%s]...Cannot Continue Download", tmsmsg.MachineId );
				continue;
			}
			if( tmsmsg.TxnCode == 700001 )
			{
				trace( "Received Good Acknowledgement for Terminal Information Download for MachineId[%s]", tmsmsg.MachineId );
				terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_STATEINFO;
				terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_SCREENINFO;
				updateTerminalProfile( terminalprofile_rec );

			}
			continueDownload( &tmsmsg );
		}
	}
}

bool EzTMSController :: configMatch( struct EzTxnMsg *tmsmsg )
{
	trace( "Matching terminalprofile_rec.ConfigId[%s] tmsmsg->RsvFld2[%s]", terminalprofile_rec.ConfigId, tmsmsg->RsvFld2 );
	if( !strcmp( terminalprofile_rec.ConfigId, tmsmsg->RsvFld2 ) )
		return true;
	else
	{
		memset( terminalprofile_rec.ConfigId, 0, sizeof( terminalprofile_rec.ConfigId ) );
		getNewConfigId( terminalprofile_rec.ConfigId );
		updateTerminalProfile( terminalprofile_rec );
		return false;
	}
}

int EzTMSController :: writeMsg( struct EzTxnMsg *tmsmsg )
{
	trace( "Writing msgtype(%d)TxnCode(%d)ResponseCode(%d)", tmsmsg->MsgType, tmsmsg->TxnCode, tmsmsg->RespCode );
	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing Message To Channel<%s>...", GetLastSenderChannelName() );
		return -1;
	}
	return 1;
}

void EzTMSController :: startDownload( struct EzTxnMsg *tmsmsg )
{
	terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_TERMINALINFO;
	terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_STATEINFO;
	terminalprofile_rec.LineNo = 0;
	memset( terminalprofile_rec.ConfigId, 0, sizeof( terminalprofile_rec.ConfigId ) );
	getNewConfigId( terminalprofile_rec.ConfigId );
	trace( "Writing ConfigId[%s] to Memory...", terminalprofile_rec.ConfigId );
	updateTerminalProfile( terminalprofile_rec );
	continueDownload( tmsmsg );
}

void EzTMSController :: continueDownload( struct EzTxnMsg *tmsmsg )
{
	switch( terminalprofile_rec.CurrentCommand )
	{
		case TMS_DOWNLOAD_CMD_TERMINALINFO:
		{
			processTerminalInfoDownload( tmsmsg );
			break;
		}

		case TMS_DOWNLOAD_CMD_FITINFO:
		{
			processFITInfoDownload( tmsmsg );
			break;
		}
		case TMS_DOWNLOAD_CMD_TIMERINFO:
		{
			processTimerInfoDownload( tmsmsg );
			break;
		}
		case TMS_DOWNLOAD_CMD_STATEINFO:
		{
			processStateInfoDownload( tmsmsg );
			break;
		}
		case TMS_DOWNLOAD_CMD_SCREENINFO:
		{
			processScreenInfoDownload( tmsmsg );
			break;
		}
		case TMS_DOWNLOAD_CMD_TXNMAPINFO:
		{
			processTxnMapInfoDownload( tmsmsg );
			break;
		}

		case TMS_DOWNLOAD_CMD_GOODRESPMAP:
		{
			processGoodRespMapDownload( tmsmsg );
			break;
		}

		case TMS_DOWNLOAD_CMD_BADRESPMAP:
		{
			processBadRespMapDownload( tmsmsg );
			break;
		}
		case TMS_DOWNLOAD_CMD_OPERATOR:
		{
			processOperatorInfoDownload( tmsmsg );
			break;
		}
		case TMS_DOWNLOAD_CMD_TEMPLATE:
		{
			processTemplateInfoDownload( tmsmsg );
			break;
		}

		case TMS_DOWNLOAD_CMD_COMPLETED:
		{
			processDownloadCompletion( tmsmsg );
			break;
		}
	}
}

void EzTMSController :: processDownloadCompletion( struct EzTxnMsg *tmsmsg )
{
	trace( "Processing Download Completion for MachineId[%s]", tmsmsg->MachineId );

	tmsmsg->MsgType = 710;
	tmsmsg->TxnCode = 700001;
	tmsmsg->RespCode = EZTMS_RC_Approved;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	trace( "Download Completion..ConfigId[%s]", terminalprofile_rec.ConfigId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, terminalprofile_rec.ConfigId );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Download Completion Message to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Download Completion Message to Channel[%s]", GetLastSenderChannelName() );
}

int EzTMSController :: processTemplateInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char TemplateBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	trace( "Processing Timer Information Download for MachienId[%s]", tmsmsg->MachineId );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_prt.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/template", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_prt.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/template", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_prt.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/template", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_prt.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/template", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_prt.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/template", terminalprofile_rec.TerminalType );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_prt.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/template", "DEFAULT" );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int TemplateCount = cfg_group_count( "TEMPLATE_INFO" );
	if( TemplateCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group TEMPLATE_INFO in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( TemplateBuffer, 0, sizeof( TemplateBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < TemplateCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "TEMPLATE_INFO", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group STATE_INFO in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "TEMPLATE_INFO", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			strcat( LineBuffer, cfgval );
		}
		if( ( strlen( TemplateBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;

		strcat( TemplateBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close( );

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= TemplateCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_COMPLETED;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_COMPLETED;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700009;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, TemplateBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Template Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Template Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

void EzTMSController :: processMasterKeyDownload( struct EzTxnMsg *tmsmsg )
{
	char TermMasterKey_LMK[ 65 ], TermMasterKey_GKey[ 65 ], TermMasterKey_KVC[ 65 ];
	int retval;

	trace( "Processing Master Key Download for MachineId[%s]", tmsmsg->MachineId );
	tmsmsg->MsgType += 10;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );

	memset( TermMasterKey_LMK, 0, sizeof( TermMasterKey_LMK ) );
	memset( TermMasterKey_GKey, 0, sizeof( TermMasterKey_GKey ) );
	memset( TermMasterKey_KVC, 0, sizeof( TermMasterKey_KVC ) );
	if( secobj.GenTerminalCommKey( terminalprofile_rec.InstId, terminalprofile_rec.TerminalId, GlobalMasterKey, strlen( GlobalMasterKey ), TermMasterKey_LMK, TermMasterKey_GKey, TermMasterKey_KVC ) < 0 )
	{
		trace( "Error in Generating Terminal Master Key for InstId[%s] TerminalId[%s] GlobalMasterKey[%s]", terminalprofile_rec.InstId, terminalprofile_rec.TerminalId, GlobalMasterKey );
		tmsmsg->RespCode = 5;
	}
	else
	{
		memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
		strcpy( tmsmsg->RsvFld2, TermMasterKey_GKey );
		memset( tmsmsg->RsvFld3, 0, sizeof( tmsmsg->RsvFld3 ) );
		strcpy( tmsmsg->RsvFld3, TermMasterKey_KVC );
		if( updateTermMasterKeyinMemory( terminalprofile_rec.MachineId, TermMasterKey_LMK ) < 0 )
		{
			trace( "Error in Updating TerminalMasterKey[%s] for MachineId[%s] in Memory", TermMasterKey_LMK, terminalprofile_rec.MachineId );
			tmsmsg->RespCode = 5;
		}
		else
		{
			retval = updateTermMasterKeyinTable( terminalprofile_rec.MachineId, TermMasterKey_LMK );
			if( retval != 0 )
			{
				if( SchemaType == SCHEMA_TYPE_SINGLE )
				{
					if( MMS_ORA_CONNECT_ERR( retval ) )
					{
						if( dbutil.DBConnect() < 0 )
							trace( "Error in Connecting with MMS Database....Cannot Update TerminalMasterKey[%s] for MachineId[%s] in Table", TermMasterKey_LMK, terminalprofile_rec.MachineId );
						else
							retval = updateTermMasterKeyinTable( terminalprofile_rec.MachineId, TermMasterKey_LMK );
					}
				}
				else
				{
					if( MMS_ORA_CONNECT_ERR( retval ) )
					{
						if( reConnectSchema() < 0 )
							trace( "Error in Connecting with MMS Database....Cannot Update TerminalMasterKey[%s] for MachineId[%s] in Table", TermMasterKey_LMK, terminalprofile_rec.MachineId );
						else
							retval = updateTermMasterKeyinTable( terminalprofile_rec.MachineId, TermMasterKey_LMK );
					}
				}
			}
			if( retval != 0 )
			{
				trace( "Error in Updating TerminalMasterKey[%s] for MachineId[%s] in Table..ORAERR[%05d]", TermMasterKey_LMK, terminalprofile_rec.MachineId, retval );
				tmsmsg->RespCode = 5;
			}
			else
				tmsmsg->RespCode = 0;
		}
	}

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Master Key Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Information Download to Channel[%s]", GetLastSenderChannelName() );
}

void EzTMSController :: processTerminalInfoDownload( struct EzTxnMsg *tmsmsg )
{
	trace( "Processing Terminal Information Download for MachienId[%s]", tmsmsg->MachineId );
	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700001;
	memset( tmsmsg->TerminalId, 0, sizeof( tmsmsg->TerminalId ) );
	strcpy( tmsmsg->TerminalId, terminalprofile_rec.TerminalId );
	trace( "Copied TerminalId[%s]", terminalprofile_rec.TerminalId );
	memset( tmsmsg->TerminalLocation, 0, sizeof( tmsmsg->TerminalLocation ) );
	strcpy( tmsmsg->TerminalLocation, terminalprofile_rec.TerminalLocation );
	memset( tmsmsg->AcceptorId, 0, sizeof( tmsmsg->AcceptorId ) );
	strcpy( tmsmsg->AcceptorId, terminalprofile_rec.MerchantId );
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( &merchantprofile_ptr, 0, sizeof( struct EzMMSMerchantProfile ) );
	if( ( readMerchantProfile( terminalprofile_rec.InstId, terminalprofile_rec.MerchantId, &merchantprofile_ptr ) )< 0 )
	{
			trace( "Error in Reading Merchant profile memory... ");
			return;
	}

	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, merchantprofile_ptr.CurrList );
	sprintf( tmsmsg->RsvFld2 + strlen( merchantprofile_ptr.CurrList ), "%c%s%c", 0x1c, terminalprofile_rec.CountryCode, 0x1c );
	memset( tmsmsg->RsvFld3, 0, sizeof( tmsmsg->RsvFld3 ) );

	if( ( readStoreProfile( terminalprofile_rec.InstId, terminalprofile_rec.MerchantId, terminalprofile_rec.StoreId, &storeprofile_ptr ) < 0 ) )
	{
		trace( "Error in Reading Store Memory..." );
		return;
	}

	sprintf( tmsmsg->RsvFld3, "%s%c%s%c%s%c%s%c%s%c%s%c%06d%c%06d%c", ezinstprofileutil.getInstName(), 0x1c, merchantprofile_ptr.MerchantName, 0x1c, storeprofile_ptr.StoreName, 0x1c, storeprofile_ptr.StoreLocation, 0x1c, storeprofile_ptr.CityName, 0x1c, storeprofile_ptr.CityCode, 0x1c, ezdatetimeutil.getSysDate(), 0x1c, ezdatetimeutil.getSysTime(), 0x1c );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Terminal Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Information Download to Channel[%s]", GetLastSenderChannelName() );
}

int EzTMSController :: processFITInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FITBuffer[ TMS_STATE_BUFFER_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	bool found = false;
	struct EzMMSFITProfile fitprofile_rec;
	int tableoffset = 0;

        trace( "Processing FIT Information Download for MachienId[%s]", tmsmsg->MachineId );

        memset( &fitprofile_rec, 0, sizeof( struct EzMMSFITProfile ) );

        memset( fitprofile_rec.InstId, 0, sizeof( fitprofile_rec.InstId ) );
        strcpy( fitprofile_rec.InstId, terminalprofile_rec.InstId );
        found = false;
        for( int i = tableoffset; i < MaxFIT; i++ )
        {
                if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_rec.InstId ) )
                {
                        found = true;
                        tableoffset = i;
                        break;
                }
        }

	if( !found )
	{
		memset( fitprofile_ptr.InstId, 0, sizeof( fitprofile_ptr.InstId ) );
		strcpy( fitprofile_ptr.InstId, "*" );
		for( int i = tableoffset; i < MaxFIT; i++ )
		{
			if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) )
			{
				found = true;
				tableoffset = i;
				break;
			}
		}
		if( !found )
		{
			trace( "Error in Searching InstId[%s] in EzTMSFitProfile...", fitprofile_ptr.InstId );
			return -1;
		}
	}

	memset( fitprofile_ptr.MerchantType, 0, sizeof( fitprofile_ptr.MerchantType ) );
	//strcpy( fitprofile_ptr.MerchantType, terminalprofile_rec.MerchantType );
	strcpy( fitprofile_ptr.MerchantType, terminalprofile_rec.TerminalType );
	found = false;
	for( int i = tableoffset; i < MaxFIT; i++ )
	{
		if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) )
		{
			found = true;
			tableoffset = i;
			break;
		}
	}

	if( !found )
	{
		memset( fitprofile_ptr.MerchantType, 0, sizeof( fitprofile_ptr.MerchantType ) );
		strcpy( fitprofile_ptr.MerchantType, "*" );
		for( int i = tableoffset; i < MaxFIT; i++ )
		{
			if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) )
			{
				found = true;
				tableoffset = i;
				break;
			}
		}
		if( !found )
		{
			trace( "Error in Searching InstId[%s] MerchantType[%s] in EzTMSFitProfile...", fitprofile_ptr.InstId, fitprofile_ptr.MerchantType );
			return -1;
		}
	}

	memset( fitprofile_ptr.MerchantId, 0, sizeof( fitprofile_ptr.MerchantId ) );
	strcpy( fitprofile_ptr.MerchantId, terminalprofile_rec.MerchantId );

	found = false;
	for( int i = tableoffset; i < MaxFIT; i++ )
	{
		if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantId, fitprofile_ptr.MerchantId ) )
		{
			found = true;
			tableoffset = i;
			break;
		}
	}

	if( !found )
	{
		memset( fitprofile_ptr.MerchantId, 0, sizeof( fitprofile_ptr.MerchantId ) );
		strcpy( fitprofile_ptr.MerchantId, "*" );
		for( int i = tableoffset; i < MaxFIT; i++ )
		{
			if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantId, fitprofile_ptr.MerchantId ) )
			{
				found = true;
				tableoffset = i;
				break;
			}
		}
		if( !found )
		{
			trace( "Error in Searching InstId[%s] MerchantType[%s] MerchantId[%s] in EzTMSFitProfile...", fitprofile_ptr.InstId, fitprofile_ptr.MerchantType, fitprofile_ptr.MerchantId );
			return -1;
		}
	}

	memset( fitprofile_ptr.TerminalId, 0, sizeof( fitprofile_ptr.TerminalId ) );
	strcpy( fitprofile_ptr.TerminalId, terminalprofile_rec.TerminalId );

	found = false;
	for( int i = tableoffset; i < MaxFIT; i++ )
	{
		if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantId, fitprofile_ptr.MerchantId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->TerminalId, fitprofile_ptr.TerminalId ) )
		{
			found = true;
			tableoffset = i;
			break;
		}
	}

	if( !found )
	{
		memset( fitprofile_ptr.TerminalId, 0, sizeof( fitprofile_ptr.TerminalId ) );
		strcpy( fitprofile_ptr.TerminalId, "*" );
		for( int i = tableoffset; i < MaxFIT; i++ )
		{
			if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantId, fitprofile_ptr.MerchantId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->TerminalId, fitprofile_ptr.TerminalId ) )
			{
				found = true;
				tableoffset = i;
				break;
			}
		}
		if( !found )
		{
			trace( "Error in Searching InstId[%s] MerchantType[%s] MerchantId[%s] TerminalId[%s] in EzTMSFitProfile...", fitprofile_ptr.InstId, fitprofile_ptr.MerchantType, fitprofile_ptr.MerchantId, fitprofile_ptr.TerminalId );
			return -1;
		}
	}

	int LineCount = 0;

	memset( FITBuffer, 0, sizeof( FITBuffer ) );
	for( int i = tableoffset; i < MaxFIT; i++ )
	{
		if( !strcmp ( ( MMSFITProfileShmPtr + i )->InstId, fitprofile_ptr.InstId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantType, fitprofile_ptr.MerchantType ) && !strcmp ( ( MMSFITProfileShmPtr + i )->MerchantId, fitprofile_ptr.MerchantId ) && !strcmp ( ( MMSFITProfileShmPtr + i )->TerminalId, fitprofile_ptr.TerminalId ) )
		{
			memset( LineBuffer, 0, sizeof( LineBuffer ) );
			sprintf( LineBuffer, "%s%c%c%c%c%c%c%c%d%c%d%c", ( MMSFITProfileShmPtr + i )->FITRecord, 0x1d, ( MMSFITProfileShmPtr + i )->IndirectState, 0x1d, ( MMSFITProfileShmPtr + i )->LocalPINVerFlag, 0x1d, ( MMSFITProfileShmPtr + i )->LocalFingerPrintFlag, 0x1d, ( MMSFITProfileShmPtr + i )->MinPINLen, 0x1d, ( MMSFITProfileShmPtr + i )->MaxPINLen, 0x1c );
			if( ( strlen( FITBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
				break;
			strcat( FITBuffer, LineBuffer );
		}
		LineCount++;
	}

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= MaxFIT )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_GOODRESPMAP;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_BADRESPMAP;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700006;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, FITBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing FIT Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal FIT Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

int EzTMSController :: processTimerInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char TimerBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	trace( "Processing Timer Information Download for MachienId[%s]", tmsmsg->MachineId );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_timer.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/timer", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_timer.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/timer", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_timer.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/timer", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_timer.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/timer", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_timer.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/timer", terminalprofile_rec.TerminalType );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_timer.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/timer", "DEFAULT" );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int TimerCount = cfg_group_count( "TIMER_INFO" );
	if( TimerCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group TIMER_INFO in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( TimerBuffer, 0, sizeof( TimerBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < TimerCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "TIMER_INFO", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group STATE_INFO in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "TIMER_INFO", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			strcat( LineBuffer, cfgval );
		}
		strcat( LineBuffer, "\x1c" );
		if( ( strlen( TimerBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;

		strcat( TimerBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close( );

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= TimerCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_FITINFO;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_FITINFO;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700005;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, TimerBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Timer Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Timer Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

int EzTMSController :: processGoodRespMapDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char RespMapBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	trace( "Processing Good RespMap Download for MachienId[%s] TerminalType[%s]", tmsmsg->MachineId, terminalprofile_rec.TerminalType );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_goodresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_goodresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_goodresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_goodresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_goodresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_goodresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", "DEFAULT" );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int RespMapCount = cfg_group_count( "GOOD_RESPONSE" );
	if( RespMapCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group GOOD_RESPONSE in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( RespMapBuffer, 0, sizeof( RespMapBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < RespMapCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "GOOD_RESPONSE", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group GOOD_RESPONSE in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "GOOD_RESPONSE", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			strcat( LineBuffer, cfgval );
			strcat( LineBuffer, "\x1d" );
		}
		strcat( LineBuffer, "\x1c" );
		if( ( strlen( RespMapBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;
		strcat( RespMapBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close( );

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= RespMapCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_BADRESPMAP;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_TEMPLATE;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700007;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, RespMapBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Good RespMap Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Good RespMap Information Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}


int EzTMSController :: processBadRespMapDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char RespMapBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	trace( "Processing Bad RespMap Download for MachienId[%s] TerminalType[%s]", tmsmsg->MachineId, terminalprofile_rec.TerminalType );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_badresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_badresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_badresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_badresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_badresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", terminalprofile_rec.TerminalType );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_badresp.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/respmap", "DEFAULT" );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int RespMapCount = cfg_group_count( "BAD_RESPONSE" );
	if( RespMapCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group BAD_RESPONSE in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( RespMapBuffer, 0, sizeof( RespMapBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < RespMapCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "BAD_RESPONSE", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group BAD_RESPONSE in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "BAD_RESPONSE", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			strcat( LineBuffer, cfgval );
			strcat( LineBuffer, "\x1d" );
		}
		strcat( LineBuffer, "\x1c" );
		if( ( strlen( RespMapBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;
		strcat( RespMapBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close( );

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= RespMapCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_OPERATOR;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_COMPLETED;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700008;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, RespMapBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Bad RespMap Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Bad RespMap Information Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

int EzTMSController :: processStateInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char StateBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	//strcpy( terminalprofile_rec.TerminalType,terminalprofile_rec.TerminalName );
	trace( "Processing State Information Download for MachienId[%s] TerminalType[%s]", tmsmsg->MachineId, terminalprofile_rec.TerminalType );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/state", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/state", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/state", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/state", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/state", terminalprofile_rec.TerminalType );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/state", "DEFAULT" );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int StateCount = cfg_group_count( "STATE_INFO" );
	if( StateCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group STATE_INFO in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( StateBuffer, 0, sizeof( StateBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < StateCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "STATE_INFO", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group STATE_INFO in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "STATE_INFO", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			if ( !strcasecmp( cfgval, "$SPACE" ) )
				strcat( LineBuffer,  "\x20" );
			else
				strcat( LineBuffer, cfgval );
		}
		strcat( LineBuffer, "\x1c" );
		if( ( strlen( StateBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;

		strcat( StateBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close( );

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= StateCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_SCREENINFO;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_TXNMAPINFO;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700002;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, StateBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing State Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal State Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

int EzTMSController :: processScreenInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char ScreenBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	trace( "Processing Screen Information Download for MachienId[%s]", tmsmsg->MachineId );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/screen", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	trace( "Trying to Open FileName[%s]....", FileName );
	if( cfg_open( FileName ) < 0 )
	{
		trace("Terminal Type[%s]",terminalprofile_rec.TerminalType);
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/screen", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		trace( "Trying to Open FileName[%s]....", FileName );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/screen", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			trace( "Trying to Open FileName[%s]....", FileName );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/screen", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				trace( "Trying to Open FileName[%s]....", FileName );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/screen", terminalprofile_rec.TerminalType );
					trace( "Trying to Open FileName[%s]....", FileName );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/screen", "DEFAULT" );
						trace( "Trying to Open FileName[%s]....", FileName );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int ScreenCount = cfg_group_count( "SCREEN_INFO" );
	if( ScreenCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group SCREEN_INFO in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( ScreenBuffer, 0, sizeof( ScreenBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < ScreenCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "SCREEN_INFO", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group SCREEN_INFO in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "SCREEN_INFO", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			if ( !strcasecmp( cfgval, "$ESC" ) )
				strcat( LineBuffer,  "\x1b" );
			else if ( !strcasecmp( cfgval, "$SI" ) )
				strcat( LineBuffer,  "\x0f" );
			else if ( !strcasecmp( cfgval, "$BS" ) )
				strcat( LineBuffer,  "\x08" );
			else if ( !strcasecmp( cfgval,"$CR" ) )
				strcat( LineBuffer,  "\x0d" );
			else if ( !strcasecmp( cfgval, "$FF" ) )
				strcat( LineBuffer,  "\x0c" );
			else if ( !strcasecmp( cfgval, "$HT" ) )
				strcat( LineBuffer,  "\x09" );
			else if ( !strcasecmp( cfgval, "$LF" ) )
				strcat( LineBuffer,  "\x0a" );
			else if ( !strcasecmp( cfgval, "$SO" ) )
				strcat( LineBuffer,  "\x0e" );
			else if ( !strcasecmp( cfgval, "$VT" ) )
				strcat( LineBuffer,  "\x0b" );
			else if ( !strcasecmp( cfgval, "$SPACE" ) )
				strcat( LineBuffer,  "\x20" );
			else if ( !strcasecmp( cfgval, "$1C" ) )
				strcat( LineBuffer,  "\x1c" );
			else if ( !strcasecmp( cfgval, "$1D" ) )
				strcat( LineBuffer,  "\x1d" );
			else
				strcat( LineBuffer,  cfgval );
		}

		strcat( LineBuffer, "\x1c" );
		if( ( strlen( ScreenBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;

		strcat( ScreenBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close( );

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= ScreenCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_TXNMAPINFO;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_TIMERINFO;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700003;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, ScreenBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Screen Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Screen Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

int EzTMSController :: processTxnMapInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char TxnMapBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];

	trace( "Processing TxnMap Information Download for MachienId[%s]", tmsmsg->MachineId );

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_%s_%s_txnmap.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/txnmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId, terminalprofile_rec.TerminalId );
	trace( "Trying to Open FileName[%s]....", FileName );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_%s_txnmap.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/txnmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType, terminalprofile_rec.MerchantId );
		trace( "Trying to Open FileName[%s]....", FileName );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_%s_txnmap.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/txnmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId, terminalprofile_rec.MerchantType );
			trace( "Trying to Open FileName[%s]....", FileName );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_%s_txnmap.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/txnmap", terminalprofile_rec.TerminalType, terminalprofile_rec.InstId );
				trace( "Trying to Open FileName[%s]....", FileName );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_txnmap.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/txnmap", terminalprofile_rec.TerminalType );
					trace( "Trying to Open FileName[%s]....", FileName );
					if( cfg_open( FileName ) < 0 )
					{
						memset( FileName, 0, sizeof( FileName ) );
						sprintf( FileName, "%s/%s/%s_txnmap.cfg", getenv( "EZDIR_HOME"), "cfg/tms/statetable/txnmap", "DEFAULT" );
						trace( "Trying to Open FileName[%s]....", FileName );
						if( cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
							return -1;
						}
					}
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );

	int TxnMapCount = cfg_group_count( "TXNMAP" );
	if( TxnMapCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group TXNMAP in file[%s]", FileName );
		cfg_close();
		return -1;
	}

	int LineCount = 0;

	memset( TxnMapBuffer, 0, sizeof( TxnMapBuffer ) );

	for( int i = terminalprofile_rec.LineNo; i < TxnMapCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "TXNMAP", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group SCREEN_INFO in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "TXNMAP", cfgval );
		int FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in counting < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}
		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in Searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			strcat( LineBuffer,  cfgval );
			strcat( LineBuffer, "\x1d");
		}
		strcat( LineBuffer, "\x1c" );
		if( ( strlen( TxnMapBuffer ) + strlen( LineBuffer ) ) >= TMS_MAX_STATE_BUFFER_SIZE )
			break;

		strcat( TxnMapBuffer, LineBuffer );
		LineCount++;
	}
	cfg_close();

	terminalprofile_rec.LineNo += LineCount;

	if( terminalprofile_rec.LineNo >= TxnMapCount )
	{
		terminalprofile_rec.LineNo = 0;
		terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_TIMERINFO;
		terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_FITINFO;
	}

	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700004;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	strcpy( tmsmsg->RsvFld2, TxnMapBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing TxnMap Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal TxnMap Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

int EzTMSController :: processOperatorInfoDownload( struct EzTxnMsg *tmsmsg )
{
	char FileName[ TMS_STATE_FILE_NAME_SIZE + 1 ], LineBuffer[ TMS_STATE_LINE_BUFFER_SIZE + 1 ];
	char cfgval[ CFG_VAL_SIZE + 1 ], RecNo[ TMS_RECORD_NO_SIZE + 1 ];
	char RespMapBuffer[ TMS_STATE_BUFFER_SIZE + 1 ];
	int retval;
	trace( "Processing OperatorInfo Download for MachienId[%s] TerminalType[%s]", tmsmsg->MachineId, terminalprofile_rec.TerminalType );

	memset( RespMapBuffer, 0, sizeof( RespMapBuffer ) );
	retval = readOperatorInfo( terminalprofile_rec.InstId, tmsmsg->MachineId, terminalprofile_rec.TerminalId, RespMapBuffer );
	if( retval != 0 )
	{
		trace( "Error in Reading OperatorInfo Download Information and sqlcode[ %04d ] Machine[ %s ] Instid[ %s ] terminalid[ %s ]", retval, tmsmsg->MachineId, terminalprofile_rec.InstId, terminalprofile_rec.TerminalId );
	//	return -1;
	}

	trace( "OperatorInfo Information Instid[ %s ] terminalid[ %s ] Operator[ %s]", terminalprofile_rec.InstId, terminalprofile_rec.TerminalId, RespMapBuffer );
	terminalprofile_rec.LineNo = 0;
	terminalprofile_rec.CurrentCommand = TMS_DOWNLOAD_CMD_TEMPLATE;
	terminalprofile_rec.NextCommand = TMS_DOWNLOAD_CMD_COMPLETED;

	trace( "Test 1 !!!");
	updateTerminalProfile( terminalprofile_rec );

	tmsmsg->MsgType = 720;
	tmsmsg->TxnCode = 700010;
	memset( tmsmsg->RsvFld1, 0, sizeof( tmsmsg->RsvFld1 ) );
	strcpy( tmsmsg->RsvFld1, tmsmsg->MachineId );
	memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
	if( strlen( RespMapBuffer ) > 1 )
		strcpy( tmsmsg->RsvFld2, RespMapBuffer );

	if( WriteLastSenderChannel( ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Operator Information Download to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Terminal Operator Information Download to Channel[%s]", GetLastSenderChannelName() );

	return 1;
}

void EzTMSController :: getNewConfigId( char *ConfigId )
{
	char ddstr[ 10 ], mmstr[ 10 ], yystr[ 10 ], temp_date[ 10 ], ConfigIdNoPath[ TMS_CONFIGID_PATH_SIZE + 1 ];
	char datestr[ 10 ], timestr[ 10 ], hhstr[ 10 ];
	int i = 0, jday = 0, ConfigNo = 0;
	FILE *config_fptr;

	memset( temp_date, 0, sizeof( temp_date ) );
	sprintf( temp_date, "%06d", ezdatetimeutil.getSysDate() );

	memset( ddstr, 0, sizeof( ddstr ) );
	strncpy( ddstr, temp_date, 2 );

	memset( mmstr, 0, sizeof( mmstr ) );
	strncpy( mmstr, temp_date + 2, 2 );

	memset( yystr, 0, sizeof( yystr ) );
	strncpy( yystr, temp_date + 4, 2 );

	jday = 0;
	for( i = 0; i < atoi( mmstr ) - 1; i++ )
			jday += month_list[ i ];

	if( ( atoi( yystr ) % 4 == 0 ) && atoi( mmstr ) >= 3 )
			jday += 1;

	jday += atoi( ddstr );

	memset( datestr, 0, sizeof( datestr ) );
	sprintf( datestr, "%06d", ezdatetimeutil.getSysDate() );

	memset( timestr, 0, sizeof( timestr ) );
	sprintf( timestr, "%06d", ezdatetimeutil.getSysTime() );

	memset( hhstr, 0, sizeof( hhstr ) );
	strncpy( hhstr, timestr, 2 );

	memset( ConfigIdNoPath, 0, sizeof( ConfigIdNoPath ) );
	sprintf( ConfigIdNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "ConfigIdNo.dat" );

	config_fptr = fopen( ConfigIdNoPath, "r" );

	if( config_fptr == NULL )
		ConfigNo = 1;
	else
	{
		fscanf( config_fptr, "%d", &ConfigNo );
		if( ConfigNo == 999999 )
			ConfigNo = 1;
		else
			ConfigNo += 1;
		fclose( config_fptr );
	}

	config_fptr = fopen( ConfigIdNoPath, "w" );
	if( config_fptr == NULL )
		ConfigNo = 1;
	else
	{
		fprintf( config_fptr, "%d", ConfigNo );
		fclose( config_fptr );
	}
	sprintf( ConfigId, "%c%03d%s%06d", datestr[ 5 ], jday, hhstr, ConfigNo );
	trace( "datestr[ 5 ][%c] jday[%d] hhstr[%s] ConfigNo[%d] ConfigId[%s]", datestr[ 5 ], jday, hhstr, ConfigNo, ConfigId );

	trace(" machineid[%s]",terminalprofile_rec.MachineId);

	int retval = updateNewConfigId( terminalprofile_rec.MachineId,  ConfigId );
	if( retval != 0 )
	{
		if( SchemaType == SCHEMA_TYPE_SINGLE )
		{
			if( MMS_ORA_CONNECT_ERR( retval ) )
			{
				if( dbutil.DBConnect() < 0 )
					trace( "Error in Connecting with MMS Database..Error in Updating New ConfigId[%s] in EzMMSTerminalProfile..", ConfigId );
				else
					retval = updateNewConfigId( terminalprofile_rec.MachineId,  ConfigId );
			}
		}
		else
		{
			if( MMS_ORA_CONNECT_ERR( retval ) )
			{
				if( reConnectSchema() < 0 )
					trace( "Error in Connecting with MMS Database..Error in Updating New ConfigId[%s] in EzMMSTerminalProfile..", ConfigId );
				else
					retval = updateNewConfigId( terminalprofile_rec.MachineId,  ConfigId );
			}
		}
	}
	if( retval == 0 )
		trace( "Updated New ConfigId[%s] in EzMMSTerminalProfile...", ConfigId );
	else
		trace( "Error in Updating New ConfigId[%s] in EzMMSTerminalProfile...OraErr[%05d]", ConfigId, retval );
	trace( "Updated New ConfigId..." );
}



int main( int argc, char **argv )
{
	EzTMSController eztmscontrollerobj;
	eztmscontrollerobj.init( argv[ 0 ] );
	eztmscontrollerobj.serviceRequest();
	return 1;
}
