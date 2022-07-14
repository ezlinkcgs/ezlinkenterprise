#include <ezmms/ezmmsmgr.h>

void EzMMSMgr :: init( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	//EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmmsmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzMMSMgr Already Running...." );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

/*	if( dbutil.initDBUtil( TaskName, this, "EZMMS" ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with MMS Database...." );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}*/

	if( initMMSMgrUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzMMSMgrUtil" );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadMerchantProfile() < 0 )
	{
		trace( "Error in Loading MerchantProfile Table...." );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadStoreProfile() < 0 )
	{
		trace( "Error in Loading StoreProfile Table...." );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadFITProfile() < 0 )
	{
			trace( "Error in Loading FIT Profile...." );
			trace( "^^^^^^^^^^^EzPOSMgr Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
	}

	if( LoadTerminalProfile() < 0 )
	{
		trace( "Error in Loading TerminalProfile Table...." );
		trace( "^^^^^^^^^^^EzMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	//dbutil.DBClose();
	TaskInit();
	initEzSigUtil( this );
}

void EzMMSMgr :: serviceRequest()
{
	while( 1 )
	{
		pause();
	}
}

int main( int argc, char **argv )
{
	EzMMSMgr mmsmgrobj;
	mmsmgrobj.init( argv[ 0 ] );
	mmsmgrobj.serviceRequest();
	return 1;
}






