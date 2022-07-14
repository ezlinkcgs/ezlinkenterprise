#include <ezlink/eztxnmon.h>


void EzSwitchMonMgr :: InitEzSwitchMonMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezswitchmonmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzSwitchMonMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
    	trace( "^^^^^^^^^^^EzSwitchMonMgr Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
	}

	if( CreateChannel( "EzSwitchMonMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzSwitchMonMgr.." );
    	trace( "^^^^^^^^^^^EzSwitchMonMgr Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
    }
	if (  LoadTxnMemory() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Loading  Transaction Memory..." );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzSwitchMonMgr Ended Abnormally^^^^^^^^^^^^^ ");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void EzSwitchMonMgr  :: ServiceRequest()
{
	while ( 1 )
	{
		pause();
	}


}

int EzSwitchMonMgr :: LoadTxnMemory()
{
	TxnMonMemoryId = CreateMemoryId( dptr, "TXNMONMEMORY" );

	if( TxnMonMemoryId < 0 )
	{
		dptr->trace( "Error in Creating TXNMONMEMORY..." );
		return -1;
	}

	TxnMonShmId = shmget ( ( key_t ) TxnMonMemoryId, sizeof( struct EzTranMon ) * MAX_MON_SIZE, IPC_CREAT | 0666 );

	if( TxnMonShmId < 0 )
	{
		dptr->trace( "Error in Creating Transaction Monitor Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnMonShmPtr = ( struct EzTranMon * ) shmat( TxnMonShmId, 0, 0 );

	if( TxnMonShmPtr == NULL )
	{
		dptr->trace( "Error in attaching Transaction Monitor Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnMonSemId = semget ( ( key_t ) TxnMonMemoryId, MAX_MON_SIZE, IPC_CREAT | 0666 );

	if( TxnMonSemId < 0 )
	{
		dptr->trace( "Error in Creating Transaction Monitor Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( DEBUG_TEST, "Transaction Monitor Semaphore Created with SemId[%d]", TxnMonSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MAX_MON_SIZE; i++ )
	{
		if( semctl( TxnMonSemId, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( "Error in Setting Transaction Monitor Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	for( int i = 0; i < MAX_MON_SIZE; i++ )
	{
		memset( ( TxnMonShmPtr + i ), 0, sizeof( struct EzTranMon ) );
		strcpy( ( TxnMonShmPtr + i )->ReqBuffer, RECORD_INIT_VAL );
	}
}

int main( int argc, char **argv )
{
	EzSwitchMonMgr ezswitchmonmgrobj;
	ezswitchmonmgrobj.InitEzSwitchMonMgr( argv[ 0 ] );
	ezswitchmonmgrobj.ServiceRequest();
	return 1;
}

