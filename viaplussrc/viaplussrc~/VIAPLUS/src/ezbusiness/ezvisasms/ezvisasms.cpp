#include <ezbusiness/ezvisasms.h>

EzVisaSMS :: EzVisaSMS()
{
}

EzVisaSMS :: ~EzVisaSMS()
{
}

void EzVisaSMS :: InitEzVisaSMS( const char *TaskName )
{
	char logpath[ LOG_PATH_SIZE + 1 ], BitMapFile[ BITMAP_FILE_SIZE + 1 ];
	char cfgpath[ CFG_PATH_SIZE + 1 ], cfgval[ CFG_VAL_SIZE + 1 ];
	EzCfgUtil cfgutil;

	memset( logpath, 0, sizeof( logpath ) );
	sprintf( logpath, "%s/%s/%s.log", getenv( "EZDIR_HOME" ), "log", TaskName );

	if( openDebug( logpath, TaskName ) < 0 )
		exit( 0 );

	trace( "^^^^^^^^^^^%s Started Running^^^^^^^^^^^^^", TaskName );

	if( InitEzTaskUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzTaskUtil");
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName );
		closeDebug();
		exit( 0 );
	}

	if( InitEzChannelUtil( this ) < 0 )
	{
		trace( "Error in Initializing EzChannelUtil" );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName );
		closeDebug();
		TaskExit();
	}

	if( CreateChannel( TaskName ) < 0 )
	{
		trace( "Error in Creating %s Channel", TaskName );
		trace( "^^^^^^^^^^^%s Ended Abnormally^^^^^^^^^^^^^", TaskName );
		closeDebug();
		TaskExit();
	}

	memset( BitMapFile, 0, sizeof( BitMapFile ) );
	sprintf( BitMapFile, "%s/%s/%s/%s", getenv( "EZDIR_HOME" ), "cfg", "iso8583", "EzVisaSMSBitMap.cfg" );

	if( initEzISO8583Util( BitMapFile, this ) < 0 )
	{
		trace( "Error in Initializing EzISO8583Util" );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		closeDebug();
		TaskExit();
	}


	memset( cfgpath, 0, sizeof( cfgpath ) );
	sprintf( cfgpath, "%s/%s/%s/%s/%s.cfg", getenv( "EZDIR_HOME" ), "cfg", "network", "visa", TaskName );

	if( cfgutil.cfg_open( cfgpath ) < 0 )
	{
		trace( "Error in Opening File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		closeDebug();
		TaskExit();
	}

	memset( &visaPvtData, 0, sizeof( struct VisaPvtDataInfo ) );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SRC_STATIONID", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching SRC_STATIONID from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( visaPvtData.SrcStationId, 0, sizeof( visaPvtData.SrcStationId ) );
	strcpy( visaPvtData.SrcStationId, cfgval );

	trace( DEBUG_TEST, "SrcStationId[%s]", visaPvtData.SrcStationId );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "DEST_STATIONID", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching DEST_STATIONID from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( visaPvtData.DestStationId, 0, sizeof( visaPvtData.DestStationId ) );
	strcpy( visaPvtData.DestStationId, cfgval );

	trace( DEBUG_TEST, "DestStationId[%s]", visaPvtData.DestStationId );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "NETWORKCODE", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching NETWORKCODE from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( visaPvtData.NetworkCode, 0, sizeof( visaPvtData.NetworkCode ) );
	strcpy( visaPvtData.NetworkCode, cfgval );

	trace( DEBUG_TEST, "NetworkCode[%s]", visaPvtData.NetworkCode );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "INSTID", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching INSTID from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( visaPvtData.InstId, 0, sizeof( visaPvtData.InstId ) );
	strcpy( visaPvtData.InstId, cfgval );

	trace( DEBUG_TEST, "InstId[%s]", visaPvtData.InstId );


	memset( &fld53info, 0, sizeof( struct Fld53Info ) );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "SECURITYFORMAT", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching SECURITYFORMAT from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( fld53info.SecurityFormat, 0, sizeof( fld53info.SecurityFormat ) );
	strcpy( fld53info.SecurityFormat, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ALGORITHMID", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ALGORITHMID from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( fld53info.AlgorithmId, 0, sizeof( fld53info.AlgorithmId ) );
	strcpy( fld53info.AlgorithmId, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PINBLOCKFORMAT", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching PINBLOCKFORMAT from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( fld53info.PinBlockFormat, 0, sizeof( fld53info.PinBlockFormat ) );
	strcpy( fld53info.PinBlockFormat, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "ZONEKEYINDEX", cfgval, 2 ) < 0 )
	{
		trace( "Error in Searching ZONEKEYINDEX from File[%s]", cfgpath );
		trace( "~~~~~~~~~~~~~~~~~~%s Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~", TaskName );
		cfgutil.cfg_close();
		closeDebug();
		TaskExit();
	}

	memset( fld53info.ZoneKeyIndex, 0, sizeof( fld53info.ZoneKeyIndex ) );
	strcpy( fld53info.ZoneKeyIndex, cfgval );

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "PINDATATYPE", cfgval, 2 ) < 0 )
	{
		memset( fld53info.PINDataType, 0, sizeof( fld53info.PINDataType ) );
		strcpy( fld53info.PINDataType, "NA" );
	}
	else
	{
		memset( fld53info.PINDataType, 0, sizeof( fld53info.PINDataType ) );
		strcpy( fld53info.PINDataType, cfgval );
	}

	memset( cfgval, 0, sizeof( cfgval ) );
	if( cfgutil.cfg_search( "VISARESERVED", cfgval, 2 ) < 0 )
	{
		memset( fld53info.VisaReserved, 0, sizeof( fld53info.VisaReserved ) );
		strcpy( fld53info.VisaReserved, "NA" );
	}
	else
	{
		memset( fld53info.VisaReserved, 0, sizeof( fld53info.VisaReserved ) );
		strcpy( fld53info.VisaReserved, cfgval );
	}

	cfgutil.cfg_close();

	if( initNetworkUtil( this ) < 0 )
        {
                trace( "Error in Initializing NetworkUtil..." );
                trace( "~~~~~~~~~~~~~~~~~~EzHost8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
                closeDebug();
                TaskExit();
        }

        if( initEchoUtil( this ) < 0 )
        {
                trace( "Error in Initializing EchoUtil...." );
                trace( "~~~~~~~~~~~~~~~~~~EzHost8583 Ended Abnormally~~~~~~~~~~~~~~~~~~~~~~~~~~");
                closeDebug();
                TaskExit();
        }

	initFmtUtil( this );

	TaskInit();
	initEzSigUtil( this );
}

void EzVisaSMS :: getToken( const char *FieldStr, char *TokenStr, char Token, int TokenNo )
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

int EzVisaSMS :: decomposeMsgHeader( unsigned char *InBuf, char *ReasonCode )
{
	int offset = 0;
	char sTemp[ 100 ];
	unsigned char uCh, uTemp[ 100 ];
	int MsgLen;

	trace( DEBUG_NORMAL, "Decomposing Visa SMS Header....." );

	// Header Length
	uCh = InBuf[ offset ];
	trace( DEBUG_NORMAL, "[HEADER][#1][IN][Length]<%x>", uCh );
	offset += 1;

	if( uCh >= 26 )
	{
		// Header Flag and Format
		uCh = InBuf[ offset ];
		trace( DEBUG_NORMAL, "[HEADER][#2][IN][Header Flag & Format]<%x>", uCh );
		offset += 1;

		// Text Format
		uCh = InBuf[ offset ];
		trace( DEBUG_NORMAL, "[HEADER][#3][IN][Text Format]<%x>", uCh );
		offset += 1;

		// Total Message Length
		memcpy( &MsgLen, InBuf + offset, 2 );
		MsgLen = htons( MsgLen );
		trace( DEBUG_NORMAL, "[HEADER][#4][IN][Total MsgLen]<%d>", MsgLen );
		offset += 2;

		// Destination Station Id
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( uTemp, InBuf + offset, 3 );
		offset += 3;
		memset( sTemp, 0, sizeof( sTemp ) );
		this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
		trace( DEBUG_NORMAL, "[HEADER][#5][IN][Destination StationId]<%s>", sTemp );

		// Source Station Id
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( uTemp, InBuf + offset, 3 );
		offset += 3;
		memset( sTemp, 0, sizeof( sTemp ) );
		this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
		trace( DEBUG_NORMAL, "[HEADER][#6][IN][Source StationId]<%s>", sTemp );

		// Round Trip Control Information
		uCh = InBuf[ offset ];
		trace( DEBUG_NORMAL, "[HEADER][#7][IN][Round Trip Control Information]<%x>", uCh );
		offset += 1;

		// Base I Flags
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( uTemp, InBuf + offset, 2 );
		offset += 2;
		memset( sTemp, 0, sizeof( sTemp ) );
		this->bcd_to_ascii( ( char * ) uTemp, sTemp, 4 );
		trace( DEBUG_NORMAL, "[HEADER][#8][IN][Base I Flags]<%s>", sTemp );

		// Message Status Flags
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( uTemp, InBuf + offset, 3 );
		offset += 3;
		memset( sTemp, 0, sizeof( sTemp ) );
		this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
		trace( DEBUG_NORMAL, "[HEADER][#9][IN][Message Status Flags]<%s>", sTemp );

		// Batch Number
		uCh = InBuf[ offset ];
		trace( DEBUG_NORMAL, "[HEADER][#10][IN][Batch Number]<%x>", uCh );
		offset += 1;

		// Reserved
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( uTemp, InBuf + offset, 3 );
		offset += 3;
		memset( sTemp, 0, sizeof( sTemp ) );
		this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
		trace( DEBUG_NORMAL, "[HEADER][#11][IN][Reserved]<%s>", sTemp );

		// User Information
		uCh = InBuf[ offset ];
		trace( DEBUG_NORMAL, "[HEADER][#12][IN][User Information]<%x>", uCh );
		offset += 1;

		// BitMap
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( uTemp, InBuf + offset, 2 );
		offset += 2;
		memset( sTemp, 0, sizeof( sTemp ) );
		this->bcd_to_ascii( ( char * ) uTemp, sTemp, 4 );
		trace( DEBUG_NORMAL, "[HEADER][#13][IN][BitMap]<%s>", sTemp );

		if( IsBitSet( uTemp, 0 ) )
		{
			//Reason Code
			memset( uTemp, 0, sizeof( uTemp ) );
			memcpy( uTemp, InBuf + offset, 2 );
			offset += 2;
			memset( sTemp, 0, sizeof( sTemp ) );
			this->bcd_to_ascii( ( char * ) uTemp, sTemp, 4 );
			trace( DEBUG_NORMAL, "[HEADER][#13.1][IN][Reject Reason Code]<%s>", sTemp );
			strcpy( ReasonCode, sTemp );
		}

		// Header Length for Normal Header
		uCh = InBuf[ offset ];
		trace( DEBUG_NORMAL, "[HEADER][#1][IN][Length]<%x>", uCh );
		offset += 1;

	}

	// Header Flag and Format
	uCh = InBuf[ offset ];
	trace( DEBUG_NORMAL, "[HEADER][#2][IN][Header Flag & Format]<%x>", uCh );
	offset += 1;

	// Text Format
	uCh = InBuf[ offset ];
	trace( DEBUG_NORMAL, "[HEADER][#3][IN][Text Format]<%x>", uCh );
	offset += 1;

	// Total Message Length
	memcpy( &MsgLen, InBuf + offset, 2 );
	MsgLen = htons( MsgLen );
	trace( DEBUG_NORMAL, "[HEADER][#4][IN][Total MsgLen]<%d>", MsgLen );
	offset += 2;


	// Destination Station Id
	memset( uTemp, 0, sizeof( uTemp ) );
	memcpy( uTemp, InBuf + offset, 3 );
	offset += 3;
	memset( sTemp, 0, sizeof( sTemp ) );
	this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
	trace( DEBUG_NORMAL, "[HEADER][#5][IN][Destination StationId]<%s>", sTemp );

	// Source Station Id
	memset( uTemp, 0, sizeof( uTemp ) );
	memcpy( uTemp, InBuf + offset, 3 );
	offset += 3;
	memset( sTemp, 0, sizeof( sTemp ) );
	this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
	trace( DEBUG_NORMAL, "[HEADER][#6][IN][Source StationId]<%s>", sTemp );

	// Round Trip Control Information
	uCh = InBuf[ offset ];
	trace( DEBUG_NORMAL, "[HEADER][#7][IN][Round Trip Control Information]<%x>", uCh );
	offset += 1;

	// Base I Flags
	memset( uTemp, 0, sizeof( uTemp ) );
	memcpy( uTemp, InBuf + offset, 2 );
	offset += 2;
	memset( sTemp, 0, sizeof( sTemp ) );
	this->bcd_to_ascii( ( char * ) uTemp, sTemp, 4 );
	trace( DEBUG_NORMAL, "[HEADER][#8][IN][Base I Flags]<%s>", sTemp );

	// Message Status Flags
	memset( uTemp, 0, sizeof( uTemp ) );
	memcpy( uTemp, InBuf + offset, 3 );
	offset += 3;
	memset( sTemp, 0, sizeof( sTemp ) );
	this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
	trace( DEBUG_NORMAL, "[HEADER][#9][IN][Message Status Flags]<%s>", sTemp );

	// Batch Number
	uCh = InBuf[ offset ];
	trace( DEBUG_NORMAL, "[HEADER][#10][IN][Batch Number]<%x>", uCh );
	offset += 1;

	// Reserved
	memset( uTemp, 0, sizeof( uTemp ) );
	memcpy( uTemp, InBuf + offset, 3 );
	offset += 3;
	memset( sTemp, 0, sizeof( sTemp ) );
	this->bcd_to_ascii( ( char * ) uTemp, sTemp, 6 );
	trace( DEBUG_NORMAL, "[HEADER][#11][IN][Reserved]<%s>", sTemp );

	// User Information
	uCh = InBuf[ offset ];
	trace( DEBUG_NORMAL, "[HEADER][#12][IN][User Information]<%x>", uCh );
	offset += 1;

	return offset;

}

int EzVisaSMS :: composeMsgHeader( unsigned char *BitMap, unsigned char *MsgHeader, int MsgLen )
{
	int offset = 0, len = 0, msglenoffset;
	char sTemp[ 100 ];
	unsigned char uTemp[ 100 ];

	trace( DEBUG_NORMAL, "<Composing VISA Message Header....>" );

	//Header Length
	MsgHeader[ offset ] = 0x16;
	trace( DEBUG_NORMAL, "[HEADER][#1][Length]<%x>", MsgHeader[ offset ] );
	offset += 1;

	// Header Flag and Format
	MsgHeader[ offset ] = 0x01;
	trace( DEBUG_NORMAL, "[HEADER][#2][Header Flag & Format]<%x>", MsgHeader[ offset ] );
	offset += 1;

	// Text Format
	if( IsBitSet( BitMap, 61 ) || IsBitSet( BitMap, 62 ) )
	{
		MsgHeader[ offset ] = 0x02;
		trace( DEBUG_NORMAL, "[HEADER][#3][Text Format]<%x>", MsgHeader[ offset ] );
	}
	else
	{
		MsgHeader[ offset ] = 0x01;
		trace( DEBUG_NORMAL, "[HEADER][#3][Text Format]<%x>", MsgHeader[ offset ] );
	}
	offset += 1;

	// Total Message Length
	msglenoffset = offset;
	offset += 2;

	// Destination Station ID
	memset( sTemp, 0, sizeof( sTemp ) );
	strcpy( sTemp, visaPvtData.DestStationId );
	memset( uTemp, 0, sizeof( uTemp ) );
	ascii_to_bcd( sTemp, ( char * )uTemp, 3 );
	memcpy( MsgHeader + offset, uTemp, 3 );
	offset += 3;

	// Source Station ID
	memset( sTemp, 0, sizeof( sTemp ) );
	strcpy( sTemp, visaPvtData.SrcStationId );
	memset( uTemp, 0, sizeof( uTemp ) );
	ascii_to_bcd( sTemp, ( char * ) uTemp, 3 );
	memcpy( MsgHeader + offset, uTemp, 3 );
	offset += 3;

	// Round Trip Control Information
	MsgHeader[ offset ] = 0x01;
	trace( DEBUG_NORMAL, "[HEADER][#3][Text Format]<%x>", MsgHeader[ offset ] );
	offset += 1;

	// Base I Flags
	memset( sTemp, 0, sizeof( sTemp ) );
	strcpy( sTemp, "0000" );
	memset( uTemp, 0, sizeof( uTemp ) );
	ascii_to_bcd( sTemp, ( char * ) uTemp, 2 );
	memcpy( MsgHeader + offset, uTemp, 2 );
	offset += 2;

	// Message Status Flag
	memset( sTemp, 0, sizeof( sTemp ) );
	strcpy( sTemp, "400000" );
	memset( uTemp, 0, sizeof( uTemp ) );
	ascii_to_bcd( sTemp, ( char * ) uTemp, 3 );
	memcpy( MsgHeader + offset, uTemp, 3 );
	offset += 3;

	// Batch Number
	MsgHeader[ offset ] = 0x00;
	trace( DEBUG_NORMAL, "[HEADER][#3][Text Format]<%x>", MsgHeader[ offset ] );
	offset += 1;

	// Reserved
	memset( sTemp, 0, sizeof( sTemp ) );
	strcpy( sTemp, "010000" );
	memset( uTemp, 0, sizeof( uTemp ) );
	ascii_to_bcd( sTemp, ( char * ) uTemp, 3 );
	memcpy( MsgHeader + offset, uTemp, 3 );
	offset += 3;

	// User Information
	MsgHeader[ offset ] = 0x00;
	trace( DEBUG_NORMAL, "[HEADER][#3][Text Format]<%x>", MsgHeader[ offset ] );
	offset += 1;

	len = MsgLen + offset;
	len = htons( len );
	memcpy( MsgHeader + msglenoffset, &len, 2 );
	trace( DEBUG_NORMAL, "[HEADER][#4][Total Message Length]<%d>", MsgLen + offset );
	return offset;
}

int EzVisaSMS :: composeField62( struct EzTxnMsg *txnmsg, unsigned char *fld62Data )
{
	int uLen = 0;
	unsigned char BitMap62[ 9 ];
	char txnStr[ 50 ], uTemp[ 50 ];

	if( txnmsg->MsgType == EZLINK_TXN_TxnRequest )
	{
		//Moving 1 byte for Length
		uLen += 1;
		//8 Bytes CPS BitMap
		memset( BitMap62, 0, sizeof( BitMap62 ) );

		//First Bit ON for Authorization Character Indicator[ACI]
		SetBitOn( BitMap62, 1 );
		memcpy( fld62Data + uLen, BitMap62, 8 );
		uLen += 8;

		//ACI should be 'Y" for Acquirer
		memset( fld62Data + uLen, ascii_to_ebcdic( 'Y' ), 1 );
		uLen += 1;

		// Length
		fld62Data[ 0 ] = uLen;
		uLen += 1;
	}
	else if ( txnmsg->MsgType == EZLINK_TXN_ReversalAdviceRequest || txnmsg->MsgType == EZLINK_TXN_TxnAdviceRequest )
	{
		memset( txnStr, 0, sizeof( txnStr ) );
		getToken( txnmsg->RsvFld6, txnStr, '^', 1 );

		if( !strcmp( txnStr, "E" ) )
		{
			//Moving 1 byte for Length
			uLen += 1;

			//8 Bytes CPS BitMap
			memset( BitMap62, 0, sizeof( BitMap62 ) );

			//First Bit ON for Authorization Character Indicator[ACI]
			SetBitOn( BitMap62, 1 );

			//Second Bit ON for Transaction Identifier
			SetBitOn( BitMap62, 2 );

			memcpy( fld62Data + uLen, BitMap62, 8 );
			uLen += 8;

			memset( fld62Data + uLen, ascii_to_ebcdic( txnStr[ 0 ] ), 1 );
			uLen += 1;

			memset( txnStr, 0, sizeof( txnStr ) );
			getToken( txnmsg->RsvFld6, txnStr, '^', 2 );

			memset( uTemp, 0, sizeof( uTemp ) );
			ascii_to_bcd( txnStr, uTemp, 16 );

			memcpy( fld62Data + uLen, uTemp, 8 );
			uLen += 8;

			//Length
			fld62Data[ 0 ] = uLen - 1;

		}
		else
		{
			//Moving 1 byte for Length
			uLen += 1;

			//8 Bytes CPS BitMap
			memset( BitMap62, 0, sizeof( BitMap62 ) );

			//First Bit ON for Authorization Character Indicator[ACI]
			SetBitOn( BitMap62, 1 );
			memcpy( fld62Data + uLen, BitMap62, 8 );
			uLen += 8;

			//ACI should be 'Y" for Acquirer
			memset( fld62Data + uLen, ascii_to_ebcdic( txnStr[ 0 ] ), 1 );
			uLen += 1;

			// Length
			fld62Data[ 0 ] = uLen - 1;

		}
	}
	else
	{
		//Moving 1 byte for Length
		uLen += 1;

		//8 Bytes CPS BitMap
		memset( BitMap62, 0, sizeof( BitMap62 ) );

		//First Bit ON for Authorization Character Indicator[ACI]
		SetBitOn( BitMap62, 1 );
		memcpy( fld62Data + uLen, BitMap62, 8 );
		uLen += 8;

		//ACI should be 'Y" for Acquirer
		memset( fld62Data + uLen, ascii_to_ebcdic( 'Y' ), 1 );
		uLen += 1;

		// Length
		fld62Data[ 0 ] = uLen - 1;

	}
	return uLen;
}

void EzVisaSMS :: populateNewRequest( struct EzTxnMsg *txnmsg )
{
	memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
	strcpy( txnmsg->OrgPort, GetLastSenderChannelName() );
	memset( txnmsg->SrcPort, 0, sizeof( txnmsg->SrcPort ) );
	strcpy( txnmsg->SrcPort, GetLastSenderChannelName() );
	memset( txnmsg->SrcChannel, 0, sizeof( txnmsg->SrcChannel ) );
	strcpy( txnmsg->SrcChannel, GetSourceChannelName() );
	memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
	strcpy( txnmsg->OrgChannel, GetSourceChannelName() );
	if( txnmsg->MerchantType == 6011 )
	{
		memset( txnmsg->DeviceType, 0, sizeof( txnmsg->DeviceType ) );
		strcpy( txnmsg->DeviceType, "ATM" );
	}
	else
	{
		memset( txnmsg->DeviceType, 0, sizeof( txnmsg->DeviceType ) );
		strcpy( txnmsg->DeviceType, "POS" );
	}
	memset( txnmsg->AcquirerInst, 0, sizeof( txnmsg->AcquirerInst ) );
	strcpy( txnmsg->AcquirerInst, visaPvtData.InstId );
}

int EzVisaSMS :: composeField63( struct EzTxnMsg *txnmsg, unsigned char *fld63Data )
{
	unsigned char BitMap63[ 4 ];
	int uLen = 0;
	char sTemp[ 100 ], uTemp[ 100 ];

	//Length
	uLen += 1;

	memset( BitMap63, 0, sizeof( BitMap63 ) );

	//Set First Bit ON->Network Identification Code
	SetBitOn( BitMap63, 1 );

	if( txnmsg->MsgType == EZLINK_TXN_ReversalAdviceRequest || txnmsg->MsgType == EZLINK_TXN_TxnAdviceRequest )
	{
		//Set the 3rd Bit Message Reason Code ON
		SetBitOn( BitMap63, 3 );
	}

	memcpy( fld63Data + uLen, BitMap63, 3 );
	uLen += 3;

	if( txnmsg->MsgType == EZLINK_TXN_ReversalAdviceRequest || txnmsg->MsgType == EZLINK_TXN_TxnAdviceRequest )
	{
		// Network Identification Code
		memset( sTemp, 0, sizeof( sTemp ) );
		getToken( txnmsg->RsvFld6, sTemp, '^', 4 );

		if( !strlen( sTemp ) )
		{
			if( !strcmp( txnmsg->CardProduct, "VISA" ) )
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strcpy( sTemp, "0002" );
			}
			else if( !strcmp( txnmsg->CardProduct, "PLUS" ) )
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strcpy( sTemp, "0004" );
			}
			else
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strcpy( sTemp, "0000" );
			}
		}

		memset( uTemp, 0, sizeof( uTemp ) );
		ascii_to_bcd( sTemp, uTemp, 4 );
		memcpy( fld63Data + uLen, uTemp, 2 );
		uLen += 2;

		//Reason Code
		memset( sTemp, 0, sizeof( sTemp ) );
		//getVISASMSReasonCode( txnmsg->RespCode, sTemp );

		memset( uTemp, 0, sizeof( uTemp ) );
		ascii_to_bcd( sTemp, uTemp, 4 );
		memcpy( fld63Data + uLen, uTemp, 2 );
		uLen += 2;
	}
	else if ( txnmsg->MsgType == EZLINK_TXN_NtwkRequest || txnmsg->MsgType == EZLINK_TXN_NtwkResponse )
	{
		// Network Identification Code
		memset( sTemp, 0, sizeof( sTemp ) );
		strcpy( sTemp, visaPvtData.NetworkCode );
		ascii_to_bcd( sTemp, uTemp, 4 );
		memset( uTemp, 0, sizeof( uTemp ) );
		memcpy( fld63Data + uLen, uTemp, 2 );
		uLen += 2;
	}
	else
	{
		// Network Identification Code
		memset( sTemp, 0, sizeof( sTemp ) );
		getToken( txnmsg->RsvFld6, sTemp, '^', 4 );

		if( !strlen( sTemp ) )
		{
			if( !strcmp( txnmsg->CardProduct, "VISA" ) )
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strcpy( sTemp, "0002" );
			}
			else if( !strcmp( txnmsg->CardProduct, "PLUS" ) )
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strcpy( sTemp, "0004" );
			}
			else
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strcpy( sTemp, "0000" );
			}
		}

		memset( uTemp, 0, sizeof( uTemp ) );
		ascii_to_bcd( sTemp, uTemp, 4 );
		memcpy( fld63Data + uLen, uTemp, 2 );
		uLen += 2;
	}
	fld63Data[ 0 ] = uLen -1;
	return uLen;
}

int EzVisaSMS :: ComposeISOMessage( struct EzTxnMsg *txnmsg, unsigned char *IsoBuffer )
{
	unsigned char Offset, StmtBuf[ STMT_BUF_SIZE + 1 ];
	unsigned char BitMap[ 33 ], MsgHeader[ 150 ], fld62Data[ 100 ], fld63Data[ 100 ] ;
	char OutBuffer[ VISA_BUFFER_SIZE + 1 ], *BufOffset, *OutBuf, sTemp[ 150 ], uTemp[ 150 ], fld53Data[ 100 ];
	char *endptr;
	int len;


	memset( OutBuffer, 0, sizeof( OutBuffer ) );
	OutBuf = OutBuffer;
	BufOffset = OutBuffer;

	if( txnmsg->RespCode == EZLINK_RC_PartialDispense )
	{
		//This will be treated as advice message for Credit Adjustment;
		memset( sTemp, 0, sizeof( sTemp ) );
		sprintf( sTemp, "%0.2lf", strtod( txnmsg->Amount, &endptr ) / 100 - strtod( txnmsg->DispAmount, &endptr ) / 100 );
		memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
		strcpy( txnmsg->Amount, sTemp );
		txnmsg->MsgType = EZLINK_TXN_TxnAdviceRequest;
	}

	//MsgType Indicator
	OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->MsgType, ITOBCD, 4, 0 );

	memset( BitMap, 0, sizeof( BitMap ) );

	if( LoadBitMap( BitMap, txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode ) < 0 )
	{
		trace( "Error in Loading BitMap for [m%d/p%6ld/r%d]", txnmsg->MsgType, txnmsg->TxnCode, txnmsg->RespCode );
		return -1;
	}

	if( txnmsg->MsgType == 210 && txnmsg->RespCode == 0 )
		SetBitOn( BitMap, 54 );

	OutBuf += fmt_out( ( char * ) OutBuf, BitMap, MOVE, 8, 1 );

	if( IsBitSet( BitMap, 1 ) )
		OutBuf += fmt_out( ( char * ) OutBuf, BitMap + 8, MOVE, 8, 1 );

	for( int bitno = 1; bitno <= 128; bitno++ )
	{
		if( !IsBitSet( BitMap, bitno ) )
			continue;

		if( bitno > 64 )
		{
			if( !IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( bitno )
		{

		case 1:
			// Seconday Bit Map
			break;

		case 2:

			//CHN
			len = strlen( txnmsg->chn );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->chn, ATOBCD, len, bitno );
			break ;

		case 3:

			//Processing Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->TxnCode, ITOBCD, 6, bitno );
			break ;

		case 4:

			//Transaction Amount
			char TempAmount[13], TempAmount1[13];
			int Amount;

			memset( TempAmount, 0, sizeof( TempAmount ) );
			if( strlen( txnmsg->Amount ) <= 0 )
				strncpy( TempAmount, "000000000000", 12 );
			else
			{
				memset( TempAmount1, 0, sizeof( TempAmount1 ) );
				for( int i = 0, j = 0; i <= strlen( txnmsg->Amount ); i++ )
				{
					if( txnmsg->Amount[i] != '.' )
					{
						TempAmount1[ j ] = txnmsg->Amount[ i ];
						j++;
					}
				}
				memset( TempAmount, 0, sizeof( TempAmount ) );
				memset( TempAmount, '0', 12 - strlen( TempAmount1 ) );
				strcpy( TempAmount + 12 - strlen( TempAmount1 ), TempAmount1 );
			}
			OutBuf += fmt_out( ( char * ) OutBuf, TempAmount, ATOBCD, 12, bitno );
			break ;

		case 5:

			//Settlement Amount
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->SettAmount, ATOBCD, 12, bitno );
			break;

		case 6:

			//Billing Amount
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->BillingAmount, ATOBCD, 6, bitno );
			break ;

		case 7:


			// Transaction Date and Time ( field format MMDDhhmmss )
			memset( sTemp, 0, sizeof( sTemp ) );
			sprintf( sTemp, "%06d", txnmsg->TranDate );
			memset( fld53Data, 0, sizeof( fld53Data ) );
			strncpy( fld53Data, sTemp + 2, 2 );
			strncpy( fld53Data + 2, sTemp, 2 );
			OutBuf += fmt_out( ( char * ) OutBuf, fld53Data, ATOBCD, 4, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->TranTime, LTOBCD, 6, bitno );
			break ;

		case 8:
			break ;

		case 9:
			break ;

		case 10:
			break ;

		case 11:

			//System Trace Audit Number
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->TraceNo, LTOBCD, 6, bitno );
			break ;

		case 12:

			//Local Transaction Time ( field format hhmmss )
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->LocalTime, LTOBCD, 6, bitno );
			break ;

		case 13:

			//Local Transaction Date ( field format MMDD )
			memset( sTemp, 0, sizeof( sTemp ) );
			sprintf( sTemp, "%06d", txnmsg->LocalDate );
			memset( fld53Data, 0, sizeof( fld53Data ) );
			strncpy( fld53Data, sTemp + 2, 2 );
			strncpy( fld53Data + 2, sTemp, 2 );
			OutBuf += fmt_out( ( char * ) OutBuf, fld53Data, ATOBCD, 4, bitno );
			break ;

		case 14:

			//Card Expiration Date ( field format YYMM )
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->ExpiryDate, LTOBCD, 4, bitno );
			break ;

		case 15:

			// Settlement Date ( field format MMDD )
			memset( sTemp, 0, sizeof( sTemp ) );
			sprintf( sTemp, "%06d", txnmsg->BusinessDate );
			memset( fld53Data, 0, sizeof( fld53Data ) );
			strncpy( fld53Data, sTemp + 2, 2 );
			strncpy( fld53Data + 2, sTemp, 2 );
			OutBuf += fmt_out( ( char * ) OutBuf, fld53Data, ATOBCD, 4, bitno );
			break ;

		case 16:

			//Card Expiration Date ( field format YYMM )
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->IssConvDate, LTOBCD, 4, bitno );
			break ;

		case 17:

			// Capture Date ( field format YYMM )
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->CaptureDate, LTOBCD, 4, bitno );
			break ;

		case 18:

			//Merchant Type
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->MerchantType, STOBCD, 4, bitno );
			break ;

		case 19:

			//Acquiring Institution Country Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->AcqCurrencyCode, STOBCD, 3, bitno );
			break ;

		case 20:

			//Primary Account Number (PAN) Country Code( Issuer )
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->IssCountryCode, ITOBCD, 3, bitno );
			break ;

		case 21:

			//Forwarding Institution Country Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->FwdCountryCode, ITOBCD, 3, bitno );
			break ;

		case 22:

			//Point of Service Entry Mode

			// PAN/Date Entry Mode
			// 90 -> Indicates Entire Track2 will be sent & reliable
			// 02 -> Indicates unreliable Track2 information

			memset( sTemp, 0, sizeof( sTemp ) );
			if( IsBitSet( BitMap, 35 ) )
				strncpy( sTemp, "90", 2 );
			else
				strncpy( sTemp, "02", 2 );

			// PIN Entry Capability
			if( IsBitSet( BitMap, 52 ) )
				strncpy( sTemp + 2, "1", 1 );
			else
				strncpy( sTemp + 2, "0", 1 );

			// Unused
			strncpy( sTemp + 3, "0", 1 );

			OutBuf += fmt_out( ( char * ) OutBuf, sTemp, ATOBCD, 4, bitno );

			break;

		case 23:
			//Card Sequence Number
			break;

		case 24:
			//Network International Identifier
			break;

		case 25:

			//Point of Service Condition Code (ISO)
			memset( sTemp, 0, sizeof( sTemp ) );
			if( txnmsg->TxnCode / 10000 == 30 )
				strcpy( sTemp, "00" );
			else
				sprintf( sTemp, "%02d", txnmsg->PosConditionCode );

			OutBuf += fmt_out( ( char * ) OutBuf, sTemp, ATOBCD, 2, bitno );

			break;

		case 26:

			//Point of Service (POS) PIN Capture Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->PinCapCode, ITOBCD, 2, bitno );
			break;

		case 27:
			//Authorization ID Response Length
			break;

		case 28:

			// Transaction Fee Amount
			break;

		case 29:
			//Amount, Settlement Fee
			break;

		case 30:
			//Amount, Transaction Processing Fee
			break;

		case 31:
			// Settlement Processing Fee
			break;

		case 32:
			//Acquiring Institution ID Code

			if( txnmsg->MsgType == 810 )
			{
				len = strlen( txnmsg->NetworkId );
				OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
				OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->NetworkId, ATOBCD, len, bitno );
			}
			else if( txnmsg->MsgType == 210 || txnmsg->MsgType == 110 || txnmsg->MsgType == 430 )
			{
				len = strlen( txnmsg->AcqNetworkId );
				OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
				OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->AcqNetworkId, ATOBCD, len, bitno );
			}
			else
			{
				len = strlen( txnmsg->AcquirerBin );
				OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
				OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->AcquirerBin, ATOBCD, len, bitno );
			}
			break;

		case 33:

			//Forwarding Institution ID Code

			len = strlen( txnmsg->FwdNetworkId );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->FwdNetworkId, ATOBCD, len, bitno );
			break;

		case 34:
			//Primary Account Number (PAN), Extended
			break;

		case 35:
			//Track 2 Data
			len = strlen( txnmsg->Track2 );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->Track2, ATOBCD, len, bitno );
			break;

		case 36:
			//Track 3 Data
			break;

		case 37:

			//Retrieval Reference Number
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->RefNum, ATOE, 12, bitno );
			break;

		case 38:

			//Authorization ID Response
			if( !strlen( txnmsg->AuthNum ) )
			{
				memset( txnmsg->AuthNum, 0, sizeof( txnmsg->AuthNum ) );
				sprintf( txnmsg->AuthNum, "%06d", txnmsg->RespCode );
			}
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->AuthNum, ATOE, 6, bitno );
			break;

		case 39:

			//Response Code
			trace( "txnmsg->RespCode[%d]", txnmsg->RespCode );
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->RespCode, ITOE, 2, bitno );
			break ;

		case 40:
			//Service Restriction Code
			break;

		case 41:

			//Card Acceptor Terminal ID
			if( strlen( txnmsg->TerminalId ) < 8 )
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				sprintf( sTemp, "%-8s", txnmsg->TerminalId );
				memset( txnmsg->TerminalId, 0, sizeof( txnmsg->TerminalId ) );
				strcpy( txnmsg->TerminalId, sTemp );
			}

			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->TerminalId, ATOE, 8, bitno );
			break;

		case 42:

			//Card Acceptor ID Code
			if( !strlen( txnmsg->AcceptorId ) )
			{
				memset( txnmsg->AcceptorId, 0, sizeof( txnmsg->AcceptorId ) );
				strcpy( txnmsg->AcceptorId, txnmsg->TerminalId );
			}

			if( strlen( txnmsg->AcceptorId ) < 15 )
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				memset( sTemp, '0', 15 - strlen( txnmsg->AcceptorId ) );
				strcpy( sTemp + 15 - strlen( txnmsg->AcceptorId ), txnmsg->AcceptorId );
			}
			else
			{
				memset( sTemp, 0, sizeof( sTemp ) );
				strncpy( sTemp, txnmsg->AcceptorId, 15 );
			}
			OutBuf += fmt_out( ( char * ) OutBuf, sTemp, ATOE, 15, bitno );
			break;

		case 43:

			//Card Acceptor Name/Location
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->TerminalLocation, ATOE, 40, bitno );
			break;

		case 44:
		{
			//Additional Response Data

			int offset = 0;

			memset( sTemp, 0, sizeof( sTemp ) );

			//Response Source or Reason Code -> 44.1
			sTemp[ offset ] = '0';
			offset += 1;

			//Not Applicable -> 44.2
			sTemp[ offset ] = '0';
			offset += 1;

			//Not Applicable -> 44.3
			sTemp[ offset ] = '0';
			offset += 1;

			//Reserved -> 44.4
			sTemp[ offset ] = '0';
			offset += 1;

			//CVV/iCVV Result Codes -> 44.5
			sTemp[ offset ] = '0';
			offset += 1;

			//Not Applicable -> 44.6
			strncpy( sTemp + offset, "00", 2 );
			offset += 2;

			//Not Applicable -> 44.7
			sTemp[ offset ] = '0';
			offset += 1;

			//Card Authentication Result Code -> 44.8
			sTemp[ offset ] = '0';
			offset += 1;

			//Not Applicable -> 44.9
			sTemp[ offset ] = '0';
			offset += 1;

			//Not Applicable -> 44.10
			sTemp[ offset ] = '0';
			offset += 1;

			//Original Response Code -> 44.11
			sprintf( sTemp + offset, "%02d", txnmsg->RespCode );
			offset += 2;

			//Not Applicable -> 44.12
			sTemp[ offset ] = '0';
			offset += 1;

			//Not Applicable -> 44.13
			sTemp[ offset ] = '0';
			offset += 1;

			len = strlen( sTemp );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, sTemp, ATOE, len, bitno );
		}
		break;

		case 45:
			//Track 1 Data
			break;

		case 46:
			//Additional Data—ISO Use
			break;

		case 47:
			//Additional Data—National Use
			break;

		case 48:
			//Additional Data—Private Use
			break;

		case 49:

			//Acquirer Currency Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->AcqCurrencyCode, STOBCD, 3, bitno );
			break;

		case 50:
			//Settlement Currency Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->SettCurrencyCode, STOBCD, 3, bitno );
			break;

		case 51:
			//Cardholder Billing Currency Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->IssCurrencyCode, STOBCD, 3, bitno );
			break;

		case 52:
			//Personal ID Number (PIN) Data
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->PINBlock, ATOBCD, 16, bitno );
			break;

		case 53:

			//Security-related Control Information
			memset( fld53Data, 0, sizeof( fld53Data ) );
			sprintf( fld53Data, "%s%s%s%s", fld53info.SecurityFormat, fld53info.AlgorithmId, fld53info.PinBlockFormat, fld53info.ZoneKeyIndex );

			if( !strcasecmp( fld53info.PINDataType, "NA" ) )
				strcat( fld53Data, "00" );
			else
				strcat( fld53Data, fld53info.PINDataType );

			if( !strcasecmp( fld53info.VisaReserved, "NA" ) )
				strcat( fld53Data, "000000" );
			else
				strcat( fld53Data, fld53info.VisaReserved );

			OutBuf += fmt_out( ( char * ) OutBuf, fld53Data, ATOBCD, 16, bitno );

			break;

		case 54:

			//Additional Amounts

			memset( sTemp, 0, sizeof( sTemp ) );

			//Account Type
			memset( uTemp, 0, sizeof( uTemp ) );
			sprintf( uTemp, "%06d", txnmsg->TxnCode );
			strncpy( sTemp, uTemp + 2, 2 );

			//Amount Type
			//02 for Available Balance
			strncpy( sTemp + 2, "02", 2 );

			//Account Currency Code
			sprintf( sTemp + 4, "%03d", txnmsg->IssCurrencyCode );

			//C->Positivie Balance D->Negative Balance
			sTemp[ 7 ] = 'C';

			if( strlen( txnmsg->AvailBalance ) < 12 )
			{
				memset( uTemp, 0, sizeof( uTemp ) );
				memset( uTemp, '0', 12 - strlen( txnmsg->AvailBalance ) );
				strcpy( uTemp + 12 - strlen( txnmsg->AvailBalance ), txnmsg->AvailBalance );
				strncpy( sTemp + 8, uTemp, 12 );
			}
			else
				strncpy( sTemp + 8, txnmsg->AvailBalance, 12 );

			//Account Type
			memset( uTemp, 0, sizeof( uTemp ) );
			sprintf( uTemp, "%06d", txnmsg->TxnCode );
			strncpy( sTemp + 20, uTemp + 2, 2 );

			//Amount Type
			//01 for Ledger Balance
			strncpy( sTemp + 22, "01", 2 );

			//Account Currency Code
			sprintf( sTemp + 24, "%03d", txnmsg->IssCurrencyCode );

			//C->Positivie Balance D->Negative Balance
			sTemp[ 27 ] = 'C';


			if( strlen( txnmsg->LedgerBalance ) < 12 )
			{
				memset( uTemp, 0, sizeof( uTemp ) );
				memset( uTemp, '0', 12 - strlen( txnmsg->LedgerBalance ) );
				strcpy( uTemp + 12 - strlen( txnmsg->LedgerBalance ), txnmsg->LedgerBalance );
				strncpy( sTemp + 28, uTemp, 12 );
			}
			else
				strncpy( sTemp + 28, txnmsg->LedgerBalance, 12 );

			len = strlen( sTemp );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, sTemp, ATOE, len, bitno );

			break;

		case 55:

			//Integrated Circuit Card (ICC) System-related Data
			break;

		case 56:
			//Reserved for ISO Use
			break;

		case 57:
			//Reserved for National Use
			break;

		case 58:
			//Authorizing Agent Institution ID
			break;

		case 59:
			//POS Geographical Data

			break;

		case 60:

			//Additional POS Information

			//Terminal Type -> Byte 1
			memset( sTemp, 0, sizeof( sTemp ) );
			if( txnmsg->MerchantType == 6011 )
				sTemp[ 0 ] = '2';
			else
				sTemp[ 0 ] = '0';

			//Terminal Capability -> Byte2
			if( txnmsg->PosEntryCode == 90 || txnmsg->PosEntryCode == 02 )
				sTemp[ 1 ] = '2';
			else if( txnmsg->PosEntryCode == 05 || txnmsg->PosEntryCode == 95 )
				sTemp[ 1 ] = '5';
			else
				sTemp[ 1 ] = '0';

			if( strlen( sTemp ) % 2 == 0 )
				len = strlen( sTemp ) / 2;
			else
				len = strlen( sTemp ) / 2 + 1;

			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOB, 1, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, sTemp, ATOBCD, 2, bitno );

			break ;

		case 61:
			//Point-of-Service (POS) Data
			//Fixed 26
			break ;

		case 62:

			//CPS[Customer Payment Service]
			memset( fld62Data, 0, sizeof( fld62Data ) );
			len = composeField62( txnmsg, fld62Data );
			OutBuf += fmt_out( ( char * ) OutBuf, ( char * ) fld62Data, MOVE, len, bitno );

			break ;

		case 63:

			//VISA SMS Private Use Fields
			memset( fld63Data, 0, sizeof( fld63Data ) );
			len = composeField63( txnmsg, fld63Data );
			OutBuf += fmt_out( ( char * ) OutBuf, ( char * ) fld63Data, MOVE, len, bitno );

			break ;

		case 64:
			//Message Authentication Code (MAC)
			//Used for  Cryptogram
            break ;

		case 65:
			//Bit Map, Extended
			break ;

		case 66:
			//Settlement Code( Used in MsgType 0530 and 0532 ) --- 1 digit
            break ;

		case 67:
			//Extended Payment Code
			break ;

		case 68:
			//Receiving Institution Country Code
			break;

		case 69:
			//Settlement Institution Country Code
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->SettCurrencyCode, STOA, 3, bitno );
			break;

		case 70:

			//Network Management Information Code
			trace( "NetCode[%d]", txnmsg->NetCode );
			txnmsg->NetCode = getOutBoundExtNetCode( txnmsg->NetCode );
			trace( "NetCode[%d]", txnmsg->NetCode );
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->NetCode, STOBCD, 3, bitno );
			break;

        case 71:
        	//Message Number
            break;

        case 72:
        	//Message Number Last
            break;

        case 73:
        	//Date, Action
        	break;

        case 74:
        	// Number of Credits, ( Used in MsgType 0520 and 0522 )
        	break;

        case 75:
        	// Number of Credits Reversal, ( Used in MsgType 0520 and 0522 )
        	break;

        case 76:
        	// Number of Debits, ( Used in MsgType 0520 and 0522 )
        	break;

        case 77:
        	// Number of Debits Reversal, ( Used in MsgType 0520 and 0522 )
        	break;

        case 78:
        	// Number of Transfers, ( Used in MsgType 0520 and 0522 )
        	break;

        case 79:
        	// Number of Transfers Reversal, ( Used in MsgType 0520 and 0522 )
        	break;

        case 80:
        	// Number of Inquiries, ( Used in MsgType 0520 and 0522 )
        	break;

        case 81:
        	// Number of Authorizations, ( Used in MsgType 0520 and 0522 )
        	break;

        case 82:
        	// Credits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 83:
        	// Credits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 84:
        	// Debits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 85:
        	// Debits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 86:
        	// Credits Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 87:
         	// Credits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
         	break;

        case 88:
        	// Debits Amount, ( Used in MsgType 0520 and 0522 )
        	break;

        case 89:
         	// Debits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
         	break;

		case 90:

			//Original Data Elements
			trace( "Original Data Elements" );
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->OrgMsgType, ITOBCD, 4, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, &txnmsg->OrgTraceNo, ITOBCD, 6, bitno );
			memset( sTemp, 0, sizeof( sTemp ) );
			sprintf( sTemp, "%06d", txnmsg->OrgTranDate );
			memset( fld53Data, 0, sizeof( fld53Data ) );
			strncpy( fld53Data, sTemp + 2, 2 );
			strncpy( fld53Data + 2, sTemp, 2 );
			OutBuf += fmt_out( ( char * ) OutBuf, fld53Data, ATOBCD, 4, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, 	&txnmsg->OrgTranTime, ITOBCD, 		6, bitno );
			memset( sTemp, 0, sizeof( sTemp ) );
			memset( sTemp, '0', 11 - strlen( txnmsg->AcquirerBin ) );
			strcpy( sTemp + 11 - strlen( txnmsg->AcquirerBin ), txnmsg->AcquirerBin );
			strcat( sTemp, "00000000000" );
			OutBuf += fmt_out( ( char * ) OutBuf, sTemp,  ATOBCD, 22, bitno );
			//OutBuf += fmt_out( ( char * ) OutBuf, ( char * ) "000000000000",  ATOBCD, 12, bitno );
			//OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->ForwardInst,  ATOBCD, 22, bitno );
			break ;

		case 91:
			//File Update Code
			break;

		case 92:
			//File Security Code
			break;

		case 93:
			//Response Indicator
			break;

		case 94:
			//Service Indicator
			break;

		case 95:

			break ;

		case 96:
			//Message Security Code
			break;

		case 97:
			//Net Settlement Amount,( Used in MsgType 0530, 0532, 0520 and 0522 )
			break;

		case 98:
			//Payee
			break;

		case 99:
			//Settlement Institution ID Code,( Used in MsgType 0530, 0532, 0520 and 0522 )
			break;

		case 100:
			//Receiving Institution ID Code
			break;

		case 101:
			//File Name
			break;

		case 102:
			//Account ID-1
			len = strlen( txnmsg->FromAccount );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->FromAccount, CHAR, len, bitno );
			break;

		case 103:
			//Account ID-2
			len = strlen( txnmsg->ToAccount );
			OutBuf += fmt_out( ( char * ) OutBuf, &len, ITOA, 2, bitno );
			OutBuf += fmt_out( ( char * ) OutBuf, txnmsg->ToAccount, CHAR, len, bitno );
			break;

		case 104:
			//Transaction Description
			break;

		case 105:
		case 106:
		case 107:
		case 108:
		case 109:
		case 110:
			//Reserved for ISO Use
			break;

		case 111:
			////Amount, Currency Conversion Assessment
			break;

		case 112:
		case 113:
		case 114:
		case 115:
		case 116:
		case 117:
		case 118:
		case 119:
			//Reserved for National Use
			break;

		case 120:
			//Record Data
			break;

		case 121:
			//Authorizing Agent ID Code
			break;

		case 122:
			//Additional Record Data
			break;

		case 123:
		case 124:
		case 125:
			//Reserved for Future Definition and RSC Use
			break;

		case 126:
			//Switch Private Data --LLLVAR
			break;

		case 127:
			//Processor Private Data
			break;

		case 128:
			//Message Authentication Code (MAC)
			break;

		default:
			trace( "Unhandled bit in ISO Decompose [%d]", bitno );

		}
	}

	int MsgLen = OutBuf - BufOffset;
	memset( MsgHeader, 0, sizeof( MsgHeader ) );
	len = composeMsgHeader( BitMap, MsgHeader, MsgLen );

	memcpy( IsoBuffer, MsgHeader,  len );
	memcpy( IsoBuffer + len, OutBuffer, MsgLen );

	return len + MsgLen;
}

int EzVisaSMS :: DecomposeISOMessage( unsigned char *InBuf, struct EzTxnMsg *txnmsg )
{
	unsigned char BitMap[ 49 ], bitmap62[ 9 ], bitmap63[ 4 ];
	int Ind, len;
	char TempAmount[13], uTemp[ 150 ], sTemp[ 150 ];
	char RejectCode[ 20 ];
	char Temp[50];

	memset( RejectCode, 0, sizeof( RejectCode ) );
	InBuf += decomposeMsgHeader( InBuf, RejectCode );

	//Message Type
	InBuf += fmt_in( ( char * ) InBuf, &txnmsg->MsgType, BCDTOI, 4, 0 );

	//Primary BitMap
	memset( BitMap, 0, sizeof( BitMap ) );
	InBuf += fmt_in( ( char * ) InBuf, BitMap, MOVE, 8, 1 );

	//Secondary BitMap
	if( IsBitSet( BitMap, 1 ) )
		InBuf += fmt_in( ( char * ) InBuf, BitMap + 8, MOVE, 8, 1 );

	for( int bitno = 1; bitno <= 128; bitno++ )
	{
		if( !IsBitSet( BitMap, bitno ) )
			continue;

		if( bitno > 64 )
		{
			if( !IsBitSet( BitMap, 1 ) )
				break;
		}

		switch ( bitno )
		{

			case 2:

				//CHN
				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->chn, BCDTOA, len, bitno );
				break ;

			case 3:

				//Processing Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->TxnCode, BCDTOL, 6, bitno );
				break ;

			case 4:

				//Transaction Amount
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->Amount, BCDTOA, 12, bitno );
				break ;

			case 5:

				//Settelment Amount
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->SettAmount, BCDTOA, 12, bitno );
				break ;

			case 6:

				//Actual Billing Amount( Amount converted to Issuer Currency )
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->BillingAmount, BCDTOA, 12, bitno );
				break ;

			case 7:

				// Transaction Date in DDMM
				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, BCDTOA, 4, bitno );
				if( txnmsg->MsgType == EZLINK_TXN_TxnRequest || txnmsg->MsgType == 420 || txnmsg->MsgType == 220 )
				{
					memset( sTemp, 0, sizeof( sTemp ) );
					strncpy( sTemp, uTemp + 2, 2 );
					strncpy( sTemp + 2, uTemp, 2 );
					memset( uTemp, 0, sizeof( uTemp ) );
					sprintf( uTemp, "%06d", ezdatetimeutil.getSysDate() );
					strncpy( sTemp + 4, uTemp + 4, 2 );
					txnmsg->TranDate = atoi( sTemp );
				}
				else
					txnmsg->TranDate = 0;

				//Transaction Time
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->TranTime, BCDTOI, 6, bitno );

				break ;

			case 9:

				break ;

			case 10:

				break;

			case 11:

				//System Trace Audit Number
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->TraceNo, BCDTOI, 6, bitno );
				break ;

			case 12:

				//Local Transaction Time ( field format hhmmss )
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->LocalTime, BCDTOI, 6, bitno );
				break ;

			case 13:

				//Local Transaction Date ( field format MMDD )
				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, BCDTOA, 4, bitno );
				if( txnmsg->MsgType == EZLINK_TXN_TxnRequest )
				{
					memset( sTemp, 0, sizeof( sTemp ) );
					strncpy( sTemp, uTemp + 2, 2 );
					strncpy( sTemp + 2, uTemp, 2 );
					memset( uTemp, 0, sizeof( uTemp ) );
					sprintf( uTemp, "%06d", ezdatetimeutil.getSysDate() );
					strncpy( sTemp + 4, uTemp + 4, 2 );
					txnmsg->LocalDate = atoi( sTemp );
				}
				else
					txnmsg->LocalDate = 0;

				break ;

			case 14:

				//Card Expiration Date ( field format YYMM )
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->ExpiryDate, BCDTOI, 4, bitno );
				break ;

			case 15:

				// Settlement Date ( field format MMDD )
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->SettlementDate, BCDTOI, 4, bitno );
				txnmsg->SettlementDate = 0;
				break ;

			case 16:

				//Issuer Coversion Date
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->IssConvDate, BCDTOI, 4, bitno );
				break ;

			case 17:

				// Capture Date ( field format YYMM )
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->CaptureDate, BCDTOI, 4, bitno );
				txnmsg->CaptureDate = 0;
				break ;

			case 18:

				//Merchant Type
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->MerchantType, BCDTOI,4, bitno );
				break ;

			case 19:

				//Acquiring Institution Country Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->AcqCountryCode, BCDTOI, 4, bitno );
				break ;

			case 20:

				//Primary Account Number (PAN) Country Code( Issuer )
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->IssCountryCode, BCDTOI, 4, bitno );
				break ;

			case 21:

				//Forwarding Institution Country Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->FwdCountryCode, BCDTOI, 4, bitno );
				break ;

			case 22:

				//POS Entry Mode Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->PosEntryCode, BCDTOI, 4, bitno );
				break;

			case 23:

				//Card Sequence Number
				break;

			case 24:
				//Network International Identifier
				break;

			case 25:
				//Point of Service Condition Code (ISO)
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->PosConditionCode, BCDTOI, 2, bitno );
				break;

			case 26:

				//Point of Service (POS) PIN Capture Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->PinCapCode, BCDTOI, 2, bitno );
				break;

			case 27:
				//Authorization ID Response Length
				break;

			case 28:
				//Amount, Settlement Fee
				memset( sTemp, 0, sizeof( sTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, sTemp, ETOA, 1, bitno );
				memset( txnmsg->TxnFee, 0, sizeof( txnmsg->TxnFee ) );
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->TxnFee, ETOA, 8, bitno );
				break;

			case 29:
				//Amount, Settlement Fee
				break;

			case 30:
				//Amount, Transaction Processing Fee
				break;

			case 31:
				// Settlement Processing Fee
				break;

			case 32:

				//Acquiring Institution ID Code

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->AcqNetworkId, BCDTOA, len, bitno );

				break;

			case 33:

				//Forwarding Institution ID Code

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->FwdNetworkId, BCDTOA, len, bitno );

				break;

			case 34:

				//Primary Account Number (PAN), Extended
				break;

			case 35:

				//Track 2 Data

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->Track2, BCDTOA, len, bitno );

				break;

			case 36:

				//Track 3 Data
				break;

			case 37:

				//Retrieval Reference Number
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->RefNum, ETOA, 12, bitno );
				break;

			case 38:

				//Authorization ID Response
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->AuthNum, ETOA, 6, bitno );
				break;

			case 39:

				//Response Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->RespCode, ETOI, 2, bitno );
				break ;

			case 40:

				//Service Restriction Code
				break;

			case 41:

				memset( sTemp, 0, sizeof( sTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, sTemp, ETOA, 8, bitno );
				memset( txnmsg->TerminalId, 0, sizeof ( txnmsg->TerminalId ) );
				for( int k = 0, j = 0; k < strlen( sTemp ); k++ )
				{
					if( sTemp[ k ] != ' ' )
					{
						txnmsg->TerminalId[ j ] = sTemp[ k ];
						j++;
					}
				}
				break ;

			case 42:

				//Card Acceptor ID Code
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->AcceptorId, ETOA, 15, bitno );
				break;

			case 43:

				//Card Acceptor Name/Location
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->TerminalLocation, ETOA, 40, bitno );
				break;

			case 44:

				//Additional Response Data
				break;

			case 45:
				//Track 1 Data
				break;

			case 46:
				//Additional Data—ISO Use
				break;

			case 47:
				//Additional Data—National Use
				break;

			case 48:
				//Additional Data—Private Use
				break;

			case 49:

				//Acquirer Currency Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->AcqCurrencyCode, BCDTOI, 4, bitno );
				break;

			case 50:

				//Settlement Currency Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->SettCurrencyCode, BCDTOI, 4, bitno );
				break;

			case 51:

				//Cardholder Billing Currency Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->IssCurrencyCode, BCDTOI, 4, bitno );
				break;

			case 52:

				//Personal ID Number (PIN) Data
				InBuf += fmt_in( ( char * ) InBuf, txnmsg->PINBlock, BCDTOA, 16, bitno );
				break;

			case 53:

				//Security-related Control Information
				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, MOVE, 8, bitno );
				break;

			case 54:

				//Additional Amounts
				char tempStr[ 20 ], amtType[ 3 ];

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );

				for( int i = 0; i < len; i += 20 )
				{
					//Account Type
					memset( sTemp, 0, sizeof( sTemp ) );
					InBuf += fmt_in( ( char * ) InBuf, sTemp, ETOA, 2, bitno );

					//Amount Type
					memset( amtType, 0, sizeof( amtType ) );
					InBuf += fmt_in( ( char * ) InBuf, amtType, ETOA, 2, bitno );

					//Currency Code
					memset( sTemp, 0, sizeof( sTemp ) );
					InBuf += fmt_in( ( char * ) InBuf, sTemp, ETOA, 3, bitno );

					//Amount Sign
					memset( sTemp, 0, sizeof( sTemp ) );
					InBuf += fmt_in( ( char * ) InBuf, sTemp, ETOA, 1, bitno );

					memset( sTemp, 0, sizeof( sTemp ) );
					InBuf += fmt_in( ( char * ) InBuf, sTemp, ETOA, 12, bitno );

					if( !strcmp( amtType, "01" ) )
					{
						memset( txnmsg->LedgerBalance, 0, sizeof( txnmsg->LedgerBalance ) );
						strcpy( txnmsg->LedgerBalance, sTemp );
					}
					else
					{
						memset( txnmsg->AvailBalance, 0, sizeof( txnmsg->AvailBalance ) );
						strcpy( txnmsg->AvailBalance, sTemp );
					}
				}
				break ;

			case 55:
				//Integrated Circuit Card (ICC) System-related Data
				break;

			case 56:
				//Reserved for ISO Use
				break;

			case 57:
				//Reserved for National Use
				break;

			case 58:
				//Authorizing Agent Institution ID
				break;

			case 59:
				//POS Geographical Data
				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, MOVE, len, bitno );
				break;

			case 60:

				//Additional POS Information

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, MOVE, len, bitno );

				break ;

			case 61:

				// Other Amounts

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );
				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, MOVE, len, bitno );
				break;

			case 62:

				//Customer Payment Service Fields BitMap
				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );

				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, MOVE, len, bitno );

				memset( bitmap62, 0, sizeof( bitmap62 ) );
				memcpy( bitmap62, uTemp, 8 );

				for( int bit62no = 0; bit62no < 65; bit62no++ )
				{
					if( !IsBitSet( bitmap62, bit62no + 1 ) )
						continue;

					switch ( bit62no + 1 )
					{
						case 1:

							trace( "ACI...[%02x]", ( unsigned char ) uTemp[ 8 ] );
							//ACI
							memset( txnmsg->RsvFld6, 0, sizeof( txnmsg->RsvFld6 ) );
							txnmsg->RsvFld6[ 0 ] = ebcdic_to_ascii( ( unsigned char ) uTemp[ 8 ] );
							trace( "ACI[%c]", txnmsg->RsvFld6[ 0 ] );
							hex_dump( ( unsigned char * ) uTemp, 9 );

						break;

						case 2:

							//Txn Identifier
							memset( sTemp, 0, sizeof( sTemp ) );
							bcd_to_ascii( uTemp + 9, sTemp, 16 );
							trace( "TxnIdentifier[%s]", sTemp );
							strcat( txnmsg->RsvFld6, "^" );
							strcat( txnmsg->RsvFld6, sTemp );
							trace( "RsvFld6[%s]", txnmsg->RsvFld6 );

						break;

						default:

						break;

					}
				}

				break ;

			case 63:

				//SMS Private-Use Fields

				InBuf += fmt_in( ( char * ) InBuf, &len, BTOI, 1, bitno );

				memset( uTemp, 0, sizeof( uTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, uTemp, MOVE, len, bitno );

				memset( bitmap63, 0, sizeof( bitmap63 ) );
				memcpy( bitmap63, uTemp, 3 );

				for( int bit63no = 1; bit63no < 24; bit63no++ )
				{
					if( !IsBitSet( bitmap63, bit63no + 1 ) )
						continue;

					switch ( bit63no + 1 )
					{
						case 1:

							memset( sTemp, 0, sizeof( sTemp ) );
							this->bcd_to_ascii( uTemp + 4, sTemp, 4 );
							strcat( txnmsg->RsvFld6, sTemp );

						break;

						case 2:

						break;

						default:

						break;

					}
				}

				break ;

			case 64:

				//Message Authentication Code (MAC)
				//Used for  Cryptogram
                break ;

			case 65:
				//Bit Map, Extended
				break ;

			case 66:
				//Settlement Code( Used in MsgType 0530 and 0532 ) --- 1 digit
                break ;

			case 67:
				//Extended Payment Code
				break ;

			case 68:
				//Receiving Institution Country Code
				break;

			case 69:
				//Settlement Institution Country Code
				break;

			case 70:

				//Network Management Information Code
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->NetCode, BCDTOI, 2, bitno );
				break;

            case 71:
            	//Message Number
                break;

            case 72:
            	//Message Number Last
                break;

            case 73:
            	//Date, Action
            	break;

            case 74:
            	// Number of Credits, ( Used in MsgType 0520 and 0522 )
            	break;

            case 75:
            	// Number of Credits Reversal, ( Used in MsgType 0520 and 0522 )
            	break;

            case 76:
            	// Number of Debits, ( Used in MsgType 0520 and 0522 )
            	break;

            case 77:
            	// Number of Debits Reversal, ( Used in MsgType 0520 and 0522 )
            	break;

            case 78:
            	// Number of Transfers, ( Used in MsgType 0520 and 0522 )
            	break;

            case 79:
            	// Number of Transfers Reversal, ( Used in MsgType 0520 and 0522 )
            	break;

            case 80:
            	// Number of Inquiries, ( Used in MsgType 0520 and 0522 )
            	break;

            case 81:
            	// Number of Authorizations, ( Used in MsgType 0520 and 0522 )
            	break;

            case 82:
            	// Credits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 83:
            	// Credits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 84:
            	// Debits, Processing Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 85:
            	// Debits, Transaction Fee Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 86:
            	// Credits Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 87:
             	// Credits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
             	break;

            case 88:
            	// Debits Amount, ( Used in MsgType 0520 and 0522 )
            	break;

            case 89:
             	// Debits , Reversal Amount, ( Used in MsgType 0520 and 0522 )
             	break;

			case 90:

				//Original Data Elements

				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->OrgMsgType, BCDTOI, 2, bitno );
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->OrgTraceNo, BCDTOI, 3, bitno );
				memset( sTemp, 0, sizeof( sTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, sTemp, BCDTOA, 2, bitno );
				InBuf += fmt_in( ( char * ) InBuf, &txnmsg->OrgTranTime, BCDTOI, 3, bitno );
				memset( sTemp, 0, sizeof( sTemp ) );
				InBuf += fmt_in( ( char * ) InBuf, sTemp, BCDTOA, 11, bitno );

				break ;

			case 91:
				//File Update Code
				break;

			case 92:
				//File Security Code
				break;

			case 93:
				//Response Indicator
				break;

			case 94:
				//Service Indicator
				break;

			case 95:
				//Replacement Amounts
				break ;

			case 96:
				//Message Security Code
				break;

			case 97:
				//Net Settlement Amount,( Used in MsgType 0530, 0532, 0520 and 0522 )
				break;

			case 98:
				//Payee
				break;

			case 99:
				//Settlement Institution ID Code,( Used in MsgType 0530, 0532, 0520 and 0522 )
				break;

			case 100:
				//Receiving Institution ID Code
				break;

			case 101:
				//File Name
				break;

			case 102:
				//Account ID-1
				break;

			case 103:
				//Account ID-2
				break;

			case 104:
				//Transaction Description
				break;

			case 105:
			case 106:
			case 107:
			case 108:
			case 109:
			case 110:
				//Reserved for ISO Use
				break;

			case 111:
				////Amount, Currency Conversion Assessment
				break;

			case 112:
			case 113:
			case 114:
			case 115:
			case 116:
			case 117:
			case 118:
			case 119:
				//Reserved for National Use
				break;

			case 120:
				//Record Data
				break;

			case 121:
				//Authorizing Agent ID Code
				break;

			case 122:
				//Additional Record Data
				break;

			case 123:
			case 124:
			case 125:
				//Reserved for Future Definition and RSC Use
				break;

			case 126:
				//Switch Private Data --LLLVAR
				break;

			case 127:
				//Processor Private Data
				break;

			case 128:
				//Message Authentication Code (MAC)
				break;

			default:
				trace( "Unhandled bit in ISO Decompose [%d]", bitno );
		}
	}
	return 1;
}

void EzVisaSMS :: ServiceRequest()
{
	struct EzTxnMsg txnmsg;
	int MsgSize;
	unsigned char ISOMessage[ 4097 ];
	unsigned char MsgBuffer[ 4600 + 1 ];
        struct EzEchoTable echotable_rec;

	while( 1 )
	{
		trace( "EzVisaSMS Waiting for Request to be Serviced" );
		memset( ISOMessage, 0, sizeof( ISOMessage ) );
		if( ReadMessage( ( char * ) ISOMessage, &MsgSize ) < 0 )
		{
			trace( "Error in Reading Message from Channel[%s]", GetSourceChannelName() );
			continue;
		}

		if( IsPortMessage() )
		{
			trace( "Message of size[ %d ] Received from PortChannel[ %s ]", MsgSize, GetSourceChannelName() );
			hex_dump( ( unsigned char * ) ISOMessage, MsgSize );
			memset( &txnmsg, 0, sizeof( struct EzTxnMsg ) );
			if( DecomposeISOMessage( ISOMessage, &txnmsg ) < 0 )
			{
				trace( "Error in Decomposing ISO Message from Port[%s]", GetLastSenderChannelName() );
				continue;
			}

			memset( txnmsg.NetworkId, 0, sizeof( txnmsg.NetworkId ) );
                        if( getNetworkIdFromPort( GetLastSenderChannelName(), txnmsg.NetworkId ) < 0 )
                                trace( "Error in Reading NetworkId for Port[%s]...", GetLastSenderChannelName() );
			
			if( txnmsg.MsgType == 800 )
                        {
				if( getNetworkStatus() == NETWORK_STATUS_DOWN )
                                {
                                	if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
                                		trace( "Error in Updating Status for NetworkId[%s]", txnmsg.NetworkId );

                                }

                                txnmsg.MsgType = 810;
                                strcpy( txnmsg.DestPort, GetLastSenderChannelName() );
                                memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
                                MsgSize = ComposeISOMessage( &txnmsg, MsgBuffer );
                                if( MsgSize < 0 )
                                {
                                        trace( "Error in Composing ISO Message" );
                                        continue;
                                }

                                hex_dump( ( unsigned char * ) MsgBuffer, MsgSize );
                                if( WritePortChannel( txnmsg.DestPort, ( char * )MsgBuffer, MsgSize ) < 0 )
	                                trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
                                else
        	                        trace( "Written Message to Port[%s]", txnmsg.DestPort );
                                continue;
                        }
			
			if( txnmsg.MsgType == 810 )
                        {
                                trace( "received 810 with NetCode[%d] RespCode[%d]", txnmsg.NetCode, txnmsg.RespCode );
                                memset( &echotable_rec, 0, sizeof( struct EzEchoTable ) );
                                if( readEchoTable( txnmsg.NetworkId, &echotable_rec ) < 0 )
                                {
                                        trace( "Error in Reading NetworkId[%s] from Echo Table....", txnmsg.NetworkId );
                                        continue;
                                }
                                if( txnmsg.NetCode == EZLINK_NETCODE_LOGON && !txnmsg.RespCode )
                                {
                                        if( echotable_rec.EchoRespStatus == ECHO_RESP_STATUS_SIGNON_SENT )
                                        {
                                                trace( "Expecting a Response for SignOn...but got Response for LogOn....for NetworkId[%s]", txnmsg.NetworkId );
                                                continue;
                                        }
                                        if( updateEchoRespStatus( txnmsg.NetworkId, ECHO_RESP_STATUS_LOGON_RCVD ) < 0 )
                                                trace( "Error in Updating LogOnStatus for NetworkId[%s]", txnmsg.NetworkId );

                                        if( getNetworkStatus() == NETWORK_STATUS_DOWN )
                                        {
                                                if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
                                                        trace( "Error in Updating Status for NetworkId[%s]", txnmsg.NetworkId );

                                        }
                                        txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
                                        if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
                                                trace( "Error in Sending Intimation Message to EzSafReader" );
                                        else
                                                trace( "Sent Intimation Message to EzSafReader" );

                                        continue;
                                }
				else if ( txnmsg.NetCode == EZLINK_NETCODE_SIGNON && !txnmsg.RespCode )
                                {
                                        if( echotable_rec.EchoRespStatus == ECHO_RESP_STATUS_LOGON_SENT )
                                        {
                                                trace( "Expecting a Response for LogOn...but got Response for SignOn....for NetworkId[%s]", txnmsg.NetworkId );
                                                continue;
                                        }
                                        if( updateEchoRespStatus( txnmsg.NetworkId, ECHO_RESP_STATUS_SIGNON_RCVD ) < 0 )
                                                trace( "Error in Updating SignOnStatus for NetworkId[%s]", txnmsg.NetworkId );
                                        if( getNetworkStatus() == NETWORK_STATUS_DOWN )
                                        {
                                                if( setNetworkStatus( txnmsg.NetworkId, NETWORK_STATUS_UP ) < 0 )
                                                        trace( "Error in Updating Status for NetworkId[%s]", txnmsg.NetworkId );
                                        }
                                        txnmsg.MsgType = EZLINK_TXN_ReplayIntimationRequest;
                                        if( WriteChannel( "EzSafReader", ( char * ) &txnmsg, sizeof( struct EzTxnMsg ) ) < 0 )
                                                trace( "Error in Sending Intimation Message to EzSafReader" );
                                        else
                                                trace( "Sent Intimation Message to EzSafReader" );

                                        continue;
                                }
                        }
			if( txnmsg.MsgType == EZLINK_TXN_TxnAdviceRequest && txnmsg.MerchantType == 6011 )
				txnmsg.MsgType = EZLINK_TXN_ReversalAdviceResponse;

			if( txnmsg.MsgType == 200 || txnmsg.MsgType == 100 || txnmsg.MsgType == 420 || txnmsg.MsgType == 220 )
				populateNewRequest( &txnmsg );

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

			memset( ISOMessage, 0, sizeof( ISOMessage ) );
			MsgSize = ComposeISOMessage( &txnmsg, ISOMessage );
			if( MsgSize < 0 )
			{
				trace( "Error in Composing ISO Message" );
				continue;
			}
			hex_dump( ( unsigned char * ) ISOMessage, MsgSize );
			if( WritePortChannel( txnmsg.DestPort, ( char * ) ISOMessage, MsgSize ) < 0 )
				trace( "Error in Writing Message to Port[%s]", txnmsg.DestPort );
			else
				trace( "Written Message to Port[%s]", txnmsg.DestPort );
		}
	}
}


int main( int argc, char **argv )
{
	EzVisaSMS ezvisasmsobj;
	ezvisasmsobj.InitEzVisaSMS( argv[ 0 ] );
	ezvisasmsobj.ServiceRequest();
	return 1;
}

