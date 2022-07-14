#include <ezkernel/ezcommdrvr.h>

void *DropMultipleMsg( void *dropmsg )
{
	pthread_t thid;
	struct timeval now;
	struct timespec timeout;
	pthread_cond_t DropCond;
	pthread_mutex_t DropMutex;
	pthread_cond_init( &DropCond, NULL );
	pthread_mutex_init( &DropMutex, NULL );
	EzCommDrvr *commptr = ( EzCommDrvr * ) dropmsg;
	gettimeofday( &now, NULL );
	timeout.tv_sec = now.tv_sec + commptr->driverconfig.multimsginterval;
	timeout.tv_nsec = now.tv_usec * 1000;
	pthread_mutex_lock( &DropMutex );
	pthread_cond_timedwait( &DropCond, &DropMutex, &timeout );
	pthread_mutex_unlock( &DropMutex );
	pthread_mutex_lock( &MultiMsgMutex );
	thid = commptr->multimsg.ThreadId;
	pthread_mutex_unlock( &MultiMsgMutex );
	if( thid == pthread_self( ) )
	{
		commptr->trace( DEBUG_NORMAL,"Msg written to the driver After [ %d ] Interval", commptr->driverconfig.multimsginterval );
		if( commptr->WriteChannel( commptr->driverconfig.destchannel, commptr->multimsg.Buffer , commptr->multimsg.BufferSize ) < 0 )
				commptr->trace( "Error in Posting Message to Channel[%s]", commptr->driverconfig.destchannel );
	}
	pthread_mutex_lock( &MultiMsgMutex );
	strcpy( commptr->multimsg.Buffer, TCTPIP_THREAD_INIT_MSG );
	pthread_mutex_unlock( &MultiMsgMutex );
	return ( void * )1;
}

void * tcpip_read_routine( void *threadMessage )
{
	char tcpipheader[ COMM_HEADER_SIZE + 1 ];
	unsigned char tcpipmsg[ COMM_MSG_SIZE + 1 ];
	short int MsgSize;
	EzCommDrvr *commptr = ( EzCommDrvr *) threadMessage;

	//Wait for EzMsgRouter to Start for Updating the Device Connection Status to EzDeviceMgr

	struct timeval now;
	struct timespec timeout;

	int TableLookUpCount = 0;

	pthread_cond_t EventCond;
	pthread_mutex_t EventMutex;

	pthread_cond_init( &EventCond, NULL );
	pthread_mutex_init( &EventMutex, NULL );

    gettimeofday( &now, NULL );
    timeout.tv_sec = now.tv_sec + 3;
    timeout.tv_nsec = now.tv_usec * 1000;
	pthread_mutex_lock( &EventMutex );
	pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
	pthread_mutex_unlock( &EventMutex );

	commptr->trace( DEBUG_TEST, "Tcp/Ip thread for driver[%s]...started", commptr->drivername );

	if( commptr->driverconfig.apptype == TCPIP_SERVER )
		commptr->trace( DEBUG_TEST, "Driver[%s] is configured as Server", commptr->drivername );
	else
		commptr->trace( DEBUG_TEST, "Driver[%s] is configured as Client", commptr->drivername );

	while( 1 )
	{
		if( commptr->driverconfig.apptype == TCPIP_SERVER )
		{
			if( commptr->createSocket() < 0 )
			{
				commptr->trace( DEBUG_ERROR, "Error in Creating Socket for Driver[%s] ...SysErr[%s] ErrNo[%d]", commptr->drivername, strerror( errno ), errno );
				gettimeofday( &now, NULL );
				timeout.tv_sec = now.tv_sec + 3;
				timeout.tv_nsec = now.tv_usec * 1000;
				pthread_mutex_lock( &EventMutex );
				pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
				pthread_mutex_unlock( &EventMutex );
				continue;
			}
		}
		else
		{
			commptr->DriverConnectionId = commptr->createSocket();
			if( commptr->DriverConnectionId < 0 )
			{
				commptr->trace( DEBUG_ERROR, "Error in Creating Socket for Driver[%s] ...SysErr[%s] ErrNo[%d]", commptr->drivername, strerror( errno ), errno );
				gettimeofday( &now, NULL );
				timeout.tv_sec = now.tv_sec + 3;
				timeout.tv_nsec = now.tv_usec * 1000;
				pthread_mutex_lock( &EventMutex );
				pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
				pthread_mutex_unlock( &EventMutex );
				continue;
			}
		}
		break;
	}

	while( 1 )
	{
		pthread_mutex_lock( &ConnectionFlagMutex );
		commptr->ConnectionStatus = PORT_DISCONNECTED;
		pthread_mutex_unlock( &ConnectionFlagMutex );

		if( commptr->driverconfig.apptype == TCPIP_SERVER )
		{
			if( commptr->UpdatePortStatus( commptr->drivername, PORT_LISTEN ) < 0 )
				commptr->trace( DEBUG_ERROR, "Error in Updating PortStatus for Driver[%s]", commptr->drivername );
			commptr->updateDeviceConnectionStatus( commptr->drivername, 0 );
			commptr->trace( DEBUG_NORMAL, "[%s] Listening at PortNo[%d]....", commptr->drivername, commptr->driverconfig.portno );
			commptr->DriverConnectionId = commptr->waitForConnection();
			if( commptr->DriverConnectionId < 0 )
			{
				commptr->trace( DEBUG_ERROR, "Error in Accepting Connection...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				gettimeofday( &now, NULL );
				timeout.tv_sec = now.tv_sec + 3;
				timeout.tv_nsec = now.tv_usec * 1000;
				pthread_mutex_lock( &EventMutex );
				pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
				pthread_mutex_unlock( &EventMutex );
				continue;
			}
			//commptr->trace( "Accepted Connection From Client with IpAddress[%s]", commptr->getConnectionIpAddress() );
			commptr->trace( "Accepted Connection From Client with IpAddress[%s]", commptr->getConnectionIpAddress() );
			if( commptr->driverconfig.enableping )
			{
				if( strcmp( commptr->getConnectionIpAddress(), commptr->driverconfig.ipaddress ) )
				{
					commptr->trace( "Cannot Accept Connection From IpAddress[%s]...IpAddress is Configured as[%s]", commptr->getConnectionIpAddress(), commptr->driverconfig.ipaddress );
					close( commptr->DriverConnectionId );
					continue;
				}
			}
		}
		else
		{
			if( commptr->UpdatePortStatus( commptr->drivername, PORT_TRYING ) < 0 )
				commptr->trace( DEBUG_ERROR, "Error in Updating PortStatus for Driver[%s]", commptr->drivername );
			commptr->updateDeviceConnectionStatus( commptr->drivername, 0 );
			if( commptr->driverconfig.connectiontype == STATIC )
			{
				commptr->DriverConnectionId = commptr->connectServer();
				if( commptr->DriverConnectionId < 0 )
				{
					commptr->trace( DEBUG_ERROR, "Error in Connecting with IpAddress[%s] PortNo[%d]...SysErr[%s] ErrNo[%d]", commptr->driverconfig.ipaddress, commptr->driverconfig.portno, strerror( errno ), errno );
					gettimeofday( &now, NULL );
					timeout.tv_sec = now.tv_sec + 3;
					timeout.tv_nsec = now.tv_usec * 1000;
					pthread_mutex_lock( &EventMutex );
					pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
					pthread_mutex_unlock( &EventMutex );
					continue;
				}
				commptr->trace( "Connected with IpAddress[%s] and PortNo[%d] ", commptr->driverconfig.ipaddress, commptr->driverconfig.portno );
			}
		}
		if( commptr->UpdatePortStatus( commptr->drivername, PORT_CONNECTED ) < 0 )
			commptr->trace( DEBUG_ERROR, "Error in Updating PortStatus for Driver[%s]", commptr->drivername );
		commptr->updateDeviceConnectionStatus( commptr->drivername, 1 );

		pthread_mutex_lock( &ConnectionFlagMutex );
		commptr->ConnectionStatus = PORT_CONNECTED;
		pthread_mutex_unlock( &ConnectionFlagMutex );

		while( 1 )
		{
			commptr->trace( "Waiting for Message From Socket");
			memset( tcpipheader, 0, sizeof( tcpipheader ) );
			if( recv( commptr->DriverConnectionId, tcpipheader, commptr->driverconfig.headerlen, 0 ) <= 0 )
			{
				commptr->trace( DEBUG_ERROR, "Error while Reading Header From Socket ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
				break;
			}
			commptr->hex_dump( DEBUG_TEST, ( unsigned char * ) tcpipheader, commptr->driverconfig.headerlen );
			if( commptr->driverconfig.headertype == ASCII )
				MsgSize = atoi( tcpipheader );
			else if( commptr->driverconfig.headertype == HEX )
			{
				memcpy( &MsgSize, tcpipheader, commptr->driverconfig.headerlen );
				MsgSize = ntohs( MsgSize );
			}
			commptr->trace( DEBUG_NORMAL, "[%d] bytes available on socket", MsgSize );

			memset( tcpipmsg, 0, sizeof( tcpipmsg ) );
			if( recv( commptr->DriverConnectionId, tcpipmsg, MsgSize, 0 ) <= 0 )
			{
				commptr->trace( DEBUG_ERROR, "Error while Reading Message From Socket ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
				break;
			}
			if( commptr->DebugFlag )
				commptr->hex_dump( ( unsigned char * ) tcpipmsg, MsgSize );

			if( commptr->driverconfig.enablemultidropmsg && !strncmp( ( char * )tcpipmsg, commptr->driverconfig.multimsgtypeindicator, strlen( commptr->driverconfig.multimsgtypeindicator ) ) )
			{
				pthread_mutex_lock( &MultiMsgMutex );
				if( strcmp( commptr->multimsg.Buffer, TCTPIP_THREAD_INIT_MSG ) )
				{
					//Dropping Message
					commptr->multimsg.ThreadId = TCPIP_THREAD_INIT_VAL;
					pthread_mutex_unlock( &MultiMsgMutex );
					continue;
				}
				pthread_mutex_unlock( &MultiMsgMutex );

				pthread_t MsgDropThid;
				pthread_attr_t dropthr_attr;
				pthread_attr_init( &dropthr_attr );
				pthread_attr_setdetachstate( &dropthr_attr, 1 );

				pthread_mutex_lock( &MultiMsgMutex );
				if( pthread_create( &MsgDropThid, &dropthr_attr, DropMultipleMsg, commptr ) != 0 )
				{
					commptr->trace( DEBUG_ERROR, "Error in Creating Tcpip Read Thread SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
					pthread_mutex_unlock( &MultiMsgMutex );
					continue;
				}
				commptr->multimsg.ThreadId = MsgDropThid;
				memset( commptr->multimsg.Buffer, 0, sizeof( commptr->multimsg.Buffer ) );
				memcpy( commptr->multimsg.Buffer, tcpipmsg, MsgSize );
				commptr->multimsg.BufferSize = MsgSize;
				pthread_mutex_unlock( &MultiMsgMutex );
			}
			else
			{
				commptr->trace( "Posting Message to Channel[%s]", commptr->driverconfig.destchannel );
				if( commptr->WriteChannel( commptr->driverconfig.destchannel, ( char * )tcpipmsg, MsgSize ) < 0 )
				{
					commptr->trace( "Error in Posting Message to Channel[%s]", commptr->driverconfig.destchannel );
					break;
				}
			}
		}
		close( commptr->DriverConnectionId );
	}
	return ( void * ) 1;
}

void * tcpip_ping_routine( void *threadMessage )
{
    int ConnStatus, PingCount = 0;
    struct timeval now;
    struct timespec timeout;

    pthread_cond_t PingCond;
    pthread_mutex_t PingMutex;
    bool found = false;

    EzCommDrvr *commptr = ( EzCommDrvr *) threadMessage;

    pthread_cond_init( &PingCond, NULL );
    pthread_mutex_init( &PingMutex, NULL );

    while( 1 )
    {
    	commptr->trace( "Waiting for Ping Interval[%d] Seconds", commptr->driverconfig.pinginterval );
        gettimeofday( &now, NULL );
        timeout.tv_sec = now.tv_sec + commptr->driverconfig.pinginterval;
        timeout.tv_nsec = now.tv_usec * 1000;
        pthread_mutex_lock( &PingMutex );
        pthread_cond_timedwait( &PingCond, &PingMutex, &timeout );
        pthread_mutex_unlock( &PingMutex );

		pthread_mutex_lock( &ConnectionFlagMutex );
		ConnStatus = commptr->ConnectionStatus;
		pthread_mutex_unlock( &ConnectionFlagMutex );

		commptr->trace( "ConnStatus = [%d]", ConnStatus );
		if( ConnStatus == PORT_CONNECTED )
		{

			if( !commptr->isPinging() )
            {
            	commptr->trace( "Not Pinging to IpAddress[%s]", commptr->driverconfig.ipaddress );
            	PingCount++;
            	if( PingCount >= commptr->driverconfig.pingprobecount )
                {
            		PingCount = 0;
                    commptr->trace( DEBUG_NORMAL, "Loss in Connection with IpAddress[%s]\n", commptr->driverconfig.ipaddress );
                    close( commptr->DriverConnectionId );
					if( commptr->driverconfig.apptype == TCPIP_SERVER )
						commptr->closeSocket();

                    pthread_cancel( tcpipReadThread );
                    pthread_attr_t thr_attr;
                    pthread_attr_init( &thr_attr );
                    pthread_attr_setdetachstate( &thr_attr, 1 );

					if( pthread_create( &tcpipReadThread, &thr_attr, tcpip_read_routine, commptr ) != 0 )
					{
						commptr->trace( "Error in Creating Tcp/Ip Thread for Driver[%s]....SysErr[%s] ErrNo[%d]", commptr->drivername, strerror( errno ), errno );
						commptr->trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", commptr->drivername );
						commptr->closeDebug();
						commptr->CommExit();
					}
                    commptr->trace( DEBUG_NORMAL, "Created Socket Read Thread with Id[%d]\n", tcpipReadThread );
                }
            }
			else
            	PingCount = 0;
        }
    }
    return ( void * ) 1;
}

bool EzCommDrvr :: IsInteger( const char *InputVal )
{
	for( int i = 0; i < strlen( InputVal ); i++ )
	{
		if( ( InputVal[ i ] < 48 ) && ( InputVal[ i ] > 57 ) )
			return false;
	}
	return true;
}

bool EzCommDrvr :: IsValidIp( char *ipaddress )
{
	int charcount = 0, fld_sep = 0, i = 0;
	for( i = 0; i <= strlen( ipaddress ) - 1; i++ )
	{
		if( !isdigit( ipaddress[ i ] ) )
		{
			if( !charcount )
				return false;
			if( fld_sep > 3 )
				return false;
			if( charcount > 3 )
				return false;
			if( ipaddress[ i ] == '.' )
			{
				charcount = 0;
				fld_sep++;
			}
			else
				return false;
		}
		else
		{
			if( charcount > 3 )
				return false;
			charcount++;
		}
	}
	if( !charcount )
		return false;
	if( fld_sep != 3 )
		return false;
	return true;
}

bool EzCommDrvr :: isPinging()
{
	char Command[ 100 ], StdBuffer[ 200 ];
	FILE *fptr;
	bool found = true;

	memset( Command, 0, sizeof( Command ) );
    sprintf( Command, "ping -c 1 %s", driverconfig.ipaddress );
    fptr = popen( Command, "r" );
    if( fptr == NULL )
    {
        trace( "Error in Opening Pipe SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
        return true;
    }

    while( !feof( fptr ) )
    {
        memset( StdBuffer, 0, sizeof( StdBuffer ) );
        fgets( StdBuffer, sizeof( StdBuffer ), fptr );
        trace( "StdBuffer[%s]", StdBuffer );

        if( !strncmp( PingString, StdBuffer, strlen( PingString ) ) )
        {
        	found = false;
        	break;
        }
    }
    pclose( fptr );
    return found;
}

int EzCommDrvr :: getPingString()
{
	FILE *fptr;
	char FPath[ PING_FILE_PATH_SIZE + 1 ];

	memset( FPath, 0, sizeof( FPath ) );
	sprintf( FPath, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "network", "Ping.dat" );

	fptr = fopen( FPath, "r" );
	if( fptr == NULL )
	{
		trace( "Error in Opening File[%s]", FPath );
		return -1;
	}
	memset( PingString, 0, sizeof( PingString ) );
	fgets( PingString, sizeof( PingString ), fptr );

	fclose( fptr );

	for( int i = 0; i < strlen( PingString ); i++ )
	{
		if( PingString[ i ] == '\n' )
		{
			PingString[ i ] = '\0';
			break;
		}
	}
	trace( "PingString[%s]", PingString );
	return 1;
}

int EzCommDrvr :: updateDeviceConnectionStatus( const char *PortName, int ConnectionStatus )
{
	struct PortStatusDetails portstatusdetails;
	EzDateTimeUtil ezdatetimeutil;

	memset( &portstatusdetails, 0, sizeof( struct PortStatusDetails ) );
	strcpy( portstatusdetails.PortId, PortName );
	portstatusdetails.Status = ConnectionStatus;
	portstatusdetails.Date = ezdatetimeutil.getSysDate();
	portstatusdetails.Time = ezdatetimeutil.getSysTime();

	if( WriteChannel( PORTUPDATERCHANNEL, ( char * ) &portstatusdetails, sizeof( struct PortStatusDetails ) ) < 0 )
	{
		trace( "Error in Writing Connection Status Message to %s", PORTUPDATERCHANNEL );
		return -1;
	}
	return 1;
}

int EzCommDrvr :: LoadDriverConfig( const char *PortName, struct ezcommdrvrconfig *drvrconfig )
{
	EzCfgUtil cfgobj;
	char cfgVal[ CFG_VAL_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], InputString[ INPUT_STRING_SIZE + 1 ];
	int retval;

	strcpy( drvrconfig->drivername, drivername );
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgobj.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#Protocol", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
	{
		trace( "Error in Reading InputString[%s] from file[%s]", InputString, cfgpath );
		trace( "Setting Default Protocol as TCPIP");
		drvrconfig->protocol = TCPIP;
	}
	else
	{
		if( !strcasecmp( cfgVal, "SERIAL" ) )
			drvrconfig->protocol = SERIAL;
		else if( !strcasecmp( cfgVal, "TCPIP" ) )
			drvrconfig->protocol = TCPIP;
		else
		{
			trace( "Invalid Protocol[%s] defined in file[%s]..Protocol should be TCPIP/SERIAL", cfgVal, cfgpath );
			cfgobj.cfg_close();
			return -1;
		}
	}

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#ConnectionType", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
	{
		trace( "Error in Reading InputString[%s] from file[%s]", InputString, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgVal, "accept" ) )
		drvrconfig->apptype = TCPIP_SERVER;
	else if( !strcasecmp( cfgVal, "make" ) )
		drvrconfig->apptype = TCPIP_CLIENT;
	else
	{
		trace( "Invalid ConnectionType[%s] defined in file[%s]..ConnectionType should be accept/make", cfgVal, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#IpAddress", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
	{
		trace( "Error in Reading InputString[%s] from file[%s]", InputString, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	if( !IsValidIp( cfgVal ) )
	{
		trace( "InValid Ipaddress[%s] configured in [%s]", cfgVal, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	strcpy( drvrconfig->ipaddress, cfgVal );

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#PortNo", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
	{
		trace( "Error in Reading InputString[%s] from file[%s]", InputString, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	if( !IsInteger( cfgVal ) )
	{
		trace( "InValid PortNo[%s] configured in [%s]", cfgVal, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	drvrconfig->portno = atoi( cfgVal );

	if( drvrconfig->apptype == TCPIP_CLIENT )
	{
		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#ConnectionMethod", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
			trace( "Setting ConnectionMethod type as static...");
			drvrconfig->connectiontype = STATIC;
    	}
		else
		{
			if( !strcasecmp( cfgVal, "dynamic" ) )
				drvrconfig->connectiontype = DYNAMIC;
			else if ( !strcasecmp( cfgVal, "static" ) )
				drvrconfig->connectiontype = STATIC;
			else
			{
				trace( "InValid ConnectionMethod[%s] configured in [%s]", cfgVal, cfgpath );
				cfgobj.cfg_close();
				return -1;
			}
		}

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#NConnectionRetries", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
			trace( " Setting NConnectionRetries as infinite...");
			drvrconfig->nretries = 0;
	    }
		else
		{
			if( !IsInteger( cfgVal ) )
			{
				trace( "Invalid NConnectionRetries Value[%s] in File[%s]", cfgVal, cfgpath );
				cfgobj.cfg_close();
				return -1;
			}
			drvrconfig->nretries = atoi( cfgVal );
		}

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#ConnectionRetryInterval", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
			trace( "Setting ConnectionRetryInterval as 5 Seconds");
			drvrconfig->retryinterval = 5;
	    }
		else
		{
			if( !IsInteger( cfgVal ) )
			{
				trace( "Invalid ConnectionRetryValue[%s] in File[%s]", cfgVal, cfgpath );
				cfgobj.cfg_close();
				return -1;
			}
			drvrconfig->retryinterval = atoi( cfgVal );
		}

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#BindReq", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
			trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
			trace( "Setting BindReq as No");
			drvrconfig->bindflag = 'N';
		}
		else
		{
			if( !strcasecmp( cfgVal, "Yes" ) )
				drvrconfig->bindflag = 'Y';
			else
				drvrconfig->bindflag = 'N';
		}
	}
	else
	{
		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#NConnections", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
			trace( " Setting NConnections as 1");
			drvrconfig->nconnections = 1;
		}
		else
		{
			if( !IsInteger( cfgVal ) )
			{
				trace( "Invalid NConnections[%s] in File[%s]", cfgVal, cfgpath );
				cfgobj.cfg_close();
				return -1;
			}
			drvrconfig->nconnections = atoi( cfgVal );
		}
		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#EnableKeepalive", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
			trace( "Setting EnableKeepalive as yes" );
			drvrconfig->keepalive = true;
		}
		else
		{
			if( !strcasecmp( cfgVal, "no" ) )
				drvrconfig->keepalive = false;
			else
				drvrconfig->keepalive = true;
		}
	}

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#HeaderLen", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
    if( retval < 0 )
    {
	   	trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
		cfgobj.cfg_close();
    	return -1;
	}

	if( !IsInteger( cfgVal ) )
	{
		trace( "Invalid HeaderLen[%s] in File[%s]", cfgVal, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	drvrconfig->headerlen = atoi( cfgVal );

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#HeaderType", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
    if( retval < 0 )
   	{
	   	trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
		cfgobj.cfg_close();
    	return -1;
	}

	if( !strcasecmp( cfgVal, "ascii" ) )
		drvrconfig->headertype = ASCII;
	else
		drvrconfig->headertype = HEX;

	drvrconfig->enablemultidropmsg = false;

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#EnableMultiDropMsg", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );

	if( retval >= 0 )
	{
		if( !strcasecmp( cfgVal, "Yes" ) )
		{
			trace( "MultiDropMsg Enabled for Driver[%s]", PortName );
			drvrconfig->enablemultidropmsg = true;
		}
	}

	if( drvrconfig->enablemultidropmsg )
	{
		memset( &multimsg, 0, sizeof( multimsg ) );
		multimsg.ThreadId = TCPIP_THREAD_INIT_VAL;
		strcpy( multimsg.Buffer, TCTPIP_THREAD_INIT_MSG );

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#MultiMsgInterval", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
			drvrconfig->multimsginterval = 2;
		else
			drvrconfig->multimsginterval = atoi( cfgVal );

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#MultiMsgTypeIndicator", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
		{
			trace( "Error in Fetching[%s] from file[%s]", InputString, cfgpath );
			cfgobj.cfg_close();
			return -1;
		}
		memset( drvrconfig->multimsgtypeindicator, 0, sizeof( drvrconfig->multimsgtypeindicator ) );
		strcpy( drvrconfig->multimsgtypeindicator, cfgVal );
	}

	drvrconfig->enableping = false;

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#EnablePing", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );

    if( retval >= 0 )
   	{
		if( !strcasecmp( cfgVal, "Yes" ) )
		{
			trace( "Ping Enabled for Driver[%s]", PortName );
			drvrconfig->enableping = true;
		}
	}

	if( drvrconfig->enableping )
	{
		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#PingInterval", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
    	if( retval < 0 )
   		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
	   		trace( "Setting Default PingInterval as 60" );
	   		drvrconfig->pinginterval = 60;
		}
    	else
    	{
    		if( !IsInteger( cfgVal ) )
    		{
    			trace( "Invalid PingInterval[%s] in File[%s]", cfgVal, cfgpath );
    			cfgobj.cfg_close();
    			return -1;
    		}
    		drvrconfig->pinginterval = atoi( cfgVal );
    		trace( DEBUG_TEST, "PingInterval[%d]", drvrconfig->pinginterval );
    	}

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#PingProbeCount", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
   		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
	   		trace( "Setting Default PingProbeCount as 3" );
	   		drvrconfig->pingprobecount = 3;
		}
    	else
    	{
    		if( !IsInteger( cfgVal ) )
    		{
    			trace( "Invalid PingProbeCount[%s] in File[%s]", cfgVal, cfgpath );
    			cfgobj.cfg_close();
    			return -1;
    		}
    		drvrconfig->pingprobecount = atoi( cfgVal );
    		trace( DEBUG_TEST, "PingProbeCount[%d]", drvrconfig->pingprobecount );
    	}
	}

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#DestChannel", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
   	{
	   	trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
		cfgobj.cfg_close();
   		return -1;
	}
	strcpy( drvrconfig->destchannel, cfgVal );

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#DebugFlag", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
		DebugFlag = false;
	else
	{
		if( !strcasecmp( cfgVal, "Yes" ) )
			DebugFlag = true;
		else
			DebugFlag = false;
	}
	cfgobj.cfg_close();
	return 1;
}

int EzCommDrvr :: InitEzCommDrvr( const char *PortName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	struct EzCommTable commtable_ptr;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", PortName );
	if( openDebug( logpath, PortName ) < 0 )
		exit( 0 );

	if( setsid() < 0 )
	{
		trace( "Error in Setting Session Id SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	    trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
		closeDebug();
		exit( 0 );
	}

	if( InitEzCommUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzCommUtil.... ");
	    trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
		closeDebug();
		exit( 0 );
	}

	trace( "Initializing Driver %s ....", PortName );

	memset( &driverconfig, 0, sizeof( driverconfig ) );

	if( LoadDriverConfig( PortName, &driverconfig ) < 0 )
	{
		trace( "Error in loading configuration for Port[%s]", PortName );
        trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
        closeDebug();
		CommExit();
	}

	trace( "[%s] initialized with following parameters", PortName );
	trace( "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	if( driverconfig.protocol == TCPIP )
	{
		trace( "Protocol[TCPIP]");
		if( driverconfig.apptype == TCPIP_SERVER )
		{
			trace( "ApplicationType[Server]");
			trace( "IpAddress[%s]", driverconfig.ipaddress );
			trace( "PortNo[%d]", driverconfig.portno );
			trace( "NConnections[%d]", driverconfig.nconnections );
			if( driverconfig.keepalive )
				trace( "Keepalive[Yes]");
			else
				trace( "Keepalive[No]");
		}
		else
		{
			trace( "ApplicationType[Client]");
			trace( "IpAddress[%s]", driverconfig.ipaddress );
			trace( "PortNo[%d]", driverconfig.portno );
			if( driverconfig.connectiontype == STATIC )
				trace( "ConnectionType[Static]" );
			else
				trace( "ConnectionType[Dynamic]" );
		}

		trace( "HeaderLength[%d]", driverconfig.headerlen );
		if( driverconfig.headertype == ASCII )
			trace( "HeaderType[Ascii]");
		else
			trace( "HeaderType[Hex]");

		trace( "DestinationChannelName[%s]", driverconfig.destchannel );
		if( driverconfig.enableping )
		{
			trace( "PingEnabled[Yes]" );
			trace( "PingInterval[%d]", driverconfig.pinginterval );
			trace( "PingProbeCount[%d]", driverconfig.pingprobecount );
			if( getPingString() < 0 )
			{
				trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
				closeDebug();
				CommExit();
			}
		}
	}

	trace( "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	initEzTCPIPUtil( this, driverconfig );

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( " Error in Initializing EzChannelUtil for Port[%s]", PortName );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
       	closeDebug();
		CommExit();
	}

	if( CreatePortChannel( PortName ) < 0 )
	{
		trace( "Error in Creating Channel For Port[%s]", PortName );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
		closeDebug();
		CommExit();
	}

	memset( this->drivername, 0, sizeof( this->drivername ) );
	strcpy( this->drivername, PortName );

	memset( &commtable_ptr, 0, sizeof( struct EzCommTable ) );

	strcpy( commtable_ptr.PortName, PortName );
	commtable_ptr.PortId = getpid();
	commtable_ptr.PortNo = driverconfig.portno;
	commtable_ptr.ApplType = driverconfig.apptype;
	commtable_ptr.PortStatus = PORT_INIT_VAL;
	strcpy( commtable_ptr.IpAddress, driverconfig.ipaddress );

	if( CommInit( commtable_ptr ) < 0 )
	{
		trace( "Error in Initializing Port[%s] in CommTable", PortName );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", PortName );
		closeDebug();
		CommExit();
	}

	initEzSigUtil( this );

	return 1;
}

void EzCommDrvr :: StartCommDriver()
{
	if( driverconfig.protocol == TCPIP )
		StartTCPIPDriver();
}

void EzCommDrvr :: StartTCPIPDriver()
{
	short int MsgSize;
	int size, retval, ConnStatus;
	unsigned char tcpipmsg[ COMM_MSG_SIZE + 1 ];
	char tcpipheader[ COMM_HEADER_SIZE + 1 ];
	pthread_attr_t thr_attr;

	pthread_attr_init( &thr_attr );
	pthread_attr_setdetachstate( &thr_attr, 1 );

	if( pthread_create( &tcpipReadThread, &thr_attr, tcpip_read_routine, this ) != 0 )
	{
		trace( "Error in Creating Tcp/Ip Thread for Driver[%s]....SysErr[%s] ErrNo[%d]", drivername, strerror( errno ), errno );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", drivername );
		closeDebug();
		CommExit();
	}

	if( driverconfig.enableping )
	{
		trace( DEBUG_TEST, "Ping is Enabled for Driver[%s]", drivername );

		if( pthread_create( &tcpipPingThread, &thr_attr, tcpip_ping_routine, this ) != 0 )
		{
			trace( "Error in Creating Ping Thread for Driver[%s]....SysErr[%s] ErrNo[%d]", drivername, strerror( errno ), errno );
			trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", drivername );
			closeDebug();
			CommExit();
		}
	}

	while( 1 )
	{
		trace( DEBUG_NORMAL, "Driver[%s] waiting for Message in PortChannel", drivername );
		memset( tcpipmsg, 0, sizeof( tcpipmsg ) );
		if( ReadMessage( ( char * )tcpipmsg + driverconfig.headerlen, &size ) < 0 )
		{
			trace( "Error in Receiving Message From Driver Channel....");
			sleep( 1 );
			continue;
		}
		if( !strcmp( this->GetLastSenderChannelName(), "ezportcmd" ) )
		{
			if( !strcasecmp( ( char * ) tcpipmsg + driverconfig.headerlen, "debug-on" ) )
			{
				trace( "Debug-On message received from portcmd...." );
				DebugFlag = true;
			}
			else
			{
				trace( "Debug-Off message received from portcmd...." );
				DebugFlag = false;
			}
			continue;
		}
		pthread_mutex_lock( &ConnectionFlagMutex );
		ConnStatus = ConnectionStatus;
		pthread_mutex_unlock( &ConnectionFlagMutex );

		if( ConnStatus == PORT_DISCONNECTED )
		{
			trace( DEBUG_NORMAL, "Port[%s] is not Connected...Dropping Message", drivername );
			continue;
		}

		if( driverconfig.headertype == ASCII )
		{
			memset( tcpipheader, 0, sizeof( tcpipheader ) );
			sprintf( tcpipheader, "%0*d", driverconfig.headerlen, size );
			memcpy( tcpipmsg, tcpipheader, driverconfig.headerlen );
		}
		else if( driverconfig.headertype == HEX )
		{
			MsgSize = size;
			MsgSize = htons( MsgSize );
			memcpy( tcpipmsg, &MsgSize, driverconfig.headerlen );
		}
		trace( "Received [%d] bytes from Channel[%s]", size, this->GetLastSenderChannelName() );

		if( DebugFlag )
			hex_dump( ( unsigned char * )tcpipmsg, driverconfig.headerlen + size );

		retval = write( DriverConnectionId, tcpipmsg, driverconfig.headerlen + size );
		if( retval < 0 )
		{
			trace( "Error in Writing Message to Socket..ErrNo[%d] StrError[%s]", errno, strerror( errno ) );
			close( DriverConnectionId );
			if( driverconfig.apptype == TCPIP_SERVER )
				closeSocket();
            pthread_cancel( tcpipReadThread );
			pthread_attr_t thr_attr;
			pthread_attr_init( &thr_attr );
			pthread_attr_setdetachstate( &thr_attr, 1 );
			if( pthread_create( &tcpipReadThread, &thr_attr, tcpip_read_routine, this ) != 0 )
			{
				trace( "Error in Creating Tcp/Ip Thread for Driver[%s]....SysErr[%s] ErrNo[%d]", drivername, strerror( errno ), errno );
				trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", drivername );
				closeDebug();
				CommExit();
			}
			trace( DEBUG_NORMAL, "Created Socket Read Thread with Id[%d]", tcpipReadThread );
		}
		else
			trace( DEBUG_NORMAL, "[%d] Bytes Written to Socket", retval );
	}
}

int main( int argc, char **argv )
{
	if( argc != 2 )
		exit( 0 );
	EzCommDrvr ezcommdrvr;
	ezcommdrvr.InitEzCommDrvr( argv[ 1 ] );
	ezcommdrvr.StartCommDriver();
	return 1;
}
