#include <ezbusiness/ezposdriver.h>

int EzPOSDriver :: initPOSDriver( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezposdriver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug( );

	trace( "^^^^^^^^^^^EzPOSDriver Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( POSDRIVERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating [%s] Channel", POSDRIVERCHANNEL );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initPOSTxnMemoryUtil( this ) < 0 )
	{
		trace( "Error in Initializing POSTxnMemoryUtil..." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initPOSDriverUtil(  this ) < 0 )
	{
		trace( "Error in Initializing InitPOSDriverUtil" );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMCCInfo() < 0 )
	{
		trace( "Error in Loading POSMCCInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMerchantTypeInfo() < 0 )
	{
		trace( "Error in Loading POSMerchantTypeInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMerchantInfo() < 0 )
	{
		trace( "Error in Loading POSMerchantInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTerminalTypeInfo() < 0 )
	{
		trace( "Error in Loading POSTerminalTypeInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTerminalInfo() < 0 )
	{
		trace( "Error in Loading POSTerminalInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSStoreInfo() < 0 )
	{
		trace( "Error in Loading POSStoreInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTxnInfo() < 0 )
	{
		trace( "Error in Loading POSTxnInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSRespCodeInfo() < 0 )
	{
		trace( "Error in Loading POSRespCodeInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSInBoundProperty() < 0 )
	{
		trace( "Error in Loading POSInBoundProperty...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSRouteSelect() < 0 )
	{
		trace( "Error in Loading POSRouteSelect...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSRouteInfo() < 0 )
	{
		trace( "Error in Loading POSRouteInfo...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSMsgTranslate() < 0 )
	{
		trace( "Error in Loading POSMsgTranslate...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSChannelProperty() < 0 )
	{
		trace( "Error in Loading POSChannelProperty...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTxnRefSelect() < 0 )
	{
		trace( "Error in Loading POSTxnRefSelect...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadPOSTxnRel() < 0 )
	{
		trace( "Error in Loading POSTxnRel...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( hypercomutilobj.initHypercomUtil( this, &ezdatetimeutil ) < 0 )
	{
		trace( "Error in Initializing HypercomUtil..." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzSecurityUtil..." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnsequtil.initTxnSeqUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnSeqUtil...." );
		trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

bool EzPOSDriver :: isValidTerminal( struct EzTxnMsg *txnmsg )
{
	struct EzPOSTerminalInfo posterminfo;
	struct EzPOSTerminalTypeInfo postermtypeinfo;
	struct EzPOSMerchantInfo merchantinfo;
	struct EzPOSMerchantTypeInfo merchanttypeinfo;

	memset( &posterminfo, 0, sizeof( struct EzPOSTerminalInfo ) );
	if( readPOSTerminalInfo( txnmsg->TerminalId, txnmsg->AcceptorId, &posterminfo ) < 0 )
	{
		trace( "Error in Reading TerminalId[%s] MerchantId[%s] from POSTerminalInfo Table....", txnmsg->TerminalId, txnmsg->AcceptorId );
		txnmsg->RespCode = EZLINK_RC_InvalidTerminalId;
		txnmsg->ReasonCode = EZLINK_Reason_POSTerminalInfo_Err;
		return false;
	}

	if( posterminfo.TerminalStatus != 'A' && posterminfo.TerminalStatus != 'a' )
	{
		trace( "POS Terminal Status is not Active for TerminalId[%s] MerchantId[%s]", txnmsg->TerminalId, txnmsg->AcceptorId );
		txnmsg->RespCode = EZLINK_RC_InvalidTerminalId;
		return false;
	}

	memset( &postermtypeinfo, 0, sizeof( struct EzPOSTerminalTypeInfo ) );
	if( readPOSTerminalTypeInfo( posterminfo.TerminalType, &postermtypeinfo ) < 0 )
	{
		trace( "POS TerminalType[%s] is not configured in POSTerminalTypeInfo", posterminfo.TerminalType );
		txnmsg->RespCode = EZLINK_RC_InvalidTerminalId;
		return false;
	}
	//trace( DEBUG_TEST, "Read TerminalId[%s] with MerchantId[%s] InstId[%s] StoreId[%s] MCC[%d]...", posterminfo.TerminalId, posterminfo.MerchantId, posterminfo.InstId, posterminfo.StoreId, posterminfo.MCC );

	memset( &merchantinfo, 0, sizeof( struct EzPOSMerchantInfo ) );
	if( readPOSMerchantInfo( posterminfo.MerchantId, &merchantinfo ) < 0 )
	{
		trace( "Error in Reading MerchantId[%s] from POSMerchantInfo Table....", posterminfo.MerchantId );
		txnmsg->RespCode = EZLINK_RC_InvalidAcceptorId;
		txnmsg->ReasonCode = EZLINK_Reason_POSMerchantInfo_Err;
		return false;
	}

	memset( &merchanttypeinfo, 0, sizeof( struct EzPOSMerchantTypeInfo ) );
	if( readPOSMerchantTypeInfo( merchantinfo.MerchantType, &merchanttypeinfo ) < 0 )
	{
		trace( "Error in Reading MerchantType[%s] from POSMerchantTypeInfo Table....", merchantinfo.MerchantType );
		txnmsg->RespCode = EZLINK_RC_InvalidAcceptorId;
		txnmsg->ReasonCode = EZLINK_Reason_POSMerchantInfo_Err;
		return false;
	}
	txnmsg->AcqCurrencyCode = posterminfo.CurrencyCode;
	txnmsg->MerchantType = posterminfo.MCC;
	memset( txnmsg->DeviceSubType, 0, sizeof( txnmsg->DeviceSubType ) );
	strcpy( txnmsg->DeviceSubType, posterminfo.TerminalType );
	memset( txnmsg->AcqBranchCode, 0, sizeof( txnmsg->AcqBranchCode ) );
	strcpy( txnmsg->AcqBranchCode, posterminfo.AcquirerCode );
	memset( txnmsg->AcquirerInst, 0, sizeof( txnmsg->AcquirerInst ) );
	strcpy( txnmsg->AcquirerInst, posterminfo.InstId );
	memset( txnmsg->TerminalLocation, 0, sizeof( txnmsg->TerminalLocation ) );
	strcpy( txnmsg->TerminalLocation, posterminfo.TerminalLocation );
	memset( txnmsg->PinKey, 0, sizeof( txnmsg->PinKey ) );
	strcpy( txnmsg->PinKey, posterminfo.TermPINKey );

	if( !strlen( txnmsg->BatchId ) )
	{
		memset( txnmsg->BatchId, 0, sizeof( txnmsg->BatchId ) );
		strcpy( txnmsg->BatchId, posterminfo.BatchId );
	}
	return true;
}

void EzPOSDriver :: populateNewPOSRequest( struct EzTxnMsg *txnmsg )
{
	memset( txnmsg->DeviceType, 0, sizeof( txnmsg->DeviceType ) );
	strcpy( txnmsg->DeviceType, "POS" );

	memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
	strcpy( txnmsg->OrgChannel, GetSourceChannelName() );
	memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
	strcpy( txnmsg->OrgPort, GetLastSenderChannelName() );
	memset( txnmsg->SrcPort, 0, sizeof( txnmsg->SrcPort ) );
	strcpy( txnmsg->SrcPort, txnmsg->OrgPort );
	memset( txnmsg->SrcChannel, 0, sizeof( txnmsg->SrcChannel ) );
	strcpy( txnmsg->SrcChannel,txnmsg->OrgChannel );

	if( !txnmsg->TranDate )
		txnmsg->TranDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->TranTime )
		txnmsg->TranTime = ezdatetimeutil.getSysTime();

	if( !txnmsg->LocalDate )
		txnmsg->LocalDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->LocalTime )
		txnmsg->LocalTime = ezdatetimeutil.getSysTime();

	if( !txnmsg->CaptureDate )
		txnmsg->CaptureDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->CaptureTime )
		txnmsg->CaptureTime = ezdatetimeutil.getSysTime();

	if( !txnmsg->SettlementDate )
		txnmsg->SettlementDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->BusinessDate )
		txnmsg->BusinessDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->TraceNo )
		txnmsg->TraceNo = eztxnsequtil.genTraceNo();

	if( !strlen( txnmsg->RefNum ) )
	{
		memset( txnmsg->RefNum, 0, sizeof( txnmsg->RefNum ) );
		eztxnsequtil.genNumericRefNum( txnmsg->RefNum );
	}
}

void EzPOSDriver :: populateOldPOSRequest( struct EzTxnMsg *txnmsg, struct EzTxnMsg *oldtxnmsg )
{
	memset( txnmsg->DeviceType, 0, sizeof( txnmsg->DeviceType ) );
	strcpy( txnmsg->DeviceType, "POS" );

	memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
	strcpy( txnmsg->OrgChannel, GetSourceChannelName() );
	memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
	strcpy( txnmsg->OrgPort, GetLastSenderChannelName() );
	memset( txnmsg->SrcPort, 0, sizeof( txnmsg->SrcPort ) );
	strcpy( txnmsg->SrcPort, txnmsg->OrgPort );
	memset( txnmsg->SrcChannel, 0, sizeof( txnmsg->SrcChannel ) );
	strcpy( txnmsg->SrcChannel,txnmsg->OrgChannel );
}

void EzPOSDriver :: populateTxnReqMsg( struct EzTxnMsg *txnmsg )
{
	if( !txnmsg->TranDate )
		txnmsg->TranDate = ezdatetimeutil.getSysDate();
	if( !txnmsg->TranTime )
			txnmsg->TranTime = ezdatetimeutil.getSysTime();
	if( !txnmsg->LocalDate )
		txnmsg->LocalDate = ezdatetimeutil.getSysDate();
	if( !txnmsg->LocalTime )
		txnmsg->LocalTime = ezdatetimeutil.getSysTime();
	if( !txnmsg->CaptureDate )
		txnmsg->CaptureDate = ezdatetimeutil.getSysDate();
	if( !txnmsg->CaptureTime )
		txnmsg->CaptureTime = ezdatetimeutil.getSysTime();

	txnmsg->RespCode = EZLINK_RC_Approved;

	strcpy( txnmsg->SrcChannel, GetSourceChannelName() );
	strcpy( txnmsg->OrgChannel, GetSourceChannelName() );
	strcpy( txnmsg->OrgPort, GetLastSenderChannelName() );
	strcpy( txnmsg->DestPort, GetLastSenderChannelName() );
	strcpy( txnmsg->SrcPort, GetLastSenderChannelName() );
}

int EzPOSDriver :: writeToChannel( const char *ChannelName, struct EzTxnMsg *txnmsg )
{
	trace( DEBUG_NORMAL, "<SEND>Channel(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", ChannelName, txnmsg->DeviceType, txnmsg->OrgChannel, txnmsg->SrcChannel, txnmsg->OrgPort, txnmsg->SrcPort, txnmsg->DestPort, txnmsg->MsgType, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->TxnCode, txnmsg->Amount, txnmsg->TerminalId, txnmsg->TraceNo, txnmsg->TranDate, txnmsg->TranTime, txnmsg->LocalDate, txnmsg->LocalTime, txnmsg->RespCode, txnmsg->ReasonCode, txnmsg->RefNum, txnmsg->NetworkId );
	if( WriteChannel( ChannelName, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Writing Message to Channel[%s]", ChannelName );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Written Successfully Message to Channel[%s]", ChannelName );
		return 1;
	}
}

void EzPOSDriver :: writeToPOS( char *ChannelName, char *ResponseBuffer, int MsgSize )
{
	trace( "Writing Message of %d Bytes to POS Channel[%s]", MsgSize, ChannelName );
	if( WriteChannel( ChannelName, ResponseBuffer, MsgSize ) < 0 )
		trace( "Error in Writing Message to Channel[%s]", ChannelName );
}

void EzPOSDriver :: process800( struct EzTxnMsg txnmsg )
{
	char TermCommKey_LMK[ 65 ], TermCommKey_TMK[ 65 ];
	int MsgSize = 0;

	txnmsg.MsgType += 10;

	if( !isValidTerminal( &txnmsg ) )
	{
		trace( "TerminalId[%s] MerchantId[%s] in not valid...", txnmsg.TerminalId, txnmsg.AcceptorId );
		txnmsg.RespCode = EZLINK_RC_InvalidTerminalId;
		if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
			MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		}
		else
		{
			trace( "Unsupported POSType[%s]... ", getPOSProtocol() );
			return;
		}
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
		return;
	}

	memset( TermCommKey_LMK, 0, sizeof( TermCommKey_LMK ) );
	memset( TermCommKey_TMK, 0, sizeof( TermCommKey_TMK ) );
	if( GenTerminalCommKey( getInstId(), getPOSId(), getTermMasterKey(), strlen( getTermMasterKey() ), TermCommKey_LMK, TermCommKey_TMK ) < 0 )
	{
		trace( "Error in Generating TerminalCommKey for InstId[%s] POSId[%s] MasterKey[%s]", getInstId(), getPOSId(), getTermMasterKey() );

		txnmsg.RespCode = EZLINK_RC_InvalidTerminalId;
		if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
			MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		}
		else
		{
			trace( "Unsupported POSType[%s]... ", getPOSProtocol() );
			return;
		}
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
		return;
	}
	trace( "Generated TermCommKey_LMK[%s] TermCommKey_TMK[%s] for InstId[%s] POSId[%s] MasterKey[%s]", TermCommKey_LMK, TermCommKey_TMK, getInstId(), getPOSId(), getTermMasterKey() );

	if( updatePOSTermCommKey( getPOSId(), TermCommKey_LMK ) < 0 )
	{
		trace( "Updated TermCommKey[%s] for POSId[%s]", getPOSId(), TermCommKey_LMK );
		txnmsg.RespCode = EZLINK_RC_InvalidTerminalId;
	}
	else
	{
		trace( "Updated TermCommKey[%s] for POSId[%s]", TermCommKey_LMK, getPOSId() );
		txnmsg.RespCode = EZLINK_RC_Approved;
	}
	//Need to send message to POSDBMgr for updating the TermCommKey in Database

	memset( txnmsg.RsvFld4, 0, sizeof( txnmsg.RsvFld4 ) );
	strcpy( txnmsg.RsvFld4, TermCommKey_TMK );

	if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
	{
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
		MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
	}
	else
	{
		trace( "Unsupported POSType[%s]... ", getPOSProtocol() );
		return;
	}
	writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
	return;
}

void EzPOSDriver :: process500( struct EzTxnMsg txnmsg )
{
	char *endptr, TempStr[ 50 ], NewBatchId[ 13 ];
	int SaleCount, VoidCount, retval, MsgSize;
	double SaleAmount, VoidAmount, TableSaleAmount, TableVoidAmount, HostSaleAmount, HostVoidAmount;
	struct EzPOSTotal tot_rec;
	struct EzPOSBatchInfo posbatchinfo_rec;
	struct EzPOSBatchInfoHist posbatchinfohist_rec;
	char SaleAmtStr[ 20 ], TableSaleAmtStr[ 20 ], VoidAmtStr[ 20 ], TableVoidAmtStr[ 20 ];

	trace( "Processing 500 Message from POSId[%s]", getPOSId() );

	trace( "Decomposing Total[%s]", txnmsg.RsvFld2 );
	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, txnmsg.RsvFld2, 3 );
	SaleCount = atoi( TempStr );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, txnmsg.RsvFld2 + 3, 12 );
	SaleAmount = ( double ) atol( TempStr ) / 100;

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, txnmsg.RsvFld2 + 15, 3 );
	VoidCount = atoi( TempStr );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, txnmsg.RsvFld2 + 18, 12 );
	VoidAmount = ( double ) atol( TempStr ) / 100;

	memset( SaleAmtStr, 0, sizeof( SaleAmtStr ) );
	sprintf( SaleAmtStr, "%0.2lf", SaleAmount );
	memset( VoidAmtStr, 0, sizeof( VoidAmtStr ) );
	sprintf( VoidAmtStr, "%0.2lf", VoidAmount );

	trace( "Checking SaleCount[%d] SaleAmount[%s] VoidCount[%d] VoidAmount[%s] sent from POS[%s]...", SaleCount, SaleAmtStr, VoidCount, VoidAmtStr, getPOSId() );

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in connecting with switch database..." );
		txnmsg.RespCode = EZLINK_RC_UnableToProcess;
		txnmsg.MsgType += 10;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
		MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
		return;
	}

	memset( &tot_rec, 0, sizeof( struct EzPOSTotal ) );
	retval = getTotals( getPOSId(), getBatchId(), &tot_rec );
	if( retval != 0 )
	{
		trace( "Error in Getting Totals for POSId[%s]...SqlErr[%05d]", getPOSId(), retval );
		txnmsg.RespCode = EZLINK_RC_UnableToProcess;
		txnmsg.MsgType += 10;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
		MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
		return;
	}

	trace( "Read Totals with SaleCount[%d] SaleAmount[%s] VoidCount[%d] VoidAmount[%s] for POS[%s]", tot_rec.TermSaleCount, tot_rec.TermSaleAmount, tot_rec.TermVoidCount, tot_rec.TermVoidAmount, getPOSId() );

	HostSaleAmount = strtod( tot_rec.SaleAmount, &endptr );
	HostVoidAmount = strtod( tot_rec.VoidAmount, &endptr );
	TableSaleAmount = strtod( tot_rec.TermSaleAmount, &endptr );
	TableVoidAmount = strtod( tot_rec.TermVoidAmount, &endptr );

	trace( "SaleAmount[%lf] TableSaleAmount[%lf] VoidAmount[%lf] TableVoidAmount[%lf]", SaleAmount, TableSaleAmount, VoidAmount, TableVoidAmount );

	//if( SaleCount != tot_rec.TermSaleCount || VoidCount != tot_rec.TermVoidCount || strcmp( tot_rec.TermSaleAmount, SaleAmtStr ) || strcmp( tot_rec.TermVoidAmount, VoidAmtStr ) )
	if( SaleCount != tot_rec.TermSaleCount || VoidCount != tot_rec.TermVoidCount || SaleAmount != TableSaleAmount || VoidAmount != TableVoidAmount )
	{
		txnmsg.RespCode = 95;
		txnmsg.MsgType += 10;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
		MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
		return;
	}

	memset( NewBatchId, 0, sizeof( NewBatchId ) );
	eztxnsequtil.genPOSBatchId( NewBatchId );

	if( updatePOSBatchId( getPOSId(), NewBatchId ) < 0 )
		trace( "Error in Updating POSBatchId in Memory..." );

	retval = updatePOSBatchInTerminalInfo( getPOSId(), NewBatchId );

	if( retval != 0 )
		trace( "Error in Updating POSBatchId in TerminalInfo Table...OraErr[%05d]", retval );

	memset( &posbatchinfohist_rec, 0, sizeof( struct EzPOSBatchInfoHist ) );
	strcpy( posbatchinfohist_rec.BatchId, getBatchId() );
	memset( posbatchinfohist_rec.TermBatchId, 0, sizeof( posbatchinfohist_rec.TermBatchId ) );
	strcpy( posbatchinfohist_rec.TermBatchId, txnmsg.BatchId );
	memset( posbatchinfohist_rec.NewBatchId, 0, sizeof( posbatchinfohist_rec.NewBatchId ) );
	strcpy( posbatchinfohist_rec.NewBatchId, NewBatchId );
	memset( posbatchinfohist_rec.InstId, 0, sizeof( posbatchinfohist_rec.InstId ) );
	strcpy( posbatchinfohist_rec.InstId, getInstId() );
	memset( posbatchinfohist_rec.POSId, 0, sizeof( posbatchinfohist_rec.POSId ) );
	strcpy( posbatchinfohist_rec.POSId, getPOSId() );
	memset( posbatchinfohist_rec.Termid, 0, sizeof( posbatchinfohist_rec.Termid ) );
	strcpy( posbatchinfohist_rec.Termid, getTerminalId() );
	memset( posbatchinfohist_rec.MerchantId, 0, sizeof( posbatchinfohist_rec.MerchantId ) );
	strcpy( posbatchinfohist_rec.MerchantId, getMerchantId() );
	memset( posbatchinfohist_rec.CloseDate, 0, sizeof( posbatchinfohist_rec.CloseDate ) );
	sprintf( posbatchinfohist_rec.CloseDate, "%06d", ezdatetimeutil.getSysDate() );
	posbatchinfohist_rec.CloseTime = ezdatetimeutil.getSysTime();
	posbatchinfohist_rec.Source = POS_SOURCE_TERMINAL;
	if( tot_rec.SaleCount == tot_rec.TermSaleCount && tot_rec.VoidCount == tot_rec.TermVoidCount && TableSaleAmount == HostSaleAmount && TableVoidAmount == HostVoidAmount )
		posbatchinfohist_rec.MatchFlag = POS_TOTALS_MATCHED;
	else
		posbatchinfohist_rec.MatchFlag = POS_TOTALS_MISMATCHED;

	posbatchinfohist_rec.HostSaleCount =  tot_rec.SaleCount;
	posbatchinfohist_rec.TermSaleCount = tot_rec.TermSaleCount;
	memset( posbatchinfohist_rec.HostSaleAmount, 0, sizeof( posbatchinfohist_rec.HostSaleAmount ) );
	strcpy( posbatchinfohist_rec.HostSaleAmount, tot_rec.SaleAmount );
	memset( posbatchinfohist_rec.TermSaleAmount, 0, sizeof( posbatchinfohist_rec.TermSaleAmount ) );
	strcpy( posbatchinfohist_rec.TermSaleAmount, tot_rec.TermSaleAmount );
	posbatchinfohist_rec.HostVoidCount =  tot_rec.VoidCount;
	posbatchinfohist_rec.TermVoidCount = tot_rec.TermVoidCount;
	memset( posbatchinfohist_rec.HostVoidAmount, 0, sizeof( posbatchinfohist_rec.HostVoidAmount ) );
	strcpy( posbatchinfohist_rec.HostVoidAmount, tot_rec.VoidAmount );
	memset( posbatchinfohist_rec.TermVoidAmount, 0, sizeof( posbatchinfohist_rec.TermVoidAmount ) );
	strcpy( posbatchinfohist_rec.TermVoidAmount, tot_rec.TermVoidAmount );

	posbatchinfohist_rec.HostAuthCount =  tot_rec.AuthCount;
	posbatchinfohist_rec.TermAuthCount = tot_rec.TermAuthCount;
	memset( posbatchinfohist_rec.HostAuthAmount, 0, sizeof( posbatchinfohist_rec.HostAuthAmount ) );
	strcpy( posbatchinfohist_rec.HostAuthAmount, "0.00" );
	memset( posbatchinfohist_rec.TermAuthAmount, 0, sizeof( posbatchinfohist_rec.TermAuthAmount ) );
	strcpy( posbatchinfohist_rec.TermAuthAmount, "0.00" );


	retval = insertPOSBatchHist( &posbatchinfohist_rec );

	if( retval != 0 )
		trace( "Error in Inserting in POSBatchHist Table..OraErr[%05d]", retval );

	retval = clearPOSBatchInfo( getPOSId(), NewBatchId, posbatchinfohist_rec.CloseDate, posbatchinfohist_rec.CloseTime );

	if( retval != 0 )
		trace( "Error in Clearing POSBatchInfo Table..OraErr[%05d]", retval );

	retval = moveFromPOSBatchTxnInfoToHist( getPOSId(), getBatchId() );
	if( retval != 0 )
		trace( "Error in Moving from POSBatchTxnInfo to Hist Table..OraErr[%05d]", retval );

	retval = deleteFromPOSBatchTxnInfo( getPOSId(), getBatchId() );

	if( retval != 0 )
		trace( "Error in Deleting POSBatchTxnInfo Table..OraErr[%05d]", retval );

	if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
	{
		txnmsg.MsgType += 10;
		txnmsg.RespCode = EZLINK_RC_Approved;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
		MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
	}
	else
	{
		trace( "Unsupported POSType[%s]... ", getPOSProtocol() );
		return;
	}
}

void EzPOSDriver :: process320( struct EzTxnMsg txnmsg )
{
	struct EzTxnMsg oldtxnmsg;
	char *endptr, POSTxnRefNum[ POS_TXNREFNUM_SIZE + 1 ], AmountStr[ 20 ];
	int retval, MsgSize;
	double Amount, TableAmount;

	trace( "Processing 320 message for POSId[%s]", getPOSId() );
	memset( POSTxnRefNum, 0, sizeof( POSTxnRefNum ) );
	getPOSTxnRefNum( &txnmsg, POSTxnRefNum );
	trace( "Got LookUp POSTxnRefNum[%s]", POSTxnRefNum );

	dbutil.DBConnect();

	memset( &oldtxnmsg, 0, sizeof( struct EzTxnMsg ) );
	retval = searchPOSTxn( POSTxnRefNum, &oldtxnmsg );
	if( retval == 1403 )
	{
		trace( "Transaction with POSTxnRefNum[%s] BatchId[%s] POSId[%s] not found in POSBatchTxnInfo Table...",  POSTxnRefNum, txnmsg.BatchId, getPOSId() );
		retval = insertPosBatchTxnInfo( getPOSId(), &txnmsg, POSTxnRefNum, POS_TXN_MISMATCH, POS_TXN_REASON_NOT_FOUND );
		if( retval != 0 )
			trace( "Error in inserting PosBatchTxnInfo OraErr[%05d]", retval );
		dbutil.DBClose();
	}
	else
	{
		if( retval == 0 )
		{
			Amount = ( double ) atol( txnmsg.Amount ) / 100;
			TableAmount = strtod( oldtxnmsg.Amount, &endptr );
			memset( AmountStr, 0, sizeof( AmountStr ) );
			sprintf( AmountStr, "%0.2lf", Amount );
			if( Amount != TableAmount )
			{
				trace( "Transaction with POSTxnRefNum[%s] BatchId[%s] POSId[%s] has a Amount MisMatch TerminalAmount != HostAmount[%s] in POSBatchTxnInfo Table...",  POSTxnRefNum, txnmsg.BatchId, getPOSId(), txnmsg.Amount, oldtxnmsg.Amount );
				retval = updatePosBatchTxnInfo( getPOSId(), POSTxnRefNum, AmountStr, POS_TXN_MISMATCH, POS_TXN_REASON_AMOUNT_MISMATCH );
				if( retval != 0 )
					trace( "Error in Updating PosBatchTxnInfo OraErr[%05d]", retval );
			}
		}
		else
		{

		}
		dbutil.DBClose();
	}

	if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
	{
		txnmsg.MsgType += 10;
		txnmsg.RespCode = EZLINK_RC_Approved;
		memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
		memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
		MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
		writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
	}
	else
	{
		trace( "Unsupported POSType[%s]... ", getPOSProtocol() );
		return;
	}
}

int EzPOSDriver :: logPOSTxnInfo( const char *POSId, unsigned char LogFlag, const char *POSTxnRefNum, struct EzTxnMsg localtxnmsg )
{
	struct EzPOSDBMgrMsg posdbmgrmsg;

	memset( &posdbmgrmsg, 0, sizeof( struct EzPOSDBMgrMsg ) );
	strcpy( posdbmgrmsg.POSId, POSId );
	posdbmgrmsg.LogFlag = LogFlag;
	strcpy( posdbmgrmsg.POSTxnRefNum, POSTxnRefNum );
	memcpy( &posdbmgrmsg.txnmsg, &localtxnmsg, sizeof( struct EzTxnMsg ) );
	posdbmgrmsg.NotificationId = getpid();

	trace( "Writing loginfo to POSDBMgr with POSId[%s] LogFlag[%x] POSTxnRefNum[%s] NotificationId[%d]", posdbmgrmsg.POSId, posdbmgrmsg.LogFlag, posdbmgrmsg.POSTxnRefNum, posdbmgrmsg.NotificationId );

	if( WriteChannel( POSDBMGRCHANNEL, ( char * ) &posdbmgrmsg, sizeof( struct EzPOSDBMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Message to Channel[%s]", POSDBMGRCHANNEL );
		return -1;
	}
	else
	{
		trace( "Written Message Successfully to Channel[%s]", POSDBMGRCHANNEL );
		return 1;
	}
}

void EzPOSDriver :: serviceRequest()
{
	int MsgSize, NRoutes, retval, tempTxnCode;
	char RequestBuffer[ 5097 ], RouteSelectId[ 17 ], RouteSelectList[ 129 ], ChannelName[ 33 ];
	char POSTxnRefNum[ POS_TXNREFNUM_SIZE + 1 ], OldPOSTxnRefNum[ POS_TXNREFNUM_SIZE + 1 ];
	struct EzTxnMsg txnmsg, localtxnmsg, oldtxnmsg;
	struct EzPOSTxnMemory postxnmemory_rec;
	struct EzPOSRouteSelect posrouteselect_rec;
	bool DEVICEFLAG = false;
	unsigned char LogFlag;

	while( 1 )
	{
		trace( "POSDriver Waiting for Request to be Serviced" );
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		if( ReadMessage( RequestBuffer, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}

		trace( "Message of size[ %d ] Received from Channel[ %s ]", MsgSize, GetLastSenderChannelName() );

		if( readPOSChannelProperty( GetLastSenderChannelName() ) < 0 )
		{
			trace( "Error in Reading ChannelName[%s] from POSChannelProperty", GetLastSenderChannelName() );
			continue;
		}

		if( isPOSPortChannel() )
		{
			trace( "Got Message from POS Port Channel[%s]", GetLastSenderChannelName() );

			if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
			{
				memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
				hypercomutilobj.decomposePOSMsg( RequestBuffer + 12, &txnmsg );
				memset( txnmsg.m_chn, 0, sizeof( txnmsg.m_chn ) );
				ezpadssutil.maskString( txnmsg.chn, 6, strlen( txnmsg.chn ) - 4, '*', txnmsg.m_chn );
			}
			else
			{
				trace( "Unsupported POSType[%s]... ", getPOSProtocol() );
				continue;
			}

			if( !isValidTerminal( &txnmsg ) )
			{
				trace( "TerminalId[%s] MerchantId[%s] in not valid...", txnmsg.TerminalId, txnmsg.AcceptorId );
				txnmsg.MsgType += 10;
				txnmsg.RespCode = EZLINK_RC_InvalidTerminalId;
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
				MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
				writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
				continue;
			}

			memset( txnmsg.RsvFld6, 0, sizeof( txnmsg.RsvFld6 ) );
			strncpy( txnmsg.RsvFld6, RequestBuffer, 12 );

			tempTxnCode = txnmsg.TxnCode;
			txnmsg.TxnCode = hypercomutilobj.getSwitchTxnCode( txnmsg.TxnCode );

			trace( "POS TxnCode[%d] Mapped to TxnCode[%d]", tempTxnCode, txnmsg.TxnCode );

			if( txnmsg.MsgType == EZLINK_TXN_NtwkRequest )
			{
				trace( "calling process800" );
				process800( txnmsg );
				continue;
			}

			if( txnmsg.MsgType == EZLINK_TXN_SettlementRequest )
			{
				trace( "calling process500" );
				process500( txnmsg );
				continue;
			}

			if( txnmsg.MsgType == EZLINK_TXN_BatchUploadRequest )
			{
				trace( "calling process320" );
				process320( txnmsg );
				continue;
			}

			if( readPOSInBoundProperty( txnmsg.MsgType, txnmsg.TxnCode ) < 0 )
			{
				trace( "Error in reading MsgType[%d] TxnCode[%d] in POSInBoundProperty...", txnmsg.MsgType, txnmsg.TxnCode );
				txnmsg.MsgType += 10;
				txnmsg.RespCode = EZLINK_RC_UnableToProcess;
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
				MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
				writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
				continue;
			}

			if( isNewPOSRequest() )
			{
				trace( "Got New Request[%d] TxnCode[%d] from POS[%s]", txnmsg.MsgType, txnmsg.TxnCode, getPOSId() );
				populateNewPOSRequest( &txnmsg );
			}
			else if( isOldPOSRequest() )
			{
				trace( "Got Old Request[%d] TxnCode[%d] from POS[%s]", txnmsg.MsgType, txnmsg.TxnCode, getPOSId() );
				int RelTxnCode;
				char TxnCodeStr1[ 7 ], TxnCodeStr2[ 7 ];

				RelTxnCode = getRelatedTxnCode( getTerminalType(), txnmsg.MsgType, txnmsg.TxnCode );

				if( RelTxnCode < 0 )
				{
					trace( "Error in Searching Relation TxnCode for TerminalType[%s] MsgType[%d] TxnCode[%d]", getTerminalType(), txnmsg.MsgType, txnmsg.TxnCode );
					txnmsg.MsgType += 10;
					txnmsg.RespCode = EZLINK_RC_UnableToProcess;
					memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
					memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
					MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
					writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
					continue;
				}
				memset( TxnCodeStr1, 0, sizeof( TxnCodeStr1 ) );
				sprintf( TxnCodeStr1, "%02d", RelTxnCode );
				memset( TxnCodeStr2, 0, sizeof( TxnCodeStr2 ) );
				sprintf( TxnCodeStr2, "%06d", txnmsg.TxnCode );
				strncpy( TxnCodeStr1 + 2, TxnCodeStr2 + 2, 4 );
				tempTxnCode = txnmsg.TxnCode;
				txnmsg.TxnCode = atoi( TxnCodeStr1 );
				trace( "Got Relation as TxnCode[%d]", txnmsg.TxnCode );

				memset( OldPOSTxnRefNum, 0, sizeof( OldPOSTxnRefNum ) );
				getPOSTxnRefNum( &txnmsg, OldPOSTxnRefNum );

				trace( "Generated LookUp POSTxnRefNum as [%s]", OldPOSTxnRefNum );

				txnmsg.TxnCode = atoi( TxnCodeStr2 );

				memset( &postxnmemory_rec, 0, sizeof( struct EzPOSTxnMemory ) );
				if( readPOSTxnMemory( getPOSId(), OldPOSTxnRefNum, &postxnmemory_rec ) < 0 )
				{
					trace( "Error in Locating LookUp POSTxnRefNum[%s] from Memory...Try it Database", OldPOSTxnRefNum );

					if( dbutil.DBConnect() < 0 )
					{
						trace( "Error in connecting with switch database..." );
						txnmsg.MsgType += 10;
						txnmsg.RespCode = EZLINK_RC_UnableToProcess;
						memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
						memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
						MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
						writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
						continue;
					}

					memset( &oldtxnmsg, 0, sizeof( EzTxnMsg ) );
					retval = searchPOSTxn( OldPOSTxnRefNum, &oldtxnmsg );
					dbutil.DBClose();

					if( retval != 0 )
					{
						trace( "Error in Searching POSTxnRefNum[%s] from EzPOSBatchInfo...SqlErr[%05d]", OldPOSTxnRefNum, retval );
						txnmsg.MsgType += 10;
						txnmsg.RespCode = EZLINK_RC_UnableToProcess;
						memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
						memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
						MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
						writeToPOS( GetLastSenderChannelName(), ResponseBuffer , MsgSize + 12 );
						continue;
					}
					populateOldPOSRequest( &txnmsg, &oldtxnmsg );
				}
				else
					populateOldPOSRequest( &txnmsg, &oldtxnmsg );
			}
			else if ( isPOSReversalRequest() )
			{

			}
		}
		else
		{
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &txnmsg, RequestBuffer, sizeof( struct EzTxnMsg ) );
		}

		trace( "InVoiceNo[%s] TxnAmount[%s]", txnmsg.AuthNum, txnmsg.Amount );
		if( isInBoundLogReq() )
		{

		}

		if( isPOSLeaveMsg() )
		{
			trace( "Leaving MsgType[%d] TxnCode[%d]....", txnmsg.MsgType, txnmsg.TxnCode );
			continue;
		}

		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
		if( getPOSRouteSelectList( &txnmsg, RouteSelectList ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in getting RouteSelect List..Dropping Message" );
			if( isNewPOSRequest() )
			{
				if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
				{
					txnmsg.RespCode = EZLINK_RC_UnableToProcess;
					memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
					memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
					MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
					writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
				}
			}
			continue;
		}


		memset( &postxnmemory_rec, 0, sizeof( struct EzPOSTxnMemory ) );
		strcpy( postxnmemory_rec.POSId, getPOSId() );
		memset( postxnmemory_rec.TxnRefNum, 0, sizeof( postxnmemory_rec.TxnRefNum ) );
		getPOSTxnRefNum( &txnmsg, postxnmemory_rec.TxnRefNum );
		postxnmemory_rec.TxnStatus = POS_TXN_STATUS_WAITFORRESP;
		memcpy( &postxnmemory_rec.txnmsg, &txnmsg, sizeof( struct EzTxnMsg ) );

		if( updatePOSTxnMemory( getPOSId(), postxnmemory_rec ) < 0 )
		{
			trace( "Error in Updating POSTxnMemory for POS[%s]", getPOSId() );
			if( !strcasecmp( getPOSProtocol(), POS_TYPE_HYPERCOM ) )
			{
				txnmsg.RespCode = EZLINK_RC_UnableToProcess;
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
				MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
				writeToPOS( GetLastSenderChannelName(), ResponseBuffer, MsgSize + 12 );
			}
		}
		else
			trace( "Updated POSTxnMemory for POS[%s] with TxnRefNum...[%s]", getPOSId(), postxnmemory_rec.TxnRefNum );

		NRoutes = tkutil.getNToken( RouteSelectList, ',' );

		for( int i = 0; i < NRoutes; i++ )
		{
			memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
			tkutil.getTokenExSpaces( RouteSelectList, RouteSelectId, ',', i + 1 );

			memset( &posrouteselect_rec, 0, sizeof( struct EzPOSRouteSelect ) );
			if( readPOSRouteSelect( RouteSelectId, &posrouteselect_rec ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading RouteSelectId[%s] From POSRouteSelect...", RouteSelectId );
				continue;
			}

			trace( DEBUG_NORMAL, "Read ChannelName[%s] MsgTranslateId[%s] from POSRouteSelect for RouteSelectId[%s]",  posrouteselect_rec.ChannelName, posrouteselect_rec.MsgTranslateId, RouteSelectId );

			memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &localtxnmsg, &txnmsg, sizeof( struct EzTxnMsg ) );

			if( strcmp( posrouteselect_rec.MsgTranslateId, "*" ) )
			{
				if( translateMsg( posrouteselect_rec.MsgTranslateId, &localtxnmsg ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Reading MsgTranslateId[%s] from EzPOSMsgTranslate Table", posrouteselect_rec.MsgTranslateId );
					continue;
				}
			}

			LogFlag = 0x0;

			if( posrouteselect_rec.LogTxnReq == 'Y' || posrouteselect_rec.LogTxnReq == 'y' )
				LogFlag = LogFlag | 0x1;


			if( ( posrouteselect_rec.LogBatchReq == 'Y' || posrouteselect_rec.LogBatchReq == 'y' ) && ( localtxnmsg.MsgType == 210 && localtxnmsg.RespCode == EZLINK_RC_Approved ) )
				LogFlag = LogFlag | 0x2;

			if( posrouteselect_rec.LogTotReq == 'Y' || posrouteselect_rec.LogTotReq == 'y' )
				LogFlag = LogFlag | 0x4;

			memset( POSTxnRefNum, 0, sizeof( POSTxnRefNum ) );
			getPOSTxnRefNum( &localtxnmsg, POSTxnRefNum );

			trace( "POSTxnRefNum[%s]..test ", POSTxnRefNum );
			if( logPOSTxnInfo( getPOSId(), LogFlag, POSTxnRefNum, localtxnmsg ) < 0 )
				trace( "Error in sending logging message EzPOSDBMgr Channel..." );

			if( !strcmp( posrouteselect_rec.ChannelName, EZIMF_DESTPORT ) )
			{
				DEVICEFLAG = true;
				if( ( !strlen( localtxnmsg.DestPort ) ) || ( !strcmp( localtxnmsg.DestPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "DestPort is NULL..Cannot Route Message to DestPort");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtxnmsg.DestPort );
			}
			if( !strcmp( posrouteselect_rec.ChannelName, EZIMF_ORGPORT ) )
			{
				DEVICEFLAG = true;
				if( ( !strlen( localtxnmsg.OrgPort ) ) || ( !strcmp( localtxnmsg.OrgPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "OrgPort is NULL..Cannot Route Message to OrgPort");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtxnmsg.OrgPort );
			}
			else
			{
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, posrouteselect_rec.ChannelName );
				DEVICEFLAG = false;
			}

			if( strcmp( ChannelName, "*" ) && strcmp( ChannelName, GetSourceChannelName() ) )
			{
				if( DEVICEFLAG )
				{
					memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
					memcpy( ResponseBuffer, txnmsg.RsvFld6, 12 );
					MsgSize = hypercomutilobj.composePOSMsg( &txnmsg, ResponseBuffer + 12 );
					writeToPOS( ChannelName, ResponseBuffer, MsgSize + 12 );
				}
				else
					writeToChannel( ChannelName,  &txnmsg );
			}
		}
	}
}


int main( int argc, char **argv )
{
	EzPOSDriver ezposdriverobj;
	ezposdriverobj.initPOSDriver( argv[ 0 ] );
	ezposdriverobj.serviceRequest();
	return 1;
}
