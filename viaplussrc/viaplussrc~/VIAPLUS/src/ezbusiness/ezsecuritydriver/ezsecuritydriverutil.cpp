#include <ezbusiness/ezsecuritydriverutil.h>

EzSecurityDriverUtil :: EzSecurityDriverUtil()
{
}

EzSecurityDriverUtil :: ~EzSecurityDriverUtil()
{
}

int EzSecurityDriverUtil :: getDeviceKeySharedMemory()
{
	DeviceKeyMemoryId = LocateMemoryId( dptr, "DEVICEKEYMEMORY" );
	if( DeviceKeyMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Locating Memory[%s]", "DEVICEKEYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Located with MemoryId[%d]", "DEVICEKEYMEMORY", DeviceKeyMemoryId );
	DeviceKeyMemoryShmid = shmget( ( key_t ) DeviceKeyMemoryId, 0, IPC_CREAT | 0666 );
	if(  DeviceKeyMemoryShmid < 0 )
	{
		dptr->trace( "Error in Creating DeviceKey Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	DeviceKeyMemoryShmPtr = ( struct DeviceKey * ) shmat( DeviceKeyMemoryShmid, 0, 0 );
	if( DeviceKeyMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching DeviceKey Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	DeviceKeyMemorySemid = semget( ( key_t ) DeviceKeyMemoryId, 0, IPC_CREAT | 0666 );
	if( DeviceKeyMemorySemid < 0 )
	{
		dptr->trace( "Error in Creating DeviceKey Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzSecurityDriverUtil :: getNetworkKeySharedMemory()
{
	NetworkKeyMemoryId = LocateMemoryId( dptr, "NETWORKKEYMEMORY" );

	if( NetworkKeyMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Locating Memory[%s]", "NETWORKKEYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Located with MemoryId[%d]", "NETWORKKEYMEMORY", NetworkKeyMemoryId );

	NetworkKeyMemoryShmid = shmget( ( key_t ) NetworkKeyMemoryId, 0, IPC_CREAT | 0666 );
	if(  NetworkKeyMemoryShmid < 0 )
	{
		dptr->trace( "Error in Creating Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	NetworkKeyMemoryShmPtr = ( struct EzNetworkKey * ) shmat( NetworkKeyMemoryShmid, 0, 0 );
	if( NetworkKeyMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching NetworkKey Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	NetworkKeyMemorySemid = semget( ( key_t ) NetworkKeyMemoryId, 0, IPC_CREAT | 0666 );
	if( NetworkKeyMemorySemid < 0 )
	{
		dptr->trace( "Error in Creating Network Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzSecurityDriverUtil :: getSecuritySharedMemory()
{
	SecurityMemoryId = LocateMemoryId( dptr, "EZSECURITYMEMORY" );

	if( SecurityMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Locating Memory[%s]", "EZSECURITYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Located with MemoryId[%d]", "EZSECURITYMEMORY", SecurityMemoryId );

	SecurityMemoryShmid = shmget( ( key_t ) SecurityMemoryId, 0, IPC_CREAT | 0666 );

	if( SecurityMemoryShmid < 0 )
	{
		dptr->trace( "Error in Creating Security Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SecurityMemoryShmPtr = ( struct EzSecurity * ) shmat( SecurityMemoryShmid, 0, 0 );
	if( SecurityMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching Security Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SecurityMemorySemid = semget( ( key_t ) SecurityMemoryId, 0, IPC_CREAT | 0666 );
	if( SecurityMemorySemid < 0 )
	{
		dptr->trace( "Error in Creating Security Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzSecurityDriverUtil :: getHSMInfoSharedMemory()
{
	HSMInfoMemoryId = LocateMemoryId( dptr, "HSMINFOMEMORY" );

	if( HSMInfoMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Locating Memory[%s]", "HSMINFOMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Located with MemoryId[%d]", "HSMINFOMEMORY", HSMInfoMemoryId );

	HSMInfoMemoryShmid = shmget( ( key_t ) HSMInfoMemoryId, 0, IPC_CREAT | 0666 );

	if( HSMInfoMemoryShmid < 0 )
	{
		dptr->trace( "Error in Getting HSMInfoMemory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	HSMInfoMemoryShmPtr = ( struct EzHSMInfo * ) shmat( HSMInfoMemoryShmid, 0, 0 );
	if( HSMInfoMemoryShmPtr == NULL )
	{
		dptr->trace( "Error in attaching HSMInfo Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	HSMInfoMemorySemid = semget( ( key_t ) HSMInfoMemoryId, 0, IPC_CREAT | 0666 );
	if( HSMInfoMemorySemid < 0 )
	{
		dptr->trace( "Error in HSMInfo Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}


int EzSecurityDriverUtil :: initEzSecurityDriverUtil( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsecurity.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in opening file[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HSM_INSTALLED", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching HSM_INSTALLED from file[%s]", cfgpath );
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
	if( cfgutil.cfg_search( "MAXNETWORKKEYS", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXNETWORKKEYS from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXNETWORKKEYS[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxNetworkKeys = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXDEVICEKEYS", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXDEVICEKEYS from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXDEVICEKEYS[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxDeviceKeys = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXSECURITY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXSECURITY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXSECURITY[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxSecurity = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXHSM", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXHSM from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXHSM[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxHSM = atoi( cfgval );

	cfgutil.cfg_close();


	EzSecurityDriverKey = CreateChannelId( dptr, SECURITYDRIVERCHANNEL );
	if( EzSecurityDriverKey < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Channel[%s]....SysErr[%s] ErrNo[%d]", SECURITYDRIVERCHANNEL, strerror( errno ), errno );
		return -1;
	}

	if( CreateSecurityDriverQueue() < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Queue for Channel[%s]....SysErr[%s] ErrNo[%d]", SECURITYDRIVERCHANNEL, strerror( errno ), errno );
		return -1;
	}

	if( getDeviceKeySharedMemory() < 0 )
		return -1;
	if( getNetworkKeySharedMemory() < 0 )
		return -1;
	if( getSecuritySharedMemory() < 0 )
		return -1;
	if( HSMRequiredFlag )
	{
		if( getHSMInfoSharedMemory() < 0 )
			return -1;
	}
	return 1;
}

int EzSecurityDriverUtil :: CreateSecurityDriverQueue()
{
	EzSecurityDriverQid = msgget( ( key_t ) EzSecurityDriverKey, IPC_CREAT | 0666 );
	if( EzSecurityDriverQid < 0 )
	{
		dptr->trace( "Error in Creating EzSecurityDriver Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzSecurityDriverUtil :: CheckInteger( const char *value )
{
    for( int i = 0; i < strlen( value ); i++ )
    {
        if( ( value[ i ] < 48 ) || ( value[ i ] > 57 ) )
        	return -1;
    }
    return 1;
}

int EzSecurityDriverUtil :: readDeviceKey( const char *DeviceId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxDeviceKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( DeviceKeyMemoryShmPtr + i )->DeviceId, DeviceId ) )
		{
			memset( &DeviceKeyObj, 0, sizeof( struct DeviceKey ) );
			memcpy( &DeviceKeyObj, ( DeviceKeyMemoryShmPtr + i ), sizeof( struct DeviceKey ) );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityDriverUtil :: readNetworkKey( const char *NetworkId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkKeyMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			memset( &NetworkKeyObj, 0, sizeof( struct EzNetworkKey ) );
			memcpy( &NetworkKeyObj, ( NetworkKeyMemoryShmPtr + i ), sizeof( struct EzNetworkKey ) );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityDriverUtil :: readEzSecurity( const char *SecurityId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxSecurity; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for EzSecurity SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( SecurityMemoryShmPtr + i )->SecurityId, SecurityId ) )
		{
			memset( &EzSecurityObj, 0, sizeof( struct EzSecurity ) );
			memcpy( &EzSecurityObj, ( SecurityMemoryShmPtr + i ), sizeof( struct EzSecurity ) );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for EzSecurity SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for EzSecurity SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityDriverUtil :: updateDeviceKey( const char *DeviceId, char *DeviceCommKey )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxDeviceKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( DeviceKeyMemoryShmPtr + i )->DeviceId, DeviceId ) )
		{
			memset( ( DeviceKeyMemoryShmPtr + i )->DeviceCommKey, 0, sizeof( ( DeviceKeyMemoryShmPtr + i )->DeviceCommKey ) );
			strcpy( ( DeviceKeyMemoryShmPtr + i )->DeviceCommKey, DeviceCommKey );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityDriverUtil :: updateAcqNetworkKey( const char *NetworkId, char *NetworkAcqCommKey )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkKeyMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			memset( ( NetworkKeyMemoryShmPtr + i )->NetworkAcqCommKey, 0, sizeof( ( NetworkKeyMemoryShmPtr + i )->NetworkAcqCommKey ) );
			strcpy( ( NetworkKeyMemoryShmPtr + i )->NetworkAcqCommKey, NetworkAcqCommKey );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityDriverUtil :: updateIssNetworkKey( const char *NetworkId, char *NetworkIssCommKey )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkKeyMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			memset( ( NetworkKeyMemoryShmPtr + i )->NetworkIssCommKey, 0, sizeof( ( NetworkKeyMemoryShmPtr + i )->NetworkIssCommKey ) );
			strcpy( ( NetworkKeyMemoryShmPtr + i )->NetworkIssCommKey, NetworkIssCommKey );
			OffSet = i;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}
int EzSecurityDriverUtil :: getSecurityDriverQid()
{
	return EzSecurityDriverQid;
}

char* EzSecurityDriverUtil :: getDeviceMasterKey()
{
	return DeviceKeyObj.DeviceMasterKey;
}

char* EzSecurityDriverUtil :: getDeviceCommKey()
{
	return DeviceKeyObj.DeviceCommKey;
}

int EzSecurityDriverUtil :: getDeviceKeyLen()
{
	return DeviceKeyObj.DeviceKeyLen;
}

char* EzSecurityDriverUtil :: getNetworkMasterKey()
{
	return NetworkKeyObj.NetworkMasterKey;
}

char* EzSecurityDriverUtil :: getAcqNetworkCommKey()
{
	return NetworkKeyObj.NetworkAcqCommKey;
}

char* EzSecurityDriverUtil :: getIssNetworkCommKey()
{
	return NetworkKeyObj.NetworkIssCommKey;
}

int EzSecurityDriverUtil :: getNetworkKeyLen()
{
	return NetworkKeyObj.NetworkKeyLen;
}

char EzSecurityDriverUtil :: getNetworkKeyProperty()
{
	return NetworkKeyObj.KeyProperty;
}

char EzSecurityDriverUtil :: getPINVerificationMethod()
{
	return EzSecurityObj.PINVerificationMethod;
}

char* EzSecurityDriverUtil :: getEPVK()
{
	return EzSecurityObj.EPVK;
}

char* EzSecurityDriverUtil :: getDecimilizationTable()
{
	return EzSecurityObj.DecimilizationTable;
}

char EzSecurityDriverUtil :: getPINPadChar()
{
	return EzSecurityObj.PINPadChar;
}

char EzSecurityDriverUtil :: getPANPadChar()
{
	return EzSecurityObj.PANPadChar;
}

short EzSecurityDriverUtil :: getPINLen()
{
	return EzSecurityObj.PINLen;
}

short EzSecurityDriverUtil :: getPANLen()
{
	return EzSecurityObj.PANLen;
}

short EzSecurityDriverUtil :: getPANValidationOffset()
{
	return EzSecurityObj.PANValidationOffset;
}

char* EzSecurityDriverUtil :: getPINBlockFormat()
{
	return EzSecurityObj.PINBlockFormat;
}

short EzSecurityDriverUtil :: getPANValidationLength()
{
	return EzSecurityObj.PANValidationLength;
}

int EzSecurityDriverUtil :: readHSMInfoMemory( const char *HSMName )
{
	struct sembuf sem_buf;
	int retval = -1;
	for( int i = 0; i < MaxHSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for HSMInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( HSMInfoMemoryShmPtr + i )->HSMName, HSMName ) )
		{
			retval = 1;
			memcpy( &HSMInfoObj, 0, sizeof( struct EzHSMInfo ) );
			sem_buf.sem_op = 2;
			if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for HSMInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for HSMInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

bool EzSecurityDriverUtil :: isHSMConnected()
{
	if( HSMInfoObj.HSMStatus == EZSEC_HSM_CONNECTED )
		return true;
	else
		return false;
}

int EzSecurityDriverUtil :: updateHSMInfoMemoryStatus( const char *HSMName, int HSMStatus )
{
	struct sembuf sem_buf;
	int retval = -1;
	for( int i = 0; i < MaxHSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for HSMInfoMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( HSMInfoMemoryShmPtr + i )->HSMName, HSMName ) )
		{
			retval = 1;
			( HSMInfoMemoryShmPtr + i )->HSMStatus = HSMStatus;
			sem_buf.sem_op = 2;
			if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for HSMInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for HSMInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

