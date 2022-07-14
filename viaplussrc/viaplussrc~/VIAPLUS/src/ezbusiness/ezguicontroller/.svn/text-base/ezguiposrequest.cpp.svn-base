#include <ezbusiness/ezguicontroller.h>

int EzGUIPOSRequest :: initGUIPOSRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzDBUtil *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initPOSDriverUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing POS Driver Util....." );
		return -1;
	}

	if( LoadPOSMCCInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSMCCInfo...." );
		return -1;
	}

	if( LoadPOSMerchantTypeInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSMerchantTypeInfo...." );
		return -1;
	}

	if( LoadPOSMerchantInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSMerchantInfo...." );
		return -1;
	}

	if( LoadPOSTerminalTypeInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSTerminalTypeInfo...." );
		return -1;
	}

	if( LoadPOSTerminalInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSTerminalInfo...." );
		return -1;
	}

	if( LoadPOSStoreInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSStoreInfo...." );
		return -1;
	}

	if( LoadPOSTxnInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSTxnInfo...." );
		return -1;
	}

	if( LoadPOSRespCodeInfo() < 0 )
	{
		dptr->trace( "Error in Loading POSRespCodeInfo...." );
		return -1;
	}
	return 1;
}

int EzGUIPOSRequest :: processTerminalAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], TerminalId[ POS_TERMINALID_SIZE + 1  ];
	struct EzPOSTerminalInfo posterminalinfo_rec;
	int retval;

	dptr->trace( "Processing Terminal Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Terminal Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( TerminalId, 0, sizeof( TerminalId ) );
	tokenutil_ptr->getToken( GuiReq, TerminalId, GUI_GS, 4 );
	if( strlen( TerminalId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALID_NULL );
		dptr->trace( "TerminalId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posterminalinfo_rec, 0, sizeof( struct EzPOSTerminalInfo ) );
	strcpy( posterminalinfo_rec.POSId, TerminalId );
	retval = readEzPOSTerminalInfo( TerminalId, &posterminalinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading TerminalId[%s] from EzPOSTerminalInfo....OraErr[%05d]", TerminalId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINAL_SEARCH_TABLE );
		return -1;
	}

	if( addPOSTerminalInfo( posterminalinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding TerminalId[%s] in POSTerminalInfo Memory", TerminalId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINAL_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added TerminalId[%s] in POSTerminalInfo Successfully", TerminalId );
	return 1;
}

int EzGUIPOSRequest :: processTerminalUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], TerminalId[ POS_TERMINALID_SIZE + 1  ];
	struct EzPOSTerminalInfo posterminalinfo_rec;
	int retval;

	dptr->trace( "Processing Terminal Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Terminal Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( TerminalId, 0, sizeof( TerminalId ) );
	tokenutil_ptr->getToken( GuiReq, TerminalId, GUI_GS, 4 );
	if( strlen( TerminalId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALID_NULL );
		dptr->trace( "TerminalId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posterminalinfo_rec, 0, sizeof( struct EzPOSTerminalInfo ) );
	strcpy( posterminalinfo_rec.POSId, TerminalId );
	retval = readEzPOSTerminalInfo( TerminalId, &posterminalinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading TerminalId[%s] from EzPOSTerminalInfo....OraErr[%05d]", TerminalId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINAL_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSTerminalInfo( posterminalinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating TerminalId[%s] in POSTerminalInfo Memory", TerminalId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINAL_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Updated TerminalId[%s] in POSTerminalInfo Successfully", TerminalId );
	return 1;
}

int EzGUIPOSRequest :: processTerminalDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], TerminalId[ POS_TERMINALID_SIZE + 1  ];
	int retval;

	dptr->trace( "Processing Terminal Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Terminal Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( TerminalId, 0, sizeof( TerminalId ) );
	tokenutil_ptr->getToken( GuiReq, TerminalId, GUI_GS, 4 );
	if( strlen( TerminalId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALID_NULL );
		dptr->trace( "TerminalId is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSTerminalInfo( TerminalId ) < 0 )
	{
		dptr->trace( "Error in Deleting TerminalId[%s] From POSTerminalInfo Memory", TerminalId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINAL_DELETE_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted TerminalId[%s] From POSTerminalInfo Successfully", TerminalId );
	return 1;
}

int EzGUIPOSRequest :: processTerminalTypeAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], TerminalType[ POS_TERMINALTYPE_SIZE + 1  ];
	struct EzPOSTerminalTypeInfo posterminaltypeinfo_rec;
	int retval;

	dptr->trace( "Processing TerminalType Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for TerminalType Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TerminalType, 0, sizeof( TerminalType ) );
	tokenutil_ptr->getToken( GuiReq, TerminalType, GUI_GS, 3 );
	if( strlen( TerminalType ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_NULL );
		dptr->trace( "TerminalType is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posterminaltypeinfo_rec, 0, sizeof( struct EzPOSTerminalTypeInfo ) );
	strcpy( posterminaltypeinfo_rec.TerminalType, TerminalType );
	retval = readEzPOSTerminalTypeInfo( TerminalType, &posterminaltypeinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading TerminalTypeId[%s] from EzPOSTerminalTypeInfo....OraErr[%05d]", TerminalType, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_SEARCH_TABLE );
		return -1;
	}

	if( addPOSTerminalTypeInfo( posterminaltypeinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding TerminalType[%s] in POSTerminalTypeInfo Memory", TerminalType );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added TerminalType[%s] in POSTerminalTypeInfo Successfully", TerminalType );
	return 1;
}

int EzGUIPOSRequest :: processTerminalTypeUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], TerminalType[ POS_TERMINALTYPE_SIZE + 1  ];
	struct EzPOSTerminalTypeInfo posterminaltypeinfo_rec;
	int retval;

	dptr->trace( "Processing TerminalType Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for TerminalType Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TerminalType, 0, sizeof( TerminalType ) );
	tokenutil_ptr->getToken( GuiReq, TerminalType, GUI_GS, 3 );
	if( strlen( TerminalType ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_NULL );
		dptr->trace( "TerminalType is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posterminaltypeinfo_rec, 0, sizeof( struct EzPOSTerminalTypeInfo ) );
	strcpy( posterminaltypeinfo_rec.TerminalType, TerminalType );
	retval = readEzPOSTerminalTypeInfo( TerminalType, &posterminaltypeinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading TerminalTypeId[%s] from EzPOSTerminalTypeInfo....OraErr[%05d]", TerminalType, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSTerminalTypeInfo( posterminaltypeinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating TerminalType[%s] in POSTerminalTypeInfo Memory", TerminalType );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Updated TerminalType[%s] in POSTerminalTypeInfo Successfully", TerminalType );
	return 1;
}

int EzGUIPOSRequest :: processTerminalTypeDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], TerminalType[ POS_TERMINALTYPE_SIZE + 1  ];
	int retval;

	dptr->trace( "Processing TerminalType Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for TerminalType Delete Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TerminalType, 0, sizeof( TerminalType ) );
	tokenutil_ptr->getToken( GuiReq, TerminalType, GUI_GS, 3 );
	if( strlen( TerminalType ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_NULL );
		dptr->trace( "TerminalType is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSTerminalTypeInfo( TerminalType ) < 0 )
	{
		dptr->trace( "Error in Delete TerminalType[%s] From POSTerminalTypeInfo Memory", TerminalType );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TERMINALTYPE_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted TerminalType[%s] From POSTerminalTypeInfo Successfully", TerminalType );
	return 1;
}

int EzGUIPOSRequest :: processMerchantTypeAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], MerchantType[ POS_MERCHANTTYPE_SIZE + 1  ];
	struct EzPOSMerchantTypeInfo posmerchanttypeinfo_rec;
	int retval;

	dptr->trace( "Processing MerchantType Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for MerchantType Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( MerchantType, 0, sizeof( MerchantType ) );
	tokenutil_ptr->getToken( GuiReq, MerchantType, GUI_GS, 3 );
	if( strlen( MerchantType ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_NULL );
		dptr->trace( "MerchantType is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posmerchanttypeinfo_rec, 0, sizeof( struct EzPOSMerchantTypeInfo ) );
	strcpy( posmerchanttypeinfo_rec.MerchantType, MerchantType );
	retval = readEzPOSMerchantTypeInfo( MerchantType, &posmerchanttypeinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading MerchantTypeId[%s] from EzPOSMerchantTypeInfo....OraErr[%05d]", MerchantType, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_SEARCH_TABLE );
		return -1;
	}

	if( addPOSMerchantTypeInfo( posmerchanttypeinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding MerchantType[%s] in POSMerchantTypeInfo Memory", MerchantType );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added MerchantType[%s] in POSMerchantTypeInfo Successfully", MerchantType );
	return 1;
}

int EzGUIPOSRequest :: processMerchantTypeUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], MerchantType[ POS_MERCHANTTYPE_SIZE + 1  ];
	struct EzPOSMerchantTypeInfo posmerchanttypeinfo_rec;
	int retval;

	dptr->trace( "Processing MerchantType Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for MerchantType Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( MerchantType, 0, sizeof( MerchantType ) );
	tokenutil_ptr->getToken( GuiReq, MerchantType, GUI_GS, 3 );
	if( strlen( MerchantType ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_NULL );
		dptr->trace( "MerchantType is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posmerchanttypeinfo_rec, 0, sizeof( struct EzPOSMerchantTypeInfo ) );
	strcpy( posmerchanttypeinfo_rec.MerchantType, MerchantType );
	retval = readEzPOSMerchantTypeInfo( MerchantType, &posmerchanttypeinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading MerchantTypeId[%s] from EzPOSMerchantTypeInfo....OraErr[%05d]", MerchantType, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSMerchantTypeInfo( posmerchanttypeinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating MerchantType[%s] in POSMerchantTypeInfo Memory", MerchantType );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Updated MerchantType[%s] in POSMerchantTypeInfo Successfully", MerchantType );
	return 1;
}

int EzGUIPOSRequest :: processMerchantTypeDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], MerchantType[ POS_MERCHANTTYPE_SIZE + 1  ];
	int retval;

	dptr->trace( "Processing MerchantType Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for MerchantType Delete Request is Null...Cannot process Request" );
		return -1;
	}

	memset( MerchantType, 0, sizeof( MerchantType ) );
	tokenutil_ptr->getToken( GuiReq, MerchantType, GUI_GS, 3 );
	if( strlen( MerchantType ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_NULL );
		dptr->trace( "MerchantType is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSMerchantTypeInfo( MerchantType ) < 0 )
	{
		dptr->trace( "Error in Delete MerchantType[%s] From POSMerchantTypeInfo Memory", MerchantType );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTTYPE_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted MerchantType[%s] From POSMerchantTypeInfo Successfully", MerchantType );
	return 1;
}

int EzGUIPOSRequest :: processMerchantAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], MerchantId[ POS_MERCHANTID_SIZE + 1  ];
	struct EzPOSMerchantInfo posmerchantinfo_rec;
	int retval;

	dptr->trace( "Processing Merchant Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Merchant Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( MerchantId, 0, sizeof( MerchantId ) );
	tokenutil_ptr->getToken( GuiReq, MerchantId, GUI_GS, 4 );
	if( strlen( MerchantId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTID_NULL );
		dptr->trace( "MerchantId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posmerchantinfo_rec, 0, sizeof( struct EzPOSMerchantInfo ) );
	strcpy( posmerchantinfo_rec.MerchantId, MerchantId );
	retval = readEzPOSMerchantInfo( MerchantId, &posmerchantinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading MerchantId[%s] from EzPOSMerchantInfo....OraErr[%05d]", MerchantId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANT_SEARCH_TABLE );
		return -1;
	}

	if( addPOSMerchantInfo( posmerchantinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding MerchantId[%s] in POSMerchantInfo Memory", MerchantId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANT_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added MerchantId[%s] in POSMerchantInfo Successfully", MerchantId );
	return 1;
}

int EzGUIPOSRequest :: processMerchantUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], MerchantId[ POS_MERCHANTID_SIZE + 1  ];
	struct EzPOSMerchantInfo posmerchantinfo_rec;
	int retval;

	dptr->trace( "Processing Merchant Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Merchant Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( MerchantId, 0, sizeof( MerchantId ) );
	tokenutil_ptr->getToken( GuiReq, MerchantId, GUI_GS, 4 );
	if( strlen( MerchantId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTID_NULL );
		dptr->trace( "MerchantId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posmerchantinfo_rec, 0, sizeof( struct EzPOSMerchantInfo ) );
	strcpy( posmerchantinfo_rec.MerchantId, MerchantId );
	retval = readEzPOSMerchantInfo( MerchantId, &posmerchantinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading MerchantId[%s] from EzPOSMerchantInfo....OraErr[%05d]", MerchantId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANT_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSMerchantInfo( posmerchantinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating MerchantId[%s] in POSMerchantInfo Memory", MerchantId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANT_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Updated MerchantId[%s] in POSMerchantInfo Successfully", MerchantId );
	return 1;
}

int EzGUIPOSRequest :: processMerchantDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], MerchantId[ POS_MERCHANTID_SIZE + 1  ];
	int retval;

	dptr->trace( "Processing Merchant Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Merchant Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( MerchantId, 0, sizeof( MerchantId ) );
	tokenutil_ptr->getToken( GuiReq, MerchantId, GUI_GS, 4 );
	if( strlen( MerchantId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANTID_NULL );
		dptr->trace( "MerchantId is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSMerchantInfo( MerchantId ) < 0 )
	{
		dptr->trace( "Error in Deleting MerchantId[%s] From POSMerchantInfo Memory", MerchantId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MERCHANT_DELETE_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted MerchantId[%s] From POSMerchantInfo Successfully", MerchantId );
	return 1;
}

int EzGUIPOSRequest :: processStoreAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], StoreId[ POS_STOREID_SIZE + 1  ];
	struct EzPOSStoreInfo posstoreinfo_rec;
	int retval;

	dptr->trace( "Processing Store Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Store Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( StoreId, 0, sizeof( StoreId ) );
	tokenutil_ptr->getToken( GuiReq, StoreId, GUI_GS, 4 );
	if( strlen( StoreId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STOREID_NULL );
		dptr->trace( "StoreId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posstoreinfo_rec, 0, sizeof( struct EzPOSStoreInfo ) );
	strcpy( posstoreinfo_rec.StoreId, StoreId );
	retval = readEzPOSStoreInfo( StoreId, &posstoreinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading StoreId[%s] from EzPOSStoreInfo....OraErr[%05d]", StoreId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STORE_SEARCH_TABLE );
		return -1;
	}

	if( addPOSStoreInfo( posstoreinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding StoreId[%s] in POSStoreInfo Memory", StoreId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STORE_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added StoreId[%s] in POSStoreInfo Successfully", StoreId );
	return 1;
}

int EzGUIPOSRequest :: processStoreUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], StoreId[ POS_STOREID_SIZE + 1  ];
	struct EzPOSStoreInfo posstoreinfo_rec;
	int retval;

	dptr->trace( "Processing Store Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Store Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( StoreId, 0, sizeof( StoreId ) );
	tokenutil_ptr->getToken( GuiReq, StoreId, GUI_GS, 4 );
	if( strlen( StoreId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STOREID_NULL );
		dptr->trace( "StoreId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posstoreinfo_rec, 0, sizeof( struct EzPOSStoreInfo ) );
	strcpy( posstoreinfo_rec.StoreId, StoreId );
	retval = readEzPOSStoreInfo( StoreId, &posstoreinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading StoreId[%s] from EzPOSStoreInfo....OraErr[%05d]", StoreId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STORE_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSStoreInfo( posstoreinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating StoreId[%s] in POSStoreInfo Memory", StoreId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STORE_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Updated StoreId[%s] in POSStoreInfo Successfully", StoreId );
	return 1;
}

int EzGUIPOSRequest :: processStoreDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], StoreId[ POS_STOREID_SIZE + 1  ];
	int retval;

	dptr->trace( "Processing Store Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for Store Delete Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( StoreId, 0, sizeof( StoreId ) );
	tokenutil_ptr->getToken( GuiReq, StoreId, GUI_GS, 4 );
	if( strlen( StoreId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STOREID_NULL );
		dptr->trace( "StoreId is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSStoreInfo( StoreId ) < 0 )
	{
		dptr->trace( "Error in Deleting StoreId[%s] From POSStoreInfo Memory", StoreId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_STORE_DELETE_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted StoreId[%s] From POSStoreInfo Successfully", StoreId );
	return 1;
}


int EzGUIPOSRequest :: processMCCAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ];
	int MCC;
	struct EzPOSMCCInfo posmccinfo_rec;
	int retval;

	dptr->trace( "Processing MCC Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for MCC Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 3 );
	if( strlen( TempStr ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_NULL );
		dptr->trace( "MCC is NULL...Cannot Process Request...");
		return -1;
	}

	MCC = atoi( TempStr );

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posmccinfo_rec, 0, sizeof( struct EzPOSMCCInfo ) );
	posmccinfo_rec.MCC = MCC;
	retval = readEzPOSMCCInfo( MCC, &posmccinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading MCC[%d] from EzPOSMCCInfo....OraErr[%05d]", MCC, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_SEARCH_TABLE );
		return -1;
	}
	if( addPOSMCCInfo( posmccinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding MCC[%d] in POSMCCInfo Memory", MCC );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added MCC[%d] in POSMCCInfo Successfully", MCC );
	return 1;
}

int EzGUIPOSRequest :: processMCCUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ];
	int MCC;
	struct EzPOSMCCInfo posmccinfo_rec;
	int retval;

	dptr->trace( "Processing MCC Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for MCC Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 3 );
	if( strlen( TempStr ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_NULL );
		dptr->trace( "MCC is NULL...Cannot Process Request...");
		return -1;
	}

	MCC = atoi( TempStr );

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posmccinfo_rec, 0, sizeof( struct EzPOSMCCInfo ) );
	posmccinfo_rec.MCC = MCC;
	retval = readEzPOSMCCInfo( MCC, &posmccinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading MCC[%d] from EzPOSMCCInfo....OraErr[%05d]", MCC, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSMCCInfo( posmccinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating MCC[%d] in POSMCCInfo Memory", MCC );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_UPDATE_MEMORY );
		return -1;
	}
	dptr->trace( "Updated MCC[%d] in POSMCCInfo Successfully", MCC );
	return 1;
}

int EzGUIPOSRequest :: processMCCDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ];
	int MCC;
	int retval;

	dptr->trace( "Processing MCC Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for MCC Delete Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 3 );
	if( strlen( TempStr ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_NULL );
		dptr->trace( "MCC is NULL...Cannot Process Request...");
		return -1;
	}

	MCC = atoi( TempStr );
	if( deletePOSMCCInfo( MCC ) < 0 )
	{
		dptr->trace( "Error in Deleting MCC[%d] From POSMCCInfo Memory", MCC );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MCC_DELETE_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted MCC[%d] From POSMCCInfo Successfully", MCC );
	return 1;
}

int EzGUIPOSRequest :: processTxnInfoAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], TxnGroupId[ POS_TXNGROUPID_SIZE + 1  ];
	struct EzPOSTxnInfo postxninfo_rec;
	int retval;

	dptr->trace( "Processing TxnInfo Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for TxnInfo Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TxnGroupId, 0, sizeof( TxnGroupId ) );
	tokenutil_ptr->getToken( GuiReq, TxnGroupId, GUI_GS, 3 );
	if( strlen( TxnGroupId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_NULL );
		dptr->trace( "TxnGroupId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &postxninfo_rec, 0, sizeof( struct EzPOSTxnInfo ) );
	strcpy( postxninfo_rec.TxnCodeGroupId, TxnGroupId );
	retval = readEzPOSTxnInfo( TxnGroupId, &postxninfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading TxnGroupId[%s] from EzPOSTxnInfo....OraErr[%05d]", TxnGroupId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_SEARCH_TABLE );
		return -1;
	}

	if( addPOSTxnInfo( postxninfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding TxnGroupId[%s] in POSTxnInfo Memory", TxnGroupId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added TxnGroupId[%s] in POSTxnInfo Successfully", TxnGroupId );
	return 1;
}

int EzGUIPOSRequest :: processTxnInfoUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], TxnGroupId[ POS_TXNGROUPID_SIZE + 1  ];
	struct EzPOSTxnInfo postxninfo_rec;
	int retval;

	dptr->trace( "Processing TxnInfo Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for TxnInfo Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TxnGroupId, 0, sizeof( TxnGroupId ) );
	tokenutil_ptr->getToken( GuiReq, TxnGroupId, GUI_GS, 3 );
	if( strlen( TxnGroupId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_NULL );
		dptr->trace( "TxnGroupId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &postxninfo_rec, 0, sizeof( struct EzPOSTxnInfo ) );
	strcpy( postxninfo_rec.TxnCodeGroupId, TxnGroupId );
	retval = readEzPOSTxnInfo( TxnGroupId, &postxninfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading TxnGroupId[%s] from EzPOSTxnInfo....OraErr[%05d]", TxnGroupId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_SEARCH_TABLE );
		return -1;
	}

	if( updatePOSTxnInfo( postxninfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating TxnGroupId[%s] in POSTxnInfo Memory", TxnGroupId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Updated TxnGroupId[%s] in POSTxnInfo Successfully", TxnGroupId );
	return 1;
}

int EzGUIPOSRequest :: processTxnInfoDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], TxnGroupId[ POS_TXNGROUPID_SIZE + 1  ];
	struct EzPOSTxnInfo postxninfo_rec;
	int retval;

	dptr->trace( "Processing TxnInfo Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for TxnInfo Delete Request is Null...Cannot process Request" );
		return -1;
	}

	memset( TxnGroupId, 0, sizeof( TxnGroupId ) );
	tokenutil_ptr->getToken( GuiReq, TxnGroupId, GUI_GS, 3 );
	if( strlen( TxnGroupId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_NULL );
		dptr->trace( "TxnGroupId is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSTxnInfo( TxnGroupId ) < 0 )
	{
		dptr->trace( "Error in Deleting TxnGroupId[%s] From POSTxnInfo Memory", TxnGroupId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted TxnGroupId[%s] From POSTxnInfo Successfully", TxnGroupId );
	return 1;
}

int EzGUIPOSRequest :: processRespCodeInfoAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], RecordId[ POS_RECORDID_SIZE + 1  ];
	struct EzPOSRespCodeInfo posrespcodeinfo_rec;
	int retval;

	dptr->trace( "Processing RespCodeInfo Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for RespCodeInfo Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );
	if( strlen( RecordId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_NULL );
		dptr->trace( "RecordId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posrespcodeinfo_rec, 0, sizeof( struct EzPOSRespCodeInfo ) );
	strcpy( posrespcodeinfo_rec.RespCodeGroupId, RecordId );
	retval = readEzPOSRespCodeInfo( RecordId, &posrespcodeinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading RecordId[%s] from EzPOSRespCodeInfo....OraErr[%05d]", RecordId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_SEARCH_TABLE );
		return -1;
	}

	if( addPOSRespCodeInfo( posrespcodeinfo_rec ) < 0 )
	{
		dptr->trace( "Error in adding RecordId[%s] in POSRespCodeInfo Memory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Added RecordId[%s] in POSRespCodeInfo Successfully", RecordId );
	return 1;
}

int EzGUIPOSRequest :: processRespCodeInfoUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], RecordId[ POS_RECORDID_SIZE + 1  ];
	struct EzPOSRespCodeInfo posrespcodeinfo_rec;
	int retval;

	dptr->trace( "Processing RespCodeInfo Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for RespCodeInfo Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );
	if( strlen( RecordId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_NULL );
		dptr->trace( "RecordId is NULL...Cannot Process Request...");
		return -1;
	}

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &posrespcodeinfo_rec, 0, sizeof( struct EzPOSRespCodeInfo ) );
	strcpy( posrespcodeinfo_rec.RespCodeGroupId, RecordId );
	retval = readEzPOSRespCodeInfo( RecordId, &posrespcodeinfo_rec );
	dbutil_ptr->DBClose();

	if( retval != 0 )
	{
		dptr->trace( "Error in Reading RecordId[%s] from EzPOSRespCodeInfo....OraErr[%05d]", RecordId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_SEARCH_TABLE );
		return -1;
	}

	if( addPOSRespCodeInfo( posrespcodeinfo_rec ) < 0 )
	{
		dptr->trace( "Error in Updating RecordId[%s] in POSRespCodeInfo Memory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Updated RecordId[%s] in POSRespCodeInfo Successfully", RecordId );
	return 1;
}

int EzGUIPOSRequest :: processRespCodeInfoDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], Action[ TEMP + 1 ], RecordId[ POS_RECORDID_SIZE + 1  ];
	struct EzPOSRespCodeInfo posrespcodeinfo_rec;
	int retval;

	dptr->trace( "Processing RespCodeInfo Delete Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_ACTION_NULL );
		dptr->trace( "Action for RespCodeInfo Delete Request is Null...Cannot process Request" );
		return -1;
	}

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );
	if( strlen( RecordId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_NULL );
		dptr->trace( "RecordId is NULL...Cannot Process Request...");
		return -1;
	}

	if( deletePOSRespCodeInfo( RecordId ) < 0 )
	{
		dptr->trace( "Error in Deleting RecordId[%s] From POSRespCodeInfo Memory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_TXNINFO_ADD_MEMORY );
		return -1;
	}
	dptr->trace( "Deleted RecordId[%s] From POSRespCodeInfo Successfully", RecordId );
	return 1;
}

int EzGUIPOSRequest :: processPOSRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], ModuleName[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing POSRequest[%s]", GuiReq );

	memset( ModuleName, 0, sizeof( ModuleName ) );
	tokenutil_ptr->getToken( GuiReq, ModuleName, 0x1c, 1 );

	if( !strlen( ModuleName ) )
	{
		dptr->trace( "ModuleName is NULL..cannot Process POS request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_MODULENAME );
		retval = -1;
	}

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process POS request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process BIN request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_POS_COMMANDTYPE );
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

	if( !strcasecmp ( ModuleName, "POS_TERMINAL" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processTerminalAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processTerminalDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processTerminalUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS TERMINAL..GUI Command Received..." );
				retval = -1;
		}
	}
	else if( !strcasecmp ( ModuleName, "POS_TERMINALTYPE" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processTerminalTypeAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processTerminalTypeDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processTerminalTypeUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS TERMINALTYPE..GUI Command Received..." );
				retval = -1;
		}
	}
	else if( !strcasecmp ( ModuleName, "POS_MERCHANT" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processMerchantAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processMerchantDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processMerchantUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS MERCHANT..GUI Command Received..." );
				retval = -1;
		}
	}
	else if( !strcasecmp ( ModuleName, "POS_MERCHANTTYPE" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processMerchantTypeAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processMerchantTypeDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processMerchantTypeUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS MERCHANT TYPE..GUI Command Received..." );
				retval = -1;
		}
	}
	else if( !strcasecmp ( ModuleName, "POS_STORE" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processStoreAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processStoreDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processStoreUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS STORE..GUI Command Received..." );
				retval = -1;
		}
	}
	else if( !strcasecmp ( ModuleName, "POS_MCC" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processMCCAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processMCCDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processMCCUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS MCC..GUI Command Received..." );
				retval = -1;
		}
	}
	else if( !strcasecmp ( ModuleName, "POS_TXNINFO" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processTxnInfoAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processTxnInfoDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processTxnInfoUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS TXNINFO..GUI Command Received..." );
				retval = -1;
		}
	}
	if( !strcasecmp ( ModuleName, "POS_RESPCODEINFO" ) )
	{
		switch ( atoi( TempStr ) )
		{
			case GUI_ADD_CMD:
				retval = processRespCodeInfoAddRequest( GuiReq );
			break;

			case GUI_REMOVE_CMD:
				retval = processRespCodeInfoDeleteRequest( GuiReq );
			break;

			case GUI_UPDATE_CMD:
				retval = processRespCodeInfoUpdateRequest( GuiReq );
			break;

			default:
				dptr->trace( "Invalid POS RESPCODEINFO..GUI Command Received..." );
				retval = -1;
		}
	}

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
	return retval;
}




