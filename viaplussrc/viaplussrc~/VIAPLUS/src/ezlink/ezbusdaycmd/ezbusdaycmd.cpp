#include <ezlink/ezbusdaycmd.h>

int EzBusDayCmd :: initBusDayCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezbusdaycmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^EzBusDayCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( initBusDayUtil( this ) < 0 )
	{
		trace( "Error in Initializing BusDayUtil...." );
		return -1;
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing ..." );
		return -1;
	}

	return 1;
}

int EzBusDayCmd :: printHelp()
{
	printf("\n <set-date> <NetworkId> <DDMMYY>" );
	printf("\n <add> <NetworkId>");
	printf("\n <update> <NetworkId>");
	printf("\n <remove> <NetworkId>");
	printf("\n <list> <NetworkId>");
	printf("\n <list>");
	return 1;
}

int EzBusDayCmd :: serviceAddBusDayCmd( const char *NetworkId )
{
	struct EzBusDayTable busdaytable_rec;
	struct EzNetworkBusDay networkbusday_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch DB..." );
		return -1;
	}
	memset( &networkbusday_rec, 0, sizeof( struct EzNetworkBusDay ) );
	retval = readEzNetworkBusDay( NetworkId, &networkbusday_rec );
	if( retval != 0 )
	{
		printf("\nError in reading NetworkId[%s] from EzNetworkBusDay....OraErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}
	DBClose();
	memset( &busdaytable_rec, 0, sizeof( EzBusDayTable ) );
	strcpy( busdaytable_rec.NetworkId, networkbusday_rec.NetworkId );
	busdaytable_rec.CutOverUseFlag = networkbusday_rec.CutOverUseFlag;
	busdaytable_rec.CutOverDate = networkbusday_rec.CutOverDate;
	busdaytable_rec.CutOverTime = networkbusday_rec.CutOverTime;

	if( addNetworkBusDayMemory( busdaytable_rec ) < 0 )
	{
		printf("\nError in adding NetworkId[%s] in BusDayMemory....", NetworkId );
		return -1;
	}
	return 1;
}

int EzBusDayCmd :: serviceUpdateBusDayCmd( const char *NetworkId )
{
	struct EzBusDayTable busdaytable_rec;
	struct EzNetworkBusDay networkbusday_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch DB..." );
		return -1;
	}
	memset( &networkbusday_rec, 0, sizeof( struct EzNetworkBusDay ) );
	retval = readEzNetworkBusDay( NetworkId, &networkbusday_rec );
	if( retval != 0 )
	{
		printf("\nError in reading NetworkId[%s] from EzNetworkBusDay....OraErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	memset( &busdaytable_rec, 0, sizeof( EzBusDayTable ) );
	strcpy( busdaytable_rec.NetworkId, networkbusday_rec.NetworkId );
	busdaytable_rec.CutOverUseFlag = networkbusday_rec.CutOverUseFlag;
	busdaytable_rec.CutOverDate = networkbusday_rec.CutOverDate;
	busdaytable_rec.CutOverTime = networkbusday_rec.CutOverTime;

	if( updateNetworkBusDayMemory( busdaytable_rec ) < 0 )
	{
		printf("\nError in Updating NetworkId[%s] in BusDayMemory....", NetworkId );
		return -1;
	}
	return 1;
}

int EzBusDayCmd :: serviceRemoveBusDayCmd( const char *NetworkId )
{
	struct EzBusDayTable busdaytable_rec;

	if( deleteNetworkBusDayMemory( NetworkId ) < 0 )
	{
		printf("\nError in removing NetworkId[%s] from BusDayMemory....", NetworkId );
		return -1;
	}

	return 1;
}

int EzBusDayCmd :: CheckInteger( const char *IntStr )
{
	for( int i = 0; i < strlen( IntStr ); i++ )
    {
        if( ( IntStr[ i ] < 48 ) || ( IntStr[ i ] > 57 ) )
                return -1;
    }
    return 1;
}

bool EzBusDayCmd :: isValidDate( const char *datestr )
{
	char ddstr[ 3 ], mmstr[ 3 ], yystr[ 3 ];

	if( strlen( datestr ) != 6 )
		return false;

	if( CheckInteger( datestr ) < 0 )
		return false;

	memset( ddstr, 0, sizeof( ddstr ) );
	strncpy( ddstr, datestr, 2 );
	memset( mmstr, 0, sizeof( mmstr ) );
	strncpy( mmstr, datestr + 2, 2 );
	memset( yystr, 0, sizeof( yystr ) );
	strncpy( yystr, datestr + 4, 2 );

	if( atoi( mmstr ) < 1 || atoi( mmstr ) > 12 )
		return false;

	if( atoi( mmstr ) == 2 && ( atoi( yystr ) % 4 == 0 ) )
	{
		if( atoi( ddstr ) < 1 || atoi( ddstr ) > 29 )
			return false;
	}
	else if( atoi( mmstr ) == 2 )
	{
		if( atoi( ddstr ) < 1 || atoi( ddstr ) > 28 )
			return false;
	}

	if( atoi( mmstr ) == 1 || atoi( mmstr ) == 3 || atoi( mmstr ) == 5 || atoi( mmstr ) == 7 || atoi( mmstr ) == 8 || atoi( mmstr ) == 10 || atoi( mmstr ) == 12 )
	{
		if( atoi( ddstr ) < 1 || atoi( ddstr ) > 31 )
			return false;
	}
	else
	{
		if( atoi( ddstr ) < 1 || atoi( ddstr ) > 30 )
			return false;
	}

	return true;
}

int EzBusDayCmd :: serviceSetBusDate( const char *NetworkId, const char *datestr )
{
	if( !isValidDate( datestr ) )
	{
		printf("\n[%s] is not a valid Business Date....", datestr );
		return -1;
	}

	struct EzBusDayTable busdaytable_rec;
	int retval;

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch DB..." );
		return -1;
	}

	retval = updateBusDate( NetworkId, datestr );
	if( retval != 0 )
	{
		printf("\nError in updating Business Date[%s] for NetworkId[%s] in EzNetworkBusDay....OraErr[%05d]", datestr, NetworkId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateCutOverDate( NetworkId, atoi( datestr ) ) < 0 )
	{
		printf("\nError in updating Business Date[%s] for NetworkId[%s] in BusDayMemory....", datestr, NetworkId );
		return -1;
	}

	return 1;
}

int EzBusDayCmd ::serviceListBusDayCmd( const char *NetworkId )
{
	struct sembuf sem_buf;
	char NetworkStatusStr[ 50 ];
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%15s%15s%15s", "NetworkId", "CutOverUseFlag", "CutOverDate", "CutOverTime" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < BusDay_MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkBusSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkBusDayMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( NetworkId, ( NetworkBusShmPtr + i )->NetworkId ) )
		{
			retval = 1;
			printf( "\n%20s%15c%15d%15d", ( NetworkBusShmPtr + i )->NetworkId, ( NetworkBusShmPtr + i )->CutOverUseFlag, ( NetworkBusShmPtr + i )->CutOverDate, ( NetworkBusShmPtr + i )->CutOverTime );
			sem_buf.sem_op = 2;
			if( semop( NetworkBusSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkBusDayMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkBusSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkBusDayMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return retval;
}

int EzBusDayCmd ::serviceListBusDayCmd()
{
	struct sembuf sem_buf;
	char NetworkStatusStr[ 50 ];
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%15s%15s%15s", "NetworkId", "CutOverUseFlag", "CutOverDate", "CutOverTime" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < BusDay_MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkBusSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkBusDayMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( NetworkBusShmPtr + i )->NetworkId, BUSDAY_NETWORKID_INIT_VAL ) )
		{
			retval = 1;
			printf( "\n%20s%15c%15d%15d", ( NetworkBusShmPtr + i )->NetworkId, ( NetworkBusShmPtr + i )->CutOverUseFlag, ( NetworkBusShmPtr + i )->CutOverDate, ( NetworkBusShmPtr + i )->CutOverTime );
		}

		sem_buf.sem_op = 2;
		if( semop( NetworkBusSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkBusDayMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n" );
	return retval;
}


int EzBusDayCmd :: serviceBusDayCmd( int argc, char **argv )
{
	char command[ 100 ], NetworkId[ 17 ], datestr[ 50 ];

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezbusdaycmd>");
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
				serviceAddBusDayCmd( command );
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
				serviceUpdateBusDayCmd( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					serviceListBusDayCmd();
					continue;
				}
				serviceListBusDayCmd( command );
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
				serviceRemoveBusDayCmd( command );
				continue;
			}
			else if( !strcasecmp( command, "set-date" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( datestr, 0, sizeof( datestr ) );
				getCommand( datestr, 3 );
				if( strlen( datestr ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				serviceSetBusDate( command, datestr );
				continue;
			}
			else if( !strcmp( command, "help" ) )
				printHelp();
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
				serviceAddBusDayCmd( command );
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
				serviceUpdateBusDayCmd( command );
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if ( argc == 2 )
				serviceListBusDayCmd();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				serviceListBusDayCmd( command );
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
				serviceRemoveBusDayCmd( command );
			}
		}
		else if( !strcasecmp( command, "set-date" ) )
		{
			if( argc == 2 || argc == 3 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				memset( datestr, 0, sizeof( datestr ) );
				strcpy( datestr, argv[ 3 ] );
				serviceSetBusDate( command, datestr );
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printHelp();
		}
		else
		{
			printf("\n invaild command ..type help for more");
		}
	}
	return 1;
}

int EzBusDayCmd :: readEzNetworkBusDay( const char *I_NetworkId, struct EzNetworkBusDay *eznetworkbusday_ptr )
{
	char NetworkId[ 17 ];
	char CutOverUseFlag;
	char CutOverDate[ 11 ];
	char tempdate[ 11 ];
	int CutOverTime;
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

    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt,  "SELECT \
			RTRIM(NETWORKID), \
			CUTOVERUSEFLAG, \
			convert(varchar, CUTOVERDATE, 4 ), \
			CUTOVERTIME \
		FROM EZNETWORKBUSDAY WHERE RTRIM(NETWORKID)='%s';", I_NetworkId );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("<%s>", SqlStmt);
		trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzNetworkBusDay [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( NetworkId, 0, sizeof( NetworkId ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &CutOverUseFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CutOverUseFlag) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, CutOverDate, sizeof(CutOverDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CutOverDate) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &CutOverTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(CutOverTime) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( eznetworkbusday_ptr, 0, sizeof( struct EzNetworkBusDay ) );

    	strcpy( eznetworkbusday_ptr->NetworkId, NetworkId );
    	eznetworkbusday_ptr->CutOverUseFlag = CutOverUseFlag;
        if( !strcasecmp( DBType, SQLSERVER ) )
        {
        	memset( tempdate, 0, sizeof( tempdate ) );
        	getSwitchDateFmt( CutOverDate, "DDMMYY", tempdate );
        	eznetworkbusday_ptr->CutOverDate = atoi(tempdate);
        }
    	eznetworkbusday_ptr->CutOverTime = CutOverTime;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzBusDayCmd :: updateBusDate( const char *I_NetworkId, const char *I_DateStr )
{
    char SqlStmt[ 255 ];
    char Input_date[ 10 ];

    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( Input_date, 0, sizeof( Input_date ) );
		getMSSQLDateFmt( I_DateStr, Input_date);
    	memset( SqlStmt, 0, sizeof( SqlStmt ) );
    	sprintf( SqlStmt, "UPDATE EZNETWORKBUSDAY SET CUTOVERDATE=convert(varchar,'%s',105) WHERE RTRIM(NETWORKID)='%s';", Input_date, I_NetworkId );
    }
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int main( int argc, char **argv )
{
	EzBusDayCmd busdaycmdobj;
	if( busdaycmdobj.initBusDayCmd( argv[ 0 ] ) < 0 )
	{
		busdaycmdobj.trace( "^^^^^^^^^^^^^^^EzBusDayCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		busdaycmdobj.closeDebug();
		exit( 0 );
	}
	busdaycmdobj.serviceBusDayCmd( argc, argv );
	return 1;
}

