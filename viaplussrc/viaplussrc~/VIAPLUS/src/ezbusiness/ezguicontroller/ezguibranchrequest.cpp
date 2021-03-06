#include <ezbusiness/ezguicontroller.h>

int EzGUIBranchRequest :: initGUIBranchRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initBranchProfile( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing BranchProfileUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIBranchRequest :: processBranchAdd( const char *GuiReq )
{
	struct EzBranchProfileMemory branchprofile_rec;
	char InstId[ 13 ], BranchId[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Branch Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_INST_NULL );
		return -1;
	}

	memset( BranchId, 0, sizeof( BranchId ) );
	tokenutil_ptr->getToken( GuiReq, BranchId, GUI_GS, 4 );

	if( !strlen( BranchId ) )
	{
		dptr->trace( "BranchId is NULL...Cannot Process Branch Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_BRANCHID_NULL );
		return -1;
	}

	dptr->trace( "Processing Branch Add Request for InstId[%s] BranchId[%s]...", InstId, BranchId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &branchprofile_rec, 0, sizeof( struct EzBranchProfileMemory ) );
	retval = dbutil_ptr->readEzBranchProfile( InstId, BranchId, &branchprofile_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading InstId[%s] BranchCode[%s] from EzBranchProfile Table....SqlErr[%05d]", InstId, BranchId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_SEARCH_TABLE );
		return -1;
	}

	if( addBranchProfile( branchprofile_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding InstId[%s] BranchId[%s] in BranchMemory...", InstId, BranchId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBranchRequest :: processBranchUpdate( const char *GuiReq )
{
	struct EzBranchProfileMemory branchprofile_rec;
	char InstId[ 13 ], BranchId[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Branch Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_INST_NULL );
		return -1;
	}

	memset( BranchId, 0, sizeof( BranchId ) );
	tokenutil_ptr->getToken( GuiReq, BranchId, GUI_GS, 4 );

	if( !strlen( BranchId ) )
	{
		dptr->trace( "BranchId is NULL...Cannot Process Branch Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_BRANCHID_NULL );
		return -1;
	}

	dptr->trace( "Processing Branch Update Request for InstId[%s] BranchId[%s]...", InstId, BranchId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &branchprofile_rec, 0, sizeof( struct EzBranchProfileMemory ) );
	retval = dbutil_ptr->readEzBranchProfile( InstId, BranchId, &branchprofile_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading InstId[%s] BranchCode[%s] from EzBranchProfile Table....SqlErr[%05d]", InstId, BranchId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_SEARCH_TABLE );
		return -1;
	}

	if( updateBranchProfile( branchprofile_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in updating InstId[%s] BranchId[%s] in BranchMemory...", InstId, BranchId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBranchRequest :: processBranchDelete( const char *GuiReq )
{
	struct EzBranchProfileMemory branchprofile_rec;
	char InstId[ 13 ], BranchId[ 13 ];
	int retval;

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Branch Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_INST_NULL );
		return -1;
	}

	memset( BranchId, 0, sizeof( BranchId ) );
	tokenutil_ptr->getToken( GuiReq, BranchId, GUI_GS, 4 );

	if( !strlen( BranchId ) )
	{
		dptr->trace( "BranchId is NULL...Cannot Process Branch Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_BRANCHID_NULL );
		return -1;
	}

	dptr->trace( "Processing Branch Delete Request for InstId[%s] BranchId[%s]...", InstId, BranchId );

	if( deleteBranchProfile( InstId, BranchId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting InstId[%s] BranchId[%s] in BranchMemory...", InstId, BranchId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIBranchRequest :: processBranchRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing BranchRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Branch request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Branch request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_BRANCH_COMMANDTYPE );
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
			retval = processBranchAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processBranchDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processBranchUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Branch..GUI Command Received..." );
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

