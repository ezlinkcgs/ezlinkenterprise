#include <ezlink/ezsafreader.h>

void EzSafReader :: initEzSafReader( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsafreader.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
	    trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
	    closeDebug();
	    TaskExit();
    }
	if( initReplayUtil( this ) < 0 )
	{
		trace( "Error in Initializing ReplayUtil" );
	    trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
	    closeDebug();
	    TaskExit();
	}
	if( CreateChannel( "EzSafReader", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzSafReader" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
	    closeDebug();
	    TaskExit();
	}
	if( initEventUtil( this, "EzSafReader" ) < 0 )
	{
		trace( "Error in Initializing EventUtil" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database....." );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezinstprofileutil.initInstProfile( this ) < 0 )
	{
		trace( "Error in initializing EzInstProfile" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( eztxnrefselectutil.initEzTxnRefSelectUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTxnRefSelectUtil" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezsafformatutil.initSAFFormatUtil( this, &ezinstprofileutil, &ezpadssutil ) < 0 )
	{
		trace( "Error in Initializing EzSAFFormatUtil" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	if( initNetworkUtil( this ) < 0 )
	{
		trace( "Error in Initializing NetworkUtil" );
		trace( "^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^^^");
	    closeDebug();
	    TaskExit();
	}
	DBClose();
	TaskInit();
	initEzSigUtil( this );
}

void EzSafReader :: serviceTimeOut( struct EzTxnMsg *txnmsg_ptr )
{
	struct EzReplayTable replaytable_rec;
	struct EzTxnMsg txnmsg;
	struct EzSafDBInfo safdbinfo;
	char SafRecordNo[ 21 ], TxnRefNum[ 255 ], NetworkChannel[ 33 ], NetworkPort[ 33 ], EventId[ EVENT_KEY_SIZE + 1 ];
	int retval, NetworkStatus, TimeOutCount = 0;

	if( txnmsg_ptr->MerchantType == 6011 )
		trace( DEBUG_TEST, "Txn with CHN[%s] MsgType[%d] TxnCode[%d] TraceNo[%d] RefNum[%s] TxnDate[%d] TxnTime[%d] got TimedOut for NetworkId[%s]", txnmsg_ptr->chn, txnmsg_ptr->MsgType, txnmsg_ptr->TxnCode, txnmsg_ptr->TraceNo, txnmsg_ptr->RefNum, txnmsg_ptr->TranDate, txnmsg_ptr->TranTime, txnmsg_ptr->NetworkId );
	else
		trace( DEBUG_TEST, "Txn with AccountNo[%s] MsgType[%d] TxnCode[%d] TraceNo[%d] RefNum[%s] TxnDate[%d] TxnTime[%d] got TimedOut for NetworkId[%s]", txnmsg_ptr->FromAccount, txnmsg_ptr->MsgType, txnmsg_ptr->TxnCode, txnmsg_ptr->TraceNo, txnmsg_ptr->RefNum, txnmsg_ptr->TranDate, txnmsg_ptr->TranTime, txnmsg_ptr->NetworkId );

	memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
	if( readReplayTable( txnmsg_ptr->NetworkId, &replaytable_rec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkId[%s] from ReplayTable", txnmsg_ptr->NetworkId );
		return;
	}

	if( replaytable_rec.Status != REPLAY_NETWORK_RUNNING )
		return;

	trace( DEBUG_TEST, "Reading NetworkId[%s] from NetworkMemory Table", txnmsg_ptr->NetworkId );
	retval = readNetworkMemory( replaytable_rec.NetworkId );

	if( retval < 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from NetworkMemory Table", txnmsg_ptr->NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
		return;
	}

	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	eztxnrefselectutil.getTxnRefNum( txnmsg_ptr, TxnRefNum );

	retval = readTimeOutCount( txnmsg_ptr->NetworkId, TxnRefNum, &TimeOutCount );
	//trace("readTimeOutCount[%d] --- [%d]", retval, TimeOutCount );
	if( EZLINK_ORA_CONNECT_ERR( retval ) )
	{
		if( DBConnect() < 0 )
		{
			trace( "Error in Connecting with Switch Database...." );
			return;
		}
		else
			retval = readTimeOutCount( txnmsg_ptr->NetworkId, TxnRefNum, &TimeOutCount );
	}

	if( retval != 0 )
	{
		trace( DEBUG_NORMAL, "Error in Reading TimeOutCount for TxnRefNum[%s] for NetworkId[%s]..OraErr[%05d]", TxnRefNum, txnmsg_ptr->NetworkId, retval );
		return;
	}

	if( TimeOutCount >= replaytable_rec.ReplayLookUpInterval )
	{
		retval = updateSafStatus( TxnRefNum, SAF_STATUS_TIMEDOUT, SAF_RESPONSE_RCVD, txnmsg_ptr->RespCode );

		if( EZLINK_ORA_CONNECT_ERR( retval ) )
		{
			if( DBConnect() < 0 )
			{
				trace( "Error in Connecting with Switch Database...." );
				return;
			}
			else
				retval = updateSafStatus( TxnRefNum, SAF_STATUS_TIMEDOUT, SAF_RESPONSE_RCVD, txnmsg_ptr->RespCode );
		}
		if( retval != 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating SAF_STATUS_TIMEDOUT for TxnRefNum[%s] ORAERR[%05d]", TxnRefNum, retval );
			return;
		}
		else
			trace( DEBUG_NORMAL, "Updated SAF_STATUS_TIMEDOUT for TxnRefNum[%s]", TxnRefNum );
	}
	else
	{
		TimeOutCount += 1;
		retval = updateTimeOutCount( txnmsg_ptr->NetworkId, TxnRefNum, TimeOutCount );
		if( EZLINK_ORA_CONNECT_ERR( retval ) )
		{
			if( DBConnect() < 0 )
			{
				trace( "Error in Connecting with Switch Database...." );
				return;
			}
			else
				retval = updateTimeOutCount( txnmsg_ptr->NetworkId, TxnRefNum, TimeOutCount );
		}
		if( retval != 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating TimeOutCount for TxnRefNum[%s] ORAERR[%05d]", TxnRefNum, retval );
			return;
		}
		else
			trace( DEBUG_NORMAL, "Updated TimeOutCount for TxnRefNum[%s] as [%d]", TxnRefNum, TimeOutCount );
	}

	if( replaytable_rec.ReplayAction == REPLAY_TIMEOUT_DOWN && getNetworkStatus() == NETWORK_STATUS_UP )
	{
		trace( DEBUG_NORMAL, "Marking the NetworkId[%s] as Down....", txnmsg_ptr->NetworkId );
		retval = setNetworkStatus( replaytable_rec.NetworkId, NETWORK_STATUS_DOWN );
		if( retval < 0 )
			trace( "Error in Updating NetworkId[%s] Status as Down....",  txnmsg_ptr->NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
	}
	else
	{
		NetworkStatus = getNetworkStatus();
		memset( NetworkChannel, 0, sizeof( NetworkChannel ) );
		getNetworkChannelName( NetworkChannel );
		memset( NetworkPort, 0, sizeof( NetworkPort ) );
		getNetworkPortName( NetworkPort );
		trace( DEBUG_TEST, "Read NetworkId[%s] with NetworkChannel[%s] NetworkPort[%s] NetworkStatus[%d]", txnmsg_ptr->NetworkId, NetworkChannel, NetworkPort, NetworkStatus );

		if( replaytable_rec.ReplayProperty ==  REPLAY_DOWN )
		{
			trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Down...", txnmsg_ptr->NetworkId );
			if( NetworkStatus == NETWORK_STATUS_UP )
			{
				trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
				if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
					trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
				return;
			}
		}
		else if( replaytable_rec.ReplayProperty ==  REPLAY_UP )
		{
			trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Up...", txnmsg_ptr->NetworkId );
			if( NetworkStatus != NETWORK_STATUS_UP &&  NetworkStatus != NETWORK_STATUS_SAFDOWNLOAD )
			{
				trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
				if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
					trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
				return;
			}
		}

		memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
		retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );

		if( EZLINK_ORA_CONNECT_ERR( retval ) )
		{
			if( DBConnect() < 0 )
			{
				trace( "Error in Connecting with Switch Database...." );
				return;
			}
			else
			{
				memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
				retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );
			}
		}

		if( retval == SQL_NO_DATA )
		{
			trace( DEBUG_NORMAL, "No Pending Record for NetworkId[%s] in EzSafDB", txnmsg_ptr->NetworkId );
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
			if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
		}
		else if( retval != 0 )
		{
			trace( "Error in Reading EzSafDB for NetworkId[%s] SqlErr[%05d]", replaytable_rec.NetworkId, retval );
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
			if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
		}
		else
		{
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			ezsafformatutil.decomposeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

			memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
			strcpy( txnmsg.DestPort, NetworkPort );

			if( safdbinfo.SafRepeatIndicator == SAF_REPEAT_DISABLE )
			{
				retval = updateSafRepeatIndicator( txnmsg_ptr->NetworkId, safdbinfo.TxnRefNum, SAF_REPEAT_ENABLE );
				if( EZLINK_ORA_CONNECT_ERR( retval ) )
				{
					if( DBConnect() < 0 )
					{
						trace( "Error in Connecting with Switch Database...." );
						trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, txnmsg_ptr->NetworkId, retval );
					}
					else
					{
						retval = updateSafRepeatIndicator( txnmsg_ptr->NetworkId, safdbinfo.TxnRefNum, SAF_REPEAT_ENABLE );
						if( retval != 0 )
							trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, txnmsg_ptr->NetworkId, retval );
					}
				}
				else if( retval != 0 )
					trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, txnmsg_ptr->NetworkId, retval );
			}
			else
				txnmsg.MsgType = txnmsg.MsgType + 1;

			trace( DEBUG_TEST, "Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, safdbinfo.TxnRefNum );

			retval = WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( EzTxnMsg ) );

			if( retval < 0 )
				trace( DEBUG_ERROR, "Error in Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, safdbinfo.TxnRefNum );
			else
				trace( DEBUG_NORMAL, "Replayed SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, safdbinfo.TxnRefNum );

			if( safdbinfo.SafRepeatIndicator != SAF_REPEAT_DISABLE )
				txnmsg.MsgType = txnmsg.MsgType - 1;

			memset( EventId, 0, sizeof( EventId ) );
			eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );
			if( createEvent( EventId, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ), replaytable_rec.ReplayInterval ) < 0 )
				trace( DEBUG_ERROR, "Error in Creating EventId[%s]", EventId );
			else
				trace( DEBUG_ERROR, "EventId[%s] Created with TimeOut[%d]", EventId, replaytable_rec.ReplayInterval );
		}
	}
}

void EzSafReader :: serviceReplayIntimationRequest( const char *NetworkId  )
{
	struct EzReplayTable replaytable_rec;
	struct EzTxnMsg txnmsg;
	char SafRecordNo[ 21 ], TxnRefNum[ 255 ], NetworkChannel[ 33 ], NetworkPort[ 33 ], EventId[ EVENT_KEY_SIZE + 1 ];
	int retval, NetworkStatus;
	struct EzSafDBInfo safdbinfo;

	trace( DEBUG_NORMAL, "Servicing Replay Intimation Request for NetworkId[%s]", NetworkId );

	memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
	if( readReplayTable( NetworkId, &replaytable_rec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkId[%s] from ReplayTable", NetworkId );
		return;
	}

	if( replaytable_rec.Status != REPLAY_NETWORK_RUNNING )
	{
		trace( DEBUG_NORMAL, "NetworkId[%s] is in Suspended State....", NetworkId );
		return;
	}

	if( replaytable_rec.ReplayFlag == REPLAY_FLAG_ACTIVE )
	{
		trace( DEBUG_ERROR, "Already NetworkId[%s] Record is Replayed and Waiting for Response", NetworkId );
		return;
	}

	trace( DEBUG_TEST, "Reading NetworkId[%s] from NetworkMemory Table", NetworkId );

	retval = readNetworkMemory( replaytable_rec.NetworkId );
	if( retval < 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from NetworkMemory Table", NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", NetworkId );
		if( updateReplayStatusAndReplayFlag( NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", NetworkId );
		return;
	}
	NetworkStatus = getNetworkStatus();
	memset( NetworkChannel, 0, sizeof( NetworkChannel ) );
	getNetworkChannelName( NetworkChannel );
	memset( NetworkPort, 0, sizeof( NetworkPort ) );
	getNetworkPortName( NetworkPort );
	trace( DEBUG_TEST, "Read NetworkId[%s] with NetworkChannel[%s] NetworkPort[%s] NetworkStatus[%d]", NetworkId, NetworkChannel, NetworkPort, NetworkStatus );

	if( replaytable_rec.ReplayProperty ==  REPLAY_DOWN )
	{
		trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Down...", NetworkId );
		if( NetworkStatus != NETWORK_STATUS_DOWN )
		{
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", NetworkId );
			if( updateReplayStatusAndReplayFlag( NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", NetworkId );
			return;
		}
	}
	else if( replaytable_rec.ReplayProperty ==  REPLAY_UP )
	{
		trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Up...", NetworkId );
		if( NetworkStatus != NETWORK_STATUS_UP &&  NetworkStatus != NETWORK_STATUS_SAFDOWNLOAD )
		{
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", NetworkId );
			if( updateReplayStatusAndReplayFlag( NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", NetworkId );
			return;
		}
	}

	memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
	retval = getNextPendingRecord( NetworkId, &safdbinfo );

	if( EZLINK_ORA_CONNECT_ERR( retval ) )
	{
		if( DBConnect() < 0 )
		{
			trace( "Error in Connecting with Switch Database...." );
			return;
		}
		else
		{
			memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
			retval = getNextPendingRecord( NetworkId, &safdbinfo );
		}
	}

	if( retval == SQL_NO_DATA )
	{
		trace( DEBUG_NORMAL, "No Pending Record for NetworkId[%s] in EzSafDB", NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", NetworkId );
		if( updateReplayStatusAndReplayFlag( NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", NetworkId );
	}
	else if( retval != 0 )
	{
		trace( "Error in Reading EzSafDB for NetworkId[%s] SqlErr[%05d]", replaytable_rec.NetworkId, retval );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", NetworkId );
		if( updateReplayStatusAndReplayFlag( NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", NetworkId );
	}
	else
	{
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_ACTIVE REPLAY_FLAG_ACTIVE", NetworkId );
		retval = checkAndUpdateReplayStatusAndReplayFlag( NetworkId, REPLAY_STATUS_ACTIVE, REPLAY_FLAG_ACTIVE );
		if( retval < 0 )
		{
			if( retval == -1 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", NetworkId );
			else
				trace( "Relay Status Flag is Active for NetworkId[%s] and is Waiting for Response.....", NetworkId );
			return;
		}

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		ezsafformatutil.decomposeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

		memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
		strcpy( txnmsg.DestPort, NetworkPort );

		if( safdbinfo.SafRepeatIndicator == SAF_REPEAT_DISABLE )
		{
			retval = updateSafRepeatIndicator( NetworkId, safdbinfo.TxnRefNum, SAF_REPEAT_ENABLE );
			if( EZLINK_ORA_CONNECT_ERR( retval ) )
			{
				if( DBConnect() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, NetworkId, retval );
				}
				else
				{
					retval = updateSafRepeatIndicator( NetworkId, safdbinfo.TxnRefNum, SAF_REPEAT_ENABLE );
					if( retval != 0 )
						trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, NetworkId, retval );
				}
			}
			else if( retval != 0 )
				trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, NetworkId, retval );
		}
		else
			txnmsg.MsgType = txnmsg.MsgType + 1;


		trace( DEBUG_TEST, "Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, safdbinfo.TxnRefNum );

		retval = WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( EzTxnMsg ) );

		if( retval < 0 )
			trace( DEBUG_ERROR, "Error in Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, safdbinfo.TxnRefNum );
		else
			trace( DEBUG_NORMAL, "Replayed SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, safdbinfo.TxnRefNum );

		if( safdbinfo.SafRepeatIndicator != SAF_REPEAT_DISABLE )
			txnmsg.MsgType = txnmsg.MsgType - 1;

		memset( EventId, 0, sizeof( EventId ) );
		eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );
		if( createEvent( EventId, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ), replaytable_rec.ReplayInterval ) < 0 )
			trace( DEBUG_ERROR, "Error in Creating EventId[%s]", EventId );
		else
			trace( DEBUG_ERROR, "EventId[%s] Created with TimeOut[%d]", EventId, replaytable_rec.ReplayInterval );
	}
}

void EzSafReader :: serviceSAFDownloadRequest( struct EzTxnMsg *txnmsg_ptr )
{
	struct EzReplayTable replaytable_rec;
	struct EzTxnMsg txnmsg;
	char SafRecordNo[ 21 ], TxnRefNum[ 255 ], NetworkChannel[ 33 ], NetworkPort[ 33 ], EventId[ EVENT_KEY_SIZE + 1 ];
	int retval, NetworkStatus;
	struct EzSafDBInfo safdbinfo;

	trace( DEBUG_NORMAL, "Servicing SAF Download Request for NetworkId[%s]", txnmsg_ptr->NetworkId );

	memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
	if( readReplayTable( txnmsg_ptr->NetworkId, &replaytable_rec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkId[%s] from ReplayTable", txnmsg_ptr->NetworkId );
		return;
	}

	if( updateReplayMsgIndicator( txnmsg_ptr->NetworkId, REPLAY_MSGTYPEINDICATOR_DOWNLOAD ) < 0 )
		trace( DEBUG_ERROR, "Error in Setting Message Indicator for NetworkId[%s]", txnmsg_ptr->NetworkId );
	else
		trace( DEBUG_ERROR, "Set Message Indicator for NetworkId[%s]", txnmsg_ptr->NetworkId );

	trace( DEBUG_TEST, "Reading NetworkId[%s] from NetworkMemory Table", txnmsg_ptr->NetworkId );
	retval = readNetworkMemory( replaytable_rec.NetworkId );
	if( retval < 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from NetworkMemory Table", txnmsg_ptr->NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
		return;
	}
	NetworkStatus = getNetworkStatus();
	memset( NetworkChannel, 0, sizeof( NetworkChannel ) );
	getNetworkChannelName( NetworkChannel );
	memset( NetworkPort, 0, sizeof( NetworkPort ) );
	getNetworkPortName( NetworkPort );
	trace( DEBUG_TEST, "Read NetworkId[%s] with NetworkChannel[%s] NetworkPort[%s] NetworkStatus[%d]", txnmsg_ptr->NetworkId, NetworkChannel, NetworkPort, NetworkStatus );


	if( setNetworkStatus( txnmsg_ptr->NetworkId, NETWORK_STATUS_SAFDOWNLOAD ) < 0 )
		trace( DEBUG_ERROR, "Error in Setting Network Status for NetworkId[%s]", txnmsg_ptr->NetworkId );
	else
		trace( DEBUG_NORMAL, "Setting Network Status for NetworkId[%s] as SAFDOWNLOAD", txnmsg_ptr->NetworkId );

	if( replaytable_rec.Status != REPLAY_NETWORK_RUNNING )
			return;

	if( replaytable_rec.ReplayFlag == REPLAY_FLAG_ACTIVE )
	{
		trace( DEBUG_ERROR, "Already NetworkId[%s] Record is Replayed and Waiting for Response", txnmsg_ptr->NetworkId );
		return;
	}

	if( replaytable_rec.ReplayProperty ==  REPLAY_DOWN )
	{
		trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Down...", txnmsg_ptr->NetworkId );
		if( NetworkStatus == NETWORK_STATUS_UP )
		{
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
			if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
			return;
		}
	}
	else if( replaytable_rec.ReplayProperty ==  REPLAY_UP )
	{
		trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Up...", txnmsg_ptr->NetworkId );
		if( NetworkStatus != NETWORK_STATUS_UP &&  NetworkStatus != NETWORK_STATUS_SAFDOWNLOAD )
		{
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
			if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
			return;
		}
	}

	memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
	retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );

	if( EZLINK_ORA_CONNECT_ERR( retval ) )
	{
		if( DBConnect() < 0 )
		{
			trace( "Error in Connecting with Switch Database...." );
			return;
		}
		else
		{
			memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
			retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );
		}
	}

	if( retval == SQL_NO_DATA )
	{
		trace( DEBUG_NORMAL, "No Pending Record for NetworkId[%s] in EzSafDB", txnmsg_ptr->NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );

		trace( DEBUG_NORMAL, "Generating SAF Download Response for NetworkId[%s]", txnmsg_ptr->NetworkId );
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		txnmsg.MsgType = EZLINK_TXN_PBFDownloadResponse;
		strcpy( txnmsg.NetworkId, txnmsg_ptr->NetworkId );
		txnmsg.RespCode = EZLINK_RC_Approved;
		strcpy( txnmsg.DestPort, NetworkPort );
		retval = WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( EzTxnMsg ) );
		if( retval < 0 )
			trace( DEBUG_ERROR, "Error in Writing SAF Download Response for NetworkId[%s] to Channel[%s]", txnmsg.NetworkId, NetworkChannel );
		else
			trace( DEBUG_NORMAL, "Written SAF Download Response for NetworkId[%s] to Channel[%s]", txnmsg.NetworkId, NetworkChannel );
		trace( DEBUG_NORMAL, "Changing NetworkId[%s] Status as ONLINE....", txnmsg.NetworkId );
		if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
			trace( DEBUG_ERROR, "Error in Setting Network Status for NetworkId[%s]", txnmsg.NetworkId );
		else
			trace( DEBUG_NORMAL, "Setting Network Status for NetworkId[%s] as ONLINE", txnmsg.NetworkId );
		if( updateReplayMsgIndicator( txnmsg.NetworkId, REPLAY_MSGTYPEINDICATOR_INIT ) < 0 )
			trace( DEBUG_ERROR, "Error in Setting Message Indicator for NetworkId[%s]", txnmsg.NetworkId );
		else
			trace( DEBUG_ERROR, "Set Message Indicator for NetworkId[%s]", txnmsg.NetworkId );

	}
	else if( retval != 0 )
	{
		trace( "Error in Reading EzSafDB for NetworkId[%s] SqlErr[%05d]", replaytable_rec.NetworkId, retval );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
	}
	else
	{
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_ACTIVE REPLAY_FLAG_ACTIVE", txnmsg_ptr->NetworkId );
		retval = checkAndUpdateReplayStatusAndReplayFlag( replaytable_rec.NetworkId, REPLAY_STATUS_ACTIVE, REPLAY_FLAG_ACTIVE );
		if( retval < 0 )
		{
			if( retval == -1 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", replaytable_rec.NetworkId );
			else
				trace( "Relay Status Flag is Active for NetworkId[%s] and is Waiting for Response.....", replaytable_rec.NetworkId );
			return;
		}

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		ezsafformatutil.decomposeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

		memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
		strcpy( txnmsg.DestPort, NetworkPort );

		if( safdbinfo.SafRepeatIndicator == SAF_REPEAT_DISABLE )
		{
			retval = updateSafRepeatIndicator( txnmsg_ptr->NetworkId, safdbinfo.TxnRefNum, SAF_REPEAT_ENABLE );
			if( retval != 0 )
				trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, txnmsg_ptr->NetworkId, retval );
		}
		else
			txnmsg.MsgType = txnmsg.MsgType + 1;

		trace( DEBUG_TEST, "Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, TxnRefNum );

		retval = WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( EzTxnMsg ) );

		if( retval < 0 )
			trace( DEBUG_ERROR, "Error in Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, TxnRefNum );
		else
			trace( DEBUG_NORMAL, "Replayed SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, TxnRefNum );

		if( safdbinfo.SafRepeatIndicator != SAF_REPEAT_DISABLE )
			txnmsg.MsgType = txnmsg.MsgType - 1;

		memset( EventId, 0, sizeof( EventId ) );
		eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );
		if( createEvent( EventId, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ), replaytable_rec.ReplayInterval ) < 0 )
			trace( DEBUG_ERROR, "Error in Creating EventId[%s]", EventId );
		else
			trace( DEBUG_ERROR, "EventId[%s] Created with TimeOut[%d]", EventId, replaytable_rec.ReplayInterval );
	}
}

void EzSafReader :: serviceReplayResponse( struct EzTxnMsg *txnmsg_ptr )
{
	struct EzReplayTable replaytable_rec;
	struct EzTxnMsg txnmsg;
	char SafRecordNo[ 21 ], TxnRefNum[ 255 ], NetworkChannel[ 33 ], NetworkPort[ 33 ], EventId[ EVENT_KEY_SIZE + 1 ];
	int retval, NetworkStatus, MsgSize;
	struct EzSafDBInfo safdbinfo;

	memset( EventId, 0, sizeof( EventId ) );
	txnmsg_ptr->MsgType -= 10;
	eztxnrefselectutil.getTxnRefNum( txnmsg_ptr, EventId );
	txnmsg_ptr->MsgType += 10;
	trace( DEBUG_NORMAL, "Destroying EventId[%s]....", EventId );

	if( destroyEvent( EventId, ( char * )txnmsg_ptr, &MsgSize ) < 0 )
		trace( DEBUG_ERROR, "Error in Destroying EventId[%s]", EventId );
	else
		trace( DEBUG_NORMAL, "Destroyed Event[%s] Successfully", EventId );

	if( updateReplayFlag( txnmsg_ptr->NetworkId, REPLAY_FLAG_IDLE ) < 0 )
		trace( "Error in Updating Replay Flag for NetworkId[%s] as Idle....", txnmsg_ptr->NetworkId );

	memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
	if( readReplayTable( txnmsg_ptr->NetworkId, &replaytable_rec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkId[%s] from ReplayTable", txnmsg_ptr->NetworkId );
		return;
	}

	if( replaytable_rec.Status != REPLAY_NETWORK_RUNNING )
			return;

	trace( DEBUG_TEST, "Reading NetworkId[%s] from NetworkMemory Table", txnmsg_ptr->NetworkId );
	retval = readNetworkMemory( replaytable_rec.NetworkId );
	if( retval < 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from NetworkMemory Table", txnmsg_ptr->NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
		return;
	}
	NetworkStatus = getNetworkStatus();
	memset( NetworkChannel, 0, sizeof( NetworkChannel ) );
	getNetworkChannelName( NetworkChannel );
	memset( NetworkPort, 0, sizeof( NetworkPort ) );
	getNetworkPortName( NetworkPort );
	trace( DEBUG_TEST, "Read NetworkId[%s] with NetworkChannel[%s] NetworkPort[%s] NetworkStatus[%d]", txnmsg_ptr->NetworkId, NetworkChannel, NetworkPort, NetworkStatus );

	if( replaytable_rec.ReplayProperty ==  REPLAY_DOWN )
	{
		trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Down...", txnmsg_ptr->NetworkId );
		if( NetworkStatus == NETWORK_STATUS_UP )
		{
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
			if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
			return;
		}
	}
	else if( replaytable_rec.ReplayProperty ==  REPLAY_UP )
	{
		trace( DEBUG_TEST, "NetworkId[%s] is Configured to Replay when Network is Up...", txnmsg_ptr->NetworkId );
		if( NetworkStatus != NETWORK_STATUS_UP &&  NetworkStatus != NETWORK_STATUS_SAFDOWNLOAD )
		{
			trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
			if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
			return;
		}
	}

	memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
	retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );

	if( EZLINK_ORA_CONNECT_ERR( retval ) )
	{
		if( DBConnect() < 0 )
		{
			trace( "Error in Connecting with Switch Database...." );
			return;
		}
		else
		{
			memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
			retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );
		}
	}

	if( retval == SQL_NO_DATA )
	{
		trace( DEBUG_NORMAL, "No Pending Record for NetworkId[%s] in EzSafDB", txnmsg_ptr->NetworkId );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );

		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );

		if( ( NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD ) && ( replaytable_rec.MsgTypeIndicator == REPLAY_MSGTYPEINDICATOR_DOWNLOAD ) )
		{
			trace( DEBUG_NORMAL, "Generating SAF Download Response for NetworkId[%s]", txnmsg_ptr->NetworkId );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			txnmsg.MsgType = EZLINK_TXN_PBFDownloadResponse;
			strcpy( txnmsg.NetworkId, txnmsg_ptr->NetworkId );
			txnmsg.RespCode = EZLINK_RC_Approved;
			strcpy( txnmsg.DestPort, NetworkPort );
			retval = WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( EzTxnMsg ) );
			if( retval < 0 )
				trace( DEBUG_ERROR, "Error in Writing SAF Download Response for NetworkId[%s] to Channel[%s]", txnmsg.NetworkId, NetworkChannel );
			else
				trace( DEBUG_NORMAL, "Written SAF Download Response for NetworkId[%s] to Channel[%s]", txnmsg.NetworkId, NetworkChannel );
			trace( DEBUG_NORMAL, "Changing NetworkId[%s] Status as ONLINE....", txnmsg.NetworkId );
			if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
				trace( DEBUG_ERROR, "Error in Setting Network Status for NetworkId[%s]", txnmsg.NetworkId );
			else
				trace( DEBUG_NORMAL, "Setting Network Status for NetworkId[%s] as ONLINE", txnmsg.NetworkId );
			if( updateReplayMsgIndicator( txnmsg.NetworkId, REPLAY_MSGTYPEINDICATOR_INIT ) < 0 )
				trace( DEBUG_ERROR, "Error in Setting Message Indicator for NetworkId[%s]", txnmsg.NetworkId );
			else
				trace( DEBUG_ERROR, "Set Message Indicator for NetworkId[%s]", txnmsg.NetworkId );
		}
	}
	else if( retval != 0 )
	{
		trace( "Error in Reading EzSafDB for NetworkId[%s] SqlErr[%05d]", replaytable_rec.NetworkId, retval );
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_IDLE REPLAY_FLAG_IDLE", txnmsg_ptr->NetworkId );
		if( updateReplayStatusAndReplayFlag( txnmsg_ptr->NetworkId, REPLAY_STATUS_IDLE, REPLAY_FLAG_IDLE ) < 0 )
			trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", txnmsg_ptr->NetworkId );
	}
	else
	{
		trace( DEBUG_TEST, "NetworkId[%s]...REPLAY_STATUS_ACTIVE REPLAY_FLAG_ACTIVE", txnmsg_ptr->NetworkId );
		retval = checkAndUpdateReplayStatusAndReplayFlag( replaytable_rec.NetworkId, REPLAY_STATUS_ACTIVE, REPLAY_FLAG_ACTIVE );
		if( retval < 0 )
		{
			if( retval == -1 )
				trace( "Error in Updating Replay Status & Flag for NetworkId[%s]", replaytable_rec.NetworkId );
			else
				trace( "Relay Status Flag is Active for NetworkId[%s] and is Waiting for Response.....", replaytable_rec.NetworkId );
			return;
		}

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		ezsafformatutil.decomposeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

		memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
		strcpy( txnmsg.DestPort, NetworkPort );

		if( safdbinfo.SafRepeatIndicator == SAF_REPEAT_DISABLE )
		{
			retval = updateSafRepeatIndicator( txnmsg_ptr->NetworkId, safdbinfo.TxnRefNum, SAF_REPEAT_ENABLE );
			if( retval != 0 )
				trace( "Error in Updating SafRepeatIndicator for TxnRefNum[%s] NetworkId[%s]...OraErr[%05d]", safdbinfo.TxnRefNum, txnmsg_ptr->NetworkId, retval );
		}
		else
			txnmsg.MsgType = txnmsg.MsgType + 1;

		trace( DEBUG_TEST, "Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, TxnRefNum );

		retval = WriteChannel( NetworkChannel, ( char * )&txnmsg, sizeof( EzTxnMsg ) );

		if( retval < 0 )
			trace( DEBUG_ERROR, "Error in Replaying SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, TxnRefNum );
		else
			trace( DEBUG_NORMAL, "Replayed SafRecordNo[%s] for NetworkId[%s] ChannelName[%s] DestPort[%s] with TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, NetworkChannel, txnmsg.DestPort, TxnRefNum );

		if( safdbinfo.SafRepeatIndicator != SAF_REPEAT_DISABLE )
			txnmsg.MsgType = txnmsg.MsgType - 1;

		trace( "txnmsg.NetCode[%d]", txnmsg.NetCode );

		memset( EventId, 0, sizeof( EventId ) );
		eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );
		if( createEvent( EventId, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ), replaytable_rec.ReplayInterval ) < 0 )
			trace( DEBUG_ERROR, "Error in Creating EventId[%s]", EventId );
		else
			trace( DEBUG_ERROR, "EventId[%s] Created with TimeOut[%d]", EventId, replaytable_rec.ReplayInterval );
	}
}

void EzSafReader :: serviceRequest()
{
	struct EzTxnMsg txnmsg;
	struct EzNetworkReplay eznetworkreplay_rec;
	struct EzReplayTable replaytable_rec;
	int MsgSize, retval;

	while( 1 )
	{
		dbUtilClose();
		trace( "SafReader waiting for servicing request...");
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * )&txnmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from EzSafReader Channel" );
			trace( "^^^^^^^^^^^^^^^EzSafReader Ended Abnormally^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
		}

		trace( DEBUG_NORMAL, "Message read from Channel[%s]", GetLastSenderChannelName() );

		if( dbUtilConnect() < 0 )
			continue;

		if( !strcmp( GetLastSenderChannelName(), EVENTMGR_CHANNEL ) )
			serviceTimeOut( &txnmsg );
		else if( txnmsg.MsgType == EZLINK_TXN_ReplayIntimationRequest )
			serviceReplayIntimationRequest( txnmsg.NetworkId );
		else if ( txnmsg.MsgType == EZLINK_TXN_PBFDownloadRequest )
			serviceSAFDownloadRequest( &txnmsg );
		else
			serviceReplayResponse( &txnmsg );
	}
}

int EzSafReader :: getNextPendingRecord( const char *I_NetworkId, struct EzSafDBInfo *safdbinfo_ptr )
{
	char SafRecordNo[ 21 ];
	char NetworkId[ 17 ];
	char TxnRefNum[ 151 ];
	char SAFDetailRec[ 2049 ];
	char SafRepeatIndicator;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    /*
     * change the symbol '||' to '+' for SqlServer
     */

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(SAFRECORDNO),\
		RTRIM(TXNREFNUM),\
		RTRIM(SAFDETREC),\
		RTRIM(SAFREPEATINDICATOR)\
    	FROM EZSAFDB WHERE RTRIM(SAFRECORDNO) + RTRIM(TRANDATE) + RTRIM(TRANTIME) IN (SELECT MIN(RTRIM(SAFRECORDNO)+RTRIM(TRANDATE)+RTRIM(TRANTIME)) FROM EZSAFDB WHERE RTRIM(NETWORKID)='%s' AND SAFSTATUS = 'P')", I_NetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( "<%s>", SqlStmt );
		trace( DEBUG_ERROR, "Error in Executing SqlStmt in getNextPendingRecord [ %d ]", odbcret );
		//getNativeErrorCode();
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum	) );
	memset( SAFDetailRec, 0, sizeof( SAFDetailRec ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, SafRecordNo, sizeof(SafRecordNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafRecordNo) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TxnRefNum, sizeof(TxnRefNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TxnRefNum) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, SAFDetailRec, sizeof(SAFDetailRec), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SAFDetailRec) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &SafRepeatIndicator, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafRepeatIndicator) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( safdbinfo_ptr->SafRecordNo, SafRecordNo );
    	strcpy( safdbinfo_ptr->TxnRefNum, TxnRefNum );
    	strcpy( safdbinfo_ptr->SAFDetailRec, SAFDetailRec );
    	strcpy( safdbinfo_ptr->NetworkId, I_NetworkId );
    	safdbinfo_ptr->SafRepeatIndicator = SafRepeatIndicator;
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else if( odbcret == SQL_NO_DATA )
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return odbcret;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzSafReader :: updateSafRepeatIndicator( const char *I_NetworkId, const char *I_TxnRefNum, char I_SafRepeatIndicator )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZSAFDB SET SAFREPEATINDICATOR = '%c' WHERE RTRIM(TXNREFNUM)='%s' AND RTRIM(NETWORKID)='%s';", I_SafRepeatIndicator, I_TxnRefNum, I_NetworkId );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafReader :: updateSafStatus( const char *I_TxnRefNum, char I_SafStatus, char I_SafResponseFlag, int I_SafResponse )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZSAFDB SET SAFSTATUS = '%c', SAFRESPONSEINDICATOR = '%c', SAFRESPONSE = '%d' WHERE RTRIM(TXNREFNUM)='%s';", I_SafStatus, I_SafResponseFlag, I_SafResponse, I_TxnRefNum );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafReader :: updateTimeOutCount( const char *I_NetworkId, const char *I_TxnRefNum, int I_TimeOutCount )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZSAFDB SET TIMEOUTCOUNT = %d WHERE RTRIM(TXNREFNUM)='%s' AND RTRIM(NETWORKID)='%s';", I_TimeOutCount, I_TxnRefNum, I_NetworkId );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafReader :: readTimeOutCount( const char *I_NetworkId, const char *I_TxnRefNum, int *I_TimeOutCount )
{
	int TimeOutCount = 0;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    /*
     * change the symbol '||' to '+' for SqlServer
     */

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT TIMEOUTCOUNT FROM EZSAFDB WHERE RTRIM(TXNREFNUM)='%s' AND RTRIM(NETWORKID)='%s';", I_TxnRefNum, I_NetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( "<%s>", SqlStmt );
		trace( DEBUG_ERROR, "Error in Executing SqlStmt in readTimeOutCount [ %d ]", odbcret );
		//getNativeErrorCode();
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &TimeOutCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TimeOutCount) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	*I_TimeOutCount = TimeOutCount;
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	trace("SQLFetch returns <%d>", odbcret);
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int main( int argc, char **argv )
{
	EzSafReader safreaderobj;
	safreaderobj.initEzSafReader( argv[ 0 ] );
	safreaderobj.serviceRequest();
	return 1;
}

