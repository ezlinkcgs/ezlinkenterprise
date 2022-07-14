#include <ezbusiness/ezhsmtools.h>

pthread_mutex_t HSMInfoTableMutex = PTHREAD_MUTEX_INITIALIZER;

int EzHSMTools :: initHSMTools( EzDebugUtil *dptr, int MaxHSM, EzSecurityDriverUtil *securitydriverutil_ptr, EzChannelUtil *chutil_ptr )
{
	this->dptr = dptr;
	this->securitydriverutil_ptr = securitydriverutil_ptr;
	this->chutil_ptr = chutil_ptr;
	this->MaxHSMs = MaxHSM;

	hsmconninfo_ptr = ( struct EzHSMConnectionInfo * ) malloc( sizeof( struct EzHSMConnectionInfo ) * MaxHSMs );

	if( hsmconninfo_ptr == NULL )
	{
		dptr->trace( "Error in Allocating Memory for HSM Info Table" );
		return -1;
	}
	for( int i = 0; i < MaxHSMs; i++ )
	{
		memset( hsmconninfo_ptr + i, 0, sizeof( struct EzHSMConnectionInfo ) );
		strcpy( ( hsmconninfo_ptr + i )->HSMName, EZSEC_HSM_INIT_NAME );
	}
	return 1;
}

int EzHSMTools :: connectWithHSM( const char *HSMName, const char *IpAddress, int PortNo )
{
	int ConnectionId;
	struct sockaddr_in saddr;
	ConnectionId = socket( AF_INET, SOCK_STREAM, 0 );
	if( ConnectionId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating HSM Socket for HSM[%s] SysErr[%s] ErrNo[%d]", HSMName, strerror( errno ), errno );
		return -1;
	}
	socklen_t addlen = sizeof( saddr );
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( PortNo );
	saddr.sin_addr.s_addr = inet_addr( IpAddress );
	memset( &saddr.sin_zero, 0, 8 );
	if( connect( ConnectionId, ( struct sockaddr * ) &saddr, addlen ) < 0 )
	{
		//dptr->trace( DEBUG_ERROR, "Failed to Connect with HSM[%s] IpAddress[%s] PortNo[%d] SysErr[%s] ErrNo[%d]", HSMName, IpAddress, PortNo, strerror( errno ), errno );
		close( ConnectionId );
		return -1;
	}
	dptr->trace( DEBUG_ERROR, "Connected with HSM[%s] IpAddress[%s] PortNo[%d]", HSMName, IpAddress, PortNo );
	return ConnectionId;
}

void* serviceHSMConnectionThread( void *threadmsg )
{
	EzHSMTools *thmsg = ( EzHSMTools * ) threadmsg;
	struct EzHSMConnectionInfo hsmconninfo;
	struct timeval now;
	struct timespec timeout;
	int ConnectionId, retval;

	pthread_cond_t EventCond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t EventMutex = PTHREAD_MUTEX_INITIALIZER;

	while( 1 )
	{
		gettimeofday( &now, NULL );
		timeout.tv_sec = now.tv_sec + 1;
		timeout.tv_nsec = now.tv_usec * 1000;
		pthread_mutex_lock( &EventMutex );
		pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
		pthread_mutex_unlock( &EventMutex );

		pthread_mutex_lock( &HSMInfoTableMutex );
		memset( &hsmconninfo, 0, sizeof( struct EzHSMConnectionInfo ) );
		retval = thmsg->readHSMConnectionInfo( pthread_self(), &hsmconninfo );
		pthread_mutex_unlock( &HSMInfoTableMutex );
		if( retval < 0 )
			continue;
		else
			break;
	}

	thmsg->dptr->trace( DEBUG_TEST, "HSM Connection Thread Started for HSM[%s]", hsmconninfo.HSMName );

	pthread_mutex_lock( &HSMInfoTableMutex );
	thmsg->securitydriverutil_ptr->updateHSMStatus( hsmconninfo.HSMName, EZSEC_HSM_DISCONNECTED );
	pthread_mutex_unlock( &HSMInfoTableMutex );

	pthread_mutex_lock( &HSMInfoTableMutex );
	thmsg->updateHSMConnectionStatus( hsmconninfo.HSMName, EZSEC_HSM_DISCONNECTED );
	pthread_mutex_unlock( &HSMInfoTableMutex );

	thmsg->dptr->trace( "Trying to Connect with HSM[%s] IpAddress[%s] PortNo[%d]", hsmconninfo.HSMName, hsmconninfo.HSMAddress, hsmconninfo.HSMPortNo );
	while( 1 )
	{
		ConnectionId = thmsg->connectWithHSM( hsmconninfo.HSMName, hsmconninfo.HSMAddress, hsmconninfo.HSMPortNo );
		if( ConnectionId < 0 )
		{
			//thmsg->dptr->trace( DEBUG_ERROR, "Error in Connection with HSM[%s] IpAddress[%s] PortNo[%d]", hsmconninfo.HSMName, hsmconninfo.HSMAddress, hsmconninfo.HSMPortNo );
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + hsmconninfo.ConnectionInterval;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
		}
		else
			break;
	}
	pthread_mutex_lock( &HSMInfoTableMutex );
	thmsg->securitydriverutil_ptr->updateHSMStatus( hsmconninfo.HSMName, EZSEC_HSM_CONNECTED );
	pthread_mutex_unlock( &HSMInfoTableMutex );

	pthread_mutex_lock( &HSMInfoTableMutex );
	thmsg->updateHSMConnectionId( hsmconninfo.HSMName, ConnectionId );
	pthread_mutex_unlock( &HSMInfoTableMutex );

	return ( void * ) 1;
}

int EzHSMTools :: initHSMConnection( struct EzHSMInfo hsminfo )
{
	pthread_mutex_lock( &HSMInfoTableMutex );
	if( addHSMConnectionInfo( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo, hsminfo.ConnectionInterval ) < 0 )
	{
		pthread_mutex_unlock( &HSMInfoTableMutex );
		dptr->trace( "Error in adding HSM[%s] in HSMConnectionInfo Table....", hsminfo.HSMName );
		return -1;
	}
	pthread_mutex_unlock( &HSMInfoTableMutex );

	pthread_t HSMConnectionThread;
	pthread_attr_t HSMConnectionThreadAttr;
	pthread_attr_init( &HSMConnectionThreadAttr );
	pthread_attr_setdetachstate( &HSMConnectionThreadAttr, 1 );

	if( pthread_create( &HSMConnectionThread, &HSMConnectionThreadAttr, serviceHSMConnectionThread, ( void * ) this ) != 0 )
	{
		dptr->trace( "Error in Creating HSMConnectionThread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	pthread_mutex_lock( &HSMInfoTableMutex );
	if( updateHSMThreadId( hsminfo.HSMName, HSMConnectionThread ) < 0 )
	{
		dptr->trace( "Error in Updating HSM ThreadId for HSM[%s]",hsminfo.HSMName );
		pthread_cancel( HSMConnectionThread );
		return -1;
	}
	pthread_mutex_unlock( &HSMInfoTableMutex );
	return 1;
}

int EzHSMTools :: readHSMConnectionInfo( pthread_t HSMThreadId, struct EzHSMConnectionInfo *hsmconninfo_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( ( hsmconninfo_ptr + i )->HSMThreadId == HSMThreadId )
		{
			retval = 1;
			memcpy( hsmconninfo_rec, hsmconninfo_ptr + i, sizeof( struct EzHSMConnectionInfo ) );
			break;
		}
	}
	return retval;
}

int EzHSMTools :: readHSMConnectionInfo( const char *HSMName, struct EzHSMConnectionInfo *hsmconninfo_rec )
{
	int retval = -1;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			retval = 1;
			memcpy( hsmconninfo_rec, hsmconninfo_ptr + i, sizeof( struct EzHSMConnectionInfo ) );
			break;
		}
	}
	return retval;
}

int EzHSMTools :: readHSMConnectionInfo( const char *HSMName )
{
	int retval = -1;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzHSMTools :: getNHSM()
{
	int HSMCount = 0;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( strcmp( ( hsmconninfo_ptr + i )->HSMName, EZSEC_HSM_INIT_NAME ) )
			HSMCount++;
	}
	return HSMCount;
}

int EzHSMTools :: addHSMConnectionInfo( const char *HSMName, const char *HSMAddress, int HSMPortNo, int ConnectionInterval )
{
	int retval = -1;

	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, EZSEC_HSM_INIT_NAME ) )
		{
			memset( hsmconninfo_ptr + i, 0, sizeof( struct EzHSMConnectionInfo ) );
			strcpy( ( hsmconninfo_ptr + i )->HSMName, HSMName );
			strcpy( ( hsmconninfo_ptr + i )->HSMAddress, HSMAddress );
			( hsmconninfo_ptr + i )->ConnectionInterval = ConnectionInterval;
			( hsmconninfo_ptr + i )->HSMPortNo = HSMPortNo;
			( hsmconninfo_ptr + i )->HSMStatus = EZSEC_HSM_DISCONNECTED;
			( hsmconninfo_ptr + i )->HSMConnectionId = -1;
			( hsmconninfo_ptr + i )->HSMThreadId = 0;
			( hsmconninfo_ptr + i )->HSMThreadFlag = false;
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzHSMTools :: updateHSMThreadId( const char *HSMName, pthread_t HSMThreadId )
{
	int retval = -1;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			( hsmconninfo_ptr + i )->HSMThreadId = HSMThreadId;
			( hsmconninfo_ptr + i )->HSMThreadFlag = true;
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzHSMTools :: updateHSMConnectionId( const char *HSMName, int ConnectionId )
{
	int retval = -1;
	dptr->trace( "Updating ConnectionId for HSMName[%s] ConnectionId[%d]", HSMName, ConnectionId );
	for( int i = 0; i < MaxHSMs; i++ )
	{
		dptr->trace( "HSMName[%s]", ( hsmconninfo_ptr + i )->HSMName );
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			( hsmconninfo_ptr + i )->HSMConnectionId = ConnectionId;
			( hsmconninfo_ptr + i )->HSMStatus = EZSEC_HSM_CONNECTED;
			retval = 1;
			break;
		}
	}
	if( retval == -1 )
		return retval;

	struct EzHSMInfoMsg hsminfomsg;
	struct EzSecurityMgrQMsg ezsecmgrqmsgObj;

	memset( &hsminfomsg, 0, sizeof( struct EzHSMInfoMsg ) );
	strcpy( hsminfomsg.HSMName, HSMName );
	hsminfomsg.HSMStatus = EZSEC_HSM_CONNECTED;

	memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );
	ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
	ezsecmgrqmsgObj.CommandCode = EZSEC_HSMINFO;
	ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
	memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&hsminfomsg, sizeof( struct EzHSMInfoMsg ) );

	dptr->trace("Routing Message bytes [ %d ] to %s", sizeof( struct EzSecurityMgrQMsg ), EZSEC_SECURITYMGRCHANNEL );

	if( chutil_ptr->WriteChannel( EZSEC_SECURITYMGRCHANNEL, (char*) &ezsecmgrqmsgObj, sizeof( struct EzSecurityMgrQMsg ) ) < 0 )
	{
		dptr->trace( "Unable to write into the channel %s", EZSEC_SECURITYMGRCHANNEL );
		return -1;
	}
	else
		dptr->trace( "Message Posted into the %s channel", EZSEC_SECURITYMGRCHANNEL );

	return 1;

}

int EzHSMTools :: updateHSMConnectionStatus( const char *HSMName, int HSMStatus )
{
	int retval = -1;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			( hsmconninfo_ptr + i )->HSMStatus = HSMStatus;
			retval = 1;
			break;
		}
	}

	if( retval == -1 )
		return retval;

	struct EzHSMInfoMsg hsminfomsg;
	struct EzSecurityMgrQMsg ezsecmgrqmsgObj;

	memset( &hsminfomsg, 0, sizeof( struct EzHSMInfoMsg ) );
	strcpy( hsminfomsg.HSMName, HSMName );
	hsminfomsg.HSMStatus = HSMStatus;

	memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );
	ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
	ezsecmgrqmsgObj.CommandCode = EZSEC_HSMINFO;
	ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
	memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&hsminfomsg, sizeof( struct EzHSMInfoMsg ) );

	dptr->trace("Routing Message bytes [ %d ] to %s", sizeof( struct EzSecurityMgrQMsg ), EZSEC_SECURITYMGRCHANNEL );

	if( chutil_ptr->WriteChannel( EZSEC_SECURITYMGRCHANNEL, (char*)&ezsecmgrqmsgObj, sizeof( struct EzSecurityMgrQMsg ) ) < 0 )
	{
		dptr->trace( "Unable to write into the channel %s", EZSEC_SECURITYMGRCHANNEL );
		return -1;
	}
	else
		dptr->trace( "Message Posted into the %s channel", EZSEC_SECURITYMGRCHANNEL );

	return 1;
}

bool EzHSMTools :: isSecurityConnected( const char *HSMName )
{
	bool retval = false;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		dptr->trace( "HSMName[%s]...HSMName[%s]", ( hsmconninfo_ptr + i )->HSMName, HSMName );
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			if( ( hsmconninfo_ptr + i )->HSMStatus == EZSEC_HSM_CONNECTED )
				retval = true;
			break;
		}
	}
	return retval;
}

int EzHSMTools :: getConnectionId( const char *HSMName )
{
	int retval = -1;
	for( int i = 0; i < MaxHSMs; i++ )
	{
		if( !strcmp( ( hsmconninfo_ptr + i )->HSMName, HSMName ) )
		{
			retval = ( hsmconninfo_ptr + i )->HSMConnectionId;
			break;
		}
	}
	return retval;
}

