#include <ezmms/ezmmsserverutil.h>

int EzMMSServerUtil :: initMMSServerUtil( EzDebugUtil *dptr, int MaxAccounts, EzInstProfileUtil *ezinstprofileutil_ptr, EzDBUtil *dbutil_ptr, EzPadssUtil *padssutil_ptr )
{
	this->dptr = dptr;
	this->MaxAccts = MaxAccounts;
	this->ezinstprofileutil_ptr = ezinstprofileutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->padssutil_ptr = padssutil_ptr;
	return 1;
}

void EzMMSServerUtil :: getExpDate( const char *Track2Data, char *ExpData )
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

void EzMMSServerUtil :: getServiceCode( const char *Track2Data, char *ServiceCode )
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

void EzMMSServerUtil :: getCVV( const char *Track2Data, char *CVV )
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

int EzMMSServerUtil :: readMerchantProfileTable( struct EzTxnMsg *txnmsg, struct EzMMSMerchantProfile *merchantprofile_rec )
{
	int retval = 0;
	retval = readEzMMSMerchantProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, merchantprofile_rec );

	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSMerchantProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, merchantprofile_rec );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] MERCHANTID[%s] FROM EZMMSMERCHANTPROFILE ORAERR[%05d]>",  txnmsg->ProcessInst, txnmsg->AcceptorId, retval );
		txnmsg->RespCode = EZLINK_RC_InvalidMerchant;
		txnmsg->ReasonCode = EZLINK_Reason_MerchantProfileRead_Err;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] MERCHANTID[%s] FROM EZMMSMERCHANTPROFILE>",  merchantprofile_rec->InstId, merchantprofile_rec->MerchantId );
	return 1;
}

int EzMMSServerUtil :: readStoreProfileTable( struct EzTxnMsg *txnmsg, struct EzMMSStoreProfile *storeprofile_rec )
{
	int retval = 0;
	retval = readEzMMSStoreProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->StoreId, storeprofile_rec );

	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSStoreProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->StoreId, storeprofile_rec );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] MERCHANTID[%s] STOREID[%s] FROM EZMMSSTOREPROFILE ORAERR[%05d]>",  txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->StoreId, retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] MERCHANTID[%s] STOREID[%s] FROM EZMMSSTOREPROFILE>",  txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->StoreId );
	return 1;
}

int EzMMSServerUtil :: readTerminalProfileTable( struct EzTxnMsg *txnmsg, struct EzMMSTerminalProfile *terminalprofile_rec )
{
	int retval = 0;
	retval = readEzMMSTerminalProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId, terminalprofile_rec );

	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSTerminalProfile( txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId, terminalprofile_rec );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] MERCHANTID[%s] TERMINALID[%s] FROM EZMMSTERMINALPROFILE ORAERR[%05d]>",  txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId, retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] MERCHANTID[%s] TERMINALID[%s] FROM EZMMSTERMINALPROFILE>",  txnmsg->ProcessInst, txnmsg->AcceptorId, txnmsg->TerminalId );
	return 1;
}

int EzMMSServerUtil :: readMerchantRelationTable( struct EzTxnMsg *txnmsg, struct EzMMSAccountProfile *acctlist )
{
	int retval = 0, SqlErr;
	retval = readEzMMSMerchantRelation( txnmsg->ProcessInst, txnmsg->AcceptorId, acctlist, &SqlErr );

	if( retval < 0 )
	{
		if( MMS_ORA_CONNECT_ERR( SqlErr ) )
		{
			if( dbutil_ptr->DBConnect() < 0 )
			{
				dptr->trace( "Error in Connecting with Switch DataBase..." );
				txnmsg->RespCode = EZLINK_RC_UnableToProcess;
				txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
				return -1;
			}
			retval = readEzMMSMerchantRelation( txnmsg->ProcessInst, txnmsg->AcceptorId, acctlist, &SqlErr );
		}
	}
	if( retval < 0 )
	{
		dptr->trace( "<ERROR WHILE READING ACCOUNTS FOR INSTID[%s] MERCHANTID[%s] FROM EZMMSMERCHANTRELATION ORAERR[%05d]>",  txnmsg->ProcessInst, txnmsg->AcceptorId, SqlErr );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	if( retval == 0 )
	{
		dptr->trace( "<NO ACCOUNTS LINKED FOR INSTID[%s] MERCHANTID[%s]>",  txnmsg->ProcessInst, txnmsg->AcceptorId );
		txnmsg->RespCode = EZLINK_RC_InvalidAccount;
		return -1;
	}
	return retval;
}

int EzMMSServerUtil :: readAccountInfo( struct EzTxnMsg *txnmsg, const char *AccountNo, struct EzMMSAccountProfile *acctprofile_ptr )
{
	int retval = 0;
	retval = readEzMMSAccountInfo( txnmsg->ProcessInst, txnmsg->AcceptorId, AccountNo, acctprofile_ptr );

	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSAccountInfo( txnmsg->ProcessInst, txnmsg->AcceptorId, AccountNo, acctprofile_ptr );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] MERCHANTID[%s] ACCOUNTNO[%s] FROM EZMMSACCOUNTINFO ORAERR[%05d]>",  txnmsg->ProcessInst, txnmsg->AcceptorId, AccountNo, retval );
		txnmsg->RespCode = EZLINK_RC_InvalidAccount;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] MERCHANTID[%s] ACCOUNTNO[%s] FROM EZMMSACCOUNTINFO>",  txnmsg->ProcessInst, txnmsg->AcceptorId, AccountNo );
	return 1;
}

int EzMMSServerUtil :: readFeeInfoTable( struct EzTxnMsg *txnmsg, const char *FeeCode, struct EzMMSFeeInfo *feeinfo_ptr )
{
	int retval = 0;
	retval = readEzMMSFeeInfo( txnmsg->ProcessInst, FeeCode, feeinfo_ptr );

	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSFeeInfo( txnmsg->ProcessInst, FeeCode, feeinfo_ptr );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] FEECODE[%s] FROM EZMMSFEEINFO ORAERR[%05d]>",  txnmsg->ProcessInst, FeeCode, retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] FEECODE[%s] FROM EZMMSFEEINFO>",  txnmsg->ProcessInst, FeeCode );
	return 1;
}

int EzMMSServerUtil :: readCommissionInfoTable( struct EzTxnMsg *txnmsg, const char *CommissionCode, struct EzMMSCommissionInfo *comissioninfo_ptr )
{
	int retval = 0;
	retval = readEzMMSCommissionInfo( txnmsg->ProcessInst, CommissionCode, comissioninfo_ptr );

	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSCommissionInfo( txnmsg->ProcessInst, CommissionCode, comissioninfo_ptr );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] COMISSIONCODE[%s] FROM EZMMSCOMISSIONINFO ORAERR[%05d]>",  txnmsg->ProcessInst, CommissionCode, retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] COMISSIONCODE[%s] FROM EZMMSCOMISSIONINFO>",  txnmsg->ProcessInst, CommissionCode );
	return 1;
}

int EzMMSServerUtil :: getCurrencyRate( struct EzTxnMsg *txnmsg, int CurrencyCode, struct EzMMSCurrencyRate *curr_rate )
{
	int retval = 0;
	retval = readEzMMSCurrencyRate( txnmsg->ProcessInst, CurrencyCode, curr_rate );
	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = readEzMMSCurrencyRate( txnmsg->ProcessInst, CurrencyCode, curr_rate );
	}
	if( retval != 0 )
	{
		dptr->trace( "<READ FAILED FOR INSTID[%s] CURRCODE[%d] FROM EZMMSCURRENCYRATE ORAERR[%05d]>",  txnmsg->ProcessInst, CurrencyCode, retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<READ SUCCESS FOR INSTID[%s] CURRCODE[%d] FROM EZMMSCURRENCYRATE>",  txnmsg->ProcessInst, CurrencyCode );
	return 1;
}

void EzMMSServerUtil :: insertTransactionToFile( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{

}

int EzMMSServerUtil :: insertTransaction( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{
	int retval = 0;
	retval = insertMMSTransactionInfo( txnmsg, txninfo_ptr );
	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = insertMMSTransactionInfo( txnmsg, txninfo_ptr );
	}
	if( retval != 0 )
	{
		dptr->trace( "<INSERT FAILED IN EZMMS_TRANSACTION ORAERR[%05d]>",  retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<INSERT SUCCESS IN EZMMS_TRANSACTION>" );
	insertTransactionToFile( txnmsg, txninfo_ptr );
	return 1;
}

int EzMMSServerUtil :: insertTermTxn( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{
	int retval = 0;
	retval = insertMMSTermBatchTxn( txnmsg, txninfo_ptr );
	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = insertMMSTermBatchTxn( txnmsg, txninfo_ptr );
	}
	if( retval != 0 )
	{
		dptr->trace( "<INSERT FAILED IN EZMMS_TERM_BATCH_TXN ORAERR[%05d]>",  retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<INSERT SUCCESS IN EZMMS_TERM_BATCH_TXN>" );
	return 1;
}

int EzMMSServerUtil :: updateMerchantBalance( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{
	int retval = 0;
	retval = updateMMSMerchantBalance( txnmsg, txninfo_ptr );
	if( MMS_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutil_ptr->DBConnect() < 0 )
		{
			dptr->trace( "Error in Connecting with Switch DataBase..." );
			txnmsg->RespCode = EZLINK_RC_UnableToProcess;
			txnmsg->ReasonCode = EZLINK_Reason_DBConnect_Err;
			return -1;
		}
		retval = updateMMSMerchantBalance( txnmsg, txninfo_ptr );
	}
	if( retval != 0 )
	{
		dptr->trace( "<MERCHANT BALANCE UPDATE FAILED FOR INSTID<%s> MERCHANTID<%s> ACCOUNT<%s> ORAERR[%05d]>",  txnmsg->ProcessInst, txnmsg->AcceptorId, txninfo_ptr->AccountNo, retval );
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
		return -1;
	}
	dptr->trace( "<MERCHANT BALANCE UPDATE SUCCESS FOR INSTID<%s> MERCHANTID<%s> ACCOUNT<%s>>",  txnmsg->ProcessInst, txnmsg->AcceptorId, txninfo_ptr->AccountNo );
	return 1;
}

int EzMMSServerUtil :: updateMerchantLoyaltyPoints( const char *LoyaltyPoints )
{
	return 1;
}

int EzMMSServerUtil :: updateMerchantTxnDateTime( int TranDate, int TranTime )
{
	return 1;
}

int EzMMSServerUtil :: readFromAccount( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: readToAccount( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: readAllAccounts( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: readAccountProfile( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: checkAvailableBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}
int EzMMSServerUtil :: checkLedgerBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: updateAvailableBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: updateLedgerBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: incrementAvailableBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: decrementAvailableBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: incrementLedgerBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: decrementLedgerBalance( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: readCardProfile( struct EzTxnMsg *txnmsg, struct EzMMSCardProfile *cardprofile_rec )
{
	return 1;
}

int EzMMSServerUtil :: readStatusMap( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: checkTrackExpiry( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: checkDBExpiry( struct EzTxnMsg *txnmsg )
{
	return 1;
}

int EzMMSServerUtil :: InvalidPIN( struct EzTxnMsg *txnmsg, struct EzMMSCardProfile *cardprofile_rec )
{
	return 1;
}

int EzMMSServerUtil :: GoodPIN( struct EzTxnMsg *txnmsg, struct EzMMSCardProfile *cardprofile_rec )
{
	return 1;
}

int EzMMSServerUtil :: PINChangeFailed( struct EzTxnMsg *txnmsg, struct EzMMSCardProfile *cardprofile_rec )
{
	return 1;
}

int EzMMSServerUtil :: NewPINChangeSucced( struct EzTxnMsg *txnmsg, const char *TempPinOffSet, struct EzMMSCardProfile *cardprofile_rec )
{
	return 1;
}

int EzMMSServerUtil :: ConfirmPINChangeSucced( struct EzTxnMsg *txnmsg, const char *TempPinOffSet, struct EzMMSCardProfile *cardprofile_rec )
{
	return 1;
}
