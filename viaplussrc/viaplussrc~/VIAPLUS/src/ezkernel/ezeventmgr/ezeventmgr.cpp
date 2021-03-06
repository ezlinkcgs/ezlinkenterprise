#include <ezkernel/ezeventmgr.h>

void EzEventMgr :: initEventMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	int retval;

	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezeventmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error Initializing EzTaskUtil.... ");
	    trace( "~~~~~~~~~~~~~~~~~~EzEventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		exit( 0 );
	}

	trace( "~~~~~~~~~~~~~~~~~~EzEventMgr Started~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( initEventTable( this ) < 0 )
	{
		trace( "Error in Initializing EventTable....");
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( ezchannelparam.initChannelParam( this ) < 0 )
	{
		trace( "Error in Initializing ChannelParam....");
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	EzEventMgrKey = CreateChannelId( this, "EzEventMgr", TaskName );

	if( EzEventMgrKey < 0 )
	{
		trace( "Error in Creating Channel EzEventMgr....." );
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	EzEventMgrSemid = semget( EzEventMgrKey, 0, IPC_CREAT | 0666 );

	if( EzEventMgrSemid < 0 )
	{
		trace( "Error in Creating EventMgr Semaphore...." );
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( IsTaskRunning( "EzEventMgr" ) < 0 )
	{
		if( setEventMgrSemaphore() < 0 )
		{
			trace( "Error in Setting EventMgr Semaphore..." );
			trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
			closeDebug();
			TaskExit();
		}
	}

	if( ezchannelparam.isUseSharedMemory() )
	{

	}
	else
	{
		if( CreateEventMgrQueue() < 0 )
		{
			trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
			closeDebug();
			TaskExit();
		}
	}

	TaskInit();
	initEzSigUtil( this );
}

int EzEventMgr :: setEventMgrSemaphore()
{
	struct sembuf sem_buf;

	sem_buf.sem_flg = SEM_UNDO;
	sem_buf.sem_num = 0;
	sem_buf.sem_op = 3;

	if( semop( EzEventMgrSemid, &sem_buf, 1 ) < 0 )
	{
		trace( "Error in EventMgr Semop SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzEventMgr :: CreateEventMgrQueue()
{
	EzEventMgrQid = msgget( ( key_t ) EzEventMgrKey, IPC_CREAT | 0666 );
	if(  EzEventMgrQid < 0 )
	{
		trace( "Error in Creating EventMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzEventMgr :: createEvent( struct EventMgrMsg eventmsg )
{
	struct EventTable eventtable_rec;
    int retval;

    memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
	strcpy( eventtable_rec.EventKey, eventmsg.EventKey );
	memcpy( eventtable_rec.EventBuffer, eventmsg.EventBuffer, eventmsg.BufferSize );
	eventtable_rec.BufferSize = eventmsg.BufferSize;
	strcpy( eventtable_rec.NotificationChannel, eventmsg.NotificationChannel );
	eventtable_rec.NotificationQid = eventmsg.NotificationQid;
	eventtable_rec.NotificationId = eventmsg.NotificationId;
	eventtable_rec.EventTimeOut = eventmsg.EventTimeOut;
	eventtable_rec.StartTime = time( NULL );
	eventtable_rec.EventActiveFlag = false;

	retval = addEventTable( eventtable_rec );

    if( retval < 0 )
    {
    	trace( DEBUG_ERROR, "Error in adding EventKey[%s] in Event Table", eventmsg.EventKey );
        return -1;
    }
    else
    {
    	trace( DEBUG_NORMAL, "added EventKey[%s] in Event Table", eventmsg.EventKey );
        return 1;
    }
}

int EzEventMgr :: destroyEvent( const char *EventKey, struct EventMgrMsg *eventmsg_ptr )
{
	int retval;
	struct EventTable eventtable_rec;

	memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
	retval = deleteEventTable( EventKey, &eventtable_rec );

	if( retval < 0 )
	{
		trace( DEBUG_ERROR, "Error in deleting EventTable with EventKey[%s]", EventKey );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Destroyed Event with EventKey[%s]", EventKey );
		memcpy( eventmsg_ptr->EventBuffer, eventtable_rec.EventBuffer, eventtable_rec.BufferSize );
		eventmsg_ptr->BufferSize = eventtable_rec.BufferSize;
		return 1;
	}
}

int EzEventMgr :: searchEvent( const char *EventKey, struct EventMgrMsg *eventmsg_ptr )
{
	int retval;
	struct EventTable eventtable_rec;

	memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
	retval = searchEventTable( EventKey, &eventtable_rec );

	if( retval < 0 )
	{
		trace( DEBUG_ERROR, "Error in searching EventTable with EventKey[%s]", EventKey );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Searched Event with EventKey[%s]", EventKey );
		memcpy( eventmsg_ptr->EventBuffer, eventtable_rec.EventBuffer, eventtable_rec.BufferSize );
		eventmsg_ptr->BufferSize = eventtable_rec.BufferSize;
		return 1;
	}
}

void EzEventMgr :: serviceRequest()
{

}

void EzEventMgr :: ServiceRequest()
{
	if( ezchannelparam.isUseSharedMemory() )
		serviceRequest();

	struct EventMgrQMsg EventReqMsg, EventRespMsg;
	int Response;

	trace( "EzEventMgr Initialized Sucessfully" );

	while( 1 )
	{
		trace( "EzEventMgr Waiting for Servicing Request ....");

		if( msgrcv( EzEventMgrQid, &EventReqMsg, sizeof( struct EventMgrQMsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			if( errno == EINTR )
				continue;
			else if ( errno == EIDRM )
			{
				trace( "Error in Receiving Message From EventMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				trace( "EventMgr Queue Removed...Creating EventMgr Queue");
				if( CreateEventMgrQueue() < 0 )
				{
					trace( "Error in Creating EventMgr Queue...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				    trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
					TaskExit();
				}
				continue;
			}
			else
			{
				trace( "Error in Receiving Message From EventMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			    trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
				TaskExit();
			}
		}

		switch ( EventReqMsg.eventmsg.Command )
		{
			case EVENT_CREATE:

			trace( "Received Event Creation Request with EventKey[%s]", EventReqMsg.eventmsg.EventKey );
			Response = createEvent( EventReqMsg.eventmsg );

			break;

			case EVENT_DESTROY:

			trace( "Received Event Destory Request with EventKey[%s]", EventReqMsg.eventmsg.EventKey );
			Response = destroyEvent( EventReqMsg.eventmsg.EventKey, &EventReqMsg.eventmsg );

			break;

			case EVENT_LOCATE:

			trace( "Received Event Locate Request with EventKey[%s]", EventReqMsg.eventmsg.EventKey );
			Response = searchEvent( EventReqMsg.eventmsg.EventKey, &EventReqMsg.eventmsg );

			break;

			default:

			trace( "Invalid Request Received....");

			break;

		}
		memset( &EventRespMsg, 0, sizeof( struct EventMgrQMsg ) );

		EventRespMsg.msgtype = EventReqMsg.eventmsg.NotificationId;
		strcpy( EventRespMsg.eventmsg.EventKey, EventReqMsg.eventmsg.EventKey );
		memcpy( EventRespMsg.eventmsg.EventBuffer, EventReqMsg.eventmsg.EventBuffer, EventReqMsg.eventmsg.BufferSize );
		EventRespMsg.eventmsg.BufferSize = EventReqMsg.eventmsg.BufferSize;
		EventRespMsg.eventmsg.Response = Response;

		if( msgsnd( EzEventMgrQid, &EventRespMsg, sizeof( struct EventMgrQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			trace( "Error in Sending Event AckMsg for EventKey[%s] NotificationId[%d] SysErr[%s] ErrNo[%d]", EventRespMsg.eventmsg.EventKey, EventRespMsg.eventmsg.NotificationId, strerror( errno ), errno );
		else
			trace( "Sent Event AckMsg for EventId[%s] NotificationId[%d]", EventReqMsg.eventmsg.EventKey, EventReqMsg.eventmsg.NotificationId );

	}

}

int main( int argc, char **argv )
{
	EzEventMgr ezeventmgr;
	ezeventmgr.initEventMgr( argv[ 0 ] );
	ezeventmgr.ServiceRequest();
	return 1;
}
