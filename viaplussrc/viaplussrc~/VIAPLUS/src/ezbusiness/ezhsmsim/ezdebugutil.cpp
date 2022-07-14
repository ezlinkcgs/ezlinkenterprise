#include "ezdebugutil.h"

EzDebugUtil :: EzDebugUtil()
{
}

EzDebugUtil :: ~EzDebugUtil()
{
	fclose(debugfd);
}

int EzDebugUtil :: openDebug( const char *filename, const char *processName )
{
	memset( debugname, 0, sizeof( debugname ) );
	strcpy( debugname, filename );
	memset( processname, 0, sizeof( processname ) );
	strcpy( processname, processName );
	debugfd = fopen( debugname, "a" );
	if( debugfd == NULL )
		return -1;
	else
		return 1;
}

void EzDebugUtil :: closeDebug()
{
	fclose( debugfd );
}

int EzDebugUtil :: trace( const char *format,...)
{
	struct tm *timenow;
	char message[ 1024 ];
	va_list ap;
	time_t t = 0;
	t = time(&t);
	timenow = localtime(&t);
	va_start( ap, format );
	memset( message, 0, sizeof( message ) );
	sprintf( message,"[%02d/%02d/%02d][%02d:%02d:%02d][%s][%u]", timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year % 100, timenow->tm_hour, timenow->tm_min, timenow->tm_sec, processname, ( unsigned int ) getpid());
	fprintf( debugfd, "%s", message );
	vfprintf(debugfd,format,ap);
	fprintf(debugfd,"\n");
	fflush(debugfd);
	va_end(ap);
	return 0;
}

int EzDebugUtil :: hex_dump( unsigned char * message, unsigned int len )
{
	unsigned int count = 1;
	int indx ;
	fprintf( debugfd , "\n" );

	while( count <= len )
	{
		for( indx = 1; ( indx <= 16 ) && ( count <= len ); indx++, count++, message++ )
			fprintf( debugfd, "%02x ", *message );
		message -= indx - 1 ;
		count -= indx - 1  ;
		while( indx++ <= 16 )
			fprintf( debugfd, "   " );
		fprintf( debugfd, "\t" );
		for( indx = 1; ( indx <= 16 ) && ( count <= len ); indx++, count++, message++ )
			if ( isprint( *message ) )
				fprintf( debugfd, "%c", *message );
			else
				fprintf( debugfd, "." );
		fprintf( debugfd, "\n");
	}
	fprintf( debugfd, "\n" );
	fflush( debugfd );
	return( 0 );
}

