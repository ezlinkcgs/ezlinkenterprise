#ifndef EZCFG_UTIL_H_
#define EZCFG_UTIL_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>

#define CFG_UTIL_BUF_SIZE   1024
#define CFG_UTIL_LINE_SIZE  250
#define CFG_UTIL_PARAM_LEN  150
#define CFG_UTIL_GROUP_NAME_SIZE  150

#define CFG_ERR_NOERROR		1
#define CFG_ERR_ENV_FAILED	-1
#define CFG_ERR_OPEN_FAILED	-2
#define CFG_ERR_NOT_OPENED	-3
#define CFG_ERR_NOT_FOUND	-4
#define CFG_ERR_SYNTAX_ERR	-5

#define GROUP_SEPARATOR  '#'
static const char *START_GROUP_DEF = "_START_DEF";
static const char *END_GROUP_DEF = "END_DEF";

class EzCfgUtil
{
	private:
		bool CLOSE_FLAG, NEXT_LINE, found, OPEN_FLAG, start_flg, end_flg;
		char buf[ CFG_UTIL_BUF_SIZE + 1 ], gpname[ CFG_UTIL_GROUP_NAME_SIZE + 1 ];
		FILE *fp;
		char line_str[ CFG_UTIL_LINE_SIZE + 1 ];
		char param_val[ CFG_UTIL_PARAM_LEN + 1 ];
		int offset, boffset, param_count, fld_count, gpcnt, ngroup, gpcount, start_group, nparam, cfg_errno;
		
	public:

		EzCfgUtil();
		~EzCfgUtil();
		int cfg_open( const char * );
		void cfg_close();
		void get_line();
		bool blank_line();
		void get_param();
		int cfg_search( const char *, char *, int );
		int cfg_param_count( const char * );
		int cfg_group_count( const char * );
		int cfg_count_param( const char * );
		int cfg_get_param( const char *, char *, int );
		void get_param_count();
		void get_gpname( const char *, char *, int );
		int get_gpcount( const char * );
		void cfg_fetch_error( char * );

};

#endif
				
		
