#include <ezlink/ezswitchmon.h>

EzSwitchMon :: EzSwitchMon( )
{

}
EzSwitchMon :: ~EzSwitchMon( )
{

}

void EzSwitchMon :: InitEzSwitchMon( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezswitchmon.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzSwitchMon Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
    	trace( "^^^^^^^^^^^EzSwitchMon Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
	}

	if( CreateChannel( "EzSwitchMon", TaskName ) < 0 )
	{
		trace( "Error in Creating Channel EzSwitchMonitor" );
    	trace( "^^^^^^^^^^^EzSwitchMon Ended Abnormally^^^^^^^^^^^^^");
    	closeDebug();
    	TaskExit();
    }

	if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing DBUtil.... " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzSwitchMon Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}

	if( dbutil.DBConnect() < 0 )
	{
		trace( DEBUG_ERROR, "Error in Connecting with database " );
		trace( DEBUG_CRITICAL, "^^^^^^^^^^^EzSwitchMon Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );
}

void EzSwitchMon :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize, retval;
	char Message[ MESSAGE_SIZE + 1 ];
	char TxnDesc[ TXNDESC + 1 ];
	char TxnBuffer[ MESSAGE_SIZE + 1 ];

	while( 1 )
	{
		trace( "EzSwitchMonitor Waiting for Request....");

		memset( Message, 0, sizeof( Message ) );
		if( ReadMessage( Message, &MsgSize ) < 0 )
		{
			trace( DEBUG_ERROR,  "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
		    continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetSourceChannelName() );
			memset( TempStr, 0, sizeof( TempStr ) );
			getToken( Message, TempStr, GUI_FS, 1 );

			if( !strcasecmp( TempStr, MON_COMMAND_TXNMON ) )
			{
				//Handle for TxnMonitoring Request
				if ( readTxnMemory( TxnBuffer, MaxReq ) < 0 )
					trace( "Unable to Read Transaction Buffer from Shared Memory" );
				else
				{
					if( WritePortChannel( MON_PORT, TxnBuffer, strlen( TxnBuffer ) ) < 0 )
						trace( "Error in Writing Message to Port[%s]", MON_PORT );
					else
						trace( "Written Message to Port[%s]", MON_PORT );
				}

			}
			else if ( !strcasecmp ( TempStr, MON_COMMAND_TASKMON ) )
			{
				//Handle for Task Monitoring Request
			}
			else if ( !strcasecmp ( TempStr, MON_COMMAND_QMON ) )
			{
				//Handle for Queue Monitoring Request
			}
			else
			{
				//Invalid Command
			}
		}
		else
		{
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
		    memcpy( &txnmsg, Message, sizeof( struct EzTxnMsg ) );

		    if ( composeTxnDescription( &txnmsg, TxnDesc ) < 0 )
		    {
		    	trace( "Error in Composing Txn Desc for MsgType[%d] TxnCode[%d] RespCode[%d]", txnmsg.MsgType, txnmsg.TxnCode, txnmsg.RespCode );
		    	continue;
		    }

		    trace( "Composed TxnDesc[%s]", TxnDesc );


		    if ( insertTxnMemory( TxnDesc ) < 0 )
			{
				trace( "Unable to Insert Transaction in Memory" );
			}
		    }

		    if ( !strcmp( txnmsg.DeviceType, "ATM" ) )
		    {
		    	retval = updateAtmMon( &txnmsg ) ;
		    	if ( retval < 0 )
		    		trace( DEBUG_ERROR, "Error in Updating Transaction " );
		    }


		}


	}
}
int main( int argc, char **argv )
{
	EzSwitchMon ezswitchmonobj;
	ezswitchmonobj.InitEzSwitchMon( argv[ 0 ] );
	ezswitchmonobj.ServiceRequest();
	return 1;
}

