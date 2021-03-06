#include <ezbusiness/ezguicontroller.h>

int EzGUIAlertRequest :: initGUIAlertRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzODBCUtil *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	if( initAlertMemUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing Alert Memory Util....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}

	 if( LoadStatusAlert() < 0 )
        {
                dptr->trace( "\n Error in Loading Status Alert.... " );
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;

        }

        if( LoadSMSAlertGroup() < 0 )
        {
                dptr->trace("\nError in Looading SMSAlertGroup...." );
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
        }
	
	if( LoadAlertDesc() < 0 )
	{
		dptr->trace( "Error in Loading AlertDesc Memory...." );
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}

	return 1;
}

int EzGUIAlertRequest :: processAlertAdd( const char *GuiReq )
{
	struct EzStatusAlertMemory statusalert_rec;
	struct EzSMSAlertGroupMemory smsalertgroup_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 4 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process Alert Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing Alert Add Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &statusalert_rec, 0, sizeof( struct EzStatusAlertMemory ) );
	retval = readEzStatusAlert( RecordId, &statusalert_rec );
        if( retval != 0 )
        {
                dptr->trace( "Error in Reading RecordId[%s] from EzStatusAlert....OraErr[%05d]", RecordId, retval );
	        memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_SEARCH_TABLE );
                dbutil_ptr->DBClose();
                return -1;
        }
        
	memset( &smsalertgroup_rec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
	retval = readEzSMSAlertGroup( statusalert_rec.SMSAlertGroupId, &smsalertgroup_rec );
	
	if( retval !=0 )
	{
		dptr->trace( "Error in Reading RecordId[%s] from EzSMSAlertGroup ... OraErr[%05d]", RecordId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_SEARCH_TABLE );
		dbutil_ptr->DBClose();
		return -1;
	}
	
	if( dbutil_ptr->DBClose() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	
	if( addStatusAlert( statusalert_rec ) < 0 )
        {
                dptr->trace( "Error in Adding RecordId[%s] in EzStatusAlertMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_ADD_MEMORY );
                return -1;
        }

	if( addSMSAlertGroup( smsalertgroup_rec ) < 0 )
        {
                dptr->trace( "Error in Adding SMSAlertGroupId[%s] in EzSMSAlertGroupMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_ADD_MEMORY );	
                return -1;
        }

	return 1;
}




int EzGUIAlertRequest :: processAlertDescAdd( const char *GuiReq )
{
	struct EzAlertDescMemory alertdesc_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process AlertDesc Add Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing AlertDesc Add Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &alertdesc_rec, 0, sizeof( struct EzAlertDescMemory ) );
	retval = readEzAlertDesc( RecordId, &alertdesc_rec );
        if( retval != 0 )
        {
                dptr->trace( "Error in Reading RecordId[%s] from EzStatusDesc....OraErr[%05d]", RecordId, retval );
	        memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERTDESC_SEARCH_TABLE );
                dbutil_ptr->DBClose();
                return -1;
        }
        
	
	if( dbutil_ptr->DBClose() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	
	if( addAlertDesc( alertdesc_rec ) < 0 )
        {
                dptr->trace( "Error in Adding RecordId[%s] in EzStatusDescriptionMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERTDESC_ADD_MEMORY );
                return -1;
        }


	return 1;
}



int EzGUIAlertRequest :: processAlertDescUpdate( const char *GuiReq )
{
	struct EzAlertDescMemory alertdesc_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process AlertDec Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing AlertDesc Update Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &alertdesc_rec, 0, sizeof( struct EzAlertDescMemory ) );
	retval = readEzAlertDesc( RecordId, &alertdesc_rec );
        if( retval != 0 )
        {
                dptr->trace( "Error in Reading RecordId[%s] from EzStatusDesc....OraErr[%05d]", RecordId, retval );
	        memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERTDESC_SEARCH_TABLE );
                dbutil_ptr->DBClose();
                return -1;
        }
        
	
	if( dbutil_ptr->DBClose() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	
	if(  updateAlertDesc( alertdesc_rec ) < 0 )
        {
                dptr->trace( "Error in Updating RecordId[%s] in EzStatusDescriptionMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERTDESC_ADD_MEMORY );
                return -1;
        }


	return 1;
}



int EzGUIAlertRequest :: processAlertUpdate( const char *GuiReq )
{
	struct EzStatusAlertMemory statusalert_rec;
	struct EzSMSAlertGroupMemory smsalertgroup_rec;
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 4 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process Alert Update Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_FIT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing Alert Update Request for RecordId[%s]", RecordId );

	if( dbutil_ptr->DBConnect() < 0 )
	{
		dptr->trace( "Error in Connecting with Switch Database...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCONNECT );
		return -1;
	}

	memset( &statusalert_rec, 0, sizeof( struct EzStatusAlertMemory ) );
	retval = readEzStatusAlert( RecordId, &statusalert_rec );
        if( retval != 0 )
        {
                dptr->trace( "Error in Reading RecordId[%s] from EzStatusAlert....OraErr[%05d]", RecordId, retval );
	        memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_SEARCH_TABLE );
                dbutil_ptr->DBClose();
                return -1;
        }
        
	memset( &smsalertgroup_rec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
	retval = readEzSMSAlertGroup( statusalert_rec.SMSAlertGroupId, &smsalertgroup_rec );
	
	if( retval !=0 )
	{
		dptr->trace( "Error in Reading RecordId[%s] from EzSMSAlertGroup ... OraErr[%05d]", RecordId, retval );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_SEARCH_TABLE );
		dbutil_ptr->DBClose();
		return -1;
	}
	
	if( dbutil_ptr->DBClose() < 0 )
	{
		dptr->trace( "Error in Closing Switch Database" );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_DBCLOSE );
		return -1;
	}

	
	if( updateStatusAlert( statusalert_rec ) < 0 )
        {
                dptr->trace( "Error in Updating RecordId[%s] in EzStatusAlertMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_ADD_MEMORY );
                return -1;
        }

	if( updateSMSAlertGroup( smsalertgroup_rec ) < 0 )
        {
                dptr->trace( "Error in Updating SMSAlertGroupId[%s] in EzSMSAlertGroupMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_ADD_MEMORY );	
                return -1;
        }

	return 1;
}




int EzGUIAlertRequest :: processAlertDelete( const char *GuiReq )
{
	char RecordId[ 17 ];
	int retval;
	char SMSAlertGroupId[ 17 ];

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 4 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process Alert Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing ALERT Delete Request for RecordId[%s]", RecordId );

	if( readSMSAlertGroupId( RecordId, SMSAlertGroupId ) < 0 )
	{	
		dptr->trace( "Error in Reading RecordId[ %s ] in EzStatusAlertMemory", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_SEARCH_TABLE );
		return -1;
	}

	if( deleteStatusAlert( RecordId ) < 0 )
        {
                dptr->trace( "Error in Deleting RecordId[%s] in EzStatusAlertMemory", RecordId );
                memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_DELETE_MEMORY );
                return -1;
        }
	
	
	if( deleteSMSAlertGroup( SMSAlertGroupId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Deleting RecordId[%s] in SMSGroup Memory...", RecordId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_DELETE_MEMORY );
		return -1;
	}
	return 1;
}


 
int EzGUIAlertRequest :: processAlertDescDelete( const char *GuiReq )
{
	char RecordId[ 17 ];
	int retval;

	memset( RecordId, 0, sizeof( RecordId ) );
	tokenutil_ptr->getToken( GuiReq, RecordId, GUI_GS, 3 );

	if( !strlen( RecordId ) )
	{
		dptr->trace( "RecordId is NULL...Cannot Process AlertDec Delete Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_RECORDID_NULL );
		return -1;
	}

	dptr->trace( "Processing ALERTDesc Delete Request for RecordId[%s]", RecordId );


	if( deleteAlertDesc( RecordId ) < 0 )
        {
                dptr->trace( "Error in Deleting RecordId[%s] in EzAlertDecMemory", RecordId );
                memset( ErrDesc, 0, sizeof( ErrDesc ) );
                strcpy( ErrDesc, GUI_ERR_ALERT_DELETE_MEMORY );
                return -1;
        }


	return 1;
}




int EzGUIAlertRequest :: processAlertRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing AlertRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process FIT request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process FIT request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_COMMANDTYPE );
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
			retval = processAlertAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processAlertDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processAlertUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid ALERT..GUI Command Received..." );
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



int EzGUIAlertRequest :: processAlertDescRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing AlertDescription Request[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process FIT request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_COMMAND );
		retval = -1;
		return -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process FIT request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_ALERT_COMMANDTYPE );
		retval = -1;
		return -1;
	}


	switch ( atoi( TempStr ) )
	{
		case GUI_ADD_CMD:
			retval = processAlertDescAdd( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processAlertDescDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processAlertDescUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid ALERTDESC..GUI Command Received..." );
			retval = -1;
	}

	return retval;
}
