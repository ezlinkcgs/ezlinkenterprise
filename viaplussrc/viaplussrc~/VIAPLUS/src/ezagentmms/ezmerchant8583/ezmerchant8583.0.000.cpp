#include <ezmms/ezmerchant8583.h>

void EzMerchant8583 :: InitEzMerchant8583( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];

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
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	if( dbutil.initDBUtil( TaskName, this, "EZMMS" ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with MMS Database...." );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	if( mmsutil.initMMSUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzMMSUtil..." );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	if( mmsdbutil.initMMSDBUtil( this, &dbutil, &dtutil ) < 0 )
	{
		trace( "Error in Initializing EzMMSDBUtil..." );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName);
		closeDebug();
		TaskExit();
	}

	initFmtUtil( this );

	TaskInit();

	initEzSigUtil( this );
}

int EzMerchant8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset, StmtBuf[ STMT_BUF_SIZE +1 ],ComTempDate[ 7 ],TempAmount[13],TempDate[ 7 ],TempBuf[ 16 ],CheckDate[ 5 ], temp[10], temptxn[7], TempStr[ 50 ];
	unsigned char BitMap[ 33 ];
	int Amount;
	int len = 0,date = 0, ExtRespCode, ExtNetCode, ExtMsgType;
	BufOffset = OutBuf;
	char *month, *day;

	OutBuf += fmt_out( OutBuf, &txnmsg->MsgType, ITOA, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
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

				OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, ITOA, 6, bitno );
				break ;

			case 4:

				memset( TempStr, 0, sizeof( TempStr ) );
				formatAmt( txnmsg->Amount, TempStr, 12 );
				OutBuf += fmt_out( OutBuf, TempStr, CHAR, 12, bitno );
				break ;

			case 7:

				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, ITOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, ITOA, 6, bitno );
				break ;

			case 11:

				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, ITOA, 6, bitno );
				break ;

			case 12:

				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, ITOA, 6, bitno );
				break;

			case 13:

				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, ITOA, 6, bitno );
				break ;

			case 14:

				OutBuf += fmt_out( OutBuf, &txnmsg->ExpiryDate, ITOA, 4, bitno );
				break ;

			case 15:
				break ;


			case 17:

				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 32:

				len = strlen( txnmsg->AcquirerInst );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->AcquirerInst, CHAR, len, bitno );
				break ;

			case 35:
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
				OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 2, bitno );
				break;

			case 41:

				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break ;

			case 42:

				OutBuf += fmt_out( OutBuf, txnmsg->AcceptorId, CHAR, 15, bitno );
				break ;

			case 43:

				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 44:

				len = strlen( txnmsg->RsvFld2 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );

				break ;

			case 49:

				OutBuf += fmt_out( OutBuf, &txnmsg->AcqCurrencyCode, ITOA, 3, bitno );
				break;

			case 52:

				OutBuf += fmt_out( OutBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break;

			case 60:

				len = strlen( txnmsg->RsvFld1 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
				break ;

			case 61:

				len = strlen( txnmsg->RsvFld2 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				break;

			case 62:

				len = strlen( txnmsg->RsvFld3 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, CHAR, len, bitno );
				break;

			case 63:

				len = strlen( txnmsg->RsvFld4 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, CHAR, len, bitno );
				break;

			case 65:

				break ;

			case 70:

				break ;

			case 90:

				break ;

			case 95:

				break ;

			case 100:

				break;

			case 102:

				break;

			default:
				trace( "Unhandled bit in iso8583" );
				break ;
		}
	}
	return( OutBuf - BufOffset );
}

void EzMerchant8583 :: formatAmt( const char *Amount, char *OutStr, int Len )
{
	char formatStr[ 50 ];
	memset( formatStr, 0, sizeof( formatStr ) );
	trace( "Amount[%s]", Amount );
	for( int i = 0, j = 0; i < strlen( Amount ); i++ )
	{
		if( Amount[ i ] != '.' && Amount[ i ] !=  ' ' )
		{
			formatStr[ j ] = Amount[ i ];
			j++;
		}
	}
	trace( "formatStr[%s] Len[%d]", formatStr, Len );
	memset( OutStr, '0', Len - strlen( formatStr ) );
	strcpy( OutStr + Len - strlen( formatStr ), formatStr );
	trace( "OutStr[%s]", OutStr );
}

void EzMerchant8583 :: normalizeAmt( const char *SrcAmt, char *DestAmt, int decPosition )
{
	if( strlen( SrcAmt ) <= decPosition )
	{
		strcpy( DestAmt, "." );
		strcat( DestAmt, SrcAmt );
	}
	else
	{
		bool found = false;
		for( int i = 0, j = 0; i < strlen( SrcAmt ); i++ )
		{
			if( SrcAmt[ i ] == '0' && !found )
				continue;
			found = true;
			if( ( i + decPosition ) == strlen( SrcAmt ) )
			{
				DestAmt[ j ] = '.';
				j++;
			}
			DestAmt[ j ] = SrcAmt[ i ];
			j++;
		}
	}
}

int EzMerchant8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len, ExtNetCode;
	char StmtBuf[ STMT_BUF_SIZE +1 ], CheckDate[ 7 ],  temp[10], temptxn[7], TempStr[ 50 ];
	char TempTranDate[ 7 ], *CurrentYear;
	int date;

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
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOI, 6, bitno );
				break ;

			case 4:

				InBuf += fmt_in( InBuf, txnmsg->Amount, CHAR, 12, bitno );
				memset( TempStr, 0, sizeof( TempStr ) );
				normalizeAmt( txnmsg->Amount, TempStr, 2 );
				memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
				strcpy( txnmsg->Amount, TempStr );
				break ;

			case 7:

				InBuf += fmt_in( InBuf, &txnmsg->TranDate, ATOI, 6, bitno );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOI, 6, bitno );
				break ;

			case 11:

				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOI, 6, bitno );
				break ;

			case 12:

				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOI, 6, bitno );
				break ;

			case 13:

				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOI, 6, bitno );
				break ;

			case 14:

				InBuf += fmt_in( InBuf, &txnmsg->ExpiryDate, ATOI, 4, bitno );
				break ;

			case 15:
				break ;

			case 17:

				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, bitno );
				break ;

			case 32:

				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->AcquirerInst, CHAR, len, bitno );
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

				InBuf += fmt_in( InBuf, txnmsg->RefNum, CHAR, 12, bitno );
				break ;

			case 38:

				InBuf += fmt_in( InBuf, txnmsg->AuthNum, CHAR, 6, bitno );
				break ;

			case 39:
				break ;

			case 41:

				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break ;

			case 42:

				InBuf += fmt_in( InBuf, txnmsg->AcceptorId, CHAR, 15, bitno );
				break;

			case 43:

				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 44:

				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				break ;

			case 49:

				InBuf += fmt_in( InBuf, &txnmsg->AcqCurrencyCode, ATOI, 3, bitno );
				break ;

			case 50:

				InBuf += fmt_in( InBuf, &txnmsg->SettCurrencyCode, ATOI, 3, bitno );
				break ;

			case 52:
				InBuf += fmt_in( InBuf, txnmsg->PINBlock, CHAR, 16, bitno );
				break ;

			case 60:

				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, bitno );
				break ;

			case 61:

				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, len, bitno );
				break ;

			case 62:

				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, bitno );
				break ;

			case 63:

				InBuf += fmt_in( InBuf, &len, ATOI, 2, bitno );
				InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, len, bitno );
				break ;

			case 70://NetCode
				break ;

			case 90:
				break ;

			case 95:
				break ;

			case 100:
				break;

			case 102:
				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", bitno );
				break ;
		}
	}
	return 1;
}

void EzMerchant8583 :: removeLeadingZeros( const char *SrcStr, char *DestStr )
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

int EzMerchant8583 :: doMerchantPreAuth( struct EzTxnMsg *txnmsg )
{
	memset( &merchantprofile_rec, 0, sizeof( struct EzMMSMerchantProfile ) );
	if( mmsutil.readMerchantProfile( txnmsg->AcquirerInst, txnmsg->AcceptorId, &merchantprofile_rec ) < 0 )
	{
		trace( "Error in Reading InstId[%s] MerchantId[%s] from MerchantProfile..." );
		txnmsg->RespCode = EZLINK_RC_InvalidMerchant;
		return -1;
	}
	return 1;
}

int EzMerchant8583 :: doMerchantPreEdits( struct EzTxnMsg *txnmsg )
{
	//If Maxstrip set 08000, If ICC then 0400
	txnmsg->PosConditionCode = 2000; //Manual Entry
	memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
	strcpy( txnmsg->OrgPort, GetLastSenderChannelName() );
	memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
	strcpy( txnmsg->OrgChannel, GetSourceChannelName() );
	memset( txnmsg->SrcChannel, 0, sizeof( txnmsg->SrcChannel ) );
	strcpy( txnmsg->SrcChannel, GetSourceChannelName() );
	memset( txnmsg->DeviceType, 0, sizeof( txnmsg->DeviceType ) );
	strcpy( txnmsg->DeviceType, "ECOM" );
	txnmsg->PinVerFlg = 'N';
	return 1;
}

void EzMerchant8583 :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 4098 + 1 ];
	char MsgBuffer[ 4098 + 1 ];

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
			if( doMerchantPreAuth( &txnmsg ) < 0 )
			{
				memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
				if( ComposeISOMessage( &txnmsg, MsgBuffer ) < 0 )
				{
					trace( "Error in Composing ISO Message" );
					continue;
				}
				if( WritePortChannel( GetLastSenderChannelName(), MsgBuffer, strlen( MsgBuffer ) ) < 0 )
					trace( "Error in Writing Message to Port[%s]", GetLastSenderChannelName() );
				else
					trace( "Written Message to Port[%s]", GetLastSenderChannelName() );
				continue;
			}
			doMerchantPreEdits( &txnmsg );
			mmsdbutil.postMerchantEntries( &txnmsg );
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
			trace( "From TxnMgr->AcquirerInst[%s] chn[%s]", txnmsg.AcquirerInst, txnmsg.chn );
			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( ComposeISOMessage( &txnmsg, MsgBuffer ) < 0 )
			{
				trace( "Error in Composing ISO Message" );
				continue;
			}
			mmsdbutil.postMerchantEntries( &txnmsg );
			if( WritePortChannel( txnmsg.DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
				trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
			else
				trace( "Written Message to Port[%s]", txnmsg.DestPort );
		}
	}
}

int main( int argc, char **argv )
{
	EzMerchant8583 ezmerchant8583obj;
	ezmerchant8583obj.InitEzMerchant8583( argv[ 0 ] );
	ezmerchant8583obj.ServiceRequest();
	return 1;
}









