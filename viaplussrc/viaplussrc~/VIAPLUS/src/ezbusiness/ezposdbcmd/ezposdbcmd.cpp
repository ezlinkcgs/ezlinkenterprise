#include <ezbusiness/ezposdbcmd.h>

int EzPOSDBCmd :: initPOSDBCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezposdbcmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^ezposdbcmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( dbutil.initDBUtil( "ezposdbcmd", this ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		printf("\nError in Initializing DBUtil...." );
		exit( 0 );
	}

	if( initPOSDriverUtil( this ) < 0 )
	{
		trace( "Error in Initializing POSDriverUtil...." );
		printf("\nError in Initializing POSDriverUtil...." );
		exit( 0 );
	}

	if( LoadPOSMCCInfo() < 0 )
	{
		trace( "Error in Loading  POSMCCInfo...." );
		printf("\nError in Loading  POSMCCInfo...." );
		exit( 0 );
	}

	if( LoadPOSMerchantTypeInfo() < 0 )
	{
		trace( "Error in Loading  POSMerchantTypeInfo...." );
		printf("\nError in Loading  POSMerchantTypeInfo...." );
		exit( 0 );
	}

	if( LoadPOSMerchantInfo() < 0 )
	{
		trace( "Error in Loading  POSMerchantInfo...." );
		printf("\nError in Loading  POSMerchantInfo...." );
		exit( 0 );
	}

	if( LoadPOSTerminalTypeInfo() < 0 )
	{
		trace( "Error in Loading  POSTerminalTypeInfo...." );
		printf("\nError in Loading  POSTerminalTypeInfo...." );
		exit( 0 );
	}

	if( LoadPOSTerminalInfo() < 0 )
	{
		trace( "Error in Loading  POSTerminalInfo...." );
		printf("\nError in Loading  POSTerminalInfo...." );
		exit( 0 );
	}

	if( LoadPOSStoreInfo() < 0 )
	{
		trace( "Error in Loading  POSStoreInfo...." );
		printf("\nError in Loading  POSStoreInfo...." );
		exit( 0 );
	}

	if( LoadPOSTxnInfo() < 0 )
	{
		trace( "Error in Loading  POSTxnInfo...." );
		printf("\nError in Loading  POSTxnInfo...." );
		exit( 0 );
	}

	if( LoadPOSRespCodeInfo() < 0 )
	{
		trace( "Error in Loading  POSRespCodeInfo...." );
		printf("\nError in Loading  POSRespCodeInfo...." );
		exit( 0 );
	}

	return 1;
}

int EzPOSDBCmd :: serviceAddPOSMCCInfo( int MCC )
{
	struct EzPOSMCCInfo posmccinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmccinfo_rec, 0, sizeof( struct EzPOSMCCInfo ) );
	retval = readEzPOSMCCInfo( MCC, &posmccinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MCC[%d] from EzPOSMCCInfo....OraErr[%05d]", MCC, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSMCCInfo( posmccinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSMCCInfo( int MCC )
{
	struct EzPOSMCCInfo posmccinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmccinfo_rec, 0, sizeof( struct EzPOSMCCInfo ) );
	retval = readEzPOSMCCInfo( MCC, &posmccinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MCC[%d] from EzPOSMCCInfo....OraErr[%05d]", MCC, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSMCCInfo( posmccinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSMCCInfo( int MCC )
{
	if( deletePOSMCCInfo( MCC ) < 0 )
	{
		trace("Error In Deleting MCC[%d]", MCC );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMCCInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%20s", "MCC", "DESCRIPTION" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMCCInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MCCInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMCCInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( MCCInfoShmPtr + i )->MCC != RECORD_NUMBERINIT_VAL )
			printf( "\n%10d%20s", ( MCCInfoShmPtr + i )->MCC, ( MCCInfoShmPtr + i )->Description );

		sem_buf.sem_op = 2;
		if( semop( MCCInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMCCInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMCCInfo( int MCC )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%20s", "MCC", "DESCRIPTION" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );


	for( int i = 0; i < MaxPOSMCCInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MCCInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMCCInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( MCCInfoShmPtr + i )->MCC == MCC )
		{
			printf( "\n%10d%20s", ( MCCInfoShmPtr + i )->MCC, ( MCCInfoShmPtr + i )->Description );
			sem_buf.sem_op = 2;
			if( semop( MCCInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSMCCInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}

		sem_buf.sem_op = 2;
		if( semop( MCCInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMCCInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSMerchantTypeInfo( const char *MerchantType )
{
	struct EzPOSMerchantTypeInfo posmerchanttypeinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmerchanttypeinfo_rec, 0, sizeof( struct EzPOSMerchantTypeInfo ) );
	retval = readEzPOSMerchantTypeInfo( MerchantType, &posmerchanttypeinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MerchantType[%s] from EzPOSMerchantTypeInfo....OraErr[%05d]", MerchantType, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSMerchantTypeInfo( posmerchanttypeinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSMerchantTypeInfo( const char *MerchantType )
{
	struct EzPOSMerchantTypeInfo posmerchanttypeinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmerchanttypeinfo_rec, 0, sizeof( struct EzPOSMerchantTypeInfo ) );
	retval = readEzPOSMerchantTypeInfo( MerchantType, &posmerchanttypeinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MerchantType[%s] from EzPOSMerchantTypeInfo....OraErr[%05d]", MerchantType, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSMerchantTypeInfo( posmerchanttypeinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSMerchantTypeInfo( const char *MerchantType )
{
	if( deletePOSMerchantTypeInfo( MerchantType ) < 0 )
	{
		trace("Error In Deleting MerchantType[%s]", MerchantType );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMerchantTypeInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s", "MerchantType", "DESCRIPTION" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMerchantTypeInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MerchantTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( MerchantTypeInfoShmPtr + i )->MerchantType, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%20s", ( MerchantTypeInfoShmPtr + i )->MerchantType, ( MerchantTypeInfoShmPtr + i )->Description );

		sem_buf.sem_op = 2;
		if( semop( MerchantTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMerchantTypeInfo( const char *MerchantType )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s", "MerchantType", "DESCRIPTION" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMerchantTypeInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MerchantTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( MerchantTypeInfoShmPtr + i )->MerchantType, MerchantType ) )
		{
			printf( "\n%20s%20s", ( MerchantTypeInfoShmPtr + i )->MerchantType, ( MerchantTypeInfoShmPtr + i )->Description );
			sem_buf.sem_op = 2;
			if( semop( MerchantTypeInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSMerchantTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( MerchantTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSMerchantInfo( const char *MerchantId )
{
	struct EzPOSMerchantInfo posmerchantinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmerchantinfo_rec, 0, sizeof( struct EzPOSMerchantInfo ) );
	retval = readEzPOSMerchantInfo( MerchantId, &posmerchantinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MerchantId[%s] from EzPOSMerchantInfo....OraErr[%05d]", MerchantId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSMerchantInfo( posmerchantinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSMerchantInfo( const char *MerchantId )
{
	struct EzPOSMerchantInfo posmerchantinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmerchantinfo_rec, 0, sizeof( struct EzPOSMerchantInfo ) );
	retval = readEzPOSMerchantInfo( MerchantId, &posmerchantinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MerchantId[%s] from EzPOSMerchantInfo....OraErr[%05d]", MerchantId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSMerchantInfo( posmerchantinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSMerchantInfo( const char *MerchantId )
{
	if( deletePOSMerchantInfo( MerchantId ) < 0 )
	{
		trace("Error In Deleting MerchantId[%s]", MerchantId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMerchantInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMerchantInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MerchantInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( MerchantInfoShmPtr + i )->MerchantId, RECORD_STRINGINIT_VAL ) )
		{
			printf("\n\t MerchantId-><%s>", ( MerchantInfoShmPtr + i )->MerchantId );
			printf("\n\t InstId-><%s>", ( MerchantInfoShmPtr + i )->InstId );
			printf("\n\t MerchantType-><%s>", ( MerchantInfoShmPtr + i )->MerchantType );
			printf("\n\t MerchantName-><%s>", ( MerchantInfoShmPtr + i )->MerchantName );
			printf("\n\t MCCList-><%s>", ( MerchantInfoShmPtr + i )->MCCList );
			printf("\n\t TxnList-><%s>", ( MerchantInfoShmPtr + i )->TxnList );
		}

		sem_buf.sem_op = 2;
		if( semop( MerchantInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMerchantInfo( const char *MerchantId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMerchantInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MerchantInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( MerchantInfoShmPtr + i )->MerchantId, MerchantId ) )
		{
			printf("\n\t MerchantId-><%s>", ( MerchantInfoShmPtr + i )->MerchantId );
			printf("\n\t InstId-><%s>", ( MerchantInfoShmPtr + i )->InstId );
			printf("\n\t MerchantType-><%s>", ( MerchantInfoShmPtr + i )->MerchantType );
			printf("\n\t MerchantName-><%s>", ( MerchantInfoShmPtr + i )->MerchantName );
			printf("\n\t MCCList-><%s>", ( MerchantInfoShmPtr + i )->MCCList );
			printf("\n\t TxnList-><%s>", ( MerchantInfoShmPtr + i )->TxnList );

			sem_buf.sem_op = 2;
			if( semop( MerchantInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSMerchantInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}

		sem_buf.sem_op = 2;
		if( semop( MerchantInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMerchantInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSTerminalTypeInfo( const char *TerminalType )
{
	struct EzPOSTerminalTypeInfo posterminaltypeinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posterminaltypeinfo_rec, 0, sizeof( struct EzPOSTerminalTypeInfo ) );
	retval = readEzPOSTerminalTypeInfo( TerminalType, &posterminaltypeinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading TerminalType[%s] from EzPOSTerminalTypeInfo....OraErr[%05d]", TerminalType, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSTerminalTypeInfo( posterminaltypeinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSTerminalTypeInfo( const char *TerminalType )
{
	struct EzPOSTerminalTypeInfo posterminaltypeinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posterminaltypeinfo_rec, 0, sizeof( struct EzPOSTerminalTypeInfo ) );
	retval = readEzPOSTerminalTypeInfo( TerminalType, &posterminaltypeinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading TerminalType[%s] from EzPOSTerminalTypeInfo....OraErr[%05d]", TerminalType, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSTerminalTypeInfo( posterminaltypeinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSTerminalTypeInfo( const char *TerminalType )
{
	if( deletePOSTerminalTypeInfo( TerminalType ) < 0 )
	{
		trace("Error In Deleting TerminalType[%s]", TerminalType );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSTerminalTypeInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%20s", "TerminalType", "DESCRIPTION", "TXNCODEGROUP", "RESPCODEGROUP" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSTerminalTypeInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TerminalTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( TerminalTypeInfoShmPtr + i )->TerminalType, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%20s%20s%20s", ( TerminalTypeInfoShmPtr + i )->TerminalType, ( TerminalTypeInfoShmPtr + i )->Description, ( TerminalTypeInfoShmPtr + i )->TxnCodeGroupId, ( TerminalTypeInfoShmPtr + i )->RespCodeGroupId );

		sem_buf.sem_op = 2;
		if( semop( TerminalTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSTerminalTypeInfo( const char *TerminalType )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%20s", "TerminalType", "DESCRIPTION", "TXNCODEGROUP", "RESPCODEGROUP" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSTerminalTypeInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TerminalTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( TerminalTypeInfoShmPtr + i )->TerminalType, TerminalType ) )
		{
			printf( "\n%20s%20s%20s%20s", ( TerminalTypeInfoShmPtr + i )->TerminalType, ( TerminalTypeInfoShmPtr + i )->Description, ( TerminalTypeInfoShmPtr + i )->TxnCodeGroupId, ( TerminalTypeInfoShmPtr + i )->RespCodeGroupId );
			sem_buf.sem_op = 2;
			if( semop( TerminalTypeInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSTerminalTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}

		sem_buf.sem_op = 2;
		if( semop( TerminalTypeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalTypeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSTerminalInfo( const char *TerminalId )
{
	struct EzPOSTerminalInfo posterminalinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posterminalinfo_rec, 0, sizeof( struct EzPOSTerminalInfo ) );
	retval = readEzPOSTerminalInfo( TerminalId, &posterminalinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading TerminalId[%s] from EzPOSTerminalInfo....OraErr[%05d]", TerminalId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSTerminalInfo( posterminalinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSTerminalInfo( const char *TerminalId )
{
	struct EzPOSTerminalInfo posterminalinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posterminalinfo_rec, 0, sizeof( struct EzPOSTerminalInfo ) );
	retval = readEzPOSTerminalInfo( TerminalId, &posterminalinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading TerminalId[%s] from EzPOSTerminalInfo....OraErr[%05d]", TerminalId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSTerminalInfo( posterminalinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSTerminalInfo( const char *TerminalId )
{
	if( deletePOSTerminalInfo( TerminalId ) < 0 )
	{
		trace("Error In Deleting TerminalId[%s]", TerminalId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSTerminalInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSTerminalInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TerminalInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( TerminalInfoShmPtr + i )->POSId, RECORD_STRINGINIT_VAL ) )
		{
			printf("\n\t POSId-><%s>", ( TerminalInfoShmPtr + i )->POSId );
			printf("\n\t InstId-><%s>", ( TerminalInfoShmPtr + i )->InstId );
			printf("\n\t TerminalId-><%s>", ( TerminalInfoShmPtr + i )->TerminalId );
			printf("\n\t MerchantId-><%s>", ( TerminalInfoShmPtr + i )->MerchantId );
			printf("\n\t MCC-><%d>", ( TerminalInfoShmPtr + i )->MCC );
			printf("\n\t TermMasterKey-><%s>", ( TerminalInfoShmPtr + i )->TermMasterKey );
			printf("\n\t TermPINKey-><%s>", ( TerminalInfoShmPtr + i )->TermPINKey );
			printf("\n\t TermMACKey-><%s>", ( TerminalInfoShmPtr + i )->TermMACKey );
			printf("\n\t TerminalLocation-><%s>", ( TerminalInfoShmPtr + i )->TerminalLocation );
			printf("\n\t TerminalType-><%s>", ( TerminalInfoShmPtr + i )->TerminalType );
			printf("\n\t TerminalStatus-><%c>", ( TerminalInfoShmPtr + i )->TerminalStatus );
			printf("\n\t StoreId-><%s>", ( TerminalInfoShmPtr + i )->StoreId );
			printf("\n\t AcquirerCode-><%s>", ( TerminalInfoShmPtr + i )->AcquirerCode );
			printf("\n\t CurrencyCode-><%d>", ( TerminalInfoShmPtr + i )->CurrencyCode );
			printf("\n\t CountryCode-><%d>", ( TerminalInfoShmPtr + i )->CountryCode );
			printf("\n\t PinCapCode-><%d>", ( TerminalInfoShmPtr + i )->PinCapCode );
			printf("\n\t BatchId-><%s>", ( TerminalInfoShmPtr + i )->BatchId );
		}
		sem_buf.sem_op = 2;
		if( semop( TerminalInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSTerminalInfo( const char *TerminalId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSTerminalInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TerminalInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( TerminalInfoShmPtr + i )->POSId, TerminalId ) )
		{
			printf("\n\t POSId-><%s>", ( TerminalInfoShmPtr + i )->POSId );
			printf("\n\t InstId-><%s>", ( TerminalInfoShmPtr + i )->InstId );
			printf("\n\t TerminalId-><%s>", ( TerminalInfoShmPtr + i )->TerminalId );
			printf("\n\t MerchantId-><%s>", ( TerminalInfoShmPtr + i )->MerchantId );
			printf("\n\t MCC-><%d>", ( TerminalInfoShmPtr + i )->MCC );
			printf("\n\t TermMasterKey-><%s>", ( TerminalInfoShmPtr + i )->TermMasterKey );
			printf("\n\t TermPINKey-><%s>", ( TerminalInfoShmPtr + i )->TermPINKey );
			printf("\n\t TermMACKey-><%s>", ( TerminalInfoShmPtr + i )->TermMACKey );
			printf("\n\t TerminalLocation-><%s>", ( TerminalInfoShmPtr + i )->TerminalLocation );
			printf("\n\t TerminalType-><%s>", ( TerminalInfoShmPtr + i )->TerminalType );
			printf("\n\t TerminalStatus-><%c>", ( TerminalInfoShmPtr + i )->TerminalStatus );
			printf("\n\t StoreId-><%s>", ( TerminalInfoShmPtr + i )->StoreId );
			printf("\n\t AcquirerCode-><%s>", ( TerminalInfoShmPtr + i )->AcquirerCode );
			printf("\n\t CurrencyCode-><%d>", ( TerminalInfoShmPtr + i )->CurrencyCode );
			printf("\n\t CountryCode-><%d>", ( TerminalInfoShmPtr + i )->CountryCode );
			printf("\n\t PinCapCode-><%d>", ( TerminalInfoShmPtr + i )->PinCapCode );
			printf("\n\t BatchId-><%s>", ( TerminalInfoShmPtr + i )->BatchId );

			sem_buf.sem_op = 2;
			if( semop( TerminalInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSTerminalInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TerminalInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTerminalInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSStoreInfo( const char *StoreId )
{
	struct EzPOSStoreInfo posstoreinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posstoreinfo_rec, 0, sizeof( struct EzPOSStoreInfo ) );
	retval = readEzPOSStoreInfo( StoreId, &posstoreinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading StoreId[%s] from EzPOSStoreInfo....OraErr[%05d]", StoreId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSStoreInfo( posstoreinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSStoreInfo( const char *StoreId )
{
	struct EzPOSStoreInfo posstoreinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posstoreinfo_rec, 0, sizeof( struct EzPOSStoreInfo ) );
	retval = readEzPOSStoreInfo( StoreId, &posstoreinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading StoreId[%s] from EzPOSStoreInfo....OraErr[%05d]", StoreId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSStoreInfo( posstoreinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSStoreInfo( const char *StoreId )
{
	if( deletePOSStoreInfo( StoreId ) < 0 )
	{
		trace("Error In Deleting StoreId[%s]", StoreId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSStoreInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSStoreInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( StoreInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSStoreInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( StoreInfoShmPtr + i )->StoreId, RECORD_STRINGINIT_VAL ) )
		{
			printf("\n\t StoreId-><%s>", ( StoreInfoShmPtr + i )->StoreId );
			printf("\n\t InstId-><%s>", ( StoreInfoShmPtr + i )->InstId );
			printf("\n\t MerchantId-><%s>", ( StoreInfoShmPtr + i )->MerchantId );
			printf("\n\t StoreName-><%s>", ( StoreInfoShmPtr + i )->StoreName );
		}
		sem_buf.sem_op = 2;
		if( semop( StoreInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSStoreInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSStoreInfo( const char *StoreId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSStoreInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( StoreInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSStoreInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( StoreInfoShmPtr + i )->StoreId, StoreId ) )
		{
			printf("\n\t StoreId-><%s>", ( StoreInfoShmPtr + i )->StoreId );
			printf("\n\t InstId-><%s>", ( StoreInfoShmPtr + i )->InstId );
			printf("\n\t MerchantId-><%s>", ( StoreInfoShmPtr + i )->MerchantId );
			printf("\n\t StoreName-><%s>", ( StoreInfoShmPtr + i )->StoreName );
			sem_buf.sem_op = 2;
			if( semop( StoreInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSStoreInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( StoreInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSStoreInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSTxnInfo( const char *TxnCodeGroupId )
{
	struct EzPOSTxnInfo postxninfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &postxninfo_rec, 0, sizeof( struct EzPOSTxnInfo ) );
	retval = readEzPOSTxnInfo( TxnCodeGroupId, &postxninfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading TxnCodeGroupId[%s] from EzPOSTxnInfo....OraErr[%05d]", TxnCodeGroupId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSTxnInfo( postxninfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSTxnInfo( const char *TxnCodeGroupId )
{
	struct EzPOSTxnInfo postxninfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &postxninfo_rec, 0, sizeof( struct EzPOSTxnInfo ) );
	retval = readEzPOSTxnInfo( TxnCodeGroupId, &postxninfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading TxnCodeGroupId[%s] from EzPOSTxnInfo....OraErr[%05d]", TxnCodeGroupId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSTxnInfo( postxninfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSTxnInfo( const char *TxnCodeGroupId )
{
	if( deletePOSTxnInfo( TxnCodeGroupId ) < 0 )
	{
		trace("Error In Deleting TxnCodeGroupId[%s]", TxnCodeGroupId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSTxnInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s", "TXNGROUPID", "TXNCODELIST" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSTxnInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTxnInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( TxnInfoShmPtr + i )->TxnCodeGroupId, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%20s", ( TxnInfoShmPtr + i )->TxnCodeGroupId, ( TxnInfoShmPtr + i )->TxnCodeList );

		sem_buf.sem_op = 2;
		if( semop( TxnInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTxnInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSTxnInfo( const char *TxnCodeGroupId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s", "TXNGROUPID", "TXNCODELIST" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSTxnInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTxnInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( TxnInfoShmPtr + i )->TxnCodeGroupId, TxnCodeGroupId ) )
		{
			printf( "\n%20s%20s", ( TxnInfoShmPtr + i )->TxnCodeGroupId, ( TxnInfoShmPtr + i )->TxnCodeList );
			sem_buf.sem_op = 2;
			if( semop( TxnInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSTxnInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSTxnInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSRespCodeInfo( const char *RecordId )
{
	struct EzPOSRespCodeInfo posrespcodeinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posrespcodeinfo_rec, 0, sizeof( struct EzPOSRespCodeInfo ) );
	retval = readEzPOSRespCodeInfo( RecordId, &posrespcodeinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RecordId[%s] from EzPOSRespCodeInfo....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSRespCodeInfo( posrespcodeinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSRespCodeInfo( const char *RecordId )
{
	struct EzPOSRespCodeInfo posrespcodeinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posrespcodeinfo_rec, 0, sizeof( struct EzPOSRespCodeInfo ) );
	retval = readEzPOSRespCodeInfo( RecordId, &posrespcodeinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RecordId[%s] from EzPOSRespCodeInfo....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSRespCodeInfo( posrespcodeinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSRespCodeInfo( const char *RecordId )
{
	if( deletePOSRespCodeInfo( RecordId ) < 0 )
	{
		trace("Error In Deleting RecordId[%s]", RecordId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSRespCodeInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%10s%10s", "RECORDID", "RESPCODEGROUPID", "RESPCODE", "POSRESPCODE" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSRespCodeInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( RespCodeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRespCodeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( RespCodeInfoShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%20s%10d%10d", ( RespCodeInfoShmPtr + i )->RecordId, ( RespCodeInfoShmPtr + i )->RespCodeGroupId, ( RespCodeInfoShmPtr + i )->RespCode, ( RespCodeInfoShmPtr + i )->POSRespCode );

		sem_buf.sem_op = 2;
		if( semop( RespCodeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRespCodeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSRespCodeInfo( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%10s%10s", "RECORDID", "RESPCODEGROUPID", "RESPCODE", "POSRESPCODE" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSRespCodeInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( RespCodeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRespCodeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( RespCodeInfoShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%20s%20s%10d%10d", ( RespCodeInfoShmPtr + i )->RecordId, ( RespCodeInfoShmPtr + i )->RespCodeGroupId, ( RespCodeInfoShmPtr + i )->RespCode, ( RespCodeInfoShmPtr + i )->POSRespCode );
			sem_buf.sem_op = 2;
			if( semop( RespCodeInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSRespCodeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( RespCodeInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRespCodeInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSInBoundProperty( const char *RecordId )
{
	struct EzPOSInBoundProperty posinboundproperty_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posinboundproperty_rec, 0, sizeof( struct EzPOSInBoundProperty ) );
	retval = readEzPOSInBoundProperty( RecordId, &posinboundproperty_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RecordId[%s] from EzPOSInBoundProperty....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSInBoundProperty( posinboundproperty_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSInBoundProperty( const char *RecordId )
{
	struct EzPOSInBoundProperty posinboundproperty_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posinboundproperty_rec, 0, sizeof( struct EzPOSInBoundProperty ) );
	retval = readEzPOSInBoundProperty( RecordId, &posinboundproperty_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RecordId[%s] from EzPOSInBoundProperty....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSInBoundProperty( posinboundproperty_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSInBoundProperty( const char *RecordId )
{
	if( deletePOSInBoundProperty( RecordId ) < 0 )
	{
		trace("Error In Deleting RecordId[%s] from POSInBoundProperty Memory", RecordId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSInBoundProperty()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%10s%10s%10s%10s", "RECORDID", "MSGTYPE", "TXNCODE", "MSGFLAG", "MSGPROCESSFLAG" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSInBoundProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSInBoundPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSInBoundProperty...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( POSInBoundPropertyShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%10s%10s%10c%10c", ( POSInBoundPropertyShmPtr + i )->RecordId, ( POSInBoundPropertyShmPtr + i )->MsgType, ( POSInBoundPropertyShmPtr + i )->TxnCode, ( POSInBoundPropertyShmPtr + i )->MsgFlag, ( POSInBoundPropertyShmPtr + i )->MsgProcessFlag );

		sem_buf.sem_op = 2;
		if( semop( POSInBoundPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSInBoundProperty...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSInBoundProperty( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%10s%10s%10s%10s", "RECORDID", "MSGTYPE", "TXNCODE", "MSGFLAG", "MSGPROCESSFLAG" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSInBoundProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSInBoundPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSInBoundProperty...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( POSInBoundPropertyShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%20s%10s%10s%10c%10c", ( POSInBoundPropertyShmPtr + i )->RecordId, ( POSInBoundPropertyShmPtr + i )->MsgType, ( POSInBoundPropertyShmPtr + i )->TxnCode, ( POSInBoundPropertyShmPtr + i )->MsgFlag, ( POSInBoundPropertyShmPtr + i )->MsgProcessFlag );
			sem_buf.sem_op = 2;
			if( semop( POSInBoundPropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSInBoundProperty...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( POSInBoundPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSInBoundProperty...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSRouteSelect( const char *RouteSelectId )
{
	struct EzPOSRouteSelect posrouteselect_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posrouteselect_rec, 0, sizeof( struct EzPOSRouteSelect ) );
	retval = readEzPOSRouteSelect( RouteSelectId, &posrouteselect_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RouteSelectId[%s] from EzPOSRouteSelect....OraErr[%05d]", RouteSelectId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSRouteSelect( posrouteselect_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSRouteSelect( const char *RouteSelectId )
{
	struct EzPOSRouteSelect posrouteselect_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posrouteselect_rec, 0, sizeof( struct EzPOSRouteSelect ) );
	retval = readEzPOSRouteSelect( RouteSelectId, &posrouteselect_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RouteSelectId[%s] from EzPOSRouteSelect....OraErr[%05d]", RouteSelectId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSRouteSelect( posrouteselect_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSRouteSelect( const char *RouteSelectId )
{
	if( deletePOSRouteSelect( RouteSelectId ) < 0 )
	{
		trace("Error In Deleting RouteSelectId[%s] from POSRouteSelect Memory", RouteSelectId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSRouteSelect()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%10s", "ROUTESELECTID", "CHANNELNAME", "MSGTRANSLATEID", "LOGFLAG" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSRouteSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteSelect...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( POSRouteSelectShmPtr + i )->RouteSelectId, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%20s%20s%10c", ( POSRouteSelectShmPtr + i )->RouteSelectId, ( POSRouteSelectShmPtr + i )->ChannelName, ( POSRouteSelectShmPtr + i )->MsgTranslateId, ( POSRouteSelectShmPtr + i )->LogFlag );

		sem_buf.sem_op = 2;
		if( semop( POSRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteSelect...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSRouteSelect( const char *RouteSelectId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%10s", "ROUTESELECTID", "CHANNELNAME", "MSGTRANSLATEID", "LOGFLAG" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSRouteSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteSelect...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( POSRouteSelectShmPtr + i )->RouteSelectId, RouteSelectId ) )
		{
			printf( "\n%20s%20s%20s%10c", ( POSRouteSelectShmPtr + i )->RouteSelectId, ( POSRouteSelectShmPtr + i )->ChannelName, ( POSRouteSelectShmPtr + i )->MsgTranslateId, ( POSRouteSelectShmPtr + i )->LogFlag );
			sem_buf.sem_op = 2;
			if( semop( POSRouteSelectSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSRouteSelect...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( POSRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteSelect...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSMsgTranslate( const char *MsgTranslateId )
{
	struct EzPOSMsgTranslate posmsgtranslate_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmsgtranslate_rec, 0, sizeof( struct EzPOSMsgTranslate ) );
	retval = readEzPOSMsgTranslate( MsgTranslateId, &posmsgtranslate_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MsgTranslateId[%s] from EzPOSMsgTranslate....OraErr[%05d]", MsgTranslateId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSMsgTranslate( posmsgtranslate_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSMsgTranslate( const char *MsgTranslateId )
{
	struct EzPOSMsgTranslate posmsgtranslate_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posmsgtranslate_rec, 0, sizeof( struct EzPOSMsgTranslate ) );
	retval = readEzPOSMsgTranslate( MsgTranslateId, &posmsgtranslate_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading MsgTranslateId[%s] from EzPOSMsgTranslate....OraErr[%05d]", MsgTranslateId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSMsgTranslate( posmsgtranslate_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSMsgTranslate( const char *MsgTranslateId )
{
	if( deletePOSMsgTranslate( MsgTranslateId ) < 0 )
	{
		trace("Error In Deleting MsgTranslateId[%s] from POSMsgTranslate Memory", MsgTranslateId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMsgTranslate()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%s", "MSGTRANSLATEID", "TRANSLATEDESC" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMsgTranslate; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSMsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMsgTranslate...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( POSMsgTranslateShmPtr + i )->MsgTranslateId, RECORD_STRINGINIT_VAL ) )
			printf( "\n%20s%s", ( POSMsgTranslateShmPtr + i )->MsgTranslateId, ( POSMsgTranslateShmPtr + i )->TranslateDesc );

		sem_buf.sem_op = 2;
		if( semop( POSMsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMsgTranslate...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSMsgTranslate( const char *MsgTranslateId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%s", "MSGTRANSLATEID", "TRANSLATEDESC" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSMsgTranslate; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSMsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMsgTranslate...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( POSMsgTranslateShmPtr + i )->MsgTranslateId, MsgTranslateId ) )
		{
			printf( "\n%20s%s", ( POSMsgTranslateShmPtr + i )->MsgTranslateId, ( POSMsgTranslateShmPtr + i )->TranslateDesc );
			sem_buf.sem_op = 2;
			if( semop( POSMsgTranslateSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSMsgTranslate...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( POSMsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSMsgTranslate...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceAddPOSRouteInfo( const char *RecordId )
{
	struct EzPOSRouteInfo posrouteinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posrouteinfo_rec, 0, sizeof( struct EzPOSRouteInfo ) );
	retval = readEzPOSRouteInfo( RecordId, &posrouteinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RecordId[%s] from EzPOSRouteInfo....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( addPOSRouteInfo( posrouteinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceUpdatePOSRouteInfo( const char *RecordId )
{
	struct EzPOSRouteInfo posrouteinfo_rec;
	int retval;
	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &posrouteinfo_rec, 0, sizeof( struct EzPOSRouteInfo ) );
	retval = readEzPOSRouteInfo( RecordId, &posrouteinfo_rec );
	if( retval != 0 )
	{
		trace( "Error in Reading RecordId[%s] from EzPOSRouteInfo....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	if( updatePOSRouteInfo( posrouteinfo_rec ) < 0 )
	{
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	return 1;
}

int EzPOSDBCmd :: serviceDeletePOSRouteInfo( const char *RecordId )
{
	if( deletePOSRouteInfo( RecordId ) < 0 )
	{
		trace("Error In Deleting RecordId[%s] from POSRouteInfo Memory", RecordId );
		return -1;
	}
	return 1;
}

int EzPOSDBCmd :: serviceListPOSRouteInfo()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSRouteInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( POSRouteInfoShmPtr + i )->RecordId, RECORD_STRINGINIT_VAL ) )
		{
			printf("\n\t RecordId-><%s>", ( POSRouteInfoShmPtr + i )->RecordId );
			printf("\n\t InstId-><%s>", ( POSRouteInfoShmPtr + i )->InstId );
			printf("\n\t TerminalType-><%s>", ( POSRouteInfoShmPtr + i )->TerminalType );
			printf("\n\t MsgType-><%s>", ( POSRouteInfoShmPtr + i )->MsgType );
			printf("\n\t TxnCode-><%s>", ( POSRouteInfoShmPtr + i )->TxnCode );
			printf("\n\t RespCode-><%s>", ( POSRouteInfoShmPtr + i )->RespCode );
			printf("\n\t RouteExp1-><%s>", ( POSRouteInfoShmPtr + i )->RouteExp1 );
			printf("\n\t RouteExpPriority1-><%d>", ( POSRouteInfoShmPtr + i )->RouteExpPriority1 );
			printf("\n\t RouteExp2-><%s>", ( POSRouteInfoShmPtr + i )->RouteExp2 );
			printf("\n\t RouteExpPriority2-><%d>", ( POSRouteInfoShmPtr + i )->RouteExpPriority2 );
			printf("\n\t ChannelName-><%s>", ( POSRouteInfoShmPtr + i )->ChannelName );
			printf("\n\t RouteSelectList-><%s>", ( POSRouteInfoShmPtr + i )->RouteSelectList );
			printf("\n\t DebugFlag-><%c>", ( POSRouteInfoShmPtr + i )->DebugFlag );
		}

		sem_buf.sem_op = 2;
		if( semop( POSRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: serviceListPOSRouteInfo( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxPOSRouteInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( POSRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( POSRouteInfoShmPtr + i )->RecordId, RecordId ) )
		{
			printf("\n\t RecordId-><%s>", ( POSRouteInfoShmPtr + i )->RecordId );
			printf("\n\t InstId-><%s>", ( POSRouteInfoShmPtr + i )->InstId );
			printf("\n\t TerminalType-><%s>", ( POSRouteInfoShmPtr + i )->TerminalType );
			printf("\n\t MsgType-><%s>", ( POSRouteInfoShmPtr + i )->MsgType );
			printf("\n\t TxnCode-><%s>", ( POSRouteInfoShmPtr + i )->TxnCode );
			printf("\n\t RespCode-><%s>", ( POSRouteInfoShmPtr + i )->RespCode );
			printf("\n\t RouteExp1-><%s>", ( POSRouteInfoShmPtr + i )->RouteExp1 );
			printf("\n\t RouteExpPriority1-><%d>", ( POSRouteInfoShmPtr + i )->RouteExpPriority1 );
			printf("\n\t RouteExp2-><%s>", ( POSRouteInfoShmPtr + i )->RouteExp2 );
			printf("\n\t RouteExpPriority2-><%d>", ( POSRouteInfoShmPtr + i )->RouteExpPriority2 );
			printf("\n\t ChannelName-><%s>", ( POSRouteInfoShmPtr + i )->ChannelName );
			printf("\n\t RouteSelectList-><%s>", ( POSRouteInfoShmPtr + i )->RouteSelectList );
			printf("\n\t DebugFlag-><%c>", ( POSRouteInfoShmPtr + i )->DebugFlag );
			sem_buf.sem_op = 2;
			if( semop( POSRouteInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on POSRouteInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( POSRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on POSRouteInfo...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	return 1;
}

int EzPOSDBCmd :: servicePOSDBCmd( int argc, char **argv )
{
	char command[ 255 ], InstId[ 50 ];

	while( 1 )
	{
		printf( "\nezposdbcmd>" );
		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;
		if( !strcasecmp( command, "MCC" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSMCCInfo( atoi( command ) ) < 0 )
				{
					printf("\n *****Error In Adding MCC[%s] To POSMCCInfo Memory*****", command );
					trace("*****Error In Adding MCC[%s] To POSMCCInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSMCCInfo( atoi( command ) ) < 0 )
				{
					printf("\n *****Error In Updating MCC[%s] To POSMCCInfo Memory*****", command );
					trace("*****Error In Updating MCC[%s] To POSMCCInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSMCCInfo( atoi( command ) ) < 0 )
				{
					printf("\n *****Error In Deleting MCC[%s] To POSMCCInfo Memory*****", command );
					trace("*****Error In Deleting MCC[%s] To POSMCCInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSMCCInfo();
				else
					serviceListPOSMCCInfo( atoi( command ) );
			}
		}
		else if ( !strcasecmp( command, "MerchantType" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSMerchantTypeInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding MerchantType[%s] To POSMerchantTypeInfo Memory*****", command );
					trace( "*****Error In Adding MerchantType[%s] To POSMerchantTypeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSMerchantTypeInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating MerchantType[%s] To POSMerchantTypeInfo Memory*****", command );
					trace( "*****Error In Updating MerchantType[%s] To POSMerchantTypeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSMerchantTypeInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting MerchantType[%s] From POSMerchantTypeInfo Memory*****", command );
					trace( "*****Error In Deleting MerchantType[%s] From POSMerchantTypeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSMerchantTypeInfo();
				else
					serviceListPOSMerchantTypeInfo( command );
			}
		}
		else if ( !strcasecmp( command, "Merchant" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSMerchantInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding MerchantId[%s] To POSMerchantInfo Memory*****", command );
					trace( "*****Error In Adding MerchantId[%s] To POSMerchantInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSMerchantInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating MerchantId[%s] To POSMerchantInfo Memory*****", command );
					trace( "*****Error In Updating MerchantId[%s] To POSMerchantInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSMerchantInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting MerchantId[%s] From POSMerchantInfo Memory*****", command );
					trace( "*****Error In Deleting MerchantId[%s] From POSMerchantInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSMerchantInfo();
				else
					serviceListPOSMerchantInfo( command );
			}
		}
		else if ( !strcasecmp( command, "TerminalType" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSTerminalTypeInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding TerminalType[%s] To POSTerminalTypeInfo Memory*****", command );
					trace( "*****Error In Adding TerminalType[%s] To POSTerminalTypeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSTerminalTypeInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating TerminalType[%s] To POSTerminalTypeInfo Memory*****", command );
					trace( "*****Error In Updating TerminalType[%s] To POSTerminalTypeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSTerminalTypeInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting TerminalType[%s] From POSTerminalTypeInfo Memory*****", command );
					trace( "*****Error In Deleting TerminalType[%s] From POSTerminalTypeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSTerminalTypeInfo();
				else
					serviceListPOSTerminalTypeInfo( command );
			}
		}
		else if ( !strcasecmp( command, "Terminal" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSTerminalInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding Terminal[%s] To POSTerminalInfo Memory*****", command );
					trace( "*****Error In Adding Terminal[%s] To POSTerminalInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSTerminalInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating Terminal[%s] To POSTerminalInfo Memory*****", command );
					trace( "*****Error In Updating Terminal[%s] To POSTerminalInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSTerminalInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting Terminal[%s] From POSTerminalInfo Memory*****", command );
					trace( "*****Error In Deleting Terminal[%s] From POSTerminalInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSTerminalInfo();
				else
					serviceListPOSTerminalInfo( command );
			}
		}
		else if ( !strcasecmp( command, "Store" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSStoreInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding Store[%s] To POSStoreInfo Memory*****", command );
					trace( "*****Error In Adding Store[%s] To POSStoreInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSStoreInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating Store[%s] To POSStoreInfo Memory*****", command );
					trace( "*****Error In Updating Store[%s] To POSStoreInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSStoreInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting Store[%s] From POSStoreInfo Memory*****", command );
					trace( "*****Error In Deleting Store[%s] From POSStoreInfo Memory*****", command );
				}
			}
		}
		else if ( !strcasecmp( command, "TxnInfo" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSTxnInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding TxnCodeGroupId[%s] To POSTxnInfo Memory*****", command );
					trace( "*****Error In Adding TxnCodeGroupId[%s] To POSTxnInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSTxnInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating TxnCodeGroupId[%s] To POSTxnInfo Memory*****", command );
					trace( "*****Error In Updating TxnCodeGroupId[%s] To POSTxnInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSTxnInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting TxnCodeGroupId[%s] From POSTxnInfo Memory*****", command );
					trace( "*****Error In Deleting TxnCodeGroupId[%s] From POSTxnInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSTxnInfo();
				else
					serviceListPOSTxnInfo( command );
			}
		}
		else if ( !strcasecmp( command, "RespCodeInfo" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSRespCodeInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordId[%s] To POSRespCodeInfo Memory*****", command );
					trace( "*****Error In Adding RecordId[%s] To POSRespCodeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSRespCodeInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating RecordId[%s] To POSRespCodeInfo Memory*****", command );
					trace( "*****Error In Updating RecordId[%s] To POSRespCodeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSRespCodeInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordId[%s] From POSRespCodeInfo Memory*****", command );
					trace( "*****Error In Deleting RecordId[%s] From POSRespCodeInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSRespCodeInfo();
				else
					serviceListPOSRespCodeInfo( command );
			}
		}
		else if ( !strcasecmp( command, "InBoundProperty" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSInBoundProperty( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordId[%s] To POSInBoundProperty Memory*****", command );
					trace( "*****Error In Adding RecordId[%s] To POSInBoundProperty Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSInBoundProperty( command ) < 0 )
				{
					printf("\n *****Error In Updating RecordId[%s] To POSInBoundProperty Memory*****", command );
					trace( "*****Error In Updating RecordId[%s] To POSInBoundProperty Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSInBoundProperty( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordId[%s] From POSInBoundProperty Memory*****", command );
					trace( "*****Error In Deleting RecordId[%s] From POSInBoundProperty Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSInBoundProperty();
				else
					serviceListPOSInBoundProperty( command );
			}
		}
		else if ( !strcasecmp( command, "RouteInfo" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSRouteInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordId[%s] To POSRouteInfo Memory*****", command );
					trace( "*****Error In Adding RecordId[%s] To POSRouteInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSRouteInfo( command ) < 0 )
				{
					printf("\n *****Error In Updating RecordId[%s] To POSRouteInfo Memory*****", command );
					trace( "*****Error In Updating RecordId[%s] To POSRouteInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSRouteInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordId[%s] From POSRouteInfo Memory*****", command );
					trace( "*****Error In Deleting RecordId[%s] From POSRouteInfo Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSRouteInfo();
				else
					serviceListPOSRouteInfo( command );
			}
		}
		else if ( !strcasecmp( command, "RouteSelect" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSRouteSelect( command ) < 0 )
				{
					printf("\n *****Error In Adding RouteSelectId[%s] To POSRouteSelect Memory*****", command );
					trace( "*****Error In Adding RouteSelectId[%s] To POSRouteSelect Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSRouteSelect( command ) < 0 )
				{
					printf("\n *****Error In Updating RouteSelectId[%s] To POSRouteSelect Memory*****", command );
					trace( "*****Error In Updating RouteSelectId[%s] To POSRouteSelect Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSRouteSelect( command ) < 0 )
				{
					printf("\n *****Error In Deleting RouteSelectId[%s] From POSRouteSelect Memory*****", command );
					trace( "*****Error In Deleting RouteSelectId[%s] From POSRouteSelect Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSRouteSelect();
				else
					serviceListPOSRouteSelect( command );
			}
		}
		else if ( !strcasecmp( command, "MsgTranslate" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "add" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceAddPOSMsgTranslate( command ) < 0 )
				{
					printf("\n *****Error In Adding MsgTranslateId[%s] To POSMsgTranslate Memory*****", command );
					trace( "*****Error In Adding MsgTranslateId[%s] To POSMsgTranslate Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "update" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceUpdatePOSMsgTranslate( command ) < 0 )
				{
					printf("\n *****Error In Updating MsgTranslateId[%s] To POSMsgTranslate Memory*****", command );
					trace( "*****Error In Updating MsgTranslateId[%s] To POSMsgTranslate Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "delete" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				if( serviceDeletePOSMsgTranslate( command ) < 0 )
				{
					printf("\n *****Error In Deleting MsgTranslateId[%s] From POSMsgTranslate Memory*****", command );
					trace( "*****Error In Deleting MsgTranslateId[%s] From POSMsgTranslate Memory*****", command );
				}
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
					serviceListPOSMsgTranslate();
				else
					serviceListPOSMsgTranslate( command );
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <MCCInfo> <Add> <MCC>" );
			printf("\n <MCCInfo> <Update> <MCC>" );
			printf("\n <MCCInfo> <Delete> <MCC>" );
			printf("\n <MCCInfo> <List> <MCC>" );
			printf("\n <MCCInfo> <List>" );
			printf("\n <MerchantType> <Add> <MerchantTypeId>" );
			printf("\n <MerchantType> <Update> <MerchantTypeId>" );
			printf("\n <MerchantType> <Delete> <MerchantTypeId>" );
			printf("\n <MerchantType> <List> <MerchantTypeId>" );
			printf("\n <MerchantType> <List>" );
			printf("\n <Merchant> <Add> <MerchantId>" );
			printf("\n <Merchant> <Update> <MerchantId>" );
			printf("\n <Merchant> <Delete> <MerchantId>" );
			printf("\n <Merchant> <List> <MerchantId>" );
			printf("\n <Merchant> <List>" );
			printf("\n <TerminalType> <Add> <TerminalTypeId>" );
			printf("\n <TerminalType> <Update> <TerminalTypeId>" );
			printf("\n <TerminalType> <Delete> <TerminalTypeId>" );
			printf("\n <TerminalType> <List> <TerminalTypeId>" );
			printf("\n <TerminalType> <List>" );
			printf("\n <Terminal> <Add> <TerminalId>" );
			printf("\n <Terminal> <Update> <TerminalId>" );
			printf("\n <Terminal> <Delete> <TerminalId>" );
			printf("\n <Terminal> <List> <TerminalId>" );
			printf("\n <Terminal> <List>" );
			printf("\n <TxnInfo> <Add> <TxnGroupId>" );
			printf("\n <TxnInfo> <Update> <TxnGroupId>" );
			printf("\n <TxnInfo> <Delete> <TxnGroupId>" );
			printf("\n <TxnInfo> <List> <TxnGroupId>" );
			printf("\n <TxnInfo> <List>" );
			printf("\n <RespCodeInfo> <Add> <RecordId>" );
			printf("\n <RespCodeInfo> <Update> <RecordId>" );
			printf("\n <RespCodeInfo> <Delete> <RecordId>" );
			printf("\n <RespCodeInfo> <List> <RecordId>" );
			printf("\n <RespCodeInfo> <List>" );
			printf("\n <InBoundProperty> <Add> <RecordId>" );
			printf("\n <InBoundProperty> <Update> <RecordId>" );
			printf("\n <InBoundProperty> <Delete> <RecordId>" );
			printf("\n <InBoundProperty> <List> <RecordId>" );
			printf("\n <InBoundProperty> <List>" );
			printf("\n <RouteInfo> <Add> <RecordId>" );
			printf("\n <RouteInfo> <Update> <RecordId>" );
			printf("\n <RouteInfo> <Delete> <RecordId>" );
			printf("\n <RouteInfo> <List> <RecordId>" );
			printf("\n <RouteInfo> <List>" );
			printf("\n <RouteSelect> <Add> <RouteSelectId>" );
			printf("\n <RouteSelect> <Update> <RouteSelectId>" );
			printf("\n <RouteSelect> <Delete> <RouteSelectId>" );
			printf("\n <RouteSelect> <List> <RouteSelectId>" );
			printf("\n <RouteSelect> <List>" );
			printf("\n <MsgTranslate> <Add> <MsgTranslateId>" );
			printf("\n <MsgTranslate> <Update> <MsgTranslateId>" );
			printf("\n <MsgTranslate> <Delete> <MsgTranslateId>" );
			printf("\n <MsgTranslate> <List> <MsgTranslateId>" );
			printf("\n <MsgTranslate> <List>" );
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

int main( int argc, char **argv )
{
	EzPOSDBCmd poscmdobj;
	if( poscmdobj.initPOSDBCmd( argv[ 0 ] ) < 0 )
	{
		poscmdobj.trace( "^^^^^^^^^^^^^^^ezposdbcmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		poscmdobj.closeDebug();
		exit( 0 );
	}
	poscmdobj.servicePOSDBCmd( argc, argv );
	return 1;
}




