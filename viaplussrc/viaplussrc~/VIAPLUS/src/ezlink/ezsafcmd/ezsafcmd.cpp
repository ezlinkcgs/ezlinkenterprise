#include <ezlink/ezsafcmd.h>

void EzSafCmd :: initSafCmd()
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsafcmd.log" );

	if( openDebug( logpath, "ezsafcmd" ) < 0 )
		exit( 0 );

	if( ezsafformatutil.initSAFFormatUtil( this, &ezinstprofileutil, &ezpadssutil ) < 0 )
	{
		printf("\nError in Initializing SAFFormatUtil......" );
		exit( 0 );
	}

	if( initNetworkUtil( this ) < 0 )
	{
		printf("\nError in Initializing NetworkUtil......" );
		exit( 0 );
	}
}

int EzSafCmd :: setSafStatus( const char *NetworkId, const char *SafStatus )
{
	int NetworkStatus;

	if( readNetworkMemory( NetworkId ) < 0 )
	{
		printf("\nInvalid NetworkId[%s]", NetworkId );
		return -1;
	}

	if( strcmp( SafStatus, "PENDING" ) && strcmp( SafStatus, "SKIP" ) && strcmp( SafStatus, "REMOVE" ) )
	{
		printf("\nInvalid Status..Status should be PENDING/SKIP/REMOVE" );
		return -1;
	}

	NetworkStatus = getNetworkStatus();

	if( NetworkStatus == NETWORK_STATUS_UP )
		printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_UP_STR );
	else if( NetworkStatus == NETWORK_STATUS_DOWN )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_DOWN_STR );
	else if( NetworkStatus == NETWORK_STATUS_SAF )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_SAF_STR );
	else if( NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_SAFUPLOAD_STR );
	else if( NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_SAFDOWNLOAD_STR );

	memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
	retval = getNextPendingRecord( NetworkId, &safdbinfo );

	if( retval != 0 )
	{
		printf("\nNo Record")
	}

	if( !strcasecmp( SafStatus, "PENDING" ) )
	{
		retval = updateSafStatus( NetworkId, SAF_STATUS_PENDING );
	}
	else if( !strcasecmp( SafStatus, "SKIP" ) )
	{
		retval = updateSafStatus( NetworkId, SAF_STATUS_SKIPPED );
	}
	else if( !strcasecmp( SafStatus, "REMOVE" ) )
	{

	}

	return 1;
}

int EzSafCmd :: ListSafDetails( const char *NetworkId )
{
	int NetworkStatus;

	if( readNetworkMemory( NetworkId ) < 0 )
	{
		printf("\nInvalid NetworkId[%s]", NetworkId );
		return -1;
	}

	NetworkStatus = getNetworkStatus();

	if( NetworkStatus == NETWORK_STATUS_UP )
		printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_UP_STR );
	else if( NetworkStatus == NETWORK_STATUS_DOWN )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_DOWN_STR );
	else if( NetworkStatus == NETWORK_STATUS_SAF )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_SAF_STR );
	else if( NetworkStatus == NETWORK_STATUS_SAFUPLOAD )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_SAFUPLOAD_STR );
	else if( NetworkStatus == NETWORK_STATUS_SAFDOWNLOAD )
			printf("\n Current Network Status of %s: [%s]", NETWORK_STATUS_SAFDOWNLOAD_STR );

	printf( "\n=============================================================================\n" );


	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsaf.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		printf("\nError in Opening File[%s].....\n", cfgpath );
		return -1;
	}

	MsgTypeCount = cfgutil.getMsgTypeCount( "MSGTYPE" );

	for( int i = 0; i < MsgTypeCount; i++ )
	{
		memset( MsgTypeStr, 0, sizeof( MsgTypeStr ) );
		if( cfgutil.cfg_get_param( "MSGTYPE", MsgTypeStr, i + 1 ) < 0 )
			break;

		printf( "\n==========================================================" );
		printf( "\nMsgType\t\tNRecords" );

		NRecords = getNRecords( NetworkId, atoi( MsgTypeStr ), SAF_ONLINE, &SqlErr );

		if( SqlErr != 1403 && SqlErr != 0 )
			printf("\n%d\t\tOraErr[%05d]", atoi( MsgTypeStr ), NRecords );
		else
			printf("\n%d\t\t%d", atoi( MsgTypeStr ), NRecords );

	}


	for( int i = 0; i < MsgTypeCount; i++ )
	{
		memset( MsgTypeStr, 0, sizeof( MsgTypeStr ) );
		if( cfgutil.cfg_get_param( "MSGTYPE", MsgTypeStr, i + 1 ) < 0 )
			break;

		printf( "\n==========================================================" );
		printf( "\nMsgType\t\tNRecords" );

		NRecords = getNRecords( NetworkId, atoi( MsgTypeStr ), SAF_STANDIN, &SqlErr );

		if( SqlErr != 1403 && SqlErr != 0 )
			printf("\n%d\t\tOraErr[%05d]", atoi( MsgTypeStr ), NRecords );
		else
			printf("\n%d\t\t%d", atoi( MsgTypeStr ), NRecords );

	}

	memset( &safdbinfo, 0, sizeof( struct EzSafDBInfo ) );
	retval = getNextPendingRecord( txnmsg_ptr->NetworkId, &safdbinfo );

	if( retval == 1403 )
		printf( "\nNo Pending Record for NetworkId[%s] in EzSafDB", NetworkId );
	else if( retval != 0 )
		printf( "\nCurrent SAF Record for NetworkId[%s] is having OraErr[%05d]", retval );
	else
	{
		memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		ezsafformatutil.decomposeSAFDetailedRec( &txnmsg, safdbinfo.SAFDetailRec );
		printf( "\nCurrent SAF Record Details:" );
		if( txnmsg.MerchantType == 6011 )
		{
			printf( "\nRecordNo\t\t\t\tMsgType\tCHN\tAccountNo\tTxnDate\tTxnTime\tTraceNo\tTerminalId\tAmount" );
			printf( "%s%d%s%s%d%d%d%s%s", safdbinfo.SafRecordNo, txnmsg.MsgType, txnmsg.chn, txnmsg.FromAccount, txnmsg.TranDate, txnmsg.TranTime, txnmsg.TraceNo, txnmsg.TerminalId, txnmsg.Amount );
		}
		else if ( txnmsg.MerchantType == 6012 )
		{
			printf( "\nRecordNo\t\t\t\tMsgType\tAccountNo\tTxnDate\tTxnTime\tTraceNo\tTerminalId\tAmount" );
			printf( "%s%d%s%d%d%d%s%s", safdbinfo.SafRecordNo, txnmsg.MsgType, txnmsg.FromAccount, txnmsg.TranDate, txnmsg.TranTime, txnmsg.TraceNo, txnmsg.TerminalId, txnmsg.Amount );
		}
		else
		{
			printf( "\nRecordNo\t\t\t\tMsgType\tCHN\tAccountNo\tTxnDate\tTxnTime\tTraceNo\tTerminalId\tAmount" );
			printf( "%s%d%s%s%d%d%d%s%s", safdbinfo.SafRecordNo, txnmsg.MsgType, txnmsg.chn, txnmsg.FromAccount, txnmsg.TranDate, txnmsg.TranTime, txnmsg.TraceNo, txnmsg.TerminalId, txnmsg.Amount );
		}

		if( safdbinfo.SafStatus == SAF_STATUS_PENDING )
			printf( "");
		else if ( safdbinfo.SafStatus == SAF_STATUS_BADRESPONSE )
			printf( "");
		else
		{

		}

		if( safdbinfo.SafResponseStatus == SAF_RESPONSE_RCVD )
			printf( "" );
		else
		{

		}

		if( safdbinfo.SafNetworkStatus == SAF_ONLINE )
			printf( "" );
		else
			printf( "" );

	}
	return 1;
}

int EzSafCmd :: serviceSafCmd( int argc, char **argv )
{
	char command[ 100 ], NetworkId[ 17 ];
	int NetworkStatus;

	if( argc == 1 )
	{
		while( 1 )
		{
			printf("\nezsafcmd>");
			waitforinput();
			memset( command, 0, sizeof( command ) );
			getCommand( command, 1 );
			if( strlen( command ) == 0 )
				continue;
			if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 2 );
				if( strlen( command ) == 0 )
				{
					printf("\ninvalid command..type help for more...." );
					continue;
				}
				if( readNetworkMemory( command ) ) < 0 )
				{
					printf("\n %s is not a valid NetworkId", command );
					continue;
				}
				ListSafDetails( command );
			}
		}
	}
}

int main( int argc, char **argv )
{
	EzSafCmd safcmdobj;
	if( safcmdobj.initSafCmd( argv[ 0 ] ) < 0 )
	{
		safcmdobj.trace( "^^^^^^^^^^^^^^^EzSafCmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		safcmdobj.closeDebug();
		exit( 0 );
	}
	safcmdobj.serviceSafCmd( argc, argv );
	return 1;
}
