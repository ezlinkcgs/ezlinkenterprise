#include <ezlink/ezinstmgr.h>

void EzInstMgr :: initInstMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	//EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezinstmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzInstMgr Already Running...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initInstMgrUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzInstMgrUtil" );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	/*if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}*/


	if( LoadInstRouteType() < 0 )
	{
		trace( "Error in Loading InstRouteType Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadInstProfile() < 0 )
	{
		trace( "Error in Loading InstProfile Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadInstSelect() < 0 )
	{
		trace( "Error in Loading InstSelect Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadBINSelect() < 0 )
	{
		trace( "Error in Loading BINSelect Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadNetworkSelect() < 0 )
	{
		trace( "Error in Loading NetworkSelect Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadBINProfile() < 0 )
	{
		trace( "Error in Loading BINProfile Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadBranchProfile() < 0 )
	{
		trace( "Error in Loading BranchProfile Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadBINRange() < 0 )
	{
		trace( "Error in Loading BINRange Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadDeviceTypeMap() < 0 )
	{
		trace( "Error in Loading DeviceTypeMap Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadAuthProperty() < 0 )
	{
		trace( "Error in Loading AuthProperty Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadChannelProperty() < 0 )
	{
		trace( "Error in Loading ChannelProperty Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadEventProperty() < 0 )
	{
		trace( "Error in Loading EventProperty Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadInBoundMsgProperty() < 0 )
	{
		trace( "Error in Loading InBoundMsgProperty Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadMsgTypeProperty() < 0 )
	{
		trace( "Error in Loading MsgTypeProperty Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadMsgTranslate() < 0 )
	{
		trace( "Error in Loading MsgTranslate Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTxnRefSelect() < 0 )
	{
		trace( "Error in Loading TxnRefSelect Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTxnRouteInfo() < 0 )
	{
		trace( "Error in Loading TxnRouteInfo Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTxnRouteSelect() < 0 )
	{
		trace( "Error in Loading TxnRouteSelect Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTxnMsgOrder() < 0 )
	{
		trace( "Error in Loading TxnMsgOrder Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadInstExtNtwkProfile() < 0 )
	{
		trace( "Error in Loading InstExtNtwkProfile Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadExtNtwkProfile() < 0 )
	{
		trace( "Error in Loading InstExtNtwkProfile Table...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTxnMonInfo() < 0 )
	{
		trace( "Error in Loading TxnMonInfo Memory...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadSafProperty() < 0 )
	{
		trace( "Error in Loading SafProperty Memory...." );
		trace( "^^^^^^^^^^^EzInstMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	//dbutil.DBClose();
	TaskInit();
	initEzSigUtil( this );
}

void EzInstMgr :: serviceRequest()
{
	while( 1 )
	{
		pause();
	}
}

int main( int argc, char **argv )
{
	EzInstMgr instmgrobj;
	instmgrobj.initInstMgr( argv[ 0 ] );
	instmgrobj.serviceRequest();
	return 1;
}



