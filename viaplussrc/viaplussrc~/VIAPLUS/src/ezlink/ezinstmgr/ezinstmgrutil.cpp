#include <ezlink/ezinstmgrutil.h>

int EzInstMgrUtil :: initInstMgrUtil( const char *TaskName, EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXINSTROUTETYPE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXINSTROUTETYPE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxInstRouteType = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXINSTSELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXINSTSELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxInstSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXBINSELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXBINSELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxBINSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXINSTPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXINSTPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxInstProfile = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXBINPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXBINPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxBINProfile = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXNETWORKSELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXNETWORKSELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxNetworkSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXBINRANGE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXBINRANGE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxBINRange = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXBRANCHPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXBRANCHPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxBranchProfile = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXAUTHPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXAUTHPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxAuthProperty = atoi( cfgval );

	dptr->trace( DEBUG_NORMAL, "MaxInstSelect[%d] MaxInstProfile[%d] MaxBINProfile[%d] MaxNetworkSelect[%d] MaxBINRange[%d] MaxBranchProfile[%d] MaxAuthProperty[%d]", MaxInstSelect, MaxInstProfile, MaxBINProfile, MaxNetworkSelect, MaxBINRange, MaxBranchProfile, MaxAuthProperty );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXDEVICETYPEMAP", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXDEVICETYPEMAP from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxDeviceTypeMap = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXCHANNELPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXCHANNELPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxChannelProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXEVENTPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXEVENTPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxEventProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXINBOUNDMSGPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXINBOUNDMSGPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxInBoundMsgProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXMSGTRANSLATE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXMSGTRANSLATE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxMsgTranslate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXMSGTYPEPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXMSGTYPEPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxMsgTypeProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXTXNREFSELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXTXNREFSELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTxnRefSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXTXNROUTEINFO", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXTXNROUTEINFO from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTxnRouteInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXTXNROUTESELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXTXNROUTESELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTxnRouteSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXTXNMSGORDER", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXTXNMSGORDER from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTxnMsgOrder = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXINSTEXTNTWKPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXINSTEXTNTWKPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxInstExtNtwkProfile = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXEXTNTWKPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXEXTNTWKPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxExtNtwkProfile = atoi( cfgval );


	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTDB#MAXSAFPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching INSTDB#MAXSAFPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxSafProperty = atoi( cfgval );

	cfgutil.cfg_close();

	if( ezlicenseutil.initLicenseUtil( dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing LicenseUtil...." );
		return -1;
	}

	if( initEzInstMgrODBC( TaskName, dptr ) < 0 )
	{
		dptr->trace( "Error in Initializing initEzInstMgrODBC...." );
		return -1;
	}
	return 1;
}

int EzInstMgrUtil :: LoadInstRouteType()
{
	InstRouteTypeMemoryId = CreateMemoryId( dptr, "INSTROUTETYPEMEMORY" );

	if( InstRouteTypeMemoryId < 0 )
	{
		dptr->trace( "Error in Creating INSTROUTETYPEMEMORY..." );
		return -1;
	}

	InstRouteTypeShmId = shmget ( ( key_t ) InstRouteTypeMemoryId, sizeof( struct EzInstRouteTypeMemory ) * MaxInstRouteType, IPC_CREAT | 0666 );

	if( InstRouteTypeShmId < 0 )
	{
		dptr->trace( "Error in Creating InstRouteType Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstRouteTypeShmPtr = ( struct EzInstRouteTypeMemory * ) shmat( InstRouteTypeShmId, 0, 0 );

	if( InstRouteTypeShmPtr == NULL )
	{
		dptr->trace( "Error in attaching InstRouteType Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstRouteTypeSemId = semget ( ( key_t ) InstRouteTypeMemoryId, MaxInstRouteType, IPC_CREAT | 0666 );

	if( InstRouteTypeSemId < 0 )
	{
		dptr->trace( "Error in Creating InstRouteType Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "InstRouteType Semaphore Created with SemId[%d]", InstRouteTypeSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxInstRouteType; i++ )
	{
		if( semctl( InstRouteTypeSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting InstRouteType Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxInstRouteType; i++ )
	{
		memset( ( InstRouteTypeShmPtr + i ), 0, sizeof( struct EzInstRouteTypeMemory ) );
		strcpy( ( InstRouteTypeShmPtr + i )->InstRouteType, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int InstRouteTypeCount = getEzInstRouteTypeCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in Getting EzInstRouteType Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( InstRouteTypeCount > MaxInstRouteType )
	{
		dptr->trace( "InstRouteTypeCount[%d] > MaxInstRouteType[%d]", InstRouteTypeCount, MaxInstRouteType );
		return -1;
	}

	if( LoadEzInstRouteType( InstRouteTypeShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzInstRouteType......OraErr[%05d]", SqlErr );
		return -1;
	}


	for( int i = 0; i < InstRouteTypeCount; i++ )
	{
		if( !ezlicenseutil.isValidInstRouteType( ( InstRouteTypeShmPtr + i )->InstRouteType ) )
		{
			dptr->trace( "InstRouteType [%s] is not Licensed to be Included.....", ( InstRouteTypeShmPtr + i )->InstRouteType );
			memset( ( InstRouteTypeShmPtr + i ), 0, sizeof( struct EzInstRouteTypeMemory ) );
			strcpy( ( InstRouteTypeShmPtr + i )->InstRouteType, RECORD_INIT_VAL );
		}
	}

	return 1;
}

int EzInstMgrUtil :: LoadInstProfile()
{
	InstProfileMemoryId = CreateMemoryId( dptr, "INSTPROFILEMEMORY" );

	if( InstProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating INSTPROFILEMEMORY..." );
		return -1;
	}

	InstProfileShmId = shmget ( ( key_t ) InstProfileMemoryId, sizeof( struct EzInstProfileMemory ) * MaxInstProfile, IPC_CREAT | 0666 );

	if( InstProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating InstProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstProfileShmPtr = ( struct EzInstProfileMemory * ) shmat( InstProfileShmId, 0, 0 );

	if( InstProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching InstProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstProfileSemId = semget ( ( key_t ) InstProfileMemoryId, MaxInstProfile, IPC_CREAT | 0666 );

	if( InstProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating InstProfile Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "InstProfile Semaphore Created with SemId[%d]", InstProfileSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxInstProfile; i++ )
	{
		if( semctl( InstProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting InstProfile Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxInstProfile; i++ )
	{
		memset( ( InstProfileShmPtr + i ), 0, sizeof( struct EzInstProfileMemory ) );
		strcpy( ( InstProfileShmPtr + i )->InstId, RECORD_INIT_VAL  );
	}

	int SqlErr=0;
	InstProfileCount = getEzInstProfileCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in Getting EzInstProfile Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( InstProfileCount > MaxInstProfile )
	{
		dptr->trace( "InstProfileCount[%d] > MaxInstProfile[%d]", InstProfileCount, MaxInstProfile );
		return -1;
	}

	if( LoadEzInstProfile( InstProfileShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzInstProfile......OraErr[%05d]", SqlErr );
		return -1;
	}

	int TempInstProfileCount = 0;

	for( int i = 0; i < InstProfileCount; i++ )
	{
		if( !ezlicenseutil.isValidInst( ( InstProfileShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstType ) )
		{
			dptr->trace( "InstId[%s] InstType[%s] is not Licensed to be Included.....", ( InstProfileShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstType );
			memset( ( InstProfileShmPtr + i ), 0, sizeof( struct EzInstProfileMemory ) );
			strcpy( ( InstProfileShmPtr + i )->InstId, RECORD_INIT_VAL  );
			TempInstProfileCount++;
		}
	}
	InstProfileCount = InstProfileCount - TempInstProfileCount;

	return 1;
}

int EzInstMgrUtil :: LoadInstSelect()
{
	InstSelectMemoryId = CreateMemoryId( dptr, "INSTSELECTMEMORY" );

	if( InstSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating INSTSELECTMEMORY..." );
		return -1;
	}

	InstSelectShmId = shmget ( ( key_t ) InstSelectMemoryId, sizeof( struct EzInstSelectMemory ) * MaxInstSelect, IPC_CREAT | 0666 );

	if( InstSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating InstSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstSelectShmPtr = ( struct EzInstSelectMemory * ) shmat( InstSelectShmId, 0, 0 );

	if( InstSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching InstSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstSelectSemId = semget ( ( key_t ) InstSelectMemoryId, MaxInstSelect, IPC_CREAT | 0666 );

	if( InstSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating InstSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "InstSelect Semaphore Created with SemId[%d]", InstSelectSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxInstSelect; i++ )
	{
		if( semctl( InstSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting InstSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxInstSelect; i++ )
	{
		memset( ( InstSelectShmPtr + i ), 0, sizeof( struct EzInstSelectMemory ) );
		strcpy( ( InstSelectShmPtr + i )->RecordId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int InstSelectCount = getEzInstSelectCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzInstSelect Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( InstSelectCount > MaxInstSelect )
	{
		dptr->trace( "InstSelectCount[%d] > MaxInstSelect[%d]", InstSelectCount, MaxInstSelect );
		return -1;
	}

	if( LoadEzInstSelect( InstSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzInstSelect......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzInstMgrUtil :: LoadBINSelect()
{
	BINSelectMemoryId = CreateMemoryId( dptr, "BINSELECTMEMORY" );

	if( BINSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating BINSELECTMEMORY..." );
		return -1;
	}

	BINSelectShmId = shmget ( ( key_t ) BINSelectMemoryId, sizeof( struct EzBINSelectMemory ) * MaxBINSelect, IPC_CREAT | 0666 );

	if( BINSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating BINSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BINSelectShmPtr = ( struct EzBINSelectMemory * ) shmat( BINSelectShmId, 0, 0 );

	if( BINSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching BINSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BINSelectSemId = semget ( ( key_t ) BINSelectMemoryId, MaxBINSelect, IPC_CREAT | 0666 );

	if( BINSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating BINSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "BINSelect Semaphore Created with SemId[%d]", InstSelectSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxBINSelect; i++ )
	{
		if( semctl( BINSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting BINSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxBINSelect; i++ )
	{
		memset( ( BINSelectShmPtr + i ), 0, sizeof( struct EzBINSelectMemory ) );
		strcpy( ( BINSelectShmPtr + i )->RecordId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int BINSelectCount = getEzBINSelectCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzBINSelect Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( BINSelectCount > MaxBINSelect )
	{
		dptr->trace( "BINSelectCount[%d] > MaxBINSelect[%d]", BINSelectCount, MaxBINSelect );
		return -1;
	}

	if( LoadEzBINSelect( BINSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzBINSelect......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}



int EzInstMgrUtil :: LoadNetworkSelect()
{
	NetworkSelectMemoryId = CreateMemoryId( dptr, "NETWORKSELECTMEMORY" );

	if( NetworkSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating NETWORKSELECTMEMORY..." );
		return -1;
	}

	NetworkSelectShmId = shmget ( ( key_t ) NetworkSelectMemoryId, sizeof( struct EzNetworkSelectMemory ) * MaxNetworkSelect, IPC_CREAT | 0666 );

	if( NetworkSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating NetworkSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkSelectShmPtr = ( struct EzNetworkSelectMemory * ) shmat( NetworkSelectShmId, 0, 0 );

	if( NetworkSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching NetworkSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkSelectSemId = semget ( ( key_t ) NetworkSelectMemoryId, MaxNetworkSelect, IPC_CREAT | 0666 );

	if( NetworkSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating NetworkSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "NetworkSelect Semaphore Created with SemId[%d]", NetworkSelectSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxNetworkSelect; i++ )
	{
		if( semctl( NetworkSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting NetworkSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxNetworkSelect; i++ )
	{
		memset( ( NetworkSelectShmPtr + i ), 0, sizeof( struct EzNetworkSelectMemory ) );
		strcpy( ( NetworkSelectShmPtr + i )->RecordId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int NetworkSelectCount = getEzNetworkSelectCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzNetworkSelect Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( NetworkSelectCount > MaxNetworkSelect )
	{
		dptr->trace( "NetworkSelectCount[%d] > MaxNetworkSelect[%d]", NetworkSelectCount, MaxNetworkSelect );
		return -1;
	}

	if( LoadEzNetworkSelect( NetworkSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzNetworkSelect......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzInstMgrUtil :: LoadBINProfile()
{
	BINProfileMemoryId = CreateMemoryId( dptr, "BINPROFILEMEMORY" );

	if( BINProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating BINPROFILEMEMORY..." );
		return -1;
	}

	BINProfileShmId = shmget ( ( key_t ) BINProfileMemoryId, sizeof( struct EzBINProfileMemory ) * MaxBINProfile, IPC_CREAT | 0666 );

	if( BINProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating BINProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BINProfileShmPtr = ( struct EzBINProfileMemory * ) shmat( BINProfileShmId, 0, 0 );

	if( BINProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching BINProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BINProfileSemId = semget ( ( key_t ) BINProfileMemoryId, MaxBINProfile, IPC_CREAT | 0666 );

	if( BINProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating BINProfile Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "BINProfile Semaphore Created with SemId[%d]", BINProfileSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxBINProfile; i++ )
	{
		if( semctl( BINProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting BINProfile Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxBINProfile; i++ )
	{
		memset( ( BINProfileShmPtr + i ), 0, sizeof( struct EzBINProfileMemory ) );
		strcpy( ( BINProfileShmPtr + i )->InstId, RECORD_INIT_VAL );
		strcpy( ( BINProfileShmPtr + i )->BIN, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int BINProfileCount = getEzBINProfileCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzBINProfile Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( BINProfileCount > MaxBINProfile )
	{
		dptr->trace( "BINProfileCount[%d] > MaxBINProfile[%d]", BINProfileCount, MaxBINProfile );
		return -1;
	}

	if( LoadEzBINProfile( BINProfileShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzBINProfile......OraErr[%05d]", SqlErr );
		return -1;
	}

	int BINLimit = 0, BINCount = 0;

	for( int i = 0; i < InstProfileCount; i++ )
	{
		if( ezlicenseutil.isBINCheckReq( ( InstProfileShmPtr + i )->InstId ) && !strcasecmp( ( InstProfileShmPtr + i )->InstId, "FIN" ) )
		{
			dptr->trace( "BIN Check is Required for InstId[%s]", ( InstProfileShmPtr + i )->InstId );
			BINLimit = ezlicenseutil.getBINLimit( ( InstProfileShmPtr + i )->InstId );
			if( BINLimit > 0 )
			{
				BINCount = 0;
				for( int j = 0; j < BINProfileCount; j++ )
				{
					if( !strcmp( ( InstProfileShmPtr + i )->InstId, ( BINProfileShmPtr + j )->InstId ) )
						BINCount++;
				}
				if( BINCount > BINLimit )
				{
					dptr->trace( "No. of BINs for InstId[%s] Configured is [%d] > License Limit [%d]", ( InstProfileShmPtr + i )->InstId, BINCount, BINLimit );
					BINCount = 0;
					for( int j = 0; j < BINProfileCount; j++ )
					{
						if( !strcmp( ( InstProfileShmPtr + i )->InstId, ( BINProfileShmPtr + j )->InstId ) )
						{
							BINCount++;
							if( BINCount > BINLimit )
							{
								memset( ( BINProfileShmPtr + j ), 0, sizeof( struct EzBINProfileMemory ) );
								strcpy( ( BINProfileShmPtr + j )->InstId, RECORD_INIT_VAL );
								strcpy( ( BINProfileShmPtr + j )->BIN, RECORD_INIT_VAL );
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

int EzInstMgrUtil :: LoadBranchProfile()
{
	BranchProfileMemoryId = CreateMemoryId( dptr, "BRANCHPROFILEMEMORY" );

	if( BranchProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating BRANCHPROFILEMEMORY..." );
		return -1;
	}

	BranchProfileShmId = shmget ( ( key_t ) BranchProfileMemoryId, sizeof( struct EzBranchProfileMemory ) * MaxBranchProfile, IPC_CREAT | 0666 );

	if( BranchProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating BranchProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BranchProfileShmPtr = ( struct EzBranchProfileMemory * ) shmat( BranchProfileShmId, 0, 0 );

	if( BranchProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching BranchProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BranchProfileSemId = semget ( ( key_t ) BranchProfileMemoryId, MaxBranchProfile, IPC_CREAT | 0666 );

	if( BranchProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating BranchProfile Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "BranchProfile Semaphore Created with SemId[%d]", BranchProfileSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxBranchProfile; i++ )
	{
		if( semctl( BranchProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting BranchProfile Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxBranchProfile; i++ )
	{
		memset( ( BranchProfileShmPtr + i ), 0, sizeof( struct EzBranchProfileMemory ) );
		strcpy( ( BranchProfileShmPtr + i )->InstId, RECORD_INIT_VAL );
		strcpy( ( BranchProfileShmPtr + i )->BranchCode, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int BranchProfileCount = getEzBranchProfileCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzBranchProfile Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( BranchProfileCount > MaxBranchProfile )
	{
		dptr->trace( "BranchProfileCount[%d] > MaxBranchProfile[%d]", BranchProfileCount, MaxBranchProfile );
		return -1;
	}

	if( LoadEzBranchProfile( BranchProfileShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzBranchProfile......OraErr[%05d]", SqlErr );
		return -1;
	}

	int BranchLimit = 0, BranchCount = 0;

	for( int i = 0; i < InstProfileCount; i++ )
	{
		if( ezlicenseutil.isBranchCheckReq( ( InstProfileShmPtr + i )->InstId ) )
		{
			dptr->trace( "BIN Check is Required for InstId[%s]", ( InstProfileShmPtr + i )->InstId );
			BranchLimit = ezlicenseutil.getBranchLimit( ( InstProfileShmPtr + i )->InstId );
			if( BranchLimit > 0 )
			{
				BranchCount = 0;
				for( int j = 0; j < BranchProfileCount; j++ )
				{
					if( !strcmp( ( InstProfileShmPtr + i )->InstId, ( BranchProfileShmPtr + j )->InstId ) )
						BranchCount++;
				}
				if( BranchCount > BranchLimit )
				{
					dptr->trace( "No. of Branch for InstId[%s] Configured is [%d] > License Limit [%d]", ( InstProfileShmPtr + i )->InstId, BranchCount, BranchLimit );
					BranchCount = 0;
					for( int j = 0; j < BranchProfileCount; j++ )
					{
						if( !strcmp( ( InstProfileShmPtr + i )->InstId, ( BranchProfileShmPtr + j )->InstId ) )
						{
							BranchCount++;
							if( BranchCount > BranchLimit )
							{
								memset( ( BranchProfileShmPtr + j ), 0, sizeof( struct EzBranchProfileMemory ) );
								strcpy( ( BranchProfileShmPtr + j )->InstId, RECORD_INIT_VAL );
								strcpy( ( BranchProfileShmPtr + j )->BranchCode, RECORD_INIT_VAL );
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

int EzInstMgrUtil :: LoadBINRange()
{
	BINRangeMemoryId = CreateMemoryId( dptr, "BINRANGEMEMORY" );

	if( BINRangeMemoryId < 0 )
	{
		dptr->trace( "Error in Creating BINRANGEMEMORY..." );
		return -1;
	}

	BINRangeShmId = shmget ( ( key_t ) BINRangeMemoryId, sizeof( struct EzBINRangeMemory ) * MaxBINRange, IPC_CREAT | 0666 );

	if( BINRangeShmId < 0 )
	{
		dptr->trace( "Error in Creating BINRange Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BINRangeShmPtr = ( struct EzBINRangeMemory * ) shmat( BINRangeShmId, 0, 0 );

	if( BINRangeShmPtr == NULL )
	{
		dptr->trace( "Error in attaching BINRange Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	BINRangeSemId = semget ( ( key_t ) BINRangeMemoryId, MaxBINRange, IPC_CREAT | 0666 );

	if( BINRangeSemId < 0 )
	{
		dptr->trace( "Error in Creating BINRange Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "BINRange Semaphore Created with SemId[%d]", BINRangeSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxBINRange; i++ )
	{
		if( semctl( BINRangeSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting BINRange Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxBINRange; i++ )
	{
		memset( ( BINRangeShmPtr + i ), 0, sizeof( struct EzBINRangeMemory ) );
		strcpy( ( BINRangeShmPtr + i )->InstId, RECORD_INIT_VAL );
		strcpy( ( BINRangeShmPtr + i )->BIN, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int BINRangeCount = getEzBINRangeCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzBINRangeTable Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( BINRangeCount > MaxBINRange )
	{
		dptr->trace( "BINRangeCount[%d] > MaxBINRange[%d]", BINRangeCount, MaxBranchProfile );
		return -1;
	}

	if( LoadEzBINRange( BINRangeShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzBINRange......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzInstMgrUtil :: LoadAuthProperty()
{
	AuthPropertyMemoryId = CreateMemoryId( dptr, "AUTHPROPERTYMEMORY" );

	if( AuthPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AUTHPROPERTYMEMORY..." );
		return -1;
	}

	AuthPropertyShmId = shmget ( ( key_t ) AuthPropertyMemoryId, sizeof( struct EzAuthPropertyMemory ) * MaxAuthProperty, IPC_CREAT | 0666 );

	if( AuthPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating AuthProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AuthPropertyShmPtr = ( struct EzAuthPropertyMemory * ) shmat( AuthPropertyShmId, 0, 0 );

	if( AuthPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching AuthProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AuthPropertySemId = semget ( ( key_t ) AuthPropertyMemoryId, MaxAuthProperty, IPC_CREAT | 0666 );

	if( AuthPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating AuthProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "AuthProperty Semaphore Created with SemId[%d]", AuthPropertySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxAuthProperty; i++ )
	{
		if( semctl( AuthPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AuthProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxAuthProperty; i++ )
	{
		memset( ( AuthPropertyShmPtr + i ), 0, sizeof( struct EzAuthPropertyMemory ) );
		strcpy( ( AuthPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int AuthPropertyCount = getEzAuthPropertyCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzAuthProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( AuthPropertyCount > MaxAuthProperty )
	{
		dptr->trace( "AuthPropertyCount[%d] > MaxAuthProperty[%d]", AuthPropertyCount, MaxAuthProperty );
		return -1;
	}

	if( LoadEzAuthProperty( AuthPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzAuthProperty......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzInstMgrUtil :: LoadDeviceTypeMap()
{
	DeviceTypeMapMemoryId = CreateMemoryId( dptr, "DEVICETYPEMAPMEMORY" );

	if( DeviceTypeMapMemoryId < 0 )
	{
		dptr->trace( "Error in Creating DEVICETYPEMAPMEMORY..." );
		return -1;
	}

	DeviceTypeMapShmId = shmget ( ( key_t ) DeviceTypeMapMemoryId, sizeof( struct EzDeviceTypeMapMemory ) * MaxDeviceTypeMap, IPC_CREAT | 0666 );

	if( DeviceTypeMapShmId < 0 )
	{
		dptr->trace( "Error in Creating DeviceTypeMap Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	DeviceTypeMapShmPtr = ( struct EzDeviceTypeMapMemory * ) shmat( DeviceTypeMapShmId, 0, 0 );

	if( DeviceTypeMapShmPtr == NULL )
	{
		dptr->trace( "Error in attaching DeviceTypeMap Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	DeviceTypeMapSemId = semget ( ( key_t ) DeviceTypeMapMemoryId, MaxDeviceTypeMap, IPC_CREAT | 0666 );

	if( DeviceTypeMapSemId < 0 )
	{
		dptr->trace( "Error in Creating DeviceTypeMap Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "DeviceTypeMap Semaphore Created with SemId[%d]", DeviceTypeMapSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxDeviceTypeMap; i++ )
	{
		if( semctl( DeviceTypeMapSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting DeviceTypeMap Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxDeviceTypeMap; i++ )
	{
		memset( ( DeviceTypeMapShmPtr + i ), 0, sizeof( struct EzDeviceTypeMapMemory ) );
		strcpy( ( DeviceTypeMapShmPtr + i )->DeviceGroupId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int DeviceTypeMapCount = getEzDeviceTypeMapCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzDeviceTypeMap Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( DeviceTypeMapCount > MaxDeviceTypeMap )
	{
		dptr->trace( "DeviceTypeMapCount[%d] > MaxDeviceTypeMap[%d]", DeviceTypeMapCount, MaxDeviceTypeMap );
		return -1;
	}

	if( LoadEzDeviceTypeMap( DeviceTypeMapShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzDeviceTypeMap......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzInstMgrUtil :: LoadChannelProperty()
{
	ChannelPropertyMemoryId = CreateMemoryId( dptr, "CHANNELPROPERTYMEMORY" );

	if( ChannelPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating CHANNELPROPERTYMEMORY..." );
		return -1;
	}

	ChannelPropertyShmId = shmget ( ( key_t ) ChannelPropertyMemoryId, sizeof( struct EzChannelPropertyMemory ) * MaxChannelProperty, IPC_CREAT | 0666 );

	if( ChannelPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating ChannelProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ChannelPropertyShmPtr = ( struct EzChannelPropertyMemory * ) shmat( ChannelPropertyShmId, 0, 0 );

	if( ChannelPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching ChannelProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ChannelPropertySemId = semget ( ( key_t ) ChannelPropertyMemoryId, MaxChannelProperty, IPC_CREAT | 0666 );

	if( ChannelPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating ChannelProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "ChannelProperty Semaphore Created with SemId[%d]", ChannelPropertySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxChannelProperty; i++ )
	{
		if( semctl( ChannelPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting ChannelProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxChannelProperty; i++ )
	{
		memset( ( ChannelPropertyShmPtr + i ), 0, sizeof( struct EzChannelPropertyMemory ) );
		strcpy( ( ChannelPropertyShmPtr + i )->ChannelName, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int ChannelPropertyCount = getEzChannelPropertyCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzChannelProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( ChannelPropertyCount > MaxChannelProperty )
	{
		dptr->trace( "ChannelPropertyCount[%d] > MaxChannelProperty[%d]", ChannelPropertyCount, MaxChannelProperty );
		return -1;
	}

	if( LoadEzChannelProperty( ChannelPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzChannelProperty......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzInstMgrUtil :: LoadMsgTypeProperty()
{
	MsgTypePropertyMemoryId = CreateMemoryId( dptr, "MSGTYPEPROPERTYMEMORY" );

	if( MsgTypePropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MSGTYPEPROPERTYMEMORY..." );
		return -1;
	}

	MsgTypePropertyShmId = shmget ( ( key_t ) MsgTypePropertyMemoryId, sizeof( struct EzMsgTypePropertyMemory ) * MaxMsgTypeProperty, IPC_CREAT | 0666 );

	if( MsgTypePropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating MsgTypeProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MsgTypePropertyShmPtr = ( struct EzMsgTypePropertyMemory * ) shmat( MsgTypePropertyShmId, 0, 0 );

	if( MsgTypePropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MsgTypeProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MsgTypePropertySemId = semget ( ( key_t ) MsgTypePropertyMemoryId, MaxMsgTypeProperty, IPC_CREAT | 0666 );

	if( MsgTypePropertySemId < 0 )
	{
		dptr->trace( "Error in Creating MsgTypeProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "MsgTypeProperty Semaphore Created with SemId[%d]", MsgTypePropertySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxMsgTypeProperty; i++ )
	{
		if( semctl( MsgTypePropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting MsgTypeProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxMsgTypeProperty; i++ )
	{
		memset( ( MsgTypePropertyShmPtr + i ), 0, sizeof( struct EzMsgTypePropertyMemory ) );
		( MsgTypePropertyShmPtr + i )->MsgType = RECORD_INIT_NUMBER_VAL;
	}

	int SqlErr=0;
	int MsgTypePropertyCount = getEzMsgTypePropertyCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzMsgTypeProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( MsgTypePropertyCount > MaxMsgTypeProperty )
	{
		dptr->trace( "MsgTypePropertyCount[%d] > MaxMsgTypeProperty[%d]", MsgTypePropertyCount, MaxMsgTypeProperty );
		return -1;
	}

	if( LoadEzMsgTypeProperty( MsgTypePropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzMsgTypeProperty......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

void EzInstMgrUtil :: sortEventProperty()
{
	struct EzEventPropertyMemory eventproperty_rec;
	int min, minpos;
	for( int i = 0; i < MaxEventProperty - 1; i++ )
	{
		min = ( EventPropertyShmPtr + i )->RecordNo;
		minpos = i;
		for( int j = i + 1; j < MaxEventProperty; j++ )
		{
			if( ( EventPropertyShmPtr + j )->RecordNo < min )
			{
				min = ( EventPropertyShmPtr + j )->RecordNo;
				minpos = j;
			}
		}
		memset( &eventproperty_rec, 0, sizeof( struct EzEventPropertyMemory ) );
		memcpy( &eventproperty_rec, EventPropertyShmPtr + minpos, sizeof( struct EzEventPropertyMemory ) );
		memset( EventPropertyShmPtr + minpos, 0, sizeof( struct EzEventPropertyMemory ) );
		memcpy( EventPropertyShmPtr + minpos, EventPropertyShmPtr + i, sizeof( struct EzEventPropertyMemory ) );
		memset( EventPropertyShmPtr + i, 0, sizeof( struct EzEventPropertyMemory ) );
		memcpy( EventPropertyShmPtr + i, &eventproperty_rec, sizeof( struct EzEventPropertyMemory ) );
	}
}

int EzInstMgrUtil :: LoadEventProperty()
{
	EventPropertyMemoryId = CreateMemoryId( dptr, "EVENTPROPERTYMEMORY" );

	if( EventPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating EVENTPROPERTYMEMORY..." );
		return -1;
	}

	EventPropertyShmId = shmget ( ( key_t ) EventPropertyMemoryId, sizeof( struct EzEventPropertyMemory ) * MaxEventProperty, IPC_CREAT | 0666 );

	if( EventPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating EventProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EventPropertyShmPtr = ( struct EzEventPropertyMemory * ) shmat( EventPropertyShmId, 0, 0 );

	if( EventPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EventProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EventPropertySemId = semget ( ( key_t ) EventPropertyMemoryId, MaxEventProperty, IPC_CREAT | 0666 );

	if( EventPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating EventProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "EventProperty Semaphore Created with SemId[%d]", EventPropertySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxEventProperty; i++ )
	{
		if( semctl( EventPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EventProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxEventProperty; i++ )
	{
		memset( ( EventPropertyShmPtr + i ), 0, sizeof( struct EzEventPropertyMemory ) );
		strcpy( ( EventPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL );
		( EventPropertyShmPtr + i )->RecordNo = 999999;
	}

	int SqlErr=0;
	int EventPropertyCount = getEzEventPropertyCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzEventProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( EventPropertyCount > MaxEventProperty )
	{
		dptr->trace( "EventPropertyCount[%d] > MaxEventProperty[%d]", EventPropertyCount, MaxEventProperty );
		return -1;
	}

	if( LoadEzEventProperty( EventPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzEventProperty......OraErr[%05d]", SqlErr );
		return -1;
	}
	sortEventProperty();
	//for( int i = 0; i < MaxEventProperty; i++ )
		//dptr->trace( "EventProperty...RecordNo[%d] RecordId[%s]", ( EventPropertyShmPtr + i )->RecordNo, ( EventPropertyShmPtr + i )->RecordId );
	return 1;
}

void EzInstMgrUtil :: sortInBoundMsgProperty()
{
	struct EzInBoundMsgPropertyMemory inboundmsgproperty_rec;
	int min, minpos;
	for( int i = 0; i < MaxInBoundMsgProperty - 1; i++ )
	{
		min = ( InBoundMsgPropertyShmPtr + i )->RecordNo;
		minpos = i;
		for( int j = i + 1; j < MaxInBoundMsgProperty; j++ )
		{
			if( ( InBoundMsgPropertyShmPtr + j )->RecordNo < min )
			{
				min = ( InBoundMsgPropertyShmPtr + j )->RecordNo;
				minpos = j;
			}
		}
		memset( &inboundmsgproperty_rec, 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		memcpy( &inboundmsgproperty_rec, InBoundMsgPropertyShmPtr + minpos, sizeof( struct EzInBoundMsgPropertyMemory ) );
		memset( InBoundMsgPropertyShmPtr + minpos, 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		memcpy( InBoundMsgPropertyShmPtr + minpos, InBoundMsgPropertyShmPtr + i, sizeof( struct EzInBoundMsgPropertyMemory ) );
		memset( InBoundMsgPropertyShmPtr + i, 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		memcpy( InBoundMsgPropertyShmPtr + i, &inboundmsgproperty_rec, sizeof( struct EzInBoundMsgPropertyMemory ) );
	}
}


int EzInstMgrUtil :: LoadInBoundMsgProperty()
{
	InBoundMsgPropertyMemoryId = CreateMemoryId( dptr, "INBOUNDMSGPROPERTYMEMORY" );

	if( InBoundMsgPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating INBOUNDMSGPROPERTYMEMORY..." );
		return -1;
	}

	InBoundMsgPropertyShmId = shmget ( ( key_t ) InBoundMsgPropertyMemoryId, sizeof( struct EzInBoundMsgPropertyMemory ) * MaxInBoundMsgProperty, IPC_CREAT | 0666 );

	if( InBoundMsgPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating InBoundMsgProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InBoundMsgPropertyShmPtr = ( struct EzInBoundMsgPropertyMemory * ) shmat( InBoundMsgPropertyShmId, 0, 0 );

	if( InBoundMsgPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching InBoundMsgProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InBoundMsgPropertySemId = semget ( ( key_t ) InBoundMsgPropertyMemoryId, MaxInBoundMsgProperty, IPC_CREAT | 0666 );

	if( InBoundMsgPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating InBoundMsgProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "InBoundMsgProperty Semaphore Created with SemId[%d]", InBoundMsgPropertySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxInBoundMsgProperty; i++ )
	{
		if( semctl( InBoundMsgPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting InBoundMsgProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxInBoundMsgProperty; i++ )
	{
		memset( ( InBoundMsgPropertyShmPtr + i ), 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		strcpy( ( InBoundMsgPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL );
		( InBoundMsgPropertyShmPtr + i )->RecordNo = 999999;
	}

	int SqlErr=0;
	int InBoundMsgPropertyCount = getEzInBoundMsgPropertyCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzInBoundMsgProperty Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( InBoundMsgPropertyCount > MaxInBoundMsgProperty )
	{
		dptr->trace( "InBoundMsgPropertyCount[%d] > MaxInBoundMsgProperty[%d]", InBoundMsgPropertyCount, MaxInBoundMsgProperty );
		return -1;
	}

	if( LoadEzInBoundMsgProperty( InBoundMsgPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzInBoundMsgProperty......OraErr[%05d]", SqlErr );
		return -1;
	}

	sortInBoundMsgProperty();

	//for( int i = 0; i < MaxEventProperty; i++ )
		//dptr->trace( "InBoundMsgProperty...RecordNo[%d] RecordId[%s]", ( InBoundMsgPropertyShmPtr + i )->RecordNo, ( InBoundMsgPropertyShmPtr + i )->RecordId );
	return 1;
}

int EzInstMgrUtil :: LoadMsgTranslate()
{
	MsgTranslateMemoryId = CreateMemoryId( dptr, "MSGTRANSLATEMEMORY" );

	if( MsgTranslateMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MSGTRANSLATEMEMORY..." );
		return -1;
	}

	MsgTranslateShmId = shmget ( ( key_t ) MsgTranslateMemoryId, sizeof( struct EzMsgTranslateMemory ) * MaxMsgTranslate, IPC_CREAT | 0666 );

	if( MsgTranslateShmId < 0 )
	{
		dptr->trace( "Error in Creating MsgTranslate Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MsgTranslateShmPtr = ( struct EzMsgTranslateMemory * ) shmat( MsgTranslateShmId, 0, 0 );

	if( MsgTranslateShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MsgTranslate Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MsgTranslateSemId = semget ( ( key_t ) MsgTranslateMemoryId, MaxMsgTranslate, IPC_CREAT | 0666 );

	if( MsgTranslateSemId < 0 )
	{
		dptr->trace( "Error in Creating MsgTranslate Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "MsgTranslate Semaphore Created with SemId[%d]", MsgTranslateSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxMsgTranslate; i++ )
	{
		if( semctl( MsgTranslateSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting MsgTranslate Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxMsgTranslate; i++ )
	{
		memset( ( MsgTranslateShmPtr + i ), 0, sizeof( struct EzMsgTranslateMemory ) );
		strcpy( ( MsgTranslateShmPtr + i )->MsgTranslateId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int MsgTranslateCount = getEzMsgTranslateCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzMsgTranslate Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( MsgTranslateCount > MaxMsgTranslate )
	{
		dptr->trace( "MsgTranslateCount[%d] > MaxMsgTranslate[%d]", MsgTranslateCount, MaxMsgTranslate );
		return -1;
	}

	if( LoadEzMsgTranslate( MsgTranslateShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzMsgTranslate......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

void EzInstMgrUtil :: sortTxnRefSelect()
{
	struct EzTxnRefSelectMemory txnrefselect_rec;
	int min, minpos;
	for( int i = 0; i < MaxTxnRefSelect - 1; i++ )
	{
		min = ( TxnRefSelectShmPtr + i )->RecordNo;
		minpos = i;
		for( int j = i + 1; j < MaxTxnRefSelect; j++ )
		{
			if( ( TxnRefSelectShmPtr + j )->RecordNo < min )
			{
				min = ( TxnRefSelectShmPtr + j )->RecordNo;
				minpos = j;
			}
		}
		memset( &txnrefselect_rec, 0, sizeof( struct EzTxnRefSelectMemory ) );
		memcpy( &txnrefselect_rec, TxnRefSelectShmPtr + minpos, sizeof( struct EzTxnRefSelectMemory ) );
		memset( TxnRefSelectShmPtr + minpos, 0, sizeof( struct EzTxnRefSelectMemory ) );
		memcpy( TxnRefSelectShmPtr + minpos, TxnRefSelectShmPtr + i, sizeof( struct EzTxnRefSelectMemory ) );
		memset( TxnRefSelectShmPtr + i, 0, sizeof( struct EzTxnRefSelectMemory ) );
		memcpy( TxnRefSelectShmPtr + i, &txnrefselect_rec, sizeof( struct EzTxnRefSelectMemory ) );
	}
}

int EzInstMgrUtil :: LoadTxnRefSelect()
{
	TxnRefSelectMemoryId = CreateMemoryId( dptr, "TXNREFSELECTMEMORY" );

	if( TxnRefSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNREFSELECTMEMORY..." );
		return -1;
	}

	TxnRefSelectShmId = shmget ( ( key_t ) TxnRefSelectMemoryId, sizeof( struct EzTxnRefSelectMemory ) * MaxTxnRefSelect, IPC_CREAT | 0666 );

	if( TxnRefSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating TxnRefSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnRefSelectShmPtr = ( struct EzTxnRefSelectMemory * ) shmat( TxnRefSelectShmId, 0, 0 );

	if( TxnRefSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TxnRefSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnRefSelectSemId = semget ( ( key_t ) TxnRefSelectMemoryId, MaxTxnRefSelect, IPC_CREAT | 0666 );

	if( TxnRefSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating TxnRefSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "TxnRefSelect Semaphore Created with SemId[%d]", TxnRefSelectSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxTxnRefSelect; i++ )
	{
		if( semctl( TxnRefSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TxnRefSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTxnRefSelect; i++ )
	{
		memset( ( TxnRefSelectShmPtr + i ), 0, sizeof( struct EzTxnRefSelectMemory ) );
		strcpy( ( TxnRefSelectShmPtr + i )->RecordId, RECORD_INIT_VAL );
		( TxnRefSelectShmPtr + i )->RecordNo = 999999;
	}

	int SqlErr=0;
	int TxnRefSelectCount = getEzTxnRefSelectCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzTxnRefSelect Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TxnRefSelectCount > MaxTxnRefSelect )
	{
		dptr->trace( "TxnRefSelectCount[%d] > MaxTxnRefSelect[%d]", TxnRefSelectCount, MaxTxnRefSelect );
		return -1;
	}

	if( LoadEzTxnRefSelect( TxnRefSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTxnRefSelect......OraErr[%05d]", SqlErr );
		return -1;
	}

	sortTxnRefSelect();

	//for( int i = 0; i < MaxTxnRefSelect; i++ )
		//dptr->trace( "TxnRefSelect...RecordNo[%d] RecordId[%s]", ( TxnRefSelectShmPtr + i )->RecordNo, ( TxnRefSelectShmPtr + i )->RecordId );

	return 1;
}

int EzInstMgrUtil :: LoadTxnRouteSelect()
{
	TxnRouteSelectMemoryId = CreateMemoryId( dptr, "TXNROUTESELECTMEMORY" );

	if( TxnRouteSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNROUTESELECTMEMORY..." );
		return -1;
	}

	TxnRouteSelectShmId = shmget ( ( key_t ) TxnRouteSelectMemoryId, sizeof( struct EzTxnRouteSelectMemory ) * MaxTxnRouteSelect, IPC_CREAT | 0666 );

	if( TxnRouteSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating TxnRouteSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnRouteSelectShmPtr = ( struct EzTxnRouteSelectMemory * ) shmat( TxnRouteSelectShmId, 0, 0 );

	if( TxnRouteSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TxnRouteSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnRouteSelectSemId = semget ( ( key_t ) TxnRouteSelectMemoryId, MaxTxnRouteSelect, IPC_CREAT | 0666 );

	if( TxnRouteSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating TxnRouteSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "TxnRouteSelect Semaphore Created with SemId[%d]", TxnRouteSelectSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxTxnRouteSelect; i++ )
	{
		if( semctl( TxnRouteSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TxnRouteSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTxnRouteSelect; i++ )
	{
		memset( ( TxnRouteSelectShmPtr + i ), 0, sizeof( struct EzTxnRouteSelectMemory ) );
		strcpy( ( TxnRouteSelectShmPtr + i )->RouteSelectId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int TxnRouteSelectCount = getEzTxnRouteSelectCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzTxnRouteSelect Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TxnRouteSelectCount > MaxTxnRouteSelect )
	{
		dptr->trace( "TxnRouteSelectCount[%d] > MaxTxnRouteSelect[%d]", TxnRouteSelectCount, MaxTxnRouteSelect );
		return -1;
	}

	if( LoadEzTxnRouteSelect( TxnRouteSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTxnRouteSelect......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

void EzInstMgrUtil :: sortTxnRouteInfo()
{
	struct EzTxnRouteInfoMemory txnrouteinfo_rec;
	int min, minpos;
	for( int i = 0; i < MaxTxnRouteInfo - 1; i++ )
	{
		min = ( TxnRouteInfoShmPtr + i )->RecordNo;
		minpos = i;
		for( int j = i + 1; j < MaxTxnRouteInfo; j++ )
		{
			if( ( TxnRouteInfoShmPtr + j )->RecordNo < min )
			{
				min = ( TxnRouteInfoShmPtr + j )->RecordNo;
				minpos = j;
			}
		}
		memset( &txnrouteinfo_rec, 0, sizeof( struct EzTxnRouteInfoMemory ) );
		memcpy( &txnrouteinfo_rec, TxnRouteInfoShmPtr + minpos, sizeof( struct EzTxnRouteInfoMemory ) );
		memset( TxnRouteInfoShmPtr + minpos, 0, sizeof( struct EzTxnRouteInfoMemory ) );
		memcpy( TxnRouteInfoShmPtr + minpos, TxnRouteInfoShmPtr + i, sizeof( struct EzTxnRouteInfoMemory ) );
		memset( TxnRouteInfoShmPtr + i, 0, sizeof( struct EzTxnRouteInfoMemory ) );
		memcpy( TxnRouteInfoShmPtr + i, &txnrouteinfo_rec, sizeof( struct EzTxnRouteInfoMemory ) );
	}
}

int EzInstMgrUtil :: LoadTxnRouteInfo()
{
	TxnRouteInfoMemoryId = CreateMemoryId( dptr, "TXNROUTEINFOMEMORY" );

	if( TxnRouteInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNROUTEINFOMEMORY..." );
		return -1;
	}

	TxnRouteInfoShmId = shmget ( ( key_t ) TxnRouteInfoMemoryId, sizeof( struct EzTxnRouteInfoMemory ) * MaxTxnRouteInfo, IPC_CREAT | 0666 );

	if( TxnRouteInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating TxnRouteInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnRouteInfoShmPtr = ( struct EzTxnRouteInfoMemory * ) shmat( TxnRouteInfoShmId, 0, 0 );

	if( TxnRouteInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TxnRouteInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnRouteInfoSemId = semget ( ( key_t ) TxnRouteInfoMemoryId, MaxTxnRouteInfo + 1, IPC_CREAT | 0666 );

	if( TxnRouteInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating TxnRouteInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "TxnRouteInfo Semaphore Created with SemId[%d]", TxnRouteInfoSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i <= MaxTxnRouteInfo; i++ )
	{
		if( semctl( TxnRouteInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TxnRouteInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTxnRouteInfo; i++ )
	{
		memset( ( TxnRouteInfoShmPtr + i ), 0, sizeof( struct EzTxnRouteInfoMemory ) );
		strcpy( ( TxnRouteInfoShmPtr + i )->RecordId, RECORD_INIT_VAL );
		( TxnRouteInfoShmPtr + i )->RecordNo = 999999;
		( TxnRouteInfoShmPtr + i )->DebugFlag = '0';
	}

	int SqlErr=0;
	int TxnRouteInfoCount = getEzTxnRouteInfoCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzTxnRouteInfo Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TxnRouteInfoCount > MaxTxnRouteInfo )
	{
		dptr->trace( "TxnRouteInfoCount[%d] > MaxTxnRouteInfo[%d]", TxnRouteInfoCount, MaxTxnRouteInfo );
		return -1;
	}

	if( LoadEzTxnRouteInfo( TxnRouteInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTxnRouteInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	sortTxnRouteInfo();

	//for( int i = 0; i < MaxTxnRouteInfo; i++ )
		//dptr->trace( "RecordNo[%d] RecordId[%s]", ( TxnRouteInfoShmPtr + i )->RecordNo, ( TxnRouteInfoShmPtr + i )->RecordId );

	return 1;
}

int EzInstMgrUtil :: LoadTxnMsgOrder()
{
	TxnMsgOrderMemoryId = CreateMemoryId( dptr, "TXNMSGORDERMEMORY" );

	if( TxnMsgOrderMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNMSGORDERMEMORY..." );
		return -1;
	}

	TxnMsgOrderShmId = shmget ( ( key_t ) TxnMsgOrderMemoryId, sizeof( struct EzTxnMsgOrderMemory ) * MaxTxnMsgOrder, IPC_CREAT | 0666 );

	if( TxnMsgOrderShmId < 0 )
	{
		dptr->trace( "Error in Creating TxnMsgOrderShared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnMsgOrderShmPtr = ( struct EzTxnMsgOrderMemory * ) shmat( TxnMsgOrderShmId, 0, 0 );

	if( TxnMsgOrderShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TxnMsgOrder Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnMsgOrderSemId = semget ( ( key_t ) TxnMsgOrderMemoryId, MaxTxnMsgOrder, IPC_CREAT | 0666 );

	if( TxnMsgOrderSemId < 0 )
	{
		dptr->trace( "Error in Creating TxnMsgOrder Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "TxnMsgOrder Semaphore Created with SemId[%d]", TxnMsgOrderSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxTxnMsgOrder; i++ )
	{
		if( semctl( TxnMsgOrderSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TxnMsgOrder Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTxnMsgOrder; i++ )
	{
		memset( ( TxnMsgOrderShmPtr + i ), 0, sizeof( struct EzTxnMsgOrderMemory ) );
		strcpy( ( TxnMsgOrderShmPtr + i )->RecordId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int TxnMsgOrderCount = getEzTxnMsgOrderCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzTxnMsgOrder Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TxnMsgOrderCount > MaxTxnMsgOrder )
	{
		dptr->trace( "TxnMsgOrderCount[%d] > MaxTxnMsgOrder[%d]", TxnMsgOrderCount, MaxTxnMsgOrder );
		return -1;
	}

	if( LoadEzTxnMsgOrder( TxnMsgOrderShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTxnMsgOrder......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzInstMgrUtil :: LoadInstExtNtwkProfile()
{
	InstExtNtwkProfileMemoryId = CreateMemoryId( dptr, "INSTEXTNTWKPROFILEMEMORY" );

	if( InstExtNtwkProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating INSTEXTNTWKPROFILEMEMORY..." );
		return -1;
	}

	InstExtNtwkProfileShmId = shmget ( ( key_t ) InstExtNtwkProfileMemoryId, sizeof( struct EzInstExtNtwkProfileMemory ) * MaxInstExtNtwkProfile, IPC_CREAT | 0666 );

	if( InstExtNtwkProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating InstExtNtwkProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstExtNtwkProfileShmPtr = ( struct EzInstExtNtwkProfileMemory * ) shmat( InstExtNtwkProfileShmId, 0, 0 );

	if( InstExtNtwkProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching InstExtNtwkProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	InstExtNtwkProfileSemId = semget ( ( key_t ) InstExtNtwkProfileMemoryId, MaxInstExtNtwkProfile, IPC_CREAT | 0666 );

	if( InstExtNtwkProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating InstExtNtwkProfile Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "InstExtNtwkProfile Semaphore Created with SemId[%d]", InstExtNtwkProfileSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxInstExtNtwkProfile; i++ )
	{
		if( semctl( InstExtNtwkProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting InstExtNtwkProfile Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxInstExtNtwkProfile; i++ )
	{
		memset( ( InstExtNtwkProfileShmPtr + i ), 0, sizeof( struct EzInstExtNtwkProfileMemory ) );
		strcpy( ( InstExtNtwkProfileShmPtr + i )->InstId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int InstExtNtwkProfileCount = getEzInstExtNtwkProfileCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzInstExtNtwkProfile Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( InstExtNtwkProfileCount > MaxInstExtNtwkProfile )
	{
		dptr->trace( "InstExtNtwkProfileCount[%d] > MaxInstExtNtwkProfile[%d]", InstExtNtwkProfileCount, MaxInstExtNtwkProfile );
		return -1;
	}

	if( LoadEzInstExtNtwkProfile( InstExtNtwkProfileShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzInstExtNtwkProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzInstMgrUtil :: LoadExtNtwkProfile()
{
	ExtNtwkProfileMemoryId = CreateMemoryId( dptr, "EXTNTWKPROFILEMEMORY" );

	if( ExtNtwkProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating EXTNTWKPROFILEMEMORY..." );
		return -1;
	}

	ExtNtwkProfileShmId = shmget ( ( key_t ) ExtNtwkProfileMemoryId, sizeof( struct EzExtNtwkProfileMemory ) * MaxExtNtwkProfile, IPC_CREAT | 0666 );

	if( ExtNtwkProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating ExtNtwkProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ExtNtwkProfileShmPtr = ( struct EzExtNtwkProfileMemory * ) shmat( ExtNtwkProfileShmId, 0, 0 );

	if( ExtNtwkProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching ExtNtwkProfile Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ExtNtwkProfileSemId = semget ( ( key_t ) ExtNtwkProfileMemoryId, MaxExtNtwkProfile, IPC_CREAT | 0666 );

	if( ExtNtwkProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating ExtNtwkProfile Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "ExtNtwkProfile Semaphore Created with SemId[%d]", ExtNtwkProfileSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxExtNtwkProfile; i++ )
	{
		if( semctl( ExtNtwkProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting ExtNtwkProfile Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxExtNtwkProfile; i++ )
	{
		memset( ( ExtNtwkProfileShmPtr + i ), 0, sizeof( struct EzExtNtwkProfileMemory ) );
		strcpy( ( ExtNtwkProfileShmPtr + i )->ExtNetworkId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int ExtNtwkProfileCount = getEzExtNtwkProfileCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzExtNtwkProfile Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( ExtNtwkProfileCount > MaxExtNtwkProfile )
	{
		dptr->trace( "ExtNtwkProfileCount[%d] > MaxExtNtwkProfile[%d]", ExtNtwkProfileCount, MaxExtNtwkProfile );
		return -1;
	}

	if( LoadEzExtNtwkProfile( ExtNtwkProfileShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzExtNtwkProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzInstMgrUtil :: LoadTxnMonInfo()
{
	TxnMonInfoMemoryId = CreateMemoryId( dptr, "TXNMONINFOMEMORY" );

	if( TxnMonInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNMONINFOMEMORY..." );
		return -1;
	}

	TxnMonInfoShmId = shmget ( ( key_t ) TxnMonInfoMemoryId, sizeof( struct EzTxnMonInfoMemory ), IPC_CREAT | 0666 );

	if( TxnMonInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating TxnMonInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnMonInfoShmPtr = ( struct EzTxnMonInfoMemory * ) shmat( TxnMonInfoShmId, 0, 0 );

	if( TxnMonInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TxnMonInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( TxnMonInfoShmPtr, 0, sizeof( struct EzTxnMonInfoMemory ) );
	memset( TxnMonInfoShmPtr->TotalHits, 0, sizeof( TxnMonInfoShmPtr->TotalHits ) );
	memset( TxnMonInfoShmPtr->TotalHits, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalAuthReq, 0, sizeof( TxnMonInfoShmPtr->TotalAuthReq ) );
	memset( TxnMonInfoShmPtr->TotalAuthReq, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalAuthResp, 0, sizeof( TxnMonInfoShmPtr->TotalAuthResp ) );
	memset( TxnMonInfoShmPtr->TotalAuthResp, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalTxnReq, 0, sizeof( TxnMonInfoShmPtr->TotalTxnReq ) );
	memset( TxnMonInfoShmPtr->TotalTxnReq, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalTxnResp, 0, sizeof( TxnMonInfoShmPtr->TotalTxnResp ) );
	memset( TxnMonInfoShmPtr->TotalTxnResp, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalOARReq, 0, sizeof( TxnMonInfoShmPtr->TotalOARReq ) );
	memset( TxnMonInfoShmPtr->TotalOARReq, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalOARResp, 0, sizeof( TxnMonInfoShmPtr->TotalOARResp ) );
	memset( TxnMonInfoShmPtr->TotalOARResp, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalRevReq, 0, sizeof( TxnMonInfoShmPtr->TotalRevReq ) );
	memset( TxnMonInfoShmPtr->TotalRevReq, '0', 32 );
	memset( TxnMonInfoShmPtr->TotalRevResp, 0, sizeof( TxnMonInfoShmPtr->TotalRevResp ) );
	memset( TxnMonInfoShmPtr->TotalRevResp, '0', 32 );
	memset( TxnMonInfoShmPtr->PreAuthResp, 0, sizeof( TxnMonInfoShmPtr->PreAuthResp ) );
	memset( TxnMonInfoShmPtr->PreAuthResp, '0', 32 );


	TxnMonInfoSemId = semget ( ( key_t ) TxnMonInfoMemoryId, 1, IPC_CREAT | 0666 );

	if( TxnMonInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating TxnMonInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "TxnMonInfo Semaphore Created with SemId[%d]", TxnMonInfoSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	if( semctl( TxnMonInfoSemId, 0, SETVAL, arg ) < 0 )
	{
		dptr->trace( "Error in Setting TxnMonInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzInstMgrUtil :: LoadSafProperty()
{
	SafPropertyMemoryId = CreateMemoryId( dptr, "SAFPROPERTYMEMORY" );

	if( SafPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating SAFPROPERTYMEMORY..." );
		return -1;
	}

	SafPropertyShmId = shmget ( ( key_t ) SafPropertyMemoryId, sizeof( struct EzSafPropertyMemory ) * MaxSafProperty, IPC_CREAT | 0666 );

	if( SafPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating SafProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SafPropertyShmPtr = ( struct EzSafPropertyMemory * ) shmat( SafPropertyShmId, 0, 0 );

	if( SafPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching SafProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SafPropertySemId = semget ( ( key_t ) SafPropertyMemoryId, MaxSafProperty, IPC_CREAT | 0666 );

	if( SafPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating SafProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "SafProperty Semaphore Created with SemId[%d]", SafPropertySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxSafProperty; i++ )
	{
		if( semctl( SafPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting SafProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxSafProperty; i++ )
	{
		memset( ( SafPropertyShmPtr + i ), 0, sizeof( struct EzSafPropertyMemory ) );
		strcpy( ( SafPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL );
	}

	int SqlErr=0;
	int SafPropertyCount = getEzSafPropertyCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		dptr->trace( "Error in Getting EzSafPropertyMemory Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( SafPropertyCount > MaxSafProperty )
	{
		dptr->trace( "SafPropertyCount[%d] > MaxSafProperty[%d]", SafPropertyCount, MaxSafProperty );
		return -1;
	}

	if( LoadEzSafProperty( SafPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzSafPropertyMemory......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}
