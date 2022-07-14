#include <ezbusiness/ezposmgr.h>

void EzPOSMgr :: InitPOSMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezposmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzPOSMgr Already Running...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( InitPOSMgrUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzPOSMgrUtil" );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMCCInfo() < 0 )
	{
		trace( "Error in Loading POSMCCInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMerchantTypeInfo() < 0 )
	{
		trace( "Error in Loading POSMerchantType Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMerchantInfo() < 0 )
	{
		trace( "Error in Loading POSMerchantInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTerminalTypeInfo() < 0 )
	{
		trace( "Error in Loading POSTerminalTypeInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTerminalInfo() < 0 )
	{
		trace( "Error in Loading POSTerminalInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSStoreInfo() < 0 )
	{
		trace( "Error in Loading POSStoreInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTxnInfo() < 0 )
	{
		trace( "Error in Loading POSTxnInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSRespCodeInfo() < 0 )
	{
		trace( "Error in Loading POSRespCodeInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSInBoundProperty() < 0 )
	{
		trace( "Error in Loading POSInBoundProperty Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSRouteInfo() < 0 )
	{
		trace( "Error in Loading POSRouteInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSRouteSelect() < 0 )
	{
		trace( "Error in Loading POSRouteSelect Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMsgTranslate() < 0 )
	{
		trace( "Error in Loading POSMsgTranslate Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSChannelProperty() < 0 )
	{
		trace( "Error in Loading POSChannelProperty Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTxnRefSelect() < 0 )
	{
		trace( "Error in Loading POSTxnRefSelect Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTxnRel() < 0 )
	{
		trace( "Error in Loading POSTxnRel Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	dbutil.DBClose();
	TaskInit();
	initEzSigUtil( this );
}

void EzPOSMgr :: ServiceRequest()
{
	while( 1 )
	{
		pause();
	}
}

int main( int argc, char **argv )
{
	EzPOSMgr posmgrobj;
	posmgrobj.InitPOSMgr( argv[ 0 ] );
	posmgrobj.ServiceRequest();
	return 1;
}


