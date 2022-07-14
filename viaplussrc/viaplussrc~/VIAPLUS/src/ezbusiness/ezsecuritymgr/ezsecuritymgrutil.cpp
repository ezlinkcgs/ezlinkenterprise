#include <ezbusiness/ezsecuritymgrutil.h>

EzSecurityMgrUtil :: EzSecurityMgrUtil()
{
}

EzSecurityMgrUtil :: ~ EzSecurityMgrUtil()
{
}

int EzSecurityMgrUtil :: initEzSecurityMgrUtil( const char *TaskName, EzDebugUtil *dptr )
{
    char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
    EzCfgUtil cfgutil;
    this->dptr = dptr;

    if ( initEzSecurityMgrODBC( TaskName, dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing EzSecurityMgrUtil" );
		return -1;
	}

    ATMKeyMemoryId = CreateMemoryId( dptr, "ATMKEYMEMORY" );

	if( ATMKeyMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", "ATMKEYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", "ATMKEYMEMORY", ATMKeyMemoryId );

    NetworkKeyMemoryId = CreateMemoryId( dptr, "NETWORKKEYMEMORY" );

    if( NetworkKeyMemoryId < 0 )
    {
    	dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", "NETWORKKEYMEMORY" );
    	return -1;
    }
    dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", "NETWORKKEYMEMORY", NetworkKeyMemoryId );

    DeviceKeyMemoryId = CreateMemoryId( dptr, "DEVICEKEYMEMORY" );

	if( DeviceKeyMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", "DEVICEKEYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", "DEVICEKEYMEMORY", DeviceKeyMemoryId );

	SecurityMemoryId = CreateMemoryId( dptr, "EZSECURITYMEMORY" );

	if( SecurityMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", "EZSECURITYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", "EZSECURITYMEMORY", SecurityMemoryId );

	SecurityPropertyMemoryId = CreateMemoryId( dptr, "EZSECPROPERTYMEMORY" );

	if( SecurityPropertyMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", "EZSECPROPERTYMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", "EZSECPROPERTYMEMORY", SecurityPropertyMemoryId );

	HSMInfoMemoryId = CreateMemoryId( dptr, "HSMINFOMEMORY" );

	if( HSMInfoMemoryId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", "HSMINFOMEMORY" );
		return -1;
	}
	dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", "HSMINFOMEMORY", HSMInfoMemoryId );

    memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsecurity.cfg" );

    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
        dptr->trace( "Error in opening file[%s]", cfgpath );
        return -1;
    }

    memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MAXATMKEYS", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXATMKEYS from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXATMKEYS[%s] value defined in file[%s]", cfgval, cfgpath );
		return -1;
	}
	MaxATMKeys = atoi( cfgval );

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
	if( cfgutil.cfg_search( "MAXSECURITYPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MAXSECURITYPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( "Invalid MAXSECURITYPROPERTY[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxSecurityProperty = atoi( cfgval );

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

    return 1;
}

int EzSecurityMgrUtil :: CheckInteger( const char *value )
{
	for( int i = 0; i < strlen( value ); i++ )
    {
		if( ( value[ i ] < 48 ) || ( value[ i ] > 57 ) )
		return -1;
	}
	return 1;
}

int EzSecurityMgrUtil :: LoadHSMInfoMemory()
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ], ParamStr[ 200 ];
	EzCfgUtil cfgutil;
	struct EzHSMInfo hsminfo;

	HSMInfoMemoryShmid = shmget( ( key_t ) HSMInfoMemoryId, sizeof( struct EzHSMInfo ) * MaxHSM, IPC_CREAT | 0666 );

    if( HSMInfoMemoryShmid < 0 )
    {
		dptr->trace( "Error in Creating HSMInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }

    HSMInfoMemoryShmPtr = ( struct EzHSMInfo * ) shmat( HSMInfoMemoryShmid, 0, 0 );

    if( HSMInfoMemoryShmPtr == NULL )
    {
		dptr->trace( "Error in attaching HSMInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }

	for( int i = 0; i < MaxHSM; i++ )
	{
		memset( ( HSMInfoMemoryShmPtr + i ), 0, sizeof( struct EzHSMInfo ) );
		strcpy( ( HSMInfoMemoryShmPtr + i )->HSMName, EZSEC_HSM_INIT_NAME );
	}

	int SqlErr;

	int HSMCount = getHSMCount( &SqlErr );

	if( HSMCount < 0 )
	{
		dptr->trace( "Error in getting HSMCount from EzHSMInfo Table... OraErr[%05d]", SqlErr );
		return -1;
	}

	dptr->trace( "HSMCount[%d]", HSMCount );

	if( HSMCount > MaxHSM )
	{
		dptr->trace( "No. of HSMs Configured[%d] > MaxHSM[%d]", HSMCount, MaxHSM );
		cfgutil.cfg_close();
		return -1;
	}

	if( LoadHSMInfo( HSMInfoMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading EzHSMInfo Table OraErr[%05d]", SqlErr );
		return -1;
	}

	HSMInfoMemorySemid = semget( ( key_t ) HSMInfoMemoryId, MaxHSM, IPC_CREAT | 0666 );

	if( HSMInfoMemorySemid < 0 )
	{
		dptr->trace( "Error in HSMInfo Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxHSM; i++ )
	{
		if( semctl( HSMInfoMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting HSMInfoMemory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityMgrUtil :: getHSMInfoMemory()
{
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

int EzSecurityMgrUtil :: LoadATMKeyMemory()
{

	ATMKeyMemoryShmid = shmget( ( key_t ) ATMKeyMemoryId, sizeof( struct EzATMKey ) * MaxATMKeys, IPC_CREAT | 0666 );

    if(  ATMKeyMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;

    }

    ATMKeyMemoryShmPtr = ( struct EzATMKey * ) shmat( ATMKeyMemoryShmid, 0, 0 );

    if( ATMKeyMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching ATM Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

	for( int i = 0; i < MaxATMKeys; i++ )
	{
		memset( ( ATMKeyMemoryShmPtr + i ), 0, sizeof( struct EzATMKey ) );
		strcpy( ( ATMKeyMemoryShmPtr + i )->ATMId, EZSEC_ATMKEYID_INIT_VAL );
	}

	int ATMCount = getATMCount( &SqlErr );

	if( ATMCount < 0 )
	{
		dptr->trace( "Error in getting ATMCount from EzATMInfo Table... OraErr[%05d]", SqlErr );
		return -1;
	}

	dptr->trace( "ATMCount[%d]", ATMCount );

	if( ATMCount > MaxATMKeys )
	{
		dptr->trace( "No.of ATMs configured in EzATMInfo Table > MaxATMKeys...Increase the MaxATMKeys Parameter");
		return -1;
	}

	if( LoadATMKey( ATMKeyMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading ATMKey from EzATMInfo Table OraErr[%05d]", SqlErr );
		return -1;
	}

	ATMKeyMemorySemid = semget( ( key_t ) ATMKeyMemoryId, MaxATMKeys, IPC_CREAT | 0666 );

    if( ATMKeyMemorySemid < 0 )
	{
    	dptr->trace( "Error in Creating ATM Key Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxATMKeys; i++ )
	{
		if( semctl( ATMKeyMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting ATM Key Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityMgrUtil :: getATMKeyMemory()
{
	ATMKeyMemoryShmid = shmget( ( key_t ) ATMKeyMemoryId, 0, IPC_CREAT | 0666 );

    if( ATMKeyMemoryShmid < 0 )
    {
		dptr->trace( "Error in Creating ATMKey Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }

    ATMKeyMemoryShmPtr = ( struct EzATMKey * ) shmat( ATMKeyMemoryShmid, 0, 0 );
    if( ATMKeyMemoryShmPtr == NULL )
    {
		dptr->trace( "Error in attaching ATMKey Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }

    ATMKeyMemorySemid = semget( ( key_t ) ATMKeyMemoryId, 0, IPC_CREAT | 0666 );
    if( ATMKeyMemorySemid < 0 )
    {
		dptr->trace( "Error in Creating ATMKey Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }
	return 1;
}


int EzSecurityMgrUtil :: LoadNetworkKeyMemory()
{
	NetworkKeyMemoryShmid = shmget( ( key_t ) NetworkKeyMemoryId, sizeof( struct EzNetworkKey ) * MaxNetworkKeys, IPC_CREAT | 0666 );

    if(  NetworkKeyMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;

    }

    NetworkKeyMemoryShmPtr = ( struct EzNetworkKey * ) shmat( NetworkKeyMemoryShmid, 0, 0 );

    if( NetworkKeyMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		memset( ( NetworkKeyMemoryShmPtr + i ), 0, sizeof( struct EzNetworkKey ) );
		strcpy( ( NetworkKeyMemoryShmPtr + i )->NetworkId, EZSEC_NETWORKKEYID_INIT_VAL );
	}

	NetworkCount = getEzNetworkCount( &SqlErr );

	if( NetworkCount < 0 )
	{
		dptr->trace( "Error in getting EzNetworkkey Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	dptr->trace( "  NetworkCount [%d]", NetworkCount );
	if( NetworkCount > MaxNetworkKeys )
	{
		dptr->trace( "No.of Networks configued in EzNetworkKey Table > MaxNetworks...Increase the MaxNetworks Parameter");
		return -1;
	}

	if( LoadEzNetworkKey( NetworkKeyMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading EzNetwork Table OraErr[%04d]", SqlErr );
		return -1;
	}

	NetworkKeyMemorySemid = semget( ( key_t ) NetworkKeyMemoryId, MaxNetworkKeys, IPC_CREAT | 0666 );

    if( NetworkKeyMemorySemid < 0 )
	{
    	dptr->trace( "Error in Creating Network Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		if( semctl( NetworkKeyMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting Network Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityMgrUtil :: getNetworkKeyMemory()
{
	NetworkKeyMemoryShmid = shmget( ( key_t ) NetworkKeyMemoryId, 0, IPC_CREAT | 0666 );

    if(  NetworkKeyMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

    NetworkKeyMemoryShmPtr = ( struct EzNetworkKey * ) shmat( NetworkKeyMemoryShmid, 0, 0 );
    if( NetworkKeyMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

int EzSecurityMgrUtil :: LoadDeviceKeyMemory()
{
	DeviceKeyMemoryShmid = shmget( ( key_t ) DeviceKeyMemoryId, sizeof( struct DeviceKey ) * MaxDeviceKeys, IPC_CREAT | 0666 );

    if(  DeviceKeyMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating Device Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;

    }

    DeviceKeyMemoryShmPtr = ( struct DeviceKey * ) shmat( DeviceKeyMemoryShmid , 0, 0 );

    if( DeviceKeyMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching Device Key Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

	for( int i = 0; i < MaxDeviceKeys; i++ )
	{
		memset( ( DeviceKeyMemoryShmPtr + i ), 0, sizeof( struct EzNetworkKey ) );
		strcpy( ( DeviceKeyMemoryShmPtr + i )->DeviceId, EZSEC_DEVICEKEYID_INIT_VAL );
	}

	DeviceCount = getDeviceKeyCount( &SqlErr );

	if( DeviceCount < 0 )
	{
		dptr->trace( "Error in getting DeviceKey Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( DeviceCount > MaxDeviceKeys )
	{
		dptr->trace( "No.of Devices configured in DeviceKey Table > MaxDeviceKeys...Increase the MaxDeviceKeys Parameter");
		return -1;
	}

	if( LoadDeviceKey( DeviceKeyMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading DeviceKey Table OraErr[%04d]", SqlErr );
		return -1;
	}

	DeviceKeyMemorySemid = semget( ( key_t ) DeviceKeyMemoryId, MaxDeviceKeys, IPC_CREAT | 0666 );

    if( DeviceKeyMemorySemid < 0 )
	{
    	dptr->trace( "Error in Creating DeviceKey Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxDeviceKeys; i++ )
	{
		if( semctl( DeviceKeyMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting DeviceKey Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityMgrUtil :: getDeviceKeyMemory()
{
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

int EzSecurityMgrUtil :: LoadSecurityMemory()
{
	int SecurityCount;
	SecurityMemoryShmid = shmget( ( key_t ) SecurityMemoryId, sizeof( struct EzSecurity ) * MaxSecurity, IPC_CREAT | 0666 );

    if(  SecurityMemoryShmid < 0 )
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

	for( int i = 0; i < MaxSecurity; i++ )
	{
		memset( ( SecurityMemoryShmPtr + i ), 0, sizeof( struct EzSecurity ) );
		strcpy( ( SecurityMemoryShmPtr + i )->SecurityId, EZSEC_SECURITYID_INIT_VAL );
	}

	SecurityCount = getSecurityCount( &SqlErr );

	if( SecurityCount < 0 )
	{
		dptr->trace( "Error in getting EzSecurity Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( SecurityCount > MaxSecurity )
	{
		dptr->trace( "No.of SecurityId configured in EzSecurity Table > MaxSecurityIds...Increase the MaxSecurity Parameter");
		return -1;
	}

	if( LoadSecurity( SecurityMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading EzSecurity Table OraErr[%04d]", SqlErr );
		return -1;
	}

	for( int i = 0; i < MaxSecurity; i++ )
	{
		dptr->trace( " ( SecurityMemoryShmPtr + i )->SecurityId[%s])", ( SecurityMemoryShmPtr + i )->SecurityId );
	}

	SecurityMemorySemid = semget( ( key_t ) SecurityMemoryId, MaxSecurity, IPC_CREAT | 0666 );

	if( SecurityMemorySemid < 0 )
	{
    	dptr->trace( "Error in Creating EzSecurity Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxSecurity; i++ )
	{
		if( semctl( SecurityMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzSecurity Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityMgrUtil :: getSecurityMemory()
{
	SecurityMemoryShmid = shmget( ( key_t ) SecurityMemoryId, 0, IPC_CREAT | 0666 );

    if(  SecurityMemoryShmid < 0 )
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

int EzSecurityMgrUtil :: LoadSecurityPropertyMemory()
{
	int SecurityPropertyCount;
	SecurityPropertyMemoryShmid = shmget( ( key_t ) SecurityPropertyMemoryId, sizeof( struct EzSecurityProperty ) * MaxSecurityProperty, IPC_CREAT | 0666 );

    if(  SecurityPropertyMemoryShmid < 0 )
    {
		dptr->trace( "Error in Creating SecurityProperty Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }

    SecurityPropertyMemoryShmPtr = ( struct EzSecurityProperty * ) shmat( SecurityPropertyMemoryShmid, 0, 0 );

    if( SecurityPropertyMemoryShmPtr == NULL )
    {
		dptr->trace( "Error in attaching SecurityProperty Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }

	for( int i = 0; i < MaxSecurityProperty; i++ )
	{
		memset( ( SecurityPropertyMemoryShmPtr + i ), 0, sizeof( struct EzSecurityProperty ) );
		strcpy( ( SecurityPropertyMemoryShmPtr + i )->RecordId, EZSEC_SECURITYPROPERTY_INIT_VAL );
	}

	SecurityPropertyCount = getSecurityPropertyCount( &SqlErr );

	if( SecurityPropertyCount < 0 )
	{
		dptr->trace( "Error in getting EzSecurityProperty Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( SecurityPropertyCount > MaxSecurityProperty )
	{
		dptr->trace( "No.of SecurityProperty configured in EzSecurityProperty Table > MaxSecurityProperty...Increase the MaxSecurityProperty Parameter");
		return -1;
	}

	if( LoadSecurityProperty( SecurityPropertyMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading EzSecurityProperty Table OraErr[%04d]", SqlErr );
		return -1;
	}

	SecurityPropertyMemorySemid = semget( ( key_t ) SecurityPropertyMemoryId, MaxSecurityProperty, IPC_CREAT | 0666 );

	if( SecurityPropertyMemorySemid < 0 )
	{
    	dptr->trace( "Error in Creating EzSecurityProperty Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
	}

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxSecurityProperty; i++ )
	{
		if( semctl( SecurityPropertyMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzSecurityProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityMgrUtil :: getSecurityPropertyMemory()
{
	SecurityPropertyMemoryShmid = shmget( ( key_t ) SecurityPropertyMemoryId, 0, IPC_CREAT | 0666 );

    if(  SecurityPropertyMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating SecurityProperty Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

    SecurityPropertyMemoryShmPtr = ( struct EzSecurityProperty * ) shmat( SecurityPropertyMemoryShmid, 0, 0 );
    if( SecurityPropertyMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching SecurityProperty Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

    SecurityPropertyMemorySemid = semget( ( key_t ) SecurityPropertyMemoryId, 0, IPC_CREAT | 0666 );
    if( SecurityMemorySemid < 0 )
    {
		dptr->trace( "Error in Creating SecurityProperty Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
    }
	return 1;
}

