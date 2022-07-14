
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
           char  filnam[15];
};
static struct sqlcxp sqlfpn =
{
    14,
    "ezinstmgrdb.pc"
};


static unsigned int sqlctx = 1246315;


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
            void  *sqhstv[23];
   unsigned int   sqhstl[23];
            int   sqhsts[23];
            void  *sqindv[23];
            int   sqinds[23];
   unsigned int   sqharm[23];
   unsigned int   *sqharc[23];
   unsigned short  sqadto[23];
   unsigned short  sqtdso[23];
} sqlstm = {12,23};

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

 static char *sq0002 = 
"select RTRIM(INSTROUTETYPE)  from EZINSTROUTETYPE            ";

 static char *sq0004 = 
"select RTRIM(RECORDID) ,RTRIM(DEVICETYPE) ,RTRIM(FIELDTYPE) ,RTRIM(FROMOFFSE\
T) ,RTRIM(TOOFFSET) ,RTRIM(FIELDVAL) ,PRIORITY ,RTRIM(INSTID) ,RTRIM(INSTTYPE)\
  from EZINSTSELECT            ";

 static char *sq0006 = 
"select RTRIM(RECORDID) ,RTRIM(BIN) ,RTRIM(INSTID) ,BINRANGEREQ ,PRIORITY  fr\
om EZBINSELECT            ";

 static char *sq0008 = 
"select RTRIM(RECORDID) ,RTRIM(INSTID) ,PRIORITY ,RTRIM(NETWORKTYPE) ,RTRIM(F\
IELDTYPE) ,RTRIM(FROMOFFSET) ,RTRIM(TOOFFSET)  from EZNETWORKSELECT           \
 ";

 static char *sq0010 = 
"select RTRIM(INSTID) ,RTRIM(INSTROUTETYPE) ,RTRIM(INSTTYPE) ,RTRIM(INSTSECUR\
ITYGROUP) ,RTRIM(INSTTERMINALGROUP) ,RTRIM(INSTAUTHGROUP) ,RTRIM(INSTCURRENCYC\
ODE) ,MAXATMPINCOUNT ,MAXTELEPINCOUNT ,RTRIM(PRIMARYBIN) ,PADSSENABLED  from E\
ZINSTPROFILE            ";

 static char *sq0012 = 
"select RTRIM(INSTID) ,RTRIM(BIN) ,RTRIM(PRODUCTCODE) ,RTRIM(PRODUCTNAME) ,RT\
RIM(BINTYPE) ,RTRIM(ROUTETYPE) ,RTRIM(TXNLIST)  from EZBINPROFILE            ";

 static char *sq0014 = 
"select RTRIM(INSTID) ,RTRIM(BIN) ,RTRIM(LOWRANGE) ,RTRIM(HIGHRANGE)  from EZ\
BINRANGE            ";

 static char *sq0016 = 
"select RTRIM(INSTID) ,RTRIM(BRANCHCODE) ,RTRIM(BRANCHMAPCODE)  from EZBRANCH\
PROFILE            ";

 static char *sq0018 = 
"select RTRIM(RECORDID) ,RTRIM(AUTHGROUPID) ,RTRIM(MSGTYPE) ,RTRIM(TXNCODE) ,\
RTRIM(RESPCODE) ,RTRIM(AUTHLIST)  from EZAUTHPROPERTY            ";

 static char *sq0020 = 
"select RTRIM(CHANNELNAME) ,RTRIM(CHANNELTYPE) ,RTRIM(DEVICETYPE) ,RTRIM(LAYE\
RID)  from EZCHANNELPROPERTY            ";

 static char *sq0022 = 
"select RECORDNO ,RTRIM(RECORDID) ,RTRIM(CHANNELNAME) ,RTRIM(MSGTYPE) ,RTRIM(\
TXNCODE) ,RTRIM(RESPCODE) ,EVENTFLAG ,EVENTTIMEOUT  from EZEVENTPROPERTY      \
      ";

 static char *sq0024 = 
"select RTRIM(MSGTRANSLATEID) ,RTRIM(TRANSLATEDESC)  from EZMSGTRANSLATE     \
       ";

 static char *sq0026 = 
"select MSGTYPE ,MSGPROPERTY ,LOOKUPPROPERTY  from EZMSGTYPEPROPERTY         \
   ";

 static char *sq0028 = 
"select RECORDNO ,RTRIM(RECORDID) ,RTRIM(DEVICETYPE) ,RTRIM(MSGTYPE) ,RTRIM(T\
XNCODE) ,RTRIM(RESPCODE) ,RTRIM(KEYFIELDS)  from EZTXNREFSELECT            ";

 static char *sq0030 = 
"select RECORDNO ,RTRIM(RECORDID) ,RTRIM(ISSUERINSTROUTETYPE) ,RTRIM(ACQUIRER\
INSTROUTETYPE) ,RTRIM(TXFINSTROUTETYPE) ,RTRIM(SETTINSTROUTETYPE) ,RTRIM(FWDIN\
STROUTETYPE) ,RTRIM(DEVICETYPE) ,RTRIM(DEVICESUBTYPE) ,RTRIM(MSGTYPE) ,RTRIM(T\
XNCODE) ,RTRIM(RESPCODE) ,RTRIM(ROUTEEXP1) ,ROUTEEXPPRIORITY1 ,RTRIM(ROUTEEXP2\
) ,ROUTEEXPPRIORITY2 ,RTRIM(CHANNELNAME) ,RTRIM(NETWORKTYPELIST) ,RTRIM(NETWOR\
KSTATUSLIST) ,NETWORKLISTPRIORITY ,RTRIM(ROUTECONDITION) ,ROUTECONDITIONPRIORI\
TY ,RTRIM(ROUTESELECTLIST)  from EZTXNROUTEINFO            ";

 static char *sq0032 = 
"select RTRIM(ROUTESELECTID) ,RTRIM(CHANNELNAME) ,RTRIM(MSGTRANSLATEID) ,LOGF\
LAG  from EZTXNROUTESELECT            ";

 static char *sq0034 = 
"select RECORDNO ,RTRIM(RECORDID) ,RTRIM(MSGTYPE) ,RTRIM(CHANNELTYPE) ,RTRIM(\
CHANNELNAME) ,MSGFLAG ,LOGFLAG ,MSGPROCESSFLAG  from EZINBOUNDMSGPROPERTY     \
       ";

 static char *sq0036 = 
"select RTRIM(DEVICEGROUPID) ,DEVICEGROUPVAL  from EZDEVICEGROUP            ";

 static char *sq0038 = 
"select RTRIM(RECORDID) ,RTRIM(SRCCHANNEL) ,RTRIM(DESTCHANNEL) ,RTRIM(MSGTYPE\
) ,RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,ORDERNO  from EZTXNMSGORDER            ";

 static char *sq0040 = 
"select RTRIM(INSTID) ,RTRIM(EXTNETWORKID) ,RTRIM(ACQINSTCODE) ,RTRIM(TXNCODE\
LIST) ,RTRIM(ADDFEE1) ,RTRIM(ADDFEE2) ,RTRIM(ADDFEE3)  from EZINSTEXTNTWKPROFI\
LE            ";

 static char *sq0042 = 
"select RTRIM(EXTNETWORKID) ,RTRIM(TXNCODELIST) ,RTRIM(TXNCOUNTCHECKREQ) ,RTR\
IM(TXNAMOUNTCHECKREQ) ,RTRIM(MAXAMOUNTPERTXN) ,RTRIM(MAXAMOUNT) ,RTRIM(MAXAMOU\
NTINTERVAL) ,RTRIM(MAXAMOUNTINTERVALTYPE) ,RTRIM(MAXAMOUNTACTION) ,RTRIM(MAXAM\
OUNTFEE) ,RTRIM(MAXCOUNT) ,RTRIM(MAXCOUNTINTERVAL) ,RTRIM(MAXCOUNTINTERVALTYPE\
) ,RTRIM(MAXCOUNTACTION) ,RTRIM(MAXCOUNTFEE)  from EZEXTNTWKPROFILE           \
 ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,48,0,4,13,0,0,1,0,0,1,0,2,3,0,0,
24,0,0,2,61,0,9,34,0,0,0,0,0,1,0,
39,0,0,2,0,0,13,40,0,0,1,0,0,1,0,2,5,0,0,
58,0,0,2,0,0,15,54,0,0,0,0,0,1,0,
73,0,0,3,45,0,4,68,0,0,1,0,0,1,0,2,3,0,0,
92,0,0,4,185,0,9,112,0,0,0,0,0,1,0,
107,0,0,4,0,0,13,125,0,0,9,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,3,0,0,2,5,0,0,2,5,0,0,
158,0,0,4,0,0,15,155,0,0,0,0,0,1,0,
173,0,0,5,44,0,4,170,0,0,1,0,0,1,0,2,3,0,0,
192,0,0,6,102,0,9,201,0,0,0,0,0,1,0,
207,0,0,6,0,0,13,209,0,0,5,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,3,0,0,
242,0,0,6,0,0,15,231,0,0,0,0,0,1,0,
257,0,0,7,48,0,4,246,0,0,1,0,0,1,0,2,3,0,0,
276,0,0,8,155,0,9,284,0,0,0,0,0,1,0,
291,0,0,8,0,0,13,295,0,0,7,0,0,1,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,5,0,0,
334,0,0,8,0,0,15,320,0,0,0,0,0,1,0,
349,0,0,9,46,0,4,334,0,0,1,0,0,1,0,2,3,0,0,
368,0,0,10,256,0,9,382,0,0,0,0,0,1,0,
383,0,0,10,0,0,13,395,0,0,11,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,1,0,0,
442,0,0,10,0,0,15,429,0,0,0,0,0,1,0,
457,0,0,11,45,0,4,444,0,0,1,0,0,1,0,2,3,0,0,
476,0,0,12,153,0,9,483,0,0,0,0,0,1,0,
491,0,0,12,0,0,13,495,0,0,7,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,
534,0,0,12,0,0,15,521,0,0,0,0,0,1,0,
549,0,0,13,43,0,4,536,0,0,1,0,0,1,0,2,3,0,0,
568,0,0,14,96,0,9,566,0,0,0,0,0,1,0,
583,0,0,14,0,0,13,575,0,0,4,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
614,0,0,14,0,0,15,595,0,0,0,0,0,1,0,
629,0,0,15,48,0,4,610,0,0,1,0,0,1,0,2,3,0,0,
648,0,0,16,95,0,9,637,0,0,0,0,0,1,0,
663,0,0,16,0,0,13,645,0,0,3,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,
690,0,0,16,0,0,15,663,0,0,0,0,0,1,0,
705,0,0,17,47,0,4,678,0,0,1,0,0,1,0,2,3,0,0,
724,0,0,18,141,0,9,714,0,0,0,0,0,1,0,
739,0,0,18,0,0,13,725,0,0,6,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,
778,0,0,18,0,0,15,750,0,0,0,0,0,1,0,
793,0,0,19,50,0,4,765,0,0,1,0,0,1,0,2,3,0,0,
812,0,0,20,116,0,9,795,0,0,0,0,0,1,0,
827,0,0,20,0,0,13,804,0,0,4,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
858,0,0,20,0,0,15,824,0,0,0,0,0,1,0,
873,0,0,21,48,0,4,837,0,0,1,0,0,1,0,2,3,0,0,
892,0,0,22,160,0,9,876,0,0,0,0,0,1,0,
907,0,0,22,0,0,13,886,0,0,8,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,2,3,0,0,
954,0,0,22,0,0,15,914,0,0,0,0,0,1,0,
969,0,0,23,47,0,4,927,0,0,1,0,0,1,0,2,3,0,0,
988,0,0,24,83,0,9,951,0,0,0,0,0,1,0,
1003,0,0,24,0,0,13,958,0,0,2,0,0,1,0,2,5,0,0,2,5,0,0,
1026,0,0,24,0,0,15,974,0,0,0,0,0,1,0,
1041,0,0,25,50,0,4,988,0,0,1,0,0,1,0,2,3,0,0,
1060,0,0,26,79,0,9,1011,0,0,0,0,0,1,0,
1075,0,0,26,0,0,13,1015,0,0,3,0,0,1,0,2,3,0,0,2,1,0,0,2,1,0,0,
1102,0,0,26,0,0,15,1033,0,0,0,0,0,1,0,
1117,0,0,27,47,0,4,1046,0,0,1,0,0,1,0,2,3,0,0,
1136,0,0,28,151,0,9,1085,0,0,0,0,0,1,0,
1151,0,0,28,0,0,13,1096,0,0,7,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,
1194,0,0,28,0,0,15,1122,0,0,0,0,0,1,0,
1209,0,0,29,47,0,4,1135,0,0,1,0,0,1,0,2,3,0,0,
1228,0,0,30,525,0,9,1217,0,0,0,0,0,1,0,
1243,0,0,30,0,0,13,1240,0,0,23,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,
0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,3,0,0,2,5,0,0,
1350,0,0,30,0,0,15,1299,0,0,0,0,0,1,0,
1365,0,0,31,49,0,4,1313,0,0,1,0,0,1,0,2,3,0,0,
1384,0,0,32,114,0,9,1342,0,0,0,0,0,1,0,
1399,0,0,32,0,0,13,1350,0,0,4,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,
1430,0,0,32,0,0,15,1371,0,0,0,0,0,1,0,
1445,0,0,33,53,0,4,1385,0,0,1,0,0,1,0,2,3,0,0,
1464,0,0,34,161,0,9,1423,0,0,0,0,0,1,0,
1479,0,0,34,0,0,13,1432,0,0,8,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,1,0,0,2,1,0,0,2,1,0,0,
1526,0,0,34,0,0,15,1461,0,0,0,0,0,1,0,
1541,0,0,35,46,0,4,1475,0,0,1,0,0,1,0,2,3,0,0,
1560,0,0,36,75,0,9,1498,0,0,0,0,0,1,0,
1575,0,0,36,0,0,13,1504,0,0,2,0,0,1,0,2,5,0,0,2,3,0,0,
1598,0,0,36,0,0,15,1520,0,0,0,0,0,1,0,
1613,0,0,37,46,0,4,1533,0,0,1,0,0,1,0,2,3,0,0,
1632,0,0,38,151,0,9,1571,0,0,0,0,0,1,0,
1647,0,0,38,0,0,13,1582,0,0,7,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,3,0,0,
1690,0,0,38,0,0,15,1609,0,0,0,0,0,1,0,
1705,0,0,39,53,0,4,1623,0,0,1,0,0,1,0,2,3,0,0,
1724,0,0,40,168,0,9,1662,0,0,0,0,0,1,0,
1739,0,0,40,0,0,13,1674,0,0,7,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,
1782,0,0,40,0,0,15,1701,0,0,0,0,0,1,0,
1797,0,0,41,49,0,4,1715,0,0,1,0,0,1,0,2,3,0,0,
1816,0,0,42,389,0,9,1778,0,0,0,0,0,1,0,
1831,0,0,42,0,0,13,1798,0,0,15,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,
1906,0,0,42,0,0,15,1840,0,0,0,0,0,1,0,
};


#include <ezlink/ezinstdbtypes.h>
#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getEzInstRouteTypeCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZINSTROUTETYPE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZINSTROUTETYPE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )5;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzInstRouteType( struct EzInstRouteTypeMemory *ezinstroutetype_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstRouteType[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstRouteType IS STRING(17); */ 

		
	/* EXEC SQL DECLARE ezinstroutetype_cur CURSOR FOR
    SELECT
    	RTRIM(INSTROUTETYPE)
    FROM EZINSTROUTETYPE; */ 

		
	/* EXEC SQL OPEN ezinstroutetype_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0002;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )24;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( InstRouteType, 0, sizeof( InstRouteType ) );
				
		/* EXEC SQL FETCH ezinstroutetype_cur INTO
		:InstRouteType; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 1;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )39;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)InstRouteType;
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


						
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezinstroutetype_ptr + i )->InstRouteType, InstRouteType );
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezinstroutetype_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )58;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
}

int getEzInstSelectCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZINSTSELECT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZINSTSELECT ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )73;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzInstSelect( struct EzInstSelectMemory *ezinstselect_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char DeviceType[ 17 ];
		char FieldType[ 65 ];
		char FromOffset[ 17 ];
		char ToOffset[ 17 ];
		char FieldVal[ 129 ];
		int Priority;
		char InstId[ 13 ];
		char InstType[ 11 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR FieldType IS STRING(65); */ 

	/* EXEC SQL VAR FromOffset IS STRING(17); */ 

	/* EXEC SQL VAR ToOffset IS STRING(17); */ 

	/* EXEC SQL VAR FieldVal IS STRING(129); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstType IS STRING(11); */ 

	
	/* EXEC SQL DECLARE ezinstselect_cur CURSOR FOR
    SELECT
    	RTRIM(RECORDID),
    	RTRIM(DEVICETYPE),
		RTRIM(FIELDTYPE),
        RTRIM(FROMOFFSET),
        RTRIM(TOOFFSET),
        RTRIM(FIELDVAL),
        PRIORITY,
        RTRIM(INSTID),
        RTRIM(INSTTYPE)
    FROM EZINSTSELECT; */ 

		
	/* EXEC SQL OPEN ezinstselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0004;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )92;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( FieldType, 0, sizeof( FieldType ) );
		memset( FromOffset, 0, sizeof( FromOffset ) );
		memset( ToOffset, 0, sizeof( ToOffset ) );
		memset( FieldVal, 0, sizeof( FieldVal ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( InstType, 0, sizeof( InstType ) );

		/* EXEC SQL FETCH ezinstselect_cur INTO
		:RecordId,
		:DeviceType,
		:FieldType,
		:FromOffset,
		:ToOffset,
		:FieldVal,
		:Priority,
		:InstId,
		:InstType; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 9;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )107;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        strcpy( ( ezinstselect_ptr + i )->RecordId, RecordId );
		strcpy( ( ezinstselect_ptr + i )->DeviceType, DeviceType );
		strcpy( ( ezinstselect_ptr + i )->FieldType, FieldType );
		strcpy( ( ezinstselect_ptr + i )->FromOffset, FromOffset );
		strcpy( ( ezinstselect_ptr + i )->ToOffset, ToOffset );
		strcpy( ( ezinstselect_ptr + i )->FieldVal, FieldVal );
		( ezinstselect_ptr + i )->Priority = Priority;
		strcpy( ( ezinstselect_ptr + i )->InstId, InstId );
		strcpy( ( ezinstselect_ptr + i )->InstType, InstType );
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezinstselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )158;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzBINSelectCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZBINSELECT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 9;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZBINSELECT ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )173;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzBINSelect( struct EzBINSelectMemory *ezbinselect_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char BIN[ 13 ];
		char InstId[ 13 ];
		char BINRangeReq;
		short Priority;
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	
	/* EXEC SQL DECLARE ezbinselect_cur CURSOR FOR
    SELECT
    	RTRIM(RECORDID),
    	RTRIM(BIN),
    	RTRIM(INSTID),
		BINRANGEREQ,
		PRIORITY
    FROM EZBINSELECT; */ 

		
	/* EXEC SQL OPEN ezbinselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0006;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )192;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( InstId, 0, sizeof( InstId ) );
		
		/* EXEC SQL FETCH ezbinselect_cur INTO
		:RecordId,
		:BIN,
		:InstId,
		:BINRangeReq,
		:Priority; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 9;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )207;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezbinselect_ptr + i )->RecordId, RecordId );	
        strcpy( ( ezbinselect_ptr + i )->BIN, BIN );
		strcpy( ( ezbinselect_ptr + i )->InstId, InstId );
		( ezbinselect_ptr + i )->BINRangeReq = BINRangeReq;
		( ezbinselect_ptr + i )->Priority = Priority;
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezbinselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )242;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzNetworkSelectCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZNETWORKSELECT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 9;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZNETWORKSELECT ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )257;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzNetworkSelect( struct EzNetworkSelectMemory *eznetworkselect_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char InstId[ 13 ];
		int Priority;
		char NetworkType[ 11 ];
		char FieldType[ 65 ];
		char FromOffset[ 33 ];
		char ToOffset[ 33 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR NetworkType IS STRING(11); */ 

	/* EXEC SQL VAR FieldType IS STRING(65); */ 

	/* EXEC SQL VAR FromOffset IS STRING(33); */ 

	/* EXEC SQL VAR ToOffset IS STRING(33); */ 

	
	/* EXEC SQL DECLARE eznetworkselect_cur CURSOR FOR
    SELECT
    	RTRIM(RECORDID),
		RTRIM(INSTID),
        PRIORITY,
        RTRIM(NETWORKTYPE),
        RTRIM(FIELDTYPE),
        RTRIM(FROMOFFSET),
        RTRIM(TOOFFSET)
    FROM EZNETWORKSELECT; */ 

		
	/* EXEC SQL OPEN eznetworkselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0008;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )276;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( NetworkType, 0, sizeof( NetworkType ) );
		memset( FieldType, 0, sizeof( FieldType ) );
		memset( FromOffset, 0, sizeof( FromOffset ) );
		memset( ToOffset, 0, sizeof( ToOffset ) );

		/* EXEC SQL FETCH eznetworkselect_cur INTO
		:RecordId,
		:InstId,
		:Priority,
		:NetworkType,
		:FieldType,
		:FromOffset,
		:ToOffset; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 9;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )291;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( eznetworkselect_ptr + i )->RecordId, RecordId );
		strcpy( ( eznetworkselect_ptr + i )->InstId, InstId );
		( eznetworkselect_ptr + i )->Priority = Priority;
		strcpy( ( eznetworkselect_ptr + i )->NetworkType, NetworkType );
		strcpy( ( eznetworkselect_ptr + i )->FieldType, FieldType );
		strcpy( ( eznetworkselect_ptr + i )->FromOffset, FromOffset );
		strcpy( ( eznetworkselect_ptr + i )->ToOffset, ToOffset );
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE eznetworkselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )334;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
}

int getEzInstProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZINSTPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 9;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZINSTPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )349;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzInstProfile( struct EzInstProfileMemory *ezinstprofile_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char InstRouteType[ 17 ];
		char InstType[ 17 ];
		char InstSecurityGroup[ 17 ];
		char InstTerminalGroup[ 17 ];
		char InstAuthGroup[ 17 ];
		char InstCurrencyCode[ 6 ];
		int MaxATMPINCount;
		int MaxTelePINCount;
		char PrimaryBin[ 13 ];
		char PADSSEnabled;
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR InstType IS STRING(17); */ 

	/* EXEC SQL VAR InstSecurityGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstAuthGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstCurrencyCode IS STRING( 6 ); */ 

	/* EXEC SQL VAR PrimaryBin IS STRING( 13 ); */ 

	
	/* EXEC SQL DECLARE ezinstprofile_cur CURSOR FOR
    SELECT
    	RTRIM(INSTID),
		RTRIM(INSTROUTETYPE),
        RTRIM(INSTTYPE),
        RTRIM(INSTSECURITYGROUP),
        RTRIM(INSTTERMINALGROUP),
        RTRIM(INSTAUTHGROUP),
        RTRIM(INSTCURRENCYCODE),
        MAXATMPINCOUNT,
        MAXTELEPINCOUNT,
        RTRIM(PRIMARYBIN),
        PADSSENABLED
    FROM EZINSTPROFILE; */ 

		
	/* EXEC SQL OPEN ezinstprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0010;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )368;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( InstId, 0, sizeof( InstId ) );
		memset( InstRouteType, 0, sizeof( InstRouteType ) );
		memset( InstType, 0, sizeof( InstType ) );
		memset( InstSecurityGroup, 0, sizeof( InstSecurityGroup ) );
		memset( InstTerminalGroup, 0, sizeof( InstTerminalGroup ) );
		memset( InstAuthGroup, 0, sizeof( InstAuthGroup ) );
		memset( InstCurrencyCode, 0, sizeof( InstCurrencyCode ) );
		memset( PrimaryBin, 0, sizeof( PrimaryBin ) );
				
		/* EXEC SQL FETCH ezinstprofile_cur INTO
		:InstId,
		:InstRouteType,
		:InstType,
		:InstSecurityGroup,
		:InstTerminalGroup,
		:InstAuthGroup,
		:InstCurrencyCode,
		:MaxATMPINCount,
		:MaxTelePINCount,
		:PrimaryBin,
		:PADSSEnabled; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )383;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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
  sqlstm.sqhstl[6] = (unsigned int  )6;
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
  sqlstm.sqhstv[10] = (         void  *)&PADSSEnabled;
  sqlstm.sqhstl[10] = (unsigned int  )1;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezinstprofile_ptr + i )->InstId, InstId );
        strcpy( ( ezinstprofile_ptr + i )->InstRouteType, InstRouteType );
		strcpy( ( ezinstprofile_ptr + i )->InstType, InstType );
		strcpy( ( ezinstprofile_ptr + i )->InstSecurityGroup, InstSecurityGroup );
		strcpy( ( ezinstprofile_ptr + i )->InstTerminalGroup, InstTerminalGroup );
		strcpy( ( ezinstprofile_ptr + i )->InstAuthGroup, InstAuthGroup );
		strcpy( ( ezinstprofile_ptr + i )->InstCurrencyCode, InstCurrencyCode );
		( ezinstprofile_ptr + i )->MaxATMPINCount = MaxATMPINCount;
		( ezinstprofile_ptr + i )->MaxTelePINCount = MaxTelePINCount;
		strcpy( ( ezinstprofile_ptr + i )->PrimaryBin, PrimaryBin );
		( ezinstprofile_ptr + i )->PADSSEnabled = PADSSEnabled;
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezinstprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )442;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzBINProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZBINPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZBINPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )457;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzBINProfile( struct EzBINProfileMemory *ezbinprofile_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char BIN[ 13 ];
		char ProductCode[ 13 ];
		char ProductName[ 13 ];
		char BINType[ 11 ];
		char RouteType[ 17 ];
		char TxnList[ 65 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR ProductCode IS STRING(13); */ 

	/* EXEC SQL VAR ProductName IS STRING(13); */ 

	/* EXEC SQL VAR BINType IS STRING(11); */ 

	/* EXEC SQL VAR RouteType IS STRING(17); */ 

	/* EXEC SQL VAR TxnList IS STRING(65); */ 

		
	/* EXEC SQL DECLARE ezbinprofile_cur CURSOR FOR
    SELECT
    	RTRIM(INSTID),
		RTRIM(BIN),
		RTRIM(PRODUCTCODE),
		RTRIM(PRODUCTNAME),
		RTRIM(BINTYPE),
		RTRIM(ROUTETYPE),
        RTRIM(TXNLIST)
    FROM EZBINPROFILE; */ 

		
	/* EXEC SQL OPEN ezbinprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0012;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )476;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( InstId, 0, sizeof( InstId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( ProductCode, 0, sizeof( ProductCode ) );
		memset( ProductName, 0, sizeof( ProductName ) );
		memset( BINType, 0, sizeof( BINType ) );
		memset( RouteType, 0, sizeof( RouteType ) );
		memset( TxnList, 0, sizeof( TxnList ) );
		
		/* EXEC SQL FETCH ezbinprofile_cur INTO
		:InstId,
		:BIN,
		:ProductCode,
		:ProductName,
		:BINType,
		:RouteType,
		:TxnList; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )491;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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
  sqlstm.sqhstv[2] = (         void  *)ProductCode;
  sqlstm.sqhstl[2] = (unsigned int  )13;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)ProductName;
  sqlstm.sqhstl[3] = (unsigned int  )13;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)BINType;
  sqlstm.sqhstl[4] = (unsigned int  )11;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)RouteType;
  sqlstm.sqhstl[5] = (unsigned int  )17;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)TxnList;
  sqlstm.sqhstl[6] = (unsigned int  )65;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezbinprofile_ptr + i )->InstId, InstId );
        strcpy( ( ezbinprofile_ptr + i )->BIN, BIN );
        strcpy( ( ezbinprofile_ptr + i )->ProductCode, ProductCode );
        strcpy( ( ezbinprofile_ptr + i )->ProductName, ProductName );
        strcpy( ( ezbinprofile_ptr + i )->BINType, BINType );
        strcpy( ( ezbinprofile_ptr + i )->RouteType, RouteType );
		strcpy( ( ezbinprofile_ptr + i )->TxnList, TxnList );
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezbinprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )534;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzBINRangeCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZBINRANGE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZBINRANGE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )549;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzBINRange( struct EzBINRangeMemory *ezbinrange_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char BIN[ 13 ];
		char LowRange[ 20 ];
		char HighRange[ 20 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR LowRange IS STRING(20); */ 

	/* EXEC SQL VAR HighRange IS STRING(20); */ 

		
	/* EXEC SQL DECLARE ezbinrange_cur CURSOR FOR
    SELECT
    	RTRIM(INSTID),
    	RTRIM(BIN),
        RTRIM(LOWRANGE),
        RTRIM(HIGHRANGE)
    FROM EZBINRANGE; */ 

		
	/* EXEC SQL OPEN ezbinrange_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0014;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )568;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( InstId, 0, sizeof( InstId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( LowRange, 0, sizeof( LowRange ) );
		memset( HighRange, 0, sizeof( HighRange ) );
		
		/* EXEC SQL FETCH ezbinrange_cur INTO
		:InstId,
		:BIN,
		:LowRange,
		:HighRange; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )583;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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
  sqlstm.sqhstv[2] = (         void  *)LowRange;
  sqlstm.sqhstl[2] = (unsigned int  )20;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)HighRange;
  sqlstm.sqhstl[3] = (unsigned int  )20;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezbinrange_ptr + i )->InstId, InstId );
        strcpy( ( ezbinrange_ptr + i )->BIN, BIN );
		strcpy( ( ezbinrange_ptr + i )->LowRange, LowRange );
		strcpy( ( ezbinrange_ptr + i )->HighRange, HighRange );
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezbinrange_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )614;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzBranchProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZBRANCHPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZBRANCHPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )629;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzBranchProfile( struct EzBranchProfileMemory *ezbranchprofile_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char BranchCode[ 13 ];
		char BranchMapCode[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR BranchCode IS STRING(13); */ 

	/* EXEC SQL VAR BranchMapCode IS STRING(13); */ 

		
	/* EXEC SQL DECLARE ezbranchprofile_cur CURSOR FOR
    SELECT
    	RTRIM(INSTID),
        RTRIM(BRANCHCODE),
        RTRIM(BRANCHMAPCODE)
    FROM EZBRANCHPROFILE; */ 

		
	/* EXEC SQL OPEN ezbranchprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0016;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )648;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( InstId, 0, sizeof( InstId ) );
		memset( BranchCode, 0, sizeof( BranchCode ) );
		memset( BranchMapCode, 0, sizeof( BranchMapCode ) );
		
		/* EXEC SQL FETCH ezbranchprofile_cur INTO
		:InstId,
		:BranchCode,
		:BranchMapCode; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )663;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezbranchprofile_ptr + i )->InstId, InstId );
		strcpy( ( ezbranchprofile_ptr + i )->BranchCode, BranchCode );
		strcpy( ( ezbranchprofile_ptr + i )->BranchMapCode, BranchMapCode );
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezbranchprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )690;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzAuthPropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZAUTHPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZAUTHPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )705;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzAuthProperty( struct EzAuthPropertyMemory *ezauthproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char AuthGroupId[ 17 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		char AuthList[ 256 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR AuthGroupId IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	/* EXEC SQL VAR AuthList IS STRING(256); */ 

		
	/* EXEC SQL DECLARE ezauthproperty_cur CURSOR FOR
    SELECT
    	RTRIM(RECORDID),
        RTRIM(AUTHGROUPID),
        RTRIM(MSGTYPE),
        RTRIM(TXNCODE),
        RTRIM(RESPCODE),
        RTRIM(AUTHLIST)
    FROM EZAUTHPROPERTY; */ 

		
	/* EXEC SQL OPEN ezauthproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0018;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )724;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( AuthGroupId, 0, sizeof( AuthGroupId ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( AuthList, 0, sizeof( AuthList ) );
		
		/* EXEC SQL FETCH ezauthproperty_cur INTO
		:RecordId,
		:AuthGroupId,
		:MsgType,
		:TxnCode,
		:RespCode,
		:AuthList; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )739;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)RecordId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)AuthGroupId;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)MsgType;
  sqlstm.sqhstl[2] = (unsigned int  )5;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)TxnCode;
  sqlstm.sqhstl[3] = (unsigned int  )7;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)RespCode;
  sqlstm.sqhstl[4] = (unsigned int  )4;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)AuthList;
  sqlstm.sqhstl[5] = (unsigned int  )256;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        strcpy( ( ezauthproperty_ptr + i )->RecordId, RecordId );
		strcpy( ( ezauthproperty_ptr + i )->AuthGroupId, AuthGroupId );
		strcpy( ( ezauthproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezauthproperty_ptr + i )->TxnCode, TxnCode );
		strcpy( ( ezauthproperty_ptr + i )->RespCode, RespCode );
		strcpy( ( ezauthproperty_ptr + i )->AuthList, AuthList );
		
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezauthproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )778;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;
			
}

int getEzChannelPropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZCHANNELPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZCHANNELPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )793;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzChannelProperty( struct EzChannelPropertyMemory *ezchannelproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char ChannelName[ 33 ];
		char ChannelType[ 11 ];
		char DeviceType[ 17 ];
		char LayerId[ 11 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR ChannelType IS STRING(11); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR LayerId IS STRING(11); */ 

	
	/* EXEC SQL DECLARE ezchannelproperty_cur CURSOR FOR
    SELECT
		RTRIM(CHANNELNAME),
		RTRIM(CHANNELTYPE),
		RTRIM(DEVICETYPE),
		RTRIM(LAYERID)
	FROM EZCHANNELPROPERTY; */ 

		
	/* EXEC SQL OPEN ezchannelproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0020;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )812;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( ChannelType, 0, sizeof( ChannelType ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( LayerId, 0, sizeof( LayerId ) );
		
		/* EXEC SQL FETCH ezchannelproperty_cur INTO
		:ChannelName,
		:ChannelType,
		:DeviceType,
		:LayerId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )827;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)ChannelName;
  sqlstm.sqhstl[0] = (unsigned int  )33;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)ChannelType;
  sqlstm.sqhstl[1] = (unsigned int  )11;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)DeviceType;
  sqlstm.sqhstl[2] = (unsigned int  )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)LayerId;
  sqlstm.sqhstl[3] = (unsigned int  )11;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezchannelproperty_ptr + i ), 0, sizeof( struct EzChannelPropertyMemory ) );
		strcpy( ( ezchannelproperty_ptr + i )->ChannelName, ChannelName );
		strcpy( ( ezchannelproperty_ptr + i )->ChannelType, ChannelType );
		strcpy( ( ezchannelproperty_ptr + i )->DeviceType, DeviceType );
		strcpy( ( ezchannelproperty_ptr + i )->LayerId, LayerId );
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezchannelproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )858;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzEventPropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZEVENTPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZEVENTPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )873;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzEventProperty( struct EzEventPropertyMemory *ezeventproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 17 ];
		char ChannelName[ 33 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		char EventFlag;
		int EventTimeOut;
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	
	/* EXEC SQL DECLARE ezeventproperty_cur CURSOR FOR
    SELECT
    	RECORDNO,
    	RTRIM(RECORDID),
		RTRIM(CHANNELNAME),
		RTRIM(MSGTYPE),
		RTRIM(TXNCODE),
		RTRIM(RESPCODE),
        EVENTFLAG,
        EVENTTIMEOUT
	FROM EZEVENTPROPERTY; */ 

		
	/* EXEC SQL OPEN ezeventproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0022;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )892;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );

		/* EXEC SQL FETCH ezeventproperty_cur INTO
		:RecordNo,
		:RecordId,
		:ChannelName,
		:MsgType,
		:TxnCode,
		:RespCode,
		:EventFlag,
		:EventTimeOut; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )907;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&RecordNo;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)RecordId;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)ChannelName;
  sqlstm.sqhstl[2] = (unsigned int  )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)MsgType;
  sqlstm.sqhstl[3] = (unsigned int  )5;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)TxnCode;
  sqlstm.sqhstl[4] = (unsigned int  )7;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)RespCode;
  sqlstm.sqhstl[5] = (unsigned int  )4;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&EventFlag;
  sqlstm.sqhstl[6] = (unsigned int  )1;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)&EventTimeOut;
  sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezeventproperty_ptr + i ), 0, sizeof( struct EzEventPropertyMemory ) );
		( ezeventproperty_ptr + i )->RecordNo = RecordNo;
		strcpy( ( ezeventproperty_ptr + i )->RecordId, RecordId );
		strcpy( ( ezeventproperty_ptr + i )->ChannelName, ChannelName );
		strcpy( ( ezeventproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezeventproperty_ptr + i )->TxnCode,  TxnCode );
		strcpy( ( ezeventproperty_ptr + i )->RespCode,  RespCode );
		( ezeventproperty_ptr + i )->EventFlag = EventFlag;
		( ezeventproperty_ptr + i )->EventTimeOut = EventTimeOut;
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezeventproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )954;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzMsgTranslateCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMSGTRANSLATE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMSGTRANSLATE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )969;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzMsgTranslate( struct EzMsgTranslateMemory *ezmsgtranslate_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MsgTranslateId[ 17 ];
		char TranslateDesc[ 256 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR MsgTranslateId IS STRING(17); */ 

	/* EXEC SQL VAR TranslateDesc IS STRING(256); */ 

	
	/* EXEC SQL DECLARE ezmsgtranslate_cur CURSOR FOR
    SELECT
		RTRIM(MSGTRANSLATEID),
        RTRIM(TRANSLATEDESC)
    FROM EZMSGTRANSLATE; */ 

		
	/* EXEC SQL OPEN ezmsgtranslate_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0024;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )988;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
		memset( TranslateDesc, 0, sizeof( TranslateDesc ) );

		/* EXEC SQL FETCH ezmsgtranslate_cur INTO
		:MsgTranslateId,
		:TranslateDesc; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1003;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)MsgTranslateId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)TranslateDesc;
  sqlstm.sqhstl[1] = (unsigned int  )256;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezmsgtranslate_ptr + i ), 0, sizeof( struct EzMsgTranslateMemory ) );
		strcpy( ( ezmsgtranslate_ptr + i )->MsgTranslateId, MsgTranslateId );
		strcpy( ( ezmsgtranslate_ptr + i )->TranslateDesc, TranslateDesc );
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmsgtranslate_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1026;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzMsgTypePropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMSGTYPEPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMSGTYPEPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1041;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzMsgTypeProperty( struct EzMsgTypePropertyMemory *ezmsgtypeproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int MsgType;
		char MsgProperty;
		char LookUpProperty;
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL DECLARE ezmsgtypeproperty_cur CURSOR FOR
    SELECT
		MSGTYPE,
        MSGPROPERTY,
        LOOKUPPROPERTY
	FROM EZMSGTYPEPROPERTY; */ 

		
	/* EXEC SQL OPEN ezmsgtypeproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0026;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1060;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		/* EXEC SQL FETCH ezmsgtypeproperty_cur INTO
		:MsgType,
		:MsgProperty,
		:LookUpProperty; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1075;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&MsgType;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&MsgProperty;
  sqlstm.sqhstl[1] = (unsigned int  )1;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&LookUpProperty;
  sqlstm.sqhstl[2] = (unsigned int  )1;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezmsgtypeproperty_ptr + i ), 0, sizeof( struct EzMsgTypePropertyMemory ) );
		( ezmsgtypeproperty_ptr + i )->MsgType = MsgType;
		( ezmsgtypeproperty_ptr + i )->MsgProperty = MsgProperty;
		( ezmsgtypeproperty_ptr + i )->LookUpProperty = LookUpProperty;
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmsgtypeproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1102;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzTxnRefSelectCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZTXNREFSELECT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZTXNREFSELECT ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1117;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
    
}

int LoadEzTxnRefSelect( struct EzTxnRefSelectMemory *eztxnrefselect_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 17 ];
		char DeviceType[ 17 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		char KeyFields[ 151 ]; 
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	/* EXEC SQL VAR KeyFields IS STRING(151); */ 

	
	/* EXEC SQL DECLARE eztxnrefselect_cur CURSOR FOR
    SELECT
    	RECORDNO,
    	RTRIM(RECORDID),
		RTRIM(DEVICETYPE),
		RTRIM(MSGTYPE),
        RTRIM(TXNCODE),
        RTRIM(RESPCODE),
        RTRIM(KEYFIELDS)
	FROM EZTXNREFSELECT; */ 

		
	/* EXEC SQL OPEN eztxnrefselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0028;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1136;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( KeyFields, 0, sizeof( KeyFields ) );
		
		/* EXEC SQL FETCH eztxnrefselect_cur INTO
		:RecordNo,
		:RecordId,
		:DeviceType,
		:MsgType,
		:TxnCode,
		:RespCode,
		:KeyFields; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1151;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&RecordNo;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)RecordId;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)DeviceType;
  sqlstm.sqhstl[2] = (unsigned int  )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)MsgType;
  sqlstm.sqhstl[3] = (unsigned int  )5;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)TxnCode;
  sqlstm.sqhstl[4] = (unsigned int  )7;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)RespCode;
  sqlstm.sqhstl[5] = (unsigned int  )4;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)KeyFields;
  sqlstm.sqhstl[6] = (unsigned int  )151;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( eztxnrefselect_ptr + i ), 0, sizeof( struct EzTxnRefSelectMemory ) );
		( eztxnrefselect_ptr + i )->RecordNo = RecordNo;
		strcpy( ( eztxnrefselect_ptr + i )->RecordId, RecordId );
		strcpy( ( eztxnrefselect_ptr + i )->DeviceType, DeviceType );
		strcpy( ( eztxnrefselect_ptr + i )->MsgType, MsgType );
		strcpy( ( eztxnrefselect_ptr + i )->TxnCode, TxnCode );
		strcpy( ( eztxnrefselect_ptr + i )->RespCode, RespCode );
		strcpy( ( eztxnrefselect_ptr + i )->KeyFields, KeyFields );
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE eztxnrefselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1194;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzTxnRouteInfoCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZTXNROUTEINFO; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 11;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZTXNROUTEINFO ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1209;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzTxnRouteInfo( struct EzTxnRouteInfoMemory *eztxnrouteinfo_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 129 ];
		char IssuerInstRouteType[ 17 ];
		char AcquirerInstRouteType[ 17 ];
		char TxfInstRouteType[ 17 ];
		char SettInstRouteType[ 17 ];
		char FwdInstRouteType[ 17 ];
		char DeviceType[ 65 ];
		char DeviceSubType[ 65 ];
		char MsgType[ 65 ];
		char TxnCode[ 129 ];
		char RespCode[ 65 ];
		char RouteExp1[ 129 ];
		int RouteExpPriority1;
		char RouteExp2[ 129 ];
		int RouteExpPriority2;		
		char ChannelName[ 65 ];
		char NetworkTypeList[ 65 ];
		char NetworkStatusList[ 65 ];
		int NetworkListPriority;
		char RouteCondition[ 129 ];
		int RouteConditionPriority;
		char RouteSelectList[ 129 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(129); */ 

	/* EXEC SQL VAR IssuerInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR AcquirerInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR TxfInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR SettInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR FwdInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(65); */ 

	/* EXEC SQL VAR DeviceSubType IS STRING(65); */ 

	/* EXEC SQL VAR MsgType IS STRING(65); */ 

	/* EXEC SQL VAR TxnCode IS STRING(129); */ 

	/* EXEC SQL VAR RespCode IS STRING(65); */ 

	/* EXEC SQL VAR RouteExp1 IS STRING(129); */ 

	/* EXEC SQL VAR RouteExp2 IS STRING(129); */ 

	/* EXEC SQL VAR ChannelName IS STRING(65); */ 

	/* EXEC SQL VAR NetworkTypeList IS STRING(65); */ 

	/* EXEC SQL VAR NetworkStatusList IS STRING(65); */ 

	/* EXEC SQL VAR RouteCondition IS STRING(129); */ 

	/* EXEC SQL VAR RouteSelectList IS STRING(129); */ 

	
	/* EXEC SQL DECLARE eztxnrouteinfo_cur CURSOR FOR
    SELECT
    	RECORDNO,
    	RTRIM(RECORDID),
	 	RTRIM(ISSUERINSTROUTETYPE),	
	 	RTRIM(ACQUIRERINSTROUTETYPE),
	 	RTRIM(TXFINSTROUTETYPE),
	 	RTRIM(SETTINSTROUTETYPE),
	 	RTRIM(FWDINSTROUTETYPE),
	 	RTRIM(DEVICETYPE),
	 	RTRIM(DEVICESUBTYPE),
	 	RTRIM(MSGTYPE),
	 	RTRIM(TXNCODE),
	 	RTRIM(RESPCODE),
	 	RTRIM(ROUTEEXP1),
	 	ROUTEEXPPRIORITY1,
	 	RTRIM(ROUTEEXP2),
	 	ROUTEEXPPRIORITY2,
	 	RTRIM(CHANNELNAME),
	 	RTRIM(NETWORKTYPELIST),
	 	RTRIM(NETWORKSTATUSLIST),
	 	NETWORKLISTPRIORITY,
	 	RTRIM(ROUTECONDITION),
	 	ROUTECONDITIONPRIORITY,
	 	RTRIM(ROUTESELECTLIST)
    FROM EZTXNROUTEINFO; */ 

		
	/* EXEC SQL OPEN eztxnrouteinfo_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0030;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1228;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( IssuerInstRouteType, 0, sizeof( IssuerInstRouteType ) );
		memset( AcquirerInstRouteType, 0, sizeof( AcquirerInstRouteType ) );
		memset( TxfInstRouteType, 0, sizeof( TxfInstRouteType ) );
		memset( SettInstRouteType, 0, sizeof( SettInstRouteType ) );
		memset( FwdInstRouteType, 0, sizeof( FwdInstRouteType ) );
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( DeviceSubType, 0, sizeof( DeviceSubType ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		memset( RouteExp1, 0, sizeof( RouteExp1 ) );
		memset( RouteExp2, 0, sizeof( RouteExp2 ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( NetworkTypeList, 0, sizeof( NetworkTypeList ) );
		memset( NetworkStatusList, 0, sizeof( NetworkStatusList ) );
		memset( RouteCondition, 0, sizeof( RouteCondition ) );
		memset( RouteSelectList, 0, sizeof( RouteSelectList ) );

		/* EXEC SQL FETCH eztxnrouteinfo_cur INTO
		:RecordNo,
		:RecordId,
		:IssuerInstRouteType,
		:AcquirerInstRouteType,
		:TxfInstRouteType,
		:SettInstRouteType,
		:FwdInstRouteType,
		:DeviceType,
		:DeviceSubType,
		:MsgType,
		:TxnCode,
		:RespCode,
		:RouteExp1,
		:RouteExpPriority1,
		:RouteExp2,
		:RouteExpPriority2,
		:ChannelName,
		:NetworkTypeList,
		:NetworkStatusList,
		:NetworkListPriority,
		:RouteCondition,
		:RouteConditionPriority,
		:RouteSelectList; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1243;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&RecordNo;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)RecordId;
  sqlstm.sqhstl[1] = (unsigned int  )129;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)IssuerInstRouteType;
  sqlstm.sqhstl[2] = (unsigned int  )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)AcquirerInstRouteType;
  sqlstm.sqhstl[3] = (unsigned int  )17;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)TxfInstRouteType;
  sqlstm.sqhstl[4] = (unsigned int  )17;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)SettInstRouteType;
  sqlstm.sqhstl[5] = (unsigned int  )17;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)FwdInstRouteType;
  sqlstm.sqhstl[6] = (unsigned int  )17;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)DeviceType;
  sqlstm.sqhstl[7] = (unsigned int  )65;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         void  *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned int  )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (         void  *)DeviceSubType;
  sqlstm.sqhstl[8] = (unsigned int  )65;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         void  *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned int  )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (         void  *)MsgType;
  sqlstm.sqhstl[9] = (unsigned int  )65;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         void  *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned int  )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (         void  *)TxnCode;
  sqlstm.sqhstl[10] = (unsigned int  )129;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         void  *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned int  )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (         void  *)RespCode;
  sqlstm.sqhstl[11] = (unsigned int  )65;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         void  *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned int  )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (         void  *)RouteExp1;
  sqlstm.sqhstl[12] = (unsigned int  )129;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         void  *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned int  )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (         void  *)&RouteExpPriority1;
  sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         void  *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned int  )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (         void  *)RouteExp2;
  sqlstm.sqhstl[14] = (unsigned int  )129;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         void  *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned int  )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (         void  *)&RouteExpPriority2;
  sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         void  *)0;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned int  )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (         void  *)ChannelName;
  sqlstm.sqhstl[16] = (unsigned int  )65;
  sqlstm.sqhsts[16] = (         int  )0;
  sqlstm.sqindv[16] = (         void  *)0;
  sqlstm.sqinds[16] = (         int  )0;
  sqlstm.sqharm[16] = (unsigned int  )0;
  sqlstm.sqadto[16] = (unsigned short )0;
  sqlstm.sqtdso[16] = (unsigned short )0;
  sqlstm.sqhstv[17] = (         void  *)NetworkTypeList;
  sqlstm.sqhstl[17] = (unsigned int  )65;
  sqlstm.sqhsts[17] = (         int  )0;
  sqlstm.sqindv[17] = (         void  *)0;
  sqlstm.sqinds[17] = (         int  )0;
  sqlstm.sqharm[17] = (unsigned int  )0;
  sqlstm.sqadto[17] = (unsigned short )0;
  sqlstm.sqtdso[17] = (unsigned short )0;
  sqlstm.sqhstv[18] = (         void  *)NetworkStatusList;
  sqlstm.sqhstl[18] = (unsigned int  )65;
  sqlstm.sqhsts[18] = (         int  )0;
  sqlstm.sqindv[18] = (         void  *)0;
  sqlstm.sqinds[18] = (         int  )0;
  sqlstm.sqharm[18] = (unsigned int  )0;
  sqlstm.sqadto[18] = (unsigned short )0;
  sqlstm.sqtdso[18] = (unsigned short )0;
  sqlstm.sqhstv[19] = (         void  *)&NetworkListPriority;
  sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[19] = (         int  )0;
  sqlstm.sqindv[19] = (         void  *)0;
  sqlstm.sqinds[19] = (         int  )0;
  sqlstm.sqharm[19] = (unsigned int  )0;
  sqlstm.sqadto[19] = (unsigned short )0;
  sqlstm.sqtdso[19] = (unsigned short )0;
  sqlstm.sqhstv[20] = (         void  *)RouteCondition;
  sqlstm.sqhstl[20] = (unsigned int  )129;
  sqlstm.sqhsts[20] = (         int  )0;
  sqlstm.sqindv[20] = (         void  *)0;
  sqlstm.sqinds[20] = (         int  )0;
  sqlstm.sqharm[20] = (unsigned int  )0;
  sqlstm.sqadto[20] = (unsigned short )0;
  sqlstm.sqtdso[20] = (unsigned short )0;
  sqlstm.sqhstv[21] = (         void  *)&RouteConditionPriority;
  sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[21] = (         int  )0;
  sqlstm.sqindv[21] = (         void  *)0;
  sqlstm.sqinds[21] = (         int  )0;
  sqlstm.sqharm[21] = (unsigned int  )0;
  sqlstm.sqadto[21] = (unsigned short )0;
  sqlstm.sqtdso[21] = (unsigned short )0;
  sqlstm.sqhstv[22] = (         void  *)RouteSelectList;
  sqlstm.sqhstl[22] = (unsigned int  )129;
  sqlstm.sqhsts[22] = (         int  )0;
  sqlstm.sqindv[22] = (         void  *)0;
  sqlstm.sqinds[22] = (         int  )0;
  sqlstm.sqharm[22] = (unsigned int  )0;
  sqlstm.sqadto[22] = (unsigned short )0;
  sqlstm.sqtdso[22] = (unsigned short )0;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        memset( ( eztxnrouteinfo_ptr + i ), 0, sizeof( struct EzTxnRouteInfoMemory ) );
        ( eztxnrouteinfo_ptr + i )->RecordNo = RecordNo;
        strcpy( ( eztxnrouteinfo_ptr + i )->RecordId, RecordId );
        strcpy( ( eztxnrouteinfo_ptr + i )->IssuerInstRouteType, IssuerInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->AcquirerInstRouteType, AcquirerInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->TxfInstRouteType, TxfInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->SettInstRouteType, SettInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->FwdInstRouteType, FwdInstRouteType );
        strcpy( ( eztxnrouteinfo_ptr + i )->DeviceType, DeviceType );
        strcpy( ( eztxnrouteinfo_ptr + i )->DeviceSubType, DeviceSubType );
        strcpy( ( eztxnrouteinfo_ptr + i )->MsgType, MsgType );
        strcpy( ( eztxnrouteinfo_ptr + i )->TxnCode, TxnCode );
        strcpy( ( eztxnrouteinfo_ptr + i )->RespCode, RespCode );
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteExp1, RouteExp1 );
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteExp2, RouteExp2 );
        ( eztxnrouteinfo_ptr + i )->RouteExpPriority1 = RouteExpPriority1;
        ( eztxnrouteinfo_ptr + i )->RouteExpPriority2 = RouteExpPriority2;
        strcpy( ( eztxnrouteinfo_ptr + i )->ChannelName, ChannelName );
        strcpy( ( eztxnrouteinfo_ptr + i )->NetworkTypeList, NetworkTypeList );
        strcpy( ( eztxnrouteinfo_ptr + i )->NetworkStatusList, NetworkStatusList );
        ( eztxnrouteinfo_ptr + i )->NetworkListPriority = NetworkListPriority;
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteCondition, RouteCondition );
        ( eztxnrouteinfo_ptr + i )->RouteConditionPriority = RouteConditionPriority;
        strcpy( ( eztxnrouteinfo_ptr + i )->RouteSelectList, RouteSelectList );
        ( eztxnrouteinfo_ptr + i )->DebugFlag = '0';
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE eztxnrouteinfo_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1350;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzTxnRouteSelectCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZTXNROUTESELECT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 23;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZTXNROUTESELECT ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1365;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzTxnRouteSelect( struct EzTxnRouteSelectMemory *eztxnrouteselect_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RouteSelectId[ 17 ];
		char ChannelName[ 33 ];
		char MsgTranslateId[ 17 ];
		char LogFlag;
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RouteSelectId IS STRING(17); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR MsgTranslateId IS STRING(17); */ 

	
	/* EXEC SQL DECLARE eztxnrouteselect_cur CURSOR FOR
    SELECT
		RTRIM(ROUTESELECTID),
        RTRIM(CHANNELNAME),
        RTRIM(MSGTRANSLATEID),
        LOGFLAG
	FROM EZTXNROUTESELECT; */ 

		
	/* EXEC SQL OPEN eztxnrouteselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0032;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1384;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );

		/* EXEC SQL FETCH eztxnrouteselect_cur INTO
		:RouteSelectId,
		:ChannelName,
		:MsgTranslateId,
		:LogFlag; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1399;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)RouteSelectId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)ChannelName;
  sqlstm.sqhstl[1] = (unsigned int  )33;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)MsgTranslateId;
  sqlstm.sqhstl[2] = (unsigned int  )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&LogFlag;
  sqlstm.sqhstl[3] = (unsigned int  )1;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( eztxnrouteselect_ptr + i ), 0, sizeof( struct EzTxnRouteSelectMemory ) );
		strcpy( ( eztxnrouteselect_ptr + i )->RouteSelectId, RouteSelectId );
		strcpy( ( eztxnrouteselect_ptr + i )->ChannelName, ChannelName );
		strcpy( ( eztxnrouteselect_ptr + i )->MsgTranslateId, MsgTranslateId );
		( eztxnrouteselect_ptr + i )->LogFlag = LogFlag;
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE eztxnrouteselect_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1430;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzInBoundMsgPropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZINBOUNDMSGPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 23;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZINBOUNDMSGPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1445;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzInBoundMsgProperty( struct EzInBoundMsgPropertyMemory *ezinboundmsgproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 17 ];
		char MsgType[ 5 ];
		char ChannelType[ 11 ];
		char ChannelName[ 33 ];
		char MsgFlag;
		char LogFlag;
		char MsgProcessFlag;
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR ChannelType IS STRING(11); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

		
	/* EXEC SQL DECLARE ezinboundmsgproperty_cur CURSOR FOR
    SELECT
    	RECORDNO,
		RTRIM(RECORDID),
		RTRIM(MSGTYPE),
		RTRIM(CHANNELTYPE),
        RTRIM(CHANNELNAME),
        MSGFLAG,
        LOGFLAG,
        MSGPROCESSFLAG
	FROM EZINBOUNDMSGPROPERTY; */ 

		
	/* EXEC SQL OPEN ezinboundmsgproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0034;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1464;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( ChannelType, 0, sizeof( ChannelType ) );
		memset( ChannelName, 0, sizeof( ChannelName ) );
		
		/* EXEC SQL FETCH ezinboundmsgproperty_cur INTO
		:RecordNo,
		:RecordId,
		:MsgType,
		:ChannelType,
		:ChannelName,
		:MsgFlag,
		:LogFlag,
		:MsgProcessFlag; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1479;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&RecordNo;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)RecordId;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)MsgType;
  sqlstm.sqhstl[2] = (unsigned int  )5;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)ChannelType;
  sqlstm.sqhstl[3] = (unsigned int  )11;
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
  sqlstm.sqhstv[5] = (         void  *)&MsgFlag;
  sqlstm.sqhstl[5] = (unsigned int  )1;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&LogFlag;
  sqlstm.sqhstl[6] = (unsigned int  )1;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)&MsgProcessFlag;
  sqlstm.sqhstl[7] = (unsigned int  )1;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezinboundmsgproperty_ptr + i ), 0, sizeof( struct EzInBoundMsgPropertyMemory ) );
		( ezinboundmsgproperty_ptr + i )->RecordNo = RecordNo;
		strcpy( ( ezinboundmsgproperty_ptr + i )->RecordId, RecordId );
		strcpy( ( ezinboundmsgproperty_ptr + i )->MsgType, MsgType );
		strcpy( ( ezinboundmsgproperty_ptr + i )->ChannelName, ChannelName );
		strcpy( ( ezinboundmsgproperty_ptr + i )->ChannelType, ChannelType );
		( ezinboundmsgproperty_ptr + i )->MsgFlag = MsgFlag;
		( ezinboundmsgproperty_ptr + i )->LogFlag = LogFlag;
		( ezinboundmsgproperty_ptr + i )->MsgProcessFlag = MsgProcessFlag;
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezinboundmsgproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1526;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzDeviceTypeMapCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZDEVICEGROUP; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 23;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZDEVICEGROUP ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1541;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzDeviceTypeMap( struct EzDeviceTypeMapMemory *ezdevicetypemap_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char DeviceGroupId[ 17 ];
		int DeviceGroupVal;
    /* EXEC SQL END DECLARE SECTION; */ 


	int ind = 0;
	
	/* EXEC SQL VAR DeviceGroupId IS STRING(17); */ 

	
	/* EXEC SQL DECLARE ezdevicetypemap_cur CURSOR FOR
    SELECT
		RTRIM(DEVICEGROUPID),
		DEVICEGROUPVAL
    FROM EZDEVICEGROUP; */ 

		
	/* EXEC SQL OPEN ezdevicetypemap_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0036;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1560;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( DeviceGroupId, 0, sizeof( DeviceGroupId ) );
		
		/* EXEC SQL FETCH ezdevicetypemap_cur INTO
		:DeviceGroupId,
		:DeviceGroupVal; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1575;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)DeviceGroupId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&DeviceGroupVal;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
        memset( ezdevicetypemap_ptr + ind,  0, sizeof( struct EzDeviceTypeMapMemory ) );
        strcpy( ( ezdevicetypemap_ptr + ind )->DeviceGroupId, DeviceGroupId );
        ( ezdevicetypemap_ptr + ind )->DeviceGroupVal = DeviceGroupVal;
		ind++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezdevicetypemap_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1598;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzTxnMsgOrderCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZTXNMSGORDER; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 23;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZTXNMSGORDER ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1613;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzTxnMsgOrder( struct EzTxnMsgOrderMemory *eztxnmsgorder_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char SrcChannel[ 33 ];
		char DestChannel[ 33 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		short OrderNo;
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR SrcChannel IS STRING(33); */ 

	/* EXEC SQL VAR DestChannel IS STRING(33); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

		
	/* EXEC SQL DECLARE eztxnmsgorder_cur CURSOR FOR
    SELECT
		RTRIM(RECORDID),
		RTRIM(SRCCHANNEL),
		RTRIM(DESTCHANNEL),
		RTRIM(MSGTYPE),
		RTRIM(TXNCODE),
        RTRIM(RESPCODE),
        ORDERNO
	FROM EZTXNMSGORDER; */ 

		
	/* EXEC SQL OPEN eztxnmsgorder_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0038;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1632;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( RecordId, 0, sizeof( RecordId ) );
		memset( SrcChannel, 0, sizeof( SrcChannel ) );
		memset( DestChannel, 0, sizeof( DestChannel ) );
		memset( MsgType, 0, sizeof( MsgType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( RespCode, 0, sizeof( RespCode ) );
		
		/* EXEC SQL FETCH eztxnmsgorder_cur INTO
		:RecordId,
		:SrcChannel,
		:DestChannel,
		:MsgType,
		:TxnCode,
		:RespCode,
		:OrderNo; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1647;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)RecordId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)SrcChannel;
  sqlstm.sqhstl[1] = (unsigned int  )33;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)DestChannel;
  sqlstm.sqhstl[2] = (unsigned int  )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)MsgType;
  sqlstm.sqhstl[3] = (unsigned int  )5;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)TxnCode;
  sqlstm.sqhstl[4] = (unsigned int  )7;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)RespCode;
  sqlstm.sqhstl[5] = (unsigned int  )4;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&OrderNo;
  sqlstm.sqhstl[6] = (unsigned int  )sizeof(short);
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( eztxnmsgorder_ptr + i ), 0, sizeof( struct EzTxnMsgOrderMemory ) );
		strcpy( ( eztxnmsgorder_ptr + i )->RecordId, RecordId );
		strcpy( ( eztxnmsgorder_ptr + i )->SrcChannel, SrcChannel );
		strcpy( ( eztxnmsgorder_ptr + i )->DestChannel, DestChannel );
		strcpy( ( eztxnmsgorder_ptr + i )->MsgType, MsgType );
		strcpy( ( eztxnmsgorder_ptr + i )->TxnCode, TxnCode );
		strcpy( ( eztxnmsgorder_ptr + i )->RespCode, RespCode );
		( eztxnmsgorder_ptr + i )->OrderNo = OrderNo;
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE eztxnmsgorder_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1690;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzInstExtNtwkProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZINSTEXTNTWKPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 23;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZINSTEXTNTWKPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1705;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzInstExtNtwkProfile( struct EzInstExtNtwkProfileMemory *ezinstextntwkprofile_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char ExtNetworkId[ 17 ];
		char AcqInstCode[ 17 ];
		char TxnCodeList[ 65 ];
		char AddFee1[ 129 ];
		char AddFee2[ 129 ];
		char AddFee3[ 129 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR ExtNetworkId IS STRING(17); */ 

	/* EXEC SQL VAR AcqInstCode IS STRING(17); */ 

	/* EXEC SQL VAR TxnCodeList IS STRING(65); */ 

	/* EXEC SQL VAR AddFee1 IS STRING(129); */ 

	/* EXEC SQL VAR AddFee2 IS STRING(129); */ 

	/* EXEC SQL VAR AddFee3 IS STRING(129); */ 

		
	/* EXEC SQL DECLARE ezinstextntwkprofile_cur CURSOR FOR
    SELECT
		RTRIM(INSTID),
		RTRIM(EXTNETWORKID),
		RTRIM(ACQINSTCODE),
		RTRIM(TXNCODELIST),
		RTRIM(ADDFEE1),
		RTRIM(ADDFEE2),
        RTRIM(ADDFEE3)
    FROM EZINSTEXTNTWKPROFILE; */ 

		
	/* EXEC SQL OPEN ezinstextntwkprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0040;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1724;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( InstId, 0, sizeof( InstId ) );
		memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
		memset( AcqInstCode, 0, sizeof( AcqInstCode ) );
		memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
		memset( AddFee1, 0, sizeof( AddFee1 ) );
		memset( AddFee2, 0, sizeof( AddFee2 ) );
		memset( AddFee3, 0, sizeof( AddFee3 ) );
		
		/* EXEC SQL FETCH ezinstextntwkprofile_cur INTO
		:InstId,
		:ExtNetworkId,
		:AcqInstCode,
		:TxnCodeList,
		:AddFee1,
		:AddFee2,
		:AddFee3; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1739;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)InstId;
  sqlstm.sqhstl[0] = (unsigned int  )13;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)ExtNetworkId;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)AcqInstCode;
  sqlstm.sqhstl[2] = (unsigned int  )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)TxnCodeList;
  sqlstm.sqhstl[3] = (unsigned int  )65;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)AddFee1;
  sqlstm.sqhstl[4] = (unsigned int  )129;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)AddFee2;
  sqlstm.sqhstl[5] = (unsigned int  )129;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)AddFee3;
  sqlstm.sqhstl[6] = (unsigned int  )129;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezinstextntwkprofile_ptr + i ), 0, sizeof( struct EzInstExtNtwkProfileMemory ) );
		strcpy( ( ezinstextntwkprofile_ptr + i )->InstId, InstId );
		strcpy( ( ezinstextntwkprofile_ptr + i )->ExtNetworkId, ExtNetworkId );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AcqInstCode, AcqInstCode );
		strcpy( ( ezinstextntwkprofile_ptr + i )->TxnCodeList, TxnCodeList );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AddFee1, AddFee1 );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AddFee2, AddFee2 );
		strcpy( ( ezinstextntwkprofile_ptr + i )->AddFee3, AddFee3 );
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezinstextntwkprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1782;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}

int getEzExtNtwkProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZEXTNTWKPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 23;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZEXTNTWKPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )1797;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


    
    *SqlErr = sqlca.sqlcode;
    return reccount;
}

int LoadEzExtNtwkProfile( struct EzExtNtwkProfileMemory *ezextntwkprofile_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char ExtNetworkId[ 17 ];
		char TxnCodeList[ 65 ];
		char TxnCountCheckReq[ 33 ];
		char TxnAmountCheckReq[ 33 ];
		char MaxAmountPerTxn[ 129 ];
		char MaxAmount[ 129 ];
		char MaxAmountInterval[ 129 ];
		char MaxAmountIntervalType[ 33 ];
		char MaxAmountAction[ 33 ];
		char MaxAmountFee[ 129 ];
		char MaxCount[ 129 ];
		char MaxCountInterval[ 129 ];
		char MaxCountIntervalType[ 33 ];
		char MaxCountAction[ 33 ];
		char MaxCountFee[ 129 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR ExtNetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnCodeList IS STRING(65); */ 

	/* EXEC SQL VAR TxnCountCheckReq IS STRING(33); */ 

	/* EXEC SQL VAR TxnAmountCheckReq IS STRING(33); */ 

	/* EXEC SQL VAR MaxAmountPerTxn IS STRING(129); */ 

	/* EXEC SQL VAR MaxAmount IS STRING(129); */ 

	/* EXEC SQL VAR MaxAmountInterval IS STRING(129); */ 

	/* EXEC SQL VAR MaxAmountIntervalType IS STRING(33); */ 

	/* EXEC SQL VAR MaxAmountAction IS STRING(33); */ 

	/* EXEC SQL VAR MaxAmountFee IS STRING(129); */ 

	/* EXEC SQL VAR MaxCount IS STRING(129); */ 

	/* EXEC SQL VAR MaxCountInterval IS STRING(129); */ 

	/* EXEC SQL VAR MaxCountIntervalType IS STRING(129); */ 

	/* EXEC SQL VAR MaxCountAction IS STRING(33); */ 

	/* EXEC SQL VAR MaxCountFee IS STRING(129); */ 

		
	/* EXEC SQL DECLARE ezextntwkprofile_cur CURSOR FOR
    SELECT
		RTRIM(EXTNETWORKID),
		RTRIM(TXNCODELIST),
		RTRIM(TXNCOUNTCHECKREQ),
		RTRIM(TXNAMOUNTCHECKREQ),
        RTRIM(MAXAMOUNTPERTXN),
        RTRIM(MAXAMOUNT),
        RTRIM(MAXAMOUNTINTERVAL),
        RTRIM(MAXAMOUNTINTERVALTYPE),
        RTRIM(MAXAMOUNTACTION),
        RTRIM(MAXAMOUNTFEE),
        RTRIM(MAXCOUNT),
        RTRIM(MAXCOUNTINTERVAL),
        RTRIM(MAXCOUNTINTERVALTYPE),
        RTRIM(MAXCOUNTACTION),
        RTRIM(MAXCOUNTFEE)
    FROM EZEXTNTWKPROFILE; */ 

		
	/* EXEC SQL OPEN ezextntwkprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0042;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1816;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	while( 1 )
	{
		memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
		memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
		memset( TxnCountCheckReq, 0, sizeof( TxnCountCheckReq ) );
		memset( TxnAmountCheckReq, 0, sizeof( TxnAmountCheckReq ) );
		memset( MaxAmountPerTxn, 0, sizeof( MaxAmountPerTxn ) );
		memset( MaxAmount, 0, sizeof( MaxAmount ) );
		memset( MaxAmountInterval, 0, sizeof( MaxAmountInterval ) );
		memset( MaxAmountIntervalType, 0, sizeof( MaxAmountIntervalType ) );
		memset( MaxAmountAction, 0, sizeof( MaxAmountAction ) );
		memset( MaxAmountFee, 0, sizeof( MaxAmountFee ) );
		memset( MaxCount, 0, sizeof( MaxCount ) );
		memset( MaxCountInterval, 0, sizeof( MaxCountInterval ) );
		memset( MaxCountIntervalType, 0, sizeof( MaxCountIntervalType ) );
		memset( MaxCountAction, 0, sizeof( MaxCountAction ) );
		memset( MaxCountFee, 0, sizeof( MaxCountFee ) );
		
		/* EXEC SQL FETCH ezextntwkprofile_cur INTO
		:ExtNetworkId,
		:TxnCodeList,
		:TxnCountCheckReq,
		:TxnAmountCheckReq,
		:MaxAmountPerTxn,
		:MaxAmount,
		:MaxAmountInterval,
		:MaxAmountIntervalType,
		:MaxAmountAction,
		:MaxAmountFee,
		:MaxCount,
		:MaxCountInterval,
		:MaxCountIntervalType,
		:MaxCountAction,
		:MaxCountFee; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 23;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1831;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)ExtNetworkId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)TxnCodeList;
  sqlstm.sqhstl[1] = (unsigned int  )65;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)TxnCountCheckReq;
  sqlstm.sqhstl[2] = (unsigned int  )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)TxnAmountCheckReq;
  sqlstm.sqhstl[3] = (unsigned int  )33;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)MaxAmountPerTxn;
  sqlstm.sqhstl[4] = (unsigned int  )129;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)MaxAmount;
  sqlstm.sqhstl[5] = (unsigned int  )129;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)MaxAmountInterval;
  sqlstm.sqhstl[6] = (unsigned int  )129;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)MaxAmountIntervalType;
  sqlstm.sqhstl[7] = (unsigned int  )33;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         void  *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned int  )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (         void  *)MaxAmountAction;
  sqlstm.sqhstl[8] = (unsigned int  )33;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         void  *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned int  )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (         void  *)MaxAmountFee;
  sqlstm.sqhstl[9] = (unsigned int  )129;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         void  *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned int  )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (         void  *)MaxCount;
  sqlstm.sqhstl[10] = (unsigned int  )129;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         void  *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned int  )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (         void  *)MaxCountInterval;
  sqlstm.sqhstl[11] = (unsigned int  )129;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         void  *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned int  )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (         void  *)MaxCountIntervalType;
  sqlstm.sqhstl[12] = (unsigned int  )129;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         void  *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned int  )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (         void  *)MaxCountAction;
  sqlstm.sqhstl[13] = (unsigned int  )33;
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         void  *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned int  )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (         void  *)MaxCountFee;
  sqlstm.sqhstl[14] = (unsigned int  )129;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         void  *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned int  )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
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


				
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezextntwkprofile_ptr + i ), 0, sizeof( struct EzExtNtwkProfileMemory ) );
		strcpy( ( ezextntwkprofile_ptr + i )->ExtNetworkId, ExtNetworkId );
		strcpy( ( ezextntwkprofile_ptr + i )->TxnCodeList, TxnCodeList );
		strcpy( ( ezextntwkprofile_ptr + i )->TxnCountCheckReq, TxnCountCheckReq );
		strcpy( ( ezextntwkprofile_ptr + i )->TxnAmountCheckReq, TxnAmountCheckReq );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountPerTxn, MaxAmountPerTxn );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmount, MaxAmount );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountInterval, MaxAmountInterval );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountIntervalType, MaxAmountIntervalType );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountAction, MaxAmountAction );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxAmountFee, MaxAmountFee );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCount, MaxCount );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountInterval, MaxCountInterval );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountIntervalType, MaxCountIntervalType );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountAction, MaxCountAction );
		strcpy( ( ezextntwkprofile_ptr + i )->MaxCountFee, MaxCountFee );
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezextntwkprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 23;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1906;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	if( *SqlErr != 1403 )
		return -1;
	else
		return 1;	
}





