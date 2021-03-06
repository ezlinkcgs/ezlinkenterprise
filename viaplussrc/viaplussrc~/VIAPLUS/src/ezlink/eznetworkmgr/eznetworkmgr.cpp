#include <ezlink/eznetworkmgr.h>

void EzNetworkMgr :: initNetworkMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eznetworkmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if ( initNetworkMgrUtil( this ) < 0 )
	{
		trace( "Error in Initializing NetworkMgrUtil" );
		trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	/*if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}*/

	if( IsTaskRunning( TaskName ) < 0 )
	{
		trace( DEBUG_NORMAL, "First Instance of EzNetworkMgr...Initializing NetworkSharedMemory" );
		if( LoadNetworkMemory()	< 0 )
		{
			trace( "Error in Loading Network Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( LoadTxnDBMemory() < 0 )
		{
			trace( "Error in Loading TxnDB Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( LoadTxnSeqMemory() < 0 )
		{
			trace( "Error in Loading Txn Sequence Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( LoadReplayMemory() < 0 )
		{
			trace( "Error in Loading Replay Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( LoadEchoMemory() < 0 )
		{
			trace( "Error in Loading Echo Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( LoadNetworkBusMemory() < 0 )
		{
			trace( "Error in Loading NetworkBus Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
	}
	else
	{
		if( getNetworkMemory() < 0 )
		{
			trace( "Error in getting Network Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getTxnDBMemory() < 0 )
		{
			trace( "Error in getting TxnDB Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getTxnSeqMemory() < 0 )
		{
			trace( "Error in getting Txn Sequence Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getReplayMemory() < 0 )
		{
			trace( "Error in getting Replay Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getEchoMemory() < 0 )
		{
			trace( "Error in getting Echo Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getNetworkBusMemory() < 0 )
		{
			trace( "Error in getting NetworkBus Memory...");
			trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
	}

	//dbutil.DBClose();

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	trace( "intialized Channelutil");

	if( CreateChannel( "EzNetworkMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating EzNetworkMgr Channel" );
		trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	trace( "Created EzNetworkMgr Channel with ChannelId[%d]", GetSourceChannelKeyId() );
	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing SecurityUtil" );
		trace( "^^^^^^^^^^^EzNetworkMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

int EzNetworkMgr :: GetSysDate()
{
    char SysDate[ 20 ];
    struct tm *timenow;
    time_t t = 0;
    t = time( &t );
    timenow = localtime( &t );
    memset( SysDate, 0, sizeof( SysDate ) );
    sprintf( SysDate, "%02d%02d%02d", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year % 100 );
    return ( atoi( SysDate ) );
}

int EzNetworkMgr :: GetSysTime()
{
    char SysTime[ 20 ];
    struct tm *timenow;
    time_t t = 0;
    t = time( &t );
    timenow = localtime( &t );
    memset( SysTime, 0, sizeof( SysTime ) );
    sprintf( SysTime, "%02d%02d%02d", timenow->tm_hour, timenow->tm_min, timenow->tm_sec );
    return ( atoi( SysTime ) );
}

int EzNetworkMgr :: serviceNetworkSignOn( const char *NetworkId )
{
	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
    txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
    memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
    strcpy( txnmsg.NetworkId, NetworkId );
    txnmsg.TranDate = GetSysDate();
    txnmsg.TranTime = GetSysTime();
    txnmsg.LocalDate = GetSysDate();
    txnmsg.LocalTime = GetSysTime();
    txnmsg.NetCode = EZLINK_NETCODE_SIGNON;

	if( readNetworkMemory( NetworkId ) < 0 )
	{
		trace( "Error in reading NetworkId[%s] from NetworkMemory", NetworkId );
		return -1;
	}
	strcpy( txnmsg.DestPort, getNetworkPortName() );
	if( WriteChannel( getNetworkChannelName(), ( char * )&txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in writing NetworkSignOn message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
		return -1;
	}
	trace( DEBUG_NORMAL, "Written Network SignOn message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
    return 1;
}

int EzNetworkMgr :: serviceNetworkSignOff( const char *NetworkId )
{
	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
    txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
    memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
    strcpy( txnmsg.NetworkId, NetworkId );
    txnmsg.TranDate = GetSysDate();
    txnmsg.TranTime = GetSysTime();
    txnmsg.LocalDate = GetSysDate();
    txnmsg.LocalTime = GetSysTime();
    txnmsg.NetCode = EZLINK_NETCODE_SIGNOFF;
	if( readNetworkMemory( NetworkId ) < 0 )
	{
		trace( "Error in reading NetworkId[%s] from NetworkMemory", NetworkId );
		return -1;
	}
	strcpy( txnmsg.DestPort, getNetworkChannelName() );
	if( WriteChannel( getNetworkChannelName(), ( char * )&txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in writing NetworkSignOff message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
		return -1;
	}
	trace( DEBUG_NORMAL, "Written Network SignOff message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
    return 1;
}

int EzNetworkMgr :: serviceNetworkLogOn( const char *NetworkId )
{
	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
    txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
    memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
    strcpy( txnmsg.NetworkId, NetworkId );
    txnmsg.TranDate = GetSysDate();
    txnmsg.TranTime = GetSysTime();
    txnmsg.LocalDate = GetSysDate();
    txnmsg.LocalTime = GetSysTime();
    txnmsg.NetCode = EZLINK_NETCODE_LOGON;
	if( readNetworkMemory( NetworkId ) < 0 )
	{
		trace( "Error in reading NetworkId[%s] from NetworkMemory", NetworkId );
		return -1;
	}
	strcpy( txnmsg.DestPort, getNetworkPortName() );
	if( WriteChannel( getNetworkChannelName(), ( char * )&txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in writing NetworkLogOn message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
		return -1;
	}
	trace( DEBUG_NORMAL, "Written NetworkLogOn message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
    return 1;
}

int EzNetworkMgr :: serviceNetworkLogOff( const char *NetworkId )
{
	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
    txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
    memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
    strcpy( txnmsg.NetworkId, NetworkId );
    txnmsg.TranDate = GetSysDate();
    txnmsg.TranTime = GetSysTime();
    txnmsg.LocalDate = GetSysDate();
    txnmsg.LocalTime = GetSysTime();
    txnmsg.NetCode = EZLINK_NETCODE_LOGOFF;
	if( readNetworkMemory( NetworkId ) < 0 )
	{
		trace( "Error in reading NetworkId[%s] from NetworkMemory", NetworkId );
		return -1;
	}
	strcpy( txnmsg.DestPort, getNetworkPortName() );
	if( WriteChannel( getNetworkChannelName(), ( char * )&txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in writing NetworkLogOff message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
		return -1;
	}
	trace( DEBUG_NORMAL, "Written NetworkLogOff message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
    return 1;
}

int EzNetworkMgr :: serviceNetworkXchg( const char *NetworkId )
{
	struct EzTxnMsg txnmsg;
	char NetworkCommKey[ 65 ];
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
    txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
    memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
    strcpy( txnmsg.NetworkId, NetworkId );
    txnmsg.TranDate = GetSysDate();
    txnmsg.TranTime = GetSysTime();
    txnmsg.LocalDate = GetSysDate();
    txnmsg.LocalTime = GetSysTime();
    txnmsg.NetCode = EZLINK_NETCODE_KEYXCHG;
    if( readNetworkMemory( NetworkId ) < 0 )
	{
		trace( "Error in reading NetworkId[%s] from NetworkMemory", NetworkId );
		return -1;
	}
    strcpy( txnmsg.DestPort, getNetworkPortName() );

    /*if( GenNetworkAcqCommKey( NetworkId, NetworkCommKey ) < 0 )
    {
    	trace( "Error in Generating NetworkAcqCommKey for NetworkId[%s]", NetworkCommKey );
    	return -1;
    }*/

    trace( DEBUG_NORMAL, "Generated Acquirer Network CommKey[%s] for NetworkId[%s]", NetworkCommKey, NetworkId );
    strcpy( txnmsg.PinKey, NetworkCommKey );
    txnmsg.Keylen = strlen( NetworkCommKey );

    if( WriteChannel( getNetworkChannelName(), ( char * )&txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in writing NetworkKeyXChg message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
		return -1;
	}
	trace( DEBUG_NORMAL, "Written NetworkKeyXChg message to Channel[%s] for NetworkId[%s]", getNetworkChannelName(), NetworkId );
	return 1;
}

int EzNetworkMgr :: serviceNetworkUpdateStatus( const char *NetworkId, int NetworkStatus )
{
	int SqlErr;
	trace( DEBUG_TEST, "Updating Network Status for NetworkId[%s] with NetworkStatus[%d]", NetworkId, NetworkStatus );

	if( updateNetworkStatus( NetworkId, NetworkStatus ) < 0 )
	{
		trace( "Error in Updating Network Status for NetworkId[%s] in NetworkMemory", NetworkId );
		return -1;
	}
	trace( "Updated Status[%d] for NetworkId[%s] in NetworkMemory", NetworkStatus, NetworkId );
	if( updateNetworkStatus( NetworkId, NetworkStatus ) < 0 )
	{
		/*if( EZLINK_ORA_CONNECT_ERR( SqlErr ) )
		{
			if( dbutil.DBConnect() < 0 )
			{
				trace( "Error in Connecting with Switch Database" );
				return -1;
			}
			if( updateEzNetworkStatus( NetworkId, NetworkStatus, &SqlErr ) < 0 )
			{
				trace( "Error in Updating Network Status for NetworkId[%s] in EzNetwork Table..OraErr[%05d]", NetworkId, SqlErr );
				return -1;
			}
		}
		else*/
		//{
			trace( "Error in Updating Network Status for NetworkId[%s] in EzNetwork Table..OraErr[%05d]", NetworkId, SqlErr );
			return -1;
		//}
	}
	trace( "Updated Status[%d] for NetworkId[%s] in EzNetwork Table", NetworkStatus, NetworkId );
	return 1;
}

int EzNetworkMgr :: serviceNetworkUpdateCutOverDate( const char *NetworkId, int CutoverDate )
{
	int SqlErr;
	trace( DEBUG_TEST, "Updating CutOverDate for NetworkId[%s] with CutoverDate[%d]", NetworkId, CutoverDate );

	if( updateNetworkBusDay( NetworkId, CutoverDate ) < 0 )
	{
		/*if( EZLINK_ORA_CONNECT_ERR( SqlErr ) )
		{
			if( dbutil.DBConnect() < 0 )
			{
				trace( "Error in Connecting with Switch Database" );
				return -1;
			}
			if( updateEzNetworkBusDay( NetworkId, CutoverDate, &SqlErr ) < 0 )
			{
				trace( "Error in Updating CutoverDate[%d] for NetworkId[%s] in EzBusDay Table..OraErr[%05d]", CutoverDate, NetworkId, SqlErr );
				return -1;
			}
		}
		else*/
		{
			trace( "Error in Updating CutoverDate[%d] for NetworkId[%s] in EzBusDay Table..OraErr[%05d]", CutoverDate, NetworkId, SqlErr );
			return -1;
		}
	}
	trace( "Updated CutoverDate[%d] for NetworkId[%s] in EzBusDay Table", CutoverDate, NetworkId );
	return 1;
}

void EzNetworkMgr :: serviceRequest()
{
	int MsgSize;
	struct EzNetworkMgrMsg netmsg;

	while( 1 )
	{
		//dbutil.dbUtilClose();
		trace( "EzNetworkMgr Waiting For Request....");
		memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
		if( ReadMessage( ( char * ) &netmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message From EzNetworkMgr Channel..." );
			sleep( 1 );
			continue;
		}
		//if( dbutil.dbUtilConnect() < 0 )
			//continue;
		switch( netmsg.Command )
		{
			case EZLINK_NTWK_SIGNON:
			serviceNetworkSignOn( netmsg.NetworkId );
			break;

			case EZLINK_NTWK_SIGNOFF:
			serviceNetworkSignOff( netmsg.NetworkId );
			break;

			case EZLINK_NTWK_LOGON:
			serviceNetworkLogOn( netmsg.NetworkId );
			break;

			case EZLINK_NTWK_LOGOFF:
			serviceNetworkLogOff( netmsg.NetworkId );
			break;

			case EZLINK_NTWK_KEYXHG:
			serviceNetworkXchg( netmsg.NetworkId );
			break;

			case EZLINK_NTWK_UPDATE_STATUS:
			serviceNetworkUpdateStatus( netmsg.NetworkId, netmsg.NetworkStatus );
			break;

			case EZLINK_NTWK_UPDATE_CUTOVERDATE:
			serviceNetworkUpdateCutOverDate( netmsg.NetworkId, netmsg.CutoverDate );

			break;
		}
	}
}

int main( int argc, char **argv )
{
	EzNetworkMgr networkmgrobj;
	networkmgrobj.initNetworkMgr( argv[ 0 ] );
	networkmgrobj.serviceRequest();
	return 1;
}


