#include <ezbusiness/eztritondriver.h>

void *EzTritonStd :: eztritonstdobj = 0;

EzTritonStd :: EzTritonStd()
{
	eztritonstdobj = this;
}

EzTritonStd :: ~EzTritonStd()
{
}

int EzTritonStd :: InitEzTritonStdDriver( const char * TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
 /*   RowList RList;
    ColList CList;
    RowList :: iterator RowListIterator;
    ColList :: iterator ColListIterator;
    TxnCodeInfo TInfo;*/

    memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztritondriver.log"  );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0  );

    if( InitEzTaskUtil( this ) < 0 )
    {
           trace( "Error in Initializing EzTaskUtil" );
           trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
           closeDebug( );
           exit( 0  );
	}

    if( InitEzChannelUtil( this ) < 0 )
    {
    	trace( "Error in Initializing EzChannelUtil"  );
    	trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
        closeDebug( );
        TaskExit( );
    }

	if( CreateChannel( TRITONSTDCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating EzTritonDriver Channel"  );
		trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	if( InitEzDeviceUtil( this ) < 0 )
	{
		trace( "Error in Initializing the DeviceUtil"  );
		trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	if( InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing the EzSecurityUtil" );
		trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

    if( LoadTxnCode( "TRITATM" ) < 0 )
    {
		trace( "Error in Initializing the TxnCode List" );
		trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

    if( LoadRespCode( "TRITATM" ) < 0 )
    {
		trace( "Error in Initializing the RespCode List" );
		trace( "^^^^^^^^^^^EzTritonDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
    }

	TaskInit( );
	initEzSigUtil( this  );

	return 1;
}

void EzTritonStd :: getToken( const char *msg, char *tmp, char ch, int count )
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

int EzTritonStd :: ParseToken( char *TokenString, char *Token, int count, char ch )
{
	for( int i = 0, j = 0, cnt = 0; i < strlen( TokenString ); i++ )
	{
		if( TokenString[ i ] == ch )
			cnt++;
		else if( cnt == count )
		        break;
		else if ( cnt + 1 == count )
		{
			Token[ j ] = TokenString[ i ];
			j++;
		}
	}
	return 1;
}

unsigned int EzTritonStd :: crc16( unsigned char *String, int length )
{
	unsigned int crc;
	crc = 0x0000;
	while (length--)
    {
		crc = ( crc >> 8 ) ^ crc_table[(crc ^ (int) *String++) & 0xff];
	}
	return(crc);
}

int EzTritonStd:: GetNColumns( const char *LineBuffer )
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

int EzTritonStd:: GetString( const char *LineBuffer, char *ColStr, int Column )
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

int EzTritonStd :: GetSwitchTxnCode( const char *tritoncode, char *switchcode )
{
        int retval = -1;
        for( int i = 0; i < NTxnCode; i++ )
        {
                if( !strcmp( tritoncode, txncode_ptr[ i ].tritoncode ) )
                {
                        strcpy( switchcode,  txncode_ptr[ i ].switchcode );
                        retval = 1;
                        break;
                }
        }
        return retval;
}

int EzTritonStd :: GetTritonTxnCode( const char *switchcode, char *tritoncode, char *templatefile )
{
        int retval = -1;
        for( int i = 0; i < NTxnCode; i++ )
        {
                if( !strcmp( switchcode, txncode_ptr[ i ].switchcode ) )
                {
                        strcpy( tritoncode,  txncode_ptr[ i ].tritoncode );
                        strcpy( templatefile, txncode_ptr[ i ].templatefile );
                        retval = 1;
                        break;
                }
        }
        return retval;
}

int EzTritonStd :: GetSwitchRespCode( const char *tritonrespcode, char *switchrespcode )
{
        int retval = -1;
        for( int i = 0; i < NRespCode; i++ )
        {
                if( !strcmp( tritonrespcode, respcode_ptr[ i ].tritonrespcode ) )
                {
                        strcpy( switchrespcode,  respcode_ptr[ i ].switchrespcode );
                        retval = 1;
                        break;
                }
        }
        return retval;
}

int EzTritonStd :: GetTritonRespCode( const char *switchrespcode, char *tritonrespcode )
{
        int retval = -1;
        for( int i = 0; i < NRespCode; i++ )
        {
                if( !strcmp( switchrespcode, respcode_ptr[ i ].switchrespcode ) )
                {
                        strcpy( tritonrespcode,  respcode_ptr[ i ].tritonrespcode );
                        retval = 1;
                        break;
                }
        }
        if( retval < 0 )
        	strcpy( tritonrespcode,  "011" );
        return retval;
}

int EzTritonStd :: LoadRespCode( string DeviceTypeId )
{
        FILE *respcode_fp;
        char RespCodePath[ 100 ], LineStr[ 100 ];
        memset( RespCodePath, 0, sizeof( RespCodePath ) );
        sprintf( RespCodePath, "%s/cfg/atm/tritontemplates/%s_respcode.cfg", getenv( "EZDIR_HOME" ), DeviceTypeId.c_str() );

        respcode_fp = fopen( RespCodePath, "r" );
        if( respcode_fp == NULL )
        {
                trace( "Error in Opening File[%s]", RespCodePath );
                return -1;
        }
        NRespCode = 0;
        while( !feof( respcode_fp ) )
        {
                memset( LineStr, 0, sizeof( LineStr ) );
                fgets( LineStr, sizeof( LineStr ), respcode_fp );
                if( IsBlankLine( LineStr ) )
                        continue;
                NRespCode++;
        }

        rewind( respcode_fp );

        trace( "No. of RespCodes  = [%d]", NRespCode );

        respcode_ptr = ( struct RespCodeMap * ) malloc( sizeof( struct RespCodeMap ) * NRespCode );
        memset( respcode_ptr, 0, sizeof( struct RespCodeMap ) * NRespCode );
        int i = 0;
        while( !feof( respcode_fp ) )
        {
                memset( LineStr, 0, sizeof( LineStr ) );
                fgets( LineStr, sizeof( LineStr ), respcode_fp );
                if( IsBlankLine( LineStr ) )
                        continue;
                memset( respcode_ptr[ i ].tritonrespcode, 0, sizeof( respcode_ptr[ i ].tritonrespcode ) );
                getToken( LineStr, respcode_ptr[ i ].tritonrespcode, '|', 1 );
                for( int j = 0; j < strlen( respcode_ptr[ i ].tritonrespcode ); j++ )
                {
                	 if( respcode_ptr[ i ].tritonrespcode[ j ] == '\n' )
                    {
                            respcode_ptr[ i ].tritonrespcode[ j ] = '\0';
                            break;
                    }
            }
            memset( respcode_ptr[ i ].switchrespcode, 0, sizeof( respcode_ptr[ i ].switchrespcode ) );

            getToken( LineStr, respcode_ptr[ i ].switchrespcode, '|', 2 );
            for( int j = 0; j < strlen( respcode_ptr[ i ].switchrespcode ); j++ )
            {
                    if( respcode_ptr[ i ].switchrespcode[ j ] == '\n' )
                    {
                            respcode_ptr[ i ].switchrespcode[ j ] = '\0';
                            break;
                    }
            }
            trace( "TritonCode[%s] SwitchCode[%s]", respcode_ptr[ i ].tritonrespcode, respcode_ptr[ i ].switchrespcode );
                i++;
        }
        fclose( respcode_fp );
        return 1;
}

int EzTritonStd :: LoadTxnCode( string DeviceTypeId )
{
        FILE *txncode_fp;
        char TxnCodePath[ 100 ], LineStr[ 100 ];
        memset( TxnCodePath, 0, sizeof( TxnCodePath ) );
        sprintf( TxnCodePath, "%s/cfg/atm/tritontemplates/%s_txncode.cfg", getenv( "EZDIR_HOME" ), DeviceTypeId.c_str() );

        txncode_fp = fopen( TxnCodePath, "r" );
        if( txncode_fp == NULL )
        {
                trace(  "Error in Opening File[%s]", TxnCodePath );
                return -1;
        }
        NTxnCode = 0;
        while( !feof( txncode_fp ) )
        {
                memset( LineStr, 0, sizeof( LineStr ) );
                fgets( LineStr, sizeof( LineStr ), txncode_fp );
                if( IsBlankLine( LineStr ) )
                        continue;
                NTxnCode++;
        }

        rewind( txncode_fp );

        trace(  "No. of TxnCodes  = [%d]", NTxnCode );

        txncode_ptr = ( struct TxnCodeMap * ) malloc( sizeof( struct TxnCodeMap ) * NTxnCode );
        memset( txncode_ptr, 0, sizeof( struct TxnCodeMap ) * NTxnCode );
        int i = 0;
        while( !feof( txncode_fp ) )
        {
                memset( LineStr, 0, sizeof( LineStr ) );
                fgets( LineStr, sizeof( LineStr ), txncode_fp );
                if( IsBlankLine( LineStr ) )
                        continue;
                memset( txncode_ptr[ i ].tritoncode, 0, sizeof( txncode_ptr[ i ].tritoncode ) );
                getToken( LineStr, txncode_ptr[ i ].tritoncode, '|', 1 );
                for( int j = 0; j < strlen( txncode_ptr[ i ].tritoncode ); j++ )
                {
                	if( txncode_ptr[ i ].tritoncode[ j ] == '\n' )
                    {
                            txncode_ptr[ i ].tritoncode[ j ] = '\0';
                            break;
                    }
            }
            memset( txncode_ptr[ i ].switchcode, 0, sizeof( txncode_ptr[ i ].switchcode ) );
            getToken( LineStr, txncode_ptr[ i ].switchcode, '|', 2 );
            for( int j = 0; j < strlen( txncode_ptr[ i ].switchcode ); j++ )
            {
                    if( txncode_ptr[ i ].switchcode[ j ] == '\n' )
                    {
                            txncode_ptr[ i ].switchcode[ j ] = '\0';
                            break;
                    }
            }
            memset( txncode_ptr[ i ].templatefile, 0, sizeof( txncode_ptr[ i ].templatefile ) );
            getToken( LineStr, txncode_ptr[ i ].templatefile, '|', 3 );
            for( int j = 0; j < strlen( txncode_ptr[ i ].templatefile ); j++ )
            {
                    if( txncode_ptr[ i ].templatefile[ j ] == '\n' )
                    {
                            txncode_ptr[ i ].templatefile[ j ] = '\0';
                            break;
                    }
            }
            trace( "TritonCode[%s] SwitchCode[%s] templatefile[%s]", txncode_ptr[ i ].tritoncode, txncode_ptr[ i ].switchcode, txncode_ptr[ i ].templatefile );
            i++;
    }
    fclose( txncode_fp );
    return 1;
}

bool EzTritonStd:: IsBlankLine( const char *line_str )
{
	for( int i = 0; i < strlen( line_str ); i++ )
	{
		if( ( line_str[ i ] != ' ' ) && ( line_str[ i ] != '\t' ) && ( line_str[ i ] != '\n' ) )
			return false;
	}
	return true;
}

void EzTritonStd :: ServiceRequest()
{
	char ReadBuf[ BUFFER_SIZE+1 ] ;
	int ret, BufSize;


	while( 1 )
	{
		trace( "Waiting for Message in EzTritonStd Channel" );
		memset( ReadBuf, 0, sizeof( ReadBuf ) );
		if( ReadMessage( ReadBuf, &BufSize ) < 0 )
		{
			trace( "Error in Reading EzTritonDriver Channel" );
			continue;
		}
		trace( "Message Received from Channel[%s]", GetLastSenderChannelName() );
		if( IsPortMessage() )
			DiagnizeAndServeAtmReq( ReadBuf,  strlen( ReadBuf ), GetLastSenderChannelName() );
		else
			DiagnizeAndServeAppReq( ReadBuf,  strlen( ReadBuf ), GetLastSenderChannelName() );
	}
}

int EzTritonStd:: DiagnizeAndServeAtmReq( char * AtmReq, int Size , string DeviceId )
{
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ],PortChannel[ CHANNEL_NAME_SIZE+1 ];
	struct EzDevMsg ConsumerReq, OldDevMsg;
	struct TritonStatusMsg status_rec;
	EzDateTimeUtil dtu;

	char TranCode[7], *p , StatusMonitoringBuf[512], tempStr[ 50 ], TempTxnCode[ 20 ];
	map<string, TxnCodeInfo> :: iterator TxnTableIterator ;
	TxnCodeInfo TInfo ;
	int fldno = 0, retval = 0;
	int RevTraceNo, CheckAmount;

	memset( ChannelName, 0, sizeof( ChannelName ) );
	strcpy( ChannelName, GetLastSenderChannelName() );

	memset( &devmem, 0, sizeof( struct DeviceMemoryTable ) );

	trace( DEBUG_NORMAL, "Reading Memory for DeviceId[ %s ]", DeviceId.c_str() );
	if( ReadDeviceMemory( DeviceId.c_str(), &devmem ) < 0 )
		trace( DEBUG_ERROR, "Unable to Read DeviceMemoryTable DeviceId[ %s ]", DeviceId.c_str() );

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memset( &devinfo, 0, sizeof( struct DeviceTableInfo ) );
	memcpy( &devinfo, devmem.DeviceInfoBuffer, sizeof( struct DeviceTableInfo ) );
	memcpy( &atmbuf, devmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

	if( devinfo.DeviceLogging == 'Y' || devinfo.DeviceLogging == 'y' )
	{
		memset( &devmgrq, 0, sizeof( struct EzDeviceMgrQMsg ) );
		PackDeviceLogMsg( devinfo.AcquirerInst, devinfo.DeviceLogicalGroupId, DeviceId.c_str(), AtmReq, MSG_FROM_DEVICE, &devmgrq );
		trace( DEBUG_NORMAL, "Logging the Message from Device[ %s ] ", DeviceId.c_str() );

		if( PostDevMgrMsg( devmgrq, DeviceId.c_str() ) < 0 )
			trace( DEBUG_ERROR, "Failed in PostDevMgrMsg" );
	}

	memset( &ConsumerReq, 0, sizeof( struct EzDevMsg ) );
	strcpy( ConsumerReq.OrgPort, DeviceId.c_str() );
	strcpy( ConsumerReq.SrcPort, DeviceId.c_str() );

	memset( &OldDevMsg, 0, sizeof( struct EzDevMsg ) );
	memcpy( &OldDevMsg, atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

	ConsumerReq.MsgType = EZLINK_TXN_TxnRequest;
    ConsumerReq.OrgMsgType = EZLINK_TXN_TxnRequest;

  	strcpy( ConsumerReq.TerminalLocation , devinfo.DeviceLocation );

	ConsumerReq.MerchantType = devinfo.DeviceGrpVal;
	ConsumerReq.TranDate  = ConsumerReq.LocalDate = ConsumerReq.CaptureDate = dtu.getSysDate();
    ConsumerReq.TranTime  = ConsumerReq.LocalTime = ConsumerReq.CaptureTime = dtu.getSysTime();
    strcpy( ConsumerReq.DeviceSubType, devinfo.DeviceTypeId );
	strcpy( ConsumerReq.AcqBranchCode, devinfo.AcquirerBranchCode );
	strcpy( ConsumerReq.AcquirerInst, devinfo.AcquirerInst );
	ConsumerReq.AcqCurrencyCode = 356;
	ConsumerReq.RespCode = 0;

	//Terminal ID
	getToken( AtmReq, ConsumerReq.TerminalId, 0x1c, ++fldno );
	trace( DEBUG_NORMAL, "<IN>[TerminalId][%s]", ConsumerReq.TerminalId );

	//Transaction Code
	memset( TranCode, 0, sizeof( TranCode ) );
	getToken( AtmReq, TranCode, 0x1c, ++fldno );
	trace( DEBUG_NORMAL, "<IN>[TxnCode][%s]", TranCode );

	if( !strcmp( TranCode, "50" ) || !strcmp( TranCode, "51" ) )
	{
		trace( DEBUG_NORMAL, "Host Download Received from ATM[%s]", ConsumerReq.TerminalId );
		composeHostTotalResponse( AtmReq, DeviceId );
		return 0;
	}

	if ( atoi( TranCode ) != 60 )
	{
		if ( ( atoi( TranCode ) != 29 ) && ( atoi( TranCode ) != 99 ) )
		{
			memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
			GetSwitchTxnCode( TranCode, TempTxnCode );
			ConsumerReq.TxnCode = atoi( TempTxnCode );
			trace( DEBUG_NORMAL, "Translating Triton TxnCode [%s] to [%d]", TranCode, ConsumerReq.TxnCode );
		}

		//Sequence Number
		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq, tempStr, 0x1c, ++fldno );
		ConsumerReq.TraceNo = atoi( tempStr );
		trace( DEBUG_NORMAL, "<IN>[SeqNo][%d]", ConsumerReq.TraceNo );

		//Track2
		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq, tempStr, 0x1c, ++fldno );
		strcpy( ConsumerReq.Track2, tempStr );
		trace( DEBUG_NORMAL, "<IN>[Track2][%s]", ConsumerReq.Track2 );
		for( int i = 0; i < strlen( ConsumerReq.Track2 ); i++ )
		{
			if( ConsumerReq.Track2[ i ] == '=' )
				break;
			else
				ConsumerReq.chn[ i ] = ConsumerReq.Track2[ i ];
		}

		trace( DEBUG_NORMAL, "<IN>[CHN][%s]", ConsumerReq.chn );

		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq, tempStr, 0x1c, ++fldno );
		trace( DEBUG_NORMAL, "<IN>[Amount1][%s]", tempStr );
		//Amount 1
		if ( !strcmp( TranCode, "11" ) || !strcmp( TranCode, "12" ) || !strcmp( TranCode, "29" ) )
		{
			strncpy( ConsumerReq.Amount, "0000", 4 );
			strcpy( ConsumerReq.Amount + 4, tempStr );
		}

		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq, tempStr, 0x1c, ++fldno );
		trace( DEBUG_NORMAL, "<IN>[Amount2][%s]", tempStr );
		if ( !strcmp( TranCode, "29" ) )
		{
			RevTraceNo = ConsumerReq.TraceNo;
			trace( DEBUG_NORMAL, "Reversal Msg TraceNo--RevTraceNo[%d]", RevTraceNo ); //NCBL-12/11/08
			atmbuf.CurrentState = REVERSAL;

			memset( &ConsumerReq, 0, sizeof( struct EzDevMsg ) );
			memcpy( &ConsumerReq, &OldDevMsg, sizeof( struct EzDevMsg ) );

			ConsumerReq.OrgTraceNo = ConsumerReq.TraceNo;
			ConsumerReq.TraceNo = RevTraceNo;
			trace( DEBUG_NORMAL, "ConsumerReq.Amount[%s], ConsumerReq.OrgTraceNo[%d], ConsumerReq.TraceNo[%d]", ConsumerReq.Amount, ConsumerReq.OrgTraceNo, ConsumerReq.TraceNo );

			//Actual Dispensed Amount
			memset( tempStr, 0, sizeof( tempStr ) );
			getToken( AtmReq, tempStr, 0x1c, ++fldno );
			trace( DEBUG_NORMAL, "<IN>[Amount3][%s]", tempStr );

			memset( ConsumerReq.DispAmount, 0, sizeof( ConsumerReq.DispAmount ) );
			strcpy( ConsumerReq.DispAmount, tempStr );

			CheckAmount = ( atoi( ConsumerReq.DispAmount ) / 100 );
			memset( ConsumerReq.DispAmount, 0, sizeof( ConsumerReq.DispAmount ) );
			sprintf( ConsumerReq.DispAmount, "%d.00", CheckAmount );

			ConsumerReq.MsgType = EZLINK_TXN_ReversalAdviceRequest ;
			if( atoi( ConsumerReq.DispAmount ) == 0 )
			{
				ConsumerReq.RespCode = EZLINK_RC_UnableDispense ;
				trace( DEBUG_NORMAL, "Making as Full Reversal RespCode[%03d]\n", ConsumerReq.RespCode );
			}
			else
			{
				ConsumerReq.RespCode = EZLINK_RC_PartialDispense ;
				trace( DEBUG_NORMAL, "Making as Partial Reversal RespCode[%03d]\n", ConsumerReq.RespCode );
			}
		}
		else
		{
			trace( DEBUG_NORMAL, "Setting Response Flag for DeviceId[%s] as No", DeviceId.c_str() );
			atmbuf.MsgCoOrdinationNo = 'N';// using MsgCoOrdinationNo as a Response Flag

			// PIN Block
			getToken( AtmReq, ConsumerReq.PINBlock, 0x1c, ++fldno );
			trace( DEBUG_NORMAL, "<IN>[PinBlock][%s]", ConsumerReq.PINBlock );
			//Miscellaneous 1
			++fldno;
			//Miscellaneous 2
			++fldno;
		}
	}

	//Status Monitoring Field
	memset( StatusMonitoringBuf, 0, sizeof( StatusMonitoringBuf ) );
	getToken( AtmReq, StatusMonitoringBuf, 0x1c, ++fldno );
	trace( DEBUG_NORMAL, "<IN>[Status][%s]", StatusMonitoringBuf );
	memset( &status_rec, 0, sizeof( struct TritonStatusMsg ) );
	ServeStatusMonitoring( StatusMonitoringBuf, DeviceId, 0, 0, 0, 0, &status_rec );
	/// send to DeviceMgr

	trace( DEBUG_NORMAL, "After Serve Status Monitoring TranCode[%s]", TranCode );

	if ( atoi( TranCode ) == 60 )
	{
		DownloadKeyDetails( ConsumerReq, DeviceId );
		return 0;
	}

	else if ( !strcmp( TranCode, "61" ) || !strcmp( TranCode, "62" ) || !strcmp( TranCode, "65" )  || !strcmp( TranCode, "71" ) || !strcmp( TranCode, "72" ) || !strcmp( TranCode, "75" ) )
	{
		//Miscellaneous X
		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq, tempStr, 0x1c, ++fldno );
		strcpy( ConsumerReq.Amount, tempStr + 1 );
		trace( DEBUG_NORMAL, "<IN>[Amount][%s]", ConsumerReq.Amount );
	}
	else if ( !strcmp( TranCode, "99" ) )
	{
		//Miscellaneous X->Extended Transaction Code for MiniStatement
		memset( TranCode, 0, sizeof( TranCode ) );
		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq , tempStr, 0x1c, ++fldno );
		strncpy( TranCode, tempStr + 1, 6 );
		trace( DEBUG_NORMAL, "<IN>[Ext.TxnCode][%s]", TranCode );
		memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
		GetSwitchTxnCode( TranCode, TempTxnCode );
		ConsumerReq.TxnCode =  atoi( TempTxnCode );
		trace( DEBUG_NORMAL, "Translating Triton TxnCode [%s] to [%d]", TranCode, ConsumerReq.TxnCode );
	}
	else if( !strcmp( TranCode, "01" ) )
	{
		//Miscellaneous X
		trace( DEBUG_NORMAL, "Inside Pin Change" );
		trace( DEBUG_NORMAL, "AtmReq=[%s]", AtmReq );
		memset( tempStr, 0, sizeof( tempStr ) );
		getToken( AtmReq, tempStr, '@', 2 );
		trace( DEBUG_NORMAL, "tempStr[%s]", tempStr );
		strncpy( ConsumerReq.NewPINBlock, tempStr, 16 );
		trace( DEBUG_NORMAL, "<IN>[NewPinBlock][%s]", ConsumerReq.NewPINBlock );
	}

	if( !strcmp( TranCode, "29" ) )
	{
		memset( &OldDevMsg, 0, sizeof( struct EzDevMsg ) );
		memcpy( &OldDevMsg, &ConsumerReq, sizeof( struct EzDevMsg ) );

		OldDevMsg.MsgType = EZLINK_TXN_ReversalAdviceResponse ;
		OldDevMsg.RespCode = EZLINK_RC_Approved ;
		trace( DEBUG_NORMAL, "Sending Reversal Response Msg: Msgtype[ %04d ], TraceNo[%04d], RespCode[%03d]", OldDevMsg.MsgType, OldDevMsg.TraceNo, OldDevMsg.RespCode );
		BuildAndPostTranResponseMsg( OldDevMsg, DeviceId );
	}


	if( !strcmp( TranCode, "29" ) )
	{
		trace( DEBUG_NORMAL, "RevTraceNo[%d] ConsumerReq.TraceNo[%d]", RevTraceNo, ConsumerReq.TraceNo ); //NCBL-12/11/08
		if( RevTraceNo != ConsumerReq.OrgTraceNo ) //NCBL-12/11/08
		{
			trace( DEBUG_NORMAL, "Reversal TraceNo != OrigTraceNo....Dropping Reversal Message for DeviceId[%s]", DeviceId.c_str() ); //NCBL-12/11/08
			return 0; //NCBL-12/11/08
		}

		if( OldDevMsg.RespCode != 0 )
		{
			trace( DEBUG_NORMAL, "Dropping Reversal Message for Bad Response for DeviceId[%s]", DeviceId.c_str() );
			return 0;
		}

		if( atmbuf.MsgCoOrdinationNo == 'Y' ) //using MsgCoOrdinationNo as a Response Flag
		{
			trace( DEBUG_NORMAL, "Dropping Reversal Message for DeviceId[%s]", DeviceId.c_str() );
			return 0;
		}
	}

	if ( ( ( ( atoi( TranCode ) == 61 ) ||
	     ( atoi( TranCode ) == 62 ) ||
	     ( atoi( TranCode ) == 65 ) ||
	     ( atoi( TranCode ) == 11 ) ||
	     ( atoi( TranCode ) == 12 ) ||
	     ( atoi( TranCode ) == 15 ) ) ) )
	{
		trace( DEBUG_NORMAL, "Withdrawal Transaction...Checking Available Cash");
		if( ( IsDisableFullReversal( DeviceId.c_str() ) ) || ( IsDisablePartialReversal( DeviceId.c_str() ) ) )
		{
			trace( DEBUG_NORMAL, "Checking Cash..for disabling Reversal for ATM[%d]", DeviceId.c_str() );
			retval = CashCheck( ConsumerReq.Amount, &status_rec );

			if( retval == -1 )
			{
				if( IsDisableFullReversal( DeviceId.c_str() ) )
				{
					trace( DEBUG_NORMAL, "No Cash in ATM[%s] to Dispense", DeviceId.c_str() );
					ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
					ConsumerReq.RespCode= 107;
					BuildAndPostTranResponseMsg( ConsumerReq, DeviceId );
					return 0;
				}
			}
			else if ( retval == -2 )
			{
				if( IsDisablePartialReversal( DeviceId.c_str() ) )
				{
					trace( DEBUG_NORMAL, "Not Enough Cash in ATM[%s] to Dispense", DeviceId.c_str() );
					ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
					ConsumerReq.RespCode= 108;
					BuildAndPostTranResponseMsg( ConsumerReq, DeviceId );
					return 0;
				}
			}
		}

		CheckAmount = ( atoi( ConsumerReq.Amount ) / 100 );
		memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
		sprintf( ConsumerReq.Amount, "%d.00", CheckAmount );
	}
	
	strcpy( ConsumerReq.SecurityId, "123456" );
	memset( atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
	memcpy( atmbuf.DevMsg, (char*)&ConsumerReq, sizeof( struct EzDevMsg ) );
	atmbuf.CurrentState = TRANSACTION;

	if( PostTxnMsg( &ConsumerReq, DeviceId.c_str() ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
		return -1;
	}
	return 0;
}

int EzTritonStd:: DiagnizeAndServeAppReq( char *ReadBuf, int BufSize, string DeviceId )
{
	struct EzTxnMsg AppReq;
	struct EzDevMsg DevMsg;

	trace( "Message from Application Modules" );
	memset( &AppReq, 0, sizeof( struct EzTxnMsg ) );
	memcpy( &AppReq, ReadBuf, sizeof( struct EzTxnMsg ) );

	memset( &DevMsg, 0, sizeof( struct EzDevMsg )  );
	trace( DEBUG_NORMAL, "Transforming the Transaction Message into Device Message" );
	trace( DEBUG_NORMAL, "MsgType[ %04d ] TxnCode[ %06d ] TraceNo[ %04d ] RespCode[ %03d ] Chn[ %s ] Amount[ %s ] ", AppReq.MsgType, AppReq.TxnCode, AppReq.TraceNo, AppReq.RespCode, AppReq.chn, AppReq.Amount );
	if( TransformINboundMsg( &DevMsg, &AppReq ) < 0 )
		trace( DEBUG_ERROR, "Failed in TransformINboundMsg" );

	trace( DEBUG_NORMAL, "MsgType[ %04d ] TxnCode[ %06d ] TraceNo[ %04d ] RespCode[ %03d ] Chn[ %s ] Amount[ %s ] ", DevMsg.MsgType, DevMsg.TxnCode, DevMsg.TraceNo, DevMsg.RespCode, DevMsg.chn, DevMsg.Amount );

	switch( DevMsg.MsgType )
	{
	     case EZLINK_TXN_TxnResponse:
	     case EZLINK_TXN_ReversalAdviceResponse:
	    	 BuildAndPostTranResponseMsg( DevMsg, DeviceId );
	         break;
	     default:
	    	 trace( "Unsupported Application message to ATM[%d]", DevMsg.MsgType );
	         break;
	}
	return 0;
}

int EzTritonStd:: BuildAndPostTranResponseMsg( struct EzDevMsg DevMsg,  string DeviceId )
{
	char TranRspMsg[1024], sRspCode[4], sAuthNumber[9], sAmount[9], tempStr[ 50 ], PortChannel[ CHANNEL_NAME_SIZE+1 ];
	string DevLogGrpId ;
	int len ;
	char crcmsg[5], TranCode[ 7 ], TempTxnCode[ 20 ], TempRespCode[ 20 ];
	unsigned int crc;

	map<string, TxnCodeInfo > :: iterator TxnTableIterator ;
	map<int, int> :: iterator RspTableIterator ;
	TxnCodeInfo TInfo ;
	char TemplateFile[255], PrinterData[1024], TemTxnCode[ 20 ], TritonTxnCode[ 20 ], TritonRespCode[ 20 ];

	memset( TemplateFile, 0, sizeof( TemplateFile ) );
	if ( DevMsg.MsgType != EZLINK_TXN_ReversalAdviceResponse  )//DEVICE_REVERSAL_RESPONSE
	{
		//Multi Block Indicator
		trace( "<OUT>[Multi-Block-Indicator][0]");
		strcpy( TranRspMsg, "0" );
		strcat( TranRspMsg, "\x1c" );
	}

	if ( DevMsg.MsgType != EZLINK_TXN_ReversalAdviceResponse  )//DEVICE_REVERSAL_RESPONSE
	{
		//Terminal ID
		trace( "<OUT>[TerminalId][%s]", DevMsg.TerminalId );
		sprintf( TranRspMsg + 2, "%-15s", DevMsg.TerminalId );
		strcat( TranRspMsg, "\x1c" );
	}
	else
	{
		trace( "<OUT>[TerminalId][%s]", DevMsg.TerminalId );
		sprintf( TranRspMsg , "%-15s", DevMsg.TerminalId );
		strcat( TranRspMsg, "\x1c" );
	}

	if ( DevMsg.MsgType == EZLINK_TXN_ReversalAdviceResponse  )//DEVICE_REVERSAL_RESPONSE
	{
		trace( "<OUT>[TxnCode][%s]", "29" );
		strcat( TranRspMsg, "29" );
		strcat( TranRspMsg, "\x1c" );
		memset( TranCode, 0, sizeof( TranCode ) );
		strcpy( TranCode, "29" );
	}
	else
	{
		//Transaction Code
		if( DevMsg.TxnCode / 10000 == 1 )
		{
			trace( "Setting Response Flag as True for ATMId[%s]", DeviceId.c_str() );
			atmbuf.MsgCoOrdinationNo == 'Y';//using MsgCoOrdinationNo as a Response Flag
		}
		memset( TempTxnCode, 0, sizeof( TempTxnCode ) );
		sprintf( TempTxnCode, "%06d", DevMsg.TxnCode );
		memset( TranCode, 0, sizeof( TranCode ) );
		memset( TemplateFile, 0, sizeof( TemplateFile ) );
		GetTritonTxnCode( TempTxnCode, TranCode, TemplateFile );
		trace( "TxnCode for Triton is [%s]", TranCode  );
		if( !strncmp( TranCode, "07", 2 ) )
		{
			trace( "<OUT>[TxnCode][%s]", "99" );
			strcat( TranRspMsg, "99" );
			strcat( TranRspMsg, "\x1c" );
		}
		else
		{
			trace( "<OUT>[TxnCode][%s]", TranCode );
			strcat( TranRspMsg, TranCode );
			strcat( TranRspMsg, "\x1c" );
		}
	}

	//Sequence No
	trace( "<OUT>[SeqNo][%d]", DevMsg.TraceNo );
	memset( tempStr, 0, sizeof( tempStr ) );
	sprintf( tempStr, "%04d", DevMsg.TraceNo );
	strcat( TranRspMsg, tempStr );
	strcat( TranRspMsg, "\x1c" );

	//Response Code
	memset( TempRespCode, 0, sizeof( TempRespCode ) );
	sprintf( TempRespCode, "%03d", DevMsg.RespCode );
	memset( TritonRespCode, 0, sizeof( TritonRespCode ) );
	GetTritonRespCode( TempRespCode, TritonRespCode );
	trace( "<OUT>[RespCode][%s]", TritonRespCode );
	strcat( TranRspMsg, TritonRespCode );
	strcat( TranRspMsg, "\x1c" );
	if( strcmp( TranCode, "29" ) )
	{
		//Authorization Number
		sprintf( sAuthNumber, "%08d", atoi( TritonRespCode ) );
		trace( "<OUT>[AuthNumber][%s]", sAuthNumber );
		strcat( TranRspMsg, sAuthNumber );
		strcat( TranRspMsg, "\x1c" );
	}
	trace( "TranCode[%s]", TranCode );
	if( strcmp( TranCode, "29" ) )
	{
		struct tm *timenow;
		time_t t = 0;
		t = time( &t );
		timenow = localtime( &t );

		//Transaction Date
		memset( tempStr, 0, sizeof( tempStr ) );
		sprintf( tempStr, "%02d%02d%02d", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year % 100 );
		trace( "<OUT>[TranDate][%s]", tempStr );
		strcat( TranRspMsg, tempStr );
		strcat( TranRspMsg, "\x1c" );

		//Transaction Time
		memset( tempStr, 0, sizeof( tempStr ) );
		sprintf( tempStr, "%02d%02d%02d", timenow->tm_hour, timenow->tm_min, timenow->tm_sec );
		trace( "<OUT>[TranTime][%s]", tempStr );
		strcat( TranRspMsg, tempStr );
		strcat( TranRspMsg, "\x1c" );

		//Business Date
		memset( tempStr, 0, sizeof( tempStr ) );
		sprintf( tempStr, "%02d%02d%02d", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year % 100 );
		trace("<OUT>[BusDate][%s]", tempStr );
		strcat( TranRspMsg, tempStr  );
		strcat( TranRspMsg, "\x1c" );

		//Amount 1
		memset( sAmount, 0, sizeof( sAmount ) );
		if ( ( ( ( atoi( TranCode ) == 11 ) ||
		     ( atoi( TranCode ) == 12 ) ||
		     ( atoi( TranCode ) == 15 ) ||
		     ( atoi( TranCode ) == 31 ) ||
		     ( atoi( TranCode ) == 32 ) ||
		     ( atoi( TranCode ) == 35 ) ) ) && ( DevMsg.RespCode == 0 ) )
		{
			char *p = DevMsg.AvailBalance;
			while( *p == '0' )
				p++;
			strncpy( sAmount, p, 8 ) ;
		}
		else
			memset( sAmount, ' ', 8 );
		trace( "<OUT>[Amount1][%s]", sAmount );
		strcat( TranRspMsg, sAmount );
		strcat( TranRspMsg, "\x1c" );

		//Amount 2
		memset( sAmount, '0', 8 );
		trace( "<OUT>[Amount2][%s]", sAmount );
		strcat( TranRspMsg, sAmount );
		strcat( TranRspMsg, "\x1c" );


		strcat( TranRspMsg, "\x1c" );
		//Miscellaneous 2
		strcat( TranRspMsg, "\x1c" );
	}

	//Miscellaneous X
	if( !strncmp( TranCode, "07", 2 ) )
	{
		//Extended Transaction Code
		strcat( TranRspMsg, "l" );
		strcat( TranRspMsg, TranCode );
		trace(  "<OUT>[Ext-TxnCode][l%s]", TranCode );
		strcat( TranRspMsg, "\x1c" );

		//Mini Statement Data
		strcat( TranRspMsg, "uj00" );
		memset( PrinterData, 0, sizeof( PrinterData ) );
		BuildPrinterData( TemplateFile, PrinterData, DevMsg );
		trace(  "<OUT>[Statement-Data][%s]", PrinterData );
		strcat( TranRspMsg, PrinterData );
		strcat( TranRspMsg, "\x1c" );
	}
	//Extended Amount Field
	if ( ( ( ( atoi( TranCode ) == 61 ) ||
	     ( atoi( TranCode ) == 62 ) ||
	     ( atoi( TranCode ) == 65 ) ||
	     ( atoi( TranCode ) == 81 ) ||
	     ( atoi( TranCode ) == 82 ) ||
	     ( atoi( TranCode ) == 85 ) ) ) && ( DevMsg.RespCode == 0 ) )
	{
		trace( "<OUT>[Ext-Amount][e%s]", DevMsg.AvailBalance );
		strcat( TranRspMsg, "e");
		char TempAmount[ 20 ];
		memset( TempAmount, 0, sizeof( TempAmount ) );
		if( strlen( DevMsg.AvailBalance ) < 12 )
		{
			memset( TempAmount, '0', 12 - strlen( DevMsg.AvailBalance ) );
			strcat( TempAmount, DevMsg.AvailBalance );
		}
		else
			strncpy( TempAmount, DevMsg.AvailBalance, 12 );
		strcat( TranRspMsg, TempAmount );
		//trace( "<OUT>[FromAccount][&%-28s]", DevMsg.FromAccount );
		//strcat( TranRspMsg, "\x1c" );
		//strcat( TranRspMsg, "&");
		//memset( tempStr, 0, sizeof( tempStr ) );
		//sprintf( tempStr, "%-28s", DevMsg.FromAccount );
		//strcat( TranRspMsg, tempStr );
	}

	strcat( TranRspMsg, "\x1c" );
	//CRC
	crc = crc16(( unsigned char * ) TranRspMsg, strlen( TranRspMsg ) + 7 );
	sprintf( crcmsg, "%04X", crc );
	strcat( TranRspMsg, "ub" );
	strcat( TranRspMsg, crcmsg );
	strcat( TranRspMsg, "\x1c" );

	atmbuf.CurrentState = TRANSACTION;

	memset( atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
	memcpy( atmbuf.DevMsg, ( char * )&DevMsg, sizeof( struct EzDevMsg ) );

	if( PostAtmMsg( DevMsg.DestPort, TranRspMsg ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}

	return 1;
}

int EzTritonStd:: DownloadKeyDetails( struct EzDevMsg DevMsg, string DeviceId )
{
	char DeviceCommKey_TMK[ COMMKEY_SIZE + 1 ];
	unsigned char lCommKey[ COMMKEY_SIZE + 1 ];
	char DecBuf[32] , lKey[ COMMKEY_SIZE + 1 ];
	char AtmBuf[1024];
	char crcmsg[5];
	unsigned int crc;

	//Terminal ID
	memset( AtmBuf, 0, sizeof( AtmBuf ) );
	strcpy( AtmBuf, DevMsg.TerminalId );
	strcat( AtmBuf, "\x1c" );
	//Transaction Code
	strcat( AtmBuf, "60" );
	strcat( AtmBuf, "\x1c" );
	//Field ID Code for Key
	strcat( AtmBuf, "~" );

	memset( DeviceCommKey_TMK, 0, sizeof( DeviceCommKey_TMK ) );
	if( GenDeviceCommKey( devinfo.AcquirerInst, DeviceId.c_str(), DeviceCommKey_TMK ) < 0 )
	{
		trace( DEBUG_ERROR,"Unable to  generate Comm Key for the Device<%s_%s>", devinfo.AcquirerInst, DeviceId.c_str() );
		return -1;
	}

	//New Generated Key
	trace ( DEBUG_NORMAL, "Obtained comm key [%s]", DeviceCommKey_TMK );
	strcat( AtmBuf, DeviceCommKey_TMK );
	strcat( AtmBuf, "\x1c" );

	//Field ID Code for Maximum Allowed Surchage Amount
	strcat( AtmBuf, "!" );
	//Surcharge Amount
	strcat( AtmBuf, "00000000" );
	strcat( AtmBuf, "\x1c" );
	//MiscX
	strcat( AtmBuf, "\x1c" );
	//CRC
	crc = crc16(( unsigned char * ) AtmBuf, strlen( AtmBuf ) + 7 );
	sprintf( crcmsg, "%04X", crc );
	strcat( AtmBuf, "ub" );
	strcat( AtmBuf, crcmsg );
	strcat( AtmBuf, "\x1c" );

	atmbuf.CurrentState = DOWNLOAD ;

	if( PostAtmMsg( DeviceId.c_str(), AtmBuf ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}


int EzTritonStd:: BuildPrinterData( const char * PrinterTemplateFile, char * PrinterData , struct EzDevMsg DevMsg )
{
	char PTFilePath[255], RspCode[4], Txn[24], sbal[25], temp[15], decimal[3];
	time_t tme ;
	FILE *fptr;
	struct tm * t;
	char local_date[10], local_time[10], tempStr[ 20 ], LineBuffer[ 200 ], ColStr[ 100 ];
	int NColumns, bal;
	time( &tme );
	t= localtime( &tme );

	sprintf( local_time, "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec );
	sprintf( local_date, "%02d/%02d/%04d", t->tm_mday, t->tm_mon+1, t->tm_year+1900 );
	sprintf( RspCode, "%03d", DevMsg.RespCode );

	if ( ( DevMsg.TxnCode /10000 ) == 1 )
		strcpy( Txn, "Cash Withdrawl" );
	else if ( ( DevMsg.TxnCode /10000 ) == 31 )
		strcpy( Txn, "Balance Enquiry" );
	else if ( ( DevMsg.TxnCode /10000 ) == 38 )
		strcpy( Txn, "Statement Enquiry" );
	else if ( ( DevMsg.TxnCode /10000 ) == 21 )
		strcpy( Txn, "Deposit" );


	trace( "DevMsg.RsvFld1 = [%s]", DevMsg.RsvFld1 );

	memset ( PTFilePath, 0, sizeof( PTFilePath ) );
	sprintf( PTFilePath, "%s/cfg/atm/tritontemplates/%s", getenv( "EZDIR_HOME" ), PrinterTemplateFile );
	fptr = fopen( PTFilePath, "r" );
        if( fptr == NULL )
        {
                trace( "Error in opening file <%s>", PTFilePath );
                return -1;
        }

        while( !feof( fptr ) )
        {
                memset( LineBuffer, 0, sizeof( LineBuffer ) );
                fgets( LineBuffer, sizeof( LineBuffer ), fptr );

                if( IsBlankLine( LineBuffer ) )
                        continue;

                NColumns = GetNColumns( LineBuffer );
                for( int i = 0; i < NColumns; i++ )
                {
                        memset( ColStr, 0, sizeof( ColStr ) );
                        GetString( LineBuffer, ColStr, i + 1 );
                        //trace( "ColStr=[%s]", ColStr );
			if ( !strcasecmp( ColStr, "$LF" ) )
				strcat( PrinterData, "\x0a" );
			else if ( !strcasecmp( ColStr, "$SO" ) )
				strcat( PrinterData, "\x0e" );
			else if ( !strcasecmp( ColStr, "$TAB" ) )
				strcat( PrinterData, "\x09" );
			else if ( !strcasecmp( ColStr, "$SPACE" ) )
				strcat( PrinterData, " " );
			else if ( !strcasecmp( ColStr, "$ESC" ) )
				strcat( PrinterData, "\x1b" );
			else if ( !strcasecmp( ColStr, "$FF" ) )
				strcat( PrinterData, "\x0c" );
			else if ( !strcasecmp( ColStr, "$CR" ) )
				strcat( PrinterData, "\x0d" );
			else if ( !strcasecmp( ColStr, "$VT" ) )
				strcat( PrinterData, "\x0b" );
			else if ( !strcasecmp( ColStr, "$TIME" ) )
				strcat( PrinterData, local_time );
			else if ( !strcasecmp( ColStr, "$DATE" ) )
				strcat( PrinterData, local_date );
			else if ( !strcasecmp( ColStr, "$CHN" ) )
				strcat( PrinterData, DevMsg.chn );
			else if ( !strcasecmp( ColStr, "$AMOUNT" ) )
				strcat( PrinterData, DevMsg.Amount );
			else if ( !strcasecmp( ColStr, "$TRACE" ) )
			{
				memset( tempStr, 0, sizeof( tempStr ) );
				sprintf( tempStr, "%04d", DevMsg.TraceNo );
				strcat( PrinterData, tempStr );
			}
			else if ( !strcasecmp( ColStr, "$RSP_CODE" ) )
				strcat( PrinterData, RspCode );
			else if ( !strcasecmp( ColStr, "$TRANSACTION" ) )
				strcat( PrinterData, Txn );
			else if ( !strcasecmp( ColStr, "$AVAILABLE_BALANCE" ) )
			{
	                        memset( temp, 0, sizeof( temp ) );
                                memset( decimal, 0, sizeof( decimal ) );
                                trace( "Bal[%s]", DevMsg.AvailBalance);
                                strncpy( temp, DevMsg.AvailBalance, strlen( DevMsg.AvailBalance ) - 2 );
                                strncpy( decimal, DevMsg.AvailBalance + strlen( DevMsg.AvailBalance ) - 2, 2 );
                                bal = atoi( temp );
                                memset( temp, 0, sizeof( temp ) );
                                sprintf( temp, "%d", bal);
                                trace( "Amount[%s] Decimal[%s]", temp, decimal );
                                memset( sbal, 0, sizeof( sbal ));
                                sprintf( sbal, "%s.%s", temp, decimal);
                                trace("Balance[%s]", sbal);
                                strcat( PrinterData, sbal );
	
			}
			else if ( !strcasecmp( ColStr, "$LEDGER_BALANCE" ) )
			{
				int BalOffset = 0;
				for( BalOffset = 0; BalOffset < strlen( DevMsg.LedgerBalance ); BalOffset++ )
				{
					if( DevMsg.LedgerBalance[ BalOffset ] != '0' )
						break;
				}
				strcat( PrinterData, DevMsg.LedgerBalance  + BalOffset );
			}
			else if ( !strcasecmp( ColStr, "$DEVICE_ID" ) )
				strcat( PrinterData, DevMsg.TerminalId );
			else if ( !strcasecmp( ColStr, "$DEVICE_LOCATION" ) )
				strcat( PrinterData, DevMsg.TerminalLocation );
			else if ( !strcasecmp( ColStr, "$FROM_ACCT" ) )
				strcat( PrinterData, DevMsg.FromAccount );
			else if ( !strcasecmp( ColStr, "$TO_ACCT" ) )
				strcat( PrinterData, DevMsg.ToAccount );
			else if ( !strcasecmp( ColStr, "$STMT_1" ) )
                                strncat( PrinterData, DevMsg.RsvFld1, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_2" ) )
                                strncat( PrinterData, DevMsg.RsvFld1+40, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_3" ) )
                                strncat( PrinterData, DevMsg.RsvFld1+80, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_4" ) )
                                strncat( PrinterData, DevMsg.RsvFld1+120, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_5" ) )
                                strncat( PrinterData, DevMsg.RsvFld1+160, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_6" ) )
                                strncat( PrinterData, DevMsg.RsvFld2, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_7" ) )
                                strncat( PrinterData, DevMsg.RsvFld2+40, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_8" ) )
                                strncat( PrinterData, DevMsg.RsvFld2+80, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_9" ) )
                                strncat( PrinterData, DevMsg.RsvFld2+120, 40 );
                        else if ( !strcasecmp( ColStr, "$STMT_10" ) )
                                strncat( PrinterData, DevMsg.RsvFld2+160, 40 );
			else
				strcat( PrinterData, ColStr );
		}
	}
	strcat( PrinterData, "\x0c" );
	hex_dump( ( unsigned char * ) PrinterData, strlen( PrinterData ) );
	fclose( fptr );
	return 0;
}


int EzTritonStd:: ServeStatusMonitoring( char *AtmReq , string DeviceId, int CassADisp, int CassBDisp, int CassCDisp, int CassDDisp, struct TritonStatusMsg *status_rec )
{
	int i,Temp, retval;
	char Buf[11];
	char StatusBuf[ 200 ];
	memset( StatusBuf, 0, sizeof( StatusBuf ) );
	strcpy( StatusBuf, AtmReq );

	double CassACash, CassBCash, CassCCash, CassDCash, TotCash;
	int CassAMin, CassBMin, CassCMin, CassDMin;
	FILE *fp;
	char casspath[ 200 ];
	EzDateTimeUtil dtu;

	memset( casspath, 0, sizeof( casspath ) );
	sprintf( casspath, "%s/%s/%s/%s/%s_%s_%s.cfg", getenv( "EZDIR_HOME" ), "cfg", "atm", "tritontemplates", "TRITATM", DeviceId.c_str(), "CassMin" );
	fp = fopen( casspath, "r" );

	if( fp == NULL )
	{
		trace( DEBUG_NORMAL, "Error in Opening File[%s]", casspath );
		memset( casspath, 0, sizeof( casspath ) );
		sprintf( casspath, "%s/%s/%s/%s/%s_%s.cfg", getenv( "EZDIR_HOME" ), "cfg", "atm", "tritontemplates","TRITATM", "CassMin" );
		if( fp == NULL )
		{
			trace( DEBUG_NORMAL, "Error in Opening File[%s]...Setting Default Min Notes as 20...", casspath );
			CassAMin=CassBMin=CassCMin=CassDMin=20;
		}
		else
		{
			fscanf( fp, "%d%d%d%d", &CassAMin, &CassBMin, &CassCMin, &CassDMin );
			fclose( fp );
			trace( DEBUG_NORMAL, "CassAMin[%d] CassBMin[%d] CassCMin[%d] CassDMin[%d]", CassAMin, CassBMin, CassCMin, CassDMin );
		}
	}
	else
	{
		fscanf( fp, "%d%d%d%d", &CassAMin, &CassBMin, &CassCMin, &CassDMin );
		fclose( fp );
		trace( DEBUG_NORMAL, "CassAMin[%d] CassBMin[%d] CassCMin[%d] CassDMin[%d]", CassAMin, CassBMin, CassCMin, CassDMin );
	}

	sprintf( status_rec->StatusDate, "%d", dtu.getSysDate() );
	sprintf( status_rec->StatusTime, "%d", dtu.getSysTime() );

	strncpy( status_rec->PgmVersionNo, AtmReq, 10 );
	trace( DEBUG_NORMAL, "Program Version Number :: [%s]\n" , status_rec->PgmVersionNo );
	AtmReq += 10 ;

	strncpy( status_rec->TabVersionNo, AtmReq, 10 );
	trace( DEBUG_NORMAL, "Table Version Number :: [%s]\n" , status_rec->TabVersionNo );
	AtmReq += 10 ;

	strncpy( status_rec->FirmVersionNo, AtmReq, 10 );
	trace( DEBUG_NORMAL, "Firmware Version Number :: [%s]\n" , status_rec->FirmVersionNo );
	AtmReq += 10 ;

	status_rec->AlarmChestDoor =  *AtmReq;
	switch( status_rec->AlarmChestDoor )
	{
		case '0':
			trace( DEBUG_NORMAL, "Alarm,Chest door Ok");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Alarm,Chest door Opened");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Alarm,Chest door Not installed");
			break;
		default:
			trace( DEBUG_NORMAL, "Alarm,Chest door Not Supported");
	}


	AtmReq ++;//Move to next bit

	status_rec->AlarmTopDoor =  *AtmReq;
	switch( status_rec->AlarmTopDoor )
	{
		case '0':
			trace( DEBUG_NORMAL, "Alarm,Top door Ok");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Alarm,Top door Opened");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Alarm,Top door Not installed");
			break;
		default:
			trace( DEBUG_NORMAL, "Alarm,Top door Not Supported");
	}

	AtmReq ++;//Move to next bit

	status_rec->AlarmSupervisor =  *AtmReq;
	switch( status_rec->AlarmSupervisor )
	{
		case '0':
			trace( DEBUG_NORMAL, "Alarm,Supervisor Inactive");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Alarm,Supervisor Active");
			break;
		default:
			trace( DEBUG_NORMAL, "Alarm,Supervisor Not Supported");
	}

	AtmReq ++;//Move to next bit

	status_rec->RPPaper =  *AtmReq;
	switch( status_rec->RPPaper )
	{
		case '0':
			trace( DEBUG_NORMAL, "Receipt Printer Paper status < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Receipt Printer Paper status < LOW >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Receipt Printer Paper status < OUT >");
			break;
		default:
			trace( DEBUG_NORMAL, "Receipt Printer Paper status < Not Supported >");
	}

	AtmReq ++;

	status_rec->RPRibbon =  *AtmReq;
	switch( status_rec->RPRibbon )
	{
		case '0':
			trace( DEBUG_NORMAL, "Receipt Printer Ribbon status < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Receipt Printer Ribbon status < LOW >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Receipt Printer Ribbon status < OUT >");
			break;
		case 'T':
			trace( DEBUG_NORMAL, "Receipt Printer Ribbon status < THERMAL >");
			break;
		default:
			trace( DEBUG_NORMAL, "Receipt Printer Ribbon status < Not Supported >");
	}
	AtmReq ++;

	status_rec->JPPaper =  *AtmReq;
	switch( status_rec->JPPaper )
	{
		case '0':
			trace( DEBUG_NORMAL, "Journal Printer Paper status < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Journal Printer Paper status < LOW >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Journal Printer Paper status < OUT >");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Journal Printer Paper status < NOT INSTALLED >");
			break;
		default:
			trace( DEBUG_NORMAL, "Journal Printer Paper status < Not Supported >");
	}
	AtmReq ++;

	status_rec->JPRibbon =  *AtmReq;
	switch( status_rec->JPRibbon )
	{
		case '0':
			trace( DEBUG_NORMAL, "Journal Printer Ribbon status < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Journal Printer Ribbon status < LOW >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Journal Printer Ribbon status < OUT >");
			break;
		case 'T':
			trace( DEBUG_NORMAL, "Journal Printer Ribbon status < THERMAL >");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Journal Printer Ribbon status < NOT INSTALLED >");
			break;
		default:
			trace( DEBUG_NORMAL, "Journal Printer Ribbon status < Not Supported >");
	}
	AtmReq ++;

	status_rec->DispNote =  *AtmReq;
	switch( status_rec->DispNote )
	{
		case '0':
			trace( DEBUG_NORMAL, "Note Status,Dispenser < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Note Status,Dispenser  < LOW >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Note Status,Dispenser < OUT >");
			break;
		default:
			trace( DEBUG_NORMAL, "Note Status,Dispenser < Not Supported >");
	}
	AtmReq ++;

	status_rec->RPStatus =  *AtmReq;
	switch( status_rec->RPStatus )
	{
		case '0':
			trace( DEBUG_NORMAL, "Receipt Printer < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Receipt Printer < NEED ATTENTION >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Receipt Printer < OUT OF SERVICE >");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Receipt Printer < NOT INSTALLED >");
			break;
		default:
			trace( DEBUG_NORMAL, "Receipt Printer < Not Supported >");
	}
	AtmReq ++;

	status_rec->JPStatus =  *AtmReq;
	switch( status_rec->JPStatus )
	{
		case '0':
			trace( DEBUG_NORMAL, "Journal Printer < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Journal Printer < NEED ATTENTION >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Journal Printer < OUT OF SERVICE >");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Journal Printer < NOT INSTALLED >");
			break;
		default:
			trace( DEBUG_NORMAL, "Journal Printer < Not Supported >");
	}
	AtmReq ++;

	status_rec->DispStatus =  *AtmReq;
	switch( status_rec->DispStatus )
	{
		case '0':
			trace( DEBUG_NORMAL, "Dispenser Printer < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Dispenser Printer < NEED ATTENTION >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Dispenser Printer < OUT OF SERVICE >");
			break;
		case 'X':
			trace( DEBUG_NORMAL, "Dispenser Printer < NOT INSTALLED >");
			break;
		default:
			trace( DEBUG_NORMAL, "Dispenser Printer < Not Supported >");
	}
	AtmReq ++;

	status_rec->CommSystem =  *AtmReq;
	switch( status_rec->CommSystem )
	{
		case '0':
			trace( DEBUG_NORMAL, "Communications System < OK >");
			break;
		case '1':
			trace( DEBUG_NORMAL, "Communications System < NEED ATTENTION >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Communications System < OUT OF SERVICE >");
			break;
		default:
			trace( DEBUG_NORMAL, "Communications System < Not Supported >");
	}
	AtmReq ++;

	status_rec->CardReader =  *AtmReq;
	switch( status_rec->CardReader )
	{
		case '0':
			trace( DEBUG_NORMAL, "Card Reader < OK >\n" );
			break;
		case '1':
			trace( DEBUG_NORMAL, "Card Reader < NEED ATTENTION >");
			break;
		case '2':
			trace( DEBUG_NORMAL, "Card Reader < OUT OF SERVICE >");
			break;
		default:
			trace( DEBUG_NORMAL, "Card Reader < Not Supported >");
	}
	AtmReq ++;

	//sscanf ((char*) AtmReq, "%03d", &Temp);
	strncpy( status_rec->CardsRetained, AtmReq, 3 );
	trace( DEBUG_NORMAL, "Card Retained [ %s ]",status_rec->CardsRetained);
	AtmReq +=3;

	// Electronic system 2 ASCII char
	AtmReq +=2;

	//sscanf ((char*) AtmReq, "%03d", &Temp);
	strncpy( status_rec->ErrCode, AtmReq, 3 );
	trace( DEBUG_NORMAL, "Current Error Code For Terminal  [ %s ]",status_rec->ErrCode);
	AtmReq +=3;

	// Communcations failures 3 ASCII char
	AtmReq +=3;

	sscanf ((char*) AtmReq, "%02d", &Temp);// 3 char last one is K always
	trace( DEBUG_NORMAL, "Cassette A Denomination  [ %d Unit Note]", Temp*10);
	strncpy( status_rec->CassADenom, AtmReq, 3 );
	AtmReq +=3;

	sscanf ((char*) AtmReq, "%04d", &Temp);
	sprintf( status_rec->CassALoaded, "%d", Temp );
	trace( DEBUG_NORMAL, "Cassette A Loaded  [ %s Notes]",status_rec->CassALoaded);
	AtmReq +=4;

	sprintf( status_rec->CassAMin, "%04d", CassAMin );
	trace( DEBUG_NORMAL, "Cassette A Min  [ %s Notes]", status_rec->CassAMin );


	sscanf ((char*) AtmReq, "%04d", &Temp);
	Temp = Temp + CassADisp;
	sprintf( status_rec->CassADisp, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette A Dispensed  [ %s Notes]", status_rec->CassADisp );
	AtmReq +=4;

	sscanf ((char*) AtmReq, "%03d", &Temp);
	sprintf( status_rec->CassAReject, "%03d", Temp );
	trace( DEBUG_NORMAL, "Cassette A Reject events  [ %s Notes]",status_rec->CassAReject);
	AtmReq +=3;

	Temp = atoi( status_rec->CassALoaded ) - ( atoi( status_rec->CassAReject ) + atoi( status_rec->CassADisp ) );
	sprintf( status_rec->CassANotes, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette A Notes  [ %s Notes]",status_rec->CassANotes);


	if( !strcmp( status_rec->CassADenom, "10K" ) )
		CassACash = atoi( status_rec->CassANotes ) * 100;
	else if( !strcmp( status_rec->CassADenom, "50K" ) )
		CassACash = atoi( status_rec->CassANotes ) * 500;
	else if( !strcmp( status_rec->CassADenom, "100K" ) )
		CassACash = atoi( status_rec->CassANotes ) * 1000;
	else
		CassACash = 0;

	sprintf( status_rec->CassACash, "%lf", CassACash );
	trace( DEBUG_NORMAL, "Cassette A Cash  [ %s Notes]",status_rec->CassACash);

	sscanf ((char*) AtmReq, "%02d", &Temp);// 3 char last one is K always
	trace( DEBUG_NORMAL, "Cassette B Denomination  [ %d Unit Note]", Temp*10);
	strncpy( status_rec->CassBDenom, AtmReq, 3 );
	AtmReq +=3;


	sscanf ((char*) AtmReq, "%04d", &Temp);
	sprintf( status_rec->CassBLoaded, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette B Loaded  [ %s Notes]",status_rec->CassBLoaded);
	AtmReq +=4;

	sprintf( status_rec->CassBMin, "%04d", CassBMin );
	trace( DEBUG_NORMAL, "Cassette B Min  [ %s Notes]", status_rec->CassBMin );


	sscanf ((char*) AtmReq, "%04d", &Temp);
	Temp = Temp + CassBDisp;
	sprintf( status_rec->CassBDisp, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette B Dispensed  [ %s Notes]", status_rec->CassBDisp );
	AtmReq +=4;

	sscanf ((char*) AtmReq, "%03d", &Temp);
	sprintf( status_rec->CassBReject, "%03d", Temp );
	trace( DEBUG_NORMAL, "Cassette B Reject events  [ %s Notes]",status_rec->CassBReject);
	AtmReq +=3;

	Temp = atoi( status_rec->CassBLoaded ) - ( atoi( status_rec->CassBReject ) + atoi( status_rec->CassBDisp ) );
	sprintf( status_rec->CassBNotes, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette B Notes  [ %s Notes]",status_rec->CassBNotes);


	if( !strcmp( status_rec->CassBDenom, "10K" ) )
		CassBCash = atoi( status_rec->CassBNotes ) * 100;
	else if( !strcmp( status_rec->CassBDenom, "50K" ) )
		CassBCash = atoi( status_rec->CassBNotes ) * 500;
	else if( !strcmp( status_rec->CassBDenom, "100K" ) )
		CassBCash = atoi( status_rec->CassBNotes ) * 1000;
	else
		CassBCash = 0;

	sprintf( status_rec->CassBCash, "%lf", CassBCash );
	trace( DEBUG_NORMAL, "Cassette B Cash  [ %s Notes]",status_rec->CassBCash);

	sscanf ((char*) AtmReq, "%02d", &Temp);// 3 char last one is K always
	trace( DEBUG_NORMAL, "Cassette C Denomination  [ %d Unit Note]",Temp*10);
	strncpy( status_rec->CassCDenom, AtmReq, 3 );
	AtmReq +=3;

	sscanf ((char*) AtmReq, "%04d", &Temp);
	sprintf( status_rec->CassCLoaded, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette C Loaded  [ %s Notes]",status_rec->CassCLoaded);
	AtmReq +=4;

	sprintf( status_rec->CassCMin, "%04d", CassCMin );
	trace( DEBUG_NORMAL, "Cassette C Min  [ %s Notes]", status_rec->CassCMin );


	sscanf ((char*) AtmReq, "%04d", &Temp);
	Temp = Temp + CassCDisp;
	sprintf( status_rec->CassCDisp, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette C Dispensed  [ %s Notes]", status_rec->CassCDisp );
	AtmReq +=4;

	sscanf ((char*) AtmReq, "%03d", &Temp);
	sprintf( status_rec->CassCReject, "%03d", Temp );
	trace( DEBUG_NORMAL, "Cassette C Reject events  [ %s Notes]",status_rec->CassCReject);
	AtmReq +=3;

	Temp = atoi( status_rec->CassCLoaded ) - ( atoi( status_rec->CassCReject ) + atoi( status_rec->CassCDisp ) );
	sprintf( status_rec->CassCNotes, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette C Notes  [ %s Notes]",status_rec->CassCNotes);


	if( !strcmp( status_rec->CassCDenom, "10K" ) )
		CassCCash = atoi( status_rec->CassCNotes ) * 100;
	else if( !strcmp( status_rec->CassCDenom, "50K" ) )
		CassCCash = atoi( status_rec->CassCNotes ) * 500;
	else if( !strcmp( status_rec->CassCDenom, "100K" ) )
		CassCCash = atoi( status_rec->CassCNotes ) * 1000;
	else
		CassCCash = 0;

	sprintf( status_rec->CassCCash, "%lf", CassCCash );
	trace( DEBUG_NORMAL, "Cassette C Cash  [ %s Notes]",status_rec->CassCCash);

	sscanf ((char*) AtmReq, "%02d", &Temp);// 3 char last one is K always
	trace( DEBUG_NORMAL, "Cassette D Denomination  [ %d Unit Note]",Temp*10);
	strncpy( status_rec->CassDDenom, AtmReq, 3 );
	AtmReq +=3;

	sscanf ((char*) AtmReq, "%04d", &Temp);
	sprintf( status_rec->CassDLoaded, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette D Loaded  [ %s Notes]",status_rec->CassDLoaded);
	AtmReq +=4;

	sprintf( status_rec->CassDMin, "%04d", CassDMin );
	trace( DEBUG_NORMAL, "Cassette D Min  [ %s Notes]", status_rec->CassDMin );


	sscanf ((char*) AtmReq, "%04d", &Temp);
	Temp = Temp + CassDDisp;
	sprintf( status_rec->CassDDisp, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette D Dispensed  [ %s Notes]", status_rec->CassDDisp );
	AtmReq +=4;

	sscanf ((char*) AtmReq, "%03d", &Temp);
	sprintf( status_rec->CassDReject, "%03d", Temp );
	trace( DEBUG_NORMAL, "Cassette D Reject events  [ %s Notes]",status_rec->CassDReject);
	AtmReq +=3;

	Temp = atoi( status_rec->CassDLoaded ) - ( atoi( status_rec->CassDReject ) + atoi( status_rec->CassDDisp ) );
	sprintf( status_rec->CassDNotes, "%04d", Temp );
	trace( DEBUG_NORMAL, "Cassette D Notes  [ %s Notes]",status_rec->CassDNotes);


	if( !strcmp( status_rec->CassDDenom, "10K" ) )
		CassDCash = atoi( status_rec->CassDNotes ) * 100;
	else if( !strcmp( status_rec->CassDDenom, "50K" ) )
		CassDCash = atoi( status_rec->CassDNotes ) * 500;
	else if( !strcmp( status_rec->CassDDenom, "100K" ) )
		CassDCash = atoi( status_rec->CassDNotes ) * 1000;
	else
		CassDCash = 0;

	sprintf( status_rec->CassDCash, "%lf", CassDCash );
	trace( DEBUG_NORMAL, "Cassette D Cash  [ %s Notes]",status_rec->CassDCash);

	TotCash = CassACash + CassBCash + CassCCash + CassDCash;
	sprintf( status_rec->TotCash, "%lf", TotCash );
	trace( DEBUG_NORMAL, "Total Cash [ %s ] ", status_rec->TotCash);

	strncpy( status_rec->TotNotesPurged, AtmReq, 3 );
	trace( DEBUG_NORMAL, "Total Notes Purged [ %s ] ",status_rec->TotNotesPurged);


	memset( &devmgrq, 0, sizeof( struct EzDeviceMgrQMsg ) );
	devmgrq.SourceType = TABLE;
	devmgrq.CommandCode = TRITONSTATUS;
	devmgrq.OperationCode = UPDATE;
	strcpy( devmgrq.DeviceId, DeviceId.c_str() );
	memcpy( devmgrq.SourceBuffer, ( char * )status_rec, sizeof( struct TritonStatusMsg ) );

	if( PostDevMgrMsg( devmgrq, DeviceId.c_str() ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostDevMgrMsg for DeviceId[%s]", DeviceId.c_str() );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Updated Status for DeviceId[%s]", DeviceId.c_str() );
		return 0;
	}
}

int EzTritonStd :: composeHostTotalResponse( char *AtmReq, string DeviceId )
{
	char OutBuf[ 1024 ];
	char tempStr[ 200 ], crcmsg[ 5 ];
	int offset = 0, fldno = 0;
	unsigned int crc;
	struct TritonStatusMsg status_rec;

	memset( OutBuf, 0, sizeof( OutBuf ) );
	memset( tempStr, 0, sizeof( tempStr ) );
	getToken( AtmReq , tempStr, 0x1c, ++fldno );
	trace( DEBUG_NORMAL, "IN <TerminalId> <%s>", tempStr );
	strcpy( OutBuf + offset, tempStr );
	trace( DEBUG_NORMAL, "<OUT>[TerminalId][%s]", tempStr );
	offset += strlen( tempStr );
	OutBuf[ offset ] = 0x1c;
	offset++;

	memset( tempStr, 0, sizeof( tempStr ) );
	getToken( AtmReq , tempStr, 0x1c, ++fldno );
	trace( DEBUG_NORMAL, "IN <TxnCode> <%s>", tempStr );
	strcpy( OutBuf + offset, tempStr );
	trace( DEBUG_NORMAL, "<OUT>[TxnCode][%s]", tempStr );
	offset += strlen( tempStr );
	OutBuf[ offset ] = 0x1c;
	offset++;

	struct tm *timenow;
	time_t t = 0;
	t = time( &t );
	timenow = localtime( &t );

	//Transaction Date
	memset( tempStr, 0, sizeof( tempStr ) );
	sprintf( tempStr, "%02d%02d%02d", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year % 100 );
	trace( DEBUG_NORMAL, "<OUT>[TranDate][%s]", tempStr );
	strcpy( OutBuf + offset, tempStr );
	offset += strlen( tempStr );
	OutBuf[ offset ] = 0x1c;
	offset++;

	memset( tempStr, 0, sizeof( tempStr ) );
	getToken( AtmReq , tempStr, 0x1c, ++fldno );
	memset( &status_rec, 0, sizeof( struct TritonStatusMsg ) );
	ServeStatusMonitoring( tempStr, DeviceId, 0, 0, 0, 0, &status_rec );

	strncpy( OutBuf + offset, AtmReq + strlen( tempStr ) + 20, 20 );
	offset += 20;
	OutBuf[ offset ] = 0x1c;
	offset++;
	OutBuf[ offset ] = 0x1c;
	offset++;

	//CRC
	crc = crc16(( unsigned char * ) OutBuf, strlen( OutBuf ) + 7 );
	sprintf( crcmsg, "%04X", crc );
	strcat( OutBuf, "ub" );
	strcat( OutBuf, crcmsg );
	strcat( OutBuf, "\x1c" );

	atmbuf.CurrentState = DOWNLOAD ;

	if( PostAtmMsg( DeviceId.c_str(), OutBuf ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}
	return 0;
}

bool EzTritonStd :: IsDisableFullReversal( const char *DeviceId )
{
	FILE *rev_fptr;
	char cfgpath[ 150 ];
	int RevFlag;
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s/%s/%s_%s_%s", getenv( "EZDIR_HOME" ), "cfg", "atm", "tritontemplates","TRITATM", DeviceId, "ReversalProperty.cfg" );
	trace( DEBUG_NORMAL, "cfgpath[%s]", cfgpath );
	rev_fptr = fopen( cfgpath, "r" );
	if( rev_fptr == NULL )
	{
		memset( cfgpath, 0, sizeof( cfgpath ) );
		sprintf( cfgpath, "%s/%s/%s/%s/%s_%s", getenv( "EZDIR_HOME" ), "cfg", "atm",  "tritontemplates","TRITATM", "ReversalProperty.cfg" );
		trace( DEBUG_NORMAL, "cfgpath[%s]", cfgpath );
		rev_fptr = fopen( cfgpath, "r" );
		if( rev_fptr == NULL )
			return false;
	}
	fscanf( rev_fptr, "%d", &RevFlag );
	fclose( rev_fptr );
	trace( DEBUG_NORMAL, "RevFlag for DeviceId[%s] is[%d]", DeviceId, RevFlag );
	if( ( RevFlag == 1 ) || ( RevFlag == 2 ) )
		return true;
	else
		return false;
}

bool EzTritonStd :: IsDisablePartialReversal( const char *DeviceId )
{
	FILE *rev_fptr;
	char cfgpath[ 150 ];
	int RevFlag;
	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s/%s/%s_%s_%s", getenv( "EZDIR_HOME" ), "cfg", "atm", "tritontemplates","TRITATM", DeviceId, "ReversalProperty.cfg" );
	rev_fptr = fopen( cfgpath, "r" );
	if( rev_fptr == NULL )
	{
		memset( cfgpath, 0, sizeof( cfgpath ) );
		sprintf( cfgpath, "%s/%s/%s/%s/%s_%s", getenv( "EZDIR_HOME" ), "cfg", "atm",  "tritontemplates","TRITATM", "ReversalProperty.cfg" );
		rev_fptr = fopen( cfgpath, "r" );
		if( rev_fptr == NULL )
			return false;
	}
	fscanf( rev_fptr, "%d", &RevFlag );
	fclose( rev_fptr );
	if( RevFlag == 2 )
		return true;
	else
		return false;
}


int EzTritonStd :: CashCheck( const char *TxnAmount, struct TritonStatusMsg *status_ptr )
{
	char *endptr;
	int TranAmount = strtod( TxnAmount, &endptr ) / 100 ;
	int CassBNotesToDisp = TranAmount / 500;
	int CassANotesToDisp = ( TranAmount - ( CassBNotesToDisp  * 500 ) ) / 100;

	trace( DEBUG_NORMAL, "TranAmount[%d] CassBNotesToDisp[%d] CassANotesToDisp[%d]", TranAmount, CassBNotesToDisp, CassANotesToDisp );

	trace( DEBUG_NORMAL, "CassANotes[%d] CassBNotes[%d]", atoi( status_ptr->CassANotes ), atoi( status_ptr->CassBNotes ) );

	if( ( !atoi( status_ptr->CassANotes ) ) && ( !atoi( status_ptr->CassBNotes ) ) )
		return -1;

	if( ( atoi( status_ptr->CassBNotes ) >= CassBNotesToDisp ) && ( atoi( status_ptr->CassANotes ) >= CassANotesToDisp ) )
	{
		trace( DEBUG_NORMAL, "Dispense Case-1");
		return 1;
	}

	if( ( atoi( status_ptr->CassBNotes ) < CassBNotesToDisp ) && ( atoi( status_ptr->CassANotes ) < CassANotesToDisp ) )
	{
		trace( DEBUG_NORMAL, "Dispense Case-2");
		return -2;
	}

	if( atoi( status_ptr->CassBNotes ) < CassBNotesToDisp )
	{
		trace( DEBUG_NORMAL, "Dispense Case-3");
		int CassBRNotes = CassBNotesToDisp - atoi( status_ptr->CassBNotes );
		CassANotesToDisp = CassANotesToDisp + ( CassBRNotes * 5 );

		if( atoi( status_ptr->CassANotes ) < CassANotesToDisp )
		{
			trace( DEBUG_NORMAL, "Dispense Case-4");
			return -2;
		}
		else
		{
			trace( DEBUG_NORMAL, "Dispense Case-5");
			return 1;
		}
	}

	if( atoi( status_ptr->CassANotes ) < CassANotesToDisp )
	{
		trace( DEBUG_NORMAL, "Dispense Case-6");
		return -2;
	}
	return 1;
}

int EzTritonStd :: PostAtmMsg( const char *DestPort, char *AtmMsg )
{
	hex_dump( ( unsigned char * )AtmMsg, ( unsigned int )strlen( AtmMsg ) );

	memset( devmem.AtmSharedBuffer, 0, sizeof( devmem.AtmSharedBuffer ) );
	memcpy( devmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

	memset( devmem.DeviceInfoBuffer, 0, sizeof( devmem.DeviceInfoBuffer ) );
	memcpy( devmem.DeviceInfoBuffer, (char *)&devinfo, sizeof( struct DeviceTableInfo ) );

	if( WriteDeviceMemory( DestPort, &devmem ) < 0 )
		trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", DestPort );
	else
		trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", DestPort );

	if( devinfo.DeviceLogging == 'Y' || devinfo.DeviceLogging == 'y' )
	{
		memset( &devmgrq, 0, sizeof( struct EzDeviceMgrQMsg ) );
		PackDeviceLogMsg( devinfo.AcquirerInst, devinfo.DeviceLogicalGroupId, DestPort, AtmMsg, MSG_TO_DEVICE, &devmgrq );
		trace( DEBUG_NORMAL, "Logging the Message from Device[ %s ] ", DestPort );

		if( PostDevMgrMsg( devmgrq, devmgrq.DeviceId ) < 0 )
			trace( DEBUG_ERROR, "Failed in PostDevMgrMsg");
	}

	if ( WritePortChannel( DestPort, AtmMsg, strlen( AtmMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to post the Message into Port Channel[ %s ]", DestPort );
		return -1;
	}
	else
		trace( DEBUG_NORMAL, "Posted the Message to Port Channel[ %s ]", DestPort );

	return 1;
}

int EzTritonStd :: PostTxnMsg( struct EzDevMsg *DevMsg, const char *DeviceId )
{
	struct EzTxnMsg eztxnmsg;

	memset( devmem.AtmSharedBuffer, 0, sizeof( devmem.AtmSharedBuffer ) );
	memcpy( devmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

	memset( devmem.DeviceInfoBuffer, 0, sizeof( devmem.DeviceInfoBuffer ) );
	memcpy( devmem.DeviceInfoBuffer, (char *)&devinfo, sizeof( struct DeviceTableInfo ) );

	if( WriteDeviceMemory( DeviceId, &devmem ) < 0 )
		trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", DeviceId );
	else
		trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", DeviceId );

	trace( DEBUG_NORMAL, "Transforming the Device message into Transaction Message");
	strcpy( DevMsg->SrcChannel, TRITONSTDCHANNEL );

	memset( &eztxnmsg, 0, sizeof( struct EzTxnMsg ) );
	TransformOUTboundMsg( &eztxnmsg, DevMsg );

	trace( DEBUG_TXN, "MsgType[ %d ] TxnCode[ %d ] TraceNo[ %d ] Chn[ %s ] Amount[ %s ] DispAmount[ %s ]", eztxnmsg.MsgType, eztxnmsg.TxnCode, eztxnmsg.TraceNo, eztxnmsg.chn, eztxnmsg.Amount, eztxnmsg.DispAmount );

	if( WriteChannel( TRANSACTIONCHANNEL, (char*)&eztxnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", TRANSACTIONCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_NORMAL, "Message written into the %s channel", TRANSACTIONCHANNEL );

	return 1;
}

int EzTritonStd :: PostDevMgrMsg( struct EzDeviceMgrQMsg devmgrq, const char *DeviceId )
{
	trace( DEBUG_NORMAL, "Posting Message to DeviceMgr for Updation");
	if( WriteChannel( DEVICEMGRCHANNEL, (char*)&devmgrq, sizeof( struct EzDeviceMgrQMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", DEVICEMGRCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_NORMAL, "Message Posted into the %s channel", DEVICEMGRCHANNEL );
	return 1;
}

int main( int argc, char **argv )
{
	EzTritonStd eztritonstd;
	eztritonstd.InitEzTritonStdDriver( argv[ 0 ] );
	eztritonstd.ServiceRequest();
	return 1;
}

