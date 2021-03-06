#include <ezlink/ezreplaycmd.h>

int EzReplayCmd :: initReplayCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezreplaycmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^^EzReplayCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		return -1;
	}

	if( createDummyChannel( "EzReplayCmd" ) < 0 )
	{
		trace( "Error in Creating Dummy Channel EzReplayCmd..." );
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

	ReplayMemoryId = LocateMemoryId( this, "REPLAYMEMORY" );

	if( ReplayMemoryId < 0 )
	{
		trace( "Error in Locating REPLAYMEMORY" );
		return -1;
	}

	ReplayShmid = shmget( ( key_t ) ReplayMemoryId, 0, IPC_CREAT | 0666 );
	if( ReplayShmid < 0 )
	{
		trace( "Error in getting Replay Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	replaytable_ptr = ( struct EzReplayTable * ) shmat( ReplayShmid, 0, 0 );

	if( replaytable_ptr == NULL )
	{
		trace( "Error in attaching Replay Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ReplaySemid = semget( ( key_t ) ReplayMemoryId, 0, IPC_CREAT | 0666 );
	if( ReplaySemid < 0 )
	{
		trace( "Error in getting Replay Semaphore...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		return -1;
	}
	return 1;
}

int EzReplayCmd :: searchReplayTable( const char *NetworkId )
{
	int retval;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( replaytable_ptr + i )->NetworkId, NetworkId ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzReplayCmd :: addNetworkReplay( const char *NetworkId )
{
	struct EzNetworkReplay networkreplay_rec;
	int retval;
	struct sembuf sem_buf;

	if( searchReplayTable( NetworkId ) >= 0 )
	{
		trace( DEBUG_ERROR, "Cannot add NetworkId[%s] in ReplayTable....NetworkId already exists...", NetworkId );
		return -1;
	}

	if( DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with Switch Database..." );
		return -1;
	}
	memset( &networkreplay_rec, 0, sizeof( struct EzNetworkReplay ) );
	retval = readEzNetworkReplay( NetworkId, &networkreplay_rec );
	if( retval != 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkReplay Table....SqlErr[%05d]", retval );
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

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( replaytable_ptr + i )->NetworkId, REPLAY_NETWORKID_INIT_VAL ) )
		{
			retval = 1;
			memset( ( replaytable_ptr + i ), 0, sizeof( struct EzReplayTable ) );
			strcpy( ( replaytable_ptr + i )->NetworkId, networkreplay_rec.NetworkId );
			( replaytable_ptr + i )->ReplayInterval = networkreplay_rec.ReplayInterval;
			( replaytable_ptr + i )->ReplayLookUpInterval = networkreplay_rec.ReplayLookUpInterval;
			( replaytable_ptr + i )->ReplayProperty = networkreplay_rec.ReplayProperty;
			( replaytable_ptr + i )->ReplayAction = networkreplay_rec.ReplayAction;
			( replaytable_ptr + i )->Status = REPLAY_NETWORK_RUNNING;
			( replaytable_ptr + i )->ReplayStatus = REPLAY_STATUS_IDLE;
			( replaytable_ptr + i )->ReplayFlag = REPLAY_FLAG_IDLE;
			( replaytable_ptr + i )->MsgTypeIndicator = REPLAY_MSGTYPEINDICATOR_INIT;
			sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzReplayCmd :: removeNetworkReplay( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

    for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( replaytable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            memset( ( replaytable_ptr + i )->NetworkId, 0, sizeof( ( replaytable_ptr + i )->NetworkId ) );
            strcpy( ( replaytable_ptr + i )->NetworkId, REPLAY_NETWORKID_INIT_VAL );
            sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzReplayCmd :: suspendNetworkReplay( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

    for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( replaytable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            ( replaytable_ptr + i )->Status = REPLAY_NETWORK_SUSPEND;
            sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzReplayCmd :: resumeNetworkReplay( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

    for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( replaytable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            ( replaytable_ptr + i )->Status = REPLAY_NETWORK_RUNNING;
            sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzReplayCmd :: updateNetworkReplay( const char *NetworkId )
{
	struct EzNetworkReplay networkreplay_rec;
	int retval;
	struct sembuf sem_buf;

	if( DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with Switch");
		return -1;
	}
	memset( &networkreplay_rec, 0, sizeof( struct EzNetworkReplay ) );
	retval = readEzNetworkReplay( NetworkId, &networkreplay_rec );
	if( retval != 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkReplay Table....SqlErr[%05d]", retval );
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

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( replaytable_ptr + i )->NetworkId, NetworkId ) )
		{
			retval = 1;
			( replaytable_ptr + i )->ReplayInterval = networkreplay_rec.ReplayInterval;
			( replaytable_ptr + i )->ReplayLookUpInterval = networkreplay_rec.ReplayLookUpInterval;
			( replaytable_ptr + i )->ReplayProperty = networkreplay_rec.ReplayProperty;
			( replaytable_ptr + i )->ReplayAction = networkreplay_rec.ReplayAction;
			sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzReplayCmd :: intimateNetworkReplay( const char *NetworkId )
{
	if( searchReplayTable( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Cannot Locate NetworkId[%s] in ReplayTable...", NetworkId );
		return -1;
	}

	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

	txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
	strcpy( txnmsg.NetworkId, NetworkId );

	if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Writing Initimate NetworkReplay Message to Channel[%s] for NetworkId[%s]", "EzSafReader", NetworkId );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Written Initimate NetworkReplay Message to Channel[%s] for NetworkId[%s]", "EzSafReader", NetworkId );
		return 1;
	}
}

int EzReplayCmd :: listNetworkReplay( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;
	char Status[ 50 ], ReplayStatus[ 50 ], ReplayFlag[ 20 ], MsgTypeIndicatorFlag[ 20 ];

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%16s%16s%16s%16s%16s%16s%16s%16s", "NetworkId", "ReplayInterval", "ReplayProperty", "ReplayAction", "Status", "ReplayStatus", "ReplayFlag", "MTypeIndicator" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}


        if( !strcmp( ( replaytable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            memset( Status, 0, sizeof( Status ) );
            memset( ReplayStatus, 0, sizeof( ReplayStatus ) );
            memset( ReplayFlag, 0, sizeof( ReplayFlag ) );
            memset( MsgTypeIndicatorFlag, 0, sizeof( MsgTypeIndicatorFlag ) );

            if( ( replaytable_ptr + i )->Status == REPLAY_NETWORK_RUNNING )
            	strcpy( Status, "RUNNING" );
            else
            	strcpy( Status, "SUSPENDED" );

            if( ( replaytable_ptr + i )->ReplayStatus == REPLAY_STATUS_ACTIVE )
            	strcpy( ReplayStatus, "ACTIVE" );
            else
            	strcpy( ReplayStatus, "IDLE" );

            if( ( replaytable_ptr + i )->ReplayFlag == REPLAY_FLAG_IDLE )
            	strcpy( ReplayFlag, "IDLE" );
			else
				strcpy( ReplayFlag, "ACTIVE" );

            if( ( replaytable_ptr + i )->MsgTypeIndicator == REPLAY_MSGTYPEINDICATOR_INIT )
				strcpy( MsgTypeIndicatorFlag, "IDLE" );
			else
				strcpy( MsgTypeIndicatorFlag, "DOWNLOAD" );

            printf( "\n%16s%16d%16c%16c%16s%16s%16s%16s", ( replaytable_ptr + i )->NetworkId, ( replaytable_ptr + i )->ReplayInterval, ( replaytable_ptr + i )->ReplayProperty, ( replaytable_ptr + i )->ReplayAction, Status, ReplayStatus, ReplayFlag, MsgTypeIndicatorFlag );
            sem_buf.sem_op = 2;
			if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
    return retval;
}

int EzReplayCmd :: listNetworkReplay()
{
	int retval = -1;
	struct sembuf sem_buf;
	char Status[ 50 ], ReplayStatus[ 50 ], ReplayFlag[ 20 ], MsgTypeIndicatorFlag[ 20 ];

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%16s%16s%16s%16s%16s%16s%16s%16s", "NetworkId", "ReplayInterval", "ReplayProperty", "ReplayAction", "Status", "ReplayStatus", "ReplayFlag", "MTypeIndicator" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( replaytable_ptr + i )->NetworkId, REPLAY_NETWORKID_INIT_VAL ) )
        {
			memset( Status, 0, sizeof( Status ) );
			memset( ReplayStatus, 0, sizeof( ReplayStatus ) );
			memset( MsgTypeIndicatorFlag, 0, sizeof( MsgTypeIndicatorFlag ) );
            if( ( replaytable_ptr + i )->Status == REPLAY_NETWORK_RUNNING )
            	strcpy( Status, "RUNNING" );
            else
            	strcpy( Status, "SUSPENDED" );

            if( ( replaytable_ptr + i )->ReplayStatus == REPLAY_STATUS_ACTIVE )
            	strcpy( ReplayStatus, "ACTIVE" );
            else
            	strcpy( ReplayStatus, "IDLE" );

            if( ( replaytable_ptr + i )->ReplayFlag == REPLAY_FLAG_IDLE )
				strcpy( ReplayFlag, "IDLE" );
			else
				strcpy( ReplayFlag, "ACTIVE" );

            if( ( replaytable_ptr + i )->MsgTypeIndicator == REPLAY_MSGTYPEINDICATOR_INIT )
				strcpy( MsgTypeIndicatorFlag, "IDLE" );
			else
				strcpy( MsgTypeIndicatorFlag, "DOWNLOAD" );

            printf( "\n%16s%16d%16c%16c%16s%16s%16s%16s", ( replaytable_ptr + i )->NetworkId, ( replaytable_ptr + i )->ReplayInterval, ( replaytable_ptr + i )->ReplayProperty, ( replaytable_ptr + i )->ReplayAction, Status, ReplayStatus, ReplayFlag, MsgTypeIndicatorFlag );
        }
    	sem_buf.sem_op = 2;
		if( semop( ReplaySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Replay Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
    return 1;
}

int EzReplayCmd :: readEzNetworkReplay( const char *I_NetworkId, struct EzNetworkReplay *eznetworkreplay_ptr )
{
	char NetworkId[ 17 ];
	int ReplayInterval;
	int ReplayLookUpInterval;
	char ReplayProperty;
	char ReplayAction;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcrt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    obdcrt = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", obdcrt );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(NETWORKID),\
		REPLAYINTERVAL,\
		REPLAYLOOKUPINTERVAL,\
		REPLAYPROPERTY,\
		REPLAYACTION FROM EZNETWORKREPLAY WHERE RTRIM(NETWORKID)='%s'", I_NetworkId );

    obdcrt = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in readSAFDBInfo [ %d ]", obdcrt );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKREPLAY [ %d ]", obdcrt );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    obdcrt = SQLBindCol( hstmt, 2, SQL_C_SLONG, &ReplayInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ReplayInterval) in EZNETWORKREPLAY [ %d ]", obdcrt );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    obdcrt = SQLBindCol( hstmt, 3, SQL_C_SLONG, &ReplayLookUpInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ReplayLookUpInterval) in EZNETWORKREPLAY [ %d ]", obdcrt );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    obdcrt = SQLBindCol( hstmt, 4, SQL_C_BINARY, &ReplayProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ReplayProperty) in EZNETWORKREPLAY [ %d ]", obdcrt );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    obdcrt = SQLBindCol( hstmt, 5, SQL_C_BINARY, &ReplayAction, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(ReplayAction) in EZNETWORKREPLAY [ %d ]", obdcrt );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    memset( NetworkId, 0, sizeof( NetworkId ) );
    if( (obdcrt = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( eznetworkreplay_ptr->NetworkId, NetworkId );
    	eznetworkreplay_ptr->ReplayInterval = ReplayInterval;
    	eznetworkreplay_ptr->ReplayLookUpInterval = ReplayLookUpInterval;
    	eznetworkreplay_ptr->ReplayProperty = ReplayProperty;
    	eznetworkreplay_ptr->ReplayAction = ReplayAction;
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzReplayCmd :: serviceReplayCmd( int argc, char **argv )
{
	char command[ 100 ];
	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezreplaycmd>");
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
					printf("\n invalid command ..type help for more");
					continue;
				}
				addNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "remove" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				removeNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "suspend" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				suspendNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "resume" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				resumeNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "intimate" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				intimateNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				updateNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					listNetworkReplay();
					continue;
				}
				listNetworkReplay( command );
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n <add> <NetworkId>");
				printf("\n <remove> <NetworkId>");
				printf("\n <suspend> <NetworkId>");
				printf("\n <resume> <NetworkId>");
				printf("\n <update> <NetworkId>");
				printf("\n <intimate> <NetworkId>");
				printf("\n <list> <NetworkId>");
				printf("\n <list>");
			}
			else if( !strcasecmp( command, "quit" ) )
				break;
			else
			{
				printf("\n invalid command ..type help for more");
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
				printf("\n invalid command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				addNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "remove" ) )
		{
			if( argc == 2 )
				printf("\n invalid command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				removeNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "suspend" ) )
		{
			if( argc == 2 )
				printf("\n invalid command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				suspendNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "resume" ) )
		{
			if( argc == 2 )
				printf("\n invalid command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				resumeNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "intimate" ) )
		{
			if( argc == 2 )
				printf("\n invalid command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				intimateNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "update" ) )
		{
			if( argc == 2 )
				printf("\n invalid command ..type help for more");
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				updateNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				listNetworkReplay();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				listNetworkReplay( command );
			}
		}
		else if( !strcasecmp( command, "help" ) )
		{
			printf("\n <add> <NetworkId>");
			printf("\n <remove> <NetworkId>");
			printf("\n <suspend> <NetworkId>");
			printf("\n <resume> <NetworkId>");
			printf("\n <update> <NetworkId>");
			printf("\n <intimate> <NetworkId>");
			printf("\n <list> <NetworkId>");
			printf("\n <list>");
		}
		else
		{
			printf("\n invalid command ..type help for more");
		}
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzReplayCmd replaycmdobj;
	if( replaycmdobj.initReplayCmd( argv[ 0 ] ) < 0 )
	{
		replaycmdobj.trace( "^^^^^^^^^^^^^^^EzNetCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		replaycmdobj.closeDebug();
		exit( 0 );
	}
	replaycmdobj.serviceReplayCmd( argc, argv );
	return 1;
}

