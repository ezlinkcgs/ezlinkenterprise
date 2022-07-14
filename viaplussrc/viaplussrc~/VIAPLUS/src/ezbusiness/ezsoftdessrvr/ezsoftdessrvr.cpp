#include <ezbusiness/ezsoftdessrvr.h>

int EzSoftDESSrvr :: initSoftDESSrvr()
{
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsoftdessrvr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsofdessrvr.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}



}


