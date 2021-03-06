#include <ezkernel/ezcommmgr.h>

void *EzCommMgr :: ezcommmgrobj = 0;

EzCommMgr :: EzCommMgr()
{
	ezcommmgrobj = this;
	CurrentTaskCount = 0;
}

EzCommMgr :: ~EzCommMgr()
{
}

void EzCommMgr :: InitEzCommMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ], errVal[ ERR_VAL_SIZE + 1 ];
	struct sembuf sem_buf;
	int retval, OrgKey;

	EzCfgUtil cfgutil;

	CurrentTaskCount = 0;

	TaskMgrPid = getppid();
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezcommmgr.log" );
	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );
	trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error Initializing EzTaskUtil.... ");
	    trace( "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		exit( 0 );
	}

	setChildSignals( ChildExitHandler );
	setProcessSignals( ProcessExitHandler );

	if( IsTaskRunning( TaskName ) >=0 )
	{
		trace( "Already One Instance of EzCommMgr is Running");
        trace( "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace(  " Error in opening file [%s] ", cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "PORT#MAXPORT", cfgVal, 2 );
	if( retval < 0 )
	{
		trace(  " Error in Reading MAXPORT under PORT GROUP from file [%s] ", cfgpath );
		memset( errVal, 0, sizeof( errVal ) );
		cfgutil.cfg_fetch_error( errVal );
		trace(  "[%s]", errVal );
		trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	MaxPort = atoi( cfgVal );
	trace(  "Max Port=[%d]", MaxPort );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "PORT#WAITTIME", cfgVal, 2 );
	if( retval < 0 )
	{
		trace(  " Error in Reading WAITTIME under PORT GROUP from file [%s]...Setting Default Value as 100... ", cfgpath );
		PortWaitTime = 100;
	}
	else
		PortWaitTime = atoi( cfgVal );

	trace(  "PortWaitTime=[%d]", PortWaitTime );


	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "CHANNEL#ORGKEY", cfgVal, 2 );
	if( retval < 0 )
	{
		trace(  " Error in Reading ORGKEY under CHANNEL GROUP from file [%s] ", cfgpath );
		memset( errVal, 0, sizeof( errVal ) );
		cfgutil.cfg_fetch_error( errVal );
		trace(  "[%s]", errVal );
		trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	OrgKey = atoi( cfgVal );
	trace(  "OrgKey=[%d]", OrgKey );

	cfgutil.cfg_close();

	if( InitEzCommMgrUtil( this, MaxPort, OrgKey ) < 0 )
	{
		trace(  " Error in Initializing EzCommMgrUtil" );
		trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( CreateEzCommMgrQueue() < 0 )
	{
		trace(  "Error in Creating EzCommMgr Queue....");
		trace(  "System Error [%s] ", strerror( errno ) );
		trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	trace( "CommMgr Queue Created");

	if( CreateEzCommMgrSharedMemory() < 0 )
	{
		trace(  " Error in Creating EzCommMgr Shared Mrmory....");
		trace(  " System Error [%s] ", strerror( errno ) );
		trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	InitCommTable();
}

void EzCommMgr :: ChildExitHandler( int signo, siginfo_t *siginfo, void *tmp )
{
	EzCommMgr *ezcommmgrptr = ( EzCommMgr *) ezcommmgrobj;
	waitpid( siginfo->si_pid, NULL, WNOHANG );
	ezcommmgrptr->trace(  "Port with PortId[%d] got Signal[%d]", siginfo->si_pid, siginfo->si_signo );

	if( siginfo->si_status != STOP_SIGNALNO )
	{
		ezcommmgrptr->trace(  "Restarting Port with PortId[%d] ", siginfo->si_pid );
		ezcommmgrptr->ReStartPort( siginfo->si_pid );
	}
	else
	{
		ezcommmgrptr->trace(  "PortId [%d] Terminated ...", siginfo->si_pid );
	}
}

void EzCommMgr :: FreeResources()
{
	trace(  "~~~~~~~~~~~~~~~~~~EzCommMgr Ended normally~~~~~~~~~~~~~~~~~~~~~~~~~~");
	closeDebug();
}

void EzCommMgr :: ProcessExitHandler( int signo, siginfo_t *siginfo, void *tmp )
{
	struct sembuf sem_buf;

	EzCommMgr *ezcommmgrptr = ( EzCommMgr *) ezcommmgrobj;
	ezcommmgrptr->trace(  "EzCommMgr received signal [%d] from pid[%d] getppid[%d] TaskMgrPid[%d]", signo, siginfo->si_pid, getppid(), ezcommmgrptr->TaskMgrPid );
	ezcommmgrptr->trace(  " cleaning all the allcated resources ....");
	if( siginfo->si_pid == ezcommmgrptr->TaskMgrPid )
	{
		ezcommmgrptr->trace(  "Received signal from EzTaskMgr");
		ezcommmgrptr->StopAllPort();
		ezcommmgrptr->TaskExit();
	}
	else
	{
		ezcommmgrptr->FreeResources();
		exit( 0 );
	}
}

void EzCommMgr :: StopAllPort()
{
	for( int i = 0; i < MaxPort; i++ )
	{
		if( strcmp( ( EzCommMgrShmPtr + i )->PortName, PORT_INIT_NAME ) )
		{
			trace( "Stopping Port with PortId[%d]", ( EzCommMgrShmPtr + i )->PortId );
			kill( ( EzCommMgrShmPtr + i )->PortId, SIGUSR1 );
		}
	}
}

int EzCommMgr :: StartConfiguredPorts()
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], PortName[ PORT_NAME_SIZE + 1 ];;
	char PortPath[ PORT_PATH_SIZE + 1 ];
	int PortCount, PortId, retval;
	EzCfgUtil cfgutil;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
        trace( "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
        closeDebug();
		TaskExit();
	}

	PortCount = cfgutil.cfg_group_count( "DRIVER" );

	if( PortCount < 0 )
	{
		trace( "Error in Searching Group DRIVER in File[%s]", cfgpath );
		cfgutil.cfg_close();
        trace( "~~~~~~~~~~~~~~~~~~EzCommMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	TaskInit();

	trace( "Port Count=[%d]", PortCount );

	for( int i = 0; i < PortCount; i++ )
	{
		memset( PortName, 0, sizeof( PortName ) );
		if( cfgutil.cfg_get_param( "DRIVER", PortName, i + 1 ) < 0 )
		{
			trace( "Error in Searching Group DRIVER in File[%s]", cfgpath );
			continue;
		}
		if( cfgutil.cfg_group_count( PortName ) < 0 )
		{
			trace( "Cannot Start Port[%s] ....Error in Searching Group[%s_START_DEF] in File[%s]", PortName, PortName, cfgpath );
			continue;
		}
		if( CurrentTaskCount >= MaxPort )
		{
			trace( "Error in Starting Port[%s]...No. of Ports Exceeded Max Ports", PortName );
			break;
		}
		/*
		if( LocateCommTable( PortName ) >= 0 )
		{
			trace( "Error in Starting Port[%s]...Port Already Started...Check for PortName Duplication in File[%s]", PortName, cfgpath );
			continue;
		}
		*/

		while( 1 )
		{
			PortId = fork();
			if( PortId < 0 )
			{
				trace( "Error in Fork System Call...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			if( PortId == 0 )
			{
				trace( "TaskId[%d] waiting for Parent...", getpid() );
				WaitForParent();
				trace( "TaskId[%d] Invoking Parent...", getpid() );
				InvokeParent();
				memset( PortPath, 0, sizeof( PortPath ) );
				sprintf( PortPath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "bin", "EzCommDriver" );
				trace( "PortPath[%s] PortName[%s]", PortPath, PortName );
				if( execl( PortPath, "EzCommDriver", PortName, NULL, NULL ) < 0 )
				{
					trace(  " Error in Starting Port[%s] ... execl failed...SysErr[%s] ErrNo[%d]", PortName, strerror( errno ), errno );
					if( SendCommInitErr( getpid() ) < 0 )
						trace( "Error in Sending Comm Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					exit( STOP_SIGNALNO );
				}
			}
			else
			{
				AddCommTable( PortName, PortId );
				trace( "Added TaskId[%d] in TaskTable", PortId );
				InvokeChild();
				trace( "Waiting for Child[%d]...", PortId );
				WaitForChild();
				trace( "Waiting for Port[%s] with PortId[%d] to initialize ...", PortName, PortId );
				retval = WaitForPort( PortId );
				//usleep( PortWaitTime );
				if( retval == -1 )
				{
					trace( "Error in initializing Port[%s] with PortId[%d] ", PortName, PortId );
					break;
				}
				else if( retval == 0 )
				{
					trace( "Error in Starting Port[%s] with PortId[%d] ", PortName, PortId );
					RemoveCommTable( PortId );
					kill( PortId, SIGKILL );
					continue;
				}
				else
				{
					CurrentTaskCount++;
					trace( "Port[%s] initilaized Successfully", PortName );
					break;
				}
			}
		}
	}
	cfgutil.cfg_close();

	return 1;
}


int EzCommMgr :: AddPort( const char *PortName )
{
	int retval;

	EzCfgUtil cfgutil;
	char PortPath[ PORT_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	int PortId;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	if( cfgutil.cfg_group_count( PortName ) < 0 )
	{
		trace( "Cannot Start Port[%s] ....Error in Searching Group[%s_START_DEF] in File[%s]", PortName, PortName, cfgpath );
		return -1;
	}

	cfgutil.cfg_close();

	if( CurrentTaskCount >= MaxPort )
	{
		trace( "Error in Starting Port[%s]...No. of Ports Exceeded Max Ports", PortName );
		return -1;
	}
	if( LocateCommTable( PortName ) >= 0 )
	{
		trace( "Error in Starting Port[%s]...Already Started...Check for PortName Duplication in File[%s]", PortName, cfgpath );
		return -1;
	}

	while( 1 )
	{
		PortId = fork();
		if( PortId < 0 )
		{
			trace( "Error in Fork System Call...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			break;
		}
		if( PortId == 0 )
		{
			trace( "TaskId[%d] waiting for Parent...", getpid() );
			WaitForParent();
			trace( "TaskId[%d] Invoking Parent...", getpid() );
			InvokeParent();
			memset( PortPath, 0, sizeof( PortPath ) );
			sprintf( PortPath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "bin", "EzCommDriver" );
			if( execl( PortPath, "EzCommDriver", PortName, NULL, NULL ) < 0 )
			{
				trace(  " Error in Starting Port[%s] ... execl failed...SysErr[%s] ErrNo[%d]", PortName, strerror( errno ), errno );
				if( SendCommInitErr( getpid() ) < 0 )
					trace( "Error in Sending Comm Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				exit( STOP_SIGNALNO );
			}
		}
		else
		{
			AddCommTable( PortName, PortId );
			trace( "Added TaskId[%d] in TaskTable", PortId );
			InvokeChild();
			trace( "Waiting for Child[%d]...", PortId );
			WaitForChild();
			trace( "Waiting for Port[%s] with PortId[%d] to initialize ...", PortName, PortId );
			retval = WaitForPort( PortId );
			//usleep( PortWaitTime );
			if( retval == -1 )
			{
				trace( "Error in initializing Port[%s] with PortId[%d] ", PortName, PortId );
				break;
			}
			else if( retval == 0 )
			{
				trace( "Error in Starting Port[%s] with PortId[%d] ", PortName, PortId );
				RemoveCommTable( PortId );
				kill( PortId, SIGKILL );
				continue;
			}
			else
			{
				trace( "Port[%s] initilaized Successfully", PortName );
				CurrentTaskCount++;
				break;
			}
		}
	}
	return 1;
}


int EzCommMgr :: StartPort( const char *PortName )
{
	int PortId, retval;
	char cfgVal[ CFG_VAL_SIZE + 1 ], PortPath[ PORT_PATH_SIZE + 1 ];

	trace( "Starting Port [%s]", PortName );

	if( LocateCommTable( PortName ) < 0 )
	{
		trace( "Cannot Start Port[%s]..Unable to Locate in CommTable", PortName );
		return -1;
	}

	if( !IsPortStopped( PortName ) )
	{
		trace( "Cannot Start Port[%s]..Port is not Stopped", PortName );
		return -1;
	}

	while( 1 )
	{
		PortId = fork();
		if( PortId < 0 )
		{
			trace( "Error In Forking Process SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			break;
		}
		if( PortId == 0 )
		{
			memset( PortPath, 0, sizeof( PortPath ) );
			sprintf( PortPath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "bin", "EzCommDriver" );
			retval = execl( PortPath, "EzCommDriver", PortName, NULL, NULL );
			if( retval < 0 )
			{
				trace( "Error in Starting Port[%s] Execl Failed SysErr[%s] ErrNo[%d]", PortName, strerror( errno ), errno );
				if( SendCommInitErr( getpid() ) < 0 )
					trace( "Error in Sending Comm Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				exit( STOP_SIGNALNO );
			}
		}
		else
		{
			trace( "Waiting for Port[%s] with PortId[%d] to initialize ...", PortName, PortId );
			retval = WaitForPort( PortId );
			//usleep( PortWaitTime );
			if( retval == -1 )
			{
				trace( "Error in initializing Port[%s] with PortId[%d] ", PortName, PortId );
				break;
			}
			else if( retval == 0 )
			{
				trace( "Error in Starting Port[%s] with PortId[%d] ", PortName, PortId );
				kill( PortId, SIGKILL );
				continue;
			}
			else
			{
				trace( "Port[%s] initilaized Successfully", PortName );
				break;
			}
		}
	}
	return 1;
}


int EzCommMgr :: ReStartPort( int Pid )
{
	char PortName[ PORT_NAME_SIZE + 1 ], PortPath[ PORT_PATH_SIZE + 1 ];
	int PortId, retval;
	memset( PortName, 0, sizeof( PortName ) );
	if( LocateCommTable( Pid, PortName ) < 0 )
	{
		trace( "Error in Locating PortId[%d] in the CommTable ...Cannot Restart Port", Pid );
		return -1;
	}

	if( !IsPortInitialized( Pid ) )
	{
		if( SendCommInitErr( Pid ) < 0 )
			trace( "Error in Sending Comm Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	}

	trace( "ReStarting Port[%s]", PortName );

	while( 1 )
	{
		PortId = fork();
		if( PortId < 0 )
		{
			trace( "Error In Forking Process SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			break;
		}
		if( PortId == 0 )
		{
			memset( PortPath, 0, sizeof( PortPath ) );
			sprintf( PortPath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "bin", "EzCommDriver" );
			retval = execl( PortPath, "EzCommDriver", PortName, NULL, NULL );
			if( retval < 0 )
			{
				trace( "Error in Starting Port[%s] Execl Failed SysErr[%s] ErrNo[%d]", PortName, strerror( errno ), errno );
				if( SendCommInitErr( getpid() ) < 0 )
					trace( "Error in Sending Comm Initialization Error ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				exit( STOP_SIGNALNO );
			}
		}
		else
		{
			trace( "Waiting for Port[%s] with PortId[%d] to initialize ...", PortName, PortId );
			retval = WaitForPort( PortId );
			//usleep( PortWaitTime );
			if( retval == -1 )
			{
				trace( "Error in initializing Port[%s] with PortId[%d] ", PortName, PortId );
				break;
			}
			else if( retval == 0 )
			{
				trace( "Error in Starting Port[%s] with PortId[%d] ", PortName, PortId );
				//RemoveCommTable( PortId );
				kill( PortId, SIGUSR2 );
				continue;
			}
			else
			{
				trace( "Port[%s] initilaized Successfully", PortName );
				break;
			}
		}
	}
	return 1;
}

int EzCommMgr :: StopPort( const char *PortName )
{
	int PortId;
	trace( "Stopping Port[%s]", PortName );
	PortId = LocateCommTable( PortName );
	if( PortId < 0 )
	{
		trace( "Cannot Stop Port ...Error in Locating Port[%s] in Commtable", PortName );
		return -1;
	}
	kill( PortId, SIGUSR1 );
	UpdatePort( PortName, PORT_STOPPED );
	ListCommTable();
	return 1;
}

int EzCommMgr :: RemovePort( const char *PortName )
{
	int PortId;
	trace( "Removing Port[%s]", PortName );
	/*
	PortId = LocateCommTable( PortName );
	if( PortId < 0 )
	{
		trace( "Cannot Remove Port ...Error in Locating Port[%s] in Commtable", PortName );
		return -1;
	}

	kill( PortId, SIGUSR1 );
	*/

	if( RemoveCommTable( PortName ) < 0 )
	{
		trace( "Cannot Remove Port ...Error in Locating Port[%s] in Commtable", PortName );
		return -1;
	}
	CurrentTaskCount--;
	ListCommTable();
	return 1;
}

void EzCommMgr :: ServiceRequest()
{
	struct EzPortCmdQMsg cmdqmsg;

	ListCommTable();

	while( 1 )
	{
		trace( "EzCommMgr waiting for request to be serviced ....");
		memset( &cmdqmsg, 0, sizeof( struct EzPortCmdQMsg ) );
		if( msgrcv( GetEzCommMgrQid(), &cmdqmsg, sizeof( cmdqmsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			if ( errno == EINTR )
				continue;
			else if ( errno == EIDRM )
			{
				if( CreateEzCommMgrQueue() < 0 )
				{
					StopAllPort();
					trace( "cleaning all the allcated resources ....");
					FreeResources();
					TaskExit();
				}
				else
					continue;
			}
			else
			{
				trace( "Error in Receiving Message from Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				StopAllPort();
				trace( "cleaning all the allcated resources ....");
				FreeResources();
				TaskExit();
			}
		}
		switch ( cmdqmsg.cmdmsg.Command )
		{
			case START_PORT:
				if( StartPort( cmdqmsg.cmdmsg.PortName ) < 0 )
				{
					cmdqmsg.cmdmsg.Response = -1;
					trace( "Error in Starting Port[%s]", cmdqmsg.cmdmsg.PortName );
				}
				else
				{
					cmdqmsg.cmdmsg.Response = 1;
					trace( "Started Port[%s] Successfully", cmdqmsg.cmdmsg.PortName );
				}
				break;

			case ADD_PORT:
				if( AddPort( cmdqmsg.cmdmsg.PortName ) < 0 )
				{
					cmdqmsg.cmdmsg.Response = -1;
					trace( "Error in Adding New Port[%s]", cmdqmsg.cmdmsg.PortName );
				}
				else
				{
					cmdqmsg.cmdmsg.Response = 1;
					trace( "Added Port[%s] Successfully", cmdqmsg.cmdmsg.PortName );
				}
				break;

			case STOP_PORT:
				if( StopPort( cmdqmsg.cmdmsg.PortName ) < 0 )
				{
					cmdqmsg.cmdmsg.Response = -1;
					trace( "Error in Stopping Port[%s]", cmdqmsg.cmdmsg.PortName );
				}
				else
				{
					cmdqmsg.cmdmsg.Response = 1;
					trace( "Stopped Port[%s] Successfully", cmdqmsg.cmdmsg.PortName );
				}
				break;

			case UPDATE_PORT:
				if( UpdatePort( cmdqmsg.cmdmsg.PortName, cmdqmsg.cmdmsg.PortStatus ) < 0 )
				{
					cmdqmsg.cmdmsg.Response = -1;
					trace( "Error in Updating Port[%s]", cmdqmsg.cmdmsg.PortName );
				}
				else
				{
					cmdqmsg.cmdmsg.Response = 1;
					trace( "Update Port[%s] Successfully", cmdqmsg.cmdmsg.PortName );
				}
				break;

			case REMOVE_PORT:
				if( RemovePort( cmdqmsg.cmdmsg.PortName ) < 0 )
				{
					cmdqmsg.cmdmsg.Response = -1;
					trace( "Error in Removing Port[%s]", cmdqmsg.cmdmsg.PortName );
				}
				else
				{
					cmdqmsg.cmdmsg.Response = 1;
					trace( "Removed Port[%s] Successfully", cmdqmsg.cmdmsg.PortName );
				}
				break;

			default:
				trace( "Invalid Command Code ....Cannot Service Request");
				cmdqmsg.cmdmsg.Response = 1;
				break;
		}
		cmdqmsg.msgtype = cmdqmsg.cmdmsg.NotificationId;
		if( msgsnd( GetEzCommMgrQid(), &cmdqmsg, sizeof( cmdqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
		{
			if( errno == EIDRM )
			{
				if( CreateEzCommMgrQueue() < 0 )
				{
					StopAllPort();
					trace( "cleaning all the allcated resources ....");
					FreeResources();
					TaskExit();
				}
				if( msgsnd( GetEzCommMgrQid(), &cmdqmsg, sizeof( cmdqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
				{
					trace( "Error in sending Port Command Response through Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					StopAllPort();
					trace( "cleaning all the allcated resources ....");
					FreeResources();
					TaskExit();
				}
			}
			else
			{
				trace( "Error in sending Port Command Response through Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				StopAllPort();
				trace( "cleaning all the allcated resources ....");
				FreeResources();
				TaskExit();
			}
		}
	}
}

int main( int argc, char **argv )
{
	EzCommMgr ezcommmgr;
	ezcommmgr.InitEzCommMgr( argv[ 0 ] );
	ezcommmgr.StartConfiguredPorts();
	ezcommmgr.ServiceRequest();
	return 1;
}
