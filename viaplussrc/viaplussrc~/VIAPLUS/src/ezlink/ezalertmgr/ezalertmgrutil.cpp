#include <ezlink/ezalertmgrutil.h>

int EzAlertMgrUtil :: initAlertMgrUtil( EzDebugUtil *dptr, EzAlertMemUtil *ezalertmemutil_ptr )
{
	this->dptr = dptr;
	this->ezalertmemutil_ptr = ezalertmemutil_ptr;
	return 1;
}

bool EzAlertMgrUtil :: BlankLine( const char *LineBuffer )
{
	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
			return false;
	}
	return true;
}

int EzAlertMgrUtil :: GetNColumns( const char *LineBuffer )
{
	bool FoundChar = true;
	int NCols = 0;

	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
		{
			if( FoundChar )
				NCols++;
			FoundChar = false;
		}
		else
			FoundChar = true;
	}

	return NCols;
}

int EzAlertMgrUtil :: GetString( const char *LineBuffer, char *ColStr, int Column )
{
	int j = 0;
	bool FoundChar = true;

	int FldCount = 0;

	for( int i = 0; i < strlen( LineBuffer ); i++ )
	{
		if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
		{
			if( FoundChar )
				FldCount++;
			FoundChar = false;
			if( FldCount == Column )
			{
				ColStr[ j ] = LineBuffer[ i ];
				j++;
			}
		}
		else
		{
			FoundChar = true;
			if( FldCount == Column )
				break;
		}
	}
	return 1;
}

int EzAlertMgrUtil :: composeATMAlertTemplate( struct AtmTableInfo atminforec, const char *ATMId, const char *StatusCode, const char *TemplateFile, char *Buffer )
{
	FILE *fptr;
	int NColumns, SqlErr;
	char TemplateFilePath[ ALERT_TEMPLATE_FILE_PATH_SIZE + 1 ], LineBuffer[ ALERT_LINE_BUFFER_SIZE + 1 ], ColStr[ ALERT_COL_STR_SIZE + 1 ];
	char LocalDate[ 20 ], LocalTime[ 20 ], StatusDesc[ 100 ], BrName[ 100 ];

	memset( TemplateFilePath, 0, sizeof( TemplateFilePath ) );
	sprintf( TemplateFilePath, "%s/%s/%s/%s/%s", getenv( "EZDIR_HOME"), "cfg", "atm", "alert", TemplateFile );
	fptr = fopen( TemplateFilePath, "r" );
	if( fptr == NULL )
	{
		dptr->trace( DEBUG_ERROR, "Error in Template File[%s]", TemplateFilePath );
		return -1;
	}
	while( !feof( fptr ) )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		fgets( LineBuffer, sizeof( LineBuffer ), fptr );

		if( BlankLine( LineBuffer ) )
			continue;

		NColumns = GetNColumns( LineBuffer );

		for( int i = 0; i < NColumns; i++ )
		{
			memset( ColStr, 0, sizeof( ColStr ) );
			GetString( LineBuffer, ColStr, i + 1 );
			if( !strcasecmp( ColStr, "$STATUSCODE" ) )
				strcat( Buffer, StatusCode );
			else if( !strcasecmp( ColStr, "$STATUSDESC" ) )
			{
				memset( StatusDesc, 0, sizeof( StatusDesc ) );
				if( ezalertmemutil_ptr->getAlertDesc( "ATM", StatusCode, StatusDesc ) < 0 )
					dptr->trace( "Error in getting Status Description for StatusCode[%s] ", StatusCode  );
				else
					strcat( Buffer, StatusDesc );
			}
			else if ( !strcasecmp( ColStr, "$SPACE" ) )
				strcat( Buffer, " " );
			else if ( !strcasecmp( ColStr, "$LF" ) )
				strcat( Buffer, "\n" );
			else if ( !strcasecmp( ColStr, "$ATMID" ) )
				strcat( Buffer, ATMId );
			else if ( !strcasecmp( ColStr, "$ATMLOCATION" ) )
			    strcat( Buffer, atminforec.AtmLocation );
			else if ( !strcasecmp( ColStr, "$ATMBRANCHCODE" ) )
				strcat( Buffer, atminforec.AcquirerBranchCode );
			else if ( !strcasecmp( ColStr, "$DATE" ) )
			{
				memset( LocalDate, 0, sizeof( LocalTime ) );
				sprintf( LocalDate, "%02d/%02d/%02d", ezdatetimeutil.getSysDay(), ezdatetimeutil.getSysMon(), ezdatetimeutil.getSysYear() );
				strcat( Buffer, LocalDate );
			}
			else if ( !strcasecmp( ColStr, "$TIME" ) )
			{
				memset( LocalTime, 0, sizeof( LocalTime ) );
				sprintf( LocalTime, "%02d:%02d:%02d", ezdatetimeutil.getSysHour(), ezdatetimeutil.getSysMin(), ezdatetimeutil.getSysSec() );
				strcat( Buffer, LocalTime );
			}
			else
				strcat( Buffer, ColStr );
		}
	}
	fclose( fptr );
	return 1;
}

int EzAlertMgrUtil :: composeNetworkAlertTemplate( EzNetworkUtil networkutilobj, const char *NetworkId, const char *StatusCode, const char *TemplateFile, char *Buffer )
{
	FILE *fptr;
	int NColumns;
	char TemplateFilePath[ ALERT_TEMPLATE_FILE_PATH_SIZE + 1 ], LineBuffer[ ALERT_LINE_BUFFER_SIZE + 1 ], ColStr[ ALERT_COL_STR_SIZE + 1 ];
	char LocalDate[ 20 ], LocalTime[ 20 ], StatusDesc[ 100 ];

	memset( TemplateFilePath, 0, sizeof( TemplateFilePath ) );
	sprintf( TemplateFilePath, "%s/%s/%s/%s/%s", getenv( "EZDIR_HOME"), "cfg", "alert", "atm", TemplateFile );
	fptr = fopen( TemplateFilePath, "r" );
	if( fptr == NULL )
	{
		dptr->trace( DEBUG_ERROR, "Error in Template File[%s]", TemplateFilePath );
		return -1;
	}
	while( !feof( fptr ) )
	{
		memset( LineBuffer, 0, sizeof( LineBuffer ) );
		fgets( LineBuffer, sizeof( LineBuffer ), fptr );

		if( BlankLine( LineBuffer ) )
			continue;

		NColumns = GetNColumns( LineBuffer );

		for( int i = 0; i < NColumns; i++ )
		{
			memset( ColStr, 0, sizeof( ColStr ) );
			GetString( LineBuffer, ColStr, i + 1 );
			if( !strcasecmp( ColStr, "$STATUSCODE" ) )
				strcat( Buffer, StatusCode );
			if( !strcasecmp( ColStr, "$STATUSDESC" ) )
			{
				memset( StatusDesc, 0, sizeof( StatusDesc ) );
				//if( getNetworkStatusDesc( atoi(StatusCode), StatusDesc ) < 0 )
					dptr->trace( "Error in getting Status Description for StatusCode[%s]", StatusCode );
				//else
					strcat( Buffer, StatusDesc );
			}
			else if ( !strcasecmp( ColStr, "$SPACE" ) )
				strcat( Buffer, " " );
			else if ( !strcasecmp( ColStr, "$LF" ) )
				strcat( Buffer, "\n" );
			else if ( !strcasecmp( ColStr, "$NTWKID" ) )
				strcat( Buffer, NetworkId );
			else if ( !strcasecmp( ColStr, "$NTWKNAME" ) )
				strcat( Buffer, networkutilobj.getNetworkName() );
			else if ( !strcasecmp( ColStr, "$NTWKPORT" ) )
				strcat( Buffer, networkutilobj.getNetworkPortName() );
			else if ( !strcasecmp( ColStr, "$DATE" ) )
			{
				memset( LocalDate, 0, sizeof( LocalTime ) );
				sprintf( LocalDate, "%02d/%02d/%02d", ezdatetimeutil.getSysDay(), ezdatetimeutil.getSysMon(), ezdatetimeutil.getSysYear() );
				strcat( Buffer, LocalDate );
			}
			else if ( !strcasecmp( ColStr, "$TIME" ) )
			{
				memset( LocalTime, 0, sizeof( LocalTime ) );
				sprintf( LocalTime, "%02d:%02d:%02d", ezdatetimeutil.getSysHour(), ezdatetimeutil.getSysMin(), ezdatetimeutil.getSysSec() );
				strcat( Buffer, LocalTime );
			}
			else
				strcat( Buffer, ColStr );
		}
	}
	fclose( fptr );
	return 1;
}

int EzAlertMgrUtil :: getPortType( const char *PortId, char *PortType )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], ParamStr[ 100 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", PortId, "PORTTYPE" );
	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching[%s] in File[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	else
	{
		strcpy( PortType, cfgval );
		cfgutil.cfg_close();
		return 1;
	}
}

int EzAlertMgrUtil :: getPortInstId( const char *PortId, char *InstId )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], ParamStr[ 100 ];

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "eznet.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( ParamStr, 0, sizeof( ParamStr ) );
	sprintf( ParamStr, "%s#%s", PortId, "INSTID" );
	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( ParamStr, cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching[%s] in File[%s]", ParamStr, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	else
	{
		strcpy( InstId, cfgval );
		cfgutil.cfg_close();
		return 1;
	}
}

int EzAlertMgrUtil :: composePortAlertTemplate( const char *InstId, const char *PortType, const char *PortId, const char *StatusCode, const char *TemplateFile, char *Buffer )
{
	return 1;
}

