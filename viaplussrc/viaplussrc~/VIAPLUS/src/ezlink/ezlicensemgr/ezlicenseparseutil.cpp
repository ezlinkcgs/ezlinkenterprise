#include <ezlink/ezlicenseparseutil.h>

void EzLicenseParseUtil :: get_line()
{
	NEXT_LINE = true;
	int i = 0;
	for( i = 0; i < strlen( line_str ); i++ )
	{
		if( ( line_str[ i ] == '#' ) || ( line_str[ i ] == '\n' ) || ( line_str[ i ] == '\r' ) )
			break;
	}
	offset = i;
}

/* Function for Getting a Line */
int getStringLine( char *strbuffer, char *line_str, int Offset )
{
	int count = 0;
	for( int i = Offset, j = 0; i < strlen( strbuffer ); i++ )
	{
		if( strbuffer[ i ] == '\n' )
			break;
		else
		{
			line_str[ j ] = strbuffer[ i ];
			j++;
			count++;
		}
	}
	return count + 1;
}

/* Function for Checking the blank line */

bool EzLicenseParseUtil :: blank_line()
{
	for( int i = 0; i < strlen( line_str ); i++ )
	{
		if( ( line_str[ i ] != ' ' ) && ( line_str[ i ] != '\t' ) && ( line_str[ i ] != '\n' ) )
		{
			if( line_str[ i ] == '#' )
				return true;
			else
				return false;
		}
	}
	return true;
}

/* Function for getting the number of parameters in a line */

void EzLicenseParseUtil :: get_param_count()
{
	bool foundChar = true;
	nparam = 0;
	for( int i = 0; i < strlen( buf ); i++ )
	{
		if( ( buf[ i ] != ' ' ) && ( buf[ i ] != '\t' ) && ( buf[ i ] != '\n' ) )
		{
			if( foundChar )
				nparam++;
			foundChar = false;
		}
		else
			foundChar = true;
	}
}

/* Function for Getting Paramater */

void EzLicenseParseUtil :: get_param()
{
	int j = 0;
	bool foundChar = true;
	fld_count = 0;
	memset( param_val, 0, sizeof( param_val ) );

	for( int i = 0; i < strlen( buf ); i++ )
	{
		if( ( buf[ i ] != ' ' ) && ( buf[ i ] != '\t' ) && ( buf[ i ] != '\n' ) )
		{
			if( foundChar )
				fld_count++;
			foundChar = false;
			if( fld_count == param_count )
			{
				param_val[ j ] = buf[ i ];
				j++;
			}
		}
		else
		{
			foundChar = true;
			if( fld_count == param_count )
			{
				break;
			}
		}
	}
}

int EzLicenseParseUtil :: get_gpcount( const char *param )
{
	int count = 0;
	for( int i = 0; i < strlen( param ); i++ )
	{
		if( param[ i ] == PARSEGROUP_SEPARATOR )
			count++;
	}
	return count;
}

void EzLicenseParseUtil :: get_gpname( const char *param, char *name, int gpcount )
{
	int count = 0;
	int i = 0;
	for( i = 0; i < strlen( param ); i++ )
	{
		if( count == gpcount )
			break;
		else if( param[ i ] == PARSEGROUP_SEPARATOR )
			count++;
	}
	for( int j = i; j < strlen( param ); j++ )
	{
		if( param[ j ] == PARSEGROUP_SEPARATOR )
			break;
		else
		{
			*name = param[ j ];
			name++;
		}
	}
	if( gpcount < ngroup )
		strcat( gpname, PARSESTART_GROUP_DEF );
}

/* Function for Getting the parameter for a given group for a given line passed as param_num */

int EzLicenseParseUtil :: cfg_get_param( char *strbuffer, const char *param, char *value, int param_num )
{
	int Len;

	found = false;
	end_flg = false;
	start_flg = false;
	memset( buf, 0, sizeof( buf ) );
	offset = 0;
	boffset = 0;
	gpcount = 0;
	gpcnt = 0;
	start_group = 0;
	ngroup = get_gpcount( param ) ;
	memset( gpname, 0, sizeof( gpname ) );
	Len = 0;

	while ( Len < strlen( strbuffer ) )
	{
		memset( line_str, 0, sizeof( line_str ) );
		Len += getStringLine( strbuffer, line_str, Len );

		if( blank_line() )
			continue;

		get_line();

		memset( buf, 0, sizeof( buf ) );
		strncpy( buf + boffset, line_str, offset );

		if( ( ngroup == gpcount ) && ( !found ) )
		{
			/* Sub-Group Found */
			/* Search for the String */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			strcat( gpname, PARSESTART_GROUP_DEF );
			param_count = 1;
			get_param();
			/* Check whether the string is a start group definition */
			if( ( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) ) && ( strcmp( param_val, gpname ) ) )
				start_group++;

			/* Check whether the string is a end group definition */
			else if ( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
			{
				if( !start_group )
				{
					end_flg = true;
					break;
				}
				else
					start_group--;
			}
			/* Check for the actual string */
			else if ( ( !strcmp( gpname, param_val ) ) && ( !start_group ) )
			{
				start_group = ngroup + 1;
				found = true;
			}
		}
		/* After the actual string is found search for the END_GROUP Count */
		else if( found )
		{
			/* Increment the group count until END_GROUP is found */
			param_count = 1;
			get_param();
			if( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
				start_group--;
			if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
			if( !start_group )
			{
				end_flg = true;
				break;
			}
			if( start_group < ngroup + 1 )
				start_flg = true;
			if( ( strcmp( param_val, PARSEEND_GROUP_DEF ) ) && ( strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) ) && ( start_group == ngroup + 1 ) && ( !start_flg ) )
			{
				gpcnt++;
				if( gpcnt == param_num )
					strcpy( value, param_val );
			}
		}
		else if ( gpcount < ngroup )
		{
			/* Find the subgroup of the actual string */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			param_count = 1;
			get_param();
			if( ( !strcmp( param_val, gpname ) ) && ( !start_group ) )
				gpcount++;
			else if( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
				start_group--;
			else if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
		}

		/* Reinitialize buf & offset to store the next line */
		memset( buf, 0, sizeof( buf ) );
		boffset = 0;
	}
	if(  ( found ) && ( end_flg ) )
	{
		cfg_errno = CFGPARSE_ERR_NOERROR;
		return gpcnt;
	}
	else
	{
		if( !found )
			cfg_errno = CFGPARSE_ERR_NOT_FOUND;
		else
			cfg_errno = CFGPARSE_ERR_SYNTAX_ERR;
		return -1;
	}

}

/* Function for Getting the No.of Entries Configured in a Given Group */
int EzLicenseParseUtil :: cfg_group_count( char *strbuffer, const char *param )
{
	int Len;

	found = false;
	end_flg = false;
	start_flg = false;
	memset( buf, 0, sizeof( buf ) );
	offset = 0;
	boffset = 0;
	gpcount = 0;
	gpcnt = 0;
	start_group = 0;
	ngroup = get_gpcount( param ) ;
	memset( gpname, 0, sizeof( gpname ) );
	Len = 0;

	while ( Len < strlen( strbuffer ) )
	{
		memset( line_str, 0, sizeof( line_str ) );
		Len += getStringLine( strbuffer, line_str, Len );

		if( blank_line() )
			continue;

		get_line();

		memset( buf, 0, sizeof( buf ) );
		strncpy( buf + boffset, line_str, offset );
		if( ( ngroup == gpcount ) && ( !found ) )
		{
			/* Sub-Group Found */
			/* Search for the String */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			strcat( gpname, PARSESTART_GROUP_DEF );
			param_count = 1;
			get_param();
			/* Check whether the string is a start group definition */
			if( ( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) ) && ( strcmp( param_val, gpname ) ) )
				start_group++;

			/* Check whether the string is a end group definition */
			else if ( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
			{
				if( !start_group )
				{
					end_flg = true;
					break;
				}
				else
					start_group--;
			}
			/* Check for the actual string */
			else if ( ( !strcmp( gpname, param_val ) ) && ( !start_group ) )
			{
				start_group = ngroup + 1;
				found = true;
			}
		}
		/* After the actual string is found search for the END_GROUP Count */
		else if( found )
		{
			/* Increment the group count until END_GROUP is found */
			param_count = 1;
			get_param();
			if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
			if ( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
					start_group--;
			if( !start_group )
			{
				end_flg = true;
				break;
			}
			if( start_group < ngroup + 1 )
				start_flg = true;
			if( ( strcmp( param_val, PARSEEND_GROUP_DEF ) ) && ( strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) ) && ( start_group == ngroup + 1 ) && ( !start_flg ) && ( strlen( buf ) > 0 ) )
				gpcnt++;
		}
		else if ( gpcount < ngroup )
		{
			/* Find the subgroup of the actual string */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			param_count = 1;
			get_param();
			if( ( !strcmp( param_val, gpname ) ) && ( !start_group ) )
				gpcount++;
			else if ( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
					start_group--;
			else if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
		}

		/* Reinitialize buf & offset to store the next line */
		memset( buf, 0, sizeof( buf ) );
		boffset = 0;
	}
	if(  ( found ) && ( end_flg ) )
	{
		cfg_errno = CFGPARSE_ERR_NOERROR;
		return gpcnt;
	}
	else
	{
		if( !found )
			cfg_errno = CFGPARSE_ERR_NOT_FOUND;
		else
			cfg_errno = CFGPARSE_ERR_SYNTAX_ERR;
		return -1;
	}

}

/* Function for getting the No. of parameters for the given String */
int EzLicenseParseUtil :: cfg_param_count( char *strbuffer, const char *param )
{
	int Len;

	found = false;
	end_flg = false;
	memset( buf, 0, sizeof( buf ) );
	offset = 0;
	boffset = 0;
	gpcount = 0;
	start_group = 0;
	ngroup = get_gpcount( param );
	memset( gpname, 0, sizeof( gpname ) );
	while ( Len < strlen( strbuffer ) )
	{
		memset( line_str, 0, sizeof( line_str ) );
		Len += getStringLine( strbuffer, line_str, Len );

		if( blank_line() )
			continue;

		get_line();

		memset( buf, 0, sizeof( buf ) );
		strncpy( buf + boffset, line_str, offset );
		if( ( ngroup == gpcount ) && ( !found ) )
		{
			/* Sub-Group Found */
			/* Search for the String */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			param_count = 1;
			get_param();

			/* Check whether the string is a start group definition */
			if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;

			/* Check whether the string is a end group definition */
			else if ( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
			{
				if( !start_group )
				{
					end_flg = true;
					break;
				}
				else
					start_group--;
			}
			/* Check for the actual string */
			else if ( ( !strcmp( gpname, param_val ) ) && ( !start_group ) )
			{
				start_group = ngroup;
				found = true;
				get_param_count();
				/* Get the No.of Parameters */
			}
		}
		/* After the actual string is found search for the END_GROUP Count */
		if( found )
		{
			/* Check for END Group Definition */
			param_count = 1;
			get_param();
			if( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
				start_group--;
			if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
			if( !start_group )
			{
				end_flg = true;
				break;
			}
		}
		if ( gpcount < ngroup )
		{
			/* Find the subgroup of the actual string */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			param_count = 1;
			get_param();
			if( ( !strcmp( param_val, gpname ) ) && ( !start_group ) )
				gpcount++;
			else if( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
				start_group--;
			else if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
		}

		/* Reinitialize buf & offset to store the next line */
		memset( buf, 0, sizeof( buf ) );
		boffset = 0;
	}
	if(  ( found ) && ( end_flg ) )
	{
		cfg_errno = CFGPARSE_ERR_NOERROR;
		return nparam;
	}
	else
	{
		if( !found )
			cfg_errno = CFGPARSE_ERR_NOT_FOUND;
		else
			cfg_errno = CFGPARSE_ERR_SYNTAX_ERR;
		return -1;
	}

}

/* Function for Searching a given value from the Configuration File */

int EzLicenseParseUtil :: cfg_search( char *strbuffer, const char *param, char *value, int paramcount )
{
	int Len = 0;

	found = false;
	end_flg = false;
	memset( buf, 0, sizeof( buf ) );
	offset = 0;
	boffset = 0;
	gpcount = 0;
	start_group = 0;
	ngroup = get_gpcount( param );
	memset( gpname, 0, sizeof( gpname ) );

	while ( Len < strlen( strbuffer ) )
	{
		memset( line_str, 0, sizeof( line_str ) );
		Len += getStringLine( strbuffer, line_str, Len );

		if( blank_line() )
			continue;

		get_line();

		memset( buf, 0, sizeof( buf ) );
		strncpy( buf + boffset, line_str, offset );
		if( ( ngroup == gpcount ) && ( !found ) )
		{
			/* Sub-Group Found */
			/* Search for the String */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			param_count = 1;
			get_param();
			/* Check whether the string is a start group definition */
			if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;

			/* Check whether the string is a end group definition */
			else if ( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
			{
				if( !start_group )
				{
					end_flg = true;
					break;
				}
				else
					start_group--;
			}
			/* Check for the actual string */
			else if ( ( !strcmp( gpname, param_val ) ) && ( !start_group ) )
			{
				start_group = ngroup;
				found = true;
				param_count = paramcount;
				get_param();
				strcpy( value, param_val );
			}
		}
		/* After the actual string is found search for the END_GROUP Count */
		if( found )
		{
			/* Check for END Group Definition */
			param_count = 1;
			get_param();
			if( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
				start_group--;
			if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
			if( !start_group )
			{
				end_flg = true;
				break;
			}
		}
		if ( gpcount < ngroup )
		{
			/* Find the subgroup of the actual string */
			memset( gpname, 0, sizeof( gpname ) );
			get_gpname( param, gpname, gpcount );
			param_count = 1;
			get_param();
			if( ( !strcmp( param_val, gpname ) ) && ( !start_group ) )
				gpcount++;
			else if( !strcmp( param_val, PARSEEND_GROUP_DEF ) )
				start_group--;
			else if( !strcmp( param_val + strlen( param_val ) - strlen( PARSESTART_GROUP_DEF ), PARSESTART_GROUP_DEF ) )
				start_group++;
		}

		/* Reinitialize buf & offset to store the next line */
		memset( buf, 0, sizeof( buf ) );
		boffset = 0;
	}
	if(  ( found ) && ( end_flg ) )
	{
		cfg_errno = CFGPARSE_ERR_NOERROR;
		return 1;
	}
	else
	{
		if( !found )
			cfg_errno = CFGPARSE_ERR_NOT_FOUND;
		else
			cfg_errno = CFGPARSE_ERR_SYNTAX_ERR;
		return -1;
	}

}

void EzLicenseParseUtil :: cfg_fetch_error( char *err_str )
{
	switch ( cfg_errno )
	{
		case CFGPARSE_ERR_NOERROR:
			strcpy( err_str, "NO ERROR" );
			break;

		case CFGPARSE_ERR_NOT_OPENED:
			strcpy( err_str, "CFGERR:CFG FILE NOT OPENED" );
			break;

		case CFGPARSE_ERR_NOT_FOUND:
			strcpy( err_str, "CFGERR:FAILED TO SEARCH STRING" );
			break;

		case CFGPARSE_ERR_SYNTAX_ERR:
			strcpy( err_str, "CFGERR:SYNTAX ERROR" );
			break;

		default:
			strcpy( err_str, "NO ERROR" );

	}
}
