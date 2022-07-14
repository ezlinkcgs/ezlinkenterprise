#include <ezbusiness/ezatmsimulator.h>

int EzAtmSimulator :: InitAtmSimulator( EzDebugUtil *dptr_ptr, const char *SimId )
{
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgVal[ CFG_VAL_SIZE + 1 ],CfgParam[ CFG_VAL_SIZE +1 ];
	EzCfgUtil cfgutil;
	this->dptr = dptr_ptr;
 
	memset( cfgpath, 0, sizeof( cfgpath ) );
    sprintf( cfgpath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsimulator.cfg" );

    if( cfgutil.cfg_open( cfgpath ) < 0 )
    {
        dptr->trace(  " Error in opening file [%s] ", cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        return -1;
    }
  	
    memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "TMK" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
    	strcpy( atmcfg.Tmk, cfgVal ) ;
    
	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "WITHDRAWSTATUS" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
    	atmcfg.WithdrawalAreaStatus =  cfgVal[ 0 ] ;
	
	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "DISPERRCODE" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
            dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
            dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
            cfgutil.cfg_close();
	return -1;
    }
    else
    	strcpy( atmcfg.DispErrCode, cfgVal ) ;
	
	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "PARTIALDISPSTATUS" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
            dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
            dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
            cfgutil.cfg_close();
            return -1;
    }
    else
    	atmcfg.PartialDispenseStatus = cfgVal[ 0 ] ;
	
	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS1DENOM" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
            dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
            dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
            cfgutil.cfg_close();
	return -1;
    }
    else
		atmcfg.Cass1DenomId = cfgVal[ 0 ] ;	

	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS2DENOM" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
            dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
            dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
            cfgutil.cfg_close();
	return -1;
    }
    else
		atmcfg.Cass2DenomId = cfgVal[ 0 ] ;
	
	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS3DENOM" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
		atmcfg.Cass3DenomId = cfgVal[ 0 ] ;	

	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS4DENOM" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
		atmcfg.Cass4DenomId = cfgVal[ 0 ] ;	

	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS1DISP" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
		strcpy( atmcfg.Cass1Dispensed, cfgVal ) ;
	
	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS2DISP" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
		strcpy( atmcfg.Cass2Dispensed, cfgVal ) ;

	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS3DISP" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
		strcpy( atmcfg.Cass3Dispensed, cfgVal ) ;

	memset( CfgParam, 0, sizeof( CfgParam ) );
    memset( cfgVal, 0, sizeof( cfgVal ) );
    sprintf( CfgParam, "%s#%s", SimId, "CASS4DISP" );
    if( cfgutil.cfg_search( CfgParam, cfgVal, 2 ) < 0 )
    {
        dptr->trace( "Error in Searching [%s] from file[%s]", CfgParam, cfgpath );
        dptr->trace(  "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", SimId );
        cfgutil.cfg_close();
        return -1;
    }
    else
		strcpy( atmcfg.Cass4Dispensed, cfgVal ) ;
	return 1;

}
int EzAtmSimulator :: composePowerUpMessage( int CliSocketId, const char *DevcieSubType )
{
	char AtmBuf[ 1024 ];
	int retval;
	
	memset( AtmBuf, 0, sizeof( AtmBuf ) );
	if( !strcasecmp( DevcieSubType, "D912" ) )
		sprintf( AtmBuf, "12%c%c%c1", 0x1c, 0x1c, 0x1c );
	else if( !strcasecmp( DevcieSubType, "NDC+" ) )
			sprintf( AtmBuf, "12%c%c%cB", 0x1c, 0x1c, 0x1c );
    dptr->trace( "Sending PowerUp Msg..");
    if( writeSocketBuf( AtmBuf,CliSocketId  ) < 0 )
    	return -1;
    if( GetDownLoadMsg( CliSocketId ) < 0 )
    	return -1;
    else
    	return 1;
        
}
int EzAtmSimulator :: writeSocketBuf( const char *Msg, int ConnectionId  )
{
	char SendBuffer[ 1024 ];
	int retval;
	memset( SendBuffer, 0, sizeof( SendBuffer ) );
	dptr->trace( "Writing Msg..In Socket Id[%d]", ConnectionId );
	sprintf( SendBuffer, "%04d%s", strlen( Msg ), Msg );
	retval = write( ConnectionId, SendBuffer, strlen( SendBuffer ) );
	if( retval < 0 )
    {
    	dptr->trace( "Error in Writing Message to Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
    	return -1;
    }
    dptr->trace( "Written Message[%s] of Bytes[%d] to Connection Socket...", Msg, retval );
    return 1;
}
int EzAtmSimulator :: readSocketBuf( char *Msg, int ConnectionId )
{
	char MessageHeader[ 5 ];
	int MsgLen;
	memset( MessageHeader, 0, sizeof( MessageHeader ) );
	if( recv( ConnectionId, MessageHeader, 4, 0 ) <= 0 )
	{
		dptr->trace( "Error in Message Header from Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
		return -1;
	}
	MsgLen = atoi( MessageHeader );

	dptr->trace( "[%d] Bytes available in Connection Socket", MsgLen );
	if( recv( ConnectionId, Msg, MsgLen, 0 ) <= 0 )
	{
		dptr->trace( "Error in Message Header from Connection Socket....SysErr[%s] ErrNo[%d]....", strerror( errno ), errno );
		return -1;
	}

	dptr->trace( "Received Message[%s] from Connection Socket....", Msg );
	dptr->hex_dump( ( unsigned char *)Msg, MsgLen );
	return 1;

}
int EzAtmSimulator :: GetDownLoadMsg( int sockfd )
{
	char AtmBuf[ 1024 ];
	int CurrState = 0, ret;
	bool flag = true;
    CurrState = STATE_OUT_OF_SERVICE;
    while( 1 )
    {
	        memset( AtmBuf, 0, sizeof( AtmBuf ) );
	        if( readSocketBuf( AtmBuf, sockfd ) < 0 )
	        {
	                //closeSocket();
	                flag = false;
	                break;
	        }
            if( CurrState == STATE_OUT_OF_SERVICE )
            {
                    ret = checkRequestType( AtmBuf );
                    dptr->trace( " ret[%d]",ret );
                    if( ret != REQUEST_OUT_OF_SERVICE )
                    {
                    		dptr->trace( "Received Invaild Request from Switch..Expecting OUTOFSERVICE Message" );
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, CMDREJECT );
                            if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;
                                    break;
                            }
                    }
                    else
                            CurrState = STATE_MISC_DOWNLOAD;
                    composeSolicitedMessage( AtmBuf, READY );
                    if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                    {
                            //closeSocket();
                    		flag = false;
                            break;
                    }
            }
            else if ( CurrState == STATE_MISC_DOWNLOAD )
            {
                    //if( checkRequestType( AtmBuf ) != REQUEST_OUT_OF_SERVICE &&  checkRequestType( AtmBuf ) !=REQUEST_MISC_DOWNLOAD )
                    ret = checkRequestType( AtmBuf );

                    if( ret != REQUEST_MISC_DOWNLOAD )
                    {
                    		dptr->trace( "Received Invaild Request from Switch..Expecting OUTOFSERVICE/MISC DOWNLOAD Message" );
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, CMDREJECT );
                            if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;
                                    break;
                            }
                    }
                    else if ( checkRequestType( AtmBuf ) == REQUEST_MISC_DOWNLOAD )
                    {

                            CurrState = STATE_STATE_DOWNLOAD;
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, READY );
                            if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;	
                                    break;
                            }
                    }
            }
            else if ( CurrState == STATE_STATE_DOWNLOAD || checkRequestType( AtmBuf ) == REQUEST_STATE_DOWNLOAD )
            {
                    if( checkRequestType( AtmBuf ) != REQUEST_MISC_DOWNLOAD &&  checkRequestType( AtmBuf ) != REQUEST_STATE_DOWNLOAD )
                    {
                    		dptr->trace( "Received Invaild Request from Switch..Expecting MISC DOWNLOAD/STATE DOWNLOADMessage" );
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, CMDREJECT );
                            if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;
                                    break;
                            }
                    }
                    else if ( checkRequestType( AtmBuf ) == REQUEST_STATE_DOWNLOAD )
                            CurrState = STATE_SCR_DOWNLOAD;
                    memset( AtmBuf, 0, sizeof( AtmBuf ) );
                    composeSolicitedMessage( AtmBuf, READY );
                    if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                    {
                            //closeSocket();
                    		flag = false;
                            break;
                    }
            }
            else if ( CurrState == STATE_SCR_DOWNLOAD )
            {
                    if( checkRequestType( AtmBuf ) != REQUEST_SCR_DOWNLOAD && checkRequestType( AtmBuf ) != REQUEST_FIT_DOWNLOAD )
                    {
                    		dptr->trace( "Received Invaild Request from Switch..Expecting SCR DOWNLOAD/FIT DOWNLOAD Message" );
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, CMDREJECT );
                            if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;
                                    break;
                            }
                    }
                    else if ( checkRequestType( AtmBuf ) == REQUEST_FIT_DOWNLOAD )
                            CurrState = STATE_FIT_DOWNLOAD;
                    composeSolicitedMessage( AtmBuf, READY );
                    if( writeSocketBuf( AtmBuf, sockfd  ) < 0 )
                    {
                            //closeSocket();
                    		flag = false;
                            break;
                    }
            }
            else if ( CurrState == STATE_FIT_DOWNLOAD )
            {
                if( checkRequestType( AtmBuf ) != REQUEST_FIT_DOWNLOAD && checkRequestType( AtmBuf ) != REQUEST_KEY_DOWNLOAD )
                {
                	dptr->trace( "Received Invaild Request from Switch..Expecting FIT DOWNLOAD/KEY DOWNLOAD Message" );
                    memset( AtmBuf, 0, sizeof( AtmBuf ) );
                    composeSolicitedMessage( AtmBuf, CMDREJECT );
                    if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                    {
                            //closeSocket();	
                    		flag = false;
                            break;
                    }
                }
                else if ( checkRequestType( AtmBuf ) == REQUEST_KEY_DOWNLOAD )
                	CurrState = STATE_KEY_DOWNLOAD;
                //Added for go in service
                else if ( checkRequestType( AtmBuf ) == REQUEST_IN_SERVICE )
                    CurrState = STATE_IN_SERVICE;
                composeSolicitedMessage( AtmBuf, READY );
                if( writeSocketBuf( AtmBuf, sockfd  ) < 0 )
                {
                    //closeSocket();
                	flag = false;	
                    break;
                }
            }
            else if ( CurrState == STATE_KEY_DOWNLOAD )
            {
                    if( checkRequestType( AtmBuf ) != REQUEST_KEY_DOWNLOAD && checkRequestType( AtmBuf ) != REQUEST_CONFIG_DOWNLOAD )
                    {
                    		dptr->trace( "Received Invaild Request from Switch..Expecting KEY DOWNLOAD/CONFIG DOWNLOADMessage" );
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, CMDREJECT );
                            if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;
                                    break;
                            }
                    }
                    else if ( checkRequestType( AtmBuf ) == REQUEST_CONFIG_DOWNLOAD )
                            CurrState = STATE_CONFIG_DOWNLOAD;
                    composeSolicitedMessage( AtmBuf, READY );
                    if( writeSocketBuf( AtmBuf, sockfd  ) < 0 )
                    {
                            //closeSocket();
                    		flag = false;
                            break;
                    }
                    //FindETpk( );
                    //FindTpk( );
                    
            }
            else if ( CurrState == STATE_CONFIG_DOWNLOAD )
            {
                    if( checkRequestType( AtmBuf ) != REQUEST_CONFIG_DOWNLOAD && checkRequestType( AtmBuf ) != REQUEST_IN_SERVICE )
                    {
                    		dptr->trace( "Received Invaild Request from Switch..Expecting CONFIG DOWNLOAD/IN SERVICE Message" );
                            memset( AtmBuf, 0, sizeof( AtmBuf ) );
                            composeSolicitedMessage( AtmBuf, CMDREJECT );
                            if( writeSocketBuf( AtmBuf, sockfd) < 0 )
                            {
                                    //closeSocket();
                            		flag = false;
                                    break;
                            }
                    }
                    else if ( checkRequestType( AtmBuf ) == REQUEST_IN_SERVICE )
                            CurrState = STATE_IN_SERVICE;
                    composeSolicitedMessage( AtmBuf, READY );
                    if( writeSocketBuf( AtmBuf, sockfd ) < 0 )
                    {
                            //closeSocket();
                    		flag = false;
                            break;
                    }
            }
            if( CurrState == STATE_IN_SERVICE )
            {
            		dptr->trace( "In-Service State....Download Completed Successfully" );
                    break;
            }
    }
    if( !flag )
    	return -1;
    else
    	return 1;
}
int EzAtmSimulator :: checkRequestType( const char *AtmBuf )
{
    int RequestType = -1;
    char RequestId[ 5 ];
    char MsgBuf[ 1024 ];

    switch ( *AtmBuf )
    {
        case '3':
            memset( RequestId, 0, sizeof( RequestId ) );
            getToken( AtmBuf, RequestId, 4, 0x1c );
            dptr->trace("RequestId[%s]",RequestId );
            if( !strncmp( RequestId, "11", 2 ) )
                    RequestType = REQUEST_SCR_DOWNLOAD;
            else if ( !strncmp( RequestId, "12", 2 ) )
                    RequestType = REQUEST_STATE_DOWNLOAD;
            else if ( !strncmp( RequestId, "13", 2 ) )
                    RequestType = REQUEST_MISC_DOWNLOAD;
            else if ( !strncmp( RequestId, "15", 2 ) )
                    RequestType = REQUEST_FIT_DOWNLOAD;
            else if ( !strncmp( RequestId, "16", 2 ) )
                    RequestType = REQUEST_CONFIG_DOWNLOAD;
            else if ( !strncmp( RequestId, "2", 1 ) )
                    RequestType = REQUEST_OAR_REQUEST;
            else if ( !strncmp( RequestId, "32", 2 ) )
            {
                int j = 0;
                RequestType = REQUEST_KEY_DOWNLOAD;
                while( *AtmBuf )
                {
                    if( *AtmBuf == 0x1c )
                            j++;
                    if(j == 4)
                    {
                        strncpy( atmcfg.KeyDownloadMsg, AtmBuf,26 );
                        dptr->trace( "KeyDownloadMsg[%s]", atmcfg.KeyDownloadMsg );
                        break;
                    }
                    AtmBuf++;
                }
            }
        break;

        case '4':
                RequestType = REQUEST_FUNCTION_COMMAND;
                memset( MsgBuf, 0, sizeof( MsgBuf ) );

        break;

        case '1':
                RequestType = REQUEST_OPERATION_COMMAND;
                int i = 0;
                while( *AtmBuf )
                {
                        if( *AtmBuf == 0x1c )
                                i++;
                        if(i == 3)
                                break;
                        AtmBuf++;
                }
                AtmBuf++;
                if( i == 3 && *AtmBuf == '2')
                        RequestType = REQUEST_OUT_OF_SERVICE;
                else if( i == 3 && *AtmBuf == '1')
                {
                        RequestType = REQUEST_IN_SERVICE;
                        dptr->trace( "Go In Service Sent By The Switch ");
                }
        break;

    }
    return RequestType;
}
void EzAtmSimulator :: FindETpk( )
{
	//char sub[ 25 ];
    int i = 1 ;
    char *p;
    memset( sub, 0, sizeof( sub ) );
    char Temp[5];
    dptr->trace("DownLoaded Message:%s\n", atmcfg.KeyDownloadMsg );
    while( i <24  )
    {
            memset( Temp, 0, sizeof( Temp ));
            strncpy( Temp, atmcfg.KeyDownloadMsg + i, 3 );
            p=FIND_E_TPK1( Temp );
            strcat(sub,p);
            i = i+3;
    }
    strcpy( atmcfg.ETpk, sub );
    dptr->trace("ETpk:%s\n",atmcfg.ETpk);

}
char * EzAtmSimulator :: FIND_E_TPK1(char *temp)
{
        int r[24],i,n;
        //char substring[25];
        //char buf[25];
        memset( substring,0,sizeof( substring ) );
        memset( buf, 0, sizeof( buf ));
        if(!strcmp(temp, "000"))
        {
                sprintf(buf, "%s", "00");
                return buf;
        }
        n=atoi(temp);
        for(i=0;n!=0;i++)
        {
                r[i]=n%16;
                n=n/16;
        }
        i--;
        for(;i>=0;i--)
        {
        if(r[i]==10)
                sprintf(buf,"%c",'A');
        else if(r[i]==11)
                sprintf(buf,"%c",'B');
        else if(r[i]==12)
                sprintf(buf,"%c",'C');
        else if(r[i]==13)
                sprintf(buf,"%c",'D');
        else if(r[i]==14)
                sprintf(buf,"%c",'E');
        else if(r[i]==15)
        	sprintf(buf,"%c",'F');
        else
                sprintf(buf,"%d",r[i]);
        strcat( substring, buf);
        }
        if( strlen( substring ) == 1)
        {
                substring[1] = substring[0];
                substring[0] = '0';
        }
        dptr->trace("substring : %s\n",substring);
        return substring;
}
void EzAtmSimulator :: FindTpk( )
{
	
	Decrypt( atmcfg.Tmk, atmcfg.ETpk,atmcfg.Tpk );
	dptr->trace("TMk:%s\n",atmcfg.Tmk);
	dptr->trace("ETpk:%s\n",atmcfg.ETpk);
	dptr->trace("Tpk:%s\n",atmcfg.Tpk );
}
int EzAtmSimulator :: getTxnOpkey( int TxnCode, char *TxnOpkey )
{
	EzCfgUtil cfgutil;
	char opkeypath[ CFG_PATH_SIZE + 1 ], TxnStr[ 7 ],CfgParam[ CFG_VAL_SIZE +1 ];;
	
	memset( opkeypath, 0, sizeof( opkeypath ) );
	sprintf( opkeypath, "%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "ezsimulator.cfg"  );

	if( cfgutil.cfg_open( opkeypath ) < 0 )
	{
		dptr->trace( "Error in opening Opkey File [%s]....", opkeypath );
		return -1;
	}

	memset( TxnStr, 0, sizeof( TxnStr ) );
	sprintf( TxnStr, "%06d", TxnCode );
	memset( CfgParam, 0, sizeof( CfgParam ) );
	sprintf( CfgParam, "OPKEY#%s", TxnStr );

	if( cfgutil.cfg_search( CfgParam, TxnOpkey, 2 ) < 0 )
	{
		dptr->trace( "Error in Searching TxnCode[%s] in Opkey File [%s]", TxnStr, opkeypath );
		cfgutil.cfg_close();
		return -1;
	}
	cfgutil.cfg_close();
	return 1;
}

int EzAtmSimulator :: getPINBlock( char *chn, char *pin, char *pinblock )
{
	char clear_block[ 17 ], acc_block[ 17 ], clear_pinblock[ 17 ], tempStr[ 17 ];
    int offset;
    offset = 0;
    memset( clear_block, 0, sizeof( clear_block ) );
    sprintf( clear_block, "%02d%s", strlen( pin ), pin );
    offset = strlen( pin ) + 2;
    memset( clear_block + offset, 'F', 16 - offset );
    memset( acc_block, 0, sizeof( acc_block ) );
    memset( acc_block, '0', 4 );
    strncpy( acc_block + 4, chn + ( strlen( chn ) - 13 ), 12 );
    memset( clear_pinblock, 0, sizeof( clear_pinblock ) );
    for( int i = 0; i < 16; i++ )
            clear_pinblock[ i ] = int_to_char ( ( char_to_int( clear_block[ i ] ) ) ^ ( char_to_int( acc_block[ i ]  ) ));
	
    memset( tempStr, 0, sizeof( tempStr ) );
	dptr->trace( "Tpk[%s]", atmcfg.Tpk );
	dptr->trace("ClearPinBlock[%s]", clear_pinblock );
	Encrypt( atmcfg.Tpk, clear_pinblock, tempStr );
	/*for( int i = 0; i < strlen( tempStr ); i++ )
	{
		switch ( tempStr[ i ] )
		{
			case 'A' || 'a':
				pinblock[ i ] = ':';
				break;
			case 'B' || 'b':
				pinblock[ i ] = ';';
				break;
			case 'C' || 'c':
				pinblock[ i ] = '<';
				break;
			case 'D' || 'd':
				pinblock[ i ] = '=';
				break;
			case 'E' || 'e':
				pinblock[ i ] = '>';
				break;
			case 'F' || 'f':
				pinblock[ i ] = '?';
				break;
			default:
				pinblock[ i ] = tempStr[ i ];
		}
	}*/
	dptr->trace( "tempStr[%s]", tempStr );
	strcpy( pinblock, tempStr );
	return 1;
}
int EzAtmSimulator :: composeTxnReq( char *chn, char *PIN, int TxnCode, int Amount, char *AtmBuf )
{
	int offset = 0;
	char Track2Data[ 50 ], PINBlock[ 17 ],TxnOpkey[ 10 ];

	//Solicited or Unsolicited 1->Unsolicited 2->Solicited
	AtmBuf[ offset ] = '1';
	offset++;

	//Message Identifier
	AtmBuf[ offset ] = '1';
	offset++;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	//Luno
	strncpy( AtmBuf + offset, "001", 3 );
	offset += 3;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	//Top Of Form Flag 0->Not Printing the Transaction at Top of Form 1->Printing
	AtmBuf[ offset ] = '1';
	offset++;

	//Message Coordination No
	AtmBuf[ offset ] = '>';
	offset++;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	//Track2
	memset( Track2Data, 0, sizeof( Track2Data ) );
	sprintf( Track2Data, ";%s=501201", chn );
	strncpy( AtmBuf + offset, Track2Data, strlen( Track2Data ) );
	offset += strlen( Track2Data );

	AtmBuf[ offset ] = 0x1c;
	offset++;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	memset( TxnOpkey, 0, sizeof( TxnOpkey ) );
	if( getTxnOpkey( TxnCode, TxnOpkey ) < 0 )
		return -1;

	//Opkey Buffer
	sprintf( AtmBuf + offset, "%8s", TxnOpkey );
	offset += 8;

	AtmBuf[ offset ] = 0x1c;
	offset++;

	//Amount Buffer
	sprintf( AtmBuf + offset, "%012d", Amount );
	offset += 12;

	AtmBuf[ offset ] = 0x1c;
	offset++;
	FindETpk( );
	FindTpk( );
	//PinBuffer
	memset( PINBlock, 0, sizeof( PINBlock ) );
	getPINBlock( chn, PIN, PINBlock );

	strncpy( AtmBuf + offset, PINBlock, strlen( PINBlock ) );
	offset += strlen( PINBlock );

	AtmBuf[ offset ] = 0x1c;
	offset++;

	//General Purpose Buffer B
	/*if( strlen( GenBufferB ) )
	{
		strncpy( AtmBuf + offset, GenBufferB, strlen( GenBufferB ) );
		offset += strlen( GenBufferB );
	}

	AtmBuf[ offset ] = 0x1c;
	offset++;*/

	return offset;
}
int EzAtmSimulator :: composeSolicitedMessage( char *AtmBuf, int StatusId )
{
    int offset = 0;

    switch( StatusId )
    {
        case READY:
            sprintf( AtmBuf, "22%c001%c%c9", 0x1c,  0x1c, 0x1c );
            offset += strlen( AtmBuf );
        break;

        case CMDREJECT:
            sprintf( AtmBuf, "22%c001%c%cA", 0x1c, 0x1c, 0x1c );
            offset += strlen( AtmBuf );
        break;

        case JOURNAL_PRINTER_FAULT:
            sprintf( AtmBuf, "22%c001%c%c8%c2%c%c%c", 0x1c, 0x1c, 0x1c, 0x1c, 0x1, 0x0, 0xf0  );
            offset += strlen( AtmBuf );
        break;

        case CONSUMER_PRINTER_FAULT:
            sprintf( AtmBuf, "22%c001%c%c8%c2%c%c%c", 0x1c,  0x1c, 0x1c, 0x1c, 0x2, 0x20, 0x0  );
            offset += strlen( AtmBuf );
        break;

        case STATEMENT_PRINTER_FAULT:
            sprintf( AtmBuf, "22%c001%c%c8%c2%c%c%c", 0x1c, 0x1c, 0x1c, 0x1c, 0x4, 0x0, 0x0 );
            offset += strlen( AtmBuf );
        break;

        case PASSBOOK_PRINTER_FAULT:
        	sprintf( AtmBuf, "22%c001%c%c8%c2%c%c%c", 0x1c, 0x1c, 0x1c, 0x1c, 0x8, 0x0, 0x0 );
        	offset += strlen( AtmBuf );
        break;

        case DISPENSOR_FAULT:
            //sprintf( AtmBuf, "22%c%s%c%c%c8%c?", 0x1c, atmcfg.Luno, 0x1c, 0x1c, 0x1c,0x1c );
            sprintf( AtmBuf, "22%c001%c%c8%c?", 0x1c, 0x1c, 0x1c,0x1c );
            offset += strlen( AtmBuf );
            //Withdrawal Area Status
            //0->No Error
            //1->Withdrawal door open prior to dispense
            //2->Withdrawal door open during dispense
            //3->Sensors blocked before dispense
            //4->Sensors blocked before dispense and withdrawal door open during dispense
            //5->Sensors not blocked after dispense
            AtmBuf[ offset ] = atmcfg.WithdrawalAreaStatus;
            offset++;
            //DispensorErrorCode
            strncpy( AtmBuf + offset, atmcfg.DispErrCode, 2 );
            offset += 2;
            //PartialDispenseStatus
            //0->Good Dispense
            //1->Not Applicable
            //2->Bad Dispense Continuation Not Possible
            //3->Dispense is not Possible [No Money was Dispensed]
            //4->Denomination Error, After Redefining the Denomination
            //5->Good Partial Dispense, Continuation is Possible
            AtmBuf[ offset ] = atmcfg.PartialDispenseStatus;
            offset++;

            //No.of Bills Dispensed in Cass1
            //Cass No
            AtmBuf[ offset ] = '1';
            offset++;

            //Cass Denomination
            AtmBuf[ offset ] = atmcfg.Cass1DenomId;
            offset++;

            //No. of Bills Dispensed from Cass1
            //sprintf( AtmBuf + offset, "%08d", atmcfg.Cass1Dispensed );
            strncpy( AtmBuf + offset, atmcfg.Cass1Dispensed,7 );
            offset += 7;

            //No.of Bills Dispensed in Cass2
            //Cass No
            AtmBuf[ offset ] = '2';
            offset++;

            //Cass Denomination
            AtmBuf[ offset ] = atmcfg.Cass2DenomId;
            offset++;

            //No. of Bills Dispensed from Cass2
            strncpy( AtmBuf + offset, atmcfg.Cass2Dispensed,7 );
            offset += 7;

            //No.of Bills Dispensed in Cass3
            //Cass No
            AtmBuf[ offset ] = '3';
            offset++;

            //Cass Denomination
            AtmBuf[ offset ] = atmcfg.Cass3DenomId;
            offset++;

            //No. of Bills Dispensed from Cass3
            strncpy( AtmBuf + offset, atmcfg.Cass3Dispensed,7 );
            offset += 7;

            //No.of Bills Dispensed in Cass4
            //Cass No
            AtmBuf[ offset ] = '4';
            offset++;

            //Cass Denomination
            AtmBuf[ offset ] = atmcfg.Cass4DenomId;
            offset++;

            //No. of Bills Dispensed from Cass1
            strncpy( AtmBuf + offset, atmcfg.Cass4Dispensed,7 );
            offset += 7;

            break;
        UNCERTAIN_DISPENSE:
            sprintf( AtmBuf, "22%c001%c%c8%c@04", 0x1c, 0x1c, 0x1c, 0x1c );
            offset += strlen( AtmBuf );
            break;

        default:
        	dptr->trace( " UnHandled Status Id[%d],", StatusId );
            break;

    }
    return offset;
}
char EzAtmSimulator :: int_to_char( int val )
{
        if( val < 10 )
                return( 48 + val );
        else
                return( 55 + val );
}
int EzAtmSimulator :: char_to_int( char hexval )
{
        if( isdigit( hexval ) )
                return ( hexval - 48 );
        else
                return ( hexval - 55 );
}
void EzAtmSimulator :: getToken( const char *FieldStr, char *TokenStr, int TokenNo, char Token )
{
    for( int i = 0, j = 0, cnt = 0; i < strlen( FieldStr ); i++ )
    {
        if( FieldStr[ i ] == Token )
                cnt++;
        else if ( cnt == TokenNo )
                break;
        else if ( cnt + 1 == TokenNo )
        {
                TokenStr[ j ] = FieldStr[ i ];
                j++;
        }
    }
}

