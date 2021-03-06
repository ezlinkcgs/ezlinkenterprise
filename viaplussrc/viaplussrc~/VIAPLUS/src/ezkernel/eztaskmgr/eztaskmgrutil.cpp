#include <ezkernel/eztaskmgrutil.h>

EzTaskMgrUtil :: EzTaskMgrUtil()
{
	NewTaskOffset = 0;
}

EzTaskMgrUtil :: ~EzTaskMgrUtil()
{
}

int EzTaskMgrUtil :: InitEzTaskMgrUtil( int maxTask, int OrgKey, EzDebugUtil *dptr )
{
	NewTaskOffset = 0;
	this->maxTask = maxTask;
	this->dptr = dptr;
	this->EzTaskMgrChildKey = OrgKey - 1;
	this->EzTaskMgrKey = OrgKey;
	this->EzTaskMgrAckKey = OrgKey + 1;
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

	if( semctl( EzTaskMgrChildSemid, 0, SETVAL, arg ) < 0 )
			return -1;

	return 1;
}

int EzTaskMgrUtil :: WaitForParent()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = -3;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzTaskMgrUtil :: InvokeChild()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 0;
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

int EzTaskMgrUtil :: WaitForChild()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 0;
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

int EzTaskMgrUtil :: InvokeParent()
{
	struct sembuf sem_buf;
	sem_buf.sem_flg = 0;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 4;
	if( semop( EzTaskMgrChildSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in semop for EzTaskMgrChild Semaphore Sys Err[%s]", strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzTaskMgrUtil :: IsTaskMgrAlreadyRunning()
{
	int EzTaskMgrAckSemid;
	struct sembuf sem_buf;

	EzTaskMgrAckSemid = semget( ( key_t ) EzTaskMgrAckKey, 2, IPC_CREAT | 0666 );

	if( EzTaskMgrAckSemid < 0 )
	{
		dptr->trace( "Error in Creating EzTaskMgrAck Semaphore SysErr[%s] errno[%d]", strerror( errno ), errno );
		return -1;
	}

	if( semctl( EzTaskMgrAckSemid, 0, GETVAL, 0 ) == 5 )
		return 1;
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
		if( semctl( EzTaskMgrAckSemid, 0, SETVAL, arg ) < 0 )
			return -1;

		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_num = 0;
		sem_buf.sem_op = 3;

		if( semop( EzTaskMgrAckSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop for EzTaskMgrChildAck Semaphore Sys Err[%s]", strerror( errno ) );
			return -1;
		}

		return 0;
	}
}

int EzTaskMgrUtil :: CreateEzTaskMgrQueue()
{
	EzTaskMgrQid = msgget( ( key_t ) EzTaskMgrKey, IPC_CREAT | 0666 );
	if( EzTaskMgrQid < 0 )
	{
		dptr->trace( "Error in Creating EzTaskMgr queue ...Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzTaskMgrUtil :: GetTaskMgrQid()
{
	return EzTaskMgrQid;
}

int EzTaskMgrUtil :: CreateEzTaskMgrSharedMemory()
{
	struct shmid_ds shmstatus;
	struct semid_ds semstatus;
	EzTaskMgrShmid = shmget( ( key_t ) EzTaskMgrKey, ( maxTask + 1 ) * sizeof( struct EzTaskTable ), IPC_CREAT | IPC_EXCL | 0666 );
	if( EzTaskMgrShmid < 0 )
	{
		if( errno == EEXIST )
		{
			EzTaskMgrShmid = shmget( ( key_t ) EzTaskMgrKey, 0, IPC_CREAT | 0666 );
			if( EzTaskMgrShmid < 0 )
			{
				dptr->trace( "Error in Creating EzTaskMgr Shared Memory ...Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			shmctl( EzTaskMgrShmid, IPC_RMID, &shmstatus );
			EzTaskMgrShmid = shmget( ( key_t ) EzTaskMgrKey, ( maxTask + 1 ) * sizeof( struct EzTaskTable ), IPC_CREAT | IPC_EXCL | 0666 );
			if ( EzTaskMgrShmid < 0 )
			{
				dptr->trace( "Error in Creating EzTaskMgr Shared Memory ...Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
		else
		{
			dptr->trace( "Error in Creating EzTaskMgr Shared Memory ...Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	EzTaskMgrShmPtr = ( struct EzTaskTable * ) shmat( EzTaskMgrShmid, NULL, 0 );
	if( EzTaskMgrShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzTaskMgr Shared Memory ...Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	EzTaskMgrSemid = semget( ( key_t ) EzTaskMgrKey, maxTask, IPC_CREAT | IPC_EXCL | 0666 );
	if( EzTaskMgrSemid < 0 )
	{
		if( errno == EEXIST )
		{
			EzTaskMgrSemid = semget( ( key_t ) EzTaskMgrKey, 0, IPC_CREAT | 0666 );
			if( EzTaskMgrSemid < 0 )
			{
				dptr->trace( "Error in Creating EzTaskMgr Semaphore Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			semctl( EzTaskMgrSemid, 0, IPC_RMID, &semstatus );
			EzTaskMgrSemid = semget( ( key_t ) EzTaskMgrKey, maxTask, IPC_CREAT | IPC_EXCL | 0666 );
			if( EzTaskMgrSemid < 0 )
			{
				dptr->trace( "Error in Creating EzTaskMgr Semaphore Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
		else
		{
			dptr->trace( "Error in Creating EzTaskMgr Semaphore Sys Err[%s] ErrNo[%d]", strerror( errno ), errno );
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
	for( int i = 0; i < maxTask; i++ )
	{
		if( semctl( EzTaskMgrSemid, i, SETVAL, arg ) < 0 )
			return -1;
	}

	return 1;
}


int EzTaskMgrUtil :: CreateEzTaskMgrChannel()
{
	struct shmid_ds shmstatus;
	struct semid_ds semstatus;

	if( CreateEzTaskMgrQueue() < 0 )
		return -1;

	if( CreateEzTaskMgrSharedMemory() < 0 )
		return -1;
	return 1;
}

int EzTaskMgrUtil :: SendTaskCommandResponse( struct EzTaskCmdMsg cmdmsg )
{
	struct EzTaskCmdQMsg cmdqmsg;

	cmdqmsg.msgtype = cmdmsg.NotificationId;
	memcpy( &cmdqmsg.cmdmsg, &cmdmsg, sizeof( struct EzTaskCmdMsg ) );
	if( msgsnd( EzTaskMgrQid, &cmdqmsg, sizeof( cmdqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
	{
		if( errno == EIDRM )
		{
			if( CreateEzTaskMgrQueue() < 0 )
					return -1;
		}
		if( msgsnd( EzTaskMgrQid, &cmdqmsg, sizeof( cmdqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			return -1;
	}
	return 1;
}

int EzTaskMgrUtil :: WaitForTaskCommandRequest( struct EzTaskCmdMsg *cmdmsg )
{
	struct EzTaskCmdQMsg cmdqmsg;
	while( 1 )
	{
		memset( &cmdqmsg, 0, sizeof( struct EzTaskCmdQMsg ) );
		if( msgrcv( EzTaskMgrQid, &cmdqmsg, sizeof( struct EzTaskCmdQMsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			if( errno == EIDRM )
			{
				if( CreateEzTaskMgrQueue() < 0 )
					return -1;
				continue;
			}
			else if ( errno == EINTR )
				continue;
			else
				return -1;
		}
		break;
	}
	memcpy( cmdmsg, &cmdqmsg.cmdmsg, sizeof( EzTaskCmdMsg ) );
	return 1;
}

int EzTaskMgrUtil :: WaitForTask( int TaskId )
{
	struct EzTaskAckQMsg ackqmsg;
	memset( &ackqmsg, 0, sizeof( ackqmsg ) );

	while( 1 )
	{
		dptr->trace( "Waiting for Task Ack Message from TaskId[%d]", TaskId );
		if( msgrcv( EzTaskMgrQid, &ackqmsg, sizeof( ackqmsg ) - sizeof( long ), TaskId, 0 ) < 0 )
		{
			if( errno == EINTR )
			{
				dptr->trace( "Interuppted while Waiting for TaskId[%d] to Start", TaskId );
				continue;
			}
			else if ( errno == EIDRM )
			{
				if( CreateEzTaskMgrQueue() < 0 )
					return -1;
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

int EzTaskMgrUtil :: SendTaskInitErr( int TaskId )
{
	struct EzTaskAckQMsg ackqmsg;
	memset( &ackqmsg, 0, sizeof( ackqmsg ) );
	ackqmsg.msgtype = TaskId;
	ackqmsg.ackmsg.Response = -1;
	if( msgsnd( EzTaskMgrQid, &ackqmsg, sizeof( ackqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
	{
		if( errno == EIDRM )
		{
			if( CreateEzTaskMgrQueue() < 0 )
				return -1;
		}
		if( msgsnd( EzTaskMgrQid, &ackqmsg, sizeof( ackqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			return -1;
	}
	return 1;
}

void EzTaskMgrUtil :: InitTaskTable()
{
	for( int i = 0; i < maxTask; i++ )
	{
		memset( ( EzTaskMgrShmPtr + i )->TaskName, 0, sizeof( ( EzTaskMgrShmPtr + i )->TaskName ) );
		strcpy( ( EzTaskMgrShmPtr + i )->TaskName, TASK_INIT_NAME );
		( EzTaskMgrShmPtr + i )->TaskId = TASK_INIT_VAL;
		( EzTaskMgrShmPtr + i )->TraceLevel = TASK_INIT_VAL;
		( EzTaskMgrShmPtr + i )->TaskStatus = TASK_INIT_VAL;
		memset( ( EzTaskMgrShmPtr + i )->StartDate, 0, sizeof( ( EzTaskMgrShmPtr + i )->StartDate ) );
		strcpy( ( EzTaskMgrShmPtr + i )->StartDate, TASK_INIT_NAME );
		memset( ( EzTaskMgrShmPtr + i )->StartTime, 0, sizeof( ( EzTaskMgrShmPtr + i )->StartTime ) );
		strcpy( ( EzTaskMgrShmPtr + i )->StartTime, TASK_INIT_NAME );
	}
}

void EzTaskMgrUtil :: InitTaskTable( int segOffset )
{
	memset( ( EzTaskMgrShmPtr + segOffset )->TaskName, 0, sizeof( ( EzTaskMgrShmPtr + segOffset )->TaskName ) );
	strcpy( ( EzTaskMgrShmPtr + segOffset )->TaskName, TASK_INIT_NAME );
	( EzTaskMgrShmPtr + segOffset )->TaskId = TASK_INIT_VAL;
	( EzTaskMgrShmPtr + segOffset )->TraceLevel = TASK_INIT_VAL;
	( EzTaskMgrShmPtr + segOffset )->TaskStatus = TASK_INIT_VAL;
	memset( ( EzTaskMgrShmPtr + segOffset )->StartDate, 0, sizeof( ( EzTaskMgrShmPtr + segOffset )->StartDate ) );
	strcpy( ( EzTaskMgrShmPtr + segOffset )->StartDate, TASK_INIT_NAME );
	memset( ( EzTaskMgrShmPtr + segOffset )->StartTime, 0, sizeof( ( EzTaskMgrShmPtr + segOffset )->StartTime ) );
	strcpy( ( EzTaskMgrShmPtr + segOffset )->StartTime, TASK_INIT_NAME );
}

int EzTaskMgrUtil :: GetTaskTableCount()
{
	int TaskCount = 0;
	struct sembuf sem_buf;
	for( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( ( strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TASK_INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + i )->TaskId != TASK_INIT_VAL ) )
			TaskCount++;
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return TaskCount;
}

int EzTaskMgrUtil :: AddTaskTable( const char *TaskName, int TaskId )
{
	struct sembuf sem_buf;

	if( ( !strcmp( ( EzTaskMgrShmPtr + NewTaskOffset )->TaskName, TASK_INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + NewTaskOffset )->TaskId == TASK_INIT_VAL ) )
	{
		memset( ( EzTaskMgrShmPtr + NewTaskOffset )->TaskName, 0, sizeof( ( EzTaskMgrShmPtr + NewTaskOffset )->TaskName ) );
		strcpy( ( EzTaskMgrShmPtr + NewTaskOffset )->TaskName, TaskName );
		( EzTaskMgrShmPtr + NewTaskOffset )->TaskId = TaskId;
		( EzTaskMgrShmPtr + NewTaskOffset )->TraceLevel = TASK_INIT_VAL;
		( EzTaskMgrShmPtr + NewTaskOffset )->TaskStatus = TASK_INIT_VAL;
		memset( ( EzTaskMgrShmPtr + NewTaskOffset )->StartDate, 0, sizeof( ( EzTaskMgrShmPtr + NewTaskOffset )->StartDate ) );
		strcpy( ( EzTaskMgrShmPtr + NewTaskOffset )->StartDate, TASK_INIT_NAME );
		memset( ( EzTaskMgrShmPtr + NewTaskOffset )->StartTime, 0, sizeof( ( EzTaskMgrShmPtr + NewTaskOffset )->StartTime ) );
		strcpy( ( EzTaskMgrShmPtr + NewTaskOffset )->StartTime, TASK_INIT_NAME );

		memset( EzTaskMgrShmPtr + maxTask, 0, sizeof( struct EzTaskTable ) );
		( EzTaskMgrShmPtr + maxTask )->TaskId = NewTaskOffset;
		dptr->trace( "NewTaskOffset[%d] is assigned for TaskId[%d] TaskName[%s]", NewTaskOffset, TaskId, TaskName );
		NewTaskOffset++;
	}
	else
	{
		for( int i = 0; i < maxTask; i++ )
		{
			sem_buf.sem_flg = 0;
			sem_buf.sem_num = i;
			sem_buf.sem_op = -2;
			if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( " Error in semop operation ...");
				dptr->trace( " Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			if( ( !strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TASK_INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + i )->TaskId == TASK_INIT_VAL ) )
			{
				NewTaskOffset = i;
				memset( ( EzTaskMgrShmPtr + i )->TaskName, 0, sizeof( ( EzTaskMgrShmPtr + i )->TaskName ) );
				strcpy( ( EzTaskMgrShmPtr + i )->TaskName, TaskName );
				( EzTaskMgrShmPtr + i )->TaskId = TaskId;
				( EzTaskMgrShmPtr + i )->TraceLevel = TASK_INIT_VAL;
				( EzTaskMgrShmPtr + i )->TaskStatus = TASK_INIT_VAL;
				memset( ( EzTaskMgrShmPtr + i )->StartDate, 0, sizeof( ( EzTaskMgrShmPtr + i )->StartDate ) );
				strcpy( ( EzTaskMgrShmPtr + i )->StartDate, TASK_INIT_NAME );
				memset( ( EzTaskMgrShmPtr + i )->StartTime, 0, sizeof( ( EzTaskMgrShmPtr + i )->StartTime ) );
				strcpy( ( EzTaskMgrShmPtr + i )->StartTime, TASK_INIT_NAME );
				sem_buf.sem_op = 2;
				if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( " Error in semop operation ...");
					dptr->trace( " Sys Error [%s] ", strerror( errno ) );
					return -1;
				}
				break;
			}
			sem_buf.sem_op = 2;
			if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( " Error in semop operation ...");
				dptr->trace( " Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
		}
		memset( EzTaskMgrShmPtr + maxTask, 0, sizeof( struct EzTaskTable ) );
		( EzTaskMgrShmPtr + maxTask )->TaskId = NewTaskOffset;
		dptr->trace( "NewTaskOffset[%d] is assigned for TaskId[%d] TaskName[%s]", NewTaskOffset, TaskId, TaskName );
		NewTaskOffset++;
	}
	return 1;
}

int EzTaskMgrUtil :: IsTaskInitialized( int TaskId )
{
	struct sembuf sem_buf;
	int retval = 0;
	for ( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return 0;
		}
		if( ( EzTaskMgrShmPtr + i )->TaskId == TaskId )
		{
			if( ( EzTaskMgrShmPtr + i )->TaskStatus == TASK_RUNNING )
				retval = 1;
			sem_buf.sem_op = 2;
			if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( " Error in semop operation ...");
				dptr->trace( " Sys Error [%s] ", strerror( errno ) );
				return 0;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return 0;
		}
	}
	return retval;
}


int EzTaskMgrUtil :: RemoveTaskTable( int TaskId )
{
	struct sembuf sem_buf;
	for ( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( EzTaskMgrShmPtr + i )->TaskId == TaskId )
		{
			InitTaskTable( i );
			sem_buf.sem_op = 2;
			if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( " Error in semop operation ...");
				dptr->trace( " Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}

int EzTaskMgrUtil :: LocateTaskTable( int TaskId, char *TaskName )
{
	struct sembuf sem_buf;
	int rval = -1;
	for( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( ( EzTaskMgrShmPtr + i )->TaskId == TaskId )
		{
			strcpy( TaskName, ( EzTaskMgrShmPtr + i )->TaskName );
			sem_buf.sem_op = 2;
			if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( " Error in semop operation ...");
				dptr->trace( " Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			rval = 1;
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return rval;
}

int EzTaskMgrUtil :: LocateTaskTable( const char *TaskName )
{
	struct sembuf sem_buf;
	int rval = -1;
	for( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TaskName ) )
		{
			sem_buf.sem_op = 2;
			rval = ( EzTaskMgrShmPtr + i )->TaskId;
			if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( " Error in semop operation ...");
				dptr->trace( " Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return rval;
}

int EzTaskMgrUtil :: LoadTaskTable( struct EzTaskTable *tmgrtable )
{
	struct sembuf sem_buf;
	int tcount = 0;
	for( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if ( ( strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TASK_INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + i )->TaskId != TASK_INIT_VAL ) )
		{
			memcpy( tmgrtable + tcount, ( EzTaskMgrShmPtr + i ), sizeof( struct EzTaskTable ) );
		 	tcount++;
		}
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}

int EzTaskMgrUtil :: ListTaskTable()
{
	struct sembuf sem_buf;
	dptr->trace( "---------------------------");
	dptr->trace( "TASK NAME TASKID TASKSTATUS TRACELEVEL STARTDATE STARTTIME");
	dptr->trace( "---------------------------");
	for( int i = 0; i < maxTask; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if ( ( strcmp( ( EzTaskMgrShmPtr + i )->TaskName, INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + i )->TaskId != INIT_VAL ) )
		dptr->trace( "[%s] [%d] [%d] [%d] [%s] [%s]", ( EzTaskMgrShmPtr + i )->TaskName, ( EzTaskMgrShmPtr + i )->TaskId, ( EzTaskMgrShmPtr + i )->TaskStatus, ( EzTaskMgrShmPtr + i )->TraceLevel, ( EzTaskMgrShmPtr + i )->StartDate, ( EzTaskMgrShmPtr + i )->StartTime );
		sem_buf.sem_op = 2;
		if( semop( EzTaskMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( " Error in semop operation ...");
			dptr->trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	dptr->trace( "-----------------------------------------------------");
	return 1;
}

