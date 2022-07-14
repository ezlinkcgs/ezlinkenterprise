#include <ezagenttms/ezagenttmsmgrutil.h>

//int EzTMSMgrUtil :: initTMSMgrUtil( EzDebugUtil *dptr )
int EzTMSMgrUtil :: initTMSMgrUtil( const char  *TaskName, EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezagenttms.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}
	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXCHANNELPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXCHANNELPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxTMSChannelProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXROUTEINFO", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXROUTEINFO from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTMSRouteInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXINBOUNDPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXINBOUNDPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxTMSInBoundProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXROUTESELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXROUTESELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTMSRouteSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXMSGTRANSLATE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXMSGTRANSLATE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTMSMsgTranslate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXTXNREFSELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXTXNREFSELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTMSTxnRefSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXTERMINALS", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching TMSDB#MAXTERMINALS from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxTerminals = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXFIT", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching TMSDB#MAXFIT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxFIT = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "TMSDB#MAXTXNREL", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TMSDB#MAXTXNREL from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTMSTxnRel = atoi( cfgval );

	cfgutil.cfg_close();
	
	if ( initEzTMSMgrODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( "Error in initEzTMSMgrODBCUtil" );
		return -1;
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTMSTxnRel()
{
	TMSTxnRelMemoryId = CreateMemoryId( dptr, "AGENTTMSTXNRELMEMORY" );

	if( TMSTxnRelMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSTXNRELMEMORY..." );
		return -1;
	}

	TMSTxnRelShmId = shmget ( ( key_t ) TMSTxnRelMemoryId, sizeof( struct EzTMSTxnRel ) * MaxTMSTxnRel, IPC_CREAT | 0666 );

	if( TMSTxnRelShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSTxnRel Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	TMSTxnRelShmPtr = ( struct EzTMSTxnRel * ) shmat( TMSTxnRelShmId, 0, 0 );

	if( TMSTxnRelShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSTxnRel Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	TMSTxnRelSemId = semget ( ( key_t ) TMSTxnRelMemoryId, MaxTMSTxnRel, IPC_CREAT | 0666 );

	if( TMSTxnRelSemId < 0 )
	{
		dptr->trace( "Error in Creating TMSTxnRel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSTxnRel; i++ )
	{
		if( semctl( TMSTxnRelSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TMSTxnRel Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSTxnRel; i++ )
	{
		memset( ( TMSTxnRelShmPtr + i ), 0, sizeof( struct EzTMSTxnRel ) );
		strcpy( ( TMSTxnRelShmPtr + i )->RecordId, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSTxnRelCount = getEzTMSTxnRelCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSTxnRel Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSTxnRelCount > MaxTMSTxnRel )
	{
		dptr->trace( "TMSTxnRelCount[%d] > MaxPOSTxnRel[%d]",  TMSTxnRelCount, MaxTMSTxnRel );
		return -1;
	}

	if( LoadEzTMSTxnRel( TMSTxnRelShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSTxnRel......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTerminalProfile()
{
	TMSTerminalProfileMemoryId = CreateMemoryId( dptr, "AGENTTMSTERMINALPROFILE" );

	if( TMSTerminalProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TMS Controller Memory[%s]", "AGENTTMSTERMINALPROFILE" );
		return -1;
	}

	TMSTerminalProfileShmId = shmget( ( key_t ) TMSTerminalProfileMemoryId, sizeof( struct EzTMSTerminalProfile ) * MaxTerminals, IPC_CREAT | 0666 );
	if( TMSTerminalProfileShmId < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating TMS TerminalProfile Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTerminalProfileShmPtr = ( struct EzTMSTerminalProfile * ) shmat( TMSTerminalProfileShmId, 0, 0 );
	if( TMSTerminalProfileShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching TMS TerminalProfile Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTerminalProfileSemid = semget( ( key_t ) TMSTerminalProfileMemoryId, MaxTerminals, IPC_CREAT | 0666 );
	if( TMSTerminalProfileSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating TMS TerminalProfile Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTerminals; i++ )
	{
		if( semctl( TMSTerminalProfileSemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TMS TerminalProfile Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTerminals; i++ )
	{
		memset( TMSTerminalProfileShmPtr + i, 0, sizeof( struct EzTMSTerminalProfile ) );
		strcpy( ( TMSTerminalProfileShmPtr + i )->MachineId, TMS_STRINGINIT_VAL );
		( TMSTerminalProfileShmPtr + i )->LineNo = 0;
		( TMSTerminalProfileShmPtr + i )->CurrentCommand = TMS_DOWNLOAD_CMD_TERMINALINFO;
		( TMSTerminalProfileShmPtr + i )->NextCommand = TMS_DOWNLOAD_CMD_MERCHANTINFO;
	}

	int SqlErr;

	int TerminalProfileCount = getTMSTerminalProfileCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting TerminalProfile Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TerminalProfileCount > MaxTerminals )
	{
		dptr->trace( "TerminalProfileCount[%d] > MaxTerminals[%d]", TerminalProfileCount, MaxTerminals );
		return -1;
	}

	if( LoadTMSTerminalProfile( TMSTerminalProfileShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading TerminalProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	
	for( int i = 0; i < MaxTerminals; i++ )
	{
		dptr->trace("Mem KeyIntvl[%d]",( TMSTerminalProfileShmPtr + i )->KeyIntvl );
        	dptr->trace("Mem EchoIntvl[%d]",( TMSTerminalProfileShmPtr + i )->EchoIntvl );
		if( strcmp( ( TMSTerminalProfileShmPtr + i )->MachineId, TMS_STRINGINIT_VAL ) )
		{
			SqlErr = getCurrencyCodeList( TMSTerminalProfileShmPtr + i );
			if( SqlErr != 0 )
			{
				dptr->trace( "Error in Loading CurrencyList for MachineId[%s] OraErr[%05d]", ( TMSTerminalProfileShmPtr + i )->MachineId, SqlErr );
				return -1;
			}
		}
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTMSChannelProperty()
{
	TMSChannelPropertyMemoryId = CreateMemoryId( dptr, "AGENTTMSCHANNELPROPERTYMEMORY" );

	if( TMSChannelPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSCHANNELPROPERTYMEMORY..." );
		return -1;
	}

	TMSChannelPropertyShmId = shmget ( ( key_t ) TMSChannelPropertyMemoryId, sizeof( struct EzTMSChannelProperty ) * MaxTMSChannelProperty, IPC_CREAT | 0666 );

	if( TMSChannelPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSChannelProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSChannelPropertyShmPtr = ( struct EzTMSChannelProperty * ) shmat( TMSChannelPropertyShmId, 0, 0 );

	if( TMSChannelPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSChannelProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSChannelPropertySemId = semget ( ( key_t ) TMSChannelPropertyMemoryId, MaxTMSChannelProperty, IPC_CREAT | 0666 );

	if( TMSChannelPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating TMSChannelProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSChannelProperty; i++ )
	{
		if( semctl( TMSChannelPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzTMSChannelProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSChannelProperty; i++ )
	{
		memset( ( TMSChannelPropertyShmPtr + i ), 0, sizeof( struct EzTMSChannelProperty ) );
		strcpy( ( TMSChannelPropertyShmPtr + i )->ChannelName, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSChannelPropertyCount = getEzTMSChannelPropertyCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSChannelProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSChannelPropertyCount > MaxTMSChannelProperty )
	{
		dptr->trace( "TMSChannelPropertyCount[%d] > MaxTMSChannelProperty[%d]", TMSChannelPropertyCount, MaxTMSChannelProperty );
		return -1;
	}

	if( LoadEzTMSChannelProperty( TMSChannelPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTMSChannelProperty......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTMSInBoundProperty()
{
	TMSInBoundPropertyMemoryId = CreateMemoryId( dptr, "AGENTTMSINBOUNDPROPERTYMEMORY" );

	if( TMSInBoundPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSINBOUNDPROPERTYMEMORY..." );
		return -1;
	}

	TMSInBoundPropertyShmId = shmget ( ( key_t ) TMSInBoundPropertyMemoryId, sizeof( struct EzTMSInBoundProperty ) * MaxTMSInBoundProperty, IPC_CREAT | 0666 );

	if( TMSInBoundPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSInBoundProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSInBoundPropertyShmPtr = ( struct EzTMSInBoundProperty * ) shmat( TMSInBoundPropertyShmId, 0, 0 );

	if( TMSInBoundPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSInBoundProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSInBoundPropertySemId = semget ( ( key_t ) TMSInBoundPropertyMemoryId, MaxTMSInBoundProperty, IPC_CREAT | 0666 );

	if( TMSInBoundPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating TMSInBoundProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSInBoundProperty; i++ )
	{
		if( semctl( TMSInBoundPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzTMSInBoundProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSInBoundProperty; i++ )
	{
		memset( ( TMSInBoundPropertyShmPtr + i ), 0, sizeof( struct EzTMSInBoundProperty ) );
		strcpy( ( TMSInBoundPropertyShmPtr + i )->RecordId, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSInBoundPropertyCount = getEzTMSInBoundPropertyCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSInBoundProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSInBoundPropertyCount > MaxTMSInBoundProperty )
	{
		dptr->trace( "TMSInBoundPropertyCount[%d] > MaxTMSInBoundProperty[%d]", TMSInBoundPropertyCount, MaxTMSInBoundProperty );
		return -1;
	}

	if( LoadEzTMSInBoundProperty( TMSInBoundPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTMSInBoundProperty......OraErr[%05d]", SqlErr );
		return -1;
	}

	for( int i = 0; i < TMSInBoundPropertyCount; i++ )
	{
		dptr->trace( "RecordId[%s] MsgType[%s] TxnCode[%s]", ( TMSInBoundPropertyShmPtr + i )->RecordId, ( TMSInBoundPropertyShmPtr + i )->MsgType, ( TMSInBoundPropertyShmPtr + i )->TxnCode );	
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTMSRouteInfo()
{
	TMSRouteInfoMemoryId = CreateMemoryId( dptr, "AGENTTMSROUTEINFOMEMORY" );

	if( TMSRouteInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSROUTEINFOMEMORY..." );
		return -1;
	}

	TMSRouteInfoShmId = shmget ( ( key_t ) TMSRouteInfoMemoryId, sizeof( struct EzTMSRouteInfo ) * MaxTMSRouteInfo, IPC_CREAT | 0666 );

	if( TMSRouteInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSRouteInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSRouteInfoShmPtr = ( struct EzTMSRouteInfo * ) shmat( TMSRouteInfoShmId, 0, 0 );

	if( TMSRouteInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSRouteInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSRouteInfoSemId = semget ( ( key_t ) TMSRouteInfoMemoryId, MaxTMSRouteInfo, IPC_CREAT | 0666 );

	if( TMSRouteInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating TMSRouteInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSRouteInfo; i++ )
	{
		if( semctl( TMSRouteInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzTMSRouteInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSRouteInfo; i++ )
	{
		memset( ( TMSRouteInfoShmPtr + i ), 0, sizeof( struct EzTMSRouteInfo ) );
		strcpy( ( TMSRouteInfoShmPtr + i )->RecordId, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSRouteInfoCount = getEzTMSRouteInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSRouteInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSRouteInfoCount > MaxTMSRouteInfo )
	{
		dptr->trace( "TMSRouteInfoCount[%d] > MaxTMSRouteInfo[%d]", TMSRouteInfoCount, MaxTMSRouteInfo );
		return -1;
	}

	if( LoadEzTMSRouteInfo( TMSRouteInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTMSRouteInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzTMSMgrUtil :: LoadTMSRouteSelect()
{
	TMSRouteSelectMemoryId = CreateMemoryId( dptr, "AGENTTMSROUTESELECTMEMORY" );

	if( TMSRouteSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSROUTESELECTMEMORY..." );
		return -1;
	}

	TMSRouteSelectShmId = shmget ( ( key_t ) TMSRouteSelectMemoryId, sizeof( struct EzTMSRouteSelect ) * MaxTMSRouteSelect, IPC_CREAT | 0666 );

	if( TMSRouteSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSRouteSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSRouteSelectShmPtr = ( struct EzTMSRouteSelect * ) shmat( TMSRouteSelectShmId, 0, 0 );

	if( TMSRouteSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSRouteSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSRouteSelectSemId = semget ( ( key_t ) TMSRouteSelectMemoryId, MaxTMSRouteSelect, IPC_CREAT | 0666 );

	if( TMSRouteSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating TMSRouteSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSRouteSelect; i++ )
	{
		if( semctl( TMSRouteSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzTMSRouteSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSRouteSelect; i++ )
	{
		memset( ( TMSRouteSelectShmPtr + i ), 0, sizeof( struct EzTMSRouteSelect ) );
		strcpy( ( TMSRouteSelectShmPtr + i )->RouteSelectId, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSRouteSelectCount = getEzTMSRouteSelectCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSRouteSelect Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSRouteSelectCount > MaxTMSRouteSelect )
	{
		dptr->trace( "TMSRouteSelectCount[%d] > MaxTMSRouteSelect[%d]", TMSRouteSelectCount, MaxTMSRouteSelect );
		return -1;
	}

	if( LoadEzTMSRouteSelect( TMSRouteSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTMSRouteSelect......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTMSMsgTranslate()
{
	TMSMsgTranslateMemoryId = CreateMemoryId( dptr, "AGENTTMSMSGTRANSLATEMEMORY" );

	if( TMSMsgTranslateMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSMSGTRANSLATEMEMORY..." );
		return -1;
	}

	TMSMsgTranslateShmId = shmget ( ( key_t ) TMSMsgTranslateMemoryId, sizeof( struct EzTMSMsgTranslate ) * MaxTMSMsgTranslate, IPC_CREAT | 0666 );

	if( TMSMsgTranslateShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSMsgTranslate Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSMsgTranslateShmPtr = ( struct EzTMSMsgTranslate * ) shmat( TMSMsgTranslateShmId, 0, 0 );

	if( TMSMsgTranslateShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSMsgTranslate Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSMsgTranslateSemId = semget ( ( key_t ) TMSMsgTranslateMemoryId, MaxTMSMsgTranslate, IPC_CREAT | 0666 );

	if( TMSMsgTranslateSemId < 0 )
	{
		dptr->trace( "Error in Creating TMSMsgTranslate Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSMsgTranslate; i++ )
	{
		if( semctl( TMSMsgTranslateSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzTMSMsgTranslate Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSMsgTranslate; i++ )
	{
		memset( ( TMSMsgTranslateShmPtr + i ), 0, sizeof( struct EzTMSMsgTranslate ) );
		strcpy( ( TMSMsgTranslateShmPtr + i )->MsgTranslateId, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSMsgTranslateCount = getEzTMSMsgTranslateCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSMsgTranslate Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSMsgTranslateCount > MaxTMSMsgTranslate )
	{
		dptr->trace( "TMSMsgTranslateCount[%d] > MaxTMSMsgTranslate[%d]", TMSMsgTranslateCount, MaxTMSMsgTranslate );
		return -1;
	}

	if( LoadEzTMSMsgTranslate( TMSMsgTranslateShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTMSMsgTranslate......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzTMSMgrUtil :: LoadTMSTxnRefSelect()
{
	TMSTxnRefSelectMemoryId = CreateMemoryId( dptr, "AGENTTMSTXNREFSELECTMEMORY" );

	if( TMSTxnRefSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSTXNREFSELECTMEMORY..." );
		return -1;
	}

	TMSTxnRefSelectShmId = shmget ( ( key_t ) TMSTxnRefSelectMemoryId, sizeof( struct EzTMSTxnRefSelect ) * MaxTMSTxnRefSelect, IPC_CREAT | 0666 );

	if( TMSTxnRefSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSTxnRefSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTxnRefSelectShmPtr = ( struct EzTMSTxnRefSelect * ) shmat( TMSTxnRefSelectShmId, 0, 0 );

	if( TMSTxnRefSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSTxnRefSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTxnRefSelectSemId = semget ( ( key_t ) TMSTxnRefSelectMemoryId, MaxTMSTxnRefSelect, IPC_CREAT | 0666 );

	if( TMSTxnRefSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating TMSTxnRefSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTMSTxnRefSelect; i++ )
	{
		if( semctl( TMSTxnRefSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzTMSTxnRefSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTMSTxnRefSelect; i++ )
	{
		memset( ( TMSTxnRefSelectShmPtr + i ), 0, sizeof( struct EzTMSTxnRefSelect ) );
		strcpy( ( TMSTxnRefSelectShmPtr + i )->RecordId, TMS_STRINGINIT_VAL );
	}

	int SqlErr;
	int TMSTxnRefSelectCount = getEzTMSTxnRefSelectCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzTMSTxnRefSelect Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( TMSTxnRefSelectCount > MaxTMSTxnRefSelect )
	{
		dptr->trace( "TMSTxnRefSelectCount[%d] > MaxTMSTxnRefSelect[%d]", TMSTxnRefSelectCount, MaxTMSTxnRefSelect );
		return -1;
	}

	if( LoadEzTMSTxnRefSelect( TMSTxnRefSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTMSTxnRefSelect......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}
/*int EzTMSMgrUtil :: LoadFITProfile()
{
        TMSFITProfileMemoryId = CreateMemoryId( dptr, "AGENTTMSFITPROFILE" );

        if( TMSFITProfileMemoryId < 0 )
        {
                dptr->trace( "Error in Creating AGENTTMSFITPROFILE Memory[%s]", "AGENTTMSFITPROFILE" );
                return -1;
        }

        TMSFITProfileShmId = shmget( ( key_t ) TMSFITProfileMemoryId, sizeof( struct EzTMSFITProfile ) * MaxFIT, IPC_CREAT | 0666 );
        if( TMSFITProfileShmId < 0 )
        {
                dptr->trace( DEBUG_ERROR,"Error in Creating TMSFITPROFILE Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
                return -1;
        }

        TMSFITProfileShmPtr = ( struct EzTMSFITProfile * ) shmat( TMSFITProfileShmId, 0, 0 );
        if( TMSFITProfileShmPtr == NULL )
        {
                dptr->trace( DEBUG_ERROR,"Error in attaching TMSFITPROFILE Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
                return -1;
        }

        TMSFITProfileSemid = semget( ( key_t ) TMSFITProfileMemoryId, MaxFIT, IPC_CREAT | 0666 );
        if( TMSFITProfileSemid < 0 )
        {
                dptr->trace( DEBUG_ERROR,"Error in Creating TMSFITPROFILE Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

        for( int i = 0; i < MaxFIT; i++ )
        {
                if( semctl( TMSFITProfileSemid, i, SETVAL, arg ) < 0 )
                {
                        dptr->trace( "Error in Setting TMSFITPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
                        return -1;
                }
        }

        for( int i = 0; i < MaxFIT; i++ )
        {
                memset( TMSFITProfileShmPtr + i, 0, sizeof( struct EzTMSFITProfile ) );
                strcpy( ( TMSFITProfileShmPtr + i )->RecordId, TMS_STRINGINIT_VAL );
        }

        int SqlErr;

        int FITProfileCount = getMMSFITProfileCount( &SqlErr );
        if( SqlErr != 0 )
        {
                dptr->trace( "Error in getting FITProfileCount...SqlErr[%05d]", SqlErr );
                return -1;
        }

        if( FITProfileCount > MaxFIT )
        {
                dptr->trace( "TerminalProfileCount[%d] > MaxFIT[%d]", FITProfileCount, MaxFIT );
                return -1;
        }

        if( LoadTMSFITProfile( TMSFITProfileShmPtr, &SqlErr ) < 0 )
        {
                dptr->trace( "Error in Loading TMSFITProfile......OraErr[%05d]", SqlErr );
                return -1;
        }
        return 1;
}
*/
