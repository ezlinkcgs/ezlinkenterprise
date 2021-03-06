#include <ezkernel/ezchannelmgr.h>

void EzChannelMgr :: FreeResources()
{
	closeDebug();
}

void EzChannelMgr :: InitEzChannelMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ];
	int retval, OrgKey;
	struct sembuf sem_buf;
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezchannelmgr.log" );
	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Started~~~~~~~~~~~~~~~~~~~~~~~~~~ ");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzChannelMgr is Already Running" );
       	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	trace( "Initializing Channel Manager ....");

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file [%s] ", cfgpath );
       	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "CHANNEL#ORGKEY", cfgVal, 2 );

    if( retval < 0 )
    {
	   	trace( "Error in Fetching CHANNEL#ORGKEY from file [%s]", cfgpath );
    	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	OrgKey = atoi( cfgVal );

	trace( "OrgKey = [%d]", OrgKey );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "CHANNEL#MAXIPCKEYS", cfgVal, 2 );
    if( retval < 0 )
    {
	   	trace( "Error in Fetching CHANNEL#MAXIPCKEYS from file [%s]", cfgpath );
    	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	MaxIpcKeys = atoi( cfgVal );
	trace( "MaxIpcKeys = [%d] ", MaxIpcKeys );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "CHANNEL#MAXCHANNELS", cfgVal, 2 );
    if( retval < 0 )
    {
	   	trace( "Error in Fetching CHANNEL#MAXTASKCHANNELS from file [%s]", cfgpath );
    	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	MaxChannels = atoi( cfgVal );
	trace( "Maximum Channels = [%d] ", MaxChannels );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "CHANNEL#MAXPORTCHANNELS", cfgVal, 2 );
   	if( retval < 0 )
   	{
	   	trace( "Error in Fetching CHANNEL#MAXPORTCHANNELS from file [%s]", cfgpath );
   		trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	MaxPortChannels = atoi( cfgVal );
	trace( "Maximum Port Channels = [%d] ", MaxPortChannels );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgutil.cfg_search( "CHANNEL#INITPORTCHANNEL", cfgVal, 2 );
	if( retval < 0 )
		InitPortChannelFlag = false;
	else
	{
		if( !strcasecmp( cfgVal, "Yes" ) )
			InitPortChannelFlag = true;
		else
			InitPortChannelFlag = false;
	}

	cfgutil.cfg_close();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
    	trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	if( InitEzChannelMgrUtil( this, OrgKey, MaxIpcKeys, MaxChannels, MaxPortChannels ) < 0 )
	{
		trace( "Error in Initializing EzChannelMgrUtil");
		trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	if( CreateEzChannelMgrQueue() < 0 )
	{
		trace( "Error in Creating EzChannelMgr Queue Sys Err[%s]", strerror( errno ) );
 		trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	if( IsChannelMgrRestarted() )
	{
		trace( "EzChannelMgr Restarted" );
		if( LocateEzChannelMgrSharedMemory() < 0 )
		{
			trace( "Error in Locating EzChannelMgr Shared Memory SysErr[%s]", strerror( errno ) );
	 		trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
			cfgutil.cfg_close();
			closeDebug();
			TaskExit();
		}
	}
	else
	{
		if( CreateEzChannelMgrSharedMemory() < 0 )
		{
			trace( "Error in Creating EzChannelMgr Shared Memory SysErr[%s]", strerror( errno ) );
	 		trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
			cfgutil.cfg_close();
			closeDebug();
			TaskExit();
		}
	}
	CreateConfiguredChannels();
	TaskInit();
	initEzSigUtil( this );
}

void EzChannelMgr :: CreateConfiguredChannels()
{
	char GroupName[ GROUP_NAME_SIZE + 1 ], errVal[ ERR_VAL_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ];
    int GroupCount = 0, retval;

	EzCfgUtil cfgutil;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file [%s] ", cfgpath );
        trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

    memset( GroupName, 0, sizeof( GroupName ) );
    sprintf( GroupName, "%s#%s", "CHANNEL", "TASK" );
    GroupCount = cfgutil.cfg_group_count( GroupName );

    if( GroupCount < 0 )
    {
		trace( "Error in Reading Group[%s]", GroupName );
		memset( errVal, 0, sizeof( errVal ) );
		cfgutil.cfg_fetch_error( errVal );
		trace( "[%s]", errVal );
    }
	else
	{
    	for( int i = 0; i < GroupCount; i++ )
    	{
    		memset( cfgVal, 0, sizeof( cfgVal ) );
			if( cfgutil.cfg_get_param( GroupName, cfgVal, i + 1 ) < 0 )
			{
				trace( " Error in Reading Group [%s]", GroupName );
				memset( errVal, 0, sizeof( errVal ) );
				cfgutil.cfg_fetch_error( errVal );
				trace( "[%s]", errVal );
				continue;
    	    }
			retval = CreateTaskChannel( cfgVal, CHANNEL_INIT_TASK_NAME );
			if( retval < 0 )
				trace( "Error in Creating Task Channel[%s]", cfgVal );
			else
				trace( "Task Channel[%s] created with ChannelKeyId[%d] ChannelQid[%d]", cfgVal, GetChannelKeyId(), GetChannelQid() );
		}
	}

    memset( GroupName, 0, sizeof( GroupName ) );
    sprintf( GroupName, "%s#%s", "CHANNEL", "TABLE" );
    GroupCount = cfgutil.cfg_group_count( GroupName );

    if( GroupCount < 0 )
    {
		trace( "Error in Reading Group[%s]", GroupName );
		memset( errVal, 0, sizeof( errVal ) );
		cfgutil.cfg_fetch_error( errVal );
		trace( "[%s]", errVal );
	}
	else
	{
        for( int i = 0; i < GroupCount; i++ )
        {
			memset( cfgVal, 0, sizeof( cfgVal ) );
			if( cfgutil.cfg_get_param( GroupName, cfgVal, i + 1 ) < 0 )
			{
				trace( " Error in Reading Group [%s]", GroupName );
				memset( errVal, 0, sizeof( errVal ) );
				cfgutil.cfg_fetch_error( errVal );
				trace( "[%s]", errVal );
				continue;
			}
			retval = CreateTableChannel( cfgVal  );
			if( retval < 0 )
				trace( "Error in Creating Table Channel[%s]", cfgVal );
			else
				trace( "Table Channel[%s] created with ChannelKeyId[%d]", cfgVal, GetChannelKeyId() );
		}
	}

    memset( GroupName, 0, sizeof( GroupName ) );
    sprintf( GroupName, "%s#%s", "CHANNEL", "MEMORY" );
    GroupCount = cfgutil.cfg_group_count( GroupName );

    if( GroupCount < 0 )
    {
		trace( "Error in Reading Group[%s]", GroupName );
		memset( errVal, 0, sizeof( errVal ) );
		cfgutil.cfg_fetch_error( errVal );
		trace( "[%s]", errVal );
	}
	else
	{
       for( int i = 0; i < GroupCount; i++ )
       {
			memset( cfgVal, 0, sizeof( cfgVal ) );
			if( cfgutil.cfg_get_param( GroupName, cfgVal, i + 1 ) < 0 )
			{
				trace( " Error in Reading Group [%s]", GroupName );
				memset( errVal, 0, sizeof( errVal ) );
				cfgutil.cfg_fetch_error( errVal );
				trace( "[%s]", errVal );
				continue;
			}
	        trace( "Creating Memory Channel[%s]", cfgVal );
	        retval = CreateMemoryChannel( cfgVal );
	        if( retval < 0 )
	        	trace( "Error in Creating Memory Channel[%s]", cfgVal );
	        else
	        	trace( "Memory Channel[%s] created with ChannelKeyId[%d]", cfgVal, GetChannelKeyId() );
	   }
	}

	cfgutil.cfg_close();

	if( InitPortChannelFlag )
	{
		memset( cfgpath, 0, sizeof( cfgpath ) );
		sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

		if( cfgutil.cfg_open( cfgpath ) < 0 )
		{
			trace( "Error in opening file [%s] ", cfgpath );
			trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
			closeDebug();
			TaskExit();
		}

		GroupCount = cfgutil.cfg_group_count( "DRIVER" );

		if( GroupCount < 0 )
		{
			trace( "Error in Reading Group[%s]", "DRIVER" );
			memset( errVal, 0, sizeof( errVal ) );
			cfgutil.cfg_fetch_error( errVal );
			trace( "[%s]", errVal );
		}
		else
		{
			for( int i = 0; i < GroupCount; i++ )
			{
				memset( cfgVal, 0, sizeof( cfgVal ) );
				if( cfgutil.cfg_get_param( "DRIVER", cfgVal, i + 1 ) < 0 )
				{
					trace( " Error in Reading Group [%s]", GroupName );
					memset( errVal, 0, sizeof( errVal ) );
					cfgutil.cfg_fetch_error( errVal );
					trace( "[%s]", errVal );
					continue;
				}
				retval = CreatePortChannel( cfgVal );
				if( retval < 0 )
					trace( "Error in Creating Port Channel[%s]", cfgVal );
				else
					trace( "Port Channel[%s] Created with PortId[%d]", cfgVal, retval );
			}
		}
		cfgutil.cfg_close();
	}
}

void EzChannelMgr :: ServiceRequest()
{
	struct EzChannelMgrQMsg chmgrqmsg;

	trace( "EzChannelMgr Initialized Successfully....");
	ListChannelTable();
	ListChannelPortTable();

	while( 1 )
	{
		trace( "EzChannelMgr Waiting for Servicing Request ....");
		memset( &chmgrqmsg, 0, sizeof( chmgrqmsg ) );
		if( msgrcv( GetEzChannelMgrQid(), &chmgrqmsg, sizeof( chmgrqmsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			trace( "FATAL:Error in receving message from ChannelMgr Queue SysErr[%s]", strerror( errno ) );
			if( errno == EIDRM )
			{
				trace( "ChannelMgr Message Queue was Removed...Creating Message Queue Once again");
				if( CreateEzChannelMgrQueue() < 0 )
				{
					trace( "Error in Creating ChannelMgr Queue...SysErr[%s]", strerror( errno ) );
	       				trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
					FreeResources();
			        	TaskExit();
				}
			}
			else if ( errno == EINTR )
			{
				trace( "Message Queue Receive was Interrupted by a Signal" );
				continue;
			}
		}
		switch( chmgrqmsg.chmgrmsg.Command )
		{
			case CREATE_TASK_CHANNEL:

			trace( "Creating Task Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			if( !strcmp( chmgrqmsg.chmgrmsg.ChannelName, "EzMsgRouter" ) )
			{
				memset( chmgrqmsg.chmgrmsg.TaskName, 0, sizeof( chmgrqmsg.chmgrmsg.TaskName ) );
				strcpy( chmgrqmsg.chmgrmsg.TaskName, chmgrqmsg.chmgrmsg.ChannelName );
			}
			chmgrqmsg.chmgrmsg.Response = CreateTaskChannel( chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.TaskName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Creating TaskChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
			{
				chmgrqmsg.chmgrmsg.ChannelKeyId = GetChannelKeyId();
				chmgrqmsg.chmgrmsg.ChannelQid = GetChannelQid();
				trace( "Created TaskChannel[%s] with ChannelKeyId[%d] ChannelQid[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.ChannelKeyId, chmgrqmsg.chmgrmsg.ChannelQid );
			}
			break;

			case CREATE_TABLE_CHANNEL:

			trace( "Creating Table Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = CreateTableChannel( chmgrqmsg.chmgrmsg.ChannelName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Creating TaskChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
			{
				chmgrqmsg.chmgrmsg.ChannelKeyId = GetChannelKeyId();
				trace( "Created TableChannel[%s] with ChannelKeyId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.ChannelKeyId );
			}
			break;

			case CREATE_MEMORY_CHANNEL:

			trace( "Creating Memory Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = CreateMemoryChannel( chmgrqmsg.chmgrmsg.ChannelName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Creating MemoryChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
			{
				chmgrqmsg.chmgrmsg.ChannelKeyId = GetChannelKeyId();
				trace( "Created MemoryChannel[%s] with ChannelKeyId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.ChannelKeyId );
			}
			break;

			case LOCATE_TASK_CHANNEL:

			trace( "Locating Task Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = LocateTaskChannel( chmgrqmsg.chmgrmsg.ChannelName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Locating TaskChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
			{
				chmgrqmsg.chmgrmsg.ChannelKeyId = GetChannelKeyId();
				chmgrqmsg.chmgrmsg.ChannelQid = GetChannelQid();
				trace( "Located TaskChannel[%s] with ChannelKeyId[%d] ChannelQid[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.ChannelKeyId, chmgrqmsg.chmgrmsg.ChannelQid );
			}
			break;

			case LOCATE_TABLE_CHANNEL:

			trace( "Locating Table Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = LocateTableChannel( chmgrqmsg.chmgrmsg.ChannelName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Locating TableChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
			{
				chmgrqmsg.chmgrmsg.ChannelKeyId = GetChannelKeyId();
				trace( "Located TableChannel[%s] with ChannelKeyId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.ChannelKeyId );
			}
			break;

			case LOCATE_MEMORY_CHANNEL:

			trace( "Locating Memory Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = LocateMemoryChannel( chmgrqmsg.chmgrmsg.ChannelName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Locating MemoryChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
			{
				chmgrqmsg.chmgrmsg.ChannelKeyId = GetChannelKeyId();
				trace( "Located MemoryChannel[%s] with ChannelKeyId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.ChannelKeyId );
			}
			break;

			case CREATE_PORT_CHANNEL:

			trace( "Crearing Port Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = CreatePortChannel( chmgrqmsg.chmgrmsg.ChannelName,  chmgrqmsg.chmgrmsg.NotificationId );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Creating PortChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
				trace( "Created PortChannel[%s] with PortId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.Response );
			break;

			case LOCATE_PORT_CHANNEL:

			trace( "Located Port Channel[%s] with NotificationId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.NotificationId );
			chmgrqmsg.chmgrmsg.Response = LocatePortChannel( chmgrqmsg.chmgrmsg.ChannelName );
			if( chmgrqmsg.chmgrmsg.Response < 0 )
				trace( "Error in Locating PortChannel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			else
				trace( "Located PortChannel[%s] with PortId[%d]", chmgrqmsg.chmgrmsg.ChannelName, chmgrqmsg.chmgrmsg.Response );
			break;

			default:
			trace( "Invalid Channel Command Received");
		}

		chmgrqmsg.msgtype = chmgrqmsg.chmgrmsg.NotificationId;
		if( msgsnd( GetEzChannelMgrQid(), &chmgrqmsg, sizeof( chmgrqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
		{
			trace( "Error in Sending Channel Response Message for Channel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
			if( errno == EAGAIN )
				trace( "Fatal Error: ChannelMgr Queue is Full..Pl. check the System Configuration");
			else if( errno == EIDRM )
			{
				trace( "Fatal Error: ChannelMgr Queue was removed..Creating ChannelMgr Queue");
				if( CreateEzChannelMgrQueue() < 0 )
				{
					trace( "Error in Creating ChannelMgr Queue...SysErr[%s]", strerror( errno ) );
	       				trace( "~~~~~~~~~~~~~~~~~~EzChannelMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
					FreeResources();
			        	TaskExit();
				}
			}
			if( msgsnd( GetEzChannelMgrQid(), &chmgrqmsg, sizeof( chmgrqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
				trace( "Error in Sending Channel Response Message for Channel[%s]", chmgrqmsg.chmgrmsg.ChannelName );
		}
	}
}

int main( int argc, char **argv )
{
	EzChannelMgr ezchannelmgr;
	ezchannelmgr.InitEzChannelMgr( argv[ 0 ] );
	ezchannelmgr.ServiceRequest();
	return 1;
}

