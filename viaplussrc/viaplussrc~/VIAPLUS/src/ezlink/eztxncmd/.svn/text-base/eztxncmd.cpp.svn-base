#include <ezlink/eztxncmd.h>

int EzTxnCmd :: initTxnCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eztxncmd.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^EzTxnCmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	TxnMemoryId = LocateMemoryId( this, "TXNDBMEMORY" );

	if( TxnMemoryId < 0 )
	{
		trace( "Error in Locating TXNDBMEMORY" );
		return -1;
	}

	TxnShmid = shmget( ( key_t ) TxnMemoryId, 0, IPC_CREAT | 0666 );
	if( TxnShmid < 0 )
	{
		trace( "Error in getting Txn Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	txntable_ptr = ( struct EzTxnDBMemory * ) shmat( TxnShmid, 0, 0 );

	if( txntable_ptr == NULL )
	{
		trace( "Error in attaching Txn Shared Memory...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	TxnSemid = semget( ( key_t ) TxnMemoryId, 0, IPC_CREAT | 0666 );

	if( TxnSemid < 0 )
	{
		trace( "Error in getting Txn Semaphore...SysErr[%s]...ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;

}

int EzTxnCmd :: listTxnMemory()
{
	struct sembuf sem_buf;

	printf( "\n%16s%20s", "TableName", "TableId" );
	printf( "\n------------------------------------------------------------------" );

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnSemid, &sem_buf, 1  ) < 0 )
	{
		trace( "Error in Semop Operation on TxnMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	printf( "\n%16s%20s", "EZTXNROUTEINFO", txntable_ptr->EzTxnRouteInfoVal );
	printf( "\n%16s%20s", "EZEVENTPROPERTY", txntable_ptr->EzEventPropertyVal );
	printf( "\n%16s%20s", "EZCHANNELPROPERTY", txntable_ptr->EzChannelPropertyVal );
	printf( "\n%16s%20s", "EZMSGTYPEPROPERTY", txntable_ptr->EzMsgTypePropertyVal );
	printf( "\n%16s%20s", "EZMSGTRANSLATE", txntable_ptr->EzMsgTranslateVal );
	printf( "\n%16s%20s", "EZNETWORKPROPERTY", txntable_ptr->EzNetworkPropertyVal );
	sem_buf.sem_op = 2;
	if( semop( TxnSemid, &sem_buf, 1  ) < 0 )
	{
		trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzTxnCmd :: getDBString( char *DBString )
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
			trace( "Error in Opening File[%s]", DBSeqNoPath );
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
			trace( "Error in Opening File[%s]", DBSeqNoPath );
		else
		{
			fprintf( db_fptr, "%d", FDBSeqNo );
			fclose( db_fptr );
		}
	}
	sprintf( DBString, "%06d%06d%06d%d", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime(), DBSeqNo, getpid() );
	return 1;
}


int EzTxnCmd :: updateTxnMemory( const char *TableId )
{
	struct sembuf sem_buf;
	char DBString[ EZTXNDBFLD_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( TxnSemid, &sem_buf, 1  ) < 0 )
	{
		trace( "Error in Semop Operation on TxnMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( !strcasecmp( TableId, "EZTXNROUTEINFO" ) )
		strcpy( txntable_ptr->EzTxnRouteInfoVal, DBString );
	else if( !strcasecmp( TableId, "EZTXNROUTESELECT" ) )
		strcpy( txntable_ptr->EzTxnRouteSelectVal, DBString );
	else if( !strcasecmp( TableId, "EZEVENTPROPERTY" ) )
		strcpy( txntable_ptr->EzEventPropertyVal, DBString );
	else if( !strcasecmp( TableId, "EZCHANNELPROPERTY" ) )
		strcpy( txntable_ptr->EzChannelPropertyVal, DBString );
	else if( !strcasecmp( TableId, "EZMSGTYPEPROPERTY" ) )
		strcpy( txntable_ptr->EzMsgTypePropertyVal, DBString );
	else if( !strcasecmp( TableId, "EZMSGTRANSLATE" ) )
		strcpy( txntable_ptr->EzMsgTranslateVal, DBString );
	else if( !strcasecmp( TableId, "EZNETWORKPROPERTY" ) )
		strcpy( txntable_ptr->EzNetworkPropertyVal, DBString );
	sem_buf.sem_op = 2;
	if( semop( TxnSemid, &sem_buf, 1  ) < 0 )
	{
		trace( "Error in Semop Operation on NetworkMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}


int EzTxnCmd :: serviceTxnCmd( int argc, char **argv )
{
	char command[ 100 ], NetworkId[ 17 ];
	int NetworkStatus;

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\neztxncmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				updateTxnMemory( command );
				continue;
			}
			else if( !strcasecmp( command, "list" ) )
			{
				listTxnMemory();
				continue;
			}
			else if( !strcmp( command, "help" ) )
			{
				printf("\n <update> <ezmsgtypeproperty>");
				printf("\n <update> <ezchannelproperty>");
				printf("\n <update> <ezinstselect>");
				printf("\n <update> <eznetworkselect>");
				printf("\n <update> <eztxnrouteinfo>");
				printf("\n <update> <eztxnrouteselect>");
				printf("\n <update> <eztxnroutefld>");
				printf("\n <update> <ezmsgtranslate>");
				printf("\n <update> <eznetworkproperty>");
				printf("\n <update> <ezeventproperty>");
				printf("\n <list>");
			}
			else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
				break;
			else
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
		}
	}
	else
	{
		memset( command, 0, sizeof( command ) );
		strcpy( command, argv[ 1 ] );
		if( !strcasecmp( command, "update" ) )
		{
			memset( command, 0, sizeof( command ) );
			strcpy( command, argv[ 2 ] );
			if( strlen( command ) == 0 )
				printf("\n invaild command ..type help for more");
			else
			updateTxnMemory( command );
		}
		else if( !strcasecmp( command, "list" ) )
			listTxnMemory();
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <update> <ezmsgtypeproperty>");
			printf("\n <update> <ezchannelproperty>");
			printf("\n <update> <ezinstselect>");
			printf("\n <update> <eznetworkselect>");
			printf("\n <update> <eztxnrouteinfo>");
			printf("\n <update> <eztxnrouteselect>");
			printf("\n <update> <eztxnroutefld>");
			printf("\n <update> <ezmsgtranslate>");
			printf("\n <update> <eznetworkproperty>");
			printf("\n <update> <ezeventproperty>");
			printf("\n <list>");
		}
		else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
			return 1;
		else
		{
			printf("\n invaild command ..type help for more");
		}

	}
	return 1;
}

int main( int argc, char **argv )
{
	EzTxnCmd txncmdobj;
	if( txncmdobj.initTxnCmd( argv[ 0 ] ) < 0 )
	{
		txncmdobj.trace( "^^^^^^^^^^^^^^^EzTxnCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		txncmdobj.closeDebug();
		exit( 0 );
	}
	txncmdobj.serviceTxnCmd( argc, argv );
	return 1;
}

