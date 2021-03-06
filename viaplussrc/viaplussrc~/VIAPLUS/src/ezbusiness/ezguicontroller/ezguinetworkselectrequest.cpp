#include <ezbusiness/ezguicontroller.h>

int EzGUINetworkSelectRequest :: initGUINetworkSelectRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initEzNetworkSelectUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing NetworkSelectUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUINetworkSelectRequest :: processNetworkSelectAdd( const char *GuiReq )
{
	struct EzNetworkSelectMemory networkselect_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process NetworkSelect Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkSelect Add Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkselect_rec, 0, sizeof( struct EzNetworkSelectMemory ) );
	retval = dbutil_ptr->readEzNetworkSelect( RecordId, &networkselect_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzNetworkSelect Table....SqlErr[%05d]", RecordId,retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_SEARCH_TABLE );
		return -1;
	}

	if( addNetworkSelect( RecordId, networkselect_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding RecordId[%s] in NetworkSelectMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUINetworkSelectRequest :: processNetworkSelectUpdate( const char *GuiReq )
{
	struct EzNetworkSelectMemory networkselect_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process NetworkSelect Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkSelect Update Request for RecordId[%s]....", RecordId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkselect_rec, 0, sizeof( struct EzNetworkSelectMemory ) );
	retval = dbutil_ptr->readEzNetworkSelect( RecordId, &networkselect_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzNetworkSelect Table....SqlErr[%05d]", RecordId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_SEARCH_TABLE );
		return -1;
	}

	if( updateNetworkSelect( RecordId, networkselect_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in updating RecordId[%s] in NetworkSelectMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUINetworkSelectRequest :: processNetworkSelectDelete( const char *GuiReq )
{
	struct EzNetworkSelectMemory branchprofile_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process NetworkSelect Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkSelect Delete Request for RecordId[%s]", RecordId );

	if( deleteNetworkSelect( RecordId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting RecordId[%s] in NetworkSelectMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUINetworkSelectRequest :: processNetworkSelectRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing NetworkSelectRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process NetworkSelect request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process NetworkSelect request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKSELECT_COMMANDTYPE );
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
			retval = processNetworkSelectAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processNetworkSelectDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processNetworkSelectUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid NetworkSelect..GUI Command Received..." );
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
			sprintf( GuiResp, "%s%c%d", GuiReq, GUI_ES, RespFlag );
		}

		if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
	}
	return retval;
}

