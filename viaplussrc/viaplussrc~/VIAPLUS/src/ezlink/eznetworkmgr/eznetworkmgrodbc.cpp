/*
 * eznetworkmgrodbc.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: mohanraj
 */

#include <ezlink/eznetworkmgrodbc.h>

int EzNetworkMgrODBC :: initEzNetworkMgrODBC( const char *TaskName, EzDebugUtil *dptr )
{
	this->dptr = dptr;	
	if( initODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Initializing the EzODBCUtil");
		return -1;
	}

	if( DBConnect( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzNetworkMgrODBC :: getEzNetworkCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];
    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZNETWORK" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZNETWORK - Count[%d]", count);
    return count;
}

int EzNetworkMgrODBC :: LoadEzNetwork( struct EzNetworkMemory *eznetwork_ptr, int *SqlErr )
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
    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
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
    FROM EZNETWORK;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace("<%s>", SqlStmt);
        dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetwork [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, NetworkName, sizeof(NetworkName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkName) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, NetworkPropertyId, sizeof(NetworkPropertyId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkPropertyId) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &TimeOut, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(TimeOut) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, PortName, sizeof(PortName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(PortName) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &NetworkStatus, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkStatus) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &KeyReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(KeyReq) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_BINARY, &CutOverReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverReq) in EZNETWORK [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( eznetwork_ptr + i ), 0, sizeof( struct EzNetworkMemory ) );

         strcpy( ( eznetwork_ptr + i )->NetworkId, NetworkId );
         strcpy( ( eznetwork_ptr + i )->NetworkName, NetworkName );
         strcpy( ( eznetwork_ptr + i )->NetworkPropertyId, NetworkPropertyId );
         ( eznetwork_ptr + i )->TimeOut = TimeOut;
         strcpy( ( eznetwork_ptr + i )->ChannelName, ChannelName );
         strcpy( ( eznetwork_ptr + i )->PortName, PortName );
         strcpy( ( eznetwork_ptr + i )->InstId, InstId );
         if( NetworkStatus == NETWORK_STATUS_UP )
         	( eznetwork_ptr + i )->NetworkStatus = NETWORK_STATUS_DOWN;
         else
         	( eznetwork_ptr + i )->NetworkStatus = NetworkStatus;
         ( eznetwork_ptr + i )->KeyReq = KeyReq;
         ( eznetwork_ptr + i )->CutOverReq = CutOverReq;
 		i++;
		memset( NetworkId, 0, sizeof( NetworkId ) );
		memset( NetworkName, 0, sizeof( NetworkName ) );
		memset( NetworkPropertyId, 0, sizeof( NetworkPropertyId ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( PortName, 0, sizeof( PortName ) );
		memset( InstId, 0, sizeof( InstId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzNetworkMgrODBC :: getEzNetworkReplayCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];
    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZNETWORKREPLAY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZNETWORKREPLAY - Count[%d]", count);
    return count;
}

int EzNetworkMgrODBC :: LoadEzNetworkReplay( struct EzNetworkReplay *eznetworkreplay_ptr, int *SqlErr )
{
	char NetworkId[ 17 ];
	int ReplayInterval;
	int ReplayLookUpInterval;
	char ReplayProperty;
	char ReplayAction;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(NETWORKID), \
		REPLAYINTERVAL, \
		REPLAYLOOKUPINTERVAL, \
		REPLAYPROPERTY, \
		REPLAYACTION  \
	FROM EZNETWORKREPLAY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace("<%s>", SqlStmt);
        dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkReplay [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &ReplayInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayInterval) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &ReplayLookUpInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayLookUpInterval) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &ReplayProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayProperty) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &ReplayAction, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayAction) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( eznetworkreplay_ptr + i ), 0, sizeof( struct EzNetworkReplay ) );
		strcpy( ( eznetworkreplay_ptr + i )->NetworkId, NetworkId );
		( eznetworkreplay_ptr + i )->ReplayInterval = ReplayInterval;
		( eznetworkreplay_ptr + i )->ReplayLookUpInterval = ReplayLookUpInterval;
		( eznetworkreplay_ptr + i )->ReplayProperty = ReplayProperty;
		( eznetworkreplay_ptr + i )->ReplayAction = ReplayAction;
		i++;
		memset( NetworkId, 0, sizeof( NetworkId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzNetworkMgrODBC :: getEzNetworkEchoCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];
    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZNETWORKECHO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZNETWORKECHO - Count[%d]", count);
    return count;
}

int EzNetworkMgrODBC :: LoadEzNetworkEcho( struct EzEchoTable *ezechotable_ptr, int *SqlErr )
{
 	char NetworkId[ 17 ];
	char EchoProperty;
	char LogOnReq;
	int EchoInterval;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
            RTRIM(NETWORKID), \
            ECHOPROPERTY, \
            LOGONREQ, \
            ECHOINTERVAL \
    FROM EZNETWORKECHO;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace("<%s>", SqlStmt);
        dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkReplay [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &EchoProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayInterval) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_BINARY, &LogOnReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayLookUpInterval) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &EchoInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(ReplayProperty) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( ezechotable_ptr + i ), 0, sizeof( struct EzEchoTable ) );
        strcpy( ( ezechotable_ptr + i )->NetworkId, NetworkId );
      	( ezechotable_ptr + i )->EchoProperty = EchoProperty;
        ( ezechotable_ptr + i )->LogOnReq = LogOnReq;
        ( ezechotable_ptr + i )->EchoInterval = EchoInterval;
        ( ezechotable_ptr + i )->Status = ECHO_THREAD_RUNNING;
        i++;
		memset( NetworkId, 0, sizeof( NetworkId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzNetworkMgrODBC :: getEzNetworkBusDayCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];
    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZNETWORKBUSDAY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZNETWORKBUSDAY - Count[%d]", count);
    return count;
	return 1;
}

int EzNetworkMgrODBC :: LoadEzNetworkBusDay( struct EzNetworkBusDay *eznetworkbusday_ptr, int *SqlErr )
{
	char NetworkId[ 17 ];
	char CutOverUseFlag;
	int CutOverDate;
	int CutOverTime;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(NETWORKID), \
		CUTOVERUSEFLAG, \
		CUTOVERDATE, \
		CUTOVERTIME \
	FROM EZNETWORKBUSDAY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace("<%s>", SqlStmt);
        dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkReplay [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &CutOverUseFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverUseFlag) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &CutOverDate, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverDate) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &CutOverTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
        dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverTime) in EZNETWORKREPLAY [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( eznetworkbusday_ptr + i ), 0, sizeof( struct EzNetworkBusDay ) );
		strcpy( ( eznetworkbusday_ptr + i )->NetworkId, NetworkId );
		( eznetworkbusday_ptr + i )->CutOverUseFlag = CutOverUseFlag;
		( eznetworkbusday_ptr + i )->CutOverDate = CutOverDate;
		( eznetworkbusday_ptr + i )->CutOverTime = CutOverTime;
		i++;
		memset( NetworkId, 0, sizeof( NetworkId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzNetworkMgrODBC :: updateEzNetworkStatus( const char *I_NetworkId, int I_NetworkStatus, int *SqlErr )
{
    char SqlStmt[ 255 ];
    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZNETWORK SET NETWORKSTATUS=%d WHERE RTRIM(NETWORKID)=%s;", I_NetworkStatus, I_NetworkId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzNetworkMgrODBC :: updateEzNetworkBusDay( const char *I_NetworkId, int I_CutOverDate, int *SqlErr )
{
    char SqlStmt[ 255 ];
    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZNETWORKBUSDAY SET CUTOVERDATE=%d WHERE RTRIM(NETWORKID)=%s;", I_CutOverDate, I_NetworkId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 1;
}
