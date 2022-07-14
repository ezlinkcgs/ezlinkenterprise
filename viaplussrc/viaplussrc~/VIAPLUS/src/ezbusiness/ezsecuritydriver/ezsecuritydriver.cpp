#include <ezbusiness/ezsecuritydriver.h>

void EzSecurityDriver :: initEzSecurityDriver( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	bool DebugFlag = false;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsecuritydriver.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	HSMHeaderVal = 1;

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( SECURITYDRIVERCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating Channel[%s]", SECURITYDRIVERCHANNEL );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( initEzSecurityDriverUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzSecurityDriverUtil" );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateSecurityDriverChannel() < 0 )
	{
		trace( "Error in Creating SecurityDriverChannel" );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( CreateSecurityDriverQueue() < 0 )
	{
		trace( "Error in Initializing SecurityDriver Queue..." );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( LoadATMKeySharedMemory() < 0 )
	{
		trace( "Error in Loading ATMKey Memory...." );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadDeviceKeySharedMemory() < 0 )
	{
		trace( "Error in Loading DeviceKey Memory...." );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadNetworkKeySharedMemory() < 0 )
	{
		trace( "Error in Loading NetworkKey Memory...." );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadSecuritySharedMemory() < 0 )
	{
		trace( "Error in Loading Security Memory...." );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadSecurityPropertyMemory() < 0 )
	{
		trace( "Error in Loading Security Property Memory...." );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsecurity.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HSM_INSTALLED", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching HSM_INSTALLED from file[%s]", cfgpath );
		HSMRequiredFlag = false;
	}
	else
	{
		if( !strcasecmp( cfgval, "Yes" ) )
			HSMRequiredFlag = true;
		else
			HSMRequiredFlag = false;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ENABLE_SOFDES_DEBUG", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ENABLE_SOFDES_DEBUG from file[%s]", cfgpath );
		DebugFlag = false;
	}
	else
	{
		if( !strcasecmp( cfgval, "Yes" ) )
			DebugFlag = true;
		else
			DebugFlag = false;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HSM_NRETRY", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching HSM_NRETRY from file[%s]", cfgpath );
		nHSMRetry = 3;
	}
	else
		nHSMRetry = atoi( cfgval );

	cfgutil.cfg_close();

	ezsoftdes.initSoftDESUtil( this, DebugFlag );

	if( HSMRequiredFlag )
	{
		if( LoadHSMInfoSharedMemory() < 0 )
		{
			trace( "Error in Loading HSMInfo Memory..." );
			trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( initHSMTools( this, MaxHSM, this, this ) < 0 )
		{
			trace( "Error in Initializing HSM Tools..." );
			trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( ezracal.initRacalUtil( this ) < 0 )
		{
			trace( "Error in Initializing RacalUtil..." );
			trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( ezeracom.initEracomUtil( this ) < 0 )
		{
			trace( "Error in Initializing EracomUtil..." );
			trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		struct EzHSMInfo hsminfo;
		struct sembuf sem_buf;

		for( int i = 0; i < MaxHSM; i++ )
		{
			sem_buf.sem_num = i;
			sem_buf.sem_flg = 0;
			sem_buf.sem_op = -2;

			if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for HSMInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
				closeDebug();
				TaskExit();
			}

			if( strcmp( ( HSMInfoMemoryShmPtr + i )->HSMName, EZSEC_HSM_INIT_NAME ) )
			{
				memset( &hsminfo, 0, sizeof( struct EzHSMInfo ) );
				memcpy( &hsminfo, HSMInfoMemoryShmPtr + i, sizeof( struct EzHSMInfo ) );
				initHSMConnection( hsminfo );
			}
			sem_buf.sem_op = 2;
			if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
				closeDebug();
				TaskExit();
			}
		}
	}
	TaskInit();
	initEzSigUtil( this );
}

int EzSecurityDriver :: genTerminalCommKey( const char *InstId, const char *TermId, const char *TermMasterKey, int TermKeyLen, char *TermCommKey_LMK, char *TermCommKey_TMK, struct EzSecurityProperty secproperty )
{
	char ATMCommKey_LMK[ EZSEC_MAX_DEVICE_KEY_LEN + 1 ], RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	trace( DEBUG_SECURED, "Generating TermCommKey for TermId[%s]", TermId );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.generateDeviceCommKey( ( char * )TermMasterKey, TermCommKey_LMK, TermCommKey_TMK, TermKeyLen ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SoftDes", TermId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenerateDeviceCommKeyReq( TermMasterKey, TermKeyLen, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", TermId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", TermId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenerateDeviceCommKeyReq( ResponseBuffer,  TermKeyLen, TermCommKey_LMK, TermCommKey_TMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", TermId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenerateDeviceCommKeyReq( TermMasterKey, TermKeyLen, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  TermId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  TermId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenerateDeviceCommKeyReq( ResponseBuffer,  TermKeyLen, TermCommKey_LMK, TermCommKey_TMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for TermId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  TermId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated New CommKey for TermId[%s]", TermId );
	//trace( DEBUG_NORMAL, "Generated New CommKey_TermMasterKey[%s] CommKey_LocalMasterKey[%s] for TermId[%s]", TermCommKey_TMK, TermCommKey_LMK, TermId );
	return 1;
}

int EzSecurityDriver :: genATMCommKey( const char *InstId, const char *ATMId, char *ATMCommKey, struct EzSecurityProperty secproperty )
{
	char ATMCommKey_LMK[ EZSEC_MAX_DEVICE_KEY_LEN + 1 ], RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	trace( DEBUG_SECURED, "Generating ATMCommKey for DeviceId[%s]", ATMId );

	if( readATMKey( ATMId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading ATMKey Memory for ATMId[%s]", ATMId );
		return -1;
	}

	//trace( DEBUG_NORMAL, "Read ATMMemory with ATMMasterKey[%s] for ATMId[%s] with ATMKeyLen[%d]", getATMMasterKey(), ATMId, getATMKeyLen() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		memset( ATMCommKey_LMK, 0, sizeof( ATMCommKey_LMK ) );
		if( ezsoftdes.generateDeviceCommKey( getATMMasterKey(), ATMCommKey_LMK, ATMCommKey, getATMKeyLen() ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for ATMId[%s] using SoftDes", ATMId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenerateDeviceCommKeyReq( getATMMasterKey(), getATMKeyLen(), RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  ATMId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  ATMId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenerateDeviceCommKeyReq( ResponseBuffer,  getATMKeyLen(), ATMCommKey_LMK, ATMCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for ATMId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  ATMId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenerateDeviceCommKeyReq( getATMMasterKey(), getATMKeyLen(), RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for ATMId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  ATMId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for ATMId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  ATMId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenerateDeviceCommKeyReq( ResponseBuffer,  getATMKeyLen(), ATMCommKey_LMK, ATMCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for ATMId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  ATMId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}

	trace( DEBUG_SECURED, "Generated New CommKey for ATMId[%s]", ATMId );
	//trace( DEBUG_NORMAL, "Generated New CommKey_TermMasterKey[%s] CommKey_LocalMasterKey[%s] for ATMId[%s]", ATMCommKey, ATMCommKey_LMK, ATMId );

	if( updateATMCommKey( ATMId, ATMCommKey_LMK ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Updating ATMMemory for ATMId[%s]", ATMId );
		return -1;
	}

	memset( &devkeymsg, 0, sizeof( struct DeviceKeyMsg) );
	memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );
	strcpy( devkeymsg.DeviceId, ATMId );
	strcpy( devkeymsg.DeviceCommKey, ATMCommKey_LMK );
	ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
	ezsecmgrqmsgObj.CommandCode = EZSEC_ATMKEY;
	ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
	memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&devkeymsg, sizeof( struct DeviceKeyMsg ) );
	if( postSecurityMgrQMsg( &ezsecmgrqmsgObj ) < 0 )
	{
		trace( "Failed in postSecurityMgrQMsg for DeviceId[%s]", devkeymsg.DeviceId );
		return -1;
	}
	return 1;
}

int EzSecurityDriver :: genDeviceCommKey( const char *InstId, const char *DeviceId, char *DeviceCommKey, struct EzSecurityProperty secproperty )
{
	char DeviceCommKey_LMK[ EZSEC_MAX_DEVICE_KEY_LEN + 1 ], RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	trace( DEBUG_SECURED, "Generating DeviceCommKey for DeviceId[%s]", DeviceId );

	if( readDeviceKey( DeviceId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading DeviceKey Memory for DeviceId[%s]", DeviceId );
		return -1;
	}

	//trace( DEBUG_NORMAL, "Read DeviceMemory with DeviceMasterKey[%s] for DeviceId[%s] with KeyLen[%d]", getDeviceMasterKey(), DeviceId, getDeviceKeyLen() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		memset( DeviceCommKey_LMK, 0, sizeof( DeviceCommKey_LMK ) );
		if( ezsoftdes.generateDeviceCommKey( getDeviceMasterKey(), DeviceCommKey_LMK, DeviceCommKey, getDeviceKeyLen() ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SoftDes", DeviceId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenerateDeviceCommKeyReq( getDeviceMasterKey(), getDeviceKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  DeviceId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  DeviceId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenerateDeviceCommKeyReq( ResponseBuffer,  getDeviceKeyLen(), DeviceCommKey_LMK, DeviceCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  DeviceId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenerateDeviceCommKeyReq( getDeviceMasterKey(), getDeviceKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  DeviceId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  DeviceId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenerateDeviceCommKeyReq( ResponseBuffer,  getDeviceKeyLen(), DeviceCommKey_LMK, DeviceCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for DeviceId[%s] using SecurityChannel[%s] SecurityProtocol[%s]",  DeviceId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated New CommKey for for DeviceId[%s]", DeviceId );
	//trace( DEBUG_NORMAL, "Generated New CommKey_TermMasterKey[%s] CommKey_LocalMasterKey[%s] for DeviceId[%s]", DeviceCommKey, DeviceCommKey_LMK, DeviceId );

	if( updateDeviceCommKey( DeviceId, DeviceCommKey_LMK ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Updating DeviceMemory for DeviceId[%s]", DeviceId );
		return -1;
	}

	memset( &devkeymsg, 0, sizeof( struct DeviceKeyMsg) );
	memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );
	strcpy( devkeymsg.DeviceId, DeviceId );
	strcpy( devkeymsg.DeviceCommKey, DeviceCommKey_LMK );
	ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
	ezsecmgrqmsgObj.CommandCode = EZSEC_DEVICEKEY;
	ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
	memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&devkeymsg, sizeof( struct DeviceKeyMsg ) );
	if( postSecurityMgrQMsg( &ezsecmgrqmsgObj ) < 0 )
	{
		trace( "Failed in postSecurityMgrQMsg for DeviceId[%s]", devkeymsg.DeviceId );
		return -1;
	}
	return 1;
}

int EzSecurityDriver :: genAcqNetworkCommKey( const char *InstId, const char *NetworkId, char *NetworkCommKey, struct EzSecurityProperty secproperty )
{
	char NetworkCommKey_LMK[ EZSEC_MAX_NETWORK_KEY_LEN + 1 ], RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	trace( DEBUG_SECURED, "Generating NetworkCommKey for NetworkId[%s]", NetworkId );

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}

	//trace( DEBUG_NORMAL, "Read NetworkMemory with NetworkMasterKey[%s] for NetworkId[%s] with KeyLen[%d]", getNetworkMasterKey(), NetworkId, getNetworkKeyLen() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		memset( NetworkCommKey_LMK, 0, sizeof( NetworkCommKey_LMK ) );
		if( ezsoftdes.generateNetworkCommKey( getNetworkMasterKey(), NetworkCommKey_LMK, NetworkCommKey, getNetworkKeyLen() ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s]", NetworkId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenerateNetworkCommKeyReq( getNetworkMasterKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenerateNetworkCommKeyReq( ResponseBuffer, getNetworkKeyLen(), NetworkCommKey_LMK, NetworkCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize =  ezeracom.composeGenerateNetworkCommKeyReq( getNetworkMasterKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenerateNetworkCommKeyReq( ResponseBuffer, getNetworkKeyLen(), NetworkCommKey_LMK, NetworkCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated New CommKey NetworkId[%s]", NetworkId );
	//trace( DEBUG_NORMAL, "Generated New CommKey_NetworkMasterKey[%s] CommKey_LocalMasterKey[%s] for NetworkId[%s]", NetworkCommKey, NetworkCommKey_LMK, NetworkId );

	if( getNetworkKeyProperty() == KEY_USE_ISS_COMMKEY )
	{
		if( updateNetworkIssuerCommKey( NetworkId, NetworkCommKey_LMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating NetworkKeyMemory for NetworkId[%s]", NetworkId );
			return -1;
		}

		memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
		memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );

		strcpy( networkkeymsg.NetworkId, NetworkId );
		strcpy( networkkeymsg.NetworkCommKey, NetworkCommKey_LMK );

		ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
		ezsecmgrqmsgObj.CommandCode = EZSEC_ISSCOMMKEY;
		ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
		memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&networkkeymsg, sizeof( struct NetworkKeyMsg ) );

		if( postSecurityMgrQMsg( &ezsecmgrqmsgObj ) < 0 )
		{
			trace( "Failed in postSecurityMgrQMsg for NetworkId[%s]", networkkeymsg.NetworkId );
			return -1;
		}
	}
	else
	{
		if( updateNetworkAcquirerCommKey( NetworkId, NetworkCommKey_LMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating NetworkKeyMemory for NetworkId[%s]", NetworkId );
			return -1;
		}

		memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
		memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );

		strcpy( networkkeymsg.NetworkId, NetworkId );
		strcpy( networkkeymsg.NetworkCommKey, NetworkCommKey_LMK );

		ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
		ezsecmgrqmsgObj.CommandCode = EZSEC_ACQCOMMKEY;
		ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
		memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&networkkeymsg, sizeof( struct NetworkKeyMsg ) );

		if( postSecurityMgrQMsg( &ezsecmgrqmsgObj ) < 0 )
		{
			trace( "Failed in postSecurityMgrQMsg for NetworkId[%s]", networkkeymsg.NetworkId );
			return -1;
		}
	}
	return 1;
}

int EzSecurityDriver :: genIssNetworkCommKey( const char *InstId, const char *NetworkId, const char *NetworkCommKey, char * NetworkCommKey_LMK, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	trace( DEBUG_SECURED, "Generating NetworkCommKey_LMK for NetworkId[%s]", NetworkId );

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}

	//trace( DEBUG_NORMAL, "Read NetworkMemory with NetworkMasterKey[%s] for NetworkId[%s] with KeyLen[%d]", getNetworkMasterKey(), NetworkId, getNetworkKeyLen() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		memset( NetworkCommKey_LMK, 0, sizeof( NetworkCommKey_LMK ) );
		//if( ezsoftdes.generateNetworkCommKey( getNetworkMasterKey(), NetworkCommKey_LMK, NetworkCommKey, getNetworkKeyLen() ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s]", NetworkId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenerateNetworkCommKeyReq( getNetworkMasterKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		//if( ezracal.decomposeGenerateNetworkCommKeyReq( ResponseBuffer, getNetworkKeyLen(), NetworkCommKey_LMK, NetworkCommKey ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeReceiveNetworkCommKeyReq( getNetworkMasterKey(), getNetworkKeyLen(), NetworkCommKey, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating CommKey for NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeReceiveNetworkCommKeyReq( ResponseBuffer, getNetworkKeyLen(), NetworkCommKey_LMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating NetworkCommKey_LMK for NetworkId[%s] NetworkCommKey[%s] using SecurityChannel[%s] SecurityProtocol[%s]", NetworkId, NetworkCommKey, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}

	trace( DEBUG_SECURED, "Generated New CommKey for NetworkId[%s]", NetworkId );
	//trace( DEBUG_NORMAL, "Generated New CommKey_NetworkMasterKey[%s] CommKey_LocalMasterKey[%s] for NetworkId[%s]", NetworkCommKey, NetworkCommKey_LMK, NetworkId );

	if( getNetworkKeyProperty() == KEY_USE_ACQ_COMMKEY )
	{
		if( updateNetworkAcquirerCommKey( NetworkId, NetworkCommKey_LMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating NetworkKeyMemory for NetworkId[%s]", NetworkId );
			return -1;
		}

		memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
		memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );

		strcpy( networkkeymsg.NetworkId, NetworkId );
		strcpy( networkkeymsg.NetworkCommKey, NetworkCommKey_LMK );

		ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
		ezsecmgrqmsgObj.CommandCode = EZSEC_ACQCOMMKEY;
		ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
		memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&networkkeymsg, sizeof( struct NetworkKeyMsg ) );

		if( postSecurityMgrQMsg( &ezsecmgrqmsgObj ) < 0 )
		{
			trace( "Failed in postSecurityMgrQMsg for NetworkId[%s]", networkkeymsg.NetworkId );
			return -1;
		}
	}
	else
	{
		if( updateNetworkIssuerCommKey( NetworkId, NetworkCommKey_LMK ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Updating NetworkKeyMemory for NetworkId[%s]", NetworkId );
			return -1;
		}

		memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
		memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );

		strcpy( networkkeymsg.NetworkId, NetworkId );
		strcpy( networkkeymsg.NetworkCommKey, NetworkCommKey_LMK );

		ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
		ezsecmgrqmsgObj.CommandCode = EZSEC_ISSCOMMKEY;
		ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
		memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&networkkeymsg, sizeof( struct NetworkKeyMsg ) );

		if( postSecurityMgrQMsg( &ezsecmgrqmsgObj ) < 0 )
		{
			trace( "Failed in postSecurityMgrQMsg for NetworkId[%s]", networkkeymsg.NetworkId );
			return -1;
		}
	}
	return 1;
}

int EzSecurityDriver :: translatePINBlockTerminalToNetwork( const char *InstId, const char *chn, const char *TermId, const char *TermCommKey, int TermKeyLen, const char *NetworkId, const char *PinBlock, char *TranPinBlock, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}

	trace( DEBUG_SECURED, "Translating PINBlock" );

	//trace( DEBUG_NORMAL, "Translating PINBlock[%s] from TermCommKey[%s] to NetworkCommKey[%s]", PinBlock, TermCommKey, getAcqNetworkCommKey() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.tranPinBlock_Device_Network( ( char * )PinBlock, ( char * ) TermCommKey, TermKeyLen, getAcqNetworkCommKey(), getNetworkKeyLen(), TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s]", PinBlock, TermId, NetworkId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPinBlock_Device_NetworkReq( chn, PinBlock, TermCommKey, TermKeyLen, getAcqNetworkCommKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, TermId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, TermId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposetranPinBlock_Device_NetworkReq( ResponseBuffer, TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, TermId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composetranPinBlock_Device_NetworkReq( PinBlock, chn, TermCommKey, TermKeyLen, getAcqNetworkCommKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, TermId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, TermId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposetranPinBlock_Device_NetworkReq( ResponseBuffer, TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for TermId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, TermId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "PIN Block Translated Successfully..." );
	return 1;
}

int EzSecurityDriver :: translatePINBlockATMToNetwork( const char *InstId, const char *chn, const char *ATMId, const char *NetworkId, const char *PinBlock, char *TranPinBlock, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	if( readATMKey( ATMId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading ATMKey Memory for ATMId[%s]", ATMId );
		return -1;
	}

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}

	trace( DEBUG_SECURED, "Translating PINBlock" );
	//trace( DEBUG_NORMAL, "Translating PINBlock[%s] from ATMCommKey[%s] to NetworkCommKey[%s]", PinBlock, getATMCommKey(), getAcqNetworkCommKey() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.tranPinBlock_Device_Network( ( char * )PinBlock, getATMCommKey(), getATMKeyLen(), getAcqNetworkCommKey(), getNetworkKeyLen(), TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s]", PinBlock, ATMId, NetworkId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPinBlock_Device_NetworkReq( chn, PinBlock, getATMCommKey(), getATMKeyLen(), getAcqNetworkCommKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, ATMId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, ATMId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposetranPinBlock_Device_NetworkReq( ResponseBuffer, TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, ATMId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composetranPinBlock_Device_NetworkReq( PinBlock, chn, getATMCommKey(), getATMKeyLen(), getAcqNetworkCommKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, ATMId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, ATMId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposetranPinBlock_Device_NetworkReq( ResponseBuffer, TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for ATMId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, ATMId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "PIN Block Translated Successfully..." );
	return 1;
}

int EzSecurityDriver :: translatePINBlockDeviceToNetwork( const char *InstId, const char *chn, const char *DeviceId, const char *NetworkId, const char *PinBlock, char *TranPinBlock, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityChannel[ 33 ];

	if( readDeviceKey( DeviceId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading DeviceKey Memory for DeviceId[%s]", DeviceId );
		return -1;
	}

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}
	trace( DEBUG_SECURED, "Translating PINBlock" );
	//trace( DEBUG_NORMAL, "Translating PINBlock[%s] from DeviceCommKey[%s] to NetworkCommKey[%s]", PinBlock, getDeviceCommKey(), getAcqNetworkCommKey() );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.tranPinBlock_Device_Network( ( char * )PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getAcqNetworkCommKey(), getNetworkKeyLen(), TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s]", PinBlock, DeviceId, NetworkId );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPinBlock_Device_NetworkReq( chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getAcqNetworkCommKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, DeviceId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, DeviceId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposetranPinBlock_Device_NetworkReq( ResponseBuffer, TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, DeviceId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composetranPinBlock_Device_NetworkReq( PinBlock, chn, getDeviceCommKey(), getDeviceKeyLen(), getAcqNetworkCommKey(), getNetworkKeyLen(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, DeviceId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, DeviceId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposetranPinBlock_Device_NetworkReq( ResponseBuffer, TranPinBlock ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Translating PINBlock[%s] for DeviceId[%s] NetworkId[%s] using SecurityChannel[%s] SecurityProtocol[%s]", PinBlock, DeviceId, NetworkId, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "PIN Block Translated Successfully..." );
	return 1;
}

int EzSecurityDriver :: verifyTerminalPIN( const char *InstId, const char *TermId, const char *TermCommKey, int TermKeyLen, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];
	int MsgSize, retval;

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}
	trace( DEBUG_SECURED, "Verifying Terminal PIN..." );
	//trace( DEBUG_TEST, "Verifying Terminal PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.verifyPIN( chn, PinBlock, ( char * ) TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeVerifyDevicePINReq( chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeVerifyDevicePINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeVerifyDevicePINReq( chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeVerifyDevicePINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Verified Terminal PIN..." );
	return 1;
}

int EzSecurityDriver :: verifyATMPIN( const char *InstId, const char *ATMId, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];
	int MsgSize, retval;

	if( readATMKey( ATMId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading ATMKey Memory for ATMId[%s]", ATMId );
		return -1;
	}

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );
	if( !strcmp( SecurityId, "999999" ) )
	{
		memset( SecurityId, 0, sizeof( SecurityId ) );
		strcpy( SecurityId, "SUPCRD" );
	}
	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}
	trace( DEBUG_SECURED, "Verifying ATM PIN..." );
	//trace( DEBUG_TEST, "Verifying ATMPIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.verifyPIN( chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeVerifyDevicePINReq( chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeVerifyDevicePINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeVerifyDevicePINReq( chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeVerifyDevicePINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Verified ATM PIN..." );
	return 1;
}

int EzSecurityDriver :: verifyDevicePIN( const char *InstId, const char *DeviceId, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];
	int MsgSize, retval;

	if( readDeviceKey( DeviceId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading DeviceKey Memory for DeviceId[%s]", DeviceId );
		return -1;
	}

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}
	trace( DEBUG_SECURED, "Verifying Device PIN..." );
	//trace( DEBUG_TEST, "Verifying DevicePIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{

		if( ezsoftdes.verifyPIN( chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeVerifyDevicePINReq( chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeVerifyDevicePINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeVerifyDevicePINReq( chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeVerifyDevicePINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Verified Device PIN..." );
	return 1;
}

int EzSecurityDriver :: verifyNetworkPIN( const char *InstId, const char *NetworkId, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}

	trace( DEBUG_SECURED, "Verifying Network PIN..." );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.verifyPIN( chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeVerifyNetworkPINReq( chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeVerifyNetworkPINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeVerifyNetworkPINReq( chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeVerifyNetworkPINReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] PinOffset[%s] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset, secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Verified Network PIN..." );
	return 1;
}

int EzSecurityDriver :: genTerminalPINOffset( const char *InstId, const char *TermId, const char *TermCommKey, int TermKeyLen, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}

	trace( DEBUG_SECURED, "Generating Terminal PIN Offset..." );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.genPINOffset( chn, PinBlock, ( char * ) TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PINOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength() );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		char RandomPIN[ 20 ];

		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPIN_TPK_LMK( chn, TermCommKey, TermKeyLen, PinBlock, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		memset( RandomPIN, 0, sizeof( RandomPIN ) );
		if( ezracal.decomposetranPIN_TPK_LMK( ResponseBuffer, RandomPIN ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenDevicePINOffsetReq( chn, RandomPIN, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenDevicePINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenDevicePINOffsetReq( chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenDevicePINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, TermCommKey, TermKeyLen, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated Terminal PIN Offset" );
	return 1;
}

int EzSecurityDriver :: genATMPINOffset( const char *InstId, const char *ATMId, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];

	if( readATMKey( ATMId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading ATMKey Memory for ATMId[%s]", ATMId );
		return -1;
	}

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );
	if( !strcmp( SecurityId, "999999" ) )
	{
		memset( SecurityId, 0, sizeof( SecurityId ) );
		strcpy( SecurityId, "SUPCRD" );
	}

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}

	trace( DEBUG_SECURED, "Generating ATM PIN Offset..." );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.genPINOffset( chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PINOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength() );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		char RandomPIN[ 20 ];

		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPIN_TPK_LMK( chn, getATMCommKey(), getATMKeyLen(), PinBlock, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		memset( RandomPIN, 0, sizeof( RandomPIN ) );
		if( ezracal.decomposetranPIN_TPK_LMK( ResponseBuffer, RandomPIN ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenDevicePINOffsetReq( chn, RandomPIN, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenDevicePINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenDevicePINOffsetReq( chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenDevicePINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getATMCommKey(), getATMKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated ATM PIN Offset" );
	return 1;
}

int EzSecurityDriver :: genDevicePINOffset( const char *InstId, const char *DeviceId, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];

	if( readDeviceKey( DeviceId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading DeviceKey Memory for DeviceId[%s]", DeviceId );
		return -1;
	}

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}

	trace( DEBUG_SECURED, "Generating Device PIN Offset..." );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.genPINOffset( chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PINOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength() );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		char RandomPIN[ 20 ];

		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPIN_TPK_LMK( chn, getDeviceCommKey(), getDeviceKeyLen(), PinBlock, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		memset( RandomPIN, 0, sizeof( RandomPIN ) );
		if( ezracal.decomposetranPIN_TPK_LMK( ResponseBuffer, RandomPIN ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating Random PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenDevicePINOffsetReq( chn, RandomPIN, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenDevicePINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenDevicePINOffsetReq( chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenDevicePINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getDeviceCommKey(), getDeviceKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated Device PIN Offset" );
	return 1;
}

int EzSecurityDriver :: genNetworkPINOffset( const char *InstId, const char *NetworkId, char *chn, char *PinBlock, char *PinOffset, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	int MsgSize, retval;
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];

	if( readNetworkKey( NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading NetworkKey Memory for NetworkId[%s]", NetworkId );
		return -1;
	}

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}

	trace( DEBUG_SECURED, "Generating Network PIN Offset..." );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.genPINOffset( chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PINOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength() );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		char RandomPIN[ 20 ];

		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composetranPIN_ZPK_LMK( chn, getIssNetworkCommKey(), getNetworkKeyLen(), PinBlock, RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Natural PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating Natural PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		memset( RandomPIN, 0, sizeof( RandomPIN ) );
		if( ezracal.decomposetranPIN_ZPK_LMK( ResponseBuffer, RandomPIN ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating Natural PIN for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}

		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeGenNetworkPINOffsetReq( chn, RandomPIN, getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] RandomPIN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, RandomPIN, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezracal.decomposeGenNetworkPINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeGenNetworkPINOffsetReq( chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
				return -1;
			}
		}
		if( ezeracom.decomposeGenNetworkPINOffsetReq( ResponseBuffer, PinOffset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Generating PinOffset for CHN[%s] PINBlock[%s] CommKey[%s] CommKeyLen[%d] PVK[%s] DecTable[%s] PANValidationOffset[%d] PANValidationLength[%d] using SecurityChannel[%s] SecurityProtocol[%s]", chn, PinBlock, getIssNetworkCommKey(), getNetworkKeyLen(), getEPVK(), getDecimilizationTable(), getPANValidationOffset(), getPANValidationLength(), secproperty.SecurityChannel, secproperty.SecurityProtocol );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "Generated Network PIN Offset" );
	return 1;
}

int EzSecurityDriver :: verifyCVV( const char *InstId, const char *chn, const char *ExpiryDate, const char *ServiceCode, const char *CVV, struct EzSecurityProperty secproperty )
{
	char RequestBuffer[ EZSEC_HSM_REQUEST_BUFFER_SIZE + 1 ], ResponseBuffer[ EZSEC_HSM_RESPONSE_BUFFER_SIZE + 1 ];
	char SecurityId[ 50 ];
	char SecurityChannel[ 33 ];
	int MsgSize, retval;

	memset( SecurityId, 0, sizeof( SecurityId ) );
	strncpy( SecurityId, chn, 6 );

	if( readEzSecurity( SecurityId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading SecurityMemory for SecurityId[%s]", SecurityId );
		return -1;
	}
	trace( DEBUG_SECURED, "Verifying CVV..." );
	//trace( DEBUG_TEST, "Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );

	if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) )
	{
		if( ezsoftdes.verifyCVV( chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezracal.composeVerifyCVVReq( chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
				return -1;
			}
		}
		if( ezracal.decomposeVerifyCVVReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
			return -1;
		}
	}
	else if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
	{
		memset( RequestBuffer, 0, sizeof( RequestBuffer ) );
		MsgSize = ezeracom.composeVerifyCVVReq( chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV, RequestBuffer );
		//trace( DEBUG_TEST, "RequestBuffer[%s]", RequestBuffer );
		for( int i = 0; i < nHSMRetry; i++ )
		{
			memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
			retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
			if( retval == -3 )
				continue;
			else
				break;
		}
		if( retval < 0 )
		{
			memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
			if( getAlternateSecurityChannel( InstId, secproperty.Priority, SecurityChannel ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
				return -1;
			}
			for( int i = 0; i < nHSMRetry; i++ )
			{
				memset( ResponseBuffer, 0, sizeof( ResponseBuffer ) );
				retval = writeToHSM( RequestBuffer, secproperty.SecurityChannel, MsgSize, ResponseBuffer );
				if( retval == -3 )
					continue;
				else
					break;
			}
			if( retval < 0 )
			{
				trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
				return -1;
			}
		}
		if( ezeracom.decomposeVerifyCVVReq( ResponseBuffer ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Verifying CVV for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVKA[%s] CVKB[%s] CVV[%s]", chn, ExpiryDate, ServiceCode, getCVKA(), getCVKB(), CVV );
			return -1;
		}
	}
	trace( DEBUG_SECURED, "CVV Verified...." );
	return 1;
}

void EzSecurityDriver :: getHSMHeader( char *HSMHeader, int HSMHeaderLen )
{
	if( HSMHeaderVal == 9999 )
		HSMHeaderVal = 1;
	else
		HSMHeaderVal += 1;

	sprintf( HSMHeader, "%0*d", HSMHeaderLen, HSMHeaderVal );
}

int EzSecurityDriver :: writeToHSM( const char *RequestBuffer, const char *SecurityChannel, int BufferSize, char *ResponseBuffer )
{
	struct EzHSMInfo hsminfo;
	char MessageHeader[ 20 ], HSMHeader[ 20 ], HSMMessage[ 1025 ], difftimestr[ 20 ];

	time_t curr_time, old_time;
	old_time = time( NULL );

	int offset = 0, MsgSize, responseflag = -1;

	memset( &hsminfo, 0, sizeof( struct EzHSMInfo ) );
	if( readHSMInfo( SecurityChannel, &hsminfo ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in reading HSMInfo for HSM[%s]", SecurityChannel );
		return -1;
	}

	if( !strcasecmp( hsminfo.HSMType , EZSEC_SECPROTOCOL_RACAL ) )
	{
		//trace( DEBUG_NORMAL, "RequestBuffer[%s] BufferSize[%d]", RequestBuffer, BufferSize );

		memset( HSMMessage, 0, sizeof( HSMMessage ) );

		if( !strcasecmp( hsminfo.HeaderType, EZSEC_HSM_HEADER_ASCII ) )
		{
			memset( MessageHeader, 0, sizeof( MessageHeader ) );
			sprintf( MessageHeader, "%0*d", hsminfo.HeaderLen, hsminfo.HSMHeaderLen + BufferSize );
			memcpy( HSMMessage + offset, MessageHeader, hsminfo.HeaderLen );
			offset += hsminfo.HeaderLen;
		}
		else
		{
			MsgSize = BufferSize + hsminfo.HSMHeaderLen;
			MsgSize = htons( MsgSize );
			memset( MessageHeader, 0, sizeof( MessageHeader ) );
			memcpy( MessageHeader, &MsgSize, hsminfo.HeaderLen );
			memcpy( HSMMessage + offset, MessageHeader, hsminfo.HeaderLen );
			offset += hsminfo.HeaderLen;
		}

		if( hsminfo.HSMHeaderLen )
		{
			memset( HSMHeader, 0, sizeof( HSMHeader ) );
			getHSMHeader( HSMHeader, hsminfo.HSMHeaderLen );
			memcpy( HSMMessage + offset, HSMHeader, hsminfo.HSMHeaderLen );
			offset += hsminfo.HSMHeaderLen;
		}

		memcpy( HSMMessage + offset, RequestBuffer, BufferSize );
		offset += BufferSize;

		hex_dump( DEBUG_NORMAL, ( unsigned char * ) HSMMessage, offset );

		if( write( HSMConnectionId, HSMMessage, offset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message to HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
			close( HSMConnectionId );
			HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
			if( HSMConnectionId < 0 )
			{
				initHSMConnection( hsminfo );
				return -1;
			}
			trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
			updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
			if( write( HSMConnectionId, HSMMessage, offset ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Writing Message to HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
				close( HSMConnectionId );
				initHSMConnection( hsminfo );
				return -1;
			}
		}
	}
	else
	{
		memset( HSMMessage, 0, sizeof( HSMMessage ) );

		//SOH
		ezeracom.eracom_ascii_to_bcd( "01", HSMMessage + offset, 1 );
		offset += 1;

		//Version Number
		ezeracom.eracom_ascii_to_bcd( "01", HSMMessage + offset, 1 );
		offset += 1;

		//Sequence Number
		memset( HSMHeader, 0, sizeof( HSMHeader ) );
		getHSMHeader( HSMHeader, 4 );
		ezeracom.eracom_ascii_to_bcd( HSMHeader, HSMMessage + offset, 2 );
		offset += 2;

		//Length of the Message
		MsgSize = htons( BufferSize );
		memset( MessageHeader, 0, sizeof( MessageHeader ) );
		memcpy( MessageHeader, &MsgSize, 2 );

		memcpy( HSMMessage + offset, MessageHeader, 2 );
		offset += 2;

		memcpy( HSMMessage + offset, RequestBuffer, BufferSize );
		offset += BufferSize;

		hex_dump( DEBUG_NORMAL, ( unsigned char * ) HSMMessage, offset );

		if( write( HSMConnectionId, HSMMessage, offset ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Writing Message to HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
			close( HSMConnectionId );
			HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
			if( HSMConnectionId < 0 )
			{
				initHSMConnection( hsminfo );
				return -1;
			}
			trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
			updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
			if( write( HSMConnectionId, HSMMessage, offset ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Writing Message to HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
				close( HSMConnectionId );
				initHSMConnection( hsminfo );
				return -1;
			}
		}
	}

	if( !strcasecmp( hsminfo.HSMType , EZSEC_SECPROTOCOL_RACAL ) )
	{
		responseflag = 1;

		while( 1 )
		{
			memset( MessageHeader, 0, sizeof( MessageHeader ) );
			if( recv( HSMConnectionId, MessageHeader, hsminfo.HeaderLen, MSG_DONTWAIT ) <= 0 )
			{
				if( errno == EAGAIN )
				{
					curr_time = time( NULL );
					memset( difftimestr, 0, sizeof( difftimestr ) );
					sprintf( difftimestr, "%f", difftime( curr_time, old_time ) );
					if( atoi( difftimestr ) > hsminfo.HSMTimeOut )
					{
						trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...Socket Timed Out....", SecurityChannel, HSMConnectionId );
						close( HSMConnectionId );
						HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
						if( HSMConnectionId < 0 )
						{
							responseflag = -1;
							break;
						}
						trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
						updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
						old_time = time( NULL );
						responseflag = -3;
						break;
					}
					continue;
				}
				else
				{
					trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
					close( HSMConnectionId );
					HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
					if( HSMConnectionId < 0 )
					{
						responseflag = -1;
						break;
					}
					trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
					updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
					old_time = time( NULL );
					responseflag = -3;
					break;
				}
			}
			break;
		}

		if( responseflag == -3 )
			return responseflag;

		if( responseflag < 0 )
		{
			initHSMConnection( hsminfo );
			return -1;
		}

		if( !strcasecmp( hsminfo.HeaderType, EZSEC_HSM_HEADER_ASCII ) )
			MsgSize = atoi( MessageHeader );
		else
		{
			memcpy( &MsgSize, MessageHeader, hsminfo.HeaderLen );
			MsgSize = ntohs( MsgSize );
		}

		responseflag = 1;

		while( 1 )
		{
			memset( HSMMessage, 0, sizeof( HSMMessage ) );
			if( recv( HSMConnectionId, HSMMessage, MsgSize, MSG_DONTWAIT ) <= 0 )
			{
				if( errno == EAGAIN )
				{
					curr_time = time( NULL );
					memset( difftimestr, 0, sizeof( difftimestr ) );
					sprintf( difftimestr, "%f", difftime( curr_time, old_time ) );
					if( atoi( difftimestr ) > hsminfo.HSMTimeOut )
					{
						trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...Socket Timed Out....", SecurityChannel, HSMConnectionId );
						close( HSMConnectionId );
						HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
						if( HSMConnectionId < 0 )
						{
							responseflag = -1;
							break;
						}
						trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
						updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
						old_time = time( NULL );
						responseflag = -3;
						break;
					}
					continue;
				}
				else
				{
					trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
					close( HSMConnectionId );
					HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
					if( HSMConnectionId < 0 )
					{
						responseflag = -1;
						break;
					}
					trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
					updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
					old_time = time( NULL );
					responseflag = -3;
					break;
				}
			}
			break;
		}

		if( responseflag == -3 )
			return responseflag;

		if( responseflag < 0 )
		{
			initHSMConnection( hsminfo );
			return -1;
		}
		hex_dump( DEBUG_NORMAL, ( unsigned char * ) HSMMessage, MsgSize );
		strcpy( ResponseBuffer, HSMMessage + hsminfo.HSMHeaderLen );
	}
	else
	{
		responseflag = 1;

		while( 1 )
		{
			memset( MessageHeader, 0, sizeof( MessageHeader ) );
			if( recv( HSMConnectionId, MessageHeader, 6, MSG_DONTWAIT ) <= 0 )
			{
				if( errno == EAGAIN )
				{
					curr_time = time( NULL );
					memset( difftimestr, 0, sizeof( difftimestr ) );
					sprintf( difftimestr, "%f", difftime( curr_time, old_time ) );
					if( atoi( difftimestr ) > hsminfo.HSMTimeOut )
					{
						trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...Socket Timed Out....", SecurityChannel, HSMConnectionId );
						close( HSMConnectionId );
						HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
						if( HSMConnectionId < 0 )
						{
							responseflag = -1;
							break;
						}
						trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
						updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
						old_time = time( NULL );
						responseflag = -3;
						break;
					}
					continue;
				}
				else
				{
					trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
					close( HSMConnectionId );
					HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
					if( HSMConnectionId < 0 )
					{
						responseflag = -1;
						break;
					}
					trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
					updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
					old_time = time( NULL );
					responseflag = -3;
					break;
				}
			}
			break;
		}

		if( responseflag == -3 )
			return responseflag;

		if( responseflag < 0 )
		{
			initHSMConnection( hsminfo );
			return -1;
		}

		memcpy( &MsgSize, MessageHeader + 4, 2 );
		MsgSize = ntohs( MsgSize );

		responseflag = 1;

		while( 1 )
		{
			memset( HSMMessage, 0, sizeof( HSMMessage ) );
			if( recv( HSMConnectionId, HSMMessage, MsgSize, MSG_DONTWAIT ) <= 0 )
			{
				if( errno == EAGAIN )
				{
					curr_time = time( NULL );
					memset( difftimestr, 0, sizeof( difftimestr ) );
					sprintf( difftimestr, "%f", difftime( curr_time, old_time ) );
					if( atoi( difftimestr ) > hsminfo.HSMTimeOut )
					{
						trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...Socket Timed Out....", SecurityChannel, HSMConnectionId );
						close( HSMConnectionId );
						HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
						if( HSMConnectionId < 0 )
						{
							responseflag = -1;
							break;
						}
						trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
						updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
						old_time = time( NULL );
						responseflag = -3;
						break;
					}
					continue;
				}
				else
				{
					trace( DEBUG_ERROR, "Error in Reading Header from HSM[%s] with SocketId[%d]...SysErr[%s], ErrNo[%d]", SecurityChannel, HSMConnectionId, strerror( errno ), errno );
					responseflag = -1;
					close( HSMConnectionId );
					break;
					close( HSMConnectionId );
					HSMConnectionId = connectWithHSM( hsminfo.HSMName, hsminfo.HSMAddress, hsminfo.HSMPortNo );
					if( HSMConnectionId < 0 )
					{
						responseflag = -1;
						break;
					}
					trace( "Updating HSMConnectionId[%d] for HSM[%s]", HSMConnectionId, hsminfo.HSMName );
					updateHSMConnectionId( hsminfo.HSMName, HSMConnectionId );
					old_time = time( NULL );
					responseflag = -3;
					break;
				}
			}
			break;
		}

		if( responseflag == -3 )
			return responseflag;

		if( responseflag < 0 )
		{
			initHSMConnection( hsminfo );
			return -1;
		}
		hex_dump( DEBUG_NORMAL, ( unsigned char * ) HSMMessage, MsgSize );
		memcpy( ResponseBuffer, HSMMessage, MsgSize );
	}
	return 1;
}

int EzSecurityDriver :: getAlternateSecurityChannel( const char *InstId, int CurrPriority, char *SecurityChannel )
{
	struct EzSecurityProperty secproperty;
	int Priority = CurrPriority + 1;
	struct EzHSMConnectionInfo hsmconninfo_rec;

	while( 1 )
	{
		memset( &secproperty, 0, sizeof( struct EzSecurityProperty ) );

		if( readSecurityProperty( InstId, Priority, &secproperty ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading EzSecurityProperty for InstId[%s] Priority[%d]", InstId, Priority );
			return -1;
		}

		//trace( DEBUG_NORMAL, "Read EzSecurityProperty for InstId[%s] with SecurityProtocol[%s] SecurityChannel[%s] Priority[%d]", InstId, secproperty.SecurityProtocol, secproperty.SecurityChannel, secproperty.Priority );

		if( strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) && strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) && strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
		{
			trace( DEBUG_ERROR, "Invalid SecurityProtocol[%s] Configured for InstId[%s] in EzSecurityProtocol",  secproperty.SecurityProtocol, InstId );
			return -1;
		}

		if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) || !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
		{
			memset( &hsmconninfo_rec, 0, sizeof( struct EzHSMConnectionInfo ) );
			if( readHSMConnectionInfo( secproperty.SecurityChannel, &hsmconninfo_rec ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading SecurityChannel[%s] from EzHSMConnectionInfo Table", secproperty.SecurityChannel );
				Priority++;
				continue;
			}

			if( hsmconninfo_rec.HSMStatus == EZSEC_HSM_DISCONNECTED )
			{
				trace( DEBUG_ERROR, "SecurityChannel[%s] is Not Connected....", secproperty.SecurityChannel );
				Priority++;
				continue;
			}
			else
			{
				HSMConnectionId = hsmconninfo_rec.HSMConnectionId;
				break;
			}
		}
		else
			return -1;
	}
	trace( "HSMConnectionId for SecurityChannel[%s] is [%d]", secproperty.SecurityChannel, HSMConnectionId );
	strcpy( SecurityChannel, secproperty.SecurityChannel );
	return 1;
}

void EzSecurityDriver :: ServiceRequest()
{
	struct EzSecurityDriverQMsg secqmsg, secqrespmsg;
	struct EzDeviceCommKeyMsg devicecommkey;
	struct EzTerminalCommKeyMsg termcommkey;
	struct EzNetworkCommKeyMsg ntwkcommkey;
	struct EzTerminalPINTranslateMsg termtranslatemsg;
	struct EzPINTranslateMsg translatemsg;
	struct EzTerminalPINInfoMsg termpininfo;
	struct EzPINInfoMsg pininfo;
	struct EzCVVInfoMsg cvvinfo;
	struct EzSecurityProperty secproperty;
	int Priority = 1, Response = 1;
	char InstId[ 13 ], NetworkCommKey_LMK[ 65 ];
	struct EzHSMConnectionInfo hsmconninfo_rec;

	while( 1 )
	{
		trace( "EzSecurityDriver Waiting For Request...." );
		trace( "SecurityDriverQid[%d]", getSecurityDriverQid() );
		memset( &secqmsg, 0, sizeof( struct EzSecurityDriverQMsg ) );
		if( msgrcv( getSecurityDriverQid(), &secqmsg, sizeof( secqmsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			trace( "Error in Receiving Message from EzSecurityDriver Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			if( errno == EIDRM )
			{
				if( CreateSecurityDriverQueue() < 0 )
				{
					trace( "Error in Creating SecurityDriver Queue...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
					closeDebug();
					TaskExit();
				}
				continue;
			}
			else if ( errno == EINTR )
				continue;
			trace( "^^^^^^^^^^^EzSecurityDriver Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		trace( "Got Request....." );
		Priority = 1;
		Response = 1;

		while( 1 )
		{

			memset( InstId, 0, sizeof( InstId ) );
			strcpy( InstId, secqmsg.secmsg.InstId );

			memset( &secproperty, 0, sizeof( struct EzSecurityProperty ) );
			if( readSecurityProperty( InstId, Priority, &secproperty ) < 0 )
			{
				trace( DEBUG_ERROR, "Error in Reading EzSecurityProperty for InstId[%s] Priority[%d]", InstId, Priority );
				Response = -1;
				break;
			}

			//trace( DEBUG_NORMAL, "Read EzSecurityProperty for InstId[%s] with SecurityProtocol[%s] SecurityChannel[%s] Priority[%d]", InstId, secproperty.SecurityProtocol, secproperty.SecurityChannel, secproperty.Priority );

			if( strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_SOFTDES ) && strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) && strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
			{
				trace( DEBUG_ERROR, "Invalid SecurityProtocol[%s] Configured for InstId[%s] in EzSecurityProtocol",  secproperty.SecurityProtocol, InstId );
				Response = -1;
				break;
			}

			if( !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_RACAL ) || !strcasecmp( secproperty.SecurityProtocol, EZSEC_SECPROTOCOL_ERACOM ) )
			{
				memset( &hsmconninfo_rec, 0, sizeof( struct EzHSMConnectionInfo ) );
				if( readHSMConnectionInfo( secproperty.SecurityChannel, &hsmconninfo_rec ) < 0 )
				{
					trace( DEBUG_ERROR, "Error in Reading SecurityChannel[%s] from EzHSMConnectionInfo Table", secproperty.SecurityChannel );
					Priority++;
					continue;
				}

				if( hsmconninfo_rec.HSMStatus == EZSEC_HSM_DISCONNECTED )
				{
					trace( DEBUG_ERROR, "SecurityChannel[%s] is Not Connected....", secproperty.SecurityChannel );
					Priority++;
					continue;
				}
				else
					HSMConnectionId = hsmconninfo_rec.HSMConnectionId;
			}
			break;
		}

		trace( "HSMConnectionId for SecurityChannel[%s] is [%d]", secproperty.SecurityChannel, HSMConnectionId );

		if( Response < 0 )
		{
			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzDeviceCommKeyMsg ) );
			secqrespmsg.secmsg.Response = Response;
			if( msgsnd( getSecurityDriverQid(), &secqrespmsg, sizeof( secqrespmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
				trace( DEBUG_ERROR, "Error in Sending Response to NotificationId[%d] through EzSecurityDriver Queue SysErr[%s] ErrNo[%d]", secqmsg.secmsg.NotificationId, strerror( errno ), errno );
			else
				trace( DEBUG_NORMAL, "Sent Response to NotificationId[%d]", secqmsg.secmsg.NotificationId );
			continue;
		}

		switch ( secqmsg.secmsg.Command )
		{
			case EZSEC_TERM_GEN_COMM_KEY:

			memset( &termcommkey, 0, sizeof( struct EzTerminalCommKeyMsg ) );
			memcpy( &termcommkey, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzTerminalCommKeyMsg ) );

			trace( DEBUG_SECURED, "Received Generate Terminal CommKey Command from NotificationId[%d] for TermId[%s]", secqmsg.secmsg.NotificationId, termcommkey.TermId );

			memset( termcommkey.TermCommKey_LMK, 0, sizeof( termcommkey.TermCommKey_LMK ) );
			memset( termcommkey.TermCommKey_TMK, 0, sizeof( termcommkey.TermCommKey_TMK ) );
			if( genTerminalCommKey( InstId, termcommkey.TermId, termcommkey.TermMasterKey, termcommkey.TermKeyLen, termcommkey.TermCommKey_LMK, termcommkey.TermCommKey_TMK, secproperty ) < 0 )
			{
				trace( "Error in Generating CommKey for TermId[%s] with NotificationId[%d]", termcommkey.TermId, secqmsg.secmsg.NotificationId );
				Response = -1;
			}
			else
			{
				trace( DEBUG_SECURED, "Generated CommKey TermId[%s] for NotificationId[%d]", termcommkey.TermId, secqmsg.secmsg.NotificationId );
				//trace( DEBUG_NORMAL, "Generated CommKey_LMK[%s] CommKey_TMK[%s] for TermId[%s] for NotificationId[%d]", termcommkey.TermCommKey_LMK, termcommkey.TermCommKey_TMK, termcommkey.TermId, secqmsg.secmsg.NotificationId );
				Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( struct EzSecurityDriverMsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *)&termcommkey, sizeof( struct EzTerminalCommKeyMsg ) );
			secqrespmsg.secmsg.Response = Response;
			break;

			case EZSEC_DEVICE_GEN_COMM_KEY:

			memset( &devicecommkey, 0, sizeof( struct EzDeviceCommKeyMsg ) );
			memcpy( &devicecommkey, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzDeviceCommKeyMsg ) );

			trace( DEBUG_SECURED, "Received Generate Device CommKey Command from NotificationId[%d] for DeviceId[%s]", secqmsg.secmsg.NotificationId, devicecommkey.DeviceId );

			memset( devicecommkey.DeviceCommKey, 0, sizeof( devicecommkey.DeviceCommKey ) );
			if( genDeviceCommKey( InstId, devicecommkey.DeviceId, devicecommkey.DeviceCommKey, secproperty ) < 0 )
			{
				trace( "Error in Generating CommKey for DeviceId[%s] with NotificationId[%d]", devicecommkey.DeviceId, secqmsg.secmsg.NotificationId );
				Response = -1;
			}
			else
			{
				trace( DEBUG_SECURED, "Generated CommKey for DeviceId[%s] for NotificationId[%d]", devicecommkey.DeviceId, secqmsg.secmsg.NotificationId );
				//trace( DEBUG_NORMAL, "Generated CommKey[%s] for DeviceId[%s] for NotificationId[%d]", devicecommkey.DeviceCommKey, devicecommkey.DeviceId, secqmsg.secmsg.NotificationId );
				Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( struct EzSecurityDriverMsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *)&devicecommkey, sizeof( struct EzDeviceCommKeyMsg ) );
			secqrespmsg.secmsg.Response = Response;
			break;

			case EZSEC_ATM_GEN_COMM_KEY:

			memset( &devicecommkey, 0, sizeof( struct EzDeviceCommKeyMsg ) );
			memcpy( &devicecommkey, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzDeviceCommKeyMsg ) );

			trace( DEBUG_SECURED, "Received Generate ATM CommKey Command from NotificationId[%d] for ATMId[%s]", secqmsg.secmsg.NotificationId, devicecommkey.DeviceId );

			memset( devicecommkey.DeviceCommKey, 0, sizeof( devicecommkey.DeviceCommKey ) );
			if( genATMCommKey( InstId, devicecommkey.DeviceId, devicecommkey.DeviceCommKey, secproperty ) < 0 )
			{
				trace( "Error in Generating CommKey for ATMId[%s] with NotificationId[%d]", devicecommkey.DeviceId, secqmsg.secmsg.NotificationId );
				Response = -1;
			}
			else
			{
				trace( DEBUG_SECURED, "Generated CommKey for ATMId[%s] for NotificationId[%d]", devicecommkey.DeviceId, secqmsg.secmsg.NotificationId );
				//trace( DEBUG_NORMAL, "Generated CommKey[%s] for ATMId[%s] for NotificationId[%d]", devicecommkey.DeviceCommKey, devicecommkey.DeviceId, secqmsg.secmsg.NotificationId );
				Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( struct EzSecurityDriverMsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *)&devicecommkey, sizeof( struct EzDeviceCommKeyMsg ) );
			secqrespmsg.secmsg.Response = Response;
			break;

			case EZSEC_ACQ_NTWK_GEN_COMM_KEY:

			memset( &ntwkcommkey, 0, sizeof( struct EzNetworkCommKeyMsg ) );
			memcpy( &ntwkcommkey, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzNetworkCommKeyMsg ) );

			trace( DEBUG_SECURED, "Received Generate Network CommKey Command from NotificationId[%d] for NetworkId[%s]", secqmsg.secmsg.NotificationId, ntwkcommkey.NetworkId );

			if( genAcqNetworkCommKey( InstId, ntwkcommkey.NetworkId, ntwkcommkey.NetworkCommKey, secproperty ) < 0 )
			{
				trace( "Error in Generating CommKey for NetworkId[%s] with NotificationId[%d]", ntwkcommkey.NetworkId, secqmsg.secmsg.NotificationId );
				Response = -1;
			}
			else
			{
				trace( DEBUG_SECURED, "Generated CommKey for NetworkId[%s] for NotificationId[%d]", ntwkcommkey.NetworkId, secqmsg.secmsg.NotificationId );
				//trace( DEBUG_NORMAL, "Generated CommKey[%s] for NetworkId[%s] for NotificationId[%d]", ntwkcommkey.NetworkCommKey, ntwkcommkey.NetworkId, secqmsg.secmsg.NotificationId );
				Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &ntwkcommkey, sizeof( struct EzNetworkCommKeyMsg ) );
			secqrespmsg.secmsg.Response = Response;

			break;

			case EZSEC_ISS_NTWK_GEN_COMM_KEY:

			memset( &ntwkcommkey, 0, sizeof( struct EzNetworkCommKeyMsg ) );
			memcpy( &ntwkcommkey, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzNetworkCommKeyMsg ) );

			trace( DEBUG_SECURED, "Received Generate NetworkCommKey Command from NotificationId[%d] for NetworkId[%s] ", secqmsg.secmsg.NotificationId, ntwkcommkey.NetworkId );
			//trace( DEBUG_NORMAL, "Received Generate NetworkCommKey_LMK Command from NotificationId[%d] for NetworkId[%s] NetworkCommKey[%s]", secqmsg.secmsg.NotificationId, ntwkcommkey.NetworkId, ntwkcommkey.NetworkCommKey );

			memset( NetworkCommKey_LMK, 0, sizeof( NetworkCommKey_LMK ) );
			if( genIssNetworkCommKey( InstId, ntwkcommkey.NetworkId, ntwkcommkey.NetworkCommKey, NetworkCommKey_LMK, secproperty ) < 0 )
			{
				trace( "Error in Generating NetworkCommKey_LMK for NetworkId[%s] NetworkCommKey[%s] with NotificationId[%d]", ntwkcommkey.NetworkId, ntwkcommkey.NetworkCommKey, secqmsg.secmsg.NotificationId );
				Response = -1;
			}
			else
			{
				trace( DEBUG_SECURED, "Generated NetworkCommKey for NetworkId[%s] for NotificationId[%d]", NetworkCommKey_LMK, ntwkcommkey.NetworkId, secqmsg.secmsg.NotificationId );
				//trace( DEBUG_NORMAL, "Generated NetworkCommKey_LMK[%s] for NetworkId[%s] NetworkCommKey[%s] for NotificationId[%d]", NetworkCommKey_LMK, ntwkcommkey.NetworkId, ntwkcommkey.NetworkCommKey, secqmsg.secmsg.NotificationId );
				Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memset( ntwkcommkey.NetworkCommKey, 0, sizeof( ntwkcommkey.NetworkCommKey ) );
			strcpy( ntwkcommkey.NetworkCommKey, NetworkCommKey_LMK );
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &ntwkcommkey, sizeof( struct EzNetworkCommKeyMsg ) );
			secqrespmsg.secmsg.Response = Response;

			break;

			case EZSEC_TRANSLATE_PIN_TERM_NTWK:

			memset( &termtranslatemsg, 0, sizeof( struct EzTerminalPINTranslateMsg ) );
			memcpy( &termtranslatemsg, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzTerminalPINTranslateMsg ) );

			trace( DEBUG_SECURED, "Received Translate PIN Block Request from NotificationId[%d]", secqmsg.secmsg.NotificationId );
			//trace( DEBUG_NORMAL, "Translating PIN Block from TermId[ %s ] to NetworkId[ %s ]", termtranslatemsg.TermId, termtranslatemsg.NetworkId );

			if( translatePINBlockTerminalToNetwork( InstId, termtranslatemsg.CHN, termtranslatemsg.TermId, termtranslatemsg.TermCommKey, termtranslatemsg.TermKeyLen, termtranslatemsg.NetworkId, termtranslatemsg.PinBlock, termtranslatemsg.TranPinBlock, secproperty ) < 0 )
			{
				trace( "Error in Translating PinBlock" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PinBlock Translated Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &termtranslatemsg, sizeof( struct EzTerminalPINTranslateMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;


			case EZSEC_TRANSLATE_PIN_ATM_NTWK:

			memset( &translatemsg, 0, sizeof( struct EzPINTranslateMsg ) );
			memcpy( &translatemsg, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINTranslateMsg ) );

			trace( "Received Translate PIN Block Request from NotificationId[%d]", secqmsg.secmsg.NotificationId );
			trace( "Translating PIN Block from ATMId[ %s ] to NetworkId[ %s ]", translatemsg.DeviceId, translatemsg.NetworkId );

			if( translatePINBlockATMToNetwork( InstId, translatemsg.CHN, translatemsg.DeviceId, translatemsg.NetworkId, translatemsg.PinBlock, translatemsg.TranPinBlock, secproperty ) < 0 )
			{
				trace( "Error in Translating PinBlock" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PinBlock Translated Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &translatemsg, sizeof( struct EzPINTranslateMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;


			case EZSEC_TRANSLATE_PIN_DEV_NTWK:

			memset( &translatemsg, 0, sizeof( struct EzPINTranslateMsg ) );
			memcpy( &translatemsg, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINTranslateMsg ) );

			trace( "Received Translate PIN Block Request from NotificationId[%d]", secqmsg.secmsg.NotificationId );
			trace( "Translating PIN Block from DeviceId[ %s ] to NetworkId[ %s ]", translatemsg.DeviceId, translatemsg.NetworkId );

			if( translatePINBlockDeviceToNetwork( InstId, translatemsg.CHN, translatemsg.DeviceId, translatemsg.NetworkId, translatemsg.PinBlock, translatemsg.TranPinBlock, secproperty ) < 0 )
			{
				trace( "Error in Translating PinBlock" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PinBlock Translated Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &translatemsg, sizeof( struct EzPINTranslateMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_TRANSLATE_PIN_NTWK_DEV:

			secqmsg.secmsg.Response = -1;
			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &translatemsg, sizeof( struct EzPINTranslateMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_VERIFY_TERM_PIN:

			memset( &termpininfo, 0, sizeof( struct EzTerminalPINInfoMsg ) );
			memcpy( &termpininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzTerminalPINInfoMsg ) );

			trace( "Received Pin Verification Request from NotificationId[%d] for TermId[%s]", secqmsg.secmsg.NotificationId, termpininfo.TermId );

			if( verifyTerminalPIN( InstId, termpininfo.TermId, termpininfo.TermCommKey, termpininfo.TermKeyLen, termpininfo.CHN, termpininfo.PinBlock, termpininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Verifying PIN" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PIN Verified Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &termpininfo, sizeof( struct EzTerminalPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_VERIFY_ATM_PIN:

			memset( &pininfo, 0, sizeof( struct EzPINInfoMsg ) );
			memcpy( &pininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINInfoMsg ) );

			trace( "Received Pin Verification Request from NotificationId[%d] for ATMId[%s]", secqmsg.secmsg.NotificationId, pininfo.DeviceId );

			if( verifyATMPIN( InstId, pininfo.DeviceId, pininfo.CHN, pininfo.PinBlock, pininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Verifying PIN" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PIN Verified Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &pininfo, sizeof( struct EzPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_VERIFY_DEVICE_PIN:

			memset( &pininfo, 0, sizeof( struct EzPINInfoMsg ) );
			memcpy( &pininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINInfoMsg ) );

			trace( "Received Pin Verification Request from NotificationId[%d] for DeviceId[%s] SecurityId[%s]", secqmsg.secmsg.NotificationId, pininfo.DeviceId );

			if( verifyDevicePIN( InstId, pininfo.DeviceId, pininfo.CHN, pininfo.PinBlock, pininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Verifying PIN" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PIN Verified Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &pininfo, sizeof( struct EzPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_VERIFY_NETWORK_PIN:

			memset( &pininfo, 0, sizeof( struct EzPINInfoMsg ) );
			memcpy( &pininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINInfoMsg ) );

			trace( "Received Pin Verification Request from NotificationId[%d] for NetworkId[%s]", secqmsg.secmsg.NotificationId, pininfo.NetworkId );

			if( verifyNetworkPIN( InstId, pininfo.NetworkId, pininfo.CHN, pininfo.PinBlock, pininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Verifying PIN" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PIN Verified Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &pininfo, sizeof( struct EzPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_VERIFY_CVV:

			memset( &cvvinfo, 0, sizeof( struct EzCVVInfoMsg ) );
			memcpy( &cvvinfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzCVVInfoMsg ) );

			trace( DEBUG_SECURED, "Received CVV Verification Request for NotificationId[%d] ", secqmsg.secmsg.NotificationId );
			//trace( DEBUG_NORMAL, "Received CVV Verification Request for CHN[%s] ExpiryDate[%s] ServiceCode[%s] CVV[%s] from NotificationId[%d] ", cvvinfo.CHN, cvvinfo.ExpiryDate, cvvinfo.ServiceCode, cvvinfo.CVV, secqmsg.secmsg.NotificationId );

			if( verifyCVV( InstId, cvvinfo.CHN, cvvinfo.ExpiryDate, cvvinfo.ServiceCode, cvvinfo.CVV, secproperty ) < 0 )
			{
				trace( "Error in Verifying CVV" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "CVV Verified Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &cvvinfo, sizeof( struct EzCVVInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_GEN_TERM_PINOFFSET:

			memset( &termpininfo, 0, sizeof( struct EzTerminalPINInfoMsg ) );
			memcpy( &termpininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzTerminalPINInfoMsg ) );

			trace( "Received Generate PinOffset Request from NotificationId[%d] for TermId[%s]", secqmsg.secmsg.NotificationId, termpininfo.TermId );

			if( genTerminalPINOffset( InstId, termpininfo.TermId, termpininfo.TermCommKey, termpininfo.TermKeyLen, termpininfo.CHN, termpininfo.PinBlock, termpininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Generating PINoffset" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PINoffset Generated Successfully" );
				secqmsg.secmsg.Response = 1;
			}
			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, &termpininfo, sizeof( struct EzTerminalPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_GEN_ATM_PINOFFSET:

			memset( &pininfo, 0, sizeof( struct EzPINInfoMsg ) );
			memcpy( &pininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINInfoMsg ) );

			trace( "Received Generate PinOffset Request from NotificationId[%d] for ATMId[%s]", secqmsg.secmsg.NotificationId, pininfo.DeviceId );

			if( genATMPINOffset( InstId, pininfo.DeviceId, pininfo.CHN, pininfo.PinBlock, pininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Generating PINoffset" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PINoffset Generated Successfully" );
				secqmsg.secmsg.Response = 1;
			}
			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, &pininfo, sizeof( struct EzPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;


			case EZSEC_GEN_DEV_PINOFFSET:

			memset( &pininfo, 0, sizeof( struct EzPINInfoMsg ) );
			memcpy( &pininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINInfoMsg ) );

			trace( "Received Generate PinOffset Request from NotificationId[%d] for DeviceId[%s]", secqmsg.secmsg.NotificationId, pininfo.DeviceId );

			if( genDevicePINOffset( InstId, pininfo.DeviceId, pininfo.CHN, pininfo.PinBlock, pininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Generating PINoffset" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PINoffset Generated Successfully" );
				secqmsg.secmsg.Response = 1;
			}
			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, &pininfo, sizeof( struct EzPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			case EZSEC_GEN_NTWK_PINOFFSET:

			memset( &pininfo, 0, sizeof( struct EzPINInfoMsg ) );
			memcpy( &pininfo, secqmsg.secmsg.SecurityBuffer, sizeof( struct EzPINInfoMsg ) );

			trace( "Received Generate PinOffset Request from NotificationId[%d] for NetworkId[%s]", secqmsg.secmsg.NotificationId, pininfo.NetworkId );

			if( genNetworkPINOffset( InstId, pininfo.NetworkId, pininfo.CHN, pininfo.PinBlock, pininfo.PinOffset, secproperty ) < 0 )
			{
				trace( "Error in Generating PINoffset" );
				secqmsg.secmsg.Response = -1;
			}
			else
			{
				trace( "PINoffset Generated Successfully" );
				secqmsg.secmsg.Response = 1;
			}

			memset( &secqrespmsg, 0, sizeof( secqrespmsg ) );
			secqrespmsg.msgtype = secqmsg.secmsg.NotificationId;
			memcpy( secqrespmsg.secmsg.SecurityBuffer, (char *) &pininfo, sizeof( struct EzPINInfoMsg ) );
			secqrespmsg.secmsg.Response = secqmsg.secmsg.Response;
			break;

			default:
			trace( "Invalid Command Received");
			secqrespmsg.secmsg.Response = -1;
			break;
		}
		//trace( DEBUG_TEST, "Response<%d> NotificationId<%d>", secqrespmsg.secmsg.Response, secqrespmsg.msgtype);

		if( msgsnd( getSecurityDriverQid(), &secqrespmsg, sizeof( struct EzSecurityDriverQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			trace( "Error in Sending Response to NotificationId[%d] through EzSecurityDriver Queue SysErr[%s] ErrNo[%d]", secqmsg.secmsg.NotificationId, strerror( errno ), errno );
		else
			trace( "Sent Response to NotificationId[%d]", secqmsg.secmsg.NotificationId );
	}

}

int EzSecurityDriver :: postSecurityMgrQMsg( struct EzSecurityMgrQMsg *ezsecmgrqmsgPtr )
{
	trace("Routing Message bytes [ %d ] to %s", sizeof( struct EzSecurityMgrQMsg ), EZSEC_SECURITYMGRCHANNEL );
	//trace("<%d><%d><%d>", ezsecmgrqmsgPtr->SourceType, ezsecmgrqmsgPtr->CommandCode, ezsecmgrqmsgPtr->OperationCode );
	if( WriteChannel( EZSEC_SECURITYMGRCHANNEL, (char*)ezsecmgrqmsgPtr, sizeof( struct EzSecurityMgrQMsg ) ) < 0 )
	{
		trace( "Unable to write into the channel %s", EZSEC_SECURITYMGRCHANNEL );
		return -1;
	}
	else
		trace( "Message Posted into the %s channel", EZSEC_SECURITYMGRCHANNEL );
	return 1;
}

int main( int argc, char **argv )
{
	EzSecurityDriver netdriverobj;
	netdriverobj.initEzSecurityDriver( argv[ 0 ] );
	netdriverobj.ServiceRequest();
	return 1;
}


