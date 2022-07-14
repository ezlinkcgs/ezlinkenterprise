#include <ezbusiness/ezatmejutil.h>

EzAtmEjUtil :: EzAtmEjUtil()
{
}

EzAtmEjUtil :: ~EzAtmEjUtil()
{
}

int EzAtmEjUtil :: InitEzAtmEjUtil( EzDebugUtil *dptr, bool ATMLockFlag )
{
	EzCfgUtil cfgutil;
	struct EzChannelMgrQMsg chqmsg;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];

	this->dptr = dptr;
	this->ATMLockFlag = ATMLockFlag;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in opening file[ %s ]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "CHANNEL#ORGKEY", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Searching CHANNEL#ORGKEY from file[ %s ]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	cfgutil.cfg_close();

	EzChannelMgrKey = atoi( cfgval ) + 2;

	EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );

	if( EzChannelMgrQid < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EzChannelMgr Queue SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}

	memset( &chqmsg, 0, sizeof( chqmsg ) );
	chqmsg.msgtype = 1;
	strcpy( chqmsg.chmgrmsg.ChannelName, ATMEJMEMORY );
	chqmsg.chmgrmsg.Command = LOCATE_MEMORY_CHANNEL;
	chqmsg.chmgrmsg.NotificationId = getpid();

	if( msgsnd( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Sending Locate Memory Channel Message to EzChannelMgr Queue SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}

	memset( &chqmsg, 0, sizeof( chqmsg ) );
	if( msgrcv( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), getpid(), 0 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Receiving Locate Memory Channel Message From EzChannelMgr Queue SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}

	if( chqmsg.chmgrmsg.Response < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Locating Memory[ %s ]", ATMEJMEMORY );
		return -1;
	}

	dptr->trace( DEBUG_NORMAL, "Memory[ %s ] Located with ChannelKeyId[ %d ]", chqmsg.chmgrmsg.ChannelName, chqmsg.chmgrmsg.ChannelKeyId );
	AtmEjMemoryId = chqmsg.chmgrmsg.ChannelKeyId;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezbusiness.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in opening file[ %s ]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXATM", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Searching EZBUSINESS#MAXATM from file[ %s ]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Invalid EZBUSINESS#MAXATM[ %s ] value defined in file[ %s ]", cfgval, cfgpath );
		return -1;
	}

	MaxAtms = atoi( cfgval );

	AtmEjMemoryShmid = shmget( ( key_t ) AtmEjMemoryId, 0, IPC_CREAT | 0666 );
	if(  AtmEjMemoryShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Device Memory Table Shared Memory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}

	AtmEjMemoryShmPtr = ( struct ATMEjBuffer * ) shmat( AtmEjMemoryShmid, 0, 0 );
	if( AtmEjMemoryShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR, "Error in attaching Device Memory Table Shared Memory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}

	AtmEjMemorySemid = semget( ( key_t ) AtmEjMemoryId, 0, IPC_CREAT | 0666 );
	if( AtmEjMemorySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Device Memory Table Semaphore SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmEjUtil :: readAtmEjMemory( const char *AtmId, struct ATMEjBuffer *AtmEjMemory_ptr )
{
	int retval = -1;

	for( int i = 0; i < MaxAtms; i++ )
	{
		if( !strcmp( ( AtmEjMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			memcpy( AtmEjMemory_ptr, ( AtmEjMemoryShmPtr + i ), sizeof( struct ATMEjBuffer ) );
			OffSet = i;
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzAtmEjUtil :: ReadAtmEjMemory( const char *AtmId, struct ATMEjBuffer *AtmEjMemory_ptr )
{
	if( !ATMLockFlag )
		return readAtmEjMemory( AtmId, AtmEjMemory_ptr );

	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( AtmEjMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			memcpy( AtmEjMemory_ptr, ( AtmEjMemoryShmPtr + i ), sizeof( struct ATMEjBuffer ) );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmEjUtil :: writeAtmEjMemory( const char *AtmId, struct ATMEjBuffer *AtmEjMemory_ptr )
{
	int retval = -1;

	if( ( !strcmp( ( AtmEjMemoryShmPtr + OffSet )->AtmId, AtmId ) ) )
	{
		memcpy( ( AtmEjMemoryShmPtr + OffSet ), AtmEjMemory_ptr, sizeof( struct ATMEjBuffer ) );
		retval = 1;
	}
	else
	{
		for( int i = 0; i < MaxAtms; i++ )
		{
			if( !strcmp( ( AtmEjMemoryShmPtr + i )->AtmId, AtmId ) )
			{
				memcpy( ( AtmEjMemoryShmPtr + i ), AtmEjMemory_ptr, sizeof( struct ATMEjBuffer ) );
				retval = 1;
				break;
			}
		}
	}
	return retval;
}

int EzAtmEjUtil :: WriteAtmEjMemory( const char *AtmId, struct ATMEjBuffer *AtmEjMemory_ptr )
{
	if( !ATMLockFlag )
		return writeAtmEjMemory( AtmId, AtmEjMemory_ptr );

	struct sembuf sem_buf;
	int retval = -1;

	sem_buf.sem_num = OffSet;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
		return -1;
	}

	if( ( !strcmp( ( AtmEjMemoryShmPtr + OffSet )->AtmId, AtmId ) ) )
	{
		memcpy( ( AtmEjMemoryShmPtr + OffSet ), AtmEjMemory_ptr, sizeof( struct ATMEjBuffer ) );
		retval = 1;
		sem_buf.sem_op = 2;
		if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	else
	{
		sem_buf.sem_op = 2;
		if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
		for( int i = 0; i < MaxAtms; i++ )
		{
			sem_buf.sem_num = i;
			sem_buf.sem_flg = 0;
			sem_buf.sem_op = -2;

			if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
				return -1;
			}

			if( !strcmp( ( AtmEjMemoryShmPtr + i )->AtmId, AtmId ) )
			{
				memcpy( ( AtmEjMemoryShmPtr + i ), AtmEjMemory_ptr, sizeof( struct ATMEjBuffer ) );
				retval = 1;
				sem_buf.sem_op = 2;
				if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
					return -1;
				}
				break;
			}
			sem_buf.sem_op = 2;
			if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
				return -1;
			}
		}
	}
	return retval;
}

int EzAtmEjUtil :: verifyAtmEjMemory( const char *AtmId )
{
	int retval = -1;

	for( int i = 0; i < MaxAtms; i++ )
	{
		if( !strcmp( ( AtmEjMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			retval = 1;
			break;
		}
	}
	return retval;
}


int EzAtmEjUtil :: VerifyAtmEjMemory( const char *AtmId )
{
	if( !ATMLockFlag )
		return verifyAtmEjMemory( AtmId );

	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( AtmEjMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			//dptr->trace( DEBUG_TEST, "ATM Id < %s > is matching", AtmId );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmEjMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmEjMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmEjUtil :: CheckInteger( const char *value )
{
    for( int i = 0; i < strlen( value ); i++ )
    {
        if( ( value[ i ] < 48 ) || ( value[ i ] > 57 ) )
        	return -1;
    }
    return 1;
}

int EzAtmEjUtil :: GetNTokens( char *TokenString, char ch )
{
	int cnt = 0;
	for( int i = 0; i < strlen( TokenString ); i++ )
	{
		if( TokenString[ i ] == ch )
			cnt++;
	}
	return cnt + 1;
}

int EzAtmEjUtil :: ParseToken( char *TokenString, char *Token, int count, char ch )
{
	for( int i = 0, j = 0, cnt = 0; i < strlen( TokenString ); i++ )
	{
		if( TokenString[ i ] == ch )
			cnt++;
		else if( cnt == count )
		        break;
		else if ( cnt + 1 == count )
		{
			Token[ j ] = TokenString[ i ];
			j++;
		}
	}
	return 1;
}
