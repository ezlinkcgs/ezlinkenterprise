/*
 * eztmsloggerodbc.cpp
 *
 *  Created on: Sep 9, 2013
 *      Author: mohanraj
 */

#include <eztms/eztmsloggerodbc.h>

int EzTMSLoggerODBC :: initEzTMSLoggerODBC( const char *TaskName, EzDebugUtil *dptr )
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

int EzTMSLoggerODBC :: ConnectDB()
{
	if( DBConnect( ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return -1;
	}
	return 1;
}

int EzTMSLoggerODBC :: insertTerminalMaster( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum, const char *I_OpType )
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
		if( txnmsg->LocalDate == 0 )
			txnmsg->LocalDate = txnmsg->TranDate;
		memset( I_LocalDate, 0, sizeof( I_LocalDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->LocalDate );
		getMSSQLDateFmt( TempDate, I_LocalDate );

		sprintf( SqlStmt, "INSERT INTO EZMMS_TRANSACTION \
		( \
			INSTID,\
			MACHINEID,\
			TERMID,\
			MERCHANTID,\
			DEVICETYPE,\
			BATCHID,\
			CARDSCHEME,\
			TXNREFNUM,\
			MSGTYPE,\
			TXNCODE,\
			TXNTYPE,\
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
			TXNCURRENCY,\
			TXNCONVRATE,\
			TXNCONVDATE,\
			MCC,\
			TXNAMOUNT,\
			TXNSTATUS\
		) \
		VALUES \
		( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, '%06d', '%s', '%s', '%s', %d, '%s', '%s', convert(varchar,'%s',105), %d, convert(varchar,'%s',105), %d, %d, %d, '%03d', '%s',  convert(varchar,'%s',105), %d, '%s', '%c' );",
		txnmsg->AcquirerInst,
		I_MachineId,
		txnmsg->TerminalId,
		txnmsg->AcceptorId,
		txnmsg->DeviceType,
		txnmsg->BatchId,
		"NA",
		I_TMSTxnRefNum,
		txnmsg->MsgType,
		txnmsg->TxnCode,
		I_OpType,
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
		"1.0",
		I_TranDate,
		txnmsg->MerchantType,
		txnmsg->Amount,
		'T');
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSLoggerODBC :: insertTerminalTxnLog( const char *I_MachineId, struct EzTxnMsg *txnmsg )
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

		if( txnmsg->LocalDate == 0 )
			txnmsg->LocalDate = txnmsg->TranDate;

		memset( I_LocalDate, 0, sizeof( I_LocalDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->LocalDate );
		getMSSQLDateFmt( TempDate, I_LocalDate );

		sprintf( SqlStmt, "INSERT INTO EZMMS_TRANSACTIONLOG \
		( \
			INSTID,\
			MACHINEID,\
			TERMID,\
			MERCHANTID,\
			DEVICETYPE,\
			BATCHID,\
			CARDSCHEME,\
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
			TXNCURRENCY,\
			MCC,\
			TXNAMOUNT\
		) \
		VALUES \
		( '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, '%06d', '%s', '%s', %d, '%s', '%s', convert(varchar,'%s',105), %d, convert(varchar,'%s',105), %d, %d, %d, '%03d', %d, '%s' );",
		txnmsg->AcquirerInst,
		I_MachineId,
		txnmsg->TerminalId,
		txnmsg->AcceptorId,
		txnmsg->DeviceType,
		txnmsg->BatchId,
		"NA",
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
		txnmsg->Amount);
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSLoggerODBC :: insertTerminalBatchTxnInfo( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum )
{
    char SqlStmt[ 1024 ];
    char I_TranDate[ 11 ], I_LocalDate[ 11 ];
    char TempDate[ 11 ];
    /*char tempamt[20];
    memset(tempamt,0,sizeof(tempamt));
    strcpy(tempamt,txnmsg->Amount);
    memset(txnmsg->Amount,0,sizeof(txnmsg->Amount));
    strncpy(txnmsg->Amount,tempamt,strlen(tempamt)-1);  
    */
    memset( SqlStmt, 0, sizeof( SqlStmt ) );
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( I_TranDate, 0, sizeof( I_TranDate ) );
		memset( TempDate, 0, sizeof( TempDate ) );
		sprintf( TempDate, "%06d", txnmsg->TranDate );
		getMSSQLDateFmt( TempDate, I_TranDate );

		if( txnmsg->LocalDate == 0 )
			txnmsg->LocalDate = txnmsg->TranDate;

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
		'M',
		"MATCHED");
	}

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSLoggerODBC :: readTerminalBatchInfo( const char *I_MachineId, struct EzTerminalBatchInfo *terminalbatchinfo_rec )
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

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &SaleCount, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SaleCount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_DOUBLE, &SaleAmount, sizeof(double), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(SaleAmount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }


    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &VoidCount, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(VoidCount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_DOUBLE, &VoidAmount, sizeof(double), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(VoidAmount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &AuthCount, sizeof(long), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(AuthCount) in EZMMSBATCHINFO [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_DOUBLE, &AuthAmount, sizeof(double), &Len );
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

    	strcpy( terminalbatchinfo_rec->InstId, InstId );
    	strcpy( terminalbatchinfo_rec->MachineId, I_MachineId );
    	strcpy( terminalbatchinfo_rec->BatchId, BatchId );
    	strcpy( terminalbatchinfo_rec->Termid, Termid );
    	strcpy( terminalbatchinfo_rec->MerchantId, MerchantId );
    	terminalbatchinfo_rec->OpenTime = OpenTime;
    	//terminalbatchinfo_rec->Source = Source;
    	terminalbatchinfo_rec->SaleCount = SaleCount;
    	terminalbatchinfo_rec->SaleAmount = SaleAmount;
    	terminalbatchinfo_rec->VoidCount = VoidCount;
    	terminalbatchinfo_rec->VoidAmount = VoidAmount;
    	terminalbatchinfo_rec->AuthCount = AuthCount;
    	terminalbatchinfo_rec->AuthAmount = AuthAmount;
        if( !strcasecmp( DBType, SQLSERVER ) )
        {
        	memset( tempdate, 0, sizeof( tempdate ) );
        	getSwitchDateFmt( OpenDate, "DDMMYY", tempdate );
        	strcpy( terminalbatchinfo_rec->OpenDate, tempdate );
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

int EzTMSLoggerODBC :: updateSaleTxn( const char *I_MachineId, double I_TxnAmount, int I_TxnCount )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZMMSBATCHINFO SET SALECOUNT = %d, SALEAMOUNT = %f WHERE RTRIM(MACHINEID) = '%s';", I_TxnCount, I_TxnAmount, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}

int EzTMSLoggerODBC :: updateVoidTxn( const char *I_MachineId, double I_TxnAmount, int I_TxnCount )
{
    char SqlStmt[ 1024 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZMMSBATCHINFO SET VOIDCOUNT = %d, VOIDAMOUNT = %f WHERE RTRIM(MACHINEID) = '%s';", I_TxnCount, I_TxnAmount, I_MachineId );

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;

	return 0;
}
