#include <ezkernel/eztaskcmd.h>

EzTaskCmd :: EzTaskCmd()
{
}

EzTaskCmd :: ~EzTaskCmd()
{
}

int EzTaskCmd :: init()
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	int retval;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztaskcmd.log" );
	if( openCmdDebug( logpath, "eztaskcmd" ) < 0 )
	{
		printf("\n Error in opening file [%s]...eztaskcmd Exiting\n", logpath );
		exit( 0 );
	}
	trace("~~~~~~~~~~~~~~~~~~eztaskcmd Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

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

	return 1;

}

int EzTaskCmd :: ListAllTask()
{
	char TaskStatus[ 20 ];
	printf("\n%20s%10s%15s%15s%15s", "TASKNAME", "TASKID", "STATUS", "STARTDATE", "STARTTIME" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	for( int i = 0; i < GetMaxTask(); i++ )
	{
		memset( TaskStatus, 0, sizeof( TaskStatus ) );
		if( ( EzTaskMgrShmPtr + i )->TaskStatus == TASK_RUNNING )
			strcpy( TaskStatus, "RUNNING" );
		else
			strcpy( TaskStatus, "INIT" );

		if ( ( strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TASK_INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + i )->TaskId != TASK_INIT_VAL ) )
			printf( "\n%20s%10d%15s%15s%15s", ( EzTaskMgrShmPtr + i )->TaskName, ( EzTaskMgrShmPtr + i )->TaskId, TaskStatus, ( EzTaskMgrShmPtr + i )->StartDate, ( EzTaskMgrShmPtr + i )->StartTime );
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n");
	return 1;
}

int EzTaskCmd :: ListTask( const char *TaskName )
{
	char TaskStatus[ 20 ];
	printf("\n%20s%10s%15s%15s%15s", "TASKNAME", "TASKID", "STATUS", "STARTDATE", "STARTTIME" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	for( int i = 0; i < GetMaxTask(); i++ )
	{
		if ( !strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TaskName ) )
		{
			memset( TaskStatus, 0, sizeof( TaskStatus ) );
			if( ( EzTaskMgrShmPtr + i )->TaskStatus == TASK_RUNNING )
				strcpy( TaskStatus, "RUNNING" );
			else
				strcpy( TaskStatus, "INIT" );
			printf( "\n%20s%10d%15s%15s%15s", ( EzTaskMgrShmPtr + i )->TaskName, ( EzTaskMgrShmPtr + i )->TaskId, TaskStatus, ( EzTaskMgrShmPtr + i )->StartDate, ( EzTaskMgrShmPtr + i )->StartTime );
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("\n");
	return -1;
}

void EzTaskCmd :: startCmdInterface( int argc, char **argv )
{
	char command[ 100 ];

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\neztaskcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "start" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				StartTask( command );
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
				StopTask( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					ListAllTask();
					continue;
				}
				ListTask( command );
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n++++++++++++++++++++++++++++++++++++++++++");
				printf("\n <start> 	<TaskName>");
				printf("\n <stop> 	<TaskName>");
				printf("\n <list> 	<TaskName>");
				printf("\n <list>");
				printf("\n++++++++++++++++++++++++++++++++++++++++++\n");
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
		trace( "command = [%s]", command );
		if( !strcasecmp( command, "start" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				StartTask( command );
			}
		}
		else if( !strcasecmp( command, "stop" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				StopTask( command );
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				ListAllTask();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				ListTask( command );
			}
		}
		else if( !strcasecmp( command, "help" ) )
		{
			printf("\n++++++++++++++++++++++++++++++++++++++++++");
			printf("\n <start> 	<TaskName>");
			printf("\n <stop> 	<TaskName>");
			printf("\n <list> 	<TaskName>");
			printf("\n <list>");
			printf("\n++++++++++++++++++++++++++++++++++++++++++\n");
		}
		else if( !strcasecmp( command, "quit" ) || !strcasecmp( command, "exit" ) )
			return ;
		else
			printf("\n invaild command ..type help for more\n");
	}
}

int main( int argc, char **argv )
{
	EzTaskCmd tskcmd;
	tskcmd.init();
	tskcmd.startCmdInterface( argc, argv );
	return 1;
}
