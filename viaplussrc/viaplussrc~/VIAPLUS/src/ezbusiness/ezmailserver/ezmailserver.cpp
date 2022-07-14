#include <ezbusiness/ezmailserver.h>

void EzMailServer :: initMailServer( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", "ezmailserver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzMailServer Started Running^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( MAILSERVERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", MAILSERVERCHANNEL );
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsmtp.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "IPADDRESS", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching IPADDRESS from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( DefaultMailIpAddress, 0, sizeof( DefaultMailIpAddress ) );
	strcpy( DefaultMailIpAddress, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PORTNO", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching PORTNO from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	if( checkInteger( cfgval ) < 0 )
	{
		trace( "Mail Server PortNo[%s] should be Integer....", cfgval );
		trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	cfgutil.cfg_close();

	DefaultMailPortNo = atoi( cfgval );

	trace( "DefaultMailIpAddress[%s] DefaultMailPortNo[%d]", DefaultMailIpAddress, DefaultMailPortNo );

	TaskInit();
	initEzSigUtil( this );
}

int EzMailServer :: checkInteger( const char *IntStr )
{
	for( int i = 0; i < strlen( IntStr ); i++ )
    {
        if( ( IntStr[ i ] < 48 ) || ( IntStr[ i ] > 57 ) )
                return -1;
    }
    return 1;
}

int EzMailServer :: CreateMailSocket()
{
	MailSocketId = socket( AF_INET, SOCK_STREAM, 0 );
	if( MailSocketId < 0 )
		return -1;
	return 1;
}

int EzMailServer :: GetNTokens( const char *TokenString, char TokenChar )
{
	int cnt = 0;
	for( int i = 0; i < strlen( TokenString ); i++ )
	{
			if( TokenString[ i ] == TokenChar )
					cnt++;
	}
	return cnt + 1;
}

void EzMailServer :: GetToken( const char *TokenString, char *Token, int count, char TokenChar )
{
	for( int i = 0, j = 0, cnt = 0; i < strlen( TokenString ); i++ )
	{
		if( TokenString[ i ] == TokenChar )
			cnt++;
		else if( cnt == count )
			break;
		else if ( cnt + 1 == count )
		{
			Token[ j ] = TokenString[ i ];
			j++;
		}
	}
}

int EzMailServer :: ConnectToMailServer( const char *MailIpAddress, int MailPortNo )
{
	struct sockaddr_in saddr;
	socklen_t addlen = sizeof( saddr );
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( MailPortNo );
	saddr.sin_addr.s_addr = inet_addr( MailIpAddress );
	memset( &saddr.sin_zero, 0, 8 );
	if( connect( MailSocketId, ( struct sockaddr * ) &saddr, addlen ) < 0 )
		return -1;
	return 1;
}

int EzMailServer :: closeMailSocket()
{
	close( MailSocketId );
}

int EzMailServer :: readMailServerMsg( char *MailMsg )
{
	char TempStr[ 2 ];
	int retval = -1;

	while( 1 )
	{
		memset( TempStr, 0, sizeof( TempStr ) );
		if( recv( MailSocketId, TempStr, 1, 0 ) <= 0 )
			break;
		if( TempStr[ 0 ] == '\n' )
		{
			retval = 1;
			break;
		}
		else
			strcat( MailMsg, TempStr );
	}
	return retval;
}

int EzMailServer :: sendMailServerMsg( const char *MailServerMsg, int MsgLen )
{
	if( write( MailSocketId, MailServerMsg, MsgLen ) < 0 )
		return -1;
	return 1;
}

int EzMailServer :: parseSMTPResponse( char *ResponseMessage )
{
	strncpy( ErrCode, ResponseMessage, 3 );
	if( !strncmp( ResponseMessage, "421", 3 ) )
	{
		strcpy( ErrDescription, "Service Not Available" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "450", 3 ) )
	{
		strcpy( ErrDescription, "Mailbox Not Available" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "451", 3 ) )
	{
		strcpy( ErrDescription, "Local Error While Processing" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "452", 3 ) )
	{
		strcpy( ErrDescription, "Insufficient Storage");
		return -1;
	}
	else if( !strncmp( ResponseMessage, "500", 3 ) )
	{
		strcpy( ErrDescription, "Syntax Error: Command Not Recognized" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "501", 3 ) )
	{
		strcpy( ErrDescription, "Syntax Error in Parameters/Arguments" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "502", 3 ) )
	{
		strcpy( ErrDescription, "Command Not Implemented"  );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "503", 3 ) )
	{
		strcpy( ErrDescription, "Bad Sequence of Commands" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "504", 3 ) )
	{
		strcpy( ErrDescription, "Command Parameter not Implemented" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "550", 3 ) )
	{
		strcpy( ErrDescription, "Requested action not taken...Mail Box unavailable" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "551", 3 ) )
	{
		strcpy( ErrDescription, "User Not Local or Invalid Address" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "552", 3 ) )
	{
		strcpy( ErrDescription, "Exceeded Storage Allocation" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "553", 3 ) )
	{
		strcpy( ErrDescription, "Invalid To Address" );
		return -1;
	}
	else if( !strncmp( ResponseMessage, "554", 3 ) )
	{
		strcpy( ErrDescription, "Transaction Failed" );
		return -1;
	}
	return 1;
}


void EzMailServer :: serviceRequest()
{
	struct EzMailMsg mailmsg;
	int MsgSize, NList;
	char MailServerMsg[ MAIL_BUFFER_SIZE + 1 ], MailAddress[ MAIL_ADDRESS_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], ParamStr[ 100 ];
	EzCfgUtil cfgutil;

	while( 1 )
	{
		trace( "EzMailServer Waiting for Request....." );
		memset( &mailmsg, 0, sizeof( struct EzMailMsg ) );
		if( ReadMessage( ( char * ) MailServerMsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from EzMailServer Channel...." );
			trace( "^^^^^^^^^^^EzMailServer Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			exit( 0 );
		}

		trace( DEBUG_TEST, "MailServerMsg[%s]", MailServerMsg );

		memset( &mailmsg, 0, sizeof( struct EzMailMsg ) );
		memset( mailmsg.InstId, 0, sizeof( mailmsg.InstId ) );
		GetToken( MailServerMsg, mailmsg.InstId, 0x1c, 1 );

		if( !strlen( mailmsg.InstId ) )
		{
			memset( mailmsg.IpAddress, 0, sizeof( mailmsg.IpAddress ) );
			strcpy( mailmsg.IpAddress, DefaultMailIpAddress );
			mailmsg.PortNo = DefaultMailPortNo;
		}
		else
		{
			memset( cfgpath, 0, sizeof( cfgpath ) );
			sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsmtp.cfg" );

			if( cfgutil.cfg_open( cfgpath ) < 0 )
			{
				trace( "Error in Opening cfg file[%s]", cfgpath );
				memset( mailmsg.IpAddress, 0, sizeof( mailmsg.IpAddress ) );
				strcpy( mailmsg.IpAddress, DefaultMailIpAddress );
				mailmsg.PortNo = DefaultMailPortNo;
			}
			else
			{
				memset( ParamStr, 0, sizeof( ParamStr ) );
				sprintf( ParamStr, "%s#IpAddress", mailmsg.InstId );
				memset( cfgval, 0, sizeof( cfgval ) );
				if( cfgutil.cfg_search( ParamStr, cfgval,2 ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching [%s] from File[%s]", ParamStr, cfgpath );
					memset( mailmsg.IpAddress, 0, sizeof( mailmsg.IpAddress ) );
					strcpy( mailmsg.IpAddress, DefaultMailIpAddress );
					mailmsg.PortNo = DefaultMailPortNo;
				}
				else
				{
					memset( mailmsg.IpAddress, 0, sizeof( mailmsg.IpAddress ) );
					strcpy( mailmsg.IpAddress, cfgval );
				}

				memset( ParamStr, 0, sizeof( ParamStr ) );
				sprintf( ParamStr, "%s#PortNo", mailmsg.InstId );
				memset( cfgval, 0, sizeof( cfgval ) );
				if( cfgutil.cfg_search( ParamStr, cfgval,2 ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching [%s] from File[%s]", ParamStr, cfgpath );
					mailmsg.PortNo = DefaultMailPortNo;
				}
				else
				{
					mailmsg.PortNo = atoi( cfgval );
				}

				cfgutil.cfg_close();
			}
		}

		memset( mailmsg.FromAddress, 0, sizeof( mailmsg.FromAddress ) );
		GetToken( MailServerMsg, mailmsg.FromAddress, 0x1c, 2 );

		if( !strlen( mailmsg.FromAddress ) )
		{
			trace( DEBUG_ERROR, "FromAddress is Null....Dropping Message" );
			continue;
		}

		memset( mailmsg.ToAddress, 0, sizeof( mailmsg.ToAddress ) );
		GetToken( MailServerMsg, mailmsg.ToAddress, 0x1c, 3 );

		if( !strlen( mailmsg.ToAddress ) )
		{
			trace( DEBUG_ERROR, "ToAddress is Null....Dropping Message" );
			continue;
		}

		memset( mailmsg.CCAddress, 0, sizeof( mailmsg.CCAddress ) );
		GetToken( MailServerMsg, mailmsg.CCAddress, 0x1c, 4 );

		memset( mailmsg.Subject, 0, sizeof( mailmsg.Subject ) );
		GetToken( MailServerMsg, mailmsg.Subject, 0x1c, 5 );

		if( !strlen( mailmsg.Subject ) )
		{
			trace( DEBUG_ERROR, "Subject is Null....Dropping Message" );
			continue;
		}

		memset( mailmsg.Body, 0, sizeof( mailmsg.Body ) );
		GetToken( MailServerMsg, mailmsg.Body, 0x1c, 6 );

		if( !strlen( mailmsg.Body ) )
		{
			trace( DEBUG_ERROR, "Message Body is Null....Dropping Message" );
			continue;
		}

		if( CreateMailSocket() < 0 )
		{
			trace( DEBUG_ERROR, "Error in Creating Mail....Socket...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			continue;
		}

		if( ConnectToMailServer( mailmsg.IpAddress, mailmsg.PortNo ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Connecting with Mail Server...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		if( readMailServerMsg( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

		memset( ErrCode, 0, sizeof( ErrCode ) );
		memset( ErrDescription, 0, sizeof( ErrDescription ) );
		if( parseSMTPResponse( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "SMTP Err : ErrCode[%s] Description[%s]", ErrCode, ErrDescription );
			closeMailSocket();
			continue;
		}

		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "HELO %s\r\n", "localhost" );

		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		if( readMailServerMsg( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

		memset( ErrCode, 0, sizeof( ErrCode ) );
		memset( ErrDescription, 0, sizeof( ErrDescription ) );
		if( parseSMTPResponse( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "SMTP Err : ErrCode[%s] Description[%s]", ErrCode, ErrDescription );
			closeMailSocket();
			continue;
		}

		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "MAIL FROM: %s\r\n", mailmsg.FromAddress );

		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		if( readMailServerMsg( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

		memset( ErrCode, 0, sizeof( ErrCode ) );
		memset( ErrDescription, 0, sizeof( ErrDescription ) );
		if( parseSMTPResponse( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "SMTP Err : ErrCode[%s] Description[%s]", ErrCode, ErrDescription );
			closeMailSocket();
			continue;
		}

		NList = GetNTokens( mailmsg.ToAddress, ',' );
		for( int i = 0; i < NList; i++ )
		{
			memset( MailAddress, 0, sizeof( MailAddress ) );
			GetToken( mailmsg.ToAddress, MailAddress, i + 1, ',' );
			memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
			sprintf( MailServerMsg, "RCPT TO: %s\r\n", MailAddress );

			if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				closeMailSocket();
				break;
			}

			hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

			memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
			if( readMailServerMsg( MailServerMsg ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				closeMailSocket();
				break;
			}

			hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

			memset( ErrCode, 0, sizeof( ErrCode ) );
			memset( ErrDescription, 0, sizeof( ErrDescription ) );
			if( parseSMTPResponse( MailServerMsg ) < 0 )
			{
				trace( DEBUG_ERROR, "SMTP Err : ErrCode[%s] Description[%s]", ErrCode, ErrDescription );
				closeMailSocket();
				break;
			}
		}

		NList = GetNTokens( mailmsg.CCAddress, ',' );
		for( int i = 0; i < NList; i++ )
		{
			memset( MailAddress, 0, sizeof( MailAddress ) );
			GetToken( mailmsg.CCAddress, MailAddress, i + 1, ',' );
			memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
			sprintf( MailServerMsg, "RCPT TO: %s\r\n", MailAddress );

			if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				closeMailSocket();
				break;
			}

			hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

			memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
			if( readMailServerMsg( MailServerMsg ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				closeMailSocket();
				break;
			}

			hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );

			memset( ErrCode, 0, sizeof( ErrCode ) );
			memset( ErrDescription, 0, sizeof( ErrDescription ) );
			if( parseSMTPResponse( MailServerMsg ) < 0 )
			{
				trace( DEBUG_ERROR, "SMTP Err : ErrCode[%s] Description[%s]", ErrCode, ErrDescription );
				closeMailSocket();
				break;
			}
		}
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		strcpy( MailServerMsg, "DATA\r\n" );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		if( readMailServerMsg( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( ErrCode, 0, sizeof( ErrCode ) );
		memset( ErrDescription, 0, sizeof( ErrDescription ) );
		if( parseSMTPResponse( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "SMTP Err : ErrCode[%s] Description[%s]", ErrCode, ErrDescription );
			closeMailSocket();
			continue;
		}
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "From: %s\r\n", mailmsg.FromAddress );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "To: %s\r\n", mailmsg.ToAddress );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "Cc: %s\r\n", mailmsg.CCAddress );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "Subject: %s\r\n", mailmsg.Subject );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "%s\r\n.\r\n", mailmsg.Body );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		if( readMailServerMsg( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}

		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		sprintf( MailServerMsg, "%s\r\n", "QUIT" );
		if( sendMailServerMsg( MailServerMsg, strlen( MailServerMsg ) ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message To Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		memset( MailServerMsg, 0, sizeof( MailServerMsg ) );
		if( readMailServerMsg( MailServerMsg ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from Mail Server Socket.....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			closeMailSocket();
			continue;
		}
		hex_dump( DEBUG_TEST, ( unsigned char * ) MailServerMsg, strlen( MailServerMsg ) );
		closeMailSocket();
	}
}


int main( int argc, char **argv )
{
	EzMailServer mailsrvr;
	mailsrvr.initMailServer( argv[ 0 ] );
	mailsrvr.serviceRequest();
	return 1;
}




