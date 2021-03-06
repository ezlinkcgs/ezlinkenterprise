#include <ezkernel/ezmcommdrvrutil.h>

char MapTable[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

EzMCommDrvrUtil :: EzMCommDrvrUtil( )
{
	FD_ZERO( &AllSet );
	ConnectionRefNo = 1;
}

EzMCommDrvrUtil :: ~EzMCommDrvrUtil( )
{

}

int EzMCommDrvrUtil :: InitEzMCommDrvrUtil( EzDebugUtil *dptr, const char *Taskname_ptr, struct ezmcommdrvrconfig drvrconfig, EzChannelUtil *chutilptr  )
{
	EzCfgUtil cfgutil;
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ], MemoryName[ 30 ];
	this->dptr = dptr;
	this->ezchannelutil = chutilptr;
	strcpy( TaskName, Taskname_ptr );
	memset( &tcpipconfig, 0, sizeof( struct ezmcommdrvrconfig ) );
	memcpy( &tcpipconfig, &drvrconfig, sizeof( struct ezmcommdrvrconfig ) );

	memset( MemoryName, 0, sizeof( MemoryName ) );
	sprintf( MemoryName, "%sMEMORY", TaskName );
	MCommMemoryId = CreateMemoryId( dptr, MemoryName );
	if( MCommMemoryId < 0 )
    {
            dptr->trace( DEBUG_ERROR, "Error in Creating Memory[%s]", MemoryName );
            return -1;
    }
    dptr->trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", MemoryName, MCommMemoryId );


	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		dptr->trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "PORT#MAXMCOMMCONNECTION", CfgVal, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching PORT#MAXMCOMMCONNECTION in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	/*if( CheckInteger( cfgval ) < 0 )
    {
        dptr->trace( "Invalid MAXPOSCONNECTION[%s] value defined in file[%s]", cfgval, cfgpath );
        return -1;
    }*/

	MaxMCommConnection = atoi( CfgVal );

	return 1;

}

int EzMCommDrvrUtil :: CreateMCommConnInfoMemory(  )
{
	MCommConnInfoShmid = shmget( ( key_t ) MCommMemoryId, sizeof( struct EzMCommConnInfo ) * MaxMCommConnection, IPC_CREAT | 0666 );

   if( MCommConnInfoShmid < 0 )
   {
       dptr->trace( "Error in Creating EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
       return -1;
   }

   MCommConnInfoShmPtr = ( struct EzMCommConnInfo * ) shmat( MCommConnInfoShmid, 0, 0 );

   if( MCommConnInfoShmPtr == NULL )
   {
       dptr->trace( "Error in attaching EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
       return -1;
   }

   for( int i = 0; i < MaxMCommConnection; i++ )
   {
       memset( ( MCommConnInfoShmPtr + i ), 0, sizeof( struct EzMCommConnInfo ) );
       ( MCommConnInfoShmPtr + i )->ConnectionId = MCOMMCONNECTION_INIT_NAME ;
   }

   MCommConnInfoSemid = semget ( ( key_t ) MCommMemoryId, MaxMCommConnection, IPC_CREAT | 0666 );
   dptr->trace( "SemaphoreId [%d]", MCommConnInfoSemid );
   if( MCommConnInfoSemid < 0 )
   {
	   dptr->trace( "Error in Creating EzMCommConnInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	   return -1;
   }

   dptr->trace( DEBUG_TEST, "EzMCommConnInfo Semaphore Created with SemId[%d]", MCommConnInfoSemid );

   union semun
   {
      int val;
      struct semid_ds *buf;
      unsigned short *array;
   };

   union semun arg;
   arg.val = 2;

   for( int i = 0; i < MaxMCommConnection; i++ )
   {
       if( semctl( MCommConnInfoSemid, i, SETVAL, arg ) < 0 )
       {
               dptr->trace( "Error in Setting EzMCommConnInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
               return -1;
       }
   }
   return 1;

}

int EzMCommDrvrUtil :: AttacheMCommConnInfoMemory( )
{
	MCommConnInfoShmid = shmget( ( key_t ) MCommMemoryId, sizeof( struct EzMCommConnInfo ) * MaxMCommConnection, IPC_CREAT | 0666 );

   if( MCommConnInfoShmid < 0 )
   {
       dptr->trace( "Error in Creating EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
       return -1;
   }

   MCommConnInfoShmPtr = ( struct EzMCommConnInfo * ) shmat( MCommConnInfoShmid, 0, 0 );

   if( MCommConnInfoShmPtr == NULL )
   {
       dptr->trace( "Error in attaching EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
       return -1;
   }

   for( int i = 0; i < MaxMCommConnection; i++ )
   {
       memset( ( MCommConnInfoShmPtr + i ), 0, sizeof( struct EzMCommConnInfo ) );
       ( MCommConnInfoShmPtr + i )->ConnectionId = MCOMMCONNECTION_INIT_NAME ;

   }

   MCommConnInfoSemid = semget ( ( key_t ) MCommMemoryId, MaxMCommConnection, IPC_CREAT | 0666 );

   if( MCommConnInfoSemid < 0 )
   {
	   dptr->trace( "Error in Creating EzMCommConnInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	   return -1;
   }

   dptr->trace( DEBUG_TEST, "EzMCommConnInfo Semaphore Created with SemId[%d]", MCommConnInfoSemid );

   union semun
   {
      int val;
      struct semid_ds *buf;
      unsigned short *array;
   };

   union semun arg;
   arg.val = 2;

   for( int i = 0; i < MaxMCommConnection; i++ )
   {
       if( semctl( MCommConnInfoSemid, i, SETVAL, arg ) < 0 )
       {
               dptr->trace( "Error in Setting EzMCommConnInfo Memory Semaphore value...SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
               return -1;
       }
   }
   return 1;

}

int EzMCommDrvrUtil :: GetConnectionIdMemory( int *ClientConnectionId, char *ConnectionIpAddress, char *ConnIdStr )
{
	dptr->trace( "Test-1");
	int retval = -1;
    struct sembuf sem_buf;
    for( int i = 0; i < MaxMCommConnection; i++ )
    {
	    sem_buf.sem_num = i;
	    sem_buf.sem_flg = 0;
	    sem_buf.sem_op = -2;
	    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	    {
	            dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	            return -1;
	    }
	    if( !strcmp( ( MCommConnInfoShmPtr + i )->ConnIdStr, ConnIdStr ) )
	    {
	    	*ClientConnectionId = ( MCommConnInfoShmPtr + i )->ConnectionId;
	    	strcpy( ConnectionIpAddress, ( MCommConnInfoShmPtr + i )->IpAddress );
	    	sem_buf.sem_op = 2;
	        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	        {
	           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	           return -1;
	        }
	    	retval = 1;
	    	break;
	    }
	    sem_buf.sem_op = 2;
        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
        {
           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
           return -1;
        }

    }
    return retval;

}
int EzMCommDrvrUtil :: GetConnectionIdMemory( int *ClientConnectionId, char *ConnectionIpAddress, int i )
{
	dptr->trace( "Test-2");
	struct sembuf sem_buf;

    sem_buf.sem_num = i;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = -2;
    dptr->trace( "Before LockSemop");
    dptr->trace( "SemaphoreId [%d] i[%d]", MCommConnInfoSemid, i );
    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
    {
            dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
            return -1;
    }
    dptr->trace( "After LockSemop");
   	*ClientConnectionId = ( MCommConnInfoShmPtr + i )->ConnectionId;
   	if( ( MCommConnInfoShmPtr + i )->ConnectionId != MCOMMCONNECTION_INIT_NAME )
   		strcpy( ConnectionIpAddress, ( MCommConnInfoShmPtr + i )->IpAddress );

    sem_buf.sem_op = 2;
    dptr->trace( "Before ReleaseSemop");
    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
    {
       dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
       return -1;
    }
    dptr->trace( "After ReleaseSemop");
    dptr->trace("Return ClientConnectionId[%d]", *ClientConnectionId );
    return 1;

}
int EzMCommDrvrUtil :: AddMCommConnInfoMemory( int ClientConnectionId, const char *ConnectionIpAddress, char *ConnIdStr )
{
	int retval = -1;
    struct sembuf sem_buf;
    for( int i = 0; i < MaxMCommConnection; i++ )
    {
	    sem_buf.sem_num = i;
	    sem_buf.sem_flg = 0;
	    sem_buf.sem_op = -2;
	    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	    {
	            dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	            return -1;
	    }
	    if( ( MCommConnInfoShmPtr + i )->ConnectionId == MCOMMCONNECTION_INIT_NAME )
	    {
	    	memset( ( MCommConnInfoShmPtr + i ), 0, sizeof( struct EzMCommConnInfo ) );
	    	//memset( ( MCommConnInfoShmPtr + i )->ConnIdStr, 0, sizeof( ( MCommConnInfoShmPtr + i )->ConnIdStr ) );
	    	( MCommConnInfoShmPtr + i )->ConnectionId = ClientConnectionId;
	    	strcpy( ( MCommConnInfoShmPtr + i )->IpAddress, ConnectionIpAddress );
	    	strcpy( ( MCommConnInfoShmPtr + i )->ConnIdStr, ConnIdStr );
	    	sem_buf.sem_op = 2;
	        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	        {
	           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	           return -1;
	        }
	    	retval = 1;
	    	break;
	    }
	    sem_buf.sem_op = 2;
        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
        {
           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
           return -1;
        }

    }
    return retval;

}
int EzMCommDrvrUtil :: UpdateMCommConnInfoMemory( int ClientConnectionId, char *ConnIdStr )
{
	int retval = -1;
    struct sembuf sem_buf;
    dptr->trace( "ClientConnectionId[%d]", ClientConnectionId );
    for( int i = 0; i < MaxMCommConnection; i++ )
    {
	    sem_buf.sem_num = i;
	    sem_buf.sem_flg = 0;
	    sem_buf.sem_op = -2;
	    dptr->trace("( MCommConnInfoShmPtr + i )->ConnectionId[%d] i[%d]", ( MCommConnInfoShmPtr + i )->ConnectionId, i  );
	    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	    {
	            dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	            return -1;
	    }
	    if( ( MCommConnInfoShmPtr + i )->ConnectionId == ClientConnectionId )
	    {
	    	strcpy( ( MCommConnInfoShmPtr + i )->ConnIdStr, ConnIdStr );
	    	sem_buf.sem_op = 2;
	        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	        {
	           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	           return -1;
	        }
	    	retval = 1;
	    	break;
	    }
	    sem_buf.sem_op = 2;
        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
        {
           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
           return -1;
        }

    }
    return retval;

}

int EzMCommDrvrUtil :: RemoveMCommConnInfoMemory( int ClientConnectionId )
{
	int retval = -1;
    struct sembuf sem_buf;

    for( int i = 0; i < MaxMCommConnection; i++ )
    {
	    sem_buf.sem_num = i;
	    sem_buf.sem_flg = 0;
	    sem_buf.sem_op = -2;
	    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	    {
	            dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	            return -1;
	    }
	    if( ( MCommConnInfoShmPtr + i )->ConnectionId == ClientConnectionId )
	    {
	    	memset( ( MCommConnInfoShmPtr + i ), 0, sizeof( struct EzMCommConnInfo ) );
	    	( MCommConnInfoShmPtr + i )->ConnectionId = MCOMMCONNECTION_INIT_NAME ;
            sem_buf.sem_op = 2;
            if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
            {
                dptr->trace( "Error while doing semop for EzMCommConnInfo  Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
                return -1;
            }
            retval = 1;
            break;

	    }
	    sem_buf.sem_op = 2;
        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
        {
           dptr->trace( "Error while doing semop for EzMCommConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
           return -1;
        }
    }
    return retval;

}

//TcpIp Related Functions

int EzMCommDrvrUtil :: createSocket()
{
	// AF_INET -> Family
	// SOCK_STREAM -> Stream Socket
	// PROTOCOL -> TCP
	// socket( int family, int type, int protocol );

	sersockfd = socket( AF_INET, SOCK_STREAM, 0 );
	if( sersockfd < 0 )
	{
		dptr->trace( " Error in Creating Socket ...Error [%s] ", strerror( errno ) );
		return -1;
	}
	dptr->trace( " Server Socket Created With [%d] Id ", sersockfd );
	setSocketOptions( );

	dptr->trace( "Test....PortNo[%d]", tcpipconfig.portno );
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons( tcpipconfig.portno );
	saddr.sin_addr.s_addr = INADDR_ANY;
	memset( &saddr.sin_zero, 0, 8 );

	if( bind( sersockfd, ( sockaddr * ) &saddr, sizeof( saddr ) ) < 0 )
	{
		dptr->trace( " Error in Binding Socket ....Error [%s] ", strerror( errno ) );
		return -1;
	}
	dptr->trace( DEBUG_TEST, " Server Socket Binded " );
	//if( listen( sersockfd, tcpipconfig.nconnections ) < 0 )
	if( listen( sersockfd, 10 ) < 0 )
	{
		dptr->trace( " Socket Listen error ....Error [%s] ", strerror( errno ) );
		return -1;
	}

	AddConnectionSet( sersockfd );

	return sersockfd;

}

int EzMCommDrvrUtil :: setSocketOptions( )
{
	int flag = 1;
	struct linger lng;
	lng.l_onoff = 1;
	lng.l_linger = 0;

	if( setsockopt( sersockfd, SOL_SOCKET, SO_LINGER, &lng, sizeof( lng ) ) < 0 )
		return -1;

	flag = 1;
	if( tcpipconfig.apptype == TCPIP_SERVER )
	{
		if( setsockopt( sersockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof( flag ) ) < 0 )
			return -1;
	}

	if( tcpipconfig.keepalive )
	{
		flag = 1;
		if( setsockopt( sersockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof( flag ) ) < 0 )
			return -1;
	}
	else
	{
		flag = 0;
		if( setsockopt( sersockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof( flag ) ) < 0 )
			return -1;
	}
	return 1;
}
void EzMCommDrvrUtil :: AddConnectionSet( int MaxConnectionId )
{
	 FD_SET( MaxConnectionId, &AllSet);
	 fdmax = MaxConnectionId;

}
void EzMCommDrvrUtil :: ProcessClientRequest( )
{
	fd_set ReadSet;
	int ClientConnectionId;
	int SeqNo = 1, size;
	short int MsgSize;
	unsigned char tcpipmsg[ COMM_MSG_SIZE + 1 ];
	char ConnIdStr[ 13 ],DateTime[ 13 ];
	char tcpipheader[ COMM_HEADER_SIZE + 1 ];
	char ConnectionIpAddress[ IPLEN + 1 ];


	while( 1 )
	{
		ReadSet = AllSet;
		dptr->trace( "Waiting For New Connection Or Existing To Process");
		dptr->trace( DEBUG_TEST, "Current fdmax[%d]", fdmax );
		if( select( fdmax+1, &ReadSet, NULL, NULL, NULL ) < 0 )
		{
			dptr->trace( "Error in Select SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
			continue;
		}
		dptr->trace( DEBUG_TEST, "Event Occured On Socket Descriptor..." );
		if(FD_ISSET ( sersockfd ,&ReadSet))
        {
			socklen_t addlen = sizeof( caddr );
			dptr->trace( DEBUG_TEST, "Event Occured On Server Socket Descriptor..." );
			dptr->trace( DEBUG_TEST," Server Socket Id [%d] ", sersockfd );
			ClientConnectionId = accept( sersockfd, ( struct sockaddr * ) &caddr, &addlen );
        	if( ClientConnectionId < 0 )
        	{
        		dptr->trace( " Error in accepting connection ....SysErr [%s] ErrNo[%d]", strerror( errno ) , errno );
        		continue;
        	}
            memset( ConnectionIpAddress, 0, sizeof( ConnectionIpAddress ) );
            strcpy( ConnectionIpAddress, inet_ntoa( caddr.sin_addr ) );

            if( ClientConnectionId > fdmax )
                    fdmax = ClientConnectionId;

            FD_SET( ClientConnectionId, &AllSet );
            //AddConnectionId & IPAddress To Memory

            if( AddMCommConnInfoMemory( ClientConnectionId, ConnectionIpAddress, ConnIdStr ) < 0 )
            {
            	dptr->trace( " Error in adding  ClientConnectionId[%d] Into MCommConnInfoMemory", ClientConnectionId );
            	continue;
            }
            dptr->trace( DEBUG_TEST, "ClientConnectionId Has Been Added To The MCommConnInfoMemory", ClientConnectionId );
            //PrintConnectionId & Address
        }
		else
		{
			dptr->trace( DEBUG_TEST, "Receiving Message From Client.." );
			for( int i = 0; i<MaxMCommConnection; i++ )
			{
				ClientConnectionId = 0;
				dptr->trace( DEBUG_TEST, "Getting ClientConnectionId One By One For checking With SelectSet"  );
				if( GetConnectionIdMemory( &ClientConnectionId, ConnectionIpAddress, i ) < 0 )
				{
					dptr->trace( "Unable To Get ConnectionId" );
					break;
				}
				dptr->trace( DEBUG_TEST, "ClientConnectionId[%d]", ClientConnectionId  );
				if( ClientConnectionId == MCOMMCONNECTION_INIT_NAME )
				{
					dptr->trace( DEBUG_TEST, "No ClientConnectionId Selected..,So Return To While Loop"  );
					break;
				}
				else
				{
					if( FD_ISSET( ClientConnectionId, &ReadSet ) )
                    {
						dptr->trace( DEBUG_TEST, "Event Occured On [%d] Client Socket Descriptor", ClientConnectionId );
                        memset( tcpipheader, 0, sizeof( tcpipheader ) );
                        if( recv( ClientConnectionId, tcpipheader, tcpipconfig.headerlen, 0 ) <= 0 )
            			{
                            dptr->trace( DEBUG_NORMAL,"Connection Closed by ConnectionId[%d]\n", ClientConnectionId );
                            close(  ClientConnectionId );
                            FD_CLR(  ClientConnectionId, &AllSet );
                            if( ClientConnectionId == fdmax )
                            	fdmax = fdmax - 1;
                            if( RemoveMCommConnInfoMemory( ClientConnectionId ) < 0 )
                            	dptr->trace( "Unable To Remove, ConnectionId[%d] Not Found\n", ClientConnectionId );
                            else
                            	dptr->trace( DEBUG_TEST, "ClientConnectionId[%d] Removed From Memory", ClientConnectionId  );
                            break;
            			}
            			dptr->hex_dump( DEBUG_TEST, ( unsigned char * ) tcpipheader, tcpipconfig.headerlen );
            			if( tcpipconfig.headertype == ASCII )
            				MsgSize = atoi( tcpipheader );
            			else if( tcpipconfig.headertype == HEX )
            			{
            				memcpy( &MsgSize, tcpipheader, tcpipconfig.headerlen );
            				MsgSize = ntohs( MsgSize );
            			}
            			dptr->trace( "[%d] bytes available on socket", MsgSize );

            			memset( tcpipmsg, 0, sizeof( tcpipmsg ) );
						if( recv(  ClientConnectionId, tcpipmsg, MsgSize, 0 ) <= 0 )
						{
							dptr->trace( DEBUG_ERROR, "Error while Reading Message From Socket ErrNo[%d] SysErr[%s]", errno, strerror( errno ) );
							break;
						}
						dptr->hex_dump( ( unsigned char * ) tcpipmsg, MsgSize );

						memset( ConnIdStr, 0, sizeof( ConnIdStr ) );
			            getConnectionRefNum( ConnIdStr );
			            dptr->trace( DEBUG_TEST, "ClientConnectionId[%d]", ClientConnectionId  );
			            dptr->trace( DEBUG_TEST, "ConnIdStr[%s]", ConnIdStr  );
			            dptr->trace( DEBUG_TEST, "ClientConnectionId[%d]", ClientConnectionId  );
			            if( UpdateMCommConnInfoMemory( ClientConnectionId, ConnIdStr ) < 0 )
			            {
			            	dptr->trace( "Unable To Update, ConnectionId[%d] Not Found\n", ClientConnectionId );
			            	break;
			            }
			            dptr->trace( DEBUG_TEST, "ConnIdStr[%s] Has Been Updated For[%d] ConnectionId", ConnIdStr,ClientConnectionId  );
						if( PackDriverMessage( tcpipmsg, ConnIdStr, MsgSize ) < 0 )
							break;
						break; //To Go For Select

                    }
				}
			}
		}//else close
	}//main while close

}

//Sending Message Function

int EzMCommDrvrUtil :: PackDriverMessage( const unsigned char *tcpipmsg, const char *ConnIdStr, int size )
{
	unsigned char WriteBuffer[ 4096 ];
	memset( WriteBuffer, 0, sizeof( WriteBuffer ) );

	memcpy( WriteBuffer, ConnIdStr, 12 );
	memcpy( WriteBuffer + 12, tcpipmsg, size );

	dptr->trace( DEBUG_TEST, "Write Buffer[%s] destchannel[%s]", WriteBuffer, tcpipconfig.destchannel );
	dptr->hex_dump( WriteBuffer, size + 12 );

	if( ezchannelutil->WriteChannel( tcpipconfig.destchannel, ( char * ) WriteBuffer , size + 12 ) < 0 )
    {
        dptr->trace( DEBUG_ERROR, "Unable to write into the channel %s", tcpipconfig.destchannel );
        return -1;
    }
    else
        dptr->trace( DEBUG_TEST, "Message[%s] written into the %s channel", WriteBuffer, tcpipconfig.destchannel );
	return 1;
}

void EzMCommDrvrUtil :: GetMappedDateTimeVal( char *MapVal )
{
	char OrgVal[ 20 ], TempStr[ 10 ];

	memset( OrgVal, 0, sizeof( OrgVal ) );
	sprintf( OrgVal, "%06d%06d", ezdatetimeutil.getSysDate(), ezdatetimeutil.getSysTime() );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal, 2 );
	MapVal [ 0 ] = MapTable [ atoi( TempStr ) ];

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal + 2, 2 );
	MapVal [ 1 ] = MapTable [ atoi( TempStr ) ];

	strncpy( MapVal + 2, OrgVal + 4, 2 );

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal + 6, 2 );
	MapVal [ 4 ] = MapTable [ atoi( TempStr ) ];

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal + 8, 2 );
	MapVal [ 5 ] = MapTable [ atoi( TempStr ) ];

	memset( TempStr, 0, sizeof( TempStr ) );
	strncpy( TempStr, OrgVal + 10, 2 );
	MapVal [ 6 ] = MapTable [ atoi( TempStr ) ];
}

void EzMCommDrvrUtil :: getConnectionRefNum( char *ConnIdStr )
{
	char MappedVal[ 20 ];

	if( ConnectionRefNo == 99999 )
		ConnectionRefNo = 1;
	else
		ConnectionRefNo++;

	memset( MappedVal, 0, sizeof( MappedVal ) );
	GetMappedDateTimeVal( MappedVal );
	sprintf( ConnIdStr, "%s%05d", MappedVal, ConnectionRefNo );
}

bool EzMCommDrvrUtil :: IsInteger( const char *InputVal )
{
	for( int i = 0; i < strlen( InputVal ); i++ )
	{
		if( ( InputVal[ i ] < 48 ) && ( InputVal[ i ] > 57 ) )
			return false;
	}
	return true;
}

bool EzMCommDrvrUtil :: IsValidIp( char *ipaddress )
{
	int charcount = 0, fld_sep = 0, i = 0;
	for( i = 0; i <= strlen( ipaddress ) - 1; i++ )
	{
		if( !isdigit( ipaddress[ i ] ) )
		{
			if( !charcount )
				return false;
			if( fld_sep > 3 )
				return false;
			if( charcount > 3 )
				return false;
			if( ipaddress[ i ] == '.' )
			{
				charcount = 0;
				fld_sep++;
			}
			else
				return false;
		}
		else
		{
			if( charcount > 3 )
				return false;
			charcount++;
		}
	}
	if( !charcount )
		return false;
	if( fld_sep != 3 )
		return false;
	return true;
}
