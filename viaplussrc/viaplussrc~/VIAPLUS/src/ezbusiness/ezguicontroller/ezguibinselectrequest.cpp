#include <ezbusiness/ezguicontroller.h>

int EzGUIBINSelectRequest :: initGUIBINSelectRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initEzBINSelectUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing BINSelectUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIBINSelectRequest :: processBINSelectAdd( const char *GuiReq )
{
	struct EzBINSelectMemory binselect_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process BINSelect Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing BINSelect Add Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &binselect_rec, 0, sizeof( struct EzBINSelectMemory ) );
	retval = dbutil_ptr->readEzBINSelect( RecordId, &binselect_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzBINSelect Table....SqlErr[%05d]", RecordId,retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_SEARCH_TABLE );
		return -1;
	}

	if( addBINSelect( RecordId, binselect_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding RecordId[%s] in BINSelectMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBINSelectRequest :: processBINSelectUpdate( const char *GuiReq )
{
	struct EzBINSelectMemory binselect_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process BINSelect Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing BINSelect Update Request for RecordId[%s]....", RecordId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &binselect_rec, 0, sizeof( struct EzBINSelectMemory ) );
	retval = dbutil_ptr->readEzBINSelect( RecordId, &binselect_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzBINSelect Table....SqlErr[%05d]", RecordId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_SEARCH_TABLE );
		return -1;
	}

	if( updateBINSelect( RecordId, binselect_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in updating RecordId[%s] in BINSelectMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBINSelectRequest :: processBINSelectDelete( const char *GuiReq )
{
	struct EzBINSelectMemory branchprofile_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process BINSelect Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing BINSelect Delete Request for RecordId[%s]", RecordId );

	if( deleteBINSelect( RecordId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting RecordId[%s] in BINSelectMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBINSelectRequest :: processBINSelectRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing BINSelectRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process BINSelect request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process BINSelect request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INSTSELECT_COMMANDTYPE );
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
			retval = processBINSelectAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processBINSelectDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processBINSelectUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid BINSelect..GUI Command Received..." );
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
