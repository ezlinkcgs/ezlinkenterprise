/****Utility for connecting SMS Center*****/

#include <ezbusiness/ezsmscutil.h>

EzSMSCUtil :: EzSMSCUtil()
{

}

EzSMSCUtil :: ~EzSMSCUtil()
{
	closeSocket();
}

int EzSMSCUtil :: initEzSMSCUtil( EzDebugUtil *dptr )
{
	this->dptr = dptr;
	return 1;
}

int EzSMSCUtil :: connectSMSC( struct EzSMSCInfo *smscinfo )
{
	struct sockaddr_in saddr;
	EzDateTimeUtil dtu;
	int	retval = -1;

	SocketId = socket( AF_INET, SOCK_STREAM, 0 );
	smscinfo->ConnectionId = SocketId;
	if( smscinfo->ConnectionId < 0 )
	{
		dptr->trace( DEBUG_ERROR, "Error in Creating SMSC Socket for SMSC[%s] SysErr[%s] ErrNo[%d]", smscinfo->SMSCName, strerror( errno ), errno );
		return -1;
	}

	socklen_t addlen = sizeof( saddr );
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( smscinfo->PortNo );
	saddr.sin_addr.s_addr = inet_addr( smscinfo->IpAddress );
	memset( &saddr.sin_zero, 0, 8 );

	if( bind( SocketId, ( sockaddr * ) &saddr, sizeof( saddr ) ) < 0 )
	{
		dptr->trace( " Error in Binding Socket ....Error [%s] ", strerror( errno ) );
		return -1;
	}



	while( 1 )
	{
		dptr->trace( " ConnectionId[%d]", smscinfo->ConnectionId );

		saddr.sin_family = AF_INET;
		saddr.sin_port = htons( smscinfo->PortNo );
		saddr.sin_addr.s_addr = inet_addr( smscinfo->IpAddress );
		memset( &saddr.sin_zero, 0, 8 );

		retval = connect( smscinfo->ConnectionId, ( struct sockaddr * ) &saddr, addlen );
		if(  retval != 0 )
		{
			dptr->trace( DEBUG_ERROR, "Failed to Connect with SMSC[%s] IpAddress[%s] PortNo[%d] SysErr[%s] ErrNo[%d]", smscinfo->SMSCName, smscinfo->IpAddress, smscinfo->PortNo, strerror( errno ), errno );
			sleep( smscinfo->ConnectionInterval );
			continue;
		}
		else
		{
			dptr->trace( DEBUG_ERROR, "Connected with SMSC[%s] IpAddress[%s] PortNo[%d]", smscinfo->SMSCName, smscinfo->IpAddress, smscinfo->PortNo );
			smscinfo->SMSCStatus = 1;
			sprintf( smscinfo->LogDate, "%06d", dtu.getSysDate() );
			sprintf( smscinfo->LogTime, "%06d", dtu.getSysTime() );
			break;
		}
	}
	return 1;
}

int EzSMSCUtil :: writeMsgToSMSC( int ConnectionId, char *Message, int MsgLen )
{
	int retval;
	retval = send( ConnectionId, Message, MsgLen, MSG_DONTWAIT );
	if( retval < 0 )
	{
		dptr->trace( " Error in sending message to socket...Error [%s] ", strerror( errno ) );
		return -1;
	}
	return retval;
}

int EzSMSCUtil :: readMsgFromSMSC( int ConnectionId, char *Message, int MsgLen )
{
	int retval;
	retval = recv( ConnectionId, Message, MsgLen, 0 );
	if( retval <= 0 )
	{
		dptr->trace( " Error in reading message from socket...Error [%s] ", strerror( errno ) );
		return -1;
	}
	return retval;
}

void EzSMSCUtil :: closeSocket( void )
{
	if( SocketId != -1 )
	{
		close( SocketId );
		SocketId = -1;
	}
}
