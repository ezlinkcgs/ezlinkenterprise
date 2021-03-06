#include <ezbusiness/ezguicontroller.h>

int EzGUINetworkRequest :: initGUINetworkRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initNetworkUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing NetworkUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUINetworkRequest :: processNetworkList( const char *GuiReq )
{
	int NetworkCount = 0, NetworkOffset = 0;
	char NetworkStatusStr[ 20 ];
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	struct EzNetworkMemory networkmem_rec;

	NetworkCount = getCurrentNetworkCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );

		if( !NetworkOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "NETWORK", GUI_GS , NetworkCount, GUI_GS );

		for( int i = NetworkOffset; i < MaxNetworks; i++ )
		{
			memset( &networkmem_rec, 0, sizeof( EzNetworkMemory ) );
			if( getNextNetworkRecord( &networkmem_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getting [%d]th NetworkRecord....", i );
				continue;
			}

			if ( strcmp( networkmem_rec.NetworkId, NETWORKID_INIT_VAL ) )
			{
				memset( NetworkStatusStr, 0, sizeof( NetworkStatusStr ) );

				if( networkmem_rec.NetworkStatus == NETWORK_STATUS_UP )
						strcpy( NetworkStatusStr, "UP" );
				else if( networkmem_rec.NetworkStatus == NETWORK_STATUS_DOWN )
						strcpy( NetworkStatusStr, "DOWN" );
				else if( networkmem_rec.NetworkStatus == NETWORK_STATUS_SAF )
						strcpy( NetworkStatusStr, "SAF" );
				else if( networkmem_rec.NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
						strcpy( NetworkStatusStr, "SAFUPLOAD" );
				else if( networkmem_rec.NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
						strcpy( NetworkStatusStr, "SAFDOWNLOAD" );

				memset( RecordString, 0, sizeof( RecordString ) );
				sprintf( RecordString, "%s%c%s%c%s%c%s%c%d%c", networkmem_rec.NetworkId, GUI_FS,  networkmem_rec.ChannelName, GUI_FS, networkmem_rec.PortName, GUI_FS, NetworkStatusStr, GUI_FS,  networkmem_rec.TimeOut, GUI_RS );

				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					NetworkOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}
			if( i + 1 == MaxNetworks )
			{
				NetworkOffset = i + 1;
				break;
			}
		}
		if( NetworkOffset == MaxNetworks )
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

int EzGUINetworkRequest :: processNetworkAdd( const char *GuiReq )
{
	struct EzNetwork eznetwork_rec;
	struct EzNetworkMemory network_rec;
	int retval;
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Network Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Network Add Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &eznetwork_rec, 0, sizeof( struct EzNetwork ) );
	retval = dbutil_ptr->readEzNetwork( NetworkId, &eznetwork_rec );
	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading NetworkId[%s] from EzNetwork Table...SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_TABLE );
		return -1;
	}

	memset( &network_rec, 0, sizeof( struct EzNetworkMemory ) );
	strcpy( network_rec.InstId, eznetwork_rec.InstId );
	strcpy( network_rec.NetworkId, eznetwork_rec.NetworkId );
	strcpy( network_rec.NetworkName, eznetwork_rec.NetworkName );
	strcpy( network_rec.NetworkPropertyId, eznetwork_rec.NetworkPropertyId );
	network_rec.NetworkStatus = eznetwork_rec.NetworkStatus;
	network_rec.CutOverReq = eznetwork_rec.CutOverReq;
	network_rec.KeyReq = eznetwork_rec.KeyReq;
	network_rec.TimeOut = eznetwork_rec.TimeOut;
	strcpy( network_rec.ChannelName, eznetwork_rec.ChannelName );
	strcpy( network_rec.PortName, eznetwork_rec.PortName );

	if( addNetworkMemory( network_rec ) < 0 )
	{
		dptr->trace( "Error in adding NetworkId[%s] in NetworkMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUINetworkRequest :: processNetworkDelete( const char *GuiReq )
{
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Network Remove Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}
	dptr->trace( "Processing Network Remove Request for NetworkId[%s]...", NetworkId );

	if( deleteNetworkMemory( NetworkId ) < 0 )
	{
		dptr->trace( "Error in removing NetworkId[%s] from NetworkMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUINetworkRequest :: processNetworkUpdate( const char *GuiReq )
{
	struct EzNetwork eznetwork_rec;
	struct EzNetworkMemory network_rec;
	int retval;
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Network Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Network Update Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &eznetwork_rec, 0, sizeof( struct EzNetwork ) );
	retval = dbutil_ptr->readEzNetwork( NetworkId, &eznetwork_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading NetworkId[%s] from EzNetwork Table...SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_TABLE );
		return -1;
	}

	memset( &network_rec, 0, sizeof( struct EzNetworkMemory ) );
	strcpy( network_rec.InstId, eznetwork_rec.InstId );
	strcpy( network_rec.NetworkId, eznetwork_rec.NetworkId );
	strcpy( network_rec.NetworkName, eznetwork_rec.NetworkName );
	strcpy( network_rec.NetworkPropertyId, eznetwork_rec.NetworkPropertyId );
	network_rec.NetworkStatus = eznetwork_rec.NetworkStatus;
	network_rec.CutOverReq = eznetwork_rec.CutOverReq;
	network_rec.KeyReq = eznetwork_rec.KeyReq;
	network_rec.TimeOut = eznetwork_rec.TimeOut;
	strcpy( network_rec.ChannelName, eznetwork_rec.ChannelName );
	strcpy( network_rec.PortName, eznetwork_rec.PortName );

	if( updateNetworkMemory( network_rec ) < 0 )
	{
		dptr->trace( "Error in Updating NetworkId[%s] in NetworkMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUINetworkRequest :: processNetworkStatusUpdate( const char *GuiReq, int StatusFlag )
{
	char NetworkId[ 17 ];
	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Status Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Network Status Update Request for NetworkId[%s]...", NetworkId );

	if( StatusFlag == 1 )
	{
		if( setNetworkStatus( NetworkId, NETWORK_STATUS_DOWN ) < 0 )
		{
			dptr->trace( "Unable to update the network[ %s ] status as Down...", NetworkId );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_NETWORK_MEMORY );
			return -1;
		}
	}
	if( StatusFlag == 2 )
	{
		if( setNetworkStatus( NetworkId, NETWORK_STATUS_UP ) < 0 )
		{
			dptr->trace( "Unable to update the network[ %s ] status as Up...", NetworkId );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_NETWORK_MEMORY );
			return -1;
		}
	}
	return 1;
}

int EzGUINetworkRequest :: processNetworkCommandRequest( const char *GuiReq, int Command )
{
	struct EzNetworkMgrMsg netmsg;
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Status Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Network Command Request for NetworkId[%s]...", NetworkId );

	memset( &netmsg, 0, sizeof( struct EzNetworkMgrMsg ) );
	netmsg.Command = Command;
	strcpy( netmsg.NetworkId, NetworkId );

	if( chutil_ptr->WriteChannel( NETWORKMGRCHANNEL,( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg ) ) < 0 )
	{
		dptr->trace( "Error in Writing Network SignOn Message to NetworkMgr" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_CHANNELWRITE );
		return -1;
	}
	return 1;
}

int EzGUINetworkRequest :: processNetworkRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing NetworkRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Network request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Network request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_COMMANDTYPE );
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
			retval = processNetworkList( GuiReq );
		break;

		case GUI_ADD_CMD:
			retval = processNetworkAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processNetworkDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processNetworkUpdate( GuiReq );
		break;

		case GUI_DOWN_CMD:
			retval = processNetworkStatusUpdate( GuiReq, 1 );
		break;

		case GUI_UP_CMD:
			retval = processNetworkStatusUpdate( GuiReq, 2 );
		break;

		case GUI_EXCHANGE_CMD:
			retval = processNetworkCommandRequest( GuiReq, EZLINK_NTWK_KEYXHG );
		break;

		case GUI_SIGNON_CMD:
			retval = processNetworkCommandRequest( GuiReq, EZLINK_NTWK_SIGNON );
		break;

		case GUI_SIGNOFF_CMD:
			retval = processNetworkCommandRequest( GuiReq, EZLINK_NTWK_SIGNOFF );
		break;

		case GUI_LOGON_CMD:
			retval = processNetworkCommandRequest( GuiReq, EZLINK_NTWK_LOGON );
		break;

		case GUI_LOGOFF_CMD:
			retval = processNetworkCommandRequest( GuiReq, EZLINK_NTWK_LOGOFF );
		break;

		default:
			dptr->trace( "Invalid Network..GUI Command Received..." );
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

