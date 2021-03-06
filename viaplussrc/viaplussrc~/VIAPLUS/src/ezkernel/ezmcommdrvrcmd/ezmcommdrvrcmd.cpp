#include<ezkernel/ezmcommdrvrcmd.h>

EzMCommDrvrCmd :: EzMCommDrvrCmd( )
{

}
EzMCommDrvrCmd :: ~EzMCommDrvrCmd( )
{
	
}

int EzMCommDrvrCmd :: InitEzMCommDrvrCmd( const char *TaskName_ptr )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ], MemoryName[ 30 ];
	char logpath[ LOG_PATH_SIZE + 1 ];
	EzCfgUtil cfgutil;
	
	memset( logpath, 0, sizeof( logpath ) ); 
	memset( MemoryName, 0, sizeof( MemoryName ) );
	
	strcpy( TaskName, TaskName_ptr );
	sprintf( MemoryName, "%sMEMORY", TaskName );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmcommdrvrcmd.log" );

	if( openDebug( logpath, TaskName ) < 0 )
	{
		printf( "\nError in Opening File[%s]\n", logpath );
		exit( 0 );
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		return -1;
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "PORT#MAXMCOMMCONNECTION", CfgVal, 2 ) < 0 )
	{
		trace( "Error in Searching PORT#MAXMCOMMCONNECTION in File[%s]", cfgpath );
		cfgutil.cfg_close();
		return -1;
	}
	MaxMCommConnection = atoi( CfgVal );

	MCommMemoryId = LocateMemoryId( this, MemoryName );
	if( MCommMemoryId < 0 )
	{
		trace( DEBUG_ERROR, "Error in Creating Memory[%s]", MemoryName );
		return -1;
	}
	trace( DEBUG_NORMAL, "Memory[%s] Created with MemoryId[%d]", MemoryName, MCommMemoryId );

	MCommConnInfoShmid = shmget( ( key_t ) MCommMemoryId, 0, IPC_CREAT | 0666 );

	if( MCommConnInfoShmid < 0 )
	{
		trace( "Error in Creating EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MCommConnInfoShmPtr = ( struct EzMCommConnInfo * ) shmat( MCommConnInfoShmid, 0, 0 );

	if( MCommConnInfoShmPtr == NULL )
	{
		trace( "Error in attaching EzMCommConnInfo Shared Memory SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}

	MCommConnInfoSemid = semget ( ( key_t ) MCommMemoryId, MaxMCommConnection, IPC_CREAT | 0666 );

	if( MCommConnInfoSemid < 0 )
	{
		trace( "Error in Creating EzMCommConnInfo Semaphore..SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
		return -1;
	}
	
	trace( DEBUG_TEST, "EzMCommConnInfo Semaphore Attached with SemId[%d]", MCommConnInfoSemid );
	
	return 1;

}

int EzMCommDrvrCmd :: ShowConnectionIdMemory( int ClientConnectionId )
{
    int retval = -1;
    struct sembuf sem_buf;
   
    printf( "\n++++++++++++++++++++++++++++++++++++++" );
    printf( "\n%s	%30s", TaskName, "ConnectionDetails" );
    printf( "\n++++++++++++++++++++++++++++++++++++++\n" );
	//printf("ClientConnectionId[%d]\n", ClientConnectionId );
    for( int i = 0; i < MaxMCommConnection; i++ )
    {
	    sem_buf.sem_num = i; 
	    sem_buf.sem_flg = 0; 
	    sem_buf.sem_op = -2;
	    //printf("( MCommConnInfoShmPtr + i )->ConnectionId[%d] i[%d]\n", ( MCommConnInfoShmPtr + i )->ConnectionId, i );
	    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	    {
	            trace( "Error while doing semop for PosConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	            return -1;
	    }
	    if( ( MCommConnInfoShmPtr + i )->ConnectionId == ClientConnectionId )
	    {
	    	printf( "ClientConnectionId	->[%d]\n", ( MCommConnInfoShmPtr + i )->ConnectionId );
	    	printf( "ConnectionIpAddress	->[%s]\n", ( MCommConnInfoShmPtr + i )->IpAddress ) ;
	    	printf( "ConnIdStr	->[%s]\n", ( MCommConnInfoShmPtr + i )->ConnIdStr ) ;
	    	
	    	sem_buf.sem_op = 2; 
	        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	        {
	           trace( "Error while doing semop for PosConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	           return -1;
	        }

	    	retval = 1;
	    	break;
	    }
	    sem_buf.sem_op = 2; 
        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
        {
           trace( "Error while doing semop for PosConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
           return -1;
        }

    }
    return retval;

}
int EzMCommDrvrCmd :: ShowConnectionIdMemory(  )
{
    int retval = -1;
    struct sembuf sem_buf;
   
    printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++" );
    printf( "\n%s	%30s", TaskName, "ConnectionDetails" );
    printf( "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
	
    for( int i = 0; i < MaxMCommConnection; i++ )
    {
	    sem_buf.sem_num = i; 
	    sem_buf.sem_flg = 0; 
	    sem_buf.sem_op = -2;
	    //printf("( MCommConnInfoShmPtr + i )->ConnectionId[%d] i[%d]\n", ( MCommConnInfoShmPtr + i )->ConnectionId, i );
	    if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
	    {
	            trace( "Error while doing semop for PosConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
	            return -1;
	    }
	    if( ( MCommConnInfoShmPtr + i )->ConnectionId != MCOMMCONNECTION_INIT_NAME ) 
	    {
	    	printf( "ClientConnectionId	->[%d]\n", ( MCommConnInfoShmPtr + i )->ConnectionId );
	    	printf( "ConnectionIpAddress	->[%s]\n", ( MCommConnInfoShmPtr + i )->IpAddress ) ;
	    	printf( "ConnIdStr	->[%s]\n", ( MCommConnInfoShmPtr + i )->ConnIdStr ) ;
	    
	    }
	    sem_buf.sem_op = 2; 
        if( semop( MCommConnInfoSemid, &sem_buf, 1 ) < 0 )
        {
           trace( "Error while doing semop for PosConnInfo Memory Semaphore SysErr[%s] ErrNo[%d]", strerror( errno ), errno );
           return -1;
        }

    }
    return retval;
}

void EzMCommDrvrCmd :: ServiceRequest( )
{
	char command[ 100 ];
	while( 1 )
	{
		printf( "\nEzMCommDrvrCmd>" );
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
            	ShowConnectionIdMemory( );
            }
			else
			{
				if( ShowConnectionIdMemory( atoi( command ) ) < 0  )
					printf("[%d] ConnectionId Not Present In %sMEMORY", atoi(command), TaskName );
				continue;
			}
		}
		else if( !strcasecmp( command, "quit" ) )
			exit( 0 );
			
	}
	
}
int main( int argc, char **argv  )
{
	EzMCommDrvrCmd mcommdrvrobj;
	if( argc != 2 )
	{
		printf( "Syntax	:	ezmcommdrvrcmd 	<MCommDriverName>");
		exit( 0 );
	}
	if( mcommdrvrobj.InitEzMCommDrvrCmd( argv[ 1 ] ) < 0 )
	{
		mcommdrvrobj.trace( "^^^^^^^^^^^^^^^Init Failed..ezmcommdrvrcmd Exited Abnormally^^^^^^^^^^^^^^^^^^^^" );
		mcommdrvrobj.closeDebug();
		exit( 0 ); 
	}

	mcommdrvrobj.ServiceRequest( );
}
