#include <ezlink/ezechocmd.h>

int EzEchoCmd :: initEchoCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezechocmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^EzEchoCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

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

	EchoMemoryId = LocateMemoryId( this, "ECHOMEMORY" );

	if( EchoMemoryId < 0 )
	{
		trace( "Error in Locating ECHOMEMORY" );
		return -1;
	}

	EchoShmid = shmget( ( key_t ) EchoMemoryId, 0, IPC_CREAT | 0666 );
	if( EchoShmid < 0 )
	{
		trace( "Error in getting Echo Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	echotable_ptr = ( struct EzEchoTable * ) shmat( EchoShmid, 0, 0 );

	if( echotable_ptr == NULL )
	{
		trace( "Error in attaching Echo Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EchoSemid = semget( ( key_t ) EchoMemoryId, 0, IPC_CREAT | 0666 );
	if( EchoSemid < 0 )
	{
		trace( "Error in getting Echo Semaphore...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil" );
		return -1;
	}
	return 1;
}

int EzEchoCmd :: searchNetworkEcho( const char *NetworkId )
{
	int retval = -1;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( !strcmp( ( echotable_ptr + i )->NetworkId, NetworkId ) )
		{
			retval = 1;
			break;
		}
	}
	return retval;
}

int EzEchoCmd :: addNetworkEcho( const char *NetworkId )
{
	struct EzNetworkEcho echotable_rec;
	struct sembuf sem_buf;

	int retval = -1;

	trace( DEBUG_NORMAL, "Adding NetworkId[%s] in EzEchoTable", NetworkId );

	if( searchNetworkEcho( NetworkId ) >= 0 )
	{
		trace( DEBUG_ERROR, "NetworkId[%s] is already added in EzEchoTable", NetworkId );
		return -1;
	}

	if( DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with Switch Database" );
		return -1;
	}

	memset( &echotable_rec, 0, sizeof( struct EzNetworkEcho ) );
	retval = readEzNetworkEcho( NetworkId, &echotable_rec );
	if( retval != 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkId[%s] from EzNetworkEcho Table....SqlErr[%05d]", retval );
		if( DBClose() < 0 )
			trace( DEBUG_ERROR, "Error in Closing Switch Database" );
		return -1;
	}

	if( DBClose() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Closing Switch Database" );
		return -1;
	}

	retval = -1;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( echotable_ptr + i )->NetworkId, ECHO_NETWORKID_INIT_VAL ) )
		{
			retval = 1;
			memset( ( echotable_ptr + i ), 0, sizeof( struct EzEchoTable ) );
			strcpy( ( echotable_ptr + i )->NetworkId, echotable_rec.NetworkId );
			//strcpy( ( echotable_ptr + i )->EchoPropertyId, echotable_rec.EchoPropertyId );
			( echotable_ptr + i )->EchoProperty = echotable_rec.EchoProperty;
			( echotable_ptr + i )->LogOnReq = echotable_rec.LogOnReq;
			( echotable_ptr + i )->Status = ECHO_THREAD_RUNNING;
			sem_buf.sem_op = 2;
			if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzEchoCmd :: removeNetworkEcho( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

    for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( echotable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            memset( ( echotable_ptr + i )->NetworkId, 0, sizeof( ( echotable_ptr + i )->NetworkId ) );
            strcpy( ( echotable_ptr + i )->NetworkId, ECHO_NETWORKID_INIT_VAL );
            sem_buf.sem_op = 2;
			if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzEchoCmd :: suspendNetworkEcho( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

    for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( echotable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            ( echotable_ptr + i )->Status = ECHO_THREAD_SUSPEND;
            sem_buf.sem_op = 2;
			if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzEchoCmd :: resumeNetworkEcho( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;

    for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( echotable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            ( echotable_ptr + i )->Status = ECHO_THREAD_RUNNING;
            sem_buf.sem_op = 2;
			if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzEchoCmd :: updateNetworkEcho( const char *NetworkId )
{
	int retval;
	struct EzNetworkEcho eznetworkecho_rec;
	struct sembuf sem_buf;

	if( DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with Switch Database...." );
		return -1;
	}

	memset( &eznetworkecho_rec, 0, sizeof( struct EzNetworkEcho ) );
	retval = readEzNetworkEcho( NetworkId, &eznetworkecho_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading NetworkId[%s] from EzNetworkEcho Table...SqlErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}

	if( DBClose() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Closing Switch Database...." );
		return -1;
	}

	retval = -1;

	for( int i = 0; i < MaxNetworks; i++ )
    {
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
        if( !strcmp( ( echotable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
           // memset( ( echotable_ptr + i )->EchoPropertyId, 0, sizeof( ( echotable_ptr + i )->EchoPropertyId ) );
            //strcpy( ( echotable_ptr + i )->EchoPropertyId, eznetworkecho_rec.EchoPropertyId );
            ( echotable_ptr + i )->EchoProperty = eznetworkecho_rec.EchoProperty;
            ( echotable_ptr + i )->LogOnReq = eznetworkecho_rec.LogOnReq;
            sem_buf.sem_op = 2;
			if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
            break;
        }
		sem_buf.sem_op = 2;
		if( semop( EchoSemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop Operation...for Echo Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
    return retval;
}

int EzEchoCmd :: listNetworkEcho( const char *NetworkId )
{
	int retval = -1;
	char StatusStr[ 20 ], RespStatusStr[ 50 ];

	printf( "\n%16s%16s%16s%16s%10s%20s", "NetworkId", "Property", "EchoInterval", "Status", "LogOnReq", "EchoRespStatus" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	for( int i = 0; i < MaxNetworks; i++ )
    {
	     if( !strcmp( ( echotable_ptr + i )->NetworkId, NetworkId ) )
        {
            retval = 1;
            memset( StatusStr, 0, sizeof( StatusStr ) );
            if( ( echotable_ptr + i )->Status == ECHO_THREAD_RUNNING )
            	strcpy( StatusStr, "RUNNING" );
            else
            	strcpy( StatusStr, "SUSPENDED" );

            memset( RespStatusStr, 0, sizeof( RespStatusStr ) );
            if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_INIT )
            	strcpy( RespStatusStr, "RESP_STATUS_INIT" );
            else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_LOGON_SENT )
            	strcpy( RespStatusStr, "RESP_STATUS_LOGON_SENT" );
            else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_LOGON_RCVD )
				strcpy( RespStatusStr, "RESP_STATUS_LOGON_RCVD" );
            else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_SIGNON_SENT )
				strcpy( RespStatusStr, "RESP_STATUS_SIGNON_SENT" );
            else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_SIGNON_RCVD )
				strcpy( RespStatusStr, "RESP_STATUS_SIGNON_RCVD" );
            else
            	strcpy( RespStatusStr, "RESP_STATUS_INIT" );

            printf( "\n%16s%16c%16d%16s%10c%20s", ( echotable_ptr + i )->NetworkId, ( echotable_ptr + i )->EchoProperty, ( echotable_ptr + i )->EchoInterval, StatusStr, ( echotable_ptr + i )->LogOnReq, RespStatusStr );
            break;
        }
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
    return retval;
}

int EzEchoCmd :: listNetworkEcho()
{
	int retval = -1;
	char StatusStr[ 20 ], RespStatusStr[ 50 ];
	printf( "\n%16s%16s%16s%16s%10s%20s", "NetworkId", "Property", "EchoInterval", "Status", "LogOnReq", "EchoRespStatus" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworks; i++ )
    {
		if ( strcmp( ( echotable_ptr + i )->NetworkId, ECHO_NETWORKID_INIT_VAL ) )
		{
			memset( StatusStr, 0, sizeof( StatusStr ) );
			if( ( echotable_ptr + i )->Status == ECHO_THREAD_RUNNING )
				strcpy( StatusStr, "RUNNING" );
			else
				strcpy( StatusStr, "SUSPENDED" );

			memset( RespStatusStr, 0, sizeof( RespStatusStr ) );
			if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_INIT )
				strcpy( RespStatusStr, "RESP_STATUS_INIT" );
			else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_LOGON_SENT )
				strcpy( RespStatusStr, "RESP_STATUS_LOGON_SENT" );
			else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_LOGON_RCVD )
				strcpy( RespStatusStr, "RESP_STATUS_LOGON_RCVD" );
			else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_SIGNON_SENT )
				strcpy( RespStatusStr, "RESP_STATUS_SIGNON_SENT" );
			else if( ( echotable_ptr + i )->EchoRespStatus == ECHO_RESP_STATUS_SIGNON_RCVD )
				strcpy( RespStatusStr, "RESP_STATUS_SIGNON_RCVD" );
			else
				strcpy( RespStatusStr, "RESP_STATUS_INIT" );

			printf( "\n%16s%16c%16d%16s%10c%20s", ( echotable_ptr + i )->NetworkId, ( echotable_ptr + i )->EchoProperty, ( echotable_ptr + i )->EchoInterval, StatusStr, ( echotable_ptr + i )->LogOnReq, RespStatusStr );
		}
    }
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
    return 1;
}

int EzEchoCmd :: serviceEchoCmd( int argc, char **argv )
{
	char command[ 100 ];
	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezechocmd>");
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
				addNetworkEcho( command );
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
				removeNetworkEcho( command );
				continue;
			}
			else if( !strcasecmp( command, "suspend" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				suspendNetworkEcho( command );
				continue;
			}
			else if( !strcasecmp( command, "resume" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				resumeNetworkEcho( command );
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
				updateNetworkEcho( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					listNetworkEcho();
					continue;
				}
				listNetworkEcho( command );
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n <add> <NetworkId>");
				printf("\n <remove> <NetworkId>");
				printf("\n <suspend> <NetworkId>");
				printf("\n <resume> <NetworkId>");
				printf("\n <update> <NetworkId>");
				printf("\n <list> <NetworkId>");
				printf("\n <list>");
			}
			else if( !strcmp( command, "quit" ) )
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
			if( argc != 3 )
			{
				printf("\n invaild command ..type help for more");
				return -1;
			}
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			addNetworkEcho( command );
		}
		else if( !strcasecmp( command, "remove" ) )
		{
			if( argc != 3 )
			{
				printf("\n invaild command ..type help for more");
				return -1;
			}
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			removeNetworkEcho( command );
		}
		else if( !strcasecmp( command, "suspend" ) )
		{
			if( argc != 3 )
			{
				printf("\n invaild command ..type help for more");
				return -1;
			}
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			suspendNetworkEcho( command );
		}
		else if( !strcasecmp( command, "resume" ) )
		{
			if( argc != 3 )
			{
				printf("\n invaild command ..type help for more");
				return -1;
			}
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			resumeNetworkEcho( command );
		}
		else if( !strcasecmp( command, "update" ) )
		{
			if( argc != 3 )
			{
				printf("\n invaild command ..type help for more");
				return -1;
			}
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			updateNetworkEcho( command );
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				listNetworkEcho();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				listNetworkEcho( command );
			}
			printf("\n" );
		}
		else if( !strcasecmp( command, "help" ) )
		{
			printf("\n <add> <NetworkId>");
			printf("\n <remove> <NetworkId>");
			printf("\n <suspend> <NetworkId>");
			printf("\n <resume> <NetworkId>");
			printf("\n <update> <NetworkId>");
			printf("\n <list> <NetworkId>");
			printf("\n <list>");
		}
		else
		{
			printf("\n invaild command ..type help for more");
		}
	}
}

int EzEchoCmd :: readEzNetworkEcho( const char *I_NetworkId, struct EzNetworkEcho *eznetworkecho_ptr )
{
    char NetworkId[ 17 ];
    char EchoPropertyId[ 17 ];
    char EchoProperty;
    char LogOnReq;
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
    sprintf( SqlStmt,  "SELECT \
        RTRIM(NETWORKID), \
        RTRIM(ECHOPROPERTYID), \
        ECHOPROPERTY, \
        LOGONREQ \
    FROM EZNETWORKECHO WHERE RTRIM(NETWORKID)='%s'", I_NetworkId );

    obdcrt = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzNetworkEcho [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );

    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKECHO [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    obdcrt = SQLBindCol( hstmt, 2, SQL_C_CHAR, EchoPropertyId, sizeof(EchoPropertyId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(EchoPropertyId) in EZNETWORKECHO [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    obdcrt = SQLBindCol( hstmt, 3, SQL_C_BINARY, &EchoProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(EchoProperty) in EZNETWORKECHO [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    obdcrt = SQLBindCol( hstmt, 4, SQL_C_BINARY, &LogOnReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(LogOnReq) in EZNETWORKECHO [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    if( (obdcrt = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( eznetworkecho_ptr->NetworkId, NetworkId );
        strcpy( eznetworkecho_ptr->EchoPropertyId, EchoPropertyId );
        eznetworkecho_ptr->EchoProperty = EchoProperty;
    	eznetworkecho_ptr->LogOnReq = LogOnReq;
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzEchoCmd :: readEzEchoProperty( const char *I_EchoPropertyId, struct EzEchoProperty *ezechoproperty_ptr )
{
    char EchoPropertyId[ 17 ];
    int EchoInterval;
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
    sprintf( SqlStmt,  "SELECT \
        RTRIM(ECHOPROPERTYID), \
        ECHOINTERVAL \
    	FROM EZECHOPROPERTY WHERE RTRIM(ECHOPROPERTYID)='%s'", I_EchoPropertyId );

    obdcrt = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzEchoProperty [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, EchoPropertyId, sizeof(EchoPropertyId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(EchoPropertyId) in EZECHOPROPERTY [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    obdcrt = SQLBindCol( hstmt, 2, SQL_C_SLONG, &EchoInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(EchoInterval) in EZECHOPROPERTY [ %d ]", obdcrt );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }


    if( (obdcrt = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ezechoproperty_ptr->EchoPropertyId, EchoPropertyId );
        ezechoproperty_ptr->EchoInterval = EchoInterval;
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int main( int argc, char **argv )
{
	EzEchoCmd echocmdobj;
	if( echocmdobj.initEchoCmd( argv[ 0 ] ) < 0 )
	{
		echocmdobj.trace( "^^^^^^^^^^^^^^^EzEchoCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		echocmdobj.closeDebug();
		exit( 0 );
	}
	echocmdobj.serviceEchoCmd( argc, argv );
	return 1;
}

