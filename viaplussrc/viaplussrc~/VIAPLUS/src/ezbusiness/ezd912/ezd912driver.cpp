#include <ezbusiness/ezd912.h>

EzD912 :: EzD912()
{

}

EzD912 :: ~EzD912()
{

}

int EzD912 :: InitEzD912Driver( const char * TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezd912driver.log"  );

    if( openDebug( logpath, TaskName ) < 0 )
    	exit( 0  );

    SetDebug();

    if( InitEzTaskUtil( this ) < 0 )
    {
	   trace( DEBUG_ERROR, "Error in Initializing EzTaskUtil" );
	   trace( DEBUG_ERROR, "^^^^^^^^^^^EzD912Driver Ended Abnormally^^^^^^^^^^^^^" );
	   closeDebug( );
	   exit( 0  );
	}

    if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzChannelUtil"  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzD912Driver Ended Abnormally^^^^^^^^^^^^^" );
	    closeDebug( );
	    TaskExit( );
	}

	if( CreateChannel( D912DRIVERCHANNEL, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Creating EzD912Driver Channel"  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzD912Driver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	//Initializing Utilizes

	if( InitEzATMUtil( this, false ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing the ATMUtil"  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzD912Driver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	InitEzTemplateUtil( this );
	InitEzAtmCashUtil( TaskName, this );
	TaskInit( );
	initEzSigUtil( this  );
	return 1;
}

void EzD912 :: ServiceRequest()
{
	char ReadBuf[ BUFFER_SIZE + 1 ];
	int ret, BufSize;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ];
	struct EzAtmController ContReq;
	struct EzTxnMsg AppReq;
	struct EzDevMsg DevMsg;

	while( 1 )
	{
		trace( DEBUG_NORMAL, "Waiting for Message in EzD912Driver Channel" );
		memset( ReadBuf, 0, sizeof( ReadBuf ) );
		if( ReadMessage( ReadBuf, &BufSize ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading EzD912Driver Channel" );
			continue;
		}

		memset( ChannelName, 0, sizeof( ChannelName ) );
		strcpy( ChannelName, GetLastSenderChannelName() );

		trace( DEBUG_NORMAL, "Message of size [%d] Received from Channel[%s]", BufSize, GetLastSenderChannelName() );

		if( IsPortMessage() )
		{
			if( DiagnizeAndServeAtmReq( ReadBuf, BufSize, ChannelName ) < 0 )
				trace( DEBUG_ERROR, "Failed in DiagnizeAndServeAtmReq" );
		}
		else
		{
			if( !strcmp( ChannelName, TRANSACTIONCHANNEL ) )
			{
				memset( &AppReq, 0, sizeof( struct EzTxnMsg )  );
				memcpy( &AppReq, ReadBuf, BufSize );

				memset( &DevMsg, 0, sizeof( struct EzDevMsg )  );

				//trace( DEBUG_NORMAL, "Transforming the Transaction Message into Device Message" );

				if( TransformINboundMsg( &DevMsg, &AppReq ) < 0 )
					trace( DEBUG_ERROR, "Failed in TransformINboundMsg" );

				if( !strlen( DevMsg.m_chn ) )
					ezpadssutil.maskString( DevMsg.chn, 6, strlen( DevMsg.chn ) - 4, '*', DevMsg.m_chn );
				trace( DEBUG_NORMAL, "MsgType[ %04d ] TxnCode[ %06d ] TraceNo[ %04d ] RespCode[ %03d ] Chn[ %s ] Amount[ %s ] ", DevMsg.MsgType, DevMsg.TxnCode, DevMsg.TraceNo, DevMsg.RespCode, DevMsg.m_chn, DevMsg.Amount );
				if(  DevMsg.MsgType == EZLINK_TXN_TxnResponse )
				{
					if( DiagnizeAndServeAppReq( DevMsg ) < 0 )
						trace( DEBUG_ERROR, "Failed in DiagnizeAndServeAppReq");
				}
				else
				{
					memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );

					trace( DEBUG_NORMAL, "Reading Memory in DiagnizeAndServeAppReq ");
					if( ReadAtmMemory( DevMsg.DestPort, &atmmem ) < 0 )
						trace( DEBUG_ERROR, "Unable to Read AtmMemoryTable AtmId[ %s ]", DevMsg.DestPort );

					memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
					memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
					memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );
					memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

					memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
					memcpy( &atmbuf.DevMsg, &DevMsg, sizeof( struct EzDevMsg ) );

					memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
					memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

					if( WriteAtmMemory( DevMsg.DestPort, &atmmem ) < 0 )
						trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", DevMsg.DestPort );
					else
						trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", DevMsg.DestPort );
				}
			}
			else if( !strcmp( ChannelName, CONTROLLERCHANNEL ) )
			{
				memset( &ContReq, 0, sizeof( struct EzAtmController )  );
				memcpy( &ContReq, ReadBuf, sizeof( struct EzAtmController ) );

				trace( DEBUG_NORMAL, "Message Received : [ %s ][ %s ][ %d ][ %d ][ %d ]", ContReq.AtmId, ContReq.MsgBuf, ContReq.MsgType, ContReq.DownloadType ,ContReq.CommandType);
				if( DiagnizeAndServeContReq( ContReq, ContReq.AtmId  ) < 0 )
					trace( DEBUG_ERROR, "Failed in DiagnizeAndServeContReq");
			}
			else
				trace( DEBUG_ERROR, "Invalid Channel Name [ %s ]", ChannelName );
		}
	}
}

int EzD912 :: DiagnizeAndServeAtmReq( char *AtmReq , int MsgSize , char *AtmId )
{
	char StatusCode[ STATUSBUF_SIZE + 1 ];

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );

	trace( DEBUG_TEST, "Reading [%s] Memory in DiagnizeAndServeAtmReq ", AtmId );

	if( ReadAtmMemory( AtmId, &atmmem ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to Read AtmMemoryTable AtmId[ %s ]", AtmId );
		return -1;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
	memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );

	memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &denominfo, &atmbuf.denominfo, sizeof( struct DenomInfo ) * 8 );

	if( atminfo.LoggingFlag == 'Y' || atminfo.LoggingFlag == 'y' )
	{
		memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
		PackAtmLogMsg( AtmId, AtmReq, MSG_FROM_DEVICE, &atmmgrq );
		trace( DEBUG_TEST, "Logging the Message from Device[ %s ] ", AtmId );

		if( PostAtmMgrMsg( atmmgrq, AtmId ) < 0 )
			trace( DEBUG_ERROR, "Failed in PostAtmMgrMsg" );
	}

	memset( StatusCode, 0, sizeof( StatusCode ) );

	switch( *AtmReq )
    {
        case '1':
                 trace( DEBUG_TEST, "Unsolicitiated Message/Consumer Request Message Received from Atm[%s]", AtmId );

                 if( ServeUnsolicitatedMessage( ++AtmReq, ( MsgSize - 1 ), AtmId, StatusCode ) < 0 )
                	 trace( DEBUG_ERROR, "Failed in ServeUnsolicitatedMessage for Atm[%s]", AtmId );
                 break ;

        case '2':
                 trace( DEBUG_TEST, "Solicitated Message Received from Atm[%s]", AtmId );
                 if( ServeSolicitatedMessage( ++AtmReq, ( MsgSize - 1 ), AtmId, StatusCode ) < 0 )
                	 trace( DEBUG_ERROR, "Failed in ServeSolicitatedMessage for Atm[%s]", AtmId );
                 break ;

        default:
                 trace( DEBUG_ERROR, "Unsupported message type from Atm[%s]", AtmId );
                 break ;
	}

    if( strlen( StatusCode ) != 0 && strcmp( StatusCode, "|" ) )
    {
		memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
		PackAtmStatusMsg( AtmId, StatusCode, atmbuf.StaticStatus, &atmmgrq );
		trace( DEBUG_TEST, "Updating the Status Message for Atm< %s > ", AtmId );
		if( PostAtmMgrMsg( atmmgrq, AtmId ) < 0 )
		{
			trace("Failed in PostAtmMgrMsg");
			return -1;
		}
    }

    if( strlen( StatusCode ) != 0 && strcmp( StatusCode, "|" ) )
    {
    	memset( &alertmgrmsg, 0, sizeof( struct EzAlertMgrMsg  ) );
    	PackAtmAlertMsg( AtmId, StatusCode, &alertmgrmsg );
    	trace( DEBUG_TEST, "Sending the Status Message for Atm < %s > ", AtmId );
    	if( PostAlertMgrMsg( alertmgrmsg ) < 0 )
    	{
			trace("Failed in PostAlertMsg");
			return -1;
		}
    }

    if( strlen( atmbuf.StaticStatus ) != 0 && strcmp( atmbuf.StaticStatus, "NONE" ) )
    {
    	memset( &alertmgrmsg, 0, sizeof( struct EzAlertMgrMsg  ) );
    	PackAtmAlertMsg( AtmId, atmbuf.StaticStatus, &alertmgrmsg );
    	trace( DEBUG_TEST, "Sending the Status Message for Atm < %s > ", AtmId );
    	if( PostAlertMgrMsg( alertmgrmsg ) < 0 )
    	{
			trace("Failed in PostAlertMsg");
			return -1;
		}
    }

	return 1;
}

int EzD912 :: DiagnizeAndServeAppReq( struct EzDevMsg DevMsg )
{
	trace( DEBUG_TEST, "Message from Transaction Mgr" );
	char FileName[ FILENAME_SIZE + 1 ], SearchId[ TEMP + 1 ], CfgVal[ TEMP + 1 ];
	int NoOfAcct;
	EzCfgUtil cfg;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );

	trace( DEBUG_TEST,"Reading Memory for [ %s ]in DiagnizeAndServeAppReq ", DevMsg.DestPort );
	if( ReadAtmMemory( DevMsg.DestPort, &atmmem ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to Read AtmMemoryTable AtmId[ %s ]", DevMsg.DestPort );
		return -1;
	}

	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
	memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );

	memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &denominfo, &atmbuf.denominfo, sizeof( struct DenomInfo ) * 8 );

	//for( int i = 0; i < 8; i++)
		//trace( "Id[%c] Pos[%d] Value[%d]\tCode[%d]\tStatus[%c]", denominfo[i].DenomId, denominfo[i].CassPosition, denominfo[i].CurrencyValue, denominfo[i].CurrencyCode, denominfo[i].Status);


	trace( DEBUG_TEST, "MsgType[%04d] TxnCode[%06d] RespCode[%03d]", DevMsg.MsgType, DevMsg.TxnCode, DevMsg.RespCode );

	if( DevMsg.RespCode == 0 )
	{
		if( DevMsg.TxnCode/10000 == 36 )
		{
			//Check No.of Account...If only one, then build function command else build OAR request
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/%s/%s", getenv("EZDIR_HOME"), "inf", DevMsg.RespFile );

			trace( DEBUG_NORMAL, "OAR info file[ %s ]", DevMsg.RespFile );

			NoOfAcct = GetTotalData( DevMsg.RespFile );

			trace( DEBUG_NORMAL, "No 0f Acct No[ %d ]", NoOfAcct );

			if( NoOfAcct < 0 )
			{
				trace( DEBUG_ERROR, "Unable to get Number of Accounts");
				return -1;
			}
			else
			{
				if( NoOfAcct == 1 )
				{
					if( cfg.cfg_open( FileName ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed to open file [ %s ]", FileName );
						return -1;
					}

					memset( SearchId, 0, sizeof( SearchId ) );
					sprintf( SearchId, "%s_%d", "OAR#VAR", 0 );
					trace( DEBUG_NORMAL, "SearchId[ %s ]", SearchId );
					if( cfg.cfg_search( SearchId, CfgVal, 2 ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
						cfg.cfg_close();
						return -1;
					}
					else
					{
						trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
						if( !strlen( DevMsg.FromAccount ) )
						{
							trace( DEBUG_TEST, "Single Account Coping the From Account");
							memset( DevMsg.FromAccount, 0, sizeof( DevMsg.FromAccount ) );
							strcpy( DevMsg.FromAccount, CfgVal );
						}
						else
						{
							trace( DEBUG_TEST, "Single Account Coping the To Account");
							memset( DevMsg.ToAccount, 0, sizeof( DevMsg.ToAccount ) );
							strcpy( DevMsg.ToAccount, CfgVal );
						}
					}

					cfg.cfg_close();

					atmbuf.CurrentState = INTERACTIVE;

					if( BuildAndPostFuncMsg( DevMsg ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
						return -1;
					}
				}
				else
				{
					trace( DEBUG_TEST, "More than one Acct");
					if( BuildAndPostOARRequest( DevMsg ) < 0 )
					{
						trace( DEBUG_ERROR,"Failed in BuildAndPostOARRequest");
						return -1;
					}
				}
			}
		}
		else
		{
			if( BuildAndPostFuncMsg( DevMsg ) < 0 )
			{
				trace( DEBUG_ERROR,"Failed in BuildAndPostFuncMsg");
				return -1;
			}
		}
	}
	else
	{
		if( BuildAndPostFuncMsg( DevMsg ) < 0 )
		{
			trace( DEBUG_ERROR,"Failed in BuildAndPostFuncMsg");
			return -1;
		}
	}
	return 1;
}

int EzD912 :: DiagnizeAndServeContReq( struct EzAtmController ContReq , char *AtmId )
{
	trace( DEBUG_TEST, "Reading [%s] Memory in DiagnizeAndServeContReq", AtmId );

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	trace( DEBUG_NORMAL, "Reading Memory for [ %s ]in DiagnizeAndServeAppReq ", AtmId );
	if( ReadAtmMemory( AtmId, &atmmem ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to Read AtmMemoryTable AtmId[ %s ]",  AtmId );
		return -1;
	}


	memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
	memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );

	memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( atmmem.AtmSharedBuffer ) );

	/*
	if ( atmbuf.CurrentState == TRANSACTIONREQUEST || atmbuf.CurrentState == TRANSACTIONRESPONSE || atmbuf.CurrentState == INTERACTIVE )
        {
                trace( " Download or Command Operation Not Allowed For ATM[ %s ]", AtmId );
                return -1;
        }
	*/

	if( ContReq.MsgType == EZ_ATM_DOWNLOAD_REQ )
	{
		trace( DEBUG_TEST, "Received Download Command For ATM[ %s ]", AtmId );
		if( BuildAndPostWriteCmd( ContReq  ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed in BuildAndPostWriteCmd For ATM[ %s ]", AtmId );
			return -1;
		}
	}
	else if( ContReq.MsgType == EZ_ATM_COMMAND_REQ )
	{
		trace( DEBUG_TEST, "Received Opertional Command For ATM[ %s ]", AtmId );
		if( BuildAndPostOperCmd( ContReq  ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed in BuildAndPostOperCmd For ATM[ %s ]", AtmId );
			return -1;
		}
	}
	else
	{
		trace( DEBUG_ERROR, "Invaild Message Type [ %d ] for ATM [ %s ]", ContReq.MsgType, AtmId );
		return -1;
	}
	return 1;
}

int EzD912 :: ServeUnsolicitatedMessage( char *AtmReq, int Size , char *AtmId, char *StatusCode )
{
	switch( *AtmReq )
	{
		case '1' :
			trace( DEBUG_TEST, "Consumer Request from ATM[ %s ]", AtmId );
		    if( ServeConsumerRequests( AtmReq + 2, ( Size - 2 ) , AtmId  ) < 0 )
		    {
		    	trace( DEBUG_ERROR, "Failed in ServeConsumerRequests For ATM[ %s ]", AtmId );
		    	return -1;
		    }
		    break ;

		case '2' :
			trace( DEBUG_TEST, "Status Change Message from ATM[ %s ]", AtmId );
		    if( ServeStatusChangeMsg( AtmReq + 2, ( Size - 2 ) , AtmId, StatusCode ) < 0 )
		    {
		    	trace( DEBUG_ERROR, "Failed in ServeStatusChangeMsg For ATM[ %s ]", AtmId );
		    	return -1;
		    }
	        break ;
	}
	return 1;
}

int EzD912 :: ServeSolicitatedMessage( char * AtmReq, int Size , char *AtmId, char *StatusCode )
{
	char Luno[ LUNO_SIZE + 1 ], Temp[ TEMP + 1 ], *p;
	char nStatusCode[ STATUSBUF_SIZE + 1 ];
	int count;
	bool found = false;

	struct EzAtmController AtmCont;
	struct EzDevMsg ConsumerReq;
	struct EzAtmCounterInfo CounterInfo;
	struct AtmDenomStatusMsg AtmDenomStatus;

	AtmReq += 2;

	memset( Luno, 0, sizeof( Luno )  );
    p = ( char * ) memchr( AtmReq, DEVICE_FS, Size  );
    memcpy( Luno, AtmReq, ( p - AtmReq ) );
    trace( DEBUG_NORMAL, "Luno :%s",Luno );
	AtmReq += ( strlen( Luno ) + 1 ) ;
	AtmReq++;//0x1c moved

	memset( &ConsumerReq, 0, sizeof( struct EzDevMsg ) );
	memcpy( &ConsumerReq, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

	switch ( * AtmReq )
	{
		case '9':
		case 'B':
			trace( DEBUG_NORMAL, "Device sents READY message. CurrentStatus[%c]", atmbuf.CurrentState );
			if( atmbuf.CurrentState == TRANSACTIONRESPONSE )
			{
				trace( DEBUG_NORMAL, "[ %s ] is in TRANSACTIONRESPONSE state", AtmId );
				if( ( ConsumerReq.TxnCode/10000 ) == 1 &&  ConsumerReq.RespCode == 0 )
				{
					atmbuf.TxnCount = atmbuf.TxnCount + 1;
					trace( DEBUG_TEST, "TxnCount[%d]", atmbuf.TxnCount );
					if( atmbuf.TxnCount == ezatmproperty.CounterRefresh )
					{
						atmbuf.TxnCount = 0;
						found = true;
					}

					memset( &AtmDenomStatus, 0, sizeof( struct AtmDenomStatusMsg ) );
					if( LoadDenomDetails( AtmId, ConsumerReq.RefNum, ConsumerReq.BatchId, atmbuf.DispenceLogicBuf, atminfo.AtmTypeId, ConsumerReq.TranDate, ConsumerReq.TranTime, &AtmDenomStatus ) < 0 )
						trace( DEBUG_ERROR, "Error in Loading Cassette Status Msg");
					else
					{
						trace( "AtmDenomStatus.BatchId[%s] AtmDenomStatus.RefNum[%s]", AtmDenomStatus.BatchId, AtmDenomStatus.RefNum );
						memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
						PackAtmDenomMsg( AtmId, &AtmDenomStatus, &atmmgrq );
						if( PostAtmMgrMsg( atmmgrq, AtmId ) < 0 )
							trace( DEBUG_ERROR, "Failed in PostAtmMgrMsg" );
					}
				}

				trace("MsgType[%d]", ConsumerReq.MsgType);
				if( ( ConsumerReq.MsgType == 6000 ) || ( ConsumerReq.MsgType == 210 && ConsumerReq.TxnCode / 10000 == 1 && ConsumerReq.RespCode == 0 ) )
				{
					ConsumerReq.MsgType = 6010;
					ConsumerReq.RespCode = EZLINK_RC_Approved;
					if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
						return -1;
					}
				}

				if( found )
				{
					trace( DEBUG_NORMAL, "Refreshing the ATM Counter Details");
					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
					AtmCont.CommandType = GET_SUPPLY_COUNTS;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
				}

				if( strcmp( atmbuf.StaticStatus, "NONE" ) )
				{
					trace( DEBUG_TEST, "Checking for ATM Action Property");
					memset( Temp, 0, sizeof( Temp ) );
					if( ReadAtmActionProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, atmbuf.StaticStatus, ConsumerReq.TxnCode, Temp, &ConsumerReq.RespCode, SENDCOMMAND ) < 0 )
						trace("ATM Action Property not Found");
					else
					{
						trace("ATM Action Property Found Command[%s]", Temp );
						memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
						AtmCont.CommandType = GetOpertionalCmd( Temp );
						if( AtmCont.CommandType <= 0 )
							trace("Invaild Command[%s] CommandType[%d]", Temp, AtmCont.CommandType );
						else
						{
							AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
							memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
							if( PostContMsg( AtmCont, AtmId ) < 0 )
							{
								trace( DEBUG_ERROR, "Failed in PostContMsg" );
								return -1;
							}
						}
					}
				}
				/*
				atmbuf.CurrentState = IDLE;
                                memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
                                memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

                                if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
                                        trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
                                else
                                        trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );
				*/
				
			}
			else if( atmbuf.CurrentState == TRANSACTIONRESPONSE )
			{
				if( ( ConsumerReq.TxnCode/10000 ) == 1 && ConsumerReq.RespCode == EZLINK_RC_DispencedFully )
				{
					memset( &AtmDenomStatus, 0, sizeof( struct AtmDenomStatusMsg ) );
					if( LoadDenomDetails( AtmId, ConsumerReq.RefNum, ConsumerReq.BatchId, atmbuf.DispenceLogicBuf, atminfo.AtmTypeId, ConsumerReq.TranDate, ConsumerReq.TranTime, &AtmDenomStatus ) < 0 )
						trace( DEBUG_ERROR, "Error in Loading Cassette Status Msg");
					else
					{
						memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
						PackAtmDenomMsg( AtmId, &AtmDenomStatus, &atmmgrq );
						if( PostAtmMgrMsg( atmmgrq, AtmId ) < 0 )
							trace( DEBUG_ERROR, "Failed in PostAtmMgrMsg" );
					}
				}
				else if( ( ConsumerReq.TxnCode/10000 ) == 20 && ConsumerReq.RespCode == EZLINK_RC_Approved )
				{
					ConsumerReq.MsgType = 6010;
					trace( DEBUG_NORMAL, "Sending Deposit Completion Message for [ %s ]", AtmId );
					if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
						return -1;
					}
				}
				/*
				atmbuf.CurrentState = IDLE;
                                memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
                                memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

                                if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
                                        trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
                                else
                                        trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );
				*/
			}
			else if( atmbuf.CurrentState == DOWNLOAD )//Download Message
			{
				trace( DEBUG_NORMAL, "[ %s ] is in DOWNLOAD state", AtmId );
				memset( &AtmCont, 0, sizeof( struct EzAtmController ) );

				AtmCont.MsgType = EZ_ATM_DOWNLOAD_RESP;
				AtmCont.DownloadType = atmbuf.NextCommand;
				AtmCont.RespType = EZ_ATM_GOOD_RESP;
				memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

				if( PostContMsg( AtmCont, AtmId ) < 0 )
				{
					trace( DEBUG_ERROR, "Failed in PostContMsg" );
					return -1;
				}
			}
			else if( atmbuf.CurrentState == OPERATIONAL )//Operation command
			{
				trace( DEBUG_NORMAL, "[ %s ] is in OPERATIONAL state", AtmId );
				memset( &AtmCont, 0, sizeof( struct EzAtmController ) );

				AtmCont.MsgType = EZ_ATM_COMMAND_RESP;
				AtmCont.CommandType = atmbuf.CurrentCommand;
				AtmCont.RespType = EZ_ATM_GOOD_RESP;
				memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

				if( PostContMsg( AtmCont, AtmId ) < 0 )
				{
					trace( DEBUG_ERROR, "Failed in PostContMsg" );
					return -1;
				}
			}
			else if( atmbuf.CurrentState == SUPERVISOR )//Supervisor Transaction
			{
				trace( DEBUG_NORMAL, "[ %s ] is in SUPERVISOR state", AtmId );
				if( ConsumerReq.TxnCode == 990005 )
				{
					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
					AtmCont.CommandType = CLEAR_SUPPLY_COUNTS;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
				}
				else if( ConsumerReq.TxnCode == 990001 )
				{
					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
					AtmCont.CommandType = GET_SUPPLY_COUNTS;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
				}
				else if( ConsumerReq.TxnCode == 990004 )
				{
					/*memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );
					if( ResetDenomStatus( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AtmId, DIEBOLD, denominfo ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reseting the DenomStatus" );
						return -1;
					}
					else
					{
						memset( &atmbuf.denominfo, 0, sizeof( struct DenomInfo ) * 8 );
						memcpy( &atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 8 );

						memset( atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
						memcpy( atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

						memset( atmmem.AtmInfoBuffer, 0, sizeof( atmmem.AtmInfoBuffer ) );
						memcpy( atmmem.AtmInfoBuffer, (char *)&atminfo, sizeof( struct AtmTableInfo ) );

						if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
						{
							trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
							return -1;
						}
						else
							trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", AtmId );
					}*/
				}
			}
		    break ;

		case '8':
			trace( DEBUG_NORMAL, "Device Fault response" );
			if( atmbuf.CurrentState == TRANSACTIONRESPONSE )
			{
				trace( DEBUG_NORMAL, "[ %s ] is in TRANSACTIONRESPONSE state", AtmId );
				if( ( ConsumerReq.TxnCode/10000 ) == 1 && ConsumerReq.RespCode == EZLINK_RC_Approved )
				{
					ConsumerReq.MsgType = 6010;
					ConsumerReq.RespCode = EZLINK_RC_SystemError;
					if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
						return -1;
					}
				}
				/*
				atmbuf.CurrentState = IDLE;
                                memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
                                memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

                                if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
                                        trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
                                else
                                        trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );
				*/
			}
			AtmReq++;
			AtmReq++; //0x1c position is moved
			if( atmbuf.CurrentCommand == GET_SUPPLY_COUNTS || atmbuf.CurrentCommand == GET_ESUPPLY_COUNTS || atmbuf.CurrentCommand == CLEAR_SUPPLY_COUNTS || atmbuf.CurrentCommand == CLEAR_ESUPPLY_COUNTS )
			{
				memset( nStatusCode, 0, sizeof( nStatusCode ) );
				if( SolStatusMsg( AtmReq, strlen( AtmReq ), nStatusCode, AtmId ) < 0 )
					trace( DEBUG_ERROR, "Failed in SolStatusMsg" );
				else
					StatusCode += BuiltStatusCode( nStatusCode, strlen( nStatusCode ), StatusCode );
			}
			else
			{
				count = GetNTokens( AtmReq, DEVICE_GS );
				for( int i = 0; i < count; i++)
				{
					memset( Temp, 0, sizeof( Temp ) );
					ParseToken( AtmReq, Temp, i+1, DEVICE_GS  );
					memset( nStatusCode, 0, sizeof( nStatusCode ) );
					if( SolStatusMsg( Temp, strlen( Temp ), nStatusCode, AtmId ) < 0 )
						trace( DEBUG_ERROR, "Failed in SolStatusMsg" );
					else
						StatusCode += BuiltStatusCode( nStatusCode, strlen( nStatusCode ), StatusCode );
				}
			}
			break ;

		case 'A':
        case 'D':
	            trace( DEBUG_NORMAL, "Command Reject" );
				int OldRespCode;
				OldRespCode = ConsumerReq.RespCode;
				if( atmbuf.CurrentState == TRANSACTIONRESPONSE || atmbuf.CurrentState == INTERACTIVE )
				{
					trace( DEBUG_NORMAL, "[ %s ] is in TRANSACTIONRESPONSE < or > INTERACTIVE state", AtmId );
					ConsumerReq.MsgType = ConsumerReq.MsgType + 10;
					OldRespCode = ConsumerReq.RespCode;
					ConsumerReq.RespCode = EZLINK_RC_MessageFormatError;
					if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
						return -1;
					}
					if( ( ConsumerReq.TxnCode/10000 == 1 ) &&  ( OldRespCode == EZLINK_RC_Approved ) )
					{
						ConsumerReq.MsgType = 420;
						ConsumerReq.RespCode = EZLINK_RC_UnableDispense;
						if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
							return -1;
						}
					}
					/*
					atmbuf.CurrentState = IDLE;
                                	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
                                	memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

                                	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
                                        	trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
                                	else
                                        	trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );
					*/
				}
				else if ( atmbuf.CurrentState == DOWNLOAD )
				{
					trace( DEBUG_NORMAL, "[ %s ] is in DOWNLOAD state", AtmId );

					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_DOWNLOAD_RESP;
					AtmCont.DownloadType = atmbuf.CurrentCommand;
					AtmCont.RespType = EZ_ATM_BAD_RESP;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
				}
				else if( atmbuf.CurrentState == OPERATIONAL )//Operation command
				{
					trace( DEBUG_NORMAL, "[ %s ] is in OPERATIONAL state", AtmId );

					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_DOWNLOAD_RESP;
					AtmCont.CommandType = atmbuf.CurrentCommand;
					AtmCont.RespType = EZ_ATM_BAD_RESP;
					memcpy( AtmCont.AtmId, AtmId, strlen(AtmId) );

					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
				}
				break;
		default:
			trace( DEBUG_ERROR, "Not a Status message" );
			break;
	}
	return 1;
}

int EzD912 :: SolStatusMsg( char * AtmReq, int Size , char *StatusCode, char *AtmId )
{
	char DispErrCode[ TEMP + 1 ], Byte[ BYTE + 1 ], Temp[ TEMP + 1 ], *p, temp[ TEMP + 1 ];
	char DenominationId, CassPos, DID, CassetteType, DispLogicBuf[ DISP + 1 ], DispenserStatus[ 5 ];
	int i, NoOfBills = 0, NoOfBillDump = 0, DispencedAmount = 0, Denomination = 0, ret, Rcass;
	char NotesDisp1[ CURRENCYCOUNTS + 1 ], NotesDisp2[ CURRENCYCOUNTS + 1 ], NotesDisp3[ CURRENCYCOUNTS + 1 ], NotesDisp4[ CURRENCYCOUNTS + 1 ], RejectCass[ CURRENCYCOUNTS + 1 ], RejectCard[ CURRENCYCOUNTS + 1 ];
	bool RevFlag = false;
	struct EzDevMsg ConsumerReq;
	struct EzAtmCounterInfo CounterInfo;
	struct EzAtmController AtmCont;


	memset( &ConsumerReq, 0, sizeof( struct EzDevMsg ) );
	memcpy( &ConsumerReq, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

	memset( ConsumerReq.SrcPort, 0, sizeof( ConsumerReq.SrcPort ) );
	strcpy( ConsumerReq.SrcPort, AtmId );

	memset( &ezatmproperty, 0, sizeof( struct EzAtmProperty ) );
	if( ReadAtmProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, ConsumerReq.TxnCode, 0, ConsumerReq.AcqCurrencyCode, &ezatmproperty ) < 0 )
    	trace( DEBUG_ERROR, "Unable to Reading EzAtmProperty");


	DID = *AtmReq;
	switch( *AtmReq )
	{
		case '?':
				trace( DEBUG_NORMAL, "Dispenser problem"  );
				AtmReq++;
				trace( DEBUG_NORMAL, "Withdrawl Area Status [%c]", *AtmReq );

				switch( *AtmReq )
				{
					case '0':
						trace( DEBUG_NORMAL, "No error");
						break;
					case '1':
						trace( DEBUG_NORMAL, "Withdrawal door open prior to dispense");
						break;
					case '2':
						trace( DEBUG_NORMAL, " Withdrawal door open during dispense");
						break;
					case '3':
						trace( DEBUG_NORMAL, "Sensors blocked before dispense");
						break;
					case '4':
						trace( DEBUG_NORMAL, "Sensors blocked before dispense and withdrawal door open during dispense");
						break;
					case '5':
						trace( DEBUG_NORMAL, "Sensors not blocked after dispense");
						break;
				}
				AtmReq++;
				memset( DispErrCode, 0, sizeof( DispErrCode )  );
		        memcpy( DispErrCode, AtmReq, 2  );
		        trace( DEBUG_NORMAL, "Dispenser Error Code [%s]", DispErrCode );
		        if( atoi( DispErrCode ) == 0 )
		        {
		        	ConsumerReq.RespCode = EZLINK_RC_DispencedFully;
		        	if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
        			{
        				trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
        				return -1;
        			}
		        	return 1;
		        }
		        else
		        {
			        memset( DispenserStatus, 0, sizeof( DispenserStatus ) );
			        getDispenserErrorCode( atoi(DispErrCode), DispenserStatus );
			        if( strlen( DispenserStatus ) != 0 )
			        {
			        	StatusCode += BuiltStatusCode( DispenserStatus, strlen( DispenserStatus ), StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, DispenserStatus, atmbuf.StaticStatus );
			        }
		        }
		        AtmReq += 2;
		        switch ( *AtmReq )
                {
		        	case '2':
                    case '3':
                    case '4':
                        	trace( DEBUG_NORMAL, "Full Reversal" );
							ConsumerReq.RespCode = EZLINK_RC_UnableDispense ;
							break ;
                    case '5':
						    trace( DEBUG_NORMAL, "Partial Dispense" );

						    ConsumerReq.RespCode = EZLINK_RC_PartialDispense ;
							AtmReq++;
							memset( DispLogicBuf, 0, sizeof( DispLogicBuf ) );
							sprintf( DispLogicBuf,"%016d", 0 );

							trace( "1{ %s }", AtmReq );
							CassPos = *AtmReq++;//Cassette Position moved
							DenominationId = *AtmReq++;
							DenominationId = toupper( DenominationId );
							trace( DEBUG_NORMAL, "Cassette Position[ %c ] Denomination[ %c ]", CassPos, DenominationId);
							if( DenominationId != '@' && DenominationId != '_')
							{
								if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
									trace( DEBUG_ERROR, "Unable to get Denomination for DenominationId[ %c ]", DenominationId );

								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBills = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Dispensed[ %d ]", NoOfBills );
								PackDispLogicBuf( Temp, DenominationId, DispLogicBuf );
								trace( DEBUG_TEST, "Reformed DispLogicBuf[%s]", DispLogicBuf );
								if( !strcmp( DispErrCode, "17" ) )
									CheckAndSetDenomStatus( DIEBOLD, Temp, DenominationId, denominfo );
								AtmReq += 2 ;//No of Bills moved
								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBillDump = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Moved to Reject Bin[ %d ]", NoOfBillDump );

								AtmReq += 2 ;//No of Bills in reject Cassette moved
								AtmReq += 3 ;//Reserved Fields
								DispencedAmount += ( NoOfBills * Denomination  );
								trace( DEBUG_NORMAL, "Denomination[%d] DispencedAmount[%d]", Denomination, DispencedAmount );
							}
							else
								AtmReq += 7;
							trace( "2{ %s }", AtmReq );
							CassPos = *AtmReq++;//Cassette Position moved
							DenominationId = *AtmReq++;
							DenominationId = toupper( DenominationId );
							trace( DEBUG_NORMAL, "Cassette Position[ %c ] Denomination[ %c ]", CassPos, DenominationId);
							if( DenominationId != '@' && DenominationId != '_')
							{
								if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
									trace( DEBUG_ERROR, "Unable to get Denomination for DenominationId[ %c ]", DenominationId );

								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBills = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Dispensed[ %d ]", NoOfBills );
								PackDispLogicBuf( Temp, DenominationId, DispLogicBuf );
								trace( DEBUG_TEST, "Reformed DispLogicBuf[%s]", DispLogicBuf );
								if( !strcmp( DispErrCode, "18" ) )
									CheckAndSetDenomStatus( DIEBOLD, Temp, DenominationId, denominfo );

								AtmReq += 2 ;//No of Bills moved
								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBillDump = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Moved to Reject Bin[ %d ]", NoOfBillDump );

								AtmReq += 2 ;//No of Bills in reject Cassette moved
								AtmReq += 3 ;//Reserved Fields
								DispencedAmount += ( NoOfBills * Denomination  );
								trace( DEBUG_NORMAL, "Denomination[%d] DispencedAmount[%d]", Denomination, DispencedAmount );
							}
							else
								AtmReq += 7;
							trace( "3{ %s }", AtmReq );
							CassPos = *AtmReq++;//Cassette Position moved
							DenominationId = *AtmReq++;
							DenominationId = toupper( DenominationId );
							trace( DEBUG_NORMAL, "Cassette Position[ %c ] Denomination[ %c ]", CassPos, DenominationId);
							if( DenominationId != '@' && DenominationId != '_')
							{
								if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
									trace( DEBUG_ERROR, "Unable to get Denomination for DenominationId[ %c ]", DenominationId );

								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBills = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Dispensed[ %d ]", NoOfBills );
								PackDispLogicBuf( Temp, DenominationId, DispLogicBuf );
								if( !strcmp( DispErrCode, "19" ) )
									CheckAndSetDenomStatus( DIEBOLD, Temp, DenominationId, denominfo );

								AtmReq += 2 ;//No of Bills moved
								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBillDump = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Moved to Reject Bin[ %d ]", NoOfBillDump );

								AtmReq += 2 ;//No of Bills in reject Cassette moved
								AtmReq += 3 ;//Reserved Fields
								DispencedAmount +=( NoOfBills * Denomination  );
								trace( DEBUG_NORMAL, "Denomination[%d] DispencedAmount[%d]", Denomination, DispencedAmount );
							}
							else
								AtmReq += 7;
							trace( "4{ %s }", AtmReq );
							CassPos = *AtmReq++;//Cassette Position moved
							DenominationId = *AtmReq++;
							DenominationId = toupper( DenominationId );
							trace( DEBUG_NORMAL, "Cassette Position[ %c ] Denomination[ %c ]", CassPos, DenominationId);
							if( DenominationId != '@' && DenominationId != '_')
							{
								if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
									trace( DEBUG_ERROR, "Unable to get Denomination for DenominationId[ %c ]", DenominationId );

								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBills = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Dispensed[ %d ]", NoOfBills );
								PackDispLogicBuf( Temp, DenominationId, DispLogicBuf );
								if( !strcmp( DispErrCode, "20" ) )
									CheckAndSetDenomStatus( DIEBOLD, Temp, DenominationId, denominfo );

								AtmReq += 2 ;//No of Bills moved
								memset( Temp, 0, sizeof(Temp) );
								strncpy( Temp, AtmReq, 2 );
								NoOfBillDump = atoi( Temp  );
								trace( DEBUG_NORMAL, "No of Bills Moved to Reject Bin[ %d ]", NoOfBillDump );

								AtmReq += 2 ;//No of Bills in reject Cassette moved
								AtmReq += 3 ;//Reserved Fields
								DispencedAmount += ( NoOfBills * Denomination  );
								trace( DEBUG_NORMAL, "Denomination[%d] DispencedAmount[%d]", Denomination, DispencedAmount );
							}
							else
								AtmReq += 7;
							//trace( DEBUG_TEST, "A<%c>B<%c>C<%c>D<%c>E<%c>F<%c>G<%c>H<%c>ALL<%c>", DenomStatus.A,DenomStatus.B,DenomStatus.C,DenomStatus.D,DenomStatus.E,DenomStatus.F,DenomStatus.G,DenomStatus.H,DenomStatus.All);
							//Coping Dispensing logic to Memory
							memset( atmbuf.DispenceLogicBuf, 0, sizeof(atmbuf.DispenceLogicBuf) );
							strcpy( atmbuf.DispenceLogicBuf, DispLogicBuf );
							sprintf( ConsumerReq.DispAmount, "%d.00", DispencedAmount );
							//memset( atmbuf.DenominationBuf, 0, sizeof( atmbuf.DenominationBuf ) );
							//memcpy( atmbuf.DenominationBuf, &DenomStatus, sizeof( struct AtmDenominationStatus ) );
							break;

                    default:
                        	trace( DEBUG_NORMAL, "Full Reversal" );
							ConsumerReq.RespCode = EZLINK_RC_UnableDispense ;
							break ;
                }
		        break;
		case '@':
				trace( DEBUG_NORMAL, "UncertainDispense" );

				StatusCode += BuiltStatusCode( ( char * )"!UD", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!UD", atmbuf.StaticStatus );

				AtmReq += 3;//3 bytes
				if( strlen( AtmReq ) != 0 )
				{
					AtmReq ++;//0x1C
					AtmReq += 3;//3 bytes
					trace( DEBUG_NORMAL,"Status Message[%s]", AtmReq );
					if( !strcmp( AtmReq, ( char * )"DR01:23:00:00" ) || !strcmp( AtmReq, ( char * )"DR01:23:00:01" ) || !strcmp( AtmReq, ( char * )"DR01:23:00:30" ) )
						ConsumerReq.RespCode = EZLINK_RC_UncertainDispense;
					else
						ConsumerReq.RespCode = EZLINK_RC_UnableDispense;
				}
				else
					ConsumerReq.RespCode = EZLINK_RC_UncertainDispense;

			    break;
		case ';':
                trace( DEBUG_NORMAL, "Full Reversal" );
                ConsumerReq.RespCode = EZLINK_RC_UnableDispense ;
                break ;

		case '2':
				trace( DEBUG_NORMAL, "printer solicited status" );
				AtmReq ++;//byte 0
				memset( Byte, 0, sizeof(Byte) );
				strncpy( Byte, AtmReq, 2 );
				for( i = 0; i < 8; i++ )
				{
					if( IsBitSet( Byte, (short)i + 1 ) == 1 )
					{
						switch( i )
						{
						case 0:
							trace( DEBUG_NORMAL, "Journal printer fault" );
							StatusCode += BuiltStatusCode( ( char * )"!JP", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!JP", atmbuf.StaticStatus );

							AtmReq += 2;//byte 1
							AtmReq += 2;//byte 2
							memset( Byte, 0, sizeof(Byte) );
							strncpy( Byte, AtmReq, 2 );
							for( i = 0; i < 8; i++ )
							{
								if( IsBitSet( Byte, (short)i + 1 ) == 1 )
								{
									switch( i )
									{
										case 0:
											trace( DEBUG_NORMAL, "Fault occurred during line print" );
											StatusCode += BuiltStatusCode( ( char * )"JP18", 4, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP18", atmbuf.StaticStatus );
											break;

										case 1:
											trace( DEBUG_NORMAL, "Fault occurred during a head return" );
											StatusCode += BuiltStatusCode( ( char * )"JP19", 4, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP19", atmbuf.StaticStatus );
											break;

										case 2:
											trace( DEBUG_NORMAL, "Fault occurred during a head return and line feed" );
											StatusCode += BuiltStatusCode( ( char * )"JP20", 4, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP20", atmbuf.StaticStatus );
											break;

										case 5:
											trace( DEBUG_NORMAL, "Run low on paper" );
											StatusCode += BuiltStatusCode( ( char * )"JP21", 4, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP21", atmbuf.StaticStatus );
											break;

										case 6:
											trace( DEBUG_NORMAL, "Electrical fault detected on ready line of journal printer" );
											StatusCode += BuiltStatusCode( ( char * )"JP22", 4, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP22", atmbuf.StaticStatus );
											break;

										case 7:
											trace( DEBUG_NORMAL, "Run out of Paper" );
											StatusCode += BuiltStatusCode( ( char * )"JP23", 4, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP23", atmbuf.StaticStatus );
											break;

										default:
											trace( DEBUG_NORMAL, "unsupported bit" );
											break;
									}
								}
							}
							break;

						case 1:
							trace( DEBUG_NORMAL, "Consumer printer fault" );
							StatusCode += BuiltStatusCode( ( char * )"!CP", 2, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CP", atmbuf.StaticStatus );
							AtmReq += 2;//byte 1
							memset( Byte, 0, sizeof(Byte) );
							strncpy( Byte, AtmReq, 2 );
							for( i = 0; i < 8; i++ )
							{
								if( IsBitSet( Byte, (short)i + 1 ) == 1 )
								{
									switch( i )
									{
										case 0:
											trace( DEBUG_NORMAL, "Fault occurred during line print" );
											StatusCode += BuiltStatusCode( ( char * )"CP1", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP1", atmbuf.StaticStatus );
											break;

										case 1:
											trace( DEBUG_NORMAL, "Fault occurred during a head return" );
											StatusCode += BuiltStatusCode( ( char * )"CP2", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP2", atmbuf.StaticStatus );
											break;

										case 2:
											trace( DEBUG_NORMAL, "Fault occurred during a head return and line feed" );
											StatusCode += BuiltStatusCode( ( char * )"CP3", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP3", atmbuf.StaticStatus );
											break;

										case 3:
											trace( DEBUG_NORMAL, "Fault occurred during a top of form search" );
											StatusCode += BuiltStatusCode( ( char * )"CP4", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP4", atmbuf.StaticStatus );
											break;

										case 5:
											trace( DEBUG_NORMAL, "Run out of Paper" );
											StatusCode += BuiltStatusCode( ( char * )"CP5", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP5", atmbuf.StaticStatus );
											break;

										case 7:
											trace( DEBUG_NORMAL, "Run low on paper" );
											StatusCode += BuiltStatusCode( ( char * )"CP6", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP6", atmbuf.StaticStatus );
											break;

										default:
											trace( DEBUG_NORMAL, "unsupported bit" );
											break;
									}
								}
							}
							break;

						case 2:
							trace( DEBUG_NORMAL, "Statement printer fault" );
							StatusCode += BuiltStatusCode( ( char * )"!SP", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!SP", atmbuf.StaticStatus );
							break;

						case 3:
							trace( DEBUG_NORMAL, "Passbook printer fault" );
							StatusCode += BuiltStatusCode( ( char * )"!PP", 2, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!PP", atmbuf.StaticStatus );
							break;

						case 4:
							trace( DEBUG_NORMAL, "Data format error,cannot print" );
							StatusCode += BuiltStatusCode( ( char * )"!DFE", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DFE", atmbuf.StaticStatus );
							break;

						case 7:
							trace( DEBUG_NORMAL, "Print operation complete" );
							StatusCode += BuiltStatusCode( ( char * )"SP6", 3, StatusCode );
							break;

						default:
							trace( DEBUG_NORMAL, "unsupported bit" );
							break;
					}
				}
			}
			break;

		case '3':
			trace( DEBUG_NORMAL, "Securomatic solicited status" );
			StatusCode += BuiltStatusCode( ( char * )"!SSS", 4, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!SSS", atmbuf.StaticStatus );
			AtmReq ++ ;//byte 0
			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 0:
							trace( DEBUG_NORMAL, "AHD will not open" );
							StatusCode += BuiltStatusCode( ( char * )"SSS1", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS1", atmbuf.StaticStatus );
							break;

						case 1:
							trace( DEBUG_NORMAL, "AHD will not lock" );
							StatusCode += BuiltStatusCode( ( char * )"SSS2", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS2", atmbuf.StaticStatus );
							break;

						case 2:
							trace( DEBUG_NORMAL, "cycle complete" );
							StatusCode += BuiltStatusCode( ( char * )"SSS3", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS3", atmbuf.StaticStatus );
							break;

						case 3:
							trace( DEBUG_NORMAL, "Door locked" );
							StatusCode += BuiltStatusCode( ( char * )"SSS4", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS4", atmbuf.StaticStatus );
							break;

						case 4:
							trace( DEBUG_NORMAL, "Bag not seen in chest throat" );
							StatusCode += BuiltStatusCode( ( char * )"SSS5", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS5", atmbuf.StaticStatus );
							break;

						case 5:
							trace( DEBUG_NORMAL, "Bin full or bag jammed sensor" );
							StatusCode += BuiltStatusCode( ( char * )"SSS6", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS6", atmbuf.StaticStatus );
							break;

						case 6:
							trace( DEBUG_NORMAL, "Door opened at timeout or cancel" );
							StatusCode += BuiltStatusCode( ( char * )"SSS7", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SSS7", atmbuf.StaticStatus );
							break;

						default:
							trace( DEBUG_NORMAL, "unsupported bit" );
							break;
					}
				}
			}
			break;

		case '>':
			trace( DEBUG_NORMAL, "card reader solicited status" );
			StatusCode += BuiltStatusCode( ( char * )"!CR", 3, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CR", atmbuf.StaticStatus );
			AtmReq ++;//byte 0
			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 5:
							trace( DEBUG_NORMAL, "Card capture failure" );
							StatusCode += BuiltStatusCode( ( char * )"CR26", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR26", atmbuf.StaticStatus );
							break;

						case 6:
							trace( DEBUG_NORMAL, "Card return timeout" );
							StatusCode += BuiltStatusCode( ( char * )"CR27", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR27", atmbuf.StaticStatus );
							break;

						case 7:
							trace( DEBUG_NORMAL, "Card return failure" );
							AtmReq += 2;//byte 1
							memset( Byte, 0, sizeof(Byte) );
							strncpy( Byte, AtmReq, 2 );
							for( i = 0; i < 8; i++ )
							{
								if( IsBitSet( Byte, (short)i + 1 ) == 0 )
								{
								switch( i )
								{
									case 0:
										trace( DEBUG_NORMAL, "Card in rear" );
										StatusCode += BuiltStatusCode( ( char * )"CR23", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR23", atmbuf.StaticStatus );
										break;

									case 1:
										trace( DEBUG_NORMAL, "Hard fault" );
										StatusCode += BuiltStatusCode( ( char * )"CR24", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR24", atmbuf.StaticStatus );
										break;

									case 2:
										trace( DEBUG_NORMAL, "Soft failure" );
										StatusCode += BuiltStatusCode( ( char * )"CR25", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR25", atmbuf.StaticStatus );
										break;

									case 3:
										trace( DEBUG_NORMAL, "Card in retain position" );
										StatusCode += BuiltStatusCode( ( char * )"CR3", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR3", atmbuf.StaticStatus );
										break;

									case 4:
										trace( DEBUG_NORMAL, "Track 3 read error" );
										StatusCode += BuiltStatusCode( ( char * )"CR19", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR19", atmbuf.StaticStatus );
										break;

									case 5:
										trace( DEBUG_NORMAL, "Track 2 read error" );
										StatusCode += BuiltStatusCode( ( char * )"CR20", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR20", atmbuf.StaticStatus );
										break;

									case 6:
										trace( DEBUG_NORMAL, "Track 1 read error" );
										StatusCode += BuiltStatusCode( ( char * )"CR21", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR21", atmbuf.StaticStatus );
										break;

									case 7:
										trace( DEBUG_NORMAL, "Read operation complete" );
										StatusCode += BuiltStatusCode( ( char * )"CR14", 4, StatusCode );
										break;

									default:
										trace( DEBUG_NORMAL, "unsupported bit" );
										break;
								}
							}
							}
							break;

						default:
							trace( DEBUG_NORMAL, "unsupported bit" );
							break;
					}
				}
			}
			break;

		case 'A':
			trace( DEBUG_NORMAL, "depository status information" );
			StatusCode += BuiltStatusCode( ( char * )"!DS", 3, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DS", atmbuf.StaticStatus );
			AtmReq ++ ;//byte 0
			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 0:
							trace( DEBUG_NORMAL, "Soft fault" );
							StatusCode += BuiltStatusCode( ( char * )"DF6", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF6", atmbuf.StaticStatus );
							break;

						case 1:
							trace( DEBUG_NORMAL, "Deposit cassette full" );
							StatusCode += BuiltStatusCode( ( char * )"DF7", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF7", atmbuf.StaticStatus );
							break;

						case 2:
							trace( DEBUG_NORMAL, "Deposit incomplete or Depository not present" );
							StatusCode += BuiltStatusCode( ( char * )"DF8", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF8", atmbuf.StaticStatus );
							break;

						case 3:
							trace( DEBUG_NORMAL, "Deposit cassette not present" );
							StatusCode += BuiltStatusCode( ( char * )"DF9", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF9", atmbuf.StaticStatus );
							break;

						case 4:
							trace( DEBUG_NORMAL, "Customer timeout" );
							StatusCode += BuiltStatusCode( ( char * )"DF10", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF10", atmbuf.StaticStatus );
							break;

						case 5:
							trace( DEBUG_NORMAL, "Printer error" );
							AtmReq += 2;//byte 1
							memset( Byte, 0, sizeof(Byte) );
							strncpy( Byte, AtmReq, 2 );
							for( i = 0; i < 8; i++ )
							{
								if( IsBitSet( Byte, (short)i + 1 ) == 1 )
								{
									switch( i )
									{
										case 0:
											trace( DEBUG_NORMAL, "Unit module error" );
											StatusCode += BuiltStatusCode( ( char * )"IF1", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IF1", atmbuf.StaticStatus );
											break;

										case 1:
											trace( DEBUG_NORMAL, "Tens module error" );
											StatusCode += BuiltStatusCode( ( char * )"IF2", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IF2", atmbuf.StaticStatus );
											break;

										case 2:
											trace( DEBUG_NORMAL, "Hundreds module error" );
											StatusCode += BuiltStatusCode( ( char * )"IF3", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IF3", atmbuf.StaticStatus );
											break;

										case 3:
											trace( DEBUG_NORMAL, "Thousands module error" );
											StatusCode += BuiltStatusCode( ( char * )"IF4", 3, StatusCode );
											BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IF4", atmbuf.StaticStatus );
											break;

										case 4:
											trace( DEBUG_NORMAL, "Customer cancel" );
											StatusCode += BuiltStatusCode( ( char * )"IF5", 3, StatusCode );
											break;

										default:
											trace( DEBUG_NORMAL, "unsupported bit" );
											break;
									}
								}
							}
							break;

						case 6:
							trace( DEBUG_NORMAL, "Hard fault" );
							StatusCode += BuiltStatusCode( ( char * )"DF12", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF12", atmbuf.StaticStatus );
							break;

						default:
							trace( DEBUG_NORMAL, "unsupported bit" );
							break;
					}
				}
			}
			break;

		case '<':

			trace( DEBUG_NORMAL, "Configuration ID Status" );
			AtmReq ++ ;//byte 0
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 4 );
			trace( DEBUG_NORMAL, "Configuration ID: %s", Byte );
			if( atminfo.AtmConfigId != atoi( Byte ) )
			{
				memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
				AtmCont.MsgType = EZ_ATM_DOWNLOAD_REQ;
				AtmCont.DownloadType = DOWNLOAD_ALL;
				memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

				if( PostContMsg( AtmCont, AtmId ) < 0 )
				{
					trace( "Failed in PostContMsg" );
					return -1;
				}
			}
			else
			{
				memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
				AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
				AtmCont.DownloadType = GO_IN_SERVICE;
				memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

				if( PostContMsg( AtmCont, AtmId ) < 0 )
				{
					trace( "Failed in PostContMsg" );
					return -1;
				}
			}

			AtmReq += 4 ;//byte 1 & 2 moved
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, ( short )i + 1 ) == 1 )
				{
					switch( i )
					{
						case 6:
							trace( DEBUG_NORMAL, "Supervisor switch activated" );
							break;

						case 5:
							trace( DEBUG_NORMAL, "Supply switch activated" );
							break;

						default:
							trace( DEBUG_NORMAL, "UnSupported Bit" );
							break;
					}
				}
			}
			AtmReq += 2 ;//byte 3 moved
			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 0:
							trace( DEBUG_NORMAL, "Go In-Service Flag" );
							break;

						default:
							trace( DEBUG_NORMAL, "UnSupported Bit" );
							break;

					}
				}
			}
			break;// for '<'

		case 'D':
			trace( DEBUG_NORMAL, "Cassette solicited status" );
			StatusCode += BuiltStatusCode( ( char * )"!CSS", 4, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CSS", atmbuf.StaticStatus );
			AtmReq ++ ;//byte 0
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );// cassette 1
			if( ( strncmp( Byte, "=?", 2 ) == 0 ) || ( strncmp( Byte, "<0", 2 ) == 0 ) )
			{
				trace( DEBUG_NORMAL, "No Feed Module for Cassette 1" );
				StatusCode += BuiltStatusCode( ( char * )"C1-N", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C1-N", atmbuf.StaticStatus );
			}
			else
			{
				switch ( Byte[0] )
				{
					case '<':
						if ( Byte[1] == ':')
						{
							trace( DEBUG_NORMAL, "Cassette 1 -Denomination ID Cannot Be Read" );
							StatusCode += BuiltStatusCode( ( char * )"C1-D", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C1-D", atmbuf.StaticStatus );
						}
						else
						{
							trace( DEBUG_NORMAL, "Cassette 1 Normal Condition" );
							StatusCode += BuiltStatusCode( ( char * )"C1-1", 4, StatusCode );
						}
						break;

					case '>':
						trace( DEBUG_NORMAL, "Cassette 1 Currency Supply Low" );
						StatusCode += BuiltStatusCode( ( char * )"C1-L", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C1-L", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "UnSupported Bit" );
						break;
				}
			}
			AtmReq += 2 ;//byte 1 & 2

			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );// cassette 2
			if( (strncmp(Byte, "=?", 2) == 0 ) || (strncmp(Byte, "<0", 2) == 0 ) )
			{
				trace( DEBUG_NORMAL, "No Feed Module for Cassette 2" );
				StatusCode += BuiltStatusCode( ( char * )"C2-N", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C2-N", atmbuf.StaticStatus );
			}
			else
			{
				switch ( Byte[0] )
				{
					case '<':
						if ( Byte[1] == ':')
						{
							trace( DEBUG_NORMAL, "Cassette 2 -Denomination ID Cannot Be Read" );
							StatusCode += BuiltStatusCode( ( char * )"C2-D", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C2-D", atmbuf.StaticStatus );
						}
						else
						{
							trace( DEBUG_NORMAL, "Cassette 2 Normal Condition" );
							StatusCode += BuiltStatusCode( ( char * )"C2-1", 4, StatusCode );
						}
						break;

					case '>':
						trace( DEBUG_NORMAL, "Cassette 2 Currency Supply Low" );
						StatusCode += BuiltStatusCode( ( char * )"C2-L", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C2-L", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "UnSupported Bit" );
						break;
				}
			}
			AtmReq += 2 ;//byte 3 & 4

			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );// cassette 3
			if( (strncmp(Byte, "=?", 2) == 0 ) || (strncmp(Byte, "<0", 2) == 0 ) )
			{
				trace( DEBUG_NORMAL, "No Feed Module for Cassette 3" );
				StatusCode += BuiltStatusCode( ( char * )"C3-N", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C3-N", atmbuf.StaticStatus );
			}
			else
			{
				switch ( Byte[0] )
				{
					case '<':
						if ( Byte[1] == ':')
						{
							trace( DEBUG_NORMAL, "Cassette 3 -Denomination ID Cannot Be Read" );
							StatusCode += BuiltStatusCode( ( char * )"C3-D", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C3-D", atmbuf.StaticStatus );
						}
						else
						{
							trace( DEBUG_NORMAL, "Cassette 3 Normal Condition" );
							StatusCode += BuiltStatusCode( ( char * )"C3-1", 4, StatusCode );
						}
						break;

					case '>':
						trace( DEBUG_NORMAL, "Cassette 3 Currency Supply Low" );
						StatusCode += BuiltStatusCode( ( char * )"C3-L", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C3-L", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "UnSupported Bit" );
						break;
				}
			}
			AtmReq += 2;

			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );// cassette 4
			if( (strncmp(Byte, "=?", 2) == 0 ) || (strncmp(Byte, "<0", 2) == 0 ) )
			{
				trace( DEBUG_NORMAL, "No Feed Module for Cassette 4" );
				StatusCode += BuiltStatusCode( ( char * )"C4-N", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C4-N", atmbuf.StaticStatus );
			}
			else
			{
				switch ( Byte[0] )
				{
					case '<':
						if ( Byte[1] == ':' )
						{
							trace( DEBUG_NORMAL, "Cassette 4 -Denomination ID Cannot Be Read" );
							StatusCode += BuiltStatusCode( ( char * )"C4-D", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C4-D", atmbuf.StaticStatus );
						}
						else
						{
							trace( DEBUG_NORMAL, "Cassette 4 Normal Condition" );
							StatusCode += BuiltStatusCode( ( char * )"C4-1", 4, StatusCode );
						}
						break;

					case '>':
						trace( DEBUG_NORMAL, "Cassette 4 Currency Supply Low" );
						StatusCode += BuiltStatusCode( ( char * )"C4-L", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"C4-L", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "UnSupported Bit" );
						break;
				}
			}
			break;// for 'D'

		case 'H':
			trace( DEBUG_NORMAL, "Supply Counts" );
			trace( DEBUG_DUMP, "[ %s ]", AtmReq );

			memset( &CounterInfo, 0, sizeof( struct EzAtmCounterInfo ) );
			strcpy( CounterInfo.AtmId, AtmId );
			strcpy( CounterInfo.DeviceLogicalGroup, atminfo.AtmLogicalGroup );

			AtmReq++;
			memset( Temp, 0, sizeof( Temp ) );
			p = ( char * ) memchr( AtmReq, DEVICE_GS, Size );
			memcpy( Temp, AtmReq, ( p - AtmReq) );
			AtmReq += strlen( Temp +1 );
			if( strlen( Temp ) != 0 )
			{
				p = Temp;
				memset( temp, 0, sizeof( temp ) );
				strncpy( temp, p, 4 );
				trace( DEBUG_NORMAL, " Depositor Id [ %s ]", temp );
				p += 4;
				CounterInfo.TotalDeposit = atoi(p);
				trace( DEBUG_NORMAL, " Depositor count [ %d ]", atoi(p) );
			}
			AtmReq ++; //0x1D moved

			trace( DEBUG_DUMP, "[ %s ]", AtmReq );
			memset( Temp, 0, sizeof( Temp ) );
			p = ( char * ) memchr( AtmReq, DEVICE_GS, Size  );
			memcpy( Temp, AtmReq, ( p - AtmReq)  );
			AtmReq += ( strlen( Temp +1 )  );
			if( strlen( Temp ) != 0 )
			{
				p = Temp;
				memset( temp, 0, sizeof( temp ) );
				strncpy( temp, p, 4 );
				trace( DEBUG_NORMAL, " Card Reader Id [ %s ]", temp );
				p += 4;
				strcpy( RejectCard, p );
				CounterInfo.TotalCardRetained = atoi( RejectCard );
				trace( DEBUG_NORMAL, " Retained Card count [ %s ]", RejectCard );
			}
			AtmReq ++; //0x1D moved
			AtmReq ++;
			trace( DEBUG_DUMP, "[ %s ]", AtmReq );
			p = AtmReq;
			memset( temp, 0, sizeof( temp ) );
			strncpy( temp, p, 4 );
			trace( DEBUG_NORMAL, " Dispenser Id [ %s ]", temp );
			p += 4;
			p++;//0x1E Record Seperator
			DenominationId = *p++;
			DenominationId = toupper( DenominationId );
			trace( DEBUG_NORMAL, "Cassette Type 1 - Denomination ID [ %c ]", DenominationId );
			DenominationId = *p++;
			DenominationId = toupper( DenominationId );
			trace( DEBUG_NORMAL, "Cassette Type 2 - Denomination ID [ %c ]", DenominationId );
			DenominationId = *p++;
			DenominationId = toupper( DenominationId );
			trace( DEBUG_NORMAL, "Cassette Type 3 - Denomination ID [ %c ]", DenominationId );
			DenominationId = *p++;
			DenominationId = toupper( DenominationId );
			trace( DEBUG_NORMAL, "Cassette Type 4 - Denomination ID [ %c ]", DenominationId );
			p++;//0x1E Record Seperator

			memset( temp, 0, sizeof( temp ) );
			strncpy( temp, p, 5 );
			CounterInfo.TotalBillReject = atoi( temp );
			trace( DEBUG_NORMAL, "Notes Diverted into Reject cassette :%d", CounterInfo.TotalBillReject );

			p += 5;
			memset( NotesDisp1, 0, sizeof(NotesDisp1) );
			strncpy( NotesDisp1, p, 5 );
			CounterInfo.Cass1_NotesDisp = atoi( NotesDisp1 );
			trace( DEBUG_NORMAL, " Total bills dispensed - cassette position 1 [ %s ]", NotesDisp1 );

			p += 5;
			memset( NotesDisp2, 0, sizeof(NotesDisp2) );
			strncpy( NotesDisp2, p, 5 );
			CounterInfo.Cass2_NotesDisp = atoi( NotesDisp2 );
			trace( DEBUG_NORMAL, " Total bills dispensed - cassette position 2 [ %s ]", NotesDisp2 );

			p += 5;
			memset( NotesDisp3, 0, sizeof(NotesDisp3) );
			strncpy( NotesDisp3, p, 5 );
			CounterInfo.Cass3_NotesDisp = atoi( NotesDisp3 );
			trace( DEBUG_NORMAL, " Total bills dispensed - cassette position 3 [ %s ]", NotesDisp3 );

			p += 5;
			memset( NotesDisp4, 0, sizeof(NotesDisp4) );
			strncpy( NotesDisp4, p, 5 );
			CounterInfo.Cass4_NotesDisp = atoi( NotesDisp4 );
			trace( DEBUG_NORMAL, " Total bills dispensed - cassette position 4 [ %s ]", NotesDisp4 );

			p += 5;
			CounterInfo.TotalDump = atoi( p );
			trace( DEBUG_NORMAL, "Notes Dumped into Reject cassette :%d", CounterInfo.TotalDump );

			if( UpdateCounterInfo( &CounterInfo, atmbuf.CurrentCommand ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in updating Counter info for [%s]", CounterInfo.AtmId );
				return -1;
			}
			break;

		default:
			trace( DEBUG_NORMAL, "Not a Status bit" );
			return -1;
			break;
	}

	if ( DID == '@' || DID == '?' || DID == '8' || DID == '9' || DID == ';')
	{
		ConsumerReq.MsgType = EZLINK_TXN_ReversalAdviceRequest;
		if( DispencedAmount == 0 )
		{
			if( ConsumerReq.RespCode != EZLINK_RC_UncertainDispense )
				ConsumerReq.RespCode = EZLINK_RC_UnableDispense;
		}

        if( ConsumerReq.RespCode == EZLINK_RC_PartialDispense )
        {
                if( ezatmproperty.PartialReversalReq == 'N' )
                {
                        ConsumerReq.RespCode = EZLINK_RC_UnableDispense;
                        RevFlag = true;
                }
        }

		//atmbuf.CurrentState = REVERSAL;
        memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

		memset( &atmbuf.DevMsg, 0, sizeof( struct EzDevMsg ) );
		memcpy( &atmbuf.DevMsg, &ConsumerReq, sizeof( struct EzDevMsg ) );

		if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
			ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
			ConsumerReq.RespCode = EZLINK_RC_UnableToProcess;

			if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
				trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");

			return -1;
		}

		trace( DEBUG_NORMAL, "Routing to BuildAndPostFuncMsg");

        //if(  RevFlag == true )
        	//ConsumerReq.RespCode = EZLINK_RC_LowCash;

        ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
        if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
        {
                trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
                return -1;
        }
	}
	else
	{
		memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

		if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
			trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
		else
			trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", AtmId );
	}
	return 1;
}

void EzD912 :: getDispenserErrorCode( int DispenserErrorCode, char *DispenserErrorStr )
{
	switch( DispenserErrorCode )
	{
		case 1:
			trace( DEBUG_NORMAL,"Unsolicited bill from cassette position 1 (top)" );
			strcpy( DispenserErrorStr, "D01" );
			break;

		case 2:
			trace( DEBUG_NORMAL,"Unsolicited bill from cassette position 2" );
			strcpy( DispenserErrorStr, "D02" );
			break;

		case 3:
			trace( DEBUG_NORMAL,"Unsolicited bill from cassette position 3" );
			strcpy( DispenserErrorStr, "D03" );
			break;

		case 4:
			trace( DEBUG_NORMAL,"Unsolicited bill from cassette position 4 (bottom)" );
			strcpy( DispenserErrorStr, "D04" );
			break;

		case 9:
			trace( DEBUG_NORMAL,"Stream feed from cassette position 1 (top)" );
			strcpy( DispenserErrorStr, "D09" );
			break;

		case 10:
			trace( DEBUG_NORMAL,"Stream feed from cassette position 2" );
			strcpy( DispenserErrorStr, "D10" );
			break;

		case 11:
			trace( DEBUG_NORMAL,"Stream feed from cassette position 3" );
			strcpy( DispenserErrorStr, "D11" );
			break;

		case 12:
			trace( DEBUG_NORMAL,"Stream feed from cassette position 4 (bottom)" );
			strcpy( DispenserErrorStr, "D12" );
			break;

		case 17:
			trace( DEBUG_NORMAL,"Feed Failure from cassette position 1 (top)" );
			strcpy( DispenserErrorStr, "D17" );
			break;

		case 18:
			trace( DEBUG_NORMAL,"Feed Failure from cassette position 2" );
			strcpy( DispenserErrorStr, "D18" );
			break;

		case 19:
			trace( DEBUG_NORMAL,"Feed Failure from cassette position 3" );
			strcpy( DispenserErrorStr, "D19" );
			break;

		case 20:
			trace( DEBUG_NORMAL,"Feed Failure from cassette position 4 (bottom)" );
			strcpy( DispenserErrorStr, "D20" );
			break;

		case 25:
			trace( DEBUG_NORMAL,"Jam before double-detect switch from cassette position 1 (top)" );
			strcpy( DispenserErrorStr, "D25" );
			break;

		case 26:
			trace( DEBUG_NORMAL,"Jam before double-detect switch from cassette position 2" );
			strcpy( DispenserErrorStr, "D26" );
			break;

		case 27:
			trace( DEBUG_NORMAL,"Jam before double-detect switch from cassette position 3" );
			strcpy( DispenserErrorStr, "D27" );
			break;

		case 28:
			trace( DEBUG_NORMAL,"Jam before double-detect switch from cassette position 4 (bottom)" );
			strcpy( DispenserErrorStr, "D28" );
			break;

		case 33:
			trace( DEBUG_NORMAL,"Jam between double-detect switch and exit throat" );
			strcpy( DispenserErrorStr, "D33" );
			break;

		case 34:
			trace( DEBUG_NORMAL,"Jam between double-detect switch and divert throat" );
			strcpy( DispenserErrorStr, "D34" );
			break;

		case 35:
			trace( DEBUG_NORMAL,"Denomination error" );
			strcpy( DispenserErrorStr, "D35" );
			break;

		case 36:
			trace( DEBUG_NORMAL,"Unidentified cassette" );
			strcpy( DispenserErrorStr, "D36" );
			break;

		case 37:
			trace( DEBUG_NORMAL,"During dispenses, the diverter will not go to the exit position" );
			strcpy( DispenserErrorStr, "D37" );
			break;

		case 38:
			trace( DEBUG_NORMAL,"During dispenses, the diverter will not go to the divert position" );
			strcpy( DispenserErrorStr, "D38" );
			break;

		case 39:
			trace( DEBUG_NORMAL,"Double bill dispensed" );
			strcpy( DispenserErrorStr, "D39" );
			break;

		case 40:
			trace( DEBUG_NORMAL,"Long or Short bill dispensed" );
			strcpy( DispenserErrorStr, "D40" );
			break;

		case 41:
			trace( DEBUG_NORMAL,"Feed and single counted bills are not equal from cassette position 1 (top)" );
			strcpy( DispenserErrorStr, "D41" );
			break;

		case 42:
			trace( DEBUG_NORMAL,"Feed and single counted bills are not equal from cassette position 2" );
			strcpy( DispenserErrorStr, "D42" );
			break;

		case 43:
			trace( DEBUG_NORMAL,"Feed and single counted bills are not equal from cassette position 3" );
			strcpy( DispenserErrorStr, "D43" );
			break;

		case 44:
			trace( DEBUG_NORMAL,"Feed and single counted bills are not equal from cassette position 4 (bottom)" );
			strcpy( DispenserErrorStr, "D44" );
			break;

		case 49:
			trace( DEBUG_NORMAL,"Single and exit counted bills are not equal from cassette position 1 (top)" );
			strcpy( DispenserErrorStr, "D49" );
			break;

		case 50:
			trace( DEBUG_NORMAL,"Single and exit counted bills are not equal from cassette position 2" );
			strcpy( DispenserErrorStr, "D50" );
			break;

		case 51:
			trace( DEBUG_NORMAL,"Single and exit counted bills are not equal from cassette position 3" );
			strcpy( DispenserErrorStr, "D51" );
			break;

		case 52:
			trace( DEBUG_NORMAL,"Single and exit counted bills are not equal from cassette position 4 (bottom)" );
			strcpy( DispenserErrorStr, "D52" );
			break;

		case 57:
			trace( DEBUG_NORMAL,"Dispenser received invalid data" );
			strcpy( DispenserErrorStr, "D57" );
			break;

		case 58:
			trace( DEBUG_NORMAL,"Too many bills dispensed" );
			strcpy( DispenserErrorStr, "D58" );
			break;

		case 59:
			trace( DEBUG_NORMAL,"Timing wheel error" );
			strcpy( DispenserErrorStr, "D59" );
			break;

		case 60:
			trace( DEBUG_NORMAL,"Feed, exit, or divert sensor blocked" );
			strcpy( DispenserErrorStr, "D60" );
			break;

		case 63:
			trace( DEBUG_NORMAL,"Dispenser RAM error" );
			strcpy( DispenserErrorStr, "D63" );
			break;

		case 64:
			trace( DEBUG_NORMAL,"Dispenser USART error" );
			strcpy( DispenserErrorStr, "D64" );
			break;

		case 65:
			trace( DEBUG_NORMAL,"Cassettes shuffled" );
			strcpy( DispenserErrorStr, "D65" );
			break;

		case 67:
			trace( DEBUG_NORMAL,"Diverter will not energize" );
			strcpy( DispenserErrorStr, "D67" );
			break;

		case 68:
			trace( DEBUG_NORMAL,"Diverter in wrong position at start of dispense" );
			strcpy( DispenserErrorStr, "D68" );
			break;

		case 78:
			trace( DEBUG_NORMAL,"Divert cassette is full" );
			strcpy( DispenserErrorStr, "D78" );
			break;

		case 79:
			trace( DEBUG_NORMAL,"Divert cassette is not present" );
			strcpy( DispenserErrorStr, "D79" );
			break;

		case 80:
			trace( DEBUG_NORMAL,"No cassette in feed module for test dispense" );
			strcpy( DispenserErrorStr, "D80" );
			break;

		case 81:
			trace( DEBUG_NORMAL,"Dispense timeout" );
			strcpy( DispenserErrorStr, "D81" );
			break;

		case 83:
			trace( DEBUG_NORMAL,"Linear Variable Differential Transformer (LVDT) double-detect, out of limits" );
			strcpy( DispenserErrorStr, "D83" );
			break;

		case 84:
			trace( DEBUG_NORMAL,"Purge error following dispense error " );
			strcpy( DispenserErrorStr, "D84" );
			break;

		case 90:
			trace( DEBUG_NORMAL,"Communication timeout" );
			strcpy( DispenserErrorStr, "D90" );
			break;

		case 91:
			trace( DEBUG_NORMAL,"Communication data invalid" );
			strcpy( DispenserErrorStr, "D91" );
			break;

		case 92:
			trace( DEBUG_NORMAL,"Excessive NAKs for a command" );
			strcpy( DispenserErrorStr, "D92" );
			break;

		case 94:
			trace( DEBUG_NORMAL,"Unreported problem with feed module 1 (top)" );
			strcpy( DispenserErrorStr, "D94" );
			break;

		case 95:
			trace( DEBUG_NORMAL,"Unreported problem with feed module 2" );
			strcpy( DispenserErrorStr, "D95" );
			break;

		case 96:
			trace( DEBUG_NORMAL,"Unreported problem with feed module 3" );
			strcpy( DispenserErrorStr, "D96" );
			break;

		case 97:
			trace( DEBUG_NORMAL,"Unreported problem with feed module 4 (bottom)" );
			strcpy( DispenserErrorStr, "D97" );
			break;

		default:
			trace( DEBUG_NORMAL,"Not Used" );
			break;
	}
}

int EzD912 :: ServeConsumerRequests( char * AtmReq, int Size , char *AtmId )
{
	char Luno[ LUNO_SIZE + 1 ], TrimOpKeyBuf[ OPKEY_SIZE + 1 ], OpKeyBuf[ OPKEY_SIZE + 1 ], OpKeyAmount[ AMOUNT_SIZE + 1 ];
	char InDirectState[ ISTATE + 1 ], DispLogicBuf[ DISP + 1 ];
	char DollarEntry[ AMOUNT_SIZE + 1 ], PinBuf[ TEMP + 1 ], GenBufB[ TEMP + 1 ], GenBufC[ TEMP + 1 ];
	char temp[ TEMP + 1 ], Date[ 11 ], Time[ 11 ];
	char CurrencyCode[ 5 ], PrinterFlag[ 3 ], TxnReqFlag[ 3 ];
	char FileName[ FILENAME_SIZE + 1 ];
	char *p, *OffSetPtr;
	char SearchId[ TEMP + 1 ], CfgVal[ TEMP + 1 ], chn[ 11 ], mcn;
	int Ind, Ind1;
	int NoOfVar, NoOfData, Count;
	int CheckAmount = 0, DecimalMultiplier = 0;
	EzCfgUtil cfg;
	EzDateTimeUtil dtu;

	struct EzDevMsg ConsumerReq, OldDevMsg;
	struct OARDetails OARList[ 9 ];

	trace( DEBUG_TEST, "Transaction Request received from ATM[ %s ]", AtmId );

	memset( &ConsumerReq, 0, sizeof( struct EzDevMsg ) );
	strcpy( ConsumerReq.OrgPort, AtmId );
	strcpy( ConsumerReq.SrcPort, AtmId );

	memset( &OldDevMsg, 0, sizeof( struct EzDevMsg ) );
	memcpy( &OldDevMsg, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

	ConsumerReq.MsgType = EZLINK_TXN_TxnRequest;
    ConsumerReq.OrgMsgType = EZLINK_TXN_TxnRequest;

  	strcpy( ConsumerReq.TerminalId , atminfo.TerminalId );
	strcpy( ConsumerReq.TerminalLocation , atminfo.AtmLocation );

	ConsumerReq.MerchantType = atminfo.MerchantId;
	strcpy( ConsumerReq.DeviceSubType, atminfo.AtmTypeId );
	ConsumerReq.PinVerFlg = atminfo.PinVerFlag;

	memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
	if( PackAtmTraceNoMsg( AtmId, atminfo.TraceNum, &atmmgrq ) < 0 )
		trace( DEBUG_ERROR, "Failed in PackTraceNumMsg");

	if( PostAtmMgrMsg( atmmgrq, AtmId ) < 0 )
		trace( DEBUG_ERROR, "Failed in PostAtmMgrMsg");

	//Loading Txn Date and Time

	ConsumerReq.TranDate  = ConsumerReq.LocalDate = ConsumerReq.CaptureDate = dtu.getSysDate();
    ConsumerReq.TranTime  = ConsumerReq.LocalTime = ConsumerReq.CaptureTime = dtu.getSysTime();

	strcpy( ConsumerReq.AcqBranchCode, atminfo.AcquirerBranchCode );
	strcpy( ConsumerReq.AcquirerInst, atminfo.AcquirerInst );
	ConsumerReq.RespCode = 0;

	memset( Luno, 0, sizeof( Luno ) );
	p = ( char * ) memchr( AtmReq, DEVICE_FS, Size );
	memcpy( Luno, AtmReq, (p-AtmReq) );
	trace( DEBUG_NORMAL, "Luno : %s",Luno );
	AtmReq += ( strlen( Luno ) );

	AtmReq++; //0x1c position is moved
    AtmReq++; //0x1c position is moved
    AtmReq++; //0x1c position is moved

	switch( *AtmReq )
	{
		case '0':
			trace( DEBUG_TEST, "will not print data for this transaction at the top of the receipt" );
			break;
		case '1':
			trace( DEBUG_TEST, "will print data for this transaction at the top of the receipt" );
			break;
		default:
		        trace( DEBUG_ERROR, "Message Not Supproted" );
			break;
	}
	AtmReq++;

	//Coping MsgCoOrdinationNo to shared mem
    mcn = *AtmReq++ ;
    atmbuf.MsgCoOrdinationNo = mcn;
    trace( DEBUG_TEST, "Message Co-ordination Number [%c]", atmbuf.MsgCoOrdinationNo );
    AtmReq++; //0x1c position is moved
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 41 );

	memset( temp, 0, sizeof( temp ) );
	memcpy( temp, AtmReq, ( OffSetPtr - AtmReq ) ); //Track2 Data

	memset( ConsumerReq.Track2, 0, sizeof( ConsumerReq.Track2 ) );
	for( int i = 0; strlen( temp ); i++ )
	{
		if( !isdigit( temp[ i ] ) )
			continue;
		else
		{
			strcpy( ConsumerReq.Track2, temp + i );
			break;
		}
	}

	p = ConsumerReq.Track2;
	for( int i = 0; i < strlen( p  ); i++ )
	{
		if( p[ i ] == '=' )
			break;
		else
			ConsumerReq.chn[ i ] = p[ i ];
	}

	AtmReq = OffSetPtr ;
	AtmReq++;//0x1c moved
	AtmReq = ( char * ) memchr( AtmReq, DEVICE_FS, 107 );//track 3
	AtmReq++;//0x1c moved

	// OpKey Buffer
	memset( OpKeyBuf, 0, sizeof( OpKeyBuf ) );
    OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 9 );
    memcpy( OpKeyBuf, AtmReq, (OffSetPtr-AtmReq) );
    trace( DEBUG_TEST, "Opkey Buffer [%s]", OpKeyBuf );
    memset( TrimOpKeyBuf, 0, sizeof( TrimOpKeyBuf ) );
    for( int i = 0, j = 0; i < strlen( OpKeyBuf ); i++ )
    {
    	if( OpKeyBuf[ i ] != ' ' )
    	{
    		TrimOpKeyBuf[ j ] = OpKeyBuf[ i ];
    		j++;
    	}
    }
	trace( DEBUG_TEST, "Trimmed Opkey Buffer [%s]", TrimOpKeyBuf );

	memset( ConsumerReq.m_chn, 0, sizeof( ConsumerReq.m_chn ) );
	ezpadssutil.maskString( ConsumerReq.chn, 6, strlen( ConsumerReq.chn ) - 4, '*', ConsumerReq.m_chn );

	trace( DEBUG_NORMAL, "MCN[%c] CHN[%s] TrimmedOpkeyBuf[%s]", atmbuf.MsgCoOrdinationNo, ConsumerReq.m_chn, TrimOpKeyBuf );

	AtmReq = OffSetPtr ;

	memset( chn, 0, sizeof( chn ) );
	strncpy( chn, ConsumerReq.chn, 10 );

	memset( InDirectState, 0, sizeof( InDirectState ) );
	if( ReadIndirectState( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, chn, InDirectState ) < 0 )
	{
		if( atmbuf.CurrentState != INTERACTIVE )
		{
			trace( DEBUG_ERROR, "Unable to get Indirectstate for Chn [ %s ]", ConsumerReq.m_chn );
			memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
			strcpy( ConsumerReq.DestPort, AtmId );
			ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
			ConsumerReq.RespCode = EZLINK_RC_UnableToProcess;
			if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
				trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
			if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
				trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
			return -1;
		}
	}
	else
		trace( DEBUG_TEST, "Indirectstate & SecurityId for Chn [ %s ] is [ %s ]", ConsumerReq.m_chn, InDirectState);

	if( !strcmp( InDirectState, "7") )
		atmbuf.CurrentState = SUPERVISOR;

	trace( DEBUG_TEST, "Current State [ %c ]", atmbuf.CurrentState );


	if( strlen( TrimOpKeyBuf ) != 0 )
	{
		memset( &temp, 0, sizeof( temp ) );
		if( LoadTxnCode( TrimOpKeyBuf, InDirectState, temp, OpKeyAmount, CurrencyCode, PrinterFlag, TxnReqFlag, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, ConsumerReq.SrcPort, atminfo.AtmTypeId ) < 0 )
		{
			if( atmbuf.CurrentState != INTERACTIVE )
			{
				trace( DEBUG_ERROR, "Unable to find TxnCode for OpKey[ %s ], AtmId[ %s ], InstitutionId[ %s ], GroupName[ %s ]",TrimOpKeyBuf , ConsumerReq.SrcPort, atminfo.AcquirerInst, atminfo.AtmLogicalGroup );
				memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
				strcpy( ConsumerReq.DestPort, AtmId );
				ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
				ConsumerReq.RespCode = EZLINK_RC_UnableToProcess;
				if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
					trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
				if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
				return -1;
			}
		}
		else
		{
			trace( DEBUG_NORMAL, "CurrencyCode[ %s ], PrinterFlag[ %s ], TxnReqFlag[ %s ] TxnCode[ %s ] OpkeyAmount[ %s ]", CurrencyCode, PrinterFlag, TxnReqFlag, temp, OpKeyAmount );
			//checking for New Transaction
			if( atoi( TxnReqFlag ) == NewTxn )
			{
				trace( DEBUG_NORMAL, "New Transaction Request" );
				memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
				atmbuf.MsgCoOrdinationNo = mcn;
				if( atminfo.TraceNum != 9999 )
				{
					ConsumerReq.PosEntryCode = atminfo.TraceNum;
					//ConsumerReq.TraceNo = atminfo.TraceNum;
					atminfo.TraceNum = atminfo.TraceNum + 1;
				}
				else
				{
					ConsumerReq.PosEntryCode = 1;
					atminfo.TraceNum = 1;
				}
				trace( DEBUG_TEST, "Transcation TraceNo[ %d ]", ConsumerReq.PosEntryCode );

				ConsumerReq.TxnCode = atoi( temp );
				if( ( ConsumerReq.TxnCode/10000 ) == 36 )
					atmbuf.OARFlag = '1';

				ConsumerReq.AcqCurrencyCode = atoi( CurrencyCode );

				if( atoi(PrinterFlag) == 1 )
					atmbuf.PrinterFlag = '1';
				else
					atmbuf.PrinterFlag = '0';
			}
			else
			{
				trace( DEBUG_NORMAL, "Old Transaction continuing<%d>.. copying the Txn Details", atoi( TxnReqFlag ) );
				ConsumerReq.TxnCode = atoi( temp );
				ConsumerReq.AcqCurrencyCode = atoi( CurrencyCode );
				ConsumerReq.TraceNo = OldDevMsg.TraceNo;
				ConsumerReq.TranDate = OldDevMsg.TranDate;
				ConsumerReq.TranTime = OldDevMsg.TranTime;
				memset( ConsumerReq.FromAccount, 0, sizeof( ConsumerReq.FromAccount ) );
				strcpy( ConsumerReq.FromAccount, OldDevMsg.FromAccount );
				memset( ConsumerReq.ToAccount, 0, sizeof( ConsumerReq.ToAccount ) );
				strcpy( ConsumerReq.ToAccount, OldDevMsg.ToAccount );
			}
		}
	}

	if( atmbuf.CurrentState != INTERACTIVE )
	{
		trace( DEBUG_TEST, "Checking for ATM Action Property");
		if( strcmp( atmbuf.StaticStatus, "NONE" ) )
		{
			trace( DEBUG_TEST, "Checking for ATM Action Property");
			memset( temp, 0, sizeof( temp ) );
			if( ReadAtmActionProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, atmbuf.StaticStatus, ConsumerReq.TxnCode, temp, &ConsumerReq.RespCode, SENDRESPONSE ) < 0 )
				trace( DEBUG_ERROR, "ATM Action Property not Found");
			else
				trace( DEBUG_TEST, "ATM Action Property Found RespCode[%d]", ConsumerReq.RespCode );

			if( ConsumerReq.RespCode != EZLINK_RC_Approved )
			{
				memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
				strcpy( ConsumerReq.DestPort, AtmId );
				ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
				if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
					trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
				if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
						trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
				return -1;
			}
		}
	}

	if( ConsumerReq.TxnCode/10000 == 1 )
	{
		strcpy( ConsumerReq.BatchId, atminfo.BatchId );
		trace( DEBUG_TEST, "Transaction BatchId[%s]", ConsumerReq.BatchId );
	}

	AtmReq++;//0x1c moved

	//Extracting Amount Buffer
    OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 13 );
    if( OffSetPtr != NULL )
    {
    	memset( DollarEntry, 0, sizeof( DollarEntry ) );
    	memcpy( DollarEntry, AtmReq, ( OffSetPtr - AtmReq ) );
    	trace( DEBUG_TEST, "Dollar Entry Buffer[ %s ]", DollarEntry );
    	AtmReq = OffSetPtr;
    }
	AtmReq ++;//0x1c moved

	if( atmbuf.CurrentState != INTERACTIVE )
	{
		if ( atoi( DollarEntry ) == 0 && atoi( OpKeyAmount ) != 0 )
		{
			memset( temp, 0, sizeof( temp ) );
			sprintf( ConsumerReq.Amount, "%d", atoi( OpKeyAmount ) );
			trace( DEBUG_TEST, "Amount Requested[ %d ]", atoi( OpKeyAmount ) );
		}
		else
		{
			if( atoi( DollarEntry ) != 0 )
			{
				sprintf( ConsumerReq.Amount, "%d", atoi( DollarEntry ) );
				trace( DEBUG_TEST, "Amount Requested[ %d ]", atoi( ConsumerReq.Amount ) );
			}
		}

		memset( &ezatmproperty, 0, sizeof( struct EzAtmProperty ) );
		if( ReadAtmProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, ConsumerReq.TxnCode, ConsumerReq.RespCode, ConsumerReq.AcqCurrencyCode, &ezatmproperty ) < 0 )
			trace( DEBUG_ERROR, "Unable to Reading EzAtmProperty");

		if( ( ConsumerReq.TxnCode/10000 ) == 1 )
		{
			if( ezatmproperty.DecimalPointCheckReq == 'Y' || ezatmproperty.DecimalPointCheckReq == 'y' )
			{
				CheckAmount = atoi( ConsumerReq.Amount );
				if( ezatmproperty.DecimalMultiplier == '2')
					DecimalMultiplier = 100;
				else if( ezatmproperty.DecimalMultiplier == '3')
					DecimalMultiplier = 1000;
				else
					DecimalMultiplier = 1;

				if( CheckAmount != 0 )
					CheckAmount = CheckAmount / DecimalMultiplier;
				ConsumerReq.DecimalMultiplier = ezatmproperty.DecimalMultiplier;
			}
			else
			{
				CheckAmount = atoi( ConsumerReq.Amount );
				ConsumerReq.DecimalMultiplier = '0';
			}
			trace( DEBUG_TEST, "Check Amount[ %d ]", CheckAmount );

			if( CheckAmount == 0 )
			{
				trace( DEBUG_ERROR, "Invalid Amount Requested[ %d ]", CheckAmount );
				ConsumerReq.RespCode = EZLINK_RC_InvalidAmount;
				memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
				strcpy( ConsumerReq.DestPort, AtmId );
				if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
					trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
				return -1;
			}
			else
			{
				memset( DispLogicBuf, 0, sizeof( DispLogicBuf ) );
				memset( DollarEntry, 0, sizeof( DollarEntry ) );
				sprintf( DollarEntry, "%d", CheckAmount );

				if( CheckAmount > atminfo.MaxAmountDisp )
				{
					trace( DEBUG_ERROR, "Amount Requested[ %d ] > Max Amount[ %d ]", CheckAmount, atminfo.MaxAmountDisp );
					ConsumerReq.RespCode = EZLINK_RC_ExceedsMaxAmount;
					memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
					strcpy( ConsumerReq.DestPort, AtmId );
					if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
						trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
					return -1;
				}
				trace( DEBUG_TEST, "Amount Requested[ %s ], checking for Cash availablity", DollarEntry );

				if( GetDispLogic( DollarEntry, ConsumerReq.AcqCurrencyCode, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, ConsumerReq.SrcPort, DispLogicBuf, DIEBOLD, atminfo.AtmTypeId ) < 0 )
				{
					trace( DEBUG_ERROR, "Unable to get Dispensing Logic" );
					ConsumerReq.RespCode = EZLINK_RC_InvalidAmount;
					memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
					strcpy( ConsumerReq.DestPort, AtmId );
					if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
						trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
					return -1;
				}
				else
				{
					//for( int i = 0; i < 8; i++)
						//trace( "Id[%c] Pos[%d] Value[%d]\tCode[%d]\tStatus[%c]", denominfo[i].DenomId, denominfo[i].CassPosition, denominfo[i].CurrencyValue, denominfo[i].CurrencyCode, denominfo[i].Status);
					//trace("MaxDispNotes[%d]",atminfo.MaxDispNotes);
					ConsumerReq.RespCode = CheckCashAvailability( atminfo.AtmTypeId, DollarEntry, DispLogicBuf, ConsumerReq.AcqCurrencyCode, denominfo, atminfo.MaxNoteDisp );

					if( ConsumerReq.RespCode != EZLINK_RC_Approved )
					{
						memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
						strcpy( ConsumerReq.DestPort, AtmId );
						if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
							trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
						return -1;
					}
					else
					{
						trace( DEBUG_NORMAL, "Amount Requested[ %s ], DispLogic[%s]", DollarEntry, DispLogicBuf );
						memset( atmbuf.DispenceLogicBuf, 0, sizeof( atmbuf.DispenceLogicBuf) );
						strcpy( atmbuf.DispenceLogicBuf, DispLogicBuf );
						CheckAmount = 0;
						CheckAmount = atoi( DollarEntry );
						strcpy( ConsumerReq.BatchId, atminfo.BatchId );
					}
				}
				if( ezatmproperty.DecimalPointCheckReq == 'Y' || ezatmproperty.DecimalPointCheckReq == 'y' )
				{
					CheckAmount = CheckAmount * DecimalMultiplier;
					memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
					sprintf( ConsumerReq.Amount, "%d", CheckAmount);
				}
				else
				{
					memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
					sprintf( ConsumerReq.Amount, "%d", CheckAmount);
				}
			}
		}

		if( ( ConsumerReq.TxnCode/10000 ) == 20 || ( ConsumerReq.TxnCode/10000 ) == 40 || ( ConsumerReq.TxnCode/10000 ) == 41 )
		{
			if( ezatmproperty.DecimalPointCheckReq == 'Y' || ezatmproperty.DecimalPointCheckReq == 'y' )
			{
				CheckAmount = atoi( ConsumerReq.Amount );
				if( ezatmproperty.DecimalMultiplier == '2')
					DecimalMultiplier = 100;
				else if( ezatmproperty.DecimalMultiplier == '3')
					DecimalMultiplier = 1000;
				else
					DecimalMultiplier = 1;

				if( CheckAmount != 0 )
					CheckAmount = CheckAmount / DecimalMultiplier;
				ConsumerReq.DecimalMultiplier = ezatmproperty.DecimalMultiplier;
			}
			else
			{
				CheckAmount = atoi( ConsumerReq.Amount );
				ConsumerReq.DecimalMultiplier = '0';
			}
			trace( DEBUG_TEST, "Check Amount[ %d ]", CheckAmount );

			if( CheckAmount == 0 )
			{
				trace( DEBUG_NORMAL, "Invalid Amount Requested[ %d ]", CheckAmount );
				ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
				ConsumerReq.RespCode = EZLINK_RC_InvalidAmount;
				memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
				strcpy( ConsumerReq.DestPort, AtmId );
				if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
					trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
				if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
				return -1;
			}
			else
			{
				if( ezatmproperty.DecimalPointCheckReq == 'Y' || ezatmproperty.DecimalPointCheckReq == 'y' )
				{
					CheckAmount = CheckAmount * DecimalMultiplier;
					memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
					sprintf( ConsumerReq.Amount, "%d", CheckAmount);
				}
				else
				{
					memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
					sprintf( ConsumerReq.Amount, "%d", CheckAmount);
				}
			}
		}

		if(	atmbuf.CurrentState != SUPERVISOR )
		{
			if( ezatmproperty.DecimalPointCheckReq == 'Y' || ezatmproperty.DecimalPointCheckReq == 'y' )
			{
				if( ezatmproperty.DecimalMultiplier == '2')
					DecimalMultiplier = 2;
				else if( ezatmproperty.DecimalMultiplier == '3')
					DecimalMultiplier = 3;

				memset( temp, 0, sizeof( temp ) );
				memset( CfgVal, 0, sizeof( CfgVal ) );

				strncpy( temp, ConsumerReq.Amount, strlen( ConsumerReq.Amount ) - DecimalMultiplier );
				strncpy( CfgVal, ConsumerReq.Amount + strlen( ConsumerReq.Amount ) - DecimalMultiplier, DecimalMultiplier );
				memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
				sprintf( ConsumerReq.Amount, "%s.%s", temp, CfgVal);
			}
			else
			{
				memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
				sprintf( ConsumerReq.Amount, "%d.00", CheckAmount);
			}
		}
	}

	//Extracting PIN Block Buffer
	memset( PinBuf, 0, sizeof( PinBuf )  );
    OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 17 );
    if( OffSetPtr != NULL )
    {
		memcpy( PinBuf, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "PinBlockBuffer[ %s ]", PinBuf );
		p = PinBuf ;

		while( *p )
		{
			switch( *p )
			{
				case ':':
					*p++='A';
					break;
				case ';':
						*p++='B';
					break;
				case '<':
						*p++='C';
					break;
				case '=':
						*p++='D';
						break;
				case '>':
						*p++='E';
						break;
				case '?':
						*p++='F';
						break;
				default:
						p++;
			}
		}

		trace( DEBUG_TEST, "Reformed PinBlockBuffer [ %s ]", PinBuf );

		if( ( ConsumerReq.TxnCode == 940002 ) || ( ConsumerReq.TxnCode == 940003 ) )
			strcpy( ConsumerReq.NewPINBlock, PinBuf );
		else
			strcpy( ConsumerReq.PINBlock, PinBuf );

		AtmReq = OffSetPtr ;
    }
	else
	{
		if( atmbuf.CurrentState != INTERACTIVE )
		{
			trace( DEBUG_TEST, "PinBlockBuffer is Empty" );
			memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
			strcpy( ConsumerReq.DestPort, AtmId );
			ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
			ConsumerReq.RespCode = EZLINK_RC_UnableToProcess;
			if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
				trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
			if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
				trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
			return -1;
		}
	}

    AtmReq ++;//0x1c moved

	memset( GenBufB, 0, sizeof( GenBufB ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 32 );
	if( OffSetPtr != NULL )
	{
		memcpy( GenBufB, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "General Purpose Buffer B [ %s ]", GenBufB );

		AtmReq += strlen( GenBufB );
		strcpy( ConsumerReq.RsvFld1, GenBufB );
	}
	AtmReq ++;//0x1c moved
	trace( DEBUG_TEST, "< %s >", AtmReq);

	if( *AtmReq != '\0' )
	{
		char TempBuf[100];
		if( !strcmp( InDirectState, "0") )
		{
			memset( GenBufC, 0, sizeof( GenBufC ) );
			memset( TempBuf, 0, sizeof( TempBuf ) );
			strcpy( TempBuf, AtmReq );

			for( int i = 0; i < strlen( TempBuf ); i++ )
			{
				if( TempBuf[i] == 0x1c )
					break;
				GenBufC[i] = TempBuf[i];
			}

			if( strlen( GenBufC ) != 0 )
			{
				trace( DEBUG_TEST, "General Purpose Buffer C [ %s ]", GenBufC );
				trace( DEBUG_TEST, "RsvFld1 <%s>", OldDevMsg.RsvFld1 );
				if( strlen( OldDevMsg.RsvFld1 ) != 0 && atoi( TxnReqFlag ) == ContinueTxn )
					strcpy( ConsumerReq.RsvFld1, OldDevMsg.RsvFld1 );

				if( strlen( ConsumerReq.RsvFld1 ) == 0 )
					strcpy( ConsumerReq.RsvFld1, GenBufC );
				else
				{
					strcat( ConsumerReq.RsvFld1, "|");
					strcat( ConsumerReq.RsvFld1, GenBufC );
				}
			}
		}
	}

	if( ( strlen( ConsumerReq.Track2 ) > 15 ) && ( atmbuf.CurrentState == INTERACTIVE ) )
    {
            memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
            memcpy( &atmbuf.DevMsg, (char*)&ConsumerReq, sizeof( struct EzDevMsg ) );
            atmbuf.CurrentState = TRANSACTIONREQUEST;

            if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
            {
                    trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
                    return -1;
            }
    }
	else if( atmbuf.CurrentState == INTERACTIVE )
	{
		if( strlen( GenBufB ) != 0 )
		{
			if( !strncmp( GenBufB, "E", 1 ) )
			{
				trace( DEBUG_TEST, "OAR Transaction is Cancelled");
				OldDevMsg.RespCode = EZLINK_RC_TrancastionCancelled;
				atmbuf.CurrentState = TRANSACTIONRESPONSE;
				if( BuildAndPostFuncMsg( OldDevMsg ) < 0 )
				{
					trace( DEBUG_ERROR, "Failed to BuildAndPostFuncMsg" );
					return -1;
				}
			}

			memset( chn, 0, sizeof( chn ) );
			strncpy( chn, OldDevMsg.chn, 10 );

			memset( InDirectState, 0, sizeof( InDirectState ) );
			memset( temp, 0, sizeof( temp ) );
			if( ReadIndirectState( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, chn, InDirectState ) < 0 )
				trace( DEBUG_ERROR, "Unable to get Indirectstate for Chn [ %s ]", OldDevMsg.m_chn );
			else
				trace( DEBUG_TEST, "Indirectstate for Chn [ %s ] is [ %s ] ", OldDevMsg.m_chn, InDirectState );

			memset( &OARList, 0, ( sizeof( struct OARDetails ) * 8 ) );
			if( LoadOARTemplate( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AtmId, InDirectState, OldDevMsg.TxnCode, OARList, atminfo.AtmTypeId ) < 0 )
			{
				trace( DEBUG_NORMAL, "Unable to Load OAR templates" );
				return -1;
			}

			NoOfVar = GetTotalVar( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AtmId, InDirectState, OldDevMsg.TxnCode, atminfo.AtmTypeId );
			if( NoOfVar < 0 )
			{
				trace( DEBUG_NORMAL, "Unable to get OAR Total Var" );
				return -1;
			}

			for( int i = 0; i < 8; i++ )
			{
				if( OARList[i].Key == GenBufB[ 0 ]  )
				{
					Count = ( atmbuf.OffsetLength - 1 ) * NoOfVar + ( OARList[i].Position );
			  		if( OARList[i].Template == VAR )
			  		{
			  			memset( FileName, 0, sizeof( FileName ));
			  			sprintf( FileName, "%s/%s/%s", getenv("EZDIR_HOME"), "inf", OldDevMsg.RespFile );
			  			trace( DEBUG_NORMAL, "Info FileName [ %s ]", FileName );

						if( cfg.cfg_open( FileName ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed to open file [ %s ]", FileName );
							return -1;
						}

						memset( SearchId, 0, sizeof( SearchId ) );
						sprintf( SearchId, "%s_%d", "OAR#VAR", Count - 1 );
						trace( DEBUG_NORMAL, "SearchId[ %s ]", SearchId );
						if( cfg.cfg_search( SearchId, CfgVal, 2 ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed to search[ %s ]", SearchId );
							cfg.cfg_close();
							return -1;
						}
						else
						{
							trace( DEBUG_NORMAL, "Selected Data[ %s ]", CfgVal );
							if( !strlen( OldDevMsg.FromAccount ) )
							{
								memset( OldDevMsg.FromAccount, 0, sizeof( OldDevMsg.FromAccount ) );
								strcpy( OldDevMsg.FromAccount, CfgVal );
							}
							else
							{
								memset( OldDevMsg.ToAccount, 0, sizeof( OldDevMsg.ToAccount ) );
								strcpy( OldDevMsg.ToAccount, CfgVal );
							}
						}

						memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
						memcpy( &atmbuf.DevMsg, (char*)&OldDevMsg, sizeof( struct EzDevMsg ) );

						atmbuf.CurrentState = INTERACTIVE;
						if ( BuildAndPostFuncMsg( OldDevMsg ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed to BuildAndPostFuncMsg" );
							cfg.cfg_close();
							return -1;
						}
						cfg.cfg_close();
					}
					else if ( OARList[i].Template == NEXT )
					{
						atmbuf.OffsetLength++;
						atmbuf.CurrentState = INTERACTIVE;

						if( BuildAndPostOARRequest( OldDevMsg ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed to BuildAndPostOARRequest" );
							return -1;
						}
					}
					else if ( OARList[i].Template == PREVIOUS )
					{
						atmbuf.OffsetLength--;
						atmbuf.CurrentState = INTERACTIVE;
						if( BuildAndPostOARRequest( OldDevMsg ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed to BuildAndPostOARRequest" );
							return -1;
						}
					}
					else
					{
						trace( DEBUG_ERROR, "Unsupported OAR Template");
						return -1;
					}
				}
			}
		}
	}
	else
	{
		if( ( ( ConsumerReq.TxnCode/10000 ) == 98 ) || ( ( ConsumerReq.TxnCode/10000 ) == 99 ) )
		{
			memset( ConsumerReq.Amount, 0, sizeof( ConsumerReq.Amount ) );
			sprintf( ConsumerReq.Amount, "%d", atoi( DollarEntry ) );
			strcpy( ConsumerReq.BatchId, atminfo.BatchId );
			atmbuf.CurrentState = SUPERVISOR;
			if( ServeSupervisorRequest( &ConsumerReq, &atminfo, &atmbuf ) < 0 )
				trace( DEBUG_ERROR, "Failed in ServeSupervisorRequest" );
			else
			{
				trace( DEBUG_NORMAL, "ServeSupervisorRequest updated successfully for [ %s ]", ConsumerReq.SrcPort );
				if( ( ConsumerReq.TxnCode/10000 ) == 99 && ( ConsumerReq.TxnCode%100 ) == 4  )
				{
					memset( atminfo.BatchId, 0, sizeof( atminfo.BatchId ) );
					strcpy( atminfo.BatchId, ConsumerReq.BatchId  );
				}
			}

			if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
			{
				trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg" );
				return -1;
			}
		}
		else
		{
			memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
			memcpy( &atmbuf.DevMsg, (char*)&ConsumerReq, sizeof( struct EzDevMsg ) );
			atmbuf.CurrentState = TRANSACTIONREQUEST;

			if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
			{
				trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
				return -1;
			}
		}
	}
	return 1;
}

int EzD912 :: ServeStatusChangeMsg( char * AtmReq, int Size , char *AtmId , char *StatusCode )
{
	char Luno[ LUNO_SIZE + 1 ], *p, temp[ TEMP + 1 ], Byte[ BYTE + 1 ] ;
	int i;

	struct EzAtmController AtmCont;

	struct EzDevMsg devmsg;

	memset( &devmsg, 0, sizeof( struct EzDevMsg ) );
	memcpy( &devmsg, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

	memset( &ezatmproperty, 0, sizeof( struct EzAtmProperty ) );
	if( ReadAtmProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, devmsg.TxnCode, 0, devmsg.AcqCurrencyCode, &ezatmproperty ) < 0 )
		trace( DEBUG_ERROR, "Unable to Reading EzAtmProperty");

	memset( Luno, 0, sizeof( Luno ) );
	p = ( char * ) memchr( AtmReq, DEVICE_FS, Size );
	memcpy( Luno, AtmReq, (p-AtmReq) );
	trace( DEBUG_NORMAL, "Luno : %s", Luno );
	AtmReq += ( strlen( Luno ) + 1 );
	trace( DEBUG_DUMP, "%s", AtmReq );
	AtmReq ++;
	trace( DEBUG_DUMP, "%s", AtmReq );

	switch ( *AtmReq )
	{
		case '1':
		        trace( DEBUG_NORMAL, "Power failure status change request" );
		        StatusCode += BuiltStatusCode( ( char * )"!PF", 3, StatusCode );
		        BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!PF", atmbuf.StaticStatus );

				if( ezatmproperty.DownloadCheckReq == 'Y' || ezatmproperty.DownloadCheckReq == 'y' )
				{
					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
					AtmCont.CommandType = GET_CONFIG_INFO;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
				}
				else
				{
					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_DOWNLOAD_REQ;
					AtmCont.DownloadType = DOWNLOAD_ALL;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( "Failed in PostContMsg" );
						return -1;
					}
				}
				break ;

		case '2':
		        trace( DEBUG_NORMAL, "Alarm Status Message" );
		        StatusCode += BuiltStatusCode( (char *)"!AS", 2, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!AS", atmbuf.StaticStatus );
		        AtmReq ++;
		        memset( Byte, 0, sizeof( Byte ) );
		        strncpy( Byte, AtmReq, 2 );
		        for( i = 0; i < 8; i++ )
		        {
		        if( IsBitSet( Byte, (short)i + 1 ) == 1 );
		        {
			        switch( i )
			        {
			 	       case 0:
				            trace( DEBUG_NORMAL, "Someone opened the terminal" );
				            StatusCode += BuiltStatusCode( (char *)"A1", 2, StatusCode );
				            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A1", atmbuf.StaticStatus );
				            break;

				       case 1:
				            trace( DEBUG_NORMAL, "The safe door is open" );
				            StatusCode += BuiltStatusCode( (char *)"A2", 2, StatusCode );
				            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A2", atmbuf.StaticStatus );
				            break;

				       case 2:
				            trace( DEBUG_NORMAL, "Withdrawal door tampered by someother" );
                            StatusCode += BuiltStatusCode( (char *)"A3", 2, StatusCode );
                            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A3", atmbuf.StaticStatus );
                            break;

                       case 3:
                            trace( DEBUG_NORMAL, "Reserved" );
                            break;

                       case 4:
                    	   	trace( DEBUG_NORMAL, "The operator triggered an alarm while opening the safe" );
                            StatusCode += BuiltStatusCode( (char *)"A4", 2, StatusCode );
                            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A4", atmbuf.StaticStatus );
                            break;

                       case 5:
                    	   	trace( DEBUG_NORMAL, "coin door is opened" );
                            StatusCode += BuiltStatusCode( (char *)"A5", 2, StatusCode );
                            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A5", atmbuf.StaticStatus );
                            break;

                       case 6:
                            trace( DEBUG_NORMAL, "lobby cash pocket alarm is detected" );
                            StatusCode += BuiltStatusCode( (char *)"A6", 2, StatusCode );
                            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A6", atmbuf.StaticStatus );
                            break;

                       case 7:
                            trace( DEBUG_NORMAL, "Enable the lobby cash pocket" );
                            StatusCode += BuiltStatusCode( (char *)"A7", 2, StatusCode );
                            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"A7", atmbuf.StaticStatus );
                            break;

                       default:
                            trace( DEBUG_NORMAL, "unsupported bit" );
                            break;

			        }
		        }
			}
		    break;

		case '3':
			trace( DEBUG_NORMAL, "Supervisory mode switch" );
            StatusCode += BuiltStatusCode( (char *)"!SS", 3, StatusCode );
            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!SS", atmbuf.StaticStatus );
			AtmReq ++;
			memset( temp, 0, sizeof(temp) );
			strncpy( temp, AtmReq, 2 );
			switch ( atoi( temp ) )
			{
				case 0 :
					trace( DEBUG_NORMAL, "The operator selects LOGOFF from any menu" );
					StatusCode += BuiltStatusCode( (char *)"SS1", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SS1", atmbuf.StaticStatus );
					break ;

				case 20:
					trace( DEBUG_NORMAL, "The operator selects SUPPLY" );
					StatusCode += BuiltStatusCode( (char *)"SS2", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SS2", atmbuf.StaticStatus );
					break ;

				case 40:
				case 60:
					trace( DEBUG_NORMAL, "The operator selects ATTN MSG." );
					StatusCode += BuiltStatusCode( (char *)"SS3", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SS3", atmbuf.StaticStatus );

					ClearStatus( atmbuf.StatusMsg, atmbuf.StaticStatus, StatusCode );
					memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
					memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

					if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
						trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
					else
						trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", AtmId );

					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
					AtmCont.CommandType = GO_IN_SERVICE;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
					break ;

				default:
					trace( DEBUG_NORMAL, "Unsupported bit" );
					break ;
			}
			break ;

		case '4':
			trace( DEBUG_NORMAL, "Problems with printers" );
			AtmReq ++;//byte 0
			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 0:
							trace( DEBUG_NORMAL, "Journal printer has faulted" );
							StatusCode += BuiltStatusCode( (char *)"!JP", 3, StatusCode );
                            BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!JP", atmbuf.StaticStatus );
							AtmReq += 2;//byte 1
							AtmReq += 2;//byte 2
							memset( Byte, 0, sizeof( Byte ) );
							strncpy( Byte, AtmReq, 2 );

							for( i = 0; i < 8; i++ )
							{
								if( IsBitSet( Byte, (short)i + 1 ) == 1 )
								{
							        switch( i )
							        {
									case 0:
										trace( DEBUG_NORMAL, "Fault occurred during a line feed" );
										StatusCode += BuiltStatusCode( (char *)"JP18", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP18", atmbuf.StaticStatus );
										break;

									case 1:
										trace( DEBUG_NORMAL, "Fault occurred during a head return " );
										StatusCode += BuiltStatusCode( (char *)"JP19", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP19", atmbuf.StaticStatus );
										break;

									case 2:
										trace( DEBUG_NORMAL, "Fault occurred during a head return and line feed" );
										StatusCode += BuiltStatusCode( (char *)"JP20", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP20", atmbuf.StaticStatus );
										break;

									case 5:
										trace( DEBUG_NORMAL, "Low paper" );
										StatusCode += BuiltStatusCode( (char *)"JP21", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP21", atmbuf.StaticStatus );
										break;

									case 6:
										trace( DEBUG_NORMAL, "Electrical fault detected on ready line of Journal printer" );
										StatusCode += BuiltStatusCode( (char *)"JP22", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP22", atmbuf.StaticStatus );
										break;

									case 7:
										trace( DEBUG_NORMAL, "Run out of Paper" );
										StatusCode += BuiltStatusCode( (char *)"JP23", 4, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP23", atmbuf.StaticStatus );
										break;

									default:
										trace( DEBUG_NORMAL, "unsupported bit" );
										break;
								}
							}
						}
						break;

					case 1:
						trace( DEBUG_NORMAL, "Consumer printer has faulted." );
						StatusCode += BuiltStatusCode( (char *)"!CP", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CP", atmbuf.StaticStatus );
						AtmReq += 2;//byte 1
						memset( Byte, 0, sizeof( Byte ) );
						strncpy( Byte, AtmReq, 2 );
						for( i = 0; i < 8; i++ )
						{
							if( IsBitSet( Byte, (short)i + 1 ) == 1 )
							{
								switch( i )
								{
									case 0:
										trace( DEBUG_NORMAL, "Fault occurred during a line feed" );
										StatusCode += BuiltStatusCode( (char *)"CP1", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP1", atmbuf.StaticStatus );
										break;

									case 1:
										trace( DEBUG_NORMAL, "Fault occurred during a head return " );
										StatusCode += BuiltStatusCode( (char *)"CP2", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP2", atmbuf.StaticStatus );
										break;

									case 2:
										trace( DEBUG_NORMAL, "Fault occurred during a head return and line feed" );
										StatusCode += BuiltStatusCode( (char *)"CP3", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP3", atmbuf.StaticStatus );
										break;

									case 3:
										trace( DEBUG_NORMAL, "Fault occurred during a top-of-form search " );
										StatusCode += BuiltStatusCode( (char *)"CP4", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP4", atmbuf.StaticStatus );
										break;

									case 5:
										trace( DEBUG_NORMAL, "Run out of Paper" );
										StatusCode += BuiltStatusCode( (char *)"CP5", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP5", atmbuf.StaticStatus );
										break;

									case 7:
										trace( DEBUG_NORMAL, "Low paper" );
										StatusCode += BuiltStatusCode( (char *)"CP6", 3, StatusCode );
										BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CP6", atmbuf.StaticStatus );
										break;

									default:
										trace( DEBUG_NORMAL, "unsupported bit" );
										break;
								}
							}
						}
						break;

					case 7:
						trace( DEBUG_NORMAL, " The print operation has been completed." );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			break ;

		case '5':
			trace( DEBUG_NORMAL, "Problem with Card reader" );
			StatusCode += BuiltStatusCode( (char *)"!CR", 3, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CR", atmbuf.StaticStatus );
			AtmReq ++;
			memset( Byte, 0, sizeof(Byte) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
				switch( i )
				{
					case 0:
						trace( DEBUG_NORMAL, "Card in rear." );
						StatusCode += BuiltStatusCode( (char *)"CR23", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR23", atmbuf.StaticStatus );
						break;

					case 1:
						trace( DEBUG_NORMAL, "Hard fault." );
						StatusCode += BuiltStatusCode( (char *)"CR24", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR24", atmbuf.StaticStatus );
						break;

					case 2:
						trace( DEBUG_NORMAL, "Soft failure" );
						StatusCode += BuiltStatusCode( (char *)"CR25", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR25", atmbuf.StaticStatus );
						break;

					case 3:
						trace( DEBUG_NORMAL, "Card in retain position" );
						StatusCode += BuiltStatusCode( (char *)"CR3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR3", atmbuf.StaticStatus );
						break;

					case 4:
						trace( DEBUG_NORMAL, "Track 3 card error" );
						StatusCode += BuiltStatusCode( (char *)"CR19", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR19", atmbuf.StaticStatus );
						break;

					case 5:
						trace( DEBUG_NORMAL, "Track 2 card error" );
						StatusCode += BuiltStatusCode( (char *)"CR20", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR20", atmbuf.StaticStatus );
						break;

					case 6:
						trace( DEBUG_NORMAL, "Track 1 card error" );
						StatusCode += BuiltStatusCode( (char *)"CR21", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR21", atmbuf.StaticStatus );
						break;

					case 7:
						trace( DEBUG_NORMAL, "Read operation error" );
						StatusCode += BuiltStatusCode( (char *)"CR4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR4", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			break;

		case '7':
			trace( DEBUG_NORMAL, "Problem with Card writer" );
			StatusCode += BuiltStatusCode( (char *)"!CW", 3, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CW", atmbuf.StaticStatus );
			AtmReq ++;
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
				switch( i )
				{
					case 0:
						trace( DEBUG_NORMAL, "No start or end sentinel" );
						break;

					case 1:
						trace( DEBUG_NORMAL, "Card write error limit exceeded" );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			break;

		case '8':
			trace( DEBUG_NORMAL, "vandal shield status(international terminals only)" );

			StatusCode += BuiltStatusCode( (char *)"!VSS", 4, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!VSS", atmbuf.StaticStatus );
			AtmReq ++;
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
				switch( i )
				{
					case 0:
						trace( DEBUG_NORMAL, "Lower sheild fault" );
						StatusCode += BuiltStatusCode( (char *)"VSS1", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"VSS1", atmbuf.StaticStatus );
						break;

					case 1:
						trace( DEBUG_NORMAL, "Raise sheild fault" );
						StatusCode += BuiltStatusCode( (char *)"VSS2", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"VSS2", atmbuf.StaticStatus );
						break;

					case 2:
						trace( DEBUG_NORMAL, "In down position" );
						StatusCode += BuiltStatusCode( (char *)"VSS3", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"VSS3", atmbuf.StaticStatus );
						break;

					case 3:
						trace( DEBUG_NORMAL, "In up position" );
						StatusCode += BuiltStatusCode( (char *)"VSS4", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"VSS4", atmbuf.StaticStatus );
						break;

					case 4:
						trace( DEBUG_NORMAL, "Lock fault" );
						StatusCode += BuiltStatusCode( (char *)"VSS5", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"VSS5", atmbuf.StaticStatus );
						break;

					case 6:
						trace( DEBUG_NORMAL, "Good operation" );
						StatusCode += BuiltStatusCode( (char *)"VSS6", 4, StatusCode );
						break;

					case 7:
						trace( DEBUG_NORMAL, "Operation complete" );
						StatusCode += BuiltStatusCode( (char *)"VSS7", 4, StatusCode );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			break;

		case '<':
			trace( DEBUG_NORMAL, "Problem in withdrawl area sensors" );
			StatusCode += BuiltStatusCode( (char *)"!WAS", 4, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!WAS", atmbuf.StaticStatus );
			AtmReq ++;
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 7:
							trace( DEBUG_NORMAL, "a sensor is blocked." );
							StatusCode += BuiltStatusCode( (char *)"S29", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S29", atmbuf.StaticStatus );
							break;

						case 6:
							trace( DEBUG_NORMAL, "Forgotten money taken." );
							StatusCode += BuiltStatusCode( (char *)"S30", 3, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S30", atmbuf.StaticStatus );
							break;

						default:
							trace( DEBUG_NORMAL, "unsupported bit" );
							break;
					}
				}
			}
			break ;

		case '?':
			trace( DEBUG_NORMAL, "Dispenser problem" );

			StatusCode += BuiltStatusCode( (char *)"!DP", 3, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DP", atmbuf.StaticStatus );
			if( atmbuf.CurrentState == TRANSACTIONREQUEST && devmsg.MsgType == EZLINK_TXN_TxnResponse )
			{
				devmsg.RespCode = EZLINK_RC_UncertainDispense;
				if( PostTxnMsg( &devmsg, AtmId ) < 0 );
				{
					trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
					return -1;
				}
			}
			break ;

		case '@':
			trace( DEBUG_NORMAL, "withdrawal door status" );
			StatusCode += BuiltStatusCode( (char *)"!WDS", 4, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!WDS", atmbuf.StaticStatus );
			AtmReq ++;
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
					switch( i )
					{
						case 2:
							trace( DEBUG_NORMAL, "The consumer has opened the door slightly." );
							StatusCode += BuiltStatusCode( (char *)"CH12", 4, StatusCode );
							BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CH12", atmbuf.StaticStatus );
							break;

						default:
							trace( DEBUG_NORMAL, "unsupported bit" );
							break;
					}
				}
			}
			break ;

		case 'A':
			trace( DEBUG_NORMAL, "IDM mode"  );

			StatusCode += BuiltStatusCode( (char *)"!IDM", 4, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!IDM", atmbuf.StaticStatus );
			AtmReq ++;//byte 0
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			trace( DEBUG_NORMAL, "Depositor Status : %s", Byte );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
				switch( i )
				{
					case 0:
						trace( DEBUG_NORMAL, "soft fault." );
						StatusCode += BuiltStatusCode( (char *)"DF6", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF6", atmbuf.StaticStatus );
						break;

					case 1:
						trace( DEBUG_NORMAL, "Deposit cassette full." );
						StatusCode += BuiltStatusCode( (char *)"DF7", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF7", atmbuf.StaticStatus );
						break;

					case 2:
						trace( DEBUG_NORMAL, "Deposit incomplete" );
						StatusCode += BuiltStatusCode( (char *)"DF8", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF8", atmbuf.StaticStatus );
						break;

					case 3:
						trace( DEBUG_NORMAL, "Initial condition fault" );
						StatusCode += BuiltStatusCode( (char *)"DF9", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF9", atmbuf.StaticStatus );
						break;

					case 4:
						trace( DEBUG_NORMAL, "Customer timeout" );
						StatusCode += BuiltStatusCode( (char *)"DF10", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF10", atmbuf.StaticStatus );
						break;

					case 5:
						trace( DEBUG_NORMAL, "Printer error" );
						StatusCode += BuiltStatusCode( (char *)"DF11", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF11", atmbuf.StaticStatus );
						break;

					case 6:
						trace( DEBUG_NORMAL, "Hard fault" );
						StatusCode += BuiltStatusCode( (char *)"DF12", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF12", atmbuf.StaticStatus );
						break;

					case 7:
						trace( DEBUG_NORMAL, "Abnormal document retain" );
						StatusCode += BuiltStatusCode( (char *)"DF13", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF13", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			AtmReq += 2;// byte 1
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			trace( DEBUG_NORMAL, "printer module fault status : " );

			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
				switch( i )
				{
					case 0:
						trace( DEBUG_NORMAL, "Unit module error." );
						StatusCode += BuiltStatusCode( (char *)"IP1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IP1", atmbuf.StaticStatus );
						break;

					case 1:
						trace( DEBUG_NORMAL, "Tens module error." );
						StatusCode += BuiltStatusCode( (char *)"IP2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IP2", atmbuf.StaticStatus );
						break;

					case 2:
						trace( DEBUG_NORMAL, "Hundreds module error" );
						StatusCode += BuiltStatusCode( (char *)"IP3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IP3", atmbuf.StaticStatus );
						break;

					case 3:
						trace( DEBUG_NORMAL, "Thousands module error" );
						StatusCode += BuiltStatusCode( (char *)"IP4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IP4", atmbuf.StaticStatus );
						break;

					case 4:
						trace( DEBUG_NORMAL, "Customer cancel" );
						StatusCode += BuiltStatusCode( (char *)"IP5", 3, StatusCode );
						break;

					case 7:
						trace( DEBUG_NORMAL, "MICR read fault" );
						StatusCode += BuiltStatusCode( (char *)"IP6", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IP6", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			AtmReq += 2;// byte 2
			memset( Byte, 0, sizeof( Byte ) );
			strncpy( Byte, AtmReq, 2 );
			for( i = 0; i < 8; i++ )
			{
				if( IsBitSet( Byte, (short)i + 1 ) == 1 )
				{
				switch( i )
				{
					case 0:
						trace( DEBUG_NORMAL, "MICR hardware error." );
						StatusCode += BuiltStatusCode( (char *)"IDM1", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IDM1", atmbuf.StaticStatus );
						break;

					case 1:
						trace( DEBUG_NORMAL, "Scanner error." );
						StatusCode += BuiltStatusCode( (char *)"IDM2", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IDM2", atmbuf.StaticStatus );
						break;

					case 2:
						trace( DEBUG_NORMAL, "Doucment size error" );
						StatusCode += BuiltStatusCode( (char *)"IDM3", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IDM3", atmbuf.StaticStatus );
						break;

					case 3:
						trace( DEBUG_NORMAL, "Bin error" );
						StatusCode += BuiltStatusCode( (char *)"IDM4", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IDM4", atmbuf.StaticStatus );
						break;

					case 4:
						trace( DEBUG_NORMAL, "Document handling error" );
						StatusCode += BuiltStatusCode( (char *)"IDM5", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IDM5", atmbuf.StaticStatus );
						break;

					case 7:
						trace( DEBUG_NORMAL, "Depositor disabled" );
						StatusCode += BuiltStatusCode( (char *)"IDM6", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"IDM6", atmbuf.StaticStatus );
						break;

					default:
						trace( DEBUG_NORMAL, "unsupported bit" );
						break;
				}
			}
			}
			break ;

		case 'G':
			trace( DEBUG_NORMAL, "Coin Dispenser" );
			break ;

		case 'J':
			trace( DEBUG_NORMAL, "Enhanced Status" );
			break ;

		default:
			trace( DEBUG_NORMAL, "Unhandled status change message" );
			break ;

	}
	trace( DEBUG_NORMAL, "Remaining value [%s]", ++AtmReq );

	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
		trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
	else
		trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", AtmId );

	return 1;
}

int EzD912 :: BuildAndPostWriteCmd( struct EzAtmController ContReq )
{
	char AtmBuf[ BUFFER_SIZE+1 ], PortChannel[ CHANNEL_NAME_SIZE+1 ], Date[ 20 ], Time[ 10 ];

	memset( AtmBuf, 0, sizeof( AtmBuf ) );
	switch( ContReq.DownloadType )
	{
		case DOWNLOAD_STATE:
			trace( DEBUG_NORMAL, "Downloading State table....." );
			sprintf( AtmBuf, "30%c001%c999%c12%c%s", DEVICE_FS, DEVICE_FS, DEVICE_FS, DEVICE_FS, ContReq.MsgBuf );
			break;

		case DOWNLOAD_SCREEN:
			trace( DEBUG_NORMAL, "Downloading Screens....." );
			sprintf( AtmBuf, "30%c001%c999%c11%c%s", DEVICE_FS, DEVICE_FS, DEVICE_FS, DEVICE_FS, ContReq.MsgBuf );
			break;

		case DOWNLOAD_MISC:
			trace( DEBUG_NORMAL, "Downloading Miscellaneous Data....." );
			sprintf( AtmBuf, "30%c001%c999%c13%c%s", DEVICE_FS, DEVICE_FS, DEVICE_FS, DEVICE_FS, ContReq.MsgBuf );
			break;

		case DOWNLOAD_FIT:
			trace( DEBUG_NORMAL, "Downloading FIT table....." );
			sprintf( AtmBuf, "30%c001%c999%c15%c%s", DEVICE_FS, DEVICE_FS, DEVICE_FS, DEVICE_FS, ContReq.MsgBuf );
			break;

		case DOWNLOAD_KEY:
			trace( DEBUG_NORMAL, "Downloading Terminal Key....." );
			sprintf( AtmBuf, "30%c001%c999%c32%c%s", DEVICE_FS, DEVICE_FS, DEVICE_FS, DEVICE_FS, ContReq.MsgBuf );
			break;

		case DOWNLOAD_CONFIG_ID:
			trace( DEBUG_NORMAL, "Downloading Configuration Id....." );
			sprintf( AtmBuf, "30%c001%c999%c16%c%s", DEVICE_FS, DEVICE_FS, DEVICE_FS, DEVICE_FS, ContReq.MsgBuf );
			break;

		default:
			trace( DEBUG_NORMAL, "Invaild Download[ %d ]", ContReq.DownloadType );
			break;
	}

	atmbuf.CurrentState = DOWNLOAD ;

	if( PostAtmMsg( ContReq.AtmId, AtmBuf ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}

int EzD912 :: BuildAndPostOperCmd( struct EzAtmController ContReq )
{
	char AtmBuf[ BUFFER_SIZE + 1 ];

	memset( AtmBuf, 0, sizeof( AtmBuf ) );
	sprintf( AtmBuf, "10%c001%c999%c", DEVICE_FS, DEVICE_FS, DEVICE_FS  );
	switch( ContReq.CommandType )
	{
		case GO_IN_SERVICE:
			strcat( AtmBuf , "1" );
			break;

		case GO_OUT_SERVICE:
			strcat( AtmBuf , "2" );
			break;

		case GET_CONFIG_INFO:
			strcat( AtmBuf , "3" );
			break;

		case CLOSE_VANDAL_SHIELD:
			strcat( AtmBuf , "4" );
			break;

		case OPEN_VANDAL_SHIELD:
			strcat( AtmBuf , "5" );
			break;

		case UNLOCK_SAFE_DOOR:
			strcat( AtmBuf , "6" );
			break;

		case LOCK_SAFE_DOOR:
			strcat( AtmBuf , "7" );
			break;

		case EMG_COMMAND:
			strcat( AtmBuf , "8" );
			break;

		case GET_SUPPLY_COUNTS:
			strcat( AtmBuf , "9" );
			break;

		case CLEAR_SUPPLY_COUNTS:
			strcat( AtmBuf , ":" );
			break;

		case GET_ESUPPLY_COUNTS:
			strcat( AtmBuf , ";" );
			break;

		case CLEAR_ESUPPLY_COUNTS:
			strcat( AtmBuf , "<" );
			break;

		case RUN_SELF_TEST:
			strcat( AtmBuf , "=" );
			break;

		case SHUTDOWN:
			strcat( AtmBuf , ">" );
			break;

		default:
			trace( DEBUG_NORMAL, "Invalid Operational Command" );
			break;
	}

	atmbuf.CurrentState = OPERATIONAL ;

	if( PostAtmMsg( ContReq.AtmId, AtmBuf ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}

int EzD912 :: BuildAndPostFuncMsg( struct EzDevMsg DevMsg )
{
	char FunctionMsg[ BUFFER_SIZE + 1 ], PrinterData[ PSDATA_SIZE + 1 ], ScreenData[ PSDATA_SIZE + 1 ], temp[ TEMP + 1 ];
	char InDirectState[ ISTATE + 1 ], FileName[ FILENAME_SIZE + 1 ];
	char NextScreenNumber[ ISTATE + 1 ], NextStateNumber[ ISTATE + 1 ], DispLogicBuf[ DISP + 1 ], chn[ 11 ];
	char Temp[ TEMP+1 ], Date[ 20 ], Time[ 10 ];
	int len, ret;


	trace( DEBUG_TEST, "Building function Command....[ %s ]", DevMsg.SrcPort );

	memset( &ezatmproperty, 0, sizeof( struct EzAtmProperty ) );
	if( ReadAtmProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, DevMsg.SrcPort, DevMsg.TxnCode, DevMsg.RespCode, DevMsg.AcqCurrencyCode, &ezatmproperty ) < 0 )
		trace( DEBUG_ERROR, "Unable to Reading EzAtmProperty");
	trace( DEBUG_TEST, "ezatmproperty.JournalPrinterReq[ %c ]" , ezatmproperty.JournalPrinterReq );
	sprintf( FunctionMsg, "4%c001%c%c", DEVICE_FS, DEVICE_FS, DEVICE_FS );

	if( DevMsg.TxnCode / 10000 == 98 || DevMsg.TxnCode / 10000 == 99 )
	{
		memset( DevMsg.DestPort, 0, sizeof( DevMsg.DestPort ) );
		strcpy( DevMsg.DestPort, DevMsg.SrcPort );
	}

	if ( DevMsg.RespCode == 0 )
    {
		trace( DEBUG_TEST, "Good response");
		memset( NextScreenNumber, 0, sizeof( NextScreenNumber ) );
		memset( NextStateNumber, 0, sizeof( NextStateNumber ) );
		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%d", DevMsg.TxnCode );

		memset( chn, 0, sizeof( chn ) );
		strncpy( chn, DevMsg.chn, 10 );
		memset( InDirectState, 0, sizeof( InDirectState ) );

		if( ReadIndirectState( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, chn, InDirectState ) < 0 )
			trace( DEBUG_ERROR, "Unable to get Indirectstate for Chn [ %s ]", DevMsg.m_chn );

		if( LoadGoodResponseState( temp, InDirectState, NextStateNumber, NextScreenNumber, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.SrcPort, atminfo.AtmTypeId ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed to Load the GoodResponseState for Device<%s_%s_%s>, TxnCode<%d_%s>",atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.SrcPort, DevMsg.TxnCode, InDirectState );
			memset( NextScreenNumber, 0, sizeof( NextScreenNumber ) );
			strcpy( NextScreenNumber, "801" );
			memset( NextStateNumber, 0, sizeof( NextStateNumber ) );
			strcpy( NextStateNumber, "801" );
		}
		trace( DEBUG_NORMAL, "Next State No [ %s ] , Next Screen No [ %s ], Processing Code<%d_%s>",NextStateNumber, NextScreenNumber, DevMsg.TxnCode, InDirectState );
		sprintf( FunctionMsg+7, "%s%c", NextStateNumber, DEVICE_FS );
		if ( ( DevMsg.TxnCode/10000 ) == 1 )
		{
			memset( DispLogicBuf, 0, sizeof( DispLogicBuf ) );
			strcpy( DispLogicBuf, atmbuf.DispenceLogicBuf );
			trace( DEBUG_NORMAL, "Dispense logic[ %s ]", DispLogicBuf);
			sprintf( FunctionMsg+11, "%s%c", DispLogicBuf, DEVICE_FS );
		}
		else
			sprintf( FunctionMsg+11, "%s%c", "00000000" , DEVICE_FS  );
	}
	else
	{
		trace( DEBUG_TEST, "Bad response");

		/*if( ( ( DevMsg.TxnCode/10000 ) == 36 ) && ( strlen( DevMsg.FromAccount ) != 0 ) && ( DevMsg.RespCode == EZLINK_RC_NoFromAccount ) )
			DevMsg.RespCode = EZLINK_RC_NoToAccount;*/

		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%d", DevMsg.RespCode );

		memset( chn, 0, sizeof( chn ) );
		strncpy( chn, DevMsg.chn, 10 );

		memset( InDirectState, 0, sizeof( InDirectState ) );
		memset( NextScreenNumber, 0, sizeof( NextScreenNumber ) );

		if( ReadIndirectState( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, chn, InDirectState ) < 0 )
			trace( DEBUG_NORMAL, "Unable to get Indirectstate for Chn [ %s ]", DevMsg.m_chn );

		if( LoadBadResponseState( temp, InDirectState, NextStateNumber, NextScreenNumber, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.SrcPort, atminfo.AtmTypeId ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed to Load the BadResponseState for Device<%s_%s_%s>, TxnCode<%d_%s>", atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.SrcPort, DevMsg.RespCode, InDirectState );
			memset( NextScreenNumber, 0, sizeof( NextScreenNumber ) );
			strcpy( NextScreenNumber, "802" );
			memset( NextStateNumber, 0, sizeof( NextStateNumber ) );
			strcpy( NextStateNumber, "802" );
		}
		trace( DEBUG_NORMAL, "Next State No [ %s ] , Next Screen No [ %s ], Processing Code<%d_%s>",NextStateNumber, NextScreenNumber, DevMsg.TxnCode, InDirectState );
		sprintf( FunctionMsg + 7, "%s%c", NextStateNumber, DEVICE_FS );
		sprintf( FunctionMsg+11, "%s%c", "00000000" , DEVICE_FS  );
	}

    memset( temp, 0, sizeof( temp ) );
    sprintf( temp, "%04d", DevMsg.PosEntryCode );
    //sprintf( temp, "%04d", DevMsg.TraceNo );
	trace( DEBUG_TEST, "trace no : %s", temp );

	strncat( FunctionMsg, temp, 4 );
	switch( ( DevMsg.TxnCode/10000 ) )
	{
		case 1 :// Cash Withdrawal
			if ( DevMsg.RespCode == EZLINK_RC_Approved )
			{
				if( atmbuf.PrinterFlag == '1' )
				{
					strcat( FunctionMsg, "B" );
					strcat( FunctionMsg, NextScreenNumber );
	                strcat( FunctionMsg, "\x1d" );
	                strcat( FunctionMsg, "C" );
	                strcat( FunctionMsg, NextScreenNumber );
	                strcat( FunctionMsg, "\x1d" );
	                strcat( FunctionMsg, "D" );
				}
				else
				{
					strcat( FunctionMsg, "B" );
					strcat( FunctionMsg, NextScreenNumber );
	                strcat( FunctionMsg, "\x1d" );
	                strcat( FunctionMsg, "C" );
				}
			}
			else if ( DevMsg.RespCode == EZLINK_RC_PartialDispense || DevMsg.RespCode == EZLINK_RC_DispencedFully )
			{
				//Check Device Property
				strcat( FunctionMsg, "C" );
				strcat( FunctionMsg, NextScreenNumber );
                strcat( FunctionMsg, "\x1d" );
                strcat( FunctionMsg, "H" );
			}
			else
				strcat( FunctionMsg, "5" );
			break;

		default:
		        strcat( FunctionMsg, "5" );
		        break;
	}

    //Building ScreenData

	if( ( DevMsg.RespCode == 0 ) && ( DevMsg.TxnCode/10000 ) != 36 )
	{
		trace( DEBUG_NORMAL, "Composing Screen template");
		strcat( FunctionMsg, NextScreenNumber );

		memset( Temp, 0, sizeof( Temp ) );
		if( GetEmptyScreen( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, Temp, atminfo.AtmTypeId ) < 0 )
			trace( DEBUG_ERROR, "Unable to Get Empty Screen" );
		else
			strcat( FunctionMsg, Temp );

		if( atmbuf.CurrentState != INTERACTIVE )
		{
			memset( ScreenData, 0, sizeof( ScreenData ) );
			if( ComposeScreenTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, &DevMsg, ScreenData ) < 0 )
				trace( DEBUG_ERROR, "Unable to Compose the screen data" );
			else
				strcat( FunctionMsg, ScreenData );
			trace( DEBUG_TEST, "ScreenData[ %s ]", ScreenData );
		}
	}
	else if ( DevMsg.RespCode != 0 )
	{
		strcat( FunctionMsg, NextScreenNumber );
	}

	len = strlen( FunctionMsg );
	sprintf( FunctionMsg + len, "%c", DEVICE_FS );
	len ++;

	//MsgCoOrdinationNo
	trace( DEBUG_TEST, "Msg CoOrdianationNo[ %c ]", atmbuf.MsgCoOrdinationNo );
	sprintf( FunctionMsg + len, "%c", atmbuf.MsgCoOrdinationNo );

	if ( DevMsg.RespCode == 0 )
		strcat( FunctionMsg, "0" );
	else
	{
		if( DevMsg.RespCode == 41 )
		{
			if( ezatmproperty.CardReaderModel == DIP_CARDREADER )
				strcat( FunctionMsg, "1" );
			else
				strcat( FunctionMsg, "0" );
		}
		else
			strcat( FunctionMsg, "0" );
	}

	//Building Printer Data
	trace( DEBUG_TEST, "Composing printer template" );
	if ( DevMsg.RespCode == 0 )
	{
		if ( atmbuf.PrinterFlag == '1' )
		{
			memset( PrinterData, 0, sizeof( PrinterData ) );
			if( atmbuf.CurrentState != INTERACTIVE )
			{
				trace( DEBUG_TEST, "TxnCode[ %d ]",DevMsg.TxnCode);
				if( ( ( DevMsg.TxnCode/10000 ) == 98 ) || ( ( DevMsg.TxnCode/10000 ) == 99 ) )
				{
					/*
					* memset( DevMsg.DestPort, 0, sizeof( DevMsg.DestPort ) );
					* strcpy( DevMsg.DestPort, DevMsg.SrcPort );
					*/

					trace( DEBUG_TEST, "Before Composing Supervisor Data DestPort[%s] SrcPort[%s]", DevMsg.DestPort, DevMsg.SrcPort );
					memset( PrinterData, 0, sizeof( PrinterData ) );
					if( BuildSupPrinterData( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, &DevMsg, atminfo.AtmTypeId, PrinterData ) < 0 )
					{
						strcat( FunctionMsg, "0" );//Do not Print
						trace( DEBUG_ERROR, "Unable to Compose the printer data" );
					}
					else
					{
						//Check DeviceProperty
						//strcat( FunctionMsg, "3" );//Print in Both Printer
						strcat( FunctionMsg, "2" );//Print in receipt Printer
						strcat( FunctionMsg, PrinterData );
					}
					trace( DEBUG_TEST, "After Composing Supervisor Data DestPort[%s] SrcPort[%s]", DevMsg.DestPort, DevMsg.SrcPort );
				}
				else
				{
					if( ezatmproperty.JournalPrinterReq == 'Y' || ezatmproperty.JournalPrinterReq == 'y' )
					{
						trace( DEBUG_TEST, "Enabling Journal Printer for TxnCode[%06d]", DevMsg.TxnCode );
						memset( PrinterData, 0, sizeof( PrinterData ) );
						if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, J0URNAL_PRINTER, &DevMsg, PrinterData ) < 0 )
						{
							trace( DEBUG_ERROR, "Unable to Compose the Journal printer data" );
						}
						else
						{
							strcat( FunctionMsg, "1" );//Print in journal Printer
							strcat( FunctionMsg, PrinterData );
							strcat( FunctionMsg, "\x1c");
						}
					}
					else if( ezatmproperty.PassbookPrinterReq == 'Y' || ezatmproperty.PassbookPrinterReq == 'y' )
					{
						trace( DEBUG_TEST, "Enabling Passbook Printer for TxnCode[%06d]", DevMsg.TxnCode );
						memset( PrinterData, 0, sizeof( PrinterData ) );
						if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, PASSBOOK_PRINTER, &DevMsg, PrinterData ) < 0 )
						{
							trace( DEBUG_ERROR, "Unable to Compose the Passbook printer data" );
						}
						else
						{
							strcat( FunctionMsg, ";" );
							strcat( FunctionMsg, PrinterData );
							strcat( FunctionMsg, "\x1c");
						}
					}
					else if( ezatmproperty.StatementPrinterReq == 'Y' || ezatmproperty.StatementPrinterReq == 'y' )
					{
						trace( DEBUG_TEST, "Enabling Statement Printer for TxnCode[%06d]", DevMsg.TxnCode );
						memset( PrinterData, 0, sizeof( PrinterData ) );
						if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, STATEMENT_PRINTER, &DevMsg, PrinterData ) < 0 )
						{
							trace( DEBUG_ERROR, "Unable to Compose the Statement printer data" );
						}
						else
						{
							strcat( FunctionMsg, ";" );//Print in journal Printer
							strcat( FunctionMsg, PrinterData );
							strcat( FunctionMsg, "\x1c");
						}
					}
					else
						trace( DEBUG_TEST, "Extra Printers are not configured for this Transaction");

					if( atmbuf.PrinterFlag == '1' )
					{
						memset( PrinterData, 0, sizeof( PrinterData ) );
						if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, CONSUMER_PRINTER, &DevMsg, PrinterData ) < 0 )
						{
							strcat( FunctionMsg, "0" );//Do not Print
							trace( DEBUG_ERROR, "Unable to Compose the Consumer printer data" );
						}
						else
						{
							strcat( FunctionMsg, "2" );//Print in consumer Printer
							strcat( FunctionMsg, PrinterData );
						}
					}
				}
			}
			else
			{
				strcat( FunctionMsg, "0" );//Do not Print
			}
		}
		else
		{
			if( ezatmproperty.JournalPrinterReq == 'Y' || ezatmproperty.JournalPrinterReq == 'y' )
			{
				trace( DEBUG_TEST, "Enabling Journal Printer for TxnCode[%d]", DevMsg.TxnCode );
				memset( PrinterData, 0, sizeof( PrinterData ) );
				if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, J0URNAL_PRINTER, &DevMsg, PrinterData ) < 0 )
				{
					strcat( FunctionMsg, "0" );//Do not Print
					trace( DEBUG_ERROR, "Unable to Compose the Journal printer data" );
				}
				else
				{
					strcat( FunctionMsg, "1" );//Print in journal Printer
					strcat( FunctionMsg, PrinterData );
				}
			}
			else
				strcat( FunctionMsg, "0" );//Do not Print
		}
	}
	else
	{
		if( ezatmproperty.JournalPrinterReq == 'Y' || ezatmproperty.JournalPrinterReq == 'y' )
		{
			trace( DEBUG_TEST, "Reversal Txns.. Enabling Journal Printer");
			memset( PrinterData, 0, sizeof( PrinterData ) );
			if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, J0URNAL_PRINTER, &DevMsg, PrinterData ) < 0 )
			{
				trace( DEBUG_ERROR, "Unable to Compose the Journal printer data" );
			}
			else
			{
				strcat( FunctionMsg, "1" );//Print in journal Printer
				strcat( FunctionMsg, PrinterData );
				strcat( FunctionMsg, "\x1c");
			}
		}

		if( ( ( DevMsg.TxnCode/10000 ) == 98 ) || ( ( DevMsg.TxnCode/10000 ) == 99 ) )
		{
			trace( DEBUG_TEST, "Before Composing Supervisor Data DestPort[%s] SrcPort[%s]", DevMsg.DestPort, DevMsg.SrcPort );
			memset( PrinterData, 0, sizeof( PrinterData ) );
			if( BuildSupPrinterData( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.RespCode, &DevMsg, atminfo.AtmTypeId, PrinterData ) < 0 )
			{
				strcat( FunctionMsg, "0" );//Do not Print
				trace( DEBUG_ERROR, "Unable to Compose the printer data" );
			}
			else
			{
				strcat( FunctionMsg, "2" );//Print in receipt Printer
				strcat( FunctionMsg, PrinterData );
			}
			trace( DEBUG_TEST, "After Composing Supervisor Data DestPort[%s] SrcPort[%s]", DevMsg.DestPort, DevMsg.SrcPort );
		}
		else
		{
			memset( PrinterData, 0, sizeof( PrinterData ) );
			if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.RespCode, CONSUMER_PRINTER, &DevMsg, PrinterData ) < 0 )
			{
				strcat( FunctionMsg, "0" );//Do not Print
				trace( DEBUG_ERROR, "Unable to Compose the printer data" );
			}
			else
			{
				strcat( FunctionMsg, "2" );//Print in receipt Printer
				trace( DEBUG_TEST, "Printer Data[ %s ]", PrinterData);
				strcat( FunctionMsg, PrinterData );
			}
		}
	}

	trace( DEBUG_TEST, "After Final Data DestPort[%s] SrcPort[%s]", DevMsg.DestPort, DevMsg.SrcPort );

	if( ( ( DevMsg.TxnCode/10000 ) == 98 ) || ( ( DevMsg.TxnCode/10000 ) == 99 ) )
		atmbuf.CurrentState = SUPERVISOR ;
	else
		atmbuf.CurrentState = TRANSACTIONRESPONSE ;

	trace( DEBUG_TEST, "Before Post ATM Message...BatchId[%s]", DevMsg.BatchId );

	memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
	memcpy( &atmbuf.DevMsg, ( char * )&DevMsg, sizeof( struct EzDevMsg ) );

	if (PostAtmMsg( DevMsg.DestPort, FunctionMsg ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}

	return 1;
}

int EzD912 :: BuildAndPostOARRequest( struct EzDevMsg DevMsg )
{
	char OARMsg[ BUFFER_SIZE + 1 ],  ScreenData[ PSDATA_SIZE + 1 ], temp[ TEMP + 1 ];
	char AtmId[ ATM_ID_SIZE + 1 ], Date[ 20 ], Time[ 10 ], KeyDetails[ 12 ];
	char FileName[ FILENAME_SIZE + 1 ], FileName1[ FILENAME_SIZE + 1 ], TimeOut[ 4 ], chn[ 11 ], InDirectState[ ISTATE + 1 ];
	int IndirectState = 0,  NoOfVar, NoOfData, TotalPage, CurrentPage;

	struct OARDetails OARList[ 9 ];
	int ret, Count;

	trace( DEBUG_TEST, "Building OAR Request..."  );
	sprintf( OARMsg, "30%c001%c%c2", DEVICE_FS, DEVICE_FS, DEVICE_FS  );

	memset( chn, 0, sizeof( chn ) );
	strncpy( chn, DevMsg.chn, 10 );

	memset( InDirectState, 0, sizeof( InDirectState ) );

	if( ReadIndirectState( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, chn, InDirectState ) < 0 )
		trace( DEBUG_ERROR, "Unable to get Indirectstate for Chn [ %s ]", DevMsg.m_chn );

	memset( &OARList, 0, ( sizeof( struct OARDetails ) * 8 ) );
	if( LoadOARTemplate( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, OARList, atminfo.AtmTypeId ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to Load OAR templates" );
		return -1;
	}


	NoOfVar = GetTotalVar( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AtmId, InDirectState, DevMsg.TxnCode, atminfo.AtmTypeId );
	if( NoOfVar < 0 )
	{
		trace( DEBUG_ERROR, "Unable to get OAR Total Var" );
		return -1;
	}

	memset( FileName, 0, sizeof( FileName ));
	sprintf( FileName, "%s/%s/%s", getenv("EZDIR_HOME"), "inf", DevMsg.RespFile );

	NoOfData = GetTotalData( DevMsg.RespFile );
	if( NoOfData < 0 )
	{
		trace( DEBUG_ERROR, "Unable to get OAR Total Data" );
		return -1;
	}
	for( int i = 0; i < 8; i++ )
		trace( DEBUG_TEST, "Key[ %c ]Template[ %d ]Status[ %d ]Position[ %d ]", OARList[i].Key, OARList[i].Template, OARList[i].Status, OARList[i].Position );


	if( NoOfData % NoOfVar == 0 )
		TotalPage = ( NoOfData/NoOfVar );
	else
		TotalPage = ( ( NoOfData/NoOfVar ) + 1 );

	atmbuf.TotalLength = TotalPage;
	trace( DEBUG_NORMAL, "TotalPage[ %d ]", TotalPage );


	if( atmbuf.OffsetLength == 0 )
		atmbuf.OffsetLength = CurrentPage = 1;
	else
		CurrentPage = atmbuf.OffsetLength;

	trace( DEBUG_NORMAL, "Current Page[ %d ]", CurrentPage );

	if( CurrentPage == TotalPage )
	{
		if( TotalPage == 1 )
		{
			Count = NoOfData % NoOfVar;
			if( Count == 0 )
				Count = NoOfVar;
			for( int i = 0, j = 0; i < 8; i ++ )
			{
				if( j != Count )
				{
					if( OARList[i].Template == VAR )
					{
						OARList[i].Status = 1;
						j++;
					}
				}
			}
		}
		else
		{
			Count = NoOfData % NoOfVar;
			if( Count == 0 )
				Count = NoOfVar;
			for( int i = 0, j = 0; i < 8; i ++ )
			{
				if( OARList[i].Template == PREVIOUS )
					OARList[i].Status = 1;

				if( j != Count )
				{
					if( OARList[i].Template == VAR )
					{
						OARList[i].Status = 1;
						j++;
					}
				}
			}
		}
	}
	else if( CurrentPage != TotalPage )
	{
		if( CurrentPage == 1 )
		{
			for( int i = 0; i < 8; i ++ )
			{
				if( OARList[i].Template == NEXT )
					OARList[i].Status = 1;
			}
		}
		else
		{
			for( int i = 0; i < 8; i ++ )
			{
				if( ( OARList[i].Template == NEXT ) || ( OARList[i].Template == PREVIOUS ) )
					OARList[i].Status = 1;
			}
		}
		for( int i = 0; i < 8; i ++ )
		{
			if( OARList[i].Template == VAR )
				OARList[i].Status = 1;
		}
	}

	for( int i = 0; i < 8; i++ )
			trace( DEBUG_TEST, "After-->Key[ %c ]Template[ %d ]Status[ %d ]Position[ %d ]", OARList[i].Key, OARList[i].Template, OARList[i].Status, OARList[i].Position );

	memset( KeyDetails, 0, sizeof( KeyDetails ) );
	if( PackKeyDetails( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, KeyDetails, OARList, atminfo.AtmTypeId ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to pack Key Details");
		return -1;
	}
	else
		strcat( OARMsg, KeyDetails );
	trace( DEBUG_TEST, "with Key Details[ %s ]", OARMsg);

	strcat( OARMsg, "\x1c" );
	memset( TimeOut, 0, sizeof( TimeOut ) );
	if( GetOARTimeOut( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, TimeOut, atminfo.AtmTypeId ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to get OAR TimeOut");
		trace( DEBUG_ERROR, "Setting default timer < 025 > ...");
		strcat( OARMsg, "025" );
	}
	else
		strcat( OARMsg, TimeOut );
	strcat( OARMsg, "\x1c" );

	memset( ScreenData, 0, sizeof( ScreenData ) );
	trace( DEBUG_TEST, "before OAR Template");
	if( ComposeOARTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, DevMsg.RespFile, IndirectState, DevMsg.TxnCode, OARList, atmbuf.OffsetLength, NoOfVar, ScreenData ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to Composing OAR Screen Data");
		return -1;
	}
	else
		strcat( OARMsg, ScreenData );

	atmbuf.CurrentState = INTERACTIVE ;

	memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
	memcpy( &atmbuf.DevMsg, &DevMsg, sizeof( struct EzDevMsg ) );

	if( PostAtmMsg( DevMsg.DestPort, OARMsg ) < 0 )
	{
		trace( DEBUG_NORMAL, "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}

int EzD912 :: PostAtmMsg( const char *DestPort, char *AtmMsg )
{
	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	memset( &atmmem.AtmInfoBuffer, 0, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmmem.AtmInfoBuffer, &atminfo, sizeof( struct AtmTableInfo ) );

	trace( DEBUG_TEST, "Before WritingAtmMemory Function....BatchId[%s]", atmmem.AtmSharedBuffer.DevMsg.BatchId );

	if( WriteAtmMemory( DestPort, &atmmem ) < 0 )
		trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", DestPort );
	else
		trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", DestPort );

	if( atminfo.LoggingFlag == 'Y' || atminfo.LoggingFlag == 'y' )
	{
		memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
		PackAtmLogMsg( DestPort, AtmMsg, MSG_TO_DEVICE, &atmmgrq );
		trace( DEBUG_TEST, "Logging the Message from Device[ %s ] ", DestPort );

		if( PostAtmMgrMsg( atmmgrq, atmmgrq.AtmId ) < 0 )
			trace( DEBUG_ERROR, "Failed in PostAtmMgrMsg");
	}

	if ( WritePortChannel( DestPort, AtmMsg, strlen( AtmMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to post the Message into Port Channel[ %s ]", DestPort );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Posted the Message to Port Channel[ %s ]", DestPort );

	return 1;
}

int EzD912 :: PostTxnMsg( struct EzDevMsg *DevMsg, char *AtmId )
{
	struct EzTxnMsg eztxnmsg;

	//for( int i = 0; i < 8; i++)
		//trace( "Id[%c] Pos[%d] Value[%d]\tCode[%d]\tStatus[%c]", denominfo[i].DenomId, denominfo[i].CassPosition, denominfo[i].CurrencyValue, denominfo[i].CurrencyCode, denominfo[i].Status);

	memset( &atmbuf.denominfo, 0, sizeof( struct DenomInfo ) * 8 );
	memcpy( &atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 8 );

	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	memset( &atmmem.AtmInfoBuffer, 0, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmmem.AtmInfoBuffer, &atminfo, sizeof( struct AtmTableInfo ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
		trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
	else
		trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );

	trace( DEBUG_TEST, "Transforming the Device message into Transaction Message");
	strcpy( DevMsg->SrcChannel, D912DRIVERCHANNEL );

	memset( &eztxnmsg, 0, sizeof( struct EzTxnMsg ) );
	TransformOUTboundMsg( &eztxnmsg, DevMsg );

	trace( DEBUG_TXN, "MsgType[ %d ] TxnCode[ %d ] TraceNo[ %d ] Chn[ %s ] Amount[ %s ] DispAmount[ %s ]", eztxnmsg.MsgType, eztxnmsg.TxnCode, eztxnmsg.TraceNo, eztxnmsg.m_chn, eztxnmsg.Amount, eztxnmsg.DispAmount );

	if( WriteChannel( TRANSACTIONCHANNEL, (char*)&eztxnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", TRANSACTIONCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message written into the %s channel", TRANSACTIONCHANNEL );

	return 1;
}

int EzD912 :: PostAtmMgrMsg( struct EzAtmMgrQMsg atmmgrq, char *AtmId )
{
	trace( DEBUG_TEST, "Posting Message to DeviceMgr for Updation");
	if( WriteChannel( ATMMGRCHANNEL, (char*)&atmmgrq, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", ATMMGRCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message Posted into the %s channel", ATMMGRCHANNEL );
	return 1;
}

int EzD912 :: PostContMsg( struct EzAtmController ContReq, char *AtmId )
{
	trace( DEBUG_TEST, "Routing Message to EzATMController");
	if( WriteChannel( CONTROLLERCHANNEL, (char*)&ContReq, sizeof( struct EzAtmController ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", CONTROLLERCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message Posted into the %s channel", CONTROLLERCHANNEL );
	return 1;
}

int EzD912 :: PostAlertMgrMsg( struct EzAlertMgrMsg alertmgrmsg )
{
	if( WriteChannel( EZALERTMGRCHANNEL, (char*)&alertmgrmsg, sizeof( struct EzAlertMgrMsg ) ) < 0 )
	{
		trace( "Unable to write into the channel %s", EZALERTMGRCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message Posted into the %s channel", EZALERTMGRCHANNEL );
	return 1;
}

int main( int argc, char **argv )
{
	EzD912 ezd912obj;
	ezd912obj.InitEzD912Driver( argv[ 0 ] );
	ezd912obj.ServiceRequest( );
	return 1;
}
