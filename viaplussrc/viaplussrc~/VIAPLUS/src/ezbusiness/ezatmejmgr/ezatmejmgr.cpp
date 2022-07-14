#include <ezbusiness/ezatmejmgr.h>

void *EzAtmEJMgr :: ezatmejmgrobj = 0;

EzAtmEJMgr :: EzAtmEJMgr()
{
	ezatmejmgrobj = this;
}

EzAtmEJMgr :: ~EzAtmEJMgr()
{

}

int EzAtmEJMgr :: InitEzAtmEJMgr( const char * TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezatmejmgr.log"  );

    if( openDebug( logpath, TaskName ) < 0 )
    	exit( 0  );
    SetDebug();

    if( InitEzTaskUtil( this ) < 0 )
    {
           trace( DEBUG_ERROR, "Error in Initializing EzTaskUtil" );
           trace( DEBUG_ERROR, "^^^^^^^^^^^EzAtmEJMgr Ended Abnormally^^^^^^^^^^^^^" );
           closeDebug( );
           exit( 0  );
	}

    if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing EzChannelUtil"  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzAtmEJMgr Ended Abnormally^^^^^^^^^^^^^" );
	    closeDebug( );
	    TaskExit( );
	}

	if( CreateChannel( ATMEJCHANNEL, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Creating EzAtmEJMgr Channel"  );
		trace( DEBUG_ERROR, "^^^^^^^^^^^EzAtmEJMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit( );
	}

	if( InitEzAtmEjUtil( this, false ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing the InitEzAtmEjUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmEJMgr Ended Abnormally^^^^^^^^^^^^^" );
		closeDebug( );
		TaskExit();
	}

	TaskInit( );
	initEzSigUtil( this  );
	return 1;
}

void EzAtmEJMgr :: ServiceRequest()
{
	char ReadBuf[ BUFFER_SIZE + 1 ];
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ], AtmId[ ATM_ID_SIZE + 1 ];
	int BufSize = 0;

	while( 1 )
	{
		trace( DEBUG_NORMAL, "Waiting for Message in EzAtmEJMgr Channel" );
		memset( ReadBuf, 0, sizeof( ReadBuf ) );
		if( ReadMessage( ReadBuf, &BufSize ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading EzAtmEJMgr Channel" );
			continue;
		}

		memset( ChannelName, 0, sizeof( ChannelName ) );
		strcpy( ChannelName, GetLastSenderChannelName() );

		trace( DEBUG_NORMAL, "Message of size [%d] Received from Channel[%s]", BufSize, GetLastSenderChannelName() );

		if( IsPortMessage() )
		{
			if( DiagnizeEjResp( ReadBuf, BufSize, ChannelName ) < 0 )
				trace( DEBUG_ERROR, "Failed in DiagnizeEjResp" );
		}
		else if( !strcmp( ChannelName, "ezejcmd" ) || !strcmp( ChannelName, "EzGUIController" ) || !strcmp( ChannelName, "EzATMController" ) )
		{
			if( strcmp( ChannelName, "EzATMController" ) )
				trace("Channel<%s> Data<%s>", ChannelName, ReadBuf );

			if( BuildAndPostCommand( ReadBuf, BufSize, ChannelName ) < 0 )
			{
				trace( DEBUG_ERROR,"Failed in BuildAndPostCommand");
			}
		}
		else
			trace( DEBUG_ERROR,"Unsupported Channel[%s]", ChannelName );
	}
}

int EzAtmEJMgr :: BuildAndPostCommand( char *Buffer, int Size, char *ChannelName )
{
	char AtmId[ ATM_ID_SIZE + 1 ], DateTime[ 13 ], *p;
	char Command;
	struct ATMEjBuffer ejmem;
	struct EzAtmController AtmCont;
	char EjReqBuffer[ 200 ];

	if( strcmp( ChannelName, "EzATMController" ) )
	{
		memset( DateTime, 0, sizeof( DateTime ) );
		memset( AtmId, 0, sizeof( AtmId ) );

		Command = *Buffer;
		trace("Command[%c]", Command );

		Buffer ++;
		Buffer ++;
		switch( Command )
		{
		case 'I':
			p = ( char * ) memchr( Buffer, HEX_FS, Size );
			memcpy( AtmId, Buffer, ( p - Buffer) );
			trace("AtmId[%s]", AtmId );
			Buffer += strlen( AtmId );
			Buffer ++;

			memset( &ejmem, 0, sizeof( struct ATMEjBuffer ) );
			if( ReadAtmEjMemory( AtmId, &ejmem) < 0 )
			{
				trace( "Unable to Read AtmEjMemoryTable AtmId< %s >",  AtmId );
				return 1;
			}
			printMemory( &ejmem );
			strcpy( DateTime, Buffer );
			trace("DateTime[%s]", DateTime );

			memset( ejmem.DateTime, 0, sizeof( ejmem.DateTime ) );
			strcpy( ejmem.DateTime, DateTime );

			ejmem.CurrentCommand = Command;
			ejmem.CurrentType = OUTOFSERVICE;
			ejmem.AtmStatus = INACTIVE;

			if( WriteAtmEjMemory( AtmId, &ejmem) < 0 )
			{
				trace( "Unable to Read AtmEjMemoryTable AtmId< %s >",  AtmId );
				return 1;
			}

			memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
			AtmCont.CommandType = GO_OUT_SERVICE ;
			AtmCont.MsgType = EZ_ATM_COMMAND_REQ ;
			strcpy( AtmCont.AtmId, AtmId );
			trace("<%d><%d><%s>", AtmCont.MsgType, AtmCont.CommandType, AtmCont.AtmId);
			postControllerMsg( &AtmCont );
			break;

		case 'M':
			break;
		}
	}
	else
	{
		memset( &AtmCont, 0, sizeof( struct EzAtmController ) );
		memcpy( &AtmCont, Buffer, Size );

		trace("<%d><%d><%s>", AtmCont.MsgType, AtmCont.CommandType, AtmCont.AtmId);

		memset( &ejmem, 0, sizeof( struct ATMEjBuffer ) );
		if( ReadAtmEjMemory( AtmCont.AtmId, &ejmem) < 0 )
		{
			trace( "Unable to Read AtmEjMemoryTable AtmId< %s >",  AtmCont.AtmId );
			return -1;
		}

		ejmem.AtmStatus = ACTIVE;
		ejmem.CurrentCommand = INTIATE;

		if( WriteAtmEjMemory( AtmCont.AtmId, &ejmem) < 0 )
		{
			trace( "Unable to Write AtmEjMemoryTable AtmId< %s >",  AtmCont.AtmId );
			return 1;
		}

		memset( EjReqBuffer, 0, sizeof( EjReqBuffer ) );
		sprintf( EjReqBuffer, "%c%c%s%c%s", ejmem.CurrentCommand, HEX_FS, ejmem.AtmId, HEX_FS, ejmem.DateTime );

		trace( "EjReqBuffer[ %s ]", EjReqBuffer );
		postAtmMsg( ejmem.AtmEjPortName , EjReqBuffer );
	}

	return 1;
}

int EzAtmEJMgr :: DiagnizeEjResp( char *Buffer, int Size, char *PortName )
{
	char AtmId[ ATM_ID_SIZE + 1 ], DateTime[ 13 ], *p, Temp[ 50 ];
	char Command;
	struct ATMEjBuffer ejmem;
	char EjBuffer[ 500 ], EjReqBuffer[ 500 ];

	Command = *Buffer;
	trace("Command[%c]", Command );

	Buffer ++;
	Buffer ++;

	p = ( char * ) memchr( Buffer, HEX_FS, Size );
	memcpy( AtmId, Buffer, ( p - Buffer) );
	trace("AtmId[%s]", AtmId );
	Buffer += strlen( AtmId );
	Buffer ++;

	memset( &ejmem, 0, sizeof( struct ATMEjBuffer ) );
	if( ReadAtmEjMemory( AtmId, &ejmem) < 0 )
	{
		trace( "Unable to Read AtmEjMemoryTable AtmId< %s >",  AtmId );
		return 1;
	}

	switch( Command )
	{
	case ACKNOWLEDGE:
		if( ejmem.CurrentCommand == INTIATE )
		{
			strcpy( Temp, Buffer );
			ejmem.TotalBytes = atoi( Temp );
			trace("TotalBytes[%s]", ejmem.TotalBytes );
			ejmem.CurrentCommand = START_DATA;

			if( WriteAtmEjMemory( AtmId, &ejmem) < 0 )
			{
				trace( "Unable to Read AtmEjMemoryTable AtmId< %s >",  AtmId );
				return 1;
			}

			memset( EjReqBuffer, 0, sizeof( EjReqBuffer ) );
			sprintf( EjReqBuffer, "%c%c%s%c%s", ejmem.CurrentCommand, HEX_FS, ejmem.AtmId, HEX_FS, ejmem.DateTime );

			trace( "EjReqBuffer[ %s ]", EjReqBuffer );
			postAtmMsg( ejmem.AtmEjPortName , EjReqBuffer );
		}
		break;

	case DATA:
		memset( EjBuffer, 0, sizeof( EjBuffer ) );
		p = ( char * ) memchr( Buffer, HEX_FS, Size );
		memcpy( EjBuffer, Buffer, ( p - Buffer) );
		trace("EjBuffer[%s]", EjBuffer );
		Buffer += strlen( EjBuffer );

		Buffer ++;
		Command = *Buffer;
		trace("Command[%c]", Command );

		ejmem.LastRevBytes = strlen( EjBuffer );
		trace("LastRevBytes[%d]", ejmem.LastRevBytes );

		ejmem.TotalRevBytes = ejmem.TotalRevBytes + ejmem.LastRevBytes;
		trace("TotalRevBytes[%d]", ejmem.TotalRevBytes );

		ejmem.CurrentCommand = ACKNOWLEDGE;

		memset( EjReqBuffer, 0, sizeof( EjReqBuffer ) );
		if( Command == 'C' )
			sprintf( EjReqBuffer, "%c%c%s%c%s", ejmem.CurrentCommand, HEX_FS, ejmem.AtmId, HEX_FS, ejmem.LastRevBytes );
		else if( Command == 'E' )
		{
			sprintf( EjReqBuffer, "%c%c%s%c%s", ejmem.CurrentCommand, HEX_FS, ejmem.AtmId, HEX_FS, ejmem.TotalRevBytes );
		}

		trace( "EjReqBuffer[ %s ]", EjReqBuffer );
		postAtmMsg( ejmem.AtmEjPortName , EjReqBuffer );
		break;
	default:
		break;
	}

	return 1;
}

void EzAtmEJMgr :: printMemory( struct ATMEjBuffer *mem_ptr )
{
	trace( "InstId[ %s ]", mem_ptr->InstId);
	trace( "AtmId[ %s ]", mem_ptr->AtmId);
	trace( "AtmTypeId[ %s ]", mem_ptr->AtmTypeId);
	trace( "AtmLogicalGroup[ %s ]", mem_ptr->AtmLogicalGroup);
	trace( "AtmEjPortName[ %s ]", mem_ptr->AtmEjPortName);
	trace( "AtmStatus[ %c ]", mem_ptr->AtmStatus);
	trace( "CurrentFile[ %s ]", mem_ptr->CurrentFile);
	trace( "CurrentType[ %c ]", mem_ptr->CurrentType);
	trace( "CurrentCommand[ %c ]", mem_ptr->CurrentCommand);
	trace( "TotalBytes[ %d ]", mem_ptr->TotalBytes);
	trace( "TotalBytes[ %d ]", mem_ptr->TotalRevBytes);
	trace( "TotalBytes[ %d ]", mem_ptr->LastRevBytes);
}

int EzAtmEJMgr :: postControllerMsg( struct EzAtmController *atmctrlmsg )
{
	if( WriteChannel( CONTROLLERCHANNEL, (char*)atmctrlmsg, sizeof( struct EzAtmController ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Unable to write into the channel %s", CONTROLLERCHANNEL );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Message Posted into the %s channel", CONTROLLERCHANNEL );
	return 1;
}

int EzAtmEJMgr :: postAtmMsg( const char *DestPort, char *AtmMsg )
{
	if ( WritePortChannel( DestPort, AtmMsg, strlen( AtmMsg ) ) < 0 )
	{
		trace( DEBUG_ERROR, "Failed to post the Message into Port Channel[ %s ]", DestPort );
		return -1;
	}
	else
		trace( DEBUG_TEST, "Posted the Message to Port Channel[ %s ]", DestPort );

	return 1;
}

int main( int argc, char **argv )
{
	EzAtmEJMgr ezatmejmgrobj;
	ezatmejmgrobj.InitEzAtmEJMgr( argv[ 0 ] );
	ezatmejmgrobj.ServiceRequest( );
	return 1;
}
