#include <ezbusiness/ezndc.h>

EzNDC :: EzNDC()
{
}

EzNDC :: ~EzNDC()
{

}

int EzNDC :: InitEzNDCDriver( const char * TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezndcdriver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug( true );

    if( InitEzTaskUtil( this ) < 0 )
    {
    	trace( "Error in Initializing EzTaskUtil" );
    	trace( "^^^^^^^^^^^EzNDCDriver Ended Abnormally^^^^^^^^^^^^^" );
    	closeDebug( );
    	exit( 0  );
	}

    if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil"  );
		trace( "^^^^^^^^^^^EzNDCDriver Ended Abnormally^^^^^^^^^^^^^" );
	    closeDebug( );
	    TaskExit( );
	}

	if( CreateChannel( NDCDRIVERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating EzNDCDriver Channel"  );
		trace( "^^^^^^^^^^^EzNDCDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	if( InitEzATMUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing the ATMUtil"   );
		trace( "^^^^^^^^^^^EzNDCDriver Ended Abnormally^^^^^^^^^^^^^"  );
		closeDebug();
	    TaskExit();
	}

	InitEzTemplateUtil( this );

	InitEzAtmCashUtil( TaskName, this );

	TaskInit();

	initEzSigUtil( this  );
	return 1;
}

void EzNDC :: ServiceRequest()
{
	char ReadBuf[ BUFFER_SIZE+1 ];
	int ret, BufSize;
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ];
	struct EzAtmController ContReq;
	struct EzTxnMsg AppReq;
	struct EzDevMsg DevMsg;

	while( 1 )
	{
		trace( "Waiting for Message in EzNDCDriver Channel" );
		memset( ReadBuf, 0, sizeof( ReadBuf ) );
		if( ReadMessage( ReadBuf, &BufSize) < 1 )
		{
			trace( "Error in Reading EzNDCDriver Channel"  );
			continue;
		}

		trace( DEBUG_SECURED, "Message of size [%d] Received from Channel[%s]", BufSize, GetLastSenderChannelName() );

		memset( ChannelName, 0, sizeof( ChannelName ) );
		strcpy( ChannelName, GetLastSenderChannelName() );

		if( IsPortMessage() )
		{
			if( DiagnizeAndServeAtmReq( ReadBuf, BufSize, ChannelName ) < 0 )
				trace("Failed in DiagnizeAndServeAtmReq");
		}
		else
		{
			if( !strcmp( ChannelName, TRANSACTIONCHANNEL ) )
			{
				memset( &AppReq, 0, sizeof(EzTxnMsg) );
				memcpy( &AppReq, ReadBuf, BufSize );

				memset( &DevMsg, 0, sizeof( struct EzTxnMsg )  );
				trace( DEBUG_TEST, "Transforming the Transaction Message into Device Message");

				if( TransformINboundMsg( &DevMsg, &AppReq ) < 0 )
					trace("Failed in TransformINboundMsg");

				if( !strlen( DevMsg.m_chn ) )
					ezpadssutil.maskString( DevMsg.chn, 6, strlen( DevMsg.chn ) - 4, '*', DevMsg.m_chn );

				trace( DEBUG_SECURED, "MsgType[ %04d ] TxnCode[ %06d ] TraceNo[ %04d ] RespCode[ %03d ] Chn[ %s ] Amount[ %s ] ", DevMsg.MsgType, DevMsg.TxnCode, DevMsg.TraceNo, DevMsg.RespCode, DevMsg.m_chn, DevMsg.Amount );
				if(  DevMsg.MsgType == EZLINK_TXN_TxnResponse )
				{
					if( DiagnizeAndServeAppReq( DevMsg ) < 0 )
						trace("Failed in DiagnizeAndServeAppReq");
				}
				else
				{
					memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );

					trace( DEBUG_NORMAL, "Reading Memory in DiagnizeAndServeAppReq ");
					if( ReadAtmMemory( DevMsg.DestPort, &atmmem ) < 0 )
						trace( DEBUG_ERROR, "Unable to Read AtmMemoryTable AtmId[ %s ]", DevMsg.DestPort );

					memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
					memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );

					memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( atmmem.AtmInfoBuffer ) );
					memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( atmmem.AtmSharedBuffer ) );

					memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
					memcpy( &atmbuf.DevMsg, &DevMsg, sizeof( struct EzDevMsg ) );

					memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
					memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

					if( WriteAtmMemory( DevMsg.DestPort, &atmmem ) < 0 )
						trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", DevMsg.DestPort );
					else
						trace( DEBUG_NORMAL, "Updated the Device memory for Device[ %s ]", DevMsg.DestPort );
				}
			}
			else if( !strcmp( ChannelName, CONTROLLERCHANNEL ) )
			{
				memset( &ContReq, 0, sizeof( struct EzAtmController )  );
				memcpy( &ContReq, ReadBuf, sizeof( struct EzAtmController ) );

				trace( DEBUG_SECURED, "Message Received : [ %s ][ %s ][ %d ][ %d ][ %d ]", ContReq.AtmId, ContReq.MsgBuf, ContReq.MsgType, ContReq.DownloadType ,ContReq.CommandType);
				if( DiagnizeAndServeContReq( ContReq, ContReq.AtmId  ) < 0 )
					trace( DEBUG_ERROR, "Failed in DiagnizeAndServeContReq");
			}
			else
				trace( "Invalid Channel Name < %s >", ChannelName );
		}
	}
}

int EzNDC :: DiagnizeAndServeAtmReq( char *AtmReq , int MsgSize , char *AtmId )
{
	char StatusCode[ STATUSBUF_SIZE + 1 ];

	trace( DEBUG_TEST, "Reading [%s] Memory in DiagnizeAndServeAtmReq ", AtmId );

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem ) < 0 )
	{
		trace( "Unable to Read AtmMemoryTable AtmId< %s >", AtmId );
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
                	trace("Failed in ServeUnsolicitatedMessage");
                break ;
        case '2':
                trace( DEBUG_TEST, "Solicitated Message Received from Atm[%s]", AtmId );
                if( ServeSolicitatedMessage( ++AtmReq, ( MsgSize - 1 ), AtmId, StatusCode ) < 0 )
                	trace("Failed in ServeSolicitatedMessage");
                break ;
        default:
                 trace( "Not an supported message type" );
                 break ;
	}

    if( strlen( StatusCode ) != 0 && strcmp( StatusCode, "|" ) )
    {
		memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
		PackAtmStatusMsg( AtmId, StatusCode, atmbuf.StaticStatus, &atmmgrq );
		trace( "Updating the Status Message for Atm< %s > ", AtmId );
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
    	trace( "Sending the Status Message for Atm < %s > ", AtmId );
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
    	trace( "Sending the Status Message for Atm < %s > ", AtmId );
    	if( PostAlertMgrMsg( alertmgrmsg ) < 0 )
    	{
			trace("Failed in PostAlertMsg");
			return -1;
		}
    }

	return 1;
}

int EzNDC :: DiagnizeAndServeAppReq( struct EzDevMsg DevMsg )
{
	//trace( DEBUG_NORMAL, "Message from Transaction Mgr" );
	char FileName[ FILENAME_SIZE + 1 ], SearchId[ TEMP + 1 ], CfgVal[ TEMP + 1 ];
	int NoOfAcct;
	EzCfgUtil cfg;

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );

	trace( DEBUG_TEST, "Reading Memory for [ %s ]in DiagnizeAndServeAppReq", DevMsg.DestPort );
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

int EzNDC :: DiagnizeAndServeContReq( struct EzAtmController ContReq , char *AtmId )
{
	trace( DEBUG_SECURED, "Reading [%s] Memory in DiagnizeAndServeContReq", AtmId );

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
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
		trace( DEBUG_NORMAL, "Received Download Command For ATM[ %s ]", AtmId );
		if( BuildAndPostWriteCmd( ContReq  ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed in BuildAndPostWriteCmd For ATM[ %s ]", AtmId );
			return -1;
		}
	}
	else if( ContReq.MsgType == EZ_ATM_COMMAND_REQ )
	{
		trace( DEBUG_SECURED, "Received Opertional Command For ATM[ %s ]", AtmId );
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

int EzNDC :: ServeUnsolicitatedMessage( char *AtmReq, int Size , char * AtmId, char *StatusCode )
{
	char Luno[ LUNO_SIZE + 1 ], *p;
	int ret;

	switch( *AtmReq )
	{
		case '1' :
			trace( DEBUG_SECURED, "Consumer Request from ATM[ %s ]", AtmId );
			MsgFromATM = TRANSACTION_REQUEST_MSG;
		    if( ServeConsumerRequests( AtmReq+2, (Size - 2 ) , AtmId ) < 0 )
		      	trace("Failed in ServeConsumerRequests");
		    break ;
		case '2' :
			trace( DEBUG_SECURED, "Status Change Message from ATM[ %s ]", AtmId );
			MsgFromATM = UNSOLICITED_STATUS_MSG;

			AtmReq += 2;
			memset( Luno, 0, sizeof( Luno ) );
			p = ( char * ) memchr( AtmReq, 0x1c, Size );
			if( p != NULL )
			{
				memcpy( Luno, AtmReq, ( p - AtmReq) );
				trace( DEBUG_TEST,"Luno[%s]",Luno );
				AtmReq += ( strlen( Luno ) + 1 );
				AtmReq ++;
			}

		    if( ServeStatusChangeMsg( AtmReq, strlen( AtmReq ) , AtmId , StatusCode ) < 0 )
		    	trace("Failed in ServeStatusChangeMsg");
			break ;
	}
	return 1;
}

int EzNDC :: ServeSolicitatedMessage( char * AtmReq, int Size , char *AtmId , char *StatusCode )
{
	char Luno[ LUNO_SIZE + 1], temp[ TEMP + 1 ];
	char NotesDisp1[ CURRENCYCOUNTS + 1 ], NotesDisp2[ CURRENCYCOUNTS + 1 ], NotesDisp3[ CURRENCYCOUNTS + 1 ], NotesDisp4[ CURRENCYCOUNTS + 1 ], RejectCass[ CURRENCYCOUNTS + 1 ], RejectCard[ CURRENCYCOUNTS + 1 ];
	char *OffSet, *p;
	int count, ret, Rcass;
	bool found = false;

	struct EzAtmController AtmCont;
	struct EzDevMsg ConsumerReq;
	struct AtmDenomStatusMsg AtmDenomStatus;
	struct EzAtmCounterInfo CounterInfo;

	AtmReq += 2;
	memset( Luno, 0, sizeof( Luno ) );
    p = ( char * ) memchr( AtmReq, 0x1c, Size );
    memcpy( Luno, AtmReq, ( p - AtmReq ) );
    trace( DEBUG_TEST, "Luno[%s]",Luno );
	AtmReq += ( strlen( Luno ) + 1 ) ;
	AtmReq++;//0x1c moved

    memset( &ConsumerReq, 0, sizeof( struct EzDevMsg ) );
    memcpy( &ConsumerReq, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );

    MsgFromATM = SOLICITED_STATUS_MSG;

	switch ( *AtmReq )
	{

	case '3':
                trace( DEBUG_TEST, "New Key Verification Value (KVV)" );
                if ( atmbuf.CurrentState == DOWNLOAD ) //Download Message
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
                break;

	case '4':

                trace( DEBUG_TEST, "Keys Status" );
                AtmReq++;//0x1c moved
                memset( temp, 0, sizeof( temp ) );
                strncpy( temp, AtmReq, 6);
                if( atoi(temp) == 0 )
                {
                        if ( atmbuf.CurrentState == DOWNLOAD )
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
                }
                else
                {
                        if ( atmbuf.CurrentState == DOWNLOAD ) //Download Message
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
                }
                break;

        case '9':
        case 'B':

			trace( DEBUG_TEST, "Device sents READY message. CurrentStatus[%c]", atmbuf.CurrentState );
			// instead of acknowledgement, use the variable from devmsg.

			if( atmbuf.CurrentState == TRANSACTIONRESPONSE )
			{
				trace( DEBUG_TEST, "[ %s ] is in TRANSACTIONRESPONSE state", AtmId );
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

				//trace( "MsgType[%d]", ConsumerReq.MsgType );

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
					memset( temp, 0, sizeof( temp ) );
					if( ReadAtmActionProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, atmbuf.StaticStatus, ConsumerReq.TxnCode, temp, &ConsumerReq.RespCode, SENDCOMMAND ) < 0 )
						trace("ATM Action Property not Found");
					else
					{
						trace("ATM Action Property Found Command[%s]", temp );
						memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
						AtmCont.CommandType = GetOpertionalCmd( temp );
						if( AtmCont.CommandType <= 0 )
							trace("Invaild Command[%s] CommandType[%d]", temp, AtmCont.CommandType );
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
			else if ( atmbuf.CurrentState == DOWNLOAD ) //Download Message
			{
				trace( DEBUG_SECURED, "[ %s ] is in DOWNLOAD state", AtmId );
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
				trace( DEBUG_SECURED, "[ %s ] is in OPERATIONAL state", AtmId );
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
				trace( DEBUG_SECURED, "[ %s ] is in SUPERVISOR state", AtmId );
				if( ConsumerReq.TxnCode == 990005 )
				{
					/*
					memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
					AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
					AtmCont.CommandType = CLEAR_SUPPLY_COUNTS;
					memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
					if( PostContMsg( AtmCont, AtmId ) < 0 )
					{
						trace( DEBUG_ERROR, "Failed in PostContMsg" );
						return -1;
					}
					*/
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
					/*if( ResetDenomStatus( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, AtmId, DIEBOLD, denominfo ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reseting the DenomStatus" );
						return -1;
					}
					else
					{
						memset( atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
						memcpy( atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

						memset( atmmem.AtmInfoBuffer, 0, sizeof( atmmem.AtmInfoBuffer ) );
						memcpy( atmmem.AtmInfoBuffer, (char *)&atminfo, sizeof( struct AtmTableInfo ) );

						if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
						{
							trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
							return -1;
						}
						else
							trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );
					}*/
				}
			}
			break;

        case 'A':
        case 'C':
            trace( DEBUG_SECURED, "Command Reject" );
			int OldRespCode;
			OldRespCode = ConsumerReq.RespCode;
			if( atmbuf.CurrentState == TRANSACTIONRESPONSE || atmbuf.CurrentState == INTERACTIVE )
			{
				trace( DEBUG_NORMAL, "[ %s ] is in TRANSACTION < or > INTERACTIVE state", AtmId );
				if( ( ConsumerReq.TxnCode/10000 == 1 ) &&  ( OldRespCode == EZLINK_RC_Approved ) )
				{
					if( ( ConsumerReq.MsgType == 6000 ) || ( ConsumerReq.MsgType == 210 && ConsumerReq.TxnCode / 10000 == 1 && ConsumerReq.RespCode == 0 ) )
					{
						ConsumerReq.MsgType = 6010;
						ConsumerReq.RespCode = EZLINK_RC_MessageFormatError;
						if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
							return -1;
						}
					}

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
				trace( DEBUG_SECURED, "[ %s ] is in OPERATIONAL state", AtmId );

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

        case 'F':
			trace( "Terminal State " );
			AtmReq ++;
			AtmReq ++;//0x1c
			switch( *AtmReq )
			{
				case '1':
                	trace( "Send configuration information" );
					AtmReq ++;
					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 4 );
					trace( "Configuration Id: %s", temp );
					AtmReq += 4;
					AtmReq ++;//0x1c
					trace( "**** Hardware Fitness ****" );
					switch( *AtmReq )
					{
						case '0':
                        	trace( "Time-of-Day Clock: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"TC5", 3, StatusCode );
							break;
						case '1':
							trace( "Time-of-Day Clock: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"TC6", 3, StatusCode );
							break;
						case '2':
							trace( "Time-of-Day Clock: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"TC3", 3, StatusCode );
							break;
						case '3':
							trace( "Time-of-Day Clock: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"TC7", 3, StatusCode );
							break;
						case '4':
							trace( "Time-of-Day Clock: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"TC4", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
					}
					AtmReq++;
					switch( *AtmReq )
					{
						case '0':
							trace( "High Order Communications: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"HOC1", 4, StatusCode );
							break;
						case '1':
							trace( "High Order Communications: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"HOC2", 4, StatusCode );
							break;
						case '2':
							trace( "High Order Communications: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"HOC3", 4, StatusCode );
							break;
						case '3':
							trace( "High Order Communications: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"HOC4", 4, StatusCode );
							break;
						case '4':
							trace( "High Order Communications: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"HOC5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
					}
					AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "System Disk: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"SYSD1", 5, StatusCode );
							break;
						case '1':
							trace( "System Disk: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"SYSD2", 5, StatusCode );
							break;
						case '2':
							trace( "System Disk: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"SYSD3", 5, StatusCode );
							break;
						case '3':
							trace( "System Disk: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"SYSD4", 5, StatusCode );
							break;
						case '4':
							trace( "System Disk: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"SYSD5", 5, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Magnetic Card Reader/Writer: No Error" );
                            StatusCode += BuiltStatusCode( ( char * )"CR14", 4, StatusCode );
                            break;
						case '1':
							trace( "Magnetic Card Reader/Writer: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"CR15", 4, StatusCode );
							break;
						case '2':
							trace( "Magnetic Card Reader/Writer: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"CR16", 4, StatusCode );
							break;
						case '3':
							trace( "Magnetic Card Reader/Writer: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"CR17", 4, StatusCode );
							break;
						case '4':
							trace( "Magnetic Card Reader/Writer: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"CR18", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Cash Handler: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"CH7", 3, StatusCode );
							break;
						case '1':
							trace( "Cash Handler: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"CH8", 3, StatusCode );
							break;
						case '2':
							trace( "Cash Handler: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"CH9", 3, StatusCode );
							break;
						case '3':
							trace( "Cash Handler: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"CH10", 4, StatusCode );
							break;
						case '4':
							trace( "Cash Handler: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"CH11", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
					}
					AtmReq ++;
					switch( *AtmReq )
					{
						case '0':
							trace( "Depository: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"DF1", 3, StatusCode );
							break;
						case '1':
							trace( "Depository: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"DF2", 3, StatusCode );
							break;
						case '2':
							trace( "Depository: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"DF3", 3, StatusCode );
							break;
						case '3':
							trace( "Depository: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"DF4", 3, StatusCode );
							break;
						case '4':
							trace( "Depository: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"DF5", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
					}
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Receipt Printer: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"RP5", 3, StatusCode );
							break;
						case '1':
							trace( "Receipt Printer: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"RP6", 3, StatusCode );
							break;
						case '2':
							trace( "Receipt Printer: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"RP7", 3, StatusCode );
							break;
						case '3':
							trace( "Receipt Printer: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"RP8", 3, StatusCode );
							break;
						case '4':
							trace( "Receipt Printer: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"RP9", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Journal Printer: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"JP13", 4, StatusCode );
							break;
						case '1':
							trace( "Journal Printer: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"JP14", 4, StatusCode );
							break;
						case '2':
							trace( "Journal Printer: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"JP15", 4, StatusCode );
							break;
						case '3':
							trace( "Journal Printer: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"JP16", 4, StatusCode );
							break;
						case '4':
							trace( "Journal Printer: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"JP17", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    //Reserved Field
                    AtmReq += 2;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Night Safe Depository: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"NSD1", 4, StatusCode );
							break;
						case '1':
							trace( "Night Safe Depository: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"NSD2", 4, StatusCode );
							break;
						case '2':
							trace( "Night Safe Depository: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"NSD3", 4, StatusCode );
							break;
						case '3':
							trace( "Night Safe Depository: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"NSD4", 4, StatusCode );
							break;
						case '4':
							trace( "Night Safe Depository: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"NSD5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Encryptor: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"E6", 2, StatusCode );
							break;
						case '1':
							trace( "Encryptor: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"E7", 2, StatusCode );
							break;
						case '2':
							trace( "Encryptor: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"E8", 2, StatusCode );
							break;
						case '3':
							trace( "Encryptor: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"E9", 2, StatusCode );
							break;
						case '4':
							trace( "Encryptor: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"E10", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Security Camera: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"CAM1", 4, StatusCode );
							break;
						case '1':
							trace( "Security Camera: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"CAM2", 4, StatusCode );
							break;
						case '2':
							trace( "Security Camera: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"CAM3", 4, StatusCode );
							break;
						case '3':
							trace( "Security Camera: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"CAM4", 4, StatusCode );
							break;
						case '4':
							trace( "Security Camera: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"CAM5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Door Access: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"DA1", 3, StatusCode );
							break;
						case '1':
							trace( "Door Access: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"DA2", 3, StatusCode );
							break;
						case '2':
							trace( "Door Access: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"DA3", 3, StatusCode );
							break;
						case '3':
							trace( "Door Access: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"DA4", 3, StatusCode );
							break;
						case '4':
							trace( "Door Access: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"DA5", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Flex Disk: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"FD1", 3, StatusCode );
							break;
						case '1':
							trace( "Flex Disk: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"FD2", 3, StatusCode );
							break;
						case '2':
							trace( "Flex Disk: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"FD3", 3, StatusCode );
							break;
						case '3':
							trace( "Flex Disk: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"FD4", 3, StatusCode );
							break;
						case '4':
							trace( "Flex Disk: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"FD5", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Cassette type 1: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"C1-1", 4, StatusCode );
							break;
						case '1':
							trace( "Cassette type 1: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"C1-2", 4, StatusCode );
							break;
						case '2':
							trace( "Cassette type 1: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"C1-3", 4, StatusCode );
							break;
						case '3':
							trace( "Cassette type 1: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"C1-4", 4, StatusCode );
							break;
						case '4':
							trace( "Cassette type 1: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"C1-5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Cassette type 2: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"C2-1", 4, StatusCode );
							break;
						case '1':
							trace( "Cassette type 2: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"C2-2", 4, StatusCode );
							break;
						case '2':
							trace( "Cassette type 2: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"C2-3", 4, StatusCode );
							break;
						case '3':
							trace( "Cassette type 2: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"C2-4", 4, StatusCode );
							break;
						case '4':
							trace( "Cassette type 2: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"C2-5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Cassette type 3: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"C3-1", 4, StatusCode );
							break;
						case '1':
							trace( "Cassette type 3: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"C3-2", 4, StatusCode );
							break;
						case '2':
							trace( "Cassette type 3: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"C3-3", 4, StatusCode );
							break;
						case '3':
							trace( "Cassette type 3: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"C3-4", 4, StatusCode );
							break;
						case '4':
							trace( "Cassette type 3: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"C3-5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Cassette type 4: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"C4-1", 4, StatusCode );
							break;
						case '1':
							trace( "Cassette type 4: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"C4-2", 4, StatusCode );
							break;
						case '2':
							trace( "Cassette type 4: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"C4-3", 4, StatusCode );
							break;
						case '3':
							trace( "Cassette type 4: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"C4-4", 4, StatusCode );
							break;
						case '4':
							trace( "Cassette type 4: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"C4-5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    AtmReq += 2;//2 Reserved fields
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Statement Printer: No Error" );
							StatusCode += BuiltStatusCode( ( char * )"SP1", 3, StatusCode );
							break;
						case '1':
							trace( "Statement Printer: Routine Error" );
							StatusCode += BuiltStatusCode( ( char * )"SP2", 3, StatusCode );
							break;
						case '2':
							trace( "Statement Printer: Warning" );
							StatusCode += BuiltStatusCode( ( char * )"SP3", 3, StatusCode );
							break;
						case '3':
							trace( "Statement Printer: Suspended" );
							StatusCode += BuiltStatusCode( ( char * )"SP4", 3, StatusCode );
							break;
						case '4':
							trace( "Statement Printer: Fatal Error" );
							StatusCode += BuiltStatusCode( ( char * )"SP5", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    AtmReq += 4;
                    //Hardware Configuration Data
                    while( *AtmReq != '[' )
                    	AtmReq++;

                    AtmReq += 4 ;
                    AtmReq += 3 ;
                    trace( "**** Supplies Status information ****" );
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Card Capture Bin: Not Configured" );
							StatusCode += BuiltStatusCode( ( char * )"CCB1", 4, StatusCode );
							break;
						case '1':
							trace( "Card Capture Bin: Good State" );
							StatusCode += BuiltStatusCode( ( char * )"CCB2", 4, StatusCode );
							break;
						case '2':
							trace( "Card Capture Bin: Media Low" );
							StatusCode += BuiltStatusCode( ( char * )"CCB3", 4, StatusCode );
							break;
						case '3':
							trace( "Card Capture Bin: Media Out" );
							StatusCode += BuiltStatusCode( ( char * )"CCB4", 4, StatusCode );
							break;
						case '4':
							trace( "Card Capture Bin: Overfill" );
							StatusCode += BuiltStatusCode( ( char * )"CCB5", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Cash Handler Reject Bin: Not Configured" );
							StatusCode += BuiltStatusCode( ( char * )"CHRB1", 5, StatusCode );
							break;
						case '1':
							trace( "Cash Handler Reject Bin: Good State" );
							StatusCode += BuiltStatusCode( ( char * )"CHRB2", 5, StatusCode );
							break;
						case '2':
							trace( "Cash Handler Reject Bin: Media Low" );
							StatusCode += BuiltStatusCode( ( char * )"CHRB3", 5, StatusCode );
							break;
						case '3':
							trace( "Cash Handler Reject Bin: Media Out" );
							StatusCode += BuiltStatusCode( ( char * )"CHRB4", 5, StatusCode );
							break;
						case '4':
							trace( "Cash Handler Reject Bin: Overfill" );
							StatusCode += BuiltStatusCode( ( char * )"CHRB5", 5, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Deposit Bin: Not Configured" );
							StatusCode += BuiltStatusCode( ( char * )"DB1", 3, StatusCode );
							break;
						case '1':
							trace( "Deposit Bin: Good State" );
							StatusCode += BuiltStatusCode( ( char * )"DB2", 3, StatusCode );
							break;
						case '2':
							trace( "Deposit Bin: Media Low" );
							StatusCode += BuiltStatusCode( ( char * )"DB3", 3, StatusCode );
							break;
						case '3':
							trace( "Deposit Bin: Media Out" );
							StatusCode += BuiltStatusCode( ( char * )"DB4", 3, StatusCode );
							break;
						case '4':
							trace( "Deposit Bin: Overfill" );
							StatusCode += BuiltStatusCode( ( char * )"DB5", 3, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Receipt Paper: Not Configured" );
							break;
						case '1':
							trace( "Receipt Paper: Good State" );
							break;
						case '2':
							trace( "Receipt Paper: Media Low" );
							break;
						case '3':
							trace( "Receipt Paper: Media Out" );
							break;
						case '4':
							trace( "Receipt Paper: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Journal Paper: Not Configured" );
							StatusCode += BuiltStatusCode( ( char * )"JP3", 3, StatusCode );
							break;
						case '1':
							trace( "Journal Paper: Good State" );
							StatusCode += BuiltStatusCode( ( char * )"JP13", 4, StatusCode );
							break;
						case '2':
							trace( "Journal Paper: Media Low" );
							StatusCode += BuiltStatusCode( ( char * )"JP21", 4, StatusCode );
							break;
						case '3':
							trace( "Journal Paper: Media Out" );
							StatusCode += BuiltStatusCode( ( char * )"JP23", 4, StatusCode );
							break;
						case '4':
							trace( "Journal Paper: Overfill" );
							StatusCode += BuiltStatusCode( ( char * )"JP16", 4, StatusCode );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq += 3;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Night Safe: Not Configured" );
							break;
						case '1':
							trace( "Night Safe: Good State" );
							break;
						case '2':
							trace( "Night Safe: Media Low" );
							break;
						case '3':
							trace( "Night Safe: Media Out" );
							break;
						case '4':
							trace( "Night Safe: Overfill" );
							break;
						default:
							trace( "Message Not Supported" );
							break;
                    }
                    AtmReq += 5;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Type 1 Currency Cassettes: Not Configured" );
							break;
						case '1':
							trace( "Type 1 Currency Cassettes: Good State" );
							break;
						case '2':
							trace( "Type 1 Currency Cassettes: Media Low" );
							break;
						case '3':
							trace( "Type 1 Currency Cassettes: Media Out" );
							break;
						case '4':
							trace( "Type 1 Currency Cassettes: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Type 2 Currency Cassettes: Not Configured" );
							break;
						case '1':
							trace( "Type 2 Currency Cassettes: Good State" );
							break;
						case '2':
							trace( "Type 2 Currency Cassettes: Media Low" );
							break;
						case '3':
							trace( "Type 2 Currency Cassettes: Media Out" );
							break;
						case '4':
							trace( "Type 2 Currency Cassettes: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Type 3 Currency Cassettes: Not Configured" );
							break;
						case '1':
							trace( "Type 3 Currency Cassettes: Good State" );
							break;
						case '2':
							trace( "Type 3 Currency Cassettes: Media Low" );
							break;
						case '3':
							trace( "Type 3 Currency Cassettes: Media Out" );
							break;
						case '4':
							trace( "Type 3 Currency Cassettes: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Type 4 Currency Cassettes: Not Configured" );
							break;
						case '1':
							trace( "Type 4 Currency Cassettes: Good State" );
							break;
						case '2':
							trace( "Type 4 Currency Cassettes: Media Low" );
							break;
						case '3':
							trace( "Type 4 Currency Cassettes: Media Out" );
							break;
						case '4':
							trace( "Type 4 Currency Cassettes: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq += 3;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Statement Paper: Not Configured" );
							break;
						case '1':
							trace( "Statement Paper: Good State" );
							break;
						case '2':
							trace( "Statement Paper: Media Low" );
							break;
						case '3':
							trace( "Statement Paper: Media Out" );
							break;
						case '4':
							trace( "Statement Paper: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    AtmReq ++;
                    switch( *AtmReq )
                    {
						case '0':
							trace( "Statement Ribbon: Not Configured" );
							break;
						case '1':
							trace( "Statement Ribbon: Good State" );
							break;
						case '2':
							trace( "Statement Ribbon: Media Low" );
							break;
						case '3':
							trace( "Statement Ribbon: Media Out" );
							break;
						case '4':
							trace( "Statement Ribbon: Overfill" );
							break;
						default:
							trace( "Message [%c] Not Supported", *AtmReq );
							break;
                    }
                    break;

				case '2':
					trace( "Send supply counters" );
					AtmReq ++;
					memset( &CounterInfo, 0, sizeof( struct EzAtmCounterInfo ) );
					strcpy( CounterInfo.AtmId, AtmId );
					strcpy( CounterInfo.DeviceLogicalGroup, atminfo.AtmLogicalGroup );

					memset( &CounterInfo, 0, sizeof( struct EzAtmCounterInfo ) );
					strcpy( CounterInfo.AtmId, AtmId );
					strcpy( CounterInfo.DeviceLogicalGroup, atminfo.AtmLogicalGroup );

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 4 );
					trace( "Transaction Serial Number:%s", temp );
					AtmReq += 4;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 7 );
					trace( "Accumulated Transaction Count:%s", temp );
					AtmReq += 7;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass1_NotesLeft = atoi( temp );
					trace( "Notes In cassette types 1:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass2_NotesLeft = atoi( temp );
					trace( "Notes In cassette types 2:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass3_NotesLeft = atoi( temp );
					trace( "Notes In cassette types 3:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass4_NotesLeft = atoi( temp );
					trace( "Notes In cassette types 4:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass1_NotesReject = atoi( temp );
					trace( "Notes Rejected In cassette types 1:%s", temp );
					Rcass += atoi( temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass2_NotesReject = atoi( temp );
					trace( "Notes Rejected In cassette types 2:%s", temp );
					Rcass += atoi( temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass3_NotesReject = atoi( temp );
					trace( "Notes Rejected In cassette types 3:%s", temp );
					Rcass += atoi( temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass4_NotesReject = atoi( temp );
					trace( "Notes Rejected In cassette types 4:%s", temp );
					Rcass += atoi( temp );
					sprintf( RejectCass, "%d", Rcass );
					trace( "Notes Rejected cassette :%s", RejectCass );
					CounterInfo.TotalBillReject = Rcass;
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					memset( NotesDisp1, 0, sizeof( NotesDisp1 ) );
					strcpy( NotesDisp1, temp );
					CounterInfo.Cass1_NotesDisp = atoi( temp );
					trace( "Notes Dispensed From cassette types 1:%s", NotesDisp1 );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					memset( NotesDisp2, 0, sizeof(NotesDisp2) );
					strcpy( NotesDisp2, temp );
					CounterInfo.Cass2_NotesDisp = atoi( temp );
					trace( "Notes Dispensed From cassette types 2:%s", NotesDisp2 );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					memset( NotesDisp3, 0, sizeof(NotesDisp3) );
					strcpy( NotesDisp3, temp );
					CounterInfo.Cass3_NotesDisp = atoi( temp );
					trace( "Notes Dispensed From cassette types 3:%s", NotesDisp3 );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					memset( NotesDisp4, 0, sizeof(NotesDisp4) );
					strcpy( NotesDisp4, temp );
					CounterInfo.Cass4_NotesDisp = atoi( temp );
					trace( "Notes Dispensed From cassette types 4:%s", NotesDisp4 );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass1_LastDisp = atoi( temp );
					trace( "Last Transaction Notes Dispensed From cassette types 1:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass2_LastDisp = atoi( temp );
					trace( "Last Transaction Notes Dispensed From cassette types 2:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass3_LastDisp = atoi( temp );
					trace( "Last Transaction Notes Dispensed From cassette types 3:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.Cass4_LastDisp = atoi( temp );
					trace( "Last Transaction Notes Dispensed From cassette types 4:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( RejectCard, AtmReq, 5 );
					trace( "No of Cards Captured:%s", RejectCard );
					CounterInfo.TotalCardRetained = atoi( RejectCard );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					CounterInfo.TotalDeposit = atoi(temp);
					trace( "No of Envelopes Captured:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					trace( "Camera Film Remaining:%s", temp );
					AtmReq += 5;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 5 );
					trace( "Last Envelope Serial Number:%s", temp );
					AtmReq += 5;

					//Update Counterinfo
					if( UpdateCounterInfo( &CounterInfo, atmbuf.CurrentCommand ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in updating Counter info for [%s]", CounterInfo.AtmId );
						return -1;
					}
					break;

				case '3':
					trace( "Send tally information" );
					AtmReq++;

					trace( "Group Number:%c",AtmReq[0] );
					AtmReq++;

					memset( temp, 0,sizeof( temp ) );
					strncpy( temp,"20",2 );
					strncat( temp,AtmReq,2 );
					strncat( temp,"/",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp,"/",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp," | ",3 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp,":",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp,":",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					trace( "Last Cleared Date And Time:%s", temp );
					AtmReq += 2;

					memset( temp, 0,sizeof( temp ) );
					memcpy( temp, AtmReq, 6 );
					trace( "Tally Data: %s", temp );
					break;

				case '4':
					trace( "Send error log information" );
					AtmReq++;

					switch( *AtmReq )
					{
						case 'A':
							trace( "Processor or System logs" );
							break;
						case 'B':
							trace( "Communications logs" );
							break;
						case 'C':
							trace( "SST devices logs" );
							break;
						default:
							trace( "Message [ %c ] Not Supported", *AtmReq );
							break;
					}
					AtmReq++;
					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 2 );
					trace( "New Entries: %s", temp );
					AtmReq += 2;

					memset( temp, 0,sizeof( temp ) );
					strncpy( temp,"20",2 );
					strncat( temp,AtmReq,2 );
					strncat( temp,"/",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp,"/",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp," | ",3 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp,":",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp,":",1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					trace( "Last Cleared Date And Time:%s", temp );
					AtmReq += 2;
					AtmReq ++;

					if( strcmp( AtmReq,"\0" ) != 0 )
					{
						AtmReq --;
						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 2 );
						trace( "Month log entry made:%s", temp );
						AtmReq += 2;

						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 2 );
						trace( "Day log entry made:%s", temp );
						AtmReq += 2;

						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 2 );
						trace( "Hour log entry made:%s", temp );
						AtmReq += 2;

						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 2 );
						trace( "Minute log entry made :%s", temp );
						AtmReq += 2;

						trace( "Device Identification Graphic:%c", *AtmReq );
						switch( *AtmReq )
						{
							case 'A':
								trace( "Processor or System logs" );
								break;
							case 'B':
								trace( "Communications logs" );
								break;
							case 'C':
								trace( "SST devices logs" );
								break;
							default:
								trace( "Message [ %c ] Not Supported", *AtmReq );
								break;
						}
						AtmReq++;

						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 2 );
						trace( "Maintenance Status :%s", temp );
						AtmReq += 2;

						trace( "Severity:%c", *AtmReq++ );
						trace( "Part Number:%c", *AtmReq++ );
						trace( "Maintenance Data:%s", AtmReq );
					}
					break;

				case '5':
					trace( "Send date/time information" );
					AtmReq++;

					switch( *AtmReq )
					{
						case '0':
							trace( "TOD Clock Status: Actual" );
							break;
						case '1':
							trace( "TOD Clock Status: Default" );
							break;
						case '2':
							trace( "TOD Clock Status: Malfunction" );
							break;
						default:
							trace( "Message [ %c ] Not Supported", *AtmReq );
							break;
					}
					AtmReq++;

					memset( temp, 0,sizeof( temp ) );
					strncpy( temp, "20" , 2 );
					strncat( temp, AtmReq , 2 );
					strncat( temp, "/" , 1 );
					AtmReq += 2;

					strncat( temp,AtmReq,2 );
					strncat( temp, "/", 1 );
					AtmReq += 2;

					strncat( temp, AtmReq, 2 );
					strncat( temp, " | ",3 );
					AtmReq += 2;

					strncat( temp, AtmReq, 2 );
					strncat( temp, ":" , 1 );
					AtmReq += 2;
					strncat( temp, AtmReq , 2 );
					strncat( temp, ":" , 1 );
					AtmReq += 2;
					strncat( temp, AtmReq, 2 );
					trace( "Terminal Date And Time:%s", temp );
					break;

				case '6':
					trace( "Send configuration ID" );
					AtmReq ++;
					trace( "Configuration ID:%s", AtmReq );
					if( atminfo.AtmConfigId != atoi( AtmReq ) )
					{
						trace( DEBUG_TEST, "Configuration ID[ %s ] not matched", atminfo.AtmConfigId );
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
						trace( DEBUG_TEST, "Configuration ID[ %s ] matched", atminfo.AtmConfigId );
						memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
						AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
						AtmCont.CommandType = GO_IN_SERVICE;
						memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

						if( PostContMsg( AtmCont, AtmId ) < 0 )
						{
							trace( "Failed in PostContMsg" );
							return -1;
						}
					}
					break;

				case 'F':
					trace( "EKC retrieve hallmark key" );
					AtmReq++;

					if( *AtmReq  == '1' )
						trace( "The EKC has reported a routine error" );
					else if( *AtmReq == '4' )
						trace( "Fatel Error" );
					else
					{
						switch( *AtmReq )
						{
							case '0':
								trace( "The EKC is operating normally" );
								break;
							case '2':
								trace( "The EKC has reported a warning condition" );
								break;
							case '3':
								trace( "The EKC has reported a suspend condition" );
								break;
							case '5':
								trace( "The EKC has not been initialised and does not contain a Hallmark key" );
								break;
							case '6':
								trace( "The EKC cannot perform DEA 2 block encryption" );
								break;
							default:
								trace( "The EKC is operating normally" );
								break;
						}
						AtmReq++;

						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 4 );
						trace( "Authentication Block Length:%s", temp );
						AtmReq += 4;
						trace( "Authentication Block Data:%s",AtmReq );
					}
					break;

				case 'H':
					trace( "Hardware configuration data" );
					AtmReq++;
					if( *AtmReq == 'A' )
					{
						trace( "Hardware configuration Id Identifier :%c", *AtmReq++ );
						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 4  );//HardwareConfigurationId
						trace( "Hardware configuration Id :%s", temp );
					}
					else
						trace( "Bad Identifier" );

					AtmReq += 4;

					AtmReq ++;//0x1c
					if( *AtmReq ==  'B' )
					{
						trace( "Product Class Identifier :%c",AtmReq[0] );
						AtmReq++;
						memset( temp, 0, sizeof( temp ) );
						memcpy( temp, AtmReq, 4 );
						trace( "Product Class :%s", temp );
					}
					else
						trace( "Bad Identifier" );
					AtmReq += 4;

					AtmReq ++;//0x1c

					if( *AtmReq == 'C' )
					{
						trace( "Hardware configuration Identifier :%c", *AtmReq++ );
						if( strncmp(AtmReq, "\0", 1 ) != 0 )
						{
							trace( "Device Identifier: %c", *AtmReq++ );
							OffSet = ( char * ) memchr( AtmReq, 0x1d, 41  );
							memset( temp, 0, sizeof( temp ) );
							if( OffSet != NULL )
							{
								memcpy( temp, AtmReq, ( OffSet - AtmReq ) );
								trace( "Hardware configuration:%s", temp );
								AtmReq = OffSet;
							}
							AtmReq++;// 0x1d

							trace( "Device Identifier:%c", *AtmReq++ );
							OffSet = ( char * ) memchr( AtmReq, 0x1c, 41  );
                            if( OffSet != NULL )
                            {
                            	memset( temp, 0, sizeof( temp ) );
                            	memcpy( temp, AtmReq, ( OffSet - AtmReq ) );
                            	trace( "Hardware configuration:%s", temp );
                            	AtmReq = OffSet;
                            }
                            AtmReq++;// 0x1c

                            trace( "Data Identifier:%c", *AtmReq++ );
                            trace( "Data:%s", AtmReq );
						}
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					break;

				case 'I':
					trace( "Supplies data" );
					AtmReq ++;
					if( *AtmReq == 'A' )
						trace( "Supplies Status Identifier :%c", *AtmReq );
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					break;

				case 'J':
					trace( "Fitness data" );
					AtmReq++;
					if( *AtmReq == 'A')
						trace( "Hardware Fitness Identifier :%c", *AtmReq );
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					break;

				case 'K':
					trace( "Tamper and sensor status data" );
					AtmReq++;
					if( *AtmReq == 'A' )
					{
						trace( "Sensor Status Identifier :%c", *AtmReq++ );
						OffSet = ( char * ) memchr( AtmReq, 0x1c, 41  );
						if( OffSet != NULL )
						{
							memset( temp, 0, sizeof( temp ) );
							memcpy( temp, AtmReq, ( OffSet - AtmReq ) );
							trace( "Sensor Status :%s", temp );
							AtmReq = OffSet;
						}
						AtmReq++;// 0x1c
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					AtmReq += 4;
					if( *AtmReq == 'B' )
					{
						trace( "Tamper Indicator Identifier :%c", *AtmReq++ );
						OffSet = ( char * ) memchr( AtmReq, 0x1c, 41  );
						if( OffSet != NULL )
						{
							memset( temp, 0, sizeof( temp ) );
							memcpy( temp, AtmReq, ( OffSet-AtmReq )  );
							trace( "Tamper Status :%s", temp );
							AtmReq = OffSet;
						}
						AtmReq++;// 0x1c
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					AtmReq += 4;
					if( *AtmReq == 'C' )
					{
						trace( "Data Identifier :%c", *AtmReq++ );
						trace( "Data :%s",AtmReq );
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					break;

				case 'L':
					trace( "Software ID and release number data" );
					AtmReq++;
					if( *AtmReq == 'A' )
					{
						trace( "Release Number Identifier :%c", *AtmReq++ );
						memset( temp, 0, sizeof( temp ) );
						strncpy( temp, AtmReq, 2 );
						AtmReq += 2;
						strncat( temp, ".", 2 );
						strncat( temp, AtmReq, 2 );
						strncat( temp, ".", 2 );
						AtmReq += 2;
						strncat( temp, AtmReq, 2 );
						trace( "NDC Release Number :%s", temp );
						AtmReq += 2;
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					AtmReq += 4;
					if( *AtmReq == 'B' )
					{
						trace( "Software ID Identifier :%c", *AtmReq++ );
						OffSet = ( char * ) memchr( AtmReq, 0x1c, 41 );
						if( OffSet != NULL )
						{
							memset( temp, 0, sizeof( temp ) );
							memcpy( temp, AtmReq, ( OffSet - AtmReq ) );
							AtmReq = OffSet;
						}
						if( strncmp( temp, "G530-0205", 9 ) == 0 )
							trace( "Software Id - %s (NDC+ Native mode)", temp );
						else if( strncmp( temp,"G530-0206",9 ) == 0 )
							trace( "Software Id -  %s (NDC+ Diebold Emulation mode)", temp );
						else
							trace( "Invaild Software Id - %s", temp );

						AtmReq++;// 0x1c
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					AtmReq += 4;
					if( *AtmReq == 'C' )
					{
						trace( "Data Identifier :%c", *AtmReq++ );
						trace( "Data :%s",AtmReq );
					}
					else
						trace( "Bad Identifier [%c]", *AtmReq );
					break;

				case 'M':
					trace( "Local configuration option digits" );
					break;

				default:
					trace( "Message [ %c ]Not Supported", *AtmReq );
					break;
			}
			break;

		case '8':
			trace( "Device Fault" );
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
			AtmReq ++;
			AtmReq ++;// 0x1c
			if( ServeStatusChangeMsg( AtmReq, strlen( AtmReq ), AtmId, StatusCode ) < 0 )
				trace( "Failed in ServeStatusChangeMsg" );
			break;

		default:
			trace( "Message [ %c ] Not Supproted", *AtmReq );
			break;
	}
	return 1;
}

int EzNDC :: ServeStatusChangeMsg( char * AtmReq, int Size , char *AtmId , char *StatusCode )
{
	char Luno[ LUNO_SIZE + 1 ], *p, *OffSetPtr, temp[ TEMP + 1 ], Byte[ BYTE + 1 ] ;
	char DenominationId, CassetteType,  DispLogicBuf[ DISP + 1 ];
	int i, NoOfBills = 0, NoOfBillDump = 0, DispencedAmount = 0, Denomination = 0, ConfigId = 0;
	bool RevFlag = false, MemFlag = false, SOPFlag = false;
	struct EzAtmController AtmCont;
	struct EzDevMsg devmsg;

	memset( &devmsg, 0, sizeof( struct EzDevMsg ) );
	memcpy( &devmsg, &atmbuf.DevMsg, sizeof( struct EzDevMsg ) );


	memset( &ezatmproperty, 0, sizeof( struct EzAtmProperty ) );
	if( ReadAtmProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, devmsg.TxnCode, 0, devmsg.AcqCurrencyCode, &ezatmproperty ) < 0 )
		trace( DEBUG_ERROR, "Unable to Reading EzAtmProperty");

	switch ( *AtmReq )
	{
		case 'A':
			trace( "Time-of-day clock fault" );
			StatusCode += BuiltStatusCode( ( char * )"!A", 2, StatusCode );
			BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!A", atmbuf.StaticStatus );
			AtmReq ++;
			switch( *AtmReq )
			{
				case '1':
					trace( " Clock reset but running" );
					StatusCode += BuiltStatusCode( ( char * )"TC1", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"TC1", atmbuf.StaticStatus );
					break;
				case '2':
					trace( " Clock has stopped" );
					StatusCode += BuiltStatusCode( ( char * )"TC2", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"TC2", atmbuf.StaticStatus );
					break;
				default:
					trace( "Message [ %c] Not supported", *AtmReq );
					break;
			}
			AtmReq ++;
			switch( *AtmReq )
			{
				case '2':
					trace( " Warning - clock reset" );
					StatusCode += BuiltStatusCode( ( char * )"TC3", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"TC3", atmbuf.StaticStatus );
					break;
				case '4':
					trace( " Fatal - clock malfunction" );
					StatusCode += BuiltStatusCode( ( char * )"TC4", 3, StatusCode );
					BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"TC4", atmbuf.StaticStatus );
					break;
				default:
					trace( "Message Not supported" );
					break;
			}
			break;

			case 'B':
				trace( "Power failure status change request" );
				StatusCode += BuiltStatusCode( ( char * )"!PF", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!PF", atmbuf.StaticStatus );
				AtmReq++;
				trace( "Device Status < %s >", AtmReq );
				ConfigId = atoi( AtmReq );

				memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
				memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

				if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
					trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
				else
					trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );

				trace("DownloadCheckReq[%c]", ezatmproperty.DownloadCheckReq);
				if( ezatmproperty.DownloadCheckReq == 'Y' || ezatmproperty.DownloadCheckReq == 'y' )
				{
					trace( DEBUG_TEST, "Download check required");
					if( atminfo.AtmConfigId == ConfigId )
					{
						memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
						AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
						AtmCont.CommandType = GO_IN_SERVICE;
						memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
						if( PostContMsg( AtmCont, AtmId ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed in PostContMsg" );
							return -1;
						}
					}
					else
					{
						trace("Atm ConfigId[%d] not matching with ConfigId[%d]", ConfigId, atminfo.AtmConfigId);
						memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
						AtmCont.MsgType = EZ_ATM_DOWNLOAD_REQ;
						AtmCont.DownloadType = DOWNLOAD_ALL;
						memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

						if( PostContMsg( AtmCont, AtmId ) < 0 )
						{
							trace( "Failed in PostContMsg");
							return -1;
						}
					}
				}
				else
				{
					trace( DEBUG_TEST, "Download check not required");
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

			case 'D':
				trace( "Card reader fault" );
				StatusCode += BuiltStatusCode( ( char * )"!CR", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CR", atmbuf.StaticStatus );
				AtmReq++;
				switch( *AtmReq )
				{
					case '0':
						trace( "severity, diagnostic status or supplies status changes" );
						StatusCode += BuiltStatusCode( ( char * )"CR1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR1", atmbuf.StaticStatus );
						break;
					case '1':
						trace( "The cardholder did not take his card within the allowed time and it was captured or jammed" );
						StatusCode += BuiltStatusCode( ( char * )"CR2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR2", atmbuf.StaticStatus );
						break;
					case '2':
						trace( "The mechanism failed to eject the card and it was captured or jammed" );
						StatusCode += BuiltStatusCode( ( char * )"CR3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR3", atmbuf.StaticStatus );
						break;
					case '3':
						trace( "The mechanism failed to update the requested tracks on the card" );
						StatusCode += BuiltStatusCode( ( char * )"CR4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR4", atmbuf.StaticStatus );
						break;
					case '4':
						trace( "Invalid track data was received from Central" );
						StatusCode += BuiltStatusCode( ( char * )"CR5", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR5", atmbuf.StaticStatus );
						break;
					case '6':
						trace( "CIM86 malfunction" );
						StatusCode += BuiltStatusCode( ( char * )"CR6", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR6", atmbuf.StaticStatus );
						break;
					case '7':
						trace( "Error in track data" );
						StatusCode += BuiltStatusCode( ( char * )"CR7", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR7", atmbuf.StaticStatus );
						break;
					case '8':
						trace( "Communications error with CIM86" );
						StatusCode += BuiltStatusCode( ( char * )"CR8", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR8", atmbuf.StaticStatus );
						break;
					case '9':
						trace( "CIM interface PCB malfunction" );
						StatusCode += BuiltStatusCode( ( char * )"CR9", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR9", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}
				AtmReq++;
				switch( *AtmReq )
				{
					case '0':
						trace( "Last CIM 86 Verification was good" );
						StatusCode += BuiltStatusCode( ( char * )"CR10", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR10", atmbuf.StaticStatus );
						break;
					case '1':
						trace( "CIM 68 Verification caused the status message to be sent when previous severity value was '0'" );
						StatusCode += BuiltStatusCode( ( char * )"CR11", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR11", atmbuf.StaticStatus );
						break;
					case '2':
						trace( "CIM 68 Verification caused the status message to be sent when previous severity value was '1'" );
						StatusCode += BuiltStatusCode( ( char * )"CR12", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR12", atmbuf.StaticStatus );
						break;
					case '4':
						trace( "CIM 68 Verification caused the status message to be sent when previous severity value was '2' or '4'" );
						StatusCode += BuiltStatusCode( ( char * )"CR13", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CR13", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}
				break;

			case 'E':
				trace( "Cash handler" );
				StatusCode += BuiltStatusCode( ( char * )"!CH", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CH", atmbuf.StaticStatus );
				char DispenserCode;
				DispenserCode = *AtmReq;
				AtmReq++;

				switch( *AtmReq )
				{
					case '0':
						trace( "Successful operation, but an exception condition occurred which is detailed in later fields" );
						StatusCode += BuiltStatusCode( ( char * )"CH1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CH1", atmbuf.StaticStatus );
						devmsg.RespCode = EZLINK_RC_DispencedFully;
						break;

					case '1':
						trace( "Short dispense" );//Partial reversal
						StatusCode += BuiltStatusCode( ( char * )"CH2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CH2", atmbuf.StaticStatus );
						devmsg.RespCode = EZLINK_RC_PartialDispense;
						break;

					case '2':
					case '4':
						trace( "No notes dispensed" );//Full reversal
						StatusCode += BuiltStatusCode( ( char * )"CH3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CH3", atmbuf.StaticStatus );
						devmsg.RespCode = EZLINK_RC_UnableDispense;
						break;

					case '3':
						trace( "Faulty dispense. Notes dispensed unknown" );//Suspect

						StatusCode += BuiltStatusCode( ( char * )"CH4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CH4", atmbuf.StaticStatus );
						devmsg.RespCode = EZLINK_RC_UncertainDispense;
						break;

					case '5'://Suspect
						trace( "Some notes have been retracted following a Present and Notes Not Taken time-out. The number of notes retracted is unknown" );

						StatusCode += BuiltStatusCode( ( char * )"CH6", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"CH6", atmbuf.StaticStatus );

						devmsg.RespCode = EZLINK_RC_UncertainDispense;
						break;

					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}

				AtmReq++;
				if( DispenserCode == '1' )
				{
					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 2 );
					NoOfBills = atoi( temp  );
					trace( "No of Notes dispensed from Cassette type 1 [%d]", NoOfBills );

					DenominationId = 'A';
					memset( temp, 0, sizeof( temp ) );
					if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
					{
						trace( "Unable to get Denomination for CassetteType< %c >", DenominationId );
						return -1;
					}

					DispencedAmount += ( NoOfBills * Denomination  );
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%02d", NoOfBills );
					PackDispLogicBuf( temp, DenominationId, DispLogicBuf );
					trace( DEBUG_TEST, "Reformed DispLogicBuf[%s]", DispLogicBuf );
					CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
					AtmReq += 2;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 2 );
					trace( "No of Notes dispensed from Cassette type 2 [%d]",NoOfBills );

					DenominationId = 'B';
					memset( temp, 0, sizeof( temp ) );
					if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
					{
						trace( "Unable to get Denomination for CassetteType< %c >", DenominationId );
						return -1;
					}

					DispencedAmount += ( NoOfBills * Denomination  );
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%02d", NoOfBills );
					PackDispLogicBuf( temp, DenominationId, DispLogicBuf );
					trace( DEBUG_TEST, "Reformed DispLogicBuf[%s]", DispLogicBuf );
					CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
					AtmReq += 2;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 2 );
					trace( "No of Notes dispensed from Cassette type 3 [%d]",NoOfBills );

					DenominationId = 'C';
					memset( temp, 0, sizeof( temp ) );
					if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
					{
						trace( "Unable to get Denomination for CassetteType< %c >", DenominationId );
						return -1;
					}

					DispencedAmount += ( NoOfBills * Denomination  );
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%02d", NoOfBills );
					PackDispLogicBuf( temp, DenominationId, DispLogicBuf );
					trace( DEBUG_TEST, "Reformed DispLogicBuf[%s]", DispLogicBuf );
					CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
					AtmReq += 2;

					memset( temp, 0, sizeof( temp ) );
					memcpy( temp, AtmReq, 2 );
					trace( "No of Notes dispensed from Cassette type 4 [%d]",NoOfBills );

					CassetteType = 'D';
					memset( temp, 0, sizeof( temp ) );
					if( GetDenomination( denominfo, DenominationId, &Denomination ) < 0 )
					{
						trace( "Unable to get Denomination for CassetteType< %c >", DenominationId );
						return -1;
					}

					DispencedAmount += ( NoOfBills * Denomination  );
					memset( temp, 0, sizeof( temp ) );
					sprintf( temp, "%02d", NoOfBills );
					PackDispLogicBuf( temp, DenominationId, DispLogicBuf );
					trace( DEBUG_TEST, "Reformed DispLogicBuf[%s]", DispLogicBuf );
					CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
					AtmReq += 2;

					memset( atmbuf.DispenceLogicBuf, 0, sizeof(atmbuf.DispenceLogicBuf) );
					strcpy( atmbuf.DispenceLogicBuf, DispLogicBuf );
					sprintf( devmsg.DispAmount, "%d.00", DispencedAmount );
				}
				else
					AtmReq += 8;
				trace("test1< %s >", AtmReq );
				if( *AtmReq == DEVICE_FS )
				{
					AtmReq++; //0x1C
					for( int i = 0; i < 5; i++ )
					{
						if( i == 0 )
							trace("Severity information related to complete device");
						else
							trace("Severity related to cassette type %d", i );
						switch( *AtmReq )
						{
							case '0':
								trace("No new state");
								break;
							case '1':
								trace("Sufficient notes");
								break;
							case '2':
								trace("Notes low");
								break;
							case '3':
								trace("Out of notes");
								break;
							case '4':
								trace("Overfill condition");
								break;
							default:
								trace("Unknown Status<%c>", *AtmReq );
								break;
						}
						AtmReq ++;
					}
				}

				trace("test2< %s >", AtmReq );
				//if( *AtmReq == DEVICE_FS )
				//{
					//AtmReq++; //0x1C
					AtmReq += 24;
					/*memset( temp, 0, sizeof( temp ) );
					OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 30 );
					if( OffSetPtr != NULL )
					{
						memcpy( temp, AtmReq, ( OffSetPtr - AtmReq ) );
						trace("Diagnostic Status< %s >", temp );
						AtmReq = OffSetPtr;
					}
					else
					{
						AtmReq += 24;
						trace("< %s >", AtmReq );
					}*/
				//}
				trace("test3< %s >", AtmReq );
				//if( *AtmReq == DEVICE_FS )
				{
					//Commented By Ram On 171210
					//AtmReq++; //0x1C
					for( int i = 0; i < 5; i++ )
					{
						if( i == 0 )
						{
							trace("State of reject bin");
							DenominationId = 'R';
						}
						else
						{
							trace("State of cassette type %d", i );
							switch( i )
							{
								case 1:
									DenominationId = 'A';
									break;
								case 2:
									DenominationId = 'B';
									break;
								case 3:
									DenominationId = 'C';
									break;
								case 4:
									DenominationId = 'D';
									break;
							}
						}
						switch( *AtmReq )
						{
							case '0':
								trace("No new state");
								break;
							case '1':
								trace("Sufficient notes");
								break;
							case '2':
								trace("Notes low DenominationId-%c", DenominationId);
								memset( temp, 0, sizeof( temp ) );
							//	CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
								memset( temp, 0, sizeof( temp ) );
								sprintf( temp, "LOC-%c", DenominationId );
								StatusCode += BuiltStatusCode( temp, strlen(temp), StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, temp, atmbuf.StaticStatus );
								break;
							case '3':
								trace("Out of notes DenominationId-%c", DenominationId);
								memset( temp, 0, sizeof( temp ) );
								CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
								sprintf( temp, "OFN-%c", DenominationId );
								StatusCode += BuiltStatusCode( temp, strlen(temp), StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, temp, atmbuf.StaticStatus );
								break;
							case '4':
								trace("Overfill condition DenominationId-%c", DenominationId);
								memset( temp, 0, sizeof( temp ) );
								CheckAndSetDenomStatus( NDC, temp, DenominationId, denominfo );
								sprintf( temp, "OVC-%c", DenominationId );
								StatusCode += BuiltStatusCode( temp, strlen(temp), StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, temp, atmbuf.StaticStatus );
								break;
							default:
								trace("Unknown Status<%c>", *AtmReq );
								break;
						}
						AtmReq ++;
					}
				}

				if( devmsg.RespCode == EZLINK_RC_PartialDispense )
				{
					if( ezatmproperty.PartialReversalReq == 'N' )
					{
						devmsg.RespCode = EZLINK_RC_UnableDispense;
						RevFlag = true;
					}
				}

				memset( &atmbuf.DevMsg, 0, sizeof( struct EzDevMsg ) );
				memcpy( &atmbuf.DevMsg, &devmsg, sizeof( struct EzDevMsg ) );
				//atmbuf.CurrentState = REVERSAL;

				if( atmbuf.CurrentState == TRANSACTIONRESPONSE )
				{
					if( ( devmsg.TxnCode/10000 == 1 ) && devmsg.RespCode != EZLINK_RC_DispencedFully )
					{
						devmsg.MsgType = EZLINK_TXN_ReversalAdviceRequest;
						if( PostTxnMsg( &devmsg, AtmId ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
							return -1;
						}
					}

					if( devmsg.RespCode != EZLINK_RC_DispencedFully )
					{
						trace( DEBUG_NORMAL, "Routing to BuildAndPostFuncMsg");
						if( RevFlag == true )
							devmsg.RespCode = EZLINK_RC_LowCash;

						devmsg.MsgType = EZLINK_TXN_TxnResponse;
						//Uncommented Hari 28/9/2012
						if( BuildAndPostFuncMsg( devmsg ) < 0 )
						{
							trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
							return -1;
						}
					}
				}
				MemFlag = true;
				break;

			case 'F':
				trace( "Depository fault" );
				StatusCode += BuiltStatusCode( ( char * )"!DF", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DF", atmbuf.StaticStatus );

				AtmReq ++;
				switch( *AtmReq )
				{
					case '0':
						trace("Successful operation, but an exception condition occurred and is detailed in the following field");
						StatusCode += BuiltStatusCode( ( char * )"DF0", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF0", atmbuf.StaticStatus );
						break;
					case '1':
						trace("Time-out on cardholder deposit");
						StatusCode += BuiltStatusCode( ( char * )"DF1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF1", atmbuf.StaticStatus );
						break;
					case '2':
						trace("Failure to enable mechanism for a deposit");
						StatusCode += BuiltStatusCode( ( char * )"DF2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF2", atmbuf.StaticStatus );
						break;
					case '3':
						trace("Envelope/document jam or envelope/document deposit failed. The cardholder has access");
						StatusCode += BuiltStatusCode( ( char * )"DF3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF3", atmbuf.StaticStatus );
						break;
					case '4':
						trace("Envelope/document jam or envelope/document deposit failed. The cardholder does not have access");
						StatusCode += BuiltStatusCode( ( char * )"DF3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"DF3", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}
				AtmReq += 2 ;

				trace("Error Severity[%c]", *AtmReq );
				AtmReq += 2;

				if( *AtmReq == DEVICE_FS )
				{
					AtmReq++; //0x1C
					memset( temp, 0, sizeof( temp ) );
					OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 24 );
					if( OffSetPtr != NULL )
					{
						memcpy( temp, AtmReq, ( OffSetPtr - AtmReq ) );
						trace("Diagnostic Status< %s >", temp );
						AtmReq = OffSetPtr;
					}
					else
						trace("< %s >", AtmReq );
				}

				if( *AtmReq == DEVICE_FS )
				{
					AtmReq++; //0x1C
					trace("Supplies Status");
					switch( *AtmReq )
					{
						case '0':
							trace("No new state or state not determined");
							break;
						case '1':
							trace("Good");
							break;
						case '2':
							trace("Overfill");
							break;
						default:
							trace("Unknown Status<%c>", *AtmReq );
							break;
					}
				}

				break;

			case 'G':
				trace( "Receipt printer fault" );
				StatusCode += BuiltStatusCode( ( char * )"!RP", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!RP", atmbuf.StaticStatus );
				AtmReq ++;
				switch( *AtmReq )
				{
					case '0':
						trace( "Successful print" );
						StatusCode += BuiltStatusCode( ( char * )"RP1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"RP1", atmbuf.StaticStatus );
						break;
					case '1':
						trace( "Print operation not successfully completed" );
						StatusCode += BuiltStatusCode( ( char * )"RP2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"RP2", atmbuf.StaticStatus );
						break;
					case '2':
						trace( "Device not configured" );
						StatusCode += BuiltStatusCode( ( char * )"RP3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"RP3", atmbuf.StaticStatus );
						break;
					case '4':
						trace( "Cancel Key pressed during sideways receipt prints" );
						StatusCode += BuiltStatusCode( ( char * )"RP4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"RP4", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}
				break;

			case 'H':
				trace( "Journal printer fault" );
				StatusCode += BuiltStatusCode( ( char * )"!JP", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!JP", atmbuf.StaticStatus );
				AtmReq ++;
				switch( *AtmReq )
				{
					case '0':
						trace( "Successful print" );
						StatusCode += BuiltStatusCode( ( char * )"JP1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP1", atmbuf.StaticStatus );
						break;
					case '1':
						trace( "Print operation not successfully completed" );
						StatusCode += BuiltStatusCode( ( char * )"JP2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP2", atmbuf.StaticStatus );
						break;
					case '2':
						trace( "Device not configured" );
						StatusCode += BuiltStatusCode( ( char * )"JP3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP3", atmbuf.StaticStatus );
						break;
					case '6':
						trace( "Journal Printer backup activated" );
						StatusCode += BuiltStatusCode( ( char * )"JP4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP4", atmbuf.StaticStatus );
						break;
					case '7':
						trace( "Journal Printer backup and reprint terminated" );
						StatusCode += BuiltStatusCode( ( char * )"JP5", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP5", atmbuf.StaticStatus );
						break;
					case '8':
						trace( "Journal printer backup reprint started" );
						StatusCode += BuiltStatusCode( ( char * )"JP6", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP6", atmbuf.StaticStatus );
						break;
					case '9':
						trace( "Journal Printer backup halted" );
						StatusCode += BuiltStatusCode( ( char * )"JP7", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP7", atmbuf.StaticStatus );
						break;
					case ':':
						trace( "Journal Printer backup log security error" );
						StatusCode += BuiltStatusCode( ( char * )"JP8", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP8", atmbuf.StaticStatus );
						break;
					case ';':
						trace( "Journal Printer backup reprint halted" );
						StatusCode += BuiltStatusCode( ( char * )"JP9", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP9", atmbuf.StaticStatus );
						break;
					case '<':
						trace( "Journal Printer backup tamper state entered" );
						StatusCode += BuiltStatusCode( ( char * )"JP10", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP10", atmbuf.StaticStatus );
						break;
					case '=':
						trace( "Journal in dual mode print operation successful" );
						StatusCode += BuiltStatusCode( ( char * )"JP11", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP11", atmbuf.StaticStatus );
						break;
					case '>':
						trace( "Journal in dual mode print operation not successful" );
						StatusCode += BuiltStatusCode( ( char * )"JP12", 4, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"JP12", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}
				break;

			case 'K':
				trace( "Night safe depository fault" );
				StatusCode += BuiltStatusCode( ( char * )"!NSD", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!NSD", atmbuf.StaticStatus );
				break;

			case 'L':
				trace( "Encryptor fault" );
				StatusCode += BuiltStatusCode( ( char * )"!EF", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!EF", atmbuf.StaticStatus );
				AtmReq ++;
				switch( *AtmReq )
				{
					case '1':
						trace( "Encryptor error" );
						StatusCode += BuiltStatusCode( ( char * )"E1", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"E1", atmbuf.StaticStatus );
						break;
					case '2':
						trace( "Encryptor not configured" );
						StatusCode += BuiltStatusCode( ( char * )"E2", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"E2", atmbuf.StaticStatus );
						break;
					case '3':
						trace( "EKC tampering detected" );
						StatusCode += BuiltStatusCode( ( char * )"E3", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"E3", atmbuf.StaticStatus );
						break;
					case '4':
						trace( "EKC keyspace set-up is illegal" );
						StatusCode += BuiltStatusCode( ( char * )"E4", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"E4", atmbuf.StaticStatus );
						break;
					case '5':
						trace( "EKC communications failure" );
						StatusCode += BuiltStatusCode( ( char * )"E5", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"E5", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c] Not supported", *AtmReq );
						break;
				}
				break;

			case 'M':
				trace( "Camera fault" );
				StatusCode += BuiltStatusCode( ( char * )"!CAM", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CAM", atmbuf.StaticStatus );
				break;

			case 'N':
				trace( "Door access fault" );
				StatusCode += BuiltStatusCode( ( char * )"!DA", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DA", atmbuf.StaticStatus );
				AtmReq ++;
				memset( temp, 0, sizeof( temp ) );
				memcpy( temp, AtmReq, 1 );
				trace( "Error indicating that access is possibly inhibited" );
				AtmReq ++;
				memset( temp, 0, sizeof( temp ) );
				memcpy( temp, AtmReq, 1 );
				trace( "Error indicating a warning. Local intervention required" );
				break;

			case 'P':
				trace( "Sensors fault" );
				StatusCode += BuiltStatusCode( ( char * )"!SF", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!SF", atmbuf.StaticStatus );
				AtmReq ++;
				switch( *AtmReq )
				{
					case '2':
						trace( "Supervisor Mode Change" );
						AtmReq ++;
						switch( *AtmReq )
						{
							case '0':
								trace( "Supervisor mode exit" );
								StatusCode += BuiltStatusCode( ( char * )"S1", 2, StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S1", atmbuf.StaticStatus );
								SOPFlag = true;
								break;
							case '1':
								trace( "Supervisor mode entry" );
								StatusCode += BuiltStatusCode( ( char * )"S2", 2, StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S2", atmbuf.StaticStatus );
								break;
							default:
								trace( "Message [ %c ]not supported" , *AtmReq );
								break;
						}
						break;

					case '3':
						trace( "Alarm Status change" );
						StatusCode += BuiltStatusCode( ( char * )"S3", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S3", atmbuf.StaticStatus );
						break;

					case '4':
						trace( "In Service Supervisor change" );
						AtmReq ++;
						switch( *AtmReq )
						{
							case '0':
								trace( "In Service Supervisor mode exit" );
								StatusCode += BuiltStatusCode( ( char * )"S4", 2, StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S4", atmbuf.StaticStatus );
								break;
							case '1':
								trace( "In Service Supervisor mode entry" );
								StatusCode += BuiltStatusCode( ( char * )"S5", 2, StatusCode );
								BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S5", atmbuf.StaticStatus );
								break;
							default:
								trace( "Message [ %c ]not supported" , *AtmReq );
								break;
						}
						break;

					case '5':
						trace( "Full TI and full alarms change detected" );
						StatusCode += BuiltStatusCode( ( char * )"S6", 2, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S6", atmbuf.StaticStatus );
						break;

					default:
						if( ( *AtmReq == '1' ) || ( *AtmReq == '3' ) )
						{
							trace( " TI sensor/Alarm Status change" );
							AtmReq += 2;
							switch( *AtmReq )
							{
								case '0':
									trace( "Vibration and/or heat sensor inactive" );
									StatusCode += BuiltStatusCode( ( char * )"S7", 2, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S7", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Vibration and/or heat sensor active" );
									StatusCode += BuiltStatusCode( ( char * )"S8", 2, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S8", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Door contact sensor inactive" );
									StatusCode += BuiltStatusCode( ( char * )"S9", 2, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S9", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Door contact sensor active" );
									StatusCode += BuiltStatusCode( ( char * )"S10", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S10", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Silent signal sensor inactive" );
									StatusCode += BuiltStatusCode( ( char * )"S11", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S11", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Silent signal sensor active" );
									StatusCode += BuiltStatusCode( ( char * )"S12", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S12", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Electronics enclosure sensor inactive" );
									StatusCode += BuiltStatusCode( ( char * )"S13", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S13", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Electronics enclosure sensor active" );
									StatusCode += BuiltStatusCode( ( char * )"S14", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S14", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Deposit bin out" );
									StatusCode += BuiltStatusCode( ( char * )"S15", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S15", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Deposit bin in" );
									StatusCode += BuiltStatusCode( ( char * )"S16", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S16", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Card bin out" );
									StatusCode += BuiltStatusCode( ( char * )"S17", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S17", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Card bin in" );
									StatusCode += BuiltStatusCode( ( char * )"S18", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S18", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Currency reject bin out" );
									StatusCode += BuiltStatusCode( ( char * )"S19", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S19", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Currency reject bin in" );
									StatusCode += BuiltStatusCode( ( char * )"S20", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S20", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Currency cassette in position 1 (top) out" );
									StatusCode += BuiltStatusCode( ( char * )"S21", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S21", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Currency cassette in position 1 (top) in" );
									StatusCode += BuiltStatusCode( ( char * )"S22", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S22", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Currency cassette in position 2(second) out" );
									StatusCode += BuiltStatusCode( ( char * )"S23", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S23", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Currency cassette in position 2 (second) in" );
									StatusCode += BuiltStatusCode( ( char * )"S24", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S23", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Currency cassette in position 3 (third) out" );
									StatusCode += BuiltStatusCode( ( char * )"S25", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S25", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Currency cassette in position 3 (third) in" );
									StatusCode += BuiltStatusCode( ( char * )"S26", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S26", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
							AtmReq ++;
							switch( *AtmReq )
							{
								case '0':
									trace( "Currency cassette in position 4 (bottom) out" );
									StatusCode += BuiltStatusCode( ( char * )"S27", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S27", atmbuf.StaticStatus );
									break;
								case '1':
									trace( "Currency cassette in position 4 (bottom) in" );
									StatusCode += BuiltStatusCode( ( char * )"S28", 3, StatusCode );
									BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"S28", atmbuf.StaticStatus );
									break;
								default:
									trace( "Message [ %c ]not supported" , *AtmReq );
									break;
							}
						}
						else
							trace( "Message [ %c ]not supported" , *AtmReq );
						break;
				}
				break;

			case 'Q':
				trace( "Touch screen keyboard fault" );
				StatusCode += BuiltStatusCode( ( char * )"!TSK", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!TSK", atmbuf.StaticStatus );
				AtmReq++;
				memset( temp, 0, sizeof( temp ) );
				memcpy( temp, AtmReq, 1 );
				trace( "Indicating Hardware Error" );
				AtmReq++;
				memset( temp, 0, sizeof( temp ) );
				memcpy( temp, AtmReq, 1 );
				trace( "Indicating fatal" );
				break;

			case 'R':
				trace( "Supervisor keys fault" );
				StatusCode += BuiltStatusCode( ( char * )"!SK", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!SK", atmbuf.StaticStatus );
				break;

			case 'V':
				trace( "Statement printer fault" );
				StatusCode += BuiltStatusCode( ( char * )"!SP", 3, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!SP", atmbuf.StaticStatus );

				AtmReq ++;
				switch( *AtmReq )
				{
					case '0':
						trace( "diagnostic status or supplies Status change" );
						StatusCode += BuiltStatusCode( ( char * )"SP1", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SP1", atmbuf.StaticStatus );
						break;
					case '1':
						trace( "Print/cut not successful" );
						StatusCode += BuiltStatusCode( ( char * )"SP2", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SP2", atmbuf.StaticStatus );
						break;
					case '2':
						trace( "Device not configured" );
						StatusCode += BuiltStatusCode( ( char * )"SP3", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SP3", atmbuf.StaticStatus );
						break;
					case '3':
						trace( "Statement present in transport" );
						StatusCode += BuiltStatusCode( ( char * )"SP4", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SP4", atmbuf.StaticStatus );
						break;
					case '4':
						trace( "Cardholder pressed Cancel during a print statement and wait function" );
						StatusCode += BuiltStatusCode( ( char * )"SP5", 3, StatusCode );
						BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"SP5", atmbuf.StaticStatus );
						break;
					default:
						trace( "Message [ %c ]not supported" , *AtmReq );
						break;
				}
				break;

			case 'Y':
				trace( "Coin dispenser fault" );
				StatusCode += BuiltStatusCode( ( char * )"!CD", 2, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!CD", atmbuf.StaticStatus );
				break;

			case ']':
				trace( "Document processing module fault" );
				StatusCode += BuiltStatusCode( ( char * )"!DPM", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DPM", atmbuf.StaticStatus );
				break;

			case 'a':
				trace( "Digital audio service fault" );
				StatusCode += BuiltStatusCode( ( char * )"!DAS", 4, StatusCode );
				BuiltStatusMsg( atmbuf.StatusMsg, ( char * )"!DAS", atmbuf.StaticStatus );
				break;

			default:
				trace( "Message type not supported" );
				break;
	}
	trace( "Remaining value [%s]", ++AtmReq  );
	if( MemFlag == false )
	{
		memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

		if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
			trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
		else
			trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );
	}

	//Since Wincor & Hoysong ATM's requried the Go-In-Service Command from Switch after Supervisor Exits.
	if( SOPFlag == true )
	{

		ClearStatus( atmbuf.StatusMsg, atmbuf.StaticStatus, StatusCode );
		memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &atmmem.AtmSharedBuffer, (char *)&atmbuf, sizeof( struct ATMSharedBuffer ) );

		if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
			trace( DEBUG_ERROR, "Unable to Update Device memory for Device[ %s ]", AtmId );
		else
			trace( DEBUG_TEST, "Updated the Device memory for Device[ %s ]", AtmId );

		memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
		AtmCont.MsgType = EZ_ATM_COMMAND_REQ;
		AtmCont.CommandType = GO_IN_SERVICE;
		memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );

		if( PostContMsg( AtmCont, AtmId ) < 0 )
		{
			trace( DEBUG_ERROR, "Failed in PostContMsg" );
			return -1;
		}

	}
	return 1;
}

int EzNDC :: ServeConsumerRequests( char * AtmReq, int Size , char *AtmId )
{
	char Luno[ LUNO_SIZE + 1 ], TrimOpKeyBuf[ OPKEY_SIZE + 1 ], OpKeyBuf[ OPKEY_SIZE + 1 ], OpKeyAmount[ AMOUNT_SIZE + 1 ];
	char InDirectState[ ISTATE + 1 ], DispLogicBuf[ DISP + 1 ];
	char DollarEntry[ AMOUNT_SIZE + 1 ], PinBuf[ TEMP + 1 ], GenBufB[ TEMP + 1 ], GenBufC[ TEMP + 1 ];
	char temp[ TEMP + 1 ], Date[ 11 ], Time[ 11 ];
	char CurrencyCode[ 5 ], PrinterFlag[ 3 ], TxnReqFlag[ 3 ];
	char FileName[ FILENAME_SIZE + 1 ];
	char *p, *OffSetPtr;
	char SearchId[ TEMP + 1 ], CfgVal[ TEMP + 1 ], chn[ 11 ], mcn;
	char BioMetricData[ BIO_DATA_SIZE + 1 ], BioMetricBuf[ BIOSERVER_BUF_SIZE + 1 ], TempBuf[ BIO_DATA_SIZE + 1 ];
	int Ind, Ind1;
	int NoOfVar, NoOfData, Count;
	int CheckAmount = 0, DecimalMultiplier = 0;
	EzCfgUtil cfg;
	EzDateTimeUtil dtu;

	struct EzDevMsg ConsumerReq, OldDevMsg;
	struct OARDetails OARList[ 9 ];

	char LTSData[ LTS_DATA_SIZE + 1 ];
	char FingerPrintData[ FINGER_PRINT_BUFFER_SIZE + 1 ];

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

	//Loading Txn Date and Time

	ConsumerReq.TranDate  = ConsumerReq.LocalDate = ConsumerReq.CaptureDate = dtu.getSysDate();
	ConsumerReq.TranTime  = ConsumerReq.LocalTime = ConsumerReq.CaptureTime = dtu.getSysTime();



	strcpy( ConsumerReq.AcquirerInst, atminfo.AcquirerInst );
	ConsumerReq.RespCode = 0;

	memset( Luno, 0, sizeof( Luno ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, Size );
	if( OffSetPtr != NULL )
	{
		memcpy( Luno, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "Luno : %s",Luno );
		AtmReq += ( strlen( Luno ) );
	}

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
				trace( DEBUG_ERROR, "Message[ %c ] Not Supproted", *AtmReq );
			break;
	}
	AtmReq++;

	//Coping MsgCoOrdinationNo to shared mem
	mcn = *AtmReq++ ;
	atmbuf.MsgCoOrdinationNo = mcn;
	trace( DEBUG_TEST, "Message Co-ordination Number [%c]", atmbuf.MsgCoOrdinationNo );

	AtmReq++; //0x1c position is moved
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 41 );
	if( OffSetPtr != NULL )
	{
		memset( temp, 0, sizeof( temp ) );
                memcpy( temp, AtmReq, ( OffSetPtr - AtmReq ) );
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
                        if( p[ i ] == '=' || p[ i ] == '>' )
                                break;
                        else
                                ConsumerReq.chn[ i ] = p[ i ];
                }
                AtmReq = OffSetPtr ;
	}
	AtmReq++;//0x1c moved
	AtmReq = ( char * ) memchr( AtmReq, DEVICE_FS, 107 );//track 3
	AtmReq++;//0x1c moved

	// OpKey Buffer
	memset( OpKeyBuf, 0, sizeof( OpKeyBuf ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 9 );
	if( OffSetPtr != NULL )
	{
		memcpy( OpKeyBuf, AtmReq, (OffSetPtr-AtmReq) );
		//trace( DEBUG_NORMAL, "Opkey Buffer [%s]", OpKeyBuf );
		memset( TrimOpKeyBuf, 0, sizeof( TrimOpKeyBuf ) );
		for( int i = 0, j = 0; i < strlen( OpKeyBuf ); i++ )
		{
			if( OpKeyBuf[ i ] != ' ' )
			{
				TrimOpKeyBuf[ j ] = OpKeyBuf[ i ];
				j++;
			}
		}
		//trace( DEBUG_TEST, "Trimmed Opkey Buffer [%s]", TrimOpKeyBuf );

		AtmReq = OffSetPtr ;
	}

	memset( ConsumerReq.m_chn, 0, sizeof( ConsumerReq.m_chn ) );
	ezpadssutil.maskString( ConsumerReq.chn, 6, strlen( ConsumerReq.chn ) - 4, '*', ConsumerReq.m_chn );
	trace( DEBUG_NORMAL, "MCN[%c] CHN[%s] Opkey[%s] TrimmedOpkey[%s]", atmbuf.MsgCoOrdinationNo, ConsumerReq.m_chn, OpKeyBuf, TrimOpKeyBuf );

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

	trace( DEBUG_TEST, "Indirectstate & SecurityId for Chn [ %s ] is [ %s ]", ConsumerReq.m_chn, InDirectState );

	if( !strcmp( InDirectState, "7" ) )
		atmbuf.CurrentState = SUPERVISOR;

	if( strlen( TrimOpKeyBuf ) != 0 )
	{
		memset( &temp, 0, sizeof( temp ) );
		if( LoadTxnCode( TrimOpKeyBuf, InDirectState, temp, OpKeyAmount, CurrencyCode, PrinterFlag, TxnReqFlag, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, ConsumerReq.SrcPort, atminfo.AtmTypeId ) < 0 )
		{
			if( atmbuf.CurrentState != INTERACTIVE )
			{
				trace( DEBUG_ERROR, "Unable to find TxnCode for OpKey[ %s ], AtmId[ %s ], InstitutionId[ %s ], AtmLogicalGroup[ %s ]",TrimOpKeyBuf , ConsumerReq.SrcPort, atminfo.AcquirerInst, atminfo.AtmLogicalGroup );
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
			trace( DEBUG_NORMAL, "TxnCode[ %s ] OpkeyAmount[ %s ] CurrencyCode[ %s ], PrinterFlag[ %s ], TxnReqFlag[ %s ]", temp, OpKeyAmount, CurrencyCode, PrinterFlag, TxnReqFlag);
			if( atoi( TxnReqFlag ) == NewTxn )
			{
				trace( DEBUG_TEST, "New Transaction Request" );
				atmbuf.CurrentState = TRANSACTIONREQUEST;
				memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
				atmbuf.MsgCoOrdinationNo = mcn;

				if( atminfo.TraceNum != 9999 )
				{
					//ConsumerReq.TraceNo = atminfo.TraceNum;
					ConsumerReq.PosEntryCode = atminfo.TraceNum;
					atminfo.TraceNum = atminfo.TraceNum + 1;
				}
				else
				{
					ConsumerReq.PosEntryCode = 1;
					atminfo.TraceNum = 1;
				}

				trace( DEBUG_TEST, "Transaction TraceNo[ %d ]", ConsumerReq.PosEntryCode );

				memset( &atmmgrq, 0, sizeof( struct EzAtmMgrQMsg ) );
				if( PackAtmTraceNoMsg( AtmId, atminfo.TraceNum, &atmmgrq ) < 0 )
					trace( DEBUG_ERROR, "Failed in PackAtmTraceNoMsg");

				if( PostAtmMgrMsg( atmmgrq, AtmId ) < 0 )
					trace( DEBUG_ERROR, "Failed in PostAtmMgrMsg" );

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
				trace( DEBUG_TEST, "Old Transaction.. coping the Txn Details" );
				ConsumerReq.TxnCode = atoi( temp );
				ConsumerReq.AcqCurrencyCode = atoi( CurrencyCode );
				ConsumerReq.PosEntryCode = OldDevMsg.PosEntryCode;
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
		if( strcmp( atmbuf.StaticStatus, "NONE" ) )
		{
			trace( DEBUG_TEST, "Checking for ATM Action Property");
			memset( temp, 0, sizeof( temp ) );
			if( ReadAtmActionProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, AtmId, atmbuf.StaticStatus, ConsumerReq.TxnCode, temp, &ConsumerReq.RespCode, SENDRESPONSE ) < 0 )
				trace("ATM Action Property not Found");
			else
				trace("ATM Action Property Found RespCode[%d]", ConsumerReq.RespCode );

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
			memset( DispLogicBuf, 0, sizeof( DispLogicBuf ) );
			memset( DollarEntry, 0, sizeof( DollarEntry ) );
			sprintf( DollarEntry, "%d", CheckAmount );

			if( CheckAmount > atminfo.MaxAmountDisp )
			{
				trace( DEBUG_ERROR, "Amount Requested[ %d ] > Max Amount[ %d ]", CheckAmount, atminfo.MaxAmountDisp );
				ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
				ConsumerReq.RespCode = EZLINK_RC_ExceedsMaxAmount;
				memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
				strcpy( ConsumerReq.DestPort, AtmId );
				if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
					trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
				if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
					trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
				return -1;
			}

			trace( DEBUG_TEST, "Amount Requested[ %s ] AcqCurrCode[%d], checking for Cash availability", DollarEntry, ConsumerReq.AcqCurrencyCode );

			if( GetDispLogic( DollarEntry, ConsumerReq.AcqCurrencyCode, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, ConsumerReq.SrcPort, DispLogicBuf, NDC, atminfo.AtmTypeId ) < 0 )
			{
				trace( DEBUG_ERROR, "Unable to get Dispensing Logic Requested Amount[ %d ]", CheckAmount );
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
				ConsumerReq.RespCode = CheckCashAvailability( atminfo.AtmTypeId, DollarEntry, DispLogicBuf, ConsumerReq.AcqCurrencyCode, denominfo, atminfo.MaxNoteDisp );
				if( ConsumerReq.RespCode != EZLINK_RC_Approved )
				{
					memset( ConsumerReq.DestPort, 0, sizeof( ConsumerReq.DestPort ) );
					strcpy( ConsumerReq.DestPort, AtmId );
					ConsumerReq.MsgType = EZLINK_TXN_TxnResponse;
					if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
						trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg");
					if( ConsumerReq.RespCode == EZLINK_RC_LowCash )
					{
						if( PostTxnMsg( &ConsumerReq, AtmId ) < 0 )
							trace( DEBUG_ERROR, "Failed in PostTxnMsg" );
					}
					return -1;
				}
				else
				{
					trace( DEBUG_TEST, "Amount Requested[ %s ], DispLogic[%s]", DollarEntry, DispLogicBuf );
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

	if(atmbuf.CurrentState != SUPERVISOR )
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

	trace( DEBUG_TEST,"Transaction Amount[%s]", ConsumerReq.Amount );

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

	if( strlen( ConsumerReq.PINBlock ) == 0 )
		ConsumerReq.PinVerFlg = 'N';
	trace( DEBUG_TEST, "ConsumerReq.PinVerFlg[%c]", ConsumerReq.PinVerFlg);

	memset( GenBufB, 0, sizeof( GenBufB ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 18 );
	if( OffSetPtr != NULL )
	{
		memcpy( GenBufB, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "General Purpose Buffer B [ %s ]", GenBufB );

		AtmReq += strlen( GenBufB );
		strcpy( ConsumerReq.RsvFld1, GenBufB );
	}
	AtmReq ++;//0x1c moved

	memset( GenBufC, 0, sizeof( GenBufC ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 19 );
	if( OffSetPtr != NULL )
	{
		memcpy( GenBufC, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "General Purpose Buffer C [ %s ]", GenBufC );

		AtmReq += strlen( GenBufC );
		strcpy( ConsumerReq.RsvFld2, GenBufC );
	}
	AtmReq ++;//0x1c moved

	trace( DEBUG_TEST, "< %s >", AtmReq);

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

	//Track1
	memset( temp, 0, sizeof( temp ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 20 );
	if( OffSetPtr != NULL )
	{
		memcpy( temp, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "Track1[%s]", temp );
		AtmReq += strlen( temp );
	}
	AtmReq ++;// 0x1c moved

	//LTS
	memset( LTSData, 0, sizeof( LTSData ) );
	OffSetPtr = ( char * ) memchr( AtmReq, DEVICE_FS, 21 );
	if( OffSetPtr != NULL )
	{
		memcpy( LTSData, AtmReq, ( OffSetPtr - AtmReq ) );
		trace( DEBUG_TEST, "LTS[%s]", LTSData );
		AtmReq += strlen( LTSData );
	}
	AtmReq ++;// 0x1c moved

	if( ( strlen( ConsumerReq.Track2 ) > 15 ) && ( atmbuf.CurrentState == INTERACTIVE ) )
    	{
		memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
		memcpy( &atmbuf.DevMsg, &ConsumerReq, sizeof( struct EzDevMsg ) );
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
			if( !strncmp( GenBufB, "E", 1 ) || !strncmp( GenBufB, "T", 1 ) )
			{
				trace( DEBUG_TEST, "OAR Transaction is Cancelled by Customer");
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
				trace( DEBUG_TEST, "Indirectstate for Chn [ %s ] is [ %s ]", OldDevMsg.m_chn, InDirectState );

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
						memcpy( &atmbuf.DevMsg, &OldDevMsg, sizeof( struct EzDevMsg ) );

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
			atmbuf.CurrentState = SUPERVISOR;
			if( ServeSupervisorRequest( &ConsumerReq, &atminfo, &atmbuf ) < 0 )
				trace( DEBUG_ERROR, "Failed in ServeSupervisorRequest" );
			else
				trace( DEBUG_NORMAL, "ServeSupervisorRequest updated successfully for [ %s ]", ConsumerReq.SrcPort );

			if( BuildAndPostFuncMsg( ConsumerReq ) < 0 )
			{
				trace( DEBUG_ERROR, "Failed in BuildAndPostFuncMsg" );
				return -1;
			}
		}
		else
		{
			memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
			memcpy( &atmbuf.DevMsg, &ConsumerReq, sizeof( struct EzDevMsg ) );
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

int EzNDC :: BuildAndPostWriteCmd( struct EzAtmController ContReq)
{
	char AtmBuf[ BUFFER_SIZE + 1 ], PortChannel[ CHANNEL_NAME_SIZE + 1 ], Date[ 20 ], Time[ 10 ];

	memset( AtmBuf, 0, sizeof( AtmBuf ) );
	switch( ContReq.DownloadType )
	{
		case DOWNLOAD_STATE:
			trace( "Downloading State table....." );
			sprintf( AtmBuf, "30%c001%c999%c12%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_SCREEN:
			trace( "Downloading Screens....." );
			sprintf( AtmBuf, "30%c001%c999%c11%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_MISC:
			trace( "Downloading (Configuration parameter) Miscellaneous Data....." );
			sprintf( AtmBuf, "30%c001%c999%c13%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_MISC_E:
			trace( "Downloading Enhanced (Configuration parameter) Miscellaneous Data....." );
			sprintf( AtmBuf, "30%c001%c999%c1A%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_FIT:
			trace( "Downloading FIT table....." );
			sprintf( AtmBuf, "30%c001%c999%c15%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_KEY:
			trace( "Downloading Terminal Key....." );
			//sprintf( AtmBuf, "30%c001%c999%c32%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			if( strlen( ContReq.MsgBuf ) > 30 )
				sprintf( AtmBuf, "30%c001%c999%c42%c%03X%s", 0x1c, 0x1c, 0x1c, 0x1c, strlen( ContReq.MsgBuf ), ContReq.MsgBuf );
			else
				sprintf( AtmBuf, "30%c001%c999%c32%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_CONFIG_ID:
			trace( "Downloading Configuration Id....." );
			sprintf( AtmBuf, "30%c001%c999%c16%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_DATE_TIME:
			trace( "Downloading Configuration Id....." );
			sprintf( AtmBuf, "30%c001%c999%c1C%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		case DOWNLOAD_RESERVED_SCREEN:
			trace( "Downloading Reserved Screens....." );
			sprintf( AtmBuf, "30%c001%c999%c1G%c%s", 0x1c, 0x1c, 0x1c, 0x1c, ContReq.MsgBuf );
			break;

		default:
			trace( "Invaild Download<%d>", ContReq.DownloadType);
			break;
	}

	atmbuf.CurrentState = DOWNLOAD ;

	if( PostAtmMsg( ContReq.AtmId, AtmBuf ) < 0 )
	{
		trace( "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}

int EzNDC :: BuildAndPostOperCmd( struct EzAtmController ContReq)
{
	char AtmBuf[ BUFFER_SIZE + 1 ], PortChannel[ CHANNEL_NAME_SIZE + 1 ], Date[ 20 ], Time[ 10 ];

	memset( AtmBuf, 0, sizeof( AtmBuf ) );
	sprintf( AtmBuf, "10%c001%c999%c", 0x1c, 0x1c, 0x1c  );
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

		case GET_SUPPLY_COUNTS:
			strcat( AtmBuf , "4" );
			break;

		case GET_TALLY_INFO:
			strcat( AtmBuf , "5" );
			break;

		case GET_ERRORLOG:
			strcat( AtmBuf , "6" );
			break;

		case GET_HW_CONF:
			strcat( AtmBuf , "7" );
			break;

		case GET_DATE_TIME:
			strcat( AtmBuf , "8" );
			break;

		case GET_EKC:
			strcat( AtmBuf , "=" );
			break;

		default:
			trace( "Invalid Operational Command" );
			break;
	}

	atmbuf.CurrentState = OPERATIONAL ;

	if( PostAtmMsg( ContReq.AtmId, AtmBuf ) < 0 )
	{
		trace( "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}

int EzNDC :: BuildAndPostFuncMsg( struct EzDevMsg DevMsg )
{
	char FunctionMsg[ BUFFER_SIZE + 1 ], PrinterData[ PSDATA_SIZE + 1 ], ScreenData[ PSDATA_SIZE + 1 ], temp[ TEMP + 1 ];
	char InDirectState[ ISTATE + 1 ], FileName[ FILENAME_SIZE + 1 ];
	char NextScreenNumber[ ISTATE + 1 ], NextStateNumber[ ISTATE + 1 ], DispLogicBuf[ DISP + 1 ], chn[ 11 ];
	char Temp[ TEMP+1 ], Date[ 20 ], Time[ 10 ];
	int len, ret;


	//trace( DEBUG_NORMAL, "Building function Command....[ %s ]", DevMsg.SrcPort );

	memset( &ezatmproperty, 0, sizeof( struct EzAtmProperty ) );
	if( ReadAtmProperty( atminfo.InstTerminalGroup, atminfo.AtmLogicalGroup, DevMsg.SrcPort, DevMsg.TxnCode, DevMsg.RespCode, DevMsg.AcqCurrencyCode, &ezatmproperty ) < 0 )
		trace( DEBUG_ERROR, "Unable to Reading EzAtmProperty");

	sprintf( FunctionMsg, "4%c001%c%c", DEVICE_FS, DEVICE_FS, DEVICE_FS );

	if( DevMsg.TxnCode / 10000 == 98 || DevMsg.TxnCode / 10000 == 99 )
	{
		memset( DevMsg.DestPort, 0, sizeof( DevMsg.DestPort ) );
		strcpy( DevMsg.DestPort, DevMsg.SrcPort );
	}

	if( DevMsg.RespCode == EZLINK_RC_Approved )
	{
		trace( DEBUG_NORMAL, "Good response");
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
		/*if( ( ( DevMsg.TxnCode/10000 ) == 36 ) && ( strlen( DevMsg.FromAccount ) != 0 ) && ( DevMsg.RespCode == EZLINK_RC_NoFromAccount ) )
			DevMsg.RespCode = EZLINK_RC_NoToAccount;*/

		memset( temp, 0, sizeof( temp ) );
		sprintf( temp, "%d", DevMsg.RespCode );

		memset( chn, 0, sizeof( chn ) );
		strncpy( chn, DevMsg.chn, 10 );

		memset( InDirectState, 0, sizeof( InDirectState ) );
		if( ReadIndirectState( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, chn, InDirectState ) < 0 )
			trace( DEBUG_NORMAL, "Unable to get Indirectstate for Chn [ %s ]", DevMsg.m_chn );

		memset( NextScreenNumber, 0, sizeof( NextScreenNumber ) );
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
	//sprintf( temp, "%04d", DevMsg.TraceNo );
	sprintf( temp, "%04d", DevMsg.PosEntryCode );
	trace( DEBUG_TEST, "Transaction TraceNo : %s", temp );

	strncat( FunctionMsg, temp, 4 );
	if ( DevMsg.RespCode == 0 )
	{
		switch( ( DevMsg.TxnCode/10000 ) )
		{
			case 1 :// Cash Withdrawal
				if ( DevMsg.RespCode == EZLINK_RC_Approved )
				{
					if( atmbuf.PrinterFlag == '1' )
					{
						if( ezatmproperty.CardReaderModel == DIP_CARDREADER )
						{
							strcat( FunctionMsg, "8" );
							strcat( FunctionMsg, NextScreenNumber );
						}
						else
						{
							strcat( FunctionMsg, "B" );
							strcat( FunctionMsg, NextScreenNumber );
						}
					}
					else
					{
						strcat( FunctionMsg, "8" );
						strcat( FunctionMsg, NextScreenNumber );
					}
				}
				else if ( DevMsg.RespCode == EZLINK_RC_PartialDispense || DevMsg.RespCode == EZLINK_RC_DispencedFully )
				{
					//Check Device Property
					strcat( FunctionMsg, "8" );
					strcat( FunctionMsg, NextScreenNumber );
				}
				else
					strcat( FunctionMsg, "5" );
				break;

			case 20://Deposit
				strcat( FunctionMsg, "7" );
				break;

			default:
				strcat( FunctionMsg, "5" );
				break;
		}
	}
	else
	{
		strcat( FunctionMsg, "3" );
	}

	//Building ScreenData

	if( ( DevMsg.RespCode == 0 ) && ( DevMsg.TxnCode/10000 ) != 36 )
	{
		trace( DEBUG_TEST, "Composing Screen template");

		if( atmbuf.CurrentState != INTERACTIVE )
		{
			memset( ScreenData, 0, sizeof( ScreenData ) );
			if( ComposeScreenTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, &DevMsg, ScreenData ) < 0 )
			{
				trace( DEBUG_ERROR, "Unable to Compose the screen data" );
				strcat( FunctionMsg, NextScreenNumber );
			}
			else
			{
				strcat( FunctionMsg, NextScreenNumber );

				memset( Temp, 0, sizeof( Temp ) );
				if( GetEmptyScreen( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, Temp, atminfo.AtmTypeId ) < 0 )
					trace( DEBUG_ERROR, "Unable to Get Empty Screen" );
				else
					strcat( FunctionMsg, Temp );

				strcat( FunctionMsg, ScreenData );
			}
			//trace( DEBUG_DUMP, "ScreenData[ %s ]", ScreenData );
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
					//memset( DevMsg.DestPort, 0, sizeof( DevMsg.DestPort ) );
					//strcpy( DevMsg.DestPort, DevMsg.SrcPort );
					memset( PrinterData, 0, sizeof( PrinterData ) );
					if( BuildSupPrinterData( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, &DevMsg, atminfo.AtmTypeId, PrinterData ) < 0 )
					{
						strcat( FunctionMsg, "0" );//Do not Print
						trace( DEBUG_ERROR, "Unable to Compose the printer data" );
					}
					else
					{
						for( int i = 0; i < strlen( PrinterData ); i++ )
						{
							if( islower( PrinterData[ i ] ) )
								PrinterData[ i ] = toupper( PrinterData[ i ] );
						}
						//Check DeviceProperty
						strcat( FunctionMsg, "2" );//Print in receipt Printer
						strcat( FunctionMsg, PrinterData );
					}
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
							for( int i = 0; i < strlen( PrinterData ); i++ )
							{
								if( islower( PrinterData[ i ] ) )
									PrinterData[ i ] = toupper( PrinterData[ i ] );
							}
							strcat( FunctionMsg, "1" );//Print in journal Printer
							strcat( FunctionMsg, PrinterData );
							strcat( FunctionMsg, "\x1d");
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
							for( int i = 0; i < strlen( PrinterData ); i++ )
							{
								if( islower( PrinterData[ i ] ) )
									PrinterData[ i ] = toupper( PrinterData[ i ] );
							}
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
							for( int i = 0; i < strlen( PrinterData ); i++ )
							{
								if( islower( PrinterData[ i ] ) )
									PrinterData[ i ] = toupper( PrinterData[ i ] );
							}
							strcat( FunctionMsg, "8" );//Print in statement Printer
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
							for( int i = 0; i < strlen( PrinterData ); i++ )
							{
								if( islower( PrinterData[ i ] ) )
									PrinterData[ i ] = toupper( PrinterData[ i ] );
							}
							strcat( FunctionMsg, "2" );//Print in consumer Printer
							strcat( FunctionMsg, PrinterData );
						}
					}

					if( DevMsg.TxnCode/10000 == 20 )
					{
						trace( DEBUG_TEST, "Enabling Envelope Printer for TxnCode[%06d]", DevMsg.TxnCode );
						memset( PrinterData, 0, sizeof( PrinterData ) );
						if( ComposePrinterTemplate( atminfo.AtmTypeId, atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, ENVELOPE_PRINTER, &DevMsg, PrinterData ) < 0 )
						{
							trace( DEBUG_ERROR, "Unable to Compose the Envelope printer data" );
						}
						else
						{
							for( int i = 0; i < strlen( PrinterData ); i++ )
							{
								if( islower( PrinterData[ i ] ) )
									PrinterData[ i ] = toupper( PrinterData[ i ] );
							}
							//strcat( FunctionMsg, "6" );//Print in Envelope Printer
							//strcat( FunctionMsg, PrinterData );
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
			//Check DeviceProperty
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
					for( int i = 0; i < strlen( PrinterData ); i++ )
					{
						if( islower( PrinterData[ i ] ) )
							PrinterData[ i ] = toupper( PrinterData[ i ] );
					}
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
				for( int i = 0; i < strlen( PrinterData ); i++ )
				{
					if( islower( PrinterData[ i ] ) )
						PrinterData[ i ] = toupper( PrinterData[ i ] );
				}
				strcat( FunctionMsg, "1" );//Print in journal Printer
				strcat( FunctionMsg, PrinterData );
				strcat( FunctionMsg, "\x1d");
			}
		}

		if( ( ( DevMsg.TxnCode/10000 ) == 98 ) || ( ( DevMsg.TxnCode/10000 ) == 99 ) )
		{
			memset( PrinterData, 0, sizeof( PrinterData ) );
			if( BuildSupPrinterData( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.RespCode, &DevMsg, atminfo.AtmTypeId, PrinterData ) < 0 )
			{
				strcat( FunctionMsg, "0" );//Do not Print
				trace( DEBUG_ERROR, "Unable to Compose the printer data" );
			}
			else
			{
				for( int i = 0; i < strlen( PrinterData ); i++ )
				{
					if( islower( PrinterData[ i ] ) )
						PrinterData[ i ] = toupper( PrinterData[ i ] );
				}
				//Check DeviceProperty
				strcat( FunctionMsg, "2" );//Print in receipt Printer
				strcat( FunctionMsg, PrinterData );
			}
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
				for( int i = 0; i < strlen( PrinterData ); i++ )
				{
					if( islower( PrinterData[ i ] ) )
						PrinterData[ i ] = toupper( PrinterData[ i ] );
				}
				strcat( FunctionMsg, "2" );//Print in receipt Printer
				trace( DEBUG_TEST, "Printer Data[ %s ]", PrinterData);
				strcat( FunctionMsg, PrinterData );
			}
		}
	}

	if( ( ( DevMsg.TxnCode/10000 ) == 98 ) || ( ( DevMsg.TxnCode/10000 ) == 99 ) )
		atmbuf.CurrentState = SUPERVISOR ;
	else
	{
		trace( "setting state as transaction response..." );
		atmbuf.CurrentState = TRANSACTIONRESPONSE ;
	}

	memset( &atmbuf.DevMsg, 0, sizeof( atmbuf.DevMsg ) );
	memcpy( &atmbuf.DevMsg, &DevMsg, sizeof( struct EzDevMsg ) );

	if( PostAtmMsg( DevMsg.DestPort, FunctionMsg ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed in PostAtmMsg" );
		return -1;
	}
	return 1;
}

int EzNDC :: BuildAndPostOARRequest( struct EzDevMsg DevMsg )
{
	char OARMsg[ BUFFER_SIZE + 1 ],  ScreenData[ PSDATA_SIZE + 1 ], temp[ TEMP + 1 ];
	char AtmId[ ATM_ID_SIZE + 1 ], Date[ 20 ], Time[ 10 ], KeyDetails[ 12 ];
	char FileName[ FILENAME_SIZE + 1 ], FileName1[ FILENAME_SIZE + 1 ], TimeOut[ 4 ], chn[ 11 ], InDirectState[ ISTATE + 1 ];
	int IndirectState = 0,  NoOfVar, NoOfData, TotalPage, CurrentPage;

	struct OARDetails OARList[ 9 ];
	int ret, Count;

	trace( DEBUG_NORMAL, "Building OAR Request..."  );
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
	//for( int i = 0; i < 8; i++ )
		//trace( DEBUG_TEST, "Key[ %c ]Template[ %d ]Status[ %d ]Position[ %d ]", OARList[i].Key, OARList[i].Template, OARList[i].Status, OARList[i].Position );

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

	//for( int i = 0; i < 8; i++ )
	//	trace( DEBUG_TEST, "After-->Key[ %c ]Template[ %d ]Status[ %d ]Position[ %d ]", OARList[i].Key, OARList[i].Template, OARList[i].Status, OARList[i].Position );

	memset( KeyDetails, 0, sizeof( KeyDetails ) );
	if( PackKeyDetails( atminfo.AcquirerInst, atminfo.AtmLogicalGroup, DevMsg.DestPort, InDirectState, DevMsg.TxnCode, KeyDetails, OARList, atminfo.AtmTypeId ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to pack Key Details");
		return -1;
	}
	else
		strcat( OARMsg, KeyDetails );
	trace( DEBUG_NORMAL, "with Key Details[ %s ]", OARMsg);

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

int EzNDC :: PostAtmMsg( const char *DestPort, char *AtmMsg )
{
	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	memset( &atmmem.AtmInfoBuffer, 0, sizeof( atmmem.AtmInfoBuffer ) );
	memcpy( &atmmem.AtmInfoBuffer, &atminfo, sizeof( struct AtmTableInfo ) );


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

	trace( DEBUG_NORMAL, "Posting Message to Port Channel[ %s ]", DestPort );

	if ( WritePortChannel( DestPort, AtmMsg, strlen( AtmMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to post the Message into Port Channel[ %s ]", DestPort );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Posted the Message to Port Channel[ %s ]", DestPort );

	return 1;
}

int EzNDC :: PostTxnMsg( struct EzDevMsg *DevMsg, char *AtmId )
{
	struct EzTxnMsg eztxnmsg;

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
	strcpy( DevMsg->SrcChannel, NDCDRIVERCHANNEL );
	strcpy( DevMsg->OrgChannel, NDCDRIVERCHANNEL );

	memset( &eztxnmsg, 0, sizeof( struct EzTxnMsg ) );
	TransformOUTboundMsg( &eztxnmsg, DevMsg );

	trace( DEBUG_TXN, "Writing MsgType[ %d ] TxnCode[ %d ] RespCode[ %d ] TraceNo[ %d ] Chn[ %s ] Amount[ %s ] DispAmount[ %s ] to Channel[%s]", eztxnmsg.MsgType, eztxnmsg.TxnCode, eztxnmsg.RespCode, eztxnmsg.TraceNo, eztxnmsg.m_chn, eztxnmsg.Amount, eztxnmsg.DispAmount, TRANSACTIONCHANNEL );

	if( WriteChannel( TRANSACTIONCHANNEL, (char*)&eztxnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", TRANSACTIONCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message written into the %s channel", TRANSACTIONCHANNEL );

	return 1;
}

int EzNDC :: PostAtmMgrMsg( struct EzAtmMgrQMsg atmmgrq, char *AtmId )
{
	if( WriteChannel( ATMMGRCHANNEL, (char*)&atmmgrq, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
	{
		trace( "Unable to write into the channel %s", ATMMGRCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message Posted into the %s channel", ATMMGRCHANNEL );
	return 1;
}

int EzNDC :: PostAlertMgrMsg( struct EzAlertMgrMsg alertmgrmsg )
{
	if( WriteChannel( EZALERTMGRCHANNEL, (char*)&alertmgrmsg, sizeof( struct EzAlertMgrMsg ) ) < 0 )
	{
		trace( "Unable to write into the channel %s", EZALERTMGRCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST,"Message Posted into the %s channel", EZALERTMGRCHANNEL );
	return 1;
}

int EzNDC :: PostContMsg( struct EzAtmController ContReq, char *AtmId )
{
	trace( DEBUG_TEST, "Routing Message to EzATMController");
	if( WriteChannel( CONTROLLERCHANNEL, (char*)&ContReq, sizeof( struct EzAtmController ) ) < 0 )
	{
		trace( "Unable to write into the channel %s", CONTROLLERCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message Posted into the %s channel", CONTROLLERCHANNEL );
	return 1;
}

int EzNDC :: PostBioMetricMsg( const char *DestPort, const char *AtmId, char *BioMetircMsg )
{
	memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
	memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
		trace( "Unable to Update Device memory for Device<%s>", AtmId );
	else
		trace( "Updated the Device memory for Device<%s>", AtmId );

	if ( WritePortChannel( DestPort, BioMetircMsg, strlen( BioMetircMsg ) ) < 0 )
	{
		trace( "Failed to post the Message into Port Channel<%s>", DestPort );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Posted the Message to Port Channel<%s>", DestPort );

	return 1;
}


int main( int argc, char **argv )
{
	EzNDC ezndcobj;
	ezndcobj.InitEzNDCDriver( argv[ 0 ] );
	ezndcobj.ServiceRequest( );
	return 1;
}
