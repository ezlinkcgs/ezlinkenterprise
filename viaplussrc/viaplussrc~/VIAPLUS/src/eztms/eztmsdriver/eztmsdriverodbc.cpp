/*
 * eztmsdriverodbc.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: mohanraj
 */

#include <eztms/eztmsdriverodbc.h>

int EzTMSDriverODBC :: initEzTMSDriverODBC( const char *TaskName, EzDebugUtil *dptr )
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

int EzTMSDriverODBC :: ConnectDB()
{
	if( DBConnect( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzTMSDriverODBC :: CloseDB()
{
	if( DBClose( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Dis-Connecting the Database");
		return -1;
	}
	return 1;
}

int EzTMSDriverODBC :: updateTerminalStatus( struct EzTMSTermStatusUpdate *termstatusptr,  int *SqlErr )
{
    char SqlStmt[ 1024 ];
    *SqlErr = 0;

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "INSERT INTO EZMMS_TERMINALSTATUSHIST SELECT * FROM EZMMS_TERMINALSTATUS;" );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}


int EzTMSDriverODBC :: updateTermCommKey( const char *I_MachineId, char *CommKey )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE  EZMMS_TERMINALPROFILE SET TERM_PIN_KEY='%s' WHERE MACHINE_ID='%s';", CommKey, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}


int EzTMSDriverODBC :: insertTerminalBatchTxnInfo( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum, char I_MatchFlag, const char *I_MatchDesc )
{
    char SqlStmt[ 1024 ];
    char I_TranDate[ 11 ], I_LocalDate[ 11 ];
    char TempDate[ 11 ];
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( I_TranDate, 0, sizeof( I_TranDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->TranDate );
		getMSSQLDateFmt( TempDate, I_TranDate );

		memset( I_LocalDate, 0, sizeof( I_LocalDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->LocalDate );
		getMSSQLDateFmt( TempDate, I_LocalDate );

		sprintf( SqlStmt, "INSERT INTO EZMMSBATCHTXNINFO \
		( \
			INSTID,\
			MACHINEID,\
			TERMID,\
			MERCHANTID,\
			BATCHID,\
			TXNREFNUM,\
			MSGTYPE,\
			TXNCODE,\
			CHN,\
			TERMLOC,\
			TRACENO,\
			AUTHNUM,\
			REFNUM,\
			TRANDATE,\
			TRANTIME,\
			LOCALDATE,\
			LOCALTIME,\
			RESPCODE,\
			AUTHCODE,\
			CURRENCYCODE,\
			MCC,\
			TXNAMOUNT,\
			TERMAMOUNT,\
			MATCHFLAG,\
			MATCHDESC\
		) \
		VALUES \
		( '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%s', '%s', '%d', '%s', '%s', convert(varchar,'%s',105), '%d', convert(varchar,'%s',105), '%d', '%d', '%d', '%d', '%d', '%s', '%s', '%c', '%s');",
		txnmsg->AcquirerInst,
		I_MachineId,
		txnmsg->TerminalId,
		txnmsg->AcceptorId,
		txnmsg->BatchId,
		I_TMSTxnRefNum,
		txnmsg->MsgType,
		txnmsg->TxnCode,
		txnmsg->chn,
		txnmsg->TerminalLocation,
		txnmsg->TraceNo,
		txnmsg->AuthNum,
		txnmsg->RefNum,
		I_TranDate,
		txnmsg->TranTime,
		I_LocalDate,
		txnmsg->LocalTime,
		txnmsg->RespCode,
		txnmsg->AuthCode,
		txnmsg->AcqCurrencyCode,
		txnmsg->MerchantType,
		"0.00",
		txnmsg->Amount,
		I_MatchFlag,
		I_MatchDesc);
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: getTotals( const char *I_MachineId, const char *I_BatchId, struct EzTerminalTotal *tot_ptr )
{
	char MachineId[ 33 ];
	int SaleCount;
	char SaleAmount[ 21 ];
	int TermSaleCount;
	char TermSaleAmount[ 21 ];
	int VoidCount;
	char VoidAmount[ 21 ];
	int TermVoidCount;
	char TermVoidAmount[ 21 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ] in getTotals", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SqlStmt,  "SELECT \
			COUNT(*), \
			SUM(CAST(TERMAMOUNT as FLOAT)),\
			SUM(CAST(TXNAMOUNT as FLOAT)) \
		FROM EZMMSBATCHTXNINFO WHERE RTRIM(MACHINEID) ='%s' AND TXNCODE LIKE '61%';", I_MachineId );
	}
	else
	{
		sprintf( SqlStmt,  "SELECT \
			COUNT(*), \
			SUM(RTRIM(TERMAMOUNT)),\
			SUM(RTRIM(TXNAMOUNT)) \
		FROM EZMMSBATCHTXNINFO WHERE RTRIM(MACHINEID) ='%s' AND TXNCODE LIKE '61%';", I_MachineId );
	}
    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in getTotals [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &SaleCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(SaleCount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TermSaleAmount, sizeof(TermSaleAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TermSaleAmount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, SaleAmount, sizeof(SaleAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(SaleAmount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLFetch( hstmt );
    if( SQL_SUCCEEDED( odbcret ) )
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    }
    else if( odbcret == SQL_NO_DATA )
    {
    	dptr->trace(  DEBUG_ERROR, "SQL_NO_DATA" );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		SaleCount = 0;
		TermSaleCount = 0;
		memset( SaleAmount, 0, sizeof( SaleAmount ) );
		strcpy( SaleAmount, "0.00" );
		memset( TermSaleAmount, 0, sizeof( TermSaleAmount ) );
		strcpy( TermSaleAmount, "0.00" );
    }
    else
    {
    	dptr->trace(  DEBUG_ERROR, "Fetch Error [%d]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	if( SaleCount == 0 )
	{
		memset( SaleAmount, 0, sizeof( SaleAmount ) );
		strcpy( SaleAmount, "0.00" );
		TermSaleCount = 0;
		memset( TermSaleAmount, 0, sizeof( TermSaleAmount ) );
		strcpy( TermSaleAmount, "0.00" );
	}

	TermSaleCount = SaleCount;


    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ] in getTotals", odbcret );
		return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SqlStmt,  "SELECT \
			COUNT(*), \
			SUM(CAST(TERMAMOUNT as FLOAT)),\
			SUM(CAST(TXNAMOUNT as FLOAT)) \
		FROM EZMMSBATCHTXNINFO WHERE RTRIM(MACHINEID) ='%s' AND TXNCODE LIKE '62%';", I_MachineId );
	}
	else
	{
		sprintf( SqlStmt,  "SELECT \
			COUNT(*), \
			SUM(RTRIM(TERMAMOUNT)),\
			SUM(RTRIM(TXNAMOUNT)) \
		FROM EZMMSBATCHTXNINFO WHERE RTRIM(MACHINEID) ='%s' AND TXNCODE LIKE '62%';", I_MachineId );
	}

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( "SqlStmt<%s>", SqlStmt);
		dptr->trace(  DEBUG_ERROR, "Error in Executing SqlStmt in getTotals [ %d ]", odbcret );
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_SLONG, &VoidCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(VoidCount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TermVoidAmount, sizeof(TermVoidAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(TermVoidAmount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, VoidAmount, sizeof(VoidAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace(  DEBUG_ERROR, "Error in Binding Column(VoidAmount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLFetch( hstmt );
    if( SQL_SUCCEEDED( odbcret ) )
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    }
    else if( odbcret == SQL_NO_DATA )
    {
    	dptr->trace(  DEBUG_ERROR, "SQL_NO_DATA" );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		VoidCount = 0;
		TermVoidCount = 0;
		memset( VoidAmount, 0, sizeof( VoidAmount ) );
		strcpy( VoidAmount, "0.00" );
		memset( TermVoidAmount, 0, sizeof( TermVoidAmount ) );
		strcpy( TermVoidAmount, "0.00" );
    }
    else
    {
    	dptr->trace(  DEBUG_ERROR, "Fetch Error [%d]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	if( VoidCount == 0 )
	{
		TermVoidCount = 0;
		memset( VoidAmount, 0, sizeof( VoidAmount ) );
		strcpy( VoidAmount, "0.00" );
		memset( TermVoidAmount, 0, sizeof( TermVoidAmount ) );
		strcpy( TermVoidAmount, "0.00" );
	}

	tot_ptr->SaleCount = SaleCount;
	tot_ptr->TermSaleCount = SaleCount;
	tot_ptr->VoidCount = VoidCount;
	tot_ptr->TermVoidCount = VoidCount;
	memset( tot_ptr->SaleAmount, 0, sizeof( tot_ptr->SaleAmount ) );
	strcpy( tot_ptr->SaleAmount, SaleAmount );
	memset( tot_ptr->TermSaleAmount, 0, sizeof( tot_ptr->TermSaleAmount ) );
	strcpy( tot_ptr->TermSaleAmount, TermSaleAmount );
	memset( tot_ptr->VoidAmount, 0, sizeof( tot_ptr->VoidAmount ) );
	strcpy( tot_ptr->VoidAmount, VoidAmount );
	memset( tot_ptr->TermVoidAmount, 0, sizeof( tot_ptr->TermVoidAmount ) );
	strcpy( tot_ptr->TermVoidAmount, TermVoidAmount );
	return 0;
}

int EzTMSDriverODBC :: updateTerminalBatchTxnInfo( const char *I_MachineId, const char *I_TMSTxnRefNum, const char *I_Amount, char I_MatchFlag, const char *I_MatchDesc )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZMMSBATCHTXNINFO SET \
    	TERMAMOUNT = '%s',\
    	MATCHFLAG = '%c',\
    	MATCHDESC = '%s'\
    WHERE RTRIM(MACHINEID) = '%s' AND TRIM(TXNREFNUM) = '%s';", I_Amount, I_MatchFlag, I_MatchDesc, I_MachineId, I_TMSTxnRefNum );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: readTerminalBatchInfo( const char *I_MachineId, struct EzTerminalBatchInfo *termbatchinfo_rec )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char BatchId[ 13 ];
	char InstId[ 13 ];
	char MachineId[ 33 ];
	char Termid[ 9 ];
	char MerchantId[ 16 ];
	char OpenDate[ 7 ];
	int OpenTime;
	char Source;
	int SaleCount;
	double SaleAmount;
	int VoidCount;
	double VoidAmount;
	int AuthCount;
	double AuthAmount;
	char tempdate[ 11 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
    	sprintf( SqlStmt,  "SELECT \
    			RTRIM(INSTID),\
    			RTRIM(BATCHID),\
    			RTRIM(TERMID),\
    			RTRIM(MERCHANTID),\
    			convert(varchar, OPENDATE, 4 ),\
    			OPENTIME,\
    			SOURCE,\
    			SALECOUNT,\
    			SALEAMOUNT,\
    			VOIDCOUNT,\
    			VOIDAMOUNT,\
    			AUTHCOUNT,\
    			AUTHAMOUNT \
    		FROM EZMMSBATCHINFO WHERE RTRIM(MACHINEID) ='%s';", I_MachineId );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readTerminalBatchInfo [ %d ]", odbcret );
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BatchId, sizeof(BatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BatchId) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, Termid, sizeof(Termid), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Termid) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, OpenDate, sizeof(OpenDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OpenDate) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_SLONG, &OpenTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(OpenTime) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &Source, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Source) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &SaleCount, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SaleCount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_DOUBLE, &SaleAmount, sizeof(double), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SaleAmount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }


    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &VoidCount, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(VoidCount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_DOUBLE, &VoidAmount, sizeof(double), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(VoidAmount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_SLONG, &AuthCount, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthCount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_DOUBLE, &AuthAmount, sizeof(double), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthAmount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

	memset( BatchId, 0, sizeof( BatchId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( Termid, 0, sizeof( Termid ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( OpenDate, 0, sizeof( OpenDate ) );

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {

    	strcpy( termbatchinfo_rec->InstId, InstId );
    	strcpy( termbatchinfo_rec->MachineId, I_MachineId );
    	strcpy( termbatchinfo_rec->BatchId, BatchId );
    	strcpy( termbatchinfo_rec->Termid, Termid );
    	strcpy( termbatchinfo_rec->MerchantId, MerchantId );
    	termbatchinfo_rec->OpenTime = OpenTime;
    	termbatchinfo_rec->Source = Source;
    	termbatchinfo_rec->SaleCount = SaleCount;
    	termbatchinfo_rec->SaleAmount = SaleAmount;
    	termbatchinfo_rec->VoidCount = VoidCount;
    	termbatchinfo_rec->VoidAmount = VoidAmount;
    	termbatchinfo_rec->AuthCount = AuthCount;
    	termbatchinfo_rec->AuthAmount = AuthAmount;
        if( !strcasecmp( DBType, SQLSERVER ) )
        {
        	memset( tempdate, 0, sizeof( tempdate ) );
        	getSwitchDateFmt( OpenDate, "DDMMYY", tempdate );
        	strcpy( termbatchinfo_rec->OpenDate, tempdate );
        }
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzTMSDriverODBC :: searchTerminalTxn( const char *I_TMSTxnRefNum, struct EzTxnMsg *txnmsg_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char BatchId[ 13 ];
	int TraceNo;
	char AuthNum[ 13 ];
	char RefNum[ 13 ];
	char TranDate[ 11 ];
	int TranTime;
	char LocalDate[ 11 ];
	int LocalTime;
	int AuthCode;
	char TxnAmount[ 21 ];
	char tempdate[ 11 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
    	sprintf( SqlStmt,  "SELECT \
			RTRIM(BATCHID),\
			TRACENO,\
			RTRIM(AUTHNUM),\
			RTRIM(REFNUM),\
			convert(varchar, TRANDATE, 4 ),\
			TRANTIME,\
			convert(varchar, LOCALDATE, 4 ),\
			LOCALTIME,\
			AUTHCODE,\
			RTRIM(TXNAMOUNT) \
    	FROM EZMMSBATCHTXNINFO WHERE RTRIM(TXNREFNUM)='%s';", I_TMSTxnRefNum );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in searchTerminalTxn [ %d ]", odbcret );
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, BatchId, sizeof(BatchId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BatchId) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &TraceNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TraceNo) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, AuthNum, sizeof(AuthNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthNum) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, RefNum, sizeof(RefNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RefNum) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TranDate, sizeof(TranDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TranDate) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_SLONG, &TranTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TranTime) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, LocalDate, sizeof(LocalDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LocalDate) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &LocalTime, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LocalTime) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &AuthCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthCode) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }


    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, TxnAmount, sizeof(TxnAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnAmount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

	memset( BatchId, 0, sizeof( BatchId ) );
	memset( AuthNum, 0, sizeof( AuthNum ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( TxnAmount, 0, sizeof( TxnAmount ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( LocalDate, 0, sizeof( LocalDate ) );

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	txnmsg_ptr->TraceNo = TraceNo;
    	strcpy( txnmsg_ptr->AuthNum, AuthNum );
    	strcpy( txnmsg_ptr->RefNum, RefNum );

    	txnmsg_ptr->TranTime = TranTime;
    	txnmsg_ptr->LocalTime = LocalTime;
    	txnmsg_ptr->AuthCode = AuthCode;
    	strcpy( txnmsg_ptr->Amount, TxnAmount );

    	if( !strcasecmp( DBType, SQLSERVER ) )
        {
        	memset( tempdate, 0, sizeof( tempdate ) );
        	getSwitchDateFmt( TranDate, "DDMMYY", tempdate );
        	txnmsg_ptr->TranDate = atoi(tempdate);
        }

    	if( !strcasecmp( DBType, SQLSERVER ) )
        {
        	memset( tempdate, 0, sizeof( tempdate ) );
        	getSwitchDateFmt( LocalDate, "DDMMYY", tempdate );
        	txnmsg_ptr->LocalDate = atoi(tempdate);
        }
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	dptr->trace("<%s>--<%d>", SqlStmt, odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzTMSDriverODBC :: insertTerminalBatchHist( struct EzTerminalBatchInfoHist *termbatchinfohist_rec )
{
    char SqlStmt[ 1024 ];
    char CloseDate[ 11 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( CloseDate, 0, sizeof( CloseDate ) );
		getMSSQLDateFmt( termbatchinfohist_rec->CloseDate, CloseDate );

		sprintf( SqlStmt, "INSERT INTO EZMMSBATCHHIST \
		( \
			BATCHID,\
			NEWBATCHID,\
			TERMBATCHID,\
			INSTID,\
			MACHINEID,\
			TERMID,\
			MERCHANTID,\
			CLOSEDATE,\
			CLOSETIME,\
			SOURCE,\
			MATCHFLAG,\
			HOSTSALECOUNT,\
			TERMSALECOUNT,\
			HOSTSALEAMOUNT,\
			TERMSALEAMOUNT,\
			HOSTVOIDCOUNT,\
			TERMVOIDCOUNT,\
			HOSTVOIDAMOUNT,\
			TERMVOIDAMOUNT,\
			HOSTAUTHCOUNT,\
			TERMAUTHCOUNT,\
			HOSTAUTHAMOUNT,\
			TERMAUTHAMOUNT\
		) \
		VALUES \
		( '%s', '%s', '%s', '%s', '%s', '%s', '%s', convert(varchar,'%s',105), %d, '%c', '%c', %d, %d, '%s', '%s', %d, %d, '%s', '%s', %d, %d, '%s', '%s');",
		termbatchinfohist_rec->BatchId,
		termbatchinfohist_rec->NewBatchId,
		termbatchinfohist_rec->TermBatchId,
		termbatchinfohist_rec->InstId,
		termbatchinfohist_rec->MachineId,
		termbatchinfohist_rec->Termid,
		termbatchinfohist_rec->MerchantId,
		CloseDate,
		termbatchinfohist_rec->CloseTime,
		termbatchinfohist_rec->Source,
		termbatchinfohist_rec->MatchFlag,
		termbatchinfohist_rec->HostSaleCount,
		termbatchinfohist_rec->TermSaleCount,
		termbatchinfohist_rec->HostSaleAmount,
		termbatchinfohist_rec->TermSaleAmount,
		termbatchinfohist_rec->HostVoidCount,
		termbatchinfohist_rec->TermVoidCount,
		termbatchinfohist_rec->HostVoidAmount,
		termbatchinfohist_rec->TermVoidAmount,
		termbatchinfohist_rec->HostAuthCount,
		termbatchinfohist_rec->TermAuthCount,
		termbatchinfohist_rec->HostAuthAmount,
		termbatchinfohist_rec->TermAuthAmount);
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: clearTerminalBatchInfo( const char *I_MachineId, const char *I_BatchId, const char *I_OpenDate, int I_OpenTime )
{
    char SqlStmt[ 1024 ];
    char OpenDate[ 11 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( OpenDate, 0, sizeof( OpenDate ) );
		getMSSQLDateFmt( I_OpenDate, OpenDate );

		sprintf( SqlStmt, "UPDATE EZMMSBATCHINFO SET \
			BATCHID = '%s',\
			OPENDATE = convert(varchar,'%s',105), \
			OPENTIME = %d,\
			SALECOUNT = 0,\
			SALEAMOUNT = 0,\
			VOIDCOUNT = 0,\
			VOIDAMOUNT = 0,\
			AUTHAMOUNT = 0,\
			AUTHCOUNT = 0\
		WHERE RTRIM(MACHINEID) ='%s';", I_BatchId, OpenDate, I_OpenTime, I_MachineId );
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: moveFromTerminalBatchTxnInfoToHist( const char *I_MachineId, const char *I_BatchId )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "INSERT INTO EZMMSBATCHTXNHIST SELECT * FROM EZMMSBATCHTXNINFO WHERE RTRIM(BATCHID) ='%s' AND RTRIM(MACHINEID) ='%s';", I_BatchId, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: updateTerminalBatchInTerminalInfo( const char *I_MachineId, const char *I_BatchId )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZMMS_TERMINALPROFILE SET BATCHID = '%s' WHERE RTRIM(MACHINE_ID) = '%s';", I_BatchId, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: deleteFromTerminalBatchTxnInfo( const char *I_MachineId, const char *I_BatchId )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "DELETE FROM EZMMSBATCHTXNINFO WHERE RTRIM(BATCHID) = '%s' AND RTRIM(MACHINEID) = '%s';", I_BatchId, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSDriverODBC :: readFromTerminalBatchTxnInfo( const char *I_MachineId, const char *I_BatchId, const char *I_TMSTxnRefNum, struct EzTxnMsg *txnmsg_ptr )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

	char Termid[ 9 ];
	char MerchantId[ 16 ];
	char StoreId[ 33 ];
	int MsgType;
	int TxnCode;
	char chn[ 20 ];
	char TermLoc[ 65 ];
	int TraceNo;
	char AuthNum[ 13 ];
	char RefNum[ 13 ];
	char TranDate[ 10 ];
	int TranTime;
	char LocalDate[ 10 ];
	int LocalTime;
	int RespCode;
	int AuthCode;
	int CurrencyCode;
	int MCC;
	char TxnAmount[ 21 ];
	char tempdate[ 11 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            dptr->trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    if( !strcasecmp( DBType, SQLSERVER ) )
    {
    	sprintf( SqlStmt,  "SELECT \
			RTRIM(TERMID),\
			RTRIM(MERCHANTID),\
			RTRIM(STOREID),\
    		MSGTYPE,\
			TXNCODE,\
			RTRIM(CHN),\
			RTRIM(TERMLOC),\
			TRACENO,\
			RTRIM(AUTHNUM),\
			RTRIM(REFNUM),\
			convert(varchar, TRANDATE, 4 ),\
			TRANTIME,\
			convert(varchar, LOCALDATE, 4 ),\
			LOCALTIME,\
			RESPCODE,\
			AUTHCODE,\
			CURRENCYCODE,\
			MCC,\
			RTRIM(TXNAMOUNT) \
		FROM EZMMSBATCHTXNINFO WHERE RTRIM(BATCHID)='%s' AND RTRIM(MACHINEID)='%s' AND RTRIM(TXNREFNUM)='%s';", I_BatchId, I_MachineId, I_TMSTxnRefNum );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in readFromTerminalBatchTxnInfo [ %d ]", odbcret );
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, Termid, sizeof(Termid), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(Termid) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, MerchantId, sizeof(MerchantId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MerchantId) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, StoreId, sizeof(StoreId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(StoreId) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &MsgType, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &TxnCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, chn, sizeof(chn), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(chn) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, TermLoc, sizeof(TermLoc), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TermLoc) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &TraceNo, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TraceNo) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_CHAR, AuthNum, sizeof(AuthNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthNum) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, RefNum, sizeof(RefNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RefNum) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, TranDate, sizeof(TranDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TranDate) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_SLONG, &TranTime, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TranTime) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, LocalDate, sizeof(LocalDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LocalDate) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_SLONG, &LocalTime, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(LocalTime) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &RespCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &AuthCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthCode) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_SLONG, &CurrencyCode, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(CurrencyCode) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_SLONG, &MCC, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(MCC) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_CHAR, TxnAmount, sizeof(TxnAmount), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnAmount) in EZMMSBATCHTXNINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

	memset( Termid, 0, sizeof( Termid ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( chn, 0, sizeof( chn ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( AuthNum, 0, sizeof( AuthNum ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( LocalDate, 0, sizeof( LocalDate ) );
	memset( TxnAmount, 0, sizeof( TxnAmount ) );

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	strcpy( txnmsg_ptr->TerminalId, Termid );
    	strcpy( txnmsg_ptr->AcceptorId, MerchantId );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzTMSDriverODBC :: updateTerminalBatchTxnAmount( const char *I_MachineId, const char *I_BatchId, const char *I_TMSTxnRefNum, const char *I_OldAmount)
{
	return 1;
}

int EzTMSDriverODBC :: insertTerminalBatchUpload( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum, char I_MatchFlag, const char *I_MatchDesc )
{
    char SqlStmt[ 1024 ];
    char I_TranDate[ 11 ], I_LocalDate[ 11 ];
    char TempDate[ 11 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( I_TranDate, 0, sizeof( I_TranDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->TranDate );
		getMSSQLDateFmt( TempDate, I_TranDate );

		memset( I_LocalDate, 0, sizeof( I_LocalDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->LocalDate );
		getMSSQLDateFmt( TempDate, I_LocalDate );

		sprintf( SqlStmt, "INSERT INTO EZMMSBATCHUPLOAD \
		( \
			INSTID,\
			MACHINEID,\
			TERMID,\
			MERCHANTID,\
			BATCHID,\
			TXNREFNUM,\
			MSGTYPE,\
			TXNCODE,\
			CHN,\
			TERMLOC,\
			TRACENO,\
			AUTHNUM,\
			REFNUM,\
			TRANDATE,\
			TRANTIME,\
			LOCALDATE,\
			LOCALTIME,\
			RESPCODE,\
			AUTHCODE,\
			CURRENCYCODE,\
			MCC,\
			TXNAMOUNT,\
			MATCHFLAG,\
			MATCHDESC\
		) \
		VALUES \
		( '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%s', '%s', '%d', '%s', '%s', convert(varchar,'%s',105), '%d', convert(varchar,'%s',105), '%d', '%d', '%d', '%d', '%d', '%s', '%c', '%s');",
		txnmsg->AcquirerInst,
		I_MachineId,
		txnmsg->TerminalId,
		txnmsg->AcceptorId,
		txnmsg->BatchId,
		I_TMSTxnRefNum,
		txnmsg->MsgType,
		txnmsg->TxnCode,
		txnmsg->chn,
		txnmsg->TerminalLocation,
		txnmsg->TraceNo,
		txnmsg->AuthNum,
		txnmsg->RefNum,
		I_TranDate,
		txnmsg->TranTime,
		I_LocalDate,
		txnmsg->LocalTime,
		txnmsg->RespCode,
		txnmsg->AuthCode,
		txnmsg->AcqCurrencyCode,
		txnmsg->MerchantType,
		txnmsg->Amount,
		I_MatchFlag,
		I_MatchDesc);
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}
