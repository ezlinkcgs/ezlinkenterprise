#include <ezbusiness/ezportupdater.h>

EzPortUpdater :: EzPortUpdater()
{

}

EzPortUpdater :: ~EzPortUpdater()
{
}

void EzPortUpdater :: initEzPortUpdater( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezportupdater.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzTaskUtil");
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzPortUpdater Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzChannelUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzPortUpdater Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( PORTUPDATERCHANNEL, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating EzPortUpdater Channel" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzPortUpdater Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing the EzDBUtil");
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzPortUpdater Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( DBConnect( ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Connecting the Database");
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzPortUpdater Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void EzPortUpdater :: ServiceRequest()
{
	int MsgSize, SqlErr;
	struct PortStatusDetails portstatus;
	char tempdate[7];
	int PortStatus;

	while( 1 )
	{
		dbUtilClose();
		trace( DEBUG_NORMAL,"PortUpdater Waiting for Service Request...." );

		memset( &portstatus, 0, sizeof( struct PortStatusDetails ) );
		if( ReadMessage( ( char * )&portstatus, &MsgSize ) >= 0 )
		{
			trace( DEBUG_NORMAL,"Received Request from channel[%s] for Port[%s]", GetLastSenderChannelName(), portstatus.PortId );
			memset( tempdate, 0, sizeof( tempdate ) );
			sprintf( tempdate, "%06d", portstatus.Date );

			dbUtilConnect();

			SqlErr = readPortStatus( portstatus.PortId, &PortStatus );
			if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
			{
				if( DBConnect() < 0 )
				{
					trace( "Error in Connecting with Database...." );
					continue;
				}
				SqlErr = readPortStatus( portstatus.PortId, &PortStatus );
			}

			if( SqlErr != 0 )
			{
				trace( "Error in Reading PortStatus for PortId[%s]..OraErr[%05d]", portstatus.PortId, SqlErr );
				continue;
			}

			if( PortStatus != portstatus.Status )
			{
				trace("updating the status");
				SqlErr =  updatePortStatus( portstatus.PortId, portstatus.Status, tempdate, portstatus.Time );
				if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
				{
					if( DBConnect() < 0 )
					{
						trace( "Error in Connecting with Database...." );
						continue;
					}
					SqlErr =  updatePortStatus( portstatus.PortId, portstatus.Status, tempdate, portstatus.Time );
				}
				if( SqlErr != 0 )
				{
					trace( DEBUG_ERROR,"Error in updating PortStatus for PortId[%s] OraErr[%05d]", portstatus.PortId, SqlErr );
					continue;
				}
			}

			SqlErr =  insertPortHist( portstatus.PortId, portstatus.Status, tempdate, portstatus.Time );
			if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
			{
				if( DBConnect() < 0 )
				{
					trace( "Error in Connecting with Database...." );
					continue;
				}
				SqlErr =  insertPortHist( portstatus.PortId, portstatus.Status, tempdate, portstatus.Time );
			}
			if( SqlErr != 0 )
			{
				trace( DEBUG_ERROR,"Error in Inserting PortStatus for PortId[%s] OraErr[%05d]", portstatus.PortId, SqlErr );
				continue;
			}
		}
	}
}

int EzPortUpdater :: readPortStatus( const char *PortId, int *PortStatus )
{
	int hPortStatus;
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
    sprintf( SqlStmt,  "SELECT PORTSTATUS FROM EZPORTCONNECTIONSTATUS WHERE RTRIM(PORTID)='%s';", PortId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( "SqlStmt<%s>", SqlStmt);
		trace( DEBUG_ERROR, "Error in Executing SqlStmt in readPortStatus [ %d ]", odbcret );
		//getNativeErrorCode();
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hPortStatus, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	*PortStatus = hPortStatus;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzPortUpdater :: updatePortStatus( const char *PortId, int Status, char *LogDate, int LogTime)
{
    char SqlStmt[ 255 ];
    char Input_date[ 10 ];

    memset( Input_date, 0, sizeof( Input_date ) );
    getMSSQLDateFmt( LogDate, Input_date);
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZPORTCONNECTIONSTATUS SET \
		PORTSTATUS=%d, \
		LOGDATE=convert(varchar,'%s',105), \
		LOGTIME=%d \
	WHERE RTRIM(PORTID)='%s';", Status, Input_date, LogTime, PortId );
    if( ExecuteQuery( SqlStmt, false ) < 0 )
    	return -1;
	return 0;
}

int EzPortUpdater :: insertPortHist( const char *PortId, int Status, char *LogDate, int LogTime )
{
    char SqlStmt[ 255 ];
    char Input_date[ 10 ];

    memset( Input_date, 0, sizeof( Input_date ) );
    getMSSQLDateFmt( LogDate, Input_date );

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "INSERT INTO EZPORTCONNECTIONHIST \
	(  \
		PORTID, \
		PORTSTATUS, \
		LOGDATE, \
		LOGTIME \
	) \
	VALUES\
	( '%s', %d, convert(varchar,'%s',105), %d );", PortId, Status, Input_date, LogTime );

    /*replace
     * to_date( '%s', 'dd-mm-yy' )
     * with
     * convert(varchar,'%s',105)
     */
    if( ExecuteQuery( SqlStmt, false ) < 0 )
    	return -1;
	return 0;
}

int main( int argc, char **argv )
{
	EzPortUpdater ezportupdater_obj;
	ezportupdater_obj.initEzPortUpdater( argv[ 0 ] );
	ezportupdater_obj.ServiceRequest();
	return 1;
}
