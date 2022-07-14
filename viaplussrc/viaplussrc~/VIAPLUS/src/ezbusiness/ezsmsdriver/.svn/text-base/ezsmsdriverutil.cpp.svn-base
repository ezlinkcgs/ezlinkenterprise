#include <ezbusiness/ezsmsdriverutil.h>

int EzSMSDriverUtil :: initSMSDriverUtil( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXGSM", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXGSM from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxGSM = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DEFAULTGSMPORT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching DEFAULTGSMPORT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( DefaultGSMPort, 0, sizeof( DefaultGSMPort ) );
	strcpy( DefaultGSMPort, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "APPCODESEP", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching APPCODESEP from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	
	dptr->trace( DEBUG_NORMAL, "cfgval[%s]", cfgval );
	
	memset( AppCodeSep, 0, sizeof( AppCodeSep ) );
	strcpy( AppCodeSep, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DEFAULTSMSCHANNEL", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching DEFAULTSMSCHANNEL from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( DefaultSMSChannel, 0, sizeof( DefaultSMSChannel ) );
	strcpy( DefaultSMSChannel, cfgval );
	
	dptr->trace( DEBUG_NORMAL, "MaxGSM[%d] DefaultGSMPort[%s] AppCodeSep[%s] DefaultSMSChannel[%s]", MaxGSM, DefaultGSMPort, AppCodeSep, DefaultSMSChannel );
	
	cfgutil.cfg_close();

	GSMMemoryId = CreateMemoryId( dptr, GSM_MEMORY_NAME );

	if( GSMMemoryId < 0 )
	{
		dptr->trace( "Error in Creating [%s] Memory", GSM_MEMORY_NAME );
		cfgutil.cfg_close();
		return -1;
	}

	dptr->trace( "GSM Memory Created with MemoryId[%d]", GSMMemoryId );
	return 1;
}

char* EzSMSDriverUtil :: getDefaultGSMPort()
{
	return DefaultGSMPort;
}

char* EzSMSDriverUtil :: getAppCodeSep()
{
	return AppCodeSep;
}

char* EzSMSDriverUtil :: getDefaultSMSChannel()
{
	return DefaultSMSChannel;
}

int EzSMSDriverUtil :: getMaxGSM()
{
	return MaxGSM;
}

int EzSMSDriverUtil :: createGSMSharedMemory()
{
	struct shmid_ds shmdsptr;
	struct semid_ds semdsptr;

	GSMMemoryShmid = shmget( GSMMemoryId, MaxGSM * sizeof( struct EzGSMInfoTable ), IPC_CREAT | IPC_EXCL | 0666 );

	if( GSMMemoryShmid < 0 )
	{
		if( errno == EEXIST )
		{
			GSMMemoryShmid = shmget( GSMMemoryId, 0, IPC_CREAT | 0666 );
			shmctl( GSMMemoryShmid, IPC_RMID, &shmdsptr );
			GSMMemoryShmid = shmget( GSMMemoryId, MaxGSM * sizeof( struct EzGSMInfoTable ), IPC_CREAT | IPC_EXCL | 0666 );
			if( GSMMemoryShmid < 0 )
			{
				dptr->trace( "Error in Creating GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
		else
		{
			dptr->trace( "Error in Creating GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	GSMMemoryShmPtr = ( struct EzGSMInfoTable * ) shmat( GSMMemoryShmid, 0, 0 );

	if( GSMMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxGSM; i++ )
	{
		memset( GSMMemoryShmPtr + i, 0, sizeof( struct EzGSMInfoTable ) );
		strcpy( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME );
	}

	GSMMemorySemid = semget( GSMMemoryId, MaxGSM, IPC_CREAT | IPC_EXCL | 0666 );

	if( GSMMemorySemid < 0 )
	{
		if( errno == EEXIST )
		{
			GSMMemorySemid = semget( GSMMemoryId, 0, IPC_CREAT | 0666 );
			semctl( GSMMemorySemid, 0, IPC_RMID, &semdsptr );
			GSMMemorySemid = semget( GSMMemoryId, MaxGSM, IPC_CREAT | IPC_EXCL | 0666 );
			if( GSMMemorySemid < 0 )
			{
				dptr->trace( "Error in Creating GSM Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
		else
		{
			dptr->trace( "Error in Creating GSM Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxGSM; i++ )
	{
		if( semctl( GSMMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting GSM Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSMSDriverUtil :: attachGSMSharedMemory()
{
	GSMMemoryShmid = shmget( GSMMemoryId, 0, IPC_CREAT | 0666 );

	if( GSMMemoryShmid < 0 )
	{
		dptr->trace( "Error in Creating GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	GSMMemoryShmPtr = ( struct EzGSMInfoTable * ) shmat( GSMMemoryShmid, 0, 0 );

	if( GSMMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	GSMMemorySemid = semget( GSMMemoryId, 0, IPC_CREAT | 0666 );

	if( GSMMemorySemid < 0 )
	{
		dptr->trace( "Error in Creating GSM Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzSMSDriverUtil :: getCurrGSMCount()
{
	struct sembuf sem_buf;
	int GSMCount = 0;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME ) )
		{
			GSMCount++;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return GSMCount;
}

int EzSMSDriverUtil :: searchGSMInfo( const char *GSMPort )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: searchGSMInfo( const char *GSMPort, struct EzGSMInfoTable *gsminfo_ptr )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			memcpy( gsminfo_ptr, GSMMemoryShmPtr + i, sizeof( struct EzGSMInfoTable ) );
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: searchGSMInfo( pthread_t GSMThreadId, struct EzGSMInfoTable *gsminfo_ptr )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( GSMMemoryShmPtr + i )->GSMThreadId == GSMThreadId )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			memcpy( gsminfo_ptr, GSMMemoryShmPtr + i, sizeof( struct EzGSMInfoTable ) );
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: addGSMInfo( struct EzGSMInfoTable gsminfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME ) )
		{
			retval = 1;
			memcpy( ( GSMMemoryShmPtr + i ), &gsminfo_rec, sizeof( struct EzGSMInfoTable ) );
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: updateGSMStatus( const char *GSMPort, int GSMStatus )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			( GSMMemoryShmPtr + i )->GSMStatus = GSMStatus;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: updateGSMConnStatus( const char *GSMPort, int GSMConnectionStatus )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			( GSMMemoryShmPtr + i )->GSMConnectionStatus = GSMConnectionStatus;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: updateGSMConnectionId( const char *GSMPort, int GSMConnectionId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			( GSMMemoryShmPtr + i )->GSMConnectionId = GSMConnectionId;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}


int EzSMSDriverUtil :: updateGSMInfo( struct EzGSMInfoTable gsminfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, gsminfo_rec.GSMPort ) )
		{
			retval = 1;
			memcpy( ( GSMMemoryShmPtr + i ), &gsminfo_rec, sizeof( struct EzGSMInfoTable ) );
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: removeGSMInfo( const char *GSMPort )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			memset( ( GSMMemoryShmPtr + i )->GSMPort, 0, sizeof( ( GSMMemoryShmPtr + i )->GSMPort ) );
			strcpy( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME );
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSMSDriverUtil :: removeGSMInfo( const char *GSMPort, struct EzGSMInfoTable *gsminfo_ptr )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			memcpy( gsminfo_ptr, GSMMemoryShmPtr + i, sizeof( struct EzGSMInfoTable ) );
			memset( ( GSMMemoryShmPtr + i )->GSMPort, 0, sizeof( ( GSMMemoryShmPtr + i )->GSMPort ) );
			strcpy( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME );
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}
