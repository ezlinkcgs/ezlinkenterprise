#include <ezbusiness/ezgsmcmd.h>

int EzGSMCmd :: initGSMCmd( const char *TaskName )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], logpath[ LOG_PATH_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezgsmcmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^EzGsmCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( InitEzChLocateUtil( this, "ezgsmcmd" ) < 0 )
	{
		trace( "Error in Initializing EzChLocateUtil....");
		return -1;
	}

	if( LocateChannel( "EzSMSDriver" ) < 0 )
	{
		trace( "Error in Locating Channel EzSMSDriver" );
		return -1;
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXGSM", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching MAXGSM from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxGSM = atoi( cfgval );

	cfgutil.cfg_close();

	GSMMemoryId = CreateMemoryId( this, GSM_MEMORY_NAME );

	if( GSMMemoryId < 0 )
	{
		trace( "Error in Creating [%s] Memory", GSM_MEMORY_NAME );
		cfgutil.cfg_close();
		return -1;
	}

	trace( "GSM Memory Created with MemoryId[%d]", GSMMemoryId );

	GSMMemoryShmid = shmget( GSMMemoryId, 0, IPC_CREAT | 0666 );

	if( GSMMemoryShmid < 0 )
	{
		trace( "Error in Creating GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	GSMMemoryShmPtr = ( struct EzGSMInfoTable * ) shmat( GSMMemoryShmid, 0, 0 );

	if( GSMMemoryShmPtr == NULL )
	{
		trace( "Error in attaching GSM Shared Memory....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	GSMMemorySemid = semget( GSMMemoryId, 0, IPC_CREAT | 0666 );

	if( GSMMemorySemid < 0 )
	{
		trace( "Error in Creating GSM Semaphore....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
    return 1;
}

int EzGSMCmd :: searchGSMInfo( const char *GSMPort, struct EzGSMInfoTable *gsminfo_ptr )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			memcpy( gsminfo_ptr, GSMMemoryShmPtr + i, sizeof( struct EzGSMInfoTable ) );
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzGSMCmd :: searchGSMInfo( const char *GSMPort )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPort ) )
		{
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzGSMCmd :: getCurrGSMCount()
{
	struct sembuf sem_buf;
	int GSMCount = 0;

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME ) )
		{
			GSMCount++;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return GSMCount;
}

int EzGSMCmd :: sendSMS( const char *GSMPort, const char *Message, const char *MobileNo )
{

	if( searchGSMInfo( GSMPort ) < 0 )
	{
		trace( "Cannot Send SMS to Port GSMPort[%s]....Unable to Locate Port....", GSMPort );
		return -1;
	}

	struct EzSMSDriverMsg smsdrvrmsg;

	memset( &smsdrvrmsg, 0, sizeof( struct EzSMSDriverMsg ) );
	smsdrvrmsg.Command = SEND_SMS;
	strcpy( smsdrvrmsg.GSMPort, GSMPort );
	strcpy( smsdrvrmsg.MsgBuffer, Message );
	strcpy( smsdrvrmsg.MobileNo, MobileNo );

	if( WriteChannel( ( char * ) &smsdrvrmsg, sizeof( struct EzSMSDriverMsg ) ) < 0 )
	{
		trace( "Error in Writing add GSMPort Message to EzSMDriver Channel" );
		return -1;
	}
	trace( "Written Message to EzSMSDriver Channel....Qid[%d]", GetDestChannelQid() );
	return 1;

}

int EzGSMCmd :: addGSMPort( const char *GSMPort )
{
	struct EzSMSDriverMsg smsdrvrmsg;
	struct EzGSMInfoTable gsminfo_rec;
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], ParamStr[ 200 ];
	int CurrGSMCount;

	trace( DEBUG_TEST, "adding GSM Port[%s]", GSMPort );

	if( searchGSMInfo( GSMPort ) >= 0 )
	{
		trace( "Cannot Add....GSMPort[%s]....already added", GSMPort );
		return -1;
	}

	CurrGSMCount = getCurrGSMCount();
	if( CurrGSMCount >= MaxGSM )
	{
		trace( "Cannot Add....GSMPort[%s]....CurrentGSMCount[%d] has Reached MaxGSM[%d]", GSMPort, CurrGSMCount, MaxGSM );
		return -1;
	}

	memset( &gsminfo_rec, 0, sizeof( struct EzGSMInfoTable ) );
	strcpy( gsminfo_rec.GSMPort, GSMPort );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Protocol" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgval, "TCPIP" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_TCPIP;
	else if( !strcasecmp( cfgval, "SERIAL" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_SERIAL;
	else
	{
		trace( "Invalid Protocol Value[%s] from file[%s]....Protocol should be Serial/Tcpip....", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Address" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	strcpy( gsminfo_rec.GSMAddress, cfgval );

	if( gsminfo_rec.GSMProtocol == GSM_PROTOCOL_TCPIP )
	{
		memset( ParamStr, 0, sizeof( ParamStr ) );
		sprintf( ParamStr, "%s#%s", GSMPort, "PortNo" );

		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
			cfgutil.cfg_close();
			return -1;
		}
		gsminfo_rec.GSMPortNo = atoi( cfgval );
	}
	else
		gsminfo_rec.GSMPortNo = 0;

	cfgutil.cfg_close();

	memset( &smsdrvrmsg, 0, sizeof( struct EzSMSDriverMsg ) );
	smsdrvrmsg.Command = ADD_GSMPORT;
	strcpy( smsdrvrmsg.GSMPort, GSMPort );

	if( WriteChannel( ( char * ) &smsdrvrmsg, sizeof( struct EzSMSDriverMsg ) ) < 0 )
	{
		trace( "Error in Writing add GSMPort Message to EzSMDriver Channel" );
		return -1;
	}
	return 1;
}

int EzGSMCmd :: removeGSMPort( const char *GSMPort )
{
	struct EzSMSDriverMsg smsdrvrmsg;

	if( searchGSMInfo( GSMPort ) < 0 )
	{
		trace( "Cannot remove GSMPort[%s]....Cannot Locate GSMsmsdrvrmsgPort in GSMInfo Table...", GSMPort );
		return -1;
	}

	memset( &smsdrvrmsg, 0, sizeof( struct EzSMSDriverMsg ) );
	smsdrvrmsg.Command = REMOVE_GSMPORT;
	strcpy( smsdrvrmsg.GSMPort, GSMPort );

	if( WriteChannel( ( char * ) &smsdrvrmsg, sizeof( struct EzSMSDriverMsg ) ) < 0 )
	{
		trace( "Error in Writing add GSMPort Message to EzSMDriver Channel" );
		return -1;
	}
	return 1;

}

int EzGSMCmd :: startGSMPort( const char *GSMPort )
{
	struct EzSMSDriverMsg smsdrvrmsg;

	struct EzGSMInfoTable gsminfo_rec;
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE +1 ], ParamStr[ 200 ];

	trace( DEBUG_TEST, "Starting GSM Port[%s]", GSMPort );

	if( searchGSMInfo( GSMPort, &gsminfo_rec ) < 0 )
	{
		trace( "Error in Searching GSMPort[%s] in GSMInfo Table..", GSMPort );
		return -1;
	}

	if( gsminfo_rec.GSMStatus != GSM_STATUS_STOPPED )
	{
		trace( "Error in Starting GSMPort[%s]...First Stop the GSMPort before Starting..", GSMPort );
		return -1;
	}

	memset( &gsminfo_rec, 0, sizeof( struct EzGSMInfoTable ) );
	strcpy( gsminfo_rec.GSMPort, GSMPort );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezgsm.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Protocol" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( !strcasecmp( cfgval, "TCPIP" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_TCPIP;
	else if( !strcasecmp( cfgval, "SERIAL" ) )
		gsminfo_rec.GSMProtocol = GSM_PROTOCOL_SERIAL;
	else
	{
		trace( "Invalid Protocol Value[%s] from file[%s]....Protocol should be Serial/Tcpip....", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", GSMPort, "Address" );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	strcpy( gsminfo_rec.GSMAddress, cfgval );

	if( gsminfo_rec.GSMProtocol == GSM_PROTOCOL_TCPIP )
	{
		memset( ParamStr, 0, sizeof( ParamStr ) );
		sprintf( ParamStr, "%s#%s", GSMPort, "PortNo" );

		memset( cfgval, 0, sizeof( cfgval ) );
		if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
		{
			trace( "Error in Searching [%s] from file[%s]", ParamStr, cfgpath );
			cfgutil.cfg_close();
			return -1;
		}
		gsminfo_rec.GSMPortNo = atoi( cfgval );
	}
	else
		gsminfo_rec.GSMPortNo = 0;

	cfgutil.cfg_close();

	memset( &smsdrvrmsg, 0, sizeof( struct EzSMSDriverMsg ) );
	smsdrvrmsg.Command = START_GSMPORT;
	strcpy( smsdrvrmsg.GSMPort, GSMPort );

	if( WriteChannel( ( char * ) &smsdrvrmsg, sizeof( struct EzSMSDriverMsg ) ) < 0 )
	{
		trace( "Error in Writing add GSMPort Message to EzSMDriver Channel" );
		return -1;
	}
	return 1;

}

int EzGSMCmd :: stopGSMPort( const char *GSMPort )
{
	struct EzSMSDriverMsg smsdrvrmsg;

	if( searchGSMInfo( GSMPort ) < 0 )
	{
		trace( "Cannot remove GSMPort[%s]....Cannot Locate GSMPort in GSMInfo Table...", GSMPort );
		return -1;
	}

	memset( &smsdrvrmsg, 0, sizeof( struct EzSMSDriverMsg ) );
	smsdrvrmsg.Command = STOP_GSMPORT;
	strcpy( smsdrvrmsg.GSMPort, GSMPort );

	if( WriteChannel( ( char * ) &smsdrvrmsg, sizeof( struct EzSMSDriverMsg ) ) < 0 )
	{
		trace( "Error in Writing add GSMPort Message to EzSMDriver Channel" );
		return -1;
	}
	return 1;

}

int EzGSMCmd :: listGSMPort()
{
	struct sembuf sem_buf;
	char GSMProtocol[ 20 ], GSMConnectionStatus[ 20 ], GSMStatus[ 20 ];

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%16s%16s%16s%20s%20s", "GSMPort", "Protocol", "Address", "ConnectionStatus", "GSMStatus" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPORT_INIT_NAME ) )
		{
			memset( GSMProtocol, 0, sizeof( GSMProtocol ) );
			if( ( GSMMemoryShmPtr + i )->GSMProtocol == GSM_PROTOCOL_SERIAL )
				strcpy( GSMProtocol, "SERIAL" );
			else
				strcpy( GSMProtocol, "TCPIP" );

			memset( GSMConnectionStatus, 0, sizeof( GSMConnectionStatus ) );
			if( ( GSMMemoryShmPtr + i )->GSMConnectionStatus == GSM_STATUS_CONNECTED )
				strcpy( GSMConnectionStatus, "CONNECTED" );
			else
				strcpy( GSMConnectionStatus, "DISCONNECTED" );

			memset( GSMStatus, 0, sizeof( GSMStatus ) );
			if( ( GSMMemoryShmPtr + i )->GSMStatus == GSM_STATUS_INIT )
				strcpy( GSMStatus, "NOT-INITIALIZED" );
			else if( ( GSMMemoryShmPtr + i )->GSMStatus == GSM_STATUS_RUNNING )
				strcpy( GSMStatus, "RUNNING" );
			else if( ( GSMMemoryShmPtr + i )->GSMStatus == GSM_STATUS_STOPPED )
				strcpy( GSMStatus, "STOPPED" );

			printf( "\n%16s%16s%16s%20s%20s", ( GSMMemoryShmPtr + i )->GSMPort, GSMProtocol, ( GSMMemoryShmPtr + i )->GSMAddress, GSMConnectionStatus, GSMStatus );

		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
}

int EzGSMCmd :: listGSMPort( const char *GSMPortName )
{
	struct sembuf sem_buf;
	char GSMProtocol[ 20 ], GSMConnectionStatus[ 20 ], GSMStatus[ 20 ];

	int retval = -1;
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%16s%16s%16s%16s%16s", "GSMPort", "Protocol", "Address", "ConnectionStatus", "GSMStatus" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxGSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( GSMMemoryShmPtr + i )->GSMPort, GSMPortName ) )
		{
			retval = 1;
			memset( GSMProtocol, 0, sizeof( GSMProtocol ) );
			if( ( GSMMemoryShmPtr + i )->GSMProtocol == GSM_PROTOCOL_SERIAL )
				strcpy( GSMProtocol, "SERIAL" );
			else
				strcpy( GSMProtocol, "TCPIP" );

			memset( GSMConnectionStatus, 0, sizeof( GSMConnectionStatus ) );
			if( ( GSMMemoryShmPtr + i )->GSMConnectionStatus == GSM_STATUS_CONNECTED )
				strcpy( GSMConnectionStatus, "CONNECTED" );
			else
				strcpy( GSMConnectionStatus, "DISCONNECTED" );

			memset( GSMStatus, 0, sizeof( GSMStatus ) );
			if( ( GSMMemoryShmPtr + i )->GSMStatus == GSM_STATUS_INIT )
				strcpy( GSMStatus, "NOT-INITIALIZED" );
			else if( ( GSMMemoryShmPtr + i )->GSMStatus == GSM_STATUS_RUNNING )
				strcpy( GSMStatus, "RUNNING" );
			else if( ( GSMMemoryShmPtr + i )->GSMStatus == GSM_STATUS_STOPPED )
				strcpy( GSMStatus, "STOPPED" );

			printf( "\n%16s%16s%16s%16s%16s", ( GSMMemoryShmPtr + i )->GSMPort, GSMProtocol, ( GSMMemoryShmPtr + i )->GSMAddress, GSMConnectionStatus, GSMStatus );
			sem_buf.sem_op = 2;
			if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( GSMMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for GSMMemorySemid SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzGSMCmd :: serviceGSMCmd( int argc, char **argv )
{
	char command[ 100 ], SMSBuffer[ 512 ], MobileNo[ 20 ];
	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezgsmcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more" );
					continue;
				}
				addGSMPort( command );
				continue;
			}
			else if( !strcasecmp( command, "remove" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ...type help for more" );
					continue;
				}
				removeGSMPort( command );
				continue;
			}
			else if( !strcasecmp( command, "stop" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				stopGSMPort( command );
				continue;
			}
			else if( !strcasecmp( command, "start" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more" );
					continue;
				}
				startGSMPort( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					listGSMPort();
					continue;
				}
				listGSMPort( command );
				continue;
			}
			else if( !strcasecmp( command, "send" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more" );
					continue;
				}
				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				getCommand( SMSBuffer, 3 );
				if( strlen( SMSBuffer ) == 0 )
				{
					printf("\n invaild command ..type help for more" );
					continue;
				}
				memset( MobileNo, 0, sizeof( MobileNo ) );
				getCommand( MobileNo, 4 );
				if( strlen( MobileNo ) == 0 )
				{
					printf("\n invaild command ..type help for more" );
					continue;
				}
				sendSMS( command, SMSBuffer, MobileNo );
				continue;
			}
			else if( !strcasecmp( command, "help" ) )
			{
				printf("\n <add> <GSMPort>" );
				printf("\n <remove> <GSMPort>" );
				printf("\n <start> <GSMPort>" );
				printf("\n <stop> <GSMPort>" );
				printf("\n <send> <GSMPort> <SMS-Message> <MobileNo>" );
				printf("\n <list> <GSMPort>" );
				printf("\n <list>" );
			}
			else if( !strcasecmp( command, "quit" ) )
				break;
			else
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
		}
	}
	else
	{
		memset( command, 0, sizeof( command ) );
		strcpy( command, argv[ 1 ] );
		if( !strcasecmp( command, "add" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				addGSMPort( command );
			}
		}
		else if( !strcasecmp( command, "remove" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				removeGSMPort( command );
			}
		}
		else if( !strcasecmp( command, "start" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				startGSMPort( command );
			}
		}
		else if( !strcasecmp( command, "stop" ) )
		{
			if( argc == 2 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				stopGSMPort( command );
			}
		}
		else if( !strcasecmp( command, "send" ) )
		{
			if( argc == 2  || argc == 3 || argc == 4 )
				printf("\n invaild command ..type help for more" );
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
				strcpy( SMSBuffer, argv[ 3 ] );
				memset( MobileNo, 0, sizeof( MobileNo ) );
				strcpy( MobileNo, argv[ 4 ] );
				sendSMS( command, SMSBuffer, MobileNo );

			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			if( argc == 2 )
				listGSMPort();
			else
			{
				memset( command, 0, sizeof( command ) );
				strcpy( command, argv[ 2 ] );
				listGSMPort( command );
			}
		}
		else if( !strcasecmp( command, "help" ) )
		{
			printf("\n <add> <GSMPort>" );
			printf("\n <remove> <GSMPort>" );
			printf("\n <start> <GSMPort>" );
			printf("\n <stop> <GSMPort>" );
			printf("\n <send> <GSMPort> <SMS-Message> <MobileNo>" );
			printf("\n <list> <GSMPort>" );
			printf("\n <list>" );
		}
		else
		{
			printf("\n invaild command ..type help for more" );
		}
		printf( "\n" );
	}
}

int main( int argc, char **argv )
{
	EzGSMCmd gsmcmdobj;
	if( gsmcmdobj.initGSMCmd( argv[ 0 ] ) < 0 )
	{
		gsmcmdobj.trace( "^^^^^^^^^^^^^^^EzGSMCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		gsmcmdobj.closeDebug();
		exit( 0 );
	}
	gsmcmdobj.serviceGSMCmd( argc, argv );
	return 1;
}




