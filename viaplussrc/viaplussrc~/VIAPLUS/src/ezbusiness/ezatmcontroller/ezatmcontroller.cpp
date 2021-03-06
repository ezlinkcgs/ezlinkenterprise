#include <ezbusiness/ezatmcontroller.h>

int EzATMcontroller :: InitEzATMcontroller( const char * TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezatmcontroller.log" );

	if( openDebug( logpath, TaskName ) < 0 )
			exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
	   trace( DEBUG_ERROR,"Error in Initializing EzTaskUtil" );
	   trace( DEBUG_ERROR,"^^^^^^^^^^^EzATMcontroller Ended Abnormally^^^^^^^^^^^^^" );
	   closeDebug( );
	   exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzChannelUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzATMcontroller Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( CONTROLLERCHANNEL, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating EzATMcontroller Channel" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzATMcontroller Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit();
	}

	if( InitEzATMUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing the ATM Util" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzATMcontroller Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit();
	}

	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing the EzSecurityUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzATMcontroller Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}
	TaskInit();
	initEzSigUtil( this );
}

void EzATMcontroller :: displayATMMemory( const char *AtmId, struct AtmTableInfo atminfo, struct ATMSharedBuffer atmbuf, int accesstype )
{

	if( accesstype == 1 )
		trace( "Read ATM[%s] details with following values...", AtmId );
	else
		trace( "Writing ATM[%s] details with following values...", AtmId );

	trace( "AtmTypeId[%s]", atminfo.AtmTypeId );
	trace( "AtmLogicalGroup[%s]", atminfo.AtmLogicalGroup );
	trace( "AcquirerInst[%s]", atminfo.AcquirerInst );
	trace( "AtmConfigId[%d]", atminfo.AtmConfigId );

	switch ( atmbuf.CurrentDownload )
	{
		case DOWNLOAD_ALL:
			trace( "Current Download [%s]", "DOWNLOAD ALL" );
		break;

		case DOWNLOAD_STATE:
			trace( "Current Download [%s]", "DOWNLOAD STATE" );
		break;

		case DOWNLOAD_SCREEN:
			trace( "Current Download [%s]", "DOWNLOAD SCREEN" );
		break;

		case DOWNLOAD_MISC:
			trace( "Current Download [%s]", "DOWNLOAD MISC" );
		break;

		case DOWNLOAD_MISC_E:
			trace( "Current Download [%s]", "DOWNLOAD MISC_E" );
		break;

		case DOWNLOAD_FIT:
			trace( "Current Download [%s]", "DOWNLOAD FIT" );
		break;

		case DOWNLOAD_KEY:
			trace( "Current Download [%s]", "DOWNLOAD KEY" );
		break;

		case DOWNLOAD_CONFIG_ID:
			trace( "Current Download [%s]", "DOWNLOAD CONFIGID" );
		break;

		case DOWNLOAD_DATE_TIME:
			trace( "Current Download [%s]", "DOWNLOAD DATE&TIME" );
		break;

		case DOWNLOAD_CUSTOM_ICON:
			trace( "Current Download [%s]", "DOWNLOAD CUSTOM-ICON" );
		break;

		case DOWNLOAD_CUSTOM_CHAR:
			trace( "Current Download [%s]", "DOWNLOAD CUSTOM-CHAR" );
		break;

		case DOWNLOAD_CELLDATA:
			trace( "Current Download [%s]", "DOWNLOAD CELL-DATA" );
		break;

		case DOWNLOAD_TEMPLATE:
			trace( "Current Download [%s]", "DOWNLOAD TEMPLATE" );
		break;

		case DOWNLOAD_RESERVED_SCREEN:
			trace( "Current Download [%s]", "DOWNLOAD RESERVED SCREEN" );
		break;

		case DOWNLOAD_SINGLE:
			trace( "Current Download [%s]", "DOWNLOAD SINGLE" );
		break;

		case GO_IN_SERVICE:
			trace( "Current Download [%s]", "GO_IN_SERVICE" );
		break;

		case GO_OUT_SERVICE:
			trace( "Current Download [%s]", "GO_OUT_SERVICE" );
		break;

		case GET_CONFIG_INFO:
			trace( "Current Download [%s]", "GET_CONFIG_INFO" );
		break;

		case CLOSE_VANDAL_SHIELD:
			trace( "Current Download [%s]", "CLOSE_VANDAL_SHIELD" );
		break;

		case OPEN_VANDAL_SHIELD:
			trace( "Current Download [%s]", "OPEN_VANDAL_SHIELD" );
		break;

		case UNLOCK_SAFE_DOOR:
			trace( "Current Download [%s]", "UNLOCK_SAFE_DOOR" );
		break;

		case LOCK_SAFE_DOOR:
			trace( "Current Download [%s]", "LOCK_SAFE_DOOR" );
		break;

		case EMG_COMMAND:
			trace( "Current Download [%s]", "EMG_COMMAND" );
		break;

		case GET_SUPPLY_COUNTS:
			trace( "Current Download [%s]", "GET_SUPPLY_COUNTS" );
		break;

		case CLEAR_SUPPLY_COUNTS:
			trace( "Current Download [%s]", "CLEAR_SUPPLY_COUNTS" );
		break;

		case GET_ESUPPLY_COUNTS:
			trace( "Current Download [%s]", "GET_ESUPPLY_COUNTS" );
		break;

		case CLEAR_ESUPPLY_COUNTS:
			trace( "Current Download [%s]", "CLEAR_ESUPPLY_COUNTS" );
		break;

		case RUN_SELF_TEST:
			trace( "Current Download [%s]", "RUN_SELF_TEST" );
		break;

		case SHUTDOWN:
			trace( "Current Download [%s]", "SHUTDOWN" );
		break;

		case GET_TALLY_INFO:
			trace( "Current Download [%s]", "GET_TALLY_INFO" );
		break;

		case GET_ERRORLOG:
			trace( "Current Download [%s]", "GET_ERRORLOG" );
		break;

		case GET_HW_CONF:
			trace( "Current Download [%s]", "GET_HW_CONF" );
		break;

		case GET_DATE_TIME:
			trace( "Current Download [%s]", "GET_DATE_TIME" );
		break;

		case GET_EKC:
			trace( "Current Download [%s]", "GET_EKC" );
		break;

		default:
			trace( "Invalid Current Download Read..." );
		break;
	}

	switch ( atmbuf.CurrentCommand )
	{

		case DOWNLOAD_ALL:
			trace( "Current Command [%s]", "DOWNLOAD ALL" );
		break;

		case DOWNLOAD_STATE:
			trace( "Current Command [%s]", "DOWNLOAD STATE" );
		break;

		case DOWNLOAD_SCREEN:
			trace( "Current Command [%s]", "DOWNLOAD SCREEN" );
		break;

		case DOWNLOAD_MISC:
			trace( "Current Command [%s]", "DOWNLOAD MISC" );
		break;

		case DOWNLOAD_MISC_E:
			trace( "Current Command [%s]", "DOWNLOAD MISC_E" );
		break;

		case DOWNLOAD_FIT:
			trace( "Current Command [%s]", "DOWNLOAD FIT" );
		break;

		case DOWNLOAD_KEY:
			trace( "Current Command [%s]", "DOWNLOAD KEY" );
		break;

		case DOWNLOAD_CONFIG_ID:
			trace( "Current Command [%s]", "DOWNLOAD CONFIGID" );
		break;

		case DOWNLOAD_DATE_TIME:
			trace( "Current Command [%s]", "DOWNLOAD DATE&TIME" );
		break;

		case DOWNLOAD_CUSTOM_ICON:
			trace( "Current Command [%s]", "DOWNLOAD CUSTOM-ICON" );
		break;

		case DOWNLOAD_CUSTOM_CHAR:
			trace( "Current Command [%s]", "DOWNLOAD CUSTOM-CHAR" );
		break;

		case DOWNLOAD_CELLDATA:
			trace( "Current Command [%s]", "DOWNLOAD CELL-DATA" );
		break;

		case DOWNLOAD_TEMPLATE:
			trace( "Current Command [%s]", "DOWNLOAD TEMPLATE" );
		break;

		case DOWNLOAD_RESERVED_SCREEN:
			trace( "Current Command [%s]", "DOWNLOAD RESERVED SCREEN" );
		break;

		case DOWNLOAD_SINGLE:
			trace( "Current Command [%s]", "DOWNLOAD SINGLE" );
		break;

		case GO_IN_SERVICE:
			trace( "Current Command [%s]", "GO_IN_SERVICE" );
		break;

		case GO_OUT_SERVICE:
			trace( "Current Command [%s]", "GO_OUT_SERVICE" );
		break;

		case GET_CONFIG_INFO:
			trace( "Current Command [%s]", "GET_CONFIG_INFO" );
		break;

		case CLOSE_VANDAL_SHIELD:
			trace( "Current Command [%s]", "CLOSE_VANDAL_SHIELD" );
		break;

		case OPEN_VANDAL_SHIELD:
			trace( "Current Command [%s]", "OPEN_VANDAL_SHIELD" );
		break;

		case UNLOCK_SAFE_DOOR:
			trace( "Current Command [%s]", "UNLOCK_SAFE_DOOR" );
		break;

		case LOCK_SAFE_DOOR:
			trace( "Current Command [%s]", "LOCK_SAFE_DOOR" );
		break;

		case EMG_COMMAND:
			trace( "Current Command [%s]", "EMG_COMMAND" );
		break;

		case GET_SUPPLY_COUNTS:
			trace( "Current Command [%s]", "GET_SUPPLY_COUNTS" );
		break;

		case CLEAR_SUPPLY_COUNTS:
			trace( "Current Command [%s]", "CLEAR_SUPPLY_COUNTS" );
		break;

		case GET_ESUPPLY_COUNTS:
			trace( "Current Command [%s]", "GET_ESUPPLY_COUNTS" );
		break;

		case CLEAR_ESUPPLY_COUNTS:
			trace( "Current Command [%s]", "CLEAR_ESUPPLY_COUNTS" );
		break;

		case RUN_SELF_TEST:
			trace( "Current Command [%s]", "RUN_SELF_TEST" );
		break;

		case SHUTDOWN:
			trace( "Current Command [%s]", "SHUTDOWN" );
		break;

		case GET_TALLY_INFO:
			trace( "Current Command [%s]", "GET_TALLY_INFO" );
		break;

		case GET_ERRORLOG:
			trace( "Current Command [%s]", "GET_ERRORLOG" );
		break;

		case GET_HW_CONF:
			trace( "Current Command [%s]", "GET_HW_CONF" );
		break;

		case GET_DATE_TIME:
			trace( "Current Command [%s]", "GET_DATE_TIME" );
		break;

		case GET_EKC:
			trace( "Current Command [%s]", "GET_EKC" );
		break;

		default:
			trace( "Invalid Current Command...." );
		break;

	}

	switch ( atmbuf.NextCommand )
	{
		case DOWNLOAD_ALL:
			trace( "Next Command [%s]", "DOWNLOAD ALL" );
		break;

		case DOWNLOAD_STATE:
			trace( "Next Command [%s]", "DOWNLOAD STATE" );
		break;

		case DOWNLOAD_SCREEN:
			trace( "Next Command [%s]", "DOWNLOAD SCREEN" );
		break;

		case DOWNLOAD_MISC:
			trace( "Next Command [%s]", "DOWNLOAD MISC" );
		break;

		case DOWNLOAD_MISC_E:
			trace( "Next Command [%s]", "DOWNLOAD MISC_E" );
		break;

		case DOWNLOAD_FIT:
			trace( "Next Command [%s]", "DOWNLOAD FIT" );
		break;

		case DOWNLOAD_KEY:
			trace( "Next Command [%s]", "DOWNLOAD KEY" );
		break;

		case DOWNLOAD_CONFIG_ID:
			trace( "Next Command [%s]", "DOWNLOAD CONFIGID" );
		break;

		case DOWNLOAD_DATE_TIME:
			trace( "Next Command [%s]", "DOWNLOAD DATE&TIME" );
		break;

		case DOWNLOAD_CUSTOM_ICON:
			trace( "Next Command [%s]", "DOWNLOAD CUSTOM-ICON" );
		break;

		case DOWNLOAD_CUSTOM_CHAR:
			trace( "Next Command [%s]", "DOWNLOAD CUSTOM-CHAR" );
		break;

		case DOWNLOAD_CELLDATA:
			trace( "Next Command [%s]", "DOWNLOAD CELL-DATA" );
		break;

		case DOWNLOAD_TEMPLATE:
			trace( "Next Command [%s]", "DOWNLOAD TEMPLATE" );
		break;

		case DOWNLOAD_RESERVED_SCREEN:
			trace( "Next Command [%s]", "DOWNLOAD RESERVED SCREEN" );
		break;

		case DOWNLOAD_SINGLE:
			trace( "Next Command [%s]", "DOWNLOAD SINGLE" );
		break;

		case GO_IN_SERVICE:
			trace( "Next Command [%s]", "GO_IN_SERVICE" );
		break;

		case GO_OUT_SERVICE:
			trace( "Next Command [%s]", "GO_OUT_SERVICE" );
		break;

		case GET_CONFIG_INFO:
			trace( "Next Command [%s]", "GET_CONFIG_INFO" );
		break;

		case CLOSE_VANDAL_SHIELD:
			trace( "Next Command [%s]", "CLOSE_VANDAL_SHIELD" );
		break;

		case OPEN_VANDAL_SHIELD:
			trace( "Next Command [%s]", "OPEN_VANDAL_SHIELD" );
		break;

		case UNLOCK_SAFE_DOOR:
			trace( "Next Command [%s]", "UNLOCK_SAFE_DOOR" );
		break;

		case LOCK_SAFE_DOOR:
			trace( "Next Command [%s]", "LOCK_SAFE_DOOR" );
		break;

		case EMG_COMMAND:
			trace( "Next Command [%s]", "EMG_COMMAND" );
		break;

		case GET_SUPPLY_COUNTS:
			trace( "Next Command [%s]", "GET_SUPPLY_COUNTS" );
		break;

		case CLEAR_SUPPLY_COUNTS:
			trace( "Next Command [%s]", "CLEAR_SUPPLY_COUNTS" );
		break;

		case GET_ESUPPLY_COUNTS:
			trace( "Next Command [%s]", "GET_ESUPPLY_COUNTS" );
		break;

		case CLEAR_ESUPPLY_COUNTS:
			trace( "Next Command [%s]", "CLEAR_ESUPPLY_COUNTS" );
		break;

		case RUN_SELF_TEST:
			trace( "Next Command [%s]", "RUN_SELF_TEST" );
		break;

		case SHUTDOWN:
			trace( "Next Command [%s]", "SHUTDOWN" );
		break;

		case GET_TALLY_INFO:
			trace( "Next Command [%s]", "GET_TALLY_INFO" );
		break;

		case GET_ERRORLOG:
			trace( "Next Command [%s]", "GET_ERRORLOG" );
		break;

		case GET_HW_CONF:
			trace( "Next Command [%s]", "GET_HW_CONF" );
		break;

		case GET_DATE_TIME:
			trace( "Next Command [%s]", "GET_DATE_TIME" );
		break;

		case GET_EKC:
			trace( "Next Command [%s]", "GET_EKC" );
		break;

		default:
			trace( "Invalid Next Command...." );
		break;

	}

	switch ( atmbuf.DownloadFlag )
	{
		case ENABLE:
			trace( "Download Flag[%s]", "ENABLE" );
		break;

		case DISABLE:
			trace( "Download Flag[%s]", "DISABLE" );
		break;

		default:
			trace( "Invalid DownloadFlag...." );
		break;
	}

	trace( "TotalLength[%d]", atmbuf.TotalLength );
	trace( "OffsetLength[%d]", atmbuf.OffsetLength );
}


void EzATMcontroller :: ServiceRequest()
{
	int ret, BufSize;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct EzAtmController ContReq;

	while( 1 )
	{
		trace( DEBUG_NORMAL,"Waiting for Message in EzATMController Channel" );
		memset( &ContReq, 0, sizeof( struct EzAtmController ) );
		if( ReadMessage( ( char * )&ContReq, &BufSize ) < 1 )
		{
			trace( DEBUG_ERROR,"Error in Reading EzATMController Channel" );
			continue;
		}
		memset( ChannelName, 0, sizeof( ChannelName ) );
		strcpy( ChannelName, GetLastSenderChannelName() );

		trace( DEBUG_NORMAL, "Message received from [%s]", ChannelName );

		memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
		trace( DEBUG_NORMAL,"Reading Device Memory[ %s ] for the first time", ContReq.AtmId );
		if( ReadAtmMemory( ContReq.AtmId, &atmmem ) < 0 )
		{
			trace( DEBUG_ERROR,"Unable to Read AtmMemoryTable AtmId[ %s ]",  ContReq.AtmId );
			continue;
		}

		memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
		memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );

		memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );
		memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

		displayATMMemory( ContReq.AtmId, atminfo, atmbuf, 1 );

		switch ( ContReq.MsgType )
		{
			case EZ_ATM_DOWNLOAD_REQ:
				trace( DEBUG_NORMAL, "Received MsgType[%s]", "Download Request" );
			break;

			case EZ_ATM_DOWNLOAD_RESP:
				trace( DEBUG_NORMAL, "Received MsgType[%s]", "Download Response" );
			break;

			case EZ_ATM_COMMAND_REQ:
				trace( DEBUG_NORMAL, "Received MsgType[%s]", "Command Request" );
			break;

			case EZ_ATM_COMMAND_RESP:
				trace( DEBUG_NORMAL, "Received MsgType[%s]", "Command Response" );
			break;

			default:
				trace( DEBUG_NORMAL, "Received MsgType[%s]", "Invalid MsgType" );
			break;
		}

		switch ( ContReq.DownloadType )
		{
			case DOWNLOAD_ALL:
				trace( "Received DownloadType[%s]", "DOWNLOAD ALL" );
			break;

			case DOWNLOAD_STATE:
				trace( "Received DownloadType[%s]", "DOWNLOAD STATE" );
			break;

			case DOWNLOAD_SCREEN:
				trace( "Received DownloadType[%s]", "DOWNLOAD SCREEN" );
			break;

			case DOWNLOAD_MISC:
				trace( "Received DownloadType[%s]", "DOWNLOAD MISC" );
			break;

			case DOWNLOAD_MISC_E:
				trace( "Received DownloadType[%s]", "DOWNLOAD MISC_E" );
			break;

			case DOWNLOAD_FIT:
				trace( "Received DownloadType[%s]", "DOWNLOAD FIT" );
			break;

			case DOWNLOAD_KEY:
				trace( "Received DownloadType[%s]", "DOWNLOAD KEY" );
			break;

			case DOWNLOAD_CONFIG_ID:
				trace( "Received DownloadType[%s]", "DOWNLOAD CONFIGID" );
			break;

			case DOWNLOAD_DATE_TIME:
				trace( "Received DownloadType[%s]", "DOWNLOAD DATE&TIME" );
			break;

			case DOWNLOAD_CUSTOM_ICON:
				trace( "Received DownloadType[%s]", "DOWNLOAD CUSTOM-ICON" );
			break;

			case DOWNLOAD_CUSTOM_CHAR:
				trace( "Received DownloadType[%s]", "DOWNLOAD CUSTOM-CHAR" );
			break;

			case DOWNLOAD_CELLDATA:
				trace( "Received DownloadType[%s]", "DOWNLOAD CELL-DATA" );
			break;

			case DOWNLOAD_TEMPLATE:
				trace( "Received DownloadType[%s]", "DOWNLOAD TEMPLATE" );
			break;

			case DOWNLOAD_RESERVED_SCREEN:
				trace( "Received DownloadType[%s]", "DOWNLOAD RESERVED SCREEN" );
			break;

			case DOWNLOAD_SINGLE:
				trace( "Received DownloadType[%s]", "DOWNLOAD SINGLE" );
				break;

			default:
				trace( "Received DownloadType[%s]", "INVALID DOWNLOAD TYPE" );
		}

		switch ( ContReq.CommandType )
		{
			case GO_IN_SERVICE:
				trace( "Received CommandType[%s]", "GO_IN_SERVICE" );
			break;

			case GO_OUT_SERVICE:
				trace( "Received CommandType[%s]", "GO_OUT_SERVICE" );
			break;

			case GET_CONFIG_INFO:
				trace( "Received CommandType[%s]", "GET_CONFIG_INFO" );
			break;

			case CLOSE_VANDAL_SHIELD:
				trace( "Received CommandType[%s]", "CLOSE_VANDAL_SHIELD" );
			break;

			case OPEN_VANDAL_SHIELD:
				trace( "Received CommandType[%s]", "OPEN_VANDAL_SHIELD" );
			break;

			case UNLOCK_SAFE_DOOR:
				trace( "Received CommandType[%s]", "UNLOCK_SAFE_DOOR" );
			break;

			case LOCK_SAFE_DOOR:
				trace( "Received CommandType[%s]", "LOCK_SAFE_DOOR" );
			break;

			case EMG_COMMAND:
				trace( "Received CommandType[%s]", "EMG_COMMAND" );
			break;

			case GET_SUPPLY_COUNTS:
				trace( "Received CommandType[%s]", "GET_SUPPLY_COUNTS" );
			break;

			case CLEAR_SUPPLY_COUNTS:
				trace( "Received CommandType[%s]", "CLEAR_SUPPLY_COUNTS" );
			break;

			case GET_ESUPPLY_COUNTS:
				trace( "Received CommandType[%s]", "GET_ESUPPLY_COUNTS" );
			break;

			case CLEAR_ESUPPLY_COUNTS:
				trace( "Received CommandType[%s]", "CLEAR_ESUPPLY_COUNTS" );
			break;

			case RUN_SELF_TEST:
				trace( "Received CommandType[%s]", "RUN_SELF_TEST" );
			break;

			case SHUTDOWN:
				trace( "Received CommandType[%s]", "SHUTDOWN" );
			break;

			case GET_TALLY_INFO:
				trace( "Received CommandType[%s]", "GET_TALLY_INFO" );
			break;

			case GET_ERRORLOG:
				trace( "Received CommandType[%s]", "GET_ERRORLOG" );
			break;

			case GET_HW_CONF:
				trace( "Received CommandType[%s]", "GET_HW_CONF" );
			break;

			case GET_DATE_TIME:
				trace( "Received CommandType[%s]", "GET_DATE_TIME" );
			break;

			case GET_EKC:
				trace( "Received CommandType[%s]", "GET_EKC" );
			break;

			default:
				trace( "Received CommandType[%s]", "INVALID COMMAND TYPE" );
			break;

		}

		switch ( ContReq.RespType )
		{
			case EZ_ATM_GOOD_RESP:
				trace( "Received RespType[%s]", "Good Response" );
			break;

			case EZ_ATM_BAD_RESP:
				trace( "Received RespType[%s]", "Bad Response" );
			break;

			default:
				trace( "Received RespType[%s]", "Invalid Response" );
			break;
		}

		if( !strcmp( ChannelName, D912DRIVERCHANNEL ) || !strcmp( ChannelName, NDCDRIVERCHANNEL ) )
		{
			trace( DEBUG_NORMAL, "Received Request from ATM Driver for AtmId[%s]", ContReq.AtmId );


			trace( DEBUG_TEST,"Received : AtmId< %s > MsgType< %d > DownloadType< %d > CommandType< %d > RespType< %d >", ContReq.AtmId, ContReq.MsgType, ContReq.DownloadType, ContReq.CommandType, ContReq.RespType );
			if( DiagnizeAndServeDriverReq( &ContReq ) < 0 )
				trace( DEBUG_ERROR,"Failed in DiagnizeAndServeDriverReq " );
		}
		else if( !strcmp( ChannelName, "ezatmcmd" ) || !strcmp( ChannelName, GUICHANNEL ) )
		{
			trace( DEBUG_NORMAL, "Received Request from Command Prompt/GUI Channel for AtmId[%s]", ContReq.AtmId );
			trace( DEBUG_TEST,"Received : AtmId< %s > MsgType< %d > DownloadType< %d > CommandType< %d > RespType< %d >", ContReq.AtmId, ContReq.MsgType, ContReq.DownloadType, ContReq.CommandType, ContReq.RespType );
			if( DiagnizeAndServeCmd_GuiReq( &ContReq ) < 0 )
				trace( DEBUG_ERROR,"Failed in DiagnizeAndServeCmd_GuiReq " );
		}
	}
}

int EzATMcontroller :: DiagnizeAndServeDriverReq( struct EzAtmController *DriverReq )
{
	if( DriverReq->MsgType == EZ_ATM_DOWNLOAD_REQ || DriverReq->MsgType == EZ_ATM_DOWNLOAD_RESP )
	{
		if( StartDownloader( DriverReq ) < 0 )
		{
			trace( DEBUG_ERROR,"Failed in StartDownloader AtmId[%s]", DriverReq->AtmId );
			return -1;
		}
	}
	else if( DriverReq->MsgType == EZ_ATM_COMMAND_RESP )
	{
		if( DriverReq->RespType == EZ_ATM_BAD_RESP )
		{
			if( DriverReq->CommandType == GO_IN_SERVICE )
			{
				memset( StatusCode, 0, sizeof( StatusCode ) );
				strcpy( StatusCode, "!OUT" );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!OUT", atmbuf.StaticStatus );
				memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
				if( PackAtmStatusMsg( DriverReq->AtmId, StatusCode, atmbuf.StaticStatus, &atmmgrq ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to update Status in Table for Device[%s] ", DriverReq->AtmId );
					return -1;
				}
				else
				{
					trace( DEBUG_ERROR,"Updated Status in Table for Device[%s] ", DriverReq->AtmId );
					if( PostAtmMgrMsg( &atmmgrq ) < 0 )
						trace( DEBUG_ERROR,"Failed in PostAtmMgrMsg");
				}
			}
			else if( DriverReq->CommandType == GO_OUT_SERVICE || DriverReq->CommandType == SHUTDOWN )
				trace( DEBUG_ERROR,"Unable To Put ATM Out Of Service" );
		}
		else if ( DriverReq->RespType == EZ_ATM_GOOD_RESP )
		{
			if( DriverReq->CommandType == GO_IN_SERVICE )
			{
				memset( StatusCode, 0, sizeof( StatusCode ) );
				strcpy( StatusCode, "!IN" );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!IN", atmbuf.StaticStatus );
				memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
				if( PackAtmStatusMsg( DriverReq->AtmId, StatusCode, atmbuf.StaticStatus, &atmmgrq ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to update Status in Table for Device<%s> ", DriverReq->AtmId );
					return -1;
				}
				else
				{
					trace( DEBUG_ERROR,"Updated Status in Table for Device<%s> ", DriverReq->AtmId );
					if( PostAtmMgrMsg( &atmmgrq ) < 0 )
						trace( DEBUG_ERROR,"Failed in PostAtmMgrMsg");
				}
			}
			else if( DriverReq->CommandType == GO_OUT_SERVICE || DriverReq->CommandType == SHUTDOWN )
			{
				memset( StatusCode, 0, sizeof( StatusCode ) );
				strcpy( StatusCode, "!OUT" );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!OUT", atmbuf.StaticStatus );
				memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
				if( PackAtmStatusMsg( DriverReq->AtmId, StatusCode, atmbuf.StaticStatus, &atmmgrq ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to update Status in Table for Device<%s> ", DriverReq->AtmId );
					return -1;
				}
				else
				{
					trace( DEBUG_ERROR,"Updated Status in Table for Device<%s> ", DriverReq->AtmId );
					if( PostAtmMgrMsg( &atmmgrq ) < 0 )
						trace( DEBUG_ERROR,"Failed in PostAtmMgrMsg");
				}

				if( atmbuf.CurrentDownload == DOWNLOAD_ALL || atmbuf.CurrentDownload == DOWNLOAD_SINGLE )
				{
					DriverReq->MsgType = EZ_ATM_DOWNLOAD_REQ;
					trace( DEBUG_TEST,"calling back StartDownloader......");
					if( StartDownloader( DriverReq ) < 0 )
					{
						trace( DEBUG_ERROR,"Failed in StartDownloader AtmId[%s]", DriverReq->AtmId );
						return -1;
					}
				}
				if( atmbuf.NextCommand == GET_SUPPLY_COUNTS )
				{
					DriverReq->MsgType = EZ_ATM_COMMAND_REQ;
					trace( DEBUG_TEST, "Calling back GetSupplyCounter.........");
					if( GetSupplyCounter( DriverReq ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in GetSupplyCounter AtmId [%s]", DriverReq->AtmId );
						return -1;
					}
				}
			}
			else if( DriverReq->CommandType == GET_SUPPLY_COUNTS )
			{
				DriverReq->MsgType = EZ_ATM_COMMAND_REQ;
				DriverReq->CommandType = GO_IN_SERVICE;
				atmbuf.NextCommand = GO_IN_SERVICE;
				if( GetSupplyCounter( DriverReq ) < 0 )	
				{
					trace( DEBUG_ERROR, "Failed in GetSupplyCounter AtmId [%s]", DriverReq->AtmId );
					return -1;
				}
			}
			else
			{
				trace( DEBUG_ERROR,"Command Type< %d > ", DriverReq->CommandType );
				 if( atmbuf.DownloadFlag == DISABLE )
                                {
					atmbuf.CurrentDownload = 0;
		                        atmbuf.CurrentCommand = 0;
		                        atmbuf.NextCommand = 0;
		                        atmbuf.TotalLength = 0;
		                        atmbuf.OffsetLength = 0;
		                        memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		                        memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

		                        displayATMMemory( DriverReq->AtmId, atminfo, atmbuf, 2 );
                		        if( WriteAtmMemory( DriverReq->AtmId, &atmmem ) < 0 )
		                        {
                		                trace( DEBUG_ERROR,"Unable to Update Device memory for Device<%s>", DriverReq->AtmId );
                                		return -1;
		                        }
                		        else
                                		trace( DEBUG_ERROR,"Cleared the Device memory for Device<%s>", DriverReq->AtmId );
				}
			}
		}
	}
	else if( DriverReq->MsgType == EZ_ATM_COMMAND_REQ )
	{
		atmbuf.CurrentCommand = DriverReq->CommandType;
		if( PostDriverMsg( DriverReq ) < 0 )
		{
			trace( DEBUG_ERROR,"Unable to post the Msg to Driver AtmId[ %s]", DriverReq->AtmId );
			return -1;
		}
	}
	return 1;
}

int EzATMcontroller :: DiagnizeAndServeCmd_GuiReq( struct EzAtmController *AppReq )
{
	trace( DEBUG_TEST,"Message Received : <%s><%s><%d><%d><%d>", AppReq->AtmId, AppReq->MsgBuf, AppReq->MsgType, AppReq->DownloadType ,AppReq->CommandType);
	if( AppReq->MsgType == EZ_ATM_COMMAND_REQ )
	{
		if ( AppReq->CommandType == GET_SUPPLY_COUNTS )
		{
			if ( GetSupplyCounter( AppReq ) < 0 )
			{
				trace( DEBUG_ERROR, "Unable to Getsupplycounter AtmId[ %s ]", AppReq->AtmId );
				return -1;
			}
		}
		else
		{
			atmbuf.CurrentCommand = AppReq->CommandType;
			if( PostDriverMsg( AppReq ) < 0 )
			{
				trace( DEBUG_ERROR,"Unable to post the Msg to Driver AtmId[ %s]", AppReq->AtmId );
				return -1;
			}
		}
	}
	else if( AppReq->MsgType == EZ_ATM_DOWNLOAD_REQ )
	{
		if( StartDownloader( AppReq ) < 0 )
		{
			trace( DEBUG_ERROR,"Failed in StartDownloader AtmId[ %s]", AppReq->AtmId );
			return -1;
		}
	}
	return 1;
}

int EzATMcontroller :: PostDriverMsg( struct EzAtmController *AppReq )
{
	trace( DEBUG_TEST,"Sent : AtmId< %s > MsgType< %d > DownloadType< %d > CommandType< %d > RespType< %d > MsgBuf< %s >", AppReq->AtmId, AppReq->MsgType, AppReq->DownloadType, AppReq->CommandType, AppReq->RespType, AppReq->MsgBuf );

	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

	displayATMMemory( AppReq->AtmId, atminfo, atmbuf, 2 );

	if( WriteAtmMemory( AppReq->AtmId, &atmmem ) < 0 )
	{
		trace( DEBUG_ERROR,"Unable to Update Device memory for Device<%s>", AppReq->AtmId );
		return -1;
	}
	else
		trace( DEBUG_ERROR,"Updated the Device memory for Device<%s>", AppReq->AtmId );
	trace( DEBUG_NORMAL, "Model< %s >", atminfo.AtmTypeId );
	if( !strcmp( atminfo.AtmTypeId, DIEBOLD ) )
	{
		if( WriteChannel( D912DRIVERCHANNEL, (char*)AppReq, sizeof( struct EzAtmController ) ) < 0 )
		{
			trace( DEBUG_ERROR,"Failed to write msg into %s Channel", D912DRIVERCHANNEL );
			return -1;
		}
		else
			trace( DEBUG_ERROR,"Msg Written into %s Channel", D912DRIVERCHANNEL );
	}
	else if( !strcmp( atminfo.AtmTypeId, NDC ) )
	{
		if( WriteChannel( NDCDRIVERCHANNEL, (char*)AppReq, sizeof( struct EzAtmController ) ) < 0 )
		{
			trace( DEBUG_ERROR,"Failed to write msg into %s Channel", NDCDRIVERCHANNEL );
			return -1;
		}
		else
			trace( DEBUG_ERROR,"Msg Written into %s Channel", NDCDRIVERCHANNEL );
	}
	else
		trace( DEBUG_ERROR,"Invalid AtmTypeId %s ", atminfo.AtmTypeId );
	return 1;
}

int EzATMcontroller :: PostAtmMgrMsg( struct EzAtmMgrQMsg *atmmgrq )
{
	trace( DEBUG_NORMAL,"Routing to %s channel", ATMMGRCHANNEL );
	if( WriteChannel( ATMMGRCHANNEL, ( char* )atmmgrq, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR,"Error while writing EzDeviceMgr channel <%s> <%d>", strerror( errno ), errno );
		return -1;
	}
	else
		trace( DEBUG_TEST,"Posted to %s Channel", ATMMGRCHANNEL );
	return 1;
}

int EzATMcontroller :: StartDownloader( struct EzAtmController *AppReq )
{
	trace( DEBUG_NORMAL,"Received Download request <%s>", AppReq->AtmId );

	if( AppReq->MsgType == EZ_ATM_DOWNLOAD_RESP )
	{
		if( AppReq->RespType == EZ_ATM_BAD_RESP )
		{
			memset( StatusCode, 0, sizeof( StatusCode ) );
			strcpy( StatusCode, "!OUT" );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!OUT", atmbuf.StaticStatus );
			memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
			if( PackAtmStatusMsg( AppReq->AtmId, StatusCode, atmbuf.StaticStatus, &atmmgrq ) < 0 )
			{
				trace( DEBUG_ERROR,"Unable to update Status in Table for Device<%s> ", AppReq->AtmId );
				return -1;
			}
			else
			{
				trace( DEBUG_ERROR,"Updated Status in Table for Device<%s> ", AppReq->AtmId );
				if( PostAtmMgrMsg( &atmmgrq ) < 0 )
					trace( DEBUG_ERROR,"Failed in PostAtmMgrMsg");
				return 1;
			}
		}
		else
		{
			if( atmbuf.CurrentDownload == DOWNLOAD_ALL  || atmbuf.TotalLength != atmbuf.OffsetLength )
				AppReq->MsgType = EZ_ATM_DOWNLOAD_REQ;
		}
	}

	trace( DEBUG_NORMAL,"DownloadType< %d >, CurrentDownload< %d > MsgType< %d >", AppReq->DownloadType, atmbuf.CurrentDownload, AppReq->MsgType );
	trace( DEBUG_NORMAL, "<%d>", DOWNLOAD_ALL );
	atmbuf.DownloadFlag = ENABLE;
	if( ( AppReq->DownloadType == DOWNLOAD_ALL || atmbuf.CurrentDownload == DOWNLOAD_ALL ) && AppReq->MsgType == EZ_ATM_DOWNLOAD_REQ )
	{
		if( AppReq->DownloadType == DOWNLOAD_ALL )
		{
			trace( DEBUG_TEST,"Updating Download all for Device< %s >", AppReq->AtmId );
			atmbuf.CurrentDownload = DOWNLOAD_ALL;
			atmbuf.NextCommand = GO_OUT_SERVICE;
		}

		switch( atmbuf.NextCommand )
		{
			case GO_OUT_SERVICE:
				if( PutAtmOutOfService( AppReq ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to Put Atm Out of Service" );
					return -1;
				}
				atmbuf.OffsetLength = 0;
                                atmbuf.TotalLength = 0;
				atmbuf.NextCommand = DOWNLOAD_MISC;
				atmbuf.CurrentCommand = GO_OUT_SERVICE;
				AppReq->CommandType = GO_OUT_SERVICE;
				break;

			case DOWNLOAD_MISC:
				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadMiscParam( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Miscellaneous Data" );
					return -1;
				}
				atmbuf.OffsetLength = 0;
                                atmbuf.TotalLength = 0;
				atmbuf.NextCommand = DOWNLOAD_STATE;
				AppReq->DownloadType = DOWNLOAD_MISC;
				if( strcmp( atminfo.AtmTypeId, "D912ATM" ) )
					atmbuf.NextCommand = DOWNLOAD_MISC_E;
				else
				{
					trace( "D912 Protocol...Hence no need of MISC_E" );
					atmbuf.NextCommand = DOWNLOAD_STATE;
				}
				break;
			case DOWNLOAD_MISC_E:
				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
                                if( DownloadMiscParam( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId ) < 0 )
                                {
                                        trace( DEBUG_ERROR,"Failed to Download Enhanced Miscellaneous Data" );
                                        return -1;
                                }

				atmbuf.OffsetLength = 0;
                                atmbuf.TotalLength = 0;
				atmbuf.NextCommand = DOWNLOAD_STATE;
				AppReq->DownloadType = DOWNLOAD_MISC_E;
				break;

			case DOWNLOAD_STATE:
				retval = GetTotalLines( EZ_ATM_STATE_LINE_COUNT, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to count State table" );
					return -1;
				}
				atmbuf.TotalLength = retval;

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				retval = 0;
				trace( "atmbuf.TotalLength[%d] atmbuf.OffsetLength[%d]", atmbuf.TotalLength, atmbuf.OffsetLength );
				retval = DownloadStateTable( AppReq->MsgBuf, atmbuf.OffsetLength, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval	< 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download State Table" );
					return -1;
				}

				atmbuf.OffsetLength += retval;
				if( atmbuf.TotalLength == atmbuf.OffsetLength )
				{
					atmbuf.OffsetLength = 0;
					atmbuf.TotalLength = 0;
					atmbuf.NextCommand = DOWNLOAD_SCREEN;
					AppReq->DownloadType = DOWNLOAD_STATE;
					trace( DEBUG_ERROR,"Download State table completed" );
					break;
				}
				AppReq->DownloadType = DOWNLOAD_STATE;

				break;

			case DOWNLOAD_SCREEN:
				retval = GetTotalLines( EZ_ATM_SCREEN_LINE_COUNT, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to count Screen info" );
					return -1;
				}
				atmbuf.TotalLength = retval;

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				retval = 0;
				retval = DownloadScreenInfo( AppReq->MsgBuf, atmbuf.OffsetLength, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Screen info" );
					return -1;
				}

				atmbuf.OffsetLength += retval;
				if( atmbuf.TotalLength == atmbuf.OffsetLength)
				{
					atmbuf.OffsetLength = 0;
					atmbuf.TotalLength = 0;
					atmbuf.NextCommand = DOWNLOAD_FIT;
					AppReq->DownloadType = DOWNLOAD_SCREEN;
					trace( DEBUG_TEST,"Download Screen info completed" );
					break;
				}
				AppReq->DownloadType = DOWNLOAD_SCREEN;
				break;

			case DOWNLOAD_FIT:

				retval = GetFitCount( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
				if( retval <= 0 )
				{
					trace( DEBUG_ERROR,"Unable to get the FIT count for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
					return -1;
				}
				else
				{
					atmbuf.TotalLength = retval;
					trace( DEBUG_TEST,"Fit -- TotalLength < %d > OffsetLength < %d >", atmbuf.TotalLength, atmbuf.OffsetLength );
				}

				trace( DEBUG_TEST,"Reading FIT Memory for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
				memset( &atmfit, 0, sizeof( struct AtmFit ) );
				if( ReadFitMemory( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId, &atmfit, atmbuf.OffsetLength + 1 ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to Read FIT Table for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
					return -1;
				}
				else
					trace( DEBUG_NORMAL,"Readed FIT Memory for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				retval =  DownloadFITInfo( AppReq->MsgBuf, &atmfit, atmbuf.OffsetLength, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download FIT info" );
					return -1;
				}

				atmbuf.OffsetLength += retval;
				if( atmbuf.TotalLength == atmbuf.OffsetLength )
				{
					atmbuf.OffsetLength = 0;
					atmbuf.TotalLength = 0;
					atmbuf.NextCommand = DOWNLOAD_KEY;
					AppReq->DownloadType = DOWNLOAD_FIT;
					trace( DEBUG_NORMAL,"Download FIT Info completed" );
					break;
				}
				AppReq->DownloadType = DOWNLOAD_FIT;

				break;

			case DOWNLOAD_KEY:

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadKeyInfo( AppReq->MsgBuf, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmKeyLen ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Key" );
					return -1;
				}
				atmbuf.NextCommand = DOWNLOAD_CONFIG_ID;
				AppReq->DownloadType = DOWNLOAD_KEY;
				break;

			case DOWNLOAD_CONFIG_ID:

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadConfigId( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Configuration Id" );
					return -1;
				}

				if( !strcmp( atminfo.AtmTypeId, "NDCatm" ) )
				{
					atmbuf.NextCommand = DOWNLOAD_DATE_TIME;
					AppReq->DownloadType = DOWNLOAD_CONFIG_ID;
				}
				else
				{
					atmbuf.NextCommand = GO_IN_SERVICE;
					AppReq->DownloadType = DOWNLOAD_CONFIG_ID;
				}
				break;

			case DOWNLOAD_DATE_TIME:

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadDateTime( AppReq->MsgBuf, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Date&Time" );
					return -1;
				}
				atmbuf.NextCommand = GO_IN_SERVICE;
				AppReq->DownloadType = DOWNLOAD_DATE_TIME;
				break;

			case GO_IN_SERVICE:

				if( PutAtmInService( AppReq ) < 0 )
				{
					trace( DEBUG_ERROR," Unable to Put Atm In-Serive" );
					return -1;
				}
				atmbuf.CurrentCommand = GO_IN_SERVICE;
				atmbuf.CurrentDownload = 0;
				AppReq->CommandType = GO_IN_SERVICE;
				atmbuf.DownloadFlag = DISABLE;
				break;

			default:
				trace( DEBUG_TEST,"invaild NextCommand < %d >", atmbuf.NextCommand );
				return -1;
		}

		if( PostDriverMsg( AppReq ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Posting Msg to Driver< %s >", AppReq->AtmId );
			return -1;
		}

	}
	else
	{
		if( AppReq->DownloadId == DOWNLOAD_SINGLE )
		{
			trace( DEBUG_NORMAL,"single download< %d >", AppReq->DownloadType );
			atmbuf.CurrentDownload = DOWNLOAD_SINGLE;
			atmbuf.NextCommand = GO_OUT_SERVICE;
		}

		switch( atmbuf.NextCommand )
		{
			case GO_OUT_SERVICE:
				if( PutAtmOutOfService( AppReq ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to Put Atm Out of Service" );
					return -1;
				}
				atmbuf.OffsetLength = 0;
				atmbuf.NextCommand = AppReq->DownloadType;
				atmbuf.CurrentCommand = GO_OUT_SERVICE;
				AppReq->CommandType = GO_OUT_SERVICE;
				break;

			case DOWNLOAD_STATE:

				AppReq->DownloadType = DOWNLOAD_STATE;
				retval = GetTotalLines( EZ_ATM_STATE_LINE_COUNT, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to count state table" );
					return -1;
				}
				atmbuf.TotalLength = retval;

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				retval = DownloadStateTable( AppReq->MsgBuf, atmbuf.OffsetLength, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval	< 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download State Table" );
					return -1;
				}
				atmbuf.OffsetLength += retval;

				if( atmbuf.TotalLength == atmbuf.OffsetLength)
				{
					atmbuf.OffsetLength = 0;
					atmbuf.TotalLength = 0;
					atmbuf.NextCommand = GO_IN_SERVICE;
					trace( DEBUG_ERROR,"Download State table completed" );
					break;
				}
				else
					atmbuf.NextCommand = DOWNLOAD_STATE;
				break;

			case DOWNLOAD_SCREEN:
				AppReq->DownloadType = DOWNLOAD_SCREEN;
				retval = GetTotalLines( EZ_ATM_SCREEN_LINE_COUNT, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to count Screen info" );
					return -1;
				}
				atmbuf.TotalLength = retval;

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				retval = DownloadScreenInfo( AppReq->MsgBuf, atmbuf.OffsetLength, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Screen info" );
					return -1;
				}
				atmbuf.OffsetLength += retval;
				if( atmbuf.TotalLength == atmbuf.OffsetLength)
				{
					atmbuf.OffsetLength = 0;
					atmbuf.TotalLength = 0;
					atmbuf.NextCommand = GO_IN_SERVICE;
					trace( DEBUG_NORMAL,"Download Screen completed" );
					break;
				}
				else
					atmbuf.NextCommand = DOWNLOAD_SCREEN;
				break;

			case DOWNLOAD_MISC:
				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadMiscParam( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Miscellaneous Data" );
					return -1;
				}
				atmbuf.NextCommand = GO_IN_SERVICE;
				AppReq->DownloadType = DOWNLOAD_MISC;
				break;
			
			case DOWNLOAD_MISC_E:                                        //Added for LTS
				if( strcmp( atminfo.AtmTypeId, "D912ATM" ) )
				{
					memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
					if( DownloadMiscParam( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmTypeId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed to Download Enhanced Miscellanous Data" );
						return -1;
					}
					atmbuf.NextCommand = GO_IN_SERVICE;
					AppReq->DownloadType = DOWNLOAD_MISC_E;
				}
				else
					trace( "D912 Protocol ATM...Not a Valid Command" );
				break;

			case DOWNLOAD_FIT:
				AppReq->DownloadType = DOWNLOAD_FIT;
				retval = GetFitCount( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
				if( retval <= 0 )
				{
					trace( DEBUG_ERROR,"Unable to get the FIT count for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
					return -1;
				}
				else
				{
					atmbuf.TotalLength = retval;
					trace( DEBUG_TEST,"Fit -- TotalLength < %d > OffsetLength < %d >", atmbuf.TotalLength, atmbuf.OffsetLength );
				}

				trace( DEBUG_NORMAL,"Reading FIT Memory for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
				memset( &atmfit, 0, sizeof( struct AtmFit ) );
				if( ReadFitMemory( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId, &atmfit, atmbuf.OffsetLength + 1 ) < 0 )
				{
					trace( DEBUG_ERROR,"Unable to Read FIT Table for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );
					return -1;
				}
				else
					trace( DEBUG_ERROR,"Readed FIT Memory for InstId< %s > DeviceLogicalGroup< %s > AtmId< %s >", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AppReq->AtmId );

				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				retval = DownloadFITInfo( AppReq->MsgBuf, &atmfit, atmbuf.OffsetLength, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst );
				if( retval < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download FIT info" );
					return -1;
				}
				atmbuf.OffsetLength += retval;
				if( atmbuf.TotalLength == atmbuf.OffsetLength)
				{
					atmbuf.OffsetLength = 0;
					atmbuf.TotalLength = 0;
					atmbuf.NextCommand = GO_IN_SERVICE;
					trace( DEBUG_NORMAL,"Download FIT Info completed" );
					break;
				}
				else
					atmbuf.NextCommand = DOWNLOAD_FIT;
				break;

			case DOWNLOAD_KEY:
				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadKeyInfo( AppReq->MsgBuf, AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst, atminfo.AtmKeyLen ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Key" );
					return -1;
				}
				atmbuf.NextCommand = GO_IN_SERVICE;
				AppReq->DownloadType = DOWNLOAD_KEY;
				break;

			case DOWNLOAD_CONFIG_ID:
				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadConfigId( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Configuration Id" );
					return -1;
				}
				atmbuf.NextCommand = GO_IN_SERVICE;
				AppReq->DownloadType = DOWNLOAD_CONFIG_ID;
				break;

			case DOWNLOAD_DATE_TIME:
				memset( AppReq->MsgBuf, 0, sizeof( AppReq->MsgBuf ) );
				if( DownloadDateTime( AppReq->MsgBuf , AppReq->AtmId, atminfo.AtmLogicalGroup, atminfo.AcquirerInst ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to Download Date&Time" );
					return -1;
				}
				atmbuf.NextCommand = GO_IN_SERVICE;
				AppReq->DownloadType = DOWNLOAD_DATE_TIME;
				break;

			case GO_IN_SERVICE:
				if( PutAtmInService( AppReq ) < 0 )
				{
					trace( DEBUG_ERROR," Unable to Put Atm In-Serive" );
					return -1;
				}
				atmbuf.CurrentCommand = GO_IN_SERVICE;
				atmbuf.DownloadFlag = DISABLE;
				break;

			default:
				trace( DEBUG_NORMAL,"Single Download Request NextCommand< %d >", atmbuf.NextCommand );
				return -1;
		}

		if( PostDriverMsg( AppReq ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Posting Msg to Driver< %s >", AppReq->AtmId );
			return -1;
		}

	}
	return 1;
}

int EzATMcontroller :: DownloadMiscParam( char *MsgBuf , const char *AtmId, const char *GroupName, const char *InstId, const char *AtmTypeId )
{
	char FileName[ FILENAME_SIZE + 1 ], CfgVal[ TEMP + 1 ];

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_misc.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/misctable", InstId, GroupName, AtmId );

	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_misc.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/misctable",InstId, GroupName );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_misc.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/misctable",InstId );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_misc.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/misctable", AtmTypeId );
				if( cfg_open( FileName ) < 0 )
				{
					trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
					return -1;
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"Filename[%s]", FileName);
	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#camera_control",CfgVal, 2 );
	strcpy( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved1",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved2",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved3",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved4",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#misc1",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved5",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#misc2",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved6",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#reserved7",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#misc3",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#misc4",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "\x1c" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#luno",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "\x1c" );
	strcat( MsgBuf, "00" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer0",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "01" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer1",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "02" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer2",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "03" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer3",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "04" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer4",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "05" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer5",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "06" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer6",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "07" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer7",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "08" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer8",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "09" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer9",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );
	strcat( MsgBuf, "10" );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	cfg_search( "ATM_PARAM#timer10",CfgVal, 2 );
	strcat( MsgBuf, CfgVal );

	cfg_close( );
	return 1;
}

int EzATMcontroller :: GetTotalLines( int FileId , const char *AtmId, const char *GroupName, const char *InstId, const char *AtmTypeId )
{
	char FileName[ FILENAME_SIZE + 1 ];

	int ret, LineCount;

	if( FileId == EZ_ATM_STATE_LINE_COUNT )
	{

		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", InstId, GroupName, AtmId );

		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", InstId, GroupName );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", AtmTypeId );
					if( cfg_open( FileName ) < 0 )
					{
						trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
						return -1;
					}
				}
			}
		}
		trace( DEBUG_NORMAL,"FileName[%s]", FileName );
		LineCount = cfg_group_count( "ATM_STATE" );
		if( LineCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group ATM_STATE in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
	}
	else
	{

		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", InstId, GroupName, AtmId );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", InstId, GroupName );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", InstId );
				if( cfg_open( FileName ) < 0 )
				{
					memset( FileName, 0, sizeof( FileName ) );
					sprintf( FileName, "%s/%s/%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", AtmTypeId );
					if( cfg_open( FileName ) < 0 )
					{
						trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
						return -1;
					}
				}
			}
		}
		trace( DEBUG_NORMAL,"FileName[%s]", FileName );
		LineCount = cfg_group_count( "ATM_SCREEN" );
		trace( DEBUG_TEST,"Screen LineCount <%d>", LineCount);
		if( LineCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group ATM_SCREEN in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
	}
	cfg_close( );
	return LineCount;
}


int EzATMcontroller :: DownloadStateTable( char *StateBuffer, int LineNo, const char *AtmId, const char *GroupName, const char *InstId, const char *AtmTypeId )
{
	char FileName[ FILENAME_SIZE + 1 ], cfgval[ TEMP + 1 ];
	char RecNo[ TEMP + 1 ], LineBuffer[ SCREEN_BUFFER_SIZE + 1 ];

	int ret, StateCount, FldCount;

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", InstId, GroupName, AtmId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", InstId, GroupName );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", InstId );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_state.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/state", AtmTypeId );
				if( cfg_open( FileName ) < 0 )
				{
					trace( DEBUG_ERROR,"Error in opening file[%s]", FileName );
					return -1;
				}
			}
		}
	}

	trace( DEBUG_NORMAL,"FileName[%s]", FileName );
	StateCount = cfg_group_count( "ATM_STATE" );
	if( StateCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching Group ATM_STATE in file[%s]", FileName );
		cfg_close( );
		return -1;
	}
	int LineCount = 0;

	trace( DEBUG_TEST, "LineNo[%d] StateCount[%d]", LineNo, StateCount );

	for( int i = LineNo; i < StateCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "ATM_STATE", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in Searching Group ATM_STATE in file[%s]", FileName );
			cfg_close( );
			return -1;
		}
		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "ATM_STATE", cfgval );
		FldCount = cfg_param_count( RecNo );
		//trace( DEBUG_TEST," State RecNo< %s > FldCount<%d> LineNo<%d>", RecNo, FldCount, LineNo );
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
		if( ( strlen( StateBuffer ) + strlen( LineBuffer ) ) >= 500 )
			break;

		strcat( StateBuffer, LineBuffer );
		//trace( DEBUG_TEST, "LineCount[%d] LineBuffer[%s]", LineCount, LineBuffer );
		LineCount++;
	}
	cfg_close( );
	return LineCount;
}


int EzATMcontroller :: DownloadScreenInfo( char *ScreenBuffer , int LineNo, const char *AtmId, const char *GroupName, const char *InstId, const char *AtmTypeId )
{
	char FileName[ FILENAME_SIZE + 1 ], cfgval[ TEMP + 1 ];
	char RecNo[ TEMP + 1 ], LineBuffer[ SCREEN_BUFFER_SIZE + 1 ];
	int ret, LineCount, FldCount, ScreenCount;

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s_%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", InstId, GroupName, AtmId );
	if( cfg_open( FileName ) < 0 )
	{
		memset( FileName, 0, sizeof( FileName ) );
		sprintf( FileName, "%s/%s/%s_%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", InstId, GroupName );
		if( cfg_open( FileName ) < 0 )
		{
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", InstId );
			if( cfg_open( FileName ) < 0 )
			{
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s_screen.cfg", getenv( "EZDIR_HOME"), "cfg/atm/statetable/screen", AtmTypeId );
				if( cfg_open( FileName ) < 0 )
				{
					trace( DEBUG_ERROR,"Failed to open the file< %s >", FileName);
					return -1;
				}
			}
		}
	}
	trace( DEBUG_NORMAL,"FileName< %s >", FileName);
	ScreenCount = cfg_group_count( "ATM_SCREEN" );
	if( ScreenCount < 0 )
	{
		trace( DEBUG_ERROR,"Error in counting Group ATM_SCREEN in file[%s]", FileName );
		cfg_close( );
		return -1;
	}

	LineCount = 0;
	for( int i = LineNo; i < ScreenCount; i++ )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfg_get_param( "ATM_SCREEN", cfgval, i + 1 ) < 0 )
		{
			trace( DEBUG_ERROR,"Error in searching Group ATM_SCREEN in file[%s]", FileName );
			cfg_close( );
			return -1;
		}

		memset( RecNo, 0, sizeof( RecNo ) );
		sprintf( RecNo, "%s#%s", "ATM_SCREEN", cfgval );

		FldCount = cfg_param_count( RecNo );
		if( FldCount < 0 )
		{
			trace( DEBUG_ERROR,"Error in searching Group < %s > in file[%s]", RecNo, FileName );
			cfg_close( );
			return -1;
		}

		for( int i = 0; i < FldCount; i++ )
		{
			memset( cfgval, 0, sizeof( cfgval ) );
			if( cfg_search( RecNo, cfgval, i + 1 ) < 0 )
			{
				trace( DEBUG_ERROR,"Error in searching Group < %s > in file[%s]", RecNo, FileName );
				cfg_close( );
				return -1;
			}
			//trace( DEBUG_TEST,"RecNo[%s]Cfgval[%s]", RecNo, cfgval );
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
			else
				strcat( LineBuffer,  cfgval );
		}

		strcat( LineBuffer,  "\x1c" );
		if( ( strlen( ScreenBuffer ) + strlen( LineBuffer ) ) >= 500 )
			break;

		strcat( ScreenBuffer, LineBuffer );
		LineCount++;
	}

	cfg_close( );
	return LineCount;
}

int EzATMcontroller :: DownloadFITInfo( char *MsgBuf, struct AtmFit *FITInfo, int Count, const char *AtmId, const char *GroupName, const char *InstId )
{
	char  FitNum[4], PadChar[4], FitDecData[128], *p;
	unsigned char  FitData[39];
	char SecurityId[11];
	struct EzSecurity ezsecurity;

	trace( DEBUG_NORMAL,"SecurityId< %s >", FITInfo->SecurityId );
	memset( &ezsecurity, 0, sizeof( struct EzSecurity ) );
	if( ReadEzSecurityTable( FITInfo->SecurityId, &ezsecurity ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Reading EzSecurityTable EzscurityId < %s > ", FITInfo->SecurityId );
		return -1;
	}

	trace( DEBUG_TEST,"Fit Info: InstId< %s > LogicalGroupName< %s > FitRecord< %s > IndirectState< %c > PinPadChar< %c > PanPadChar< %c > DecimilizationTable< %s >", FITInfo->InstId, FITInfo->AtmLogicalGroup, FITInfo->FitRecord, FITInfo->IndirectState, ezsecurity.PINPadChar, ezsecurity.PANPadChar, ezsecurity.DecimilizationTable );
	memset( FitData, 0, sizeof( FitData ) );
	memset( FitNum, 0, sizeof( FitNum ) );
	sprintf( FitNum, "%03d", Count );
	strcpy( MsgBuf, FitNum );

	memset( FitData, 0, sizeof( FitData ) );
	FitData[0] = 0x00 ;
	sscanf( (const char*)FITInfo->FitRecord , "%02x%02x%02x%02x%02x", &FitData[1], &FitData[2], &FitData[3], &FitData[4], &FitData[5] );
	FitData[6] = FITInfo->IndirectState - 48;
	FitData[7] = 0x00;

	if( ezsecurity.PINLen == 4 )
                FitData[8] = 0x84;
        else if( ezsecurity.PINLen == 5 )
                FitData[8] = 0x85;
        else if( ezsecurity.PINLen == 6 )
                FitData[8] = 0x86;
        else if( ezsecurity.PINLen == 7 )
                FitData[8] = 0x87;
        else if( ezsecurity.PINLen == 8 )
                FitData[8] = 0x88;
        else if( ezsecurity.PINLen == 9 )
                FitData[8] = 0x89;
        else if( ezsecurity.PINLen == 10 )
                FitData[8] = 0x8A;
        else if( ezsecurity.PINLen == 11 )
                FitData[8] = 0x8B;
        else if( ezsecurity.PINLen == 12 )
                FitData[8] = 0x8C;
	else
		FitData[8] = 0x84;

	FitData[9] = 0x00;
	sprintf( PadChar, "0%c", ezsecurity.PINPadChar );
	sscanf( PadChar, "%02x", &FitData[10] );
	FitData[11] = 0x00;
	FitData[12] = 0x1F;
	sprintf( PadChar, "0%c", ezsecurity.PANPadChar );
	sscanf( PadChar, "%02x", &FitData[13] );
	FitData[14] = 0xFF;
	FitData[15] = 0x00;
	sscanf( (const char*)ezsecurity.DecimilizationTable , "%02x%02x%02x%02x%02x%2x%2x%2x", &FitData[16], &FitData[17], &FitData[18], &FitData[19], &FitData[20], &FitData[21], &FitData[22], &FitData[23] );
	sscanf( (const char*)ezsecurity.EPVK , "%02x%02x%02x%02x%02x%2x%2x%2x", &FitData[24], &FitData[25], &FitData[26], &FitData[27], &FitData[28], &FitData[29], &FitData[30], &FitData[31] );

	FitData[32] = 0x00;
	FitData[33] = 0x00;
	FitData[34] = 0x00;
	FitData[35] = 0x00;
	FitData[36] = 0x00;
	FitData[37] = 0x00;

	hex_dump( ( unsigned char* )FitData, 38 );
	p = FitDecData ;
	memset( FitDecData, 0, sizeof( FitDecData ) );
	for( int I = 0; I < 38 ; I++ )
	{
		sprintf( p, "%03d", FitData[ I ] );
		p = p+3;
	}
	trace( DEBUG_TEST,"Dec Data[ %s ]", FitDecData );
	strcat( MsgBuf , FitDecData );
	return 1;
}

int EzATMcontroller :: DownloadConfigId( char *MsgBuf , const char *AtmId, const char *GroupName, const char *InstId )
{
	sprintf( MsgBuf, "%04d", atminfo.AtmConfigId );
	return 1;
}

int EzATMcontroller :: DownloadKeyInfo( char *MsgBuf , const char *AtmId, const char *GroupName, const char *InstId, int KeyLen )
{
	char AtmCommKeyTMK[ ATM_KEY_SIZE + 1 ];
	unsigned char lCommKey[ ATM_KEY_SIZE + 1 ];
	char DecBuf[97] , lKey[ ATM_KEY_SIZE + 1 ];
	int ret;

	memset( AtmCommKeyTMK, 0, sizeof( AtmCommKeyTMK ) );
	if( GenATMCommKey( InstId, AtmId, AtmCommKeyTMK ) < 0 )
	{
		trace( DEBUG_ERROR,"Unable to  generate Comm Key for the Device<%s_%s_%s>", InstId, GroupName, AtmId );
		return -1;
	}

	memset( lKey, 0, sizeof( lKey ) );
	strcpy( lKey, AtmCommKeyTMK );
	memset( lCommKey, 0, sizeof( lCommKey ) );
	//trace( DEBUG_TEST,"lKey<%s> ", lKey);
	if( KeyLen == SINGLE_LENGTH_KEY )
	{
		sscanf( lKey, "%02X%02X%02X%02X%02X%02X%02X%02X", &lCommKey[0], &lCommKey[1], &lCommKey[2], &lCommKey[3], &lCommKey[4], &lCommKey[5], &lCommKey[6], &lCommKey[7] );
		trace( DEBUG_TEST,"Single: lKey<%s> lCommKey< %s >", lKey, lCommKey);
	}
	else if( KeyLen == DOUBLE_LENGTH_KEY )
	{
		sscanf( lKey, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", &lCommKey[0], &lCommKey[1], &lCommKey[2], &lCommKey[3], &lCommKey[4], &lCommKey[5], &lCommKey[6], &lCommKey[7], &lCommKey[8], &lCommKey[9], &lCommKey[10], &lCommKey[11], &lCommKey[12], &lCommKey[13], &lCommKey[14], &lCommKey[15] );
		trace( DEBUG_TEST,"Double: lKey<%s> lCommKey< %s >", lKey, lCommKey);
	}
	else if( KeyLen == TRIPLE_LENGTH_KEY )
	{
		sscanf( lKey, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", &lCommKey[0], &lCommKey[1], &lCommKey[2], &lCommKey[3], &lCommKey[4], &lCommKey[5], &lCommKey[6], &lCommKey[7], &lCommKey[8], &lCommKey[9], &lCommKey[10], &lCommKey[11], &lCommKey[12], &lCommKey[13], &lCommKey[14], &lCommKey[15], &lCommKey[16], &lCommKey[17], &lCommKey[18], &lCommKey[19], &lCommKey[20], &lCommKey[21], &lCommKey[22], &lCommKey[23] );
		trace( DEBUG_TEST,"Triple: lKey<%s> lCommKey< %s >", lKey, lCommKey);
	}
	else
	{
		trace( DEBUG_ERROR, "Invalid Key Length[%d]", KeyLen );
	}

	memset( DecBuf, 0, sizeof( DecBuf ) );

	for( int Ind = 0 ; Ind < KeyLen/2; Ind++ )
	{
		//trace("lCommKey[ %03d ]", lCommKey[ Ind ] );
		sprintf( ( DecBuf + ( Ind * 3 ) ),  "%03d", lCommKey[ Ind ] );

		//trace("[%02d] [%s]", Ind, DecBuf );
	}

	trace( DEBUG_TEST,"Decimal Comm Key Value is [%s]", DecBuf );
	strcpy( MsgBuf, DecBuf );
	return 1;
}

int EzATMcontroller :: DownloadDateTime( char *MsgBuf , const char *AtmId, const char *GroupName, const char *InstId )
{
	time_t now;
	struct tm *nowtime;

	time(&now );
	nowtime = localtime(&now );

	sprintf( MsgBuf, "%02d%02d%02d%02d%02d", (nowtime->tm_year - 100), nowtime->tm_mon+1, nowtime->tm_mday, nowtime->tm_hour, nowtime->tm_min);
	return 1;
}

int EzATMcontroller :: PutAtmInService( struct EzAtmController *AppReq )
{
	AppReq->MsgType = EZ_ATM_COMMAND_REQ;
	AppReq->CommandType = GO_IN_SERVICE;
	return 1;
}

int EzATMcontroller :: PutAtmOutOfService( struct EzAtmController *AppReq )
{
	AppReq->MsgType = EZ_ATM_COMMAND_REQ;
	AppReq->CommandType = GO_OUT_SERVICE;
	return 1;
}

int EzATMcontroller :: GetSupplyCounter( struct EzAtmController *AppReq )
{
	if( AppReq->MsgType == EZ_ATM_COMMAND_REQ && AppReq->CommandType == GET_SUPPLY_COUNTS )
	{
		atmbuf.NextCommand = GO_OUT_SERVICE;
	}
	
	
	switch( atmbuf.NextCommand )
	{
		case GO_OUT_SERVICE:
			atmbuf.NextCommand = GET_SUPPLY_COUNTS;
			atmbuf.CurrentCommand = GO_OUT_SERVICE;
			AppReq->CommandType = GO_OUT_SERVICE;
			atmbuf.OffsetLength = 0;
                        atmbuf.TotalLength = 0;
			break;

		case GET_SUPPLY_COUNTS:
			atmbuf.NextCommand = GO_IN_SERVICE;
			atmbuf.CurrentCommand = GET_SUPPLY_COUNTS;
			AppReq->CommandType = GET_SUPPLY_COUNTS;
			atmbuf.OffsetLength = 0;
                        atmbuf.TotalLength = 0;
			break;
		case GO_IN_SERVICE:
			atmbuf.NextCommand = 0;
			atmbuf.CurrentCommand = GO_IN_SERVICE;
			AppReq->CommandType = GO_IN_SERVICE;
			atmbuf.OffsetLength = 0;
			atmbuf.TotalLength = 0;
			break;
	}


	if( PostDriverMsg( AppReq ) < 0 )
        {
              trace( DEBUG_ERROR,"Error in Posting Msg to Driver< %s >", AppReq->AtmId );
              return -1;
        }

	return 1;

}

int main( int argc, char **argv )
{
    EzATMcontroller ezatmcontrollerobj;
    ezatmcontrollerobj.InitEzATMcontroller( argv[ 0 ] );
    ezatmcontrollerobj.ServiceRequest();
    return 1;
}

