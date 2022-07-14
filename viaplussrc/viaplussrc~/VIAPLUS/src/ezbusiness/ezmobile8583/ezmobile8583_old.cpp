#include <ezbusiness/ezmobile8583.h>
#include <ezbusiness/ezdevwrapper.h>
#include <ezlink/ezauthdb.h>
#include <ezutils/ezdbcfg.h>
#include <ezutils/ezcfg.h>
#include <string.h>
#include <ctype.h>
#include <eztasktools.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

EzMobile8583 :: EzMobile8583( ezdebug * adbg ) : FmtUtil( adbg )
{
	dbg = adbg;
} 

EzMobile8583 :: ~EzMobile8583()
{
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

 
int EzMobile8583 :: InitDriver( string DBname )
{
	int ret ;
	string DBUserName, DBPassWord, DBName ;
	char GroupHndlrPipe[65], BitMapPath[ 150 ];

	ISOPipe = new EzPipe( "Mobile8583Handler" );
	dbg->trace( NORMAL, "Mobile8583Handler Pipe got created...\n" );

	if ( GetDBUserDetails( DBName, DBUserName, DBPassWord ) < 0 )
	{
		dbg->trace( NORMAL, "Unable to get the details from the config\n" );
		return -1;
	}

	if ( ( ret = ConnectDB( ( char * ) DBUserName.c_str(), ( char * ) DBPassWord.c_str() , ( char * ) DBName.c_str() ) ) < 0 )
		dbg->trace( NORMAL, "Unable to connect with DB [ORA%04d]\n", ret );
	else
		dbg->trace( NORMAL, "Connected with Database successfully\n" );

        dbg->trace( NORMAL, "Ezmobile is initialised \n" );

	return 1;
}


int EzMobile8583 :: ServiceRequests()
{
	EzDevWrapper DevWrapper ;
	char MsgBuf[ 1024 ];
		
	for(;;)
	{
		if( ISOPipe->RcvMsg( ( char * ) &DevWrapper, sizeof( DevWrapper ) ) < 0 )
		{
			dbg->trace( NORMAL, "Connection with PipeMgr is Broken\n" );
                        exit(0);
		}
		GroupHandlerPipeName = ISOPipe->SrcPipe() ;
		dbg->trace( NORMAL, "Received an Request from [%s]\n", ISOPipe->SrcPipe() );
		dbg->trace( NORMAL, "Group Handler Pipe Name [%s]\n", GroupHandlerPipeName.c_str() ); 
		//dbg->hex_dump( ( unsigned char * ) DevWrapper.MsgBuf, DevWrapper.MsgSize ) ;
		dbg->trace( NORMAL, "Message is from Device [%s]\n", DevWrapper.DevicePipeName );
		if ( DevWrapper.CmdCode == DECOMPOSE_REQUEST )
		{
			memset( MsgBuf, 0, sizeof( MsgBuf ) );
			memcpy( MsgBuf, DevWrapper.MsgBuf, DevWrapper.MsgSize );
			DiagnizeAndServeNetworkRequest( MsgBuf, DevWrapper.MsgSize, DevWrapper.DevicePipeName ); 
		}
		else if ( DevWrapper.CmdCode == COMPOSE_REQUEST )
			DiagnizeAndServeAppRequest( DevWrapper.MsgBuf, DevWrapper.MsgSize, DevWrapper.DevicePipeName ); 
	}
}


int EzMobile8583:: DiagnizeAndServeNetworkRequest( char * MsgBuf, int MsgSize, char * DevicePipeName )
{
	int size ;
	EzMsg DevMsg ;
	EzDevWrapper DevWrapper ;
	char XMsg[512];
	
	dbg->trace( NORMAL, "Servicing Network request [%s]\n", MsgBuf );
	
	memset( &DevMsg, 0, sizeof( EzMsg ) );
	size = DecomposeISOMessage( MsgBuf, &DevMsg, DevicePipeName ); 
	dbg->trace( NORMAL, "Size of the Msg[%d]\n", MsgSize);

	if ( size > 0 )
	{
		memset( &DevWrapper, 0, sizeof( EzDevWrapper ) );
		DevWrapper.CmdCode = DECOMPOSE_RESPONSE ;
		DevWrapper.MsgSize = sizeof( EzMsg ) ;
		if ( DevMsg.MsgId == NETWORK_TXN_REQUEST )
			strcpy( DevMsg.DeviceId, DevicePipeName );
		strcpy( DevWrapper.DevicePipeName, DevicePipeName );
		memcpy( DevWrapper.MsgBuf, &DevMsg, sizeof( EzMsg ) );

		if( ISOPipe->SendMsg( GroupHandlerPipeName.c_str(), &DevWrapper, sizeof( EzDevWrapper ) ) < 0 )
			dbg->trace( NORMAL, "Error in Sending Message from Mobile8583...SysErr[%s] ErrNo[%d]\n", strerror( errno ), errno );
		else
			dbg->trace( NORMAL, "Message Sent Successfully from Mobile8583\n");
	}
	return 1;
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

int EzMobile8583:: DiagnizeAndServeAppRequest( char * MsgBuf, int MsgSize, char * DevicePipeName )
{
	int size ;
	EzMsg DevMsg ;
	EzDevWrapper DevWrapper ;

	char XMsg[1024];
	memset( XMsg, 0, sizeof( XMsg ) );
	dbg->trace( NORMAL, "Servicing Application request\n" );
	memset( &DevMsg, 0, sizeof( DevMsg ) );
	memcpy( &DevMsg, MsgBuf, sizeof( DevMsg ) );

	if( DevMsg.MsgId = NETWORK_TXN_RESPONSE )
	{
		size = ComposeRespMsg( DevMsg, XMsg );
		
	}
	else 
		dbg->trace( NORMAL,"<Unsupported MSG TYPE>\n");
	
	dbg->hex_dump( ( unsigned char * ) XMsg, size );
	memset( &DevWrapper, 0, sizeof( EzDevWrapper ) );
	DevWrapper.CmdCode = COMPOSE_RESPONSE ;
	DevWrapper.MsgSize = size ;
	strcpy( DevWrapper.DevicePipeName, DevicePipeName );
	memcpy( DevWrapper.MsgBuf, XMsg, size );

	ISOPipe->SendMsg( GroupHandlerPipeName.c_str(), &DevWrapper, sizeof( EzDevWrapper ) );
}

int EzMobile8583:: ComposeRespMsg( EzMsg Devmsg, char * ResMsg)
{
	char MobileNumber[ 25 ];
	FILE *fp;
        char Buffer[ 200 ], FileName[ 100 ];
        int len;

	memset( MobileNumber, 0, sizeof( MobileNumber ) );
//	dbg->trace( NORMAL, "Mobile Number Length[ %d ]\n", strlen(Devmsg.txnmsg.TermLocation) );

	strncpy( MobileNumber, Devmsg.txnmsg.TermLocation, 13 );
	dbg->trace( NORMAL, "Mobile Number Length[ %s ]\n", MobileNumber );
	//dbg->trace( NORMAL, "Composing the Response Message[ %d ]\n", Devmsg.txnmsg.MsgType );

	dbg->trace( NORMAL, "Response Code [ %d ]\n", Devmsg.txnmsg.Response );

	memset( ResMsg , 0, sizeof( ResMsg ) );
	
	switch( Devmsg.txnmsg.Response )
	{
		case 0:
			dbg->trace( NORMAL, "Transaction Code [ %d ]\n", Devmsg.txnmsg.TxnCode );
			switch( Devmsg.txnmsg.TxnCode )
			{
				case 301000:
					sprintf( ResMsg, "%s%c%s%s%s%12s%s%c%s", MobileNumber, 0x1c, "The available balance for the A/C NO", Devmsg.txnmsg.FromAccount, " is ", Devmsg.txnmsg.AvailBalance, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 302000:
					sprintf( ResMsg, "%s%c%s%s%s%12s%s%c%s", MobileNumber, 0x1c, "The available balance for the A/C NO", Devmsg.txnmsg.FromAccount, " is ", Devmsg.txnmsg.AvailBalance, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 303000:
					sprintf( ResMsg, "%s%c%s%s%s%12s%s%c%s", MobileNumber, 0x1c, "The available balance for the A/C NO", Devmsg.txnmsg.FromAccount, " is ", Devmsg.txnmsg.AvailBalance, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 921000:
					sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Statement request transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed", "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 922000:
					sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Statement request transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed" , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 923000:
					sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Statement request transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed" , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 481000:
					sprintf( ResMsg, "%s%c%s%s%s%d%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed. Cheque is honoured on " ,Devmsg.txnmsg.IdDate, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 482000:
					sprintf( ResMsg, "%s%c%s%s%s%d%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed. Cheque is honoured on " ,Devmsg.txnmsg.IdDate, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 483000:
					sprintf( ResMsg, "%s%c%s%s%s%d%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed. Cheque is honoured on " ,Devmsg.txnmsg.IdDate, "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 491000:
					sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The  Stop Payment transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed.Stop Payment Request Recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 492000:
					sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The  Stop Payment transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed.Stop Payment Request Recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				case 493000:
					sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The  Stop Payment transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed.Stop Payment Request Recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );
					break;
				default:
					sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
					break;
			}
			break;	
		case 5: 
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Requested Information could not be retrived,Please try latter ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 7: 
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "This is not a  Registered Mobile number ,Try with your Registered Mobile number ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 14:
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Requested Information could not be retrived, This is a Invalid Card  ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 80:	
			sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed.Cheque is Dishonoured" , "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 82:
			sprintf( ResMsg, "%s%c%s%s%s%s%c%s", MobileNumber, 0x1c, "The Cheque Status Inquiry transaction for the A/C NO", Devmsg.txnmsg.FromAccount, " is sucussfully completed.Cheque yet not recieved." , "\r\n From Samarth Bank ", 0x1c, "0" );			
			break;
		case 83: 
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Other Reason, Contact Branch.  ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 41:
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "HOT Card, Contact Branch.  ", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 54:
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Your Card is Expried, Contact Branch.", "\r\n From Samarth Bank ", 0x1c, "0" );
			break;
		case 800:
			memset( FileName, 0, sizeof( FileName ) );
			sprintf( FileName, "%s/mobileinfo/%s", getenv( "EZDIR" ), Devmsg.txnmsg.RsvFld3 );
			dbg->trace( NORMAL, "FileName[ %s ]\n", FileName );

			fp = fopen( FileName, "r" );
		        if( fp == NULL )
		        {
                		dbg->trace( NORMAL, "failed to open file< %s >..\n", FileName );
				sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
		        }

		        memset( Buffer, 0, sizeof( Buffer ) );
		        len = fread( Buffer, sizeof( Buffer ), sizeof( Buffer ), fp);
		        if( len == 0 )
		        {
                		dbg->trace( NORMAL, "Buffer< %s >\n", Buffer );
				sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, Buffer, "\r\n From Samarth Bank ", 0x1c, "0" );
		                fclose( fp );
                		
        		}
			else
			{
                		dbg->trace( NORMAL, "unable to read the file< %d >\n", len );
		                fclose( fp );
				sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
				
			}	
			break;
		default:
			sprintf( ResMsg, "%s%c%s%s%c%s", MobileNumber, 0x1c, "Unable to Process your request","\r\n From Samarth Bank ", 0x1c, "0" );
			break;
	}
	return strlen(ResMsg);
}


int EzMobile8583 :: DecomposeISOMessage( char * InBuf, EzMsg *devMsg, char * DeviceId )
{
	int len ;
	char MobileNumber[17];
	char AplnCode[17];
	char Ack[2];
	char TransCode[200],TranCode[50],TranData[100];
	char Chn[20];
	char InstNo[13],Acc_Type[3];
	int PCode;
	struct ezcardinfo cinfo;
	struct ezcustomer custinfo; 
	time_t tme ;
	struct tm * t;
	char local_date[7], local_time[7], tran_date[7], tran_time[7];

		
	memset( MobileNumber, 0, sizeof( MobileNumber ) );
	memset( AplnCode, 0, sizeof( AplnCode ) );
	memset( Ack, 0, sizeof( Ack ) );
	memset( TransCode, 0, sizeof( TransCode ) );
	memset( Chn, 0, sizeof( Chn ) );
	memset( devMsg, 0, sizeof(EzMsg));
	memset( TranCode, 0, sizeof( TranCode ));
	memset( TranData, 0, sizeof( TranData ));

	
	getToken( InBuf, AplnCode, 0x1c, 1 );
	dbg->trace( NORMAL, "AplnCode [%s]\n",AplnCode );
	getToken( InBuf, MobileNumber, 0x1c, 2 );
	dbg->trace( NORMAL, "MobileNumber [%s]\n",MobileNumber );
	getToken( InBuf, Ack, 0x1c, 3 );
	dbg->trace( NORMAL, "Ack [%s]\n",Ack );
	getToken( InBuf, TransCode, 0x1c, 4 );
	dbg->trace( NORMAL, "TransCode [%s]\n",TransCode );
	getToken( TransCode, TranCode, ' ', 1);
	dbg->trace( NORMAL, "TranCode [%s]\n",TranCode );
	getToken( TransCode, TranData, ' ', 2);
	dbg->trace( NORMAL, "TranData [%s]\n",TranData );

	if ( ( len = GetMobileFileInfo( TranCode, devMsg->txnmsg.RsvFld3 ) ) != 0 )
	{
		dbg->trace( NORMAL, "Error in Reading EzMobileFileInfo: ORA[ %d ]\n", len );
	}
	else
	{
		dbg->trace( NORMAL, "MobileCode< %s > Filename< %s >\n", TranCode, devMsg->txnmsg.RsvFld3 );
		devMsg->txnmsg.Response = 800;
		
		devMsg->MsgId = NETWORK_TXN_RESPONSE;
		strcpy(devMsg->DeviceId,"MOBILE");
		dbg->trace( NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( devMsg->txnmsg.TermLocation, MobileNumber , strlen(MobileNumber));
		devMsg->txnmsg.OrgTraceNo = GenerateDeviceTraceNum( devMsg->DeviceId ); 
		time( &tme );
		t= localtime( &tme ); 
		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		devMsg->txnmsg.TranDate = atol( local_date );
		devMsg->txnmsg.TranTime = atol( local_time );
		devMsg->txnmsg.OrgDate = atol( local_date );
		devMsg->txnmsg.OrgTime = atol( local_time );
		devMsg->txnmsg.LocalDate = atol( local_date );
		devMsg->txnmsg.LocalTime = atol( local_time );
		devMsg->txnmsg.CaptureDate = atol( local_date );
		devMsg->txnmsg.CaptureTime = atol( local_time );
		
		DiagnizeAndServeAppRequest( (char *) devMsg, sizeof( devMsg ), DeviceId );
		return 0;
	}
	
	len =  GetChn( MobileNumber, Chn );
	if ( len != 0) 
	{
		dbg->trace( NORMAL, "Mobile Number in Not Valid [%d]\n",len );
		devMsg->txnmsg.Response = 7;
		devMsg->MsgId = NETWORK_TXN_RESPONSE;
		strcpy(devMsg->DeviceId,"MOBILE");
		dbg->trace( NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( devMsg->txnmsg.TermLocation, MobileNumber , strlen(MobileNumber));
		devMsg->txnmsg.OrgTraceNo = GenerateDeviceTraceNum( devMsg->DeviceId ); 
		time( &tme );
		t= localtime( &tme ); 
		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		devMsg->txnmsg.TranDate = atol( local_date );
		devMsg->txnmsg.TranTime = atol( local_time );
		devMsg->txnmsg.OrgDate = atol( local_date );
		devMsg->txnmsg.OrgTime = atol( local_time );
		devMsg->txnmsg.LocalDate = atol( local_date );
		devMsg->txnmsg.LocalTime = atol( local_time );
		devMsg->txnmsg.CaptureDate = atol( local_date );
		devMsg->txnmsg.CaptureTime = atol( local_time );
		DiagnizeAndServeAppRequest( ( char * ) devMsg, sizeof( devMsg ), DeviceId );
		return 0;
	}
	else 
		dbg->trace( NORMAL, "MobileNumber [%s] belongs to the CHN [%s]\n", MobileNumber, Chn );
	
	
	dbg->trace( NORMAL, " < CONDITION: CHECK CARDNO[%s] IN EZCARDINFO TABLE > \n", Chn ); 
	if( ( len = readCardInfo( Chn, &cinfo ) ) != 0 )
	{
		dbg->trace( NORMAL, " < Error In reading the ora[%d] From EZCARDINFO TABLE > \n", len );
		dbg->trace( NORMAL, " < Error In reading the CARDNO[%s] From EZCARDINFO TABLE > \n", Chn );
		devMsg->txnmsg.Response = 14;
			
		devMsg->MsgId = NETWORK_TXN_RESPONSE;
		strcpy(devMsg->DeviceId,"MOBILE");
		dbg->trace( NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( devMsg->txnmsg.TermLocation, MobileNumber , strlen(MobileNumber));
		devMsg->txnmsg.OrgTraceNo = GenerateDeviceTraceNum( devMsg->DeviceId ); 
		time( &tme );
		t= localtime( &tme ); 
		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		devMsg->txnmsg.TranDate = atol( local_date );
		devMsg->txnmsg.TranTime = atol( local_time );
		devMsg->txnmsg.OrgDate = atol( local_date );
		devMsg->txnmsg.OrgTime = atol( local_time );
		devMsg->txnmsg.LocalDate = atol( local_date );
		devMsg->txnmsg.LocalTime = atol( local_time );
		devMsg->txnmsg.CaptureDate = atol( local_date );
		devMsg->txnmsg.CaptureTime = atol( local_time );
		DiagnizeAndServeAppRequest(( char * ) devMsg, sizeof( devMsg ), DeviceId );
		return 0;
	}
	else
	{
		dbg->trace( NORMAL, " CARDNO[%s] readed sucessfully From EZCARDINFO TABLE > \n", Chn );
		//dbg->trace( NORMAL,"CARDNO Successfully readed from EZCARDINFO TABLE [%s][%s][%s][%s][%s][%d][%d][%s][%d][%d][%s][%s]" ,cinfo.chn ,cinfo.cardtype ,cinfo.custid,cinfo.name,cinfo.limit_flag,cinfo.expiry_date,cinfo.status,cinfo.pinoffset,cinfo.retrycount,cinfo.last_txn_date,cinfo.txn_group_id,cinfo.visa_pvki);
		dbg->trace( NORMAL, " CARDNO[%s] CUSTID[%s] > \n", cinfo.chn , cinfo.custid );
		
		memset( InstNo, 0, sizeof( InstNo ) );
		strncpy( InstNo, Chn, 6 );
		memset( Acc_Type, 0 ,sizeof(Acc_Type) );
		
		dbg->trace(NORMAL, "Reading the Mobile Transaction Inforamation for TRANSACTION CODE [%s] from EZMOBILETRANSINFO TABLE \n", TransCode );
		
		if ( ( len = GetMobileTranInfo( TranCode, &PCode, Acc_Type ) ) != 0 )
		{
			dbg->trace( NORMAL, "<Error in reading the Mobile Transaction Inforamation from EZMOBILETRANINFO Error ORA[%d]\n>",len);
			devMsg->txnmsg.Response = 5;
			
			devMsg->MsgId = NETWORK_TXN_RESPONSE;
			strcpy(devMsg->DeviceId,"MOBILE");
			dbg->trace( NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
			strncpy( devMsg->txnmsg.TermLocation, MobileNumber , strlen(MobileNumber));
			devMsg->txnmsg.OrgTraceNo = GenerateDeviceTraceNum( devMsg->DeviceId ); 
			time( &tme );
			t= localtime( &tme ); 
			sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
			sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
			devMsg->txnmsg.TranDate = atol( local_date );
			devMsg->txnmsg.TranTime = atol( local_time );
			devMsg->txnmsg.OrgDate = atol( local_date );
			devMsg->txnmsg.OrgTime = atol( local_time );
			devMsg->txnmsg.LocalDate = atol( local_date );
			devMsg->txnmsg.LocalTime = atol( local_time );
			devMsg->txnmsg.CaptureDate = atol( local_date );
			devMsg->txnmsg.CaptureTime = atol( local_time );
			
			DiagnizeAndServeAppRequest(( char * ) devMsg, sizeof( devMsg ), DeviceId );
			return 0;
		}
		else 
			dbg->trace(NORMAL, "Mobile Transaction Inforamation PCODE [%d] ACT_TYPE[%s] Successfully Loaded\n", PCode, Acc_Type);
		
		if ( ( len =  readPrimaryAccount( InstNo, cinfo.custid, Acc_Type, &custinfo ) )!= 0 )
		{
			dbg->trace( NORMAL, "<Error in Reading the ACTNO details from the EZCUSTOMER TABLE Error ORA[%d] \n>",len);
			devMsg->txnmsg.Response = 5;
			devMsg->MsgId = NETWORK_TXN_RESPONSE;
			strcpy(devMsg->DeviceId,"MOBILE");
			dbg->trace( NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
			strncpy( devMsg->txnmsg.TermLocation, MobileNumber , strlen(MobileNumber));
			devMsg->txnmsg.OrgTraceNo = GenerateDeviceTraceNum( devMsg->DeviceId ); 
			time( &tme );
			t= localtime( &tme ); 
			sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
			sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
			devMsg->txnmsg.TranDate = atol( local_date );
			devMsg->txnmsg.TranTime = atol( local_time );
			devMsg->txnmsg.OrgDate = atol( local_date );
			devMsg->txnmsg.OrgTime = atol( local_time );
			devMsg->txnmsg.LocalDate = atol( local_date );
			devMsg->txnmsg.LocalTime = atol( local_time );
			devMsg->txnmsg.CaptureDate = atol( local_date );
			devMsg->txnmsg.CaptureTime = atol( local_time );
			
			DiagnizeAndServeAppRequest(( char * ) devMsg, sizeof( devMsg ), DeviceId );
			return 0;
			
		}
		else 
		{
			dbg->trace( NORMAL, "<AccNO[%s] readed Sucessfully from the EZCUSTOMER TABLE>\n",custinfo.acct_no);
		}
		devMsg->MsgId = NETWORK_TXN_REQUEST;
		strcpy(devMsg->DeviceId,"MOBILE");
		devMsg->txnmsg.TxnCode = PCode;
		dbg->trace( NORMAL, "mobile len [%d] [%s]\n", strlen(MobileNumber), MobileNumber );
		strncpy( devMsg->txnmsg.TermLocation, MobileNumber , strlen(MobileNumber));
		
		
		devMsg->txnmsg.OrgTraceNo = GenerateDeviceTraceNum( devMsg->DeviceId ); 
		devMsg->txnmsg.MsgType = 200;
		
		time( &tme );
		t= localtime( &tme ); 

		sprintf( local_time, "%02d%02d%02d", t->tm_hour, t->tm_min, t->tm_sec );
		sprintf( local_date, "%02d%02d%02d", t->tm_mday, t->tm_mon+1, (t->tm_year+1900) - 2000 );
		
		devMsg->txnmsg.TranDate = atol( local_date );
		devMsg->txnmsg.TranTime = atol( local_time );
		devMsg->txnmsg.OrgDate = atol( local_date );
		devMsg->txnmsg.OrgTime = atol( local_time );
		devMsg->txnmsg.LocalDate = atol( local_date );
		devMsg->txnmsg.LocalTime = atol( local_time );
		devMsg->txnmsg.CaptureDate = atol( local_date );
		devMsg->txnmsg.CaptureTime = atol( local_time );
		strcpy(devMsg->txnmsg.chn, cinfo.chn );
		strcpy(devMsg->txnmsg.AcqBranch, custinfo.branch_id );
		strcpy(devMsg->txnmsg.IssBranch, custinfo.branch_id  ) ;
		strcpy( devMsg->txnmsg.ForwardBranch, custinfo.branch_id );
		strcpy( devMsg->txnmsg.FromAcctType, Acc_Type);
		strcpy( devMsg->txnmsg.FromAcctSubType, custinfo.acct_subtype );
		strcpy(devMsg->txnmsg.FromAccount,custinfo.acct_no);
		strcpy(devMsg->txnmsg.AcquirerInst, custinfo.iin );
		strcpy(devMsg->txnmsg.IssuerInst, custinfo.iin  );
		strcpy(devMsg->txnmsg.ForwardInst, custinfo.iin );
		strcpy(devMsg->txnmsg.IdNo, TranData);
		dbg->trace( NORMAL, "Successfully Completed");

		return 1;
	}
	return 1;
}

int main()
{
	ezdebug ezdbg ;
	TaskTools TTools;
	TTools.TaskInit();

	ezdbg.trace_on_file( "ezmobile8583.log", "ezmobile8583" );	
	EzMobile8583 isoobj( &ezdbg );
	isoobj.InitDriver( "ezdb" );
	isoobj.ServiceRequests();
}
