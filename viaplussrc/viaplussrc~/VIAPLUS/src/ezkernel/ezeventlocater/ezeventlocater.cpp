#include <ezkernel/ezeventlocater.h>

int EzEventLocater :: initEventLocater( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezeventlocater.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzEventLocater Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzEventLocater Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Already One Instance of EzEventLocater is Running" );
		trace( "~~~~~~~~~~~~~~~~~~EzEventLocater Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil...." );
		trace( "~~~~~~~~~~~~~~~~~~EzEventLocater Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( createDummyChannel( "EzEventMgr" ) < 0 )
	{
		trace( "Error in Creating Dummy Channel EzEventMgr..." );
		trace( "~~~~~~~~~~~~~~~~~~EzEventLocater Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( initEventTable( this ) < 0 )
	{
		trace( "Error in Initializing EventTable...." );
		trace( "~~~~~~~~~~~~~~~~~~EzEventLocater Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
	return 1;
}

int EzEventLocater :: serviceRequest()
{
	int EventCount, retval;
	time_t CurrTime;
	struct EventTable eventtable_rec;
	char difftimestr[ 20 ];
	struct sembuf sem_buf;

	while( 1 )
	{
		CurrTime = time( NULL );
		for( int i = 0; i < MaxEvents; i++ )
		{
			sem_buf.sem_num = i;
			sem_buf.sem_flg = 0;
			sem_buf.sem_op = -2;
			if( semop( EventTableSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on EventTable...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				break;
			}
			if( strcmp( ( EventTableShmPtr + i )->EventKey, EVENT_KEY_INIT_VAL ) )
			{
				memset( difftimestr, 0, sizeof( difftimestr ) );
				sprintf( difftimestr, "%f", difftime( CurrTime, ( EventTableShmPtr + i )->StartTime ) );
				if( atoi( difftimestr ) >= ( EventTableShmPtr + i )->EventTimeOut )
				{
					memset( &eventtable_rec, 0, sizeof( struct EventTable ) );
					memcpy( &eventtable_rec, EventTableShmPtr + i, sizeof( struct EventTable ) );
					memset( ( EventTableShmPtr + i ), 0, sizeof( struct EventTable ) );
					strcpy( ( EventTableShmPtr + i )->EventKey, EVENT_KEY_INIT_VAL );
					sem_buf.sem_op = 2;
					if( semop( EventTableSemId, &sem_buf, 1  ) < 0 )
					{
						trace( "Error in Semop Operation on EventTable...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
						break;
					}
					incrementEventTimeOutCount();
					trace( DEBUG_ERROR, "Event with EventId[%s] TimedOut......", eventtable_rec.EventKey );
					if( WriteChannel( eventtable_rec.NotificationChannel, ( char * ) eventtable_rec.EventBuffer, eventtable_rec.BufferSize ) < 0 )
						trace( DEBUG_ERROR, "Error in Writing TimeOut Message to Channel[%s]", eventtable_rec.NotificationChannel );
					else
						trace( DEBUG_ERROR, "Written TimeOut Message to Channel[%s]", eventtable_rec.NotificationChannel );
				}
				else
				{
					sem_buf.sem_op = 2;
					if( semop( EventTableSemId, &sem_buf, 1  ) < 0 )
					{
						trace( "Error in Semop Operation on EventTable...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
						break;
					}
				}
			}
			else
			{
				sem_buf.sem_op = 2;
				if( semop( EventTableSemId, &sem_buf, 1  ) < 0 )
				{
					trace( "Error in Semop Operation on EventTable...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					break;
				}
			}
		}
		sleep( 1 );
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzEventLocater ezeventlocater;
	ezeventlocater.initEventLocater( argv[ 0 ] );
	ezeventlocater.serviceRequest();
	return 1;
}
