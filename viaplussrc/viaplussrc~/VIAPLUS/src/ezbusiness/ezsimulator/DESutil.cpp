/****************************************************************************

	File Name : DESUtil.cpp
	Purpose   : Shared Library for DES Encryption & Decryption

****************************************************************************/


#include <ezbusiness/DESUtil.h>

DesAlgo::DesAlgo()
{

}

DesAlgo::~DesAlgo()
{

}

DesAlgo theApp;

 void DesAlgo::UnPack(char * p1, char * p2, int length )
{
	int    i;

    for( i = 0; i < length; i++ )
		    sprintf( p1 + ( i << 1 ), "%02x", p2[i] & 0377 );
}

void DesAlgo::Pack(char * p1, char * p2, int length )
{
	int    i, x;

    for( i = 0; i < length; i += 2 )
	{
		     sscanf (p2 + i, "%2x", &x);
    		 *p1++ = x;
    }
}

 void DesAlgo::Des(int type, char * key, char * tinp, char * tout, int tlen )
{
 int    i,x;
 DES kbit;
 DES tbit;
 DES * k = &kbit;
 DES * t = &tbit;

    tlen &= ~7;
    ROW (k) = 0;
    ROW (t) = 0;

    for( i = 0; i < 64; i++ ) {
			BIT(k)[ 0 ][ i ] = key[ i >> 3 ] >> 7 - ( i & 7 ) & 1;

    }
    DesTranspose( k, (char *)DES_KeyTr1, 56 );       /* initial key transposition */
    for( tlen += (int) tinp; (int) tinp < tlen; tinp += 8, tout += 8 ) {
		   for( i = 0; i < 64; i++ ) {
				BIT(t)[ ROW(t) ][ i ] = tinp[ i >> 3 ] >> 7 - ( i & 7 ) & 1;

    	 }
	     DesTranspose( t, (char *)DES_InitialTr, 64 );   /* initial text transposition */
	     for( i = 0; i < 16; i++ )       /* here come the 16 iterations */
  	   {
    	     DesTranspose( t, (char *)DES_Swap, 64 );  /* swap left right halves */
      	   DesF( type, i, k, t );     /* compute f(r[i-1],k[i]) */
        	 ROW(t) ^= 1;
	         for( x = 32; x < 64; x++ )
			          BIT(t)[ ROW(t) ][ x ] ^= BIT(t)[ ROW(t) ^ 1 ][ x ];
     	 }
	     DesTranspose( t, (char *)DES_Swap, 64 );      /* swap left right halves */
  	   DesTranspose( t, (char *)DES_FinalTr, 64 );   /* final transposition */
	     for( i = 0; i < 8; i++ )
  	       for( tout[ i ] = 0, x = 0; x < 8; x++ )
    		      tout[ i ] |= BIT(t)[ ROW(t) ][ (i << 3) + x ] << 7 - x;
    }

}

void DesAlgo::DesTranspose(DES * p, char * tab, int n )
{
    while( --n >= 0 )
		     BIT(p)[ ROW(p) ^ 1 ][ n ] = BIT(p)[ ROW(p) ][ tab[ n ] - 1 ];
    ROW(p) ^= 1;
}

void DesAlgo::DesRotateEncr( DES * k )
{
 int    i;

    for( i = 0; i < 55; i++ )
		     BIT (k)[ROW (k) ^ 1][i] = BIT (k)[ROW (k)][i + 1];
    BIT(k)[ ROW(k) ^ 1 ][ 27 ] = BIT(k)[ ROW(k) ][ 0 ];
    BIT(k)[ ROW(k) ^ 1 ][ 55 ] = BIT(k)[ ROW(k) ][ 28 ];
    ROW(k) ^= 1;
}

void DesAlgo::DesRotateDecr( DES * k)
{
 int    i;

    for( i = 1; i < 56; i++ )
		     BIT (k)[ROW (k) ^ 1][i] = BIT (k)[ROW (k)][i - 1];
    BIT(k)[ ROW(k) ^ 1 ][ 0 ] = BIT(k)[ ROW(k) ][ 27 ];
    BIT(k)[ ROW(k) ^ 1 ][ 28 ] = BIT(k)[ ROW(k) ][ 55 ];
    ROW(k) ^= 1;
}

void DesAlgo::DesF(int type, int n, DES * k, DES * t )  /* f(r[i-1], k[i]) */
{
 int    i, x;

    DesTranspose(t, (char *)DES_Etr, 48);         /* expand data block to 48 bits */
    if( !type ) {
	     for( i=DES_Rots[ n ]; i > 0; i-- )
         DesRotateEncr( k );
    }
    DesTranspose( k, (char *)DES_KeyTr2, 48 );
    for( i = 0; i < 48; i++ )
		    BIT(t)[ ROW(t) ][ i ] ^= BIT(k)[ ROW(k) ][ i ];
    ROW(k) ^= 1;
    if( type ) {
	  	  for( i = DES_Rots[ 15-n ]; i > 0; i-- )
  	  	     DesRotateDecr( k );
    }
    for( i = 0; i < 8; i++ ) {
		    x = BIT(t)[ ROW(t) ][ 6 * i ] << 5;
    	  x |= BIT(t)[ ROW(t) ][ 6 * i + 5 ] << 4;
	      for( n = 1; n < 5; n++ )
   		      x |= BIT(t)[ ROW(t) ][ 6 * i + n ] << 4 - n;
	      for( n = 0; n < 4; n++ )
   		      BIT(t)[ ROW(t) ][ (i << 2) + n ] = DES_S[ i ][ x ] >> 3 - n & 1;
    }
    for( i = 0; i < 32; i++ )
		    BIT(t)[ ROW(t) ][ i + 32 ] = BIT(t)[ ROW(t) ][ DES_Ptr[ i ] - 1 ];
}

void DesAlgo::MapDecTable(char * EncrText, char * DecTable, char * IPin )
{
 int i,j;

		for( i=0; i < ( int ) strlen( EncrText ); i++ )
			for( j=0; j < ( int ) strlen( DES_HexTable ); j++ )
				if( EncrText[ i ] == DES_HexTable[ j ] )
					IPin[ i ] = DecTable[ j ];
		IPin[ i ] = '\x0';
}

int DesAlgo::Mod10Add(int Num1, int Num2 )
{
 int No1, No2, Idx, Num, Temp;

 	Idx = Num = Temp = 0;
	No1 = Num1;
	No2 = Num2;
	while( ( No1 > 0 ) && ( No2 > 0 ) ) {
		Temp = ( No1 % 10 ) + ( No2 % 10 );
		No1 /= 10;
		No2 /= 10;
		if( Temp >= 10 )
			Temp -= 10;
		Num += Temp * int(pow( 10, Idx ));
		Idx++;
		Temp = 0;
	}
	return( Num );
}

void DesAlgo::DesMain(int type, char * bskey, char * upkt )
{
 int 		tlen;
 char		key[ 8 ];
 char   text[ 32 ];
 char   encrtext[ 32 ];

	tlen = strlen( bskey );
     Pack( key, bskey, tlen );		/* tlen -> 16  */
		 tlen = strlen( upkt );
     Pack( text, upkt, tlen << 1 );
     Des( type, key, text, encrtext, tlen );

     UnPack( tmp_deskey, encrtext, tlen );

     tmp_deskey[ tlen ] = '\x0';

		 for( tlen = 0; tmp_deskey[ tlen ]; tlen++ )
					tmp_deskey[ tlen ] = toupper( tmp_deskey[ tlen ] );
}

void DesAlgo::Encrypt( char *bskey, char *upkt, char *etext )
{
	memset( tmp_deskey, 0, sizeof( tmp_deskey ) );
//	DesMain( 0, bskey, upkt );
	DesMain( 0, upkt, bskey );
	strcpy( etext, tmp_deskey );
}

void DesAlgo::Decrypt( char *bskey, char *upkt, char *etext )
{
	memset( tmp_deskey, 0, sizeof( tmp_deskey ) );
//	DesMain( 1, bskey, upkt );
	DesMain( 1, upkt, bskey );
	strcpy( etext, tmp_deskey );
}

