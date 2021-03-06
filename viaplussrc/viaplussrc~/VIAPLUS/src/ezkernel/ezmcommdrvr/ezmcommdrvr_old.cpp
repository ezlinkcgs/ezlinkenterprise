#include <ezkernel/ezmcommdrvr.h>

void * tcpip_select_routine( void *threadMessage )
{
	char tcpipheader[ COMM_HEADER_SIZE + 1 ];
	unsigned char tcpipmsg[ COMM_MSG_SIZE + 1 ];
	short int MsgSize;
	EzMCommDrvr *mcommptr = ( EzMCommDrvr *) threadMessage;

	struct timeval now;
	struct timespec timeout;

	pthread_cond_t EventCond;
	pthread_mutex_t EventMutex;

	pthread_cond_init( &EventCond, NULL );
	pthread_mutex_init( &EventMutex, NULL );

    /*gettimeofday( &now, NULL );
    timeout.tv_sec = now.tv_sec + 3;
    timeout.tv_nsec = now.tv_usec * 1000;
	pthread_mutex_lock( &EventMutex );
	pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
	pthread_mutex_unlock( &EventMutex );*/

	mcommptr->trace( DEBUG_TEST, "Tcp/Ip thread for driver[%s]...started", mcommptr->drivername );

	while( 1 )
	{
		if( mcommptr->createSocket() < 0 )
		{
			mcommptr->trace( DEBUG_ERROR, "Error in Creating Socket for Driver[%s] ...SysErr[%s] ErrNo[%d]", mcommptr->drivername, strerror( errno ), errno );
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

	mcommptr->ProcessClientRequest( );
	return ( void * ) 1;
}

bool EzMCommDrvr :: isPinging()
{
	char Command[ 100 ], StdBuffer[ 200 ];
	FILE *fptr;
	bool found = true;

	memset( Command, 0, sizeof( Command ) );
    sprintf( Command, "ping -c 1 %s", drvrconfig.ipaddress );
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

int EzMCommDrvr :: getPingString()
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
/*int EzMCommDrvr :: updateDeviceConnectionStatus( const char *PortName, int ConnectionStatus )
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
}*/

int EzMCommDrvr :: Loaddrvrconfig( const char *PortName )
{
	EzCfgUtil cfgobj;
	char cfgVal[ CFG_VAL_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], InputString[ INPUT_STRING_SIZE + 1 ];
	int retval;

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
		drvrconfig.protocol = TCPIP;
	}
	else
	{
		if( !strcasecmp( cfgVal, "SERIAL" ) )
			drvrconfig.protocol = SERIAL;
		else if( !strcasecmp( cfgVal, "TCPIP" ) )
			drvrconfig.protocol = TCPIP;
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
		drvrconfig.apptype = TCPIP_SERVER;
	else if( !strcasecmp( cfgVal, "make" ) )
		drvrconfig.apptype = TCPIP_CLIENT;
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
	strcpy( drvrconfig.ipaddress, cfgVal );

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
	drvrconfig.portno = atoi( cfgVal );


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
		drvrconfig.headertype = ASCII;
	else
		drvrconfig.headertype = HEX;

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
	drvrconfig.headerlen = atoi( cfgVal );


	drvrconfig.enablemultidropmsg = false;

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#EnableMultiDropMsg", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );

	if( retval >= 0 )
	{
		if( !strcasecmp( cfgVal, "Yes" ) )
		{
			trace( "MultiDropMsg Enabled for Driver[%s]", PortName );
			drvrconfig.enablemultidropmsg = true;
		}
	}

	if( drvrconfig.enablemultidropmsg )
	{
		memset( &multimsg, 0, sizeof( multimsg ) );
		multimsg.ThreadId = TCPIP_THREAD_INIT_VAL;
		strcpy( multimsg.Buffer, TCTPIP_THREAD_INIT_MSG );

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#MultiMsgInterval", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
			drvrconfig.multimsginterval = 2;
		else
			drvrconfig.multimsginterval = atoi( cfgVal );

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
		memset( drvrconfig.multimsgtypeindicator, 0, sizeof( drvrconfig.multimsgtypeindicator ) );
		strcpy( drvrconfig.multimsgtypeindicator, cfgVal );
	}

	drvrconfig.enableping = false;

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#EnablePing", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );

    if( retval >= 0 )
   	{
		if( !strcasecmp( cfgVal, "Yes" ) )
		{
			trace( "Ping Enabled for Driver[%s]", PortName );
			drvrconfig.enableping = true;
		}
	}

	if( drvrconfig.enableping )
	{
		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#PingInterval", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
    	if( retval < 0 )
   		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
	   		trace( "Setting Default PingInterval as 60" );
	   		drvrconfig.pinginterval = 60;
		}
    	else
    	{
    		if( !IsInteger( cfgVal ) )
    		{
    			trace( "Invalid PingInterval[%s] in File[%s]", cfgVal, cfgpath );
    			cfgobj.cfg_close();
    			return -1;
    		}
    		drvrconfig.pinginterval = atoi( cfgVal );
    		trace( DEBUG_TEST, "PingInterval[%d]", drvrconfig.pinginterval );
    	}

		memset( InputString, 0, sizeof( InputString ) );
		sprintf( InputString, "%s#PingProbeCount", PortName );
		memset( cfgVal, 0, sizeof( cfgVal ) );
		retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
		if( retval < 0 )
   		{
	   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
	   		trace( "Setting Default PingProbeCount as 3" );
	   		drvrconfig.pingprobecount = 3;
		}
    	else
    	{
    		if( !IsInteger( cfgVal ) )
    		{
    			trace( "Invalid PingProbeCount[%s] in File[%s]", cfgVal, cfgpath );
    			cfgobj.cfg_close();
    			return -1;
    		}
    		drvrconfig.pingprobecount = atoi( cfgVal );
    		trace( DEBUG_TEST, "PingProbeCount[%d]", drvrconfig.pingprobecount );
    	}
	}

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#NConnections", PortName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
	{
   		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
		trace( " Setting NConnections as 1");
		drvrconfig.nconnections = 1;
	}
	else
	{
		if( !IsInteger( cfgVal ) )
		{
			trace( "Invalid NConnections[%s] in File[%s]", cfgVal, cfgpath );
			cfgobj.cfg_close();
			return -1;
		}
		drvrconfig.nconnections = atoi( cfgVal );
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
	strcpy( drvrconfig.destchannel, cfgVal );
	cfgobj.cfg_close();
	return 1;


}

int EzMCommDrvr :: InitEzMCommDrvr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", TaskName );
	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^%s Started^^^^^^^^^^^^^", TaskName );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzTaskUtil");
		trace( DEBUG_ERROR,"^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName );
		closeDebug();
		exit( 0 );
	}

	trace( DEBUG_TEST, "Loading Configuration for %s ....", TaskName );
	memset( &drvrconfig, 0, sizeof( drvrconfig ) );
	if( Loaddrvrconfig( TaskName ) < 0 )
	{
		trace( "Error in loading configuration for Port[%s]", TaskName );
        trace( "~~~~~~~~~~~~~~~~~~%s TaskName Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
        closeDebug();
        exit( 0 );
	}

	trace( "[%s] initialized with following parameters", TaskName );
	trace( "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	trace( "IpAddress[%s]", drvrconfig.ipaddress );
	trace( "PortNo[%d]", drvrconfig.portno );
	trace( "HeaderLength[%d]", drvrconfig.headerlen );
	if( drvrconfig.headertype == ASCII )
		trace( "HeaderType[Ascii]");
	else
		trace( "HeaderType[Hex]");
	trace( "NConnections[%d]", drvrconfig.nconnections );
	trace( "DestinationChannelName[%s]", drvrconfig.destchannel );
	if( drvrconfig.enableping )
	{
		trace( "PingEnabled[Yes]" );
		trace( "PingInterval[%d]", drvrconfig.pinginterval );
		trace( "PingProbeCount[%d]", drvrconfig.pingprobecount );
		if( getPingString() < 0 )
		{
			trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
			closeDebug();
			exit( 0 );
		}
	}

	trace( "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( " Error in Initializing EzChannelUtil for Port[%s]", TaskName );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
       	closeDebug();
       	exit( 0 );
	}
	if( CreateChannel( TaskName, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating [%s] Channel", TaskName );
		trace( DEBUG_ERROR,"^^^^^^^^^^^[%s] Ended Abnormally^^^^^^^^^^^^^", TaskName );
		closeDebug();
		exit( 0 );
	}

	if( InitEzMCommDrvrUtil( this , TaskName, drvrconfig, this ) < 0 )
	{
		trace( "Error in initializing commdrvrutil" );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
        closeDebug();
        exit( 0 );
	}
	if( ( IsTaskRunning( TaskName ) < 0 )  )
	{
		trace( DEBUG_NORMAL, "First Instance of %s...Initializing", TaskName );
		if( CreateMCommConnInfoMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading %ssMEMORY Memory...", TaskName );
			trace( DEBUG_ERROR,"^^^^^^^^^^^[%s] Ended Abnormally^^^^^^^^^^^^^", TaskName );
			closeDebug();
			exit( 0 );
		}
		else
			trace( DEBUG_NORMAL,"%sMEMORY Memory Loaded sucessfully...", TaskName );
	}
	else
	{
		trace( DEBUG_NORMAL, "More than one instance Initializing, Attaching Memory for Process", TaskName );
		if( AttacheMCommConnInfoMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading %ssMEMORY Memory...", TaskName );
			trace( DEBUG_ERROR,"^^^^^^^^^^^[%s] Ended Abnormally^^^^^^^^^^^^^", TaskName );
			closeDebug();
			exit( 0 );
		}
		else
			trace( DEBUG_NORMAL,"%sMEMORY Memory Loaded sucessfully...", TaskName );
	}
	TaskInit();
	initEzSigUtil( this );

	memset( this->drivername, 0, sizeof( this->drivername ) );
	strcpy( this->drivername, TaskName );

	return 1;
}

void EzMCommDrvr :: StartMCommDriver()
{
	short int MsgSize;
	int size, retval,ConnectionId;
	unsigned char tcpipmsg[ COMM_MSG_SIZE + 1 ];
	char DriverMsg[ 4096 ];
	char ConnIdStr[ 13 ]; //Used To Identify the ConnectionId When To Send Message To Client
	char tcpipheader[ COMM_HEADER_SIZE + 1 ];
	char IpAddress[ IPLEN + 1 ];
	pthread_attr_t thr_attr;

	pthread_attr_init( &thr_attr );
	pthread_attr_setdetachstate( &thr_attr, 1 );

	if( pthread_create( &tcpipReadThread, &thr_attr, tcpip_select_routine, this ) != 0 )
	{
		trace( "Error in Creating Tcp/Ip Thread for Driver[%s]....SysErr[%s] ErrNo[%d]", drivername, strerror( errno ), errno );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", drivername );
		closeDebug();
		exit( 0 );
	}
	while( 1 )
	{
		trace( DEBUG_NORMAL, "Driver[%s] waiting for Message ", drivername );
		memset( tcpipmsg, 0, sizeof( tcpipmsg ) );
		memset( DriverMsg, 0, sizeof( DriverMsg ) );
		if( ReadMessage( ( char * )DriverMsg, &size ) < 0 )
		{
			trace( "Error in Receiving Message From PosDriver Channel....");
			sleep( 1 );
			continue;
		}
		hex_dump( ( unsigned char * )DriverMsg, size  );
		size = size - 12;
		//GetPosRefNum( DriverMsg, PosRefNum );

		memset( ConnIdStr, 0, sizeof( ConnIdStr ) );
		strncpy( ConnIdStr, DriverMsg, 12 );
		trace( DEBUG_TEST, "ConnIdStr[%s] Got From Driver Message",  ConnIdStr );
		if( GetConnectionIdMemory( &ConnectionId, IpAddress, ConnIdStr )< 0 )
		{
			trace( "No ConnectionId Found For ConnIdStr[%s], Dropping Message",  ConnIdStr );
			continue;
		}
		trace( DEBUG_TEST, "ConnectionId[ %d ],IpAddress[ %s ] Got For ConnIdStr[ %s ] Got From Driver Message",  ConnectionId, IpAddress, ConnIdStr );
		if( drvrconfig.headertype == ASCII )
		{
			memset( tcpipheader, 0, sizeof( tcpipheader ) );
			sprintf( tcpipheader, "%0*d", drvrconfig.headerlen, size );
			memcpy( tcpipmsg, tcpipheader, drvrconfig.headerlen );
		}
		else if( drvrconfig.headertype == HEX )
		{
			MsgSize = size;
			MsgSize = htons( MsgSize );
			memcpy( tcpipmsg, &MsgSize, drvrconfig.headerlen );
		}
		memcpy( ( char * )tcpipmsg + drvrconfig.headerlen,  DriverMsg + 12, size );
		hex_dump( ( unsigned char * )tcpipmsg, drvrconfig.headerlen + size  );
		retval = write( ConnectionId, tcpipmsg, drvrconfig.headerlen + size );
		if( retval < 0 )
		{
			trace( "Error in Writing Message to Socket..ErrNo[%d] StrError[%s]", errno, strerror( errno ) );
			close( ConnectionId );
			FD_CLR(  ConnectionId, &AllSet );
			if(  ConnectionId == fdmax )
					fdmax = fdmax - 1;
			RemoveMCommConnInfoMemory( ConnectionId );

		}
		else
			trace( DEBUG_NORMAL, "[%d] Bytes Written to Socket", retval );
	}

}

int main( int argc, char **argv )
{
	EzMCommDrvr ezmcommdrvr;
	ezmcommdrvr.InitEzMCommDrvr( argv[ 0 ] );
	ezmcommdrvr.StartMCommDriver();
	return 1;
}




