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

    cfgutil.cfg_close();

    dptr->trace( "MaxEvents[%d] MaxEventOffset[%d]", MaxEvents, MaxEventOffset );

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
	}
	return 1;
}

int EventTableUtil :: getMaxEvents()
{
	return MaxEvents;
}

int EventTableUtil :: getMaxEventOffset()
{
	return MaxEventOffset;
}

int EventTableUtil :: getActiveEvents()
{
	int EventCount = 0;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( strcmp( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL ) )
		{
			( eventtable_ptr + i )->EventActiveFlag = true;
			EventCount++;
		}
	}
	return EventCount;
}

int EventTableUtil :: searchEventTable( struct EventTable *eventtable_rec, int RowCount )
{
	int EventCount = 0;
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( strcmp( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL ) && ( eventtable_ptr + i )->EventActiveFlag )
			EventCount++;
		if( EventCount == RowCount )
		{
			memcpy( eventtable_rec, ( eventtable_ptr + i ), sizeof( struct EventTable ) );
			retval = 1;
			break;
		}
	}
	return retval;
}

int EventTableUtil :: insertEventTable( struct EventTable *eventtable_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( !strcmp( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL ) )
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
		}
	}
	return 1;
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

int EventTableUtil :: deleteEventTable( const char *EventKey )
{
	int retval = -1;
	for( int i = 0; i < MaxEvents; i++ )
	{
		if( !strcmp( ( eventtable_ptr + i )->EventKey, EventKey ) )
		{
			retval = 1;
			memset( ( eventtable_ptr + i )->EventKey, 0, sizeof( ( eventtable_ptr + i )->EventKey ) );
			strcpy( ( eventtable_ptr + i )->EventKey, EVENT_KEY_INIT_VAL );
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

