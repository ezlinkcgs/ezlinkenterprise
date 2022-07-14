#include <ezkernel/ezmcommdrvr.h>

void* tcpip_write_routine( void *threadMessage )
{
	EzMCommDrvr *thmsg = ( EzMCommDrvr *) threadMessage;
	char tcpipmsg[ COMM_MSG_SIZE + 1 ], finaltcpipmsg[ COMM_MSG_SIZE + 1 ], RefNum[ CONNECTION_REFNUM_SIZE + 1 ], tcpipheader[ COMM_HEADER_SIZE ];
	int size, ConnectionId, retval;
	short int MsgSize;
	struct EzMCommConnInfo connectioninfo_rec;
	while( 1 )
	{
		thmsg->trace( "Driver[%s] Writer Thread Waiting for Message in Channel[%s]", thmsg->DriverName, thmsg->GetSourceChannelName() );
		memset( tcpipmsg, 0, sizeof( tcpipmsg ) );

		if( thmsg->ReadMessage( ( char * )tcpipmsg, &size ) < 0 )
		{
			thmsg->trace( "Error in Receiving Message From Driver Channel[%s]....", thmsg->GetSourceChannelName() );
			sleep( 1 );
			continue;
		}

		thmsg->trace( "Received [%d] bytes from Channel[%s]", size, thmsg->GetLastSenderChannelName() );

		memset( RefNum, 0, sizeof( RefNum ) );
		for( int i = 0, j = 0; i < size; i++ )
		{
			if( tcpipmsg[ i ] == 0x1c )
				break;
			else
			{
				RefNum[ j ] = tcpipmsg[ i ];
				j++;
			}
		}

		if( !strlen( RefNum ) )
		{
			thmsg->trace( "Cannot Get Connection RefNum from Message....Dropping the Message..." );
			continue;
		}

		thmsg->trace( "Got Connection RefNum[%s] from Message....", RefNum );

		size = size - ( strlen( RefNum ) + 1 );
		memset( finaltcpipmsg, 0, sizeof( finaltcpipmsg ) );

		if( thmsg->drvrconfig.headertype == ASCII )
		{
			memset( tcpipheader, 0, sizeof( tcpipheader ) );
			sprintf( tcpipheader, "%0*d", thmsg->drvrconfig.headerlen, size );
			memcpy( finaltcpipmsg, tcpipheader, thmsg->drvrconfig.headerlen );
		}
		else if( thmsg->drvrconfig.headertype == HEX )
		{
			MsgSize = size;
			MsgSize = htons( MsgSize );
			memcpy( finaltcpipmsg, &MsgSize, thmsg->drvrconfig.headerlen );
		}

		memcpy( finaltcpipmsg + thmsg->drvrconfig.headerlen, tcpipmsg + strlen( RefNum ) + 1, size );
		memset( &connectioninfo_rec, 0, sizeof( struct EzMCommConnInfo ) );
		retval = thmsg->getConnectionId( RefNum, &connectioninfo_rec );

		if( retval < 0 )
		{
			thmsg->trace( "Cannot Get ConnectionId for RefNum[%s] from Message....Dropping the Message...", RefNum );
			continue;
		}

		thmsg->trace( "Got ConnectionId[%d] for RefNum[%s]", connectioninfo_rec.ConnectionId, RefNum );

		retval = write( connectioninfo_rec.ConnectionId, finaltcpipmsg, thmsg->drvrconfig.headerlen + size );

		if( retval < 0 )
		{
			thmsg->trace( "Error in Writing Message to Socket..ErrNo[%d] StrError[%s]", errno, strerror( errno ) );
			close( connectioninfo_rec.ConnectionId );
			pthread_cancel( connectioninfo_rec.ConnectionThread );
			pthread_cancel( connectioninfo_rec.TimeOutThread );
			thmsg->removeConnectionMemory( connectioninfo_rec.ConnectionId );
			break;
		}
		else
		{
			thmsg->hex_dump( ( unsigned char * ) finaltcpipmsg, thmsg->drvrconfig.headerlen + size );
			thmsg->trace( DEBUG_NORMAL, "[%d] Bytes Written to Socket", retval );
		}
	}
}

void* tcpip_read_routine( void *threadMessage )
{
	char tcpipheader[ COMM_HEADER_SIZE + 1 ];
	unsigned char tcpipmsg[ COMM_MSG_SIZE + 1 ], finaltcpipmsg[ COMM_MSG_SIZE + 1 ];
	short int MsgSize;
	int retval;
	struct EzMCommConnInfo connectioninfo_rec;
	EzMCommDrvr *thmsg = ( EzMCommDrvr *) threadMessage;
	struct timeval now;
	struct timespec timeout;
	pthread_cond_t EventCond;
	pthread_mutex_t EventMutex;

	pthread_cond_init( &EventCond, NULL );
	pthread_mutex_init( &EventMutex, NULL );

	thmsg->trace( "Inside Reader Thread...." );

	while( 1 )
	{
		memset( &connectioninfo_rec, 0, sizeof( struct EzMCommConnInfo ) );
		retval = thmsg->readConnectionMemoryFrmConnectionThread( pthread_self(), &connectioninfo_rec );
		if( retval < 0 )
		{
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 1;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
			continue;
		}
		break;
	}

	thmsg->trace( "Tcpip Read Thread Created with Id[%d] for ConnectionId[%d] IpAddress[%s]", pthread_self(), connectioninfo_rec.ConnectionId, connectioninfo_rec.IpAddress );

	while( 1 )
	{
		if( thmsg->updateConnectionTime( pthread_self() ) < 0 )
			thmsg->trace( "Error in Updating ConnectionTime for ConnectionThread[%d]", pthread_self() );
		thmsg->trace( "Reader Thread with Id[%d] Waiting for Message From Socket from ConnectionId[%d] with IpAddress[%s]", pthread_self(), connectioninfo_rec.ConnectionId, connectioninfo_rec.IpAddress );
		memset( tcpipheader, 0, sizeof( tcpipheader ) );
		if( recv( connectioninfo_rec.ConnectionId, tcpipheader, thmsg->drvrconfig.headerlen, 0 ) <= 0 )
		{
			thmsg->trace( DEBUG_ERROR, "Error while Reading Header From Socket ErrNo[%d] SysErr[%s] with ConnectionId[%d]", errno, strerror( errno ), connectioninfo_rec.ConnectionId );
			break;
		}

		thmsg->hex_dump( ( unsigned char * ) tcpipheader, thmsg->drvrconfig.headerlen );

		if( thmsg->drvrconfig.headertype == ASCII )
			MsgSize = atoi( tcpipheader );
		else if( thmsg->drvrconfig.headertype == HEX )
		{
			memcpy( &MsgSize, tcpipheader, thmsg->drvrconfig.headerlen );
			MsgSize = ntohs( MsgSize );
		}

		thmsg->trace( "[%d] bytes available on socket", MsgSize );

		memset( tcpipmsg, 0, sizeof( tcpipmsg ) );
		if( recv( connectioninfo_rec.ConnectionId, tcpipmsg, MsgSize, 0 ) <= 0 )
		{
			thmsg->trace( DEBUG_ERROR, "Error while Reading Message From Socket ErrNo[%d] SysErr[%s] with ConnectionId[%d]", errno, strerror( errno ), connectioninfo_rec.ConnectionId );
			break;
		}

		if( thmsg->DebugFlag )
			thmsg->hex_dump( ( unsigned char * ) tcpipmsg, MsgSize );

		memset( finaltcpipmsg, 0, sizeof( finaltcpipmsg ) );
		memcpy( finaltcpipmsg, connectioninfo_rec.RefNum, strlen( connectioninfo_rec.RefNum ) );
		finaltcpipmsg[ strlen( connectioninfo_rec.RefNum ) ] = 0x1c;
		memcpy( finaltcpipmsg + strlen( connectioninfo_rec.RefNum ) + 1, tcpipmsg, MsgSize );
		MsgSize = MsgSize + strlen( connectioninfo_rec.RefNum ) + 1;

		thmsg->trace( "Posting Message to Channel[%s]", thmsg->drvrconfig.destchannel );
		if( thmsg->WriteChannel( thmsg->drvrconfig.destchannel, ( char * )finaltcpipmsg, MsgSize ) < 0 )
		{
			thmsg->trace( "Error in Posting Message to Channel[%s]", thmsg->drvrconfig.destchannel );
			break;
		}
	}
	thmsg->trace( "Closing ConnectionId[%d] with ThreadId[%d]", connectioninfo_rec.ConnectionId, pthread_self() );
	close( connectioninfo_rec.ConnectionId );
	thmsg->trace( "Cancelling TimeoutThread[%d]", connectioninfo_rec.TimeOutThread );
	pthread_cancel( connectioninfo_rec.TimeOutThread );
	thmsg->trace( "Removing ConnectionId[%d]", connectioninfo_rec.ConnectionId );
	thmsg->removeConnectionMemory( connectioninfo_rec.ConnectionId );
}

void* tcpip_timeout_routine( void *threadMessage )
{
	int retval;
	char difftimestr[ 20 ];
	time_t curr_time;
	struct EzMCommConnInfo connectioninfo_rec;
	EzMCommDrvr *thmsg = ( EzMCommDrvr *) threadMessage;
	struct timeval now;
	struct timespec timeout;
	pthread_cond_t EventCond;
	pthread_mutex_t EventMutex;

	pthread_cond_init( &EventCond, NULL );
	pthread_mutex_init( &EventMutex, NULL );

	thmsg->trace( "Inside Writer Thread...." );

	while( 1 )
	{
		memset( &connectioninfo_rec, 0, sizeof( struct EzMCommConnInfo ) );
		retval = thmsg->readConnectionMemoryFrmTimeoutThread( pthread_self(), &connectioninfo_rec );
		if( retval < 0 )
		{
			gettimeofday( &now, NULL );
			timeout.tv_sec = now.tv_sec + 1;
			timeout.tv_nsec = now.tv_usec * 1000;
			pthread_mutex_lock( &EventMutex );
			pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
			pthread_mutex_unlock( &EventMutex );
			continue;
		}
		break;
	}

	while( 1 )
	{
		memset( &connectioninfo_rec, 0, sizeof( struct EzMCommConnInfo ) );
		retval = thmsg->readConnectionMemoryFrmTimeoutThread( pthread_self(), &connectioninfo_rec );
		if( retval < 0 )
			break;
		else
		{
			curr_time = time( NULL );
			memset( difftimestr, 0, sizeof( difftimestr ) );
			sprintf( difftimestr, "%f", difftime( curr_time, connectioninfo_rec.ConnectionTime ) );
			if( atoi( difftimestr ) > thmsg->ConnectionTimeOut )
			{
				close( connectioninfo_rec.ConnectionId );
				pthread_cancel( connectioninfo_rec.ConnectionThread );
				thmsg->removeConnectionMemory( connectioninfo_rec.ConnectionId );
				break;
			}
			else
			{
				gettimeofday( &now, NULL );
				timeout.tv_sec = now.tv_sec + thmsg->ConnectionTimeOut - atoi( difftimestr );
				timeout.tv_nsec = now.tv_usec * 1000;
				pthread_mutex_lock( &EventMutex );
				pthread_cond_timedwait( &EventCond, &EventMutex, &timeout );
				pthread_mutex_unlock( &EventMutex );
			}
		}
	}
}

int EzMCommDrvr :: init( const char *DriverName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( this->DriverName, 0, sizeof( this->DriverName ) );
	strcpy( this->DriverName, DriverName );

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", DriverName );
	if( openDebug( logpath, DriverName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^%s Started^^^^^^^^^^^^^", DriverName );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzTaskUtil");
		trace( DEBUG_ERROR,"^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", DriverName );
		closeDebug();
		exit( 0 );
	}

	trace( DEBUG_TEST, "Loading Configuration for %s ....", DriverName );

	memset( &drvrconfig, 0, sizeof( drvrconfig ) );
	if( LoadDriverConfig( DriverName, &drvrconfig ) < 0 )
	{
		trace( "Error in loading configuration for Driver[%s]", DriverName );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", DriverName );
		closeDebug();
		TaskExit();
	}

	trace( "[%s] initialized with following parameters", DriverName );
	trace( "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	trace( "PortNo[%d]", drvrconfig.portno );
	trace( "HeaderLength[%d]", drvrconfig.headerlen );
	if( drvrconfig.headertype == ASCII )
		trace( "HeaderType[Ascii]");
	else
		trace( "HeaderType[Hex]");
	trace( "NConnections[%d]", drvrconfig.nconnections );
	trace( "DestinationChannelName[%s]", drvrconfig.destchannel );
	trace( "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( " Error in Initializing EzChannelUtil for Driver[%s]", DriverName );
		trace( "~~~~~~~~~~~~~~~~~~%s Driver Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", DriverName );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( DriverName, DriverName ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating [%s] Channel", DriverName );
		trace( DEBUG_ERROR,"^^^^^^^^^^^[%s] Ended Abnormally^^^^^^^^^^^^^", DriverName );
		closeDebug();
		TaskExit();
	}

	if( CreateConnectionMemory() < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating Connection Memory for Driver[%s]", DriverName );
		trace( DEBUG_ERROR,"^^^^^^^^^^^[%s] Ended Abnormally^^^^^^^^^^^^^", DriverName );
		closeDebug();
		TaskExit();
	}

	initEzTCPIPUtil( this, drvrconfig );

	pthread_attr_t thr_attr;
	pthread_attr_init( &thr_attr );
	pthread_attr_setdetachstate( &thr_attr, 1 );

	if( pthread_create( &tcpipWriteThread, &thr_attr, tcpip_write_routine, this ) != 0 )
	{
		trace( "Error in Creating tcpip Writer Thread....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		trace( DEBUG_ERROR,"^^^^^^^^^^^[%s] Ended Abnormally^^^^^^^^^^^^^", DriverName );
		closeDebug();
		TaskExit();
	}

	trace( "Writer Thread Created Successfully...." );

	ConnectionSeqNo = 1;

	TaskInit();
	initEzSigUtil( this );

	return 1;
}

int EzMCommDrvr :: CreateConnectionMemory()
{
	if( IsTaskRunning( DriverName ) >= 0 )
	{
		ConnectionInfoMemoryId = LocateMemoryId( this, DriverName );

		if( ConnectionInfoMemoryId < 0 )
		{
			trace( DEBUG_ERROR, "Error in Locating Memory[%s]", DriverName );
			return -1;
		}

		ConnectionInfoShmid = shmget( ( key_t ) ConnectionInfoMemoryId, 0, IPC_CREAT | 0666 );

		if( ConnectionInfoShmid < 0 )
		{
			trace( "Error in Getting EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		MCommConnInfoShmPtr = ( struct EzMCommConnInfo * ) shmat( ConnectionInfoShmid, 0, 0 );

		if( MCommConnInfoShmPtr == NULL )
		{
			trace( "Error in attaching EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		ConnectionInfoSemid = semget ( ( key_t ) ConnectionInfoMemoryId, 0, IPC_CREAT | 0666 );
		if( ConnectionInfoSemid < 0 )
		{
			trace( "Error in Creating EzMCommConnInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		trace( DEBUG_TEST, "EzMCommConnInfo Semaphore Created with SemId[%d]", ConnectionInfoSemid );
	}
	else
	{
		ConnectionInfoMemoryId = CreateMemoryId( this, DriverName );

		if( ConnectionInfoMemoryId < 0 )
		{
			trace( DEBUG_ERROR, "Error in Creating Memory[%s]", DriverName );
			return -1;
		}

		trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", DriverName, ConnectionInfoMemoryId );


		ConnectionInfoShmid = shmget( ( key_t ) ConnectionInfoMemoryId, sizeof( struct EzMCommConnInfo ) * drvrconfig.nconnections, IPC_CREAT | 0666 );

		if( ConnectionInfoShmid < 0 )
		{
			trace( "Error in Creating EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		MCommConnInfoShmPtr = ( struct EzMCommConnInfo * ) shmat( ConnectionInfoShmid, 0, 0 );

		if( MCommConnInfoShmPtr == NULL )
		{
			trace( "Error in attaching EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		for( int i = 0; i < drvrconfig.nconnections; i++ )
		{
			memset( ( MCommConnInfoShmPtr + i ), 0, sizeof( struct EzMCommConnInfo ) );
			( MCommConnInfoShmPtr + i )->ConnectionId = CONNECTIONID_INIT_VAL ;
		}

		ConnectionInfoSemid = semget ( ( key_t ) ConnectionInfoMemoryId, drvrconfig.nconnections, IPC_CREAT | 0666 );
		if( ConnectionInfoSemid < 0 )
		{
			trace( "Error in Creating EzMCommConnInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		trace( DEBUG_TEST, "EzMCommConnInfo Semaphore Created with SemId[%d]", ConnectionInfoSemid );

		union semun
		{
			int val;
			struct semid_ds *buf;
			unsigned short *array;
		};

		union semun arg;
		arg.val = 2;

		for( int i = 0; i < drvrconfig.nconnections; i++ )
		{
			if( semctl( ConnectionInfoSemid, i, SETVAL, arg ) < 0 )
			{
				trace( "Error in Setting EzMCommConnInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
	}
	return 1;
}

int EzMCommDrvr :: addConnectionMemory( struct EzMCommConnInfo connectioninfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( ( MCommConnInfoShmPtr + i )->ConnectionId == CONNECTIONID_INIT_VAL )
		{
			memcpy( MCommConnInfoShmPtr + i, &connectioninfo_rec, sizeof( struct EzMCommConnInfo ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: ListConnectionMemory()
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: removeConnectionMemory( int ConnectionId )
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( ConnectionId == ( MCommConnInfoShmPtr + i )->ConnectionId )
		{
			( MCommConnInfoShmPtr + i )->ConnectionId = CONNECTIONID_INIT_VAL;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: getConnectionId( const char *RefNum, struct EzMCommConnInfo *connectioninfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( !strcmp( ( MCommConnInfoShmPtr + i )->RefNum, RefNum ) )
		{
			memcpy( connectioninfo_rec, MCommConnInfoShmPtr + i, sizeof( struct EzMCommConnInfo ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: readConnectionMemory( int ConnectionId, struct EzMCommConnInfo *connectioninfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( ConnectionId == ( MCommConnInfoShmPtr + i )->ConnectionId )
		{
			memcpy( connectioninfo_rec, MCommConnInfoShmPtr + i, sizeof( struct EzMCommConnInfo ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: readConnectionMemoryFrmTimeoutThread( pthread_t TimeOutThread, struct EzMCommConnInfo *connectioninfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( TimeOutThread == ( MCommConnInfoShmPtr + i )->TimeOutThread )
		{
			memcpy( connectioninfo_rec, MCommConnInfoShmPtr + i, sizeof( struct EzMCommConnInfo ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: readConnectionMemoryFrmConnectionThread( pthread_t ConnectionThread, struct EzMCommConnInfo *connectioninfo_rec )
{
	struct sembuf sem_buf;
	int retval = -1;

	trace( "inside read connection memory..." );
	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( ConnectionThread == ( MCommConnInfoShmPtr + i )->ConnectionThread && ( MCommConnInfoShmPtr + i )->ConnectionId != CONNECTIONID_INIT_VAL )
		{
			memcpy( connectioninfo_rec, MCommConnInfoShmPtr + i, sizeof( struct EzMCommConnInfo ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}

int EzMCommDrvr :: updateConnectionTime( pthread_t ConnectionThread )
{
	struct sembuf sem_buf;
	int retval = -1;

	pthread_mutex_lock( &ConnectionMutex );
	for( int i = 0; i < drvrconfig.nconnections; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
		if( ConnectionThread == ( MCommConnInfoShmPtr + i )->ConnectionThread )
		{
			( MCommConnInfoShmPtr + i )->ConnectionTime = time( NULL );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				pthread_mutex_unlock( &ConnectionMutex );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ConnectionInfoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			pthread_mutex_unlock( &ConnectionMutex );
			return -1;
		}
	}
	pthread_mutex_unlock( &ConnectionMutex );
	return retval;
}


bool EzMCommDrvr :: IsInteger( const char *InputVal )
{
	for( int i = 0; i < strlen( InputVal ); i++ )
	{
		if( ( InputVal[ i ] < 48 ) && ( InputVal[ i ] > 57 ) )
			return false;
	}
	return true;
}

int EzMCommDrvr :: LoadDriverConfig( const char *DriverName, struct ezcommdrvrconfig *drvrconfig )
{
	EzCfgUtil cfgobj;
	char cfgVal[ CFG_VAL_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], InputString[ INPUT_STRING_SIZE + 1 ];
	int retval;

	strcpy( drvrconfig->drivername, DriverName );
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezmnet.cfg" );

	if( cfgobj.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	drvrconfig->protocol = TCPIP;
	drvrconfig->apptype = TCPIP_SERVER;

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#PortNo", DriverName );
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

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#NConnections", DriverName );
	memset( cfgVal, 0, sizeof( cfgVal ) );
	retval = cfgobj.cfg_search( InputString, cfgVal, 2 );
	if( retval < 0 )
	{
		trace( "Error in Fetching[%s] from file [%s]", InputString, cfgpath );
		cfgobj.cfg_close();
		return -1;
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
	sprintf( InputString, "%s#EnableKeepalive", DriverName );
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

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#HeaderLen", DriverName );
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
	sprintf( InputString, "%s#HeaderType", DriverName );
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
	drvrconfig->enableping = false;

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#DestChannel", DriverName );
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
	sprintf( InputString, "%s#DebugFlag", DriverName );
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

	memset( InputString, 0, sizeof( InputString ) );
	sprintf( InputString, "%s#ConnectionTimeOut", DriverName );
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
		trace( "Invalid ConnectionTimeOut[%s] in File[%s]", cfgVal, cfgpath );
		cfgobj.cfg_close();
		return -1;
	}

	ConnectionTimeOut = atoi( cfgVal );

	cfgobj.cfg_close();
	return 1;
}

void EzMCommDrvr :: genConnectionRefNum( struct EzMCommConnInfo connectioninfo, char *RefNum )
{
	if( ConnectionSeqNo == 99999 )
		ConnectionSeqNo = 1;
	else
		ConnectionSeqNo++;
	sprintf( RefNum, "%06d_%06d_%05d_%s_%d", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime(), ConnectionSeqNo, connectioninfo.IpAddress, connectioninfo.ConnectionId );
	trace( "Generated RefNum[%s]", RefNum );
}

void EzMCommDrvr :: startDriver()
{
	int ConnectionId;
	struct EzMCommConnInfo connectioninfo;

	while( 1 )
	{
		if( createSocket() < 0 )
		{
			trace( "Error in Creating Socket for Driver[%s]...", DriverName );
			sleep( 5 );
			continue;
		}
		break;
	}

	while( 1 )
	{
		trace( "<%s> Listening at PortNo[%d]....", DriverName, drvrconfig.portno );
		ConnectionId = waitForConnection();
		if( ConnectionId < 0 )
			continue;
		trace( "Got New Connection from IpAddress[%s] with ConnectionId[%d]", getConnectionIpAddress(), ConnectionId );

		pthread_t tcpipReadThread;
		pthread_t tcpipTimeOutThread;
		pthread_attr_t thr_attr;
		pthread_attr_init( &thr_attr );
		pthread_attr_setdetachstate( &thr_attr, 1 );

		if( pthread_create( &tcpipReadThread, &thr_attr, tcpip_read_routine, this ) != 0 )
		{
			trace( "Error in Creating Read Thread for IpAddress[%s] with ConnectionId[%d]...SysErr[%s] ErrNo[%d]", getConnectionIpAddress(), ConnectionId, strerror( errno ), errno );
			closeConnectionSocket( ConnectionId );
			continue;
		}

		trace( "Read Thread Successfully Created....with ThreadId[%d]",  tcpipReadThread );

		if( pthread_create( &tcpipTimeOutThread, &thr_attr, tcpip_timeout_routine, this ) != 0 )
		{
			trace( "Error in Creating Timeout Thread for IpAddress[%s] with ConnectionId[%d]...SysErr[%s] ErrNo[%d]", getConnectionIpAddress(), ConnectionId, strerror( errno ), errno );
			closeConnectionSocket( ConnectionId );
			continue;
		}

		trace( "TimeOut Thread Successfully Created....with ThreadId[%d]",  tcpipTimeOutThread );

		memset( &connectioninfo, 0, sizeof( struct EzMCommConnInfo ) );
		connectioninfo.ConnectionId = ConnectionId;
		connectioninfo.ConnectionThread = tcpipReadThread;
		connectioninfo.TimeOutThread = tcpipTimeOutThread;
		memset( connectioninfo.IpAddress, 0, sizeof( connectioninfo.IpAddress ) );
		strcpy( connectioninfo.IpAddress, getConnectionIpAddress() );
		memset( connectioninfo.RefNum, 0, sizeof( connectioninfo.RefNum ) );
		genConnectionRefNum( connectioninfo, connectioninfo.RefNum );
		connectioninfo.ConnectionTime = time( NULL );
		//ListConnectionMemory();
		if( addConnectionMemory( connectioninfo ) < 0 )
		{
			trace( "Error in Adding New Connection with IpAddress[%s] and ConnectionId[%s]", connectioninfo.IpAddress, connectioninfo.ConnectionId );
			pthread_cancel( tcpipReadThread );
			closeConnectionSocket( ConnectionId );
			continue;
		}
		//ListConnectionMemory();
		trace( "Added ConnectionId[%d] ConnectionThread[%d] TimeOutThread[%d] IpAddress[%s] RefNum[%s] to Connection Memory...", connectioninfo.ConnectionId, connectioninfo.ConnectionThread, connectioninfo.TimeOutThread, connectioninfo.IpAddress, connectioninfo.RefNum );
	}
}

int main( int argc, char **argv )
{
	EzMCommDrvr ezmcommdrvr;
	ezmcommdrvr.init( argv[ 0 ] );
	ezmcommdrvr.startDriver();
	return 1;
}



