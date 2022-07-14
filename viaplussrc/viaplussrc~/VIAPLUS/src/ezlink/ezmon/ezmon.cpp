#include <ezlink/ezmon.h>

void EzMon :: initEzMon()
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], CfgVal[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;
	int retval;

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezkernel.cfg" );
	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		printf( "Error in Opening File[%s]\n", cfgpath );
		exit( 0 );
	}

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#ORGKEY", CfgVal, 2 ) < 0 )
	{
		printf( "Error in Searching CHANNEL#ORGKEY in File[%s]\n", cfgpath );
		cfgutil.cfg_close();
		exit( 0 );
	}
	EzChannelMgrKey = atoi( CfgVal ) + 2;
	EzChannelMgrPortKey = atoi( CfgVal ) + 3;

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXCHANNELS", CfgVal, 2 ) < 0 )
	{
		printf( "Error in Searching CHANNEL#MAXCHANNELS in File[%s]\n", cfgpath );
		cfgutil.cfg_close();
		exit( 0 );
	}

	MaxChannels = atoi( CfgVal );

	memset( CfgVal, 0, sizeof( CfgVal ) );
	if( cfgutil.cfg_search( "CHANNEL#MAXPORTCHANNELS", CfgVal, 2 ) < 0 )
	{
		printf( "Error in Searching CHANNEL#MAXPORTCHANNELS in File[%s]\n", cfgpath );
		cfgutil.cfg_close();
		exit( 0 );
	}

	MaxPortChannels = atoi( CfgVal );

	cfgutil.cfg_close();

	EzChannelMgrShmid = shmget( ( key_t ) EzChannelMgrKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrShmid < 0 )
	{
		printf( "Error in Creating EzChannel Shared Memory SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		exit( 0 );
	}

	EzChannelMgrShmPtr = ( struct EzChannelTable * ) shmat( EzChannelMgrShmid, 0, 0 );
	if( EzChannelMgrShmPtr == NULL )
	{
		printf( "Error in Attaching EzChannel Shared Memory SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		exit( 0 );
	}

	EzChannelMgrPortShmid = shmget( ( key_t ) EzChannelMgrPortKey, 0, IPC_CREAT | 0666 );
	if( EzChannelMgrPortShmid < 0 )
	{
		printf( "Error in Creating EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		exit( 0 );
	}

	EzChannelMgrPortShmPtr = ( struct EzChannelPortTable * ) shmat( EzChannelMgrPortShmid, 0, 0 );
	if( EzChannelMgrPortShmPtr == NULL )
	{
		printf( "Error in Attaching EzChannelPort Shared Memory SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		exit( 0 );
	}

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmon.log" );

	if( openDebug( logpath, "ezmon" ) < 0 )
	{
		printf("\n Error in opening file [%s]...ezmon Exiting\n", logpath );
		exit( 0 );
	}

	trace("~~~~~~~~~~~~~~~~~~ezmon Started Running~~~~~~~~~~~~~~~~~~~~~~~~~~");

	if( eventtable.initEventTable( this ) < 0 )
	{
		trace( "Error in Initializing EventTable...." );
		printf( "Error in Initializing EventTable....\n" );
		closeDebug();
		exit( 0 );
	}

	if( txnmoninfo.initTxnMonInfoUtil( this ) < 0 )
	{
		trace( "Error in Initializing TxnMonInfoUtil...." );
		printf( "Error in Initializing TxnMonInfoUtil....\n" );
		closeDebug();
		exit( 0 );
	}
}

char* EzMon :: trimLeadingZeros( char *InpStr )
{
	char tempstr[ 65 ];
	int offset = 0, i = 0;
	memset( tempstr, 0, sizeof( tempstr ) );
	strcpy( tempstr, InpStr );
	for( i = 0; i < strlen( tempstr ); i++ )
	{
		if( tempstr[ i ] != '0' )
		{
			offset = i;
			break;
		}
	}
	if( i == strlen( tempstr ) )
		strcpy( InpStr, "0" );
	else
		strcpy( InpStr, tempstr + offset );
	return InpStr;
}

void EzMon :: startEzMon( int RefreshInterval )
{
	char ChannelName[ CHANNEL_NAME_SIZE + 1 ];
	struct EventInfoTable eventinfo_rec;
	struct EzTxnMonInfoMemory txnmoninfo_rec;
	initscr();
	while( 1 )
	{
		clear();
		mvwprintw( stdscr, 1, 20, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 2, 25, "******Transaction Monitoring Window******" );
		mvwprintw( stdscr, 3, 20, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 4, 1, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 5, 1, "ChannelName" );
		mvwprintw( stdscr, 5, 21, "NMessage" );
		mvwprintw( stdscr, 5, 35, "DropCount" );
		mvwprintw( stdscr, 6, 1, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );

		mvwprintw( stdscr, 4, 65, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 5, 70, "Event Statistics" );
		mvwprintw( stdscr, 6, 65, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 7, 70, "Active" );
		mvwprintw( stdscr, 8, 70, "TimeOut" );
		mvwprintw( stdscr, 9, 70, "AddDrp" );
		mvwprintw( stdscr, 10, 70, "DelDrp" );
		mvwprintw( stdscr, 11, 70, "TimeOutDrp" );

		mvwprintw( stdscr, 13, 65, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 14, 70, "Transaction Statistics" );
		mvwprintw( stdscr, 15, 65, "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" );
		mvwprintw( stdscr, 16, 70, "TotalHits" );
		mvwprintw( stdscr, 17, 70, "TotalTxnReq" );
		mvwprintw( stdscr, 18, 70, "TotalTxnResp" );
		mvwprintw( stdscr, 19, 70, "TotalRevReq" );
		mvwprintw( stdscr, 20, 70, "TotalRevResp" );
		mvwprintw( stdscr, 21, 70, "TotalPreAuth" );
		mvwprintw( stdscr, 22, 70, "TotalAuthReq" );
		mvwprintw( stdscr, 23, 70, "TotalAuthResp" );
		mvwprintw( stdscr, 24, 70, "TotalOARReq" );
		mvwprintw( stdscr, 25, 70, "TotalOARResp" );

		for( int i = 0, j = 0; i < MaxChannels; i++ )
		{
			if( ( strcmp( ( EzChannelMgrShmPtr + i )->ChannelName, CHANNEL_INIT_NAME ) ) && ( ( EzChannelMgrShmPtr + i )->ChannelType == TASK_CHANNEL ) )
			{
					if( ezmsgqutil.LoadMsgQInfo( ( EzChannelMgrShmPtr + i )->ChannelQid ) >= 0 )
					{
						memset( ChannelName, 0, sizeof( ChannelName ) );
						strcpy( ChannelName, ( EzChannelMgrShmPtr + i )->ChannelName + 5 );
						mvwprintw( stdscr, j + 7, 1, "%s", ChannelName );
						mvwprintw( stdscr, j + 7, 21, "%d", ezmsgqutil.GetNMsg() );
						mvwprintw( stdscr, j + 7, 35, "%d", ( EzChannelMgrShmPtr + i )->DropCount );
						j++;
					}
			}
		}
		memset( &eventinfo_rec, 0, sizeof( struct EventInfoTable ) );
		eventtable.readEventInfoTable( &eventinfo_rec );
		mvwprintw( stdscr, 7, 85, "[%d]", eventinfo_rec.ActiveEvents );
		mvwprintw( stdscr, 8, 85, "[%d]", eventinfo_rec.EventTimeOuts );
		mvwprintw( stdscr, 9, 85, "[%d]", eventinfo_rec.EventAddDropCount );
		mvwprintw( stdscr, 10, 85, "[%d]", eventinfo_rec.EventDeleteDropCount );
		mvwprintw( stdscr, 11, 85, "[%d]", eventinfo_rec.EventTimeOutDropCount );

		memset( &txnmoninfo_rec, 0, sizeof( struct EzTxnMonInfoMemory ) );
		txnmoninfo.readMonInfoMemory( &txnmoninfo_rec );
		trace( "TotalHits[%s] TotalTxnReq[%s] TotalTxnResp[%s] PreAuthResp[%s]", txnmoninfo_rec.TotalHits, txnmoninfo_rec.TotalTxnReq, txnmoninfo_rec.TotalTxnResp, txnmoninfo_rec.PreAuthResp );
		mvwprintw( stdscr, 16, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalHits ) );
		mvwprintw( stdscr, 17, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalTxnReq ) );
		mvwprintw( stdscr, 18, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalTxnResp ) );
		mvwprintw( stdscr, 19, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalRevReq ) );
		mvwprintw( stdscr, 20, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalRevResp ) );
		mvwprintw( stdscr, 21, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.PreAuthResp ) );
		mvwprintw( stdscr, 22, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalAuthReq ) );
		mvwprintw( stdscr, 23, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalAuthResp ) );
		mvwprintw( stdscr, 24, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalOARReq ) );
		mvwprintw( stdscr, 25, 85, "[%s]", trimLeadingZeros( txnmoninfo_rec.TotalOARResp ) );
		mvwprintw( stdscr, 40, 1, "");
		wrefresh( stdscr );
		sleep( RefreshInterval );
	}
	getchar();
	endwin();
}

int main( int argc, char **argv )
{
	if( argc != 2 )
	{
		printf("\n Usage <ezmon> <refresh-interval>" );
		return 1;
	}
	EzMon ezmonobj;
	ezmonobj.initEzMon();
	ezmonobj.startEzMon( atoi( argv[ 1 ] ) );
	return 1;
}

