#include <ezlink/ezauthmgr.h>
//#include <ezutils/ezdbutil.h>

EzAuthMgr :: EzAuthMgr()
{
}

EzAuthMgr :: ~EzAuthMgr()
{
}

void EzAuthMgr :: InitEzAuthMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezauthmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
    	trace( "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
	}

	if( CreateChannel( "EzAuthMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzAuthMgr" );
    	trace( "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
    }

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "AUTH#MAXACCOUNTS", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching MAXACCOUNTS from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CheckNumeric( cfgval ) < 0 )
	{
		trace( "MaxAccounts[%s] not an numeric value", cfgval );
		trace( "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	MaxAccounts = atoi( cfgval );
	trace( "Maximum No.of Accounts Supported per Card[%d]", MaxAccounts );
	acctlist = ( struct AccountList * ) malloc( sizeof( struct AccountList ) * MaxAccounts );

	/*if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing DBUtil.... " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with database " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}*/

	if( ezinstprofileutil.initInstProfile( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzInstProfileUtil" );
		trace( DEBUG_CRITICAL,"^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezauthpropertyutil.initAuthPropertyUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzAuthPropertyUtil" );
		trace( DEBUG_CRITICAL,"^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzSecurityUtil" );
	    trace( DEBUG_CRITICAL,"^^^^^^^^^^^EzAuthMgr Ended Abnormally^^^^^^^^^^^^^");
	    closeDebug();
	    TaskExit();
    }

	InitEzAuthUtil( TaskName, this, MaxAccounts, &ezinstprofileutil, &ezpadssutil );

	TaskInit();
	initEzSigUtil( this );
}

void EzAuthMgr :: getExpDate( const char *Track2Data, char *ExpData )
{
	int offset = 0;
	for( int i = 0; i < strlen( Track2Data ); i++ )
	{
		if( Track2Data[ i ] == '=' || Track2Data[ i ] == 'd' || Track2Data[ i ] == 'D' )
		{
			offset = i;
			break;
		}
	}
	strncpy( ExpData, Track2Data + offset + 1, 4 );
}

void EzAuthMgr :: getServiceCode( const char *Track2Data, char *ServiceCode )
{
	int offset = 0;
	for( int i = 0; i < strlen( Track2Data ); i++ )
	{
		if( Track2Data[ i ] == '=' || Track2Data[ i ] == 'd' || Track2Data[ i ] == 'D' )
		{
			offset = i;
			break;
		}
	}
	strncpy( ServiceCode, Track2Data + offset + 1 + 4, 3 );
}

void EzAuthMgr :: getCVV( const char *Track2Data, char *CVV )
{
	int offset = 0;
	for( int i = 0; i < strlen( Track2Data ); i++ )
	{
		if( Track2Data[ i ] == '=' || Track2Data[ i ] == 'd' || Track2Data[ i ] == 'D' )
		{
			offset = i;
			break;
		}
	}
	strncpy( CVV, Track2Data + offset + 1 + 7, 3 );
}

int EzAuthMgr :: StartAuthorization( struct EzTxnMsg *txnmsg )
{
	int NAuth, nAccounts, FldCount, bufoffset = 0, AuthRespCode;
	bool CARD_CHECK_FLAG = false;
	bool ACCOUNT_CHECK_FLAG = false;
	bool CUSTOMER_CHECK_FLAG = false;
	char AuthToken[ 100 ] , DeviceType[ 11 ];
	struct EzCardInfo crdinfo;
	struct EzCustomerInfo custinfo;
	struct EzAccountInfo accountinfo ;
	char OARPath[ 100 ] ,OARFileName[ 100 ], TempPinOffSet[ 11 ],OarFileName[ 150 ],FieldVal[ 25  ], AuthList[ 513 ];
	char ExpDate[ 10 ], ServiceCode[ 10 ], CVV[ 10 ];

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
	memset( AuthList, 0, sizeof( AuthList ) );
	if( ezauthpropertyutil.readAuthProperty( txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode, txnmsg->IssuerInst, ezinstprofileutil.getInstAuthGroup(), AuthList ) < 0 )
	{
		trace( DEBUG_ERROR, " Error in Reading AuthProperty From EzAuthProperty TABLE" );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}

	trace( DEBUG_NORMAL, "AuthList[%s]", AuthList );

	AuthRespCode = txnmsg->RespCode;

	NAuth = GetNAuth( AuthList );

	for( int i = 0; i < NAuth; i++ )
	{
		memset( AuthToken, 0, sizeof( AuthToken ) );
		GetToken( AuthList, AuthToken, i + 1 );
		if( CheckNumeric( AuthToken ) < 0 )
			continue;
		trace( DEBUG_TXN, "AuthToken[%s]", AuthToken );

		switch ( atoi( AuthToken ) )
		{
			case CARD_CHECK:
				trace( DEBUG_TXN, "CHECKING THE CARDINFO FOR THE CARD NUMBER [%s] [%s]", txnmsg->m_chn, txnmsg->t_chn  );
				memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
				ReadCardInfo( txnmsg, &crdinfo );
				CARD_CHECK_FLAG = true;
			break;

			case CARDSTATUS_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE CARD STATUS FOR THE CARD NUMBER [%s]",txnmsg->m_chn  );
				ReadStatusMap( txnmsg , crdinfo.status );
				if( txnmsg->TxnCode / 10000 == 94 && crdinfo.status == EZLINK_RC_FirstUseCard )
					txnmsg->RespCode = EZLINK_RC_Approved;
			break;

			case CARDEXPIRY_DB_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE DB EXPIRY DATE FOR THE CARD NUMBER [%s]",txnmsg->m_chn  );
				if( CheckDBExpiryDate( crdinfo.expirydate ) < 0 )
				{
					trace( DEBUG_TXN, "CARD NUMBER [%s] IS EXPIRED CARD",txnmsg->m_chn  );
					txnmsg->RespCode = EZLINK_RC_ExpiredCard;
					break;
				}
			break;

			case CARDEXPIRY_TRACK_CHECK:
				trace( DEBUG_TXN, "CHECKING THE TRACK EXPIRY DATE FOR THE CARD NUMBER [%s]",txnmsg->m_chn  );
				if( CheckTrackExpiryDate( txnmsg->Track2 ) < 0 )
				{
					trace( DEBUG_TXN, "CARD NUMBER [%s] IS EXPIRED CARD",txnmsg->m_chn  );
					//txnmsg->RespCode = EZLINK_RC_ExpiredCard;
					break;
				}
			break;

			case CARDTXNGROUP_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE TRANSACTION TYPE[%d] ALLOWED FOR THE CARD NUMBER [%s]", txnmsg->TxnCode, txnmsg->m_chn  );
				CheckTxnAllowed( txnmsg, crdinfo.txngroupid );
			break;

			case CARDPIN_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE PIN FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );

				/*Check for Device Request or Network Request*/
				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					if ( !strcmp( txnmsg->DeviceType, "ATM" ) )
					{
						if( txnmsg->PinVerFlg == 'Y' || txnmsg->PinVerFlg == 'y' )
						{
							if( VerifyATMPIN( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->PINBlock, crdinfo.pinoffset ) < 0  )
							{
								memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
								if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
									break;
								CARD_CHECK_FLAG = true;
								InvalidPIN( txnmsg, &crdinfo );
								break;
							}
							else
								GoodPIN( txnmsg , &crdinfo );
						}
						else
							GoodPIN( txnmsg , &crdinfo );
					}
					else if( !strcmp( txnmsg->DeviceType, "POS") )
					{
						if( VerifyTerminalPIN( txnmsg->IssuerInst, txnmsg->TerminalId, txnmsg->chn, txnmsg->PINBlock, txnmsg->PinKey, strlen( txnmsg->PinKey ), crdinfo.pinoffset  ) < 0 )
						{
							memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
							if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
								break;
							CARD_CHECK_FLAG = true;
							InvalidPIN( txnmsg, &crdinfo );
							break;
						}
						else
							GoodPIN( txnmsg , &crdinfo );
					}
					else
					{
						if( VerifyDevicePIN( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->PINBlock, crdinfo.pinoffset ) < 0  )
						{
							memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
							if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
								break;
							CARD_CHECK_FLAG = true;
							InvalidPIN( txnmsg, &crdinfo );
							break;
						}
						else
							GoodPIN( txnmsg , &crdinfo );
					}
				}
				else
				{
					if( VerifyNetworkPIN( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->PINBlock, crdinfo.pinoffset ) < 0  )
					{
						memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
						if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
							break;
						CARD_CHECK_FLAG = true;
						InvalidPIN( txnmsg, &crdinfo );
						break;
					}
					else
						GoodPIN( txnmsg , &crdinfo );
				}
			break;
			case TELEPIN_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE PIN FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
				if( VerifyDevicePIN( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->PINBlock, crdinfo.tpinoffset ) < 0  )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
					InvalidTelePIN( txnmsg, &crdinfo );
					break;
				}
				else
					GoodTelePIN( txnmsg , &crdinfo );
			break;

			case CVV1_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE CVV1 FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
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
				else
				{
					CARD_CHECK_FLAG = true;
					break;
				}
				break;

			case CVV2_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE CVV2 FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
				memset( ExpDate, 0, sizeof( ExpDate ) );
				getExpDate( txnmsg->Track2, ExpDate );
				memset( ServiceCode, 0, sizeof( ServiceCode ) );
				strcpy( ServiceCode, "000" );
				memset( CVV, 0, sizeof( CVV ) );
				strcpy( CVV, txnmsg->RsvFld6 );
				if( verifyCVV( txnmsg->IssuerInst, txnmsg->chn, ExpDate, ServiceCode, CVV ) < 0  )
				{
					txnmsg->RespCode = EZLINK_RC_InvalidCVV;
					txnmsg->ReasonCode = EZLINK_Reason_CVVVerifyErr;
					break;
				}
				else
				{
					CARD_CHECK_FLAG = true;
					break;
				}
				break;

			case LIMIT_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				switch( crdinfo.limitflag )
				{
					case CARD_LIMIT_FLAG:
						if( !CARD_CHECK_FLAG )
						{
							memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
							if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
								break;
							CARD_CHECK_FLAG = true;
						}
						trace( DEBUG_TXN, "CHECKING THE CARD BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
						CheckCardLimit( txnmsg );
						break;

					case CARDTYPE_LIMIT_FLAG:
						if( !CARD_CHECK_FLAG )
						{
							memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
							if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
								break;
							CARD_CHECK_FLAG = true;
						}

						trace( DEBUG_TXN, "CHECKING THE CARD TYPE BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
						CheckCardTypeLimit( txnmsg, crdinfo.cardtype );
						break;

					case CARD_ACCT_LIMIT_FLAG:

						if( !CARD_CHECK_FLAG )
						{
							memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
							if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
								break;
							CARD_CHECK_FLAG = true;
						}
						trace( DEBUG_TXN, "CHECKING THE CARD BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
						if( CheckCardLimit( txnmsg ) < 0 )
							break;
						else
						{
							if( !ACCOUNT_CHECK_FLAG )
							{
								memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
								if( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
									break;
								ACCOUNT_CHECK_FLAG = true;
							}

							switch( accountinfo.limitflag )
							{
								case ACCOUNT_LIMIT_FLAG:
									trace( DEBUG_TXN, "CHECKING THE ACCOUNT BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
									CheckAccountLimit( txnmsg );
									break;
								case ACCOUNTTYPE_LIMIT_FLAG:
									trace( DEBUG_TXN, "CHECKING THE ACCOUNT TYPE BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
									CheckAccountTypeLimit( txnmsg, accountinfo.accounttype );
									break;
								default:
									trace( DEBUG_TXN, "InVaild ACCOUNT Limit Flag[%c]", accountinfo.limitflag );
									break;
							}
						}
					break;

					case CARDTYPE_ACCT_LIMIT_FLAG:
						if( !CARD_CHECK_FLAG )
						{
							memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
							if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
								break;
							CARD_CHECK_FLAG = true;
						}

						trace( DEBUG_TXN, "CHECKING THE CARD TYPE BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
						if( CheckCardTypeLimit( txnmsg, crdinfo.cardtype ) < 0 )
							break;
						else
						{
							if( !ACCOUNT_CHECK_FLAG )
							{
								memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
								if( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
									break;
								ACCOUNT_CHECK_FLAG = true;
							}
							switch( accountinfo.limitflag )
							{
								case ACCOUNT_LIMIT_FLAG:
									trace( DEBUG_TXN, "CHECKING THE ACCOUNT BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
									CheckAccountLimit( txnmsg );
									break;
								case ACCOUNTTYPE_LIMIT_FLAG:
									trace( DEBUG_TXN, "CHECKING THE ACCOUNT TYPE BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
									CheckAccountTypeLimit( txnmsg, accountinfo.accounttype );
									break;
								default:
									trace( DEBUG_TXN, "InVaild ACCOUNT Limit Flag[%c]", accountinfo.limitflag );
									break;
							}
						}
					break;

					case ACCOUNT_LIMIT_LOOKUP_FLAG:
						if( !ACCOUNT_CHECK_FLAG )
						{
							memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
							if( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
								break;
							ACCOUNT_CHECK_FLAG = true;
						}
						switch( accountinfo.limitflag )
						{
							case ACCOUNT_LIMIT_FLAG:
								trace( DEBUG_TXN, "CHECKING THE ACCOUNT BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
								CheckAccountLimit( txnmsg );
								break;
							case ACCOUNTTYPE_LIMIT_FLAG:
								trace( DEBUG_TXN, "CHECKING THE ACCOUNT TYPE BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->m_chn  );
								CheckAccountTypeLimit( txnmsg, accountinfo.accounttype );
								break;
							default:
								trace( DEBUG_TXN, "InVaild ACCOUNT Limit Flag[%c]", accountinfo.limitflag );
								break;
						}
					break;
				}
				break;

			case CUSTOMER_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				if( !CUSTOMER_CHECK_FLAG )
				{
					memset( &custinfo, 0, sizeof( struct EzCustomerInfo ) );
					if( ReadCustomerInfo( txnmsg, crdinfo.custid, &custinfo ) < 0 )
						break;
					CUSTOMER_CHECK_FLAG = true;
				}
			break;

			case OAR_CHECK:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				memset( acctlist, 0, sizeof( struct AccountList ) * MaxAccounts );
				nAccounts = ReadFromAccounts( txnmsg, acctlist );
				trace("nAccounts[%d]", nAccounts);
				if( nAccounts <= 0 )
					break;

				memset( OARFileName, 0, sizeof( OARFileName ) );
				if( getOARFileName( txnmsg, OARFileName ) < 0 )
				{
					trace( "Unable to get param from EzOarFileParam Table ");
					break;
				}

				strcat( OARFileName, ".inf" );

				memset( OARPath, 0, sizeof( OARPath ) );
				sprintf( OARPath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "inf", OARFileName );
				WriteOARFile( OARPath, acctlist, nAccounts );

				strcpy( txnmsg->RespFile, OARFileName);

				trace(" OARFileName [%s] OARPath[%s]", OARFileName, OARPath );
			break;

			case READ_FROM_ACCOUNT_CHECK:

				memset( txnmsg->FromAccount, 0, sizeof( txnmsg->FromAccount ) );
				memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
				if( GetFromAccount( txnmsg, txnmsg->FromAccount, &accountinfo ) < 0 )
					trace("Error in Reading From Account for CHN[%s]", txnmsg->m_chn );
			break;

			case READ_TO_ACCOUNT_CHECK:

				memset( txnmsg->ToAccount, 0, sizeof( txnmsg->ToAccount ) );
				if( GetToAccount( txnmsg, txnmsg->ToAccount ) < 0 )
					trace("Error in Reading To Account for CHN[%s]", txnmsg->m_chn );

			break;

			case FROM_ACCOUNT_CHECK:
				if( !ACCOUNT_CHECK_FLAG )
				{
					memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
					if( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
						break;

					ACCOUNT_CHECK_FLAG = true;

					strcpy( txnmsg->IssBranchCode, accountinfo.branchcode );
					txnmsg->IssCurrencyCode = atoi( accountinfo.currcode );
					if( !strcmp( accountinfo.accountno,txnmsg->FromAccount))
						strcpy( txnmsg->FromAcctSubType, accountinfo.productcode );
				}
			break;

			case TO_ACCOUNT_CHECK:
					memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
					if( ReadAccountInfo( txnmsg,txnmsg->ToAccount, &accountinfo ) < 0 )
						break;

					ACCOUNT_CHECK_FLAG = true;

					strcpy( txnmsg->TxfBranchCode, accountinfo.branchcode );
					//txnmsg->TxfCurrencyCode = atoi( accountinfo.currcode );
					if( !strcmp( accountinfo.accountno, txnmsg->ToAccount))
						strcpy( txnmsg->ToAcctSubType, accountinfo.productcode );

			break;

			case GENERATE_NEW_PIN_OFFSET:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				/*Check for Device Request or Network Request*/
				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					if( txnmsg->MerchantType == 6011 )
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenATMPinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &crdinfo );
						else
						{
							if( !strcmp( TempPinOffSet, crdinfo.pinoffset ) )
							{
								trace( "NewPinOffset & Old PinOffset are Same...." );
								txnmsg->RespCode = EZLINK_RC_NewPINError;
								break;
							}
							NewPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
						}
					}
					else
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &crdinfo );
						else
						{
							if( !strcmp( TempPinOffSet, crdinfo.pinoffset ) )
							{
								trace( "NewPinOffset & Old PinOffset are Same...." );
								txnmsg->RespCode = EZLINK_RC_NewPINError;
								break;
							}
							NewPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
						}
					}
				}
				else
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenNetworkPinOffset( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &crdinfo );
					else
					{
						if( !strcmp( TempPinOffSet, crdinfo.pinoffset ) )
						{
							trace( "NewPinOffset & Old PinOffset are Same...." );
							txnmsg->RespCode = EZLINK_RC_NewPINError;
							break;
						}
						NewPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
					}
				}
			break;

			case GENERATE_CONFIRM_PIN_OFFSET:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				/*Check for Device Request or Network Request*/
				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					if( txnmsg->MerchantType == 6011 )
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenATMPinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &crdinfo );
						else
							ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
					}
					else
					{
						memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
						if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
							PINChangeFailed( txnmsg, &crdinfo );
						else
							ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
					}
				}
				else
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenNetworkPinOffset( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &crdinfo );
					else
						ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
				}
			break;
			//Added for TelePin

			case GENERATE_NEW_TELEPIN_OFFSET:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				/*Check for Device Request or Network Request*/
				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &crdinfo );
					else
						NewTELEPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
				}
				else
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenNetworkPinOffset( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &crdinfo );
					else
						NewTELEPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
				}
			break;

			case GENERATE_CONFIRM_TELEPIN_OFFSET:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				/*Check for Device Request or Network Request*/
				if( txnmsg->DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &crdinfo );
					else
						ConfirmTELEPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
				}
				else
				{
					memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
					if( GenNetworkPinOffset( txnmsg->IssuerInst, txnmsg->NetworkId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
						PINChangeFailed( txnmsg, &crdinfo );
					else
						ConfirmTELEPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
				}
			break;

			case GENERATE_TRITON_PIN_OFFSET:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}

				memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
				if( GenDevicePinOffset( txnmsg->IssuerInst, txnmsg->OrgPort, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
					PINChangeFailed( txnmsg, &crdinfo );
				else
					ConfirmTritonPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
			break;

			case ACCOUNT_AVAILBAL_CHECK:
				if( !ACCOUNT_CHECK_FLAG )
				{
					memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
					if ( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
						break;

					ACCOUNT_CHECK_FLAG = true;
				}
				memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
				CheckAccountAvailBal( txnmsg, &accountinfo );
			break;

			case ACCOUNT_LEDGERBAL_CHECK:
				if( !ACCOUNT_CHECK_FLAG )
				{
					memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
					if ( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
							break;
					ACCOUNT_CHECK_FLAG = true;
				}
				memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
				CheckAccountLedgerBal( txnmsg, &accountinfo );
			break;

			case UPDATE_AVAILBAL:
				if( !ACCOUNT_CHECK_FLAG )
				{
					memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
					if ( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
						break;
					ACCOUNT_CHECK_FLAG = true;
				}
				memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
				UpdateAcctAvailBalance( txnmsg );
			break;

			case UPDATE_LEDGERBAL:
				if( !ACCOUNT_CHECK_FLAG )
				{
					memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
					if ( ReadAccountInfo( txnmsg,txnmsg->FromAccount, &accountinfo ) < 0 )
							break;
					ACCOUNT_CHECK_FLAG = true;
				}
				memset( &accountinfo, 0, sizeof( struct EzAccountInfo ) );
				UpdateAcctLedgerBalance( txnmsg );
			break;

			case INCREMENT_AVAILBAL:
				IncrementAvailBalance( txnmsg );
			break;

			case DECREMENT_AVAILBAL:
				DecrementAvailBalance( txnmsg );
			break;

			case INCREMENT_LEDGERBAL:
				IncrementLedgerBalance( txnmsg );
			break;

			case DECREMENT_LEDGERBAL:
				DecrementLedgerBalance( txnmsg );
			break;

			case INCREMENT_ACCUM:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				if( ( crdinfo.limitflag == CARD_LIMIT_FLAG ) || ( crdinfo.limitflag == CARDTYPE_LIMIT_FLAG ) )
					IncrementCardAccum( txnmsg );
				else if( ( crdinfo.limitflag == CARD_ACCT_LIMIT_FLAG ) || ( crdinfo.limitflag == CARDTYPE_ACCT_LIMIT_FLAG ) )
				{
					IncrementCardAccum( txnmsg );
					IncrementAccountAccum( txnmsg );
				}
				else if( crdinfo.limitflag == ACCOUNT_LIMIT_LOOKUP_FLAG )
					IncrementAccountAccum( txnmsg );
				else
					trace( DEBUG_NORMAL, "Invalid Card limit flag[%c]", crdinfo.limitflag );
			break;

			case DECREMENT_ACCUM:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				if( ( crdinfo.limitflag == CARD_LIMIT_FLAG ) || ( crdinfo.limitflag == CARDTYPE_LIMIT_FLAG ) )
					DecrementCardAccum( txnmsg );
				else if( ( crdinfo.limitflag == CARD_ACCT_LIMIT_FLAG ) || ( crdinfo.limitflag == CARDTYPE_ACCT_LIMIT_FLAG ) )
				{
					DecrementCardAccum( txnmsg );
					DecrementAccountAccum( txnmsg );
				}
				else if( crdinfo.limitflag == ACCOUNT_LIMIT_LOOKUP_FLAG )
					DecrementAccountAccum( txnmsg );
				else
					trace( DEBUG_NORMAL, "Invalid Card limit flag[%c]", crdinfo.limitflag );
			break;

			case HOTCARD_REQUEST:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				if( UpdateHotCardStatus( &crdinfo ) < 0 )
				{
					txnmsg->RespCode = EZLINK_RC_UnableToProcess;
					break;
				}
			break;

			case TELEPIN_RETRYEXIST_STATUS:
				if( !CARD_CHECK_FLAG )
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				if( UpdateTelePinRetryExist( &crdinfo ) < 0 )
				{
					txnmsg->RespCode = EZLINK_RC_UnableToProcess;
					break;
				}
			break;

			default:
				trace( DEBUG_NORMAL, "InValid AuthProperty[%d]", atoi( AuthToken ) );
			break;
		}
		if( AuthRespCode != txnmsg->RespCode  )
			break;
	}
	return 1;
}

int EzAuthMgr :: WriteOARFile( const char *oarpath, struct AccountList *acctlist, int NAccounts )
{
	FILE *oarfptr;
	oarfptr = fopen( oarpath, "w" );

	if( oarfptr == NULL )
		return -1;
	for( int i = 0; i < NAccounts; i++ )
	{
		trace( "BranchCode[%s]", ( acctlist + i )->IssBranchCode ) ;
		trace( "ActType[%s]", ( acctlist + i )->AccountType );
		trace("ProductCode[%s]",( acctlist + i )->ProductCode );
		trace( "ActNum[%s]", ( acctlist + i )->AccountNo );
		trace( "Desc[%s]", ( acctlist + i )->Description );
	}
	fprintf( oarfptr, "OAR_START_DEF\n");
	for( int i = 0; i < NAccounts; i++ )
		fprintf( oarfptr, "VAR_%d\t%s\t%s\t%s\t%s\t%s\n", i,( acctlist + i )->AccountNo, ( acctlist + i )->IssBranchCode,( acctlist + i )->AccountType,( acctlist + i )->ProductCode, ( acctlist + i )->Description );
	fprintf( oarfptr, "END_DEF\n");
	fclose( oarfptr );
	return 1;

}

void EzAuthMgr :: SendResponse( struct EzTxnMsg *txnmsg )
{
	trace( "Sending Response MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d] to Channel[%s]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->IssuerInst, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->Amount, txnmsg->RespCode, GetLastSenderChannelName() );
	if( WriteLastSenderChannel( ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Response to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Response to Channel[%s]", GetLastSenderChannelName() );
}

void EzAuthMgr :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgLen;

	while( 1 )
	{
		//dbutil.dbUtilClose();
		trace( "EzAuthMgr Waiting for Request....");
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * ) &txnmsg, &MsgLen ) < 0 )
		{
			trace( "Error in Reading Message from EzAuthMgr Channel" );
			continue;
		}

		trace( "Read Message MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.IssuerInst, txnmsg.m_chn, txnmsg.FromAccount, txnmsg.Amount, txnmsg.RespCode );
		//dbutil.dbUtilConnect();
		StartAuthorization( &txnmsg );
		txnmsg.MsgType += 10;

		SendResponse( &txnmsg );
	}
}

int main( int argc, char **argv )
{
	EzAuthMgr ezauthmgrobj;
	ezauthmgrobj.InitEzAuthMgr( argv[ 0 ] );
	ezauthmgrobj.ServiceRequest();
	return 1;
}

