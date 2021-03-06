#include <ezbusiness/ezguicontroller.h>

int EzGUIReplayRequest :: initGUIReplayRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initReplayUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ReplayUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIReplayRequest :: processReplayList( const char *GuiReq )
{
	int ReplayCount = 0, ReplayOffset = 0;
	char Status[ 20 ], ReplayStatus[ 20 ],ReplayProperty[ 50 ], ReplayAction[ 50 ], ReplayFlag[ 20 ], MsgTypeIndicatorFlag[ 20 ];
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	struct EzReplayTable replaytable_rec;

	ReplayCount = getCurrentReplayCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !ReplayOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "REPLAY", GUI_GS , ReplayCount, GUI_GS );

		for( int i = ReplayOffset; i < ReplayTable_MaxNetworks; i++ )
		{
			memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
			if( getNextReplayRecord( &replaytable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th ReplayRecord....", i );
				continue;
			}

			if ( ( strcmp( replaytable_rec.NetworkId, REPLAY_NETWORKID_INIT_VAL ) ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				memset( ReplayProperty, 0, sizeof( ReplayProperty ) );
				memset( ReplayAction, 0, sizeof( ReplayAction ) );
				memset( Status, 0, sizeof( Status ) );
				memset( ReplayStatus, 0, sizeof( ReplayStatus ) );
				memset( ReplayFlag, 0, sizeof( ReplayFlag ) );
				memset( MsgTypeIndicatorFlag, 0, sizeof( MsgTypeIndicatorFlag ) );

				if( replaytable_rec.ReplayProperty == REPLAY_DOWN )
					strcpy( ReplayProperty, "REPLAY WHEN DOWN" );
				else if( replaytable_rec.ReplayProperty == REPLAY_UP )
					strcpy( ReplayProperty, "REPLAY WHEN UP" );
				else
					strcpy( ReplayProperty, "REPLAY WHEN ALWAYS" );

				if( replaytable_rec.ReplayAction == REPLAY_TIMEOUT_DOWN )
					strcpy( ReplayAction, "TIMEOUT, DOWN THE NETWORK" );
				else
					strcpy( ReplayAction, "TIMEOUT, CONTINUE REPLAY" );

				if( replaytable_rec.Status == REPLAY_NETWORK_RUNNING )
					strcpy( Status, "RUNNING" );
				else
					strcpy( Status, "SUSPENDED" );

				if( replaytable_rec.ReplayStatus == REPLAY_STATUS_ACTIVE )
					strcpy( ReplayStatus, "ACTIVE" );
				else
					strcpy( ReplayStatus, "IDLE" );

				if( replaytable_rec.ReplayFlag == REPLAY_FLAG_IDLE )
					strcpy( ReplayFlag, "IDLE" );
				else
					strcpy( ReplayFlag, "ACTIVE" );

				if( replaytable_rec.MsgTypeIndicator == REPLAY_MSGTYPEINDICATOR_INIT )
					strcpy( MsgTypeIndicatorFlag, "IDLE" );
				else
					strcpy( MsgTypeIndicatorFlag, "DOWNLOAD" );

				sprintf( RecordString, "%s%c%d%c%s%c%s%c%s%c%s%c%s%c%s%c", ( replaytable_ptr + i )->NetworkId, GUI_FS,  ( replaytable_ptr + i )->ReplayInterval, GUI_FS, ReplayProperty, GUI_FS,  ReplayAction, GUI_FS, Status, GUI_FS, ReplayStatus, GUI_FS, ReplayFlag, GUI_FS, MsgTypeIndicatorFlag, GUI_RS );

				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					ReplayOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}
			if( i + 1 == ReplayTable_MaxNetworks )
			{
				ReplayOffset = i + 1;
					break;
			}

		}
		if( ReplayOffset == ReplayTable_MaxNetworks )
		{
			strcat( GuiResp, "\x0f" );
			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
				dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
			break;
		}
		else
		{
			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			{
				dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
				break;
			}
		}
	}
	return 1;
}

int EzGUIReplayRequest :: processReplayAdd( const char *GuiReq )
{
	struct EzNetworkReplay networkreplay_rec;
	struct EzReplayTable replaytable_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Replay Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Replay Add Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkreplay_rec, 0, sizeof( struct EzNetworkReplay ) );
	retval = dbutil_ptr->readEzNetworkReplay( NetworkId, &networkreplay_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkReplay Table....SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_SEARCH_TABLE );
		return -1;
	}

	memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
	strcpy( replaytable_rec.NetworkId, networkreplay_rec.NetworkId );
	replaytable_rec.ReplayInterval = networkreplay_rec.ReplayInterval;
	replaytable_rec.ReplayProperty = networkreplay_rec.ReplayProperty;
	replaytable_rec.ReplayAction = networkreplay_rec.ReplayAction;
	replaytable_rec.ReplayLookUpInterval = networkreplay_rec.ReplayLookUpInterval;
	replaytable_rec.Status = REPLAY_NETWORK_RUNNING;
	replaytable_rec.ReplayStatus = REPLAY_STATUS_IDLE;
	replaytable_rec.ReplayFlag = REPLAY_FLAG_IDLE;
	replaytable_rec.MsgTypeIndicator = REPLAY_MSGTYPEINDICATOR_INIT;

	if( addReplayMemory( replaytable_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding NetworkId[%s] in ReplayMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIReplayRequest :: processReplayDelete( const char *GuiReq )
{
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Replay Remove Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Replay Remove Request for NetworkId[%s]...", NetworkId );

	if( deleteReplayMemory( NetworkId ) < 0 )
	{
		dptr->trace( "Error in removing NetworkId[%s] from ReplayMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIReplayRequest :: processReplayUpdate( const char *GuiReq )
{
	struct EzNetworkReplay networkreplay_rec;
	struct EzReplayTable replaytable_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Replay Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Replay Update Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkreplay_rec, 0, sizeof( struct EzNetworkReplay ) );
	retval = dbutil_ptr->readEzNetworkReplay( NetworkId, &networkreplay_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkReplay Table....SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_SEARCH_TABLE );
		return -1;
	}

	memset( &replaytable_rec, 0, sizeof( struct EzReplayTable ) );
	strcpy( replaytable_rec.NetworkId, networkreplay_rec.NetworkId );
	replaytable_rec.ReplayInterval = networkreplay_rec.ReplayInterval;
	replaytable_rec.ReplayProperty = networkreplay_rec.ReplayProperty;
	replaytable_rec.ReplayAction = networkreplay_rec.ReplayAction;
	replaytable_rec.ReplayLookUpInterval = networkreplay_rec.ReplayLookUpInterval;
	replaytable_rec.Status = REPLAY_NETWORK_RUNNING;
	replaytable_rec.ReplayStatus = REPLAY_STATUS_IDLE;
	replaytable_rec.ReplayFlag = REPLAY_FLAG_IDLE;
	replaytable_rec.MsgTypeIndicator = REPLAY_MSGTYPEINDICATOR_INIT;

	if( updateReplayMemory( replaytable_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Updating NetworkId[%s] in ReplayMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIReplayRequest :: processReplayStatusUpdate( const char *GuiReq, int ReplayStatus )
{
	char NetworkId[ 17 ];
	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Replay Status Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Replay Status Update Request for NetworkId[%s]...", NetworkId );

	if( updateReplayStatus( NetworkId, ReplayStatus ) < 0 )
	{
		dptr->trace( "Error in Updating Replay Status in Replay Memory...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_STATUS_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIReplayRequest :: processIntimateReplay( const char *GuiReq )
{
	char NetworkId[ 17 ];
	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Intimate Replay Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Intimate Replay Request for NetworkId[%s]...", NetworkId );

	struct EzTxnMsg txnmsg;
	memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

	txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
	strcpy( txnmsg.NetworkId, NetworkId );

	if( chutil_ptr->WriteChannel( EZSAFREADERCHANNEL, ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Writing Initimate NetworkReplay Message to Channel[%s] for NetworkId[%s]", "EzSafReader", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_INTIMATE );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Written Initimate NetworkReplay Message to Channel[%s] for NetworkId[%s]", "EzSafReader", NetworkId );\
	return 1;
}

int EzGUIReplayRequest :: processReplayRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing ReplayRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Replay request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Replay request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_REPLAY_COMMANDTYPE );
		retval = -1;
	}

	if( retval < 0 )
	{
		RespFlag = 1;
		memset( GuiResp, 0, sizeof( GuiResp ) );
		sprintf( GuiResp, "%s%c%d%c%s", GuiReq, GUI_ES, RespFlag, GUI_ES, ErrDesc );
		if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
		return -1;
	}

	switch ( atoi( TempStr ) )
	{
		case GUI_LIST_CMD:
			retval = processReplayList( GuiReq );
		break;

		case GUI_ADD_CMD:
			retval = processReplayAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processReplayDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processReplayUpdate( GuiReq );
		break;

		case GUI_SUSPEND_CMD:
			retval = processReplayStatusUpdate( GuiReq, REPLAY_NETWORK_SUSPEND );
		break;

		case GUI_RESUME_CMD:
			retval = processReplayStatusUpdate( GuiReq, REPLAY_NETWORK_RUNNING );
		break;

		case GUI_INTIMATE_CMD:
			retval = processIntimateReplay( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Replay..GUI Command Received..." );
			retval = -1;
	}

	if( atoi( TempStr ) != GUI_LIST_CMD )
	{
		if( retval < 0 )
		{
			RespFlag = 1;
			memset( GuiResp, 0, sizeof( GuiResp ) );
			sprintf( GuiResp, "%s%c%d%c%s", GuiReq, GUI_ES, RespFlag, GUI_ES, ErrDesc );
		}
		else
		{
			RespFlag = 0;
			memset( GuiResp, 0, sizeof( GuiResp ) );
			sprintf( GuiResp, "%s%c%d%c%s", GuiReq, GUI_ES, RespFlag );
		}

		if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
	}
	return retval;
}


