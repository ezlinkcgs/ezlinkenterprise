#include <ezlink/ezinstdbcmd.h>

int EzInstDBCmd :: initInstDBCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezinstdbcmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^ezinstdbcmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	/*if( dbutil.initDBUtil( "ezinstdbcmd", this ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		printf("\nError in Initializing DBUtil...." );
		exit( 0 );
	}*/

	if ( initEzInstDbODBC( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzInstDbODBC...." );
		printf("\nError in Initializing EzInstDbODBC...." );
		exit( 0 );
	}

	if ( initInstRouteType( this ) < 0 )
	{
		trace( "Error in Initializing InstRouteType...." );
		printf("\nError in Initializing InstRouteType...." );
		exit( 0 );
	}

	if ( initInstProfile( this ) < 0 )
	{
		trace( "Error in Initializing InstProfile...." );
		printf("\nError in Initializing InstProfile...." );
		exit( 0 );
	}

	if( initEzInstSelectUtil( this ) < 0 )
	{
		trace( "Error in Initializing InstSelect...." );
		printf("\nError in Initializing InstSelect...." );
		exit( 0 );
	}

	if( initEzBINSelectUtil( this ) < 0 )
	{
		trace( "Error in Initializing BINSelect...." );
		printf("\nError in Initializing BINSelect...." );
		exit( 0 );
	}

	if( initEzNetworkSelectUtil( this ) < 0 )
	{
		trace( "Error in Initializing NetworkSelect...." );
		printf("\nError in Initializing NetworkSelect...." );
		exit( 0 );
	}

	if( initBINProfile( this ) < 0 )
	{
		trace( "Error in Initializing BINProfile...." );
		printf("\nError in Initializing BINProfile...." );
		exit( 0 );
	}

	if( initBranchProfile( this ) < 0 )
	{
		trace( "Error in Initializing BranchProfile...." );
		printf("\nError in Initializing BranchProfile...." );
		exit( 0 );
	}

	if( initAuthPropertyUtil( this ) < 0 )
	{
		trace( "Error in Initializing AuthProperty...." );
		printf("\nError in Initializing AuthProperty...." );
		exit( 0 );
	}

	if( initEzChannelPropertyUtil( this ) < 0 )
	{
		trace( "Error in Initializing ChannelProperty...." );
		printf("\nError in Initializing ChannelProperty...." );
		exit( 0 );
	}

	if( initEzEventPropertyUtil( this ) < 0 )
	{
		trace( "Error in Initializing EventProperty...." );
		printf("\nError in Initializing EventProperty...." );
		exit( 0 );
	}

	if( initEzMsgTypePropertyUtil( this ) < 0 )
	{
		trace( "Error in Initializing MsgTypeProperty...." );
		printf("\nError in Initializing MsgTypeProperty...." );
		exit( 0 );
	}

	if( initEzMsgTranslateUtil( this ) < 0 )
	{
		trace( "Error in Initializing MsgTranslate...." );
		printf("\nError in Initializing MsgTranslate...." );
		exit( 0 );
	}

	if( initEzTxnRefSelectUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnRefSelect...." );
		printf("\nError in Initializing TxnRefSelect...." );
		exit( 0 );
	}

	if( initEzTxnRouteInfoUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnRouteInfo...." );
		printf("\nError in Initializing TxnRouteInfo...." );
		exit( 0 );
	}

	if( initEzTxnRouteSelectUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnRouteSelect...." );
		printf("\nError in Initializing TxnRouteSelect...." );
		exit( 0 );
	}

	if( initInBoundMsgPropertyUtil( this ) < 0 )
	{
		trace( "Error in Initializing InBoundMsgProperty...." );
		printf("\nError in Initializing InBoundMsgProperty...." );
		exit( 0 );
	}

	if( initEzDeviceTypeMapUtil( this ) < 0 )
	{
		trace( "Error in Initializing DeviceTypeMap...." );
		printf("\nError in Initializing DeviceTypeMap...." );
		exit( 0 );
	}

	if( initTxnMsgOrderUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTxnMsgOrder...." );
		printf("\nError in Initializing EzTxnMsgOrder..." );
		exit( 0 );
	}

	if( initInstExtNtwkProfile( this ) < 0 )
	{
		trace( "Error in Initializing EzInstExtNtwkProfile...." );
		printf("\nError in Initializing EzInstExtNtwkProfile..." );
		exit( 0 );
	}

	if( initExtNtwkProfile( this ) < 0 )
	{
		trace( "Error in Initializing EzExtNtwkProfile...." );
		printf("\nError in Initializing EzExtNtwkProfile..." );
		exit( 0 );
	}

	if( initSafPropertyUtil( this ) < 0 )
	{
		trace( "Error in Initializing SafProperty...." );
		printf("\nError in Initializing SafProperty...." );
		exit( 0 );
	}

	return 1;
}

int EzInstDBCmd :: serviceAddInstRouteType( const char *InstRouteType )
{
	struct EzInstRouteTypeMemory instroutetype_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &instroutetype_rec, 0, sizeof( struct EzInstRouteTypeMemory ) );
	retval = readEzInstRouteType( InstRouteType, &instroutetype_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstRouteType[%s] from EzInstRouteType....OraErr[%05d]", InstRouteType, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addInstRouteType( InstRouteType ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateInstRouteType( const char *InstRouteType )
{
	struct EzInstRouteTypeMemory instroutetype_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &instroutetype_rec, 0, sizeof( struct EzInstRouteTypeMemory ) );
	retval = readEzInstRouteType( InstRouteType, &instroutetype_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstRouteType[%s] from EzInstRouteType....OraErr[%05d]", InstRouteType, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateInstRouteType( InstRouteType ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteInstRouteType( const char *InstRouteType )
{
	if( deleteInstRouteType( InstRouteType ) < 0 )
	{
		trace("Error In Deleting InstRouteType[%s]", InstRouteType );
		return -1;
	}
	return 1;
}

int EzInstDBCmd :: serviceListInstRouteType()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++" );
	printf( "\n%20s", "InstRouteType" );
	printf( "\n+++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < getMaxInstRouteType(); i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstRouteTypeSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstRouteTypeMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( InstRouteTypeShmPtr + i )->InstRouteType, RECORD_INIT_VAL ) )
			printf( "\n%20s", ( InstRouteTypeShmPtr + i )->InstRouteType );

		sem_buf.sem_op = 2;
		if( semop( InstRouteTypeSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListInstRouteType( const char *InstRouteType )
{
	struct sembuf sem_buf;
	printf( "\n+++++++++++++++++++++++++++++++++" );
	printf( "\n%20s", "InstRouteType" );
	printf( "\n+++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < getMaxInstRouteType(); i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstRouteTypeSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstRouteTypeMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( InstRouteTypeShmPtr + i )->InstRouteType, InstRouteType ) )
		{
			printf( "\n%20s", ( InstRouteTypeShmPtr + i )->InstRouteType );
			sem_buf.sem_op = 2;
			if( semop( InstRouteTypeSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on InstRouteTypeMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}

		sem_buf.sem_op = 2;
		if( semop( InstRouteTypeSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstRouteTypeMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}


int EzInstDBCmd :: serviceAddInstProfile( const char *InstId )
{
	struct EzInstProfileMemory instprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &instprofile_rec, 0, sizeof( struct EzInstProfileMemory ) );
	retval = readEzInstProfile( InstId, &instprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] from EzInstProfile....OraErr[%05d]", InstId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addInstProfile( InstId, instprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateInstProfile( const char *InstId )
{
	struct EzInstProfileMemory instprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &instprofile_rec, 0, sizeof( struct EzInstProfileMemory ) );
	retval = readEzInstProfile( InstId, &instprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] from EzInstProfile....OraErr[%05d]", InstId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateInstProfile( InstId, instprofile_rec ) < 0 )
	{
		trace( "Error In Updating InstProfileMemory For InstId[%s]", InstId );
		//dbutil.DBClose();
		return -1;
	}
	trace( "Updated InstProfileMemory For InstId[%s]", InstId );
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteInstProfile( const char *InstId )
{
	if( deleteInstProfile( InstId ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListInstProfile()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s%15s%15s%15s%10s%10s%10s%15s%15s", "InstId", "InstType", "RouteType", "SecurityGroup", "TerminalGroup", "AuthGroup", "CurrCode", "PINCount", "TPINCount", "PrimaryBin", "PADSSEnabled" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < getMaxInstProfile(); i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( InstProfileShmPtr + i )->InstId, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%15s%15s%15s%15s%10s%10d%10d%15s%15c", ( InstProfileShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstType, ( InstProfileShmPtr + i )->InstRouteType, ( InstProfileShmPtr + i )->InstSecurityGroup, ( InstProfileShmPtr + i )->InstTerminalGroup, ( InstProfileShmPtr + i )->InstAuthGroup, ( InstProfileShmPtr + i )->InstCurrencyCode, ( InstProfileShmPtr + i )->MaxATMPINCount, ( InstProfileShmPtr + i )->MaxTelePINCount, ( InstProfileShmPtr + i )->PrimaryBin, ( InstProfileShmPtr + i )->PADSSEnabled );

		sem_buf.sem_op = 2;
		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListInstProfile( const char *InstId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s%15s%15s%15s%10s%10s%10s%15s%15s", "InstId", "InstType", "RouteType", "SecurityGroup", "TerminalGroup", "AuthGroup", "CurrCode", "PINCount", "TPINCount", "PrimaryBin", "PADSSEnabled" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < getMaxInstProfile(); i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( InstProfileShmPtr + i )->InstId, InstId ) )
		{
			printf( "\n%15s%15s%15s%15s%15s%15s%10s%10d%10d%15s%15c", ( InstProfileShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstType, ( InstProfileShmPtr + i )->InstRouteType, ( InstProfileShmPtr + i )->InstSecurityGroup, ( InstProfileShmPtr + i )->InstTerminalGroup, ( InstProfileShmPtr + i )->InstAuthGroup, ( InstProfileShmPtr + i )->InstCurrencyCode, ( InstProfileShmPtr + i )->MaxATMPINCount, ( InstProfileShmPtr + i )->MaxTelePINCount, ( InstProfileShmPtr + i )->PrimaryBin, ( InstProfileShmPtr + i )->PADSSEnabled );
			sem_buf.sem_op = 2;
			if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddInstSelect( const char *RecordNo )
{
	struct EzInstSelectMemory instselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &instselect_rec, 0, sizeof( struct EzInstSelectMemory ) );
	retval = readEzInstSelect( RecordNo, &instselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzInstSelect....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addInstSelect( RecordNo, instselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateInstSelect( const char *RecordNo )
{
	struct EzInstSelectMemory instselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &instselect_rec, 0, sizeof( struct EzInstSelectMemory ) );
	retval = readEzInstSelect( RecordNo, &instselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzInstSelect....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateInstSelect( RecordNo, instselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteInstSelect( const char *RecordNo )
{
	if( deleteInstSelect( RecordNo ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListInstSelect()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%20s%15s%15s%20s%10s%15s%10s", "RecordId", "DeviceType", "FieldType", "FromOffset", "ToOffset", "FieldVal", "Priority", "InstId", "InstType" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxInstSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( InstSelectShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%20s%15s%15s%20s%10d%15s%10s", ( InstSelectShmPtr + i )->RecordId, ( InstSelectShmPtr + i )->DeviceType, ( InstSelectShmPtr + i )->FieldType, ( InstSelectShmPtr + i )->FromOffset, ( InstSelectShmPtr + i )->ToOffset, ( InstSelectShmPtr + i )->FieldVal, ( InstSelectShmPtr + i )->Priority, ( InstSelectShmPtr + i )->InstId, ( InstSelectShmPtr + i )->InstType );

		sem_buf.sem_op = 2;
		if( semop( InstSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListInstSelect( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%20s%15s%15s%20s%10s%15s%10s", "RecordId", "DeviceType", "FieldType", "FromOffset", "ToOffset", "FieldVal", "Priority", "InstId", "InstType" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxInstSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( InstSelectShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%15s%15s%20s%15s%15s%20s%10d%15s%10s", ( InstSelectShmPtr + i )->RecordId, ( InstSelectShmPtr + i )->DeviceType, ( InstSelectShmPtr + i )->FieldType, ( InstSelectShmPtr + i )->FromOffset, ( InstSelectShmPtr + i )->ToOffset, ( InstSelectShmPtr + i )->FieldVal, ( InstSelectShmPtr + i )->Priority, ( InstSelectShmPtr + i )->InstId, ( InstSelectShmPtr + i )->InstType );
			sem_buf.sem_op = 2;
			if( semop( InstSelectSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on InstSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( InstSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddBINSelect( const char *RecordNo )
{
	struct EzBINSelectMemory binselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &binselect_rec, 0, sizeof( struct EzBINSelectMemory ) );
	retval = readEzBINSelect( RecordNo, &binselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzBINSelect....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addBINSelect( RecordNo, binselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateBINSelect( const char *RecordNo )
{
	struct EzBINSelectMemory binselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &binselect_rec, 0, sizeof( struct EzBINSelectMemory ) );
	retval = readEzBINSelect( RecordNo, &binselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzBINSelect....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateBINSelect( RecordNo, binselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteBINSelect( const char *RecordNo )
{
	if( deleteBINSelect( RecordNo ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListBINSelect()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s%15s%10s", "RecordId", "BIN", "InstId", "BINRangeReq", "Priority" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBINSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BINSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( BINSelectShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%15s%15c%10d", ( BINSelectShmPtr + i )->RecordId, ( BINSelectShmPtr + i )->BIN, ( BINSelectShmPtr + i )->InstId, ( BINSelectShmPtr + i )->BINRangeReq, ( BINSelectShmPtr + i )->Priority );

		sem_buf.sem_op = 2;
		if( semop( BINSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListBINSelect( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s%15s%10s", "RecordId", "BIN", "InstId", "BINRangeReq", "Priority" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBINSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BINSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( BINSelectShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%15s%15s%15s%15c%10d", ( BINSelectShmPtr + i )->RecordId, ( BINSelectShmPtr + i )->BIN, ( BINSelectShmPtr + i )->InstId, ( BINSelectShmPtr + i )->BINRangeReq, ( BINSelectShmPtr + i )->Priority );
			sem_buf.sem_op = 2;
			if( semop( BINSelectSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on BINSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}

		sem_buf.sem_op = 2;
		if( semop( BINSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddNetworkSelect( const char *RecordNo )
{
	struct EzNetworkSelectMemory networkselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &networkselect_rec, 0, sizeof( struct EzNetworkSelectMemory ) );
	retval = readEzNetworkSelect( RecordNo, &networkselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzNetworkSelect....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addNetworkSelect( RecordNo, networkselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateNetworkSelect( const char *RecordNo )
{
	struct EzNetworkSelectMemory networkselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &networkselect_rec, 0, sizeof( struct EzNetworkSelectMemory ) );
	retval = readEzNetworkSelect( RecordNo, &networkselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzNetworkSelect....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateNetworkSelect( RecordNo, networkselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteNetworkSelect( const char *RecordNo )
{
	if( deleteNetworkSelect( RecordNo ) < 0 )
			return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListNetworkSelect()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%10s%5s%15s%20s%10s%10s", "RecordId", "InstId", "Priority", "NetworkType", "FieldType", "FromOffset", "ToOffset" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworkSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( NetworkSelectShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%15s%10s%5d%15s%20s%10s%10s", ( NetworkSelectShmPtr + i )->RecordId, ( NetworkSelectShmPtr + i )->InstId, ( NetworkSelectShmPtr + i )->Priority, ( NetworkSelectShmPtr + i )->NetworkType, ( NetworkSelectShmPtr + i )->FieldType, ( NetworkSelectShmPtr + i )->FromOffset, ( NetworkSelectShmPtr + i )->ToOffset );

		sem_buf.sem_op = 2;
		if( semop( NetworkSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListNetworkSelect( const char *RecordNo )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%10s%5s%15s%20s%10s%10s", "RecordId", "InstId", "Priority", "NetworkType", "FieldType", "FromOffset", "ToOffset" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxNetworkSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( NetworkSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( NetworkSelectShmPtr + i )->RecordId, RecordNo ) )
			printf( "\n%15s%10s%5d%15s%20s%10s%10s", ( NetworkSelectShmPtr + i )->RecordId, ( NetworkSelectShmPtr + i )->InstId, ( NetworkSelectShmPtr + i )->Priority, ( NetworkSelectShmPtr + i )->NetworkType, ( NetworkSelectShmPtr + i )->FieldType, ( NetworkSelectShmPtr + i )->FromOffset, ( NetworkSelectShmPtr + i )->ToOffset );

		sem_buf.sem_op = 2;
		if( semop( NetworkSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddBINProfile( const char *InstId, const char *BIN )
{
	struct EzBINProfileMemory binprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &binprofile_rec, 0, sizeof( struct EzBINProfileMemory ) );
	retval = readEzBINProfile( InstId, BIN, &binprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] BIN[%s] from EzBINProfile....OraErr[%05d]", InstId, BIN, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addBINProfile( binprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateBINProfile( const char *InstId, const char *BIN )
{
	struct EzBINProfileMemory binprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &binprofile_rec, 0, sizeof( struct EzBINProfileMemory ) );
	retval = readEzBINProfile( InstId, BIN, &binprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] BIN[%s] from EzBINProfile....OraErr[%05d]", InstId, BIN, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateBINProfile( binprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteBINProfile( const char *InstId, const char *BIN )
{
	if( deleteBINProfile( InstId, BIN ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListBINProfile()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%20s", "InstId", "BIN", "TxnList" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBINProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( BINProfileShmPtr + i )->InstId, RECORD_INIT_VAL ) && strcmp( ( BINProfileShmPtr + i )->BIN, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%20s", ( BINProfileShmPtr + i )->InstId, ( BINProfileShmPtr + i )->BIN, ( BINProfileShmPtr + i )->TxnList );

		sem_buf.sem_op = 2;
		if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListBINProfile( const char *InstId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%20s", "InstId", "BIN", "TxnList" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBINProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( BINProfileShmPtr + i )->InstId, InstId ) && strcmp( ( BINProfileShmPtr + i )->BIN, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%20s", ( BINProfileShmPtr + i )->InstId, ( BINProfileShmPtr + i )->BIN, ( BINProfileShmPtr + i )->TxnList );

		sem_buf.sem_op = 2;
		if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListBINProfile( const char *InstId, const char *BIN )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%20s", "InstId", "BIN", "TxnList" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBINProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( BINProfileShmPtr + i )->InstId, InstId ) && strcmp( ( BINProfileShmPtr + i )->BIN, BIN ) )
		{
			printf( "\n%15s%15s%20s", ( BINProfileShmPtr + i )->InstId, ( BINProfileShmPtr + i )->BIN, ( BINProfileShmPtr + i )->TxnList );
			sem_buf.sem_op = 2;
			if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( BINProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		break;
	}
	return 1;
}

int EzInstDBCmd :: serviceAddBranchProfile( const char *InstId, const char *BranchCode )
{
	struct EzBranchProfileMemory branchprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &branchprofile_rec, 0, sizeof( struct EzBranchProfileMemory ) );
	retval = readEzBranchProfile( InstId, BranchCode, &branchprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] BranchCode[%s] from EzBranchProfile....OraErr[%05d]", InstId, BranchCode, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( addBranchProfile( branchprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateBranchProfile( const char *InstId, const char *BranchCode )
{
	struct EzBranchProfileMemory branchprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &branchprofile_rec, 0, sizeof( struct EzBranchProfileMemory ) );
	retval = readEzBranchProfile( InstId, BranchCode, &branchprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] BranchCode[%s] from EzBranchProfile....OraErr[%05d]", InstId, BranchCode, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateBranchProfile( branchprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteBranchProfile( const char *InstId, const char *BranchCode )
{
	if( deleteBranchProfile( InstId, BranchCode ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListBranchProfile()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s", "InstId", "BranchCode", "BranchMapCode" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBranchProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BranchProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( BranchProfileShmPtr + i )->InstId, RECORD_INIT_VAL ) && strcmp( (  BranchProfileShmPtr + i )->BranchCode, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%15s", ( BranchProfileShmPtr + i )->InstId, ( BranchProfileShmPtr + i )->BranchCode, ( BranchProfileShmPtr + i )->BranchMapCode );

		sem_buf.sem_op = 2;
		if( semop(  BranchProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}


int EzInstDBCmd :: serviceListBranchProfile( const char *InstId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s", "InstId", "BranchCode", "BranchMapCode" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBranchProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BranchProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( BranchProfileShmPtr + i )->InstId, InstId ) && strcmp( (  BranchProfileShmPtr + i )->BranchCode, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%15s", ( BranchProfileShmPtr + i )->InstId, ( BranchProfileShmPtr + i )->BranchCode, ( BranchProfileShmPtr + i )->BranchMapCode );

		sem_buf.sem_op = 2;
		if( semop(  BranchProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListBranchProfile( const char *InstId, const char *BranchCode )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%15s", "InstId", "BranchCode", "BranchMapCode" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxBranchProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( BranchProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on BINProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( BranchProfileShmPtr + i )->InstId, InstId ) && !strcmp( (  BranchProfileShmPtr + i )->BranchCode, BranchCode ) )
		{
			printf( "\n%15s%15s%15s", ( BranchProfileShmPtr + i )->InstId, ( BranchProfileShmPtr + i )->BranchCode, ( BranchProfileShmPtr + i )->BranchMapCode );
			sem_buf.sem_op = 2;
			if( semop(  BranchProfileSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop(  BranchProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on NetworkSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddAuthProperty( const char *RecordNo )
{
	struct EzAuthPropertyMemory authproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &authproperty_rec, 0, sizeof( struct EzAuthPropertyMemory ) );
	retval = readEzAuthProperty( RecordNo, &authproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzAuthProperty....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addAuthProperty( RecordNo, authproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateAuthProperty( const char *RecordNo )
{
	struct EzAuthPropertyMemory authproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &authproperty_rec, 0, sizeof( struct EzAuthPropertyMemory ) );
	retval = readEzAuthProperty( RecordNo, &authproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzAuthProperty....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateAuthProperty( RecordNo, authproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteAuthProperty( const char *RecordNo )
{
	if( deleteAuthProperty( RecordNo ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListAuthProperty()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%15s%10s%10s%10s%s", "RecordId", "AuthGroupId", "MsgType", "TxnCode", "RespCode", "AuthList" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxAuthProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( AuthPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on AuthPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( AuthPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%10s%15s%10s%10s%10s%s", ( AuthPropertyShmPtr + i )->RecordId, ( AuthPropertyShmPtr + i )->AuthGroupId, ( AuthPropertyShmPtr + i )->MsgType, ( AuthPropertyShmPtr + i )->TxnCode, ( AuthPropertyShmPtr + i )->RespCode, ( AuthPropertyShmPtr + i )->AuthList );

		sem_buf.sem_op = 2;
		if( semop( AuthPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on AuthPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListAuthProperty( const char *RecordNo )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%15s%10s%10s%10s%s", "RecordId", "AuthGroupId", "MsgType", "TxnCode", "RespCode", "AuthList" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxAuthProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( AuthPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on AuthPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AuthPropertyShmPtr + i )->RecordId, RecordNo ) )
		{
			printf( "\n%10s%15s%10s%10s%10s%s", ( AuthPropertyShmPtr + i )->RecordId, ( AuthPropertyShmPtr + i )->AuthGroupId, ( AuthPropertyShmPtr + i )->MsgType, ( AuthPropertyShmPtr + i )->TxnCode, ( AuthPropertyShmPtr + i )->RespCode, ( AuthPropertyShmPtr + i )->AuthList );
			sem_buf.sem_op = 2;
			if( semop( AuthPropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on AuthPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AuthPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on AuthPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddChannelProperty( const char *ChannelName )
{
	struct EzChannelPropertyMemory channelproperty_rec;

	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &channelproperty_rec, 0, sizeof( struct EzChannelPropertyMemory ) );
	retval = readEzChannelProperty( ChannelName, &channelproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading ChannelName[%s] from EzChannelProperty....OraErr[%05d]", ChannelName, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( addChannelProperty( ChannelName, channelproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateChannelProperty( const char *ChannelName )
{
	struct EzChannelPropertyMemory channelproperty_rec;

	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &channelproperty_rec, 0, sizeof( struct EzChannelPropertyMemory ) );
	retval = readEzChannelProperty( ChannelName, &channelproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading ChannelName[%s] from EzChannelProperty....OraErr[%05d]", ChannelName, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateChannelProperty( ChannelName, channelproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteChannelProperty( const char *ChannelName )
{
	if( deleteChannelProperty( ChannelName ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListChannelProperty()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%25s%15s%15s%15s", "ChannelName", "ChannelType", "DeviceType", "LayerId" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxChannelProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ChannelPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ChannelPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( ChannelPropertyShmPtr + i )->ChannelName, RECORD_INIT_VAL ) )
			printf( "\n%25s%15s%15s%15s", ( ChannelPropertyShmPtr + i )->ChannelName, ( ChannelPropertyShmPtr + i )->ChannelType, ( ChannelPropertyShmPtr + i )->DeviceType, ( ChannelPropertyShmPtr + i )->LayerId );

		sem_buf.sem_op = 2;
		if( semop( ChannelPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ChannelPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListChannelProperty( const char *ChannelName )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%25s%15s%15s%15s", "ChannelName", "ChannelType", "DeviceType", "LayerId" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxChannelProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ChannelPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ChannelPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( ChannelPropertyShmPtr + i )->ChannelName, ChannelName ) )
		{
			printf( "\n%25s%15s%15s%15s", ( ChannelPropertyShmPtr + i )->ChannelName, ( ChannelPropertyShmPtr + i )->ChannelType, ( ChannelPropertyShmPtr + i )->DeviceType, ( ChannelPropertyShmPtr + i )->LayerId );
			sem_buf.sem_op = 2;
			if( semop( ChannelPropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on ChannelPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ChannelPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ChannelPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddEventProperty( const char *RecordId )
{
	struct EzEventPropertyMemory eventproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &eventproperty_rec, 0, sizeof( struct EzEventPropertyMemory ) );
	retval = readEzEventProperty( RecordId, &eventproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from EventPropertyMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addEventProperty( RecordId, eventproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateEventProperty( const char *RecordId )
{
	struct EzEventPropertyMemory eventproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &eventproperty_rec, 0, sizeof( struct EzEventPropertyMemory ) );
	retval = readEzEventProperty( RecordId, &eventproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from EventPropertyMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateEventProperty( RecordId, eventproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteEventProperty( const char *RecordId )
{
	if( deleteEventProperty( RecordId ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListEventProperty()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%25s%10s%10s%10s%10s%10s", "RecordId", "ChannelName", "MsgType", "TxnCode", "RespCode", "EventFlag", "TimeOut" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxEventProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EventPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( EventPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%10s%25s%10s%10s%10s%10c%10d", ( EventPropertyShmPtr + i )->RecordId, ( EventPropertyShmPtr + i )->ChannelName, ( EventPropertyShmPtr + i )->MsgType, ( EventPropertyShmPtr + i )->TxnCode, ( EventPropertyShmPtr + i )->RespCode, ( EventPropertyShmPtr + i )->EventFlag, ( EventPropertyShmPtr + i )->EventTimeOut );

		sem_buf.sem_op = 2;
		if( semop( EventPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListEventProperty( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%25s%10s%10s%10s%10s%10s", "RecordId", "ChannelName", "MsgType", "TxnCode", "RespCode", "EventFlag", "TimeOut" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxEventProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( EventPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( EventPropertyShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%10s%25s%10s%10s%10s%10c%10d", ( EventPropertyShmPtr + i )->RecordId, ( EventPropertyShmPtr + i )->ChannelName, ( EventPropertyShmPtr + i )->MsgType, ( EventPropertyShmPtr + i )->TxnCode, ( EventPropertyShmPtr + i )->RespCode, ( EventPropertyShmPtr + i )->EventFlag, ( EventPropertyShmPtr + i )->EventTimeOut );
			sem_buf.sem_op = 2;
			if( semop( EventPropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( EventPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddMsgTypeProperty( int MsgType )
{
	struct EzMsgTypePropertyMemory msgtypeproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &msgtypeproperty_rec, 0, sizeof( struct EzMsgTypePropertyMemory ) );
	retval = readEzMsgTypePropertyTable( MsgType, &msgtypeproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading MsgType[%d] from MsgTypePropertyMemory....OraErr[%05d]", MsgType, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( addMsgTypeProperty( MsgType, msgtypeproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateMsgTypeProperty( int MsgType )
{
	struct EzMsgTypePropertyMemory msgtypeproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &msgtypeproperty_rec, 0, sizeof( struct EzMsgTypePropertyMemory ) );
	retval = readEzMsgTypePropertyTable( MsgType, &msgtypeproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%d] from MsgTypePropertyMemory....OraErr[%05d]", MsgType, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateMsgTypeProperty( MsgType, msgtypeproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteMsgTypeProperty( int MsgType )
{
	if( deleteMsgTypeProperty( MsgType ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListMsgTypeProperty()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%15s%15s", "MsgType", "MsgProperty", "LookUpProperty" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxMsgTypeProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MsgTypePropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on MsgTypePropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( MsgTypePropertyShmPtr + i )->MsgType != RECORD_INIT_NUMBER_VAL )
			printf( "\n%10d%15c%15c", ( MsgTypePropertyShmPtr + i )->MsgType, ( MsgTypePropertyShmPtr + i )->MsgProperty, ( MsgTypePropertyShmPtr + i )->LookUpProperty );

		sem_buf.sem_op = 2;
		if( semop( MsgTypePropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListMsgTypeProperty( int MsgType )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%15s%15s", "MsgType", "MsgProperty", "LookUpProperty" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxMsgTypeProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MsgTypePropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on MsgTypePropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( ( MsgTypePropertyShmPtr + i )->MsgType == MsgType )
		{
			printf( "\n%10d%15c%15c", ( MsgTypePropertyShmPtr + i )->MsgType, ( MsgTypePropertyShmPtr + i )->MsgProperty, ( MsgTypePropertyShmPtr + i )->LookUpProperty );
			sem_buf.sem_op = 2;
			if( semop( MsgTypePropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( MsgTypePropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on EventPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddMsgTranslate( const char *MsgTranslateId )
{
	struct EzMsgTranslateMemory msgtranslate_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &msgtranslate_rec, 0, sizeof( struct EzMsgTranslateMemory ) );
	retval = readEzMsgTranslate( MsgTranslateId, &msgtranslate_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading MsgTranslateId[%s] from MsgTranslateMemory....OraErr[%05d]", MsgTranslateId, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( addMsgTranslate( MsgTranslateId, msgtranslate_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateMsgTranslate( const char *MsgTranslateId )
{
	struct EzMsgTranslateMemory msgtranslate_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &msgtranslate_rec, 0, sizeof( struct EzMsgTranslateMemory ) );
	retval = readEzMsgTranslate( MsgTranslateId, &msgtranslate_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading MsgTranslateId[%s] from MsgTranslateMemory....OraErr[%05d]", MsgTranslateId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateMsgTranslate( MsgTranslateId, msgtranslate_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteMsgTranslate( const char *MsgTranslateId )
{
	if( deleteMsgTranslate( MsgTranslateId ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListMsgTranslate()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s\t%s", "MsgTranslateId", "TranslateDesc" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxMsgTranslate; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on MsgTranslateMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( MsgTranslateShmPtr + i )->MsgTranslateId, RECORD_INIT_VAL ) )
			printf( "\n%20s\t%s", ( MsgTranslateShmPtr + i )->MsgTranslateId, ( MsgTranslateShmPtr + i )->TranslateDesc );

		sem_buf.sem_op = 2;
		if( semop( MsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on MsgTranslateMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListMsgTranslate( const char *MsgTranslateId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s\t%s", "MsgTranslateId", "TranslateDesc" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxMsgTranslate; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( MsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on MsgTranslateMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( MsgTranslateShmPtr + i )->MsgTranslateId, MsgTranslateId ) )
		{
			printf( "\n%20s\t%s", ( MsgTranslateShmPtr + i )->MsgTranslateId, ( MsgTranslateShmPtr + i )->TranslateDesc );
			sem_buf.sem_op = 2;
			if( semop( MsgTranslateSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on MsgTranslateMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
		sem_buf.sem_op = 2;
		if( semop( MsgTranslateSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on MsgTranslateMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddTxnRefSelect( const char *RecordId )
{
	struct EzTxnRefSelectMemory txnrefselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &txnrefselect_rec, 0, sizeof( struct EzTxnRefSelectMemory ) );
	retval = readEzTxnRefSelect( RecordId, &txnrefselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from TxnRefSelectMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( addTxnRefSelect( RecordId, txnrefselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateTxnRefSelect( const char *RecordId )
{
	struct EzTxnRefSelectMemory txnrefselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &txnrefselect_rec, 0, sizeof( struct EzTxnRefSelectMemory ) );
	retval = readEzTxnRefSelect( RecordId, &txnrefselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from TxnRefSelectMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateTxnRefSelect( RecordId, txnrefselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteTxnRefSelect( const char *RecordId )
{
	if( deleteTxnRefSelect( RecordId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListTxnRefSelect()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%10s%10s%10s%s", "RecordId", "DeviceType", "MsgType", "TxnCode", "RespCode", "KeyFields" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxTxnRefSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRefSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRefSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( TxnRefSelectShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%15s%15s%10s%10s%10s%s", ( TxnRefSelectShmPtr + i )->RecordId, ( TxnRefSelectShmPtr + i )->DeviceType, ( TxnRefSelectShmPtr + i )->MsgType, ( TxnRefSelectShmPtr + i )->TxnCode, ( TxnRefSelectShmPtr + i )->RespCode, ( TxnRefSelectShmPtr + i )->KeyFields );

		sem_buf.sem_op = 2;
		if( semop( TxnRefSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRefSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListTxnRefSelect( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%15s%10s%10s%10s%s", "RecordId", "DeviceType", "MsgType", "TxnCode", "RespCode", "KeyFields" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxTxnRefSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRefSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRefSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( TxnRefSelectShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%15s%15s%10s%10s%10s%s", ( TxnRefSelectShmPtr + i )->RecordId, ( TxnRefSelectShmPtr + i )->DeviceType, ( TxnRefSelectShmPtr + i )->MsgType, ( TxnRefSelectShmPtr + i )->TxnCode, ( TxnRefSelectShmPtr + i )->RespCode, ( TxnRefSelectShmPtr + i )->KeyFields );
			sem_buf.sem_op = 2;
			if( semop( TxnRefSelectSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on TxnRefSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}

		sem_buf.sem_op = 2;
		if( semop( TxnRefSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRefSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddTxnRouteSelect( const char *RouteSelectId )
{
	struct EzTxnRouteSelectMemory txnrouteselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &txnrouteselect_rec, 0, sizeof( struct EzTxnRouteSelectMemory ) );
	retval = readEzTxnRouteSelect( RouteSelectId, &txnrouteselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RouteSelectId[%s] from TxnRouteSelectMemory....OraErr[%05d]", RouteSelectId, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( addRouteSelect( RouteSelectId, txnrouteselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateTxnRouteSelect( const char *RouteSelectId )
{
	struct EzTxnRouteSelectMemory txnrouteselect_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &txnrouteselect_rec, 0, sizeof( struct EzTxnRouteSelectMemory ) );
	retval = readEzTxnRouteSelect( RouteSelectId, &txnrouteselect_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RouteSelectId[%s] from TxnRouteSelectMemory....OraErr[%05d]", RouteSelectId, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateRouteSelect( RouteSelectId, txnrouteselect_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteTxnRouteSelect( const char *RouteSelectId )
{
	if( deleteRouteSelect( RouteSelectId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListTxnRouteSelect()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%10s", "RouteSelectId", "ChannelName", "MsgTranslateId", "LogFlag" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxTxnRouteSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( TxnRouteSelectShmPtr + i )->RouteSelectId, RECORD_INIT_VAL ) )
			printf( "\n%20s%20s%20s%10c", ( TxnRouteSelectShmPtr + i )->RouteSelectId, ( TxnRouteSelectShmPtr + i )->ChannelName, ( TxnRouteSelectShmPtr + i )->MsgTranslateId, ( TxnRouteSelectShmPtr + i )->LogFlag );

		sem_buf.sem_op = 2;
		if( semop( TxnRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListTxnRouteSelect( const char *RouteSelectId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%20s%20s%10s", "RouteSelectId", "ChannelName", "MsgTranslateId", "LogFlag" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxTxnRouteSelect; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( TxnRouteSelectShmPtr + i )->RouteSelectId, RouteSelectId ) )
		{
			printf( "\n%20s%20s%20s%10c", ( TxnRouteSelectShmPtr + i )->RouteSelectId, ( TxnRouteSelectShmPtr + i )->ChannelName, ( TxnRouteSelectShmPtr + i )->MsgTranslateId, ( TxnRouteSelectShmPtr + i )->LogFlag );
			sem_buf.sem_op = 2;
			if( semop( TxnRouteSelectSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on TxnRouteSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnRouteSelectSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteSelectMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddDeviceTypeMap( const char *DeviceGroupId )
{
	struct EzDeviceTypeMapMemory devicetypemap_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &devicetypemap_rec, 0, sizeof( struct EzDeviceTypeMapMemory ) );
	retval = readEzDeviceTypeMap( DeviceGroupId, &devicetypemap_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading DeviceGroupId[%s] from DeviceTypeMapMemory....OraErr[%05d]", DeviceGroupId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addDeviceTypeMap( DeviceGroupId, devicetypemap_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateDeviceTypeMap( const char *DeviceGroupId )
{
	struct EzDeviceTypeMapMemory devicetypemap_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &devicetypemap_rec, 0, sizeof( struct EzDeviceTypeMapMemory ) );
	retval = readEzDeviceTypeMap( DeviceGroupId, &devicetypemap_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading DeviceGroupId[%s] from DeviceTypeMapMemory....OraErr[%05d]", DeviceGroupId, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateDeviceTypeMap( DeviceGroupId, devicetypemap_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteDeviceTypeMap( const char *DeviceGroupId )
{
	if( deleteDeviceTypeMap( DeviceGroupId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListDeviceTypeMap()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%10s", "DeviceGroupId", "DeviceGroupVal" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxDeviceTypeMap; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( DeviceTypeMapSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on DeviceTypeMapMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( DeviceTypeMapShmPtr + i )->DeviceGroupId, RECORD_INIT_VAL ) )
			printf( "\n%20s%10d", ( DeviceTypeMapShmPtr + i )->DeviceGroupId, ( DeviceTypeMapShmPtr + i )->DeviceGroupVal );

		sem_buf.sem_op = 2;
		if( semop( DeviceTypeMapSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on DeviceTypeMapMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListDeviceTypeMap( const char *DeviceGroupId )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%20s%10s", "DeviceGroupId", "DeviceGroupVal" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxDeviceTypeMap; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( DeviceTypeMapSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on DeviceTypeMapMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( DeviceTypeMapShmPtr + i )->DeviceGroupId, DeviceGroupId ) )
		{
			printf( "\n%20s%10d", ( DeviceTypeMapShmPtr + i )->DeviceGroupId, ( DeviceTypeMapShmPtr + i )->DeviceGroupVal );
			sem_buf.sem_op = 2;
			if( semop( DeviceTypeMapSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on DeviceTypeMapMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( DeviceTypeMapSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on DeviceTypeMapMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddInBoundMsgProperty( const char *RecordId )
{
	struct EzInBoundMsgPropertyMemory inboundmsgproperty_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &inboundmsgproperty_rec, 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
	retval = readEzInBoundMsgProperty( RecordId, &inboundmsgproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from InBoundMsgPropertyMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addInBoundMsgProperty( RecordId, inboundmsgproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateInBoundMsgProperty( const char *RecordId )
{
	struct EzInBoundMsgPropertyMemory inboundmsgproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &inboundmsgproperty_rec, 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
	retval = readEzInBoundMsgProperty( RecordId, &inboundmsgproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from InBoundMsgPropertyMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateInBoundMsgProperty( RecordId, inboundmsgproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteInBoundMsgProperty( const char *RecordId )
{
	if( deleteInBoundMsgProperty( RecordId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListInBoundMsgProperty()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%10s%15s%20s%10s%10s%10s", "RecordId", "MsgType", "ChannelType", "ChannelName", "MsgFlag", "LogFlag", "MsgProcessFlag" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxInBoundMsgProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InBoundMsgPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InBoundMsgPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( InBoundMsgPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%15s%10s%15s%20s%10c%10c%10c", ( InBoundMsgPropertyShmPtr + i )->RecordId, ( InBoundMsgPropertyShmPtr + i )->MsgType, ( InBoundMsgPropertyShmPtr + i )->ChannelType, ( InBoundMsgPropertyShmPtr + i )->ChannelName, ( InBoundMsgPropertyShmPtr + i )->MsgFlag, ( InBoundMsgPropertyShmPtr + i )->LogFlag, ( InBoundMsgPropertyShmPtr + i )->MsgProcessFlag );

		sem_buf.sem_op = 2;
		if( semop( InBoundMsgPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InBoundMsgPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListInBoundMsgProperty( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%10s%15s%20s%10s%10s%10s", "RecordId", "MsgType", "ChannelType", "ChannelName", "MsgFlag", "LogFlag", "MsgProcessFlag" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxInBoundMsgProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InBoundMsgPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InBoundMsgPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( InBoundMsgPropertyShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%15s%10s%15s%20s%10c%10c%10c", ( InBoundMsgPropertyShmPtr + i )->RecordId, ( InBoundMsgPropertyShmPtr + i )->MsgType, ( InBoundMsgPropertyShmPtr + i )->ChannelType, ( InBoundMsgPropertyShmPtr + i )->ChannelName, ( InBoundMsgPropertyShmPtr + i )->MsgFlag, ( InBoundMsgPropertyShmPtr + i )->LogFlag, ( InBoundMsgPropertyShmPtr + i )->MsgProcessFlag );
			sem_buf.sem_op = 2;
			if( semop( InBoundMsgPropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on InBoundMsgPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( InBoundMsgPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InBoundMsgPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddTxnRouteInfo( const char *RecordId )
{
	struct EzTxnRouteInfoMemory txnrouteinfo_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &txnrouteinfo_rec, 0, sizeof( struct EzTxnRouteInfoMemory ) );
	retval = readEzTxnRouteInfo( RecordId, &txnrouteinfo_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from TxnRouteInfoMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addTxnRouteInfo( RecordId, txnrouteinfo_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateTxnRouteInfo( const char *RecordId )
{
	struct EzTxnRouteInfoMemory txnrouteinfo_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &txnrouteinfo_rec, 0, sizeof( struct EzTxnRouteInfoMemory ) );
	retval = readEzTxnRouteInfo( RecordId, &txnrouteinfo_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from TxnRouteInfoMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateTxnRouteInfo( RecordId, txnrouteinfo_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteTxnRouteInfo( const char *RecordId )
{
	if( deleteTxnRouteInfo( RecordId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceSetDebugFlag( const char *RecordId, char DebugFlag )
{
	struct sembuf sem_buf;

	for( int i = 0; i < MaxTxnRouteInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( TxnRouteInfoShmPtr + i )->RecordId, RecordId ) )
		{
			( TxnRouteInfoShmPtr + i )->DebugFlag = DebugFlag;
			sem_buf.sem_op = 2;
			if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}


int EzInstDBCmd :: serviceListTxnRouteInfo()
{
	struct sembuf sem_buf;

	for( int i = 0; i < MaxTxnRouteInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( TxnRouteInfoShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
		{
			printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			printf( "\nRecordId[%s]", ( TxnRouteInfoShmPtr + i )->RecordId );
			printf( "\nIssuerInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->IssuerInstRouteType );
			printf( "\nAcquirerInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->AcquirerInstRouteType );
			printf( "\nTxfInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->TxfInstRouteType );
			printf( "\nSettInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->SettInstRouteType );
			printf( "\nFwdInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->FwdInstRouteType );
			printf( "\nDeviceType[%s]", ( TxnRouteInfoShmPtr + i )->DeviceType );
			printf( "\nDeviceSubType[%s]", ( TxnRouteInfoShmPtr + i )->DeviceSubType );
			printf( "\nMsgType[%s]", ( TxnRouteInfoShmPtr + i )->MsgType );
			printf( "\nTxnCode[%s]", ( TxnRouteInfoShmPtr + i )->TxnCode );
			printf( "\nRespCode[%s]", ( TxnRouteInfoShmPtr + i )->RespCode );
			printf( "\nRouteExp1[%s]", ( TxnRouteInfoShmPtr + i )->RouteExp1 );
			printf( "\nRouteExpPriority1[%d]", ( TxnRouteInfoShmPtr + i )->RouteExpPriority1 );
			printf( "\nRouteExp2[%s]", ( TxnRouteInfoShmPtr + i )->RouteExp2 );
			printf( "\nRouteExpPriority2[%d]", ( TxnRouteInfoShmPtr + i )->RouteExpPriority2 );
			printf( "\nChannelName[%s]", ( TxnRouteInfoShmPtr + i )->ChannelName );
			printf( "\nNetworkTypeList[%s]", ( TxnRouteInfoShmPtr + i )->NetworkTypeList );
			printf( "\nNetworkStatusList[%s]", ( TxnRouteInfoShmPtr + i )->NetworkStatusList );
			printf( "\nNetworkListPriority[%d]", ( TxnRouteInfoShmPtr + i )->NetworkListPriority );
			printf( "\nRouteCondition[%s]", ( TxnRouteInfoShmPtr + i )->RouteCondition );
			printf( "\nRouteConditionPriority[%d]", ( TxnRouteInfoShmPtr + i )->RouteConditionPriority );
			printf( "\nRouteSelectList[%s]", ( TxnRouteInfoShmPtr + i )->RouteSelectList );
			printf( "\nDebugFlag[%c]", ( TxnRouteInfoShmPtr + i )->DebugFlag );
		}
		sem_buf.sem_op = 2;
		if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListTxnRouteInfo( const char *RecordId )
{
	struct sembuf sem_buf;

	for( int i = 0; i < MaxTxnRouteInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( TxnRouteInfoShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			printf( "\nRecordId[%s]", ( TxnRouteInfoShmPtr + i )->RecordId );
			printf( "\nIssuerInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->IssuerInstRouteType );
			printf( "\nAcquirerInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->AcquirerInstRouteType );
			printf( "\nTxfInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->TxfInstRouteType );
			printf( "\nSettInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->SettInstRouteType );
			printf( "\nFwdInstRouteType[%s]", ( TxnRouteInfoShmPtr + i )->FwdInstRouteType );
			printf( "\nDeviceType[%s]", ( TxnRouteInfoShmPtr + i )->DeviceType );
			printf( "\nDeviceSubType[%s]", ( TxnRouteInfoShmPtr + i )->DeviceSubType );
			printf( "\nMsgType[%s]", ( TxnRouteInfoShmPtr + i )->MsgType );
			printf( "\nTxnCode[%s]", ( TxnRouteInfoShmPtr + i )->TxnCode );
			printf( "\nRespCode[%s]", ( TxnRouteInfoShmPtr + i )->RespCode );
			printf( "\nRouteExp1[%s]", ( TxnRouteInfoShmPtr + i )->RouteExp1 );
			printf( "\nRouteExpPriority1[%d]", ( TxnRouteInfoShmPtr + i )->RouteExpPriority1 );
			printf( "\nRouteExp2[%s]", ( TxnRouteInfoShmPtr + i )->RouteExp2 );
			printf( "\nRouteExpPriority2[%d]", ( TxnRouteInfoShmPtr + i )->RouteExpPriority2 );
			printf( "\nChannelName[%s]", ( TxnRouteInfoShmPtr + i )->ChannelName );
			printf( "\nNetworkTypeList[%s]", ( TxnRouteInfoShmPtr + i )->NetworkTypeList );
			printf( "\nNetworkStatusList[%s]", ( TxnRouteInfoShmPtr + i )->NetworkStatusList );
			printf( "\nNetworkListPriority[%d]", ( TxnRouteInfoShmPtr + i )->NetworkListPriority );
			printf( "\nRouteCondition[%s]", ( TxnRouteInfoShmPtr + i )->RouteCondition );
			printf( "\nRouteConditionPriority[%d]", ( TxnRouteInfoShmPtr + i )->RouteConditionPriority );
			printf( "\nRouteSelectList[%s]", ( TxnRouteInfoShmPtr + i )->RouteSelectList );
			printf( "\nDebugFlag[%c]", ( TxnRouteInfoShmPtr + i )->DebugFlag );
			sem_buf.sem_op = 2;
			if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnRouteInfoSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnRouteInfoMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddTxnMsgOrder( const char *RecordId )
{
	struct EzTxnMsgOrderMemory txnmsgorder_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &txnmsgorder_rec, 0, sizeof( struct EzTxnMsgOrderMemory ) );
	retval = readEzTxnMsgOrder( RecordId, &txnmsgorder_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from TxnMsgOrderMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addTxnMsgOrder( RecordId, txnmsgorder_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateTxnMsgOrder( const char *RecordId )
{
	struct EzTxnMsgOrderMemory txnmsgorder_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &txnmsgorder_rec, 0, sizeof( struct EzTxnMsgOrderMemory ) );
	retval = readEzTxnMsgOrder( RecordId, &txnmsgorder_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordId[%s] from TxnMsgOrderMemory....OraErr[%05d]", RecordId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateTxnMsgOrder( RecordId, txnmsgorder_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteTxnMsgOrder( const char *RecordId )
{
	if( deleteTxnMsgOrder( RecordId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListTxnMsgOrder()
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%20s%10s%10s%10s%10s", "RecordId", "SrcChannel", "DestChannel", "MsgType", "TxnCode", "RespCode", "OrderNo" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxTxnMsgOrder; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnMsgOrderSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnMsgOrderMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( TxnMsgOrderShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%15s%20s%20s%10s%10s%10s%10d", ( TxnMsgOrderShmPtr + i )->RecordId, ( TxnMsgOrderShmPtr + i )->SrcChannel, ( TxnMsgOrderShmPtr + i )->DestChannel, ( TxnMsgOrderShmPtr + i )->MsgType, ( TxnMsgOrderShmPtr + i )->TxnCode, ( TxnMsgOrderShmPtr + i )->RespCode, ( TxnMsgOrderShmPtr + i )->OrderNo );
		sem_buf.sem_op = 2;
		if( semop( TxnMsgOrderSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnMsgOrderMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListTxnMsgOrder( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%20s%10s%10s%10s%10s", "RecordId", "SrcChannel", "DestChannel", "MsgType", "TxnCode", "RespCode", "OrderNo" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxTxnMsgOrder; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( TxnMsgOrderSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnMsgOrderMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( TxnMsgOrderShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "\n%15s%20s%20s%10s%10s%10s%10d", ( TxnMsgOrderShmPtr + i )->RecordId, ( TxnMsgOrderShmPtr + i )->SrcChannel, ( TxnMsgOrderShmPtr + i )->DestChannel, ( TxnMsgOrderShmPtr + i )->MsgType, ( TxnMsgOrderShmPtr + i )->TxnCode, ( TxnMsgOrderShmPtr + i )->RespCode, ( TxnMsgOrderShmPtr + i )->OrderNo );
			sem_buf.sem_op = 2;
			if( semop( TxnMsgOrderSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on TxnMsgOrderMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( TxnMsgOrderSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on TxnMsgOrderMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddInstExtNtwkProfile( const char *InstId, const char *ExtNetworkId )
{
	struct EzInstExtNtwkProfileMemory instextntwkprofile_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &instextntwkprofile_rec, 0, sizeof( struct EzInstExtNtwkProfileMemory ) );
	retval = readEzInstExtNtwkProfile( InstId, ExtNetworkId, &instextntwkprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] ExtNetworkId[%s] from InstExtNtwkProfileMemory....OraErr[%05d]", InstId, ExtNetworkId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addInstExtNtwkProfile( InstId, ExtNetworkId, instextntwkprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateInstExtNtwkProfile( const char *InstId, const char *ExtNetworkId )
{
	struct EzInstExtNtwkProfileMemory instextntwkprofile_rec;
	int retval;
	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/
	memset( &instextntwkprofile_rec, 0, sizeof( struct EzInstExtNtwkProfileMemory ) );
	retval = readEzInstExtNtwkProfile( InstId, ExtNetworkId, &instextntwkprofile_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading InstId[%s] ExtNetworkId[%s] from InstExtNtwkProfileMemory....OraErr[%05d]", InstId, ExtNetworkId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateInstExtNtwkProfile( InstId, ExtNetworkId, instextntwkprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteInstExtNtwkProfile( const char *InstId, const char *ExtNetworkId )
{
	if( deleteInstExtNtwkProfile( InstId, ExtNetworkId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListInstExtNtwkProfile()
{
	struct sembuf sem_buf;

	for( int i = 0; i < MaxInstExtNtwkProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( InstExtNtwkProfileShmPtr + i )->InstId, RECORD_INIT_VAL ) && strcmp( ( InstExtNtwkProfileShmPtr + i )->ExtNetworkId, RECORD_INIT_VAL ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nInstId[%s]", ( InstExtNtwkProfileShmPtr + i )->InstId );
			printf( "\nExtNetworkId[%s]", ( InstExtNtwkProfileShmPtr + i )->ExtNetworkId );
			printf( "\nAcqInstCode[%s]", ( InstExtNtwkProfileShmPtr + i )->AcqInstCode );
			printf( "\nTxnCodeList[%s]", ( InstExtNtwkProfileShmPtr + i )->TxnCodeList );
			printf( "\nAddFee1[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee1 );
			printf( "\nAddFee2[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee2 );
			printf( "\nAddFee3[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee3 );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
		}
		sem_buf.sem_op = 2;
		if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListInstExtNtwkProfile( const char *InstId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%15s%12s%12s%12s", "InstId", "ExtNetworkId", "AcqInstCode", "AddFee1", "AddFee2", "AddFee3" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxInstExtNtwkProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( InstExtNtwkProfileShmPtr + i )->InstId, InstId ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nInstId[%s]", ( InstExtNtwkProfileShmPtr + i )->InstId );
			printf( "\nExtNetworkId[%s]", ( InstExtNtwkProfileShmPtr + i )->ExtNetworkId );
			printf( "\nAcqInstCode[%s]", ( InstExtNtwkProfileShmPtr + i )->AcqInstCode );
			printf( "\nTxnCodeList[%s]", ( InstExtNtwkProfileShmPtr + i )->TxnCodeList );
			printf( "\nAddFee1[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee1 );
			printf( "\nAddFee2[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee2 );
			printf( "\nAddFee3[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee3 );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
		}
		sem_buf.sem_op = 2;
		if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListInstExtNtwkProfile( const char *InstId, const char *ExtNetworkId )
{
	struct sembuf sem_buf;

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%15s%12s%12s%12s", "InstId", "ExtNetworkId", "AcqInstCode", "AddFee1", "AddFee2", "AddFee3" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxInstExtNtwkProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( InstExtNtwkProfileShmPtr + i )->InstId, InstId ) && !strcmp( ( InstExtNtwkProfileShmPtr + i )->ExtNetworkId, ExtNetworkId ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nInstId[%s]", ( InstExtNtwkProfileShmPtr + i )->InstId );
			printf( "\nExtNetworkId[%s]", ( InstExtNtwkProfileShmPtr + i )->ExtNetworkId );
			printf( "\nAcqInstCode[%s]", ( InstExtNtwkProfileShmPtr + i )->AcqInstCode );
			printf( "\nTxnCodeList[%s]", ( InstExtNtwkProfileShmPtr + i )->TxnCodeList );
			printf( "\nAddFee1[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee1 );
			printf( "\nAddFee2[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee2 );
			printf( "\nAddFee3[%s]", ( InstExtNtwkProfileShmPtr + i )->AddFee3 );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
			sem_buf.sem_op = 2;
			if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( InstExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on InstExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddExtNtwkProfile( const char *ExtNetworkId )
{
	struct EzExtNtwkProfileMemory extntwkprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &extntwkprofile_rec, 0, sizeof( struct EzExtNtwkProfileMemory ) );
	retval = readEzExtNtwkProfile( ExtNetworkId, &extntwkprofile_rec );

	if( retval != 1 )
	{
		trace( "Error in Reading ExtNetworkId[%s] from ExtNtwkProfileMemory....OraErr[%05d]", ExtNetworkId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addExtNtwkProfile( ExtNetworkId, extntwkprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateExtNtwkProfile( const char *ExtNetworkId )
{
	struct EzExtNtwkProfileMemory extntwkprofile_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &extntwkprofile_rec, 0, sizeof( struct EzExtNtwkProfileMemory ) );
	retval = readEzExtNtwkProfile( ExtNetworkId, &extntwkprofile_rec );

	if( retval != 1 )
	{
		trace( "Error in Reading ExtNetworkId[%s] from ExtNtwkProfileMemory....OraErr[%05d]", ExtNetworkId, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( updateExtNtwkProfile( ExtNetworkId, extntwkprofile_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}


int EzInstDBCmd :: serviceDeleteExtNtwkProfile( const char *ExtNetworkId )
{
	if( deleteExtNtwkProfile( ExtNetworkId ) < 0 )
		return -1;
	return 1;
}

int EzInstDBCmd :: serviceListExtNtwkProfile()
{
	struct sembuf sem_buf;

	for( int i = 0; i < MaxExtNtwkProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( ExtNtwkProfileShmPtr + i )->ExtNetworkId, RECORD_INIT_VAL ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nExtNetworkId[%s]", ( ExtNtwkProfileShmPtr + i )->ExtNetworkId );
			printf( "\nTxnCodeList[%s]", ( ExtNtwkProfileShmPtr + i )->TxnCodeList );
			printf( "\nTxnAmountCheckReq[%s]", ( ExtNtwkProfileShmPtr + i )->TxnAmountCheckReq );
			printf( "\nTxnCountCheckReq[%s]", ( ExtNtwkProfileShmPtr + i )->TxnCountCheckReq );
			printf( "\nMaxAmountPerTxn[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountPerTxn );
			printf( "\nMaxAmount[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmount );
			printf( "\nMaxAmountInterval[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountInterval );
			printf( "\nMaxAmountIntervalType[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountIntervalType );
			printf( "\nMaxAmountAction[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountAction );
			printf( "\nMaxAmountFee[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountFee );
			printf( "\nMaxCount[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCount );
			printf( "\nMaxCountInterval[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountInterval );
			printf( "\nMaxCountIntervalType[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountIntervalType );
			printf( "\nMaxCountAction[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountAction );
			printf( "\nMaxCountFee[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountFee );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
		}
		sem_buf.sem_op = 2;
		if( semop( ExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListExtNtwkProfile( const char *ExtNetworkId )
{
	struct sembuf sem_buf;

	for( int i = 0; i < MaxExtNtwkProfile; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( ExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( ExtNtwkProfileShmPtr + i )->ExtNetworkId, ExtNetworkId ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nExtNetworkId[%s]", ( ExtNtwkProfileShmPtr + i )->ExtNetworkId );
			printf( "\nTxnCodeList[%s]", ( ExtNtwkProfileShmPtr + i )->TxnCodeList );
			printf( "\nTxnAmountCheckReq[%s]", ( ExtNtwkProfileShmPtr + i )->TxnAmountCheckReq );
			printf( "\nTxnCountCheckReq[%s]", ( ExtNtwkProfileShmPtr + i )->TxnCountCheckReq );
			printf( "\nMaxAmountPerTxn[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountPerTxn );
			printf( "\nMaxAmount[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmount );
			printf( "\nMaxAmountInterval[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountInterval );
			printf( "\nMaxAmountIntervalType[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountIntervalType );
			printf( "\nMaxAmountAction[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountAction );
			printf( "\nMaxAmountFee[%s]", ( ExtNtwkProfileShmPtr + i )->MaxAmountFee );
			printf( "\nMaxCount[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCount );
			printf( "\nMaxCountInterval[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountInterval );
			printf( "\nMaxCountIntervalType[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountIntervalType );
			printf( "\nMaxCountAction[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountAction );
			printf( "\nMaxCountFee[%s]", ( ExtNtwkProfileShmPtr + i )->MaxCountFee );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
		}
		sem_buf.sem_op = 2;
		if( semop( ExtNtwkProfileSemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on ExtNtwkProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceAddSafProperty( const char *RecordNo )
{
	struct EzSafPropertyMemory Safproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &Safproperty_rec, 0, sizeof( struct EzSafPropertyMemory ) );
	retval = readEzSafProperty( RecordNo, &Safproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzSafProperty....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}
	if( addSafProperty( RecordNo, Safproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceUpdateSafProperty( const char *RecordNo )
{
	struct EzSafPropertyMemory Safproperty_rec;
	int retval;

	/*if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}*/

	memset( &Safproperty_rec, 0, sizeof( struct EzSafPropertyMemory ) );
	retval = readEzSafProperty( RecordNo, &Safproperty_rec );
	if( retval != 1 )
	{
		trace( "Error in Reading RecordNo[%s] from EzSafProperty....OraErr[%05d]", RecordNo, retval );
		//dbutil.DBClose();
		return -1;
	}

	if( updateSafProperty( RecordNo, Safproperty_rec ) < 0 )
	{
		//dbutil.DBClose();
		return -1;
	}
	//dbutil.DBClose();
	return 1;
}

int EzInstDBCmd :: serviceDeleteSafProperty( const char *RecordNo )
{
	if( deleteSafProperty( RecordNo ) < 0 )
		return -1;
	else
		return 1;
}

int EzInstDBCmd :: serviceListSafProperty()
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%10s%10s%10s%10s%10s%10s%10s%10s%s", "RecordId", "MsgIndicator", "InstId", "NetworkId", "NetworkStatus", "MsgType", "TxnCode", "RespCode", "RevCode", "SafAction" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxSafProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( SafPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on SafPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( SafPropertyShmPtr + i )->RecordId, RECORD_INIT_VAL ) )
			printf( "\n%10s%10c%10s%10s%10s%10s%10s%10s%10s%c", ( SafPropertyShmPtr + i )->RecordId, ( SafPropertyShmPtr + i )->MsgIndicator, ( SafPropertyShmPtr + i )->InstId, ( SafPropertyShmPtr + i )->NetworkId, ( SafPropertyShmPtr + i )->NetworkStatus, ( SafPropertyShmPtr + i )->MsgType, ( SafPropertyShmPtr + i )->TxnCode, ( SafPropertyShmPtr + i )->RespCode, ( SafPropertyShmPtr + i )->RevCode, ( SafPropertyShmPtr + i )->SafAction );

		sem_buf.sem_op = 2;
		if( semop( SafPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on SafPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceListSafProperty( const char *RecordNo )
{
	struct sembuf sem_buf;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%10s%10s%10s%10s%10s%10s%10s%10s%10s%s", "RecordId", "MsgIndicator", "InstId", "NetworkId", "NetworkStatus", "MsgType", "TxnCode", "RespCode", "RevCode", "SafAction" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxSafProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( SafPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on SafPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( SafPropertyShmPtr + i )->RecordId, RecordNo ) )
		{
			printf( "\n%10s%10c%10s%10s%10s%10s%10s%10s%10s%c", ( SafPropertyShmPtr + i )->RecordId, ( SafPropertyShmPtr + i )->MsgIndicator, ( SafPropertyShmPtr + i )->InstId, ( SafPropertyShmPtr + i )->NetworkId, ( SafPropertyShmPtr + i )->NetworkStatus, ( SafPropertyShmPtr + i )->MsgType, ( SafPropertyShmPtr + i )->TxnCode, ( SafPropertyShmPtr + i )->RespCode, ( SafPropertyShmPtr + i )->RevCode, ( SafPropertyShmPtr + i )->SafAction );
			sem_buf.sem_op = 2;
			if( semop( SafPropertySemId, &sem_buf, 1  ) < 0 )
			{
				trace( "Error in Semop Operation on SafPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SafPropertySemId, &sem_buf, 1  ) < 0 )
		{
			trace( "Error in Semop Operation on SafPropertyMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzInstDBCmd :: serviceInstDBCmd( int argc, char **argv )
{
	char command[ 255 ], InstId[ 50 ];

	while( 1 )
	{
		printf( "\nezinstdbcmd>" );
		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;
		if( !strcasecmp( command, "add" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "InstRouteType" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddInstRouteType( command ) < 0 )
				{
					printf("\n *****Error In Adding InstRouteTypeId[%s] To InstRouteType Memory*****", command );
					trace("\n *****Error In Adding InstRouteTypeId[%s] To InstRouteType Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InstProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddInstProfile( command ) < 0 )
				{
					printf("\n *****Error In Adding InstId[%s] To InstProfile Memory*****", command );
					trace("\n *****Error In Adding InstId[%s] To InstProfile Memory*****", command );
				}

				continue;
			}
			else if( !strcasecmp( command, "InstSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddInstSelect( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To InstSelect Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To InstSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BINSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddBINSelect( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To BINSelect Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To BINSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "NetworkSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddNetworkSelect( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To NetworkSelect Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To NetworkSelect mory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BINProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddBINProfile( InstId, command ) < 0 )
				{
					printf("\n *****Error In Adding InstId[%s],Bin[%s] To BINProfile Memory*****", InstId, command );
					trace("\n *****Error In Adding InstId[%s],Bin[%s] To BINProfile Memory*****", InstId, command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BranchProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddBranchProfile( InstId, command ) < 0 )
				{
					printf("\n *****Error In Adding InstId[%s],Branch[%s] To BranchProfile Memory*****", InstId, command );
					trace("\n *****Error In Adding InstId[%s],Branch[%s] To BranchProfile Memory*****", InstId, command );
				}
				continue;
			}
			else if( !strcasecmp( command, "AuthProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddAuthProperty( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To AuthProperty Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To AuthProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "ChannelProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddChannelProperty( command ) < 0 )
				{
					printf("\n *****Error In Adding ChannelName[%s] To ChannelProperty Memory*****", command );
					trace("\n *****Error In Adding ChannelName[%s] To ChannelProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "EventProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddEventProperty( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To EventProperty Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To EventProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "MsgTypeProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddMsgTypeProperty( atoi( command ) ) < 0 )
				{
					printf("\n *****Error In Adding MsgType[%s] To MsgTypeProperty Memory*****", command );
					trace("\n *****Error In Adding MsgType[%s] To MsgTypeProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "MsgTranslate" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddMsgTranslate( command ) < 0 )
				{
					printf("\n *****Error In Adding MsgTranslateId[%s] To MsgTranslate Memory*****", command );
					trace("\n *****Error In Adding MsgTranslateId[%s] To MsgTranslate Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRefSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddTxnRefSelect( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To TxnRefSelect Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To TxnRefSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddTxnRouteSelect( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To TxnRouteSelect Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To TxnRouteSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteInfo" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddTxnRouteInfo( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To TxnRouteInfo Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To TxnRouteInfo Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InBoundMsgProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddInBoundMsgProperty( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To InBoundMsgProperty Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To InBoundMsgProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnMsgOrder" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddTxnMsgOrder( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To TxnMsgOrder Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To TxnMsgOrder Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "SafProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceAddSafProperty( command ) < 0 )
				{
					printf("\n *****Error In Adding RecordNum[%s] To SafProperty Memory*****", command );
					trace("\n *****Error In Adding RecordNum[%s] To SafProperty Memory*****", command );
				}
				continue;
			}
			else
			{
				printf("Invalid Command..");
				continue;
			}

		}
		else if( !strcasecmp( command, "update" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "InstRouteType" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateInstRouteType( command ) < 0 )
				{
					printf("\n *****Error In Updating InstRouteTypeId[%s] To InstRouteType Memory*****", command );
					trace("\n *****Error In Updating InstRouteTypeId[%s] To InstRouteType Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InstProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateInstProfile( command ) < 0 )
				{
					printf("\n *****Error In Updating InstId[%s] To InstProfile Memory*****", command );
					trace("\n *****Error In Updating InstId[%s] To InstProfile Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InstSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateBINSelect( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To InstSelect Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To InstSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BINSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateBINSelect( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To BINSelect Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To BINSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "NetworkSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateNetworkSelect( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To NetworkSelect Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To NetworkSelect mory*****", command );

				}
				continue;
			}
			else if( !strcasecmp( command, "BINProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateBINProfile( InstId, command ) < 0 )
				{
					printf("\n *****Error In updating InstId[%s],Bin[%s] To BINProfile Memory*****", InstId, command );
					trace("\n *****Error In updating InstId[%s],Bin[%s] To BINProfile Memory*****", InstId, command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BranchProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateBranchProfile( InstId, command ) < 0 )
				{
					printf("\n *****Error In updating InstId[%s],Branch[%s] To BranchProfile Memory*****", InstId, command );
					trace("\n *****Error In updating InstId[%s],Branch[%s] To BranchProfile Memory*****", InstId, command );

				}
				continue;
			}
			else if( !strcasecmp( command, "AuthProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateAuthProperty( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To AuthProperty Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To AuthProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "ChannelProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateChannelProperty( command ) < 0 )
				{
					printf("\n *****Error In updating ChannelName[%s] To ChannelProperty Memory*****", command );
					trace("\n *****Error In updating ChannelName[%s] To ChannelProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "EventProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateEventProperty( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To EventProperty Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To EventProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "MsgTypeProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateMsgTypeProperty( atoi( command ) ) < 0 )
				{
					printf("\n *****Error In updating MsgType[%s] To MsgTypeProperty Memory*****", command );
					trace("\n *****Error In updating MsgType[%s] To MsgTypeProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "MsgTranslate" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateMsgTranslate( command ) < 0 )
				{
					printf("\n *****Error In updating MsgTranslateId[%s] To MsgTranslate Memory*****", command );
					trace("\n *****Error In updating MsgTranslateId[%s] To MsgTranslate Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRefSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateTxnRefSelect( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To TxnRefSelect Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To TxnRefSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateTxnRouteSelect( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To TxnRouteSelect Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To TxnRouteSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteInfo" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( !strcasecmp( command, "set" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 4 );
					if( strlen( command ) == 0 )
					{
						printf("\n invaild command ..type help for more");
						continue;
					}
					serviceSetDebugFlag( command, '1' );
					continue;
				}
				else if( !strcasecmp( command, "clear" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 4 );
					if( strlen( command ) == 0 )
					{
						printf("\n invaild command ..type help for more");
						continue;
					}
					serviceSetDebugFlag( command, '0' );
					continue;
				}
				else
				{
					if( serviceUpdateTxnRouteInfo( command ) < 0 )
					{
						printf("\n *****Error In updating RecordNum[%s] To TxnRouteInfo Memory*****", command );
						trace("\n *****Error In updating RecordNum[%s] To TxnRouteInfo Memory*****", command );
					}
					continue;
				}
			}
			else if( !strcasecmp( command, "InBoundMsgProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateInBoundMsgProperty( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To InBoundMsgProperty Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To InBoundMsgProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnMsgOrder" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateTxnMsgOrder( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To TxnMsgOrder Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To TxnMsgOrder Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "SafProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceUpdateSafProperty( command ) < 0 )
				{
					printf("\n *****Error In updating RecordNum[%s] To SafProperty Memory*****", command );
					trace("\n *****Error In updating RecordNum[%s] To SafProperty Memory*****", command );
				}
				continue;
			}
			else
			{
				printf("Invalid Command..");
				continue;
			}
		}
		else if( !strcasecmp( command, "delete" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "InstRouteType" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteInstRouteType( command ) < 0 )
				{
					printf("\n *****Error In Deleting InstRouteTypeId[%s] To InstRouteType Memory*****", command );
					trace("\n *****Error In Deleting InstRouteTypeId[%s] To InstRouteType Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InstProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteInstProfile( command ) < 0 )
				{
					printf("\n *****Error In Deleting InstId[%s] To InstProfile Memory*****", command );
					trace("\n *****Error In Deleting InstId[%s] To InstProfile Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InstSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteInstSelect( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To InstSelect Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To InstSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BINSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteBINSelect( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To BINSelect Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To BINSelect mory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "NetworkSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteNetworkSelect( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To NetworkSelect Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To NetworkSelect mory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BINProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteBINProfile( InstId, command ) < 0 )
				{
					printf("\n *****Error In Deleting InstId[%s],Bin[%s] To BINProfile Memory*****", InstId, command );
					trace("\n *****Error In Deleting InstId[%s],Bin[%s] To BINProfile Memory*****", InstId, command );
				}
				continue;
			}
			else if( !strcasecmp( command, "BranchProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteBranchProfile( InstId, command ) < 0 )
				{
					printf("\n *****Error In Deleting InstId[%s],Branch[%s] To BranchProfile Memory*****", InstId, command );
					trace("\n *****Error In Deleting InstId[%s],Branch[%s] To BranchProfile Memory*****", InstId, command );
				}
				continue;
			}
			else if( !strcasecmp( command, "AuthProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteAuthProperty( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To AuthProperty Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To AuthProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "ChannelProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteChannelProperty( command ) < 0)
				{
					printf("\n *****Error In Deleting ChannelName[%s] To ChannelProperty Memory*****", command );
					trace("\n *****Error In Deleting ChannelName[%s] To ChannelProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "EventProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteEventProperty( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To EventProperty Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To EventProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "MsgTypeProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteMsgTypeProperty( atoi( command ) ) < 0 )
				{
					printf("\n *****Error In Deleting MsgType[%s] To MsgTypeProperty Memory*****", command );
					trace("\n *****Error In Deleting MsgType[%s] To MsgTypeProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "MsgTranslate" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteMsgTranslate( command ) < 0 )
				{
					printf("\n *****Error In Deleting MsgTranslateId[%s] To MsgTranslate Memory*****", command );
					trace("\n *****Error In Deleting MsgTranslateId[%s] To MsgTranslate Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRefSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteTxnRefSelect( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To TxnRefSelect Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To TxnRefSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteTxnRouteSelect( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To TxnRouteSelect Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To TxnRouteSelect Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteInfo" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteTxnRouteInfo( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To TxnRouteInfo Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To TxnRouteInfo Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "InBoundMsgProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteInBoundMsgProperty( command ) <  0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To InBoundMsgProperty Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To InBoundMsgProperty Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "TxnMsgOrder" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteTxnMsgOrder( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To TxnMsgOrder Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To TxnMsgOrder Memory*****", command );
				}
				continue;
			}
			else if( !strcasecmp( command, "SafProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf("\n invaild command ..type help for more");
					continue;
				}
				if( serviceDeleteSafProperty( command ) < 0 )
				{
					printf("\n *****Error In Deleting RecordNum[%s] To SafProperty Memory*****", command );
					trace("\n *****Error In Deleting RecordNum[%s] To SafProperty Memory*****", command );
				}
				continue;
			}
			else
			{
				printf("Invalid Command..");
				continue;
			}
		}
		else if( !strcasecmp( command, "list" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\n invaild command ..type help for more");
				continue;
			}
			if( !strcasecmp( command, "InstRouteType" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListInstRouteType();
					continue;
				}
				serviceListInstRouteType( command );
				continue;
			}
			else if( !strcasecmp( command, "InstProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListInstProfile();
					continue;
				}
				serviceListInstProfile( command );
				continue;
			}
			else if( !strcasecmp( command, "InstSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListInstSelect();
					continue;
				}
				serviceListInstSelect( command );
				continue;
			}
			else if( !strcasecmp( command, "BINSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListBINSelect();
					continue;
				}
				serviceListBINSelect( command );
				continue;
			}
			else if( !strcasecmp( command, "NetworkSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListNetworkSelect();
					continue;
				}
				serviceListNetworkSelect( command );
				continue;
			}
			else if( !strcasecmp( command, "BINProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListBINProfile();
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					serviceListBINProfile( InstId );
					continue;
				}
				serviceListBINProfile( InstId, command );
				continue;
			}
			else if( !strcasecmp( command, "BranchProfile" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListBranchProfile();
					continue;
				}
				memset( InstId, 0, sizeof( InstId ) );
				strcpy( InstId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 4 );
				if( strlen( command ) == 0 )
				{
					serviceListBranchProfile( InstId );
					continue;
				}
				serviceListBranchProfile( InstId, command );
				continue;
			}
			else if( !strcasecmp( command, "AuthProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListAuthProperty();
					continue;
				}
				serviceListAuthProperty( command );
				continue;
			}
			else if( !strcasecmp( command, "ChannelProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListChannelProperty();
					continue;
				}
				serviceListChannelProperty( command );
				continue;
			}
			else if( !strcasecmp( command, "EventProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListEventProperty();
					continue;
				}
				serviceListEventProperty( command );
				continue;
			}
			else if( !strcasecmp( command, "MsgTypeProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListMsgTypeProperty();
					continue;
				}
				serviceListMsgTypeProperty( atoi( command ) );
				continue;
			}
			else if( !strcasecmp( command, "MsgTranslate" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListMsgTranslate();
					continue;
				}
				serviceListMsgTranslate( command );
				continue;
			}
			else if( !strcasecmp( command, "TxnRefSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTxnRefSelect();
					continue;
				}
				serviceListTxnRefSelect( command );
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteSelect" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTxnRouteSelect();
					continue;
				}
				serviceListTxnRouteSelect( command );
				continue;
			}
			else if( !strcasecmp( command, "TxnRouteInfo" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTxnRouteInfo();
					continue;
				}
				serviceListTxnRouteInfo( command );
				continue;
			}
			else if( !strcasecmp( command, "InBoundMsgProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListInBoundMsgProperty();
					continue;
				}
				serviceListInBoundMsgProperty( command );
				continue;
			}
			else if( !strcasecmp( command, "TxnMsgOrder" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTxnMsgOrder();
					continue;
				}
				serviceListTxnMsgOrder( command );
				continue;
			}
			else if( !strcasecmp( command, "SafProperty" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListSafProperty();
					continue;
				}
				serviceListSafProperty( command );
				continue;
			}
			else
			{
				printf("Invalid Command..");
				continue;
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <add> <InstRouteType> <InstRouteTypeId>" );
			printf("\n <add> <InstProfile> <InstId>" );
			printf("\n <add> <InstSelect> <RecordNum>" );
			printf("\n <add> <BINSelect> <RecordNum>" );
			printf("\n <add> <NetworkSelect> <RecordNum>" );
			printf("\n <add> <BINProfile> <InstId> <BIN>" );
			printf("\n <add> <BranchProfile> <InstId> <BranchCode>" );
			printf("\n <add> <AuthProperty> <RecordNum>" );
			printf("\n <add> <ChannelProperty> <ChannelName>" );
			printf("\n <add> <EventProperty> <RecordNum>" );
			printf("\n <add> <MsgTypeProperty> <MsgType>" );
			printf("\n <add> <MsgTranslate> <MsgTranslateId>" );
			printf("\n <add> <TxnRefSelect> <RecordNum>" );
			printf("\n <add> <TxnRouteSelect> <RouteSelectId>" );
			printf("\n <add> <TxnRouteInfo> <RecordNum>" );
			printf("\n <add> <InBoundMsgProperty> <RecordNum>" );
			printf("\n <add> <TxnMsgOrder> <RecordNum>" );
			printf("\n <add> <SafProperty> <RecordNum>" );
			printf("\n <update> <InstRouteType> <InstRouteTypeId>" );
			printf("\n <update> <InstProfile> <InstId>" );
			printf("\n <update> <InstSelect> <RecordNum>" );
			printf("\n <update> <BINSelect> <RecordNum>" );
			printf("\n <update> <NetworkSelect> <RecordNum>" );
			printf("\n <update> <BINProfile> <InstId> <BIN>" );
			printf("\n <update> <BranchProfile> <InstId> <BranchCode>" );
			printf("\n <update> <AuthProperty> <RecordNum>" );
			printf("\n <update> <ChannelProperty> <ChannelName>" );
			printf("\n <update> <EventProperty> <RecordNum>" );
			printf("\n <update> <MsgTypeProperty> <MsgType>" );
			printf("\n <update> <MsgTranslate> <MsgTranslateId>" );
			printf("\n <update> <TxnRefSelect> <RecordNum>" );
			printf("\n <update> <TxnRouteSelect> <RouteSelectId>" );
			printf("\n <update> <TxnRouteInfo> <RecordNum>" );
			printf("\n <update> <InBoundMsgProperty> <RecordNum>" );
			printf("\n <update> <TxnMsgOrder> <RecordNum>" );
			printf("\n <update> <SafProperty> <RecordNum>" );
			printf("\n <delete> <InstRouteType> <InstRouteTypeId>" );
			printf("\n <delete> <InstProfile> <InstId>" );
			printf("\n <delete> <InstSelect> <RecordNum>" );
			printf("\n <delete> <BINSelect> <RecordNum>" );
			printf("\n <delete> <NetworkSelect> <RecordNum>" );
			printf("\n <delete> <BINProfile> <InstId> <BIN>" );
			printf("\n <delete> <AuthProperty> <RecordNum>" );
			printf("\n <delete> <BranchProfile> <InstId> <BranchCode>" );
			printf("\n <delete> <ChannelProperty> <ChannelName>" );
			printf("\n <delete> <EventProperty> <RecordNum>" );
			printf("\n <delete> <MsgTypeProperty> <MsgType>" );
			printf("\n <delete> <MsgTranslate> <MsgTranslateId>" );
			printf("\n <delete> <TxnRefSelect> <RecordNum>" );
			printf("\n <delete> <TxnRouteSelect> <RouteSelectId>" );
			printf("\n <delete> <TxnRouteInfo> <RecordNum>" );
			printf("\n <delete> <InBoundMsgProperty> <RecordNum>" );
			printf("\n <delete> <TxnMsgOrder> <RecordNum>" );
			printf("\n <delete> <SafProperty> <RecordNum>" );
			printf("\n <list> <InstRouteType>" );
			printf("\n <list> <InstRouteType> <InstRouteTypeId>" );
			printf("\n <list> <InstProfile>" );
			printf("\n <list> <InstProfile> <InstId>" );
			printf("\n <list> <InstSelect>" );
			printf("\n <list> <InstSelect> <RecordNum>" );
			printf("\n <list> <BINSelect>" );
			printf("\n <list> <BINSelect> <RecordNum>" );
			printf("\n <list> <NetworkSelect>" );
			printf("\n <list> <NetworkSelect> <RecordNum>" );
			printf("\n <list> <BINProfile>" );
			printf("\n <list> <BINProfile> <InstId>" );
			printf("\n <list> <BINProfile> <InstId> <BIN>" );
			printf("\n <list> <BranchProfile> <InstId>" );
			printf("\n <list> <BranchProfile> <InstId> <BranchCode>" );
			printf("\n <list> <AuthProperty>" );
			printf("\n <list> <AuthProperty> <RecordNum>" );
			printf("\n <list> <ChannelProperty>" );
			printf("\n <list> <ChannelProperty> <ChannelName>" );
			printf("\n <list> <EventProperty>" );
			printf("\n <list> <EventProperty> <RecordNum>" );
			printf("\n <list> <MsgTypeProperty>" );
			printf("\n <list> <MsgTypeProperty> <MsgType>" );
			printf("\n <list> <MsgTranslate>" );
			printf("\n <list> <MsgTranslate> <MsgTranslateId>" );
			printf("\n <list> <TxnRefSelect>" );
			printf("\n <list> <TxnRefSelect> <RecordNum>" );
			printf("\n <list> <TxnRouteSelect>" );
			printf("\n <list> <TxnRouteSelect> <RouteSelectId>" );
			printf("\n <list> <TxnRouteInfo>" );
			printf("\n <list> <TxnRouteInfo> <RecordNum>" );
			printf("\n <list> <InBoundMsgProperty>" );
			printf("\n <list> <InBoundMsgProperty> <RecordNum>" );
			printf("\n <list> <TxnMsgOrder>" );
			printf("\n <list> <TxnMsgOrder> <RecordNum>" );
			printf("\n <list> <SafProperty>" );
			printf("\n <list> <SafProperty> <RecordNum>" );
		}
		else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
			break;
		else
		{
			printf("\n invaild command ..type help for more");
			continue;
		}
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzInstDBCmd instcmdobj;
	if( instcmdobj.initInstDBCmd( argv[ 0 ] ) < 0 )
	{
		instcmdobj.trace( "^^^^^^^^^^^^^^^ezinstdbcmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		instcmdobj.closeDebug();
		exit( 0 );
	}
	instcmdobj.serviceInstDBCmd( argc, argv );
	return 1;
}



