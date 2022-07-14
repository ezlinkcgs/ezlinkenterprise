#include <ezmms/ezmmsmgrutil.h>

int EzMMSMgrUtil :: initMMSMgrUtil( const char *TaskName, EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezmms.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

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
	cfgutil.cfg_close();

	if( initEzMMSMgrODBCUtil( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in initEzMMSMgrODBCUtil" );
		cfgutil.cfg_close();
		return -1;
	}

	return 1;
}

int EzMMSMgrUtil :: LoadMerchantProfile()
{
	MerchantProfileMemoryId = CreateMemoryId( dptr, "MMS_MERCHANTPROFILE" );

	if( MerchantProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MMS_MERCHANTPROFILE Memory..." );
		return -1;
	}

	MerchantProfileShmId = shmget ( ( key_t ) MerchantProfileMemoryId, sizeof( struct EzMMSMerchantProfile ) * MaxMerchantProfile, IPC_CREAT | 0666 );

	if( MerchantProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating MMS_MERCHANTPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantProfileShmPtr = ( struct EzMMSMerchantProfile * ) shmat( MerchantProfileShmId, 0, 0 );

	if( MerchantProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MMS_MERCHANTPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantProfileSemId = semget ( ( key_t ) MerchantProfileMemoryId, MaxMerchantProfile, IPC_CREAT | 0666 );

	if( MerchantProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating MMS_MERCHANTPROFILE Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
			dptr->trace( "Error in Setting MMS_MERCHANTPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxMerchantProfile; i++ )
	{
		memset( ( MerchantProfileShmPtr + i ), 0, sizeof( struct EzMMSMerchantProfile ) );
		strcpy( ( MerchantProfileShmPtr + i )->InstId, MMS_RECORD_STRINGINIT_VAL );
		strcpy( ( MerchantProfileShmPtr + i )->MerchantId, MMS_RECORD_STRINGINIT_VAL );
	}

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
	return 1;
}

int EzMMSMgrUtil :: LoadStoreProfile()
{
	StoreProfileMemoryId = CreateMemoryId( dptr, "MMS_STOREPROFILE" );

	if( StoreProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MMS_STOREPROFILE Memory..." );
		return -1;
	}

	StoreProfileShmId = shmget ( ( key_t ) StoreProfileMemoryId, sizeof( struct EzMMSStoreProfile ) * MaxStoreProfile, IPC_CREAT | 0666 );

	if( StoreProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating MMS_STOREPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StoreProfileShmPtr = ( struct EzMMSStoreProfile * ) shmat( StoreProfileShmId, 0, 0 );

	if( StoreProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MMS_STOREPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StoreProfileSemId = semget ( ( key_t ) StoreProfileMemoryId, MaxStoreProfile, IPC_CREAT | 0666 );

	if( StoreProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating MMS_STOREPROFILE Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
			dptr->trace( "Error in Setting MMS_STOREPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
	return 1;
}

int EzMMSMgrUtil :: LoadTerminalProfile()
{
	TerminalProfileMemoryId = CreateMemoryId( dptr, "MMS_TERMINALPROFILE" );

	if( TerminalProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TERMINALPROFILE Memory..." );
		return -1;
	}

	TerminalProfileShmId = shmget ( ( key_t ) TerminalProfileMemoryId, sizeof( struct EzMMSTerminalProfile ) * MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TerminalProfileShmId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TERMINALPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalProfileShmPtr = ( struct EzMMSTerminalProfile * ) shmat( TerminalProfileShmId, 0, 0 );

	if( TerminalProfileShmPtr == NULL )
	{
		dptr->trace( "Error in attaching MMS_TERMINALPROFILE Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalProfileSemId = semget ( ( key_t ) TerminalProfileMemoryId, MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TerminalProfileSemId < 0 )
	{
		dptr->trace( "Error in Creating MMS_TERMINALPROFILE Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
			dptr->trace( "Error in Setting MMS_TERMINALPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	}

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

	for( int i = 0; i < MaxTerminalProfile; i++ )
	{
		memset( ( TerminalProfileShmPtr + i )->TermBatchId, 0, sizeof( ( TerminalProfileShmPtr + i )->TermBatchId ) );
		strcpy( ( TerminalProfileShmPtr + i )->TermBatchId, MMS_RECORD_STRINGINIT_VAL );
	}

	TMSTxnMemoryId = CreateMemoryId( dptr, "TMSTXNMEMORY" );

	if( TMSTxnMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TMSTXNMEMORY..." );
		return -1;
	}

	TMSTxnShmId = shmget ( ( key_t ) TMSTxnMemoryId, sizeof( struct EzTMSTxnMemory ) * MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TMSTxnShmId < 0 )
	{
		dptr->trace( "Error in Creating TMSTxn Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTxnShmPtr = ( struct EzTMSTxnMemory * ) shmat( TMSTxnShmId, 0, 0 );

	if( TMSTxnShmPtr == NULL )
	{
		dptr->trace( "Error in attaching TMSTxn Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TMSTxnSemId = semget ( ( key_t ) TMSTxnMemoryId, MaxTerminalProfile, IPC_CREAT | 0666 );

	if( TMSTxnSemId < 0 )
	{
		dptr->trace( "Error in Creating TMSTxn Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	arg.val = 2;

	for( int i = 0; i < MaxTerminalProfile; i++ )
	{
		if( semctl( TMSTxnSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting TMSTxn Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
	MMSFITProfileMemoryId = CreateMemoryId( dptr, "MMS_FITPROFILE" );
    if( MMSFITProfileMemoryId < 0 )
	{
		dptr->trace( "Error in Creating MMS_FITPROFILE Memory[%s]", "MMS_FITPROFILE" );
		return -1;
	}

	MMSFITProfileShmId = shmget( ( key_t ) MMSFITProfileMemoryId, sizeof( struct EzMMSFITProfile ) * MaxFIT, IPC_CREAT | 0666 );
	if( MMSFITProfileShmId < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating MMSFITPROFILE Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSFITProfileShmPtr = ( struct EzMMSFITProfile * ) shmat( MMSFITProfileShmId, 0, 0 );
	if( MMSFITProfileShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching MMSFITPROFILE Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MMSFITProfileSemid = semget( ( key_t ) MMSFITProfileMemoryId, MaxFIT, IPC_CREAT | 0666 );
	if( MMSFITProfileSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating MMSFITPROFILE Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
			dptr->trace( "Error in Setting MMSFITPROFILE Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxFIT; i++ )
	{
		memset( MMSFITProfileShmPtr + i, 0, sizeof( struct EzMMSFITProfile ) );
		strcpy( ( MMSFITProfileShmPtr + i )->RecordId, MMS_RECORD_STRINGINIT_VAL );
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
    return 1;
}

