#include <ezkernel/ezeventtableutil.h>

int EventTableUtil :: initEventTable( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	int retval;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );

    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
        dptr->trace( "Error in opening file [%s]", cfgpath );
        return -1;
    }

    memset( cfgVal, 0, sizeof( cfgVal ) );
    retval = cfgutil.cfg_search( "EVENT#MAXEVENTS", cfgVal, 2 );
    if( retval < 0 )
    {
        dptr->trace( "Error in Fetching EVENT#MAXEVENTS from file [%s]", cfgpath );
        cfgutil.cfg_close();
		return -1;
    }

    MaxEvents = atoi( cfgVal );

    memset( cfgVal, 0, sizeof( cfgVal ) );
    retval = cfgutil.cfg_search( "EVENT#MAXEVENTOFFSET", cfgVal, 2 );
    if( retval < 0 )
    {
        dptr->trace( "Error in Fetching EVENT#MAXEVENTOFFSET from file [%s]", cfgpath );
        cfgutil.cfg_close();
        return -1;
    }

    MaxEventOffset = atoi( cfgVal );

    memset( cfgVal, 0, sizeof( cfgVal ) );
    retval = cfgutil.cfg_search( "EVENT#EVENTLOOKUPINTERVAL", cfgVal, 2 );
    if( retval < 0 )
    {
        dptr->trace( "Error in Fetching EVENT#EVENTLOOKUPINTERVAL from file [%s]", cfgpath );
        cfgutil.cfg_close();
		return -1;
    }

    EventLookUpInterval = atoi( cfgVal );
	
    memset( cfgVal, 0, sizeof( cfgVal ) );
    retval = cfgutil.cfg_search( "EVENT#TABLELOOKUPINTERVAL", cfgVal, 2 );
    if( retval < 0 )
    {
        dptr->trace( "Error in Fetching EVENT#TABLELOOKUPINTERVAL from file [%s]", cfgpath );
        cfgutil.cfg_close();
		return -1;
    }

    TableLookUpInterval = atoi( cfgVal );
    
    cfgutil.cfg_close();
    
    dptr->trace( "MaxEvents[%d] MaxEventOffset[%d] EventLookUpInterval[%d] TableLookUpInterval[%d]", MaxEvents, MaxEventOffset, EventLookUpInterval, TableLookUpInterval );
   
	eventtable_ptr = ( struct EventTable * ) malloc( sizeof( struct EventTable ) * MaxEvents );		
	
	if( eventtable_ptr == NULL )
	{
		dptr->trace( "Error in allocating memory for EventTable...Malloc Error" );
		return -1;
	}

	for( int i = 0; i < MaxEvents; i++ )
	{
		memset( eventtable_ptr + i, 0, sizeof( struct EventTable ) );
		strcpy( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL );
		( eventtable_ptr + i )->EventThreadId = EVENT_THREAD_INIT_VAL;
		( eventtable_ptr + i )->EventThreadFlag = false;
	}
	return 1;
}

int EventTableUtil :: getEventLookUpInterval()
{
	return EventLookUpInterval;
}

int EventTableUtil :: getTableLookUpInterval()
{
	return TableLookUpInterval;
}

int EventTableUtil :: getMaxEvents()
{
	return MaxEvents;
}

int EventTableUtil :: getMaxEventOffset()
{
	return MaxEventOffset;
}

int EventTableUtil :: insertEventTable( struct EventTable *eventtable_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( ( !strcmp( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL ) ) && ( ( eventtable_ptr + i )->EventThreadId == EVENT_THREAD_INIT_VAL ) && ( !( eventtable_ptr + i )->EventThreadFlag ) )
		{
			retval = 1;
			memset( ( eventtable_ptr + i ), 0, sizeof( struct EventTable ) );
			memcpy( ( eventtable_ptr + i ), eventtable_rec, sizeof( struct EventTable ) );
			break;
		}
	}

	if( retval < 0 )
	{
		struct EventTable *tmp_eventtable_ptr;
		int OldMaxEvents = MaxEvents;
		tmp_eventtable_ptr = ( struct EventTable * ) malloc ( sizeof( struct EventTable ) * OldMaxEvents );
		if( tmp_eventtable_ptr == NULL )
		{
			dptr->trace( "Error in allocating memory for Temp...EventTable...Malloc Error" );
			return -1;
		}
		memset( tmp_eventtable_ptr , 0, sizeof( struct EventTable ) * OldMaxEvents );
		memcpy( tmp_eventtable_ptr, eventtable_ptr, sizeof( struct EventTable ) * OldMaxEvents );
		free( eventtable_ptr );
		MaxEvents = MaxEvents + MaxEventOffset;	
		eventtable_ptr = ( struct EventTable * ) malloc ( sizeof( struct EventTable ) * MaxEvents );
		if( eventtable_ptr == NULL )
		{
			dptr->trace( "Error in allocating memory for New EventTable...Malloc Error" );
			return -1;
		}
		memset( eventtable_ptr , 0, sizeof( struct EventTable ) * MaxEvents );
		memcpy( eventtable_ptr, tmp_eventtable_ptr, sizeof( struct EventTable ) * OldMaxEvents );
		free( tmp_eventtable_ptr );
		memcpy( ( eventtable_ptr + OldMaxEvents ), eventtable_rec, sizeof( struct EventTable ) );
		for( int i =  OldMaxEvents + 1 ; i < MaxEvents; i++ )
		{
			memset( eventtable_ptr + i, 0, sizeof( struct EventTable ) );
			strcpy( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL );
			( eventtable_ptr + i )->EventThreadId = EVENT_THREAD_INIT_VAL;
			( eventtable_ptr + i )->EventThreadFlag = false;
		}
	}
	return 1;	
}

int EventTableUtil :: searchEventTable( pthread_t ThreadId, struct EventTable *eventtable_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( ( ( eventtable_ptr + i )->EventThreadId == ThreadId ) && ( ( eventtable_ptr + i )->EventThreadFlag ) )
		{
			retval = 1;
			memcpy( eventtable_rec, ( eventtable_ptr + i ), sizeof( struct EventTable ) );
			break;
		}
	}
	return retval;
} 

int EventTableUtil :: searchEventTable( const char *EventKey, struct EventTable *eventtable_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( !strcmp( ( eventtable_ptr + i )->EventKey, EventKey ) )
		{
			retval = 1;
			memcpy( eventtable_rec, ( eventtable_ptr + i ), sizeof( struct EventTable ) );
			break;
		}
	}
	return retval;
} 

int EventTableUtil :: deleteEventTable( pthread_t ThreadId, struct EventTable *eventtable_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( ( ( eventtable_ptr + i )->EventThreadId == ThreadId ) && ( ( eventtable_ptr + i )->EventThreadFlag ) )
		{
			retval = 1;
			memcpy( eventtable_rec, ( eventtable_ptr + i ), sizeof( struct EventTable ) );
			memset( ( eventtable_ptr + i )->EventKey, 0, sizeof( ( eventtable_ptr + i )->EventKey ) );
			strcpy( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL );
			( eventtable_ptr + i )->EventThreadId = EVENT_THREAD_INIT_VAL;
			( eventtable_ptr + i )->EventThreadFlag = false;
			break;
		}
	}
	return retval;
}

int EventTableUtil :: deleteEventTable( const char *EventKey, struct EventTable *eventtable_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( !strcmp( ( eventtable_ptr + i )->EventKey, EventKey ) )
		{
			retval = 1;
			memcpy( eventtable_rec, ( eventtable_ptr + i ), sizeof( struct EventTable ) );
			memset( ( eventtable_ptr + i )->EventKey, 0, sizeof( ( eventtable_ptr + i )->EventKey ) );
			strcpy( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL );
			break;
		}
	}
	return retval;
}

