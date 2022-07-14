/*
 * ezinstdbodbc.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: mohanraj
 */

#include <ezlink/ezinstdbodbc.h>

int EzInstDbODBC :: initEzInstDbODBC( const char *TaskName, EzDebugUtil *dptr )
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

int EzInstDbODBC :: readEzInstRouteType( const char *I_InstRouteType, struct EzInstRouteTypeMemory *instroutetype_ptr )
{
	int i = 0;
	SQLHSTMT hstmt;
	SQLRETURN obdcret;
	SQLLEN Len;
	char SqlStmt[ 1024 ];
	char InstRouteType[ 17 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }
    memset( InstRouteType, 0, sizeof( InstRouteType ) );
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT RTRIM(INSTROUTETYPE) FROM EZINSTROUTETYPE WHERE RTRIM(INSTROUTETYPE) ='%s'", I_InstRouteType );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
		dptr->trace( DEBUG_ERROR, "Error in Executing in EZINSTROUTETYPE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstRouteType, sizeof(InstRouteType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Binding INSTROUTETYPE in EZINSTROUTETYPE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    memset( InstRouteType, 0, sizeof( InstRouteType ) );
	if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
	{
		memset( instroutetype_ptr->InstRouteType, 0, sizeof( instroutetype_ptr->InstRouteType ) );
		strcpy( instroutetype_ptr->InstRouteType, InstRouteType );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC ::  readEzInstProfile( const char *I_InstId, struct EzInstProfileMemory *instprofile_ptr )
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
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzInstSelect( const char *I_RecordNo, struct EzInstSelectMemory *instselect_ptr )
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
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstDbODBC :: readEzBINSelect( const char *I_RecordNo, struct EzBINSelectMemory *binselect_ptr )
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
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzNetworkSelect( const char *I_RecordNo, struct EzNetworkSelectMemory *networkselect_ptr )
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
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzBINProfile( const char *I_InstId, const char *I_BIN, struct EzBINProfileMemory *binprofile_ptr )
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
    sprintf( SqlStmt,  "SELECT \
    	RTRIM(INSTID), \
		RTRIM(BIN), \
		RTRIM(PRODUCTCODE), \
		RTRIM(PRODUCTNAME), \
		RTRIM(BINTYPE), \
		RTRIM(ROUTETYPE), \
        RTRIM(TXNLIST) \
    FROM EZBINPROFILE WHERE RTRIM(INSTID)='%s' AND RTRIM(BIN)='%s';", I_InstId, I_BIN );

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
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzBranchProfile( const char *I_InstId, const char *I_BranchCode, struct EzBranchProfileMemory *branchprofile_ptr )
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
    sprintf( SqlStmt,  "SELECT \
    	RTRIM(INSTID), \
        RTRIM(BRANCHCODE), \
        RTRIM(BRANCHMAPCODE) \
    FROM EZBRANCHPROFILE WHERE RTRIM(INSTID)='%s' AND RTRIM(BRANCHCODE)='%s';", I_InstId, I_BranchCode );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzBranchProfile [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( InstId, 0, sizeof( InstId ) );
	memset( BranchCode, 0, sizeof( BranchCode ) );
	memset( BranchMapCode, 0, sizeof( BranchMapCode ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( branchprofile_ptr->InstId, InstId );
    	strcpy( branchprofile_ptr->BranchCode, BranchCode );
    	strcpy( branchprofile_ptr->BranchMapCode, BranchMapCode );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzAuthProperty( const char *I_RecordNo, struct EzAuthPropertyMemory *ezauthproperty_ptr )
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
    sprintf( SqlStmt,  "SELECT \
    	RTRIM(RECORDID), \
        RTRIM(AUTHGROUPID), \
        RTRIM(MSGTYPE), \
        RTRIM(TXNCODE), \
        RTRIM(RESPCODE), \
        RTRIM(AUTHLIST) \
    FROM EZAUTHPROPERTY WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzAuthProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( AuthGroupId, 0, sizeof( AuthGroupId ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	memset( AuthList, 0, sizeof( AuthList ) );

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

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, RespCode, sizeof(int), &Len );
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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	memset( ezauthproperty_ptr, 0, sizeof( struct EzAuthPropertyMemory ) );
    	strcpy( ezauthproperty_ptr->RecordId, RecordId );
    	strcpy( ezauthproperty_ptr->AuthGroupId, AuthGroupId );
    	strcpy( ezauthproperty_ptr->MsgType, MsgType );
    	strcpy( ezauthproperty_ptr->TxnCode, TxnCode );
    	strcpy( ezauthproperty_ptr->RespCode, RespCode );
    	strcpy( ezauthproperty_ptr->AuthList, AuthList );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzChannelProperty( const char *I_ChannelName, struct EzChannelPropertyMemory *ezchannelproperty_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		RTRIM(CHANNELNAME), \
		RTRIM(CHANNELTYPE), \
		RTRIM(DEVICETYPE), \
		RTRIM(LAYERID) \
	FROM EZCHANNELPROPERTY WHERE RTRIM(CHANNELNAME)='%s';", I_ChannelName );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzChannelProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( ChannelType, 0, sizeof( ChannelType ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( LayerId, 0, sizeof( LayerId ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezchannelproperty_ptr, 0, sizeof( struct EzChannelPropertyMemory ) );
		strcpy( ezchannelproperty_ptr->ChannelName, ChannelName );
		strcpy( ezchannelproperty_ptr->ChannelType, ChannelType );
		strcpy( ezchannelproperty_ptr->DeviceType, DeviceType );
		strcpy( ezchannelproperty_ptr->LayerId, LayerId );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzEventProperty( const char *I_RecordNo, struct EzEventPropertyMemory *ezeventproperty_ptr )
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
    sprintf( SqlStmt,  "SELECT \
    	RECORDNO, \
    	RTRIM(RECORDID), \
		RTRIM(CHANNELNAME), \
		RTRIM(MSGTYPE), \
		RTRIM(TXNCODE), \
		RTRIM(RESPCODE), \
        EVENTFLAG, \
        EVENTTIMEOUT \
	FROM EZEVENTPROPERTY WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzEventProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
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
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzMsgTypePropertyTable( int I_MsgType, struct EzMsgTypePropertyMemory *ezmsgtypeproperty_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		MSGTYPE, \
        MSGPROPERTY, \
        LOOKUPPROPERTY \
	FROM EZMSGTYPEPROPERTY  WHERE RTRIM(MSGTYPE)='%s';", I_MsgType );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezmsgtypeproperty_ptr, 0, sizeof( struct EzMsgTypePropertyMemory ) );
		ezmsgtypeproperty_ptr->MsgType = MsgType;
		ezmsgtypeproperty_ptr->MsgProperty = MsgProperty;
		ezmsgtypeproperty_ptr->LookUpProperty = LookUpProperty;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzMsgTranslate( const char *I_MsgTranslateId, struct EzMsgTranslateMemory *ezmsgtranslate_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		RTRIM(MSGTRANSLATEID), \
        RTRIM(TRANSLATEDESC) \
    FROM EZMSGTRANSLATE WHERE RTRIM(MSGTRANSLATEID)='%s';", I_MsgTranslateId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzMsgTranslate [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
	memset( TranslateDesc, 0, sizeof( TranslateDesc ) );

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


    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezmsgtranslate_ptr, 0, sizeof( struct EzMsgTranslateMemory ) );
		strcpy( ezmsgtranslate_ptr->MsgTranslateId, MsgTranslateId );
		strcpy( ezmsgtranslate_ptr->TranslateDesc, TranslateDesc );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzDeviceTypeMap( const char *I_DeviceGroupId, struct EzDeviceTypeMapMemory *ezdevicetypemap_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		RTRIM(DEVICEGROUPID), \
		DEVICEGROUPVAL \
    FROM EZDEVICEGROUP WHERE RTRIM(DEVICEGROUPID)='%s';", I_DeviceGroupId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzDeviceTypeMap [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( DeviceGroupId, 0, sizeof( DeviceGroupId ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ezdevicetypemap_ptr,  0, sizeof( struct EzDeviceTypeMapMemory ) );
        strcpy( ezdevicetypemap_ptr->DeviceGroupId, DeviceGroupId );
        ezdevicetypemap_ptr->DeviceGroupVal = DeviceGroupVal;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzTxnRefSelect( const char *I_RecordNo, struct EzTxnRefSelectMemory *eztxnrefselect_ptr )
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
    sprintf( SqlStmt,  "SELECT \
    	RECORDNO, \
    	RTRIM(RECORDID), \
		RTRIM(DEVICETYPE), \
		RTRIM(MSGTYPE), \
        RTRIM(TXNCODE), \
        RTRIM(RESPCODE), \
        RTRIM(KEYFIELDS) \
	FROM EZTXNREFSELECT  WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnRefSelect [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	memset( KeyFields, 0, sizeof( KeyFields ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( eztxnrefselect_ptr, 0, sizeof( struct EzTxnRefSelectMemory ) );
		eztxnrefselect_ptr->RecordNo = RecordNo;
		strcpy( eztxnrefselect_ptr->RecordId, RecordId );
		strcpy( eztxnrefselect_ptr->DeviceType, DeviceType );
		strcpy( eztxnrefselect_ptr->MsgType, MsgType );
		strcpy( eztxnrefselect_ptr->TxnCode, TxnCode );
		strcpy( eztxnrefselect_ptr->RespCode, RespCode );
		strcpy( eztxnrefselect_ptr->KeyFields, KeyFields );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzTxnRouteSelect( const char *I_RouteSelectId, struct EzTxnRouteSelectMemory *eztxnrouteselect_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		RTRIM(ROUTESELECTID), \
        RTRIM(CHANNELNAME), \
        RTRIM(MSGTRANSLATEID), \
        LOGFLAG \
	FROM EZTXNROUTESELECT WHERE RTRIM(ROUTESELECTID)='%s';", I_RouteSelectId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnRouteInfo [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );

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


    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( eztxnrouteselect_ptr, 0, sizeof( struct EzTxnRouteSelectMemory ) );
		strcpy( eztxnrouteselect_ptr->RouteSelectId, RouteSelectId );
		strcpy( eztxnrouteselect_ptr->ChannelName, ChannelName );
		strcpy( eztxnrouteselect_ptr->MsgTranslateId, MsgTranslateId );
		( eztxnrouteselect_ptr + i )->LogFlag = LogFlag;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzTxnRouteInfo( const char *I_RecordNo, struct EzTxnRouteInfoMemory *eztxnrouteinfo_ptr )
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
    sprintf( SqlStmt,  "SELECT \
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
    FROM EZTXNROUTEINFO  WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnRouteInfo [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( eztxnrouteinfo_ptr, 0, sizeof( struct EzTxnRouteInfoMemory ) );
        eztxnrouteinfo_ptr->RecordNo = RecordNo;
        strcpy( eztxnrouteinfo_ptr->RecordId, RecordId );
        strcpy( eztxnrouteinfo_ptr->IssuerInstRouteType, IssuerInstRouteType );
        strcpy( eztxnrouteinfo_ptr->AcquirerInstRouteType, AcquirerInstRouteType );
        strcpy( eztxnrouteinfo_ptr->TxfInstRouteType, TxfInstRouteType );
        strcpy( eztxnrouteinfo_ptr->SettInstRouteType, SettInstRouteType );
        strcpy( eztxnrouteinfo_ptr->FwdInstRouteType, FwdInstRouteType );
        strcpy( eztxnrouteinfo_ptr->DeviceType, DeviceType );
        strcpy( eztxnrouteinfo_ptr->DeviceSubType, DeviceSubType );
        strcpy( eztxnrouteinfo_ptr->MsgType, MsgType );
        strcpy( eztxnrouteinfo_ptr->TxnCode, TxnCode );
        strcpy( eztxnrouteinfo_ptr->RespCode, RespCode );
        strcpy( eztxnrouteinfo_ptr->RouteExp1, RouteExp1 );
        strcpy( eztxnrouteinfo_ptr->RouteExp2, RouteExp2 );
        eztxnrouteinfo_ptr->RouteExpPriority1 = RouteExpPriority1;
        eztxnrouteinfo_ptr->RouteExpPriority2 = RouteExpPriority2;
        strcpy( eztxnrouteinfo_ptr->ChannelName, ChannelName );
        strcpy( eztxnrouteinfo_ptr->NetworkTypeList, NetworkTypeList );
        strcpy( eztxnrouteinfo_ptr->NetworkStatusList, NetworkStatusList );
        eztxnrouteinfo_ptr->NetworkListPriority = NetworkListPriority;
        strcpy( eztxnrouteinfo_ptr->RouteCondition, RouteCondition );
        eztxnrouteinfo_ptr->RouteConditionPriority = RouteConditionPriority;
        strcpy( eztxnrouteinfo_ptr->RouteSelectList, RouteSelectList );
        eztxnrouteinfo_ptr->DebugFlag = '0';
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzInBoundMsgProperty( const char *I_RecordNo, struct EzInBoundMsgPropertyMemory *ezinboundmsgproperty_ptr )
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
    sprintf( SqlStmt,  "SELECT \
    	RECORDNO, \
		RTRIM(RECORDID), \
		RTRIM(MSGTYPE), \
		RTRIM(CHANNELTYPE), \
        RTRIM(CHANNELNAME), \
        MSGFLAG, \
        LOGFLAG, \
        MSGPROCESSFLAG \
	FROM EZINBOUNDMSGPROPERTY WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzEventProperty [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( ChannelType, 0, sizeof( ChannelType ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezinboundmsgproperty_ptr, 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		ezinboundmsgproperty_ptr->RecordNo = RecordNo;
		strcpy( ezinboundmsgproperty_ptr->RecordId, RecordId );
		strcpy( ezinboundmsgproperty_ptr->MsgType, MsgType );
		strcpy( ezinboundmsgproperty_ptr->ChannelName, ChannelName );
		strcpy( ezinboundmsgproperty_ptr->ChannelType, ChannelType );
		ezinboundmsgproperty_ptr->MsgFlag = MsgFlag;
		ezinboundmsgproperty_ptr->LogFlag = LogFlag;
		ezinboundmsgproperty_ptr->MsgProcessFlag = MsgProcessFlag;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzTxnMsgOrder( const char *I_RecordNo, struct EzTxnMsgOrderMemory *eztxnmsgorder_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		RTRIM(RECORDID), \
		RTRIM(SRCCHANNEL), \
		RTRIM(DESTCHANNEL), \
		RTRIM(MSGTYPE), \
		RTRIM(TXNCODE), \
        RTRIM(RESPCODE), \
        ORDERNO \
	FROM EZTXNMSGORDER WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTxnMsgOrder [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( SrcChannel, 0, sizeof( SrcChannel ) );
	memset( DestChannel, 0, sizeof( DestChannel ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( eztxnmsgorder_ptr, 0, sizeof( struct EzTxnMsgOrderMemory ) );
		strcpy( eztxnmsgorder_ptr->RecordId, RecordId );
		strcpy( eztxnmsgorder_ptr->SrcChannel, SrcChannel );
		strcpy( eztxnmsgorder_ptr->DestChannel, DestChannel );
		strcpy( eztxnmsgorder_ptr->MsgType, MsgType );
		strcpy( eztxnmsgorder_ptr->TxnCode, TxnCode );
		strcpy( eztxnmsgorder_ptr->RespCode, RespCode );
		eztxnmsgorder_ptr->OrderNo = OrderNo;
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzInstExtNtwkProfile( const char *I_InstId, const char *I_ExtNetworkId, struct EzInstExtNtwkProfileMemory *ezinstextntwkprofile_ptr )
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
    sprintf( SqlStmt,  "SELECT \
		RTRIM(INSTID), \
		RTRIM(EXTNETWORKID), \
		RTRIM(ACQINSTCODE), \
		RTRIM(TXNCODELIST), \
		RTRIM(ADDFEE1), \
		RTRIM(ADDFEE2), \
        RTRIM(ADDFEE3) \
    FROM EZINSTEXTNTWKPROFILE  WHERE RTRIM(INSTID)='%s' AND RTRIM(EXTNETWORKID)='%s';", I_InstId, I_ExtNetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstExtNtwkProfile [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( InstId, 0, sizeof( InstId ) );
	memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
	memset( AcqInstCode, 0, sizeof( AcqInstCode ) );
	memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
	memset( AddFee1, 0, sizeof( AddFee1 ) );
	memset( AddFee2, 0, sizeof( AddFee2 ) );
	memset( AddFee3, 0, sizeof( AddFee3 ) );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezinstextntwkprofile_ptr, 0, sizeof( struct EzInstExtNtwkProfileMemory ) );
		strcpy( ezinstextntwkprofile_ptr->InstId, InstId );
		strcpy( ezinstextntwkprofile_ptr->ExtNetworkId, ExtNetworkId );
		strcpy( ezinstextntwkprofile_ptr->AcqInstCode, AcqInstCode );
		strcpy( ezinstextntwkprofile_ptr->TxnCodeList, TxnCodeList );
		strcpy( ezinstextntwkprofile_ptr->AddFee1, AddFee1 );
		strcpy( ezinstextntwkprofile_ptr->AddFee2, AddFee2 );
		strcpy( ezinstextntwkprofile_ptr->AddFee3, AddFee3 );
	}
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 1;
}

int EzInstDbODBC :: readEzExtNtwkProfile( const char *I_ExtNetworkId, struct EzExtNtwkProfileMemory *ezextntwkprofile_ptr )
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
    sprintf( SqlStmt,  "SELECT \
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
    FROM EZEXTNTWKPROFILE WHERE RTRIM(EXTNETWORKID)='%s';", I_ExtNetworkId);

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzInstExtNtwkProfile [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
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
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	 	return 1;
	}
	else
	{
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
	}
}

int EzInstDbODBC :: readEzSafProperty( const char *I_RecordNo, struct EzSafPropertyMemory *ezsafproperty_ptr )
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
    sprintf( SqlStmt,  "SELECT \
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
   	FROM EZSAFPROPERTY WHERE RTRIM(RECORDID)='%s';", I_RecordNo );

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

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
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
		memset( RecordId, 0, sizeof( RecordId ) );
	    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return 1;
	}
    else
    {
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}
