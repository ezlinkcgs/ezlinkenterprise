#include <ezbusiness/ezejcmd.h>

void *EzEJcmd :: ezejcmdobj = 0;

EzEJcmd :: EzEJcmd()
{
	ezejcmdobj = this;
}

EzEJcmd :: ~EzEJcmd()
{

}

int EzEJcmd :: InitEzEJcmd()
{
	char ejlogpath[ LOG_PATH_SIZE + 1 ];

	memset( ejlogpath, 0, sizeof( ejlogpath ));
	sprintf( ejlogpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezejcmd.log" );

	if( openDebug( ejlogpath, "ezejcmd" ) < 0 )
		exit( 0 );

	if( InitEzChLocateUtil( this, "ezejcmd" ) < 0 )
	{
		trace( "Error in Initializing EzChLocateUtil" );
		trace( "^^^^^^^^^^EzEJcmd Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LocateChannel( ATMEJCHANNEL ) < 0 )
	{
		trace( "Error in locating EzEJupload Channel" );
		trace( "^^^^^^^^^EzEJcmd Ended Abnormally^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( !IsTaskRunning( "EzAtmEJMgr" ) )
	{
		trace( "EzAtmEjMgr is not running" );
		trace( "^^^^^^^^^^^^EzEJcmd Ended Abnormally^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	return 1;
}

void EzEJcmd :: startCmdInterface( int argc, char **argv )
{
	char ejcommand[ 100 ];
	char atmejreq[ 100];
	EzDateTimeUtil dtu;

	if( argc == 1 )
	{
		while(1)
		{
			printf("\nezejcmd>");
			waitforinput();
			memset( ejcommand, 0, sizeof( ejcommand ) );
			getCommand( ejcommand, 1 );
			if( strlen( ejcommand ) == 0 )
				continue;

			if( !strcasecmp( ejcommand, "help" ) )
			{
				printf( "\n\t\t<<<<<<<<<<<<<<< Help For EZEJCMD >>>>>>>>>>>>>>>>>\n" );
				printf( "\n\tSYNTAX 1: < ejcommand > < ATM ID >" );
				printf( "\n\tejcommand: < INTIATE/MAINTANANCE > " );
			}
			else if( !strcasecmp( ejcommand, "quit" ) || !strcasecmp( ejcommand, "exit" ) )
				exit( 0 );
			else
			{
				memset( atmejreq, 0, sizeof( atmejreq ) );

				if( !strcasecmp( ejcommand, "INTIATE" ) || !strcasecmp( ejcommand, "I" ) )
					sprintf( atmejreq, "I%c", HEX_FS );
				else if( !strcasecmp( ejcommand, "MAINTANANCE" ) || !strcasecmp( ejcommand, "M" ) )
					sprintf( atmejreq, "M%c", HEX_FS );
				else
				{
					printf("Invalid Command Type");
					trace("Invalid Command Type[%s]", ejcommand );
					continue;
				}

				memset( ejcommand, 0, sizeof( ejcommand ) );
				getCommand( ejcommand, 2 );
				if( strlen( ejcommand ) == 0 )
				{
					printf("ATMID is missing");
					continue;
				}
				else
				{
					sprintf( atmejreq + 2, "%s%c%06d%06d", ejcommand, HEX_FS, dtu.getSysDate(), dtu.getSysTime() );
				}
				trace( "Request Command[%s]", atmejreq );

				if( WriteChannel( atmejreq, strlen( atmejreq ) ) < 0 )
				{
					trace( "Failed to write msg into  Channel %s", ATMEJCHANNEL );
					printf( "Failed to Process the Request...");
					return;
				}
			}
		}
	}
}

int main( int argc, char **argv )
{
	EzEJcmd ezejcmdobj;
	ezejcmdobj.InitEzEJcmd();
	ezejcmdobj.startCmdInterface( argc, argv );
	return 1;
}

