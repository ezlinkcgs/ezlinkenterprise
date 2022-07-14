/*
 * ezagenttmsdriverodbc.cpp
 *
 *  Created on: Jun 20, 2021
 *      Author: C.Hariharan
 */

#include <ezagenttms/ezagenttmsdriverodbc.h>

int EzTMSDriverODBC :: initEzTMSDriverODBC( const char *TaskName, EzDebugUtil *dptr )
{
	this->dptr = dptr;
	if( initODBCUtil( TaskName, dptr, "EZAGENTMMS" ) < 0 )
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

int EzTMSDriverODBC :: readTxnAllowed( const char *I_InstId, const char *I_TerminalType, char *I_BinList, char *I_TxnList )
{
    SQLHSTMT hstmt;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

		char InstId[ 13 ];
		char BinList[ 129 ];
		char TxnList[ 129 ];
		char TerminalType[ 17 ];

	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	
	memset( TerminalType, 0, sizeof( TerminalType ) );
	strcpy( TerminalType, I_TerminalType );
	memset( BinList, 0, sizeof( BinList ) );
	memset( TxnList, 0, sizeof( TxnList ) );

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
    			TRIM(BINLIST), \
				TRIM(TXNLIST) \
    		FROM  EZMMS_TERMINAL_RESTRICT WHERE TRIM(INST_ID) = '%s' AND TRIM(TERMINALTYPE) = '%s' ; ",I_InstId, I_TerminalType );
    }

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
		dptr->trace( DEBUG_ERROR, "Error in Executing SqlStmt in EZMMS_TERMINAL_RESTRICT [ %d ]", odbcret );
		dptr->trace("<%s>", SqlStmt);
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, InstId, sizeof(InstId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(InstId) in EZMMS_TERMINAL_RESTRICT [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, BinList, sizeof(BinList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(BinList) in EZMMS_TERMINAL_RESTRICT [ %d ]", odbcret );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TxnList, sizeof(TxnList), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TxnList) in EZMMS_TERMINAL_RESTRICT [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, TerminalType, sizeof(TerminalType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Binding Column(TerminalType) in EZMMS_TERMINAL_RESTRICT [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }


    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {

    	strcpy( I_BinList, BinList );
		strcpy( I_TxnList, TxnList );
	
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}
