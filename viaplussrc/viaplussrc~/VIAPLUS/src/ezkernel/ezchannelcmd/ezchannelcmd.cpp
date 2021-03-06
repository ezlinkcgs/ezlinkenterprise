#include <ezkernel/ezchannelcmd.h>

EzChannelCmd :: EzChannelCmd()
{
}

EzChannelCmd :: ~EzChannelCmd()
{
}

int EzChannelCmd :: init()
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	int retval;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezchannelcmd.log" );
	if( openCmdDebug( logpath, "ezchannelcmd" ) < 0 )
	{
		printf("\n Error in opening file [%s]...echannelcmd Exiting\n", logpath );
		exit( 0 );
	}
	trace("~~~~~~~~~~~~~~~~~~eztaskcmd Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( InitEzTaskUtil( this, 1 ) < 0 )
	{
		printf(	"\nError in Initializing EzTaskUtil\n" );
		trace(	"Error in Initializing EzTaskUtil" );
		exit( 0 );
	}

	if( !IsTaskMgrRunning() )
	{
		printf( "\neztaskmgr is not running..start the ezkernel\n");
		exit( 0 );
	}

	if( InitEzChannelCmdUtil( this ) < 0 )
	{
		printf( "\neztaskmgr is not running..start the ezkernel\n");
		exit( 0 );
	}
	return 1;
}

void EzChannelCmd :: startCmdInterface( int argc, char **argv )
{
	char command[ 100 ];

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezchannelcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					ListChannel();
					continue;
				}
				ListChannel( command );
				continue;
			}
			else if( !strcasecmp( command, "port" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					ListPortChannel();
					continue;
				}
				ListPortChannel( command );
				continue;
			}
			else if( !strcasecmp( command, "table" ) )
			{
				memset( command, 0, sizeof( command ) );
				ListTableChannel();
				continue;
			}
			else if( !strcasecmp( command, "memory" ) )
			{
				memset( command, 0, sizeof( command ) );
				ListMemoryChannel();
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n<List>");
				printf("\n<List> <ChannelName>");
				printf("\n<Port>");
				printf("\n<Port Name>");
				printf("\n<Table>");
				printf("\n<Memory>");
			}
			else if( !strcasecmp( command, "quit" ) )
				break;
			else
			{
				printf("\n invaild command ..type help for more");
					continue;
			}
		}
	}
	else
	{
		memset( command, 0, sizeof( command ) );
		strcpy( command, argv[ 1 ] );
		if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				ListChannel();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				ListChannel( command );
			}
		}
		else if( !strcasecmp( command, "port" ) )
		{
			if( argc == 2 )
				ListPortChannel();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				ListPortChannel( command );
			}
		}
		else if( !strcasecmp( command, "table" ) )
			ListTableChannel();
		else if( !strcasecmp( command, "memory" ) )
			ListMemoryChannel();
		else if( !strcmp( command, "help" ) )
		{
			printf("\n<List>");
			printf("\n<List> <ChannelName>");
			printf("\n<Port>");
			printf("\n<Port Name>");
			printf("\n<Table>");
			printf("\n<Memory>");
		}
		else if( !strcmp( command, "quit" ) )
			return ;
		else
			printf("\n invaild command ..type help for more");
	}
}

int main( int argc, char **argv )
{
	EzChannelCmd channelcmd;
	channelcmd.init();
	channelcmd.startCmdInterface( argc, argv );
	return 1;
}
