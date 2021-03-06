#include <eztms/eztmsdriver.h>

int EzTMSDriver :: initTMSDriver( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ TMS_BITMAP_FILE_SIZE + 1 ],MerchId[ 33 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztmsdriver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
			exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzTMSDriver Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( CHANNEL_NAME_TMSDRIVER, TaskName ) < 0 )
	{
		trace( "Error in Creating [%s] Channel", CHANNEL_NAME_TMSDRIVER );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( castle8583.initCastles8583( this, &ezdatetimeutil, &merchantprofile_rec, &terminalprofile_rec, &amtutil ) < 0 )
	{
		trace( "Error in Initializing Castles8583...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initSchemaInfoUtil( this ) < 0 )
	{
		trace( "Error in Initializing SchemaInfoUtil..." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this, "EZMMS" ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( SchemaType == SCHEMA_TYPE_SINGLE )
	{
		if( dbutil.DBConnect() < 0 )
		{
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^" );
			closeDebug();
			TaskExit();
		}
	}

	if( initTMSDriverUtil( this ) < 0 )
	{
		trace( "Error in Initializing TMSDriverUtil...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if(  LoadTMSChannelProperty() < 0 )
	{
		trace( "Error in Loading TMSChannelProperty...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSRouteInfo() < 0 )
	{
		trace( "Error in Loading TMSRouteInfo...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSRouteSelect() < 0 )
	{
		trace( "Error in Loading TMSRouteSelect...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSMsgTranslate() < 0 )
	{
		trace( "Error in Loading TMSMsgTranslate...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSTxnRefSelect() < 0 )
	{
		trace( "Error in Loading TMSTxnRefSelect...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSInBoundProperty() < 0 )
	{
		trace( "Error in Loading TMSInBoundProperty...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadTMSTxnRel() < 0 )
	{
		trace( "Error in Loading TMSTxnRel...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnsequtil.initTxnSeqUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnSeqUtil...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initMMSUtil( this ) < 0 )
	{
		trace( "Error in Initializing MMSUtil..." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezmmsdbutil.initMMSDBUtil( this, this, &dbutil, &ezdatetimeutil, &tkutil, this ) < 0 )
	{
		trace( "Error in Initializing MMSDBUtil...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing SecurityUtil...." );
		trace( "^^^^^^^^^^^EzTMSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

int EzTMSDriver :: logTMSTxnInfo( char LogFlag, const char *TMSTxnRefNum, struct EzTxnMsg *tmsmsg_ptr )
{
	struct EzTMSLoggerMsg tmsloggermsg;

	memset( &tmsloggermsg, 0, sizeof( struct EzTMSLoggerMsg ) );
	strcpy( tmsloggermsg.MachineId, tmsmsg_ptr->MachineId );
	tmsloggermsg.LogFlag = LogFlag;
	tmsloggermsg.NotificationId = getpid();
	strcpy( tmsloggermsg.TMSTxnRefNum, TMSTxnRefNum );
	memcpy( &tmsloggermsg.txnmsg, tmsmsg_ptr, sizeof( struct EzTxnMsg ) );

	if( WriteChannel( TMSLOGGERCHANNEL, ( char * ) &tmsloggermsg, sizeof( struct EzTMSLoggerMsg ) ) < 0 )
	{
		trace( "Error in Writing Message to Channel[%s]...", TMSLOGGERCHANNEL );
		return -1;
	}
	return 1;
}

void EzTMSDriver :: process500( struct EzTxnMsg tmsmsg )
{
	char *endptr, TempStr[ 50 ], NewBatchId[ 13 ], MatchFlag;
	int SaleCount, RefundCount, AuthCount, retval, MsgSize, settoffset = 0;
	char SaleAmount[ 33 ], RefundAmount[ 33 ], AuthAmount[ 33 ];
	struct EzTerminalTotal tot_rec;
	struct EzTerminalBatchInfo termbatchinfo_rec;
	struct EzTerminalBatchInfoHist termbatchinfohist_rec;
	char SaleAmtStr[ 20 ], TableSaleAmtStr[ 20 ], VoidAmtStr[ 20 ], TableVoidAmtStr[ 20 ];

	trace( "Processing 500 Message from MachineId[%s]", terminalprofile_rec.MachineId );

	trace( "Decomposing Total[%s]", tmsmsg.RsvFld2 );

	populateNewTerminalRequest( &tmsmsg );

	if( tmsmsg.TxnCode == EZTMS_Txn_Settlement_Init )
	{
		memset( &tot_rec, 0, sizeof( struct EzTerminalTotal ) );
		if( ezmmsdbutil.getTotals( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId, &tot_rec, '1' ) < 0 )
		{
			trace( "Error in Getting Terminal Totals for MachineId[%s] BatchId[%s]", terminalprofile_rec.MachineId, terminalprofile_rec.BatchId );
			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			return;
		}
	}
	else
	{
		memset( &tot_rec, 0, sizeof( struct EzTerminalTotal ) );
		if( ezmmsdbutil.getTotals( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId, &tot_rec, '2' ) < 0 )
		{
			trace( "Error in Getting Terminal Totals for MachineId[%s] BatchId[%s]", terminalprofile_rec.MachineId, terminalprofile_rec.BatchId );
			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			return;
		}
	}

	settoffset = 0;

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + settoffset, 3 );
	settoffset += 3;
	SaleCount = atoi( TempStr );
	trace( "SaleCount[%d]", SaleCount );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + settoffset, 12 );
	settoffset += 12;

	memset( SaleAmount, 0, sizeof( SaleAmount ) );
	amtutil.normalizeAmt( TempStr, SaleAmount, 2 );
	trace( "SaleAmount[%s]", SaleAmount );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + settoffset, 3 );
	settoffset += 3;
	RefundCount = atoi( TempStr );
	trace( "RefundCount[%d]", RefundCount );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + settoffset, 12 );
	settoffset += 12;

	memset( RefundAmount, 0, sizeof( RefundAmount ) );
	amtutil.normalizeAmt( TempStr, RefundAmount, 2 );
	trace( "RefundAmount[%s]", RefundAmount );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + settoffset, 3 );
	settoffset += 3;
	AuthCount = atoi( TempStr );
	trace( "AuthCount[%d]", AuthCount );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, tmsmsg.RsvFld2 + settoffset, 12 );
	settoffset += 12;
	memset( AuthAmount, 0, sizeof( AuthAmount ) );
	amtutil.normalizeAmt( TempStr, AuthAmount, 2 );
	trace( "AuthAmount[%s]", AuthAmount );

	trace( "Checking SaleCount[%d] SaleAmount[%s] RefundCount[%d] RefundAmount[%s] AuthCount[%d] AuthAmount[%s] sent from Terminal[%s]...", SaleCount, SaleAmount, RefundCount, RefundAmount, AuthCount, AuthAmount, terminalprofile_rec.MachineId );
	trace( "Read From Totals.. SaleCount[%d] SaleAmount[%s] RefundCount[%d] RefundAmount[%s] AuthCount[%d] AuthAmount[%s]...", tot_rec.SaleCount, tot_rec.SaleAmount, tot_rec.RefundCount, tot_rec.RefundAmount, tot_rec.AuthCount, tot_rec.AuthAmount );

	if( SaleCount != tot_rec.TermSaleCount )
	{
		trace( "TermSaleCount[%d] != TotalSaleCount[%d]", SaleCount, tot_rec.TermSaleCount );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = 95;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}

	if( amtutil.compareAmount( SaleAmount, tot_rec.TermSaleAmount ) )
	{
		trace( "SaleAmount[%s] != TotalSaleAmount[%s]", SaleAmount, tot_rec.TermSaleAmount );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = 95;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}

	if( RefundCount != tot_rec.TermRefundCount )
	{
		trace( "TermRefundCount[%d] != TotalRefundCount[%d]", RefundCount, tot_rec.TermRefundCount );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = 95;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}

	if( amtutil.compareAmount( RefundAmount, tot_rec.TermRefundAmount ) )
	{
		trace( "SaleAmount[%s] != TotalSaleAmount[%s]", RefundAmount, tot_rec.TermRefundAmount );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = 95;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}

	if( AuthCount != tot_rec.TermAuthCount )
	{
		trace( "TermAuthCount[%d] != TotalAuthCount[%d]", AuthCount, tot_rec.TermAuthCount );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = 95;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}

	if( amtutil.compareAmount( AuthAmount, tot_rec.TermAuthAmount ) )
	{
		trace( "AuthAmount[%s] != TotalAuthAmount[%s]", AuthAmount, tot_rec.TermAuthAmount );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = 95;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}

	memset( NewBatchId, 0, sizeof( NewBatchId ) );
	eztxnsequtil.genPOSBatchId( NewBatchId );
	trace( "Generated NewBatchId[%s] for Terminal[%s]", NewBatchId, terminalprofile_rec.MachineId );

	if( ezmmsdbutil.updateBatchId( terminalprofile_rec.MachineId, NewBatchId, '2' ) < 0 )
	{
		trace( "Error in Updating NewPOSBatchId[%s] in Table for Terminal[%s]", NewBatchId, terminalprofile_rec.MachineId );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		ezmmsdbutil.revertSettlementEntries();
		return;
	}

	memset( &termbatchinfohist_rec, 0, sizeof( struct EzTerminalBatchInfoHist ) );
	strcpy( termbatchinfohist_rec.BatchId, terminalprofile_rec.BatchId );
	memset( termbatchinfohist_rec.TermBatchId, 0, sizeof( termbatchinfohist_rec.TermBatchId ) );
	strcpy( termbatchinfohist_rec.TermBatchId, tmsmsg.BatchId );
	memset( termbatchinfohist_rec.NewBatchId, 0, sizeof( termbatchinfohist_rec.NewBatchId ) );
	strcpy( termbatchinfohist_rec.NewBatchId, NewBatchId );
	memset( termbatchinfohist_rec.InstId, 0, sizeof( termbatchinfohist_rec.InstId ) );
	strcpy( termbatchinfohist_rec.InstId, terminalprofile_rec.InstId );
	memset( termbatchinfohist_rec.MachineId, 0, sizeof( termbatchinfohist_rec.MachineId ) );
	strcpy( termbatchinfohist_rec.MachineId, terminalprofile_rec.MachineId );
	memset( termbatchinfohist_rec.Termid, 0, sizeof( termbatchinfohist_rec.Termid ) );
	strcpy( termbatchinfohist_rec.Termid, terminalprofile_rec.TerminalId );
	memset( termbatchinfohist_rec.MerchantId, 0, sizeof( termbatchinfohist_rec.MerchantId ) );
	strcpy( termbatchinfohist_rec.MerchantId, terminalprofile_rec.MerchantId );
	memset( termbatchinfohist_rec.CloseDate, 0, sizeof( termbatchinfohist_rec.CloseDate ) );
	sprintf( termbatchinfohist_rec.CloseDate, "%06d", ezdatetimeutil.getSysDate() );
	termbatchinfohist_rec.CloseTime = ezdatetimeutil.getSysTime();
	termbatchinfohist_rec.Source = TMS_SOURCE_TERMINAL;
	termbatchinfohist_rec.HostSaleCount =  tot_rec.SaleCount;
	memset( termbatchinfohist_rec.HostSaleAmount, 0, sizeof( termbatchinfohist_rec.HostSaleAmount ) );
	strcpy( termbatchinfohist_rec.HostSaleAmount, tot_rec.SaleAmount );
	termbatchinfohist_rec.TermSaleCount = SaleCount;
	memset( termbatchinfohist_rec.TermSaleAmount, 0, sizeof( termbatchinfohist_rec.TermSaleAmount ) );
	strcpy( termbatchinfohist_rec.TermSaleAmount, SaleAmount );
	termbatchinfohist_rec.HostRefundCount =  tot_rec.RefundCount;
	memset( termbatchinfohist_rec.HostRefundAmount, 0, sizeof( termbatchinfohist_rec.HostRefundAmount ) );
	strcpy( termbatchinfohist_rec.HostRefundAmount, tot_rec.RefundAmount );
	termbatchinfohist_rec.TermRefundCount = RefundCount;
	memset( termbatchinfohist_rec.TermRefundAmount, 0, sizeof( termbatchinfohist_rec.TermRefundAmount ) );
	strcpy( termbatchinfohist_rec.TermRefundAmount, RefundAmount );
	termbatchinfohist_rec.HostAuthCount =  tot_rec.AuthCount;
	memset( termbatchinfohist_rec.HostAuthAmount, 0, sizeof( termbatchinfohist_rec.HostAuthAmount ) );
	strcpy( termbatchinfohist_rec.HostAuthAmount, tot_rec.AuthAmount );
	termbatchinfohist_rec.TermAuthCount = AuthCount;
	memset( termbatchinfohist_rec.TermAuthAmount, 0, sizeof( termbatchinfohist_rec.TermAuthAmount ) );
	strcpy( termbatchinfohist_rec.TermAuthAmount, AuthAmount );

	if( tmsmsg.TxnCode != EZTMS_Txn_Settlement_Init )
	{
		termbatchinfohist_rec.MatchFlag = TMS_TOTALS_MISMATCHED;
		if( ezmmsdbutil.updateTxnMasterAsSettled( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId, '2' ) < 0 )
		{
			trace( "Error in Updating TxnMaster As Settled For MachineId[%s] BatchId[%s]", terminalprofile_rec.MachineId, terminalprofile_rec.BatchId );
			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			ezmmsdbutil.revertSettlementEntries();
			return;
		}
	}
	else
	{
		termbatchinfohist_rec.MatchFlag = TMS_TOTALS_MATCHED;
		if( ezmmsdbutil.updateTxnMasterAsSettled( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId, '1' ) < 0 )
		{
			trace( "Error in Updating TxnMaster As Settled For MachineId[%s] BatchId[%s]", terminalprofile_rec.MachineId, terminalprofile_rec.BatchId );
			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			ezmmsdbutil.revertSettlementEntries();
			return;
		}
		if( ezmmsdbutil.updateBatchTxnAsMatched( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId ) < 0 )
		{
			trace( "Error in Updating BatcTxnInfo As Matched For MachineId[%s] BatchId[%s]", terminalprofile_rec.MachineId, terminalprofile_rec.BatchId );
			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			ezmmsdbutil.revertSettlementEntries();
			return;
		}
	}

	if( ezmmsdbutil.insertBatchHist( &termbatchinfohist_rec, '2' ) < 0 )
	{
		trace( "Error in Inserting TerminalBatchHist in Table for Terminal[%s]", terminalprofile_rec.MachineId );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		ezmmsdbutil.revertSettlementEntries();
		return;
	}

	if( ezmmsdbutil.changeFromBatchTxnInfoToHist( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId, '2' ) < 0 )
	{
		trace( "Error in Moving from POSBatchTxnInfo to Hist Table..for Terminal[%s]", terminalprofile_rec.MachineId );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		ezmmsdbutil.revertSettlementEntries();
		return;
	}

	if( ezmmsdbutil.deleteBatchTxns( terminalprofile_rec.MachineId, terminalprofile_rec.BatchId, '2' ) < 0 )
	{
		trace( "Error in Deleting TerminalBatchTxnInfo..for Terminal[%s]", terminalprofile_rec.MachineId );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		ezmmsdbutil.revertSettlementEntries();
		return;
	}

	trace( "Saving Settlement Entries...." );
	ezmmsdbutil.saveSettlementEntries();

	if( updateTerminalBatchId( terminalprofile_rec.MachineId, NewBatchId ) < 0 )
	{
		trace( "Error in Updating NewPOSBatchId[%s] in Memory for Terminal[%s]", NewBatchId, terminalprofile_rec.MachineId );
		tmsmsg.MsgType += 10;
		tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
		writeToPOS( GetLastSenderChannelName(), &tmsmsg );
		return;
	}
	tmsmsg.MsgType += 10;
	tmsmsg.RespCode = EZTMS_RC_Approved;
	writeToPOS( GetLastSenderChannelName(), &tmsmsg );
}

void EzTMSDriver :: process320( struct EzTxnMsg *tmsmsg_ptr )
{
	struct EzTxnMsg oldtmsmsg;
	char *endptr, TMSTxnRefNum[ 151 ], AmountStr[ 33 ];
	int retval, MsgSize;
	double Amount, TableAmount;

	trace( "Processing 320 message for POSId[%s]", terminalprofile_rec.MachineId );
	populateNewTerminalRequest( tmsmsg_ptr );

	memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
	getTMSTxnRefNum( tmsmsg_ptr, TMSTxnRefNum );
	trace( "Got LookUp POSTxnRefNum[%s]", TMSTxnRefNum );

	memset( &oldtmsmsg, 0, sizeof( struct EzTxnMsg ) );
	retval = ezmmsdbutil.searchBatchTxn( &oldtmsmsg, TMSTxnRefNum );
	if( retval < 0 )
	{
		trace( "Error in Searching Transaction in  TerminalBatchTxnInfo with MachineId[%s] TxnRefNum[%s]", terminalprofile_rec.MachineId, TMSTxnRefNum );
		tmsmsg_ptr->MsgType += 10;
		tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
		writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
		return;
	}

	if( retval == 2 )
	{
		ezmmsdbutil.generateTxnNarration( tmsmsg_ptr );
		ezmmsdbutil.checkTransactionEntries( tmsmsg_ptr );
		trace( "Transaction with POSTxnRefNum[%s] BatchId[%s] POSId[%s] not found in POSBatchTxnInfo Table...",  TMSTxnRefNum, tmsmsg_ptr->BatchId, terminalprofile_rec.MachineId );
		if( ezmmsdbutil.insertMMSTransactionBatch( tmsmsg_ptr, TMSTxnRefNum, '2', TMS_TXN_REASON_NOT_FOUND_HOST ) < 0 )
		{
			trace( "Error in Inserting Transaction in TerminalBatchTxnInfo with MachineId[%s] TxnRefNum[%s]", terminalprofile_rec.MachineId, TMSTxnRefNum );
			tmsmsg_ptr->MsgType += 10;
			tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
			return;
		}

		if( ezmmsdbutil.insertMMSTransactionMaster( tmsmsg_ptr, TMSTxnRefNum, TXN_STATUS_PENDING, '2', TMS_TXN_REASON_NOT_FOUND_HOST ) < 0 )
		{
			trace( "Error in Inserting Transaction in TransactionMaster with MachineId[%s] TxnRefNum[%s]", terminalprofile_rec.MachineId, TMSTxnRefNum );
			tmsmsg_ptr->MsgType += 10;
			tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
			writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
			return;
		}
	}
	else
	{
		memset( AmountStr, 0, sizeof( AmountStr ) );
		amtutil.normalizeAmount( tmsmsg_ptr->Amount, AmountStr, 2 );
		if( amtutil.compareAmount( AmountStr, oldtmsmsg.Amount ) )
		{
			trace( "Transaction with POSTxnRefNum[%s] BatchId[%s] POSId[%s] has a Amount MisMatch TerminalAmount[%s] != HostAmount[%s] in TerminalBatchTxnInfo Table...",  TMSTxnRefNum, tmsmsg_ptr->BatchId, terminalprofile_rec.MachineId, tmsmsg_ptr->Amount, oldtmsmsg.Amount );
			if( ezmmsdbutil.updateTerminalBatchTxnInfo( terminalprofile_rec.MachineId, TMSTxnRefNum, AmountStr, TMS_TXN_MISMATCH, TMS_TXN_REASON_AMOUNT_MISMATCH ) < 0 )
			{
				trace( "Error in Updating PosBatchTxnInfo OraErr[%05d]", retval );
				tmsmsg_ptr->MsgType += 10;
				tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
				writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
				return;
			}
			if( ezmmsdbutil.updateMMSTransactionMaster( terminalprofile_rec.MachineId, TMSTxnRefNum, AmountStr, TMS_TXN_MISMATCH, TMS_TXN_REASON_AMOUNT_MISMATCH ) < 0 )
			{
				trace( "Error in Updating TransactionMaster OraErr[%05d]", retval );
				tmsmsg_ptr->MsgType += 10;
				tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
				writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
				return;
			}
		}
		else
		{
			if( ezmmsdbutil.updateTerminalBatchTxnInfo( terminalprofile_rec.MachineId, TMSTxnRefNum, AmountStr, TMS_TXN_MATCH, TMS_TXN_REASON_MATCH ) < 0 )
			{
				trace( "Error in Updating PosBatchTxnInfo OraErr[%05d]", retval );
				tmsmsg_ptr->MsgType += 10;
				tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
				writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
				return;
			}
			if( ezmmsdbutil.updateMMSTransactionMaster( terminalprofile_rec.MachineId, TMSTxnRefNum, AmountStr, TMS_TXN_MATCH, TMS_TXN_REASON_MATCH ) < 0 )
			{
				trace( "Error in Updating TransactionMaster OraErr[%05d]", retval );
				tmsmsg_ptr->MsgType += 10;
				tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
				writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
				return;
			}
		}
	}
	tmsmsg_ptr->MsgType += 10;
	tmsmsg_ptr->RespCode = EZTMS_RC_Approved;
	writeToPOS( GetLastSenderChannelName(), tmsmsg_ptr );
}

void EzTMSDriver :: populateOldTerminalRequest( struct EzTxnMsg *tmsmsg, struct EzTxnMsg *oldtmsmsg )
{
	trace( "Copying Old Transaction Details" );
	memset( tmsmsg->DeviceType, 0, sizeof( tmsmsg->DeviceType ) );
	strcpy( tmsmsg->DeviceType, "POS" );

	memset( tmsmsg->OrgChannel, 0, sizeof( tmsmsg->OrgChannel ) );
	strcpy( tmsmsg->OrgChannel, GetSourceChannelName() );
	memset( tmsmsg->OrgPort, 0, sizeof( tmsmsg->OrgPort ) );
	strcpy( tmsmsg->OrgPort, GetLastSenderChannelName() );
	memset( tmsmsg->SrcPort, 0, sizeof( tmsmsg->SrcPort ) );
	strcpy( tmsmsg->SrcPort, tmsmsg->OrgPort );
	memset( tmsmsg->SrcChannel, 0, sizeof( tmsmsg->SrcChannel ) );
	strcpy( tmsmsg->SrcChannel, tmsmsg->OrgChannel );
	if( !strlen( tmsmsg->RefNum ) )
	{
		memset( tmsmsg->RefNum, 0, sizeof( tmsmsg->RefNum ) );
		strcpy( tmsmsg->RefNum, oldtmsmsg->RefNum );
	}
	if( !strlen( tmsmsg->AuthNum ) )
	{
		memset( tmsmsg->AuthNum, 0, sizeof( tmsmsg->AuthNum ) );
		strcpy( tmsmsg->AuthNum, oldtmsmsg->AuthNum );
	}
	if( !tmsmsg->TranDate )
		tmsmsg->TranDate = oldtmsmsg->TranDate;
	if( !tmsmsg->TranTime )
		tmsmsg->TranTime = oldtmsmsg->TranTime;
	if( !tmsmsg->LocalDate )
		tmsmsg->LocalDate = oldtmsmsg->LocalDate;
	if( !tmsmsg->LocalTime )
		tmsmsg->LocalTime = oldtmsmsg->LocalTime;
	if( !tmsmsg->BusinessDate )
		tmsmsg->BusinessDate = oldtmsmsg->BusinessDate;
	if( !strlen( tmsmsg->BatchId ) )
	{
		memset( tmsmsg->BatchId, 0, sizeof( tmsmsg->BatchId ) );
		strcpy( tmsmsg->BatchId, oldtmsmsg->BatchId );
	}
	if( !tmsmsg->AuthCode )
		tmsmsg->AuthCode = oldtmsmsg->AuthCode;

	//Copying VISA Transaction Identifier
	memset( tmsmsg->RsvFld4, 0, sizeof( tmsmsg->RsvFld4 ) );
	strcpy( tmsmsg->RsvFld4, oldtmsmsg->RsvFld4 );
}

int EzTMSDriver :: logTerminalStatus( struct EzTxnMsg *tmsmsg, char StatusId )
{
	int retval;
	trace( "Logging Terminal Status with StatusId[%c]", StatusId );
	memset( &termstatus_rec, 0, sizeof( struct EzMMSTerminalStatus ) );
	strcpy( termstatus_rec.InstId, tmsmsg->AcquirerInst );
	strcpy( termstatus_rec.MerchantId, tmsmsg->AcceptorId );
	strcpy( termstatus_rec.MachineId, tmsmsg->MachineId );
	strcpy( termstatus_rec.TerminalId, tmsmsg->TerminalId );
	strcpy( termstatus_rec.StoreId, tmsmsg->StoreId );
	sprintf( termstatus_rec.LastRcvDate, "%06d", ezdatetimeutil.getSysDate() );
	sprintf( termstatus_rec.LastRcvTime, "%06d", ezdatetimeutil.getSysTime() );
	strcpy( termstatus_rec.LastTxnDate, termstatus_rec.LastRcvDate );
	strcpy( termstatus_rec.LastTxnTime, termstatus_rec.LastRcvTime );
	//strcpy( termstatus_rec.Version, tmsmsg->RsvFld2 );
	strcpy( termstatus_rec.Version, "1.0" );
	if( ezmmsdbutil.updateTerminalStatus( &termstatus_rec, StatusId  ) < 0 )
		trace( "Cannot Update the TerminalStatus for InstId[%s] MachineId[%s]", termstatus_rec.InstId, termstatus_rec.MachineId );
	else
		trace( "Updated the TerminalStatus for InstId[%s] MachineId[%s]", termstatus_rec.InstId, termstatus_rec.MachineId );
	return 1;
}

void EzTMSDriver :: processEchoRequest( struct EzTxnMsg *tmsmsg )
{
	logTerminalStatus( tmsmsg, TERMINAL_STATUSID_ECHO );
	tmsmsg->MsgType += 10;
	tmsmsg->RespCode = EZTMS_RC_Approved;
	writeToPOS( GetLastSenderChannelName(), tmsmsg );
}

void EzTMSDriver :: processKeyRequest( struct EzTxnMsg *tmsmsg )
{
	int retval;
	char TermPINKey_LMK[ 65 ], TermPINKey_TMK[ 65 ], TermPINKey_KCV[ 65 ], TempStr[ 255 ];
	char CatCode[ 17 ], UserName[ 33 ], Password[ MMS_PWD_SIZE + 1 ], hPassword[ MMS_PWD_SIZE + 1 ];

	if( !tmsmsg->TranDate )
		tmsmsg->TranDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->TranTime )
		tmsmsg->TranTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->LocalDate )
		tmsmsg->LocalDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->LocalTime )
		tmsmsg->LocalTime = ezdatetimeutil.getSysTime();

	if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
	{
		if( strlen( tmsmsg->RsvFld2 ) )
		{
			trace( "UserDetails[%s]", tmsmsg->RsvFld2 );
			memset( TempStr, 0, sizeof( TempStr ) );
			tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 1 );
			memset( CatCode, 0, sizeof( CatCode ) );
			strcpy( CatCode, TempStr );
			if( !strcmp( CatCode, "1" ) )
			{
				memset( UserName, 0, sizeof( UserName ) );
				strcpy( UserName, "Admin" );
				memset( TempStr, 0, sizeof( TempStr ) );
				tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 2 );
				memset( Password, 0, sizeof( Password ) );
				strcpy( Password, TempStr );
			}
			else if ( !strcmp( CatCode, "2" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 2 );
				memset( UserName, 0, sizeof( UserName ) );
				strcpy( UserName, TempStr );
				memset( TempStr, 0, sizeof( TempStr ) );
				tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 3 );
				memset( Password, 0, sizeof( Password ) );
				strcpy( Password, TempStr );
			}
			else
			{
				trace( "Invalid UserCategory[%s]...", CatCode );
				tmsmsg->RespCode = 5;
				tmsmsg->MsgType += 10;
				writeToPOS( GetLastSenderChannelName(), tmsmsg );
				return;
			}
			memset( hPassword, 0, sizeof( hPassword ) );
			ezpadssutil.tokenizeString( Password, "NOTDEFINED", hPassword );
			if( ezmmsdbutil.verifyTerminalUser( tmsmsg->MachineId, CatCode, UserName, hPassword ) < 0 )
			{
				trace( "Error in Verifying UserName[%s]Pwd[%s] for MachineId[%s] CatCode[%s]", UserName, hPassword, tmsmsg->MachineId, CatCode );
				tmsmsg->RespCode = 5;
				tmsmsg->MsgType += 10;
				writeToPOS( GetLastSenderChannelName(), tmsmsg );
				return;
			}
			if( ezmmsdbutil.insertTermUserLog( tmsmsg->AcquirerInst, tmsmsg->MachineId, tmsmsg->AcceptorId, tmsmsg->TerminalId, CatCode, UserName ) < 0 )
			{
				tmsmsg->RespCode = 5;
				tmsmsg->MsgType += 10;
				writeToPOS( GetLastSenderChannelName(), tmsmsg );
				return;
			}
			if( ezmmsdbutil.updateTermUserInfo( tmsmsg->MachineId, CatCode, UserName ) < 0 )
			{
				tmsmsg->RespCode = 5;
				tmsmsg->MsgType += 10;
				writeToPOS( GetLastSenderChannelName(), tmsmsg );
				return;
			}
			if( updateUserinTermMemory( tmsmsg->MachineId, CatCode, UserName ) < 0 )
			{
				tmsmsg->RespCode = 5;
				tmsmsg->MsgType += 10;
				writeToPOS( GetLastSenderChannelName(), tmsmsg );
				return;
			}
		}
	}

	memset( TermPINKey_LMK, 0, sizeof( TermPINKey_LMK ) );
	memset( TermPINKey_TMK, 0, sizeof( TermPINKey_TMK ) );
	memset( TermPINKey_KCV, 0, sizeof( TermPINKey_KCV ) );

	if( GenTerminalCommKey( terminalprofile_rec.InstId, terminalprofile_rec.TerminalId, terminalprofile_rec.TermMasterKey, ( int ) strlen( terminalprofile_rec.TermMasterKey ), TermPINKey_LMK, TermPINKey_TMK, TermPINKey_KCV ) < 0 )
	{
		trace( "Error in Generating Terminal Master Key for InstId[%s] TerminalId[%s] TerminalMasterKey[%s]", terminalprofile_rec.InstId, terminalprofile_rec.TerminalId, terminalprofile_rec.TermMasterKey );
		tmsmsg->RespCode = 5;
	}
	else
	{
		memset( tmsmsg->RsvFld2, 0, sizeof( tmsmsg->RsvFld2 ) );
		strcpy( tmsmsg->RsvFld2, TermPINKey_TMK );
		memset( tmsmsg->RsvFld3, 0, sizeof( tmsmsg->RsvFld3 ) );
		strcpy( tmsmsg->RsvFld3, TermPINKey_KCV );
		if( updateTermPINKeyinMemory( terminalprofile_rec.MachineId, TermPINKey_LMK ) < 0 )
		{
			trace( "Error in Updating TerminalPINKey[%s] for MachineId[%s]", TermPINKey_LMK, terminalprofile_rec.MachineId );
			tmsmsg->RespCode = 5;
		}
		else
		{
			if( ezmmsdbutil.updateTermPINKeyinTable( terminalprofile_rec.MachineId, TermPINKey_LMK ) < 0 )
			{
				trace( "Error in Updating TerminalPINKey[%s] for MachineId[%s]", TermPINKey_LMK, terminalprofile_rec.MachineId );
				tmsmsg->RespCode = 5;
			}
			else
				tmsmsg->RespCode = 0;
		}
	}
	logTerminalStatus( tmsmsg, TERMINAL_STATUSID_ECHO );
	tmsmsg->MsgType += 10;
	writeToPOS( GetLastSenderChannelName(), tmsmsg );
}

bool EzTMSDriver :: isTxnAllowed( const char *I_InstId, const char *I_TerminalType, const char *I_TxnCode, const char *I_CHN )
{
	int retval;
	char BinList[ 129 ];
	char TempChn[ 20 ];
	char TxnList[ 129 ];
	char TxnCode[10];

	memset( BinList, 0, sizeof( BinList ) );
	memset( TxnList, 0, sizeof( TxnList ) );
	if( ezmmsdbutil.readTxnAllowed( I_InstId, I_TerminalType, BinList, TxnList ) < 0 )
		return true;

	bool TxnFound = false;

	memset( TxnCode, 0, sizeof( TxnCode ) );
	strncpy( TxnCode, I_TxnCode, 2 );
	int TxnCount = tkutil.getNToken( TxnList, ',' );
	for( int i = 0; i < TxnCount; i++ )
	{
		char TempTxnCode[ 10 ];
		memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
		tkutil.getToken( TxnList, TempTxnCode, ',', i + 1 );
		if( !strcmp( TempTxnCode, TxnCode ) )
		{
			TxnFound = true;
			break;
		}
	}

	TxnCount = tkutil.getNToken( TxnList, ',' );
	for( int i = 0; i < TxnCount; i++ )
	{
		char TempTxnCode[ 10 ];
		memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
		tkutil.getToken( TxnList, TempTxnCode, ',', i + 1 );
		if( !strcmp( TempTxnCode, I_TxnCode ) )
		{
			TxnFound = true;
			break;
		}
	}

	return TxnFound;
}

bool EzTMSDriver :: isTxnAllowedonProduct( const char *I_InstId, const char *I_TerminalType, const char *I_TxnCode, const char *I_CHN )
{
	int retval;
	char BinList[ 129 ];
	char TempChn[ 20 ];
	char TxnList[ 129 ];
	char TxnCode[10];

	memset( BinList, 0, sizeof( BinList ) );
	memset( TxnList, 0, sizeof( TxnList ) );
	if( ezmmsdbutil.readTxnAllowed( I_InstId, I_TerminalType, BinList, TxnList ) < 0 )
		return true;

	bool TxnFound = false;

	int BinCount = tkutil.getNToken( BinList, ',' );
	for( int i = 0; i < BinCount; i++ )
	{
		char TempBin[ 15 ];
		memset( TempBin, 0, sizeof( TempBin ) );
		tkutil.getToken( BinList, TempBin, ',', i + 1 );
		memset( TempChn, 0, sizeof( TempChn ) );
		strncpy( TempChn, I_CHN, strlen( TempBin ) );
		if( !strcmp( TempChn, TempBin ) )
		{
			TxnFound = true;
			break;
		}
	}

	return TxnFound;
}


bool EzTMSDriver :: isValidTerminal( struct EzTxnMsg *tmsmsg_ptr )
{
	int retval;

	if( strlen( tmsmsg_ptr->MachineId ) == 32 )
	{
		trace( "Validating MachineId[%s]", tmsmsg_ptr->MachineId );
		memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
		if( readTerminalProfile( tmsmsg_ptr->MachineId, &terminalprofile_rec ) < 0 )
		{
			trace( "Error in Reading MachineId[%s] from TerminalInfo Memory....", tmsmsg_ptr->MachineId );
			memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
			if( SchemaType == SCHEMA_TYPE_SINGLE )
			{
				if( ezmmsdbutil.readEzMMSTerminalProfile( tmsmsg_ptr->MachineId, &terminalprofile_rec ) < 0 )
				{
					tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
					tmsmsg_ptr->ReasonCode = EZTMS_Reason_POSTerminalInfo_Err;
					return false;
				}
			}
			else
			{
				bool EntityFound = false;

				for( int i = 0; i < MaxSchemaInfo; i++ )
				{
					if( strcmp( ( SchemaInfoShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
					{
						if( !strcmp( ( SchemaInfoShmPtr + i )->ProductType, "MMS" ) )
						{
							if( ConnectDatabase( ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName ) != 0 )
							{
								trace( "Error in Connecting Database [%s/%s@%s]", ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName );
								continue;
							}
							else
								trace( "Connected Database [%s/%s@%s]", ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName );
							if( ezmmsdbutil.readEzMMSTerminalProfile( tmsmsg_ptr->MachineId, &terminalprofile_rec ) < 0 )
							{
								CloseDatabase();
								continue;
							}
							EntityFound = true;
							CloseDatabase();
							break;
						}
					}
				}
				if( !EntityFound )
				{
					tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
					tmsmsg_ptr->ReasonCode = EZTMS_Reason_POSTerminalInfo_Err;
					return false;
				}
			}
			if( addTerminalProfile( terminalprofile_rec ) < 0 )
				trace( "Error in Adding Terminal with MachineId[%s] in TerminalProfile Memory...", terminalprofile_rec.MachineId );
		}
		if( !strlen( tmsmsg_ptr->AcceptorId ) )
		{
			memset( tmsmsg_ptr->AcceptorId, 0, sizeof( tmsmsg_ptr->AcceptorId ) );
			strcpy( tmsmsg_ptr->AcceptorId, terminalprofile_rec.MerchantId );
		}
		if( !strlen( tmsmsg_ptr->TerminalId ) )
		{
			memset( tmsmsg_ptr->TerminalId, 0, sizeof( tmsmsg_ptr->TerminalId ) );
			strcpy( tmsmsg_ptr->TerminalId, terminalprofile_rec.TerminalId );
		}
	}
	else
	{
		trace( "Validating MerchantId[%s] TerminalId[%s]", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );
		memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
		if( readTerminalProfile( tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId, &terminalprofile_rec ) < 0 )
		{
			trace( "Error in Reading MerchantId[%s] TerminalId[%s] from TerminalInfo Memory....", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );
			memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
			if( SchemaType == SCHEMA_TYPE_SINGLE )
			{
				if( ezmmsdbutil.readEzMMSTerminalProfile( tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId, &terminalprofile_rec ) < 0 )
				{
					tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
					tmsmsg_ptr->ReasonCode = EZTMS_Reason_POSTerminalInfo_Err;
					return false;
				}
			}
			else
			{
				bool EntityFound = false;

				for( int i = 0; i < MaxSchemaInfo; i++ )
				{
					if( strcmp( ( SchemaInfoShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
					{
						if( !strcmp( ( SchemaInfoShmPtr + i )->ProductType, "MMS" ) )
						{
							if( ConnectDatabase( ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName ) != 0 )
							{
								trace( "Error in Connecting Database [%s/%s@%s]", ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName );
								continue;
							}
							else
								trace( "Connected Database [%s/%s@%s]", ( SchemaInfoShmPtr + i )->LoginName, ( SchemaInfoShmPtr + i )->Password, ( SchemaInfoShmPtr + i )->SchemaName );
							if( ezmmsdbutil.readEzMMSTerminalProfile( tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId, &terminalprofile_rec ) < 0 )
							{
								CloseDatabase();
								continue;
							}
							EntityFound = true;
							CloseDatabase();
							break;
						}
					}
				}
				if( !EntityFound )
				{
					tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
					tmsmsg_ptr->ReasonCode = EZTMS_Reason_POSTerminalInfo_Err;
					return false;
				}
			}
			if( addTerminalProfile( terminalprofile_rec ) < 0 )
				trace( "Error in Adding Terminal with MachineId[%s] in TerminalProfile Memory...", terminalprofile_rec.MachineId );
		}
	}

	if( tmsmsg_ptr->PinVerFlg == 'y' || tmsmsg_ptr->PinVerFlg == 'Y' )
	{
		memset( tmsmsg_ptr->PinKey, 0, sizeof( tmsmsg_ptr->PinKey ) );
		strcpy( tmsmsg_ptr->PinKey, terminalprofile_rec.TermPINKey );
		trace( "PIN Verification Flag is Yes...PinKey[%s]", terminalprofile_rec.TermPINKey );
	}


	if( terminalprofile_rec.TerminalStatus != '1' )
	{
		trace( "Terminal Status is not Active for MerchantId[%s] TerminalId[%s]", tmsmsg_ptr->AcceptorId, tmsmsg_ptr->TerminalId );
		tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
		return false;
	}

	if( SchemaType != SCHEMA_TYPE_SINGLE )
	{
		if( ConnectSchema( terminalprofile_rec.InstId, "MMS", "*" ) < 0 )
		{
			tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
			return false;
		}
	}

	memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
	if( readMerchantProfile( terminalprofile_rec.InstId, terminalprofile_rec.MerchantId, &merchantprofile_rec ) < 0  )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] from MerchantProfile Memory......", terminalprofile_rec.InstId, terminalprofile_rec.MerchantId );
		memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
		if( ezmmsdbutil.readEzMMSMerchantProfile( terminalprofile_rec.InstId, terminalprofile_rec.MerchantId, &merchantprofile_rec ) < 0 )
		{
			tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
			return false;
		}
		if( addMerchantProfile( merchantprofile_rec ) < 0 )
			trace( "Error in Adding InstId[%s] MerchantId[%s] in MerchantProfile Memory...", merchantprofile_rec.InstId, merchantprofile_rec.MerchantId );
	}

	memset( &storeprofile_rec, 0, sizeof( struct EzMMSStoreProfile ) );
	if( readStoreProfile( terminalprofile_rec.InstId, tmsmsg_ptr->AcceptorId, terminalprofile_rec.StoreId, &storeprofile_rec ) < 0 )
	{
		trace( "Error in Reading StoreId for InstId[%s] MerchantId[%s] StoreId[%s] from StoreProfile Memory....", terminalprofile_rec.InstId, tmsmsg_ptr->AcceptorId, terminalprofile_rec.StoreId );
		memset( &storeprofile_rec, 0, sizeof( struct EzMMSStoreProfile ) );
		if( ezmmsdbutil.readEzMMSStoreProfile( terminalprofile_rec.InstId, tmsmsg_ptr->AcceptorId, terminalprofile_rec.StoreId, &storeprofile_rec ) < 0 )
		{
			tmsmsg_ptr->RespCode = EZTMS_RC_InvalidTerminalId;
			return false;
		}
		if( addStoreProfile( storeprofile_rec ) < 0 )
			trace( "Error in Adding InstId[%s] MerchantId[%s] StoreId[%s] in StoreProfile Memory...", storeprofile_rec.InstId, storeprofile_rec.MerchantId, storeprofile_rec.StoreId );
	}
	strcpy( tmsmsg_ptr->MachineId, terminalprofile_rec.MachineId );
	strcpy( tmsmsg_ptr->AcquirerInst, terminalprofile_rec.InstId );
	memset( tmsmsg_ptr->TerminalLocation, 0, sizeof( tmsmsg_ptr->TerminalLocation ) );
	strcpy( tmsmsg_ptr->TerminalLocation, terminalprofile_rec.TerminalLocation );
	strcpy( tmsmsg_ptr->StoreId, terminalprofile_rec.StoreId );
	memset( tmsmsg_ptr->e_chn, 0, sizeof( tmsmsg_ptr->e_chn ) );
	strcpy( tmsmsg_ptr->e_chn, merchantprofile_rec.MerchantAcctNo );
	memset( tmsmsg_ptr->AcceptorName, 0, sizeof( tmsmsg_ptr->AcceptorName ) );
	strcpy( tmsmsg_ptr->AcceptorName, merchantprofile_rec.MerchantName );
	memset( tmsmsg_ptr->AcquirerBin, 0, sizeof( tmsmsg_ptr->AcquirerBin ) );
	strcpy( tmsmsg_ptr->AcquirerBin, merchantprofile_rec.AcquirerBIN );

	memset( &merchantscheme_rec, 0, sizeof( struct EzMMSMerchantScheme ) );
	if( strlen( tmsmsg_ptr->chn ) >= 16 )
	{
		memset( BIN, 0, sizeof( BIN ) );
		strncpy( BIN, tmsmsg_ptr->chn, 12 );
		if( readMerchantScheme( tmsmsg_ptr->AcquirerInst, BIN, &merchantscheme_rec ) < 0 )
		{
			trace( "Error in Reading MerchantScheme InstId[%s] BIN[%s] from MerchantScheme Memory....", tmsmsg_ptr->AcquirerInst, BIN );
			tmsmsg_ptr->RespCode = EZTMS_RC_UnableToProcess;
			tmsmsg_ptr->ReasonCode = EZTMS_Reason_POSTerminalInfo_Err;
			return false;
		}
		else
			trace( "Read MerchantScheme for InstId[%s] BIN[%s] Successfully with CardProduct[%s]", tmsmsg_ptr->AcquirerInst, BIN, merchantscheme_rec.SchemeName );
		memset( tmsmsg_ptr->CardProduct, 0, sizeof( tmsmsg_ptr->CardProduct ) );
		strcpy( tmsmsg_ptr->CardProduct, merchantscheme_rec.SchemeName );
		trace( "CardProduct[%s]", tmsmsg_ptr->CardProduct );
	}

	if( !tmsmsg_ptr->AcqCurrencyCode )
		tmsmsg_ptr->AcqCurrencyCode = atoi( terminalprofile_rec.CurrCode );

	tmsmsg_ptr->MerchantType = terminalprofile_rec.Mcc;

	if( !strlen( tmsmsg_ptr->BatchId ) )
	{
		if( !strcmp( terminalprofile_rec.BatchId, TMS_STRINGINIT_VAL ) )
		{
			memset( tmsmsg_ptr->BatchId, 0, sizeof( tmsmsg_ptr->BatchId ) );
			eztxnsequtil.genPOSBatchId( tmsmsg_ptr->BatchId );
			trace( "Generated New BatchId[%s]", tmsmsg_ptr->BatchId );
			memset( terminalprofile_rec.BatchId, 0, sizeof( terminalprofile_rec.BatchId ) );
			strcpy( terminalprofile_rec.BatchId, tmsmsg_ptr->BatchId );
			if( updateTerminalBatchId( terminalprofile_rec.MachineId, tmsmsg_ptr->BatchId ) < 0 )
				trace( "Error in Updating POSBatchId in Memory..." );
			ezmmsdbutil.updateBatchId( terminalprofile_rec.MachineId, tmsmsg_ptr->BatchId );
		}
		else
		{
			memset( tmsmsg_ptr->BatchId, 0, sizeof( tmsmsg_ptr->BatchId ) );
			strcpy( tmsmsg_ptr->BatchId, terminalprofile_rec.BatchId );
		}
	}
	return true;
}

int EzTMSDriver :: writeToInternalChannel( const char *ChannelName, struct EzTxnMsg *tmsmsg )
{
	trace( DEBUG_NORMAL, "<SEND>Channel(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", ChannelName, tmsmsg->DeviceType, tmsmsg->OrgChannel, tmsmsg->SrcChannel, tmsmsg->OrgPort, tmsmsg->SrcPort, tmsmsg->DestPort, tmsmsg->MsgType, tmsmsg->chn, tmsmsg->FromAccount, tmsmsg->TxnCode, tmsmsg->Amount, tmsmsg->TerminalId, tmsmsg->TraceNo, tmsmsg->TranDate, tmsmsg->TranTime, tmsmsg->LocalDate, tmsmsg->LocalTime, tmsmsg->RespCode, tmsmsg->ReasonCode, tmsmsg->RefNum, tmsmsg->NetworkId );
	if( WriteChannel( ChannelName, ( char * ) tmsmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing Message to Channel[%s]", ChannelName );
		return -1;
	}
	else
	{
		trace( "Written Successfully Message to Channel[%s]", ChannelName );
		return 1;
	}
}

void EzTMSDriver :: writeToExternalChannel( const char *ChannelName, char *ResponseBuffer, int MsgSize )
{
	trace( "Writing Message of %d Bytes to External Channel[%s]", MsgSize, ChannelName );
	if( WriteChannel( ChannelName, ResponseBuffer, MsgSize ) < 0 )
		trace( "Error in Writing Message to Channel[%s]", ChannelName );
}

void EzTMSDriver :: writeToPOS( const char *ChannelName, struct EzTxnMsg *tmsmsg )
{
	int ChannelKeyId, ChannelQid, MsgSize;

	//For reversal
	/*if( tmsmsg->MsgType == 210 )//&& tmsmsg->TxnCode / 10000 == 01  )
	{
		trace( "Dropping For Reversal...." );
		return;
	}*/

	if( LocateChannel( ChannelName, &ChannelKeyId, &ChannelQid  ) >= 0 )
	{
		if( readTMSChannelProperty( ChannelName ) < 0 )
		{
			trace( "Error in Reading ChannelName[%s] from TMSChannelProperty", GetLastSenderChannelName() );
			return;
		}
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		sprintf( ResponseBuffer, "%s%c", tmsmsg->RsvFld6, 0x1c );
		if( !strcasecmp( getTMSProtocol(), "VERIFONE" ) )
			MsgSize = castle8583.composeMsg( tmsmsg, ResponseBuffer + strlen( tmsmsg->RsvFld6 ) + 1, POS_PROTOCOL_HYPERCOM );
		else
			MsgSize = castle8583.composeMsg( tmsmsg, ResponseBuffer + strlen( tmsmsg->RsvFld6 ) + 1 );
		if( MsgSize < 0 )
		{
			trace( "Error in composing castles pos terminal...." );
			return;
		}
		MsgSize += strlen( tmsmsg->RsvFld6 ) + 1;
		writeToExternalChannel( ChannelName, ResponseBuffer, MsgSize );
	}
	else
	{
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		MsgSize = castle8583.composeMsg( tmsmsg, ResponseBuffer );
		if( MsgSize < 0 )
		{
			trace( "Error in composing castles pos terminal...." );
			return;
		}
		if( WritePortChannel( ChannelName, ResponseBuffer, MsgSize ) < 0 )
			trace( "Error in Writing Message to Port Channel[%s]", ChannelName );
		else
			trace( "Written Message to Port Channel[%s]", ChannelName );
	}
	hex_dump( ( unsigned char * ) ResponseBuffer, MsgSize );
}

void EzTMSDriver :: populateNewTerminalRequest( struct EzTxnMsg *tmsmsg )
{
	char temp[ 50 ];

	trace( "Populating New Request for TerminalId[%s]", tmsmsg->TerminalId );
	memset( tmsmsg->DeviceType, 0, sizeof( tmsmsg->DeviceType ) );
	strcpy( tmsmsg->DeviceType, "POS" );
	memset( tmsmsg->m_chn, 0, sizeof( tmsmsg->m_chn ) );
	ezpadssutil.maskString( tmsmsg->chn, 6, strlen( tmsmsg->chn ) - 4, '*', tmsmsg->m_chn );
	memset( tmsmsg->OrgChannel, 0, sizeof( tmsmsg->OrgChannel ) );
	strcpy( tmsmsg->OrgChannel, GetSourceChannelName() );
	memset( tmsmsg->OrgPort, 0, sizeof( tmsmsg->OrgPort ) );
	strcpy( tmsmsg->OrgPort, GetLastSenderChannelName() );
	memset( tmsmsg->SrcPort, 0, sizeof( tmsmsg->SrcPort ) );
	strcpy( tmsmsg->SrcPort, tmsmsg->OrgPort );
	memset( tmsmsg->SrcChannel, 0, sizeof( tmsmsg->SrcChannel ) );
	strcpy( tmsmsg->SrcChannel,tmsmsg->OrgChannel );

	if( !tmsmsg->TranDate )
		tmsmsg->TranDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->TranTime )
		tmsmsg->TranTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->LocalDate )
		tmsmsg->LocalDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->LocalTime )
		tmsmsg->LocalTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->CaptureDate )
		tmsmsg->CaptureDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->CaptureTime )
		tmsmsg->CaptureTime = ezdatetimeutil.getSysTime();

	if( !tmsmsg->SettlementDate )
		tmsmsg->SettlementDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->BusinessDate )
		tmsmsg->BusinessDate = ezdatetimeutil.getSysDate();

	if( !tmsmsg->TraceNo )
		tmsmsg->TraceNo = eztxnsequtil.genTraceNo();

	if( !strlen( tmsmsg->RefNum ) )
	{
		memset( tmsmsg->RefNum, 0, sizeof( tmsmsg->RefNum ) );
		memset( temp, 0, sizeof( temp ) );
		eztxnsequtil.genNumericRefNum( temp );
		strncpy( tmsmsg->RefNum, temp, 6 );
		sprintf( tmsmsg->RefNum + 6, "%06d", tmsmsg->TraceNo );
	}

	memset( tmsmsg->TransactionInput, 0, sizeof( tmsmsg->TransactionInput ) );
	strcpy( tmsmsg->TransactionInput, "NNNNNNNN");
	tmsmsg->TransactionInput[0] = 'P';//POS
	if( strlen( tmsmsg->Track2 ) != 0 )
	{
		tmsmsg->TransactionInput[1] = 'Y';//Card Present
		tmsmsg->TransactionInput[2] = 'Y';//Track2 Present
		tmsmsg->TransactionInput[3] = 'Y';//Expiry Date Present
		tmsmsg->TransactionInput[6] = 'Y';//CVV1/ICVV Present
	}

	if( strlen( tmsmsg->chn ) != 0 )
		tmsmsg->TransactionInput[1] = 'Y';//Card Present

	if( tmsmsg->ExpiryDate != 0 )
		tmsmsg->TransactionInput[3] = 'Y';//Expiry Date Present

	if( strlen( tmsmsg->PINBlock ) != 0 )
		tmsmsg->TransactionInput[4] = 'Y';//PIN Present

	if( tmsmsg->ChipEnabled == 'Y' )
		tmsmsg->TransactionInput[5] = 'Y';//Chip Data Present
}

void EzTMSDriver :: serviceRequest()
{
	int MsgSize, tempTxnCode, NRoutes, retval;
	struct EzTxnMsg tmsmsg, localtmsmsg;
	struct EzTMSRouteSelect tmsrouteselect_rec;
	unsigned char TCPHeader[ 20 ];
	char RouteSelectList[ 129 ], RouteSelectId[ 33 ], ChannelName[ 33 ], ConnectionRefNum[ 51 ], MerchId[ 33 ];
	bool EXTFLAG = false;
	struct EzTMSTxnMemory tmstxnmemory_rec;
	unsigned char LogFlag;
	char Txncodestr[ 7 ];
	char TempStr[ 150 ];

	while( 1 )
	{
		/*
		if( SchemaType != SCHEMA_TYPE_SINGLE )
			CloseSchema();
		*/

		trace( "TMSDriver Waiting for Request to be Serviced...." );
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		if( ReadMessage( RequestBuffer, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			sleep( 1 );
			continue;
		}

		trace( "Message of size[ %d ] Received from Channel[ %s ]", MsgSize, GetLastSenderChannelName() );

		if( readTMSChannelProperty( GetLastSenderChannelName() ) < 0 )
		{
			trace( "Error in Reading ChannelName[%s] from TMSChannelProperty", GetLastSenderChannelName() );
			continue;
		}

		if( isTerminalChannel() )
		{

			if( !IsPortMessage() )
			{
				trace( "Got Message from Terminal Channel[%s]", GetLastSenderChannelName() );
				memset( ConnectionRefNum, 0, sizeof( ConnectionRefNum ) );
				tkutil.getToken( RequestBuffer, ConnectionRefNum, 0x1c, 1 );
				hex_dump( ( unsigned char * ) RequestBuffer, MsgSize );
				if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
				{
					memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
					if( castle8583.decomposeMsg( RequestBuffer + strlen ( ConnectionRefNum ) + 1, &tmsmsg ) < 0 )
					{
						trace( "Error while decomposing message from castles pos terminal....." );
						continue;
					}
					memset( tmsmsg.RsvFld6, 0, sizeof( tmsmsg.RsvFld6 ) );
					strcpy( tmsmsg.RsvFld6, ConnectionRefNum );
					if( tmsmsg.TxnCode / 10000 == 29  )
					{
						trace( "Cash Deposit Transaction..Hence Swapping From Card and ToCard" );
						memset( TempStr, 0, sizeof( TempStr ) );
						strcpy( TempStr, tmsmsg.chn );
						memset( tmsmsg.chn, 0, sizeof( tmsmsg.chn ) );
						strcpy( tmsmsg.chn, tmsmsg.tochn );
						memset( tmsmsg.tochn, 0, sizeof( tmsmsg.tochn ) );
						strcpy( tmsmsg.tochn, TempStr );
					}
				}
				else if( !strcasecmp( getTMSProtocol(), "VERIFONE" ) )
				{
					memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
					if( castle8583.decomposeMsg( RequestBuffer + strlen ( ConnectionRefNum ) + 1, &tmsmsg, POS_PROTOCOL_HYPERCOM ) < 0 )
					{
						trace( "Error while decomposing message from castles pos terminal....." );
						continue;
					}
					memset( tmsmsg.RsvFld6, 0, sizeof( tmsmsg.RsvFld6 ) );
					strcpy( tmsmsg.RsvFld6, ConnectionRefNum );
					if( tmsmsg.TxnCode / 10000 == 29  )
					{
						trace( "Cash Deposit Transaction..Hence Swapping From Card and ToCard" );
						memset( TempStr, 0, sizeof( TempStr ) );
						strcpy( TempStr, tmsmsg.chn );
						memset( tmsmsg.chn, 0, sizeof( tmsmsg.chn ) );
						strcpy( tmsmsg.chn, tmsmsg.tochn );
						memset( tmsmsg.tochn, 0, sizeof( tmsmsg.tochn ) );
						strcpy( tmsmsg.tochn, TempStr );
					}
				}
				else
				{
					trace( "TMS Protocol[%s] Not Supported.....", getTMSProtocol() );
					continue;
				}
			}
			else
			{
				trace( "Got Message from Terminal Channel[%s]", GetLastSenderChannelName() );
				if( !strcasecmp( getTMSProtocol(), "CASTLES" ) || !strcasecmp( getTMSProtocol(), "VERIFONE" ) )
				{
					memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
					if( castle8583.decomposeMsg( RequestBuffer, &tmsmsg ) < 0 )
					{
						trace( "Error while decomposing message from castles pos terminal....." );
						continue;
					}
				}
				else
				{
					trace( "TMS Protocol[%s] Not Supported.....", getTMSProtocol() );
					continue;
				}
			}
			memset( tmsmsg.OrgPort, 0, sizeof( tmsmsg.OrgPort ) );
			strcpy( tmsmsg.OrgPort, GetLastSenderChannelName() );
			tempTxnCode = castle8583.getTMSTxnCode( tmsmsg.TxnCode );
			tmsmsg.TxnCode = tempTxnCode;
		}
		else if ( !isExternalApplication() )
		{
			memset( &tmsmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &tmsmsg, RequestBuffer, sizeof( struct EzTxnMsg ) );
			trace( DEBUG_NORMAL, "<RECV>Channel(%s)AcqInst(%s)MerchantId(%s)TerminalId(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", GetLastSenderChannelName(), tmsmsg.AcquirerInst, tmsmsg.AcceptorId, tmsmsg.TerminalId, tmsmsg.DeviceType,tmsmsg.OrgChannel, tmsmsg.SrcChannel, tmsmsg.OrgPort, tmsmsg.SrcPort, tmsmsg.DestPort, tmsmsg.MsgType, tmsmsg.chn, tmsmsg.FromAccount, tmsmsg.TxnCode, tmsmsg.Amount, tmsmsg.TerminalId, tmsmsg.TraceNo, tmsmsg.TranDate, tmsmsg.TranTime, tmsmsg.LocalDate, tmsmsg.LocalTime, tmsmsg.RespCode, tmsmsg.ReasonCode, tmsmsg.RefNum, tmsmsg.NetworkId );
		}

		if( !isValidTerminal( &tmsmsg ) )
		{
			trace( "Terminal with MachineId[%s] is not valid....", tmsmsg.MachineId );
			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_InvalidMachineId;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			continue;
		}

		if( tmsmsg.MsgType == 500 )
		{
			trace( "calling process500(Settlement)" );
			process500( tmsmsg );
			continue;
		}

		if( tmsmsg.MsgType == 320 )
		{
			trace( "calling process320(BatchUpload)" );
			process320( &tmsmsg );
			continue;
		}

		if( tmsmsg.MsgType == EZTMS_MTYPE_NtwkMgmtRequest && tmsmsg.TxnCode == EZTMS_Txn_Echo )
		{
			trace( "calling processEcho" );
			processEchoRequest( &tmsmsg );
			continue;
		}

		if( tmsmsg.MsgType == EZTMS_MTYPE_NtwkMgmtRequest && ( tmsmsg.TxnCode == EZTMS_Txn_KeyDownload || tmsmsg.TxnCode == 920000 ) )
		{
			trace( "calling processKey" );
			processKeyRequest( &tmsmsg );
			continue;
		}

		if( tmsmsg.MsgType == EZTMS_MTYPE_UserMgmtRequest  )
		{
			trace( "calling processUserMgmt" );
			processTerminalUserRequest( &tmsmsg );
			continue;
		}

		if( readTMSInBoundProperty( tmsmsg.MsgType, tmsmsg.TxnCode, GetLastSenderChannelName() ) < 0 )
		{
			if( tmsmsg.MsgType != 400 && tmsmsg.MsgType != 420 )
			{
				trace( "Error in reading MsgType[%d] TxnCode[%d] ChannelName[%s] from TMSInBoundProperty....", tmsmsg.MsgType, tmsmsg.TxnCode, GetLastSenderChannelName() );
				continue;
			}
		}

		if( isInBoundTxnMsg() && tmsmsg.MsgType != 400 && tmsmsg.MsgType != 420 )
		{
			if( strlen( tmsmsg.chn ) )
			{
				if( !strlen( tmsmsg.m_chn ) )
				{
					memset( tmsmsg.m_chn, 0, sizeof( tmsmsg.m_chn ) );
					ezpadssutil.maskString( tmsmsg.chn, 6, strlen( tmsmsg.chn ) - 4, '*', tmsmsg.m_chn );
				}
			}
			trace( "Transaction Message Received from Channel[%s]", GetLastSenderChannelName() );
			logTerminalStatus( &tmsmsg, TERMINAL_STATUSID_TXN );

			memset( Txncodestr, 0, sizeof( Txncodestr ) );
			sprintf( Txncodestr, "%06d", tmsmsg.TxnCode );
			if( !isTxnAllowed( terminalprofile_rec.InstId, terminalprofile_rec.TerminalType, Txncodestr, tmsmsg.chn ) )
			{
				trace( "Transaction Not Allowed on TerminalType [ %s ] and Chn [ %s ]", terminalprofile_rec.TerminalType, tmsmsg.chn );
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_TransactionNotAllowed;
				writeToPOS( GetLastSenderChannelName(), &tmsmsg );
				continue;
			}
			if( !isTxnAllowedonProduct( terminalprofile_rec.InstId, terminalprofile_rec.TerminalType, Txncodestr, tmsmsg.chn ) )
			{
				trace( "Transaction Not Allowed on TerminalType [ %s ] and Chn [ %s ]", terminalprofile_rec.TerminalType, tmsmsg.chn );
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_TransactionNotAllowed;
				writeToPOS( GetLastSenderChannelName(), &tmsmsg );
				continue;
			}
			if( isInBoundNewTxnRequest() || isInBoundNewFinTxnRequest() )
			{
				trace( "New Request Received from TerminalId[%s]", tmsmsg.TerminalId );
				populateNewTerminalRequest( &tmsmsg );

				if( tmsmsg.TxnCode / 10000 == 83 || tmsmsg.TxnCode /10000 == 84 )
				{
					char MobileNo[ 33 ], MeterNo[ 33 ];

					int count = tkutil.getNToken( tmsmsg.RsvFld2, 0x1c  );
					if( count == 2 )
					{
						memset( MeterNo, 0, sizeof( MeterNo ) );
						tkutil.getToken( tmsmsg.RsvFld2, MeterNo, 0x1c, 1 );
						memset( MobileNo, 0, sizeof( MobileNo ) );
						tkutil.getToken( tmsmsg.RsvFld2, MobileNo, 0x1c, 2 );
						memset( tmsmsg.RsvFld2, 0, sizeof( tmsmsg.RsvFld2 ) );
						strcpy( tmsmsg.RsvFld2, MeterNo );
						memset( tmsmsg.RsvFld3, 0, sizeof( tmsmsg.RsvFld3 ) );
						strcpy( tmsmsg.RsvFld3, MobileNo );
					}
				}
				memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, TMSTxnRefNum ) == 1 )//Mohan
				{
					trace( "TXN WITH TXNREFNUM[%s] DUPLICATED...", TMSTxnRefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_DuplicateTransaction;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
			}
			else if ( isInBoundTxnVoidRequest() )
			{
				int RelTxnCode;
				char TxnCodeStr1[ 7 ], TxnCodeStr2[ 7 ];

				trace( "Got Void Request[%d] TxnCode[%d] from Terminal[%s]", tmsmsg.MsgType, tmsmsg.TxnCode, terminalprofile_rec.MachineId );
				memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, TMSTxnRefNum ) >= 0 )
				{
					trace( "TXN WITH TXNREFNUM[%s] ALREADY VOIDED...", TMSTxnRefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_DuplicateTransaction;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}

				if( tmsmsg.TxnCode / 10000 == EZTMS_Txn_Void )
				{
					memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
					sprintf( TxnCodeStr1, "%02d", EZTMS_Txn_Refund );
					memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
					sprintf( TxnCodeStr2, "%06d", tmsmsg.TxnCode );
					strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );

					tempTxnCode = tmsmsg.TxnCode;
					tmsmsg.TxnCode = atoi( TxnCodeStr1 );

					memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
					getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum );
					tmsmsg.TxnCode = tempTxnCode;

					if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) >= 0 )
					{
						trace( "TXN WITH TXNREFNUM[%s] ALREADY REFUNDED...", OldTMSTxnRefNum );
						tmsmsg.MsgType += 10;
						tmsmsg.RespCode = EZTMS_RC_DuplicateTransaction;
						writeToPOS( GetLastSenderChannelName(), &tmsmsg );
						continue;
					}
				}

				RelTxnCode = getRelatedTxnCode( terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
				if( RelTxnCode < 0 )
				{
					trace( "Error in Searching Relation TxnCode for TerminalType[%s] MsgType[%d] TxnCode[%d]", terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
				sprintf( TxnCodeStr1, "%02d", RelTxnCode );
				memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
				sprintf( TxnCodeStr2, "%06d", tmsmsg.TxnCode );
				strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );
				memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum, TxnCodeStr1 );
				trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchBatchTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) < 0 )
				{
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) < 0 )
				{
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}

				if( strcmp( tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount ) )
				{
					trace( "TxnAmount[%s] is Not Matching with OldTxnAmount[%s]", tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_InvalidAmount;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				if( strcmp( tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum ) )
				{
					trace( "RefNum[%s] is Not Matching with OldRefNum[%s]", tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				populateOldTerminalRequest( &tmsmsg, &tmstxnmemory_rec.txnmsg );
			}
			else if ( isInBoundTxnPreAuthCompRequest() )
			{
				memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, TMSTxnRefNum ) >= 0 )
				{
					trace( "TXN WITH TXNREFNUM[%s] ALREADY REFUNDED...", TMSTxnRefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_DuplicateTransaction;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				trace( "Got Old Request[%d] TxnCode[%d] from Terminal[%s]", tmsmsg.MsgType, tmsmsg.TxnCode, terminalprofile_rec.MachineId );
				int RelTxnCode;
				char TxnCodeStr1[ 7 ], TxnCodeStr2[ 7 ];
				RelTxnCode = getRelatedTxnCode( terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
				if( RelTxnCode < 0 )
				{
					trace( "Error in Searching Relation TxnCode for TerminalType[%s] MsgType[%d] TxnCode[%d]", terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
				sprintf( TxnCodeStr1, "%02d", RelTxnCode );
				memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
				sprintf( TxnCodeStr2, "%06d", tmsmsg.TxnCode );
				strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );
				memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum, TxnCodeStr1 );
				trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) < 0 )
				{
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				if( strcmp( tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum ) )
				{
					trace( "RefNum[%s] is Not Matching with OldRefNum[%s]", tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				if( strcmp( tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount ) )
				{
					trace( "TxnAmount[%s] is Not Matching with OldTxnAmount[%s]", tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_InvalidAmount;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				populateOldTerminalRequest( &tmsmsg, &tmstxnmemory_rec.txnmsg );
			}
			else if ( isInBoundTxnRefundRequest() )
			{
				memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, TMSTxnRefNum ) >= 0 )
				{
					trace( "TXN WITH TXNREFNUM[%s] ALREADY REFUNDED...", TMSTxnRefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_DuplicateTransaction;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				trace( "Got Old Request[%d] TxnCode[%d] from Terminal[%s]", tmsmsg.MsgType, tmsmsg.TxnCode, terminalprofile_rec.MachineId );
				int RelTxnCode;
				char TxnCodeStr1[ 7 ], TxnCodeStr2[ 7 ];
				RelTxnCode = getRelatedTxnCode( terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
				if( RelTxnCode < 0 )
				{
					trace( "Error in Searching Relation TxnCode for TerminalType[%s] MsgType[%d] TxnCode[%d]", terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
				sprintf( TxnCodeStr1, "%02d", RelTxnCode );
				memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
				sprintf( TxnCodeStr2, "%06d", tmsmsg.TxnCode );
				strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );
				memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum, TxnCodeStr1 );
				trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) < 0 )
				{
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}

				if( !strlen( tmsmsg.RefNum ) )
					strcpy( tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum );

				if( strcmp( tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum ) )
				{
					trace( "RefNum[%s] is Not Matching with OldRefNum[%s]", tmsmsg.RefNum, tmstxnmemory_rec.txnmsg.RefNum );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				if( amtutil.compareAmount( tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount ) > 0 )
				{
					trace( "TxnAmount[%s] is Greater Than OldTxnAmount[%s]..Cannot Do Refund", tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_InvalidAmount;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}

				trace( "Original Transaction Amount[%s] Refund Amount[%s]", tmstxnmemory_rec.txnmsg.Amount, tmsmsg.Amount );
				if( !strcmp( tmstxnmemory_rec.txnmsg.Amount, tmsmsg.Amount ) )
					tmsmsg.RespCode = 103;
				else
				{
					memset( tmsmsg.DispAmount, 0, sizeof( tmsmsg.DispAmount ) );
					strcpy( tmsmsg.DispAmount, tmsmsg.Amount );

					memset( tmsmsg.Amount, 0, sizeof( tmsmsg.Amount ) );
					strcpy( tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount );
					tmsmsg.RespCode = 102;
				}
				populateOldTerminalRequest( &tmsmsg, &tmstxnmemory_rec.txnmsg );
			}
			/*
			else if ( isInBoundTxnRevRequest() )
			{
				trace( "Got Reversal Request[%d] TxnCode[%d] from Terminal[%s]", tmsmsg.MsgType, tmsmsg.TxnCode, terminalprofile_rec.MachineId );
				if( isInBoundLeaveTxn() )
				{
					trace( "Reversal Process Flag is Configured as Leave..Hence No Need to Process" );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_Approved;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum );
				trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
				memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
				if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) < 0 )
				{
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				if( strcmp( tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount ) )
				{
					trace( "TxnAmount[%s] is Not Matching with OldTxnAmount[%s]", tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				populateOldTerminalRequest( &tmsmsg, &tmstxnmemory_rec.txnmsg );
			}
			*/
		}
		else
			trace( "Not a Transaction Message...." );
		
		if( tmsmsg.MsgType == 400 || tmsmsg.MsgType == 420 )
		{
			if( strlen( tmsmsg.chn ) )
			{
				if( !strlen( tmsmsg.m_chn ) )
				{
					memset( tmsmsg.m_chn, 0, sizeof( tmsmsg.m_chn ) );
					ezpadssutil.maskString( tmsmsg.chn, 6, strlen( tmsmsg.chn ) - 4, '*', tmsmsg.m_chn );
				}
			}
			trace( "Transaction Message Received from Channel[%s]", GetLastSenderChannelName() );
			logTerminalStatus( &tmsmsg, TERMINAL_STATUSID_TXN );

			memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
			getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );

			trace( "Got Reversal Transaction..." );
			if( !strlen( tmsmsg.Amount ) )
			{
				trace( "Amount[%s] is Null..Dropping Reversal", tmsmsg.Amount );
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_Approved;
				writeToPOS( GetLastSenderChannelName(), &tmsmsg );
				continue;
			}
			if( !strcmp( tmsmsg.Amount, "000000000000" ) )
			{
				trace( "Amount[%s] is Zero..Dropping Reversal", tmsmsg.Amount );
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_Approved;
				writeToPOS( GetLastSenderChannelName(), &tmsmsg );
				continue;
			}
			memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
			getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum );
			trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
			memset( &tmstxnmemory_rec.txnmsg, 0, sizeof( struct EzTxnMsg ) );
			if( ezmmsdbutil.searchOldTxn( &tmstxnmemory_rec.txnmsg, OldTMSTxnRefNum ) < 0 )
			{
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
				writeToPOS( GetLastSenderChannelName(), &tmsmsg );
				continue;
			}
			if( strcmp( tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount ) )
			{
				trace( "TxnAmount[%s] is Not Matching with OldTxnAmount[%s]", tmsmsg.Amount, tmstxnmemory_rec.txnmsg.Amount );
				tmsmsg.MsgType += 10;
				tmsmsg.RespCode = EZTMS_RC_UnableLocateRecord;
				writeToPOS( GetLastSenderChannelName(), &tmsmsg );
				continue;
			}
			populateOldTerminalRequest( &tmsmsg, &tmstxnmemory_rec.txnmsg );
			ezmmsdbutil.generateTxnNarration( &tmsmsg );
			ezmmsdbutil.checkTransactionEntries( &tmsmsg );
			ezmmsdbutil.insertMMSTransactionLog( &tmsmsg, TMSTxnRefNum );


			tmsmsg.MsgType += 10;
			tmsmsg.RespCode = EZTMS_RC_Approved;
			writeToPOS( GetLastSenderChannelName(), &tmsmsg );
			if( tmsmsg.MsgType == 410 || tmsmsg.MsgType == 430 )
			{
				trace( "Got Reversal Response with ResponseCode[%d]", tmsmsg.RespCode );
				memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
				ezmmsdbutil.generateTxnNarration( &tmsmsg );
				ezmmsdbutil.checkTransactionEntries( &tmsmsg );
				ezmmsdbutil.insertMMSTransactionLog( &tmsmsg, TMSTxnRefNum );
				ezmmsdbutil.deleteMMSTransactionBatch( &tmsmsg, TMSTxnRefNum );
				ezmmsdbutil.insertMMSTransactionMaster( &tmsmsg, TMSTxnRefNum, TXN_STATUS_SETTLED, '1', TMS_TXN_REASON_MATCH );
				ezmmsdbutil.deleteMMSTransactionRef( TMSTxnRefNum );
			}

			tmsmsg.MsgType -= 10;
			if( tmsmsg.MsgType == 400 )
				tmsmsg.MsgType = 420;
			tmsmsg.RespCode = 103;
			writeToInternalChannel( "EzTxnMgr",  &tmsmsg );
			continue;
		}

		if( isInBoundTxnMsg() && tmsmsg.MsgType != 400 && tmsmsg.MsgType != 420 )
		{
			memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
			getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
			ezmmsdbutil.generateTxnNarration( &tmsmsg );
			ezmmsdbutil.checkTransactionEntries( &tmsmsg );
			ezmmsdbutil.insertMMSTransactionLog( &tmsmsg, TMSTxnRefNum );

			if( ( isInBoundFinTxnResponse() || isInBoundTxnRefundResponse() || isInBoundTxnPreAuthCompResponse() ) && !tmsmsg.RespCode )
			{
				ezmmsdbutil.insertMMSTransactionBatch( &tmsmsg, TMSTxnRefNum, '1', TMS_TXN_REASON_NOT_FOUND_TERMINAL );
				ezmmsdbutil.insertMMSTransactionMaster( &tmsmsg, TMSTxnRefNum, TXN_STATUS_PENDING, '1', TMS_TXN_REASON_NOT_FOUND_TERMINAL );
				ezmmsdbutil.insertMMSTransactionRef( &tmsmsg, TMSTxnRefNum );
			}
			else if( isInBoundTxnVoidResponse() && !tmsmsg.RespCode )
			{
				int RelTxnCode;
				char TxnCodeStr1[ 7 ], TxnCodeStr2[ 7 ];
				RelTxnCode = getRelatedTxnCode( terminalprofile_rec.TerminalType, tmsmsg.MsgType - 10, tmsmsg.TxnCode );
				if( RelTxnCode < 0 )
				{
					trace( "Error in Searching Relation TxnCode for TerminalType[%s] MsgType[%d] TxnCode[%d]", terminalprofile_rec.TerminalType, tmsmsg.MsgType, tmsmsg.TxnCode );
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
				sprintf( TxnCodeStr1, "%02d", RelTxnCode );
				memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
				sprintf( TxnCodeStr2, "%06d", tmsmsg.TxnCode );
				strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );
				memset( OldTMSTxnRefNum, 0, sizeof( OldTMSTxnRefNum ) );
				getTMSTxnRefNum( &tmsmsg, OldTMSTxnRefNum, TxnCodeStr1 );
				trace( "Generated LookUp POSTxnRefNum as [%s]", OldTMSTxnRefNum );
				tmsmsg.TxnCode = atoi( TxnCodeStr2 );
				//ezmmsdbutil.deleteMMSTransactionBatch( &tmsmsg, OldTMSTxnRefNum );
				ezmmsdbutil.insertMMSTransactionMaster( &tmsmsg, TMSTxnRefNum, TXN_STATUS_SETTLED, '1', TMS_TXN_REASON_MATCH );
				ezmmsdbutil.insertMMSTransactionBatch( &tmsmsg, TMSTxnRefNum, '1', TMS_TXN_REASON_NOT_FOUND_TERMINAL );
				ezmmsdbutil.deleteMMSTransactionRef( OldTMSTxnRefNum );
			}
			/*
			else if( isInBoundTxnRevResponse() )
			{
				trace( "Reversal Response" );
				ezmmsdbutil.deleteMMSTransactionBatch( &tmsmsg, TMSTxnRefNum );
				ezmmsdbutil.insertMMSTransactionMaster( &tmsmsg, TMSTxnRefNum, TXN_STATUS_SETTLED, '1', TMS_TXN_REASON_MATCH );
				ezmmsdbutil.deleteMMSTransactionRef( TMSTxnRefNum );
			}
			*/
			else if( isInBoundTxnResponse() && !tmsmsg.RespCode )
			{
				ezmmsdbutil.insertMMSTransactionMaster( &tmsmsg, TMSTxnRefNum, TXN_STATUS_SETTLED, '1' );
				ezmmsdbutil.insertMMSTransactionRef( &tmsmsg, TMSTxnRefNum );
			}
		}

		if( tmsmsg.MsgType == 410 || tmsmsg.MsgType == 430 )
		{
			trace( "Got Reversal Response with ResponseCode[%d]", tmsmsg.RespCode );
			memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
			getTMSTxnRefNum( &tmsmsg, TMSTxnRefNum );
			ezmmsdbutil.generateTxnNarration( &tmsmsg );
			ezmmsdbutil.checkTransactionEntries( &tmsmsg );
			ezmmsdbutil.insertMMSTransactionLog( &tmsmsg, TMSTxnRefNum );
			ezmmsdbutil.deleteMMSTransactionBatch( &tmsmsg, TMSTxnRefNum );
			ezmmsdbutil.insertMMSTransactionMaster( &tmsmsg, TMSTxnRefNum, TXN_STATUS_SETTLED, '1', TMS_TXN_REASON_MATCH );
			ezmmsdbutil.deleteMMSTransactionRef( TMSTxnRefNum );
			continue;
		}

		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
		if( getTMSRouteSelectList( &tmsmsg, RouteSelectList ) < 0 )
		{
			trace( "Error in reading TMSRouteSelectList.....Dropping Message" );
			if( isInBoundNewRequest() )
			{
				if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
				{
					tmsmsg.MsgType += 10;
					tmsmsg.RespCode = EZTMS_RC_UnableToProcess;
					writeToPOS( GetLastSenderChannelName(), &tmsmsg );
					continue;
				}
				continue;
			}
		}

		NRoutes = tkutil.getNToken( RouteSelectList, ',' );
		for( int i = 0; i < NRoutes; i++ )
		{
			memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
			tkutil.getTokenExSpaces( RouteSelectList, RouteSelectId, ',', i + 1 );

			memset( &tmsrouteselect_rec, 0, sizeof( struct EzTMSRouteSelect ) );
			if( readTMSRouteSelect( RouteSelectId, &tmsrouteselect_rec ) < 0 )
			{
					trace( DEBUG_ERROR, "Error in Reading RouteSelectId[%s] From TMSRouteSelect...", RouteSelectId );
					continue;
			}

			trace( DEBUG_NORMAL, "Read ChannelName[%s] MsgTranslateId[%s] from TMSRouteSelect for RouteSelectId[%s]",  tmsrouteselect_rec.ChannelName, tmsrouteselect_rec.MsgTranslateId, RouteSelectId );

			memset( &localtmsmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &localtmsmsg, &tmsmsg, sizeof( struct EzTxnMsg ) );

			if( strcmp( tmsrouteselect_rec.MsgTranslateId, "*" ) )
			{
				if( translateMsg( tmsrouteselect_rec.MsgTranslateId, &localtmsmsg ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Reading MsgTranslateId[%s] from EzTMSMsgTranslate Table", tmsrouteselect_rec.MsgTranslateId );
					continue;

				}
			}
		
			if( !strcmp( tmsrouteselect_rec.ChannelName, EZTMSIMF_DESTPORT ) )
			{
				EXTFLAG = true;
				if( ( !strlen( localtmsmsg.DestPort ) ) || ( !strcmp( localtmsmsg.DestPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "DestPort is NULL..Cannot Route Message to DestPort");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtmsmsg.DestPort );
			}
			if( !strcmp( tmsrouteselect_rec.ChannelName, EZTMSIMF_ORGPORT ) )
			{
				EXTFLAG = true;
				if( ( !strlen( localtmsmsg.OrgPort ) ) || ( !strcmp( localtmsmsg.OrgPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "OrgPort is NULL..Cannot Route Message to OrgPort");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtmsmsg.OrgPort );
			}
			else
			{
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, tmsrouteselect_rec.ChannelName );
				EXTFLAG = false;
			}
			if( strcmp( ChannelName, "*" ) && strcmp( ChannelName, GetSourceChannelName() ) )
			{
				if( EXTFLAG )
				{
					/*
					if( ( tmsmsg.TxnCode / 10000 == 61 || tmsmsg.TxnCode / 10000 == 0 || tmsmsg.TxnCode / 10000 == 1 ) && ( !tmsmsg.RespCode ) && ( tmsmsg.MsgType == 210 ) )
					{
						trace( "Drop Message for Reversal" );
					}
					else if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
						writeToPOS( ChannelName, &localtmsmsg );
					*/
					if( !strcasecmp( getTMSProtocol(), "CASTLES" ) )
						writeToPOS( ChannelName, &localtmsmsg );
				}
				else
				{
					writeToInternalChannel( ChannelName,  &localtmsmsg );
				}
			}
		}
	}
}

void EzTMSDriver :: processTerminalUserRequest( struct EzTxnMsg *tmsmsg )
{
	int retval;
	char TermPINKey_LMK[ 65 ], TermPINKey_TMK[ 65 ], TermPINKey_KCV[ 65 ], TempStr[ 255 ];
	char CatCode[ 17 ], UserName[ 33 ], Password[ MMS_PWD_SIZE + 1 ], hPassword[ MMS_PWD_SIZE + 1 ];

	if( strlen( tmsmsg->RsvFld2 ) )
	{
		trace( "UserDetails[%s]", tmsmsg->RsvFld2 );
		memset( TempStr, 0, sizeof( TempStr ) );
		tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 1 );
		memset( CatCode, 0, sizeof( CatCode ) );
		strcpy( CatCode, TempStr );
		if( !strcmp( CatCode, "1" ) )
		{
			memset( UserName, 0, sizeof( UserName ) );
			strcpy( UserName, "Admin" );
			memset( TempStr, 0, sizeof( TempStr ) );
			tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 2 );
			memset( Password, 0, sizeof( Password ) );
			strcpy( Password, TempStr );
		}
		else if ( !strcmp( CatCode, "2" ) )
		{
			memset( TempStr, 0, sizeof( TempStr ) );
			tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 2 );
			memset( UserName, 0, sizeof( UserName ) );
			strcpy( UserName, TempStr );
			memset( TempStr, 0, sizeof( TempStr ) );
			tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 3 );
			memset( Password, 0, sizeof( Password ) );
			strcpy( Password, TempStr );
		}
		else
		{
			trace( "Invalid UserCategory[%s]...", CatCode );
			tmsmsg->RespCode = 5;
			tmsmsg->MsgType += 10;
			writeToPOS( GetLastSenderChannelName(), tmsmsg );
			return;
		}
		memset( hPassword, 0, sizeof( hPassword ) );
		ezpadssutil.tokenizeString( Password, "NOTDEFINED", hPassword );
	}
	else
	{
		trace( "Invalid UserDetails for MachineId[ %s ]...", tmsmsg->MachineId );
		tmsmsg->RespCode = 5;
		tmsmsg->MsgType += 10;
		writeToPOS( GetLastSenderChannelName(), tmsmsg );
		return;
	}


	if( tmsmsg->TxnCode == 970001 )  //Change Terminal Password
	{
		if( ezmmsdbutil.verifyTerminalUser( tmsmsg->MachineId, CatCode, UserName, hPassword ) < 0 )
		{
			trace( "Error in Verifying UserName[%s]Pwd[%s] for MachineId[%s] CatCode[%s]", UserName, hPassword, tmsmsg->MachineId, CatCode );
			tmsmsg->RespCode = 55;
			tmsmsg->MsgType += 10;
			writeToPOS( GetLastSenderChannelName(), tmsmsg );
			return;
		}
		memset( TempStr, 0, sizeof( TempStr ) );
		tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 4 );
		if( strlen( TempStr) ==  0 )
		{
			trace( "Error in New Password Pwd[%s] for MachineId[%s] ", TempStr,  tmsmsg->MachineId );
			tmsmsg->RespCode = 55;
			tmsmsg->MsgType += 10;
			writeToPOS( GetLastSenderChannelName(), tmsmsg );
			return;

		}
		memset( Password, 0, sizeof( Password ) );
		strcpy( Password, TempStr );
		memset( hPassword, 0, sizeof( hPassword ) );
		ezpadssutil.tokenizeString( Password, "NOTDEFINED", hPassword );
		if(  ezmmsdbutil.updateTermUserPassword( tmsmsg->MachineId, CatCode, UserName, hPassword ) < 0 )
		{
			trace( "Error in Updating UserName[%s]Pwd[%s] for MachineId[%s] CatCode[%s]", UserName, hPassword, tmsmsg->MachineId, CatCode );
			tmsmsg->RespCode = 5;
			tmsmsg->MsgType += 10;
			writeToPOS( GetLastSenderChannelName(), tmsmsg );
			return;
		}

	}
	else if( tmsmsg->TxnCode == 970002 )  //Reset the terminal user password
	{
		memset( TempStr, 0, sizeof( TempStr ) );
		tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 2 );
		memset( UserName, 0, sizeof( UserName ) );
		strcpy( UserName, TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tkutil.getToken( tmsmsg->RsvFld2, TempStr, 0x1c, 3 );
		memset( Password, 0, sizeof( Password ) );
		strcpy( Password, TempStr );
		memset( CatCode, 0, sizeof( CatCode ) );
		strcpy( CatCode, "2" );
		memset( hPassword, 0, sizeof( hPassword ) );
		ezpadssutil.tokenizeString( Password, "NOTDEFINED", hPassword );
		if(  ezmmsdbutil.updateTermUserPassword( tmsmsg->MachineId, CatCode, UserName, hPassword ) < 0 )
		{
			trace( "Error in Updating UserName[%s]Pwd[%s] for MachineId[%s] CatCode[%s]", UserName, hPassword, tmsmsg->MachineId, CatCode );
			tmsmsg->RespCode = 5;
			tmsmsg->MsgType += 10;
			writeToPOS( GetLastSenderChannelName(), tmsmsg );
			return;
		}
	}

	tmsmsg->RespCode = 0;
	tmsmsg->MsgType += 10;
	writeToPOS( GetLastSenderChannelName(), tmsmsg );
	return;


}

int main( int argc, char **argv )
{
	EzTMSDriver eztmsdriverobj;
	eztmsdriverobj.initTMSDriver( argv[ 0 ] );
	eztmsdriverobj.serviceRequest();
	return 1;
}



	

