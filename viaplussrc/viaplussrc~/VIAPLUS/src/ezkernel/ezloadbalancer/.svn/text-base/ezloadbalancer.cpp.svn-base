#include <ezkernel/ezloadbalancer.h>

void EzLoadBalancer :: initLoadBalancer( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezloadbalancer.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzLoadBalancer Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzLoadBalancer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Already One Instance of EzDebugMgr is Running" );
		trace( "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace(  " Error in opening file [%s] ", cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "EZLOADBALANCER#LOOKUPTIME", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching EZLOADBALANCER#LOOKUPTIME from file[%s],,Setting Default Value as 3 Seconds", cfgpath );
		LookUpTime = 3;
	}
	else
	{
		LookUpTime = atoi( CfgVal );
		if( !LookUpTime )
			LookUpTime = 3;
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#ORGKEY", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching CHANNEL#ORGKEY in File[%s]", cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	EzChannelMgrKey = atoi( CfgVal ) + 2;
	EzChannelMgrPortKey = atoi( CfgVal ) + 3;

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXCHANNELS", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching CHANNEL#MAXCHANNELS in File[%s]", cfgpath );
		cfgutil.cfg_close();
		trace(  "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	MaxChannels = atoi( CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXPORTCHANNELS", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching CHANNEL#MAXPORTCHANNELS in File[%s]", cfgpath );
		cfgutil.cfg_close();
		trace(  "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	MaxPortChannels = atoi( CfgVal );
	cfgutil.cfg_close();

	if( LoadChannelMgrMemory() < 0 )
	{
		trace( "Error in Loading ChannelMgr Memory...." );
		trace(  "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

int EzLoadBalancer :: LoadChannelMgrMemory()
{
	EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );
	if( EzChannelMgrQid < 0 )
	{
		trace( "Error in Creating EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortQid = msgget( ( key_t ) EzChannelMgrPortKey, IPC_CREAT | 0666 );
	if( EzChannelMgrPortQid < 0 )
	{
		trace( "Error in Creating EzChannelMgrPort Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrShmid < 0 )
	{
		trace( "Error in Creating EzChannel Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrShmPtr = ( struct EzChannelTable * ) shmat( EzChannelMgrShmid, 0, 0 );
	if( EzChannelMgrShmPtr == NULL )
	{
		trace( "Error in Attaching EzChannel Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrSemid = semget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrSemid < 0 )
	{
		trace( "Error in Creating EzChannel Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortShmid < 0 )
	{
		trace( "Error in Creating EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, 0 );
	if( EzChannelMgrPortShmPtr == NULL )
	{
		trace( "Error in Attaching EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortSemid < 0 )
	{
		trace( "Error in Creating EzChannelPort Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzLoadBalancer :: getChannelCount()
{
	struct sembuf sem_buf;
	int ChannelCount = 0;

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace(" Error in semop operation ...");
			trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TASK_CHANNEL ) && ( strcmp( ( EzChannelMgrShmPtr + i )->TaskName, CHANNEL_INIT_TASK_NAME ) ) && ( strlen( ( EzChannelMgrShmPtr + i )->TaskName ) ) )
				ChannelCount++;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace(" Error in semop operation ...");
			trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return ChannelCount;
}

int EzLoadBalancer :: getChannelQid( int ChCount, int *ChannelQid, char *ChannelName, char *TaskName )
{
	struct sembuf sem_buf;
	int ChannelCount = 0, retval = -1;

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;

		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace(" Error in semop operation ...");
			trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}

		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TASK_CHANNEL ) && ( strcmp( ( EzChannelMgrShmPtr + i )->TaskName, CHANNEL_INIT_TASK_NAME ) ) && ( strlen( ( EzChannelMgrShmPtr + i )->TaskName ) ) )
		{
			ChannelCount++;
			if( ChannelCount == ChCount )
			{
				retval = 1;
				*ChannelQid = ( EzChannelMgrShmPtr + i )->ChannelQid;
				strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 5 );
				strcpy( TaskName, ( EzChannelMgrShmPtr + i )->TaskName );
				sem_buf.sem_op = 2;
				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					trace(" Error in semop operation ...");
					trace(" Sys Error [%s] ", strerror( errno ) );
					return -1;
				}
				break;
			}
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace(" Error in semop operation ...");
			trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return retval;
}

int EzLoadBalancer :: getMaxMsg( const char *ChannelName )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ], cfgstring[ 100 ];
	EzCfgUtil cfgutil;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace(  " Error in opening file [%s] ", cfgpath );
		return -1;
	}
	memset( cfgstring, 0, sizeof( cfgstring ) );
	sprintf( cfgstring, "%s#%s", "EZLOADBALANCER#THROTTLE", ChannelName );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( cfgstring, CfgVal, 2 ) < 0 )
	{
		//trace( "Error in Searching %s from file[%s]", cfgstring, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	else
	{
		if( !atoi( CfgVal ) )
		{
			cfgutil.cfg_close();
			return 10;
		}
		else
		{
			cfgutil.cfg_close();
			return atoi( CfgVal );
		}
	}
}

void EzLoadBalancer :: startBalancing()
{
	int ChannelCount = 0, ChannelQid, retval, MaxMsg;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];
	char TaskName[ TASKNAME_SIZE + 1 ];
	while( 1 )
	{
		sleep( LookUpTime );
		ChannelCount = getChannelCount();
		if( ChannelCount <= 0 )
		{
			trace( "Error in Getting ChannelCount...." );
			if( LoadChannelMgrMemory() < 0 )
			{
				trace( "Error in Loading ChannelMgr Memory...." );
				trace(  "~~~~~~~~~~~~~~~~~~EzLoadBalancer Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
				closeDebug();
				TaskExit();
			}
		}
		trace( "ChannelCount[%d]", ChannelCount );
		for( int i = 0; i < ChannelCount; i++ )
		{
			memset( ChannelName, 0, sizeof( ChannelName ) );
			memset( TaskName, 0, sizeof( TaskName ) );
			retval = getChannelQid( i + 1, &ChannelQid, ChannelName, TaskName );
			if( retval < 0 )
			{
				trace( "Error in Getting ChannelQid for ChannelCount[%d]", i );
				break;
			}
			//trace( "Got ChannelQid[%d] for ChannelName[%s] TaskName[%s]", ChannelQid,  ChannelName, TaskName );
			if( LoadMsgQInfo( ChannelQid ) < 0 )
			{
				trace( "Error in Loading Message Queue Information for ChannelName[%s] TaskName[%s] with Qid[%d]", ChannelName, TaskName, ChannelQid );
				continue;
			}
			MaxMsg = getMaxMsg( ChannelName );
			if( MaxMsg < 0 )
				continue;

			if( GetNMsg() > MaxMsg )
			{
				trace( "Current Message [%d] in Queue for ChannelName[%s] > MaxMsg[%d]..Starting one more Instance of [%s]", GetNMsg(), ChannelName, MaxMsg, TaskName );
				int NProcess = GetNMsg() / MaxMsg;
				trace( "Need to Start %d Instance of Task[%s]", NProcess, TaskName );
				for( int j = 0; j < NProcess; j++ )
				{
					if( StartTask( TaskName ) < 0 )
					{
						trace( "Error in Starting Task[%s]", TaskName );
						break;
					}
					else
						trace( "Started Task[%s] .....Successfully....", TaskName );
				}
			}
		}
	}
}

int main( int argc, char **argv )
{
	EzLoadBalancer ezloadbalancer;
	ezloadbalancer.initLoadBalancer( argv[ 0 ] );
	ezloadbalancer.startBalancing();
	return 1;
}
