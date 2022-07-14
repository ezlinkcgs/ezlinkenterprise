#include <ezbusiness/ezposdriver.h>

int EzHypercomUtil :: initHypercomUtil( EzDebugUtil *dptr, EzDateTimeUtil *dtutil_ptr )
{
	char BitMapFile[ 256 ];
	this->dptr = dptr;
	this->dtutil_ptr = dtutil_ptr;
	fmtutilobj.initFmtUtil( dptr );
	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "pos", "EzHypercomBitMap.cfg" );
	if( isoutilobj.initEzISO8583Util( BitMapFile, dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ISO8583Util...." );
		dptr->trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		return -1;
	}
	return 1;
}

int EzHypercomUtil :: getSwitchTxnCode( int POSTxnCode )
{
	return ( isoutilobj.getInBoundSwitchTxnCode( POSTxnCode ) );
}

int EzHypercomUtil :: getPOSTxnCode( int SwitchTxnCode )
{
	return ( isoutilobj.getOutBoundExtTxnCode( SwitchTxnCode ) );
}

void EzHypercomUtil :: formatAmt( const char *Amount, char *OutStr, int Len )
{
	char formatStr[ 50 ];
	memset( formatStr, 0, sizeof( formatStr ) );
	for( int i = 0, j = 0; i < strlen( Amount ); i++ )
	{
		if( Amount[ i ] != '.' )
		{
			formatStr[ j ] = Amount[ i ];
			j++;
		}
	}
	memset( OutStr, '0', Len - strlen( formatStr ) );
	strcpy( OutStr + Len - strlen( formatStr ), formatStr );
}

int EzHypercomUtil :: decomposePOSMsg( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int len, digitoffset = 0;
	char TempStr[ 50 ], DateStr[ 20 ];

	//Message Type
	InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->MsgType, FMT_BCDTOI, 4 , 0 );

	//Primary BitMap
	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmtutilobj.fmt_in( InBuf, BitMap, FMT_MOVE, 8, 1 );
	if( isoutilobj.IsBitSet( BitMap, 1 ) )
	{
		//Secondary BitMap
		InBuf += fmtutilobj.fmt_in( InBuf, BitMap + 8, MOVE, 8, 1 );
	}

	if( isoutilobj.IsBitSet( BitMap, 1 ) )
	{
		if( isoutilobj.checkValidBitMap( txnmsg->MsgType, BitMap, 128 ) < 0 )
		{
			dptr->trace( "Not a Valid BitMap...Dropping Message..." );
			return -1;
		}
	}
	else
	{
		if( isoutilobj.checkValidBitMap( txnmsg->MsgType, BitMap, 64 ) < 0 )
		{
			dptr->trace( "Not a Valid BitMap...Dropping Message..." );
			return -1;
		}
	}

	for( int bitno = 1; bitno <= 128; bitno++ )
	{
		if( !isoutilobj.IsBitSet( BitMap, bitno ) )
			continue;

		if( bitno > 64 )
		{
			if( !isoutilobj.IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( bitno )
		{
			case 1:
			// Seconday Bit Map

			break;

			case 2:

				//CHN
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_BTOI, 1, bitno );
				fmtutilobj.format_str( 6, len - 4, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->chn, FMT_BCDTOS, len, bitno );
				break ;

			case 3:

				//TxnCode
				InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->TxnCode, FMT_BCDTOI, 6, bitno );
				break ;

			case 4:

				//Amount
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->Amount, FMT_BCDTOA, 12, bitno );
				break ;

			case 7:

				break ;

			case 11:

				//TraceNo
				InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->TraceNo, FMT_BCDTOI, 6, bitno );
				break ;

			case 12:

				//Local Time
				InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->LocalTime, FMT_BCDTOI, 6, bitno );
				break ;

			case 13:

				//Local Date
				memset( DateStr, 0, sizeof( DateStr ) );
				InBuf += fmtutilobj.fmt_in( InBuf, DateStr, BCDTOA, 4, bitno );
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, DateStr + 2, 2 );
				strncpy( TempStr + 2, DateStr, 2 );
				dtutil_ptr->getSysDate();
				strcpy( TempStr + 4, dtutil_ptr->getSysYear() );
				txnmsg->LocalDate = atoi( TempStr );
				break ;

			case 14:

				InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->ExpiryDate, FMT_BCDTOI, 4, bitno );
				break ;

			case 22:

				//POS Entry Code
				InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->PosEntryCode, FMT_BCDTOI, 3, bitno );
				break ;

			case 24:

				//NII->Network International Identifier
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->RsvFld5, FMT_BCDTOA, 3, bitno );
				break ;

			case 25:

				//POS Condition Code
				InBuf += fmtutilobj.fmt_in( InBuf, &txnmsg->PosConditionCode, FMT_BCDTOI, 2, bitno );
				break ;

			case 35:

				//Track2 Data
				InBuf += fmtutilobj.fmt_in( InBuf, &len, BCDTOI, 2, bitno );
				fmtutilobj.format_str( 6, len, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->Track2, FMT_BCDTOA, len, bitno );
				for( int i = 0; i < strlen( txnmsg->Track2 ); i++ )
				{
					if( isdigit( txnmsg->Track2[ i ] ) )
					{
						digitoffset = i;
						break;
					}
				}

				memset( txnmsg->chn, 0, sizeof( txnmsg->chn ) );
				for( int i = digitoffset; i < strlen( txnmsg->Track2 ); i++ )
				{
					if( !isdigit( txnmsg->Track2[ i ] ) )
						break;
					else
						txnmsg->chn[ i ] = txnmsg->Track2[ i ];
				}

				break ;

			case 37:

				//Reference No
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 41:

				//TerminalId
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 42:

				//MerchantId
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->AcceptorId, CHAR, 15, bitno );
				break ;

			case 52:

				//PIN Block
				fmtutilobj.format_str( 0, 16, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->PINBlock, BCDTOA, 16, bitno );
				break;

			case 54:

				//Additional Ammounts
				break ;

			case 60:

				//Private Use - BatchId For 500, Origainal Data For 320
				if( txnmsg->MsgType == 500 )
				{
					InBuf += fmtutilobj.fmt_in( InBuf, &len, BCDTOI, 3, bitno );
					InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->BatchId, CHAR, len, bitno );
				}
				else
				{
					InBuf += fmtutilobj.fmt_in( InBuf, &len, BCDTOI, 3, bitno );
					InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->AuthNum, CHAR, len, bitno );
				}
				break;

			case 61:

				//Private Use - Total Count, Total Amount
				break;

			case 62:

				//Private Use - InVoiceNo

				InBuf += fmtutilobj.fmt_in( InBuf, &len, BCDTOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->AuthNum, CHAR, len, bitno );
				break;

			case 63:

				//Private Use - Original Data
				InBuf += fmtutilobj.fmt_in( InBuf, &len, BCDTOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				break;

			case 64:

				//MAC Code
				break ;

			default:
				dptr->trace( "Unhandled bit in ISO Decompose [%d]", bitno );
		}
	}
	return 1;
}

int EzHypercomUtil :: composePOSMsg( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset;

	unsigned char BitMap[ 33 ];
	char TempStr1[ 50 ], TempStr2[ 50 ];

	int len;
	BufOffset = OutBuf;

	OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->MsgType, ITOBCD, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	if( isoutilobj.LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		dptr->trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}
	OutBuf += fmtutilobj.fmt_out( OutBuf, BitMap, MOVE, 8, 1 );
	if( isoutilobj.IsBitSet( BitMap, 1 ) )
		OutBuf += fmtutilobj.fmt_out( OutBuf, BitMap + 8, MOVE, 8, 1 );


	for( int bitno = 1; bitno <= 128; bitno++ )
	{
		if( !isoutilobj.IsBitSet( BitMap, bitno ) )
			continue;

		if( bitno > 64 )
		{
			if( !isoutilobj.IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( bitno )
		{
			case 1:

				// Seconday Bit Map
				break;

			case 2:

				//CHN
				len = strlen( txnmsg->chn );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, ITOBCD, 2, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->chn, ITOBCD, len, bitno );
				break;

			case 3:

				//TxnCode
				len = getPOSTxnCode( txnmsg->TxnCode );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, ITOBCD, 6, bitno );
				break;

			case 4:

				//Amount
				memset( TempStr1, 0, sizeof( TempStr1 ) );
				formatAmt( txnmsg->Amount, TempStr1, 12 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr1, ATOBCD, 12, bitno );
				break;

			case 11:

				//TraceNo
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->TraceNo, ITOBCD, 6, bitno );
				break;

			case 12:

				//LocalTime
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->LocalTime, ITOBCD, 6, bitno );
				break;

			case 13:

				//LocalDate
				memset( TempStr1, 0, sizeof( TempStr1 ) );
				sprintf( TempStr1, "%06d", txnmsg->LocalDate );
				memset( TempStr2, 0, sizeof( TempStr2 ) );
				strncpy( TempStr2, TempStr1 + 2, 2 );
				strncpy( TempStr2 + 2, TempStr1 , 2 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr2, ATOBCD, 4, bitno );
				break ;

			case 14:

				//Expiry Date
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->ExpiryDate, ITOBCD, 4, bitno );
				break;

			case 22:

				//POS Entry Code
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->PosEntryCode, ITOBCD, 3, bitno );
				break;

			case 24:

				//Network International ID
				dptr->trace( "txnmsg->RsvFld5[%s]", txnmsg->RsvFld5 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->RsvFld5, ATOBCD, 3, bitno );
				break;

			case 25:

				//POS Condition Code
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->PosConditionCode, ITOBCD, 2, bitno );
				break;

			case 37:

				//RefNum
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 38:

				//AuthCode
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->AuthCode, ITOA, 6, bitno );
				break ;

			case 39:

				//RespCode
				OutBuf += fmtutilobj.fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 2, bitno );
				break;

			case 41:

				//TerminalId
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 42:

				//MerchantId
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->AcceptorId, CHAR, 15, bitno );
				break ;

			case 52:

				//PIN Block
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->PINBlock, STOBCD, 16, bitno );
				break ;

			case 54:
				break;

			case 60:

				//BatchId
				if( txnmsg->MsgType == POS_SETTLEMENTRESPONSE )
				{
					len = strlen( txnmsg->BatchId );
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, ITOBCD, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->BatchId, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->AuthNum );
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, ITOBCD, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->AuthNum, CHAR, len, bitno );
				}

				break ;

			case 61:

				//TxnCount

				break;

			case 62:

				//Private Use - InVoiceNo
				len = strlen( txnmsg->AuthNum );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, ITOBCD, 3, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, txnmsg->AuthNum, ATOBCD, len, bitno );

				break ;

			case 63:

				break ;

			case 64:

				break ;

			default:

				dptr->trace( "Unhandled bit in iso8583" );
				break ;
		}
	}
	return( OutBuf - BufOffset );
}

