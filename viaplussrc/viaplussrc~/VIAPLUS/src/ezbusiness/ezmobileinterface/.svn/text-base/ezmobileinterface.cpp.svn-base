#include <ezbusiness/ezmobileinterface.h>

EzMobileInf :: EzMobileInf()
{
}

EzMobileInf :: ~EzMobileInf()
{
}

void EzMobileInf :: initMobileInterface( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmobileinterface.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzMobileInterface Started Running^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzMobileInterface Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzMobileInterface Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( MOBILEINFCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", MOBILEINFCHANNEL );
		trace( "^^^^^^^^^^^EzMobileInterface Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

void EzMobileInf :: ServiceRequest()
{
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ], ReadBuf[ BUFFER_SIZE + 1 ];
	int BufSize;
	struct EzTxnMsg AppReq;

	while( 1 )
	{
		trace( "EzMobileInterface Waiting for Request to be Serviced" );
		memset( ReadBuf, 0, sizeof( ReadBuf ) );
		if( ReadMessage( ReadBuf, &BufSize ) < 0 )
		{
			trace( "Error in Reading Message in [%s] Channel", MOBILEINFCHANNEL );
			continue;
		}

		memset( ChannelName, 0, sizeof( ChannelName ) );
		strcpy( ChannelName, GetLastSenderChannelName() );
		trace( DEBUG_NORMAL, "Message of size [%d] Received from Channel[%s]", BufSize, GetLastSenderChannelName() );

		if( !strcmp( ChannelName, SMSDRIVERCHANNEL ) )
		{
			trace( DEBUG_NORMAL, "Message from SMS Driver" );
			DiagnizeAndServeSMSReq( ReadBuf , BufSize );
		}
		else if( !strcmp( ChannelName, "EzMobileSim" ) )
		{
			trace( DEBUG_NORMAL, "Message from SMS Driver" );
			DiagnizeAndServeSMSReq( ReadBuf , BufSize );
		}
		else if( !strcmp( ChannelName, TRANSACTIONCHANNEL ) )
		{
			trace( DEBUG_NORMAL, "Message from Transaction Mgr" );
			memset( &AppReq, 0, sizeof( struct EzTxnMsg )  );
			memcpy( &AppReq, ReadBuf, BufSize );

			//trace( DEBUG_NORMAL, "MsgType[ %04d ] TxnCode[ %06d ] TraceNo[ %04d ] RespCode[ %03d ] AcctNo[%s]", DevMsg.MsgType, DevMsg.TxnCode, DevMsg.TraceNo, DevMsg.RespCode, DevMsg.FromAccount );

			DiagnizeAndServeAppReq( AppReq );
		}
		else
			trace("Message from the Channel %s will not be Processed", ChannelName );
	}
}

int EzMobileInf :: DiagnizeAndServeAppReq( struct EzTxnMsg TxnMsg )
{
	char SMSReply[ 512 ], SMSBuf[ BUFFER_SIZE + 1 ];
	char TemplateId[ 4 ];

	trace( "TxnCode[ %d ] BranchCode[ %s ] AcctSubType[ %s ] AccountNo[ %s ] RespCode[ %d ]", TxnMsg.TxnCode, TxnMsg.IssBranchCode, TxnMsg.FromAcctSubType, TxnMsg.FromAccount, TxnMsg.RespCode );
	if( TxnMsg.RespCode == 0 )
	{
		memset( TemplateId, 0, sizeof( TemplateId ) );
		sprintf( TemplateId, "%02d", ( ( TxnMsg.TxnCode ) / 10000 ) );

		memset( SMSReply, 0, sizeof( SMSReply ) );
		if( BuildAndPostSMSResp( &TxnMsg, TemplateId, SMSReply ) < 0 )
		{
			trace( "Error in Building SMS Reply");
			return -1;
		}
	}
	else
	{
		memset( TemplateId, 0, sizeof( TemplateId ) );
		sprintf( TemplateId, "%d", TxnMsg.RespCode );

		memset( SMSReply, 0, sizeof( SMSReply ) );
		if( BuildAndPostSMSResp( &TxnMsg, TemplateId, SMSReply ) < 0 )
		{
			trace( "Error in Building SMS Reply");
			return -1;
		}
	}

	memset( SMSBuf, 0, sizeof( SMSBuf ) );
	sprintf( SMSBuf, "%s%c%c%s%c%s", TxnMsg.RsvFld6, 0x1d, 0x1c, SMSReply, 0x1c, "GSM0001" );
	trace( "Composed Message[ %s ]", SMSBuf );
	if( WriteChannel( SMSDRIVERCHANNEL, SMSBuf, strlen( SMSBuf) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", SMSDRIVERCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_NORMAL, "Message written into the %s channel", SMSDRIVERCHANNEL );

	return 1;
}

int EzMobileInf :: BuildAndPostSMSResp( struct EzTxnMsg *TxnMsg, char *TemplateId, char *SMSBuffer )
{
	FILE *fptr;
	int NColumns;
	char FileName[ FILENAME_SIZE + 1 ], LineBuffer[ LINE_BUFFER_SIZE + 1 ], ColStr[ COLUMN_STR_SIZE + 1 ], TempStr[ TEMP_STR_SIZE + 1 ];
	char sbal[ BALANCE + 1 ], Txn[ TMP + 1 ], Temp[ TMP + 1 ], *P,  temp[15], decimal[3];
	int FromOffset, ToOffset, bal;

	memset( FileName, 0, sizeof( FileName ) );

	sprintf( FileName, "%s/cfg/mobile/%s_%s.sms", getenv( "EZDIR_HOME"), TxnMsg->AcquirerInst, TemplateId );

	fptr = fopen( FileName, "r" );
	if( fptr == NULL )
	{
		trace( DEBUG_NORMAL, "Failed to open file [ %s ]", FileName);
		return -1;
	}

	trace( DEBUG_TEST, "FileName [ %s ]", FileName );

	while( !feof( fptr ) )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		fgets( LineBuffer, sizeof( LineBuffer ), fptr );

		//trace( DEBUG_TEST, "LineBuffer=[%s]", LineBuffer );

		if( BlankLine( LineBuffer ) )
			continue;

		NColumns = GetNColumns( LineBuffer );

		//trace( DEBUG_TEST, "NColums=[%d]", NColumns );

		for( int i = 0; i < NColumns; i++ )
		{
			memset( ColStr, 0, sizeof( ColStr ) );
			GetString( LineBuffer, ColStr, i + 1 );
			//trace( DEBUG_TEST, "ColStr[%d]=[%s]", i, ColStr );

			if ( !strcasecmp( ColStr, "$SPACE" ) )
				strcat( SMSBuffer, " " );
			else if ( !strcasecmp( ColStr, "$AMOUNT" ) )
				strcat( SMSBuffer, TxnMsg->Amount );
			else if ( !strcasecmp( ColStr, "$DISPAMOUNT" ) )
				strcat( SMSBuffer, TxnMsg->DispAmount );
			else if ( !strcasecmp( ColStr, "$AVAIL_BALANCE" ) )
			{
				/*strcat( SMSBuffer, TxnMsg->AvailBalance );
				float bal = (float ) atoi( TxnMsg->AvailBalance );
				memset( sbal, 0, sizeof( sbal ));
				sprintf( sbal, "%.2f", bal );
				strcat( SMSBuffer, sbal );*/
                                memset( temp, 0, sizeof( temp ) );
                                memset( decimal, 0, sizeof( decimal ) );
                                trace( "Bal[%s]", TxnMsg->AvailBalance);
                                strncpy( temp, TxnMsg->AvailBalance, strlen( TxnMsg->AvailBalance ) - 2 );
                                strncpy( decimal, TxnMsg->AvailBalance + strlen( TxnMsg->AvailBalance ) - 2, 2 );
				bal = atoi( temp );
                                memset( temp, 0, sizeof( temp ) );
				sprintf( temp, "%d", bal);
                                trace( "Amount[%s] Decimal[%s]", temp, decimal );
				memset( sbal, 0, sizeof( sbal ));
                                sprintf( sbal, "%s.%s", temp, decimal);
                                trace("Balance[%s]", sbal);
				strcat( SMSBuffer, sbal );
			}
			else if ( !strcasecmp( ColStr, "$LEDGER_BALANCE" ) )
			{
				//strcat( SMSBuffer, TxnMsg->AvailBalance );
				float bal = (float ) atoi( TxnMsg->LedgerBalance );
				memset( sbal, 0, sizeof( sbal ));
				sprintf( sbal, "%.2f", bal );
				strcat( SMSBuffer, sbal );
			}
			else if ( !strcasecmp( ColStr, "$TRACE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%04d", TxnMsg->TraceNo );
				strcat( SMSBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$RESP_CODE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%03d", TxnMsg->RespCode );
				strcat( SMSBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$DEVICE_ID" ) )
				strcat( SMSBuffer, TxnMsg->SrcPort );
			else if ( !strcasecmp( ColStr, "$TERMINAL_ID" ) )
				strcat( SMSBuffer, TxnMsg->TerminalId );
			else if ( !strcasecmp( ColStr, "$DEVICE_LOCATION" ) )
			    strcat( SMSBuffer, TxnMsg->TerminalLocation );
			else if ( !strcasecmp( ColStr, "$FROM_ACCT" ) )
			    strcat( SMSBuffer, TxnMsg->FromAccount );
			else if ( !strncasecmp( ColStr, "$FROM_ACCT[", 11 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr + 5, TempStr, ',', 1 );
				FromOffset = atoi( TempStr );
				trace( DEBUG_TEST, "FromOffset[%d]", FromOffset );
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr , TempStr, ',', 2 );
				ToOffset = atoi( TempStr );
				trace( DEBUG_TEST, "ToOffset[%d]", ToOffset );
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, TxnMsg->FromAccount + ( FromOffset - 1 ), ( ToOffset - FromOffset ) + 1 );
				strcat( SMSBuffer, TempStr );
			}
			else if ( !strcasecmp( ColStr, "$TO_ACCT" ) )
			    strcat( SMSBuffer, TxnMsg->ToAccount );
			else if ( !strncasecmp( ColStr, "$TO_ACCT[", 9 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr + 5, TempStr, ',', 1 );
				FromOffset = atoi( TempStr );
				trace( DEBUG_TEST, "FromOffset[%d]", FromOffset );
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr , TempStr, ',', 2 );
				ToOffset = atoi( TempStr );
				trace( DEBUG_TEST, "ToOffset[%d]", ToOffset );
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, TxnMsg->ToAccount + ( FromOffset - 1 ), ( ToOffset - FromOffset ) + 1 );
				strcat( SMSBuffer, TempStr );
			}
			else if ( !strcasecmp( ColStr, "$STMT_1" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld1, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_2" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld1+40, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_3" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld1+80, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_4" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld1+120, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_5" ) )
				strncat( SMSBuffer, TxnMsg->RsvFld1+160, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_6" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld2, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_7" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld2+40, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_8" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld2+80, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_9" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld2+120, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_10" ) )
			    strncat( SMSBuffer, TxnMsg->RsvFld2+160, 40 );
			else if ( !strcasecmp( ColStr, "$DATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%06d", TxnMsg->TranDate );
				strcat( SMSBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%06d", TxnMsg->TranTime );
				strcat( SMSBuffer, Temp );
			}
			else
				strcat( SMSBuffer, ColStr );
		}
	}
	fclose( fptr );
	return 1;
}

int EzMobileInf :: DiagnizeAndServeSMSReq( char *SMSReq , int MsgSize )
{
	char SMS[ 512 ], SMSReply[ 512 ], SMSBuf[ BUFFER_SIZE + 1 ], MobileNo[ 20 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], cfgsearch[ CFG_VAL_SIZE + 1 ];
	int AppCode, Count, TxnCode, AcctType, LineCount;
	char temp[ TEMP + 1 ], KeyWord[ TEMP + 1 ];
	EzCfgUtil cfgutil;
	struct EzTxnMsg ConsumerReq;
	FILE *fptr;
	char FileName[ FILENAME_SIZE + 1 ], LineBuffer[ LINE_BUFFER_SIZE + 1 ];

	memset( &ConsumerReq, 0, sizeof( struct EzTxnMsg ) );

	memset( MobileNo, 0, sizeof( MobileNo ) );
	getToken( SMSReq, MobileNo, DEVICE_FS, 1 );
	strcpy( ConsumerReq.RsvFld6, "+");
	strcat( ConsumerReq.RsvFld6, MobileNo );
	trace( DEBUG_NORMAL, "MobileNo[ %s ]", ConsumerReq.RsvFld6 );

	memset( temp, 0, sizeof( temp ) );
	getToken( SMSReq, temp, DEVICE_FS, 2 );
	AppCode = atoi( temp );
	trace( DEBUG_NORMAL, "AppCode[ %d ]", AppCode );

	memset( SMS, 0, sizeof( SMS ) );
	getToken( SMSReq, SMS, DEVICE_FS, 3 );
	trace( DEBUG_NORMAL, "SMS[ %s ]", SMS );

	memset( temp, 0, sizeof( temp ) );
	getToken( SMSReq, temp, DEVICE_FS, 4 );
	ConsumerReq.TranDate = atoi( temp );
	trace( DEBUG_NORMAL, "TranDate[ %d ]", ConsumerReq.TranDate );

	memset( temp, 0, sizeof( temp ) );
	getToken( SMSReq, temp, DEVICE_FS, 4 );
	ConsumerReq.TranTime = atoi( temp );
	trace( DEBUG_NORMAL, "TranTime[ %d ]", ConsumerReq.TranTime );

	if( !strcasecmp( SMS, "HELP" ) )
	{
		trace( "Composing HELP Message");
		memset( cfgpath, 0, sizeof( cfgpath ) );
		sprintf( cfgpath, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "mobile", "ARCO_mobile.cfg" );

		if( cfgutil.cfg_open( cfgpath ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in opening file[ %s ]", cfgpath );
			return -1;
		}

		memset( cfgval, 0, sizeof( cfgval ) );
	        if( cfgutil.cfg_search( "HELP", cfgval, 2 ) < 0 )
          		trace( "Error in Searching HELP from file[%s]", cfgpath );
		else
		{
			memset( FileName, 0, sizeof( FileName ) );

			sprintf( FileName, "%s/cfg/mobile/%s", getenv( "EZDIR_HOME"), cfgval );
			trace( "FileName [ %s ]", FileName );

			fptr = fopen( FileName, "r" );
			if( fptr == NULL )
			{
				trace( DEBUG_NORMAL, "Failed to open file [ %s ]", FileName);
				return -1;
			}

			memset( SMSReply, 0, sizeof( SMSReply ) );
			while( !feof( fptr ) )
			{
				memset( LineBuffer, 0, sizeof( LineBuffer ) );
				fgets( LineBuffer, sizeof( LineBuffer ), fptr );
				trace( "LineBuffer[ %s ]", LineBuffer );
				strcat( SMSReply, LineBuffer );
				//strcat( SMSReply, "\n" );
			}
			fclose( fptr );
		}
		cfgutil.cfg_close( );

		memset( SMSBuf, 0, sizeof( SMSBuf ) );
		sprintf( SMSBuf, "%s%c%c%s%c%s", ConsumerReq.RsvFld6, 0x1d, 0x1c, SMSReply, 0x1c, "GSM0001" );
		trace( "Composed Message[ %s ]", SMSBuf );
		if( WriteChannel( SMSDRIVERCHANNEL, SMSBuf, strlen( SMSBuf) ) < 0 )
		{
			trace( DEBUG_ERROR, "Unable to write into the channel %s", SMSDRIVERCHANNEL );
			return -1;
		}
		else
			trace( DEBUG_NORMAL, "Message written into the %s channel", SMSDRIVERCHANNEL );
	}
	else
	{
		trace("SMS< %s >", SMS);
		Count = getNTokens( SMS, ' ' );
		trace("Count< %d >", Count );
		if( Count >= 3 )
		{
			memset( cfgpath, 0, sizeof( cfgpath ) );
			sprintf( cfgpath, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "mobile", "ARCO_mobile.cfg" );

			if( cfgutil.cfg_open( cfgpath ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in opening file[ %s ]", cfgpath );
				return -1;
			}

			memset( temp, 0, sizeof( temp ) );
			getToken( SMS, temp, ' ', 1 );

			memset( KeyWord, 0, sizeof( KeyWord ) );
			RemoveBlankSpace( temp, KeyWord );

			memset( cfgsearch, 0, sizeof( cfgsearch ) );
			sprintf( cfgsearch, "%s#%s", "TXNCODE_MAP", KeyWord );
			memset( cfgval, 0, sizeof( cfgval ) );

			if( cfgutil.cfg_search( cfgsearch, cfgval, 2 ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Searching [ %s ] ", cfgsearch );
				cfgutil.cfg_close();
				return -1;
			}
			else
				TxnCode = atoi( cfgval );


			memset( temp, 0, sizeof( temp ) );
			getToken( SMS, temp, ' ', 2 );

			memset( KeyWord, 0, sizeof( KeyWord ) );
			RemoveBlankSpace( temp, KeyWord );

			memset( cfgsearch, 0, sizeof( cfgsearch ) );
			sprintf( cfgsearch, "%s#%s", "BRANCHCODE_MAP", KeyWord );
			memset( cfgval, 0, sizeof( cfgval ) );

			if( cfgutil.cfg_search( cfgsearch, cfgval, 2 ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Searching [ %s ] ", cfgsearch );
				cfgutil.cfg_close();
				return -1;
			}
			else
				strcpy( ConsumerReq.IssBranchCode, cfgval );

			memset( temp, 0, sizeof( temp ) );
			getToken( SMS, temp, ' ', 3 );

			memset( KeyWord, 0, sizeof( KeyWord ) );
			RemoveBlankSpace( temp, KeyWord );

			memset( cfgsearch, 0, sizeof( cfgsearch ) );
			sprintf( cfgsearch, "%s#%s", "ACCOUNTINFO", KeyWord );
			memset( cfgval, 0, sizeof( cfgval ) );

			if( cfgutil.cfg_search( cfgsearch, cfgval, 2 ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Searching [ %s ] ", cfgsearch );
				cfgutil.cfg_close();
				return -1;
			}
			else
				AcctType = atoi( cfgval );

			if( cfgutil.cfg_search( cfgsearch, cfgval, 3 ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Searching [ %s ] ", cfgsearch );
				cfgutil.cfg_close();
				return -1;
			}
			else
				strcpy( ConsumerReq.FromAcctSubType, cfgval );

			cfgutil.cfg_close();

			memset( temp, 0, sizeof( temp ) );
			getToken( SMS, temp, ' ', 4 );

			memset( KeyWord, 0, sizeof( KeyWord ) );
			RemoveBlankSpace( temp, KeyWord );

			strcpy( ConsumerReq.FromAccount, KeyWord );

			memset( temp, 0, sizeof( temp ) );
			sprintf( temp, "%d%02d00", TxnCode, AcctType );

			ConsumerReq.TxnCode = atoi( temp );

			trace( "TxnCode[ %d ] BranchCode[ %s ] AcctSubType[ %s ] AccountNo[ %s ]", ConsumerReq.TxnCode, ConsumerReq.IssBranchCode, ConsumerReq.FromAcctSubType, ConsumerReq.FromAccount );
			ConsumerReq.MsgType = 200;
			strcpy( ConsumerReq.AcquirerInst, "ARCO" );
			strcpy( ConsumerReq.IssuerInst, "ARCO" );
			strcpy( ConsumerReq.TerminalId, "GSM0001" );
			strcpy( ConsumerReq.SrcPort, "GSM0001" );
			strcpy( ConsumerReq.SrcChannel, MOBILEINFCHANNEL );
			ConsumerReq.MerchantType = 6015;

			if( WriteChannel( TRANSACTIONCHANNEL, ( char * )&ConsumerReq, sizeof( struct EzTxnMsg ) ) < 0 )
			{
				trace( DEBUG_ERROR, "Unable to write into the channel %s", TRANSACTIONCHANNEL );
				return -1;
			}
			else
				trace( DEBUG_NORMAL, "Message written into the %s channel", TRANSACTIONCHANNEL );
		}
	}
	return 1;
}

int EzMobileInf :: getNTokens( const char *FieldStr, char Token )
{
	int TokenCount = 0;
	for( int i = 0; i < strlen( FieldStr ); i++ )
	{
		if( FieldStr[ i ] == Token )
			TokenCount++;
	}
	return TokenCount;
}

void EzMobileInf :: getToken( const char *FieldStr, char *TokenStr, char Token, int TokenNo )
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

bool EzMobileInf :: BlankLine( const char *LineBuffer )
{
	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
			return false;
	}
	return true;
}

void  EzMobileInf :: RemoveBlankSpace( const char *InBuf, char *OutBuf )
{
	for( int i = 0, j = 0; i < strlen( InBuf ); i++ )
	{
		if( InBuf[i] != ' ' && InBuf[i] != '\r' && InBuf[i] != '\n' )
		{
			OutBuf[j] = InBuf[i];
			j++;
		}
	}
}

int EzMobileInf :: GetNColumns( const char *LineBuffer )
{
	bool FoundChar = true;
	int NCols = 0;

	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
		{
			if( FoundChar )
				NCols++;
			FoundChar = false;
		}
		else
			FoundChar = true;
	}

	return NCols;
}

int EzMobileInf :: GetString( const char *LineBuffer, char *ColStr, int Column )
{
	int j = 0;
	bool FoundChar = true;

	int FldCount = 0;

	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
		{
			if( FoundChar )
				FldCount++;
			FoundChar = false;
			if( FldCount == Column )
			{
				ColStr[ j ] = LineBuffer[ i ];
				j++;
			}
		}
		else
		{
			FoundChar = true;
			if( FldCount == Column )
				break;
		}
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzMobileInf EzMobileInfObj;
	EzMobileInfObj.initMobileInterface( argv[ 0 ] );
	EzMobileInfObj.ServiceRequest();
	return 1;
}

