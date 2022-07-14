#include "ezhsmsim.h"

int EzHSMSim :: checkInteger( const char *IntStr, int IntLen )
{
	if( strlen( IntStr ) > IntLen )
		return -1;
	for( int i = 0; i < strlen( IntStr ); i++ )
    {
        if( ( IntStr[ i ] < 48 ) || ( IntStr[ i ] > 57 ) )
                return -1;
    }
    return 1;
}

int EzHSMSim :: initHSMSim( const char *TaskName, const char *PortNoStr, const char *CfgFile )
{
	EzCfgUtil cfgutil;
	char cfgpath[ 200 ], cfgval [ 100 ], logpath[ 200 ];

	if( checkInteger( PortNoStr, 5 ) < 0 )
	{
		printf( "\n[%s] is not a valid PortNo....\n", PortNoStr );
		return -1;
	}

	memset( &hsmparam, 0, sizeof( struct EzHSMParam ) );

	hsmparam.HSMPortNo = atoi( PortNoStr );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s/%s", getenv( "HOME" ), "hsmsimulator", "cfg", CfgFile );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		printf( "\nError in Opening HSM Configuration File[%s]...\n", cfgpath );
		return -1;
	}

	memset( hsmparam.HSMId, 0, sizeof( hsmparam.HSMId ) );
	if( cfgutil.cfg_search( "HSMID", hsmparam.HSMId, 2 ) < 0 )
	{
		printf( "\nError in Searching HSMID from File[%s]....\n", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HSMTYPE", cfgval, 2 ) < 0 )
	{
		printf( "\nError in Searching HSMTYPE from File[%s]....\n", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgval, "ERACOM" ) )
		hsmparam.HSMType = HSM_TYPE_ERACOM;
	else
		hsmparam.HSMType = HSM_TYPE_RACAL;

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HEADERLEN", cfgval, 2 ) < 0 )
	{
		printf( "\nError in Searching HEADERLEN from File[%s]....\n", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( checkInteger( cfgval, 2 ) < 0 )
	{
		printf( "\n[%s] is not a valid Header Length....\n", cfgval );
		return -1;
	}
	hsmparam.HeaderLen = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HEADERTYPE", cfgval, 2 ) < 0 )
	{
		printf( "\nError in Searching HEADERTYPE from File[%s]....\n", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgval, "HEX" ) )
		hsmparam.HeaderType = HEADER_TYPE_HEX;
	else
		hsmparam.HeaderType = HEADER_TYPE_ASCII;

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MSGHEADERLEN", cfgval, 2 ) < 0 )
	{
		printf( "\nError in Searching MSGHEADERLEN from File[%s]....\n", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	if( checkInteger( cfgval, 2 ) < 0 )
	{
		printf( "\n[%s] is not a valid MsgHeader Length....\n", cfgval );
		return -1;
	}
	hsmparam.MsgHeaderLen = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXCLIENTS", cfgval, 2 ) < 0 )
	{
		printf( "\nError in Searching MAXCLIENTS from File[%s]....\n", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	if( checkInteger( cfgval, 2 ) < 0 )
	{
		printf( "\n[%s] is not a valid MsgHeader Length....\n", cfgval );
		return -1;
	}
	hsmparam.MaxClients = atoi( cfgval );

	cfgutil.cfg_close();

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s/%s.log", getenv( "HOME" ), "hsmsimulator", "log", hsmparam.HSMId );

	if( openDebug( logpath, hsmparam.HSMId ) < 0 )
	{
		printf("\nError in Opening Log File[%s]", logpath );
		return -1;
	}
	return 1;
}

int EzHSMSim :: identifyCommandType( const char *tcpipmsg )
{
	int retval = 1;

	if( hsmparam.HSMType == HSM_TYPE_RACAL )
	{
		if( !strncmp( tcpipmsg + hsmparam.MsgHeaderLen, "HC", 2 ) )
			CommandType = HSM_TERMINAL_KEY_GEN_REQ;
		else if( !strncmp( tcpipmsg + hsmparam.MsgHeaderLen, "IA", 2 ) )
			CommandType = HSM_NETWORK_KEY_GEN_REQ;
		else if( !strncmp( tcpipmsg + hsmparam.MsgHeaderLen, "CA", 2 ) )
			CommandType = HSM_PIN_TRNSLATE_REQ;
		else if( !strncmp( tcpipmsg + hsmparam.MsgHeaderLen, "DA", 2 ) )
			CommandType = HSM_TERMINAL_PIN_VERIFICATION_REQ;
		else if( !strncmp( tcpipmsg + hsmparam.MsgHeaderLen, "EA", 2 ) )
			CommandType = HSM_NETWORK_PIN_VERIFICATION_REQ;
		else
			retval = -1;
	}
	else
	{

	}
	return retval;
}

int EzHSMSim :: writeHSMSocket( int ConnectionId, const char *HSMRespMsg, int MsgLen )
{
	char tcpipHeader[ 10 ], tcpipRespMsg[ 1024 ];
	short sMsgSize;

	if( hsmparam.HeaderType == HEADER_TYPE_ASCII )
	{
		memset( tcpipHeader, 0, sizeof( tcpipHeader ) );
		sprintf( tcpipHeader, "%0*d", hsmparam.HeaderLen, MsgLen );
		memset( tcpipRespMsg, 0, sizeof( tcpipRespMsg ) );
		memcpy( tcpipRespMsg, tcpipHeader, hsmparam.HeaderLen );
		memcpy( tcpipRespMsg + hsmparam.HeaderLen, HSMRespMsg, MsgLen );
	}
	else
	{
		sMsgSize = MsgLen;
		sMsgSize = htons( sMsgSize );
		memset( tcpipRespMsg, 0, sizeof( tcpipRespMsg ) );
		memcpy( tcpipRespMsg, &sMsgSize, hsmparam.HeaderLen );
		memcpy( tcpipRespMsg + hsmparam.HeaderLen, HSMRespMsg, MsgLen );
	}
	hex_dump( ( unsigned char * )tcpipRespMsg, hsmparam.HeaderLen + MsgLen );
	retval = write( ConnectionId, tcpipRespMsg, hsmparam.HeaderLen + MsgLen );
	if( retval < 0 )
	{
		trace( "Error in Writing Message to Socket..ErrNo[%d] StrError[%s]", errno, strerror( errno ) );
		return -1;
	}
	return 1;
}

int EzHSMSim :: serviceTerminalKeyGenReq( const char *tcpipmsg, char *HSMRespMsg )
{
	if( HSMType == HSM_TYPE_RACAL )
	{
		MsgOffset = 0;

		//Message Header
		if( MsgHeaderLen )
			strncpy( HSMRespMsg + MsgOffset, tcpipmsg, MsgHeaderLen );
		MsgOffset += MsgHeaderLen;

		//Command Code
		strncpy( HSMRespMsg + MsgOffset, "HD", 2 );
		MsgOffset += 2;

		//Response Code
		strncpy( HSMRespMsg + MsgOffset, "00", 2 );
		MsgOffset += 2;

		if( tcpipmsg[ MsgHeaderLen + 2 ] == 'U' )
		{
			strncpy( HSMRespMsg + MsgOffset, "X", 1 );
			MsgOffset += 1;
			memset( HSMRespMsg + MsgOffset, '1', 32 );
			MsgOffset += 32;
			strncpy( HSMRespMsg + MsgOffset, "U", 1 );
			MsgOffset += 1;
			memset( HSMRespMsg + MsgOffset, '1', 32 );
			MsgOffset += 32;
		}
		else if( tcpipmsg[ MsgHeaderLen + 2 ] == 'T' )
		{
			strncpy( HSMRespMsg + MsgOffset, "Y", 1 );
			MsgOffset += 1;
			memset( HSMRespMsg + MsgOffset, '1', 48 );
			MsgOffset += 48;
			strncpy( HSMRespMsg + MsgOffset, "T", 1 );
			MsgOffset += 1;
			memset( HSMRespMsg + MsgOffset, '1', 48 );
			MsgOffset += 48;
		}
		else
		{
			memset( HSMRespMsg + MsgOffset, '1', 32 );
			MsgOffset += 32;
		}
	}
	return MsgOffset;
}

int EzHSMSim :: serviceNetworkKeyGenReq()
{

}

int EzHSMSim :: servicePINTranslateReq()
{

}

int EzHSMSim :: servicePINVerificationReq()
{

}

int EzHSMSim :: createServerSocket()
{
	int Opt = 1 ;
	struct sockaddr_in cliaddr;

	ServerSocketId = socket( AF_INET, SOCK_STREAM, 0 );
	if( ServerSocketId < 0 )
	{
		trace( "Error in Creating Server Socket....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	setsockopt( ServerSocketId, SOL_SOCKET, SO_KEEPALIVE, &Opt, sizeof( Opt ) );

	bzero( &cliaddr, sizeof( struct sockaddr_in ) );

	if( listen( ServerSocketId, hsmparam.MaxClientss ) < 0 )
	{
		trace( "Error in Listen....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzHSMSim :: allocateDescriptorList()
{
	desc_list_ptr = ( int * ) malloc( sizeof( int ) * hsmparam.MaxClients );
	if( desc_list_ptr == NULL )
	{
		trace( "Malloc Error....While Allocating Memory for Descriptor List...." );
		return -1;
	}
	for( int i = 0; i < hsmparam.MaxClients; i++ )
		desc_list_ptr[ i ] = SOCKET_DESCRIPTOR_INIT_VAL;
	return 1;
}

void EzHSMSim :: processHSMRequest( int ConnectionId, const char *tcpipmsg, int MsgSize )
{
	trace( "processing HSM Request...." );

	if( identifyCommandType( tcpipmsg ) < 0 )
	{
		trace( "Invalid Command Type Received....." );
		return;
	}

	switch ( CommandType )
	{
		case HSM_TERMINAL_KEY_GEN_REQ:

			trace( "Terminal Key Generation Request Received...." );
			serviceTerminalKeyGenReq( ConnectionId, tcpipmsg, MsgSize );
			break;

		case HSM_NETWORK_KEY_GEN_REQ:

			trace( "Network Key Generation Request Received...." );
			serviceNetworkKeyGenReq( ConnectionId, tcpipmsg, MsgSize );
			break;

		case HSM_PIN_TRANSLATE_REQ:

			trace( "PIN Translation Request Received...." );
			servicePINTranslateReq( ConnectionId, tcpipmsg, MsgSize );
			break;

		case HSM_PIN_VERIFICATION_REQ:

			trace( "PIN Verification Request Received...." );
			servicePINVerificationReq( ConnectionId, tcpipmsg, MsgSize );
			break;

		default:
			break;
	}
}

int EzHSMSim :: serviceRequest()
{
	int size, fdmax, sockfd, RecvBytes, MsgLen, ConnectionId;
	int DescList[ 21 ], DescCount = 0;
	char MsgHeader[ 10 ], Message[ 5 ];

	fd_set ReadSet, AllSet;

	FD_ZERO( &AllSet );
	FD_SET( ServerSocketId, &AllSet );

	fdmax = ServerSocketId;

	while( 1 )
	{
		ReadSet = AllSet;
		trace( "HSM Simulator Waiting for Request....." );
		if( select( fdmax + 1, &ReadSet, NULL, NULL, NULL ) < 0 )
		{
			trace( "Error in Select System Call....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			break;
		}
		if( FD_ISSET ( ServerSocketId , &ReadSet ) )
		{
			SockAddrSize = sizeof( struct sockaddr_in );
			ConnectionId = accept( ServerSocketId, ( struct sockaddr * ) &cliaddr,  ( socklen_t * ) &SockAddrSize );
			if( ConnectionId < 0 )
			{
				trace( "Error in accepting connection from client...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				continue;
			}
			trace( "Accepted Connection from IpAddress[%s] with ConnectionId[%d] fdmax[%d].....", ClientIpAddress, ConnectionId, fdmax );
			if( ConnectionId > fdmax )
				fdmax = ConnectionId;
			if( addDescriptorList( ConnectionId ) < 0 )
			{
				trace( "Error in adding ConnectionId[%d] in Descriptor List...", ConnectionId );
				close( ConnectionId );
				continue;
			}
			FD_SET( ConnectionId, &AllSet );
		}
		else
		{
			for( int i = 0; i < hsmparam.MaxClients; i++ )
			{
				ConnectionId = desc_list_ptr[ i ];
				if( FD_ISSET( ConnectionId, &ReadSet ) )
				{
					trace( "Got Message from ConnectionId[%d]", ConnectionId );
					break;
				}
			}
			memset( tcpipHeader, 0, sizeof( tcpipHeader ) );
			if( recv( ConnectionId, tcpipHeader, HeaderLen, 0 ) <= 0 )
			{
				trace( "Connection Closed by ConnectionId[%d]", ConnectionId );
				close( ConnectionId );
				FD_CLR( ConnectionId, &AllSet );
				deleteDescriptorList( ConnectionId );
			}
			else
			{
				if( HeaderType == HEADER_ASCII )
				{
					MsgSize = atoi( tcpipHeader );
					trace( "Waiting to read[%d] Bytes from ConnectionId[%d]", MsgSize, ConnectionId );
					memset( tcpipMsg, 0, sizeof( tcpipMsg ) );
					if( recv( ConnectionId, tcpipMsg, MsgSize, 0 ) <= 0 )
					{
						trace( "Connection Closed by ConnectionId[%d]", ConnectionId );
						close( ConnectionId );
						FD_CLR( ConnectionId, &AllSet );
						deleteDescriptorList( ConnectionId );
					}
					hex_dump( tcpipmsg, MsgSize );
					processHSMRequest( ConnectionId, tcpipmsg, MsgSize );
				}
				else
				{
					memcpy( &MsgSize, tcpipHeader, HeaderLen );
					MsgSize = ntohs( MsgSize );
					memset( tcpipMsg, 0, sizeof( tcpipMsg ) );
					if( recv( ConnectionId, tcpipMsg, MsgSize, 0 ) <= 0 )
					{
						trace( "Connection Closed by ConnectionId[%d]", ConnectionId );
						close( ConnectionId );
						FD_CLR( ConnectionId, &AllSet );
						deleteDescriptorList( ConnectionId );
					}
					hex_dump( tcpipmsg, MsgSize );
					processHSMRequest( ConnectionId, tcpipmsg, MsgSize );
				}
			}
		}
	}
}


