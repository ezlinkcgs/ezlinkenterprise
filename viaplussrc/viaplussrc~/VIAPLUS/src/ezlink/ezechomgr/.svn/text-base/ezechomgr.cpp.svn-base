#include <ezlink/ezechomgr.h>

void EzEchoMgr :: initEchoMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezechomgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "EzEchoMgr alreading running" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzEchoMgrUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzEchoMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating EzEchoMgrChannel" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( InitEzCommUtil( this ) < 0 )
	{
		trace( "Error in initializing EzCommUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initNetworkUtil( this ) < 0 )
	{
		trace( "Error in initializing NetworkUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initEchoUtil( this ) < 0 )
	{
		trace( "Error in initializing EchoUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initEchoMgrUtil( this ) < 0 )
	{
		trace( "Error in initializing EchoMgrUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in initializing DBUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	initNetworks();
	initEchoThreads();

	if( startNetworkStatusThread() < 0 )
	{
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBClose() < 0 )
	{
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ECHO#CONCURRENTECHO", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ECHO#CONCURRENTECHO from file[%s]..Setting Default as 50", cfgpath );
		ConcurrentEchoCount = 50;
	}
	else
		ConcurrentEchoCount = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ECHO#CONCURRENTECHOINTERVAL", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ECHO#CONCURRENTECHOINTERVAL from file[%s]..Setting Default as 1 second", cfgpath );
		ConcurrentEchoInterval = 1;
	}
	else
		ConcurrentEchoInterval = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ECHO#NTWKPROBEINTERVAL", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ECHO#NTWKPROBEINTERVAL from file[%s]..Setting Default as 3 seconds", cfgpath );
		NetworkProbeInterval = 3;
	}
	else
		NetworkProbeInterval = atoi( cfgval );

	cfgutil.cfg_close();

	trace( DEBUG_NORMAL, "ConcurrentEchoCount[%d] ConcurrentEchoInterval[%d] NetworkProbeInterval[%d]", ConcurrentEchoCount, ConcurrentEchoInterval, NetworkProbeInterval );

	TaskInit();
	initEzSigUtil( this );
}

void *serviceNetworkStatusThread( void *threadmsg )
{
	EzEchoMgr *thmsg;
	struct timeval now;
	struct timespec timeout;
	char NetworkId[ 17 ], NetworkPort[ 33 ];
	int NetworkStatus, NetworkCount, retval;
	bool PortFlag;

	pthread_cond_t EchoEventCond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t EchoEventMutex = PTHREAD_MUTEX_INITIALIZER;

	thmsg = ( EzEchoMgr * ) threadmsg;

	while( 1 )
	{
		gettimeofday( &now, NULL );
		timeout.tv_sec = now.tv_sec + thmsg->NetworkProbeInterval;
		timeout.tv_nsec = now.tv_usec * 1000;
		pthread_mutex_lock( &EchoEventMutex );
		pthread_cond_timedwait( &EchoEventCond, &EchoEventMutex, &timeout );
		pthread_mutex_unlock( &EchoEventMutex );

		pthread_mutex_lock( &NetworkTableMutex );
		NetworkCount = thmsg->getCurrentNetworkCount();
		pthread_mutex_unlock( &NetworkTableMutex );

		for( int i = 0; i < NetworkCount; i++ )
		{
			pthread_mutex_lock( &NetworkTableMutex );
			memset( NetworkId, 0, sizeof( NetworkId ) );
			retval = thmsg->readNetworkId( i + 1, NetworkId );
			if( retval < 0 )
			{
				pthread_mutex_unlock( &NetworkTableMutex );
				continue;
			}
			retval = thmsg->readNetworkMemory( NetworkId );
			if( retval >= 0 )
			{
				NetworkStatus = thmsg->getNetworkStatus();
				memset( NetworkPort, 0, sizeof( NetworkPort ) );
				thmsg->getNetworkPortName( NetworkPort );
			}
			pthread_mutex_unlock( &NetworkTableMutex );

			pthread_mutex_lock( &NetworkTableMutex );
			PortFlag = thmsg->IsPortUp( NetworkPort );
			pthread_mutex_unlock( &NetworkTableMutex );

			if( !PortFlag )
			{
				if( NetworkStatus == NETWORK_STATUS_UP )
				{
					pthread_mutex_lock( &NetworkTableMutex );
					thmsg->setNetworkStatus( NetworkId, NETWORK_STATUS_DOWN );
					pthread_mutex_unlock( &NetworkTableMutex );
				}
			}
		}
	}
	return ( void * )1;
}

void* serviceEchoThread( void *threadmsg )
{
	EzEchoMgr *thmsg;
	struct timeval now;
	struct timespec timeout;
	struct EzEchoPropertyTable echopropertytable_rec;
	struct EzEchoTable echotable_rec;
	int retval;
	char NetworkChannel[ 33 ], NetworkPort[ 33 ];
	struct EzTxnMsg txnmsg;
	int NetworkStatus, NetworkCount = 0, EchoSendCount = 0;
	EzDateTimeUtil ezdatetimeutil;
	bool PortFlag;
	int TraceNo = 1;

	thmsg = ( EzEchoMgr * ) threadmsg;

	pthread_cond_t EchoEventCond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t EchoEventMutex = PTHREAD_MUTEX_INITIALIZER;

	while( 1 )
	{
		gettimeofday( &now, NULL );
		timeout.tv_sec = now.tv_sec + 1;
		timeout.tv_nsec = now.tv_usec * 1000;
		pthread_mutex_lock( &EchoEventMutex );
		pthread_cond_timedwait( &EchoEventCond, &EchoEventMutex, &timeout );
		pthread_mutex_unlock( &EchoEventMutex );
		memset( &echopropertytable_rec, 0, sizeof( struct EzEchoPropertyTable ) );
		retval = thmsg->searchEchoPropertyTable( pthread_self(), &echopropertytable_rec );
		if( retval < 0 )
			continue;
		else
			break;
	}

	if( !strcmp( echopropertytable_rec.EchoPropertyId, ECHOPROPERTY_INIT_VAL ) )
	{
		thmsg->removeEchoPropertyTable( pthread_self() );
		pthread_exit( 0 );
	}

	thmsg->trace( DEBUG_NORMAL, "Echo Thread with Id[%d] Started for EchoPropertyId[%s]", pthread_self(), echopropertytable_rec.EchoPropertyId );

	while( 1 )
	{
		memset( &echopropertytable_rec, 0, sizeof( struct EzEchoPropertyTable ) );
		retval = thmsg->searchEchoPropertyTable( pthread_self(), &echopropertytable_rec );

		if( !strcmp( echopropertytable_rec.EchoPropertyId, ECHOPROPERTY_INIT_VAL ) )
			break;

		NetworkCount = thmsg->getNetworkCount( echopropertytable_rec.EchoPropertyId );

		EchoSendCount = 0;

		for( int i = 0; i < NetworkCount; i++ )
		{
			if( TraceNo >= 900000 )
				TraceNo = 1;

			memset( &echotable_rec, 0, sizeof( EzEchoTable ) );
			retval = thmsg->searchEchoTable( echopropertytable_rec.EchoPropertyId, i + 1, &echotable_rec );
			if( retval < 0 )
				continue;

			thmsg->trace( DEBUG_TEST," NetworkId[ %s ] EchoPropertyId[%s] ThreadFlag [ %d ] EchoProperty[ %c ] LogOnReq[ %c ] Status [ %d ] EchoRespStatus[%c]", echotable_rec.NetworkId, echotable_rec.EchoPropertyId, echopropertytable_rec.ThreadFlag, echotable_rec.EchoProperty, echotable_rec.LogOnReq, echotable_rec.Status, echotable_rec.EchoRespStatus );

			if( echotable_rec.Status != ECHO_THREAD_RUNNING )
				continue;

			pthread_mutex_lock( &NetworkTableMutex );
			retval = thmsg->readNetworkMemory( echotable_rec.NetworkId );
			if( retval >= 0 )
			{
				NetworkStatus = thmsg->getNetworkStatus();
				memset( NetworkChannel, 0, sizeof( NetworkChannel ) );
				thmsg->getNetworkChannelName( NetworkChannel );
				memset( NetworkPort, 0, sizeof( NetworkPort ) );
				thmsg->getNetworkPortName( NetworkPort );
			}
			pthread_mutex_unlock( &NetworkTableMutex );
			if( retval < 0 )
			{
				thmsg->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from NetworkMemory Table", echotable_rec.NetworkId );
				continue;
			}

			if( echotable_rec.EchoRespStatus == ECHO_RESP_STATUS_LOGON_SENT || echotable_rec.EchoRespStatus == ECHO_RESP_STATUS_SIGNON_SENT )
			{
				if( NetworkStatus == NETWORK_STATUS_UP )
				{
					pthread_mutex_lock( &NetworkTableMutex );
					thmsg->setNetworkStatus( echotable_rec.NetworkId, NETWORK_STATUS_DOWN );
					pthread_mutex_unlock( &NetworkTableMutex );
					NetworkStatus = NETWORK_STATUS_DOWN;
				}
			}

			if( echotable_rec.LogOnReq == 'y' || echotable_rec.LogOnReq == 'Y' )
			{
				pthread_mutex_lock( &NetworkTableMutex );
				PortFlag = thmsg->IsPortUp( NetworkPort );
				pthread_mutex_unlock( &NetworkTableMutex );

				if( NetworkStatus == NETWORK_STATUS_DOWN && PortFlag )
				{
					thmsg->trace( DEBUG_TEST,"NetworkId[ %s ] is down...Sending LogonReq", echotable_rec.NetworkId );
					memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
					txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
					txnmsg.LocalDate = ezdatetimeutil.getSysDate();
					txnmsg.LocalTime = ezdatetimeutil.getSysTime();
					txnmsg.TranDate = ezdatetimeutil.getSysDate();
					txnmsg.TranTime = ezdatetimeutil.getSysTime();
					strcpy( txnmsg.DestPort, NetworkPort );
					strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
					txnmsg.NetCode = EZLINK_NETCODE_LOGON;
					txnmsg.TraceNo = TraceNo++;

					if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_LOGON_SENT );
					{
						retval = thmsg->updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_LOGON_SENT );
						if( retval < 0 )
							thmsg->trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
					}

					pthread_mutex_lock( &ChannelMutex );
					retval = thmsg->WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
					pthread_mutex_unlock( &ChannelMutex );
					if( retval < 0 )
						thmsg->trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", NetworkChannel, echotable_rec.NetworkId );
					continue;
				}
			}

			if( echotable_rec.EchoProperty == ECHO_SEND_NEVER )
			{
				pthread_mutex_lock( &NetworkTableMutex );
				PortFlag = thmsg->IsPortUp( NetworkPort );
				pthread_mutex_unlock( &NetworkTableMutex );
				if( PortFlag )
				{
					if( NetworkStatus == NETWORK_STATUS_DOWN )
					{
						pthread_mutex_lock( &NetworkTableMutex );
						thmsg->setNetworkStatus( echotable_rec.NetworkId, NETWORK_STATUS_UP );
						pthread_mutex_unlock( &NetworkTableMutex );
					}
				}
				else
				{
					if( NetworkStatus == NETWORK_STATUS_UP )
					{
						pthread_mutex_lock( &NetworkTableMutex );
						thmsg->setNetworkStatus( echotable_rec.NetworkId, NETWORK_STATUS_DOWN );
						pthread_mutex_unlock( &NetworkTableMutex );
					}
				}
			}
			else if( echotable_rec.EchoProperty == ECHO_SEND_ALWAYS )
			{
				if( NetworkStatus == NETWORK_STATUS_UP )
				{
					pthread_mutex_lock( &NetworkTableMutex );
					PortFlag = thmsg->IsPortUp( NetworkPort );
					pthread_mutex_unlock( &NetworkTableMutex );
					if( !PortFlag )
					{
						pthread_mutex_lock( &NetworkTableMutex );
						thmsg->setNetworkStatus( echotable_rec.NetworkId, NETWORK_STATUS_DOWN );
						pthread_mutex_unlock( &NetworkTableMutex );
						continue;
					}

					memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
					strcpy( txnmsg.DestPort, NetworkPort );
					txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
					txnmsg.LocalDate = ezdatetimeutil.getSysDate();
					txnmsg.LocalTime = ezdatetimeutil.getSysTime();
					txnmsg.TranDate = ezdatetimeutil.getSysDate();
					txnmsg.TranTime = ezdatetimeutil.getSysTime();
					strcpy( txnmsg.DestPort, NetworkPort );
					strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
					txnmsg.NetCode = EZLINK_NETCODE_SIGNON;
					txnmsg.TraceNo = TraceNo++;

					if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_SIGNON_SENT );
					{
						retval = thmsg->updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_SIGNON_SENT );
						if( retval < 0 )
							thmsg->trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
					}

					pthread_mutex_lock( &ChannelMutex );
					retval = thmsg->WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
					pthread_mutex_unlock( &ChannelMutex );
					if( retval < 0 )
						thmsg->trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", NetworkChannel, echotable_rec.NetworkId );
					else
					{
						thmsg->trace( DEBUG_NORMAL, "Written composed Echo Message to Channel[%s] for Port[%s] for NetworkId[%s]", NetworkChannel, NetworkPort, echotable_rec.NetworkId );
						EchoSendCount++;
					}
				}
			}
			else if( echotable_rec.EchoProperty == ECHO_SEND_DOWN )
			{
				if( NetworkStatus == NETWORK_STATUS_DOWN )
				{
					thmsg->trace( DEBUG_TEST,"NetworkId[ %s ] is down", echotable_rec.NetworkId );
					memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
					txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
					txnmsg.LocalDate = ezdatetimeutil.getSysDate();
					txnmsg.LocalTime = ezdatetimeutil.getSysTime();
					txnmsg.TranDate = ezdatetimeutil.getSysDate();
					txnmsg.TranTime = ezdatetimeutil.getSysTime();
					strcpy( txnmsg.DestPort, NetworkPort );
					strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
					txnmsg.NetCode = EZLINK_NETCODE_SIGNON;
					txnmsg.TraceNo = TraceNo++;

					if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_SIGNON_SENT );
					{
						retval = thmsg->updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_SIGNON_SENT );
						if( retval < 0 )
							thmsg->trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
					}

					pthread_mutex_lock( &ChannelMutex );
					retval = thmsg->WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
					pthread_mutex_unlock( &ChannelMutex );
					if( retval < 0 )
						thmsg->trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", NetworkChannel, echotable_rec.NetworkId );
					else
					{
						thmsg->trace( DEBUG_NORMAL, "Written composed Echo Message to Channel[%s] for Port[%s] for NetworkId[%s]", NetworkChannel, NetworkPort, echotable_rec.NetworkId );
						EchoSendCount++;
					}
				}
			}
			else if( echotable_rec.EchoProperty == ECHO_SEND_UP )
			{
				if( NetworkStatus == NETWORK_STATUS_UP )
				{
					thmsg->trace( DEBUG_TEST,"NetworkId[ %s ] is Up", echotable_rec.NetworkId );
					memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
					txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
					txnmsg.LocalDate = ezdatetimeutil.getSysDate();
					txnmsg.LocalTime = ezdatetimeutil.getSysTime();
					txnmsg.TranDate = ezdatetimeutil.getSysDate();
					txnmsg.TranTime = ezdatetimeutil.getSysTime();
					strcpy( txnmsg.DestPort, NetworkPort );
					strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
					txnmsg.NetCode = EZLINK_NETCODE_SIGNON;
					txnmsg.TraceNo = TraceNo++;

					if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_SIGNON_SENT );
					{
						retval = thmsg->updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_SIGNON_SENT );
						if( retval < 0 )
							thmsg->trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
					}

					pthread_mutex_lock( &ChannelMutex );
					retval = thmsg->WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
					pthread_mutex_unlock( &ChannelMutex );
					if( retval < 0 )
						thmsg->trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", NetworkChannel, echotable_rec.NetworkId );
					else
					{
						thmsg->trace( DEBUG_NORMAL, "Written composed Echo Message to Channel[%s] for Port[%s] for NetworkId[%s]", NetworkChannel, NetworkPort, echotable_rec.NetworkId );
						EchoSendCount++;
					}
				}
			}
			if( NetworkStatus == NETWORK_STATUS_UP || NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
			{
				/*
				pthread_mutex_lock( &ChannelMutex );
				thmsg->sendReplayIntimation( echotable_rec.NetworkId );
				pthread_mutex_unlock( &ChannelMutex );
				*/
			}

			if( EchoSendCount == thmsg->ConcurrentEchoCount )
			{
				EchoSendCount = 0;
				gettimeofday( &now, NULL );
				timeout.tv_sec = now.tv_sec + thmsg->ConcurrentEchoInterval;
				timeout.tv_nsec = now.tv_usec * 1000;
				pthread_mutex_lock( &EchoEventMutex );
				pthread_cond_timedwait( &EchoEventCond, &EchoEventMutex, &timeout );
				pthread_mutex_unlock( &EchoEventMutex );
			}
		}
		gettimeofday( &now, NULL );
		timeout.tv_sec = now.tv_sec + echopropertytable_rec.EchoInterval;
		timeout.tv_nsec = now.tv_usec * 1000;
		pthread_mutex_lock( &EchoEventMutex );
		pthread_cond_timedwait( &EchoEventCond, &EchoEventMutex, &timeout );
		pthread_mutex_unlock( &EchoEventMutex );
	}
	retval = thmsg->removeEchoPropertyTable( pthread_self() );
	if( retval < 0 )
		thmsg->trace( "Error in removing EchoPropertyTable with Echo ThreadId[%d]", pthread_self() );

	thmsg->trace( DEBUG_NORMAL, "Echo Thread[%d] for exiting", pthread_self(), echotable_rec.NetworkId );
	return ( void * ) 1;
}

int EzEchoMgr :: sendReplayIntimation( const char *NetworkId )
{
	struct EzTxnMsg localtxnmsg;
	memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
	localtxnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
	if( WriteChannel( "EzSafReader", ( char * ) &localtxnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Sending Replay Intimation Message for NetworkId[%s]", NetworkId );
		return -1;
	}
	trace( DEBUG_NORMAL, "Sent Replay Intimation Message for NetworkId[%s]", NetworkId );
	return 1;
}

int EzEchoMgr :: startNetworkStatusThread()
{
	pthread_t NetworkStatusThread;
	pthread_attr_t NetworkStatusThreadAttr;
	pthread_attr_init( &NetworkStatusThreadAttr );
	pthread_attr_setdetachstate( &NetworkStatusThreadAttr, 1 );
	if( pthread_create( &NetworkStatusThread, &NetworkStatusThreadAttr, serviceNetworkStatusThread, ( void * ) this ) != 0 )
	{
		trace( "Error in Creating Network Status Thread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzEchoMgr :: startEchoThread( const char *EchoPropertyId, int EchoInterval )
{
	trace( DEBUG_TEST, "Starting Echo Thread for EchoPropertyId[%s]", EchoPropertyId );

	pthread_t EchoPropertyThread;
	pthread_attr_t EchoPropertyThreadAttr;
	pthread_attr_init( &EchoPropertyThreadAttr );
	pthread_attr_setdetachstate( &EchoPropertyThreadAttr, 1 );
	if( pthread_create( &EchoPropertyThread, &EchoPropertyThreadAttr, serviceEchoThread, ( void * ) this ) != 0 )
	{
		trace( "Error in Creating Echo Thread...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	if( addEchoPropertyTable( EchoPropertyId, EchoPropertyThread, EchoInterval ) < 0 )
	{
		trace( "Error in adding EchoPropertyId[%s] in EchoPropertyTable", EchoPropertyId );
		pthread_cancel( EchoPropertyThread );
		return -1;
	}
	return 1;
}

void EzEchoMgr :: initEchoThreads()
{
	struct EzEchoProperty *ezechoproperty_ptr;
	int SqlErr, EchoPropertyCount;

	EchoPropertyCount = getEzEchoPropertyCount( &SqlErr );

	if( SqlErr != 0 )
	{
		trace( "Error in getting EchoPropertyCount...OraErr[%05d]", SqlErr );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	ezechoproperty_ptr = ( struct EzEchoProperty * ) malloc( sizeof( struct EzEchoProperty ) * EchoPropertyCount );
	memset( ezechoproperty_ptr, 0, sizeof( struct EzEchoProperty ) * EchoPropertyCount );

	if( LoadEzEchoProperty( ezechoproperty_ptr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzEchoProperty Table...OraErr[%05d]", SqlErr );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		free( ezechoproperty_ptr );
		TaskExit();
	}

	for( int i = 0; i < EchoPropertyCount; i++ )
		startEchoThread( ( ezechoproperty_ptr + i )->EchoPropertyId, ( ezechoproperty_ptr + i )->EchoInterval );

	free( ezechoproperty_ptr );
}


void EzEchoMgr :: initNetworks()
{
	struct EzNetworkEcho *eznetworkecho_ptr;
	int SqlErr, NetworkCount;

	NetworkCount = getEzNetworkEchoCount( &SqlErr );

	if( SqlErr != 0 )
	{
		trace( "Error in getting EzNetworkEcho Count...OraErr[%05d]", SqlErr );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( NetworkCount > getEchoTableMaxNetworks() )
	{
		trace( "No. of Networks configured in EzNetworkEcho [%d] > MaxNetworks[%d]", NetworkCount, getEchoTableMaxNetworks() );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	trace( DEBUG_TEST, "NetworkCount[ %d ]", NetworkCount );

	eznetworkecho_ptr = ( struct EzNetworkEcho * ) malloc( sizeof( struct EzNetworkEcho ) * NetworkCount );
	memset( eznetworkecho_ptr, 0, sizeof( struct EzNetworkEcho ) * NetworkCount );

	if( LoadEzNetworkEcho( eznetworkecho_ptr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzNetworkEcho Table...OraErr[%05d]", SqlErr );
		trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		free( eznetworkecho_ptr );
		TaskExit();
	}

	for( int i = 0; i < NetworkCount; i++ )
	{
		if( updateEchoTable( ( eznetworkecho_ptr + i )->NetworkId, ( eznetworkecho_ptr + i )->EchoPropertyId, ( eznetworkecho_ptr + i )->EchoProperty, ( eznetworkecho_ptr + i )->LogOnReq ) < 0 )
			trace( "Error in adding Network[%s] in EzNetworkEcho Table", ( eznetworkecho_ptr + i )->NetworkId );
	}
	free( eznetworkecho_ptr );
}

void EzEchoMgr :: serviceRequest()
{
	struct EzEchoMgrMsg echomgrmsg;
	struct EzEchoProperty ezechoproperty_rec;
	int MsgSize, retval;

	while( 1 )
	{
		trace( "EchoMgr waiting for servicing request...");
		memset( &echomgrmsg, 0, sizeof( struct EzEchoMgrMsg ) );
		if( ReadMessage( ( char * )&echomgrmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from EzEchoMgr Channel" );
			trace( "^^^^^^^^^^^^^^^EzEchoMgr Ended Abnormally^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
		}
		trace( DEBUG_NORMAL, "Message read from Channel[%s]", GetLastSenderChannelName() );

		switch( echomgrmsg.Command )
		{
			case EZLINK_NTWK_ECHOPROPERTY_ADD:

			trace( DEBUG_NORMAL, "Received Start Echo Request for EchoPropertyId[%s]", echomgrmsg.EchoPropertyId );

			if( dbutil.DBConnect() < 0 )
				break;
			memset( &ezechoproperty_rec, 0, sizeof( struct EzEchoProperty ) );
			retval = readEzEchoProperty( echomgrmsg.EchoPropertyId, &ezechoproperty_rec );
			if( retval != 0 )
			{
				trace( "Error in reading EzEchoProperty table for EchoPropertyId[%s] ..OraErr[%05d]", echomgrmsg.EchoPropertyId, retval );
				break;
			}
			if( dbutil.DBClose() < 0 )
				break;

			startEchoThread( ezechoproperty_rec.EchoPropertyId, ezechoproperty_rec.EchoInterval );
			break;

			case EZLINK_NTWK_ECHOPROPERTY_UPDATE:

			trace( DEBUG_NORMAL, "Received Update Echo Request for EchoPropertyId[%s]", echomgrmsg.EchoPropertyId );
			if( dbutil.DBConnect() < 0 )
				break;
			memset( &ezechoproperty_rec, 0, sizeof( struct EzEchoProperty ) );
			retval = readEzEchoProperty( echomgrmsg.EchoPropertyId, &ezechoproperty_rec );
			if( retval != 0 )
			{
				trace( "Error in reading EzEchoProperty table for EchoPropertyId[%s] ..OraErr[%05d]", echomgrmsg.EchoPropertyId, retval );
				break;
			}
			if( dbutil.DBClose() < 0 )
				break;

			if( updateEchoPropertyTable( ezechoproperty_rec.EchoPropertyId, ezechoproperty_rec.EchoInterval ) < 0 )
				trace( "Error in Updating EchoPropertyId[%s] in EchoPropertyTable", ezechoproperty_rec.EchoPropertyId );
			else
				trace( "Updated EchoPropertyId[%s] in EchoPropertyTable", ezechoproperty_rec.EchoPropertyId );

			break;

			case EZLINK_NTWK_ECHOPROPERTY_REMOVE:
			trace( DEBUG_NORMAL, "Received Remove Echo Request for EchoPropertyId[%s]", echomgrmsg.EchoPropertyId );
			if( removeEchoPropertyTable( echomgrmsg.EchoPropertyId ) < 0 )
				trace( "Error in Removing EchoPropertyId[%s] from EchoProperty Table", echomgrmsg.EchoPropertyId );
			else
				trace( "Removed EchoPropertyId[%s] from EchoProperty Table", echomgrmsg.EchoPropertyId );
			break;

			default:

			trace( DEBUG_NORMAL, "Invalid Echo Request for EchoPropertyId[%s]", echomgrmsg.EchoPropertyId );

			break;
		}

	}
}

int main( int argc, char **argv )
{
	EzEchoMgr ezechomgrobj;
	ezechomgrobj.initEchoMgr( argv[ 0 ] );
	ezechomgrobj.serviceRequest();
	return 1;
}
