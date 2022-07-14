#include <ezbusiness/ezsmsdriver.h>

void EzSMSDriver :: initSMSDriver( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsmsdriver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzSMSDriver Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "EzSMSDriver alreading running" );
		trace( "^^^^^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( SMSDRIVERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", SMSDRIVERCHANNEL );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initSMSInfoQueue( this ) < 0 )
	{
		trace( "Error in Initializing SMSInfoQueue...." );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initSMSDriverUtil( this ) < 0 )
	{
		trace( "Error in Initializing SMSDriverUtil...." );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( createGSMSharedMemory() < 0 )
	{
		trace( "Error in Creating GSM Shared Memory...." );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initGSMPorts() < 0 )
	{
		trace( "Error in Initializing GSM Ports...." );
		trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void* serviceGSMThread( void *threadmsg )
{
	EzSMSDriver *thmsg = ( EzSMSDriver * ) threadmsg;
	struct EzGSMInfoTable gsminfo_rec;
	struct timeval now;
	struct timespec timeout;
	int GSMConnectionId, retval, MsgLen;
	char SMSBuffer[ SMS_BUFFER_SIZE + 1 ], RespBuffer[ SMS_BUFFER_SIZE + 1 ], GSMRespCmd[ SMS_BUFFER_SIZE + 1 ];
	struct EzSMSRespMsg smsrespmsg;
	pthread_cond_t GSMThreadCond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t GSMThreadMutex = PTHREAD_MUTEX_INITIALIZER;
	bool CloseDescriptorFlag = true;

	thmsg->trace( DEBUG_TEST, "GSM Thread with Id[%d] Started...", pthread_self() );

	while( 1 )
	{
		memset( &gsminfo_rec, 0, sizeof( struct EzGSMInfoTable ) );
		if( thmsg->searchGSMInfo( pthread_self(), &gsminfo_rec ) < 0 )
		{
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 1;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &GSMThreadMutex );
			pthread_cond_timedwait( &GSMThreadCond, &GSMThreadMutex, &timeout );
			pthread_mutex_unlock( &GSMThreadMutex );
		}
		else
			break;
	}

	thmsg->trace( DEBUG_NORMAL, "GSM Thread with GSMPort[%s] GSMThreadId[%d] GSMAddress[%s] GSMPortNo[%d] Started....", gsminfo_rec.GSMPort, gsminfo_rec.GSMThreadId, gsminfo_rec.GSMAddress, gsminfo_rec.GSMPortNo );

	if( gsminfo_rec.GSMProtocol == GSM_PROTOCOL_SERIAL )
	{
		while( 1 )
		{
			retval = thmsg->updateGSMStatus(  gsminfo_rec.GSMPort, GSM_STATUS_INIT );
			if( retval < 0 )
			{
				thmsg->trace( "Error in Updating GSMStatus for GSMPort[%s]", gsminfo_rec.GSMPort );
				break;
			}

			if( CloseDescriptorFlag )
			{
				retval = thmsg->updateGSMConnStatus(  gsminfo_rec.GSMPort, GSM_STATUS_DISCONNECTED );
				if( retval < 0 )
				{
					thmsg->trace( "Error in Updating GSM Connectivity Status for GSMPort[%s]", gsminfo_rec.GSMPort );
					break;
				}
				thmsg->trace( DEBUG_TEST, "Serial Protocol Configured for GSMPort[%s]", gsminfo_rec.GSMPort );

				GSMConnectionId = thmsg->openGSMSerialPort( gsminfo_rec.srlinfo );

				if( GSMConnectionId < 0 )
				{
					thmsg->trace( "Error in Opening GSMPort[%s]", gsminfo_rec.GSMAddress );
					gettimeofday( &now, NULL );
					timeout.tv_sec = now.tv_sec + 3;
					timeout.tv_nsec = now.tv_usec * 1000;
					pthread_cond_timedwait( &GSMThreadCond, &GSMThreadMutex, &timeout );
					continue;
				}
				thmsg->trace( DEBUG_TEST, "Opened GSM Serial Port[%s]", gsminfo_rec.GSMAddress );

				retval = thmsg->updateGSMConnStatus(  gsminfo_rec.GSMPort, GSM_STATUS_CONNECTED );
				if( retval < 0 )
				{
					thmsg->trace( "Error in Updating GSM Connectivity Status for GSMPort[%s]", gsminfo_rec.GSMPort );
					break;
				}

				retval = thmsg->updateGSMConnectionId(  gsminfo_rec.GSMPort, GSMConnectionId );
				if( retval < 0 )
				{
					thmsg->trace( "Error in Updating GSM ConnectionId[%d] for GSMPort[%s]", GSMConnectionId, gsminfo_rec.GSMPort );
					break;
				}

			}

			CloseDescriptorFlag = false;

			if( thmsg->initGSMModem( gsminfo_rec, GSMConnectionId ) < 0 )
				continue;

			thmsg->trace( "GSMPort[%s] with Address[%s] Initialized Successfully.....", gsminfo_rec.GSMPort, gsminfo_rec.GSMAddress );

			retval = thmsg->updateGSMStatus(  gsminfo_rec.GSMPort, GSM_STATUS_RUNNING );
			if( retval < 0 )
			{

				thmsg->trace( "Error in Updating GSM Connectivity Status for GSMPort[%s]", gsminfo_rec.GSMPort );
				break;
			}

			while( 1 )
			{
				retval = thmsg->readAsyncGSMSerialPortMsg( gsminfo_rec, GSMConnectionId, SMSBuffer );

				if( retval == -2 )
					break;

				if( retval < 0 )
				{
					thmsg->trace( "Error in Reading Message From Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					close( GSMConnectionId );
					CloseDescriptorFlag = true;
					gettimeofday( &now, NULL );
					timeout.tv_sec = now.tv_sec + 3;
					timeout.tv_nsec = now.tv_usec * 1000;
					pthread_mutex_lock( &GSMThreadMutex );
					pthread_cond_timedwait( &GSMThreadCond, &GSMThreadMutex, &timeout );
					pthread_mutex_unlock( &GSMThreadMutex );
					break;
				}

				memset( &smsrespmsg, 0, sizeof( struct EzSMSRespMsg ) );
				if( thmsg->decomposeAsyncGSMMsg( SMSBuffer, &smsrespmsg ) < 0 )
						continue;

				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				MsgLen = thmsg->composeApplicationMsg( &smsrespmsg, SMSBuffer );
				if( thmsg->WriteChannel( smsrespmsg.ApplicationChannel, SMSBuffer, MsgLen ) < 0 )
					thmsg->trace( "Error in Writing Message[%s] to Application Channel[%s]", SMSBuffer, smsrespmsg.ApplicationChannel );
				else
					thmsg->trace( "Written Message[%s] to Application Channel[%s]", SMSBuffer, smsrespmsg.ApplicationChannel );
			}
		}
	}
	else
	{
		thmsg->trace( DEBUG_TEST, "TCP/IP Protocol Configured for GSMPort[%s]", gsminfo_rec.GSMPort );
	}
	return ( void * ) 1;
}

int EzSMSDriver :: openGSMSerialPort( struct EzSerialPortInfo srlinfo )
{
	struct termios oldoptions, options;
	int ConnFd;
	long BAUD;
	short DATABITS, STOPBITS, PARITYON, PARITY;

	/*if( chmod( srlinfo.SerialPort, S_IROTH | S_IWOTH | S_IXOTH ) < 0 )
		trace( "Error in chmod...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	*/

	if( srlinfo.ReadMode == SERIAL_MODE_BLOCKING )
	{
		trace( DEBUG_TEST, "Opening Serial Port[%s]....in Blocking Mode", srlinfo.SerialPort );
		ConnFd = open( srlinfo.SerialPort, O_CREAT | O_RDWR | O_NOCTTY );
	}
	else
	{
		trace( DEBUG_TEST, "Opening Serial Port[%s]....in Non-Blocking Mode", srlinfo.SerialPort );
		ConnFd = open( srlinfo.SerialPort, O_CREAT | O_RDWR | O_NOCTTY | O_NDELAY );
	}

	if( ConnFd < 0 )
	{
		trace( "Error in Opening Serial Port[%s] SysErr[%s] ErrNo[%d]", srlinfo.SerialPort, strerror( errno ), errno );
		return -1;
	}

	trace( "Opened GSM Serial Port[%s] with ConnectionId[%d]", srlinfo.SerialPort, ConnFd );

	fcntl( ConnFd, F_SETFL, 0 );
	fcntl( ConnFd, F_SETOWN, getpid() );

	switch ( srlinfo.BaudRate )
	{
		case 57600:
			BAUD = B57600;
			break;
		case 115200:
			BAUD = B115200;
			break;
		case 230400:
			BAUD  = B230400;
			break;
		case 460800:
			BAUD  = B460800;
			break;
		case 500000:
			BAUD  = B500000;
			break;
		case 576000:
			BAUD  = B576000;
			break;
		case 921600:
			BAUD  = B921600;
			break;
		case 1000000:
			BAUD  = B1000000;
			break;
		case 1152000:
			BAUD  = B1152000;
			break;
		case 1500000:
			BAUD  = B1500000;
			break;
		case 2000000:
			BAUD  = B2000000;
			break;
		case 2500000:
			BAUD  = B2500000;
			break;
		case 3000000:
			BAUD  = B3000000;
			break;
		case 3500000:
			BAUD  = B3500000;
			break;
		case 4000000:
			BAUD  = B4000000;
			break;
		case 9600:
			BAUD  = B9600;
			break;
		default:
			BAUD  = B9600;
			break;
	}

	switch ( srlinfo.DataBits )
	{
		case 8:
			DATABITS = CS8;
	        break;
		case 7:
			DATABITS = CS7;
			break;
		case 6:
			DATABITS = CS6;
			break;
		case 5:
			DATABITS = CS5;
			break;
		default:
			DATABITS = CS8;
	        break;
	}

	switch ( srlinfo.StopBits )
	{
		case 1:
			STOPBITS = 0;
			break;
		case 2:
			STOPBITS = CSTOPB;
			break;
		default:
			STOPBITS = 0;
			break;
	}

	if( srlinfo.Parity == SERIAL_PARITY_NONE )
	{
		PARITYON = 0;
		PARITY = 0;
	}
	else if( srlinfo.Parity == SERIAL_PARITY_ODD )
	{
		PARITYON = PARENB;
		PARITY = PARODD;
	}
	else if ( srlinfo.Parity == SERIAL_PARITY_EVEN )
	{
		PARITYON = PARENB;
		PARITY = 0;
	}
	else
	{
		PARITYON = 0;
		PARITY = 0;
	}

	tcgetattr( ConnFd, &oldoptions );

	options.c_cflag = BAUD | CRTSCTS | DATABITS | STOPBITS | PARITYON | PARITY | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG );
	options.c_cc[VMIN] = srlinfo.MinChar;
	options.c_cc[VTIME] = srlinfo.ReadTimeOut;

	tcflush( ConnFd, TCIFLUSH );
	tcsetattr( ConnFd, TCSANOW, &options);

	return ConnFd;

}

bool EzSMSDriver :: isGoodResponse( const char *SMSBuffer, const char *RespBuffer )
{
	char GSMRespCmd[ SMS_BUFFER_SIZE + 1 ];

	memset( GSMRespCmd, 0, sizeof( GSMRespCmd ) );
	getGSMRespCmd( RespBuffer, GSMRespCmd );

	strcat( GSMRespCmd, "\r\n" );
	if( strcmp( GSMRespCmd, SMSBuffer ) )
		return false;

	memset( GSMRespCmd, 0, sizeof( GSMRespCmd ) );
	getGSMResp( RespBuffer, GSMRespCmd );
	if( strcmp( GSMRespCmd, "OK" ) )
		return false;

	return true;
}

bool EzSMSDriver :: isBadResponse( const char *SMSBuffer, const char *RespBuffer )
{
	char GSMRespCmd[ SMS_BUFFER_SIZE + 1 ];

	memset( GSMRespCmd, 0, sizeof( GSMRespCmd ) );
	getGSMRespCmd( RespBuffer, GSMRespCmd );

	strcat( GSMRespCmd, "\r\n" );
	if( strcmp( GSMRespCmd, SMSBuffer ) )
		return false;

	memset( GSMRespCmd, 0, sizeof( GSMRespCmd ) );
	getGSMResp( RespBuffer, GSMRespCmd );
	if( strcmp( GSMRespCmd, "ERROR" ) )
		return false;

	return true;
}

int EzSMSDriver :: initGSMModem( struct EzGSMInfoTable gsminfo_rec, int GSMConnectionId )
{
	char SMSBuffer[ SMS_BUFFER_SIZE + 1 ], RespBuffer[ SMS_BUFFER_SIZE + 1 ];
	int retval, MsgLen;

	while( 1 )
	{
		// SignOn Message

		while( 1 )
		{
			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			MsgLen = composeSignOn( SMSBuffer );

			retval = writeGSMSerialPort( GSMConnectionId, SMSBuffer, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			retval = readAsyncGSMSerialPort( GSMConnectionId, gsminfo_rec.InitCmdTimeOut, RespBuffer );

			if( retval == -1 )
				break;

			if( retval == -2 )
				continue;

			if( !isGoodResponse( SMSBuffer, RespBuffer) )
				continue;

			break;
		}

		if( retval < 0 )
			continue;

		trace( DEBUG_NORMAL, "Received SignOn Response from GSMPort[%s]...", gsminfo_rec.GSMPort );

		// SMS Format

		while( 1 )
		{
			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			MsgLen = composeGSMFormat( SMSBuffer );

			retval = writeGSMSerialPort( GSMConnectionId, SMSBuffer, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			retval = readAsyncGSMSerialPort( GSMConnectionId, gsminfo_rec.InitCmdTimeOut, RespBuffer );

			if( retval == -1 )
				break;

			if( retval == -2 )
				continue;

			if( !isGoodResponse( SMSBuffer, RespBuffer) )
				continue;

			break;
		}

		if( retval < 0 )
			continue;

		trace( DEBUG_NORMAL, "Received GSM Format Response from GSMPort[%s]...", gsminfo_rec.GSMPort );

		// Message Center No

		while( 1 )
		{
			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			MsgLen = composeMsgCenterNo( gsminfo_rec.MsgCenterNo, SMSBuffer );

			retval = writeGSMSerialPort( GSMConnectionId, SMSBuffer, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			retval = readAsyncGSMSerialPort( GSMConnectionId, gsminfo_rec.InitCmdTimeOut, RespBuffer );

			if( retval == -1 )
				break;

			if( retval == -2 )
				continue;

			if( !isGoodResponse( SMSBuffer, RespBuffer) )
				continue;

			break;
		}

		if( retval < 0 )
			continue;

		trace( DEBUG_NORMAL, "Received MCN Response from GSMPort[%s]...", gsminfo_rec.GSMPort );

		if( gsminfo_rec.GSMType == GSM_TYPE_USB )
		{
			//Compose TE Character Set
			while( 1 )
			{
				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				MsgLen = composeTECharSet( SMSBuffer );

				retval = writeGSMSerialPort( GSMConnectionId, SMSBuffer, MsgLen );
				if( retval < 0 )
				{
					trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}

				retval = readAsyncGSMSerialPort( GSMConnectionId, gsminfo_rec.InitCmdTimeOut, RespBuffer );

				if( retval == -1 )
					break;

				if( retval == -2 )
					continue;

				if( !isGoodResponse( SMSBuffer, RespBuffer) )
					continue;

				break;
			}
		}

		if( retval < 0 )
			continue;

		trace( DEBUG_NORMAL, "Received TE Character Set Response from GSMPort[%s]...", gsminfo_rec.GSMPort );

		// Compose Read All Message
		while( 1 )
		{

			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			MsgLen = composeReadAllFormat( SMSBuffer );

			retval = writeGSMSerialPort( GSMConnectionId, SMSBuffer, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			retval = readAsyncGSMSerialPort( GSMConnectionId, gsminfo_rec.InitCmdTimeOut, RespBuffer );

			if( retval == -1 )
				break;

			if( retval == -2 )
				continue;

			if( !isGoodResponse( SMSBuffer, RespBuffer) )
				continue;

			break;
		}

		if( retval < 0 )
			continue;

		trace( DEBUG_NORMAL, "Received Compose Read All Message from GSMPort[%s]...", gsminfo_rec.GSMPort );
		break;
	}
	return 1;
}

int EzSMSDriver :: composeSignOn( char *SMSBuffer )
{
	strcpy( SMSBuffer, "AT\r\n" );
	return ( strlen( SMSBuffer ) );
}

int EzSMSDriver :: composeGSMFormat( char *SMSBuffer )
{
	strcpy( SMSBuffer, "AT+CMGF=1\r\n" );
	return ( strlen( SMSBuffer ) );
}

int EzSMSDriver :: composeMsgCenterNo( const char *MsgCenterNo, char *SMSBuffer )
{
	sprintf( SMSBuffer, "AT+CSCA=\"%s\"\r\n", MsgCenterNo );
	return ( strlen( SMSBuffer ) );
}

int EzSMSDriver :: composeTECharSet( char *SMSBuffer )
{
	strcpy( SMSBuffer, "AT+CSCS=\"GSM\"\r\n" );
	return ( strlen( SMSBuffer ) );
}

int EzSMSDriver :: composeReadAllFormat( char *SMSBuffer )
{
	strcpy( SMSBuffer, "AT+CNMI=1,2,0,0,0\r\n" );
	return ( strlen( SMSBuffer ) );
}

int EzSMSDriver :: getApplicationCode( const char *SMSBuffer, char *ApplicationCode )
{
	int retval = -1;

	if( strlen( SMSBuffer ) <= strlen( getAppCodeSep() ) )
		return retval;

	trace( DEBUG_NORMAL, "AppCodeSep[%s] SMSBuffer[%s]", getAppCodeSep(), SMSBuffer );

	for( int i = 0; i < strlen( SMSBuffer ); i++ )
	{
		if( !strncmp( SMSBuffer + i, getAppCodeSep(), strlen( getAppCodeSep() ) ) )
		{
			strncpy( ApplicationCode, SMSBuffer, i - strlen( getAppCodeSep() ) );
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzSMSDriver :: getApplicationChannel( const char *ApplicationCode, char *ApplicationChannel )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], ParamStr[ 100 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
		return -1;
	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", "APPCODEMAP", ApplicationCode );
	if( cfgutil.cfg_search( ParamStr, ApplicationChannel, 2 ) < 0 )
	{
		cfgutil.cfg_close();
		return -1;
	}
	else
	{
		cfgutil.cfg_close();
		return 1;
	}
}

void EzSMSDriver :: getSMSMessage( const char *SMSBuffer, char *TempBuffer )
{
	bool TxtFound = false, EOTFound = false;

	int offset = 0;

	for( int i = 0; i < strlen( SMSBuffer ); i++ )
	{
		if( SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
		{
			offset = i;
			break;
		}
	}

	for( int i = offset, j = 0; i < strlen( SMSBuffer ); i++ )
	{
		if( !TxtFound )
		{
			if( SMSBuffer[ i ] == '\r' || SMSBuffer[ i ] == '\n' )
			{
				EOTFound = true;
				continue;
			}
		}
		if( EOTFound && SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
		{
			TxtFound = true;
			TempBuffer[ j ] = SMSBuffer[ i ];
			j++;
		}
		if( TxtFound && ( SMSBuffer[ i ] == '\r' || SMSBuffer[ i ] == '\n' ) )
			break;
	}
}

int EzSMSDriver :: decomposeGSMMsg( const char *SMSBuffer, struct EzSMSRespMsg *smsrespmsg_ptr )
{
	char TempBuffer[ SMS_BUFFER_SIZE + 1 ];
	struct EzSMSRespMsg respmsg_rec;

	trace( DEBUG_TEST, "Decomposing Message[%s]", SMSBuffer );

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, ':', 1 );

	if( !strlen( TempBuffer ) )
		return -1;

	if( strncmp( TempBuffer, "+CMT", 4 ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, '"', 2 );

	if( !strlen( TempBuffer ) )
		return -1;

	memset( respmsg_rec.MobileNo, 0, sizeof( respmsg_rec.MobileNo ) );
	getToken( TempBuffer, respmsg_rec.MobileNo, '"', 1 );

	if( !strlen( respmsg_rec.MobileNo ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, '"', 4 );

	if( !strlen( TempBuffer ) )
		return -1;

	memset( respmsg_rec.SMSDate, 0, sizeof( respmsg_rec.SMSDate ) );
	getToken( TempBuffer, respmsg_rec.SMSDate, ',', 1 );

	if( !strlen( respmsg_rec.SMSDate ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, ',', 4 );

	if( !strlen( TempBuffer ) )
		return -1;

	memset( respmsg_rec.SMSTime, 0, sizeof( respmsg_rec.SMSTime ) );
	getToken( TempBuffer, respmsg_rec.SMSTime, '+', 1 );

	if( !strlen( respmsg_rec.SMSTime ) )
		return -1;

	return 1;

}

int EzSMSDriver :: decomposeAsyncGSMMsg( const char *SMSBuffer, struct EzSMSRespMsg *smsrespmsg_ptr )
{
	char TempBuffer[ SMS_BUFFER_SIZE + 1 ];

	trace( DEBUG_TEST, "Decomposing Message[%s]", SMSBuffer );

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, ':', 1 );

	if( !strlen( TempBuffer ) )
		return -1;

	if( strncmp( TempBuffer + strlen( TempBuffer ) - 4, "+CMT", 4 ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, '"', 2 );

	if( !strlen( TempBuffer ) )
		return -1;

	memset( smsrespmsg_ptr->MobileNo, 0, sizeof( smsrespmsg_ptr->MobileNo ) );
	getToken( TempBuffer, smsrespmsg_ptr->MobileNo, '"', 1 );

	if( !strlen( smsrespmsg_ptr->MobileNo ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, '"', 4 );

	if( !strlen( TempBuffer ) )
		return -1;

	memset( smsrespmsg_ptr->SMSDate, 0, sizeof( smsrespmsg_ptr->SMSDate ) );
	getToken( TempBuffer, smsrespmsg_ptr->SMSDate, ',', 1 );

	if( !strlen( smsrespmsg_ptr->SMSDate ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getToken( SMSBuffer, TempBuffer, ',', 4 );

	if( !strlen( TempBuffer ) )
		return -1;

	trace( DEBUG_TEST, "TempBuffer4[%s]", TempBuffer );

	memset( smsrespmsg_ptr->SMSTime, 0, sizeof( smsrespmsg_ptr->SMSTime ) );
	getToken( TempBuffer, smsrespmsg_ptr->SMSTime, '+', 1 );

	if( !strlen( smsrespmsg_ptr->SMSTime ) )
		return -1;

	memset( TempBuffer, 0, sizeof( TempBuffer ) );
	getSMSMessage( SMSBuffer, TempBuffer );

	trace( DEBUG_TEST, "SMSMessage[%s]", TempBuffer );

	memset( smsrespmsg_ptr->ApplicationCode, 0, sizeof( smsrespmsg_ptr->ApplicationCode ) );
	if( getApplicationCode( TempBuffer, smsrespmsg_ptr->ApplicationCode ) < 0 )
	{
		memset( smsrespmsg_ptr->ApplicationChannel, 0, sizeof( smsrespmsg_ptr->ApplicationChannel ) );
		strcpy( smsrespmsg_ptr->ApplicationChannel, getDefaultSMSChannel() );
		memset( smsrespmsg_ptr->MsgBuffer, 0, sizeof( smsrespmsg_ptr->MsgBuffer ) );
		strcpy( smsrespmsg_ptr->MsgBuffer, TempBuffer );
	}
	else
	{
		trace( DEBUG_NORMAL, "Got ApplicationCode[%s]", smsrespmsg_ptr->ApplicationCode );
		memset( smsrespmsg_ptr->ApplicationChannel, 0, sizeof( smsrespmsg_ptr->ApplicationChannel ) );
		if( getApplicationChannel( smsrespmsg_ptr->ApplicationCode, smsrespmsg_ptr->ApplicationChannel ) < 0 )
		{
			trace( DEBUG_NORMAL, "Error in Getting Application Channel for ApplicationCode[%s]", smsrespmsg_ptr->ApplicationCode );
			memset( smsrespmsg_ptr->ApplicationChannel, 0, sizeof( smsrespmsg_ptr->ApplicationChannel ) );
			strcpy( smsrespmsg_ptr->ApplicationChannel, getDefaultSMSChannel() );
			memset( smsrespmsg_ptr->MsgBuffer, 0, sizeof( smsrespmsg_ptr->MsgBuffer ) );
			strcpy( smsrespmsg_ptr->MsgBuffer, TempBuffer );
		}
		else
		{
			memset( smsrespmsg_ptr->MsgBuffer, 0, sizeof( smsrespmsg_ptr->MsgBuffer ) );
			strncpy( smsrespmsg_ptr->MsgBuffer, TempBuffer + strlen( smsrespmsg_ptr->ApplicationCode ) + 2 , strlen( TempBuffer ) - strlen( smsrespmsg_ptr->ApplicationCode ) + 2 );
		}
	}
	return 1;
}

int EzSMSDriver :: composeApplicationMsg( struct EzSMSRespMsg *smsrespmsg_ptr, char *SMSBuffer )
{
	trace( DEBUG_TEST, "Composing Application Message....." );

	//MobileNo
	strcpy( SMSBuffer, smsrespmsg_ptr->MobileNo );
	strcat( SMSBuffer, "\x1c" );

	//Message -----0->Acknowledgement 1->Application Message
	strcat( SMSBuffer, "1" );
	strcat( SMSBuffer, "\x1c" );

	//Message
	strcat( SMSBuffer, smsrespmsg_ptr->MsgBuffer );
	strcat( SMSBuffer, "\x1c" );

	//Date
	strcat( SMSBuffer, smsrespmsg_ptr->SMSDate );
	strcat( SMSBuffer, "\x1c" );

	//Time
	strcat( SMSBuffer, smsrespmsg_ptr->SMSTime );
	strcat( SMSBuffer, "\x1c" );

	trace( "Composed ApplicationMsg = [%s]", SMSBuffer );

	return ( strlen( SMSBuffer ) );
}

int EzSMSDriver :: writeGSMSerialPort( int GSMConnectionId, const char *SMSBuffer, int MsgLen )
{
	int retval;


	retval = write( GSMConnectionId, SMSBuffer, MsgLen );
	if( retval <= 0 )
	{
		trace( "Error in Writing Message to Serial PortId[%d]...SysErr[%s] ErrNo[%d]", GSMConnectionId, strerror( errno ), errno );
		return -1;
	}
	else
	{
		hex_dump( ( unsigned char *) SMSBuffer, MsgLen );
		trace( "[%d] Bytes written to Serial PortId[%d]", retval, GSMConnectionId );
		return retval;
	}
}

int EzSMSDriver :: probeGSMConnection( struct EzGSMInfoTable gsminfo_rec, int GSMConnectionId )
{
	char SMSBuffer[ SMS_BUFFER_SIZE + 1 ], RespBuffer[ SMS_BUFFER_SIZE + 1 ];
	int retval = -1, MsgLen;

	trace( DEBUG_TEST, "Probing GSM Connection for GSMPort[%s].....", gsminfo_rec.GSMPort );

	memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
	MsgLen = composeSignOn( SMSBuffer );

	for( int i = 0; i < gsminfo_rec.ConnectionProbeCount; i++ )
	{
		retval = writeGSMSerialPort( GSMConnectionId, SMSBuffer, MsgLen );
		if( retval < 0 )
		{
			trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		retval = readAsyncGSMSerialPort( GSMConnectionId, gsminfo_rec.InitCmdTimeOut, RespBuffer );

		if( retval == -1 )
			break;
		if( retval == -2 )
			continue;

		trace( DEBUG_TEST, "Checking Bad Response for SMSBuffer[%s] RespBuffer[%s]\n", SMSBuffer, RespBuffer );

		if( isGoodResponse( SMSBuffer, RespBuffer) )
		{
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzSMSDriver :: readGSMSerialPort( int GSMConnectionId, char *SMSBuffer )
{
	char SerialCh[ 10 ];
	bool found = false;
	int offset = 0, retval;
	//trace( "Waiting to Read Message from SerialPortId[%d]", GSMConnectionId );
	memset( SerialCh, 0, sizeof( SerialCh ) );
	while( 1 )
	{
		retval = read( GSMConnectionId, SerialCh, 1 );
		if( retval > 0 )
		{
			if( ( SerialCh[ 0 ] == '\r' ||  SerialCh[ 0 ] == '\n' ) && ( !found ) )
				found = true;
			else if ( ( SerialCh[ 0 ] == '\r' ||  SerialCh[ 0 ] == '\n' ) && ( found ) )
				break;
			else
			{
				SMSBuffer[ offset ] = SerialCh[ 0 ];
				offset++;
			}
		}
		hex_dump( DEBUG_NORMAL, ( unsigned char * ) SerialCh, 1 );
	}
	hex_dump( DEBUG_NORMAL, ( unsigned char * ) SMSBuffer, offset );
	return offset;
}

int EzSMSDriver :: readAsyncGSMSerialPortMsg( struct EzGSMInfoTable gsminfo_rec, int GSMConnectionId, char *SMSBuffer )
{
	char SerialCh[ 10 ], difftimestr[ 20 ];
	bool found = false, DataFound = false;
	int offset = 0, retval;
	struct EzSMSInfo smsinfo;
	time_t curr_time, old_time;

	old_time = time( NULL );

	memset( SerialCh, 0, sizeof( SerialCh ) );
	while( 1 )
	{
		retval = read( GSMConnectionId, SerialCh, 1 );
		if( retval < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from GSMPort[%s] ConnectionId[%d]...SysErr[%s] ErrNo[%d]", gsminfo_rec.GSMPort, GSMConnectionId, strerror( errno ), errno  );
			break;
		}

		if( !retval )
		{
			if( DataFound )
			{
				DataFound = false;
				break;
			}
			else
			{
				curr_time = time( NULL );
				memset( difftimestr, 0, sizeof( difftimestr ) );
				sprintf( difftimestr, "%f", difftime( curr_time, old_time ) );
				if( atoi( difftimestr ) > gsminfo_rec.ConnectionProbeTime )
				{
					if( probeGSMConnection( gsminfo_rec, GSMConnectionId) < 0 )
					{
						trace( DEBUG_TEST, "Connection Probing Failed for GSMPort[%s]", gsminfo_rec.GSMPort );
						retval = -2;
						break;
					}
					old_time = time( NULL );
				}

				//trace( DEBUG_TEST, "No Data Found in Serial Port...Check for Message in SMInfoQueue for GSMPort" );

				while( 1 )
				{
					memset( &smsinfo, 0, sizeof( struct EzSMSInfo ) );
					if( popSMSInfoQueue( gsminfo_rec.GSMPort, &smsinfo ) < 0 )
					{
						//trace( DEBUG_TEST, "No Data Found in SMSInfoQueue for GSMPort[%s]", GSMPort );
						break;
					}
					retval = sendSMS( smsinfo.SMSBuffer, gsminfo_rec.GSMPort, smsinfo.MobileNo );
					if( retval < 0 )
						break;
				}
				if( retval < 0 )
					break;
			}
		}
		else if( retval > 0 )
		{
			DataFound = true;
			SMSBuffer[ offset ] = SerialCh[ 0 ];
			offset++;
		}
	}

	if( retval < 0 )
		return retval;

	hex_dump( DEBUG_NORMAL, ( unsigned char * ) SMSBuffer, offset );

	return offset;
}

int EzSMSDriver :: readAsyncGSMSerialPort( int GSMConnectionId, int ResponseTimeOut, char *SMSBuffer )
{
	char SerialCh[ 10 ], difftimestr[ 20 ];
	bool found = false, DataFound = false;
	int offset = 0, retval, TReadTimeOut;
	time_t curr_time, old_time;

	old_time = time( NULL );

	memset( SerialCh, 0, sizeof( SerialCh ) );
	while( 1 )
	{
		retval = read( GSMConnectionId, SerialCh, 1 );
		if( retval < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading Message from ConnectionId[%d]...SysErr[%s] ErrNo[%d]", GSMConnectionId, strerror( errno ), errno  );
			retval = -1;
			break;
		}
		if( !retval )
		{
			if( DataFound )
			{
				DataFound = false;
				break;
			}
			else
			{
				curr_time = time( NULL );
				memset( difftimestr, 0, sizeof( difftimestr ) );
				sprintf( difftimestr, "%f", difftime( curr_time, old_time ) );
				if( atoi( difftimestr ) > ResponseTimeOut )
				{
					retval = -2;
					break;
				}
			}
		}
		else if( retval > 0 )
		{
			DataFound = true;
			SMSBuffer[ offset ] = SerialCh[ 0 ];
			offset++;
		}
	}
	if( retval < 0 )
		return retval;
	hex_dump( DEBUG_NORMAL, ( unsigned char * ) SMSBuffer, offset );
	return offset;
}

int EzSMSDriver :: addGSMPort( const char *GSMPort )
{
	struct EzGSMInfoTable gsminfo_rec;
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE +1 ], ParamStr[ 200 ];
	int CurrGSMCount;

	trace( DEBUG_TEST, "adding GSM Port[%s]", GSMPort );

	if( searchGSMInfo( GSMPort ) >= 0 )
	{
		trace( "Cannot Add....GSMPort[%s]....already added", GSMPort );
		return -1;
	}

	CurrGSMCount = getCurrGSMCount();
	if( CurrGSMCount >= getMaxGSM() )
	{
		trace( "Cannot Add....GSMPort[%s]....CurrentGSMCount[%d] has Reached MaxGSM[%d]", GSMPort, CurrGSMCount, getMaxGSM() );
		return -1;
	}

	memset( &gsminfo_rec, 0, sizeof( struct EzGSMInfoTable ) );
	strcpy( gsminfo_rec.GSMPort, GSMPort );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Protocol" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgval, "TCPIP" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_TCPIP;
	else if( !strcasecmp( cfgval, "SERIAL" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_SERIAL;
	else
	{
		trace( "Invalid Protocol Value[%s] from file[%s]....Protocol should be Serial/Tcpip....", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Address" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	strcpy( gsminfo_rec.GSMAddress, cfgval );

	if( gsminfo_rec.GSMProtocol == GSM_PROTOCOL_TCPIP )
	{
		memset( ParamStr, 0, sizeof( ParamStr ) );
		sprintf( ParamStr, "%s#%s", GSMPort, "PortNo" );

		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
			cfgutil.cfg_close();
			return -1;
		}
		gsminfo_rec.GSMPortNo = atoi( cfgval );
	}
	else
		gsminfo_rec.GSMPortNo = 0;

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MCN" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	strcpy( gsminfo_rec.MsgCenterNo, cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "GSMTYPE" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.GSMType == GSM_TYPE_SERIAL;
	else if( !strcasecmp( cfgval, "USB" ) )
		gsminfo_rec.GSMType == GSM_TYPE_USB;
	else
		gsminfo_rec.GSMType == GSM_TYPE_SERIAL;

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "NRetries" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.NRetries = 5;
	}
	else
		gsminfo_rec.NRetries = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "RetryInterval" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.RetryInterval = 5;
	}
	else
		gsminfo_rec.RetryInterval = atoi( cfgval );


	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MsgSendInterval" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.MsgSendInterval = 5;
	}
	else
		gsminfo_rec.MsgSendInterval = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "AckTimeOut" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.AckTimeOut = 5;
	}
	else
		gsminfo_rec.AckTimeOut = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "InitCmdTimeOut" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.InitCmdTimeOut = 5;
	}
	else
		gsminfo_rec.InitCmdTimeOut = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ConnectionProbeTime" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.ConnectionProbeTime = 15;
	}
	else
		gsminfo_rec.ConnectionProbeTime = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ConnectionProbeCount" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.ConnectionProbeCount = 3;
	}
	else
		gsminfo_rec.ConnectionProbeCount = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MultiSendFlag" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.MultiSendFlag = true;
	}
	else
	{
		if( !strcasecmp( cfgval, "Yes" ) )
			gsminfo_rec.MultiSendFlag = true;
		else
			gsminfo_rec.MultiSendFlag = false;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "NMobileAck" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.NMobileAck = 1;
	}
	else
	{
		gsminfo_rec.NMobileAck = atoi( cfgval );
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "NMsgAck" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.NMsgAck = 1;
	}
	else
	{
		gsminfo_rec.NMsgAck = atoi( cfgval );
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "GSMFormatReq" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.GSMFormatReq = false;
	}
	else if( !strcasecmp( cfgval, "Yes" ) )
		gsminfo_rec.GSMFormatReq = true;
	else
		gsminfo_rec.GSMFormatReq = false;

	if( gsminfo_rec.GSMFormatReq )
	{
		memset( ParamStr, 0, sizeof( ParamStr ) );
		sprintf( ParamStr, "%s#%s", GSMPort, "GSMFormatAckTimeOut" );

		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
			gsminfo_rec.GSMFormatAckTimeOut = 5;
		}
		else
			gsminfo_rec.GSMFormatAckTimeOut = atoi( cfgval );
	}

	memset( &gsminfo_rec.srlinfo, 0, sizeof( struct EzSerialPortInfo ) );
	strcpy( gsminfo_rec.srlinfo.SerialPort, gsminfo_rec.GSMAddress );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ReadMode" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.ReadMode = SERIAL_MODE_BLOCKING;
	else if( !strcasecmp( cfgval, "NONBLOCKING" ) )
		gsminfo_rec.srlinfo.ReadMode = SERIAL_MODE_NONBLOCKING;
	else
		gsminfo_rec.srlinfo.ReadMode = SERIAL_MODE_BLOCKING;

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MinChar" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.MinChar = 1;
	else
		gsminfo_rec.srlinfo.MinChar = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ReadTimeOut" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.ReadTimeOut = 0;
	else
		gsminfo_rec.srlinfo.ReadTimeOut = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "BaudRate" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	gsminfo_rec.srlinfo.BaudRate = atol( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "DataBits" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.DataBits = 8;
	else
		gsminfo_rec.srlinfo.DataBits = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "StopBits" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.StopBits = 1;
	else
		gsminfo_rec.srlinfo.StopBits = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Parity" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_NONE;
	else if( !strcasecmp( cfgval, "ODDPARITY" ) )
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_ODD;
	else if( !strcasecmp( cfgval, "EVENPARITY" ) )
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_EVEN;
	else
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_NONE;

	cfgutil.cfg_close();

	pthread_t GSMThread;
	pthread_attr_t GSMThreadAttr;
	pthread_attr_init( &GSMThreadAttr );
	pthread_attr_setdetachstate( &GSMThreadAttr, 1 );
	if( pthread_create( &GSMThread, &GSMThreadAttr, serviceGSMThread, ( void * ) this ) != 0 )
	{
		trace( "Error in Creating GSM Thread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	gsminfo_rec.GSMThreadId = GSMThread;

	if( addGSMInfo( gsminfo_rec ) < 0 )
	{
		trace( "Error in adding GSMPort[%s] in GSMInfo Table", gsminfo_rec.GSMPort );
		pthread_cancel( GSMThread );
		return -1;
	}

	if( insertSMSInfoQueue( gsminfo_rec.GSMPort ) < 0 )
	{
		trace( "Error in adding GSMPort[%s] in SMSInfoQueue Table", gsminfo_rec.GSMPort );
		pthread_cancel( GSMThread );
		return -1;
	}
	return 1;
}

void EzSMSDriver :: getGSMRespCmd( const char *SMSBuffer, char *GSMRespCmd )
{
	bool EodFound = false, DataFound = false;
	for( int i = 0, j = 0; i < strlen( SMSBuffer ); i++ )
	{
		if( !DataFound )
		{
			if( SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
				EodFound = true;
		}
		if( EodFound )
		{
			if( SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
			{
				DataFound = true;
				GSMRespCmd[ j ] = SMSBuffer[ i ];
				j++;
			}
			else if( DataFound )
				break;
		}
	}
}

void EzSMSDriver :: getGSMResp( const char *SMSBuffer, char *RespBuffer )
{
	bool EodFound = false, DataFound = false;
	int offset = 0;
	for( int i = 0, j = 0; i < strlen( SMSBuffer ); i++ )
	{
		if( !DataFound )
		{
			if( SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
				EodFound = true;
		}
		if( EodFound )
		{
			if( SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
			{
				DataFound = true;
				j++;
			}
			else if( DataFound )
			{
				offset = i;
				break;
			}
		}
	}
	EodFound = false, DataFound = false;
	for( int i = offset, j = 0; i < strlen( SMSBuffer ); i++ )
	{
		if( !DataFound )
		{
			if( SMSBuffer[ i ] == '\r' || SMSBuffer[ i ] == '\n' )
			{
				EodFound = true;
				continue;
			}
		}
		if( EodFound )
		{
			if( SMSBuffer[ i ] != '\r' && SMSBuffer[ i ] != '\n' )
			{
				DataFound = true;
				RespBuffer[ j ] = SMSBuffer[ i ];
				j++;
			}
			else if( DataFound )
			{
				offset = i;
				break;
			}
		}
	}
}

int EzSMSDriver :: stopGSMPort( const char *GSMPort )
{
	struct EzGSMInfoTable gsminfo_rec;

	trace( DEBUG_TEST, "Stopping GSM Port[%s]", GSMPort );

	if( searchGSMInfo( GSMPort, &gsminfo_rec ) < 0 )
	{
		trace( "Error in Searching GSMPort[%s] in GSMInfo Table..", GSMPort );
		return -1;
	}

	pthread_cancel( gsminfo_rec.GSMThreadId );

	if( updateGSMStatus( GSMPort, GSM_STATUS_STOPPED ) < 0 )
	{
		trace( "Error in Updating GSM Status for GSMPort[%s] in GSMInfo Table..", GSMPort );
		return -1;
	}
	return 1;
}

int EzSMSDriver :: removeGSMPort( const char *GSMPort )
{
	struct EzGSMInfoTable gsminfo_rec;

	trace( DEBUG_TEST, "Removing GSM Port[%s]", GSMPort );

	if( removeGSMInfo( GSMPort, &gsminfo_rec ) < 0 )
	{
		trace( "Error in Removing GSMPort[%s] in GSMInfo Table..", GSMPort );
		return -1;
	}

	if( deleteSMSInfoQueue( GSMPort ) < 0 )
	{
		trace( "Error in Removing GSMPort[%s] from SMSInfoQueue..", GSMPort );
		return -1;
	}

	pthread_cancel( gsminfo_rec.GSMThreadId );

	return 1;
}

int EzSMSDriver :: startGSMPort( const char *GSMPort )
{
	struct EzGSMInfoTable gsminfo_rec;
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE +1 ], ParamStr[ 200 ];

	trace( DEBUG_TEST, "Starting GSM Port[%s]", GSMPort );

	if( searchGSMInfo( GSMPort, &gsminfo_rec ) < 0 )
	{
		trace( "Error in Searching GSMPort[%s] in GSMInfo Table..", GSMPort );
		return -1;
	}

	if( gsminfo_rec.GSMStatus != GSM_STATUS_STOPPED )
	{
		trace( "Error in Starting GSMPort[%s]...First Stop the GSMPort before Starting..", GSMPort );
		return -1;
	}

	memset( &gsminfo_rec, 0, sizeof( struct EzGSMInfoTable ) );
	strcpy( gsminfo_rec.GSMPort, GSMPort );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Protocol" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgval, "TCPIP" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_TCPIP;
	else if( !strcasecmp( cfgval, "SERIAL" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_SERIAL;
	else
	{
		trace( "Invalid Protocol Value[%s] from file[%s]....Protocol should be Serial/Tcpip....", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Address" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	strcpy( gsminfo_rec.GSMAddress, cfgval );

	if( gsminfo_rec.GSMProtocol == GSM_PROTOCOL_TCPIP )
	{
		memset( ParamStr, 0, sizeof( ParamStr ) );
		sprintf( ParamStr, "%s#%s", GSMPort, "PortNo" );

		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
			cfgutil.cfg_close();
			return -1;
		}
		gsminfo_rec.GSMPortNo = atoi( cfgval );
	}
	else
		gsminfo_rec.GSMPortNo = 0;

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MCN" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	strcpy( gsminfo_rec.MsgCenterNo, cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "GSMTYPE" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.GSMType == GSM_TYPE_SERIAL;
	else if( !strcasecmp( cfgval, "USB" ) )
		gsminfo_rec.GSMType == GSM_TYPE_USB;
	else
		gsminfo_rec.GSMType == GSM_TYPE_SERIAL;

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "NRetries" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.NRetries = 5;
	}
	else
		gsminfo_rec.NRetries = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "RetryInterval" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.RetryInterval = 5;
	}
	else
		gsminfo_rec.RetryInterval = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MsgSendInterval" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.MsgSendInterval = 5;
	}
	else
		gsminfo_rec.MsgSendInterval = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "AckTimeOut" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.AckTimeOut = 5;
	}
	else
		gsminfo_rec.AckTimeOut = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "InitCmdTimeOut" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.InitCmdTimeOut = 5;
	}
	else
		gsminfo_rec.InitCmdTimeOut = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ConnectionProbeTime" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.ConnectionProbeTime = 15;
	}
	else
		gsminfo_rec.ConnectionProbeTime = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ConnectionProbeCount" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.ConnectionProbeCount = 3;
	}
	else
		gsminfo_rec.ConnectionProbeCount = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MultiSendFlag" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.MultiSendFlag = true;
	}
	else
	{
		if( !strcasecmp( cfgval, "Yes" ) )
			gsminfo_rec.MultiSendFlag = true;
		else
			gsminfo_rec.MultiSendFlag = false;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "NMobileAck" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.NMobileAck = 1;
	}
	else
	{
		gsminfo_rec.NMobileAck = atoi( cfgval );
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "NMsgAck" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.NMsgAck = 1;
	}
	else
	{
		gsminfo_rec.NMsgAck = atoi( cfgval );
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "GSMFormatReq" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		gsminfo_rec.GSMFormatReq = false;
	}
	else if( !strcasecmp( cfgval, "Yes" ) )
		gsminfo_rec.GSMFormatReq = true;
	else
		gsminfo_rec.GSMFormatReq = false;

	if( gsminfo_rec.GSMFormatReq )
	{
		memset( ParamStr, 0, sizeof( ParamStr ) );
		sprintf( ParamStr, "%s#%s", GSMPort, "GSMFormatAckTimeOut" );

		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
			gsminfo_rec.GSMFormatAckTimeOut = 5;
		}
		else
			gsminfo_rec.GSMFormatAckTimeOut = atoi( cfgval );
	}

	memset( &gsminfo_rec.srlinfo, 0, sizeof( struct EzSerialPortInfo ) );
	strcpy( gsminfo_rec.srlinfo.SerialPort, gsminfo_rec.GSMAddress );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ReadMode" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.ReadMode = SERIAL_MODE_BLOCKING;
	else if( !strcasecmp( cfgval, "NONBLOCKING" ) )
		gsminfo_rec.srlinfo.ReadMode = SERIAL_MODE_NONBLOCKING;
	else
		gsminfo_rec.srlinfo.ReadMode = SERIAL_MODE_BLOCKING;

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "MinChar" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.MinChar = 1;
	else
		gsminfo_rec.srlinfo.MinChar = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "ReadTimeOut" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.ReadTimeOut = 0;
	else
		gsminfo_rec.srlinfo.ReadTimeOut = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "BaudRate" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	gsminfo_rec.srlinfo.BaudRate = atol( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "DataBits" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.DataBits = 8;
	else
		gsminfo_rec.srlinfo.DataBits = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "StopBits" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.StopBits = 1;
	else
		gsminfo_rec.srlinfo.StopBits = atoi( cfgval );

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Parity" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_NONE;
	else if( !strcasecmp( cfgval, "ODDPARITY" ) )
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_ODD;
	else if( !strcasecmp( cfgval, "EVENPARITY" ) )
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_EVEN;
	else
		gsminfo_rec.srlinfo.Parity = SERIAL_PARITY_NONE;

	cfgutil.cfg_close();

	pthread_t GSMThread;
	pthread_attr_t GSMThreadAttr;
	pthread_attr_init( &GSMThreadAttr );
	pthread_attr_setdetachstate( &GSMThreadAttr, 1 );

	if( pthread_create( &GSMThread, &GSMThreadAttr, serviceGSMThread, ( void * ) this ) != 0 )
	{
		trace( "Error in Creating GSM Thread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	gsminfo_rec.GSMThreadId = GSMThread;
	if( updateGSMInfo( gsminfo_rec ) < 0 )
	{
		trace( "Error in Updating GSMPort[%s] in GSMInfo Table", gsminfo_rec.GSMPort );
		pthread_cancel( GSMThread );
		return -1;
	}
	return 1;
}

int EzSMSDriver :: initGSMPorts()
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE +1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	int GSMCount;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	GSMCount = cfgutil.cfg_group_count( "DRIVER" );

	if( GSMCount < 0 )
	{
		trace( "Error in Searching Group GSM in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( GSMCount > getMaxGSM() )
	{
		trace( "No.of GSMPort[%d] in File[%s] > MaxGSM[%d]", GSMCount, cfgpath, getMaxGSM() );
		cfgutil.cfg_close();
		return -1;
	}

	for( int i = 0; i < GSMCount; i++ )
	{
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_get_param( "DRIVER", cfgval, i + 1 ) < 0 )
		{
			trace( "Error in Searching Group DRIVER in File[%s]", cfgpath );
			continue;
		}
		addGSMPort( cfgval );
	}
	cfgutil.cfg_close();
	return 1;
}

int EzSMSDriver :: sendSMS( const char *SMSMessage, const char *GSMPort, const char *MobileNo )
{
	char SMSBuffer[ SMS_BUFFER_SIZE + 1 ], LocalBuffer[ SMS_BUFFER_SIZE + 1 ];
	char RespBuffer[ SMS_BUFFER_SIZE + 1 ], GSMRespCmd[ SMS_BUFFER_SIZE + 1 ];
	struct EzGSMInfoTable gsminfo_rec;
	int retval, MsgLen;
	struct timeval now;
	struct timespec timeout;
	pthread_cond_t GSMThreadCond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t GSMThreadMutex = PTHREAD_MUTEX_INITIALIZER;
	bool SendFlag = false, EOTFound = false, TxtFound = false;

	memset( &gsminfo_rec, 0, sizeof( struct EzGSMInfoTable ) );
	if( searchGSMInfo( GSMPort, &gsminfo_rec ) < 0 )
	{
		trace( "Error in Searching GSMPort[%s] in GSMInfoTable", GSMPort );
		return 1;
	}

	if( gsminfo_rec.GSMConnectionStatus != GSM_STATUS_CONNECTED )
	{
		trace( DEBUG_ERROR, "GSMPort[%s] is Not Connected", GSMPort );
		return 1;
	}

	if( gsminfo_rec.GSMStatus != GSM_STATUS_RUNNING )
	{
		trace( DEBUG_ERROR, "GSMPort[%s] is Not Running", GSMPort );
		return 1;
	}

	trace( DEBUG_TEST, "Sending SMS[%s] to MobileNo[%s] through GSM Port[%s] ConnectionId[%d]", SMSMessage, MobileNo, GSMPort, gsminfo_rec.GSMConnectionId );

	if( gsminfo_rec.GSMFormatReq )
	{
		while( 1 )
		{
			// SMS Format
			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			MsgLen = composeGSMFormat( SMSBuffer );
			retval = writeGSMSerialPort( gsminfo_rec.GSMConnectionId, SMSBuffer, MsgLen );
			if( retval < 0 )
			{
				trace( "Error in Writing Message to Serial Port...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			retval = readAsyncGSMSerialPort( gsminfo_rec.GSMConnectionId, gsminfo_rec.GSMFormatAckTimeOut, RespBuffer );

			if( retval == -2 )
			{
				if( probeGSMConnection( gsminfo_rec, gsminfo_rec.GSMConnectionId ) < 0 )
				{
					retval = -2;
					break;
				}
				else
					continue;
			}

			if( retval == -1 )
				break;

			if( isBadResponse( SMSBuffer, RespBuffer ) )
				continue;

			break;
		}
		if( retval < 0 )
			return retval;
	}

	for( int i = 0; i <  gsminfo_rec.NRetries; i++ )
	{
		if( gsminfo_rec.MultiSendFlag )
		{
			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			sprintf( SMSBuffer, "AT+CMGS=\"%s\"\r\n", MobileNo );
			retval = write( gsminfo_rec.GSMConnectionId, SMSBuffer, strlen( SMSBuffer ) );
			if( retval < 0 )
			{
				trace( DEBUG_TEST, "Error in Writing Message to GSM Port[%s]..SysErr[%s] ErrNo[%d]", GSMPort, strerror( errno ), errno );
				break;
			}
			trace( DEBUG_TEST, "Written [%d] Bytes Message to ConnectionId[%d]", retval, gsminfo_rec.GSMConnectionId );

			for( int i = 0; i < gsminfo_rec.NMobileAck; i++ )
			{
				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				retval = readAsyncGSMSerialPort( gsminfo_rec.GSMConnectionId, gsminfo_rec.AckTimeOut, SMSBuffer );
				if( retval == -1 )
					break;
				if( retval == -2 )
				{
					if( probeGSMConnection( gsminfo_rec, gsminfo_rec.GSMConnectionId ) < 0 )
					{
						retval = -3;
						break;
					}
				}
			}
			if( retval == -1 || retval == -3 )
				break;

			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			sprintf( SMSBuffer, "%s%c", SMSMessage, 0x1a );
			retval = write( gsminfo_rec.GSMConnectionId, SMSBuffer, strlen( SMSBuffer ) );
			if( retval < 0 )
			{
				trace( DEBUG_TEST, "Error in Writing Message to GSM Port[%s]..SysErr[%s] ErrNo[%d]", GSMPort, strerror( errno ), errno );
				break;
			}
			trace( DEBUG_TEST, "Written [%d] Bytes Message to ConnectionId[%d]", retval, gsminfo_rec.GSMConnectionId );

			for( int i = 0; i < gsminfo_rec.NMsgAck; i++ )
			{
				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				retval = readAsyncGSMSerialPort( gsminfo_rec.GSMConnectionId, gsminfo_rec.AckTimeOut, SMSBuffer );
				if( retval == -1 )
					break;
				if( retval == -2 )
				{
					if( probeGSMConnection( gsminfo_rec, gsminfo_rec.GSMConnectionId ) < 0 )
					{
						retval = -3;
						break;
					}
				}

			}
			if( retval == -1 || retval == -3 )
				break;
		}
		else
		{
			memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
			sprintf( SMSBuffer, "AT+CMGS=\"%s\"\r\n%s%c", MobileNo, SMSMessage, 0x1a );
			retval = write( gsminfo_rec.GSMConnectionId, SMSBuffer, strlen( SMSBuffer ) );
			if( retval < 0 )
			{
				trace( DEBUG_TEST, "Error in Writing Message to GSM Port[%s]..SysErr[%s] ErrNo[%d]", GSMPort, strerror( errno ), errno );
				break;
			}
			trace( DEBUG_TEST, "Written [%d] Bytes Message to ConnectionId[%d]", retval, gsminfo_rec.GSMConnectionId );

			for( int i = 0; i < gsminfo_rec.NMsgAck; i++ )
			{
				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				retval = readAsyncGSMSerialPort( gsminfo_rec.GSMConnectionId, gsminfo_rec.AckTimeOut, SMSBuffer );
				if( retval == -1 )
					break;
				if( retval == -2 )
				{
					if( probeGSMConnection( gsminfo_rec, gsminfo_rec.GSMConnectionId ) < 0 )
					{
						retval = -3;
						break;
					}
				}
			}
			if( retval == -1 || retval == -3 )
				break;
		}
		if( retval == -1 )
			break;

		if( retval == -2 )
		{
			trace( DEBUG_NORMAL, "Message[%s] to MobileNo[%s] through GSMPort[%s] got timedout....", SMSMessage, MobileNo, GSMPort );
			continue;
		}

		if( !gsminfo_rec.NMsgAck )
			break;

		if( retval >= 0 )
		{
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + gsminfo_rec.RetryInterval;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &GSMThreadMutex );
			pthread_cond_timedwait( &GSMThreadCond, &GSMThreadMutex, &timeout );
			pthread_mutex_unlock( &GSMThreadMutex );

			EOTFound = false;
			TxtFound = false;

			memset( LocalBuffer, 0, sizeof( LocalBuffer ) );
			for( int i = 0, j = 0; i < strlen( SMSBuffer ); i++ )
			{
				if( !EOTFound )
				{
					if( SMSBuffer[ i ] == '\n' || SMSBuffer[ i ] == '\r' )
					{
						EOTFound = true;
						continue;
					}
				}
				if( EOTFound )
				{
					if( ( SMSBuffer[ i ] == '\n' || SMSBuffer[ i ] == '\r' ) && TxtFound )
						break;

					if( SMSBuffer[ i ] != '\n' && SMSBuffer[ i ] != '\r' )
					{
						TxtFound = true;
						LocalBuffer[ j ] = SMSBuffer[ i ];
						j++;
					}
				}
			}
			if( strncmp( LocalBuffer, "ERROR", 5 ) )
			{
				SendFlag = true;
				break;
			}
		}

		if( retval < 0 )
			return retval;

		if( SendFlag )
			trace( DEBUG_NORMAL, "Message[%s] to MobileNo[%s] sent Successfully through GSMPort[%s]", SMSMessage, MobileNo, GSMPort );
		else
			trace( DEBUG_NORMAL, "Failed sending Message[%s] to MobileNo[%s] through GSMPort[%s]", SMSMessage, MobileNo, GSMPort );

	}
	gettimeofday( &now, NULL );
	timeout.tv_sec = now.tv_sec + gsminfo_rec.MsgSendInterval;
	timeout.tv_nsec = now.tv_usec * 1000;
	pthread_mutex_lock( &GSMThreadMutex );
	pthread_cond_timedwait( &GSMThreadCond, &GSMThreadMutex, &timeout );
	pthread_mutex_unlock( &GSMThreadMutex );

	return 1;
}

int EzSMSDriver :: getNTokens( const char *FieldStr, char Token )
{
	int TokenCount = 0;
	for( int i = 0; i < strlen( FieldStr ); i++ )
	{
		if( FieldStr[ i ] == Token )
			TokenCount++;
	}
	return TokenCount;
}

void EzSMSDriver :: getToken( const char *FieldStr, char *TokenStr, char Token, int TokenNo )
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

void EzSMSDriver :: processApplicationRequest( const char *RequestBuffer )
{
	char MobileList[ MOBILE_LIST_SIZE + 1 ], SMSMessage[ SMS_BUFFER_SIZE + 1 ], GSMPort[ 33 ], MobileNo[ 17 ];
	int MobileCount;
	struct EzSMSInfo smsinfo;

	memset( MobileList, 0, sizeof( MobileList ) );
	getToken( RequestBuffer, MobileList, 0x1c, 1 );

	trace( DEBUG_TEST, "MobileList[%s]", MobileList );

	MobileCount = getNTokens( MobileList, 0x1d );

	if( !MobileCount )
	{
		trace( DEBUG_ERROR, "Mobile No is NULL.....Dropping Message" );
		return;
	}

	memset( SMSMessage, 0, sizeof( SMSMessage ) );
	getToken( RequestBuffer, SMSMessage, 0x1c, 2 );

	trace( DEBUG_TEST, "SMSMessage[%s]", SMSMessage );

	if( !strlen( SMSMessage ) )
	{
		trace( DEBUG_ERROR, "Application Message is NULL.....Dropping Message" );
		return;
	}

	memset( GSMPort, 0, sizeof( GSMPort ) );
	getToken( RequestBuffer, GSMPort, 0x1c, 4 );
	if( !strlen( GSMPort ) )
		strcpy( GSMPort, getDefaultGSMPort() );

	trace( DEBUG_TEST, "GSMPort[%s]", GSMPort );

	for( int i = 0; i < MobileCount; i++ )
	{
		memset( MobileNo, 0, sizeof( MobileNo ) );
		getToken( MobileList, MobileNo, 0x1d, i + 1 );
		memset( &smsinfo, 0, sizeof( struct EzSMSInfo ) );
		strcpy( smsinfo.MobileNo, MobileNo );
		strcpy( smsinfo.SMSBuffer, SMSMessage );
		if( pushSMSInfoQueue( GSMPort, &smsinfo ) < 0 )
			trace( "Error in Pushing MobileNo[%s] Message[%s] in SMSInfoQueue for GSMPort[%s]", smsinfo.MobileNo, smsinfo.SMSBuffer, GSMPort );
	}
}

void EzSMSDriver :: processCommandRequest( struct EzSMSDriverMsg smsdrvrmsg )
{

	trace( DEBUG_TEST, "Command Request Received from Channel[%s]", GetLastSenderChannelName() );

	switch ( smsdrvrmsg.Command )
	{
		case ADD_GSMPORT:

			addGSMPort( smsdrvrmsg.GSMPort );
			break;

		case START_GSMPORT:

			startGSMPort( smsdrvrmsg.GSMPort );
			break;

		case STOP_GSMPORT:

			stopGSMPort( smsdrvrmsg.GSMPort );
			break;

		case REMOVE_GSMPORT:

			stopGSMPort( smsdrvrmsg.GSMPort );
			break;

		case SEND_SMS:

			sendSMS( smsdrvrmsg.MsgBuffer, smsdrvrmsg.GSMPort, smsdrvrmsg.MobileNo );
			break;

		default:
			trace( DEBUG_ERROR, "Invalid Command Received....." );
			break;
	}
}

bool EzSMSDriver :: isCmdChannel( const char *ChannelName )
{
	if( !strcmp( ChannelName, SMSCMDCHANNEL ) )
		return true;
	else
		return false;
}

void EzSMSDriver :: serviceRequest()
{
	int MsgSize;

	char RequestBuffer[ 1025 ];

	struct EzSMSDriverMsg smsdrvrmsg;
	while( 1 )
	{
		trace( "EzSMSDriver Waiting for Request.....in Qid[%d]", GetSourceChannelQid() );
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		if( ReadMessage( RequestBuffer, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from EzSMSDriver Channel...." );
			trace( "^^^^^^^^^^^EzSMSDriver Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			exit( 0 );
		}

		trace( DEBUG_NORMAL, "Message Received in %s Channel", SMSDRIVERCHANNEL );
		//hex_dump( DEBUG_TEST, ( unsigned char * ) RequestBuffer, MsgSize );

		if( isCmdChannel( GetLastSenderChannelName() ) )
		{
			memset( &smsdrvrmsg, 0, sizeof( struct EzSMSDriverMsg ) );
			memcpy( &smsdrvrmsg, RequestBuffer, sizeof( struct EzSMSDriverMsg ) );
			processCommandRequest( smsdrvrmsg );
		}
		else
			processApplicationRequest( RequestBuffer );
	}
}

int main( int argc, char **argv )
{
	EzSMSDriver smsdrvrobj;
	smsdrvrobj.initSMSDriver( argv[ 0 ] );
	smsdrvrobj.serviceRequest();
	return 1;
}






