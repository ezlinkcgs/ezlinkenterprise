#include <eztms/eztmslogger.h>

int EzTMSLogger :: initTMSLogger( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	//EzDBUtil dbutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztmslogger.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug( );

	trace( "^^^^^^^^^^^EzTMSLogger Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzTMSLogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzTMSLogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( TMSLOGGERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating [%s] Channel", TMSLOGGERCHANNEL );
		trace( "^^^^^^^^^^^EzTMSLogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initEzTMSLoggerODBC( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzTMSLogger Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void EzTMSLogger :: serviceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize, SqlErr, retval;
	struct EzTMSLoggerMsg tmsloggermsg;
	struct EzTerminalBatchInfo terminalbatchinfo_rec;
	int TxnCount;
	double TxnAmount;
	char *endptr, OpType[ 3 ];

	while( 1 )
	{
		trace( DEBUG_NORMAL,"POSDBMgr Waiting for Service Request...." );
		memset( &tmsloggermsg, 0, sizeof( struct EzTMSLoggerMsg ) );
		if( ReadMessage( ( char * )&tmsloggermsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}
		trace( DEBUG_NORMAL,"Received Request from channel[%s] With Size[%d] LogFlag[%x]", GetLastSenderChannelName(), MsgSize, tmsloggermsg.LogFlag );

		SqlErr = insertTerminalTxnLog( tmsloggermsg.MachineId, &tmsloggermsg.txnmsg );
		if( EZTMS_ORA_CONNECT_ERR( SqlErr ) )
		{
			if( ConnectDB() < 0 )
			{
				trace( "Error in Connecting with Switch Database...." );
				//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
			}
			else
			{
				SqlErr = insertTerminalTxnLog( tmsloggermsg.MachineId, &tmsloggermsg.txnmsg );
				if( SqlErr != 0 )
				{
					trace( DEBUG_ERROR, "Error in inserting EZTMSTXNLOG Table SqlErr[ %05d ]", SqlErr );
					//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
				}
			}
		}
		else if( SqlErr != 0 )
		{
			trace( DEBUG_ERROR, "Error in inserting EZTMSTXNLOG Table SqlErr[ %05d ]", SqlErr );
			//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
		}

		if( ( tmsloggermsg.LogFlag & 0x1 ) == 0x1 && tmsloggermsg.txnmsg.RespCode == 0 && ( ( tmsloggermsg.txnmsg.MsgType % 100 ) == 10 || ( tmsloggermsg.txnmsg.MsgType % 100 ) == 30 ) )
		{
			trace( DEBUG_NORMAL, "Inserting in to TerminalTxnLog Table...with NotificationId[%d] POSTxnRefNum[%s] POSId[%s]", tmsloggermsg.NotificationId, tmsloggermsg.TMSTxnRefNum, tmsloggermsg.MachineId );

			memset( OpType, 0, sizeof( OpType ) );
			if( tmsloggermsg.txnmsg.TxnCode / 10000 == 61 )
				strcpy( OpType, "CR" );
			else if( tmsloggermsg.txnmsg.TxnCode / 10000 == 62 )
				strcpy( OpType, "DR" );
			else if( tmsloggermsg.txnmsg.TxnCode / 10000 == 82 )
				strcpy( OpType, "DR" );
			else
				strcpy( OpType, "CR" );

			SqlErr = insertTerminalMaster( tmsloggermsg.MachineId, &tmsloggermsg.txnmsg, tmsloggermsg.TMSTxnRefNum, OpType );

			if( EZTMS_ORA_CONNECT_ERR( SqlErr ) )
			{
				if( ConnectDB() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					//insertPosTxnLogToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
				}
				else
				{
					SqlErr = insertTerminalMaster( tmsloggermsg.MachineId, &tmsloggermsg.txnmsg, tmsloggermsg.TMSTxnRefNum, OpType );
					if( SqlErr != 0 )
					{
						trace( DEBUG_ERROR, "Error in inserting EZTMSTXNLOG Table SqlErr[ %05d ]", SqlErr );
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

		if( ( tmsloggermsg.LogFlag & 0x2 ) == 0x2 )
		{
			trace( DEBUG_NORMAL, "Inserting in to TMSBatchTxnInfo Table...with NotificationId[%d] POSTxnRefNum[%s] POSId[%s]", tmsloggermsg.NotificationId, tmsloggermsg.TMSTxnRefNum, tmsloggermsg.MachineId );
			trace( DEBUG_NORMAL,"InstId[%s] PosId[%s] TermId[%s] MerchantId[%s] BatchId[%s] TxnRefNum[%s] MsgType[%d] TxnCode[%d] CHN[%s] TermLoc[%s] TraceNo[%d] AuthNum[%s] RefNum[%s] TranDate[%d] TranTime[%d] LocalDate[%d] LocalTime[%d] RespCode[%d] AuthCode[%d] CurrencyCode[%d] MCC[%d] TxnAmount[%s]", tmsloggermsg.txnmsg.AcquirerInst, tmsloggermsg.MachineId, tmsloggermsg.txnmsg.TerminalId, tmsloggermsg.txnmsg.AcceptorId, tmsloggermsg.txnmsg.BatchId, tmsloggermsg.TMSTxnRefNum, tmsloggermsg.txnmsg.MsgType, tmsloggermsg.txnmsg.TxnCode, tmsloggermsg.txnmsg.m_chn, tmsloggermsg.txnmsg.TerminalLocation, tmsloggermsg.txnmsg.TraceNo, tmsloggermsg.txnmsg.AuthNum, tmsloggermsg.txnmsg.RefNum, tmsloggermsg.txnmsg.TranDate, tmsloggermsg.txnmsg.TranTime, tmsloggermsg.txnmsg.LocalDate, tmsloggermsg.txnmsg.LocalTime, tmsloggermsg.txnmsg.RespCode, tmsloggermsg.txnmsg.AuthCode, tmsloggermsg.txnmsg.AcqCurrencyCode, tmsloggermsg.txnmsg.MerchantType, tmsloggermsg.txnmsg.Amount );
			/*char tempamt[20];
			memset(tempamt,0,sizeof(tempamt));
    			strcpy(tempamt,tmsloggermsg.txnmsg.Amount );
    			memset(tmsloggermsg.txnmsg.Amount,0,sizeof(tmsloggermsg.txnmsg.Amount));
    			strncpy(tmsloggermsg.txnmsg.Amount,tempamt,strlen(tempamt)-1);
			trace( DEBUG_NORMAL,"tmsloggermsg.txnmsg.Amount[%s]",tmsloggermsg.txnmsg.Amount );
			*/
			SqlErr = insertTerminalBatchTxnInfo( tmsloggermsg.MachineId, &tmsloggermsg.txnmsg, tmsloggermsg.TMSTxnRefNum );

			if( EZTMS_ORA_CONNECT_ERR( SqlErr ) )
			{
				if( ConnectDB() < 0 )
				{
					trace( "Error in Connecting with Switch Database...." );
					//insertPosBatchTxnInfoToFile( posdbmgrmsg.txnmsg, posdbmgrmsg.POSTxnRefNum );
				}
				else
				{

					SqlErr = insertTerminalBatchTxnInfo( tmsloggermsg.MachineId, &tmsloggermsg.txnmsg, tmsloggermsg.TMSTxnRefNum );
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

		if( ( tmsloggermsg.LogFlag & 0x4 ) == 0x4 )
		{
			trace( DEBUG_NORMAL, "Updating in to PosBatchInfo Table...with NotificationId[%d] POSTxnRefNum[%s] POSId[%s]", tmsloggermsg.NotificationId, tmsloggermsg.TMSTxnRefNum, tmsloggermsg.MachineId );

			memset( &terminalbatchinfo_rec, 0, sizeof( struct EzTerminalBatchInfo ) );
			SqlErr = readTerminalBatchInfo( tmsloggermsg.MachineId, &terminalbatchinfo_rec );
			if( SqlErr != 0 )
			{
				trace( "Error while reading POSBatchInfo..for POSId[%s]...SqlErr[%05d]", tmsloggermsg.MachineId, SqlErr );
				continue;
			}

			if( tmsloggermsg.txnmsg.TxnCode / 10000 == 61 && tmsloggermsg.txnmsg.MsgType == 210 && tmsloggermsg.txnmsg.RespCode == 0 )
			{
				TxnAmount = strtod( tmsloggermsg.txnmsg.Amount, &endptr ) + terminalbatchinfo_rec.SaleAmount;
				TxnCount =  terminalbatchinfo_rec.SaleCount + 1;

				SqlErr = updateSaleTxn( tmsloggermsg.MachineId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with SaleAmount[%0,2lf] SaleCount[%d]...SqlErr[%05d]", tmsloggermsg.MachineId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with SaleAmount[%0.2lf] SaleCount[%d]...", tmsloggermsg.MachineId, TxnAmount, TxnCount );
			}
			else if ( tmsloggermsg.txnmsg.TxnCode / 10000 == 61 && tmsloggermsg.txnmsg.MsgType == 420 )
			{
				TxnAmount = terminalbatchinfo_rec.SaleAmount - strtod( tmsloggermsg.txnmsg.Amount, &endptr );
				TxnCount =  terminalbatchinfo_rec.SaleCount - 1;
				SqlErr = updateSaleTxn( tmsloggermsg.MachineId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with SaleAmount[%0,2lf] SaleCount[%d]...SqlErr[%05d]", tmsloggermsg.MachineId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with SaleAmount[%0.2lf] SaleCount[%d]...", tmsloggermsg.MachineId, TxnAmount, TxnCount );
			}
			if( tmsloggermsg.txnmsg.TxnCode / 10000 == 62 && tmsloggermsg.txnmsg.MsgType == 210 && tmsloggermsg.txnmsg.RespCode == 0 )
			{
				TxnAmount = strtod( tmsloggermsg.txnmsg.Amount, &endptr ) + terminalbatchinfo_rec.VoidAmount;
				TxnCount =  terminalbatchinfo_rec.VoidCount + 1;
				SqlErr = updateVoidTxn( tmsloggermsg.MachineId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with VoidAmount[%0,2lf] VoidCount[%d]...SqlErr[%05d]", tmsloggermsg.MachineId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with VoidAmount[%0.2lf] VoidCount[%d]...", tmsloggermsg.MachineId, TxnAmount, TxnCount );
			}
			else if ( tmsloggermsg.txnmsg.TxnCode / 10000 == 62 && tmsloggermsg.txnmsg.MsgType == 420 )
			{
				TxnAmount = terminalbatchinfo_rec.VoidAmount - strtod( tmsloggermsg.txnmsg.Amount, &endptr );
				TxnCount =  terminalbatchinfo_rec.VoidCount - 1;
				SqlErr = updateVoidTxn( tmsloggermsg.MachineId, TxnAmount, TxnCount );
				if( SqlErr != 0 )
				{
					trace( "Error while updating POSBatchInfo..for POSId[%s] with VoidAmount[%0,2lf] VoidCount[%d]...SqlErr[%05d]", tmsloggermsg.MachineId, TxnAmount, TxnCount, SqlErr );
					continue;
				}
				trace( "Updated POSBatchInfo..for POSId[%s] with VoidAmount[%0.2lf] VoidCount[%d]...", tmsloggermsg.MachineId, TxnAmount, TxnCount );
			}

		}
	}
}

int main( int argc, char **argv )
{
	EzTMSLogger eztmsloggerobj;
	eztmsloggerobj.initTMSLogger( argv[ 0 ] );
	eztmsloggerobj.serviceRequest();
	return 1;
}



