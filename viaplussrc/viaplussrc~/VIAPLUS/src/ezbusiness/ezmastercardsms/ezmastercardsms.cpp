#include <ezbusiness/ezmastercardsms.h>

EzMasterCardSMS :: EzMasterCardSMS()
{
}

EzMasterCardSMS :: ~EzMasterCardSMS()
{
}

void EzMasterCardSMS :: InitEzMasterCardSMS( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmastercardsms.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzMasterCardSMS Started Running^^^^^^^^^^^^^");
	
	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzMasterCardSMS Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzMasterCardSMS Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();	
	}

	if( CreateChannel( "EzMasterCardSMS" ) < 0 )
	{
		trace( "Error in Creating EzMasterCardSMS Channel" );
		trace( "^^^^^^^^^^^EzMasterCardSMS Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();	
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", "EzMasterCardSMSBitMap.cfg" );
	
	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzMasterCardSMS Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}
	
	initFmtUtil( this );
	
	TaskInit();
	initEzSigUtil( this );
}

int EzMasterCardSMS :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf ) 
{
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ];
	unsigned char BitMap[ 33 ];
	char TempAmount[13];
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
	
	if( ( txnmsg->MsgType == 800 || txnmsg->MsgType == 810 ) && txnmsg->NetCode == 161 )
		SetBitOn( BitMap, 48 );
	
	if( txnmsg->RespCode == EZLINK_RC_MessageFormatError )
		SetBitOn( BitMap, 44 );
	
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
			//CHN
			len = strlen( txnmsg->chn );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->chn, CHAR, len, bitno );
			break ;

		case 3:
			//Processing Code
			char TempTxnCode[7];
			memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
			sprintf( TempTxnCode, "%06d", txnmsg->TxnCode );
			OutBuf += fmt_out( OutBuf, TempTxnCode, CHAR, 6, bitno );
			break ;

		case 4:
			//Transaction Amount
			//if Amount in HEX convert into ACSII
					
			memset( TempAmount, 0, sizeof( TempAmount ) );				
			if( strlen( txnmsg->Amount ) <= 0 )
				strncpy( TempAmount, "000000000000", 12 );					
			else
				sprintf( TempAmount, "%012d", txnmsg->Amount );
						
			OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
			break ;

		case 5:
			//Settelment Amount
			//if Amount in HEX convert into ACSII
			memset( TempAmount, 0, sizeof( TempAmount ) );				
			if( strlen( txnmsg->SettAmount ) <= 0 )
				strncpy( TempAmount, "000000000000", 12 );					
			else
				sprintf( TempAmount, "%012d", txnmsg->SettAmount );
						
			OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
			break ;
			
		case 6:
			//Actual Billing Amount( Amount converted to Issuer Currency )
			//if Amount in HEX convert into ACSII
			memset( TempAmount, 0, sizeof( TempAmount ) );				
			if( strlen( txnmsg->BillingAmount ) <= 0 )
				strncpy( TempAmount, "000000000000", 12 );					
			else
				sprintf( TempAmount, "%012d", txnmsg->BillingAmount );
						
			OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
			break ;
				
		case 7:
			// Transaction Date and Time ( field format MMDDhhmmss )
			OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, LTOA, 4, bitno );
			OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );
			break ;
			
		case 8:
			//Issuer Transaction Fee
			//OutBuf += fmt_out( OutBuf, txnmsg->TxnFee, CHAR, 8, bitno );
			break ;
			
		case 9:
			//Conversion Rate, Settlement
			OutBuf += fmt_out( OutBuf, &txnmsg->SettConvRate, LTOA, 8, bitno );
			break ;
			
		case 10:
			//Conversion Rate, Cardholder Billing
			OutBuf += fmt_out( OutBuf, &txnmsg->IssConvRate, LTOA, 8, bitno );
			break ;
			
		case 11:
			//System Trace Audit Number
			OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
			break ;

		case 12:
			//Local Transaction Time ( field format hhmmss )
			OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, LTOA, 6, bitno );
			break ;

		case 13:
			//Local Transaction Date ( field format MMDD )
			OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, LTOA, 4, bitno );
			break ;
			
		case 14:
			//Card Expiration Date ( field format YYMM )
			OutBuf += fmt_out( OutBuf, &txnmsg->ExpiryDate, LTOA, 4, bitno );
			break ;
			
		case 15:
			// Settlement Date ( field format MMDD )
			OutBuf += fmt_out( OutBuf, &txnmsg->SettConvDate, LTOA, 4, bitno );
			break ;
			
		case 16:
			//Card Expiration Date ( field format YYMM )
			OutBuf += fmt_out( OutBuf, &txnmsg->IssConvDate, LTOA, 4, bitno );
			break ;
			
		case 17:
			// Capture Date ( field format YYMM )
			OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, LTOA, 6, bitno );
			break ;
		
		case 18:
			//Merchant Type
			OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
			break ;
			
		case 19:
			//Acquiring Institution Country Code
			OutBuf += fmt_out( OutBuf, &txnmsg->AcqCurrencyCode, STOA, 3, bitno );
			break ;
			
		case 20:
			//Primary Account Number (PAN) Country Code( Issuer ) 
			OutBuf += fmt_out( OutBuf, &txnmsg->IssCurrencyCode, STOA, 3, bitno );
			break ;
			
		case 21:
			//Forwarding Institution Country Code
			//OutBuf += fmt_out( InBuf, &txnmsg->AcqCurrencyCode, STOA, 3, bitno );
			break ;
		
		case 22:
			//Point of Service Entry Mode
			break;
		
		case 23:
			//Card Sequence Number
			break;
		
		case 24:
			//Network International Identifier
			break;
			
		case 25:
			//Point of Service Condition Code (ISO)
			break;
			
		case 26:
			//Point of Service (POS) PIN Capture Code
			OutBuf += fmt_out( OutBuf, &txnmsg->PinCapCode, STOA, 2, bitno );
			break;
			
		case 27:
			//Authorization ID Response Length
			break;
			
		case 28:
			// Transaction Fee Amount
			//OutBuf += fmt_out( OutBuf, txnmsg->ProcessingFlag, STOA, 1, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->TxnFee, CHAR, 8, bitno );
			break;
			
		case 29:
			//Amount, Settlement Fee
			break;
			
		case 30:
			//Amount, Transaction Processing Fee
			break;
		
		case 31:
			// Settlement Processing Fee
			break;
			
		case 32:
			//Acquiring Institution ID Code
			if( txnmsg->MsgType == 810 )
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
			break;
			
		case 33:
			//Forwarding Institution ID Code
			len = strlen( txnmsg->FwdNetworkId );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->FwdNetworkId, CHAR, len, bitno );
			break;
			
		case 34:
			//Primary Account Number (PAN), Extended
			break;
			
		case 35:
			//Track 2 Data
			len = strlen( txnmsg->Track2 );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->Track2, CHAR, len, bitno );
			break;
			
		case 36:
			//Track 3 Data
			break;
		
		case 37:
			//Retrieval Reference Number
			OutBuf += fmt_out( OutBuf, &txnmsg->RefNum, CHAR, 12, bitno );
			break;
		
		case 38:
			//Authorization ID Response 
			OutBuf += fmt_out( OutBuf, &txnmsg->AuthCode, CHAR, 6, bitno );
			break;
			
		case 39:
			//Responce Code
			OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 2, bitno );
			break ;
		
		case 40:
			//Service Restriction Code
			break;
			
		case 41:
			//Card Acceptor Terminal ID
			OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 16, bitno );
			break;
			
		case 42:
			//Card Acceptor ID Code
			break;
			
		case 43:
			//Card Acceptor Name/Location
			OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
			break;
			
		case 44:
			//Additional Response Data
			break;
		
		case 45:
			//Track 1 Data
			break;
		
		case 46:
			//Additional Data—ISO Use
			break;
			
		case 47:
			//Additional Data—National Use			
			break;
			
		case 48:
			//Additional Data—Private Use
			break;
			
		case 49:
			//Acquirer Currency Code
			OutBuf += fmt_out( OutBuf, &txnmsg->AcqCurrencyCode, STOA, 3, bitno );
			break;
			
		case 50:
			//Settlement Currency Code
			OutBuf += fmt_out( OutBuf, &txnmsg->SettCurrencyCode, STOA, 3, bitno );
			break;
		
		case 51:
			//Cardholder Billing Currency Code
			OutBuf += fmt_out( OutBuf, &txnmsg->IssCurrencyCode, STOA, 3, bitno );
			break;
		
		case 52:
			//Personal ID Number (PIN) Data
			OutBuf += fmt_out( OutBuf, txnmsg->PINBlock, CHAR, 16, bitno );
			break;
			
		case 53:
			//Security-related Control Information
			break;
			
		case 54:
			//Additional Amounts
			char tempStr1[ 20 ], tempStr2[ 20 ], acctType[ 3 ], TempLedgerBalance[13], TempAvailBalance[13];
			
			memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
			sprintf( TempTxnCode, "%06d", txnmsg->TxnCode );
			
			memset( acctType, 0, sizeof( acctType ) );
			acctType[0] = TempTxnCode[ 2 ];
			acctType[1] = TempTxnCode[ 3 ];
			
			memset( TempLedgerBalance, 0, sizeof( TempLedgerBalance ) );				
			if( strlen( txnmsg->LedgerBalance ) <= 0 )
				strncpy( TempLedgerBalance, "000000000000", 12 );					
			else
				sprintf( TempLedgerBalance, "%012s", txnmsg->LedgerBalance );

			memset( TempAvailBalance, 0, sizeof( TempAvailBalance ) );				
			if( strlen( txnmsg->AvailBalance ) <= 0 )
				strncpy( TempAvailBalance, "000000000000", 12 );					
			else
				sprintf( TempAvailBalance, "%012s", txnmsg->AvailBalance );

			memset( tempStr1, 0, sizeof( tempStr1 ) );
			sprintf( tempStr1, "%s01%03d%c", acctType, txnmsg->IssCurrencyCode,  txnmsg->ProcessingFlag, TempLedgerBalance );
			memset( tempStr2, 0, sizeof( tempStr2 ) );
			sprintf( tempStr2, "%s02%03d%c", acctType, txnmsg->IssCurrencyCode,  txnmsg->ProcessingFlag, TempAvailBalance );
			
			len = strlen( tempStr1 ) + strlen( tempStr2 );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
			OutBuf += fmt_out( OutBuf, tempStr1, CHAR, 20, bitno );
			OutBuf += fmt_out( OutBuf, tempStr2, CHAR, 20, bitno );
			break ;
			
		case 55:
			//Integrated Circuit Card (ICC) System-related Data
			break;
			
		case 56:
			//Reserved for ISO Use
			break;
			
		case 57:
			//Reserved for National Use
			break;
		
		case 58:
			//Authorizing Agent Institution ID
			break;
		
		case 59:
			//Reserved for National Use
			break;
			
		case 60: 
			//Advice Reason Code
			
			len = 3;
			OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
			OutBuf += fmt_out( OutBuf, &txnmsg->ReasonCode, STOA, 3, bitno );
			//need to add reason code details
			break ;

		case 61: 
			//Point-of-Service (POS) Data
			//Fixed 26
			break ;

		case 62: 
			//Intermediate Network Facility (INF) Data
			break ;

		case 63: 
			//Network Data 
			//ISO: ans…999; LLLVAR
			//RSC: an…044; LLVAR
			break ;
			
		case 64:
			//Message Authentication Code (MAC) 
			//Used for  Cryptogram
            break ;

		case 65:
			//Bit Map, Extended
			break ;

		case 66:
			//Settlement Code( Used in MsgType 0530 and 0532 ) --- 1 digit 
            break ;
            
		case 67:
			//Extended Payment Code
			break ;
		
		case 68:
			//Receiving Institution Country Code
			break;
			
		case 69:
			//Settlement Institution Country Code
			OutBuf += fmt_out( OutBuf, &txnmsg->SettCurrencyCode, STOA, 3, bitno );
			break;
			
		case 70:
			//Network Management Information Code
			OutBuf += fmt_out( OutBuf, &txnmsg->NetCode, ITOA, 3, bitno );
			trace( "Net Code [%03d]", txnmsg->NetCode );
			break;
		
        case 71:
        	//Message Number
            break;

        case 72:
        	//Message Number Last
            break;
              
        case 73:
        	//Date, Action
        	break;
        	
        case 74:
        	// Number of Credits, ( Used in MsgType 0520 and 0522 )
        	break;
        
        case 75:
        	// Number of Credits Reversal, ( Used in MsgType 0520 and 0522 )
        	break;
        
        case 76:
        	// Number of Debits, ( Used in MsgType 0520 and 0522 )
        	break;
        	
        case 77:	
        	// Number of Debits Reversal, ( Used in MsgType 0520 and 0522 )
        	break;

        case 78:
        	// Number of Transfers, ( Used in MsgType 0520 and 0522 )
        	break;
        	
        case 79:	
        	// Number of Transfers Reversal, ( Used in MsgType 0520 and 0522 )
        	break;
        	
        case 80:
        	// Number of Inquiries, ( Used in MsgType 0520 and 0522 )
        	break;
        	
        case 81:
        	// Number of Authorizations, ( Used in MsgType 0520 and 0522 )
        	break;

        case 82:
        	// Credits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 83:
        	// Credits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;
        	
        case 84:
        	// Debits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;
        	
        case 85:
        	// Debits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 86:
        	// Credits Amount, ( Used in MsgType 0520 and 0522 )
        	break;
        
        case 87:
         	// Credits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
         	break;
         	
        case 88:
        	// Debits Amount, ( Used in MsgType 0520 and 0522 )
        	break;
        
        case 89:
         	// Debits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
         	break;

		case 90:
			//Original Data Elements
			trace( "Original Data Elements" );
			OutBuf += fmt_out( OutBuf, &txnmsg->OrgMsgType, ITOA, 4, bitno );
			OutBuf += fmt_out( OutBuf, &txnmsg->OrgTraceNo, LTOA, 6, bitno );
			OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranDate, LTOA, 4, bitno );
			OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranTime, LTOA, 6, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->AcquirerInst,  CHAR, 11, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->IssuerInst,  CHAR, 11, bitno );
			break ;
			
		case 91:
			//File Update Code
			break;
		
		case 92:
			//File Security Code
			break;
		
		case 93:
			//Response Indicator
			break;
		
		case 94:
			//Service Indicator
			break;
			
		case 95:
			//Replacement Amounts
			char DispAmount[ 13 ], TempBillingAmount[ 13 ];
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
			
			memset( TempAmount, 0, sizeof( TempAmount ) );				
			if( strlen( txnmsg->Amount ) <= 0 )
				strncpy( TempAmount, "000000000000", 12 );					
			else
				sprintf( TempAmount, "%012d", txnmsg->Amount );

			memset( TempBillingAmount, 0, sizeof( TempBillingAmount ) );				
			if( strlen( txnmsg->BillingAmount ) <= 0 )
				strncpy( TempBillingAmount, "000000000000", 12 );					
			else
				sprintf( TempBillingAmount, "%012d", txnmsg->BillingAmount );
						


			OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
			OutBuf += fmt_out( OutBuf, DispAmount,  CHAR, 12, bitno );
			OutBuf += fmt_out( OutBuf, TempBillingAmount, CHAR, 12, bitno );
			OutBuf += fmt_out( OutBuf, ( char * ) "000000",  CHAR, 6, bitno );
			break ;
			
		case 96:
			//Message Security Code
			break;
			
		case 97:
			//Net Settlement Amount,( Used in MsgType 0530, 0532, 0520 and 0522 )
			break;

		case 98:
			//Payee
			break;
			
		case 99:
			//Settlement Institution ID Code,( Used in MsgType 0530, 0532, 0520 and 0522 )
			break;
			
		case 100:
			//Receiving Institution ID Code
			break;

		case 101:
			//File Name
			break;

		case 102:
			//Account ID-1
			len = strlen( txnmsg->FromAccount );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->FromAccount, CHAR, len, bitno );
			break;

		case 103:
			//Account ID-2
			len = strlen( txnmsg->ToAccount );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( OutBuf, txnmsg->ToAccount, CHAR, len, bitno );
			break;
			
		case 104:
			//Transaction Description
			break;
			
		case 105:
		case 106:
		case 107:
		case 108:
		case 109:
		case 110:
			//Reserved for ISO Use
			break;
		
		case 111:
			////Amount, Currency Conversion Assessment
			break;
			
		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
		case 117:
		case 118:
		case 119:
			//Reserved for National Use
			break;

		case 120:
			//Record Data
			break;
			
		case 121:
			//Authorizing Agent ID Code
			break;
			
		case 122:
			//Additional Record Data
			break;
			
		case 123:
		case 124:
		case 125:
			//Reserved for Future Definition and RSC Use
			break;
			
		case 126:
			//Switch Private Data --LLLVAR
			break;
			
		case 127:
			//Processor Private Data
			memset( StmtBuf, 0, sizeof( StmtBuf ) );
			strcpy( StmtBuf, txnmsg->RsvFld1 );
			trace( DEBUG_NORMAL, "Reserved Field [%s]\n", StmtBuf );
			
			len = strlen( StmtBuf );
			OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
			OutBuf += fmt_out( OutBuf, StmtBuf, CHAR, len, bitno );
			break;
			
		case 128:
			//Message Authentication Code (MAC)
			break;
			
		default:
			trace( "Unhandled bit in ISO Decompose [%d]", bitno );

		}
	}
	return( OutBuf - BufOffset ); 
}


int EzMasterCardSMS :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len;
	char StmtBuf[ STMT_BUF_SIZE +1 ];
	char TempAmount[13];
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
				//CHN
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->chn, CHAR, len, bitno );
				break ;

			case 3:
				//Processing Code
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOL, 6, bitno );
				break ;
	
			case 4:
				//Transaction Amount
				//if Amount in HEX convert into ACSII
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				sprintf( txnmsg->Amount, "%s", TempAmount );
				break ;

			case 5:
				//Settelment Amount
				//if Amount in HEX convert into ACSII
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				sprintf( txnmsg->SettAmount, "%s", TempAmount );
				break ;
				
			case 6:
				//Actual Billing Amount( Amount converted to Issuer Currency )
				//if Amount in HEX convert into ACSII
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				sprintf( txnmsg->BillingAmount, "%s", TempAmount );
				break ;
					
			case 7:
				// Transaction Date and Time ( field format MMDDhhmmss )
				InBuf += fmt_in( InBuf, &txnmsg->TranDate, ATOL, 4, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, bitno );
				break ;
				
			case 8:
				//Issuer Transaction Fee
				//InBuf += fmt_in( InBuf, txnmsg->TxnFee, CHAR, 8, bitno );
				break ;
				
			case 9:
				//Conversion Rate, Settlement
				InBuf += fmt_in( InBuf, &txnmsg->SettConvRate, ATOL, 8, bitno );
				break ;
				
			case 10:
				//Conversion Rate, Cardholder Billing
				InBuf += fmt_in( InBuf, &txnmsg->IssConvRate, ATOL, 8, bitno );
				break ;
				
			case 11:
				//System Trace Audit Number
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOL, 6, bitno );
				break ;

			case 12:
				//Local Transaction Time ( field format hhmmss )
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, bitno );
				break ;

			case 13:
				//Local Transaction Date ( field format MMDD )
				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOL, 4, bitno );
				break ;
				
			case 14:
				//Card Expiration Date ( field format YYMM )
				InBuf += fmt_in( InBuf, &txnmsg->ExpiryDate, ATOL, 4, bitno );
				break ;
				
			case 15:
				// Settlement Date ( field format MMDD )
				InBuf += fmt_in( InBuf, &txnmsg->SettConvDate, ATOL, 4, bitno );
				break ;
				
			case 16:
				//Card Expiration Date ( field format YYMM )
				InBuf += fmt_in( InBuf, &txnmsg->IssConvDate, ATOL, 4, bitno );
				break ;
				
			case 17:
				// Capture Date ( field format YYMM )
				InBuf += fmt_in( InBuf, &txnmsg->CaptureDate, ATOL, 6, bitno );
				break ;
			
			case 18:
				//Merchant Type
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;
				
			case 19:
				//Acquiring Institution Country Code
				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOS, 3, bitno );
				break ;
				
			case 20:
				//Primary Account Number (PAN) Country Code( Issuer ) 
				InBuf += fmt_in( InBuf, &txnmsg->IssCurrencyCode, ATOS, 3, bitno );
				break ;
				
			case 21:
				//Forwarding Institution Country Code
				//InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOS, 3, bitno );
				break ;
			
			case 22:
				char POSmode[4];
				char TempMode[4]; 
				int P1, P2;
				
				//Point of Service Entry Mode
				memset( POSmode, 0, sizeof( POSmode ) );
				InBuf += fmt_in( InBuf, POSmode, CHAR, 3, bitno );
				
				memset( TempMode, 0, sizeof( TempMode ) );
				strncpy( TempMode, POSmode, 2 );
				P1 = atoi( TempMode );
				
				switch( P1 )
				{
					case 0:
						trace( DEBUG_NORMAL, "PAN entry mode unknown" );
						break;
					case 1:
						trace( DEBUG_NORMAL, "PAN manual entry" );
						break;
					case 2:
						trace( DEBUG_NORMAL, "PAN auto-entry via magnetic stripe" );
						break;
					case 3:
						trace( DEBUG_NORMAL, "PAN auto-entry via bar code reader" );
						break;
					case 4:
						trace( DEBUG_NORMAL, "PAN auto-entry via optical character reader (OCR)" );
						break;
					case 5:
						trace( DEBUG_NORMAL, "PAN auto-entry via integrated circuit card" );
						break;
					case 6:
						trace( DEBUG_NORMAL, "PAN key entry" );
						break;
					case 7:
						trace( DEBUG_NORMAL, "PAN auto-entry via contactless M/Chip" );
						break;
					case 79:
						trace( DEBUG_NORMAL, "Chip card at chip-capable terminal was unable to process the transaction using chip technology" );
						break;	
					case 80:
						trace( DEBUG_NORMAL, "PAN auto entry with magnetic stripe" );
						break;
					case 81:
						trace( DEBUG_NORMAL, "PAN manual entry via electronic commerce" );
						break;
					case 90:
						trace( DEBUG_NORMAL, "PAN auto-entry via magnetic stripe" );
						break;
					case 91:
						trace( DEBUG_NORMAL, "PAN auto-entry with contactless Magnetic Stripe" );
						break;
					case 92:
						trace( DEBUG_NORMAL, "Contactless input. PayPass Mapping Service" );
						break;
				}
				
				
				switch( POSmode[ 2 ] )
				{
					case '0':
						trace( DEBUG_NORMAL, "Capability is unspecified or unknown." );
						break;
					case '1':
						trace( DEBUG_NORMAL, "Terminal has PIN entry capability" );
						break;
					case '2':
						trace( DEBUG_NORMAL, "Terminal does not have PIN entry capability" );
						break;
					case '8':
						trace( DEBUG_NORMAL, "Terminal has PIN entry capability, but PIN pad is out of service" );
						break;
				}
				break;
			
			case 23:
				//Card Sequence Number
				break;
			
			case 24:
				//Network International Identifier
				break;
				
			case 25:
				//Point of Service Condition Code (ISO)
				break;
				
			case 26:
				//Point of Service (POS) PIN Capture Code
				InBuf += fmt_in( InBuf, &txnmsg->PinCapCode, ATOS, 2, bitno );
				break;
				
			case 27:
				//Authorization ID Response Length
				break;
				
			case 28:
				char TempFee[2];
				// Transaction Fee Amount
				memset( TempFee, 0, sizeof( TempFee ) );
				InBuf += fmt_in( InBuf, TempFee, CHAR, 1, bitno );
				txnmsg->ProcessingFlag = TempFee[0];
				InBuf += fmt_in( InBuf, txnmsg->TxnFee, CHAR, 8, bitno );
				break;
				
			case 29:
				//Amount, Settlement Fee
				break;
				
			case 30:
				//Amount, Transaction Processing Fee
				break;
			
			case 31:
				// Settlement Processing Fee
				break;
				
			case 32:
				//Acquiring Institution ID Code
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
				break;
				
			case 33:
				//Forwarding Institution ID Code
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FwdNetworkId, CHAR, len, bitno );
				break;
				
			case 34:
				//Primary Account Number (PAN), Extended
				break;
				
			case 35:
				//Track 2 Data
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->Track2, CHAR, len, bitno );
				break;
				
			case 36:
				//Track 3 Data
				break;
			
			case 37:
				//Retrieval Reference Number
				InBuf += fmt_in( InBuf, &txnmsg->RefNum, CHAR, 12, bitno );
				break;
			
			case 38:
				//Authorization ID Response 
				InBuf += fmt_in( InBuf, &txnmsg->AuthCode, CHAR, 6, bitno );
				break;
				
			case 39:
				//Responce Code
				InBuf += fmt_in( InBuf, &txnmsg->RespCode, ATOI, 2, bitno );
				break ;
			
			case 40:
				//Service Restriction Code
				break;
				
			case 41:
				//Card Acceptor Terminal ID
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break;
				
			case 42:
				//Card Acceptor ID Code
				break;
				
			case 43:
				//Card Acceptor Name/Location
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;
				
			case 44:
				//Additional Response Data
				break;
			
			case 45:
				//Track 1 Data
				break;
			
			case 46:
				//Additional Data—ISO Use
				break;
				
			case 47:
				//Additional Data—National Use			
				break;
				
			case 48:
				//Additional Data—Private Use
				break;
				
			case 49:
				//Acquirer Currency Code
				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOS, 3, bitno );
				break;
				
			case 50:
				//Settlement Currency Code
				InBuf += fmt_in( InBuf, &txnmsg->SettCurrencyCode, ATOS, 3, bitno );
				break;
			
			case 51:
				//Cardholder Billing Currency Code
				InBuf += fmt_in( InBuf, &txnmsg->IssCurrencyCode, ATOS, 3, bitno );
				break;
			
			case 52:
				//Personal ID Number (PIN) Data
				InBuf += fmt_in( InBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break;
				
			case 53:
				//Security-related Control Information
				break;
				
			case 54:
				//Additional Amounts
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
				
			case 55:
				//Integrated Circuit Card (ICC) System-related Data
				break;
				
			case 56:
				//Reserved for ISO Use
				break;
				
			case 57:
				//Reserved for National Use
				break;
			
			case 58:
				//Authorizing Agent Institution ID
				break;
			
			case 59:
				//Reserved for National Use
				break;
				
			case 60: 
				//Advice Reason Code
				char Temp[ 100 ];
				
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->ReasonCode, ATOS, 3, bitno );
				memset( Temp, 0, sizeof( Temp ) );
				InBuf += fmt_in( InBuf, Temp, ATOS, len - 3 , bitno );
				break ;

			case 61: 
				//Point-of-Service (POS) Data
				char PosData[ 27 ];
				memset( PosData, 0, sizeof( PosData ) ); 
				InBuf += fmt_in( InBuf, PosData, CHAR, 26, bitno );
				break ;

			case 62: 
				//Intermediate Network Facility (INF) Data
				break ;

			case 63: 
				//Network Data 
				//ISO: ans…999; LLLVAR
				//RSC: an…044; LLVAR
				break ;
				
			case 64:
				//Message Authentication Code (MAC) 
				//Used for  Cryptogram
                break ;

			case 65:
				//Bit Map, Extended
				break ;

			case 66:
				//Settlement Code( Used in MsgType 0530 and 0532 ) --- 1 digit 
                break ;
                
			case 67:
				//Extended Payment Code
				break ;
			
			case 68:
				//Receiving Institution Country Code
				break;
				
			case 69:
				//Settlement Institution Country Code
				InBuf += fmt_in( InBuf, &txnmsg->SettCurrencyCode, ATOS, 3, bitno );
				break;
				
			case 70:
				//Network Management Information Code
				InBuf += fmt_in( InBuf, &txnmsg->NetCode, ATOI, 3, bitno );
				trace( "Net Code [%03d]", txnmsg->NetCode );
				break;
			
            case 71:
            	//Message Number
                break;

            case 72:
            	//Message Number Last
                break;
                  
            case 73:
            	//Date, Action
            	break;
            	
            case 74:
            	// Number of Credits, ( Used in MsgType 0520 and 0522 )
            	break;
            
            case 75:
            	// Number of Credits Reversal, ( Used in MsgType 0520 and 0522 )
            	break;
            
            case 76:
            	// Number of Debits, ( Used in MsgType 0520 and 0522 )
            	break;
            	
            case 77:	
            	// Number of Debits Reversal, ( Used in MsgType 0520 and 0522 )
            	break;

            case 78:
            	// Number of Transfers, ( Used in MsgType 0520 and 0522 )
            	break;
            	
            case 79:	
            	// Number of Transfers Reversal, ( Used in MsgType 0520 and 0522 )
            	break;
            	
            case 80:
            	// Number of Inquiries, ( Used in MsgType 0520 and 0522 )
            	break;
            	
            case 81:
            	// Number of Authorizations, ( Used in MsgType 0520 and 0522 )
            	break;

            case 82:
            	// Credits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 83:
            	// Credits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;
            	
            case 84:
            	// Debits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;
            	
            case 85:
            	// Debits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 86:
            	// Credits Amount, ( Used in MsgType 0520 and 0522 )
            	break;
            
            case 87:
             	// Credits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
             	break;
             	
            case 88:
            	// Debits Amount, ( Used in MsgType 0520 and 0522 )
            	break;
            
            case 89:
             	// Debits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
             	break;

			case 90:
				//Original Data Elements
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld2, CHAR, 42, bitno );
				break ;
				
			case 91:
				//File Update Code
				break;
			
			case 92:
				//File Security Code
				break;
			
			case 93:
				//Response Indicator
				break;
			
			case 94:
				//Service Indicator
				break;
				
			case 95:
				//Replacement Amounts
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld3, CHAR, 42, bitno );
				break ;
				
			case 96:
				//Message Security Code
				break;
				
			case 97:
				//Net Settlement Amount,( Used in MsgType 0530, 0532, 0520 and 0522 )
				break;

			case 98:
				//Payee
				break;
				
			case 99:
				//Settlement Institution ID Code,( Used in MsgType 0530, 0532, 0520 and 0522 )
				break;
				
			case 100:
				//Receiving Institution ID Code
				break;

			case 101:
				//File Name
				break;

			case 102:
				//Account ID-1
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			case 103:
				//Account ID-2
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ToAccount, CHAR, len, bitno );
				break;
				
			case 104:
				//Transaction Description
				break;
				
			case 105:
			case 106:
			case 107:
			case 108:
			case 109:
			case 110:
				//Reserved for ISO Use
				break;
			
			case 111:
				////Amount, Currency Conversion Assessment
				break;
				
			case 112:
			case 113:
			case 114:
			case 115:
			case 116:
			case 117:
			case 118:
			case 119:
				//Reserved for National Use
				break;

			case 120:
				//Record Data
				break;
				
			case 121:
				//Authorizing Agent ID Code
				break;
				
			case 122:
				//Additional Record Data
				break;
				
			case 123:
			case 124:
			case 125:
				//Reserved for Future Definition and RSC Use
				break;
				
			case 126:
				//Switch Private Data --LLLVAR
				break;
				
			case 127:
				//Processor Private Data
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
				
			case 128:
				//Message Authentication Code (MAC)
				break;
				
			default:
				trace( "Unhandled bit in ISO Decompose [%d]", bitno );
		}
	}
	return 1;
}

void EzMasterCardSMS :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 2600 + 1 ];
	char MsgBuffer[ 2600 + 1 ];
	while( 1 )
	{
		trace( "EzMasterCardSMS Waiting for Request to be Serviced" );
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
	EzMasterCardSMS ezmastercardsmsobj;
	ezmastercardsmsobj.InitEzMasterCardSMS( argv[ 0 ] );
	ezmastercardsmsobj.ServiceRequest();
	return 1;
}

