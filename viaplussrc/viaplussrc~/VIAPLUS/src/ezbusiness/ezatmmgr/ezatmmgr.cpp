#include <ezbusiness/ezatmmgr.h>

EzAtmMgr :: EzAtmMgr()
{
}

EzAtmMgr :: ~EzAtmMgr()
{
}

void EzAtmMgr :: initEzAtmMgr( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ];

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezatmmgr.log" );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	SetDebug();

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzTaskUtil");
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	/*if( dbutil.initDBUtil( TaskName, this ) < 0 )
	{
		trace( DEBUG_ERROR, "Error in Initializing the EzDBUtil");
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}

	if( dbutil.DBConnect( ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Connecting the Database");
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		exit( 0 );
	}*/

	if ( initEzAtmMgrUtil( TaskName, this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing AtmMgrUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( ( IsTaskRunning( TaskName ) < 0 ) && ( getAtmSemVal() <= 0 ) && ( getAtmFitSemVal() <= 0 ) )
	{
		trace( DEBUG_NORMAL, "First Instance of EzAtmMgr...Initializing AtmSharedMemory" );
		if( LoadAtmMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading Atm Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"Atm Memory Loaded successfully...");

		if( LoadAtmFit() < 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading Atm Fit...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"Atm Fit Loaded successfully...");

		if( LoadAtmEjMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading AtmEj Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmEj Memory Loaded successfully...");

		if( LoadAtmPropertyMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading AtmProperty Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmProperty Memory Loaded successfully...");

		if( LoadAtmActionPropertyMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading AtmActionProperty Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmActionProperty Memory Loaded successfully...");

		if( LoadAtmStatusMemory()	< 0 )
		{
			trace( DEBUG_ERROR,"Error in Loading AtmStatus Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmStatus Memory Loaded successfully...");

	}
	else
	{
		trace( DEBUG_NORMAL, "Not a First Instance of EzAtmMgr...Attaching AtmSharedMemory" );
		if( GetAtmMemory() < 0 )
		{
			trace( DEBUG_ERROR,"Error in getting Atm Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"Atm Memory attached successfully...");

		if( GetAtmFit() < 0 )
		{
			trace( DEBUG_ERROR,"Error in getting Atm Fit Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"Atm Fit attached successfully...");

		if( GetAtmEjMemory() < 0 )
		{
			trace( DEBUG_ERROR,"Error in getting AtmEj Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmEj Memory attached successfully...");

		if( GetAtmPropertyMemory() < 0 )
		{
			trace( DEBUG_ERROR,"Error in getting AtmProperty Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmProperty Memory attached successfully...");

		if( GetAtmActionPropertyMemory() < 0 )
		{
			trace( DEBUG_ERROR,"Error in getting AtmActionProperty Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmActionProperty Memory attached successfully...");

		if( GetAtmStatusMemory() < 0 )
		{
			trace( DEBUG_ERROR,"Error in getting AtmStatus Memory...");
			trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}
		else
			trace( DEBUG_NORMAL,"AtmStatus Memory attached successfully...");
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Initializing EzChannelUtil" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( ATMMGRCHANNEL, TaskName ) < 0 )
	{
		trace( DEBUG_ERROR,"Error in Creating EzAtmMgr Channel" );
		trace( DEBUG_ERROR,"^^^^^^^^^^^EzAtmMgr Ended Abnormally^^^^^^^^^^^^^");
		closeDebug();
		TaskExit();
	}

	TaskInit();
	initEzSigUtil( this );
}

void EzAtmMgr :: ServiceRequest()
{
		int MsgSize;
        struct EzAtmMgrQMsg atmmgrqmsg;

        struct AtmFitMsg atmfitmsg;
        struct AtmStatusMsg atmstatusmsg;
        struct LogDetails logdetails;
        struct AtmDenomStatusMsg atmdenomstatusmsg;
        struct AtmTraceNumMsg atmtracenummsg;
        struct TritonStatusMsg tritonstatusmsg;

        while( 1 )
        {
				//dbutil.dbUtilClose();
                trace( DEBUG_NORMAL,"AtmMgr Waiting for Service Request...." );
                memset( &atmmgrqmsg, 0, sizeof( struct EzAtmMgrQMsg ) );
                if( ReadMessage( ( char * )&atmmgrqmsg, &MsgSize ) > 0 )
                {
						trace( DEBUG_NORMAL,"Received Request from channel[%s] ", GetLastSenderChannelName() );
						//dbutil.dbUtilConnect();
                	    switch ( atmmgrqmsg.SourceType )
                        {
                                case MEMORY:
                                	trace( DEBUG_NORMAL, "Memory updation Request");
                                	switch( atmmgrqmsg.CommandCode )
                                	{
                                        	case ATMINFOMEMORY:
                                        		switch( atmmgrqmsg.OperationCode )
                                               	{
													case ADD:
														trace( DEBUG_NORMAL, "Adding Atm[%s] in AtmInfoMemory", atmmgrqmsg.AtmId );
														if( addAtmMemory( atmmgrqmsg.SourceBuffer, atmmgrqmsg.AtmId ) < 0 )
															trace( DEBUG_ERROR,"Error in Adding Atm[%s] in Memory", atmmgrqmsg.AtmId );
														break;
													case UPDATE:
														trace( DEBUG_NORMAL, "updating Atm[%s] in AtmInfoMemory", atmmgrqmsg.AtmId );
														if( updateAtmMemory( atmmgrqmsg.AtmId ) < 0 )
															trace( DEBUG_ERROR,"Error in updating Atm[%s] in Memory", atmmgrqmsg.AtmId );
														break;
													case DELETE:
														trace( DEBUG_NORMAL, "Removing Atm[%s] in AtmInfoMemory", atmmgrqmsg.AtmId );
														if( removeAtmMemory( atmmgrqmsg.AtmId ) < 0 )
															trace( DEBUG_ERROR,"Error in removing Atm[%s] in Memory", atmmgrqmsg.AtmId );
														break;
													default:
														trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
														break;
												}
                                        	break;

											case ATMPROPERTY:
												switch( atmmgrqmsg.OperationCode )
												{
													case ADD:
														trace( DEBUG_NORMAL, "Adding RecordId[%d] in AtmPropertyMemory", atoi( atmmgrqmsg.AtmId ));
														if( addAtmPropertyMemory( atoi( atmmgrqmsg.AtmId ) ) < 0 )
															trace( DEBUG_ERROR,"Error in Adding RecordId[%d] in Memory", atoi( atmmgrqmsg.AtmId ) );
														break;
													case UPDATE:
														trace( DEBUG_NORMAL, "Updating RecordId[%d] in AtmPropertyMemory", atoi( atmmgrqmsg.AtmId ));
														if( updateAtmPropertyMemory( atoi( atmmgrqmsg.AtmId ) ) < 0 )
															trace( DEBUG_ERROR,"Error in Updating RecordId[%d] in Memory", atoi( atmmgrqmsg.AtmId ) );
														break;
													case DELETE:
														trace( DEBUG_NORMAL, "Removing RecordId[%d] in AtmPropertyMemory", atoi( atmmgrqmsg.AtmId ));
														if( removeAtmPropertyMemory( atoi( atmmgrqmsg.AtmId ) ) < 0 )
															trace( DEBUG_ERROR,"Error in Removing RecordId[%d] in Memory", atoi( atmmgrqmsg.AtmId ) );
														break;
													default:
														trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
														break;
												}
											break;

											case ATMACTIONPROPERTY:
												switch( atmmgrqmsg.OperationCode )
												{
													case ADD:
														trace( DEBUG_NORMAL, "Adding RecordId[%d] in AtmActionPropertyMemory", atoi( atmmgrqmsg.AtmId ));
														if( addAtmActionPropertyMemory( atoi( atmmgrqmsg.AtmId ) ) < 0 )
															trace( DEBUG_ERROR,"Error in Adding RecordId[%d] in Memory", atoi( atmmgrqmsg.AtmId ) );
														break;
													case UPDATE:
														trace( DEBUG_NORMAL, "Updating RecordId[%d] in AtmActionPropertyMemory", atoi( atmmgrqmsg.AtmId ));
														if( updateAtmActionPropertyMemory( atoi( atmmgrqmsg.AtmId ) ) < 0 )
															trace( DEBUG_ERROR,"Error in Updating RecordId[%d] in Memory", atoi( atmmgrqmsg.AtmId ) );
														break;
													case DELETE:
														trace( DEBUG_NORMAL, "Removing RecordId[%d] in AtmActionPropertyMemory", atoi( atmmgrqmsg.AtmId ));
														if( removeAtmActionPropertyMemory( atoi( atmmgrqmsg.AtmId ) ) < 0 )
															trace( DEBUG_ERROR,"Error in Removing RecordId[%d] in Memory", atoi( atmmgrqmsg.AtmId ) );
														break;
													default:
														trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
														break;
												}
											break;

                                        	case FITMEMORY:
                                        		memset( &atmfitmsg, 0, sizeof( struct AtmFitMsg ) );
                                        		memcpy( &atmfitmsg, atmmgrqmsg.SourceBuffer, sizeof( struct AtmFitMsg ) );

                                        		switch( atmmgrqmsg.OperationCode )
                                                {
	                                                case ADD:
	                                                	trace( DEBUG_NORMAL, "Adding AtmFitMemory");
														if( addAtmFit( &atmfitmsg ) < 0 )
															trace( DEBUG_ERROR,"Error in Adding FitRecord in Memory for <%s><%s>", atmfitmsg.InstId, atmfitmsg.FitRecord );
														break;
													case UPDATE:
														trace( DEBUG_NORMAL, "Updating AtmFitMemory");
														if( updateAtmFit( &atmfitmsg ) < 0 )
															trace( DEBUG_ERROR,"Error in Updating FitRecord in Memory for <%s><%s>", atmfitmsg.InstId, atmfitmsg.FitRecord );
														break;
													case DELETE:
														trace( DEBUG_NORMAL, "Deleting AtmFitMemory");
														if( removeAtmFit( &atmfitmsg ) < 0 )
															trace( DEBUG_ERROR,"Error in Deleting FitRecord in Memory for <%s><%s>", atmfitmsg.InstId, atmfitmsg.FitRecord );
														break;
													default:
														trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
														break;
												}
											break;

                                        	default:
												trace( DEBUG_ERROR,"Invalid CommandCode [%d]", atmmgrqmsg.CommandCode );
											break;
                                	}
                                break;// Ending Memory

                                case TABLE:
                                	trace( DEBUG_NORMAL, "Table updation Request");
                                	switch( atmmgrqmsg.CommandCode )
                                	{
                                       	case ATMLOG:

                                       		trace( DEBUG_NORMAL, "Updating AtmLog Table");
                                       		memset( &logdetails, 0, sizeof( struct LogDetails ) );
                                       		memcpy( &logdetails, atmmgrqmsg.SourceBuffer, sizeof( struct LogDetails ) );

                                       		switch( atmmgrqmsg.OperationCode )
                                            {
                                       			case INSERT:
                                       					retval = InsertAtmLog( &logdetails );
									if( retval == -1  )
                                       					{
															if( DBConnect() < 0 )
															{
																trace( DEBUG_ERROR,"Error in Connecting with Switch DB....Cannot Insert ATMLog Table..." );
																break;
															}
															retval = InsertAtmLog( &logdetails );
                                       					}
                                       					if( retval != 0)
                                       						trace( DEBUG_ERROR,"unable to insert AtmLOG OraErr[ %04d ]", retval );
                                       				break;
                                       			case TRUNCATE:
                                       					retval = TruncateAtmLog();
                                       					if( retval != 0)
                                       						trace( DEBUG_ERROR,"unable to Truncate AtmLOG OraErr[ %04d ]", retval );
                                       				break;
                                       			default:
														trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
													break;
                                            }
                                       	break;

                                        case ATMSTATUS:

                                        	trace( DEBUG_NORMAL, "Updating EzAtmStatus Table");

                                        	memset( &atmstatusmsg, 0, sizeof( struct AtmStatusMsg ) );
                                        	memcpy( &atmstatusmsg, atmmgrqmsg.SourceBuffer, sizeof( struct AtmStatusMsg ) );

                                        	switch( atmmgrqmsg.OperationCode )
                                            {
                                        		case UPDATE:

                                        			if( UpdateATMStatusTable( &atmstatusmsg ) < 0 )
                                        				trace( DEBUG_ERROR,"Error while Updating ATM Status in table" );

                                        			break;

                                        		case TRUNCATE:

                                        			retval = TruncateAtmStatusHist();
	                               					if( retval != 0)
	                               						trace( DEBUG_ERROR,"unable to Truncate ATMLOG OraErr[ %04d ]", retval );
                                       				break;

                                        		default:

													trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
													break;
                                            }
                                        break;

                                        case ATMDENOMSTATUS:

                                        	trace( DEBUG_NORMAL, "Updating EzAtmDenomStatus Table");
                                        	memset( &atmdenomstatusmsg, 0, sizeof( struct AtmDenomStatusMsg ) );
                                        	memcpy( &atmdenomstatusmsg, atmmgrqmsg.SourceBuffer, sizeof( struct AtmDenomStatusMsg ) );

                                        	switch( atmmgrqmsg.OperationCode )
                                            {
                                        		case UPDATE:

                                        		retval = UpdateAtmDenomStatus( &atmdenomstatusmsg );
												if(  retval == -1 )
												{
													if( DBConnect() < 0 )
													{
														trace( "Error in Connecting with Switch DB..Cannot Update DenomStatus Table..for AtmId[%s]", atmdenomstatusmsg.AtmId );
														break;
													}
													retval = UpdateAtmDenomStatus( &atmdenomstatusmsg );
												}
												if( retval != 0 )
												{
													trace( DEBUG_ERROR,"unable to Update AtmDenomStatus OraErr[ %05d ] for [ %s ]", retval, atmdenomstatusmsg.AtmId );
													break;
												}

												retval = InsertAtmDenomHist( &atmdenomstatusmsg );
												if(  retval == -1 )
												{
													if( DBConnect() < 0 )
													{
														trace( "Error in Connecting with Switch DB..Cannot Insert DenomHist Table..for AtmId[%s]", atmdenomstatusmsg.AtmId );
														break;
													}
													retval = InsertAtmDenomHist( &atmdenomstatusmsg );
												}
												if( retval != 0 )
												{
													trace( DEBUG_ERROR,"Unable to Insert AtmDenomHist OraErr[ %05d ] for [ %s ]", retval, atmdenomstatusmsg.AtmId );
													break;
												}
                                        		break;

                                        		default:
													trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
													break;
                                            }
                                        break;

                                        case ATMTRACE:

                                        	trace( DEBUG_NORMAL, "Updating AtmTraceNo Table");
                                        	memset( &atmtracenummsg, 0, sizeof( struct AtmTraceNumMsg ) );
                                        	memcpy( &atmtracenummsg, atmmgrqmsg.SourceBuffer, sizeof( struct AtmTraceNumMsg ) );

                                        	switch( atmmgrqmsg.OperationCode )
                                            {
                                        		case UPDATE:

                                        		retval = UpdateAtmTraceNo( &atmtracenummsg );

                                        		if( retval == -1 )
                                        		{
                                        			if( DBConnect() < 0 )
                                        			{
														trace( "Error in Connecting Switch DB.....Cannot Update TraceNo for ATMId[%s] TraceNo[%d] in EZATMDATAINFO Table", atmtracenummsg.AtmId, atmtracenummsg.AtmTraceNo );
														break;
                                        			}
                                        			retval = UpdateAtmTraceNo( &atmtracenummsg );
                                        		}
                                        		if( retval == 1403 )
                                        		{
                                        			retval = InsertAtmTraceNo( &atmtracenummsg );
                                        			if( retval != 0 )
                                        			{
                                        				trace( "Error in Inserting AtmId[%s] TraceNo[%d] in EZATMDATAINFO Table...SqlErr[%05d]", atmtracenummsg.AtmId, atmtracenummsg.AtmTraceNo, retval );
                                        				break;
                                        			}
                                        		}
                                        		else if( retval != 0 )
                                        		{
                                        			trace( "Error in Updating AtmId[%s] TraceNo[%d] in EZATMDATAINFO Table...SqlErr[%05d]", atmtracenummsg.AtmId, atmtracenummsg.AtmTraceNo, retval );
                                        			break;
                                        		}

                                       			break;

                                        		default:

                                        		trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
												break;
                                            }

                                        break;

										case TRITONSTATUS:

											trace( DEBUG_NORMAL, "Updating TritonStatusLog Table");
											memset( &tritonstatusmsg, 0, sizeof( struct TritonStatusMsg ) );
											memcpy( &tritonstatusmsg, atmmgrqmsg.SourceBuffer, sizeof( struct TritonStatusMsg ) );

											switch( atmmgrqmsg.OperationCode )
											{
												case UPDATE:
													retval = updateTritonStatusLog( atmmgrqmsg.AtmId, &tritonstatusmsg );
													if( retval == -1 )
													{
														if( DBConnect() < 0 )
														{
															trace( "Error in Connecting with Switch DB...Cannot Update TritonStatusLog Table..." );
															break;
														}
														retval = updateTritonStatusLog( atmmgrqmsg.AtmId, &tritonstatusmsg );
													}
													if( retval != 0 )
													{
														trace( DEBUG_ERROR,"unable to Update TritonStatusLog OraErr[ %04d ]", retval );
														trace( DEBUG_ERROR, "StatusDate< %s > StatusTime< %s >", tritonstatusmsg.StatusDate, tritonstatusmsg.StatusTime );
														trace( DEBUG_ERROR, "PgmVersionNo< %s > TabVersionNo< %s > FirmVersionNo< %s >", tritonstatusmsg.PgmVersionNo, tritonstatusmsg.TabVersionNo, tritonstatusmsg.FirmVersionNo );
														trace( DEBUG_ERROR, "AlarmChestDoor< %c > AlarmTopDoor< %c > AlarmSupervisor< %c >", tritonstatusmsg.AlarmChestDoor, tritonstatusmsg.AlarmTopDoor, tritonstatusmsg.AlarmSupervisor);
                                                        trace( DEBUG_ERROR, "RPPaper< %c > RPRibbon< %c >", tritonstatusmsg.RPPaper, tritonstatusmsg.RPRibbon );
                                                        trace( DEBUG_ERROR, "JPPaper< %c > JPRibbon< %c >", tritonstatusmsg.JPPaper, tritonstatusmsg.JPRibbon );
                                                        trace( DEBUG_ERROR, "DispNote< %c > RPStatus< %c > JPStatus< %c > DispStatus< %c > CommSystem< %c > CardReader< %c >", tritonstatusmsg.DispNote,tritonstatusmsg.RPStatus,tritonstatusmsg.JPStatus,tritonstatusmsg.DispStatus,tritonstatusmsg.CommSystem,tritonstatusmsg.CardReader);
														trace( DEBUG_ERROR, "CardsRetained< %s > ErrCode< %s >", tritonstatusmsg.CardsRetained, tritonstatusmsg.ErrCode );
														trace( DEBUG_ERROR, "CassADenom< %s > CassALoaded< %s > CassAMin< %s > CassADisp< %s > CassAReject< %s > CassANotes< %s > CassACash< %s >", tritonstatusmsg.CassADenom,tritonstatusmsg.CassALoaded,tritonstatusmsg.CassAMin,tritonstatusmsg.CassADisp,tritonstatusmsg.CassAReject,tritonstatusmsg.CassANotes,tritonstatusmsg.CassACash);
														trace( DEBUG_ERROR, "CassBDenom< %s > CassBLoaded< %s > CassBMin< %s > CassBDisp< %s > CassBReject< %s > CassBNotes< %s > CassBCash< %s >", tritonstatusmsg.CassBDenom,tritonstatusmsg.CassBLoaded,tritonstatusmsg.CassBMin,tritonstatusmsg.CassBDisp,tritonstatusmsg.CassBReject,tritonstatusmsg.CassBNotes,tritonstatusmsg.CassBCash);
														trace( DEBUG_ERROR, "CassCDenom< %s > CassCLoaded< %s > CassCMin< %s > CassCDisp< %s > CassCReject< %s > CassCNotes< %s > CassCCash< %s >", tritonstatusmsg.CassCDenom,tritonstatusmsg.CassCLoaded,tritonstatusmsg.CassCMin,tritonstatusmsg.CassCDisp,tritonstatusmsg.CassCReject,tritonstatusmsg.CassCNotes,tritonstatusmsg.CassCCash);
														trace( DEBUG_ERROR, "CassDDenom< %s > CassDLoaded< %s > CassDMin< %s > CassDDisp< %s > CassDReject< %s > CassDNotes< %s > CassDCash< %s >", tritonstatusmsg.CassDDenom,tritonstatusmsg.CassDLoaded,tritonstatusmsg.CassDMin,tritonstatusmsg.CassDDisp,tritonstatusmsg.CassDReject,tritonstatusmsg.CassDNotes,tritonstatusmsg.CassDCash);
														trace( DEBUG_ERROR, "TotCash< %s > TotNotesPurged< %s >", tritonstatusmsg.TotCash, tritonstatusmsg.TotNotesPurged );
													}
													break;
												default:
													trace( DEBUG_ERROR,"Invalid OpertionCode [%d]", atmmgrqmsg.OperationCode );
													break;
											}
											break;

                                        default:
                                        	trace( DEBUG_ERROR,"Invalid CommandCode [%d]", atmmgrqmsg.CommandCode );
                                        	break;
                                	}
                                break;//Ending Table

                                default:
                                	   trace( DEBUG_ERROR,"Invalid SourceType [%d]", atmmgrqmsg.SourceType );
                        		       break;
                         }
                }
                else
                	trace( DEBUG_ERROR,"Error in Receiving message <%s> <%d>", strerror( errno ), errno );
        }
}

int main( int argc, char **argv )
{
	EzAtmMgr ezatmmgr_obj;
	ezatmmgr_obj.initEzAtmMgr( argv[ 0 ] );
	ezatmmgr_obj.ServiceRequest();
	return 1;
}
