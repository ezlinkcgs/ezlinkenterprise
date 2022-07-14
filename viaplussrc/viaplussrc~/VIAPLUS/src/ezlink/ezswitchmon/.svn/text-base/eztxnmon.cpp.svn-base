#include <ezlink/eztxnmon.h>

int EzTxnMon :: initTxnMon( EzDebugUtil *dptr )
{

	this->dptr = dptr;
	return 1;

}

void EzTxnMon :: getToken( const char *FieldStr, char *TokenStr, char Token, int TokenNo )
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

int EzTxnMon :: getNToken( const char *FieldStr, char Token )
{
        int TokenCount = 0;
        for( int i = 0; i < strlen( FieldStr ); i++ )
        {
                if( FieldStr[ i ] == Token )
                        TokenCount++;
        }
        return TokenCount + 1;
}



int EzTxnMon :: sendTransaction()
{

	return 1;
}

int  EzTxnMon :: composeTxnDescription( struct EzTxnMsg *txnmsg, char *TxnDesc)
{
	char Description[ TXNDESC + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], Token[ 50 ], Desc[ 50 ], Parse[ 50 ];
	int desc_count = 0;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg/switchmon", "eztxnmon.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening file[%s]...", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TXNMON#TXNDESC", cfgval, 2 ) < 0 )
	{
		dptr->trace ( "Error in Finding TXNMON#TXNDESC in [ %s ]", cfgpath );
		return -1;
    }
	memset( Description, 0, sizeof( Description ) );
	strcpy( Description, cfgval );

	dptr->trace( DEBUG_TEST, "The Description String [ %s ]", Description );
	desc_count = getNToken( Description, '+' );

	memset( TxnDesc, 0, sizeof( TxnDesc ) );

	for ( int i = 1; i < desc_count; i++ )
	{
		memset( Token, 0, sizeof( Token ) );
		getToken( Description, Token, '+', i );
		if( !strcasecmp( "$MSGTYPE", Token ) )
		{
			memset( Parse, 0, sizeof( Parse ) );
			sprintf( Parse, "MSGTYPE#%d", txnmsg->MsgType );
			strcat( TxnDesc, DATA_FS);
			if( cfgutil.cfg_search( Parse, Desc, 2 ) < 0 )
			{
				memset( Desc, 0, sizeof( Desc ) );
				sprintf( Desc, "%d", txnmsg->MsgType );
				strcat( TxnDesc, Desc  );
				break;
			}
			else
				strcat( TxnDesc, Desc );

			break;
		}
		else if ( !strcasecmp( "$CHN", Token ) )
		{
			strcat( TxnDesc, DATA_FS);
			strcat( TxnDesc, txnmsg->chn );
			break;
		}
		else if( !strcasecmp( "$RESPCODE", Token ) )
		{
			memset( Parse, 0, sizeof( Parse ) );
			sprintf( Parse, "RESPCODE#%d", txnmsg->RespCode );
			strcat( TxnDesc, DATA_FS);
			if( cfgutil.cfg_search( Parse, Desc, 2 ) < 0 )
			{
				memset( Desc, 0, sizeof( Desc ) );
				sprintf( Desc, "%d", txnmsg->RespCode );
				strcat( TxnDesc, Desc  );
				break;
			}
			else
				strcat( TxnDesc, Desc );

			break;
		}
		else if( !strcasecmp( "$TRANDATE", Token ) )
		{
			memset( Desc, 0, sizeof( Desc ) );
			sprintf( Desc, "%d", txnmsg->TranDate );
			strcat( TxnDesc, DATA_FS);
			strcat( TxnDesc, Desc  );
			break;
		}
		else if( !strcasecmp( "$TRANTIME", Token ) )
		{
			memset( Desc, 0, sizeof( Desc ) );
			sprintf( Desc, "%d", txnmsg->TranTime );
			strcat( TxnDesc, DATA_FS);
			strcat( TxnDesc, Desc  );
			break;
		}
		else if ( !strcasecmp( "$AMOUNT", Token ) )
		{
			strcat( TxnDesc, DATA_FS);
			strcat( TxnDesc, txnmsg->Amount  );
			break;
		}
		else if( !strcasecmp( "$TXNCODE", Token ) )
		{
			memset( Parse, 0, sizeof( Parse ) );
			sprintf( Parse, "TXNCODE#%d", TXNCODE( txnmsg->TxnCode ) );
			strcat( TxnDesc, DATA_FS);
			if( cfgutil.cfg_search( Parse, Desc, 2 ) < 0 )
			{
				memset( Desc, 0, sizeof( Desc ) );
				sprintf( Desc, "%d", txnmsg->TxnCode );
				strcat( TxnDesc, Desc  );
				break;
			}
			else
				strcat( TxnDesc, Desc );

		}
		else if( !strcasecmp( "$REFNUM", Token ) )
		{
			strcat( TxnDesc, DATA_FS);
			strcat( TxnDesc, txnmsg->RefNum );
		}
		else if( !strcasecmp( "$TERMID", Token ) )
		{
			strcat( TxnDesc, DATA_FS );
			strcat( TxnDesc, txnmsg->TerminalId );
		}
		else if( !strcasecmp( "$TERMLOCATION", Toke ) )
		{
			strcat( TxnDesc, DATA_FS );
			strcat( TxnDesc, txnmsg->TerminalLocation );
		}
		else if( !strcasecmp( "$ISSINST", Token ) )
		{
			strcat( TxnDesc, DATA_FS );
			strcat( TxnDesc, txnmsg->IssuerInst );

		}
		else if( !strcasecmp( "$ACQINST", Token ) )
		{
			strcat( TxnDesc, DATA_FS );
			strcat( TxnDesc, txnmsg->AcquirerInst );

		}
		else if( !strcasecmp( "$ISSNTWK", Token ) )
		{
			strcat( TxnDesc, DATA_FS );
			strcat( TxnDesc, txnmsg->IssuerNetworkId );

		}
		else if( !strcasecmp( "$DEVICETYPE", Token ) )
		{
			strcat( TxnDesc, DATA_FS );
			strcat( TxnDesc, txnmsg->DeviceType );

		}
	}

	return 1;
}


int EzTxnMon :: insertTxnMemory( char *buffer )
{
	struct sembuf sem_buf;
	int retval = 1;

	for( int i = 0; i < MAX_MON_SIZE; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( TxnMonSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for Transaction Mon Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( TxnMonShmPtr + i )->ReqBuffer, RECORD_INIT_VAL ) )
		{
			memset( TxnMonShmPtr + i, 0, sizeof( struct EzTranMon ) );
			memcpy( TxnMonShmPtr + i, buffer, sizeof( struct EzTranMon ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( TxnMonSemId, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for Transaction Mon Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnMonSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for Transaction Mon Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}


int EzTxnMon :: readTxnMemory( char *Buffer, int Req )
{
	struct sembuf sem_buf;
	int retval = -1;
	char ReqBuffer[ BUFFER_SIZE ];
	memset( Buffer, 0, sizeof( Buffer ) );

	for( int i = 0; i < MAX_MON_SIZE ; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( TxnMonSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for TxnMemory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( i < Req )
		{
			memset( ReqBuffer, 0, sizeof( ReqBuffer ) );
			if( strcmp( ( TxnMonShmPtr + i )->ReqBuffer, RECORD_INIT_VAL ) )
			{
				strcat( ReqBuffer, ( TxnMonShmPtr +i )->ReqBuffer );
				strcat( ReqBuffer, RECORD_FS );
				strcat( Buffer, ReqBuffer );
				Req++;

			}
		}
		else
		{
			sem_buf.sem_op = 2;
			if( semop( TxnMonSemId, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for TxnMemory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnMonSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for TxnMemory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}


