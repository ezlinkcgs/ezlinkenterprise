#include <ezbusiness/ezguicontroller.h>

int EzGUIPortRequest :: initGUIPortRequest( EzDebugUtil *dptr, EzChannelUtil *chutil_ptr, EzTokenUtil *tokenutil_ptr, EzGuiControllerODBC *dbutil_ptr, int MaxGuiBytes )
{
	this->dptr = dptr;
	this->chutil_ptr = chutil_ptr;
	this->tokenutil_ptr = tokenutil_ptr;
	this->dbutil_ptr = dbutil_ptr;
	this->MaxGuiBytes = MaxGuiBytes;
	this->MaxPorts = MaxPorts;

	if( InitEzCommUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing PortUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}

	if( initNetworkUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing NetworkUtil....");
		dptr->trace( "^^^^^^^^^^^EzGuiController Ended Abnormally^^^^^^^^^^^^^" );
		return -1;
	}
	MaxPorts = GetMaxPort();
	return 1;
}

int EzGUIPortRequest :: processPortList( const char *GuiReq )
{
	int PortCount = 0, PortOffset = 0;
	char GuiResp[ GUI_MAX_SIZE + 1 ], RecordString[ GUI_RECORD_SIZE + 1 ], TempStr[ GUI_TEMP_STR_SIZE + 1 ];
	char ConnStatus[ 50 ], ConnType[ 50 ];

	struct EzCommTable commtable_rec;

	PortCount = GetPortCount();
	while( 1 )
	{
		memset( GuiResp, 0, sizeof( GuiResp ) );
		if( !PortOffset )
			sprintf( GuiResp, "%c%s%c%d%c", GUI_STARTBIT, "PORT", GUI_GS , PortCount, GUI_GS );
		for( int i = PortOffset; i < MaxPorts; i++ )
		{
			memset( &commtable_rec, 0, sizeof( struct EzCommTable ) );
			if( getNextPortRecord( &commtable_rec, i ) < 0 )
			{
				dptr->trace( "Error in Getiing [%d]th PortRecord....", i );
				continue;
			}
			if ( ( strcmp( commtable_rec.PortName, PORT_INIT_NAME ) ) && ( commtable_rec.PortId != PORT_INIT_VAL ) )
			{
				memset( RecordString, 0, sizeof( RecordString ) );
				memset( ConnType, 0, sizeof( ConnType ) );
				if( commtable_rec.ApplType == TCPIP_SERVER )
					strcpy( ConnType, "SERVER" );
				else
					strcpy( ConnType, "CLIENT" );

				memset( ConnStatus, 0, sizeof( ConnStatus ) );
				if( commtable_rec.PortStatus == PORT_INIT )
					strcpy( ConnStatus, "INIT" );
				else if( commtable_rec.PortStatus == PORT_STOPPED )
					strcpy( ConnStatus, "STOPPED" );
				else if( commtable_rec.PortStatus == PORT_LISTEN )
					strcpy( ConnStatus, "LISTEN" );
				else if( commtable_rec.PortStatus == PORT_TRYING )
					strcpy( ConnStatus, "TRY_CONNECT" );
				else if( commtable_rec.PortStatus == PORT_CONNECTED )
					strcpy( ConnStatus, "CONNECTED" );

				sprintf( RecordString, "%s%c%s%c%d%c%s%c%d%c%s%c", commtable_rec.PortName, GUI_FS,  commtable_rec.IpAddress, GUI_FS, commtable_rec.PortNo, GUI_FS, ConnType, GUI_FS,  commtable_rec.PortId, GUI_FS, ConnStatus, GUI_RS );
				if( strlen( RecordString ) + strlen( GuiResp ) >= MaxGuiBytes )
				{
					PortOffset = i;
					break;
				}
				else
					strcat( GuiResp, RecordString );
			}

			if( i + 1 == MaxPorts )
			{
				PortOffset = i + 1;
				break;
			}
		}
		if( PortOffset == MaxPorts )
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

int EzGUIPortRequest :: addPortInFile( struct ezcommdrvrconfig drvrconfig )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], newcfgpath[ CFG_PATH_SIZE + 1 ], cfgparam[ CFG_VAL_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	char command[ 150 ];
	bool driver_start_found = false, driver_end_found = false;
	FILE *curr_fp, *new_fp, *pipe_ptr;
	EzDateTimeUtil ezdatetimeutil;
	char FBuffer[ 200 ], LineStr[ 200 ], backupfile[ 200 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]....cannot add port[%s]", cfgpath, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
		return -1;
	}

	memset( cfgparam, 0, sizeof( cfgparam ) );
	sprintf( cfgparam, "DRIVER#%s", drvrconfig.drivername );

	memset( cfgval ,0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( cfgparam, cfgval, 1 ) >= 0 )
	{
		dptr->trace( "Cannot add Port[%s]....PortName already exists in DRIVER_START_DEF in eznet.cfg file", drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_EXISTS );
		cfgutil.cfg_close();
		return -1;
	}

	memset( cfgval ,0, sizeof( cfgval ) );
	if( cfgutil.cfg_group_count( drvrconfig.drivername ) >= 0 )
	{
		dptr->trace( "Cannot add Port[%s]....%s_START_DEF already exists in eznet.cfg file", drvrconfig.drivername, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_EXISTS );
		cfgutil.cfg_close();
		return -1;
	}

	cfgutil.cfg_close();

	curr_fp = fopen( cfgpath, "r" );

	if( curr_fp == NULL )
	{
		dptr->trace( "Error in opening file[%s]....cannot add port[%s]", cfgpath, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
		return -1;
	}

	memset( newcfgpath, 0, sizeof( newcfgpath ) );
	sprintf( newcfgpath, "%s/%s/%s/%s.%06d%06d", getenv( "EZDIR_HOME" ), "cfg", "eznetbakfiles", "eznet.cfg.tmp", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );
	new_fp = fopen( newcfgpath, "w" );

	if( new_fp == NULL )
	{
		dptr->trace( "Error in opening file[%s]....cannot add port[%s]", newcfgpath, drvrconfig.drivername );
		fclose( curr_fp );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFGBACKUP_OPEN );
		return -1;
	}

	while( !feof( curr_fp ) )
	{
		memset( FBuffer, 0, sizeof( FBuffer ) );
		fgets( FBuffer, sizeof( FBuffer ), curr_fp );
		memset( LineStr, 0, sizeof( LineStr ) );
		for( int i = 0, j = 0; i < strlen( FBuffer ); i++ )
		{
			if( FBuffer[ i ] != '\t' && FBuffer[ i ] != '\n' && FBuffer[ i ] != '\r' && FBuffer[ i ] != ' ' )
			{
				LineStr[ j ] = FBuffer[ i ];
				j++;
			}
		}

		if( !strcmp( LineStr, "DRIVER_START_DEF" ) )
			driver_start_found = true;

		if( driver_start_found && !driver_end_found && !strcmp( LineStr, "END_DEF" ) )
		{
			fprintf( new_fp, "\t%s\n", drvrconfig.drivername );
			driver_end_found = true;
		}
		fprintf( new_fp, "%s", FBuffer );
	}

	fclose( curr_fp );

	fprintf( new_fp, "\n" );

	fprintf( new_fp, "\n%s_START_DEF", drvrconfig.drivername );
	fprintf( new_fp, "\n\tProtocol\tTCPIP" );

	if( drvrconfig.connectiontype == TCPIP_SERVER )
		fprintf( new_fp, "\n\tConnectionType\taccept" );
	else
		fprintf( new_fp, "\n\tConnectionType\tmake" );
	fprintf( new_fp, "\n\tIpAddress\t%s", drvrconfig.ipaddress );
	fprintf( new_fp, "\n\tPortNo\t%d", drvrconfig.portno );
	fprintf( new_fp, "\n\tDestChannel\t%s", drvrconfig.destchannel );
	fprintf( new_fp, "\n\tNConnections\t%d", drvrconfig.nconnections );
	if( drvrconfig.headertype == ASCII )
		fprintf( new_fp, "\n\tHeaderType\tascii" );
	else
		fprintf( new_fp, "\n\tHeaderType\thex" );

	fprintf( new_fp, "\n\tHeaderLen\t%d", drvrconfig.headerlen );
	if( drvrconfig.keepalive )
		fprintf( new_fp, "\n\tEnableKeepalive\tYes" );
	else
		fprintf( new_fp, "\n\tEnableKeepalive\tNo" );

	fprintf( new_fp, "\nEND_DEF" );
	fclose( new_fp );

	memset( backupfile, 0, sizeof( backupfile ) );
	sprintf( backupfile, "%s/%s/%s/%s.%06d_%06d", getenv( "EZDIR_HOME" ), "cfg", "eznetbakfiles", "eznet.cfg", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "cp %s %s", cfgpath, backupfile );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "cp %s %s", newcfgpath, cfgpath );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "rm %s", newcfgpath );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	int count = 0;
	bool fileflg = false;

	while( count < 5 )
	{
		if( cfgutil.cfg_open( cfgpath ) < 0 )
		{
			dptr->trace( "Error in opening file[%s]....cannot add port[%s]", cfgpath, drvrconfig.drivername );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
			return -1;
		}

		if( cfgutil.cfg_group_count( drvrconfig.drivername ) < 0 )
		{
			count++;
			sleep( 1 );
			cfgutil.cfg_close();
		}
		else
		{
			fileflg = true;
			cfgutil.cfg_close();
			break;
		}
	}

	if( !fileflg )
	{
		dptr->trace( "Cannot add Port[%s]....%s_START_DEF doesn't exists in eznet.cfg file", drvrconfig.drivername, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_EXISTS );
		return -1;
	}
	return 1;
}

int EzGUIPortRequest :: updatePortInFile( struct ezcommdrvrconfig drvrconfig )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], newcfgpath[ CFG_PATH_SIZE + 1 ], cfgparam[ CFG_VAL_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	char command[ 150 ];
	bool driver_start_found = false, driver_end_found = false;
	FILE *curr_fp, *new_fp, *pipe_ptr;
	EzDateTimeUtil ezdatetimeutil;
	char FBuffer[ 200 ], LineStr[ 200 ], backupfile[ 200 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]....cannot Update port[%s]", cfgpath, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
		return -1;
	}

	memset( cfgparam, 0, sizeof( cfgparam ) );
	sprintf( cfgparam, "DRIVER#%s", drvrconfig.drivername );

	memset( cfgval ,0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( cfgparam, cfgval, 1 ) < 0 )
	{
		dptr->trace( "Cannot Update Port[%s]....PortName doesn't exists in DRIVER_START_DEF in [%s]", drvrconfig.drivername, cfgpath );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_NOTEXISTS );
		cfgutil.cfg_close();
		return -1;
	}

	memset( cfgval ,0, sizeof( cfgval ) );
	if( cfgutil.cfg_group_count( drvrconfig.drivername ) < 0 )
	{
		dptr->trace( "Cannot Update Port[%s]....%s_START_DEF doesn't exists in [%s]", drvrconfig.drivername, drvrconfig.drivername, cfgpath );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_NOTEXISTS );
		cfgutil.cfg_close();
		return -1;
	}

	cfgutil.cfg_close();

	curr_fp = fopen( cfgpath, "r" );

	if( curr_fp == NULL )
	{
		dptr->trace( "Error in opening file[%s]....cannot update port[%s]", cfgpath, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
		return -1;
	}

	memset( newcfgpath, 0, sizeof( newcfgpath ) );
	sprintf( newcfgpath, "%s/%s/%s/%s.%06d%06d", getenv( "EZDIR_HOME" ), "cfg", "eznetbakfiles", "eznet.cfg.tmp", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );
	new_fp = fopen( newcfgpath, "w" );

	if( new_fp == NULL )
	{
		dptr->trace( "Error in opening file[%s]....cannot update port[%s]", newcfgpath, drvrconfig.drivername );
		fclose( curr_fp );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFGBACKUP_OPEN );
		return -1;
	}

	memset( cfgparam, 0, sizeof( cfgparam ) );
	sprintf( cfgparam, "%s_START_DEF", drvrconfig.drivername );

	driver_start_found = false;
	driver_end_found = false;


	memset( cfgparam, 0, sizeof( cfgparam ) );
	sprintf( cfgparam, "%s_START_DEF", drvrconfig.drivername );

	driver_start_found = false;
	driver_end_found = false;

	while( !feof( curr_fp ) )
	{
		memset( FBuffer, 0, sizeof( FBuffer ) );
		fgets( FBuffer, sizeof( FBuffer ), curr_fp );
		memset( LineStr, 0, sizeof( LineStr ) );
		for( int i = 0, j = 0; i < strlen( FBuffer ); i++ )
		{
			if( FBuffer[ i ] != '\t' && FBuffer[ i ] != '\n' && FBuffer[ i ] != '\r' && FBuffer[ i ] != ' ' )
			{
				LineStr[ j ] = FBuffer[ i ];
				j++;
			}
		}

		if( !strcmp( LineStr, cfgparam ) )
		{
			driver_start_found = true;
			continue;
		}

		if( !strcmp( LineStr, "END_DEF" ) && driver_start_found && !driver_end_found )
		{
			driver_end_found = true;
			continue;
		}

		if( driver_start_found && !driver_end_found )
			continue;

		fprintf( new_fp, "%s", FBuffer );
	}

	fclose( curr_fp );

	fprintf( new_fp, "\n" );

	fprintf( new_fp, "\n%s_START_DEF", drvrconfig.drivername );
	fprintf( new_fp, "\n\tProtocol\tTCPIP" );
	if( drvrconfig.connectiontype == TCPIP_SERVER )
		fprintf( new_fp, "\n\tConnectionType\taccept" );
	else
		fprintf( new_fp, "\n\tConnectionType\tmake" );
	fprintf( new_fp, "\n\tIpAddress\t%s", drvrconfig.ipaddress );
	fprintf( new_fp, "\n\tPortNo\t%d", drvrconfig.portno );
	fprintf( new_fp, "\n\tDestChannel\t%s", drvrconfig.destchannel );
	fprintf( new_fp, "\n\tNConnections\t%d", drvrconfig.nconnections );
	if( drvrconfig.headertype == ASCII )
		fprintf( new_fp, "\n\tHeaderType\tascii" );
	else
		fprintf( new_fp, "\n\tHeaderType\thex" );

	fprintf( new_fp, "\n\tHeaderLen\t%d", drvrconfig.headerlen );
	if( drvrconfig.keepalive )
		fprintf( new_fp, "\n\tEnableKeepalive\tYes" );
	else
		fprintf( new_fp, "\n\tEnableKeepalive\tNo" );

	fprintf( new_fp, "\nEND_DEF" );
	fclose( new_fp );

	memset( backupfile, 0, sizeof( backupfile ) );
	sprintf( backupfile, "%s/%s/%s/%s.%06d_%06d", getenv( "EZDIR_HOME" ), "cfg", "eznetbakfiles", "eznet.cfg", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "cp %s %s", cfgpath, backupfile );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "cp %s %s", newcfgpath, cfgpath );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "rm %s", newcfgpath );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	int count = 0;
	bool fileflg = false;

	while( count < 5 )
	{
		if( cfgutil.cfg_open( cfgpath ) < 0 )
		{
			dptr->trace( "Error in opening file[%s]....cannot add port[%s]", cfgpath, drvrconfig.drivername );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
			return -1;
		}

		if( cfgutil.cfg_group_count( drvrconfig.drivername ) < 0 )
		{
			count++;
			sleep( 1 );
			cfgutil.cfg_close();
		}
		else
		{
			fileflg = true;
			cfgutil.cfg_close();
			break;
		}
	}

	if( !fileflg )
	{
		dptr->trace( "Cannot add Port[%s]....%s_START_DEF doesn't exists in eznet.cfg file", drvrconfig.drivername, drvrconfig.drivername );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_EXISTS );
		return -1;
	}
	return 1;
}

int EzGUIPortRequest :: deletePortFromFile( const char *PortName )
{
	char NetworkId[ 17 ];
	memset( NetworkId, 0, sizeof( NetworkId ) );

	if( getNetworkIdFromPort( PortName, NetworkId ) >= 0 )
	{
		dptr->trace( "Cannot Delete PortName[%s]...PortName already configured for NetworkId[%s]", PortName, NetworkId );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_OTHER_NTWK );
		return -1;
	}

	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], newcfgpath[ CFG_PATH_SIZE + 1 ], cfgparam[ CFG_VAL_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	char command[ 150 ];
	bool driver_start_found = false, driver_end_found = false;
	FILE *curr_fp, *new_fp, *pipe_ptr;
	EzDateTimeUtil ezdatetimeutil;
	char FBuffer[ 200 ], LineStr[ 200 ], backupfile[ 200 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]....cannot add port[%s]", cfgpath, PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
		return -1;
	}

	memset( cfgparam, 0, sizeof( cfgparam ) );
	sprintf( cfgparam, "DRIVER#%s", PortName );

	memset( cfgval ,0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( cfgparam, cfgval, 1 ) < 0 )
	{
		dptr->trace( "Cannot Remove Port[%s]....PortName doesn't exists in DRIVER_START_DEF in [%s]", PortName, cfgpath );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_NOTEXISTS );
		cfgutil.cfg_close();
		return -1;
	}

	memset( cfgval ,0, sizeof( cfgval ) );
	if( cfgutil.cfg_group_count( PortName ) < 0 )
	{
		dptr->trace( "Cannot Remove Port[%s]....%s_START_DEF doesn't exists in [%s]", PortName, PortName, cfgpath );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_NOTEXISTS );
		cfgutil.cfg_close();
		return -1;
	}

	cfgutil.cfg_close();

	curr_fp = fopen( cfgpath, "r" );

	if( curr_fp == NULL )
	{
		dptr->trace( "Error in opening file[%s]....cannot add port[%s]", cfgpath, PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFG_OPEN );
		return -1;
	}

	memset( newcfgpath, 0, sizeof( newcfgpath ) );
	sprintf( newcfgpath, "%s/%s/%s/%s.%06d%06d", getenv( "EZDIR_HOME" ), "cfg", "eznetbakfiles", "eznet.cfg.tmp", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );
	new_fp = fopen( newcfgpath, "w" );

	if( new_fp == NULL )
	{
		dptr->trace( "Error in opening file[%s]....cannot remove port[%s]", newcfgpath, PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_EZNETCFGBACKUP_OPEN );
		fclose( curr_fp );
		return -1;
	}

	while( !feof( curr_fp ) )
	{
		memset( FBuffer, 0, sizeof( FBuffer ) );
		fgets( FBuffer, sizeof( FBuffer ), curr_fp );
		memset( LineStr, 0, sizeof( LineStr ) );
		for( int i = 0, j = 0; i < strlen( FBuffer ); i++ )
		{
			if( FBuffer[ i ] != '\t' && FBuffer[ i ] != '\n' && FBuffer[ i ] != '\r' && FBuffer[ i ] != ' ' )
			{
				LineStr[ j ] = FBuffer[ i ];
				j++;
			}
		}

		if( !strcmp( LineStr, "DRIVER_START_DEF" ) )
			driver_start_found = true;

		if( !strcmp( LineStr, "END_DEF" ) && driver_start_found && !driver_end_found )
		{
			fprintf( new_fp, "%s", FBuffer );
			driver_end_found = true;
			break;
		}

		if( driver_start_found && !driver_end_found && !strcmp( LineStr, PortName ) )
			continue;

		fprintf( new_fp, "%s", FBuffer );
	}

	memset( cfgparam, 0, sizeof( cfgparam ) );
	sprintf( cfgparam, "%s_START_DEF", PortName );

	driver_start_found = false;
	driver_end_found = false;

	while( !feof( curr_fp ) )
	{
		memset( FBuffer, 0, sizeof( FBuffer ) );
		fgets( FBuffer, sizeof( FBuffer ), curr_fp );
		memset( LineStr, 0, sizeof( LineStr ) );
		for( int i = 0, j = 0; i < strlen( FBuffer ); i++ )
		{
			if( FBuffer[ i ] != '\t' && FBuffer[ i ] != '\n' && FBuffer[ i ] != '\r' && FBuffer[ i ] != ' ' )
			{
				LineStr[ j ] = FBuffer[ i ];
				j++;
			}
		}

		if( !strcmp( LineStr, cfgparam ) )
		{
			driver_start_found = true;
			continue;
		}

		if( !strcmp( LineStr, "END_DEF" ) && driver_start_found && !driver_end_found )
		{
			driver_end_found = true;
			continue;
		}

		if( driver_start_found && !driver_end_found )
			continue;

		fprintf( new_fp, "%s", FBuffer );
	}

	fclose( curr_fp );

	fclose( new_fp );

	memset( backupfile, 0, sizeof( backupfile ) );
	sprintf( backupfile, "%s/%s/%s/%s.%06d_%06d", getenv( "EZDIR_HOME" ), "cfg", "eznetbakfiles", "eznet.cfg", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "cp %s %s", cfgpath, backupfile );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "cp %s %s", newcfgpath, cfgpath );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	memset( command, 0, sizeof( command ) );
	sprintf( command, "rm %s", newcfgpath );

	pipe_ptr = popen( command, "r" );

	if( pipe_ptr == NULL )
	{
		dptr->trace( "Error in opening pipe...SysErr[%s]", strerror( errno ) );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_PIPE );
		return -1;
	}

	pclose( pipe_ptr );

	return 1;
}

int EzGUIPortRequest :: processPortAdd( const char *GuiReq )
{
	struct ezcommdrvrconfig drvrconfig;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ];

	memset( &drvrconfig, 0, sizeof( struct ezcommdrvrconfig ) );
	memset( drvrconfig.drivername, 0, sizeof( drvrconfig.drivername ) );
	tokenutil_ptr->getToken( GuiReq, drvrconfig.drivername, GUI_GS, 3 );

	dptr->trace( "Processing Port Add Request for Port[ %s ]...", drvrconfig.drivername );

	if( !strlen( drvrconfig.drivername ) )
	{
		dptr->trace( "Cannot Process Port Add Request...PortName is Null...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_NULL );
		return -1;
	}

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 5 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Cannot Process Port Add Request...ConnectionType is Null...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_CONNECTIONTYPE_NULL );
		return -1;
	}

	dptr->trace( "ConnectionType[%s]", TempStr );

	if( !strcasecmp( TempStr, "accept" ) )
		drvrconfig.connectiontype = TCPIP_SERVER;
	else if( !strcasecmp( TempStr, "make" ) )
		drvrconfig.connectiontype = TCPIP_CLIENT;
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_CONNECTIONTYPE_INVALID );
		dptr->trace( "Cannot Process Port Add Request...Connection Type is not make/accept" );
		return -1;
	}

	if( drvrconfig.connectiontype == TCPIP_SERVER )
	{
		memset( drvrconfig.ipaddress, 0, sizeof( drvrconfig.ipaddress ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.ipaddress, GUI_GS, 6 );

		if( !strlen( drvrconfig.ipaddress ) )
		{
			dptr->trace( "Cannot Process Port Add Request...IpAddress is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_IPADDRESS_NULL );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 7 );

		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...PortNo is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_NULL );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			dptr->trace( "Cannot Process Port Add Request...PortNo is Not Numeric...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_INVALID );
			return -1;
		}

		drvrconfig.portno = atoi( TempStr );

		memset( drvrconfig.destchannel, 0, sizeof( drvrconfig.destchannel ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.destchannel, GUI_GS, 8 );

		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...DestChannel is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_DESTCHANNEL_NULL );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 9 );
		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...NConnections is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_NULL );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			dptr->trace( "Cannot Process Port Add Request...NConnections is Not Numeric...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_INVALID );
			return -1;
		}

		drvrconfig.nconnections = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 10 );
		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...HeaderType is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERTYPE_NULL );
			return -1;
		}

		if( !strcasecmp( TempStr, "hex" ) )
			drvrconfig.headertype = HEX;
		else
			drvrconfig.headertype = ASCII;

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 11 );
		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...HeaderLen is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_NULL );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			dptr->trace( "Cannot Process Port Add Request...HeaderLen is Not Numeric...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_INVALID );
			return -1;
		}
		drvrconfig.headerlen = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 12 );
		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...Keepalive is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_KEEPALIVE_NULL );
			return -1;
		}
		if( !strcasecmp( TempStr, "Yes" ) )
			drvrconfig.keepalive = true;
		else
			drvrconfig.keepalive = false;
	}
	else
	{
		memset( drvrconfig.ipaddress, 0, sizeof( drvrconfig.ipaddress ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.ipaddress, GUI_GS, 6 );

		if( !strlen( drvrconfig.ipaddress ) )
		{
			dptr->trace( "Cannot Process Port Add Request...IpAddress is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_IPADDRESS_NULL );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 7 );

		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_NULL );
			dptr->trace( "Cannot Process Port Add Request...PortNo is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			dptr->trace( "Cannot Process Port Add Request...PortNo is Not Numeric...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_INVALID );
			return -1;
		}

		drvrconfig.portno = atoi( TempStr );

		memset( drvrconfig.destchannel, 0, sizeof( drvrconfig.destchannel ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.destchannel, GUI_GS, 8 );

		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...DestChannel is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_DESTCHANNEL_NULL );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 9 );
		if( !strlen( TempStr ) )
		{
			dptr->trace( "Cannot Process Port Add Request...NConnections is Null...." );
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_NULL );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_INVALID );
			dptr->trace( "Cannot Process Port Add Request...NConnections is Not Numeric...." );
			return -1;
		}
		drvrconfig.nconnections = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 10 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERTYPE_NULL );
			dptr->trace( "Cannot Process Port Add Request...HeaderType is Null...." );
			return -1;
		}
		if( !strcasecmp( TempStr, "hex" ) )
			drvrconfig.headertype = HEX;
		else
			drvrconfig.headertype = ASCII;

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 11 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_NULL );
			dptr->trace( "Cannot Process Port Add Request...HeaderLen is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_INVALID );
			dptr->trace( "Cannot Process Port Add Request...HeaderLen is Not Numeric...." );
			return -1;
		}
		drvrconfig.headerlen = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 12 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_KEEPALIVE_NULL );
			dptr->trace( "Cannot Process Port Add Request...Keepalive is Null...." );
			return -1;
		}

		if( !strcasecmp( TempStr, "Yes" ) )
			drvrconfig.keepalive = true;
		else
			drvrconfig.keepalive = false;
	}

	if( addPortInFile( drvrconfig ) < 0 )
	{
		dptr->trace( "Error in Servicing Port Add Command for Port[ %s ]", drvrconfig.drivername );
		return -1;
	}

	if( AddPort( drvrconfig.drivername ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_ADD_MEMORY );
		dptr->trace( DEBUG_ERROR, "Error in Adding Port[ %s ] in PortMemory", drvrconfig.drivername );
		return -1;
	}

	return 1;
}

int EzGUIPortRequest :: processPortDelete( const char *GuiReq )
{
	char PortName[ 33 ];

	memset( PortName, 0, sizeof( PortName ) );
	tokenutil_ptr->getToken( GuiReq, PortName, GUI_GS, 3 );

	if( !strlen( PortName ) )
	{
		dptr->trace( "PortName is NULL...Cannot Process Port Remove Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_NULL );
		return -1;
	}
	dptr->trace( "Processing Port Remove Request for Port[%s]...", PortName );

	if( deletePortFromFile( PortName ) < 0 )
	{
		dptr->trace( "Error in deleting Port File...Cannot Process Port Remove Request...." );
		return -1;
	}

	if( StopPort( PortName ) < 0 )
	{
		dptr->trace( "Cannot Stop PortName[%s].....", PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_NETWORK_NULL );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_STOP );
		return -1;
	}

	if( RemovePort( PortName ) < 0 )
	{
		dptr->trace( "Cannot remove PortName[%s] from Port Memory...", PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_DELETE_MEMORY );
		return -1;
	}
	return 1;
}

int EzGUIPortRequest :: processPortUpdate( const char *GuiReq )
{
	struct ezcommdrvrconfig drvrconfig;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ];

	memset( &drvrconfig, 0, sizeof( struct ezcommdrvrconfig ) );
	memset( drvrconfig.drivername, 0, sizeof( drvrconfig.drivername ) );
	tokenutil_ptr->getToken( GuiReq, drvrconfig.drivername, GUI_GS, 3 );

	dptr->trace( "Processing Port Update Request for Port[ %s ]...", drvrconfig.drivername );

	if( !strlen( drvrconfig.drivername ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_NULL );
		dptr->trace( "Cannot Process Port Update Request...PortName is Null...." );
		return -1;
	}

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 5 );

	if( !strlen( TempStr ) )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_CONNECTIONTYPE_NULL );
		dptr->trace( "Cannot Process Port Update Request...ConnectionType is Null...." );
		return -1;
	}

	if( !strcasecmp( TempStr, "accept" ) )
		drvrconfig.connectiontype = TCPIP_SERVER;
	else if( !strcasecmp( TempStr, "make" ) )
		drvrconfig.connectiontype = TCPIP_CLIENT;
	else
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_CONNECTIONTYPE_INVALID );
		dptr->trace( "Cannot Process Port Update Request...Connection Type is not make/accept" );
		return -1;
	}

	if( drvrconfig.connectiontype == TCPIP_SERVER )
	{
		memset( drvrconfig.ipaddress, 0, sizeof( drvrconfig.ipaddress ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.ipaddress, GUI_GS, 6 );

		if( !strlen( drvrconfig.ipaddress ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_IPADDRESS_NULL );
			dptr->trace( "Cannot Process Port Update Request...IpAddress is Null...." );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 7 );

		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_NULL );
			dptr->trace( "Cannot Process Port Update Request...PortNo is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_INVALID );
			dptr->trace( "Cannot Process Port Update Request...PortNo is Not Numeric...." );
			return -1;
		}

		drvrconfig.portno = atoi( TempStr );

		memset( drvrconfig.destchannel, 0, sizeof( drvrconfig.destchannel ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.destchannel, GUI_GS, 8 );

		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_DESTCHANNEL_NULL );
			dptr->trace( "Cannot Process Port Update Request...DestChannel is Null...." );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 9 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_NULL );
			dptr->trace( "Cannot Process Port Update Request...NConnections is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_INVALID );
			dptr->trace( "Cannot Process Port Update Request...NConnections is Not Numeric...." );
			return -1;
		}

		drvrconfig.nconnections = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 10 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERTYPE_NULL );
			dptr->trace( "Cannot Process Port Update Request...HeaderType is Null...." );
			return -1;
		}

		if( !strcasecmp( TempStr, "hex" ) )
			drvrconfig.headertype = HEX;
		else
			drvrconfig.headertype = ASCII;

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 11 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_NULL );
			dptr->trace( "Cannot Process Port Update Request...HeaderLen is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_INVALID );
			dptr->trace( "Cannot Process Port Update Request...HeaderLen is Not Numeric...." );
			return -1;
		}
		drvrconfig.headerlen = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 12 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_KEEPALIVE_NULL );
			dptr->trace( "Cannot Process Port Update Request...Keepalive is Null...." );
			return -1;
		}
		if( !strcasecmp( TempStr, "Yes" ) )
			drvrconfig.keepalive = true;
		else
			drvrconfig.keepalive = false;
	}
	else
	{
		memset( drvrconfig.ipaddress, 0, sizeof( drvrconfig.ipaddress ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.ipaddress, GUI_GS, 6 );

		if( !strlen( drvrconfig.ipaddress ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_IPADDRESS_NULL );
			dptr->trace( "Cannot Process Port Update Request...IpAddress is Null...." );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 7 );

		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_NULL );
			dptr->trace( "Cannot Process Port Update Request...PortNo is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_PORTNO_INVALID );
			dptr->trace( "Cannot Process Port Update Request...PortNo is Not Numeric...." );
			return -1;
		}

		drvrconfig.portno = atoi( TempStr );

		memset( drvrconfig.destchannel, 0, sizeof( drvrconfig.destchannel ) );
		tokenutil_ptr->getToken( GuiReq, drvrconfig.destchannel, GUI_GS, 8 );

		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_DESTCHANNEL_NULL );
			dptr->trace( "Cannot Process Port Update Request...DestChannel is Null...." );
			return -1;
		}

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 9 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_NULL );
			dptr->trace( "Cannot Process Port Update Request...NConnections is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_NCONNECTIONS_INVALID );
			dptr->trace( "Cannot Process Port Update Request...NConnections is Not Numeric...." );
			return -1;
		}
		drvrconfig.nconnections = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 10 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERTYPE_NULL );
			dptr->trace( "Cannot Process Port Update Request...HeaderType is Null...." );
			return -1;
		}
		if( !strcasecmp( TempStr, "hex" ) )
			drvrconfig.headertype = HEX;
		else
			drvrconfig.headertype = ASCII;

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 11 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_NULL );
			dptr->trace( "Cannot Process Port Update Request...HeaderLen is Null...." );
			return -1;
		}

		if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_HEADERLEN_INVALID );
			dptr->trace( "Cannot Process Port Update Request...HeaderLen is Not Numeric...." );
			return -1;
		}
		drvrconfig.headerlen = atoi( TempStr );

		memset( TempStr, 0, sizeof( TempStr ) );
		tokenutil_ptr->getToken( GuiReq, TempStr, GUI_GS, 12 );
		if( !strlen( TempStr ) )
		{
			memset( ErrDesc, 0, sizeof( ErrDesc ) );
			strcpy( ErrDesc, GUI_ERR_PORT_KEEPALIVE_NULL );
			dptr->trace( "Cannot Process Port Update Request...Keepalive is Null...." );
			return -1;
		}

		if( !strcasecmp( TempStr, "Yes" ) )
			drvrconfig.keepalive = true;
		else
			drvrconfig.keepalive = false;
	}

	if( updatePortInFile( drvrconfig ) < 0 )
	{
		dptr->trace( "Error in Servicing Port Update Command for Port[ %s ]", drvrconfig.drivername );
		return -1;
	}

	if( StopPort( drvrconfig.drivername ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_STOP );
		dptr->trace( DEBUG_ERROR, "Error in Stopping Port[ %s ]", drvrconfig.drivername );
		return -1;
	}

	if( StartPort( drvrconfig.drivername ) < 0 )
	{
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_START );
		dptr->trace( DEBUG_ERROR, "Error in Starting Port[ %s ]", drvrconfig.drivername );
		return -1;
	}
	return 1;
}

int EzGUIPortRequest :: processPortStart( const char *GuiReq )
{
	char PortName[ 33 ];

	memset( PortName, 0, sizeof( PortName ) );
	tokenutil_ptr->getToken( GuiReq, PortName, GUI_GS, 3 );

	if( !strlen( PortName ) )
	{
		dptr->trace( "PortName is NULL...Cannot Process Port Start Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_NULL );
		return -1;
	}
	dptr->trace( "Processing Port Start Request for Port[%s]...", PortName );

	if( StartPort( PortName ) < 0 )
	{
		dptr->trace( "Cannot Start PortName[%s].....", PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_START );
		return -1;
	}
	return 1;
}

int EzGUIPortRequest :: processPortStop( const char *GuiReq )
{
	char PortName[ 33 ];

	memset( PortName, 0, sizeof( PortName ) );
	tokenutil_ptr->getToken( GuiReq, PortName, GUI_GS, 3 );

	if( !strlen( PortName ) )
	{
		dptr->trace( "PortName is NULL...Cannot Process Port Stop Request...." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_NULL );
		return -1;
	}
	dptr->trace( "Processing Port Stop Request for Port[%s]...", PortName );

	if( StopPort( PortName ) < 0 )
	{
		dptr->trace( "Cannot Stop PortName[%s].....", PortName );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_STOP );
		return -1;
	}
	return 1;
}

int EzGUIPortRequest :: processPortRequest( const char *GuiReq )
{
	int retval = 1, RespFlag;
	char TempStr[ GUI_TEMP_STR_SIZE + 1 ], GuiResp[ GUI_MAX_SIZE + 1 ];

	dptr->trace( "Processing PortRequest[%s]", GuiReq );

	memset( TempStr, 0, sizeof( TempStr ) );
	tokenutil_ptr->getToken( GuiReq, TempStr, 0x1c, 2 );

	if( !strlen( TempStr ) )
	{
		dptr->trace( "Command Code is NULL..cannot Process Port request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_COMMAND );
		retval = -1;
	}

	if( tokenutil_ptr->CheckInteger( TempStr ) < 0 )
	{
		dptr->trace( "Command Code is not Numeric..cannot Process Port request..." );
		memset( ErrDesc, 0, sizeof( ErrDesc ) );
		strcpy( ErrDesc, GUI_ERR_PORT_COMMANDTYPE );
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
			retval = processPortList( GuiReq );
		break;

		case GUI_ADD_CMD:
			retval = processPortAdd( GuiReq );
		break;

		case GUI_START_CMD:
			retval = processPortStart( GuiReq );
		break;

		case GUI_STOP_CMD:
			retval = processPortStop( GuiReq );
		break;

		case GUI_REMOVE_CMD:
			retval = processPortDelete( GuiReq );
		break;

		case GUI_UPDATE_CMD:
			retval = processPortUpdate( GuiReq );
		break;

		default:
			dptr->trace( "Invalid Port..GUI Command Received..." );
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
			sprintf( GuiResp, "%s%c%d", GuiReq, GUI_ES, RespFlag );
		}

		if( chutil_ptr->WritePortChannel( chutil_ptr->GetLastSenderChannelName(), GuiResp, strlen( GuiResp ) ) < 0 )
			dptr->trace( "Error in Writing Message to Port Channel[%s]...", chutil_ptr->GetLastSenderChannelName() );
	}
	return retval;
}


