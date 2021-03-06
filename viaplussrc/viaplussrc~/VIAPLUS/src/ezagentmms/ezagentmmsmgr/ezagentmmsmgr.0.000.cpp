#include <ezagentmms/ezagentmmsmgr.h>

void EzMMSMgr :: init( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	//EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezagentmmsmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzMMSMgr Already Running...." );
		trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
/*
	if( initSchemaInfoUtil( this ) < 0 )
	{
		trace( "Error in Initializing SchemaInfoUtil..." );
		trace( "^^^^^^^^^^^EzPrepaidMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
*/
	/*//if( dbutil.initDBUtil( TaskName, this, "EZMMS" ) < 0 )
	if( dbutil.initDBUtil( TaskName, this, "EZAGENTMMS" ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( SchemaType == SCHEMA_TYPE_SINGLE )
	{
		if( dbutil.DBConnect() < 0 )
		{
			trace( "Error in Connecting with MMS Database...." );
			trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( initMMSMgrUtil( this ) < 0 )
		{
			trace( "Error in Initializing EzMMSMgrUtil" );
			trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		dbutil.DBClose();
	}
	else
	{*/
		//if( initMMSMgrUtil( this, true ) < 0 )
		if( initMMSMgrUtil( TaskName, this, true ) < 0 )
		{
			trace( "Error in Initializing EzMMSMgrUtil" );
			trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
/*
		for( int i = 0; i < MaxSchemaInfo; i++ )
		{
			if( strcmp( ( SchemaInfoShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			{
				if( !strcmp( ( SchemaInfoShmPtr + i )->ProductType, "AGENTMMS" ) )
				{
					if( ConnectDatabase( ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName ) != 0 )
					{
						trace( "Error in Connecting Database [%s/%s@%s]", ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName );
						continue;
					}
					else
						trace( "Connected Database [%s/%s@%s]", ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName );
					if( LoadMMSTables() < 0 )
					{
						trace( "Error in Loading MMSTables..." );
						trace( "^^^^^^^^^^^EzAGENTMMSMgr Ended Abnormally^^^^^^^^^^^^^");
						closeDebug();
						TaskExit();
					}
					CloseDatabase();
				}
			}
		}
*/	
	TaskInit();
	initEzSigUtil( this );
}

void EzMMSMgr :: serviceRequest()
{
	while( 1 )
	{
		pause();
	}
}

int main( int argc, char **argv )
{
	EzMMSMgr mmsmgrobj;
	mmsmgrobj.init( argv[ 0 ] );
	mmsmgrobj.serviceRequest();
	return 1;
}






