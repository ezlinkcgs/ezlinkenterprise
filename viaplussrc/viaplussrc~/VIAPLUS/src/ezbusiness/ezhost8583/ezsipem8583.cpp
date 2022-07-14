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

	if( CreateChannel( TaskName, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", TaskName );
		trace( "^^^^^^^^^^^EzHost8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%sBitMap.cfg", getenv( "EZDIR_HOME" ), "cfg", "iso8583", TaskName );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzHost8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( initNetworkUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing NetworkUtil..." );
		trace( "~~~~~~~~~~~~~~~~~~EzHost8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	if( initEchoUtil( this ) < 0 )
	{
		trace( "Error in Initializing EchoUtil...." );
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

void EzHost8583 :: removeLeadingZeros( const char *SrcStr, char *DestStr )
{
	int i = 0;
	for( i = 0; i < strlen( SrcStr ); i++ )
	{
		if( SrcStr[ i ] != '0' )
			break;
	}
	strcpy( DestStr, SrcStr + i );
}

void EzHost8583 :: formatAmtOut( const char *Amount, char *OutStr, int Len )
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
		else
			break;	
	}
	strcat( formatStr, "00");
	memset( OutStr, '0', Len - strlen( formatStr ) );
	strcpy( OutStr + Len - strlen( formatStr ), formatStr );
}

void EzHost8583 :: formatAmtIn( const char *Amount, char *OutStr, int Len )
{
	char formatStr[ 50 ];
	char TempAmount[ 12 ], Decimal[ 5 ];
	if( strlen( Amount ) != 0 )
	{
		memset( formatStr, 0, sizeof( formatStr ) );
		memset( TempAmount, 0, sizeof( TempAmount ) );
		memset( Decimal, 0, sizeof( Decimal ) );
		strncpy( Decimal, Amount + ( strlen(Amount) - Len), Len );
		strncpy( TempAmount, Amount, strlen(Amount) - Len );
		sprintf( OutStr, "%d.%s0", atoi(TempAmount), Decimal );
	}
}

int EzHost8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{

	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ], AcctStr[ 50 ], Temp[ 50 ];
	unsigned char BitMap[ 33 ];
	int len;
	BufOffset = OutBuf;

	trace( "MsgType = [%d]", txnmsg->MsgType );


	if( txnmsg->MsgType == 421 || txnmsg->MsgType == 1421 || txnmsg->MsgType == 221 || txnmsg->MsgType == 1221 )
		txnmsg->MsgType = txnmsg->MsgType -1;

	trace( "New MsgType = [%d]", txnmsg->MsgType );

	OutBuf += fmt_out( OutBuf, &txnmsg->MsgType, FMT_ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

	/*if( ( txnmsg->MsgType == 200 ) && ( (txnmsg->TxnCode/10000 ) == 38 ) )
	{
                        SetBitOn( BitMap, 28 );
			trace( "Set bin on 28" );
	}
	*/
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

	if( !strcmp( txnmsg->DeviceType, "POS" ) )
			SetBitOn( BitMap, 42 );

	OutBuf += fmt_out( OutBuf, BitMap, FMT_HTOA, 16, 1 );
	if( IsBitSet( BitMap, 1 ) )
		OutBuf += fmt_out( OutBuf, BitMap + 8, FMT_HTOA, 16, 1 );


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
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				format_str( 6, strlen( txnmsg->chn ) - 4, '*' );
				OutBuf += fmt_out( OutBuf, txnmsg->chn, FMT_CHAR, len, bitno );
				break ;

			case 3:
				OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, FMT_ITOA, 6, bitno );
				break ;

			case 4:
				char TempAmount[13];
				memset( TempAmount, 0, sizeof( TempAmount ) );
				formatAmtOut( txnmsg->Amount, TempAmount, 12 );
				OutBuf += fmt_out( OutBuf, TempAmount, FMT_CHAR, 12, bitno );
				break ;

			case 7:
				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, FMT_ITOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, FMT_ITOA, 6, bitno );
				break ;

			case 11:
				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, FMT_ITOA, 6, bitno );
				break ;

			case 12:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, FMT_ITOA, 6, bitno );
				break;

			case 13:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, FMT_ITOA, 6, bitno );
				break ;

			case 15:
				OutBuf += fmt_out( OutBuf, &txnmsg->BusinessDate, FMT_ITOA, 6, bitno );
				break ;

			case 17:
				OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, FMT_ITOA, 6, bitno );
				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, FMT_STOA, 4, bitno );
				break;
		
			case 28:
				trace(" Fee enabled ");
			 char cfgpath[151];
       			 char str1[16],str2[13],SendFee[13];
       			 int Feelen,cmp,SendFeeFlag;
       			 memset( cfgpath, 0 , sizeof( cfgpath ) );
       			 memset( str1, 0 , sizeof( str1 ) );
        		 memset( str2, 0 , sizeof( str2 ) );
      			 memset( SendFee, 0 , sizeof( SendFee ) );
        		 sprintf( cfgpath, "%s/%s", getenv( "EZDIR_HOME" ),"FeeFile.dat" );
        		 FILE *FeeFile;
          		 FeeFile = fopen( cfgpath, "r" );
        		 if( FeeFile == NULL ) { trace("Error in Reading File[%s]",cfgpath); }
          		 else
            		  {
             		    trace("Path [%s]",cfgpath);
            		    rewind(FeeFile);
             		    fscanf( FeeFile, "%s",str1);
            		  //  trace("%s is ", str1 );
        	            cmp = strcmp(str1,"MinistatementFee");
             		    if (cmp == 0)
              		     {
               		       fscanf( FeeFile, " %s ",str2);
                               strcat(str2,"00");
                          //     trace("|%s|", str2 );
                               Feelen = strlen(str2);
                               if (Feelen == 12) { strcpy(SendFee,str2);SendFeeFlag=1;}
               		       else { SendFeeFlag=0;}
                             }
                            if (cmp != 0) {strcpy(SendFee,"000000000000");trace("Bad config!..Fee Disabled!..Sending Fee[%s]",SendFee);} 
                            if (SendFeeFlag == 1){trace("Fee Amount is [%s]",SendFee );}
                            if (SendFeeFlag != 1){trace("Fee Length Should be 10 Digit.");
                                  strcpy(SendFee,"000000000000");trace("Bad Fee config!..Fee Disabled!..Sending Fee[%s]",SendFee);}
                            fclose( FeeFile );
                           }
                          Feelen=0;cmp=0;SendFeeFlag=0;
                          OutBuf += fmt_out( OutBuf, SendFee, FMT_CHAR, 12, bitno );
                          break;
			
			case 32:
				memset( Temp, 0, sizeof( Temp ) );
				if( txnmsg->MsgType == 800 )
					strcpy( Temp, txnmsg->NetworkId );
				else if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 )
					strcpy( Temp, txnmsg->AcquirerBin );
				else if( txnmsg->MsgType == 1220 || txnmsg->MsgType == 1420 )
					strcpy( Temp, txnmsg->IssuerBin );
				else
				{
					trace("Invaild Msgtype[%d] at 32", txnmsg->MsgType );
					return -1;
				}

				len = strlen( Temp );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, Temp, FMT_CHAR, len, bitno );
				break;

                        case 33:
                                memset( Temp, 0, sizeof( Temp ) );
                                if( txnmsg->MsgType == 800 )
                                        strcpy( Temp, txnmsg->NetworkId );
                                else if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 )
                                        strcpy( Temp, txnmsg->IssuerBin );
                                else if( txnmsg->MsgType == 1220 || txnmsg->MsgType == 1420 )
                                        strcpy( Temp, txnmsg->IssuerBin );
                                else
                                {
                                        trace("Invaild Msgtype[%d] at 32", txnmsg->MsgType );
                                        return -1;
                                }

                                len = strlen( Temp );
                                OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
                                OutBuf += fmt_out( OutBuf, Temp, FMT_CHAR, len, bitno );
                                break;


			case 37:
				OutBuf += fmt_out( OutBuf, &txnmsg->RefNum, FMT_CHAR, 12, bitno );
				break;

			case 39:
				OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, FMT_ITOA, 2, bitno );
				break;

			case 41:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, FMT_CHAR, 8, bitno );
				break ;

			case 42:
				OutBuf += fmt_out( OutBuf, txnmsg->AcceptorId, FMT_CHAR, 15, bitno );
				break ;

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, FMT_CHAR, 40, bitno );
				break;

			case 49:
				OutBuf += fmt_out( OutBuf, &txnmsg->AcqCurrencyCode, FMT_STOA, 3, bitno );
				break;

			case 52:

				format_str( 0, 16, '*' );
				OutBuf += fmt_out( OutBuf, txnmsg->PINBlock, FMT_CHAR, 16, bitno );
				break ;

			case 54:
				break;

			case 60:
				len = strlen( txnmsg->IssBranchCode );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->IssBranchCode, FMT_CHAR, len, bitno );
				break ;

			case 61:
				len = strlen( txnmsg->FromAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAcctSubType, FMT_CHAR, len, bitno );
				break;

			case 62:
				len = strlen( txnmsg->TxfBranchCode );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->TxfBranchCode, FMT_CHAR, len, bitno );
				break ;

			case 63:
				len = strlen( txnmsg->ToAcctSubType );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ToAcctSubType, FMT_CHAR, len, bitno );
				break ;

			case 64:
				len = strlen( txnmsg->RsvFld3 );
				OutBuf += fmt_out( OutBuf, &len, FMT_ATOI, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, FMT_CHAR, len, bitno );
                break ;

			case 65:
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, FMT_CHAR, 6, bitno );
                break ;

        	case 66:
        		len = strlen( txnmsg->RsvFld5 );
        		OutBuf += fmt_out( OutBuf, &len, FMT_ATOI, 2, bitno );
        		OutBuf += fmt_out( OutBuf, txnmsg->RsvFld5, FMT_CHAR, len, bitno );
                break ;

			case 67:
				len = strlen( txnmsg->AcqBranchCode );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcqBranchCode, FMT_CHAR, len, bitno );
				break ;

			case 70:

				txnmsg->NetCode = getOutBoundExtNetCode( txnmsg->NetCode );
				OutBuf += fmt_out( OutBuf, &txnmsg->NetCode, FMT_ITOA, 3, bitno );
				trace( "Net Code [%03d]", txnmsg->NetCode );

				break ;

			 case 71:
                len = strlen( txnmsg->RsvFld1 );
                OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, FMT_CHAR, len, bitno );
                break;

			 case 72:
				 if( txnmsg->MsgType == 900 )
				 {
					 len = strlen( txnmsg->RsvFld2 );
				 	 OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				 	 OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, FMT_CHAR, len, bitno );
				 }
				 break;

			 case 80:
				len = strlen( txnmsg->NetworkId );
                OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, FMT_CHAR, len, bitno );
                break ;

            case 81:
            	len = strlen( txnmsg->RsvFld1 );
                OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, FMT_CHAR, len, bitno );
                break ;

			case 90:

				trace( "Original Data Elements" );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgMsgType, FMT_ITOA, 4, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgTraceNo, FMT_ITOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranDate, FMT_ITOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranTime, FMT_ITOA, 6, bitno );
				memset( Temp, 0, sizeof( Temp ) );
				sprintf( Temp, "%011d", atoi( txnmsg->AcquirerBin ) );
				OutBuf += fmt_out( OutBuf, Temp,  FMT_CHAR, strlen(Temp), bitno );
				memset( Temp, 0, sizeof( Temp ) );
				sprintf( Temp, "%011d", atoi( txnmsg->IssuerBin ) );
				OutBuf += fmt_out( OutBuf, Temp,  FMT_CHAR, strlen(Temp), bitno );

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

				OutBuf += fmt_out( OutBuf, DispAmount,  FMT_CHAR, 12, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "000000000000",  FMT_CHAR, 12, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  FMT_CHAR, 8, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  FMT_CHAR, 8, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  FMT_CHAR, 8, bitno );
				OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  FMT_CHAR, 8, bitno );

				break ;


			case 102:

				memset( AcctStr, 0, sizeof( AcctStr ) );
				unPackAccountNo( txnmsg->IssBranchCode, txnmsg->FromAcctSubType, txnmsg->FromAccount, AcctStr );
				len = strlen( AcctStr );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, AcctStr, FMT_CHAR, len, bitno );
				break;

			case 103:

				memset( AcctStr, 0, sizeof( AcctStr ) );
				unPackAccountNo( txnmsg->TxfBranchCode, txnmsg->ToAcctSubType, txnmsg->ToAccount, AcctStr );
				len = strlen( AcctStr );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, AcctStr, FMT_CHAR, len, bitno );
				break;

			case 127:

				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				strcpy( StmtBuf, txnmsg->RsvFld1 );
				trace( DEBUG_NORMAL, "Reserved Field [%s]\n", StmtBuf );

				len = strlen( StmtBuf );
				OutBuf += fmt_out( OutBuf, &len, FMT_ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, StmtBuf, FMT_CHAR, len, bitno );
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
	char StmtBuf[ STMT_BUF_SIZE + 1 ], AcctStr[ 50 ], Temp[ 50 ];

	InBuf += fmt_in( InBuf, &txnmsg->MsgType, FMT_ATOI, 4 , 0 );


	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmt_in( InBuf, BitMap, FMT_ATOH, 16, 1 );

	if( IsBitSet( BitMap, 1 ) )
		InBuf += fmt_in( InBuf, BitMap + 8, FMT_ATOH, 16, 1 );

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

				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				format_str( 6, len - 4, '*' );
				InBuf += fmt_in( InBuf, txnmsg->chn, FMT_CHAR, len, bitno );
				memset( txnmsg->m_chn, 0, sizeof( txnmsg->m_chn ) );
				ezpadssutil.maskString( txnmsg->chn, 6, strlen( txnmsg->chn ) - 4, '*', txnmsg->m_chn );
				break ;

			case 3:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, FMT_ATOI, 6, bitno );
				break ;

			case 4:
				char TempAmount[15];
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, FMT_CHAR, 12, bitno );
				formatAmtIn( TempAmount, txnmsg->Amount, 2 );
				break ;

			case 7:
				InBuf += fmt_in( InBuf, &txnmsg->TranDate, FMT_ATOI, 6, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, FMT_ATOI, 6, bitno );
				break ;

			case 11:
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, FMT_ATOI, 6, bitno );
				break ;

			case 12:
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, FMT_ATOI, 6, bitno );
				break ;

			case 13:
				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, FMT_ATOI, 6, bitno );
				break ;

			case 15:
				InBuf += fmt_in( InBuf, &txnmsg->BusinessDate, FMT_ATOI, 6, bitno );
				break ;

			case 17:
				InBuf += fmt_in( InBuf, &txnmsg->CaptureDate, FMT_ATOI, 6, bitno );
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, FMT_ATOS, 4, bitno );
				if( txnmsg->MerchantType != 6011 )
					strcpy( txnmsg->DeviceType, "POS" );
				break ;
			
			case 28:
				char tempamt[15];
				memset(tempamt,0,sizeof(tempamt));
				InBuf += fmt_in( InBuf, tempamt, FMT_CHAR, 12, bitno );
                                trace("Fee from CBS [%s] ", tempamt );
				break ;
			case 32:
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, Temp, FMT_CHAR, len, bitno );
				break ;

                        case 33:
                                InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
                                InBuf += fmt_in( InBuf, Temp, FMT_CHAR, len, bitno );
                                break ;

			case 37:
				InBuf += fmt_in( InBuf, &txnmsg->RefNum, FMT_CHAR, 12, bitno );
				break ;

			case 38:
                                InBuf += fmt_in( InBuf, &txnmsg->AuthCode, FMT_ATOI, 6, bitno );
                                break ;

			case 39:

				InBuf += fmt_in( InBuf, &txnmsg->RespCode, FMT_ATOI, 2, bitno );
				txnmsg->RespCode = getInBoundSwitchRespCode( txnmsg->RespCode );
				trace( "RespCode[%d]", txnmsg->RespCode );
				break ;

			case 41:
				char TempStr[ 50 ];
				memset( TempStr, 0, sizeof( TempStr ) );
				InBuf += fmt_in( InBuf, TempStr, FMT_CHAR, 8, bitno );
				memset( txnmsg->TerminalId, 0, sizeof ( txnmsg->TerminalId ) );
				for( int k = 0, j = 0; k < strlen( TempStr ); k++ )
				{
					if( TempStr[ k ] != ' ' )
					{
						txnmsg->TerminalId[ j ] = TempStr[ k ];
						j++;
					}
				}
				break ;

			case 42:

				InBuf += fmt_in( InBuf, txnmsg->AcceptorId, FMT_CHAR, 15, bitno );
				break;

			case 43:

				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, FMT_CHAR, 40, bitno );
				break;

			case 49:

				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, FMT_ATOS, 3, bitno );
				break;

			case 52:

				format_str( 0, 16, '*' );
				InBuf += fmt_in( InBuf, txnmsg->PINBlock, FMT_CHAR, 16, bitno );
				break;

			case 54:
				char tempStr[ 20 ], amtType[ 3 ];
				char Balance[ 15 ];
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				for( int i = 0; i < len; )
				{
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, FMT_CHAR, 2, bitno );
					i += 2;
					memset( amtType, 0, sizeof( amtType ) );
					InBuf += fmt_in( InBuf, amtType, FMT_CHAR, 2, bitno );
					i += 2;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, FMT_CHAR, 3, bitno );
					i += 3;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, FMT_CHAR, 1, bitno );
					i += 1;
				/*	if( !strcmp( amtType, "02" ) )
					{
						memset( Balance, 0, sizeof( Balance ) );
						InBuf += fmt_in( InBuf, Balance, FMT_CHAR, 12, bitno );
						removeLeadingZeros( Balance, txnmsg->AvailBalance );
						trace( "Balance[%s]", Balance );
					}
					else
					{
						memset( Balance, 0, sizeof( Balance ) );
						InBuf += fmt_in( InBuf, Balance, FMT_CHAR, 12, bitno );
						removeLeadingZeros( Balance, txnmsg->LedgerBalance );
						trace( "Balance[%s]", Balance );
					}*/
                                        if( !strcmp( amtType, "02" ) )
                                        {
                                                memset( Balance, 0, sizeof( Balance ) );
                                                InBuf += fmt_in( InBuf, Balance, FMT_CHAR, 12, bitno );
                                                memset( tempStr, 0, sizeof( tempStr ) );
                                                strncpy( tempStr, Balance, 10 );
                                                strcat( tempStr, "." );
                                                strcat( tempStr, Balance + 10 );
						strcat( tempStr, "0" );
                                                removeLeadingZeros( tempStr, txnmsg->AvailBalance );
                                                trace( "Balance[%s]", tempStr );
                                        }
                                        else
                                        {
                                                memset( Balance, 0, sizeof( Balance ) );
                                                InBuf += fmt_in( InBuf, Balance, FMT_CHAR, 12, bitno );
                                                memset( tempStr, 0, sizeof( tempStr ) );
                                                strncpy( tempStr, Balance, 10 );
                                                strcat( tempStr, "." );
                                                strcat( tempStr, Balance + 10 );
						strcat( tempStr, "0" );
                                                removeLeadingZeros( tempStr, txnmsg->LedgerBalance );
                                                trace( "Balance[%s]", tempStr );
                                        }
					i += 12;
				}

				break ;

			case 60:
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->IssBranchCode, FMT_CHAR, len, bitno );
				break ;

			case 61:
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAcctSubType, FMT_CHAR, len, bitno );
				break ;

			case 62:
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->TxfBranchCode, FMT_CHAR, len, bitno );
				break ;

			case 63:
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ToAcctSubType, FMT_CHAR, len, bitno );
				break ;

			case 64:
                len = strlen( txnmsg->RsvFld3 );
                InBuf += fmt_in( InBuf, &len, FMT_ITOA, 2, Ind + 1 );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld3, FMT_CHAR, len, bitno );
                break ;

			case 65:
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, FMT_CHAR, 6, bitno );
                break ;

			case 66:
                len = strlen( txnmsg->RsvFld5 );
                InBuf += fmt_in( InBuf, &len, FMT_ITOA, 2, Ind + 1 );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld5, FMT_CHAR, len, bitno );
                break ;

			case 67:
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcqBranchCode, FMT_CHAR, len, bitno );
				break ;

			case 70:
				InBuf += fmt_in( InBuf, &txnmsg->NetCode, FMT_ATOI, 3, bitno );
				txnmsg->NetCode = getInBoundSwitchNetCode( txnmsg->NetCode );
				trace( "Net Code [%03d]", txnmsg->NetCode );
				break ;

            case 71:
                InBuf += fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, FMT_CHAR, len, bitno );
                trace( "Host Data 1 [%s]\n", txnmsg->RsvFld1 );
                break ;

            case 72:
                InBuf += fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld2, FMT_CHAR, len, bitno );
                trace( "Host Data 2 [%s]\n", txnmsg->RsvFld2 );
                break ;
            case 80:
                InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->NetworkId, FMT_CHAR, len, bitno );
                break ;
            case 81:
                InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, FMT_CHAR, len, bitno );
                break ;

			case 90:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld2, FMT_CHAR, 44, bitno );
				break ;

			case 95:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld3, FMT_CHAR, 44, bitno );
				break ;

			case 102:

				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				memset( AcctStr, 0, sizeof( AcctStr ) );
				InBuf += fmt_in( InBuf, AcctStr, FMT_CHAR, len, bitno );
				packAccountNo( txnmsg->IssBranchCode, txnmsg->FromAcctSubType, AcctStr, txnmsg->FromAccount );
				break;

			case 103:

				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 2, bitno );
				memset( AcctStr, 0, sizeof( AcctStr ) );
				InBuf += fmt_in( InBuf, AcctStr, FMT_CHAR, len, bitno );
				packAccountNo( txnmsg->TxfBranchCode, txnmsg->ToAcctSubType, AcctStr, txnmsg->ToAccount );
				break;

			case 127:

				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				InBuf += fmt_in( InBuf, &len, FMT_ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, StmtBuf, FMT_CHAR, len, bitno );

				strcpy( txnmsg->RsvFld1, StmtBuf );
				trace( "RsvFld1[%s]", txnmsg->RsvFld1 );

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
	char ISOMessage[ 4096 + 1 ];
	char MsgBuffer[ 4096 + 1 ];
	struct EzEchoTable echotable_rec;

	while( 1 )
	{
		trace( "EzHost8583 Waiting for Request to be Serviced" );
		trace("EzSIPEM8583 Started");
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetSourceChannelName() );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			if( DecomposeISOMessage( ISOMessage, &txnmsg ) < 0 )
			{
				trace( "Error in Decomposing ISO Message from Port[%s]", GetLastSenderChannelName() );
				continue;
			}

			memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
			if( getNetworkIdFromPort( GetLastSenderChannelName(), txnmsg.NetworkId ) < 0 )
				trace( "Error in Reading NetworkId for Port[%s]...", GetLastSenderChannelName() );

			if( txnmsg.MsgType == 810 )
			{
				memset( &echotable_rec, 0, sizeof( struct EzEchoTable ) );
				if( readEchoTable( txnmsg.NetworkId, &echotable_rec ) < 0 )
				{
					trace( "Error in Reading NetworkId[%s] from Echo Table....", txnmsg.NetworkId );
					continue;
				}
				if( txnmsg.NetCode == EZLINK_NETCODE_LOGON && !txnmsg.RespCode )
				{
					if( echotable_rec.EchoRespStatus == ECHO_RESP_STATUS_SIGNON_SENT )
					{
						trace( "Expecting a Response for SignOn...but got Response for LogOn....for NetworkId[%s]", txnmsg.NetworkId );
						continue;
					}
					if( updateEchoRespStatus( txnmsg.NetworkId, ECHO_RESP_STATUS_LOGON_RCVD ) < 0 )
						trace( "Error in Updating LogOnStatus for NetworkId[%s]", txnmsg.NetworkId );

					if( getNetworkStatus() == NETWORK_STATUS_DOWN )
					{
						if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
							trace( "Error in Updating Status for NetworkId[%s]", txnmsg.NetworkId );

					}
					txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
					if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
						trace( "Error in Sending Intimation Message to EzSafReader" );
					else
						trace( "Sent Intimation Message to EzSafReader" );

					continue;
				}
				else if ( txnmsg.NetCode == EZLINK_NETCODE_SIGNON && !txnmsg.RespCode )
				{
					if( echotable_rec.EchoRespStatus == ECHO_RESP_STATUS_LOGON_SENT )
					{
						trace( "Expecting a Response for LogOn...but got Response for SignOn....for NetworkId[%s]", txnmsg.NetworkId );
						continue;
					}
					if( updateEchoRespStatus( txnmsg.NetworkId, ECHO_RESP_STATUS_SIGNON_RCVD ) < 0 )
						trace( "Error in Updating SignOnStatus for NetworkId[%s]", txnmsg.NetworkId );
					if( getNetworkStatus() == NETWORK_STATUS_DOWN )
					{
						if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
							trace( "Error in Updating Status for NetworkId[%s]", txnmsg.NetworkId );
					}
					txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
					if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
						trace( "Error in Sending Intimation Message to EzSafReader" );
					else
						trace( "Sent Intimation Message to EzSafReader" );

					continue;
				}
			}



			if( WriteChannel( "EzTxnMgr", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
				trace( "Error in Writing Message to Channel EzTxnMgr" );
			else
				trace( "Message Successfully Written to Channel EzTxnMgr" );
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

