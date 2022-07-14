#include <ezlink/ezsmssender.h>

int EzSMSSender :: initSMSSender( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsmssender.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzSMSSender Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	SetDebug();

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzSMSSender", TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel",  "EzSMSSender" );
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( composeSMSString() < 0 )
	{
		trace( "Error in Composing SMS String...." );
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
        sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezalert.cfg" );

        if( cfgutil.cfg_open( cfgpath ) < 0 )
        {
                trace( "Erron in Opening file[%s]...", cfgpath );
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
        }

        memset( cfgval, 0, sizeof( cfgval ) );
        if( cfgutil.cfg_search( "SMSSEND#IPADDRESS", cfgval, 2 ) < 0 )
        {
                trace( "Error in Searching SMSSEND#IPADDRESS from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
        }

	memset( ipaddress, 0, sizeof( ipaddress ) );
	strcpy( ipaddress, cfgval );

        memset( cfgval, 0, sizeof( cfgval ) );
        if( cfgutil.cfg_search( "SMSSEND#PORTNO", cfgval, 2 ) < 0 )
        {
                trace( "Error in Searching SMSSEND#PORTNO from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
        }
	portno = atoi( cfgval );

	 memset( cfgval, 0, sizeof( cfgval ) );
        if( cfgutil.cfg_search( "SMSSEND#HEADERREQ", cfgval, 2 ) < 0 )
        {
                trace( "Error in Searching SMSSEND#HEADERREQ from file[%s]", cfgpath );
                trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
                cfgutil.cfg_close();
                closeDebug();
                TaskExit();
        }

	memset( headerreq, 0, sizeof( headerreq ) );
	strcpy( headerreq, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
        if( cfgutil.cfg_search( "SMSSEND#HEADERTYPE", cfgval, 2 ) < 0 )
        {
                trace( "Error in Searching SMSSEND#HEADERTYPE from file[%s]", cfgpath );
                trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
                cfgutil.cfg_close();
                closeDebug();
                TaskExit();
        }

        memset( headertype, 0, sizeof( headertype ) );
        strcpy( headertype, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
        if( cfgutil.cfg_search( "SMSSEND#HEADERLEN", cfgval, 2 ) < 0 )
        {
                trace( "Error in Searching SMSSEND#HEADERLEN from file[%s]", cfgpath );
                trace( "^^^^^^^^^^^EzSMSSender Ended Abnormally^^^^^^^^^^^^^");
                cfgutil.cfg_close();
                closeDebug();
                TaskExit();
        }

	headerlen = atoi( cfgval );

	cfgutil.cfg_close();

	TaskInit();
	initEzSigUtil( this );
	return 1;
}

int EzSMSSender :: composeSMSString()
{
	char cfgpath[ CFG_PATH_SIZE + 1 ];
	FILE *fp;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsmssender.cfg" );
	fp = fopen( cfgpath, "r" );
	if( fp == NULL )
	{
		trace( "Error in opening file[%s]", cfgpath );
		return -1;
	}
	memset( SMSString, 0, sizeof( SMSString ) );
	fgets( SMSString, sizeof( SMSString ), fp );
	fclose( fp );
	SMSString[ strlen( SMSString ) - 1 ] = 0;
	trace( "SMSString[%s]", SMSString );
	return 1;
}

void EzSMSSender :: composeSMS( const char *MobileNo, const char *MsgBuffer, char *smsMessage )
{
	for( int i = 0, j = 0; i < strlen( SMSString ); i++ )
	{
		if( SMSString[ i ] == '(' )
		{
			strcat( smsMessage, MsgBuffer );
			j += strlen( MsgBuffer );
		}
		else if ( SMSString[ i ] == ')' )
		{
			strcat( smsMessage, MobileNo );
			j += strlen( MobileNo );
		}
		else
		{
			smsMessage[ j ] = SMSString[ i ];
			j++;
		}
	}
}

int EzSMSSender :: createSocket()
{
	int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if( sockfd < 0 )
	{
		trace( " Error in Creating Socket ...Error [%s] ", strerror( errno ) );
		return -1;
	}
	return sockfd;
}

int EzSMSSender :: connectServer( int sockfd, const char *ipaddress, int portno )
{
	struct sockaddr_in saddr;
	socklen_t addlen = sizeof( saddr );
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( portno );
	saddr.sin_addr.s_addr = inet_addr( ipaddress );
	memset( &saddr.sin_zero, 0, 8 );

	if( connect( sockfd, ( struct sockaddr * ) &saddr, addlen ) < 0 )
	{
		trace( " Failed to Connect ipaddress [%s] portno [%d] error [%s] ", ipaddress, portno, strerror( errno ) );
		close( sockfd );
		return -1;
	}
	else
		return 1;
}

int EzSMSSender :: writeSocket( int sockfd, const char *MsgBuffer, int MsgSize )
{
	char SMSBuffer[ 4097 ];
	int retval;
	short int msgsize;

	memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
	if( !strcasecmp( headerreq, "Yes" ) )
	{
		if( !strcasecmp( headertype, "Hex" ) )
		{
			msgsize = MsgSize;
			msgsize = htons( msgsize );
			memcpy( SMSBuffer, &msgsize, headerlen );
			memcpy( SMSBuffer + headerlen, MsgBuffer, MsgSize );
		}
		else
		{
			sprintf( SMSBuffer, "%0*d", headerlen, MsgSize );
			strncpy( SMSBuffer + headerlen, MsgBuffer, MsgSize );
		}
	}

	hex_dump( ( unsigned char * ) SMSBuffer, MsgSize );

	retval = write( sockfd, SMSBuffer, MsgSize );
	if( retval < 0 )
	{
		trace( "Error in Writing Message to Socket...SysErr[%s] errno[%d]", strerror( errno ), errno );
		close( sockfd );
		return -1;
	}
	else
	{
		trace( "Message of Bytes[%d] written to Socket...", retval );
		memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
		retval = recv( sockfd, SMSBuffer, 1024, 0 );
		if ( retval <= 0 )
			trace( "Error in Reading Message From Socket.. SysErr[ %s ] errno[%d] ", strerror( errno ), errno );
		else
		{
			trace(" Message Received From Socket... ");
			hex_dump( ( unsigned char * ) SMSBuffer, retval );
		}
		close( sockfd );
		return 1;
	}

}

void EzSMSSender :: serviceRequest()
{
	struct EzSMSBufferInfo smsbufferinfo;
	int MsgSize, sockfd, NMobileNo;
	char smsMessage[ 1025 ], MobileNo[ 20 ];
	memset( &smsbufferinfo, 0, sizeof( struct EzSMSBufferInfo ) );
	while( 1 )
	{
		trace( "EzSMSender Waiting for Request...." );
		memset( &smsbufferinfo, 0, sizeof( struct EzSMSBufferInfo ) );
		if( ReadMessage( ( char * )&smsbufferinfo, &MsgSize ) < 0 )
		{
			trace( "Error While Reading Message from EzAlertMgr Channel...." );
			sleep( 1 );
			continue;
		}

		NMobileNo = eztokenutil.getNToken( smsbufferinfo.MobileList, ',' );
		for( int i = 0; i < NMobileNo; i++ )
		{
			memset( MobileNo, 0, sizeof( MobileNo ) );
			eztokenutil.getToken( smsbufferinfo.MobileList, MobileNo, ',', i + 1 );
			memset( smsMessage, 0, sizeof( smsMessage ) );
			composeSMS( MobileNo, smsbufferinfo.MsgBuffer, smsMessage );

			sockfd = createSocket();
			if( sockfd < 0 )
				continue;

			if( connectServer( sockfd, ipaddress, portno )	< 0 )
				continue;

			if( writeSocket( sockfd, smsMessage, strlen( smsMessage ) ) < 0 )
				trace(" Error Writing Message to Socket " );
			else
				trace(" Written Message to socket " );
		}
	}
}

int main( int argc, char **argv )
{
	EzSMSSender ezsmssenderobj;
	ezsmssenderobj.initSMSSender( argv[ 0 ] );
	ezsmssenderobj.serviceRequest();
	return 1;
}

