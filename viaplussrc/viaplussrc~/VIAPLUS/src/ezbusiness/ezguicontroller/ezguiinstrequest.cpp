#include <ezbusiness/ezguicontroller.h>

int EzGUIInstRequest :: initGUIInstRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initInstProfile( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing InstProfileUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIInstRequest :: processInstAdd( const char *GuiReq )
{
	struct EzInstProfileMemory instprofile_rec;
	char InstId[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Inst Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_INSTID_NULL );
		return -1;
	}

	dptr->trace( "Processing Inst Add Request for InstId[%s]", InstId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &instprofile_rec, 0, sizeof( struct EzInstProfileMemory ) );
	retval = dbutil_ptr->readEzInstProfile( InstId, &instprofile_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading InstId[%s] from EzInstProfile Table....SqlErr[%05d]", InstId,retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_SEARCH_TABLE );
		return -1;
	}

	if( addInstProfile( InstId, instprofile_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding InstId[%s] in InstMemory...", InstId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIInstRequest :: processInstUpdate( const char *GuiReq )
{
	struct EzInstProfileMemory instprofile_rec;
	char InstId[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Inst Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_INSTID_NULL );
		return -1;
	}

	dptr->trace( "Processing Inst Update Request for InstId[%s]....", InstId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &instprofile_rec, 0, sizeof( struct EzInstProfileMemory ) );
	retval = dbutil_ptr->readEzInstProfile( InstId, &instprofile_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading InstId[%s] from EzInstProfile Table....SqlErr[%05d]", InstId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_SEARCH_TABLE );
		return -1;
	}

	if( updateInstProfile( InstId, instprofile_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in updating InstId[%s] in InstMemory...", InstId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIInstRequest :: processInstDelete( const char *GuiReq )
{
	struct EzInstProfileMemory branchprofile_rec;
	char InstId[ 13 ], Inst[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Inst Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_INSTID_NULL );
		return -1;
	}

	dptr->trace( "Processing Inst Delete Request for InstId[%s]", InstId );

	if( deleteInstProfile( InstId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting InstId[%s] in InstMemory...", InstId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIInstRequest :: processInstRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing InstRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Inst request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Inst request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_INST_COMMANDTYPE );
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
			retval = processInstAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processInstDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processInstUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Inst..GUI Command Received..." );
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



