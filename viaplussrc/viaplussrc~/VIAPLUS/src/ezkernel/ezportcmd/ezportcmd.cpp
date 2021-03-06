#include <ezkernel/ezportcmd.h>

EzPortCmd :: EzPortCmd()
{
}

EzPortCmd :: ~EzPortCmd()
{
}

int EzPortCmd :: init()
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	int retval;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezportcmd.log" );
	if( openCmdDebug( logpath, "ezportcmd" ) < 0 )
	{
		printf("\n Error in opening file [%s]...ezportcmd Exiting\n", logpath );
		exit( 0 );
	}
	trace( "~~~~~~~~~~~~~~~~~~ezportcmd Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( InitEzCommUtil( this ) < 0 )
	{
		printf("\n Error in Initializing CommUtil\n");
		trace( "Error in Initialzing EzCommUtil" );
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		printf("\n Error in Initializing ChannelUtil\n");
		trace( "Error in Initialzing ChannelUtil" );
		exit( 0 );
	}

	if( createDummyChannel( "ezportcmd" ) < 0 )
	{
		printf("\n Error in Creating Dummy Channel ezportcmd\n");
		trace( "Error in Creating Dummy Channel ezportcmd" );
		exit( 0 );
	}
	return 1;
}

int EzPortCmd :: ListAllPort()
{
	struct sembuf sem_buf;
	char ConnStatus[ 50 ], ConnType[ 50 ];

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%15s%10s%10s%10s%20s", "PORTNAME", "IPADRESS", "PORTNO", "APPTYPE", "PORTID", "PORTSTATUS" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < GetMaxPort(); i++ )
	{
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace( " Error in semop operation ...");
			trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}

		memset( ConnType, 0, sizeof( ConnType ) );
		if( ( EzCommMgrShmptr + i )->ApplType == TCPIP_SERVER )
			strcpy( ConnType, "SERVER" );
		else
			strcpy( ConnType, "CLIENT" );

		memset( ConnStatus, 0, sizeof( ConnStatus ) );
		if( ( EzCommMgrShmptr + i )->PortStatus == PORT_INIT )
			strcpy( ConnStatus, "INIT" );
		else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_STOPPED )
			strcpy( ConnStatus, "STOPPED" );
		else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_LISTEN )
			strcpy( ConnStatus, "LISTEN" );
		else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_TRYING )
			strcpy( ConnStatus, "TRY_CONNECT" );
		else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_CONNECTED )
			strcpy( ConnStatus, "CONNECTED" );
		if ( ( strcmp( ( EzCommMgrShmptr + i )->PortName, PORT_INIT_NAME ) ) && ( ( EzCommMgrShmptr + i )->PortId != PORT_INIT_VAL ) )
			printf( "\n%20s%15s%10d%10s%10d%20s", ( EzCommMgrShmptr + i )->PortName, ( EzCommMgrShmptr + i )->IpAddress, (EzCommMgrShmptr + i )->PortNo, ConnType, ( EzCommMgrShmptr + i )->PortId, ConnStatus );
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace( " Error in semop operation ...");
			trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n");
	return 1;
}

int EzPortCmd :: ListPort( const char *PortName )
{
	struct sembuf sem_buf;
	char ConnStatus[ 50 ], ConnType[ 50 ];

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%15s%10s%10s%10s%20s", "PORTNAME", "IPADRESS", "PORTNO", "APPTYPE", "PORTID", "PORTSTATUS" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < GetMaxPort(); i++ )
	{
		sem_buf.sem_flg = SEM_UNDO;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace( " Error in semop operation ...");
			trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
		if ( !strcmp( ( EzCommMgrShmptr + i )->PortName, PortName ) )
		{
			memset( ConnType, 0, sizeof( ConnType ) );
			if( ( EzCommMgrShmptr + i )->ApplType == TCPIP_SERVER )
				strcpy( ConnType, "SERVER" );
			else
				strcpy( ConnType, "CLIENT" );

			memset( ConnStatus, 0, sizeof( ConnStatus ) );
			if( ( EzCommMgrShmptr + i )->PortStatus == PORT_INIT )
				strcpy( ConnStatus, "INIT" );
			else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_STOPPED )
				strcpy( ConnStatus, "STOPPED" );
			else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_LISTEN )
				strcpy( ConnStatus, "LISTEN" );
			else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_TRYING )
				strcpy( ConnStatus, "TRY_CONNECT" );
			else if( ( EzCommMgrShmptr + i )->PortStatus == PORT_CONNECTED )
				strcpy( ConnStatus, "CONNECTED" );

			printf( "\n%20s%15s%10d%10s%10d%20s", ( EzCommMgrShmptr + i )->PortName, ( EzCommMgrShmptr + i )->IpAddress, (EzCommMgrShmptr + i )->PortNo, ConnType, ( EzCommMgrShmptr + i )->PortId, ConnStatus );
			sem_buf.sem_op = 2;
			if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
			{
				trace( " Error in semop operation ...");
				trace( " Sys Error [%s] ", strerror( errno ) );
				return -1;
			}
		}
		sem_buf.sem_op = 2;
		if( semop( EzCommMgrSemid, &sem_buf, 1 ) < 0 )
		{
			trace( " Error in semop operation ...");
			trace( " Sys Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf("\n");
	return 1;
}

void EzPortCmd :: startCmdInterface( int argc, char **argv )
{
	char command[ 100 ];

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezportcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			else if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				AddPort( command );
				continue;
			}
			else if( !strcasecmp( command, "start" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				StartPort( command );
				continue;
			}
			else if( !strcasecmp( command, "stop" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				StopPort( command );
				continue;
			}
			else if( !strcasecmp( command, "remove" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				RemovePort( command );
				continue;
			}
			else if( !strcasecmp( command, "debug-on" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( WritePortChannel( command, "debug-on", 8 ) < 0 )
					trace( "Error in writing debug-on message to port[%s]", command );
				continue;
			}
			else if( !strcasecmp( command, "debug-off" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( WritePortChannel( command, "debug-off", 9 ) < 0 )
					trace( "Error in writing debug-off message to port[%s]", command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					ListAllPort();
					continue;
				}
				ListPort( command );
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n <add> <PortName>");
				printf("\n <start> <PortName>");
				printf("\n <stop> <PortName>");
				printf("\n <remove> <PortName>");
				printf("\n <debug-on> <PortName>");
				printf("\n <debug-off> <PortName>");
				printf("\n <list> <PortName>");
				printf("\n <list>");
			}
			else if( !strcasecmp( command, "quit" ) || !strcasecmp( command, "exit" ) )
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
		if( !strcasecmp( command, "start" ) )
		{
			if( argc != 3 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				StartPort( command );
			}
		}
		else if( !strcasecmp( command, "add" ) )
		{
			if( argc != 3 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				AddPort( command );
			}
		}
		else if( !strcasecmp( command, "stop" ) )
		{
			if( argc != 3 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				StopPort( command );
			}
		}
		else if( !strcasecmp( command, "debug-on" ) )
		{
			if( argc != 3 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				if( WritePortChannel( command, "debug-on", 8 ) < 0 )
					trace( "Error in writing debug-on message to port[%s]", command );
			}
		}
		else if( !strcasecmp( command, "debug-off" ) )
		{
			if( argc != 3 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				if( WritePortChannel( command, "debug-off", 9 ) < 0 )
					trace( "Error in writing debug-off message to port[%s]", command );
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				ListAllPort();
			else
			{
				if( argc != 3 )
					printf("\n invaild command ..type help for more");
				else
				{
					memset( command, 0, sizeof( command ) );
					strcpy( command, argv[ 2 ] );
					ListPort( command );
				}
			}
		}
		else if( !strcasecmp( command, "help" ) )
		{
			printf("\n <add> <PortName>");
			printf("\n <start> <PortName>");
			printf("\n <stop> <PortName>");
			printf("\n <remove> <PortName>");
			printf("\n <debug-on> <PortName>");
			printf("\n <debug-off> <PortName>");
			printf("\n <list> <PortName>");
			printf("\n <list>");
		}
		else if( !strcasecmp( command, "quit" ) || !strcasecmp( command, "exit" ) )
			return ;
		else
			printf("\n invaild command ..type help for more");

		printf( "\n" );
	}
}

int main( int argc, char **argv )
{
	EzPortCmd portcmd;
	portcmd.init();
	portcmd.startCmdInterface( argc, argv );
	return 1;
}
