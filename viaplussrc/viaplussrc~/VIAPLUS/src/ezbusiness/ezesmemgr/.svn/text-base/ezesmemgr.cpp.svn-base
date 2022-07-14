/*External Short Message Entity (ESME) Manager*/

#include <ezbusiness/ezesmemgr.h>

void EzESMEMgr :: initEzESMEMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];

	bool DebugFlag = false;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezesmemgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( ESMECHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating Channel[%s]", ESMECHANNEL );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initEzESMEmgrUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzESMEmgrUtil" );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateESMEQueue() < 0 )
	{
		trace( "Error in Initializing ESME Queue..." );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil..." );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB...." );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadSMSCInfoSharedMemory() < 0 )
	{
		trace( "Error in Loading SMSCInfo Memory..." );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	ListSMSCInfo( SMSCInfoMemoryShmPtr, MaxSMSC );

	if( initEzSMSCUtil( this ) < 0 )
	{
		trace( "Error in Initializing SMSC Util..." );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	struct EzSMSCInfo smscinfo;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxSMSC; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for SMSCInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( strcmp( ( SMSCInfoMemoryShmPtr + i )->SMSCName, SMSC_INIT_NAME ) )
		{
			memset( &smscinfo, 0, sizeof( struct EzSMSCInfo ) );
			memcpy( &smscinfo, SMSCInfoMemoryShmPtr + i, sizeof( struct EzSMSCInfo ) );
			connectSMSC( &smscinfo );
			//initSMPPUtil( this, &smscinfo );
		}

		sem_buf.sem_op = 2;
		if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for SMSCInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
	}

	if( initEventUtil( this, TaskName ) < 0 )
	{
		trace( "Error in Initializing EventUtil" );
		trace( "^^^^^^^^^^^EzESMEmgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void EzESMEMgr :: ServiceRequest()
{
	while (1)
	{

	}
}

int main( int argc, char **argv )
{
	EzESMEMgr esmeobj;
	esmeobj.initEzESMEMgr( argv[ 0 ] );
	esmeobj.ServiceRequest();
	return 1;
}
