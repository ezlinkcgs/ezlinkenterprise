#include <ezlink/eztxnlogger.h>

void EzTxnLogger :: initTxnLogger( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztxnlogger.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^eztxnlogger Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	SetDebug( );

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( EZTXNLOGGERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating eztxnlogger Channel" );
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil..." );
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting Database" );
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnmsgvalidator.initTxnMsgValidator( this, "TXNLOG" ) < 0 )
	{
		trace( "Error in Initializing TxnMsgValidator..." );
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnmsgvalidator.LoadTxnMsgDef() < 0 )
	{
		trace( "Error in Loading TxnMsgDef..." );
		trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	composeSqlString();

	TaskInit();
	initEzSigUtil( this );
}


void EzTxnLogger :: composeSqlString()
{
	memset( SQLString, 0, sizeof( SQLString ) );

	sprintf( SQLString, "INSERT INTO EZTXNLOG (" );
	strcat( SQLString, "TXNREFNUM," );
	strcat( SQLString, "DEVICETYPE," );
	strcat( SQLString, "MSGTYPE," );
	strcat( SQLString, "ORGMSGTYPE," );
	strcat( SQLString, "TXNCODE," );
	strcat( SQLString, "TERMINALID," );
	strcat( SQLString, "TERMLOC," );
	strcat( SQLString, "TRACENO," );
	strcat( SQLString, "ORGTRACENO," );
	strcat( SQLString, "TRANDATE," );
	strcat( SQLString, "TRANTIME," );
	strcat( SQLString, "ORGTRANDATE," );
	strcat( SQLString, "ORGTRANTIME," );
	strcat( SQLString, "LOCALDATE," );
	strcat( SQLString, "LOCALTIME," );
	strcat( SQLString, "RESPCODE," );
	strcat( SQLString, "REVCODE," );
	strcat( SQLString, "REASONCODE," );
	strcat( SQLString, "AUTHCODE," );
	strcat( SQLString, "CAPTUREDATE," );
	strcat( SQLString, "CAPTURETIME," );
	strcat( SQLString, "SETTLEMENTDATE," );
	strcat( SQLString, "BUSINESSDATE," );
	strcat( SQLString, "ACQCURRENCYCODE," );
	strcat( SQLString, "ACQCONVRATE," );
	strcat( SQLString, "ACQCONVDATE," );
	strcat( SQLString, "ISSCURRENCYCODE," );
	strcat( SQLString, "ISSCONVRATE," );
	strcat( SQLString, "ISSCONVDATE," );
	strcat( SQLString, "SETTCURRENCYCODE," );
	strcat( SQLString, "SETTCONVRATE," );
	strcat( SQLString, "SETTCONVDATE," );
	strcat( SQLString, "MERCHANTTYPE," );
	strcat( SQLString, "POSENTRYCODE," );
	strcat( SQLString, "POSCONDITIONCODE," );
	strcat( SQLString, "POSCAPCODE," );
	strcat( SQLString, "POSPINCAPCODE," );
	strcat( SQLString, "CHN," );
	strcat( SQLString, "TCHN," );
	strcat( SQLString, "ACQBRANCHCODE," );
	strcat( SQLString, "ISSBRANCHCODE," );
	strcat( SQLString, "TXFBRANCHCODE," );
	strcat( SQLString, "FORWARDBRANCHCODE," );
	strcat( SQLString, "FROMACCTSUBTYPE," );
	strcat( SQLString, "TOACCTSUBTYPE," );
	strcat( SQLString, "AVAILBALANCE," );
	strcat( SQLString, "LEDGERBALANCE," );
	strcat( SQLString, "AMOUNT," );
	strcat( SQLString, "TXNFEE," );
	strcat( SQLString, "DISPAMOUNT," );
	strcat( SQLString, "FROMACCOUNT," );
	strcat( SQLString, "TOACCOUNT," );
	strcat( SQLString, "REFNUM," );
	strcat( SQLString, "AUTHNUM," );
	strcat( SQLString, "BATCHID," );
	strcat( SQLString, "ACCEPTORID," );
	strcat( SQLString, "ACCEPTORNAME," );
	strcat( SQLString, "ACQUIRERINST," );
	strcat( SQLString, "ISSUERINST," );
	strcat( SQLString, "FORWARDINST," );
	strcat( SQLString, "TXFINST," );
	strcat( SQLString, "SETTINST," );
	strcat( SQLString, "NETWORKID," );
	strcat( SQLString, "ACQNETWORKID," );
	strcat( SQLString, "ISSUERNETWORKID," );
	strcat( SQLString, "FWDNETWORKID," );
	strcat( SQLString, "TXFNETWORKID," );
	strcat( SQLString, "SETTNETWORKID," );
	strcat( SQLString, "RSVFLD1," );
	strcat( SQLString, "RSVFLD2," );
	strcat( SQLString, "RSVFLD3," );
	strcat( SQLString, "RSVFLD4," );
	strcat( SQLString, "RSVFLD5," );
	strcat( SQLString, "RSVFLD6," );
	strcat( SQLString, "ORGCHANNEL," );
	strcat( SQLString, "ORGPORT," );
	strcat( SQLString, "SRCCHANNEL," );
	strcat( SQLString, "DESTCHANNEL," );
	strcat( SQLString, "SRCPORT," );
	strcat( SQLString, "DESTPORT," );
	strcat( SQLString, "REFSEQNO" );
	strcat( SQLString, ") VALUES (" );
	trace( "SQLString[%s]", SQLString );
}

void EzTxnLogger :: dumpTxnMsg( struct EzTxnMsg *txnmsg, const char *TxnRefNum, const char *SrcChannelName, const char *DestChannelName )
{
	trace("************************************************");
	trace( "SrcChannelName[ %s ]", SrcChannelName );
	trace( "DestChannelName[ %s ]", DestChannelName );
	trace( "TxnRefNum [ %s ]", TxnRefNum );
	trace( "DeviceType [ %s ]", txnmsg->DeviceType );
	trace(" MsgType[ %d ] ", txnmsg->MsgType );
	trace(" OrgMsgType[ %d ] ", txnmsg->OrgMsgType );
	trace(" TxnCode[ %d ] ", txnmsg->TxnCode );
	trace(" TerminalId[ %s ] ", txnmsg->TerminalId );
	trace(" TerminalLocation[ %s ] ", txnmsg->TerminalLocation );
	trace(" TraceNo[ %d ] ", txnmsg->TraceNo );
	trace(" OrgTraceNo[ %d ] ", txnmsg->OrgTraceNo );
	trace(" TranDate[ %d ] ", txnmsg->TranDate );
	trace(" TranTime[ %d ] ", txnmsg->TranTime );
	trace(" OrgTranDate[ %d ] ", txnmsg->OrgTranDate );
	trace(" OrgTranTime[ %d ] ", txnmsg->OrgTranTime );
	trace(" LocalDate[ %d ] ", txnmsg->LocalDate );
	trace(" LocalTime[ %d ] ", txnmsg->LocalTime );
	trace(" RespCode[ %d ] ", txnmsg->RespCode );
	trace(" RevCode[ %d ] ", txnmsg->RevCode );
	trace(" ReasonCode[ %d ] ", txnmsg->ReasonCode );
	trace(" AuthCode[ %d ] ", txnmsg->AuthCode );
	trace(" CaptureDate[ %d ] ", txnmsg->CaptureDate );
	trace(" CaptureTime[ %d ] ", txnmsg->CaptureTime );
	trace(" SettlementDate[ %d ] ", txnmsg->SettlementDate );
	trace(" BusinessDate[ %d ] ", txnmsg->BusinessDate );
	trace(" AcqCurrencyCode[ %d ] ", txnmsg->AcqCurrencyCode );
	trace(" IssCurrencyCode[ %d ] ", txnmsg->IssCurrencyCode );
	trace(" SettCurrencyCode[ %d ] ", txnmsg->SettCurrencyCode );
	trace(" AcqConvRate[ %d ] ", txnmsg->AcqConvRate );
	trace(" AcqConvDate[ %d ] ", txnmsg->AcqConvDate );
	trace(" IssConvRate[ %d ] ", txnmsg->IssConvRate );
	trace(" IssConvDate[ %d ] ", txnmsg->IssConvDate );
	trace(" SettConvRate[ %d ] ", txnmsg->SettConvRate );
	trace(" SettConvDate[ %d ] ", txnmsg->SettConvDate );
	trace(" PosEntryCode[ %d ] ", txnmsg->PosEntryCode );
	trace(" PosConditionCode[ %d ] ", txnmsg->PosConditionCode );
	trace(" PosCapCode[ %d ] ", txnmsg->PosCapCode );
	trace(" PosPinCapCode[ %d ] ", txnmsg->PosPinCapCode );
	trace(" AvailBalanceFlg[ %c ]", txnmsg->AvailBalanceFlg );
	trace(" PinVerFlg[ %c ]", txnmsg->PinVerFlg );
	trace(" AuthFlg[ %c ]", txnmsg->AuthFlg );
	trace(" CheckCardExpiry[ %c ]", txnmsg->CheckCardExpiry );
	trace(" CheckServiceCode[ %c ]", txnmsg->CheckServiceCode );
	trace(" CheckCVV[ %c ]", txnmsg->CheckCVV );
	trace(" MerchantType[ %d ] ", txnmsg->MerchantType );
	trace(" chn[ %s ]", txnmsg->m_chn );
	trace(" AcqBranchCode[ %s ]", txnmsg->AcqBranchCode );
	trace(" TxfBranchCode[ %s ]", txnmsg->TxfBranchCode );
	trace(" IssBranchCode[ %s ] ", txnmsg->IssBranchCode );
	trace(" ForwardBranchCode[ %s ] ", txnmsg->ForwardBranchCode );
	trace(" FromAcctSubType[ %s ]", txnmsg->FromAcctSubType );
	trace(" ToAcctSubType[ %s ]", txnmsg->ToAcctSubType );
	trace(" Amount[ %s ]", txnmsg->Amount );
	trace(" DispAmount[ %s ]", txnmsg->DispAmount );
	trace(" TxnFee[ %s ] ", txnmsg->TxnFee );
	trace(" FromAccount[ %s ]", txnmsg->FromAccount );
	trace(" ToAccount[ %s ]", txnmsg->ToAccount );
	trace(" AvailBalance[ %s ]", txnmsg->AvailBalance );
	trace(" LedgerBalance[ %s ]", txnmsg->LedgerBalance );
	trace(" RefNum[ %s ]", txnmsg->RefNum );
	trace(" AuthNum[ %s ]", txnmsg->AuthNum );
	trace(" PINBlock[ %s ]", txnmsg->PINBlock );
	trace(" NewPINBlock[ %s ]", txnmsg->NewPINBlock );
	trace(" PinKey[ %s ]", txnmsg->PinKey );
	trace(" Keylen[ %d ]", txnmsg->Keylen );
	trace(" AcceptorName[ %s ]", txnmsg->AcceptorName );
	trace(" AcquirerInst[ %s ]", txnmsg->AcquirerInst );
	trace(" IssuerInst[ %s ]", txnmsg->IssuerInst );
	trace(" ForwardInst[ %s ]", txnmsg->ForwardInst );
	trace(" TxfInst[ %s ]", txnmsg->TxfInst );
	trace(" SettInst[ %s ]", txnmsg->SettInst );
	trace(" NetworkId[ %s ]", txnmsg->NetworkId );
	trace(" AcqNetworkId[ %s ]", txnmsg->AcqNetworkId );
	trace(" IssuerNetworkId[ %s ]", txnmsg->IssuerNetworkId );
	trace(" FwdNetworkId[ %s ]", txnmsg->FwdNetworkId );
	trace(" TxfNetworkId[ %s ]", txnmsg->TxfNetworkId );
	trace(" SettNetworkId[ %s ]", txnmsg->SettNetworkId );
	trace(" NetCode[ %d ]", txnmsg->NetCode );
	trace(" SecurityId[ %s ]", txnmsg->SecurityId );
	trace(" RsvFld1[ %s ]", txnmsg->RsvFld1 );
	trace(" RsvFld2[ %s ]", txnmsg->RsvFld2 );
	trace(" RsvFld3[ %s ]", txnmsg->RsvFld3 );
	trace(" RsvFld4[ %s ]", txnmsg->RsvFld4 );
	trace(" RsvFld5[ %s ]", txnmsg->RsvFld5 );
	trace(" RsvFld6[ %s ]", txnmsg->RsvFld6 );
	trace(" SrcChannel[ %s ]", txnmsg->SrcChannel );
	trace(" SrcPort[ %s ]", txnmsg->SrcPort );
	trace(" OrgChannel[ %s ]", txnmsg->OrgChannel );
	trace(" OrgPort[ %s ]", txnmsg->OrgPort );
	trace(" DestPort[ %s ]", txnmsg->DestPort );
	trace(" RespFile[ %s ]", txnmsg->RespFile );
	trace("************************************************");
}

void EzTxnLogger :: composeInsertQuery( const char *TxnRefNum, const char *SrcChannelName, const char *DestChannelName, short RefSeqNo, struct EzTxnMsg *txnmsg, char *SQLQuery )
{
	char hTranDate[ 10 ];
	char hOrgTranDate[ 10 ];
	char hLocalDate[ 10 ];
	char hCaptureDate[ 10 ];
	char hSettlementDate[ 10 ];
	char hBusinessDate[ 10 ];
	char hAcqConvDate[ 10 ];
	char hIssConvDate[ 10 ];
	char hSettConvDate[ 10 ];
	char Input_date[ 10 ];

	if( txnmsg->OrgTranDate == 0 )
		txnmsg->OrgTranDate = txnmsg->TranDate;
	if( txnmsg->LocalDate == 0 )
		txnmsg->LocalDate = txnmsg->TranDate;
	if( txnmsg->CaptureDate == 0 )
		txnmsg->CaptureDate = txnmsg->TranDate;
	if( txnmsg->SettlementDate == 0 )
		txnmsg->SettlementDate = txnmsg->TranDate;
	if( txnmsg->BusinessDate == 0 )
		txnmsg->BusinessDate = txnmsg->TranDate;
	if( txnmsg->AcqConvDate == 0 )
		txnmsg->AcqConvDate = txnmsg->TranDate;
	if( txnmsg->IssConvDate == 0 )
		txnmsg->IssConvDate = txnmsg->TranDate;
	if( txnmsg->SettConvDate == 0 )
		txnmsg->SettConvDate = txnmsg->TranDate;

	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->TranDate);
		memset( hTranDate, 0, sizeof(hTranDate) );
		getMSSQLDateFmt( Input_date,  hTranDate);

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->OrgTranDate );
		memset( hOrgTranDate, 0, sizeof(hOrgTranDate ) );
		getMSSQLDateFmt( Input_date, hOrgTranDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->LocalDate );
		memset( hLocalDate, 0, sizeof( hLocalDate) );
		getMSSQLDateFmt( Input_date, hLocalDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->CaptureDate );
		memset( hCaptureDate, 0, sizeof( hCaptureDate) );
		getMSSQLDateFmt( Input_date, hCaptureDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->SettlementDate );
		memset( hSettlementDate, 0, sizeof( hSettlementDate ) );
		getMSSQLDateFmt( Input_date, hSettlementDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->BusinessDate );
		memset( hBusinessDate, 0, sizeof( hBusinessDate ) );
		getMSSQLDateFmt( Input_date, hBusinessDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->IssConvDate );
		memset( hIssConvDate, 0, sizeof( hIssConvDate ) );
		getMSSQLDateFmt( Input_date, hIssConvDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->AcqConvDate );
		memset( hAcqConvDate, 0, sizeof( hAcqConvDate ) );
		getMSSQLDateFmt( Input_date, hAcqConvDate );

		memset( Input_date, 0, sizeof( Input_date ) );
		sprintf( Input_date, "%06d", txnmsg->SettConvDate );
		memset( hSettConvDate, 0, sizeof( hSettConvDate ) );
		getMSSQLDateFmt( Input_date, hSettConvDate );
	}

	strcpy( SQLQuery, SQLString );

	//TXNREFNUM
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", TxnRefNum );

	//TXNREFNUM
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->DeviceType );

	//MSGTYPE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->MsgType );

	//ORGMSGTYPE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->OrgMsgType );

	//TXNCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->TxnCode );

	//TERMINALID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->TerminalId );

	//TERMLOC
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->TerminalLocation );

	//TRACENO
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->TraceNo );

	//ORGTRACENO
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->OrgTraceNo );

	//TRANDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hTranDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->TranDate );

	//TRANTIME
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->TranTime );

	//ORGTRANDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hOrgTranDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->OrgTranDate );

	//ORGTRANTIME
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->OrgTranTime );

	//LOCALDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hLocalDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->LocalDate );

	//LOCALTIME
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->LocalTime );

	//RESPCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->RespCode );

	//REVCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->RevCode );

	//REASONCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->ReasonCode );

	//AUTHCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->AuthCode );

	//CAPTUREDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hCaptureDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->CaptureDate );

	//CAPTURETIME
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->CaptureTime );

	//SETTLEMENTDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hSettlementDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->SettlementDate );

	//BUSINESSDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hBusinessDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->BusinessDate );


	//ACQCURRENCYCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->AcqCurrencyCode );

	//ACQCONVRATE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AcqConvRate );

	//ACQCONVDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hAcqConvDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->AcqConvDate );

	//ISSCURRENCYCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->IssCurrencyCode );

	//ISSCONVRATE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->IssConvRate );

	//ISSCONVDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hIssConvDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->IssConvDate );

	//SETTCURRENCYCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->SettCurrencyCode );

	//SETTCONVRATE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->SettConvRate );

	//SETTCONVDATE
	if( !strcasecmp( DBType, SQLSERVER ) )
	{
		sprintf( SQLQuery + strlen( SQLQuery ), "convert(varchar,'%s',105),", hSettConvDate );
	}
	else
		sprintf( SQLQuery + strlen( SQLQuery ), "to_date('%06d', 'dd-mm-yy'),", txnmsg->SettConvDate );


	//MERCHANTTYPE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->MerchantType );

	//POSENTRYCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->PosEntryCode );

	//POSCONDITIONCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->PosConditionCode );

	//POSCAPCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->PosCapCode );

	//POSPINCAPCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", txnmsg->PosPinCapCode );

	//CHN
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->m_chn );

	//TCHN
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->t_chn );

	//ACQBRANCHCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AcqBranchCode );

	//ISSBRANCHCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->IssBranchCode );

	//TXFBRANCHCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->TxfBranchCode );

	//FORWARDBRANCHCODE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->ForwardBranchCode );

	//FROMACCTSUBTYPE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->FromAcctSubType );

	//TOACCTSUBTYPE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->ToAcctSubType );

	//AVAILBALANCE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AvailBalance );

	//LEDGERBALANCE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->LedgerBalance );

	//AMOUNT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->Amount );

	//TXNFEE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->TxnFee );

	//DISPAMOUNT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->DispAmount );

	//FROMACCOUNT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->FromAccount );

	//TOACCOUNT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->ToAccount );

	//REFNUM
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RefNum );

	//AUTHNUM
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AuthNum );

	//BATCHID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->BatchId );

	//ACCEPTORID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AcceptorId );

	//ACCEPTORNAME
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AcceptorName );

	//ACQUIRERINST
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AcquirerInst );

	//ISSUERINST
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->IssuerInst );

	//FORWARDINST
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->ForwardInst );

	//TXFINST
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->TxfInst );

	//SETTINST
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->SettInst );

	//NETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->NetworkId );

	//ACQNETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->AcqNetworkId );

	//ISSUERNETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->IssuerNetworkId );

	//FWDNETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->FwdNetworkId );

	//TXFNETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->TxfNetworkId );

	//SETTNETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->SettNetworkId );

	//RSVFLD1
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RsvFld1 );

	//RSVFLD2
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RsvFld2 );

	//RSVFLD3
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RsvFld3 );

	//RSVFLD4
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RsvFld4 );

	//RSVFLD5
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RsvFld5 );

	//RSVFLD6
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->RsvFld6 );

	//ORGCHANNEL
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->OrgChannel );

	//ORGPORT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->OrgPort );

	//SRCCHANNEL
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", SrcChannelName );

	//DESTCHANNEL
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", DestChannelName );

	//SRCPORT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->SrcPort );

	//DESTPORT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", txnmsg->DestPort );

	//REFSEQNO
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d'", RefSeqNo );

	strcat( SQLQuery, ");");
}

void EzTxnLogger :: insertToFile( struct EzTxnMsg *txnmsg, const char *TxnRefNum, const char *SrcChannelName, const char *DestChannelName, short RefSeqNo )
{
	char FileName[ 200 ], SQLQuery[ MAX_INSERT_QUERY_SIZE + 1 ];

	FILE *fptr;
	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s/%06d_%d.TXNLOG", getenv( "EZDIR_HOME" ), "inf", "txnlog", ezdatetimeutil.getSysDate(), getpid() );
	fptr = fopen( FileName, "a" );
	if( fptr == NULL )
	{
		trace( "Error in Opening File[%s] ...SysErr[%s] ErrNo[%d]", FileName, strerror( errno ), errno );
		return;
	}
	memset( SQLQuery, 0, sizeof( SQLQuery ) );
	composeInsertQuery( TxnRefNum, SrcChannelName, DestChannelName, RefSeqNo, txnmsg, SQLQuery );
	fprintf( fptr, "%s\n", SQLQuery );
	fclose( fptr );
}

void EzTxnLogger :: serviceRequest()
{
	struct EzTxnLogMsg txnlogmsg;
	int MsgSize;

	struct EzTxnLogQMsg eztxnlogqmsg;
	while( 1 )
	{
		dbUtilClose();

		trace( "EzTxnMgr Waiting For Request....");
		memset( &txnlogmsg, 0, sizeof( struct EzTxnLogMsg ) );
		if( ReadMessage( ( char * ) &txnlogmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message From EzTxnLogger Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			sleep( 1 );
			continue;
		}
		dbUtilConnect();

		trace( DEBUG_TEST, "Message Received From Channel[%s]", GetLastSenderChannelName() );

		if( eztxnmsgvalidator.validateMsg( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName, txnlogmsg.RefSeqNo ) < 0 )
		{
			trace( DEBUG_ERROR, "Message Validation Failed...." );
		}

		switch( txnlogmsg.CommandCode )
		{
			case 'I':
				trace( DEBUG_NORMAL, "Received Insert TxnLog Message from NotificationId[%d]", txnlogmsg.NotificationId );
				SqlErr = insertEzTxnLog( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName, txnlogmsg.RefSeqNo );
				if( EZLINK_ORA_CONNECT_ERR( SqlErr ) )
				{
					if( DBConnect() < 0 )
					{
						trace( "Error in Connecting with Switch Database...." );
						insertToFile( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName, txnlogmsg.RefSeqNo );
					}
					else
					{
						SqlErr = insertEzTxnLog( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName, txnlogmsg.RefSeqNo );
						if( SqlErr != 0 )
						{
							trace( DEBUG_ERROR, "Error in inserting EZTXNLOG Table SqlErr[ %05d ]", SqlErr );
							insertToFile( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName, txnlogmsg.RefSeqNo );
						}
					}
				}
				else if( SqlErr != 0 )
				{
					trace( DEBUG_ERROR, "Error in inserting EZTXNLOG Table SqlErr[ %05d ]", SqlErr );
					insertToFile( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName, txnlogmsg.RefSeqNo );
				}
				break;

			case 'U':

				trace( DEBUG_NORMAL, "Received Update TxnLog Message from NotificationId[%d]", txnlogmsg.NotificationId );
				SqlErr = updateEzTxnLog( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName );
				if( SqlErr != 0 )
				{
					trace( DEBUG_ERROR, "Error in Updating EZTXNLOG Table SqlErr[ %05d ]", SqlErr );
					dumpTxnMsg( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName );
				}
				break;

			case 'S':
				trace( DEBUG_NORMAL, "Received Read TxnLog Message from NotificationId[%d]", txnlogmsg.NotificationId );
				memset( &txnlogmsg.eztxnmsg, 0, sizeof( struct EzTxnMsg ) );
				memset( txnlogmsg.SrcChannelName, 0, sizeof( txnlogmsg.SrcChannelName ) );
				SqlErr = selectEzTxnLog( &txnlogmsg.eztxnmsg, txnlogmsg.SearchIndex, txnlogmsg.SrcChannelName, txnlogmsg.DestChannelName );
				if( SqlErr != 0 )
				{
					trace( "Error in reading EZTXNLOG Table for TxnRefNum[%s]...SqlErr[%05d]", txnlogmsg.SearchIndex );
					memset( &eztxnlogqmsg, 0, sizeof( struct EzTxnLogQMsg ) );
					eztxnlogqmsg.msgtype = txnlogmsg.NotificationId;
					eztxnlogqmsg.txnlogmsg.CommandCode = 'S';
					eztxnlogqmsg.txnlogmsg.Response = -1;

					if( msgsnd( this->GetSourceChannelQid(), &eztxnlogqmsg, sizeof( struct EzTxnLogQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
						trace( DEBUG_ERROR, "Error in Sending Response to NotificationId[%d]...SysErr[%s] ErrNo[%d]", txnlogmsg.NotificationId, strerror( errno ), errno );
					else
						trace( DEBUG_NORMAL, "Send Response to NotificationId[%d] ...", txnlogmsg.NotificationId );
				}
				else
				{
					trace( DEBUG_NORMAL, "Read Message from EzTxnLog Table for TxnRefNum[%s]", txnlogmsg.SearchIndex );
					memset( &eztxnlogqmsg, 0, sizeof( struct EzTxnLogQMsg ) );
					eztxnlogqmsg.msgtype = txnlogmsg.NotificationId;
					eztxnlogqmsg.txnlogmsg.CommandCode = 'S';
					eztxnlogqmsg.txnlogmsg.Response = 1;
					memcpy( &eztxnlogqmsg.txnlogmsg.eztxnmsg, &txnlogmsg.eztxnmsg, sizeof( struct EzTxnMsg ) );
					if( msgsnd( this->GetSourceChannelQid(), &eztxnlogqmsg, sizeof( struct EzTxnLogQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
						trace( DEBUG_ERROR, "Error in Sending Response to NotificationId[%d]...SysErr[%s] ErrNo[%d]", txnlogmsg.NotificationId, strerror( errno ), errno );
					else
						trace( DEBUG_NORMAL, "Send Response to NotificationId[%d] ...", txnlogmsg.NotificationId );
				}
				break;

			default:
				trace( DEBUG_ERROR, "Invalid Command Received.....");
				break;
		}
	}
}

int EzTxnLogger :: insertEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum, const char *I_SrcChannelName, const char *I_DestChannelName, short RefSeqNo )
{
	char SqlStmt[ MAX_INSERT_QUERY_SIZE + 1 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );
	composeInsertQuery( I_TxnRefNum, I_SrcChannelName, I_DestChannelName, RefSeqNo, txnmsg, SqlStmt );
	trace("Test<%s>", SqlStmt );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
};

int EzTxnLogger :: updateEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum, const char *I_SrcChannelName, const char *I_DestChannelName )
{
	char SqlStmt[ MAX_INSERT_QUERY_SIZE + 1 ];

	memset( SqlStmt, 0, sizeof( SqlStmt ) );

	sprintf( SqlStmt, "UPDATE INTO EZTXNLOG SET\
			MSGTYPE = %d,\
			TXNCODE = %d,\
			ORGMSGTYPE = %d,\
			TERMINALID = '%s',\
			TERMLOC = '%s',\
			TRACENO = %d,\
			ORGTRACENO = %d,\
			TRANDATE = %d,\
			TRANTIME = %d,\
			ORGTRANDATE = %d,\
			ORGTRANTIME = %d,\
			LOCALDATE = %d,\
			LOCALTIME = %d,\
			RESPCODE = %d,\
			REVCODE = %d,\
			REASONCODE = %d,\
			AUTHCODE = %d,\
			CAPTUREDATE = %d,\
			CAPTURETIME = %d,\
			SETTLEMENTDATE = %d,\
			ACQCURRENCYCODE = %d,\
			ACQCONVRATE = %d,\
			ACQCONVDATE = %d,\
			ISSCURRENCYCODE = %d,\
			ISSCONVRATE = %d,\
			ISSCONVDATE = %d,\
			SETTCURRENCYCODE = %d,\
			SETTCONVRATE = %d,\
			SETTCONVDATE = %d,\
			MERCHANTTYPE = %d,\
			POSENTRYCODE = %d,\
			POSCONDITIONCODE = %d,\
			POSCAPCODE = %d,\
			POSPINCAPCODE = %c,\
			CHN = '%s',\
			ACQBRANCHCODE = '%s',\
			ISSBRANCHCODE = '%s',\
			TXFBRANCHCODE = '%s',\
			FORWARDBRANCHCODE = '%s',\
			FROMACCTSUBTYPE = '%s',\
			TOACCTSUBTYPE = '%s',\
			AVAILBALANCE = '%s',\
			LEDGERBALANCE = '%s',\
			AMOUNT = '%s',\
			TXNFEE = '%s',\
			DISPAMOUNT = '%s',\
			FROMACCOUNT = '%s',\
			TOACCOUNT = '%s',\
			REFNUM = '%s',\
			AUTHNUM = '%s',\
			ACCEPTORNAME = '%s',\
			ACQUIRERINST = '%s',\
			ISSUERINST = '%s',\
			FORWARDINST = '%s',\
			TXFINST = '%s',\
			SETTINST = '%s',\
			NETWORKID = '%s',\
			ACQNETWORKID = '%s',\
			ISSUERNETWORKID = '%s',\
			FWDNETWORKID = '%s',\
			TXFNETWORKID = '%s',\
			SETTNETWORKID = '%s',\
			TRACK2 = '%s',\
			RSVFLD1 = '%s',\
			RSVFLD2 = '%s',\
			RSVFLD3 = '%s',\
			RSVFLD4 = '%s',\
			RSVFLD5 = '%s',\
			RSVFLD6 = '%s',\
			ORGCHANNEL = '%s',\
			ORGPORT = '%s',\
			SRCPORT = '%s'\
		WHERE RTRIM(TXNREFNUM) = '%s'", I_TxnRefNum,
		txnmsg->MsgType,
	    txnmsg->OrgMsgType,
	    txnmsg->TxnCode,
	    txnmsg->TerminalId,
	    txnmsg->TerminalLocation,
	    txnmsg->TraceNo,
	    txnmsg->OrgTraceNo,
	    txnmsg->TranDate,
	    txnmsg->TranTime,
	    txnmsg->OrgTranDate,
	    txnmsg->OrgTranTime,
	    txnmsg->LocalDate,
	    txnmsg->LocalTime,
	    txnmsg->RespCode,
	    txnmsg->RevCode,
	    txnmsg->ReasonCode,
	    txnmsg->AuthCode,
	    txnmsg->CaptureDate,
	    txnmsg->CaptureTime,
	    txnmsg->SettlementDate,
	    txnmsg->AcqCurrencyCode,
	    txnmsg->AcqConvRate,
	    txnmsg->AcqConvDate,
	    txnmsg->IssCurrencyCode,
	    txnmsg->IssConvRate,
	    txnmsg->IssConvDate,
	    txnmsg->SettCurrencyCode,
	    txnmsg->SettConvRate,
	    txnmsg->SettConvDate,
	    txnmsg->MerchantType,
	    txnmsg->PosEntryCode,
	    txnmsg->PosConditionCode,
	    txnmsg->PosCapCode,
	    txnmsg->PosPinCapCode,
	    txnmsg->chn,
	    txnmsg->AcqBranchCode,
	    txnmsg->IssBranchCode,
	    txnmsg->ForwardBranchCode,
	    txnmsg->TxfBranchCode,
		txnmsg->FromAcctSubType,
	    txnmsg->ToAcctSubType,
	    txnmsg->AvailBalance,
	    txnmsg->LedgerBalance,
	    txnmsg->Amount,
	    txnmsg->TxnFee,
	    txnmsg->DispAmount,
	    txnmsg->FromAccount,
	    txnmsg->ToAccount,
	    txnmsg->RefNum,
	    txnmsg->AuthNum,
	    txnmsg->AcceptorName,
	    txnmsg->AcquirerInst,
	    txnmsg->IssuerInst,
	    txnmsg->ForwardInst,
	    txnmsg->TxfInst,
	    txnmsg->SettInst,
	    txnmsg->NetworkId,
	    txnmsg->AcqNetworkId,
	    txnmsg->IssuerNetworkId,
	    txnmsg->FwdNetworkId,
	    txnmsg->TxfNetworkId,
	    txnmsg->SettNetworkId,
	    txnmsg->Track2,
	    txnmsg->RsvFld1,
	    txnmsg->RsvFld2,
	    txnmsg->RsvFld3,
	    txnmsg->RsvFld4,
	    txnmsg->RsvFld5,
	    txnmsg->RsvFld6,
	   	txnmsg->OrgChannel,
		txnmsg->OrgPort,
		I_SrcChannelName);

    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
};

int EzTxnLogger :: selectEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum, char *I_SrcChannelName, char *I_DestChannelName )
{
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ MAX_INSERT_QUERY_SIZE + 1 ];

	char TxnRefNum[ 151 ];
	int MsgType;
    int OrgMsgType;
    int TxnCode;
    char TerminalId[ 17 ];
    char TerminalLocation[ 65 ];
    int TraceNo;
    int OrgTraceNo;
    int TranDate;
    int TranTime;
    int OrgTranDate;
    int OrgTranTime;
    int LocalDate;
    int LocalTime;
    int RespCode;
    int RevCode;
    int ReasonCode;
    int AuthCode;
    int CaptureDate;
    int CaptureTime;
    int SettlementDate;
    int AcqCurrencyCode;
    char AcqConvRate[32];
    int AcqConvDate;
    int IssCurrencyCode;
    char IssConvRate[32];
    int IssConvDate;
    int SettCurrencyCode;
    char SettConvRate[32];
    int SettConvDate;
    int MerchantType;
    int PosEntryCode;
    int PosConditionCode;
    int PosCapCode;
    char PosPinCapCode;
    char chn[ 20 ];
    char AcqBranchCode[ 11 ];
    char IssBranchCode[ 11 ];
    char TxfBranchCode[ 11 ];
    char ForwardBranchCode[ 11 ];
    char FromAcctSubType[ 11 ];
    char ToAcctSubType[ 11 ];
	char AvailBalance[ 15 ];
    char LedgerBalance[ 15 ];
    char Amount[ 15 ];
    char TxnFee[ 15 ];
    char DispAmount[ 15 ];
    char FromAccount[ 33 ];
    char ToAccount[ 33 ];
    char RefNum[ 13 ];
    char AuthNum[ 13 ];
    char AcceptorName[ 41 ];
    char AcquirerInst[ 13 ];
    char IssuerInst[ 13 ];
    char ForwardInst[ 13 ];
    char TxfInst[ 13 ];
    char SettInst[ 13 ];
    char NetworkId[ 17 ];
    char AcqNetworkId[ 17 ];
	char IssuerNetworkId[ 17 ];
	char FwdNetworkId[ 17 ];
	char TxfNetworkId[ 17 ];
	char SettNetworkId[ 17 ];
    char Track2[ 40 ];
    char RsvFld1[ 513 ];
    char RsvFld2[ 513 ];
    char RsvFld3[ 51 ];
    char RsvFld4[ 51 ];
    char RsvFld5[ 51 ];
    char RsvFld6[ 51 ];
    char OrgChannel[ 33 ];
    char OrgPort[ 33 ];
    char SrcChannel[ 33 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
            return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT\
		RTRIM(TXNREFNUM),\
		MSGTYPE,\
		ORGMSGTYPE,\
		TXNCODE,\
		RTRIM(TERMINALID),\
		RTRIM(TERMLOC),\
		TRACENO,\
		ORGTRACENO,\
		TRANDATE,\
		TRANTIME,\
		ORGTRANDATE,\
		ORGTRANTIME,\
		LOCALDATE,\
		LOCALTIME,\
		RESPCODE,\
		REVCODE,\
		REASONCODE,\
		AUTHCODE,\
		CAPTUREDATE,\
		CAPTURETIME,\
		SETTLEMENTDATE,\
		ACQCURRENCYCODE,\
		ACQCONVRATE,\
		ACQCONVDATE,\
		ISSCURRENCYCODE,\
		ISSCONVRATE,\
		ISSCONVDATE,\
		SETTCURRENCYCODE,\
		SETTCONVRATE,\
		SETTCONVDATE,\
		MERCHANTTYPE,\
		POSENTRYCODE,\
		POSCONDITIONCODE,\
		POSCAPCODE,\
		POSPINCAPCODE,\
		RTRIM(CHN),\
		RTRIM(ACQBRANCHCODE),\
		RTRIM(ISSBRANCHCODE),\
		RTRIM(TXFBRANCHCODE),\
		RTRIM(FORWARDBRANCHCODE),\
		RTRIM(FROMACCTSUBTYPE),\
		RTRIM(TOACCTSUBTYPE),\
		RTRIM(AVAILBALANCE),\
		RTRIM(LEDGERBALANCE),\
		RTRIM(AMOUNT),\
		RTRIM(TXNFEE),\
		RTRIM(DISPAMOUNT),\
		RTRIM(FROMACCOUNT),\
		RTRIM(TOACCOUNT),\
		RTRIM(REFNUM),\
		RTRIM(AUTHNUM),\
		RTRIM(ACCEPTORNAME),\
		RTRIM(ACQUIRERINST),\
		RTRIM(ISSUERINST),\
		RTRIM(FORWARDINST),\
		RTRIM(TXFINST),\
		RTRIM(SETTINST),\
		RTRIM(NETWORKID),\
		RTRIM(ACQNETWORKID),\
		RTRIM(ISSUERNETWORKID),\
		RTRIM(FWDNETWORKID),\
		RTRIM(TXFNETWORKID),\
		RTRIM(SETTNETWORKID),\
		RTRIM(TRACK2),\
		RTRIM(RSVFLD1),\
		RTRIM(RSVFLD2),\
		RTRIM(RSVFLD3),\
		RTRIM(RSVFLD4),\
		RTRIM(RSVFLD5),\
		RTRIM(RSVFLD6),\
		RTRIM(ORGCHANNEL),\
		RTRIM(ORGPORT),\
		RTRIM(SRCCHANNEL)\
		FROM EZTXNLOG WHERE RTRIM(TXNREFNUM)='%s';", I_TxnRefNum );


    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Executing SqlStmt in selectEzTxnLog [ %d ]", odbcret );
            //getNativeErrorCode();
            trace("<%s>", SqlStmt);
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

 	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
    memset( chn, 0, sizeof( chn ) );
    memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
    memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
    memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
    memset( TxfBranchCode, 0, sizeof( TxfBranchCode ) );
    memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
    memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
    memset( AvailBalance, 0, sizeof( AvailBalance ) );
    memset( LedgerBalance, 0, sizeof( LedgerBalance ) );
    memset( Amount, 0, sizeof( Amount ) );
    memset( TxnFee, 0, sizeof( TxnFee ) );
    memset( DispAmount, 0, sizeof( DispAmount ) );
    memset( FromAccount, 0, sizeof( FromAccount ) );
    memset( ToAccount, 0, sizeof( ToAccount ) );
    memset( RefNum, 0, sizeof( RefNum ) );
    memset( AuthNum, 0, sizeof( AuthNum ) );
    memset( AcceptorName, 0, sizeof( AcceptorName ) );
    memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
    memset( IssuerInst, 0, sizeof( IssuerInst ) );
    memset( ForwardInst, 0, sizeof( ForwardInst ) );
    memset( TxfInst, 0, sizeof( TxfInst ) );
    memset( SettInst, 0, sizeof( SettInst ) );
    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( AcqNetworkId, 0, sizeof( AcqNetworkId ) );
    memset( IssuerNetworkId, 0, sizeof( IssuerNetworkId ) );
    memset( FwdNetworkId, 0, sizeof( FwdNetworkId ) );
    memset( TxfNetworkId, 0, sizeof( TxfNetworkId ) );
    memset( SettNetworkId, 0, sizeof( SettNetworkId ) );
    memset( AcqConvRate, 0, sizeof( AcqConvRate ) );
    memset( IssConvRate, 0, sizeof( IssConvRate ) );
    memset( SettConvRate, 0, sizeof( SettConvRate ) );
    memset( Track2, 0, sizeof( Track2 ) );
    memset( RsvFld1, 0, sizeof( RsvFld1 ) );
    memset( RsvFld2, 0, sizeof( RsvFld2 ) );
    memset( RsvFld3, 0, sizeof( RsvFld3 ) );
    memset( RsvFld4, 0, sizeof( RsvFld4 ) );
    memset( RsvFld5, 0, sizeof( RsvFld5 ) );
    memset( RsvFld6, 0, sizeof( RsvFld6 ) );
    memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	memset( SrcChannel, 0, sizeof( SrcChannel ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, TxnRefNum, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TxnRefNum) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_SLONG, &MsgType, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(MsgType) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_SLONG, &OrgMsgType, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(OrgMsgType) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &TxnCode, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TxnCode) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_CHAR, TerminalId, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TerminalId) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_CHAR, TerminalLocation, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TerminalLocation) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &TraceNo, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TraceNo) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &OrgTraceNo, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(OrgTraceNo) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &TranDate, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TranDate) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &TranTime, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(TranTime) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &OrgTranDate, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(OrgTranDate) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_SLONG, &OrgTranTime, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(OrgTranTime) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_SLONG, &LocalDate, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(LocalDate) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 14, SQL_C_SLONG, &LocalTime, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(LocalTime) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 15, SQL_C_SLONG, &RespCode, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(RespCode) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 16, SQL_C_SLONG, &RevCode, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(RevCode) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 17, SQL_C_SLONG, &ReasonCode, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(ReasonCode) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 18, SQL_C_SLONG, &AuthCode, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(AuthCode) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 19, SQL_C_SLONG, &CaptureDate, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(CaptureDate) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 20, SQL_C_SLONG, &CaptureTime, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
            trace( DEBUG_ERROR, "Error in Binding Column(CaptureTime) in EZTXNLOG [ %d ]", odbcret );
            SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
            return -1;
    }

    odbcret = SQLBindCol( hstmt, 21, SQL_C_SLONG, &SettlementDate, MAXRESULT, &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SettlementDate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 22, SQL_C_SLONG, &AcqCurrencyCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcqCurrencyCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 23, SQL_C_CHAR, AcqConvRate, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcqConvRate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 24, SQL_C_SLONG, &AcqConvDate, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcqConvDate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 25, SQL_C_SLONG, &IssCurrencyCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(IssCurrencyCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 26, SQL_C_CHAR, IssConvRate, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(IssConvRate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 27, SQL_C_SLONG, &IssConvDate, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(IssConvDate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 28, SQL_C_SLONG, &SettCurrencyCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SettCurrencyCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 29, SQL_C_CHAR, SettConvRate, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SettConvRate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 30, SQL_C_SLONG, &SettConvDate, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SettConvDate) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 31, SQL_C_SLONG, &MerchantType, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(MerchantType) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 32, SQL_C_SLONG, &PosEntryCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(PosEntryCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 33, SQL_C_SLONG, &PosConditionCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(PosConditionCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 34, SQL_C_SLONG, &PosCapCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(PosCapCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 35, SQL_C_CHAR, &PosPinCapCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(PosPinCapCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 36, SQL_C_CHAR, chn, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(chn) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 37, SQL_C_CHAR, AcqBranchCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcqBranchCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 38, SQL_C_CHAR, IssBranchCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(IssBranchCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 39, SQL_C_CHAR, TxfBranchCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(TxfBranchCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 40, SQL_C_CHAR, ForwardBranchCode, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(ForwardBranchCode) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 41, SQL_C_CHAR, FromAcctSubType, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(FromAcctSubType) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 42, SQL_C_CHAR, ToAcctSubType, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(ToAcctSubType) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 43, SQL_C_CHAR, AvailBalance, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AvailBalance) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 44, SQL_C_CHAR, LedgerBalance, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(LedgerBalance) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 45, SQL_C_CHAR, Amount, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(Amount) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 46, SQL_C_CHAR, TxnFee, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(TxnFee) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 47, SQL_C_CHAR, DispAmount, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(DispAmount) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 48, SQL_C_CHAR, FromAccount, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(FromAccount) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 49, SQL_C_CHAR, ToAccount, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(ToAccount) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 50, SQL_C_CHAR, RefNum, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RefNum) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 51, SQL_C_CHAR, AuthNum, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AuthNum) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 52, SQL_C_CHAR, AcceptorName, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcceptorName) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 53, SQL_C_CHAR, AcquirerInst, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcquirerInst) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 54, SQL_C_CHAR, IssuerInst, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(IssuerInst) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 55, SQL_C_CHAR, ForwardInst, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(ForwardInst) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 56, SQL_C_CHAR, TxfInst, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(TxfInst) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 57, SQL_C_CHAR, SettInst, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SettInst) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 58, SQL_C_CHAR, NetworkId, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 59, SQL_C_CHAR, AcqNetworkId, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(AcqNetworkId) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 60, SQL_C_CHAR, IssuerNetworkId, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(IssuerNetworkId) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 61, SQL_C_CHAR, FwdNetworkId, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(FwdNetworkId) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 62, SQL_C_CHAR, TxfNetworkId, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(TxfNetworkId) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 63, SQL_C_CHAR, SettNetworkId, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SettNetworkId) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 64, SQL_C_CHAR, Track2, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(Track2) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 65, SQL_C_CHAR, RsvFld1, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RsvFld1) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 66, SQL_C_CHAR, RsvFld2, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RsvFld2) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 67, SQL_C_CHAR, RsvFld3, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RsvFld3) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 68, SQL_C_CHAR, RsvFld4, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RsvFld4) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 69, SQL_C_CHAR, RsvFld5, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RsvFld5) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 70, SQL_C_CHAR, RsvFld6, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(RsvFld6) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 71, SQL_C_CHAR, OrgChannel, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(OrgChannel) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 72, SQL_C_CHAR, OrgPort, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(OrgPort) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	odbcret = SQLBindCol( hstmt, 73, SQL_C_CHAR, SrcChannel, MAXRESULT, &Len );
	if( !SQL_SUCCEEDED( odbcret ) )
	{
		 trace( DEBUG_ERROR, "Error in Binding Column(SrcChannel) in EZTXNLOG [ %d ]", odbcret );
		 SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		 return -1;
	}

	while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
	{
		txnmsg->MsgType = MsgType;
		txnmsg->OrgMsgType = OrgMsgType;
		txnmsg->TxnCode = TxnCode;
		memset( txnmsg->TerminalId, 0, sizeof( txnmsg->TerminalId ) );
		strcpy( txnmsg->TerminalId, TerminalId );
		memset( txnmsg->TerminalLocation, 0, sizeof( txnmsg->TerminalLocation ) );
		strcpy( txnmsg->TerminalLocation, TerminalLocation );
		txnmsg->TraceNo = TraceNo;
		txnmsg->OrgTraceNo = OrgTraceNo;
		txnmsg->TranDate = TranDate;
		txnmsg->TranTime = TranTime;
		txnmsg->OrgTranDate = OrgTranDate;
		txnmsg->OrgTranTime = OrgTranTime;
		txnmsg->LocalDate = LocalDate;
		txnmsg->LocalTime = LocalTime;
		txnmsg->RespCode = RespCode;
		txnmsg->RevCode = RevCode;
		txnmsg->AuthCode = AuthCode;
		txnmsg->ReasonCode = ReasonCode;
		txnmsg->CaptureDate = CaptureDate;
		txnmsg->CaptureTime = CaptureTime;
		txnmsg->SettlementDate = SettlementDate;
		txnmsg->AcqCurrencyCode = AcqCurrencyCode;
		txnmsg->IssCurrencyCode = IssCurrencyCode;
		txnmsg->SettCurrencyCode = SettCurrencyCode;
		memset( txnmsg->AcqConvRate, 0, sizeof(txnmsg->AcqConvRate) );
		strcpy( txnmsg->AcqConvRate ,AcqConvRate );
		txnmsg->AcqConvDate = AcqConvDate;
		memset( txnmsg->IssConvRate, 0, sizeof(txnmsg->IssConvRate) );
		strcpy( txnmsg->IssConvRate ,IssConvRate );
		txnmsg->IssConvDate = IssConvDate;
		memset( txnmsg->SettConvRate, 0, sizeof(txnmsg->SettConvRate) );
		strcpy( txnmsg->SettConvRate ,SettConvRate );
		txnmsg->SettConvDate = SettConvDate;
		txnmsg->MerchantType = MerchantType;
		txnmsg->PosEntryCode = PosEntryCode;
		txnmsg->PosConditionCode = PosConditionCode;
		txnmsg->PosCapCode = PosCapCode;
		txnmsg->PosPinCapCode = PosPinCapCode;
		memset( txnmsg->AcqBranchCode, 0, sizeof( txnmsg->AcqBranchCode ) );
		strcpy( txnmsg->AcqBranchCode, AcqBranchCode );
		memset( txnmsg->IssBranchCode, 0, sizeof( txnmsg->IssBranchCode ) );
		strcpy( txnmsg->IssBranchCode, IssBranchCode );
		memset( txnmsg->TxfBranchCode, 0, sizeof( txnmsg->TxfBranchCode ) );
		strcpy( txnmsg->TxfBranchCode, TxfBranchCode );
		memset( txnmsg->ForwardBranchCode, 0, sizeof( txnmsg->ForwardBranchCode ) );
		strcpy( txnmsg->ForwardBranchCode,ForwardBranchCode );
		memset( txnmsg->FromAcctSubType, 0, sizeof( txnmsg->FromAcctSubType ) );
		strcpy( txnmsg->FromAcctSubType, FromAcctSubType );
		memset( txnmsg->ToAcctSubType, 0, sizeof( txnmsg->ToAcctSubType ) );
		strcpy( txnmsg->ToAcctSubType, ToAcctSubType );
		memset( txnmsg->AvailBalance, 0, sizeof( txnmsg->AvailBalance ) );
		strcpy( txnmsg->AvailBalance, AvailBalance );
		memset( txnmsg->LedgerBalance, 0, sizeof( txnmsg->LedgerBalance ) );
		strcpy( txnmsg->LedgerBalance, LedgerBalance );
		memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
		strcpy( txnmsg->Amount, Amount );
		memset( txnmsg->TxnFee, 0, sizeof( txnmsg->TxnFee ) );
		strcpy( txnmsg->TxnFee, TxnFee );
		memset( txnmsg->DispAmount, 0, sizeof( txnmsg->DispAmount ) );
		strcpy( txnmsg->DispAmount, DispAmount );
		memset( txnmsg->FromAccount, 0, sizeof( txnmsg->FromAccount ) );
		strcpy( txnmsg->FromAccount, FromAccount );
		memset( txnmsg->ToAccount, 0, sizeof( txnmsg->ToAccount ) );
		strcpy( txnmsg->ToAccount, ToAccount );
		memset( txnmsg->RefNum, 0, sizeof( txnmsg->RefNum ) );
		strcpy( txnmsg->RefNum, RefNum );
		memset( txnmsg->AuthNum, 0, sizeof( txnmsg->AuthNum ) );
		strcpy( txnmsg->AuthNum, AuthNum );
		memset( txnmsg->AcceptorName, 0, sizeof( txnmsg->AcceptorName ) );
		strcpy( txnmsg->AcceptorName, AcceptorName );
		memset( txnmsg->AcquirerInst, 0, sizeof( txnmsg->AcquirerInst ) );
		strcpy( txnmsg->AcquirerInst, AcquirerInst );
		memset( txnmsg->IssuerInst, 0, sizeof( txnmsg->IssuerInst ) );
		strcpy( txnmsg->IssuerInst, IssuerInst );
		memset( txnmsg->ForwardInst, 0, sizeof( txnmsg->ForwardInst ) );
		strcpy( txnmsg->ForwardInst, ForwardInst );
		memset( txnmsg->TxfInst, 0, sizeof( txnmsg->TxfInst ) );
		strcpy( txnmsg->TxfInst, TxfInst );
		memset( txnmsg->SettInst, 0, sizeof( txnmsg->SettInst ) );
		strcpy( txnmsg->SettInst, SettInst );
		memset( txnmsg->NetworkId, 0, sizeof( txnmsg->NetworkId ) );
		strcpy( txnmsg->NetworkId, NetworkId );
		memset( txnmsg->AcqNetworkId, 0, sizeof( txnmsg->AcqNetworkId ) );
		strcpy( txnmsg->AcqNetworkId, AcqNetworkId );
		memset( txnmsg->IssuerNetworkId, 0, sizeof( txnmsg->IssuerNetworkId ) );
		strcpy( txnmsg->IssuerNetworkId, IssuerNetworkId );
		memset( txnmsg->FwdNetworkId, 0, sizeof( txnmsg->FwdNetworkId ) );
		strcpy( txnmsg->FwdNetworkId, FwdNetworkId );
		memset( txnmsg->TxfNetworkId, 0, sizeof( txnmsg->TxfNetworkId ) );
		strcpy( txnmsg->TxfNetworkId, TxfNetworkId );
		memset( txnmsg->SettNetworkId, 0, sizeof( txnmsg->SettNetworkId ) );
		strcpy( txnmsg->SettNetworkId, SettNetworkId );
		memset( txnmsg->Track2, 0, sizeof( txnmsg->Track2 ) );
		strcpy( txnmsg->Track2, Track2 );
		memset( txnmsg->RsvFld1, 0, sizeof( txnmsg->RsvFld1 ) );
		strcpy( txnmsg->RsvFld1, RsvFld1 );
		memset( txnmsg->RsvFld2, 0, sizeof( txnmsg->RsvFld2 ) );
		strcpy( txnmsg->RsvFld2, RsvFld2 );
		memset( txnmsg->RsvFld3, 0, sizeof( txnmsg->RsvFld3 ) );
		strcpy( txnmsg->RsvFld3, RsvFld3 );
		memset( txnmsg->RsvFld4, 0, sizeof( txnmsg->RsvFld4 ) );
		strcpy( txnmsg->RsvFld4, RsvFld4 );
		memset( txnmsg->RsvFld5, 0, sizeof( txnmsg->RsvFld5 ) );
		strcpy( txnmsg->RsvFld5, RsvFld5 );
		memset( txnmsg->RsvFld6, 0, sizeof( txnmsg->RsvFld6 ) );
		strcpy( txnmsg->RsvFld6, RsvFld6 );
		memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
		strcpy( txnmsg->OrgChannel, OrgChannel );
		memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
		strcpy( txnmsg->OrgPort, OrgPort );
		strcpy( I_SrcChannelName, SrcChannel );
	}

    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
};


int main( int argc, char **argv )
{
	EzTxnLogger txnloggerobj;
	txnloggerobj.initTxnLogger( argv[ 0 ] );
	txnloggerobj.serviceRequest();
	return 1;
}
