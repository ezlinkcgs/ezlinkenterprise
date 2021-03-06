#include <ezbusiness/ezguicontroller.h>

int EzGUIFITRequest :: initGUIFITRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initATMMemoryUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ATM Memory Util....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}

	if( LoadFITMemory() < 0 )
	{
		dptr->trace( "Error in Loading ATM FIT Memory....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIFITRequest :: processFITAdd( const char *GuiReq )
{
	struct AtmFit atmfit_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process FIT Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing FIT Add Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &atmfit_rec, 0, sizeof( struct AtmFit ) );
	retval = dbutil_ptr->readEzAtmFit( RecordId, &atmfit_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzAtmFIT Table....SqlErr[%05d]", RecordId,retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_SEARCH_TABLE );
		return -1;
	}

	if( addFITMemory( atmfit_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding RecordId[%s] in FITMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIFITRequest :: processFITUpdate( const char *GuiReq )
{
	struct AtmFit atmfit_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process FIT Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing FIT Update Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &atmfit_rec, 0, sizeof( struct AtmFit ) );
	retval = dbutil_ptr->readEzAtmFit( RecordId, &atmfit_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading RecordId[%s] from EzAtmFIT Table....SqlErr[%05d]", RecordId,retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_SEARCH_TABLE );
		return -1;
	}

	if( updateFITMemory( atmfit_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Updating RecordId[%s] in FITMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIFITRequest :: processFITDelete( const char *GuiReq )
{
	struct AtmFit atmfit_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process FIT Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing FIT Delete Request for RecordId[%s]", RecordId );

	if( deleteFITMemory( RecordId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting RecordId[%s] in FITMemory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIFITRequest :: processFITRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing FITRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process FIT request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process FIT request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_COMMANDTYPE );
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
			retval = processFITAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processFITDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processFITUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid FIT..GUI Command Received..." );
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
