
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[21];
};
static struct sqlcxp sqlfpn =
{
    20,
    "ezguicontrollerdb.pc"
};


static unsigned int sqlctx = 79436651;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
            short *cud;
   unsigned char  *sqlest;
            char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
            void  *sqhstv[27];
   unsigned int   sqhstl[27];
            int   sqhsts[27];
            void  *sqindv[27];
            int   sqinds[27];
   unsigned int   sqharm[27];
   unsigned int   *sqharc[27];
   unsigned short  sqadto[27];
   unsigned short  sqtdso[27];
} sqlstm = {12,27};

/* SQLLIB Prototypes */
extern sqlcxt ( void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * );
extern sqlcx2t( void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * );
extern sqlbuft( void **, char * );
extern sqlgs2t( void **, char * );
extern sqlorat( void **, unsigned int *, void * );

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem( unsigned char *, signed int * );

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,254,0,4,55,0,0,11,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,
0,0,2,3,0,0,2,5,0,0,2,1,0,0,2,1,0,0,1,5,0,0,
64,0,0,2,138,0,4,117,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,2,1,0,0,1,5,0,0,
99,0,0,3,165,0,4,160,0,0,6,1,0,1,0,2,5,0,0,2,3,0,0,2,3,0,0,2,1,0,0,2,1,0,0,1,5,
0,0,
138,0,0,4,164,0,4,207,0,0,5,1,0,1,0,2,5,0,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
173,0,0,5,108,0,4,249,0,0,3,1,0,1,0,2,5,0,0,2,3,0,0,1,5,0,0,
200,0,0,6,61,0,4,278,0,0,1,1,0,1,0,1,5,0,0,
219,0,0,7,201,0,4,316,0,0,8,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,1,5,0,0,
266,0,0,8,300,0,4,385,0,0,11,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,5,0,0,1,5,0,0,
325,0,0,9,240,0,4,462,0,0,10,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
380,0,0,10,202,0,4,531,0,0,8,1,0,1,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,1,5,0,0,
427,0,0,11,129,0,4,588,0,0,5,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
462,0,0,12,152,0,4,633,0,0,5,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
497,0,0,13,104,0,5,680,0,0,4,4,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
528,0,0,14,0,0,29,689,0,0,0,0,0,1,0,
543,0,0,15,73,0,4,709,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
566,0,0,16,325,0,4,761,0,0,14,1,0,1,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,1,0,0,
2,1,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
637,0,0,17,130,0,4,832,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,1,5,0,0,
672,0,0,18,274,0,4,880,0,0,1,1,0,1,0,1,5,0,0,
691,0,0,19,141,0,4,930,0,0,6,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,3,0,0,1,
5,0,0,
730,0,0,20,627,0,4,999,0,0,19,1,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,
2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,
0,2,3,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
821,0,0,21,656,0,3,1071,0,0,27,27,0,1,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,5,0,0,1,3,0,0,
944,0,0,22,0,0,29,1136,0,0,0,0,0,1,0,
959,0,0,23,503,0,3,1237,0,0,22,22,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,
0,1,1,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
1062,0,0,24,0,0,29,1291,0,0,0,0,0,1,0,
1077,0,0,25,503,0,3,1357,0,0,22,22,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,
0,1,1,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
1180,0,0,26,0,0,29,1411,0,0,0,0,0,1,0,
1195,0,0,27,59,0,5,1431,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
1218,0,0,28,0,0,29,1437,0,0,0,0,0,1,0,
1233,0,0,29,477,0,5,1500,0,0,19,19,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,
1324,0,0,30,0,0,29,1523,0,0,0,0,0,1,0,
1339,0,0,31,658,0,3,1557,0,0,27,27,0,1,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,5,0,0,1,3,0,0,
1462,0,0,32,0,0,29,1621,0,0,0,0,0,1,0,
1477,0,0,33,67,0,4,1637,0,0,2,1,0,1,0,2,5,0,0,1,3,0,0,
1500,0,0,34,92,0,4,1666,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
1523,0,0,35,194,0,4,1706,0,0,7,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,1,5,0,0,
1566,0,0,36,147,0,4,1755,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
1597,0,0,37,400,0,4,1825,0,0,17,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,
0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,3,
0,0,2,5,0,0,1,5,0,0,
1680,0,0,38,120,0,4,1905,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
1711,0,0,39,85,0,4,1941,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
1734,0,0,40,119,0,4,1973,0,0,4,1,0,1,0,2,5,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
1765,0,0,41,223,0,4,2026,0,0,9,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,
2,1,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
1816,0,0,42,133,0,4,2082,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
1847,0,0,43,123,0,4,2123,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
};


#include <ezdb/eznetwork.h>
#include <ezdb/eznetworkecho.h>
#include <ezdb/eznetworkreplay.h>
#include <ezdb/ezechoproperty.h>
#include <ezdb/eznetworkbusday.h>
#include <ezbusiness/ezbusinesstypes.h>
#include <ezlink/ezinstdbtypes.h>
#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezdb/eznetworkkey.h>
#include <ezdb/ezsecurity.h>
#include <ezbusiness/ezatmkey.h>
#include <ezdb/ezatmdenomstatus.h>
#include <ezbusiness/ezposdbtypes.h>
#include <ezlink/ezalertdbtypes.h>

int readEzNetwork( const char *I_NetworkId, struct EzNetwork *eznetwork_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char Input_NetworkId[ 17 ];
		char NetworkName[ 33 ];
		char NetworkPropertyId[ 11 ];
		int TimeOut;
		char ChannelName[ 33 ];
		char PortName[ 33 ];
		int NetworkStatus;
		char InstId[ 13 ];
		char KeyReq;
		char CutOverReq;
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR NetworkName IS STRING(33); */ 

	/* EXEC SQL VAR NetworkPropertyId IS STRING(11); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR PortName IS STRING(33); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
	memset( NetworkName, 0, sizeof( NetworkName ) );
	memset( NetworkPropertyId, 0, sizeof( NetworkPropertyId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( PortName, 0, sizeof( PortName ) );
	memset( InstId, 0, sizeof( InstId ) );
	
	strcpy( Input_NetworkId, I_NetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(NETWORKID),
		RTRIM(NETWORKNAME),
		RTRIM(NETWORKPROPERTYID),
		TIMEOUT,
		RTRIM(CHANNELNAME),
		RTRIM(PORTNAME),
		NETWORKSTATUS,
		RTRIM(INSTID),
		KEYREQ,
		CUTOVERREQ
	INTO
		:NetworkId,
		:NetworkName,
		:NetworkPropertyId,
		:TimeOut,
		:ChannelName,
		:PortName,
		:NetworkStatus,
		:InstId,
		:KeyReq,
		:CutOverReq
	FROM EZNETWORK WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NETWORKID) ,RTRIM(NETWORKNAME) ,RTRIM(NETWORKPR\
OPERTYID) ,TIMEOUT ,RTRIM(CHANNELNAME) ,RTRIM(PORTNAME) ,NETWORKSTATUS ,RTRIM(\
INSTID) ,KEYREQ ,CUTOVERREQ into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9  from\
 EZNETWORK where RTRIM(NETWORKID)=:b10";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)NetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)NetworkName;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)NetworkPropertyId;
 sqlstm.sqhstl[2] = (unsigned int  )11;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&TimeOut;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)ChannelName;
 sqlstm.sqhstl[4] = (unsigned int  )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)PortName;
 sqlstm.sqhstl[5] = (unsigned int  )33;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&NetworkStatus;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)InstId;
 sqlstm.sqhstl[7] = (unsigned int  )13;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&KeyReq;
 sqlstm.sqhstl[8] = (unsigned int  )1;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&CutOverReq;
 sqlstm.sqhstl[9] = (unsigned int  )1;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)Input_NetworkId;
 sqlstm.sqhstl[10] = (unsigned int  )17;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
   
	strcpy( eznetwork_ptr->NetworkId, NetworkId );
	strcpy( eznetwork_ptr->NetworkName, NetworkName );
	strcpy( eznetwork_ptr->NetworkPropertyId, NetworkPropertyId );
	eznetwork_ptr->TimeOut = TimeOut;
	strcpy( eznetwork_ptr->ChannelName, ChannelName );
	strcpy( eznetwork_ptr->PortName, PortName );
	eznetwork_ptr->NetworkStatus = NetworkStatus;
	strcpy( eznetwork_ptr->InstId, InstId );
	eznetwork_ptr->KeyReq = KeyReq;
	eznetwork_ptr->CutOverReq = CutOverReq;
	return sqlca.sqlcode;	
}

int readEzNetworkEcho( const char *I_NetworkId, struct EzNetworkEcho *eznetworkecho_ptr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char NetworkId[ 17 ];
        char Input_NetworkId[ 17 ];
        char EchoPropertyId[ 17 ];
        char EchoProperty;
        char LogOnReq;
    /* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

    /* EXEC SQL VAR NetworkId IS STRING(17); */ 

    /* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR EchoPropertyId IS STRING(17); */ 

	
    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
    memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );

    strcpy( Input_NetworkId, I_NetworkId );

    /* EXEC SQL SELECT
        RTRIM(NETWORKID),
        RTRIM(ECHOPROPERTYID),
        ECHOPROPERTY,
        LOGONREQ
    INTO
        :NetworkId,
        :EchoPropertyId,
        :EchoProperty,
        :LogOnReq
	FROM EZNETWORKECHO WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(NETWORKID) ,RTRIM(ECHOPROPERTYID) ,ECHOPROPE\
RTY ,LOGONREQ into :b0,:b1,:b2,:b3  from EZNETWORKECHO where RTRIM(NETWORKID)=\
:b4";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )64;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)NetworkId;
    sqlstm.sqhstl[0] = (unsigned int  )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)EchoPropertyId;
    sqlstm.sqhstl[1] = (unsigned int  )17;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void  *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)&EchoProperty;
    sqlstm.sqhstl[2] = (unsigned int  )1;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void  *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void  *)&LogOnReq;
    sqlstm.sqhstl[3] = (unsigned int  )1;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void  *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void  *)Input_NetworkId;
    sqlstm.sqhstl[4] = (unsigned int  )17;
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         void  *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



    if( sqlca.sqlcode != 0 )
        return sqlca.sqlcode;

    strcpy( eznetworkecho_ptr->NetworkId, NetworkId );
    strcpy( eznetworkecho_ptr->EchoPropertyId, EchoPropertyId ); 
    eznetworkecho_ptr->EchoProperty = EchoProperty;
	eznetworkecho_ptr->LogOnReq = LogOnReq;
    return 0;
}

int readEzNetworkReplay( const char *I_NetworkId, struct EzNetworkReplay *eznetworkreplay_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char Input_NetworkId[ 17 ];
		int ReplayInterval;
		int ReplayLookUpInterval;
		char ReplayProperty;
		char ReplayAction;
    	/* EXEC SQL END DECLARE SECTION; */ 


        int i = 0;

        /* EXEC SQL VAR NetworkId IS STRING(17); */ 

        /* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 


	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );

	strcpy( Input_NetworkId, I_NetworkId );

	/* EXEC SQL SELECT
		RTRIM(NETWORKID),
		REPLAYINTERVAL,
		REPLAYLOOKUPINTERVAL,
		REPLAYPROPERTY,
		REPLAYACTION
	INTO
		:NetworkId,
		:ReplayInterval,
		:ReplayLookUpInterval,
		:ReplayProperty,
		:ReplayAction
	FROM EZNETWORKREPLAY WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NETWORKID) ,REPLAYINTERVAL ,REPLAYLOOKUPINTERVA\
L ,REPLAYPROPERTY ,REPLAYACTION into :b0,:b1,:b2,:b3,:b4  from EZNETWORKREPLAY\
 where RTRIM(NETWORKID)=:b5";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )99;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)NetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&ReplayInterval;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&ReplayLookUpInterval;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&ReplayProperty;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&ReplayAction;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)Input_NetworkId;
 sqlstm.sqhstl[5] = (unsigned int  )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	if( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( eznetworkreplay_ptr->NetworkId, NetworkId );
	eznetworkreplay_ptr->ReplayInterval = ReplayInterval;
	eznetworkreplay_ptr->ReplayLookUpInterval = ReplayLookUpInterval;
	eznetworkreplay_ptr->ReplayProperty = ReplayProperty;
	eznetworkreplay_ptr->ReplayAction = ReplayAction;

	return 0;

}

int readEzNetworkBusDay( const char *I_NetworkId, struct EzNetworkBusDay *eznetworkbusday_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char Input_NetworkId[ 17 ];
		char CutOverUseFlag;
		int CutOverDate;
		int CutOverTime;
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
	
	strcpy( Input_NetworkId, I_NetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(NETWORKID),
		CUTOVERUSEFLAG,
		TO_NUMBER(TO_CHAR(CUTOVERDATE,'DDMMYY')),
		CUTOVERTIME
	INTO
		:NetworkId,
		:CutOverUseFlag,
		:CutOverDate,
		:CutOverTime
	FROM EZNETWORKBUSDAY WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NETWORKID) ,CUTOVERUSEFLAG ,TO_NUMBER(TO_CHAR(C\
UTOVERDATE,'DDMMYY')) ,CUTOVERTIME into :b0,:b1,:b2,:b3  from EZNETWORKBUSDAY \
where RTRIM(NETWORKID)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )138;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)NetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&CutOverUseFlag;
 sqlstm.sqhstl[1] = (unsigned int  )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&CutOverDate;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&CutOverTime;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_NetworkId;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
		
	strcpy( eznetworkbusday_ptr->NetworkId, NetworkId );
	eznetworkbusday_ptr->CutOverUseFlag = CutOverUseFlag;
	eznetworkbusday_ptr->CutOverDate = CutOverDate;
	eznetworkbusday_ptr->CutOverTime = CutOverTime;
   
	return sqlca.sqlcode;	
}


int readEzEchoProperty( const char *I_EchoPropertyId, struct EzEchoProperty *ezechoproperty_ptr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char EchoPropertyId[ 17 ];
        char Input_EchoPropertyId[ 17 ];
        int EchoInterval;
   	/* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

    /* EXEC SQL VAR EchoPropertyId IS STRING(17); */ 

    /* EXEC SQL VAR Input_EchoPropertyId IS STRING(17); */ 

	
	memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
	memset( Input_EchoPropertyId, 0, sizeof( Input_EchoPropertyId ) );
    
    strcpy( Input_EchoPropertyId, I_EchoPropertyId );

    /* EXEC SQL SELECT
        RTRIM(ECHOPROPERTYID),
        ECHOINTERVAL
    INTO
        :EchoPropertyId,
        :EchoInterval
	FROM EZECHOPROPERTY WHERE RTRIM(ECHOPROPERTYID)=:Input_EchoPropertyId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(ECHOPROPERTYID) ,ECHOINTERVAL into :b0,:b1  \
from EZECHOPROPERTY where RTRIM(ECHOPROPERTYID)=:b2";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )173;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)EchoPropertyId;
    sqlstm.sqhstl[0] = (unsigned int  )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)&EchoInterval;
    sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void  *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)Input_EchoPropertyId;
    sqlstm.sqhstl[2] = (unsigned int  )17;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void  *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



    if( sqlca.sqlcode != 0 )
        return sqlca.sqlcode;

    strcpy( ezechoproperty_ptr->EchoPropertyId, EchoPropertyId );
    ezechoproperty_ptr->EchoInterval = EchoInterval;

    return 0;

}
	
int readSecurityTable( const char *SecurityId )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char Input_SecurityId[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR Input_SecurityId IS STRING(17); */ 

	
	memset( Input_SecurityId, 0, sizeof( Input_SecurityId ) );
	strcpy( Input_SecurityId, SecurityId );
	
	/* EXEC SQL SELECT COUNT(*) FROM EZSECURITY WHERE RTRIM(SECURITYID) = :Input_SecurityId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select count(*)   from EZSECURITY where RTRIM(SECURITYID)=:b\
0";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )200;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_SecurityId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
                return sqlca.sqlcode ;
    return 0;
}	

int readEzAtmFit( const char *I_RecordId, struct AtmFit *atmfit_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char InstId[ 13 ];
		char AtmLogicalGroup[ 17 ];
		char AtmId[ 17 ];
		char FitRecord[ 11 ];
		char SecurityId[ 11 ];
		char IndirectState;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR FitRecord IS STRING(13); */ 

	/* EXEC SQL VAR AtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR AtmId IS STRING(17); */ 

	/* EXEC SQL VAR SecurityId IS STRING(11); */ 


	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( FitRecord, 0, sizeof( FitRecord ) );
	memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( AtmId, 0, sizeof( AtmId ) );
	
	strcpy( Input_RecordId, I_RecordId );
				
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(INSTID),
        RTRIM(ATMLOGICALGROUP),
		RTRIM(ATMID),
		RTRIM(FITRECORD),
		RTRIM(SECURITYID),
		INDIRECTSTATE
	INTO
		:RecordId,
		:InstId,
		:AtmLogicalGroup,
		:AtmId,
		:FitRecord,
		:SecurityId,
		:IndirectState
	FROM EZATMFIT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(INSTID) ,RTRIM(ATMLOGICALGROUP\
) ,RTRIM(ATMID) ,RTRIM(FITRECORD) ,RTRIM(SECURITYID) ,INDIRECTSTATE into :b0,:\
b1,:b2,:b3,:b4,:b5,:b6  from EZATMFIT where RTRIM(RECORDID)=:b7";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )219;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)RecordId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)InstId;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)AtmLogicalGroup;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)AtmId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)FitRecord;
 sqlstm.sqhstl[4] = (unsigned int  )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)SecurityId;
 sqlstm.sqhstl[5] = (unsigned int  )11;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&IndirectState;
 sqlstm.sqhstl[6] = (unsigned int  )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[7] = (unsigned int  )17;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

		
		
	if ( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    	
    strcpy( atmfit_ptr->RecordId, RecordId );	
   	strcpy( atmfit_ptr->InstId, InstId );
	strcpy( atmfit_ptr->AtmLogicalGroup, AtmLogicalGroup );
	strcpy( atmfit_ptr->AtmId, AtmId );
	strcpy( atmfit_ptr->FitRecord, FitRecord );
	strcpy( atmfit_ptr->SecurityId, SecurityId );
	atmfit_ptr->IndirectState = IndirectState;
	return sqlca.sqlcode;
}

int readEzInstProfile( const char *I_InstId, struct EzInstProfileMemory *instprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ];
		char InstRouteType[ 17 ];
		char InstType[ 17 ];
		char InstSecurityGroup[ 17 ];
        char InstTerminalGroup[ 17 ];
        char InstAuthGroup[ 17 ];
        char InstCurrencyCode[ 6 ];
        int MaxATMPINCount;
        int MaxTelePINCount;
        char PrimaryBin[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR InstType IS STRING(17); */ 

	/* EXEC SQL VAR InstSecurityGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstAuthGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstCurrencyCode IS STRING(17); */ 

	/* EXEC SQL VAR PrimaryBin IS STRING(13); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( InstRouteType, 0, sizeof( InstRouteType ) );
	memset( InstType, 0, sizeof( InstType ) );
	memset( InstSecurityGroup, 0, sizeof( InstSecurityGroup ) );
	memset( InstTerminalGroup, 0, sizeof( InstTerminalGroup ) );
	memset( InstAuthGroup, 0, sizeof( InstAuthGroup) );
	memset( InstCurrencyCode, 0, sizeof( InstCurrencyCode ) );
	memset( PrimaryBin, 0, sizeof( PrimaryBin ) );
	
	strcpy( Input_InstId, I_InstId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(INSTROUTETYPE),
		RTRIM(INSTTYPE),
		RTRIM(INSTSECURITYGROUP),
		RTRIM(INSTTERMINALGROUP),
		RTRIM(INSTAUTHGROUP),
		RTRIM(INSTCURRENCYCODE),
		MAXATMPINCOUNT,
		MAXTELEPINCOUNT,
		RTRIM(PRIMARYBIN)
	INTO
		:InstId,
		:InstRouteType,
		:InstType,
		:InstSecurityGroup,
		:InstTerminalGroup,
		:InstAuthGroup,
		:InstCurrencyCode,
		:MaxATMPINCount,
		:MaxTelePINCount,
		:PrimaryBin
	FROM EZINSTPROFILE WHERE RTRIM(INSTID)=:Input_InstId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(INSTROUTETYPE) ,RTRIM(INSTTYPE) \
,RTRIM(INSTSECURITYGROUP) ,RTRIM(INSTTERMINALGROUP) ,RTRIM(INSTAUTHGROUP) ,RTR\
IM(INSTCURRENCYCODE) ,MAXATMPINCOUNT ,MAXTELEPINCOUNT ,RTRIM(PRIMARYBIN) into \
:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9  from EZINSTPROFILE where RTRIM(INSTID\
)=:b10";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )266;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)InstRouteType;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)InstType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)InstSecurityGroup;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)InstTerminalGroup;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)InstAuthGroup;
 sqlstm.sqhstl[5] = (unsigned int  )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)InstCurrencyCode;
 sqlstm.sqhstl[6] = (unsigned int  )17;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&MaxATMPINCount;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&MaxTelePINCount;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)PrimaryBin;
 sqlstm.sqhstl[9] = (unsigned int  )13;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)Input_InstId;
 sqlstm.sqhstl[10] = (unsigned int  )13;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( instprofile_ptr->InstId, InstId );
	strcpy( instprofile_ptr->InstRouteType, InstRouteType );
	strcpy( instprofile_ptr->InstType, InstType );
	strcpy( instprofile_ptr->InstSecurityGroup, InstSecurityGroup );
	strcpy( instprofile_ptr->InstTerminalGroup, InstTerminalGroup );
	strcpy( instprofile_ptr->InstAuthGroup, InstAuthGroup );
	strcpy( instprofile_ptr->InstCurrencyCode, InstCurrencyCode );
	instprofile_ptr->MaxATMPINCount = MaxATMPINCount ;
	instprofile_ptr->MaxTelePINCount = MaxTelePINCount;
	strcpy( instprofile_ptr->PrimaryBin, PrimaryBin );
	return sqlca.sqlcode;
}

int readEzInstSelect( const char *I_RecordNo, struct EzInstSelectMemory *instselect_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char DeviceType[ 17 ];
		char FieldType[ 65 ];
		char FromOffset[ 17 ];
		char ToOffset[ 17 ];
		char FieldVal[ 129 ];
		int Priority;
		char InstId[ 13 ];
		char InstType[ 11 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR FieldType IS STRING(65); */ 

	/* EXEC SQL VAR FromOffset IS STRING(17); */ 

	/* EXEC SQL VAR ToOffset IS STRING(17); */ 

	/* EXEC SQL VAR FieldVal IS STRING(129); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstType IS STRING(11); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( FieldType, 0, sizeof( FieldType ) );
	memset( FromOffset, 0, sizeof( FromOffset ) );
	memset( ToOffset, 0, sizeof( ToOffset ) );
	memset( FieldVal, 0, sizeof( FieldVal ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( InstType, 0, sizeof( InstType ) );
	
	strcpy( Input_RecordId, I_RecordNo );
	
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(DEVICETYPE),
		RTRIM(FIELDTYPE),
		RTRIM(FROMOFFSET),
		RTRIM(TOOFFSET),
		RTRIM(FIELDVAL),
		PRIORITY,
		RTRIM(INSTID),
		RTRIM(INSTTYPE)
	INTO
		:RecordId,
		:DeviceType,
		:FieldType,
		:FromOffset,
		:ToOffset,
		:FieldVal,
		:Priority,
		:InstId,
		:InstType
	FROM EZINSTSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(DEVICETYPE) ,RTRIM(FIELDTYPE) \
,RTRIM(FROMOFFSET) ,RTRIM(TOOFFSET) ,RTRIM(FIELDVAL) ,PRIORITY ,RTRIM(INSTID) \
,RTRIM(INSTTYPE) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8  from EZINSTSELECT w\
here RTRIM(RECORDID)=:b9";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )325;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)RecordId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)DeviceType;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)FieldType;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)FromOffset;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)ToOffset;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)FieldVal;
 sqlstm.sqhstl[5] = (unsigned int  )129;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&Priority;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)InstId;
 sqlstm.sqhstl[7] = (unsigned int  )13;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)InstType;
 sqlstm.sqhstl[8] = (unsigned int  )11;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[9] = (unsigned int  )17;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( instselect_ptr->RecordId, RecordId );
	strcpy( instselect_ptr->DeviceType, DeviceType );
	strcpy( instselect_ptr->FieldType, FieldType );
	strcpy( instselect_ptr->FromOffset, FromOffset );
	strcpy( instselect_ptr->ToOffset, ToOffset );
	instselect_ptr->Priority = Priority;
	strcpy( instselect_ptr->FieldVal, FieldVal );
	strcpy( instselect_ptr->InstId, InstId );
	strcpy( instselect_ptr->InstType, InstType );
	
	return sqlca.sqlcode;
}

int readEzNetworkSelect( const char *I_RecordNo, struct EzNetworkSelectMemory *networkselect_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char InstId[ 13 ];
		int Priority;
		char NetworkType[ 11 ];
		char FieldType[ 65 ];
		char FromOffset[ 33 ];
		char ToOffset[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR NetworkType IS STRING(11); */ 

	/* EXEC SQL VAR FieldType IS STRING(65); */ 

	/* EXEC SQL VAR FromOffset IS STRING(33); */ 

	/* EXEC SQL VAR ToOffset IS STRING(33); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( NetworkType, 0, sizeof( NetworkType ) );
	memset( FieldType, 0, sizeof( FieldType ) );
	memset( FromOffset, 0, sizeof( FromOffset ) );
	memset( ToOffset, 0, sizeof( ToOffset ) );

	strcpy( Input_RecordId, I_RecordNo );

	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(INSTID),
		PRIORITY,
		RTRIM(NETWORKTYPE),
		RTRIM(FIELDTYPE),
		RTRIM(FROMOFFSET),
		RTRIM(TOOFFSET)
	INTO
		:RecordId,
		:InstId,
		:Priority,
		:NetworkType,
		:FieldType,
		:FromOffset,
		:ToOffset
	FROM EZNETWORKSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(INSTID) ,PRIORITY ,RTRIM(NETWO\
RKTYPE) ,RTRIM(FIELDTYPE) ,RTRIM(FROMOFFSET) ,RTRIM(TOOFFSET) into :b0,:b1,:b2\
,:b3,:b4,:b5,:b6  from EZNETWORKSELECT where RTRIM(RECORDID)=:b7";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )380;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)RecordId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)InstId;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&Priority;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)NetworkType;
 sqlstm.sqhstl[3] = (unsigned int  )11;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)FieldType;
 sqlstm.sqhstl[4] = (unsigned int  )65;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)FromOffset;
 sqlstm.sqhstl[5] = (unsigned int  )33;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)ToOffset;
 sqlstm.sqhstl[6] = (unsigned int  )33;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[7] = (unsigned int  )17;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( networkselect_ptr->RecordId, RecordId );
	strcpy( networkselect_ptr->InstId, InstId );
	networkselect_ptr->Priority = Priority;
	strcpy( networkselect_ptr->NetworkType, NetworkType );
	strcpy( networkselect_ptr->FieldType, FieldType );
	strcpy( networkselect_ptr->FromOffset, FromOffset );
	strcpy( networkselect_ptr->ToOffset, ToOffset );
	
	return sqlca.sqlcode;
}

int readEzBINProfile( const char *I_InstId, const char *I_BIN, struct EzBINProfileMemory *binprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ];
		char BIN[ 13 ];
		char Input_BIN[ 13 ];
		char TxnList[ 65 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR Input_BIN IS STRING(13); */ 

	/* EXEC SQL VAR TxnList IS STRING(65); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( BIN, 0, sizeof( BIN ) );
	memset( Input_BIN, 0, sizeof( Input_BIN ) );
	memset( TxnList, 0, sizeof( TxnList ) );
	
	strcpy( Input_InstId, I_InstId );
	strcpy( Input_BIN, I_BIN );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(BIN),
		RTRIM(TXNLIST)
	INTO
		:InstId,
		:BIN,
		:TxnList
	FROM EZBINPROFILE WHERE RTRIM(INSTID)=:Input_InstId AND RTRIM(BIN)=:Input_BIN; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(BIN) ,RTRIM(TXNLIST) into :b0,:b\
1,:b2  from EZBINPROFILE where (RTRIM(INSTID)=:b3 and RTRIM(BIN)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )427;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)BIN;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TxnList;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_InstId;
 sqlstm.sqhstl[3] = (unsigned int  )13;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_BIN;
 sqlstm.sqhstl[4] = (unsigned int  )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
		
	strcpy( binprofile_ptr->InstId, InstId );
	strcpy( binprofile_ptr->BIN, BIN );
	strcpy( binprofile_ptr->TxnList, TxnList );
		
	return sqlca.sqlcode;
}

int readEzBranchProfile( const char *I_InstId, const char *I_BranchCode, struct EzBranchProfileMemory *branchprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ];
		char BranchCode[ 13 ];
		char Input_BranchCode[ 13 ];
		char BranchMapCode[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR BranchCode IS STRING(13); */ 

	/* EXEC SQL VAR Input_BranchCode IS STRING(13); */ 

	/* EXEC SQL VAR BranchMapCode IS STRING(13); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( BranchCode, 0, sizeof( BranchCode ) );
	memset( Input_BranchCode, 0, sizeof( Input_BranchCode ) );
	memset( BranchMapCode, 0, sizeof( BranchMapCode ) );
	
	strcpy( Input_InstId, I_InstId );
	strcpy( Input_BranchCode, I_BranchCode );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(BRANCHCODE),
		RTRIM(BRANCHMAPCODE)
	INTO
		:InstId,
		:BranchCode,
		:BranchMapCode
	FROM EZBRANCHPROFILE WHERE RTRIM(INSTID)=:Input_InstId AND RTRIM(BRANCHCODE)=:Input_BranchCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(BRANCHCODE) ,RTRIM(BRANCHMAPCODE\
) into :b0,:b1,:b2  from EZBRANCHPROFILE where (RTRIM(INSTID)=:b3 and RTRIM(BR\
ANCHCODE)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )462;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)BranchCode;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)BranchMapCode;
 sqlstm.sqhstl[2] = (unsigned int  )13;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_InstId;
 sqlstm.sqhstl[3] = (unsigned int  )13;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_BranchCode;
 sqlstm.sqhstl[4] = (unsigned int  )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( branchprofile_ptr->InstId, InstId );
	strcpy( branchprofile_ptr->BranchCode, BranchCode );
	strcpy( branchprofile_ptr->BranchMapCode, BranchMapCode );
		
	return sqlca.sqlcode;
}



int ClearATMStaticStatus( char *StaticStatusCode, const char *AtmId, char *Date, char *Time )
{	
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];  
		char hDate[ 7 ];  
		char hTime[ 7 ];  
		char hStaticStatusCode[ 11 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hTime IS STRING( 7 ); */ 

	/* EXEC SQL VAR hStaticStatusCode IS STRING( 11 ); */ 


	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hDate, 0, sizeof( hDate ) );
	memset( hTime, 0, sizeof( hTime ) );
	memset( hStaticStatusCode, 0, sizeof( hStaticStatusCode ) );
	
	strcpy( hAtmId, AtmId );
	strcpy( hDate, Date );
	strcpy( hTime, Time );
	strcpy( hStaticStatusCode, StaticStatusCode );

	
	/* EXEC SQL UPDATE EZATMSTATUS SET 
		STATICCODE=:hStaticStatusCode,
		LOGDATE=to_date( :hDate, 'dd-mm-yy' ), 
		LOGTIME=:hTime 
	WHERE TRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMSTATUS  set STATICCODE=:b0,LOGDATE=to_date(:b1,'\
dd-mm-yy'),LOGTIME=:b2 where trim(ATMID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )497;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hStaticStatusCode;
 sqlstm.sqhstl[0] = (unsigned int  )11;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hDate;
 sqlstm.sqhstl[1] = (unsigned int  )7;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hTime;
 sqlstm.sqhstl[2] = (unsigned int  )7;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)hAtmId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if ( sqlca.sqlcode != 0 )
    	return ( sqlca.sqlcode );
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )528;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		return ( sqlca.sqlcode );
	}
}

int readAtmBatchId( char *AtmId, char *BatchId )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hAtmId[ 17 ];
		char hBatchId[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hBatchId IS STRING(13); */ 

		
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hBatchId, 0, sizeof( hBatchId ) );
	
	strcpy( hAtmId, AtmId );
	
	/* EXEC SQL SELECT
		RTRIM(BATCHID)
	INTO
		:hBatchId
	FROM EZATMDATAINFO WHERE RTRIM(ATMID) =:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(BATCHID) into :b0  from EZATMDATAINFO where RTR\
IM(ATMID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )543;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hBatchId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hAtmId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( sqlca.sqlcode == 0 )
	{
		strcpy( BatchId, hBatchId );
		return sqlca.sqlcode ;
	}
	else
	   return sqlca.sqlcode ;
}

int readEzSecurityTable( const char *I_SecurityId, struct EzSecurity *security_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SecurityId[ 11 ];
		char Input_SecurityId[ 11 ];
		char PINVerificationMethod;
		char EPVK[ 65 ];
		char DecimilizationTable[ 17 ];
		char PINPadChar;
		char PANPadChar;
		short PINLen;
		short PANLen;
		short PANValidationOffset;
		char PINBlockFormat[ 3 ];
		short PANValidationLength;
		char CVKA[ 65 ];
		char CVKB[ 65 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR SecurityId IS STRING(11); */ 

	/* EXEC SQL VAR Input_SecurityId IS STRING(11); */ 

	/* EXEC SQL VAR EPVK IS STRING(65); */ 

	/* EXEC SQL VAR DecimilizationTable IS STRING(17); */ 

	/* EXEC SQL VAR PINBlockFormat IS STRING(2); */ 

	/* EXEC SQL VAR CVKA IS STRING(65); */ 

	/* EXEC SQL VAR CVKB IS STRING(65); */ 

	
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( Input_SecurityId, 0, sizeof( Input_SecurityId ) );
	memset( EPVK, 0, sizeof( EPVK ) );
	memset( DecimilizationTable, 0, sizeof( DecimilizationTable ) );
	memset( PINBlockFormat, 0, sizeof( PINBlockFormat ) );
	memset( CVKA, 0, sizeof( CVKA ) );
	memset( CVKB, 0, sizeof( CVKB ) );
	
	strcpy( Input_SecurityId, I_SecurityId );
	
	/* EXEC SQL SELECT
		RTRIM(SECURITYID),
		PINVERIFICATIONMETHOD,
		RTRIM(EPVK),
		RTRIM(DECIMILIZATIONTABLE),
		PINPADCHAR,
		PANPADCHAR,
		PINLEN,
		PANLEN,
		PANVALIDATIONOFFSET,
		RTRIM(PINBLOCKFORMAT),
		PANVALIDATIONLENGTH,
		RTRIM(CVKA),
		RTRIM(CVKB)
	INTO
		:SecurityId,
		:PINVerificationMethod,
		:EPVK,
		:DecimilizationTable,
		:PINPadChar,
		:PANPadChar,
		:PINLen,
		:PANLen,
		:PANValidationOffset,
		:PINBlockFormat,
		:PANValidationLength,
		:CVKA,
		:CVKB
	FROM EZSECURITY WHERE RTRIM(SECURITYID)=:Input_SecurityId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 14;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(SECURITYID) ,PINVERIFICATIONMETHOD ,RTRIM(EPVK)\
 ,RTRIM(DECIMILIZATIONTABLE) ,PINPADCHAR ,PANPADCHAR ,PINLEN ,PANLEN ,PANVALID\
ATIONOFFSET ,RTRIM(PINBLOCKFORMAT) ,PANVALIDATIONLENGTH ,RTRIM(CVKA) ,RTRIM(CV\
KB) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12  from EZSECURI\
TY where RTRIM(SECURITYID)=:b13";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )566;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SecurityId;
 sqlstm.sqhstl[0] = (unsigned int  )11;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&PINVerificationMethod;
 sqlstm.sqhstl[1] = (unsigned int  )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)EPVK;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)DecimilizationTable;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&PINPadChar;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&PANPadChar;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&PINLen;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&PANLen;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&PANValidationOffset;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)PINBlockFormat;
 sqlstm.sqhstl[9] = (unsigned int  )2;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&PANValidationLength;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)CVKA;
 sqlstm.sqhstl[11] = (unsigned int  )65;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)CVKB;
 sqlstm.sqhstl[12] = (unsigned int  )65;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)Input_SecurityId;
 sqlstm.sqhstl[13] = (unsigned int  )11;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( security_ptr->SecurityId, SecurityId );
	security_ptr->PINVerificationMethod = PINVerificationMethod;
	strcpy( security_ptr->EPVK, EPVK );
	strcpy( security_ptr->DecimilizationTable, DecimilizationTable );
	security_ptr->PINPadChar = PINPadChar;
	security_ptr->PANPadChar = PANPadChar;
	security_ptr->PINLen = PINLen;
	security_ptr->PANLen = PANLen;
	security_ptr->PANValidationOffset = PANValidationOffset;
	strcpy( security_ptr->PINBlockFormat, PINBlockFormat );
	security_ptr->PANValidationLength = PANValidationLength;
	strcpy( security_ptr->CVKA, CVKA );
	strcpy( security_ptr->CVKB, CVKB );
	return sqlca.sqlcode;
}

int readATMKeyTable( const char *I_ATMId, struct EzATMKey *atmkey_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char ATMId[ 33 ];
		char Input_ATMId[ 33 ];
		char ATMMasterKey[ 65 ];
		char ATMCommKey[ 65 ];
		int ATMKeyLen;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR ATMId IS STRING(33); */ 

	/* EXEC SQL VAR Input_ATMId IS STRING(33); */ 

	/* EXEC SQL VAR ATMMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR ATMCommKey IS STRING(65); */ 

	
	memset( ATMId, 0, sizeof( ATMId ) );
	memset( Input_ATMId, 0, sizeof( Input_ATMId ) );
	memset( ATMMasterKey, 0, sizeof( ATMMasterKey ) );
	memset( ATMCommKey, 0, sizeof( ATMCommKey ) );
	
	strcpy( Input_ATMId, I_ATMId );
	
	/* EXEC SQL SELECT
		RTRIM(ATMID),
		RTRIM(ATMMASTERKEY),
		RTRIM(ATMCOMMKEY),
		ATMKEYLEN
	INTO
		ATMId,
		ATMMasterKey,
		ATMCommKey,
		ATMKeyLen
	FROM EZATMINFO WHERE RTRIM(ATMID)=:Input_ATMId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 14;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(ATMID) ,RTRIM(ATMMASTERKEY) ,RTRIM(ATMCOMMKEY) \
,ATMKEYLEN into :b0,:b1,:b2,:b3  from EZATMINFO where RTRIM(ATMID)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )637;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)ATMId;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)ATMMasterKey;
 sqlstm.sqhstl[1] = (unsigned int  )65;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)ATMCommKey;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&ATMKeyLen;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_ATMId;
 sqlstm.sqhstl[4] = (unsigned int  )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( atmkey_ptr->ATMId, ATMId );
	strcpy( atmkey_ptr->ATMMasterKey, ATMMasterKey );
	strcpy( atmkey_ptr->ATMCommKey, ATMCommKey );
	atmkey_ptr->ATMKeyLen = ATMKeyLen;
	return sqlca.sqlcode;
}

int readNetworkKeyTable( const char *I_NetworkId, struct EzNetworkKey *networkkey_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char Input_NetworkId[ 17 ];
		char NetworkMasterKey[ 65 ];
		char NetworkAcqCommKey[ 65 ];
		char NetworkIssCommKey[ 65 ];
		int NetworkKeyLen;
		char KeyProperty;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR NetworkMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR NetworkAcqCommKey IS STRING(65); */ 

	/* EXEC SQL VAR NetworkIssCommKey IS STRING(65); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
	memset( NetworkMasterKey, 0, sizeof( NetworkMasterKey ) );
	memset( NetworkAcqCommKey, 0, sizeof( NetworkAcqCommKey ) );
	memset( NetworkIssCommKey, 0, sizeof( NetworkIssCommKey ) );
	
	strcpy( Input_NetworkId, I_NetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(NETWORKID),
		RTRIM(NETWORKMASTERKEY),
		RTRIM(NETWORKACQCOMMKEY),
		RTRIM(NETWORKISSCOMMKEY),
		NETWORKKEYLEN,
		KEYPROPERTY,
	INTO
		NetworkId,
		NetworkMasterKey,
		NetworkAcqCommKey,
		NetworkIssCommKey,
		NetworkKeyLen,
		KeyProperty
	FROM EZNETWORKKEY WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 14;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NETWORKID) ,RTRIM(NETWORKMASTERKEY) ,RTRIM(NETW\
ORKACQCOMMKEY) ,RTRIM(NETWORKISSCOMMKEY) ,NETWORKKEYLEN ,KEYPROPERTY ,INTO Net\
workId ,NetworkMasterKey ,NetworkAcqCommKey ,NetworkIssCommKey ,NetworkKeyLen \
,KeyProperty  from EZNETWORKKEY where RTRIM(NETWORKID)=:b0";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )672;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_NetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( networkkey_ptr->NetworkId, NetworkId );
	strcpy( networkkey_ptr->NetworkMasterKey, NetworkMasterKey );
	strcpy( networkkey_ptr->NetworkAcqCommKey, NetworkAcqCommKey );
	strcpy( networkkey_ptr->NetworkIssCommKey, NetworkIssCommKey );
	networkkey_ptr->NetworkKeyLen = NetworkKeyLen;
	networkkey_ptr->KeyProperty = KeyProperty;
	return sqlca.sqlcode;
}

int readEzBINSelect( const char *I_RecordNo, struct EzBINSelectMemory *binselect_ptr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char RecordId[ 17 ];
        char Input_RecordId[ 17 ];
        char BIN[ 13 ];
        char InstId[ 13 ];
        char BINRangeReq;
        short Priority;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL VAR RecordId IS STRING(17); */ 

    /* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

    /* EXEC SQL VAR BIN IS STRING(13); */ 

    /* EXEC SQL VAR InstId IS STRING(13); */ 


    memset( RecordId, 0, sizeof( RecordId ) );
    memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
    memset( BIN, 0, sizeof( BIN ) );
    memset( InstId, 0, sizeof( InstId ) );

    strcpy( Input_RecordId, I_RecordNo );
    /* EXEC SQL SELECT
        RTRIM(RECORDID),
	    RTRIM(BIN),
	    RTRIM(INSTID),
        BINRANGEREQ,
        PRIORITY
    INTO
        :RecordId,
        :BIN,
        :InstId,
        :BINRangeReq,
        :Priority
    FROM EZBINSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 14;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(BIN) ,RTRIM(INSTID) ,BINRAN\
GEREQ ,PRIORITY into :b0,:b1,:b2,:b3,:b4  from EZBINSELECT where RTRIM(RECORDI\
D)=:b5";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )691;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)RecordId;
    sqlstm.sqhstl[0] = (unsigned int  )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)BIN;
    sqlstm.sqhstl[1] = (unsigned int  )13;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void  *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)InstId;
    sqlstm.sqhstl[2] = (unsigned int  )13;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void  *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void  *)&BINRangeReq;
    sqlstm.sqhstl[3] = (unsigned int  )1;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void  *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void  *)&Priority;
    sqlstm.sqhstl[4] = (unsigned int  )sizeof(short);
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         void  *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (         void  *)Input_RecordId;
    sqlstm.sqhstl[5] = (unsigned int  )17;
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         void  *)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned int  )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



    if ( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    	
	strcpy( binselect_ptr->RecordId, RecordId );
    strcpy( binselect_ptr->BIN, BIN );
    strcpy( binselect_ptr->InstId, InstId );
    binselect_ptr->BINRangeReq = BINRangeReq;
    binselect_ptr->Priority = Priority;
    return sqlca.sqlcode;
}

int readEzAtmDenomStatus( const char *I_AtmId, int LastResetDate, int LastResetTime, struct EzAtmDenomStatus *ezatmdenomstatus_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char Input_AtmId[ 17 ];
		int DenomANotesLoaded;
		int DenomADisp;
		int DenomAMin;
		int DenomBNotesLoaded;
		int DenomBDisp;
		int DenomBMin;
		int DenomCNotesLoaded;
		int DenomCDisp;
		int DenomCMin;
		int DenomDNotesLoaded;
		int DenomDDisp;
		int DenomDMin;
		int DenomENotesLoaded;
		int DenomEDisp;
		int DenomEMin;
		int DenomFNotesLoaded;
		int DenomFDisp;
		int DenomFMin;
		int DenomGNotesLoaded;
		int DenomGDisp;
		int DenomGMin;
		int DenomHNotesLoaded;
		int DenomHDisp;
		int DenomHMin;
		int hLastResetDate;
		int hLastResetTime;
		char Input_LastResetDate[ 7 ];
		int Input_LastResetTime;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR Input_AtmId IS STRING(17); */ 

	/* EXEC SQL VAR Input_LastResetDate IS STRING(7); */ 

		
	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	strcpy( Input_AtmId, I_AtmId );
	
	memset( Input_LastResetDate, '0', sizeof( Input_LastResetDate ) );
	sprintf( Input_LastResetDate, "%06d", LastResetDate );
	Input_LastResetTime = LastResetTime;
		
	/* EXEC SQL SELECT
       	RTRIM(DENOM_A_NOTESLOADED),
		RTRIM(DENOM_A_NOTESDISP),
		RTRIM(DENOM_B_NOTESLOADED),
		RTRIM(DENOM_B_NOTESDISP),
		RTRIM(DENOM_C_NOTESLOADED),
		RTRIM(DENOM_C_NOTESDISP),
		RTRIM(DENOM_D_NOTESLOADED),
		RTRIM(DENOM_D_NOTESDISP),
		RTRIM(DENOM_E_NOTESLOADED),
		RTRIM(DENOM_E_NOTESDISP),
		RTRIM(DENOM_F_NOTESLOADED),
		RTRIM(DENOM_F_NOTESDISP),
		RTRIM(DENOM_G_NOTESLOADED),
		RTRIM(DENOM_G_NOTESDISP),
		RTRIM(DENOM_H_NOTESLOADED),
		RTRIM(DENOM_H_NOTESDISP),
		TO_NUMBER(TO_CHAR(LASTRESETDATE,'DDMMYY')),
		LASTRESETTIME
	INTO
		:DenomANotesLoaded,
		:DenomADisp,
		:DenomBNotesLoaded,
		:DenomBDisp,
		:DenomCNotesLoaded,
		:DenomCDisp,
		:DenomDNotesLoaded,
		:DenomDDisp,
		:DenomENotesLoaded,
		:DenomEDisp,
		:DenomFNotesLoaded,
		:DenomFDisp,
		:DenomGNotesLoaded,
		:DenomGDisp,
		:DenomHNotesLoaded,
		:DenomHDisp,
		:hLastResetDate,
		:hLastResetTime
	FROM EZATMDENOMSTATUS WHERE TRIM(ATMID)=:Input_AtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DENOM_A_NOTESLOADED) ,RTRIM(DENOM_A_NOTESDISP) \
,RTRIM(DENOM_B_NOTESLOADED) ,RTRIM(DENOM_B_NOTESDISP) ,RTRIM(DENOM_C_NOTESLOAD\
ED) ,RTRIM(DENOM_C_NOTESDISP) ,RTRIM(DENOM_D_NOTESLOADED) ,RTRIM(DENOM_D_NOTES\
DISP) ,RTRIM(DENOM_E_NOTESLOADED) ,RTRIM(DENOM_E_NOTESDISP) ,RTRIM(DENOM_F_NOT\
ESLOADED) ,RTRIM(DENOM_F_NOTESDISP) ,RTRIM(DENOM_G_NOTESLOADED) ,RTRIM(DENOM_G\
_NOTESDISP) ,RTRIM(DENOM_H_NOTESLOADED) ,RTRIM(DENOM_H_NOTESDISP) ,TO_NUMBER(T\
O_CHAR(LASTRESETDATE,'DDMMYY')) ,LASTRESETTIME into :b0,:b1,:b2,:b3,:b4,:b5,:b\
6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,:b16,:b17  from EZATMDENOMSTATUS w\
here trim(ATMID)=:b18";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )730;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&DenomANotesLoaded;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&DenomADisp;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&DenomBNotesLoaded;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&DenomBDisp;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&DenomCNotesLoaded;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&DenomCDisp;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&DenomDNotesLoaded;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&DenomDDisp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&DenomENotesLoaded;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&DenomEDisp;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&DenomFNotesLoaded;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&DenomFDisp;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&DenomGNotesLoaded;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&DenomGDisp;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&DenomHNotesLoaded;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&DenomHDisp;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&hLastResetDate;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&hLastResetTime;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[18] = (unsigned int  )17;
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 && sqlca.sqlcode != 1403 )
    	return ( sqlca.sqlcode );
    	
    if( sqlca.sqlcode == 1403 )
    {
    	DenomANotesLoaded = 0;
    	DenomADisp = 0;
 		DenomAMin = 50;
 		DenomBNotesLoaded = 0;
    	DenomBDisp = 0;
 		DenomBMin = 50;
 		DenomCNotesLoaded = 0;
    	DenomCDisp = 0;
 		DenomCMin = 50;
 		DenomDNotesLoaded = 0;
    	DenomDDisp = 0;
 		DenomDMin = 50;
 		DenomENotesLoaded = 0;
    	DenomEDisp = 0;
 		DenomEMin = 50;
 		DenomFNotesLoaded = 0;
    	DenomFDisp = 0;
 		DenomFMin = 50;
 		DenomGNotesLoaded = 0;
    	DenomGDisp = 0;
 		DenomGMin = 50;
 		DenomHNotesLoaded = 0;
    	DenomHDisp = 0;
 		DenomHMin = 50;
 		ezatmdenomstatus_ptr->LastResetDate = LastResetDate;
		ezatmdenomstatus_ptr->LastResetTime = LastResetTime;
 		
 		/* EXEC SQL INSERT INTO EZATMDENOMSTATUS
		(
			ATMID,
			DENOM_A_NOTESLOADED,
			DENOM_A_NOTESDISP,
			DENOM_A_NOTESMIN,
			DENOM_B_NOTESLOADED,
			DENOM_B_NOTESDISP,
			DENOM_B_NOTESMIN,
			DENOM_C_NOTESLOADED,
			DENOM_C_NOTESDISP,
			DENOM_C_NOTESMIN,
			DENOM_D_NOTESLOADED,
			DENOM_D_NOTESDISP,
			DENOM_D_NOTESMIN,
			DENOM_E_NOTESLOADED,
			DENOM_E_NOTESDISP,
			DENOM_E_NOTESMIN,
			DENOM_F_NOTESLOADED,
			DENOM_F_NOTESDISP,
			DENOM_F_NOTESMIN,
			DENOM_G_NOTESLOADED,
			DENOM_G_NOTESDISP,
			DENOM_G_NOTESMIN,
			DENOM_H_NOTESLOADED,
			DENOM_H_NOTESDISP,
			DENOM_H_NOTESMIN,
			LASTRESETDATE,
			LASTRESETTIME
		)
		VALUES
		(
			:Input_AtmId,
			:DenomANotesLoaded,
			:DenomADisp,
			:DenomAMin,
			:DenomBNotesLoaded,
			:DenomBDisp,
			:DenomBMin,
			:DenomCNotesLoaded,
			:DenomCDisp,
			:DenomCMin,
			:DenomDNotesLoaded,
			:DenomDDisp,
			:DenomDMin,
			:DenomENotesLoaded,
			:DenomEDisp,
			:DenomEMin,
			:DenomFNotesLoaded,
			:DenomFDisp,
			:DenomFMin,
			:DenomGNotesLoaded,
			:DenomGDisp,
			:DenomGMin,
			:DenomHNotesLoaded,
			:DenomHDisp,
			:DenomHMin,
			to_date(:Input_LastResetDate, 'DDMMYY'),
			:Input_LastResetTime	
		); */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 27;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "insert into EZATMDENOMSTATUS (ATMID,DENOM_A_NOTESLOADED,DE\
NOM_A_NOTESDISP,DENOM_A_NOTESMIN,DENOM_B_NOTESLOADED,DENOM_B_NOTESDISP,DENOM_B\
_NOTESMIN,DENOM_C_NOTESLOADED,DENOM_C_NOTESDISP,DENOM_C_NOTESMIN,DENOM_D_NOTES\
LOADED,DENOM_D_NOTESDISP,DENOM_D_NOTESMIN,DENOM_E_NOTESLOADED,DENOM_E_NOTESDIS\
P,DENOM_E_NOTESMIN,DENOM_F_NOTESLOADED,DENOM_F_NOTESDISP,DENOM_F_NOTESMIN,DENO\
M_G_NOTESLOADED,DENOM_G_NOTESDISP,DENOM_G_NOTESMIN,DENOM_H_NOTESLOADED,DENOM_H\
_NOTESDISP,DENOM_H_NOTESMIN,LASTRESETDATE,LASTRESETTIME) values (:b0,:b1,:b2,:\
b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:\
b20,:b21,:b22,:b23,:b24,to_date(:b25,'DDMMYY'),:b26)";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )821;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)Input_AtmId;
   sqlstm.sqhstl[0] = (unsigned int  )17;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&DenomANotesLoaded;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&DenomADisp;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[2] = (         int  )0;
   sqlstm.sqindv[2] = (         void  *)0;
   sqlstm.sqinds[2] = (         int  )0;
   sqlstm.sqharm[2] = (unsigned int  )0;
   sqlstm.sqadto[2] = (unsigned short )0;
   sqlstm.sqtdso[2] = (unsigned short )0;
   sqlstm.sqhstv[3] = (         void  *)&DenomAMin;
   sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[3] = (         int  )0;
   sqlstm.sqindv[3] = (         void  *)0;
   sqlstm.sqinds[3] = (         int  )0;
   sqlstm.sqharm[3] = (unsigned int  )0;
   sqlstm.sqadto[3] = (unsigned short )0;
   sqlstm.sqtdso[3] = (unsigned short )0;
   sqlstm.sqhstv[4] = (         void  *)&DenomBNotesLoaded;
   sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[4] = (         int  )0;
   sqlstm.sqindv[4] = (         void  *)0;
   sqlstm.sqinds[4] = (         int  )0;
   sqlstm.sqharm[4] = (unsigned int  )0;
   sqlstm.sqadto[4] = (unsigned short )0;
   sqlstm.sqtdso[4] = (unsigned short )0;
   sqlstm.sqhstv[5] = (         void  *)&DenomBDisp;
   sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[5] = (         int  )0;
   sqlstm.sqindv[5] = (         void  *)0;
   sqlstm.sqinds[5] = (         int  )0;
   sqlstm.sqharm[5] = (unsigned int  )0;
   sqlstm.sqadto[5] = (unsigned short )0;
   sqlstm.sqtdso[5] = (unsigned short )0;
   sqlstm.sqhstv[6] = (         void  *)&DenomBMin;
   sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[6] = (         int  )0;
   sqlstm.sqindv[6] = (         void  *)0;
   sqlstm.sqinds[6] = (         int  )0;
   sqlstm.sqharm[6] = (unsigned int  )0;
   sqlstm.sqadto[6] = (unsigned short )0;
   sqlstm.sqtdso[6] = (unsigned short )0;
   sqlstm.sqhstv[7] = (         void  *)&DenomCNotesLoaded;
   sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[7] = (         int  )0;
   sqlstm.sqindv[7] = (         void  *)0;
   sqlstm.sqinds[7] = (         int  )0;
   sqlstm.sqharm[7] = (unsigned int  )0;
   sqlstm.sqadto[7] = (unsigned short )0;
   sqlstm.sqtdso[7] = (unsigned short )0;
   sqlstm.sqhstv[8] = (         void  *)&DenomCDisp;
   sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[8] = (         int  )0;
   sqlstm.sqindv[8] = (         void  *)0;
   sqlstm.sqinds[8] = (         int  )0;
   sqlstm.sqharm[8] = (unsigned int  )0;
   sqlstm.sqadto[8] = (unsigned short )0;
   sqlstm.sqtdso[8] = (unsigned short )0;
   sqlstm.sqhstv[9] = (         void  *)&DenomCMin;
   sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[9] = (         int  )0;
   sqlstm.sqindv[9] = (         void  *)0;
   sqlstm.sqinds[9] = (         int  )0;
   sqlstm.sqharm[9] = (unsigned int  )0;
   sqlstm.sqadto[9] = (unsigned short )0;
   sqlstm.sqtdso[9] = (unsigned short )0;
   sqlstm.sqhstv[10] = (         void  *)&DenomDNotesLoaded;
   sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[10] = (         int  )0;
   sqlstm.sqindv[10] = (         void  *)0;
   sqlstm.sqinds[10] = (         int  )0;
   sqlstm.sqharm[10] = (unsigned int  )0;
   sqlstm.sqadto[10] = (unsigned short )0;
   sqlstm.sqtdso[10] = (unsigned short )0;
   sqlstm.sqhstv[11] = (         void  *)&DenomDDisp;
   sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[11] = (         int  )0;
   sqlstm.sqindv[11] = (         void  *)0;
   sqlstm.sqinds[11] = (         int  )0;
   sqlstm.sqharm[11] = (unsigned int  )0;
   sqlstm.sqadto[11] = (unsigned short )0;
   sqlstm.sqtdso[11] = (unsigned short )0;
   sqlstm.sqhstv[12] = (         void  *)&DenomDMin;
   sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[12] = (         int  )0;
   sqlstm.sqindv[12] = (         void  *)0;
   sqlstm.sqinds[12] = (         int  )0;
   sqlstm.sqharm[12] = (unsigned int  )0;
   sqlstm.sqadto[12] = (unsigned short )0;
   sqlstm.sqtdso[12] = (unsigned short )0;
   sqlstm.sqhstv[13] = (         void  *)&DenomENotesLoaded;
   sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[13] = (         int  )0;
   sqlstm.sqindv[13] = (         void  *)0;
   sqlstm.sqinds[13] = (         int  )0;
   sqlstm.sqharm[13] = (unsigned int  )0;
   sqlstm.sqadto[13] = (unsigned short )0;
   sqlstm.sqtdso[13] = (unsigned short )0;
   sqlstm.sqhstv[14] = (         void  *)&DenomEDisp;
   sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[14] = (         int  )0;
   sqlstm.sqindv[14] = (         void  *)0;
   sqlstm.sqinds[14] = (         int  )0;
   sqlstm.sqharm[14] = (unsigned int  )0;
   sqlstm.sqadto[14] = (unsigned short )0;
   sqlstm.sqtdso[14] = (unsigned short )0;
   sqlstm.sqhstv[15] = (         void  *)&DenomEMin;
   sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[15] = (         int  )0;
   sqlstm.sqindv[15] = (         void  *)0;
   sqlstm.sqinds[15] = (         int  )0;
   sqlstm.sqharm[15] = (unsigned int  )0;
   sqlstm.sqadto[15] = (unsigned short )0;
   sqlstm.sqtdso[15] = (unsigned short )0;
   sqlstm.sqhstv[16] = (         void  *)&DenomFNotesLoaded;
   sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[16] = (         int  )0;
   sqlstm.sqindv[16] = (         void  *)0;
   sqlstm.sqinds[16] = (         int  )0;
   sqlstm.sqharm[16] = (unsigned int  )0;
   sqlstm.sqadto[16] = (unsigned short )0;
   sqlstm.sqtdso[16] = (unsigned short )0;
   sqlstm.sqhstv[17] = (         void  *)&DenomFDisp;
   sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[17] = (         int  )0;
   sqlstm.sqindv[17] = (         void  *)0;
   sqlstm.sqinds[17] = (         int  )0;
   sqlstm.sqharm[17] = (unsigned int  )0;
   sqlstm.sqadto[17] = (unsigned short )0;
   sqlstm.sqtdso[17] = (unsigned short )0;
   sqlstm.sqhstv[18] = (         void  *)&DenomFMin;
   sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[18] = (         int  )0;
   sqlstm.sqindv[18] = (         void  *)0;
   sqlstm.sqinds[18] = (         int  )0;
   sqlstm.sqharm[18] = (unsigned int  )0;
   sqlstm.sqadto[18] = (unsigned short )0;
   sqlstm.sqtdso[18] = (unsigned short )0;
   sqlstm.sqhstv[19] = (         void  *)&DenomGNotesLoaded;
   sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[19] = (         int  )0;
   sqlstm.sqindv[19] = (         void  *)0;
   sqlstm.sqinds[19] = (         int  )0;
   sqlstm.sqharm[19] = (unsigned int  )0;
   sqlstm.sqadto[19] = (unsigned short )0;
   sqlstm.sqtdso[19] = (unsigned short )0;
   sqlstm.sqhstv[20] = (         void  *)&DenomGDisp;
   sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[20] = (         int  )0;
   sqlstm.sqindv[20] = (         void  *)0;
   sqlstm.sqinds[20] = (         int  )0;
   sqlstm.sqharm[20] = (unsigned int  )0;
   sqlstm.sqadto[20] = (unsigned short )0;
   sqlstm.sqtdso[20] = (unsigned short )0;
   sqlstm.sqhstv[21] = (         void  *)&DenomGMin;
   sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[21] = (         int  )0;
   sqlstm.sqindv[21] = (         void  *)0;
   sqlstm.sqinds[21] = (         int  )0;
   sqlstm.sqharm[21] = (unsigned int  )0;
   sqlstm.sqadto[21] = (unsigned short )0;
   sqlstm.sqtdso[21] = (unsigned short )0;
   sqlstm.sqhstv[22] = (         void  *)&DenomHNotesLoaded;
   sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[22] = (         int  )0;
   sqlstm.sqindv[22] = (         void  *)0;
   sqlstm.sqinds[22] = (         int  )0;
   sqlstm.sqharm[22] = (unsigned int  )0;
   sqlstm.sqadto[22] = (unsigned short )0;
   sqlstm.sqtdso[22] = (unsigned short )0;
   sqlstm.sqhstv[23] = (         void  *)&DenomHDisp;
   sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[23] = (         int  )0;
   sqlstm.sqindv[23] = (         void  *)0;
   sqlstm.sqinds[23] = (         int  )0;
   sqlstm.sqharm[23] = (unsigned int  )0;
   sqlstm.sqadto[23] = (unsigned short )0;
   sqlstm.sqtdso[23] = (unsigned short )0;
   sqlstm.sqhstv[24] = (         void  *)&DenomHMin;
   sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[24] = (         int  )0;
   sqlstm.sqindv[24] = (         void  *)0;
   sqlstm.sqinds[24] = (         int  )0;
   sqlstm.sqharm[24] = (unsigned int  )0;
   sqlstm.sqadto[24] = (unsigned short )0;
   sqlstm.sqtdso[24] = (unsigned short )0;
   sqlstm.sqhstv[25] = (         void  *)Input_LastResetDate;
   sqlstm.sqhstl[25] = (unsigned int  )7;
   sqlstm.sqhsts[25] = (         int  )0;
   sqlstm.sqindv[25] = (         void  *)0;
   sqlstm.sqinds[25] = (         int  )0;
   sqlstm.sqharm[25] = (unsigned int  )0;
   sqlstm.sqadto[25] = (unsigned short )0;
   sqlstm.sqtdso[25] = (unsigned short )0;
   sqlstm.sqhstv[26] = (         void  *)&Input_LastResetTime;
   sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[26] = (         int  )0;
   sqlstm.sqindv[26] = (         void  *)0;
   sqlstm.sqinds[26] = (         int  )0;
   sqlstm.sqharm[26] = (unsigned int  )0;
   sqlstm.sqadto[26] = (unsigned short )0;
   sqlstm.sqtdso[26] = (unsigned short )0;
   sqlstm.sqphsv = sqlstm.sqhstv;
   sqlstm.sqphsl = sqlstm.sqhstl;
   sqlstm.sqphss = sqlstm.sqhsts;
   sqlstm.sqpind = sqlstm.sqindv;
   sqlstm.sqpins = sqlstm.sqinds;
   sqlstm.sqparm = sqlstm.sqharm;
   sqlstm.sqparc = sqlstm.sqharc;
   sqlstm.sqpadto = sqlstm.sqadto;
   sqlstm.sqptdso = sqlstm.sqtdso;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		
		if ( sqlca.sqlcode != 0 )
	    	return sqlca.sqlcode;
		else
		{
			/* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 27;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )944;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


			if ( sqlca.sqlcode != 0 )
	    		return sqlca.sqlcode;
	    }
	}
	else
	{
		ezatmdenomstatus_ptr->LastResetDate = hLastResetDate;
		ezatmdenomstatus_ptr->LastResetTime = hLastResetTime;
	}
			 
	strcpy( ezatmdenomstatus_ptr->AtmId, Input_AtmId );
	ezatmdenomstatus_ptr->DenomANotesLoaded = DenomANotesLoaded;
	ezatmdenomstatus_ptr->DenomADisp = DenomADisp;
	ezatmdenomstatus_ptr->DenomAMin = DenomAMin;
	ezatmdenomstatus_ptr->DenomBNotesLoaded = DenomBNotesLoaded;
	ezatmdenomstatus_ptr->DenomBDisp = DenomBDisp;
	ezatmdenomstatus_ptr->DenomBMin = DenomBMin;
	ezatmdenomstatus_ptr->DenomCNotesLoaded = DenomCNotesLoaded;
	ezatmdenomstatus_ptr->DenomCDisp = DenomCDisp;
	ezatmdenomstatus_ptr->DenomCMin = DenomCMin;
	ezatmdenomstatus_ptr->DenomDNotesLoaded = DenomDNotesLoaded;
	ezatmdenomstatus_ptr->DenomDDisp = DenomDDisp;
	ezatmdenomstatus_ptr->DenomDMin = DenomDMin;
	ezatmdenomstatus_ptr->DenomENotesLoaded = DenomENotesLoaded;
	ezatmdenomstatus_ptr->DenomEDisp = DenomEDisp;
	ezatmdenomstatus_ptr->DenomEMin = DenomEMin;
	ezatmdenomstatus_ptr->DenomFNotesLoaded = DenomFNotesLoaded;
	ezatmdenomstatus_ptr->DenomFDisp = DenomFDisp;
	ezatmdenomstatus_ptr->DenomEMin = DenomFMin;
	ezatmdenomstatus_ptr->DenomGNotesLoaded = DenomGNotesLoaded;
	ezatmdenomstatus_ptr->DenomGDisp = DenomGDisp;
	ezatmdenomstatus_ptr->DenomEMin = DenomGMin;
	ezatmdenomstatus_ptr->DenomHNotesLoaded = DenomHNotesLoaded;
	ezatmdenomstatus_ptr->DenomHDisp = DenomHDisp;
	ezatmdenomstatus_ptr->DenomEMin = DenomHMin;
	return ( sqlca.sqlcode );	
}

int openBatch( const char *AtmId, const char *BatchId, const char *UserId, int GenDate, int GenTime, int DenomADisp, int DenomBDisp, int DenomCDisp, int DenomDDisp, int DenomEDisp, int DenomFDisp, int DenomGDisp, int DenomHDisp, int DenomALoaded, int DenomBLoaded, int DenomCLoaded, int DenomDLoaded, int DenomELoaded, int DenomFLoaded, int DenomGLoaded, int DenomHLoaded )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        char Input_AtmId[ 17 ];
		char Input_BatchId[ 13 ];
        char Input_UserId[ 51 ];
        char Input_GenDate[ 7 ];
        int Input_GenTime;
        char Input_Status;
        int Input_DenomADisp;
        int Input_DenomBDisp;
        int Input_DenomCDisp;
        int Input_DenomDDisp;
        int Input_DenomEDisp;
        int Input_DenomFDisp;
        int Input_DenomGDisp;
        int Input_DenomHDisp;
        int Input_DenomALoaded;
        int Input_DenomBLoaded;
        int Input_DenomCLoaded;
        int Input_DenomDLoaded;
        int Input_DenomELoaded;
        int Input_DenomFLoaded;
        int Input_DenomGLoaded;
        int Input_DenomHLoaded;
    /* EXEC SQL END DECLARE SECTION; */ 

    
    /* EXEC SQL VAR Input_AtmId IS STRING(17); */ 

	/* EXEC SQL VAR Input_BatchId IS STRING(13); */ 

	/* EXEC SQL VAR Input_UserId IS STRING(51); */ 

	/* EXEC SQL VAR Input_GenDate IS STRING(7); */ 

	
	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( Input_BatchId, 0, sizeof( Input_BatchId ) );
	memset( Input_UserId, 0, sizeof( Input_UserId ) );
	memset( Input_GenDate, 0, sizeof( Input_GenDate ) );
	
	strcpy( Input_AtmId, AtmId );
	strcpy( Input_BatchId, BatchId );
	strcpy( Input_UserId, UserId );
	sprintf( Input_GenDate, "%06d", GenDate );
	Input_GenTime = GenTime;
	Input_Status = 'O';
	
	Input_DenomADisp = 0;
	Input_DenomBDisp = 0;
	Input_DenomCDisp = 0;
	Input_DenomDDisp = 0;
	Input_DenomEDisp = 0;
	Input_DenomFDisp = 0;
	Input_DenomGDisp = 0;
	Input_DenomHDisp = 0;
	
	Input_DenomALoaded = 0;
	Input_DenomBLoaded = 0;
	Input_DenomCLoaded = 0;
	Input_DenomDLoaded = 0;
	Input_DenomELoaded = 0;
	Input_DenomFLoaded = 0;
	Input_DenomGLoaded = 0;
	Input_DenomHLoaded = 0;
	
	/* EXEC SQL INSERT INTO EZATMBATCHINFO
	(
		ATMID,
		BATCHID,
		USERID,
		GENDATE,
		GENTIME,
		STATUS,
		DENOM_A_NOTESLOADED,
		DENOM_A_NOTESDISP,
		DENOM_B_NOTESLOADED,
		DENOM_B_NOTESDISP,
		DENOM_C_NOTESLOADED,
		DENOM_C_NOTESDISP,
		DENOM_D_NOTESLOADED,
		DENOM_D_NOTESDISP,
		DENOM_E_NOTESLOADED,
		DENOM_E_NOTESDISP,
		DENOM_F_NOTESLOADED,
		DENOM_F_NOTESDISP,
		DENOM_G_NOTESLOADED,
		DENOM_G_NOTESDISP,
		DENOM_H_NOTESLOADED,
		DENOM_H_NOTESDISP
	)
	VALUES
	(
		:Input_AtmId,
		:Input_BatchId,
		:Input_UserId,
		to_date( :Input_GenDate, 'DDMMYY' ),
		:Input_GenTime,
		:Input_Status,
		:Input_DenomADisp,
		:Input_DenomBDisp,
		:Input_DenomCDisp,
		:Input_DenomDDisp,
		:Input_DenomEDisp,
		:Input_DenomFDisp,
		:Input_DenomGDisp,
		:Input_DenomHDisp,
		:Input_DenomALoaded,
		:Input_DenomBLoaded,
		:Input_DenomCLoaded,
		:Input_DenomDLoaded,
		:Input_DenomELoaded,
		:Input_DenomFLoaded,
		:Input_DenomGLoaded,
		:Input_DenomHLoaded
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMBATCHINFO (ATMID,BATCHID,USERID,GENDATE,GEN\
TIME,STATUS,DENOM_A_NOTESLOADED,DENOM_A_NOTESDISP,DENOM_B_NOTESLOADED,DENOM_B_\
NOTESDISP,DENOM_C_NOTESLOADED,DENOM_C_NOTESDISP,DENOM_D_NOTESLOADED,DENOM_D_NO\
TESDISP,DENOM_E_NOTESLOADED,DENOM_E_NOTESDISP,DENOM_F_NOTESLOADED,DENOM_F_NOTE\
SDISP,DENOM_G_NOTESLOADED,DENOM_G_NOTESDISP,DENOM_H_NOTESLOADED,DENOM_H_NOTESD\
ISP) values (:b0,:b1,:b2,to_date(:b3,'DDMMYY'),:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b\
11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )959;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)Input_BatchId;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)Input_UserId;
 sqlstm.sqhstl[2] = (unsigned int  )51;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_GenDate;
 sqlstm.sqhstl[3] = (unsigned int  )7;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&Input_GenTime;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&Input_Status;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&Input_DenomBDisp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&Input_DenomCDisp;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&Input_DenomDDisp;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&Input_DenomEDisp;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&Input_DenomFDisp;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&Input_DenomGDisp;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&Input_DenomHDisp;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&Input_DenomBLoaded;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&Input_DenomCLoaded;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&Input_DenomDLoaded;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&Input_DenomELoaded;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&Input_DenomFLoaded;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&Input_DenomGLoaded;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&Input_DenomHLoaded;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
	else
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 27;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1062;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
	return sqlca.sqlcode;
}

int closeBatch( const char *AtmId, const char *BatchId, const char *UserId, int GenDate, int GenTime, int DenomADisp, int DenomBDisp, int DenomCDisp, int DenomDDisp, int DenomEDisp, int DenomFDisp, int DenomGDisp, int DenomHDisp, int DenomALoaded, int DenomBLoaded, int DenomCLoaded, int DenomDLoaded, int DenomELoaded, int DenomFLoaded, int DenomGLoaded, int DenomHLoaded )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        char Input_AtmId[ 17 ];
		char Input_BatchId[ 13 ];
        char Input_UserId[ 51 ];
        char Input_GenDate[ 7 ];
        int Input_GenTime;
        char Input_Status;
        int Input_DenomADisp;
        int Input_DenomBDisp;
        int Input_DenomCDisp;
        int Input_DenomDDisp;
        int Input_DenomEDisp;
        int Input_DenomFDisp;
        int Input_DenomGDisp;
        int Input_DenomHDisp;
        int Input_DenomALoaded;
        int Input_DenomBLoaded;
        int Input_DenomCLoaded;
        int Input_DenomDLoaded;
        int Input_DenomELoaded;
        int Input_DenomFLoaded;
        int Input_DenomGLoaded;
        int Input_DenomHLoaded;
    /* EXEC SQL END DECLARE SECTION; */ 

    
    /* EXEC SQL VAR Input_AtmId IS STRING(17); */ 

	/* EXEC SQL VAR Input_BatchId IS STRING(13); */ 

	/* EXEC SQL VAR Input_UserId IS STRING(51); */ 

	/* EXEC SQL VAR Input_GenDate IS STRING(7); */ 

	
	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( Input_BatchId, 0, sizeof( Input_BatchId ) );
	memset( Input_UserId, 0, sizeof( Input_UserId ) );
	memset( Input_GenDate, 0, sizeof( Input_GenDate ) );
		
	strcpy( Input_AtmId, AtmId );
	strcpy( Input_BatchId, BatchId );
	strcpy( Input_UserId, UserId );
	sprintf( Input_GenDate, "%06d", GenDate );
	Input_GenTime = GenTime;
	Input_Status = 'C';
	
	Input_DenomADisp = DenomADisp;
	Input_DenomBDisp = DenomBDisp;
	Input_DenomCDisp = DenomCDisp;
	Input_DenomDDisp = DenomDDisp;
	Input_DenomEDisp = DenomEDisp;
	Input_DenomFDisp = DenomFDisp;
	Input_DenomGDisp = DenomGDisp;
	Input_DenomHDisp = DenomHDisp;
	
	Input_DenomALoaded = DenomALoaded;
	Input_DenomBLoaded = DenomBLoaded;
	Input_DenomCLoaded = DenomCLoaded;
	Input_DenomDLoaded = DenomDLoaded;
	Input_DenomELoaded = DenomELoaded;
	Input_DenomFLoaded = DenomFLoaded;
	Input_DenomGLoaded = DenomGLoaded;
	Input_DenomHLoaded = DenomHLoaded;
	
	/* EXEC SQL INSERT INTO EZATMBATCHINFO
	(
		ATMID,
		BATCHID,
		USERID,
		GENDATE,
		GENTIME,
		STATUS,
		DENOM_A_NOTESLOADED,
		DENOM_A_NOTESDISP,
		DENOM_B_NOTESLOADED,
		DENOM_B_NOTESDISP,
		DENOM_C_NOTESLOADED,
		DENOM_C_NOTESDISP,
		DENOM_D_NOTESLOADED,
		DENOM_D_NOTESDISP,
		DENOM_E_NOTESLOADED,
		DENOM_E_NOTESDISP,
		DENOM_F_NOTESLOADED,
		DENOM_F_NOTESDISP,
		DENOM_G_NOTESLOADED,
		DENOM_G_NOTESDISP,
		DENOM_H_NOTESLOADED,
		DENOM_H_NOTESDISP
	)
	VALUES
	(
		:Input_AtmId,
		:Input_BatchId,
		:Input_UserId,
		to_date( :Input_GenDate, 'DDMMYY' ),
		:Input_GenTime,
		:Input_Status,
		:Input_DenomALoaded,
		:Input_DenomADisp,
		:Input_DenomBLoaded,
		:Input_DenomBDisp,
		:Input_DenomCLoaded,
		:Input_DenomCDisp,
		:Input_DenomDLoaded,
		:Input_DenomDDisp,
		:Input_DenomELoaded,
		:Input_DenomEDisp,
		:Input_DenomFLoaded,
		:Input_DenomFDisp,
		:Input_DenomGLoaded,
		:Input_DenomGDisp,
		:Input_DenomHLoaded,
		:Input_DenomHDisp
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMBATCHINFO (ATMID,BATCHID,USERID,GENDATE,GEN\
TIME,STATUS,DENOM_A_NOTESLOADED,DENOM_A_NOTESDISP,DENOM_B_NOTESLOADED,DENOM_B_\
NOTESDISP,DENOM_C_NOTESLOADED,DENOM_C_NOTESDISP,DENOM_D_NOTESLOADED,DENOM_D_NO\
TESDISP,DENOM_E_NOTESLOADED,DENOM_E_NOTESDISP,DENOM_F_NOTESLOADED,DENOM_F_NOTE\
SDISP,DENOM_G_NOTESLOADED,DENOM_G_NOTESDISP,DENOM_H_NOTESLOADED,DENOM_H_NOTESD\
ISP) values (:b0,:b1,:b2,to_date(:b3,'DDMMYY'),:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b\
11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1077;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)Input_BatchId;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)Input_UserId;
 sqlstm.sqhstl[2] = (unsigned int  )51;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_GenDate;
 sqlstm.sqhstl[3] = (unsigned int  )7;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&Input_GenTime;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&Input_Status;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&Input_DenomBLoaded;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&Input_DenomBDisp;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&Input_DenomCLoaded;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&Input_DenomCDisp;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&Input_DenomDLoaded;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&Input_DenomDDisp;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&Input_DenomELoaded;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&Input_DenomEDisp;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&Input_DenomFLoaded;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&Input_DenomFDisp;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&Input_DenomGLoaded;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&Input_DenomGDisp;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&Input_DenomHLoaded;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&Input_DenomHDisp;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
	else
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 27;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1180;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
	return sqlca.sqlcode;
}

int updateBatchInAtmDataInfo( const char *AtmId, const char *BatchId )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        char Input_AtmId[ 17 ];
		char Input_BatchId[ 25 ];
    /* EXEC SQL END DECLARE SECTION; */ 

    
    /* EXEC SQL VAR Input_AtmId IS STRING(17); */ 

	/* EXEC SQL VAR Input_BatchId IS STRING(25); */ 

	
	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( Input_BatchId, 0, sizeof( Input_BatchId ) );
	
	strcpy( Input_AtmId, AtmId );
	strcpy( Input_BatchId, BatchId );
	
	/* EXEC SQL UPDATE EZATMDATAINFO SET BATCHID = :Input_BatchId WHERE TRIM(ATMID)=:Input_AtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMDATAINFO  set BATCHID=:b0 where trim(ATMID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1195;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_BatchId;
 sqlstm.sqhstl[0] = (unsigned int  )25;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
    	return ( sqlca.sqlcode );
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 27;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1218;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
		return ( sqlca.sqlcode );
	}
}

int updateDenomStatusResetDateTime( const char *AtmId, int ResetDate, int ResetTime )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        char Input_AtmId[ 17 ];
		int Input_DenomALoaded;
        int Input_DenomBLoaded;
        int Input_DenomCLoaded;
        int Input_DenomDLoaded;
        int Input_DenomELoaded;
        int Input_DenomFLoaded;
        int Input_DenomGLoaded;
        int Input_DenomHLoaded;
        int Input_DenomADisp;
        int Input_DenomBDisp;
        int Input_DenomCDisp;
        int Input_DenomDDisp;
        int Input_DenomEDisp;
        int Input_DenomFDisp;
        int Input_DenomGDisp;
        int Input_DenomHDisp;
        int Input_DenomAMin;
        int Input_DenomBMin;
        int Input_DenomCMin;
        int Input_DenomDMin;
        int Input_DenomEMin;
        int Input_DenomFMin;
        int Input_DenomGMin;
        int Input_DenomHMin;
        char Input_ResetDate[ 7 ];
        int Input_ResetTime;
    /* EXEC SQL END DECLARE SECTION; */ 

    
    /* EXEC SQL VAR Input_AtmId IS STRING(17); */ 

	/* EXEC SQL VAR Input_ResetDate IS STRING(7); */ 

	
	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( Input_ResetDate, 0, sizeof( Input_ResetDate ) );
	
	strcpy( Input_AtmId, AtmId );
	sprintf( Input_ResetDate, "%06d", ResetDate );
	Input_ResetTime = ResetTime;
	Input_DenomALoaded = 0;
	Input_DenomADisp = 0;
	Input_DenomBLoaded = 0;
	Input_DenomBDisp = 0;
	Input_DenomCLoaded = 0;
	Input_DenomCDisp = 0;
	Input_DenomDLoaded = 0;
	Input_DenomDDisp = 0;
	Input_DenomELoaded = 0;
	Input_DenomEDisp = 0;
	Input_DenomFLoaded = 0;
	Input_DenomFDisp = 0;
	Input_DenomGLoaded = 0;
	Input_DenomGDisp = 0;
	Input_DenomHLoaded = 0;
	Input_DenomHDisp = 0;
	
	/* EXEC SQL UPDATE EZATMDENOMSTATUS SET
		DENOM_A_NOTESLOADED = :Input_DenomALoaded,
		DENOM_A_NOTESDISP = :Input_DenomADisp,
		DENOM_B_NOTESLOADED = :Input_DenomALoaded,
		DENOM_B_NOTESDISP = :Input_DenomADisp,
		DENOM_C_NOTESLOADED = :Input_DenomALoaded,
		DENOM_C_NOTESDISP = :Input_DenomADisp,
		DENOM_D_NOTESLOADED = :Input_DenomALoaded,
		DENOM_D_NOTESDISP = :Input_DenomADisp,
		DENOM_E_NOTESLOADED = :Input_DenomALoaded,
		DENOM_E_NOTESDISP = :Input_DenomADisp,
		DENOM_F_NOTESLOADED = :Input_DenomALoaded,
		DENOM_F_NOTESDISP = :Input_DenomADisp,
		DENOM_G_NOTESLOADED = :Input_DenomALoaded,
		DENOM_G_NOTESDISP = :Input_DenomADisp,
		DENOM_H_NOTESLOADED = :Input_DenomALoaded,
		DENOM_H_NOTESDISP = :Input_DenomADisp,
		LASTRESETDATE = to_date( :Input_ResetDate, 'dd-mm-yy' ), 
		LASTRESETTIME = :Input_ResetTime
	WHERE TRIM(ATMID)=:Input_AtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMDENOMSTATUS  set DENOM_A_NOTESLOADED=:b0,DENOM_A\
_NOTESDISP=:b1,DENOM_B_NOTESLOADED=:b0,DENOM_B_NOTESDISP=:b1,DENOM_C_NOTESLOAD\
ED=:b0,DENOM_C_NOTESDISP=:b1,DENOM_D_NOTESLOADED=:b0,DENOM_D_NOTESDISP=:b1,DEN\
OM_E_NOTESLOADED=:b0,DENOM_E_NOTESDISP=:b1,DENOM_F_NOTESLOADED=:b0,DENOM_F_NOT\
ESDISP=:b1,DENOM_G_NOTESLOADED=:b0,DENOM_G_NOTESDISP=:b1,DENOM_H_NOTESLOADED=:\
b0,DENOM_H_NOTESDISP=:b1,LASTRESETDATE=to_date(:b16,'dd-mm-yy'),LASTRESETTIME=\
:b17 where trim(ATMID)=:b18";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1233;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)Input_ResetDate;
 sqlstm.sqhstl[16] = (unsigned int  )7;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&Input_ResetTime;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[18] = (unsigned int  )17;
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode == 0 )
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 27;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1324;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


    	return sqlca.sqlcode;
    }
    
    if( sqlca.sqlcode != 1403 )
    	return sqlca.sqlcode;
    	
   	Input_DenomAMin = 50;
	Input_DenomBMin = 50;
	Input_DenomCMin = 50;
	Input_DenomDMin = 50;
	Input_DenomEMin = 50;
	Input_DenomFMin = 50;
	Input_DenomGMin = 50;
	Input_DenomHMin = 50;
	
	Input_DenomADisp = 0;
	Input_DenomBDisp = 0;
	Input_DenomCDisp = 0;
	Input_DenomDDisp = 0;
	Input_DenomEDisp = 0;
	Input_DenomFDisp = 0;
	Input_DenomGDisp = 0;
	Input_DenomHDisp = 0;
		
	Input_DenomALoaded = 0;
	Input_DenomBLoaded = 0;
	Input_DenomCLoaded = 0;
	Input_DenomDLoaded = 0;
	Input_DenomELoaded = 0;
	Input_DenomFLoaded = 0;
	Input_DenomGLoaded = 0;
	Input_DenomHLoaded = 0;
			
	/* EXEC SQL INSERT INTO EZATMDENOMSTATUS
	(
		ATMID,
		DENOM_A_NOTESLOADED,
		DENOM_A_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_B_NOTESLOADED,
		DENOM_B_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_C_NOTESLOADED,
		DENOM_C_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_D_NOTESLOADED,
		DENOM_D_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_E_NOTESLOADED,
		DENOM_E_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_F_NOTESLOADED,
		DENOM_F_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_G_NOTESLOADED,
		DENOM_G_NOTESDISP,
		DENOM_A_NOTESMIN,
		DENOM_H_NOTESLOADED,
		DENOM_H_NOTESDISP,
		DENOM_A_NOTESMIN,
		LASTRESETDATE,
		LASTRESETTIME
	)
	VALUES
	(
		:Input_AtmId,
		:Input_DenomALoaded,
		:Input_DenomADisp,
		:Input_DenomAMin,
		:Input_DenomBLoaded,
		:Input_DenomBDisp,
		:Input_DenomBMin,
		:Input_DenomCLoaded,
		:Input_DenomCDisp,
		:Input_DenomCMin,
		:Input_DenomDLoaded,
		:Input_DenomDDisp,
		:Input_DenomDMin,
		:Input_DenomELoaded,
		:Input_DenomEDisp,
		:Input_DenomEMin,
		:Input_DenomFLoaded,
		:Input_DenomFDisp,
		:Input_DenomFMin,
		:Input_DenomGLoaded,
		:Input_DenomGDisp,
		:Input_DenomGMin,
		:Input_DenomHLoaded,
		:Input_DenomHDisp,
		:Input_DenomHMin,
		to_date( :Input_ResetDate, 'dd-mm-yy' ),
		:Input_ResetTime	
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMDENOMSTATUS (ATMID,DENOM_A_NOTESLOADED,DENO\
M_A_NOTESDISP,DENOM_A_NOTESMIN,DENOM_B_NOTESLOADED,DENOM_B_NOTESDISP,DENOM_A_N\
OTESMIN,DENOM_C_NOTESLOADED,DENOM_C_NOTESDISP,DENOM_A_NOTESMIN,DENOM_D_NOTESLO\
ADED,DENOM_D_NOTESDISP,DENOM_A_NOTESMIN,DENOM_E_NOTESLOADED,DENOM_E_NOTESDISP,\
DENOM_A_NOTESMIN,DENOM_F_NOTESLOADED,DENOM_F_NOTESDISP,DENOM_A_NOTESMIN,DENOM_\
G_NOTESLOADED,DENOM_G_NOTESDISP,DENOM_A_NOTESMIN,DENOM_H_NOTESLOADED,DENOM_H_N\
OTESDISP,DENOM_A_NOTESMIN,LASTRESETDATE,LASTRESETTIME) values (:b0,:b1,:b2,:b3\
,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b2\
0,:b21,:b22,:b23,:b24,to_date(:b25,'dd-mm-yy'),:b26)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1339;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&Input_DenomALoaded;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&Input_DenomADisp;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&Input_DenomAMin;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&Input_DenomBLoaded;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&Input_DenomBDisp;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&Input_DenomBMin;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&Input_DenomCLoaded;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&Input_DenomCDisp;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&Input_DenomCMin;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&Input_DenomDLoaded;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&Input_DenomDDisp;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&Input_DenomDMin;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&Input_DenomELoaded;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&Input_DenomEDisp;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&Input_DenomEMin;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&Input_DenomFLoaded;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&Input_DenomFDisp;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&Input_DenomFMin;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&Input_DenomGLoaded;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&Input_DenomGDisp;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&Input_DenomGMin;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&Input_DenomHLoaded;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&Input_DenomHDisp;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&Input_DenomHMin;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)Input_ResetDate;
 sqlstm.sqhstl[25] = (unsigned int  )7;
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&Input_ResetTime;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
	else
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 27;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1462;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
	return sqlca.sqlcode;
}

int readEzPOSMCCInfo( int I_MCC, struct EzPOSMCCInfo *posmccinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int MCC;
		char Description[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR Description IS STRING(33); */ 

	
	memset( Description, 0, sizeof( Description ) );
	MCC = I_MCC;
	
	/* EXEC SQL SELECT
		RTRIM(DESCRIPTION)
	INTO
		:Description
	FROM EZPOSMCCINFO WHERE MCC=:MCC; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DESCRIPTION) into :b0  from EZPOSMCCINFO where \
MCC=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1477;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Description;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&MCC;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	posmccinfo_rec->MCC = MCC;
	strcpy( posmccinfo_rec->Description, Description );
	return sqlca.sqlcode;
}

int readEzPOSMerchantTypeInfo( const char *I_MerchantType, struct EzPOSMerchantTypeInfo *posmerchanttypeinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MerchantType[ 17 ];
		char Description[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MerchantType IS STRING(17); */ 

	/* EXEC SQL VAR Description IS STRING(33); */ 

	
	memset( MerchantType, 0, sizeof( MerchantType ) );
	memset( Description, 0, sizeof( Description ) );
	
	strcpy( MerchantType, I_MerchantType );
	
	/* EXEC SQL SELECT
		RTRIM(DESCRIPTION)
	INTO
		:Description	
	FROM EZPOSMERCHANTTYPEINFO WHERE RTRIM(MERCHANTTYPE)=:MerchantType; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DESCRIPTION) into :b0  from EZPOSMERCHANTTYPEIN\
FO where RTRIM(MERCHANTTYPE)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1500;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Description;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)MerchantType;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
		
	strcpy( posmerchanttypeinfo_rec->Description, Description );
	return sqlca.sqlcode;
}

int readEzPOSMerchantInfo( const char *I_MerchantId, struct EzPOSMerchantInfo *posmerchantinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char MerchantType[ 17 ];
		char MerchantName[ 33 ];
		char MCCList[ 129 ];
		char TxnList[ 65 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR MerchantType IS STRING(17); */ 

	/* EXEC SQL VAR MerchantName IS STRING(33); */ 

	/* EXEC SQL VAR MCCList IS STRING(129); */ 

	/* EXEC SQL VAR TxnList IS STRING(65); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( MerchantType, 0, sizeof( MerchantType ) );
	memset( MerchantName, 0, sizeof( MerchantName ) );
	memset( MCCList, 0, sizeof( MCCList ) );
	memset( TxnList, 0, sizeof( TxnList ) );
	
	strcpy( MerchantId, I_MerchantId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(MERCHANTID),
		RTRIM(MERCHANTTYPE),
		RTRIM(MERCHANTNAME),
		RTRIM(MCCLIST),
		RTRIM(TXNLIST)
	INTO
		:InstId,
		:MerchantId,
		:MerchantType,
		:MerchantName,
		:MCCList,
		:TxnList
	FROM EZPOSMERCHANTINFO WHERE RTRIM(MERCHANTID)=:MerchantId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(MERCHANTID) ,RTRIM(MERCHANTTYPE)\
 ,RTRIM(MERCHANTNAME) ,RTRIM(MCCLIST) ,RTRIM(TXNLIST) into :b0,:b1,:b2,:b3,:b4\
,:b5  from EZPOSMERCHANTINFO where RTRIM(MERCHANTID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1523;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)MerchantId;
 sqlstm.sqhstl[1] = (unsigned int  )16;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MerchantType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MerchantName;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)MCCList;
 sqlstm.sqhstl[4] = (unsigned int  )129;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)TxnList;
 sqlstm.sqhstl[5] = (unsigned int  )65;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)MerchantId;
 sqlstm.sqhstl[6] = (unsigned int  )16;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( posmerchantinfo_rec->InstId, InstId );
	strcpy( posmerchantinfo_rec->MerchantId, MerchantId );
	strcpy( posmerchantinfo_rec->MerchantType, MerchantType );
	strcpy( posmerchantinfo_rec->MerchantName, MerchantName );
	strcpy( posmerchantinfo_rec->MCCList, MCCList );	
	strcpy( posmerchantinfo_rec->TxnList, TxnList );
	return sqlca.sqlcode;
}

int readEzPOSTerminalTypeInfo( const char *I_TerminalType, struct EzPOSTerminalTypeInfo *posterminaltypeinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TerminalType[ 17 ];
		char Description[ 33 ];
		char TxnCodeGroupId[ 17 ];
		char RespCodeGroupId[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TerminalType IS STRING(33); */ 

	/* EXEC SQL VAR Description IS STRING(33); */ 

	/* EXEC SQL VAR TxnCodeGroupId IS STRING(33); */ 

	/* EXEC SQL VAR RespCodeGroupId IS STRING(33); */ 

	
	memset( TerminalType, 0, sizeof( TerminalType ) );
	memset( Description, 0, sizeof( Description ) );
	memset( TxnCodeGroupId, 0, sizeof( TxnCodeGroupId ) );
	memset( RespCodeGroupId, 0, sizeof( RespCodeGroupId ) );
	
	strcpy( TerminalType, I_TerminalType );
	
	/* EXEC SQL SELECT
		RTRIM(DESCRIPTION),
		RTRIM(TXNCODEGROUPID),
		RTRIM(RESPCODEGROUPID)
	INTO
		:Description,
		:TxnCodeGroupId,
		:RespCodeGroupId
	FROM EZPOSTERMINALTYPEINFO WHERE RTRIM(TERMINALTYPE)=:TerminalType; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DESCRIPTION) ,RTRIM(TXNCODEGROUPID) ,RTRIM(RESP\
CODEGROUPID) into :b0,:b1,:b2  from EZPOSTERMINALTYPEINFO where RTRIM(TERMINAL\
TYPE)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1566;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Description;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnCodeGroupId;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)RespCodeGroupId;
 sqlstm.sqhstl[2] = (unsigned int  )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TerminalType;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( posterminaltypeinfo_rec->TerminalType, TerminalType );
	strcpy( posterminaltypeinfo_rec->TxnCodeGroupId, TxnCodeGroupId );
	strcpy( posterminaltypeinfo_rec->RespCodeGroupId, RespCodeGroupId );
	strcpy( posterminaltypeinfo_rec->Description, Description );
	return sqlca.sqlcode;
}

int readEzPOSTerminalInfo( const char *I_POSId, struct EzPOSTerminalInfo *posterminalinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char POSId[ 33 ];
		char InstId[ 13 ];
		char TerminalId[ 9 ];
		char MerchantId[ 16 ];
		int MCC;
		char TermMasterKey[ 49 ];
		char TermPINKey[ 49 ];
		char TermMACKey[ 49 ];
		char TerminalLocation[ 33 ];
		char TerminalType[ 17 ];
		char TerminalStatus;
		char StoreId[ 33 ];
		char AcquirerCode[ 13 ];
		int CurrencyCode;
		int CountryCode;
		int PinCapCode;
		char BatchId[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR POSId IS STRING(33); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR TerminalId IS STRING(9); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR TermMasterKey IS STRING(49); */ 

	/* EXEC SQL VAR TermPINKey IS STRING(49); */ 

	/* EXEC SQL VAR TermMACKey IS STRING(49); */ 

	/* EXEC SQL VAR TerminalLocation IS STRING(33); */ 

	/* EXEC SQL VAR TerminalType IS STRING(17); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR AcquirerCode IS STRING(13); */ 

	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	
	memset( POSId, 0, sizeof( POSId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
	memset( TermPINKey, 0, sizeof( TermPINKey ) );
	memset( TermMACKey, 0, sizeof( TermMACKey ) );
	memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
	memset( TerminalType, 0, sizeof( TerminalType ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( AcquirerCode, 0, sizeof( AcquirerCode ) );
	memset( BatchId, 0, sizeof( BatchId ) );
	
	strcpy( POSId, I_POSId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(TERMINALID),
		RTRIM(MERCHANTID),
		MCC,
		RTRIM(TERMMASTERKEY),
		RTRIM(TERMPINKEY),
		RTRIM(TERMMACKEY),
		RTRIM(TERMINALLOCATION),
		RTRIM(TERMINALTYPE),
		TERMINALSTATUS,
		RTRIM(STOREID),
		RTRIM(ACQUIRERCODE),
		CURRENCYCODE,
		COUNTRYCODE,
		PINCAPCODE,
		RTRIM(BATCHID)
	INTO
		:InstId,
		:TerminalId,
		:MerchantId,
		:MCC,
		:TermMasterKey,
		:TermPINKey,
		:TermMACKey,
		:TerminalLocation,
		:TerminalType,
		:TerminalStatus,
		:StoreId,
		:AcquirerCode,
		:CurrencyCode,
		:CountryCode,
		:PinCapCode,
		:BatchId
	FROM EZPOSTERMINALINFO WHERE RTRIM(POSID)=:POSId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(TERMINALID) ,RTRIM(MERCHANTID) ,\
MCC ,RTRIM(TERMMASTERKEY) ,RTRIM(TERMPINKEY) ,RTRIM(TERMMACKEY) ,RTRIM(TERMINA\
LLOCATION) ,RTRIM(TERMINALTYPE) ,TERMINALSTATUS ,RTRIM(STOREID) ,RTRIM(ACQUIRE\
RCODE) ,CURRENCYCODE ,COUNTRYCODE ,PINCAPCODE ,RTRIM(BATCHID) into :b0,:b1,:b2\
,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15  from EZPOSTERMINAL\
INFO where RTRIM(POSID)=:b16";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1597;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TerminalId;
 sqlstm.sqhstl[1] = (unsigned int  )9;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MerchantId;
 sqlstm.sqhstl[2] = (unsigned int  )16;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&MCC;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TermMasterKey;
 sqlstm.sqhstl[4] = (unsigned int  )49;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)TermPINKey;
 sqlstm.sqhstl[5] = (unsigned int  )49;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)TermMACKey;
 sqlstm.sqhstl[6] = (unsigned int  )49;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)TerminalLocation;
 sqlstm.sqhstl[7] = (unsigned int  )33;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)TerminalType;
 sqlstm.sqhstl[8] = (unsigned int  )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&TerminalStatus;
 sqlstm.sqhstl[9] = (unsigned int  )1;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)StoreId;
 sqlstm.sqhstl[10] = (unsigned int  )33;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)AcquirerCode;
 sqlstm.sqhstl[11] = (unsigned int  )13;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&CurrencyCode;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&CountryCode;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&PinCapCode;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)BatchId;
 sqlstm.sqhstl[15] = (unsigned int  )13;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)POSId;
 sqlstm.sqhstl[16] = (unsigned int  )33;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( posterminalinfo_rec->POSId, POSId );
	strcpy( posterminalinfo_rec->TerminalId, TerminalId );
	strcpy( posterminalinfo_rec->MerchantId, MerchantId );
	posterminalinfo_rec->MCC = MCC;
	strcpy( posterminalinfo_rec->TermMasterKey, TermMasterKey );
	strcpy( posterminalinfo_rec->TermPINKey, TermPINKey );
	strcpy( posterminalinfo_rec->TermMACKey, TermMACKey );
	strcpy( posterminalinfo_rec->TerminalLocation, TerminalLocation );
	strcpy( posterminalinfo_rec->TerminalType, TerminalType );
	posterminalinfo_rec->TerminalStatus = TerminalStatus;
	strcpy( posterminalinfo_rec->StoreId, StoreId );
	strcpy( posterminalinfo_rec->AcquirerCode, AcquirerCode );
	posterminalinfo_rec->CurrencyCode = CurrencyCode;
	posterminalinfo_rec->CountryCode = CountryCode;
	posterminalinfo_rec->PinCapCode = PinCapCode;
	strcpy( posterminalinfo_rec->BatchId, BatchId );
	
	return sqlca.sqlcode;
}

int readEzPOSStoreInfo( const char *I_StoreId, struct EzPOSStoreInfo *posstoreinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char StoreId[ 33 ];
		char MerchantId[ 16 ];
		char StoreName[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreName IS STRING(33); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreName, 0, sizeof( StoreName ) );
	
	strcpy( StoreId, I_StoreId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(MERCHANTID),
		RTRIM(STORENAME)
	INTO
		:InstId,
		:MerchantId,
		:StoreName
	FROM EZPOSSTOREINFO WHERE RTRIM(STOREID)=:StoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(MERCHANTID) ,RTRIM(STORENAME) in\
to :b0,:b1,:b2  from EZPOSSTOREINFO where RTRIM(STOREID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1680;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)MerchantId;
 sqlstm.sqhstl[1] = (unsigned int  )16;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)StoreName;
 sqlstm.sqhstl[2] = (unsigned int  )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)StoreId;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( posstoreinfo_rec->InstId, InstId );
	strcpy( posstoreinfo_rec->StoreId, StoreId );
	strcpy( posstoreinfo_rec->MerchantId, MerchantId );
	strcpy( posstoreinfo_rec->StoreName, StoreName );
	
	return sqlca.sqlcode;
}

int readEzPOSTxnInfo( const char *I_TxnCodeGroupId, struct EzPOSTxnInfo *postxninfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnCodeGroupId[ 17 ];
		char TxnCodeList[ 129 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TxnCodeGroupId IS STRING(17); */ 

	/* EXEC SQL VAR TxnCodeList IS STRING(129); */ 

	
	memset( TxnCodeGroupId, 0, sizeof( TxnCodeGroupId ) );
	memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
	
	strcpy( TxnCodeGroupId, I_TxnCodeGroupId );
	
	/* EXEC SQL SELECT
		RTRIM(TXNCODELIST)
	INTO
		:TxnCodeList
	FROM EZPOSTXNINFO WHERE RTRIM(TXNCODEGROUPID)=:TxnCodeGroupId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TXNCODELIST) into :b0  from EZPOSTXNINFO where \
RTRIM(TXNCODEGROUPID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1711;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)TxnCodeList;
 sqlstm.sqhstl[0] = (unsigned int  )129;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnCodeGroupId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( postxninfo_rec->TxnCodeGroupId, TxnCodeGroupId );
	strcpy( postxninfo_rec->TxnCodeList, TxnCodeList );
	
	return sqlca.sqlcode;
}

int readEzPOSRespCodeInfo( const char *I_RecordId, struct EzPOSRespCodeInfo *posrespcodeinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char RespCodeGroupId[ 17 ];
		short RespCode;
		short POSRespCode;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR RespCodeGroupId IS STRING(17); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( RespCodeGroupId, 0, sizeof( RespCodeGroupId ) );
		
	strcpy( RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(RESPCODEGROUPID),
		RESPCODE,
		POSRESPCODE
	INTO
		:RespCodeGroupId,
		:RespCode,
		:POSRespCode
	FROM EZPOSRESPCODEINFO WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RESPCODEGROUPID) ,RESPCODE ,POSRESPCODE into :b\
0,:b1,:b2  from EZPOSRESPCODEINFO where RTRIM(RECORDID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1734;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)RespCodeGroupId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&RespCode;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&POSRespCode;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)RecordId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( posrespcodeinfo_rec->RecordId, RecordId );
	strcpy( posrespcodeinfo_rec->RespCodeGroupId, RespCodeGroupId );
	posrespcodeinfo_rec->RespCode = RespCode;
	posrespcodeinfo_rec->POSRespCode = POSRespCode;
	
	return sqlca.sqlcode;
}

int readEzStatusAlert( const char *I_RecordId, struct EzStatusAlertMemory *statusalert_rec )
{
        /* EXEC SQL BEGIN DECLARE SECTION; */ 

                char RecordId[17];
                char InstId[17];
                char DeviceId[ 33 ];
                char AlertType[ 17 ];
                char StatusList[ 129 ];
                char SMSReq;
                char MailReq;
                char SMSAlertGroupId[ 17 ];
                char MailAlertGroupId[ 17 ];
        /* EXEC SQL END DECLARE SECTION; */ 


        /* EXEC SQL VAR RecordId IS STRING(17); */ 

        /* EXEC SQL VAR InstId IS STRING(17); */ 

        /* EXEC SQL VAR DeviceId IS STRING(33); */ 

        /* EXEC SQL VAR AlertType IS STRING(17); */ 

        /* EXEC SQL VAR StatusList IS STRING(129); */ 

        /* EXEC SQL VAR SMSAlertGroupId IS STRING(17); */ 

        /* EXEC SQL VAR MailAlertGroupId IS STRING(17); */ 


        memset( RecordId, 0, sizeof( RecordId ) );
        memset( InstId, 0, sizeof( InstId ) );
        memset( DeviceId, 0, sizeof( DeviceId ) );
        memset( AlertType, 0, sizeof( AlertType ) );
        memset( StatusList, 0, sizeof( StatusList ) );
        memset( SMSAlertGroupId, 0, sizeof( SMSAlertGroupId ) );
        memset( MailAlertGroupId, 0, sizeof( MailAlertGroupId ) );

        strcpy( RecordId, I_RecordId );

	/* EXEC SQL SELECT
                RTRIM(INSTID),
                RTRIM(DEVICEID),
                RTRIM(ALERTTYPE),
                RTRIM(STATUSLIST),
                SMSREQ,
                MAILREQ,
                RTRIM(SMSALERTGROUPID),
                RTRIM(MAILALERTGROUPID)
        INTO
                :InstId,
                :DeviceId,
                :AlertType,
                :StatusList,
                :SMSReq,
                :MailReq,
                :SMSAlertGroupId,
                :MailAlertGroupId
        FROM EZSTATUSALERT WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 27;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(DEVICEID) ,RTRIM(ALERTTYPE) ,RTR\
IM(STATUSLIST) ,SMSREQ ,MAILREQ ,RTRIM(SMSALERTGROUPID) ,RTRIM(MAILALERTGROUPI\
D) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7  from EZSTATUSALERT where RTRIM(RECORD\
ID)=:b8";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1765;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)DeviceId;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)AlertType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)StatusList;
 sqlstm.sqhstl[3] = (unsigned int  )129;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SMSReq;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&MailReq;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)SMSAlertGroupId;
 sqlstm.sqhstl[6] = (unsigned int  )17;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)MailAlertGroupId;
 sqlstm.sqhstl[7] = (unsigned int  )17;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)RecordId;
 sqlstm.sqhstl[8] = (unsigned int  )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



        if ( sqlca.sqlcode != 0 )
                return sqlca.sqlcode;

        strcpy( statusalert_rec->RecordId, RecordId );
        strcpy( statusalert_rec->InstId, InstId );
        strcpy( statusalert_rec->DeviceId, DeviceId );
        strcpy( statusalert_rec->AlertType, AlertType );
        strcpy( statusalert_rec->StatusList, StatusList );
        statusalert_rec->SMSReq = SMSReq;
        statusalert_rec->MailReq = MailReq;
        strcpy( statusalert_rec->SMSAlertGroupId, SMSAlertGroupId );
        strcpy( statusalert_rec->MailAlertGroupId, MailAlertGroupId );
        return sqlca.sqlcode;
}

int readEzSMSAlertGroup( const char *I_SMSAlertGroupId, struct EzSMSAlertGroupMemory *smsalertgroup_rec )
{
        /* EXEC SQL BEGIN DECLARE SECTION; */ 

                char SMSAlertGroupId[17];
                char MobileList[ 255 ];
                char TemplateFile[ 33 ];
                char GSMPort[ 33 ];
        /* EXEC SQL END DECLARE SECTION; */ 


        /* EXEC SQL VAR SMSAlertGroupId IS STRING(17); */ 

        /* EXEC SQL VAR MobileList IS STRING(255); */ 

        /* EXEC SQL VAR TemplateFile IS STRING(33); */ 

        /* EXEC SQL VAR GSMPort IS STRING(33); */ 


        memset( SMSAlertGroupId, 0, sizeof( SMSAlertGroupId ) );
        memset( MobileList, 0, sizeof( MobileList ) );
        memset( TemplateFile, 0, sizeof( TemplateFile ) );
        memset( GSMPort, 0, sizeof( GSMPort ) );

        strcpy( SMSAlertGroupId, I_SMSAlertGroupId );

        /* EXEC SQL SELECT
                RTRIM(MOBILELIST),
                RTRIM(TEMPLATEFILE),
                RTRIM(GSMPORT)
        INTO
                :MobileList,
                :TemplateFile,
                :GSMPort
        FROM EZSMSALERTGROUP WHERE RTRIM(SMSALERTGROUPID)=:SMSAlertGroupId; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 27;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select RTRIM(MOBILELIST) ,RTRIM(TEMPLATEFILE) ,RTRIM(\
GSMPORT) into :b0,:b1,:b2  from EZSMSALERTGROUP where RTRIM(SMSALERTGROUPID)=:\
b3";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )1816;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)MobileList;
        sqlstm.sqhstl[0] = (unsigned int  )255;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)TemplateFile;
        sqlstm.sqhstl[1] = (unsigned int  )33;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         void  *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned int  )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (         void  *)GSMPort;
        sqlstm.sqhstl[2] = (unsigned int  )33;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         void  *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned int  )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (         void  *)SMSAlertGroupId;
        sqlstm.sqhstl[3] = (unsigned int  )17;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         void  *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned int  )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



        if ( sqlca.sqlcode != 0 )
                return sqlca.sqlcode;
	strcpy( smsalertgroup_rec->SMSAlertGroupId, SMSAlertGroupId );
        strcpy( smsalertgroup_rec->MobileList, MobileList );
        strcpy( smsalertgroup_rec->TemplateFile, TemplateFile );
        strcpy( smsalertgroup_rec->GSMPort, GSMPort );

        return sqlca.sqlcode;
}

int readEzAlertDesc( const char *I_RecordId, struct EzAlertDescMemory *alertdesc_rec )
{
        /* EXEC SQL BEGIN DECLARE SECTION; */ 

                char RecordId[ 17 ];
                char DeviceType[ 17 ];
                char StatusCode[ 10 ];
                char StatusDesc[ 65 ];
        /* EXEC SQL END DECLARE SECTION; */ 


        /* EXEC SQL VAR RecordId IS STRING(17); */ 

        /* EXEC SQL VAR DeviceType IS STRING(17); */ 

        /* EXEC SQL VAR StatusCode IS STRING(10); */ 

        /* EXEC SQL VAR StatusDesc IS STRING(65); */ 


        memset( RecordId, 0, sizeof( RecordId ) );
        memset( DeviceType, 0, sizeof( DeviceType ) );
        memset( StatusCode, 0, sizeof( StatusCode ) );
        memset( StatusDesc, 0, sizeof( StatusDesc ) );

        strcpy( RecordId, I_RecordId );

        /* EXEC SQL SELECT
                RTRIM(DEVICETYPE),
                RTRIM(STATUSCODE),
                RTRIM(STATUSDESC)
        INTO
                :DeviceType,
                :StatusCode,
                :StatusDesc
        FROM EZALERTDESC WHERE RTRIM(RECORDID)=:RecordId; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 27;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select RTRIM(DEVICETYPE) ,RTRIM(STATUSCODE) ,RTRIM(ST\
ATUSDESC) into :b0,:b1,:b2  from EZALERTDESC where RTRIM(RECORDID)=:b3";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )1847;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (         void  *)DeviceType;
        sqlstm.sqhstl[0] = (unsigned int  )17;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         void  *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned int  )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (         void  *)StatusCode;
        sqlstm.sqhstl[1] = (unsigned int  )10;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         void  *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned int  )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (         void  *)StatusDesc;
        sqlstm.sqhstl[2] = (unsigned int  )65;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         void  *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned int  )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (         void  *)RecordId;
        sqlstm.sqhstl[3] = (unsigned int  )17;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         void  *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned int  )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if ( sqlca.sqlcode != 0 )
                return sqlca.sqlcode;

        strcpy( alertdesc_rec->RecordId, RecordId );
        strcpy( alertdesc_rec->DeviceType, DeviceType );
        strcpy( alertdesc_rec->StatusCode, StatusCode );
        strcpy( alertdesc_rec->StatusDesc, StatusDesc );
        return sqlca.sqlcode;
}

