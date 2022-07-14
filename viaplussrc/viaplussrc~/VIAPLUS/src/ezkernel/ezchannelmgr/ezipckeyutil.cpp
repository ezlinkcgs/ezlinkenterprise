#include <ezkernel/ezipckeyutil.h>

EzIPCKeyUtil :: EzIPCKeyUtil()
{

}

EzIPCKeyUtil :: ~EzIPCKeyUtil()
{

}

void EzIPCKeyUtil :: InitEzIPCKeyUtil( EzDebugUtil *dptr, int OrgKey, int MaxIpcKeys )
{
	this->dptr = dptr;
	this->OrgKey = OrgKey;
	this->MaxKeys = MaxIpcKeys;
}

int EzIPCKeyUtil :: CreateIPCKeySharedMemory()
{
	KeyShmid = shmget( ( key_t ) OrgKey, MaxKeys * sizeof( struct IPCKeyMessage ), IPC_CREAT | 0666 );
	if( KeyShmid < 0 )
	{
		dptr->trace( "Error in Creating IPC Key Shared Memory Sys Err [%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	dptr->trace( "IPC Key Shared Memory Created with Id[%d]", KeyShmid );
	KeyShmptr = ( struct IPCKeyMessage * ) shmat( KeyShmid, 0, 0 );
	if( KeyShmptr == NULL )
	{
		dptr->trace( "Error in attaching IPC Key Shared Memory Sys Err [%s]", strerror( errno ) );
		return -1;
	}

	KeySemid = semget( ( key_t ) OrgKey, MaxKeys, IPC_CREAT | 0666 );

	if( KeySemid < 0 )
	{
		dptr->trace( "Error in Creating IPC Key Semaphore Sys Err [%s]", strerror( errno ) );
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
	for( int i = 0; i < MaxKeys; i++ )
	{
		if( semctl( KeySemid, i, SETVAL, arg ) < 0 )
		        return -1;
	}

	for( int i = 0; i < MaxKeys; i++ )
	{
		memset( ( KeyShmptr + i )->KeyName, 0, sizeof( ( KeyShmptr + i )->KeyName ) );
		strcpy( ( KeyShmptr + i )->KeyName, KEY_INIT_NAME );
		( KeyShmptr + i )->Key = KEY_INIT_VAL;
	}

	return 1;
}

int EzIPCKeyUtil :: GetIPCKeySharedMemory()
{

	KeyShmid = shmget( ( key_t )OrgKey, 0, IPC_CREAT | 0666 );

	if( KeyShmid < 0 )
	{
		dptr->trace( "Error in Creating IPC Key Shared Memory Sys Err [%s]", strerror( errno ) );
		return -1;
	}

	dptr->trace( "IPC Key Shared Memory Created with Id[%d]", KeyShmid );

	KeyShmptr = ( struct IPCKeyMessage * ) shmat( KeyShmid, 0, 0 );

	if( KeyShmptr == NULL )
	{
		dptr->trace( "Error in attaching IPC Key Shared Memory Sys Err [%s]", strerror( errno ) );
		return -1;
	}

	KeySemid = semget( ( key_t ) OrgKey, 0, IPC_CREAT | 0666 );

	if( KeySemid < 0 )
	{
		dptr->trace( "Error in Creating IPC Key Semaphore Sys Err [%s]", strerror( errno ) );
		return -1;
	}

	return 1;
}

int EzIPCKeyUtil :: ListIPCKeyTable()
{
	struct sembuf sem_buf;
	dptr->trace( "----------------------------------------------");
	dptr->trace( "KeyName 		Key");
	dptr->trace( "----------------------------------------------");
	for( int i = 0; i < MaxKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_op = -2;
		if( semop( KeySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
			return -1;
		}
		dptr->trace( "[%s]	[%d]", ( KeyShmptr + i )->KeyName, ( KeyShmptr + i )->Key );
		sem_buf.sem_op = 2;
		if( semop( KeySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
			return -1;
		}
	}
	return 1;
}
		
int EzIPCKeyUtil :: LocateIPCKey( const char *KeyName )
{
	int ipckey = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_op = -2;
		if( semop( KeySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
			return -1;
		}
		if( !strcmp( ( KeyShmptr + i )->KeyName, KeyName ) )
		{
			ipckey = ( KeyShmptr + i )->Key;
			sem_buf.sem_op = 2;
			if( semop( KeySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( KeySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
			return -1;
		}
	}
	return ipckey;

}
		
int EzIPCKeyUtil :: CreateIPCKey( const char *KeyName )
{
	int ipckey = -1;
	struct sembuf sem_buf;

	ipckey = LocateIPCKey( KeyName );

	if( ipckey >= 0 )
		return ipckey;

	for( int i = 0; i < MaxKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_op = -2;
		if( semop( KeySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
			return -1;
		}
		if( ( KeyShmptr + i )->Key == KEY_INIT_VAL ) 
		{
			if( i == 0 )
			{
				( KeyShmptr + i )->Key = ++OrgKey;
				memset( ( KeyShmptr + i )->KeyName, 0, sizeof( ( KeyShmptr + i )->KeyName ) );
				strcpy( ( KeyShmptr + i )->KeyName, KeyName );
			}
			else
			{
				sem_buf.sem_num = i - 1;
				sem_buf.sem_flg = SEM_UNDO;
				sem_buf.sem_op = -2;
				if( semop( KeySemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
					return -1;
				}
				( KeyShmptr + i )->Key = ( KeyShmptr + i - 1 )->Key + 1;
				memset( ( KeyShmptr + i )->KeyName, 0, sizeof( ( KeyShmptr + i )->KeyName ) );
				strcpy( ( KeyShmptr + i )->KeyName, KeyName );
				sem_buf.sem_num = i - 1;
				sem_buf.sem_flg = SEM_UNDO;
				sem_buf.sem_op = 2;
				if( semop( KeySemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
					return -1;
				}
			}
			ipckey = ( KeyShmptr + i )->Key;
			sem_buf.sem_num = i;
			sem_buf.sem_flg = SEM_UNDO;
			sem_buf.sem_op = 2;
			if( semop( KeySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
				return -1;
			}
			break;
		}
		sem_buf.sem_num = i;
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_op = 2;
		if( semop( KeySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in semop sys err[%s]", strerror( errno ) );
			return -1;
		}
	}

	return ipckey;

}



