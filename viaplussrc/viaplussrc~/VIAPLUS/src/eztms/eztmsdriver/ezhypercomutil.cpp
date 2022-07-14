/*
 * ezhypercomutil.cpp
 *
 *  Created on: Sep 13, 2013
 *      Author: mohanraj
 */

#include <eztms/eztmsdriver.h>

int EzHypercomUtil :: initHypercomUtil( EzDebugUtil *dptr, EzDateTimeUtil *dtutil_ptr )
{
	char BitMapFile[ 256 ];
	this->dptr = dptr;
	this->dtutil_ptr = dtutil_ptr;
	fmtutilobj.initFmtUtil( dptr );
	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "tms", "EzHypercomBitMap.cfg" );
	if( isoutilobj.initEzISO8583Util( BitMapFile, dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ISO8583Util...." );
		dptr->trace( "^^^^^^^^^^^EzPOSDriver Ended Abnormally^^^^^^^^^^^^^");
		return -1;
	}
	return 1;
}

int EzHypercomUtil :: getTMSTxnCode( int POSTxnCode )
{
	return ( isoutilobj.getInBoundSwitchTxnCode( POSTxnCode ) );
}

int EzHypercomUtil :: getTerminalTxnCode( int SwitchTxnCode )
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

int EzHypercomUtil :: decomposeMsg( char *InBuf, struct EzTxnMsg *tmsmsg )
{
	unsigned char BitMap[ 33 ];
	int len, digitoffset = 0;
	char TempStr[ 50 ], DateStr[ 20 ];

	//Message Type
	InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->MsgType, FMT_BCDTOI, 4 , 0 );

	//Primary BitMap
	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmtutilobj.fmt_in( InBuf, BitMap, FMT_MOVE, 8, 1 );
	if( isoutilobj.IsBitSet( BitMap, 1 ) )
	{
		//Secondary BitMap
		InBuf += fmtutilobj.fmt_in( InBuf, BitMap + 8, FMT_MOVE, 8, 1 );
	}

	if( isoutilobj.IsBitSet( BitMap, 1 ) )
	{
		if( isoutilobj.checkValidBitMap( tmsmsg->MsgType, BitMap, 128 ) < 0 )
		{
			dptr->trace( "Not a Valid BitMap...Dropping Message..." );
			return -1;
		}
	}
	else
	{
		if( isoutilobj.checkValidBitMap( tmsmsg->MsgType, BitMap, 64 ) < 0 )
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
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->chn, FMT_BCDTOS, len, bitno );
				break ;

			case 3:

				//TxnCode
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->TxnCode, FMT_BCDTOI, 6, bitno );
				break ;

			case 4:

				//Amount
				char TempAmount[13], Decimal[ 3 ], Amount[ 11 ];
				int temp;
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmtutilobj.fmt_in( InBuf, TempAmount, FMT_BCDTOA, 12, bitno );
				strncpy( Amount, TempAmount, 10 );
				strncpy( Decimal, TempAmount+10, 2 );
				sprintf( tmsmsg->Amount, "%d.%s", atoi(Amount), Decimal );
				break ;

			case 7:

				break ;

			case 11:

				//TraceNo
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->TraceNo, FMT_BCDTOI, 6, bitno );
				break ;

			case 12:

				//Local Time
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->LocalTime, FMT_BCDTOI, 6, bitno );
				break ;

			case 13:

				//Local Date
				memset( DateStr, 0, sizeof( DateStr ) );
				InBuf += fmtutilobj.fmt_in( InBuf, DateStr, FMT_BCDTOA, 4, bitno );
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, DateStr + 2, 2 );
				strncpy( TempStr + 2, DateStr, 2 );
				dtutil_ptr->getSysDate();
				strcpy( TempStr + 4, dtutil_ptr->getSysYear() );
				tmsmsg->LocalDate = atoi( TempStr );
				break ;

			case 14:

				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->ExpiryDate, FMT_BCDTOI, 4, bitno );
				break ;

			case 22:

				//POS Entry Code
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->PosEntryCode, FMT_BCDTOI, 3, bitno );
				break ;

			case 24:

				//NII->Network International Identifier
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld5, FMT_BCDTOA, 3, bitno );
				break ;

			case 25:

				//POS Condition Code
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->PosConditionCode, FMT_BCDTOI, 2, bitno );
				break ;

			case 35:

				//Track2 Data
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_BCDTOI, 2, bitno );
				fmtutilobj.format_str( 6, len, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->Track2, FMT_BCDTOA, len, bitno );
				for( int i = 0; i < strlen( tmsmsg->Track2 ); i++ )
				{
					if( isdigit( tmsmsg->Track2[ i ] ) )
					{
						digitoffset = i;
						break;
					}
				}

				memset( tmsmsg->chn, 0, sizeof( tmsmsg->chn ) );
				for( int i = digitoffset; i < strlen( tmsmsg->Track2 ); i++ )
				{
					if( !isdigit( tmsmsg->Track2[ i ] ) )
						break;
					else
						tmsmsg->chn[ i ] = tmsmsg->Track2[ i ];
				}

				break ;

			case 37:

				//Reference No
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RefNum, FMT_CHAR, 12, bitno );
				break ;

			case 41:

				//TerminalId
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->TerminalId, FMT_CHAR, 8, bitno );
				break ;

			case 42:

				//MerchantId
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->AcceptorId, FMT_CHAR, 15, bitno );
				break ;

			case 49:

				//Acqurier Currency Code
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->AcqCurrencyCode, FMT_BCDTOI, 3, bitno );
				break ;

			case 52:

				//PIN Block
				fmtutilobj.format_str( 0, 16, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->PINBlock, FMT_BCDTOA, 16, bitno );
				break;

			case 54:

				//Additional Ammounts
				break ;

			case 60:

				//Private Use - BatchId For 500, Origainal Data For 320
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_BCDTOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld1, FMT_CHAR, len, bitno );

				memset( tmsmsg->MachineId, 0, sizeof( tmsmsg->MachineId ) );
				strcpy( tmsmsg->MachineId, tmsmsg->RsvFld1 );
				break;

			case 61:

				//Private Use - Total Count, Total Amount
				break;

			case 62:

				//Private Use - InVoiceNo

				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_BCDTOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->AuthNum, FMT_CHAR, len, bitno );
				break;

			case 63:

				//Private Use - Original Data
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_BCDTOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
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

int EzHypercomUtil :: composeMsg( struct EzTxnMsg *tmsmsg, char *OutBuf )
{
	char *BufOffset;

	unsigned char BitMap[ 33 ];
	char TempStr1[ 50 ], TempStr2[ 50 ];

	int len;
	BufOffset = OutBuf;

	OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->MsgType, FMT_ITOBCD, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	if( isoutilobj.LoadBitMap( BitMap, tmsmsg->MsgType, tmsmsg->TxnCode, tmsmsg->RespCode ) < 0 )
	{
		dptr->trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", tmsmsg->MsgType, tmsmsg->TxnCode, tmsmsg->RespCode );
		return -1;
	}
	OutBuf += fmtutilobj.fmt_out( OutBuf, BitMap, FMT_MOVE, 8, 1 );
	if( isoutilobj.IsBitSet( BitMap, 1 ) )
		OutBuf += fmtutilobj.fmt_out( OutBuf, BitMap + 8, FMT_MOVE, 8, 1 );


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
				len = strlen( tmsmsg->chn );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOBCD, 2, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->chn, FMT_ITOBCD, len, bitno );
				break;

			case 3:

				//TxnCode
				len = getTerminalTxnCode( tmsmsg->TxnCode );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOBCD, 6, bitno );
				break;
/*
			case 4:

				//Amount
                                dptr->trace("(ezhypercomutil.cpp)tmsmsg->Amount [%s]", tmsmsg->Amount );
                                if(!strlen(tmsmsg->Amount)){strcpy(tmsmsg->Amount,"000000000000");dptr->trace("Trace(tmsmsg->Amount[%s])",tmsmsg->Amount);}
				/*else 
				{
					IntAmt = atol(tmsmsg->Amount);dptr->trace("tmsmsg->Amount[%ld]",IntAmt);
				}*/
//                                OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr1, FMT_ATOBCD, 12, bitno );
/*				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->Amount, FMT_ATOBCD, 12, bitno );
				break;*/
                        case 4:
                                /*Amount*/
				long IntAmt;
                                dptr->trace("(ezhypercomutil.cpp)tmsmsg->Amount [%s]", tmsmsg->Amount );
                                if(!strlen(tmsmsg->Amount)){strcpy(TempStr1,"000000000000");dptr->trace("Trace(TempStr1[%s])",TempStr1);}
                                else 
                                {
                                        IntAmt = atol(tmsmsg->Amount);dptr->trace("tmsmsg->Amount[%ld]",IntAmt);
					sprintf( TempStr1, "%010ld00", IntAmt);
                                }
                                OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr1, FMT_ATOBCD, 12, bitno );
                                break;

			case 11:

				//TraceNo
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->TraceNo, FMT_ITOBCD, 6, bitno );
				break;

			case 12:

				//LocalTime
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->LocalTime, FMT_ITOBCD, 6, bitno );
				break;

			case 13:

				//LocalDate
				memset( TempStr1, 0, sizeof( TempStr1 ) );
				sprintf( TempStr1, "%06d", tmsmsg->LocalDate );
				memset( TempStr2, 0, sizeof( TempStr2 ) );
				strncpy( TempStr2, TempStr1 + 2, 2 );
				strncpy( TempStr2 + 2, TempStr1 , 2 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr2, FMT_ATOBCD, 4, bitno );
				break ;

			case 14:

				//Expiry Date
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->ExpiryDate, FMT_ITOBCD, 4, bitno );
				break;

			case 22:

				//POS Entry Code
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->PosEntryCode, FMT_ITOBCD, 3, bitno );
				break;

			case 24:

				//Network International ID
				dptr->trace( "tmsmsg->RsvFld5[%s]", tmsmsg->RsvFld5 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld5, FMT_ATOBCD, 3, bitno );
				break;

			case 25:

				//POS Condition Code
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->PosConditionCode, FMT_ITOBCD, 2, bitno );
				break;

			case 37:

				//RefNum
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RefNum, FMT_CHAR, 12, bitno );
				break ;

			case 38:

				//AuthCode
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->AuthCode, FMT_ITOA, 6, bitno );
				break ;

			case 39:

				//RespCode
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->RespCode, FMT_ITOA, 2, bitno );
				break;

			case 41:

				//TerminalId
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->TerminalId, FMT_CHAR, 8, bitno );
				break ;

			case 42:

				//MerchantId
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->AcceptorId, FMT_CHAR, 15, bitno );
				break ;

			case 52:

				//PIN Block
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->PINBlock, FMT_STOBCD, 16, bitno );
				break ;

			case 54:
				break;

			case 60:

				//BatchId
				len = strlen( tmsmsg->RsvFld1 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOBCD, 3, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld1, FMT_CHAR, len, bitno );

				break ;

			case 61:

				//TxnCount

				break;

			case 62:
				if( tmsmsg->MsgType == 810 )
				{
					//Private Use - InVoiceNo
					len = strlen( tmsmsg->RsvFld4 );
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOBCD, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld4, FMT_CHAR, len, bitno );
				}
				else
				{
					if( tmsmsg->TxnCode/10000 == 30 )
					{
						//Private Use - Available Balance
						len = strlen( tmsmsg->AvailBalance );
						OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOBCD, 3, bitno );
						OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->AvailBalance, FMT_CHAR, len, bitno );
					}
					else
					{
						//Private Use - InVoiceNo
						len = strlen( tmsmsg->AuthNum );
						OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOBCD, 3, bitno );
						OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->AuthNum, FMT_CHAR, len, bitno );
					}
				}
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




