#include <ezlink/eztxnsim.h>

void EzTxnSim :: initTxnSim( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztxnsim.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
    	trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	exit(0);
	}

	if( CreateChannel( "EzTxnSim" ) < 0 )
	{
		trace( "Error in Creating Channel EzTxnSim" );
    	trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	exit(0);
    }

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eztxnsim.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	memset( &txnmsg, 0, sizeof( EzTxnMsg ) );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MSGTYPE", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching MSGTYPE from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	txnmsg.MsgType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ORGMSGTYPE", cfgval, 2 ) < 0 )
		txnmsg.OrgMsgType = 0;
	else
		txnmsg.OrgMsgType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXNCODE", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching TXNCODE from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	txnmsg.TxnCode = atoi( cfgval );


	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TERMID", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching TERMID from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	memset( txnmsg.TerminalId, 0, sizeof( txnmsg.TerminalId ) );
	strcpy( txnmsg.TerminalId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TERMLOC", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching TERMLOC from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	memset( txnmsg.TerminalLocation, 0, sizeof( txnmsg.TerminalLocation ) );
	strcpy( txnmsg.TerminalLocation, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TRACENO", cfgval, 2 ) < 0 )
		txnmsg.TraceNo = 1;
	else
		txnmsg.TraceNo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ORGTRACENO", cfgval, 2 ) < 0 )
		txnmsg.OrgTraceNo = 0;
	else
		txnmsg.OrgTraceNo = atoi( cfgval );

	if( cfgutil.cfg_search( "TRANDATE", cfgval, 2 ) < 0 )
		txnmsg.TranDate = ezdatetimeutil.getSysDate();

	else
		txnmsg.TranDate = atoi( cfgval );

	if( cfgutil.cfg_search( "TRANTIME", cfgval, 2 ) < 0 )
		txnmsg.TranTime = ezdatetimeutil.getSysTime();
	else
		txnmsg.TranTime = atoi( cfgval );

	txnmsg.OrgTranDate = ezdatetimeutil.getSysDate();
	txnmsg.OrgTranTime = ezdatetimeutil.getSysTime();
	txnmsg.LocalDate = ezdatetimeutil.getSysDate();
	txnmsg.LocalTime = ezdatetimeutil.getSysTime();
	txnmsg.ExpiryDate = ezdatetimeutil.getSysDate();
	memset( cfgval, 0, sizeof( cfgval ) );

	if( cfgutil.cfg_search( "RESPCODE", cfgval, 2 ) < 0 )
		txnmsg.RespCode = 0;
	else
		txnmsg.RespCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REVCODE", cfgval, 2 ) < 0 )
		txnmsg.RevCode = 0;
	else
		txnmsg.RevCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REASONCODE", cfgval, 2 ) < 0 )
		txnmsg.ReasonCode = 0;
	else
		txnmsg.ReasonCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AUTHCODE", cfgval, 2 ) < 0 )
		txnmsg.AuthCode = 0;
	else
		txnmsg.AuthCode = atoi( cfgval );

	txnmsg.CaptureDate = ezdatetimeutil.getSysDate();
	txnmsg.CaptureTime = ezdatetimeutil.getSysTime();
	txnmsg.SettlementDate = ezdatetimeutil.getSysDate();
	txnmsg.BusinessDate = ezdatetimeutil.getSysDate();

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCURRCODE", cfgval, 2 ) < 0 )
		txnmsg.AcqCurrencyCode = 356;
	else
		txnmsg.AcqCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCURRCODE", cfgval, 2 ) < 0 )
		txnmsg.IssCurrencyCode = 356;
	else
		txnmsg.IssCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFCURRCODE", cfgval, 2 ) < 0 )
		txnmsg.TxfCurrencyCode = 356;
	else
		txnmsg.TxfCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCURRCODE", cfgval, 2 ) < 0 )
		txnmsg.SettCurrencyCode = 356;
	else
		txnmsg.SettCurrencyCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCONVRATE", cfgval, 2 ) < 0 )
		txnmsg.AcqConvRate = 0;
	else
		txnmsg.AcqConvRate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCONVRATE", cfgval, 2 ) < 0 )
		txnmsg.IssConvRate = 0;
	else
		txnmsg.IssConvRate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCONVRATE", cfgval, 2 ) < 0 )
		txnmsg.SettConvRate = 0;
	else
		txnmsg.SettConvRate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQCONVDATE", cfgval, 2 ) < 0 )
		txnmsg.AcqConvDate = 0;
	else
		txnmsg.AcqConvDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSCONVDATE", cfgval, 2 ) < 0 )
		txnmsg.IssConvDate = 0;
	else
		txnmsg.IssConvDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTCONVDATE", cfgval, 2 ) < 0 )
		txnmsg.SettConvDate = 0;
	else
		txnmsg.SettConvDate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSENTRYCODE", cfgval, 2 ) < 0 )
		txnmsg.PosEntryCode = 0;
	else
		txnmsg.PosEntryCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSCONDITIONCODE", cfgval, 2 ) < 0 )
		txnmsg.PosConditionCode = 0;
	else
		txnmsg.PosConditionCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSPINCAPCODE", cfgval, 2 ) < 0 )
		txnmsg.PosPinCapCode = 0;
	else
		txnmsg.PosPinCapCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSCAPCODE", cfgval, 2 ) < 0 )
		txnmsg.PosCapCode = 0;
	else
		txnmsg.PosCapCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MERCHANTTYPE", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching MERCHANTTYPE from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	txnmsg.MerchantType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DEVICESUBTYPE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.DeviceSubType, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "CHN", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching CHN from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}

	strcpy( txnmsg.chn, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TRACK2", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.Track2, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQBRANCHCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AcqBranchCode, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSBRANCHCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.IssBranchCode, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFBRANCHCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.TxfBranchCode, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTBRANCHCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SettBranchCode, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FWDBRANCHCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.ForwardBranchCode, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FROMPRODUCTCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.FromAcctSubType, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TOPRODUCTCODE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.ToAcctSubType, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AMOUNT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.Amount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DISPAMOUNT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.DispAmount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTAMOUNT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SettAmount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "BILLINGAMOUNT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.BillingAmount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXNFEE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.TxnFee, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FROMACCOUNT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.FromAccount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TOACCOUNT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.ToAccount, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AVAILBALANCE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AvailBalance, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "LEDGERBALANCE", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.LedgerBalance, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "REFNUM", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RefNum, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AUTHNUM", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AuthNum, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PINBLOCK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.PINBlock, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "NEWPINBLOCK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.NewPINBlock, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PINKEY", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.PinKey, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACCEPTORID", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AcceptorId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACCEPTORNAME", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AcceptorName, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQINST", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AcquirerInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSINST", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.IssuerInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FWDINST", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.ForwardInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFINST", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.TxfInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTINST", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SettInst, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQBIN", cfgval, 2 ) >= 0 )
	strcpy( txnmsg.AcquirerBin, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSBIN", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.IssuerBin, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FWDBIN", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.ForwardBin, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFBIN", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.TxfBin, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTBIN", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SettBin, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "NTWKID", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.NetworkId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ACQNTWK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.AcqNetworkId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ISSNTWK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.IssuerNetworkId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "FWDNTWK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.FwdNetworkId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXFNTWK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.TxfNetworkId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SETTNTWK", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SettNetworkId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "NETCODE", cfgval, 2 ) < 0 )
		txnmsg.NetCode = 0;
	else
		txnmsg.NetCode = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RSVFLD1", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RsvFld1, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RSVFLD2", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RsvFld2, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RSVFLD3", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RsvFld3, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RSVFLD4", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RsvFld4, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RSVFLD5", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RsvFld5, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "RSVFLD6", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.RsvFld6, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SRCCHANNEL", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SrcChannel, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SRCPORT", cfgval, 2 ) >= 0 )
		strcpy( txnmsg.SrcPort, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DESTCHANNEL", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching DESTCHANNEL from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzTxnSim Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit(0);
	}
	memset( DestChannel, 0, sizeof( DestChannel ) );
	strcpy( DestChannel, cfgval );
}

void EzTxnSim :: startTxnSim()
{
	int MsgSize;
	if( WriteChannel( DestChannel, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Sending Message to Channel[%s]", DestChannel );
	}
	else
	{
		trace( "TxnSim Waiting for Response.....");
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * ) &txnmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from EzTxnSim Channel" );
		}
		printf("\n Read Response with MsgType[%d] TxnCode[%d] TraceNo[%d] TxnDate[%d] TxnTime[%d] ResponseCode[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.TraceNo, txnmsg.TranDate, txnmsg.TranTime, txnmsg.RespCode );
	}
}

int main( int argc, char **argv )
{
	EzTxnSim eztxnsim;
	eztxnsim.initTxnSim( "EzTxnSim" );
	eztxnsim.startTxnSim();
	return 1;
}


