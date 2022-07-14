#include <ezlink/eztxnmgr.h>

void EzTxnMgr :: initEzTxnMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztxnmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzTxnMgr Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	SetDebug();

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzTxnMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating EzTxnMgr Channel" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( initEventUtil( this, GetSourceChannelName() ) < 0 )
	{
		trace( "Error in Initializing EventUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezsecurityutil.InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzNetworkUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( eznetworkutil.initNetworkUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzNetworkUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( ezdevicetypemaputil.initEzDeviceTypeMapUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzDeviceTypeMapUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezbranchprofileutil.initBranchProfile( this, false ) < 0 )
	{
		trace( "Error in Initializing EzBranchProfileUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnfldval.initEzTxnFldVal( this, &ezbranchprofileutil ) < 0 )
	{
		trace( "Error in Initializing EzTxnFldVal" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnsequtil.initTxnSeqUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTxnSeqUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezmsgtypepropertyutil.initEzMsgTypePropertyUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzMsgTypePropertyUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezinstprofileutil.initInstProfile( this, false ) < 0 )
	{
		trace( "Error in Initializing EzInstProfileUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezinstselectutil.initEzInstSelectUtil( this, &eztxnfldval, false ) < 0 )
	{
		trace( "Error in Initializing EzInstSelectUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezbinselectutil.initEzBINSelectUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzBINSelectUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezbinprofileutil.initBINProfile( this, false ) < 0 )
	{
		trace( "Error in Initializing EzBINProfileUtil...." );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezbinrangeutil.initBINRange( this, false ) < 0 )
	{
		trace( "Error in Initializing EzBINRangeUtil...." );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eznetworkselectutil.initEzNetworkSelectUtil( this, &eznetworkutil, &eztxnfldval, false ) < 0 )
	{
		trace( "Error in Initializing EzNetworkSelectUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnrouteinfoutil.initEzTxnRouteInfoUtil( this, &eznetworkutil, &ezbranchprofileutil, true ) < 0 )
	{
		trace( "Error in Initializing EzTxnRouteInfoUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnrouteselectutil.initEzTxnRouteSelectUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzTxnRouteSelectUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezmsgtranslateutil.initEzMsgTranslateUtil( this,  &eznetworkutil, &eztxnsequtil, false ) < 0 )
	{
		trace( "Error in Initializing EzMsgTranslateUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezeventpropertyutil.initEzEventPropertyUtil( this, true ) < 0 )
	{
		trace( "Error in Initializing EzEventPropertyUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezchannelpropertyutil.initEzChannelPropertyUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzChannelPropertyUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnrefselectutil.initEzTxnRefSelectUtil( this, true ) < 0 )
	{
		trace( "Error in Initializing EzTxnRefSelectUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezbusdayutil.initBusDayUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzBusDayUtil...." );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnmgrutil.initTxnMgrUtil() < 0 )
	{
		trace( "Error in Initializing EzTxnMgrUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezinboundmsgpropertyutil.initInBoundMsgPropertyUtil( this, true ) < 0 )
	{
		trace( "Error in Initializing EzInBoundMsgPropertyUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnmsgorderutil.initTxnMsgOrderUtil( this, false ) < 0 )
	{
		trace( "Error in Initializing EzTxnMsgOrderUtil" );
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnlogutil.initTxnLogUtil( this, this ) < 0 )
	{
		trace( "Error in Initializing EzTxnLogUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( eztxnmoninfoutil.initTxnMonInfoUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTxnMonInfoUtil");
		trace( "^^^^^^^^^^^EzTxnMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

int EzTxnMgr :: sendToChannel( const char *ChannelName, struct EzTxnMsg *txnmsg )
{
	trace( DEBUG_NORMAL, "<SEND>Channel(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", ChannelName, txnmsg->DeviceType, txnmsg->OrgChannel, txnmsg->SrcChannel, txnmsg->OrgPort, txnmsg->SrcPort, txnmsg->DestPort, txnmsg->MsgType, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->TxnCode, txnmsg->Amount, txnmsg->TerminalId, txnmsg->TraceNo, txnmsg->TranDate, txnmsg->TranTime, txnmsg->LocalDate, txnmsg->LocalTime, txnmsg->RespCode, txnmsg->ReasonCode, txnmsg->RefNum, txnmsg->NetworkId );
	eztxnmgrutil.dumpTxnMsg( txnmsg );
	if( WriteChannel( ChannelName, ( char * ) txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Writing Message to Channel[%s]", ChannelName );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "Written Successfully Message to Channel[%s]", ChannelName );
		return 1;
	}
}

int EzTxnMgr :: receiveFromChannel( struct EzTxnMsg *txnmsg )
{
	int MsgSize;
	if( ReadMessage( ( char * ) txnmsg, &MsgSize ) < 0 )
	{
		trace( "Error in Reading Message From EzTxnMgr Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	else
	{
		trace( DEBUG_NORMAL, "<RECV>Channel(%s)DeviceType(%s)OrgChannel(%s)SrcChannel(%s)OrgPort(%s)SrcPort(%s)DestPort(%s)MType(%d)CHN(%s)Account(%s)TxnCode(%d)Amount(%s)TerminalId(%s)TraceNo(%d)TranDate(%d)TranTime(%d)LocalDate(%d)LocalTime(%d)RespCode(%d)ReasonCode(%d)RefNum(%s)NetworkId(%s)", GetLastSenderChannelName(), txnmsg->DeviceType, txnmsg->OrgChannel, txnmsg->SrcChannel, txnmsg->OrgPort, txnmsg->SrcPort, txnmsg->DestPort, txnmsg->MsgType, txnmsg->m_chn, txnmsg->FromAccount, txnmsg->TxnCode, txnmsg->Amount, txnmsg->TerminalId, txnmsg->TraceNo, txnmsg->TranDate, txnmsg->TranTime, txnmsg->LocalDate, txnmsg->LocalTime, txnmsg->RespCode, txnmsg->ReasonCode, txnmsg->RefNum, txnmsg->NetworkId );
		eztxnmgrutil.dumpTxnMsg( txnmsg );
		return 1;
	}
}

void EzTxnMgr :: populateNewRequest( struct EzTxnMsg *txnmsg )
{
	char ExpDateStr[ 10 ];

	if( strlen( txnmsg->Track2 ) )
	{
		for( int i = 0; i < strlen( txnmsg->Track2 ); i++ )
		{
			if( !isdigit( txnmsg->Track2[ i ] ) )
			{
				memset( ExpDateStr, 0, sizeof( ExpDateStr ) );
				strncpy( ExpDateStr, txnmsg->Track2 + i + 1, 4 );
				break;
			}
		}
		txnmsg->ExpiryDate = atoi( ExpDateStr );
	}

	if( !txnmsg->TranDate )
		txnmsg->TranDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->TranTime )
		txnmsg->TranTime = ezdatetimeutil.getSysTime();

	if( !txnmsg->LocalDate )
		txnmsg->LocalDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->LocalTime )
		txnmsg->LocalTime = ezdatetimeutil.getSysTime();

	if( !txnmsg->CaptureDate )
		txnmsg->CaptureDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->CaptureTime )
		txnmsg->CaptureTime = ezdatetimeutil.getSysTime();

	if( !txnmsg->SettlementDate )
		txnmsg->SettlementDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->BusinessDate )
		txnmsg->BusinessDate = ezdatetimeutil.getSysDate();

	if( !txnmsg->TraceNo )
		txnmsg->TraceNo = eztxnsequtil.genTraceNo();

	if( !strlen( txnmsg->RefNum ) )
	{
		memset( txnmsg->RefNum, 0, sizeof( txnmsg->RefNum ) );
		eztxnsequtil.genNumericRefNum( txnmsg->RefNum );
	}

	if( !strcmp( txnmsg->DeviceType, "ATM" ) )
	{
		memset( txnmsg->AcceptorId, 0, sizeof( txnmsg->AcceptorId ) );
		if( strlen( txnmsg->SrcPort ) >= 15 )
			strncpy( txnmsg->AcceptorId, txnmsg->SrcPort, 15 );
		else
			sprintf( txnmsg->AcceptorId, "%-15s", txnmsg->SrcPort );
	}
}

bool EzTxnMgr :: isNewTxnRequest( int MsgType )
{
	if( MsgType == EZLINK_TXN_TxnRequest || MsgType == EZLINK_TXN_InfRequest )
		return true;
	else
		return false;
}

bool EzTxnMgr :: isTxnResponse( int MsgType )
{
	if( MsgType == EZLINK_TXN_TxnResponse )
		return true;
	else
		return false;
}

int EzTxnMgr :: dropTxn( struct EzTxnMsg *txnmsg )
{
	char EventId[ EVENT_KEY_SIZE + 1 ];
	short RefSeqNo = 0;

	if( !txnmsg->RespCode )
		txnmsg->RespCode = EZLINK_RC_UnableToProcess;
	memset( txnmsg->DestPort, 0, sizeof( txnmsg->DestPort ) );
	strcpy( txnmsg->DestPort, txnmsg->OrgPort );

	memset( EventId, 0, sizeof( EventId ) );
	eztxnrefselectutil.getTxnRefNum( txnmsg, EventId );

	memset( txnmsg->SrcChannel, 0, sizeof( txnmsg->SrcChannel ) );
	strcpy( txnmsg->SrcChannel, GetSourceChannelName() );

	sendToChannel( txnmsg->OrgChannel, txnmsg );

	RefSeqNo = 1;
	if( eztxnlogutil.insertTxnLog( txnmsg, EventId, GetSourceChannelName(), txnmsg->OrgChannel, RefSeqNo ) < 0 )
		trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
	return 1;

}

void EzTxnMgr :: ServiceRequest()
{
	struct EzTxnMsg txnmsg, localtxnmsg;
	struct EzInstRouteType ezinstroutetype;
	int Priority, NRoutes, EventTimeOut, MsgSize;
	char InstId[ 13 ], PrimaryInstId[ 13 ], NetworkId[ 17 ], RouteSelectList[ 256 ], RouteSelectId[ 17 ], ChannelName[ 33 ];
	char EventId[ EVENT_KEY_SIZE + 1 ], MsgTranslateId[ 17 ], TranPinBlock[ 17 ];
	short RefSeqNo;

	while( 1 )
	{
		trace( "EzTxnMgr Waiting For Request....");

		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		if( receiveFromChannel( &txnmsg ) < 0 )
		{
			trace( "Error in Reading Message From EzTxnMgr Channel SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			sleep( 1 );
			continue;
		}

		if( ezmsgtypepropertyutil.readEzMsgTypeProperty( txnmsg.MsgType ) < 0 )
		{
			trace( "Error in reading MsgType[%d] in ezmsgtypeproperty table...Dropping Message", txnmsg.MsgType );
			continue;
		}

		if( ezchannelpropertyutil.readChannelProperty( GetLastSenderChannelName() ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading ChannelName[%s] in EzChannelProperty Table...assigning device flag as Network...", GetLastSenderChannelName() );
			txnmsg.DeviceFlag = EZLINK_MSG_FROM_NETWORK;
		}
		else
		{
			if( ezchannelpropertyutil.isDeviceChannel() )
				txnmsg.DeviceFlag = EZLINK_MSG_FROM_DEVICE;
			else if( ezchannelpropertyutil.isNetworkChannel() )
				txnmsg.DeviceFlag = EZLINK_MSG_FROM_NETWORK;
			else
				txnmsg.DeviceFlag = EZLINK_MSG_FROM_APPLICATION;
		}

		if( ezmsgtypepropertyutil.isTxnMsg() )
		{
			if( !strlen( txnmsg.DeviceType ) || !strcmp( txnmsg.DeviceType, "*" ) )
			{
				memset( txnmsg.DeviceType, 0, sizeof( txnmsg.DeviceType ) );
				if( ezdevicetypemaputil.readDeviceType( txnmsg.MerchantType, txnmsg.DeviceType ) < 0 )
					strcpy( txnmsg.DeviceType, "*" );
			}

			if( ezinboundmsgpropertyutil.readInBoundMsgProperty( txnmsg.MsgType, ezchannelpropertyutil.getChannelType(), GetLastSenderChannelName() ) < 0 )
			{
				trace( "Error in reading MsgType[%04d] ChannelType[%s] ChannelName[%s] from EzInBoundMsgProperty...Dropping Message", txnmsg.MsgType, ezchannelpropertyutil.getChannelType(), GetLastSenderChannelName() );
				continue;
			}

			if( ezinboundmsgpropertyutil.isLeaveMsg() )
			{
				if( ezmsgtypepropertyutil.isTxnMsg() && ezeventpropertyutil.isEventLookUpReq( GetLastSenderChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode ) )
				{
					trace( DEBUG_TEST, "EventLookUp Configured for ChannelName[%s] MsgType[%d] TxnCode[%d] RespCode[%d]", GetLastSenderChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode );

					memset( EventId, 0, sizeof( EventId ) );
					txnmsg.MsgType = txnmsg.MsgType - 10;
					eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );

					trace( DEBUG_TEST, "Destroying EventId[%s]....", EventId );

					txnmsg.MsgType = txnmsg.MsgType + 10;

					memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
					if( destroyEvent( EventId, ( char * )&localtxnmsg, &MsgSize ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Destroying EventId[%s]...Might be Late Response", EventId );
						trace( DEBUG_ERROR, "Dropping Message....");
						continue;
					}
					trace( DEBUG_NORMAL, "Destroyed EventId[%s] Successfully", EventId );

					eztxnmgrutil.populateTxnMsg( &txnmsg, &localtxnmsg );

					trace( DEBUG_TEST, "Populated Transaction Message Successfully....");

				}

				if( ezinboundmsgpropertyutil.isInsertTxnLog() )
				{
					RefSeqNo = 1;
					if( eztxnlogutil.insertTxnLog( &txnmsg, EventId, GetLastSenderChannelName(), GetSourceChannelName(), RefSeqNo ) < 0 )
						trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
				}
				continue;
			}

			eztxnmoninfoutil.updateTxnMonInfo( &txnmsg );

			if( ezinboundmsgpropertyutil.isNewRequest() && strcmp( GetLastSenderChannelName(), "EzEventMgr" ) )
			{
				trace( DEBUG_NORMAL, "Got New Request[%d].....",  txnmsg.MsgType );
				if( !strlen( txnmsg.DeviceType ) )
				{
					memset( txnmsg.DeviceType, 0, sizeof( txnmsg.DeviceType ) );
					strcpy( txnmsg.DeviceType, ezchannelpropertyutil.getDeviceType() );
				}
				populateNewRequest( &txnmsg );
			}
			memset( EventId, 0, sizeof( EventId ) );
			eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );

			if( txnmsg.DeviceFlag == EZLINK_MSG_FROM_DEVICE || txnmsg.DeviceFlag == EZLINK_MSG_FROM_NETWORK )
			{
				memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
				strcpy( txnmsg.DestPort, "*" );
			}
			else
			{
				memset( txnmsg.SrcPort, 0, sizeof( txnmsg.SrcPort ) );
				strcpy( txnmsg.SrcPort, "*" );
				memset( txnmsg.DestPort, 0, sizeof( txnmsg.DestPort ) );
				strcpy( txnmsg.DestPort, "*" );
			}

			if( ezinboundmsgpropertyutil.isInsertTxnLog() )
			{
				RefSeqNo = 1;
				if( eztxnlogutil.insertTxnLog( &txnmsg, EventId, GetLastSenderChannelName(), GetSourceChannelName(), RefSeqNo ) < 0 )
					trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
			}
		}

		if( ezmsgtypepropertyutil.isTxnMsg() && ezinboundmsgpropertyutil.isNewRequest() && strcmp( GetLastSenderChannelName(), "EzEventMgr" ) )
		{
			if( !strlen( txnmsg.SrcPort ) )
			{
				trace( DEBUG_ERROR, "Source Port is Null for New Request...Dropping Message" );
				txnmsg.MsgType += 10;
				txnmsg.ReasonCode = EZLINK_Reason_NoOrgChannel_Err;
				memset( txnmsg.OrgChannel, 0, sizeof( txnmsg.OrgChannel ) );
				strcpy( txnmsg.OrgChannel, txnmsg.SrcChannel );
				if( !ezmsgtypepropertyutil.isResponse() )
					dropTxn( &txnmsg );
				continue;
			}

			if( !strlen( txnmsg.AcquirerInst ) )
			{
				trace( DEBUG_ERROR, "Acquirer Institution is Null for New Request...Dropping Message" );
				txnmsg.MsgType += 10;
				txnmsg.ReasonCode = EZLINK_Reason_NoAcqInst_Err;
				memset( txnmsg.OrgChannel, 0, sizeof( txnmsg.OrgChannel ) );
				strcpy( txnmsg.OrgChannel, txnmsg.SrcChannel );
				if( !ezmsgtypepropertyutil.isResponse() )
					dropTxn( &txnmsg );
				continue;
			}

			memset( txnmsg.OrgChannel, 0, sizeof( txnmsg.OrgChannel ) );
			memset( txnmsg.OrgPort, 0, sizeof( txnmsg.OrgPort ) );
			strcpy( txnmsg.OrgChannel, GetLastSenderChannelName() );
			strcpy( txnmsg.OrgPort, txnmsg.SrcPort );

			if( ezchannelpropertyutil.isDeviceChannel() )
			{
				txnmsg.DeviceFlag = EZLINK_MSG_FROM_DEVICE;
				trace( DEBUG_NORMAL, "Message from Device....." );
			}
			else
			{
				txnmsg.DeviceFlag = EZLINK_MSG_FROM_NETWORK;
				trace( DEBUG_NORMAL, "Message from Network....." );

				memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
				if( eznetworkutil.getNetworkIdFromPort( txnmsg.OrgPort, txnmsg.NetworkId ) < 0 )
				{
					if( !ezmsgtypepropertyutil.isResponse() )
					{
						trace( DEBUG_ERROR, "Error in Reading NetworkId.... for NetworkPort[%s]", txnmsg.OrgPort );
						txnmsg.ReasonCode = EZLINK_Reason_NetworkPort_Err;
						txnmsg.MsgType += 10;
						if( !ezmsgtypepropertyutil.isResponse() )
							dropTxn( &txnmsg );
						continue;
					}
				}
			}
		}

		if( ezmsgtypepropertyutil.isTxnMsg() && ezeventpropertyutil.isEventLookUpReq( GetLastSenderChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode ) )
		{
			trace( DEBUG_TEST, "EventLookUp Configured for ChannelName[%s] MsgType[%d] TxnCode[%d] RespCode[%d]", GetLastSenderChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode );

			memset( EventId, 0, sizeof( EventId ) );
			txnmsg.MsgType = txnmsg.MsgType - 10;
			eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );

			trace( DEBUG_TEST, "Destroying EventId[%s].....>", EventId );

			txnmsg.MsgType = txnmsg.MsgType + 10;

			memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
			if( destroyEvent( EventId, ( char * )&localtxnmsg, &MsgSize ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Destroying EventId[%s]...Might be Late Response", EventId );
				trace( DEBUG_ERROR, "Dropping Message....");
				continue;
			}

			trace( DEBUG_NORMAL, "Destroyed EventId[%s] Successfully", EventId );

			eztxnmgrutil.populateTxnMsg( &txnmsg, &localtxnmsg );

			trace( DEBUG_TEST, "Populated Transaction Message Successfully....");
		}
		else if( ezmsgtypepropertyutil.isTxnMsg() && ezeventpropertyutil.isEventSearchReq( GetLastSenderChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode ) )
		{
			trace( DEBUG_TEST, "EventSearch Configured for ChannelName[%s] MsgType[%d] TxnCode[%d] RespCode[%d]", GetLastSenderChannelName(), txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode );

			memset( EventId, 0, sizeof( EventId ) );
			txnmsg.MsgType = txnmsg.MsgType - 10;
			eztxnrefselectutil.getTxnRefNum( &txnmsg, EventId );

			trace( DEBUG_TEST, "Searching EventId[%s]....", EventId );

			txnmsg.MsgType = txnmsg.MsgType + 10;

			memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
			if( searchEvent( EventId, ( char * )&localtxnmsg, &MsgSize ) < 0 )
				trace( DEBUG_ERROR, "Error in Searching EventId[%s]...", EventId );

			trace( DEBUG_NORMAL, "Searched EventId[%s] Successfully", EventId );

			eztxnmgrutil.populateTxnMsg( &txnmsg, &localtxnmsg );

			trace( DEBUG_TEST, "Populated Transaction Message Successfully....");
		}

		if( ezmsgtypepropertyutil.isTxnMsg() )
		{
			memset( InstId, 0, sizeof( InstId ) );
			if( ezinstselectutil.getInst( &txnmsg, EZIMF_ISSINST, InstId ) < 0 )
			{
				trace( "Test institution select" );
				if( ezbinselectutil.readBINSelect( txnmsg.chn, 1 ) < 0 )
				{
					memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
					strcpy( txnmsg.IssuerInst, "*" );
				}
				else
				{
					memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
					strcpy( txnmsg.IssuerInst, ezbinselectutil.getInstId() );
					if( ezbinselectutil.isBINRangeReq() )
					{
						if( ezbinrangeutil.readBINRange( ezbinselectutil.getInstId(), ezbinselectutil.getBIN(), txnmsg.chn ) < 0 )
						{
							memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
							strcpy( txnmsg.IssuerInst, "*" );
						}
					}
				}
			}
			else
			{
				memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
				strcpy( txnmsg.IssuerInst, InstId );
			}
			trace( DEBUG_NORMAL, "Searched Issuer Institution as [%s]", txnmsg.IssuerInst );

			if( ezmsgtypepropertyutil.isNewRequest() )
			{
				if( !strcmp( txnmsg.IssuerInst, "*" ) && !ezmsgtypepropertyutil.isResponse() )
				{
					trace( "Error in Searching IssuerInst....Dropping the Transaction...." );
					txnmsg.ReasonCode = EZLINK_Reason_IssuerNotFound_Err;
					txnmsg.MsgType += 10;
					txnmsg.RespCode = EZLINK_RC_InvalidIssuer;
					if( !ezmsgtypepropertyutil.isResponse() )
						dropTxn( &txnmsg );
					continue;
				}
			}

			memset( InstId, 0, sizeof( InstId ) );
			if( ezinstselectutil.getInst( &txnmsg, EZIMF_TXFINST, InstId ) < 0 )
			{
				memset( txnmsg.TxfInst, 0, sizeof( txnmsg.TxfInst ) );
				strcpy( txnmsg.TxfInst, "*" );
			}
			else
			{
				memset( txnmsg.TxfInst, 0, sizeof( txnmsg.TxfInst ) );
				strcpy( txnmsg.TxfInst, InstId );
			}
			trace( DEBUG_NORMAL, "Searched Transfer Institution as [%s]", txnmsg.TxfInst );

			memset( InstId, 0, sizeof( InstId ) );
			if( ezinstselectutil.getInst( &txnmsg, EZIMF_SETTINST, InstId ) < 0 )
			{
				memset( txnmsg.SettInst, 0, sizeof( txnmsg.SettInst ) );
				strcpy( txnmsg.SettInst, txnmsg.IssuerInst );
			}
			else
			{
				memset( txnmsg.SettInst, 0, sizeof( txnmsg.SettInst ) );
				strcpy( txnmsg.SettInst, InstId );
			}
			trace( DEBUG_NORMAL, "Searched Settlement Institution as [%s]", txnmsg.SettInst );

			memset( InstId, 0, sizeof( InstId ) );
			if( ezinstselectutil.getInst( &txnmsg, EZIMF_FWDINST, InstId ) < 0 )
			{
				memset( txnmsg.ForwardInst, 0, sizeof( txnmsg.ForwardInst ) );
				strcpy( txnmsg.ForwardInst, txnmsg.AcquirerInst );
			}
			else
			{
				memset( txnmsg.ForwardInst, 0, sizeof( txnmsg.ForwardInst ) );
				strcpy( txnmsg.ForwardInst, InstId );
			}
			trace( DEBUG_NORMAL, "Searched Forwarding Institution as [%s]", txnmsg.ForwardInst );

			if( !strlen( txnmsg.IssuerInst ) )
			{
				memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
				strcpy( txnmsg.IssuerInst, "*" );
			}

			if( !strlen( txnmsg.AcquirerInst ) )
			{
				memset( txnmsg.AcquirerInst, 0, sizeof( txnmsg.AcquirerInst ) );
				strcpy( txnmsg.AcquirerInst, "*" );
			}

			if( !strlen( txnmsg.TxfInst ) )
			{
				memset( txnmsg.TxfInst, 0, sizeof( txnmsg.TxfInst ) );
				strcpy( txnmsg.TxfInst, "*" );
			}

			if( !strlen( txnmsg.SettInst ) )
			{
				memset( txnmsg.SettInst, 0, sizeof( txnmsg.SettInst ) );
				strcpy( txnmsg.SettInst, "*" );
			}

			if( !strlen( txnmsg.ForwardInst ) )
			{
				memset( txnmsg.ForwardInst, 0, sizeof( txnmsg.ForwardInst ) );
				strcpy( txnmsg.ForwardInst, "*" );
			}

			memset( &ezinstroutetype, 0, sizeof( struct EzInstRouteType ) );

			//Check Acquirer Institution in InstProfile Table

			if( ezinstprofileutil.readInstProfile( txnmsg.AcquirerInst ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Searching AcquirerInst[%s] in InstProfile....", txnmsg.AcquirerInst );
				txnmsg.ReasonCode = EZLINK_Reason_NoAcqInst_Err;
				txnmsg.MsgType += 10;
				txnmsg.RespCode = EZLINK_RC_InvalidAcquirer;
				if( !ezmsgtypepropertyutil.isResponse() )
					dropTxn( &txnmsg );
				continue;
			}
			memset( ezinstroutetype.AcquirerInstRouteType, 0, sizeof( ezinstroutetype.AcquirerInstRouteType ) );
			strcpy( ezinstroutetype.AcquirerInstRouteType, ezinstprofileutil.getInstRouteType() );

			trace( "AcquirerInstRouteType[%s]", ezinstroutetype.AcquirerInstRouteType );

			if( ezinstprofileutil.isFinInstitution() )
			{
				memset( txnmsg.AcquirerBin, 0, sizeof( txnmsg.AcquirerBin ) );
				strcpy( txnmsg.AcquirerBin, ezinstprofileutil.getPrimaryBin() );
				trace( "AcquirerBin[%s] Selected for AcquirerInstId[%s]", txnmsg.AcquirerBin, txnmsg.AcquirerInst );
			}

			//Check Issuer Institution in InstProfile Table

			if( !strcmp( txnmsg.AcquirerInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
				strcpy( ezinstroutetype.IssuerInstRouteType, ezinstprofileutil.getInstRouteType() );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.IssuerInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching IssuerInst[%s] in InstProfile....", txnmsg.IssuerInst );
					txnmsg.ReasonCode = EZLINK_Reason_IssuerNotFound_Err;
					txnmsg.MsgType += 10;
					txnmsg.RespCode = EZLINK_RC_InvalidIssuer;
					if( !ezmsgtypepropertyutil.isResponse() )
						dropTxn( &txnmsg );
					continue;
				}
				memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
				strcpy( ezinstroutetype.IssuerInstRouteType, ezinstprofileutil.getInstRouteType() );
			}

			if( ezinstprofileutil.isFinInstitution() )
			{
				if( strlen( txnmsg.chn ) >= 16  && strcmp( txnmsg.DeviceType, "TELLER" ) )
				{
					if( ezbinprofileutil.readBINProfile( txnmsg.IssuerInst, txnmsg.chn ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in reading InstId[%s] CHN[%s] from BINProfile....", txnmsg.IssuerInst, txnmsg.m_chn );
						txnmsg.ReasonCode = EZLINK_Reason_NoIssuerBin_Err;
						txnmsg.MsgType += 10;
						txnmsg.RespCode = EZLINK_RC_InvalidIssuer;
						if( !ezmsgtypepropertyutil.isResponse() )
							dropTxn( &txnmsg );
						continue;
					}

					if( ezinstprofileutil.isPADSSEnabled() )
					{
						if( !strlen( txnmsg.t_chn ) )
						{
							memset( txnmsg.t_chn, 0, sizeof( txnmsg.t_chn ) );
							ezpadssutil.tokenizeString( txnmsg.chn, txnmsg.IssuerInst, txnmsg.t_chn );
						}
					}
					else
					{
						memset( txnmsg.t_chn, 0, sizeof( txnmsg.t_chn ) );
						strcpy( txnmsg.t_chn, txnmsg.m_chn );
					}

					if( !ezbinprofileutil.isTxnAllowed( txnmsg.TxnCode ) )
					{
						trace( DEBUG_ERROR, "TxnCode[%d] is not allowed for InstId[%s] BIN[%s]", txnmsg.TxnCode, txnmsg.IssuerInst, ezbinprofileutil.getBIN() );
						txnmsg.ReasonCode = EZLINK_Reason_TxnNotAllowed_Err;
						txnmsg.MsgType += 10;
						txnmsg.RespCode = EZLINK_RC_TransactionNotAllowed;
						if( !ezmsgtypepropertyutil.isResponse() )
							dropTxn( &txnmsg );
						continue;
					}
					memset( txnmsg.IssuerBin, 0, sizeof( txnmsg.IssuerBin ) );
					strcpy( txnmsg.IssuerBin,ezinstprofileutil.getPrimaryBin() );
					memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
					strcpy( ezinstroutetype.IssuerInstRouteType, ezbinprofileutil.getRouteType() );
				}
			}
			else
			{
				if( ezinstprofileutil.isPADSSEnabled() )
				{
					memset( txnmsg.t_chn, 0, sizeof( txnmsg.t_chn ) );
					strcpy( txnmsg.t_chn, txnmsg.m_chn );
				}
				else
				{
					memset( txnmsg.t_chn, 0, sizeof( txnmsg.t_chn ) );
					strcpy( txnmsg.t_chn, txnmsg.chn );
				}
			}

			//Check Transfer Institution in InstProfile Table

			if( !strcmp( txnmsg.TxfInst, "*" ) )
			{
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.TxfInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, ezinstroutetype.IssuerInstRouteType );
			}
			else if( !strcmp( txnmsg.TxfInst, txnmsg.AcquirerInst ) )
			{
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.TxfInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching TxfInst[%s] in InstProfile....", txnmsg.TxfInst );
					txnmsg.ReasonCode = EZLINK_Reason_NoTxfInst_Err;
					txnmsg.MsgType += 10;
					txnmsg.RespCode = EZLINK_RC_UnableToProcess;
					if( !ezmsgtypepropertyutil.isResponse() )
						dropTxn( &txnmsg );
					continue;
				}
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, ezinstprofileutil.getInstRouteType() );
			}

			//Check Settlement Institution in InstProfile Table

			if( !strcmp( txnmsg.SettInst, "*" ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.SettInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstroutetype.IssuerInstRouteType );
			}
			else if( !strcmp( txnmsg.SettInst, txnmsg.AcquirerInst ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else if( !strcmp( txnmsg.SettInst, txnmsg.TxfInst ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstroutetype.TxfInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.SettInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching SettInst[%s] in InstProfile....", txnmsg.SettInst );
					txnmsg.ReasonCode = EZLINK_Reason_NoSettInst_Err;
					txnmsg.MsgType += 10;
					txnmsg.RespCode = EZLINK_RC_UnableToProcess;
					if( !ezmsgtypepropertyutil.isResponse() )
						dropTxn( &txnmsg );
					continue;
				}
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstprofileutil.getInstRouteType() );
			}

			//Check Forward Institution in InstProfile Table

			if( !strcmp( txnmsg.ForwardInst, "*" ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.IssuerInstRouteType );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.AcquirerInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.TxfInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.TxfInstRouteType );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.SettInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.SettInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.ForwardInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching ForwardInst[%s] in InstProfile....", txnmsg.ForwardInst );
					txnmsg.ReasonCode = EZLINK_Reason_NoFwdInst_Err;
					txnmsg.MsgType += 10;
					txnmsg.RespCode = EZLINK_RC_UnableToProcess;
					if( !ezmsgtypepropertyutil.isResponse() )
						dropTxn( &txnmsg );
					continue;
				}
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstprofileutil.getInstRouteType() );
			}

			memset( NetworkId, 0, sizeof( NetworkId ) );
			if( eznetworkselectutil.getNtwk( &txnmsg, EZIMF_ISSNTWK, NetworkId ) < 0 )
			{
				trace("Failed IssuerNetworkId search");
				memset( txnmsg.IssuerNetworkId, 0, sizeof( txnmsg.IssuerNetworkId ) );
				strcpy( txnmsg.IssuerNetworkId, "*" );
			}
			else
			{
				memset( txnmsg.IssuerNetworkId, 0, sizeof( txnmsg.IssuerNetworkId ) );
				strcpy( txnmsg.IssuerNetworkId, NetworkId );

			}
			trace( DEBUG_NORMAL, "Searched Issuer Network as [%s]", txnmsg.IssuerNetworkId );

			memset( NetworkId, 0, sizeof( NetworkId ) );
			if( eznetworkselectutil.getNtwk( &txnmsg, EZIMF_ACQNTWK, NetworkId ) < 0 )
			{
				trace("Failed IssuerNetworkId search");
				memset( txnmsg.AcqNetworkId, 0, sizeof( txnmsg.AcqNetworkId ) );
				strcpy( txnmsg.AcqNetworkId, "*" );
			}
			else
			{
				memset( txnmsg.AcqNetworkId, 0, sizeof( txnmsg.AcqNetworkId ) );
				strcpy( txnmsg.AcqNetworkId, NetworkId );

			}
			trace( DEBUG_NORMAL, "Searched Acquirer Network as [%s]", txnmsg.AcqNetworkId );

			memset( NetworkId, 0, sizeof( NetworkId ) );
			if( eznetworkselectutil.getNtwk( &txnmsg, EZIMF_TXFNTWK, NetworkId ) < 0 )
			{
				memset( txnmsg.TxfNetworkId, 0, sizeof( txnmsg.TxfNetworkId ) );
				strcpy( txnmsg.TxfNetworkId, "*" );
			}
			else
			{
				memset( txnmsg.TxfNetworkId, 0, sizeof( txnmsg.TxfNetworkId ) );
				strcpy( txnmsg.TxfNetworkId, NetworkId );
			}
			trace( DEBUG_NORMAL, "Searched Txf Network as [%s]", txnmsg.TxfNetworkId );

			memset( NetworkId, 0, sizeof( NetworkId ) );
			if( eznetworkselectutil.getNtwk( &txnmsg, EZIMF_SETTNTWK, NetworkId ) < 0 )
			{
				memset( txnmsg.SettNetworkId, 0, sizeof( txnmsg.SettNetworkId ) );
				strcpy( txnmsg.SettNetworkId, "*" );
			}
			else
			{
				memset( txnmsg.SettNetworkId, 0, sizeof( txnmsg.SettNetworkId ) );
				strcpy( txnmsg.SettNetworkId, NetworkId );

			}
			trace( DEBUG_NORMAL, "Searched Settlement Network as [%s]", txnmsg.SettNetworkId );

			memset( NetworkId, 0, sizeof( NetworkId ) );
			if( eznetworkselectutil.getNtwk( &txnmsg, EZIMF_FWDNTWK, NetworkId ) < 0 )
			{
				memset( txnmsg.FwdNetworkId, 0, sizeof( txnmsg.FwdNetworkId ) );
				strcpy( txnmsg.FwdNetworkId, "*" );
			}
			else
			{
				memset( txnmsg.FwdNetworkId, 0, sizeof( txnmsg.FwdNetworkId ) );
				strcpy( txnmsg.FwdNetworkId, NetworkId );
			}
			trace( DEBUG_NORMAL, "Searched Forwarding Network as [%s]", txnmsg.FwdNetworkId );
		}
		else
		{
			//Network Management Message
			if( !strlen( txnmsg.IssuerInst ) )
			{
				memset( txnmsg.IssuerInst, 0, sizeof( txnmsg.IssuerInst ) );
				strcpy( txnmsg.IssuerInst, "*" );
			}

			if( !strlen( txnmsg.AcquirerInst ) )
			{
				memset( txnmsg.AcquirerInst, 0, sizeof( txnmsg.AcquirerInst ) );
				strcpy( txnmsg.AcquirerInst, "*" );
			}

			if( !strlen( txnmsg.TxfInst ) )
			{
				memset( txnmsg.TxfInst, 0, sizeof( txnmsg.TxfInst ) );
				strcpy( txnmsg.TxfInst, "*" );
			}

			if( !strlen( txnmsg.SettInst ) )
			{
				memset( txnmsg.SettInst, 0, sizeof( txnmsg.SettInst ) );
				strcpy( txnmsg.SettInst, "*" );
			}

			if( !strlen( txnmsg.ForwardInst ) )
			{
				memset( txnmsg.ForwardInst, 0, sizeof( txnmsg.ForwardInst ) );
				strcpy( txnmsg.ForwardInst, "*" );
			}

			memset( &ezinstroutetype, 0, sizeof( struct EzInstRouteType ) );

			//Check Acquirer Institution in InstProfile Table
			if( !strcmp( txnmsg.AcquirerInst, "*" ) )
			{
				memset( ezinstroutetype.AcquirerInstRouteType, 0, sizeof( ezinstroutetype.AcquirerInstRouteType ) );
				strcpy( ezinstroutetype.AcquirerInstRouteType, "*" );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.AcquirerInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching AcquirerInst[%s] in InstProfile....", txnmsg.AcquirerInst );
					memset( ezinstroutetype.AcquirerInstRouteType, 0, sizeof( ezinstroutetype.AcquirerInstRouteType ) );
					strcpy( ezinstroutetype.AcquirerInstRouteType, "*" );
				}
				else
				{
					memset( ezinstroutetype.AcquirerInstRouteType, 0, sizeof( ezinstroutetype.AcquirerInstRouteType ) );
					strcpy( ezinstroutetype.AcquirerInstRouteType, ezinstprofileutil.getInstRouteType() );
				}
			}

			//Check Issuer Institution in InstProfile Table

			if( !strcmp( txnmsg.IssuerInst, "*" ) )
			{
				memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
				strcpy( ezinstroutetype.IssuerInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.AcquirerInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
				strcpy( ezinstroutetype.IssuerInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.IssuerInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching IssuerInst[%s] in InstProfile....", txnmsg.IssuerInst );
					memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
					strcpy( ezinstroutetype.IssuerInstRouteType, "*" );
				}
				else
				{
					memset( ezinstroutetype.IssuerInstRouteType, 0, sizeof( ezinstroutetype.IssuerInstRouteType ) );
					strcpy( ezinstroutetype.IssuerInstRouteType, ezinstprofileutil.getInstRouteType() );
				}
			}

			//Check Transfer Institution in InstProfile Table

			if( !strcmp( txnmsg.TxfInst, "*" ) )
			{
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.TxfInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, ezinstroutetype.IssuerInstRouteType );
			}
			else if( !strcmp( txnmsg.TxfInst, txnmsg.AcquirerInst ) )
			{
				memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
				strcpy( ezinstroutetype.TxfInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.TxfInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching TxfInst[%s] in InstProfile....", txnmsg.TxfInst );
					memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
					strcpy( ezinstroutetype.TxfInstRouteType, "*" );
				}
				else
				{
					memset( ezinstroutetype.TxfInstRouteType, 0, sizeof( ezinstroutetype.TxfInstRouteType ) );
					strcpy( ezinstroutetype.TxfInstRouteType, ezinstprofileutil.getInstRouteType() );
				}
			}

			//Check Settlement Institution in InstProfile Table

			if( !strcmp( txnmsg.SettInst, "*" ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.TxfInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstroutetype.IssuerInstRouteType );
			}
			else if( !strcmp( txnmsg.TxfInst, txnmsg.AcquirerInst ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else if( !strcmp( txnmsg.SettInst, txnmsg.TxfInst ) )
			{
				memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
				strcpy( ezinstroutetype.SettInstRouteType, ezinstroutetype.TxfInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.SettInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching SettInst[%s] in InstProfile....", txnmsg.SettInst );
					memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
					strcpy( ezinstroutetype.SettInstRouteType, "*" );
				}
				else
				{
					memset( ezinstroutetype.SettInstRouteType, 0, sizeof( ezinstroutetype.SettInstRouteType ) );
					strcpy( ezinstroutetype.SettInstRouteType, ezinstprofileutil.getInstRouteType() );
				}
			}

			//Check Forward Institution in InstProfile Table

			if( !strcmp( txnmsg.ForwardInst, "*" ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, "*" );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.IssuerInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.IssuerInstRouteType );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.AcquirerInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.AcquirerInstRouteType );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.TxfInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.TxfInstRouteType );
			}
			else if( !strcmp( txnmsg.ForwardInst, txnmsg.SettInst ) )
			{
				memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
				strcpy( ezinstroutetype.FwdInstRouteType, ezinstroutetype.SettInstRouteType );
			}
			else
			{
				if( ezinstprofileutil.readInstProfile( txnmsg.ForwardInst ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Searching ForwardInst[%s] in InstProfile....", txnmsg.ForwardInst );
					memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
					strcpy( ezinstroutetype.FwdInstRouteType, "*" );
				}
				else
				{
					memset( ezinstroutetype.FwdInstRouteType, 0, sizeof( ezinstroutetype.FwdInstRouteType ) );
					strcpy( ezinstroutetype.FwdInstRouteType, ezinstprofileutil.getInstRouteType() );
				}
			}
		}

		if( !strlen( txnmsg.IssuerNetworkId ) )
		{
			memset( txnmsg.IssuerNetworkId, 0, sizeof( txnmsg.IssuerNetworkId ) );
			strcpy( txnmsg.IssuerNetworkId, "*" );
		}

		if( !strlen( txnmsg.AcqNetworkId ) )
		{
			memset( txnmsg.AcqNetworkId, 0, sizeof( txnmsg.AcqNetworkId ) );
			strcpy( txnmsg.AcqNetworkId, "*" );
		}

		if( !strlen( txnmsg.TxfNetworkId ) )
		{
			memset( txnmsg.TxfNetworkId, 0, sizeof( txnmsg.TxfNetworkId ) );
			strcpy( txnmsg.TxfNetworkId, "*" );
		}

		if( !strlen( txnmsg.SettNetworkId ) )
		{
			memset( txnmsg.SettNetworkId, 0, sizeof( txnmsg.SettNetworkId ) );
			strcpy( txnmsg.SettNetworkId, "*" );
		}

		if( !strlen( txnmsg.FwdNetworkId ) )
		{
			memset( txnmsg.FwdNetworkId, 0, sizeof( txnmsg.FwdNetworkId ) );
			strcpy( txnmsg.FwdNetworkId, "*" );
		}

		if( !strlen( txnmsg.NetworkId ) )
		{
			memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
			strcpy( txnmsg.NetworkId, "*" );
		}

		memset( txnmsg.SrcChannel, 0, sizeof( txnmsg.SrcChannel ) );
		strcpy( txnmsg.SrcChannel, GetLastSenderChannelName() );

		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
		if( eztxnrouteinfoutil.getRouteSelectList( &txnmsg, ezinstroutetype, RouteSelectList ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in getting RouteSelect List..Dropping Message" );

			if( ezmsgtypepropertyutil.isTxnMsg() && ezmsgtypepropertyutil.isNewRequest() )
			{
				txnmsg.ReasonCode = EZLINK_Reason_RouteSelectList_Err;
				txnmsg.MsgType += 10;
				dropTxn( &txnmsg );
			}
			continue;
		}


		NRoutes = eztxnfldval.getNTokens( RouteSelectList, ',' );

		for( int i = 0; i < NRoutes; i++ )
		{
			memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
			eztxnfldval.getTokenExSpaces( RouteSelectList, RouteSelectId, ',', i + 1 );

			memset( ChannelName, 0, sizeof( ChannelName ) );
			memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
			if( eztxnrouteselectutil.readRoutselect( RouteSelectId, MsgTranslateId, ChannelName ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading RouteSelectId[%s] in EzTxnRouteSelect Table", RouteSelectId );
				continue;
			}

			trace( DEBUG_NORMAL, "Read ChannelName[%s] MsgTranslateId[%s] from EzTxnRouteSelect for RouteSelectId[%s]",  ChannelName, MsgTranslateId, RouteSelectId );

			memset( &localtxnmsg, 0, sizeof( struct EzTxnMsg ) );
			memcpy( &localtxnmsg, &txnmsg, sizeof( struct EzTxnMsg ) );

			if( strcmp( MsgTranslateId, "*" ) )
			{
				if( ezmsgtranslateutil.translateMsg( MsgTranslateId, &localtxnmsg ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Reading MsgTranslateId[%s] from EzMsgTranslate Table", MsgTranslateId );
					continue;
				}
			}

			if( !strcmp( ChannelName, EZIMF_ORGCHANNEL ) )
			{
				if( ( !strlen( localtxnmsg.OrgChannel ) ) || ( !strcmp( localtxnmsg.OrgChannel, "*" ) ) )
				{
					trace( DEBUG_ERROR, "Originating Channel is NULL..Cannot Route Message to Originating Channel");
					continue;
				}
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, localtxnmsg.OrgChannel );

				if( ( !strlen( localtxnmsg.OrgPort ) ) || ( !strcmp( localtxnmsg.OrgPort, "*" ) ) )
				{
					trace( DEBUG_ERROR, "Originating Port is NULL..Cannot Route Message to Originating Port");
					continue;
				}
				memset( localtxnmsg.DestPort, 0, sizeof( localtxnmsg.DestPort ) );
				strcpy( localtxnmsg.DestPort, localtxnmsg.OrgPort );
			}
			else if ( ( !strcmp( ChannelName, EZIMF_ISSNTWK ) ) || ( !strcmp( ChannelName, EZIMF_ACQNTWK ) ) || ( !strcmp( ChannelName, EZIMF_SETTNTWK ) ) || ( !strcmp( ChannelName, EZIMF_FWDNTWK ) ) || ( !strcmp( ChannelName, EZIMF_TXFNTWK ) ) )
			{
				if ( !strcmp( ChannelName, EZIMF_ISSNTWK ) )
				{
					if( eznetworkutil.readNetworkMemory( localtxnmsg.IssuerNetworkId ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reading Issuer NetworkId[%s] from NetworkMemory Table", localtxnmsg.IssuerNetworkId );
						continue;
					}
					memset( localtxnmsg.NetworkId, 0, sizeof( localtxnmsg.NetworkId ) );
					strcpy( localtxnmsg.NetworkId, localtxnmsg.IssuerNetworkId );
				}
				else if ( !strcmp( ChannelName, EZIMF_ACQNTWK ) )
				{
					if( eznetworkutil.readNetworkMemory( localtxnmsg.AcqNetworkId ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reading Issuer NetworkId[%s] from NetworkMemory Table", localtxnmsg.AcqNetworkId );
						continue;
					}
					memset( localtxnmsg.NetworkId, 0, sizeof( localtxnmsg.NetworkId ) );
					strcpy( localtxnmsg.NetworkId, localtxnmsg.AcqNetworkId );
				}
				else if ( !strcmp( ChannelName, EZIMF_FWDNTWK ) )
				{
					if( eznetworkutil.readNetworkMemory( localtxnmsg.FwdNetworkId ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reading Issuer NetworkId[%s] from NetworkMemory Table", localtxnmsg.FwdNetworkId );
						continue;
					}
					memset( localtxnmsg.NetworkId, 0, sizeof( localtxnmsg.NetworkId ) );
					strcpy( localtxnmsg.NetworkId, localtxnmsg.FwdNetworkId );
				}
				else if ( !strcmp( ChannelName, EZIMF_TXFNTWK ) )
				{
					if( eznetworkutil.readNetworkMemory( localtxnmsg.TxfNetworkId ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reading Issuer NetworkId[%s] from NetworkMemory Table", localtxnmsg.TxfNetworkId );
						continue;
					}
					memset( localtxnmsg.NetworkId, 0, sizeof( localtxnmsg.NetworkId ) );
					strcpy( localtxnmsg.NetworkId, localtxnmsg.TxfNetworkId );
				}
				else if ( !strcmp( ChannelName, EZIMF_SETTNTWK ) )
				{
					if( eznetworkutil.readNetworkMemory( localtxnmsg.SettNetworkId ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reading Issuer NetworkId[%s] from NetworkMemory Table", localtxnmsg.SettNetworkId );
						continue;
					}
					memset( localtxnmsg.NetworkId, 0, sizeof( localtxnmsg.NetworkId ) );
					strcpy( localtxnmsg.NetworkId, localtxnmsg.SettNetworkId );
				}

				EventTimeOut = eznetworkutil.getNetworkTimeOut();

				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, eznetworkutil.getNetworkChannelName() );

				memset( localtxnmsg.DestPort, 0, sizeof( localtxnmsg.DestPort ) );
				strcpy( localtxnmsg.DestPort, eznetworkutil.getNetworkPortName() );
				if( eznetworkutil.isNetworkKeyReq() && !ezmsgtypepropertyutil.isOldRequest() && txnmsg.DeviceFlag == EZLINK_MSG_FROM_DEVICE )
				{
					trace( DEBUG_TEST, "Need to translate PIN Block for InstId[%s] DeviceId[%s] NetworkId[%s] PINBlock[%s]", txnmsg.AcquirerInst, localtxnmsg.OrgPort, localtxnmsg.NetworkId, localtxnmsg.PINBlock ) ;
					if( !strlen( localtxnmsg.PINBlock ) )
					{
						trace( DEBUG_ERROR, "PINBlock is Null....Cannot Translate PIN Block...Dropping Message" );
						continue;
					}
					if( !strlen( localtxnmsg.AcquirerInst ) )
					{
						trace( DEBUG_ERROR, "InstId is Null....Cannot Translate PIN Block...Dropping Message" );
						continue;
					}
					if( !strlen( localtxnmsg.OrgPort ) )
					{
						trace( DEBUG_ERROR, "DeviceId is Null....Cannot Translate PIN Block...Dropping Message" );
						continue;
					}
					if( !strlen( localtxnmsg.NetworkId ) )
					{
						trace( DEBUG_ERROR, "NetworkId is Null....Cannot Translate PIN Block...Dropping Message" );
						continue;
					}
					memset( TranPinBlock, 0, sizeof( TranPinBlock ) );
					if( localtxnmsg.MerchantType == 6011 )
					{
						if( ezsecurityutil.TranslatePINATMToNetwork( txnmsg.AcquirerInst, localtxnmsg.OrgPort, localtxnmsg.NetworkId, localtxnmsg.PINBlock, localtxnmsg.chn, TranPinBlock ) < 0 )
						{
							trace( DEBUG_ERROR, "Error in Translating PINBlock for InstId[%s] DeviceId[%s] NetworkId[%s] PINBlock[%s] CHN[%s]", localtxnmsg.AcquirerInst, localtxnmsg.OrgPort, localtxnmsg.NetworkId, localtxnmsg.PINBlock, localtxnmsg.m_chn );
							continue;
						}
						trace( DEBUG_TEST, "Translated PINBlock Successfully[%s]", TranPinBlock );
					}
					else
					{
						if( ezsecurityutil.TranslatePINDeviceToNetwork( txnmsg.AcquirerInst, localtxnmsg.OrgPort, localtxnmsg.NetworkId, localtxnmsg.PINBlock, localtxnmsg.chn, TranPinBlock ) < 0 )
						{
							trace( DEBUG_ERROR, "Error in Translating PINBlock for InstId[%s] DeviceId[%s] NetworkId[%s] PINBlock[%s] CHN[%s]", localtxnmsg.AcquirerInst, localtxnmsg.OrgPort, localtxnmsg.NetworkId, localtxnmsg.PINBlock, localtxnmsg.m_chn );
							continue;
						}
						trace( DEBUG_TEST, "Translated PINBlock Successfully[%s]", TranPinBlock );
					}
					memset( localtxnmsg.PINBlock, 0, sizeof( localtxnmsg.PINBlock ) );
					strcpy( localtxnmsg.PINBlock, TranPinBlock );
				}
			}

			if( ezmsgtypepropertyutil.readEzMsgTypeProperty( localtxnmsg.MsgType ) < 0 )
			{
				trace( "Error in reading MsgType[%d] in ezmsgtypeproperty table...Dropping Message", localtxnmsg.MsgType );
				continue;
			}

			if( ezmsgtypepropertyutil.isTxnMsg() )
			{
				memset( EventId, 0, sizeof( EventId ) );
				eztxnrefselectutil.getTxnRefNum( &localtxnmsg, EventId );

				if( strcmp( ChannelName, "*" ) )
				{
					if( ezchannelpropertyutil.readChannelProperty( ChannelName ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Reading ChannelName[%s] in EzChannelProperty Table", ChannelName );
						continue;
					}
					if( ezchannelpropertyutil.isDeviceChannel() || ezchannelpropertyutil.isNetworkChannel() )
					{
						memset( localtxnmsg.SrcPort, 0, sizeof( localtxnmsg.SrcPort ) );
						strcpy( localtxnmsg.SrcPort, "*" );
					}
					else
					{
						memset( localtxnmsg.SrcPort, 0, sizeof( localtxnmsg.SrcPort ) );
						strcpy( localtxnmsg.SrcPort, "*" );
						memset( localtxnmsg.DestPort, 0, sizeof( localtxnmsg.DestPort ) );
						strcpy( localtxnmsg.DestPort, "*" );
					}
				}
				if( ( ezeventpropertyutil.isEventReq( ChannelName, localtxnmsg.MsgType, localtxnmsg.TxnCode, localtxnmsg.RespCode ) ) && ( ezmsgtypepropertyutil.isTxnMsg() ) )
				{
					trace( DEBUG_NORMAL, "Event Required for ChannelName[%s] MsgType[%d] TxnCode[%d] RespCode[%d]", ChannelName, localtxnmsg.MsgType, localtxnmsg.TxnCode, localtxnmsg.RespCode );

					if( !ezchannelpropertyutil.isNetworkChannel() )
					{
						EventTimeOut = ezeventpropertyutil.getEventTimeOut();
						trace( DEBUG_TEST, "EventTimeOut[%d]", EventTimeOut );
					}

					trace( DEBUG_NORMAL, "Creating Event with with EventId[%s]....TimeOut[%d]", EventId, EventTimeOut );

					if( createEvent( EventId, ( char * )&localtxnmsg, sizeof( struct EzTxnMsg ), EventTimeOut ) < 0 )
					{
						trace( DEBUG_ERROR, "Error in Creating Event with EventId[%s] EventTimeOut[%d]", EventId, EventTimeOut );
						if( ezmsgtypepropertyutil.isNewRequest() )
						{
							localtxnmsg.ReasonCode = EZLINK_Reason_EventCreation_Err;
							localtxnmsg.MsgType += 10;
							dropTxn( &localtxnmsg );
							break;
						}
					}
					else
						trace( DEBUG_ERROR, "Event Created with EventId[%s] EventTimeOut[%d]", EventId, EventTimeOut );
				}
				if( eznetworkutil.isCutOverReq() && !localtxnmsg.BusinessDate )
				{
					if( ezbusdayutil.readNetworkBusDay( localtxnmsg.NetworkId ) < 0 )
						localtxnmsg.BusinessDate = ezdatetimeutil.getSysDate();
					else
					{
						if( ezbusdayutil.isNetworkCutOverReq() )
							localtxnmsg.BusinessDate = ezbusdayutil.getCutOverDate();
						else
							localtxnmsg.BusinessDate = ezdatetimeutil.getSysDate();
					}
				}
				if( eztxnrouteselectutil.isInsertTxnLog() )
				{
					trace( DEBUG_NORMAL, "Need to Insert the Message in EzTxnLog Table" );
					if( !strcmp( ChannelName, "*" ) )
					{
						RefSeqNo = 1;
						if( eztxnlogutil.insertTxnLog( &localtxnmsg, EventId, GetLastSenderChannelName(), GetSourceChannelName(), RefSeqNo ) < 0 )
							trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
					}
					else
					{
						RefSeqNo = 1;
						if( eztxnlogutil.insertTxnLog( &localtxnmsg, EventId, GetLastSenderChannelName(), ChannelName, RefSeqNo ) < 0 )
							trace( DEBUG_ERROR, "Error in Sending Insert EzTxnLog Message to EzTxnLogger" );
					}
				}
				else if ( eztxnrouteselectutil.isUpdateTxnLog() )
				{
					trace( DEBUG_NORMAL, "Need to Update the Message in EzTxnLog Table" );
					if( eztxnlogutil.updateTxnLog( &localtxnmsg, EventId ) < 0 )
						trace( DEBUG_ERROR, "Error in Sending Update EzTxnLog Message to EzTxnLogger" );
				}
			}
			if( strcmp( ChannelName, "*" ) && strcmp( ChannelName, GetSourceChannelName() ) )
				sendToChannel( ChannelName, &localtxnmsg );
		}
	}
}

int main( int argc, char **argv )
{
	EzTxnMgr txnmgrobj;
	txnmgrobj.initEzTxnMgr( argv[ 0 ] );
	txnmgrobj.ServiceRequest();
	return 1;
}
