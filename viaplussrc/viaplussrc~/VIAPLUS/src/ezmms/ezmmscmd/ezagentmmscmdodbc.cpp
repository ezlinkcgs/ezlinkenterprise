#include <ezagentmms/ezagentmmsodbcutil.h>

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

int EzMMSMgrODBCUtil :: readEzMMSMerchantProfile( const char *I_InstId, const char *I_MerchantId, struct EzMMSMerchantProfile *merchantprofile_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
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




    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    		       RTRIM( NVL( MCC_LIST, 'NA' ) ),
        RTRIM( NVL( MERCH_TYPE_ID, 'NA' ) ),
        RTRIM( NVL( PARENT_MERCH_ID, 'NA' ) ),
        RTRIM( NVL( MERCH_NAME, 'NA' ) ),
        RTRIM( NVL( PRIM_MAIL_ADDR, 'NA' ) ),
        RTRIM( NVL( SEC_MAIL_ADDR, 'NA' ) ),
        NVL( STATUS, '0' ),
        RTRIM( NVL( TO_CHAR(DOB, 'DD-MM-YY' ), 'NA' ) ),
        RTRIM( NVL( PRIM_MOBILE_NO, 'NA' ) ),
        RTRIM( NVL( SEC_MOBILE_NO, 'NA' ) ),
        RTRIM( NVL( PRIM_EMAIL_ID, 'NA' ) ),
        RTRIM( NVL( SEC_EMAIL_ID, 'NA' ) ),
        RTRIM( NVL( SETT_CURR_CODE, 'NA' ) ),
        RTRIM( NVL( CURR_LIST, 'NA' ) ),
        NVL( CARD_ISSUED_FLAG, 'N' )



    		 FROM EZMMSMERCHANTPROFILE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID)=:MerchantId;

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in  readEzMMSMerchantProfile [ %d ]", odbcret );
		getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
		//getNativeErrorCode();
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MCC_LIST, sizeof(MCC_LIST), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MCC_LIST) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, AutMERCH_TYPE_IDhNum, sizeof(AuthMERCH_TYPE_IDNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AMERCH_TYPE_IDuthNum) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, PARENT_MERCH_ID, sizeof(PARENT_MERCH_ID), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PARENT_MERCH_ID) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MERCH_NAME, sizeof(MERCH_NAME), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MERCH_NAME) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	 odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, PRIM_MAIL_ADDR, sizeof(PRIM_MAIL_ADDR), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PRIM_MAIL_ADDR) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SEC_MAIL_ADDR, sizeof(SEC_MAIL_ADDR), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SEC_MAIL_ADDR) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, STATUS, sizeof(STATUS), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(STATUS) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, DOB, sizeof(DOB), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(DOB) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, PRIM_MOBILE_NO, sizeof(PRIM_MOBILE_NO), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PRIM_MOBILE_NO) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SEC_MOBILE_NO, sizeof(SEC_MOBILE_NO), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SEC_MOBILE_NO) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, PRIM_EMAIL_ID, sizeof(PRIM_EMAIL_ID), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PRIM_EMAIL_ID) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SEC_EMAIL_ID, sizeof(SEC_EMAIL_ID), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SEC_EMAIL_ID) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SETT_CURR_CODE, sizeof(SETT_CURR_CODE), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SETT_CURR_CODE) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CURR_LIST, sizeof(CURR_LIST), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CURR_LIST) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CARD_ISSUED_FLAG, sizeof(CARD_ISSUED_FLAG), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CARD_ISSUED_FLAG) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }


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



    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
       strcpy( merchantprofile_ptr->InstId, InstId );
    strcpy( merchantprofile_ptr->MerchantId, MerchantId );
    strcpy( merchantprofile_ptr->MCCList, MCCList );
    strcpy( merchantprofile_ptr->MerchantTypeId, MerchantTypeId );
    strcpy( merchantprofile_ptr->ParentMerchantId, ParentMerchantId );
        strcpy( merchantprofile_ptr->MerchantName, MerchantName );
        strcpy( merchantprofile_ptr->Addr1, Addr1 );
        strcpy( merchantprofile_ptr->Addr2, Addr2 );
        merchantprofile_ptr->Status = Status;
        strcpy( merchantprofile_ptr->DOB, DOB );
        strcpy( merchantprofile_ptr->PMobileNo, PMobileNo );
        strcpy( merchantprofile_ptr->SMobileNo, SMobileNo );
        strcpy( merchantprofile_ptr->PMailAddr, PMailAddr );
        strcpy( merchantprofile_ptr->SMailAddr, SMailAddr );
        strcpy( merchantprofile_ptr->SettCurrCode, SettCurrCode );
        strcpy( merchantprofile_ptr->CurrList, CurrList );
        merchantprofile_ptr->CardIssuanceFlag = CardIssuanceFlag;


    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1403;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil :: readEzMMSStoreProfile( const char *I_InstId, const char *I_MerchantId, const char *I_StoreId, struct EzMMSStoreProfile *storeprofile_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
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




    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
         NVL( STORE_STATUS, '0' ),
        RTRIM( NVL( STORE_NAME, 'NA' ) ),
        RTRIM( NVL( STORE_LOCATION, 'NA' ) ),
        RTRIM( NVL( CITY_NAME, 'NA' ) ),
        RTRIM( NVL( CITY_CODE, 'NA' ) ),
        RTRIM( NVL( STATE_NAME, 'NA' ) ),
        RTRIM( NVL( COUNTRY_NAME, 'NA' ) ),
        RTRIM( NVL( PRIM_LAND_LINE_NO, 'NA' ) ),
        RTRIM( NVL( SEC_LAND_LINE_NO, 'NA' ) ),
        RTRIM( NVL( PRIM_MOBILE_NUM, 'NA' ) ),
        RTRIM( NVL( SEC_MOBILE_NUM, 'NA' ) ),
        NVL( WORKING_HRS, '24' ),
        RTRIM( NVL( OPENING_TIME, '000000' ) ),
        RTRIM( NVL( CLOSING_TIME, '235959' ) )

    		FROM EZMMS_STOREPROFILE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID)=:MerchantId AND RTRIM(STORE_ID)=:StoreId;

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in  readEzMMSStoreProfile [ %d ]", odbcret );
		getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
		//getNativeErrorCode();
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, Status, sizeof(Status), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Status) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	 odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StoreName, sizeof(StoreName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StoreLocation, sizeof(StoreLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreLocation) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CityName, sizeof(CityName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CityName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CityCode, sizeof(CityCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CityCode) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StateName, sizeof(StateName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StateName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CountryName, sizeof(CountryName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CountryName) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, LandLine1, sizeof(LandLine1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LandLine1) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, LandLine2, sizeof(LandLine2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LandLine2) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, PMobileNo, sizeof(PMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(PMobileNo) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SMobileNo, sizeof(SMobileNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SMobileNo) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, WorkingHrs, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(WorkingHrs) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, OpeningTime, sizeof(OpeningTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OpeningTime) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, ClosingTime, sizeof(ClosingTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_MERCHANTPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	


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




    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( storeprofile_ptr->InstId, InstId );
    strcpy( storeprofile_ptr->MerchantId, MerchantId );
    strcpy( storeprofile_ptr->StoreId, StoreId );
    storeprofile_ptr->Status = Status;
    strcpy( storeprofile_ptr->StoreName, StoreName );
    strcpy( storeprofile_ptr->StoreLocation, StoreLocation );
    strcpy( storeprofile_ptr->CityName, CityName );
    strcpy( storeprofile_ptr->CityCode, CityCode );
    strcpy( storeprofile_ptr->StateName, StateName );
    strcpy( storeprofile_ptr->CountryName, CountryName );
    strcpy( storeprofile_ptr->LandLine1, LandLine1 );
    strcpy( storeprofile_ptr->LandLine2, LandLine2 );
    strcpy( storeprofile_ptr->PMobileNo, PMobileNo );
    strcpy( storeprofile_ptr->SMobileNo, SMobileNo );
    storeprofile_ptr->WorkingHrs = WorkingHrs;
    strcpy( storeprofile_ptr->OpeningTime, OpeningTime );
    strcpy( storeprofile_ptr->ClosingTime, ClosingTime );



    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1403;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil ::   readEzMMSTerminalProfile( const char *I_MachineId, struct EzMMSTerminalProfile *terminalprofile_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
   char MachineId[ 33 ];
                char InstId[ 13 ];
                char MerchantId[ 16 ];
                char StoreId[ 33 ];
                char TerminalId[ 9 ];
                char TerminalName[ 33 ];
                char TermLocation[ 65 ];
                char TerminalStatus;
                int WorkingHrs;
                char OpeningTime[ 7 ];
                char ClosingTime[ 7 ];
                char CountryCode[ 5 ];
                char ChipEnabled;
                char TermMasterKey[ 65 ];
                char TermPINKey[ 65 ];
                char TermMACKey[ 65 ];
                char BatchId[ 13 ];
                char TermBatchId[ 13 ];




    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
          RTRIM(INST_ID),
        RTRIM(MERCH_ID),
        RTRIM(STORE_ID),
        RTRIM(TERMINAL_ID),
        RTRIM( NVL( TERMINAL_NAME, 'NA' ) ),
        RTRIM( NVL( TERMINAL_LOCATION, 'NA' ) ),
        NVL( TERMINAL_STATUS, '0' ),
        NVL( WORKING_HRS, '24' ),
        RTRIM( NVL( OPENING_TIME, '000000' ) ),
        RTRIM( NVL( CLOSING_TIME, '235959' ) ),
        RTRIM(COUNTRY_CODE),
        NVL( CHIP_ENABLED, 'N' ),
        RTRIM( TERM_MASTER_KEY ),
        NVL( RTRIM( TERM_PIN_KEY, '1111111111111111' ) ),
        NVL( RTRIM( TERM_MAC_KEY, '1111111111111111' ) )

			FROM EZMMS_TERMINALPROFILE WHERE RTRIM(MACHINE_ID) = :MachineId;
    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in  readEzMMSTerminalProfile [ %d ]", odbcret );
		getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
		//getNativeErrorCode();
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MachineId, sizeof(MachineId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MachineId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	 odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TerminalId, sizeof(TerminalId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TerminalName, sizeof(TerminalName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalName) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TermLocation, sizeof(TermLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermLocation) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TerminalStatus, sizeof(TerminalStatus), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalStatus) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, WorkingHrs, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(WorkingHrs) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, OpeningTime, sizeof(OpeningTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OpeningTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, ClosingTime, sizeof(ClosingTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ClosingTime) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CountryCode, sizeof(CountryCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CountryCode) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, TermMasterKey, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermMasterKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TermPINKey, sizeof(TermPINKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermPINKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, ChipEnabled, sizeof(ChipEnabled), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(ChipEnabled) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TermMACKey, sizeof(TermMACKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermMACKey) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, BatchId, sizeof(BatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BatchId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TermBatchId, sizeof(TermBatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermBatchId) in EZMMS_TERMINALPROFILE [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	
	


         memset( MachineId, 0, sizeof( MachineId ) );
        memset( InstId, 0, sizeof( InstId ) );
        memset( MerchantId, 0, sizeof( MerchantId ) );
        memset( StoreId, 0, sizeof( StoreId ) );
        memset( TerminalId, 0, sizeof( TerminalId ) );
        memset( TerminalName, 0, sizeof( TerminalName ) );
        memset( TermLocation, 0, sizeof( TermLocation ) );
        memset( OpeningTime, 0, sizeof( OpeningTime ) );
        memset( ClosingTime, 0, sizeof( ClosingTime ) );
        memset( CountryCode, 0, sizeof( CountryCode ) );
        memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
        memset( TermPINKey, 0, sizeof( TermPINKey ) );
        memset( TermMACKey, 0, sizeof( TermMACKey ) );
        memset( BatchId, 0, sizeof( BatchId ) );
        memset( TermBatchId, 0, sizeof( TermBatchId ) );




    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
      strcpy( terminalprofile_ptr->MachineId, MachineId );
        strcpy( terminalprofile_ptr->InstId, InstId );
    strcpy( terminalprofile_ptr->MerchantId, MerchantId );
    strcpy( terminalprofile_ptr->StoreId, StoreId );
    strcpy( terminalprofile_ptr->TerminalId, TerminalId );
    strcpy( terminalprofile_ptr->TerminalName, TerminalName );
    strcpy( terminalprofile_ptr->TerminalLocation, TermLocation );
    terminalprofile_ptr->TerminalStatus = TerminalStatus;
    terminalprofile_ptr->WorkingHrs = WorkingHrs;
    strcpy( terminalprofile_ptr->OpeningTime, OpeningTime );
    strcpy( terminalprofile_ptr->ClosingTime, ClosingTime );
        strcpy( terminalprofile_ptr->CountryCode, CountryCode );
        terminalprofile_ptr->ChipEnabled = ChipEnabled;
        strcpy( terminalprofile_ptr->TermMasterKey, TermMasterKey );
        strcpy( terminalprofile_ptr->TermPINKey, TermPINKey );
        strcpy( terminalprofile_ptr->TermMACKey, TermMACKey );



    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1403;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil :: readEzMMSMerchantRelation( const char *I_InstId, const char *I_MerchantId, const char *I_AccountNo, struct EzMMSMerchantRelation *merchantrelation_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
              char InstId[ 13 ];
                char MerchantId[ 16 ];
                char AccountNo[ 33 ];
                char CurrCode[ 5 ];
                char AccountStatus;
                short AccountPriority;




    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
     RTRIM(CURR_CODE),
        STATUS,
        PRIORITY


    		 FROM EZMMS_RELATION WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID) = :MerchantId AND RTRIM(ACCT_NO) = :AccountNo;

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzMMSMerchantRelation [ %d ]", odbcret );
		getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
		//getNativeErrorCode();
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, AccountNo, sizeof(AccountNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AccountNo) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CurrCode, sizeof(CurrCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CurrCode) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	 odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, AccountStatus, sizeof(AccountStatus), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AccountStatus) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	odbcret = SQLBindCol( hstmt, 4, SQL_C_SHORT, AccountPriority, sizeof(AccountPriority), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AccountPriority) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	


   memset( InstId, 0, sizeof( InstId ) );
        memset( MerchantId, 0, sizeof( MerchantId ) );
        memset( AccountNo, 0, sizeof( AccountNo ) );
        memset( CurrCode, 0, sizeof( CurrCode ) );



    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
   strcpy( merchantrelation_ptr->InstId, InstId );
    strcpy( merchantrelation_ptr->MerchantId, MerchantId );
    strcpy( merchantrelation_ptr->AccountNo, AccountNo );
    strcpy( merchantrelation_ptr->CurrCode, CurrCode );
    merchantrelation_ptr->AccountStatus = AccountStatus;
    merchantrelation_ptr->AccountPriority = AccountPriority;



    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1403;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzMMSMgrODBCUtil :: readEzMMSMerchantType( const char *I_InstId, const char *I_MerchantTypeId, struct EzMMSMerchantType *merchanttype_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
             char InstId[ 13 ];
                char MerchantTypeId[ 17 ];
                char TxnAllowed[ 65 ];
                char LoyaltyReq;
                int MaxPINRetryCount;




    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
         RTRIM( NVL( TXN_ALLOWED, 'NA' ) ),
        NVL( LOYALTY_PGM_REQ, 'N' ),
        NVL( MAX_PIN_RETRY_COUNT, '3' )


    		 FROM EZMMS_MERCHANTTYPE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCHANT_TYPE_ID)=:MerchantTypeId;

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readEzMMSMerchantType [ %d ]", odbcret );
		getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
		//getNativeErrorCode();
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantTypeId, sizeof(MerchantTypeId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantTypeId) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TxnAllowed, sizeof(TxnAllowed), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnAllowed) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, LoyaltyReq, sizeof(LoyaltyReq), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LoyaltyReq) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	 odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, MaxPINRetryCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MaxPINRetryCount) in EZMMS_RELATION [ %d ]", odbcret );
	getNativeErrorCode( hstmt, SQL_HANDLE_STMT );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }
	
	


  memset( InstId, 0, sizeof( InstId ) );
        memset( MerchantTypeId, 0, sizeof( MerchantTypeId ) );
        memset( TxnAllowed, 0, sizeof( TxnAllowed ) );



    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
      strcpy( merchanttype_ptr->InstId, InstId );
    strcpy( merchanttype_ptr->MerchantTypeId, MerchantTypeId );
    strcpy( merchanttype_ptr->TxnAllowed, TxnAllowed );
    merchanttype_ptr->LoyaltyReq = LoyaltyReq;
        merchanttype_ptr->MaxPINRetryCount = MaxPINRetryCount;




    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1403;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

