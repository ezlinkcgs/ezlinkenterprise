#include <ezlink/ezechomanager.h>

void EzEchoManager :: initEchoManager( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezechomgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^^^^^EzEchoManager Started^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "EzEchoManager already running" );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
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
	if( cfgutil.cfg_search( "ECHO#MIN_ECHO_INTERVAL", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ECHO#MIN_ECHO_INTERVAL from file[%s]..Setting Default as 30", cfgpath );
		MinEchoInterval = 30;
	}
	else
		MinEchoInterval = atoi( cfgval );

	cfgutil.cfg_close();

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil....." );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( createDummyChannel( "EzEchoMgr" ) < 0 )
	{
		trace( "Error in Creating Dummy Channel EzEchoMgr...." );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( InitEzCommUtil( this ) < 0 )
	{
		trace( "Error in initializing EzCommUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initNetworkUtil( this, false ) < 0 )
	{
		trace( "Error in initializing NetworkUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initEchoUtil( this, false ) < 0 )
	{
		trace( "Error in initializing EchoUtil" );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( echointervaltable.initEchoIntervalTable( this, getMaxNetworks() ) < 0 )
	{
		trace( "Error in initializing EchoIntervalTable" );
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initODBCUtil( "EzEchoMgr", this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing the EzODBCUtil");
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( DBConnect( ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Connecting the Database");
		trace( "^^^^^^^^^^^^^^^EzEchoManager Ended Abnormally^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	TraceNo = 1;
	TaskInit();
	initEzSigUtil( this );
}

void EzEchoManager :: probeNetworkStatus( int NetworkStatus, const char *NetworkId )
{
	if( !PortFlag )
	{
		if( NetworkStatus == NETWORK_STATUS_UP )
			setNetworkStatus( NetworkId, NETWORK_STATUS_DOWN );
	}
}

int EzEchoManager :: getNextTraceNo()
{
	if( TraceNo == 999999 )
		TraceNo = 1;
	else
		TraceNo++;
	return TraceNo;
}

void EzEchoManager :: sendSAFIntimation( const char *NetworkId )
{
	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

	txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
	strcpy( txnmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( DEBUG_ERROR, "Error in Writing Initimate NetworkReplay Message to Channel[%s] for NetworkId[%s]", "EzSafReader", NetworkId );
	else
		trace( DEBUG_NORMAL, "Written Initimate NetworkReplay Message to Channel[%s] for NetworkId[%s]", "EzSafReader", NetworkId );
}

void EzEchoManager :: probeSAFStatus( int NetworkStatus, const char *NetworkId )
{
	int retval;

	if( NetworkStatus != NETWORK_STATUS_UP )
		return;

	retval = readSAFDBInfo( NetworkId );
	/*if( retval != 0 && retval != 1403 )
	{
		if( dbutil.isDBConnectErr( retval ) )
		{
			if( dbutil.DBConnect() < 0 )
			{
				trace( "Error in Connecting with Switch DB...." );
				return;
			}
			retval = readSAFDBInfo( NetworkId );
		}
	}*/
	if( retval != 0 && retval != SQL_NO_DATA )
	{
		trace( "Error in Reading SAFDBInfo for NetworkId[%s]", NetworkId );
		return;
	}

	if( retval == 0 )
		sendSAFIntimation( NetworkId );
}

int EzEchoManager :: processLogOn( struct EzNetworkMemory network_rec, struct EzEchoTable echotable_rec )
{
	struct EzEchoIntervalTable echoint_rec;
	time_t currtime;
	struct EzTxnMsg txnmsg;
	int retval;
	char difftimestr[ 20 ];

	if( network_rec.NetworkStatus != NETWORK_STATUS_DOWN )
		return -1;

	if( !PortFlag )
		return -1;

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	retval = echointervaltable.readEchoIntervalTable( network_rec.NetworkId, &echoint_rec );

	if( retval < 0 )
	{
		memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
		strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
		currtime = time( NULL );
		echoint_rec.LastEchoTime = currtime;
		if( echointervaltable.addEchoIntervalTable( echoint_rec ) < 0 )
		{
			trace( "Error in adding NetworkId[%s] in EchoIntervalTable....", network_rec.NetworkId );
			return -1;
		}
	}
	else
	{
		currtime = time( NULL );
		memset( difftimestr, 0, sizeof( difftimestr ) );
		sprintf( difftimestr, "%f", difftime( currtime, echoint_rec.LastEchoTime ) );
		if( atoi( difftimestr ) < echotable_rec.EchoInterval )
		{
			return -1;
		}
	}

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
	echoint_rec.LastEchoTime = currtime;
	if( echointervaltable.updateEchoIntervalTable( echoint_rec ) < 0 )
	{
		trace( "Error in Updating NetworkId[%s] in EchoIntervalTable....test 1", network_rec.NetworkId );
		return -1;
	}

	trace( DEBUG_TEST,"NetworkId[ %s ] is down...Sending LogonReq", network_rec.NetworkId );

	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
	txnmsg.LocalDate = ezdatetimeutil.getSysDate();
	txnmsg.LocalTime = ezdatetimeutil.getSysTime();
	txnmsg.TranDate = ezdatetimeutil.getSysDate();
	txnmsg.TranTime = ezdatetimeutil.getSysTime();
	strcpy( txnmsg.DestPort, network_rec.PortName );
	strcpy( txnmsg.NetworkId, network_rec.NetworkId );
	txnmsg.NetCode = EZLINK_NETCODE_LOGON;
	txnmsg.TraceNo = getNextTraceNo();

	if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_LOGON_SENT )
	{
		retval = updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_LOGON_SENT );
		if( retval < 0 )
			trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
	}

	retval = WriteChannel( network_rec.ChannelName, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
	if( retval < 0 )
	{
		trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", network_rec.ChannelName, echotable_rec.NetworkId );
		return -1;
	}
	return 1;
}

void EzEchoManager :: processEchoNever( int NetworkStatus, const char *NetworkId )
{
	if( PortFlag )
	{
		if( NetworkStatus == NETWORK_STATUS_DOWN )
			setNetworkStatus( NetworkId, NETWORK_STATUS_UP );
	}
	else
	{
		if( NetworkStatus == NETWORK_STATUS_UP )
			setNetworkStatus( NetworkId, NETWORK_STATUS_DOWN );
	}
}

void EzEchoManager :: processEchoAlways( struct EzNetworkMemory network_rec, struct EzEchoTable echotable_rec )
{
	struct EzEchoIntervalTable echoint_rec;
	time_t currtime;
	struct EzTxnMsg txnmsg;
	int retval;
	char difftimestr[ 20 ];

	if( network_rec.NetworkStatus != NETWORK_STATUS_UP )
		return;

	if( !PortFlag )
	{
		setNetworkStatus( network_rec.NetworkId, NETWORK_STATUS_DOWN );
		return;
	}

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	retval = echointervaltable.readEchoIntervalTable( network_rec.NetworkId, &echoint_rec );

	if( retval < 0 )
	{
		memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
		strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
		currtime = time( NULL );
		echoint_rec.LastEchoTime = currtime;
		if( echointervaltable.addEchoIntervalTable( echoint_rec ) < 0 )
		{
			trace( "Error in adding NetworkId[%s] in EchoIntervalTable....", network_rec.NetworkId );
			return;
		}
	}
	else
	{
		currtime = time( NULL );
		memset( difftimestr, 0, sizeof( difftimestr ) );
		sprintf( difftimestr, "%f", difftime( currtime, echoint_rec.LastEchoTime ) );
		if( atoi( difftimestr ) < echotable_rec.EchoInterval )
		{
			return;
		}
	}

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
	echoint_rec.LastEchoTime = currtime;
	if( echointervaltable.updateEchoIntervalTable( echoint_rec ) < 0 )
	{
		trace( "Error in Updating NetworkId[%s] in EchoIntervalTable....test 2", network_rec.NetworkId );
		return;
	}

	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
	txnmsg.LocalDate = ezdatetimeutil.getSysDate();
	txnmsg.LocalTime = ezdatetimeutil.getSysTime();
	txnmsg.TranDate = ezdatetimeutil.getSysDate();
	txnmsg.TranTime = ezdatetimeutil.getSysTime();
	strcpy( txnmsg.DestPort, network_rec.PortName );
	strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
	txnmsg.NetCode = EZLINK_NETCODE_SIGNON;
	txnmsg.TraceNo = getNextTraceNo();

	if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_SIGNON_SENT )
	{
		retval = updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_SIGNON_SENT );
		if( retval < 0 )
			trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
	}
	retval = WriteChannel( network_rec.ChannelName, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
	if( retval < 0 )
		trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", network_rec.ChannelName, echotable_rec.NetworkId );
	else
		trace( DEBUG_NORMAL, "Written composed Echo Message to Channel[%s] for Port[%s] for NetworkId[%s]", network_rec.ChannelName, network_rec.PortName, echotable_rec.NetworkId );
}

void EzEchoManager :: processEchoWhenDown( struct EzNetworkMemory network_rec, struct EzEchoTable echotable_rec )
{
	struct EzEchoIntervalTable echoint_rec;
	time_t currtime;
	struct EzTxnMsg txnmsg;
	int retval;
	char difftimestr[ 20 ];

	if( network_rec.NetworkStatus != NETWORK_STATUS_DOWN )
			return;

	if( !PortFlag )
		return;

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	retval = echointervaltable.readEchoIntervalTable( network_rec.NetworkId, &echoint_rec );

	if( retval < 0 )
	{
		memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
		strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
		currtime = time( NULL );
		echoint_rec.LastEchoTime = currtime;
		if( echointervaltable.addEchoIntervalTable( echoint_rec ) < 0 )
		{
			trace( "Error in adding NetworkId[%s] in EchoIntervalTable....", network_rec.NetworkId );
			return;
		}
	}
	else
	{
		currtime = time( NULL );
		sprintf( difftimestr, "%f", difftime( currtime, echoint_rec.LastEchoTime ) );
		if( atoi( difftimestr ) < echotable_rec.EchoInterval )
		{
			return;
		}
	}

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
	echoint_rec.LastEchoTime = currtime;
	if( echointervaltable.updateEchoIntervalTable( echoint_rec ) < 0 )
	{
		trace( "Error in Updating NetworkId[%s] in EchoIntervalTable....", network_rec.NetworkId );
		return;
	}

	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
	txnmsg.LocalDate = ezdatetimeutil.getSysDate();
	txnmsg.LocalTime = ezdatetimeutil.getSysTime();
	txnmsg.TranDate = ezdatetimeutil.getSysDate();
	txnmsg.TranTime = ezdatetimeutil.getSysTime();
	strcpy( txnmsg.DestPort, network_rec.PortName );
	strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
	txnmsg.NetCode = EZLINK_NETCODE_SIGNON;
	txnmsg.TraceNo = getNextTraceNo();

	if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_SIGNON_SENT )
	{
		retval = updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_SIGNON_SENT );
		if( retval < 0 )
			trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
	}
	retval = WriteChannel( network_rec.ChannelName, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
	if( retval < 0 )
		trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", network_rec.ChannelName, echotable_rec.NetworkId );
	else
		trace( DEBUG_NORMAL, "Written composed Echo Message to Channel[%s] for Port[%s] for NetworkId[%s]", network_rec.ChannelName, network_rec.PortName, echotable_rec.NetworkId );
}

void EzEchoManager :: processEchoWhenUp( struct EzNetworkMemory network_rec, struct EzEchoTable echotable_rec )
{
	struct EzEchoIntervalTable echoint_rec;
	time_t currtime;
	struct EzTxnMsg txnmsg;
	int retval;
	char difftimestr[ 20 ];

	if( network_rec.NetworkStatus != NETWORK_STATUS_UP )
		return;

	if( !PortFlag )
	{
		setNetworkStatus( network_rec.NetworkId, NETWORK_STATUS_DOWN );
		return;
	}

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	retval = echointervaltable.readEchoIntervalTable( network_rec.NetworkId, &echoint_rec );

	if( retval < 0 )
	{
		memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
		strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
		currtime = time( NULL );
		echoint_rec.LastEchoTime = currtime;
		if( echointervaltable.addEchoIntervalTable( echoint_rec ) < 0 )
		{
			trace( "Error in adding NetworkId[%s] in EchoIntervalTable....", network_rec.NetworkId );
			return;
		}
	}
	else
	{
		currtime = time( NULL );
		sprintf( difftimestr, "%f", difftime( currtime, echoint_rec.LastEchoTime ) );
		if( atoi( difftimestr ) < echotable_rec.EchoInterval )
		{
			return;
		}
	}

	memset( &echoint_rec, 0, sizeof( struct EzEchoIntervalTable ) );
	strcpy( echoint_rec.NetworkId, network_rec.NetworkId );
	echoint_rec.LastEchoTime = currtime;
	if( echointervaltable.updateEchoIntervalTable( echoint_rec ) < 0 )
	{
		trace( "Error in Updating NetworkId[%s] in EchoIntervalTable....test 3", network_rec.NetworkId );
		return;
	}

	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	txnmsg.MsgType = EZLINK_TXN_NtwkRequest;
	txnmsg.LocalDate = ezdatetimeutil.getSysDate();
	txnmsg.LocalTime = ezdatetimeutil.getSysTime();
	txnmsg.TranDate = ezdatetimeutil.getSysDate();
	txnmsg.TranTime = ezdatetimeutil.getSysTime();
	strcpy( txnmsg.DestPort, network_rec.PortName );
	strcpy( txnmsg.NetworkId, echotable_rec.NetworkId );
	txnmsg.NetCode = EZLINK_NETCODE_SIGNON;
	txnmsg.TraceNo = getNextTraceNo();

	if( echotable_rec.EchoRespStatus != ECHO_RESP_STATUS_SIGNON_SENT )
	{
		retval = updateEchoRespStatus( echotable_rec.NetworkId, ECHO_RESP_STATUS_SIGNON_SENT );
		if( retval < 0 )
			trace( "Error in Updating EchoRespStatus for NetworkId[%s]", echotable_rec.NetworkId );
	}
	retval = WriteChannel( network_rec.ChannelName, ( char * )&txnmsg, sizeof( struct EzTxnMsg ) );
	if( retval < 0 )
		trace( "Error in writing Message to Channel[%s] for NetworkId[%s]", network_rec.ChannelName, echotable_rec.NetworkId );
	else
		trace( DEBUG_NORMAL, "Written composed Echo Message to Channel[%s] for Port[%s] for NetworkId[%s]", network_rec.ChannelName, network_rec.PortName, echotable_rec.NetworkId );
}

void EzEchoManager :: processEcho( struct EzNetworkMemory network_rec, struct EzEchoTable echotable_rec )
{
	if( echotable_rec.LogOnReq == 'Y' || echotable_rec.LogOnReq == 'y' )
	{
		if( processLogOn( network_rec, echotable_rec ) >= 0 )
			return;
	}
	if( echotable_rec.EchoProperty == ECHO_SEND_ALWAYS )
	{
		processEchoAlways( network_rec, echotable_rec );
	}
	else if( echotable_rec.EchoProperty == ECHO_SEND_UP )
	{
		processEchoWhenUp( network_rec, echotable_rec );
	}
	else if( echotable_rec.EchoProperty == ECHO_SEND_DOWN )
	{
		processEchoWhenDown( network_rec, echotable_rec );
	}
}

int EzEchoManager :: readSAFDBInfo( const char *I_NetworkId )
{
	char NetworkId[ 17 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcrt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    obdcrt = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", obdcrt );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(NETWORKID) FROM EZSAFDB WHERE RTRIM(NETWORKID)='%s'", I_NetworkId );

    obdcrt = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
        trace( "SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in readSAFDBInfo [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZSAFDB [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    if( (obdcrt = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else if( obdcrt == SQL_NO_DATA )
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return obdcrt;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

void EzEchoManager :: serviceRequest()
{
	struct EzNetworkMemory network_rec;
	struct EzEchoTable echotable_rec;
	int retval, NetworkCount;

	while( 1 )
	{
		sleep( MinEchoInterval );
		NetworkCount = getCurrentNetworkCount();
		for( int i = 0; i < NetworkCount; i++ )
		{
			memset( &network_rec, 0, sizeof( struct EzNetworkMemory ) );
			retval = getNextNetworkRecord( &network_rec, i );
			if( retval < 0 )
			{
				trace( "Error in Getting Network Record %d from NetworkMemory....", i + 1 );
				break;
			}
			memset( &echotable_rec, 0, sizeof( struct EzEchoTable ) );
			retval = readEchoTable( network_rec.NetworkId, &echotable_rec );
			if( retval < 0 )
			{
				trace( "Error in Reading NetworkId[%s] from NetworkEcho Memory....", network_rec.NetworkId );
				continue;
			}
			PortFlag = IsPortUp( network_rec.PortName );
			probeNetworkStatus( network_rec.NetworkStatus, network_rec.NetworkId );
			probeSAFStatus( network_rec.NetworkStatus, network_rec.NetworkId );
			processEcho( network_rec, echotable_rec );
		}
	}
}

int main( int argc, char **argv )
{
	EzEchoManager ezechomgrobj;
	ezechomgrobj.initEchoManager( argv[ 0 ] );
	ezechomgrobj.serviceRequest();
	return 1;
}


