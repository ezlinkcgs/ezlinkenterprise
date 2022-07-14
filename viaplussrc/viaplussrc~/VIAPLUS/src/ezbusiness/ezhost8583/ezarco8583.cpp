#include <ezbusiness/ezhost8583.h>

EzHost8583 :: EzHost8583()
{
}

EzHost8583 :: ~EzHost8583()
{
}

void EzHost8583 :: getToken( const char *FieldStr, char *TokenStr, char Token, int TokenNo )
{
	for( int i = 0, j = 0, cnt = 0; i < strlen( FieldStr ); i++ )
	{
		if( FieldStr[ i ] == Token )
			cnt++;
		else if ( cnt == TokenNo )
			break;
		else if ( cnt + 1 == TokenNo )
		{
			TokenStr[ j ] = FieldStr[ i ];
			j++;
		}
	}
}

void EzHost8583 :: removeDecimal( const char *SrcStr, char *DestStr )
{
	for( int i = 0, j = 0; i < strlen( SrcStr ); i++ )
	{
		if( SrcStr[ i ] != '.' )
		{
			DestStr[ j ] = SrcStr[ i ];
			j++;
		}
	}
}

void EzHost8583 :: removeLeadingZeros( const char *SrcStr, char *DestStr )
{
	int i = 0;
	trace( "SrcStr[%s]", SrcStr );
	for( i = 0; i < strlen( SrcStr ); i++ )
	{
		if( SrcStr[ i ] != '0' )
			break;
	}
	trace( "offset = [%d]  SrcStr[%s]", i, SrcStr + i );
	strcpy( DestStr, SrcStr + i );
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

	if( CreateChannel( TaskName, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", TaskName );
		trace( "^^^^^^^^^^^EzHost8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( RespFilePath, 0, sizeof( RespFilePath ) );
	sprintf( RespFilePath, "%s/%s/%s/%s%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", TaskName, "Resp.cfg" );

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", TaskName, "BitMap.cfg" );

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

int EzHost8583 :: getSwitchRespCode( int RespCode )
{
	EzCfgUtil cfgutil;
	char cfgval[ CFG_VAL_SIZE + 1 ], SearchId[ CFG_VAL_SIZE + 1 ], TempTxnCode[ 3 ];
	int ResponseCode;

	if( cfgutil.cfg_open( RespFilePath ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in opening file[ %s ]", RespFilePath );
		if( RespCode == 0 )
			return RespCode;
		else
			return 5;
	}

	memset( SearchId, 0, sizeof( SearchId ) );
	sprintf( SearchId, "%03d", RespCode );
	trace( DEBUG_NORMAL, "SearchId [%s]", SearchId );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( SearchId, cfgval, 2 ) < 0 )
	{
		if( RespCode == 0 )
			ResponseCode = RespCode;
		else
			ResponseCode = 5;
	}
	else
	{
		ResponseCode = atoi( cfgval );
	}
	cfgutil.cfg_close();
	return ResponseCode;
}

/*
void EzHost8583 :: getAccountStr( struct EzTxnMsg *txnmsg, const char *SrcAccount, char *DestAccount )
{
	EzCfgUtil cfgutil;
	char cfgval[ CFG_VAL_SIZE + 1 ], AcctBrkUpPath[ 150 ];
	int AcctOffset = 0, BrkCount;

	memset( AcctBrkUpPath, 0, sizeof( AcctBrkUpPath ) );
	sprintf( AcctBrkUpPath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

	if( cfgutil.cfg_open( AcctBrkUpPath ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Opening File[%s]", AcctBrkUpPath );
		strcpy( DestAccount, SrcAccount );
		return;
	}

	BrkCount = cfgutil.cfg_param_count( "ANSCB_HOST#ACCOUNT_BRKUP" );
	trace( DEBUG_NORMAL, "BrkCount[%d]", BrkCount );

	for( int i = 1; i < BrkCount; i++ )
	{
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( "ANSCB_HOST#ACCOUNT_BRKUP", cfgval, i + 1 ) < 0 )
			continue;
		if( !strcasecmp( cfgval, "$ISSBRANCHCODE" ) )
			AcctOffset += strlen( txnmsg->IssBranchCode );
		else if( !strcasecmp( cfgval, "$TXFBRANCHCODE" ) )
			AcctOffset += strlen( txnmsg->TxfBranchCode );
		else if( !strcasecmp( cfgval, "$ACQBRANCHCODE" ) )
			AcctOffset += strlen( txnmsg->AcqBranchCode );
		else if( !strcasecmp( cfgval, "$FROMPRODUCTCODE" ) )
			AcctOffset += strlen( txnmsg->FromAcctSubType );
		else if( !strcasecmp( cfgval, "$TOPRODUCTCODE" ) )
			AcctOffset += strlen( txnmsg->ToAcctSubType );
		else if( !strcasecmp( cfgval, "$FROMACCTTYPE" ) )
			AcctOffset += 2;
		else if( !strcasecmp( cfgval, "$TOACCTTYPE" ) )
			AcctOffset += 2;
		else if( !strcasecmp( cfgval, "$ACCOUNT" ) )
			break;
		else
			AcctOffset += strlen( cfgval );
	}
	trace( DEBUG_NORMAL, "AcctOffset[%d]", AcctOffset );
	strcpy( DestAccount, SrcAccount + AcctOffset );
	cfgutil.cfg_close();
}
*/

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
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ], AccountStr[ 33 ], Branch[ 10 ], TempNetworkId[ 16 ], TempInstId[ 10 ];
	int BranchCode;
	unsigned char BitMap[ 33 ];
	int len;
	BufOffset = OutBuf;
	char BusinessDate[ 10 ], FileName[ 200 ];
	FILE *BDateFP;

	trace( "MsgType = [%d]", txnmsg->MsgType );
	OutBuf += fmt_out( OutBuf, &txnmsg->MsgType, ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	if( txnmsg->TxnCode/10000 == 41 )
		strcpy( txnmsg->ToAccount, txnmsg->RsvFld1 );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}
	if( ( txnmsg->MerchantType == 6012 ) && (( txnmsg->TxnCode/10000 ) == 1) && (( txnmsg->TxnCode%10 ) == 1 )&& txnmsg->MsgType == 200 )
	{
		SetBitOn( BitMap, 64 );
		SetBitOn( BitMap, 65 );
		SetBitOn( BitMap, 66 );
	}
	else if( ( txnmsg->MerchantType == 6012 ) && ( txnmsg->TxnCode/10000 ) == 1 && txnmsg->MsgType == 200 )
	{
		SetBitOff( BitMap, 64 );
		SetBitOff( BitMap, 65 );
		SetBitOn( BitMap, 66 );
	}
	if( txnmsg->MerchantType == 6012 && ( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 || txnmsg->MsgType == 1220 ) )
	{
		SetBitOff( BitMap, 2 );
		SetBitOff( BitMap, 12 );
		SetBitOff( BitMap, 13 );
		SetBitOn( BitMap, 104 );
	}
	if( txnmsg->MerchantType == 6012 )
	{
		if( !strlen( txnmsg->RsvFld4 ) )
		{
			SetBitOff( BitMap, 64 );
			SetBitOff( BitMap, 65 );
		}
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
				/*char TempTxnCode[7];
				int TxnCode;
				if( ( txnmsg->TxnCode/10000 ) == 1 )
					TxnCode = txnmsg->TxnCode + 1;
				else
					TxnCode = txnmsg->TxnCode;
				memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
				sprintf( TempTxnCode, "%06d", TxnCode );
				OutBuf += fmt_out( OutBuf, TempTxnCode, CHAR, 6, bitno );*/
				OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, LTOA, 6, bitno );
				break ;

			case 4:
				char TempAmount[ 20 ], TempAmountStr[ 20 ];
				int Amount;

				//Different Cases for Amount

				memset( TempAmount, 0, sizeof( TempAmount ) );
				if( strlen( txnmsg->Amount ) <= 0 )
					strncpy( TempAmount, "000000000000", 12 );

				memset( TempAmount, 0, sizeof( TempAmount ) );
				getToken( txnmsg->Amount, TempAmount, '.', 2 );
				trace( "TempAmount[%s]", TempAmount );
				if( !strlen( TempAmount ) )
				{
					memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
					strcpy( TempAmountStr, txnmsg->Amount );
					strcat( TempAmountStr, "00" );
					memset( TempAmount, 0, sizeof( TempAmount ) );
					if( strlen( TempAmountStr ) < 12 )
					{
						memset( TempAmount, '0', 12 - strlen( TempAmountStr ) );
						strncpy( TempAmount + 12 - strlen( TempAmountStr ), TempAmountStr, strlen( TempAmountStr ) );
					}
					else
						strncpy( TempAmount,  TempAmountStr, 12 );
				}
				else if( strlen( TempAmount ) == 1 )
				{
					memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
					strcpy( TempAmountStr, txnmsg->Amount );
					strcat( TempAmountStr, "0" );
					trace( "TempAmountStr[%s]", TempAmountStr );
					memset( TempAmount, 0, sizeof( TempAmount ) );
					removeDecimal( TempAmountStr, TempAmount );
					trace( "TempAmount[%s]", TempAmount );
					memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
					strcpy( TempAmountStr, TempAmount );
					memset( TempAmount, 0, sizeof( TempAmount ) );
					if( strlen( TempAmountStr ) < 12 )
					{
						memset( TempAmount, '0', 12 - strlen( TempAmountStr ) );
						strncpy( TempAmount + 12 - strlen( TempAmountStr ), TempAmountStr, strlen( TempAmountStr ) );
					}
					else
						strncpy( TempAmount,  TempAmountStr, 12 );
				}
				else if( strlen( TempAmount ) >= 2 )
				{
					memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
					strcpy( TempAmountStr, txnmsg->Amount );
					trace( "TempAmountStr[%s]", TempAmountStr );
					memset( TempAmount, 0, sizeof( TempAmount ) );
					removeDecimal( TempAmountStr, TempAmount );
					trace( "TempAmount[%s]", TempAmount );
					memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
					strcpy( TempAmountStr, TempAmount );
					memset( TempAmount, 0, sizeof( TempAmount ) );
					if( strlen( TempAmountStr ) < 12 )
					{
						memset( TempAmount, '0', 12 - strlen( TempAmountStr ) );
						strncpy( TempAmount + 12 - strlen( TempAmountStr ), TempAmountStr, strlen( TempAmountStr ) );
					}
					else
						strncpy( TempAmount,  TempAmountStr, 12 );
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
				memset( FileName, 0, sizeof( FileName ) );
				sprintf( FileName, "%s/%s/%s.dat", getenv( "EZDIR_HOME" ), "cfg/businessdate", txnmsg->IssuerNetworkId );
				memset( BusinessDate, 0, sizeof( BusinessDate ) );
				BDateFP = fopen( FileName, "r" );
				if( BDateFP == NULL )
				{
					trace( " Error in Opening file [%s]", FileName );
					sprintf( BusinessDate, "%06d", txnmsg->TranDate );
				}
				else
				{
					fscanf( BDateFP, "%s", BusinessDate );
					fclose( BDateFP );
				}

				if( strlen( BusinessDate ) == 0 )
					sprintf( BusinessDate, "%06d", txnmsg->TranDate );
				trace( "Business Date of Network[%s] is [ %s ]", txnmsg->IssuerNetworkId, BusinessDate );
				//OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, BusinessDate, CHAR, 6, bitno );
				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 32:
				if( txnmsg->MsgType == 800 )
				{
					memset( TempInstId, 0, sizeof( TempInstId ) );
					strncpy( TempInstId, txnmsg->NetworkId, 4 );
					memset( Branch, 0, sizeof( Branch ) );
					strcpy( Branch, txnmsg->NetworkId + 4 );
					trace( "TempInstId[%s] Branch[%s]", TempInstId, Branch );
					BranchCode = atoi( Branch );
					memset( TempNetworkId, 0, sizeof( TempNetworkId ) );
					sprintf( TempNetworkId, "%s%03d", TempInstId, BranchCode );
					/*len = strlen( txnmsg->NetworkId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, CHAR, len, bitno );*/
				}
				else
				{
					memset( TempInstId, 0, sizeof( TempInstId ) );
					strncpy( TempInstId, txnmsg->AcqNetworkId, 4 );
					memset( Branch, 0, sizeof( Branch ) );
					strcpy( Branch, txnmsg->AcqNetworkId + 4 );
					trace( "TempInstId[%s] Branch[%s]", TempInstId, Branch );
					BranchCode = atoi( Branch );
					memset( TempNetworkId, 0, sizeof( TempNetworkId ) );
					sprintf( TempNetworkId, "%s%03d", TempInstId, BranchCode );
					/*len = strlen( txnmsg->AcqNetworkId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->AcqNetworkId, CHAR, len, bitno );*/
				}
				len = strlen( TempNetworkId );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, TempNetworkId, CHAR, len, bitno );
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

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 54:
				break;

			case 60:
				BranchCode = atoi( txnmsg->IssBranchCode );
				memset( Branch, 0, sizeof( Branch ) );
				sprintf( Branch, "%03d", BranchCode );
				trace( DEBUG_ERROR, "txnmsg->IssBranchCode[%s]", Branch );
				len = strlen( Branch );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, Branch, CHAR, len, bitno );
				/*trace( DEBUG_ERROR, "txnmsg->IssBranchCode[%s]", txnmsg->IssBranchCode );
				len = strlen( txnmsg->IssBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->IssBranchCode, CHAR, len, bitno );*/
				break ;

			case 61:
				trace( DEBUG_ERROR, "txnmsg->FromAcctSubType[%s]", txnmsg->FromAcctSubType );
				len = strlen( txnmsg->FromAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAcctSubType, CHAR, len, bitno );
				break;

			case 62:
				BranchCode = atoi( txnmsg->TxfBranchCode );
				memset( Branch, 0, sizeof( Branch ) );
				sprintf( Branch, "%03d", BranchCode );
				trace( DEBUG_ERROR, "txnmsg->TxfBranchCode[%s]", Branch );
				len = strlen( Branch );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, Branch, CHAR, len, bitno );
				/*trace( DEBUG_ERROR, "txnmsg->TxfBranchCode[%s]", txnmsg->TxfBranchCode );
				len = strlen( txnmsg->TxfBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->TxfBranchCode, CHAR, len, bitno );*/
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
				BranchCode = atoi( txnmsg->AcqBranchCode );
				memset( Branch, 0, sizeof( Branch ) );
				sprintf( Branch, "%03d", BranchCode );
				trace( DEBUG_ERROR, "txnmsg->AcqBranchCode[%s]", Branch );
				len = strlen( Branch );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, Branch, CHAR, len, bitno );
/*				len = strlen( txnmsg->AcqBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcqBranchCode, CHAR, len, bitno );*/
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

            case 80:
                len = strlen( txnmsg->NetworkId );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, CHAR, len, bitno );
                break ;

            case 81:
                len = strlen( txnmsg->RsvFld1 );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
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

			case 101:
				len = strlen( txnmsg->RsvFld6 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld6, CHAR, len, bitno );
				break ;

			case 102:
				memset( AccountStr, 0, sizeof( AccountStr ) );
				if( ( ( txnmsg->MerchantType == 6011 ) || ( txnmsg->MerchantType == 6014 ) ) && ( strlen( txnmsg->FromAccount ) > 7 ) )
					strcpy( AccountStr , txnmsg->FromAccount + 6 );
				else
					strcpy( AccountStr , txnmsg->FromAccount );

				trace( DEBUG_NORMAL, "AccountStr[%s]", AccountStr );
				len = strlen( AccountStr );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, AccountStr, CHAR, len, bitno );
				break;

			case 103:
				memset( AccountStr, 0, sizeof( AccountStr ) );
				if( ( txnmsg->MerchantType == 6011 ) && ( strlen( txnmsg->FromAccount ) > 7 ) )
					strcpy( AccountStr , txnmsg->ToAccount + 7 );
				else
					strcpy( AccountStr , txnmsg->ToAccount );

				trace( DEBUG_NORMAL, "AccountStr[%s]", AccountStr );
				len = strlen( AccountStr );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, AccountStr, CHAR, len, bitno );
				break;

			case 104:
				if( txnmsg->TxnCode/10000 == 38 )
				{
					len = strlen(  txnmsg->RsvFld3 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, CHAR, len, bitno );
				}
				else
				{
					len = strlen(  txnmsg->RsvFld2 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				}
				break;

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
	int len, BranchCode;
	char StmtBuf[ STMT_BUF_SIZE + 1 ], AccountStr[ 33 ], Branch[ 10 ], TempNetworkId[ 16 ], TempInstId[ 10 ];

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
				char TempAmount[ 20 ], TempAmountStr[ 20 ];

				/*
				if( txnmsg->MerchantType == 6011 )
				{

					int Amount;

					memset( TempAmount, 0, sizeof( TempAmount ) );
					InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
					if( ( txnmsg->TxnCode/10000 ) == 1 )
						Amount = atoi( TempAmount ) / 100;
					else
						Amount = atoi( TempAmount );
					sprintf( txnmsg->Amount, "%d", Amount );
				}
				else
					InBuf += fmt_in( InBuf, txnmsg->Amount, CHAR, 12, bitno );
				*/

				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				if( !strncmp( TempAmount, "000000000000", 12 ) )
				{
					memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
					strcpy( txnmsg->Amount, TempAmount );
				}
				else
				{
					memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
					removeLeadingZeros( TempAmount, TempAmountStr );
					trace( "TempAmountStr[%s]", TempAmountStr );
					memset( TempAmount, 0, sizeof( TempAmount ) );
					strncpy( TempAmount, TempAmountStr, strlen( TempAmountStr ) - 2 );
					trace( "TempAmount[%s]", TempAmount );
					strcat( TempAmount, "." );
					strcat( TempAmount, TempAmountStr + strlen( TempAmountStr ) - 2 );
					trace( "TempAmount[%s]", TempAmount );
					memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
					strcpy( txnmsg->Amount, TempAmount );
				}
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
				InBuf += fmt_in( InBuf, &txnmsg->BusinessDate, ATOL, 6, bitno );
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;

			case 32:
				memset( TempNetworkId, 0, sizeof( TempNetworkId ));
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, TempNetworkId, CHAR, len, bitno );

				memset( TempInstId, 0, sizeof( TempInstId ) );
				strncpy( TempInstId, TempNetworkId, 4 );
				memset( Branch, 0, sizeof( Branch ) );
				strcpy( Branch, TempNetworkId + 4 );
				trace( "TempInstId[%s] Branch[%s]", TempInstId, Branch );
				BranchCode = atoi( Branch );

				if( txnmsg->MsgType == 810 )
				{
/*					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->NetworkId, CHAR, len, bitno );*/
					memset( txnmsg->NetworkId, 0, sizeof( txnmsg->NetworkId) );
					sprintf( txnmsg->NetworkId, "%s%06d", TempInstId, BranchCode );
					trace( "txnmsg->NetworkId[%s]", txnmsg->NetworkId );
				}
				else
				{
/*					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->AcqNetworkId, CHAR, len, bitno );*/
					memset( txnmsg->AcqNetworkId, 0, sizeof( txnmsg->AcqNetworkId) );
					sprintf( txnmsg->AcqNetworkId, "%s%06d", TempInstId, BranchCode );
					trace( "txnmsg->AcqNetworkId[%s]", txnmsg->AcqNetworkId );
				}
				break ;

			case 37:
				InBuf += fmt_in( InBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 39:
				InBuf += fmt_in( InBuf, &txnmsg->RespCode, ATOI, 2, bitno );
				if( !txnmsg->RespCode )
					txnmsg->RespCode = getSwitchRespCode( txnmsg->RespCode );
				trace( DEBUG_NORMAL, "Mapped ResponseCode[%d]", txnmsg->RespCode );
				break ;

			case 41:
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break ;

			case 43:
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 54:
				char tempStr[ 20 ], amtType[ 3 ];
				char Balance[ 15 ];
				int TotBal ;
				memset( Balance, 0, sizeof( Balance ));
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
					InBuf += fmt_in( InBuf, Balance, CHAR, 12, bitno );
					TotBal = atoi( Balance );
					if( !strcmp( amtType, "02" ) )
					{
						if( !strncmp( Balance, "000000000000", 12 ) )
						{
							memset( txnmsg->AvailBalance, 0, sizeof( txnmsg->AvailBalance ) );
							strcpy( txnmsg->AvailBalance, "0.00" );
						}
						else
						{
							memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
							removeLeadingZeros( Balance, TempAmountStr );
							trace( "TempBalance[%s]", TempAmountStr );

							memset( Balance, 0, sizeof( Balance ) );
							strncpy( Balance, TempAmountStr, strlen( TempAmountStr ) - 2 );
							trace( "TempBalance[%s]", Balance );
							strcat( Balance, "." );
							strcat( Balance, TempAmountStr + strlen( TempAmountStr ) - 2 );
							trace( "Balance[%s]", Balance );
							memset( txnmsg->AvailBalance, 0, sizeof( txnmsg->AvailBalance ) );
							strcpy( txnmsg->AvailBalance, Balance );
						}
						//InBuf += fmt_in( InBuf, txnmsg->AvailBalance, CHAR, 12, bitno );
					}
					else
					{
						if( !strncmp( Balance, "000000000000", 12 ) )
						{
							memset( txnmsg->LedgerBalance, 0, sizeof( txnmsg->LedgerBalance ) );
							strcpy( txnmsg->LedgerBalance, "0.00" );
						}
						else
						{
							memset( TempAmountStr, 0, sizeof( TempAmountStr ) );
							removeLeadingZeros( Balance, TempAmountStr );
							trace( "TempBalance[%s]", TempAmountStr );

							memset( Balance, 0, sizeof( Balance ) );
							strncpy( Balance, TempAmountStr, strlen( TempAmountStr ) - 2 );
							trace( "TempBalance[%s]", Balance );
							strcat( Balance, "." );
							strcat( Balance, TempAmountStr + strlen( TempAmountStr ) - 2 );
							trace( "Balance[%s]", Balance );
							memset( txnmsg->LedgerBalance, 0, sizeof( txnmsg->LedgerBalance ) );
							strcpy( txnmsg->LedgerBalance, Balance );
						}
					}
					i += 12;
				}
				break ;

			case 60:
/*				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->IssBranchCode, CHAR, len, bitno );*/
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, Branch, CHAR, len, bitno );
				BranchCode = atoi( Branch );
				sprintf( txnmsg->IssBranchCode, "%06d", BranchCode );
				trace( "txnmsg->IssBranchCode [%s]", txnmsg->IssBranchCode );
				break ;

			case 61:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAcctSubType, CHAR, len, bitno );
				break ;

			case 62:
/*				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->TxfBranchCode, CHAR, len, bitno );*/
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, Branch, CHAR, len, bitno );
				BranchCode = atoi( Branch );
				sprintf( txnmsg->TxfBranchCode, "%06d", BranchCode );
				trace( "txnmsg->TxfBranchCode [%s]", txnmsg->TxfBranchCode );
				break ;

			case 63:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ToAcctSubType, CHAR, len, bitno );
				break ;

			case 64:
                len = strlen( txnmsg->RsvFld3 );
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, bitno );
                break ;

			case 65:
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

			case 66:
                len = strlen( txnmsg->RsvFld5 );
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld5, CHAR, len, bitno );
                break ;

			case 67:
/*				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcqBranchCode, CHAR, len, bitno );*/
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, Branch, CHAR, len, bitno );
				BranchCode = atoi( Branch );
				sprintf( txnmsg->AcqBranchCode, "%06d", BranchCode );
				trace( "txnmsg->AcqBranchCode [%s]", txnmsg->AcqBranchCode );
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
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, bitno );
                break ;

			case 90:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld2, CHAR, 44, bitno );
				break ;

			case 95:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld3, CHAR, 44, bitno );
				break ;

			case 101:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, len, bitno );
				break ;

			case 102:
				memset( AccountStr, 0, sizeof( AccountStr ) );
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, AccountStr, CHAR, len, bitno );
				memset( txnmsg->FromAccount, 0, sizeof( txnmsg->FromAccount ) );
				if( txnmsg->MerchantType == 6011 || txnmsg->MerchantType == 6014 )
				{
					strcat( txnmsg->FromAccount, txnmsg->IssBranchCode );
					strcat( txnmsg->FromAccount, AccountStr );
				}
				else
					strcpy( txnmsg->FromAccount, AccountStr );

				trace( DEBUG_NORMAL, "FromAccount[%s]", txnmsg->FromAccount );

				break;

			case 103:
				memset( AccountStr, 0, sizeof( AccountStr ) );
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, AccountStr, CHAR, len, bitno );
				memset( txnmsg->ToAccount, 0, sizeof( txnmsg->ToAccount ) );

				if( txnmsg->MerchantType == 6011 )
				{
					strcat( txnmsg->ToAccount, txnmsg->TxfBranchCode );
					strcat( txnmsg->ToAccount, txnmsg->ToAcctSubType );
					strcat( txnmsg->ToAccount, AccountStr );
				}
				else
					strcpy( txnmsg->ToAccount, AccountStr );

				trace( DEBUG_NORMAL, "ToAccount[%s]", txnmsg->ToAccount );

				break;

			case 104:
				if( txnmsg->TxnCode/10000 == 38 )
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, bitno );
				}
				else
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				}
				break;

			case 127:
				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, StmtBuf, CHAR, len, bitno );

				if( txnmsg->MsgType == 210 )
				{
					if( len > 200 )
					{
						strncpy( txnmsg->RsvFld1, StmtBuf, 200 );
						strncpy( txnmsg->RsvFld2, StmtBuf + 200, ( len - 200 ) );
					}
					else
						strcpy( txnmsg->RsvFld1, StmtBuf );
				}

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

			if( txnmsg.MsgType == 1220 )
			{
				trace(" Checking for LORO Posting ");
				if( !strcmp( txnmsg.AcqBranchCode, txnmsg.IssBranchCode ) )
				{
					trace("Both are Same Branch");
					continue;
				}
			}

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

