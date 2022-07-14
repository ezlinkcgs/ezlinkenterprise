#include <ezlink/ezalertmgr.h>

int EzAlertMgr :: initAlertMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezalertmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^EzAlertMgr Started^^^^^^^^^^^^^");

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	SetDebug();

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( EZALERTMGRCHANNEL, TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel",  EZALERTMGRCHANNEL );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( atmutilobj.InitEzATMUtil( this ) < 0 )
	{
		trace( "Error in Initializing DeviceUtil...." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( networkutilobj.initNetworkUtil( this ) < 0 )
	{
		trace( "Error in Initializing DeviceUtil...." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.initAlertMemUtil( this ) < 0 )
	{
		trace( "Error in Initializing AlertMemUtil...." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadStatusAlert() < 0 )
	{
		trace( "Error in Loading StatusAlert....." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadSMSAlertGroup() < 0 )
	{
		trace( "Error in Loading SMSAlertGroup....." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadMailAlertGroup() < 0 )
	{
		trace( "Error in Loading MailAlertGroup....." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadAlertInfo() < 0 )
	{
		trace( "Error in Loading AlertInfo....." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadAlertSeqMemory() < 0 )
	{
		trace( "Error in Loading AlertSeqMemory....." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ezalertmemutil.LoadAlertDesc() < 0 )
	{
		trace( "Error in Loading AlertDesc....." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	initAlertMgrUtil( this, &ezalertmemutil );

	if( dbutilobj.initDBUtil( TaskName, this ) < 0 )
	{
		trace( "Error in Initializing DBUtil..." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( dbutilobj.DBConnect() < 0 )
	{
		trace( "Error in Connecting with Switch DB...." );
		trace( "^^^^^^^^^^^EzAlertMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();

	}
	TaskInit();
	initEzSigUtil( this );
	return 1;
}

int EzAlertMgr :: insertSMSBufferInfo( const char *InstId, const char *MobileList, const char *MsgBuffer )
{
	char SMSDate[ 10 ], SMSTime[ 10 ], SMSSeqNo[ 25 ], SMSStatus;
	int retval;

	trace( "Inserting InstId[%s] MobileList[%s] MsgBuffer[%s] in EzSMSBufferInfo Table....", InstId, MobileList, MsgBuffer );

	memset( SMSSeqNo, 0, sizeof( SMSSeqNo ) );
	ezalertmemutil.genSMSAlertSeqNo( SMSSeqNo );

	memset( SMSDate, 0, sizeof( SMSDate ) );
	sprintf( SMSDate, "%06d", dtutil.getSysDate() );

	memset( SMSTime, 0, sizeof( SMSTime ) );
	sprintf( SMSTime, "%06d", dtutil.getSysTime() );

	SMSStatus = SMS_PENDING;

	retval = insertSMSBufferInfoTable( SMSSeqNo, InstId, SMSDate, SMSTime, SMS_PENDING, MobileList, MsgBuffer );

	if( ALERT_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutilobj.DBConnect() < 0 )
		{
			trace( "Error in Connecting with Switch DB..." );
			return -1;
		}
		retval = insertSMSBufferInfoTable( SMSSeqNo, InstId, SMSDate, SMSTime, SMSStatus, MobileList, MsgBuffer );
	}
	if( retval != 0 )
	{
		trace( "Error in Inserting SMSSeqNo[%s] InstId[%s] SMSDate[%s] SMSTime[%s] SMSStatus[%c] MobileList[%s] MsgBuffer[%s] in EzSMSBufferInfo Table...SqlErr[%05d]", SMSSeqNo, InstId, SMSDate, SMSTime, SMSStatus, MobileList, MsgBuffer, retval );
		return -1;
	}
	trace( "Inserted SMSSeqNo[%s] InstId[%s] SMSDate[%s] SMSTime[%s] SMSStatus[%c] MobileList[%s] MsgBuffer[%s] in EzSMSBufferInfo Table", SMSSeqNo, InstId, SMSDate, SMSTime, SMSStatus, MobileList, MsgBuffer );
	return 1;
}

int EzAlertMgr :: insertMailBufferInfo( const char *InstId, const char *FromAddress, const char *ToList, const char *CCList, const char *Subject, const char *MsgBuffer )
{
	char MailDate[ 10 ], MailTime[ 10 ], MailSeqNo[ 25 ], MailStatus;
	int retval;

	trace( "Inserting InstId[%s] FromAddress[%s] ToList[%s] CCList[%s] Subject[%s] MsgBuffer[%s] in EzMailBufferInfo Table....", InstId, FromAddress, ToList, CCList, Subject, MsgBuffer );

	memset( MailSeqNo, 0, sizeof( MailSeqNo ) );
	ezalertmemutil.genMailAlertSeqNo( MailSeqNo );

	memset( MailDate, 0, sizeof( MailDate ) );
	sprintf( MailDate, "%06d", dtutil.getSysDate() );

	memset( MailTime, 0, sizeof( MailTime ) );
	sprintf( MailTime, "%06d", dtutil.getSysTime() );

	MailStatus = MAIL_PENDING;

	retval = insertMailBufferInfoTable( MailSeqNo, InstId, MailDate, MailTime, MailStatus, FromAddress, ToList, CCList, Subject, MsgBuffer );

	if( ALERT_ORA_CONNECT_ERR( retval ) )
	{
		if( dbutilobj.DBConnect() < 0 )
		{
			trace( "Error in Connecting with Switch DB..." );
			return -1;
		}
		retval = insertMailBufferInfoTable( MailSeqNo, InstId, MailDate, MailTime, MailStatus, FromAddress, ToList, CCList, Subject, MsgBuffer );
	}
	if( retval != 0 )
	{
		trace( "Error in Inserting MailSeqNo[%s] InstId[%s] MailDate[%s] MailTime[%s] MailStatus FromAddress[%s] ToList[%s] CCList[%s] Subject[%s] MsgBuffer[%s] in EzMailBufferInfo Table...SqlErr[%05d]", MailSeqNo, InstId, MailDate, MailTime, MailStatus, FromAddress, ToList, CCList, Subject, MsgBuffer, retval );
		return -1;
	}
	trace( "Inserted MailSeqNo[%s] InstId[%s] MailDate[%s] MailTime[%s] MailStatus FromAddress[%s] ToList[%s] CCList[%s] Subject[%s] MsgBuffer[%s] in EzMailBufferInfo Table", MailSeqNo, InstId, MailDate, MailTime, MailStatus, FromAddress, ToList, CCList, Subject, MsgBuffer );
	return 1;
}

void EzAlertMgr :: processATMAlertRequest( struct EzATMAlertMsg atmalertmsg )
{
	struct EzStatusAlertMemory statusrec;
	struct EzSMSAlertGroupMemory smsalertgrouprec;
	struct EzMailAlertGroupMemory mailalertgrouprec;
	char MsgBuffer[ ALERT_MSG_BUFFER_SIZE + 1 ], StatusCode[ 11 ];
	char ExtMsgBuffer[ ALERT_EXTMSG_BUFFER_SIZE + 1 ];
	struct AtmMemoryTable atmmemrec;
	struct AtmTableInfo atminforec;
	int StatusCount = 0;

	trace( DEBUG_TEST, "Processing ATM Alert Request for ATMId[%s] StatusCode[%s]", atmalertmsg.ATMId, atmalertmsg.StatusCode );

	memset( &atmmemrec, 0, sizeof( struct AtmMemoryTable ) );
	if( atmutilobj.ReadAtmMemory( atmalertmsg.ATMId, &atmmemrec ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading ATMId[%s] from DeviceMemory Table....", atmalertmsg.ATMId );
		return;
	}

	memset( &atminforec, 0, sizeof( struct AtmTableInfo ) );
	memcpy( &atminforec, &atmmemrec.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );

	trace( "Read ATMId[%s] with InstId[%s] Location[%s]... ", atmalertmsg.ATMId, atminforec.AcquirerInst, atminforec.AtmLocation );

	trace("atmalertmsg.StatusCode[%s]", atmalertmsg.StatusCode);

	memset( &statusrec, 0, sizeof( struct EzStatusAlertMemory ) );
	StatusCount = eztokenutil.getNToken( atmalertmsg.StatusCode, '|' );
	trace("StatusCount[%d]",StatusCount);

	for( int i = 0; i < StatusCount; i++ )
	{
		memset( StatusCode, 0, sizeof( StatusCode ) );
		eztokenutil.getTokenExSpaces( atmalertmsg.StatusCode, StatusCode, '|', i + 1 );
		trace("StatusCode [%s]", StatusCode );
		if( strlen( StatusCode ) )
		{
			if( ezalertmemutil.readStatusAlert( atminforec.AcquirerInst, atmalertmsg.ATMId, "ATM", StatusCode, &statusrec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading InstId[%s] ATMId[%s] StatusCode[%s] from EzStatusAlert Table....", atminforec.AcquirerInst, atmalertmsg.ATMId, atmalertmsg.StatusCode );
				continue;
			}

			trace( DEBUG_TEST, "Read SMSReq[%c] MailReq[%c] SMSAlertGroupId[%s] MailAlertGroupId[%s] for InstId[%s] ATMId[%s] StatusCode[%s] from EzStatusAlert Table", statusrec.SMSReq, statusrec.MailReq, statusrec.SMSAlertGroupId, statusrec.MailAlertGroupId, atminforec.AcquirerInst, atmalertmsg.ATMId, StatusCode );

			if( statusrec.SMSReq == 'y' || statusrec.SMSReq == 'Y' )
			{
				memset( &smsalertgrouprec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
				if( ezalertmemutil.readSMSAlertGroup( statusrec.SMSAlertGroupId, &smsalertgrouprec ) < 0 )
					trace( DEBUG_TEST, "Error in Reading SMSGroupId[%s] from EzSMSAlertGroup Table....", statusrec.SMSAlertGroupId );
				else
				{
					trace( DEBUG_TEST, "Read MobileList[%s] TemplateFile[%s] from EzSMSAlertGroup Table", smsalertgrouprec.MobileList, smsalertgrouprec.TemplateFile );

					memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
					if( composeATMAlertTemplate( atminforec, atmalertmsg.ATMId, StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
						trace( DEBUG_ERROR, "Error in Composing ATMAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
					else
					{
						trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );
						insertSMSBufferInfo( atminforec.AcquirerInst, smsalertgrouprec.MobileList, MsgBuffer );
					}
				}
			}

			if( statusrec.MailReq == 'y' || statusrec.MailReq == 'Y' )
			{
				memset( &mailalertgrouprec, 0, sizeof( struct EzMailAlertGroupMemory ) );
				if( ezalertmemutil.readMailAlertGroup( statusrec.MailAlertGroupId, &mailalertgrouprec ) < 0 )
					trace( DEBUG_TEST, "Error in Reading MailGroupId[%s] from EzSMSAlertGroup Table....", statusrec.MailAlertGroupId );
				else
				{
					trace( DEBUG_TEST, "Read ToList[%s] CCList[%s] TemplateFile[%s] from EzMailAlertGroup Table", mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.TemplateFile );

					memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
					if( composeATMAlertTemplate( atminforec, atmalertmsg.ATMId, StatusCode, mailalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
						trace( DEBUG_TEST, "Error in Composing ATMAlertTemplate for TemplateFile[%s]", mailalertgrouprec.TemplateFile );
					else
					{
						trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );
						insertMailBufferInfo( atminforec.AcquirerInst, mailalertgrouprec.FromAddress, mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.Subject, MsgBuffer );
					}
				}
			}
		}
	}
}

void EzAlertMgr :: processPortAlertRequest( struct EzPortAlertMsg portalertmsg )
{
	char PortType[ 20 ], InstId[ 13 ], NetworkId[ 17 ];
	struct EzStatusAlertMemory statusrec;
	struct EzSMSAlertGroupMemory smsalertgrouprec;
	struct EzMailAlertGroupMemory mailalertgrouprec;
	char MsgBuffer[ ALERT_MSG_BUFFER_SIZE + 1 ], StatusCode[ 11 ];
	struct AtmMemoryTable atmmemrec;
	struct AtmTableInfo atminforec;

	trace( DEBUG_TEST, "Processing Port Alert Request for PortId[%s] StatusCode[%s]", portalertmsg.PortId, portalertmsg.StatusCode );

	memset( PortType, 0, sizeof( PortType ) );
	if( getPortType( portalertmsg.PortId, PortType ) < 0 )
	{
		trace( "Error in getting PortType for PortId[%s]", portalertmsg.PortId );
		return;
	}

	if( !strcasecmp( PortType, "ATM" ) )
	{
		trace( DEBUG_TEST, "Processing ATM Alert Request for ATMId[%s] StatusCode[%s]", portalertmsg.PortId, portalertmsg.StatusCode );

		memset( &atmmemrec, 0, sizeof( struct AtmMemoryTable ) );
		if( atmutilobj.ReadAtmMemory( portalertmsg.PortId, &atmmemrec ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading ATMId[%s] from DeviceMemory Table....", portalertmsg.PortId );
			return;
		}

		memset( &atminforec, 0, sizeof( struct AtmTableInfo ) );
		memcpy( &atminforec, &atmmemrec.AtmInfoBuffer, sizeof( struct AtmTableInfo ) );

		trace( "Read ATMId[%s] with InstId[%s] Location[%s]... ", atminforec.AcquirerInst, atminforec.AtmLocation );

		memset( &statusrec, 0, sizeof( struct EzStatusAlertMemory ) );
		if( ezalertmemutil.readStatusAlert( atminforec.AcquirerInst, portalertmsg.PortId, "ATM", portalertmsg.StatusCode, &statusrec ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Reading InstId[%s] ATMId[%s] StatusCode[%s] from EzStatusAlert Table....", atminforec.AcquirerInst, portalertmsg.PortId, portalertmsg.StatusCode );
			return;
		}

		trace( DEBUG_TEST, "Read SMSReq[%c] MailReq[%c] SMSAlertGroupId[%s] MailAlertGroupId[%s] for InstId[%s] ATMId[%s] StatusCode[%s] from EzStatusAlert Table", statusrec.SMSReq, statusrec.MailReq, statusrec.SMSAlertGroupId, statusrec.MailAlertGroupId, atminforec.AcquirerInst, portalertmsg.PortId, portalertmsg.StatusCode );

		if( statusrec.SMSReq == 'y' )
		{
			memset( &smsalertgrouprec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
			if( ezalertmemutil.readSMSAlertGroup( statusrec.SMSAlertGroupId, &smsalertgrouprec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading SMSGroupId[%s] from EzSMSAlertGroup Table....", statusrec.SMSAlertGroupId );
				return;
			}

			trace( DEBUG_TEST, "Read MobileList[%s] TemplateFile[%s] from EzSMSAlertGroup Table", smsalertgrouprec.MobileList, smsalertgrouprec.TemplateFile );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( composeATMAlertTemplate( atminforec, portalertmsg.PortId, portalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Composing ATMAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
				return;
			}
			trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );
			insertSMSBufferInfo( atminforec.AcquirerInst, smsalertgrouprec.MobileList, MsgBuffer );
		}

		if( statusrec.MailReq == 'y' )
		{
			memset( &mailalertgrouprec, 0, sizeof( struct EzMailAlertGroupMemory ) );
			if( ezalertmemutil.readMailAlertGroup( statusrec.MailAlertGroupId, &mailalertgrouprec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading MailGroupId[%s] from EzSMSAlertGroup Table....", statusrec.MailAlertGroupId );
				return;
			}

			trace( DEBUG_TEST, "Read ToList[%s] CCList[%s] TemplateFile[%s] from EzMailAlertGroup Table", mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.TemplateFile );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( composeATMAlertTemplate( atminforec, portalertmsg.PortId, portalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Composing ATMAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
				return;
			}

			trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );

			insertMailBufferInfo( atminforec.AcquirerInst, mailalertgrouprec.FromAddress, mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.Subject, MsgBuffer );
		}
	}
	else if ( !strcasecmp( PortType, "NETWORK" ) )
	{
		memset( NetworkId, 0, sizeof( NetworkId ) );
		if( networkutilobj.getNetworkIdFromPort( portalertmsg.PortId, NetworkId ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading NetworkId from NetworkPort[%s]", portalertmsg.PortId );
			return;
		}

		trace( DEBUG_TEST, "Processing Network Alert Request for NetworkId[%s] StatusCode[%s]", NetworkId, portalertmsg.StatusCode );

		if( networkutilobj.readNetworkMemory( NetworkId ) < 0 )
		{
			trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from Network Memory", NetworkId );
			return;
		}

		trace( "Read NetworkId[%s] InstId[%s] from NetworkMemory Table", NetworkId );

		memset( &statusrec, 0, sizeof( struct EzStatusAlertMemory ) );

		if( ezalertmemutil.readStatusAlert( networkutilobj.getInstId(), NetworkId, "NETWORK", portalertmsg.StatusCode, &statusrec ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Reading InstId[%s] NetworkId[%s] StatusCode[%s] from EzStatusAlert Table....", networkutilobj.getInstId(), NetworkId, portalertmsg.StatusCode  );
			return;
		}

		trace( DEBUG_TEST, "Read SMSReq[%c] MailReq[%c] SMSAlertGroupId[%s] MailAlertGroupId[%s] for InstId[%s] ATMId[%s] StatusCode[%s] from EzStatusAlert Table", statusrec.SMSReq, statusrec.MailReq, statusrec.SMSAlertGroupId, statusrec.MailAlertGroupId, networkutilobj.getInstId(), NetworkId, portalertmsg.StatusCode );

		if( statusrec.SMSReq == 'y' )
		{
			memset( &smsalertgrouprec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
			if( ezalertmemutil.readSMSAlertGroup( statusrec.SMSAlertGroupId, &smsalertgrouprec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading SMSGroupId[%s] from EzSMSAlertGroup Table....", statusrec.SMSAlertGroupId );
				return;
			}

			trace( DEBUG_TEST, "Read MobileList[%s] TemplateFile[%s] from EzSMSAlertGroup Table", smsalertgrouprec.MobileList, smsalertgrouprec.TemplateFile );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( composeNetworkAlertTemplate( networkutilobj, NetworkId, portalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Composing NetworkAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
				return;
			}

			trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );
			insertSMSBufferInfo( atminforec.AcquirerInst, smsalertgrouprec.MobileList, MsgBuffer );

		}

		if( statusrec.MailReq == 'y' )
		{
			memset( &mailalertgrouprec, 0, sizeof( struct EzMailAlertGroupMemory ) );
			if( ezalertmemutil.readMailAlertGroup( statusrec.MailAlertGroupId, &mailalertgrouprec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading MailGroupId[%s] from EzSMSAlertGroup Table....", statusrec.MailAlertGroupId );
				return;
			}

			trace( DEBUG_TEST, "Read ToList[%s] CCList[%s] TemplateFile[%s] from EzMailAlertGroup Table", mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.TemplateFile );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( composeNetworkAlertTemplate( networkutilobj, NetworkId, portalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Composing NetworkAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
				return;
			}

			trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );
			insertMailBufferInfo( atminforec.AcquirerInst, mailalertgrouprec.FromAddress, mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.Subject, MsgBuffer );
		}
	}
	else
	{
		memset( InstId, 0, sizeof( InstId ) );
		if( getPortInstId( portalertmsg.PortId, InstId ) < 0 )
		{
			trace( "Error in Selecting InstId for PortId[%s] PortType[%s]", portalertmsg.PortId, PortType );
			return;
		}

		trace( DEBUG_TEST, "Selected InstId[%s] for PortId[%s] PortType[%s]", InstId, portalertmsg.PortId, PortType );

		memset( &statusrec, 0, sizeof( struct EzStatusAlertMemory ) );

		if( ezalertmemutil.readStatusAlert( InstId, portalertmsg.PortId, "PORT", portalertmsg.StatusCode, &statusrec ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Reading InstId[%s] PortId[%s] StatusCode[%s] from EzStatusAlert Table....", InstId, portalertmsg.PortId, portalertmsg.StatusCode );
			return;
		}

		trace( DEBUG_TEST, "Read SMSReq[%c] MailReq[%c] SMSAlertGroupId[%s] MailAlertGroupId[%s] for InstId[%s] PortId[%s] StatusCode[%s] from EzStatusAlert Table", statusrec.SMSReq, statusrec.MailReq, statusrec.SMSAlertGroupId, statusrec.MailAlertGroupId, InstId, portalertmsg.PortId, portalertmsg.StatusCode );

		if( statusrec.SMSReq == 'y' )
		{
			memset( &smsalertgrouprec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
			if( ezalertmemutil.readSMSAlertGroup( statusrec.SMSAlertGroupId, &smsalertgrouprec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading SMSGroupId[%s] from EzSMSAlertGroup Table....", statusrec.SMSAlertGroupId );
				return;
			}

			trace( DEBUG_TEST, "Read MobileList[%s] TemplateFile[%s] from EzSMSAlertGroup Table", smsalertgrouprec.MobileList, smsalertgrouprec.TemplateFile );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( composePortAlertTemplate( InstId, PortType, portalertmsg.PortId, portalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Composing PortAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
				return;
			}

			trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );

			insertSMSBufferInfo( atminforec.AcquirerInst, smsalertgrouprec.MobileList, MsgBuffer );
		}

		if( statusrec.MailReq == 'y' )
		{
			memset( &mailalertgrouprec, 0, sizeof( struct EzMailAlertGroupMemory ) );
			if( ezalertmemutil.readMailAlertGroup( statusrec.MailAlertGroupId, &mailalertgrouprec ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Reading MailGroupId[%s] from EzSMSAlertGroup Table....", statusrec.MailAlertGroupId );
				return;
			}

			trace( DEBUG_TEST, "Read ToList[%s] CCList[%s] TemplateFile[%s] from EzMailAlertGroup Table", mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.TemplateFile );

			memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
			if( composePortAlertTemplate( InstId, PortType, portalertmsg.PortId, portalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
			{
				trace( DEBUG_TEST, "Error in Composing PortAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
				return;
			}

			trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );

			insertMailBufferInfo( atminforec.AcquirerInst, mailalertgrouprec.FromAddress, mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.Subject, MsgBuffer );
		}
	}
}

void EzAlertMgr :: processNetworkAlertRequest( struct EzNetworkAlertMsg networkalertmsg )
{
	struct EzStatusAlertMemory statusrec;
	struct EzSMSAlertGroupMemory smsalertgrouprec;
	struct EzMailAlertGroupMemory mailalertgrouprec;
	char MsgBuffer[ ALERT_MSG_BUFFER_SIZE + 1 ];

	trace( DEBUG_TEST, "Processing Network Alert Request for NetworkId[%s] StatusCode[%s]", networkalertmsg.NetworkId, networkalertmsg.StatusCode );

	if( networkutilobj.readNetworkMemory( networkalertmsg.NetworkId ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Reading NetworkId[%s] from Network Memory", networkalertmsg.NetworkId );
		return;
	}

	trace( "Read NetworkId[%s] InstId[%s] from NetworkMemory Table", networkalertmsg.NetworkId );

	memset( &statusrec, 0, sizeof( struct EzStatusAlertMemory ) );

	if( ezalertmemutil.readStatusAlert( networkutilobj.getInstId(), networkalertmsg.NetworkId, "NETWORK", networkalertmsg.StatusCode, &statusrec ) < 0 )
	{
		trace( DEBUG_TEST, "Error in Reading InstId[%s] NetworkId[%s] StatusCode[%s] from EzStatusAlert Table....", networkutilobj.getInstId(), networkalertmsg.NetworkId, networkalertmsg.StatusCode  );
		return;
	}

	trace( DEBUG_TEST, "Read SMSReq[%c] MailReq[%c] SMSAlertGroupId[%s] MailAlertGroupId[%s] for InstId[%s] ATMId[%s] StatusCode[%s] from EzStatusAlert Table", statusrec.SMSReq, statusrec.MailReq, statusrec.SMSAlertGroupId, statusrec.MailAlertGroupId, networkutilobj.getInstId(), networkalertmsg.NetworkId, networkalertmsg.StatusCode );

	if( statusrec.SMSReq == 'y' )
	{
		memset( &smsalertgrouprec, 0, sizeof( struct EzSMSAlertGroupMemory ) );
		if( ezalertmemutil.readSMSAlertGroup( statusrec.SMSAlertGroupId, &smsalertgrouprec ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Reading SMSGroupId[%s] from EzSMSAlertGroup Table....", statusrec.SMSAlertGroupId );
			return;
		}

		trace( DEBUG_TEST, "Read MobileList[%s] TemplateFile[%s] from EzSMSAlertGroup Table", smsalertgrouprec.MobileList, smsalertgrouprec.TemplateFile );

		memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
		if( composeNetworkAlertTemplate( networkutilobj, networkalertmsg.NetworkId, networkalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Composing NetworkAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
			return;
		}

		trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );

		insertSMSBufferInfo( networkutilobj.getInstId(), smsalertgrouprec.MobileList, MsgBuffer );
	}

	if( statusrec.MailReq == 'y' )
	{
		memset( &mailalertgrouprec, 0, sizeof( struct EzMailAlertGroupMemory ) );
		if( ezalertmemutil.readMailAlertGroup( statusrec.MailAlertGroupId, &mailalertgrouprec ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Reading MailGroupId[%s] from EzSMSAlertGroup Table....", statusrec.MailAlertGroupId );
			return;
		}

		trace( DEBUG_TEST, "Read ToList[%s] CCList[%s] TemplateFile[%s] from EzMailAlertGroup Table", mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.TemplateFile );

		memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
		if( composeNetworkAlertTemplate( networkutilobj, networkalertmsg.NetworkId, networkalertmsg.StatusCode, smsalertgrouprec.TemplateFile, MsgBuffer ) < 0 )
		{
			trace( DEBUG_TEST, "Error in Composing NetworkAlertTemplate for TemplateFile[%s]", smsalertgrouprec.TemplateFile );
			return;
		}

		trace( DEBUG_TEST, "Composed MsgBuffer[%s]", MsgBuffer );

		insertMailBufferInfo( networkutilobj.getInstId(), mailalertgrouprec.FromAddress, mailalertgrouprec.ToList, mailalertgrouprec.CCList, mailalertgrouprec.Subject, MsgBuffer );
	}
}

void EzAlertMgr :: processTxnAlertRequest( struct EzTxnAlertMsg txnalertmsg )
{

}

void EzAlertMgr :: startAlertMgr()
{
	int MsgSize;
	struct EzAlertMgrMsg alertmgrmsg;
	struct EzATMAlertMsg atmalertmsg;
	struct EzPortAlertMsg portalertmsg;
	struct EzNetworkAlertMsg networkalertmsg;
	struct EzTxnAlertMsg txnalertmsg;

	while( 1 )
	{
		trace( "EzAlertMgr Waiting for Request...." );
		memset( &alertmgrmsg, 0, sizeof( struct EzAlertMgrMsg ) );
		if( ReadMessage( ( char * )&alertmgrmsg, &MsgSize ) < 0 )
		{
			trace( "Error While Reading Message from EzAlertMgr Channel...." );
			sleep( 1 );
			continue;
		}

		switch ( alertmgrmsg.AlertCode )
		{
			case ALERT_CODE_ATMSTATUS:

				memset( &atmalertmsg, 0, sizeof( struct EzATMAlertMsg ) );
				memcpy( &atmalertmsg, alertmgrmsg.MsgBuffer, sizeof( struct EzATMAlertMsg ) );
				processATMAlertRequest( atmalertmsg );

			break;

			case ALERT_CODE_PORTSTATUS:

				memset( &portalertmsg, 0, sizeof( struct EzPortAlertMsg ) );
				memcpy( &portalertmsg, alertmgrmsg.MsgBuffer, sizeof( struct EzPortAlertMsg ) );
				processPortAlertRequest( portalertmsg );

			break;

			case ALERT_CODE_NETWORKSTATUS:

				memset( &networkalertmsg, 0, sizeof( struct EzNetworkAlertMsg ) );
				memcpy( &networkalertmsg, alertmgrmsg.MsgBuffer, sizeof( struct EzNetworkAlertMsg ) );
				processNetworkAlertRequest( networkalertmsg );

			break;

			case ALERT_CODE_TXN:

				memset( &txnalertmsg, 0, sizeof( struct EzTxnAlertMsg ) );
				memcpy( &txnalertmsg, alertmgrmsg.MsgBuffer, sizeof( struct EzTxnAlertMsg ) );
				processTxnAlertRequest( txnalertmsg );

			break;

			default:
				trace( "Invalid AlertCode Received...." );
			break;
		}
	}
}

int main( int argc, char **argv )
{
	EzAlertMgr alertmgrobj;
	alertmgrobj.initAlertMgr( argv[ 0 ] );
	alertmgrobj.startAlertMgr();
	return 1;
}
