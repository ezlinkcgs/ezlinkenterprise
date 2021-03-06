#include <ezbusiness/ezatmmgrutil.h>

EzAtmMgrUtil :: EzAtmMgrUtil()
{

}

EzAtmMgrUtil :: ~EzAtmMgrUtil()
{

}

int EzAtmMgrUtil :: initEzAtmMgrUtil( const char *TaskName, EzDebugUtil *dptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	struct EzChannelMgrQMsg chqmsg;
	int EzChannelMgrKey, EzChannelMgrQid;

	this->dptr = dptr;
	//this->dbutil_ptr = dbutil_ptr;

	if( initEzAtmMgrODBC( TaskName, dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in initEzAtmMgrODBC" );
		return -1;
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezbusiness.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in opening file[%s]", cfgpath );
		return -1;
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXATM", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#MAXATM from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Invalid EZBUSINESS#MAXATM[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxAtms = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXFIT", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#MAXFIT from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Invalid EZBUSINESS#MAXFIT[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxFits = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXATMPROPERTY", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#MAXATMPROPERTY from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Invalid EZBUSINESS#MAXATMPROPERTY[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxProperty = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "EZBUSINESS#MAXATMSTATUS", cfgval, 2 ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Searching EZBUSINESS#MAXATMSTATUS from file[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	if( CheckInteger( cfgval ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Invalid EZBUSINESS#MAXATMSTATUS[%s] value defined in file[%s]", cfgval, cfgpath );
		cfgutil.cfg_close();
		return -1;
	}

	MaxStatus = atoi( cfgval );

	cfgutil.cfg_close();

	AtmMemoryId = CreateMemoryId( dptr, ATMMEMORY );

	if( AtmMemoryId < 0 )
	{
		dptr->trace( "Error in Creating ATMMemory[%s]", ATMMEMORY );
		return -1;
	}

	AtmFitId = CreateMemoryId( dptr, ATMFITMEMORY );

	if( AtmFitId < 0 )
	{
		dptr->trace( "Error in Creating ATMFitMemory[%s]", ATMFITMEMORY );
		return -1;
	}

	AtmEjId = CreateMemoryId( dptr, ATMEJMEMORY );

	if( AtmEjId < 0 )
	{
		dptr->trace( "Error in Creating ATMEJMemory[%s]", ATMEJMEMORY );
		return -1;
	}

	AtmPropertyId = CreateMemoryId( dptr, ATMPROPERTYMEMORY );

	if( AtmPropertyId < 0 )
	{
		dptr->trace( "Error in Creating ATMPropertyMemory[%s]", ATMPROPERTYMEMORY );
		return -1;
	}

	AtmActionPropertyId = CreateMemoryId( dptr, ATMACTIONPROPERTYMEMORY );

	if( AtmActionPropertyId < 0 )
	{
		dptr->trace( "Error in Creating ATMActionPropertyMemory[%s]", ATMACTIONPROPERTYMEMORY );
		return -1;
	}

	AtmStatusId = CreateMemoryId( dptr, ATMSTATUSMEMORY );

	if( AtmStatusId < 0 )
	{
		dptr->trace( "Error in Creating ATMStatusMemory[%s]", ATMSTATUSMEMORY );
		return -1;
	}

	if( initInstProfile( dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in initializing the InstProfile");
		return -1;
	}

	if( initLicenseUtil( dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in initializing the LicenseUtil");
		return -1;
	}

	if( initEzSecurityDriverUtil( dptr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in initializing the SecurityDriverUtil...");
		return -1;
	}

	return 1;
}

int EzAtmMgrUtil :: CheckInteger( const char *value )
{
    for( int i = 0; i < strlen( value ); i++ )
    {
        if( ( value[ i ] < 48 ) || ( value[ i ] > 57 ) )
        	return -1;
    }
    return 1;
}

int EzAtmMgrUtil :: getAtmSemVal()
{
	return semctl( AtmMemorySemid, 0, GETVAL, 0 );
}

int EzAtmMgrUtil :: getAtmFitSemVal()
{
	return semctl( AtmFitSemid, 0, GETVAL, 0 );
}

int EzAtmMgrUtil :: getAtmEjSemVal()
{
	return semctl( AtmEjSemid, 0, GETVAL, 0 );
}

int EzAtmMgrUtil :: LoadAtmMemory()
{
	struct AtmMemoryTable atmmemory;
	struct AtmTableInfo atminfo;
	int MemAtmCount = 0, LicenseCount = 0;
    struct sembuf sem_buf;

	dptr->trace( DEBUG_NORMAL,"Loading ATM Memory.. MaxAtms[%d]", MaxAtms );

	AtmMemoryShmid = shmget( ( key_t ) AtmMemoryId, sizeof( struct AtmMemoryTable ) * MaxAtms, IPC_CREAT | 0666 );
	if(  AtmMemoryShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmMemoryShmPtr = ( struct AtmMemoryTable * ) shmat( AtmMemoryShmid, 0, 0 );

	if( AtmMemoryShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxAtms; i++ )
	{
		memset( ( AtmMemoryShmPtr + i ), 0, sizeof( struct AtmMemoryTable ) );
		strcpy( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME );
	}

	AtmCount = getAtmCount();

	if( AtmCount == 0 )
		dptr->trace( DEBUG_ERROR,"No Atm Configured" );

	if( AtmCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting Atm Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( AtmCount > MaxAtms )
	{
		dptr->trace( DEBUG_ERROR,"No.of Atms configured in Atm Table > MaxAtms...Increase the MaxAtms Parameter");
		return -1;
	}

	if( LoadAtmInfo( AtmMemoryShmPtr, AtmCount ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while loading Atm Table Info");
		return -1;
	}

	for( int i = 0; i < getMaxInstProfile(); i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( InstProfileShmPtr + i )->InstId, RECORD_INIT_VAL ) && !strcasecmp( ( InstProfileShmPtr + i )->InstType, "FIN" ) )
		{
			dptr->trace( DEBUG_TEST, "%s--%s--%s", ( InstProfileShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstType, ( InstProfileShmPtr + i )->InstRouteType );

			if( isATMCheckReq( ( InstProfileShmPtr + i )->InstId ) )
			{
				LicenseCount = getATMLimit( ( InstProfileShmPtr + i )->InstId );
				dptr->trace( DEBUG_TEST,"LicenseCount[%d]", LicenseCount );

				for( int j = 0; j < MaxAtms; j++ )
				{
					if( strcmp( ( AtmMemoryShmPtr + j )->AtmId, ATMID_INIT_NAME ) )
					{
						memset( &atmmemory, 0, sizeof( struct AtmMemoryTable ) );
						memcpy( &atmmemory, ( AtmMemoryShmPtr + j ), sizeof( struct AtmMemoryTable ) );

						memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
						memcpy( &atminfo, &atmmemory.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );


						if( !strcmp( atminfo.AcquirerInst, ( InstProfileShmPtr + i )->InstId ) )
							MemAtmCount++;
					}
				}

				dptr->trace( DEBUG_TEST,"MemAtmCount[%d]", MemAtmCount );

				if( MemAtmCount > LicenseCount )
				{
					dptr->trace( DEBUG_TEST,"No of ATMs Configured for this Inst[%s] is [%d] greater than License count[%d]", ( InstProfileShmPtr + i )->InstId, MemAtmCount, LicenseCount );
					MemAtmCount = 0;
					for( int j = 0; j < MaxAtms; j++ )
					{
						if( strcmp( ( AtmMemoryShmPtr + j )->AtmId, ATMID_INIT_NAME ) )
						{
							memset( &atmmemory, 0, sizeof( struct AtmMemoryTable ) );
							memcpy( &atmmemory, ( AtmMemoryShmPtr + j ), sizeof( struct AtmMemoryTable ) );

							memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
							memcpy( &atminfo, &atmmemory.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );


							if( !strcmp( atminfo.AcquirerInst, ( InstProfileShmPtr + i )->InstId ) )
							{
								MemAtmCount++;
								if( MemAtmCount > LicenseCount )
								{
									memset( ( AtmMemoryShmPtr + i ), 0, sizeof( struct AtmMemoryTable ) );
									strcpy( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME );
								}
							}
						}
					}
				}
			}
		}
		sem_buf.sem_op = 2;
		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

	}

	AtmMemorySemid = semget( ( key_t ) AtmMemoryId, MaxAtms, IPC_CREAT | 0666 );
	if( AtmMemorySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxAtms; i++ )
	{
		if( semctl( AtmMemorySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting Atm Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	dptr->trace( DEBUG_TEST,"Loaded ATM Memory Successfully....");
	return 1;
}

int EzAtmMgrUtil :: LoadAtmFit()
{
	int MemFitCount = 0, LicenseCount = 0;
	struct sembuf sem_buf;

	AtmFitShmid = shmget( ( key_t ) AtmFitId, sizeof( struct AtmFit ) * MaxFits, IPC_CREAT | 0666 );

	if(  AtmFitShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Fit Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmFitShmPtr = ( struct AtmFit * ) shmat( AtmFitShmid, 0, 0 );

	if( AtmFitShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Fit Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxFits; i++ )
	{
		memset( ( AtmFitShmPtr + i ), 0, sizeof( struct AtmFit ) );
		strcpy( ( AtmFitShmPtr + i )->RecordId, FITRECORD_INIT_VAL );
	}

	AtmFitCount = getAtmFitCount( &SqlErr );

	if( AtmFitCount == 0 )
		dptr->trace( DEBUG_ERROR,"No Fit Configured" );


	if( AtmFitCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting AtmFit Table Count OraErr[%05d]", SqlErr );
		return -1;
	}

	if( AtmFitCount > MaxFits )
	{
		dptr->trace( DEBUG_ERROR,"No.of Fits configured in AtmFit Table > MaxFits...Increase the MaxFits Parameter");
		return -1;
	}

	if( LoadAtmFitDetails( AtmFitShmPtr  ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading AtmFit Table OraErr[%04d]", SqlErr );
		return -1;
	}
	else
	{
		for( int i = 0; i < getMaxInstProfile(); i++ )
		{
			sem_buf.sem_num = i;
			sem_buf.sem_flg = 0;
			sem_buf.sem_op = -2;

			if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
			{
				dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			if( strcmp( ( InstProfileShmPtr + i )->InstId, RECORD_INIT_VAL ) && !strcasecmp( ( InstProfileShmPtr + i )->InstType, "FIN" ) )
			{
				dptr->trace( DEBUG_TEST, "%s--%s--%s", ( InstProfileShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstType, ( InstProfileShmPtr + i )->InstRouteType );

				if( isBINCheckReq( ( InstProfileShmPtr + i )->InstId ) )
				{
					LicenseCount = getBINLimit( ( InstProfileShmPtr + i )->InstId );
					dptr->trace( DEBUG_TEST,"LicenseCount[%d]", LicenseCount );

					for( int j = 0; j < MaxFits; j++ )
					{
						if( !strcmp( ( AtmFitShmPtr + j )->InstId, ( InstProfileShmPtr + i )->InstId ) )
								MemFitCount++;
					}

					dptr->trace( DEBUG_TEST,"MemFitCount[%d]", MemFitCount );

					if( MemFitCount > LicenseCount )
					{
						dptr->trace( DEBUG_TEST,"No of FITs Configured for this Inst[%s] is [%d] greater than License count[%d]", ( InstProfileShmPtr + i )->InstId, MemFitCount, LicenseCount );
						MemFitCount = 0;
						for( int i = 0; i < MaxFits; i++ )
						{
							if( !strcmp( ( AtmFitShmPtr + i )->InstId, ( InstProfileShmPtr + i )->InstId ) )
							{
								MemFitCount++;
								if( MemFitCount > LicenseCount )
								{
									memset( ( AtmFitShmPtr + i ), 0, sizeof( struct AtmFit ) );
									strcpy( ( AtmFitShmPtr + i )->RecordId , FITRECORD_INIT_VAL );
								}
							}
						}
					}
				}
			}
			sem_buf.sem_op = 2;
			if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
			{
				dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

		}
	}

	AtmFitSemid = semget( ( key_t ) AtmFitId, MaxFits, IPC_CREAT | 0666 );
	if( AtmFitSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Fit Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxFits; i++ )
	{
		if( semctl( AtmFitSemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting Atm Fit Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzAtmMgrUtil :: LoadAtmEjMemory()
{
	struct sembuf sem_buf;

	AtmEjShmid = shmget( ( key_t ) AtmEjId, sizeof( struct ATMEjBuffer ) * MaxAtms, IPC_CREAT | 0666 );

	if(  AtmEjShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Fit Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmEjShmPtr = ( struct ATMEjBuffer * ) shmat( AtmEjShmid, 0, 0 );

	if( AtmEjShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Fit Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxAtms; i++ )
	{
		memset( ( AtmEjShmPtr + i ), 0, sizeof( struct ATMEjBuffer ) );
		strcpy( ( AtmEjShmPtr + i )->AtmId , ATMID_INIT_NAME );
	}

	AtmEjCount = getAtmEjCount( &SqlErr );

	if( AtmEjCount == 0 )
		dptr->trace( DEBUG_ERROR,"No Atm Configured" );


	if( AtmEjCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting AtmEj Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( AtmEjCount > MaxAtms )
	{
		dptr->trace( DEBUG_ERROR,"No.of Atms configured in AtmEj Table > MaxAtms...Increase the MaxAtms Parameter");
		return -1;
	}

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( AtmMemorySemid, &sem_buf, 1  ) < 0 )
		{
			dptr->trace( "Error in Semop Operation on ATM Memory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME ) )
		{
			memset( ( AtmEjShmPtr + i ), 0, sizeof( struct ATMEjBuffer ) );
			dptr->trace("ATMid[%s]", ( AtmMemoryShmPtr + i )->AtmId );
			SqlErr = LoadAtmEjDetails( ( AtmMemoryShmPtr + i )->AtmId, AtmEjShmPtr + i );
			dptr->trace("SqlErr[%d]",SqlErr);
			if( SqlErr != 0 )
				dptr->trace( DEBUG_ERROR,"Error while Loading AtmEj Table for ATM[%s] OraErr[%04d]", ( AtmMemoryShmPtr + i )->AtmId, SqlErr );
		}

		sem_buf.sem_op = 2;
		if( semop( AtmMemorySemid, &sem_buf, 1  ) < 0 )
		{
			dptr->trace( "Error in Semop Operation on ATM Memory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	dptr->trace("test");
	AtmEjSemid = semget( ( key_t ) AtmEjId, MaxAtms, IPC_CREAT | 0666 );
	if( AtmEjSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating AtmEj Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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
	dptr->trace("test");
	for( int i = 0; i < MaxAtms; i++ )
	{
		if( semctl( AtmEjSemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting AtmEj Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	dptr->trace("test");
	return 1;
}

int EzAtmMgrUtil :: LoadAtmPropertyMemory()
{
	int AtmPropertyCount = 0;

	AtmPropertyShmid = shmget( ( key_t ) AtmPropertyId, sizeof( struct EzAtmProperty ) * MaxProperty, IPC_CREAT | 0666 );

	if(  AtmPropertyShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmPropertyShmPtr = ( struct EzAtmProperty * ) shmat( AtmPropertyShmid, 0, 0 );

	if( AtmPropertyShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxProperty; i++ )
	{
		memset( ( AtmPropertyShmPtr + i ), 0, sizeof( struct EzAtmProperty ) );
		strcpy( ( AtmPropertyShmPtr + i )->InstTerminalGroup , INSTTERMINALGROUP_INIT_VAL );
	}

	AtmPropertyCount = getAtmPropertyCount( &SqlErr );

	if( AtmPropertyCount == 0 )
		dptr->trace( DEBUG_ERROR,"No Atm Property Configured" );


	if( AtmPropertyCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting EzAtmProperty Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( AtmPropertyCount > MaxProperty )
	{
		dptr->trace( DEBUG_ERROR,"No.of Property configured in EzAtmProperty Table > MaxProperty...Increase the MaxProperty Parameter");
		return -1;
	}

	if( LoadAtmPropertyTable( AtmPropertyShmPtr  ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading EzAtmProperty Table OraErr[%04d]", SqlErr );
		return -1;
	}

/*	for( int i = 0; i < MaxProperty; i++ )
	{
		dptr->trace( DEBUG_TEST,"[%d] [%s] [%s] [%s] [%s] [%s] [%s]", ( AtmPropertyShmPtr + i )->RecordId, ( AtmPropertyShmPtr + i )->InstTerminalGroup, ( AtmPropertyShmPtr + i )->AtmLogicalGroup, ( AtmPropertyShmPtr + i )->AtmId,
				( AtmPropertyShmPtr + i )->TxnCode, ( AtmPropertyShmPtr + i )->RespCode, ( AtmPropertyShmPtr + i )->CurrencyCode);
	}*/

	AtmPropertySemid = semget( ( key_t ) AtmPropertyId, MaxProperty, IPC_CREAT | 0666 );
	if( AtmPropertySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Property Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxProperty; i++ )
	{
		if( semctl( AtmPropertySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting Atm Property Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzAtmMgrUtil :: LoadAtmActionPropertyMemory()
{
	int AtmActionPropertyCount = 0;

	AtmActionPropertyShmid = shmget( ( key_t ) AtmActionPropertyId, sizeof( struct EzAtmActionProperty ) * MaxProperty, IPC_CREAT | 0666 );

	if(  AtmActionPropertyShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Action Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmActionPropertyShmPtr = ( struct EzAtmActionProperty * ) shmat( AtmActionPropertyShmid, 0, 0 );

	if( AtmActionPropertyShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Action Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxProperty; i++ )
	{
		memset( ( AtmActionPropertyShmPtr + i ), 0, sizeof( struct EzAtmActionProperty ) );
		strcpy( ( AtmActionPropertyShmPtr + i )->InstTerminalGroup , INSTTERMINALGROUP_INIT_VAL );
	}

	AtmActionPropertyCount = getAtmActionPropertyCount( &SqlErr );

	if( AtmActionPropertyCount == 0 )
		dptr->trace( DEBUG_ERROR,"No Atm Action Property Configured" );


	if( AtmActionPropertyCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting EzAtmActionProperty Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( AtmActionPropertyCount > MaxProperty )
	{
		dptr->trace( DEBUG_ERROR,"No.of Property configured in EzAtmActionProperty Table > MaxProperty...Increase the MaxProperty Parameter");
		return -1;
	}

	if( LoadAtmActionPropertyTable( AtmActionPropertyShmPtr  ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading EzAtmActionProperty Table OraErr[%04d]", SqlErr );
		return -1;
	}

	AtmActionPropertySemid = semget( ( key_t ) AtmActionPropertyId, MaxProperty, IPC_CREAT | 0666 );
	if( AtmActionPropertySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Action Property Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxProperty; i++ )
	{
		if( semctl( AtmActionPropertySemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting Atm Action Property Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzAtmMgrUtil :: LoadAtmStatusMemory()
{
	int AtmStatusCount = 0;

	AtmStatusShmid = shmget( ( key_t ) AtmStatusId, sizeof( struct EzAtmStatus ) * MaxStatus, IPC_CREAT | 0666 );

	if(  AtmStatusShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Status Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmStatusShmPtr = ( struct EzAtmStatus * ) shmat( AtmStatusShmid, 0, 0 );

	if( AtmStatusShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Status Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	for( int i = 0; i < MaxStatus; i++ )
	{
		memset( ( AtmStatusShmPtr + i ), 0, sizeof( struct EzAtmStatus ) );
		strcpy( ( AtmStatusShmPtr + i )->StatusCode, STATUS_INIT_CODE );
	}

	AtmStatusCount = getAtmStatusCount( &SqlErr );

	if( AtmStatusCount == 0 )
	{
		dptr->trace( DEBUG_ERROR,"No Atm Status Configured" );
		return -1;
	}

	if( AtmStatusCount < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in getting EzAtmStatusDesc Table Count OraErr[%04d]", SqlErr );
		return -1;
	}

	if( AtmStatusCount > MaxStatus )
	{
		dptr->trace( DEBUG_ERROR,"No.of Property configured in EzAtmStatusDesc Table > MaxStatus...Increase the MaxStatus Parameter");
		return -1;
	}

	if( LoadAtmStatusTable( AtmStatusShmPtr  ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading EzAtmStatusDesc Table OraErr[%04d]", SqlErr );
		return -1;
	}

	AtmStatusSemid = semget( ( key_t ) AtmStatusId, MaxStatus, IPC_CREAT | 0666 );
	if( AtmStatusSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Status Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	for( int i = 0; i < MaxStatus; i++ )
	{
		if( semctl( AtmStatusSemid, i, SETVAL, arg ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Setting Atm Status Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzAtmMgrUtil :: GetAtmMemory()
{
	AtmMemoryShmid = shmget( ( key_t ) AtmMemoryId, 0, IPC_CREAT | 0666 );
	if(  AtmMemoryShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmMemoryShmPtr = ( struct AtmMemoryTable * ) shmat( AtmMemoryShmid, 0, 0 );
	if( AtmMemoryShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Memory Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmMemorySemid = semget( ( key_t ) AtmMemoryId, 0, IPC_CREAT | 0666 );
	if( AtmMemorySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Memory Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: GetAtmFit()
{
	AtmFitShmid = shmget( ( key_t ) AtmFitId, 0, IPC_CREAT | 0666 );
	if(  AtmFitShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Fit Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmFitShmPtr = ( struct AtmFit * ) shmat( AtmFitShmid, 0, 0 );
	if( AtmFitShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Fit Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmFitSemid = semget( ( key_t ) AtmFitId, 0, IPC_CREAT | 0666 );
	if( AtmFitSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Fit Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: GetAtmEjMemory()
{
	AtmEjShmid = shmget( ( key_t ) AtmEjId, 0, IPC_CREAT | 0666 );
	if(  AtmEjShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating AtmEj Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmEjShmPtr = ( struct ATMEjBuffer * ) shmat( AtmEjShmid, 0, 0 );
	if( AtmEjShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching AtmEj Table Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmEjSemid = semget( ( key_t ) AtmEjId, 0, IPC_CREAT | 0666 );
	if( AtmEjSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating AtmEj Table Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: GetAtmMemoryCount( const char *InstId )
{
	struct sembuf sem_buf;
	int retval = -1, Count = 0;
	struct AtmMemoryTable atmmemory;
	struct AtmTableInfo atminfo;

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME ) )
		{
			memset( &atmmemory, 0, sizeof( struct AtmMemoryTable ) );
			memcpy( &atmmemory, ( AtmMemoryShmPtr + i ), sizeof( struct AtmMemoryTable ) );

			memset( &atminfo, 0, sizeof( struct AtmTableInfo ) );
			memcpy( &atminfo, &atmmemory.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );

			if( !strcmp( atminfo.AcquirerInst, InstId ) )
				Count++;
		}

		sem_buf.sem_op = 2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR, "Error in Semop for AtmMemory SysErr[ %s ] ErrNo[ %d ]", strerror( errno ), errno );
			return -1;
		}
	}

	return Count;
}

int EzAtmMgrUtil :: GetAtmPropertyMemory()
{
	AtmPropertyShmid = shmget( ( key_t ) AtmPropertyId, 0, IPC_CREAT | 0666 );
	if( AtmPropertyShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmPropertyShmPtr = ( struct EzAtmProperty * ) shmat( AtmPropertyShmid, 0, 0 );
	if( AtmPropertyShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmPropertySemid = semget( ( key_t ) AtmPropertyId, 0, IPC_CREAT | 0666 );
	if( AtmPropertySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Property Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: GetAtmActionPropertyMemory()
{
	AtmActionPropertyShmid = shmget( ( key_t ) AtmActionPropertyId, 0, IPC_CREAT | 0666 );
	if( AtmActionPropertyShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Action Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmActionPropertyShmPtr = ( struct EzAtmActionProperty * ) shmat( AtmActionPropertyShmid, 0, 0 );
	if( AtmActionPropertyShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Action Property Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmActionPropertySemid = semget( ( key_t ) AtmActionPropertyId, 0, IPC_CREAT | 0666 );
	if( AtmActionPropertySemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Action Property Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: GetAtmStatusMemory()
{
	AtmStatusShmid = shmget( ( key_t ) AtmStatusId, 0, IPC_CREAT | 0666 );
	if( AtmStatusShmid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Status Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmStatusShmPtr = ( struct EzAtmStatus * ) shmat( AtmStatusShmid, 0, 0 );
	if( AtmStatusShmPtr == NULL )
	{
		dptr->trace( DEBUG_ERROR,"Error in attaching Atm Status Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AtmStatusSemid = semget( ( key_t ) AtmStatusId, 0, IPC_CREAT | 0666 );
	if( AtmStatusSemid < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in Creating Atm Status Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: addAtmMemory( const char *InstId, const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;
	struct AtmTableInfo atmtableinfo;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9];
	char StaticStatus[ 11 ];
	int LicenseCount = 0, MemCount = 0;
	bool Found = false;
	struct EzATMKey atmkey;

	if( isATMCheckReq( InstId ) )
	{
		LicenseCount = getATMLimit( InstId );
		dptr->trace( DEBUG_TEST,"LicenseCount[%d]", LicenseCount );

		MemCount = GetAtmMemoryCount( InstId );
		if( MemCount >= LicenseCount )
			dptr->trace( DEBUG_TEST,"ATM Configuration License for this Inst[%s] is Expired", InstId );
		else
			Found = true;
	}
	else
		Found = true;

	if( Found )
	{
		for( int i = 0; i < MaxAtms; i++ )
		{
			sem_buf.sem_num = i;
			sem_buf.sem_flg = 0;
			sem_buf.sem_op = -2;
			if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}

			if( !strcmp( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME ) )
			{
				memset( ( AtmMemoryShmPtr + i ), 0, sizeof( struct AtmMemoryTable ) );
				strcpy( ( AtmMemoryShmPtr + i )->AtmId, AtmId );
				memset( &atmtableinfo, 0, sizeof( struct AtmTableInfo ) );

				if( LoadAtmInfoTables( &atmtableinfo, ( AtmMemoryShmPtr + i )->AtmId ) < 0 )
				{
					dptr->trace( DEBUG_ERROR,"Error while Loading AtmInfo Tables" );
					return -1;
				}

				if( strcmp( atmtableinfo.AtmTypeId, TRITON ) )
				{
					memset( &denominfo, 0, sizeof( struct DenomInfo ) * 9 );
					if( LoadAtmDenomInfo( ( AtmMemoryShmPtr + i )->AtmId, denominfo ) < 0 )
					{
						dptr->trace( DEBUG_ERROR,"Error while Loading Denomination Status AtmId[%s]", ( AtmMemoryShmPtr + i )->AtmId );
						return -1;
					}

					if( LoadAtmStaticStatus( ( AtmMemoryShmPtr + i )->AtmId, StaticStatus ) < 0 )
					{
						dptr->trace( DEBUG_ERROR,"Error while Loading Static Status AtmId[%s]", ( AtmMemoryShmPtr + i )->AtmId );
						return -1;
					}

					memset( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, 0,  sizeof( struct AtmTableInfo ) );
					memcpy( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, &atmtableinfo, sizeof( struct AtmTableInfo ) );

					memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
					memcpy( atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 9 );

					strcpy( atmbuf.StaticStatus, StaticStatus );

					memset( &( AtmMemoryShmPtr + i )->AtmSharedBuffer, 0, sizeof( struct ATMSharedBuffer ) );
					memcpy( &( AtmMemoryShmPtr + i )->AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

				}
				else
				{
					memset( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, 0,  sizeof( struct AtmTableInfo ) );
					memcpy( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, &atmtableinfo, sizeof( struct AtmTableInfo ) );
				}

				retval = 1;
				sem_buf.sem_op = 2;
				if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
				{
					dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
					return -1;
				}
				break;
			}
			sem_buf.sem_op = 2;
			if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
		}
	}


	memset( &atmkey, 0, sizeof( struct EzATMKey ) );
	strcpy( atmkey.ATMId, AtmId );
	strcpy( atmkey.ATMMasterKey, atmtableinfo.AtmMasterKey );
	strcpy( atmkey.ATMCommKey, atmtableinfo.AtmCommKey );
	atmkey.ATMKeyLen = atmtableinfo.AtmKeyLen;

	if( addATMKey( AtmId, &atmkey ) < 0 )
	{
		dptr->trace( "Error in adding ATMId[%s] in ATMKey Memory...", AtmId );
		return -1;
	}

	return retval;
}

int EzAtmMgrUtil :: getInstTermGroup( const char *InstId, char *InstTermGroup )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < getMaxInstProfile(); i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;

		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return retval;
		}

		if( !strcmp( ( InstProfileShmPtr + i )->InstId, InstId ) && !strcasecmp( ( InstProfileShmPtr + i )->InstType, "FIN" ) )
		{
			memset( InstTermGroup, 0, sizeof( InstTermGroup ) );
			strcpy( InstTermGroup, ( InstProfileShmPtr + i )->InstTerminalGroup );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
			{
				dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return retval;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( InstProfileSemId, &sem_buf, 1  ) < 0 )
		{
			dptr->trace( "Error in Semop Operation on InstProfileMemory...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return retval;
		}

	}
	return retval;
}

int EzAtmMgrUtil :: updateAtmMemory( const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;
	struct AtmTableInfo atmtableinfo;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9];
	char StaticStatus[ 11 ];
	struct EzATMKey atmkey;

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			memset( ( AtmMemoryShmPtr + i ), 0, sizeof( struct AtmMemoryTable ) );
			strcpy( ( AtmMemoryShmPtr + i )->AtmId, AtmId );

			memset( &atmtableinfo, 0, sizeof( struct AtmTableInfo ) );
			if( LoadAtmInfoTables( &atmtableinfo, ( AtmMemoryShmPtr + i )->AtmId ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while Loading AtmInfo Tables" );
				return -1;
			}

			if( strcmp( atmtableinfo.AtmTypeId, TRITON ) )
			{
				memset( &denominfo, 0, sizeof( struct DenomInfo ) * 9 );
				if( LoadAtmDenomInfo( ( AtmMemoryShmPtr + i )->AtmId, denominfo ) < 0 )
				{
					dptr->trace( DEBUG_ERROR,"Error while Loading Denomination Status AtmId[%s]", ( AtmMemoryShmPtr + i )->AtmId );
					return -1;
				}

				if( LoadAtmStaticStatus( ( AtmMemoryShmPtr + i )->AtmId, StaticStatus ) < 0 )
				{
					dptr->trace( DEBUG_ERROR,"Error while Loading Static Status AtmId[%s]", ( AtmMemoryShmPtr + i )->AtmId );
					return -1;
				}

				memset( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, 0,  sizeof( struct AtmTableInfo ) );
				memcpy( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, &atmtableinfo, sizeof( struct AtmTableInfo ) );

				memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
				memcpy( atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 9 );

				strcpy( atmbuf.StaticStatus, StaticStatus );

				memset( &( AtmMemoryShmPtr + i )->AtmSharedBuffer, 0, sizeof( struct ATMSharedBuffer ) );
				memcpy( &( AtmMemoryShmPtr + i )->AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );

			}
			else
				memset( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, 0,  sizeof( struct AtmTableInfo ) );
				memcpy( &( AtmMemoryShmPtr + i )->AtmInfoBuffer, &atmtableinfo, sizeof( struct AtmTableInfo ) );

			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	memset( &atmkey, 0, sizeof( struct EzATMKey ) );
	strcpy( atmkey.ATMId, AtmId );
	strcpy( atmkey.ATMMasterKey, atmtableinfo.AtmMasterKey );
	strcpy( atmkey.ATMCommKey, atmtableinfo.AtmCommKey );
	atmkey.ATMKeyLen = atmtableinfo.AtmKeyLen;

	if( updateATMKey( AtmId, &atmkey ) < 0 )
	{
		dptr->trace( "Error in Updating ATMId[%s] in ATMKey Memory...", AtmId );
		return -1;
	}
	return retval;
}

int EzAtmMgrUtil :: removeAtmMemory( const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;
	struct AtmTableInfo atmtableinfo;

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			memset( ( AtmMemoryShmPtr + i ), 0, sizeof( struct AtmMemoryTable ) );
			strcpy( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	if( deleteATMKey( AtmId ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error in deleting ATMId[%s] in ATMKey Memory...", AtmId );
		return -1;
	}
	return retval;
}

int EzAtmMgrUtil :: addAtmFit( struct AtmFitMsg *Atmfitmsg )
{
	int retval = -1;
	struct sembuf sem_buf;

	//Get no of BINs from License server

	for( int i = 0; i < MaxFits; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmFitShmPtr + i )->RecordId, FITRECORD_INIT_VAL ) )
		{
			memset( ( AtmFitShmPtr + i ), 0, sizeof( struct AtmFit ) );
			SqlErr = 0;
			SqlErr = AddAtmFit( (AtmFitShmPtr + i), Atmfitmsg );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding Atm Fit Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: updateAtmFit( struct AtmFitMsg *Atmfitmsg )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxFits; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmFitShmPtr + i )->RecordId, Atmfitmsg->RecordId ) )
		{
			memset( ( AtmFitShmPtr + i ), 0, sizeof( struct AtmFit ) );
			SqlErr = 0;
			SqlErr = AddAtmFit( (AtmFitShmPtr + i), Atmfitmsg );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding Atm Fit Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: removeAtmFit( struct AtmFitMsg *Atmfitmsg )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxFits; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmFitShmPtr + i )->RecordId, Atmfitmsg->RecordId ) )
		{
			memset( ( AtmFitShmPtr + i ), 0, sizeof( struct AtmFit ) );
			strcpy( ( AtmFitShmPtr + i )->RecordId, FITRECORD_INIT_VAL );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmFitSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmFit Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: addAtmEjMemory( const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;

	//Get no of BINs from License server

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmEjShmPtr + i )->AtmId , ATMID_INIT_NAME ) )
		{
			memset( ( AtmEjShmPtr + i ), 0, sizeof( struct ATMEjBuffer ) );
			SqlErr = 0;
			//SqlErr = AddAtmEj( (AtmEjShmPtr + i), Atmfitmsg );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding Atm Fit Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: updateAtmEjMemory( const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmEjShmPtr + i )->AtmId, AtmId ) )
		{
			memset( ( AtmEjShmPtr + i ), 0, sizeof( struct ATMEjBuffer ) );
			SqlErr = 0;
			//SqlErr = AddAtmEj( (AtmEjShmPtr + i), AtmEjmsg );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding Atm Fit Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: removeAtmEjMemory( const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmEjShmPtr + i )->AtmId, AtmId ) )
		{
			memset( ( AtmEjShmPtr + i ), 0, sizeof( struct ATMEjBuffer ) );
			strcpy( ( AtmEjShmPtr + i )->AtmId, ATMID_INIT_NAME );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmEjSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmEj Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: addAtmPropertyMemory( int RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for Atm Property Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmPropertyShmPtr + i )->InstTerminalGroup , INSTTERMINALGROUP_INIT_VAL ) )
		{
			memset( ( AtmPropertyShmPtr + i ), 0, sizeof( struct EzAtmProperty ) );
			SqlErr = 0;
			SqlErr = ReadAtmPropertyTable( ( AtmPropertyShmPtr + i ), RecordId );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding AtmPropertyTable Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: updateAtmPropertyMemory( int RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( AtmPropertyShmPtr + i )->RecordId == RecordId )
		{
			memset( ( AtmPropertyShmPtr + i ), 0, sizeof( struct EzAtmProperty ) );
			SqlErr = 0;
			SqlErr = ReadAtmPropertyTable( ( AtmPropertyShmPtr + i ), RecordId );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding AtmProperty Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: removeAtmPropertyMemory( int RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( AtmPropertyShmPtr + i )->RecordId == RecordId )
		{
			memset( ( AtmPropertyShmPtr + i ), 0, sizeof( struct EzAtmProperty ) );
			strcpy( ( AtmPropertyShmPtr + i )->InstTerminalGroup , INSTTERMINALGROUP_INIT_VAL );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: addAtmActionPropertyMemory( int RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmPropertyShmPtr + i )->InstTerminalGroup , INSTTERMINALGROUP_INIT_VAL ) )
		{
			memset( ( AtmActionPropertyShmPtr + i ), 0, sizeof( struct EzAtmActionProperty ) );
			SqlErr = 0;
			SqlErr = ReadAtmActionPropertyTable( ( AtmActionPropertyShmPtr + i ), RecordId );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding AtmActionPropertyTable Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: updateAtmActionPropertyMemory( int RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( AtmActionPropertyShmPtr + i )->RecordId == RecordId )
		{
			memset( ( AtmActionPropertyShmPtr + i ), 0, sizeof( struct EzAtmActionProperty ) );
			SqlErr = 0;
			SqlErr = ReadAtmActionPropertyTable( ( AtmActionPropertyShmPtr + i ), RecordId );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding AtmActionProperty Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: removeAtmActionPropertyMemory( int RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( ( AtmActionPropertyShmPtr + i )->RecordId == RecordId )
		{
			memset( ( AtmActionPropertyShmPtr + i ), 0, sizeof( struct EzAtmActionProperty ) );
			strcpy( ( AtmActionPropertyShmPtr + i )->InstTerminalGroup , INSTTERMINALGROUP_INIT_VAL );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmActionPropertySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmActionProperty Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: addAtmStatusMemory( const char *StatusCode )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxStatus; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for Atm Status Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmStatusShmPtr + i )->StatusCode , STATUS_INIT_CODE ) )
		{
			memset( ( AtmStatusShmPtr + i ), 0, sizeof( struct EzAtmStatus ) );
			SqlErr = 0;
			SqlErr = ReadAtmStatusTable( ( AtmStatusShmPtr + i ), StatusCode );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in adding EzAtmStatusDesc Table Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	return retval;
}

int EzAtmMgrUtil :: updateAtmStatusMemory( const char *StatusCode )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxStatus; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmStatusShmPtr + i )->StatusCode, StatusCode ) )
		{
			memset( ( AtmStatusShmPtr + i ), 0, sizeof( struct EzAtmStatus ) );
			SqlErr = 0;
			SqlErr = ReadAtmStatusTable( ( AtmStatusShmPtr + i ), StatusCode );
			if( SqlErr != 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in updating AtmStatus Record SqlErr[%05d]", SqlErr );
				return -1;
			}
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: removeAtmStatusMemory( const char *StatusCode )
{
	int retval = -1;
	struct sembuf sem_buf;

	for( int i = 0; i < MaxStatus; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmStatusShmPtr + i )->StatusCode, StatusCode ) )
		{
			memset( ( AtmStatusShmPtr + i ), 0, sizeof( struct EzAtmStatus ) );
			strcpy( ( AtmStatusShmPtr + i )->StatusCode , STATUS_INIT_CODE );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmStatusSemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmStatus Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: LoadAtmInfo( struct AtmMemoryTable *AtmMemoryPtr, int AtmCount )
{
	struct AtmTableInfo atmtableinfo;
	struct ATMSharedBuffer atmbuf;
	struct DenomInfo denominfo[9];
    char StaticStatus[ 101 ];

    if( LoadAtmId( AtmMemoryPtr ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading AtmId's... OraErr[%05d]", SqlErr );
		return -1;
	}

  	for( int i = 0; i < AtmCount; i ++ )
	{
		memset( &atmtableinfo, 0, sizeof( struct AtmTableInfo ) );

		if( LoadAtmInfoTables( &atmtableinfo, ( AtmMemoryPtr + i )->AtmId ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while Loading AtmInfo Tables AtmId[%s]", ( AtmMemoryPtr + i )->AtmId );
			memset( ( AtmMemoryShmPtr + i )->AtmId, 0, sizeof( ( AtmMemoryShmPtr + i )->AtmId ) );
			strcpy( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME );
			continue;
		}

		if( strcmp( atmtableinfo.AtmTypeId, TRITON ) )
		{
			memset( &denominfo, 0, sizeof( struct DenomInfo ) * 8 );
			if( LoadAtmDenomInfo( ( AtmMemoryPtr + i )->AtmId, denominfo ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while Loading Denomination Status AtmId[%s]", ( AtmMemoryPtr + i )->AtmId );
				memset( ( AtmMemoryShmPtr + i )->AtmId, 0, sizeof( ( AtmMemoryShmPtr + i )->AtmId ) );
				strcpy( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME );
				continue;
			}

			memset( StaticStatus, 0, sizeof( StaticStatus ) );
			if( LoadAtmStaticStatus( ( AtmMemoryPtr + i )->AtmId, StaticStatus ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while Loading Static Status AtmId[%s]", ( AtmMemoryPtr + i )->AtmId );
				memset( ( AtmMemoryShmPtr + i )->AtmId, 0, sizeof( ( AtmMemoryShmPtr + i )->AtmId ) );
				strcpy( ( AtmMemoryShmPtr + i )->AtmId, ATMID_INIT_NAME );
				continue;
			}

			memset( &( AtmMemoryPtr + i )->AtmInfoBuffer, 0,  sizeof( struct AtmTableInfo ) );
			memcpy( &( AtmMemoryPtr + i )->AtmInfoBuffer, &atmtableinfo, sizeof( struct AtmTableInfo ) );

 			memset( &atmbuf, 0, sizeof( struct ATMSharedBuffer ) );
			memcpy( atmbuf.denominfo, &denominfo, sizeof( struct DenomInfo ) * 9 );

			strcpy( atmbuf.StaticStatus, StaticStatus );

			memset( &( AtmMemoryPtr + i )->AtmSharedBuffer, 0, sizeof( struct ATMSharedBuffer ) );
			memcpy( &( AtmMemoryPtr + i )->AtmSharedBuffer, &atmbuf, sizeof( struct ATMSharedBuffer ) );
		}
	}
	return 1;
}

int EzAtmMgrUtil :: LoadAtmInfoTables( struct AtmTableInfo *Atmtableinfo_ptr , char *AtmId )
{
	SqlErr = LoadAtm( Atmtableinfo_ptr, AtmId );

	if( SqlErr != 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading AtmTable OraErr[%05d] -- AtmId[%s]", SqlErr, AtmId );
		return -1;
	}

	Atmtableinfo_ptr->TraceNum = GetTraceNum( AtmId );
	if( SqlErr != 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading AtmTraceNo Table OraErr[%05d] -- AtmId[%s]", SqlErr, AtmId );
		return -1;
	}

	SqlErr = LoadAtmBatchId( AtmId, Atmtableinfo_ptr->BatchId );
	if( SqlErr != 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading BatchId Table OraErr[%05d] -- AtmId[%s]", SqlErr, AtmId );
		return -1;
	}

	if( getInstTermGroup( Atmtableinfo_ptr->AcquirerInst, Atmtableinfo_ptr->InstTerminalGroup ) < 0 )
	{
		dptr->trace( DEBUG_ERROR,"Error while Loading InstTerminalGroup for InstId[%s] ", Atmtableinfo_ptr->AcquirerInst );
		return -1;
	}
	return 1;
}

int EzAtmMgrUtil :: LoadAtmDenomInfo( const char *AtmId, struct DenomInfo *denominfo_ptr )
{
	for( int j=0, i = 0x41; i <= 0x48; i++,j++ )
	{
		memset( ( denominfo_ptr + j ), 0, sizeof( struct DenomInfo ) );
        ( denominfo_ptr + j )->DenomId = i;
        SqlErr = LoadAtmDenom( AtmId, denominfo_ptr + j );
    	//dptr->trace( DEBUG_TEST, "Id[%c] Pos[%d] Value[%4d] Status[%c] Code[%3d] LastDispNotes[%d]", (denominfo_ptr + j)->DenomId, (denominfo_ptr + j)->CassPosition, (denominfo_ptr + j)->CurrencyValue, (denominfo_ptr + j)->Status, (denominfo_ptr + j)->CurrencyCode, (denominfo_ptr + j)->LastDispNotes );
    	if( SqlErr != 0 )
    	{
    		dptr->trace( DEBUG_ERROR, "Error in Loading DenomInfo ORA: [ %05d ] for Denom[%c]", SqlErr, ( denominfo_ptr + j )->DenomId );
    		return -1;
    	}
	}
   	return 1;
}

int EzAtmMgrUtil :: LoadAtmStaticStatus( const char *AtmId, char *StaticStatus )
{
	int retval = -1;

	SqlErr = LoadAtmStaticCode( AtmId, StaticStatus );

	if( SqlErr == 0 )
		retval = 1;
	else
		dptr->trace( DEBUG_ERROR, "Error in Loading StaticStatus: ORA:[ %05d ]", SqlErr );

	return retval;
}

int EzAtmMgrUtil :: cleanATMSharedBuffer( const char *AtmId )
{
	int retval = -1;
	struct sembuf sem_buf;
	for( int i = 0; i < MaxAtms; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AtmMemoryShmPtr + i )->AtmId, AtmId ) )
		{
			memset( &( AtmMemoryShmPtr + i )->AtmSharedBuffer, 0, sizeof( struct ATMSharedBuffer ) );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AtmMemorySemid, &sem_buf, 1 ) < 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error while doing semop for AtmMemory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzAtmMgrUtil :: UpdateATMStatusTable( struct AtmStatusMsg *atmstatus_ptr )
{
	int SqlErr =-1;

	SqlErr = UpdateATMStatus( atmstatus_ptr->StaticCode, atmstatus_ptr->DynamicCode, atmstatus_ptr->AtmId, atmstatus_ptr->Date, atmstatus_ptr->Time );
	if( SqlErr != 1403 )
	{
		/*if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
		{
			if( dbutil_ptr->DBConnect() < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in Connecting with Switch DB....Cannot Update EZATMSTATUS" );
				return -1;
			}
			SqlErr = UpdateATMStatus( atmstatus_ptr->StaticCode, atmstatus_ptr->DynamicCode, atmstatus_ptr->AtmId, atmstatus_ptr->Date, atmstatus_ptr->Time );
		}*/
		if( SqlErr != 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in updating the EZATMSTATUS table OraErr[ %05d ]", SqlErr );
			return -1;
		}
	}
	else
	{
		SqlErr = InsertATMStatus( atmstatus_ptr->StaticCode, atmstatus_ptr->DynamicCode, atmstatus_ptr->AtmId, atmstatus_ptr->Date, atmstatus_ptr->Time );
		/*if( EZBUSINESS_ORA_CONNECT_ERR( SqlErr ) )
		{
			if( dbutil_ptr->DBConnect() < 0 )
			{
				dptr->trace( DEBUG_ERROR,"Error in Connecting with Switch DB....Cannot Update EZATMSTATUS" );
				return -1;
			}
			SqlErr = InsertATMStatus( atmstatus_ptr->StaticCode, atmstatus_ptr->DynamicCode, atmstatus_ptr->AtmId, atmstatus_ptr->Date, atmstatus_ptr->Time );
		}*/
		if( SqlErr != 0 )
		{
			dptr->trace( DEBUG_ERROR,"Error in Inserting the EZATMSTATUSHIST table OraErr[ %05d ]", SqlErr );
			return -1;
		}
	}
	return 1;
}
