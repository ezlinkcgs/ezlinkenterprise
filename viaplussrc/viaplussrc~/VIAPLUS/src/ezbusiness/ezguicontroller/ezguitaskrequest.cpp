#include <ezbusiness/ezguicontroller.h>

int EzGUITaskRequest :: initGUITaskRequest( EzDebugUtil *dptr, EzTaskUtil *taskutil_ptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;
	this->taskutil_ptr = taskutil_ptr;
	MaxTasks = taskutil_ptr->GetMaxTask();
	return 1;
}

int EzGUITaskRequest :: processTaskList( const char *GuiReq )
{
	int TaskCount = 0, TaskOffset = 0;
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	char TaskStatus[ 20 ];
	struct EzTaskTable tasktable_rec;

	TaskCount = taskutil_ptr->getTaskCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !TaskOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "TASK", GUI_GS , TaskCount, GUI_GS );

		for( int i = TaskOffset; i < MaxTasks; i++ )
		{
			memset( &tasktable_rec, 0, sizeof( struct EzTaskTable ) );
			if( taskutil_ptr->getNextTaskRecord( &tasktable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th TaskRecord....", i );
				continue;
			}
			if ( ( strcmp( tasktable_rec.TaskName, TASK_INIT_NAME ) ) && ( tasktable_rec.TaskId != TASK_INIT_VAL ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				memset( TaskStatus, 0, sizeof( TaskStatus ) );
				if( tasktable_rec.TaskStatus == TASK_RUNNING )
						strcpy( TaskStatus, "RUNNING" );
				else
						strcpy( TaskStatus, "INIT" );

				sprintf( RecordString, "%s%c%d%c%d%c%s%c%s%c%s%c", tasktable_rec.TaskName, GUI_FS,  tasktable_rec.TaskId, GUI_FS, tasktable_rec.TraceLevel, GUI_FS, TaskStatus, GUI_FS,  tasktable_rec.StartDate, GUI_FS, tasktable_rec.StartTime, GUI_RS );
				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					TaskOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}

			if( i + 1 == MaxTasks )
			{
					TaskOffset = i + 1;
					break;
			}

		}
		if( TaskOffset == MaxTasks )
		{
			strcat( GuiResp, "\x0f" );
			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
				dptr->trace( "Error in Writing Message to Task Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
			break;
		}
		else
		{
			if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			{
				dptr->trace( "Error in Writing Message to Task Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
				break;
			}
		}
	}
	return 1;
}

int EzGUITaskRequest :: processTaskStart( const char *GuiReq )
{
	char TaskName[ 33 ];

	memset( TaskName, 0, sizeof( TaskName ) );
	tokenutil_ptr->getToken( GuiReq, TaskName, GUI_GS, 3 );

	if( !strlen( TaskName ) )
	{
		dptr->trace( "TaskName is NULL...Cannot Process Task Start Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_TASK_NULL );
		return -1;
	}
	dptr->trace( "Processing Task Start Request for Task[%s]...", TaskName );

	if( taskutil_ptr->StartTask( TaskName ) < 0 )
	{
		dptr->trace( "Cannot Start TaskName[%s].....", TaskName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_TASK_START );
		return -1;
	}
	return 1;
}

int EzGUITaskRequest :: processTaskStop( const char *GuiReq )
{
	char TaskName[ 33 ];

	memset( TaskName, 0, sizeof( TaskName ) );
	tokenutil_ptr->getToken( GuiReq, TaskName, GUI_GS, 3 );

	if( !strlen( TaskName ) )
	{
		dptr->trace( "TaskName is NULL...Cannot Process Task Stop Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_TASK_NULL );
		return -1;
	}
	dptr->trace( "Processing Task Stop Request for Task[%s]...", TaskName );

	if( taskutil_ptr->StopTask( TaskName ) < 0 )
	{
		dptr->trace( "Cannot Stop TaskName[%s].....", TaskName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_TASK_STOP );
		return -1;
	}
	return 1;
}

int EzGUITaskRequest :: processTaskRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing TaskRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Task request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_TASK_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Task request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_TASK_COMMANDTYPE );
		retval = -1;
	}

	if( retval < 0 )
	{
		RespFlag = 1;
		memset( GuiResp, 0, sizeof( GuiResp ) );
		sprintf( GuiResp, "%s%c%d%c%s", GuiReq, GUI_ES, RespFlag, GUI_ES, ErrDesc );
		if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			dptr->trace( "Error in Writing Message to Task Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
		return -1;
	}

	switch ( atoi( TempStr ) )
	{
		case GUI_LIST_CMD:
			retval = processTaskList( GuiReq );
		break;

		case GUI_START_CMD:
			retval = processTaskStart( GuiReq );
		break;

		case GUI_STOP_CMD:
			retval = processTaskStop( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Task..GUI Command Received..." );
			retval = -1;
	}

	if( atoi( TempStr ) != GUI_LIST_CMD && atoi( TempStr ) != GUI_START_CMD && atoi( TempStr ) != GUI_STOP_CMD )
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
			dptr->trace( "Error in Writing Message to Task Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
	}
	return retval;
}



