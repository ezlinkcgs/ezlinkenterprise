#include <ezbusiness/ezeracomutil.h>

int EzEracomUtil :: initEracomUtil( EzDebugUtil *dptr )
{
	this->dptr = dptr;
	return 1;
}

bool EzEracomUtil :: IsBitSet( unsigned char * bitmap, short bit )
{
	if( ( bit < 1 ) || ( bit > 128 ) )
		return true;
	int byte_offset = bit/8;
	int bit_offset = bit%8;
	if ( bit_offset == 0 )
	{
		byte_offset --;
		bit_offset = 8 ;
	}
	if ( ( *(bitmap+byte_offset) & ( 0x80 >> ( bit_offset - 1 ) ) ) )
		return true;
	else
		return false;
}

void EzEracomUtil :: eracom_SetBitOn( unsigned char * bitmap, short bit )
{
	if( ( bit < 1 ) || ( bit > 128 ) )
		return;
	int byte_offset = bit/8;
	int bit_offset = bit%8;
	if ( bit_offset == 0 )
	{
		byte_offset --;
		bit_offset = 8 ;
	}
	*( bitmap+byte_offset ) = ( *(bitmap+byte_offset) | ( 0x80 >> ( bit_offset - 1 ) ) ) ;
}

void EzEracomUtil :: eracom_SetBitOff( unsigned char * bitmap, short bit )
{
	if( ( bit < 1 ) || ( bit > 128 ) )
		return;
	unsigned char x = 1;
	if( !IsBitSet( bitmap, bit ) )
		return;

	int byte_offset = bit/8;
	int bit_offset = bit%8;
	if ( bit_offset == 0 )
	{
		byte_offset --;
		bit_offset = 8 ;
	}
	x = x << ( 7 - ( bit_offset - 1 ) );
	x = ~x;
	*( bitmap+byte_offset ) = *(bitmap+byte_offset) & x;
}

int EzEracomUtil :: eracom_atohex( int val )
{
     if( ( val >= 48 ) && ( val <= 57 ) )
         return ( val - 48 );
     else if( ( val >= 65 ) && ( val <= 70 ) )
         return ( val - 55 );
     else if( ( val >= 97 ) && ( val <= 102 ) )
         return ( val - 87 );
     else
         return val;
}

void EzEracomUtil :: eracom_ascii_to_bcd( const char *strptr, char *bp, int size )
{
	unsigned int lnibble, rnibble;

	for( int i = 0, lnibble = 0, rnibble = 0; i < size; i++, strptr += 2 )
	{
		 lnibble = *strptr;
		 lnibble = eracom_atohex( lnibble );
		 rnibble = *( strptr + 1 );
		 rnibble = eracom_atohex( rnibble );
		 *bp = ( lnibble << 4 ) | ( rnibble & 0xf );
		 bp++;
	}
}

void EzEracomUtil :: eracom_bcd_to_ascii( const char *bp, char *str, int size )
{
	int i = 0, j = 0;
	while( 1 )
	{
		if( j >= size )
			break;
		str[ j ] = ( ( bp[ i ] & 0xf0 ) >> 4 );
		if( ( str[ j ] >= 0 ) && ( str[ j ] <= 9 ) )
			str[ j ] += 48;
		else
			str[ j ] += 87;
		str[ j + 1 ] = bp[ i ] & 0x0f;
		if( ( str[ j + 1 ] >= 0 ) && ( str[ j + 1 ] <= 9 ) )
			str[ j + 1 ] += 48;
		else
			str[ j + 1 ] += 87;
		j += 2;
		i++;
	}
}

int EzEracomUtil :: eracom_out( void *data_ptr, char *outbuf, int size, const char *FldName, int opt_type )
{
	int offsetsize = 0;

	offsetsize = size;

	switch( opt_type )
	{
		case ERACOM_STR_TO_BCD:
		{
			unsigned char *strptr;

			if( size % 2 == 0 )
				offsetsize = size / 2 ;
			else
				offsetsize = size / 2 + 1;
			strptr = ( unsigned char * ) data_ptr;
			dptr->strace( "ERACOM_OUT[%s]<%s>\n", FldName, strptr );
			eracom_ascii_to_bcd( ( char * ) strptr, outbuf, offsetsize );
		}
		break;

		case ERACOM_INT_TO_BINARY:
		{
			int *tmp;
			tmp = ( int * ) data_ptr;
			if( size == 1 )
			{
				dptr->strace( "ERACOM_OUT[%s]<%x>\n", FldName, *tmp );
				memcpy( outbuf, tmp, 1 );
			}
			else if ( size == 2 )
			{
				dptr->strace( "ERACOM_OUT[%s]<%x>\n", FldName, *tmp );
				*tmp = htons( *tmp );
				memcpy( outbuf, tmp, 2 );
			}
		}
		break;

		case ERACOM_MOVE:
		{
			char *bp;
			memcpy( outbuf, data_ptr, size );
			bp = outbuf;
			dptr->strace( "ERACOM_OUT[%s] <", FldName );
			for( int i = 0; i < size; i++ )
				dptr->strace( "%02x", * ( bp + i ) );
			dptr->strace( ">" );
		}
		break;
	}
	return offsetsize;
}

int EzEracomUtil :: eracom_in( char *inbuf, void *data_ptr, int size, const char *FldName, int opt_type )
{
	int offsetsize = 0;

	offsetsize = size;

	switch( opt_type )
	{
		case ERACOM_BCD_TO_STR:
		{
			int i = 0, j = 0;
			char str[ ERACOM_UTIL_BUF_SIZE + 1 ];
			char *temp_ptr;

			memset( str, 0, sizeof( str ) );
			eracom_bcd_to_ascii( inbuf, str, size );
			temp_ptr = ( char * ) data_ptr;
			strcpy( temp_ptr, str );
			dptr->strace( "ERACOM_IN[%s]<%s>\n", FldName, str );

			if( size % 2 == 0 )
				offsetsize = size / 2;
			else
				offsetsize = size / 2 + 1;
		}
		break;

		case ERACOM_BINARY_TO_INT:
		{
			int *temp_ptr;
			if( size == 1 )
			{
				temp_ptr = ( int * ) data_ptr;
				*temp_ptr = *inbuf;
				dptr->strace( "ERACOM_IN[%s]<%x>\n", FldName, *( int * )data_ptr );
			}
			else if ( size == 2 )
			{
				temp_ptr = ( int * ) data_ptr;
				memcpy( temp_ptr, inbuf, 2 );
				*temp_ptr = htons( *temp_ptr );
				dptr->strace( "ERACOM_IN[%s]<%d>\n", FldName, *( int * )data_ptr );
			}
		}
		break;
	}
	return offsetsize;
}

int EzEracomUtil :: composeGenerateDeviceCommKeyReq( const char *DeviceMasterKey, int KeyLen, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	unsigned char KeyFlags[ 5 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;
	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0400", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//KTM Specifier->Terminal Master Key Specifier

	//Length of KTM Specifier
	Len = KeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "TMK-LEN", ERACOM_INT_TO_BINARY );
	//Key Specification Format
	if( KeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "TMK-FORMAT", ERACOM_STR_TO_BCD );
	else if( KeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "TMK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "TMK-FORMAT", ERACOM_STR_TO_BCD );

	//KTM
	ReqBuffer += eracom_out( ( void * ) DeviceMasterKey, ReqBuffer, KeyLen, "TMK", ERACOM_STR_TO_BCD );

	//Key Flags
	//Bit 0   Single-length Data Key (DPK).
	//Bit 1   Single-length PIN encrypting key (PPK).
	//Bit 2   Single-length MAC key (MPK).
	//Bit 3   Single-length terminal master key (KTM).
	//Bit 4-7 Reserved. Must be zero.
	//Bit 8   Double-length Data Key (DPK).
	//Bit 9   Double-length PIN encrypting key (PPK).
	//Bit 10  Double-length MAC key (MPK).
	//Bit 11  Double-length terminal master key (KTM).
	//Bit 12  Encryption mode: 0 = ECB, 1 = CBC
	//Bit 13-15 Reserved. Must be zero.
	//Bit 0 is the least significant (rightmost) bit.
	//To generate a single-length MAC key, this field must be set to 0004
	//To generate a double-length PIN encrypting key and a single-length MAC key, the field must be set to 0204

	memset( KeyFlags, 0, sizeof( KeyFlags ) );
	if( KeyLen == 16 )
	{
		//Bit 1   Single-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 15 );
	}
	else if ( KeyLen == 32 )
	{
		//Bit 9   Double-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 7 );
	}
	else
	{
		//Bit 9   Double-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 7 );
	}
	ReqBuffer += eracom_out( ( void * ) KeyFlags, ReqBuffer, 2, "KeyFlags", ERACOM_MOVE );
	dptr->hex_dump( ( unsigned char * )  BasePtr, ( ReqBuffer - BasePtr ) );
	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeGenerateDeviceCommKeyReq( const char *ResponseBuffer,  int KeyLen, char *DeviceCommKey_LMK, char *DeviceCommKey )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];
	int Len;

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;

	//No. of Keys
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "NKEYS", ERACOM_BCD_TO_STR );

	//Key Length
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, ( void *) &Len, 1, "COMMKEY_TMK_LEN", ERACOM_BINARY_TO_INT );

	if( Len % 2 == 0 )
		Len = Len * 2;
	else
		Len = ( Len * 2 ) - 1;

	//COMMKEY_TMK
	RespBuffer += eracom_in( RespBuffer, DeviceCommKey, Len, "COMMKEY_TMK", ERACOM_BCD_TO_STR );

	//Key Length
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, ( void *) &Len, 1, "COMMKEY_LMK_LEN", ERACOM_BINARY_TO_INT );

	//Format
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "FORMAT", ERACOM_BCD_TO_STR );

	Len = Len -1;

	if( Len % 2 == 0 )
		Len = Len * 2;
	else
		Len = ( Len * 2 ) - 1;

	RespBuffer += eracom_in( RespBuffer, DeviceCommKey_LMK, Len, "COMMKEY_LMK", ERACOM_BCD_TO_STR );
	return 1;
}

int EzEracomUtil :: composeGenerateNetworkCommKeyReq( const char *NetworkMasterKey, int KeyLen, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len = 0;
	unsigned char KeyFlags[ 5 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;

	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0402", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//KIS Specifier->Key Encryption Key Specifier

	//Length of KIS Specifier
	Len = KeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "KEK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( KeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "KEK-FORMAT", ERACOM_STR_TO_BCD );
	else if( KeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "KEK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "KEK-FORMAT", ERACOM_STR_TO_BCD );

	//KIS
	ReqBuffer += eracom_out( ( void * ) NetworkMasterKey, ReqBuffer, KeyLen, "KEK", ERACOM_STR_TO_BCD );

	//Key Flags
	//Bit 0   Single-length Data Key (DPK).
	//Bit 1   Single-length PIN encrypting key (PPK).
	//Bit 2   Single-length MAC key (MPK).
	//Bit 3   Single-length terminal master key (KTM).
	//Bit 4-7 Reserved. Must be zero.
	//Bit 8   Double-length Data Key (DPK).
	//Bit 9   Double-length PIN encrypting key (PPK).
	//Bit 10  Double-length MAC key (MPK).
	//Bit 11  Double-length terminal master key (KTM).
	//Bit 12  Encryption mode: 0 = ECB, 1 = CBC
	//Bit 13-15 Reserved. Must be zero.
	//Bit 0 is the least significant (rightmost) bit.
	//To generate a single-length MAC key, this field must be set to 0004
	//To generate a double-length PIN encrypting key and a single-length MAC key, the field must be set to 0204

	memset( KeyFlags, 0, sizeof( KeyFlags ) );
	if( KeyLen == 16 )
	{
		//Bit 1   Single-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 15 );
	}
	else if ( KeyLen == 32 )
	{
		//Bit 9   Double-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 7 );
	}
	else
	{
		//Bit 9   Double-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 7 );
	}
	ReqBuffer += eracom_out( ( void * ) KeyFlags, ReqBuffer, 2, "KeyFlags", ERACOM_MOVE );
	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeGenerateNetworkCommKeyReq( const char *ResponseBuffer, int KeyLen, char *NetworkCommKey_LMK, char *NetworkCommKey )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];
	int Len;

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;

	//No. of Keys
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "NKEYS", ERACOM_BCD_TO_STR );

	//Key Length
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, ( void * ) &Len, 1, "COMMKEY_KEK_LEN", ERACOM_BINARY_TO_INT );

	if( Len % 2 == 0 )
		Len = Len * 2;
	else
		Len = ( Len * 2 ) - 1;

	RespBuffer += eracom_in( RespBuffer, NetworkCommKey, Len, "COMMKEY_KEK", ERACOM_BCD_TO_STR );

	//Key Length
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, ( void * ) &Len, 1, "COMMKEY_LMK_LEN", ERACOM_BINARY_TO_INT );

	Len = Len -1;

	if( Len % 2 == 0 )
		Len = Len * 2;
	else
		Len = ( Len * 2 ) - 1;

	//Format
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "FORMAT", ERACOM_BCD_TO_STR );

	RespBuffer += eracom_in( RespBuffer, NetworkCommKey_LMK, Len, "COMMKEY_LMK", ERACOM_BCD_TO_STR );
	return 1;
}

int EzEracomUtil :: composeReceiveNetworkCommKeyReq( const char *NetworkMasterKey, int KeyLen, const char *NetworkCommKey_TMK, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	unsigned char KeyFlags[ 5 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;

	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0403", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//KIR Specifier->Key Encryption Key Specifier

	//Length of KIR Specifier
	Len = KeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "KEK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( KeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "KEK-FORMAT", ERACOM_STR_TO_BCD );
	else if( KeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "KEK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "KEK-FORMAT", ERACOM_STR_TO_BCD );

	//KIS
	ReqBuffer += eracom_out( ( void * ) NetworkMasterKey, ReqBuffer, KeyLen, "KEK", ERACOM_STR_TO_BCD );

	//Key Flags
	//Bit 0   Single-length Data Key (DPK).
	//Bit 1   Single-length PIN encrypting key (PPK).
	//Bit 2   Single-length MAC key (MPK).
	//Bit 3   Single-length terminal master key (KTM).
	//Bit 4-7 Reserved. Must be zero.
	//Bit 8   Double-length Data Key (DPK).
	//Bit 9   Double-length PIN encrypting key (PPK).
	//Bit 10  Double-length MAC key (MPK).
	//Bit 11  Double-length terminal master key (KTM).
	//Bit 12  Encryption mode: 0 = ECB, 1 = CBC
	//Bit 13-15 Reserved. Must be zero.
	//Bit 0 is the least significant (rightmost) bit.
	//To generate a single-length MAC key, this field must be set to 0004
	//To generate a double-length PIN encrypting key and a single-length MAC key, the field must be set to 0204

	memset( KeyFlags, 0, sizeof( KeyFlags ) );
	if( KeyLen == 16 )
	{
		//Bit 1   Single-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 15 );
	}
	else if ( KeyLen == 32 )
	{
		//Bit 9   Double-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 7 );
	}
	else
	{
		//Bit 9   Double-length PIN encrypting key (PPK).
		eracom_SetBitOn( KeyFlags, 7 );
	}
	ReqBuffer += eracom_out( ( void * ) KeyFlags, ReqBuffer, 2, "KeyFlags", ERACOM_MOVE );

	//Length of NetworkCommKey_TMK->Session Key
	Len = KeyLen / 2;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "COMMKEY_KEK-LEN", ERACOM_INT_TO_BINARY );

	//NetworkCommKey_TMK->Session Key
	ReqBuffer += eracom_out( ( void * ) NetworkCommKey_TMK, ReqBuffer, KeyLen, "COMMKEY_KEK", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeReceiveNetworkCommKeyReq( const char *ResponseBuffer, int KeyLen, char *NetworkCommKey_LMK )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];
	int Len;

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;

	//No. of Keys
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "NKEYS", ERACOM_BCD_TO_STR );

	//Key Length
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, ( void * ) &Len, 1, "COMMKEY_LEN", ERACOM_BINARY_TO_INT );

	Len = Len -1;

	if( Len % 2 == 0 )
		Len = Len * 2;
	else
		Len = ( Len * 2 ) - 1;

	//Format
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "FORMAT", ERACOM_BCD_TO_STR );

	RespBuffer += eracom_in( RespBuffer, NetworkCommKey_LMK, Len, "COMMKEY_LMK", ERACOM_BCD_TO_STR );
	return 1;
}

int EzEracomUtil :: composetranPinBlock_Device_NetworkReq( const char *PinBlock, const char *chn, const char *DeviceCommKey, int DeviceKeyLen, const char *AcqNetworkCommKey, int NetworkKeyLen, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	char AcctNoBlock[ 20 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;

	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0602", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//PINBlock
	ReqBuffer += eracom_out( ( void * ) PinBlock, ReqBuffer, 16, "PINBLOCK", ERACOM_STR_TO_BCD );

	//PPK Specifier
	//Length of PPK Specifier
	Len = DeviceKeyLen / 2 + 1 ;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PPK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( DeviceKeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else if( DeviceKeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );

	//PPK
	ReqBuffer += eracom_out( ( void * ) DeviceCommKey, ReqBuffer, DeviceKeyLen, "PPK", ERACOM_STR_TO_BCD );

	//PPK PIN Block Format
	ReqBuffer += eracom_out( ( void * ) "01", ReqBuffer, 2, "PPK-PINBLOCK-FORMAT", ERACOM_STR_TO_BCD );

	//Account No Block 12 right-most digits of chn excluding the check digit
	memset( AcctNoBlock, 0, sizeof( AcctNoBlock ) );
	strncpy( AcctNoBlock, chn + strlen( chn ) - 13, 12 );
	ReqBuffer += eracom_out( AcctNoBlock, ReqBuffer, 12, "ACCT-BLOCK", ERACOM_STR_TO_BCD );

	//PPK PIN Block Format
	ReqBuffer += eracom_out( ( void * ) "01", ReqBuffer, 2, "COMMKEY-PINBLOCK-FORMAT", ERACOM_STR_TO_BCD );

	//AcqNetwork Key Specifier

	//Length of KIR Specifier
	Len = NetworkKeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "COMMKEY-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( NetworkKeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "COMMKEY-FORMAT", ERACOM_STR_TO_BCD );
	else if( NetworkKeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "COMMKEY-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "COMMKEY-FORMAT", ERACOM_STR_TO_BCD );

	//NetworkCommKey
	ReqBuffer += eracom_out( ( void * ) AcqNetworkCommKey, ReqBuffer, NetworkKeyLen, "COMMKEY", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposetranPinBlock_Device_NetworkReq( const char *ResponseBuffer, char *TranPinBlock )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;

	//TranPINBlock
	RespBuffer += eracom_in( RespBuffer, TranPinBlock, 16, "TRAN-PINBLOCK", ERACOM_BCD_TO_STR );

	return 1;
}

int EzEracomUtil :: composeVerifyDevicePINReq( const char *chn, const char *PinBlock, const char *DeviceCommKey, int DeviceKeyLen, const char *EPVK, const char *DecimilizationTable, int PANValidationOffset, int PANValidationLength, const char *PinOffset, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	char AcctNoBlock[ 20 ], PANValidationData[ 20 ], PINOffsetData[ 20 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;
	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0603", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//PIN Block
	ReqBuffer += eracom_out( ( void * ) PinBlock, ReqBuffer, 16, "PIN-BLOCK", ERACOM_STR_TO_BCD );

	//PPK Specifier
	//Length of PPK Specifier
	Len = DeviceKeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PPK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( DeviceKeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else if( DeviceKeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );

	//PPK
	ReqBuffer += eracom_out( ( void * ) DeviceCommKey, ReqBuffer, DeviceKeyLen, "PPK", ERACOM_STR_TO_BCD );

	//PIN Block Format
	ReqBuffer += eracom_out( ( void * ) "01", ReqBuffer, 2, "PINBLOCK-FORMAT", ERACOM_STR_TO_BCD );

	//Account No Block 12 right-most digits of chn excluding the check digit
	memset( AcctNoBlock, 0, sizeof( AcctNoBlock ) );
	strncpy( AcctNoBlock, chn + strlen( chn ) - 13, 12 );
	ReqBuffer += eracom_out( ( void * ) AcctNoBlock, ReqBuffer, 12, "ACCT-BLOCK", ERACOM_STR_TO_BCD );

	//PVK Specifier

	if( strlen( EPVK ) == 2 )
	{
		ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 2, "PVK", ERACOM_STR_TO_BCD );
	}
	else if ( strlen( EPVK ) == 4 )
	{
		ReqBuffer += eracom_out( ( void * ) "02", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 4, "PVK", ERACOM_STR_TO_BCD );
	}
	else
	{
		//Length of PVK Specifier
		Len = strlen( EPVK ) / 2 + 1;
		ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PVK-LEN", ERACOM_INT_TO_BINARY );

		//Key Specification Format
		if( strlen( EPVK ) == 16 )
			ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else if( strlen( EPVK ) == 32 )
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );

		//PVK
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, strlen( EPVK ), "PVK", ERACOM_STR_TO_BCD );
	}

	//PAN Validation Data
	memset( PANValidationData, 0, sizeof( PANValidationData ) );
	strncpy( PANValidationData, chn + PANValidationOffset, PANValidationLength );
	if( strlen( PANValidationData ) < 16 )
		memset( PANValidationData + PANValidationLength, 'F', 16 - PANValidationLength );
	ReqBuffer += eracom_out( ( void * ) PANValidationData, ReqBuffer, 16, "PAN-VAL-DATA", ERACOM_STR_TO_BCD );

	//PIN Offset
	memset( PINOffsetData, 0, sizeof( PINOffsetData ) );
	strncpy( PINOffsetData, PinOffset, strlen( PinOffset ) );
	if( strlen( PINOffsetData ) < 12 )
		memset( PINOffsetData + strlen( PinOffset ), '0', 12 - strlen( PinOffset ) );
	ReqBuffer += eracom_out( ( void * ) PINOffsetData, ReqBuffer, 12, "PIN-OFFSET-DATA", ERACOM_STR_TO_BCD );

	//PIN Len
	ReqBuffer += eracom_out( ( void * ) "04", ReqBuffer, 	2, "PIN-LEN", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeVerifyDevicePINReq( const char *ResponseBuffer )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;
	else
		return 1;
}

int EzEracomUtil :: composeVerifyCVVReq( const char *chn, const char *ExpiryDate, const char *ServiceCode, const char *CVKA, const char *CVKB, const char *CVV, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	char CVVData[ 50 ], CVK[ 50 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;

	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0803", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//CVK Specifier

	memset( CVK, 0, sizeof( CVK ) );
	sprintf( CVK, "%s%s", CVKA, CVKB );

	if( strlen( CVK ) == 2 )
	{
		ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "CVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) CVK, ReqBuffer, 2, "CVK", ERACOM_STR_TO_BCD );
	}
	else if ( strlen( CVK ) == 4 )
	{
		ReqBuffer += eracom_out( ( void * ) "02", ReqBuffer, 2, "CVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) CVK, ReqBuffer, 4, "CVK", ERACOM_STR_TO_BCD );
	}
	else
	{
		//Length of CVK Specifier
		Len = strlen( CVK ) / 2 + 1;
		ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "CVK-LEN", ERACOM_INT_TO_BINARY );

		//Key Specification Format
		if( strlen( CVK ) == 16 )
			ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "CVK-FORMAT", ERACOM_STR_TO_BCD );
		else if( strlen( CVK ) == 32 )
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "CVK-FORMAT", ERACOM_STR_TO_BCD );
		else
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "CVK-FORMAT", ERACOM_STR_TO_BCD );

		//CVK
		ReqBuffer += eracom_out( ( void * ) CVK, ReqBuffer, strlen( CVK ), "CVK", ERACOM_STR_TO_BCD );
	}

	//CVVData
	memset( CVVData, 0, sizeof( CVVData ) );
	memset( CVVData, '0', 32 );
	sprintf( CVVData, "%s%s%s", chn, ExpiryDate, ServiceCode );
	ReqBuffer += eracom_out( ( void * ) CVVData, ReqBuffer, 32, "CVV-DATA", ERACOM_STR_TO_BCD );

	//CVV
	ReqBuffer += eracom_out( ( void * ) CVV, ReqBuffer, 2, "CVV", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeVerifyCVVReq( const char *ResponseBuffer )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;
	else
		return 1;
}

int EzEracomUtil :: composeVerifyNetworkPINReq( const char *chn, const char *PinBlock, const char *NetworkCommKey, int NetworkKeyLen, const char *EPVK, const char *DecimilizationTable, int PANValidationOffset, int PANValidationLength, const char *PinOffset, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	char AcctNoBlock[ 20 ], PANValidationData[ 20 ], PINOffsetData[ 20 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;
	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0603", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//PIN Block
	ReqBuffer += eracom_out( ( void * ) PinBlock, ReqBuffer, 16, "PIN-BLOCK", ERACOM_STR_TO_BCD );

	//PPK Specifier
	//Length of PPK Specifier
	Len = NetworkKeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PPK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( NetworkKeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else if( NetworkKeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );

	//PPK
	ReqBuffer += eracom_out( ( void * ) NetworkCommKey, ReqBuffer, NetworkKeyLen, "PPK", ERACOM_STR_TO_BCD );

	//PIN Block Format
	ReqBuffer += eracom_out( ( void * ) "01", ReqBuffer, 2, "PINBLOCK-FORMAT", ERACOM_STR_TO_BCD );

	//Account No Block 12 right-most digits of chn excluding the check digit
	memset( AcctNoBlock, 0, sizeof( AcctNoBlock ) );
	strncpy( AcctNoBlock, chn + strlen( chn ) - 13, 12 );
	ReqBuffer += eracom_out( ( void * ) AcctNoBlock, ReqBuffer, 12, "ACCT-BLOCK", ERACOM_STR_TO_BCD );

	//PVK Specifier

	if( strlen( EPVK ) == 2 )
	{
		ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 2, "PVK", ERACOM_STR_TO_BCD );
	}
	else if ( strlen( EPVK ) == 4 )
	{
		ReqBuffer += eracom_out( ( void * ) "02", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 4, "PVK", ERACOM_STR_TO_BCD );
	}
	else
	{
		//Length of PVK Specifier
		Len = strlen( EPVK ) / 2 + 1;
		ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PVK-LEN", ERACOM_INT_TO_BINARY );

		//Key Specification Format
		if( strlen( EPVK ) == 16 )
			ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else if( strlen( EPVK ) == 32 )
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );

		//PVK
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, strlen( EPVK ), "PVK", ERACOM_STR_TO_BCD );
	}

	//PAN Validation Data
	memset( PANValidationData, 0, sizeof( PANValidationData ) );
	strncpy( PANValidationData, chn + PANValidationOffset, PANValidationLength );
	if( strlen( PANValidationData ) < 16 )
		memset( PANValidationData + PANValidationLength, 'F', 16 - PANValidationLength );
	ReqBuffer += eracom_out( ( void * ) PANValidationData, ReqBuffer, 16, "PAN-VAL-DATA", ERACOM_STR_TO_BCD );

	//PIN Offset
	memset( PINOffsetData, 0, sizeof( PINOffsetData ) );
	strncpy( PINOffsetData, PinOffset, strlen( PinOffset ) );
	if( strlen( PINOffsetData ) < 12 )
		memset( PINOffsetData + strlen( PinOffset ), '0', 12 - strlen( PinOffset ) );
	ReqBuffer += eracom_out( ( void * ) PINOffsetData, ReqBuffer, 12, "PIN-OFFSET-DATA", ERACOM_STR_TO_BCD );

	//PIN Len
	ReqBuffer += eracom_out( ( void * ) "04", ReqBuffer, 	2, "PIN-LEN", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeVerifyNetworkPINReq( const char *ResponseBuffer )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;
	else
		return 1;
}

int EzEracomUtil :: composeGenDevicePINOffsetReq( const char *chn, const char *PinBlock, const char *DeviceCommKey, int DeviceKeyLen, const char *EPVK, const char *DecimilizationTable, int PANValidationOffset, int PANValidationLength, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	char AcctNoBlock[ 20 ], PANValidationData[ 20 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;
	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0604", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//PIN Block
	ReqBuffer += eracom_out( ( void * ) PinBlock, ReqBuffer, 16, "PIN-BLOCK", ERACOM_STR_TO_BCD );

	//PPK Specifier
	//Length of PPK Specifier
	Len = DeviceKeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PPK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( DeviceKeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else if( DeviceKeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );

	//PPK
	ReqBuffer += eracom_out( ( void * ) DeviceCommKey, ReqBuffer, DeviceKeyLen, "PPK", ERACOM_STR_TO_BCD );

	//PIN Block Format
	ReqBuffer += eracom_out( ( void * ) "01", ReqBuffer, 2, "PINBLOCK-FORMAT", ERACOM_STR_TO_BCD );

	//Account No Block 12 right-most digits of chn excluding the check digit
	memset( AcctNoBlock, 0, sizeof( AcctNoBlock ) );
	strncpy( AcctNoBlock, chn + strlen( chn ) - 13, 12 );
	ReqBuffer += eracom_out( ( void * ) AcctNoBlock, ReqBuffer, 12, "ACCT-BLOCK", ERACOM_STR_TO_BCD );

	//PVK Specifier

	if( strlen( EPVK ) == 2 )
	{
		ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 2, "PVK", ERACOM_STR_TO_BCD );
	}
	else if ( strlen( EPVK ) == 4 )
	{
		ReqBuffer += eracom_out( ( void * ) "02", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 4, "PVK", ERACOM_STR_TO_BCD );
	}
	else
	{
		//Length of PVK Specifier
		Len = strlen( EPVK ) / 2 + 1;
		ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PVK-LEN", ERACOM_INT_TO_BINARY );

		//Key Specification Format
		if( strlen( EPVK ) == 16 )
			ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else if( strlen( EPVK ) == 32 )
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );

		//PVK
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, strlen( EPVK ), "PVK", ERACOM_STR_TO_BCD );
	}

	//PAN Validation Data
	memset( PANValidationData, 0, sizeof( PANValidationData ) );
	strncpy( PANValidationData, chn + PANValidationOffset, PANValidationLength );
	if( strlen( PANValidationData ) < 16 )
		memset( PANValidationData + PANValidationLength, 'F', 16 - PANValidationLength );
	ReqBuffer += eracom_out( ( void * ) PANValidationData, ReqBuffer, 16, "PAN-VAL-DATA", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeGenDevicePINOffsetReq( const char *ResponseBuffer, char *PinOffset )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];
	char PINOffsetData[ 20 ];

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;

	//Offset
	memset( PINOffsetData, 0, sizeof( PINOffsetData ) );
	RespBuffer += eracom_in( RespBuffer, PINOffsetData, 12, "PIN-OFFSET-DATA", ERACOM_BCD_TO_STR );

	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "PIN-LEN", ERACOM_BCD_TO_STR );

	strncpy( PinOffset, PINOffsetData, atoi( TempStr ) );
	return 1;
}

int EzEracomUtil :: composeGenNetworkPINOffsetReq( const char *chn, const char *PinBlock, const char *NetworkCommKey, int NetworkKeyLen, const char *EPVK, const char *DecimilizationTable, int PANValidationOffset, int PANValidationLength, char *RequestBuffer )
{
	int BuffOffset = 0;
	char *ReqBuffer;
	char *BasePtr;
	int Len;
	char AcctNoBlock[ 20 ], PANValidationData[ 20 ];

	ReqBuffer = RequestBuffer;
	BasePtr = ReqBuffer;
	//Command Code
	ReqBuffer += eracom_out( ( void * ) "EE0604", ReqBuffer, 6, "COMMAND", ERACOM_STR_TO_BCD );

	//Function Modifier
	ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "FUNCTION-MODIFIER", ERACOM_STR_TO_BCD );

	//PIN Block
	ReqBuffer += eracom_out( ( void * ) PinBlock, ReqBuffer, 16, "PIN-BLOCK", ERACOM_STR_TO_BCD );

	//PPK Specifier
	//Length of PPK Specifier
	Len = NetworkKeyLen / 2 + 1;
	ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PPK-LEN", ERACOM_INT_TO_BINARY );

	//Key Specification Format
	if( NetworkKeyLen == 16 )
		ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else if( NetworkKeyLen == 32 )
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );
	else
		ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PPK-FORMAT", ERACOM_STR_TO_BCD );

	//PPK
	ReqBuffer += eracom_out( ( void * ) NetworkCommKey, ReqBuffer, NetworkKeyLen, "PPK", ERACOM_STR_TO_BCD );

	//PIN Block Format
	ReqBuffer += eracom_out( ( void * ) "01", ReqBuffer, 2, "PINBLOCK-FORMAT", ERACOM_STR_TO_BCD );

	//Account No Block 12 right-most digits of chn excluding the check digit
	memset( AcctNoBlock, 0, sizeof( AcctNoBlock ) );
	strncpy( AcctNoBlock, chn + strlen( chn ) - 13, 12 );
	ReqBuffer += eracom_out( ( void * ) AcctNoBlock, ReqBuffer, 12, "ACCT-BLOCK", ERACOM_STR_TO_BCD );

	//PVK Specifier

	if( strlen( EPVK ) == 2 )
	{
		ReqBuffer += eracom_out( ( void * ) "00", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 2, "PVK", ERACOM_STR_TO_BCD );
	}
	else if ( strlen( EPVK ) == 4 )
	{
		ReqBuffer += eracom_out( ( void * ) "02", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, 4, "PVK", ERACOM_STR_TO_BCD );
	}
	else
	{
		//Length of PVK Specifier
		Len = strlen( EPVK ) / 2 + 1;
		ReqBuffer += eracom_out( ( void * ) &Len, ReqBuffer, 1, "PVK-LEN", ERACOM_INT_TO_BINARY );

		//Key Specification Format
		if( strlen( EPVK ) == 16 )
			ReqBuffer += eracom_out( ( void * ) "10", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else if( strlen( EPVK ) == 32 )
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );
		else
			ReqBuffer += eracom_out( ( void * ) "11", ReqBuffer, 2, "PVK-FORMAT", ERACOM_STR_TO_BCD );

		//PVK
		ReqBuffer += eracom_out( ( void * ) EPVK, ReqBuffer, strlen( EPVK ), "PVK", ERACOM_STR_TO_BCD );
	}

	//PAN Validation Data
	memset( PANValidationData, 0, sizeof( PANValidationData ) );
	strncpy( PANValidationData, chn + PANValidationOffset, PANValidationLength );
	if( strlen( PANValidationData ) < 16 )
		memset( PANValidationData + PANValidationLength, 'F', 16 - PANValidationLength );
	ReqBuffer += eracom_out( ( void * ) PANValidationData, ReqBuffer, 16, "PAN-VAL-DATA", ERACOM_STR_TO_BCD );

	return ( ReqBuffer - BasePtr );
}

int EzEracomUtil :: decomposeGenNetworkPINOffsetReq( const char *ResponseBuffer, char *PinOffset )
{
	char *RespBuffer;
	char TempStr[ ERACOM_UTIL_BUF_SIZE + 1 ];
	char PINOffsetData[ 20 ];

	RespBuffer = ( char * ) ResponseBuffer;

	//Command Code
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 6, "COMMAND", ERACOM_BCD_TO_STR );

	//ResponseCode
	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "RESPCODE", ERACOM_BCD_TO_STR );
	if( atoi( TempStr ) != 0 )
		return -1;

	//Offset
	memset( PINOffsetData, 0, sizeof( PINOffsetData ) );
	RespBuffer += eracom_in( RespBuffer, PINOffsetData, 12, "PIN-OFFSET-DATA", ERACOM_BCD_TO_STR );

	memset( TempStr, 0, sizeof( TempStr ) );
	RespBuffer += eracom_in( RespBuffer, TempStr, 2, "PIN-LEN", ERACOM_BCD_TO_STR );

	strncpy( PinOffset, PINOffsetData, atoi( TempStr ) );
	return 1;
}

