#include <eztms/eztmsdriver.h>

void EzTMSDriverTemplate :: initTMSDriverTemplate( EzDebugUtil *dptr, EzAmountUtil *amtutil_ptr )
{
	this->dptr = dptr;
	this->amtutil_ptr = amtutil_ptr;
}

bool EzTMSDriverTemplate :: BlankLine( const char *LineBuffer )
{
	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
			return false;
	}
	return true;
}

void EzTMSDriverTemplate :: getToken( const char *FieldStr, char *TokenStr, char Token, int TokenNo )
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

int EzTMSDriverTemplate :: GetNColumns( const char *LineBuffer )
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

int EzTMSDriverTemplate :: GetString( const char *LineBuffer, char *ColStr, int Column )
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

int EzTMSDriverTemplate :: getNStmts( struct EzTxnMsg *txnmsg )
{
	return ( tkutil.getNToken( txnmsg->RsvFld1, 0x1c ) - 1 );
}

void EzTMSDriverTemplate :: getStmtData( struct EzTxnMsg *txnmsg, int StmtNo, const char *DataId, char *StmtData )
{
	char StmtTempStr[ 255 ], TokenStr[ 150 ];

	tkutil.getToken( txnmsg->RsvFld1, StmtTempStr, 0x1c, StmtNo + 1 );
	if( !strcmp( DataId, "STMT_DATE" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 1 );
		strcpy( StmtData, TokenStr );
	}
	else if( !strcmp( DataId, "STMT_DATE_DD" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 1 );
		strncpy( StmtData, TokenStr, 2 );
	}
	else if( !strcmp( DataId, "STMT_DATE_MM" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 1 );
		strncpy( StmtData, TokenStr + 2, 2 );
	}
	else if( !strcmp( DataId, "STMT_DATE_YY" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 1 );
		strncpy( StmtData, TokenStr + 4, 2 );
	}
	else if( !strcmp( DataId, "STMT_TIME" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 2 );
		strcpy( StmtData, TokenStr );
	}
	else if( !strcmp( DataId, "STMT_DATE_HH" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 2 );
		strncpy( StmtData, TokenStr, 2 );
	}
	else if( !strcmp( DataId, "STMT_DATE_MIS" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 2 );
		strncpy( StmtData, TokenStr + 2, 2 );
	}
	else if( !strcmp( DataId, "STMT_DATE_SEC" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 2 );
		strncpy( StmtData, TokenStr + 4, 2 );
	}
	else if( !strcmp( DataId, "STMT_DESC" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 3 );
		strcpy( StmtData, TokenStr );
	}
	else if( !strcmp( DataId, "STMT_TXNTYPE" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 4 );
		strcpy( StmtData, TokenStr );
	}
	else if( !strcmp( DataId, "STMT_AMT" ) )
	{
		memset( TokenStr, 0, sizeof( TokenStr ) );
		tkutil.getToken( StmtTempStr, TokenStr, 0x1d, 5 );
		strcpy( StmtData, TokenStr );
	}
}

void EzTMSDriverTemplate :: composeStmtData( struct EzTxnMsg *txnmsg )
{
	char TempStmtData[ 513 ], StmtTempStr[ 150 ], TempStr[ 50 ];
	int NStmts = 0;

	if( !strncmp( txnmsg->chn, "6376762", 7 ) )
	{
		memset( TempStmtData, 0, sizeof( TempStmtData ) );
		for( int i = 0; i < getNStmts( txnmsg ); i++ )
		{
			memset( StmtTempStr, 0, sizeof( StmtTempStr ) );
			getStmtData( txnmsg, i, "STMT_DATE_DD", StmtTempStr );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", StmtTempStr );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", "/" );
			memset( StmtTempStr, 0, sizeof( StmtTempStr ) );
			getStmtData( txnmsg, i, "STMT_DATE_MM", StmtTempStr );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", StmtTempStr );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", " " );
			memset( StmtTempStr, 0, sizeof( StmtTempStr ) );
			getStmtData( txnmsg, i, "STMT_DESC", StmtTempStr );
			strncpy( TempStmtData + strlen( TempStmtData ), StmtTempStr, 7 );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", " " );
			memset( StmtTempStr, 0, sizeof( StmtTempStr ) );
			getStmtData( txnmsg, i, "STMT_AMT", StmtTempStr );
			memset( TempStr, 0, sizeof( TempStr ) );
			amtutil_ptr->normalizeAmt( StmtTempStr, TempStr, 2 );
			sprintf( TempStmtData + strlen( TempStmtData ), "%13s", TempStr );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", " " );
			getStmtData( txnmsg, i, "STMT_TXNTYPE", StmtTempStr );
			sprintf( TempStmtData + strlen( TempStmtData ), "%s", StmtTempStr );
		}
		memset( txnmsg->RsvFld1, 0, sizeof( txnmsg->RsvFld1 ) );
		strcpy( txnmsg->RsvFld1, TempStmtData );
	}
}


int EzTMSDriverTemplate :: composeResponseTemplate( struct EzTxnMsg *devmsg, const char *TerminalType, const char *MerchantType, const char *MerchantId, char *PrinterBuffer, bool templateflag )
{
	int NColumns;
	char LineBuffer[ 129 ], ColStr[ 129 ], TempStr[ 129 ], FPath[ 129 ];
	char sbal[ 65 ], Txn[ 129 ], Temp[ 129 ], *P;
	int FromOffset, ToOffset;
	FILE *fptr;

	memset( FPath, 0, sizeof( FPath ) );
	if( !templateflag )
		sprintf( FPath, "%s/%s/%s/%s/%s_%s_%s_%06d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, MerchantId, devmsg->TxnCode );
	else
		sprintf( FPath, "%s/%s/%s/%s/%s_%s_%s_%06d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, MerchantId, devmsg->TxnCode );
	fptr = fopen( FPath, "r" );
	if( fptr == NULL )
	{
		memset( FPath, 0, sizeof( FPath ) );
		if( !templateflag )
			sprintf( FPath, "%s/%s/%s/%s/%s_%s_%s_%02d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, MerchantId, devmsg->TxnCode / 10000 );
		else
			sprintf( FPath, "%s/%s/%s/%s/%s_%s_%s_%02d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, MerchantId, devmsg->TxnCode / 10000 );
		fptr = fopen( FPath, "r" );
		if( fptr == NULL )
		{
			memset( FPath, 0, sizeof( FPath ) );
			if( !templateflag )
				sprintf( FPath, "%s/%s/%s/%s/%s_%s_%06d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, devmsg->TxnCode );
			else
				sprintf( FPath, "%s/%s/%s/%s/%s_%s_%06d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, devmsg->TxnCode );
			fptr = fopen( FPath, "r" );
			if( fptr == NULL )
			{
				memset( FPath, 0, sizeof( FPath ) );
				if( !templateflag )
					sprintf( FPath, "%s/%s/%s/%s/%s_%02d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode / 10000 );
				else
					sprintf( FPath, "%s/%s/%s/%s/%s_%02d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode / 10000 );
				fptr = fopen( FPath, "r" );
				if( fptr == NULL )
				{
					memset( FPath, 0, sizeof( FPath ) );
					if( !templateflag )
						sprintf( FPath, "%s/%s/%s/%s/%s_%06d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode );
					else
						sprintf( FPath, "%s/%s/%s/%s/%s_%06d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode );
					fptr = fopen( FPath, "r" );
					if( fptr == NULL )
					{
						memset( FPath, 0, sizeof( FPath ) );
						if( !templateflag )
							sprintf( FPath, "%s/%s/%s/%s/%s_%02d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode / 10000 );
						else
							sprintf( FPath, "%s/%s/%s/%s/%s_%02d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode / 10000 );
						fptr = fopen( FPath, "r" );
						if( fptr == NULL )
						{
							memset( FPath, 0, sizeof( FPath ) );
							if( !templateflag )
								sprintf( FPath, "%s/%s/%s/%s/%06d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", devmsg->TxnCode );
							else
								sprintf( FPath, "%s/%s/%s/%s/%06d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", devmsg->TxnCode );
							fptr = fopen( FPath, "r" );
							if( fptr == NULL )
							{
								memset( FPath, 0, sizeof( FPath ) );
								if( !templateflag )
									sprintf( FPath, "%s/%s/%s/%s/%02d.prt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", devmsg->TxnCode / 10000 );
								else
									sprintf( FPath, "%s/%s/%s/%s/%02d.sct", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", devmsg->TxnCode / 10000 );
								fptr = fopen( FPath, "r" );
								if( fptr == NULL )
								{
									return -1;
								}
							}
						}
					}
				}
			}
		}
	}

	if( devmsg->TxnCode / 10000 == 38 )
		composeStmtData( devmsg );

	while( !feof( fptr ) )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		fgets( LineBuffer, sizeof( LineBuffer ), fptr );

		if( BlankLine( LineBuffer ) )
			continue;

		NColumns = GetNColumns( LineBuffer );

		for( int i = 0; i < NColumns; i++ )
		{
			memset( ColStr, 0, sizeof( ColStr ) );
			GetString( LineBuffer, ColStr, i + 1 );

			if( !strcasecmp( ColStr, "$LF" ) )
				strcat( PrinterBuffer, "\x0a" );
			else if ( !strcasecmp( ColStr, "$SO" ) )
				strcat( PrinterBuffer, "\x0e" );
			else if ( !strcasecmp( ColStr, "$SPACE" ) )
				strcat( PrinterBuffer, " " );
			else if ( !strncasecmp( ColStr, "$SPACE-", 7 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				for( int i = 0; i < atoi( TempStr ); i++ )
					strcat( PrinterBuffer, " " );
			}
			else if ( !strncasecmp( ColStr, "$RSVFLD5-", 9 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				memset( Temp, 0, sizeof( Temp ) );
				getToken( devmsg->RsvFld5, Temp, 0x1c, atoi( TempStr ) );
				if( strlen( Temp ) )
					strcat( PrinterBuffer, Temp );
			}
			else if ( !strncasecmp( ColStr, "$RSVFLD4-", 9 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				memset( Temp, 0, sizeof( Temp ) );
				getToken( devmsg->RsvFld4, Temp, 0x1c, atoi( TempStr ) );
				if( strlen( Temp ) )
					strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$ESC" ) )
				strcat( PrinterBuffer, "\x1b" );
			else if ( !strcasecmp( ColStr, "$FF" ) )
				strcat( PrinterBuffer, "\x0c" );
			else if ( !strcasecmp( ColStr, "$CR" ) )
				strcat( PrinterBuffer, "\x0d" );
			else if ( !strcasecmp( ColStr, "$VT" ) )
				strcat( PrinterBuffer, "\x0b" );
			else if ( !strcasecmp( ColStr, "$CHN" ) )
				strcat( PrinterBuffer, devmsg->chn );
			else if ( !strcasecmp( ColStr, "$AMOUNT" ) )
				strcat( PrinterBuffer, devmsg->Amount );
			else if ( !strcasecmp( ColStr, "$AVAIL_BALANCE" ) )
				strcat( PrinterBuffer, devmsg->AvailBalance );
			else if ( !strcasecmp( ColStr, "$LEDGER_BALANCE" ) )
				strcat( PrinterBuffer, devmsg->LedgerBalance );
			else if ( !strcasecmp( ColStr, "$TRACE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%04d", devmsg->TraceNo );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$RESP_CODE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%03d", devmsg->RespCode );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TRANSACTION" ) )
			{
				memset( Txn, 0, sizeof(Txn));
				if(devmsg->TxnCode/10000 == 1)
					strcpy(Txn,"WITHDRAWAL");
				if(devmsg->TxnCode/10000 == 30)
					strcpy(Txn,"BALANCE INQUIRY");
				if(devmsg->TxnCode/10000 == 92)
					strcpy(Txn,"STATEMENT REQUEST");
				if(devmsg->TxnCode/10000 == 38)
					strcpy(Txn,"MINISTATEMENT REQUEST");
				if(devmsg->TxnCode/10000 == 91)
					strcpy(Txn,"CHQBK REQUEST");
				if(devmsg->TxnCode/10000 == 40)
					strcpy(Txn,"FUND TRANSFER");
				if(devmsg->TxnCode/10000 == 41)
					strcpy(Txn,"FUND TRANSFER");
				if(devmsg->TxnCode/10000 == 94)
					strcpy(Txn,"PINCHANGE");
				if(devmsg->TxnCode/10000 == 95)
					strcpy(Txn,"PINCHANGE");
				if(devmsg->TxnCode/10000 == 20)
					strcpy(Txn,"DEPOIST");
				strcat( PrinterBuffer, Txn );
			}
			else if ( !strcasecmp( ColStr, "$RSVFLD1" ) )
				strcat( PrinterBuffer, devmsg->RsvFld1 );
			else if ( !strcasecmp( ColStr, "$RSVFLD2" ) )
				strcat( PrinterBuffer, devmsg->RsvFld2 );
			else if ( !strcasecmp( ColStr, "$RSVFLD3" ) )
				strcat( PrinterBuffer, devmsg->RsvFld3 );
			else if ( !strcasecmp( ColStr, "$RSVFLD4" ) )
				strcat( PrinterBuffer, devmsg->RsvFld4 );
			else if ( !strcasecmp( ColStr, "$RSVFLD5" ) )
				strcat( PrinterBuffer, devmsg->RsvFld5 );
			else if ( !strcasecmp( ColStr, "$RSVFLD6" ) )
				strcat( PrinterBuffer, devmsg->RsvFld6 );
			else if ( !strcasecmp( ColStr, "$ACQINST" ) )
				strcat( PrinterBuffer, devmsg->AcquirerInst );
			else if ( !strcasecmp( ColStr, "$DEVICE_ID" ) )
				strcat( PrinterBuffer, devmsg->SrcPort );
			else if ( !strcasecmp( ColStr, "$TERMINAL_ID" ) )
			{
				dptr->trace( DEBUG_TEST, "Inside Compose TermId[%s]", devmsg->TerminalId );
				strcat( PrinterBuffer, devmsg->TerminalId );
			}
			else if ( !strcasecmp( ColStr, "$DEVICE_LOCATION" ) )
			{
				dptr->trace( DEBUG_TEST, "Inside Compose TermLocation[%s]", devmsg->TerminalLocation );
				strcat( PrinterBuffer, devmsg->TerminalLocation );
			}
			else if ( !strcasecmp( ColStr, "$FROM_ACCT" ) )
					strcat( PrinterBuffer, devmsg->FromAccount );
			else if ( !strncasecmp( ColStr, "$FROM_ACCT[", 11 ) )
			{
				FromOffset = ColStr[ 11 ] - 48;
				ToOffset = ColStr[ 13 ] - 48;
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, devmsg->FromAccount + ( FromOffset - 1 ), ( ToOffset - FromOffset ) + 1 );
				strcat( PrinterBuffer, TempStr );
			}
			else if ( !strcasecmp( ColStr, "$TO_ACCT" ) )
					strcat( PrinterBuffer, devmsg->ToAccount );
			else if ( !strncasecmp( ColStr, "$TO_ACCT[", 9 ) )
			{
				FromOffset = ColStr[ 9 ] - 48;
				ToOffset = ColStr[ 11 ] - 48;
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, devmsg->ToAccount + ( FromOffset - 1 ), ( ToOffset - FromOffset ) + 1 );
				strcat( PrinterBuffer, TempStr );
			}
			else if ( !strcasecmp( ColStr, "$STMT_1" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_2" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+ 30, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_3" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+60, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_4" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+90, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_5" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+120, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_6" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+150, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_7" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+180, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_8" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+210, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_9" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+240, 30 );
			else if ( !strcasecmp( ColStr, "$STMT_10" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+270, 30 );
			else if ( !strcasecmp( ColStr, "$DATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->TranDate );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$DATE[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->TranDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$DATE[/]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->TranDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALDATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->LocalDate );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALDATE[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->LocalDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALDATE[/]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->LocalDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$BUSDATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->BusinessDate );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$BUSDATE[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->BusinessDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$BUSDATE[/]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->BusinessDate );
				memset( Temp, 0, sizeof( Temp ) );
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->TranTime );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$PRSVFLD1" ) )
			{
				strcat( PrinterBuffer, (char*)devmsg->private_use.RsvFld1 );
			}
			else if ( !strcasecmp( ColStr, "$PRSVFLD2" ) )
			{
				strcat( PrinterBuffer, (char*)devmsg->private_use.RsvFld2 );
			}
			else if ( !strncasecmp( ColStr, "$PRSVFLD1-", 10 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				memset( Temp, 0, sizeof( Temp ) );
				getToken( (char*)devmsg->private_use.RsvFld1, Temp, 0x1c, atoi( TempStr ) );
				if( strlen( Temp ) )
					strcat( PrinterBuffer, Temp );
			}
			else if ( !strncasecmp( ColStr, "$PRSVFLD2-", 10 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				memset( Temp, 0, sizeof( Temp ) );
				getToken( (char*)devmsg->private_use.RsvFld2, Temp, 0x1c, atoi( TempStr ) );
				if( strlen( Temp ) )
					strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->TranTime );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALTIME" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->LocalTime );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->LocalTime );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else
				strcat( PrinterBuffer, ColStr );
		}
	}
	fclose( fptr );
	return 1;
}

int EzTMSDriverTemplate :: composeBadResponseTemplate( struct EzTxnMsg *devmsg, const char *TerminalType, const char *MerchantType, const char *MerchantId, char *PrinterBuffer )
{
	int NColumns;
	char LineBuffer[ 129 ], ColStr[ 129 ], TempStr[ 129 ], FPath[ 129 ];
	char sbal[ 65 ], Txn[ 129 ], Temp[ 129 ], *P;
	int FromOffset, ToOffset;
	FILE *fptr;

	memset( FPath, 0, sizeof( FPath ) );
	sprintf( FPath, "%s/%s/%s/%s/%s_%s_%s_%06d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, MerchantId, devmsg->TxnCode );
	fptr = fopen( FPath, "r" );
	if( fptr == NULL )
	{
		memset( FPath, 0, sizeof( FPath ) );
		sprintf( FPath, "%s/%s/%s/%s/%s_%s_%s_%02d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, MerchantId, devmsg->TxnCode / 10000 );
		fptr = fopen( FPath, "r" );
		if( fptr == NULL )
		{
			memset( FPath, 0, sizeof( FPath ) );
			sprintf( FPath, "%s/%s/%s/%s/%s_%s_%06d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, MerchantType, devmsg->TxnCode );
			fptr = fopen( FPath, "r" );
			if( fptr == NULL )
			{
				memset( FPath, 0, sizeof( FPath ) );
				sprintf( FPath, "%s/%s/%s/%s/%s_%02d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode / 10000 );
				fptr = fopen( FPath, "r" );
				if( fptr == NULL )
				{
					memset( FPath, 0, sizeof( FPath ) );
					sprintf( FPath, "%s/%s/%s/%s/%s_%06d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode );
					fptr = fopen( FPath, "r" );
					if( fptr == NULL )
					{
						memset( FPath, 0, sizeof( FPath ) );
						sprintf( FPath, "%s/%s/%s/%s/%s_%02d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", TerminalType, devmsg->TxnCode / 10000 );
						fptr = fopen( FPath, "r" );
						if( fptr == NULL )
						{
							memset( FPath, 0, sizeof( FPath ) );
							sprintf( FPath, "%s/%s/%s/%s/%06d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", devmsg->TxnCode );
							fptr = fopen( FPath, "r" );
							if( fptr == NULL )
							{
								memset( FPath, 0, sizeof( FPath ) );
								sprintf( FPath, "%s/%s/%s/%s/%02d.bprt", getenv( "EZDIR_HOME" ), "cfg", "tms", "template", devmsg->TxnCode / 10000 );
								fptr = fopen( FPath, "r" );
								if( fptr == NULL )
								{
									return -1;
								}
							}
						}
					}
				}
			}
		}
	}

	while( !feof( fptr ) )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		fgets( LineBuffer, sizeof( LineBuffer ), fptr );

		if( BlankLine( LineBuffer ) )
			continue;

		NColumns = GetNColumns( LineBuffer );

		for( int i = 0; i < NColumns; i++ )
		{
			memset( ColStr, 0, sizeof( ColStr ) );
			GetString( LineBuffer, ColStr, i + 1 );
			if( !strcasecmp( ColStr, "$LF" ) )
				strcat( PrinterBuffer, "\x0a" );
			else if ( !strcasecmp( ColStr, "$SO" ) )
				strcat( PrinterBuffer, "\x0e" );
			else if ( !strcasecmp( ColStr, "$SPACE" ) )
				strcat( PrinterBuffer, " " );
			else if ( !strncasecmp( ColStr, "$SPACE-", 7 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				for( int i = 0; i < atoi( TempStr ); i++ )
					strcat( PrinterBuffer, " " );
			}
			else if ( !strncasecmp( ColStr, "$RSVFLD5-", 9 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				memset( Temp, 0, sizeof( Temp ) );
				getToken( devmsg->RsvFld5, Temp, 0x1c, atoi( TempStr ) );
				if( strlen( Temp ) )
					strcat( PrinterBuffer, Temp );
			}
			else if ( !strncasecmp( ColStr, "$RSVFLD4-", 9 ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				getToken( ColStr, TempStr, '-', 2 );
				memset( Temp, 0, sizeof( Temp ) );
				getToken( devmsg->RsvFld4, Temp, 0x1c, atoi( TempStr ) );
				if( strlen( Temp ) )
					strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$ESC" ) )
				strcat( PrinterBuffer, "\x1b" );
			else if ( !strcasecmp( ColStr, "$FF" ) )
				strcat( PrinterBuffer, "\x0c" );
			else if ( !strcasecmp( ColStr, "$CR" ) )
				strcat( PrinterBuffer, "\x0d" );
			else if ( !strcasecmp( ColStr, "$VT" ) )
				strcat( PrinterBuffer, "\x0b" );
			else if ( !strcasecmp( ColStr, "$CHN" ) )
				strcat( PrinterBuffer, devmsg->chn );
			else if ( !strcasecmp( ColStr, "$AMOUNT" ) )
				strcat( PrinterBuffer, devmsg->Amount );
			else if ( !strcasecmp( ColStr, "$AVAIL_BALANCE" ) )
				strcat( PrinterBuffer, devmsg->AvailBalance );
			else if ( !strcasecmp( ColStr, "$LEDGER_BALANCE" ) )
				strcat( PrinterBuffer, devmsg->LedgerBalance );
			else if ( !strcasecmp( ColStr, "$TRACE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%04d", devmsg->TraceNo );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$RESP_CODE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%03d", devmsg->RespCode );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TRANSACTION" ) )
			{
				memset( Txn, 0, sizeof(Txn));
				if(devmsg->TxnCode/10000 == 1)
					strcpy(Txn,"WITHDRAWAL");
				if(devmsg->TxnCode/10000 == 30)
					strcpy(Txn,"BALANCE INQUIRY");
				if(devmsg->TxnCode/10000 == 92)
					strcpy(Txn,"STATEMENT REQUEST");
				if(devmsg->TxnCode/10000 == 38)
					strcpy(Txn,"MINISTATEMENT REQUEST");
				if(devmsg->TxnCode/10000 == 91)
					strcpy(Txn,"CHQBK REQUEST");
				if(devmsg->TxnCode/10000 == 40)
					strcpy(Txn,"FUND TRANSFER");
				if(devmsg->TxnCode/10000 == 41)
					strcpy(Txn,"FUND TRANSFER");
				if(devmsg->TxnCode/10000 == 94)
					strcpy(Txn,"PINCHANGE");
				if(devmsg->TxnCode/10000 == 95)
					strcpy(Txn,"PINCHANGE");
				if(devmsg->TxnCode/10000 == 20)
					strcpy(Txn,"DEPOIST");
				strcat( PrinterBuffer, Txn );
			}
			else if ( !strcasecmp( ColStr, "$RSVFLD1" ) )
				strcat( PrinterBuffer, devmsg->RsvFld1 );
			else if ( !strcasecmp( ColStr, "$RSVFLD2" ) )
				strcat( PrinterBuffer, devmsg->RsvFld2 );
			else if ( !strcasecmp( ColStr, "$RSVFLD3" ) )
				strcat( PrinterBuffer, devmsg->RsvFld3 );
			else if ( !strcasecmp( ColStr, "$RSVFLD4" ) )
				strcat( PrinterBuffer, devmsg->RsvFld4 );
			else if ( !strcasecmp( ColStr, "$RSVFLD5" ) )
				strcat( PrinterBuffer, devmsg->RsvFld5 );
			else if ( !strcasecmp( ColStr, "$RSVFLD6" ) )
				strcat( PrinterBuffer, devmsg->RsvFld6 );
			else if ( !strcasecmp( ColStr, "$ACQINST" ) )
				strcat( PrinterBuffer, devmsg->AcquirerInst );
			else if ( !strcasecmp( ColStr, "$DEVICE_ID" ) )
				strcat( PrinterBuffer, devmsg->SrcPort );
			else if ( !strcasecmp( ColStr, "$TERMINAL_ID" ) )
			{
				dptr->trace( DEBUG_TEST, "Inside Compose TermId[%s]", devmsg->TerminalId );
				strcat( PrinterBuffer, devmsg->TerminalId );
			}
			else if ( !strcasecmp( ColStr, "$DEVICE_LOCATION" ) )
			{
				dptr->trace( DEBUG_TEST, "Inside Compose TermLocation[%s]", devmsg->TerminalLocation );
				strcat( PrinterBuffer, devmsg->TerminalLocation );
			}
			else if ( !strcasecmp( ColStr, "$FROM_ACCT" ) )
					strcat( PrinterBuffer, devmsg->FromAccount );
			else if ( !strncasecmp( ColStr, "$FROM_ACCT[", 11 ) )
			{
				FromOffset = ColStr[ 11 ] - 48;
				ToOffset = ColStr[ 13 ] - 48;
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, devmsg->FromAccount + ( FromOffset - 1 ), ( ToOffset - FromOffset ) + 1 );
				strcat( PrinterBuffer, TempStr );
			}
			else if ( !strcasecmp( ColStr, "$TO_ACCT" ) )
					strcat( PrinterBuffer, devmsg->ToAccount );
			else if ( !strncasecmp( ColStr, "$TO_ACCT[", 9 ) )
			{
				FromOffset = ColStr[ 9 ] - 48;
				ToOffset = ColStr[ 11 ] - 48;
				memset( TempStr, 0, sizeof( TempStr ) );
				strncpy( TempStr, devmsg->ToAccount + ( FromOffset - 1 ), ( ToOffset - FromOffset ) + 1 );
				strcat( PrinterBuffer, TempStr );
			}
			else if ( !strcasecmp( ColStr, "$STMT_1" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_2" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+40, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_3" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+80, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_4" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+120, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_5" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+160, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_6" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+200, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_7" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+240, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_8" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+280, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_9" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+320, 40 );
			else if ( !strcasecmp( ColStr, "$STMT_10" ) )
					strncat( PrinterBuffer, devmsg->RsvFld1+360, 40 );
			else if ( !strcasecmp( ColStr, "$DATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->TranDate );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$DATE[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->TranDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$DATE[/]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->TranDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALDATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->LocalDate );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALDATE[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->LocalDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALDATE[/]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->LocalDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$BUSDATE" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->BusinessDate );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$BUSDATE[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->BusinessDate );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$BUSDATE[/]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->BusinessDate );
				memset( Temp, 0, sizeof( Temp ) );
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, "/" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->TranTime );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->TranTime );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$LOCALTIME" ) )
			{
				memset( Temp, 0, sizeof( Temp ));
				sprintf( Temp, "%d", devmsg->LocalTime );
				strcat( PrinterBuffer, Temp );
			}
			else if ( !strcasecmp( ColStr, "$TIME[:]" ) )
			{
				memset( TempStr, 0, sizeof( TempStr ) );
				sprintf( TempStr, "%06d", devmsg->LocalTime );
				memset( Temp, 0, sizeof( Temp ));
				strncpy( Temp, TempStr , 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 3, TempStr + 2, 2 );
				strcat( Temp, ":" );
				strncpy( Temp + 6, TempStr + 4, 2 );
				strcat( PrinterBuffer, Temp );
			}
			else
				strcat( PrinterBuffer, ColStr );
		}
	}
	fclose( fptr );
	return 1;
}

