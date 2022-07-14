#include <ezbusiness/ezposmgrutil.h>

int EzPOSMgrUtil :: InitPOSMgrUtil( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	this->dptr = dptr;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezpos.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSMERCHANT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSMERCHANT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSMerchantInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSTERMINAL", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSTERMINAL from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSTerminalInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSMCC", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSMCC from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSMCCInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSMERCHANTTYPE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSMERCHANTTYPE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSMerchantTypeInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSTERMINALTYPE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSTERMINALTYPE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSTerminalTypeInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSSTORE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSSTORE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSStoreInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSTXNINFO", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSTXNINFO from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSTxnInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSRESPCODEINFO", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSRESPCODEINFO from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSRespCodeInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSINBOUNDPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSINBOUNDPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSInBoundProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSROUTEINFO", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSROUTEINFO from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSRouteInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSROUTESELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSROUTESELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSRouteSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSMSGTRANSLATE", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSMSGTRANSLATE from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSMsgTranslate = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSCHANNELPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSCHANNELPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSChannelProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSTXNREFSELECT", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSTXNREFSELECT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSTxnRefSelect = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "POSDB#MAXPOSTXNREL", cfgval, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching POSDB#MAXPOSTXNREL from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxPOSTxnRel = atoi( cfgval );

	dptr->trace( DEBUG_NORMAL, "MaxPOSMerchantInfo[%d] MaxPOSTerminalInfo[%d] MaxPOSMCCInfo[%d] MaxPOSMerchantTypeInfo[%d] MaxPOSTerminalTypeInfo[%d] MaxPOSStoreInfo[%d] MaxPOSTxnInfo[%d] MaxPOSRespCodeInfo[%d] MaxPOSInBoundProperty[%d] MaxPOSRouteInfo[%d] MaxPOSRouteSelect[%d] MaxPOSMsgTranslate[%d] MaxPOSChannelProperty[%d] MaxPOSTxnRefSelect[%d] MaxPOSTxnRel[%d]", MaxPOSMerchantInfo, MaxPOSTerminalInfo,MaxPOSMCCInfo, MaxPOSMerchantTypeInfo, MaxPOSTerminalTypeInfo, MaxPOSStoreInfo, MaxPOSTxnInfo, MaxPOSRespCodeInfo, MaxPOSInBoundProperty, MaxPOSRouteInfo, MaxPOSRouteSelect, MaxPOSMsgTranslate, MaxPOSChannelProperty, MaxPOSTxnRefSelect, MaxPOSTxnRel );

	cfgutil.cfg_close();

	return 1;
}

int EzPOSMgrUtil :: LoadPOSMCCInfo()
{
	MCCInfoMemoryId = CreateMemoryId( dptr, "POSMCCINFOMEMORY" );

	if( MCCInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSMCCINFOMEMORY..." );
		return -1;
	}

	MCCInfoShmId = shmget ( ( key_t ) MCCInfoMemoryId, sizeof( struct EzPOSMCCInfo ) * MaxPOSMCCInfo, IPC_CREAT | 0666 );

	if( MCCInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSMCCINFO Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MCCInfoShmPtr = ( struct EzPOSMCCInfo * ) shmat( MCCInfoShmId, 0, 0 );

	if( MCCInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSMCCINFO Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MCCInfoSemId = semget ( ( key_t ) MCCInfoMemoryId, MaxPOSMCCInfo, IPC_CREAT | 0666 );

	if( MCCInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSMCCINFO Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSMCCInfo; i++ )
	{
		if( semctl( MCCInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting EzPOSMCCInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSMCCInfo; i++ )
	{
		memset( ( MCCInfoShmPtr + i ), 0, sizeof( struct EzPOSMCCInfo ) );
		( MCCInfoShmPtr + i )->MCC = RECORD_NUMBERINIT_VAL ;
	}

	int SqlErr;
	int MCCInfoCount = getEzPOSMCCInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSMCCInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( MCCInfoCount > MaxPOSMCCInfo )
	{
		dptr->trace( "MCCInfoCount[%d] > MaxPOSMCCInfo[%d]", MCCInfoCount, MaxPOSMCCInfo );
		return -1;
	}

	if( LoadEzPOSMCCInfo( MCCInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSMCCInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzPOSMgrUtil :: LoadPOSMerchantTypeInfo()
{
	MerchantTypeInfoMemoryId = CreateMemoryId( dptr, "POSMERCHANTTYPEINFOMEMORY" );

	if( MerchantTypeInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSMERCHANTTYPEINFOMEMORY..." );
		return -1;
	}

	MerchantTypeInfoShmId = shmget ( ( key_t ) MerchantTypeInfoMemoryId, sizeof( struct EzPOSMerchantTypeInfo ) * MaxPOSMerchantTypeInfo, IPC_CREAT | 0666 );

	if( MerchantTypeInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSMerchantTypeInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantTypeInfoShmPtr = ( struct EzPOSMerchantTypeInfo * ) shmat( MerchantTypeInfoShmId, 0, 0 );

	if( MerchantTypeInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSMerchantTypeInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantTypeInfoSemId = semget ( ( key_t ) MerchantTypeInfoMemoryId, MaxPOSMCCInfo, IPC_CREAT | 0666 );

	if( MerchantTypeInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSMerchantTypeInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSMerchantTypeInfo; i++ )
	{
		if( semctl( MerchantTypeInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSMerchantTypeInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSMerchantTypeInfo; i++ )
	{
		memset( ( MerchantTypeInfoShmPtr + i ), 0, sizeof( struct EzPOSMerchantTypeInfo ) );
		strcpy( ( MerchantTypeInfoShmPtr + i )->MerchantType, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;

	int PosMerchantTypeCount = getEzPOSMerchantTypeInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSMerchantTypeInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( PosMerchantTypeCount > MaxPOSMerchantTypeInfo )
	{
		dptr->trace( "PosMerchantTypeCount[%d] > MaxPOSMerchantType[%d]", PosMerchantTypeCount, MaxPOSMerchantTypeInfo );
		return -1;
	}

	if( LoadEzPOSMerchantTypeInfo( MerchantTypeInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSMerchantTypeInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzPOSMgrUtil :: LoadPOSMerchantInfo()
{
	MerchantInfoMemoryId = CreateMemoryId( dptr, "POSMERCHANTINFOMEMORY" );

	if( MerchantInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSMERCHANTINFOMEMORY..." );
		return -1;
	}

	MerchantInfoShmId = shmget ( ( key_t ) MerchantInfoMemoryId, sizeof( struct EzPOSMerchantInfo ) * MaxPOSMerchantInfo, IPC_CREAT | 0666 );

	if( MerchantInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSMerchantInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantInfoShmPtr = ( struct EzPOSMerchantInfo * ) shmat( MerchantInfoShmId, 0, 0 );

	if( MerchantInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSMerchantInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MerchantInfoSemId = semget ( ( key_t ) MerchantInfoMemoryId, MaxPOSMerchantInfo, IPC_CREAT | 0666 );

	if( MerchantInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSMerchantInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSMerchantInfo; i++ )
	{
		if( semctl( MerchantInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSMerchantInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSMerchantInfo; i++ )
	{
		memset( ( MerchantInfoShmPtr + i ), 0, sizeof( struct EzPOSMerchantInfo ) );
		strcpy( ( MerchantInfoShmPtr + i )->MerchantId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int MerchantInfoCount = getEzPOSMerchantInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSMerchantInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( MerchantInfoCount > MaxPOSMerchantInfo )
	{
		dptr->trace( "MerchantInfoCount[%d] > MaxPOSMerchantInfo[%d]", MerchantInfoCount, MaxPOSMerchantInfo );
		return -1;
	}

	if( LoadEzPOSMerchantInfo( MerchantInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSMerchantInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzPOSMgrUtil :: LoadPOSTerminalTypeInfo()
{
	TerminalTypeInfoMemoryId = CreateMemoryId( dptr, "POSTERMINALTYPEINFOMEMORY" );

	if( TerminalTypeInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSTERMINALTYPEINFOMEMORY..." );
		return -1;
	}

	TerminalTypeInfoShmId = shmget ( ( key_t ) TerminalTypeInfoMemoryId, sizeof( struct EzPOSTerminalTypeInfo ) * MaxPOSTerminalTypeInfo, IPC_CREAT | 0666 );

	if( TerminalTypeInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSTerminalTypeInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalTypeInfoShmPtr = ( struct EzPOSTerminalTypeInfo * ) shmat( TerminalTypeInfoShmId, 0, 0 );

	if( TerminalTypeInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSTerminalTypeInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalTypeInfoSemId = semget ( ( key_t ) TerminalTypeInfoMemoryId, MaxPOSTerminalTypeInfo, IPC_CREAT | 0666 );

	if( TerminalTypeInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSTerminalTypeInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSTerminalTypeInfo; i++ )
	{
		if( semctl( TerminalTypeInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSTerminalTypeInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSTerminalTypeInfo; i++ )
	{
		memset( ( TerminalTypeInfoShmPtr + i ), 0, sizeof( struct EzPOSTerminalTypeInfo ) );
		strcpy( ( TerminalTypeInfoShmPtr + i )->TerminalType, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int TerminalTypeInfoCount = getEzPOSTerminalTypeInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSTerminalTypeInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( TerminalTypeInfoCount > MaxPOSTerminalTypeInfo )
	{
		dptr->trace( "TerminalTypeInfoCount[%d] > MaxPOSTerminalType[%d]", TerminalTypeInfoCount, MaxPOSTerminalTypeInfo );
		return -1;
	}

	if( LoadEzPOSTerminalTypeInfo( TerminalTypeInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSTerminalType......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzPOSMgrUtil :: LoadPOSTerminalInfo()
{
	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;

	TerminalInfoMemoryId = CreateMemoryId( dptr, "POSTERMINALINFOMEMORY" );

	if( TerminalInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSTERMINALINFOMEMORY..." );
		return -1;
	}

	TerminalInfoShmId = shmget ( ( key_t ) TerminalInfoMemoryId, sizeof( struct EzPOSTerminalInfo ) * MaxPOSTerminalInfo, IPC_CREAT | 0666 );

	if( TerminalInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSTerminalInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalInfoShmPtr = ( struct EzPOSTerminalInfo * ) shmat( TerminalInfoShmId, 0, 0 );

	if( TerminalInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSTerminalInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TerminalInfoSemId = semget ( ( key_t ) TerminalInfoMemoryId, MaxPOSTerminalInfo, IPC_CREAT | 0666 );

	if( TerminalInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSTerminalInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	arg.val = 2;

	for( int i = 0; i < MaxPOSTerminalInfo; i++ )
	{
		if( semctl( TerminalInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSTerminalInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSTerminalInfo; i++ )
	{
		memset( ( TerminalInfoShmPtr + i ), 0, sizeof( struct EzPOSTerminalInfo ) );
		strcpy( ( TerminalInfoShmPtr + i )->POSId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int TerminalInfoCount = getEzPOSTerminalInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSTerminalInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( TerminalInfoCount > MaxPOSTerminalInfo )
	{
		dptr->trace( "TerminalInfoCount[%d] > MaxPOSTerminalInfo[%d]", TerminalInfoCount, MaxPOSTerminalInfo );
		return -1;
	}

	if( LoadEzPOSTerminalInfo( TerminalInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSTerminalInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	POSTxnMemoryId = CreateMemoryId( dptr, "POSTXNMEMORY" );

	if( POSTxnMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSTXNMEMORY..." );
		return -1;
	}

	POSTxnShmId = shmget ( ( key_t ) POSTxnMemoryId, sizeof( struct EzPOSTxnMemory ) * MaxPOSTerminalInfo, IPC_CREAT | 0666 );

	if( POSTxnShmId < 0 )
	{
		dptr->trace( "Error in Creating POSTxn Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSTxnShmPtr = ( struct EzPOSTxnMemory * ) shmat( POSTxnShmId, 0, 0 );

	if( POSTxnShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSTxn Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSTxnSemId = semget ( ( key_t ) POSTxnMemoryId, MaxPOSTerminalInfo, IPC_CREAT | 0666 );

	if( POSTxnSemId < 0 )
	{
		dptr->trace( "Error in Creating POSTxn Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}


	arg.val = 2;

	for( int i = 0; i < MaxPOSTerminalInfo; i++ )
	{
		if( semctl( POSTxnSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSTxn Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSTerminalInfo; i++ )
	{
		memset( ( POSTxnShmPtr + i ), 0, sizeof( struct EzPOSTxnMemory ) );
		strcpy( ( POSTxnShmPtr + i )->POSId, ( TerminalInfoShmPtr + i )->POSId );
		( POSTxnShmPtr + i )->TxnStatus = POS_TXN_STATUS_INIT;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSStoreInfo()
{
	StoreInfoMemoryId = CreateMemoryId( dptr, "POSSTOREINFOMEMORY" );

	if( StoreInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSSTOREINFOMEMORY..." );
		return -1;
	}

	StoreInfoShmId = shmget ( ( key_t ) StoreInfoMemoryId, sizeof( struct EzPOSStoreInfo ) * MaxPOSStoreInfo, IPC_CREAT | 0666 );

	if( StoreInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSStoreInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StoreInfoShmPtr = ( struct EzPOSStoreInfo * ) shmat( StoreInfoShmId, 0, 0 );

	if( StoreInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSStoreInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StoreInfoSemId = semget ( ( key_t ) StoreInfoMemoryId, MaxPOSStoreInfo, IPC_CREAT | 0666 );

	if( StoreInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSStoreInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSStoreInfo; i++ )
	{
		if( semctl( StoreInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSStoreInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSStoreInfo; i++ )
	{
		memset( ( StoreInfoShmPtr + i ), 0, sizeof( struct EzPOSStoreInfo ) );
		strcpy( ( StoreInfoShmPtr + i )->StoreId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int StoreInfoCount = getEzPOSStoreInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSStoreInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( StoreInfoCount > MaxPOSStoreInfo )
	{
		dptr->trace( "StoreInfoCount[%d] > MaxPOSStoreInfo[%d]", StoreInfoCount, MaxPOSStoreInfo );
		return -1;
	}

	if( LoadEzPOSStoreInfo( StoreInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSStoreInfo......OraErr[%05d]", SqlErr );
		return -1;
	}

	return 1;
}

int EzPOSMgrUtil :: LoadPOSTxnInfo()
{
	TxnInfoMemoryId = CreateMemoryId( dptr, "POSTXNINFOMEMORY" );

	if( TxnInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSTXNINFOMEMORY..." );
		return -1;
	}

	TxnInfoShmId = shmget ( ( key_t ) TxnInfoMemoryId, sizeof( struct EzPOSTxnInfo ) * MaxPOSTxnInfo, IPC_CREAT | 0666 );

	if( TxnInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSTxnInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnInfoShmPtr = ( struct EzPOSTxnInfo * ) shmat( TxnInfoShmId, 0, 0 );

	if( TxnInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSTxnInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnInfoSemId = semget ( ( key_t ) TxnInfoMemoryId, MaxPOSTxnInfo, IPC_CREAT | 0666 );

	if( TxnInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSTxnInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSTxnInfo; i++ )
	{
		if( semctl( TxnInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSTxnInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSTxnInfo; i++ )
	{
		memset( ( TxnInfoShmPtr + i ), 0, sizeof( struct EzPOSTxnInfo ) );
		strcpy( ( TxnInfoShmPtr + i )->TxnCodeGroupId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int TxnInfoCount = getEzPOSTxnInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSTxnInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( TxnInfoCount > MaxPOSTxnInfo )
	{
		dptr->trace( "TxnInfoCount[%d] > MaxPOSTxnInfo[%d]", TxnInfoCount, MaxPOSTxnInfo );
		return -1;
	}

	if( LoadEzPOSTxnInfo( TxnInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSTxnInfo......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSRespCodeInfo()
{
	RespCodeInfoMemoryId = CreateMemoryId( dptr, "POSRESPCODEINFOMEMORY" );

	if( RespCodeInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSRESPCODEINFOMEMORY..." );
		return -1;
	}

	RespCodeInfoShmId = shmget ( ( key_t ) RespCodeInfoMemoryId, sizeof( struct EzPOSRespCodeInfo ) * MaxPOSRespCodeInfo, IPC_CREAT | 0666 );

	if( RespCodeInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSRespCodeInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	RespCodeInfoShmPtr = ( struct EzPOSRespCodeInfo * ) shmat( RespCodeInfoShmId, 0, 0 );

	if( RespCodeInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSRespCodeInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	RespCodeInfoSemId = semget ( ( key_t ) RespCodeInfoMemoryId, MaxPOSRespCodeInfo, IPC_CREAT | 0666 );

	if( RespCodeInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSRespCodeInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSRespCodeInfo; i++ )
	{
		if( semctl( RespCodeInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSRespCodeInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSRespCodeInfo; i++ )
	{
		memset( ( RespCodeInfoShmPtr + i ), 0, sizeof( struct EzPOSRespCodeInfo ) );
		strcpy( ( RespCodeInfoShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int RespCodeInfoCount = getEzPOSRespCodeInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSRespCodeInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( RespCodeInfoCount > MaxPOSRespCodeInfo )
	{
		dptr->trace( "RespCodeInfoCount[%d] > MaxPOSRespCodeInfo[%d]",  RespCodeInfoCount, MaxPOSRespCodeInfo );
		return -1;
	}

	if( LoadEzPOSRespCodeInfo( RespCodeInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSRespCodeInfo......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSInBoundProperty()
{
	POSInBoundPropertyMemoryId = CreateMemoryId( dptr, "POSINBOUNDPROPERTYMEMORY" );

	if( POSInBoundPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSINBOUNDPROPERTYMEMORY..." );
		return -1;
	}

	POSInBoundPropertyShmId = shmget ( ( key_t ) POSInBoundPropertyMemoryId, sizeof( struct EzPOSInBoundProperty ) * MaxPOSInBoundProperty, IPC_CREAT | 0666 );

	if( POSInBoundPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating POSInBoundProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSInBoundPropertyShmPtr = ( struct EzPOSInBoundProperty * ) shmat( POSInBoundPropertyShmId, 0, 0 );

	if( POSInBoundPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSInBoundProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSInBoundPropertySemId = semget ( ( key_t ) POSInBoundPropertyMemoryId, MaxPOSInBoundProperty, IPC_CREAT | 0666 );

	if( POSInBoundPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating POSInBoundProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSInBoundProperty; i++ )
	{
		if( semctl( POSInBoundPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSInBoundProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSInBoundProperty; i++ )
	{
		memset( ( POSInBoundPropertyShmPtr + i ), 0, sizeof( struct EzPOSInBoundProperty ) );
		strcpy( ( POSInBoundPropertyShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int POSInBoundPropertyCount = getEzPOSInBoundPropertyCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSInBoundProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( POSInBoundPropertyCount > MaxPOSInBoundProperty )
	{
		dptr->trace( "POSInBoundPropertyCount[%d] > MaxPOSInBoundProperty[%d]",  POSInBoundPropertyCount, MaxPOSInBoundProperty );
		return -1;
	}

	if( LoadEzPOSInBoundProperty( POSInBoundPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSInBoundProperty......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSRouteInfo()
{
	POSRouteInfoMemoryId = CreateMemoryId( dptr, "POSROUTEINFOMEMORY" );

	if( POSRouteInfoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSROUTEINFOMEMORY..." );
		return -1;
	}

	POSRouteInfoShmId = shmget ( ( key_t ) POSRouteInfoMemoryId, sizeof( struct EzPOSRouteInfo ) * MaxPOSRouteInfo, IPC_CREAT | 0666 );

	if( POSRouteInfoShmId < 0 )
	{
		dptr->trace( "Error in Creating POSRouteInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSRouteInfoShmPtr = ( struct EzPOSRouteInfo * ) shmat( POSRouteInfoShmId, 0, 0 );

	if( POSRouteInfoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSRouteInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSRouteInfoSemId = semget ( ( key_t ) POSRouteInfoMemoryId, MaxPOSRouteInfo, IPC_CREAT | 0666 );

	if( POSRouteInfoSemId < 0 )
	{
		dptr->trace( "Error in Creating POSRouteInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSRouteInfo; i++ )
	{
		if( semctl( POSRouteInfoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSRouteInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSRouteInfo; i++ )
	{
		memset( ( POSRouteInfoShmPtr + i ), 0, sizeof( struct EzPOSRouteInfo ) );
		strcpy( ( POSRouteInfoShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL );
		( POSRouteInfoShmPtr + i )->DebugFlag = '0';
	}

	int SqlErr;
	int POSRouteInfoCount = getEzPOSRouteInfoCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSRouteInfo Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( POSRouteInfoCount > MaxPOSRouteInfo )
	{
		dptr->trace( "POSRouteInfoCount[%d] > MaxPOSRouteInfo[%d]",  POSRouteInfoCount, MaxPOSRouteInfo );
		return -1;
	}

	if( LoadEzPOSRouteInfo( POSRouteInfoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSRouteInfo......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSRouteSelect()
{
	POSRouteSelectMemoryId = CreateMemoryId( dptr, "POSROUTESELECTMEMORY" );

	if( POSRouteSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSROUTESELECTMEMORY..." );
		return -1;
	}

	POSRouteSelectShmId = shmget ( ( key_t ) POSRouteSelectMemoryId, sizeof( struct EzPOSRouteSelect ) * MaxPOSRouteSelect, IPC_CREAT | 0666 );

	if( POSRouteSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating POSRouteSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSRouteSelectShmPtr = ( struct EzPOSRouteSelect * ) shmat( POSRouteSelectShmId, 0, 0 );

	if( POSRouteSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSRouteSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSRouteSelectSemId = semget ( ( key_t ) POSRouteSelectMemoryId, MaxPOSRouteSelect, IPC_CREAT | 0666 );

	if( POSRouteSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating POSRouteSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSRouteSelect; i++ )
	{
		if( semctl( POSRouteSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSRouteSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSRouteSelect; i++ )
	{
		memset( ( POSRouteSelectShmPtr + i ), 0, sizeof( struct EzPOSRouteSelect ) );
		strcpy( ( POSRouteSelectShmPtr + i )->RouteSelectId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int POSRouteSelectCount = getEzPOSRouteSelectCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSRouteSelect Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( POSRouteSelectCount > MaxPOSRouteSelect )
	{
		dptr->trace( "POSRouteSelectCount[%d] > MaxPOSRouteSelect[%d]",  POSRouteSelectCount, MaxPOSRouteSelect );
		return -1;
	}

	if( LoadEzPOSRouteSelect( POSRouteSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSRouteSelect......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSMsgTranslate()
{
	POSMsgTranslateMemoryId = CreateMemoryId( dptr, "POSMSGTRANSLATEMEMORY" );

	if( POSMsgTranslateMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSMSGTRANSLATEMEMORY..." );
		return -1;
	}

	POSMsgTranslateShmId = shmget ( ( key_t ) POSMsgTranslateMemoryId, sizeof( struct EzPOSMsgTranslate ) * MaxPOSMsgTranslate, IPC_CREAT | 0666 );

	if( POSMsgTranslateShmId < 0 )
	{
		dptr->trace( "Error in Creating POSMsgTranslate Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSMsgTranslateShmPtr = ( struct EzPOSMsgTranslate * ) shmat( POSMsgTranslateShmId, 0, 0 );

	if( POSMsgTranslateShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSMsgTranslate Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSMsgTranslateSemId = semget ( ( key_t ) POSMsgTranslateMemoryId, MaxPOSMsgTranslate, IPC_CREAT | 0666 );

	if( POSMsgTranslateSemId < 0 )
	{
		dptr->trace( "Error in Creating POSMsgTranslate Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSMsgTranslate; i++ )
	{
		if( semctl( POSMsgTranslateSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSMsgTranslate Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSMsgTranslate; i++ )
	{
		memset( ( POSMsgTranslateShmPtr + i ), 0, sizeof( struct EzPOSMsgTranslate ) );
		strcpy( ( POSMsgTranslateShmPtr + i )->MsgTranslateId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int POSMsgTranslateCount = getEzPOSMsgTranslateCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSMsgTranslate Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( POSMsgTranslateCount > MaxPOSMsgTranslate )
	{
		dptr->trace( "POSMsgTranslateCount[%d] > MaxPOSMsgTranslate[%d]",  POSMsgTranslateCount, MaxPOSMsgTranslate );
		return -1;
	}

	if( LoadEzPOSMsgTranslate( POSMsgTranslateShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSMsgTranslate......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSChannelProperty()
{
	POSChannelPropertyMemoryId = CreateMemoryId( dptr, "POSCHANNELPROPERTYMEMORY" );

	if( POSChannelPropertyMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSCHANNELPROPERTYMEMORY..." );
		return -1;
	}

	POSChannelPropertyShmId = shmget ( ( key_t ) POSChannelPropertyMemoryId, sizeof( struct EzPOSChannelProperty ) * MaxPOSChannelProperty, IPC_CREAT | 0666 );

	if( POSChannelPropertyShmId < 0 )
	{
		dptr->trace( "Error in Creating POSChannelProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSChannelPropertyShmPtr = ( struct EzPOSChannelProperty * ) shmat( POSChannelPropertyShmId, 0, 0 );

	if( POSChannelPropertyShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSChannelProperty Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSChannelPropertySemId = semget ( ( key_t ) POSChannelPropertyMemoryId, MaxPOSChannelProperty, IPC_CREAT | 0666 );

	if( POSChannelPropertySemId < 0 )
	{
		dptr->trace( "Error in Creating POSChannelProperty Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSChannelProperty; i++ )
	{
		if( semctl( POSChannelPropertySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSChannelProperty Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSChannelProperty; i++ )
	{
		memset( ( POSChannelPropertyShmPtr + i ), 0, sizeof( struct EzPOSChannelProperty ) );
		strcpy( ( POSChannelPropertyShmPtr + i )->ChannelName, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int POSChannelPropertyCount = getEzPOSChannelPropertyCount( &SqlErr );
	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSChannelProperty Count...SqlErr[%05d]", SqlErr );
		return -1;
	}
	if( POSChannelPropertyCount > MaxPOSChannelProperty )
	{
		dptr->trace( "POSChannelPropertyCount[%d] > MaxPOSChannelProperty[%d]",  POSChannelPropertyCount, MaxPOSChannelProperty );
		return -1;
	}

	if( LoadEzPOSChannelProperty( POSChannelPropertyShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSChannelProperty......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSTxnRefSelect()
{
	POSTxnRefSelectMemoryId = CreateMemoryId( dptr, "POSTXNREFSELECTMEMORY" );

	if( POSTxnRefSelectMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSTXNREFSELECTMEMORY..." );
		return -1;
	}

	POSTxnRefSelectShmId = shmget ( ( key_t ) POSTxnRefSelectMemoryId, sizeof( struct EzPOSTxnRefSelect ) * MaxPOSTxnRefSelect, IPC_CREAT | 0666 );

	if( POSTxnRefSelectShmId < 0 )
	{
		dptr->trace( "Error in Creating POSTxnRefSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSTxnRefSelectShmPtr = ( struct EzPOSTxnRefSelect * ) shmat( POSTxnRefSelectShmId, 0, 0 );

	if( POSTxnRefSelectShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSTxnRefSelect Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSTxnRefSelectSemId = semget ( ( key_t ) POSTxnRefSelectMemoryId, MaxPOSTxnRefSelect, IPC_CREAT | 0666 );

	if( POSTxnRefSelectSemId < 0 )
	{
		dptr->trace( "Error in Creating POSTxnRefSelect Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSTxnRefSelect; i++ )
	{
		if( semctl( POSTxnRefSelectSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSTxnRefSelect Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSTxnRefSelect; i++ )
	{
		memset( ( POSTxnRefSelectShmPtr + i ), 0, sizeof( struct EzPOSTxnRefSelect ) );
		strcpy( ( POSTxnRefSelectShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int POSTxnRefSelectCount = getEzPOSTxnRefSelectCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSTxnRefSelect Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( POSTxnRefSelectCount > MaxPOSTxnRefSelect )
	{
		dptr->trace( "POSTxnRefSelectCount[%d] > MaxPOSTxnRefSelect[%d]",  POSTxnRefSelectCount, MaxPOSTxnRefSelect );
		return -1;
	}

	if( LoadEzPOSTxnRefSelect( POSTxnRefSelectShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSTxnRefSelect......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzPOSMgrUtil :: LoadPOSTxnRel()
{
	POSTxnRelMemoryId = CreateMemoryId( dptr, "POSTXNRELMEMORY" );

	if( POSTxnRelMemoryId < 0 )
	{
		dptr->trace( "Error in Creating POSTXNRELMEMORY..." );
		return -1;
	}

	POSTxnRelShmId = shmget ( ( key_t ) POSTxnRelMemoryId, sizeof( struct EzPOSTxnRel ) * MaxPOSTxnRel, IPC_CREAT | 0666 );

	if( POSTxnRelShmId < 0 )
	{
		dptr->trace( "Error in Creating POSTxnRel Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSTxnRelShmPtr = ( struct EzPOSTxnRel * ) shmat( POSTxnRelShmId, 0, 0 );

	if( POSTxnRelShmPtr == NULL )
	{
		dptr->trace( "Error in attaching POSTxnRel Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	POSTxnRelSemId = semget ( ( key_t ) POSTxnRelMemoryId, MaxPOSTxnRel, IPC_CREAT | 0666 );

	if( POSTxnRelSemId < 0 )
	{
		dptr->trace( "Error in Creating POSTxnRel Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxPOSTxnRel; i++ )
	{
		if( semctl( POSTxnRelSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting POSTxnRel Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxPOSTxnRel; i++ )
	{
		memset( ( POSTxnRelShmPtr + i ), 0, sizeof( struct EzPOSTxnRel ) );
		strcpy( ( POSTxnRelShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL );
	}

	int SqlErr;
	int POSTxnRelCount = getEzPOSTxnRelCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzPOSTxnRel Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( POSTxnRelCount > MaxPOSTxnRel )
	{
		dptr->trace( "POSTxnRelCount[%d] > MaxPOSTxnRel[%d]",  POSTxnRelCount, MaxPOSTxnRel );
		return -1;
	}

	if( LoadEzPOSTxnRel( POSTxnRelShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzPOSTxnRel......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

