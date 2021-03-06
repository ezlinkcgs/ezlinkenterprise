#include <ezlink/eznetworkmgrutil.h>

int EzNetworkMgrUtil :: initNetworkMgrUtil( EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
    EzCfgUtil cfgutil;
    struct EzChannelMgrQMsg chqmsg;
    int EzChannelMgrKey, EzChannelMgrQid;

    this->dptr = dptr;

    if( initEzNetworkMgrODBC( "EzNetworkMgr", dptr ) < 0 )
    {
    	dptr->trace( "Error in initEzNetworkMgrODBC" );
    	return -1;
    }
    memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
        dptr->trace( "Error in opening file[%s]", cfgpath );
        return -1;
    }

    memset( cfgval, 0, sizeof( cfgval ) );
    if( cfgutil.cfg_search( "CHANNEL#ORGKEY", cfgval, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching CHANNEL#ORGKEY from file[%s]", cfgpath );
        cfgutil.cfg_close();
        return -1;
    }
    cfgutil.cfg_close();
    EzChannelMgrKey = atoi( cfgval ) + 2;
    EzChannelMgrQid = msgget( ( key_t ) EzChannelMgrKey, IPC_CREAT | 0666 );
	if( EzChannelMgrQid < 0 )
    {
		dptr->trace( "Error in Creating EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
    }

    memset( &chqmsg, 0, sizeof( chqmsg ) );
    chqmsg.msgtype = 1;
    strcpy( chqmsg.chmgrmsg.ChannelName, "NETWORKMEMORY" );
    chqmsg.chmgrmsg.Command = CREATE_MEMORY_CHANNEL;
    chqmsg.chmgrmsg.NotificationId = getpid();

    if( msgsnd( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
    {
        dptr->trace( "Error in Sending Locate Memory Channel Message to EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
        return -1;
    }

    memset( &chqmsg, 0, sizeof( chqmsg ) );
    if( msgrcv( EzChannelMgrQid, &chqmsg, sizeof( chqmsg ) - sizeof( long ), getpid(), 0 ) < 0 )
    {
            dptr->trace( "Error in Receiving Locate Memory Channel Message From EzChannelMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }
    if( chqmsg.chmgrmsg.Response < 0 )
    {
        dptr->trace( "Error in Locating Memory[%s]", "NETWORKMEMORY" );
        return -1;
    }

    dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with ChannelKeyId[%d]", chqmsg.chmgrmsg.ChannelName, chqmsg.chmgrmsg.ChannelKeyId );
	NetworkMemoryId = chqmsg.chmgrmsg.ChannelKeyId;

    memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlink.cfg" );

    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
            dptr->trace( "Error in opening file[%s]", cfgpath );
            return -1;
    }

    memset( cfgval, 0, sizeof( cfgval ) );
    if( cfgutil.cfg_search( "NETWORK#MAXNETWORK", cfgval, 2 ) < 0 )
    {
            dptr->trace( "Error in Searching NETWORK#MAXNETWORK from file[%s]", cfgpath );
            cfgutil.cfg_close();
            return -1;
    }

    cfgutil.cfg_close();
    MaxNetworks = atoi( cfgval );

	return 1;
}

int EzNetworkMgrUtil :: LoadNetworkMemory()
{
	int NetworkCount, SqlErr = 0;

	NetworkMemoryShmid = shmget( ( key_t ) NetworkMemoryId, sizeof( struct EzNetworkMemory ) * MaxNetworks, IPC_CREAT | 0666 );

    if(  NetworkMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;

    }

    NetworkMemoryShmPtr = ( struct EzNetworkMemory * ) shmat( NetworkMemoryShmid, 0, 0 );

    if( NetworkMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

	for( int i = 0; i < MaxNetworks; i++ )
	{
		memset( ( NetworkMemoryShmPtr + i ), 0, sizeof( struct EzNetworkMemory ) );
		strcpy( ( NetworkMemoryShmPtr + i )->NetworkId, NETWORKID_INIT_VAL );
	}

	NetworkCount = getEzNetworkCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in getting EzNetwork Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( NetworkCount > MaxNetworks )
	{
		dptr->trace( "No.of Networks configured in EzNetwork Table > MaxNetworks...Increase the MaxNetworks Parameter");
		return -1;
	}

	if( LoadEzNetwork( NetworkMemoryShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error while loading EzNetwork Table OraErr[%04d]", SqlErr );
		return -1;
	}

	NetworkMemorySemid = semget( ( key_t ) NetworkMemoryId, MaxNetworks, IPC_CREAT | 0666 );

    if( NetworkMemorySemid < 0 )
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

	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( semctl( NetworkMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting Network Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzNetworkMgrUtil :: getNetworkMemory()
{
	NetworkMemoryShmid = shmget( ( key_t ) NetworkMemoryId, 0, IPC_CREAT | 0666 );

    if(  NetworkMemoryShmid < 0 )
    {
            dptr->trace( "Error in Creating Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

    NetworkMemoryShmPtr = ( struct EzNetworkMemory * ) shmat( NetworkMemoryShmid, 0, 0 );
    if( NetworkMemoryShmPtr == NULL )
    {
            dptr->trace( "Error in attaching Network Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }

    NetworkMemorySemid = semget( ( key_t ) NetworkMemoryId, 0, IPC_CREAT | 0666 );
    if( NetworkMemorySemid < 0 )
    {
            dptr->trace( "Error in Creating Network Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }
	return 1;
}

int EzNetworkMgrUtil :: getDBString( char *DBString )
{
	FILE *db_fptr;
	char DBSeqNoPath[ EZDBSEQNOPATH_SIZE + 1 ];
	int DBSeqNo, FDBSeqNo;

	memset( DBSeqNoPath, 0, sizeof( DBSeqNoPath ) );
	sprintf( DBSeqNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "DBSeqNo.dat" );

	db_fptr = fopen( DBSeqNoPath, "r" );
	if( db_fptr == NULL )
	{
		db_fptr = fopen( DBSeqNoPath, "w" );
		if( db_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", DBSeqNoPath );
			DBSeqNo = 1;
		}
		else
		{
			DBSeqNo = 1;
			fprintf( db_fptr, "%d", DBSeqNo );
			fclose( db_fptr );
		}
	}
	else
	{
		fscanf( db_fptr, "%d", &DBSeqNo );
		fclose( db_fptr );

		if( DBSeqNo == 999999 )
			FDBSeqNo = 1;
		else
			FDBSeqNo = DBSeqNo + 1;

		db_fptr = fopen( DBSeqNoPath, "w" );
		if( db_fptr == NULL )
			dptr->trace( "Error in Opening File[%s]", DBSeqNoPath );
		else
		{
			fprintf( db_fptr, "%d", FDBSeqNo );
			fclose( db_fptr );
		}
	}
	sprintf( DBString, "%06d%06d%06d%d", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime(), DBSeqNo, getpid() );

	return 1;
}

int EzNetworkMgrUtil :: LoadTxnDBMemory()
{
	char DBString[ EZTXNDBFLD_SIZE + 1 ];
	struct sembuf sem_buf;

	TxnDBMemoryId = CreateMemoryId( dptr, "TXNDBMEMORY" );

	if( TxnDBMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNDBMEMORY..." );
		return -1;
	}

	TxnDBShmId = shmget ( ( key_t ) TxnDBMemoryId, sizeof( struct EzTxnDBMemory ), IPC_CREAT | 0666 );

	if( TxnDBShmId < 0 )
	{
		dptr->trace( "Error in Creating EzTxnDB Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnDBShmPtr = ( struct EzTxnDBMemory * ) shmat( TxnDBShmId, 0, 0 );

	if( TxnDBShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzTxnDB Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnDBSemId = semget ( ( key_t ) TxnDBMemoryId, 1, IPC_CREAT | 0666 );

	if( TxnDBSemId < 0 )
	{
		dptr->trace( "Error in Creating EzTxnDB Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	if( semctl( TxnDBSemId, 0, SETVAL, arg ) < 0 )
	{
		dptr->trace( "Error in Setting Semaphore Value for TxnDB Semahore...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnDBSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( DBString, 0, sizeof( DBString ) );
	memset( TxnDBShmPtr, 0, sizeof( struct EzTxnDBMemory ) );
	getDBString( DBString );

	strcpy( TxnDBShmPtr->EzTxnRouteInfoVal, DBString );
	strcpy( TxnDBShmPtr->EzTxnRouteSelectVal, DBString );
	strcpy( TxnDBShmPtr->EzEventPropertyVal, DBString );
	strcpy( TxnDBShmPtr->EzChannelPropertyVal, DBString );
	strcpy( TxnDBShmPtr->EzMsgTypePropertyVal, DBString );
	strcpy( TxnDBShmPtr->EzMsgTranslateVal, DBString );
	strcpy( TxnDBShmPtr->EzNetworkPropertyVal, DBString );

	dptr->trace( DEBUG_TEST, "EzTxnRouteInfoVal[%s]", TxnDBShmPtr->EzTxnRouteInfoVal );
	dptr->trace( DEBUG_TEST, "EzTxnRouteSelectVal[%s]", TxnDBShmPtr->EzTxnRouteSelectVal );
	dptr->trace( DEBUG_TEST, "EzEventPropertyVal[%s]", TxnDBShmPtr->EzEventPropertyVal );
	dptr->trace( DEBUG_TEST, "EzChannelPropertyVal[%s]", TxnDBShmPtr->EzChannelPropertyVal );
	dptr->trace( DEBUG_TEST, "EzMsgTypePropertyVal[%s]", TxnDBShmPtr->EzMsgTypePropertyVal );
	dptr->trace( DEBUG_TEST, "EzMsgTranslateVal[%s]", TxnDBShmPtr->EzMsgTranslateVal );
	dptr->trace( DEBUG_TEST, "EzNetworkPropertyVal[%s]", TxnDBShmPtr->EzNetworkPropertyVal );

	sem_buf.sem_op = 2;
	if( semop( TxnDBSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: getTxnDBMemory()
{
	TxnDBMemoryId = LocateMemoryId( dptr, "TXNDBMEMORY" );

	if( TxnDBMemoryId < 0 )
	{
		dptr->trace( "Error in Locating TXNDBMEMORY..." );
		return -1;
	}

	TxnDBShmId = shmget ( ( key_t ) TxnDBMemoryId, 0, IPC_CREAT | 0666 );

	if( TxnDBShmId < 0 )
	{
		dptr->trace( "Error in Getting EzTxnDB Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnDBShmPtr = ( struct EzTxnDBMemory * ) shmat( TxnDBShmId, 0, 0 );

	if( TxnDBShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzTxnDB Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnDBSemId = semget ( ( key_t ) TxnDBMemoryId, 0, IPC_CREAT | 0666 );

	if( TxnDBSemId < 0 )
	{
		dptr->trace( "Error in Getting EzTxnDB Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: LoadSafRecordNo()
{
	struct sembuf sem_buf;
	FILE *saf_fptr;
	char SafRecordPath[ SAF_RECORD_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( SafRecordPath, 0, sizeof( SafRecordPath ) );
	sprintf( SafRecordPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "SafRecordNo.dat" );

	saf_fptr = fopen( SafRecordPath, "r" );

	if( saf_fptr == NULL )
	{
		saf_fptr = fopen( SafRecordPath, "w" );
		if( saf_fptr == NULL )
		{
			dptr->trace( "Error in Opening File [%s]", SafRecordPath );
			return -1;
		}
		memset( TxnSeqShmPtr->SafRecordNo, 0, sizeof( TxnSeqShmPtr->SafRecordNo ) );
		dptr->trace( DEBUG_TEST, "Initializing SafRecordNo...Since there is no SafRecordNo.dat file" );
		ezsequtil.InitSeqNo( TxnSeqShmPtr->SafRecordNo, 20 );
		dptr->trace( DEBUG_TEST, "SafRecordNo[%s]...1", TxnSeqShmPtr->SafRecordNo );
		ezsequtil.GenNextSeqNo( TxnSeqShmPtr->SafRecordNo );
		fprintf( saf_fptr, "%s", TxnSeqShmPtr->SafRecordNo );
		dptr->trace( DEBUG_TEST, "SafRecordNo[%s]...2", TxnSeqShmPtr->SafRecordNo );
		fclose( saf_fptr );
	}
	else
	{
		memset( TxnSeqShmPtr->SafRecordNo, 0, sizeof( TxnSeqShmPtr->SafRecordNo ) );
		fscanf( saf_fptr, "%s", TxnSeqShmPtr->SafRecordNo );
		dptr->trace( DEBUG_TEST, "SafRecordNo[%s]...From File", TxnSeqShmPtr->SafRecordNo );
		if( !strlen( TxnSeqShmPtr->SafRecordNo ) )
		{
			dptr->trace( DEBUG_TEST, "SafRecordNo[%s]...is Null", TxnSeqShmPtr->SafRecordNo );
			memset( TxnSeqShmPtr->SafRecordNo, 0, sizeof( TxnSeqShmPtr->SafRecordNo ) );
			ezsequtil.InitSeqNo( TxnSeqShmPtr->SafRecordNo, 20 );
			dptr->trace( DEBUG_TEST, "SafRecordNo[%s]...1", TxnSeqShmPtr->SafRecordNo );
			ezsequtil.GenNextSeqNo( TxnSeqShmPtr->SafRecordNo );
			dptr->trace( DEBUG_TEST, "SafRecordNo[%s]...2", TxnSeqShmPtr->SafRecordNo );
		}
		fclose( saf_fptr );
	}

	sem_buf.sem_op = 2;
	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzNetworkMgrUtil :: LoadTraceNo()
{
	int TraceNo;
	FILE *trace_fptr;
	struct sembuf sem_buf;
	char TraceNoPath[ TRACENO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( TraceNoPath, 0, sizeof( TraceNoPath ) );
	sprintf( TraceNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "TraceNo.dat" );

	trace_fptr = fopen( TraceNoPath, "r" );

	if( trace_fptr == NULL )
	{
		trace_fptr = fopen( TraceNoPath, "w" );
		if( trace_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", TraceNoPath );
			return -1;
		}
		TxnSeqShmPtr->TraceNo = 1;
		fprintf( trace_fptr, "%d", TxnSeqShmPtr->TraceNo );
		fclose( trace_fptr );
	}
	else
	{
		fscanf( trace_fptr, "%d", &TxnSeqShmPtr->TraceNo );
		fclose( trace_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: LoadRefNo()
{
	struct sembuf sem_buf;
	FILE *ref_fptr;
	char RefNoPath[ REFNO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( RefNoPath, 0, sizeof( RefNoPath ) );
	sprintf( RefNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "RefNo.dat" );

	ref_fptr = fopen( RefNoPath, "r" );

	if( ref_fptr == NULL )
	{
		ref_fptr = fopen( RefNoPath, "w" );
		if( ref_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", RefNoPath );
			return -1;
		}
		TxnSeqShmPtr->RefNo = 1;
		fprintf( ref_fptr, "%d", TxnSeqShmPtr->RefNo );
		fclose( ref_fptr );
	}
	else
	{
		fscanf( ref_fptr, "%d", &TxnSeqShmPtr->RefNo );
		fclose( ref_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: LoadLogNo()
{
	struct sembuf sem_buf;
	FILE *ref_fptr;
	char LogNoPath[ REFNO_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( LogNoPath, 0, sizeof( LogNoPath ) );
	sprintf( LogNoPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "LogNo.dat" );

	ref_fptr = fopen( LogNoPath, "r" );

	if( ref_fptr == NULL )
	{
		ref_fptr = fopen( LogNoPath, "w" );
		if( ref_fptr == NULL )
		{
			dptr->trace( "Error in Opening File[%s]", LogNoPath );
			return -1;
		}
		TxnSeqShmPtr->LogNo = 1;
		fprintf( ref_fptr, "%d", TxnSeqShmPtr->LogNo );
		fclose( ref_fptr );
	}
	else
	{
		fscanf( ref_fptr, "%d", &TxnSeqShmPtr->LogNo );
		fclose( ref_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( TxnSeqSemId, &sem_buf, 1 ) < 0 )
	{
		dptr->trace( "Error in Semop...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: LoadTxnSeqMemory()
{
	TxnSeqMemoryId = CreateMemoryId( dptr, "TXNSEQMEMORY" );

	if( TxnSeqMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNSEQMEMORY..." );
		return -1;
	}

	TxnSeqShmId = shmget ( ( key_t ) TxnSeqMemoryId, sizeof( struct EzTxnSeqMemory ), IPC_CREAT | 0666 );

	if( TxnSeqShmId < 0 )
	{
		dptr->trace( "Error in Creating EzTxnSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnSeqShmPtr = ( struct EzTxnSeqMemory * ) shmat( TxnSeqShmId, 0, 0 );

	if( TxnSeqShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzTxnSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnSeqSemId = semget ( ( key_t ) TxnSeqMemoryId, 1, IPC_CREAT | 0666 );

	if( TxnSeqSemId < 0 )
	{
		dptr->trace( "Error in Creating EzTxnSeq Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	if( semctl( TxnSeqSemId, 0, SETVAL, arg ) < 0 )
	{
		dptr->trace( "Error in Setting Network Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "Loading inf file");
	if( LoadSafRecordNo() < 0 )
		return -1;
	dptr->trace( DEBUG_TEST, "Loaded SAF Record No");
	if( LoadTraceNo() < 0 )
		return -1;
	dptr->trace( DEBUG_TEST, "Loaded Trace No");
	if( LoadRefNo() < 0 )
		return -1;
	dptr->trace( DEBUG_TEST, "Loaded Ref No");
	if( LoadLogNo() < 0 )
		return -1;
	dptr->trace( DEBUG_TEST, "Loaded Log No");
	return 1;
}

int EzNetworkMgrUtil :: getTxnSeqMemory()
{
	TxnSeqMemoryId = LocateMemoryId( dptr, "TXNSEQMEMORY" );

	if( TxnSeqMemoryId < 0 )
	{
		dptr->trace( "Error in Loacting TXNSEQMEMORY..." );
		return -1;
	}

	TxnSeqShmId = shmget ( ( key_t ) TxnSeqMemoryId, 0, IPC_CREAT | 0666 );

	if( TxnSeqShmId < 0 )
	{
		dptr->trace( "Error in getting EzTxnSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnSeqShmPtr = ( struct EzTxnSeqMemory * ) shmat( TxnSeqShmId, 0, 0 );

	if( TxnSeqShmPtr == NULL )
	{
		dptr->trace( "Error in attaching EzTxnSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnSeqSemId = semget ( ( key_t ) TxnSeqMemoryId, 0, IPC_CREAT | 0666 );

	if( TxnSeqSemId < 0 )
	{
		dptr->trace( "Error in getting EzTxnSeq Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: LoadReplayMemory()
{
	ReplayMemoryId = CreateMemoryId( dptr, "REPLAYMEMORY" );

	if( ReplayMemoryId < 0 )
	{
		dptr->trace( "Error in Creating REPLAYMEMORY..." );
		return -1;
	}

	ReplayShmId = shmget ( ( key_t ) ReplayMemoryId, sizeof( struct EzReplayTable ) * MaxNetworks, IPC_CREAT | 0666 );

	if( ReplayShmId < 0 )
	{
		dptr->trace( "Error in Creating Replay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ReplayShmPtr = ( struct EzReplayTable * ) shmat( ReplayShmId, 0, 0 );

	if( ReplayShmPtr == NULL )
	{
		dptr->trace( "Error in attaching Replay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ReplaySemId = semget ( ( key_t ) ReplayMemoryId, MaxNetworks, IPC_CREAT | 0666 );

	if( ReplaySemId < 0 )
	{
		dptr->trace( "Error in Creating Replay Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "Replay Semaphore Created with SemId[%d]", ReplaySemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( semctl( ReplaySemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting Network Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxNetworks; i++ )
	{
		memset( ( ReplayShmPtr + i ), 0, sizeof( struct EzReplayTable ) );
		strcpy( ( ReplayShmPtr + i )->NetworkId, REPLAY_NETWORKID_INIT_VAL );
	}

	int SqlErr;
	int NetworkReplayCount = getEzNetworkReplayCount( &SqlErr );
	if( NetworkReplayCount > MaxNetworks )
	{
		dptr->trace( "NetworkReplayCount[%d] > MaxNetworks[%d]", NetworkReplayCount, MaxNetworks );
		return -1;
	}

	struct EzNetworkReplay *networkreplay_ptr;
	networkreplay_ptr = ( struct EzNetworkReplay * ) malloc ( sizeof( struct EzNetworkReplay ) * NetworkReplayCount );
	memset( networkreplay_ptr, 0, sizeof( struct EzNetworkReplay ) * NetworkReplayCount );
	if( LoadEzNetworkReplay( networkreplay_ptr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzNetworkReplay......OraErr[%05d]", SqlErr );
		free( networkreplay_ptr );
		return -1;
	}

	for( int i = 0; i < NetworkReplayCount; i++ )
	{
		strcpy( ( ReplayShmPtr + i )->NetworkId, ( networkreplay_ptr + i )->NetworkId );
		( ReplayShmPtr + i )->ReplayInterval = ( networkreplay_ptr + i )->ReplayInterval;
		( ReplayShmPtr + i )->ReplayProperty = ( networkreplay_ptr + i )->ReplayProperty;
		( ReplayShmPtr + i )->ReplayAction = ( networkreplay_ptr + i )->ReplayAction;
		( ReplayShmPtr + i )->ReplayLookUpInterval = ( networkreplay_ptr + i )->ReplayLookUpInterval;
		( ReplayShmPtr + i )->Status = REPLAY_NETWORK_RUNNING;
		( ReplayShmPtr + i )->ReplayStatus = REPLAY_STATUS_IDLE;
		( ReplayShmPtr + i )->ReplayFlag = REPLAY_FLAG_IDLE;
		( ReplayShmPtr + i )->MsgTypeIndicator = REPLAY_MSGTYPEINDICATOR_INIT;
	}

	free( networkreplay_ptr );
	return 1;
}

int EzNetworkMgrUtil :: getReplayMemory()
{
	ReplayMemoryId = LocateMemoryId( dptr, "REPLAYMEMORY" );

	if( ReplayMemoryId < 0 )
	{
		dptr->trace( "Error in Locating REPLAYMEMORY..." );
		return -1;
	}

	ReplayShmId = shmget ( ( key_t ) ReplayMemoryId, 0, IPC_CREAT | 0666 );

	if( ReplayShmId < 0 )
	{
		dptr->trace( "Error in Creating Replay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ReplayShmPtr = ( struct EzReplayTable * ) shmat( ReplayShmId, 0, 0 );

	if( ReplayShmPtr == NULL )
	{
		dptr->trace( "Error in attaching Replay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	ReplaySemId = semget ( ( key_t ) ReplayMemoryId, 0, IPC_CREAT | 0666 );

	if( ReplaySemId < 0 )
	{
		dptr->trace( "Error in Creating Replay Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzNetworkMgrUtil :: LoadNetworkBusMemory()
{
	NetworkBusMemoryId = CreateMemoryId( dptr, "NETWORKBUSMEMORY" );

	if( NetworkBusMemoryId < 0 )
	{
		dptr->trace( "Error in Creating NETWORKBUSMEMORY..." );
		return -1;
	}

	NetworkBusShmId = shmget ( ( key_t ) NetworkBusMemoryId, sizeof( struct EzBusDayTable ) * MaxNetworks, IPC_CREAT | 0666 );

	if( NetworkBusShmId < 0 )
	{
		dptr->trace( "Error in Creating NetworkBusDay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkBusShmPtr = ( struct EzBusDayTable * ) shmat( NetworkBusShmId, 0, 0 );

	if( NetworkBusShmPtr == NULL )
	{
		dptr->trace( "Error in attaching NetworkBusDay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkBusSemId = semget ( ( key_t ) NetworkBusMemoryId, MaxNetworks, IPC_CREAT | 0666 );

	if( NetworkBusSemId < 0 )
	{
		dptr->trace( "Error in Creating NetworkBusDay Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "NetworkBusDay Semaphore Created with SemId[%d]", NetworkBusSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( semctl( NetworkBusSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting NetworkBusDay Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxNetworks; i++ )
	{
		memset( ( NetworkBusShmPtr + i ), 0, sizeof( struct EzBusDayTable ) );
		strcpy( ( NetworkBusShmPtr + i )->NetworkId, BUSDAY_NETWORKID_INIT_VAL );
	}

	int SqlErr;

	int NetworkBusDayCount = getEzNetworkBusDayCount( &SqlErr );
	if( NetworkBusDayCount > MaxNetworks )
	{
		dptr->trace( "NetworkBusDayCount[%d] > MaxNetworks[%d]", NetworkBusDayCount, MaxNetworks );
		return -1;
	}

	struct EzNetworkBusDay *networkbusday_ptr;
	networkbusday_ptr = ( struct EzNetworkBusDay * ) malloc ( sizeof( struct EzNetworkBusDay ) * NetworkBusDayCount );
	memset( networkbusday_ptr, 0, sizeof( struct EzNetworkBusDay ) * NetworkBusDayCount );
	if( LoadEzNetworkBusDay( networkbusday_ptr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzNetworkBusDay......OraErr[%05d]", SqlErr );
		free( networkbusday_ptr );
		return -1;
	}

	for( int i = 0; i < NetworkBusDayCount; i++ )
	{
		strcpy( ( NetworkBusShmPtr + i )->NetworkId, ( networkbusday_ptr + i )->NetworkId );
		( NetworkBusShmPtr + i )->CutOverUseFlag = ( networkbusday_ptr + i )->CutOverUseFlag;
		( NetworkBusShmPtr + i )->CutOverDate = ( networkbusday_ptr + i )->CutOverDate;
		( NetworkBusShmPtr + i )->CutOverTime = ( networkbusday_ptr + i )->CutOverTime;
	}
	free( networkbusday_ptr );
	return 1;
}

int EzNetworkMgrUtil :: getNetworkBusMemory()
{
	NetworkBusMemoryId = LocateMemoryId( dptr, "NETWORKBUSMEMORY" );

	if( NetworkBusMemoryId < 0 )
	{
		dptr->trace( "Error in Locating NETWORKBUSMEMORY..." );
		return -1;
	}

	NetworkBusShmId = shmget ( ( key_t ) NetworkBusMemoryId, 0, IPC_CREAT | 0666 );

	if( NetworkBusShmId < 0 )
	{
		dptr->trace( "Error in Creating NetworkBusDay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkBusShmPtr = ( struct EzBusDayTable * ) shmat( NetworkBusShmId, 0, 0 );

	if( NetworkBusShmPtr == NULL )
	{
		dptr->trace( "Error in attaching NetworkBusDay Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	NetworkBusSemId = semget ( ( key_t ) NetworkBusMemoryId, 0, IPC_CREAT | 0666 );

	if( NetworkBusSemId < 0 )
	{
		dptr->trace( "Error in Creating NetworkBusDay Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	dptr->trace( DEBUG_TEST, "NetworkBusDay Semaphore Created with SemId[%d]", NetworkBusSemId );

	return 1;
}

int EzNetworkMgrUtil :: LoadEchoMemory()
{
	EchoMemoryId = CreateMemoryId( dptr, "ECHOMEMORY" );

	if( EchoMemoryId < 0 )
	{
		dptr->trace( "Error in Creating ECHOMEMORY..." );
		return -1;
	}

	EchoShmId = shmget ( ( key_t ) EchoMemoryId, sizeof( struct EzEchoTable ) * MaxNetworks, IPC_CREAT | 0666 );

	if( EchoShmId < 0 )
	{
		dptr->trace( "Error in Creating Echo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EchoShmPtr = ( struct EzEchoTable * ) shmat( EchoShmId, 0, 0 );

	if( EchoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching Echo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EchoSemId = semget ( ( key_t ) EchoMemoryId, MaxNetworks, IPC_CREAT | 0666 );

	if( EchoSemId < 0 )
	{
		dptr->trace( "Error in Creating Echo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxNetworks; i++ )
	{
		if( semctl( EchoSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting Echo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxNetworks; i++ )
	{
		memset( ( EchoShmPtr + i ), 0, sizeof( EzEchoTable ) );
		strcpy( ( EchoShmPtr + i )->NetworkId, ECHO_NETWORKID_INIT_VAL );
		( EchoShmPtr + i )->Status = ECHO_THREAD_RUNNING;
		( EchoShmPtr + i )->EchoRespStatus = ECHO_RESP_STATUS_INIT;
	}

	int SqlErr;
	int NetworkEchoCount = getEzNetworkEchoCount( &SqlErr );

	if( SqlErr != 0 )
	{
		dptr->trace( "Error in Getting EzNetworkEchoCount....SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( NetworkEchoCount > MaxNetworks )
	{
		dptr->trace( "NetworkCount[%d] > MaxNetworks[%d]", NetworkEchoCount, MaxNetworks );
		return -1;
	}

	if( LoadEzNetworkEcho( EchoShmPtr, &SqlErr ) < 0 )
	{
		dptr->trace( "Error in Loading EzNetworkEcho......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzNetworkMgrUtil :: getEchoMemory()
{
	EchoMemoryId = LocateMemoryId( dptr, "ECHOMEMORY" );

	if( EchoMemoryId < 0 )
	{
		dptr->trace( "Error in Locating ECHOMEMORY..." );
		return -1;
	}

	EchoShmId = shmget ( ( key_t ) EchoMemoryId, 0, IPC_CREAT | 0666 );

	if( EchoShmId < 0 )
	{
		dptr->trace( "Error in Getting Echo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EchoShmPtr = ( struct EzEchoTable * ) shmat( EchoShmId, 0, 0 );

	if( EchoShmPtr == NULL )
	{
		dptr->trace( "Error in attaching Echo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	EchoSemId = semget ( ( key_t ) EchoMemoryId, 0, IPC_CREAT | 0666 );

	if( EchoSemId < 0 )
	{
		dptr->trace( "Error in Getting Echo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}


int EzNetworkMgrUtil :: addNetworkMemory( struct EzNetwork *eznetwork_ptr )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkMemoryShmPtr + i )->NetworkId, NETWORKID_INIT_VAL ) )
		{
			memset( ( NetworkMemoryShmPtr + i ), 0, sizeof( struct EzNetworkMemory ) );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkId, eznetwork_ptr->NetworkId );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkName, eznetwork_ptr->NetworkName );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkPropertyId, eznetwork_ptr->NetworkPropertyId );
			( NetworkMemoryShmPtr + i )->TimeOut = eznetwork_ptr->TimeOut;
			strcpy( ( NetworkMemoryShmPtr + i )->ChannelName, eznetwork_ptr->ChannelName );
			strcpy( ( NetworkMemoryShmPtr + i )->PortName, eznetwork_ptr->PortName );
			( NetworkMemoryShmPtr + i )->NetworkStatus = eznetwork_ptr->NetworkStatus;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetworkMgrUtil :: updateNetworkMemory( struct EzNetwork *eznetwork_ptr )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkMemoryShmPtr + i )->NetworkId, eznetwork_ptr->NetworkId ) )
		{
			memset( ( NetworkMemoryShmPtr + i ), 0, sizeof( struct EzNetworkMemory ) );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkId, eznetwork_ptr->NetworkId );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkName, eznetwork_ptr->NetworkName );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkPropertyId, eznetwork_ptr->NetworkPropertyId );
			( NetworkMemoryShmPtr + i )->TimeOut = eznetwork_ptr->TimeOut;
			strcpy( ( NetworkMemoryShmPtr + i )->ChannelName, eznetwork_ptr->ChannelName );
			strcpy( ( NetworkMemoryShmPtr + i )->PortName, eznetwork_ptr->PortName );
			( NetworkMemoryShmPtr + i )->NetworkStatus = eznetwork_ptr->NetworkStatus;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetworkMgrUtil :: removeNetworkMemory( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			memset( ( NetworkMemoryShmPtr + i ), 0, sizeof( struct EzNetworkMemory ) );
			strcpy( ( NetworkMemoryShmPtr + i )->NetworkId, NETWORKID_INIT_VAL );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetworkMgrUtil :: readNetworkMemory( const char *NetworkId )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			memset( &eznetworkmem_rec, 0, sizeof( struct EzNetworkMemory ) );
			memcpy( &eznetworkmem_rec, NetworkMemoryShmPtr + i, sizeof( struct EzNetworkMemory ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;

}

int EzNetworkMgrUtil :: updateNetworkStatus( const char *NetworkId, int NetworkStatus )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxNetworks; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			( NetworkMemoryShmPtr + i )->NetworkStatus = NetworkStatus;
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( "Error while doing semop for NetworkMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzNetworkMgrUtil :: updateNetworkBusDay( const char *NetworkId, int CutoverDate )
{
	int SqlErr = 0;
	if( updateEzNetworkBusDay( NetworkId, CutoverDate, &SqlErr ) < 0 )
		return -1;
	return 0;
}
