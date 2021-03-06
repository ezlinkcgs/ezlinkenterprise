#include <ezkernel/ezchannelmgrutil.h>

int EzChannelMgrUtil :: InitEzChannelMgrUtil( EzDebugUtil *dptr, int OrgKey, int MaxIpcKeys, int MaxChannels, int MaxPortChannels )
{
	this->dptr = dptr;
	this->MaxChannels = MaxChannels;
	this->MaxPortChannels = MaxPortChannels;
	this->MaxIpcKeys = MaxIpcKeys;
	this->OrgKey = OrgKey;
	this->EzChannelMgrAckKey = OrgKey + 1;
	this->EzChannelMgrKey = OrgKey + 2;
	this->EzChannelMgrPortKey = OrgKey + 3;
	InitEzIPCKeyUtil( dptr, OrgKey + 4, MaxIpcKeys );
	if( ezchannelparam.initChannelParam( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ChannelParam...." );
		return -1;
	}
	return 1;
}

int EzChannelMgrUtil :: CreateEzChannelMgrQueue()
{
	EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );
	if( EzChannelMgrQid < 0 )
	{
		dptr->trace( "Error in ChannelMgr Queue Creation ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	dptr->trace( "EzChannelMgr Queue Created with Id[%d]", EzChannelMgrQid );
	return 1;
}

int EzChannelMgrUtil :: IsChannelMgrRestarted()
{
	int EzChannelMgrAckSemid;
	struct sembuf sem_buf;

	EzChannelMgrAckSemid = semget( ( key_t ) EzChannelMgrAckKey, 2, IPC_CREAT | 0666 );

	if( EzChannelMgrAckSemid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgrAck Semaphore SysErr[%s] errno[%d]", strerror( errno ), errno );
		return -1;
	}

	if( semctl( EzChannelMgrAckSemid, 1, GETVAL, 0 ) == 2 )
	{
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_num = 1;
		sem_buf.sem_op = 3;

		if( semop( EzChannelMgrAckSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop for EzChannelMgrChildAck Semaphore Sys Err[%s]", strerror( errno ) );
			return -1;
		}
		return 1;
	}
	else if ( semctl( EzChannelMgrAckSemid, 1, GETVAL, 0 ) == 5 )
		return 0;
	else
	{
		union semun
		{
			int val;
			struct semid_ds *buf;
			unsigned short *array;
		};

		union semun arg;
		arg.val = 2;
		if( semctl( EzChannelMgrAckSemid, 1, SETVAL, arg ) < 0 )
			return -1;

		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_num = 1;
		sem_buf.sem_op = 3;

		if( semop( EzChannelMgrAckSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop for EzChannelMgrChildAck Semaphore Sys Err[%s]", strerror( errno ) );
			return -1;
		}
		return 0;
	}
}

int EzChannelMgrUtil :: GetEzChannelMgrQid()
{
	return EzChannelMgrQid;
}

int EzChannelMgrUtil :: LocateEzChannelMgrSharedMemory()
{
	EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrShmid < 0 )
	{
		dptr->trace( "Error in ChannelMgr Shared Memory Creation SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	dptr->trace( "EzChannelMgr Shared Memory Created with Id[%d]", EzChannelMgrShmid );
	EzChannelMgrShmPtr = ( struct EzChannelTable * ) shmat( EzChannelMgrShmid, 0, 0 );
	if( EzChannelMgrShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzChannelMgr Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	EzChannelMgrSemid = semget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrSemid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortShmid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Port Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	dptr->trace( "EzChannelMgr Port Shared Memory Created with Id[%d]", EzChannelMgrPortShmid );

	EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, 0 );
	if( EzChannelMgrPortShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzChannelMgr Port Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortSemid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Port Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( GetIPCKeySharedMemory() < 0 )
	{
		dptr->trace( "Error in Creating EzIpcKeyUtil Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzChannelMgrUtil :: CreateEzChannelMgrSharedMemory()
{
	struct shmid_ds shmdsptr;
	struct semid_ds semdsptr;

	EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, MaxChannels * sizeof( struct EzChannelTable ), IPC_CREAT | IPC_EXCL | 0666 );
	if( EzChannelMgrShmid < 0 )
	{
		EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
		shmctl( EzChannelMgrShmid, IPC_RMID, &shmdsptr );
		EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, MaxChannels * sizeof( struct EzChannelTable ), IPC_CREAT | IPC_EXCL | 0666 );
		if( EzChannelMgrShmid < 0 )
		{
			dptr->trace( " Error in EzChannelMgr Shared Memory Creation SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	dptr->trace( "EzChannelMgr Shared Memory Created with Id[%d]", EzChannelMgrShmid );
	EzChannelMgrShmPtr = ( struct EzChannelTable * ) shmat( EzChannelMgrShmid, 0, 0 );
	if( EzChannelMgrShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzChannelMgr Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	EzChannelMgrSemid = semget( ( key_t ) EzChannelMgrKey, MaxChannels, IPC_CREAT | IPC_EXCL | 0666 );
	if( EzChannelMgrSemid < 0 )
	{
		EzChannelMgrSemid = semget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
		semctl( EzChannelMgrSemid, 0, IPC_RMID, &semdsptr );
		EzChannelMgrSemid = semget( ( key_t ) EzChannelMgrKey, MaxChannels, IPC_CREAT | IPC_EXCL | 0666 );
		if( EzChannelMgrSemid < 0 )
		{
			dptr->trace("Error in Creating EzChannelMgr Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxChannels; i++ )
	{
		if( semctl( EzChannelMgrSemid, i, SETVAL, arg ) < 0 )
			return -1;
	}

	InitChannelTable();

	EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, MaxPortChannels * sizeof( struct EzChannelPortTable ), IPC_CREAT | IPC_EXCL | 0666 );
	if( EzChannelMgrPortShmid < 0 )
	{
		EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
		shmctl( EzChannelMgrPortShmid, IPC_RMID, &shmdsptr );
		EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, MaxPortChannels * sizeof( struct EzChannelPortTable ), IPC_CREAT | IPC_EXCL | 0666 );
		if( EzChannelMgrPortShmid < 0 )
		{
			dptr->trace( " Error in EzChannelMgrPort Shared Memory Creation SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	dptr->trace( "EzChannelPortMgr Shared Memory Created with Id[%d]", EzChannelMgrPortShmid );
	EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, 0 );
	if( EzChannelMgrPortShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzChannelMgr Port Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, MaxPortChannels, IPC_CREAT | IPC_EXCL | 0666 );
	if( EzChannelMgrPortSemid < 0 )
	{
		EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
		semctl( EzChannelMgrPortSemid, 0, IPC_RMID, &semdsptr );
		EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, MaxPortChannels, IPC_CREAT | IPC_EXCL | 0666 );
		if( EzChannelMgrPortSemid < 0 )
		{
			dptr->trace( "Error in Creating EzChannelMgr Port Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	arg.val = 2;

	for( int i = 0; i < MaxPortChannels; i++ )
	{
		if( semctl( EzChannelMgrPortSemid, i, SETVAL, arg ) < 0 )
			return -1;
	}

	InitChannelPortTable();

	if( CreateTaskChannel( "EzTaskMgr", "EzTaskMgr", OrgKey ) < 0 )
	{
		dptr->trace( "Error in Creating EzTaskMgr Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( CreateTaskChannel( "EzChannelMgr", "EzChannelMgr", OrgKey + 2 ) < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( CreateTaskChannel( "EzChannelPortMgr", "EzChannelMgr", OrgKey + 3 ) < 0 )
	{
		dptr->trace( "Error in Creating EzChannelPortMgr Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( CreateIPCKeySharedMemory() < 0 )
	{
		dptr->trace( "Error in Creating EzIpcKeyUtil Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;

}

void EzChannelMgrUtil :: InitChannelTable()
{
	for( int i = 0; i < MaxChannels; i++ )
	{
		( EzChannelMgrShmPtr + i )->ChannelKeyId = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->ChannelQid = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->ChannelShmId = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->ChannelSemId = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->ChannelType = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->MaxSegment = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->MaxSegmentLock = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->CurrentBufferSize = CHANNEL_INIT_VAL;
		( EzChannelMgrShmPtr + i )->DropCount = CHANNEL_INIT_VAL;
		memset( ( EzChannelMgrShmPtr + i )->ChannelName, 0, sizeof( ( EzChannelMgrShmPtr + i )->ChannelName ) );
		strcpy( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME );
		memset( ( EzChannelMgrShmPtr + i )->TaskName, 0, sizeof( ( EzChannelMgrShmPtr + i )->TaskName ) );
		strcpy( ( EzChannelMgrShmPtr + i )->TaskName, CHANNEL_INIT_TASK_NAME );
	}
}

void EzChannelMgrUtil :: InitChannelTable( int segOffset )
{
	( EzChannelMgrShmPtr + segOffset )->ChannelKeyId = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->ChannelQid = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->ChannelShmId = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->ChannelSemId = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->MaxSegment = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->MaxSegmentLock = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->CurrentBufferSize = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->DropCount = CHANNEL_INIT_VAL;
	( EzChannelMgrShmPtr + segOffset )->ChannelType = CHANNEL_INIT_VAL;
	memset( ( EzChannelMgrShmPtr + segOffset )->ChannelName, 0, sizeof( ( EzChannelMgrShmPtr + segOffset )->ChannelName ) );
	strcpy( ( EzChannelMgrShmPtr + segOffset )->ChannelName, CHANNEL_INIT_NAME );
	memset( ( EzChannelMgrShmPtr + segOffset )->TaskName, 0, sizeof( ( EzChannelMgrShmPtr + segOffset )->TaskName ) );
	strcpy( ( EzChannelMgrShmPtr + segOffset )->TaskName, CHANNEL_INIT_TASK_NAME );
}

void EzChannelMgrUtil :: InitChannelPortTable()
{
	for( int i = 0; i < MaxPortChannels; i++ )
	{
		( EzChannelMgrPortShmPtr + i )->PortId = CHANNEL_INIT_VAL;
		memset( ( EzChannelMgrPortShmPtr + i )->PortName, 0, sizeof( ( EzChannelMgrPortShmPtr + i )->PortName ) );
		strcpy( ( EzChannelMgrPortShmPtr + i )->PortName, CHANNEL_INIT_NAME );
		( EzChannelMgrPortShmPtr + i )->NMessage = CHANNEL_INIT_VAL;
	}
}

void EzChannelMgrUtil :: InitChannelPortTable( int segOffset )
{
	( EzChannelMgrPortShmPtr + segOffset )->PortId = CHANNEL_INIT_VAL;
	memset( ( EzChannelMgrPortShmPtr + segOffset )->PortName, 0, sizeof( ( EzChannelMgrPortShmPtr + segOffset )->PortName ) );
	strcpy( ( EzChannelMgrPortShmPtr + segOffset )->PortName, CHANNEL_INIT_NAME );
	( EzChannelMgrPortShmPtr + segOffset )->NMessage = CHANNEL_INIT_VAL;
}

int EzChannelMgrUtil :: GetChannelCount()
{
	int ChannelCount = 0;
	struct sembuf sem_buf;
	for ( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelKeyId != CHANNEL_INIT_VAL ) )
			ChannelCount++;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return ChannelCount;
}

int EzChannelMgrUtil :: GetChannelPortCount()
{
	int ChannelCount = 0;
	struct sembuf sem_buf;
	for ( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrPortShmPtr + i )->PortId != CHANNEL_INIT_VAL ) )
			ChannelCount++;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return ChannelCount;
}

int EzChannelMgrUtil :: AddChannelTable( struct EzChannelTable chtable )
{
	int retval = -1;
	struct sembuf sem_buf;
	for ( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelKeyId == CHANNEL_INIT_VAL ) )
		{
			retval = 1;
			( EzChannelMgrShmPtr + i )->ChannelKeyId = chtable.ChannelKeyId;
			( EzChannelMgrShmPtr + i )->ChannelQid = chtable.ChannelQid;
			( EzChannelMgrShmPtr + i )->ChannelType = chtable.ChannelType;
			( EzChannelMgrShmPtr + i )->ChannelShmId = chtable.ChannelShmId;
			( EzChannelMgrShmPtr + i )->ChannelSemId = chtable.ChannelSemId;
			( EzChannelMgrShmPtr + i )->MaxSegment = chtable.MaxSegment;
			( EzChannelMgrShmPtr + i )->MaxSegmentLock = chtable.MaxSegmentLock;
			( EzChannelMgrShmPtr + i )->CurrentBufferSize = chtable.CurrentBufferSize;
			( EzChannelMgrShmPtr + i )->DropCount = chtable.DropCount;
			memset( ( EzChannelMgrShmPtr + i )->ChannelName, 0, sizeof( ( EzChannelMgrShmPtr + i )->ChannelName ) );
			strcpy( ( EzChannelMgrShmPtr + i )->ChannelName, chtable.ChannelName );
			memset( ( EzChannelMgrShmPtr + i )->TaskName, 0, sizeof( ( EzChannelMgrShmPtr + i )->TaskName ) );
			strcpy( ( EzChannelMgrShmPtr + i )->TaskName, chtable.TaskName );
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
			{
					dptr->trace(" Error in semop operation ...");
					dptr->trace(" Sys Error [%s] ", strerror( errno ) );
					return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return retval;
}

int EzChannelMgrUtil :: AddChannelPortTable( struct EzChannelPortTable chtable )
{
	int retval = -1;
	struct sembuf sem_buf;
	for ( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( !strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrPortShmPtr + i )->PortId == CHANNEL_INIT_VAL ) )
		{
			retval = 1;
			( EzChannelMgrPortShmPtr + i )->PortId = chtable.PortId;
			( EzChannelMgrPortShmPtr + i )->NMessage = 0;
			memset( ( EzChannelMgrPortShmPtr + i )->PortName, 0, sizeof( ( EzChannelMgrPortShmPtr + i )->PortName ) );
			strcpy( ( EzChannelMgrPortShmPtr + i )->PortName, chtable.PortName );
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return retval;
}

int EzChannelMgrUtil :: RemoveChannelTable( const char *ChannelName )
{
	int retval = -1;

	struct sembuf sem_buf;
	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, ChannelName ) )
		{
			InitChannelTable( i );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
		}
	}
	return retval;

}

int EzChannelMgrUtil :: RemoveChannelPortTable( const char *PortName )
{
	int retval = -1;

	struct sembuf sem_buf;
	for( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, PortName ) )
		{
			InitChannelPortTable( i );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
		}
	}
	return retval;

}

int EzChannelMgrUtil :: ListChannelTable()
{
	struct sembuf sem_buf;
	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		dptr->trace(" ChannelName [%s] ChannelKeyId[%d] ChannelQid[%d] ChannelType[%d]", ( EzChannelMgrShmPtr + i )->ChannelName, ( EzChannelMgrShmPtr + i )->ChannelKeyId, ( EzChannelMgrShmPtr + i )->ChannelQid, ( EzChannelMgrShmPtr + i )->ChannelType );
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}

int EzChannelMgrUtil :: ListChannelPortTable()
{
	struct sembuf sem_buf;
	for( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		dptr->trace(" PortName[%s] PortId[%d] NMessage[%d]", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId, ( EzChannelMgrPortShmPtr + i )->NMessage );
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}

int EzChannelMgrUtil :: CreateTaskChannel( const char *ChannelName, const char *TaskName, int ChannelKeyId )
{
	struct EzChannelTable table_ptr;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	int retval;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );
	retval = LocateTaskChannel( ChannelName, TaskName );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.ChannelName, 0, sizeof( table_ptr.ChannelName ) );
	strcpy( table_ptr.ChannelName, TaskChannelName );
	memset( table_ptr.TaskName, 0, sizeof( table_ptr.TaskName ) );
	strcpy( table_ptr.TaskName, TaskName );
	table_ptr.ChannelSemId = CHANNEL_INIT_VAL;
	table_ptr.ChannelShmId = CHANNEL_INIT_VAL;
	table_ptr.MaxSegment = 0;
	table_ptr.MaxSegmentLock = 0;
	table_ptr.CurrentBufferSize = 0;
	table_ptr.DropCount = 0;
	table_ptr.ChannelKeyId = ChannelKeyId;
	table_ptr.ChannelQid = msgget( ( key_t ) table_ptr.ChannelKeyId, IPC_CREAT | 0666 );
	if( table_ptr.ChannelQid < 0 )
	{
		dptr->trace("Error in Creating Queue for Channel[%s] SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}
	table_ptr.ChannelType = TASK_CHANNEL;
	if( AddChannelTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding ChannelName[%s] in ChannelTable...", ChannelName );
		return -1;
	}
	return 1;
}

int EzChannelMgrUtil :: createTaskChannel( const char *ChannelName, const char *TaskName )
{
	struct EzChannelTable table_ptr;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	int retval;
	struct EzChannelMsg *ChannelShmPtr;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );
	retval = LocateTaskChannel( ChannelName, TaskName );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.ChannelName, 0, sizeof( table_ptr.ChannelName ) );
	strcpy( table_ptr.ChannelName, TaskChannelName );

	memset( table_ptr.TaskName, 0, sizeof( table_ptr.TaskName ) );
	if( !strcmp( TaskName, CHANNEL_INIT_TASK_NAME ) )
		ezchannelparam.getTaskName( ChannelName, table_ptr.TaskName );

	table_ptr.ChannelType = TASK_CHANNEL;
	table_ptr.ChannelKeyId = CreateIPCKey( TaskChannelName );
	table_ptr.ChannelQid = CHANNEL_INIT_VAL;
	table_ptr.CurrentBufferSize = 0;
	table_ptr.DropCount = 0;

	table_ptr.MaxSegment = ezchannelparam.getMaxBufferSize( ChannelName );
	if( table_ptr.MaxSegment < 0 )
	{
		dptr->trace( "Error in Getting MaxBufferSize for Channel[%s]...", ChannelName );
		return -1;
	}

	dptr->trace( "MaxSegment[%d] for Channel[%s]", table_ptr.MaxSegment, ChannelName );
	table_ptr.ChannelShmId = shmget( table_ptr.ChannelKeyId, sizeof( struct EzChannelMsg ) * table_ptr.MaxSegment, IPC_CREAT | 0666 );
	if( table_ptr.ChannelShmId < 0 )
	{
		dptr->trace( "Error in Creating Shared Memory for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	table_ptr.ChannelShmId = shmget( table_ptr.ChannelKeyId, sizeof( struct EzChannelMsg ) * table_ptr.MaxSegment, IPC_CREAT | 0666 );
	if( table_ptr.ChannelShmId < 0 )
	{
		dptr->trace( "Error in Creating Shared Memory for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	ChannelShmPtr = ( struct EzChannelMsg * ) shmat( table_ptr.ChannelShmId, 0, 0 );

	if( ChannelShmPtr == NULL )
	{
		dptr->trace( "Error in Attaching Shared Memory for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < table_ptr.MaxSegment; i++ )
	{
		memset( ( ChannelShmPtr + i )->Message, 0, sizeof( ( ChannelShmPtr + i )->Message ) );
		strcpy( ( ChannelShmPtr + i )->Message, CHANNEL_FREE_SPACE );
	}

	shmdt( (char * ) ChannelShmPtr );

	table_ptr.MaxSegmentLock = ezchannelparam.getMaxSemaphoreSize( ChannelName );

	if( table_ptr.MaxSegmentLock < 0 )
			table_ptr.MaxSegmentLock = 1;
	table_ptr.ChannelSemId = semget( table_ptr.ChannelKeyId, table_ptr.MaxSegmentLock, IPC_CREAT | 0666 );
	if( table_ptr.ChannelSemId < 0 )
	{
		dptr->trace( "Error in Creating Semaphore for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
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
	for( int i = 0; i < table_ptr.MaxSegmentLock; i++ )
	{
		if( semctl( table_ptr.ChannelSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting Semahore Value for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
			return -1;
		}
	}
	if( AddChannelTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding ChannelName[%s] in ChannelTable...", ChannelName );
		return -1;
	}
	this->ObjChannelKeyId = table_ptr.ChannelKeyId;
	this->ObjChannelQid = CHANNEL_INIT_VAL;
	return 1;
}

int EzChannelMgrUtil :: CreateTaskChannel( const char *ChannelName, const char *TaskName )
{
	if( ezchannelparam.isUseSharedMemory()  && strcmp( ChannelName, "EzCommMgr" ) && strcmp( ChannelName, "EzSecurityDriver" ) )
			return createTaskChannel( ChannelName, TaskName );

	struct EzChannelTable table_ptr;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	int retval;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );
	retval = LocateTaskChannel( ChannelName, TaskName );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.ChannelName, 0, sizeof( table_ptr.ChannelName ) );
	strcpy( table_ptr.ChannelName, TaskChannelName );
	memset( table_ptr.TaskName, 0, sizeof( table_ptr.TaskName ) );
	if( !strcmp( TaskName, CHANNEL_INIT_TASK_NAME ) )
			ezchannelparam.getTaskName( ChannelName, table_ptr.TaskName );
	table_ptr.ChannelSemId = CHANNEL_INIT_VAL;
	table_ptr.ChannelShmId = CHANNEL_INIT_VAL;
	table_ptr.MaxSegment = 0;
	table_ptr.MaxSegmentLock = 0;
	table_ptr.CurrentBufferSize = 0;
	table_ptr.DropCount = 0;
	table_ptr.ChannelType = TASK_CHANNEL;
	table_ptr.ChannelKeyId = CreateIPCKey( TaskChannelName );
	table_ptr.ChannelQid = msgget( ( key_t ) table_ptr.ChannelKeyId, IPC_CREAT | 0666 );
	if( table_ptr.ChannelQid < 0 )
	{
		dptr->trace("Error in Creating Queue for Channel[%s] SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}
	this->ObjChannelKeyId = table_ptr.ChannelKeyId;
	this->ObjChannelQid = table_ptr.ChannelQid;
	table_ptr.ChannelType = TASK_CHANNEL;

	if( !strcmp( ChannelName, "EzEventMgr" ) )
	{
		table_ptr.MaxSegmentLock = 2;

		table_ptr.ChannelSemId = semget( table_ptr.ChannelKeyId, table_ptr.MaxSegmentLock, IPC_CREAT | 0666 );
		if( table_ptr.ChannelSemId < 0 )
		{
			dptr->trace( "Error in Creating Semaphore for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
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
		for( int i = 0; i < table_ptr.MaxSegmentLock; i++ )
		{
			if( semctl( table_ptr.ChannelSemId, i, SETVAL, arg ) < 0 )
			{
				dptr->trace( "Error in Setting Semahore Value for Channel[%s]...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
				return -1;
			}
		}
	}

	if( AddChannelTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding ChannelName[%s] in ChannelTable...", ChannelName );
		return -1;
	}
	return 1;
}

int EzChannelMgrUtil :: CreateTableChannel( const char *ChannelName )
{
	struct EzChannelTable table_ptr;
	char TableChannelName[ CHANNEL_NAME_SIZE + 1 ];
	int retval;

	memset( TableChannelName, 0, sizeof( TableChannelName ) );
	sprintf( TableChannelName, "TABLE_%s", ChannelName );
	retval = LocateTableChannel( TableChannelName );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.ChannelName, 0, sizeof( table_ptr.ChannelName ) );
	strcpy( table_ptr.ChannelName, TableChannelName );

	table_ptr.ChannelKeyId = CreateIPCKey( TableChannelName );
	table_ptr.ChannelQid = CHANNEL_INIT_VAL;
	table_ptr.ChannelType = TABLE_CHANNEL;
	table_ptr.ChannelSemId = CHANNEL_INIT_VAL;
	table_ptr.ChannelShmId = CHANNEL_INIT_VAL;
	table_ptr.MaxSegment = 0;
	table_ptr.MaxSegmentLock = 0;
	table_ptr.CurrentBufferSize = 0;
	table_ptr.DropCount = 0;
	if( AddChannelTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding ChannelName[%s] in ChannelTable...", ChannelName );
		return -1;
	}
	this->ObjChannelKeyId = table_ptr.ChannelKeyId;
	return 1;
}

int EzChannelMgrUtil :: CreateMemoryChannel( const char *ChannelName )
{
	struct EzChannelTable table_ptr;
	char MemoryChannelName[ CHANNEL_NAME_SIZE + 1 ];
	int retval;

	memset( MemoryChannelName, 0, sizeof( MemoryChannelName ) );
	sprintf( MemoryChannelName, "TABLE_%s", ChannelName );
	retval = LocateTableChannel( MemoryChannelName );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.ChannelName, 0, sizeof( table_ptr.ChannelName ) );
	strcpy( table_ptr.ChannelName, MemoryChannelName );

	table_ptr.ChannelKeyId = CreateIPCKey( MemoryChannelName );
	table_ptr.ChannelQid = CHANNEL_INIT_VAL;
	table_ptr.ChannelType = MEMORY_CHANNEL;
	table_ptr.ChannelSemId = CHANNEL_INIT_VAL;
	table_ptr.ChannelShmId = CHANNEL_INIT_VAL;
	table_ptr.MaxSegment = 0;
	table_ptr.MaxSegmentLock = 0;
	table_ptr.CurrentBufferSize = 0;
	table_ptr.DropCount = 0;
	if( AddChannelTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding ChannelName[%s] in ChannelTable...", ChannelName );
		return -1;
	}
	this->ObjChannelKeyId = table_ptr.ChannelKeyId;
	return 1;
}

int EzChannelMgrUtil :: CreatePortChannel( const char *PortName )
{
	struct EzChannelPortTable table_ptr;
	int retval;

	retval = LocatePortChannel( PortName );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.PortName, 0, sizeof( table_ptr.PortName ) );
	strcpy( table_ptr.PortName, PortName );
	table_ptr.PortId = CHANNEL_INIT_VAL;
	table_ptr.NMessage = 0;

	if( AddChannelPortTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding PortName[%s] in ChannelPortTable....", table_ptr.PortName );
		return -1;
	}
	return 1;
}

int EzChannelMgrUtil :: CreatePortChannel( const char *PortName, int PortId )
{
	struct EzChannelPortTable table_ptr;
	int retval;

	retval = LocatePortChannel( PortName, PortId );
	if( retval >= 0 )
		return retval;

	memset( table_ptr.PortName, 0, sizeof( table_ptr.PortName ) );
	strcpy( table_ptr.PortName, PortName );
	table_ptr.PortId = PortId;
	table_ptr.NMessage = 0;

	if( AddChannelPortTable( table_ptr ) < 0 )
	{
		dptr->trace( "Error in Adding PortName[%s] in ChannelPortTable....", table_ptr.PortName );
		return -1;
	}
	return 1;
}

int EzChannelMgrUtil :: LocateTaskChannel( const char *ChannelName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
		{
			this->ObjChannelQid = ( EzChannelMgrShmPtr + i )->ChannelQid;
			this->ObjChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			   	return -1;
            		}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        	}
	}
	return retval;
}

int EzChannelMgrUtil :: LocateTaskChannel( const char *ChannelName, const char *TaskName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->TaskName, CHANNEL_INIT_TASK_NAME ) )
			{
				memset( ( EzChannelMgrShmPtr + i )->TaskName, 0, sizeof( ( EzChannelMgrShmPtr + i )->TaskName ) );
				strcpy( ( EzChannelMgrShmPtr + i )->TaskName, TaskName );
			}
			this->ObjChannelQid = ( EzChannelMgrShmPtr + i )->ChannelQid;
			this->ObjChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			   	return -1;
           	}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        }
	}
	return retval;
}

int EzChannelMgrUtil :: LocateTableChannel( const char *ChannelName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char TableChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TableChannelName, 0, sizeof( TableChannelName ) );
	sprintf( TableChannelName, "TABLE_%s", ChannelName );

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TableChannelName ) )
		{
			this->ObjChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			   	return -1;
            		}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        	}
	}
	return retval;
}

int EzChannelMgrUtil :: LocateMemoryChannel( const char *ChannelName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char MemoryChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( MemoryChannelName, 0, sizeof( MemoryChannelName ) );
	sprintf( MemoryChannelName, "TABLE_%s", ChannelName );

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, MemoryChannelName ) )
		{
			this->ObjChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			   	return -1;
            		}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        	}
	}
	return retval;
}

int EzChannelMgrUtil :: LocatePortChannel( const char *PortName, int PortId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, PortName ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			( EzChannelMgrPortShmPtr + i )->PortId = PortId;
			if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			   	return -1;
            		}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        	}
	}
	return retval;
}

int EzChannelMgrUtil :: LocatePortChannel( const char *PortName )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, PortName ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			   	return -1;
            		}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        	}
	}
	return retval;
}

int EzChannelMgrUtil :: GetChannelKeyId()
{
	return ( this->ObjChannelKeyId );
}

int EzChannelMgrUtil :: GetChannelQid()
{
	return ( this->ObjChannelQid );
}

