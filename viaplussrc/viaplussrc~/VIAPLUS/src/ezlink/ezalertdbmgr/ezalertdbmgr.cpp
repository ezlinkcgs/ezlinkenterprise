#include <ezlink/ezalertdbmgr.h>

void EzAlertDBMgr :: initAlertDBMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzDBUtil dbutil;
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezalertdbmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another AlertDBance of EzAlertDBMgr Already Running...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezalert.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Erron in Opening file[%s]...", cfgpath );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTDB#MAXSTATUSALERT", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTDB#MAXSTATUSALERT from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	MaxStatusAlert = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTDB#MAXSMSALERTGROUP", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTDB#MAXSMSALERTGROUP from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	MaxSMSAlertGroup = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTDB#MAXMAILALERTGROUP", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTDB#MAXMAILALERTGROUP from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	MaxMailAlertGroup = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTDB#MAXALERTINFO", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTDB#MAXALERTINFO from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	MaxAlertInfo = atoi( cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALERTDB#MAXALERTDESC", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALERTDB#MAXALERTDESC from file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}
	MaxAlertDesc = atoi( cfgval );

	cfgutil.cfg_close();

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzDBUtil..." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch Database" );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadStatusAlert() < 0 )
	{
		trace( "Error in Loading StatusAlert Table...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadSMSAlertGroup() < 0 )
	{
		trace( "Error in Loading SMSAlertGroup Table...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadMailAlertGroup() < 0 )
	{
		trace( "Error in Loading MailAlertGroup Table...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadAlertInfo() < 0 )
	{
		trace( "Error in Loading AlertInfo Table...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadAlertSeqMemory() < 0 )
	{
		trace( "Error in Loading AlertSeqMemory ...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( LoadAlertDesc() < 0 )
	{
		trace( "Error in Loading AlertDes ...." );
		trace( "^^^^^^^^^^^EzAlertDBMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	dbutil.DBClose();
	TaskInit();
	initEzSigUtil( this );
}

int EzAlertDBMgr :: LoadAlertSeqMemory()
{
	AlertSeqMemoryId = CreateMemoryId( this, "ALERTSEQMEMORY" );

	if( AlertSeqMemoryId < 0 )
	{
		trace( "Error in Creating ALERTSEQMEMORY..." );
		return -1;
	}

	AlertSeqShmId = shmget ( ( key_t ) AlertSeqMemoryId, sizeof( struct EzAlertSeqMemory ), IPC_CREAT | 0666 );

	if( AlertSeqShmId < 0 )
	{
		trace( "Error in Creating EzAlertSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AlertSeqShmPtr = ( struct EzAlertSeqMemory * ) shmat( AlertSeqShmId, 0, 0 );

	if( AlertSeqShmPtr == NULL )
	{
		trace( "Error in attaching EzAlertSeq Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AlertSeqSemId = semget ( ( key_t ) AlertSeqMemoryId, 1, IPC_CREAT | 0666 );

	if( AlertSeqSemId < 0 )
	{
		trace( "Error in Creating EzAlertSeq Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
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

	if( semctl( AlertSeqSemId, 0, SETVAL, arg ) < 0 )
	{
		trace( "Error in Setting Network Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	if( LoadSMSAlertSeqNo() < 0 )
		return -1;

	if( LoadMailAlertSeqNo() < 0 )
			return -1;

	return 1;
}

int EzAlertDBMgr :: LoadSMSAlertSeqNo()
{
	struct sembuf sem_buf;
	FILE *alertseq_fptr;
	char AlertSeqPath[ ALERT_SEQ_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( AlertSeqSemId, &sem_buf, 1 ) < 0 )
	{
		trace( "Error in Semop for AlertSeqSemId..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( AlertSeqPath, 0, sizeof( AlertSeqPath ) );
	sprintf( AlertSeqPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "SMSAlertSeqNo.dat" );

	alertseq_fptr = fopen( AlertSeqPath, "r" );

	if( alertseq_fptr == NULL )
	{
		alertseq_fptr = fopen( AlertSeqPath, "w" );
		if( alertseq_fptr == NULL )
		{
			trace( "Error in Opening File [%s]", AlertSeqPath );
			return -1;
		}
		memset( AlertSeqShmPtr->SMSAlertSeqNo, 0, sizeof( AlertSeqShmPtr->SMSAlertSeqNo ) );
		ezsequtil.InitSeqNo( AlertSeqShmPtr->SMSAlertSeqNo, 20 );
		ezsequtil.GenNextSeqNo( AlertSeqShmPtr->SMSAlertSeqNo );
		fprintf( alertseq_fptr, "%s", AlertSeqShmPtr->SMSAlertSeqNo );
		fclose( alertseq_fptr );
	}
	else
	{
		memset( AlertSeqShmPtr->SMSAlertSeqNo, 0, sizeof( AlertSeqShmPtr->SMSAlertSeqNo ) );
		fscanf( alertseq_fptr, "%s", AlertSeqShmPtr->SMSAlertSeqNo );
		if( !strlen( AlertSeqShmPtr->SMSAlertSeqNo ) )
		{
			memset( AlertSeqShmPtr->SMSAlertSeqNo, 0, sizeof( AlertSeqShmPtr->SMSAlertSeqNo ) );
			ezsequtil.InitSeqNo( AlertSeqShmPtr->SMSAlertSeqNo, 20 );
			ezsequtil.GenNextSeqNo( AlertSeqShmPtr->SMSAlertSeqNo );
			fprintf( alertseq_fptr, "%s", AlertSeqShmPtr->SMSAlertSeqNo );
		}
		fclose( alertseq_fptr );
	}

	sem_buf.sem_op = 2;
	if( semop( AlertSeqSemId, &sem_buf, 1 ) < 0 )
	{
		trace( "Error in Semop for AlertSeqSemId...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	return 1;
}

int EzAlertDBMgr :: LoadMailAlertSeqNo()
{
	struct sembuf sem_buf;
	FILE *alertseq_fptr;
	char AlertSeqPath[ ALERT_SEQ_PATH_SIZE + 1 ];

	sem_buf.sem_num = 0;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -2;

	if( semop( AlertSeqSemId, &sem_buf, 1 ) < 0 )
	{
		trace( "Error in Semop for AlertSeqSemId..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	memset( AlertSeqPath, 0, sizeof( AlertSeqPath ) );
	sprintf( AlertSeqPath, "%s/%s/%s", getenv( "EZDIR_HOME"), "inf", "MailAlertSeqNo.dat" );

	alertseq_fptr = fopen( AlertSeqPath, "r" );

	if( alertseq_fptr == NULL )
	{
		alertseq_fptr = fopen( AlertSeqPath, "w" );
		if( alertseq_fptr == NULL )
		{
			trace( "Error in Opening File [%s]", AlertSeqPath );
			return -1;
		}
		memset( AlertSeqShmPtr->MailAlertSeqNo, 0, sizeof( AlertSeqShmPtr->MailAlertSeqNo ) );
		ezsequtil.InitSeqNo( AlertSeqShmPtr->MailAlertSeqNo, 20 );
		ezsequtil.GenNextSeqNo( AlertSeqShmPtr->MailAlertSeqNo );
		fprintf( alertseq_fptr, "%s", AlertSeqShmPtr->MailAlertSeqNo );
		fclose( alertseq_fptr );
	}
	else
	{
		memset( AlertSeqShmPtr->MailAlertSeqNo, 0, sizeof( AlertSeqShmPtr->MailAlertSeqNo ) );
		fscanf( alertseq_fptr, "%s", AlertSeqShmPtr->MailAlertSeqNo );
		if( !strlen( AlertSeqShmPtr->MailAlertSeqNo ) )
		{
			memset( AlertSeqShmPtr->MailAlertSeqNo, 0, sizeof( AlertSeqShmPtr->MailAlertSeqNo ) );
			ezsequtil.InitSeqNo( AlertSeqShmPtr->MailAlertSeqNo, 20 );
			ezsequtil.GenNextSeqNo( AlertSeqShmPtr->MailAlertSeqNo );
			fprintf( alertseq_fptr, "%s", AlertSeqShmPtr->MailAlertSeqNo );
		}
		fclose( alertseq_fptr );
	}
	sem_buf.sem_op = 2;
	if( semop( AlertSeqSemId, &sem_buf, 1 ) < 0 )
	{
		trace( "Error in Semop for AlertSeqSemId...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

int EzAlertDBMgr :: LoadAlertDesc()
{
	AlertDescMemoryId = CreateMemoryId( this, "ALERTDESCMEMORY" );

	if( AlertDescMemoryId < 0 )
	{
		trace( "Error in Creating ALERTDESCMEMORY..." );
		return -1;
	}

	AlertDescShmId = shmget ( ( key_t ) AlertDescMemoryId, sizeof( struct EzAlertDescMemory ) * MaxAlertDesc, IPC_CREAT | 0666 );

	if( AlertDescShmId < 0 )
	{
		trace( "Error in Creating AlertDesc Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AlertDescShmPtr = ( struct EzAlertDescMemory * ) shmat( AlertDescShmId, 0, 0 );

	if( AlertDescShmPtr == NULL )
	{
		trace( "Error in attaching AlertDesc Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AlertDescSemId = semget ( ( key_t ) AlertDescMemoryId, MaxAlertDesc, IPC_CREAT | 0666 );

	if( AlertDescSemId < 0 )
	{
		trace( "Error in Creating AlertDesc Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	trace( DEBUG_TEST, "AlertDesc Semaphore Created with SemId[%d]", AlertDescSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxAlertDesc; i++ )
	{
		if( semctl( AlertDescSemId, i, SETVAL, arg ) < 0 )
		{
			trace( "Error in Setting AlertDesc Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxAlertDesc; i++ )
	{
		memset( ( AlertDescShmPtr + i ), 0, sizeof( struct EzAlertDescMemory ) );
		strcpy( ( AlertDescShmPtr + i )->RecordId, ALERT_RECORD_INIT_VAL );
	}

	int SqlErr;
	int AlertDescCount = getEzAlertDescCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		trace( "Error in Getting EzAlertDesc Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( AlertDescCount > MaxAlertDesc )
	{
		trace( "AlertDescCount[%d] > MaxAlertDesc[%d]", AlertDescCount, MaxAlertDesc );
		return -1;
	}

	if( LoadEzAlertDesc( AlertDescShmPtr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzAlertDesc......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}


int EzAlertDBMgr :: LoadStatusAlert()
{
	StatusAlertMemoryId = CreateMemoryId( this, "STATUSALERTMEMORY" );

	if( StatusAlertMemoryId < 0 )
	{
		trace( "Error in Creating INSTROUTETYPEMEMORY..." );
		return -1;
	}

	StatusAlertShmId = shmget ( ( key_t ) StatusAlertMemoryId, sizeof( struct EzStatusAlertMemory ) * MaxStatusAlert, IPC_CREAT | 0666 );

	if( StatusAlertShmId < 0 )
	{
		trace( "Error in Creating StatusAlert Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StatusAlertShmPtr = ( struct EzStatusAlertMemory * ) shmat( StatusAlertShmId, 0, 0 );

	if( StatusAlertShmPtr == NULL )
	{
		trace( "Error in attaching StatusAlert Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	StatusAlertSemId = semget ( ( key_t ) StatusAlertMemoryId, MaxStatusAlert, IPC_CREAT | 0666 );

	if( StatusAlertSemId < 0 )
	{
		trace( "Error in Creating StatusAlert Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	trace( DEBUG_TEST, "StatusAlert Semaphore Created with SemId[%d]", StatusAlertSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxStatusAlert; i++ )
	{
		if( semctl( StatusAlertSemId, i, SETVAL, arg ) < 0 )
		{
			trace( "Error in Setting StatusAlert Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxStatusAlert; i++ )
	{
		memset( ( StatusAlertShmPtr + i ), 0, sizeof( struct EzStatusAlertMemory ) );
		strcpy( ( StatusAlertShmPtr + i )->RecordId, ALERT_RECORD_INIT_VAL );
	}

	int SqlErr;
	int StatusAlertCount = getEzStatusAlertCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		trace( "Error in Getting EzStatusAlert Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( StatusAlertCount > MaxStatusAlert )
	{
		trace( "StatusAlertCount[%d] > MaxStatusAlert[%d]", StatusAlertCount, MaxStatusAlert );
		return -1;
	}

	if( LoadEzStatusAlert( StatusAlertShmPtr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzStatusAlert......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzAlertDBMgr :: LoadSMSAlertGroup()
{
	SMSAlertGroupMemoryId = CreateMemoryId( this, "SMSALERTGROUPMEMORY" );

	if( SMSAlertGroupMemoryId < 0 )
	{
		trace( "Error in Creating SMSALERTGROUPMEMORY..." );
		return -1;
	}

	SMSAlertGroupShmId = shmget ( ( key_t ) SMSAlertGroupMemoryId, sizeof( struct EzSMSAlertGroupMemory ) * MaxSMSAlertGroup, IPC_CREAT | 0666 );

	if( SMSAlertGroupShmId < 0 )
	{
		trace( "Error in Creating SMSAlertGroup Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SMSAlertGroupShmPtr = ( struct EzSMSAlertGroupMemory * ) shmat( SMSAlertGroupShmId, 0, 0 );

	if( SMSAlertGroupShmPtr == NULL )
	{
		trace( "Error in attaching SMSAlertGroup Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	SMSAlertGroupSemId = semget ( ( key_t ) SMSAlertGroupMemoryId, MaxSMSAlertGroup, IPC_CREAT | 0666 );

	if( SMSAlertGroupSemId < 0 )
	{
		trace( "Error in Creating SMSAlertGroup Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	trace( DEBUG_TEST, "SMSAlertGroup Semaphore Created with SemId[%d]", SMSAlertGroupSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxSMSAlertGroup; i++ )
	{
		if( semctl( SMSAlertGroupSemId, i, SETVAL, arg ) < 0 )
		{
			trace( "Error in Setting SMSAlertGroup Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxSMSAlertGroup; i++ )
	{
		memset( ( SMSAlertGroupShmPtr + i ), 0, sizeof( struct EzSMSAlertGroupMemory ) );
		strcpy( ( SMSAlertGroupShmPtr + i )->SMSAlertGroupId, ALERT_RECORD_INIT_VAL );
	}

	int SqlErr;
	int SMSAlertGroupCount = getEzSMSAlertGroupCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		trace( "Error in Getting EzSMSAlertGroup Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( SMSAlertGroupCount > MaxSMSAlertGroup )
	{
		trace( "SMSAlertGroupCount[%d] > MaxSMSAlertGroup[%d]", SMSAlertGroupCount, MaxSMSAlertGroup );
		return -1;
	}

	if( LoadEzSMSAlertGroup( SMSAlertGroupShmPtr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzSMSAlertGroup......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzAlertDBMgr :: LoadMailAlertGroup()
{
	MailAlertGroupMemoryId = CreateMemoryId( this, "MAILALERTGROUPMEMORY" );

	if( MailAlertGroupMemoryId < 0 )
	{
		trace( "Error in Creating MAILALERTGROUPMEMORY..." );
		return -1;
	}

	MailAlertGroupShmId = shmget ( ( key_t ) MailAlertGroupMemoryId, sizeof( struct EzMailAlertGroupMemory ) * MaxMailAlertGroup, IPC_CREAT | 0666 );

	if( MailAlertGroupShmId < 0 )
	{
		trace( "Error in Creating MailAlertGroup Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MailAlertGroupShmPtr = ( struct EzMailAlertGroupMemory * ) shmat( MailAlertGroupShmId, 0, 0 );

	if( MailAlertGroupShmPtr == NULL )
	{
		trace( "Error in attaching MailAlertGroup Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MailAlertGroupSemId = semget ( ( key_t ) MailAlertGroupMemoryId, MaxMailAlertGroup, IPC_CREAT | 0666 );

	if( MailAlertGroupSemId < 0 )
	{
		trace( "Error in Creating MailAlertGroup Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	trace( DEBUG_TEST, "MailAlertGroup Semaphore Created with SemId[%d]", MailAlertGroupSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxMailAlertGroup; i++ )
	{
		if( semctl( MailAlertGroupSemId, i, SETVAL, arg ) < 0 )
		{
			trace( "Error in Setting MailAlertGroup Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxMailAlertGroup; i++ )
	{
		memset( ( MailAlertGroupShmPtr + i ), 0, sizeof( struct EzMailAlertGroupMemory ) );
		strcpy( ( MailAlertGroupShmPtr + i )->MailAlertGroupId, ALERT_RECORD_INIT_VAL );
	}

	int SqlErr;
	int MailAlertGroupCount = getEzMailAlertGroupCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		trace( "Error in Getting EzMailAlertGroup Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( MailAlertGroupCount > MaxMailAlertGroup )
	{
		trace( "AlertGroupCount[%d] > MaxMailAlertGroup[%d]", MailAlertGroupCount, MaxMailAlertGroup );
		return -1;
	}

	if( LoadEzMailAlertGroup( MailAlertGroupShmPtr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzMailAlertGroup......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}

int EzAlertDBMgr :: LoadAlertInfo()
{
	AlertInfoMemoryId = CreateMemoryId( this, "ALERTINFOMEMORY" );

	if( AlertInfoMemoryId < 0 )
	{
		trace( "Error in Creating INSTROUTETYPEMEMORY..." );
		return -1;
	}

	AlertInfoShmId = shmget ( ( key_t ) AlertInfoMemoryId, sizeof( struct EzAlertInfoMemory ) * MaxAlertInfo, IPC_CREAT | 0666 );

	if( AlertInfoShmId < 0 )
	{
		trace( "Error in Creating AlertInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AlertInfoShmPtr = ( struct EzAlertInfoMemory * ) shmat( AlertInfoShmId, 0, 0 );

	if( AlertInfoShmPtr == NULL )
	{
		trace( "Error in attaching AlertInfo Shared Memory..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	AlertInfoSemId = semget ( ( key_t ) AlertInfoMemoryId, MaxAlertInfo, IPC_CREAT | 0666 );

	if( AlertInfoSemId < 0 )
	{
		trace( "Error in Creating AlertInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	trace( DEBUG_TEST, "AlertInfo Semaphore Created with SemId[%d]", AlertInfoSemId );

	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	union semun arg;
	arg.val = 2;

	for( int i = 0; i < MaxAlertInfo; i++ )
	{
		if( semctl( AlertInfoSemId, i, SETVAL, arg ) < 0 )
		{
			trace( "Error in Setting AlertInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}

	for( int i = 0; i < MaxAlertInfo; i++ )
	{
		memset( ( AlertInfoShmPtr + i ), 0, sizeof( struct EzAlertInfoMemory ) );
		strcpy( ( AlertInfoShmPtr + i )->RecordId, ALERT_RECORD_INIT_VAL );
	}

	int SqlErr;
	int AlertInfoCount = getEzAlertInfoCount( &SqlErr );

	if( SqlErr!= 0 )
	{
		trace( "Error in Getting EzAlertInfo Table Count...SqlErr[%05d]", SqlErr );
		return -1;
	}

	if( AlertInfoCount > MaxAlertInfo )
	{
		trace( "AlertInfoCount[%d] > MaxAlertInfo[%d]", AlertInfoCount, MaxAlertInfo );
		return -1;
	}

	if( LoadEzAlertInfo( AlertInfoShmPtr, &SqlErr ) < 0 )
	{
		trace( "Error in Loading EzAlertInfo......OraErr[%05d]", SqlErr );
		return -1;
	}
	return 1;
}


void EzAlertDBMgr :: serviceRequest()
{
	while( 1 )
	{
		pause();
	}
}

int main( int argc, char **argv )
{
	EzAlertDBMgr alertdbmgrobj;
	alertdbmgrobj.initAlertDBMgr( argv[ 0 ] );
	alertdbmgrobj.serviceRequest();
	return 1;
}




