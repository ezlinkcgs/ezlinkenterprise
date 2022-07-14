/*
 * ezatmmgrodbc.cpp
 *
 *  Created on: Jul 27, 2013
 *      Author: mohanraj
 */


#include <ezbusiness/ezatmmgrodbc.h>

int EzAtmMgrODBC :: initEzAtmMgrODBC( const char *TaskName, EzDebugUtil *dptr )
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

int EzAtmMgrODBC :: getAtmCount( )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMINFO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMINFO - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: getInstAtmCount( const char *InstId )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMINFO WHERE RTRIM(ACQUIRERINST)='%s'", InstId );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMINFO - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: getAtmFitCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMFIT" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMFIT - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: getAtmEjCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMEJINFO" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMEJINFO - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: getAtmPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMPROPERTY - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: getAtmActionPropertyCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMACTIONPROPERTY" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMACTIONPROPERTY - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: getAtmStatusCount( int *SqlErr )
{
    int count;
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "SELECT COUNT(*) FROM EZATMSTATUSDESC" );
    getTableRowCount( SqlStmt, &count );
    dptr->trace( "EZATMSTATUSDESC - Count[%d]", count);

    return count;
}

int EzAtmMgrODBC :: LoadAtmId( struct AtmMemoryTable *atm_ptr )
{
	char AtmId[ 17 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle in LoadAtmId [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(ATMID) FROM EZATMINFO;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmId [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, AtmId, sizeof(AtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(AtmId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	memset( atm_ptr + i, 0, sizeof( struct AtmMemoryTable ) );
		strcpy( ( atm_ptr + i )->AtmId, AtmId );
		memset( AtmId, 0, sizeof( AtmId ) );
		i++;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtm( struct AtmTableInfo *atminfo_ptr, char *Atmid )
{
	char hAtmId[ 17 ];
	char hAtmTypeId[ 17 ];
	char hAtmLogicalGroup[ 17 ];
	int  hMerchantId;
	char hTerminalId[ 17 ];
	char hAtmLocation[ 41 ];
	char hAcquirerInst[ 13 ];
	char hAcquirerBranchCode[ 13 ];
	int  hAtmConfigId;
	char hLoggingFlag;
	char hPinVerFlag;
	char hAtmStatus;
	char hAtmMasterKey[ 65 ];
	char hAtmCommKey[ 65 ];
	int  hAtmKeyLen;
	int  hMaxNoteDisp;
	int  hMaxAmountDisp;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
        RTRIM(ATMTYPEID), \
		RTRIM(ATMLOGICALGROUP), \
		MERCHANTID, \
		RTRIM(TERMINALID), \
		RTRIM(ATMLOCATION), \
		RTRIM(ACQUIRERINST), \
		RTRIM(ACQUIRERBRANCHCODE), \
		ATMCONFIGID, \
		LOGGINGFLAG, \
		PINVERFLAG, \
		ATMSTATUS, \
		RTRIM(ATMMASTERKEY), \
		RTRIM(ATMCOMMKEY), \
		ATMKEYLEN, \
		MAXNOTEDISP, \
		MAXAMOUNTDISP FROM EZATMINFO WHERE RTRIM(ATMID) = '%s'", Atmid );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtm [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hAtmTypeId, 0, sizeof( hAtmTypeId ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmLocation, 0, sizeof( hAtmLocation ) );
	memset( hTerminalId, 0, sizeof( hTerminalId ) );
	memset( hAcquirerInst, 0, sizeof( hAcquirerInst ) );
	memset( hAcquirerBranchCode, 0, sizeof( hAcquirerBranchCode ) );
	memset( hAtmMasterKey, 0, sizeof( hAtmMasterKey ) );
	memset( hAtmCommKey, 0, sizeof( hAtmCommKey ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, hAtmTypeId, sizeof(hAtmTypeId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmTypeId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, hAtmLogicalGroup, sizeof(hAtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLogicalGroup) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &hMerchantId, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hMerchantId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, hTerminalId, sizeof(hTerminalId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hTerminalId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, hAtmLocation, sizeof(hAtmLocation), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLocation) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, hAcquirerInst, sizeof(hAcquirerInst), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAcquirerInst) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, hAcquirerBranchCode, sizeof(hAcquirerBranchCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAcquirerBranchCode) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &hAtmConfigId, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmConfigId) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &hLoggingFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hLoggingFlag) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_BINARY, &hPinVerFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hPinVerFlag) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_BINARY, &hAtmStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmStatus) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, hAtmMasterKey, sizeof(hAtmMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmMasterKey) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, hAtmCommKey, sizeof(hAtmCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmCommKey) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_SLONG, &hAtmKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmKeyLen) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &hMaxNoteDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hMaxNoteDisp) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &hMaxAmountDisp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hMaxAmountDisp) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( atminfo_ptr->AtmTypeId, hAtmTypeId );
    	strcpy( atminfo_ptr->AtmLogicalGroup, hAtmLogicalGroup );
    	atminfo_ptr->MerchantId = hMerchantId;
    	strcpy( atminfo_ptr->TerminalId, hTerminalId );
    	strcpy( atminfo_ptr->AtmLocation, hAtmLocation );
    	strcpy( atminfo_ptr->AcquirerInst, hAcquirerInst );
    	strcpy( atminfo_ptr->AcquirerBranchCode, hAcquirerBranchCode );
    	atminfo_ptr->AtmConfigId = hAtmConfigId;
    	atminfo_ptr->LoggingFlag = hLoggingFlag;
    	atminfo_ptr->PinVerFlag = hPinVerFlag;
    	atminfo_ptr->AtmStatus = hAtmStatus;
    	strcpy( atminfo_ptr->AtmMasterKey, hAtmMasterKey );
    	strcpy( atminfo_ptr->AtmCommKey, hAtmCommKey );
    	atminfo_ptr->AtmKeyLen = hAtmKeyLen;
    	atminfo_ptr->MaxNoteDisp = hMaxNoteDisp;
    	atminfo_ptr->MaxAmountDisp = hMaxAmountDisp;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmFitDetails( struct AtmFit *atmfit_ptr )
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
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
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
	    FROM EZATMFIT;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmFitDetails [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RecordId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(InstId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, AtmLogicalGroup, sizeof(AtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(AtmLogicalGroup) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, AtmId, sizeof(AtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(AtmId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, SecurityId, sizeof(SecurityId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, FitRecord, sizeof(FitRecord), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(FitRecord) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &IndirectState, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(IndirectState) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( atmfit_ptr + i, 0, sizeof( struct AtmFit ) );
		strcpy( ( atmfit_ptr + i )->RecordId, RecordId );
		strcpy( ( atmfit_ptr + i )->InstId, InstId );
		strcpy( ( atmfit_ptr + i )->AtmLogicalGroup, AtmLogicalGroup );
		strcpy( ( atmfit_ptr + i )->AtmId, AtmId );
		strcpy( ( atmfit_ptr + i )->SecurityId, SecurityId );
		strcpy( ( atmfit_ptr + i )->FitRecord, FitRecord );
		( atmfit_ptr + i )->IndirectState = IndirectState;
		i++;
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
		memset( FitRecord, 0, sizeof( FitRecord ) );
		memset( SecurityId, 0, sizeof( SecurityId ) );
		memset( AtmId, 0, sizeof( AtmId ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmPropertyTable( struct EzAtmProperty *ezatmproperty_ptr )
{
	int	 hRecordId;
	char hInstTerminalGroup[ 17 ];
	char hAtmLogicalGroup[ 17 ];
	char hAtmId[ 17 ];
	char hDownloadCheckReq;
	char hFingerPrintCheckReq;
	char hFingerPrintCheckChannel[ 33 ];
	char hJournalPrinterReq;
	char hPassbookPrinterReq;
	char hStatementPrinterReq;
	char hPartialReversalReq;
	char hCardReaderModel;
	char hTxnCode[ 7 ];
	char hRespCode[ 4 ];
	char hDecimalPointCheckReq;
	int  hCurrencyCode;
	char hDecimalMultiplier;
	int  hCounterRefresh;
	int  hKeyRefresh;

	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RECORDID, \
    	RTRIM(INSTTERMINALGROUP), \
		RTRIM(ATMLOGICALGROUP), \
		RTRIM(ATMID), \
		RTRIM(TXNCODE), \
		RTRIM(RESPCODE), \
		DOWNLOADCHECKREQ, \
		FINGERPRINTCHECKREQ, \
		RTRIM(FINGERPRINTCHECKCHANNEL), \
		JOURNALPRINTERREQ, \
		PASSBOOKPRINTERREQ, \
		STATEMENTPRINTERREQ, \
		PARTIALREVERSALREQ, \
		CARDREADERMODEL, \
		DECIMALPOINTCHECKREQ, \
		CURRENCYCODE, \
		DECIMALMULTIPLIER, \
		COUNTERREFERSH, \
		KEYREFERSH \
	FROM EZATMPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmPropertyTable [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hRecordId, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRecordId) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, hInstTerminalGroup, sizeof(hInstTerminalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hInstTerminalGroup) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, hAtmLogicalGroup, sizeof(hAtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLogicalGroup) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, hAtmId, sizeof(hAtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmId) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, hTxnCode, sizeof(hTxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hTxnCode) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, hRespCode, sizeof(hTxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRespCode) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &hDownloadCheckReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDownloadCheckReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &hFingerPrintCheckReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hFingerPrintCheckReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, hFingerPrintCheckChannel, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hFingerPrintCheckChannel) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_BINARY, &hJournalPrinterReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hJournalPrinterReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_BINARY, &hPassbookPrinterReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hPassbookPrinterReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_BINARY, &hStatementPrinterReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatementPrinterReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_BINARY, &hPartialReversalReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hPartialReversalReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_BINARY, &hCardReaderModel, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCardReaderModel) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_BINARY, &hDecimalPointCheckReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDecimalPointCheckReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &hCurrencyCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCurrencyCode) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_BINARY, &hDecimalMultiplier, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDecimalMultiplier) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_SLONG, &hCounterRefresh, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCounterRefresh) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_SLONG, &hKeyRefresh, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hKeyRefresh) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezatmproperty_ptr + i ), 0, sizeof( struct EzAtmProperty ) );
		( ezatmproperty_ptr + i )->RecordId = hRecordId;
		strcpy( ( ezatmproperty_ptr + i )->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ( ezatmproperty_ptr + i )->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ( ezatmproperty_ptr + i )->AtmId, hAtmId );
		strcpy( ( ezatmproperty_ptr + i )->TxnCode, hTxnCode );
		strcpy( ( ezatmproperty_ptr + i )->RespCode, hRespCode );
		( ezatmproperty_ptr + i )->DownloadCheckReq = hDownloadCheckReq;
		( ezatmproperty_ptr + i )->FingerPrintCheckReq = hFingerPrintCheckReq;
		strcpy( ( ezatmproperty_ptr + i )->FingerPrintCheckChannel, hFingerPrintCheckChannel );
		( ezatmproperty_ptr + i )->JournalPrinterReq = hJournalPrinterReq;
		( ezatmproperty_ptr + i )->PassbookPrinterReq = hPassbookPrinterReq;
		( ezatmproperty_ptr + i )->StatementPrinterReq = hStatementPrinterReq;
		( ezatmproperty_ptr + i )->PartialReversalReq = hPartialReversalReq;
		( ezatmproperty_ptr + i )->CardReaderModel = hCardReaderModel;
		( ezatmproperty_ptr + i )->DecimalPointCheckReq = hDecimalPointCheckReq;
		( ezatmproperty_ptr + i )->CurrencyCode = hCurrencyCode;
		( ezatmproperty_ptr + i )->DecimalMultiplier = hDecimalMultiplier;
		( ezatmproperty_ptr + i )->CounterRefresh = hCounterRefresh;
		( ezatmproperty_ptr + i )->KeyRefresh = hKeyRefresh;
		i++;
		memset( hInstTerminalGroup, 0, sizeof( hInstTerminalGroup ) );
		memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
		memset( hAtmId, 0, sizeof( hAtmId ) );
		memset( hFingerPrintCheckChannel, 0, sizeof( hFingerPrintCheckChannel ) );
		memset( hTxnCode, 0, sizeof( hTxnCode ) );
		memset( hRespCode, 0, sizeof( hRespCode ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmActionPropertyTable( struct EzAtmActionProperty *ezatmactionproperty_ptr )
{
	int  hRecordId;
	char hInstTerminalGroup[ 17 ];
	char hAtmLogicalGroup[ 17 ];
	char hAtmId[ 17 ];
	char hStatus[ 11 ];
	char hSendCommand;
	char hCommand[ 21 ];
	char hSendResponse;
	char hTxnCode[ 7 ];
	char hRespCode[ 4 ];

	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RECORDID, \
    	RTRIM(INSTTERMINALGROUP), \
		RTRIM(LOGICALGROUPID), \
		RTRIM(ATMID), \
		RTRIM(STATUS), \
		SENDCOMMAND, \
		RTRIM(COMMAND), \
		SENDRESPONSE, \
		RTRIM(TXNCODE), \
		RESPCODE \
	FROM EZATMACTIONPROPERTY;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmActionPropertyTable [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( hInstTerminalGroup, 0, sizeof( hInstTerminalGroup ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hStatus, 0, sizeof( hStatus ) );
	memset( hCommand, 0, sizeof( hCommand ) );
	memset( hTxnCode, 0, sizeof( hTxnCode ) );
	memset( hRespCode, 0, sizeof( hRespCode ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hRecordId, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRecordId) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, hInstTerminalGroup, sizeof(hInstTerminalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hInstTerminalGroup) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, hAtmLogicalGroup, sizeof(hAtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLogicalGroup) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, hAtmId, sizeof(hAtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmId) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, hStatus, sizeof(hStatus), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatus) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &hSendCommand, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hSendCommand) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, hCommand, sizeof(hCommand), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCommand) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &hSendResponse, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hSendResponse) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, hTxnCode, sizeof(hTxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hTxnCode) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, hRespCode, sizeof(hRespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRespCode) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezatmactionproperty_ptr, 0, sizeof( struct EzAtmActionProperty ) );
		ezatmactionproperty_ptr->RecordId = hRecordId;
		strcpy( ezatmactionproperty_ptr->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ezatmactionproperty_ptr->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ezatmactionproperty_ptr->AtmId, hAtmId );
		strcpy( ezatmactionproperty_ptr->Status, hStatus );
		ezatmactionproperty_ptr->SendCommand = hSendCommand;
		strcpy( ezatmactionproperty_ptr->Command, hCommand );
		ezatmactionproperty_ptr->SendResponse = hSendResponse;
		strcpy( ezatmactionproperty_ptr->TxnCode, hTxnCode );
		strcpy( ezatmactionproperty_ptr->RespCode, hRespCode );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmStaticCode( const char *AtmId, char *StaticCode )
{
	char hStaticCode[ 101 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT STATICCODE FROM EZATMSTATUS WHERE RTRIM(ATMID)='%s';", AtmId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmStaticCode [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, hStaticCode, sizeof(hStaticCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStaticCode) in EZATMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( StaticCode, hStaticCode );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmDenom( const char *AtmId, struct DenomInfo *denominfo_ptr )
{
	char hStatus;
	int  hCurrencyValue;
	int  hCurrencyCode;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    switch( denominfo_ptr->DenomId )
    {
		case 'A':
			sprintf( SqlStmt, "SELECT DENOMASTATUS, DENOMAVALUE, DENOMACURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'B':
			sprintf( SqlStmt, "SELECT DENOMBSTATUS, DENOMBVALUE, DENOMBCURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'C':
			sprintf( SqlStmt, "SELECT DENOMCSTATUS, DENOMCVALUE, DENOMCCURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'D':
			sprintf( SqlStmt, "SELECT DENOMDSTATUS, DENOMDVALUE, DENOMDCURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'E':
			sprintf( SqlStmt, "SELECT DENOMESTATUS, DENOMEVALUE, DENOMECURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'F':
			sprintf( SqlStmt, "SELECT DENOMFSTATUS, DENOMFVALUE, DENOMFCURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'G':
			sprintf( SqlStmt, "SELECT DENOMGSTATUS, DENOMGVALUE, DENOMGCURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		case 'H':
			sprintf( SqlStmt, "SELECT DENOMHSTATUS, DENOMHVALUE, DENOMHCURRCODE FROM EZATMINFO WHERE RTRIM(ATMID) ='%s'",  AtmId );
			break;

		Default:
			break;
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmDenom [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_BINARY, &hStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatus) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &hCurrencyValue, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCurrencyValue) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &hCurrencyCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCurrencyCode) in EZATMINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	denominfo_ptr->Status = hStatus;
    	denominfo_ptr->CurrencyValue = hCurrencyValue;
    	denominfo_ptr->CurrencyCode = hCurrencyCode;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmEjDetails( const char *AtmId, struct ATMEjBuffer *atmej_ptr )
{
	char hInstId[ INST_SIZE + 1 ];
	char hAtmTypeId[ ATM_ID_SIZE + 1 ];
	char hAtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	char hAtmStatus;
	char hAtmEjPortName[ ATM_ID_SIZE + 1 ];
	char hCurrentFile[ 26 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
			RTRIM(INSTID), \
			RTRIM(ATMTYPEID), \
			RTRIM(LOGICALGROUP), \
			ATMSTATUS, \
			RTRIM(EJPORTNAME), \
			RTRIM(LASTFILENAME) \
			FROM EZATMEJINFO WHERE RTRIM(ATMID)='%s';", AtmId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmEjDetails [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( hInstId, 0, sizeof( hInstId ) );
	memset( hAtmTypeId, 0, sizeof( hAtmTypeId ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmEjPortName, 0, sizeof( hAtmEjPortName ) );
	memset( hCurrentFile, 0, sizeof( hCurrentFile ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, hInstId, sizeof(hInstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hInstId) in EZATMEJINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, hAtmTypeId, sizeof(hAtmTypeId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmTypeId) in EZATMEJINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, hAtmLogicalGroup, sizeof(hAtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLogicalGroup) in EZATMEJINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_BINARY, &hAtmStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmStatus) in EZATMEJINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, hAtmEjPortName, sizeof(hAtmEjPortName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmEjPortName) in EZATMEJINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, hCurrentFile, sizeof(hCurrentFile), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCurrentFile) in EZATMEJINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	memset( atmej_ptr, 0, sizeof( struct ATMEjBuffer ) );
       	strcpy( atmej_ptr->InstId, hInstId );
    	strcpy( atmej_ptr->AtmId, AtmId );
		strcpy( atmej_ptr->AtmTypeId, hAtmTypeId );
		strcpy( atmej_ptr->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( atmej_ptr->AtmEjPortName, hAtmEjPortName );
		atmej_ptr->AtmStatus = hAtmStatus;
		strcpy( atmej_ptr->CurrentFile, hCurrentFile );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}
int EzAtmMgrODBC :: LoadAtmStatusTable( struct EzAtmStatus *ezatmstatus_ptr )
{
	char hStatusCode[ 11 ];
	char hStatusFlag;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    strcpy( SqlStmt,  "SELECT RTRIM(STATUSCODE),STATUSFLAG FROM EZATMSTATUSDESC;" );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmStatusTable [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, hStatusCode, sizeof(hStatusCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatusCode) in EZATMSTATUSDESC [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &hStatusFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatusFlag) in EZATMSTATUSDESC [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezatmstatus_ptr + i ), 0, sizeof( struct EzAtmStatus ) );
		strcpy( ( ezatmstatus_ptr + i )->StatusCode, hStatusCode );
		( ezatmstatus_ptr + i )->StatusFlag = hStatusFlag;
		i++;
		memset( hStatusCode, 0, sizeof( hStatusCode ) );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: LoadAtmBatchId( char *AtmId, char *BatchId )
{
	char hBatchId[ 13 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(BATCHID) FROM EZATMDATAINFO WHERE RTRIM(ATMID) ='%s';", AtmId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmBatchId [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, hBatchId, sizeof(hBatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hBatchId) in EZATMSTATUSDESC [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( BatchId, hBatchId );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: GetTraceNum( char *AtmId )
{
	int hTraceNum;
	char hBatchId[ 13 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(TRACENUM) FROM EZATMDATAINFO WHERE RTRIM(ATMID) ='%s';", AtmId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmBatchId [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hTraceNum, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hTraceNum) in EZATMSTATUSDESC [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if( ( odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return hTraceNum;
    }
    else
    {
    	hTraceNum = 1;
		strcpy( hBatchId, "123456789000" );
	    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	    sprintf( SqlStmt, "INSERT INTO EZATMDATAINFO(ATMID,TRACENUM,BATCHID) VALUES ('%s',%d,'%s');", AtmId, hTraceNum, hBatchId);
	    if( ExecuteQuery( SqlStmt, true ) < 0 )
	    	return -1;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    return 0;
}

int EzAtmMgrODBC :: AddAtmFit( struct AtmFit *Atmfit_ptr, struct AtmFitMsg *Atmfitmsg )
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
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
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
	    FROM EZATMFIT WHERE ( RTRIM(INSTID)='%s' AND RTRIM(FITRECORD)='%s';", Atmfitmsg->InstId, Atmfitmsg->FitRecord );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmFitDetails [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
	memset( FitRecord, 0, sizeof( FitRecord ) );
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( AtmId, 0, sizeof( AtmId ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(RecordId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(InstId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, AtmLogicalGroup, sizeof(AtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(AtmLogicalGroup) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, AtmId, sizeof(AtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(AtmId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, SecurityId, sizeof(SecurityId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, FitRecord, sizeof(FitRecord), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(FitRecord) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &IndirectState, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(IndirectState) in EZATMFIT [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		strcpy( Atmfit_ptr->RecordId, RecordId );
	   	strcpy( Atmfit_ptr->InstId, InstId );
    	strcpy( Atmfit_ptr->AtmLogicalGroup, AtmLogicalGroup );
    	strcpy( Atmfit_ptr->AtmId, AtmId );
    	strcpy( Atmfit_ptr->FitRecord, FitRecord );
    	strcpy( Atmfit_ptr->SecurityId, SecurityId );
    	Atmfit_ptr->IndirectState = IndirectState;

    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: InsertATMStatus( char *StaticCode, char *DynamicCode, char *AtmId, char *Date, char *Time )
{
    char SqlStmt[ 1024 ];
    char Input_date[ 10 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
        memset( Input_date, 0, sizeof( Input_date ) );
        getMSSQLDateFmt( Date, Input_date);
        memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt, "INSERT INTO EZATMSTATUSHIST( \
			ATMID, \
			STATICCODE, \
			DYNAMICCODE, \
			LOGDATE, \
			LOGTIME  \
		) VALUES \
		(  '%s', '%s', '%s', convert(varchar,'%s',105), %s );", AtmId, StaticCode, DynamicCode, Input_date, Time);
    }
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzAtmMgrODBC :: UpdateATMStatus( char *StaticCode, char *DynamicCode, char *AtmId, char *Date, char *Time )
{
    char SqlStmt[ 1024 ];
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( Date, Input_date );
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt, "UPDATE EZATMSTATUS SET \
			STATICCODE='%s', \
			DYNAMICCODE='%s', \
			LOGDATE=convert(varchar,'%s',105), \
			LOGTIME='%s' \
			WHERE RTRIM(ATMID)='%s';", StaticCode, DynamicCode, Input_date, Time, AtmId );
	}
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzAtmMgrODBC :: InsertAtmLog( struct LogDetails *logdetails )
{
    char SqlStmt[ 1024 ];
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( logdetails->Date, Input_date );
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt, "INSERT INTO EZATMLOG \
		( ATMID, ATMMSG, LOGDATE, LOGTIME, FLAG ) \
		VALUES \
		('%s','%s',convert(varchar,'%s',105),'%s','%c');", \
		logdetails->AtmId, logdetails->AtmMsg, Input_date, logdetails->Time, logdetails->Flag );
	}
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzAtmMgrODBC :: InsertAtmDenomHist( struct AtmDenomStatusMsg *atmdenomstatus_ptr )
{
    char SqlStmt[ 1024 ];
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( atmdenomstatus_ptr->ResetDate, Input_date );
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt, "INSERT INTO EZATMDENOMHIST( \
			ATMID, \
			BATCHID, \
			REFNUM, \
			DENOM_A_NOTESDISP, \
			DENOM_B_NOTESDISP, \
			DENOM_C_NOTESDISP, \
			DENOM_D_NOTESDISP, \
			DENOM_E_NOTESDISP, \
			DENOM_F_NOTESDISP, \
			DENOM_G_NOTESDISP, \
			DENOM_H_NOTESDISP, \
			LASTRESETDATE, \
			LASTRESETTIME \
		)VALUES \
		('%s', '%s', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', convert(varchar,'%s',105), '%s');", \
		atmdenomstatus_ptr->AtmId, \
		atmdenomstatus_ptr->BatchId, \
		atmdenomstatus_ptr->RefNum, \
		atmdenomstatus_ptr->Denom_A_Disp, \
		atmdenomstatus_ptr->Denom_B_Disp, \
		atmdenomstatus_ptr->Denom_C_Disp, \
		atmdenomstatus_ptr->Denom_D_Disp, \
		atmdenomstatus_ptr->Denom_E_Disp, \
		atmdenomstatus_ptr->Denom_F_Disp, \
		atmdenomstatus_ptr->Denom_G_Disp, \
		atmdenomstatus_ptr->Denom_H_Disp, \
		Input_date, \
		atmdenomstatus_ptr->ResetTime );
	}
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzAtmMgrODBC :: UpdateAtmDenomStatus( struct AtmDenomStatusMsg *atmdenomstatus_ptr )
{
	char hAtmId[ 17 ];
	char hBatchId[ 13 ];
	char hRefNum[ 13 ];
	int hDenom_A_Disp;
	int hDenom_B_Disp;
	int hDenom_C_Disp;
	int hDenom_D_Disp;
	int hDenom_E_Disp;
	int hDenom_F_Disp;
	int hDenom_G_Disp;
	int hDenom_H_Disp;
    char hResetDate[ 7 ];
	char hResetTime[ 7 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT  \
		DENOM_A_NOTESDISP, \
		DENOM_B_NOTESDISP, \
		DENOM_C_NOTESDISP, \
		DENOM_D_NOTESDISP, \
		DENOM_E_NOTESDISP, \
		DENOM_F_NOTESDISP, \
		DENOM_G_NOTESDISP, \
		DENOM_H_NOTESDISP \
	FROM EZATMDENOMSTATUS WHERE RTRIM(ATMID)='%s';", atmdenomstatus_ptr->AtmId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in UpdateAtmDenomStatus [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hDenom_A_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_A_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &hDenom_B_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_B_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }


    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &hDenom_C_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_C_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &hDenom_D_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_D_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &hDenom_E_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_E_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_SLONG, &hDenom_F_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_F_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &hDenom_G_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_G_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &hDenom_H_Disp, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDenom_H_Disp) in EZATMDENOMSTATUS [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    if(  SQLFetch( hstmt ) != SQL_NO_DATA )
    {
	//dptr->trace( " A [ %d ], B [ %d ], C [ %d ], D[ %d ], E[ %d ], F[ %d ], G[ %d ], H[ %d ]", hDenom_A_Disp, hDenom_B_Disp, hDenom_C_Disp, hDenom_D_Disp, hDenom_E_Disp, hDenom_F_Disp, hDenom_G_Disp, hDenom_H_Disp );

    	hDenom_A_Disp += atmdenomstatus_ptr->Denom_A_Disp;
    	hDenom_B_Disp += atmdenomstatus_ptr->Denom_B_Disp;
    	hDenom_C_Disp += atmdenomstatus_ptr->Denom_C_Disp;
    	hDenom_D_Disp += atmdenomstatus_ptr->Denom_D_Disp;
    	hDenom_E_Disp += atmdenomstatus_ptr->Denom_E_Disp;
    	hDenom_F_Disp += atmdenomstatus_ptr->Denom_F_Disp;
    	hDenom_G_Disp += atmdenomstatus_ptr->Denom_G_Disp;
    	hDenom_H_Disp += atmdenomstatus_ptr->Denom_H_Disp;
    }
    else
    {
	dptr->trace( "The Denom Status Entries AtmId [ %s ] Not Found ", atmdenomstatus_ptr->AtmId );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return -1403;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );

	//dptr->trace( " After Read A [ %d ], B [ %d ], C [ %d ], D[ %d ], E[ %d ], F[ %d ], G[ %d ], H[ %d ]", hDenom_A_Disp, hDenom_B_Disp, hDenom_C_Disp, hDenom_D_Disp, hDenom_E_Disp, hDenom_F_Disp, hDenom_G_Disp, hDenom_H_Disp );
    char Input_date[ 10 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );

		getMSSQLDateFmt( atmdenomstatus_ptr->ResetDate, Input_date );
		memset( SqlStmt, 0, sizeof( SqlStmt ) );
		sprintf( SqlStmt, "UPDATE EZATMDENOMSTATUS SET \
			DENOM_A_NOTESDISP=%d, \
			DENOM_B_NOTESDISP=%d, \
			DENOM_C_NOTESDISP=%d, \
			DENOM_D_NOTESDISP=%d, \
			DENOM_E_NOTESDISP=%d, \
			DENOM_F_NOTESDISP=%d, \
			DENOM_G_NOTESDISP=%d, \
			DENOM_H_NOTESDISP=%d, \
			LASTRESETDATE=convert(varchar,'%s',105), \
			LASTRESETTIME='%s' \
		WHERE RTRIM(ATMID)='%s';", \
		hDenom_A_Disp, \
		hDenom_B_Disp, \
		hDenom_C_Disp, \
		hDenom_D_Disp, \
		hDenom_E_Disp, \
		hDenom_F_Disp, \
		hDenom_G_Disp, \
		hDenom_H_Disp, \
		Input_date, \
		atmdenomstatus_ptr->ResetTime, \
		atmdenomstatus_ptr->AtmId );
	}
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzAtmMgrODBC :: UpdateAtmTraceNo( struct AtmTraceNumMsg *devtraceno_ptr )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZATMDATAINFO SET \
		TRACENUM=%d \
	WHERE RTRIM(ATMID)='%s';", devtraceno_ptr->AtmTraceNo, devtraceno_ptr->AtmId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzAtmMgrODBC :: InsertAtmTraceNo( struct AtmTraceNumMsg *devtraceno_ptr )
{
    char SqlStmt[ 1024 ];
    char hBatchId[ 13 ];

    memset( hBatchId, 0, sizeof( hBatchId ) );
    strcpy( hBatchId, "123456789123" );

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "INSERT INTO EZATMDATAINFO \
	( \
		ATMID, \
		TRACENUM, \
		BATCHID \
	) \
	VALUES \
	( \
		'%s', \
		'%d', \
		'%s');", devtraceno_ptr->AtmId, devtraceno_ptr->AtmTraceNo, hBatchId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;


	return 0;
}

int EzAtmMgrODBC :: updateTritonStatusLog( char *AtmId, struct TritonStatusMsg *StatusMsg )
{
    char SqlStmt[ 1024 ];


    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE TRITONSTATUSLOG SET \
		PGMVERSIONNO='%s', \
		TABVERSIONNO='%s', \
		FIRMVERSIONNO='%s', \
		ALARMCHESTDOOR='%c', \
		ALARMTOPDOOR='%c', \
		ALARMSUPERVISOR='%c', \
		RPPAPER='%c', \
		RPRIBBON='%c', \
		JPPAPER='%c', \
		JPRIBBON='%c', \
		DISPNOTE='%c', \
		RPSTATUS='%c', \
		JPSTATUS='%c', \
		DISPSTATUS='%c', \
		COMMSYSTEM='%c', \
		CARDREADER='%c', \
		CARDSRETAINED='%s', \
		ERRCODE='%s', \
		CASSADENOM='%s', \
		CASSALOADED='%s', \
		CASSAMIN='%s', \
		CASSADISP='%s', \
		CASSAREJECT='%s', \
		CASSANOTES='%s', \
		CASSACASH='%s', \
		CASSBDENOM='%s', \
		CASSBLOADED='%s', \
		CASSBMIN='%s', \
		CASSBDISP='%s', \
		CASSBREJECT='%s', \
		CASSBNOTES='%s', \
		CASSBCASH='%s', \
		CASSCDENOM='%s', \
		CASSCLOADED='%s', \
		CASSCMIN='%s', \
		CASSCDISP='%s', \
		CASSCREJECT='%s', \
		CASSCNOTES='%s', \
		CASSCCASH='%s', \
		CASSDDENOM='%s', \
		CASSDLOADED='%s', \
		CASSDMIN='%s', \
		CASSDDISP='%s', \
		CASSDREJECT='%s', \
		CASSDNOTES='%s', \
		CASSDCASH='%s', \
		TOTCASH='%s', \
		TOTNOTESPURGED='%s', \
		LOGDATE=to_date( %s, 'dd-mm-yy' ), \
		LOGTIME='%s', \
		WHERE RTRIM(AtmID)='%s';",
		StatusMsg->PgmVersionNo,
		StatusMsg->TabVersionNo,
		StatusMsg->FirmVersionNo,
		StatusMsg->AlarmChestDoor,
		StatusMsg->AlarmTopDoor,
		StatusMsg->AlarmSupervisor,
		StatusMsg->RPPaper,
		StatusMsg->RPRibbon,
		StatusMsg->JPPaper,
		StatusMsg->JPRibbon,
		StatusMsg->DispNote,
		StatusMsg->RPStatus,
		StatusMsg->JPStatus,
		StatusMsg->DispStatus,
		StatusMsg->CommSystem,
		StatusMsg->CardReader,
		StatusMsg->CardsRetained,
		StatusMsg->ErrCode,
		StatusMsg->CassADenom,
		StatusMsg->CassALoaded,
		StatusMsg->CassAMin,
		StatusMsg->CassADisp,
		StatusMsg->CassAReject,
		StatusMsg->CassANotes,
		StatusMsg->CassACash,
		StatusMsg->CassBDenom,
		StatusMsg->CassBLoaded,
		StatusMsg->CassBMin,
		StatusMsg->CassBDisp,
		StatusMsg->CassBReject,
		StatusMsg->CassBNotes,
		StatusMsg->CassBCash,
		StatusMsg->CassCDenom,
		StatusMsg->CassCLoaded,
		StatusMsg->CassCMin,
		StatusMsg->CassCDisp,
		StatusMsg->CassCReject,
		StatusMsg->CassCNotes,
		StatusMsg->CassCCash,
		StatusMsg->CassDDenom,
		StatusMsg->CassDLoaded,
		StatusMsg->CassDMin,
		StatusMsg->CassDDisp,
		StatusMsg->CassDReject,
		StatusMsg->CassDNotes,
		StatusMsg->CassDCash,
		StatusMsg->TotCash,
		StatusMsg->TotNotesPurged,
		StatusMsg->StatusDate,
		StatusMsg->StatusTime,
		AtmId);

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

    //Check for Insert
	return 0;
}

int EzAtmMgrODBC :: ReadAtmPropertyTable( struct EzAtmProperty *ezatmproperty_ptr, int RecordId )
{
	int	 hRecordId;
	char hInstTerminalGroup[ 17 ];
	char hAtmLogicalGroup[ 17 ];
	char hAtmId[ 17 ];
	char hDownloadCheckReq;
	char hFingerPrintCheckReq;
	char hFingerPrintCheckChannel[ 33 ];
	char hJournalPrinterReq;
	char hPassbookPrinterReq;
	char hStatementPrinterReq;
	char hPartialReversalReq;
	char hCardReaderModel;
	char hTxnCode[ 7 ];
	char hRespCode[ 4 ];
	char hDecimalPointCheckReq;
	int  hCurrencyCode;
	char hDecimalMultiplier;
	int  hCounterRefresh;
	int  hKeyRefresh;

	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RECORDID, \
    	RTRIM(INSTTERMINALGROUP), \
		RTRIM(ATMLOGICALGROUP), \
		RTRIM(ATMID), \
		RTRIM(TXNCODE), \
		RTRIM(RESPCODE), \
		DOWNLOADCHECKREQ, \
		FINGERPRINTCHECKREQ, \
		RTRIM(FINGERPRINTCHECKCHANNEL), \
		JOURNALPRINTERREQ, \
		PASSBOOKPRINTERREQ, \
		STATEMENTPRINTERREQ, \
		PARTIALREVERSALREQ, \
		CARDREADERMODEL, \
		DECIMALPOINTCHECKREQ, \
		CURRENCYCODE, \
		DECIMALMULTIPLIER, \
		COUNTERREFERSH, \
		KEYREFERSH \
	FROM EZATMPROPERTY WHERE RECORDID=%d;", RecordId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmPropertyTable [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( hInstTerminalGroup, 0, sizeof( hInstTerminalGroup ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hFingerPrintCheckChannel, 0, sizeof( hFingerPrintCheckChannel ) );
	memset( hTxnCode, 0, sizeof( hTxnCode ) );
	memset( hRespCode, 0, sizeof( hRespCode ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hRecordId, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRecordId) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, hInstTerminalGroup, sizeof(hInstTerminalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hInstTerminalGroup) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, hAtmLogicalGroup, sizeof(hAtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLogicalGroup) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, hAtmId, sizeof(hAtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmId) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &hDownloadCheckReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDownloadCheckReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &hFingerPrintCheckReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hFingerPrintCheckReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, hFingerPrintCheckChannel, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hFingerPrintCheckChannel) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &hJournalPrinterReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hJournalPrinterReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_BINARY, &hPassbookPrinterReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hPassbookPrinterReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_BINARY, &hStatementPrinterReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatementPrinterReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_BINARY, &hPartialReversalReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hPartialReversalReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_BINARY, &hCardReaderModel, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCardReaderModel) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, hTxnCode, sizeof(hTxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hTxnCode) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_CHAR, hRespCode, sizeof(hRespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRespCode) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_BINARY, &hDecimalPointCheckReq, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDecimalPointCheckReq) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &hCurrencyCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCurrencyCode) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_BINARY, &hDecimalMultiplier, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hDecimalMultiplier) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_SLONG, &hCounterRefresh, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCounterRefresh) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_SLONG, &hKeyRefresh, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hKeyRefresh) in EZATMPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ezatmproperty_ptr, 0, sizeof( struct EzAtmProperty ) );
		ezatmproperty_ptr->RecordId = RecordId;
		strcpy( ezatmproperty_ptr->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ezatmproperty_ptr->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ezatmproperty_ptr->AtmId, hAtmId );
		strcpy( ezatmproperty_ptr->TxnCode, hTxnCode );
		strcpy( ezatmproperty_ptr->RespCode, hRespCode );
		ezatmproperty_ptr->DownloadCheckReq = hDownloadCheckReq;
		ezatmproperty_ptr->FingerPrintCheckReq = hFingerPrintCheckReq;
		strcpy( ezatmproperty_ptr->FingerPrintCheckChannel, hFingerPrintCheckChannel );
		ezatmproperty_ptr->JournalPrinterReq = hJournalPrinterReq;
		ezatmproperty_ptr->PassbookPrinterReq = hPassbookPrinterReq;
		ezatmproperty_ptr->StatementPrinterReq = hStatementPrinterReq;
		ezatmproperty_ptr->PartialReversalReq = hPartialReversalReq;
		ezatmproperty_ptr->CardReaderModel = hCardReaderModel;
		ezatmproperty_ptr->DecimalPointCheckReq = hDecimalPointCheckReq;
		ezatmproperty_ptr->CurrencyCode = hCurrencyCode;
		ezatmproperty_ptr->DecimalMultiplier = hDecimalMultiplier;
		ezatmproperty_ptr->CounterRefresh = hCounterRefresh;
		ezatmproperty_ptr->KeyRefresh = hKeyRefresh;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: ReadAtmActionPropertyTable( struct EzAtmActionProperty *ezatmactionproperty_ptr, int RecordId )
{
	int  hRecordId;
	char hInstTerminalGroup[ 17 ];
	char hAtmLogicalGroup[ 17 ];
	char hAtmId[ 17 ];
	char hStatus[ 11 ];
	char hSendCommand;
	char hCommand[ 21 ];
	char hSendResponse;
	char hTxnCode[ 7 ];
	char hRespCode[ 4 ];

	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
    	RECORDID, \
    	RTRIM(INSTTERMINALGROUP), \
		RTRIM(LOGICALGROUPID), \
		RTRIM(ATMID), \
		RTRIM(STATUS), \
		SENDCOMMAND, \
		RTRIM(COMMAND), \
		SENDRESPONSE, \
		RTRIM(TXNCODE), \
		RESPCODE \
	FROM EZATMACTIONPROPERTY  WHERE RECORDID=%d;", RecordId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmActionPropertyTable [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( hInstTerminalGroup, 0, sizeof( hInstTerminalGroup ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hStatus, 0, sizeof( hStatus ) );
	memset( hCommand, 0, sizeof( hCommand ) );
	memset( hTxnCode, 0, sizeof( hTxnCode ) );
	memset( hRespCode, 0, sizeof( hRespCode ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &hRecordId, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRecordId) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, hInstTerminalGroup, sizeof(hInstTerminalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hInstTerminalGroup) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, hAtmLogicalGroup, sizeof(hAtmLogicalGroup), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmLogicalGroup) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, hAtmId, sizeof(hAtmId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hAtmId) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, hStatus, sizeof(hStatus), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatus) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &hSendCommand, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hSendCommand) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, hCommand, sizeof(hCommand), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hCommand) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &hSendResponse, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hSendResponse) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, hTxnCode, sizeof(hTxnCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hTxnCode) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, hRespCode, sizeof(hRespCode), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hRespCode) in EZATMACTIONPROPERTY [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		memset( ( ezatmactionproperty_ptr + i ), 0, sizeof( struct EzAtmActionProperty ) );
		( ezatmactionproperty_ptr + i )->RecordId = hRecordId;
		strcpy( ( ezatmactionproperty_ptr + i )->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ( ezatmactionproperty_ptr + i )->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ( ezatmactionproperty_ptr + i )->AtmId, hAtmId );
		strcpy( ( ezatmactionproperty_ptr + i )->Status, hStatus );
		( ezatmactionproperty_ptr + i )->SendCommand = hSendCommand;
		strcpy( ( ezatmactionproperty_ptr + i )->Command, hCommand );
		( ezatmactionproperty_ptr + i )->SendResponse = hSendResponse;
		strcpy( ( ezatmactionproperty_ptr + i )->TxnCode, hTxnCode );
		strcpy( ( ezatmactionproperty_ptr + i )->RespCode, hRespCode );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: ReadAtmStatusTable( struct EzAtmStatus *ezatmstatus_ptr, const char *StatusCode )
{
	char hStatusFlag;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT STATUSFLAG FROM EZATMSTATUSDESC WHERE RTRIM(STATUSCODE)='%s';", StatusCode );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in LoadAtmStatusTable [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_BINARY, &hStatusFlag, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(hStatusFlag) in EZATMSTATUSDESC [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
		ezatmstatus_ptr->StatusFlag = hStatusFlag;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzAtmMgrODBC :: TruncateAtmLog( )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "TRUNCATE TABLE EZATMLOG;");

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzAtmMgrODBC :: TruncateAtmStatusHist( )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "TRUNCATE TABLE EZATMSTATUSHIST");

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

