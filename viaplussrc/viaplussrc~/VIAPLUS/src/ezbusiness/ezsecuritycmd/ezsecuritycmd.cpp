#include <ezbusiness/ezsecuritycmd.h>

int EzSecurityCmd :: initEzSecurityCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsecuritycmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
	{
		printf( "\nError in Opening File[%s]\n", logpath );
		exit( 0 );
	}

    if( initODBCUtil( TaskName, this ) < 0 )
    {
    	printf( "\nError in Initializing initODBCUtil ...\n" );
		closeDebug();
		exit( 0 );
    }

    if( initEzSecurityDriverUtil( this ) < 0 )
	{
    	printf("\nError in Initializing SecurityDriverUtil.....\n" );
    	closeDebug();
    	exit( 0 );
	}

    if( LoadATMKeySharedMemory() < 0 )
    {
    	printf("\nError in Loading ATMKey Memory....\n" );
    	closeDebug();
    	exit( 0 );
    }

    if( LoadDeviceKeySharedMemory() < 0 )
    {
    	printf("\nError in Loading DeviceKey Memory....\n" );
    	closeDebug();
    	exit( 0 );
    }

    if( LoadNetworkKeySharedMemory() < 0 )
    {
    	printf("\nError in Loading NetworkKey Memory....\n" );
		closeDebug();
		exit( 0 );
    }

    if( LoadSecuritySharedMemory() < 0 )
    {
    	printf("\nError in Loading Security Memory....\n" );
		closeDebug();
		exit( 0 );
    }

    if( LoadSecurityPropertyMemory() < 0 )
	{
		printf("\nError in Loading SecurityProperty Memory....\n" );
		closeDebug();
		exit( 0 );
	}

    if( LoadHSMInfoSharedMemory() < 0 )
    {
    	printf("\nError in Loading HSMInfo Memory....\n" );
		closeDebug();
		exit( 0 );
    }
    return 1;
}

int EzSecurityCmd :: serviceAddATMKey( const char *ATMId )
{
	struct EzATMKey atmkey_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Add ATMKey for ATMId[%s]", ATMId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &atmkey_rec, 0, sizeof( struct EzATMKey ) );
	retval = readEzATMKeyTable( ATMId, &atmkey_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading ATMId[%s] from EzATMInfo Table....SqlErr[%05d]", ATMId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( addATMKey( ATMId, &atmkey_rec ) < 0 )
	{
		printf( "\nError in adding ATMId[%s] in ATMKey Memory...", ATMId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceUpdateATMKey( const char *ATMId )
{
	struct EzATMKey atmkey_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Update ATMKey for ATMId[%s]", ATMId );

	if( DBConnect() < 0 )
	{
		printf( "\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &atmkey_rec, 0, sizeof( struct EzATMKey ) );
	retval = readEzATMKeyTable( ATMId, &atmkey_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading ATMId[%s] from EzATMInfo Table....SqlErr[%05d]", ATMId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateATMKey( ATMId, &atmkey_rec ) < 0 )
	{
		printf( "\nError in Updating ATMId[%s] in ATMKey Memory...", ATMId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceDeleteATMKey( const char *ATMId )
{
	trace( DEBUG_TEST, "Received Service Delete ATMKey for ATMId[%s]", ATMId );

	if( deleteATMKey( ATMId ) < 0 )
	{
		printf( "\nError in deleting ATMId[%s] in ATMKey Memory...", ATMId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceListATMKey()
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxATMKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ATMKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for ATMKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( ATMKeyMemoryShmPtr + i )->ATMId, EZSEC_ATMKEYID_INIT_VAL ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nATMId -> [%s]", ( ATMKeyMemoryShmPtr + i )->ATMId );
			printf( "\nATMMasterKey -> [%s]", ( ATMKeyMemoryShmPtr + i )->ATMMasterKey );
			printf( "\nATMCommKey -> [%s]", ( ATMKeyMemoryShmPtr + i )->ATMCommKey );
			printf( "\nKeyLen -> [%d]", ( ATMKeyMemoryShmPtr + i )->ATMKeyLen );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
		}
		sem_buf.sem_op = 2;
		if( semop( ATMKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for ATMKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceListATMKey( const char *ATMId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxATMKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( ATMKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for ATMKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( ATMKeyMemoryShmPtr + i )->ATMId, ATMId ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nATMId -> [%s]", ( ATMKeyMemoryShmPtr + i )->ATMId );
			printf( "\nATMMasterKey -> [%s]", ( ATMKeyMemoryShmPtr + i )->ATMMasterKey );
			printf( "\nATMCommKey -> [%s]", ( ATMKeyMemoryShmPtr + i )->ATMCommKey );
			printf( "\nKeyLen -> [%d]", ( ATMKeyMemoryShmPtr + i )->ATMKeyLen );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			sem_buf.sem_op = 2;
			if( semop( ATMKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for ATMKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( ATMKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for ATMKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceAddDeviceKey( const char *DeviceId )
{
	int retval;
	struct DeviceKey devicekey_rec;

	trace( DEBUG_TEST, "Received Service Add DeviceKey for DeviceId[%s]", DeviceId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &devicekey_rec, 0, sizeof( struct DeviceKey ) );
	retval = readDeviceKeyTable( DeviceId, &devicekey_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading DeviceId[%s] from DeviceKey Table....SqlErr[%05d]", DeviceId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( addDeviceKey( DeviceId, &devicekey_rec ) < 0 )
	{
		printf( "\nError in adding DeviceId[%s] in DeviceKey Memory...", DeviceId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceUpdateDeviceKey( const char *DeviceId )
{
	int retval;
	struct DeviceKey devicekey_rec;

	trace( DEBUG_TEST, "Received Service Update DeviceKey for DeviceId[%s]", DeviceId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &devicekey_rec, 0, sizeof( struct DeviceKey ) );
	retval = readDeviceKeyTable( DeviceId, &devicekey_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading DeviceId[%s] from DeviceKey Table....SqlErr[%05d]", DeviceId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateDeviceKey( DeviceId, &devicekey_rec ) < 0 )
	{
		printf( "\nError in Updating DeviceId[%s] in DeviceKey Memory...", DeviceId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceDeleteDeviceKey( const char *DeviceId )
{
	trace( DEBUG_TEST, "Received Service Delete DeviceKey for DeviceId[%s]", DeviceId );

	if( deleteDeviceKey( DeviceId ) < 0 )
	{
		printf( "\nError in deleting DeviceId[%s] in DeviceKey Memory...", DeviceId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceListDeviceKey()
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxDeviceKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( DeviceKeyMemoryShmPtr + i )->DeviceId, EZSEC_DEVICEKEYID_INIT_VAL ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nDeviceId -> [%s]", ( DeviceKeyMemoryShmPtr + i )->DeviceId );
			printf( "\nDeviceMasterKey -> [%s]", ( DeviceKeyMemoryShmPtr + i )->DeviceMasterKey );
			printf( "\nDeviceCommKey -> [%s]", ( DeviceKeyMemoryShmPtr + i )->DeviceCommKey );
			printf( "\nKeyLen -> [%d]", ( DeviceKeyMemoryShmPtr + i )->DeviceKeyLen );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
		}
		sem_buf.sem_op = 2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceListDeviceKey( const char *DeviceId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxDeviceKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( DeviceKeyMemoryShmPtr + i )->DeviceId, DeviceId ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nDeviceId -> [%s]", ( DeviceKeyMemoryShmPtr + i )->DeviceId );
			printf( "\nDeviceMasterKey -> [%s]", ( DeviceKeyMemoryShmPtr + i )->DeviceMasterKey );
			printf( "\nDeviceCommKey -> [%s]", ( DeviceKeyMemoryShmPtr + i )->DeviceCommKey );
			printf( "\nKeyLen -> [%d]", ( DeviceKeyMemoryShmPtr + i )->DeviceKeyLen );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
		}
		sem_buf.sem_op = 2;
		if( semop( DeviceKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceAddNetworkKey( const char *NetworkId )
{
	int retval;
	struct EzNetworkKey ntwkkey_rec;

	trace( DEBUG_TEST, "Received Service Add NetworkKey for NetworkId[%s]", NetworkId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &ntwkkey_rec, 0, sizeof( struct EzNetworkKey ) );
	retval = readEzNetworkKeyTable( NetworkId, &ntwkkey_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading NetworkId[%s] from NetworkKey Table....SqlErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( addNetworkKey( NetworkId, &ntwkkey_rec ) < 0 )
	{
		printf( "\nError in adding NetworkId[%s] in NetworkKey Memory...", NetworkId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceUpdateNetworkKey( const char *NetworkId )
{
	int retval;
	struct EzNetworkKey ntwkkey_rec;

	trace( DEBUG_TEST, "Received Service Update NetworkKey for NetworkId[%s]", NetworkId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &ntwkkey_rec, 0, sizeof( struct EzNetworkKey ) );
	retval = readEzNetworkKeyTable( NetworkId, &ntwkkey_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading NetworkId[%s] from NetworkKey Table....SqlErr[%05d]", NetworkId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateNetworkKey( NetworkId, &ntwkkey_rec ) < 0 )
	{
		printf( "\nError in Updating NetworkId[%s] in NetworkKey Memory...", NetworkId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceDeleteNetworkKey( const char *NetworkId )
{
	trace( DEBUG_TEST, "Received Service Delete NetworkKey for NetworkId[%s]", NetworkId );

	if( deleteNetworkKey( NetworkId ) < 0 )
	{
		printf( "\nError in deleting NetworkId[%s] in NetworkKey Memory...", NetworkId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceListNetworkKey()
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( NetworkKeyMemoryShmPtr + i )->NetworkId, EZSEC_NETWORKKEYID_INIT_VAL ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nNetworkId -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkId );
			printf( "\nNetworkMasterKey -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkMasterKey );
			printf( "\nNetworkIssCommKey -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkIssCommKey );
			printf( "\nNetworkAcqCommKey -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkAcqCommKey );
			printf( "\nKeyLen -> [%d]", ( NetworkKeyMemoryShmPtr + i )->NetworkKeyLen );
			printf( "\nKeyProperty -> [%c]", ( NetworkKeyMemoryShmPtr + i )->KeyProperty );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceListNetworkKey( const char *NetworkId )
{
	struct sembuf sem_buf;
	int retval = -1;

	for( int i = 0; i < MaxNetworkKeys; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for NetworkKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( NetworkKeyMemoryShmPtr + i )->NetworkId, NetworkId ) )
		{
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			printf( "\nNetworkId -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkId );
			printf( "\nNetworkMasterKey -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkMasterKey );
			printf( "\nNetworkIssCommKey -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkIssCommKey );
			printf( "\nNetworkAcqCommKey -> [%s]", ( NetworkKeyMemoryShmPtr + i )->NetworkAcqCommKey );
			printf( "\nKeyLen -> [%d]", ( NetworkKeyMemoryShmPtr + i )->NetworkKeyLen );
			printf( "\nKeyProperty -> [%c]", ( NetworkKeyMemoryShmPtr + i )->KeyProperty );
			printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
			retval = 1;
			sem_buf.sem_op = 2;
			if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( NetworkKeyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for DeviceKey SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceAddEzSecurity( const char *SecurityId )
{
	struct EzSecurity ezsecurity_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Add EzSecurity for SecurityId[%s]", SecurityId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &ezsecurity_rec, 0, sizeof( struct EzSecurity ) );
	retval = readEzSecurityTable( SecurityId, &ezsecurity_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading SecurityId[%s] from EzSecurity Table....SqlErr[%05d]", SecurityId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( addEzSecurity( SecurityId, &ezsecurity_rec ) < 0 )
	{
		printf( "\nError in adding SecurityId[%s] in EzSecurity Memory...", SecurityId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceUpdateEzSecurity( const char *SecurityId )
{
	struct EzSecurity ezsecurity_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Update EzSecurity for SecurityId[%s]", SecurityId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &ezsecurity_rec, 0, sizeof( struct EzSecurity ) );
	retval = readEzSecurityTable( SecurityId, &ezsecurity_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading SecurityId[%s] from EzSecurity Table....SqlErr[%05d]", SecurityId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateEzSecurity( SecurityId, &ezsecurity_rec ) < 0 )
	{
		printf( "\nError in Updating SecurityId[%s] in EzSecurity Memory...", SecurityId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceDeleteEzSecurity( const char *SecurityId )
{
	trace( DEBUG_TEST, "Received Service Delete EzSecurity for SecurityId[%s]", SecurityId );

	if( deleteEzSecurity( SecurityId ) < 0 )
	{
		printf( "\nError in deleting SecurityId[%s] from EzSecurity Memory...", SecurityId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceListEzSecurity()
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%12s%10s%40s%20s%10s%10s%10s%10s%10s%10s%10s", "SecurityId", "Method", "PVK", "DecTable", "PINPadChar", "PANPadChar", "PINLen", "PANLen", "PANValOffset", "PINFormat", "PANValLen" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxSecurity; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for Security Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( SecurityMemoryShmPtr + i )->SecurityId, EZSEC_SECURITYID_INIT_VAL ) )
			printf( "\n%12s%10c%40s%20s%10c%10c%10d%10d%10d%10s%10d", ( SecurityMemoryShmPtr + i )->SecurityId, ( SecurityMemoryShmPtr + i )->PINVerificationMethod, ( SecurityMemoryShmPtr + i )->EPVK, ( SecurityMemoryShmPtr + i )->DecimilizationTable, ( SecurityMemoryShmPtr + i )->PINPadChar, ( SecurityMemoryShmPtr + i )->PANPadChar, ( SecurityMemoryShmPtr + i )->PINLen, ( SecurityMemoryShmPtr + i )->PANLen, ( SecurityMemoryShmPtr + i )->PANValidationOffset, ( SecurityMemoryShmPtr + i )->PINBlockFormat, ( SecurityMemoryShmPtr + i )->PANValidationLength );
		sem_buf.sem_op = 2;
		if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for Security Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceListEzSecurity( const char *SecurityId )
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%12s%10s%40s%20s%10s%10s%10s%10s%10s%10s%10s", "SecurityId", "Method", "PVK", "DecTable", "PINPadChar", "PANPadChar", "PINLen", "PANLen", "PANValOffset", "PINFormat", "PANValLen" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxSecurity; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for Security Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( SecurityMemoryShmPtr + i )->SecurityId, SecurityId ) )
		{
			printf( "\n%12s%10c%40s%20s%10c%10c%10d%10d%10d%10s%10d", ( SecurityMemoryShmPtr + i )->SecurityId, ( SecurityMemoryShmPtr + i )->PINVerificationMethod, ( SecurityMemoryShmPtr + i )->EPVK, ( SecurityMemoryShmPtr + i )->DecimilizationTable, ( SecurityMemoryShmPtr + i )->PINPadChar, ( SecurityMemoryShmPtr + i )->PANPadChar, ( SecurityMemoryShmPtr + i )->PINLen, ( SecurityMemoryShmPtr + i )->PANLen, ( SecurityMemoryShmPtr + i )->PANValidationOffset, ( SecurityMemoryShmPtr + i )->PINBlockFormat, ( SecurityMemoryShmPtr + i )->PANValidationLength );
			sem_buf.sem_op = 2;
			if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for Security Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			retval = 1;
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SecurityMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for Security Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceAddSecurityProperty( const char *RecordId )
{
	struct EzSecurityProperty securityproperty_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Add SecurityProperty for RecordId[%s]", RecordId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &securityproperty_rec, 0, sizeof( struct EzSecurityProperty ) );
	retval = readEzSecurityPropertyTable( RecordId, &securityproperty_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading RecordId[%s] from SecurityProperty Table....SqlErr[%05d]", RecordId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( addSecurityProperty( RecordId, &securityproperty_rec ) < 0 )
	{
		printf( "\nError in adding RecordId[%s] in SecurityProperty Memory...", RecordId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceUpdateSecurityProperty( const char *RecordId )
{
	struct EzSecurityProperty securityproperty_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Update SecurityProperty for RecordId[%s]", RecordId );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &securityproperty_rec, 0, sizeof( struct EzSecurityProperty ) );
	retval = readEzSecurityPropertyTable( RecordId, &securityproperty_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading RecordId[%s] from SecurityProperty Table....SqlErr[%05d]", RecordId, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateSecurityProperty( RecordId, &securityproperty_rec ) < 0 )
	{
		printf( "\nError in updating RecordId[%s] in SecurityProperty Memory...", RecordId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceDeleteSecurityProperty( const char *RecordId )
{
	trace( DEBUG_TEST, "Received Service Delete SecurityProperty for RecordId[%s]", RecordId );

	if( deleteSecurityProperty( RecordId ) < 0 )
	{
		printf( "\nError in deleting RecordId[%s] from SecurityProperty Memory...", RecordId );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceListSecurityProperty()
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%20s%20s%10s", "RecordId", "InstSecurityGroupId", "SecurityProtocol", "SecurityChannel", "Priority" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxSecurityProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SecurityPropertyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SecurityProperty Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( SecurityPropertyMemoryShmPtr + i )->RecordId, EZSEC_SECURITYPROPERTY_INIT_VAL ) )
			printf( "\n%15s%20s%20s%20s%10d", ( SecurityPropertyMemoryShmPtr + i )->RecordId, ( SecurityPropertyMemoryShmPtr + i )->InstSecurityGroupId, ( SecurityPropertyMemoryShmPtr + i )->SecurityProtocol, ( SecurityPropertyMemoryShmPtr + i )->SecurityChannel, ( SecurityPropertyMemoryShmPtr + i )->Priority );
		sem_buf.sem_op = 2;
		if( semop( SecurityPropertyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SecurityProperty Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceListSecurityProperty( const char *RecordId )
{
	struct sembuf sem_buf;
	int retval = -1;

	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%15s%20s%20s%20s%10s", "RecordId", "InstSecurityGroupId", "SecurityProtocol", "SecurityChannel", "Priority" );
	printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxSecurityProperty; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( SecurityPropertyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SecurityProperty Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( SecurityPropertyMemoryShmPtr + i )->RecordId, RecordId ) )
		{
			retval = 1;
			printf( "\n%15s%20s%20s%20s%10d", ( SecurityPropertyMemoryShmPtr + i )->RecordId, ( SecurityPropertyMemoryShmPtr + i )->InstSecurityGroupId, ( SecurityPropertyMemoryShmPtr + i )->SecurityProtocol, ( SecurityPropertyMemoryShmPtr + i )->SecurityChannel, ( SecurityPropertyMemoryShmPtr + i )->Priority );
			sem_buf.sem_op = 2;
			if( semop( SecurityPropertyMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for SecurityProperty Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( SecurityPropertyMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for SecurityProperty Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityCmd :: serviceAddHSMInfo( const char *HSMName )
{
	struct EzHSMInfo hsminfo_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Add HSMInfo for HSMName[%s]", HSMName );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &hsminfo_rec, 0, sizeof( struct EzHSMInfo ) );
	retval = readEzHSMInfoTable( HSMName, &hsminfo_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading HSMName[%s] from EzHSMInfo Table....SqlErr[%05d]", HSMName, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( addHSMInfo( HSMName, &hsminfo_rec ) < 0 )
	{
		printf( "\nError in adding HSMName[%s] in HSMInfo Memory...", HSMName );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceUpdateHSMInfo( const char *HSMName )
{
	struct EzHSMInfo hsminfo_rec;
	int retval;

	trace( DEBUG_TEST, "Received Service Update HSMInfo for HSMName[%s]", HSMName );

	if( DBConnect() < 0 )
	{
		printf("\nError in Connecting with Switch Database....\n" );
		return -1;
	}

	memset( &hsminfo_rec, 0, sizeof( struct EzHSMInfo ) );
	retval = readEzHSMInfoTable( HSMName, &hsminfo_rec );
	if( retval != 0 )
	{
		printf( "\nError in Reading HSMName[%s] from EzHSMInfo Table....SqlErr[%05d]", HSMName, retval );
		DBClose();
		return -1;
	}
	DBClose();

	if( updateHSMInfo( HSMName, &hsminfo_rec ) < 0 )
	{
		printf( "\nError in Updating HSMName[%s] in HSMInfo Memory...", HSMName );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceDeleteHSMInfo( const char *HSMName )
{
	trace( DEBUG_TEST, "Received Service Delete HSMInfo for HSMName[%s]", HSMName );

	if( deleteHSMInfo( HSMName ) < 0 )
	{
		printf( "\nError in Deleting HSMName[%s] from HSMInfo Memory...", HSMName );
		return -1;
	}
	return 1;
}

int EzSecurityCmd :: serviceListHSMInfo()
{
	trace( DEBUG_TEST, "Received List HSMInfo ...." );

	struct sembuf sem_buf;
	int retval = -1;
	char HSMStatus[ 20 ];

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%16s%25s%15s%15s%15s", "HSMName", "HSMAddress", "HSMType", "PortNo", "HSMStatus" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxHSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for HSMInfo Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( strcmp( ( HSMInfoMemoryShmPtr + i )->HSMName, EZSEC_HSM_INIT_NAME ) )
		{
			memset( HSMStatus, 0, sizeof( HSMStatus ) );
			if( ( HSMInfoMemoryShmPtr + i )->HSMStatus == EZSEC_HSM_CONNECTED )
				strcpy( HSMStatus, "CONNECTED" );
			else
				strcpy( HSMStatus, "TRY_CONNECTING" );

			printf( "\n%16s%25s%15s%15d%15s", ( HSMInfoMemoryShmPtr + i )->HSMName, ( HSMInfoMemoryShmPtr + i )->HSMAddress, ( HSMInfoMemoryShmPtr + i )->HSMType, ( HSMInfoMemoryShmPtr + i )->HSMPortNo, HSMStatus );
		}
		sem_buf.sem_op = 2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for HSMInfo Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return 1;
}

int EzSecurityCmd :: serviceListHSMInfo( const char *HSMName )
{
	trace( DEBUG_TEST, "Received List HSMInfo ...." );

	struct sembuf sem_buf;
	int retval = -1;
	char HSMStatus[ 20 ];

	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );
	printf( "\n%16s%25s%15s%15s%15s", "HSMName", "HSMAddress", "HSMType", "PortNo", "HSMStatus" );
	printf( "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" );

	for( int i = 0; i < MaxHSM; i++ )
	{
		sem_buf.sem_num = i;
		sem_buf.sem_flg = 0;
		sem_buf.sem_op = -2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for HSMInfo Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
		if( !strcmp( ( HSMInfoMemoryShmPtr + i )->HSMName, HSMName ) )
		{
			memset( HSMStatus, 0, sizeof( HSMStatus ) );
			if( ( HSMInfoMemoryShmPtr + i )->HSMStatus == EZSEC_HSM_CONNECTED )
				strcpy( HSMStatus, "CONNECTED" );
			else
				strcpy( HSMStatus, "TRY_CONNECTING" );
			retval = 1;
			printf( "\n%16s%25s%15s%15d%15s", ( HSMInfoMemoryShmPtr + i )->HSMName, ( HSMInfoMemoryShmPtr + i )->HSMAddress, ( HSMInfoMemoryShmPtr + i )->HSMType, ( HSMInfoMemoryShmPtr + i )->HSMPortNo, HSMStatus );
			sem_buf.sem_op = 2;
			if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
			{
				trace( "Error in Semop for HSMInfo Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				return -1;
			}
			break;
		}
		sem_buf.sem_op = 2;
		if( semop( HSMInfoMemorySemid, &sem_buf, 1 ) < 0 )
		{
			trace( "Error in Semop for HSMInfo Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			return -1;
		}
	}
	return retval;
}

int EzSecurityCmd :: serviceHelpATMKey()
{
	printf( "\n>>>>>>>>Help for ATMKey>>>>>>>>>>>>>>>" );
	printf( "\n<add> <ATMId>" );
	printf( "\n<update> <ATMId>" );
	printf( "\n<delete> <ATMId>" );
	printf( "\n<List>" );
	printf( "\n<List> <ATMId>" );
	printf( "\n" );
	return 1;
}

int EzSecurityCmd :: serviceHelpDeviceKey()
{
	printf( "\n>>>>>>>>Help for DeviceKey>>>>>>>>>>>>>>>" );
	printf( "\n<add> <DeviceId>" );
	printf( "\n<update> <DeviceId>" );
	printf( "\n<delete> <DeviceId>" );
	printf( "\n<List>" );
	printf( "\n<List> <DeviceId>" );
	printf( "\n" );
	return 1;
}

int EzSecurityCmd :: serviceHelpNetworkKey()
{
	printf( "\n>>>>>>>>Help for NetworkKey>>>>>>>>>>>>>>>" );
	printf( "\n<add> <NetworkId>" );
	printf( "\n<update> <NetworkId>" );
	printf( "\n<delete> <NetworkId>" );
	printf( "\n<List>" );
	printf( "\n<List> <NetworkId>" );
	printf( "\n" );
	return 1;
}

int EzSecurityCmd :: serviceHelpEzSecurity()
{
	printf( "\n>>>>>>>>Help for EzSecurity>>>>>>>>>>>>>>>" );
	printf( "\n<add> <SecurityId> " );
	printf( "\n<update> <SecurityId> " );
	printf( "\n<delete> <SecurityId> " );
	printf( "\n<List>" );
	printf( "\n<List> <SecurityId>" );
	printf( "\n" );
	return 1;
}

int EzSecurityCmd :: serviceHelpHSMInfo()
{
	printf( "\n>>>>>>>>Help for HSMInfo>>>>>>>>>>>>>>>" );
	printf( "\n<add> <HSMName>" );
	printf( "\n<update> <HSMName>" );
	printf( "\n<delete> <HSMName>" );
	printf( "\n<List>" );
	printf( "\n<List> <HSMName>" );
	printf( "\n" );
	return 1;
}

int EzSecurityCmd :: startATMKeyCmdInterface()
{
	char command[ 200 ];

	while( 1 )
	{
		printf("\natmkeycmd>" );

		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;

		if( !strcasecmp( command, "Add" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceAddATMKey( command );
		}
		else if ( !strcasecmp( command, "Update" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceUpdateATMKey( command );
		}
		else if ( !strcasecmp( command, "Delete" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceDeleteATMKey( command );
		}
		else if ( !strcasecmp( command, "List" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				serviceListATMKey();
				continue;
			}
			serviceListATMKey( command );
		}
		else if ( !strcasecmp( command, "Help" ) )
			serviceHelpATMKey();
		else if ( !strcasecmp( command, "quit" ) || !strcasecmp( command, "q" ) || !strcasecmp( command, "exit" ) )
			break;
	}
	return 1;
}

int EzSecurityCmd :: startDeviceKeyCmdInterface()
{
	char command[ 200 ];

	while( 1 )
	{
		printf("\ndevicekeycmd>" );

		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;

		if( !strcasecmp( command, "Add" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceAddDeviceKey( command );
		}
		else if ( !strcasecmp( command, "Update" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceUpdateDeviceKey( command );
		}
		else if ( !strcasecmp( command, "Delete" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceDeleteDeviceKey( command );
		}
		else if ( !strcasecmp( command, "List" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				serviceListDeviceKey();
				continue;
			}
			serviceListDeviceKey( command );
		}
		else if ( !strcasecmp( command, "Help" ) )
			serviceHelpDeviceKey();
		else if ( !strcasecmp( command, "quit" ) || !strcasecmp( command, "q" ) || !strcasecmp( command, "exit" ) )
			break;
	}
	return 1;
}

int EzSecurityCmd :: startNetworkKeyCmdInterface()
{
	char command[ 200 ];

	while( 1 )
	{
		printf("\nntwkkeycmd>" );

		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;

		if( !strcasecmp( command, "Add" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceAddNetworkKey( command );
		}
		else if ( !strcasecmp( command, "Update" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceUpdateNetworkKey( command );
		}
		else if ( !strcasecmp( command, "Delete" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceDeleteNetworkKey( command );
		}
		else if ( !strcasecmp( command, "List" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				serviceListNetworkKey();
				continue;
			}
			serviceListNetworkKey( command );
		}
		else if ( !strcasecmp( command, "Help" ) )
			serviceHelpNetworkKey();
		else if ( !strcasecmp( command, "quit" ) || !strcasecmp( command, "q" ) || !strcasecmp( command, "exit" ) )
			break;
	}
	return 1;
}

int EzSecurityCmd :: startEzSecurityCmdInterface()
{
	char command[ 200 ];

	while( 1 )
	{
		printf("\nezsecuritycmd>" );

		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;

		if( !strcasecmp( command, "Add" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceAddEzSecurity( command );
		}
		else if ( !strcasecmp( command, "Update" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceUpdateEzSecurity( command );
		}
		else if ( !strcasecmp( command, "Delete" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceDeleteEzSecurity( command );
		}
		else if ( !strcasecmp( command, "List" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				serviceListEzSecurity();
				continue;
			}
			serviceListEzSecurity( command );
		}
		else if ( !strcasecmp( command, "Help" ) )
			serviceHelpEzSecurity();
		else if ( !strcasecmp( command, "quit" ) || !strcasecmp( command, "q" ) || !strcasecmp( command, "exit" ) )
			break;
	}
	return 1;
}

int EzSecurityCmd :: startHSMInfoCmdInterface()
{
	char command[ 200 ];

	while( 1 )
	{
		printf("\nhsminfocmd>" );

		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;

		if( !strcasecmp( command, "Add" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceAddHSMInfo( command );
		}
		else if ( !strcasecmp( command, "Update" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceUpdateHSMInfo( command );
		}
		else if ( !strcasecmp( command, "Delete" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				printf("\ninvalid command..Type help for more..");
				continue;
			}
			serviceDeleteHSMInfo( command );
		}
		else if ( !strcasecmp( command, "List" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			if( strlen( command ) == 0 )
			{
				serviceListHSMInfo();
				continue;
			}
			serviceListHSMInfo( command );
		}
		else if ( !strcasecmp( command, "Help" ) )
			serviceHelpHSMInfo();
		else if ( !strcasecmp( command, "quit" ) || !strcasecmp( command, "q" ) || !strcasecmp( command, "exit" ) )
			break;
	}
	return 1;
}

int EzSecurityCmd :: startCmdInterface( int argc, char **argv )
{
	if( argc != 2 )
	{
		printf("\nUsage <ezseccmd> <atmkey/devicekey/ntwkkey/security/hsminfo>\n" );
		return 1;
	}
	if( strcasecmp( argv[ 1 ], "atmkey" ) && strcasecmp( argv[ 1 ], "devicekey" ) && strcasecmp( argv[ 1 ], "ntwkkey" ) && strcasecmp( argv[ 1 ], "security" ) && strcasecmp( argv[ 1 ], "hsminfo" ) )
	{
		printf( "\nUsage <ezseccmd> <atmkey/devicekey/ntwkkey/security/hsminfo>\n" );
		return 1;
	}
	if( !strcasecmp( argv[ 1 ], "atmkey" ) )
		startATMKeyCmdInterface();
	else if( !strcasecmp( argv[ 1 ], "devicekey" ) )
		startDeviceKeyCmdInterface();
	else if ( !strcasecmp( argv[ 1 ], "ntwkkey" ) )
		startNetworkKeyCmdInterface();
	else if( !strcasecmp( argv[ 1 ], "security" ) )
		startEzSecurityCmdInterface();
	else if( !strcasecmp( argv[ 1 ], "hsminfo" ) )
		startHSMInfoCmdInterface();
	else
		printf( "\nUsage <ezseccmd> <atmkey/devicekey/ntwkkey/security/hsminfo>\n" );
	return 1;
}

int EzSecurityCmd :: readEzATMKeyTable( const char *I_ATMId, struct EzATMKey *atmkey_rec )
{
    char ATMId[ 33 ];
    char ATMMasterKey[ 65 ];
    char ATMCommKey[ 65 ];
    int ATMKeyLen;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(ATMID),RTRIM(ATMMASTERKEY),RTRIM(ATMCOMMKEY),ATMKEYLEN FROM EZATMINFO WHERE RTRIM(ATMID)='%s';", I_ATMId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in LoadATMKey [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( ATMId, 0, sizeof( ATMId ) );
	memset( ATMMasterKey, 0, sizeof( ATMMasterKey ) );
	memset( ATMCommKey, 0, sizeof( ATMCommKey ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, ATMId, sizeof(ATMId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(ATMId) in EZATMINFO [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, ATMMasterKey, sizeof(ATMMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(ATMMasterKey) in EZATMINFO [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, ATMCommKey, sizeof(ATMCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(ATMCommKey) in EZATMINFO [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &ATMKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(ATMKeyLen) in EZATMINFO [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( atmkey_rec, 0, sizeof( struct EzATMKey ) );
        strcpy( atmkey_rec->ATMId, ATMId );
        strcpy( atmkey_rec->ATMMasterKey, ATMMasterKey );
        strcpy( atmkey_rec->ATMCommKey, ATMCommKey );
        atmkey_rec->ATMKeyLen = ATMKeyLen;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityCmd :: readEzNetworkKeyTable( const char *I_NetworkId, struct EzNetworkKey *ntwkkey_rec )
{
	char NetworkId[ 17 ];
    char NetworkMasterKey[ 65 ];
    char NetworkAcqCommKey[ 65 ];
    char NetworkIssCommKey[ 65 ];
    int NetworkKeyLen;
    char KeyProperty;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(NETWORKID), \
        RTRIM(NETWORKMASTERKEY), \
        RTRIM(NETWORKACQCOMMKEY), \
        RTRIM(NETWORKISSCOMMKEY), \
		NETWORKKEYLEN, \
		KEYPROPERTY \
	FROM EZNETWORKKEY WHERE RTRIM(NETWORKID)='%s';", I_NetworkId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in LoadEzNetworkKey [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( NetworkMasterKey, 0, sizeof( NetworkMasterKey ) );
	memset( NetworkAcqCommKey, 0, sizeof( NetworkAcqCommKey ) );
	memset( NetworkIssCommKey, 0, sizeof( NetworkIssCommKey ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, NetworkId, sizeof(NetworkId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(NetworkId) in EZNETWORKKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, NetworkMasterKey, sizeof(NetworkMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(NetworkMasterKey) in EZNETWORKKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, NetworkAcqCommKey, sizeof(NetworkAcqCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(NetworkAcqCommKey) in EZNETWORKKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, NetworkIssCommKey, sizeof(NetworkIssCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(NetworkIssCommKey) in EZNETWORKKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &NetworkKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(NetworkKeyLen) in EZNETWORKKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &KeyProperty, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(KeyProperty) in EZNETWORKKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ntwkkey_rec, 0, sizeof( struct EzNetworkKey ) );
        strcpy( ntwkkey_rec->NetworkId, NetworkId );
        strcpy( ntwkkey_rec->NetworkMasterKey, NetworkMasterKey );
        strcpy( ntwkkey_rec->NetworkAcqCommKey, NetworkAcqCommKey );
        strcpy( ntwkkey_rec->NetworkIssCommKey, NetworkIssCommKey );
        ntwkkey_rec->NetworkKeyLen = NetworkKeyLen;
        ntwkkey_rec->KeyProperty = KeyProperty;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityCmd :: readDeviceKeyTable( const char *I_DeviceId, struct DeviceKey *devicekey_rec )
{
    char DeviceId[ 33 ];
    char DeviceMasterKey[ 65 ];
    char DeviceCommKey[ 65 ];
    int DeviceKeyLen;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT RTRIM(DEVICEID),RTRIM(DEVICEMASTERKEY),RTRIM(DEVICECOMMKEY),DEVICEKEYLEN FROM EZDEVICEKEY WHERE RTRIM(DEVICEID)='%s'", I_DeviceId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in LoadDeviceKey [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( DeviceId, 0, sizeof( DeviceId ) );
	memset( DeviceMasterKey, 0, sizeof( DeviceMasterKey ) );
	memset( DeviceCommKey, 0, sizeof( DeviceCommKey ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, DeviceId, sizeof(DeviceId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(DeviceId) in EZDEVICEKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, DeviceMasterKey, sizeof(DeviceMasterKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(DeviceMasterKey) in EZDEVICEKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, DeviceCommKey, sizeof(DeviceCommKey), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(DeviceCommKey) in EZDEVICEKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_SLONG, &DeviceKeyLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(DeviceKeyLen) in EZDEVICEKEY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }
    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( devicekey_rec, 0, sizeof( struct DeviceKey ) );
        strcpy( devicekey_rec->DeviceId, DeviceId );
        strcpy( devicekey_rec->DeviceMasterKey, DeviceMasterKey );
        strcpy( devicekey_rec->DeviceCommKey, DeviceCommKey );
        devicekey_rec->DeviceKeyLen = DeviceKeyLen;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityCmd :: readEzSecurityTable( const char *I_SecurityId, struct EzSecurity *ezsecurity_rec )
{
	char SecurityId[ 11 ];
	char PINVerificationMethod;
	char EPVK[ 65 ];
	char DecimilizationTable[ 17 ];
	char PINPadChar;
	char PANPadChar;
	short PINLen;
	short PANLen;
	short PANValidationOffset;
	char PINBlockFormat[ 3 ];
	short PANValidationLength;
	char CVKA[ 65 ];
	char CVKB[ 65 ];
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(SECURITYID), \
        PINVERIFICATIONMETHOD, \
        RTRIM(EPVK), \
        RTRIM(DECIMILIZATIONTABLE), \
        PINPADCHAR, \
		PANPADCHAR, \
		PINLEN, \
		PANLEN, \
		PANVALIDATIONOFFSET, \
		RTRIM(PINBLOCKFORMAT), \
		PANVALIDATIONLENGTH, \
		RTRIM(CVKA), \
		RTRIM(CVKB) \
    FROM EZSECURITY WHERE RTRIM(SECURITYID)='%s'", I_SecurityId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in LoadSecurity [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( EPVK, 0, sizeof( EPVK ) );
	memset( DecimilizationTable, 0, sizeof( DecimilizationTable ) );
	memset( PINBlockFormat, 0, sizeof( PINBlockFormat ) );
	memset( CVKA, 0, sizeof( CVKA ) );
	memset( CVKB, 0, sizeof( CVKB ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, SecurityId, sizeof(SecurityId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(SecurityId) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_BINARY, &PINVerificationMethod, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PINVerificationMethod) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, EPVK, sizeof(EPVK), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(EPVK) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, DecimilizationTable, sizeof(DecimilizationTable), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(DecimilizationTable) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_BINARY, &PINPadChar, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PINPadChar) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_BINARY, &PANPadChar, sizeof(char), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PANPadChar) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_SLONG, &PINLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PINLen) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &PANLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PANLen) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &PANValidationOffset, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PANValidationOffset) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_CHAR, PINBlockFormat, sizeof(PINBlockFormat), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PINBlockFormat) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &PANValidationLength, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(PANValidationLength) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 12, SQL_C_CHAR, CVKA, sizeof(CVKA), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(CVKA) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 13, SQL_C_CHAR, CVKB, sizeof(CVKB), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(CVKB) in EZSECURITY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( ezsecurity_rec, 0, sizeof( struct EzSecurity ) );
        strcpy( ezsecurity_rec->SecurityId, SecurityId );
        ezsecurity_rec->PINVerificationMethod = PINVerificationMethod;
        strcpy( ezsecurity_rec->EPVK, EPVK );
        strcpy( ezsecurity_rec->DecimilizationTable, DecimilizationTable );
        ezsecurity_rec->PINPadChar = PINPadChar;
        ezsecurity_rec->PANPadChar = PANPadChar;
        ezsecurity_rec->PINLen = PINLen;
        ezsecurity_rec->PANLen = PANLen;
        ezsecurity_rec->PANValidationOffset = PANValidationOffset;
        strcpy( ezsecurity_rec->PINBlockFormat, PINBlockFormat );
        ezsecurity_rec->PANValidationLength = PANValidationLength;
		strcpy( ezsecurity_rec->CVKA, CVKA );
		strcpy( ezsecurity_rec->CVKB, CVKB );
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityCmd :: readEzSecurityPropertyTable( const char *I_RecordId, struct EzSecurityProperty *securityproperty_rec )
{
    char RecordId[ 11 ];
	char InstSecurityGroupId[ 17 ];
	char SecurityProtocol[ 17 ];
	char SecurityChannel[ 33 ];
	int Priority;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(RECORDID), \
        RTRIM(INSTSECURITYGROUPID), \
        RTRIM(SECURITYPROTOCOL), \
        RTRIM(SECURITYCHANNEL), \
        PRIORITY \
	FROM EZSECURITYPROPERTY WHERE RTRIM(RECORDID)='%s'", I_RecordId );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in LoadSecurityProperty [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstSecurityGroupId, 0, sizeof( InstSecurityGroupId ) );
	memset( SecurityProtocol, 0, sizeof( SecurityProtocol ) );
	memset( SecurityChannel, 0, sizeof( SecurityChannel ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, RecordId, sizeof(RecordId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(RecordId) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, InstSecurityGroupId, sizeof(InstSecurityGroupId), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(InstSecurityGroupId) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, SecurityProtocol, sizeof(SecurityProtocol), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(SecurityProtocol) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, SecurityChannel, sizeof(SecurityChannel), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(SecurityChannel) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &Priority, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(Priority) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( securityproperty_rec, 0, sizeof( struct EzSecurityProperty ) );
        strcpy( securityproperty_rec->RecordId, RecordId );
        strcpy( securityproperty_rec->InstSecurityGroupId, InstSecurityGroupId );
        strcpy( securityproperty_rec->SecurityProtocol, SecurityProtocol );
        strcpy( securityproperty_rec->SecurityChannel, SecurityChannel );
        securityproperty_rec->Priority = Priority;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int EzSecurityCmd :: readEzHSMInfoTable( const char *I_HSMName, struct EzHSMInfo *hsminfo_rec )
{
	char HSMName[ 33 ];
	char HSMProtocol[ 17 ];
	char HSMType[ 17 ];
	char HSMAddress[ 33 ];
	int HSMPortNo;
	int HeaderLen;
	char HeaderType[ 9 ];
	int HSMHeaderLen;
	int HSMTimeOut;
	int ConnectionInterval;
	int HSMStatus;
	int i = 0;
    SQLHSTMT hstmt;
    SQLRETURN obdcret;
    SQLLEN Len;
    char SqlStmt[ 1024 ];

    odbcret = SQLAllocHandle( SQL_HANDLE_STMT, odbcdbc, &hstmt );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Allocation Statement Handle [ %d ]", odbcret );
    	return -1;
    }

    memset( SqlStmt, 0, sizeof( SqlStmt ) );
    sprintf( SqlStmt,  "SELECT \
		RTRIM(HSMNAME), \
        RTRIM(HSMPROTOCOL), \
        RTRIM(HSMTYPE), \
        RTRIM(HSMADDRESS), \
        HSMPORT, \
        HEADERLEN, \
		RTRIM(HEADERTYPE), \
		HSMHEADERLEN, \
		HSMTIMEOUT, \
		CONNECTIONINTERVAL, \
		HSMSTATUS \
    FROM EZHSMINFO WHERE RTRIM(HSMNAME)='%s' ;", I_HSMName );

    odbcret = SQLExecDirect( hstmt, (SQLCHAR *)SqlStmt, SQL_NTS  );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace("SqlStmt<%s>", SqlStmt);
    	trace(DEBUG_ERROR, "Error in Executing SqlStmt in LoadHSMInfo [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

	memset( HSMName, 0, sizeof( HSMName ) );
	memset( HSMProtocol, 0, sizeof( HSMProtocol ) );
	memset( HSMType, 0, sizeof( HSMType ) );
	memset( HSMAddress, 0, sizeof( HSMAddress ) );
	memset( HeaderType, 0, sizeof( HeaderType ) );

    odbcret = SQLBindCol( hstmt, 1, SQL_C_CHAR, HSMName, sizeof(HSMName), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMName) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 2, SQL_C_CHAR, HSMProtocol, sizeof(HSMProtocol), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMProtocol) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 3, SQL_C_CHAR, HSMType, sizeof(HSMType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMType) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 4, SQL_C_CHAR, HSMAddress, sizeof(HSMAddress), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMAddress) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 5, SQL_C_SLONG, &HSMPortNo, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMPortNo) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 6, SQL_C_SLONG, &HeaderLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HeaderLen) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 7, SQL_C_CHAR, HeaderType, sizeof(HeaderType), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HeaderType) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 8, SQL_C_SLONG, &HSMHeaderLen, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMHeaderLen) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 9, SQL_C_SLONG, &HSMTimeOut, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMTimeOut) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 10, SQL_C_SLONG, &ConnectionInterval, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(ConnectionInterval) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle(SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    odbcret = SQLBindCol( hstmt, 11, SQL_C_SLONG, &HSMStatus, sizeof(int), &Len );
    if( !SQL_SUCCEEDED( odbcret ) )
    {
    	trace(DEBUG_ERROR, "Error in Binding Column(HSMStatus) in EZSECURITYPROPERTY [ %d ]", odbcret );
    	SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
    	return -1;
    }

    while( (odbcret = SQLFetch( hstmt ) )!= SQL_NO_DATA )
    {
        memset( hsminfo_rec, 0, sizeof( struct EzHSMInfo ) );
        strcpy( hsminfo_rec->HSMName, HSMName );
        strcpy( hsminfo_rec->HSMProtocol, HSMProtocol );
        strcpy( hsminfo_rec->HSMType, HSMType );
        strcpy( hsminfo_rec->HSMAddress, HSMAddress );
        hsminfo_rec->HSMPortNo = HSMPortNo;
        hsminfo_rec->HeaderLen = HeaderLen;
        strcpy( hsminfo_rec->HeaderType, HeaderType );
        hsminfo_rec->HSMHeaderLen = HSMHeaderLen;
        hsminfo_rec->HSMTimeOut = HSMTimeOut;
        hsminfo_rec->ConnectionInterval = ConnectionInterval;
        hsminfo_rec->HSMStatus = 0;
    }
    SQLFreeHandle( SQL_HANDLE_STMT, hstmt );
	return 0;
}

int main( int argc, char **argv )
{
	EzSecurityCmd ezsecuritycmdobj;
	ezsecuritycmdobj.initEzSecurityCmd( argv[ 0 ] );
	ezsecuritycmdobj.startCmdInterface( argc, argv );
	return 1;
}

