#include <ezbusiness/ezguicontroller.h>

char GUIMapTable[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

int EzGUIATMRequest :: initGUIATMRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( InitEzATMUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing ATMUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: BuildDownLoadAll(  const char *GuiResp, struct EzAtmController *AtmControler )
{

	dptr->trace( "Building Download All Request...." );

	char CommandId[ TEMP + 1 ];

	memset( CommandId, 0, sizeof( CommandId ) );
	tokenutil_ptr->getToken( GuiResp, CommandId, DEVICE_FS, 5 );
	if( !strcasecmp( CommandId, "all" ) )
			AtmControler->DownloadType = DOWNLOAD_ALL ;
	else if( !strcasecmp( CommandId, "state" ) )
			AtmControler->DownloadType = DOWNLOAD_STATE ;
	else if( !strcasecmp( CommandId, "screen" ) )
			AtmControler->DownloadType = DOWNLOAD_SCREEN ;
	else if( !strcasecmp( CommandId, "misc" ) )
			AtmControler->DownloadType = DOWNLOAD_MISC ;
	else if( !strcasecmp( CommandId, "emisc" ) )
			AtmControler->DownloadType = DOWNLOAD_MISC_E ;
	else if( !strcasecmp( CommandId, "fit" ) )
			AtmControler->DownloadType = DOWNLOAD_FIT ;
	else if( !strcasecmp( CommandId, "key" ) )
			AtmControler->DownloadType = DOWNLOAD_KEY ;
	else if( !strcasecmp( CommandId, "configid" ) )
			AtmControler->DownloadType = DOWNLOAD_CONFIG_ID ;
	else if( !strcasecmp( CommandId, "date_time" ) )
			AtmControler->DownloadType = DOWNLOAD_DATE_TIME ;
	else if( !strcasecmp( CommandId, "custom_icon" ) )
			AtmControler->DownloadType = DOWNLOAD_CUSTOM_ICON ;
	else if( !strcasecmp( CommandId, "custom_char" ) )
			AtmControler->DownloadType = DOWNLOAD_CUSTOM_CHAR ;
	else if( !strcasecmp( CommandId, "celldata" ) )
			AtmControler->DownloadType = DOWNLOAD_CELLDATA ;
	else if( !strcasecmp( CommandId, "template" ) )
			AtmControler->DownloadType = DOWNLOAD_TEMPLATE ;
	else if( !strcasecmp( CommandId, "reserved_screen" ) )
			AtmControler->DownloadType = DOWNLOAD_RESERVED_SCREEN ;
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INVALID_DOWNLOAD_TYPE );
		dptr->trace( "Invalid Download Type.....");
		return -1;
	}
	if( chutil_ptr->WriteChannel( CONTROLLERCHANNEL, (char*)AtmControler, sizeof( struct EzAtmController ) ) < 0 )
	{
		   dptr->trace( "Failed to write msg into EzATMController Channel" );
		   memset( ErrDesc, 0, sizeof( ErrDesc ) );
		   strcpy( ErrDesc, GUI_ERR_ATM_CONTROLLER_WRITE );
		   return -1;
	}
	return 1;
}


int EzGUIATMRequest :: processATMDownloadRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct EzAtmController AtmCont;
	bool GroupActivity = false;
	int AtmCount = 0;

	dptr->trace( "Processing Download Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		dptr->trace( "Action for Download Request is Null...Cannot process Request" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		dptr->trace( "ATMId is NULL...Cannot Process Request...");
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		return -1;
	}

	dptr->trace( "Processing Download Request for InstId[%s] ATMId[%s] ", InstId, AtmId );

	if( VerifyAtmMemory( AtmId ) < 0 )
	{
		AtmCount = GetAtmCount( AtmId );
		if( AtmCount <= 0 )
		{
			dptr->trace( "Error in searching AtmLogicalGroup[%s] AtmCount[%d]", AtmId, AtmCount );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
			return -1;
		}
		else
		{
			GroupActivity = true;
			memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ));
			strcpy( AtmLogicalGroup, AtmId );
		}
	}

	memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
	AtmCont.MsgType = EZ_ATM_DOWNLOAD_REQ ;
	AtmCont.DownloadId = DOWNLOAD_SINGLE;

	if( GroupActivity )
	{
		for( int i = 0; i < AtmCount; i++ )
		{
			if( GetAtmId( AtmLogicalGroup, AtmCont.AtmId, i + 1 ) > 0 )
			{
				dptr->trace("Posting Download All Message for ATMId[%s]", AtmCont.AtmId );
				if( BuildDownLoadAll( GuiReq, &AtmCont  ) < 0 )
				{
					dptr->trace( DEBUG_ERROR, "Failed in BuildDownLoadAll" );
					return -1;
				}
			}
		}
	}
	else
	{
		memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
		if( BuildDownLoadAll( GuiReq, &AtmCont  ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Failed in BuildDownLoadAll" );
			return -1;
		}
	}
	return 1;
}

int EzGUIATMRequest :: MakeAtmService ( char *CommandId,  struct EzAtmController *AtmControler )
{
	if( !strcasecmp( CommandId, "go_in_service" ) )
	         AtmControler->CommandType = GO_IN_SERVICE ;
    else if( !strcasecmp( CommandId, "go_out_service" ) )
             AtmControler->CommandType = GO_OUT_SERVICE ;
    else if( !strcasecmp( CommandId, "shutdown" ) )
             AtmControler->CommandType = SHUTDOWN ;
    else if( !strcasecmp( CommandId, "get_config_info" ) )
    		AtmControler->CommandType = GET_CONFIG_INFO ;
	else if( !strcasecmp( CommandId, "close_valid_shield" ) )
			AtmControler->CommandType = CLOSE_VANDAL_SHIELD ;
	else if( !strcasecmp( CommandId, "open_valid_shield" ) )
	        AtmControler->CommandType = OPEN_VANDAL_SHIELD ;
	else if( !strcasecmp( CommandId, "unlock_safe_door" ) )
	        AtmControler->CommandType = UNLOCK_SAFE_DOOR ;
	else if( !strcasecmp( CommandId, "lock_safe_door" ) )
	        AtmControler->CommandType = LOCK_SAFE_DOOR ;
	else if( !strcasecmp( CommandId, "emg" ) )
	        AtmControler->CommandType = EMG_COMMAND ;
	else if( !strcasecmp( CommandId, "get_supply_counters" ) )
	        AtmControler->CommandType = GET_SUPPLY_COUNTS ;
	else if( !strcasecmp( CommandId, "clear_supply_counters" ) )
	        AtmControler->CommandType =  CLEAR_SUPPLY_COUNTS ;
	else if( !strcasecmp( CommandId, "get_esupply_counters" ) )
	        AtmControler->CommandType = GET_ESUPPLY_COUNTS ;
	else if( !strcasecmp( CommandId, "clear_esupply_counters" ) )
			AtmControler->CommandType =  CLEAR_ESUPPLY_COUNTS ;
    else if( !strcasecmp( CommandId, "run_self_test" ) )
            AtmControler->CommandType = RUN_SELF_TEST ;
    else if( !strcasecmp( CommandId, "get_tally_info" ) )
            AtmControler->CommandType = GET_TALLY_INFO ;
    else if( !strcasecmp( CommandId, "get_errorlog" ) )
            AtmControler->CommandType = GET_ERRORLOG ;
    else if( !strcasecmp( CommandId, "get_hw_config" ) )
           AtmControler->CommandType = GET_HW_CONF ;
   else if( !strcasecmp( CommandId, "get_date_time" ) )
           AtmControler->CommandType = GET_DATE_TIME ;
   else if( !strcasecmp( CommandId, "get_ekc" ) )
           AtmControler->CommandType =  GET_EKC ;
   else
   {
	   memset( ErrDesc, 0, sizeof( ErrDesc ) );
	   strcpy( ErrDesc, GUI_ERR_ATM_COMMANDTYPE );
	   dptr->trace( "Invalid Command Type..Cannot process Request....");
	   return -1;
   }

   if( chutil_ptr->WriteChannel( CONTROLLERCHANNEL, (char*)AtmControler, sizeof( struct EzAtmController ) ) < 0 )
   {
	   memset( ErrDesc, 0, sizeof( ErrDesc ) );
	   strcpy( ErrDesc, GUI_ERR_ATM_CONTROLLER_WRITE );
	   dptr->trace( "Failed to write msg into EzATMController Channel" );
	   return -1;
   }
   return 1;
}

int EzGUIATMRequest :: processATMCommandRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct EzAtmController AtmCont;
	bool GroupActivity = false;
	int AtmCount = 0;

	dptr->trace( "Processing Command Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for Download Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process Request...");
		return -1;
	}

	dptr->trace( "Processing Command Request for InstId[%s] ATMId[%s] ", InstId, AtmId );

	if( VerifyAtmMemory( AtmId ) < 0 )
	{
		AtmCount = GetAtmCount( AtmId );

		if( AtmCount <= 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
			dptr->trace( "Error in searching AtmLogicalGroup[%s] AtmCount[%d]", AtmId, AtmCount );
			return -1;
		}
		else
		{
			GroupActivity = true;
			memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ));
			strcpy( AtmLogicalGroup, AtmId );
		}
	}

	memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
	AtmCont.MsgType = EZ_ATM_COMMAND_REQ ;

	if( GroupActivity )
	{
		for( int i = 0; i < AtmCount; i++ )
		{
			if( GetAtmId( AtmLogicalGroup, AtmCont.AtmId, i + 1 ) > 0 )
			{
				memset( TempStr, 0, sizeof( TempStr ));
				tokenutil_ptr->getToken( GuiReq, TempStr, DEVICE_FS, 5 );
				MakeAtmService( TempStr , &AtmCont );
			}
		}
	}
	else
	{
		memcpy( AtmCont.AtmId, AtmId, strlen( AtmId ) );
		memset( TempStr, 0, sizeof( TempStr ));
		tokenutil_ptr->getToken( GuiReq, TempStr, DEVICE_FS, 5 );
		MakeAtmService( TempStr , &AtmCont );
	}
	return 1;
}

int EzGUIATMRequest :: processATMAddRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct EzAtmMgrQMsg atmmgrqmsg;
	bool GroupActivity = false;
	int AtmCount = 0;

	dptr->trace( "Processing ATM Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for ATM Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process Request...");
		return -1;
	}

	dptr->trace( "Processing ATM Add Request for InstId[%s] ATMId[%s] ", InstId, AtmId );

	if( VerifyAtmMemory( AtmId ) < 0 )
	{
		memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
		atmmgrqmsg.SourceType = MEMORY;
		atmmgrqmsg.CommandCode = ATMINFOMEMORY;
		atmmgrqmsg.OperationCode = ADD;
		strcpy( atmmgrqmsg.AtmId, AtmId );
		strcpy( atmmgrqmsg.SourceBuffer, InstId );
		if( chutil_ptr->WriteChannel( ATMMGRCHANNEL, ( char * )&atmmgrqmsg, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_MGR_WRITE );
			dptr->trace( "Failed to write msg into %s Channel", ATMMGRCHANNEL );
			return -1;
		}
	}
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ALREADY_EXISTS_MEMORY );
		dptr->trace( DEBUG_ERROR, "Atm id [%s] already Exist", AtmId );
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: processATMDeleteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct EzAtmMgrQMsg atmmgrqmsg;
	bool GroupActivity = false;
	int AtmCount = 0;

	dptr->trace( "Processing ATM Add Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for ATM Add Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process Request...");
		return -1;
	}

	dptr->trace( "Processing ATM Delete Request for InstId[%s] ATMId[%s] ", InstId, AtmId );

	if( VerifyAtmMemory( AtmId ) > 0 )
	{
		memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
		atmmgrqmsg.SourceType = MEMORY;
		atmmgrqmsg.CommandCode = ATMINFOMEMORY;
		atmmgrqmsg.OperationCode = DELETE;
		strcpy( atmmgrqmsg.AtmId, AtmId );
		strcpy( atmmgrqmsg.SourceBuffer, InstId );
		if( chutil_ptr->WriteChannel( ATMMGRCHANNEL, ( char * )&atmmgrqmsg, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_MGR_WRITE );
			dptr->trace( "Failed to write msg into %s Channel", ATMMGRCHANNEL );
			return -1;
		}
	}
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
		dptr->trace( DEBUG_ERROR, "Atm id [%s] does not Exist", AtmId );
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: processATMUpdateRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct EzAtmMgrQMsg atmmgrqmsg;
	bool GroupActivity = false;
	int AtmCount = 0;

	dptr->trace( "Processing ATM Update Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for ATM Update Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process Request...");
		return -1;
	}

	dptr->trace( "Processing ATM Update Request for InstId[%s] ATMId[%s] ", InstId, AtmId );

	if( VerifyAtmMemory( AtmId ) > 0 )
	{
		memset( &atmmgrqmsg,0, sizeof( struct EzAtmMgrQMsg ));
		atmmgrqmsg.SourceType = MEMORY;
		atmmgrqmsg.CommandCode = ATMINFOMEMORY;
		atmmgrqmsg.OperationCode = UPDATE;
		strcpy( atmmgrqmsg.AtmId, AtmId );
		strcpy( atmmgrqmsg.SourceBuffer, InstId );
		if( chutil_ptr->WriteChannel( ATMMGRCHANNEL, ( char * )&atmmgrqmsg, sizeof( struct EzAtmMgrQMsg ) ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_MGR_WRITE );
			dptr->trace( "Failed to write msg into %s Channel", ATMMGRCHANNEL );
			return -1;
		}
	}
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
		dptr->trace( DEBUG_ERROR, "Atm id [%s] does not Exist", AtmId );
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: processATMResetDenomRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct AtmMemoryTable atmmem;
	struct AtmTableInfo atminfo;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9];
	int SqlErr;

	dptr->trace( "Processing ATM Reset Denom Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for ATM Reset Denom Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process ATM Reset Denom Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process ATM Reset Denom Request...");
		return -1;
	}

	dptr->trace( "Processing ATM Reset Denom Request for InstId[%s] ATMId[%s] ", InstId, AtmId );


	if( VerifyAtmMemory( AtmId ) > 0 )
	{
		memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
		if( ReadAtmMemory( AtmId, &atmmem ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
			dptr->trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
			return -1;
		}

		memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
		memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
		memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );

		memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( atmmem.AtmInfoBuffer ) );
		memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &denominfo, &atmbuf.denominfo, sizeof( struct DenomInfo ) * 8 );

		for( int i = 0; i < 8; i++ )
		{
			if( denominfo[ i ].Status == 'N' )
				denominfo[ i ].Status = 'Y';
		}

		if( dbutil_ptr->ConnectDB( ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_DBCONNECT );
			dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
			return  -1;
		}
		memset( atminfo.BatchId, 0, sizeof( atminfo.BatchId ) );
		SqlErr = dbutil_ptr->readAtmBatchId( AtmId, atminfo.BatchId );
		if( SqlErr != 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_SEARCH_BATCHID_TABLE );
			dptr->trace( "Error in Fetching BatchId for AtmId[%s] Ora[%05d]", AtmId, SqlErr);
			dbutil_ptr->CloseDB();
			return -1;
		}
		dbutil_ptr->CloseDB();

		dptr->trace("Current BatchId[%s]",atminfo.BatchId);
		memset( &atmbuf.denominfo, 0, sizeof( struct DenomInfo ) * 8 );
		memcpy( &atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 8 );

		memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

		memset( &atmmem.AtmInfoBuffer, 0, sizeof( atmmem.AtmInfoBuffer ) );
		memcpy( &atmmem.AtmInfoBuffer, &atminfo, sizeof( atmmem.AtmInfoBuffer ) );

		if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_WRITE_MEMORY );
			dptr->trace( "Error in Reseting Denom memory for Atm[ %s ]", AtmId );
			return -1;
		}
		else
			dptr->trace( "Denom memory for Atm[ %s ] is Reseted", AtmId );
	}
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
		dptr->trace( DEBUG_ERROR, "Atm id [%s] does not Exist", AtmId );
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: processATMClearStatusRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ], AtmLogicalGroup[ ATM_ID_SIZE + 1 ];
	struct AtmMemoryTable atmmem;
	struct AtmTableInfo atminfo;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9];
	int SqlErr;
	EzDateTimeUtil dtu;
	char Date[ 10 ], Time[ 10 ];

	dptr->trace( "Processing ATM Clear Status Request for GuiReq[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for ATM Clear Status Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process ATM Clear Status Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process ATM Clear Status Request...");
		return -1;
	}

	dptr->trace( "Processing ATM Clear Status Request for InstId[%s] ATMId[%s] ", InstId, AtmId );

	if( VerifyAtmMemory( AtmId ) > 0 )
	{
		memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
		if( ReadAtmMemory( AtmId, &atmmem) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
			dptr->trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
			return -1;
		}

		memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
		memcpy( &atminfo, &atmmem.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );

		memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
		memcpy( &atmbuf, &atmmem.AtmSharedBuffer, sizeof( struct ATMSharedBuffer ) );

		memset( atmbuf.StaticStatus, 0, sizeof( atmbuf.StaticStatus ) );
		strcpy( atmbuf.StaticStatus, "NONE" );

		memset( atmbuf.StatusMsg, 0, sizeof( atmbuf.StatusMsg ) );

		memset( &atmmem.AtmSharedBuffer, 0, sizeof( atmmem.AtmSharedBuffer ) );
		memcpy( &atmmem.AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

		if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_WRITE_MEMORY );
			dptr->trace( "Error in Clearing Status memory for Atm[ %s ]", AtmId );
			return -1;
		}
		else
			dptr->trace( "Status memory for Atm[ %s ] is Cleared", AtmId );

		if( dbutil_ptr->ConnectDB( ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_DBCONNECT );
			dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
			return  -1;
		}

		memset( Date, 0, sizeof( Date ) );
		sprintf( Date, "%06d", dtu.getSysDate() );
		memset( Time, 0, sizeof( Time ) );
		sprintf( Time, "%06d", dtu.getSysTime() );

		SqlErr = dbutil_ptr->ClearATMStaticStatus( atmbuf.StaticStatus, AtmId, Date, Time );
		if( SqlErr != 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_ATM_UPDATE_STATUS_TABLE );
			dptr->trace( DEBUG_ERROR,"Error in Updating the table ORA ERR: [%05d]", SqlErr );
			dbutil_ptr->CloseDB();
			return -1;
		}
		else
		{
			dptr->trace( "Status Table for Atm[ %s ] is Cleared", AtmId );
		}

		dbutil_ptr->CloseDB();
	}
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
		dptr->trace( DEBUG_ERROR, "Atm id [%s] does not Exist", AtmId );
		return -1;
	}
	return 1;
}

void EzGUIATMRequest :: getMappedDateTimeVal( char *MapVal )
{
	char OrgVal[ 20 ], TempStr[ 10 ];

	memset( OrgVal, 0, sizeof( OrgVal ) );
	sprintf( OrgVal, "%06d%06d", dtutil.getSysDate(), dtutil.getSysTime() );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal, 2 );
	MapVal [ 0 ] = GUIMapTable [ atoi( TempStr ) ];

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal + 2, 2 );
	MapVal [ 1 ] = GUIMapTable [ atoi( TempStr ) ];

	strncpy( MapVal + 2, OrgVal + 4, 2 );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal + 6, 2 );
	MapVal [ 4 ] = GUIMapTable [ atoi( TempStr ) ];

	strncpy( MapVal + 5, OrgVal + 8, 2 );

	strncpy( MapVal + 7, OrgVal + 10, 2 );
}


int EzGUIATMRequest :: createNewBatchId( const char *AtmId, char *NewBatchId )
{
	char FilePath[ 200 ], MappedVal[ 20 ];
	int retval;
	FILE *fptr;
	int BatchSeqNo = 0;

	memset( FilePath, 0, sizeof( FilePath ) );
	sprintf( FilePath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "inf", "BatchSeqNo.dat " );

	fptr = fopen( FilePath, "r" );
	if( fptr == NULL )
	{
		dptr->trace( "Error in Opening File[%s]", FilePath );
		BatchSeqNo = 1;
	}
	else
	{
		fscanf( fptr, "%d", &BatchSeqNo );
		fclose( fptr );
	}

	memset( MappedVal, 0, sizeof( MappedVal ) );
	getMappedDateTimeVal( MappedVal );

	sprintf( NewBatchId, "%s%03d", MappedVal, BatchSeqNo );

	if( BatchSeqNo == 999 )
		BatchSeqNo = 1;
	else
		BatchSeqNo = BatchSeqNo + 1;

	fptr = fopen( FilePath, "w" );
	if( fptr == NULL )
		dptr->trace( "Error in Opening File[%s]", FilePath );
	else
	{
		fprintf( fptr, "%d", BatchSeqNo );
		fclose( fptr );
	}

	retval = dbutil_ptr->updateBatchInAtmDataInfo( AtmId, NewBatchId );

	if( retval != 0 )
	{
		dptr->trace( "Error in Updating NewBatchId[%s] for ATMId[%s] in ATMDataInfo...SqlErr[%05d]", NewBatchId, AtmId, retval );
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: processATMClearCassetteRequest( const char *GuiReq )
{
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ], InstId[ INST_SIZE + 1 ], Action[ TEMP + 1 ];
	struct EzAtmDenomStatus ezatmdenomstatus;
	struct AtmMemoryTable atmmem;
	char CurrentBatchId[ 13 ], UserId[ 33 ], NewBatchId[ 13 ];
	int SqlErr;

	dptr->trace( "Processing ATM Clear Cassette Request[%s]....", GuiReq );

	memset( Action, 0, sizeof( Action ) );
	tokenutil_ptr->getToken( GuiReq, Action, GUI_GS, 2 );

	if( !strlen( Action ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ACTION_NULL );
		dptr->trace( "Action for ATM Clear Cassette Request is Null...Cannot process Request" );
		return -1;
	}

	memset( InstId, 0, sizeof( InstId ) );
	tokenutil_ptr->getToken( GuiReq, InstId, GUI_GS, 3 );

	if( !strlen( InstId ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_INST_NULL );
		dptr->trace( "InstId is NULL...Cannot Process Clear Cassette Load Request...");
		return -1;
	}

	memset( AtmId, 0, sizeof( AtmId ) );
	tokenutil_ptr->getToken( GuiReq, AtmId, GUI_GS, 4 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_ATMID_NULL );
		dptr->trace( "ATMId is NULL...Cannot Process Clear Cassette Load Request...");
		return -1;
	}

	memset( UserId, 0, sizeof( UserId ) );
	tokenutil_ptr->getToken( GuiReq, UserId, GUI_GS, 5 );
	if( strlen( AtmId ) == 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_USERID_NULL );
		dptr->trace( "UserId is NULL...Cannot Process Clear Cassette Load Request...");
		return -1;
	}

	dptr->trace( "Processing ATM Clear Cassette Request for InstId[%s] ATMId[%s] UserId[%s]", InstId, AtmId, UserId );

	memset( &atmmem, 0, sizeof( struct AtmMemoryTable ) );
	if( ReadAtmMemory( AtmId, &atmmem ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_NOT_EXISTS_MEMORY );
		dptr->trace( "Unable to Read AtmMemoryTable AtmId< %s >",  AtmId );
		return -1;
	}

	memset( CurrentBatchId, 0, sizeof( CurrentBatchId ) );
	strcpy( CurrentBatchId, atmmem.AtmInfoBuffer.BatchId );

	if( dbutil_ptr->ConnectDB( ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		dptr->trace( DEBUG_ERROR,"Error in Connecting the Database");
		return  -1;
	}

	memset( &ezatmdenomstatus, 0, sizeof( struct EzAtmDenomStatus ) );
	SqlErr = dbutil_ptr->readEzAtmDenomStatus( AtmId, dtutil.getSysDate(), dtutil.getSysTime(), &ezatmdenomstatus );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in reading EzAtmDenomStatus for ATMId[%s]...SqlErr[%05d]", AtmId, SqlErr );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_SEARCH_DENOMSTATUS_TABLE );
		dbutil_ptr->CloseDB();
		return  -1;
	}

	dptr->trace( DEBUG_NORMAL, "Got Current BatchId[%s] for ATMId[%s]", CurrentBatchId, AtmId );

	/*SqlErr = dbutil_ptr->closeBatch( AtmId, CurrentBatchId, UserId, dtutil.getSysDate(), dtutil.getSysTime(), ezatmdenomstatus.DenomADisp, ezatmdenomstatus.DenomBDisp, ezatmdenomstatus.DenomCDisp, ezatmdenomstatus.DenomDDisp, ezatmdenomstatus.DenomEDisp, ezatmdenomstatus.DenomFDisp, ezatmdenomstatus.DenomGDisp, ezatmdenomstatus.DenomHDisp, ezatmdenomstatus.DenomANotesLoaded, ezatmdenomstatus.DenomBNotesLoaded, ezatmdenomstatus.DenomCNotesLoaded, ezatmdenomstatus.DenomDNotesLoaded, ezatmdenomstatus.DenomENotesLoaded, ezatmdenomstatus.DenomFNotesLoaded, ezatmdenomstatus.DenomGNotesLoaded, ezatmdenomstatus.DenomHNotesLoaded );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in Closing the BatchId[%s] for ATMId[%s] UserId[%s]...SqlErr[%05d]", CurrentBatchId, AtmId, UserId, SqlErr );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_CLOSE_BATCH_TABLE );
		dbutil_ptr->CloseDB();
		return -1;
	}*/

	memset( NewBatchId, 0, sizeof( NewBatchId ) );
	if( createNewBatchId( AtmId, NewBatchId ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_BATCH_CREATE );
		dbutil_ptr->CloseDB();
		return -1;
	}

	SqlErr = dbutil_ptr->openBatch( AtmId, NewBatchId, UserId, dtutil.getSysDate(), dtutil.getSysTime(), ezatmdenomstatus.DenomADisp, ezatmdenomstatus.DenomBDisp, ezatmdenomstatus.DenomCDisp, ezatmdenomstatus.DenomDDisp, ezatmdenomstatus.DenomEDisp, ezatmdenomstatus.DenomFDisp, ezatmdenomstatus.DenomGDisp, ezatmdenomstatus.DenomHDisp, ezatmdenomstatus.DenomANotesLoaded, ezatmdenomstatus.DenomBNotesLoaded, ezatmdenomstatus.DenomCNotesLoaded, ezatmdenomstatus.DenomDNotesLoaded, ezatmdenomstatus.DenomENotesLoaded, ezatmdenomstatus.DenomFNotesLoaded, ezatmdenomstatus.DenomGNotesLoaded, ezatmdenomstatus.DenomHNotesLoaded );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in Opening the BatchId[%s] for ATMId[%s] UserId[%s]...SqlErr[%05d]", NewBatchId, AtmId, UserId, SqlErr );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_OPEN_BATCH_TABLE );
		dbutil_ptr->CloseDB();
		return -1;
	}

	/*SqlErr = dbutil_ptr->updateDenomStatusResetDateTime( AtmId, dtutil.getSysDate(), dtutil.getSysTime() );

	if( SqlErr != 0 )
		dptr->trace( "Error in Updating Reset Date & Time in EzATMDenomStatus for ATMId[%s] SqlErr[%05d]", AtmId, SqlErr );*/

	dbutil_ptr->CloseDB();

	memset( atmmem.AtmInfoBuffer.BatchId, 0, sizeof( atmmem.AtmInfoBuffer.BatchId ) );
	strcpy( atmmem.AtmInfoBuffer.BatchId, NewBatchId );

	for( int i = 0; i < 8; i++ )
	{
		if( atmmem.AtmSharedBuffer.denominfo[ i ].Status == 'N' )
			atmmem.AtmSharedBuffer.denominfo[ i ].Status = 'Y';
	}
	if( WriteAtmMemory( AtmId, &atmmem ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_WRITE_MEMORY );
		dbutil_ptr->CloseDB();
		return -1;
	}
	return 1;
}

int EzGUIATMRequest :: processATMRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing ATMRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process ATM request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process ATM request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ATM_COMMANDTYPE );
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
		case GUI_DOWNLOAD:
			retval = processATMDownloadRequest( GuiReq );
		break;

		case GUI_COMMAND:
			retval =  processATMCommandRequest( GuiReq );
		break;

		case GUI_ADD_CMD:
			retval = processATMAddRequest( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processATMDeleteRequest( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processATMUpdateRequest( GuiReq );
		break;

		case GUI_RESETDENOM:
			retval = processATMResetDenomRequest( GuiReq );
		break;

		case GUI_CLEARSTATUS:
			retval = processATMClearStatusRequest( GuiReq );
		break;

		case GUI_CLEARCASSETTE:
			retval = processATMClearCassetteRequest( GuiReq );
		break;

		default:
			dptr->trace( "Invalid ATM..GUI Command Received..." );
			retval = -1;
	}

	if( atoi( TempStr ) == GUI_CLEARCASSETTE )
	{
		if( retval < 0 )
		{
			RespFlag = 1;
			memset( GuiResp, 0, sizeof( GuiResp ) );
			sprintf( GuiResp, "%s%c%d%c%s", GuiReq, GUI_ES, RespFlag, GUI_ES, ErrDesc );

			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
				dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
		}
		else
		{
			RespFlag = 0;
			memset( GuiResp, 0, sizeof( GuiResp ) );
			sprintf( GuiResp, "%s%c%d", GuiReq, GUI_ES, RespFlag );

			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
				dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
		}
		return 0;
	}

	if( ( atoi( TempStr ) != GUI_LIST_CMD ) && ( atoi( TempStr ) != GUI_DOWNLOAD ) && ( atoi( TempStr ) != GUI_COMMAND )  && ( atoi( TempStr ) != GUI_RESETDENOM ) && ( atoi( TempStr ) != GUI_CLEARSTATUS ) )
	{
		if( retval < 0 )
		{
			RespFlag = 1;
			memset( GuiResp, 0, sizeof( GuiResp ) );
			sprintf( GuiResp, "%s%c%d%c%s", GuiReq, GUI_ES, RespFlag, GUI_ES, ErrDesc );

			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
				dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
		}
		return 1;
	}
	else
		return 0;
}


