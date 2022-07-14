#include <ezmms/ezmmssim.h>

void EzMMSSim :: initMMSSim( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmmssim.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzChannelUtil( this ) < 0 )
	{
		printf( "\nError in Initializing EzChannelUtil...\n" );
		trace( "Error in Initializing EzChannelUtil" );
    	trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^" );
    	closeDebug();
    	exit( 0 );
    }

	if( CreateChannel( "EzMMSSim", TaskName ) < 0 )
	{
		printf( "\nError in Creating Channel EzMMS...\n" );
		trace( "Error in Creating Channel EzMMS" );
    	trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^" );
    	closeDebug();
    	exit( 0 );
    }
}

void EzMMSSim :: composeRequest( struct EzTxnMsg *txnmsg )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezmmssim.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		printf("\nError in opening file[%s]...\n", cfgpath );
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MSGTYPE", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching MSGTYPE from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	txnmsg->MsgType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ORGMSGTYPE", cfgval, 2 ) < 0 )
		txnmsg->OrgMsgType = txnmsg->MsgType;
	else
		txnmsg->OrgMsgType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXNCODE", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching TXNCODE from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	txnmsg->TxnCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TERMID", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching TERMID from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	strcpy( txnmsg->TerminalId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "CHANNELNAME", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching CHANNELNAME from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	strcpy( txnmsg->DestPort, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TERMLOC", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching TERMLOC from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	strcpy( txnmsg->TerminalLocation, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TRACENO", cfgval, 2 ) < 0 )
		txnmsg->TraceNo = dtutil.getSysTime();
	else
		txnmsg->TraceNo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ORGTRACENO", cfgval, 2 ) < 0 )
		txnmsg->OrgTraceNo = txnmsg->TraceNo;
	else
		txnmsg->OrgTraceNo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TRANDATE", cfgval, 2 ) < 0 )
		txnmsg->TranDate = dtutil.getSysDate();
	else
		txnmsg->TranDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TRANTIME", cfgval, 2 ) < 0 )
		txnmsg->TranTime = dtutil.getSysTime();
	else
		txnmsg->TranTime = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ORGTRANDATE", cfgval, 2 ) < 0 )
		txnmsg->OrgTranDate = txnmsg->TranDate;
	else
		txnmsg->OrgTranDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ORGTRANTIME", cfgval, 2 ) < 0 )
		txnmsg->OrgTranTime = txnmsg->TranTime;
	else
		txnmsg->OrgTranTime = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "LOCALDATE", cfgval, 2 ) < 0 )
		txnmsg->LocalDate = dtutil.getSysDate();
	else
		txnmsg->LocalDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "LOCALTIME", cfgval, 2 ) < 0 )
		txnmsg->LocalTime = dtutil.getSysTime();
	else
		txnmsg->LocalTime = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "EXPIRYDATE", cfgval, 2 ) < 0 )
		txnmsg->ExpiryDate = dtutil.getSysDate();
	else
		txnmsg->ExpiryDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RESPCODE", cfgval, 2 ) < 0 )
		txnmsg->RespCode = 0;
	else
		txnmsg->RespCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REVCODE", cfgval, 2 ) < 0 )
		txnmsg->RevCode = 0;
	else
		txnmsg->RevCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REASONCODE", cfgval, 2 ) < 0 )
		txnmsg->ReasonCode = 0;
	else
		txnmsg->ReasonCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AUTHCODE", cfgval, 2 ) < 0 )
		txnmsg->AuthCode = 0;
	else
		txnmsg->AuthCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "CAPTUREDATE", cfgval, 2 ) < 0 )
		txnmsg->CaptureDate = dtutil.getSysDate();
	else
		txnmsg->CaptureDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "CAPTURETIME", cfgval, 2 ) < 0 )
		txnmsg->CaptureTime = dtutil.getSysTime();
	else
		txnmsg->CaptureTime = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTDATE", cfgval, 2 ) < 0 )
		txnmsg->SettlementDate = dtutil.getSysDate();
	else
		txnmsg->SettlementDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "BUSINESSDATE", cfgval, 2 ) < 0 )
		txnmsg->BusinessDate = dtutil.getSysDate();
	else
		txnmsg->BusinessDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCOUNTRYCODE", cfgval, 2 ) < 0 )
		txnmsg->AcqCountryCode = 0;
	else
		txnmsg->AcqCountryCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCOUNTRYCODE", cfgval, 2 ) < 0 )
		txnmsg->IssCountryCode = 0;
	else
		txnmsg->IssCountryCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FWDCOUNTRYCODE", cfgval, 2 ) < 0 )
		txnmsg->FwdCountryCode = 0;
	else
		txnmsg->FwdCountryCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCOUNTRYCODE", cfgval, 2 ) < 0 )
		txnmsg->SettCountryCode = 0;
	else
		txnmsg->SettCountryCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCURRENCYCODE", cfgval, 2 ) < 0 )
		txnmsg->AcqCurrencyCode = 0;
	else
		txnmsg->AcqCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCURRENCYCODE", cfgval, 2 ) < 0 )
		txnmsg->IssCurrencyCode = 0;
	else
		txnmsg->IssCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFCURRENCYCODE", cfgval, 2 ) < 0 )
		txnmsg->TxfCurrencyCode = 0;
	else
		txnmsg->TxfCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCURRENCYCODE", cfgval, 2 ) < 0 )
		txnmsg->SettCurrencyCode = 0;
	else
		txnmsg->SettCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCONVRATE", cfgval, 2 ) < 0 )
		strcpy( txnmsg->AcqConvRate, "0" );
	else
		strcpy( txnmsg->AcqConvRate, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCONVDATE", cfgval, 2 ) < 0 )
		txnmsg->AcqConvDate = dtutil.getSysDate();
	else
		txnmsg->AcqConvDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCONVRATE", cfgval, 2 ) < 0 )
		strcpy( txnmsg->IssConvRate, "0" );
	else
		strcpy( txnmsg->IssConvRate, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCONVDATE", cfgval, 2 ) < 0 )
		txnmsg->IssConvDate = dtutil.getSysDate();
	else
		txnmsg->IssConvDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCONVRATE", cfgval, 2 ) < 0 )
		strcpy( txnmsg->SettConvRate, "0" );
	else
		strcpy( txnmsg->SettConvRate, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCONVDATE", cfgval, 2 ) < 0 )
		txnmsg->SettConvDate = dtutil.getSysDate();
	else
		txnmsg->SettConvDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSENTRYCODE", cfgval, 2 ) < 0 )
		txnmsg->PosEntryCode = 0;
	else
		txnmsg->PosEntryCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSCONDITIONCODE", cfgval, 2 ) < 0 )
		txnmsg->PosConditionCode = 0;
	else
		txnmsg->PosConditionCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSCAPCODE", cfgval, 2 ) < 0 )
		txnmsg->PosCapCode = 0;
	else
		txnmsg->PosCapCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSPINCAPCODE", cfgval, 2 ) < 0 )
		txnmsg->PosPinCapCode = 0;
	else
		txnmsg->PosPinCapCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PINCAPCODE", cfgval, 2 ) < 0 )
		txnmsg->PinCapCode = 0;
	else
		txnmsg->PinCapCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DEVICEFLAG", cfgval, 2 ) < 0 )
		txnmsg->DeviceFlag = 'N';
	else
		txnmsg->DeviceFlag = 'Y';

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MCC", cfgval, 2 ) < 0 )
		txnmsg->MerchantType = 6011;
	else
		txnmsg->MerchantType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DEVICETYPE", cfgval, 2 ) < 0 )
		strcpy( txnmsg->DeviceType, "ATM" );
	else
		strcpy( txnmsg->DeviceType, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "CHN", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching CHN from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->chn, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TRACK2", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching TRACK2 from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->Track2, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AMOUNT", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching AMOUNT from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->Amount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DISPAMOUNT", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching DISPAMOUNT from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->DispAmount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REFNUM", cfgval, 2 ) < 0 )
		sprintf( txnmsg->RefNum, "%06d%06d", dtutil.getSysDate(), dtutil.getSysTime() );
	else
		strcpy( txnmsg->RefNum, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REFNUM", cfgval, 2 ) < 0 )
		strcpy( txnmsg->AuthNum, txnmsg->RefNum );
	else
		strcpy( txnmsg->AuthNum, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MERCHANTID", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching MERCHANTID from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->AcceptorId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PROCESSINST", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching PROCESSINST from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->ProcessInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQINST", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching ACQINST from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->AcquirerInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSINST", cfgval, 2 ) < 0 )
	{
		printf("\nError in Searching ISSINST from File[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	else
		strcpy( txnmsg->IssuerInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FWDINST", cfgval, 2 ) < 0 )
		strcpy( txnmsg->ForwardInst, txnmsg->IssuerInst );
	else
		strcpy( txnmsg->ForwardInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFINST", cfgval, 2 ) < 0 )
		strcpy( txnmsg->TxfInst, txnmsg->IssuerInst );
	else
		strcpy( txnmsg->TxfInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTINST", cfgval, 2 ) < 0 )
		strcpy( txnmsg->SettInst, txnmsg->IssuerInst );
	else
		strcpy( txnmsg->SettInst, cfgval );

	cfgutil.cfg_close();
}

void EzMMSSim :: sendRequest( const char *ChannelName, struct EzTxnMsg *txnmsg )
{
	trace( "Sending Request MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d] to Channel[%s]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->IssuerInst, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->Amount, txnmsg->RespCode, GetLastSenderChannelName() );
	if( WriteChannel( ChannelName, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Response to Channel[%s]", ChannelName );
	else
		trace( "Written Response to Channel[%s]", ChannelName );
}

void EzMMSSim :: waitForResponse( struct EzTxnMsg *txnmsg )
{
	int MsgLen;
	if( ReadMessage( ( char * ) txnmsg, &MsgLen ) < 0 )
	{
		trace( "Error in Reading Message from EzMMSSim Channel" );
		return;
	}
	trace( "Read Message MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->IssuerInst, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->Amount, txnmsg->RespCode );
}

void EzMMSSim :: startSim()
{
	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	composeRequest( &txnmsg );
	sendRequest( txnmsg.DestPort, &txnmsg );
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
	waitForResponse( &txnmsg );
}

int main( int argc, char **argv )
{
	EzMMSSim ezmmssimobj;
	ezmmssimobj.initMMSSim( argv[ 0 ] );
	ezmmssimobj.startSim();
	return 1;
}









