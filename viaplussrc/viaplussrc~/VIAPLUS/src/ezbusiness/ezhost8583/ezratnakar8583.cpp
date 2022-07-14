#include <ezbusiness/ezhost8583.h>
#include <ezutils/ezdatetimeutil.h>

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
	sprintf( BitMapFile, "%s/%s/%s/%sBitMap.cfg", getenv( "EZDIR_HOME" ), "cfg", "iso8583", TaskName );

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

/*int EzHost8583 :: getUBPToAcct( int TxnCode, char *ToAcct )
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
}*/

void EzHost8583 :: removeLeadingZeros( const char *SrcStr, char *DestStr )
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

int EzHost8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ], temp[10], tempbin[7], temptxn[7];
	unsigned char BitMap[ 33 ];
	int len;
	EzDateTimeUtil dtu;
	int Date = 0, time = 0, ExtMsgType = 0;

	BufOffset = OutBuf;

	/*Changing the MsgType As per the CMS Req*/
	/*if( txnmsg->MsgType == 800 )
	{
		txnmsg->MsgType = 1804;
		txnmsg->TranDate = dtu.getSysDate();
		txnmsg->TranTime = dtu.getSysTime();
		txnmsg->TraceNo = 1;
		trace("MT<%d>TD<%d>TT<%d>TN<%d>", txnmsg->MsgType, txnmsg->TranDate, txnmsg->TranTime, txnmsg->TraceNo );
	}
	else if( txnmsg->MsgType == 200 )
		txnmsg->MsgType = 1200;
	else if( txnmsg->MsgType == 420 )
		txnmsg->MsgType = 1420;
	 */
	trace( "Switch MsgType [%d]", txnmsg->MsgType );
	ExtMsgType = getOutBoundExtMsgType( txnmsg->MsgType );
	OutBuf += fmt_out( OutBuf, &ExtMsgType, ITOA, 4, 0 );
	trace( "Ext MsgType [%d]", ExtMsgType );

	trace( "IIN [%s]", txnmsg->AcquirerBin );

	if( ExtMsgType == 1804 )
	{
		txnmsg->TranDate = dtu.getSysDate();
		txnmsg->TranTime = dtu.getSysTime();
		txnmsg->TraceNo = 1;
		trace("MT<%d>TD<%d>TT<%d>TN<%d>", txnmsg->MsgType, txnmsg->TranDate, txnmsg->TranTime, txnmsg->TraceNo );
	}

	if( txnmsg->TxnCode/10000 == 1 )
	{
		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%06d", txnmsg->TxnCode );
		memset( temptxn, 0, sizeof( temptxn ) );
		strcpy( temptxn, "17" );
		strcat( temptxn, temp + 2 );
		trace( "temptxn[%s]",temptxn);
	}
	else if( txnmsg->TxnCode/10000 == 38 )
	{
		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%06d", txnmsg->TxnCode );
		memset( temptxn, 0, sizeof( temptxn ) );
		strcpy( temptxn, "91" );
		strcat( temptxn, temp + 2 );
		trace( "temptxn[%s]",temptxn);
	}
	else if( txnmsg->TxnCode/10000 == 30 )
	{
		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%06d", txnmsg->TxnCode );
		memset( temptxn, 0, sizeof( temptxn ) );
		strcpy( temptxn, "31" );
		strcat( temptxn, temp + 2 );
		trace( "temptxn[%s]",temptxn);
	}
	else
	{
		memset( temptxn, 0, sizeof( temptxn ) );
		sprintf( temptxn, "%06d", txnmsg->TxnCode );
	}

	if( txnmsg->MsgType != ExtMsgType )
	{
		memset( tempbin, 0, sizeof( tempbin ) );
		strncpy( tempbin, txnmsg->chn, 6 );
		trace( "tempbin[%s]", tempbin );
	}

	if( ExtMsgType == 1420 )
	{
		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%06d", txnmsg->TxnCode );
		memset( temptxn, 0, sizeof( temptxn ) );
		strcpy( temptxn, "15" );
		strcat( temptxn, temp + 2 );
		trace( "temptxn[%s]",temptxn);
	}

	trace( "Loading BitMap for MsgType[%d]", ExtMsgType );
	memset( BitMap, 0, sizeof( BitMap ) );
	if( LoadBitMap( BitMap, ExtMsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", ExtMsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

	//Changes for Remote Issuer
	/*if( strcmp( txnmsg->AcquirerInst, txnmsg->IssuerInst ) && ( txnmsg->TxnCode/10000 == 1 ) )
		SetBitOn( BitMap, 46 );*/

	memcpy( OutBuf, BitMap, 8 );
	OutBuf += 8;

	if( IsBitSet( BitMap, 1 ) )
	{
		memcpy( OutBuf, BitMap + 8, 8 );
		OutBuf += 8;
	}
	hex_dump( (unsigned char *)BitMap, 16 );

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
				//OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, temptxn, CHAR, 6, bitno );
				break ;

			case 4:
				char TempAmount[13];
				int Amount;

				memset( TempAmount, 0, sizeof( TempAmount ) );
				if( txnmsg->RespCode == 102 )
				{
					if( strlen( txnmsg->DispAmount ) <= 0 )
						strncpy( TempAmount, "000000000000", 12 );
					else if( txnmsg->MerchantType == 6011 )
					{
						if( ( txnmsg->TxnCode/10000 ) == 17 )
							Amount = atoi( txnmsg->DispAmount ) * 100;
						else
						{
							memset( TempAmount, 0, sizeof( TempAmount ) );
							for( int i = 0, j = 0; i <= strlen( txnmsg->DispAmount ); i++ )
							{
								if( txnmsg->DispAmount[i] != '.' )
								{
									TempAmount[j] = txnmsg->DispAmount[i];
									j++;
								}
							}
							Amount = atoi( TempAmount );
						}
						sprintf( TempAmount, "%012d", Amount );
					}
					else
						strcpy( TempAmount, txnmsg->DispAmount );
				}
				else
				{
					if( strlen( txnmsg->Amount ) <= 0 )
						strncpy( TempAmount, "000000000000", 12 );
					else if( txnmsg->MerchantType == 6011 )
					{
						if( ( txnmsg->TxnCode/10000 ) == 17 )
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
					else
						strcpy( TempAmount, txnmsg->Amount );
				}

				OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
				break ;

			case 7:
				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );
				break ;

			case 11:
				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break ;

			case 12:
				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break;

			case 13:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, LTOA, 6, bitno );
				break ;

			case 17:
				memset( temp, 0, sizeof( temp ) );
				sprintf( temp, "%06d", txnmsg->CaptureDate );
				OutBuf += fmt_out( OutBuf, temp, CHAR, 4, bitno );
				//OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, LTOA, 4, bitno );
				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 24://function code
				if( ExtMsgType == 1804 || ExtMsgType == 1814 )
					len = 831;
				else if( ExtMsgType == 1200 )
				{
					if( atoi( temptxn )/10000 == 17 )
						len = 200;
					else if( atoi( temptxn )/10000 == 31 )
						len = 281;
					else if( atoi( temptxn )/10000 == 91 )
						len = 100;
					else if( atoi( temptxn )/10000 == 40 )
						len = 200;
				}
				else if( ExtMsgType == 1420 )
					len = 400;

				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break;

			case 30:
				//fixed 24
				// requested amount and field 4 will be disp amount
				if( ( txnmsg->TxnCode/10000 ) == 17 )
					Amount = atoi( txnmsg->DispAmount ) * 100;
				else
				{
					memset( TempAmount, 0, sizeof( TempAmount ) );
					for( int i = 0, j = 0; i <= strlen( txnmsg->DispAmount ); i++ )
					{
						if( txnmsg->DispAmount[i] != '.' )
						{
							TempAmount[j] = txnmsg->DispAmount[i];
							j++;
						}
					}
					Amount = atoi( TempAmount );
				}
				sprintf( TempAmount, "%024d", Amount );
				OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 24, bitno );
				break;

			case 32:
				/*len = strlen( txnmsg->NetworkId );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, CHAR, len, bitno );*/

				len = strlen( txnmsg->AcquirerBin );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcquirerBin, CHAR, len, bitno );
				break;

			case 37:
				OutBuf += fmt_out( OutBuf, &txnmsg->RefNum, CHAR, 12, bitno );
				break;

			case 39:
				OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 3, bitno );
				break;

			case 41:
				//OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 46:
				char fee[14];
				memset( fee, 0, sizeof( fee ) );
				if( txnmsg->TxnCode/10000 == 1 )
					strcpy( fee, "000000001800");
				else
					strcpy( fee, "000000000883");

				len = strlen( fee );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, fee, CHAR, len, bitno );
				break;

			case 49:
				OutBuf += fmt_out( OutBuf, &txnmsg->AcqCurrencyCode, ITOA, 3, bitno );
				break;

			case 54:
				break;

			case 56://org_data_element
				char Data[36];


				if( txnmsg->OrgMsgType == 200 )
					txnmsg->OrgMsgType = 1200;

				len = strlen( txnmsg->AcquirerBin );

				memset( Data, 0, sizeof( Data ) );
				sprintf( Data, "%04d%06d%06d%06d%02d%s", txnmsg->OrgMsgType, txnmsg->OrgTraceNo, txnmsg->OrgTranDate, txnmsg->OrgTranTime, len, txnmsg->AcquirerBin );

				trace( "Original Data Elements[ %s ]", Data );
				len = strlen( Data );

				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, Data, CHAR, len, bitno );
				break;

			case 59://transport_data
				memset( temp, 0, sizeof( temp ) );
				strcpy( temp, "123");
				len = strlen( temp );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, temp, CHAR, len, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset );
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
				OutBuf += fmt_out( OutBuf, &len, ATOI, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, CHAR, len, bitno );
                break ;

			case 65:
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

        	case 66:
        		len = strlen( txnmsg->RsvFld5 );
        		OutBuf += fmt_out( OutBuf, &len, ATOI, 2, bitno );
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

			 case 72:
				 if( txnmsg->MsgType == 900 )
				 {
					 len = strlen( txnmsg->RsvFld2 );
				 	 OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				 	 OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				 }
				 break;

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

			case 93://tx_des_ins_id_cod
				memset( temp, 0, sizeof( temp ) );
				strcpy( temp, "123");
				len = strlen( temp );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, temp, CHAR, len, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break;

			case 94://tx_org_ins_id_cod
				memset( temp, 0, sizeof( temp ) );
				strcpy( temp, "123");
				len = strlen( temp );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, temp, CHAR, len, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break;

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
				len = strlen( txnmsg->FromAccount );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			case 103:
				len = strlen( txnmsg->ToAccount );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->ToAccount, CHAR, len, bitno );
				break;

			case 121://reserved_pvt121
				//lllvar fee indicator 0 or 1
				break;

			case 123://reserved_pvt123
				memset( temp, 0, sizeof( temp ) );
				if( txnmsg->MsgType == 1804 )
					strcpy( temp, "ATM");
				else
				{
					if( strcmp( txnmsg->AcquirerInst, txnmsg->IssuerInst ) )
					{
						if( !strcmp( txnmsg->AcquirerInst, "NFS" ) )
							strcpy( temp, "NFS");
						else if( !strcmp( txnmsg->AcquirerInst, "BANCS" ) )
							strcpy( temp, "BAN");
					}
					else
						strcpy( temp, "SWT");
				}
				len = strlen( temp );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, temp, CHAR, len, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break;

			case 124://reserved_pvt124
				memset( temp, 0, sizeof( temp ) );
				if( txnmsg->MerchantType == 6011 )
					strcpy( temp, "ATM");
				else if( txnmsg->MerchantType == 6014 )
					strcpy( temp, "PHONE");
				else if( txnmsg->MerchantType == 6015 )
					strcpy( temp, "MOBILE");

				len = strlen( temp );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, temp, CHAR, len, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
				break;

			case 126://reserved_pvt126
				memset( temp, 0, sizeof( temp ) );
				strcpy( temp, "2010");
				len = strlen( temp );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, temp, CHAR, len, bitno );

				//hex_dump( (unsigned char *)BufOffset, OutBuf-BufOffset);
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

	//hex_dump( (unsigned char *)BufOffset, OutBuf - BufOffset );
	return( OutBuf - BufOffset );
}


int EzHost8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len, ExtMsgType = 0, ExtRespCode;
	char StmtBuf[ STMT_BUF_SIZE + 1 ], temptxn[7];
	char TempAmount[25], temp[25], decimal[3];
	int Amount;

	InBuf += fmt_in( InBuf, &ExtMsgType, ATOI, 4 , 0 );
	trace( "Ext MsgType [%d]", ExtMsgType );
	txnmsg->MsgType = getInBoundSwitchMsgType( ExtMsgType );
	trace( "Switch MsgType [%d]", txnmsg->MsgType );

	memset( BitMap, 0, sizeof( BitMap ) );
	memcpy( BitMap, InBuf, 16 );
	hex_dump( (unsigned char *)BitMap, 16 );
	InBuf += 16;

	//InBuf += fmt_in( InBuf, BitMap, ATOH, 16, 1 );


	if( txnmsg->MsgType == 810 )
		strcpy( txnmsg->NetworkId, "RATNAKARCBS");

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
				if( txnmsg->TxnCode/10000 == 17 )
				{
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%06d", txnmsg->TxnCode );
					memset( temptxn, 0, sizeof( temptxn ) );
					strcpy( temptxn, "1" );
					strcat( temptxn, temp + 2 );
					trace( "temptxn[%s]",temptxn);
				}
				else if( txnmsg->TxnCode/10000 == 91 )
				{
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%06d", txnmsg->TxnCode );
					memset( temptxn, 0, sizeof( temptxn ) );
					strcpy( temptxn, "38" );
					strcat( temptxn, temp + 2 );
					trace( "temptxn[%s]",temptxn);
				}
				else if( txnmsg->TxnCode/10000 == 31 )
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

				if( txnmsg->MsgType == 430 )
				{
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%06d", txnmsg->TxnCode );
					memset( temptxn, 0, sizeof( temptxn ) );
					strcpy( temptxn, "01" );
					strcat( temptxn, temp + 2 );
					trace( "temptxn[%s]",temptxn);
				}

				txnmsg->TxnCode = atoi( temptxn );
				break ;

			case 4:
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
					memset( TempAmount, 0, sizeof( TempAmount ) );
					sprintf( TempAmount, "%s.%s", temp, decimal);
					memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
					removeLeadingZeros( TempAmount, txnmsg->Amount );
				}
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
				InBuf += fmt_in( InBuf, &txnmsg->TranDate, ATOL, 6, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, bitno );
				//InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOL, 6, bitno );
				//InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, bitno );
				break ;

			case 13:
				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOL, 6, bitno );
				break ;

			case 17:
				InBuf += fmt_in( InBuf, &txnmsg->CaptureDate, ATOL, 4, bitno );
				txnmsg->CaptureDate = txnmsg->TranDate;
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;

			case 24:
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, 3, bitno );
				break ;

			case 30:
				strcpy( txnmsg->DispAmount, txnmsg->Amount );
				memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
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
					memset( TempAmount, 0, sizeof( TempAmount ) );
					sprintf( TempAmount, "%s.%s", temp, decimal);
					memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
					removeLeadingZeros( TempAmount, txnmsg->Amount );
				}
				break;

			case 32:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcquirerBin, CHAR, len, bitno );
				break ;

			case 37:
				InBuf += fmt_in( InBuf, &txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 39:
				InBuf += fmt_in( InBuf, &ExtRespCode, ATOI, 3, bitno );
				txnmsg->RespCode = getInBoundSwitchRespCode( ExtRespCode );
				trace("Switch Respcode[ %d ]", txnmsg->RespCode );
				break ;

			case 41:
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 43:
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 46:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, len, bitno );

				memset( temp, 0, sizeof( temp ) );
				memset( decimal, 0, sizeof( decimal ) );
				trace( "TempAmount[%s]", TempAmount);
				strncpy( temp, TempAmount, strlen( TempAmount )-2 );
				strncpy( decimal, TempAmount + strlen( TempAmount ) - 2, 2 );
				trace( "Amount[%s] Decimal[%s]", temp, decimal );
				memset( TempAmount, 0, sizeof( TempAmount ) );
				sprintf( TempAmount, "%s.%s", temp, decimal);
				memset( txnmsg->TxnFee, 0, sizeof( txnmsg->TxnFee ) );
				removeLeadingZeros( TempAmount, txnmsg->TxnFee );

				trace("Transaction Fee[%s]", txnmsg->TxnFee);
				break ;

			case 48:
				char tempStr[ 20 ], amtType[ 3 ];
				char Balance[ 20 ];
				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, StmtBuf, CHAR, len, bitno );

				for( int i = 0; i < len; )
				{
					if( i == 0 )
					{
						memset( Balance, 0, sizeof( Balance ) );
						strncpy( Balance, StmtBuf, 17 );
						trace("Balance[%s]",Balance);
						memset( tempStr, 0, sizeof( tempStr ) );
						removeLeadingZeros( Balance, tempStr );
						if( atoi( tempStr ) != 0 )
						{
							strncpy( txnmsg->LedgerBalance, tempStr, strlen( tempStr ) - 2 );
							strcat( txnmsg->LedgerBalance,"." );
							strncat( txnmsg->LedgerBalance, tempStr + strlen( tempStr ) - 2, 2 );
							trace("Balance[%s]",txnmsg->LedgerBalance);
						}
						else
							strcpy( txnmsg->LedgerBalance,"0.00" );
					}
					else
					{
						memset( Balance, 0, sizeof( Balance ) );
						strncpy( Balance, StmtBuf + 17, 17 );
						trace("Balance1[%s]",Balance);
						memset( tempStr, 0, sizeof( tempStr ) );
						removeLeadingZeros( Balance, tempStr );
						if( atoi( tempStr ) != 0 )
						{
							strncpy( txnmsg->AvailBalance, tempStr, strlen( tempStr ) - 2 );
							strcat( txnmsg->AvailBalance,"." );
							strncat( txnmsg->AvailBalance, tempStr + strlen( tempStr ) - 2, 2 );
							trace("Balance1[%s]",txnmsg->AvailBalance);
						}
						else
							strcpy( txnmsg->AvailBalance,"0.00" );
						break;
					}
					i += 17;
				}
				break;

			case 49:
				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOI, 3, bitno );
				break;

			case 54:
				/*char tempStr[ 20 ], amtType[ 3 ];
				char Balance[ 15 ];
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
						removeLeadingZeros( Balance, txnmsg->AvailBalance );
					}
					else
					{
						memset( Balance, 0, sizeof( Balance ) );
						InBuf += fmt_in( InBuf, Balance, CHAR, 12, bitno );
						removeLeadingZeros( Balance, txnmsg->LedgerBalance );
					}
					i += 12;
				}*/

				break ;

			case 56:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld2, CHAR, len, bitno );
				break;

			case 59:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, len, bitno );
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
                len = strlen( txnmsg->RsvFld3 );
                InBuf += fmt_in( InBuf, &len, ITOA, 2, Ind + 1 );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, bitno );
                break ;

			case 65:
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

			case 66:
                len = strlen( txnmsg->RsvFld5 );
                InBuf += fmt_in( InBuf, &len, ITOA, 2, Ind + 1 );
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
                InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, bitno );
                break ;

			case 90:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld2, CHAR, 44, bitno );
				break ;

			case 93:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, len, bitno );
				break ;

			case 94:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, len, bitno );
				break ;

			case 95:
				InBuf += fmt_in( InBuf, &txnmsg->RsvFld3, CHAR, 44, bitno );
				break ;

			case 102:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			case 103:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->ToAccount, CHAR, len, bitno );
				break;

			case 123:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, len, bitno );
				break ;

			case 124:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, len, bitno );
				if( !strcmp( temp, "ATM" ) )
					txnmsg->MerchantType = 6011;
				else if( !strcmp( temp, "PHONE" ) )
					txnmsg->MerchantType = 6014;
				else if( !strcmp( temp, "MOBILE" ) )
					txnmsg->MerchantType = 6015;
				break ;

			case 125:
				char TempBuf[ 80 ];
				memset( StmtBuf, 0, sizeof( StmtBuf ) );

				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, StmtBuf, CHAR, len, bitno );

				for( int i = 0, j = 0 ; i < len; j ++ )
				{
					memset( TempBuf, 0, sizeof( TempBuf ) );
					if( i == 0 )
					{
						strncpy( TempBuf, StmtBuf, 72 );
						//trace( "TempBuf[%s]",TempBuf);
						strncpy( txnmsg->RsvFld1, TempBuf, 40 );
						//trace( "txnmsg->RsvFld1[%s]",txnmsg->RsvFld1);
					}
					else
					{
						strncpy( TempBuf, StmtBuf + ( j * 72 ), 72 );
						//trace( "TempBuf[%s][%d]",TempBuf,j);
						strncat( txnmsg->RsvFld1, TempBuf, 40 );
						//trace( "txnmsg->RsvFld1[%s]",txnmsg->RsvFld1);
					}
					i+=72;
				}
				break;

			case 126:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				memset( temp, 0, sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, len, bitno );
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

			memset( txnmsg.SrcPort, 0, sizeof( txnmsg.SrcPort ) );
			strcpy( txnmsg.SrcPort, GetLastSenderChannelName() );

			if( txnmsg.MsgType == 1804 )
			{
				memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
				txnmsg.MsgType = 1814;
				MsgSize = ComposeISOMessage( &txnmsg, MsgBuffer ) ;
				trace("MsgSize[%d]", MsgSize);
				if( MsgSize < 0 )
				{
					trace( "Error in Composing ISO Message" );
					continue;
				}

				strcpy( txnmsg.DestPort, GetSourceChannelName() );
				hex_dump( ( unsigned char * ) MsgBuffer, MsgSize );
				if( WritePortChannel( txnmsg.DestPort, MsgBuffer, MsgSize ) < 0 )
					trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
				else
					trace( "Written Message to Port[%s]", txnmsg.DestPort );
			}
			else
			{
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
			MsgSize = ComposeISOMessage( &txnmsg, MsgBuffer ) ;
			trace("MsgSize[%d]", MsgSize);
			if( MsgSize < 0 )
			{
				trace( "Error in Composing ISO Message" );
				continue;
			}

			hex_dump( ( unsigned char * ) MsgBuffer, MsgSize );

			if( WritePortChannel( txnmsg.DestPort, MsgBuffer, MsgSize ) < 0 )
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

