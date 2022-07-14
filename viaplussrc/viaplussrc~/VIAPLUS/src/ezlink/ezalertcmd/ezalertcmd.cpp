#include <ezlink/ezalertcmd.h>

void EzAlertCmd :: initAlertCmd()
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezalertcmd.log" );

	if( openCmdDebug( logpath, "ezalertcmd" ) < 0 )
		exit( 0 );

	if( InitEzChLocateUtil( this, "EzAlertCmd" )  < 0 )
	{
		printf("\nError in Initializing EzChLocateUtil...." );
		closeDebug();
		exit( 0 );
	}

	if( LocateChannel( "EzAlertMgr" ) < 0 )
	{
		printf("\nError in Locating Channel EzAlertMgr...." );
		closeDebug();
		exit( 0 );
	}

	if( initAlertMemUtil( this ) < 0 )
	{
		printf("\nError in Initializing AlertMemUtil...." );
		closeDebug();
		exit( 0 );
	}

	if( LoadStatusAlert() < 0 )
	{
		printf("\nError in Initializing AlertMemUtil...." );
		closeDebug();
		exit( 0 );

	}

	if( LoadSMSAlertGroup() < 0 )
	{
		printf("\nError in Looading SMSAlertGroup...." );
		closeDebug();
		exit( 0 );
	}

	if( LoadMailAlertGroup() < 0 )
	{
		printf("\nError in Loading MailAlertGroup...." );
		closeDebug();
		exit( 0 );
	}

	if( LoadAlertInfo() < 0 )
	{
		printf("\nError in Loading LoadAlertInfo...." );
		closeDebug();
		exit( 0 );
	}

	if( LoadAlertDesc() < 0 )
	{
		printf("\nError in Loading LoadAlertDesc...." );
		closeDebug();
		exit( 0 );
	}
}

int EzAlertCmd :: serviceAddStatusAlert( const char *RecordId )
{
	struct EzStatusAlertMemory statusalert_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &statusalert_rec, 0, sizeof( struct EzStatusAlertMemory ) );
	retval = readEzStatusAlert( RecordId, &statusalert_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading RecordId[%s] from EzStatusAlert....OraErr[%05d]\n", RecordId, retval );
		trace( "Error in Reading RecordId[%s] from EzStatusAlert....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	if( addStatusAlert( statusalert_rec ) < 0 )
	{
		printf( "Error in Adding RecordId[%s] in EzStatusAlertMemory\n", RecordId );
		trace( "Error in Adding RecordId[%s] in EzStatusAlertMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceUpdateStatusAlert( const char *RecordId )
{
	struct EzStatusAlertMemory statusalert_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &statusalert_rec, 0, sizeof( struct EzStatusAlertMemory ) );
	retval = readEzStatusAlert( RecordId, &statusalert_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading RecordId[%s] from EzStatusAlert....OraErr[%05d]\n", RecordId, retval );
		trace( "Error in Reading RecordId[%s] from EzStatusAlert....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	if( updateStatusAlert( statusalert_rec ) < 0 )
	{
		printf( "Error in Updating RecordId[%s] in EzStatusAlertMemory\n", RecordId );
		trace( "Error in Updating RecordId[%s] in EzStatusAlertMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceDeleteStatusAlert( const char *RecordId )
{
	if( deleteStatusAlert( RecordId ) < 0 )
	{
		printf( "Error in Deleting RecordId[%s] from EzStatusAlertMemory\n", RecordId );
		trace( "Error in Deleting RecordId[%s] from EzStatusAlertMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceListStatusAlert()
{
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "\n%15s%10s%10s%32s%10s%10s%15s%15s", "RecordId", "DeviceId", "AlertType", "StatusList", "SMSReq", "MailReq", "SMSAlertGroup", "MailAlertGroup" );

	for( int i = 0; i < MaxStatusAlert; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( StatusAlertSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for StatusAlert SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( StatusAlertShmPtr + i )->RecordId, ALERT_RECORD_INIT_VAL ) )
			printf( "\n%15s%10s%10s%32s%10c%10c%15s%15s", ( StatusAlertShmPtr + i )->RecordId, ( StatusAlertShmPtr + i )->DeviceId, ( StatusAlertShmPtr + i )->AlertType, ( StatusAlertShmPtr + i )->StatusList, ( StatusAlertShmPtr + i )->SMSReq, ( StatusAlertShmPtr + i )->MailReq, ( StatusAlertShmPtr + i )->SMSAlertGroupId, ( StatusAlertShmPtr + i )->MailAlertGroupId );
		sem_buf.sem_op = 2;
		if( semop( StatusAlertSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for StatusAlert SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return 1;
}

int EzAlertCmd :: serviceListStatusAlert( const char *RecordId )
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%10s%10s%32s%10s%10s%15s%15s", "RecordId", "DeviceId", "AlertType", "StatusList", "SMSReq", "MailReq", "SMSAlertGroup", "MailAlertGroup" );

	for( int i = 0; i < MaxStatusAlert; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( StatusAlertSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for StatusAlert SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( StatusAlertShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "%15s%10s%10s%32s%10c%10c%15s%15s", ( StatusAlertShmPtr + i )->RecordId, ( StatusAlertShmPtr + i )->DeviceId, ( StatusAlertShmPtr + i )->AlertType, ( StatusAlertShmPtr + i )->StatusList, ( StatusAlertShmPtr + i )->SMSReq, ( StatusAlertShmPtr + i )->MailReq, ( StatusAlertShmPtr + i )->SMSAlertGroupId, ( StatusAlertShmPtr + i )->MailAlertGroupId );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( StatusAlertSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for StatusAlert SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( StatusAlertSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for StatusAlert SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return retval;
}

int EzAlertCmd :: serviceAddSMSAlertGroup( const char *SMSAlertGroupId )
{
	struct EzSMSAlertGroupMemory smsalertgroup_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &smsalertgroup_rec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
	retval = readEzSMSAlertGroup( SMSAlertGroupId, &smsalertgroup_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading SMSAlertGroupId[%s] from EzSMSAlertGroup....OraErr[%05d]\n", SMSAlertGroupId, retval );
		trace( "Error in Reading SMSAlertGroupId[%s] from EzSMSAlertGroup....OraErr[%05d]", SMSAlertGroupId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();

	if( addSMSAlertGroup( smsalertgroup_rec ) < 0 )
	{
		printf( "Error in Adding SMSAlertGroupId[%s] in EzSMSAlertGroupMemory\n", SMSAlertGroupId );
		trace( "Error in Adding SMSAlertGroupId[%s] in EzSMSAlertGroupMemory", SMSAlertGroupId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceUpdateSMSAlertGroup( const char *SMSAlertGroupId )
{
	struct EzSMSAlertGroupMemory smsalertgroup_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &smsalertgroup_rec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
	retval = readEzSMSAlertGroup( SMSAlertGroupId, &smsalertgroup_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading SMSAlertGroupId[%s] from EzSMSAlertGroup....OraErr[%05d]\n", SMSAlertGroupId, retval );
		trace( "Error in Reading SMSAlertGroupId[%s] from EzSMSAlertGroup....OraErr[%05d]", SMSAlertGroupId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();

	if( updateSMSAlertGroup( smsalertgroup_rec ) < 0 )
	{
		printf( "Error in Updating SMSAlertGroupId[%s] in EzSMSAlertGroupMemory\n", SMSAlertGroupId );
		trace( "Error in Updating SMSAlertGroupId[%s] in EzSMSAlertGroupMemory", SMSAlertGroupId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceDeleteSMSAlertGroup( const char *SMSAlertGroupId )
{
	if( deleteSMSAlertGroup( SMSAlertGroupId ) < 0 )
	{
		printf( "Error in Deleting SMSAlertGroupId[%s] From EzSMSAlertGroupMemory\n", SMSAlertGroupId );
		trace( "Error in Deleting SMSAlertGroupId[%s] From EzSMSAlertGroupMemory", SMSAlertGroupId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceListSMSAlertGroup()
{
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%32s%32s%16s", "SMSAlertGroupId", "MobileList", "TemplateFile", "GSMPort" );

	for( int i = 0; i < MaxSMSAlertGroup; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SMSAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SMSAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( SMSAlertGroupShmPtr + i )->SMSAlertGroupId, ALERT_RECORD_INIT_VAL ) )
			printf( "\n%15s%32s%32s%16s", ( SMSAlertGroupShmPtr + i )->SMSAlertGroupId, ( SMSAlertGroupShmPtr + i )->MobileList, ( SMSAlertGroupShmPtr + i )->TemplateFile, ( SMSAlertGroupShmPtr + i )->GSMPort );
		sem_buf.sem_op = 2;
		if( semop( SMSAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SMSAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return 1;
}

int EzAlertCmd :: serviceListSMSAlertGroup( const char *SMSAlertGroupId )
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%32s%32s%16s", "SMSAlertGroupId", "MobileList", "TemplateFile", "GSMPort" );

	for( int i = 0; i < MaxSMSAlertGroup; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SMSAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SMSAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( StatusAlertShmPtr + i )->SMSAlertGroupId, SMSAlertGroupId ) )
		{
			retval = 1;
			printf( "\n%15s%32s%32s%16s", ( SMSAlertGroupShmPtr + i )->SMSAlertGroupId, ( SMSAlertGroupShmPtr + i )->MobileList, ( SMSAlertGroupShmPtr + i )->TemplateFile, ( SMSAlertGroupShmPtr + i )->GSMPort );
			sem_buf.sem_op = 2;
			if( semop( SMSAlertGroupSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for SMSAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SMSAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SMSAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return retval;
}

int EzAlertCmd :: serviceAddMailAlertGroup( const char *MailAlertGroupId )
{
	struct EzMailAlertGroupMemory mailalertgroup_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}

	memset( &mailalertgroup_rec, 0, sizeof( struct EzMailAlertGroupMemory ) );
	retval = readEzMailAlertGroup( MailAlertGroupId, &mailalertgroup_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading MailAlertGroupId[%s] from EzMailAlertGroup....OraErr[%05d]\n", MailAlertGroupId, retval );
		trace( "Error in Reading MailAlertGroupId[%s] from EzMailAlertGroup....OraErr[%05d]", MailAlertGroupId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();

	if( addMailAlertGroup( mailalertgroup_rec ) < 0 )
	{
		printf( "Error in Adding MailAlertGroupId[%s] in EzMailAlertGroupMemory\n", MailAlertGroupId );
		trace( "Error in Adding MailAlertGroupId[%s] in EzMailAlertGroupMemory", MailAlertGroupId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceUpdateMailAlertGroup( const char *MailAlertGroupId )
{
	struct EzMailAlertGroupMemory mailalertgroup_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}

	memset( &mailalertgroup_rec, 0, sizeof( struct EzMailAlertGroupMemory ) );
	retval = readEzMailAlertGroup( MailAlertGroupId, &mailalertgroup_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading MailAlertGroupId[%s] from EzMailAlertGroup....OraErr[%05d]\n", MailAlertGroupId, retval );
		trace( "Error in Reading MailAlertGroupId[%s] from EzMailAlertGroup....OraErr[%05d]", MailAlertGroupId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();

	if( updateMailAlertGroup( mailalertgroup_rec ) < 0 )
	{
		printf( "Error in Updating MailAlertGroupId[%s] in EzMailAlertGroupMemory\n", MailAlertGroupId );
		trace( "Error in Updating MailAlertGroupId[%s] in EzMailAlertGroupMemory", MailAlertGroupId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceDeleteMailAlertGroup( const char *MailAlertGroupId )
{
	if( deleteMailAlertGroup( MailAlertGroupId ) < 0 )
	{
		printf( "Error in Deleting MailAlertGroupId[%s] in EzMailAlertGroupMemory\n", MailAlertGroupId );
		trace( "Error in Deleting MailAlertGroupId[%s] in EzMailAlertGroupMemory", MailAlertGroupId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceListMailAlertGroup()
{
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "\n%15s%32s%32s%32s%32s", "MailAlertGroupId", "FromAddress", "ToList", "CCList", "Subject", "TemplateFile" );

	for( int i = 0; i < MaxMailAlertGroup; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( MailAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for MailAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( MailAlertGroupShmPtr + i )->MailAlertGroupId, ALERT_RECORD_INIT_VAL ) )
			printf( "%15s%32s%32s%32s%32s", ( MailAlertGroupShmPtr + i )->MailAlertGroupId, ( MailAlertGroupShmPtr + i )->FromAddress, ( MailAlertGroupShmPtr + i )->ToList, ( MailAlertGroupShmPtr + i )->CCList, ( MailAlertGroupShmPtr + i )->Subject, ( MailAlertGroupShmPtr + i )->TemplateFile );
		sem_buf.sem_op = 2;
		if( semop( MailAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for MailAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return 1;
}

int EzAlertCmd :: serviceListMailAlertGroup( const char *MailAlertGroupId )
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%32s%32s%32s%32s", "MailAlertGroupId", "FromAddress", "ToList", "CCList", "Subject", "TemplateFile" );

	for( int i = 0; i < MaxMailAlertGroup; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( MailAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for MailAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( MailAlertGroupShmPtr + i )->MailAlertGroupId, MailAlertGroupId ) )
		{
			printf( "\n%15s%32s%32s%32s%32s", ( MailAlertGroupShmPtr + i )->MailAlertGroupId, ( MailAlertGroupShmPtr + i )->FromAddress, ( MailAlertGroupShmPtr + i )->ToList, ( MailAlertGroupShmPtr + i )->CCList, ( MailAlertGroupShmPtr + i )->Subject, ( MailAlertGroupShmPtr + i )->TemplateFile );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( MailAlertGroupSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for MailAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( MailAlertGroupSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for MailAlertGroup SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return retval;
}

int EzAlertCmd :: serviceAddAlertInfo( const char *RecordId )
{
	struct EzAlertInfoMemory alertinfo_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &alertinfo_rec, 0, sizeof( struct EzAlertInfoMemory ) );
	retval = readEzAlertInfo( RecordId, &alertinfo_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading RecordId[%s] from EzAlertInfo....OraErr[%05d]\n", RecordId, retval );
		trace( "Error in Reading RecordId[%s] from EzAlertInfo....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	if( addAlertInfo( alertinfo_rec ) < 0 )
	{
		printf( "Error in Adding RecordId[%s] in EzAlertInfoMemory\n", RecordId );
		trace( "Error in Adding RecordId[%s] in EzAlertInfoMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceUpdateAlertInfo( const char *RecordId )
{
	struct EzAlertInfoMemory alertinfo_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &alertinfo_rec, 0, sizeof( struct EzAlertInfoMemory ) );
	retval = readEzAlertInfo( RecordId, &alertinfo_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading RecordId[%s] from EzAlertInfo....OraErr[%05d]\n", RecordId, retval );
		trace( "Error in Reading RecordId[%s] from EzAlertInfo....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	if( updateAlertInfo( alertinfo_rec ) < 0 )
	{
		printf( "Error in Updating RecordId[%s] in EzAlertInfoMemory\n", RecordId );
		trace( "Error in Updating RecordId[%s] in EzAlertInfoMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceDeleteAlertInfo( const char *RecordId )
{
	if( deleteAlertInfo( RecordId ) < 0 )
	{
		printf( "Error in Deleting RecordId[%s] from EzAlertInfoMemory\n", RecordId );
		trace( "Error in Deleting RecordId[%s] from EzAlertInfoMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceListAlertInfo()
{
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%10s%10s%10s%15s%15s", "RecordId", "InstId", "SMSReq", "MailReq", "SMSChannel", "MailChannel" );

	for( int i = 0; i < MaxAlertInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AlertInfoSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertInfo SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( AlertInfoShmPtr + i )->RecordId, ALERT_RECORD_INIT_VAL ) )
			printf( "\n%15s%10s%10s%10s%15s%15s", ( AlertInfoShmPtr + i )->RecordId, ( AlertInfoShmPtr + i )->InstId, ( AlertInfoShmPtr + i )->SMSReq, ( AlertInfoShmPtr + i )->MailReq, ( AlertInfoShmPtr + i )->SMSChannel, ( AlertInfoShmPtr + i )->MailChannel );
		sem_buf.sem_op = 2;
		if( semop( AlertInfoSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertInfo SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return 1;
}

int EzAlertCmd :: serviceListAlertInfo( const char *RecordId )
{
	int retval = -1;
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%10s%10s%10s%15s%15s", "RecordId", "InstId", "SMSReq", "MailReq", "SMSChannel", "MailChannel" );

	for( int i = 0; i < MaxAlertInfo; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AlertInfoSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertInfo SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AlertInfoShmPtr + i )->RecordId, RecordId ) )
		{
			retval = 1;
			printf( "\n%15s%10s%10s%10s%15s%15s", ( AlertInfoShmPtr + i )->RecordId, ( AlertInfoShmPtr + i )->InstId, ( AlertInfoShmPtr + i )->SMSReq, ( AlertInfoShmPtr + i )->MailReq, ( AlertInfoShmPtr + i )->SMSChannel, ( AlertInfoShmPtr + i )->MailChannel );
			sem_buf.sem_op = 2;
			if( semop( AlertInfoSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for AlertInfo SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AlertInfoSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertInfo SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return retval;
}

int EzAlertCmd :: serviceAddAlertDesc( const char *RecordId )
{
	struct EzAlertDescMemory alertdesc_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &alertdesc_rec, 0, sizeof( struct EzAlertDescMemory ) );
	retval = readEzAlertDesc( RecordId, &alertdesc_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading RecordId[%s] from EzAlertDesc....OraErr[%05d]\n", RecordId, retval );
		trace( "Error in Reading RecordId[%s] from EzAlertDesc....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	if( addAlertDesc( alertdesc_rec ) < 0 )
	{
		printf( "Error in Adding RecordId[%s] in EzAlertDescMemory\n", RecordId );
		trace( "Error in Adding RecordId[%s] in EzAlertDescMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceUpdateAlertDesc( const char *RecordId )
{
	struct EzAlertDescMemory alertdesc_rec;
	int retval;

	if( dbutil.DBConnect() < 0 )
	{
		printf( "Error in Connecting with Switch Database\n" );
		trace( "Error in Connecting with Switch Database" );
		return -1;
	}
	memset( &alertdesc_rec, 0, sizeof( struct EzAlertDescMemory ) );
	retval = readEzAlertDesc( RecordId, &alertdesc_rec );
	if( retval != 0 )
	{
		printf( "Error in Reading RecordId[%s] from EzAlertDesc....OraErr[%05d]\n", RecordId, retval );
		trace( "Error in Reading RecordId[%s] from EzAlertDesc....OraErr[%05d]", RecordId, retval );
		dbutil.DBClose();
		return -1;
	}
	dbutil.DBClose();
	if( updateAlertDesc( alertdesc_rec ) < 0 )
	{
		printf( "Error in Updating RecordId[%s] in EzAlertDescMemory\n", RecordId );
		trace( "Error in Updating RecordId[%s] in EzAlertDescMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceDeleteAlertDesc( const char *RecordId )
{
	if( deleteAlertDesc( RecordId ) < 0 )
	{
		printf( "Error in Deleting RecordId[%s] from EzAlertDescMemory\n", RecordId );
		trace( "Error in Deleting RecordId[%s] from EzAlertDescMemory", RecordId );
		return -1;
	}
	return 1;
}

int EzAlertCmd :: serviceListAlertDesc()
{
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%10s%10s%50s", "RecordId", "DeviceType", "StatusCode", "StatusCodeDesc" );

	for( int i = 0; i < MaxAlertDesc; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AlertDescSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertDesc SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( strcmp( ( AlertDescShmPtr + i )->RecordId, ALERT_RECORD_INIT_VAL ) )
			printf( "%15s%10s%10s%50s", ( AlertDescShmPtr + i )->RecordId, ( AlertDescShmPtr + i )->DeviceType, ( AlertDescShmPtr + i )->StatusCode, ( AlertDescShmPtr + i )->StatusDesc );
		sem_buf.sem_op = 2;
		if( semop( AlertDescSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertDesc SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return 1;
}

int EzAlertCmd :: serviceListAlertDesc( const char *RecordId )
{
	struct sembuf sem_buf;

	printf( "\n*********************************************************************************\n" );
	printf( "%15s%10s%10s%50s", "RecordId", "DeviceType", "StatusCode", "StatusCodeDesc" );

	for( int i = 0; i < MaxAlertDesc; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( AlertDescSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertDesc SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}

		if( !strcmp( ( AlertDescShmPtr + i )->RecordId, RecordId ) )
		{
			printf( "%15s%10s%10s%50s", ( AlertDescShmPtr + i )->RecordId, ( AlertDescShmPtr + i )->DeviceType, ( AlertDescShmPtr + i )->StatusCode, ( AlertDescShmPtr + i )->StatusDesc );
			sem_buf.sem_op = 2;
			if( semop( AlertDescSemId, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for AlertDesc SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( AlertDescSemId, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for AlertDesc SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	printf( "\n*********************************************************************************\n" );
	return 1;
}

int EzAlertCmd :: serviceATMAlert( const char *ATMId, const char *StatusCode )
{
	struct EzAlertMgrMsg alertmgrmsg;
	struct EzATMAlertMsg atmalertmsg;

	memset( &alertmgrmsg, 0, sizeof( struct EzAlertMgrMsg ) );
	memset( &atmalertmsg, 0, sizeof( struct EzATMAlertMsg ) );

	alertmgrmsg.AlertCode = ALERT_CODE_ATMSTATUS;
	strcpy( atmalertmsg.ATMId, ATMId );
	strcpy( atmalertmsg.StatusCode, StatusCode );
	memcpy( alertmgrmsg.MsgBuffer, &atmalertmsg, sizeof( struct EzATMAlertMsg ) );

	if( WriteChannel( ( char * ) &alertmgrmsg, sizeof( EzAlertMgrMsg ) ) < 0 )
	{
		trace( "Error in Writing Message to AlertMgr....." );
		printf( "\nError in Writing Message to AlertMgr.....\n" );
	}
	return 1;
}

int EzAlertCmd :: servicePortAlert( const char *PortId, const char *StatusCode )
{

}

int EzAlertCmd :: serviceNetworkAlert( const char *PortId, const char *StatusCode )
{

}

int EzAlertCmd :: serviceAlertCmd( int argc, char **argv )
{
	char command[ 100 ], ATMId[ 33 ], NetworkId[ 17 ], StatusCode[ 33 ];
	int NetworkStatus;

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezalertcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "StatusAlert" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				if( !strcasecmp( command, "Add" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceAddStatusAlert( command );
				}
				if( !strcasecmp( command, "Update" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceUpdateStatusAlert( command );
				}
				if( !strcasecmp( command, "Delete" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceDeleteStatusAlert( command );
				}
				if( !strcasecmp( command, "List" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
						serviceListStatusAlert();
					else
						serviceListStatusAlert( command );
				}
			}
			else if( !strcasecmp( command, "SMSAlertGroup" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				if( !strcasecmp( command, "Add" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceAddSMSAlertGroup( command );
				}
				if( !strcasecmp( command, "Update" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceUpdateSMSAlertGroup( command );
				}
				if( !strcasecmp( command, "Delete" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceDeleteSMSAlertGroup( command );
				}
				if( !strcasecmp( command, "List" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
						serviceListSMSAlertGroup();
					else
						serviceListSMSAlertGroup( command );
				}
			}
			else if( !strcasecmp( command, "MailAlertGroup" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				if( !strcasecmp( command, "Add" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceAddMailAlertGroup( command );
				}
				if( !strcasecmp( command, "Update" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceUpdateMailAlertGroup( command );
				}
				if( !strcasecmp( command, "Delete" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceDeleteMailAlertGroup( command );
				}
				if( !strcasecmp( command, "List" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
						serviceListMailAlertGroup();
					else
						serviceListMailAlertGroup( command );
				}
			}
			else if( !strcasecmp( command, "AlertInfo" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				if( !strcasecmp( command, "Add" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceAddAlertInfo( command );
				}
				if( !strcasecmp( command, "Update" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceUpdateAlertInfo( command );
				}
				if( !strcasecmp( command, "Delete" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceDeleteAlertInfo( command );
				}
				if( !strcasecmp( command, "List" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
						serviceListAlertInfo();
					else
						serviceListAlertInfo( command );
				}
			}
			else if( !strcasecmp( command, "AlertDesc" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				if( !strcasecmp( command, "Add" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceAddAlertDesc( command );
				}
				if( !strcasecmp( command, "Update" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceUpdateAlertDesc( command );
				}
				if( !strcasecmp( command, "Delete" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
					{
						printf( "\nInvalid Command....Type Help for More..." );
						continue;
					}
					serviceDeleteAlertDesc( command );
				}
				if( !strcasecmp( command, "List" ) )
				{
					memset( command, 0, sizeof( command ) );
					getCommand( command, 3 );
					if( strlen( command ) == 0 )
						serviceListAlertDesc();
					else
						serviceListAlertDesc( command );
				}
			}
			if( !strcasecmp( command, "ATMAlert" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				memset( ATMId, 0, sizeof( ATMId ) );
				strcpy( ATMId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				memset( StatusCode, 0, sizeof( StatusCode ) );
				strcpy( StatusCode, command );
				serviceATMAlert( ATMId, StatusCode );
			}
			else if( !strcasecmp( command, "ATMAlert" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				memset( NetworkId, 0, sizeof( NetworkId ) );
				strcpy( NetworkId, command );
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					printf( "\nInvalid Command....Type Help for More..." );
					continue;
				}
				memset( StatusCode, 0, sizeof( StatusCode ) );
				strcpy( StatusCode, command );
				serviceNetworkAlert( NetworkId, StatusCode );
			}
			else if( !strcasecmp( command, "Help" ) )
			{
				printf( "<StatusAlert> <Add> <RecordId>\n" );
				printf( "<StatusAlert> <Update> <RecordId>\n" );
				printf( "<StatusAlert> <Delete> <RecordId>\n" );
				printf( "<StatusAlert> <List> <RecordId>\n" );
				printf( "<StatusAlert> <List>\n" );
				printf( "<SMSAlertGroup> <Add> <SMSAlertGroupId>\n" );
				printf( "<SMSAlertGroup> <Update> <SMSAlertGroupId>\n" );
				printf( "<SMSAlertGroup> <Delete> <SMSAlertGroupId>\n" );
				printf( "<SMSAlertGroup> <List> <SMSAlertGroupId>\n" );
				printf( "<SMSAlertGroup> <List>\n" );
				printf( "<MailAlertGroup> <Add> <MailAlertGroupId>\n" );
				printf( "<MailAlertGroup> <Update> <MailAlertGroupId>\n" );
				printf( "<MailAlertGroup> <Delete> <MailAlertGroupId>\n" );
				printf( "<MailAlertGroup> <List> <MailAlertGroupId>\n" );
				printf( "<MailAlertGroup> <List>\n" );
				printf( "<AlertInfo> <Add> <RecordId>\n" );
				printf( "<AlertInfo> <Update> <RecordId>\n" );
				printf( "<AlertInfo> <Delete> <RecordId>\n" );
				printf( "<AlertInfo> <List> <RecordId>\n" );
				printf( "<AlertInfo> <List>\n" );
				printf( "<AlertDesc> <Add> <RecordId>\n" );
				printf( "<AlertDesc> <Update> <RecordId>\n" );
				printf( "<AlertDesc> <Delete> <RecordId>\n" );
				printf( "<AlertDesc> <List> <RecordId>\n" );
				printf( "<AlertDesc> <List>\n" );
				printf( "<ATMAlert> <ATMId> <StatusCode>\n" );
				printf( "<NetworkAlert> <NetworkId> <StatusCode>\n" );
				printf( "Quit\Exit\n" );
			}
			else if( !strcasecmp( command, "Exit" ) || !strcasecmp( command, "Quit" ) )
				break;
		}
	}
}

int main( int argc, char **argv )
{
	EzAlertCmd alertcmdobj;
	alertcmdobj.initAlertCmd();
	alertcmdobj.serviceAlertCmd( argc, argv );
	return 1;
}
