#include <ezbusiness/bittools.h>



int BitTools :: SetBitOn( unsigned char * bitmap, int bit )
{
	if( IsBitSet( bitmap, bit ) )
		return 0;

	if ( bit == 0 )
		return 0;

	int byte_offset = bit/8;
	int bit_offset = bit%8;
	
	if ( bit_offset == 0 )
	{
		byte_offset --;
		bit_offset = 8 ;
	}
	*( bitmap+byte_offset ) = ( *(bitmap+byte_offset) | ( 0x80 >> ( bit_offset - 1 ) ) ) ; 
}



int BitTools :: SetBitOff( unsigned char * bitmap, int bit )
{
	unsigned char x = 1;
	if( !IsBitSet( bitmap, bit ) )
		return 0;
	if ( bit == 0 )
		return 0;
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
//	*( bitmap+byte_offset ) = ( *(bitmap+byte_offset) & ( 0x7F >> ( bit_offset - 1 ) ) ) ; 
}


bool BitTools :: IsBitSet( unsigned char * bitmap, int bit )
{
	if ( bit == 0 )
		return 0;
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

