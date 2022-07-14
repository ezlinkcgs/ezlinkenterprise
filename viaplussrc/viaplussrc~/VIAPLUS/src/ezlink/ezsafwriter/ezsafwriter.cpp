#include <ezlink/ezsafwriter.h>

void EzSafWriter :: initSafWriter( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], dirpath[ 200 ];
	EzCfgUtil cfgutil;
	DIR *dir_ptr;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsafwriter.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzSafWriter", TaskName ) < 0 )
	{
		trace( "Error in Creating EzSafWriter Channel" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initODBCUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing ....." );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezinstprofileutil.initInstProfile( this ) < 0 )
	{
		trace( "Error in initializing EzInstProfile" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initNetworkUtil( this ) < 0 )
	{
		trace( "Error in Initializing NetworkUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( eztxnrefselectutil.initEzTxnRefSelectUtil( this ) < 0 )
	{
		trace( "Error in initializing EzTxnRefSelectUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}


	if( eztxnsequtil.initTxnSeqUtil( this ) < 0 )
	{
		trace( "Error in initializing TxnSeqUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezreplayutil.initReplayUtil( this ) < 0 )
	{
		trace( "Error in initializing TxnSeqUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezsafpropertyutil.initSafPropertyUtil( this ) < 0 )
	{
		trace( "Error in initializing EzSafPropertyUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezsafformatutil.initSAFFormatUtil( this, &ezinstprofileutil, &ezpadssutil ) < 0 )
	{
		trace( "Error in initializing EzSafFormatUtil" );
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( eztxnmsgorderutil.initTxnMsgOrderUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTxnMsgOrderUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnlogutil.initTxnLogUtil( this, this ) < 0 )
	{
		trace( "Error in Initializing EzTxnLogUtil");
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}


	memset( dirpath, 0, sizeof( dirpath ) );
	sprintf( dirpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "inf", "safdb" );

	if( checkDir( dirpath ) < 0 )
	{
		trace( "^^^^^^^^^^^EzSafWriter Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	composeSqlString();

	TaskInit();
	initEzSigUtil( this );
}

int EzSafWriter :: checkDir( const char *DirPath )
{
	DIR *dir_ptr;
	dir_ptr = opendir( DirPath );
	if( dir_ptr == NULL )
	{
		if( errno == ENOENT )
		{
			if( mkdir( DirPath, 0777 ) < 0 )
			{
				trace( "Error in Creating Directory[%s]...SysErr[%s] ErrNo[%d]", DirPath, strerror( errno ), errno );
				return -1;
			}
			dir_ptr = opendir( DirPath );
			if( dir_ptr == NULL )
			{
				trace( "Error in Opening Directory[%s]...SysErr[%s] ErrNo[%d]", DirPath, strerror( errno ), errno );
				return -1;
			}
		}
		else
		{
			trace( "Error in Opening Directory[%s]...SysErr[%s] ErrNo[%d]", DirPath, strerror( errno ), errno );
			return -1;
		}
	}
	closedir( dir_ptr );
	return 1;
}

void EzSafWriter :: composeSqlString()
{
	memset( SQLString, 0, sizeof( SQLString ) );

	sprintf( SQLString, "INSERT INTO EZSAFDB (" );
	strcat( SQLString, "SAFRECORDNO," );
	strcat( SQLString, "TRANDATE," );
	strcat( SQLString, "TRANTIME," );
	strcat( SQLString, "NETWORKID," );
	strcat( SQLString, "SAFSTATUS," );
	strcat( SQLString, "SAFINDICATOR," );
	strcat( SQLString, "SAFRESPONSEINDICATOR," );
	strcat( SQLString, "SAFRESPONSE," );
	strcat( SQLString, "TIMEOUTCOUNT," );
	strcat( SQLString, "TXNREFNUM," );
	strcat( SQLString, "SAFDETREC," );
	strcat( SQLString, "SAFREPEATINDICATOR" );
	strcat( SQLString, ") VALUES (" );
	trace( "SQLString[%s]", SQLString );
}

void EzSafWriter :: composeInsertQuery( struct EzSafDBInfo safdbinfo, char *SQLQuery )
{
	strcpy( SQLQuery, SQLString );

	//SAFRECORDNO
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", safdbinfo.SafRecordNo );

	//TRANDATE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", safdbinfo.TranDate );

	//TRANTIME
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", safdbinfo.TranTime );

	//NETWORKID
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", safdbinfo.NetworkId );

	//SAFSTATUS
	sprintf( SQLQuery + strlen( SQLQuery ), "'%c',", safdbinfo.SafStatus );

	//SAFINDICATOR
	sprintf( SQLQuery + strlen( SQLQuery ), "'%c',", safdbinfo.SafIndicator );

	//SAFRESPONSEINDICATOR
	sprintf( SQLQuery + strlen( SQLQuery ), "'%c',", safdbinfo.SafResponseIndicator );

	//SAFRESPONSE
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", safdbinfo.SafResponse );

	//TIMEOUTCOUNT
	sprintf( SQLQuery + strlen( SQLQuery ), "'%d',", safdbinfo.TimeOutCount );

	//TXNREFNUM
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", safdbinfo.TxnRefNum );

	//SAFDETREC
	sprintf( SQLQuery + strlen( SQLQuery ), "'%s',", safdbinfo.SAFDetailRec );

	//SAFREPEATINDICATOR
	sprintf( SQLQuery + strlen( SQLQuery ), "'%c'", safdbinfo.SafRepeatIndicator );

	strcat( SQLQuery, ");");

}

bool EzSafWriter :: isSafRequest( int MsgType )
{
	if( MsgType % 100 == 0 || MsgType % 100 == 20 || MsgType % 100 == 40 || MsgType % 100 == 60 || MsgType % 100 == 80 )
		return true;
	else
		return false;
}

bool EzSafWriter :: isSafResponse( int MsgType )
{
	if( MsgType % 100 == 10 || MsgType % 100 == 30 || MsgType % 100 == 50 || MsgType % 100 == 70 || MsgType % 100 == 90 )
		return true;
	else
		return false;
}

void EzSafWriter :: insertToFile( struct EzSafDBInfo safdbinfo )
{
	char FileName[ 200 ], dirpath[ 200 ], SQLQuery[ MAX_INSERT_QUERY_SIZE + 1 ];
	FILE *fptr;

	memset( FileName, 0, sizeof( FileName ) );
	sprintf( FileName, "%s/%s/%s/%s_%06d_%d.SAF", getenv( "EZDIR_HOME" ), "inf", "safdb", safdbinfo.NetworkId, ezdatetimeutil.getSysDate(), getpid() );
	fptr = fopen( FileName, "a" );
	if( fptr == NULL )
	{
		trace( "Error in Opening File[%s] ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		memset( dirpath, 0, sizeof( dirpath ) );
		sprintf( dirpath, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "inf", "safdb", safdbinfo.NetworkId );
		if( checkDir( dirpath ) < 0 )
			return;
		fptr = fopen( FileName, "a" );
		if( fptr == NULL )
		{
				trace( "Error in Opening File[%s] ...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return;
		}
	}
	memset( SQLQuery, 0, sizeof( SQLQuery ) );
	composeInsertQuery( safdbinfo, SQLQuery );
	fprintf( fptr, "%s\n", SQLQuery );
	fclose( fptr );
}

void EzSafWriter :: populateTxnMsg( struct EzTxnMsg *txnmsgNew, struct EzTxnMsg *txnmsgOld )
{
	if( txnmsgNew->MsgType == 0 )
		txnmsgNew->MsgType = txnmsgOld->MsgType;

	if( txnmsgNew->OrgMsgType == 0 )
		txnmsgNew->OrgMsgType = txnmsgOld->OrgMsgType;

	if( txnmsgNew->TxnCode == 0 )
		txnmsgNew->TxnCode = txnmsgOld->TxnCode;

	if( strlen( txnmsgNew->TerminalId ) == 0 )
		strcpy( txnmsgNew->TerminalId, txnmsgOld->TerminalId );

	if( strlen( txnmsgNew->TerminalLocation ) == 0 )
		strcpy( txnmsgNew->TerminalLocation, txnmsgOld->TerminalLocation );

	if( txnmsgNew->TraceNo == 0 )
		txnmsgNew->TraceNo = txnmsgOld->TraceNo;

	if( txnmsgNew->OrgTraceNo == 0 )
		txnmsgNew->OrgTraceNo = txnmsgOld->OrgTraceNo;

	if( txnmsgNew->TranDate == 0 )
		txnmsgNew->TranDate = txnmsgOld->TranDate;

	if( txnmsgNew->TranTime == 0 )
		txnmsgNew->TranTime = txnmsgOld->TranTime;

	if( txnmsgNew->OrgTranDate == 0 )
		txnmsgNew->OrgTranDate = txnmsgOld->OrgTranDate;

	if( txnmsgNew->OrgTranTime == 0 )
		txnmsgNew->OrgTranTime = txnmsgOld->OrgTranTime;

	if( txnmsgNew->LocalDate == 0 )
		txnmsgNew->LocalDate = txnmsgOld->LocalDate;

	if( txnmsgNew->LocalTime == 0 )
		txnmsgNew->LocalTime = txnmsgOld->LocalTime;

	if( txnmsgNew->RevCode == 0 )
		txnmsgNew->RevCode = txnmsgOld->RevCode;

	if( txnmsgNew->ReasonCode == 0 )
		txnmsgNew->ReasonCode = txnmsgOld->ReasonCode;

	if( txnmsgNew->AuthCode == 0 )
		txnmsgNew->AuthCode = txnmsgOld->AuthCode;

	if( txnmsgNew->CaptureDate == 0 )
		txnmsgNew->CaptureDate = txnmsgOld->CaptureDate;

	if( txnmsgNew->CaptureTime == 0 )
		txnmsgNew->CaptureTime = txnmsgOld->CaptureTime;

	if( txnmsgNew->SettlementDate  == 0 )
		txnmsgNew->SettlementDate = txnmsgOld->SettlementDate;

	if( txnmsgNew->BusinessDate  == 0 )
			txnmsgNew->BusinessDate = txnmsgOld->BusinessDate;

	if( txnmsgNew->AcqCurrencyCode  == 0 )
		txnmsgNew->AcqCurrencyCode = txnmsgOld->AcqCurrencyCode;

	if( txnmsgNew->IssCurrencyCode  == 0 )
		txnmsgNew->IssCurrencyCode = txnmsgOld->IssCurrencyCode;

	if( txnmsgNew->SettCurrencyCode  == 0 )
		txnmsgNew->SettCurrencyCode = txnmsgOld->SettCurrencyCode;

	if( strlen( txnmsgNew->AcqConvRate ) == 0 )
		strcpy( txnmsgNew->AcqConvRate ,txnmsgOld->AcqConvRate );

	if( txnmsgNew->AcqConvDate == 0 )
		txnmsgNew->AcqConvDate = txnmsgOld->AcqConvDate;

	if( strlen( txnmsgNew->IssConvRate ) == 0 )
		strcpy( txnmsgNew->IssConvRate ,txnmsgOld->IssConvRate );

	if( txnmsgNew->IssConvDate == 0 )
		txnmsgNew->IssConvDate = txnmsgOld->IssConvDate;

	if( strlen( txnmsgNew->SettConvRate ) == 0 )
		strcpy( txnmsgNew->SettConvRate ,txnmsgOld->SettConvRate );

	if( txnmsgNew->SettConvDate == 0 )
		txnmsgNew->SettConvDate = txnmsgOld->SettConvDate;

	if( txnmsgNew->PosEntryCode == 0 )
		txnmsgNew->PosEntryCode = txnmsgOld->PosEntryCode;

	if( txnmsgNew->PosConditionCode == 0 )
		txnmsgNew->PosConditionCode = txnmsgOld->PosConditionCode;

	if( txnmsgNew->PosCapCode == 0 )
		txnmsgNew->PosCapCode = txnmsgOld->PosCapCode;

	if( txnmsgNew->PosPinCapCode == 0 )
		txnmsgNew->PosPinCapCode = txnmsgOld->PosPinCapCode;

	if( txnmsgNew->AvailBalanceFlg == '\0' )
		txnmsgNew->AvailBalanceFlg = txnmsgOld->AvailBalanceFlg;

	if( txnmsgNew->PinVerFlg == '\0' )
		txnmsgNew->PinVerFlg = txnmsgOld->PinVerFlg;

	if( txnmsgNew->AuthFlg == '\0' )
		txnmsgNew->AuthFlg = txnmsgOld->AuthFlg;

	if( txnmsgNew->CheckCardExpiry == '\0' )
		txnmsgNew->CheckCardExpiry = txnmsgOld->CheckCardExpiry;

	if( txnmsgNew->CheckServiceCode == '\0' )
		txnmsgNew->CheckServiceCode = txnmsgOld->CheckServiceCode;

	if( txnmsgNew->CheckCVV == '\0' )
		txnmsgNew->CheckCVV = txnmsgOld->CheckCVV;

	if( txnmsgNew->MerchantType == 0 )
		txnmsgNew->MerchantType = txnmsgOld->MerchantType;

	if( strlen( txnmsgNew->chn ) == 0 )
		strcpy( txnmsgNew->chn, txnmsgOld->chn );

	if( strlen( txnmsgNew->AcqBranchCode ) == 0 )
		strcpy( txnmsgNew->AcqBranchCode, txnmsgOld->AcqBranchCode );

	if( strlen( txnmsgNew->TxfBranchCode ) == 0 )
		strcpy( txnmsgNew->TxfBranchCode, txnmsgOld->TxfBranchCode );

	if( strlen( txnmsgNew->IssBranchCode ) == 0 )
		strcpy( txnmsgNew->IssBranchCode, txnmsgOld->IssBranchCode );

	if( strlen( txnmsgNew->ForwardBranchCode ) == 0 )
		strcpy( txnmsgNew->ForwardBranchCode, txnmsgOld->ForwardBranchCode );

	if( strlen( txnmsgNew->FromAcctSubType ) == 0 )
		strcpy( txnmsgNew->FromAcctSubType, txnmsgOld->FromAcctSubType );

	if( strlen( txnmsgNew->ToAcctSubType ) == 0 )
		strcpy( txnmsgNew->ToAcctSubType, txnmsgOld->ToAcctSubType );

	if( strlen( txnmsgNew->Amount ) == 0 )
		strcpy( txnmsgNew->Amount, txnmsgOld->Amount );

	if( strlen( txnmsgNew->DispAmount ) == 0 )
		strcpy( txnmsgNew->DispAmount, txnmsgOld->DispAmount );

	if( strlen( txnmsgNew->TxnFee ) == 0 )
		strcpy( txnmsgNew->TxnFee, txnmsgOld->TxnFee );

	if( strlen( txnmsgNew->FromAccount ) == 0 )
		strcpy( txnmsgNew->FromAccount, txnmsgOld->FromAccount );

	if( strlen( txnmsgNew->ToAccount ) == 0 )
		strcpy( txnmsgNew->ToAccount, txnmsgOld->FromAccount );

	if( strlen( txnmsgNew->AvailBalance ) == 0 )
		strcpy( txnmsgNew->AvailBalance, txnmsgOld->AvailBalance );

	if( strlen( txnmsgNew->LedgerBalance ) == 0 )
		strcpy( txnmsgNew->LedgerBalance, txnmsgOld->LedgerBalance );

	if( strlen( txnmsgNew->RefNum ) == 0 )
		strcpy( txnmsgNew->RefNum, txnmsgOld->RefNum );

	if( strlen( txnmsgNew->BatchId ) == 0 )
		strcpy( txnmsgNew->BatchId, txnmsgOld->BatchId );

	if( strlen( txnmsgNew->AuthNum ) == 0 )
		strcpy( txnmsgNew->AuthNum, txnmsgOld->AuthNum );

	if( strlen( txnmsgNew->PINBlock ) == 0 )
		strcpy( txnmsgNew->PINBlock, txnmsgOld->PINBlock );

	if( strlen( txnmsgNew->NewPINBlock ) == 0 )
		strcpy( txnmsgNew->NewPINBlock, txnmsgOld->NewPINBlock );

	if( strlen( txnmsgNew->PinKey ) == 0 )
		strcpy( txnmsgNew->PinKey, txnmsgOld->PinKey );

	if( txnmsgNew->Keylen == 0 )
		txnmsgNew->Keylen = txnmsgOld->Keylen;

	if( strlen( txnmsgNew->AcceptorName ) == 0 )
		strcpy( txnmsgNew->AcceptorName, txnmsgOld->AcceptorName );

	if( strlen( txnmsgNew->AcquirerInst ) == 0 )
		strcpy( txnmsgNew->AcquirerInst, txnmsgOld->AcquirerInst );

	if( strlen( txnmsgNew->IssuerInst ) == 0 )
		strcpy( txnmsgNew->IssuerInst, txnmsgOld->IssuerInst );

	if( strlen( txnmsgNew->ForwardInst ) == 0 )
		strcpy( txnmsgNew->ForwardInst, txnmsgOld->ForwardInst );

	if( strlen( txnmsgNew->TxfInst ) == 0 )
			strcpy( txnmsgNew->TxfInst, txnmsgOld->TxfInst );

	if( strlen( txnmsgNew->SettInst ) == 0 )
		strcpy( txnmsgNew->SettInst, txnmsgOld->SettInst );

	if( strlen( txnmsgNew->AcquirerBin ) == 0 )
			strcpy( txnmsgNew->AcquirerBin, txnmsgOld->AcquirerBin );

	if( strlen( txnmsgNew->IssuerBin ) == 0 )
		strcpy( txnmsgNew->IssuerBin, txnmsgOld->IssuerBin );

	if( strlen( txnmsgNew->ForwardBin ) == 0 )
		strcpy( txnmsgNew->ForwardBin, txnmsgOld->ForwardBin );

	if( strlen( txnmsgNew->TxfBin ) == 0 )
		strcpy( txnmsgNew->TxfBin, txnmsgOld->TxfBin );

	if( strlen( txnmsgNew->SettBin ) == 0 )
		strcpy( txnmsgNew->SettBin, txnmsgOld->SettBin );

	if( strlen( txnmsgNew->NetworkId ) == 0 )
		strcpy( txnmsgNew->NetworkId, txnmsgOld->NetworkId );

	if( strlen( txnmsgNew->AcqNetworkId ) == 0 )
		strcpy( txnmsgNew->AcqNetworkId, txnmsgOld->AcqNetworkId );

	if( strlen( txnmsgNew->IssuerNetworkId ) == 0 )
		strcpy( txnmsgNew->IssuerNetworkId, txnmsgOld->IssuerNetworkId );

	if( strlen( txnmsgNew->FwdNetworkId ) == 0 )
		strcpy( txnmsgNew->FwdNetworkId, txnmsgOld->FwdNetworkId );

	if( strlen( txnmsgNew->TxfNetworkId ) == 0 )
		strcpy( txnmsgNew->TxfNetworkId, txnmsgOld->TxfNetworkId );

	if( strlen( txnmsgNew->SettNetworkId ) == 0 )
		strcpy( txnmsgNew->SettNetworkId, txnmsgOld->SettNetworkId );

	if( txnmsgNew->NetCode == 0 )
		txnmsgNew->NetCode = txnmsgOld->NetCode;

	if( strlen( txnmsgNew->SecurityId ) == 0 )
		strcpy( txnmsgNew->SecurityId, txnmsgOld->SecurityId );

	if( strlen( txnmsgNew->Track2 ) == 0 )
		strcpy( txnmsgNew->Track2, txnmsgOld->Track2 );

	if( strlen( txnmsgNew->RsvFld1 ) == 0 )
		strcpy( txnmsgNew->RsvFld1, txnmsgOld->RsvFld1 );

	if( strlen( txnmsgNew->RsvFld2 ) == 0 )
		strcpy( txnmsgNew->RsvFld2, txnmsgOld->RsvFld2 );

	if( strlen( txnmsgNew->RsvFld3 ) == 0 )
		strcpy( txnmsgNew->RsvFld3, txnmsgOld->RsvFld3 );

	if( strlen( txnmsgNew->RsvFld4 ) == 0 )
		strcpy( txnmsgNew->RsvFld4, txnmsgOld->RsvFld4 );

	if( strlen( txnmsgNew->RsvFld5 ) == 0 )
		strcpy( txnmsgNew->RsvFld5, txnmsgOld->RsvFld5 );

	if( strlen( txnmsgNew->RsvFld6 ) == 0 )
		strcpy( txnmsgNew->RsvFld6, txnmsgOld->RsvFld6 );

	if( strlen( txnmsgNew->SrcChannel ) == 0 )
		strcpy( txnmsgNew->SrcChannel, txnmsgOld->SrcChannel );

	if( strlen( txnmsgNew->SrcPort ) == 0 )
		strcpy( txnmsgNew->SrcPort, txnmsgOld->SrcPort );

	if( strlen( txnmsgNew->OrgChannel ) == 0 )
		strcpy( txnmsgNew->OrgChannel, txnmsgOld->OrgChannel );

	if( strlen( txnmsgNew->OrgPort ) == 0 )
		strcpy( txnmsgNew->OrgPort, txnmsgOld->OrgPort );

	if( strlen( txnmsgNew->DestPort ) == 0 )
		strcpy( txnmsgNew->DestPort, txnmsgOld->DestPort );

	if( strlen( txnmsgNew->RespFile ) == 0 )
		strcpy( txnmsgNew->RespFile, txnmsgOld->RespFile );
}

void EzSafWriter :: ServiceRequest()
{
	struct EzTxnMsg txnmsg, localtxnmsg;
	int MsgSize, retval, RefSeqNo;
	char NetworkStatus[ 50 ], SafAction;
	struct EzReplayTable replaytable_rec;
	struct EzSafDBInfo safdbinfo;

	while( 1 )
	{
		trace( "EzSafWriter Waiting For Request....");

		dbUtilClose();

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

		if( ReadMessage( ( char * ) &txnmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message From EzSafWriter Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			sleep( 1 );
			continue;
		}

		trace( DEBUG_NORMAL, "Message Received From Channel[%s] with MsgType[%d]", GetLastSenderChannelName(), txnmsg.MsgType );

		if( dbUtilConnect() < 0 )
			continue;

		if( isSafRequest( txnmsg.MsgType ) )
		{
			memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );

			if( readNetworkMemory( txnmsg.NetworkId ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from Network Memory", txnmsg.NetworkId );
				continue;
			}

			memset( safdbinfo.NetworkId, 0, sizeof( safdbinfo.NetworkId ) );
			strcpy( safdbinfo.NetworkId, txnmsg.NetworkId );

			memset( safdbinfo.TxnRefNum, 0, sizeof( safdbinfo.TxnRefNum  ) );
			if( eztxnrefselectutil.getTxnRefNum( &txnmsg, safdbinfo.TxnRefNum ) < 0 )
			{
				trace( "Error in Getting TenRefNum from EzTxnRefSelect Table for MsgType[%d] TxnCode[%d] TraceNo[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.TraceNo );
				continue;
			}

			trace( DEBUG_NORMAL, "Got TxnRefNum[%s] from EzTxnRefSelect Table for MsgType[%d] TxnCode[%d] TraceNo[%d]", safdbinfo.TxnRefNum, txnmsg.MsgType, txnmsg.TxnCode, txnmsg.TraceNo );
			trace( DEBUG_NORMAL, "Received Request From EzTxnMgr for NetworkId[%s]", txnmsg.NetworkId );

			retval = readTxnRefNum( safdbinfo.TxnRefNum, txnmsg.NetworkId );

			if( EZLINK_ORA_CONNECT_ERR( retval ) )
			{
				if( DBConnect() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					continue;
				}
				retval = readTxnRefNum( safdbinfo.TxnRefNum, txnmsg.NetworkId );
			}

			if( retval == 0 )
			{
				trace( DEBUG_ERROR, "TxnRefNum[%s] for NetworkId[%s] is already inserted in the EzSafDB Table...", safdbinfo.TxnRefNum, txnmsg.NetworkId );
				continue;
			}

			memset( safdbinfo.SafRecordNo, 0, sizeof( safdbinfo.SafRecordNo ) );
			retval = eztxnsequtil.genSafRecordNo( safdbinfo.SafRecordNo );
			trace( DEBUG_NORMAL, "Generated SafRecordNo[%s]", safdbinfo.SafRecordNo );

			memset( safdbinfo.SAFDetailRec, 0, sizeof( safdbinfo.SAFDetailRec ) );
			ezsafformatutil.composeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

			memset( safdbinfo.TranDate, 0, sizeof( safdbinfo.TranDate ) );
			sprintf( safdbinfo.TranDate, "%06d", txnmsg.TranDate );
			memset( safdbinfo.TranTime, 0, sizeof( safdbinfo.TranTime ) );
			sprintf( safdbinfo.TranTime, "%06d", txnmsg.TranTime );

			if( getNetworkStatus() == NETWORK_STATUS_SAF || getNetworkStatus() == NETWORK_STATUS_SAFDOWNLOAD )
				safdbinfo.SafIndicator = SAF_STANDIN;
			else
				safdbinfo.SafIndicator = SAF_ONLINE;

			safdbinfo.SafStatus = SAF_STATUS_PENDING;
			safdbinfo.SafResponseIndicator = SAF_RESPONSE_NOTRCVD;
			safdbinfo.SafResponse = 0;
			safdbinfo.SafRepeatIndicator = SAF_REPEAT_DISABLE;
			safdbinfo.TimeOutCount = 0;

			retval = insertSafRecord( safdbinfo );

			if( EZLINK_ORA_CONNECT_ERR( retval ) )
			{
				if( DBConnect() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					insertToFile( safdbinfo );
					continue;
				}
				retval = insertSafRecord( safdbinfo );
			}

			if( retval != 0 )
			{
				trace( DEBUG_ERROR, "Error in Inserting EzSafDB Table for SafRecordNo[%s] TranDate[%s] TranTime[%s] NetworkId[%s] SafStatus[%c] SafIndicator[%c] SafResponseIndicator[%c] SafResponse[%d] TxnRefNum[%s] SafDetRec[%s] ORAERR[%05d]", safdbinfo.SafRecordNo, safdbinfo.TranDate, safdbinfo.TranTime, safdbinfo.NetworkId, safdbinfo.SafStatus, safdbinfo.SafIndicator, safdbinfo.SafResponseIndicator, safdbinfo.SafResponse, safdbinfo.TxnRefNum, safdbinfo.SAFDetailRec, retval );
				insertToFile( safdbinfo );
				continue;
			}
			else
				trace( DEBUG_NORMAL, "Inserted Record Successfully in EzSafDB Table with NetworkId[%s] SafRecordNo[%s] SafIndicator[%c]", txnmsg.NetworkId, safdbinfo.SafRecordNo, safdbinfo.SafIndicator );

			if( ezreplayutil.readReplayTable( txnmsg.NetworkId, &replaytable_rec ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading ReplayTable for NetworkId[%s]", txnmsg.NetworkId );
				continue;
			}

			if( replaytable_rec.ReplayStatus == REPLAY_STATUS_IDLE )
			{
				trace( DEBUG_NORMAL, "NetworkId[%s] is in Idle State..Sending Intimation Message to EzSafReader", txnmsg.NetworkId );
				txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
				if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
					trace( DEBUG_ERROR, "Error in Writing Network Intimation Message to EzSafReader" );
				else
					trace( DEBUG_ERROR, "Written Network Intimation Message to EzSafReader for NetworkId[%s]", txnmsg.NetworkId );
			}
		}
		else if( isSafResponse( txnmsg.MsgType ) )
		{
			trace( DEBUG_TEST, "Received Saf Response Message....");

			memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );

			txnmsg.MsgType -= 10;
			memset( safdbinfo.TxnRefNum, 0, sizeof( safdbinfo.TxnRefNum  ) );
			if( eztxnrefselectutil.getTxnRefNum( &txnmsg, safdbinfo.TxnRefNum ) < 0 )
			{
				trace( "Error in Getting TenRefNum from EzTxnRefSelect Table for MsgType[%d] TxnCode[%d] TraceNo[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.TraceNo );
				continue;
			}

			trace( DEBUG_NORMAL, "Got TxnRefNum[%s] from EzTxnRefSelect Table for MsgType[%d] TxnCode[%d] TraceNo[%d]", safdbinfo.TxnRefNum, txnmsg.MsgType, txnmsg.TxnCode, txnmsg.TraceNo );

			retval = readSafDBInfo( safdbinfo.TxnRefNum, &safdbinfo );

			if( EZLINK_ORA_CONNECT_ERR( retval ) )
			{
				if( DBConnect() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					continue;
				}
				retval = readSafDBInfo( safdbinfo.TxnRefNum, &safdbinfo );
			}

			if( retval != 0 )
			{
				trace( "Error in Reading TxnRefNum[%s] from EzSafDB Table ORAERR[%05d]", safdbinfo.TxnRefNum, retval );
				continue;
			}

			memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
			ezsafformatutil.decomposeSAFDetailedRec( &localtxnmsg, safdbinfo.SAFDetailRec );

			if( strlen(txnmsg.IssuerInst) == 0 )
			{
				memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
				strcpy( txnmsg.IssuerInst, localtxnmsg.IssuerInst );
			}
			if( strlen( txnmsg.NetworkId ) == 0)
			{
				memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
				strcpy( txnmsg.NetworkId, localtxnmsg.NetworkId );
			}

			trace( "Read TxnRefNum[%s] with SafRecordNo[%s] SafIndicator[%c] InstId[%s] NetworkId[%s] RespCode[%d] RevCode[%d] from EzSafDB Table", safdbinfo.TxnRefNum, safdbinfo.SafRecordNo, safdbinfo.SafIndicator, txnmsg.IssuerInst, txnmsg.NetworkId, localtxnmsg.RespCode, localtxnmsg.RevCode );

			if( safdbinfo.SafIndicator == SAF_STANDIN )
				trace( DEBUG_NORMAL, "TxnRefNum[%s] with SafRecordNo[%s] for NetworkId[%s] generated during SAF Mode", safdbinfo.TxnRefNum, safdbinfo.SafRecordNo, txnmsg.NetworkId );
			else
				trace( DEBUG_NORMAL, "TxnRefNum[%s] with SafRecordNo[%s] for NetworkId[%s] generated during Online Mode", safdbinfo.TxnRefNum, safdbinfo.SafRecordNo, txnmsg.NetworkId );

			txnmsg.MsgType += 10;

			if( txnmsg.RespCode == EZLINK_RC_Approved )
			{
				trace( DEBUG_NORMAL, "Good Response Received for TxnRefNum[%s] with SafRecordNo[%s] for NetworkId[%s]", safdbinfo.TxnRefNum, safdbinfo.SafRecordNo, txnmsg.NetworkId );
				retval = deleteEzSafDB( safdbinfo.TxnRefNum );
				if( EZLINK_ORA_CONNECT_ERR( retval ) )
				{
					if( DBConnect() < 0 )
					{
						trace( "Error in Connecting with Switch Database...." );
						continue;
					}
					else
						retval = deleteEzSafDB( safdbinfo.TxnRefNum );
				}

				if( retval != 0 )
					trace( DEBUG_ERROR, "Error in deleting TxnRefNum[%s] from EzSafDB Table ORAERR[%05d]", safdbinfo.TxnRefNum, retval );
				else
					trace( DEBUG_NORMAL, "Deleted Record with SafRecordNo[%s] for NetworkId[%s] TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, safdbinfo.TxnRefNum );

				populateTxnMsg( &txnmsg, &localtxnmsg );

				memset( safdbinfo.SAFDetailRec, 0, sizeof( safdbinfo.SAFDetailRec ) );
				ezsafformatutil.composeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

				retval = insertEzSafHist( safdbinfo );

				if( EZLINK_ORA_CONNECT_ERR( retval ) )
				{
					if( DBConnect() < 0 )
					{
						trace( "Error in Connecting with Switch Database...." );
						continue;
					}
					else
						retval = insertEzSafHist( safdbinfo );
				}

				if( retval != 0 )
					trace( DEBUG_ERROR, "Error in Inserting EzSafHist Table for SafRecordNo[%s] TranDate[%s] TranTime[%s] NetworkId[%s] SafStatus[%c] SafIndicator[%c] SafResponseIndicator[%c] SafResponse[%d] TxnRefNum[%s] SafDetRec[%s] ORAERR[%05d]", safdbinfo.SafRecordNo, safdbinfo.TranDate, safdbinfo.TranTime, safdbinfo.NetworkId, safdbinfo.SafStatus, safdbinfo.SafIndicator, safdbinfo.SafResponseIndicator, safdbinfo.SafResponse, safdbinfo.TxnRefNum, safdbinfo.SAFDetailRec, retval );
				else
					trace( DEBUG_NORMAL, "Inserted SafRecordNo[%s] NetworkId[%s] TxnRefNum[%s] in EzSafHist Table", safdbinfo.SafRecordNo, txnmsg.NetworkId, safdbinfo.TxnRefNum );

				memset( txnmsg.SrcPort, 0, sizeof( txnmsg.SrcPort ) );
				strcpy( txnmsg.SrcPort, getNetworkPortName() );
				memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
				strcpy( txnmsg.DestPort, "*" );

				if( eztxnmsgorderutil.readTxnMsgOrder( getNetworkChannelName(), GetSourceChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode ) < 0 )
				{
					trace( DEBUG_NORMAL, "Error in reading SrcChannel[%s] DestChannel[%s] MsgType[%04d] TxnCode[%06d] RespCode[%03d] from TxnMsgOrder....assigning RefSeqNo as 1...", getNetworkChannelName(), GetSourceChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode );
					RefSeqNo = 1;
				}
				else
					RefSeqNo = eztxnmsgorderutil.getTxnMsgOrderNo();

				if( eztxnlogutil.insertTxnLog( &txnmsg, safdbinfo.TxnRefNum, getNetworkChannelName(), GetSourceChannelName(), RefSeqNo ) < 0 )
					trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
			}
			else
			{
				trace( DEBUG_NORMAL, "Bad Response with RespCode[%d] Received for TxnRefNum[%s] RevCode[%d] with SafRecordNo[%s] for NetworkId[%s]", txnmsg.RespCode, safdbinfo.TxnRefNum, txnmsg.RevCode, safdbinfo.SafRecordNo, txnmsg.NetworkId );

				memset( NetworkStatus, 0, sizeof( NetworkStatus ) );

				if( safdbinfo.SafIndicator == SAF_STANDIN )
					strcpy( NetworkStatus, "SAF" );
				else
					strcpy( NetworkStatus, "ONLINE" );

				if( ezsafpropertyutil.readSafProperty( SAF_RESPONSE, txnmsg.IssuerInst, txnmsg.NetworkId, NetworkStatus, txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode, txnmsg.RevCode, &SafAction ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Reading EzSafProperty for IssuerInst[%s] NetworkId[%s] NetworkStatus[%s] MsgType[%04d] TxnCode[%06d] RespCode[%03d] RevCode[%d]", txnmsg.IssuerInst, txnmsg.NetworkId, NetworkStatus, txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode, txnmsg.RevCode );
					continue;
				}
				else
					trace( "Reading EzSafProperty for IssuerInst[%s] NetworkId[%s] NetworkStatus[%s] MsgType[%04d] TxnCode[%06d] RespCode[%03d] RevCode[%d] -- SafAction[%c]", txnmsg.IssuerInst, txnmsg.NetworkId, NetworkStatus, txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode, txnmsg.RevCode, SafAction );

				switch ( SafAction )
				{
					case SAF_RESPONSE_REMOVE_RECORD:

					retval = deleteEzSafDB( safdbinfo.TxnRefNum );

					if( EZLINK_ORA_CONNECT_ERR( retval ) )
					{
						if( DBConnect() < 0 )
						{
							trace( "Error in Connecting with Switch Database...." );
							break;
						}
						else
							retval = deleteEzSafDB( safdbinfo.TxnRefNum );
					}

					if( retval != 0 )
						trace( DEBUG_ERROR, "Error in deleting TxnRefNum[%s] from EzSafDB Table ORAERR[%05d]", safdbinfo.TxnRefNum, retval );
					else
						trace( DEBUG_NORMAL, "Deleted Record with SafRecordNo[%s] for NetworkId[%s] TxnRefNum[%s]", safdbinfo.SafRecordNo, txnmsg.NetworkId, safdbinfo.TxnRefNum );

					populateTxnMsg( &txnmsg, &localtxnmsg );

					memset( safdbinfo.SAFDetailRec, 0, sizeof( safdbinfo.SAFDetailRec ) );
					ezsafformatutil.composeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );

					retval = insertEzSafHist( safdbinfo );

					if( EZLINK_ORA_CONNECT_ERR( retval ) )
					{
						if( DBConnect() < 0 )
						{
							trace( "Error in Connecting with Switch Database...." );
							break;
						}
						else
							retval = insertEzSafHist( safdbinfo );
					}

					if( retval != 0 )
						trace( DEBUG_ERROR, "Error in Inserting SafRecordNo[%s] NetworkId[%s] TxnRefNum[%s] in EzSafHist Table ORAERR[%05d]", safdbinfo.SafRecordNo, txnmsg.NetworkId, safdbinfo.TxnRefNum, retval );
					else
						trace( DEBUG_NORMAL, "Inserted SafRecordNo[%s] NetworkId[%s] TxnRefNum[%s] in EzSafHist Table", safdbinfo.SafRecordNo, txnmsg.NetworkId, safdbinfo.TxnRefNum );

					memset( txnmsg.SrcPort, 0, sizeof( txnmsg.SrcPort ) );
					strcpy( txnmsg.SrcPort, getNetworkPortName() );
					memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
					strcpy( txnmsg.DestPort, "*" );

					if( eztxnmsgorderutil.readTxnMsgOrder( getNetworkChannelName(), GetSourceChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode ) < 0 )
					{
						trace( DEBUG_NORMAL, "Error in reading SrcChannel[%s] DestChannel[%s] MsgType[%04d] TxnCode[%06d] RespCode[%03d] from TxnMsgOrder....assigning RefSeqNo as 1...", getNetworkChannelName(), GetSourceChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode );
						RefSeqNo = 1;
					}
					else
						RefSeqNo = eztxnmsgorderutil.getTxnMsgOrderNo();

					if( eztxnlogutil.insertTxnLog( &txnmsg, safdbinfo.TxnRefNum, getNetworkChannelName(), GetSourceChannelName(), RefSeqNo ) < 0 )
						trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
					break;

					case SAF_RESPONSE_REPLAY_RECORD:

					retval = updateSafResponse( safdbinfo.TxnRefNum, SAF_RESPONSE_RCVD, txnmsg.RespCode );

					if( EZLINK_ORA_CONNECT_ERR( retval ) )
					{
						if( DBConnect() < 0 )
						{
							trace( "Error in Connecting with Switch Database...." );
							break;
						}
						else
							retval = updateSafResponse( safdbinfo.TxnRefNum, SAF_RESPONSE_RCVD, txnmsg.RespCode );
					}

					if( retval != 0 )
						trace( DEBUG_ERROR, "Error in Updating Saf Response for TxnRefNum[%s] ORAERR[%05d]", safdbinfo.TxnRefNum, retval );
					else
						trace( DEBUG_NORMAL, "Updated Saf Response for TxnRefNum[%s]", safdbinfo.TxnRefNum );

					break;

					case SAF_RESPONSE_CHANGESTATUS:

					retval = updateSafStatus( safdbinfo.TxnRefNum, SAF_STATUS_SKIP, SAF_RESPONSE_RCVD, txnmsg.RespCode );

					if( EZLINK_ORA_CONNECT_ERR( retval ) )
					{
						if( DBConnect() < 0 )
						{
							trace( "Error in Connecting with Switch Database...." );
							break;
						}
						else
							retval = updateSafStatus( safdbinfo.TxnRefNum, SAF_STATUS_SKIP, SAF_RESPONSE_RCVD, txnmsg.RespCode );
					}
					if( retval != 0 )
						trace( DEBUG_ERROR, "Error in Updating SAF_STATUS_BADRESPONSE for TxnRefNum[%s] ORAERR[%05d]", safdbinfo.TxnRefNum, retval );
					else
						trace( DEBUG_NORMAL, "Updated SAF_STATUS_BADRESPONSE as SKIP for TxnRefNum[%s] ORAERR[%05d]", safdbinfo.TxnRefNum );

					break;
				}
			}
			if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
				trace( DEBUG_ERROR, "Error in Writing SAF Response Message to EzSafReader" );
			else
				trace( DEBUG_ERROR, "Written SAF Response Message to EzSafReader for NetworkId[%s]", txnmsg.NetworkId );
		}
		else
		{
			trace( DEBUG_ERROR, "Invalid Message Received ....Dropping Message" );
		}
	}
}

int EzSafWriter :: readTxnRefNum( const char *I_TxnRefNum, const char *I_NetworkId )
{
	char NetworkId[ 17 ];
	char TxnRefNum[ 151 ];
	int i = 0, retval = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(NETWORKID), RTRIM(TXNREFNUM) FROM EZSAFDB WHERE RTRIM(TXNREFNUM)='%s' AND RTRIM(NETWORKID)='%s';", I_TxnRefNum, I_NetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("<%s>", SqlStmt );
		trace( DEBUG_ERROR, "Error in Executing NetworkId in readTxnRefNum [ %d ]", odbcret );
		//getNativeErrorCode();
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

    memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );

	odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TxnRefNum, sizeof(TxnRefNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TxnRefNum) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
    	trace("TxnRefNum[%s]", TxnRefNum);
        if(strlen(TxnRefNum) == 0 )
        	retval = -1;
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzSafWriter :: readSafDBInfo( const char *I_TxnRefNum, struct EzSafDBInfo *safdbinfo_ptr )
{
	char SafRecordNo[ 21 ];
	char TranDate[ 7 ];
	char TranTime[ 7 ];
	char NetworkId[ 17 ];
	char SafStatus;
	char SafIndicator;
	char SafResponseIndicator;
	char SafRepeatIndicator;
	int SafResponse;
	int TimeOutCount;
	char TxnRefNum[ 151 ];
	char SAFDetailRec[ 2049 ];
	int i = 0, retval = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
        return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(SAFRECORDNO),\
		RTRIM(TRANDATE),\
		RTRIM(TRANTIME),\
		RTRIM(NETWORKID),\
		SAFSTATUS,\
		SAFINDICATOR,\
		SAFRESPONSEINDICATOR,\
		SAFREPEATINDICATOR,\
		SAFRESPONSE,\
		TIMEOUTCOUNT,\
		RTRIM(SAFDETREC)\
		FROM EZSAFDB WHERE RTRIM(TXNREFNUM)='%s';", I_TxnRefNum );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("<%s>", SqlStmt );
		trace( DEBUG_ERROR, "Error in Executing NetworkId in readTxnRefNum [ %d ]", odbcret );
		//getNativeErrorCode();
		SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
		return -1;
    }

	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( TranTime, 0, sizeof( TranTime ) );
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( SAFDetailRec, 0, sizeof( SAFDetailRec ) );

	odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, SafRecordNo, sizeof(SafRecordNo), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafRecordNo) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, TranDate, sizeof(TranDate), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TranDate) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

	odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, TranTime, sizeof(TranTime), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TranTime) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &SafStatus, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafStatus) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

	odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &SafIndicator, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafIndicator) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_BINARY, &SafResponseIndicator, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafResponseIndicator) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

	odbcret = SQLBindCol( hstmt, 8, SQL_C_BINARY, &SafRepeatIndicator, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafRepeatIndicator) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &SafResponse, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SafResponse) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &TimeOutCount, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TxnRefNum) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_CHAR, TxnRefNum, sizeof(TxnRefNum), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(TxnRefNum) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, SAFDetailRec, sizeof(SAFDetailRec), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace( DEBUG_ERROR, "Error in Binding Column(SAFDetailRec) in EZSAFDB [ %d ]", odbcret );
        SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
        return -1;
    }

    if( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        strcpy( safdbinfo_ptr->SafRecordNo, SafRecordNo );
        strcpy( safdbinfo_ptr->TranDate, TranDate );
        strcpy( safdbinfo_ptr->TranTime, TranTime );
        strcpy( safdbinfo_ptr->NetworkId, NetworkId );
        safdbinfo_ptr->SafStatus = SafStatus;
       	safdbinfo_ptr->SafIndicator = SafIndicator;
       	safdbinfo_ptr->SafResponseIndicator = SafResponseIndicator;
       	safdbinfo_ptr->SafRepeatIndicator = SafRepeatIndicator;
       	safdbinfo_ptr->SafResponse = SafResponse;
       	safdbinfo_ptr->TimeOutCount = TimeOutCount;
       	strcpy( safdbinfo_ptr->SAFDetailRec, SAFDetailRec );
       	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
       	return 0;
    }
    else
    {
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
}

int EzSafWriter :: deleteEzSafDB( const char *I_TxnRefNum )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "DELETE FROM EZSAFDB WHERE RTRIM(TXNREFNUM)='%s';", I_TxnRefNum );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafWriter :: updateSafResponse( const char *I_TxnRefNum, char I_SafResponseFlag, int I_SafResponse )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZSAFDB SET SAFRESPONSEINDICATOR = '%c', SAFRESPONSE = '%d' WHERE RTRIM(TXNREFNUM)='%s';", I_SafResponseFlag, I_SafResponse, I_TxnRefNum );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafWriter :: updateSafStatus( const char *I_TxnRefNum, char SafStatus, char I_SafResponseFlag, int I_SafResponse )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZSAFDB SET SAFSTATUS = '%c', SAFRESPONSEINDICATOR = '%c', SAFRESPONSE = '%d' WHERE RTRIM(TXNREFNUM)='%s';", SafStatus, I_SafResponseFlag, I_SafResponse, I_TxnRefNum );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafWriter :: updateSafRepeatIndicator( const char *I_NetworkId, const char *I_TxnRefNum, char I_SafRepeatIndicator )
{
    char SqlStmt[ 255 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "UPDATE EZSAFDB SET SAFREPEATINDICATOR = '%c' WHERE RTRIM(TXNREFNUM)='%s' AND RTRIM(NETWORKID)='%s';", I_SafRepeatIndicator, I_TxnRefNum, I_NetworkId );
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafWriter :: insertSafRecord( struct EzSafDBInfo safdbinfo )
{
    char SqlStmt[ 3500 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "INSERT INTO EZSAFDB \
	( \
		SAFRECORDNO,\
		TRANDATE,\
		TRANTIME,\
		NETWORKID,\
		SAFSTATUS,\
		SAFINDICATOR,\
		SAFRESPONSEINDICATOR,\
		SAFREPEATINDICATOR,\
		SAFRESPONSE,\
		TIMEOUTCOUNT,\
		TXNREFNUM,\
		SAFDETREC\
	)\
	VALUES ( '%s', '%s', '%s', '%s', '%c', '%c', '%c', '%c', %d, %d, '%s', '%s' );", \
		safdbinfo.SafRecordNo,
		safdbinfo.TranDate,
		safdbinfo.TranTime,
		safdbinfo.NetworkId,
		safdbinfo.SafStatus,
		safdbinfo.SafIndicator,
		safdbinfo.SafResponseIndicator,
		safdbinfo.SafRepeatIndicator,
		safdbinfo.TimeOutCount,
		safdbinfo.SafResponse,
		safdbinfo.TxnRefNum,
		safdbinfo.SAFDetailRec);
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int EzSafWriter :: insertEzSafHist( struct EzSafDBInfo safdbinfo )
{
    char SqlStmt[ 3500 ];

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt, "INSERT INTO EZSAFHIST \
	( \
		SAFRECORDNO,\
		TRANDATE,\
		TRANTIME,\
		NETWORKID,\
		SAFINDICATOR,\
		SAFRESPONSEINDICATOR,\
		SAFRESPONSE,\
		TXNREFNUM,\
		SAFDETREC,\
    	TIMEOUTCOUNT\
	)\
	VALUES ( '%s', '%s', '%s', '%s', '%c', '%c', %d, '%s', '%s', %d );", \
		safdbinfo.SafRecordNo,
		safdbinfo.TranDate,
		safdbinfo.TranTime,
		safdbinfo.NetworkId,
		safdbinfo.SafIndicator,
		safdbinfo.SafResponseIndicator,
		safdbinfo.SafResponse,
		safdbinfo.TxnRefNum,
		safdbinfo.SAFDetailRec,
		safdbinfo.TimeOutCount);
    if( ExecuteQuery( SqlStmt, true ) < 0 )
    	return -1;
	return 0;
}

int main( int argc, char **argv )
{
	EzSafWriter safwriterobj;
	safwriterobj.initSafWriter( argv[ 0 ] );
	safwriterobj.ServiceRequest();
	return 1;
}
