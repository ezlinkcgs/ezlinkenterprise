#include <ezlink/ezatmmon.h>

int EzAtmMon :: initAtmMon( EzDebugUtil *dptr )
{
	this->dptr = dptr;
	return 1;

}

int EzAtmMon :: updateAtmMon( struct EzTxnMsg *txnmsg )
{
	char DateTime[ 13 ];
	char TxnDesc[ TXNDESC ];
	int retval ;

	memset( DateTime, 0, sizeof( DateTime ) );
	sprintf( DateTime, "%06d", txnmsg->TranDate );

	dbutil.DBConnect();

	if( GetAtmCount( txnmsg->TerminalId ) == 0 )
	{
		retval = InsertEzmonAtminfo( DateTime, txnmsg->TerminalId );
		if( retval < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error while Inserting EZMON_ATMINFO table for withdrawal OraErr...[%d] ", retval );
			return -1;
		}
	}

	if( txnmsg->MsgType == EZLINK_TXN_TxnResponse )
	{
		if( TXNCODE( txnmsg->TxnCode ) == WITHDRAWAL )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "WITHDRAWAL " );
				retval = UpdateWithdrawal( DateTime, TxnDesc,txnmsg->TerminalId, TxnDesc, txnmsg->RespCode );
				if( retval < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for withdrawal OraErr...[%d] ",retval );
			}

			if( TXNCODE( txnmsg->TxnCode ) == BALANCEINQ )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "BALANCE INQUIRY" );
				retval = UpdateBalance( DateTime, txnmsg->TerminalId, txnmsg->RespCode, TxnDesc );
				if ( retval < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for BalanceEnquiry OraErr...[%d] ", retval );

			}

			if( TXNCODE( txnmsg->TxnCode ) == MINISTATEMENT )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "MINI-STATEMENT" );
				retval = UpdateMinistmt( DateTime, txnmsg->TerminalId, txnmsg->RespCode, TxnDesc );
				if( retval < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for Ministatement OraErr...[%d] ", retval );
			}

			if( TXNCODE( txnmsg->TxnCode ) == FUNDTRANSFER )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "FUND TRANSFER" );
				retval = UpdateFndtrn( DateTime, txnmsg->TerminalId, txnmsg->RespCode, TxnDesc );
				if( retval  < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for FundTransfer OraErr...[%d] ", retval );

			}

			if( TXNCODE( txnmsg->TxnCode ) == PINCHANGE )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "PINCHANGE" );
				retval = UpdatePinchange( DateTime, txnmsg->TerminalId, txnmsg->RespCode, TxnDesc );
				if( retval < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for Pinchange OraErr...[%d] ", retval );
			}

			if( TXNCODE( txnmsg->TxnCode ) == STATEMENTREQ )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "STATEMENT REQUEST" );
				retval = UpdatePinchange( DateTime, txnmsg->TerminalId, txnmsg->RespCode, TxnDesc );
				if( retval < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for StatementRequest OraErr...[%d] ", retval );
			}

			if( TXNCODE ( txnmsg->TxnCode ) == CHEQUEBOOKREQ )
			{
				memset( TxnDesc, 0, sizeof( TxnDesc ) );
				sprintf( TxnDesc, "%s  %s", txnmsg->chn, "CHEQUE BOOK REQUEST" );
				retval = UpdatePinchange( DateTime, txnmsg->TerminalId, txnmsg->RespCode, TxnDesc );
				if( retval < 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for ChequebookReq OraErr...[%d] ", retval );

			}

			else if( txnmsg->MsgType == EZLINK_TXN_ReversalAdviceRequest )
			{
				retval = UpdateReversal( DateTime, txnmsg->RespCode,txnmsg->chn, txnmsg->TerminalId );
				if( retval != 0 )
					dptr->trace( DEBUG_ERROR, "Error while Updating EZMON_ATMINFO table for ReversalReq OraErr...[%d] ", retval );

			}
	}
}
