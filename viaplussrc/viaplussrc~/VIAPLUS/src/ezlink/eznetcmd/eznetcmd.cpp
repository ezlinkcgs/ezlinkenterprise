#include <ezlink/eznetcmd.h>

int EzNetCmd :: initNetCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eznetcmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^EzNetCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil...." );
		return -1;
	}

	if( createDummyChannel( "eznetcmd" ) < 0 )
	{
		trace( "Error in Creating Dummy Channel eznetcmd...." );
		return -1;
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
        trace( "Error in opening file[%s]", cfgpath );
        return -1;
    }

    memset( cfgval, 0, sizeof( cfgval ) );
    if( cfgutil.cfg_search( "NETWORK#MAXNETWORK", cfgval, 2 ) < 0 )
    {
        trace( "Error in Searching NETWORK#MAXNETWORK from file[%s]", cfgpath );
        cfgutil.cfg_close();
        return -1;
    }

    cfgutil.cfg_close();

    MaxNetworks = atoi( cfgval );

	NetworkMemoryId = LocateMemoryId( this, "NETWORKMEMORY" );

	if( NetworkMemoryId < 0 )
	{
		trace( "Error in Locating NETWORKMEMORY" );
		return -1;
	}

	NetworkShmid = shmget( ( key_t ) NetworkMemoryId, 0, IPC_CREAT | 0666 );
	if( NetworkShmid < 0 )
	{
		trace( "Error in getting Network Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	networktable_ptr = ( struct EzNetworkMemory * ) shmat( NetworkShmid, 0, 0 );

	if( networktable_ptr == NULL )
	{
		trace( "Error in attaching Network Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkSemid = semget( ( key_t ) NetworkMemoryId, 0, IPC_CREAT | 0666 );
	if( NetworkSemid < 0 )
	{
		trace( "Error in getting Network Semaphore...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing initODBCUtil...." );
		return -1;
	}

	return 1;
}

int EzNetCmd :: listNetworkInfo()
{
	struct sembuf sem_buf;
	char NetworkStatusStr[ 50 ];

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%16s%16s%12s%10s%12s", "NetworkId", "ChannelName", "PortName", "Status", "TimeOut", "InstId", "KeyReq", "CutOverReq" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( networktable_ptr + i )->NetworkId, NETWORKID_INIT_VAL ) )
		{

			memset( NetworkStatusStr, 0, sizeof( NetworkStatusStr ) );

			if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_UP )
				strcpy( NetworkStatusStr, "UP" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_DOWN )
				strcpy( NetworkStatusStr, "DOWN" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAF )
				strcpy( NetworkStatusStr, "SAF" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
				strcpy( NetworkStatusStr, "SAFUPLOAD" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
				strcpy( NetworkStatusStr, "SAFDOWNLOAD" );

			printf( "\n%20s%20s%20s%16s%16d%12s%10c%12c", ( networktable_ptr + i )->NetworkId, ( networktable_ptr + i )->ChannelName, ( networktable_ptr + i )->PortName, NetworkStatusStr, ( networktable_ptr + i )->TimeOut, ( networktable_ptr + i )->InstId, ( networktable_ptr + i )->KeyReq, ( networktable_ptr + i )->CutOverReq );
		}

		sem_buf.sem_op = 2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return 1;
}

int EzNetCmd :: listNetworkInfo( const char *NetworkId )
{
	struct sembuf sem_buf;
	char NetworkStatusStr[ 50 ];
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%16s%16s%12s%10s%12s", "NetworkId", "ChannelName", "PortName", "Status", "TimeOut", "InstId", "KeyReq", "CutOverReq" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( NetworkId, ( networktable_ptr + i )->NetworkId ) )
		{
			retval = 1;
			memset( NetworkStatusStr, 0, sizeof( NetworkStatusStr ) );
			if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_UP )
				strcpy( NetworkStatusStr, "UP" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_DOWN )
				strcpy( NetworkStatusStr, "DOWN" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAF )
				strcpy( NetworkStatusStr, "SAF" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
				strcpy( NetworkStatusStr, "SAFUPLOAD" );
			else if( ( networktable_ptr + i )->NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
				strcpy( NetworkStatusStr, "SAFDOWNLOAD" );

			printf( "\n%20s%20s%20s%16s%16d%12s%10c%12c", ( networktable_ptr + i )->NetworkId, ( networktable_ptr + i )->ChannelName, ( networktable_ptr + i )->PortName, NetworkStatusStr, ( networktable_ptr + i )->TimeOut, ( networktable_ptr + i )->InstId, ( networktable_ptr + i )->KeyReq, ( networktable_ptr + i )->CutOverReq );
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return retval;
}

int EzNetCmd :: updateNetworkInfo( const char *NetworkId )
{
	struct EzNetwork eznetwork_rec;
	int retval;
	struct sembuf sem_buf;

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB...." );
		return -1;
	}
	memset( &eznetwork_rec, 0, sizeof( struct EzNetwork ) );
	retval = readEzNetwork( NetworkId, &eznetwork_rec );

	if( retval != 0 )
	{
		trace( "Error in Reading NetworkId[%s] from EzNetwork Table...SqlErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}

	DBClose();

	retval = -1;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( NetworkId, ( networktable_ptr + i )->NetworkId ) )
		{
			retval = 1;
			strcpy( ( networktable_ptr + i )->NetworkPropertyId, eznetwork_rec.NetworkPropertyId );
			strcpy( ( networktable_ptr + i )->ChannelName, eznetwork_rec.ChannelName );
			strcpy( ( networktable_ptr + i )->PortName, eznetwork_rec.PortName );
			strcpy( ( networktable_ptr + i )->NetworkName, eznetwork_rec.NetworkName );
			( networktable_ptr + i )->TimeOut = eznetwork_rec.TimeOut;
			strcpy( ( networktable_ptr + i )->InstId, eznetwork_rec.InstId );
			( networktable_ptr + i )->KeyReq = eznetwork_rec.KeyReq;
			( networktable_ptr + i )->CutOverReq = eznetwork_rec.CutOverReq;
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetCmd :: searchNetworkInfo( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( networktable_ptr + i )->NetworkId, NetworkId ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetCmd :: addNetworkInfo( const char *NetworkId )
{
	struct EzNetwork eznetwork_rec;
	int retval;
	struct sembuf sem_buf;

	if( searchNetworkInfo( NetworkId ) >= 0 )
	{
		trace( "Cannot add NetworkId[%s]....NetworkId is Already Added" );
		return -1;
	}

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB...." );
		return -1;
	}
	memset( &eznetwork_rec, 0, sizeof( struct EzNetwork ) );
	retval = readEzNetwork( NetworkId, &eznetwork_rec );

	if( retval != 0 )
	{
		trace( "Error in Reading NetworkId[%s] from EzNetwork Table...SqlErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	retval = -1;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( networktable_ptr + i )->NetworkId, NETWORKID_INIT_VAL ) )
		{
			retval = 1;
			memset( networktable_ptr + i, 0, sizeof( EzNetworkMemory ) );
			strcpy( ( networktable_ptr + i )->NetworkId, eznetwork_rec.NetworkId );
			( networktable_ptr + i )->NetworkStatus = eznetwork_rec.NetworkStatus;
			strcpy( ( networktable_ptr + i )->NetworkPropertyId, eznetwork_rec.NetworkPropertyId );
			strcpy( ( networktable_ptr + i )->ChannelName, eznetwork_rec.ChannelName );
			strcpy( ( networktable_ptr + i )->PortName, eznetwork_rec.PortName );
			strcpy( ( networktable_ptr + i )->NetworkName, eznetwork_rec.NetworkName );
			strcpy( ( networktable_ptr + i )->InstId, eznetwork_rec.InstId );
			( networktable_ptr + i )->TimeOut = eznetwork_rec.TimeOut;
			( networktable_ptr + i )->KeyReq = eznetwork_rec.KeyReq;
			( networktable_ptr + i )->CutOverReq = eznetwork_rec.CutOverReq;
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetCmd :: removeNetworkInfo( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( networktable_ptr + i )->NetworkId, NetworkId ) )
		{
			memset( networktable_ptr + i, 0, sizeof( struct EzNetworkMemory ) );
			strcpy( ( networktable_ptr + i )->NetworkId, NETWORKID_INIT_VAL );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetCmd :: serviceSignOn( const char *NetworkId )
{
	struct EzNetworkMgrMsg netmsg;

	memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
	netmsg.Command = EZLINK_NTWK_SIGNON;
	strcpy( netmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzNetworkMgr", ( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Network SignOn Message to NetworkMgr" );
		return -1;
	}
	trace( "Written Network SignOn Message Successfully to NetworkMgr" );
	return 1;
}

int EzNetCmd :: serviceSignOff( const char *NetworkId )
{
	struct EzNetworkMgrMsg netmsg;

	memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
	netmsg.Command = EZLINK_NTWK_SIGNOFF;
	strcpy( netmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzNetworkMgr", ( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Network SignOff Message to NetworkMgr" );
		return -1;
	}
	trace( "Written Network SignOff Message Successfully to NetworkMgr" );
	return 1;

}

int EzNetCmd :: serviceLogOn( const char *NetworkId )
{
	struct EzNetworkMgrMsg netmsg;

	memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
	netmsg.Command = EZLINK_NTWK_LOGON;
	strcpy( netmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzNetworkMgr", ( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Network LogOn Message to NetworkMgr" );
		return -1;
	}
	trace( "Written Network LogOn Message Successfully to NetworkMgr" );
	return 1;

}

int EzNetCmd :: serviceLogOff( const char *NetworkId )
{
	struct EzNetworkMgrMsg netmsg;

	memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
	netmsg.Command = EZLINK_NTWK_LOGOFF;
	strcpy( netmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzNetworkMgr", ( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Network LogOff Message to NetworkMgr" );
		return -1;
	}
	trace( "Written Network LogOff Message Successfully to NetworkMgr" );
	return 1;
}

int EzNetCmd :: serviceKeyXchg( const char *NetworkId )
{
	struct EzNetworkMgrMsg netmsg;

	memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
	netmsg.Command = EZLINK_NTWK_KEYXHG;
	strcpy( netmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzNetworkMgr", ( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Network Key Exchange Message to NetworkMgr" );
		return -1;
	}
	trace( "Written Network Ke Exchange Message Successfully to NetworkMgr" );
	return 1;
}

int EzNetCmd :: setNetworkStatus( const char *NetworkId, int NetworkStatus )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( networktable_ptr + i )->NetworkId, NetworkId ) )
		{
			( networktable_ptr + i )->NetworkStatus = NetworkStatus;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkSemid, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	if( retval < 0 )
		return retval;

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB...." );
		return -1;
	}

	int SqlErr;
	if( updateEzNetworkStatus( NetworkId, NetworkStatus, &SqlErr ) < 0 )
	{
		trace( "Error in Updating Status for NetworkId[%s] in EzNetwork Table...SqlErr[%05d]", NetworkId, SqlErr );
		DBClose();
		return -1;
	}

	DBClose();
	return 1;
}

int EzNetCmd :: readEzNetwork( const char *I_NetworkId, struct EzNetwork *eznetwork_ptr )
{
	char NetworkId[ 17 ];
	char NetworkName[ 33 ];
	char NetworkPropertyId[ 11 ];
	int TimeOut;
	char ChannelName[ 33 ];
	char PortName[ 33 ];
	int NetworkStatus;
	char InstId[ 13 ];
	char KeyReq;
	char CutOverReq;
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

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(NETWORKID), \
        RTRIM(NETWORKNAME), \
        RTRIM(NETWORKPROPERTYID), \
        TIMEOUT, \
        RTRIM(CHANNELNAME), \
        RTRIM(PORTNAME), \
        NETWORKSTATUS, \
        RTRIM(INSTID), \
        KEYREQ, \
        CUTOVERREQ \
    FROM EZNETWORK EZNETWORK WHERE RTRIM(NETWORKID)='%s';", I_NetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetwork [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( NetworkName, 0, sizeof( NetworkName ) );
	memset( NetworkPropertyId, 0, sizeof( NetworkPropertyId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( PortName, 0, sizeof( PortName ) );
	memset( InstId, 0, sizeof( InstId ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, NetworkName, sizeof(NetworkName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkName) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, NetworkPropertyId, sizeof(NetworkPropertyId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkPropertyId) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &TimeOut, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TimeOut) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, PortName, sizeof(PortName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(PortName) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &NetworkStatus, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkStatus) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &KeyReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(KeyReq) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_BINARY, &CutOverReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CutOverReq) in EZNETWORK [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( eznetwork_ptr, 0, sizeof( struct EzNetworkMemory ) );

         strcpy( eznetwork_ptr->NetworkId, NetworkId );
         strcpy( eznetwork_ptr->NetworkName, NetworkName );
         strcpy( eznetwork_ptr->NetworkPropertyId, NetworkPropertyId );
         eznetwork_ptr->TimeOut = TimeOut;
         strcpy( eznetwork_ptr->ChannelName, ChannelName );
         strcpy( eznetwork_ptr->PortName, PortName );
         strcpy( eznetwork_ptr->InstId, InstId );
         if( NetworkStatus == NETWORK_STATUS_UP )
         	eznetwork_ptr->NetworkStatus = NETWORK_STATUS_DOWN;
         else
         	eznetwork_ptr->NetworkStatus = NetworkStatus;
         eznetwork_ptr->KeyReq = KeyReq;
         eznetwork_ptr->CutOverReq = CutOverReq;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzNetCmd :: updateEzNetworkStatus( const char *I_NetworkId, int I_NetworkStatus, int *SqlErr )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZNETWORK SET NETWORKSTATUS=%d WHERE RTRIM(NETWORKID)=%s;", I_NetworkStatus, I_NetworkId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}


int EzNetCmd :: serviceNetCmd( int argc, char **argv )
{
	char command[ 100 ], NetworkId[ 17 ];
	int NetworkStatus;

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\neznetcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				addNetworkInfo( command );
				continue;
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				updateNetworkInfo( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					listNetworkInfo();
					continue;
				}
				listNetworkInfo( command );
				continue;
			}
			else if( !strcasecmp( command, "remove" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				removeNetworkInfo( command );
				continue;
			}
			else if( !strcasecmp( command, "signon" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				serviceSignOn( command );
				continue;
			}
			else if( !strcasecmp( command, "signoff" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				serviceSignOff( command );
				continue;
			}
			else if( !strcasecmp( command, "logon" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				serviceLogOn( command );
				continue;
			}
			else if( !strcasecmp( command, "logoff" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				serviceLogOff( command );
				continue;
			}
			else if( !strcasecmp( command, "xchg" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				serviceKeyXchg( command );
				continue;
			}
			else if( !strcasecmp( command, "set" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( NetworkId, 0, sizeof( NetworkId ) );
				strcpy( NetworkId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( !strcasecmp( command, "UP") )
					NetworkStatus = NETWORK_STATUS_UP;
				else if( !strcasecmp( command, "DOWN") )
					NetworkStatus = NETWORK_STATUS_DOWN;
				else if( !strcasecmp( command, "SAF") )
					NetworkStatus = NETWORK_STATUS_SAF;
				else if( !strcasecmp( command, "SAFUPLOAD") )
					NetworkStatus = NETWORK_STATUS_SAFUPLOAD;
				else if( !strcasecmp( command, "SAFDOWNLOAD") )
					NetworkStatus = NETWORK_STATUS_SAFDOWNLOAD;
				else
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				setNetworkStatus( NetworkId, NetworkStatus );
				continue;
			}
			else if( !strcmp( command, "help" ) )
			{
				printf("\n <set> <NetworkId> <up/down/saf/safupload/safdownload>");
				printf("\n <add> <NetworkId>");
				printf("\n <update> <NetworkId>");
				printf("\n <remove> <NetworkId>");
				printf("\n <signon> <NetworkId>");
				printf("\n <signoff> <NetworkId>");
				printf("\n <logon> <NetworkId>");
				printf("\n <logoff> <NetworkId>");
				printf("\n <xchg> <NetworkId>");
				printf("\n <list> <NetworkId>");
				printf("\n <list>");
			}
			else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
				break;
			else
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
		}
	}
	else
	{
		memset( command, 0, sizeof( command ) );
		strcpy( command, argv[ 1 ] );
		if( !strcasecmp( command, "add" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				addNetworkInfo( command );
			}
		}
		else if( !strcasecmp( command, "update" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				updateNetworkInfo( command );
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if ( argc == 2 )
				listNetworkInfo();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				listNetworkInfo( command );
			}
		}
		else if( !strcasecmp( command, "remove" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				removeNetworkInfo( command );
			}
		}
		else if( !strcasecmp( command, "signon" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				serviceSignOn( command );
			}
		}
		else if( !strcasecmp( command, "signoff" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				serviceSignOff( command );
			}
		}
		else if( !strcasecmp( command, "logon" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				serviceLogOn( command );
			}
		}
		else if( !strcasecmp( command, "logoff" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				serviceLogOff( command );
			}
		}
		else if( !strcasecmp( command, "xchg" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				serviceKeyXchg( command );
			}
		}
		else if( !strcasecmp( command, "set" ) )
		{
			if( argc == 2 || argc == 3 )
			{
				printf("\n invaild command ..type help for more");
				return 1;
			}
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			memset( NetworkId, 0, sizeof( NetworkId ) );
			strcpy( NetworkId, command );
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 3 ] );
			if( !strcasecmp( command, "UP") )
				setNetworkStatus( NetworkId, NETWORK_STATUS_UP );
			else if( !strcasecmp( command, "DOWN") )
				setNetworkStatus( NetworkId, NETWORK_STATUS_DOWN );
			else if( !strcasecmp( command, "SAF") )
				setNetworkStatus( NetworkId, NETWORK_STATUS_SAF );
			else if( !strcasecmp( command, "SAFUPLOAD") )
				setNetworkStatus( NetworkId, NETWORK_STATUS_SAFUPLOAD );
			else if( !strcasecmp( command, "SAFDOWNLOAD") )
				NetworkStatus = NETWORK_STATUS_SAFDOWNLOAD;
			else
			{
				printf("\n invaild command ..type help for more");
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <set> <NetworkId> <up/down/saf/safupload/safdownload>");
			printf("\n <add> <NetworkId>");
			printf("\n <update> <NetworkId>");
			printf("\n <remove> <NetworkId>");
			printf("\n <signon> <NetworkId>");
			printf("\n <signoff> <NetworkId>");
			printf("\n <logon> <NetworkId>");
			printf("\n <logoff> <NetworkId>");
			printf("\n <xchg> <NetworkId>");
			printf("\n <list> <NetworkId>");
			printf("\n <list>");
		}
		else
		{
			printf("\n invaild command ..type help for more");
		}
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzNetCmd netcmdobj;
	if( netcmdobj.initNetCmd( argv[ 0 ] ) < 0 )
	{
		netcmdobj.trace( "^^^^^^^^^^^^^^^EzNetCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		netcmdobj.closeDebug();
		exit( 0 );
	}
	netcmdobj.serviceNetCmd( argc, argv );
	return 1;
}

