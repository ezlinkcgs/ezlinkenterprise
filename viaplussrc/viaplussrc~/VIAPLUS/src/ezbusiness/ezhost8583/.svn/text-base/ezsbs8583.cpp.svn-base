#include <ezbusiness/ezhost8583.h>

EzHost8583 :: EzHost8583()
{
}

EzHost8583 :: ~EzHost8583()
{
}

void EzHost8583 :: InitEzHost8583( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", TaskName );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzHost8583 Started Running^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzHost8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzHost8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", TaskName );
		trace( "^^^^^^^^^^^EzHost8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", "EzSBS8583BitMap.cfg" );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzHost8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	initFmtUtil( this );

	TaskInit();
	initEzSigUtil( this );
}

int EzHost8583 :: getUBPToAcct( int TxnCode, char *ToAcct )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], SearchId[ CFG_VAL_SIZE + 1 ], TempTxnCode[ 3 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg/ubp", "UBPacctmap.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in opening file[ %s ]", cfgpath );
		return -1;
	}

	memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
	sprintf( TempTxnCode, "%02d", ( TxnCode%100 ) );

	memset( SearchId, 0, sizeof( SearchId ) );
	sprintf( SearchId, "%s#%s", "UBPACCTMAP", TempTxnCode );
	trace( DEBUG_NORMAL, "SearchId [%s]", SearchId );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( SearchId, cfgval, 2 ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Searching CHANNEL#ORGKEY from file[ %s ]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "CfgVal [%s]", cfgval );
		memset( ToAcct, 0, sizeof( ToAcct ) );
		strcpy( ToAcct, cfgval );
	}

	cfgutil.cfg_close();
	return 1;
}

int EzHost8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ];
	unsigned char BitMap[ 33 ];
	int len;
	BufOffset = OutBuf;

	trace( "MsgType = [%d]", txnmsg->MsgType );
	OutBuf += fmt_out( OutBuf, &txnmsg->MsgType, ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

	if( ( txnmsg->TxnCode/10000 ) == 83 || ( txnmsg->TxnCode/10000 ) == 82 )
	{
		if( getUBPToAcct( txnmsg->TxnCode, txnmsg->ToAccount ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Loading UBP Account");
			return -1;
		}
	}
	if( txnmsg->TxnCode/10000 == 41 )
		strcpy( txnmsg->ToAccount, txnmsg->RsvFld1 );

	if( txnmsg->MerchantType == 6012 )
	{
		if( txnmsg->MsgType == 200 || txnmsg->MsgType == 1220 )
		{
			SetBitOff( BitMap, 2 );
			if( ( ( txnmsg->TxnCode/10000 ) != 20 ) && ( ( txnmsg->TxnCode/10000 ) != 55 ) && ( ( txnmsg->TxnCode/10000 ) != 56 ) && ( ( txnmsg->TxnCode/10000 ) != 57 ) && ( ( txnmsg->TxnCode/10000 ) != 58 ) )
			{
				SetBitOn( BitMap, 64 );
				SetBitOn( BitMap, 65 );
				SetBitOn( BitMap, 66 );
			}

			if( ( ( txnmsg->TxnCode/10000 ) == 55 ) || ( ( txnmsg->TxnCode/10000 ) == 56 ) || ( ( txnmsg->TxnCode/10000 ) == 57 ) || ( ( txnmsg->TxnCode/10000 ) == 58 ) )
				SetBitOn( BitMap, 126 );
		}
	}

	if( txnmsg->MerchantType == 6015 )
		SetBitOn( BitMap, 81 );

	OutBuf += fmt_out( OutBuf, BitMap, HTOA, 16, 1 );
	if( IsBitSet( BitMap, 1 ) )
		OutBuf += fmt_out( OutBuf, BitMap + 8, HTOA, 16, 1 );


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

			case 2:
				len = strlen( txnmsg->chn );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->chn, CHAR, len, bitno );
				break ;

			case 3:
				OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, LTOA, 6, bitno );
				break ;

			case 4:
				char TempAmount[13];
				int Amount;

				memset( TempAmount, 0, sizeof( TempAmount ) );
				if( strlen( txnmsg->Amount ) <= 0 )
					strncpy( TempAmount, "000000000000", 12 );
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
					sprintf( TempAmount, "%012d", Amount );
				}
				OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
				break ;

			case 7:
				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );
				break ;

			case 11:
				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
				break ;

			case 12:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, LTOA, 6, bitno );
				break;

			case 13:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, LTOA, 6, bitno );
				break ;

			case 17:
				OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, LTOA, 6, bitno );
				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 32:
				if( txnmsg->MsgType == 800 )
				{
					len = strlen( txnmsg->NetworkId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->AcqNetworkId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->AcqNetworkId, CHAR, len, bitno );
				}
				break ;

			case 37:
				OutBuf += fmt_out( OutBuf, &txnmsg->RefNum, CHAR, 12, bitno );
				break;

			case 39:
				OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 2, bitno );
				break;

			case 41:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break ;

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 54:
				break;

			case 60:
				trace( DEBUG_ERROR, "txnmsg->IssBranchCode[%s]", txnmsg->IssBranchCode );
				len = strlen( txnmsg->IssBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->IssBranchCode, CHAR, len, bitno );
				break ;

			case 61:
				trace( DEBUG_ERROR, "txnmsg->FromAcctSubType[%s]", txnmsg->FromAcctSubType );
				len = strlen( txnmsg->FromAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAcctSubType, CHAR, len, bitno );
				break;

			case 62:
				len = strlen( txnmsg->TxfBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->TxfBranchCode, CHAR, len, bitno );
				break ;

			case 63:
				len = strlen( txnmsg->ToAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ToAcctSubType, CHAR, len, bitno );
				break ;

			case 64:
				len = strlen( txnmsg->RsvFld3 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, CHAR, len, bitno );
                break ;

			case 65:
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

        	case 66:
        		len = strlen( txnmsg->RsvFld5 );
        		OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
        		OutBuf += fmt_out( OutBuf, txnmsg->RsvFld5, CHAR, len, bitno );
                break ;

			case 67:
				len = strlen( txnmsg->AcqBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcqBranchCode, CHAR, len, bitno );
				break ;

			case 70:
				OutBuf += fmt_out( OutBuf, &txnmsg->NetCode, ITOA, 3, bitno );
				trace( "Net Code [%03d]", txnmsg->NetCode );
				break ;

			 case 71:
                len = strlen( txnmsg->RsvFld1 );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
                break;

            case 80:
		len = strlen( txnmsg->NetworkId );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, CHAR, len, bitno );
                break ;

            case 81:
		len = strlen( txnmsg->RsvFld6 );
		if( txnmsg->MerchantType == 6015 )
		{
                	OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
                	OutBuf += fmt_out( OutBuf, txnmsg->RsvFld6, CHAR, len, bitno );
		}
		else
		{
                	OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
               		OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
		}
                break ;

			case 90:

				trace( "Original Data Elements" );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgMsgType, ITOA, 4, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgTraceNo, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranDate, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranTime, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000000",  CHAR, 11, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000000",  CHAR, 11, bitno );

				break ;

			case 95:

				trace( "Added for Partial Reversal" );

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


			case 102:
				char TempAcct[ 10 ];
				if( txnmsg->MerchantType == 6011 )
				{
					memset( TempAcct, 0, sizeof( TempAcct ) );
					strncpy( TempAcct, txnmsg->FromAccount + strlen( txnmsg->FromAccount ) - 8, 8 );
					len = strlen( TempAcct );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, TempAcct, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->FromAccount );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->FromAccount, CHAR, len, bitno );
				}
				break;

			case 103:
				len = strlen( txnmsg->ToAccount );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ToAccount, CHAR, len, bitno );
				break;

			case 126:
				len = strlen( txnmsg->RsvFld1 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
                break ;

			case 127:

				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				strcpy( StmtBuf, txnmsg->RsvFld1 );
				trace( DEBUG_NORMAL, "Reserved Field [%s]\n", StmtBuf );

				len = strlen( StmtBuf );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, StmtBuf, CHAR, len, bitno );
				break;


			default:
				trace( "Unhandled bit in iso8583" );
				break ;
		}
	}
	return( OutBuf - BufOffset );
}


int EzHost8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len;
	char StmtBuf[ STMT_BUF_SIZE +1 ];
	InBuf += fmt_in( InBuf, &txnmsg->MsgType, ATOI, 4 , 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmt_in( InBuf, BitMap, ATOH, 16, 1 );

	if( IsBitSet( BitMap, 1 ) )
		InBuf += fmt_in( InBuf, BitMap + 8, ATOH, 16, 1 );

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

			case 2:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->chn, CHAR, len, bitno );
				break ;

			case 3:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOL, 6, bitno );
				break ;

			case 4:
				char TempAmount[15], temp[15], decimal[3];
				int Amount;

				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				memset( temp, 0, sizeof( temp ) );
				memset( decimal, 0, sizeof( decimal ) );
				trace( "TempAmount[%s]", TempAmount);
				strncpy( temp, TempAmount, strlen( TempAmount )-2 );
				strncpy( decimal, TempAmount + strlen( TempAmount ) - 2, 2 );
				Amount = atoi( temp );
				memset( temp, 0, sizeof( temp ) );
				sprintf( temp, "%d", Amount );
				trace( "Amount[%s] Decimal[%s]", temp, decimal );
				memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
				sprintf( txnmsg->Amount, "%s.%s", temp, decimal);
				trace("Transaction Amount[%s]", txnmsg->Amount);
				break ;

			case 7:
				InBuf += fmt_in( InBuf, &txnmsg->TranDate, ATOL, 6, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, bitno );
				break ;

			case 11:
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOL, 6, bitno );
				break ;

			case 12:
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, bitno );
				break ;

			case 13:
				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOL, 6, bitno );
				break ;

			case 17:
				InBuf += fmt_in( InBuf, &txnmsg->CaptureDate, ATOL, 6, bitno );
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;

			case 32:
				if( txnmsg->MsgType == 810 )
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->NetworkId, CHAR, len, bitno );
				}
				else
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->AcqNetworkId, CHAR, len, bitno );
				}
				break ;
			case 37:
				InBuf += fmt_in( InBuf, &txnmsg->RefNum, CHAR, 12, bitno );
				break ;
			case 38:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AuthNum, CHAR, len, bitno );
				break ;
			case 39:
				InBuf += fmt_in( InBuf, &txnmsg->RespCode, ATOI, 2, bitno );
				break ;

			case 41:
				char TempTid[17];
				memset( TempTid, 0, sizeof( TempTid ) );
				InBuf += fmt_in( InBuf, TempTid, CHAR, 16, bitno );
				for( int i = 0, j = 0; i < strlen( TempTid ); i++ )
				{
					if( TempTid[i] != ' ' )
					{
						txnmsg->TerminalId[j] = TempTid[i];
						j++;
					}
				}
				break ;

			case 43:
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 54:
				char tempStr[ 20 ], amtType[ 3 ];
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
						InBuf += fmt_in( InBuf, txnmsg->AvailBalance, CHAR, 12, bitno );
					else
						InBuf += fmt_in( InBuf, txnmsg->LedgerBalance, CHAR, 12, bitno );
					i += 12;
				}
				break ;

			case 60:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->IssBranchCode, CHAR, len, bitno );
				break ;

			case 61:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAcctSubType, CHAR, len, bitno );
				break ;

			case 62:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->TxfBranchCode, CHAR, len, bitno );
				break ;

			case 63:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ToAcctSubType, CHAR, len, bitno );
				break ;

			case 64:
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, bitno );
                break ;

			case 65:
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

			case 66:
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld5, CHAR, len, bitno );
                break ;

			case 67:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcqBranchCode, CHAR, len, bitno );
				break ;

			case 70:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOI, 3, bitno );
				trace( "Net Code [%03d]", txnmsg->TxnCode );
				break ;

            case 71:
                InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, bitno );
                trace( "Host Data 1 [%s]\n", txnmsg->RsvFld1 );
                break ;

            case 72:
                InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, len, bitno );
                trace( "Host Data 2 [%s]\n", txnmsg->RsvFld2 );
                break ;

            case 80:
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->NetworkId, CHAR, len, bitno );
                break ;
            case 81:
		if( txnmsg->MerchantType == 6015 )
		{
                	InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
                	InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, len, bitno );
		}
		else
		{
                	InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
                	InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, bitno );
		}
                break ;

			case 90:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld2, CHAR, 44, bitno );
				break ;

			case 95:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld3, CHAR, 44, bitno );
				break ;

			case 102:
				char TempAcct[ 10 ];
				if( txnmsg->MerchantType == 6011 )
				{
					memset( TempAcct, 0, sizeof( TempAcct ) );
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, TempAcct, CHAR, len, bitno );
					sprintf( txnmsg->FromAccount, "%s%s%s", txnmsg->IssBranchCode, txnmsg->FromAcctSubType, TempAcct );
				}
				else
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, bitno );
				}
				break;

			case 103:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ToAccount, CHAR, len, bitno );
				break;

			case 126:
                InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, bitno );
                break ;

			case 127:

				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, StmtBuf, CHAR, len, bitno );

				if( len > 200 )
				{
					strncpy( txnmsg->RsvFld1, StmtBuf, 200 );
					strncpy( txnmsg->RsvFld2, StmtBuf + 200, ( len - 200 ) );
				}
				else
					strcpy( txnmsg->RsvFld1, StmtBuf );

				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", bitno );

		}

	}
	return 1;
}

void EzHost8583 :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 2600 + 1 ];
	char MsgBuffer[ 2600 + 1 ];
	while( 1 )
	{
		trace( "EzHost8583 Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetSourceChannelName() );
			hex_dump( ( unsigned char * ) ISOMessage, MsgSize );
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
		}
		else
		{
			trace( "Message of size[ %d ] Received from Channel[ %s ]", MsgSize, GetSourceChannelName() );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &txnmsg, ISOMessage, sizeof( struct EzTxnMsg ) );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( ComposeISOMessage( &txnmsg, MsgBuffer ) < 0 )
			{
				trace( "Error in Composing ISO Message" );
				continue;
			}

			if( WritePortChannel( txnmsg.DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
				trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
			else
				trace( "Written Message to Port[%s]", txnmsg.DestPort );
		}
	}
}


int main( int argc, char **argv )
{
	EzHost8583 ezhost8583obj;
	ezhost8583obj.InitEzHost8583( argv[ 0 ] );
	ezhost8583obj.ServiceRequest();
	return 1;
}

