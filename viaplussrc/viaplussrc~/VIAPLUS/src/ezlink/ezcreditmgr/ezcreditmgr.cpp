#include <ezlink/ezcreditmgr.h>
#include <ezutils/ezdbutil.h>

EzCreditMgr :: EzCreditMgr()
{
}

EzCreditMgr :: ~EzCreditMgr()
{
}

void EzCreditMgr :: InitEzCreditMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzDBUtil dbutil;
	EzCfgUtil cfgutil;
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezcreditmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );
	
	SetDebug();
	
	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzCreditMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
    	trace( "^^^^^^^^^^^EzCreditMgr Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
	}

	if( CreateChannel( "EzCreditMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzCreditMgr" );
    	trace( "^^^^^^^^^^^EzCreditMgr Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
    }
	
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );
	
	if( dbutil.DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with database " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzCreditMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	InitEzCreditUtil( this );
	
	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzSecurityUtil" );
	    trace( DEBUG_CRITICAL,"^^^^^^^^^^^EzCreditMgr Ended Abnormally^^^^^^^^^^^^^");
	    closeDebug();
	    TaskExit();
    }
	
	TaskInit();
	initEzSigUtil( this );
}
int EzCreditMgr :: StartAuthorization( struct EzTxnMsg *txnmsg )
{
	struct EzCreditProperty creditproperty;
	int NAuth;
	bool CARD_CHECK_FLAG = false;
	
	char AuthToken[ 100 ] , DeviceType[ 11 ];
	struct EzCardInfo crdinfo;
	struct EzInstProfile instprof;
	char TempPinOffSet[ 11 ];
	
	trace( DEBUG_TXN, " Starting Credit Authorization\n");
	
	trace( DEBUG_TXN, " Reading INST Profile ");
	memset( &instprof, 0, sizeof( struct EzInstProfile ) );
	if( ReadEzInstProfile( txnmsg->IssuerInst, &instprof  ) < 0 )
	{
		trace( DEBUG_ERROR, " Error in Reading Inst Profile  From EzInstProfile TABLE\n");
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	trace( DEBUG_NORMAL, "INSTID[%s] SETL_CURRENCY_CODE[%s] INSTNAME[%s] MAXCOUNT[%d]", instprof.instid, instprof.setl_currency_code, instprof.instname, instprof.maxcount );
	txnmsg->SettCurrencyCode = atoi( instprof.setl_currency_code );
	
	trace( DEBUG_TXN, " Reading Credit Property ");
	memset( &creditproperty, 0, sizeof( struct EzCreditProperty ) );
	if( ReadCreditProperty( txnmsg, &creditproperty ) < 0 )
	{
		trace( DEBUG_ERROR, " Error in Reading CreditProperty From EzCreditProperty TABLE\n");
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	trace( DEBUG_NORMAL, "creditproperty.AuthList[%s]", creditproperty.AuthList );
	
	NAuth = GetNAuth( creditproperty.AuthList );

	for( int i = 0; i < NAuth; i++ )
	{
		memset( AuthToken, 0, sizeof( AuthToken ) );
		
		GetToken( creditproperty.AuthList, AuthToken, i + 1 );		
		if( CheckNumeric( AuthToken ) < 0 )
			continue;
		
		trace( DEBUG_TXN, "AuthToken[%s]", AuthToken );
		
		switch ( atoi( AuthToken ) )
		{
			case CARD_CHECK:
				trace( DEBUG_TXN, "CHECKING THE CARDINFO FOR THE CARD NUMBER [%s]",txnmsg->chn  );
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
				trace( DEBUG_TXN, "CHECKING THE CARD STATUS FOR THE CARD NUMBER [%s]",txnmsg->chn  );
				ReadStatusMap( txnmsg , crdinfo.status );
			break;

			case CARDEXPIRY_DB_CHECK: 
				if( !CARD_CHECK_FLAG )	
				{
					memset( &crdinfo, 0, sizeof( struct EzCardInfo ) );	
					if( ReadCardInfo( txnmsg, &crdinfo ) < 0 )
						break;
					CARD_CHECK_FLAG = true;
				}
				trace( DEBUG_TXN, "CHECKING THE DB EXPIRY DATE FOR THE CARD NUMBER [%s]",txnmsg->chn  );
				if( CheckDBExpiryDate( crdinfo.expirydate ) < 0 )
				{
					trace( DEBUG_TXN, "CARD NUMBER [%s] IS EXPIRED CARD",txnmsg->chn  );
					txnmsg->RespCode = EZLINK_RC_ExpiredCard;
					break;
				}
			break;

			case CARDEXPIRY_TRACK_CHECK:
				trace( DEBUG_TXN, "CHECKING THE TRACK EXPIRY DATE FOR THE CARD NUMBER [%s]",txnmsg->chn  );
				if( CheckTrackExpiryDate( txnmsg->Track2 ) < 0 )
				{
					trace( DEBUG_TXN, "CARD NUMBER [%s] IS EXPIRED CARD",txnmsg->chn  );
					txnmsg->RespCode = EZLINK_RC_ExpiredCard;
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
				trace( DEBUG_TXN, "CHECKING THE TRANSACTION TYPE[%d] ALLOWED FOR THE CARD NUMBER [%s]", txnmsg->TxnCode, txnmsg->chn  );
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
				trace( DEBUG_TXN, "CHECKING THE PIN FOR THE CARD NUMBER [%s]", txnmsg->chn  );
				
				/*Check for Device Request or Network Request*/
				trace( DEBUG_TEST, "SecurityId[%s]", txnmsg->SecurityId );
				if( VerifyDevicePIN( txnmsg->SrcPort, txnmsg->SecurityId, txnmsg->chn, txnmsg->PINBlock, crdinfo.pinoffset ) < 0  )
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
						trace( DEBUG_TXN, "CHECKING THE CARD BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->chn  );
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
						
						trace( DEBUG_TXN, "CHECKING THE CARD TYPE BASED LIMIT FOR THE CARD NUMBER [%s]", txnmsg->chn  );
						CheckCardTypeLimit( txnmsg, crdinfo.cardtype );
						break;
					default:
						trace( DEBUG_TXN, "Invaild Limit Type" );
					    break; 
				}
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
				memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
				if( GenDevicePinOffset( txnmsg->SrcPort, txnmsg->SecurityId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
					PINChangeFailed( txnmsg, &crdinfo ); 
				else
					NewPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
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
				memset( TempPinOffSet, 0, sizeof( TempPinOffSet ) );
				if( GenDevicePinOffset( txnmsg->SrcPort, txnmsg->SecurityId, txnmsg->chn, txnmsg->NewPINBlock, TempPinOffSet ) < 0 )
					PINChangeFailed( txnmsg, &crdinfo ); 
				else
					ConfirmPINChangeSucced( txnmsg, TempPinOffSet, &crdinfo );
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
				else
					trace( DEBUG_NORMAL, "Invalid Card limit flag[%c]", crdinfo.limitflag );
			break;
			
			default:
				trace( DEBUG_NORMAL, "InValied CreditProperty[%d]", atoi( AuthToken ) );
			break;
		}
		if( txnmsg->RespCode != EZLINK_RC_Approved )
			break;
	}
	return 1;
}

void EzCreditMgr :: SendResponse( struct EzTxnMsg *txnmsg )
{
	trace( "Sending Response MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Account[%s] Amount[%s] RespCode[%d] to Channel[%s]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->IssuerInst, txnmsg->chn, txnmsg->FromAccount, txnmsg->Amount, txnmsg->RespCode, GetLastSenderChannelName() );
	if( WriteLastSenderChannel( ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( "Error in Writing Response to Channel[%s]", GetLastSenderChannelName() );
	else
		trace( "Written Response to Channel[%s]", GetLastSenderChannelName() );
}

void EzCreditMgr :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgLen;

	while( 1 )
	{
		trace( "EzCreditMgr Waiting for Request....");
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * ) &txnmsg, &MsgLen ) < 0 )
		{
			trace( "Error in Reading Message from EzCreditMgr Channel" );
			continue;
		}

		trace( "Read Message MsgType[%d] TxnCode[%d] InstId[%s] CHN[%s] Amount[%s] RespCode[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.IssuerInst, txnmsg.chn, txnmsg.Amount, txnmsg.RespCode );
		
		StartAuthorization( &txnmsg );
		txnmsg.MsgType += 10;
		
		SendResponse( &txnmsg );
	}
}

int main( int argc, char **argv )
{
	EzCreditMgr ezcreditmgrobj;
	ezcreditmgrobj.InitEzCreditMgr( argv[ 0 ] );
	ezcreditmgrobj.ServiceRequest();
	return 1;
}

