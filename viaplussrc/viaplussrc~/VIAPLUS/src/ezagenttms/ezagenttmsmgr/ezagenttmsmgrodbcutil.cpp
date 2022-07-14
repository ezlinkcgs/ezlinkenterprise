/*
 * eztmsmgrodbcutil.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: mohanraj
 */

#include <ezagenttms/ezagenttmsmgrodbcutil.h>


int EzTMSMgrODBCUtil :: initEzTMSMgrODBCUtil( const char *TaskName, EzDebugUtil *dptr )
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

int  EzTMSMgrODBCUtil :: getEzTMSTxnRelCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSTXNREL" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSTXNREL - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSTxnRel( struct EzTMSTxnRel *eztmstxnrel_ptr, int *SqlErr )
{
	char RecordId[ 17 ];
	char TerminalType[ 17 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char RelatedTxnCode[ 7 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSTxnRel [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID),\
    	RTRIM(TERMINALTYPE),\
    	RTRIM(MSGTYPE),\
    	RTRIM(TXNCODE),\
    	RTRIM(RELATEDTXNCODE) \
    FROM EZTMSTXNREL;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSTxnRel [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTMSTXNREL [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TerminalType, sizeof(TerminalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalType) in EZTMSTXNREL [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTMSTXNREL [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTMSTXNREL [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, RelatedTxnCode, sizeof(RelatedTxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RelatedTxnCode) in EZTMSTXNREL [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmstxnrel_ptr + i )->RecordId, RecordId );
        strcpy( ( eztmstxnrel_ptr + i )->TerminalType, TerminalType );
        strcpy( ( eztmstxnrel_ptr + i )->MsgType, MsgType );
        strcpy( ( eztmstxnrel_ptr + i )->TxnCode, TxnCode );
        strcpy( ( eztmstxnrel_ptr + i )->RelatedTxnCode, RelatedTxnCode );
        i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( TerminalType, 0, sizeof( TerminalType ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RelatedTxnCode, 0, sizeof( RelatedTxnCode ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getTMSFITProfileCount(int *SqlErr )
{
	*SqlErr = 0;
	return 0;
}

int EzTMSMgrODBCUtil :: LoadTMSFITProfile( struct EzTMSFITProfile *eztmsfitprofile_ptr, int *SqlErr )
{

	return 0;
}

int EzTMSMgrODBCUtil :: getTMSTerminalProfileCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZMMSTERMINALPROFILE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZMMSTERMINALPROFILE - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadTMSTerminalProfile( struct EzTMSTerminalProfile *eztmsterminalprofile_ptr, int *SqlErr )
{
	char MachineId[ 33 ];
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char StoreId[ 33 ];
	char TerminalId[ 9 ];
	char TerminalType[ 17 ];
	char TerminalLocation[ 65 ];
	int BusinessStartTime;
	int BusinessEndTime;
	char TerminalStatus;
	char TermMasterKey[ 65 ];
	char TermPINKey[ 65 ];
	char TermMACKey[ 65 ];
	int TerminalCurrencyCode;
	int CountryCode;
	int PinCapCode;
	char BatchId[ 13 ];
	char ConfigId[ 13 ];
	int KeyIntvl;
	int EchoIntvl;
	int TxnKeyIntvl;
	int MccCode;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadTMSTerminalProfile [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(MACHINEID),\
    	RTRIM(INSTID),\
    	RTRIM(MERCHANTID),\
    	RTRIM(STOREID),\
    	RTRIM(TERMINALID),\
    	RTRIM(TERMINALTYPE),\
    	RTRIM(TERMLOC),\
    	STARTTIME,\
    	ENDTIME,\
    	STATUS,\
    	RTRIM(MASTERKEY),\
    	RTRIM(PINKEY),\
    	RTRIM(MACKEY),\
    	CURRENCYCODE,\
    	COUNTRYCODE,\
    	PINCAPCODE,\
    	RTRIM(BATCHID),\
    	RTRIM(CONFIGID),\
		KEY_INTVL,\
		ECHO_INTVL,\
		TXN_KEY_INTVL,\
    	MCC_CODE \
		FROM EZMMSTERMINALPROFILE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadTMSTerminalProfile [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MachineId, sizeof(MachineId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MachineId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TerminalId, sizeof(TerminalId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, TerminalType, sizeof(TerminalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalType) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, TerminalLocation, sizeof(TerminalLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalLocation) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &BusinessStartTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(BusinessStartTime) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &BusinessEndTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(BusinessEndTime) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_BINARY, &TerminalStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RelatedTxnCode) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, TermMasterKey, sizeof(TermMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TermMasterKey) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, TermPINKey, sizeof(TermPINKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TermPINKey) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, TermMACKey, sizeof(TermMACKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TermMACKey) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_SLONG, &TerminalCurrencyCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalCurrencyCode) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &CountryCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(CountryCode) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &PinCapCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(PinCapCode) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_CHAR, BatchId, sizeof(BatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(BatchId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_CHAR, ConfigId, sizeof(ConfigId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ConfigId) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_SLONG, &KeyIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(KeyIntvl) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 20, SQL_C_SLONG, &EchoIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(EchoIntvl) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 21, SQL_C_SLONG, &TxnKeyIntvl, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TxnKeyIntvl) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 22, SQL_C_SLONG, &MccCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MccCode) in EZMMSTERMINALPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmsterminalprofile_ptr + i )->MachineId, MachineId );
        strcpy( ( eztmsterminalprofile_ptr + i )->InstId, InstId );
        strcpy( ( eztmsterminalprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( eztmsterminalprofile_ptr + i )->StoreId, StoreId );
        strcpy( ( eztmsterminalprofile_ptr + i )->TerminalId, TerminalId );
        strcpy( ( eztmsterminalprofile_ptr + i )->TerminalType, TerminalType );
        strcpy( ( eztmsterminalprofile_ptr + i )->TerminalLocation, TerminalLocation );
        ( eztmsterminalprofile_ptr + i )->BusinessStartTime = BusinessStartTime;
        ( eztmsterminalprofile_ptr + i )->BusinessEndTime = BusinessEndTime;
        ( eztmsterminalprofile_ptr + i )->TerminalStatus = TerminalStatus;
        strcpy( ( eztmsterminalprofile_ptr + i )->TermMasterKey, TermMasterKey );
        strcpy( ( eztmsterminalprofile_ptr + i )->TermPINKey, TermPINKey );
        strcpy( ( eztmsterminalprofile_ptr + i )->TermMACKey, TermMACKey );
        ( eztmsterminalprofile_ptr + i )->TerminalCurrencyCode = TerminalCurrencyCode;
        ( eztmsterminalprofile_ptr + i )->CountryCode = CountryCode;
        ( eztmsterminalprofile_ptr + i )->PinCapCode = PinCapCode;
        strcpy( ( eztmsterminalprofile_ptr + i )->BatchId, BatchId );
        strcpy( ( eztmsterminalprofile_ptr + i )->ConfigId, ConfigId );
		( eztmsterminalprofile_ptr + i )->KeyIntvl = KeyIntvl;
		( eztmsterminalprofile_ptr + i )->EchoIntvl = EchoIntvl;
		( eztmsterminalprofile_ptr + i )->TxnKeyIntvl = TxnKeyIntvl;
		( eztmsterminalprofile_ptr + i )->MCC = MccCode;
		i++;
		memset( MachineId, 0, sizeof( MachineId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( MerchantId, 0, sizeof( MerchantId ) );
		memset( StoreId, 0, sizeof( StoreId ) );
		memset( TerminalId, 0, sizeof( TerminalId ) );
		memset( TerminalType, 0, sizeof( TerminalType ) );
		memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
		memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
		memset( TermPINKey, 0, sizeof( TermPINKey ) );
		memset( TermMACKey, 0, sizeof( TermMACKey ) );
		memset( BatchId, 0, sizeof( BatchId ) );
		memset( ConfigId, 0, sizeof( ConfigId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getCurrencyCodeList( struct EzTMSTerminalProfile *eztmsterminalprofile_ptr )
{
	char InstId[ 13 ];
	char MerchantId[ 16 ];
	char MerchantType[ 17 ];
	char CurrencyCode[ 65 ];
	int MCC;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in getCurrencyCodeList [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(MERCHANTTYPE),\
		MCC \
	FROM EZMMSMERCHANTPROFILE WHERE RTRIM(INSTID)='%s' AND RTRIM(MERCHANTID)='%s';", eztmsterminalprofile_ptr->InstId, eztmsterminalprofile_ptr->MerchantId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in getCurrencyCodeList [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MerchantType, sizeof(MerchantType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MerchantType) in EZMMSMERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &MCC, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MCC) in EZMMSMERCHANTPROFILE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( MerchantType, 0, sizeof( MerchantType ) );
    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( eztmsterminalprofile_ptr->MerchantType, MerchantType );
    	eztmsterminalprofile_ptr->MCC = MCC;
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    }
    else
    {
    	dptr->trace( DEBUG_ERROR, "Error in SQLFetch for EZMMSMERCHANTPROFILE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }


    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in getCurrencyCodeList [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(CURRENCYCODE) \
	FROM EZMMSMERCHANTTYPE WHERE RTRIM(INSTID)='%s' AND RTRIM(MERCHANTTYPE)='%s';", eztmsterminalprofile_ptr->InstId, eztmsterminalprofile_ptr->MerchantType );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in getCurrencyCodeList [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, CurrencyCode, sizeof(CurrencyCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(CurrencyCode) in EZMMSMERCHANTTYPE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( CurrencyCode, 0, sizeof( CurrencyCode ) );
    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( eztmsterminalprofile_ptr->CurrencyList, CurrencyCode );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return 0;
    }
    else
    {
    	dptr->trace( DEBUG_ERROR, "Error in SQLFetch for EZMMSMERCHANTTYPE [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzTMSMgrODBCUtil :: getEzTMSChannelPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSCHANNELPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSCHANNELPROPERTY - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSChannelProperty( struct EzTMSChannelProperty *eztmschannelproperty_ptr, int *SqlErr )
{
	char ChannelName[ 33 ];
	char ChannelType[ 17 ];
	char TMSProtocol[ 17 ];
	char CommunicationType[ 11 ];
	char TerminalFlag;
	char ExternalFlag;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSChannelProperty [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(CHANNELNAME),\
    	RTRIM(CHANNELTYPE),\
    	RTRIM(TMSPROTOCOL),\
    	RTRIM(COMMTYPE),\
    	TERMINALFLAG,\
    	EXTERNALFLAG \
    FROM EZTMSCHANNELPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSChannelProperty [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZTMSCHANNELPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ChannelType, sizeof(ChannelType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ChannelType) in EZTMSCHANNELPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TMSProtocol, sizeof(TMSProtocol), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TMSProtocol) in EZTMSCHANNELPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, CommunicationType, sizeof(CommunicationType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(CommunicationType) in EZTMSCHANNELPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &TerminalFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalFlag) in EZTMSCHANNELPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &ExternalFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ExternalFlag) in EZTMSCHANNELPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmschannelproperty_ptr + i )->ChannelName, ChannelName );
        strcpy( ( eztmschannelproperty_ptr + i )->ChannelType, ChannelType );
        strcpy( ( eztmschannelproperty_ptr + i )->TMSProtocol, TMSProtocol );
        strcpy( ( eztmschannelproperty_ptr + i )->CommunicationType, CommunicationType );
        ( eztmschannelproperty_ptr + i )->TerminalFlag = TerminalFlag;
        ( eztmschannelproperty_ptr + i )->ExternalFlag = ExternalFlag;
        i++;
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( ChannelType, 0, sizeof( ChannelType ) );
		memset( TMSProtocol, 0, sizeof( TMSProtocol ) );
		memset( CommunicationType, 0, sizeof( CommunicationType ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getEzTMSInBoundPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSINBOUNDPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSINBOUNDPROPERTY - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSInBoundProperty( struct EzTMSInBoundProperty *eztmsinboundproperty_ptr, int *SqlErr )
{
	char RecordId[ 17 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char ChannelName[ 33 ];
	char MsgFlag;
	char MsgProcessFlag;
	char LogFlag;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSInBoundProperty [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID),\
    	RTRIM(MSGTYPE),\
    	RTRIM(TXNCODE),\
    	RTRIM(CHANNELNAME),\
    	MSGFLAG,\
    	MSGPROCESSFLAG,\
    	LOGFLAG \
    FROM EZTMSINBOUNDPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSInBoundProperty [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &MsgFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgFlag) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &MsgProcessFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ExternalFlag) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &LogFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(LogFlag) in EZTMSINBOUNDPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmsinboundproperty_ptr + i )->RecordId, RecordId );
        strcpy( ( eztmsinboundproperty_ptr + i )->MsgType, MsgType );
        strcpy( ( eztmsinboundproperty_ptr + i )->TxnCode, TxnCode );
        strcpy( ( eztmsinboundproperty_ptr + i )->ChannelName, ChannelName );
        ( eztmsinboundproperty_ptr + i )->MsgFlag = MsgFlag;
        ( eztmsinboundproperty_ptr + i )->MsgProcessFlag = MsgProcessFlag;
        ( eztmsinboundproperty_ptr + i )->LogFlag = LogFlag;
        i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getEzTMSRouteInfoCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSROUTEINFO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSROUTEINFO - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSRouteInfo( struct EzTMSRouteInfo *eztmsrouteinfo_ptr, int *SqlErr )
{
	char RecordId[ 129 ];
	char InstId[ 13 ];
	char TerminalType[ 17 ];
	char MsgType[ 65 ];
	char TxnCode[ 129 ];
	char RespCode[ 65 ];
	char RouteExp1[ 129 ];
	int RouteExpPriority1;
	char RouteExp2[ 129 ];
	int RouteExpPriority2;
	char ChannelName[ 65 ];
	char RouteSelectList[ 129 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSRouteInfo [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID),\
    	RTRIM(INSTID),\
    	RTRIM(TERMINALTYPE),\
    	RTRIM(MSGTYPE),\
    	RTRIM(TXNCODE),\
    	RTRIM(RESPCODE),\
    	RTRIM(ROUTEEXP1),\
    	ROUTEEXPPRIORITY1,\
    	RTRIM(ROUTEEXP2),\
    	ROUTEEXPPRIORITY2,\
    	RTRIM(CHANNELNAME),\
    	RTRIM(ROUTESELECTLIST) \
    FROM EZTMSROUTEINFO;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSRouteInfo [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(InstId) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TerminalType, sizeof(TerminalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TerminalType) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, RespCode, sizeof(RespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RespCode) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, RouteExp1, sizeof(RouteExp1), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RouteExp1) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }


    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &RouteExpPriority1, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RouteExpPriority1) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, RouteExp2, sizeof(RouteExp2), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RouteExp2) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }


    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &RouteExpPriority2, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RouteExpPriority2) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, RouteSelectList, sizeof(RouteSelectList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RouteSelectList) in EZTMSROUTEINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmsrouteinfo_ptr + i )->RecordId, RecordId );
        strcpy( ( eztmsrouteinfo_ptr + i )->InstId, InstId );
        strcpy( ( eztmsrouteinfo_ptr + i )->TerminalType, TerminalType );
        strcpy( ( eztmsrouteinfo_ptr + i )->MsgType, MsgType );
        strcpy( ( eztmsrouteinfo_ptr + i )->TxnCode, TxnCode );
        strcpy( ( eztmsrouteinfo_ptr + i )->RespCode, RespCode );
        strcpy( ( eztmsrouteinfo_ptr + i )->RouteExp1, RouteExp1 );
        ( eztmsrouteinfo_ptr + i )->RouteExpPriority1 = RouteExpPriority1;
        strcpy( ( eztmsrouteinfo_ptr + i )->RouteExp2, RouteExp2 );
        ( eztmsrouteinfo_ptr + i )->RouteExpPriority2 = RouteExpPriority2;
        strcpy( ( eztmsrouteinfo_ptr + i )->ChannelName, ChannelName );
        strcpy( ( eztmsrouteinfo_ptr + i )->RouteSelectList, RouteSelectList );
        i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( TerminalType, 0, sizeof( TerminalType ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( RouteExp1, 0, sizeof( RouteExp1 ) );
		memset( RouteExp2, 0, sizeof( RouteExp2 ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getEzTMSRouteSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSROUTESELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSROUTESELECT - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSRouteSelect( struct EzTMSRouteSelect *eztmsrouteselect_ptr, int *SqlErr )
{
	char RouteSelectId[ 17 ];
	char ChannelName[ 33 ];
	char MsgTranslateId[ 17 ];
	char LogFlag;
	char LogBatchReq;
	char LogTotReq;
	char LogTxnReq;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSRouteSelect [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(ROUTESELECTID),\
    	RTRIM(CHANNELNAME),\
    	RTRIM(MSGTRANSLATEID),\
    	LOGFLAG,\
    	LOGBATCHREQ,\
    	LOGTOTREQ,\
    	LOGTXNREQ \
    FROM EZTMSROUTESELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSRouteSelect [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RouteSelectId, sizeof(RouteSelectId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RouteSelectId) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ChannelName, sizeof(ChannelName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(ChannelName) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, MsgTranslateId, sizeof(MsgTranslateId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgTranslateId) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &LogFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(LogFlag) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &LogBatchReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(LogBatchReq) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &LogTotReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(LogTotReq) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &LogTxnReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(LogTxnReq) in EZTMSROUTESELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmsrouteselect_ptr + i )->RouteSelectId, RouteSelectId );
        strcpy( ( eztmsrouteselect_ptr + i )->ChannelName, ChannelName );
        strcpy( ( eztmsrouteselect_ptr + i )->MsgTranslateId, MsgTranslateId );
        ( eztmsrouteselect_ptr + i )->LogFlag = LogFlag;
        ( eztmsrouteselect_ptr + i )->LogBatchReq = LogBatchReq;
        ( eztmsrouteselect_ptr + i )->LogTotReq = LogTotReq;
        ( eztmsrouteselect_ptr + i )->LogTxnReq = LogTxnReq;
        i++;
		memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getEzTMSMsgTranslateCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSMSGTRANSLATE" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSMSGTRANSLATE - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSMsgTranslate( struct EzTMSMsgTranslate *eztmsmsgtranslate_ptr, int *SqlErr )
{
	char MsgTranslateId[ 17 ];
	char TranslateDesc[ 256 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSMsgTranslate [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(MSGTRANSLATEID), RTRIM(TRANSLATEDESC) FROM EZTMSMSGTRANSLATE;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSMsgTranslate [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, MsgTranslateId, sizeof(MsgTranslateId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgTranslateId) in EZTMSMSGTRANSLATE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TranslateDesc, sizeof(TranslateDesc), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TranslateDesc) in EZTMSMSGTRANSLATE [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmsmsgtranslate_ptr + i )->MsgTranslateId, MsgTranslateId );
        strcpy( ( eztmsmsgtranslate_ptr + i )->TranslateDesc, TranslateDesc );
        i++;
		memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
		memset( TranslateDesc, 0, sizeof( TranslateDesc ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzTMSMgrODBCUtil :: getEzTMSTxnRefSelectCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZTMSTXNREFSELECT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZTMSTXNREFSELECT - Count[%d]", count);

    return count;
}

int EzTMSMgrODBCUtil :: LoadEzTMSTxnRefSelect( struct EzTMSTxnRefSelect *eztmstxnrefselect_ptr, int *SqlErr )
{
	char RecordId[ 17 ];
	char MsgType[ 5 ];
	char TxnCode[ 7 ];
	char KeyFields[ 151 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadEzTMSTxnRefSelect [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT \
    	RTRIM(RECORDID),\
    	RTRIM(MSGTYPE),\
    	RTRIM(TXNCODE),\
    	RTRIM(KEYFIELDS) \
    FROM EZTMSTXNREFSELECT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzTMSTxnRefSelect [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RecordId) in EZTMSTXNREFSELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MsgType, sizeof(MsgType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTMSTXNREFSELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TxnCode, sizeof(TxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTMSTXNREFSELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, KeyFields, sizeof(KeyFields), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(KeyFields) in EZTMSTXNREFSELECT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( ( eztmstxnrefselect_ptr + i )->RecordId, RecordId );
        strcpy( ( eztmstxnrefselect_ptr + i )->MsgType, MsgType );
        strcpy( ( eztmstxnrefselect_ptr + i )->TxnCode, TxnCode );
        strcpy( ( eztmstxnrefselect_ptr + i )->KeyFields, KeyFields );
        i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( KeyFields, 0, sizeof( KeyFields ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}
