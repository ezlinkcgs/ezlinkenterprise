#include<ezbusiness/ezposdbmgr.h>

int EzPOSDBMgr :: initPOSDBMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezposdbmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug( );

	trace( "^^^^^^^^^^^EzPOSDBMgr Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzPOSDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzPOSDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( POSDBMGRCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating [%s] Channel", POSDBMGRCHANNEL );
		trace( "^^^^^^^^^^^EzPOSDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzPOSDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database...." );
		trace( "^^^^^^^^^^^EzPOSDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

void EzPOSDBMgr :: serviceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize, SqlErr, retval;
	struct EzPOSDBMgrMsg posdbmgrmsg;
	struct EzPOSBatchInfo posbatchinfo_rec;
	int TxnCount;
	double TxnAmount;
	char *endptr;

	while( 1 )
	{
		trace( DEBUG_NORMAL,"POSDBMgr Waiting for Service Request...." );
		memset( &posdbmgrmsg, 0, sizeof( struct EzPOSDBMgrMsg ) );
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( ReadMessage( ( char * )&posdbmgrmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}
		trace( DEBUG_NORMAL,"Received Request from channel[%s] With Size[%d] LogFlag[%x]", GetLastSenderChannelName(), MsgSize, posdbmgrmsg.LogFlag );

		if( ( posdbmgrmsg.LogFlag & 0x1 ) == 0x1 )
		{
			trace( DEBUG_NORMAL, "Inserting in to PosTxnLog Table...with NotificationId[%d] POSTxnRefNum[%s] POSId[%s]", posdbmgrmsg.NotificationId, posdbmgrmsg.POSTxnRefNum, posdbmgrmsg.POSId );

			SqlErr = insertPosTxnLog( posdbmgrmsg.POSId, &posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );

			if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
			{
				if( dbutil.DBConnect() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
				}
				else
				{
					SqlErr = insertPosTxnLog( posdbmgrmsg.POSId, &posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
					if( SqlErr != 0 )
					{
						trace( DEBUG_ERROR, "Error in inserting EZPOSTXNLOG Table SqlErr[ %05d ]", SqlErr );
						//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
					}
				}
			}
			else if( SqlErr != 0 )
			{
				trace( DEBUG_ERROR, "Error in inserting EZPOSTXNLOG Table SqlErr[ %05d ]", SqlErr );
				//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
			}
		}

		if( ( posdbmgrmsg.LogFlag & 0x2 ) == 0x2 )
		{
			trace( DEBUG_NORMAL, "Inserting in to PosBatchTxnInfo Table...with NotificationId[%d] POSTxnRefNum[%s] POSId[%s]", posdbmgrmsg.NotificationId, posdbmgrmsg.POSTxnRefNum, posdbmgrmsg.POSId );
			trace( "InstId[%s] PosId[%s] TermId[%s] MerchantId[%s] BatchId[%s] TxnRefNum[%s] MsgType[%d] TxnCode[%d] CHN[%s] TermLoc[%s] TraceNo[%d] AuthNum[%s] RefNum[%s] TranDate[%d] TranTime[%d] LocalDate[%d] LocalTime[%d] RespCode[%d] AuthCode[%d] CurrencyCode[%d] MCC[%d] TxnAmount[%s]", posdbmgrmsg.txnmsg.AcquirerInst, posdbmgrmsg.POSId, posdbmgrmsg.txnmsg.TerminalId, posdbmgrmsg.txnmsg.AcceptorId, posdbmgrmsg.txnmsg.BatchId, posdbmgrmsg.POSTxnRefNum, posdbmgrmsg.txnmsg.MsgType, posdbmgrmsg.txnmsg.TxnCode, posdbmgrmsg.txnmsg.m_chn, posdbmgrmsg.txnmsg.TerminalLocation, posdbmgrmsg.txnmsg.TraceNo, posdbmgrmsg.txnmsg.AuthNum, posdbmgrmsg.txnmsg.RefNum, posdbmgrmsg.txnmsg.TranDate, posdbmgrmsg.txnmsg.TranTime, posdbmgrmsg.txnmsg.LocalDate, posdbmgrmsg.txnmsg.LocalTime, posdbmgrmsg.txnmsg.RespCode, posdbmgrmsg.txnmsg.AuthCode, posdbmgrmsg.txnmsg.AcqCurrencyCode, posdbmgrmsg.txnmsg.MerchantType, posdbmgrmsg.txnmsg.Amount );

			SqlErr = insertPosBatchTxnInfo( posdbmgrmsg.POSId, &posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );

			if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
			{
				if( dbutil.DBConnect() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					//insertPosBatchTxnInfoToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
				}
				else
				{

					SqlErr = insertPosBatchTxnInfo( posdbmgrmsg.POSId, &posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
					if( SqlErr != 0 )
					{
						trace( DEBUG_ERROR, "Error in inserting EZPOSBATCHTXNINFO Table SqlErr[ %05d ]", SqlErr );
						//insertPosBatchTxnInfoToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
					}
				}
			}
			else if( SqlErr != 0 )
			{
				trace( DEBUG_ERROR, "Error in inserting EZPOSBATCHTXNINFO Table SqlErr[ %05d ]", SqlErr );
				//insertPosBatchTxnInfoToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
			}

		}

		if( ( posdbmgrmsg.LogFlag & 0x4 ) == 0x4 )
		{
			trace( DEBUG_NORMAL, "Updating in to PosBatchInfo Table...with NotificationId[%d] POSTxnRefNum[%s] POSId[%s]", posdbmgrmsg.NotificationId, posdbmgrmsg.POSTxnRefNum, posdbmgrmsg.POSId );

			memset( &posbatchinfo_rec, 0, sizeof( struct EzPOSBatchInfo ) );
			SqlErr = readPOSBatchInfo( posdbmgrmsg.POSId, &posbatchinfo_rec );
			if( SqlErr != 0 )
			{
				trace( "Error while reading POSBatchInfo..for POSId[%s]...SqlErr[%05d]", posdbmgrmsg.POSId, SqlErr );
				continue;
			}

			if( posdbmgrmsg.txnmsg.TxnCode / 10000 == 61 && posdbmgrmsg.txnmsg.MsgType == 210 && posdbmgrmsg.txnmsg.RespCode == 0 )
			{
				TxnAmount = strtod( posdbmgrmsg.txnmsg.Amount, &endptr ) + posbatchinfo_rec.SaleAmount;
				TxnCount =  posbatchinfo_rec.SaleCount + 1;

				SqlErr = updateSaleTxn( posdbmgrmsg.POSId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with SaleAmount[%0,2lf] SaleCount[%d]...SqlErr[%05d]", posdbmgrmsg.POSId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with SaleAmount[%0.2lf] SaleCount[%d]...", posdbmgrmsg.POSId, TxnAmount, TxnCount );
			}
			else if ( posdbmgrmsg.txnmsg.TxnCode / 10000 == 61 && posdbmgrmsg.txnmsg.MsgType == 420 )
			{
				TxnAmount = posbatchinfo_rec.SaleAmount - strtod( posdbmgrmsg.txnmsg.Amount, &endptr );
				TxnCount =  posbatchinfo_rec.SaleCount - 1;
				SqlErr = updateSaleTxn( posdbmgrmsg.POSId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with SaleAmount[%0,2lf] SaleCount[%d]...SqlErr[%05d]", posdbmgrmsg.POSId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with SaleAmount[%0.2lf] SaleCount[%d]...", posdbmgrmsg.POSId, TxnAmount, TxnCount );
			}
			if( posdbmgrmsg.txnmsg.TxnCode / 10000 == 62 && posdbmgrmsg.txnmsg.MsgType == 210 && posdbmgrmsg.txnmsg.RespCode == 0 )
			{
				TxnAmount = strtod( posdbmgrmsg.txnmsg.Amount, &endptr ) + posbatchinfo_rec.VoidAmount;
				TxnCount =  posbatchinfo_rec.VoidCount + 1;
				SqlErr = updateVoidTxn( posdbmgrmsg.POSId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with VoidAmount[%0,2lf] VoidCount[%d]...SqlErr[%05d]", posdbmgrmsg.POSId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with VoidAmount[%0.2lf] VoidCount[%d]...", posdbmgrmsg.POSId, TxnAmount, TxnCount );
			}
			else if ( posdbmgrmsg.txnmsg.TxnCode / 10000 == 62 && posdbmgrmsg.txnmsg.MsgType == 420 )
			{
				TxnAmount = posbatchinfo_rec.VoidAmount - strtod( posdbmgrmsg.txnmsg.Amount, &endptr );
				TxnCount =  posbatchinfo_rec.VoidCount - 1;
				SqlErr = updateVoidTxn( posdbmgrmsg.POSId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with VoidAmount[%0,2lf] VoidCount[%d]...SqlErr[%05d]", posdbmgrmsg.POSId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with VoidAmount[%0.2lf] VoidCount[%d]...", posdbmgrmsg.POSId, TxnAmount, TxnCount );
			}

		}
	}
}

int main( int argc, char **argv )
{
	EzPOSDBMgr ezposdbmgrobj;
	ezposdbmgrobj.initPOSDBMgr( argv[ 0 ] );
	ezposdbmgrobj.serviceRequest();
	return 1;
}
