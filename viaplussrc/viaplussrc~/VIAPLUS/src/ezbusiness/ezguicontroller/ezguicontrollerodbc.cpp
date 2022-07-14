/*
 * EzGuiControllerODBCodbc.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: mohanraj
 */

#include <ezbusiness/ezguicontrollerodbc.h>

int EzGuiControllerODBC :: initEzGuiControllerODBC( const char *TaskName, EzDebugUtil *dptr )
{
	this->dptr = dptr;
	if( initODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Initializing the EzODBCUtil");
		return -1;
	}
	return 1;
}

int EzGuiControllerODBC :: ConnectDB()
{
	if( DBConnect( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzGuiControllerODBC :: CloseDB()
{
	if( DBClose( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Dis-Connecting the Database");
		return -1;
	}
	return 1;
}

int EzGuiControllerODBC :: readEzNetwork( const char *I_NetworkId, struct EzNetwork *eznetwork_ptr )
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
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
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
		dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetwork [ %d ]", odbcret );
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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( eznetwork_ptr, 0, sizeof( struct EzNetwork ) );

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

int EzGuiControllerODBC :: readEzNetworkEcho( const char *I_NetworkId, struct EzNetworkEcho *eznetworkecho_ptr )
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
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", obdcrt );
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
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzNetworkEcho [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );

    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKECHO [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 2, SQL_C_CHAR, EchoPropertyId, sizeof(EchoPropertyId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EchoPropertyId) in EZNETWORKECHO [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 3, SQL_C_BINARY, &EchoProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EchoProperty) in EZNETWORKECHO [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 4, SQL_C_BINARY, &LogOnReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LogOnReq) in EZNETWORKECHO [ %d ]", obdcrt );
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

int EzGuiControllerODBC :: readEzNetworkReplay( const char *I_NetworkId, struct EzNetworkReplay *eznetworkreplay_ptr )
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
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", obdcrt );
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
    	dptr->trace(DEBUG_ERROR, "Error in Executing SqlStmt in readSAFDBInfo [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace(DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKREPLAY [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 2, SQL_C_SLONG, &ReplayInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace(DEBUG_ERROR, "Error in Binding Column(ReplayInterval) in EZNETWORKREPLAY [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 3, SQL_C_SLONG, &ReplayLookUpInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace(DEBUG_ERROR, "Error in Binding Column(ReplayLookUpInterval) in EZNETWORKREPLAY [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 4, SQL_C_BINARY, &ReplayProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace(DEBUG_ERROR, "Error in Binding Column(ReplayProperty) in EZNETWORKREPLAY [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 5, SQL_C_BINARY, &ReplayAction, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace(DEBUG_ERROR, "Error in Binding Column(ReplayAction) in EZNETWORKREPLAY [ %d ]", obdcrt );
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

int EzGuiControllerODBC :: readEzNetworkBusDay( const char *I_NetworkId, struct EzNetworkBusDay *eznetworkbusday_ptr )
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
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
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
		dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzNetworkBusDay [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( NetworkId, 0, sizeof( NetworkId ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &CutOverUseFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverUseFlag) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, CutOverDate, sizeof(CutOverDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverDate) in EZNETWORKBUSDAY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &CutOverTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CutOverTime) in EZNETWORKBUSDAY [ %d ]", odbcret );
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

int EzGuiControllerODBC :: readEzEchoProperty( const char *I_EchoPropertyId, struct EzEchoProperty *ezechoproperty_ptr )
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
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", obdcrt );
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
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzEchoProperty [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
    obdcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, EchoPropertyId, sizeof(EchoPropertyId), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EchoPropertyId) in EZECHOPROPERTY [ %d ]", obdcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    obdcrt = SQLBindCol( hstmt, 2, SQL_C_SLONG, &EchoInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( obdcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EchoInterval) in EZECHOPROPERTY [ %d ]", obdcrt );
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

int EzGuiControllerODBC :: readEzSecurityTable( const char *I_SecurityId, struct EzSecurity *ezsecurity_rec )
{
	char SecurityId[ 11 ];
	char PINVerificationMethod;
	char EPVK[ 65 ];
	char DecimilizationTable[ 17 ];
	char PINPadChar;
	char PANPadChar;
	short PINLen;
	short PANLen;
	short PANValidationOffset;
	char PINBlockFormat[ 3 ];
	short PANValidationLength;
	char CVKA[ 65 ];
	char CVKB[ 65 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(SECURITYID), \
        PINVERIFICATIONMETHOD, \
        RTRIM(EPVK), \
        RTRIM(DECIMILIZATIONTABLE), \
        PINPADCHAR, \
		PANPADCHAR, \
		PINLEN, \
		PANLEN, \
		PANVALIDATIONOFFSET, \
		RTRIM(PINBLOCKFORMAT), \
		PANVALIDATIONLENGTH, \
		RTRIM(CVKA), \
		RTRIM(CVKB) \
    FROM EZSECURITY WHERE RTRIM(SECURITYID)='%s'", I_SecurityId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadSecurity [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( EPVK, 0, sizeof( EPVK ) );
	memset( DecimilizationTable, 0, sizeof( DecimilizationTable ) );
	memset( PINBlockFormat, 0, sizeof( PINBlockFormat ) );
	memset( CVKA, 0, sizeof( CVKA ) );
	memset( CVKB, 0, sizeof( CVKB ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, SecurityId, sizeof(SecurityId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &PINVerificationMethod, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINVerificationMethod) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, EPVK, sizeof(EPVK), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EPVK) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, DecimilizationTable, sizeof(DecimilizationTable), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DecimilizationTable) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &PINPadChar, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINPadChar) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &PANPadChar, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANPadChar) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &PINLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINLen) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &PANLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANLen) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &PANValidationOffset, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANValidationOffset) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, PINBlockFormat, sizeof(PINBlockFormat), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PINBlockFormat) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &PANValidationLength, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PANValidationLength) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, CVKA, sizeof(CVKA), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CVKA) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, CVKB, sizeof(CVKB), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CVKB) in EZSECURITY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ezsecurity_rec, 0, sizeof( struct EzSecurity ) );
        strcpy( ezsecurity_rec->SecurityId, SecurityId );
        ezsecurity_rec->PINVerificationMethod = PINVerificationMethod;
        strcpy( ezsecurity_rec->EPVK, EPVK );
        strcpy( ezsecurity_rec->DecimilizationTable, DecimilizationTable );
        ezsecurity_rec->PINPadChar = PINPadChar;
        ezsecurity_rec->PANPadChar = PANPadChar;
        ezsecurity_rec->PINLen = PINLen;
        ezsecurity_rec->PANLen = PANLen;
        ezsecurity_rec->PANValidationOffset = PANValidationOffset;
        strcpy( ezsecurity_rec->PINBlockFormat, PINBlockFormat );
        ezsecurity_rec->PANValidationLength = PANValidationLength;
		strcpy( ezsecurity_rec->CVKA, CVKA );
		strcpy( ezsecurity_rec->CVKB, CVKB );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return 0;
    }
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
}

int EzGuiControllerODBC :: readATMKeyTable( const char *I_ATMId, struct EzATMKey *atmkey_rec )
{
    char ATMId[ 33 ];
    char ATMMasterKey[ 65 ];
    char ATMCommKey[ 65 ];
    int ATMKeyLen;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(ATMID),RTRIM(ATMMASTERKEY),RTRIM(ATMCOMMKEY),ATMKEYLEN FROM EZATMINFO WHERE RTRIM(ATMID)='%s';", I_ATMId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadATMKey [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( ATMId, 0, sizeof( ATMId ) );
	memset( ATMMasterKey, 0, sizeof( ATMMasterKey ) );
	memset( ATMCommKey, 0, sizeof( ATMCommKey ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, ATMId, sizeof(ATMId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ATMMasterKey, sizeof(ATMMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMMasterKey) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, ATMCommKey, sizeof(ATMCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMCommKey) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &ATMKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ATMKeyLen) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( atmkey_rec, 0, sizeof( struct EzATMKey ) );
        strcpy( atmkey_rec->ATMId, ATMId );
        strcpy( atmkey_rec->ATMMasterKey, ATMMasterKey );
        strcpy( atmkey_rec->ATMCommKey, ATMCommKey );
        atmkey_rec->ATMKeyLen = ATMKeyLen;
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return 0;
    }
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
}

int EzGuiControllerODBC :: readNetworkKeyTable( const char *I_NetworkId, struct EzNetworkKey *ntwkkey_rec )
{
	char NetworkId[ 17 ];
    char NetworkMasterKey[ 65 ];
    char NetworkAcqCommKey[ 65 ];
    char NetworkIssCommKey[ 65 ];
    int NetworkKeyLen;
    char KeyProperty;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(NETWORKID), \
        RTRIM(NETWORKMASTERKEY), \
        RTRIM(NETWORKACQCOMMKEY), \
        RTRIM(NETWORKISSCOMMKEY), \
		NETWORKKEYLEN, \
		KEYPROPERTY \
	FROM EZNETWORKKEY WHERE RTRIM(NETWORKID)='%s';", I_NetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkKey [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( NetworkMasterKey, 0, sizeof( NetworkMasterKey ) );
	memset( NetworkAcqCommKey, 0, sizeof( NetworkAcqCommKey ) );
	memset( NetworkIssCommKey, 0, sizeof( NetworkIssCommKey ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKKEY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, NetworkMasterKey, sizeof(NetworkMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkMasterKey) in EZNETWORKKEY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, NetworkAcqCommKey, sizeof(NetworkAcqCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkAcqCommKey) in EZNETWORKKEY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, NetworkIssCommKey, sizeof(NetworkIssCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkIssCommKey) in EZNETWORKKEY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &NetworkKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkKeyLen) in EZNETWORKKEY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &KeyProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(KeyProperty) in EZNETWORKKEY [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ntwkkey_rec, 0, sizeof( struct EzNetworkKey ) );
        strcpy( ntwkkey_rec->NetworkId, NetworkId );
        strcpy( ntwkkey_rec->NetworkMasterKey, NetworkMasterKey );
        strcpy( ntwkkey_rec->NetworkAcqCommKey, NetworkAcqCommKey );
        strcpy( ntwkkey_rec->NetworkIssCommKey, NetworkIssCommKey );
        ntwkkey_rec->NetworkKeyLen = NetworkKeyLen;
        ntwkkey_rec->KeyProperty = KeyProperty;
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return 0;
    }
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
}

int EzGuiControllerODBC :: readEzAtmFit( const char *I_RecordId, struct AtmFit *atmfit_ptr )
{
	char RecordId[ 17 ];
	char InstId[ 13 ];
	char AtmLogicalGroup[ 17 ];
	char AtmId[ 17 ];
	char SecurityId[ 11 ];
	char FitRecord[ 11 ];
	char IndirectState;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN odbcrt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcrt = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcrt );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
        	RTRIM(RECORDID), \
           	RTRIM(INSTID), \
			RTRIM(ATMLOGICALGROUP), \
			RTRIM(ATMID), \
			RTRIM(SECURITYID), \
			RTRIM(FITRECORD), \
			INDIRECTSTATE \
	    FROM EZATMFIT WHERE RTRIM(RECORDID)='%s';", I_RecordId );

    odbcrt = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzAtmFit [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
	memset( FitRecord, 0, sizeof( FitRecord ) );
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( AtmId, 0, sizeof( AtmId ) );

    odbcrt = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 3, SQL_C_CHAR, AtmLogicalGroup, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AtmLogicalGroup) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 4, SQL_C_CHAR, AtmId, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AtmId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 5, SQL_C_CHAR, SecurityId, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 6, SQL_C_CHAR, FitRecord, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FitRecord) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcrt = SQLBindCol( hstmt, 7, SQL_C_CHAR, &IndirectState, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcrt ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(IndirectState) in EZATMFIT [ %d ]", odbcrt );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcrt = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( atmfit_ptr + i, 0, sizeof( struct AtmFit ) );
		strcpy( ( atmfit_ptr + i )->RecordId, RecordId );
		strcpy( ( atmfit_ptr + i )->InstId, InstId );
		strcpy( ( atmfit_ptr + i )->AtmLogicalGroup, AtmLogicalGroup );
		strcpy( ( atmfit_ptr + i )->AtmId, AtmId );
		strcpy( ( atmfit_ptr + i )->SecurityId, SecurityId );
		strcpy( ( atmfit_ptr + i )->FitRecord, FitRecord );
		( atmfit_ptr + i )->IndirectState = IndirectState;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzGuiControllerODBC :: readEzInstProfile( const char *I_InstId, struct EzInstProfileMemory *instprofile_ptr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char InstId[ 13 ];
	char InstRouteType[ 17 ];
	char InstType[ 17 ];
	char InstSecurityGroup[ 17 ];
	char InstTerminalGroup[ 17 ];
	char InstAuthGroup[ 17 ];
	char InstCurrencyCode[ 6 ];
	int MaxATMPINCount;
	int MaxTelePINCount;
	char PrimaryBin[ 13 ];
	char PADSSEnabled;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(INSTID),\
		RTRIM(INSTROUTETYPE),\
        RTRIM(INSTTYPE),\
        RTRIM(INSTSECURITYGROUP),\
        RTRIM(INSTTERMINALGROUP),\
        RTRIM(INSTAUTHGROUP),\
        RTRIM(INSTCURRENCYCODE),\
        RTRIM(PRIMARYBIN),\
        PADSSENABLED,\
    	MAXATMPINCOUNT,\
    	MAXTELEPINCOUNT\
    FROM EZINSTPROFILE  WHERE RTRIM(INSTID)='%s'", I_InstId );


    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( InstId, 0, sizeof( InstId ) );
	memset( InstRouteType, 0, sizeof( InstRouteType ) );
	memset( InstType, 0, sizeof( InstType ) );
	memset( InstSecurityGroup, 0, sizeof( InstSecurityGroup ) );
	memset( InstTerminalGroup, 0, sizeof( InstTerminalGroup ) );
	memset( InstAuthGroup, 0, sizeof( InstAuthGroup ) );
	memset( InstCurrencyCode, 0, sizeof( InstCurrencyCode ) );
	memset( PrimaryBin, 0, sizeof( PrimaryBin ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstRouteType, sizeof(InstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstRouteType) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, InstType, sizeof(InstType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstType) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, InstSecurityGroup, sizeof(InstSecurityGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstSecurityGroup) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, InstTerminalGroup, sizeof(InstTerminalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstTerminalGroup) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, InstAuthGroup, sizeof(InstAuthGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstAuthGroup) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, InstCurrencyCode, sizeof(InstCurrencyCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstCurrencyCode) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, PrimaryBin, sizeof(PrimaryBin), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PrimaryBin) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &PADSSEnabled, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PADSSEnabled) in EZINSTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &MaxATMPINCount, sizeof(int), &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxATMPINCount) in EZINSTPROFILE [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &MaxTelePINCount, sizeof(int), &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxTelePINCount) in EZINSTPROFILE [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
 		memset( instprofile_ptr, 0, sizeof( struct EzInstProfileMemory ) );

 		strcpy( instprofile_ptr->InstId, InstId );
 		strcpy( instprofile_ptr->InstRouteType, InstRouteType );
 		strcpy( instprofile_ptr->InstType, InstType );
 		strcpy( instprofile_ptr->InstSecurityGroup, InstSecurityGroup );
 		strcpy( instprofile_ptr->InstTerminalGroup, InstTerminalGroup );
 		strcpy( instprofile_ptr->InstAuthGroup, InstAuthGroup );
 		strcpy( instprofile_ptr->InstCurrencyCode, InstCurrencyCode );
 		instprofile_ptr->MaxATMPINCount = MaxATMPINCount ;
 		instprofile_ptr->MaxTelePINCount = MaxTelePINCount;
 		strcpy( instprofile_ptr->PrimaryBin, PrimaryBin );
 		instprofile_ptr->PADSSEnabled = PADSSEnabled;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 0;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzGuiControllerODBC :: readEzInstSelect( const char *I_RecordNo, struct EzInstSelectMemory *instselect_ptr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char RecordId[ 17 ];
	char DeviceType[ 17 ];
	char FieldType[ 65 ];
	char FromOffset[ 17 ];
	char ToOffset[ 17 ];
	char FieldVal[ 129 ];
	int Priority;
	char InstId[ 13 ];
	char InstType[ 11 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  " SELECT \
    	RTRIM(RECORDID), \
    	RTRIM(DEVICETYPE), \
		RTRIM(FIELDTYPE), \
        RTRIM(FROMOFFSET), \
        RTRIM(TOOFFSET), \
        RTRIM(FIELDVAL), \
        PRIORITY, \
        RTRIM(INSTID), \
        RTRIM(INSTTYPE) \
    FROM EZINSTSELECT  WHERE RTRIM(RECORDID)='%s'", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstSelect [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( FieldType, 0, sizeof( FieldType ) );
	memset( FromOffset, 0, sizeof( FromOffset ) );
	memset( ToOffset, 0, sizeof( ToOffset ) );
	memset( FieldVal, 0, sizeof( FieldVal ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( InstType, 0, sizeof( InstType ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, DeviceType, sizeof(DeviceType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceType) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, FieldType, sizeof(FieldType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FieldType) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, FromOffset, sizeof(FromOffset), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FromOffset) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, ToOffset, sizeof(ToOffset), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ToOffset) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, FieldVal, sizeof(FieldVal), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FieldVal) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &Priority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Priority) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, InstType, sizeof(InstType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstType) in EZINSTSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	memset( instselect_ptr, 0, sizeof( struct EzInstSelectMemory ) );
    	strcpy( instselect_ptr->RecordId, RecordId );
    	strcpy( instselect_ptr->DeviceType, DeviceType );
    	strcpy( instselect_ptr->FieldType, FieldType );
    	strcpy( instselect_ptr->FromOffset, FromOffset );
    	strcpy( instselect_ptr->ToOffset, ToOffset );
    	instselect_ptr->Priority = Priority;
    	strcpy( instselect_ptr->FieldVal, FieldVal );
    	strcpy( instselect_ptr->InstId, InstId );
    	strcpy( instselect_ptr->InstType, InstType );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
	}
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzGuiControllerODBC :: readEzNetworkSelect( const char *I_RecordNo, struct EzNetworkSelectMemory *networkselect_ptr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char RecordId[ 17 ];
	char InstId[ 13 ];
	int Priority;
	char NetworkType[ 11 ];
	char FieldType[ 65 ];
	char FromOffset[ 33 ];
	char ToOffset[ 33 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RTRIM(RECORDID), \
		RTRIM(INSTID), \
        PRIORITY, \
        RTRIM(NETWORKTYPE), \
        RTRIM(FIELDTYPE), \
        RTRIM(FROMOFFSET), \
        RTRIM(TOOFFSET) \
    FROM EZNETWORKSELECT  WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkSelect [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( NetworkType, 0, sizeof( NetworkType ) );
	memset( FieldType, 0, sizeof( FieldType ) );
	memset( FromOffset, 0, sizeof( FromOffset ) );
	memset( ToOffset, 0, sizeof( ToOffset ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &Priority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Priority) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, NetworkType, sizeof(NetworkType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkType) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, FieldType, sizeof(FieldType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FieldType) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, FromOffset, sizeof(FromOffset), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FromOffset) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, ToOffset, sizeof(ToOffset), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ToOffset) in EZNETWORKSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( networkselect_ptr->RecordId, RecordId );
    	strcpy( networkselect_ptr->InstId, InstId );
    	networkselect_ptr->Priority = Priority;
    	strcpy( networkselect_ptr->NetworkType, NetworkType );
    	strcpy( networkselect_ptr->FieldType, FieldType );
    	strcpy( networkselect_ptr->FromOffset, FromOffset );
    	strcpy( networkselect_ptr->ToOffset, ToOffset );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 0;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzGuiControllerODBC :: readEzBINProfile( const char *I_InstId, const char *I_BIN, struct EzBINProfileMemory *binprofile_ptr )
{
	int i = 0;
    SQLHSTMT hstmt;
    //SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char InstId[ 13 ];
	char BIN[ 13 ];
	char ProductCode[ 13 ];
	char ProductName[ 13 ];
	char BINType[ 11 ];
	char RouteType[ 17 ];
	char TxnList[ 65 ];

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RTRIM(INSTID), \
		RTRIM(BIN), \
		RTRIM(PRODUCTCODE), \
		RTRIM(PRODUCTNAME), \
		RTRIM(BINTYPE), \
		RTRIM(ROUTETYPE), \
        RTRIM(TXNLIST) \
    FROM EZBINPROFILE WHERE RTRIM(INSTID)='%s' AND RTRIM(BIN)='%s';", I_InstId, I_BIN );

    dptr->trace("<%s>", SqlStmt);
    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBINProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( InstId, 0, sizeof( InstId ) );
	memset( BIN, 0, sizeof( BIN ) );
	memset( ProductCode, 0, sizeof( ProductCode ) );
	memset( ProductName, 0, sizeof( ProductName ) );
	memset( BINType, 0, sizeof( BINType ) );
	memset( RouteType, 0, sizeof( RouteType ) );
	memset( TxnList, 0, sizeof( TxnList ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BIN, sizeof(BIN), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BIN) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, ProductCode, sizeof(ProductCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ProductCode) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, ProductName, sizeof(ProductName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ProductName) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, BINType, sizeof(BINType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BINType) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, RouteType, sizeof(RouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteType) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, TxnList, sizeof(TxnList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnList) in EZBINPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( binprofile_ptr->InstId, InstId );
        strcpy( binprofile_ptr->BIN, BIN );
        strcpy( binprofile_ptr->ProductCode, ProductCode );
        strcpy( binprofile_ptr->ProductName, ProductName );
        strcpy( binprofile_ptr->BINType, BINType );
        strcpy( binprofile_ptr->RouteType, RouteType );
		strcpy( binprofile_ptr->TxnList, TxnList );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 0;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzGuiControllerODBC :: readEzBranchProfile( const char *I_InstId, const char *I_BranchCode, struct EzBranchProfileMemory *branchprofile_ptr )
{
	char InstId[ 13 ];
	char BranchCode[ 13 ];
	char BranchMapCode[ 13 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(INSTID), RTRIM(BRANCHCODE), RTRIM(BRANCHMAPCODE) FROM EZBRANCHPROFILE WHERE RTRIM(INSTID)='%s' AND RTRIM(BRANCHCODE)='%s';", I_InstId, I_BranchCode );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzBranchProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( InstId, 0, sizeof( InstId ) );
	memset( BranchCode, 0, sizeof( BranchCode ) );
	memset( BranchMapCode, 0, sizeof( BranchMapCode ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BranchCode, sizeof(BranchCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BranchCode) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, BranchMapCode, sizeof(BranchMapCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BranchMapCode) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( branchprofile_ptr, 0, sizeof( struct EzBranchProfileMemory ) );
        strcpy( branchprofile_ptr->InstId, InstId );
        strcpy( branchprofile_ptr->BranchCode, BranchCode );
        strcpy( branchprofile_ptr->BranchMapCode, BranchMapCode );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return 0;
    }
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
}

int EzGuiControllerODBC :: readAtmBatchId( char *AtmId, char *BatchId )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];
    char hBatchId[ 13 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(BATCHID) FROM EZATMDATAINFO WHERE RTRIM(ATMID)='%s';", AtmId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readAtmBatchId [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    memset( hBatchId, 0, sizeof( hBatchId ) );
    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, hBatchId, sizeof(hBatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BatchId) in EZATMDATAINFO [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( BatchId, hBatchId );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return 0;
    }
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
}

int EzGuiControllerODBC :: ClearATMStaticStatus( char *StaticStatusCode, const char *AtmId, char *Date, char *Time )
{
    char SqlStmt[ 1024 ];
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( Date, Input_date );

		sprintf( SqlStmt, "UPDATE EZATMSTATUS SET \
			STATICCODE='%s', \
			LOGDATE=convert(varchar,'%s',105), \
			LOGTIME='%s' \
		WHERE RTRIM(ATMID)='%s';", StaticStatusCode, Input_date, Time, AtmId );
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzGuiControllerODBC :: readEzBINSelect( const char *I_RecordNo, struct EzBINSelectMemory *binselect_ptr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    char RecordId[ 17 ];
	char BIN[ 13 ];
	char InstId[ 13 ];
	char BINRangeReq;
	short Priority;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RTRIM(RECORDID), \
    	RTRIM(BIN), \
    	RTRIM(INSTID), \
		BINRANGEREQ, \
		PRIORITY \
    FROM EZBINSELECT WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBINSelect [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( BIN, 0, sizeof( BIN ) );
	memset( InstId, 0, sizeof( InstId ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZBINSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BIN, sizeof(BIN), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BIN) in EZBINSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZBINSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &BINRangeReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BINRangeReq) in EZBINSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &Priority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FieldVal) in EZBINSELECT [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }


    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( binselect_ptr->RecordId, RecordId );
    	strcpy( binselect_ptr->BIN, BIN );
    	strcpy( binselect_ptr->InstId, InstId );
    	binselect_ptr->BINRangeReq = BINRangeReq;
    	binselect_ptr->Priority = Priority;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 0;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzGuiControllerODBC :: readEzAtmDenomStatus( const char *I_AtmId, int LastResetDate, int LastResetTime, struct EzAtmDenomStatus *ezatmdenomstatus_ptr )
{
	int DenomANotesLoaded;
	int DenomADisp;
	int DenomAMin;
	int DenomBNotesLoaded;
	int DenomBDisp;
	int DenomBMin;
	int DenomCNotesLoaded;
	int DenomCDisp;
	int DenomCMin;
	int DenomDNotesLoaded;
	int DenomDDisp;
	int DenomDMin;
	int DenomENotesLoaded;
	int DenomEDisp;
	int DenomEMin;
	int DenomFNotesLoaded;
	int DenomFDisp;
	int DenomFMin;
	int DenomGNotesLoaded;
	int DenomGDisp;
	int DenomGMin;
	int DenomHNotesLoaded;
	int DenomHDisp;
	int DenomHMin;
	char hLastResetDate[11];
	int hLastResetTime;
	char tempdate[ 11 ];

	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		sprintf( SqlStmt, "SELECT \
			RTRIM(DENOM_A_NOTESLOADED), \
			RTRIM(DENOM_A_NOTESDISP), \
			RTRIM(DENOM_B_NOTESLOADED), \
			RTRIM(DENOM_B_NOTESDISP), \
			RTRIM(DENOM_C_NOTESLOADED), \
			RTRIM(DENOM_C_NOTESDISP), \
			RTRIM(DENOM_D_NOTESLOADED), \
			RTRIM(DENOM_D_NOTESDISP), \
			RTRIM(DENOM_E_NOTESLOADED), \
			RTRIM(DENOM_E_NOTESDISP), \
			RTRIM(DENOM_F_NOTESLOADED), \
			RTRIM(DENOM_F_NOTESDISP), \
			RTRIM(DENOM_G_NOTESLOADED), \
			RTRIM(DENOM_G_NOTESDISP), \
			RTRIM(DENOM_H_NOTESLOADED), \
			RTRIM(DENOM_H_NOTESDISP), \
			convert(varchar, LASTRESETDATE, 4 ), \
			LASTRESETTIME \
		FROM EZATMDENOMSTATUS WHERE RTRIM(ATMID)='%s'", I_AtmId);
    }
    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzAtmDenomStatus [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &DenomANotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomANotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &DenomADisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomADisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &DenomBNotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomBNotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &DenomBDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomBDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &DenomCNotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomCNotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_SLONG, &DenomCDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomCDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &DenomDNotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomDNotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &DenomDDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomDDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &DenomENotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomENotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &DenomEDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomEDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &DenomFNotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomFNotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_SLONG, &DenomFDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomFDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_SLONG, &DenomGNotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomGNotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_SLONG, &DenomGDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomGDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &DenomHNotesLoaded, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomHNotesLoaded) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &DenomHDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DenomHDisp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_CHAR, hLastResetDate, sizeof(hLastResetDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(hLastResetDate) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_SLONG, &hLastResetTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(hLastResetTime) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( ezatmdenomstatus_ptr->AtmId, I_AtmId );
    	ezatmdenomstatus_ptr->DenomANotesLoaded = DenomANotesLoaded;
    	ezatmdenomstatus_ptr->DenomADisp = DenomADisp;
    	ezatmdenomstatus_ptr->DenomAMin = DenomAMin;
    	ezatmdenomstatus_ptr->DenomBNotesLoaded = DenomBNotesLoaded;
    	ezatmdenomstatus_ptr->DenomBDisp = DenomBDisp;
    	ezatmdenomstatus_ptr->DenomBMin = DenomBMin;
    	ezatmdenomstatus_ptr->DenomCNotesLoaded = DenomCNotesLoaded;
    	ezatmdenomstatus_ptr->DenomCDisp = DenomCDisp;
    	ezatmdenomstatus_ptr->DenomCMin = DenomCMin;
    	ezatmdenomstatus_ptr->DenomDNotesLoaded = DenomDNotesLoaded;
    	ezatmdenomstatus_ptr->DenomDDisp = DenomDDisp;
    	ezatmdenomstatus_ptr->DenomDMin = DenomDMin;
    	ezatmdenomstatus_ptr->DenomENotesLoaded = DenomENotesLoaded;
    	ezatmdenomstatus_ptr->DenomEDisp = DenomEDisp;
    	ezatmdenomstatus_ptr->DenomEMin = DenomEMin;
    	ezatmdenomstatus_ptr->DenomFNotesLoaded = DenomFNotesLoaded;
    	ezatmdenomstatus_ptr->DenomFDisp = DenomFDisp;
    	ezatmdenomstatus_ptr->DenomEMin = DenomFMin;
    	ezatmdenomstatus_ptr->DenomGNotesLoaded = DenomGNotesLoaded;
    	ezatmdenomstatus_ptr->DenomGDisp = DenomGDisp;
    	ezatmdenomstatus_ptr->DenomEMin = DenomGMin;
    	ezatmdenomstatus_ptr->DenomHNotesLoaded = DenomHNotesLoaded;
    	ezatmdenomstatus_ptr->DenomHDisp = DenomHDisp;
    	ezatmdenomstatus_ptr->DenomEMin = DenomHMin;
        if( !strcasecmp( DBType, SQLSERVER ) )
        {
        	memset( tempdate, 0, sizeof( tempdate ) );
        	getSwitchDateFmt( hLastResetDate, "DDMMYY", tempdate );
        	ezatmdenomstatus_ptr->LastResetDate = atoi( tempdate );
        }
    	ezatmdenomstatus_ptr->LastResetTime = hLastResetTime;
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzGuiControllerODBC :: closeBatch( const char *AtmId, const char *BatchId, const char *UserId, int GenDate, int GenTime, int DenomADisp, int DenomBDisp, int DenomCDisp, int DenomDDisp, int DenomEDisp, int DenomFDisp, int DenomGDisp, int DenomHDisp, int DenomALoaded, int DenomBLoaded, int DenomCLoaded, int DenomDLoaded, int DenomELoaded, int DenomFLoaded, int DenomGLoaded, int DenomHLoaded )
{
    char SqlStmt[ 1024 ];
    char Input_AtmId[ 17 ];
	char Input_BatchId[ 13 ];
    char Input_UserId[ 51 ];
    char Input_GenDate[ 7 ];
    int Input_GenTime;
    char Input_Status;
    int Input_DenomADisp;
    int Input_DenomBDisp;
    int Input_DenomCDisp;
    int Input_DenomDDisp;
    int Input_DenomEDisp;
    int Input_DenomFDisp;
    int Input_DenomGDisp;
    int Input_DenomHDisp;
    int Input_DenomALoaded;
    int Input_DenomBLoaded;
    int Input_DenomCLoaded;
    int Input_DenomDLoaded;
    int Input_DenomELoaded;
    int Input_DenomFLoaded;
    int Input_DenomGLoaded;
    int Input_DenomHLoaded;

	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( Input_BatchId, 0, sizeof( Input_BatchId ) );
	memset( Input_UserId, 0, sizeof( Input_UserId ) );
	memset( Input_GenDate, 0, sizeof( Input_GenDate ) );

	strcpy( Input_AtmId, AtmId );
	strcpy( Input_BatchId, BatchId );
	strcpy( Input_UserId, UserId );
	sprintf( Input_GenDate, "%06d", GenDate );
	Input_GenTime = GenTime;
	Input_Status = 'C';

	Input_DenomADisp = DenomADisp;
	Input_DenomBDisp = DenomBDisp;
	Input_DenomCDisp = DenomCDisp;
	Input_DenomDDisp = DenomDDisp;
	Input_DenomEDisp = DenomEDisp;
	Input_DenomFDisp = DenomFDisp;
	Input_DenomGDisp = DenomGDisp;
	Input_DenomHDisp = DenomHDisp;

	Input_DenomALoaded = DenomALoaded;
	Input_DenomBLoaded = DenomBLoaded;
	Input_DenomCLoaded = DenomCLoaded;
	Input_DenomDLoaded = DenomDLoaded;
	Input_DenomELoaded = DenomELoaded;
	Input_DenomFLoaded = DenomFLoaded;
	Input_DenomGLoaded = DenomGLoaded;
	Input_DenomHLoaded = DenomHLoaded;

    char Input_date[ 15 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( Input_GenDate, Input_date );

		sprintf( SqlStmt, "INSERT INTO EZATMBATCHINFO \
		( \
			ATMID, \
			BATCHID, \
			USERID, \
			GENDATE, \
			GENTIME, \
			STATUS, \
			DENOM_A_NOTESLOADED, \
			DENOM_A_NOTESDISP, \
			DENOM_B_NOTESLOADED, \
			DENOM_B_NOTESDISP, \
			DENOM_C_NOTESLOADED, \
			DENOM_C_NOTESDISP, \
			DENOM_D_NOTESLOADED, \
			DENOM_D_NOTESDISP, \
			DENOM_E_NOTESLOADED, \
			DENOM_E_NOTESDISP, \
			DENOM_F_NOTESLOADED, \
			DENOM_F_NOTESDISP, \
			DENOM_G_NOTESLOADED, \
			DENOM_G_NOTESDISP, \
			DENOM_H_NOTESLOADED, \
			DENOM_H_NOTESDISP \
		) VALUES ('%s', '%s', '%s', convert(varchar,'%s',105), '%d', '%c', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d' );", \
			Input_AtmId,
			Input_BatchId,
			Input_UserId,
			Input_date,
			Input_GenTime,
			Input_Status,
			Input_DenomALoaded,
			Input_DenomADisp,
			Input_DenomBLoaded,
			Input_DenomBDisp,
			Input_DenomCLoaded,
			Input_DenomCDisp,
			Input_DenomDLoaded,
			Input_DenomDDisp,
			Input_DenomELoaded,
			Input_DenomEDisp,
			Input_DenomFLoaded,
			Input_DenomFDisp,
			Input_DenomGLoaded,
			Input_DenomGDisp,
			Input_DenomHLoaded,
			Input_DenomHDisp );
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzGuiControllerODBC :: openBatch( const char *AtmId, const char *BatchId, const char *UserId, int GenDate, int GenTime, int DenomADisp, int DenomBDisp, int DenomCDisp, int DenomDDisp, int DenomEDisp, int DenomFDisp, int DenomGDisp, int DenomHDisp, int DenomALoaded, int DenomBLoaded, int DenomCLoaded, int DenomDLoaded, int DenomELoaded, int DenomFLoaded, int DenomGLoaded, int DenomHLoaded )
{
    char SqlStmt[ 1024 ];
    char Input_AtmId[ 17 ];
	char Input_BatchId[ 13 ];
    char Input_UserId[ 51 ];
    char Input_GenDate[ 7 ];
    int Input_GenTime;
    char Input_Status;
    int Input_DenomADisp;
    int Input_DenomBDisp;
    int Input_DenomCDisp;
    int Input_DenomDDisp;
    int Input_DenomEDisp;
    int Input_DenomFDisp;
    int Input_DenomGDisp;
    int Input_DenomHDisp;
    int Input_DenomALoaded;
    int Input_DenomBLoaded;
    int Input_DenomCLoaded;
    int Input_DenomDLoaded;
    int Input_DenomELoaded;
    int Input_DenomFLoaded;
    int Input_DenomGLoaded;
    int Input_DenomHLoaded;

	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( Input_BatchId, 0, sizeof( Input_BatchId ) );
	memset( Input_UserId, 0, sizeof( Input_UserId ) );
	memset( Input_GenDate, 0, sizeof( Input_GenDate ) );

	strcpy( Input_AtmId, AtmId );
	strcpy( Input_BatchId, BatchId );
	strcpy( Input_UserId, UserId );
	sprintf( Input_GenDate, "%06d", GenDate );
	Input_GenTime = GenTime;
	Input_Status = 'O';

	Input_DenomADisp = DenomADisp;
	Input_DenomBDisp = DenomBDisp;
	Input_DenomCDisp = DenomCDisp;
	Input_DenomDDisp = DenomDDisp;
	Input_DenomEDisp = DenomEDisp;
	Input_DenomFDisp = DenomFDisp;
	Input_DenomGDisp = DenomGDisp;
	Input_DenomHDisp = DenomHDisp;

	Input_DenomALoaded = DenomALoaded;
	Input_DenomBLoaded = DenomBLoaded;
	Input_DenomCLoaded = DenomCLoaded;
	Input_DenomDLoaded = DenomDLoaded;
	Input_DenomELoaded = DenomELoaded;
	Input_DenomFLoaded = DenomFLoaded;
	Input_DenomGLoaded = DenomGLoaded;
	Input_DenomHLoaded = DenomHLoaded;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( Input_GenDate, Input_date );
		sprintf( SqlStmt, "INSERT INTO EZATMBATCHINFO \
		( \
			ATMID, \
			BATCHID, \
			USERID, \
			GENDATE, \
			GENTIME, \
			STATUS, \
			DENOM_A_NOTESLOADED, \
			DENOM_A_NOTESDISP, \
			DENOM_B_NOTESLOADED, \
			DENOM_B_NOTESDISP, \
			DENOM_C_NOTESLOADED, \
			DENOM_C_NOTESDISP, \
			DENOM_D_NOTESLOADED, \
			DENOM_D_NOTESDISP, \
			DENOM_E_NOTESLOADED, \
			DENOM_E_NOTESDISP, \
			DENOM_F_NOTESLOADED, \
			DENOM_F_NOTESDISP, \
			DENOM_G_NOTESLOADED, \
			DENOM_G_NOTESDISP, \
			DENOM_H_NOTESLOADED, \
			DENOM_H_NOTESDISP \
		) VALUES ('%s', '%s', '%s', convert(varchar,'%s',105), '%d', '%c', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d' );", \
			Input_AtmId,
			Input_BatchId,
			Input_UserId,
			Input_date,
			Input_GenTime,
			Input_Status,
			Input_DenomALoaded,
			Input_DenomADisp,
			Input_DenomBLoaded,
			Input_DenomBDisp,
			Input_DenomCLoaded,
			Input_DenomCDisp,
			Input_DenomDLoaded,
			Input_DenomDDisp,
			Input_DenomELoaded,
			Input_DenomEDisp,
			Input_DenomFLoaded,
			Input_DenomFDisp,
			Input_DenomGLoaded,
			Input_DenomGDisp,
			Input_DenomHLoaded,
			Input_DenomHDisp );
	}
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzGuiControllerODBC :: updateBatchInAtmDataInfo( const char *AtmId, const char *BatchId )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZATMDATAINFO SET BATCHID = '%s' WHERE RTRIM(ATMID)='%s';", BatchId, AtmId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzGuiControllerODBC :: updateDenomStatusResetDateTime( const char *AtmId, int ResetDate, int ResetTime )
{
    char SqlStmt[ 1024 ];
    char Input_ResetDate[ 7 ];
    int Input_ResetTime;

	memset( Input_ResetDate, 0, sizeof( Input_ResetDate ) );
	sprintf( Input_ResetDate, "%06d", ResetDate );
	Input_ResetTime = ResetTime;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( Input_ResetDate, Input_date );
		sprintf( SqlStmt, "UPDATE EZATMDENOMSTATUS SET \
			DENOM_A_NOTESLOADED = 0, \
			DENOM_A_NOTESDISP = 0, \
			DENOM_B_NOTESLOADED = 0, \
			DENOM_B_NOTESDISP = 0, \
			DENOM_C_NOTESLOADED = 0, \
			DENOM_C_NOTESDISP = 0, \
			DENOM_D_NOTESLOADED = 0, \
			DENOM_D_NOTESDISP = 0, \
			DENOM_E_NOTESLOADED = 0, \
			DENOM_E_NOTESDISP = 0, \
			DENOM_F_NOTESLOADED = 0, \
			DENOM_F_NOTESDISP = 0, \
			DENOM_G_NOTESLOADED = 0, \
			DENOM_G_NOTESDISP = 0, \
			DENOM_H_NOTESLOADED = 0, \
			DENOM_H_NOTESDISP = 0, \
			LASTRESETDATE = convert(varchar,'%s',105), \
			LASTRESETTIME = %d \
		WHERE RTRIM(ATMID)='%s';", Input_date, Input_ResetTime, AtmId );
	}
	if( ExecuteQuery( SqlStmt, true ) < 0 )
		return -1;
	return 0;
}

/*int EzGuiControllerODBC :: readEzPOSMCCInfo( int I_MCC, struct EzPOSMCCInfo *posmccinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSMerchantTypeInfo( const char *I_MerchantType, struct EzPOSMerchantTypeInfo *posmerchanttypeinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSMerchantInfo( const char *I_MerchantId, struct EzPOSMerchantInfo *posmerchantinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSTerminalTypeInfo( const char *I_TerminalType, struct EzPOSTerminalTypeInfo *posterminaltypeinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSTerminalInfo( const char *I_POSId, struct EzPOSTerminalInfo *posterminalinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSStoreInfo( const char *I_StoreId, struct EzPOSStoreInfo *posstoreinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSTxnInfo( const char *I_TxnCodeGroupId, struct EzPOSTxnInfo *postxninfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzPOSRespCodeInfo( const char *I_RecordId, struct EzPOSRespCodeInfo *posrespcodeinfo_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzSMSAlertGroup( const char *I_SMSAlertGroupId, struct EzSMSAlertGroupMemory *smsalertgroup_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzStatusAlert( const char *I_RecordId, struct EzStatusAlertMemory *statusalert_rec )
{
	return 0;
}

int EzGuiControllerODBC :: readEzAlertDesc( const char *I_RecordId, struct EzAlertDescMemory *alertdesc_rec )
{
	return 0;
}*/



