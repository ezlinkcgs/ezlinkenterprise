#include <ezbusiness/ezguicontroller.h>

int EzGUIChannelRequest :: initGUIChannelRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE +1 ], CfgVal[ CFG_VAL_SIZE + 1 ];

	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXCHANNELS", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching CHANNEL#MAXCHANNELS in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxChannels = atoi( CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXPORTCHANNELS", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Fetching CHANNEL#MAXPORTCHANNELS from file [%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	cfgutil.cfg_close();
	MaxPortChannels = atoi( CfgVal );

	if( attachChannelMemory() < 0 )
	{
		dptr->trace( "Error in Attaching Channel Memory..." );
		return -1;
	}

	if( attachChannelPortMgrMemory() < 0 )
	{
		dptr->trace( "Error in Attaching Channel Port Memory..." );
		return -1;
	}
	return 1;
}

int EzGUIChannelRequest :: attachChannelMemory()
{
	ChannelMgrId = LocateChannelId( dptr, "EzChannelMgr" );

	if( ChannelMgrId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EZCHANNELMGR Channel..." );
		return -1;
	}

	ChannelMgrShmId = shmget ( ( key_t ) ChannelMgrId, 0, IPC_CREAT | 0666 );

	if( ChannelMgrShmId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EzChannelMgr Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ChannelMgrShmPtr = ( struct EzChannelTable * ) shmat( ChannelMgrShmId, 0, 0 );

	if( ChannelMgrShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR, "Error in attaching EzChannelMgr Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ChannelMgrSemId = semget ( ( key_t ) ChannelMgrId, 0, IPC_CREAT | 0666 );

	if( ChannelMgrSemId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EzChannelMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzGUIChannelRequest :: attachChannelPortMgrMemory()
{
	ChannelPortMgrId = LocateChannelId( dptr, "EzChannelPortMgr" );

	if( ChannelPortMgrId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EZCHANNELPORTMGR Channel..." );
		return -1;
	}

	ChannelPortMgrShmId = shmget ( ( key_t ) ChannelPortMgrId, 0, IPC_CREAT | 0666 );

	if( ChannelPortMgrShmId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EzChannelPortMgr Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ChannelPortMgrShmPtr = ( struct EzChannelPortTable * ) shmat( ChannelPortMgrShmId, 0, 0 );

	if( ChannelPortMgrShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR, "Error in attaching EzChannelPortMgr Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ChannelPortMgrSemId = semget ( ( key_t ) ChannelPortMgrId, 0, IPC_CREAT | 0666 );

	if( ChannelPortMgrSemId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating EzChannelPortMgr Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzGUIChannelRequest :: getChannelTaskCount()
{
	struct sembuf sem_buf;
	int Count = 0;
	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}

		if( ( strcmp( ( ChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( ChannelMgrShmPtr +    i )->ChannelType == TASK_CHANNEL ) )
			Count ++;

		sem_buf.sem_op = 2;
		if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	return Count;
}

int EzGUIChannelRequest :: getNextChannelTaskRecord( struct EzChannelTable *channeltable_rec, int channeloffset )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}

		if( i == channeloffset )
		{
			retval = 1;
			memcpy( channeltable_rec, ChannelMgrShmPtr + i, sizeof( struct EzChannelTable ) );
			sem_buf.sem_op = 2;
			if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzGUIChannelRequest :: getChannelPortCount()
{
	struct sembuf sem_buf;
	int Count = 0;
	for( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ChannelPortMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelPortMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}

		if( ( strcmp( ( ChannelPortMgrShmPtr + i )->PortName, CHANNEL_INIT_NAME ) ) )
			Count ++;

		sem_buf.sem_op = 2;
		if( semop( ChannelPortMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelPortMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	return Count;
}

int EzGUIChannelRequest :: getNextChannelPortRecord( struct EzChannelPortTable *channelporttable_rec, int channeloffset )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxPortChannels; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ChannelPortMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelPortMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}

		if( i == channeloffset )
		{
			retval = 1;
			memcpy( channelporttable_rec, ChannelPortMgrShmPtr + i, sizeof( struct EzChannelPortTable ) );
			sem_buf.sem_op = 2;
			if( semop( ChannelPortMgrSemId, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelPortMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ChannelPortMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for Channel:PortMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzGUIChannelRequest :: getChannelMemoryCount()
{
	struct sembuf sem_buf;
	int Count = 0;
	for( int i = 0; i < MaxChannels; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}

		if( ( strcmp( ( ChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( ChannelMgrShmPtr +    i )->ChannelType == MEMORY_CHANNEL ) )
			Count ++;

		sem_buf.sem_op = 2;
		if( semop( ChannelMgrSemId, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for ChannelMgrChannel SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}
	return Count;
}

int EzGUIChannelRequest :: processChannelTaskRequest( const char *GuiReq )
{
	int ChannelTaskCount = 0, ChannelOffset = 0;
	char ChannelName[ GUI_TEMP_STR_SIZE + 1 ];
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	struct EzChannelTable channeltable_rec;
	ChannelTaskCount = getChannelTaskCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !ChannelOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "CHANNELTASK", GUI_GS , ChannelTaskCount, GUI_GS );

		for( int i = ChannelOffset; i < MaxChannels; i++ )
		{
			memset( &channeltable_rec, 0, sizeof( struct EzChannelTable ) );
			if( getNextChannelTaskRecord( &channeltable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th ChannelTaskRecord....", i );
				continue;
			}
			if( ( strcmp( channeltable_rec.ChannelName, CHANNEL_INIT_NAME ) ) && ( channeltable_rec.ChannelType == TASK_CHANNEL ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				if( LoadMsgQInfo( channeltable_rec.ChannelQid ) >= 0 )
				{
					memset( ChannelName, 0, sizeof( ChannelName ) );
					strcpy( ChannelName, channeltable_rec.ChannelName + 5 );
					sprintf( RecordString, "%s%c%d%c%d%c%d%c%d%c", ChannelName, GUI_FS,  channeltable_rec.ChannelQid, GUI_FS,  GetNMsg(), GUI_FS,  GetNBytes(), GUI_FS, GetMaxBytes(), GUI_RS );
				}
				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					ChannelOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}
			if( i + 1 == MaxChannels )
			{
					ChannelOffset = i + 1;
					break;
			}

		}
		if( ChannelOffset == MaxChannels )
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


int EzGUIChannelRequest :: processChannelPortRequest( const char *GuiReq )
{
	int ChannelPortCount = 0, ChannelPortOffset = 0;
	char ChannelName[ GUI_TEMP_STR_SIZE + 1 ];
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	struct EzChannelPortTable channelporttable_rec;

	ChannelPortCount = getChannelPortCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !ChannelPortOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "CHANNELPORT", GUI_GS , ChannelPortCount, GUI_GS );

		for( int i = ChannelPortOffset; i < MaxPortChannels; i++ )
		{
			memset( &channelporttable_rec, 0, sizeof( struct EzChannelPortTable ) );
			if( getNextChannelPortRecord( &channelporttable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th ChannelPortRecord....", i );
				continue;
			}
			if( strcmp( channelporttable_rec.PortName, CHANNEL_INIT_NAME ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				sprintf( RecordString, "%s%c%d%c%d%c", channelporttable_rec.PortName, GUI_FS,  channelporttable_rec.PortId, GUI_FS,  channelporttable_rec.NMessage, GUI_RS );
				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					ChannelPortOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}
			if( i + 1 == MaxPortChannels )
			{
					ChannelPortOffset = i + 1;
					break;
			}
			else
				strcat( GuiResp, RecordString );

		}
		if( ChannelPortOffset == MaxPortChannels )
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

int EzGUIChannelRequest :: processChannelMemoryRequest( const char *GuiReq )
{
	int ChannelMemoryCount = 0, ChannelOffset = 0;
	char ChannelName[ GUI_TEMP_STR_SIZE + 1 ];
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	struct EzChannelTable channeltable_rec;
	ChannelMemoryCount = getChannelMemoryCount();

	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !ChannelOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "CHANNELMEMORY", GUI_GS , ChannelMemoryCount, GUI_GS );

		for( int i = ChannelOffset; i < MaxChannels; i++ )
		{
			memset( &channeltable_rec, 0, sizeof( struct EzChannelTable ) );
			if( getNextChannelTaskRecord( &channeltable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th ChannelTaskRecord....", i );
				continue;
			}
			if( ( strcmp( channeltable_rec.ChannelName, CHANNEL_INIT_NAME ) ) && ( channeltable_rec.ChannelType == MEMORY_CHANNEL ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				memset( ChannelName, 0, sizeof( ChannelName ) );
				strcpy( ChannelName, channeltable_rec.ChannelName + 6 );
				sprintf( RecordString, "%s%c%d%c", ChannelName, GUI_FS,  channeltable_rec.ChannelKeyId,GUI_RS );
				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					ChannelOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}
			if( i + 1 == MaxChannels )
			{
					ChannelOffset = i + 1;
					break;
			}

		}
		if( ChannelOffset == MaxChannels )
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


