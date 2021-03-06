#include <ezkernel/ezchannelcmdutil.h>

int EzChannelCmdUtil :: InitEzChannelCmdUtil( EzDebugUtil *dptr )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];
	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}
	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#ORGKEY", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching CHANNEL#ORGKEY in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	EzChannelMgrKey = atoi( CfgVal ) + 2;
	EzChannelMgrPortKey = atoi( CfgVal ) + 3;

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXCHANNELS", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching CHANNEL#MAXCHANNELS in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxChannels = atoi( CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXPORTCHANNELS", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching CHANNEL#MAXPORTCHANNELS in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxPortChannels = atoi( CfgVal );

	cfgutil.cfg_close();
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

	EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, 0 );
	if( EzChannelMgrPortShmPtr == NULL )
	{
		dptr->trace( "Error in Attaching EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EzChannelMgrPortSemid = semget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortSemid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelPort Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( ezchannelparam.initChannelParam( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ChannelParam...." );
		return -1;
	}

	if( eventtable.initEventTable( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing EventTable...." );
		return -1;
	}
	return 1;
}

int EzChannelCmdUtil :: listChannel()
{
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];
	bool first = true;

	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
	printf("\n%25s%15s%15s", "ChannelName", "NMessages", "CurrentSize" );
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );

	for( int i = 0; i < MaxChannels; i++ )
	{
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TASK_CHANNEL ) )
		{
			if( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, "TASK_EzTaskMgr" ) || !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, "TASK_EzChannelMgr" ) || !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, "TASK_EzCommMgr" ) || !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, "TASK_EzChannelPortMgr" ) || !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, "TASK_EzSecurityDriver" ) )
			{
				if( LoadMsgQInfo( ( EzChannelMgrShmPtr + i )->ChannelQid ) >= 0 )
				{
					memset( ChannelName, 0, sizeof( ChannelName ) );
					strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 5 );
					printf("\n%25s%15d%15d", ChannelName, GetNMsg(), GetNBytes() );
				}
			}
			else
			{
				if( first )
				{
					printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
					printf("\n%25s%15s%15s", "ChannelName", "NMessages", "DropCount" );
					printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
					first = false;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 5 );
				printf("\n%25s%15d%15d", ChannelName, ( EzChannelMgrShmPtr + i )->CurrentBufferSize, ( EzChannelMgrShmPtr + i )->DropCount );

			}
		}
	}
	printf("\t\t\tActiveEvents->[%d]", eventtable.getActiveEvents() );
	printf( "\n\n" );
	return 1;
}


int EzChannelCmdUtil :: ListChannel()
{
	if( ezchannelparam.isUseSharedMemory() )
		return listChannel();

	struct sembuf sem_buf;
	int retval = -1;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];

	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n%20s%15s%15s%15s%10s", "ChannelName", "ChannelQid", "NMessages", "CurrentSize", "MaxSize" );
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

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
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TASK_CHANNEL ) )
		{
			if( LoadMsgQInfo( ( EzChannelMgrShmPtr + i )->ChannelQid ) >= 0 )
			{
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 5 );
				printf("\n%20s%15d%15d%15d%10d", ChannelName, ( EzChannelMgrShmPtr + i )->ChannelQid, GetNMsg(), GetNBytes(), GetMaxBytes() );
			}
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
		}
	}
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n");
	return retval;

}

int EzChannelCmdUtil :: ListChannel( const char *ChannelName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char TaskChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TaskChannelName, 0, sizeof( TaskChannelName ) );
	sprintf( TaskChannelName, "TASK_%s", ChannelName );

	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n%20s%15s%15s%15s%10s", "ChannelName", "ChannelQid", "NMessages", "CurrentSize", "MaxSize" );
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

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
		if( ( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TaskChannelName ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TASK_CHANNEL ) )
		{
			if( LoadMsgQInfo( ( EzChannelMgrShmPtr + i )->ChannelQid ) >= 0 )
			{
				printf("\n%20s%15d%15d%15d%10d", ChannelName, ( EzChannelMgrShmPtr + i )->ChannelQid, GetNMsg(), GetNBytes(), GetMaxBytes() );
			}
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        	}
	}
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n");
	return retval;
}

int EzChannelCmdUtil :: ListMemoryChannel()
{
	struct sembuf sem_buf;
	int retval = -1;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n%20s%15s", "ChannelName", "MemoryId" );
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

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
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == MEMORY_CHANNEL ) )
		{
			memset( ChannelName, 0, sizeof( ChannelName ) );
			strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 7 );
			printf("\n%20s%15d", ChannelName, ( EzChannelMgrShmPtr + i )->ChannelKeyId );
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        	return -1;
        }
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return retval;
}

int EzChannelCmdUtil :: ListMemoryChannel( const char *ChannelName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char MemoryChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( MemoryChannelName, 0, sizeof( MemoryChannelName ) );
	sprintf( MemoryChannelName, "MEMORY_%s", ChannelName );

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n%20s%15s", "ChannelName", "MemoryId" );
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

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
		if( ( !strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, MemoryChannelName ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == MEMORY_CHANNEL ) )
		{
			printf("\n%20s%15d", ChannelName, ( EzChannelMgrShmPtr + i )->ChannelKeyId );
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
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return retval;
}

int EzChannelCmdUtil :: ListTableChannel()
{
	struct sembuf sem_buf;
	int retval = -1;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n%20s%15s", "ChannelName", "TableId" );
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

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
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TABLE_CHANNEL ) )
		{
			memset( ChannelName, 0, sizeof( ChannelName ) );
			strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 6 );
			printf("\n%%20s%15d", ChannelName, ( EzChannelMgrShmPtr + i )->ChannelKeyId );
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        return -1;
        }
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );

	return retval;

}

int EzChannelCmdUtil :: ListTableChannel( const char *ChannelName )
{
	struct sembuf sem_buf;
	int retval = -1;
	char TableChannelName[ CHANNEL_NAME_SIZE + 1 ];

	memset( TableChannelName, 0, sizeof( TableChannelName ) );
	sprintf( TableChannelName, "TABLE_%s", ChannelName );

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n%20s%15s", "ChannelName", "TableId" );
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

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
		if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, TableChannelName ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TABLE_CHANNEL ) )
		{
			printf("\n%20s%10d", ChannelName, ( EzChannelMgrShmPtr + i )->ChannelKeyId );
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
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );

	return retval;
}

int EzChannelCmdUtil :: ListPortChannel()
{
	struct sembuf sem_buf;
	int retval = -1;

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n%20s%10s%15s", "PortName", "PortId", "NMessages" );
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

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
		if( strcmp( ( EzChannelMgrPortShmPtr + i )->PortName, CHANNEL_INIT_NAME ) )
		{
			printf("\n%20s%10d%15d", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId, ( EzChannelMgrPortShmPtr + i )->NMessage );
		}
		sem_buf.sem_op = 2;
		if( semop( EzChannelMgrPortSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace(" Error in semop operation ...");
			dptr->trace(" Sys Error [%s] ", strerror( errno ) );
	        return -1;
        }
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );

	return retval;
}


int EzChannelCmdUtil :: ListPortChannel( const char *PortName )
{
	struct sembuf sem_buf;
	int retval = -1;

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n%20s%10s%15s", "PortName", "PortId", "NMessages" );
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

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
			printf("\n%20s%10d%15d", ( EzChannelMgrPortShmPtr + i )->PortName, ( EzChannelMgrPortShmPtr + i )->PortId, ( EzChannelMgrPortShmPtr + i )->NMessage );
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
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );

	return retval;
}

