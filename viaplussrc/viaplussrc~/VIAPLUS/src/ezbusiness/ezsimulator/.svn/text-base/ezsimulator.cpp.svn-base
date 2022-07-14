#include <ezbusiness/ezsimulator.h>

void *tcpip_client_thread( void *threadmsg )
{
	EzSimulator *thmsg = ( EzSimulator * ) threadmsg;
	pthread_cond_t EventCond;
	pthread_mutex_t EventMutex;
	struct timeval now;
	struct timespec timeout;

	pthread_cond_init( &EventCond, NULL );
	pthread_mutex_init( &EventMutex, NULL );

	thmsg->trace( "Client thread started for connecting with IpAddress[%s] PortNo[%d]...", thmsg->ClientIpAddress, thmsg->ClientPort );

	pthread_mutex_lock( &EventMutex );
	thmsg->ConnectionFlag = false;
	pthread_mutex_unlock( &EventMutex );

	while( 1 )
	{
		thmsg->ClientSocketId = thmsg->createSocket( 2 );
		if( thmsg->ClientSocketId < 0 )
		{
			thmsg->trace( "Error in Creating Client SocketId...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 3;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
			continue;
		}
		else
			thmsg->trace("Client Socket Created[%d] With Id", thmsg->ClientSocketId );
		if( thmsg->connectServer() < 0 )
		{
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 3;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
			close( thmsg->ClientSocketId );
			continue;
		}
		else
			thmsg->trace( "Client Connected With Switch..");
		thmsg->trace( "SimType[%s]", thmsg->SimType );
		if( !strcmp( thmsg->SimType, "ATM" ) )
		{
			if( thmsg->atmsimobj.composePowerUpMessage( thmsg->ClientSocketId, thmsg->DeviceSubType ) < 0 )
			{
				gettimeofday( &now, NULL );
				timeout.tv_sec = now.tv_sec + 3;
				timeout.tv_nsec = now.tv_usec * 1000;
				pthread_mutex_lock( &EventMutex );
				pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
				pthread_mutex_unlock( &EventMutex );
				close( thmsg->ClientSocketId );
				continue;
			}
		}
		break;
	}
	pthread_mutex_lock( &EventMutex );
	thmsg->ConnectionFlag = true;
	pthread_mutex_unlock( &EventMutex );
	return ( void * ) 1;
}

int EzSimulator :: createSocket( int TypeId )
{
	int sockfd;
	int flag = 1;
	struct linger lng;
	lng.l_onoff = 1;
	lng.l_linger = 0;

	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if( sockfd < 0 )
	{
		trace( " Error in Creating Socket ...Error [%s] ", strerror( errno ) );
		return -1;
	}
	trace( "Socket Created With Id[%d]", sockfd );
	if( setsockopt( sockfd, SOL_SOCKET, SO_LINGER, &lng, sizeof( lng ) ) < 0 )
	{
		trace( " Error in Setting Socket Option ...Error [%s] ", strerror( errno ) );
		return -1;
	}

	if( TypeId == 1 )
	{
		flag = 1;
		if( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof( flag ) ) < 0 )
			return -1;
		flag = 1;
		if( setsockopt( sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof( flag ) ) < 0 )
			return -1;
	}

	if( TypeId == 1 )
	{
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons( ServerPort );
		saddr.sin_addr.s_addr = INADDR_ANY;
		memset( &saddr.sin_zero, 0, 8 );

		if( bind( sockfd, ( sockaddr * ) &saddr, sizeof( saddr ) ) < 0 )
		{
			trace( " Error in Binding Socket ....Error [%s] ", strerror( errno ) );
			return -1;
		}

		if( listen( sockfd, 1 ) < 0 )
		{
			trace( " Socket Listen error ....Error [%s] ", strerror( errno ) );
			return -1;
		}
	}
	return sockfd;
}

int EzSimulator :: connectServer()
{
	socklen_t addlen = sizeof( saddr );

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( ClientPort );
	saddr.sin_addr.s_addr = inet_addr( ClientIpAddress );
	memset( &saddr.sin_zero, 0, 8 );
	if( connect( ClientSocketId, ( struct sockaddr * ) &saddr, addlen ) < 0 )
	{
		trace( "Error in Connecting IpAddress[%s] PortNo[%d]....ErrNo[%d] SysErr[%s]", ClientIpAddress, ClientPort, errno, strerror( errno ) );
		return -1;
	}
	return 1;
}
void EzSimulator :: getToken( const char *FieldStr, char *TokenStr, int TokenNo, char Token )
{
    for( int i = 0, j = 0, cnt = 0; i < strlen( FieldStr ); i++ )
    {
            if( FieldStr[ i ] == Token )
                    cnt++;
            else if ( cnt == TokenNo )
                    break;
            else if ( cnt + 1 == TokenNo )
            {
                    TokenStr[ j ] = FieldStr[ i ];
                    j++;
            }
    }
}
int EzSimulator :: initSimulator( const char *SimId )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ],CfgParam[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", SimId );

	if( openDebug( logpath, SimId ) < 0 )
		exit( 0 );

	SetDebug();

	strcpy( this->SimId, SimId );

	trace( "^^^^^^^^^^^%s Started^^^^^^^^^^^^^", SimId );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzSimulator Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsimulator.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace(  " Error in opening file [%s] ", cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
		closeDebug();
		TaskExit();
	}

	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "%s#%s", SimId, "SIMTYPE" );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	else
		strcpy( SimType, cfgVal );
	
	if( !strcasecmp( SimType, "ATM" ) )
	{
		memset( CfgParam, 0, sizeof( CfgParam ) );
		sprintf( CfgParam, "%s#%s", SimId, "DEVICESUBTYPE" );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
			trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
			cfgutil.cfg_close();
			closeDebug();
			TaskExit();
		}
		else
			strcpy( DeviceSubType, cfgVal );
		if( strcasecmp( DeviceSubType, "D912") && strcasecmp( DeviceSubType, "NDC+" ) )
		{
			trace( "Configured Wrong DeviceSubType[%s] For ATM Device, DeviceSubType Should Be Either D912 Or NDC+", DeviceSubType );
			trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
			cfgutil.cfg_close();
			closeDebug();
			TaskExit();
		}
	}

		
	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "%s#%s", SimId, "SERVER_PORT" );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	else
		ServerPort = atoi( cfgVal );

	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "%s#%s", SimId, "CLIENT_IP" );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	else
	{
		memset( ClientIpAddress, 0, sizeof( ClientIpAddress ) );
		strcpy( ClientIpAddress, cfgVal );
	}

	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "%s#%s", SimId, "CLIENT_PORT" );

	memset( cfgVal, 0, sizeof( cfgVal ) );
	if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
		trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	else
		ClientPort = atoi( cfgVal );

	cfgutil.cfg_close();
	if( atmsimobj.InitAtmSimulator( this, SimId ) < 0 )
	{
		trace( "Unable To Initialize AtmSimulator..");
		return -1;
	}
	trace( "Initialized AtmSimulator Successfully..");
	
	TaskInit();
	initEzSigUtil( this );
	return 1;
}

int EzSimulator :: CreateConnectionThread()
{
	pthread_t ConnectionThread;

	pthread_attr_t thr_attr;
	pthread_attr_init( &thr_attr );
	pthread_attr_setdetachstate( &thr_attr, 1 );

	if( pthread_create( &ConnectionThread, &thr_attr, tcpip_client_thread, this ) != 0 )
	{
		trace( "Error in Creating Connection Thread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzSimulator :: acceptConnection()
{
	socklen_t addlen = sizeof( saddr );
	int clientfd;
	trace( "Waiting For Accept..");
	clientfd = accept( ServerSocketId, ( struct sockaddr * ) &saddr, &addlen );

	if( clientfd < 0 )
	{
		trace( "Error while Accepting New Connection....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	trace( "Connection Accepted from IpAddress[%s] with ConnectionId[%d]", inet_ntoa( saddr.sin_addr ), clientfd );
	return clientfd;
}
int EzSimulator :: processRequest( const char *ReqMessage, char *RespMessage )
{
	char Chn[ 20 ],DeviceType[ 15 ],PIN[ 5 ],Amount[ 13 ], CommandType[ 50 ],DeviceProtocol[ 20 ],TxnCode[ 20 ];
	trace( "ReqMessage[%s]", ReqMessage );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	getToken( ReqMessage, DeviceType, 1, 0x1c );

	trace( "DeviceType[%s]", DeviceType );
	if( !strcasecmp( DeviceType, "ATM" ) )
	{
		memset( DeviceProtocol, 0, sizeof( DeviceProtocol ) );
		getToken( ReqMessage, DeviceProtocol, 2, 0x1c );
		trace( "DeviceProtocol[%s]", DeviceProtocol );
		if( !strcasecmp( DeviceProtocol, "D912" ) )
		{
			memset( CommandType, 0, sizeof( CommandType ) );
			getToken( ReqMessage, CommandType, 3, 0x1c );
			if( !strcasecmp( CommandType, "TXN" ) )
			{
				memset( Chn, 0, sizeof( Chn ) );
				getToken( ReqMessage, Chn, 4, 0x1c );
				memset( PIN, 0, sizeof( PIN ) );
				getToken( ReqMessage, PIN, 5, 0x1c );
				memset( TxnCode, 0, sizeof( TxnCode ) );
				getToken( ReqMessage, TxnCode, 6, 0x1c );
				memset( Amount, 0, sizeof( Amount ) );
				getToken( ReqMessage, Amount, 7, 0x1c );
				trace( "Amount[%s]", Amount );
				if( atmsimobj.composeTxnReq( Chn, PIN, atoi( TxnCode ), atoi( Amount ), RespMessage ) < 0 )
				{
					return -1;
				}
			}
			else if( !strcasecmp( CommandType, "GOODACK" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, READY );
			}
			else if( !strcasecmp( CommandType, "FULLREV" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, DISPENSOR_FAULT );
			}
			else if( !strcasecmp( CommandType, "PARTIALREV" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, DISPENSOR_FAULT )	;
			}
			else if( !strcasecmp( CommandType, "SUSPECTREV" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, UNCERTAIN_DISPENSE );
			}
		}
		else if( !strcasecmp( DeviceProtocol, "NDC+" ) )
		{
			memset( CommandType, 0, sizeof( CommandType ) );
			getToken( ReqMessage, CommandType, 3, 0x1c );
			if( !strcasecmp( CommandType, "TXN" ) )
			{
				memset( Chn, 0, sizeof( Chn ) );
				getToken( ReqMessage, Chn, 4, 0x1c );
				memset( PIN, 0, sizeof( PIN ) );
				getToken( ReqMessage, PIN, 5, 0x1c );
				memset( TxnCode, 0, sizeof( TxnCode ) );
				getToken( ReqMessage, TxnCode, 6, 0x1c );
				memset( Amount, 0, sizeof( Amount ) );
				getToken( ReqMessage, Amount, 7, 0x1c );
				if( atmsimobj.composeTxnReq( Chn, PIN, atoi( TxnCode ), atoi( Amount ), RespMessage ) < 0 )
				{
					return -1;
				}
			}
			else if( !strcasecmp( CommandType, "GOODACK" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, READY );
			}
			else if( !strcasecmp( CommandType, "FULLREV" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, DISPENSOR_FAULT );
			}
			else if( !strcasecmp( CommandType, "PARTIALREV" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, DISPENSOR_FAULT )	;
			}
			else if( !strcasecmp( CommandType, "SUSPECTREV" ) )
			{
				atmsimobj.composeSolicitedMessage( RespMessage, UNCERTAIN_DISPENSE );
			}
		}
		else
		{
			trace( "Invalid DeviceProtocol[%s]", DeviceProtocol );
			return -1;
		}
			
	}
	else
	{
		trace( "Invalid DeviceType[%s]", DeviceType );
		return -1;
	}
	return 1;
}
int EzSimulator ::  composeBadResponse( const char *ReqMessage, char *RespMessage, int RespCode )
{
	EzCfgUtil cfgutil;
	char CfgParam[ CFG_VAL_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ], ScreenNo[ 4 ],Template[ 50 ];
	
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsimulator.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace(  " Error in opening file [%s] ", cfgpath );
		return -1;
	}
	
	memset( cfgVal, 0, sizeof( cfgVal ) );
	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "RESPCODE#%d", RespCode );
	if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
		cfgutil.cfg_close();
		return -1;
		
	}
	else
	{
		strcpy( ScreenNo,cfgVal );
		trace(  "Got ScreenNo[%s] For RespCode[%d]", ScreenNo, RespCode );
	}
	
	memset( cfgVal, 0, sizeof( cfgVal ) );
	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "RESPCODE#%d", RespCode );
	if( cfgutil.cfg_search( CfgParam, cfgVal, 3 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	else
	{
		strcpy( Template,cfgVal );
		trace(  "Got Template[%s] For RespCode[%d]", Template, RespCode );
	}
	sprintf( RespMessage, "%s%c%s%c%s", ReqMessage, 0x1c, ScreenNo, 0x1c, Template );
	return 1;
}
int EzSimulator :: composeResponse( const char *SimMsg, const char *ReqMessage, char *RespMessage )
{
	char ScreenNo[ 4 ],SwitchMsg[ 600 ], Template[ 600 ],Balance[ 20 ], Pcode[ 7 ];
	
	memset( ScreenNo, 0, sizeof( ScreenNo ) );
	memset( SwitchMsg, 0, sizeof( SwitchMsg ) );
	memset( Template, 0, sizeof( Template ) );
	memset( Balance, 0, sizeof( Balance ) );
	
	getToken( ReqMessage, SwitchMsg, 6, 0x1c );
	trace( "SwitchScreenMsg[%s] and Len[%d]", SwitchMsg, strlen( SwitchMsg ) );
	strncpy( ScreenNo, &SwitchMsg[ 5 ], 3 );
	trace( "ScreenNo[%s]", ScreenNo );
	memset( Pcode, 0, sizeof( Pcode ) );
	getToken( SimMsg, Pcode, 6, 0x1c );
	trace( "PCode[%s]", Pcode );
	if( strlen( ReqMessage ) > 32 )
	{
		if( !strcmp( Pcode, "301000" ) || !strcmp( Pcode, "302000" ) )
		{
			strncpy( Balance, &SwitchMsg[ strlen( SwitchMsg ) - 12 ], 12 );
			trace( "Balance[%s]", Balance );
			memset( SwitchMsg, 0, sizeof( SwitchMsg ) );
			getToken( ReqMessage, SwitchMsg, 7, 0x1c );
			strncpy( Template, &SwitchMsg[ 6 ], strlen( SwitchMsg ) - 6 );
			sprintf( RespMessage, "%s%c%s%c%s%c%s", SimMsg, 0x1c, ScreenNo, 0x1c, Balance, 0x1c, Template );
		}
		else if( !strcmp( Pcode, "11000" ) || !strcmp( Pcode, "011000" ) || !strcmp( Pcode, "12000" ) || !strcmp( Pcode, "012000" ))	
		{
			memset( SwitchMsg, 0, sizeof( SwitchMsg ) );
			getToken( ReqMessage, SwitchMsg, 7, 0x1c );
			if( strlen( SwitchMsg ) )
			{
				strncpy( Template, &SwitchMsg[ 6 ], strlen( SwitchMsg ) - 6 );
				sprintf( RespMessage, "%s%c%s%c%s", SimMsg, 0x1c, ScreenNo, 0x1c, Template );
			}
		}
		else if( !strcmp( Pcode, "381000" ) || !strcmp( Pcode, "382000" ) )
		{
			memset( SwitchMsg, 0, sizeof( SwitchMsg ) );
			getToken( ReqMessage, SwitchMsg, 7, 0x1c );
			strncpy( Template, &SwitchMsg[ 6 ], strlen( SwitchMsg ) - 6 );
			sprintf( RespMessage, "%s%c%s%c%s", SimMsg, 0x1c, ScreenNo, 0x1c, Template );
		}
	}
	else
		sprintf( RespMessage, "%s%c%s%c", SimMsg, 0x1c, ScreenNo,0x1c );
		
	return 1;
}
int EzSimulator :: writemsg( int ConnectionId, const char *Msg, int Size )
{
	char SendBuffer[ 1024 ];
	int retval;
	memset( SendBuffer, 0, sizeof( SendBuffer ) );
	sprintf( SendBuffer, "%04d%s", strlen( Msg ), Msg );
	retval = write( ConnectionId, SendBuffer, strlen( SendBuffer ) );
	if( retval < 0 )
    {
    	trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
    	return -1;
    }
    trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", Msg, retval );
    hex_dump( ( unsigned char *)SendBuffer, strlen( SendBuffer ) );
	return 1;
}
int EzSimulator :: startSim( )
{
	pthread_cond_t EventCond;
	pthread_mutex_t EventMutex;
	struct timeval now;
	struct timespec timeout;
	bool ConnFlag;
	char MessageHeader[ 5 ], ReqMessage[ 512 ], RespMessage[ 512 ],SimMsg[ 512 ] ;
	int ConnectionId, MsgLen, retval;
		
	pthread_cond_init( &EventCond, NULL );
	pthread_mutex_init( &EventMutex, NULL );

	while( 1 )
	{
		ServerSocketId = createSocket( 1 );
		if( ServerSocketId < 0 )
		{
			trace( "Error in Creating Server SocketId...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 3;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
			continue;
		}
		break;
	}

	if( CreateConnectionThread() < 0 )
	{
		trace( "Error in Creating Connection Thread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
		closeDebug();
		TaskExit();
	}

	while( 1 )
	{
		ConnectionId = acceptConnection( );
		if( ConnectionId < 0 )
		{
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 3;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
			continue;
		}

		while( 1 )
		{
			trace( "Waiting for Message from Socket...." );

			memset( MessageHeader, 0, sizeof( MessageHeader ) );
			if( recv( ConnectionId, MessageHeader, 4, 0 ) <= 0 )
			{
				trace( "Error in Message Header from Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ConnectionId );
				break;
			}
			MsgLen = atoi( MessageHeader );

			trace( "[%d] Bytes available in Connection Socket", MsgLen );
			memset( ReqMessage, 0, sizeof( ReqMessage ) );
			if( recv( ConnectionId, ReqMessage, MsgLen, 0 ) <= 0 )
			{
				trace( "Error in Message Header from Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ConnectionId );
				break;
			}

			trace( "Received Message[%s] from Connection Socket....", ReqMessage );
			hex_dump( ( unsigned char *)ReqMessage, MsgLen );
			pthread_mutex_lock( &EventMutex );
			ConnFlag = ConnectionFlag;
			pthread_mutex_unlock( &EventMutex );

			if( !ConnFlag )
			{
				trace( "Switch is not Connected....." );
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_NOT_CONNECTED );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
					close( ConnectionId );
					break;
				}
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
				continue;
			}
			memset( SimMsg, 0, sizeof( SimMsg ) );
			strcpy( SimMsg, ReqMessage );
			memset( RespMessage, 0, sizeof( RespMessage ) );
			MsgLen = processRequest( ReqMessage, RespMessage );
			if( MsgLen < 0 )
			{
				trace( "Cannot Process Request[%s]", ReqMessage );
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_FORMAT_ERR );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					close( ConnectionId );
					break;
				}
				continue;
			}

			retval = writemsg( ClientSocketId, RespMessage, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Client Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ClientSocketId );
				CreateConnectionThread();
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_NOT_CONNECTED );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
					close( ConnectionId );
					break;
				}
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
				continue;
			}
			trace( "Written Message[%s] of Bytes[%d] to Client Socket Socket...", RespMessage, retval );

			memset( MessageHeader, 0, sizeof( MessageHeader ) );
			if( recv( ClientSocketId, MessageHeader, 4, 0 ) <= 0 )
			{
				trace( "Error in Message Header from ClientSocketId Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ClientSocketId );
				CreateConnectionThread( );
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_NOT_CONNECTED );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
					close( ConnectionId );
					break;
				}
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
				continue;
			}
			MsgLen = atoi( MessageHeader );
			trace( "[%d] Bytes available in Switch Connection Socket", MsgLen );
			memset( ReqMessage, 0, sizeof( ReqMessage ) );
			if( recv( ClientSocketId, ReqMessage, MsgLen, 0 ) <= 0 )
			{
				trace( "Error in Message Header from Client Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ClientSocketId );
				CreateConnectionThread();
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_NOT_CONNECTED );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
					close( ConnectionId );
					break;
				}
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
				continue;
			}
			trace( "Received Switch Message[%s] from Connection Socket....", ReqMessage );
			memset( RespMessage, 0, sizeof( RespMessage ) );
			MsgLen = composeResponse( SimMsg, ReqMessage, RespMessage );
			retval = writemsg( ConnectionId, RespMessage, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ConnectionId );
				break;
			}
			else
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
			//Added on 220410
			/*memset( MessageHeader, 0, sizeof( MessageHeader ) );
			if( recv( ConnectionId, MessageHeader, 4, 0 ) <= 0 )
			{
				trace( "Error in Message Header from Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ConnectionId );
				break;
			}
			MsgLen = atoi( MessageHeader );

			trace( "[%d] Bytes available in Connection Socket", MsgLen );
			memset( ReqMessage, 0, sizeof( ReqMessage ) );
			if( recv( ConnectionId, ReqMessage, MsgLen, 0 ) <= 0 )
			{
				trace( "Error in Message Header from Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ConnectionId );
				break;
			}

			trace( "Received Message[%s] from Connection Socket....", ReqMessage );
			hex_dump( ( unsigned char *)ReqMessage, MsgLen );
			pthread_mutex_lock( &EventMutex );
			ConnFlag = ConnectionFlag;
			pthread_mutex_unlock( &EventMutex );

			if( !ConnFlag )
			{
				trace( "Switch is not Connected....." );
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_NOT_CONNECTED );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
					close( ConnectionId );
					break;
				}
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
				continue;
			}
			memset( SimMsg, 0, sizeof( SimMsg ) );
			strcpy( SimMsg, ReqMessage );
			memset( RespMessage, 0, sizeof( RespMessage ) );
			MsgLen = processRequest( ReqMessage, RespMessage );
			if( MsgLen < 0 )
			{
				trace( "Cannot Process Request[%s]", ReqMessage );
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_FORMAT_ERR );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					close( ConnectionId );
					break;
				}
				continue;
			}

			retval = writemsg( ClientSocketId, RespMessage, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Client Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
				close( ClientSocketId );
				CreateConnectionThread();
				memset( RespMessage, 0, sizeof( RespMessage ) );
				MsgLen = composeBadResponse( ReqMessage, RespMessage, RESP_NOT_CONNECTED );
				retval = writemsg( ConnectionId, RespMessage, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
					close( ConnectionId );
					break;
				}
				trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", RespMessage, retval );
				continue;
			}
			trace( "Written Message[%s] of Bytes[%d] to Client Socket Socket...", RespMessage, retval );
			*/

		}
	}
}
int main( int argc, char **argv )
{
	EzSimulator simobj;
	simobj.initSimulator( argv[ 0 ] );
	simobj.startSim( );
}




