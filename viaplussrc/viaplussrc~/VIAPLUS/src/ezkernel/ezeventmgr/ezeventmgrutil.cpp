#include <ezkernel/ezeventmgrutil.h>

int EzEventMgrUtil :: initEzEventMgrUtil( EzDebugUtil *dptr )
{
	struct EzChannelMgrQMsg chqmsg;
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];
	int EzChannelMgrKey, EzChannelMgrQid;

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
	
	cfgutil.cfg_close();

	EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );
	if( EzChannelMgrQid < 0 )
	{
		dptr->trace( "Error in Creating EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( &chqmsg, 0, sizeof( chqmsg ) );
	chqmsg.msgtype = 1;
	strcpy( chqmsg.chmgrmsg.ChannelName, "EzEventMgr" );
	chqmsg.chmgrmsg.Command = CREATE_TASK_CHANNEL;
	chqmsg.chmgrmsg.NotificationId = getpid();

	if( msgsnd( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
	{
		dptr->trace( "Error in Sending Channel Creation Message to EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( &chqmsg, 0, sizeof( chqmsg ) );
	if( msgrcv( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), getpid(), 0 ) < 0 )
	{
		dptr->trace( "Error in Receiving Channel Creation Message to EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( chqmsg.chmgrmsg.Response < 0 )
	{
		dptr->trace( "Error in Creating Channel[%s]", "EzEventMgr" );
		return -1;
	}

	dptr->trace( "Channel[%s] Created with ChannelKeyId[%d] ChannelQid[%d]", chqmsg.chmgrmsg.ChannelName, chqmsg.chmgrmsg.ChannelKeyId, chqmsg.chmgrmsg.ChannelQid );

	EzEventMgrQid = chqmsg.chmgrmsg.ChannelQid;	
	EzEventMgrKey = chqmsg.chmgrmsg.ChannelKeyId;
	
	if( CreateEventMgrQueue() < 0 )
		return -1;
	
	if( CreateEventMgrSemaphore() < 0 )
		return -1;
	
	return 1;
}

int EzEventMgrUtil :: setEventMgrSemaphore()
{
	struct sembuf sem_buf;

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	if( semctl( EzEventMgrSemid, 0, SETVAL, arg ) < 0 )
	{
		dptr->trace( "Error in Setting EventMgr Semaphore Value SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	
	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 3;

	if( semop( EzEventMgrSemid, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in EventMgr Semop SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;

}

int EzEventMgrUtil :: CreateEventMgrQueue()
{
	EzEventMgrQid = msgget( ( key_t ) EzEventMgrKey, IPC_CREAT | 0666 );
	if(  EzEventMgrQid < 0 )
	{
		dptr->trace( "Error in Creating EventMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzEventMgrUtil :: CreateEventMgrSemaphore()
{
	EzEventMgrSemid = semget( ( key_t ) EzEventMgrKey, 1, IPC_CREAT | 0666 );
	if(  EzEventMgrSemid < 0 )
	{
		dptr->trace( "Error in Creating EventMgr Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzEventMgrUtil :: GetEventMgrQid()
{
	return  EzEventMgrQid;
}
