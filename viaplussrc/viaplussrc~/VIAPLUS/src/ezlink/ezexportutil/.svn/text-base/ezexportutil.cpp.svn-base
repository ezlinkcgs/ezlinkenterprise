#include <ezlink/ezexportutil.h>

EzExportUtil :: EzExportUtil()
{
}

EzExportUtil :: ~EzExportUtil()
{
}

int EzExportUtil :: initExportUtil()
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezexportutil.log" );

	if( openDebug( logpath, "ezexport" ) < 0 )
	{
		printf("\n Error in Opening Debug File[%s]", logpath );
		return -1;
	}

	TxnLogExportId = CreateMemoryId( this, "TXNLOGEXPORT" );
	if( TxnLogExportId < 0 )
	{
		printf( "\nError in Creating Memory[%s]", "TXNLOGEXPORT" );
		return -1;
	}
	TxnLogExportSemid = semget( TxnLogExportId, 1, IPC_CREAT | 0666 );
	if( TxnLogExportSemid < 0 )
	{
		printf( "\nError in Creating TxnLogExport Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	SafDBExportId = CreateMemoryId( this, "SAFDBEXPORT" );
	if( SafDBExportId < 0 )
	{
		printf( "\nError in Creating Memory[%s]", "SAFDBEXPORT" );
		return -1;
	}
	SafDBExportSemid = semget( SafDBExportId, 1, IPC_CREAT | 0666 );
	if( SafDBExportSemid < 0 )
	{
		printf( "\nError in Creating SafDBExport Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	if( dbutil.initDBUtil( "ezexport", this ) )
	{
		printf("\n Error in Initializing DBUtil...." );
		return -1;
	}
	return 1;
}

int EzExportUtil :: LockTxnLogFile()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 0;
	if( semop( TxnLogExportSemid, &sem_buf, 1 ) < 0 )
	{
		printf( "\n Error in doing semop operation for TxnLogExport Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	sem_buf.sem_op = 2;
	if( semop( TxnLogExportSemid, &sem_buf, 1 ) < 0 )
	{
		printf( "\n Error in doing semop operation for TxnLogExport Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzExportUtil :: UnLockTxnLogFile()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;
	if( semop( TxnLogExportSemid, &sem_buf, 1 ) < 0 )
	{
		printf( "\n Error in doing semop operation for TxnLogExport Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzExportUtil :: LockSafDBFile()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 0;
	if( semop( SafDBExportSemid, &sem_buf, 1 ) < 0 )
	{
		printf( "\n Error in doing semop operation for SafDBExport Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	sem_buf.sem_op = 2;
	if( semop( SafDBExportSemid, &sem_buf, 1 ) < 0 )
	{
		printf( "\n Error in doing semop operation for SafDBExport Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzExportUtil :: UnLockSafDBFile()
{
	struct sembuf sem_buf;
	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;
	if( semop( SafDBExportSemid, &sem_buf, 1 ) < 0 )
	{
		printf( "\n Error in doing semop operation for SafDBExport Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

void EzExportUtil :: getField( const char *RecordBuffer, char *FieldStr, int FieldCount )
{
	for( int i = 0, j = 0, cnt = 0; i < strlen( RecordBuffer ); i++ )
	{
		if( RecordBuffer[ i ] == 0x1c &&  RecordBuffer[ i + 1 ] == 0x1d )
			cnt++;
		else if ( cnt == FieldCount )
			break;
		else if ( cnt + 1 == FieldCount )
		{
			FieldStr[ j ] = RecordBuffer[ i ];
			j++;
		}
	}
}

int EzExportUtil :: exportTxnLog( const char *FileName )
{
	struct EzTxnMsg txnmsg;
	FILE *fp;
	int FieldCount = 0, retval;
	char RecordBuffer[ RECORDBUFFER_SIZE + 1 ], FieldStr[ FIELDSTR_SIZE + 1 ], TxnRefNum[ 255 ];

	fp = fopen( FileName, "r" );
	if( fp == NULL )
	{
		printf("\n Error in Reading File[%s]", FileName );
		return -1;
	}

	retval = dbutil.DBConnect();
	if( retval != 0 )
	{
		printf("\n Error in Connecting with Switch Database....." );
		return -1;
	}

	while( !feof( fp ) )
	{
		memset( RecordBuffer, 0, sizeof( RecordBuffer ) );
		fgets( RecordBuffer, sizeof( RecordBuffer ), fp );
		if( strlen( RecordBuffer ) < 50 )
			continue;

		FieldCount = 0;

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

		//TxnRefNum
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
		strcpy( TxnRefNum, FieldStr );
		FieldCount++;

		//MsgType
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.MsgType = atoi( FieldStr );
		FieldCount++;

		//OrgMsgType
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.OrgMsgType = atoi( FieldStr );
		FieldCount++;

		//TxnCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TxnCode = atoi( FieldStr );
		FieldCount++;

		//TerminalId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TerminalId, FieldStr );
		FieldCount++;

		//TerminalLocation
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TerminalLocation, FieldStr );
		FieldCount++;

		//TraceNo
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TraceNo = atoi( FieldStr );
		FieldCount++;

		//TranDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TranDate = atoi( FieldStr );
		FieldCount++;

		//TranTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TranTime = atoi( FieldStr );
		FieldCount++;

		//OrgTranDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.OrgTranDate = atoi( FieldStr );
		FieldCount++;

		//OrgTranTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.OrgTranTime = atoi( FieldStr );
		FieldCount++;

		//LocalDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.LocalDate = atoi( FieldStr );
		FieldCount++;

		//LocalTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.LocalTime = atoi( FieldStr );
		FieldCount++;

		//RespCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.RespCode = atoi( FieldStr );
		FieldCount++;

		//RespCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.RespCode = atoi( FieldStr );
		FieldCount++;

		//RevCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.RevCode = atoi( FieldStr );
		FieldCount++;

		//ReasonCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.ReasonCode = atoi( FieldStr );
		FieldCount++;

		//AuthCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AuthCode = atoi( FieldStr );
		FieldCount++;

		//CaptureDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.CaptureDate = atoi( FieldStr );
		FieldCount++;

		//CaptureTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.CaptureTime = atoi( FieldStr );
		FieldCount++;

		//SettlementDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettlementDate = atoi( FieldStr );
		FieldCount++;

		//AcqCurrencyCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AcqCurrencyCode = atoi( FieldStr );
		FieldCount++;

		//AcqConvRate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AcqConvRate = atoi( FieldStr );
		FieldCount++;

		//AcqConvDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AcqConvDate = atoi( FieldStr );
		FieldCount++;

		//IssCurrencyCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.IssCurrencyCode = atoi( FieldStr );
		FieldCount++;

		//IssConvRate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.IssConvRate = atoi( FieldStr );
		FieldCount++;

		//IssConvDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.IssConvDate = atoi( FieldStr );
		FieldCount++;

		//SettCurrencyCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettCurrencyCode = atoi( FieldStr );
		FieldCount++;

		//SettConvRate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettConvRate = atoi( FieldStr );
		FieldCount++;

		//SettConvDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettConvDate = atoi( FieldStr );
		FieldCount++;

		//Merchant Type
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.MerchantType = atoi( FieldStr );
		FieldCount++;

		//POS Entry Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosEntryCode = atoi( FieldStr );
		FieldCount++;

		//POS Condition Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosConditionCode = atoi( FieldStr );
		FieldCount++;

		//POS CapCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosCapCode = atoi( FieldStr );
		FieldCount++;

		//POS PinCapCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosPinCapCode = FieldStr[ 0 ];
		FieldCount++;

		//AcqBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcqBranchCode, FieldStr );
		FieldCount++;

		//IssBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.IssBranchCode, FieldStr );
		FieldCount++;

		//TxfBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxfBranchCode, FieldStr );
		FieldCount++;

		//ForwardBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ForwardBranchCode, FieldStr );
		FieldCount++;

		//From Product Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.FromAcctSubType, FieldStr );
		FieldCount++;

		//To Product Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ToAcctSubType, FieldStr );
		FieldCount++;

		//Available Balance
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AvailBalance, FieldStr );
		FieldCount++;

		//Ledger Balance
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.LedgerBalance, FieldStr );
		FieldCount++;

		//Amount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.Amount, FieldStr );
		FieldCount++;

		//TxnFee
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxnFee, FieldStr );
		FieldCount++;

		//DispAmount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.DispAmount, FieldStr );
		FieldCount++;

		//FromAccount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.FromAccount, FieldStr );
		FieldCount++;

		//ToAccount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ToAccount, FieldStr );
		FieldCount++;

		//RefNum
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RefNum, FieldStr );
		FieldCount++;

		//AuthNum
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AuthNum, FieldStr );
		FieldCount++;

		//AcceptorName
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcceptorName, FieldStr );
		FieldCount++;

		//AcqInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcquirerInst, FieldStr );
		FieldCount++;

		//IssuerInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.IssuerInst, FieldStr );
		FieldCount++;

		//ForwardInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ForwardInst, FieldStr );
		FieldCount++;

		//TxfInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxfInst, FieldStr );
		FieldCount++;

		//Settlement Inst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.SettInst, FieldStr );
		FieldCount++;

		//NetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.NetworkId, FieldStr );
		FieldCount++;

		//AcqNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcqNetworkId, FieldStr );
		FieldCount++;

		//IssuerNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.IssuerNetworkId, FieldStr );
		FieldCount++;

		//FwdNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.FwdNetworkId, FieldStr );
		FieldCount++;

		//TxfNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxfNetworkId, FieldStr );
		FieldCount++;

		//SettNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.SettNetworkId, FieldStr );
		FieldCount++;

		//Track2
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.Track2, FieldStr );
		FieldCount++;

		//RsvFld1
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld1, FieldStr );
		FieldCount++;

		//RsvFld2
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld2, FieldStr );
		FieldCount++;

		//RsvFld3
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld3, FieldStr );
		FieldCount++;


		//RsvFld4
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld4, FieldStr );
		FieldCount++;

		//RsvFld5
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld5, FieldStr );
		FieldCount++;

		//RsvFld6
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld6, FieldStr );
		FieldCount++;

		//OrgChannel
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.OrgChannel, FieldStr );
		FieldCount++;

		//OrgPort
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.OrgPort, FieldStr );
		FieldCount++;

		retval = selectEzTxnLog( TxnRefNum );
		if( retval != 0 )
		{
			retval = insertEzTxnLog( &txnmsg, TxnRefNum );
			if( retval != 0 )
			{
				printf( "Error in Inserting Record[%s] in TxnLog Table....SqlErr[%05d]", TxnRefNum, retval );

			}
		}
		else
			printf( "Error in Inserting Record[%s] in TxnLog Table. Record Already Exists", TxnRefNum );
	}
	dbutil.DBClose();
	return 1;
}

int EzExportUtil :: exportSafDB( const char *FileName )
{
	struct EzTxnMsg txnmsg;
	FILE *fp, *fp_err;
	int FieldCount = 0, retval;
	char RecordBuffer[ RECORDBUFFER_SIZE + 1 ], FieldStr[ FIELDSTR_SIZE + 1 ], TxnRefNum[ 255 ], SafRecordNo[ 21 ], SafIndicator, SafStatus, ErrFileName[ 200 ];
	bool ErrorFileOpenFlag = false;
	fp = fopen( FileName, "r" );
	if( fp == NULL )
	{
		printf("\n Error in Reading File[%s]", FileName );
		return -1;
	}

	retval = dbutil.DBConnect();
	if( retval != 0 )
	{
		printf("\n Error in Connecting with Switch Database....." );
		return -1;
	}

	while( !feof( fp ) )
	{
		memset( RecordBuffer, 0, sizeof( RecordBuffer ) );
		fgets( RecordBuffer, sizeof( RecordBuffer ), fp );
		if( strlen( RecordBuffer ) < 50 )
			continue;

		FieldCount = 0;

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

		//SafRecordNo
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
		strcpy( SafRecordNo, FieldStr );
		FieldCount++;

		//NetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.NetworkId, FieldStr );
		FieldCount++;

		//SafStatus
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		SafStatus = FieldStr[ 0 ];
		FieldCount++;

		//SafIndicator
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		SafIndicator = FieldStr[ 0 ];
		FieldCount++;

		//TxnRefNum
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
		strcpy( TxnRefNum, FieldStr );
		FieldCount++;

		//MsgType
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.MsgType = atoi( FieldStr );
		FieldCount++;

		//OrgMsgType
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.OrgMsgType = atoi( FieldStr );
		FieldCount++;

		//TxnCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TxnCode = atoi( FieldStr );
		FieldCount++;

		//TerminalId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TerminalId, FieldStr );
		FieldCount++;

		//TerminalLocation
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TerminalLocation, FieldStr );
		FieldCount++;

		//TraceNo
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TraceNo = atoi( FieldStr );
		FieldCount++;

		//TranDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TranDate = atoi( FieldStr );
		FieldCount++;

		//TranTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.TranTime = atoi( FieldStr );
		FieldCount++;

		//OrgTranDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.OrgTranDate = atoi( FieldStr );
		FieldCount++;

		//OrgTranTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.OrgTranTime = atoi( FieldStr );
		FieldCount++;

		//LocalDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.LocalDate = atoi( FieldStr );
		FieldCount++;

		//LocalTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.LocalTime = atoi( FieldStr );
		FieldCount++;

		//RespCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.RespCode = atoi( FieldStr );
		FieldCount++;

		//RespCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.RespCode = atoi( FieldStr );
		FieldCount++;

		//RevCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.RevCode = atoi( FieldStr );
		FieldCount++;

		//ReasonCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.ReasonCode = atoi( FieldStr );
		FieldCount++;

		//AuthCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AuthCode = atoi( FieldStr );
		FieldCount++;

		//CaptureDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.CaptureDate = atoi( FieldStr );
		FieldCount++;

		//CaptureTime
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.CaptureTime = atoi( FieldStr );
		FieldCount++;

		//SettlementDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettlementDate = atoi( FieldStr );
		FieldCount++;

		//AcqCurrencyCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AcqCurrencyCode = atoi( FieldStr );
		FieldCount++;

		//AcqConvRate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AcqConvRate = atoi( FieldStr );
		FieldCount++;

		//AcqConvDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.AcqConvDate = atoi( FieldStr );
		FieldCount++;

		//IssCurrencyCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.IssCurrencyCode = atoi( FieldStr );
		FieldCount++;

		//IssConvRate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.IssConvRate = atoi( FieldStr );
		FieldCount++;

		//IssConvDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.IssConvDate = atoi( FieldStr );
		FieldCount++;

		//SettCurrencyCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettCurrencyCode = atoi( FieldStr );
		FieldCount++;

		//SettConvRate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettConvRate = atoi( FieldStr );
		FieldCount++;

		//SettConvDate
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.SettConvDate = atoi( FieldStr );
		FieldCount++;

		//Merchant Type
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.MerchantType = atoi( FieldStr );
		FieldCount++;

		//POS Entry Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosEntryCode = atoi( FieldStr );
		FieldCount++;

		//POS Condition Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosConditionCode = atoi( FieldStr );
		FieldCount++;

		//POS CapCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosCapCode = atoi( FieldStr );
		FieldCount++;

		//POS PinCapCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		txnmsg.PosPinCapCode = FieldStr[ 0 ];
		FieldCount++;

		//AcqBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcqBranchCode, FieldStr );
		FieldCount++;

		//IssBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.IssBranchCode, FieldStr );
		FieldCount++;

		//TxfBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxfBranchCode, FieldStr );
		FieldCount++;

		//ForwardBranchCode
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ForwardBranchCode, FieldStr );
		FieldCount++;

		//From Product Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.FromAcctSubType, FieldStr );
		FieldCount++;

		//To Product Code
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ToAcctSubType, FieldStr );
		FieldCount++;

		//Available Balance
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AvailBalance, FieldStr );
		FieldCount++;

		//Ledger Balance
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.LedgerBalance, FieldStr );
		FieldCount++;

		//Amount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.Amount, FieldStr );
		FieldCount++;

		//TxnFee
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxnFee, FieldStr );
		FieldCount++;

		//DispAmount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.DispAmount, FieldStr );
		FieldCount++;

		//FromAccount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.FromAccount, FieldStr );
		FieldCount++;

		//ToAccount
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ToAccount, FieldStr );
		FieldCount++;

		//RefNum
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RefNum, FieldStr );
		FieldCount++;

		//AuthNum
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AuthNum, FieldStr );
		FieldCount++;

		//AcceptorName
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcceptorName, FieldStr );
		FieldCount++;

		//AcqInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcquirerInst, FieldStr );
		FieldCount++;

		//IssuerInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.IssuerInst, FieldStr );
		FieldCount++;

		//ForwardInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.ForwardInst, FieldStr );
		FieldCount++;

		//TxfInst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxfInst, FieldStr );
		FieldCount++;

		//Settlement Inst
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.SettInst, FieldStr );
		FieldCount++;

		//NetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.NetworkId, FieldStr );
		FieldCount++;

		//AcqNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.AcqNetworkId, FieldStr );
		FieldCount++;

		//IssuerNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.IssuerNetworkId, FieldStr );
		FieldCount++;

		//FwdNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.FwdNetworkId, FieldStr );
		FieldCount++;

		//TxfNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.TxfNetworkId, FieldStr );
		FieldCount++;

		//SettNetworkId
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.SettNetworkId, FieldStr );
		FieldCount++;

		//Track2
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.Track2, FieldStr );
		FieldCount++;

		//RsvFld1
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld1, FieldStr );
		FieldCount++;

		//RsvFld2
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld2, FieldStr );
		FieldCount++;

		//RsvFld3
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld3, FieldStr );
		FieldCount++;


		//RsvFld4
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld4, FieldStr );
		FieldCount++;

		//RsvFld5
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld5, FieldStr );
		FieldCount++;

		//RsvFld6
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.RsvFld6, FieldStr );
		FieldCount++;

		//OrgChannel
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.OrgChannel, FieldStr );
		FieldCount++;

		//OrgPort
		memset( FieldStr, 0, sizeof( FieldStr ) );
		getField( RecordBuffer, FieldStr, FieldCount + 1 );
		strcpy( txnmsg.OrgPort, FieldStr );
		FieldCount++;

		retval = selectEzSafDB( TxnRefNum );

		if( retval == 1403 )
		{
			retval = insertSafRecord( SafRecordNo, txnmsg.NetworkId, TxnRefNum, &txnmsg, SafIndicator, SafStatus );
			if( retval != 0 )
			{
				printf( "Error in Inserting Record[%s] in EzSafDB Table....SqlErr[%05d]", TxnRefNum, retval );
				if( !ErrorFileOpenFlag )
				{
					memset( ErrFileName, 0, sizeof( ErrFileName ) );
					sprintf( ErrFileName, "%s.err", FileName );
					fp_err = fopen( ErrFileName, "w" );
					if( fp_err == NULL )
						printf("\nError in Opening File[%s]...\n", ErrFileName );
					else
						ErrorFileOpenFlag = true;
				}
				if( ErrorFileOpenFlag )
					fprintf( fp_err, "%s", RecordBuffer );
			}
		}
		else
			printf( "Error in Inserting Record[%s] in EzSafDB Table. Record Already Exists", TxnRefNum );
	}
	if( ErrorFileOpenFlag )
		fclose( fp_err );
	fclose( fp );
	dbutil.DBClose();
	return 1;
}

int EzExportUtil :: getTxnLogExportSeqNo()
{

}

int EzExportUtil :: getSafDBExportSeqNo()
{

}

bool EzExportUtil :: FileExists( const char *FilePath )
{
	FILE *fp;
	fp = fopen( FilePath, "r" );
	if( fp == NULL )
		return false;
	else
	{
		fclose( fp );
		return true;
	}
}

int EzExportUtil :: startExporting( const char *TableName, const char *FileName )
{
	char FilePath[ 200 ], ExportFilePath[ 200 ], CommandStr[ 512 ];
	FILE *CommandPtr;

	if( !strcasecmp( TableName, "TXNLOG" ) )
	{
		memset( FilePath, 0, sizeof( FilePath ) );
		sprintf( FilePath, "%s/%s/%s/%s.TXNLOG", getenv( "EZDIR_HOME" ), "inf", "txnlog", FileName );
		printf( "\nExporting File[%s] into EzTxnLog Table.....\n",  FilePath );
		if( !FileExists( FilePath ) )
		{
			printf("\nFile[%s] does not exists....", FilePath );
			return -1;
		}
		if( LockTxnLogFile() < 0 )
			return -1;

		memset( ExportFilePath, 0, sizeof( ExportFilePath ) );
		sprintf( ExportFilePath, "%s/%s/%s/%s/%s/%s_%06d_%06d_%02d.exp", getenv( "EZDIR_HOME" ), "inf", "txnlog", "export", FileName, ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime(), getTxnLogExportSeqNo() );

		memset( CommandStr, 0, sizeof( CommandStr ) );
		sprintf( CommandStr, "cp %s %s", FilePath, ExportFilePath );

		CommandPtr = popen( CommandStr, "r" );
		if( CommandPtr == NULL )
		{
			printf("\n Error in popen for Command[%s]...SysErr[%s] ErrNo[%d]\n", CommandStr, strerror( errno ), errno );
			return -1;
		}

		pclose( CommandPtr );

		memset( CommandStr, 0, sizeof( CommandStr ) );
		sprintf( CommandStr, "> %s", FilePath );

		CommandPtr = popen( CommandStr, "r" );
		if( CommandPtr == NULL )
		{
			printf("\n Error in popen for Command[%s]...SysErr[%s] ErrNo[%d]\n", CommandStr, strerror( errno ), errno );
			return -1;
		}
		pclose( CommandPtr );

		if( UnLockTxnLogFile() < 0 )
			return -1;

		exportTxnLog( ExportFilePath );
	}
	else if ( !strcasecmp( TableName, "SAFDB" ) )
	{
		memset( FilePath, 0, sizeof( FilePath ) );
		sprintf( FilePath, "%s/%s/%s/%s.TXNLOG", getenv( "EZDIR_HOME" ), "inf", "safdb", FileName );
		printf( "\nExporting File[%s] into EzTxnLog Table.....\n",  FilePath );
		if( !FileExists( FilePath ) )
		{
			printf("\nFile[%s] does not exists....", FilePath );
			return -1;
		}
		if( LockSafDBFile() < 0 )
			return -1;

		memset( ExportFilePath, 0, sizeof( ExportFilePath ) );
		sprintf( ExportFilePath, "%s/%s/%s/%s/%s/%s_%06d_%06d_%02d.exp", getenv( "EZDIR_HOME" ), "inf", "safdb", "export", FileName, ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime(), getSafDBExportSeqNo() );

		memset( CommandStr, 0, sizeof( CommandStr ) );
		sprintf( CommandStr, "cp %s %s", FilePath, ExportFilePath );

		CommandPtr = popen( CommandStr, "r" );
		if( CommandPtr == NULL )
		{
			printf("\n Error in popen for Command[%s]...SysErr[%s] ErrNo[%d]\n", CommandStr, strerror( errno ), errno );
			return -1;
		}

		pclose( CommandPtr );

		memset( CommandStr, 0, sizeof( CommandStr ) );
		sprintf( CommandStr, "> %s", FilePath );

		CommandPtr = popen( CommandStr, "r" );
		if( CommandPtr == NULL )
		{
			printf("\n Error in popen for Command[%s]...SysErr[%s] ErrNo[%d]\n", CommandStr, strerror( errno ), errno );
			return -1;
		}
		pclose( CommandPtr );

		if( UnLockSafDBFile() < 0 )
			return -1;

		exportSafDB( ExportFilePath );
	}
	else
	{
		printf("\n InValid TableName[%s] to Export.....\n", TableName );
		return -1;
	}
	return 1;
}

int main( int argc, char **argv )
{
	if( argc != 3 )
	{
		printf( "Usage <export> <TxnLog/SafDB> <FileName>\n" );
		return 1;
	}
	EzExportUtil exportutil;
	exportutil.startExporting( argv[ 1 ], argv[ 2 ] );
	return 1;
}






