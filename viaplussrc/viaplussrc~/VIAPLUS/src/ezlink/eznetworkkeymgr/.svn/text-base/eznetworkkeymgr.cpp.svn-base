#include <ezlink/eznetworkkeymgr.h>

void EzNetworkKeyMgr :: initNetworkKeyMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "eznetworkkeymgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( IsTaskRunning( TaskName ) >= 0 )
	{
		trace( "Already one instance of NetworkKeyMgr is Running....." );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( "EzNetworkKeyMgr", TaskName ) < 0 )
	{
		trace( "Error in Creating EzNetworkKeyMgr Channel" );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( securityutilobj.InitEzSecurityUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzSecurityUtil...." );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( securitydriverutilobj.initEzSecurityDriverUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzSecurityDriverUtil...." );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( securitydriverutilobj.LoadNetworkKeySharedMemory() < 0 )
	{
		trace( "Error in Loading NetworkKey Memory..." );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( networkutilobj.initNetworkUtil( this ) < 0 )
	{
		trace( "Error in Initializing NetworkUtil..." );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( busdayutilobj.initBusDayUtil( this ) < 0 )
	{
		trace( "Error in Initializing BusDayUtil..." );
		trace( "^^^^^^^^^^^EzNetworkKeyMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}


void EzNetworkKeyMgr :: processNetworkKeyGenReq( struct EzTxnMsg *keymsg )
{
	char NetworkCommKey[ 65 ];

	keymsg->MsgType = 810;
	if( networkutilobj.readNetworkMemory( keymsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", keymsg->NetworkId );
		keymsg->RespCode = 5;
	}
	else
	{
		if( securitydriverutilobj.readNetworkKey( keymsg->NetworkId ) < 0 )
		{
			trace( "Error in Reading NetworkId[%s] from NetworkKeyMemory...", keymsg->NetworkId );
			keymsg->RespCode = 5;
		}
		else
		{
			memset( NetworkCommKey, 0, sizeof( NetworkCommKey ) );

			if( securityutilobj.GenNetworkAcqCommKey( networkutilobj.getInstId(), keymsg->NetworkId, NetworkCommKey ) < 0 )
			{
				trace( "Error in Generating NetworkCommKey for InstId[%s] NetworkId[%s]...", networkutilobj.getInstId(),keymsg->NetworkId );
				keymsg->RespCode = 5;
			}
			else
			{
				keymsg->RespCode = 0;
				memset( keymsg->RsvFld1, 0, sizeof( keymsg->RsvFld1 ) );
				strcpy( keymsg->RsvFld1, NetworkCommKey );
			}
		}
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )keymsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processNetworkKeyStoreReq( struct EzTxnMsg *keymsg )
{
	struct NetworkKeyMsg networkkeymsg;
	struct EzSecurityMgrQMsg ezsecmgrqmsgObj;

	keymsg->MsgType = 810;

	if( networkutilobj.readNetworkMemory( keymsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", keymsg->NetworkId );
		keymsg->RespCode = 5;
	}
	else
	{
		if( securitydriverutilobj.updateNetworkAcquirerCommKey( keymsg->NetworkId, keymsg->RsvFld1  ) < 0 )
		{
			trace( "Error in Updating NetworkCommKey[%s] for NetworkId[%s] in NetworkKeyMemory...", keymsg->RsvFld1, keymsg->NetworkId );
			keymsg->RespCode = 5;
		}
		else
			keymsg->RespCode = 0;

		memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
		memset( &ezsecmgrqmsgObj, 0, sizeof( struct EzSecurityMgrQMsg ) );

		strcpy( networkkeymsg.NetworkId, keymsg->NetworkId );
		strcpy( networkkeymsg.NetworkCommKey, keymsg->RsvFld1 );

		ezsecmgrqmsgObj.SourceType = EZSEC_TABLE;
		ezsecmgrqmsgObj.CommandCode = EZSEC_ACQCOMMKEY;
		ezsecmgrqmsgObj.OperationCode = EZSEC_UPDATE;
		memcpy( ezsecmgrqmsgObj.SourceBuffer, ( char * )&networkkeymsg, sizeof( struct NetworkKeyMsg ) );

		if( WriteChannel( "EzSecurityMgr", ( char * ) &ezsecmgrqmsgObj, sizeof( struct EzSecurityMgrQMsg ) ) < 0 )
			trace( "Error in Writing Message to EzSecurityMgr Channel...." );

	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )keymsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processNetworkKeyGenResp( struct EzTxnMsg *networkkeymsg )
{


}


void EzNetworkKeyMgr :: processNetworkKeyStoreResp( struct EzTxnMsg *networkkeymsg )
{


}

void EzNetworkKeyMgr :: composeNetworkKeyGenReq( struct EzTxnMsg *keymsg )
{
	char NetworkCommKey[ 65 ];

	keymsg->MsgType = 800;
	if( networkutilobj.readNetworkMemory( keymsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", keymsg->NetworkId );
		return;
	}
	else
	{
		if( securitydriverutilobj.readNetworkKey( keymsg->NetworkId ) < 0 )
		{
			trace( "Error in Reading NetworkId[%s] from NetworkKeyMemory...", keymsg->NetworkId );
			return;
		}
		else
		{
			memset( NetworkCommKey, 0, sizeof( NetworkCommKey ) );

			if( securityutilobj.GenNetworkAcqCommKey( networkutilobj.getInstId(), keymsg->NetworkId, NetworkCommKey ) < 0 )
			{
				trace( "Error in Generating NetworkCommKey for InstId[%s] NetworkId[%s]...", networkutilobj.getInstId(),keymsg->NetworkId );
				return;
			}
			else
			{
				memset( keymsg->RsvFld1, 0, sizeof( keymsg->RsvFld1 ) );
				strcpy( keymsg->RsvFld1, NetworkCommKey );
			}
		}
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )keymsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}


void EzNetworkKeyMgr :: composeNetworkKeyStoreReq( struct EzTxnMsg *keymsg )
{
	char NetworkCommKey[ 65 ];

	keymsg->MsgType = 800;
	if( networkutilobj.readNetworkMemory( keymsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", keymsg->NetworkId );
		return;
	}
	else
	{
		if( securitydriverutilobj.readNetworkKey( keymsg->NetworkId ) < 0 )
		{
			trace( "Error in Reading NetworkId[%s] from NetworkKeyMemory...", keymsg->NetworkId );
			return;
		}
		else
		{
			memset( NetworkCommKey, 0, sizeof( NetworkCommKey ) );

			if( securityutilobj.GenNetworkAcqCommKey( networkutilobj.getInstId(), keymsg->NetworkId, NetworkCommKey ) < 0 )
			{
				trace( "Error in Generating NetworkCommKey for InstId[%s] NetworkId[%s]...", networkutilobj.getInstId(),keymsg->NetworkId );
				return;
			}
			else
			{
				memset( keymsg->RsvFld1, 0, sizeof( keymsg->RsvFld1 ) );
				strcpy( keymsg->RsvFld1, NetworkCommKey );
			}
		}
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )keymsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processLogOnReq( struct EzTxnMsg *networkmsg )
{
	networkmsg->MsgType = 810;

	if( networkutilobj.readNetworkMemory( networkmsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", networkmsg->NetworkId );
		return;
	}
	else
	{
		if( networkutilobj.getNetworkStatus() == NETWORK_STATUS_DOWN )
		{
			if( networkutilobj.setNetworkStatus( networkmsg->NetworkId, NETWORK_STATUS_UP ) < 0 )
			{
				trace( "Error in Marking the NetworkId[%s] Status as UP", networkmsg->NetworkId );
				networkmsg->RespCode = 5;
			}
			else
				networkmsg->RespCode = 0;
		}
		else
			networkmsg->RespCode = 0;
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )networkmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processLogOffReq( struct EzTxnMsg *networkmsg )
{
	networkmsg->MsgType = 810;

	if( networkutilobj.readNetworkMemory( networkmsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", networkmsg->NetworkId );
		return;
	}
	else
	{
		if( networkutilobj.getNetworkStatus() == NETWORK_STATUS_UP )
		{
			if( networkutilobj.setNetworkStatus( networkmsg->NetworkId, NETWORK_STATUS_DOWN ) < 0 )
			{
				trace( "Error in Marking the NetworkId[%s] Status as DOWN", networkmsg->NetworkId );
				networkmsg->RespCode = 5;
			}
			else
				networkmsg->RespCode = 0;
		}
		else
			networkmsg->RespCode = 0;
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )networkmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processSignOnReq( struct EzTxnMsg *networkmsg )
{
	networkmsg->MsgType = 810;

	if( networkutilobj.readNetworkMemory( networkmsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", networkmsg->NetworkId );
		return;
	}
	else
	{
		if( networkutilobj.getNetworkStatus() == NETWORK_STATUS_DOWN )
		{
			if( networkutilobj.setNetworkStatus( networkmsg->NetworkId, NETWORK_STATUS_UP ) < 0 )
			{
				trace( "Error in Marking the NetworkId[%s] Status as UP", networkmsg->NetworkId );
				networkmsg->RespCode = 5;
			}
			else
				networkmsg->RespCode = 0;
		}
		else
			networkmsg->RespCode = 0;
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )networkmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processSignOffReq( struct EzTxnMsg *networkmsg )
{
	networkmsg->MsgType = 810;

	if( networkutilobj.readNetworkMemory( networkmsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", networkmsg->NetworkId );
		return;
	}
	else
	{
		if( networkutilobj.getNetworkStatus() == NETWORK_STATUS_UP )
		{
			if( networkutilobj.setNetworkStatus( networkmsg->NetworkId, NETWORK_STATUS_DOWN ) < 0 )
			{
				trace( "Error in Marking the NetworkId[%s] Status as DOWN", networkmsg->NetworkId );
				networkmsg->RespCode = 5;
			}
			else
				networkmsg->RespCode = 0;
		}
		else
			networkmsg->RespCode = 0;
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )networkmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}
}

void EzNetworkKeyMgr :: processCutOverReq( struct EzTxnMsg *networkmsg )
{
	struct EzNetworkMgrMsg netmsg;

	networkmsg->MsgType = 810;

	if( networkutilobj.readNetworkMemory( networkmsg->NetworkId ) < 0 )
	{
		trace( "Error in Reading NetworkId[%s] from NetworkMemory...", networkmsg->NetworkId );
		return;
	}

	if( !networkutilobj.isCutOverReq() )
	{
		trace( "CutOver is Not Configured for NetworkId[%s]", networkmsg->NetworkId );
		networkmsg->RespCode = 5;
	}
	else
	{
		if( busdayutilobj.updateCutOverDate( networkmsg->NetworkId, networkmsg->BusinessDate ) )
		{
			trace( "Error in Updating BusinessDate[%d] for NetworkId[%s]", networkmsg->BusinessDate, networkmsg->NetworkId );
			networkmsg->RespCode = 5;
		}
		else
			networkmsg->RespCode = 0;
	}
	if( WriteChannel( networkutilobj.getNetworkChannelName(), ( char * )networkmsg, sizeof( struct EzTxnMsg ) ) < 0 )
	{
		trace( "Error in Writing NetworkKeyGenResp Message to Channel[%s]", networkutilobj.getNetworkChannelName() );
	}

	memset( &netmsg, 0, sizeof( EzNetworkMgrMsg ) );
	netmsg.Command = EZLINK_NTWK_UPDATE_CUTOVERDATE;
	strcpy( netmsg.NetworkId, networkmsg->NetworkId );
	netmsg.CutoverDate = networkmsg->BusinessDate;

	if( WriteChannel( "EzNetworkMgr", ( char * ) &netmsg, sizeof( struct EzNetworkMgrMsg) ) < 0 )
		trace( "Error in Writing Update CutOverDate Message to NetworkMgr" );

}


void EzNetworkKeyMgr :: serviceRequest()
{
	int MsgSize;
	struct EzTxnMsg networkkeymsg;

	while( 1 )
	{
		trace( "EzNetworkKeyMgr Waiting For Request....");

		memset( &networkkeymsg, 0, sizeof( struct EzTxnMsg ) );

		if( ReadMessage( ( char * ) &networkkeymsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message From EzNetworkKeyMgr Channel..." );
			sleep( 1 );
			continue;
		}

		switch( networkkeymsg.NetCode )
		{

			case EZLINK_NETCODE_LOGON:

				processLogOnReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_LOGOFF:

				processLogOffReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_SIGNON:

				processSignOnReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_SIGNOFF:

				processSignOffReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_CUTOVER:

				processCutOverReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_KEYSTOREREQ:

				processNetworkKeyStoreReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_KEYGENRESP:

				processNetworkKeyGenResp( &networkkeymsg );

			break;

			case EZLINK_NETCODE_KEYSTORERESP:

				processNetworkKeyStoreResp( &networkkeymsg );

			break;

			case EZLINK_NETCODE_COMPOSE_KEYGENREQ:

				composeNetworkKeyGenReq( &networkkeymsg );

			break;

			case EZLINK_NETCODE_COMPOSE_KEYSTOREREQ:

				composeNetworkKeyStoreReq( &networkkeymsg );

			break;

			default:

				trace( "Invalid NetCode[%d] Received by NetworkKeyMgr...." );
			break;

		}
	}
}


int main( int argc, char **argv )
{
	EzNetworkKeyMgr networkkeymgrobj;
	networkkeymgrobj.initNetworkKeyMgr( argv[ 0 ] );
	networkkeymgrobj.serviceRequest();
	return 1;
}

