#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv )
{
	FILE *fp_input, *fp_output;
	int InputData, OutputData;

	if( argc != 3 )
	{
		printf( "Usage <encryptfile> <SrcFileName> <EncFileName>\n" );
		return -1;
	}
	fp_input = fopen( argv[ 1 ] , "r" );
	fp_output = fopen( argv[ 2 ], "w" );

	if( fp_input == NULL )
	{
		printf("\nError in Opening File[%s]\n", argv[ 1 ] );
		return -1;
	}

	if( fp_output == NULL )
	{
		printf("\nError in Opening File[%s]\n", argv[ 2 ] );
		return -1;
	}

	while( !feof( fp_input ) )
	{
		InputData = fgetc( fp_input );
		OutputData = InputData + 100;
		fputc( OutputData, fp_output );
	}

	fclose( fp_input );
	fclose( fp_output );
	return 1;
}


