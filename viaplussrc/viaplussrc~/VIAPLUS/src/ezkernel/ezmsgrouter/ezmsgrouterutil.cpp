#include <ezkernel/ezmsgrouterutil.h>

int EzMsgRouterUtil :: InitEzMsgRouterUtil( EzDebugUtil *dptr, EzChannelParam *channelparam, bool MsgRouterLockFlag )
{
	this->dptr = dptr;
	this->MsgRouterLockFlag = MsgRouterLockFlag;
	this->channelparam = channelparam;

	EzChannelMgrKey = channelparam->getOrgKey() + 2;
	EzChannelMgrPortKey = channelparam->getOrgKey() + 3;
	MaxChannels = channelparam->getMaxChannels();
	MaxPortChannels = channelparam->getMaxPortChannels();

	if( channelparam->isUseSharedMemory() )
	{
		EzMsgRouterMaxBuffer = channelparam->getMaxBufferSize( "EzMsgRouter" );
		if( EzMsgRouterMaxBuffer < 0 )
		{
			dptr->trace( "Error in Getting MaxBufferSize for EzMsgRouter" );
			return -1;
		}
		if( initMsgRouterTable() < 0 )
		{
			dptr->trace( "Error in Intializing MsgRouter Table...." );
			return -1;
		}
	}

	EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );
	if( EzChannelMgrQid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortQid = msgget( ( key_t ) EzChannelMgrPortKey, IPC_CREAT | 0666 );
	if( EzChannelMgrPortQid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgrPort Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrShmid < 0 )
	{
		dptr->trace( "Error in Creating EzChannel Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrShmPtr = ( struct EzChannelTable * ) shmat( EzChannelMgrShmid, 0, 0 );

	if( EzChannelMgrShmPtr == NULL )
	{
		dptr->trace( "Error in Attaching EzChannel Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrSemid = semget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrSemid < 0 )
	{
		dptr->trace( "Error in Creating EzChannel Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortShmid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( MsgRouterLockFlag )
		EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, 0 );
	else
		EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, SHM_RDONLY );

	if( EzChannelMgrPortShmPtr == NULL )
	{
		dptr->trace( "Error in Attaching EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( MsgRouterLockFlag )
	{
		EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
		if( EzChannelMgrPortSemid < 0 )
		{
			dptr->trace( "Error in Creating EzChannelPort Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzMsgRouterUtil :: CreateEzChannelMgrPortQueue()
{
	EzChannelMgrPortQid = msgget( ( key_t ) EzChannelMgrPortKey, IPC_CREAT | 0666 );
	if( EzChannelMgrPortQid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgrPort Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMsgRouterUtil :: initMsgRouterSemaphore()
{
	union semun arg;
	struct sembuf sem_buf;

	if( semctl( EzMsgRouterSemid, 0, GETVAL ) > 3 )
	{
		dptr->trace( "Channel[%s] Semaphore value is > 3...Resetting to 3", "EzMsgRouter" );
		arg.val = 3;
		semctl( EzMsgRouterSemid, 0, SETVAL, arg );
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op1..SysErr[%s] ErrNo[%d]", "EzMsgRouter", strerror( errno ), errno );
		return -1;
	}

	if( semctl( EzMsgRouterSemid, 0, GETVAL ) == 0 )
	{
		sem_buf.sem_num = 0;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = 1;

		if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Channel[%s] Semaphore..Op2..SysErr[%s] ErrNo[%d]", "EzMsgRouter", strerror( errno ), errno );
			return -1;
		}
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_op = -1;

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op3..SysErr[%s] ErrNo[%d]", "EzMsgRouter", strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op4..SysErr[%s] ErrNo[%d]", "EzMsgRouter", strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_op = -1;

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op5..SysErr[%s] ErrNo[%d]", "EzMsgRouter", strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 2;

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op6..SysErr[%s] ErrNo[%d]", "EzMsgRouter", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMsgRouterUtil :: createEzMsgRouterChannel()
{
	int retval;

	retval = locateTaskChannel( "EzMsgRouter",  &EzMsgRouterKey );

	if( retval < 0 )
	{
		EzMsgRouterKey = CreateChannelId( dptr, "EzMsgRouter" );
		if( EzMsgRouterKey < 0 )
		{
			dptr->trace( "Error in Creating EzMsgRouter Task Memory..." );
			return -1;
		}
		retval = locateTaskChannel( "EzMsgRouter",  &EzMsgRouterKey );
		if( retval < 0 )
		{
			dptr->trace( "Error in Locating EzMsgRouter Task Memory..." );
			return -1;
		}
	}

	EzMsgRouterShmid = shmget( ( key_t ) EzMsgRouterKey, 0, IPC_CREAT | 0666 );

	if( EzMsgRouterShmid < 0 )
	{
		dptr->trace( "Error in Creating EzMsgRouter Shared Memory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzMsgRouterSemid = semget( ( key_t ) EzMsgRouterKey, 0, IPC_CREAT | 0666 );

	if( EzMsgRouterSemid < 0 )
	{
		dptr->trace( "Error in Creating EzMsgRouter SharedMemory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzMsgRouterShmPtr = ( struct EzChannelMsg * ) shmat( EzMsgRouterShmid, 0, 0 );

	if( EzMsgRouterShmPtr == NULL )
	{
		dptr->trace( "Error in Attaching EzMsgRouter Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	/*
	if( initMsgRouterSemaphore() < 0 )
	{
		dptr->trace( "Error in Initializing EzMsgRouter Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	*/
	return 1;
}

int EzMsgRouterUtil :: initChannelSemaphore( const char *ChannelName, int ChannelSemid )
{
	union semun arg;
	struct sembuf sem_buf;

	if( semctl( ChannelSemid, 0, GETVAL ) > 3 )
	{
		dptr->trace( "Channel[%s] Semaphore value is > 3...Resetting to 3", ChannelName );
		arg.val = 3;
		semctl( ChannelSemid, 0, SETVAL, arg );
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op1..SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	if( semctl( ChannelSemid, 0, GETVAL ) == 0 )
	{
		sem_buf.sem_num = 0;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = 1;

		if( semop( ChannelSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Channel[%s] Semaphore..Op2..SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
			return -1;
		}
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_op = -1;

	if( semop( ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op3..SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;

	if( semop( ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op4..SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_op = -1;

	if( semop( ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op5..SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 2;

	if( semop( ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Channel[%s] Semaphore..Op6..SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMsgRouterUtil :: createTaskChannel( const char *ChannelName, int MaxBuffer )
{
	int retval = -1;
	for( int i = 0; i < MaxChannels; i++ )
	{
		if( !strcmp( ( msgroutertable_ptr + i )->ChannelName, CHANNEL_INIT_NAME ) )
		{
			retval = locateTaskChannel( ChannelName,  &( msgroutertable_ptr + i )->ChannelKeyId );

			if( retval < 0 )
			{
				( msgroutertable_ptr + i )->ChannelKeyId = CreateChannelId( dptr, ChannelName );
				if( ( msgroutertable_ptr + i )->ChannelKeyId < 0 )
				{
					dptr->trace( "Error in Creating [%s] Task Memory...", ChannelName );
					return -1;
				}
			}

			( msgroutertable_ptr + i )->ChannelShmid = shmget( ( key_t ) ( msgroutertable_ptr + i )->ChannelKeyId, 0, IPC_CREAT | 0666 );

			if( ( msgroutertable_ptr + i )->ChannelShmid < 0 )
			{
				dptr->trace( "Error in Creating [%s] Shared Memory...SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
				return -1;
			}

			( msgroutertable_ptr + i )->ChannelSemid = semget( ( key_t ) ( msgroutertable_ptr + i )->ChannelKeyId, 0, IPC_CREAT | 0666 );

			if( ( msgroutertable_ptr + i )->ChannelSemid < 0 )
			{
				dptr->trace( "Error in Creating [%s] Semaphore SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
				return -1;
			}

			( msgroutertable_ptr + i )->ChannelShmPtr = ( struct EzChannelMsg * ) shmat( ( msgroutertable_ptr + i )->ChannelShmid, 0, 0 );

			if( ( msgroutertable_ptr + i )->ChannelShmPtr == NULL )
			{
				dptr->trace( "Error in Attaching [%s] SharedMemory SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
				return -1;
			}

			/*
			if( initChannelSemaphore( ChannelName, ( msgroutertable_ptr + i )->ChannelSemid ) < 0 )
			{
				dptr->trace( "Error in Initializing [%s] Semaphore SysErr[%s] ErrNo[%d]", ChannelName, strerror( errno ), errno );
				return -1;
			}
			*/
			strcpy( ( msgroutertable_ptr + i )->ChannelName, ChannelName );
			( msgroutertable_ptr + i )->MaxBuffer = MaxBuffer;
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzMsgRouterUtil :: writeTaskChannel( struct EzMsgRouterTable *msgrouter_rec, struct EzChannelMsg RequestMsg )
{
	struct sembuf sem_buf;
	union semun arg;

	int retval = -1;

	if( RequestMsg.MsgSize <= 0 )
	{
		dptr->trace( "Fatal:Error in Writing Messsage to Channel[%s]", msgrouter_rec->ChannelName );
		dptr->trace( "MsgSize[%d] < 1", RequestMsg.MsgSize );
		return -1;
	}

	if( RequestMsg.MsgSize >= CHANNEL_MSG_SIZE )
	{
		dptr->trace( "Fatal:Error in Writing Messsage to Channel[%s]", msgrouter_rec->ChannelName );
		dptr->trace( "MsgSize[%d]>=MaxSize[%d]", RequestMsg.MsgSize, CHANNEL_MSG_SIZE );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( msgrouter_rec->ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop on [%s] Semaphore with Semid[%d]....SysErr[%s] ErrNo[%d]", msgrouter_rec->ChannelName, msgrouter_rec->ChannelSemid, strerror( errno ), errno );
		return -1;
	}

	if( semctl( msgrouter_rec->ChannelSemid, 0, GETVAL ) > 1 )
	{
		arg.val = 1;
		semctl( msgrouter_rec->ChannelSemid, 0, SETVAL, arg );
	}

	for( int i = 0; i < msgrouter_rec->MaxBuffer; i++ )
	{
		if( !strcmp( ( msgrouter_rec->ChannelShmPtr + i )->Message, CHANNEL_FREE_SPACE ) )
		{
			retval = 1;
			memset( msgrouter_rec->ChannelShmPtr + i, 0, sizeof( struct EzChannelMsg ) );
			memcpy( msgrouter_rec->ChannelShmPtr + i, &RequestMsg, sizeof( struct EzChannelMsg ) );
			break;
		}
	}

	if( retval < 0 )
	{
		if( incrementChannelDropCount( msgrouter_rec->ChannelName ) < 0 )
			dptr->trace( "Error in Incrementing ChannelDropCount for Channel[%s]", msgrouter_rec->ChannelName );
		sem_buf.sem_op = 2;
	}
	else
	{
		if( semctl( msgrouter_rec->ChannelSemid, 0, GETVAL ) == 0 )
			sem_buf.sem_op = 3;
		else
			sem_buf.sem_op = 2;
		if( incrementChannelBufferSize( msgrouter_rec->ChannelName ) < 0 )
			dptr->trace( "Error in Incrementing Channel[%s] BufferSize...", msgrouter_rec->ChannelName );
	}

	if( semop( msgrouter_rec->ChannelSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop on [%s] Semaphore with Semid[%d]....SysErr[%s] ErrNo[%d]", msgrouter_rec->ChannelName, msgrouter_rec->ChannelSemid, strerror( errno ), errno );
		return -1;
	}
	return retval;
}

int EzMsgRouterUtil :: readFromMsgRouterChannel( struct EzChannelMsg *RequestMsg )
{
	struct sembuf sem_buf;
	union semun arg;

	while( 1 )
	{
		sem_buf.sem_num = 0;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -3;

		if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop on EzMsgRouter Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( EzMsgRouterShmPtr->Message, CHANNEL_FREE_SPACE ) )
		{
			sem_buf.sem_num = 0;
			sem_buf.sem_flg = 0;
			sem_buf.sem_op = 2;

			if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop on EzMsgRouter Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			continue;
		}
		break;
	}

	memcpy( RequestMsg, EzMsgRouterShmPtr, sizeof( struct EzChannelMsg ) );
	memset( EzMsgRouterShmPtr, 0, sizeof( struct EzChannelMsg ) );
	memcpy( EzMsgRouterShmPtr, EzMsgRouterShmPtr + 1, sizeof( struct EzChannelMsg ) * ( EzMsgRouterMaxBuffer - 1 ) );
	memset( EzMsgRouterShmPtr + EzMsgRouterMaxBuffer - 1, 0, sizeof( struct EzChannelMsg ) );
	strcpy( ( EzMsgRouterShmPtr + EzMsgRouterMaxBuffer - 1 )->Message, CHANNEL_FREE_SPACE );

	if( !getMsgRouterDropCount() )
	{
		arg.val = 0;
		semctl( EzMsgRouterSemid, 2, SETVAL, arg );
	}
	else
	{
		sem_buf.sem_num = 2;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = 1;
		if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop on EzMsgRouter Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	if( decrementMsgRouterBufferSize() < 0 )
		dptr->trace( "Error in Decrementing MsgRouter BufferSize...." );

	if( !strcmp( EzMsgRouterShmPtr->Message, CHANNEL_FREE_SPACE ) )
	{
		arg.val = 0;
		semctl( EzMsgRouterSemid, 2, SETVAL, arg );
		sem_buf.sem_num = 0;
		sem_buf.sem_op = 2;
	}
	else
	{
		sem_buf.sem_num = 0;
		sem_buf.sem_op = 3;
	}

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop on EzMsgRouter Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMsgRouterUtil :: CreateEzMsgRouterChannel()
{
	int retval, TaskChannelCount, MaxBuffer;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];

	if( channelparam->isUseSharedMemory() )
	{
		if( createEzMsgRouterChannel() < 0 )
			return -1;

		TaskChannelCount = channelparam->getCurrentChannelCount();

		for( int i = 0; i < TaskChannelCount; i++ )
		{
			memset( ChannelName, 0, sizeof( ChannelName ) );
			if( channelparam->getNextChannelName( ChannelName, &MaxBuffer, i + 1 ) < 0 )
			{
				dptr->trace( "Error in Getting %dth ChannelName", i + 1 );
				return -1;
			}
			if( strcmp( ChannelName, "EzMsgRouter" ) )
			{
				retval = createTaskChannel( ChannelName, MaxBuffer );
				if( retval < 0 )
					return retval;
			}
		}
		return 1;
	}

	struct EzChannelMgrQMsg chqmsg;
	memset( &chqmsg, 0, sizeof( chqmsg ) );
	chqmsg.msgtype = 1;
	strcpy( chqmsg.chmgrmsg.ChannelName, "EzMsgRouter" );
	strcpy( chqmsg.chmgrmsg.TaskName, "EzMsgRouter" );
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
		dptr->trace( "Error in Creating Channel[%s]", "EzMsgRouter" );
		return -1;
	}

	dptr->trace( "Channel[%s] Created with ChannelKeyId[%d] ChannelQid[%d]", chqmsg.chmgrmsg.ChannelName, chqmsg.chmgrmsg.ChannelKeyId, chqmsg.chmgrmsg.ChannelQid );

	EzMsgRouterQid = chqmsg.chmgrmsg.ChannelQid;
	EzMsgRouterKey = chqmsg.chmgrmsg.ChannelKeyId;

	EzMsgRouterSemid = semget( ( key_t ) EzMsgRouterKey, 1, IPC_CREAT | 0666 );

	if( EzMsgRouterSemid < 0 )
	{
		dptr->trace( "Error in Creating EzMsgRouter Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMsgRouterUtil :: GetEzMsgRouterQid()
{
	return EzMsgRouterQid;
}

int EzMsgRouterUtil :: GetEzMsgRouterKey()
{
	return EzMsgRouterKey;
}

int EzMsgRouterUtil :: GetEzPortQid()
{
	return EzChannelMgrPortQid;
}

int EzMsgRouterUtil :: GetEzMsgRouterSemVal()
{
	return ( semctl( EzMsgRouterSemid, 0, GETVAL, 0 ) );
}

int EzMsgRouterUtil :: SetEzMsgRouterSemaphore()
{
	struct sembuf sem_buf;

	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_num = 1;
	sem_buf.sem_op = 3;

	if( semop( EzMsgRouterSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in EzMsgRouter Semop SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMsgRouterUtil :: locateTaskChannel( const char *ChannelName, int *ChannelKeyId )
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	for( int i = 0; i < MaxChannels; i++ )
	{
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
		{
			*ChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			if( !strcmp( ChannelName, "EzMsgRouter" ) )
				EzMsgRouterChannelOffset = i;
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzMsgRouterUtil :: getMsgRouterBufferSize()
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct sembuf sem_buf;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", "EzMsgRouter" );

	if( !strcmp( TaskChannelName, ( EzChannelMgrShmPtr + EzMsgRouterChannelOffset )->ChannelName ) )
	{
		sem_buf.sem_num = EzMsgRouterChannelOffset;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		retval = ( EzChannelMgrShmPtr + EzMsgRouterChannelOffset )->CurrentBufferSize;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	if( retval < 0 )
	{
		for( int i = 0; i < MaxChannels; i++ )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
			{
				sem_buf.sem_num = i;
				sem_buf.sem_flg = 0;
				sem_buf.sem_op = -2;

				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				retval = ( EzChannelMgrShmPtr + i )->CurrentBufferSize;
				EzMsgRouterChannelOffset = i;
				sem_buf.sem_op = 2;
				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				break;
			}
		}
	}
	return retval;
}

int EzMsgRouterUtil :: getMsgRouterDropCount()
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct sembuf sem_buf;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", "EzMsgRouter" );

	if( !strcmp( TaskChannelName, ( EzChannelMgrShmPtr + EzMsgRouterChannelOffset )->ChannelName ) )
	{
		sem_buf.sem_num = EzMsgRouterChannelOffset;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		retval = ( EzChannelMgrShmPtr + EzMsgRouterChannelOffset )->DropCount;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	if( retval < 0 )
	{
		for( int i = 0; i < MaxChannels; i++ )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
			{
				sem_buf.sem_num = i;
				sem_buf.sem_flg = 0;
				sem_buf.sem_op = -2;

				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				retval = ( EzChannelMgrShmPtr + i )->DropCount;
				EzMsgRouterChannelOffset = i;
				sem_buf.sem_op = 2;
				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				break;
			}
		}
	}
	return retval;
}

int EzMsgRouterUtil :: decrementMsgRouterBufferSize()
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct sembuf sem_buf;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", "EzMsgRouter" );

	if( !strcmp( TaskChannelName, ( EzChannelMgrShmPtr + EzMsgRouterChannelOffset )->ChannelName ) )
	{
		sem_buf.sem_num = EzMsgRouterChannelOffset;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		( EzChannelMgrShmPtr + EzMsgRouterChannelOffset )->CurrentBufferSize -= 1;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		retval = 1;
	}
	if( retval < 0 )
	{
		for( int i = 0; i < MaxChannels; i++ )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
			{
				sem_buf.sem_num = i;
				sem_buf.sem_flg = 0;
				sem_buf.sem_op = -2;

				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				( EzChannelMgrShmPtr + i )->CurrentBufferSize -= 1;
				EzMsgRouterChannelOffset = i;
				sem_buf.sem_op = 2;
				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				retval = 1;
				break;
			}
		}
	}
	return retval;
}

int EzMsgRouterUtil :: incrementChannelBufferSize( const char *ChannelName )
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct sembuf sem_buf;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	if( !strcmp( TaskChannelName, ( EzChannelMgrShmPtr + ChannelOffset )->ChannelName ) )
	{
		sem_buf.sem_num = ChannelOffset;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		( EzChannelMgrShmPtr + ChannelOffset )->CurrentBufferSize += 1;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		retval = 1;
	}
	if( retval < 0 )
	{
		for( int i = 0; i < MaxChannels; i++ )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
			{
				sem_buf.sem_num = i;
				sem_buf.sem_flg = 0;
				sem_buf.sem_op = -2;

				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				( EzChannelMgrShmPtr + i )->CurrentBufferSize += 1;
				ChannelOffset = i;
				sem_buf.sem_op = 2;
				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				retval = 1;
				break;
			}
		}
	}
	return retval;
}

int EzMsgRouterUtil :: incrementChannelDropCount( const char *ChannelName )
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct sembuf sem_buf;

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	if( !strcmp( TaskChannelName, ( EzChannelMgrShmPtr + ChannelOffset )->ChannelName ) )
	{
		sem_buf.sem_num = ChannelOffset;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		( EzChannelMgrShmPtr + ChannelOffset )->DropCount += 1;
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		retval = 1;
	}
	if( retval < 0 )
	{
		for( int i = 0; i < MaxChannels; i++ )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
			{
				sem_buf.sem_num = i;
				sem_buf.sem_flg = 0;
				sem_buf.sem_op = -2;

				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				( EzChannelMgrShmPtr + i )->DropCount += 1;
				ChannelOffset = i;
				sem_buf.sem_op = 2;
				if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				retval = 1;
				break;
			}
		}
	}
	return retval;
}

int EzMsgRouterUtil :: locateChannel( const char *ChannelName, char *TaskName, int *ChannelQid, int *ChannelKeyId )
{
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	for( int i = 0; i < MaxChannels; i++ )
	{
		if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) )
		{
			*ChannelQid = ( EzChannelMgrShmPtr + i )->ChannelQid;
			*ChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			strcpy( TaskName, ( EzChannelMgrShmPtr + i )->TaskName );
			ChannelOffset = i;
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzMsgRouterUtil :: LocateChannel( const char *ChannelName, char *TaskName, int *ChannelQid, int *ChannelKeyId )
{
	if( !MsgRouterLockFlag )
		return locateChannel( ChannelName, TaskName, ChannelQid, ChannelKeyId );

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
			*ChannelQid = ( EzChannelMgrShmPtr + i )->ChannelQid;
			*ChannelKeyId = ( EzChannelMgrShmPtr + i )->ChannelKeyId;
			strcpy( TaskName, ( EzChannelMgrShmPtr + i )->TaskName );
			retval = 1;
			ChannelOffset = i;
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

int EzMsgRouterUtil :: locatePortName( const char *PortName, int *PortId )
{
	int retval = -1;

	for( int i = 0; i < MaxPortChannels; i++ )
	{
		if( !strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, PortName ) )
		{
			dptr->trace( "Inside PortName[%s] PortId[%d]", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId );
			retval = 1;
			*PortId = ( EzChannelMgrPortShmPtr + i )->PortId;
			break;
		}
	}
	return retval;
}

int EzMsgRouterUtil :: LocatePortName( const char *PortName, int *PortId )
{
	if( !MsgRouterLockFlag )
		return locatePortName( PortName, PortId );

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
			dptr->trace( "Inside PortName[%s] PortId[%d]", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId );
			retval = 1;
			*PortId = ( EzChannelMgrPortShmPtr + i )->PortId;
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

int EzMsgRouterUtil :: listPortChannelTable()
{
	for( int i = 0; i < MaxPortChannels; i++ )
	{
		dptr->trace( "PortName[%s] PortId[%d]", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId );
	}
	return 1;
}

int EzMsgRouterUtil :: ListPortChannelTable()
{
	if( !MsgRouterLockFlag )
		return listPortChannelTable();

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
		dptr->trace( "PortName[%s] PortId[%d]", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId );
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

int EzMsgRouterUtil :: initMsgRouterTable()
{
	msgroutertable_ptr = ( struct EzMsgRouterTable * ) malloc( sizeof( struct EzMsgRouterTable ) * MaxChannels );

	if( msgroutertable_ptr == NULL )
	{
		dptr->trace( "Error in Allocating Memory for MsgRouterTable...Malloc Error..." );
		return -1;
	}

	for( int i = 0; i < MaxChannels; i++ )
	{
		memset( msgroutertable_ptr + i, 0, sizeof( struct EzMsgRouterTable ) );
		strcpy( ( msgroutertable_ptr + i )->ChannelName, CHANNEL_INIT_NAME );
	}
	return 1;
}

int EzMsgRouterUtil :: addMsgRouterTable( struct EzMsgRouterTable *msgrouter_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxChannels; i++ )
	{
		if( !strcmp( ( msgroutertable_ptr + i )->ChannelName, CHANNEL_INIT_NAME ) )
		{
			retval = 1;
			memset( msgroutertable_ptr + i, 0, sizeof( struct EzMsgRouterTable ) );
			memcpy( msgroutertable_ptr + i, msgrouter_rec, sizeof( struct EzMsgRouterTable ) );
			dptr->trace( "after adding ChannelShmPtr[%u]", ( msgroutertable_ptr + i )->ChannelShmPtr );
			break;
		}
	}
	return retval;
}

int EzMsgRouterUtil :: readMsgRouterTable( const char *ChannelName, struct EzMsgRouterTable *msgrouter_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxChannels; i++ )
	{
		if( !strcmp( ( msgroutertable_ptr + i )->ChannelName, ChannelName ) )
		{
			retval = 1;
			memcpy( msgrouter_rec, msgroutertable_ptr + i, sizeof( struct EzMsgRouterTable ) );
			break;
		}
	}
	return retval;
}

