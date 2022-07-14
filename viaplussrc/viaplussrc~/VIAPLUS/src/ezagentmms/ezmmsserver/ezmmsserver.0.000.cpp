#include <ezmms/ezmmsserver.h>

int EzMMSServer :: init( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmmsserver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzMMSServer", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzMMSServer....." );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initMMSUtil( this ) < 0 )
	{
		trace( "Error in Initializing MMSUtil..." );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezmms.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMS#MAXACCOUNTS", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching MMS#MAXACCOUNTS from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	MAX_ACCTS = atoi( cfgval );

	cfgutil.cfg_close();

	acctlist = ( struct EzMMSAccountProfile * ) malloc( sizeof( struct EzMMSAccountProfile ) * MAX_ACCTS );

	if( acctlist == NULL )
	{
		trace( "Error in Allocating Memory for AccountList...Malloc Error" );
		trace( "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this, "EZMMS" ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing DBUtil.... " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with database " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}


	if( ezinstprofileutil.initInstProfile( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzInstProfileUtil" );
		trace( DEBUG_CRITICAL,"^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	initMMSServerUtil( this, MAX_ACCTS, &ezinstprofileutil, &dbutil, &ezpadssutil );

	if( secutil.InitEzSecurityUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzSecurityUtil" );
		trace( DEBUG_CRITICAL,"^^^^^^^^^^^EzMMSServer Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void EzMMSServer :: sendResponse( struct EzTxnMsg *txnmsg )
{
	trace( "Sending Response MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d] to Channel[%s]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->IssuerInst, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->Amount, txnmsg->RespCode, GetLastSenderChannelName() );
	if( WriteLastSenderChannel( ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Response to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Response to Channel[%s]", GetLastSenderChannelName() );
}

void EzMMSServer :: processReadMerchantProfile( struct EzTxnMsg *txnmsg )
{
	if( !READ_MERCHANT_PROFILE_FLAG )
	{
		trace( "READING MERCHANTPROFILE FOR INSTID<%s> MERCHANTID<%s>", txnmsg->ProcessInst, txnmsg->AcceptorId  );
		memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
		if( readMerchantProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, &merchantprofile_rec ) < 0 )
		{
			trace( "ERROR READING INSTID<%s> MERCHANTID<%s> FROM MERCHANTPROFILE MEMORY...LOOKING INTO TABLE", txnmsg->ProcessInst, txnmsg->AcceptorId );
			memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
			if( readMerchantProfileTable( txnmsg, &merchantprofile_rec ) < 0 )
				return;
			if( addMerchantProfile( merchantprofile_rec ) < 0 )
			{
				txnmsg->RespCode = EZLINK_RC_UnableToProcess;
				return;
			}
		}
		READ_MERCHANT_PROFILE_FLAG = true;
	}
}

void EzMMSServer :: processReadStoreProfile( struct EzTxnMsg *txnmsg )
{
	if( !READ_STORE_PROFILE_FLAG )
	{
		trace( "READING STORE PROFILE FOR INSTID<%s> MERCHANTID<%s> STOREID<%s>", txnmsg->ProcessInst, txnmsg->AcceptorId, terminalprofile_rec.StoreId  );
		memset( &storeprofile_rec, 0, sizeof( struct EzMMSStoreProfile ) );
		if( readStoreProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, terminalprofile_rec.StoreId, &storeprofile_rec ) < 0 )
		{
			trace( "ERROR STORE PROFILE FOR INSTID<%s> MERCHANTID<%s> STOREID<%s> FROM STOREPROFILE MEMORY...LOOKING INTO TABLE", txnmsg->ProcessInst, txnmsg->AcceptorId, terminalprofile_rec.StoreId );
			memset( &storeprofile_rec, 0, sizeof( struct EzMMSStoreProfile ) );
			if( readStoreProfileTable( txnmsg, &storeprofile_rec ) < 0 )
				return;
			if( addStoreProfile( storeprofile_rec ) < 0 )
			{
				txnmsg->RespCode = EZLINK_RC_UnableToProcess;
				return;
			}
		}
		READ_STORE_PROFILE_FLAG = true;
	}
}

void EzMMSServer :: processReadTerminalProfile( struct EzTxnMsg *txnmsg )
{
	if( !READ_TERMINAL_PROFILE_FLAG )
	{
		trace( "READING TERMINAL PROFILE FOR INSTID<%s> MERCHANTID<%s> TERMINALID<%s>", txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId  );
		memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
		if( readTerminalProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId, &terminalprofile_rec ) < 0 )
		{
			trace( "ERROR TERMINAL PROFILE FOR INSTID<%s> MERCHANTID<%s> TERMINALID<%s> FROM TERMINALPROFILE MEMORY...LOOKING INTO TABLE", txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId );
			memset( &terminalprofile_rec, 0, sizeof( struct EzMMSTerminalProfile ) );
			if( readTerminalProfileTable( txnmsg, &terminalprofile_rec ) < 0 )
				return;
			if( addTerminalProfile( terminalprofile_rec ) < 0 )
			{
				txnmsg->RespCode = EZLINK_RC_UnableToProcess;
				return;
			}
		}
		READ_TERMINAL_PROFILE_FLAG = true;
		memset( txnmsg->StoreId, 0, sizeof( txnmsg->StoreId ) );
		strcpy( txnmsg->StoreId, terminalprofile_rec.StoreId );
	}
}

int EzMMSServer :: LoadAccounts( struct EzTxnMsg *txnmsg )
{
	int NAccounts = 0;
	struct EzMMSMerchantRelation merchantrelation_rec;
	struct EzMMSAccountProfile acctprofile_rec;

	memset( acctlist, 0, sizeof( struct EzMMSAccountProfile ) * MAX_ACCTS );

	NAccounts = readMerchantRelation( txnmsg->ProcessInst, txnmsg->AcceptorId, acctlist );

	if( !NAccounts )
	{
		trace( "NO ACCOUNTS LINKED TO INSTID<%s> MERCHANTID<%s>..LOOKING INTO THE TABLE", txnmsg->ProcessInst, txnmsg->AcceptorId );
		NAccounts = readMerchantRelationTable( txnmsg, acctlist );
		if( !NAccounts )
		{
			trace( "NO ACCOUNTS LINKED TO INSTID<%s> MERCHANTID<%s>", txnmsg->ProcessInst, txnmsg->AcceptorId );
			txnmsg->RespCode = EZLINK_RC_InvalidAccount;
			return -1;
		}

		for( int i = 0; i < NAccounts; i++ )
		{
			memset( &merchantrelation_rec, 0, sizeof( struct EzMMSMerchantRelation ) );
			strcpy( merchantrelation_rec.InstId, txnmsg->ProcessInst );
			strcpy( merchantrelation_rec.MerchantId, txnmsg->AcceptorId );
			strcpy( merchantrelation_rec.AccountNo, acctlist[ i ].AccountNo );
			strcpy( merchantrelation_rec.CurrCode, acctlist[ i ].CurrCode );
			merchantrelation_rec.AccountStatus = acctlist[ i ].AccountStatus;
			merchantrelation_rec.AccountPriority = acctlist[ i ].AccountPriority;
			addMerchantRelation( merchantrelation_rec );
		}
	}

	for( int i = 0; i < NAccounts; i++ )
	{
		if( acctlist[ i ].AccountStatus != '1' )
		{
			trace( "ACCOUNT[%s] IS INACTIVE", acctlist[ i ].AccountNo );
			if( i == NAccounts - 1 )
			{
				NAccounts--;
				break;
			}
			memcpy( acctlist + i, acctlist + i + 1, sizeof( struct EzMMSAccountProfile ) * ( NAccounts - i - 1 ) );
			NAccounts--;
		}
	}

	if( !NAccounts )
	{
		trace( "NO ACCOUNTS LINKED TO INSTID<%s> MERCHANTID<%s>", txnmsg->ProcessInst, txnmsg->AcceptorId );
		txnmsg->RespCode = EZLINK_RC_InvalidAccount;
		return -1;
	}

	for( int i = 0; i < NAccounts; i++ )
	{
		if( readAccountInfo( txnmsg, acctlist[ i ].AccountNo,  acctlist + i ) < 0 )
			return -1;
	}
	trace( "NAccounts[%d] with Original Order as below....", NAccounts );

	if( NAccounts == 2 )
	{
		if( atoi( acctlist[ 1 ].CurrCode ) == txnmsg->AcqCurrencyCode )
		{
			memset( &acctprofile_rec, 0, sizeof( struct EzMMSAccountProfile ) );
			memcpy( &acctprofile_rec, &acctlist[ 0 ], sizeof( struct EzMMSAccountProfile ) );
			memset( &acctlist[ 0 ], 0, sizeof( struct EzMMSAccountProfile ) );
			memcpy( &acctlist[ 0 ], &acctlist[ 1 ], sizeof( struct EzMMSAccountProfile ) );
			memset( &acctlist[ 1 ], 0, sizeof( struct EzMMSAccountProfile ) );
			memcpy( &acctlist[ 1 ], &acctprofile_rec, sizeof( struct EzMMSAccountProfile ) );
		}
	}
	if( NAccounts > 2 )
	{
		for( int i = 0; i < NAccounts; i++ )
		{
			if( atoi( acctlist[ i ].CurrCode ) == txnmsg->AcqCurrencyCode )
				acctlist[ i ].AccountPriority = -1;
		}
		int min, minpos;
		for( int i = 0; i < NAccounts - 1; i++ )
		{
			min = ( acctlist + i )->AccountPriority;
			minpos = i;
			for( int j = i + 1; j < NAccounts; j++ )
			{
				if( ( acctlist + j )->AccountPriority < min )
				{
					min = ( acctlist + j )->AccountPriority;
					minpos = j;
				}
			}
			memset( &acctprofile_rec, 0, sizeof( struct EzMMSAccountProfile ) );
			memcpy( &acctprofile_rec, acctlist + minpos, sizeof( struct EzMMSAccountProfile ) );
			memset( acctlist + minpos, 0, sizeof( struct EzMMSAccountProfile ) );
			memcpy( acctlist + minpos, acctlist + i, sizeof( struct EzMMSAccountProfile ) );
			memset( acctlist + i, 0, sizeof( struct EzMMSAccountProfile ) );
			memcpy( acctlist + i, &acctprofile_rec, sizeof( struct EzMMSAccountProfile ) );
		}
	}
	trace( "%d ACCOUNTS LOADED WITH ORDER AS BELOW......", NAccounts );
	for( int i = 0; i < NAccounts; i++ )
		trace( "AccountNo[%s]--CurrencyCode[%s]--AccountPriority[%d]--AvailBalance[%s]--LedgerBalance[%s]", acctlist[ i ].AccountNo, acctlist[ i ].CurrCode, acctlist[ i ].AccountPriority, acctlist[ i ].AvailableBalance, acctlist[ i ].LedgerBalance );

	memset( txninfo_rec.AccountNo, 0, sizeof( txninfo_rec.AccountNo ) );
	strcpy( txninfo_rec.AccountNo, acctlist[ 0 ].AccountNo );
	return NAccounts;
}

int EzMMSServer :: getFeeAmount( struct EzTxnMsg *txnmsg, const char *FeeCode, char *FeeAmount )
{
	char TempAmount1[ 21 ], TempAmount2[ 21 ];
	struct EzMMSFeeInfo feeinfo_rec;
	struct EzMMSCurrencyRate curr_rate_rec1, curr_rate_rec2;
	memset( &feeinfo_rec, 0, sizeof( struct EzMMSFeeInfo ) );
	if( readFeeInfo( txnmsg->ProcessInst, FeeCode, &feeinfo_rec ) < 0 )
	{
		trace( "ERROR IN READING INSTID[%s] FEECODE[%s] FROM FEEINFO MEMORY..LOOKING INTO THE TABLE", txnmsg->ProcessInst, FeeCode );
		memset( &feeinfo_rec, 0, sizeof( struct EzMMSFeeInfo ) );
		if( readFeeInfoTable( txnmsg, FeeCode, &feeinfo_rec ) < 0 )
			return -1;
		if( addFeeInfo( feeinfo_rec ) < 0 )
		{
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			return -1;
		}
	}
	trace( "READ INSTID[%s] FEECODE[%s] WITH FEEMODE[%c] FEEAMT[%s] CURRCODE[%s]", feeinfo_rec.InstId, feeinfo_rec.FeeCode, feeinfo_rec.FeeMode, feeinfo_rec.FeeAmt, feeinfo_rec.CurrCode );

	if( feeinfo_rec.FeeMode == FEE_MODE_PERCENTAGE )
	{
		trace( "PERCENTAGE FEE..." );
		memset( TempAmount1, 0, sizeof( TempAmount1 ) );
		amtutil.divideAmount( txnmsg->Amount, "100", TempAmount1 );
		memset( TempAmount2, 0, sizeof( TempAmount2 ) );
		amtutil.multiplyAmount( feeinfo_rec.FeeAmt, TempAmount1, TempAmount2 );
	}
	else
	{
		trace( "FLAT FEE..." );
		trace( "AcqCurrencyCode[%d] feeinfo_rec.CurrCode[%s]", txnmsg->AcqCurrencyCode, feeinfo_rec.CurrCode );
		if( txnmsg->AcqCurrencyCode != atoi( feeinfo_rec.CurrCode ) )
		{
			if( atoi( feeinfo_rec.CurrCode ) == atoi( ezinstprofileutil.getInstCurrencyCode() ) )
			{
				memset( &curr_rate_rec1, 0, sizeof( struct EzMMSCurrencyRate ) );
				if( getCurrencyRate( txnmsg, txnmsg->AcqCurrencyCode, &curr_rate_rec1 ) < 0 )
					return -1;
				if( curr_rate_rec1.CurrencyMode == CURRENCY_MODE_MULTIPLY )
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.multiplyAmount( feeinfo_rec.FeeAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				else
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.divideAmount( feeinfo_rec.FeeAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				trace( "TempAmount2----1[%s]", TempAmount2 );
			}
			else
			{
				memset( &curr_rate_rec1, 0, sizeof( struct EzMMSCurrencyRate ) );
				if( getCurrencyRate( txnmsg, atoi( feeinfo_rec.CurrCode ), &curr_rate_rec1 ) < 0 )
					return -1;
				if( curr_rate_rec1.CurrencyMode == CURRENCY_MODE_MULTIPLY )
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.multiplyAmount( feeinfo_rec.FeeAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				else
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.divideAmount( feeinfo_rec.FeeAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				trace( "TempAmount2----2[%s]", TempAmount2 );
				memset( &curr_rate_rec2, 0, sizeof( struct EzMMSCurrencyRate ) );
				if( getCurrencyRate( txnmsg, txnmsg->AcqCurrencyCode, &curr_rate_rec2 ) < 0 )
					return -1;
				if( curr_rate_rec2.CurrencyMode == CURRENCY_MODE_MULTIPLY )
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.multiplyAmount( TempAmount2, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				else
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.divideAmount( TempAmount2, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				trace( "TempAmount2----3[%s]", TempAmount2 );
			}
		}
		else
		{
			memset( TempAmount2, 0, sizeof( TempAmount2 ) );
			strcpy( TempAmount2, feeinfo_rec.FeeAmt );
		}
	}

	strcpy( FeeAmount, TempAmount2 );
	return 1;
}

int EzMMSServer :: getCommissionAmount( struct EzTxnMsg *txnmsg, const char *CommissionCode, char *CommissionAmount )
{
	char TempAmount1[ 21 ], TempAmount2[ 21 ];
	struct EzMMSCommissionInfo commisioninfo_rec;
	struct EzMMSCurrencyRate curr_rate_rec1, curr_rate_rec2;
	memset( &commisioninfo_rec, 0, sizeof( struct EzMMSCommissionInfo ) );
	if( readCommissionInfo( txnmsg->ProcessInst, CommissionCode, &commisioninfo_rec ) < 0 )
	{
		trace( "ERROR IN READING INSTID[%s] COMISSIONCODE[%s] FROM COMISSIONINFO MEMORY..LOOKING INTO THE TABLE", txnmsg->ProcessInst, CommissionCode );
		memset( &commisioninfo_rec, 0, sizeof( struct EzMMSCommissionInfo ) );
		//if( readCommissionInfoTable( txnmsg, CommissionCode, &commisioninfo_rec ) < 0 )
			return -1;
		if( addCommissionInfo( commisioninfo_rec ) < 0 )
		{
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			return -1;
		}
	}
	trace( "READ INSTID[%s] COMISSIONCODE[%s] WITH COMISSIONMODE[%c] COMISSIONAMT[%s] CURRCODE[%s]", commisioninfo_rec.InstId, commisioninfo_rec.CommissionCode, commisioninfo_rec.CommissionMode, commisioninfo_rec.CommissionAmt, commisioninfo_rec.CurrCode );

	if( commisioninfo_rec.CommissionMode == COMISSION_MODE_PERCENTAGE )
	{
		memset( TempAmount1, 0, sizeof( TempAmount1 ) );
		amtutil.divideAmount( txnmsg->Amount, "100", TempAmount1 );
		memset( TempAmount2, 0, sizeof( TempAmount2 ) );
		amtutil.multiplyAmount( commisioninfo_rec.CommissionAmt, TempAmount1, TempAmount2 );
	}
	else
	{
		if( txnmsg->AcqCurrencyCode != atoi( commisioninfo_rec.CurrCode ) )
		{
			if( atoi( commisioninfo_rec.CurrCode ) == atoi( ezinstprofileutil.getInstCurrencyCode() ) )
			{
				memset( &curr_rate_rec1, 0, sizeof( struct EzMMSCurrencyRate ) );
				if( getCurrencyRate( txnmsg, txnmsg->AcqCurrencyCode, &curr_rate_rec1 ) < 0 )
					return -1;
				if( curr_rate_rec1.CurrencyMode == CURRENCY_MODE_MULTIPLY )
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.multiplyAmount( commisioninfo_rec.CommissionAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				else
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.divideAmount( commisioninfo_rec.CommissionAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
			}
			else
			{
				memset( &curr_rate_rec1, 0, sizeof( struct EzMMSCurrencyRate ) );
				if( getCurrencyRate( txnmsg, atoi( commisioninfo_rec.CurrCode ), &curr_rate_rec1 ) < 0 )
					return -1;
				if( curr_rate_rec1.CurrencyMode == CURRENCY_MODE_MULTIPLY )
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.multiplyAmount( commisioninfo_rec.CommissionAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				else
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.divideAmount( commisioninfo_rec.CommissionAmt, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				memset( &curr_rate_rec2, 0, sizeof( struct EzMMSCurrencyRate ) );
				if( getCurrencyRate( txnmsg, txnmsg->AcqCurrencyCode, &curr_rate_rec2 ) < 0 )
					return -1;
				if( curr_rate_rec2.CurrencyMode == CURRENCY_MODE_MULTIPLY )
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.multiplyAmount( TempAmount2, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
				else
				{
					memset( TempAmount1, 0, sizeof( TempAmount1 ) );
					amtutil.divideAmount( TempAmount2, curr_rate_rec1.SellingRate, TempAmount1 );
					memset( TempAmount2, 0, sizeof( TempAmount2 ) );
					amtutil.normalizeAmount( TempAmount1, TempAmount2, 2 );
				}
			}
		}
		else
		{
			memset( TempAmount2, 0, sizeof( TempAmount2 ) );
			strcpy( TempAmount2, commisioninfo_rec.CommissionAmt );
		}
	}
	strcpy( CommissionAmount, TempAmount2 );
	return 1;
}

int EzMMSServer :: startAuthorization( struct EzTxnMsg *txnmsg )
{
	char AuthToken[ 20 ];
	int NAuth, AuthRespCode;
	char ExpDate[ 10 ], ServiceCode[ 10 ], CVV[ 10 ], TempPinOffSet[ 20 ];

	initAuthFlags();

	if( ezinstprofileutil.readInstProfile( txnmsg->IssuerInst ) < 0 )
	{
		trace( DEBUG_ERROR, " Error in Reading InstId[%s] From EzInstProfile TABLE" );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		txnmsg->ReasonCode = EZLINK_Reason_InstProfile_Err;
		return -1;
	}

	if( !ezinstprofileutil.isFinInstitution() )
	{
		trace( DEBUG_ERROR, "InstId[%s] is not a Financial Institution..." );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		txnmsg->ReasonCode = EZLINK_Reason_NotFinancialInst_Err;
		return -1;
	}

	AuthRespCode = txnmsg->RespCode;

	processReadMerchantProfile( txnmsg );
	processReadTerminalProfile( txnmsg );

	if( AuthRespCode != txnmsg->RespCode  )
		return -1;

	memset( &txnrule_rec, 0, sizeof( struct EzMMSMerchantTxnRule ) );
	if( readTxnRule( txnmsg, merchantprofile_rec.MerchantTypeId, &txnrule_rec ) < 0 )
	{
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}

	NAuth = tkutil.getNToken( txnrule_rec.AuthList, '~' );

	memset( &txninfo_rec, 0, sizeof( struct EzMMSTxnInfo ) );
	memset( txninfo_rec.TxnRefNum, 0, sizeof( txninfo_rec.TxnRefNum ) );
	sprintf( txninfo_rec.TxnRefNum, "%s--%06d--%06d--%s--%s--%06d--%06d", txnmsg->m_chn, txnmsg->TxnCode, txnmsg->TraceNo, txnmsg->RefNum, txnmsg->TerminalId, txnmsg->TranDate, txnmsg->TranTime );

	for( int i = 0; i < NAuth; i++ )
	{
		memset( AuthToken, 0, sizeof( AuthToken ) );
		tkutil.getToken( txnrule_rec.AuthList, AuthToken, '~', i + 1 );
		if( tkutil.CheckInteger( AuthToken ) < 0 )
			continue;
		trace( "AuthToken[%s]", AuthToken );
		switch ( atoi( AuthToken ) )
		{
			case READ_MERCHANT_PROFILE:
			processReadMerchantProfile( txnmsg );
			break;

			case READ_STORE_PROFILE:
			processReadMerchantProfile( txnmsg );
			processReadTerminalProfile( txnmsg );
			processReadStoreProfile( txnmsg );
			break;

			case READ_TERMINAL_PROFILE:
			processReadMerchantProfile( txnmsg );
			processReadTerminalProfile( txnmsg );
			processReadStoreProfile( txnmsg );
			break;

			case LOAD_MERCHANT_ACCOUNTS:
			if( !LOAD_MERCHANT_ACCOUNTS_FLAG )
			{
				trace( "LOADING ACCOUNTS FOR INSTID<%s> MERCHANTID<%s>", txnmsg->ProcessInst, txnmsg->AcceptorId );
				N_ACCTS = LoadAccounts( txnmsg );
				LOAD_MERCHANT_ACCOUNTS_FLAG = true;
			}
			break;

			case PEFORM_MERCHANT_ACCOUNTING:
			if( !PEFORM_MERCHANT_ACCOUNTING_FLAG )
			{
				char FeeCode[ 33 ], CommissionCode[ 33 ];
				int N_FEE, N_COMMISION;
				char NetAmount[ 20 ], FeeAmount[ 20 ], CommissionAmount[ 20 ], TempAmount[ 20 ];
				bool SUCCESS_FLAG;

				N_FEE = tkutil.getNToken( txnrule_rec.FeeList, ',' );

				memset( NetAmount, 0, sizeof( NetAmount ) );
				strcpy( NetAmount, txnmsg->Amount );

				SUCCESS_FLAG = true;
				for( int i = 0; i < N_FEE; i++ )
				{
					memset( FeeCode, 0, sizeof( FeeCode ) );
					tkutil.getTokenExSpaces( txnrule_rec.FeeList, FeeCode, ',', i + 1 );
					memset( FeeAmount, 0, sizeof( FeeAmount ) );
					if( getFeeAmount( txnmsg, FeeCode, FeeAmount ) < 0 )
					{
						SUCCESS_FLAG = false;
						break;
					}
					memset( TempAmount, 0, sizeof( TempAmount ) );
					amtutil.subAmount( NetAmount, FeeAmount, TempAmount );
					memset( NetAmount, 0, sizeof( NetAmount ) );
					amtutil.normalizeAmount( TempAmount, NetAmount, 2 );
				}

				if( !SUCCESS_FLAG )
					break;

				trace( "NETAMOUNT AFTER FEE DEDUCTION IS [%s]", NetAmount );

				N_COMMISION = tkutil.getNToken( txnrule_rec.CommissionList, ',' );

				SUCCESS_FLAG = true;
				for( int i = 0; i < N_COMMISION; i++ )
				{
					memset( CommissionCode, 0, sizeof( CommissionCode ) );
					tkutil.getTokenExSpaces( txnrule_rec.CommissionList, CommissionCode, ',', i + 1 );
					memset( CommissionAmount, 0, sizeof( CommissionAmount ) );
					if( getCommissionAmount( txnmsg, CommissionCode, CommissionAmount ) < 0 )
					{
						SUCCESS_FLAG = false;
						break;
					}
					memset( TempAmount, 0, sizeof( TempAmount ) );
					amtutil.addAmount( NetAmount, CommissionAmount, TempAmount );
					memset( NetAmount, 0, sizeof( NetAmount ) );
					amtutil.normalizeAmount( TempAmount, NetAmount, 2 );
				}

				if( !SUCCESS_FLAG )
					break;

				trace( "NETAMOUNT AFTER ADDING COMMISION IS [%s]", NetAmount );

				memset( txninfo_rec.NetAmount, 0, sizeof( txninfo_rec.NetAmount ) );
				strcpy( txninfo_rec.NetAmount, NetAmount );
				memset( txninfo_rec.CommissionAmount, 0, sizeof( txninfo_rec.CommissionAmount ) );
				strcpy( txninfo_rec.CommissionAmount, CommissionAmount );
				memset( txninfo_rec.FeeAmount, 0, sizeof( txninfo_rec.FeeAmount ) );
				strcpy( txninfo_rec.FeeAmount, FeeAmount );
				memset( txninfo_rec.TxnType, 0, sizeof( txninfo_rec.TxnType ) );
				strcpy( txninfo_rec.TxnType, txnrule_rec.OperationType );
				memset( txninfo_rec.TxnDesc, 0, sizeof( txninfo_rec.TxnDesc ) );
				sprintf( txninfo_rec.TxnDesc, "%06d %06d %s %s", txnmsg->TranDate, txnmsg->TranTime, txninfo_rec.TxnType, txninfo_rec.NetAmount );

				if( insertTransaction( txnmsg, &txninfo_rec ) < 0 )
					break;

				if( insertTermTxn( txnmsg, &txninfo_rec ) < 0 )
					break;

				if( updateMerchantBalance( txnmsg, &txninfo_rec ) < 0 )
					break;

				PEFORM_MERCHANT_ACCOUNTING_FLAG = true;
			}
			break;

			case CHECK_MERCHANT_AVAIL_BALANCE:

			if( !CHECK_MERCHANT_AVAIL_BALANCE_FLAG )
			{
				if( !READ_MERCHANT_FROM_ACCOUNT_PROFILE_FLAG )
				{
					trace( "READ ACCOUNT PROFILE FOR INSTID<%s> ACCOUNTNO<%s>", txnmsg->ProcessInst, txnmsg->FromAccount  );
					readAccountProfile( txnmsg );
					READ_MERCHANT_FROM_ACCOUNT_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}

				trace( "CHECK AVAILABLE BALANCE FOR INSTID<%s> ACCOUNTNO<%s>", txnmsg->ProcessInst, txnmsg->FromAccount  );
				checkAvailableBalance( txnmsg );
				CHECK_MERCHANT_AVAIL_BALANCE_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_LEDGER_BALANCE:

			if( !CHECK_MERCHANT_LEDGER_BALANCE_FLAG )
			{
				if( !READ_MERCHANT_FROM_ACCOUNT_PROFILE_FLAG )
				{
					trace( "READ ACCOUNT PROFILE FOR INSTID<%s> ACCOUNTNO<%s>", txnmsg->ProcessInst, txnmsg->FromAccount  );
					readAccountProfile( txnmsg );
					READ_MERCHANT_FROM_ACCOUNT_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}

				trace( "CHECK LEDGER BALANCE FOR INSTID<%s> ACCOUNTNO<%s>", txnmsg->ProcessInst, txnmsg->FromAccount  );
				checkLedgerBalance( txnmsg );
				CHECK_MERCHANT_LEDGER_BALANCE_FLAG = true;
			}

			break;

			case READ_MERCHANT_CARD_PROFILE:

			if( !READ_MERCHANT_CARD_PROFILE_FLAG )
			{
				memset( &cardprofile_rec, 0, sizeof( struct EzMMSCardProfile ) );
				readCardProfile( txnmsg, &cardprofile_rec );
				READ_MERCHANT_CARD_PROFILE_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_CARD_STATUS:

			if( !CHECK_MERCHANT_CARD_STATUS_FLAG )
			{
				if( !READ_MERCHANT_CARD_PROFILE_FLAG )
				{
					memset( &cardprofile_rec, 0, sizeof( struct EzMMSCardProfile ) );
					readCardProfile( txnmsg, &cardprofile_rec );
					READ_MERCHANT_CARD_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}
				readStatusMap( txnmsg );
				CHECK_MERCHANT_CARD_STATUS_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_CARD_TRACKEXPIRY:

			if( !CHECK_MERCHANT_CARD_TRACKEXPIRY_FLAG )
			{
				checkTrackExpiry( txnmsg );
				CHECK_MERCHANT_CARD_TRACKEXPIRY_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_CARD_DBEXPIRY:

			if( !CHECK_MERCHANT_CARD_DBEXPIRY_FLAG )
			{
				if( !READ_MERCHANT_CARD_PROFILE_FLAG )
				{
					memset( &cardprofile_rec, 0, sizeof( struct EzMMSCardProfile ) );
					readCardProfile( txnmsg, &cardprofile_rec );
					READ_MERCHANT_CARD_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}
				checkDBExpiry( txnmsg );
				CHECK_MERCHANT_CARD_DBEXPIRY_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_CARD_PIN:

			if( !CHECK_MERCHANT_CARD_PIN_FLAG )
			{
				if( !READ_MERCHANT_CARD_PROFILE_FLAG )
				{
					memset( &cardprofile_rec, 0, sizeof( struct EzMMSCardProfile ) );
					readCardProfile( txnmsg, &cardprofile_rec );
					READ_MERCHANT_CARD_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}

				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					if ( !strcmp( txnmsg->DeviceType, "ATM" ) )
					{
						if( txnmsg->PinVerFlg == 'Y' || txnmsg->PinVerFlg == 'y' )
						{
							if( VerifyATMPIN( txnmsg->ProcessInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->PINBlock, cardprofile_rec.PINOffset ) < 0  )
								InvalidPIN( txnmsg, &cardprofile_rec );
							else
								GoodPIN( txnmsg , &cardprofile_rec );
						}
						else
							GoodPIN( txnmsg , &cardprofile_rec );
					}
					else if( !strcmp( txnmsg->DeviceType, "POS" ) )
					{
						if( VerifyTerminalPIN( txnmsg->ProcessInst, txnmsg->TerminalId, txnmsg->chn, txnmsg->PINBlock, txnmsg->PinKey, strlen( txnmsg->PinKey ), cardprofile_rec.PINOffset  ) < 0 )
							InvalidPIN( txnmsg, &cardprofile_rec );
						else
							GoodPIN( txnmsg, &cardprofile_rec );
					}
					else
					{
						if( VerifyDevicePIN( txnmsg->ProcessInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->PINBlock, cardprofile_rec.PINOffset ) < 0  )
							InvalidPIN( txnmsg, &cardprofile_rec );
						else
							GoodPIN( txnmsg, &cardprofile_rec );
					}
				}
				else
				{
					if( VerifyNetworkPIN( txnmsg->ProcessInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->PINBlock, cardprofile_rec.PINOffset ) < 0  )
						InvalidPIN( txnmsg, &cardprofile_rec );
					else
						GoodPIN( txnmsg, &cardprofile_rec );
				}
				CHECK_MERCHANT_CARD_PIN_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_CARD_CVV1:

			if( !CHECK_MERCHANT_CARD_CVV1_FLAG )
			{
				memset( ExpDate, 0, sizeof( ExpDate ) );
				getExpDate( txnmsg->Track2, ExpDate );
				memset( ServiceCode, 0, sizeof( ServiceCode ) );
				getServiceCode( txnmsg->Track2, ServiceCode );
				memset( CVV, 0, sizeof( CVV ) );
				getCVV( txnmsg->Track2, CVV );

				if( verifyCVV( txnmsg->IssuerInst, txnmsg->chn, ExpDate, ServiceCode, CVV ) < 0  )
				{
					txnmsg->RespCode = EZLINK_RC_InvalidCVV;
					txnmsg->ReasonCode = EZLINK_Reason_CVVVerifyErr;
					break;
				}
				CHECK_MERCHANT_CARD_CVV1_FLAG = true;
			}

			break;

			case CHECK_MERCHANT_CARD_CVV2:

			if( !CHECK_MERCHANT_CARD_CVV2_FLAG )
			{
				memset( ExpDate, 0, sizeof( ExpDate ) );
				getExpDate( txnmsg->Track2, ExpDate );
				memset( ServiceCode, 0, sizeof( ServiceCode ) );
				getServiceCode( txnmsg->Track2, ServiceCode );
				memset( CVV, 0, sizeof( CVV ) );
				strcpy( CVV, txnmsg->RsvFld6 );

				if( verifyCVV( txnmsg->IssuerInst, txnmsg->chn, ExpDate, ServiceCode, CVV ) < 0  )
				{
					txnmsg->RespCode = EZLINK_RC_InvalidCVV;
					txnmsg->ReasonCode = EZLINK_Reason_CVVVerifyErr;
					break;
				}
				CHECK_MERCHANT_CARD_CVV2_FLAG = true;
			}

			break;

			case GENERATE_MERCHANT_CARD_NEW_PIN_OFFSET:

			if( !GENERATE_MERCHANT_CARD_NEW_PIN_OFFSET_FLAG )
			{
				if( !READ_MERCHANT_CARD_PROFILE_FLAG )
				{
					memset( &cardprofile_rec, 0, sizeof( struct EzMMSCardProfile ) );
					readCardProfile( txnmsg, &cardprofile_rec );
					READ_MERCHANT_CARD_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}

				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					if ( !strcmp( txnmsg->DeviceType, "ATM" ) )
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenATMPinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &cardprofile_rec );
						else
						{
							if( !strcmp( TempPinOffSet, cardprofile_rec.PINOffset ) )
							{
								trace( "NewPinOffset & Old PinOffset are Same...." );
								txnmsg->RespCode = EZLINK_RC_NewPINError;
								GENERATE_MERCHANT_CARD_NEW_PIN_OFFSET_FLAG = true;
								break;
							}
							NewPINChangeSucced( txnmsg, TempPinOffSet, &cardprofile_rec );
						}
					}
					else
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &cardprofile_rec );
						else
						{
							if( !strcmp( TempPinOffSet, cardprofile_rec.PINOffset ) )
							{
								trace( "NewPinOffset & Old PinOffset are Same...." );
								txnmsg->RespCode = EZLINK_RC_NewPINError;
								GENERATE_MERCHANT_CARD_NEW_PIN_OFFSET_FLAG = true;
								break;
							}
							NewPINChangeSucced( txnmsg, TempPinOffSet, &cardprofile_rec );
						}
					}
				}
				else
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenNetworkPinOffset( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &cardprofile_rec );
					else
					{
						if( !strcmp( TempPinOffSet, cardprofile_rec.PINOffset ) )
						{
							trace( "NewPinOffset & Old PinOffset are Same...." );
							txnmsg->RespCode = EZLINK_RC_NewPINError;
							GENERATE_MERCHANT_CARD_NEW_PIN_OFFSET_FLAG = true;
							break;
						}
						NewPINChangeSucced( txnmsg, TempPinOffSet, &cardprofile_rec );
					}
				}
				GENERATE_MERCHANT_CARD_NEW_PIN_OFFSET_FLAG = true;
			}
			break;

			case GENERATE_MERCHANT_CARD_CONFIRM_PIN_OFFSET:

			if( !GENERATE_MERCHANT_CARD_CONFIRM_PIN_OFFSET_FLAG )
			{
				if( !READ_MERCHANT_CARD_PROFILE_FLAG )
				{
					memset( &cardprofile_rec, 0, sizeof( struct EzMMSCardProfile ) );
					readCardProfile( txnmsg, &cardprofile_rec );
					READ_MERCHANT_CARD_PROFILE_FLAG = true;
					if( AuthRespCode != txnmsg->RespCode  )
						break;
				}

				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					if ( !strcmp( txnmsg->DeviceType, "ATM" ) )
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenATMPinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &cardprofile_rec );
						else
							ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &cardprofile_rec );
					}
					else
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &cardprofile_rec );
						else
							ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &cardprofile_rec );
					}
				}
				else
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenNetworkPinOffset( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &cardprofile_rec );
					else
						ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &cardprofile_rec );
				}
				GENERATE_MERCHANT_CARD_CONFIRM_PIN_OFFSET_FLAG = true;
			}

			break;

		}
		if( AuthRespCode != txnmsg->RespCode  )
			break;
	}
	return 1;
}

void EzMMSServer :: serviceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgLen;

	while( 1 )
	{
		dbutil.dbUtilClose();
		trace( "EZMMS SERVER WAITING TO SERVICE REQUEST->->->");
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * ) &txnmsg, &MsgLen ) < 0 )
		{
			trace( "Error in Reading Message from EzAuthMgr Channel" );
			continue;
		}

		trace( "Read Message MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.IssuerInst, txnmsg.m_chn, txnmsg.FromAccount, txnmsg.Amount, txnmsg.RespCode );
		dbutil.dbUtilConnect();
		startAuthorization( &txnmsg );
		txnmsg.MsgType += 10;
		sendResponse( &txnmsg );
	}
}

int main( int argc, char **argv )
{
	EzMMSServer ezmmsserverobj;;
	ezmmsserverobj.init( argv[ 0 ] );
	ezmmsserverobj.serviceRequest();
	return 1;
}



