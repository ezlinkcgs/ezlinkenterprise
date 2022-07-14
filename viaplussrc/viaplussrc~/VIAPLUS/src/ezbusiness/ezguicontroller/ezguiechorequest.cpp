#include <ezbusiness/ezguicontroller.h>

int EzGUIEchoRequest :: initGUIEchoRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initEchoUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing EchoUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoList( const char *GuiReq )
{
	int EchoCount = 0, EchoOffset = 0;
	char Status[ 20 ], EchoStatus[ 20 ],EchoProperty[ 50 ], EchoAction[ 50 ], EchoFlag[ 20 ], MsgTypeIndicatorFlag[ 20 ];
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	struct EzEchoTable echotable_rec;

	EchoCount = getCurrentEchoCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !EchoOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "ECHO", GUI_GS , EchoCount, GUI_GS );

		for( int i = EchoOffset; i < EchoTable_MaxNetworks; i++ )
		{
			memset( &echotable_rec, 0, sizeof( struct EzEchoTable ) );
			if( getNextEchoRecord( &echotable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th EchoRecord....", i );
				continue;
			}

			if ( ( strcmp( echotable_rec.NetworkId, ECHO_NETWORKID_INIT_VAL ) ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				memset( EchoProperty, 0, sizeof( EchoProperty ));
				memset( Status, 0, sizeof( Status ));

				if( echotable_rec.EchoProperty == ECHO_SEND_ALWAYS )
					strcpy( EchoProperty, "ECHO ALWAYS" );
				else
					strcpy( EchoProperty, "SEND ECHO, WHEN DOWN" );
				if( echotable_rec.Status == ECHO_THREAD_RUNNING )
					strcpy( Status, "RUNNING" );
				else
					strcpy( Status, "SUSPENDED" );

				sprintf( RecordString, "%s%c%d%c%s%c%s%c", echotable_rec.NetworkId, GUI_FS,  echotable_rec.EchoInterval, GUI_FS, EchoProperty, GUI_FS,  Status, GUI_RS );
				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					EchoOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}
			if( i + 1 == EchoTable_MaxNetworks )
			{
				EchoOffset = i + 1;
				break;
			}
		}
		if( EchoOffset == EchoTable_MaxNetworks )
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

int EzGUIEchoRequest :: processEchoAdd( const char *GuiReq )
{
	struct EzNetworkEcho networkecho_rec;
	struct EzEchoTable echotable_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Echo Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Echo Add Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkecho_rec, 0, sizeof( struct EzNetworkEcho ) );
	retval = dbutil_ptr->readEzNetworkEcho( NetworkId, &networkecho_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkEcho Table....SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_SEARCH_TABLE );
		return -1;
	}

	memset( &echotable_rec, 0, sizeof( struct EzEchoTable ) );
	strcpy( echotable_rec.NetworkId, networkecho_rec.NetworkId );
	echotable_rec.EchoProperty = networkecho_rec.EchoProperty;
	echotable_rec.LogOnReq = networkecho_rec.LogOnReq;

	if( addEchoMemory( echotable_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in adding NetworkId[%s] in EchoMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_ADD_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoDelete( const char *GuiReq )
{
	char NetworkId[ 17 ];

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Echo Remove Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Echo Remove Request for NetworkId[%s]...", NetworkId );

	if( deleteEchoMemory( NetworkId ) < 0 )
	{
		dptr->trace( "Error in removing NetworkId[%s] from EchoMemory", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoUpdate( const char *GuiReq )
{
	struct EzNetworkEcho networkecho_rec;
	struct EzEchoTable echotable_rec;
	char NetworkId[ 17 ];
	int retval;

	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Echo Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Echo Update Request for NetworkId[%s]...", NetworkId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &networkecho_rec, 0, sizeof( struct EzNetworkEcho ) );
	retval = dbutil_ptr->readEzNetworkEcho( NetworkId, &networkecho_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from EzNetworkEcho Table....SqlErr[%05d]", NetworkId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_SEARCH_TABLE );
		return -1;
	}

	memset( &echotable_rec, 0, sizeof( struct EzEchoTable ) );
	strcpy( echotable_rec.NetworkId, networkecho_rec.NetworkId );
	//strcpy( echotable_rec.EchoPropertyId, networkecho_rec.EchoPropertyId );
	echotable_rec.EchoProperty = networkecho_rec.EchoProperty;
	echotable_rec.LogOnReq = networkecho_rec.LogOnReq;

	if( updateEchoMemory( echotable_rec ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Updating NetworkId[%s] in EchoMemory...", NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_UPDATE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoStatusUpdate( const char *GuiReq, int EchoStatus )
{
	char NetworkId[ 17 ];
	memset( NetworkId, 0, sizeof( NetworkId ) );
	tokenutil_ptr->getToken( GuiReq, NetworkId, GUI_GS, 3 );

	if( !strlen( NetworkId ) )
	{
		dptr->trace( "NetworkId is NULL...Cannot Process Echo Status Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_NETWORK_NULL );
		return -1;
	}

	dptr->trace( "Processing Echo Status Update Request for NetworkId[%s]...", NetworkId );

	if( updateEchoThreadStatus( NetworkId, EchoStatus ) < 0 )
	{
		dptr->trace( "Error in Updating Echo Status in Echo Memory...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_STATUS_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing EchoRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Echo request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Echo request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHO_COMMANDTYPE );
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
			retval = processEchoList( GuiReq );
		break;

		case GUI_ADD_CMD:
			retval = processEchoAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processEchoDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processEchoUpdate( GuiReq );
		break;

		case GUI_SUSPEND_CMD:
			retval = processEchoStatusUpdate( GuiReq, ECHO_THREAD_SUSPEND );
		break;

		case GUI_RESUME_CMD:
			retval = processEchoStatusUpdate( GuiReq, ECHO_THREAD_RUNNING );
		break;


		default:
			dptr->trace( "Invalid Echo..GUI Command Received..." );
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

int EzGUIEchoRequest :: processEchoPropertyAdd( const char *GuiReq )
{
	struct EzEchoMgrMsg echomsg;
	struct EzEchoProperty echoproperty_rec;
	char EchoPropertyId[ 17 ];
	int retval;

	memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
	tokenutil_ptr->getToken( GuiReq, EchoPropertyId, GUI_GS, 3 );

	if( !strlen( EchoPropertyId ) )
	{
		dptr->trace( "EchoPropertyId is NULL...Cannot Process EchoProperty Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_NULL );
		return -1;
	}

	dptr->trace( "Processing EchoProperty Add Request for EchoPropertyId[%s]...", EchoPropertyId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &echoproperty_rec, 0, sizeof( struct EzEchoProperty ) );
	retval = dbutil_ptr->readEzEchoProperty( EchoPropertyId, &echoproperty_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_SEARCH_TABLE );
		dptr->trace( DEBUG_ERROR, "Error in Reading EchoPropertyId[%s] from EzEchoProperty Table...SqlErr[%05d]", EchoPropertyId, retval );
		return -1;
	}

	echomsg.Command = EZLINK_NTWK_ECHOPROPERTY_ADD;
	strcpy( echomsg.EchoPropertyId, EchoPropertyId );

	if( chutil_ptr->WriteChannel( ECHOMGRCHANNEL, ( char * ) &echomsg, sizeof( struct EzEchoMgrMsg ) ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_ADD_MEMORY );
		dptr->trace( DEBUG_ERROR, "Error in Writing Add EchoProperty Thread to Channel[%s] for EchoPropertyId[%s]", "EzEchoMgr", EchoPropertyId );
		return -1;
	}
	else
	{
		dptr->trace( DEBUG_NORMAL, "Written Add EchoProperty Thread to Channel[%s] for EchoPropertyId[%s]", "EzEchoMgr", EchoPropertyId );
		return 1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoPropertyUpdate( const char *GuiReq )
{
	struct EzEchoMgrMsg echomsg;
	struct EzEchoProperty echoproperty_rec;
	char EchoPropertyId[ 17 ];
	int retval;

	memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
	tokenutil_ptr->getToken( GuiReq, EchoPropertyId, GUI_GS, 3 );

	if( !strlen( EchoPropertyId ) )
	{
		dptr->trace( "EchoPropertyId is NULL...Cannot Process EchoProperty Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_NULL );
		return -1;
	}

	dptr->trace( "Processing EchoProperty Update Request for EchoPropertyId[%s]...", EchoPropertyId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &echoproperty_rec, 0, sizeof( struct EzEchoProperty ) );
	retval = dbutil_ptr->readEzEchoProperty( EchoPropertyId, &echoproperty_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_SEARCH_TABLE );
		dptr->trace( DEBUG_ERROR, "Error in Reading EchoPropertyId[%s] from EzEchoProperty Table...SqlErr[%05d]", EchoPropertyId, retval );
		return -1;
	}

	echomsg.Command = EZLINK_NTWK_ECHOPROPERTY_UPDATE;
	strcpy( echomsg.EchoPropertyId, EchoPropertyId );

	if( chutil_ptr->WriteChannel( ECHOMGRCHANNEL, ( char * ) &echomsg, sizeof( struct EzEchoMgrMsg ) ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_UPDATE_MEMORY );
		dptr->trace( DEBUG_ERROR, "Error in Writing Update EchoProperty Thread to Channel[%s] for EchoPropertyId[%s]", "EzEchoMgr", EchoPropertyId );
		return -1;
	}
	else
	{
		dptr->trace( DEBUG_NORMAL, "Written Update EchoProperty Thread to Channel[%s] for EchoPropertyId[%s]", "EzEchoMgr", EchoPropertyId );
		return 1;
	}
	return 1;
}


int EzGUIEchoRequest :: processEchoPropertyDelete( const char *GuiReq )
{
	struct EzEchoMgrMsg echomsg;
	struct EzEchoProperty echoproperty_rec;
	char EchoPropertyId[ 17 ];
	int retval;

	memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
	tokenutil_ptr->getToken( GuiReq, EchoPropertyId, GUI_GS, 3 );

	if( !strlen( EchoPropertyId ) )
	{
		dptr->trace( "EchoPropertyId is NULL...Cannot Process EchoProperty Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_NULL );
		return -1;
	}

	dptr->trace( "Processing EchoProperty Delete Request for EchoPropertyId[%s]...", EchoPropertyId );

	if( dbutil_ptr->ConnectDB() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &echoproperty_rec, 0, sizeof( struct EzEchoProperty ) );
	retval = dbutil_ptr->readEzEchoProperty( EchoPropertyId, &echoproperty_rec );

	if( dbutil_ptr->CloseDB() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	if( retval != 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_SEARCH_TABLE );
		dptr->trace( DEBUG_ERROR, "Error in Reading EchoPropertyId[%s] from EzEchoProperty Table...SqlErr[%05d]", EchoPropertyId, retval );
		return -1;
	}

	echomsg.Command = EZLINK_NTWK_ECHOPROPERTY_REMOVE;
	strcpy( echomsg.EchoPropertyId, EchoPropertyId );

	if( chutil_ptr->WriteChannel( ECHOMGRCHANNEL, ( char * ) &echomsg, sizeof( struct EzEchoMgrMsg ) ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_DELETE_MEMORY );
		dptr->trace( DEBUG_ERROR, "Error in Writing Delete EchoProperty Thread to Channel[%s] for EchoPropertyId[%s]", "EzEchoMgr", EchoPropertyId );
		return -1;
	}
	else
	{
		dptr->trace( DEBUG_NORMAL, "Written Delete EchoProperty Thread to Channel[%s] for EchoPropertyId[%s]", "EzEchoMgr", EchoPropertyId );
		return 1;
	}
	return 1;
}

int EzGUIEchoRequest :: processEchoPropertyRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing EchoRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Echo Property request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Echo Property request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ECHOPROPERTY_COMMANDTYPE );
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
			retval = processEchoPropertyAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processEchoPropertyDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processEchoPropertyUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Echo Property..GUI Command Received..." );
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

