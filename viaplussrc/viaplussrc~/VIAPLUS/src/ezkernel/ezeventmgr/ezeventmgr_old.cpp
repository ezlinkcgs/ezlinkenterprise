#include <ezkernel/ezeventmgr.h>

EzEventMgr :: EzEventMgr()
{
}

EzEventMgr :: ~EzEventMgr()
{
}

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
	
	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Already One Instance of EventMgr is Running" );
		trace( "~~~~~~~~~~~~~~~~~~EzEventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	trace( "~~~~~~~~~~~~~~~~~~EzEventMgr Started~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( initEzEventMgrUtil( this ) < 0 )
	{
		trace( "Error in Initializing EventMgrUtil" );
	    trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	if( CreateChannel( "EzEventMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzEventMgr" );
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	if( CreateEventMgrQueue() < 0 )
	{
		trace( "Error in Creating EventMgr Queue...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	    trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	if( CreateEventMgrSemaphore() < 0 )
	{
		trace( "Error in Creating EventMgr Semaphore...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	    trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	if( setEventMgrSemaphore() < 0 )
	{
		trace( "Error in Setting EventMgr Semaphore" );
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
		
	if( initEventTable( this ) < 0 )
	{
		trace( "Error in Initializing EventTable....");
		trace( "~~~~~~~~~~~~~~~~~~EventMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

void* EventThreadFunction( void *ThreadData )
{
    int retval;
    struct timeval now;
    struct timespec timeout;
    struct EventTable eventtable_rec;	 
    
	int TableLookUpCount = 0;
	char EventKey[ EVENT_KEY_SIZE + 1 ];

    pthread_cond_t EventCond;
    pthread_mutex_t EventMutex;

    EzEventMgr *eventmgrptr;
    eventmgrptr = ( class EzEventMgr * ) ThreadData;

    int TableLookUpInterval = eventmgrptr->getTableLookUpInterval();
    int EventLookUpInterval = eventmgrptr->getEventLookUpInterval();

    pthread_cond_init( &EventCond, NULL );
    pthread_mutex_init( &EventMutex, NULL );

    while( 1 )
    {
    	TableLookUpCount++;
        gettimeofday( &now, NULL );
        timeout.tv_sec = now.tv_sec + TableLookUpInterval;
        timeout.tv_nsec = now.tv_usec * 1000;
        pthread_mutex_lock( &EventMutex );
        pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
        pthread_mutex_unlock( &EventMutex );
        pthread_mutex_lock( &EventTableMutex );
        memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
        retval = eventmgrptr->searchEventTable( pthread_self(), &eventtable_rec );
        pthread_mutex_unlock( &EventTableMutex );
		if( retval < 0 )
                continue;
		break;
    }

    if( !strcmp( eventtable_rec.EventKey, EVENT_KEY_INIT_VAL ) )
    {
        eventmgrptr->trace( DEBUG_NORMAL, "Event with ThreadId[%d] already Destoryted", pthread_self() );
        pthread_mutex_lock( &EventTableMutex );
        memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
        retval = eventmgrptr->deleteEventTable( pthread_self(), &eventtable_rec );
        pthread_mutex_unlock( &EventTableMutex );
		if( retval < 0 )
			eventmgrptr->trace( DEBUG_ERROR, "Error in deleting ThreadId[%d] from EventTable", pthread_self() );
		else
			eventmgrptr->trace( DEBUG_NORMAL, "Deleted ThreadId[%d] from EventTable", pthread_self() );
        return ( void * ) NULL;
    }

    eventmgrptr->trace( DEBUG_NORMAL, "Inside Thread EventKey[%s] TimeOut[%d]", eventtable_rec.EventKey, eventtable_rec.EventTimeOut );

    memset( EventKey, 0, sizeof( EventKey ) );
    strcpy( EventKey, eventtable_rec.EventKey );

	if( eventtable_rec.EventTimeOut )
	{
		if( eventtable_rec.EventTimeOut > ( TableLookUpInterval * TableLookUpInterval ) )
			eventtable_rec.EventTimeOut =  eventtable_rec.EventTimeOut - ( TableLookUpInterval * TableLookUpCount );
	}

    int NLookUps = eventtable_rec.EventTimeOut / EventLookUpInterval;
	int RLookUp = eventtable_rec.EventTimeOut % EventLookUpInterval;

    bool EventTimeOutFlag = true;

    if( eventtable_rec.EventTimeOut )
    {
        for( int i = 0; i <= NLookUps; i++ )
        {
            gettimeofday( &now, NULL );
			if( i == NLookUps )
            	timeout.tv_sec = now.tv_sec + RLookUp;
			else
            	timeout.tv_sec = now.tv_sec + EventLookUpInterval;
            timeout.tv_nsec = now.tv_usec * 1000;
            pthread_mutex_lock( &EventMutex );
            pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
            pthread_mutex_unlock( &EventMutex );
			pthread_mutex_lock( &EventTableMutex );
			memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
            retval = eventmgrptr->searchEventTable( EventKey, &eventtable_rec );
            pthread_mutex_unlock( &EventTableMutex );
            if( retval < 0 )
            {
                    EventTimeOutFlag = false;
                    break;
            }
        }
    }
    else
    {
        while( 1 )
        {
            gettimeofday( &now, NULL );
            timeout.tv_sec = now.tv_sec + EventLookUpInterval;
            timeout.tv_nsec = now.tv_usec * 1000;
            pthread_mutex_lock( &EventMutex );
            pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
            pthread_mutex_unlock( &EventMutex );
            pthread_mutex_lock( &EventTableMutex );
            memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
            retval = eventmgrptr->searchEventTable( EventKey, &eventtable_rec );
            pthread_mutex_unlock( &EventTableMutex );
            if( retval < 0 )
            {
                EventTimeOutFlag = false;
                break;
            }
        }
    }

	if( EventTimeOutFlag )
    {
        pthread_mutex_lock( &EventTableMutex );
        memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
        retval = eventmgrptr->deleteEventTable( pthread_self(), &eventtable_rec );
        pthread_mutex_unlock( &EventTableMutex );
        
        if( retval < 0 )
        	eventmgrptr->trace( DEBUG_ERROR, "Error in deleting ThreadId[%d] from EventTable", pthread_self() );
        else
        {
        	if( eventmgrptr->WriteChannel( eventtable_rec.NotificationChannel, ( char * ) eventtable_rec.EventBuffer, eventtable_rec.BufferSize ) < 0 )
        		eventmgrptr->trace( DEBUG_ERROR, "Error in Writing TimeOut Message to Channel[%s]", eventtable_rec.NotificationChannel );
        	else
        		eventmgrptr->trace( DEBUG_ERROR, "Written TimeOut Message to Channel[%s]", eventtable_rec.NotificationChannel );
        }
    }
    else
    {
        pthread_mutex_lock( &EventTableMutex );
        memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
        retval = eventmgrptr->deleteEventTable( pthread_self(), &eventtable_rec );
        pthread_mutex_unlock( &EventTableMutex );
        if( retval < 0 )
       		eventmgrptr->trace( DEBUG_ERROR, "Error in deleting ThreadId[%d] from EventTable\n", pthread_self() );
        else
        	eventmgrptr->trace( DEBUG_NORMAL, "Deleted ThreadId[%d] from EventTable\n", pthread_self() );
    }
    return ( void * ) NULL;
}

int EzEventMgr :: createEvent( struct EventMgrMsg eventmsg )
{
	struct EventTable eventtable_rec;
    int retval;
    pthread_t thr_id ;
    pthread_attr_t thr_attr;
    pthread_attr_init( &thr_attr );
    pthread_attr_setdetachstate( &thr_attr, 1 );

    if( pthread_create( &thr_id, &thr_attr, EventThreadFunction, ( void * ) this ) != 0 )
    {
            trace( "Error in Creating Event Thread for EventKey[%s]...SysErr[%s] ErrNo[%d]", eventmsg.EventKey, strerror( errno ), errno );
            return -1;
    }
    else
    {
       trace( DEBUG_NORMAL, "Event Thread with ThreadId[%d] Created for EventKey[%s]", thr_id, eventmsg.EventKey );

	   memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
	   strcpy( eventtable_rec.EventKey, eventmsg.EventKey );
	   eventtable_rec.EventThreadId = thr_id;
	   memcpy( eventtable_rec.EventBuffer, eventmsg.EventBuffer, eventmsg.BufferSize );
	   eventtable_rec.BufferSize = eventmsg.BufferSize;
	   strcpy( eventtable_rec.NotificationChannel, eventmsg.NotificationChannel );
	   eventtable_rec.NotificationQid = eventmsg.NotificationQid;
	   eventtable_rec.NotificationId = eventmsg.NotificationId;
	   eventtable_rec.EventTimeOut = eventmsg.EventTimeOut;
	   eventtable_rec.EventThreadFlag = true;
           
       pthread_mutex_lock( &EventTableMutex );
       retval = insertEventTable( &eventtable_rec );
       pthread_mutex_unlock( &EventTableMutex );

       if( retval < 0 )
       {
       		pthread_cancel( thr_id );
            trace( DEBUG_ERROR, "Error in inserting EventKey[%s] in Event Table", eventmsg.EventKey );
            return -1;
       }
       else
       {
       		trace( DEBUG_NORMAL, "Inserted EventKey[%s] in Event Table", eventmsg.EventKey );
            return 1;
       }
    }
}

int EzEventMgr :: destroyEvent( const char *EventKey, struct EventMgrMsg *eventmsg_ptr )
{
	int retval;
	struct EventTable eventtable_rec;

	pthread_mutex_lock( &EventTableMutex );
	memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
	retval = deleteEventTable( EventKey, &eventtable_rec );
	pthread_mutex_unlock( &EventTableMutex );

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

void EzEventMgr :: ServiceRequest()
{
	struct EventMgrQMsg EventReqMsg, EventRespMsg;
	int Response;
	
	trace( "EzEventMgr Initialized Sucessfully");

	while( 1 )
	{
		trace( "EzEventMgr Waiting for Servicing Request ....");

		if( msgrcv( GetEventMgrQid(), &EventReqMsg, sizeof( struct EventMgrQMsg ) - sizeof( long ), 1, 0 ) < 0 )
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

		if( msgsnd( GetEventMgrQid(), &EventRespMsg, sizeof( struct EventMgrQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
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
