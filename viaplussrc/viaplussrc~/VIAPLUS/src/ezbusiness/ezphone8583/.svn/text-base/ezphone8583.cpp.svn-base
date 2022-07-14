#include <ezbusiness/ezphone8583.h>

EzPhone8583 :: EzPhone8583()
{
}

EzPhone8583 :: ~EzPhone8583()
{
}

void EzPhone8583 :: InitEzPhone8583( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];
	char FilePath[ FILENAME_SIZE + 1 ], SearchId[ TEMP +1 ], CfgVal[ TEMP + 1 ], Temp[ TEMP + 1 ];
	EzCfgUtil cfg;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezphone8583.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzPhone8583 Started Running^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzPhone8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzPhone8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzPhone8583" ) < 0 )
	{
		trace( "Error in Creating EzPhone8583 Channel" );
		trace( "^^^^^^^^^^^EzPhone8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", "EzPhone8583BitMap.cfg" );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzPhone8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	initFmtUtil( this );

	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing the EzSecurityUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzPhone8583 Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	memset( FilePath, 0, sizeof( FilePath ) );
	sprintf( FilePath, "%s/%s", getenv("EZDIR_HOME"), "cfg/ezphone.cfg" );

	if( cfg.cfg_open( FilePath ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to open file [ %s ]", FilePath );
		closeDebug( );
		TaskExit( );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	memset( SearchId, 0, sizeof( SearchId ) );
	sprintf( SearchId, "%s", "DEFAULT#INSTID" );

	trace( DEBUG_NORMAL, "SearchId[ %s ]", SearchId );
	if( cfg.cfg_search( SearchId, CfgVal, 2 ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		closeDebug( );
		TaskExit( );
	}
	else
	{
		memset( InstId, 0, sizeof( InstId ) );
		strcpy( InstId, CfgVal );
		trace( DEBUG_NORMAL, "Institution Id[ %s ]", InstId );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	memset( SearchId, 0, sizeof( SearchId ) );
	sprintf( SearchId, "%s", "DEFAULT#BRANCH" );

	trace( DEBUG_NORMAL, "SearchId[ %s ]", SearchId );
	if( cfg.cfg_search( SearchId, CfgVal, 2 ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		closeDebug( );
		TaskExit( );
	}
	else
	{
		memset( BranchCode, 0, sizeof( BranchCode ) );
		strcpy( BranchCode, CfgVal );
		trace( DEBUG_NORMAL, "Branch Code[ %s ]", BranchCode );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	memset( SearchId, 0, sizeof( SearchId ) );
	sprintf( SearchId, "%s", "DEFAULT#SECURITYID" );

	trace( DEBUG_NORMAL, "SearchId[ %s ]", SearchId );
	if( cfg.cfg_search( SearchId, CfgVal, 2 ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		closeDebug( );
		TaskExit( );
	}
	else
	{
		memset( SecurityId, 0, sizeof( SecurityId ) );
		strcpy( SecurityId, CfgVal );
		trace( DEBUG_NORMAL, "Security Id[ %s ]", SecurityId );
	}

	TaskInit();
	initEzSigUtil( this );
}

int EzPhone8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset;
	unsigned char BitMap[ 33 ];
	char tempStr[ 121 ], TempAvailBalance[ 30 ], TempLedgerBalance[ 30 ];
	int len;
	int availbal = 0;
	BufOffset = OutBuf;

	trace( "MsgType = [%d]", txnmsg->MsgType );
	OutBuf += fmt_out( OutBuf, ( char * )"ISO031000076", CHAR, 12, 0 );
	OutBuf += fmt_out( OutBuf, &txnmsg->MsgType, ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

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
				if( strlen( txnmsg->Amount ) <= 0 )
				strncpy( txnmsg->Amount, "000000000000", 12 );
				OutBuf += fmt_out( OutBuf, txnmsg->Amount, CHAR, 12, bitno );
				break ;

			case 7:
				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, LTOA, 4, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );
				break ;

			case 11:
				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
				break ;

			case 12:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, LTOA, 6, bitno );
				break;

			case 13:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, LTOA, 4, bitno );
				break ;

			case 15:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, LTOA, 4, bitno );
				break ;
			case 17:
				OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, LTOA, 4, bitno );
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
					len = strlen( txnmsg->AcquirerInst );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->AcquirerInst, CHAR, len, bitno );
				}
				break ;

			case 35:
				char Track2[ 40 ];
				memset( Track2, 0, sizeof( Track2 ) );
				sprintf( Track2, "%s=12125010000000000", txnmsg->chn );
				len = strlen( Track2 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, Track2, CHAR, len, bitno );
				break ;

			case 37:
				OutBuf += fmt_out( OutBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 39:
				OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 2, bitno );
				break;

			case 41:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break ;

			case 42:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 15, bitno );
				break;

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 44:
				memset( TempAvailBalance, 0, sizeof( TempAvailBalance ) );
				for( int k = 0, l = 0; k < strlen( txnmsg->AvailBalance ); k++ )
				{
					if( txnmsg->AvailBalance[ k ] != '.' )
					{
						TempAvailBalance[ l ] = txnmsg->AvailBalance[ k ];
						l++;
					}
				}
				memset( TempLedgerBalance, 0, sizeof( TempLedgerBalance ) );
				for( int k = 0, l = 0; k < strlen( txnmsg->LedgerBalance ); k++ )
				{
					if( txnmsg->LedgerBalance[ k ] != '.' )
					{
						TempLedgerBalance[ l ] = txnmsg->LedgerBalance[ k ];
						l++;
					}
				}
				memset( tempStr, 0, sizeof( tempStr ) );
				availbal = atoi( TempAvailBalance );
				availbal = availbal/100;
	            sprintf( tempStr, "a%012d%012d", availbal, availbal );
	            len = strlen( tempStr );
	            OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
	            OutBuf += fmt_out( OutBuf, tempStr, CHAR, len, bitno );

				/*char AddRespData[ 100 ];
				memset( AddRespData, 0, sizeof( AddRespData ) );
				sprintf( AddRespData, "a%012s%012s", txnmsg->LedgerBalance, txnmsg->AvailBalance );
				len = strlen( AddRespData );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, AddRespData, CHAR, len, bitno );*/
				break ;

			case 49:
				OutBuf += fmt_out( OutBuf, (char *) "356", CHAR, 3, bitno );
				break;

			case 52:
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->PINBlock, CHAR, len, bitno );
				break;

			case 54:
				memset( TempAvailBalance, 0, sizeof( TempAvailBalance ) );
				for( int k = 0, l = 0; k < strlen( txnmsg->AvailBalance ); k++ )
				{
					if( txnmsg->AvailBalance[ k ] != '.' )
					{
						TempAvailBalance[ l ] = txnmsg->AvailBalance[ k ];
						l++;
					}
				}
				memset( TempLedgerBalance, 0, sizeof( TempLedgerBalance ) );
				for( int k = 0, l = 0; k < strlen( txnmsg->LedgerBalance ); k++ )
				{
					if( txnmsg->LedgerBalance[ k ] != '.' )
					{
						TempLedgerBalance[ l ] = txnmsg->LedgerBalance[ k ];
						l++;
					}
				}
				memset( tempStr, 0, sizeof( tempStr ) );
	            sprintf( tempStr, "0502356D%012s0501356D%012s", TempAvailBalance, TempLedgerBalance );
	            len = strlen( tempStr );
	            OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
	            OutBuf += fmt_out( OutBuf, tempStr, CHAR, len, bitno );
				break;

			case 59:
		        len = strlen ( txnmsg->PinKey );
			    OutBuf += fmt_out ( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out ( OutBuf, txnmsg->PinKey, CHAR, len, bitno );
				break;

			case 60:
				len = strlen( txnmsg->IssBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->IssBranchCode, CHAR, len, bitno );
				break ;

			case 61:
				len = strlen( txnmsg->FromAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAcctSubType, CHAR, len, bitno );
				break;

			case 62:
				len = strlen( txnmsg->ForwardBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ForwardBranchCode, CHAR, len, bitno );
				break ;

			case 63:
				len = strlen( txnmsg->ToAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ToAcctSubType, CHAR, len, bitno );
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
                break ;

			case 72:
                len = strlen( txnmsg->RsvFld2 );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );
                break ;

			case 90:
				/*
				InBuf += format_str( ( unsigned char * ) DevMsg->RsvFld18, InBuf, CHAR, 22 );
				dbg->trace( NORMAL, "Original Data Elements [%s]\n", DevMsg->RsvFld18 );
				*/
				break ;

			case 102:
				len = strlen( txnmsg->FromAccount );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			case 103:
				len = strlen( txnmsg->ToAccount );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ToAccount, CHAR, len, bitno );
				break;

			case 127:
				char ResvBuf[ 300 ],TempBuf[ 40 ], AcctNo[ 33 ],Description[ 20 ],AccountType[ 3 ],IssBranchCode[ 13 ], ProductCode[ 11 ];
				int NoOfAcct;


				if( ( txnmsg->TxnCode/10000 ) == 36 )
				{
					NoOfAcct =  GetTotalAcct( txnmsg->RespFile );
					if( NoOfAcct <= 0 )
						trace( DEBUG_NORMAL, "No Accts Found<%d>", NoOfAcct );
					else
					{
						trace( DEBUG_NORMAL, "NoOfAccts<%d> ", NoOfAcct );
						memset( ResvBuf, 0, sizeof( ResvBuf ) );
						for( int i = 0; i < NoOfAcct; i++ )
						{
							memset( TempBuf, 0, sizeof( TempBuf ) );
							memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
							memset( AccountType, 0, sizeof( AccountType ) );
							memset( ProductCode, 0, sizeof( ProductCode ));
							memset( AcctNo, 0, sizeof( AcctNo ) );
							memset( Description, 0, sizeof( Description ) );
							if( GetAcctNo( txnmsg->RespFile, i, IssBranchCode, AccountType, ProductCode, AcctNo,Description ) < 0 )
								trace( DEBUG_NORMAL, "Error in getting Account No ");
							else
							{
								trace( DEBUG_NORMAL, "Account No < %s >", AcctNo );
								if( i == 0 )
								{
									sprintf( ResvBuf, "%s~%s~%s~%s|", IssBranchCode,AccountType,ProductCode,AcctNo );
								}
								else
								{
									sprintf( TempBuf, "%s~%s~%s~%s", IssBranchCode,AccountType,ProductCode,AcctNo );
									strcat( ResvBuf, TempBuf );
									strcat( ResvBuf, "|" );
								}
							}
						}
					}

					len = strlen( ResvBuf );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
					OutBuf += fmt_out( OutBuf, ResvBuf, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->RsvFld1 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
				}
				break;


			default:
				trace( "Unhandled bit in iso8583[%d]", bitno );
				break ;
		}
	}
	return( OutBuf - BufOffset );
}


int EzPhone8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len;
	char IsoHeader[ 13 ];

	memset( IsoHeader, 0, sizeof( IsoHeader ) );
	InBuf += fmt_in( InBuf, IsoHeader, CHAR, 12, 0 );
	InBuf += fmt_in( InBuf, &txnmsg->MsgType, ATOI, 4 , 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmt_in( InBuf, BitMap, ATOH, 16, 1 );

	if( IsBitSet( BitMap, 1 ) )
		InBuf += fmt_in( InBuf, BitMap + 8, ATOH, 16, 1 );
	txnmsg->MerchantType = 6014 ;
	strcpy( txnmsg->SecurityId, SecurityId );

	for( int Ind = 0; Ind < 128; Ind++ )
	{
		if( !IsBitSet( BitMap, Ind ) )
			continue;

		if( Ind > 64 )
		{
			if( !IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( Ind )
		{

			case 1:
			     // Seconday Bit Map
			break;

			case 2:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->chn, CHAR, len, Ind );
				break ;

			case 3:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOL, 6, Ind );
				break ;

			case 4:
				InBuf += fmt_in( InBuf, txnmsg->Amount, CHAR, 12, Ind );
				break ;

			case 7:
				InBuf += fmt_in( InBuf, &txnmsg->TranDate, ATOL, 4, Ind );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, Ind );
				break ;

			case 11:
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOL, 6, Ind );
				break ;

			case 12:
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, Ind );
				break ;

			case 13:
				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOL, 4, Ind );
				break ;

			case 17:
				InBuf += fmt_in( InBuf, &txnmsg->CaptureDate, ATOL, 4, Ind );
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, Ind );
				break ;

			case 32:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->AcquirerInst, CHAR, len, Ind );
				memset( txnmsg->AcquirerInst, 0, sizeof( txnmsg->AcquirerInst ) );
				strcpy( txnmsg->AcquirerInst, InstId );
				break ;

			case 35:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->Track2, CHAR, len, Ind );
				memset( txnmsg->chn, 0, sizeof( txnmsg->chn ) );
				for( int i = 0; i < strlen( txnmsg->Track2 ); i++ )
				{
						if( txnmsg->Track2[ i ] == '=' )
							break;
						else
							txnmsg->chn[ i ] =  txnmsg->Track2[ i ];
				}
				trace( "chn [%s]\n", txnmsg->chn  );

				break;

			case 37:
				InBuf += fmt_in( InBuf, txnmsg->RefNum, CHAR, 12, Ind );
				break;

			case 39:
				InBuf += fmt_in( InBuf, &txnmsg->RespCode, ATOI, 2, Ind );
				break ;

			case 41:
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 16, Ind );
				break ;

			case 42:
				InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, 15, Ind );
				break ;

			case 43:
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, Ind );
				break;

			case 48:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind );
				memset( txnmsg->RsvFld6, 0, sizeof( txnmsg->RsvFld6 ) );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, len, Ind );
				break;

			case 49:
				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOL, 3, Ind );
				break;

			case 52:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->PINBlock, CHAR, len, Ind );
				break;

			case 53:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->NewPINBlock, CHAR, len, Ind );
				break;

			case 54:
				char tempStr[ 20 ], amtType[ 3 ];
				InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind );
				for( int i = 0; i < len; )
				{
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 2, Ind );
					i += 2;
					memset( amtType, 0, sizeof( amtType ) );
					InBuf += fmt_in( InBuf, amtType, CHAR, 2, Ind );
					i += 2;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 3, Ind );
					i += 3;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 1, Ind );
					i += 1;
					if( !strcmp( amtType, "02" ) )
						InBuf += fmt_in( InBuf, txnmsg->AvailBalance, CHAR, 12, Ind );
					else
						InBuf += fmt_in( InBuf, txnmsg->LedgerBalance, CHAR, 12, Ind );
					i += 12;
				}
				break ;

			case 60:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind + 1 );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld5, CHAR, len, Ind );
				break ;

			case 61:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->FromAcctSubType, CHAR, len, Ind );
				break ;

			case 62:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->ForwardBranchCode, CHAR, len, Ind );
				break ;

			case 63:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->ToAcctSubType, CHAR, len, Ind );
				break ;
			case 64:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, Ind );
				break ;
			case 65:
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, 6, Ind );
				break ;

			case 67:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->AcqBranchCode, CHAR, len, Ind );
				break ;

			case 70:
				InBuf += fmt_in( InBuf, &txnmsg->NetCode, ATOI, 3, Ind );
				trace( "Net Code [%03d]", txnmsg->NetCode );
				break ;


			case 102:
	/*			InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, Ind );
				if( txnmsg->TxnCode/10000 == 36 )
					memset( txnmsg->FromAccount, 0, sizeof( txnmsg->FromAccount ) );
				break;*/


				char TempBuf[ 25 ];
				int acctno;
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind  );
				memset( txnmsg->RsvFld6, 0, sizeof( txnmsg->RsvFld6 ) );
        	    InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, len, Ind  );
                memset( txnmsg->IssBranchCode, 0, sizeof( txnmsg->IssBranchCode ) );
                getToken( txnmsg->RsvFld6, txnmsg->IssBranchCode, '~', 2 );
                trace( "IssBranch = [%s]", txnmsg->IssBranchCode );
	            memset( txnmsg->FromAcctSubType, 0, sizeof( txnmsg->FromAcctSubType ) );
	            getToken( txnmsg->RsvFld6,txnmsg->FromAcctSubType, '~', 4 );
	            trace(  "AccountSubType = [%s]", txnmsg->FromAcctSubType );
				memset( TempBuf, 0, sizeof( TempBuf ) );
	            getToken( txnmsg->RsvFld6, TempBuf, '~', 5 );
				trace( "TempBuf[%s]", TempBuf );
				acctno = atoi( TempBuf );
				memset( txnmsg->FromAccount, 0, sizeof( txnmsg->FromAccount ) );
//				strcpy( txnmsg->FromAccount, txnmsg->IssBranchCode );
//				strcat( txnmsg->FromAccount, txnmsg->FromAcctSubType );
				//strcpy( txnmsg->FromAccount, TempBuf );
				sprintf( txnmsg->FromAccount, "%06s%06s%010d",txnmsg->IssBranchCode, txnmsg->FromAcctSubType, acctno );
	            trace( "AccountNo = [%s]", txnmsg->FromAccount );
	            break;


			case 103:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->ToAccount, CHAR, len, Ind );
				break;

			case 126:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, Ind );
				break ;

			case 127:
				/*
				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				InBuf += format_str( ( unsigned char * ) &len, InBuf, ATOI, 3 );
				InBuf += format_str( ( unsigned char * ) StmtBuf, InBuf, CHAR, len );
				dbg->trace( NORMAL, "Statement Buffer [%s]\n", StmtBuf );
				if ( len > 200 )
				{
					strncpy( DevMsg->RsvFld19, StmtBuf, 200 );
					strncpy( DevMsg->RsvFld20, StmtBuf+200, (len-200 ) );
				}
				else
					strcpy( DevMsg->RsvFld19, StmtBuf );
				*/
				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", Ind );
		}
	}
	return 1;
}


void EzPhone8583 :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 2600 + 1 ];
	char MsgBuffer[ 2600 + 1 ];
	char DeviceCommKey_TMK[ COMMKEY_SIZE + 1 ];
	while( 1 )
	{
		trace( "EzPhone8583 Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetLastSenderChannelName() );
			continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetLastSenderChannelName() );
			hex_dump( ( unsigned char * ) ISOMessage, MsgSize );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

			strcpy( txnmsg.SrcPort, GetLastSenderChannelName() );

			if( DecomposeISOMessage( ISOMessage, &txnmsg ) < 0 )
			{
				trace( "Error in Decomposing ISO Message from Port[%s]", GetLastSenderChannelName() );
				continue;
			}

			if( txnmsg.MsgType == 800 )
			{
				txnmsg.MsgType += 10;
				strcpy ( txnmsg.DestPort, GetLastSenderChannelName() );
				memset( DeviceCommKey_TMK, 0, sizeof( DeviceCommKey_TMK ) );
				if( GenDeviceCommKey( InstId, txnmsg.DestPort, DeviceCommKey_TMK ) < 0 )//Added Temp
				{
					trace( DEBUG_ERROR,"Unable to  generate Comm Key for the Device<%s>", txnmsg.DestPort );
					txnmsg.RespCode = EZLINK_RC_UnableToProcess;
				}
				else
					strcpy( txnmsg.PinKey, DeviceCommKey_TMK );

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
			else
			{
				txnmsg.MerchantType = 6014;
				txnmsg.PinVerFlg = 'Y';
				strcpy( txnmsg.AcqBranchCode, BranchCode );

				if( WriteChannel( "EzTxnMgr", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
					trace( "Error in Writing Message to Channel EzTxnMgr" );
				else
					trace( "Message Sucessfully Written to Channel EzTxnMgr" );
			}
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

int  EzPhone8583 :: GetTotalAcct(  const char *FileName )
{
	char FilePath[ FILENAME_SIZE + 1 ], SearchId[ TEMP +1 ], CfgVal[ TEMP + 1 ];
	int Count;
	EzCfgUtil cfg;

	memset( FilePath, 0, sizeof( FilePath ) );
	sprintf( FilePath, "%s/%s/%s", getenv("EZDIR_HOME"), "inf", FileName );

	if( cfg.cfg_open( FilePath ) < 0 )
	{
		trace( DEBUG_NORMAL, "Failed to open file [ %s ]", FilePath );
		return -1;
	}

	Count = cfg.cfg_group_count( "OAR" );
	if( Count < 0 )
	{
		trace( DEBUG_ERROR, "Failed to Count OAR Group");
		cfg.cfg_close();
		return -1;
	}
	else
	{
		cfg.cfg_close();
		return Count;
	}
}

int EzPhone8583 :: GetAcctNo(  const char *FileName, int Count, char *IssBranchCode, char *AccountType, char *ProductCode,char *AccountNo,char *Description )
{
	char FilePath[ FILENAME_SIZE + 1 ], SearchId[ TEMP +1 ], CfgVal[ TEMP + 1 ], Temp[ TEMP + 1 ];
	EzCfgUtil cfg;
	int AcctNo;

	memset( FilePath, 0, sizeof( FilePath ) );
	sprintf( FilePath, "%s/%s/%s", getenv("EZDIR_HOME"), "inf", FileName );

	if( cfg.cfg_open( FilePath ) < 0 )
	{
		trace( DEBUG_NORMAL, "Failed to open file [ %s ]", FilePath );
		return -1;
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	memset( SearchId, 0, sizeof( SearchId ) );
	sprintf( SearchId, "%s_%d", "OAR#VAR", Count );

	trace( DEBUG_NORMAL, "SearchId[ %s ]", SearchId );
	if( cfg.cfg_search( SearchId, CfgVal, 2 ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
	//	strcpy( IssBranchCode, CfgVal );
		strcpy( AccountType, CfgVal );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg.cfg_search( SearchId, CfgVal, 3 ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		return -1;
	}
	else
		trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
	cfg.cfg_close();

	strncpy( IssBranchCode, CfgVal, 6 );
	strncpy( ProductCode, CfgVal + 6, 6 );
	strcpy( AccountNo, CfgVal + strlen( CfgVal ) - 10 );
/*	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg.cfg_search( SearchId, CfgVal, 4) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
		strcpy( ProductCode, CfgVal );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg.cfg_search( SearchId, CfgVal, 5) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
		strcpy( AccountNo, CfgVal + strlen( CfgVal ) - 10 );
		AcctNo = atoi( AccountNo );
		memset( AccountNo, 0, sizeof( AccountNo ) );
		sprintf( AccountNo, "%d", AcctNo );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg.cfg_search( SearchId, CfgVal, 6) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
		cfg.cfg_close();
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
		strcpy( Description, CfgVal );
	}*/
	return 1;
}

void EzPhone8583 :: getToken( const char *msg, char *tmp, char ch, int count )
{
        int i = 0, j = 0, cnt = 0;
        for( i = 0; i < strlen( msg ); i++ )
        {
                if( msg[ i ] == ch )
                        cnt++;
                else if( cnt == count )
                        break;
                else if ( cnt + 1 == count )
                {
                        tmp[ j ] = msg[ i ];
                        j++;
                }
        }
}

int main( int argc, char **argv )
{
	EzPhone8583 EzPhone8583obj;
	EzPhone8583obj.InitEzPhone8583( argv[ 0 ] );
	EzPhone8583obj.ServiceRequest();
	return 1;
}
