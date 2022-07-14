#include <ezbusiness/ezsecuritymgr.h>

void EzSecurityMgr :: InitEzSecurityMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezsecuritymgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsecurity.cfg" );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in opening file[%s]", cfgpath );
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "HSM_INSTALLED", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching HSM_INSTALLED from file[%s]", cfgpath );
		HSMRequiredFlag = false;
	}
	else
	{
		if( !strcasecmp( cfgval, "Yes" ) )
			HSMRequiredFlag = true;
		else
			HSMRequiredFlag = false;
	}

	cfgutil.cfg_close();

	if ( initEzSecurityMgrUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing EzSecurityMgrUtil" );
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	/*if( initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil..." );
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB..." );
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}*/

	if( IsTaskRunning( TaskName ) < 0 )
	{
		trace( DEBUG_NORMAL, "First Instance of EzSecurityMgr...Initializing SecurityMgrSharedMemory" );

		if( LoadSecurityMemory () < 0 )
		{
			trace( "Error in Loading EzSecurity  Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( LoadATMKeyMemory() < 0 )
		{
			trace( "Error in Loading ATMKey Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( LoadNetworkKeyMemory()	< 0 )
		{
			trace( "Error in Loading Network Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( LoadDeviceKeyMemory () < 0 )
		{
			trace( "Error in Loading DeviceKey  Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( LoadSecurityPropertyMemory () < 0 )
		{
			trace( "Error in Loading SecurityProperty  Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( HSMRequiredFlag )
		{
			if( LoadHSMInfoMemory() < 0 )
			{
				trace( "Error in Loading EzHSMInfo Memory...");
				trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
				closeDebug();
				TaskExit();
			}
		}
	}
	else
	{
		if( getATMKeyMemory() < 0 )
		{
			trace( "Error in getting ATM Key Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( getNetworkKeyMemory() < 0 )
		{
			trace( "Error in getting Network Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getDeviceKeyMemory() < 0)
		{
			trace( "Error in getting DeviceKey Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( getSecurityMemory() < 0 )
		{
			trace( "Error in getting EzSecurity Memory...");
			trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		if( HSMRequiredFlag )
		{
			if( getHSMInfoMemory() < 0 )
			{
				trace( "Error in getting EzHSMInfo Memory...");
				trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
				closeDebug();
				TaskExit();
			}
		}
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( SECURITYMGRCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating EzSecurityMgr Channel" );
		trace( "^^^^^^^^^^^EzSecurityMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}
	TaskInit();
	initEzSigUtil( this );

	trace( "Initialized EzSecurityMgr....");
}

void EzSecurityMgr :: ServiceRequest()
{
	int MsgSize;
	struct EzSecurityMgrQMsg secmgrqmsg;
	struct DeviceKeyMsg devkeymsg;
	struct NetworkKeyMsg networkkeymsg;
	struct EzHSMInfoMsg hsminfomsg;

	while( 1 )
	{
		trace( "EzSecurityMgr Waiting For Request....");
		memset( &secmgrqmsg, 0, sizeof( struct EzSecurityMgrQMsg ) );

		//dbUtilClose();
		if( ReadMessage( ( char * )&secmgrqmsg, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message From EzSecurityMgr Channel..." );
			sleep( 1 );
			continue;
		}
		else
			trace( " Msg Received <%d> <%d> <%d> " ,secmgrqmsg.SourceType, secmgrqmsg.CommandCode, secmgrqmsg.OperationCode );

		/*if( dbUtilConnect() < 0 )
			continue;*/

		switch( secmgrqmsg.SourceType )
		{
			case EZSEC_TABLE:
			{
				switch( secmgrqmsg.CommandCode )
				{
					case EZSEC_ACQCOMMKEY:
					{
						memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
						memcpy( &networkkeymsg, secmgrqmsg.SourceBuffer, sizeof( struct NetworkKeyMsg ) );

						switch( secmgrqmsg.OperationCode )
						{
							case EZSEC_UPDATE:
								retval = updateEzNetworkAcqKeyTable( networkkeymsg.NetworkId, networkkeymsg.NetworkCommKey, &SqlErr );
								if( SqlErr == -1  )
								{
									if( DBConnect() < 0 )
									{
										trace( "Error In Updating AcqKey Into NetworkKey Table For [ %s ] networkId...Error in Connecting to Switch DB ", networkkeymsg.NetworkCommKey, networkkeymsg.NetworkId );
										break;
									}
									retval = updateEzNetworkAcqKeyTable( networkkeymsg.NetworkId, networkkeymsg.NetworkCommKey, &SqlErr );
								}
								if( retval < 0 )
									trace( "Error In Updating AcqKey Into NetworkKey Table For [ %s ] networkId..SqlErr[%05d] ", networkkeymsg.NetworkCommKey, networkkeymsg.NetworkId, SqlErr );
							else
								trace( " Updated NetworkAcqCommKey For [ %s ] Network", networkkeymsg.NetworkId );
							break;

							default:
								trace ( "Invalid OperationCode [ %d ] ", secmgrqmsg.OperationCode );
							break;
						}
					}
					break;

					case EZSEC_ISSCOMMKEY:
					{
						memset( &networkkeymsg, 0, sizeof( struct NetworkKeyMsg ) );
						memcpy( &networkkeymsg, secmgrqmsg.SourceBuffer, sizeof( struct NetworkKeyMsg ) );

						switch( secmgrqmsg.OperationCode )
						{
							case EZSEC_UPDATE:
								retval = updateEzNetworkIssKeyTable(networkkeymsg.NetworkId, networkkeymsg.NetworkCommKey ,&SqlErr);
								if( SqlErr == -1 )
								{
									if( DBConnect() < 0 )
									{
										trace( "Error In Updating IssKey Into NetworkKey Table For [ %s ] networkId ..Error in Connecting with DB...", networkkeymsg.NetworkCommKey, networkkeymsg.NetworkId );
										break;
									}
									retval = updateEzNetworkIssKeyTable(networkkeymsg.NetworkId, networkkeymsg.NetworkCommKey ,&SqlErr);
								}
								if( retval <  0 )
									trace( "Error In Updating IssKey Into NetworkKey Table For [ %s ] networkId ..SqlErr[%05d]", networkkeymsg.NetworkCommKey, networkkeymsg.NetworkId, SqlErr );
							else
								trace( " Updated NetworkIssCommKey For [ %s ] Network", networkkeymsg.NetworkId );
							break;

							default:
								trace ( "Invalid OperationCode [ %d ] ", secmgrqmsg.OperationCode );
							break;
						}
					}
					break;

					case EZSEC_HSMINFO:
					{
						memset( &hsminfomsg, 0, sizeof( struct EzHSMInfoMsg ) );
						memcpy( &hsminfomsg, secmgrqmsg.SourceBuffer, sizeof( struct EzHSMInfoMsg ) );

						switch( secmgrqmsg.OperationCode )
						{
							case EZSEC_UPDATE:
								retval = updateHSMInfoTable( hsminfomsg.HSMName, hsminfomsg.HSMStatus, &SqlErr  );
								if( SqlErr == -1 )
								{
									if( DBConnect() < 0 )
									{
										trace( "Error In Updating [ %s ]HSMName Into EzHSMInfo Table...Error in Connecting with DB...." ,devkeymsg.DeviceId );
										break;
									}
									retval = updateHSMInfoTable( hsminfomsg.HSMName, hsminfomsg.HSMStatus, &SqlErr  );
								}
								if( retval < 0 )
									trace( "Error In Updating [ %s ]HSMName Into EzATMInfo Table" ,hsminfomsg.HSMName );
								else
									trace( " Updated Status For HSMName[%s] HSMStatus[%d]", hsminfomsg.HSMName, hsminfomsg.HSMStatus );
							break;

							default:
							trace (" Invalid OperationCode [ %d ] ",secmgrqmsg.OperationCode );
							break;
						}
					}
					break;

					case EZSEC_ATMKEY:
					{
						memset( &devkeymsg, 0, sizeof( struct DeviceKeyMsg ) );
						memcpy( &devkeymsg, secmgrqmsg.SourceBuffer, sizeof( struct DeviceKeyMsg ) );

						switch( secmgrqmsg.OperationCode )
						{
							case EZSEC_UPDATE:
							retval = updateATMKeyTable( devkeymsg.DeviceId, devkeymsg.DeviceCommKey, &SqlErr  );
							if( SqlErr == -1 )
							{
								if( DBConnect() < 0 )
								{
									trace( "Error In Updating [ %s ]ATMId Into EzATMInfo Table...Error in Connecting with DB...." ,devkeymsg.DeviceId );
									break;
								}
								retval = updateATMKeyTable( devkeymsg.DeviceId, devkeymsg.DeviceCommKey, &SqlErr  );
							}
							if( retval < 0 )
								trace( "Error In Updating [ %s ]ATMId Into EzATMInfo Table..SqlErr[%05d]" ,devkeymsg.DeviceId, SqlErr );
							else
								trace( " Updated LocalComKey For [ %s ] ATMId", devkeymsg.DeviceId );
						break;

						default:
							trace (" Invalid OperationCode [ %d ] ",secmgrqmsg.OperationCode );
						break;
						}
					}
					break;

					case EZSEC_DEVICEKEY:
					{
						memset( &devkeymsg, 0, sizeof( struct DeviceKeyMsg ) );
						memcpy( &devkeymsg, secmgrqmsg.SourceBuffer, sizeof( struct DeviceKeyMsg ) );

						switch( secmgrqmsg.OperationCode )
						{
						case EZSEC_UPDATE:
							retval = updateDeviceKeyTable( devkeymsg.DeviceId, devkeymsg.DeviceCommKey, &SqlErr  );
							if(  SqlErr == -1 )
							{
								if( DBConnect() < 0 )
								{
									trace( "Error In Updating [ %s ]DeviceId Into DeviceKey Table...Error in Connecting with Switch DB...." ,devkeymsg.DeviceId );
									break;
								}
								retval = updateDeviceKeyTable( devkeymsg.DeviceId, devkeymsg.DeviceCommKey, &SqlErr  );
							}
							if( retval < 0 )
								trace( "Error In Updating [ %s ]DeviceId Into DeviceKey Table...SqlErr[%05d]" ,devkeymsg.DeviceId, SqlErr );
							else
								trace( " Updated LocalComKey For [ %s ] DeviceId", devkeymsg.DeviceId );
						break;

						default:
							trace (" Invalid OperationCode [ %d ] ",secmgrqmsg.OperationCode );
						break;
						}
					}
					break;

					default:
						trace( "Invalid CommandCode [%d]", secmgrqmsg.CommandCode );
					break;
				}
			}
			break;

			default:
				trace( "Invalid Source Type[%d]", secmgrqmsg.SourceType );
			break;
		}
	}
}

int main( int argc, char **argv )
{
	EzSecurityMgr ezsecuritymgrobj;
	ezsecuritymgrobj.InitEzSecurityMgr( argv[ 0 ] );
	ezsecuritymgrobj.ServiceRequest();
	return 1;
}


