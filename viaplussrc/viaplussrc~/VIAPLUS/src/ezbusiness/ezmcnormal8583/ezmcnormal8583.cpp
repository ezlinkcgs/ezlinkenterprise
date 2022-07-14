#include <ezbusiness/ezmcnormal8583.h>

EzMcNormal8583 :: EzMcNormal8583()
{
}

EzMcNormal8583 :: ~EzMcNormal8583()
{
}

void EzMcNormal8583 :: InitEzMcNormal8583( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", TaskName );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzMcNormal8583 Started Running^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzMcNormal8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzMcNormal8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", TaskName );
		trace( "^^^^^^^^^^^EzMcNormal8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", "EzMcNormal8583BitMap.cfg" );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzMcNormal8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	initFmtUtil( this );

	TaskInit();
	initEzSigUtil( this );
}

int EzMcNormal8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ];
	unsigned char BitMap[ 33 ];
	int len, date = 0;
	char *month, *day, *year;
	BufOffset = OutBuf;
	char ComTempDate[ 7 ],TempAmount[13],TempDate[ 7 ],TempBuf[ 16 ],CheckDate[ 5 ], temp[ 50 ],temptxn[7];
	char TempLocalDate[ 7 ];
	int Amount, ExtRespCode, ExtNetCode, ExtMsgType;


	ExtMsgType = getOutBoundExtMsgType( txnmsg->MsgType );
	trace( "Switch MsgType [%d] --> Ext MsgType [%d]", txnmsg->MsgType, ExtMsgType );
	OutBuf += fmt_out( OutBuf, &ExtMsgType, ITOA, 4, 0 );

	//trace( "MsgType = [%d]", txnmsg->MsgType );
	//OutBuf += fmt_out( OutBuf, &txnmsg->MsgType, ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

	/*OutBuf += fmt_out( OutBuf, BitMap, HTOA, 16, 1 );
	if( IsBitSet( BitMap, 1 ) )
		OutBuf += fmt_out( OutBuf, BitMap + 8, HTOA, 16, 1 );*/

	if( strlen( txnmsg->FromAccount ) == 0 )
		SetBitOff( BitMap, 102 );

	memcpy( OutBuf, BitMap, 8 );
	OutBuf += 8;

	if( IsBitSet( BitMap, 1 ) )
	{
		memcpy( OutBuf, BitMap + 8, 8 );
		OutBuf += 8;
	}
	//hex_dump( (unsigned char *)BitMap, 16 );


	for( int bitno = 1; bitno <= 128; bitno++ )
	{
		if( !IsBitSet( BitMap, bitno ) )
			continue;

		if( bitno > 64 )
		{
			if( !IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( bitno )
		{

			case 1:
			// Seconday Bit Map
			break;

			case 2://Primary Account Number (PAN)
				len = strlen( txnmsg->chn );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				format_str( 6, len - 4, '*' );
				OutBuf += fmt_out( OutBuf, txnmsg->chn, CHAR, len, bitno );
				break ;

			case 3://Processing Code
				memset( temp, 0, sizeof( temp ) );
				memset( temptxn, 0, sizeof( temptxn ) );
				if( txnmsg->TxnCode/10000 == 30 )
				{
					sprintf( temp, "%06d", txnmsg->TxnCode );
					strcpy( temptxn, "31" );
					strcat( temptxn, temp + 2 );
					trace( "temptxn[%s]",temptxn);
				}
				else
					sprintf( temptxn, "%06d", txnmsg->TxnCode );
				OutBuf += fmt_out( OutBuf, temptxn, CHAR, 6, bitno );
				break ;

			case 4://Transaction Amount
				memset( TempAmount, 0, sizeof( TempAmount ) );
				if( strlen( txnmsg->Amount ) <= 0 )
					strncpy( TempAmount, "000000000000", 12 );
				else
				{
					if( ( txnmsg->TxnCode/10000 ) == 1 )
						Amount = atoi( txnmsg->Amount ) * 100;
					else
					{
						memset( TempAmount, 0, sizeof( TempAmount ) );
						for( int i = 0, j = 0; i <= strlen( txnmsg->Amount ); i++ )
						{
							if( txnmsg->Amount[i] != '.' )
							{
								TempAmount[j] = txnmsg->Amount[i];
								j++;
							}
						}
						Amount = atoi( TempAmount );
					}
					sprintf( TempAmount, "%012d", Amount );
				}

				OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
				break ;


			case 5://Settlement Amount
				memset( TempAmount, 0, sizeof( TempAmount ) );
				if( strlen( txnmsg->SettAmount ) <= 0 )
					strncpy( TempAmount, "000000000000", 12 );
				else
				{
					if( ( txnmsg->TxnCode/10000 ) == 1 )
						Amount = atoi( txnmsg->SettAmount ) * 100;
					else
					{
						memset( TempAmount, 0, sizeof( TempAmount ) );
						for( int i = 0, j = 0; i <= strlen( txnmsg->SettAmount ); i++ )
						{
							if( txnmsg->Amount[i] != '.' )
							{
								TempAmount[j] = txnmsg->SettAmount[i];
								j++;
							}
						}
						Amount = atoi( TempAmount );
					}
					sprintf( TempAmount, "%012d", Amount );
				}

				OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
				break ;

			case 7://Transmission Date and Time
				//format need to be changed as MMDDhhmmss
				/*if( txnmsg->MsgType == 200 ||  txnmsg->MsgType == 420 ||  txnmsg->MsgType == 800 )
				{
					date  = getSysDate( );
					month = getSysMon( );
					trace("month[%s]", month );
					memset( ComTempDate, 0, sizeof( ComTempDate ) );
					sprintf( ComTempDate, "%s%02d", month, date );
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else
				{*/
					memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempLocalDate, "%06d", txnmsg->TranDate );
					strncpy( CheckDate, &TempLocalDate[2], 2 );
					strncat( CheckDate, TempLocalDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				//}
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );
				break ;

			case 8://Billing fee amount
				//reserved to use for online fee
				break ;

			case 11://Systems Trace Audit Number
				if( txnmsg->TraceNo == 0 )
					txnmsg->TraceNo = txnmsg->TraceNo + 1;

				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
				break ;

			case 12://Local Transaction Time - hhmmss
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, LTOA, 6, bitno );
				break;

			case 13://Local Transaction Date -- MMDD
				/*if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 )
				{
					date  = getSysDate( );
					month = getSysMon( );
					trace("month[%s]", month );
					memset( ComTempDate, 0, sizeof( ComTempDate ) );
					sprintf( ComTempDate, "%s%02d", month, date );
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else
				{*/
					memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempLocalDate, "%06d", txnmsg->LocalDate );
					strncpy( CheckDate, &TempLocalDate[2], 2 );
					strncat( CheckDate, TempLocalDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				//}
				break ;

			case 14://Expiration Date -- YYMM
				OutBuf += fmt_out( OutBuf, &txnmsg->ExpiryDate, LTOA, 4, bitno );
				break ;

			case 15://Settlement Date -- MMDD
				memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
				memset( CheckDate, 0, sizeof( CheckDate ) );
				sprintf( TempLocalDate, "%06d", txnmsg->SettlementDate );
				strncpy( CheckDate, &TempLocalDate[2], 2 );
				strncat( CheckDate, TempLocalDate, 2 );

				OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				break ;

			case 17://Capture Date -- MMDD
				/*if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 )
				{
					date  = getSysDate( );
					month = getSysMon( );
					trace("month[%s]", month );
					memset( ComTempDate, 0, sizeof( ComTempDate ) );
					sprintf( ComTempDate, "%s%02d", month, date );
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else
				{*/
					char TempLocalDate[ 7 ];
					memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempLocalDate, "%06d", txnmsg->CaptureDate );
					strncpy( CheckDate, &TempLocalDate[2], 2 );
					strncat( CheckDate, TempLocalDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				//}
				break ;

			case 18://Merchant’s Type (MCC)
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 22://Point of Service Entry Mode
				txnmsg->PosEntryCode = 901;
				OutBuf += fmt_out( OutBuf, &txnmsg->PosEntryCode, STOA, 3, bitno );
				/*Positions 1 and 2 PAN Entry Mode
				00 Unspecified
				01 Manual
				02 Magnetic Stripe
				03 Bar Code
				04 OCR
				05 ICC
				61 Contact less Magnetic Stripe.
				90 Magnetic stripe read - Content of Track II included.
				Position 3 PIN Entry Capability
				0 Unspecified
				1 PIN Entry Capability
				2 No Pin Entry Capability*/
				break;

			case 23://Card Sequence Number
				//Used for EMV transactions only.
				break;

			case 32://Acquiring Institution Identification Code
				len = strlen( txnmsg->AcquirerBin );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcquirerBin, CHAR, len, bitno );
				break ;

			case 33://Forwarding Institution Identification Code
				len = strlen( txnmsg->ForwardBin );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ForwardBin, CHAR, len, bitno );
				break ;

			case 35://Track 2 Data
				if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 )
				{
					char TempTrack[ 64 ];
					memset( TempTrack, 0, sizeof( TempTrack ) );
					strncpy( TempTrack, txnmsg->Track2 + 1, strlen( txnmsg->Track2 ) - 2 );
					len = strlen( TempTrack );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					format_str( 0, len, '*' );
					OutBuf += fmt_out( OutBuf, TempTrack, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->Track2 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					format_str( 0, len, '*' );
					OutBuf += fmt_out( OutBuf, txnmsg->Track2, CHAR, len, bitno );
				}
				break ;

			case 37://Retrieval Reference Number
				/*change format as YDDDHHNNNNNN*/
				OutBuf += fmt_out( OutBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 38://Authorization Identification Response
				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
				break ;

			case 39://Response Code
				if( txnmsg->MsgType == 210 || txnmsg->MsgType == 430 )
				{
					ExtRespCode = getOutBoundExtRespCode( txnmsg->RespCode );
					trace("SwitchRespCode[%d] --> ExtRespCode[%d] ", txnmsg->RespCode, ExtRespCode );
				}
				else
				{
					ExtRespCode = getOutBoundExtRespCode( txnmsg->RespCode );
					trace("SwitchRespCode[%d] --> ExtRespCode[%d] ", txnmsg->RespCode, ExtRespCode );
				}
				OutBuf += fmt_out( OutBuf, &ExtRespCode, ITOA, 2, bitno );
				break;

			case 41://Card Acceptor Terminal Identification
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 42:////Card Acceptor Identification Code
				if( ExtMsgType == 200 || ExtMsgType == 420 )
					OutBuf += fmt_out( OutBuf, txnmsg->AcquirerInst, CHAR, 15, bitno );
				else
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld6, CHAR, 15, bitno );
				break ;

			case 43://Card Acceptor Name/Location
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 48://Additional Data DKE
				break;

			case 49://Transaction Currency Code
				OutBuf += fmt_out( OutBuf, &txnmsg->AcqCurrencyCode, ITOA, 3, bitno );
				break;

			case 50://Settlement Currency Code
				OutBuf += fmt_out( OutBuf, &txnmsg->SettCurrencyCode, ITOA, 3, bitno );
				break;

			case 52://Personal Identification Number (PIN) Data
				format_str( 0, 16, '*' );
				OutBuf += fmt_out( OutBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break;

			case 54://Additional Amounts
				char TempBal[ 13 ];
				char TotalBal[ 30 ];
				char TempTxn[ 7 ];
				int Bal;

				memset( TempBal, 0, sizeof( TempBal ) );
				memset( TotalBal, 0, sizeof( TotalBal ) );
				memset( TempTxn, 0, sizeof( TempTxn ) );

				sprintf( TempTxn, "%06d", txnmsg->TxnCode );
				strncpy( TotalBal, TempTxn + 2, 2 );
				strncat( TotalBal, "02", 2 );
				strncat( TotalBal, "356", 3 );
				strncat( TotalBal, "C", 1 );

				memset( TempBal, 0, sizeof( TempBal ) );

				if( atoi( txnmsg->AvailBalance ) <= 0 )
					Bal = 0;
				else
				{
					for( int i = 0,j = 0; i < strlen( txnmsg->AvailBalance ); i++ )
					{
						if( txnmsg->AvailBalance[ i ] != '.' )
						{
							TempBal[ j ] = txnmsg->AvailBalance[ i ];
							j++;
						}
					}
					Bal = atoi( TempBal );
					trace("AvailBal[%d]", Bal );
				}

				memset( TempBal, 0, sizeof( TempBal ) );
				sprintf( TempBal, "%012d", Bal );
				strcat( TotalBal, TempBal );

				memset( TempBal, 0, sizeof( TempBal ) );
				memset( TempTxn, 0, sizeof( TempTxn ) );

				sprintf( TempTxn, "%06d", txnmsg->TxnCode );
				strncat( TotalBal, TempTxn + 2, 2 );
				strncat( TotalBal, "01", 2 );
				strncat( TotalBal, "356", 3 );
				strncat( TotalBal, "C", 1 );

				memset( TempBal, 0, sizeof( TempBal ) );

				if( atoi( txnmsg->LedgerBalance ) <= 0 )
					Bal = 0;
				else
				{
					for( int i = 0,j = 0; i < strlen( txnmsg->LedgerBalance ); i++ )
					{
						if( txnmsg->LedgerBalance[ i ] != '.' )
						{
							TempBal[ j ] = txnmsg->LedgerBalance[ i ];
							j++;
						}
					}
					Bal = atoi( TempBal );
					trace("LedgerBal[%d]", Bal );
				}

				memset( TempBal, 0, sizeof( TempBal ) );
				sprintf( TempBal, "%012d", Bal );
				strcat( TotalBal, TempBal );

				len = strlen( TotalBal );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, TotalBal, CHAR, len, bitno );
				break;

			case 55://EMV Tag data
				break;

			case 57://EMV System related data
				break;

			case 70://Network Management Information Code
				ExtNetCode = getOutBoundExtNetCode( txnmsg->NetCode );
				trace( "Switch NetCode [%d] --> ExtNetCode[%03d]", txnmsg->NetCode, ExtNetCode );
				OutBuf += fmt_out( OutBuf, &ExtNetCode, ITOA, 3, bitno );
				break ;

			case 90://Original Data Elements
				if( txnmsg->MsgType == 430 )
				{
					len = strlen( txnmsg->RsvFld2 );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				}
				else
				{
					OutBuf += fmt_out( OutBuf, &txnmsg->OrgMsgType, ITOA, 4, bitno );
					OutBuf += fmt_out( OutBuf, &txnmsg->OrgTraceNo, LTOA, 6, bitno );
					//OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranDate, LTOA, 4, bitno );

					memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempLocalDate, "%06d", txnmsg->OrgTranDate );
					strncpy( CheckDate, &TempLocalDate[2], 2 );
					strncat( CheckDate, TempLocalDate, 2 );

					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
					OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranTime, LTOA, 6, bitno );
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%011s", txnmsg->AcquirerBin );
					OutBuf += fmt_out( OutBuf, temp,  CHAR, 11, bitno );
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%011s", txnmsg->ForwardBin );
					OutBuf += fmt_out( OutBuf, temp,  CHAR, 11, bitno );
				}
				break ;

			case 95://Actual Transaction Amount
				char DispAmount[ 20 ];
				int Dispamount;

				memset( DispAmount, 0, sizeof( DispAmount ) );
				memset( DispAmount, '0', 12 );
				Dispamount = atoi( txnmsg->DispAmount ) * 100;
				trace( DEBUG_NORMAL, "DispAmount[ %d ]\n", Dispamount);
				memset( txnmsg->DispAmount, 0, sizeof(txnmsg->DispAmount ) );
				sprintf( txnmsg->DispAmount, "%012d", Dispamount );
				if( strlen( txnmsg->DispAmount ) < 12 )
					strncpy( DispAmount + 12 - strlen( txnmsg->DispAmount ) , txnmsg->DispAmount, strlen( txnmsg->DispAmount ) );
				else
					strncpy( DispAmount, txnmsg->DispAmount, 12 );

				OutBuf += fmt_out( OutBuf, DispAmount,  CHAR, 12, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "000000000000",  CHAR, 12, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  CHAR, 8, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  CHAR, 8, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  CHAR, 8, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  CHAR, 8, bitno );
				break ;

			case 102://Account Identification 1
				len = strlen( txnmsg->FromAccount );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			default:
				trace( "Unhandled bit in iso8583" );
				break ;
		}
	}
	return( OutBuf - BufOffset );
}


int EzMcNormal8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len;
	char StmtBuf[ STMT_BUF_SIZE +1 ];
	char TempAmount[15], temp[50], decimal[3], temptxn[7];
	char ComTempDate[ 7 ], TempDate[ 7 ], CheckDate[ 5 ];
	char *month, *day, *year;
	int Amount, ExtRespCode, ExtNetCode, ExtMsgType, date;


	InBuf += fmt_in( InBuf, &ExtMsgType, ATOI, 4 , 0 );
	txnmsg->MsgType = getInBoundSwitchMsgType( ExtMsgType );
	trace( "Ext MsgType [%d] --> Switch MsgType [%d]", ExtMsgType,  txnmsg->MsgType );

	//InBuf += fmt_in( InBuf, &txnmsg->MsgType, ATOI, 4 , 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	memcpy( BitMap, InBuf, 8 );
	InBuf += 8;
//	hex_dump( (unsigned char *)BitMap, 8 );
	if( IsBitSet( BitMap, 1 ) )
	{
		memcpy( BitMap+8, InBuf, 8 );
		InBuf += 8;
//		hex_dump( (unsigned char *)BitMap, 16 );
	}
	//InBuf += fmt_in( InBuf, BitMap, ATOH, 16, 1 );

	if( txnmsg->MsgType == 420 )
	{
		memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
		memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
		strcpy( txnmsg->OrgChannel, "EzMcNormal8583");
		strcpy( txnmsg->OrgPort, "McNormal");
	}

	strcpy( txnmsg->SrcChannel, "EzMcNormal8583");
	strcpy( txnmsg->SrcPort, "McNormal");


	if( txnmsg->MsgType == 800 )
		strcpy( txnmsg->NetworkId, "McNormal");

	if( txnmsg->MsgType == 810 )
		strcpy( txnmsg->NetworkId, "McNormal");

	//if( IsBitSet( BitMap, 1 ) )
		//InBuf += fmt_in( InBuf, BitMap + 8, ATOH, 16, 1 );

	for( int bitno = 1; bitno <= 128; bitno++ )
	{
		if( !IsBitSet( BitMap, bitno ) )
			continue;

		if( bitno > 64 )
		{
			if( !IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( bitno )
		{

			case 1:// Seconday Bit Map
				break ;

			case 2://Primary Account Number
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				format_str( 6, len - 4, '*' );
				InBuf += fmt_in( InBuf, txnmsg->chn, CHAR, len, bitno );
				break ;

			case 3://Processing Code
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOL, 6, bitno );
				if( txnmsg->TxnCode/10000 == 31 )
				{
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%06d", txnmsg->TxnCode );
					memset( temptxn, 0, sizeof( temptxn ) );
					strcpy( temptxn, "30" );
					strcat( temptxn, temp + 2 );
					trace( "temptxn[%s]",temptxn);
				}
				else
				{
					memset( temptxn, 0, sizeof( temptxn ) );
					sprintf( temptxn, "%06d", txnmsg->TxnCode );
				}
				txnmsg->TxnCode = atoi( temptxn );
				break ;

			case 4://Transaction Amount
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				if( ( txnmsg->TxnCode/10000 ) == 1 )
				{
					Amount = atoi( TempAmount ) / 100;
					sprintf( txnmsg->Amount, "%d.00", Amount );
				}
				else
				{
					memset( temp, 0, sizeof( temp ) );
					memset( decimal, 0, sizeof( decimal ) );
					trace( "TempAmount[%s]", TempAmount);
					strncpy( temp, TempAmount, strlen( TempAmount )-2 );
					strncpy( decimal, TempAmount + strlen( TempAmount ) - 2, 2 );
					trace( "Amount[%s] Decimal[%s]", temp, decimal );
					memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
					sprintf( txnmsg->Amount, "%s.%s", temp, decimal);
				}
				trace("Transaction Amount[%s]", txnmsg->Amount);
				break ;

			case 5://Settlement Amount
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				if( ( txnmsg->TxnCode/10000 ) == 1 )
				{
					Amount = atoi( TempAmount ) / 100;
					sprintf( txnmsg->SettAmount, "%d.00", Amount );
				}
				else
				{
					memset( temp, 0, sizeof( temp ) );
					memset( decimal, 0, sizeof( decimal ) );
					trace( "TempAmount[%s]", TempAmount);
					strncpy( temp, TempAmount, strlen( TempAmount )-2 );
					strncpy( decimal, TempAmount + strlen( TempAmount ) - 2, 2 );
					trace( "Amount[%s] Decimal[%s]", temp, decimal );
					memset( txnmsg->SettAmount, 0, sizeof( txnmsg->SettAmount ) );
					sprintf( txnmsg->SettAmount, "%s.%s", temp, decimal);
				}
				trace("Settlement Amount[%s]", txnmsg->SettAmount);
				break ;

			case 7://Transmission Date and Time - MMDDhhmmss

				memset( TempDate, 0, sizeof( TempDate ) );

				InBuf += fmt_in( InBuf, TempDate, CHAR, 4, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, bitno );

				memset( CheckDate, 0, sizeof( CheckDate ) );
				strncpy( CheckDate, &TempDate[2], 2 );
				strncat( CheckDate, TempDate, 2 );
				date = getSysDate( );
				year = getSysYear( );
				strcat( CheckDate, year );
				txnmsg->TranDate = atoi( CheckDate );
				trace( "txnmsg->TranDate[%d]", txnmsg->TranDate );

				break ;

			case 8://Billing fee amount
				//reserved to use for online fee.
				break ;

			case 11://Systems Trace Audit Number
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOL, 6, bitno );
				break ;

			case 12://Local Transaction Time
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, bitno );
				break ;

			case 13://Local Transaction Date - MMDD
				memset( TempDate, 0, sizeof( TempDate ) );

				InBuf += fmt_in( InBuf, TempDate, CHAR, 4, bitno );

				memset( CheckDate, 0, sizeof( CheckDate ) );
				strncpy( CheckDate, &TempDate[2], 2 );
				strncat( CheckDate, TempDate, 2 );
				date = getSysDate( );
				year = getSysYear( );
				strcat( CheckDate, year );
				txnmsg->LocalDate = atoi( CheckDate );
				trace( "txnmsg->LocalDate[%d]", txnmsg->LocalDate );
				break ;

			case 14://Expiration Date - YYMM
				InBuf += fmt_in( InBuf, &txnmsg->ExpiryDate, ATOL, 4, bitno );
				break ;

			case 15://Settlement Date -- MMDD
				memset( TempDate, 0, sizeof( TempDate ) );

				InBuf += fmt_in( InBuf, TempDate, CHAR, 4, bitno );

				memset( CheckDate, 0, sizeof( CheckDate ) );
				strncpy( CheckDate, &TempDate[2], 2 );
				strncat( CheckDate, TempDate, 2 );
				date = getSysDate( );
				year = getSysYear( );
				strcat( CheckDate, year );
				txnmsg->SettlementDate = atoi( CheckDate );
				trace( "txnmsg->SettlementDate[%d]", txnmsg->SettlementDate );
				break;

			case 16://Convertion Date -- MMDD
				memset( TempDate, 0, sizeof( TempDate ) );

				InBuf += fmt_in( InBuf, TempDate, CHAR, 4, bitno );

				memset( CheckDate, 0, sizeof( CheckDate ) );
				strncpy( CheckDate, &TempDate[2], 2 );
				strncat( CheckDate, TempDate, 2 );
				date = getSysDate( );
				year = getSysYear( );
				strcat( CheckDate, year );
				txnmsg->IssConvDate = atoi( CheckDate );
				trace( "txnmsg->IssConvDate[%d]", txnmsg->IssConvDate );
				break;

			case 17://Capture Date - MMDD
				memset( TempDate, 0, sizeof( TempDate ) );

				InBuf += fmt_in( InBuf, TempDate, CHAR, 4, bitno );

				memset( CheckDate, 0, sizeof( CheckDate ) );
				strncpy( CheckDate, &TempDate[2], 2 );
				strncat( CheckDate, TempDate, 2 );
				date = getSysDate( );
				year = getSysYear( );
				strcat( CheckDate, year );
				txnmsg->CaptureDate = atoi( CheckDate );
				trace( "txnmsg->CaptureDate[%d]", txnmsg->CaptureDate );
				break ;

			case 18://Merchant’s Type (MCC)
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;

			case 22://Point of Service Entry Mode
				InBuf += fmt_in( InBuf, &txnmsg->PosEntryCode, ATOS, 3, bitno );
				break ;

			case 23://Card Sequence Number
				//Used for EMV transactions only.
				break ;

			case 32://Acquiring Institution Identification Code
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcquirerBin, CHAR, len, bitno );
				if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 || txnmsg->MsgType == 421 )
					strcpy( txnmsg->AcquirerInst, "McNormal" );
				break ;

			case 33://Forwarding Institution Identification Code
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ForwardBin, CHAR, len, bitno );
				break ;

			case 35://Track 2 Data
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				format_str( 0, len, '*' );
				InBuf += fmt_in( InBuf, txnmsg->Track2, CHAR, len, bitno );
				break ;

			case 37://Retrieval Reference Number
				InBuf += fmt_in( InBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 38://Auth Number
				InBuf += fmt_in( InBuf, txnmsg->AuthNum, CHAR, 6, bitno );
				break ;

			case 39://Response Code
				InBuf += fmt_in( InBuf, &ExtRespCode, ATOI, 2, bitno );
				//if( txnmsg->MsgType == 210 || txnmsg->MsgType == 430 )
				//{
				txnmsg->RespCode = getInBoundSwitchRespCode( ExtRespCode );
				trace("ExtRespCode[%d] --> SwitchRespCode[%d]", ExtRespCode, txnmsg->RespCode );
				//}
				break ;

			case 41://Card Acceptor Terminal Identification
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 42://Card Acceptor Identification Code
				InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, 15, bitno );
				break ;

			case 43://Card Acceptor Name/Location
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break ;

			case 48://Additional Data DKE
				break ;

			case 49://Transaction Currency Code
				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOI, 3, bitno );
				break ;

			case 50://Settlement Currency Code
				InBuf += fmt_in( InBuf, &txnmsg->SettCurrencyCode, ATOI, 3, bitno );
				break ;

			case 52://Personal Identification Number (PIN) Data
				format_str( 0, 16, '*' );
				InBuf += fmt_in( InBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break ;

			case 54://Additional Amounts
				char tempStr[ 20 ], amtType[ 3 ], Balance[20];
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				for( int i = 0; i < len; )
				{
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 2, bitno );
					i += 2;
					memset( amtType, 0, sizeof( amtType ) );
					InBuf += fmt_in( InBuf, amtType, CHAR, 2, bitno );
					i += 2;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 3, bitno );
					i += 3;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 1, bitno );
					i += 1;
					if( !strcmp( amtType, "02" ) )
					{
						memset( Balance, 0, sizeof( Balance ) );
						InBuf += fmt_in( InBuf, Balance, CHAR, 12, bitno );
						memset( tempStr, 0, sizeof( tempStr ) );
						removeLeadingZeros( Balance, tempStr );
						if( atoi( tempStr ) > 0 )
						{
							strncpy( txnmsg->AvailBalance, tempStr, strlen( tempStr ) - 2 );
							strcat( txnmsg->AvailBalance,"." );
							strncat( txnmsg->AvailBalance, tempStr + strlen( tempStr ) - 2, 2 );
							trace("Balance[%s]",txnmsg->AvailBalance);
						}
						else
							strcpy( txnmsg->AvailBalance,"0.00" );
					}
					else
					{
						memset( Balance, 0, sizeof( Balance ) );
						InBuf += fmt_in( InBuf, Balance, CHAR, 12, bitno );
						memset( tempStr, 0, sizeof( tempStr ) );
						removeLeadingZeros( Balance, tempStr );
						if( atoi( tempStr ) > 0 )
						{
							strncpy( txnmsg->LedgerBalance, tempStr, strlen( tempStr ) - 2 );
							strcat( txnmsg->LedgerBalance,"." );
							strncat( txnmsg->LedgerBalance, tempStr + strlen( tempStr ) - 2, 2 );
							trace("Balance1[%s]",txnmsg->LedgerBalance);
						}
						else
							strcpy( txnmsg->LedgerBalance,"0.00" );
					}
					i += 12;
				}
				break ;

			case 55://EMV Tag data
				break ;

			case 57://EMV System related data
				break ;

			case 70://Network Management Information Code
				InBuf += fmt_in( InBuf, &ExtNetCode, ATOI, 3, bitno );
				txnmsg->NetCode = getInBoundSwitchNetCode( ExtNetCode );
				trace( "ExtNetCode[%03d] --> Switch NetCode [%03d]", ExtNetCode, txnmsg->NetCode );
				break ;

            case 90://Original Data Elements
            	InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, 42, bitno );
            	/*InBuf += fmt_in( InBuf, &txnmsg->OrgMsgType, ATOI, 4 , bitno );
            	InBuf += fmt_in( InBuf, &txnmsg->OrgTraceNo, ATOL, 6 , bitno );
				memset( TempDate, 0, sizeof( TempDate ) );

				InBuf += fmt_in( InBuf, TempDate, CHAR, 4, bitno );
				memset( CheckDate, 0, sizeof( CheckDate ) );
				strncpy( CheckDate, &TempDate[2], 2 );
				strncat( CheckDate, TempDate, 2 );
				date = getSysDate( );
				year = getSysYear( );
				strcat( CheckDate, year );
				txnmsg->OrgTranDate = atoi( CheckDate );
				trace( "txnmsg->OrgTranDate[%d]", txnmsg->OrgTranDate );

				InBuf += fmt_in( InBuf, &txnmsg->OrgTranTime, ATOL, 6, bitno );

				memset( temp, 0,sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, 22, bitno );*/
				break ;

			case 95://Actual Transaction Amount
				InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, 42, bitno );
				memset(TempAmount, 0, sizeof( TempAmount ) );
				strncpy( TempAmount, txnmsg->RsvFld3, 12 );
				Amount = atoi( TempAmount ) / 100;
				sprintf( txnmsg->DispAmount, "%d.00", Amount );
				trace("DispAmount[ %s ]", txnmsg->DispAmount );
				break ;

			case 102://Account Identification 1
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", bitno );
				break;
		}
	}
	return 1;
}

void EzMcNormal8583 :: removeLeadingZeros( const char *SrcStr, char *DestStr )
{
	int i = 0;
	trace( "SrcStr[%s]", SrcStr );
	DestStr[ 0 ] = SrcStr[ 0 ];

	for( i = 1; i < strlen( SrcStr ); i++ )
	{
		if( SrcStr[ i ] != '0' )
			break;
	}
	trace( "offset = [%d]  SrcStr[%s]", i, SrcStr + i );
	strcpy( DestStr+1, SrcStr + i );
}

void EzMcNormal8583 :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 4096 + 1 ];
	char MsgBuffer[ 4096 + 1 ];
	while( 1 )
	{
		trace( "EzMcNormal8583 Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetSourceChannelName() );
		//	hex_dump( ( unsigned char * ) ISOMessage, MsgSize );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			if( DecomposeISOMessage( ISOMessage, &txnmsg ) < 0 )
			{
				trace( "Error in Decomposing ISO Message from Port[%s]", GetLastSenderChannelName() );
				continue;
			}

			if( WriteChannel( "EzTxnMgr", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
				trace( "Error in Writing Message to Channel EzTxnMgr" );
			else
				trace( "Message Sucessfully Written to Channel EzTxnMgr" );
			if( txnmsg.MsgType == 800 )
			{
				txnmsg.MsgType = 810;
				strcpy( txnmsg.DestPort, GetLastSenderChannelName() );
				memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
				MsgSize = ComposeISOMessage( &txnmsg, MsgBuffer );
				if( MsgSize < 0 )
				{
					trace( "Error in Composing ISO Message" );
					continue;
				}

				//hex_dump( ( unsigned char * ) MsgBuffer, MsgSize );
				if( WritePortChannel( txnmsg.DestPort, MsgBuffer, MsgSize ) < 0 )
					trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
				else
					trace( "Written Message to Port[%s]", txnmsg.DestPort );
			}
		}
		else
		{
			trace( "Message of size[ %d ] Received from Channel[ %s ]", MsgSize, GetSourceChannelName() );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &txnmsg, ISOMessage, sizeof( struct EzTxnMsg ) );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			MsgSize = ComposeISOMessage( &txnmsg, MsgBuffer );
			if( MsgSize < 0 )
			{
				trace( "Error in Composing ISO Message" );
				continue;
			}

			//hex_dump( ( unsigned char * ) MsgBuffer, MsgSize );
			if( WritePortChannel( txnmsg.DestPort, MsgBuffer, MsgSize ) < 0 )
				trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
			else
				trace( "Written Message to Port[%s]", txnmsg.DestPort );
		}
	}
}



int main( int argc, char **argv )
{
	EzMcNormal8583 EzMcNormal8583obj;
	EzMcNormal8583obj.InitEzMcNormal8583( argv[ 0 ] );
	EzMcNormal8583obj.ServiceRequest();
	return 1;
}

