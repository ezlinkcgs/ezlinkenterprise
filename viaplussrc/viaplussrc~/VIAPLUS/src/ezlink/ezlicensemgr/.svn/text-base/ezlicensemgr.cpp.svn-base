#include <ezlink/ezlicensemgr.h>

void EzLicenseMgr :: initLicenseMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezlicensemgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	trace( "^^^^^^^^^^^EzLicenseMgr Started^^^^^^^^^^^^^" );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil" );
		trace( "^^^^^^^^^^^EzLicenseMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Another Instance of EzLicenseMgr Already Running...." );
		trace( "^^^^^^^^^^^EzLicenseMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	FBuffer = NULL;

	if( LoadLicenseFile() < 0 )
	{
		trace( "Error in Loading License File...." );
		trace( "^^^^^^^^^^^EzLicenseMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	LicenseMgrKeyId = CreateChannelId( this, LICENSEMGR_CHANNEL );

	if( LicenseMgrKeyId < 0 )
	{
		trace( "Error in Creating Channel Id[%s]...", LICENSEMGR_CHANNEL );
		trace( "^^^^^^^^^^^EzLicenseMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateLicenseMgrQueue() < 0 )
	{
		trace( "Error in Creating LicenseMgrQueue....." );
		trace( "^^^^^^^^^^^EzLicenseMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

int EzLicenseMgr :: CheckInteger( const char *IntStr )
{
	for( int i = 0; i < strlen( IntStr ); i++ )
    {
        if( ( IntStr[ i ] < 48 ) || ( IntStr[ i ] > 57 ) )
                return -1;
    }
    return 1;
}

int EzLicenseMgr :: LoadLicenseFile()
{
	char LicensePath[ CFG_PATH_SIZE + 1 ];
	struct stat FStat;
	FILE *license_fptr;

	memset( LicensePath, 0, sizeof( LicensePath ) );
	sprintf( LicensePath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezlicense.cfg" );

	license_fptr = fopen( LicensePath, "r" );
	if( license_fptr == NULL )
	{
		trace( "Error in Opening File[%s]...", LicensePath );
		return -1;
	}

	if( stat( LicensePath, &FStat ) < 0 )
	{
		trace( "Error in stat System Call....SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	/*
	 * if( FBuffer != NULL )
		free( FBuffer );
	*/

	FBuffer = ( char * ) malloc( FStat.st_size + 100 );
	if( FBuffer == NULL )
	{
		trace( "Error in Allocating Memory for License File Buffer...Malloc Error" );
		return -1;
	}
	memset( FBuffer, 0, FStat.st_size + 100 );

	int i = 0, InputData;
	while( !feof( license_fptr ) )
	{
		InputData = fgetc( license_fptr );
		FBuffer[ i ] = InputData - 100;
		i++;
	}
	fclose( license_fptr );

	if( !isValidMachine() )
	{
		trace( "License File is having invalid ServerId...." );
		return -1;
	}
	return 1;
}

void EzLicenseMgr :: ChangeMachineId( char *MachineId )
{
	for( int i = 0; i < strlen( MachineId ); i++ )
	{
		switch ( MachineId[ i ] )
		{
			case '0':
				MachineId[ i ] = '9';
			break;

			case '1':
				MachineId[ i ] = '8';
			break;

			case '2':
				MachineId[ i ] = '7';
			break;

			case '3':
				MachineId[ i ] = '6';
			break;

			case '4':
				MachineId[ i ] = '5';
			break;

			case '5':
				MachineId[ i ] = '4';
			break;

			case '6':
				MachineId[ i ] = '3';
			break;

			case '7':
				MachineId[ i ] = '2';
			break;

			case '8':
				MachineId[ i ] = '1';
			break;

			case '9':
				MachineId[ i ] = '0';
			break;

			case 'a':
				MachineId[ i ] = 'f';
			break;

			case 'A':
				MachineId[ i ] = 'F';
			break;

			case 'b':
				MachineId[ i ] = 'e';
			break;

			case 'B':
				MachineId[ i ] = 'E';
			break;

			case 'c':
				MachineId[ i ] = 'd';
			break;

			case 'C':
				MachineId[ i ] = 'D';
			break;

			case 'd':
				MachineId[ i ] = 'c';
			break;

			case 'D':
				MachineId[ i ] = 'C';
			break;

			case 'e':
				MachineId[ i ] = 'b';
			break;

			case 'E':
				MachineId[ i ] = 'B';
			break;

			case 'f':
				MachineId[ i ] = 'a';
			break;

			case 'F':
				MachineId[ i ] = 'A';
			break;

			default:
			break;

		}
	}
}

int EzLicenseMgr :: getMachineId( char *MachineId )
{
	struct ifreq *ifr, *ifend;
	struct ifreq ifreq;
	struct ifconf ifc;
	struct ifreq ifs[MAX_IFS];
	int SockFD;
	char TempMachineId[ 20 ];

	SockFD = socket(AF_INET, SOCK_DGRAM, 0);
	ifc.ifc_len = sizeof(ifs);
	ifc.ifc_req = ifs;

	if (ioctl( SockFD, SIOCGIFCONF, &ifc) < 0)
	{
		printf( "ioctl error...while getting the machine id.....SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		return -1;
	}

	ifend = ifs + (ifc.ifc_len / sizeof(struct ifreq));
	for (ifr = ifc.ifc_req; ifr < ifend; ifr++)
	{
		//if (ifr->ifr_addr.sa_family == AF_INET && !strncmp( ifr->ifr_name, "eth", 3 ) )
		if (ifr->ifr_addr.sa_family == AF_INET )
		{
			strncpy(ifreq.ifr_name, ifr->ifr_name,sizeof(ifreq.ifr_name));
			if (ioctl (SockFD, SIOCGIFHWADDR, &ifreq) < 0)
			{
				printf( "ioctl error...while getting the machine id.....SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
				return -1;
			}
			memset( TempMachineId, 0, sizeof( TempMachineId ) );
			sprintf( TempMachineId,"%02x%02x%02x%02x%02x%02x", (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[0], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[1], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[2], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[3], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[4], (int) ((unsigned char *) &ifreq.ifr_hwaddr.sa_data)[5] );
			if( strcmp( TempMachineId, "000000000000" ) )
			{
				strcpy( MachineId, TempMachineId );
				break;
			}
		}
	}
    ChangeMachineId( MachineId );
    return 1;
}

bool EzLicenseMgr ::  isValidMachine()
{
	char MachineId[ 50 ], ServerId[ 50 ], ServerIdList[ 150 ];
	int NTokens;
	bool found = false;

	memset( MachineId, 0, sizeof( MachineId ) );
	if( getMachineId( MachineId ) < 0 )
		return false;

	memset( ServerIdList, 0, sizeof( ServerIdList ) );
	if( cfg_search( FBuffer, "SERVERID", ServerIdList, 2 ) < 0 )
	{
		trace( "Error in Searching SERVERID from License File...." );
		return false;
	}

	NTokens = eztokenutil.getNToken( ServerIdList, ',' );

	for( int i = 0; i < NTokens; i++ )
	{
		memset( ServerId, 0, sizeof( ServerId ) );
		eztokenutil.getToken( ServerIdList, ServerId, ',', i + 1 );
		if( !strcmp( MachineId, ServerId ) )
		{
			found = true;
			break;
		}
	}
	return found;
}

bool EzLicenseMgr :: isValidInstRouteType( const char *InstRouteType )
{
	char CfgInstRouteType[ 100 ], CfgVal[ 100 ];

	memset( CfgInstRouteType, 0, sizeof( CfgInstRouteType ) );
	sprintf( CfgInstRouteType, "INSTROUTETYPE#%s", InstRouteType );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgInstRouteType, CfgVal, 1 ) < 0 )
	{
		trace( "Error in Searching InstRouteType[%s] from License File", InstRouteType );
		return false;
	}
	else
		return true;
}

bool EzLicenseMgr :: isValidInst( const char *InstId, const char *InstType )
{
	char CfgInstId[ 50 ], CfgInstType[ 50 ];

	memset( CfgInstId, 0, sizeof( CfgInstId ) );
	sprintf( CfgInstId, "INST#%s", InstId );

	memset( CfgInstType, 0, sizeof( CfgInstType ) );
	if( cfg_search( FBuffer, CfgInstId, CfgInstType, 2 ) < 0 )
	{
		trace( "Error in Searching InstId[%s] from License File", InstId );
		return false;
	}

	if( strcmp( CfgInstType, InstType ) )
	{
		trace( "InstType[%s] is not matching in LicenseFile..", InstType );
		return false;
	}
	return true;
}

bool EzLicenseMgr :: isBINCheckReq( const char *InstId )
{
	char CfgBin[ 100 ], CfgVal[ 100 ];

	memset( CfgBin, 0, sizeof( CfgBin ) );
	sprintf( CfgBin, "%s#BINCHECKREQ", InstId );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgBin, CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching Parameter[%s] from License File..", CfgBin );
		return false;
	}

	if( !strcasecmp( CfgVal, "Yes" ) )
		return true;
	else
		return false;
}

int EzLicenseMgr :: getBINLimit( const char *InstId )
{
	char CfgBin[ 100 ], CfgVal[ 100 ];

	memset( CfgBin, 0, sizeof( CfgBin ) );
	sprintf( CfgBin, "%s#MAXBIN", InstId );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgBin, CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching Parameter[%s] from License File..", CfgBin );
		return -1;
	}

	if( CheckInteger( CfgVal ) < 0 )
	{
		trace( "Parameter[%s] Should be a Numeric Value...", CfgVal );
		return -1;
	}
	return atoi( CfgVal );
}

bool EzLicenseMgr :: isBranchCheckReq( const char *InstId )
{
	char CfgBranch[ 100 ], CfgVal[ 100 ];

	memset( CfgBranch, 0, sizeof( CfgBranch ) );
	sprintf( CfgBranch, "%s#BRANCHCHECKREQ", InstId );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgBranch, CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching Parameter[%s] from License File..", CfgBranch );
		return false;
	}
	if( !strcasecmp( CfgVal, "Yes" ) )
		return true;
	else
		return false;
}

int EzLicenseMgr :: getBranchLimit( const char *InstId )
{
	char CfgBranch[ 100 ], CfgVal[ 100 ];

	memset( CfgBranch, 0, sizeof( CfgBranch ) );
	sprintf( CfgBranch, "%s#MAXBRANCH", InstId );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgBranch, CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching Parameter[%s] from License File..", CfgBranch );
		return -1;
	}
	if( CheckInteger( CfgVal ) < 0 )
	{
		trace( "Parameter[%s] Should be a Numeric Value...", CfgVal );
		return -1;
	}
	return atoi( CfgVal );
}

bool EzLicenseMgr :: isATMCheckReq( const char *InstId )
{
	char CfgATM[ 100 ], CfgVal[ 100 ];

	memset( CfgATM, 0, sizeof( CfgATM ) );
	sprintf( CfgATM, "%s#ATMCHECKREQ", InstId );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgATM, CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching Parameter[%s] from License File...", CfgATM );
		return false;
	}

	if( !strcasecmp( CfgVal, "Yes" ) )
		return true;
	else
		return false;
}

int EzLicenseMgr :: getATMLimit( const char *InstId )
{
	char CfgATM[ 100 ], CfgVal[ 100 ];

	memset( CfgATM, 0, sizeof( CfgATM ) );
	sprintf( CfgATM, "%s#MAXATM", InstId );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfg_search( FBuffer, CfgATM, CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching Parameter[%s] from License File..", CfgATM );
		return -1;
	}
	if( CheckInteger( CfgVal ) < 0 )
	{
		trace( "Parameter[%s] Should be a Numeric Value...", CfgVal );
		return -1;
	}
	return atoi( CfgVal );
}

int EzLicenseMgr :: CreateLicenseMgrQueue()
{
	LicenseMgrQid = msgget( ( key_t ) LicenseMgrKeyId, IPC_CREAT | 0666 );
	if( LicenseMgrQid < 0 )
	{
		trace( "Error in Creating LicenseMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	return 1;
}

void EzLicenseMgr :: ServiceRequest()
{
	struct EzLicenseMgrReqMsg licensemgrreqmsg;
	struct EzLicenseMgrRespMsg licensemgrrespmsg;
	int Response;

	while( 1 )
	{
		trace( "EzLicenseMgr Waiting for Servicing Request ....");
		memset( &licensemgrreqmsg, 0, sizeof( struct EzLicenseMgrReqMsg ) );

		if( msgrcv( LicenseMgrQid, &licensemgrreqmsg, sizeof( struct EzLicenseMgrReqMsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			if( errno == EINTR )
				continue;
			else if ( errno == EIDRM )
			{
				trace( "Error in Receiving Message From LicenseMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				trace( "LicenseMgr Queue Removed...Creating LicenseMgr Queue");
				if( CreateLicenseMgrQueue() < 0 )
				{
					trace( "Error in Creating LicenseMgr Queue...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
				    trace( "~~~~~~~~~~~~~~~~~~EzLicenseMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
					TaskExit();
				}
				continue;
			}
			else
			{
				trace( "Error in Receiving Message From LicenseMgr Queue SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			    trace( "~~~~~~~~~~~~~~~~~~EzLicenseMgr Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
				TaskExit();
			}
		}

		switch ( licensemgrreqmsg.Command )
		{
			case LICENSE_LOAD_REQ:

			trace( "Received License File Load Request....from NotificationId[%d]", licensemgrreqmsg.NotificationId );
			Response = LoadLicenseFile();

			break;

			case LICENSE_INSTROUTETYPE_CHECK_REQ:

			trace( "Received InstId Check Request for InstRouteType[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			if( isValidInstRouteType( licensemgrreqmsg.LicenseId ) )
				Response = 1;
			else
				Response = -1;

			break;

			case LICENSE_INST_CHECK_REQ:

			trace( "Received InstId Check Request for InstId[%s] InstType[%s] ....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.LicenseType, licensemgrreqmsg.NotificationId );
			if( isValidInst( licensemgrreqmsg.LicenseId, licensemgrreqmsg.LicenseType ) )
				Response = 1;
			else
				Response = -1;

			break;

			case LICENSE_BIN_CHECK_REQ:

			trace( "Received BIN Check Request for InstId[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			if( isBINCheckReq( licensemgrreqmsg.LicenseId ) )
				Response = 1;
			else
				Response = -1;

			break;

			case LICENSE_BIN_LIMIT_REQ:

			trace( "Received BIN Limit Request for InstId[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			Response = getBINLimit( licensemgrreqmsg.LicenseId );

			break;

			case LICENSE_BRANCH_CHECK_REQ:

			trace( "Received Branch Check Request for InstId[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			if( isBranchCheckReq( licensemgrreqmsg.LicenseId ) )
				Response = 1;
			else
				Response = -1;

			break;

			case LICENSE_BRANCH_LIMIT_REQ:

			trace( "Received Branch Limit Request for InstId[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			Response = getBranchLimit( licensemgrreqmsg.LicenseId );

			break;

			case LICENSE_ATM_CHECK_REQ:

			trace( "Received ATM Check Request for InstId[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			if( isATMCheckReq( licensemgrreqmsg.LicenseId ) )
				Response = 1;
			else
				Response = -1;

			break;

			case LICENSE_ATM_LIMIT_REQ:

			trace( "Received ATM Limit Request for InstId[%s]....from NotificationId[%d]", licensemgrreqmsg.LicenseId, licensemgrreqmsg.NotificationId );
			Response = getATMLimit( licensemgrreqmsg.LicenseId );

			break;

			default:

			trace( "Invalid Request Received....");
			Response = -1;

			break;

		}

		memset( &licensemgrrespmsg, 0, sizeof( struct EzLicenseMgrRespMsg ) );

		licensemgrrespmsg.msgtype = licensemgrreqmsg.NotificationId;
		licensemgrrespmsg.Response = Response;

		if( msgsnd( LicenseMgrQid, &licensemgrrespmsg, sizeof( struct EzLicenseMgrRespMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			trace( "Error in Sending License Response for NotificationId[%d] SysErr[%s] ErrNo[%d]", licensemgrrespmsg.msgtype, strerror( errno ), errno );
		else
			trace( "Sent License Response for NotificationId[%d]....", licensemgrrespmsg.msgtype );
	}
}

int main( int argc, char **argv )
{
	EzLicenseMgr licensemgrobj;
	licensemgrobj.initLicenseMgr( argv[ 0 ] );
	licensemgrobj.ServiceRequest();
	return 1;
}

