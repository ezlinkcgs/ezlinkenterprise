#include <ezlink/ezalertposter.h>

int EzAlertPoster :: initAlertPoster( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezalertposter.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzAlertPoster Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( EZALERTPOSTERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel",  EZALERTMGRCHANNEL );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.initAlertMemUtil( this ) < 0 )
	{
		trace( "Error in Initializing AlertMemUtil....");
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadAlertInfo() < 0 )
	{
		trace( "Error in Initializing AlertMemUtil....");
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( composeSMSString() < 0 )
	{
		trace( "Error in Composing SMS String...." );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezalert.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening file[%s]...", cfgpath );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTPOST#PROXYREQ", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTPOST#PROXYREQ from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( proxyreq, 0, sizeof( proxyreq ) );
	strcpy( proxyreq, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTPOST#IPADDRESS", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTPOST#IPADDRESS from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( ipaddress, 0, sizeof( ipaddress ) );
	strcpy( ipaddress, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTPOST#PORTNO", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTPOST#PORTNO from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	portno = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTPOST#SMSRETRYCOUNT", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTPOST#SMSRETRYCOUNT from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	SMSRetryCount = atoi( cfgval );

	trace( "SMSRetryCount[%d]", SMSRetryCount );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTPOST#ALERTWAITTIME", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTPOST#ALERTWAITTIME from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	AlertWaitTime = atoi( cfgval );

	trace( "AlertWaitTime[%d]", AlertWaitTime );

	cfgutil.cfg_close();

	curl = curl_easy_init();
  	if( !curl )
	{
		trace( "Error in Intializing Curl...." );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
    }

	SetDebug();

	if( dbutilobj.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil..." );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutilobj.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB...." );
		trace( "^^^^^^^^^^^EzAlertPoster Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();

	}
	TaskInit();
	initEzSigUtil( this );
	return 1;
}

int EzAlertPoster :: composeSMSString()
{
	char cfgpath[ CFG_PATH_SIZE + 1 ];
	FILE *fp;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsmssender.cfg" );
	fp = fopen( cfgpath, "r" );
	if( fp == NULL )
	{
		trace( "Error in opening file[%s]", cfgpath );
		return -1;
	}
	memset( SMSString, 0, sizeof( SMSString ) );
	fgets( SMSString, sizeof( SMSString ), fp );
	fclose( fp );
	SMSString[ strlen( SMSString ) - 1 ] = 0;
	trace( "SMSString[%s]", SMSString );
	return 1;
}

void EzAlertPoster :: composeSMS( const char *MobileNo, const char *MsgBuffer, char *smsMessage )
{
	char SMSBuffer[ 2049 ];
	memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
	for( int i = 0, j = 0; i < strlen( MsgBuffer ); i++ )
	{
		if( MsgBuffer[ i ] == ' ' )
		{
			strcat( SMSBuffer, "%20" );
			j += 3;
		}
		else if( MsgBuffer[ i ] == '\n' )
		{
			strcat( SMSBuffer, "%0A" );
			j += 3;
		}
		else
		{
			SMSBuffer[ j ] = MsgBuffer[ i ];
			j++;
		}
	}

	for( int i = 0, j = 0; i < strlen( SMSString ); i++ )
	{
		if( SMSString[ i ] == '(' )
		{
				strcat( smsMessage, SMSBuffer );
				j += strlen( SMSBuffer );
		}
		else if ( SMSString[ i ] == ')' )
		{
				strcat( smsMessage, MobileNo );
				j += strlen( MobileNo );
		}
		else
		{
				smsMessage[ j ] = SMSString[ i ];
				j++;
		}
	}
}

size_t CurlWriteFunction(void *buffer, size_t size, size_t nmemb, void *userp)
{
	return 1;
}


int EzAlertPoster :: sendSMS( struct EzSMSBufferInfo *smsinfo_ptr )
{
	char SMSBuffer[ 2049 ];
	CURLcode retval;
	char PROXYAddr[ 512 ];

	memset( SMSBuffer, 0, sizeof( SMSBuffer ) );
	composeSMS( smsinfo_ptr->MobileList, smsinfo_ptr->MsgBuffer, SMSBuffer );

	trace( "Composed SMSBuffer[%s]", SMSBuffer );

	memset( PROXYAddr, 0, sizeof( PROXYAddr ) );
	sprintf( PROXYAddr, "%s:%d", ipaddress, portno );

	for( int i = 0; i < SMSRetryCount; i++ )
	{
		curl_easy_setopt( curl, CURLOPT_URL, SMSBuffer );

		if ( !strcasecmp( proxyreq, "yes" ) )
		{
			curl_easy_setopt(curl, CURLOPT_PROXY, PROXYAddr );
		}
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteFunction );

		retval = curl_easy_perform( curl );

		if( retval == 0 || retval == 23 )
			break;
		continue;
	}

	if( retval == 0 || retval == 23 )
		return 1;
	else
		return -1;
}

int EzAlertPoster :: startAlertPoster()
{
	struct EzAlertInfoMemory ezalertinfo;
	struct EzSMSBufferInfo smsinfo;
	struct EzMailBufferInfo mailinfo;
	int retval = 0;

	while( 1 )
	{
		sleep( AlertWaitTime );

		int InstCount = -1;
		while( 1 )
		{
			InstCount++;
			memset( &ezalertinfo, 0, sizeof( struct EzAlertInfoMemory ) );
			if( ezalertmemutil.readAlertInfo( InstCount, &ezalertinfo ) < 0 )
			{
				break;
			}
			if( ezalertinfo.SMSReq == 'y' || ezalertinfo.SMSReq == 'Y' )
			{
				while( 1 )
				{
					memset( &smsinfo, 0, sizeof( struct EzSMSBufferInfo ) );
					retval = readSMSBufferInfoTable( ezalertinfo.InstId, &smsinfo );
					if( ALERT_ORA_CONNECT_ERR( retval ) )
					{
						if( dbutilobj.DBConnect() < 0 )
						{
							trace( "Error in Connecting DB...." );
							break;
						}
						retval = readSMSBufferInfoTable( ezalertinfo.InstId, &smsinfo );
					}
					if( retval == 1403 )
						break;
					if( retval != 0 )
					{
						trace( "Error in Reading EzSMSInfo Table for InstId[%s]..SqlErr[%05d]", retval );
						break;
					}
					trace( "Read SMSBuffer[%s] MobileList[%s] for InstId[%s]", smsinfo.MsgBuffer, smsinfo.MobileList, smsinfo.InstId );

					if( strcmp( ezalertinfo.SMSChannel, "*" ) )
					{
						if( IsTaskRunning( ezalertinfo.SMSChannel ) < 0 )
						{
							trace( "Task[%s] is Not Running....", ezalertinfo.SMSChannel );
							break;
						}

						if( WriteChannel( ezalertinfo.SMSChannel, ( char * )&smsinfo, sizeof( struct EzSMSBufferInfo ) ) < 0 )
						{
							trace( "Error in Writing SMS Message to Channel[%s]....", ezalertinfo.SMSChannel );
							break;
						}
					}
					else
					{
						retval = sendSMS( &smsinfo );
						if( retval < 0 )
						{
							retval = updateSMSStatus( &smsinfo, SMS_TIMEOUT );
							if( ALERT_ORA_CONNECT_ERR( retval ) )
							{
								if( dbutilobj.DBConnect() < 0 )
								{
									trace( "Error in Connecting DB...." );
									break;
								}
								retval = updateSMSStatus( &smsinfo, SMS_TIMEOUT );
							}
							if( retval != 0 )
								trace( "Error in Updating SMS Status as TimedOut......SqlErr[%05d]", retval );
						}
						else
						{
							trace( "SMS Sent Susccessfully...." );
							retval = updateSMSStatus( &smsinfo, SMS_SENT );
							if( ALERT_ORA_CONNECT_ERR( retval ) )
							{
								if( dbutilobj.DBConnect() < 0 )
								{
									trace( "Error in Connecting DB...." );
									break;
								}
								retval = updateSMSStatus( &smsinfo, SMS_SENT );
							}
							if( retval != 0 )
								trace( "Error in Updating SMS Status as SENT......SqlErr[%05d]", retval );
						}
					}
				}
			}
			if( ezalertinfo.MailReq == 'y' || ezalertinfo.MailReq == 'Y' )
			{
				while( 1 )
				{
					memset( &mailinfo, 0, sizeof( struct EzMailBufferInfo ) );
					retval = readMailBufferInfoTable( ezalertinfo.InstId, &mailinfo );
					if( ALERT_ORA_CONNECT_ERR( retval ) )
					{
						if( dbutilobj.DBConnect() < 0 )
						{
							trace( "Error in Connecting DB...." );
							break;
						}
						retval = readMailBufferInfoTable( ezalertinfo.InstId, &mailinfo );
					}
					if( retval == 1403 )
						break;
					if( retval != 0 )
					{
						trace( "Error in Reading EzMailInfo Table for InstId[%s]..SqlErr[%05d]", retval );
						break;
					}
					trace( "Read Subject[%s] Message[%s] ToList[%s] CCList[%s] for InstId[%s]", mailinfo.Subject, mailinfo.MsgBuffer, mailinfo.ToList, mailinfo.CCList, mailinfo.InstId );

					if( IsTaskRunning( ezalertinfo.MailChannel ) < 0 )
					{
						trace( "Task[%s] is Not Running....", ezalertinfo.MailChannel );
						break;
					}

					if( WriteChannel( ezalertinfo.MailChannel, ( char * )&mailinfo, sizeof( struct EzMailBufferInfo ) ) < 0 )
					{
						trace( "Error in Writing SMS Message to Channel[%s]....", ezalertinfo.MailChannel );
						break;
					}

					retval = updateMailStatus( &mailinfo, MAIL_SENT );

					if( retval != 0 )
						trace( "Updating Mail Status as Sent...SqlErr[%05d]", retval );
				}
			}
		}
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzAlertPoster alertposterobj;
	alertposterobj.initAlertPoster( argv[ 0 ] );
	alertposterobj.startAlertPoster();
	return 1;
}
