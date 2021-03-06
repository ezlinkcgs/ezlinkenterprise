#include <ezkernel/eztaskmgr.h>

void *EzTaskMgr :: eztaskmgrobj = 0;

EzTaskMgr :: EzTaskMgr()
{
	eztaskmgrobj = this;
	CurrentTaskCount = 0;
}

EzTaskMgr :: ~EzTaskMgr()
{
}

void EzTaskMgr :: InitEzTaskMgr()
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ], errVal[ ERR_VAL_SIZE + 1 ];
	int retval, OrgKey;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztaskmgr.log" );
	if( openDebug( logpath, "EzTaskMgr" ) < 0 )
	{
		printf("\n Error in opening file [%s]...EzTaskMgr Exiting\n", logpath );
		exit( 0 );
	}
	trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( LoadDebugMemory() < 0 )
	{
		trace( " Error in Loading Debug Memory..." );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		exit( 0 );
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfg_open( cfgpath ) < 0 )
	{
		trace( " Error in opening file [%s] ", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		exit( 0 );
	}

	if( setsid() < 0 )
	{
		trace( "Setting Session ID Failed ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		exit( 0 );
	}

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfg_search( "TASK#MAXTASK", cfgVal, 2 );
	if( retval < 0 )
	{
		trace( " Error in Reading MAXTASK under TASK GROUP from file [%s] ", cfgpath );
		memset( errVal, 0, sizeof( errVal ) );
		cfg_fetch_error( errVal );
		trace( "[%s]", errVal );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfg_close();
		closeDebug();
		exit( 0 );
	}

	MaxTask = atoi( cfgVal );
	trace( " Max Task = [%d] ", MaxTask );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfg_search( "TASK#WAITTIME", cfgVal, 2 );
	if( retval < 0 )
	{
		TaskWaitTime = 100;
		trace( " Error in Reading WAITTIME under TASK GROUP from file [%s] ...Setting Default WaitTime as 100..", cfgpath );
	}
	else
		TaskWaitTime = atoi( cfgVal );

	trace( " TaskWaitTime = [%d] ", TaskWaitTime );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfg_search( "CHANNEL#ORGKEY", cfgVal, 2 );
	if( retval < 0 )
	{
		trace( " Error in Reading ORGKEY under CHANNEL group from file [%s] ", cfgpath );
		memset( errVal, 0, sizeof( errVal ) );
		cfg_fetch_error( errVal );
		trace( "[%s]", errVal );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfg_close();
		closeDebug();
		exit( 0 );
	}

	OrgKey = atoi( cfgVal );
	trace( " OrgKey = [%d] ", MaxTask );

	InitEzTaskMgrUtil( MaxTask, OrgKey, this );

	if( IsTaskMgrAlreadyRunning() )
	{
		printf( "\nEzTaskMgr is Running Already\n"  );
		trace( "EzTaskMgr is Running Already"  );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfg_close();
		closeDebug();
		exit( 0 );
	}

	if( CreateEzTaskMgrChannel() < 0 )
	{
		trace( "Error in Creating EzTaskMgr Channel ....");
		trace( "System Error [%s] ErrNo[%d]", strerror( errno ), errno );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfg_close();
		closeDebug();
		exit( 0 );
	}
	InitTaskTable();
	ListTaskTable();
	setChildSignals( ChildExitHandler );
	setProcessSignals( TaskExitHandler );

}

int EzTaskMgr :: LoadDebugMemory()
{
	char debugkeypath[ 100 ], DebugParamName[ 100 ];
	int MAXDEBUGLEVELENTRY, DebugKey, DebugShmId, DebugSemId;
	struct EzDebugLevelMemory *debug_ptr;
	memset( debugkeypath, 0, sizeof( debugkeypath ) );
	sprintf( debugkeypath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezdebug.cfg" );

	if( cfg_open( debugkeypath ) < 0 )
	{
		trace( "Error in Opening file[%s]", debugkeypath );
		return -1;
	}

	memset( DebugParamName, 0, sizeof( DebugParamName ) );
	if( cfg_search( "DEBUGKEY", DebugParamName, 2 ) < 0 )
	{
		trace( "Error in searching DEBUGKEY in debugkeypath[%s]", debugkeypath );
		return -1;
	}
	DebugKey = atoi( DebugParamName );
	memset( DebugParamName, 0, sizeof( DebugParamName ) );
	if( cfg_search( "MAXDEBUGLEVELENTRY", DebugParamName, 2 ) < 0 )
	{
		trace( "Error in searching MAXDEBUGLEVELENTRY in debugkeypath[%s]", debugkeypath );
		return -1;
	}
	MAXDEBUGLEVELENTRY = atoi( DebugParamName );

	DebugShmId = shmget ( ( key_t ) DebugKey, MAXDEBUGLEVELENTRY * sizeof( struct EzDebugLevelMemory ), IPC_CREAT | 0666 );

	if( DebugShmId < 0 )
	{
		trace( "Error in Creating DebugLevel Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	debug_ptr = ( struct EzDebugLevelMemory * ) shmat( DebugShmId, 0, 0 );

	if( debug_ptr == NULL )
	{
		trace( "Error in attaching DebugLevel Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	DebugSemId = semget ( ( key_t ) DebugKey, MAXDEBUGLEVELENTRY, IPC_CREAT | 0666 );

	if( DebugSemId < 0 )
	{
		trace( "Error in Creating DebugLevel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		shmdt( debug_ptr );
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

	for( int i = 0; i < MAXDEBUGLEVELENTRY; i++ )
	{
		if( semctl( DebugSemId, i, SETVAL, arg ) < 0 )
		{
			trace( "Error in Setting DebugLevel Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MAXDEBUGLEVELENTRY; i++ )
	{
		memset( ( debug_ptr + i ), 0, sizeof( struct EzDebugLevelMemory ) );
		strcpy( ( debug_ptr + i )->ProcessName, DEBUG_PROCESS_INIT_NAME );
	}
	return 1;
}

void EzTaskMgr :: ChildExitHandler( int signo, siginfo_t *siginfo, void *tmp )
{
	EzTaskMgr *eztaskmgrptr = ( EzTaskMgr *) eztaskmgrobj;
	eztaskmgrptr->trace( "Task with TaskId[%d] got Signal[%d] ", siginfo->si_pid, siginfo->si_status );
	eztaskmgrptr->ReStartTask( siginfo->si_pid, siginfo->si_status );
}

void EzTaskMgr :: FreeResources()
{
	trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended normally~~~~~~~~~~~~~~~~~~~~~~~~~~");
	cfg_close();
	closeDebug();
}

void EzTaskMgr :: TaskExitHandler( int signo, siginfo_t *siginfo, void *tmp )
{
	EzTaskMgr *eztaskmgrptr = ( EzTaskMgr *) eztaskmgrobj;
	if( siginfo->si_signo == SIGUSR2 )
		exit( SIGUSR2 );
	eztaskmgrptr->trace( "EzTaskMgr received signal [%d]", signo );
	eztaskmgrptr->StopAllTasks();
	eztaskmgrptr->trace( "cleaning all the allocated resources ....");
	eztaskmgrptr->FreeResources();
	exit( 0 );
}

int EzTaskMgr :: StopAllTasks()
{
	ignoreChildSignals();
	for( int i = 0; i < MaxTask; i++ )
	{
		if( ( strcmp( ( EzTaskMgrShmPtr + i )->TaskName, TASK_INIT_NAME ) ) && ( ( EzTaskMgrShmPtr + i )->TaskId != TASK_INIT_VAL ) )
		{
			trace( "Stopping Task[%s] TaskId[%d]", ( EzTaskMgrShmPtr + i )->TaskName, ( EzTaskMgrShmPtr + i )->TaskId  );
			kill( ( EzTaskMgrShmPtr + i )->TaskId, SIGUSR1 );
		}
	}
	return 1;
}

bool EzTaskMgr :: IsValidTask( const char *TaskPath, const char *TaskName )
{
	DIR *dirname;
	struct dirent *rdir;
	bool dirfound = false;
	dirname = opendir( TaskPath );
	if( dirname == NULL )
	{
		trace( "Error in Opening BIN Directory[%s]", TaskPath );
		return dirfound;
	}

	while( ( rdir = readdir( dirname ) ) != NULL )
	{
		if( !strcmp( rdir->d_name, TaskName ) )
		{
			dirfound = true;
			break;
		}
	}
	closedir( dirname );
	return dirfound;
}

int EzTaskMgr :: StartTask( const char *TaskName )
{
	int TaskId, retval;
	char taskpath[ BIN_PATH_SIZE + 1 ];

	trace( "Starting Task[%s]", TaskName );

	if( CurrentTaskCount >= MaxTask )
	{
		trace( "Cannot Start Task[%s]", TaskName );
		trace( "No. of Tasks reached Max Task[%d] ", MaxTask );
		return -1;
	}
	memset( taskpath, 0, sizeof( taskpath ) );
	sprintf( taskpath, "%s/%s", getenv( "EZDIR_HOME" ), "bin" );

	if( !IsValidTask( taskpath, TaskName ) )
	{
		trace( "TaskName[%s] does not exist in path[%s] Cannot Start Task", TaskName, taskpath );
		return -1;
	}

	while( 1 )
	{
		TaskId = fork();
		if( TaskId < 0 )
		{
			trace( "Error in starting Task[%s] Fork Error..System Error[%s] ErrNo[%d]...", TaskName, strerror( errno ), errno );
			return -1;
		}

		if( TaskId == 0 )
		{
			trace( "TaskId[%d] waiting for Parent...", getpid() );
			WaitForParent();
			trace( "TaskId[%d] Invoking Parent...", getpid() );
			InvokeParent();
			memset( taskpath, 0, sizeof( taskpath ) );
			sprintf( taskpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "bin", TaskName );
			retval = execl( taskpath, TaskName, NULL, NULL );
			trace( "Return Value of execl = [%d]", retval );
			if( retval < 0 )
			{
				trace( "Error in Starting Task[%s]... execl failed SysErr[%s] ErrNo[%d]", TaskName, strerror( errno ), errno );
				if( SendTaskInitErr( getpid() ) < 0 )
					trace( "Error in Sending Task Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				exit( STOP_SIGNALNO );
			}
		}
		else
		{
			if( AddTaskTable( TaskName, TaskId ) < 0 )
			{
				trace( "Error in Adding TaskId[%d] in TaskTable...", TaskId );
				return -1;
			}
			trace( "Added TaskId[%d] in TaskTable", TaskId );
			InvokeChild();
			trace( "Waiting for Child[%d]...", TaskId );
			WaitForChild();
			trace( "Waiting for Task[%s] with TaskId[%d] to initialize ...", TaskName, TaskId );
			retval = WaitForTask( TaskId );
			usleep( TaskWaitTime );
			if( retval == -1 )
			{
				trace( "Error in initializing Task[%s] with TaskId[%d] ", TaskName, TaskId );
				return -1;
			}
			else if( retval == 0 )
			{
				trace( "Error in Starting Task[%s] with TaskId[%d] ", TaskName, TaskId );
				RemoveTaskTable( TaskId );
				kill( TaskId, SIGKILL );
				continue;
			}
			else
			{
				trace( "Task[%s] initilaized Successfully", TaskName );
				CurrentTaskCount++;
				break;
			}
		}
	}
	return 1;
}

int EzTaskMgr :: ReStartTask( int TaskId, int SigNo )
{
	char TaskName[ TASKNAME_SIZE + 1 ];

	int TaskState, TaskStatus, retval;

	trace( "Waiting for TaskId[%d]", TaskId );
	TaskState = waitpid( TaskId, &TaskStatus, WNOHANG );

	trace( "Locating TaskId[%d]", TaskId );

	memset( TaskName, 0, sizeof( TaskName ) );
	if( LocateTaskTable( TaskId, TaskName ) < 0 )
	{
		trace( "Error in Locating TaskId[%d] in TaskTable...Cannot Restart Task", TaskId );
		return -1;
	}

	trace( "Located TaskId[%d] with TaskName[%s]", TaskId, TaskName );

	/*
	if( !IsTaskInitialized( TaskId ) )
	{
		if( SendTaskInitErr( TaskId ) < 0 )
			trace( "Error in Sending Task Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	}
	*/

	RemoveTaskTable( TaskId );
	trace( "TaskStatus[%d]", TaskStatus );

	if( WEXITSTATUS( TaskStatus ) == STOP_SIGNALNO || SigNo == STOP_SIGNALNO )
	{
		trace( "Task[%s] with TaskId[%d] Got Terminated with Signal[%d]", TaskName, TaskId, STOP_SIGNALNO );
		return 1;
	}
	else
	{
		trace( "Task[%s] with TaskId[%d] Got Signal[%d]", TaskName, TaskId, SigNo );
		//ListTaskTable();
		trace( "Restarting Task[%s]", TaskName );
		retval = StartTask( TaskName );
		if( retval < 0 )
			trace( "Error in Starting Task[%s]", TaskName );
		else
			trace( "Started Task[%s] Successfully", TaskName );
	}
	return 1;
}

int EzTaskMgr :: StopTask( const char *TaskName )
{
	int TaskId;
	trace( "Stopping Task[%s]", TaskName );
	TaskId = LocateTaskTable( TaskName );
	if( TaskId < 0 )
	{
		trace( "Cannot Stop Task[%s]...Error Locating Task in TaskTable", TaskName );
		return -1;
	}
	kill( TaskId, SIGUSR1 );
	RemoveTaskTable( TaskId );
	CurrentTaskCount--;
	return 1;
}

int EzTaskMgr :: StartGroup( const char *TaskGroup )
{
	char GroupName[ GROUP_NAME_SIZE + 1 ], errVal[ ERR_VAL_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ];
	int GroupCount = 0, retval;

	trace( "Starting Group[%s]", TaskGroup );

	memset( GroupName, 0, sizeof( GroupName ) );
	sprintf( GroupName, "%s#%s", "TASK", TaskGroup );
	GroupCount = cfg_group_count( GroupName );
	trace( "Group Count=[%d]", GroupCount );

	if( GroupCount < 0 )
	{
		trace( "Error in Reading Group[%s] ", GroupName );
		memset( errVal, 0, sizeof( errVal ) );
		cfg_fetch_error( errVal );
		trace( "ErrVal = [%s]", errVal );
		return -1;
	}
	for( int i = 0; i < GroupCount; i++ )
	{
		if( cfg_get_param( GroupName, cfgVal, i + 1 ) < 0 )
		{
			trace( "Error in Reading Group [%s]", GroupName );
			memset( errVal, 0, sizeof( errVal ) );
			cfg_fetch_error( errVal );
			trace( "ErrVal = [%s]", errVal );
			return -1;
		}
		retval = StartTask( cfgVal );
		if( retval < 0 )
			trace( "Error in Starting Task[%s]", cfgVal );
	}
	return 1;
}

bool EzTaskMgr :: IsKernelTask( const char *TaskName )
{
	if( ( !strcmp( TaskName, "EzChannelMgr" ) ) || ( !strcmp( TaskName, "EzCommMgr" ) ) || ( !strcmp( TaskName, "EzEventMgr" ) ) || ( !strcmp( TaskName, "EzMsgRouter" ) ) || ( !strcmp( TaskName, "EzDBLoadMgr" ) ) || ( !strcmp( TaskName, "EzEventPoolMgr" ) ) )
		return true;
	else
		return false;
}

void EzTaskMgr :: ServiceRequest()
{
	struct EzTaskCmdMsg cmdmsg;
	char errVal[ ERR_VAL_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ];
	int GroupCount = 0, retval;

	GroupCount = cfg_group_count( "TASK#EZTASKGROUP" );
	trace( "Group Count=[%d]", GroupCount );

	if( GroupCount < 0 )
	{
		trace( "Error in Reading Group[%s] ", "TASK#EZTASKGROUP" );
		trace( "~~~~~~~~~~~~~~~~~~EzTaskMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		exit( 0 );
	}

	for( int i = 0; i < GroupCount; i++ )
	{
		if( cfg_get_param( "TASK#EZTASKGROUP", cfgVal, i + 1 ) < 0 )
		{
			trace( "Error in Reading Group [%s]", "TASK#EZTASKGROUP" );
			memset( errVal, 0, sizeof( errVal ) );
			cfg_fetch_error( errVal );
			trace( "ErrVal = [%s]", errVal );
		}
		StartGroup( cfgVal );
	}

	while( 1 )
	{
		trace( "EzTaskMgr Waiting for request .....");
		if( WaitForTaskCommandRequest( &cmdmsg ) < 0 )
		{
			if ( errno == EINTR )
				continue;
			else
			{
				trace( "Error While Waiting for Request SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				StopAllTasks();
				FreeResources();
				exit( 0 );
			}

		}
		switch ( cmdmsg.Command )
		{
			case TASK_START:

			if( !strcmp( cmdmsg.TaskName, "EzCommMgr" ) )
			{
				trace( "Cannot Start Kernel Task %s", cmdmsg.TaskName );
				cmdmsg.Response = -1;
				SendTaskCommandResponse( cmdmsg );
			}
			else
			{
				retval = StartTask( cmdmsg.TaskName );
				if( retval < 0 )
				{
					trace( "Cannot Start Task[%s]", cmdmsg.TaskName );
					cmdmsg.Response = -1;
					SendTaskCommandResponse( cmdmsg );
				}
				else if( retval > 0 )
				{
					trace( "Started Task[%s] Sucessfully", cmdmsg.TaskName );
					cmdmsg.Response = 1;
					SendTaskCommandResponse( cmdmsg );
				}
			}
			break;

			case TASK_STOP:

			if( IsKernelTask( cmdmsg.TaskName ) )
			{
				trace( "Cannot Stop Kernel Task %s", cmdmsg.TaskName );
				cmdmsg.Response = -1;
				SendTaskCommandResponse( cmdmsg );
			}
			else
			{
				if( StopTask( cmdmsg.TaskName ) < 0 )
				{
					trace( "Cannot Stop Task[%s]", cmdmsg.TaskName );
					cmdmsg.Response = -1;
					SendTaskCommandResponse( cmdmsg );
				}
				else
				{
					trace( "Stopped Task[%s] Sucessfully", cmdmsg.TaskName );
					cmdmsg.Response = 1;
					SendTaskCommandResponse( cmdmsg );
				}
			}
			break;

			default:
			trace( " Invalid Command Request....");
		}
	}
}

int main()
{
	if( getenv( "EZDIR_HOME" ) == NULL )
	{
		printf("\n EZDIR_HOME environment variable is not set in the .profile directory...");
		printf("\n Pl. check the installation \n");
		exit( 0 );
	}
	if( fork() != 0 )
		exit( 0 );
	EzTaskMgr eztaskmgr;
	eztaskmgr.InitEzTaskMgr();
	eztaskmgr.ServiceRequest();
	return 1;
}
