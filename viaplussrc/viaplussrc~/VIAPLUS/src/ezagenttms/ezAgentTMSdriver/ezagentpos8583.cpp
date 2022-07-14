#include <ezagenttms/ezagenttmsdriver.h>

int EzCastles8583 :: initCastles8583( EzDebugUtil *dptr, EzDateTimeUtil *dtutil_ptr, struct EzMMSMerchantProfile *merchantprofile_ptr, struct EzMMSTerminalProfile *terminalprofile_ptr, EzAmountUtil *amtutil_ptr )
{
	char BitMapFile[ 256 ];
	this->dptr = dptr;
	this->dtutil_ptr = dtutil_ptr;
	fmtutilobj.initFmtUtil( dptr );
	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "tms", "EzAgentTMSBitMap.cfg" );
	if( isoutilobj.initEzISO8583Util( BitMapFile, dptr ) < 0 )
		return -1;
/*	if( emvutil.initEMVUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing EMVUtil..." );
		return -1;
	}
*/
	tmsdrvrtemplate.initTMSDriverTemplate( dptr, amtutil_ptr );
	this->merchantprofile_ptr = merchantprofile_ptr;
	this->terminalprofile_ptr = terminalprofile_ptr;
	this->amtutil_ptr = amtutil_ptr;
	return 1;
}

int EzCastles8583 :: getTMSTxnCode( int TerminalTxnCode )
{
	return ( isoutilobj.getInBoundSwitchTxnCode( TerminalTxnCode ) );
}

int EzCastles8583 :: getTerminalTxnCode( int TMSTxnCode )
{
	return ( isoutilobj.getOutBoundExtTxnCode( TMSTxnCode ) );
}

int EzCastles8583 :: decomposeMsg( char *InBuf, struct EzTxnMsg *tmsmsg, int ProtocolFlag )
{
	unsigned char BitMap[ 33 ];
	int len, digitoffset = 0;
	char TempStr[ 50 ], DateStr[ 20 ], TDate[ 10 ], TempStr1[50];

	tmsmsg->ChipEnabled = 'N';
	tmsmsg->PinVerFlg = 'N';

/*	if( ProtocolFlag == POS_PROTOCOL_HYPERCOM )
	{
		dptr->trace( "HYPERCOM" );
		//TCPHEADER
		memset( tmsmsg->private_use.RsvFld3, 0, sizeof( tmsmsg->private_use.RsvFld3 ) );
		InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->private_use.RsvFld3, BCDTOA, 10, 0 );
		dptr->trace( "TCPIPHeader<%s>", tmsmsg->private_use.RsvFld3 );
	}*/

	//Message Type
	InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->MsgType, FMT_ATOI, 4 , 0 );

	if( tmsmsg->MsgType == 220 )
		tmsmsg->MsgType = 200;

	//Primary BitMap
	memset( BitMap, 0, sizeof( BitMap ) );
	//InBuf += fmtutilobj.fmt_in( InBuf, BitMap, FMT_ATOI, 8, 1 );
	InBuf += fmtutilobj.fmt_in( InBuf, BitMap, FMT_ATOH, 16, 1 );

	if( isoutilobj.IsBitSet( BitMap, 1 ) )
	{
		//Secondary BitMap
		//InBuf += fmtutilobj.fmt_in( InBuf, BitMap + 8, FMT_ATOI, 8, 1 );
//		InBuf += fmtutilobj.fmt_in( InBuf, BitMap + 16, FMT_ATOH, 16, 1 );
		InBuf += fmtutilobj.fmt_in( InBuf, BitMap + 8, FMT_ATOH, 16, 1 );
	}
/*
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
*/
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
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				fmtutilobj.format_str( 6, len - 4, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->chn, FMT_CHAR, len, bitno );
				tmsmsg->ManualEntry = 'C';
				memset( tmsmsg->RsvFld3, 0, sizeof( tmsmsg->RsvFld3 ) );
				strcpy( tmsmsg->RsvFld3, "760");
				break ;

			case 3:

				//TxnCode
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->TxnCode, FMT_ATOI, 6, bitno );
				break ;

			case 4:

				//Amount
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->Amount, FMT_CHAR, 12, bitno );
				memset( TempStr, 0, sizeof( TempStr ) );
				amtutil_ptr->normalizeAmt( tmsmsg->Amount, TempStr, 2 );
				memset( tmsmsg->Amount, 0, sizeof( tmsmsg->Amount ) );
				strcpy( tmsmsg->Amount, TempStr );
				break ;

			case 7:

				break ;

			case 11:

				//TraceNo
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->TraceNo, FMT_ATOI, 6, bitno );
				//setting tracenum as 0 to
				//if( tmsmsg->MsgType == 200 && ( tmsmsg->TxnCode == 0 || tmsmsg->TxnCode/10000 == 61 ) )  
				//	tmsmsg->TraceNo = 0;
				break ;

			case 12:

				//Local Time
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->LocalTime, FMT_ATOI, 6, bitno );
				break ;

			case 13:

				//Local Date
				/*if( ProtocolFlag == POS_PROTOCOL_HYPERCOM )
				{
					memset( TempStr, 0, sizeof( TempStr ) );
					InBuf += fmtutilobj.fmt_in( InBuf, TempStr, ATOA, 4, bitno );
					memset( TDate, 0, sizeof( TDate ) );
					strncpy( TDate, &TempStr[2], 2 );
					strncat( TDate, TempStr, 2 );
					strcat( TDate, dtutil_ptr->getSysYear() );
					tmsmsg->LocalDate = atoi( TDate );
				}
				elsei*/
					InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->LocalDate, FMT_ATOI, 6, bitno );
				break ;

			case 14:

				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->ExpiryDate, FMT_ATOI, 4, bitno );
				break ;

			case 22:

				//POS Entry Code
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->PosEntryCode, FMT_ATOI, 3, bitno );
				break ;
			/*
			case 23:
				//PAN Sequence Number
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->emvbuf.PANSeqNo, FMT_ATOI, 4, bitno );
				break ;
*/
			case 24:

				//NII->Network International Identifier
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld5, FMT_ATOI, 3, bitno );
				break ;

			case 25:

				//POS Condition Code
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->PosConditionCode, FMT_ATOI, 2, bitno );
				break ;

			case 35:

				//Track2 Data
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				fmtutilobj.format_str( 6, len - 4, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->Track2, FMT_CHAR, len, bitno );

				//dptr->trace( "Track2Data[%s]", tmsmsg->Track2 );
				//Added to Remove F0 data at the end
				/*
				memset( TempStr, 0, sizeof( TempStr ) );
				strcpy( TempStr, tmsmsg->Track2 );
				memset( tmsmsg->Track2, 0, sizeof( tmsmsg->Track2 ) );
				for( int i = 0; i < strlen( TempStr ); i++ )
				{
					if( TempStr[ i ] == 'F' )
					{
						dptr->trace("F [%d]", i );
						strncpy( tmsmsg->Track2, TempStr, i );
						break;
					}
				}

				dptr->trace( "Track2Data[%s]", tmsmsg->Track2 );
				*/

				for( int i = 0; i < strlen( tmsmsg->Track2 ); i++ )
				{
					if( isdigit( tmsmsg->Track2[ i ] ) )
					{
						digitoffset = i;
						break;
					}
				}
				memset( tmsmsg->chn, 0, sizeof( tmsmsg->chn ) );
				for( int i = digitoffset, j = 0; i < strlen( tmsmsg->Track2 ); i++ )
				{
					if( !isdigit( tmsmsg->Track2[ i ] ) )
						break;
					else
					{
						tmsmsg->chn[ j ] = tmsmsg->Track2[ i ];
						j++;
					}
				}
				break ;

			case 37:

				//Reference No
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RefNum, FMT_CHAR, 12, bitno );
				break ;

			case 39:

				//RespCode
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->RespCode, FMT_ATOI, 2, bitno );
				break;

			case 41:
				//TerminalId
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->TerminalId, FMT_CHAR, 8, bitno );
				break ;
					
			
			
			case 42:

				//MerchantId
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->AcceptorId, FMT_CHAR, 15, bitno );
				break ;

                        case 43:

                                //TerminalLocation
                                InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->TerminalLocation, FMT_CHAR, 40, bitno );
                                break;
			
			case 48:

                                InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld1, FMT_CHAR, 3, bitno );
				//InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld1, BCDTOI, 3, bitno );
				dptr->trace( "RsvFld1[%s]" , tmsmsg->RsvFld1 );
				break ;
				
			case 49:

				//MerchantId
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->AcqCurrencyCode, FMT_ATOI, 3, bitno );
				break ;

			case 51:

				//New PIN Block
				fmtutilobj.format_str( 0, 16, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->NewPINBlock, FMT_CHAR, 16, bitno );
				break;

			case 52:

				//PIN Block
				fmtutilobj.format_str( 0, 16, '*' );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->PINBlock, FMT_CHAR, 16, bitno );
				tmsmsg->PinVerFlg = 'Y';
				break;

			case 53:

				//Confirm PIN Block
				fmtutilobj.format_str( 0, 16, '*' );
				//InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld4, BCDTOA, 16, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld6, FMT_CHAR, 16, bitno );
				break;

			case 54:

				//Additional Ammounts
				break ;
			/*
			case 55:
			{
				//EMV Elements
				char EMVTag[ EMV_TAG_MAX_SIZE ], EMVData[ EMV_SFMT_CHAR_SIZE + 1 ];
				unsigned char EMVBuffer[ EMV_UFMT_CHAR_SIZE + 1 ];
				int EMVLen;
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
				memset( EMVBuffer, 0, sizeof( EMVBuffer ) );
				//InBuf += fmtutilobj.fmt_in( InBuf, EMVBuffer, MOVE, len, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, EMVBuffer, FMT_CHAR, len, bitno );
				int emvoffset = 0;
               	 		memset( &tmsmsg->emvbuf, 0, sizeof( struct EzEMVBuffer ) );
                		while ( emvoffset < len )
				{
                			memset( EMVTag, 0, sizeof( EMVTag ) );
                			emvoffset += emvutil.getEMVTag( ( char * )EMVBuffer + emvoffset, len, EMV_TAG_BCD, EMVTag );
                			emvoffset += emvutil.getEMVTagLen( ( char * ) EMVBuffer + emvoffset, 1, EMV_LEN_BINARY, &EMVLen );
                			memset( EMVData, 0, sizeof( EMVData ) );
                			emvoffset += emvutil.getEMVData( ( char * )EMVBuffer + emvoffset, EMVLen, EMV_DATA_BCD, EMVData );
                			emvutil.copyEMVElement( &tmsmsg->emvbuf, EMVTag, EMVData );
				}
         		        tmsmsg->ChipEnabled = 'Y';
				break;
			}
*/
			case 59:

				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld5, FMT_CHAR, len, bitno );
				break;

			case 60:

				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld1, FMT_CHAR, len, bitno );

				memset( tmsmsg->MachineId, 0, sizeof( tmsmsg->MachineId ) );
				strcpy( tmsmsg->MachineId, tmsmsg->RsvFld1 );

				break;

			case 61:
                                if( tmsmsg->TxnCode/10000 == 57 )
                                {
                                        InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                                        InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->private_use.RsvFld3, FMT_CHAR, len, bitno );
                                }
                                else
                                {				
					InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
					InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
				}
				break;

			case 62:
				if( tmsmsg->TxnCode/10000 == 68 )
				{
					InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
					InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld1, FMT_CHAR, len, bitno );
				}
				else
				{
	                                InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                                        InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld3, FMT_CHAR, len, bitno );
				}
				break;

			case 63:
				//Private Use - Original Data
				if( tmsmsg->TxnCode/10000 == 57 )
				{
	                                memset( tmsmsg->private_use.EchoBack, 0, sizeof( tmsmsg->private_use.EchoBack ) );
        	                        InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                	                InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->private_use.EchoBack, FMT_CHAR, len, bitno );
                        	}
				else
				{
					InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
					InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld1, FMT_CHAR, len, bitno );
					dptr->trace( "RsvFld1[%s]" , tmsmsg->RsvFld1 );

				}
				break;

			case 64:

				//Terminal User Details for authentication
				InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
				InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
				dptr->trace( "RsvFld2[%s]" , tmsmsg->RsvFld2 );
				//dptr->trace("UBP Customer account number[%s]", tmsmsg->RsvFld1 );
				break ;

			case 70:
				InBuf += fmtutilobj.fmt_in( InBuf, &tmsmsg->NetCode, FMT_ATOI, 3, bitno );
                		break;

			case 102:
                                InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
                                InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->FromAccount, FMT_CHAR, len, bitno );
                                break;

                        case 103:
                                if( tmsmsg->TxnCode == 710000 || tmsmsg->TxnCode == 390000 )
                                {
                                        InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
                                        InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
					memset( tmsmsg->tochn, 0, sizeof(tmsmsg->tochn) );
					strcpy( tmsmsg->tochn, tmsmsg->RsvFld2 );
                                }
				else 
				{
                                        InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
                                        InBuf += fmtutilobj.fmt_in( InBuf, tmsmsg->ToAccount, FMT_CHAR, len, bitno );
				}
                                break ;

			case 122:
                                memset( tmsmsg->private_use.RsvFld1 , 0, sizeof( tmsmsg->private_use.RsvFld1 ) );
                                InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                                InBuf += fmtutilobj.fmt_in( InBuf ,tmsmsg->private_use.RsvFld1, FMT_CHAR, len, bitno );
                                dptr->trace("Biller Acct [%s]", tmsmsg->private_use.RsvFld1);
                                break;

			case 123:
                                memset( tmsmsg->private_use.RsvFld2 , 0, sizeof( tmsmsg->private_use.RsvFld2 ) );
                                InBuf += fmtutilobj.fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                                InBuf += fmtutilobj.fmt_in( InBuf ,tmsmsg->private_use.RsvFld2, FMT_CHAR, len, bitno );
                                dptr->trace("Biller ID [%s]", tmsmsg->private_use.RsvFld2);
                                break;

			default:
				dptr->trace( "Unhandled bit in ISO Decompose [%d]", bitno );
		}
	}
	return 1;
}

int EzCastles8583 :: composeMsg( struct EzTxnMsg *tmsmsg, char *OutBuf, int ProtocolFlag )
{
	char *BufOffset;

	unsigned char BitMap[ 33 ];
	char TempStr[ 50 ], TDate[ 10 ], TempStr1[ 50 ], TempStr2[ 50 ];
	char PrinterResponseTemplate[ 512 ], ScreenResponseTemplate[ 512 ];
	int len, TmpMsgType;
	BufOffset = OutBuf;
	/*
	//start
        //Reversal Test case
        if ( tmsmsg->MsgType == 210)
        {
		dptr->trace ("---TESTING FOR REVERSAL NOT RESPONDING---");
		return -1;
	}
        //end
	*/

/*	if( ProtocolFlag == POS_PROTOCOL_HYPERCOM )
	{
		dptr->trace( "HYPERCOM" );
		//TCPHEADER
		memset( TempStr1, 0, sizeof( TempStr1 ) );
		strncpy( TempStr1, (char*)tmsmsg->private_use.RsvFld3, 2 );
		strncpy( TempStr1 + 2, (char*)tmsmsg->private_use.RsvFld3 + 6, 4 );
		strncpy( TempStr1 + 6, (char*)tmsmsg->private_use.RsvFld3 + 2, 4 );
		OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr1, ATOBCD, 10, 0 );
	}*/

	if( tmsmsg->MsgType == 210 && tmsmsg->TxnCode / 10000 == EZTMS_Txn_PreAuthComp )
	{
		TmpMsgType = 230;
		OutBuf += fmtutilobj.fmt_out( OutBuf, &TmpMsgType, FMT_ITOA, 4, 0 );
	}
	else
		OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->MsgType, FMT_ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	if( isoutilobj.LoadBitMap( BitMap, tmsmsg->MsgType, tmsmsg->TxnCode, tmsmsg->RespCode ) < 0 )
	{
		dptr->trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", tmsmsg->MsgType, tmsmsg->TxnCode, tmsmsg->RespCode );
		return -1;
	}
/*
	if( ProtocolFlag == POS_PROTOCOL_CASTLES )
	{
		memset( PrinterResponseTemplate, 0, sizeof( PrinterResponseTemplate ) );
		memset( ScreenResponseTemplate, 0, sizeof( ScreenResponseTemplate ) );
		if( !tmsmsg->RespCode )
		{
			if( tmsdrvrtemplate.composeResponseTemplate( tmsmsg, terminalprofile_ptr->TerminalType, merchantprofile_ptr->MerchantTypeId, tmsmsg->AcceptorId, PrinterResponseTemplate ) < 0 )
				isoutilobj.SetBitOff( BitMap, 63 );
			else
				isoutilobj.SetBitOn( BitMap, 63 );
			if( tmsdrvrtemplate.composeResponseTemplate( tmsmsg, terminalprofile_ptr->TerminalType, merchantprofile_ptr->MerchantTypeId, tmsmsg->AcceptorId, ScreenResponseTemplate, true ) < 0 )
				isoutilobj.SetBitOff( BitMap, 64 );
			else
				isoutilobj.SetBitOn( BitMap, 64 );
		}
		else
		{
			if( tmsdrvrtemplate.composeBadResponseTemplate( tmsmsg, terminalprofile_ptr->TerminalType, merchantprofile_ptr->MerchantTypeId, tmsmsg->AcceptorId, PrinterResponseTemplate ) < 0 )
				isoutilobj.SetBitOff( BitMap, 63 );
			else
				isoutilobj.SetBitOn( BitMap, 63 );
		}

	}
*/
	//isoutilobj.SetBitOff( BitMap, 63 );

	if( tmsmsg->TxnCode/10000 == 30 && tmsmsg->RespCode == 0 )
		isoutilobj.SetBitOn( BitMap, 54 );
	
	if(  tmsmsg->TxnCode/10000 == 38 && tmsmsg->RespCode == 0 )
                isoutilobj.SetBitOn( BitMap, 60 );

	if( tmsmsg->MsgType == 210 && ( tmsmsg->TxnCode/10000 == 30 || tmsmsg->TxnCode/10000 == 38 ) )
        {
                isoutilobj.SetBitOn( BitMap, 49 );
        }
	
	if( tmsmsg->MsgType == 210 && tmsmsg->RespCode == 0 && ( tmsmsg->TxnCode/10000 == 56 || tmsmsg->TxnCode/10000 == 57 || tmsmsg->TxnCode/10000 == 68 ) )
        {
		isoutilobj.SetBitOn( BitMap, 124 );	
	}
		
	//Setting the DE 55 for Response Msg
	if( tmsmsg->ChipEnabled == 'Y' )
	{
		isoutilobj.SetBitOn( BitMap, 55 );
		dptr->trace( "HYPERCOM" );
	}

	OutBuf += fmtutilobj.fmt_out( OutBuf, BitMap, FMT_HTOA, 16, 1 );
	if( isoutilobj.IsBitSet( BitMap, 1 ) )
		OutBuf += fmtutilobj.fmt_out( OutBuf, BitMap + 8, FMT_HTOA, 16, 1 );


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
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				fmtutilobj.format_str( 6, strlen( tmsmsg->chn ) - 4, '*' );
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->chn, FMT_CHAR, len, bitno );
				break;

			case 3:

				//TxnCode
				len = getTerminalTxnCode( tmsmsg->TxnCode );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 6, bitno );
				break;

			case 4:

				//Amount
				memset( TempStr1, 0, sizeof( TempStr1 ) );
				amtutil_ptr->formatAmt( tmsmsg->Amount, TempStr1, 12 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr1, FMT_CHAR, 12, bitno );
				break;

			case 11:

				//TraceNo
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->TraceNo, FMT_ITOA, 6, bitno );
				break;

			case 12:

				//LocalTime
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->LocalTime, FMT_ITOA, 6, bitno );
				break;

			case 13:

				//LocalDate
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->LocalDate, FMT_ITOA, 6, bitno );
				break ;

			case 14:

				//Expiry Date
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->ExpiryDate, FMT_ITOA, 4, bitno );
				break;

			case 22:

				//POS Entry Code
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->PosEntryCode, FMT_ITOA, 3, bitno );
				break;

			case 24:

				//Network International ID
				dptr->trace( "tmsmsg->RsvFld5[%s]", tmsmsg->RsvFld5 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld5, FMT_CHAR, 3, bitno );
				break;

			case 25:

				//POS Condition Code
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->PosConditionCode, FMT_ITOA, 2, bitno );
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
				tmsmsg->RespCode = isoutilobj.getOutBoundExtRespCode( tmsmsg->RespCode );
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

			case 43:

				//TerminalLocation
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->TerminalLocation, FMT_CHAR, 40, bitno );
				break ;
			
			case 48:

                                OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld1, FMT_ITOA, 3, bitno );
                                break ;
		
			case 49:
                                //OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->IssCurrencyCode, FMT_ITOA, 3, bitno );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->AcqCurrencyCode, FMT_ITOA, 3, bitno );
                                break ;
				
			case 52:

				//PIN Block
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->PINBlock, FMT_CHAR, 16, bitno );
				break ;

			case 54:
				memset( TempStr1, 0, sizeof( TempStr1 ) );
				amtutil_ptr->formatAmt( tmsmsg->AvailBalance, TempStr1, 12 );
				len = strlen( TempStr1 );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr1, FMT_CHAR, len, bitno );
				break;
/*
			case 55:
				{
					//EMV Elements
					char AuthRespCode[ 5 ], RespStr[ 5 ], IssuerAuthData[ 49 ], IssuerAuthResp[ 10 ];
					unsigned char *EMVBuf;
					unsigned char EMVData[ 513 ];
					int len, datasetid;

					memset( EMVData, 0, sizeof( EMVData ) );
					EMVBuf = EMVData;

					
					dptr->trace( "EMV IssuerAuthData[%s]", tmsmsg->emvbuf.IssuerAuthData );
					if( strlen( tmsmsg->emvbuf.IssuerAuthData ) )
					{
						EMVBuf += emvutil.composeEMVData( EMV_TAG_ISSAUTHDATA, EMV_TAG_BCD, strlen(tmsmsg->emvbuf.IssuerAuthData), EMV_LEN_BINARY, 2, tmsmsg->emvbuf.IssuerAuthData, EMV_TAG_BCD, EMVBuf );
					}
					
					dptr->trace( "EMV IssuerScriptData[%s]", tmsmsg->emvbuf.IssuerScriptData );
					if( strlen( tmsmsg->emvbuf.IssuerScriptData ) )
					{
						EMVBuf += emvutil.composeEMVData( EMV_TAG_ISSSCRIPT2, EMV_TAG_BCD, strlen(tmsmsg->emvbuf.IssuerScriptData), EMV_LEN_BINARY, 2, tmsmsg->emvbuf.IssuerScriptData, EMV_TAG_BCD, EMVBuf );
					}

					dptr->trace( "EMV RsvFld1[%s]", tmsmsg->emvbuf.RsvFld1 );
					if( strlen( tmsmsg->emvbuf.RsvFld1 ) )
					{
						EMVBuf += emvutil.composeEMVData( "71", EMV_TAG_BCD, strlen(tmsmsg->emvbuf.RsvFld1), EMV_LEN_BINARY, 2, tmsmsg->emvbuf.RsvFld1, EMV_TAG_BCD, EMVBuf );
					}

					len = EMVBuf - EMVData;
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, EMVData, MOVE, len, bitno );
				}
				break;
*/
			case 60:

				len = strlen( tmsmsg->RsvFld1 );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld1, FMT_CHAR, len, bitno );
				break ;

			case 61:
				if( tmsmsg->TxnCode/10000 == 56 || tmsmsg->TxnCode/10000 == 57 )
				{
					memset( TempStr, 0, sizeof(TempStr) );
					sprintf( TempStr, "%s", tmsmsg->private_use.RsvFld3 );
	                                len = strlen( TempStr );
        	                        dptr->trace("Bill Due Date: [%s] ", TempStr );
                		        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                	OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr , FMT_CHAR, len, bitno );
				}	
				else
				{
					len = strlen( tmsmsg->RsvFld2 );
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
				}
				break;

			case 62:
				//Private Use - InVoiceNo
				if( tmsmsg->TxnCode/10000 == 68 )
                                {
					/*len = strlen( tmsmsg->RsvFld4 );
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld4, FMT_CHAR, len, bitno );*/
					dptr->trace( "tmsmsg->private_use.EchoBack[ %s ]", tmsmsg->private_use.EchoBack );
                                        memset( TempStr, 0, sizeof( TempStr ) );
                                        sprintf( TempStr, "%s", tmsmsg->private_use.EchoBack );
                                        len = strlen( TempStr );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr, FMT_CHAR, len, bitno );
				}
				else
				{
                                        len = strlen( tmsmsg->RsvFld3 );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld3, FMT_CHAR, len, bitno );
				}
				break ;

			case 63:
	                       	if( tmsmsg->TxnCode/10000 == 56 || tmsmsg->TxnCode/10000 == 57 )
	                       	{
					dptr->trace( "tmsmsg->private_use.EchoBack[ %s ]", tmsmsg->private_use.EchoBack );
                                	memset( TempStr, 0, sizeof( TempStr ) );
                                        sprintf( TempStr, "%s", tmsmsg->private_use.EchoBack );
                                        len = strlen( TempStr );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, TempStr, FMT_CHAR, len, bitno );
	                        }
				else
				{
					len = strlen( tmsmsg->RsvFld2 );
					OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
					OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
				}
				break ;

			case 64:

				len = strlen( ScreenResponseTemplate );
				OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
				OutBuf += fmtutilobj.fmt_out( OutBuf, ScreenResponseTemplate, FMT_CHAR, len, bitno );

				break ;

			case 70:
				tmsmsg->NetCode = 184;
				OutBuf += fmtutilobj.fmt_out( OutBuf, &tmsmsg->NetCode, FMT_ITOA, 3, bitno );
				break;

      			case 102:
                                //Account Identification-1
                                len = strlen( tmsmsg->FromAccount );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->FromAccount, FMT_CHAR, len, bitno );
                                break;

                        case 103:
                                //Account Identification-2
                                if( tmsmsg->TxnCode == 710000 || tmsmsg->TxnCode == 390000 )
                                {
                                        len = strlen( tmsmsg->tochn );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->tochn, FMT_CHAR, len, bitno );
				}
				else
				{
	                                len = strlen( tmsmsg->ToAccount );
        	                        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
                	                OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->ToAccount, FMT_CHAR, len, bitno );
				}
                                break;

			case 120:
                                len = strlen( tmsmsg->RsvFld2 );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld2, FMT_CHAR, len, bitno );
                                break;

			case 122:
                                memset( TempStr, 0, sizeof(TempStr) );
                                sprintf( TempStr, "%s", tmsmsg->private_use.RsvFld1 );
                                len = strlen( TempStr );				
                                OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                OutBuf += fmtutilobj.fmt_out( OutBuf , TempStr, FMT_CHAR, len, bitno );
                                dptr->trace("Biller Acct [%s]", TempStr );
				break;

			case 123:
                                memset( TempStr, 0, sizeof(TempStr) );
                                sprintf( TempStr, "%s", tmsmsg->private_use.RsvFld2 );
                                len = strlen( TempStr );
                                OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                OutBuf += fmtutilobj.fmt_out( OutBuf , TempStr, FMT_CHAR, len, bitno );
                                dptr->trace("Biller ID [%s]", TempStr );
                                break;

			case 124:
				if( tmsmsg->TxnCode/10000 == 56 || tmsmsg->TxnCode/10000 == 57 || tmsmsg->TxnCode/10000 == 68 )
                                {
					len = strlen( tmsmsg->RsvFld5 );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                                        OutBuf += fmtutilobj.fmt_out( OutBuf, tmsmsg->RsvFld5, FMT_CHAR, len, bitno );
					dptr->trace("BILLER TXN REF ID [%s]", tmsmsg->RsvFld5 );
                                }
                                break;

		
			default:

				dptr->trace( "Unhandled bit in iso8583" );
				break ;
		}
	}
		return( OutBuf - BufOffset );
}


