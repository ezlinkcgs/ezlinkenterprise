#ifndef _EZDEBUGUTIL_H
#define _EZDEBUGUTIL_H

#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

class EzDebugUtil
{
	private:
		FILE *debugfd;
		int DebugLevel;
		char debugname[ 100 ], processname[ 100 ];
	public:
		EzDebugUtil();
		~EzDebugUtil();
		int openDebug( const char *, const char * );
		void SetDebug();
		void closeDebug();
		int trace( const char *format,...);
		int hex_dump( unsigned char *, unsigned int );
};

#endif // _EZDEBUGUTIL_H_

