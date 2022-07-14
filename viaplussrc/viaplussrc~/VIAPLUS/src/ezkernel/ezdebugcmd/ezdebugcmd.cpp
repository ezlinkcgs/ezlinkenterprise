#include <ezkernel/ezdebugcmd.h>

int EzDebugCmd :: init()
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char debugkeypath[ 100 ], DebugParamName[ 100 ];
	int retval;
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezdebugcmd.log" );

	if( openCmdDebug( logpath, "ezdebugcmd" ) < 0 )
	{
		printf("\n Error in opening file [%s]...ezdebugcmd Exiting\n", logpath );
		exit( 0 );
	}
	trace("~~~~~~~~~~~~~~~~~~ezdebugcmd Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( InitEzTaskUtil( this, 1 ) < 0 )
	{
		printf(	"\nError in Initializing EzTaskUtil\n" );
		trace(	"Error in Initializing EzTaskUtil" );
		exit( 0 );
	}

	if( !IsTaskMgrRunning() )
	{
		printf( "\neztaskmgr is not running..start the ezkernel\n");
		exit( 0 );
	}

	memset( debugkeypath, 0, sizeof( debugkeypath ) );
	sprintf( debugkeypath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezdebug.cfg" );

	if( cfgutil.cfg_open( debugkeypath ) < 0 )
	{
		printf( "\nError in Opening file[%s]\n", debugkeypath );
		exit( 0 );
	}

	memset( DebugParamName, 0, sizeof( DebugParamName ) );
	if( cfgutil.cfg_search( "DEBUGKEY", DebugParamName, 2 ) < 0 )
	{
		printf( "Error in searching DEBUGKEY in debugkeypath[%s]\n", debugkeypath );
		cfgutil.cfg_close();
		exit( 0 );
	}
	DebugKey = atoi( DebugParamName );
	memset( DebugParamName, 0, sizeof( DebugParamName ) );
	if( cfgutil.cfg_search( "MAXDEBUGLEVELENTRY", DebugParamName, 2 ) < 0 )
	{
		printf( "Error in searching MAXDEBUGLEVELENTRY in debugkeypath[%s]\n", debugkeypath );
		cfgutil.cfg_close();
		exit( 0 );
	}
	MAXDEBUGLEVELENTRY = atoi( DebugParamName );
	cfgutil.cfg_close();

	DebugShmId = shmget ( ( key_t ) DebugKey, 0, IPC_CREAT | 0666 );

	if( DebugShmId < 0 )
	{
		printf( "Error in getting DebugLevel Shared Memory..SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		exit( 0 );
	}

	debug_ptr = ( struct EzDebugLevelMemory * ) shmat( DebugShmId, 0, 0 );

	if( debug_ptr == NULL )
	{
		printf( "Error in attaching DebugLevel Shared Memory..SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		exit( 0 );
	}

	DebugSemId = semget ( ( key_t ) DebugKey, 0, IPC_CREAT | 0666 );

	if( DebugSemId < 0 )
	{
		printf( "Error in getting DebugLevel Semaphore..SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		shmdt( debug_ptr );
		exit( 0 );
	}
	return 1;
}

void EzDebugCmd :: ListDebug()
{
	char DebugLevel[ 20 ];
	trace( "Processing List All Debug..." );
	printf( "\n%20s\t\t%15s", "PROCESS NAME", "DEBUG LEVEL" );
	printf( "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" );

	for( int i = 0; i < MAXDEBUGLEVELENTRY; i++ )
	{
		if( strcmp( ( debug_ptr + i )->ProcessName, DEBUG_PROCESS_INIT_NAME ) )
		{
			memset( DebugLevel, 0, sizeof( DebugLevel ) );
			switch ( ( debug_ptr + i )->DebugLevel )
			{
				case DEBUG_CRITICAL:
					strcpy( DebugLevel, "CRITICAL" );
				break;
				case DEBUG_ERROR:
					strcpy( DebugLevel, "ERROR" );
				break;
				case DEBUG_TXN:
					strcpy( DebugLevel, "TXN" );
				break;
				case DEBUG_DUMP:
					strcpy( DebugLevel, "DUMP" );
				break;
				case DEBUG_SECURED:
					strcpy( DebugLevel, "SECURED" );
				break;
				case DEBUG_NORMAL:
					strcpy( DebugLevel, "NORMAL" );
				break;
				case DEBUG_TEST:
					strcpy( DebugLevel, "TEST" );
				break;
				default:
					strcpy( DebugLevel, "NORMAL" );
			}
			printf( "\n%20s\t\t%15s", ( debug_ptr + i )->ProcessName, DebugLevel );
		}
	}
	printf( "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" );
}

void EzDebugCmd :: ListDebug( const char *ProcessName )
{
	char DebugLevel[ 20 ];

	trace( "Processing List Debug[%s]...", ProcessName );
	printf( "\n%20s\t\t%15s", "PROCESS NAME", "DEBUG LEVEL" );
	printf( "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" );

	for( int i = 0; i < MAXDEBUGLEVELENTRY; i++ )
	{
		if( !strcmp( ( debug_ptr + i )->ProcessName, ProcessName ) )
		{
			memset( DebugLevel, 0, sizeof( DebugLevel ) );
			switch ( ( debug_ptr + i )->DebugLevel )
			{
				case DEBUG_CRITICAL:
					strcpy( DebugLevel, "CRITICAL" );
				break;
				case DEBUG_ERROR:
					strcpy( DebugLevel, "ERROR" );
				break;
				case DEBUG_TXN:
					strcpy( DebugLevel, "TXN" );
				break;
				case DEBUG_DUMP:
					strcpy( DebugLevel, "DUMP" );
				break;
				case DEBUG_SECURED:
					strcpy( DebugLevel, "SECURED" );
				break;
				case DEBUG_NORMAL:
					strcpy( DebugLevel, "NORMAL" );
				break;
				case DEBUG_TEST:
					strcpy( DebugLevel, "TEST" );
				break;
				default:
					strcpy( DebugLevel, "NORMAL" );
			}
			printf( "\n%20s\t\t%15s", ( debug_ptr + i )->ProcessName, DebugLevel );
			break;
		}
	}
	printf( "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" );
}

void EzDebugCmd :: getDebugLevel( const char *ProcessName, int *DebugLevel )
{
	char debugpath[ 100 ], DebugString[ 50 ], debugkeypath[ 100 ];
	char DebugParamName[ 50 ];
	EzCfgUtil cfgutil;

	memset( debugpath, 0, sizeof( debugpath ) );
	sprintf( debugpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezdebug.cfg" );

	if( cfgutil.cfg_open( debugpath ) < 0 )
		*DebugLevel = DEBUG_NORMAL;
	else
	{
		memset( DebugString, 0, sizeof( DebugString ) );
		sprintf( DebugString, "%s#%s", "DEBUGLEVEL", ProcessName );
		memset( DebugParamName, 0, sizeof( DebugParamName ) );
		if( cfgutil.cfg_search( DebugString, DebugParamName, 2 ) < 0 )
			*DebugLevel = DEBUG_NORMAL;
		else
		{
			if( !strcasecmp( DebugParamName, "DEBUG_CRITICAL" ) )
				*DebugLevel = DEBUG_CRITICAL;
			else if ( !strcasecmp( DebugParamName, "DEBUG_ERROR") )
				*DebugLevel = DEBUG_ERROR;
			else if ( !strcasecmp( DebugParamName, "DEBUG_TXN") )
				*DebugLevel = DEBUG_TXN;
			else if ( !strcasecmp( DebugParamName, "DEBUG_DUMP") )
				*DebugLevel = DEBUG_DUMP;
			else if ( !strcasecmp( DebugParamName, "DEBUG_SECURED") )
				*DebugLevel = DEBUG_SECURED;
			else if ( !strcasecmp( DebugParamName, "DEBUG_NORMAL") )
				*DebugLevel = DEBUG_NORMAL;
			else if ( !strcasecmp( DebugParamName, "DEBUG_TEST") )
				*DebugLevel = DEBUG_TEST;
			else
				*DebugLevel = DEBUG_NORMAL;
		}
		cfgutil.cfg_close();
	}
}

void EzDebugCmd :: updateDebug( const char *ProcessName )
{
	int DebugLevel, retval = -1;
	getDebugLevel( ProcessName, &DebugLevel );

	trace( "Processing Update Debug for [%s]...", ProcessName );
	struct sembuf sem_buf;
	for( int i = 0; i < MAXDEBUGLEVELENTRY; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( DebugSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return;
		}
		if( !strcmp( ( debug_ptr + i )->ProcessName, ProcessName ) )
		{
			( debug_ptr + i )->DebugLevel = DebugLevel;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( DebugSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( DebugSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return;
		}
	}
	if( retval < 0 )
		printf( "****Update Error for ProcessName[%s]*******\n", ProcessName );
}

void EzDebugCmd :: updateDebug( const char *ProcessName, const char *DebugLevelStr )
{
	int DebugLevel, retval = -1;

	trace( "Processing Update Debug for [%s] with DebugLevel[%s]...", ProcessName, DebugLevel );

	if( !strcasecmp( DebugLevelStr, "CRITICAL" ) )
		DebugLevel = DEBUG_CRITICAL;
	else if( !strcasecmp( DebugLevelStr, "ERROR" ) )
			DebugLevel = DEBUG_ERROR;
	else if( !strcasecmp( DebugLevelStr, "TXN" ) )
			DebugLevel = DEBUG_TXN;
	else if( !strcasecmp( DebugLevelStr, "DUMP" ) )
			DebugLevel = DEBUG_DUMP;
	else if( !strcasecmp( DebugLevelStr, "SECURED" ) )
			DebugLevel = DEBUG_SECURED;
	else if( !strcasecmp( DebugLevelStr, "NORMAL" ) )
			DebugLevel = DEBUG_NORMAL;
	else if( !strcasecmp( DebugLevelStr, "TEST" ) )
			DebugLevel = DEBUG_TEST;
	else
		DebugLevel = DEBUG_NORMAL;

	struct sembuf sem_buf;
	for( int i = 0; i < MAXDEBUGLEVELENTRY; i++ )
	{
		sem_buf.sem_flg = 0;
		sem_buf.sem_num = i;
		sem_buf.sem_op = -2;
		if( semop( DebugSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return;
		}
		if( !strcmp( ( debug_ptr + i )->ProcessName, ProcessName ) )
		{
			( debug_ptr + i )->DebugLevel = DebugLevel;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( DebugSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( DebugSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return;
		}
	}
	if( retval < 0 )
		printf( "****Update Error for ProcessName[%s]*******\n", ProcessName );
}

void EzDebugCmd :: startCmdInterface( int argc, char **argv )
{
	char command[ 100 ];

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezdebugcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					ListDebug();
					continue;
				}
				ListDebug( command );
				continue;
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\ninvalid option..type help for more\n" );
					continue;
				}
				updateDebug( command );
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n<List>");
				printf("\n<List> <ProcessName>");
				printf("\n<Add> <ProcessName>");
				printf("\n<Update> <ProcessName>");
			}
			else if( !strcasecmp( command, "quit" ) )
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
		if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				ListDebug();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				ListDebug( command );
			}
		}
		else if( !strcasecmp( command, "update" ) )
		{
			if( argc == 2 )
			{
				printf("\n invaild command ..type help for more");
				return;
			}
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				updateDebug( command );
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printf("\n<List>");
			printf("\n<List> <ProcessName>");
			printf("\n<Add> <ProcessName>");
			printf("\n<Update> <ProcessName>");
		}
		else if( !strcmp( command, "quit" ) )
			return ;
		else
			printf("\n invaild command ..type help for more");
	}
	printf( "\n" );
}

int main( int argc, char **argv )
{
	EzDebugCmd debugcmd;
	debugcmd.init();
	debugcmd.startCmdInterface( argc, argv );
	return 1;
}
