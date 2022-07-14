#include <ezbusiness/ezprepaid8583.h>

EzPrepaid8583:: EzPrepaid8583()
{
}

EzPrepaid8583 :: ~EzPrepaid8583()
{
}

void EzPrepaid8583 :: InitEzPrepaid8583( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];
	char BancsInfPath[ CFG_PATH_SIZE + 1 ], CfgParam[ CFG_VAL_SIZE + 1 ], ParamStr[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	TraceNo = 1;
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", TaskName );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^%s Started Running^^^^^^^^^^^^^", TaskName);

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^",TaskName);
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( TaskName, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", TaskName );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", TaskName, "BitMap.cfg" );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzBancs8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	//open file bancsinf.cfg

	memset( BancsInfPath, 0, sizeof( BancsInfPath ) );
	sprintf( BancsInfPath, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583","EzBancsInf.cfg" );

	if( cfgutil.cfg_open( BancsInfPath ) < 0 )
	{
		trace( " Error in opening the EzBancsInf.cfg " );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName);
		closeDebug();
		TaskExit();
	}

	memset( &ezbancsmsg, 0, sizeof( ezbancsmsg ) );

	memset( CfgParam, 0, sizeof( CfgParam ) );
    sprintf( CfgParam, "%s#%s", "BANK_INF", "ISOHEADER" );

    memset( ParamStr, 0, sizeof( ParamStr ) );
    if( cfgutil.cfg_search( CfgParam, ParamStr, 2 ) < 0 )
    {
    	trace("\nError in Searching ISOHEADER from File[%s]\n", "EzBancsInf.cfg" );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName);
		closeDebug();
		cfgutil.cfg_close();
		TaskExit();
	}
    else
    	strcpy( ezbancsmsg.IsoHeader, ParamStr );

	memset( CfgParam, 0, sizeof( CfgParam ) );
    sprintf( CfgParam, "%s#%s", "BANK_INF", "ACCEPT_ID_CODE" );

    memset( ParamStr, 0, sizeof( ParamStr ) );
    if( cfgutil.cfg_search( CfgParam, ParamStr, 2 ) < 0 )
    {
    	trace("\nError in Searching ACCEPT_ID_CODE from File[%s]\n", "EzBancsInf.cfg" );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName);
		closeDebug();
		cfgutil.cfg_close();
		TaskExit();
	}
    else
    	strcpy( ezbancsmsg.AcceptIDCode, ParamStr );

	memset( CfgParam, 0, sizeof( CfgParam ) );
    sprintf( CfgParam, "%s#%s", "BANK_INF", "CURR_CODE" );
    memset( ParamStr, 0, sizeof( ParamStr ) );
    if( cfgutil.cfg_search( CfgParam, ParamStr, 2 ) < 0 )
    {
       	trace("\nError in Searching CURR_CODE from File[%s]\n", "EzBancsInf.cfg" );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName);
		closeDebug();
		cfgutil.cfg_close();
		TaskExit();
	}
    else
        strcpy( ezbancsmsg.CurrCode, ParamStr );

	memset( CfgParam, 0, sizeof( CfgParam ) );
    sprintf( CfgParam, "%s#%s", "BANK_INF", "INSTID" );
    memset( ParamStr, 0, sizeof( ParamStr ) );
    if( cfgutil.cfg_search( CfgParam, ParamStr, 2 ) < 0 )
    {
    	trace("\nError in Searching INSTID from File[%s]\n", "EzBancsInf.cfg" );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName);
		closeDebug();
		cfgutil.cfg_close();
		TaskExit();
	}
    else
        strcpy( ezbancsmsg.InstId, ParamStr );

	memset( CfgParam, 0, sizeof( CfgParam ) );
    sprintf( CfgParam, "%s#%s", "BANK_INF", "BIN" );
    memset( ParamStr, 0, sizeof( ParamStr ) );
    if( cfgutil.cfg_search( CfgParam, ParamStr, 2 ) < 0 )
    {
    	trace("\nError in Searching BIN from File[%s]\n", "EzBancsInf.cfg" );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName);
		closeDebug();
		cfgutil.cfg_close();
		TaskExit();
	}
    else
        strcpy( ezbancsmsg.Bin, ParamStr );

	cfgutil.cfg_close();

	if( initNetworkUtil( this ) < 0 )
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

int EzPrepaid8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ],ComTempDate[ 7 ],TempAmount[13],TempDate[ 7 ],TempBuf[ 16 ],CheckDate[ 5 ], temp[10], temptxn[7];;
	unsigned char BitMap[ 33 ];
	int Amount;
	int len = 0,date = 0, ExtRespCode, ExtNetCode, ExtMsgType;
	BufOffset = OutBuf;
	char *month, *day;

	trace( "MsgType = [%d]", txnmsg->MsgType );

	if(  ( txnmsg->MsgType == 430 ) &&  ( strlen( txnmsg->DispAmount ) )  && ( txnmsg->RespCode == 0 ))
		txnmsg->RespCode = 102 ;

	trace( "IsoHeader[%s]", ezbancsmsg.IsoHeader );
	strncpy( OutBuf, ezbancsmsg.IsoHeader,strlen( ezbancsmsg.IsoHeader ) );
	OutBuf+=strlen( ezbancsmsg.IsoHeader );

	ExtMsgType = getOutBoundExtMsgType( txnmsg->MsgType );
	trace( "Switch MsgType [%d] --> Ext MsgType [%d]", txnmsg->MsgType, ExtMsgType );
	OutBuf += fmt_out( OutBuf, &ExtMsgType, ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, ExtMsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", ExtMsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

	if(  ( txnmsg->MsgType == 430 ) &&  ( strlen( txnmsg->DispAmount ) )  && ( txnmsg->RespCode == 102 ))
		txnmsg->RespCode = 0 ;

	OutBuf += fmt_out( OutBuf, BitMap, HTOA, 16, 1 );
	if( IsBitSet( BitMap, 1 ) )
		OutBuf += fmt_out( OutBuf, BitMap + 8, HTOA, 16, 1 );

	if( txnmsg->TxnCode/10000 == 30 )
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
				OutBuf += fmt_out( OutBuf, txnmsg->chn, CHN_MASK, len, bitno );
				break ;

			case 3:
				//OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, temptxn, CHAR, 6, bitno );
				break ;

			case 4:

				memset( TempAmount, 0, sizeof( TempAmount ) );
				if( strlen( txnmsg->Amount ) <= 0 )
					strncpy( TempAmount, "000000000000", 12 );
				else
				{
					if( ( txnmsg->TxnCode/10000 ) == 1 )
						Amount = atoi( txnmsg->Amount ) * 100;
					else
						Amount = atoi( txnmsg->Amount );
					sprintf( TempAmount, "%012d", Amount );
				}

				OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
				break ;

			case 7:

				char TempTime[ 7 ];
				memset( ComTempDate, 0, sizeof( ComTempDate ) );
				if( txnmsg->MsgType == 200 || ( txnmsg->MsgType == 420 && txnmsg->RespCode == 8 ) )
				{
					date = getSysDate( );
					month=getSysMon( );
					trace("month[%s]", month );
					strcpy( ComTempDate, month );
					day = getSysDay( );
					trace("day[%s]", day );
					strcat( ComTempDate, day );
					trace("ComTempDate[%s]", ComTempDate );
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else if( txnmsg->MsgType == 800 )
				{
					trace("Composig 800...");
					date = getSysDate( );
					month=getSysMon( );
					trace("month[%s]", month );
					strcpy( ComTempDate, month );
					day = getSysDay( );
					trace("day[%s]", day );
					strcat( ComTempDate, day );
					trace("ComTempDate[%s]", ComTempDate );
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
					txnmsg->TranTime = 0;
					txnmsg->TranTime = getSysTime( );

				}
				else
				{
					memset( CheckDate, 0, sizeof( CheckDate ) );
					memset( TempDate, 0, sizeof( TempDate ) );
					sprintf( TempDate, "%06d", txnmsg->TranDate );
					trace("SwitchDate[%s]", TempDate );
					strncpy( CheckDate, &TempDate[2], 2 );
					strncat( CheckDate, TempDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				}
				memset( TempTime, 0, sizeof( TempTime ) );
				sprintf( TempTime, "%06d", txnmsg->TranTime );
				OutBuf += fmt_out( OutBuf, TempTime, CHAR, 6, bitno );
				break ;

			case 11:
				if( txnmsg->MsgType == 800 )
				{
					if( TraceNo == 25000 )
						TraceNo=1;
					else
						TraceNo+=1;

					OutBuf += fmt_out( OutBuf, &TraceNo, LTOA, 6, bitno );
				}
				else
					OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
				break ;

			case 12:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, LTOA, 6, bitno );
				break;

			case 13:
				if( txnmsg->MsgType == 200 ||  ( txnmsg->MsgType == 420 && txnmsg->RespCode == 8 ) )
				{
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else
				{
					char TempLocalDate[ 7 ];
					memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempLocalDate, "%06d", txnmsg->LocalDate );
					strncpy( CheckDate, &TempLocalDate[2], 2 );
					strncat( CheckDate, TempLocalDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				}
				break ;

			case 15:
				if( txnmsg->MsgType == 200 ||  ( txnmsg->MsgType == 420 && txnmsg->RespCode == 8 ))
				{
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else
				{
					char TempSettlementDate[ 7 ];
					memset( TempSettlementDate, 0, sizeof( TempSettlementDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempSettlementDate, "%06d", txnmsg->CaptureDate );
					strncpy( CheckDate, &TempSettlementDate[2], 2 );
					strncat( CheckDate, TempSettlementDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				}
				break ;
			case 17:
				if( txnmsg->MsgType == 200 ||  ( txnmsg->MsgType == 420 && txnmsg->RespCode == 8 ))
				{
					OutBuf += fmt_out( OutBuf, ComTempDate, CHAR, 4, bitno );
				}
				else
				{
					char TempCaptureDate[ 7 ];
					memset( TempCaptureDate, 0, sizeof( TempCaptureDate ) );
					memset( CheckDate, 0, sizeof( CheckDate ) );
					sprintf( TempCaptureDate, "%06d", txnmsg->CaptureDate );
					strncpy( CheckDate, &TempCaptureDate[2], 2 );
					strncat( CheckDate, TempCaptureDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
				}
				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 32:
				/*char TempAcqNetId[ 7 ];
				if( txnmsg->MsgType == 800 )
				{
					len = strlen( txnmsg->NetworkId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->NetworkId, CHAR, len, bitno );
				}
				else if( txnmsg->MsgType == 200 || ( txnmsg->MsgType == 420 && txnmsg->RespCode == 8 ) )
				{
					memset( TempAcqNetId, 0, sizeof( TempAcqNetId ) );
					strcpy( TempAcqNetId, ezbancsmsg.Bin );
					len = strlen( TempAcqNetId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, TempAcqNetId, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->TxfNetworkId );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->TxfNetworkId, CHAR, len, bitno );
				}*/
				len = strlen( txnmsg->AcquirerBin );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcquirerBin, CHAR, len, bitno );
				break ;

			case 35:
				/*if( ExtMsgType == 200 || ( ExtMsgType == 420 && txnmsg->RespCode == 34 ) )
				{
					//trace("test");
					char TempTrack[ 25 ];
					memset( TempTrack, 0, sizeof( TempTrack ) );
					strncpy( TempTrack, &txnmsg->Track2[1], strlen( txnmsg->Track2 ) - 3 );
					len = strlen( TempTrack );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, TempTrack, CHAR, len, bitno );
				}
				else
				{
					len = strlen( txnmsg->Track2 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->Track2, CHAR, len, bitno );
				}*/
				len = strlen( txnmsg->Track2 );
				trace( "end-sentinentel---->[%c]", txnmsg->Track2[ strlen( txnmsg->Track2 ) - 1 ] );
				if( !isdigit( txnmsg->Track2[ strlen( txnmsg->Track2 ) - 1 ] ) )
					len = len - 1;
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->Track2, CHAR, len, bitno );
				break ;

			case 37:
				OutBuf += fmt_out( OutBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 38:
				OutBuf += fmt_out( OutBuf, txnmsg->AuthNum, CHAR, 6, bitno );
				break ;

			case 39:
				int ExtRespCode;
				/*if( txnmsg->RespCode == 102 )
					RespCode = 32;
				else if( txnmsg->RespCode == 103 )
					RespCode = 21;
				else if( txnmsg->RespCode == 106 || txnmsg->RespCode == 112 )
					RespCode = 22;
				else if( txnmsg->RespCode == 8 )
					RespCode = 91;
				else
					RespCode = txnmsg->RespCode;*/
				ExtRespCode = getOutBoundExtRespCode( txnmsg->RespCode );
				trace("SwitchRespCode[%d] --> ExtRespCode[%d] ", txnmsg->RespCode, ExtRespCode );
				OutBuf += fmt_out( OutBuf, &ExtRespCode, ITOA, 2, bitno );
				break;

			case 41:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;
			case 42:
				OutBuf += fmt_out( OutBuf, ezbancsmsg.AcceptIDCode, CHAR, 15, bitno );
				break ;

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 44:
				char tempstr[ 26 ],TempBal[ 13 ];
				char TotalBal[ 13 ];
				int CheckAmount;
				memset( tempstr, 0, sizeof( tempstr ));
				memset( TempBal, 0, sizeof( TempBal ));
				strcpy( tempstr, "4" );
				if( txnmsg->RespCode != 0 )
				{
					strcat( tempstr, "000000000000000000000000");
					len = strlen( tempstr );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, tempstr, CHAR, len, bitno );
				}
				else
				{
					char *ptr;
					int check=0;
					ptr = txnmsg->AvailBalance;
					memset( TotalBal, 0, sizeof( TotalBal ));
					for( int i=0; i<strlen( ptr ); i++ )
					{
						if( ptr[i] == '.' )
						{
							check =1;
							break;
						}
						else
							TotalBal[i] = ptr[i];
					}
					if( check == 1 )
					{
						trace("coming with dot");
						//strcpy( TempBal,"0" );
						CheckAmount = atoi( TotalBal );
						memset( TotalBal, 0, sizeof( TotalBal ));
						sprintf( TotalBal, "%010d", CheckAmount );
						strcat( TempBal,TotalBal );
						strcat( TempBal,"00" );
					}
					else
					{
						trace("coming without dot");
						CheckAmount = atoi( TotalBal );
						memset( TotalBal, 0, sizeof( TotalBal ));
						sprintf( TotalBal, "%010d", CheckAmount );
						memset( TempBal, 0, sizeof( TempBal ));
//						strncpy ( TempBal, &TotalBal[2], 10 );
						strcat( TempBal,TotalBal );
						strcat( TempBal,"00" );
					}
					strncat( tempstr, TempBal,strlen( TempBal ) );

					strcat( tempstr, TempBal );
					len = strlen( tempstr );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, tempstr, CHAR, len, bitno );

				}
				break ;
			case 49:
				OutBuf += fmt_out( OutBuf, ezbancsmsg.CurrCode, CHAR, 3, bitno );
				break;

			case 52:
				OutBuf += fmt_out( OutBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break;

			case 60:
				if( ExtMsgType == 200 || ExtMsgType == 420 )
				{
					memset( TempBuf, 0, sizeof( TempBuf ) );
					trace( DEBUG_ERROR,"InstId[%s]", ezbancsmsg.InstId );
					strcpy( TempBuf, ezbancsmsg.InstId );
					strcat( TempBuf, ezbancsmsg.InstId );
					strcat( TempBuf, "+000" );
					len = strlen(  TempBuf );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
					OutBuf += fmt_out( OutBuf, TempBuf, CHAR, len, bitno );
				}
				else
				{
					len = strlen(  txnmsg->RsvFld4 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, CHAR, len, bitno );
				}
				break ;

			case 61:

				if( ExtMsgType == 200 || ExtMsgType == 420 )
				{
					int FromAcctType =0 ;
					memset( TempBuf, 0, sizeof( TempBuf ) );
					strncpy( TempBuf, txnmsg->chn, 4 );
					strcat( TempBuf, "PROD" );
					FromAcctType = ( ( txnmsg->TxnCode / 100 ) % 100 );
					if( FromAcctType == 10 )
						strcat( TempBuf, "02" );
					else if( FromAcctType == 20 )
						strcat( TempBuf, "01" );
					strcat( TempBuf, "00Z" );
					len = strlen( TempBuf );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
					OutBuf += fmt_out( OutBuf, TempBuf, CHAR, len, bitno );
				}
				else
				{
					len = strlen(  txnmsg->RsvFld5 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld5, CHAR, len, bitno );
				}
				break;

			case 65:
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

			case 70:
				ExtNetCode = getOutBoundExtNetCode( txnmsg->NetCode );
				trace( "Switch NetCode [%d] --> ExtNetCode[%03d]", txnmsg->NetCode, ExtNetCode );
				OutBuf += fmt_out( OutBuf, &ExtNetCode, ITOA, 3, bitno );
				break ;

			case 90:
				if( ExtMsgType == 420 )
				{
					char CheckDate[ 5 ];
					memset( CheckDate, 0, sizeof( CheckDate ) );
					memset( TempDate, 0, sizeof( TempDate ) );
					trace( "Original Data Elements" );
					OutBuf += fmt_out( OutBuf, &txnmsg->OrgMsgType, ITOA, 4, bitno );
					OutBuf += fmt_out( OutBuf, &txnmsg->OrgTraceNo, LTOA, 6, bitno );
					sprintf( TempDate, "%06d", txnmsg->OrgTranDate );
					trace("SwitchDate[%s]", TempDate );
					strncpy( CheckDate, &TempDate[2], 2 );
					strncat( CheckDate, TempDate, 2 );
					OutBuf += fmt_out( OutBuf, CheckDate, CHAR, 4, bitno );
//					OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranDate, LTOA, 6, bitno );
					OutBuf += fmt_out( OutBuf, &txnmsg->OrgTranTime, LTOA, 6, bitno );
					OutBuf += fmt_out( OutBuf, ( char * ) "00000000000",  CHAR, 11, bitno );
					OutBuf += fmt_out( OutBuf, ( char * ) "00000000000",  CHAR, 11, bitno );
				}
				else
				{
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, 42, bitno );
				}
				break ;

			case 95:
				if( txnmsg->MsgType == 420 )
				{
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
					OutBuf += fmt_out( OutBuf, ( char * ) "0000000000",  CHAR, 10, bitno );
					OutBuf += fmt_out( OutBuf, ( char * ) "00000000",  CHAR, 8, bitno );
				}
				else
				{
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, CHAR, 42, bitno );
				}
				break ;

			case 100:
				if( ExtMsgType == 200 || ExtMsgType == 420 )
				{
					strncpy( txnmsg->RsvFld6, txnmsg->chn, 9 );
					len = strlen(  txnmsg->RsvFld6 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld6, CHAR, len, bitno );
				}
				else
				{
					len = strlen(  txnmsg->RsvFld6 );
					OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
					OutBuf += fmt_out( OutBuf, txnmsg->RsvFld6, CHAR, len, bitno );
				}
				break;

			case 102:
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


int EzPrepaid8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len, ExtNetCode;
	char StmtBuf[ STMT_BUF_SIZE +1 ], CheckDate[ 7 ],  temp[10], temptxn[7];;
	char TempTranDate[ 7 ], *CurrentYear;
	int date;

	memset( ezbancsmsg.IsoHeader, 0, sizeof( ezbancsmsg.IsoHeader ));
	strncpy( ezbancsmsg.IsoHeader, InBuf, 12 );
	trace( "IsoHeader[%s]", ezbancsmsg.IsoHeader );
	InBuf += 12;
	InBuf += fmt_in( InBuf, &txnmsg->MsgType, ATOI, 4 , 0 );

	if( txnmsg->MsgType == 420 )
	{
		memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
		memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
		strcpy( txnmsg->OrgChannel, "EzBANCS8583");
		strcpy( txnmsg->OrgPort, "BANCS");
	}
	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmt_in( InBuf, BitMap, ATOH, 16, 1 );

	if( IsBitSet( BitMap, 1 ) )
		InBuf += fmt_in( InBuf, BitMap + 8, ATOH, 16, 1 );
	strcpy( txnmsg->SecurityId, "123456");
	if( txnmsg->MsgType == 800 )
		strcpy( txnmsg->AcqNetworkId, "BANCS");

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
				InBuf += fmt_in( InBuf, txnmsg->chn, CHN_MASK, len, bitno );
				break ;

			case 3:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOL, 6, bitno );
				if( txnmsg->TxnCode/10000 == 31 )
				{
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%06d", txnmsg->TxnCode );
					memset( temptxn, 0, sizeof( temptxn ) );
					strcpy( temptxn, "30" );
					strcat( temptxn, temp + 2 );
					trace( "temptxn[%s]",temptxn);
					txnmsg->TxnCode = atoi( temptxn );
				}
				break ;

			case 4:
				char TempAmount[13];
				int Amount ;
				memset( TempAmount, 0, sizeof( TempAmount ) );
				InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, bitno );
				if( ( txnmsg->TxnCode/10000 ) == 1 )
				{
					Amount = atoi( TempAmount ) / 100;
					sprintf( txnmsg->Amount, "%d%s", Amount,".00" );
				}
				else
				{
					Amount = atoi( TempAmount );
					sprintf( txnmsg->Amount, "%d", Amount );
				}
				break ;

			case 7:
				memset( TempTranDate, 0, sizeof( TempTranDate ) );
				memset( CheckDate, 0, sizeof( CheckDate ) );
				InBuf += fmt_in( InBuf, TempTranDate, CHAR, 4, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, bitno );
				strncpy( CheckDate, &TempTranDate[2], 2 );
				strncat( CheckDate, TempTranDate, 2 );
				date = getSysDate( );
				trace( "Date[%d]", date );
				CurrentYear = getSysYear( );
				trace( "CurrentYear[%s]", CurrentYear );
				strcat( CheckDate, CurrentYear );
				txnmsg->TranDate = atoi( CheckDate );
				trace( "txnmsg->TranDate[%d]", txnmsg->TranDate );
				break ;

			case 11:
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOL, 6, bitno );
				break ;

			case 12:
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, bitno );
				break ;

			case 13:
				char TempLocalDate[ 7 ];
				memset( TempLocalDate, 0, sizeof( TempLocalDate ) );
				memset( CheckDate, 0, sizeof( CheckDate ) );
				InBuf += fmt_in( InBuf, TempLocalDate, CHAR, 4, bitno );
				strncpy( CheckDate, &TempLocalDate[2], 2 );
				strncat( CheckDate, TempLocalDate, 2 );
				strcat( CheckDate, CurrentYear );
				txnmsg->LocalDate = atoi( CheckDate );
				break ;
			case 15:
				char TempSettlementDate[ 7 ];
				memset( CheckDate, 0, sizeof( CheckDate ) );
				memset( TempSettlementDate, 0, sizeof( TempSettlementDate ) );
				InBuf += fmt_in( InBuf, TempSettlementDate, CHAR, 4, bitno );
				strncpy( CheckDate, &TempSettlementDate[2], 2 );
				strncat( CheckDate, TempSettlementDate, 2 );
				strcat( CheckDate, CurrentYear );
				txnmsg->SettlementDate = atoi( CheckDate );
				break ;
			case 17:
				char TempCaptureDate[ 7 ];
				memset( CheckDate, 0, sizeof( CheckDate ) );
				memset( TempCaptureDate, 0, sizeof( TempCaptureDate ) );
				InBuf += fmt_in( InBuf, TempCaptureDate, CHAR, 4, bitno );
				strncpy( CheckDate, &TempCaptureDate[2], 2 );
				strncat( CheckDate, TempCaptureDate, 2 );
				strcat( CheckDate, CurrentYear );
				txnmsg->CaptureDate = atoi( CheckDate );
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;

			case 32:
				/*if( txnmsg->MsgType == 810 )
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->NetworkId, CHAR, len, bitno );
				}
				else if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 )
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->TxfNetworkId, CHAR, len, bitno );
					strcpy( txnmsg->AcquirerInst, "BANCS" );
				}
				else
				{
					InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
					InBuf += fmt_in( InBuf, txnmsg->TxfNetworkId, CHAR, len, bitno );
				}*/
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcquirerBin, CHAR, len, bitno );
				if( txnmsg->MsgType == 200 || txnmsg->MsgType == 420 || txnmsg->MsgType == 421 )
					strcpy( txnmsg->AcquirerInst, "BANCS" );
				break ;

			case 35:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->Track2, CHAR, len, bitno );
				char *p;
				p= txnmsg->Track2;
				for( int i = 0; i < strlen( p  ); i++ )
			        {
			                if( p[ i ] == '=' )
                        			break;
			                else
	                        		txnmsg->chn[ i ] = p[ i ];
        			}
				trace( "CHN[%s]", txnmsg->chn );
				break ;
			case 37:
				InBuf += fmt_in( InBuf, &txnmsg->RefNum, CHAR, 12, bitno );
				break ;
			case 38:
				InBuf += fmt_in( InBuf, &txnmsg->AuthNum, CHAR, 6, bitno );
				break ;
			case 39:
				int ExtRespCode;
				/*if( txnmsg->MsgType == 420 )
				{
					int RespCode;
					InBuf += fmt_in( InBuf, &RespCode, ATOI, 2, bitno );
					if( RespCode == 32 )
						txnmsg->RespCode = 102;
					else if( RespCode == 21 )
						txnmsg->RespCode = 103;
					else if( RespCode == 22 )
						txnmsg->RespCode = 112;
					else if( RespCode == 91 )
						txnmsg->RespCode = 8;
				}
				else*/

				InBuf += fmt_in( InBuf, &ExtRespCode, ATOI, 2, bitno );
				txnmsg->RespCode = getInBoundSwitchRespCode( ExtRespCode );
				trace("SwitchRespCode[%d] --> ExtRespCode[%d] ", txnmsg->RespCode, ExtRespCode );
				break ;

			case 41:
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 8, bitno );
				break ;

			case 42:
				char AcceptIDCode[ 16 ];
				memset( AcceptIDCode, 0, sizeof( AcceptIDCode ) );
				InBuf += fmt_in( InBuf, AcceptIDCode, CHAR, 15, bitno );
				break;

			case 43:
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 44:
				char tempStr[ 20 ], Balance[20];
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += 1;
				memset( Balance, 0, sizeof( Balance ) );
				InBuf += fmt_in( InBuf, Balance, CHAR, 10, bitno );
				memset( tempStr, 0, sizeof( tempStr ) );
				removeLeadingZeros( Balance, tempStr );
				trace("tempStr[%s]", tempStr);
				if( atoi( tempStr ) > 0 )
				{
					//strncpy( txnmsg->AvailBalance, tempStr, strlen( tempStr ) - 2 );
					strncpy( txnmsg->AvailBalance, tempStr, strlen( tempStr ) );
					strcat( txnmsg->AvailBalance,".00" );
					//strncat( txnmsg->AvailBalance, tempStr + strlen( tempStr ) - 2, 2 );
					trace("Balance[%s]",txnmsg->AvailBalance);
				}
				else
					strcpy( txnmsg->AvailBalance,"0.00" );

				InBuf += 2;
				memset( Balance, 0, sizeof( Balance ) );
				InBuf += fmt_in( InBuf, Balance, CHAR, 10, bitno );
				memset( tempStr, 0, sizeof( tempStr ) );
				removeLeadingZeros( Balance, tempStr );
				trace("tempStr[%s]", tempStr);
				if( atoi( tempStr ) > 0 )
				{
					//strncpy( txnmsg->LedgerBalance, tempStr, strlen( tempStr ) - 2 );
					strncpy( txnmsg->LedgerBalance, tempStr, strlen( tempStr ) );
					strcat( txnmsg->LedgerBalance,".00" );
					//strncat( txnmsg->LedgerBalance, tempStr + strlen( tempStr ) - 2, 2 );
					trace("Balance1[%s]", txnmsg->LedgerBalance);
				}
				else
					strcpy( txnmsg->LedgerBalance,"0.00" );

				InBuf += 2;
				break ;

			case 49:
				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOI, 3, bitno );
				break ;
			case 52:
				InBuf += fmt_in( InBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break ;

			case 60:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, len, bitno );
				break ;

			case 61:
				InBuf += fmt_in( InBuf, &len, ATOI, 3, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld5, CHAR, len, bitno );
				break ;

			case 70://NetCode
				strcpy( txnmsg->NetworkId, "BANCS" );
				InBuf += fmt_in( InBuf, &ExtNetCode, ATOI, 3, bitno );
				txnmsg->NetCode = getInBoundSwitchNetCode( ExtNetCode );
				trace( "ExtNetCode[%03d] --> Switch NetCode [%03d]", ExtNetCode, txnmsg->NetCode );
				break ;

			case 90:
				//InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, 42, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->OrgMsgType, ATOI, 4 , bitno );
				InBuf += fmt_in( InBuf, &txnmsg->OrgTraceNo, ATOL, 6 , bitno );

				memset( TempTranDate, 0, sizeof( TempTranDate ) );
				memset( CheckDate, 0, sizeof( CheckDate ) );
				InBuf += fmt_in( InBuf, TempTranDate, CHAR, 4, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->OrgTranTime, ATOL, 6, bitno );
				strncpy( CheckDate, &TempTranDate[2], 2 );
				strncat( CheckDate, TempTranDate, 2 );
				date = getSysDate( );
				trace( "Date[%d]", date );
				CurrentYear = getSysYear( );
				trace( "CurrentYear[%s]", CurrentYear );
				strcat( CheckDate, CurrentYear );
				txnmsg->OrgTranDate = atoi( CheckDate );
				trace( "txnmsg->OrgTranDate[%d]", txnmsg->OrgTranDate );

				memset( temp, 0,sizeof( temp ) );
				InBuf += fmt_in( InBuf, temp, CHAR, 22, bitno );
				sprintf(txnmsg->RsvFld2, "%04d%06d%s%06d%s",txnmsg->OrgMsgType,txnmsg->OrgTraceNo,TempTranDate,txnmsg->OrgTranTime,temp);
				trace("txnmsg->RsvFld2[%s]", txnmsg->RsvFld2 );
				break ;

			case 95:
				char ParDispAmount[ 13 ];
				Amount = 0;
				memset( ParDispAmount, 0, sizeof( ParDispAmount ) );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, 42, bitno );
				strncpy( ParDispAmount, txnmsg->RsvFld3, 12 );
				if( ( txnmsg->TxnCode/10000 ) == 1 )
				{
					Amount = atoi( ParDispAmount ) / 100;
					sprintf( txnmsg->DispAmount, "%d%s", Amount,".00" );
				}
				break ;

			case 100:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld6, CHAR, len, bitno );
				break;

			case 102:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, bitno );
				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", bitno );
				break ;

		}

	}
	return 1;
}

void EzPrepaid8583 :: removeLeadingZeros( const char *SrcStr, char *DestStr )
{
	int i = 0;
	trace( "SrcStr[%s]", SrcStr );
	//DestStr[ 0 ] = SrcStr[ 0 ];

	for( i = 1; i < strlen( SrcStr ); i++ )
	{
		if( SrcStr[ i ] != '0' )
			break;
	}
	trace( "offset = [%d]  SrcStr[%s]", i, SrcStr + i );
	strcpy( DestStr, SrcStr + i );
}

void EzPrepaid8583 :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 2600 + 1 ];
	char MsgBuffer[ 2600 + 1 ];
	struct EzEchoTable echotable_rec;

	while( 1 )
	{
		trace( "EzBancs8583 Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
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
				else
				{
					if( WriteChannel( "EzTxnMgr", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
						trace( "Error in Writing Message to Channel EzTxnMgr" );
					else
						trace( "Message Sucessfully Written to Channel EzTxnMgr" );
				}
			}
			else if( txnmsg.MsgType == 800 )
			{
				txnmsg.MsgType = 810;
				strcpy( txnmsg.DestPort, GetLastSenderChannelName() );
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


int main( int argc, char **argv )
{
	EzPrepaid8583 ezprepaid8583obj;
	ezprepaid8583obj.InitEzPrepaid8583( argv[ 0 ] );
	ezprepaid8583obj.ServiceRequest();
	return 1;
}

