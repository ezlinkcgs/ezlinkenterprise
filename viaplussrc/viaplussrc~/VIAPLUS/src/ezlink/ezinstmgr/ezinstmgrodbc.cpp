/*
 * ezinstmgrodbc.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: mohanraj
 */


#include <ezlink/ezinstmgrodbc.h>

int EzInstMgrODBC :: initEzInstMgrODBC( const char *TaskName, EzDebugUtil *dptr )
{
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
	this->dptr = dptr;
	return 1;
}

int EzInstMgrODBC :: getEzInstRouteTypeCount( int *SqlErr )
{

    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZINSTROUTETYPE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZINSTROUTETYPE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzInstRouteType( struct EzInstRouteTypeMemory *ezinstroutetype_ptr, int *SqlErr )
{
	char InstRouteType[ 17 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    //dptr->trace("DBType[%s]", DBType );
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	if(odbcret == SQL_INVALID_HANDLE )
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [SQL_INVALID_HANDLE = %d ]", odbcret );
    	else
    		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(INSTROUTETYPE) FROM EZINSTROUTETYPE" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	//getNativeErrorCode();
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstRouteType [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstRouteType, sizeof(InstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstRouteType) in LoadEzInstRouteType [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	dptr->trace("InstRouteType[%s]", InstRouteType);
		memset( ezinstroutetype_ptr + i, 0, sizeof( struct EzInstRouteTypeMemory ) );
		strcpy( ( ezinstroutetype_ptr + i )->InstRouteType, InstRouteType );
		memset( InstRouteType, 0, sizeof( InstRouteType ) );
		i++;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzInstProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZINSTPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZINSTPROFILE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzInstProfile( struct EzInstProfileMemory *ezinstprofile_ptr, int *SqlErr )
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
    strcpy( SqlStmt,  "SELECT RTRIM(INSTID),\
		RTRIM(INSTROUTETYPE),\
        RTRIM(INSTTYPE),\
        RTRIM(INSTSECURITYGROUP),\
        RTRIM(INSTTERMINALGROUP),\
        RTRIM(INSTAUTHGROUP),\
        RTRIM(INSTCURRENCYCODE),\
        MAXATMPINCOUNT,\
        MAXTELEPINCOUNT,\
        RTRIM(PRIMARYBIN),\
        PADSSENABLED\
    FROM EZINSTPROFILE" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

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

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &MaxATMPINCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxATMPINCount) in EZINSTPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &MaxTelePINCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxTelePINCount) in EZINSTPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, PrimaryBin, sizeof(PrimaryBin), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PrimaryBin) in EZINSTPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_BINARY, &PADSSEnabled, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PADSSEnabled) in EZINSTPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	dptr->trace("InstId[%s]", InstId);
		memset( ezinstprofile_ptr + i, 0, sizeof( struct EzInstProfileMemory ) );
		strcpy( ( ezinstprofile_ptr + i )->InstId, InstId );
		strcpy( ( ezinstprofile_ptr + i )->InstRouteType, InstRouteType );
		strcpy( ( ezinstprofile_ptr + i )->InstType, InstType );
		strcpy( ( ezinstprofile_ptr + i )->InstSecurityGroup, InstSecurityGroup );
		strcpy( ( ezinstprofile_ptr + i )->InstTerminalGroup, InstTerminalGroup );
		strcpy( ( ezinstprofile_ptr + i )->InstAuthGroup, InstAuthGroup );
		strcpy( ( ezinstprofile_ptr + i )->InstCurrencyCode, InstCurrencyCode );
		( ezinstprofile_ptr + i )->MaxATMPINCount = MaxATMPINCount;
		( ezinstprofile_ptr + i )->MaxTelePINCount = MaxTelePINCount;
		strcpy( ( ezinstprofile_ptr + i )->PrimaryBin, PrimaryBin );
		( ezinstprofile_ptr + i )->PADSSEnabled = PADSSEnabled;
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( InstRouteType, 0, sizeof( InstRouteType ) );
		memset( InstType, 0, sizeof( InstType ) );
		memset( InstSecurityGroup, 0, sizeof( InstSecurityGroup ) );
		memset( InstTerminalGroup, 0, sizeof( InstTerminalGroup ) );
		memset( InstAuthGroup, 0, sizeof( InstAuthGroup ) );
		memset( InstCurrencyCode, 0, sizeof( InstCurrencyCode ) );
		memset( PrimaryBin, 0, sizeof( PrimaryBin ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzInstSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZINSTSELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZINSTSELECT - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzInstSelect( struct EzInstSelectMemory *ezinstselect_ptr, int *SqlErr )
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
    strcpy( SqlStmt,  " SELECT \
    	RTRIM(RECORDID), \
    	RTRIM(DEVICETYPE), \
		RTRIM(FIELDTYPE), \
        RTRIM(FROMOFFSET), \
        RTRIM(TOOFFSET), \
        RTRIM(FIELDVAL), \
        PRIORITY, \
        RTRIM(INSTID), \
        RTRIM(INSTTYPE) \
    FROM EZINSTSELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstSelect [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

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

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( ezinstselect_ptr + i )->RecordId, RecordId );
		strcpy( ( ezinstselect_ptr + i )->DeviceType, DeviceType );
		strcpy( ( ezinstselect_ptr + i )->FieldType, FieldType );
		strcpy( ( ezinstselect_ptr + i )->FromOffset, FromOffset );
		strcpy( ( ezinstselect_ptr + i )->ToOffset, ToOffset );
		strcpy( ( ezinstselect_ptr + i )->FieldVal, FieldVal );
		( ezinstselect_ptr + i )->Priority = Priority;
		strcpy( ( ezinstselect_ptr + i )->InstId, InstId );
		strcpy( ( ezinstselect_ptr + i )->InstType, InstType );
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( FieldType, 0, sizeof( FieldType ) );
		memset( FromOffset, 0, sizeof( FromOffset ) );
		memset( ToOffset, 0, sizeof( ToOffset ) );
		memset( FieldVal, 0, sizeof( FieldVal ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( InstType, 0, sizeof( InstType ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzBINSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZBINSELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZBINSELECT - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzBINSelect( struct EzBINSelectMemory *ezbinselect_ptr, int *SqlErr )
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
	int Priority;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID), \
    	RTRIM(BIN), \
    	RTRIM(INSTID), \
		BINRANGEREQ, \
		PRIORITY \
    FROM EZBINSELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBINSelect [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

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
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Priority) in EZBINSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }


    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		strcpy( ( ezbinselect_ptr + i )->RecordId, RecordId );
		strcpy( ( ezbinselect_ptr + i )->BIN, BIN );
		strcpy( ( ezbinselect_ptr + i )->InstId, InstId );
		( ezbinselect_ptr + i )->BINRangeReq = BINRangeReq;
		( ezbinselect_ptr + i )->Priority = Priority;
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( InstId, 0, sizeof( InstId ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzNetworkSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZNETWORKSELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZNETWORKSELECT - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzNetworkSelect( struct EzNetworkSelectMemory *eznetworkselect_ptr, int *SqlErr )
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
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID), \
		RTRIM(INSTID), \
        PRIORITY, \
        RTRIM(NETWORKTYPE), \
        RTRIM(FIELDTYPE), \
        RTRIM(FROMOFFSET), \
        RTRIM(TOOFFSET) \
    FROM EZNETWORKSELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkSelect [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

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

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eznetworkselect_ptr + i )->RecordId, RecordId );
 		strcpy( ( eznetworkselect_ptr + i )->InstId, InstId );
 		( eznetworkselect_ptr + i )->Priority = Priority;
 		strcpy( ( eznetworkselect_ptr + i )->NetworkType, NetworkType );
 		strcpy( ( eznetworkselect_ptr + i )->FieldType, FieldType );
 		strcpy( ( eznetworkselect_ptr + i )->FromOffset, FromOffset );
 		strcpy( ( eznetworkselect_ptr + i )->ToOffset, ToOffset );
 		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( NetworkType, 0, sizeof( NetworkType ) );
		memset( FieldType, 0, sizeof( FieldType ) );
		memset( FromOffset, 0, sizeof( FromOffset ) );
		memset( ToOffset, 0, sizeof( ToOffset ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzBINProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZBINPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZBINPROFILE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzBINProfile( struct EzBINProfileMemory *ezbinprofile_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
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
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(INSTID), \
		RTRIM(BIN), \
		RTRIM(PRODUCTCODE), \
		RTRIM(PRODUCTNAME), \
		RTRIM(BINTYPE), \
		RTRIM(ROUTETYPE), \
        RTRIM(TXNLIST) \
    FROM EZBINPROFILE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBINProfile [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

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

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( ezbinprofile_ptr + i )->InstId, InstId );
        strcpy( ( ezbinprofile_ptr + i )->BIN, BIN );
        strcpy( ( ezbinprofile_ptr + i )->ProductCode, ProductCode );
        strcpy( ( ezbinprofile_ptr + i )->ProductName, ProductName );
        strcpy( ( ezbinprofile_ptr + i )->BINType, BINType );
        strcpy( ( ezbinprofile_ptr + i )->RouteType, RouteType );
		strcpy( ( ezbinprofile_ptr + i )->TxnList, TxnList );
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( ProductCode, 0, sizeof( ProductCode ) );
		memset( ProductName, 0, sizeof( ProductName ) );
		memset( BINType, 0, sizeof( BINType ) );
		memset( RouteType, 0, sizeof( RouteType ) );
		memset( TxnList, 0, sizeof( TxnList ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzBINRangeCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZBINRANGE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZBINRANGE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzBINRange( struct EzBINRangeMemory *ezbinrange_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char InstId[ 13 ];
	char BIN[ 13 ];
	char LowRange[ 20 ];
	char HighRange[ 20 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(INSTID), \
    	RTRIM(BIN), \
        RTRIM(LOWRANGE), \
        RTRIM(HIGHRANGE) \
    FROM EZBINRANGE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBINRange [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZBINRANGE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BIN, sizeof(BIN), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BIN) in EZBINRANGE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, LowRange, sizeof(LowRange), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LowRange) in EZBINRANGE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, HighRange, sizeof(HighRange), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(HighRange) in EZBINRANGE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( ezbinrange_ptr + i )->InstId, InstId );
        strcpy( ( ezbinrange_ptr + i )->BIN, BIN );
		strcpy( ( ezbinrange_ptr + i )->LowRange, LowRange );
		strcpy( ( ezbinrange_ptr + i )->HighRange, HighRange );
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( LowRange, 0, sizeof( LowRange ) );
		memset( HighRange, 0, sizeof( HighRange ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzBranchProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZBRANCHPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZBRANCHPROFILE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzBranchProfile( struct EzBranchProfileMemory *ezbranchprofile_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char InstId[ 13 ];
	char BranchCode[ 13 ];
	char BranchMapCode[ 13 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(INSTID), \
        RTRIM(BRANCHCODE), \
        RTRIM(BRANCHMAPCODE) \
    FROM EZBRANCHPROFILE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBranchProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZBRANCHPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BranchCode, sizeof(BranchCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BranchCode) in EZBRANCHPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, BranchMapCode, sizeof(BranchMapCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BranchMapCode) in EZBRANCHPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( ezbranchprofile_ptr + i )->InstId, InstId );
		strcpy( ( ezbranchprofile_ptr + i )->BranchCode, BranchCode );
		strcpy( ( ezbranchprofile_ptr + i )->BranchMapCode, BranchMapCode );
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( BranchCode, 0, sizeof( BranchCode ) );
		memset( BranchMapCode, 0, sizeof( BranchMapCode ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzDeviceTypeMapCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZDEVICEGROUP" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZDEVICEGROUP - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzDeviceTypeMap( struct EzDeviceTypeMapMemory *ezdevicetypemap_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char DeviceGroupId[ 17 ];
	int DeviceGroupVal;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(DEVICEGROUPID), \
		DEVICEGROUPVAL \
    FROM EZDEVICEGROUP;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzDeviceTypeMap [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, DeviceGroupId, sizeof(DeviceGroupId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceGroupId) in EZDEVICEGROUP [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &DeviceGroupVal, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceGroupVal) in EZDEVICEGROUP [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ezdevicetypemap_ptr + i,  0, sizeof( struct EzDeviceTypeMapMemory ) );
        strcpy( ( ezdevicetypemap_ptr + i )->DeviceGroupId, DeviceGroupId );
        ( ezdevicetypemap_ptr + i )->DeviceGroupVal = DeviceGroupVal;
		i++;
		memset( DeviceGroupId, 0, sizeof( DeviceGroupId ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzAuthPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZAUTHPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZAUTHPROPERTY - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzAuthProperty( struct EzAuthPropertyMemory *ezauthproperty_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char RecordId[ 17 ];
	char AuthGroupId[ 17 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char RespCode[ 4 ];
	char AuthList[ 256 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID), \
        RTRIM(AUTHGROUPID), \
        RTRIM(MSGTYPE), \
        RTRIM(TXNCODE), \
        RTRIM(RESPCODE), \
        RTRIM(AUTHLIST) \
    FROM EZAUTHPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzAuthProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZAUTHPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, AuthGroupId, sizeof(AuthGroupId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthGroupId) in EZAUTHPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZAUTHPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZAUTHPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZAUTHPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, AuthList, sizeof(AuthList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthList) in EZAUTHPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	memset( ( ezauthproperty_ptr + i ), 0, sizeof( struct EzAuthPropertyMemory ) );
        strcpy( ( ezauthproperty_ptr + i )->RecordId, RecordId );
		strcpy( ( ezauthproperty_ptr + i )->AuthGroupId, AuthGroupId );
		strcpy( ( ezauthproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezauthproperty_ptr + i )->TxnCode, TxnCode );
		strcpy( ( ezauthproperty_ptr + i )->RespCode, RespCode );
		strcpy( ( ezauthproperty_ptr + i )->AuthList, AuthList );
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( AuthGroupId, 0, sizeof( AuthGroupId ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( AuthList, 0, sizeof( AuthList ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzChannelPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZCHANNELPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZCHANNELPROPERTY - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzChannelProperty( struct EzChannelPropertyMemory *ezchannelproperty_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char ChannelName[ 33 ];
	char ChannelType[ 11 ];
	char DeviceType[ 17 ];
	char LayerId[ 11 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(CHANNELNAME), \
		RTRIM(CHANNELTYPE), \
		RTRIM(DEVICETYPE), \
		RTRIM(LAYERID) \
	FROM EZCHANNELPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzChannelProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZCHANNELPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ChannelType, sizeof(ChannelType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelType) in EZCHANNELPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, DeviceType, sizeof(DeviceType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceType) in EZCHANNELPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, LayerId, sizeof(LayerId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LayerId) in EZCHANNELPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezchannelproperty_ptr + i ), 0, sizeof( struct EzChannelPropertyMemory ) );
		strcpy( ( ezchannelproperty_ptr + i )->ChannelName, ChannelName );
		strcpy( ( ezchannelproperty_ptr + i )->ChannelType, ChannelType );
		strcpy( ( ezchannelproperty_ptr + i )->DeviceType, DeviceType );
		strcpy( ( ezchannelproperty_ptr + i )->LayerId, LayerId );
		i++;
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( ChannelType, 0, sizeof( ChannelType ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( LayerId, 0, sizeof( LayerId ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzEventPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZEVENTPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZEVENTPROPERTY - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzEventProperty( struct EzEventPropertyMemory *ezeventproperty_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	int RecordNo;
	char RecordId[ 17 ];
	char ChannelName[ 33 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char RespCode[ 4 ];
	char EventFlag;
	int EventTimeOut;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RECORDNO, \
    	RTRIM(RECORDID), \
		RTRIM(CHANNELNAME), \
		RTRIM(MSGTYPE), \
		RTRIM(TXNCODE), \
		RTRIM(RESPCODE), \
        EVENTFLAG, \
        EVENTTIMEOUT \
	FROM EZEVENTPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzEventProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &RecordNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordNo) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &EventFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EventFlag) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &EventTimeOut, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EventTimeOut) in EZEVENTPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezeventproperty_ptr + i ), 0, sizeof( struct EzEventPropertyMemory ) );
		( ezeventproperty_ptr + i )->RecordNo = RecordNo;
		strcpy( ( ezeventproperty_ptr + i )->RecordId, RecordId );
		strcpy( ( ezeventproperty_ptr + i )->ChannelName, ChannelName );
		strcpy( ( ezeventproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezeventproperty_ptr + i )->TxnCode,  TxnCode );
		strcpy( ( ezeventproperty_ptr + i )->RespCode,  RespCode );
		( ezeventproperty_ptr + i )->EventFlag = EventFlag;
		( ezeventproperty_ptr + i )->EventTimeOut = EventTimeOut;
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzInBoundMsgPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZINBOUNDMSGPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZINBOUNDMSGPROPERTY - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzInBoundMsgProperty( struct EzInBoundMsgPropertyMemory *ezinboundmsgproperty_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	int RecordNo;
	char RecordId[ 17 ];
	char MsgType[ 5 ];
	char ChannelType[ 11 ];
	char ChannelName[ 33 ];
	char MsgFlag;
	char LogFlag;
	char MsgProcessFlag;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RECORDNO, \
		RTRIM(RECORDID), \
		RTRIM(MSGTYPE), \
		RTRIM(CHANNELTYPE), \
        RTRIM(CHANNELNAME), \
        MSGFLAG, \
        LOGFLAG, \
        MSGPROCESSFLAG \
	FROM EZINBOUNDMSGPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzEventProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &RecordNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordNo) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, ChannelType, sizeof(ChannelType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelType) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &MsgFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgFlag) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &LogFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LogFlag) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &MsgProcessFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgProcessFlag) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezinboundmsgproperty_ptr + i ), 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		( ezinboundmsgproperty_ptr + i )->RecordNo = RecordNo;
		strcpy( ( ezinboundmsgproperty_ptr + i )->RecordId, RecordId );
		strcpy( ( ezinboundmsgproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezinboundmsgproperty_ptr + i )->ChannelName, ChannelName );
		strcpy( ( ezinboundmsgproperty_ptr + i )->ChannelType, ChannelType );
		( ezinboundmsgproperty_ptr + i )->MsgFlag = MsgFlag;
		( ezinboundmsgproperty_ptr + i )->LogFlag = LogFlag;
		( ezinboundmsgproperty_ptr + i )->MsgProcessFlag = MsgProcessFlag;
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( ChannelType, 0, sizeof( ChannelType ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzMsgTypePropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMSGTYPEPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMSGTYPEPROPERTY - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzMsgTypeProperty( struct EzMsgTypePropertyMemory *ezmsgtypeproperty_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	int MsgType;
	char MsgProperty;
	char LookUpProperty;

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		MSGTYPE, \
        MSGPROPERTY, \
        LOOKUPPROPERTY \
	FROM EZMSGTYPEPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzMsgTypeProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &MsgType, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &MsgProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgProperty) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_BINARY, &LookUpProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LookUpProperty) in EZINBOUNDMSGPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezmsgtypeproperty_ptr + i ), 0, sizeof( struct EzMsgTypePropertyMemory ) );
		( ezmsgtypeproperty_ptr + i )->MsgType = MsgType;
		( ezmsgtypeproperty_ptr + i )->MsgProperty = MsgProperty;
		( ezmsgtypeproperty_ptr + i )->LookUpProperty = LookUpProperty;
		i++;
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzTxnRefSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTXNREFSELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTXNREFSELECT - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzTxnRefSelect( struct EzTxnRefSelectMemory *eztxnrefselect_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	int RecordNo;
	char RecordId[ 17 ];
	char DeviceType[ 17 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char RespCode[ 4 ];
	char KeyFields[ 151 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RECORDNO, \
    	RTRIM(RECORDID), \
		RTRIM(DEVICETYPE), \
		RTRIM(MSGTYPE), \
        RTRIM(TXNCODE), \
        RTRIM(RESPCODE), \
        RTRIM(KEYFIELDS) \
	FROM EZTXNREFSELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnRefSelect [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &MsgType, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, DeviceType, sizeof(DeviceType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceType) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, KeyFields, sizeof(KeyFields), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(KeyFields) in EZTXNREFSELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( eztxnrefselect_ptr + i ), 0, sizeof( struct EzTxnRefSelectMemory ) );
		( eztxnrefselect_ptr + i )->RecordNo = RecordNo;
		strcpy( ( eztxnrefselect_ptr + i )->RecordId, RecordId );
		strcpy( ( eztxnrefselect_ptr + i )->DeviceType, DeviceType );
		strcpy( ( eztxnrefselect_ptr + i )->MsgType, MsgType );
		strcpy( ( eztxnrefselect_ptr + i )->TxnCode, TxnCode );
		strcpy( ( eztxnrefselect_ptr + i )->RespCode, RespCode );
		strcpy( ( eztxnrefselect_ptr + i )->KeyFields, KeyFields );
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( KeyFields, 0, sizeof( KeyFields ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzTxnRouteInfoCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTXNROUTEINFO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTXNROUTEINFO - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzTxnRouteInfo( struct EzTxnRouteInfoMemory *eztxnrouteinfo_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	int RecordNo;
	char RecordId[ 129 ];
	char IssuerInstRouteType[ 17 ];
	char AcquirerInstRouteType[ 17 ];
	char TxfInstRouteType[ 17 ];
	char SettInstRouteType[ 17 ];
	char FwdInstRouteType[ 17 ];
	char DeviceType[ 65 ];
	char DeviceSubType[ 65 ];
	char MsgType[ 65 ];
	char TxnCode[ 129 ];
	char RespCode[ 65 ];
	char RouteExp1[ 129 ];
	int RouteExpPriority1;
	char RouteExp2[ 129 ];
	int RouteExpPriority2;
	char ChannelName[ 65 ];
	char NetworkTypeList[ 65 ];
	char NetworkStatusList[ 65 ];
	int NetworkListPriority;
	char RouteCondition[ 129 ];
	int RouteConditionPriority;
	char RouteSelectList[ 129 ];

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RECORDNO, \
    	RTRIM(RECORDID), \
	 	RTRIM(ISSUERINSTROUTETYPE), \
	 	RTRIM(ACQUIRERINSTROUTETYPE), \
	 	RTRIM(TXFINSTROUTETYPE), \
	 	RTRIM(SETTINSTROUTETYPE), \
	 	RTRIM(FWDINSTROUTETYPE), \
   	 	RTRIM(DEVICETYPE), \
	 	RTRIM(DEVICESUBTYPE), \
	 	RTRIM(MSGTYPE), \
	 	RTRIM(TXNCODE), \
	 	RTRIM(RESPCODE), \
	 	RTRIM(ROUTEEXP1), \
	 	ROUTEEXPPRIORITY1, \
	 	RTRIM(ROUTEEXP2), \
	 	ROUTEEXPPRIORITY2, \
	 	RTRIM(CHANNELNAME), \
	 	RTRIM(NETWORKTYPELIST), \
	 	RTRIM(NETWORKSTATUSLIST), \
	 	NETWORKLISTPRIORITY, \
	 	RTRIM(ROUTECONDITION), \
	 	ROUTECONDITIONPRIORITY, \
	 	RTRIM(ROUTESELECTLIST) \
    FROM EZTXNROUTEINFO;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnRouteInfo [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &RecordNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordNo) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, IssuerInstRouteType, sizeof(IssuerInstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(IssuerInstRouteType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, AcquirerInstRouteType, sizeof(AcquirerInstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AcquirerInstRouteType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TxfInstRouteType, sizeof(TxfInstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxfInstRouteType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, SettInstRouteType, sizeof(SettInstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SettInstRouteType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, FwdInstRouteType, sizeof(FwdInstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FwdInstRouteType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, DeviceType, sizeof(DeviceType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, DeviceSubType, sizeof(DeviceSubType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceSubType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, RouteExp1, sizeof(RouteExp1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteExp1) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_SLONG, &RouteExpPriority1, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteExpPriority1) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_CHAR, RouteExp2, sizeof(RouteExp2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteExp2) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &RouteExpPriority2, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteExpPriority2) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_CHAR, NetworkTypeList, sizeof(NetworkTypeList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkTypeList) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_CHAR, NetworkStatusList, sizeof(NetworkStatusList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkStatusList) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 20, SQL_C_SLONG, &NetworkListPriority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkListPriority) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 21, SQL_C_CHAR, RouteCondition, sizeof(RouteCondition), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteCondition) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 22, SQL_C_SLONG, &RouteConditionPriority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteConditionPriority) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 23, SQL_C_CHAR, RouteSelectList, sizeof(RouteSelectList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteSelectList) in EZTXNROUTEINFO [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ( eztxnrouteinfo_ptr + i ), 0, sizeof( struct EzTxnRouteInfoMemory ) );
        ( eztxnrouteinfo_ptr + i )->RecordNo = RecordNo;
        strcpy( ( eztxnrouteinfo_ptr + i )->RecordId, RecordId );
        strcpy( ( eztxnrouteinfo_ptr + i )->IssuerInstRouteType, IssuerInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->AcquirerInstRouteType, AcquirerInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->TxfInstRouteType, TxfInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->SettInstRouteType, SettInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->FwdInstRouteType, FwdInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->DeviceType, DeviceType );
        strcpy( ( eztxnrouteinfo_ptr + i )->DeviceSubType, DeviceSubType );
        strcpy( ( eztxnrouteinfo_ptr + i )->MsgType, MsgType );
        strcpy( ( eztxnrouteinfo_ptr + i )->TxnCode, TxnCode );
        strcpy( ( eztxnrouteinfo_ptr + i )->RespCode, RespCode );
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteExp1, RouteExp1 );
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteExp2, RouteExp2 );
        ( eztxnrouteinfo_ptr + i )->RouteExpPriority1 = RouteExpPriority1;
        ( eztxnrouteinfo_ptr + i )->RouteExpPriority2 = RouteExpPriority2;
        strcpy( ( eztxnrouteinfo_ptr + i )->ChannelName, ChannelName );
        strcpy( ( eztxnrouteinfo_ptr + i )->NetworkTypeList, NetworkTypeList );
        strcpy( ( eztxnrouteinfo_ptr + i )->NetworkStatusList, NetworkStatusList );
        ( eztxnrouteinfo_ptr + i )->NetworkListPriority = NetworkListPriority;
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteCondition, RouteCondition );
        ( eztxnrouteinfo_ptr + i )->RouteConditionPriority = RouteConditionPriority;
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteSelectList, RouteSelectList );
        ( eztxnrouteinfo_ptr + i )->DebugFlag = '0';
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( IssuerInstRouteType, 0, sizeof( IssuerInstRouteType ) );
		memset( AcquirerInstRouteType, 0, sizeof( AcquirerInstRouteType ) );
		memset( TxfInstRouteType, 0, sizeof( TxfInstRouteType ) );
		memset( SettInstRouteType, 0, sizeof( SettInstRouteType ) );
		memset( FwdInstRouteType, 0, sizeof( FwdInstRouteType ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( DeviceSubType, 0, sizeof( DeviceSubType ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( RouteExp1, 0, sizeof( RouteExp1 ) );
		memset( RouteExp2, 0, sizeof( RouteExp2 ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( NetworkTypeList, 0, sizeof( NetworkTypeList ) );
		memset( NetworkStatusList, 0, sizeof( NetworkStatusList ) );
		memset( RouteCondition, 0, sizeof( RouteCondition ) );
		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzMsgTranslateCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMSGTRANSLATE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMSGTRANSLATE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzMsgTranslate( struct EzMsgTranslateMemory *ezmsgtranslate_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char MsgTranslateId[ 17 ];
	char TranslateDesc[ 256 ];

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(MSGTRANSLATEID), \
        RTRIM(TRANSLATEDESC) \
    FROM EZMSGTRANSLATE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzMsgTranslate [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MsgTranslateId, sizeof(MsgTranslateId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgTranslateId) in EZMSGTRANSLATE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TranslateDesc, sizeof(TranslateDesc), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TranslateDesc) in EZMSGTRANSLATE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }


    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezmsgtranslate_ptr + i ), 0, sizeof( struct EzMsgTranslateMemory ) );
		strcpy( ( ezmsgtranslate_ptr + i )->MsgTranslateId, MsgTranslateId );
		strcpy( ( ezmsgtranslate_ptr + i )->TranslateDesc, TranslateDesc );
		i++;
		memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
		memset( TranslateDesc, 0, sizeof( TranslateDesc ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzTxnRouteSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTXNROUTESELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTXNROUTESELECT - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzTxnRouteSelect( struct EzTxnRouteSelectMemory *eztxnrouteselect_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char RouteSelectId[ 17 ];
	char ChannelName[ 33 ];
	char MsgTranslateId[ 17 ];
	char LogFlag;

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(ROUTESELECTID), \
        RTRIM(CHANNELNAME), \
        RTRIM(MSGTRANSLATEID), \
        LOGFLAG \
	FROM EZTXNROUTESELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnRouteInfo [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RouteSelectId, sizeof(RouteSelectId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RouteSelectId) in EZTXNROUTESELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZTXNROUTESELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MsgTranslateId, sizeof(MsgTranslateId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgTranslateId) in EZTXNROUTESELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &LogFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LogFlag) in EZTXNROUTESELECT [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }


    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( eztxnrouteselect_ptr + i ), 0, sizeof( struct EzTxnRouteSelectMemory ) );
		strcpy( ( eztxnrouteselect_ptr + i )->RouteSelectId, RouteSelectId );
		strcpy( ( eztxnrouteselect_ptr + i )->ChannelName, ChannelName );
		strcpy( ( eztxnrouteselect_ptr + i )->MsgTranslateId, MsgTranslateId );
		( eztxnrouteselect_ptr + i )->LogFlag = LogFlag;
		i++;
		memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzTxnMsgOrderCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTXNMSGORDER" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTXNMSGORDER - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzTxnMsgOrder( struct EzTxnMsgOrderMemory *eztxnmsgorder_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char RecordId[ 17 ];
	char SrcChannel[ 33 ];
	char DestChannel[ 33 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char RespCode[ 4 ];
	short OrderNo;

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(RECORDID), \
		RTRIM(SRCCHANNEL), \
		RTRIM(DESTCHANNEL), \
		RTRIM(MSGTYPE), \
		RTRIM(TXNCODE), \
        RTRIM(RESPCODE), \
        ORDERNO \
	FROM EZTXNMSGORDER;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnMsgOrder [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, SrcChannel, sizeof(SrcChannel), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SrcChannel) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, DestChannel, sizeof(DestChannel), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DestChannel) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &OrderNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OrderNo) in EZTXNMSGORDER [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( eztxnmsgorder_ptr + i ), 0, sizeof( struct EzTxnMsgOrderMemory ) );
		strcpy( ( eztxnmsgorder_ptr + i )->RecordId, RecordId );
		strcpy( ( eztxnmsgorder_ptr + i )->SrcChannel, SrcChannel );
		strcpy( ( eztxnmsgorder_ptr + i )->DestChannel, DestChannel );
		strcpy( ( eztxnmsgorder_ptr + i )->MsgType, MsgType );
		strcpy( ( eztxnmsgorder_ptr + i )->TxnCode, TxnCode );
		strcpy( ( eztxnmsgorder_ptr + i )->RespCode, RespCode );
		( eztxnmsgorder_ptr + i )->OrderNo = OrderNo;
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( SrcChannel, 0, sizeof( SrcChannel ) );
		memset( DestChannel, 0, sizeof( DestChannel ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzInstExtNtwkProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZINSTEXTNTWKPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZINSTEXTNTWKPROFILE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzInstExtNtwkProfile( struct EzInstExtNtwkProfileMemory *ezinstextntwkprofile_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char InstId[ 13 ];
	char ExtNetworkId[ 17 ];
	char AcqInstCode[ 17 ];
	char TxnCodeList[ 65 ];
	char AddFee1[ 129 ];
	char AddFee2[ 129 ];
	char AddFee3[ 129 ];

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(INSTID), \
		RTRIM(EXTNETWORKID), \
		RTRIM(ACQINSTCODE), \
		RTRIM(TXNCODELIST), \
		RTRIM(ADDFEE1), \
		RTRIM(ADDFEE2), \
        RTRIM(ADDFEE3) \
    FROM EZINSTEXTNTWKPROFILE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstExtNtwkProfile [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ExtNetworkId, sizeof(ExtNetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ExtNetworkId) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, AcqInstCode, sizeof(AcqInstCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AcqInstCode) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TxnCodeList, sizeof(TxnCodeList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCodeList) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, AddFee1, sizeof(AddFee1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AddFee1) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, AddFee2, sizeof(AddFee2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AddFee2) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, AddFee3, sizeof(AddFee3), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AddFee3) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezinstextntwkprofile_ptr + i ), 0, sizeof( struct EzInstExtNtwkProfileMemory ) );
		strcpy( ( ezinstextntwkprofile_ptr + i )->InstId, InstId );
		strcpy( ( ezinstextntwkprofile_ptr + i )->ExtNetworkId, ExtNetworkId );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AcqInstCode, AcqInstCode );
		strcpy( ( ezinstextntwkprofile_ptr + i )->TxnCodeList, TxnCodeList );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AddFee1, AddFee1 );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AddFee2, AddFee2 );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AddFee3, AddFee3 );
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
		memset( AcqInstCode, 0, sizeof( AcqInstCode ) );
		memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
		memset( AddFee1, 0, sizeof( AddFee1 ) );
		memset( AddFee2, 0, sizeof( AddFee2 ) );
		memset( AddFee3, 0, sizeof( AddFee3 ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzExtNtwkProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZEXTNTWKPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZEXTNTWKPROFILE - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzExtNtwkProfile( struct EzExtNtwkProfileMemory *ezextntwkprofile_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char ExtNetworkId[ 17 ];
	char TxnCodeList[ 65 ];
	char TxnCountCheckReq[ 33 ];
	char TxnAmountCheckReq[ 33 ];
	char MaxAmountPerTxn[ 129 ];
	char MaxAmount[ 129 ];
	char MaxAmountInterval[ 129 ];
	char MaxAmountIntervalType[ 33 ];
	char MaxAmountAction[ 33 ];
	char MaxAmountFee[ 129 ];
	char MaxCount[ 129 ];
	char MaxCountInterval[ 129 ];
	char MaxCountIntervalType[ 33 ];
	char MaxCountAction[ 33 ];
	char MaxCountFee[ 129 ];

	odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
		RTRIM(EXTNETWORKID), \
		RTRIM(TXNCODELIST), \
		RTRIM(TXNCOUNTCHECKREQ), \
		RTRIM(TXNAMOUNTCHECKREQ), \
        RTRIM(MAXAMOUNTPERTXN), \
        RTRIM(MAXAMOUNT), \
        RTRIM(MAXAMOUNTINTERVAL), \
        RTRIM(MAXAMOUNTINTERVALTYPE), \
        RTRIM(MAXAMOUNTACTION), \
        RTRIM(MAXAMOUNTFEE), \
        RTRIM(MAXCOUNT), \
        RTRIM(MAXCOUNTINTERVAL), \
        RTRIM(MAXCOUNTINTERVALTYPE), \
        RTRIM(MAXCOUNTACTION), \
        RTRIM(MAXCOUNTFEE) \
    FROM EZEXTNTWKPROFILE;");

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstExtNtwkProfile [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, ExtNetworkId, sizeof(ExtNetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ExtNetworkId) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TxnCodeList, sizeof(TxnCodeList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCodeList) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TxnCountCheckReq, sizeof(TxnCountCheckReq), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCountCheckReq) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TxnAmountCheckReq, sizeof(TxnAmountCheckReq), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnAmountCheckReq) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, MaxAmountPerTxn, sizeof(MaxAmountPerTxn), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxAmountPerTxn) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, MaxAmount, sizeof(MaxAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxAmount) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, MaxAmountInterval, sizeof(MaxAmountInterval), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxAmountInterval) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, MaxAmountIntervalType, sizeof(MaxAmountIntervalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxAmountIntervalType) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, MaxAmountAction, sizeof(MaxAmountAction), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxAmountAction) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, MaxAmountFee, sizeof(MaxAmountFee), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxAmountFee) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, MaxCount, sizeof(MaxCount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxCount) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, MaxCountInterval, sizeof(MaxCountInterval), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxCountInterval) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, MaxCountIntervalType, sizeof(MaxCountIntervalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxCountIntervalType) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, MaxCountAction, sizeof(MaxCountAction), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxCountAction) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_CHAR, MaxCountFee, sizeof(MaxCountFee), &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
			dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxCountFee) in EZINSTEXTNTWKPROFILE [ %d ]", odbcret );
			SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
			return -1;
	}

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezextntwkprofile_ptr + i ), 0, sizeof( struct EzExtNtwkProfileMemory ) );
		strcpy( ( ezextntwkprofile_ptr + i )->ExtNetworkId, ExtNetworkId );
		strcpy( ( ezextntwkprofile_ptr + i )->TxnCodeList, TxnCodeList );
		strcpy( ( ezextntwkprofile_ptr + i )->TxnCountCheckReq, TxnCountCheckReq );
		strcpy( ( ezextntwkprofile_ptr + i )->TxnAmountCheckReq, TxnAmountCheckReq );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountPerTxn, MaxAmountPerTxn );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmount, MaxAmount );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountInterval, MaxAmountInterval );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountIntervalType, MaxAmountIntervalType );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountAction, MaxAmountAction );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountFee, MaxAmountFee );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCount, MaxCount );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountInterval, MaxCountInterval );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountIntervalType, MaxCountIntervalType );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountAction, MaxCountAction );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountFee, MaxCountFee );
		i++;
		memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
		memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
		memset( TxnCountCheckReq, 0, sizeof( TxnCountCheckReq ) );
		memset( TxnAmountCheckReq, 0, sizeof( TxnAmountCheckReq ) );
		memset( MaxAmountPerTxn, 0, sizeof( MaxAmountPerTxn ) );
		memset( MaxAmount, 0, sizeof( MaxAmount ) );
		memset( MaxAmountInterval, 0, sizeof( MaxAmountInterval ) );
		memset( MaxAmountIntervalType, 0, sizeof( MaxAmountIntervalType ) );
		memset( MaxAmountAction, 0, sizeof( MaxAmountAction ) );
		memset( MaxAmountFee, 0, sizeof( MaxAmountFee ) );
		memset( MaxCount, 0, sizeof( MaxCount ) );
		memset( MaxCountInterval, 0, sizeof( MaxCountInterval ) );
		memset( MaxCountIntervalType, 0, sizeof( MaxCountIntervalType ) );
		memset( MaxCountAction, 0, sizeof( MaxCountAction ) );
		memset( MaxCountFee, 0, sizeof( MaxCountFee ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstMgrODBC :: getEzSafPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZSAFPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZSAFPROPERTY - Count[%d]", count);

    return count;
}

int EzInstMgrODBC :: LoadEzSafProperty( struct EzSafPropertyMemory *ezsafproperty_ptr, int *SqlErr )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char MsgIndicator;
	char InstId[ 13 ];
	char NetworkId[ 17 ];
	char NetworkStatus[ 17 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char RespCode[ 4 ];
	char RevCode[ 7 ];
	char SafAction;
	char RecordId[ 17 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	MSGINDICATOR,\
		RTRIM(INSTID),\
        RTRIM(NETWORKID),\
        RTRIM(NETWORKSTATUS),\
        RTRIM(MSGTYPE),\
        RTRIM(TXNCODE),\
        RTRIM(RESPCODE),\
        RTRIM(REVCODE),\
        SAFACTION,\
    	RTRIM(RECORDID)\
   	FROM EZSAFPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzSafProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_BINARY, &MsgIndicator, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgIndicator) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, NetworkStatus, sizeof(NetworkStatus), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(NetworkStatus) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DeviceType) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, RevCode, sizeof(RevCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RevCode) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9,  SQL_C_BINARY, &SafAction, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SafAction) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZSAFPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezsafproperty_ptr + i ), 0, sizeof( struct EzSafPropertyMemory ) );
		( ezsafproperty_ptr + i )->MsgIndicator = MsgIndicator;
		strcpy( ( ezsafproperty_ptr + i )->InstId, InstId );
		strcpy( ( ezsafproperty_ptr + i )->NetworkId, NetworkId );
		strcpy( ( ezsafproperty_ptr + i )->NetworkStatus, NetworkStatus );
		strcpy( ( ezsafproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezsafproperty_ptr + i )->TxnCode, TxnCode );
		strcpy( ( ezsafproperty_ptr + i )->RespCode, RespCode );
		strcpy( ( ezsafproperty_ptr + i )->RevCode, RevCode );
		( ezsafproperty_ptr + i )->SafAction = SafAction;
		strcpy( ( ezsafproperty_ptr + i )->RecordId, RecordId );
		i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( NetworkId, 0, sizeof( NetworkId ) );
		memset( NetworkStatus, 0, sizeof( NetworkStatus ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( RevCode, 0, sizeof( RevCode ) );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}
