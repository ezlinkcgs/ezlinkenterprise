#include <ezbusiness/ezsmsinfoqueue.h>

pthread_mutex_t SMSQueueMutex = PTHREAD_MUTEX_INITIALIZER;

int EzSMSInfoQueue :: initSMSInfoQueue( EzDebugUtil *dptr )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];

	this->dptr = dptr;
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXGSM", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXGSM from file[%s]", cfgpath );
		return -1;
	}

	MaxGSM = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXQUEUESIZE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXQUEUESIZE from file[%s]", cfgpath );
		return -1;
	}

	MaxQueueSize = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "QUEUEOFFSET", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching QUEUEOFFSET from file[%s]", cfgpath );
		return -1;
	}

	Queueoffset = atoi( cfgval );

	cfgutil.cfg_close();

	smsqueue_ptr = ( struct EzSMSQueueInfo * ) malloc( sizeof( struct EzSMSQueueInfo ) * MaxGSM );

	if( smsqueue_ptr == NULL )
	{
		dptr->trace( "Error in Allocating Memory for SMSQueue...Malloc Error" );
		return -1;
	}

	for( int i = 0; i < MaxGSM; i++ )
	{
		memset( ( smsqueue_ptr + i )->GSMPort, 0, sizeof( ( smsqueue_ptr + i )->GSMPort ) );
		strcpy( ( smsqueue_ptr + i )->GSMPort, GSMPORT_INIT_NAME );
		( smsqueue_ptr + i )->smsinfo_ptr = ( struct EzSMSInfo * ) malloc( sizeof( struct EzSMSInfo ) * MaxQueueSize );
		if( ( smsqueue_ptr + i )->smsinfo_ptr == NULL )
		{
			dptr->trace( "Error in Allocating Memory for SMSInfo...Malloc Error" );
			return -1;
		}
		for( int j = 0; j < MaxQueueSize; j++ )
		{
			memset( ( smsqueue_ptr + i )->smsinfo_ptr + j, 0, sizeof( struct EzSMSInfo ) );
			strcpy( ( ( smsqueue_ptr + i )->smsinfo_ptr + j )->MobileNo, GSM_MOBILENO_INIT_VAL );
			strcpy( ( ( smsqueue_ptr + i )->smsinfo_ptr + j )->SMSBuffer, GSM_BUFFER_INIT_VAL );
		}
	}
	return 1;
}

int EzSMSInfoQueue :: insertSMSInfoQueue( const char *GSMPort )
{
	pthread_mutex_lock( &SMSQueueMutex );
	int retval = -1;
	for( int i = 0; i < MaxGSM; i++ )
	{
		if( !strcmp( ( smsqueue_ptr + i )->GSMPort, GSMPORT_INIT_NAME ) )
		{
			retval = 1;
			memset( ( smsqueue_ptr + i )->GSMPort, 0, sizeof( ( smsqueue_ptr + i )->GSMPort ) );
			strcpy( ( smsqueue_ptr + i )->GSMPort, GSMPort );
			break;
		}
	}
	pthread_mutex_unlock( &SMSQueueMutex );
	return retval;
}

int EzSMSInfoQueue :: deleteSMSInfoQueue( const char *GSMPort )
{
	pthread_mutex_lock( &SMSQueueMutex );
	int retval = -1;
	for( int i = 0; i < MaxGSM; i++ )
	{
		if( !strcmp( ( smsqueue_ptr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			memset( ( smsqueue_ptr + i )->GSMPort, 0, sizeof( ( smsqueue_ptr + i )->GSMPort ) );
			strcpy( ( smsqueue_ptr + i )->GSMPort, GSMPORT_INIT_NAME );
			break;
		}
	}
	pthread_mutex_unlock( &SMSQueueMutex );
	return retval;
}

int EzSMSInfoQueue :: pushSMSInfoQueue( const char *GSMPort, struct EzSMSInfo *smsinfo_ptr )
{
	pthread_mutex_lock( &SMSQueueMutex );
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		if( !strcmp( ( smsqueue_ptr + i )->GSMPort, GSMPort ) )
		{
			for( int j = 0; j < MaxQueueSize; j++ )
			{
				if( !strcmp( ( ( smsqueue_ptr + i )->smsinfo_ptr + j )->MobileNo, GSM_MOBILENO_INIT_VAL ) )
				{
					retval = 1;
					memcpy( ( smsqueue_ptr + i )->smsinfo_ptr + j, smsinfo_ptr, sizeof( struct EzSMSInfo ) );
					break;
				}
			}
			if( retval < 0 )
			{
				struct EzSMSInfo *tmp_smsinfo_ptr;
				int OldMaxQueueSize = MaxQueueSize;

				tmp_smsinfo_ptr = ( struct EzSMSInfo * ) malloc ( sizeof( struct EzSMSInfo ) * OldMaxQueueSize );
				if( tmp_smsinfo_ptr == NULL )
				{
					dptr->trace( "Error in allocating memory for Temp...SMSInfoTable...Malloc Error" );
					pthread_mutex_unlock( &SMSQueueMutex );
					return -1;
				}
				memset( tmp_smsinfo_ptr , 0, sizeof( struct EzSMSInfo ) * OldMaxQueueSize );
				memcpy( tmp_smsinfo_ptr, ( smsqueue_ptr + i )->smsinfo_ptr, sizeof( struct EzSMSInfo ) * OldMaxQueueSize );
				free( ( smsqueue_ptr + i )->smsinfo_ptr );
				MaxQueueSize = MaxQueueSize + Queueoffset;
				( smsqueue_ptr + i )->smsinfo_ptr = ( struct EzSMSInfo * ) malloc ( sizeof( struct EzSMSInfo ) * MaxQueueSize );
				if( ( smsqueue_ptr + i )->smsinfo_ptr == NULL )
				{
					dptr->trace( "Error in allocating memory for New SMSInfoTable...Malloc Error" );
					pthread_mutex_unlock( &SMSQueueMutex );
					return -1;
				}

				memset( ( smsqueue_ptr + i )->smsinfo_ptr , 0, sizeof( struct EzSMSInfo ) * MaxQueueSize );
				memcpy( ( smsqueue_ptr + i )->smsinfo_ptr, tmp_smsinfo_ptr, sizeof( struct EzSMSInfo ) * OldMaxQueueSize );
				free( tmp_smsinfo_ptr );
				memcpy( ( smsqueue_ptr + i )->smsinfo_ptr + OldMaxQueueSize, smsinfo_ptr, sizeof( struct EzSMSInfo ) );
				for( int j =  OldMaxQueueSize + 1 ; j < MaxQueueSize; j++ )
				{
					memset( ( smsqueue_ptr + i )->smsinfo_ptr + j, 0, sizeof( struct EzSMSInfo ) );
					strcpy( ( ( smsqueue_ptr + i )->smsinfo_ptr + j )->MobileNo, GSM_MOBILENO_INIT_VAL );
					strcpy( ( ( smsqueue_ptr + i )->smsinfo_ptr + j )->SMSBuffer, GSM_BUFFER_INIT_VAL );
				}
				retval = 1;
				break;
			}
		}
	}
	pthread_mutex_unlock( &SMSQueueMutex );
	return retval;
}

int EzSMSInfoQueue :: popSMSInfoQueue( const char *GSMPort, struct EzSMSInfo *smsinfo_ptr )
{
	pthread_mutex_lock( &SMSQueueMutex );
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		if( !strcmp( ( smsqueue_ptr + i )->GSMPort, GSMPort ) )
		{
			if( strcmp( ( ( smsqueue_ptr + i )->smsinfo_ptr + 0 )->MobileNo, GSM_MOBILENO_INIT_VAL ) )
			{
				memcpy( smsinfo_ptr, ( smsqueue_ptr + i )->smsinfo_ptr + 0, sizeof( struct EzSMSInfo ) );
				memcpy( ( smsqueue_ptr + i )->smsinfo_ptr, ( smsqueue_ptr + i )->smsinfo_ptr + 1, sizeof( struct EzSMSInfo ) * ( MaxQueueSize - 1 ) );
				memset( ( smsqueue_ptr + i )->smsinfo_ptr + MaxQueueSize, 0, sizeof( struct EzSMSInfo ) );
				strcpy( ( ( smsqueue_ptr + i )->smsinfo_ptr + MaxQueueSize )->MobileNo, GSM_MOBILENO_INIT_VAL );
				strcpy( ( ( smsqueue_ptr + i )->smsinfo_ptr + MaxQueueSize )->SMSBuffer, GSM_BUFFER_INIT_VAL );
				retval = 1;
				break;
			}
		}
	}
	pthread_mutex_unlock( &SMSQueueMutex );
	return retval;
}


