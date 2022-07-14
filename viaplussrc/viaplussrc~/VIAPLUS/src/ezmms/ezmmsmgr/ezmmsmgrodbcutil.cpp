/*
 * ezmmsmgrodbcutil.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: mohanraj
 */
#include <ezmms/ezmmsmgrodbcutil.h>

int EzMMSMgrODBCUtil :: initEzMMSMgrODBCUtil( const char *TaskName, EzDebugUtil *dptr )
{
	this->dptr = dptr;
	if( initODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Initializing the EzODBCUtil");
		return -1;
	}

	if( DBConnect() < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzMMSMgrODBCUtil :: getEzMerchantProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMMS_MERCHANTPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMMS_MERCHANTPROFILE - Count[%d]", count);

    return count;
}

int EzMMSMgrODBCUtil :: LoadEzMerchantProfile( struct EzMMSMerchantProfile *merchantprofile_ptr, int *SqlErr )
{
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char MCCList[ 33 ];
	char MerchantTypeId[ 17 ];
	char ParentMerchantId[ 16 ];
	char MerchantName[ 33 ];
	char Addr1[ 65 ];
	char Addr2[ 65 ];
	char Status;
	char DOB[ 11 ];
	char PMobileNo[ 17 ];
	char SMobileNo[ 17 ];
	char PMailAddr[ 33 ];
	char SMailAddr[ 33 ];
	char SettCurrCode[ 5 ];
	char CurrList[ 33 ];
	char CardIssuanceFlag;
	char tempdate[ 11 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzMerchantProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		strcpy( SqlStmt,  "SELECT \
			RTRIM(INST_ID),\
			RTRIM(MERCH_ID),\
			RTRIM( ISNULL( MCC_LIST, 'NA' ) ),\
			RTRIM( ISNULL( MERCH_TYPE_ID, 'NA' ) ),\
			RTRIM( ISNULL( PARENT_MERCH_ID, 'NA' ) ),\
			RTRIM( ISNULL( MERCH_NAME, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_MAIL_ADDR, 'NA' ) ),\
			RTRIM( ISNULL( SEC_MAIL_ADDR, 'NA' ) ),\
			ISNULL( STATUS, '0' ),\
			RTRIM( ISNULL( convert(varchar,DOB, 105 ), 'NA' ) ),\
			RTRIM( ISNULL( PRIM_MOBILE_NO, 'NA' ) ),\
			RTRIM( ISNULL( SEC_MOBILE_NO, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_EMAIL_ID, 'NA' ) ),\
			RTRIM( ISNULL( SEC_EMAIL_ID, 'NA' ) ),\
			RTRIM( ISNULL( SETT_CURR_CODE, 'NA' ) ),\
			RTRIM( ISNULL( CURR_LIST, 'NA' ) ),\
			ISNULL( CARD_ISSUED_FLAG, 'N' ) \
		FROM EZMMS_MERCHANTPROFILE;" );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("SqlStmt<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzMerchantProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MCCList, sizeof(MCCList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AtmId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MerchantTypeId, sizeof(MerchantTypeId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantTypeId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, ParentMerchantId, sizeof(ParentMerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ParentMerchantId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, MerchantName, sizeof(MerchantName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, Addr1, sizeof(Addr1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Addr1) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, Addr2, sizeof(Addr2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Addr2) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &Status, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Status) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, DOB, sizeof(DOB), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DOB) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, PMobileNo, sizeof(PMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PMobileNo) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, SMobileNo, sizeof(SMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SMobileNo) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, PMailAddr, sizeof(PMailAddr), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PMailAddr) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, SMailAddr, sizeof(SMailAddr), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SMailAddr) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_CHAR, SettCurrCode, sizeof(SettCurrCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SettCurrCode) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_CHAR, CurrList, sizeof(CurrList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CurrList) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_BINARY, &CardIssuanceFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CardIssuanceFlag) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( merchantprofile_ptr + i, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( ( merchantprofile_ptr + i )->InstId, InstId );
        strcpy( ( merchantprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( merchantprofile_ptr + i )->MCCList, MCCList );
        strcpy( ( merchantprofile_ptr + i )->MerchantTypeId, MerchantTypeId );
        strcpy( ( merchantprofile_ptr + i )->ParentMerchantId, ParentMerchantId );
      	strcpy( ( merchantprofile_ptr + i )->MerchantName, MerchantName );
      	strcpy( ( merchantprofile_ptr + i )->Addr1, Addr1 );
      	strcpy( ( merchantprofile_ptr + i )->Addr2, Addr2 );
      	( merchantprofile_ptr + i )->Status = Status;
      	if( !strcasecmp( DBType, SQLSERVER ) )
		{
			memset( tempdate, 0, sizeof( tempdate ) );
			getSwitchDateFmt( DOB, "DDMMYY", tempdate );
			strcpy( ( merchantprofile_ptr + i )->DOB, tempdate );
		}
      	strcpy( ( merchantprofile_ptr + i )->PMobileNo, PMobileNo );
      	strcpy( ( merchantprofile_ptr + i )->SMobileNo, SMobileNo );
      	strcpy( ( merchantprofile_ptr + i )->PMailAddr, PMailAddr );
      	strcpy( ( merchantprofile_ptr + i )->SMailAddr, SMailAddr );
      	strcpy( ( merchantprofile_ptr + i )->SettCurrCode, SettCurrCode );
      	strcpy( ( merchantprofile_ptr + i )->CurrList, CurrList );
      	( merchantprofile_ptr + i )->CardIssuanceFlag = CardIssuanceFlag;
       	i++;
		memset( InstId, 0, sizeof( InstId ) );
		memset( MerchantId, 0, sizeof( MerchantId ) );
		memset( MCCList, 0, sizeof( MCCList ) );
		memset( MerchantTypeId, 0, sizeof( MerchantTypeId ) );
		memset( ParentMerchantId, 0, sizeof( ParentMerchantId ) );
		memset( MerchantName, 0, sizeof( MerchantName ) );
		memset( Addr1, 0, sizeof( Addr1 ) );
		memset( Addr2, 0, sizeof( Addr2 ) );
		memset( DOB, 0, sizeof( DOB ) );
		memset( PMobileNo, 0, sizeof( PMobileNo ) );
		memset( SMobileNo, 0, sizeof( SMobileNo ) );
		memset( PMailAddr, 0, sizeof( PMailAddr ) );
		memset( SMailAddr, 0, sizeof( SMailAddr ) );
		memset( SettCurrCode, 0, sizeof( SettCurrCode ) );
		memset( CurrList, 0, sizeof( CurrList ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil :: getEzStoreProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMMS_STOREPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMMS_STOREPROFILE - Count[%d]", count);

    return count;
}

int EzMMSMgrODBCUtil :: LoadEzStoreProfile( struct EzMMSStoreProfile *storeprofile_ptr, int *SqlErr )
{
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char StoreId[ 33 ];
	char Status;
	char StoreName[ 33 ];
	char StoreLocation[ 65 ];
	char CityName[ 33 ];
	char CityCode[ 17 ];
	char StateName[ 33 ];
	char CountryName[ 33 ];
	char LandLine1[ 17 ];
	char LandLine2[ 17 ];
	char PMobileNo[ 17 ];
	char SMobileNo[ 17 ];
	int WorkingHrs;
	char OpeningTime[ 7 ];
	char ClosingTime[ 7 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzStoreProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		strcpy( SqlStmt,  "SELECT \
			RTRIM(INST_ID),\
			RTRIM(MERCH_ID),\
			RTRIM(STORE_ID),\
			ISNULL( STORE_STATUS, '0' ),\
			RTRIM( ISNULL( STORE_NAME, 'NA' ) ),\
			RTRIM( ISNULL( STORE_LOCATION, 'NA' ) ),\
			RTRIM( ISNULL( CITY_NAME, 'NA' ) ),\
			RTRIM( ISNULL( CITY_CODE, 'NA' ) ),\
			RTRIM( ISNULL( STATE_NAME, 'NA' ) ),\
			RTRIM( ISNULL( COUNTRY_NAME, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_LAND_LINE_NO, 'NA' ) ),\
			RTRIM( ISNULL( SEC_LAND_LINE_NO, 'NA' ) ),\
			RTRIM( ISNULL( PRIM_MOBILE_NUM, 'NA' ) ),\
			RTRIM( ISNULL( SEC_MOBILE_NUM, 'NA' ) ),\
			ISNULL( WORKING_HRS, '24' ),\
			RTRIM( ISNULL( OPENING_TIME, '000000' ) ),\
			RTRIM( ISNULL( CLOSING_TIME, '235959' ) )\
		FROM EZMMS_STOREPROFILE;" );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("SqlStmt<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzStoreProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &Status, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Status) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, StoreName, sizeof(StoreName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreName) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, StoreLocation, sizeof(StoreLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreLocation) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, CityName, sizeof(CityName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CityName) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, CityCode, sizeof(CityCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CityCode) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, StateName, sizeof(StateName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StateName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, CountryName, sizeof(CountryName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DOB) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, LandLine1, sizeof(LandLine1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LandLine1) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, LandLine2, sizeof(LandLine2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LandLine2) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, PMobileNo, sizeof(PMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PMobileNo) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, SMobileNo, sizeof(SMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SMobileNo) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &WorkingHrs, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(WorkingHrs) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_CHAR, OpeningTime, sizeof(OpeningTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OpeningTime) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_CHAR, ClosingTime, sizeof(ClosingTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_STOREPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( storeprofile_ptr + i, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( ( storeprofile_ptr + i )->InstId, InstId );
        strcpy( ( storeprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( storeprofile_ptr + i )->StoreId, StoreId );
        ( storeprofile_ptr + i )->Status = Status;
        strcpy( ( storeprofile_ptr + i )->StoreName, StoreName );
        strcpy( ( storeprofile_ptr + i )->StoreLocation, StoreLocation );
        strcpy( ( storeprofile_ptr + i )->CityName, CityName );
        strcpy( ( storeprofile_ptr + i )->CityCode, CityCode );
        strcpy( ( storeprofile_ptr + i )->StateName, StateName );
        strcpy( ( storeprofile_ptr + i )->CountryName, CountryName );
        strcpy( ( storeprofile_ptr + i )->LandLine1, LandLine1 );
        strcpy( ( storeprofile_ptr + i )->LandLine2, LandLine2 );
        strcpy( ( storeprofile_ptr + i )->PMobileNo, PMobileNo );
        strcpy( ( storeprofile_ptr + i )->SMobileNo, SMobileNo );
        ( storeprofile_ptr + i )->WorkingHrs = WorkingHrs;
        strcpy( ( storeprofile_ptr + i )->OpeningTime, OpeningTime );
        strcpy( ( storeprofile_ptr + i )->ClosingTime, ClosingTime );
       	i++;
       	memset( InstId, 0, sizeof( InstId ) );
		memset( MerchantId, 0, sizeof( MerchantId ) );
		memset( StoreId, 0, sizeof( StoreId ) );
		memset( StoreName, 0, sizeof( StoreName ) );
		memset( StoreLocation, 0, sizeof( StoreLocation ) );
		memset( CityName, 0, sizeof( CityName ) );
		memset( CityCode, 0, sizeof( CityCode ) );
		memset( StateName, 0, sizeof( StateName ) );
		memset( CountryName, 0, sizeof( CountryName ) );
		memset( LandLine1, 0, sizeof( LandLine1 ) );
		memset( LandLine2, 0, sizeof( LandLine2 ) );
		memset( PMobileNo, 0, sizeof( PMobileNo ) );
		memset( SMobileNo, 0, sizeof( SMobileNo ) );
		memset( OpeningTime, 0, sizeof( OpeningTime ) );
		memset( ClosingTime, 0, sizeof( ClosingTime ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil :: getEzTerminalProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMMS_TERMINALPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMMS_TERMINALPROFILE - Count[%d]", count);

    return count;
}

int EzMMSMgrODBCUtil :: LoadEzTerminalProfile( struct EzMMSTerminalProfile *terminalprofile_ptr, int *SqlErr )
{
	char MachineId[ 33 ];
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char StoreId[ 33 ];
	char TerminalId[ 9 ];
	char TerminalType[ 17 ];
	char TerminalName[ 33 ];
	char TermLocation[ 65 ];
	char TerminalStatus;
	int WorkingHrs;
	char OpeningTime[ 7 ];
	char ClosingTime[ 7 ];
	char CountryCode[ 5 ];
	char CurrCode[ 5 ];
	char TermMasterKey[ 65 ];
	char TermPINKey[ 65 ];
	char ChipEnabled;
	char TermMACKey[ 65 ];
	char BatchId[ 13 ];
	int KeyIntvl;
	int TxnKeyIntvl;
	int EchoIntvl;
	int mcc;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTerminalProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		strcpy( SqlStmt,  "SELECT \
			RTRIM(MACHINE_ID),\
			RTRIM(INST_ID),\
			RTRIM(MERCH_ID),\
			RTRIM(STORE_ID),\
			RTRIM(TERMINAL_ID),\
			RTRIM(TERMINAL_TYPE),\
			RTRIM( ISNULL( TERMINAL_NAME, 'NA' ) ),\
			RTRIM( ISNULL( TERMINAL_LOCATION, 'NA' ) ),\
			ISNULL( TERMINAL_STATUS, '0' ),\
			ISNULL( WORKING_HRS, '24' ),\
			RTRIM( ISNULL( OPENING_TIME, '000000' ) ),\
			RTRIM( ISNULL( CLOSING_TIME, '235959' ) ),\
			RTRIM(COUNTRY_CODE),\
			RTRIM(CURR_CODE),\
			ISNULL( CHIP_ENABLED, 'N' ),\
			RTRIM( TERM_MASTER_KEY ),\
			RTRIM( ISNULL( TERM_PIN_KEY, '1111111111111111' ) ),\
			RTRIM( ISNULL( TERM_MAC_KEY, '1111111111111111' ) ),\
			KEY_INTVL,\
			ECHO_INTVL,\
			TXN_KEY_INTVL,\
			MCC_CODE,\
			RTRIM( ISNULL( BATCHID, 'NOTDEFINED' ) )\
		FROM EZMMS_TERMINALPROFILE;" );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("SqlStmt<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTerminalProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }


    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MachineId, sizeof(MachineId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MachineId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TerminalId, sizeof(TerminalId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, TerminalType, sizeof(TerminalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalType) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, TerminalName, sizeof(TerminalName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalName) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_CHAR, TermLocation, sizeof(TermLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CityCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &TerminalStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalStatus) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &WorkingHrs, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(WorkingHrs) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, OpeningTime, sizeof(OpeningTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OpeningTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, ClosingTime, sizeof(ClosingTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, CountryCode, sizeof(CountryCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CountryCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, CurrCode, sizeof(CurrCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CurrCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_BINARY, &ChipEnabled, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_CHAR, TermMasterKey, sizeof(TermMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermMasterKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_CHAR, TermPINKey, sizeof(TermPINKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermPINKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_CHAR, TermMACKey, sizeof(TermMACKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermMACKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_SLONG, &KeyIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(KeyIntvl) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 20, SQL_C_SLONG, &EchoIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(EchoIntvl) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 21, SQL_C_SLONG, &TxnKeyIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnKeyIntvl) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 22, SQL_C_SLONG, &mcc, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(mcc) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 23, SQL_C_CHAR, BatchId, sizeof(BatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BatchId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( terminalprofile_ptr + i, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( ( terminalprofile_ptr + i )->MachineId, MachineId );
        strcpy( ( terminalprofile_ptr + i )->InstId, InstId );
        strcpy( ( terminalprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( terminalprofile_ptr + i )->StoreId, StoreId );
        strcpy( ( terminalprofile_ptr + i )->TerminalId, TerminalId );
        strcpy( ( terminalprofile_ptr + i )->TerminalName, TerminalName );
        strcpy( ( terminalprofile_ptr + i )->TerminalType, TerminalType );
        strcpy( ( terminalprofile_ptr + i )->TerminalLocation, TermLocation );
       	( terminalprofile_ptr + i )->TerminalStatus = TerminalStatus;
       	( terminalprofile_ptr + i )->WorkingHrs = WorkingHrs;
       	strcpy( ( terminalprofile_ptr + i )->OpeningTime, OpeningTime );
        strcpy( ( terminalprofile_ptr + i )->ClosingTime, ClosingTime );
        ( terminalprofile_ptr + i )->ChipEnabled = ChipEnabled;
        strcpy( ( terminalprofile_ptr + i )->CountryCode, CountryCode );
        strcpy( ( terminalprofile_ptr + i )->CurrCode, CurrCode );
        strcpy( ( terminalprofile_ptr + i )->TermMasterKey, TermMasterKey );
        strcpy( ( terminalprofile_ptr + i )->TermPINKey, TermPINKey );
        strcpy( ( terminalprofile_ptr + i )->TermMACKey, TermMACKey );
		( terminalprofile_ptr + i )->KeyIntvl = KeyIntvl;
	 	( terminalprofile_ptr + i )->EchoIntvl = EchoIntvl;
	 	( terminalprofile_ptr + i )->TxnKeyIntvl = TxnKeyIntvl;
		( terminalprofile_ptr + i )->Mcc =  mcc ;
		strcpy( ( terminalprofile_ptr + i )->BatchId, BatchId );
        i++;
		memset( MachineId, 0, sizeof( MachineId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( MerchantId, 0, sizeof( MerchantId ) );
		memset( StoreId, 0, sizeof( StoreId ) );
		memset( TerminalId, 0, sizeof( TerminalId ) );
		memset( TerminalType, 0, sizeof( TerminalType ) );
		memset( TerminalName, 0, sizeof( TerminalName ) );
		memset( TermLocation, 0, sizeof( TermLocation ) );
		memset( OpeningTime, 0, sizeof( OpeningTime ) );
		memset( ClosingTime, 0, sizeof( ClosingTime ) );
		memset( CountryCode, 0, sizeof( CountryCode ) );
		memset( CurrCode, 0, sizeof( CurrCode ) );
		memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
		memset( TermPINKey, 0, sizeof( TermPINKey ) );
		memset( TermMACKey, 0, sizeof( TermMACKey ) );
		memset( BatchId, 0, sizeof( BatchId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil :: getMMSFITProfileCount(int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMMS_FITPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMMS_FITPROFILE - Count[%d]", count);

    return count;
}

int EzMMSMgrODBCUtil :: LoadMMSFITProfile( struct EzMMSFITProfile *ezmmsfitprofile_ptr, int *SqlErr )
{
    char RecordId[ 17 ];
    char InstId[ 13 ];
    char MerchantType[ 17 ];
    char MerchantId[ 16 ];
    char TerminalId[ 9 ];
    char FITRecord[ 13 ];
    char IndirectState;
    char LocalPINVerFlag;
    char LocalFingerPrintFlag;
    int MaxPINLen;
    int MinPINLen;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;
    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadMMSFITProfile [ %d ]", odbcret );
		return -1;
    }

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	strcpy( SqlStmt,  "SELECT \
			RTRIM(RECORDID),\
			RTRIM(INSTID),\
			RTRIM(MERCHANTTYPE),\
			RTRIM(MERCHANTID),\
			RTRIM(TERMINALID),\
			RTRIM(FITRECORD),\
			INDIRECTSTATE,\
			LOCALPINVERFLAG,\
			LOCALFINGERVERFLAG,\
			MAXPINLEN,\
			MINPINLEN\
		FROM EZMMS_FITPROFILE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace("SqlStmt<%s>", SqlStmt);
    	dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in LoadMMSFITProfile [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RecordId) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MerchantType, sizeof(MerchantType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantType) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TerminalId, sizeof(TerminalId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalId) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, FITRecord, sizeof(FITRecord), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(FITRecord) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &IndirectState, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(IndirectState) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &LocalPINVerFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LocalPINVerFlag) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &LocalFingerPrintFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LocalFingerPrintFlag) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &MaxPINLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxPINLen) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &MinPINLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MinPINLen) in EZMMS_FITPROFILE [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ezmmsfitprofile_ptr + i, 0, sizeof( struct EzMMSFITProfile ) );
        strcpy( ( ezmmsfitprofile_ptr + i )->RecordId, RecordId );
        strcpy( ( ezmmsfitprofile_ptr + i )->InstId, InstId );
        strcpy( ( ezmmsfitprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( ezmmsfitprofile_ptr + i )->MerchantType, MerchantType );
        strcpy( ( ezmmsfitprofile_ptr + i )->TerminalId, TerminalId );
        strcpy( ( ezmmsfitprofile_ptr + i )->FITRecord, FITRecord );
        ( ezmmsfitprofile_ptr + i )->IndirectState = IndirectState;
        ( ezmmsfitprofile_ptr + i )->LocalPINVerFlag = LocalPINVerFlag;
        ( ezmmsfitprofile_ptr + i )->LocalFingerPrintFlag = LocalFingerPrintFlag;
        ( ezmmsfitprofile_ptr + i )->MaxPINLen = MaxPINLen;
        ( ezmmsfitprofile_ptr + i )->MinPINLen = MinPINLen;
        i++;
        memset( RecordId, 0, sizeof( RecordId ) );
        memset( InstId, 0, sizeof( InstId ) );
        memset( MerchantType, 0, sizeof( MerchantType ) );
        memset( MerchantId, 0, sizeof( MerchantId ) );
        memset( TerminalId, 0, sizeof( TerminalId ) );
        memset( FITRecord, 0, sizeof( FITRecord ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}
