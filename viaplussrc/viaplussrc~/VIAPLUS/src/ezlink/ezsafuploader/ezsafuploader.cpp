#include <ezlink/ezsafuploader.h>

void EzSafUploader :: initSafUploader( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsafuploader.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^^^^^^^^^^^^^^EzSafUploader Started^^^^^^^^^^^^^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzSafUploader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}
	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzSafUploader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	if( CreateChannel( "EzSafUploader", TaskName ) < 0 )
	{
		trace( "Error in Creating EzSafUploader Channel" );
		trace( "^^^^^^^^^^^EzSafUploader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		trace( "^^^^^^^^^^^EzSafUploader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	if( initNetworkUtil( this ) < 0 )
	{
		trace( "Error in Initializing NetworkUtil" );
		trace( "^^^^^^^^^^^EzSafUploader Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

void EzSafUploader :: getString( const char *LineBuffer, char *ColStr, int Column )
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
}

int EzSafUploader :: getTokenCount( const char *msg, char ch )
{
	int TokenCount = 0;
	for( int i = 0; i < strlen( msg ); i++ )
	{
		if( msg[ i ] == ch )
			TokenCount++;
	}
	return TokenCount + 1;
}

void EzSafUploader :: getToken( const char *msg, char *tmp, char ch, int count )
{
	int i = 0, j = 0, cnt = 0;
	for( i = 0; i < strlen( msg ); i++ )
	{
		if( msg[ i ] == ch )
				cnt++;
		else if( cnt == count )
				break;
		else if ( cnt + 1 == count )
		{
				tmp[ j ] = msg[ i ];
				j++;
		}
	}
}

bool EzSafUploader :: isBlankLine( const char *line_str )
{
	for( int i = 0; i < strlen( line_str ); i++ )
	{
		if( ( line_str[ i ] != ' ' ) && ( line_str[ i ] != '\t' ) && ( line_str[ i ] != '\n' ) )
				return false;
	}
	return true;
}

void EzSafUploader :: processPBFUploadRequest( struct EzTxnMsg *txnmsg, const char *NetworkChannel )
{
	char PBFPath[ PBF_PATH_SIZE + 1 ], dirpath[ PBF_PATH_SIZE + 20 ], fpath[ PBF_PATH_SIZE + 40 ], temppath[ PBF_PATH_SIZE + 50 ];
	char RecordStr[ PBF_RECORD_SIZE + 1 ], LineStr[ PBF_RECORD_SIZE + 1 ], InstId[ 13 ], AccountNo[ 33 ], AvailBal[ 33 ], LedgerBal[ 33 ];
	char PBFSearchString[ PBF_SEARCH_STRING_SIZE + 1 ], PBFFileFormatStr[ PBF_FILE_FORMAT_STRING_SIZE + 1 ], AccountFormatStr[ ACCOUNT_FORMAT_STRING_SIZE + 1 ];
	char FieldStr[ FIELD_STR_SIZE + 1 ], BranchCode[ 13 ], AccountType[ 13 ], ProductCode[ 13 ], AccountStr[ 33 ];
	int FieldCount, AccountFormatCount;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	FILE *fp, *fp_ok, *fp_err;
	char *endptr;
	struct tm *timenow;
	time_t t = 0;
	int retval;
	EzCfgUtil cfgutil;

	trace( DEBUG_TEST, "Processing PBF Upload Request for NetworkId[%s] BranchCode[%s]", txnmsg->NetworkId, txnmsg->IssBranchCode );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return;
	}

	if( !strlen( txnmsg->IssuerInst ) || !strcmp( txnmsg->IssuerInst, "*" ) )
	{
		trace( DEBUG_TEST, "test...1" );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( "PBF#DEFAULTINST", cfgval, 2 )  < 0 )
		{
			trace( "Error in Searching PBF#DEFAULTINST from file[%s]", cfgpath );
			cfgutil.cfg_close();
			return;
		}
		memset( txnmsg->IssuerInst, 0, sizeof( txnmsg->IssuerInst ) );
		strcpy( txnmsg->IssuerInst, cfgval );
		memset( PBFSearchString, 0, sizeof( PBFSearchString ) );
		sprintf( PBFSearchString, "PBF#FILEFORMAT#%s", txnmsg->IssuerInst );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( PBFSearchString, cfgval, 2 )  < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", PBFSearchString, cfgpath );
			cfgutil.cfg_close();
			return;
		}
		memset( PBFFileFormatStr, 0, sizeof( PBFFileFormatStr ) );
		strcpy( PBFFileFormatStr, cfgval );

		memset( PBFSearchString, 0, sizeof( PBFSearchString ) );
		sprintf( PBFSearchString, "PBF#FILEFORMAT#%s", txnmsg->IssuerInst );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( PBFSearchString, cfgval, 3 )  < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", PBFSearchString, cfgpath );
			cfgutil.cfg_close();
			return;
		}
		memset( AccountFormatStr, 0, sizeof( AccountFormatStr ) );
		strcpy( AccountFormatStr, cfgval );
		trace( DEBUG_TEST, "PBFFileFormatStr[%s] AccountFormatStr[%s] for InstId[%s]", PBFFileFormatStr, AccountFormatStr, txnmsg->IssuerInst );
	}
	else
	{
		trace( DEBUG_TEST, "test...2" );
		memset( PBFSearchString, 0, sizeof( PBFSearchString ) );
		sprintf( PBFSearchString, "PBF#FILEFORMAT#%s", txnmsg->IssuerInst );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( PBFSearchString, cfgval, 2 )  < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", PBFSearchString, cfgpath );
			cfgutil.cfg_close();
			return;
		}
		memset( PBFFileFormatStr, 0, sizeof( PBFFileFormatStr ) );
		strcpy( PBFFileFormatStr, cfgval );

		memset( PBFSearchString, 0, sizeof( PBFSearchString ) );
		sprintf( PBFSearchString, "PBF#FILEFORMAT#%s", txnmsg->IssuerInst );
		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( PBFSearchString, cfgval, 3 )  < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", PBFSearchString, cfgpath );
			cfgutil.cfg_close();
			return;
		}
		memset( AccountFormatStr, 0, sizeof( AccountFormatStr ) );
		strcpy( AccountFormatStr, cfgval );
		trace( DEBUG_TEST, "PBFFileFormatStr[%s] AccountFormatStr[%s] for InstId[%s]", PBFFileFormatStr, AccountFormatStr, txnmsg->IssuerInst );
	}
	cfgutil.cfg_close();

	FieldCount = getTokenCount( PBFFileFormatStr, '^' );
	AccountFormatCount = getTokenCount( AccountFormatStr, '^' );
	trace( DEBUG_TEST, "FieldCount[%d] AccountFormatCount[%d]", FieldCount, AccountFormatCount );

	memset( PBFPath, 0, sizeof( PBFPath ) );
	sprintf( PBFPath, "%s/%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "files", "pbf", txnmsg->NetworkId, txnmsg->RsvFld1 );

	fp = fopen( PBFPath, "r" );

	if( fp == NULL )
	{
		trace( DEBUG_ERROR, "Error in Opening File[%s]", PBFPath );
		txnmsg->MsgType = EZLINK_TXN_PBFUploadResponse;
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;

		if( WriteChannel( NetworkChannel, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
			trace( DEBUG_ERROR, "Error in Writing Message to Network Channel[%s]", NetworkChannel );
		else
			trace( DEBUG_NORMAL, "Written Message to Network Channel[%s]", NetworkChannel );
		return;
	}

	t = time( &t );
	timenow = localtime( &t );

	memset( dirpath, 0, sizeof( dirpath ) );
	sprintf( dirpath, "%s/%s/%s/%s/%02d%02d%02d", getenv( "EZDIR_HOME" ), "files", "pbf", txnmsg->NetworkId, timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year % 100 );
	mkdir( dirpath, 0777 );
	memset( fpath, 0, sizeof( fpath ) );
	sprintf( fpath, "%s/%s_%02d%02d%02d", dirpath, txnmsg->RsvFld1, timenow->tm_hour, timenow->tm_min, timenow->tm_sec );

	memset( temppath, 0, sizeof( temppath ) );
	sprintf( temppath, "%s.success", fpath );

	fp_ok = fopen( temppath, "w" );

	if( fp_ok == NULL )
	{
		trace( DEBUG_ERROR, "Error in Opening File[%s]", temppath );
		fclose( fp );
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		txnmsg->MsgType = EZLINK_TXN_PBFUploadResponse;
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;

		if( WriteChannel( NetworkChannel, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
			trace( DEBUG_ERROR, "Error in Writing Message to Network Channel[%s]", NetworkChannel );
		else
			trace( DEBUG_NORMAL, "Written Message to Network Channel[%s]", NetworkChannel );
		return;
	}

	memset( temppath, 0, sizeof( temppath ) );
	sprintf( temppath, "%s.err", fpath );
	fp_err = fopen( temppath, "w" );

	if( fp_err == NULL )
	{
		trace( DEBUG_ERROR, "Error in Opening File[%s]", temppath );
		fclose( fp );
		fclose( fp_ok );

		txnmsg->MsgType = EZLINK_TXN_PBFUploadResponse;
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;

		if( WriteChannel( NetworkChannel, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
			trace( DEBUG_ERROR, "Error in Writing Message to Network Channel[%s]", NetworkChannel );
		else
			trace( DEBUG_NORMAL, "Written Message to Network Channel[%s]", NetworkChannel );
		return;
	}

	if( strlen( txnmsg->IssBranchCode ) )
	{
		retval = ResetAccountBalance( txnmsg->IssuerInst, txnmsg->IssBranchCode );
		if( retval != 0 )
			trace( DEBUG_ERROR, "Error in Reseting Account Balance for BranchCode[%s]", txnmsg->IssBranchCode );
		else
			trace( DEBUG_NORMAL,"Reset..Account Balance for BrCode[%s]", txnmsg->IssBranchCode );
	}

	while( !feof( fp ) )
	{
		memset( RecordStr, 0, sizeof( RecordStr ) );
		fgets( RecordStr, sizeof( RecordStr ), fp );
		if( isBlankLine( RecordStr ) )
			continue;
		memset( LineStr, 0, sizeof( LineStr ) );
		getString( RecordStr, LineStr, 1 );
		trace( DEBUG_TEST, "LineStr[%s]", LineStr );

		for( int i = 0; i < FieldCount; i++ )
		{
			memset( FieldStr, 0, sizeof( FieldStr ) );
			getToken( PBFFileFormatStr, FieldStr, '^', i + 1 );
			if( !strcasecmp( FieldStr, "$BRANCHCODE" ) )
			{
				memset( BranchCode, 0, sizeof( BranchCode ) );
				getToken( LineStr, BranchCode, '^', i + 1 );
				trace( DEBUG_TEST, "BranchCode[%s]", BranchCode );
			}
			else if( !strcasecmp( FieldStr, "$INSTID" ) )
			{
				memset( InstId, 0, sizeof( InstId ) );
				getToken( LineStr,  InstId, '^', i + 1 );
				trace( DEBUG_TEST, "InstId[%s]", InstId );
			}
			else if( !strcasecmp( FieldStr, "$ACCOUNTTYPE" ) )
			{
				memset( AccountType, 0, sizeof( AccountType ) );
				getToken( LineStr,  AccountType, '^', i + 1 );
				trace( DEBUG_TEST, "AccountType[%s]",  AccountType );
			}
			else if( !strcasecmp( FieldStr, "$PRODUCTCODE" ) )
			{
				memset( ProductCode, 0, sizeof( ProductCode ) );
				getToken( LineStr,  ProductCode, '^', i + 1 );
				trace( DEBUG_TEST, "ProductCode[%s]",  ProductCode );
			}
			else if( !strcasecmp( FieldStr, "$ACCOUNT" ) )
			{
				memset( AccountNo, 0, sizeof( AccountNo ) );
				getToken( LineStr,  AccountNo, '^', i + 1 );
				trace( DEBUG_TEST, "AccountNo[%s]",  AccountNo );
			}
			else if( !strcasecmp( FieldStr, "$AVAILBAL" ) )
			{
				memset( AvailBal, 0, sizeof( AvailBal ) );
				getToken( LineStr,  AvailBal, '^', i + 1 );
				trace( DEBUG_TEST, "AvailBalance[%s]",  AvailBal );
			}
			else if( !strcasecmp( FieldStr, "$LEDGERBAL" ) )
			{
				memset( LedgerBal, 0, sizeof( LedgerBal ) );
				getToken( LineStr,  LedgerBal, '^', i + 1 );
				trace( DEBUG_TEST, "LedgerBalance[%s]", LedgerBal );
			}
		}

		memset( AccountStr, 0, sizeof( AccountStr ) );
		for( int i = 0; i < AccountFormatCount; i++ )
		{
			memset( FieldStr, 0, sizeof( FieldStr ) );
			getToken( AccountFormatStr, FieldStr, '^', i + 1 );
			if( !strcasecmp( FieldStr, "$BRANCHCODE" ) )
				strcat( AccountStr, BranchCode );
			if( !strcasecmp( FieldStr, "$INSTID" ) )
				strcat( AccountStr, InstId );
			else if( !strcasecmp( FieldStr, "$ACCOUNTTYPE" ) )
				strcat( AccountStr, AccountType );
			else if( !strcasecmp( FieldStr, "$PRODUCTCODE" ) )
				strcat( AccountStr, ProductCode );
			else if( !strcasecmp( FieldStr, "$ACCOUNT" ) )
				strcat( AccountStr, AccountNo );
			else
				strcat( AccountStr, FieldStr );
		}

		trace( DEBUG_TEST, "InstId [%s] AccountStr [%s] AvailBal [%s] LedgerBal [%s]" ,InstId, AccountStr, AvailBal, LedgerBal  );

		if( !strlen( InstId ) )
		{
			memset( InstId, 0, sizeof( InstId ) );
			strcpy( InstId, txnmsg->IssuerInst );
		}

		if( !strlen( InstId ) || !strlen( AccountStr ) || !strlen( AvailBal ) || !strlen( LedgerBal ) )
			continue;

		retval = UpdateAccountBalance( InstId, AccountStr, strtod( AvailBal, &endptr ), strtod( LedgerBal, &endptr ) );

		if( retval != 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating Record[%s] OraErr[%05d]", LineStr, retval );
			fprintf( fp_err, "%s\n", LineStr );
		}
		else
		{
			trace( DEBUG_TEST, "Update Record[%s]", LineStr );
			fprintf( fp_ok, "%s\n", LineStr );
		}
	}

	fclose( fp );
	fclose( fp_err );
	fclose( fp_ok );

	trace( DEBUG_NORMAL, "All the PBF Records are Uploaded for NetworkId[%s] PBFFile[%s]", txnmsg->NetworkId, txnmsg->RsvFld1 );

	if( setNetworkStatus( txnmsg->NetworkId, NETWORK_STATUS_SAF ) < 0 )
		trace( DEBUG_ERROR, "Error in Marking Status of NetworkId[%s] as SAF....", txnmsg->NetworkId );
	else
		trace( DEBUG_ERROR, "Marked Status of NetworkId[%s] as SAF....", txnmsg->NetworkId );

	txnmsg->MsgType = EZLINK_TXN_PBFUploadResponse;
	txnmsg->RespCode = EZLINK_RC_Approved;

	if( WriteChannel( NetworkChannel, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
		trace( DEBUG_ERROR, "Error in Writing Message to Network Channel[%s]", NetworkChannel );
	else
		trace( DEBUG_NORMAL, "Written Message to Network Channel[%s]", NetworkChannel );
}

void EzSafUploader :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize, retval;
	char NetworkChannel[ 33 ];

	while( 1 )
	{
		trace( "EzSafUploader Waiting For Request....");
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

		if( ReadMessage( ( char * ) &txnmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message From EzSafUploader Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			sleep( 1 );
			continue;
		}
		trace( DEBUG_NORMAL, "Message Received From Channel[%s] with MsgType[%d]", GetLastSenderChannelName(), txnmsg.MsgType );

		if( !strlen( txnmsg.NetworkId ) )
		{
			trace( DEBUG_ERROR, "NetworkId Field is Null.....Check the Message");
			continue;
		}

		if( txnmsg.MsgType != EZLINK_TXN_PBFUploadRequest )
		{
			trace( DEBUG_ERROR, "Invalid MsgType[%d] Received", txnmsg.MsgType );
			continue;
		}

		trace( DEBUG_NORMAL, "Received PBF Upload Message for NetworkId[%s] FileName[%s]", txnmsg.NetworkId, txnmsg.RsvFld1 );

		if( readNetworkMemory( txnmsg.NetworkId ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in reading NetworkId from NetworkMemory", txnmsg.NetworkId );
			continue;
		}

		if( getNetworkStatus() != NETWORK_STATUS_UP && getNetworkStatus() != NETWORK_STATUS_DOWN )
		{
			trace( DEBUG_ERROR, "Cannot Accept PBF Upload Request .....Network Status has to be Online/Offline...");
			txnmsg.MsgType = EZLINK_TXN_PBFUploadResponse;
			txnmsg.RespCode = EZLINK_RC_UnableToProcess;

			if( WriteChannel( NetworkChannel, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
				trace( DEBUG_ERROR, "Error in Writing Message to Network Channel[%s]", NetworkChannel );
			else
				trace( DEBUG_NORMAL, "Written Message to Network Channel[%s]", NetworkChannel );
			continue;
		}

		if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_SAFUPLOAD ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Setting Network Status for NetworkId[%s]", txnmsg.NetworkId );
			continue;
		}

		memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
		getNetworkPortName( txnmsg.DestPort );
		memset( NetworkChannel, 0, sizeof( NetworkChannel ) );
		getNetworkChannelName( NetworkChannel );

		if( dbutil.DBConnect() < 0 )
		{
			trace( DEBUG_ERROR, "Error in Connecting with Switch DB..." );

			txnmsg.MsgType = EZLINK_TXN_PBFUploadResponse;
			txnmsg.RespCode = EZLINK_RC_UnableToProcess;

			if( WriteChannel( NetworkChannel, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
				trace( DEBUG_ERROR, "Error in Writing Message to Network Channel[%s]", NetworkChannel );
			else
				trace( DEBUG_NORMAL, "Written Message to Network Channel[%s]", NetworkChannel );
			continue;
		}
		trace( DEBUG_NORMAL, "Connected With oracle" );
		processPBFUploadRequest( &txnmsg, NetworkChannel );
		dbutil.DBClose();
	}
}

int main( int argc, char **argv )
{
	EzSafUploader safuploadobj;
	safuploadobj.initSafUploader( argv[ 0 ] );
	safuploadobj.ServiceRequest();
	return 1;
}

