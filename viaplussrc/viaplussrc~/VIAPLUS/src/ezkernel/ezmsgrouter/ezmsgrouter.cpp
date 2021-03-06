#include <ezkernel/ezmsgrouter.h>

EzMsgRouter :: EzMsgRouter()
{
}

EzMsgRouter :: ~EzMsgRouter()
{
}

void EzMsgRouter :: InitEzMsgRouter( char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmsgrouter.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^^^^^^^^^^^^^^EzMsgRouter Started^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( initChannelParam( this ) < 0 )
	{
		trace( "Error in Initializing ChannelParam...." );
		trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( InitEzMsgRouterUtil( this, this, false ) < 0 )
	{
		trace( "Error in Initializing EzMsgRouterUtil" );
		trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateEzMsgRouterChannel() < 0 )
	{
		trace( "Error in Creating EzMsgRouter Channel" );
		trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( IsTaskRunning( TaskName ) < 0 )
	{
		if( SetEzMsgRouterSemaphore() < 0 )
		{
			trace( "Error in Setting EzMsgRouter Semaphore" );
			trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
	}

	if( InitEzCommUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzCommUtil" );
		trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	EzMsgRouterQid = GetEzMsgRouterQid();
	EzMsgPortQid = GetEzPortQid();
	TaskInit();
	initEzSigUtil( this );
}

void EzMsgRouter :: startEzMsgRouter()
{
	struct EzChannelMsg RequestMsg;
	struct EzChannelQMsg requestMsg;
	struct EzMsgRouterTable msgrouter_rec;
	int PortId, ChannelKeyId, ChannelQid, MaxBuffer;
	char TaskName[ TASKNAME_SIZE + 1 ];

	while( 1 )
	{
		trace( "EzMsgRouter waiting for request .....");
		memset( &RequestMsg, 0, sizeof( struct EzChannelMsg ) );
		if( readFromMsgRouterChannel( &RequestMsg ) < 0 )
		{
			trace( "Fatal Error...Error in Receiving Message From EzMsgRouter Memory..ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
			trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			exit( 0 );
		}
		trace( "ChannelSource[%c]--ChannelDest[%c]--SrcChannel[%s]--DestChannel[%s]--Message[%s]--MsgSize[%d]", RequestMsg.ChannelSource, RequestMsg.ChannelDest, RequestMsg.SrcChannel, RequestMsg.DestChannel, RequestMsg.Message, RequestMsg.MsgSize );

		if( ( RequestMsg.ChannelSource == SRC_PORT_CHANNEL ) && ( RequestMsg.ChannelDest == SRC_PORT_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Port %s]->Destination[Port %s]", RequestMsg.SrcChannel, RequestMsg.DestChannel );

			if( LocatePortName( RequestMsg.DestChannel, &PortId ) < 0 )
			{
				trace( "Error in Locating Port[%s]", RequestMsg.DestChannel );
				continue;
			}
			trace( "Locate DestPort[%s] with PortId[%d]", RequestMsg.DestChannel );

			if( !IsPortUp( RequestMsg.DestChannel ) )
			{
				trace( "Port[%s] with Pid[%d] Not Running..Cannot Route the Message", RequestMsg.DestChannel, PortId );
				continue;
			}
			memset( &requestMsg, 0, sizeof( struct EzChannelQMsg ) );
			memcpy( &requestMsg.chmsg, &RequestMsg, sizeof( struct EzChannelMsg ) );
			requestMsg.msgtype = PortId;

			if( msgsnd( EzMsgPortQid, &requestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			{
				if( errno == EIDRM )
				{
					trace( "Fatal Error..EzChannelMgrPort Queue is Removed...Creating the EzChannelMgrPort Queue Once Again" );
					if( CreateEzChannelMgrPortQueue() < 0 )
						continue;
					if( msgsnd( EzMsgPortQid, &requestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					{
						trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", requestMsg.chmsg.DestChannel, errno, strerror( errno ) );
						continue;
					}
				}
				else
				{
					trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", requestMsg.chmsg.DestChannel, errno, strerror( errno ) );
					continue;
				}
			}
		}
		else if( ( RequestMsg.ChannelSource == SRC_PORT_CHANNEL ) && ( RequestMsg.ChannelDest == SRC_TASK_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Port %s]->Destination[Channel %s]", RequestMsg.SrcChannel, RequestMsg.DestChannel );

			memset( TaskName, 0, sizeof( TaskName ) );
			if( LocateChannel( RequestMsg.DestChannel, TaskName, &ChannelQid, &ChannelKeyId ) < 0 )
			{
				trace( "Error Locating Channel[%s]", RequestMsg.DestChannel );
				continue;
			}
			trace( "Located Channel[%s] with ChannelKeyId[%d] OwnerTaskName[%s]", RequestMsg.DestChannel, ChannelKeyId, TaskName );
			if( strcmp( TaskName, CHANNEL_INIT_TASK_NAME ) )
			{
				if( !IsTaskRunning( TaskName ) )
				{
					trace( "Channel[%s] OwnerTask[%s] is not running..Cannot Route the Message", RequestMsg.DestChannel, TaskName );
					continue;
				}
			}
			memset( &msgrouter_rec, 0, sizeof( struct EzMsgRouterTable ) );
			if( readMsgRouterTable( RequestMsg.DestChannel, &msgrouter_rec ) < 0 )
			{
				MaxBuffer = getMaxBufferSize( RequestMsg.DestChannel );
				if( MaxBuffer < 0 )
				{
					trace( "Error in Getting MaxBufferSize for Channel[%s]", RequestMsg.DestChannel );
					continue;
				}
				if( createTaskChannel( RequestMsg.DestChannel, MaxBuffer ) < 0 )
				{
					trace( "Error in Creating Task Channel[%s]", RequestMsg.DestChannel );
					continue;
				}
				if( readMsgRouterTable( RequestMsg.DestChannel, &msgrouter_rec ) < 0 )
				{
					trace( "Error in Reading ChannelName[%s] from MsgRouter Table...", RequestMsg.DestChannel );
					continue;
				}
			}
			if( writeTaskChannel( &msgrouter_rec, RequestMsg ) < 0 )
				trace( "Error in Writing Message to TaskChannel[%s]...", RequestMsg.DestChannel );
		}
		else if( ( RequestMsg.ChannelSource == SRC_TASK_CHANNEL ) && ( RequestMsg.ChannelDest == SRC_PORT_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Channel %s]->Destination[Port %s]", RequestMsg.SrcChannel, RequestMsg.DestChannel );

			if( LocatePortName( RequestMsg.DestChannel, &PortId ) < 0 )
			{
				trace( "Error in Locating Port[%s]", RequestMsg.DestChannel );
				continue;
			}
			trace( "Locate DestPort[%s] with PortId[%d]", RequestMsg.DestChannel );

			if( !IsPortUp( RequestMsg.DestChannel ) )
			{
				trace( "Port[%s] with Pid[%d] Not Running..Cannot Route the Message", RequestMsg.DestChannel, PortId );
				continue;
			}
			memset( &requestMsg, 0, sizeof( struct EzChannelQMsg ) );
			memcpy( &requestMsg.chmsg, &RequestMsg, sizeof( struct EzChannelMsg ) );
			requestMsg.msgtype = PortId;

			if( msgsnd( EzMsgPortQid, &requestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			{
				if( errno == EIDRM )
				{
					trace( "Fatal Error..EzChannelMgrPort Queue is Removed...Creating the EzChannelMgrPort Queue Once Again" );
					if( CreateEzChannelMgrPortQueue() < 0 )
						continue;
					if( msgsnd( EzMsgPortQid, &requestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					{
						trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", requestMsg.chmsg.DestChannel, errno, strerror( errno ) );
						continue;
					}
				}
				else
				{
					trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", requestMsg.chmsg.DestChannel, errno, strerror( errno ) );
					continue;
				}
			}
		}
		else if( ( RequestMsg.ChannelSource == SRC_TASK_CHANNEL ) && ( RequestMsg.ChannelDest == SRC_TASK_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Channel %s]->Destination[Channel %s]", RequestMsg.SrcChannel, RequestMsg.DestChannel );

			/*
			memset( TaskName, 0, sizeof( TaskName ) );
			if( LocateChannel( RequestMsg.DestChannel, TaskName, &ChannelQid, &ChannelKeyId ) < 0 )
			{
				trace( "Error Locating Channel[%s]", RequestMsg.DestChannel );
				continue;
			}
			trace( "Located Channel[%s] with ChannelKeyId[%d] OwnerTaskName[%s]", RequestMsg.DestChannel, ChannelKeyId, TaskName );
			*/

			if( strcmp( TaskName, CHANNEL_INIT_TASK_NAME ) )
			{
				if( !IsTaskRunning( TaskName ) )
				{
					trace( "Channel[%s] OwnerTask[%s] is not running..Cannot Route the Message", RequestMsg.DestChannel, TaskName );
					continue;
				}
			}
			memset( &msgrouter_rec, 0, sizeof( struct EzMsgRouterTable ) );
			if( readMsgRouterTable( RequestMsg.DestChannel, &msgrouter_rec ) < 0 )
			{
				MaxBuffer = getMaxBufferSize( RequestMsg.DestChannel );
				if( MaxBuffer < 0 )
				{
					trace( "Error in Getting MaxBufferSize for Channel[%s]", RequestMsg.DestChannel );
					continue;
				}
				if( createTaskChannel( RequestMsg.DestChannel, MaxBuffer ) < 0 )
				{
					trace( "Error in Creating Task Channel[%s]", RequestMsg.DestChannel );
					continue;
				}
				if( readMsgRouterTable( RequestMsg.DestChannel, &msgrouter_rec ) < 0 )
				{
					trace( "Error in Reading ChannelName[%s] from MsgRouter Table...", RequestMsg.DestChannel );
					continue;
				}
			}
			if( writeTaskChannel( &msgrouter_rec, RequestMsg ) < 0 )
				trace( "Error in Writing Message to TaskChannel[%s]...", RequestMsg.DestChannel );
		}
	}
}

void EzMsgRouter :: StartEzMsgRouter()
{
	if( isUseSharedMemory() )
		startEzMsgRouter();

	struct EzChannelQMsg RequestMsg;
	int PortId, ChannelKeyId, ChannelQid;
	char TaskName[ TASKNAME_SIZE + 1 ];

	while( 1 )
	{
		trace( "EzMsgRouter waiting for request .....");
		memset( &RequestMsg, 0, sizeof( struct EzChannelQMsg ) );
		if( msgrcv( EzMsgRouterQid, &RequestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), 1, 0 ) < 0 )
		{
			if( errno == EINTR )
				continue;
			else if( errno == EIDRM )
			{
				trace( "Fatal Error..MsgRouter Queue is Removed...Creating the EzMsgRouter Queue Once Again");
				EzMsgRouterQid = msgget( ( key_t ) GetEzMsgRouterKey(), IPC_CREAT | 0666 );
				if( EzMsgRouterQid < 0 )
				{
					trace( "Fatal Error...Error while creating EzMsgRouter Queue ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
					trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
					closeDebug();
					exit( 0 );
				}
				continue;
			}
			else
			{
				trace( "Fatal Error...Error in Receiving Message From EzMsgRouter Queue..ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
				trace( "^^^^^^^^^^^EzMsgRouter Ended Abnormally^^^^^^^^^^^^^");
				closeDebug();
				exit( 0 );
			}
		}

		trace( "Channel Source[%c]", RequestMsg.chmsg.ChannelSource );
		trace( "Channel Dest[%c]", RequestMsg.chmsg.ChannelDest );
		trace( "Src Channel[%s]", RequestMsg.chmsg.SrcChannel );
		trace( "Dest Channel[%s]", RequestMsg.chmsg.DestChannel );
		trace( "Message[%s]", RequestMsg.chmsg.Message );
		trace( "MsgSize[%d]", RequestMsg.chmsg.MsgSize );

		if( ( RequestMsg.chmsg.ChannelSource == SRC_PORT_CHANNEL ) && ( RequestMsg.chmsg.ChannelDest == SRC_PORT_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Port %s]->Destination[Port %s]", RequestMsg.chmsg.SrcChannel, RequestMsg.chmsg.DestChannel );

			if( LocatePortName( RequestMsg.chmsg.DestChannel, &PortId ) < 0 )
			{
				trace( "Error in Locating Port[%s]", RequestMsg.chmsg.DestChannel );
				continue;
			}
			trace( "Locate DestPort[%s] with PortId[%d]", RequestMsg.chmsg.DestChannel );

			if( !IsPortUp( RequestMsg.chmsg.DestChannel ) )
			{
				trace( "Port[%s] with Pid[%d] Not Running..Cannot Route the Message", RequestMsg.chmsg.DestChannel, PortId );
				continue;
			}

			RequestMsg.msgtype = PortId;
			if( msgsnd( EzMsgPortQid, &RequestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			{
				if( errno == EIDRM )
				{
					trace( "Fatal Error..EzChannelMgrPort Queue is Removed...Creating the EzChannelMgrPort Queue Once Again" );
					if( CreateEzChannelMgrPortQueue() < 0 )
						continue;
					if( msgsnd( EzMsgPortQid, &RequestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					{
						trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", RequestMsg.chmsg.DestChannel, errno, strerror( errno ) );
						continue;
					}
				}
				else
				{
					trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", RequestMsg.chmsg.DestChannel, errno, strerror( errno ) );
					continue;
				}
			}
		}
		else if( ( RequestMsg.chmsg.ChannelSource == SRC_PORT_CHANNEL ) && ( RequestMsg.chmsg.ChannelDest == SRC_TASK_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Port %s]->Destination[Channel %s]", RequestMsg.chmsg.SrcChannel, RequestMsg.chmsg.DestChannel );

			memset( TaskName, 0, sizeof( TaskName ) );
			if( LocateChannel( RequestMsg.chmsg.DestChannel, TaskName, &ChannelQid, &ChannelKeyId ) < 0 )
			{
				trace( "Error Locating Channel[%s]", RequestMsg.chmsg.DestChannel );
				continue;
			}
			trace( "Located Channel[%s] with ChannelQid[%d] ChannelKeyId[%d] OwnerTaskName[%s]", RequestMsg.chmsg.DestChannel, ChannelQid, ChannelKeyId, TaskName );
			if( strcmp( TaskName, CHANNEL_INIT_TASK_NAME ) )
			{
				if( !IsTaskRunning( TaskName ) )
				{
					trace( "Channel[%s] OwnerTask[%s] is not running..Cannot Route the Message", RequestMsg.chmsg.DestChannel, TaskName );
					continue;
				}
			}
			RequestMsg.msgtype = 1;
			if( msgsnd( ChannelQid, &RequestMsg, sizeof( EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			{
				if( errno == EIDRM )
				{
					trace( "Fatal Error..Channel[%s]Queue is Removed...Creating the Queue Once Again", RequestMsg.chmsg.DestChannel );
					ChannelQid = msgget( ( key_t ) ChannelKeyId, IPC_CREAT | 0666 );
					if( ChannelQid < 0 )
					{
						trace( "Error in Creating Queue for Channel[%s]...SysErr[%s] ErrNo[%d]", RequestMsg.chmsg.DestChannel, strerror( errno ), errno );
						continue;
					}
					if( msgsnd( ChannelQid, &RequestMsg, sizeof( EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					{
						trace( "Error in Sending to Destination Channel Queue ...ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
						continue;
					}
				}
				else
				{
					trace( "Error in Sending to Destination Channel Queue ...ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
					continue;
				}
			}
		}
		else if( ( RequestMsg.chmsg.ChannelSource == SRC_TASK_CHANNEL ) && ( RequestMsg.chmsg.ChannelDest == SRC_PORT_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Channel %s]->Destination[Port %s]", RequestMsg.chmsg.SrcChannel, RequestMsg.chmsg.DestChannel );

			if( LocatePortName( RequestMsg.chmsg.DestChannel, &PortId ) < 0 )
			{
				trace( "Error Locating Port[%s]", RequestMsg.chmsg.DestChannel );
				continue;
			}
			trace( "Located Port[%s] with PortId[%d]", RequestMsg.chmsg.DestChannel, PortId );

			if( !IsPortUp( RequestMsg.chmsg.DestChannel ) )
			{
				trace( "Port[%s] with Pid[%d] Not Running..Cannot Route the Message", RequestMsg.chmsg.DestChannel, PortId );
				continue;
			}
			RequestMsg.msgtype = PortId;

			if( msgsnd( EzMsgPortQid, &RequestMsg, sizeof( EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			{
				if( errno == EIDRM )
				{
					trace( "Fatal Error..EzChannelMgrPort Queue is Removed...Creating the EzChannelMgrPort Queue Once Again" );
					if( CreateEzChannelMgrPortQueue() < 0 )
						continue;
					if( msgsnd( EzMsgPortQid, &RequestMsg, sizeof( struct EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					{
						trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", RequestMsg.chmsg.DestChannel, errno, strerror( errno ) );
						continue;
					}
				}
				else
				{
					trace( "Error in Sending to Destination Port [%s] Queue ...ErrNo[%d] SysErr[%s]", RequestMsg.chmsg.DestChannel, errno, strerror( errno ) );
					continue;
				}
			}
		}
		else if( ( RequestMsg.chmsg.ChannelSource == SRC_TASK_CHANNEL ) && ( RequestMsg.chmsg.ChannelDest == SRC_TASK_CHANNEL ) )
		{
			trace( "Message to be Routed From Source[Channel %s]->Destination[Channel %s]", RequestMsg.chmsg.SrcChannel, RequestMsg.chmsg.DestChannel );
			memset( TaskName, 0, sizeof( TaskName ) );
			if( LocateChannel( RequestMsg.chmsg.DestChannel, TaskName, &ChannelQid, &ChannelKeyId ) < 0 )
			{
				trace( "Error Locating Channel[%s]", RequestMsg.chmsg.DestChannel );
				continue;
			}
			trace( "Located Channel[%s] with ChannelQid[%d] ChannelKeyId[%d] OwnerTask[%s]", RequestMsg.chmsg.DestChannel, ChannelQid, ChannelKeyId, TaskName );

			if( strcmp( TaskName, CHANNEL_INIT_TASK_NAME ) )
			{
				if( !IsTaskRunning( TaskName ) )
				{
					trace( "Channel[%s] OwnerTask[%s] is not running..Cannot Route the Message", RequestMsg.chmsg.DestChannel, TaskName );
					continue;
				}
			}
			RequestMsg.msgtype = 1;
			if( msgsnd( ChannelQid, &RequestMsg, sizeof( EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
			{
				if( errno == EIDRM )
				{
					trace( "Fatal Error..Channel[%s]Queue is Removed...Creating the Queue Once Again", RequestMsg.chmsg.DestChannel );
					ChannelQid = msgget( ( key_t ) ChannelKeyId, IPC_CREAT | 0666 );
					if( ChannelQid < 0 )
					{
						trace( "Error in Creating Queue for Channel[%s]...SysErr[%s] ErrNo[%d]", RequestMsg.chmsg.DestChannel, strerror( errno ), errno );
						continue;
					}
					if( msgsnd( ChannelQid, &RequestMsg, sizeof( EzChannelQMsg ) - sizeof( long ), IPC_NOWAIT ) < 0 )
					{
						trace( "Error in Sending to Destination Channel Queue ...ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
						continue;
					}
				}
				else
				{
					trace( "Error in Sending to Destination Channel Queue ...ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
					continue;
				}
			}
		}

	}
}

int main( int argc, char **argv )
{
	EzMsgRouter msgrouter;
	msgrouter.InitEzMsgRouter( argv[ 0 ] );
	msgrouter.StartEzMsgRouter();
	return 1;
}



