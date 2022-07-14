#include <ezbusiness/ezguicontroller.h>

int EzGUISecurityRequest :: initGUISecurityRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initEzSecurityDriverUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing SecurityDriverUtil....");
		return -1;
	}

	if( LoadATMKeySharedMemory() < 0 )
	{
		dptr->trace( "Error in Loading ATMKey Memory....");
		return -1;
	}

	if( LoadNetworkKeySharedMemory() < 0 )
	{
		dptr->trace( "Error in Loading NetworkKey Memory....");
		return -1;
	}

	if( LoadSecuritySharedMemory() < 0 )
	{
		dptr->trace( "Error in Loading Security Memory....");
		return -1;
	}

	return 1;
}

int EzGUISecurityRequest :: processSecurityAdd( const char *GuiReq )
{
	struct EzSecurity securitytable_rec;
	char SecurityId[ 11 ];
	int retval;

	memset( SecurityId, 0, sizeof( SecurityId ) );
	tokenutil_ptr->getToken( GuiReq, SecurityId, GUI_GS, 3 );

	if( !strlen( SecurityId ) )
	{
		dptr->trace( "SecurityId is NULL...Cannot Process Security Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_SECURITYID_NULL );
		return -1;
	}

	dptr->trace( "Processing Security Add Request for SecurityId[%s]...", SecurityId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &securitytable_rec, 0, sizeof( struct EzSecurity ) );
	retval = dbutil_ptr->readEzSecurityTable( SecurityId, &securitytable_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading SecurityId[%s] from EzSecurity Table....SqlErr[%05d]", SecurityId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_SEARCH_TABLE );
		return -1;
	}

	if( addEzSecurity( SecurityId, &securitytable_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding SecurityId[%s] in SecurityMemory...", SecurityId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processSecurityUpdate( const char *GuiReq )
{
	struct EzSecurity securitytable_rec;
	char SecurityId[ 11 ];
	int retval;

	memset( SecurityId, 0, sizeof( SecurityId ) );
	tokenutil_ptr->getToken( GuiReq, SecurityId, GUI_GS, 3 );

	if( !strlen( SecurityId ) )
	{
		dptr->trace( "SecurityId is NULL...Cannot Process Security Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_SECURITYID_NULL );
		return -1;
	}

	dptr->trace( "Processing Security Update Request for SecurityId[%s]...", SecurityId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &securitytable_rec, 0, sizeof( struct EzSecurity ) );
	retval = dbutil_ptr->readEzSecurityTable( SecurityId, &securitytable_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading SecurityId[%s] from EzSecurity Table....SqlErr[%05d]", SecurityId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_SEARCH_TABLE );
		return -1;
	}

	if( updateEzSecurity( SecurityId, &securitytable_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Updating SecurityId[%s] in SecurityMemory...", SecurityId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processSecurityDelete( const char *GuiReq )
{
	struct EzSecurity securitytable_rec;
	char SecurityId[ 11 ];
	int retval;

	memset( SecurityId, 0, sizeof( SecurityId ) );
	tokenutil_ptr->getToken( GuiReq, SecurityId, GUI_GS, 3 );

	if( !strlen( SecurityId ) )
	{
		dptr->trace( "SecurityId is NULL...Cannot Process Security Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_SECURITYID_NULL );
		return -1;
	}

	dptr->trace( "Processing Security Delete Request for SecurityId[%s]...", SecurityId );

	if( deleteEzSecurity( SecurityId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding SecurityId[%s] in SecurityMemory...", SecurityId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processSecurityRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing SecurityRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Security request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Security request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_SECURITY_COMMANDTYPE );
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
			retval = processSecurityAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processSecurityDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processSecurityUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Security..GUI Command Received..." );
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

int EzGUISecurityRequest :: processATMKeyAdd( const char *GuiReq )
{
	struct EzATMKey atmkey_rec;

	char ATMId[ 33 ];
	int retval;

	memset( ATMId, 0, sizeof( ATMId ) );
	tokenutil_ptr->getToken( GuiReq, ATMId, GUI_GS, 4 );

	if( !strlen( ATMId ) )
	{
		dptr->trace( "ATMId is NULL...Cannot Process ATMKey Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_ATMID_NULL );
		return -1;
	}

	dptr->trace( "Processing ATMKey Add Request for ATMId[%s]...", ATMId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &atmkey_rec, 0, sizeof( struct EzATMKey ) );
	retval = dbutil_ptr->readATMKeyTable( ATMId, &atmkey_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading ATMId[%s] from EzATMInfo Table....SqlErr[%05d]", ATMId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_SEARCH_TABLE );
		return -1;
	}
	if( addATMKey( ATMId, &atmkey_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding ATMId[%s] in ATMKeyMemory...", ATMId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processATMKeyUpdate( const char *GuiReq )
{
	struct EzATMKey atmkey_rec;

	char ATMId[ 33 ];
	int retval;

	memset( ATMId, 0, sizeof( ATMId ) );
	tokenutil_ptr->getToken( GuiReq, ATMId, GUI_GS, 4 );

	if( !strlen( ATMId ) )
	{
		dptr->trace( "ATMId is NULL...Cannot Process ATMKey Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_ATMID_NULL );
		return -1;
	}

	dptr->trace( "Processing ATMKey Update Request for ATMId[%s]...", ATMId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &atmkey_rec, 0, sizeof( struct EzATMKey ) );
	retval = dbutil_ptr->readATMKeyTable( ATMId, &atmkey_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading ATMId[%s] from EzATMInfo Table....SqlErr[%05d]", ATMId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_SEARCH_TABLE );
		return -1;
	}

	if( updateATMKey( ATMId, &atmkey_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Updating ATMId[%s] in ATMKeyMemory...", ATMId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processATMKeyDelete( const char *GuiReq )
{
	struct EzATMKey atmkey_rec;

	char ATMId[ 33 ];
	int retval;

	memset( ATMId, 0, sizeof( ATMId ) );
	tokenutil_ptr->getToken( GuiReq, ATMId, GUI_GS, 4 );

	if( !strlen( ATMId ) )
	{
		dptr->trace( "ATMId is NULL...Cannot Process ATMKey Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_ATMID_NULL );
		return -1;
	}

	dptr->trace( "Processing ATMKey Delete Request for ATMId[%s]...", ATMId );

	if( deleteATMKey( ATMId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in deleting ATMId[%s] in ATMKeyMemory...", ATMId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processATMKeyRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing ATMKeyRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process ATMKey request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process ATMKey request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATMKEY_COMMANDTYPE );
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
			retval = processATMKeyAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processATMKeyDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processATMKeyUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid ATMKey..GUI Command Received..." );
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

int EzGUISecurityRequest :: processNetworkKeyAdd( const char *GuiReq )
{
	struct EzNetworkKey networkkey_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process NetworkKey Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_NETWORKID_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkKey Add Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkkey_rec, 0, sizeof( struct EzNetworkKey ) );
	retval = dbutil_ptr->readNetworkKeyTable( NetworkId, &networkkey_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzATMInfo Table....SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_SEARCH_TABLE );
		return -1;
	}

	if( addNetworkKey( NetworkId, &networkkey_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding NetworkId[%s] in NetworkKeyMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processNetworkKeyUpdate( const char *GuiReq )
{
	struct EzNetworkKey networkkey_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process NetworkKey Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_NETWORKID_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkKey Update Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkkey_rec, 0, sizeof( struct EzNetworkKey ) );
	retval = dbutil_ptr->readNetworkKeyTable( NetworkId, &networkkey_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkKey Table....SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_SEARCH_TABLE );
		return -1;
	}

	if( updateNetworkKey( NetworkId, &networkkey_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Updating NetworkId[%s] in NetworkKeyMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processNetworkKeyDelete( const char *GuiReq )
{
	struct EzNetworkKey networkkey_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process NetworkKey Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_NETWORKID_NULL );
		return -1;
	}

	dptr->trace( "Processing NetworkKey Delete Request for NetworkId[%s]...", NetworkId );

	if( deleteNetworkKey( NetworkId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting NetworkId[%s] in NetworkKeyMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUISecurityRequest :: processNetworkKeyRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing NetworkKey Request[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process NetworkKey request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process NetworkKey request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORKKEY_COMMANDTYPE );
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
			retval = processNetworkKeyAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processNetworkKeyDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processNetworkKeyUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid NetworkKey..GUI Command Received..." );
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

