#include <ezbusiness/ezguicontroller.h>

int EzGuiController :: InitEzGuiController( const char * TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezguicontroller.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
	   trace( DEBUG_ERROR, "Error in Initializing EzTaskUtil" );
	   trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
	   closeDebug();
	   exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzChannelUtil" );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( InitEzCommUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzCommUtil" );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( GUICHANNEL, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Creating EzGuiController Channel" );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( !IsTaskRunning( "EzATMController" ) )
	{
		trace( "EzATMController is not running " );
		trace( "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( !IsTaskRunning( "EzAtmMgr" ) )
	{
		trace( "EzATMController is not running " );
		trace( "^^^^^^^^^^^EzATMcmd Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
		return -1;
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "TASK#MAXTASK", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching TASK#MAXTASK in File[%s]", cfgpath );
		cfgutil.cfg_close();
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	MaxTask = atoi( CfgVal );

	trace( DEBUG_TEST, "MaxTask[%d]", MaxTask );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "PORT#MAXPORT", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching PORT#MAXPORT in File[%s]", cfgpath );
		cfgutil.cfg_close();
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	MaxPort = atoi( CfgVal );
	trace( DEBUG_TEST, "MaxPort[%d]", MaxPort );

	cfgutil.cfg_close();

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezbusiness.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXGUIBYTES", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching EZBUSINESS#MAXGUIBYTES in File[%s]", cfgpath );
		cfgutil.cfg_close();
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	MaxGuiBytes = atoi( CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXFIT", CfgVal, 2 ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#MAXFIT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( CfgVal ) < 0 )
	{
		trace( DEBUG_ERROR,"Invalid EZBUSINESS#MAXFIT[%s] value defined in file[%s]", CfgVal, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxFits = atoi( CfgVal );

	POSFlag = false;
	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "EZBUSINESS#POS_INSTALLED", CfgVal, 2 ) < 0 )
		trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#POS_INSTALLED from file[%s]..setting POSFlag as Flag", cfgpath );
	else if( !strcasecmp( CfgVal, "Yes" ) )
		POSFlag = true;

	AlertFlag = false;
	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "EZBUSINESS#ALERT_INSTALLED", CfgVal, 2 ) < 0 )
		trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#ALERT_INSTALLED from file[%s]..setting POSFlag as Flag", cfgpath );
	else if( !strcasecmp( CfgVal, "Yes" ) )
		AlertFlag = true;

	cfgutil.cfg_close();

	if( initEzGuiControllerODBC( TaskName, this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzGuiControllerODBC");
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguitaskrequest.initGUITaskRequest( this, this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing GUITaskRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguichannelrequest.initGUIChannelRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing GUITaskRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguiportrequest.initGUIPortRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing GUITaskRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguiatmrequest.initGUIATMRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIATMRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguibinrequest.initGUIBINRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIBINRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguibranchrequest.initGUIBranchRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIBranchRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguiinstrequest.initGUIInstRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIInstRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguiinstselectrequest.initGUIInstSelectRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIInstSelectRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguibinselectrequest.initGUIBINSelectRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
			trace( "Error in Initializing EzGUIBINSelectRequest...." );
			trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
	}

	if( ezguinetworkselectrequest.initGUINetworkSelectRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUINetworkSelectRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguinetworkrequest.initGUINetworkRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUINetworkRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	 if( ezguibusdayrequest.initGUIBusDayRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	 {
		 trace( "Error in Initializing EzGUIBusDayRequest...." );
		 trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		 closeDebug();
		 TaskExit();
	 }


	if( ezguireplayrequest.initGUIReplayRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIReplayRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguiechorequest.initGUIEchoRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIEchoRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguisecurityrequest.initGUISecurityRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUISecurityRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguifitrequest.initGUIFITRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUISecurityRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezguibinrequest.initGUIBINRequest( this, this, this, this, MaxGuiBytes ) < 0 )
	{
		trace( "Error in Initializing EzGUIBINRequest...." );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	/*if( POSFlag )
	{
		if( ezguiposrequest.initGUIPOSRequest( this, this, this, this, MaxGuiBytes ) < 0 )
		{
			trace( "Error in Initializing EzGUIPOSRequest...." );
			trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
		}
	}

	if( AlertFlag )
	{
		if( ezguialertrequest.initGUIAlertRequest( this, this, this, this, MaxGuiBytes ) < 0 )
        {
			trace( "Error in Initializing EzGUIAlertRequest...." );
			trace( DEBUG_ERROR, "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
		}
	}
	 */

	TaskInit();
	initEzSigUtil( this );
}

void EzGuiController :: ServiceRequest()
{
	char ReadBuf[ GUI_BUFFER_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	int BufSize;

	while( 1 )
	{
		trace( DEBUG_NORMAL, "Waiting for Message in EzGuiController Channel" );
		memset( ReadBuf, 0, sizeof( ReadBuf ) );
		if( ReadMessage( ReadBuf, &BufSize ) < 1 )
		{
			trace( DEBUG_ERROR, "Error in Reading EzATMController Channel" );
			continue;
		}
		trace( DEBUG_NORMAL, "Message received from [ %s ]", GetLastSenderChannelName() );

		memset( TempStr, 0, sizeof( TempStr ) );
		getToken( ReadBuf, TempStr, GUI_GS, 1 );

		if( !strcasecmp( TempStr, TASK_REQ ) )
			ezguitaskrequest.processTaskRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, PORT_REQ ) )
			ezguiportrequest.processPortRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, CHANNELTASK_REQ ) )
			ezguichannelrequest.processChannelTaskRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, CHANNELPORT_REQ ) )
			ezguichannelrequest.processChannelPortRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, CHANNELMEMORY_REQ ) )
			ezguichannelrequest.processChannelMemoryRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, NETWORK_REQ ) )
			ezguinetworkrequest.processNetworkRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, BUSDAY_REQ ) )
			ezguibusdayrequest.processBusDayRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, REPLAY_REQ ) )
			ezguireplayrequest.processReplayRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, ECHO_REQ ) )
			ezguiechorequest.processEchoRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, ECHOPROPERTY_REQ ) )
			ezguiechorequest.processEchoPropertyRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, ATM_REQ ) )
		{
			if( ezguiatmrequest.processATMRequest( ReadBuf ) > 0 )
				ezguisecurityrequest.processATMKeyRequest( ReadBuf );
		}
		else if ( !strcasecmp( TempStr, SECURITY_REQ ) )
			ezguisecurityrequest.processSecurityRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, FIT_REQ ) )
			ezguifitrequest.processFITRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, INST_REQ ) )
			ezguiinstrequest.processInstRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, INSTSELECT_REQ ) )
			ezguiinstselectrequest.processInstSelectRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, BINSELECT_REQ ) )
		    ezguibinselectrequest.processBINSelectRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, BIN_REQ ) )
			ezguibinrequest.processBINRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, NTWKSELECT_REQ ) )
			ezguinetworkselectrequest.processNetworkSelectRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, BRANCH_REQ ) )
			ezguibranchrequest.processBranchRequest( ReadBuf );
		else if ( !strcasecmp( TempStr, BIN_REQ ) )
			ezguibinrequest.processBINRequest( ReadBuf );
		else
		{
			trace( DEBUG_ERROR, "UnSupported Request[%s] from gui", TempStr );
			continue;
		}
		/*else if ( !strncasecmp( TempStr, "POS_", 4 ) )
			ezguiposrequest.processPOSRequest( ReadBuf );
		else if( !strcasecmp( TempStr, ALERT_REQ ) )
			ezguialertrequest.processAlertRequest( ReadBuf );
		else if( !strcasecmp( TempStr, ALERTDESC_REQ ) )
			ezguialertrequest.processAlertDescRequest( ReadBuf );*/
	}
}

int main( int argc, char **argv )
{
    EzGuiController ezatmcontrollerobj;
    ezatmcontrollerobj.InitEzGuiController( argv[ 0 ] );
    ezatmcontrollerobj.ServiceRequest();
    return 1;
}
