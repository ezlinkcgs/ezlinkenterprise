#include <ezbusiness/ezteller8583.h>

EzTeller8583 :: EzTeller8583()
{
}

EzTeller8583 :: ~EzTeller8583()
{
}

void EzTeller8583 :: InitEzTeller8583( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezteller8583.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzTeller8583 Started Running^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzTeller8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzTeller8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzTeller8583" ) < 0 )
	{
		trace( "Error in Creating EzTeller8583 Channel" );
		trace( "^^^^^^^^^^^EzTeller8583 Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", "EzTeller8583BitMap.cfg" );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~EzTeller8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
		closeDebug();
		TaskExit();
	}

	initFmtUtil( this );

	TaskInit();
	initEzSigUtil( this );
}

int EzTeller8583 :: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char *BufOffset;
	unsigned char BitMap[ 33 ];
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
				OutBuf += fmt_out( OutBuf, &txnmsg->TxnCode, LTOA, 6, bitno );
				break ;

			case 4:
				if( strlen( txnmsg->Amount ) <= 0 )
				{
					strncpy( txnmsg->Amount, "000000000000", 12 );
					OutBuf += fmt_out( OutBuf, txnmsg->Amount, CHAR, 12, bitno );
				}
				else
				{
					char TempAmount[13];
					int Amount;
					memset( TempAmount, 0, sizeof( TempAmount ) );
					Amount = atoi( txnmsg->Amount ) * 100;
					sprintf( TempAmount, "%012d", Amount );
					OutBuf += fmt_out( OutBuf, TempAmount, CHAR, 12, bitno );
					
				}
				break ;

			case 7:
				OutBuf += fmt_out( OutBuf, &txnmsg->TranDate, LTOA, 6, bitno );
				OutBuf += fmt_out( OutBuf, &txnmsg->TranTime, LTOA, 6, bitno );
				break ;

			case 11:
				OutBuf += fmt_out( OutBuf, &txnmsg->TraceNo, LTOA, 6, bitno );
				break ;

			case 12:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalTime, LTOA, 6, bitno );
				break;

			case 13:
				OutBuf += fmt_out( OutBuf, &txnmsg->LocalDate, LTOA, 6, bitno );
				break ;

			case 17:
				OutBuf += fmt_out( OutBuf, &txnmsg->CaptureDate, LTOA, 6, bitno );
				break ;

			case 18:
				OutBuf += fmt_out( OutBuf, &txnmsg->MerchantType, STOA, 4, bitno );
				break;

			case 32:
				if( txnmsg->MsgType == 800 )
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
				break ;

			case 39:
				OutBuf += fmt_out( OutBuf, &txnmsg->RespCode, ITOA, 2, bitno );
				break;

			case 41:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalId, CHAR, 16, bitno );
				break ;

			case 43:
				OutBuf += fmt_out( OutBuf, txnmsg->TerminalLocation, CHAR, 40, bitno );
				break;

			case 54:
				char tempStr[ 121 ], TempAvailBalance[ 30 ], TempLedgerBalance[ 30 ];
				memset( TempAvailBalance, 0, sizeof( TempAvailBalance ) );
				for( int k = 0, l = 0; k < strlen( txnmsg->AvailBalance ); k++ )
				{
					if( txnmsg->AvailBalance[ k ] != '.' )
					{
						TempAvailBalance[ l ] = txnmsg->AvailBalance[ k ];
						l++;
					}
				}
				memset( TempLedgerBalance, 0, sizeof( TempLedgerBalance ) );
				for( int k = 0, l = 0; k < strlen( txnmsg->LedgerBalance ); k++ )
				{
					if( txnmsg->LedgerBalance[ k ] != '.' )
					{
						TempLedgerBalance[ l ] = txnmsg->LedgerBalance[ k ];
						l++;
					}
				}
				memset( tempStr, 0, sizeof( tempStr ) );
	            sprintf( tempStr, "0502356D%012s0501356D%012s", TempAvailBalance, TempLedgerBalance );
	            len = strlen( tempStr );
	            OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
	            OutBuf += fmt_out( OutBuf, tempStr, CHAR, len, bitno );
				break;

			case 60:
				len = strlen( txnmsg->IssBranchCode );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->IssBranchCode, CHAR, len, bitno );
				break ;

			case 61:
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
                OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld3, CHAR, len, bitno );
                break ;

			case 65:
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld4, CHAR, 6, bitno );
                break ;

			case 66:
                len = strlen( txnmsg->RsvFld5 );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 2, bitno );
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
                break ;

			case 72:
                len = strlen( txnmsg->RsvFld2 );
                OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
                OutBuf += fmt_out( OutBuf, txnmsg->RsvFld2, CHAR, len, bitno );
                break ;

			case 90:
				/*
				InBuf += format_str( ( unsigned char * ) DevMsg->RsvFld18, InBuf, CHAR, 22 );
				dbg->trace( NORMAL, "Original Data Elements [%s]\n", DevMsg->RsvFld18 );
				*/
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

			case 127:
				len = strlen( txnmsg->RsvFld1 );
				OutBuf += fmt_out( OutBuf, &len, ITOA, 3, bitno );
				OutBuf += fmt_out( OutBuf, txnmsg->RsvFld1, CHAR, len, bitno );
				break;


			default:
				trace( "Unhandled bit in iso8583" );
				break ;
		}
	}
	return( OutBuf - BufOffset );
}


int EzTeller8583 :: DecomposeISOMessage( char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 33 ];
	int Ind, len;
	InBuf += fmt_in( InBuf, &txnmsg->MsgType, ATOI, 4 , 0 );

	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmt_in( InBuf, BitMap, ATOH, 16, 1 );

	if( IsBitSet( BitMap, 1 ) )
		InBuf += fmt_in( InBuf, BitMap + 8, ATOH, 16, 1 );

	for( int Ind = 0; Ind < 128; Ind++ )
	{
		if( !IsBitSet( BitMap, Ind ) )
			continue;

		if( Ind > 64 )
		{
			if( !IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( Ind )
		{

			case 1:
			// Seconday Bit Map
			break;

			case 2:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->chn, CHAR, len, Ind );
				break ;

			case 3:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOL, 6, Ind );
				break ;

			case 4:
				 char TempAmount[13];
                                int Amount;
                                memset( TempAmount, 0, sizeof( TempAmount ) );
                                InBuf += fmt_in( InBuf, TempAmount, CHAR, 12, Ind );
				if( TempAmount<= 0 )
                                {
                                        strncpy( txnmsg->Amount, "000000000000", 12 );
                                }
				else
				{
					Amount = atoi( TempAmount ) / 100;
                                        trace( "AmountFromHost[%d]", Amount );
                                        sprintf( txnmsg->Amount, "%d%s", Amount,".00" );
                                        trace( "txnmsg->Amount[%s]", txnmsg->Amount );
				}

			break;
					
			case 7:
				InBuf += fmt_in( InBuf, &txnmsg->TranDate, ATOL, 6, Ind );
				InBuf += fmt_in( InBuf, &txnmsg->TranTime, ATOL, 6, Ind );
				break ;

			case 11:
				InBuf += fmt_in( InBuf, &txnmsg->TraceNo, ATOL, 6, Ind );
				break ;

			case 12:
				InBuf += fmt_in( InBuf, &txnmsg->LocalTime, ATOL, 6, Ind );
				break ;

			case 13:
				InBuf += fmt_in( InBuf, &txnmsg->LocalDate, ATOL, 6, Ind );
				break ;

			case 17:
				InBuf += fmt_in( InBuf, &txnmsg->CaptureDate, ATOL, 6, Ind );
				break ;

			case 18:
				InBuf += fmt_in( InBuf, &txnmsg->MerchantType, ATOS, 4, Ind );
				break ;

			case 32:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->AcquirerInst, CHAR, len, Ind );
				break ;

			case 39:
				InBuf += fmt_in( InBuf, &txnmsg->RespCode, ATOI, 2, Ind );
				break ;

			case 41:
				InBuf += fmt_in( InBuf, txnmsg->TerminalId, CHAR, 16, Ind );
				break ;

			case 43:
				InBuf += fmt_in( InBuf, txnmsg->TerminalLocation, CHAR, 40, Ind );
				break;

			case 54:
				char tempStr[ 20 ], amtType[ 3 ];


				InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind );
				for( int i = 0; i < len; )
				{
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 2, Ind );
					i += 2;
					memset( amtType, 0, sizeof( amtType ) );
					InBuf += fmt_in( InBuf, amtType, CHAR, 2, Ind );
					i += 2;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 3, Ind );
					i += 3;
					memset( tempStr, 0, sizeof( tempStr ) );
					InBuf += fmt_in( InBuf, tempStr, CHAR, 1, Ind );
					i += 1;
					if( !strcmp( amtType, "02" ) )
					{
						char TempBalance[ 30 ];

						memset( TempBalance, 0, sizeof( TempBalance ) );
						for( int k = 0, l = 0; k < strlen( txnmsg->AvailBalance ); k++ )
						{
							if( txnmsg->AvailBalance[ k ] != '.' )
							{
								TempBalance[ l ] = txnmsg->AvailBalance[ k ];
								l++;
							}
						}
						InBuf += fmt_in( InBuf, TempBalance, CHAR, 12, Ind );
					}
					else
					{
						char TempBalance[ 30 ];
						memset( TempBalance, 0, sizeof( TempBalance ) );
						for( int k = 0, l = 0; k < strlen( txnmsg->LedgerBalance ); k++ )
						{
							if( txnmsg->LedgerBalance[ k ] != '.' )
							{
								TempBalance[ l ] = txnmsg->LedgerBalance[ k ];
								l++;
							}
						}
						InBuf += fmt_in( InBuf, TempBalance, CHAR, 12, Ind );
					}

					//InBuf += fmt_in( InBuf, txnmsg->LedgerBalance, CHAR, 12, Ind );
					i += 12;
				}
				break ;

			case 60:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->IssBranchCode, CHAR, len, Ind );
				break ;

			case 61:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->FromAcctSubType, CHAR, len, Ind );
				break ;

			case 62:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->TxfBranchCode, CHAR, len, Ind );
				break ;

			case 63:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->ToAcctSubType, CHAR, len, Ind );
				break;

			 case 64:
                InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind + 1 );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld3, CHAR, len, Ind + 1 );
                break ;

			 case 65:
                InBuf += fmt_in( InBuf, txnmsg->RsvFld4, CHAR, 6, Ind + 1 );
                break ;

        	case 66:
                InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind + 1 );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld5, CHAR, len, Ind + 1 );
                break ;

			case 67:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->AcqBranchCode, CHAR, len, Ind );
				break ;

			case 70:
				InBuf += fmt_in( InBuf, &txnmsg->TxnCode, ATOI, 3, Ind );
				trace( "Net Code [%03d]", txnmsg->TxnCode );
				break ;

			case 71:
                InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld1, CHAR, len, Ind );
                trace( "Host Data 1 [%s]\n", txnmsg->RsvFld1 );
                break ;

            case 72:
                InBuf += fmt_in( InBuf, &len, ATOI, 3, Ind );
                InBuf += fmt_in( InBuf, txnmsg->RsvFld2, CHAR, len, Ind );
                trace( "Host Data 2 [%s]\n", txnmsg->RsvFld2 );
                break ;

			case 90:
				/*
				InBuf += format_str( ( unsigned char * ) DevMsg->RsvFld18, InBuf, CHAR, 22 );
				dbg->trace( NORMAL, "Original Data Elements [%s]\n", DevMsg->RsvFld18 );
				*/
				break ;

			case 102:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->FromAccount, CHAR, len, Ind );
				break;

			case 103:
				InBuf += fmt_in( InBuf, &len, ATOI, 2, Ind );
				InBuf += fmt_in( InBuf, txnmsg->ToAccount, CHAR, len, Ind );
				break;

			case 127:
				/*
				memset( StmtBuf, 0, sizeof( StmtBuf ) );
				InBuf += format_str( ( unsigned char * ) &len, InBuf, ATOI, 3 );
				InBuf += format_str( ( unsigned char * ) StmtBuf, InBuf, CHAR, len );
				dbg->trace( NORMAL, "Statement Buffer [%s]\n", StmtBuf );
				if ( len > 200 )
				{
					strncpy( DevMsg->RsvFld19, StmtBuf, 200 );
					strncpy( DevMsg->RsvFld20, StmtBuf+200, (len-200 ) );
				}
				else
					strcpy( DevMsg->RsvFld19, StmtBuf );
				*/
				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", Ind );

		}

	}
	return 1;
}


void EzTeller8583 :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 2600 + 1 ];
	char MsgBuffer[ 2600 + 1 ];
	while( 1 )
	{
		trace( "EzTeller8583 Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetLastSenderChannelName() );
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
	EzTeller8583 EzTeller8583obj;
	EzTeller8583obj.InitEzTeller8583( argv[ 0 ] );
	EzTeller8583obj.ServiceRequest();
	return 1;
}

