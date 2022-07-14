#include <ezbusiness/ezguicontroller.h>

int EzGUIBusDayRequest :: initGUIBusDayRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initBusDayUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing BusDayUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIBusDayRequest :: processBusDayAdd( const char *GuiReq )
{
	struct EzNetworkBusDay eznetworkbusday_rec;
	struct EzBusDayTable busdaymem_rec;
	int retval;
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process NetworkBusDay Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkBusDay Add Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &eznetworkbusday_rec, 0, sizeof( struct EzNetworkBusDay ) );
	retval = dbutil_ptr->readEzNetworkBusDay( NetworkId, &eznetworkbusday_rec );
	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading NetworkId[%s] from EzNetworkBusDay Table...SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKBUSDAY_TABLE );
		return -1;
	}

	memset( &busdaymem_rec, 0, sizeof( struct EzBusDayTable ) );
	strcpy( busdaymem_rec.NetworkId, eznetworkbusday_rec.NetworkId );
	busdaymem_rec.CutOverUseFlag = eznetworkbusday_rec.CutOverUseFlag;
	busdaymem_rec.CutOverDate = eznetworkbusday_rec.CutOverDate;
	busdaymem_rec.CutOverTime = eznetworkbusday_rec.CutOverTime;

	if( addNetworkBusDayMemory( busdaymem_rec ) < 0 )
	{
		dptr->trace( "Error in adding NetworkId[%s] in NetworkBusDayMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ADD_NETWORKBUSDAY_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBusDayRequest :: processBusDayDelete( const char *GuiReq )
{
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process NetworkBusDay Remove Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}
	dptr->trace( "Processing NetworkBusDay Remove Request for NetworkId[%s]...", NetworkId );

	if( deleteNetworkBusDayMemory( NetworkId ) < 0 )
	{
		dptr->trace( "Error in removing NetworkId[%s] from NetworkMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DELETE_NETWORKBUSDAY_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBusDayRequest :: processBusDayUpdate( const char *GuiReq )
{
	struct EzNetworkBusDay eznetworkbusday_rec;
	struct EzBusDayTable busdaymem_rec;
	int retval;
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process NetworkBusDay Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkBusDay Update Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &eznetworkbusday_rec, 0, sizeof( struct EzNetworkBusDay ) );
	retval = dbutil_ptr->readEzNetworkBusDay( NetworkId, &eznetworkbusday_rec );
	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}


	if( retval != 0 )
	{
		dptr->trace( "Error in Reading NetworkId[%s] from EzNetworkBusDay Table...SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKBUSDAY_TABLE );
		return -1;
	}

	memset( &busdaymem_rec, 0, sizeof( struct EzBusDayTable ) );
	strcpy( busdaymem_rec.NetworkId, eznetworkbusday_rec.NetworkId );
	busdaymem_rec.CutOverUseFlag = eznetworkbusday_rec.CutOverUseFlag;
	busdaymem_rec.CutOverDate = eznetworkbusday_rec.CutOverDate;
	busdaymem_rec.CutOverTime = eznetworkbusday_rec.CutOverTime;

	if( updateNetworkBusDayMemory( busdaymem_rec ) < 0 )
	{
		dptr->trace( "Error in Updating NetworkId[%s] in NetworkBusDayMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_UPDATE_NETWORKBUSDAY_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBusDayRequest :: processBusDayRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing BusDayRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Network request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKBUSDAY_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Network request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKBUSDAY_COMMANDTYPE );
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
		case GUI_ADD_CMD:
			retval = processBusDayAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processBusDayDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processBusDayUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid NetworkBusDay..GUI Command Received..." );
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

