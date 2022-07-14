#include <ezlink/ezechomgrutil.h>

pthread_mutex_t EchoPropertyMutex = PTHREAD_MUTEX_INITIALIZER;

int EzEchoMgrUtil :: initEchoMgrUtil( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]", cfgpath );
	    return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ECHO#MAXECHOPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching ECHO#MAXECHOPROPERTY from file[%s]", cfgpath );
	    cfgutil.cfg_close();
	    return -1;
	}

	cfgutil.cfg_close();

	MaxEchoProperty = atoi( cfgval );

	echopropertytable_ptr = ( struct EzEchoPropertyTable * ) malloc( sizeof( struct EzEchoPropertyTable ) * MaxEchoProperty );

	if( echopropertytable_ptr == NULL )
	{
		dptr->trace( "Error in allocating memory for EzEchoPropertyTable..Malloc Error" );
		return -1;
	}

	for( int i = 0; i < MaxEchoProperty; i++ )
	{
		memset( ( echopropertytable_ptr + i ), 0, sizeof( struct EzEchoPropertyTable ) );
		strcpy( ( echopropertytable_ptr + i )->EchoPropertyId, ECHOPROPERTY_INIT_VAL );
		( echopropertytable_ptr + i )->EchoThreadId = ECHO_THREAD_INIT_VAL;
		( echopropertytable_ptr + i )->ThreadFlag = false;
	}
	return 1;
}

int EzEchoMgrUtil :: updateEchoPropertyTable( const char *EchoPropertyId, int EchoInterval )
{
	int retval = -1;
	pthread_mutex_lock( &EchoPropertyMutex );
	for( int i = 0; i < MaxEchoProperty; i++ )
	{
		if( !strcmp( ( echopropertytable_ptr + i )->EchoPropertyId, EchoPropertyId ) )
		{
			retval = 1;
			( echopropertytable_ptr + i )->EchoInterval = EchoInterval;
			break;
		}
	}
	pthread_mutex_unlock( &EchoPropertyMutex );
	return retval;
}

int EzEchoMgrUtil :: addEchoPropertyTable( const char *EchoPropertyId, pthread_t EchoThreadId, int EchoInterval )
{
	int retval = -1;
	pthread_mutex_lock( &EchoPropertyMutex );
	for( int i = 0; i < MaxEchoProperty; i++ )
	{
		if( ( !strcmp( ( echopropertytable_ptr + i )->EchoPropertyId, ECHOPROPERTY_INIT_VAL ) ) && ( ( echopropertytable_ptr + i )->EchoThreadId == ECHO_THREAD_INIT_VAL ) && ( !( echopropertytable_ptr + i )->ThreadFlag ) )
		{
			retval = 1;
			strcpy( ( echopropertytable_ptr + i )->EchoPropertyId, EchoPropertyId );
			( echopropertytable_ptr + i )->EchoThreadId = EchoThreadId;
			( echopropertytable_ptr + i )->ThreadFlag = true;
			( echopropertytable_ptr + i )->EchoInterval = EchoInterval;
			break;
		}
	}
	pthread_mutex_unlock( &EchoPropertyMutex );
	return retval;
}

int EzEchoMgrUtil :: removeEchoPropertyTable( const char *EchoPropertyId )
{
	int retval = -1;
	pthread_mutex_lock( &EchoPropertyMutex );
	for( int i = 0; i < MaxEchoProperty; i++ )
	{
		if( !strcmp( ( echopropertytable_ptr + i )->EchoPropertyId, EchoPropertyId ) )
		{
			retval = 1;
			strcpy( ( echopropertytable_ptr + i )->EchoPropertyId, ECHO_NETWORKID_INIT_VAL );
			break;
		}
	}
	pthread_mutex_unlock( &EchoPropertyMutex );
	return retval;
}

int EzEchoMgrUtil :: removeEchoPropertyTable( pthread_t EchoThreadId )
{
	int retval = -1;
	pthread_mutex_lock( &EchoPropertyMutex );
	for( int i = 0; i < MaxEchoProperty; i++ )
	{
		if( ( !strcmp( ( echopropertytable_ptr + i )->EchoPropertyId, ECHO_NETWORKID_INIT_VAL ) ) && ( ( echopropertytable_ptr + i )->EchoThreadId == EchoThreadId ) && ( ( echopropertytable_ptr + i )->ThreadFlag ) )
		{
			retval = 1;
			( echopropertytable_ptr + i )->EchoThreadId = ECHO_THREAD_INIT_VAL;
			( echopropertytable_ptr + i )->ThreadFlag = false;
			break;
		}
	}
	pthread_mutex_unlock( &EchoPropertyMutex );
	return retval;
}

int EzEchoMgrUtil :: searchEchoPropertyTable( pthread_t EchoThreadId, struct EzEchoPropertyTable *echopropertytable_rec )
{
	int retval = -1;
	pthread_mutex_lock( &EchoPropertyMutex );
	for( int i = 0; i < MaxEchoProperty; i++ )
	{
		if( ( ( echopropertytable_ptr + i )->EchoThreadId == EchoThreadId ) && ( ( echopropertytable_ptr + i )->ThreadFlag ) )
		{
			retval = 1;
			memcpy( echopropertytable_rec, ( echopropertytable_ptr + i ), sizeof( struct EzEchoPropertyTable ) );
			break;
		}
	}
	pthread_mutex_unlock( &EchoPropertyMutex );
	return retval;
}

int EzEchoMgrUtil :: getMaxEchoProperty()
{
	return MaxEchoProperty;
}

