#include <ezlink/ezuploadcmd.h>

int EzUploadCmd :: initUploadCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezuploadcmd.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^EzUploadCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( InitEzChLocateUtil( this, "ezuploadcmd" ) < 0 )
	{
		trace( "Error in Initializing EzChLocateUtil");
		return -1;
	}

	if( LocateChannel( "EzSafUploader" ) < 0 )
	{
		trace( "Error in Locating Channel EzSafUploader" );
		return -1;
	}
	
	if( !IsTaskRunning( "EzSafUploader" ) )
	{
		trace( "EzSafUploader is not running");
		return -1;
	}
    memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
        trace( "Error in opening file[%s]", cfgpath );
        return -1;
    }

    memset( cfgval, 0, sizeof( cfgval ) );
    if( cfgutil.cfg_search( "NETWORK#MAXNETWORK", cfgval, 2 ) < 0 )
    {
        trace( "Error in Searching NETWORK#MAXNETWORK from file[%s]", cfgpath );
        cfgutil.cfg_close();
        return -1;
    }

    cfgutil.cfg_close();

    MaxNetworks = atoi( cfgval );

	NetworkMemoryId = LocateMemoryId( this, "NETWORKMEMORY" );

	if( NetworkMemoryId < 0 )
	{
		trace( "Error in Locating NETWORKMEMORY" );
		return -1;
	}

	NetworkShmid = shmget( ( key_t ) NetworkMemoryId, 0, IPC_CREAT | 0666 );
	if( NetworkShmid < 0 )
	{
		trace( "Error in getting Network Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	networktable_ptr = ( struct EzNetworkMemory * ) shmat( NetworkShmid, 0, 0 );

	if( networktable_ptr == NULL )
	{
		trace( "Error in attaching Network Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkSemid = semget( ( key_t ) NetworkMemoryId, 0, IPC_CREAT | 0666 );
	if( NetworkSemid < 0 )
	{
		trace( "Error in getting Network Semaphore...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzUploadCmd :: listNetworkInfo()
{
	struct sembuf sem_buf;
	char NetworkStatusStr[ 50 ];

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%16s%16s", "NetworkId", "ChannelName", "PortName", "Status", "TimeOut" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( networktable_ptr + i )->NetworkId, NETWORKID_INIT_VAL ) )
		{

			memset( NetworkStatusStr, 0, sizeof( NetworkStatusStr ) );

			if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_UP )
				strcpy( NetworkStatusStr, "UP" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_DOWN )
				strcpy( NetworkStatusStr, "DOWN" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAF )
				strcpy( NetworkStatusStr, "SAF" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
				strcpy( NetworkStatusStr, "SAFUPLOAD" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
				strcpy( NetworkStatusStr, "SAFDOWNLOAD" );

			printf( "\n%20s%20s%20s%16s%16d", ( networktable_ptr + i )->NetworkId, ( networktable_ptr + i )->ChannelName, ( networktable_ptr + i )->PortName, NetworkStatusStr, ( networktable_ptr + i )->TimeOut );
		}

		sem_buf.sem_op = 2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return 1;
}

int EzUploadCmd :: listNetworkInfo( const char *NetworkId )
{
	struct sembuf sem_buf;
	char NetworkStatusStr[ 50 ];
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%16s%16s", "NetworkId", "ChannelName", "PortName", "Status", "TimeOut" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( NetworkId, ( networktable_ptr + i )->NetworkId ) )
		{
			retval = 1;
			memset( NetworkStatusStr, 0, sizeof( NetworkStatusStr ) );
			if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_UP )
				strcpy( NetworkStatusStr, "UP" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_DOWN )
				strcpy( NetworkStatusStr, "DOWN" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAF )
				strcpy( NetworkStatusStr, "SAF" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
				strcpy( NetworkStatusStr, "SAFUPLOAD" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
				strcpy( NetworkStatusStr, "SAFDOWNLOAD" );

			printf( "\n%20s%20s%20s%16s%16d", ( networktable_ptr + i )->NetworkId, ( networktable_ptr + i )->ChannelName, ( networktable_ptr + i )->PortName, NetworkStatusStr, ( networktable_ptr + i )->TimeOut );
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return retval;
}

int EzUploadCmd :: searchNetworkInfo( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( networktable_ptr + i )->NetworkId, NetworkId ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzUploadCmd :: uploadPBFfile( const char *NetworkId, char *Filename )
{
	struct EzTxnMsg txnmsg;
	
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	txnmsg.MsgType = 600;	
	strcpy( txnmsg.RsvFld1, Filename );
	strcpy( txnmsg.NetworkId, NetworkId ); 

        if( WriteChannel( ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	return 1;
}

int EzUploadCmd :: serviceUploadCmd( int argc, char **argv )
{
	char command[ 100 ], NetworkId[ 17 ];
	int NetworkStatus;

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezuploadcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "upload" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				else
				{
					if( searchNetworkInfo( command ) < 0 )
					{
						printf("\n invaild Network ..type help for more");
						continue;
					}
					else
					{
						memset( NetworkId, 0, sizeof( NetworkId ) );
						strcpy( NetworkId, command );
					}
				}
				
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				uploadPBFfile( NetworkId, command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					listNetworkInfo();
					continue;
				}
				listNetworkInfo( command );
				continue;
			}
			else if( !strcmp( command, "help" ) )
			{
				printf("\n <upload> <NetworkId> <PBF FileName>");
				printf("\n <list> <NetworkId>");
				printf("\n <list>");
			}
			else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
				break;
			else
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
		}
	}
	else
	{
		memset( command, 0, sizeof( command ) );
		strcpy( command, argv[ 1 ] );
		if( !strcasecmp( command, "upload" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				//updateNetworkInfo( command );
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if ( argc == 2 )
				listNetworkInfo();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				listNetworkInfo( command );
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <upload> <NetworkId> <PBF FileName>");
			printf("\n <list> <NetworkId>");
			printf("\n <list>\n");
		}
		else
		{
			printf("\n invaild command ..type help for more");
		}
	}
}

int main( int argc, char **argv )
{
	EzUploadCmd uploadcmdobj;
	if( uploadcmdobj.initUploadCmd( argv[ 0 ] ) < 0 )
	{
		uploadcmdobj.trace( "^^^^^^^^^^^^^^^EzUploadCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		uploadcmdobj.closeDebug();
		exit( 0 );
	}
	uploadcmdobj.serviceUploadCmd( argc, argv );
	return 1;
}

