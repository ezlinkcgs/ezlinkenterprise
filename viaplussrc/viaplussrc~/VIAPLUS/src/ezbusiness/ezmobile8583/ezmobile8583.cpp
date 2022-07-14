#include <ezbusiness/ezmobile8583.h>


EzMobile8583 :: EzMobile8583( ) 
{
	
} 

EzMobile8583 :: ~EzMobile8583()
{
}


 
int EzMobile8583 :: InitMobile8583Driver( const char *TaskName )
{
		char logpath[ LOG_PATH_SIZE + 1 ];

		memset( logpath, 0, sizeof( logpath ) );
		sprintf( logpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "log", "ezmobile8583.log" );

		if( openDebug( logpath, TaskName ) < 0 )
			exit( 0 );

		trace( "^^^^^^^^^^^EzMobile8583 Started Running^^^^^^^^^^^^^");

		if( InitEzTaskUtil( this ) < 0 )
		{
			trace( "Error in Initializing EzTaskUtil");
			trace( "^^^^^^^^^^^EzMobile8583 Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			exit( 0 );
		}

		if( InitEzChannelUtil( this ) < 0 )
		{
			trace( "Error in Initializing EzChannelUtil" );
			trace( "^^^^^^^^^^^EzMobile8583 Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}

		if( CreateChannel( "EzMobile8583" ) < 0 )
		{
			trace( "Error in Creating EzMobile8583 Channel" );
			trace( "^^^^^^^^^^^EzMobile8583 Ended Abnormally^^^^^^^^^^^^^");
			closeDebug();
			TaskExit();
		}


		initFmtUtil( this );

		if( initDBUtil( TaskName, this ) < 0 ) 
        {   
                trace( "Error in Initializing DBUtil..." );
                trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
                closeDebug();
                TaskExit();
        }   

        if( DBConnect() < 0 ) 
        {   
                trace( "Error in Connecting Database" );
                trace( "^^^^^^^^^^^eztxnlogger Ended Abnormally^^^^^^^^^^^^^");
                closeDebug();
                TaskExit();
        }   


		TaskInit();
		initEzSigUtil( this );
}


int EzMobile8583 :: ServiceRequests()
{

	struct EzTxnMsg txnmsg;
	int MsgSize;
	char ISOMessage[ 2600 + 1 ];
	char MsgBuffer[ 2600 + 1 ];
	while( 1 )
	{
		trace( "EzMobile8583 Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetLastSenderChannelName() );
			continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetLastSenderChannelName() );
			hex_dump( ( unsigned char * ) ISOMessage, MsgSize );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );

			strcpy( txnmsg.DestPort, GetLastSenderChannelName() );
			strcpy( txnmsg.SrcPort, GetLastSenderChannelName() );
			strcpy( txnmsg.DestPort, GetLastSenderChannelName() );

			if( DecomposeISOMessage( ISOMessage, &txnmsg ) < 0 )
			{
				trace( "Error in Decomposing ISO Message from Port[%s]", GetLastSenderChannelName() );
				continue;
			}

			if( WriteChannel( "EzTxnMgr", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
				trace( "Error in Writing Message to Channel EzTxnMgr" );
			else
				trace( "Message Sucessfully Written to Channel EzTxnMgr" );

		}
		else
		{
				trace( "Message of size[ %d ] Received from Channel[ %s ]", MsgSize, GetSourceChannelName() );
				memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
				memcpy( &txnmsg, ISOMessage, sizeof( struct EzTxnMsg ) );

				memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
				if( ComposeISOMessage( &txnmsg, MsgBuffer ) < 0 )
				{
					trace( "Error in Composing ISO Message" );
					continue;
				}

				if( WritePortChannel( txnmsg.DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
					trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
				else
					trace( "Written Message to Port[%s]", txnmsg.DestPort );
		}
			
	}
}



int EzMobile8583 :: GetNAccounts( const char *msg )
{
        int cnt = 0;
	for( int i = 0; i < strlen( msg ); i++ )
	{
		if( msg[ i ] == 0x1c )
	        	cnt++;
        }
	return cnt;
}

void EzMobile8583 :: getToken( const char *msg, char *tmp, char ch, int count )
{
  	int i = 0, j = 0, cnt = 0;
	for( i = 0; i < strlen( msg ); i++ )
	{
		if( msg[ i ] == ch )
			cnt++;
	        else if( cnt == count )
	        	break;
		else if ( cnt + 1 == count )
		{
			tmp[ j ] = msg[ i ];
		        j++;
		}
	}
}

int EzMobile8583:: ComposeISOMessage( struct EzTxnMsg *txnmsg, char *OutBuf )
{
	char MobileNumber[ 25 ];
	FILE *fp;
        char Buffer[ 200 ], FileName[ 100 ];
        int len;

	memset( MobileNumber, 0, sizeof( MobileNumber ) );
//	dbg->trace( NORMAL, "Mobile Number Length[ %d ]\n", strlen(txnmsg->txnmsg.TerminalLocation) );

	strncpy( MobileNumber, txnmsg->TerminalLocation, 13 );
	trace( DEBUG_NORMAL, "Mobile Number Length[ %s ]\n", MobileNumber );
	//dbg->trace( NORMAL, "Composing the Response Message[ %d ]\n", txnmsg->txnmsg.MsgType );

	trace( DEBUG_NORMAL, "Response Code [ %d ]\n", txnmsg->RespCode );

	memset( OutBuf , 0, sizeof( OutBuf ) );
	
	switch( txnmsg->RespCode )
	{
		case 0:
			trace( DEBUG_NORMAL, "Transaction Code [ %d ]\n", txnmsg->TxnCode );
			switch( txnmsg->TxnCode )
			{
				case 301000:
					sprintf( OutBuf, "%s%c%s%s%s%12s%s%c%s", MobileNumber, 0x1c, "The available balance for the A/C NO", txnmsg->FromAccount, " is ", txnmsg->AvailBalance, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 302000:
					sprintf( OutBuf, "%s%c%s%s%s%12s%s%c%s", MobileNumber, 0x1c, "The available balance for the A/C NO", txnmsg->FromAccount, " is ", txnmsg->AvailBalance, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 303000:
					sprintf( OutBuf, "%s%c%s%s%s%12s%s%c%s", MobileNumber, 0x1c, "The available balance for the A/C NO", txnmsg->FromAccount, " is ", txnmsg->AvailBalance, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 921000:
					sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Statement request transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed", "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 922000:
					sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Statement request transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed" , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 923000:
					sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Statement request transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed" , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 481000:
					sprintf( OutBuf, "%s%c%s%s%s%d%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed. Cheque is honoured on " ,txnmsg->RsvFld4, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 482000:
					sprintf( OutBuf, "%s%c%s%s%s%d%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed. Cheque is honoured on " ,txnmsg->RsvFld4, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 483000:
					sprintf( OutBuf, "%s%c%s%s%s%d%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed. Cheque is honoured on " ,txnmsg->RsvFld4, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 491000:
					sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The  Stop Payment transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed.Stop Payment Request Recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 492000:
					sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The  Stop Payment transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed.Stop Payment Request Recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 493000:
					sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The  Stop Payment transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed.Stop Payment Request Recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				default:
					sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
					break;
			}
			break;	
		case 5: 
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Requested Information could not be retrived,Please try latter ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 7: 
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "This is not a  Registered Mobile number ,Try with your Registered Mobile number ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 14:
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Requested Information could not be retrived, This is a Invalid Card  ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 80:	
			sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed.Cheque is Dishonoured" , "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 82:
			sprintf( OutBuf, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", txnmsg->FromAccount, " is sucussfully completed.Cheque yet not recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );			
			break;
		case 83: 
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Other Reason, Contact Branch.  ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 41:
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "HOT Card, Contact Branch.  ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 54:
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Your Card is Expried, Contact Branch.", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 800:
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/mobileinfo/%s", getenv( "EZDIR" ), txnmsg->RsvFld3 );
			trace( DEBUG_NORMAL, "FileName[ %s ]\n", FileName );

			fp = fopen( FileName, "r" );
		        if( fp == NULL )
		        {
                		trace( DEBUG_NORMAL, "failed to open file< %s >..\n", FileName );
                		sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
		        }

		        memset( Buffer, 0, sizeof( Buffer ) );
		        len = fread( Buffer, sizeof( Buffer ), sizeof( Buffer ), fp);
		        if( len == 0 )
		        {
                		trace( DEBUG_NORMAL, "Buffer< %s >\n", Buffer );
                		sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, Buffer, "\r\n From Samarth Bank ", 0x1c, "0" );
		                fclose( fp );
                		
        		}
			else
			{
                		trace( DEBUG_NORMAL, "unable to read the file< %d >\n", len );
		                fclose( fp );
		                sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
				
			}	
			break;
		default:
			sprintf( OutBuf, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
			break;
	}
	return strlen(OutBuf);
}



int EzMobile8583 :: DecomposeISOMessage( char * InBuf,  struct EzTxnMsg *txnmsg  )
{
	int len,OraCode ;
	char MobileNumber[17];
	char AplnCode[17];
	char Ack[2];
	char TransCode[200],TranCode[50],TranData[100];
	char Chn[20];
	char InstNo[13],Acc_Type[3];
	int PCode;
	struct EzCardInfo crdinfo;
	//struct ezcustomer custinfo; 
	time_t tme ;
	struct tm * t;
	char local_date[7], local_time[7], tran_date[7], tran_time[7];
	char MsgBuffer[ 2600 + 1 ];

		
	memset( MobileNumber, 0, sizeof( MobileNumber ) );
	memset( AplnCode, 0, sizeof( AplnCode ) );
	memset( Ack, 0, sizeof( Ack ) );
	memset( TransCode, 0, sizeof( TransCode ) );
	memset( Chn, 0, sizeof( Chn ) );
	memset( TranCode, 0, sizeof( TranCode ));
	memset( TranData, 0, sizeof( TranData ));

	
	getToken( InBuf, AplnCode, 0x1c, 1 );
	trace( DEBUG_NORMAL, "AplnCode [%s]\n",AplnCode );
	getToken( InBuf, MobileNumber, 0x1c, 2 );
	trace( DEBUG_NORMAL, "MobileNumber [%s]\n",MobileNumber );
	getToken( InBuf, Ack, 0x1c, 3 );
	trace( DEBUG_NORMAL, "Ack [%s]\n",Ack );
	getToken( InBuf, TransCode, 0x1c, 4 );
	trace( DEBUG_NORMAL, "TransCode [%s]\n",TransCode );
	getToken( TransCode, TranCode, ' ', 1);
	trace( DEBUG_NORMAL, "TranCode [%s]\n",TranCode );
	getToken( TransCode, TranData, ' ', 2);
	trace( DEBUG_NORMAL, "TranData [%s]\n",TranData );
	txnmsg->MerchantType = 6015;
	if ( ( len = GetMobileFileInfo( TranCode, txnmsg->RsvFld3 ) ) != 0 )
	{
		trace( DEBUG_NORMAL, "Error in Reading EzMobileFileInfo: ORA[ %d ]\n", len );
	}
	else
	{
		trace(DEBUG_NORMAL, "MobileCode< %s > Filename< %s >\n", TranCode, txnmsg->RsvFld3 );
		txnmsg->RespCode = 800;
		
		strcpy( txnmsg->TerminalId,"MOBILE");
		trace( DEBUG_NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
		txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort ); 
		time( &tme );
		t= localtime( &tme ); 
		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		txnmsg->TranDate = atol( local_date );
		txnmsg->TranTime = atol( local_time );
		txnmsg->OrgTranDate = atol( local_date );
		txnmsg->OrgTranTime = atol( local_time );
		txnmsg->LocalDate = atol( local_date );
		txnmsg->LocalTime = atol( local_time );
		txnmsg->CaptureDate = atol( local_date );
		txnmsg->CaptureTime = atol( local_time );
		
		if( ComposeISOMessage( txnmsg, MsgBuffer ) < 0 )
		{
			trace( "Error in Composing ISO Message" );
			return -1;
		
		}
		if( WritePortChannel( txnmsg->DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
		{	
			trace( "Error in Writing Message to Port[%s]", txnmsg->DestPort );
			return -1;
		}
		else
			trace( "Written Message to Port[%s]", txnmsg->DestPort );
		return 0;
	}
	
	len =  GetChn( MobileNumber, Chn );
	if ( len != 0) 
	{
		trace( "Mobile Number is Not Valid [%d]\n",len );
		txnmsg->RespCode = 7;
		strcpy( txnmsg->TerminalId,"MOBILE");
		trace( "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
		txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort ); 
		time( &tme );
		t= localtime( &tme ); 
		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		txnmsg->TranDate = atol( local_date );
		txnmsg->TranTime = atol( local_time );
		txnmsg->OrgTranDate = atol( local_date );
		txnmsg->OrgTranTime = atol( local_time );
		txnmsg->LocalDate = atol( local_date );
		txnmsg->LocalTime = atol( local_time );
		txnmsg->CaptureDate = atol( local_date );
		txnmsg->CaptureTime = atol( local_time );
		if( ComposeISOMessage( txnmsg, MsgBuffer ) < 0 )
		{
			trace( "Error in Composing ISO Message" );
			return -1;
		
		}
		if( WritePortChannel( txnmsg->DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
		{	
			trace( "Error in Writing Message to Port[%s]", txnmsg->DestPort );
			return -1;
		}
		else
			trace( "Written Message to Port[%s]", txnmsg->DestPort );
		return 0;
	}
	else 
		trace(DEBUG_NORMAL, "MobileNumber [%s] belongs to the CHN [%s]\n", MobileNumber, Chn );
	
	
	trace( DEBUG_NORMAL, " < CONDITION: CHECK CARDNO[%s] IN EZCARDINFO TABLE > \n", Chn ); 
	if( ( len = ReadEzCardInfo( Chn, &crdinfo ) ) != 0 )
	{
		trace( DEBUG_NORMAL, " < Error In reading the ora[%d] From EZCARDINFO TABLE > \n", len );
		trace( DEBUG_NORMAL, " < Error In reading the CARDNO[%s] From EZCARDINFO TABLE > \n", Chn );
		txnmsg->RespCode = 14;
		strcpy( txnmsg->TerminalId,"MOBILE");
		trace( DEBUG_TEST, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
		txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort ); 
		time( &tme );
		t= localtime( &tme ); 
		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		txnmsg->TranDate = atol( local_date );
		txnmsg->TranTime = atol( local_time );
		txnmsg->OrgTranDate = atol( local_date );
		txnmsg->OrgTranTime = atol( local_time );
		txnmsg->LocalDate = atol( local_date );
		txnmsg->LocalTime = atol( local_time );
		txnmsg->CaptureDate = atol( local_date );
		txnmsg->CaptureTime = atol( local_time );
		if( ComposeISOMessage( txnmsg, MsgBuffer ) < 0 )
		{
			trace( "Error in Composing ISO Message" );
			return -1;
		
		}
		if( WritePortChannel( txnmsg->DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
		{	
			trace( "Error in Writing Message to Port[%s]", txnmsg->DestPort );
			return -1;
		}
		else
			trace( "Written Message to Port[%s]", txnmsg->DestPort );
		return 0;
	}
	else
	{
		trace( DEBUG_NORMAL, " CARDNO[%s] readed sucessfully From EZCARDINFO TABLE > \n", Chn );
		
		memset( InstNo, 0, sizeof( InstNo ) );
		strncpy( InstNo, Chn, 6 );
		memset( Acc_Type, 0 ,sizeof(Acc_Type) );
		
		trace(DEBUG_NORMAL, "Reading the Mobile Transaction Information for TRANSACTION CODE [%s] from EZMOBILETRANSINFO TABLE \n", TransCode );
		
		if ( ( len = GetMobileTranInfo( TranCode, &PCode, Acc_Type ) ) != 0 )
		{
			trace( DEBUG_NORMAL, "<Error in reading the Mobile Transaction Information from EZMOBILETRANINFO Error ORA[%d]\n>",len);
			txnmsg->RespCode = 5;
			
			strcpy( txnmsg->TerminalId,"MOBILE");
			trace( DEBUG_NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
			strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
			txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort ); 
			time( &tme );
			t= localtime( &tme ); 
			sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
			sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
			txnmsg->TranDate = atol( local_date );
			txnmsg->TranTime = atol( local_time );
			txnmsg->OrgTranDate = atol( local_date );
			txnmsg->OrgTranTime = atol( local_time );
			txnmsg->LocalDate = atol( local_date );
			txnmsg->LocalTime = atol( local_time );
			txnmsg->CaptureDate = atol( local_date );
			txnmsg->CaptureTime = atol( local_time );
			
			if( ComposeISOMessage( txnmsg, MsgBuffer ) < 0 )
			{
				trace( "Error in Composing ISO Message" );
				return -1;
			
			}
			if( WritePortChannel( txnmsg->DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
			{	
				trace( "Error in Writing Message to Port[%s]", txnmsg->DestPort );
				return -1;
			}
			else
				trace( "Written Message to Port[%s]", txnmsg->DestPort );
			return 0;
		}
		else 
			trace( DEBUG_NORMAL, "Mobile Transaction Information PCODE [%d] ACT_TYPE[%s] Successfully Loaded\n", PCode, Acc_Type);
		strcpy( InstNo, "SSBL" );		
		trace( DEBUG_NORMAL, "InstNo[%s] Chn[%s] Acc_Type[%s]", InstNo, crdinfo.chn,Acc_Type );
		len =  ReadFirstAccount( InstNo, crdinfo.chn, Acc_Type, txnmsg->FromAccount, &OraCode ) ;
		trace( DEBUG_NORMAL, "OraCode[%d] len[%d]", OraCode,len );
		if( len < 0 )	
		{
			trace( DEBUG_NORMAL, "<Error in Reading the ACTNO details from the EZAUTHREL TABLE Error ORA[%d] \n>",OraCode );
			txnmsg->RespCode = 5;
			strcpy( txnmsg->TerminalId,"MOBILE");
			trace( DEBUG_NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
			strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
			txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort  ); 
			time( &tme );
			t= localtime( &tme ); 
			sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
			sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
			txnmsg->TranDate = atol( local_date );
			txnmsg->TranTime = atol( local_time );
			txnmsg->OrgTranDate = atol( local_date );
			txnmsg->OrgTranTime = atol( local_time );
			txnmsg->LocalDate = atol( local_date );
			txnmsg->LocalTime = atol( local_time );
			txnmsg->CaptureDate = atol( local_date );
			txnmsg->CaptureTime = atol( local_time );
			
			if( ComposeISOMessage( txnmsg, MsgBuffer ) < 0 )
			{
				trace( "Error in Composing ISO Message" );
				return -1;
			
			}
			if( WritePortChannel( txnmsg->DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
			{	
				trace( "Error in Writing Message to Port[%s]", txnmsg->DestPort );
				return -1;
			}
			else
				trace( "Written Message to Port[%s]", txnmsg->DestPort );
			return 0;
			
		}
		else 
		{
			trace( DEBUG_NORMAL, "<ACCNO[%s] readed Sucessfully from the EzAuthRel TABLE>\n",txnmsg->FromAccount );
		}
		if ( SearchEzAccountInfo( InstNo, txnmsg->FromAccount, txnmsg->IssBranchCode, txnmsg->FromAcctSubType ) != 0 )
		{
			trace( DEBUG_NORMAL, "<Error in reading issuer network or product code details from the EzAccountInfo TABLE Error ORA[%d] \n>",len);
			txnmsg->RespCode = 5;
			strcpy( txnmsg->TerminalId,"MOBILE");
			trace( DEBUG_NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
			strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
			txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort  ); 
			time( &tme );
			t= localtime( &tme ); 
			sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
			sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
			txnmsg->TranDate = atol( local_date );
			txnmsg->TranTime = atol( local_time );
			txnmsg->OrgTranDate = atol( local_date );
			txnmsg->OrgTranTime = atol( local_time );
			txnmsg->LocalDate = atol( local_date );
			txnmsg->LocalTime = atol( local_time );
			txnmsg->CaptureDate = atol( local_date );
			txnmsg->CaptureTime = atol( local_time );
			
			if( ComposeISOMessage( txnmsg, MsgBuffer ) < 0 )
			{
				trace( "Error in Composing ISO Message" );
				return -1;
			
			}
			if( WritePortChannel( txnmsg->DestPort, MsgBuffer, strlen( MsgBuffer ) ) < 0 )
			{	
				trace( "Error in Writing Message to Port[%s]", txnmsg->DestPort );
				return -1;
			}
			else
				trace( "Written Message to Port[%s]", txnmsg->DestPort );
			return 0;
		
		}
		else
			trace( DEBUG_NORMAL, "<IssBranchCode[%s] and ProductCode readed Sucessfully from the EzAccountInfo TABLE >\n",txnmsg->IssBranchCode, txnmsg->FromAcctSubType );
		
		strcpy(txnmsg->TerminalId,"MOBILE");
		txnmsg->TxnCode = PCode;
		trace( "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( txnmsg->TerminalLocation, MobileNumber , strlen(MobileNumber));
				
		txnmsg->OrgTraceNo = GenerateDeviceTraceNum( txnmsg->SrcPort  ); 
		txnmsg->MsgType = 200;
		
		time( &tme );
		t= localtime( &tme ); 

		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		
		txnmsg->TranDate = atol( local_date );
		txnmsg->TranTime = atol( local_time );
		txnmsg->OrgTranDate = atol( local_date );
		txnmsg->OrgTranTime = atol( local_time );
		txnmsg->LocalDate = atol( local_date );
		txnmsg->LocalTime = atol( local_time );
		txnmsg->CaptureDate = atol( local_date );
		txnmsg->CaptureTime = atol( local_time );
		strcpy(txnmsg->chn, crdinfo.chn );
		strcpy(txnmsg->AcqBranchCode, txnmsg->IssBranchCode );
		strcpy( txnmsg->ForwardBranchCode, txnmsg->IssBranchCode );
		//strcpy( txnmsg->FromAcctType, Acc_Type);
		//strcpy( txnmsg->FromAcctSubType, custinfo.acct_subtype );
		//strcpy(txnmsg->FromAccount,custinfo.acct_no);
		strcpy( txnmsg->AcquirerInst, InstNo );
		strcpy( txnmsg->IssuerInst, InstNo  );
		strcpy( txnmsg->ForwardInst, InstNo );
		strcpy( txnmsg->RsvFld4, TranData );
		trace( DEBUG_NORMAL, "Successfully Completed" );

		return 1;
	}
}
bool EzMobile8583 :: IsBlankLine( const char *line_str )
{
        for( int i = 0; i < strlen( line_str ); i++ )
        {
                if( ( line_str[ i ] != ' ' ) && ( line_str[ i ] != '\t' ) && ( line_str[ i ] != '\n' ) )
                        return false;
        }
        return true;
}

int EzMobile8583 :: GetLine( const char *LineBuffer, char *RowStr )
{
        for( int i = 0, j = 0; i < strlen( LineBuffer ); i++, j++ )
        {
                if( LineBuffer[ i ] == '\n' )
                        break;
                else
                        RowStr[ j ] = LineBuffer[ i ];
        }
        return 1;
}

int EzMobile8583 :: GetString( const char *LineBuffer, char *ColStr, int Column )
{
        int j = 0;
        bool FoundChar = true;

        int FldCount = 0;

        for( int i = 0; i < strlen( LineBuffer ); i++ )
        {
                if( ( LineBuffer[ i ] != ' ' ) && ( LineBuffer[ i ] != '\t' ) && ( LineBuffer[ i ] != '\n' ) )
                {
                        if( FoundChar )
                                FldCount++;
                        FoundChar = false;
                        if( FldCount == Column )
                        {
                                ColStr[ j ] = LineBuffer[ i ];
                                j++;
                        }
                }
                else
                {
                        FoundChar = true;
                        if( FldCount == Column )
                                break;
                }
        }
        return 1;
}


int main( int argc, char **argv )
{
	
	EzMobile8583 EzMobile8583obj;
	EzMobile8583obj.InitMobile8583Driver( argv[ 0 ] );
	EzMobile8583obj.ServiceRequests();
}
