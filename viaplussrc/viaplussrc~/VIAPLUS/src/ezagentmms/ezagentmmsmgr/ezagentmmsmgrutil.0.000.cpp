#include <ezagentmms/ezagentmmsmgrutil.h>

int EzMMSMgrUtil :: initMMSMgrUtil(const char *TaskName, EzDebugUtil *dptr, bool MemoryFlag )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	GlobalMMSTransactionDescCount = 0;
	GlobalMMSTxnCodeDescCount = 0;
	GlobalFITProfileCount = 0;
	GlobalTerminalProfileCount = 0;
	GlobalStoreProfileCount = 0;
	GlobalMerchantProfileCount = 0;
	GlobalMerchantSchemeCount = 0;
	InstOffset = 1;

	this->dptr = dptr;
	this->MemoryFlag = MemoryFlag;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezagentmms.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXMERCHANTSCHEME", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MMSDB#MAXMERCHANTSCHEME from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxMerchantScheme = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXMERCHANTPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MMSDB#MAXMERCHANTPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxMerchantProfile = atoi( cfgval );

	dptr->trace( DEBUG_NORMAL, "MaxMerchantProfile[%d]", MaxMerchantProfile );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXSTOREPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MMSDB#MAXSTOREPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxStoreProfile = atoi( cfgval );

	dptr->trace( DEBUG_NORMAL, "MaxStoreProfile[%d]", MaxStoreProfile );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXTERMINALPROFILE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching MMSDB#MAXTERMINALPROFILE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxTerminalProfile = atoi( cfgval );

	dptr->trace( DEBUG_NORMAL, "MaxTerminalProfile[%d]", MaxTerminalProfile );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXTERMINALS", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching MMSDB#MAXTERMINALS from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxTerminals = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXFIT", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching MMSDB#MAXFIT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxFIT = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXMMSTXNCODEDESC", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching DB#MAXMMSTXNCODEDESC from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MAXMMSTXNCODEDESC = atoi( cfgval );

	dptr->trace( "MAXMMSTXNCODEDESC[%d]", MAXMMSTXNCODEDESC );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "MMSDB#MAXMMSTRANSACTIONDESC", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching DB#MAXMMSTRANSACTIONDESC from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MAXMMSTRANSACTIONDESC = atoi( cfgval );

	dptr->trace( "MAXMMSTRANSACTIONDESC[%d]", MAXMMSTRANSACTIONDESC );

	cfgutil.cfg_close();

	if( LoadMerchantScheme() < 0 )
	{
		dptr->trace( "Error in Loading MerchantScheme Table...." );
		return -1;
	}
	
	if( initEzMMSMgrODBCUtil( TaskName, dptr , "EZAGENTMMS" ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in initEzMMSMgrODBCUtil" );
		cfgutil.cfg_close();
		return -1;
	}

	if( LoadMerchantProfile() < 0 )
	{
		dptr->trace( "Error in Loading MerchantProfile Table...." );
		return -1;
	}

	if( LoadStoreProfile() < 0 )
	{
		dptr->trace( "Error in Loading StoreProfile Table...." );
		return -1;
	}

	if( LoadFITProfile() < 0 )
	{
		dptr->trace( "Error in Loading FIT Profile...." );
		return -1;
	}

	if( LoadTerminalProfile() < 0 )
	{
		dptr->trace( "Error in Loading TerminalProfile Table...." );
		return -1;
	}

	if( LoadMMSTxnCodeDesc() < 0 )
	{
		dptr->trace( "Error in Loading TxnCodeDesc Table...." );
		return -1;
	}

	if( LoadMMSTransactionDesc() < 0 )
	{
		dptr->trace( "Error in Loading TransactionDesc Table...." );
		return -1;
	}
	if( LoadMMSSequenceMemory() < 0 )
	{
		dptr->trace( "Error in Loading MMS Sequence Memory...." );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMerchantScheme()
{
	MerchantSchemeMemoryId = CreateMemoryId( dptr, "AGENTMMS_MERCHANTSCHEME" );

	if( MerchantSchemeMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_MERCHANTSCHEME Memory..." );
		return -1;
	}

	MerchantSchemeShmId = shmget ( ( key_t ) MerchantSchemeMemoryId, sizeof( struct EzMMSMerchantScheme ) * MaxMerchantScheme, IPC_CREAT | 0666 );

	if( MerchantSchemeShmId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_MERCHANTSCHEME Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantSchemeShmPtr = ( struct EzMMSMerchantScheme * ) shmat( MerchantSchemeShmId, 0, 0 );

	if( MerchantSchemeShmPtr == NULL )
	{
		dptr->trace( "Error in attaching AGENTMMS_MERCHANTSCHEME Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantSchemeSemId = semget ( ( key_t ) MerchantSchemeMemoryId, MaxMerchantScheme, IPC_CREAT | 0666 );

	if( MerchantSchemeSemId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_MERCHANTSCHEME Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxMerchantScheme; i++ )
	{
		if( semctl( MerchantSchemeSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AGENTMMS_MERCHANTSCHEME Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxMerchantScheme; i++ )
	{
		memset( ( MerchantSchemeShmPtr + i ), 0, sizeof( struct EzMMSMerchantScheme ) );
		strcpy( ( MerchantSchemeShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( MerchantSchemeShmPtr + i )->BIN, MMS_RECORD_STRINGINIT_VAL );
	}

	if( !MemoryFlag )
	{
		int SqlErr;
		int MerchantSchemeCount = getEzMerchantSchemeCount( &SqlErr );
		if( SqlErr != 0 )
		{
			dptr->trace( "Error in getting EzMerchantScheme Count...SqlErr[%05d]", SqlErr );
			return -1;
		}
		dptr->trace( "MerchantSchemeCount[%d]", MerchantSchemeCount );

		if( MerchantSchemeCount > MaxMerchantScheme )
		{
			dptr->trace( "MerchantSchemeCount[%d] > MaxMerchantScheme[%d]", MerchantSchemeCount, MaxMerchantScheme );
			return -1;
		}

		if( LoadEzMerchantScheme( MerchantSchemeShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading EzMMSMerchantScheme......OraErr[%05d]", SqlErr );
			return -1;
		}
	}
	return 1;
}


int EzMMSMgrUtil :: LoadMerchantProfile()
{
	MerchantProfileMemoryId = CreateMemoryId( dptr, "AGENTMMS_MERCHANTPROFILE" );

	if( MerchantProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_MERCHANTPROFILE Memory..." );
		return -1;
	}

	MerchantProfileShmId = shmget ( ( key_t ) MerchantProfileMemoryId, sizeof( struct EzMMSMerchantProfile ) * MaxMerchantProfile, IPC_CREAT | 0666 );

	if( MerchantProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_MERCHANTPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantProfileShmPtr = ( struct EzMMSMerchantProfile * ) shmat( MerchantProfileShmId, 0, 0 );

	if( MerchantProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching AGENTMMS_MERCHANTPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantProfileSemId = semget ( ( key_t ) MerchantProfileMemoryId, MaxMerchantProfile, IPC_CREAT | 0666 );

	if( MerchantProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_MERCHANTPROFILE Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxMerchantProfile; i++ )
	{
		if( semctl( MerchantProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AGENTMMS_MERCHANTPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxMerchantProfile; i++ )
	{
		memset( ( MerchantProfileShmPtr + i ), 0, sizeof( struct EzMMSMerchantProfile ) );
		strcpy( ( MerchantProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( MerchantProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL );
	}

	if( !MemoryFlag )
	{
		int SqlErr;
		int MerchantProfileCount = getEzMerchantProfileCount( &SqlErr );
		if( SqlErr != 0 )
		{
			dptr->trace( "Error in getting EzMerchantProfile Count...SqlErr[%05d]", SqlErr );
			return -1;
		}
		dptr->trace( "MerchantProfileCount[%d]", MerchantProfileCount );

		if( MerchantProfileCount > MaxMerchantProfile )
		{
			dptr->trace( "MerchantProfileCount[%d] > MaxMerchantProfile[%d]", MerchantProfileCount, MaxMerchantProfile );
			return -1;
		}

		if( LoadEzMerchantProfile( MerchantProfileShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading EzMMSMerchantProfile......OraErr[%05d]", SqlErr );
			return -1;
		}
	}
	return 1;
}

int EzMMSMgrUtil :: LoadStoreProfile()
{
	StoreProfileMemoryId = CreateMemoryId( dptr, "AGENTMMS_STOREPROFILE" );

	if( StoreProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_STOREPROFILE Memory..." );
		return -1;
	}

	StoreProfileShmId = shmget ( ( key_t ) StoreProfileMemoryId, sizeof( struct EzMMSStoreProfile ) * MaxStoreProfile, IPC_CREAT | 0666 );

	if( StoreProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_STOREPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StoreProfileShmPtr = ( struct EzMMSStoreProfile * ) shmat( StoreProfileShmId, 0, 0 );

	if( StoreProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching AGENTMMS_STOREPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StoreProfileSemId = semget ( ( key_t ) StoreProfileMemoryId, MaxStoreProfile, IPC_CREAT | 0666 );

	if( StoreProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_STOREPROFILE Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxStoreProfile; i++ )
	{
		if( semctl( StoreProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AGENTMMS_STOREPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxStoreProfile; i++ )
	{
		memset( ( StoreProfileShmPtr + i ), 0, sizeof( struct EzMMSStoreProfile ) );
		strcpy( ( StoreProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( StoreProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( StoreProfileShmPtr + i )->StoreId, MMS_RECORD_STRINGINIT_VAL );
	}

	if( !MemoryFlag )
	{
		int SqlErr;
		int StoreProfileCount = getEzStoreProfileCount( &SqlErr );
		if( SqlErr != 0 )
		{
			dptr->trace( "Error in getting EzMMSStoreProfile Count...SqlErr[%05d]", SqlErr );
			return -1;
		}
		dptr->trace( "StoreProfileCount[%d]", StoreProfileCount );

		if( StoreProfileCount > MaxStoreProfile )
		{
			dptr->trace( "StoreProfileCount[%d] > MaxStoreProfile[%d]", StoreProfileCount, MaxStoreProfile );
			return -1;
		}

		if( LoadEzStoreProfile( StoreProfileShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading EzStoreProfile......OraErr[%05d]", SqlErr );
			return -1;
		}
	}
	return 1;
}

int EzMMSMgrUtil :: LoadTerminalProfile()
{
	TerminalProfileMemoryId = CreateMemoryId( dptr, "AGENTMMS_TERMINALPROFILE" );

	if( TerminalProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_TERMINALPROFILE Memory..." );
		return -1;
	}

	TerminalProfileShmId = shmget ( ( key_t ) TerminalProfileMemoryId, sizeof( struct EzMMSTerminalProfile ) * MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TerminalProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_TERMINALPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalProfileShmPtr = ( struct EzMMSTerminalProfile * ) shmat( TerminalProfileShmId, 0, 0 );

	if( TerminalProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching AGENTMMS_TERMINALPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalProfileSemId = semget ( ( key_t ) TerminalProfileMemoryId, MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TerminalProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_TERMINALPROFILE Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxTerminalProfile; i++ )
	{
		if( semctl( TerminalProfileSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AGENTMMS_TERMINALPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTerminalProfile; i++ )
	{
		memset( ( TerminalProfileShmPtr + i ), 0, sizeof( struct EzMMSTerminalProfile ) );
		strcpy( ( TerminalProfileShmPtr + i )->MachineId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( TerminalProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( TerminalProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( TerminalProfileShmPtr + i )->TerminalId, MMS_RECORD_STRINGINIT_VAL );
		( TerminalProfileShmPtr + i )->LineNo = 0;
		( TerminalProfileShmPtr + i )->CurrentCommand = TMS_DOWNLOAD_CMD_TERMINALINFO;
        ( TerminalProfileShmPtr + i )->NextCommand = TMS_DOWNLOAD_CMD_MERCHANTINFO;
        memset( ( TerminalProfileShmPtr + i )->TermBatchId, 0, sizeof( ( TerminalProfileShmPtr + i )->TermBatchId ) );
        strcpy( ( TerminalProfileShmPtr + i )->TermBatchId, MMS_RECORD_STRINGINIT_VAL );
    }

	if( !MemoryFlag )
	{
		int SqlErr;
		int TerminalProfileCount = getEzTerminalProfileCount( &SqlErr );
		if( SqlErr != 0 )
		{
			dptr->trace( "Error in getting EzMMSTerminalProfile Count...SqlErr[%05d]", SqlErr );
			return -1;
		}
		dptr->trace( "TerminalProfileCount[%d]", TerminalProfileCount );

		if( TerminalProfileCount > MaxTerminalProfile )
		{
			dptr->trace( "TerminalProfileCount[%d] > MaxTerminalProfile[%d]", TerminalProfileCount, MaxTerminalProfile );
			return -1;
		}

		if( LoadEzTerminalProfile( TerminalProfileShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading EzTerminalProfile......OraErr[%05d]", SqlErr );
			return -1;
		}
	}

	TMSTxnMemoryId = CreateMemoryId( dptr, "AGENTTMSTXNMEMORY" );

	if( TMSTxnMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSTXNMEMORY..." );
		return -1;
	}

	TMSTxnShmId = shmget ( ( key_t ) TMSTxnMemoryId, sizeof( struct EzTMSTxnMemory ) * MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TMSTxnShmId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSTxn Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTxnShmPtr = ( struct EzTMSTxnMemory * ) shmat( TMSTxnShmId, 0, 0 );

	if( TMSTxnShmPtr == NULL )
	{
		dptr->trace( "Error in attaching AGENTTMSTxn Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTxnSemId = semget ( ( key_t ) TMSTxnMemoryId, MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TMSTxnSemId < 0 )
	{
		dptr->trace( "Error in Creating AGENTTMSTxn Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	arg.val = 2;

	for( int i = 0; i < MaxTerminalProfile; i++ )
	{
		if( semctl( TMSTxnSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AGENTTMSTxn Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxTerminalProfile; i++ )
	{
		memset( ( TMSTxnShmPtr + i ), 0, sizeof( struct EzTMSTxnMemory ) );
		strcpy( ( TMSTxnShmPtr + i )->MachineId, ( TerminalProfileShmPtr + i )->MachineId );
		( TMSTxnShmPtr + i )->TxnStatus = TMS_TXN_STATUS_INIT;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadFITProfile()
{
	MMSFITProfileMemoryId = CreateMemoryId( dptr, "AGENTMMS_FITPROFILE" );
    if( MMSFITProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MMS_FITPROFILE Memory[%s]", "AGENTMMS_FITPROFILE" );
		return -1;
	}

	MMSFITProfileShmId = shmget( ( key_t ) MMSFITProfileMemoryId, sizeof( struct EzMMSFITProfile ) * MaxFIT, IPC_CREAT | 0666 );
	if( MMSFITProfileShmId < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating AGENT_MMSFITPROFILE Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSFITProfileShmPtr = ( struct EzMMSFITProfile * ) shmat( MMSFITProfileShmId, 0, 0 );
	if( MMSFITProfileShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching AGENT_MMSFITPROFILE Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSFITProfileSemid = semget( ( key_t ) MMSFITProfileMemoryId, MaxFIT, IPC_CREAT | 0666 );
	if( MMSFITProfileSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating AGENT_MMSFITPROFILE Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
		if( semctl( MMSFITProfileSemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting AGENT_MMSFITPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxFIT; i++ )
	{
		memset( MMSFITProfileShmPtr + i, 0, sizeof( struct EzMMSFITProfile ) );
		strcpy( ( MMSFITProfileShmPtr + i )->RecordId, MMS_RECORD_STRINGINIT_VAL );
	}

	if( !MemoryFlag )
	{
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

		if( LoadMMSFITProfile( MMSFITProfileShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading MMSFITProfile......OraErr[%05d]", SqlErr );
			return -1;
		}

		dptr->trace( "Loaded FIT Profile with Following Entires..." );
		for( int i = 0; i < MaxFIT; i++ )
		{
			if( strcmp( ( MMSFITProfileShmPtr + i )->RecordId, MMS_RECORD_STRINGINIT_VAL ) )
				dptr->trace( "RecordId[%s] InstId[%s] MerchantType[%s] MerchantId[%s] TerminalId[%s] FITRecord[%s] IndirectState[%c] LocalPINVerFlag[%c] LocalFingerPrintFlag[%c] MaxPINLen[%d] MinPINLen[%d]", ( MMSFITProfileShmPtr + i )->RecordId, ( MMSFITProfileShmPtr + i )->InstId, ( MMSFITProfileShmPtr + i )->MerchantType, ( MMSFITProfileShmPtr + i )->MerchantId, ( MMSFITProfileShmPtr + i )->TerminalId, ( MMSFITProfileShmPtr + i )->FITRecord, ( MMSFITProfileShmPtr + i )->IndirectState, ( MMSFITProfileShmPtr + i )->LocalPINVerFlag, ( MMSFITProfileShmPtr + i )->LocalFingerPrintFlag, ( MMSFITProfileShmPtr + i )->MaxPINLen, ( MMSFITProfileShmPtr + i )->MinPINLen );
		}
	}
    return 1;
}

int EzMMSMgrUtil :: LoadMMSTxnCodeDesc()
{
	MMSTxnCodeDescMemoryId = CreateMemoryId( dptr, "AGENTMMS_TXNCODEDESC" );

	if( MMSTxnCodeDescMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMS_TXNCODEDESC Memory..." );
		return -1;
	}

	MMSTxnCodeDescShmId = shmget ( ( key_t ) MMSTxnCodeDescMemoryId, sizeof( struct EzMMSTxnCodeDesc ) * MAXMMSTXNCODEDESC, IPC_CREAT | 0666 );

	if( MMSTxnCodeDescShmId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TXNCODEDESC Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSTxnCodeDescShmPtr = ( struct EzMMSTxnCodeDesc * ) shmat( MMSTxnCodeDescShmId, 0, 0 );

	if( MMSTxnCodeDescShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MMS_TXNCODEDESC Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSTxnCodeDescSemId = semget ( ( key_t ) MMSTxnCodeDescMemoryId, MAXMMSTXNCODEDESC, IPC_CREAT | 0666 );

	if( MMSTxnCodeDescSemId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TXNCODEDESC Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MAXMMSTXNCODEDESC; i++ )
	{
		if( semctl( MMSTxnCodeDescSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting MMS_TXNCODEDESC Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MAXMMSTXNCODEDESC; i++ )
	{
		memset( ( MMSTxnCodeDescShmPtr + i ), 0, sizeof( struct EzMMSTxnCodeDesc ) );
		strcpy( ( MMSTxnCodeDescShmPtr + i )->RecordId, MMS_RECORD_STRINGINIT_VAL );
	}

	if( !MemoryFlag )
	{
		int SqlErr;
		int MMSTxnCodeDescCount = getMMSTxnCodeDescCount( &SqlErr );
		if( SqlErr != 0 )
		{
			dptr->trace( "Error in getting MMSTxnCodeDesc Count...SqlErr[%05d]", SqlErr );
			return -1;
		}
		dptr->trace( "MMSTxnCodeDescCount[%d]", MMSTxnCodeDescCount );

		if( MMSTxnCodeDescCount > MAXMMSTXNCODEDESC )
		{
			dptr->trace( "MMSTxnCodeDescCount[%d] > MAXMMSTXNCODEDESC[%d]", MMSTxnCodeDescCount, MAXMMSTXNCODEDESC );
			return -1;
		}

		if( LoadMMSTxnCodeDescTable( MMSTxnCodeDescShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading MMSTxnCodeDesc......OraErr[%05d]", SqlErr );
			return -1;
		}
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMMSTransactionDesc()
{
	MMSTransactionDescMemoryId = CreateMemoryId( dptr, "AGENTMMS_TRANSACTIONDESC" );

	if( MMSTransactionDescMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TRANSACTIONDESC Memory..." );
		return -1;
	}

	MMSTransactionDescShmId = shmget ( ( key_t ) MMSTransactionDescMemoryId, sizeof( struct EzMMSTransactionDesc ) * MAXMMSTRANSACTIONDESC, IPC_CREAT | 0666 );

	if( MMSTransactionDescShmId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TRANSACTIONDESC Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSTransactionDescShmPtr = ( struct EzMMSTransactionDesc * ) shmat( MMSTransactionDescShmId, 0, 0 );

	if( MMSTransactionDescShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MMS_TRANSACTIONDESC Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSTransactionDescSemId = semget ( ( key_t ) MMSTransactionDescMemoryId, MAXMMSTRANSACTIONDESC, IPC_CREAT | 0666 );

	if( MMSTransactionDescSemId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TRANSACTIONDESC Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MAXMMSTRANSACTIONDESC; i++ )
	{
		if( semctl( MMSTransactionDescSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting MMS_TRANSACTIONDESC Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MAXMMSTRANSACTIONDESC; i++ )
	{
		memset( ( MMSTransactionDescShmPtr + i ), 0, sizeof( struct EzMMSTransactionDesc ) );
		strcpy( ( MMSTransactionDescShmPtr + i )->RecordId, MMS_RECORD_STRINGINIT_VAL );
	}

	if( !MemoryFlag )
	{
		int SqlErr;
		int MMSTransactionDescCount = getMMSTransactionDescCount( &SqlErr );
		if( SqlErr != 0 )
		{
			dptr->trace( "Error in getting MMSTransactionDesc Count...SqlErr[%05d]", SqlErr );
			return -1;
		}
		dptr->trace( "MMSTransactionDescCount[%d]", MMSTransactionDescCount );

		if( MMSTransactionDescCount > MAXMMSTRANSACTIONDESC )
		{
			dptr->trace( "MMSTransactionDescCount[%d] > MAXMMSTRANSACTIONDESC[%d]", MMSTransactionDescCount, MAXMMSTRANSACTIONDESC );
			return -1;
		}

		if( LoadMMSTransactionDescTable( MMSTransactionDescShmPtr, &SqlErr ) < 0 )
		{
			dptr->trace( "Error in Loading MMSTransactionDesc......OraErr[%05d]", SqlErr );
			return -1;
		}
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMMSSequenceMemory()
{
	MMSTxnSeqMemoryId = CreateMemoryId( dptr, "AGENTMMSTXNSEQMEMORY" );

	if( MMSTxnSeqMemoryId < 0 )
	{
		dptr->trace( "Error in Creating AGENTMMSTXNSEQMEMORY..." );
		return -1;
	}

	MMSTxnSeqShmId = shmget ( ( key_t ) MMSTxnSeqMemoryId, sizeof( struct EzMMSTxnSeqMemory ), IPC_CREAT | 0666 );

	if( MMSTxnSeqShmId < 0 )
	{
		dptr->trace( "Error in Creating EzMMSTxnSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSTxnSeqShmPtr = ( struct EzMMSTxnSeqMemory * ) shmat( MMSTxnSeqShmId, 0, 0 );

	if( MMSTxnSeqShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzMMSTxnSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSTxnSeqSemId = semget ( ( key_t ) MMSTxnSeqMemoryId, 1, IPC_CREAT | 0666 );

	if( MMSTxnSeqSemId < 0 )
	{
		dptr->trace( "Error in Creating EzMMSTxnSeq Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	if( semctl( MMSTxnSeqSemId, 0, SETVAL, arg ) < 0 )
	{
		dptr->trace( "Error in Setting MMSTxnSeq Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( LoadMMSTxnMasterSeqNo() < 0 )
		return -1;
	if( LoadMMSTxnLogSeqNo() < 0 )
		return -1;
	if( LoadMMSTxnBatchSeqNo() < 0 )
		return -1;
	if( LoadMMSTxnRefSeqNo() < 0 )
		return -1;
	return 1;
}

int EzMMSMgrUtil :: LoadMMSTxnMasterSeqNo()
{
	int TraceNo;
	FILE *trace_fptr;
	struct sembuf sem_buf;
	char TraceNoPath[ MMS_TRACENO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( TraceNoPath, 0, sizeof( TraceNoPath ) );
	sprintf( TraceNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "MMSTxnMasterSeqNo.dat" );

	trace_fptr = fopen( TraceNoPath, "r" );

	if( trace_fptr == NULL )
	{
		trace_fptr = fopen( TraceNoPath, "w" );
		if( trace_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", TraceNoPath );
			return -1;
		}
		MMSTxnSeqShmPtr->TxnMasterTraceNo = 1;
		fprintf( trace_fptr, "%d", MMSTxnSeqShmPtr->TxnMasterTraceNo );
		fclose( trace_fptr );
	}
	else
	{
		fscanf( trace_fptr, "%d", &MMSTxnSeqShmPtr->TxnMasterTraceNo );
		fclose( trace_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMMSTxnLogSeqNo()
{
	int TraceNo;
	FILE *trace_fptr;
	struct sembuf sem_buf;
	char TraceNoPath[ MMS_TRACENO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( TraceNoPath, 0, sizeof( TraceNoPath ) );
	sprintf( TraceNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "MMSTxnLogSeqNo.dat" );

	trace_fptr = fopen( TraceNoPath, "r" );

	if( trace_fptr == NULL )
	{
		trace_fptr = fopen( TraceNoPath, "w" );
		if( trace_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", TraceNoPath );
			return -1;
		}
		MMSTxnSeqShmPtr->TxnLogTraceNo = 1;
		fprintf( trace_fptr, "%d", MMSTxnSeqShmPtr->TxnLogTraceNo );
		fclose( trace_fptr );
	}
	else
	{
		fscanf( trace_fptr, "%d", &MMSTxnSeqShmPtr->TxnLogTraceNo );
		fclose( trace_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMMSTxnBatchSeqNo()
{
	int TraceNo;
	FILE *trace_fptr;
	struct sembuf sem_buf;
	char TraceNoPath[ MMS_TRACENO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( TraceNoPath, 0, sizeof( TraceNoPath ) );
	sprintf( TraceNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "MMSTxnBatchSeqNo.dat" );

	trace_fptr = fopen( TraceNoPath, "r" );

	if( trace_fptr == NULL )
	{
		trace_fptr = fopen( TraceNoPath, "w" );
		if( trace_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", TraceNoPath );
			return -1;
		}
		MMSTxnSeqShmPtr->TxnBatchTraceNo = 1;
		fprintf( trace_fptr, "%d", MMSTxnSeqShmPtr->TxnBatchTraceNo );
		fclose( trace_fptr );
	}
	else
	{
		fscanf( trace_fptr, "%d", &MMSTxnSeqShmPtr->TxnBatchTraceNo );
		fclose( trace_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMMSTxnRefSeqNo()
{
	int TraceNo;
	FILE *trace_fptr;
	struct sembuf sem_buf;
	char TraceNoPath[ MMS_TRACENO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( TraceNoPath, 0, sizeof( TraceNoPath ) );
	sprintf( TraceNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "MMSTxnRefSeqNo.dat" );

	trace_fptr = fopen( TraceNoPath, "r" );

	if( trace_fptr == NULL )
	{
		trace_fptr = fopen( TraceNoPath, "w" );
		if( trace_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", TraceNoPath );
			return -1;
		}
		MMSTxnSeqShmPtr->TxnRefTraceNo = 1;
		fprintf( trace_fptr, "%d", MMSTxnSeqShmPtr->TxnRefTraceNo );
		fclose( trace_fptr );
	}
	else
	{
		fscanf( trace_fptr, "%d", &MMSTxnSeqShmPtr->TxnRefTraceNo );
		fclose( trace_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( MMSTxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...for MMSTxnSeqSemId SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadInstMerchantScheme()
{
	int SqlErr;
	int MerchantSchemeCount = getEzMerchantSchemeCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzMerchantScheme Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	dptr->trace( "MerchantSchemeCount[%d]", MerchantSchemeCount );

	GlobalMerchantSchemeCount += MerchantSchemeCount;

	if( GlobalMerchantSchemeCount > MaxMerchantScheme )
	{
		dptr->trace( "GlobalMerchantSchemeCount[%d] > MaxMerchantScheme[%d]", GlobalMerchantSchemeCount, MaxMerchantScheme );
		return -1;
	}

	if( LoadEzMerchantScheme( MerchantSchemeShmPtr + ( GlobalMerchantSchemeCount - MerchantSchemeCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzMMSMerchantScheme......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadInstMerchantProfile()
{
	int SqlErr;
	int MerchantProfileCount = getEzMerchantProfileCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzMerchantProfile Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	dptr->trace( "MerchantProfileCount[%d]", MerchantProfileCount );

	GlobalMerchantProfileCount += MerchantProfileCount;

	if( GlobalMerchantProfileCount > MaxMerchantProfile )
	{
		dptr->trace( "GlobalMerchantProfileCount[%d] > MaxMerchantProfile[%d]", GlobalMerchantProfileCount, MaxMerchantProfile );
		return -1;
	}

	if( LoadEzMerchantProfile( MerchantProfileShmPtr + ( GlobalMerchantProfileCount - MerchantProfileCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzMMSMerchantProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadInstStoreProfile()
{
	int SqlErr;
	int StoreProfileCount = getEzStoreProfileCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzMMSStoreProfile Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	dptr->trace( "StoreProfileCount[%d]", StoreProfileCount );

	GlobalStoreProfileCount += StoreProfileCount;

	if( GlobalStoreProfileCount > MaxStoreProfile )
	{
		dptr->trace( "GlobalStoreProfileCount[%d] > MaxStoreProfile[%d]", GlobalStoreProfileCount, MaxStoreProfile );
		return -1;
	}

	if( LoadEzStoreProfile( StoreProfileShmPtr + ( GlobalStoreProfileCount - StoreProfileCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzStoreProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadInstTerminalProfile()
{
	int SqlErr;
	int TerminalProfileCount = getEzTerminalProfileCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzMMSTerminalProfile Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	dptr->trace( "TerminalProfileCount[%d]", TerminalProfileCount );

	GlobalTerminalProfileCount += TerminalProfileCount;

	if( GlobalTerminalProfileCount > MaxTerminalProfile )
	{
		dptr->trace( "GlobalTerminalProfileCount[%d] > MaxTerminalProfile[%d]", GlobalTerminalProfileCount, MaxTerminalProfile );
		return -1;
	}

	if( LoadEzTerminalProfile( TerminalProfileShmPtr + ( GlobalTerminalProfileCount - TerminalProfileCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzTerminalProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadInstFITProfile()
{
	int SqlErr;

	int FITProfileCount = getMMSFITProfileCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting FITProfileCount...SqlErr[%05d]", SqlErr );
		return -1;
	}

	GlobalFITProfileCount += FITProfileCount;

	if( GlobalFITProfileCount > MaxFIT )
	{
		dptr->trace( "GlobalFITProfileCount[%d] > MaxFIT[%d]", GlobalFITProfileCount, MaxFIT );
		return -1;
	}

	if( LoadMMSFITProfile( MMSFITProfileShmPtr + ( GlobalFITProfileCount - FITProfileCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading MMSFITProfile......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}


int EzMMSMgrUtil :: LoadInstMMSTxnCodeDesc()
{
	int SqlErr;
	int MMSTxnCodeDescCount = getMMSTxnCodeDescCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting MMSTxnCodeDesc Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	dptr->trace( "MMSTxnCodeDescCount[%d]", MMSTxnCodeDescCount );

	GlobalMMSTxnCodeDescCount += MMSTxnCodeDescCount;

	if( GlobalMMSTxnCodeDescCount > MAXMMSTXNCODEDESC )
	{
		dptr->trace( "GlobalMMSTxnCodeDescCount[%d] > MAXMMSTXNCODEDESC[%d]", GlobalMMSTxnCodeDescCount, MAXMMSTXNCODEDESC );
		return -1;
	}

	if( LoadMMSTxnCodeDescTable( MMSTxnCodeDescShmPtr + ( GlobalMMSTxnCodeDescCount - MMSTxnCodeDescCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading MMSTxnCodeDesc......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadInstMMSTransactionDesc()
{
	int SqlErr;
	int MMSTransactionDescCount = getMMSTransactionDescCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting MMSTransactionDesc Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	dptr->trace( "MMSTransactionDescCount[%d]", MMSTransactionDescCount );

	GlobalMMSTransactionDescCount += MMSTransactionDescCount;

	if( GlobalMMSTransactionDescCount > MAXMMSTRANSACTIONDESC )
	{
		dptr->trace( "GlobalMMSTransactionDescCount[%d] > MAXMMSTRANSACTIONDESC[%d]", GlobalMMSTransactionDescCount, MAXMMSTRANSACTIONDESC );
		return -1;
	}

	if( LoadMMSTransactionDescTable( MMSTransactionDescShmPtr + ( GlobalMMSTransactionDescCount - MMSTransactionDescCount ), &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading MMSTransactionDesc......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzMMSMgrUtil :: LoadMMSTables()
{
	if( LoadInstMerchantScheme() < 0 )
		return -1;
	if( LoadInstMerchantProfile() < 0 )
		return -1;
	if( LoadInstStoreProfile() < 0 )
		return -1;
	if( LoadInstTerminalProfile() < 0 )
		return -1;
	if( LoadInstFITProfile() < 0 )
		return -1;
	if( LoadInstMMSTxnCodeDesc() < 0 )
		return -1;
	if( LoadInstMMSTransactionDesc() < 0 )
		return -1;
	InstOffset++;
	return 1;
}

