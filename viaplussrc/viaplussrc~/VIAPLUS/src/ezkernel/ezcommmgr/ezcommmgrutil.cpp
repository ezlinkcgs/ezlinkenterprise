#include <ezkernel/ezcommmgrutil.h>

EzCommMgrUtil :: EzCommMgrUtil()
{
	NewTaskOffset = 0;
}

EzCommMgrUtil :: ~EzCommMgrUtil()
{
}

int EzCommMgrUtil :: InitEzCommMgrUtil( EzDebugUtil *dptr, int MaxPort, int OrgKey )
{
	int EzChannelMgrKey, EzChannelMgrQid;
	struct EzChannelMgrQMsg chqmsg;
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];

	NewTaskOffset = 0;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}
	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "PORT#ACKREQ", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching PORT#ACKREQ in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	cfgutil.cfg_close();

	if( !strcasecmp( CfgVal, "Yes" ) )
			PortAckReq = true;
	else
			PortAckReq = false;

	this->dptr = dptr;
	this->MaxPort = MaxPort;
	EzChannelMgrKey = OrgKey + 2;

	this->EzTaskMgrChildKey = OrgKey - 1;

	EzTaskMgrChildSemid = semget ( EzTaskMgrChildKey, 4, IPC_CREAT | 0666 );

	if( EzTaskMgrChildSemid < 0 )
	{
		dptr->trace( "Error in Creating EzTaskMgrChild Semaphore...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	if( semctl( EzTaskMgrChildSemid, 2, SETVAL, arg ) < 0 )
			return -1;

	EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );
	if( EzChannelMgrQid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	memset( &chqmsg, 0, sizeof( chqmsg ) );
	chqmsg.msgtype = 1;
	strcpy( chqmsg.chmgrmsg.ChannelName, "EzCommMgr" );
	chqmsg.chmgrmsg.Command = CREATE_TASK_CHANNEL;
	chqmsg.chmgrmsg.NotificationId = getpid();

	if( msgsnd( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
	{
		dptr->trace( "Error in Sending Channel Creation Message to EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( &chqmsg, 0, sizeof( chqmsg ) );
	if( msgrcv( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), getpid(), 0 ) < 0 )
	{
		dptr->trace( "Error in Receiving Channel Creation Message to EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( chqmsg.chmgrmsg.Response < 0 )
	{
		dptr->trace( "Error in Creating Channel[%s]", "EzCommMgr" );
		return -1;
	}

	EzCommMgrKey = chqmsg.chmgrmsg.ChannelKeyId;
	dptr->trace( "EzCommMgr Key Located with KeyId[%d]", EzCommMgrKey );
	return 1;
}

int EzCommMgrUtil :: WaitForParent()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 2;
	sem_buf.sem_op = -3;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzCommMgrUtil :: InvokeChild()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 2;
	sem_buf.sem_op = -2;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	sem_buf.sem_op = 3;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzCommMgrUtil :: WaitForChild()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 2;
	sem_buf.sem_op = -4;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	sem_buf.sem_op = 2;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzCommMgrUtil :: InvokeParent()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 2;
	sem_buf.sem_op = 4;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzCommMgrUtil :: CreateEzCommMgrQueue()
{
	EzCommMgrQid = msgget( ( key_t ) EzCommMgrKey, IPC_CREAT | 0666 );
	if( EzCommMgrQid < 0 )
	{
		dptr->trace("Error in Creating EzCommMgr queue ...Sys Err [%s] ", strerror( errno ) );
		return -1;
	}

	return 1;
}

int EzCommMgrUtil :: GetEzCommMgrQid()
{
	return EzCommMgrQid;
}

int EzCommMgrUtil :: WaitForPort( int PortId )
{
	if( !PortAckReq )
		return 1;
	struct EzCommAckQMsg ackqmsg;
	memset( &ackqmsg, 0, sizeof( ackqmsg ) );
	dptr->trace( "Waiting for Driver Ack Message from PortId[%d]", PortId );

	while( 1 )
	{
		if( msgrcv( EzCommMgrQid, &ackqmsg, sizeof( ackqmsg ) - sizeof( long ), PortId, 0 ) < 0 )
		{
			if( errno == EIDRM )
			{
				if( CreateEzCommMgrQueue() < 0 )
					return -1;
			}
			else if( errno == EINTR )
			{
				dptr->trace( "Interuppted while Waiting for PortId[%d] to Start", PortId );
				continue;
			}
			else
				return -1;
		}
		else
			break;
	}
	dptr->trace( "ackqmsg.ackmsg.Response[%d]", ackqmsg.ackmsg.Response );
	return ackqmsg.ackmsg.Response;
}

int EzCommMgrUtil :: SendCommInitErr( int PortId )
{
	if( !PortAckReq )
		return 1;
	struct EzCommAckQMsg ackqmsg;
	memset( &ackqmsg, 0, sizeof( ackqmsg ) );
	ackqmsg.msgtype = PortId;
	ackqmsg.ackmsg.Response = -1;
	if( msgsnd( EzCommMgrQid, &ackqmsg, sizeof( ackqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
	{
		if( errno == EIDRM )
		{
			if( CreateEzCommMgrQueue() < 0 )
				return -1;
			else
			{
				if( msgsnd( EzCommMgrQid, &ackqmsg, sizeof( ackqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					return -1;
			}
		}
		else
			return -1;
	}
	return 1;
}


int EzCommMgrUtil :: LocateEzCommMgrSharedMemory()
{
	EzCommMgrShmid = shmget( ( key_t ) EzCommMgrKey, 0, IPC_CREAT | 0666 );
	if( EzCommMgrShmid < 0 )
	{
		dptr->trace(" Error in Creating EzCommMgr Shared Memory ...Sys Err [%s] ", strerror( errno ) );
		return -1;
	}
	EzCommMgrShmPtr = ( struct EzCommTable * ) shmat( EzCommMgrShmid, 0, 0 );
	if( EzCommMgrShmPtr == NULL )
	{
		dptr->trace(" Error in attaching EzCommMgr Shared Memory ...Sys Err [%s] ", strerror( errno ) );
		return -1;
	}
	EzCommMgrSemid = semget( ( key_t ) EzCommMgrKey, 0, IPC_CREAT | 0666 );
	if( EzCommMgrSemid < 0 )
	{
		dptr->trace(" Error in Creating EzCommMgr Semaphore ...Sys Err [%s] ", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzCommMgrUtil :: CreateEzCommMgrSharedMemory()
{
	struct shmid_ds shmdsptr;
	EzCommMgrShmid = shmget( ( key_t ) EzCommMgrKey, MaxPort * sizeof( struct EzCommTable ), IPC_CREAT | IPC_EXCL | 0666 );
	dptr->trace("test1");
	if( EzCommMgrShmid < 0 )
	{
		if( errno != EEXIST )
		{
			dptr->trace("Error in Creating EzCommMgr Shared Memory Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		EzCommMgrShmid = shmget ( ( key_t ) EzCommMgrKey, 0, IPC_CREAT | 0666 );
		if( EzCommMgrShmid < 0 )
		{
			dptr->trace("Error in Creating EzCommMgr Shared Memory Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		shmctl( EzCommMgrShmid, IPC_RMID, &shmdsptr );
		EzCommMgrShmid = shmget( ( key_t ) EzCommMgrKey, MaxPort * sizeof( struct EzCommTable ), IPC_CREAT | IPC_EXCL | 0666 );
		if( EzCommMgrShmid < 0 )
		{
			dptr->trace("Error in Creating EzCommMgr Shared Memory Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	EzCommMgrShmPtr = ( struct EzCommTable * ) shmat( EzCommMgrShmid, 0, 0 );
	if( EzCommMgrShmPtr == NULL )
	{
		dptr->trace(" Error in attaching EzCommMgr Shared Memory ...Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	EzCommMgrSemid = semget( ( key_t ) EzCommMgrKey, MaxPort, IPC_CREAT | 0666 );
	if( EzCommMgrSemid < 0 )
	{
		dptr->trace(" Error in Creating EzCommMgr Semaphore ...Sys Err [%s] ", strerror( errno ) );
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
	for( int i = 0; i < MaxPort; i++ )
	{
		if( semctl( EzCommMgrSemid, i, SETVAL, arg ) < 0 )
			return -1;
	}
	dptr->trace("test4");

	return 1;
}

void EzCommMgrUtil :: InitCommTable()
{
	for( int i = 0; i < MaxPort; i++ )
	{
		memset( ( EzCommMgrShmPtr + i )->PortName, 0, sizeof( ( EzCommMgrShmPtr + i )->PortName ) );
		strcpy( ( EzCommMgrShmPtr + i )->PortName, PORT_INIT_NAME );
		memset( ( EzCommMgrShmPtr + i )->Protocol, 0, sizeof( ( EzCommMgrShmPtr + i )->Protocol ) );
		strcpy( ( EzCommMgrShmPtr + i )->Protocol, PORT_INIT_NAME );
		memset( ( EzCommMgrShmPtr + i )->IpAddress, 0, sizeof( ( EzCommMgrShmPtr + i )->IpAddress ) );
		strcpy( ( EzCommMgrShmPtr + i )->IpAddress, PORT_INIT_NAME );
		( EzCommMgrShmPtr + i )->PortNo  = PORT_INIT_VAL;
		( EzCommMgrShmPtr + i )->PortId = PORT_INIT_VAL;
		( EzCommMgrShmPtr + i )->ApplType = PORT_INIT_VAL;
		( EzCommMgrShmPtr + i )->PortStatus = PORT_INIT_VAL;
	}
}

void EzCommMgrUtil :: InitCommTable( int segOffset )
{
	memset( ( EzCommMgrShmPtr + segOffset )->PortName, 0, sizeof( ( EzCommMgrShmPtr + segOffset )->PortName ) );
	strcpy( ( EzCommMgrShmPtr + segOffset )->PortName, PORT_INIT_NAME );
	memset( ( EzCommMgrShmPtr + segOffset )->Protocol, 0, sizeof( ( EzCommMgrShmPtr + segOffset )->Protocol ) );
	strcpy( ( EzCommMgrShmPtr + segOffset )->Protocol, PORT_INIT_NAME );
	memset( ( EzCommMgrShmPtr + segOffset )->IpAddress, 0, sizeof( ( EzCommMgrShmPtr + segOffset )->IpAddress ) );
	strcpy( ( EzCommMgrShmPtr + segOffset )->IpAddress, PORT_INIT_NAME );
	( EzCommMgrShmPtr + segOffset )->PortNo = PORT_INIT_VAL;
	( EzCommMgrShmPtr + segOffset )->PortId = PORT_INIT_VAL;
	( EzCommMgrShmPtr + segOffset )->ApplType = PORT_INIT_VAL;
	( EzCommMgrShmPtr + segOffset )->PortStatus = PORT_INIT_VAL;
}

int EzCommMgrUtil :: GetNPorts()
{
	int PortCount = 0;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( strcmp( ( EzCommMgrShmPtr + i )->PortName, PORT_INIT_NAME ) )
			PortCount++;
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return PortCount;
}

int EzCommMgrUtil :: AddCommTable( const char *PortName, int PortId )
{
	if( !strcmp( ( EzCommMgrShmPtr + NewTaskOffset )->PortName, PORT_INIT_NAME ) )
	{
		memset( ( EzCommMgrShmPtr + NewTaskOffset )->PortName, 0, sizeof( ( EzCommMgrShmPtr + NewTaskOffset )->PortName ) );
		strcpy( ( EzCommMgrShmPtr + NewTaskOffset )->PortName, PortName );
		( EzCommMgrShmPtr + NewTaskOffset )->PortId = PortId;
		NewTaskOffset++;
	}
	else
	{
		for( int i = 0; i < MaxPort; i++ )
		{
			sem_buf.sem_flg = 0;
			sem_buf.sem_num = i;
			sem_buf.sem_op = -2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PORT_INIT_NAME ) )
			{
				memset( ( EzCommMgrShmPtr + i )->PortName, 0, sizeof( ( EzCommMgrShmPtr + i )->PortName ) );
				strcpy( ( EzCommMgrShmPtr + i )->PortName, PortName );
				( EzCommMgrShmPtr + i )->PortId = PortId;
				sem_buf.sem_op = 2;
				if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace(" Error in semop operation ...");
					dptr->trace(" Sys Error [%s] ", strerror( errno ) );
					return -1;
				}
				break;
			}
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
		}
	}
	return 1;
}

int EzCommMgrUtil :: RemoveCommTable( const char *PortName )
{
	for ( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PortName ) )
		{
			InitCommTable( i );
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace("Error in semop operation ...");
				dptr->trace("Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace("Error in semop operation ...");
			dptr->trace("Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}

int EzCommMgrUtil :: IsPortInitialized( int PortId )
{
	int retval = 0;

	for ( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return 0;
		}
		if( ( EzCommMgrShmPtr + i )->PortId == PortId )
		{
			if( ( EzCommMgrShmPtr + i )->PortStatus == PORT_INIT_VAL )
				retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace("Error in semop operation ...");
				dptr->trace("Sys Error [%s] ", strerror( errno ) );
				return 0;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace("Error in semop operation ...");
			dptr->trace("Sys Error [%s] ", strerror( errno ) );
			return 0;
		}
	}
	return retval;
}


int EzCommMgrUtil :: RemoveCommTable( int PortId )
{
	for ( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( EzCommMgrShmPtr + i )->PortId == PortId )
		{
			InitCommTable( i );
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace("Error in semop operation ...");
				dptr->trace("Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace("Error in semop operation ...");
			dptr->trace("Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}

int EzCommMgrUtil :: LocateCommTable( int PortId, char *PortName )
{
	int retval = -1;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( EzCommMgrShmPtr + i )->PortId == PortId )
		{
			retval = 1;
			strcpy( PortName, ( EzCommMgrShmPtr + i )->PortName );
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return retval;
}

int EzCommMgrUtil :: IsPortStopped( const char *PortName )
{
	int PortStatus = 0;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PortName ) )
		{
			if( ( EzCommMgrShmPtr + i )->PortStatus == PORT_STOPPED )
				PortStatus = 1;
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return PortStatus;
}

int EzCommMgrUtil :: LocateCommTable( const char *PortName )
{
	int PortId = -1;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PortName ) )
		{
			PortId = ( EzCommMgrShmPtr + i )->PortId;
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return PortId;
}

int EzCommMgrUtil :: UpdatePort( const char *PortName, int PortStatus )
{
	int retval = -1;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PortName ) )
		{
			retval = 1;
			( EzCommMgrShmPtr + i )->PortStatus = PortStatus;
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return retval;
}

int EzCommMgrUtil :: UpdatePortId( const char *PortName, int PortId )
{
	int retval = -1;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PortName ) )
		{
			retval = 1;
			( EzCommMgrShmPtr + i )->PortId = PortId;
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return retval;
}

int EzCommMgrUtil :: GetPortStatus( const char *PortName )
{
	int PortStatus = -1;
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzCommMgrShmPtr + i )->PortName, PortName ) )
		{
			PortStatus = ( EzCommMgrShmPtr + i )->PortStatus;
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace(" Error in semop operation ...");
				dptr->trace(" Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return PortStatus;
}

int EzCommMgrUtil :: ListCommTable()
{
	dptr->trace("---------------------------");
	dptr->trace(" PORT NAME PORTID APPTYPE IPADDRESS PORTNAME STATUS ");
	dptr->trace("---------------------------");
	for( int i = 0; i < MaxPort; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if ( ( strcmp( ( EzCommMgrShmPtr + i )->PortName, PORT_INIT_NAME ) ) && ( ( EzCommMgrShmPtr + i )->PortId != PORT_INIT_VAL ) )
		dptr->trace("[%s] [%d] [%d] [%s] [%d] [%d]", ( EzCommMgrShmPtr + i )->PortName, ( EzCommMgrShmPtr + i )->PortId, ( EzCommMgrShmPtr + i )->ApplType, ( EzCommMgrShmPtr + i )->IpAddress, ( EzCommMgrShmPtr + i )->PortNo, ( EzCommMgrShmPtr + i )->PortStatus );
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	dptr->trace("-----------------------------------------------------");
	return 1;
}

