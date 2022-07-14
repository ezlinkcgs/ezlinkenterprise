#include <ezbusiness/ezguicontroller.h>

int EzGUIBINRequest :: initGUIBINRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initBINProfile( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing BINProfileUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIBINRequest :: processBINAdd( const char *GuiReq )
{
	struct EzBINProfileMemory binprofile_rec;
	char InstId[ 13 ], BIN[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process BIN Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_INST_NULL );
		return -1;
	}

	memset( BIN, 0, sizeof( BIN ) );
	tokenutil_ptr->getToken( GuiReq, BIN, GUI_GS, 4 );

	if( !strlen( BIN ) )
	{
		dptr->trace( "BIN is NULL...Cannot Process BIN Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_BINID_NULL );
		return -1;
	}

	dptr->trace( "Processing BIN Add Request for InstId[%s] BIN[%s]...", InstId, BIN );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &binprofile_rec, 0, sizeof( struct EzBINProfileMemory ) );
	retval = dbutil_ptr->readEzBINProfile( InstId, BIN, &binprofile_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading InstId[%s] BINCode[%s] from EzBINProfile Table....SqlErr[%05d]", InstId, BIN, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_SEARCH_TABLE );
		return -1;
	}

	if( addBINProfile( binprofile_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding InstId[%s] BIN[%s] in BINMemory...", InstId, BIN );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_ADD_MEMORY );
		return -1;
	}

	return 1;
}

int EzGUIBINRequest :: processBINUpdate( const char *GuiReq )
{
	struct EzBINProfileMemory binprofile_rec;
	char InstId[ 13 ], BIN[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process BIN Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_INST_NULL );
		return -1;
	}

	memset( BIN, 0, sizeof( BIN ) );
	tokenutil_ptr->getToken( GuiReq, BIN, GUI_GS, 4 );

	if( !strlen( BIN ) )
	{
		dptr->trace( "BIN is NULL...Cannot Process BIN Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_BINID_NULL );
		return -1;
	}

	dptr->trace( "Processing BIN Update Request for InstId[%s] BIN[%s]...", InstId, BIN );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &binprofile_rec, 0, sizeof( struct EzBINProfileMemory ) );
	retval = dbutil_ptr->readEzBINProfile( InstId, BIN, &binprofile_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading InstId[%s] BINCode[%s] from EzBINProfile Table....SqlErr[%05d]", InstId, BIN, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_SEARCH_TABLE );
		return -1;
	}

	if( updateBINProfile( binprofile_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in updating InstId[%s] BIN[%s] in BINMemory...", InstId, BIN );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBINRequest :: processBINDelete( const char *GuiReq )
{
	struct EzBINProfileMemory binprofile_rec;
	char InstId[ 13 ], BIN[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process BIN Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_INST_NULL );
		return -1;
	}

	memset( BIN, 0, sizeof( BIN ) );
	tokenutil_ptr->getToken( GuiReq, BIN, GUI_GS, 4 );

	if( !strlen( BIN ) )
	{
		dptr->trace( "BIN is NULL...Cannot Process BIN Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_BINID_NULL );
		return -1;
	}

	dptr->trace( "Processing BIN Delete Request for InstId[%s] BIN[%s]...", InstId, BIN );

	if( deleteBINProfile( InstId, BIN ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting InstId[%s] BIN[%s] in BINMemory...", InstId, BIN );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBINRequest :: processBINRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing BINRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process BIN request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process BIN request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BIN_COMMANDTYPE );
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
			retval = processBINAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processBINDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processBINUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid BIN..GUI Command Received..." );
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
