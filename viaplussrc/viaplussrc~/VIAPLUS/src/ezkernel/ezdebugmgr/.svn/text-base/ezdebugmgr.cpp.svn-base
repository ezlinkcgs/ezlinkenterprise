#include <ezkernel/ezdebugmgr.h>

int EzDebugMgr :: initDebugMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezdebugmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzDebugMgr Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzDebugMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Already One Instance of EzDebugMgr is Running" );
		trace( "~~~~~~~~~~~~~~~~~~EzDebugMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezdebug.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace(  " Error in opening file [%s] ", cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~EzDebugMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	memset( cfgVal, 0, sizeof( cfgVal ) );
	if( cfgutil.cfg_search( "DEBUGLOOKUPTIME", cfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching DEBUGLOOKUPTIME from file[%s],,Setting Default Value as 120 Seconds", cfgpath );
		DebugLookUpTime = 120;
	}
	else
		DebugLookUpTime = atoi( cfgVal );

	cfgutil.cfg_close();
	TaskInit();
	initEzSigUtil( this );
}

void EzDebugMgr :: PurgeDebug( const char *DebugName, const char *DebugPath )
{
	DIR *dir_ptr;
	char BackUpDir[ 200 ], BackUpFileName[ 200 ], CommandStr[ 512 ];
	FILE *fp;

	trace( DEBUG_TEST, "Purging DebugFile[%s]....", DebugName );
	memset( BackUpDir, 0, sizeof( BackUpDir ) );
	sprintf( BackUpDir, "%s/%s", getenv( "EZDIR_HOME" ), "logbackup" );
	dir_ptr = opendir( BackUpDir );
	if( dir_ptr == NULL )
	{
		if( errno == ENOENT )
		{
			if( mkdir( BackUpDir, 0777 ) < 0 )
			{
				trace( "Error in Creating Directory[%s]...SysErr[%s] ErrNo[%d]", BackUpDir, strerror( errno ), errno );
				return;
			}
			dir_ptr = opendir( BackUpDir );
			if( dir_ptr == NULL )
			{
				trace( "Error in Opening Directory[%s]...SysErr[%s] ErrNo[%d]", BackUpDir, strerror( errno ), errno );
				return;
			}
		}
		else
		{
			trace( "Error in Opening Directory[%s]...SysErr[%s] ErrNo[%d]", BackUpDir, strerror( errno ), errno );
			return;
		}
	}

	closedir( dir_ptr );

	memset( BackUpDir, 0, sizeof( BackUpDir ) );
	sprintf( BackUpDir, "%s/%s/%06d", getenv( "EZDIR_HOME" ), "logbackup", ezdatetimeutil.getSysDate() );
	dir_ptr = opendir( BackUpDir );
	if( dir_ptr == NULL )
	{
		if( errno == ENOENT )
		{
			if( mkdir( BackUpDir, 0777 ) < 0 )
			{
				trace( "Error in Creating Directory[%s]...SysErr[%s] ErrNo[%d]", BackUpDir, strerror( errno ), errno );
				return;
			}
			dir_ptr = opendir( BackUpDir );
			if( dir_ptr == NULL )
			{
				trace( "Error in Opening Directory[%s]...SysErr[%s] ErrNo[%d]", BackUpDir, strerror( errno ), errno );
				return;
			}
		}
		else
		{
			trace( "Error in Opening Directory[%s]...SysErr[%s] ErrNo[%d]", BackUpDir, strerror( errno ), errno );
			return;
		}
	}
	closedir( dir_ptr );

	memset( BackUpFileName, 0, sizeof( BackUpFileName ) );
	sprintf( BackUpFileName, "%s/%s.log_%06d", BackUpDir, DebugName, ezdatetimeutil.getSysTime() );

	memset( CommandStr, 0, sizeof( CommandStr ) );
	sprintf( CommandStr, "cp %s %s", DebugPath, BackUpFileName );
	fp = popen( CommandStr, "r" );
	if( fp == NULL )
	{
		trace( "Error in popen while copying file from Source[%s] to BackUp[%s] ....SysErr[%s] ErrNo[%d]", DebugPath, BackUpFileName, strerror( errno ), errno );
		return;
	}
	pclose( fp );

	memset( CommandStr, 0, sizeof( CommandStr ) );
	sprintf( CommandStr, ">%s", DebugPath );
	fp = popen( CommandStr, "r" );
	if( fp == NULL )
	{
		trace( "Error in popen while clearing DebugFile[%s] SysErr[%s] ErrNo[%d]", DebugPath, strerror( errno ), errno );
		return;
	}
	pclose( fp );
	return;
}

int EzDebugMgr :: checkInteger( const char *IntStr )
{
	for( int i = 0; i < strlen( IntStr ); i++ )
    {
        if( ( IntStr[ i ] < 48 ) || ( IntStr[ i ] > 57 ) )
                return -1;
    }
    return 1;
}

int EzDebugMgr :: startDebugMgr()
{
	EzCfgUtil cfgutil;
	struct stat fileinfo;
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ], DebugName[ 50 ], DebugParamStr[ 100 ];
	int FileCount;
	long int DebugSize;

	while( 1 )
	{
		sleep( DebugLookUpTime );
		memset( cfgpath, 0, sizeof( cfgpath ) );
		sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezdebug.cfg" );

		if( cfgutil.cfg_open( cfgpath ) < 0 )
		{
			trace(  " Error in opening file [%s]", cfgpath );
			trace(  "~~~~~~~~~~~~~~~~~~EzDebugMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~" );
			closeDebug();
			TaskExit();
		}

		FileCount = cfgutil.cfg_group_count( "DEBUGSIZE" );

		if( FileCount < 0 )
		{
			trace( "Error in Searching Group DEBUGSIZE from [%s] ", cfgpath );
			trace(  "~~~~~~~~~~~~~~~~~~EzDebugMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~" );
			closeDebug();
			cfgutil.cfg_close();
			TaskExit();
		}

		for( int i = 0; i < FileCount; i++ )
		{
			memset( DebugName, 0, sizeof( DebugName ) );
			if( cfgutil.cfg_get_param( "DEBUGSIZE", DebugName, i + 1 ) < 0 )
				continue;
			memset( DebugParamStr, 0, sizeof( DebugParamStr ) );
			sprintf( DebugParamStr, "%s#%s", "DEBUGSIZE", DebugName );
			memset(cfgVal, 0, sizeof( cfgVal ) );
			if( cfgutil.cfg_search( DebugParamStr, cfgVal, 2 ) < 0 )
			{
				trace( "Error in Searchhing [%s] from File[%s]", DebugParamStr, cfgpath );
				trace( "Setting Default Size as 1GB....." );
				DebugSize = 1024 * 1024 * 1024;
			}
			else if( checkInteger( cfgVal ) < 0 )
			{
				trace( "Invalid DebugSize[%s] Configured for [%s] in File[%s]", cfgVal, DebugParamStr, cfgpath );
				trace( "Setting Default Size as 1GB....." );
				DebugSize = 1024 * 1024 * 1024;
			}
			else if( atoi( cfgVal ) > 1024 )
			{
				trace( "Invalid DebugSize[%s] Configured for [%s] in File[%s]...Maximum DebugSize should be 1024MB[1GB]....", cfgVal, DebugParamStr, cfgpath );
				trace( "Setting Default Size as 1GB....." );
				DebugSize = 1024 * 1024 * 1024;
			}
			else
				DebugSize = atoi( cfgVal ) * 1024 * 1024;

			memset( logpath, 0, sizeof( logpath ) );
			sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", DebugName );
			memset( &fileinfo, 0, sizeof( struct stat ) );
			if( stat( logpath, &fileinfo ) < 0 )
			{
				trace( "Error in Getting File Information for DebugFile[%s]...SysErr[%s] ErrNo[%d]", DebugName, strerror( errno ), errno );
				continue;
			}
			trace( DEBUG_TEST, "CurrentDebugSize[%d] MaxDebugSize[%d]", fileinfo.st_size, DebugSize );
			if( fileinfo.st_size > DebugSize )
			{
				trace( "CurrentDebugSize[%d] > MaxDebugSize[%d]", fileinfo.st_size, DebugSize );
				PurgeDebug( DebugName, logpath );
			}
		}
		cfgutil.cfg_close();
	}
}

int main( int argc, char **argv )
{
	EzDebugMgr ezdebugmgr;
	ezdebugmgr.initDebugMgr( argv[ 0 ] );
	ezdebugmgr.startDebugMgr();
	return 1;
}
