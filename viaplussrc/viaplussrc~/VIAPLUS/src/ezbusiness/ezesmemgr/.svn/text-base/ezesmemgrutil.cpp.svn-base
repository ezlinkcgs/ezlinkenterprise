#include <ezbusiness/ezesmemgrutil.h>

EzESMEmgrUtil :: EzESMEmgrUtil()
{
}

EzESMEmgrUtil :: ~EzESMEmgrUtil()
{
}

int EzESMEmgrUtil :: initEzESMEmgrUtil( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezesme.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]", cfgpath );
		return -1;
	}


	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXSMSC", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXSMSC from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXSMSC[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxSMSC = atoi( cfgval );

	cfgutil.cfg_close();


	ESMEKey = CreateChannelId( dptr, ESMECHANNEL );
	if( ESMEKey < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Channel[%s]....SysErr[%s] ErrNo[%d]", ESMECHANNEL, strerror( errno ), errno );
		return -1;
	}

	if( CreateESMEQueue() < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Queue for Channel[%s]....SysErr[%s] ErrNo[%d]", ESMECHANNEL, strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzESMEmgrUtil :: CreateESMEQueue()
{
	ESMEQid = msgget( ( key_t ) ESMEKey, IPC_CREAT | 0666 );
	if( ESMEQid < 0 )
	{
		dptr->trace( "Error in Creating ESME Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzESMEmgrUtil :: CheckInteger( const char *value )
{
    for( int i = 0; i < strlen( value ); i++ )
    {
        if( ( value[ i ] < 48 ) || ( value[ i ] > 57 ) )
        	return -1;
    }
    return 1;
}

int EzESMEmgrUtil :: LoadSMSCInfoSharedMemory()
{
	struct EzSMSCInfo smscinfo;
	struct sembuf sem_buf;
	int SMSCInfoCount = 0;

	dptr->trace( DEBUG_NORMAL,"Loading ESME Info Memory.. MaxSMSC[%d]", MaxSMSC );

	SMSCInfoMemoryShmid = shmget( ( key_t ) SMSCInfoMemoryId, sizeof( struct EzSMSCInfo ) * MaxSMSC, IPC_CREAT | 0666 );
	if(  SMSCInfoMemoryShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating SMSCInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SMSCInfoMemoryShmPtr = ( struct EzSMSCInfo * ) shmat( SMSCInfoMemoryShmid, 0, 0 );

	if( SMSCInfoMemoryShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching SMSCInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxSMSC; i++ )
	{
		memset( ( SMSCInfoMemoryShmPtr + i ), 0, sizeof( struct EzSMSCInfo ) );
		strcpy( ( SMSCInfoMemoryShmPtr + i )->SMSCName, SMSC_INIT_NAME );
	}

	SMSCInfoCount = getSMSCInfoCount( &SqlErr );

	if( SMSCInfoCount == 0 )
		dptr->trace( DEBUG_ERROR,"No SMSCInfo Configured" );

	if( SMSCInfoCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting SMSCInfo Table Count OraErr[%05d]", SqlErr );
		return -1;
	}

	if( SMSCInfoCount > MaxSMSC )
	{
		dptr->trace( DEBUG_ERROR,"No.of SMSCInfos configured in SMSCInfo Table > MaxSMSC...Increase the MaxSMSC Parameter");
		return -1;
	}

	if( readSMSCInfo( SMSCInfoMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while loading SMSCInfo Table OraErr[%05d]", SqlErr );
		return -1;
	}


	SMSCInfoMemorySemid = semget( ( key_t ) SMSCInfoMemoryId, MaxSMSC, IPC_CREAT | 0666 );
	if( SMSCInfoMemorySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating SMSCInfo Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxSMSC; i++ )
	{
		if( semctl( SMSCInfoMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting SMSCInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	dptr->trace( DEBUG_TEST,"Loaded SMSCInfo Memory");
	return 1;
}

int EzESMEmgrUtil :: getSMSCInfoSharedMemory()
{
	SMSCInfoMemoryId = LocateMemoryId( dptr, "SMSCInfoMEMORY" );

	if( SMSCInfoMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Locating Memory[%s]", "SMSCInfoMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Located with MemoryId[%d]", "SMSCInfoMEMORY", SMSCInfoMemoryId );

	SMSCInfoMemoryShmid = shmget( ( key_t ) SMSCInfoMemoryId, 0, IPC_CREAT | 0666 );

	if( SMSCInfoMemoryShmid < 0 )
	{
		dptr->trace( "Error in Getting SMSCInfoMemory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	SMSCInfoMemoryShmPtr = ( struct EzSMSCInfo * ) shmat( SMSCInfoMemoryShmid, 0, 0 );
	if( SMSCInfoMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching SMSCInfo Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SMSCInfoMemorySemid = semget( ( key_t ) SMSCInfoMemoryId, 0, IPC_CREAT | 0666 );
	if( SMSCInfoMemorySemid < 0 )
	{
		dptr->trace( "Error in SMSCInfo Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzESMEmgrUtil :: readSMSCInfoMemory( const char *SMSCName, struct EzSMSCInfo *SMSCInfoObj )
{
	struct sembuf sem_buf;
	int retval = -1;
	for( int i = 0; i < MaxSMSC; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for SMSCInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( SMSCInfoMemoryShmPtr + i )->SMSCName, SMSCName ) )
		{
			retval = 1;
			memcpy( &SMSCInfoObj, 0, sizeof( struct EzSMSCInfo ) );
			sem_buf.sem_op = 2;
			if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for SMSCInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for SMSCInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzESMEmgrUtil :: updateSMSCStatus( const char *SMSCName, int SMSCStatus )
{
	struct sembuf sem_buf;
	int retval = -1;
	for( int i = 0; i < MaxSMSC; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for SMSCInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( SMSCInfoMemoryShmPtr + i )->SMSCName, SMSCName ) )
		{
			retval = 1;
			( SMSCInfoMemoryShmPtr + i )->SMSCStatus = SMSCStatus;
			sem_buf.sem_op = 2;
			if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for SMSCInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SMSCInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for SMSCInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

void EzESMEmgrUtil :: ListSMSCInfo( struct EzSMSCInfo *smscinfoptr, int MaxSMSC )
{

	for( int i = 0; i < MaxSMSC ; i++ )
	{
		if( strcmp( ( smscinfoptr + i )->SMSCName, SMSC_INIT_NAME ) )
		{
			dptr->trace( "SMSCName[%s]", ( smscinfoptr + i )->SMSCName );
			dptr->trace( "IpAddress[%s]", ( smscinfoptr + i )->IpAddress );
			dptr->trace( "TcpIpHeaderType[%s]", ( smscinfoptr + i )->TcpIpHeaderType );
			dptr->trace( "SystemId[%s]", ( smscinfoptr + i )->SystemId );
			dptr->trace( "Password[%s]", ( smscinfoptr + i )->Password );
			dptr->trace( "SystemType[%s]", ( smscinfoptr + i )->SystemType );
			dptr->trace( "TxnChannel[%s]", ( smscinfoptr + i )->TxnChannel );
			dptr->trace( "PortNo[%d]", ( smscinfoptr + i )->PortNo );
			dptr->trace( "TcpIpHeaderLen[%d]", ( smscinfoptr + i )->TcpIpHeaderLen );
			dptr->trace( "ConnectionInterval[%d]", ( smscinfoptr + i )->ConnectionInterval );
		}
	}
}
