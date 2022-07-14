#include <ezagentmms/ezagentmmscmd.h>

int EzMMSCmd :: initMMSCmd( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezagentmmscmd.log" );

	if( openCmdDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^ezmmscmd Started Running^^^^^^^^^^^^^^^^^^^^" );

	if( dbutil.initDBUtil( "ezagentmmscmd", this, "EZAGENTMMS" ) < 0 )
	{
		trace( "Error in Initializing DBUtil...." );
		printf("\nError in Initializing DBUtil...." );
		exit( 0 );
	}

	if( shmutil.init( this ) < 0 )
	{
		trace( "Error in Initializing SHMUtil...." );
		printf("\nError in Initializing SHMUtil...." );
		exit( 0 );
	}
	return 1;
}

int EzMMSCmd :: serviceAddMerScheme( const char *InstId, const char *BIN )
{
	return shmutil.addMerScheme( InstId, BIN );
}

int EzMMSCmd :: serviceUpdateMerScheme( const char *InstId, const char *BIN )
{
	return shmutil.updateMerScheme( InstId, BIN );
}

int EzMMSCmd :: serviceDeleteMerScheme( const char *InstId, const char *BIN )
{
	return shmutil.deleteMerScheme( InstId, BIN );
}

void EzMMSCmd :: serviceListMerScheme( const char *InstId, const char *BIN )
{
	shmutil.ListMerScheme( InstId, BIN );
}

void EzMMSCmd :: serviceListMerScheme( const char *InstId )
{
	shmutil.ListMerScheme( InstId );
}

void EzMMSCmd :: serviceListMerScheme()
{
	shmutil.ListMerScheme();
}

int EzMMSCmd :: serviceAddMerProfile( const char *InstId, const char *MerchantId )
{
	return shmutil.addMerProfile( InstId, MerchantId );
}

int EzMMSCmd :: serviceUpdateMerProfile( const char *InstId, const char *MerchantId )
{
	return shmutil.updateMerProfile( InstId, MerchantId );
}

int EzMMSCmd :: serviceDeleteMerProfile( const char *InstId, const char *MerchantId )
{
	return shmutil.deleteMerProfile( InstId, MerchantId );
}

void EzMMSCmd :: serviceListMerProfile( const char *InstId, const char *MerchantId )
{
	shmutil.ListMerProfile( InstId, MerchantId );
}

void EzMMSCmd :: serviceListMerProfile( const char *InstId )
{
	shmutil.ListMerProfile( InstId );
}

void EzMMSCmd :: serviceListMerProfile()
{
	trace( "Calling List Merchant Profile...." );
	shmutil.ListMerProfile();
}

int EzMMSCmd :: serviceAddStorProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	return shmutil.addStorProfile( InstId, MerchantId, StoreId );
}

int EzMMSCmd :: serviceUpdateStorProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	return shmutil.updateStorProfile( InstId, MerchantId, StoreId );
}

int EzMMSCmd :: serviceDeleteStorProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	return shmutil.deleteStorProfile( InstId, MerchantId, StoreId );
}

void EzMMSCmd :: serviceListStorProfile( const char *InstId, const char *MerchantId, const char *StoreId )
{
	shmutil.ListStorProfile( InstId, MerchantId, StoreId );
}

void EzMMSCmd :: serviceListStorProfile( const char *InstId, const char *MerchantId )
{
	shmutil.ListStorProfile( InstId, MerchantId );
}

void EzMMSCmd :: serviceListStorProfile( const char *InstId )
{
	shmutil.ListStorProfile( InstId );
}

void EzMMSCmd :: serviceListStorProfile()
{
	shmutil.ListStorProfile();
}

int EzMMSCmd :: serviceAddTermProfile( const char *MachineId )
{
	return shmutil.addTermProfile( MachineId );
}

int EzMMSCmd :: serviceUpdateTermProfile( const char *MachineId )
{
	return shmutil.updateTermProfile( MachineId );
}

int EzMMSCmd :: serviceDeleteTermProfile( const char *MachineId )
{
	return shmutil.deleteTermProfile( MachineId );
}

void EzMMSCmd :: serviceListTermProfile( const char *MachineId )
{
	shmutil.ListTermProfile( MachineId );
}

void EzMMSCmd :: serviceListTermProfile()
{
	shmutil.ListTermProfile();
}

int EzMMSCmd :: serviceAddFIT( const char *RecordId )
{
	return shmutil.addFIT( RecordId );
}

int EzMMSCmd :: serviceUpdateFIT( const char *RecordId )
{
	return shmutil.updateFIT( RecordId );
}

int EzMMSCmd :: serviceDeleteFIT( const char *RecordId )
{
	return shmutil.deleteFIT( RecordId );
}

void EzMMSCmd :: serviceListFIT( const char *RecordId )
{
	shmutil.ListFIT( RecordId );
}

void EzMMSCmd :: serviceListFIT()
{
	shmutil.ListFIT();
}

int EzMMSCmd :: serviceAddTxnCode( const char *RecordId )
{
	return shmutil.addTxnCode( RecordId );
}

int EzMMSCmd :: serviceUpdateTxnCode( const char *RecordId )
{
	return shmutil.updateTxnCode( RecordId );
}

int EzMMSCmd :: serviceDeleteTxnCode( const char *RecordId )
{
	return shmutil.deleteTxnCode( RecordId );
}

void EzMMSCmd :: serviceListTxnCode( const char *RecordId )
{
	shmutil.ListTxnCode( RecordId );
}

void EzMMSCmd :: serviceListTxnCode()
{
	shmutil.ListTxnCode();
}

int EzMMSCmd :: serviceAddNarration( const char *RecordId )
{
	return shmutil.addNarration( RecordId );
}

int EzMMSCmd :: serviceUpdateNarration( const char *RecordId )
{
	return shmutil.updateNarration( RecordId );
}

int EzMMSCmd :: serviceDeleteNarration( const char *RecordId )
{
	return shmutil.deleteNarration( RecordId );
}

void EzMMSCmd :: serviceListNarration( const char *RecordId )
{
	shmutil.ListNarration( RecordId );
}

void EzMMSCmd :: serviceListNarration()
{
	shmutil.ListNarration();
}

int EzMMSCmd :: serviceAddPOSTransactionRel( const char *RecordId )
{
	return shmutil.addPOSTransactionRel( RecordId );
}

int EzMMSCmd :: serviceUpdatePOSTransactionRel( const char *RecordId )
{
	return shmutil.updatePOSTransactionRel( RecordId );
}

int EzMMSCmd :: serviceDeletePOSTransactionRel( const char *RecordId )
{
	return shmutil.deletePOSTransactionRel( RecordId );
}

void EzMMSCmd :: serviceListPOSTransactionRel( const char *RecordId )
{
	shmutil.ListPOSTransactionRel( RecordId );
}

void EzMMSCmd :: serviceListPOSTransactionRel()
{
	shmutil.ListPOSTransactionRel();
}

int EzMMSCmd :: serviceAddTMSChProperty( const char *ChannelName )
{
	return shmutil.addTMSChProperty( ChannelName );
}

int EzMMSCmd :: serviceUpdateTMSChProperty( const char *ChannelName )
{
	return shmutil.updateTMSChProperty( ChannelName );
}

int EzMMSCmd :: serviceDeleteTMSChProperty( const char *ChannelName )
{
	return shmutil.deleteTMSChProperty( ChannelName );
}

void EzMMSCmd :: serviceListTMSChProperty( const char *ChannelName )
{
	shmutil.ListTMSChProperty( ChannelName );
}

void EzMMSCmd :: serviceListTMSChProperty()
{
	shmutil.ListTMSChProperty();
}

int EzMMSCmd :: serviceAddTMSRtInfo( const char *RecordId )
{
	return shmutil.addTMSRtInfo( RecordId );
}

int EzMMSCmd :: serviceUpdateTMSRtInfo( const char *RecordId )
{
	return shmutil.updateTMSRtInfo( RecordId );
}

int EzMMSCmd :: serviceDeleteTMSRtInfo( const char *RecordId )
{
	return shmutil.deleteTMSRtInfo( RecordId );
}

void EzMMSCmd :: serviceListTMSRtInfo( const char *RecordId )
{
	shmutil.ListTMSRtInfo( RecordId );
}

void EzMMSCmd :: serviceListTMSRtInfo()
{
	shmutil.ListTMSRtInfo();
}

int EzMMSCmd :: serviceAddTMSRtSelect( const char *RouteSelectId )
{
	return shmutil.addTMSRtSelect( RouteSelectId );
}

int EzMMSCmd :: serviceUpdateTMSRtSelect( const char *RouteSelectId )
{
	return shmutil.updateTMSRtSelect( RouteSelectId );
}

int EzMMSCmd :: serviceDeleteTMSRtSelect( const char *RouteSelectId )
{
	return shmutil.deleteTMSRtSelect( RouteSelectId );
}

void EzMMSCmd :: serviceListTMSRtSelect( const char *RouteSelectId )
{
	shmutil.ListTMSRtSelect( RouteSelectId );
}

void EzMMSCmd :: serviceListTMSRtSelect()
{
	shmutil.ListTMSRtSelect();
}

int EzMMSCmd :: serviceAddTMSMsgTran( const char *MsgTranslateId )
{
	return shmutil.addTMSMsgTran( MsgTranslateId );
}

int EzMMSCmd :: serviceUpdateTMSMsgTran( const char *MsgTranslateId )
{
	return shmutil.updateTMSMsgTran( MsgTranslateId );
}

int EzMMSCmd :: serviceDeleteTMSMsgTran( const char *MsgTranslateId )
{
	return shmutil.deleteTMSMsgTran( MsgTranslateId );
}

void EzMMSCmd :: serviceListTMSMsgTran( const char *MsgTranslateId )
{
	shmutil.ListTMSMsgTran( MsgTranslateId );
}

void EzMMSCmd :: serviceListTMSMsgTran()
{
	shmutil.ListTMSMsgTran();
}

int EzMMSCmd :: serviceAddTMSInBndProperty( const char *RecordId )
{
	return shmutil.addTMSInBndProperty( RecordId );
}

int EzMMSCmd :: serviceUpdateTMSInBndProperty( const char *RecordId )
{
	return shmutil.updateTMSInBndProperty( RecordId );
}

int EzMMSCmd :: serviceDeleteTMSInBndProperty( const char *RecordId )
{
	return shmutil.deleteTMSInBndProperty( RecordId );
}

void EzMMSCmd :: serviceListTMSInBndProperty( const char *RecordId )
{
	shmutil.ListTMSInBndProperty( RecordId );
}

void EzMMSCmd :: serviceListTMSInBndProperty()
{
	shmutil.ListTMSInBndProperty();
}

int EzMMSCmd :: serviceAddTMSTransactionRefSelect( const char *RecordId )
{
	return shmutil.addTMSTransactionRefSelect( RecordId );
}

int EzMMSCmd :: serviceUpdateTMSTransactionRefSelect( const char *RecordId )
{
	return shmutil.updateTMSTransactionRefSelect( RecordId );
}

int EzMMSCmd :: serviceDeleteTMSTransactionRefSelect( const char *RecordId )
{
	return shmutil.deleteTMSTransactionRefSelect( RecordId );
}

void EzMMSCmd :: serviceListTMSTransactionRefSelect( const char *RecordId )
{
	shmutil.ListTMSTransactionRefSelect( RecordId );;
}

void EzMMSCmd :: serviceListTMSTransactionRefSelect()
{
	shmutil.ListTMSTransactionRefSelect();
}

int EzMMSCmd :: serviceMMSCmd( int argc, char **argv )
{
	char InstId[ 50 ], command[ 100 ], command1[ 100 ], command2[ 100 ];
	printf( "\n******************Ezlink AGENT_MMS System Command Interface****************");

	while( 1 )
	{
		printf( "\nezagentmmscmd>" );
		waitforinput();
		memset( command, 0, sizeof( command ) );
		getCommand( command, 1 );
		if( strlen( command ) == 0 )
			continue;
		trace( "command[%s]", command );
		if( !strcasecmp( command, "Merchant" ) )
		{
			memset( command, 0, sizeof( command ) );
			getCommand( command, 2 );
			trace( "command1[%s]", command );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddMerProfile( command, command1 );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateMerProfile( command, command1 );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteMerProfile( command, command1 );
			}
			else if( !strcasecmp( command, "List" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				trace( "command2[%s]", command );
				if( strlen( command ) == 0 )
				{
					serviceListMerProfile();
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				trace( "command3[%s]", command );
				if( strlen( command1 ) == 0 )
				{
					serviceListMerProfile( command );
					continue;
				}
				serviceListMerProfile( command, command1 );
			}
		}
		else if( !strcasecmp( command, "Terminal" ) )
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
				serviceAddTermProfile( command );
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
				serviceUpdateTermProfile( command );
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
				serviceDeleteTermProfile( command );
			}
			else if( !strcasecmp( command, "List" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTermProfile();
					continue;
				}
				serviceListTermProfile( command );
			}
		}
		else if( !strcasecmp( command, "Store" ) )
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command2, 0, sizeof( command2 ) );
				getCommand( command2, 5 );
				if( strlen( command2 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddStorProfile( command, command1, command2 );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command2, 0, sizeof( command2 ) );
				getCommand( command2, 5 );
				if( strlen( command2 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateStorProfile( command, command1, command2 );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				memset( command2, 0, sizeof( command2 ) );
				getCommand( command2, 5 );
				if( strlen( command2 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteStorProfile( command, command1, command2 );
			}
			else if( !strcasecmp( command, "List" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListStorProfile();
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					serviceListStorProfile( command );
					continue;
				}
				memset( command2, 0, sizeof( command2 ) );
				getCommand( command2, 5 );
				if( strlen( command2 ) == 0 )
				{
					serviceListStorProfile( command, command1 );
					continue;
				}
				serviceListStorProfile( command, command1, command2 );
			}
		}
		else if( !strcasecmp( command, "FIT" ) )
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
				serviceAddFIT( command );
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
				serviceUpdateFIT( command );
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
				serviceDeleteFIT( command );
			}
			else if( !strcasecmp( command, "List" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListFIT();
					continue;
				}
				serviceListFIT( command );
			}
		}
		else if( !strcasecmp( command, "Scheme" ) )
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceAddMerScheme( command, command1 );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceUpdateMerScheme( command, command1 );
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
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					printf("\n invalid command ..type help for more");
					continue;
				}
				serviceDeleteMerScheme( command, command1 );
			}
			else if( !strcasecmp( command, "List" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListMerScheme();
					continue;
				}
				memset( command1, 0, sizeof( command1 ) );
				getCommand( command1, 4 );
				if( strlen( command1 ) == 0 )
				{
					serviceListMerScheme( command );
					continue;
				}
				serviceListMerScheme( command, command1 );
			}
		}
		else if( !strcasecmp( command, "TxnCode" ) )
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
				serviceAddTxnCode( command );
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
				serviceUpdateTxnCode( command );
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
				serviceDeleteTxnCode( command );
			}
			else if( !strcasecmp( command, "List" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTxnCode();
					continue;
				}
				serviceListTxnCode( command );
			}
		}
		else if( !strcasecmp( command, "Narration" ) )
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
				serviceAddNarration( command );
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
				serviceUpdateNarration( command );
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
				serviceDeleteNarration( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListNarration();
					continue;
				}
				serviceListNarration( command );
			}
		}
		else if( !strcasecmp( command, "TxnRel" ) )
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
				serviceAddPOSTransactionRel( command );
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
				serviceUpdatePOSTransactionRel( command );
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
				serviceDeletePOSTransactionRel( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListPOSTransactionRel();
					continue;
				}
				serviceListPOSTransactionRel( command );
			}
		}
		else if( !strcasecmp( command, "ChannelProperty" ) )
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
				serviceAddTMSChProperty( command );
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
				serviceUpdateTMSChProperty( command );
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
				serviceDeleteTMSChProperty( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTMSChProperty();
					continue;
				}
				serviceListTMSChProperty( command );
			}
		}
		else if( !strcasecmp( command, "RouteInfo" ) )
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
				serviceAddTMSRtInfo( command );
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
				serviceUpdateTMSRtInfo( command );
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
				serviceDeleteTMSRtInfo( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTMSRtInfo();
					continue;
				}
				serviceListTMSRtInfo( command );
			}
		}
		else if( !strcasecmp( command, "RouteSelect" ) )
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
				serviceAddTMSRtSelect( command );
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
				serviceUpdateTMSRtSelect( command );
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
				serviceDeleteTMSRtSelect( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTMSRtSelect();
					continue;
				}
				serviceListTMSRtSelect( command );
			}
		}
		else if( !strcasecmp( command, "MsgTranslate" ) )
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
				serviceAddTMSMsgTran( command );
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
				serviceUpdateTMSMsgTran( command );
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
				serviceDeleteTMSMsgTran( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTMSMsgTran();
					continue;
				}
				serviceListTMSMsgTran( command );
			}
		}
		else if( !strcasecmp( command, "InBoundProperty" ) )
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
				serviceAddTMSInBndProperty( command );
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
				serviceUpdateTMSInBndProperty( command );
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
				serviceDeleteTMSInBndProperty( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTMSInBndProperty();
					continue;
				}
				serviceListTMSInBndProperty( command );
			}
		}
		else if( !strcasecmp( command, "TxnRefSelect" ) )
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
				serviceAddTMSTransactionRefSelect( command );
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
				serviceUpdateTMSTransactionRefSelect( command );
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
				serviceDeleteTMSTransactionRefSelect( command );
			}
			else if( !strcasecmp( command, "list" ) )
			{
				memset( command, 0, sizeof( command ) );
				getCommand( command, 3 );
				if( strlen( command ) == 0 )
				{
					serviceListTMSTransactionRefSelect();
					continue;
				}
				serviceListTMSTransactionRefSelect( command );
			}
		}
		else if( !strcmp( command, "help" ) )
		{
			printf("\n <Merchant> <Add> <InstId> <MerchantId>" );
			printf("\n <Merchant> <Update> <InstId> <MerchantId>" );
			printf("\n <Merchant> <Delete> <InstId> <MerchantId>" );
			printf("\n <Merchant> <List> <InstId> <MerchantId>" );
			printf("\n <Merchant> <List> <InstId>" );
			printf("\n <Merchant> <List>" );
			printf("\n <Store> <Add> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <Update> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <Delete> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <List> <InstId> <MerchantId> <StoreId>" );
			printf("\n <Store> <List> <InstId> <MerchantId>" );
			printf("\n <Store> <List> <InstId>" );
			printf("\n <Store> <List>" );
			printf("\n <Terminal> <Add> <MachineId>" );
			printf("\n <Terminal> <Update> <MachineId>" );
			printf("\n <Terminal> <Delete> <MachineId>" );
			printf("\n <Terminal> <List> <MachineId>" );
			printf("\n <Terminal> <List>" );
			printf("\n <FIT> <Add> <RecordId>" );
			printf("\n <FIT> <Update> <RecordId>" );
			printf("\n <FIT> <Delete> <RecordId>" );
			printf("\n <FIT> <List> <RecordId>" );
			printf("\n <FIT> <List>" );
			printf("\n <Scheme> <Add> <InstId> <BIN>" );
			printf("\n <Scheme> <Update> <InstId> <BIN>" );
			printf("\n <Scheme> <List> <InstId> <BIN>" );
			printf("\n <Scheme> <List> <InstId> <BIN>" );
			printf("\n <Scheme> <List> <InstId>" );
			printf("\n <Scheme> <List>" );
			printf("\n <TxnCode> <Add> <RecordId>" );
			printf("\n <TxnCode> <Update> <RecordId>" );
			printf("\n <TxnCode> <Delete> <RecordId>" );
			printf("\n <TxnCode> <List> <RecordId>" );
			printf("\n <TxnCode> <List>" );
			printf("\n <Narration> <Add> <RecordId>" );
			printf("\n <Narration> <Update> <RecordId>" );
			printf("\n <Narration> <Delete> <RecordId>" );
			printf("\n <Narration> <List> <RecordId>" );
			printf("\n <Narration> <List>" );
			printf("\n <TxnRel> <Add> <RecordId>" );
			printf("\n <TxnRel> <Update> <RecordId>" );
			printf("\n <TxnRel> <Delete> <RecordId>" );
			printf("\n <TxnRel> <List> <RecordId>" );
			printf("\n <TxnRel> <List>" );
			printf("\n <ChannelProperty> <Add> <ChannelName>" );
			printf("\n <ChannelProperty> <Update> <ChannelName>" );
			printf("\n <ChannelProperty> <Delete> <ChannelName>" );
			printf("\n <ChannelProperty> <List> <ChannelName>" );
			printf("\n <ChannelProperty> <List>" );
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
			printf("\n <InBoundProperty> <Add> <RecordId>" );
			printf("\n <InBoundProperty> <Update> <RecordId>" );
			printf("\n <InBoundProperty> <Delete> <RecordId>" );
			printf("\n <InBoundProperty> <List> <RecordId>" );
			printf("\n <RouteInfo> <List>" );
			printf("\n <TxnRefSelect> <Add> <RecordId>" );
			printf("\n <TxnRefSelect> <Update> <RecordId>" );
			printf("\n <TxnRefSelect> <Delete> <RecordId>" );
			printf("\n <TxnRefSelect> <List> <RecordId>" );
			printf("\n <RouteInfo> <List>" );
		}
		else if( !strcmp( command, "quit" )  || !strcmp( command, "exit" ) )
			break;
		else
		{
			printf("\n invaild command ..type help for more" );
			continue;
		}
	}
	return 1;
}

int main( int argc, char **argv )
{
	EzMMSCmd mmscmdobj;
	if( mmscmdobj.initMMSCmd( argv[ 0 ] ) < 0 )
	{
		mmscmdobj.trace( "^^^^^^^^^^^^^^^ezagentmmscmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		mmscmdobj.closeDebug();
		exit( 0 );
	}
	mmscmdobj.serviceMMSCmd( argc, argv );
	return 1;
}

