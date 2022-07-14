#include <ezagenttms/ezagenttmsmgr.h>

void EzTMSMgr :: initTMSMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	//EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezagenttmsmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzTMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzPOSMgr Already Running...." );
		trace( "^^^^^^^^^^^EzTMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
/*
	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzTMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
        if( dbutil.DBConnect( ) < 0 )
        {
                trace( DEBUG_ERROR,"Error in Connecting the Database");
                trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
                closeDebug();
                exit( 0 );
        }


	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database...." );
		trace( "^^^^^^^^^^^EzTMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initTMSMgrUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTMSMgrUtil" );
		trace( "^^^^^^^^^^^EzTMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
*/

	if( initTMSMgrUtil( TaskName, this ) < 0 )
        {
                trace( "Error in Initializing EzTMSMgrUtil" );
                trace( "^^^^^^^^^^^EzTMSMgr Ended Abnormally^^^^^^^^^^^^^");
                closeDebug();
                TaskExit();
        }

	/*
	if( LoadFITProfile() < 0 )
	{
		trace( "Error in Loading FIT Profile...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	*/

	if( LoadTMSChannelProperty() < 0 )
	{
		trace( "Error in Loading TMSChannelProperty Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadTMSInBoundProperty() < 0 )
	{
		trace( "Error in Loading TMSInBoundProperty Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadTMSRouteInfo() < 0 )
	{
		trace( "Error in Loading TMSRouteInfo Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadTMSRouteSelect() < 0 )
	{
		trace( "Error in Loading TMSRouteSelect Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadTMSMsgTranslate() < 0 )
	{
		trace( "Error in Loading MsgTranslate Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadTMSTxnRefSelect() < 0 )
	{
		trace( "Error in Loading RefSelect Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadTMSTxnRel() < 0 )
	{
		trace( "Error in Loading TMSTxnRel Table...." );
		trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	//dbutil.DBClose();
	TaskInit();
	initEzSigUtil( this );
}

void EzTMSMgr :: serviceRequest()
{
	while( 1 )
	{
		pause();
	}
}

int main( int argc, char **argv )
{
	EzTMSMgr tmsmgrobj;
	tmsmgrobj.initTMSMgr( argv[ 0 ] );
	tmsmgrobj.serviceRequest();
	return 1;
}


