
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
           char  filnam[14];
};
static struct sqlcxp sqlfpn =
{
    13,
    "ezatmmgrdb.pc"
};


static unsigned int sqlctx = 615275;


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
            void  *sqhstv[51];
   unsigned int   sqhstl[51];
            int   sqhsts[51];
            void  *sqindv[51];
            int   sqinds[51];
   unsigned int   sqharm[51];
   unsigned int   *sqharc[51];
   unsigned short  sqadto[51];
   unsigned short  sqtdso[51];
} sqlstm = {12,51};

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

 static char *sq0008 = 
"select RTRIM(ATMID)  from EZATMINFO            ";

 static char *sq0010 = 
"select RTRIM(RECORDID) ,RTRIM(INSTID) ,RTRIM(ATMLOGICALGROUP) ,RTRIM(ATMID) \
,RTRIM(SECURITYID) ,RTRIM(FITRECORD) ,INDIRECTSTATE  from EZATMFIT            ";

 static char *sq0011 = 
"select RECORDID ,RTRIM(INSTTERMINALGROUP) ,RTRIM(ATMLOGICALGROUP) ,RTRIM(ATM\
ID) ,RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,DOWNLOADCHECKREQ ,FINGERPRINTCHECKREQ ,R\
TRIM(FINGERPRINTCHECKCHANNEL) ,JOURNALPRINTERREQ ,PASSBOOKPRINTERREQ ,STATEMEN\
TPRINTERREQ ,PARTIALREVERSALREQ ,CARDREADERMODEL ,DECIMALPOINTCHECKREQ ,CURREN\
CYCODE ,DECIMALMULTIPLIER ,COUNTERREFERSH ,KEYREFERSH  from EZATMPROPERTY     \
       ";

 static char *sq0012 = 
"select RECORDID ,RTRIM(INSTTERMINALGROUP) ,RTRIM(LOGICALGROUPID) ,RTRIM(ATMI\
D) ,RTRIM(STATUS) ,SENDCOMMAND ,RTRIM(COMMAND) ,SENDRESPONSE ,RTRIM(TXNCODE) ,\
RESPCODE  from EZATMACTIONPROPERTY            ";

 static char *sq0013 = 
"select RTRIM(STATUSCODE) ,STATUSFLAG  from EZATMSTATUSDESC            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,42,0,4,18,0,0,1,0,0,1,0,2,3,0,0,
24,0,0,2,71,0,4,40,0,0,2,1,0,1,0,2,3,0,0,1,5,0,0,
47,0,0,3,41,0,4,56,0,0,1,0,0,1,0,2,3,0,0,
66,0,0,4,44,0,4,72,0,0,1,0,0,1,0,2,3,0,0,
85,0,0,5,46,0,4,89,0,0,1,0,0,1,0,2,3,0,0,
104,0,0,6,52,0,4,101,0,0,1,0,0,1,0,2,3,0,0,
123,0,0,7,48,0,4,113,0,0,1,0,0,1,0,2,3,0,0,
142,0,0,8,47,0,9,138,0,0,0,0,0,1,0,
157,0,0,8,0,0,13,144,0,0,1,0,0,1,0,2,5,0,0,
176,0,0,8,0,0,15,160,0,0,0,0,0,1,0,
191,0,0,9,389,0,4,212,0,0,17,1,0,1,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,3,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,
2,3,0,0,1,5,0,0,
274,0,0,10,154,0,9,303,0,0,0,0,0,1,0,
289,0,0,10,0,0,13,314,0,0,7,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,
332,0,0,10,0,0,15,342,0,0,0,0,0,1,0,
347,0,0,11,395,0,9,405,0,0,0,0,0,1,0,
362,0,0,11,0,0,13,416,0,0,19,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,2,1,0,0,2,5,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,1,0,0,
2,3,0,0,2,1,0,0,2,3,0,0,2,3,0,0,
453,0,0,11,0,0,15,469,0,0,0,0,0,1,0,
468,0,0,12,200,0,9,516,0,0,0,0,0,1,0,
483,0,0,12,0,0,13,528,0,0,10,0,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
1,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,
538,0,0,12,0,0,15,560,0,0,0,0,0,1,0,
553,0,0,13,70,0,9,584,0,0,0,0,0,1,0,
568,0,0,13,0,0,13,590,0,0,2,0,0,1,0,2,5,0,0,2,1,0,0,
591,0,0,13,0,0,15,606,0,0,0,0,0,1,0,
606,0,0,14,66,0,4,630,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
629,0,0,15,101,0,3,644,0,0,3,3,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,
656,0,0,16,0,0,29,664,0,0,0,0,0,1,0,
671,0,0,17,67,0,4,693,0,0,2,1,0,1,0,2,3,0,0,1,5,0,0,
694,0,0,18,71,0,3,703,0,0,3,3,0,1,0,1,5,0,0,1,3,0,0,1,5,0,0,
721,0,0,19,0,0,29,724,0,0,0,0,0,1,0,
736,0,0,20,73,0,4,764,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
759,0,0,21,104,0,4,800,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
790,0,0,22,104,0,4,804,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
821,0,0,23,104,0,4,808,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
852,0,0,24,104,0,4,812,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
883,0,0,25,104,0,4,816,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
914,0,0,26,104,0,4,820,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
945,0,0,27,104,0,4,824,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
976,0,0,28,104,0,4,828,0,0,4,1,0,1,0,2,1,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
1007,0,0,29,204,0,4,894,0,0,8,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,1,0,0,1,5,0,0,1,5,0,0,
1054,0,0,30,123,0,3,958,0,0,5,5,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1089,0,0,31,0,0,29,978,0,0,0,0,0,1,0,
1104,0,0,32,105,0,5,1011,0,0,4,4,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1135,0,0,33,0,0,29,1021,0,0,0,0,0,1,0,
1150,0,0,34,60,0,5,1028,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
1173,0,0,35,0,0,29,1036,0,0,0,0,0,1,0,
1188,0,0,36,105,0,3,1068,0,0,5,5,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,0,
1223,0,0,37,0,0,29,1089,0,0,0,0,0,1,0,
1238,0,0,38,305,0,3,1140,0,0,13,13,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,
1305,0,0,39,0,0,29,1176,0,0,0,0,0,1,0,
1320,0,0,40,239,0,4,1220,0,0,9,1,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,
2,3,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
1371,0,0,41,283,0,5,1249,0,0,11,11,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1430,0,0,42,0,0,29,1266,0,0,0,0,0,1,0,
1445,0,0,43,21,0,1,1273,0,0,0,0,0,1,0,
1460,0,0,44,34,0,1,1279,0,0,0,0,0,1,0,
1475,0,0,45,30,0,1,1285,0,0,0,0,0,1,0,
1490,0,0,46,60,0,5,1304,0,0,2,2,0,1,0,1,3,0,0,1,5,0,0,
1513,0,0,47,0,0,29,1311,0,0,0,0,0,1,0,
1528,0,0,48,71,0,3,1334,0,0,3,3,0,1,0,1,5,0,0,1,3,0,0,1,5,0,0,
1555,0,0,49,0,0,29,1351,0,0,0,0,0,1,0,
1570,0,0,50,850,0,5,1545,0,0,51,51,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,
0,0,1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1789,0,0,51,302,0,3,1601,0,0,51,51,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,
0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,
0,0,1,1,0,0,1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
2008,0,0,52,0,0,29,1656,0,0,0,0,0,1,0,
2023,0,0,53,0,0,29,1661,0,0,0,0,0,1,0,
2038,0,0,54,180,0,4,1695,0,0,7,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,
2,5,0,0,1,5,0,0,
2081,0,0,55,471,0,4,1764,0,0,19,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,1,0,0,2,1,0,0,2,5,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,3,
0,0,2,1,0,0,2,3,0,0,2,3,0,0,1,3,0,0,
2172,0,0,56,238,0,4,1857,0,0,10,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,
0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,1,3,0,0,
2227,0,0,57,69,0,4,1908,0,0,2,1,0,1,0,2,1,0,0,1,97,0,0,
};


#include<sqlca.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ezbusiness/ezatmmgrtypes.h>
#include<ezbusiness/ezatmejtypes.h>
#include<ezbusiness/ezbusinesstypes.h>
#include <ezdb/ezatmproperty.h>
#include <ezdb/ezatmactionproperty.h>


int getAtmCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMINFO; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMINFO ";
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


    if ( sqlca.sqlcode != 0 )
    {
    	*SqlErr = sqlca.sqlcode;
    	return -1;
    }
    else
        return reccount;
}

int getInstAtmCount( const char *InstId, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        int reccount;
        char hInstId[ 13 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR hInstId IS STRING(17); */ 
	
	
	memset( hInstId, 0, sizeof( hInstId ) );
	strcpy( hInstId, InstId );

    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMINFO WHERE RTRIM(ACQUIRERINST)=:hInstId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMINFO where RTRIM(ACQ\
UIRERINST)=:b1";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )24;
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
    sqlstm.sqhstv[1] = (         void  *)hInstId;
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
    {
    	*SqlErr = sqlca.sqlcode;
    	return -1;
    }
    else
        return reccount;
}

int getAtmFitCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

    	int reccount;
	/* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMFIT; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMFIT ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )47;
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


    if ( sqlca.sqlcode != 0 )
    {
    	*SqlErr = sqlca.sqlcode;
    	return -1;
    }
    else
        return reccount;
}

int getAtmEjCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

            int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMEJINFO; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMEJINFO ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )66;
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


    
    if ( sqlca.sqlcode != 0 )
    {
    	*SqlErr = sqlca.sqlcode;
    	return -1;
    }
    else
        return reccount;
}

int getAtmPropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )85;
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

int getAtmActionPropertyCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMACTIONPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMACTIONPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )104;
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

int getAtmStatusCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZATMSTATUSDESC; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 2;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZATMSTATUSDESC ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )123;
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


    if ( sqlca.sqlcode != 0 )
    {
    	*SqlErr = sqlca.sqlcode;
    	return -1;
    }
    else
        return reccount;
}

int LoadAtmId( struct AtmMemoryTable *atmptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hAtmId[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 


	/* EXEC SQL DECLARE atmid_cur CURSOR FOR
    SELECT
    	RTRIM(ATMID)	
    FROM EZATMINFO; */ 

		
	/* EXEC SQL OPEN atmid_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0008;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )142;
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
		memset( hAtmId, 0, sizeof( hAtmId ) );
		
		/* EXEC SQL FETCH atmid_cur INTO
		:hAtmId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )157;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)hAtmId;
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
			break;
       
		if ( sqlca.sqlcode == 1403 )
            break;
                	
		memset( ( atmptr + i )->AtmId, 0, sizeof( ( atmptr + i )->AtmId ) );
		strcpy( ( atmptr+ i )->AtmId, hAtmId );
				
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE atmid_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )176;
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

int LoadAtm( struct AtmTableInfo *atminfo_ptr, char *atmid )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hAtmId[ 17 ];
		char hAtmTypeId[ 17 ];
		char hAtmLogicalGroup[ 17 ];
		int  hMerchantId;
		char hTerminalId[ 17 ];
		char hAtmLocation[ 41 ];
		char hAcquirerInst[ 13 ];
		char hAcquirerBranchCode[ 13 ];
		int  hAtmConfigId;
		char hLoggingFlag;
		char hPinVerFlag;
		char hAtmStatus;
		char hAtmMasterKey[ 65 ];
		char hAtmCommKey[ 65 ];
		int  hAtmKeyLen;
		int  hMaxNoteDisp;
		int  hMaxAmountDisp;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR hAtmId IS STRING(17); */ 
	
	/* EXEC SQL VAR hAtmTypeId IS STRING(17); */ 
	
	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hTerminalId IS STRING(17); */ 

	/* EXEC SQL VAR hAtmLocation IS STRING(33); */ 

	/* EXEC SQL VAR hAcquirerInst IS STRING(13); */ 

	/* EXEC SQL VAR hAcquirerBranchCode IS STRING(13); */ 

	/* EXEC SQL VAR hAtmMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR hAtmCommKey IS STRING(65); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hAtmTypeId, 0, sizeof( hAtmTypeId ) );		
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmLocation, 0, sizeof( hAtmLocation ) );
	memset( hTerminalId, 0, sizeof( hTerminalId ) );
	memset( hAcquirerInst, 0, sizeof( hAcquirerInst ) );
	memset( hAcquirerBranchCode, 0, sizeof( hAcquirerBranchCode ) );
	memset( hAtmMasterKey, 0, sizeof( hAtmMasterKey ) );
	memset( hAtmCommKey, 0, sizeof( hAtmCommKey ) );
	
	strcpy( hAtmId, atmid );
	
	/* EXEC SQL SELECT
        RTRIM(ATMTYPEID),
		RTRIM(ATMLOGICALGROUP),
		MERCHANTID,
		RTRIM(TERMINALID),
		RTRIM(ATMLOCATION),
		RTRIM(ACQUIRERINST),
		RTRIM(ACQUIRERBRANCHCODE),
		ATMCONFIGID,
		LOGGINGFLAG,
		PINVERFLAG,
		ATMSTATUS,
		RTRIM(ATMMASTERKEY),
		RTRIM(ATMCOMMKEY),
		ATMKEYLEN,
		MAXNOTEDISP,
		MAXAMOUNTDISP
	INTO
		:hAtmTypeId,
		:hAtmLogicalGroup,
		:hMerchantId,
		:hTerminalId,
		:hAtmLocation,
		:hAcquirerInst,
		:hAcquirerBranchCode,
		:hAtmConfigId,
		:hLoggingFlag,
		:hPinVerFlag,
		:hAtmStatus,
		:hAtmMasterKey,
		:hAtmCommKey,
		:hAtmKeyLen,
		:hMaxNoteDisp,
		:hMaxAmountDisp
	FROM EZATMINFO WHERE RTRIM(ATMID) = :hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(ATMTYPEID) ,RTRIM(ATMLOGICALGROUP) ,MERCHANTID \
,RTRIM(TERMINALID) ,RTRIM(ATMLOCATION) ,RTRIM(ACQUIRERINST) ,RTRIM(ACQUIRERBRA\
NCHCODE) ,ATMCONFIGID ,LOGGINGFLAG ,PINVERFLAG ,ATMSTATUS ,RTRIM(ATMMASTERKEY)\
 ,RTRIM(ATMCOMMKEY) ,ATMKEYLEN ,MAXNOTEDISP ,MAXAMOUNTDISP into :b0,:b1,:b2,:b\
3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15  from EZATMINFO where \
RTRIM(ATMID)=:b16";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )191;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hAtmTypeId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hAtmLogicalGroup;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&hMerchantId;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)hTerminalId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)hAtmLocation;
 sqlstm.sqhstl[4] = (unsigned int  )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)hAcquirerInst;
 sqlstm.sqhstl[5] = (unsigned int  )13;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)hAcquirerBranchCode;
 sqlstm.sqhstl[6] = (unsigned int  )13;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&hAtmConfigId;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&hLoggingFlag;
 sqlstm.sqhstl[8] = (unsigned int  )1;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&hPinVerFlag;
 sqlstm.sqhstl[9] = (unsigned int  )1;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&hAtmStatus;
 sqlstm.sqhstl[10] = (unsigned int  )1;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)hAtmMasterKey;
 sqlstm.sqhstl[11] = (unsigned int  )65;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)hAtmCommKey;
 sqlstm.sqhstl[12] = (unsigned int  )65;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&hAtmKeyLen;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&hMaxNoteDisp;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&hMaxAmountDisp;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)hAtmId;
 sqlstm.sqhstl[16] = (unsigned int  )17;
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


		
	if( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
		
   	strcpy( atminfo_ptr->AtmTypeId, hAtmTypeId );
	strcpy( atminfo_ptr->AtmLogicalGroup, hAtmLogicalGroup );
	atminfo_ptr->MerchantId = hMerchantId;
	strcpy( atminfo_ptr->TerminalId, hTerminalId );
	strcpy( atminfo_ptr->AtmLocation, hAtmLocation );
	strcpy( atminfo_ptr->AcquirerInst, hAcquirerInst );
	strcpy( atminfo_ptr->AcquirerBranchCode, hAcquirerBranchCode );
	atminfo_ptr->AtmConfigId = hAtmConfigId;
	atminfo_ptr->LoggingFlag = hLoggingFlag;
	atminfo_ptr->PinVerFlag = hPinVerFlag;
	atminfo_ptr->AtmStatus = hAtmStatus;
	strcpy( atminfo_ptr->AtmMasterKey, hAtmMasterKey );
	strcpy( atminfo_ptr->AtmCommKey, hAtmCommKey );
	atminfo_ptr->AtmKeyLen = hAtmKeyLen;
	atminfo_ptr->MaxNoteDisp = hMaxNoteDisp;
	atminfo_ptr->MaxAmountDisp = hMaxAmountDisp; 
	return sqlca.sqlcode;
	
}

int LoadAtmFitDetails( struct AtmFit *atmfit_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char InstId[ 13 ];
		char AtmLogicalGroup[ 17 ];
		char AtmId[ 17 ];
		char SecurityId[ 11 ];
		char FitRecord[ 11 ];
		char IndirectState;
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;

	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR AtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR AtmId IS STRING(17); */ 

	/* EXEC SQL VAR SecurityId IS STRING(11); */ 

	/* EXEC SQL VAR FitRecord IS STRING(11); */ 

		
	/* EXEC SQL DECLARE atmfit_cur CURSOR FOR
        SELECT
        	RTRIM(RECORDID),
           	RTRIM(INSTID),
			RTRIM(ATMLOGICALGROUP),
			RTRIM(ATMID),
			RTRIM(SECURITYID),
			RTRIM(FITRECORD),
			INDIRECTSTATE
	    FROM EZATMFIT; */ 

		
	/* EXEC SQL OPEN atmfit_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0010;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )274;
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
		memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
		memset( FitRecord, 0, sizeof( FitRecord ) );
		memset( SecurityId, 0, sizeof( SecurityId ) );
		memset( AtmId, 0, sizeof( AtmId ) );
		
		/* EXEC SQL FETCH atmfit_cur INTO
			:RecordId,
			:InstId,
			:AtmLogicalGroup,
			:AtmId,
			:SecurityId,
			:FitRecord,
			:IndirectState; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 17;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )289;
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
  sqlstm.sqhstv[4] = (         void  *)SecurityId;
  sqlstm.sqhstl[4] = (unsigned int  )11;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)FitRecord;
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


		
		if( sqlca.sqlcode == 1403 )
			break;
        		
		if( sqlca.sqlcode != 0 )
		   	break;
                        
		memset( atmfit_ptr + i, 0, sizeof( struct AtmFit ) );
		strcpy( ( atmfit_ptr + i )->RecordId, RecordId );
		strcpy( ( atmfit_ptr + i )->InstId, InstId );
		strcpy( ( atmfit_ptr + i )->AtmLogicalGroup, AtmLogicalGroup );
		strcpy( ( atmfit_ptr + i )->AtmId, AtmId );
		strcpy( ( atmfit_ptr + i )->SecurityId, SecurityId );
		strcpy( ( atmfit_ptr + i )->FitRecord, FitRecord );
		( atmfit_ptr + i )->IndirectState = IndirectState;
		
		i++;
	}

	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE atmfit_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )332;
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

int LoadAtmPropertyTable( struct EzAtmProperty *ezatmproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int	 hRecordId;
		char hInstTerminalGroup[ 17 ];
		char hAtmLogicalGroup[ 17 ];
		char hAtmId[ 17 ];
		char hDownloadCheckReq;
		char hFingerPrintCheckReq;
		char hFingerPrintCheckChannel[ 33 ];
		char hJournalPrinterReq;
		char hPassbookPrinterReq;
		char hStatementPrinterReq;
		char hPartialReversalReq;
		char hCardReaderModel;
		char hTxnCode[ 7 ];
		char hRespCode[ 4 ];
		char hDecimalPointCheckReq;
		int  hCurrencyCode;
		char hDecimalMultiplier;
 		int  hCounterRefresh;
 		int  hKeyRefresh;
 		int  i = 0;
    /* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR hInstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hFingerPrintCheckChannel IS STRING(33); */ 

	/* EXEC SQL VAR hTxnCode IS STRING(7); */ 

	/* EXEC SQL VAR hRespCode IS STRING(4); */ 

	
	/* EXEC SQL DECLARE ezatmproperty_cur CURSOR FOR
    SELECT
    	RECORDID,
    	RTRIM(INSTTERMINALGROUP),
		RTRIM(ATMLOGICALGROUP),
		RTRIM(ATMID),
		RTRIM(TXNCODE),
		RTRIM(RESPCODE),
		DOWNLOADCHECKREQ,
		FINGERPRINTCHECKREQ,
		RTRIM(FINGERPRINTCHECKCHANNEL),
		JOURNALPRINTERREQ,
		PASSBOOKPRINTERREQ,
		STATEMENTPRINTERREQ,
		PARTIALREVERSALREQ,
		CARDREADERMODEL,
		DECIMALPOINTCHECKREQ,
		CURRENCYCODE,
		DECIMALMULTIPLIER,
		COUNTERREFERSH,
		KEYREFERSH
	FROM EZATMPROPERTY; */ 

		
	/* EXEC SQL OPEN ezatmproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0011;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )347;
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
		memset( hInstTerminalGroup, 0, sizeof( hInstTerminalGroup ) );
		memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
		memset( hAtmId, 0, sizeof( hAtmId ) );
		memset( hFingerPrintCheckChannel, 0, sizeof( hFingerPrintCheckChannel ) );
		memset( hTxnCode, 0, sizeof( hTxnCode ) );
		memset( hRespCode, 0, sizeof( hRespCode ) );

		/* EXEC SQL FETCH ezatmproperty_cur INTO
			:hRecordId,
			:hInstTerminalGroup,
			:hAtmLogicalGroup,
			:hAtmId,
			:hTxnCode,
			:hRespCode,
			:hDownloadCheckReq,
			:hFingerPrintCheckReq,
			:hFingerPrintCheckChannel,
			:hJournalPrinterReq,
			:hPassbookPrinterReq,
			:hStatementPrinterReq,
			:hPartialReversalReq,
			:hCardReaderModel,
			:hDecimalPointCheckReq,
			:hCurrencyCode,
			:hDecimalMultiplier,
			:hCounterRefresh,
			:hKeyRefresh; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )362;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&hRecordId;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)hInstTerminalGroup;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)hAtmLogicalGroup;
  sqlstm.sqhstl[2] = (unsigned int  )17;
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
  sqlstm.sqhstv[4] = (         void  *)hTxnCode;
  sqlstm.sqhstl[4] = (unsigned int  )7;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)hRespCode;
  sqlstm.sqhstl[5] = (unsigned int  )4;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&hDownloadCheckReq;
  sqlstm.sqhstl[6] = (unsigned int  )1;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)&hFingerPrintCheckReq;
  sqlstm.sqhstl[7] = (unsigned int  )1;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         void  *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned int  )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (         void  *)hFingerPrintCheckChannel;
  sqlstm.sqhstl[8] = (unsigned int  )33;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         void  *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned int  )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (         void  *)&hJournalPrinterReq;
  sqlstm.sqhstl[9] = (unsigned int  )1;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         void  *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned int  )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (         void  *)&hPassbookPrinterReq;
  sqlstm.sqhstl[10] = (unsigned int  )1;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         void  *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned int  )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (         void  *)&hStatementPrinterReq;
  sqlstm.sqhstl[11] = (unsigned int  )1;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         void  *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned int  )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (         void  *)&hPartialReversalReq;
  sqlstm.sqhstl[12] = (unsigned int  )1;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         void  *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned int  )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (         void  *)&hCardReaderModel;
  sqlstm.sqhstl[13] = (unsigned int  )1;
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         void  *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned int  )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (         void  *)&hDecimalPointCheckReq;
  sqlstm.sqhstl[14] = (unsigned int  )1;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         void  *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned int  )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (         void  *)&hCurrencyCode;
  sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         void  *)0;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned int  )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (         void  *)&hDecimalMultiplier;
  sqlstm.sqhstl[16] = (unsigned int  )1;
  sqlstm.sqhsts[16] = (         int  )0;
  sqlstm.sqindv[16] = (         void  *)0;
  sqlstm.sqinds[16] = (         int  )0;
  sqlstm.sqharm[16] = (unsigned int  )0;
  sqlstm.sqadto[16] = (unsigned short )0;
  sqlstm.sqtdso[16] = (unsigned short )0;
  sqlstm.sqhstv[17] = (         void  *)&hCounterRefresh;
  sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[17] = (         int  )0;
  sqlstm.sqindv[17] = (         void  *)0;
  sqlstm.sqinds[17] = (         int  )0;
  sqlstm.sqharm[17] = (unsigned int  )0;
  sqlstm.sqadto[17] = (unsigned short )0;
  sqlstm.sqtdso[17] = (unsigned short )0;
  sqlstm.sqhstv[18] = (         void  *)&hKeyRefresh;
  sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezatmproperty_ptr + i ), 0, sizeof( struct EzAtmProperty ) );
		( ezatmproperty_ptr + i )->RecordId = hRecordId;
		strcpy( ( ezatmproperty_ptr + i )->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ( ezatmproperty_ptr + i )->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ( ezatmproperty_ptr + i )->AtmId, hAtmId );
		strcpy( ( ezatmproperty_ptr + i )->TxnCode, hTxnCode );
		strcpy( ( ezatmproperty_ptr + i )->RespCode, hRespCode );
		( ezatmproperty_ptr + i )->DownloadCheckReq = hDownloadCheckReq;
		( ezatmproperty_ptr + i )->FingerPrintCheckReq = hFingerPrintCheckReq;
		strcpy( ( ezatmproperty_ptr + i )->FingerPrintCheckChannel, hFingerPrintCheckChannel );
		( ezatmproperty_ptr + i )->JournalPrinterReq = hJournalPrinterReq;
		( ezatmproperty_ptr + i )->PassbookPrinterReq = hPassbookPrinterReq;
		( ezatmproperty_ptr + i )->StatementPrinterReq = hStatementPrinterReq;
		( ezatmproperty_ptr + i )->PartialReversalReq = hPartialReversalReq;
		( ezatmproperty_ptr + i )->CardReaderModel = hCardReaderModel;
		( ezatmproperty_ptr + i )->DecimalPointCheckReq = hDecimalPointCheckReq;
		( ezatmproperty_ptr + i )->CurrencyCode = hCurrencyCode;
		( ezatmproperty_ptr + i )->DecimalMultiplier = hDecimalMultiplier;
		( ezatmproperty_ptr + i )->CounterRefresh = hCounterRefresh;
		( ezatmproperty_ptr + i )->KeyRefresh = hKeyRefresh;
		
		i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	
	/* EXEC SQL CLOSE ezatmproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )453;
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

int LoadAtmActionPropertyTable( struct EzAtmActionProperty *ezatmactionproperty_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int  hRecordId;
		char hInstTerminalGroup[ 17 ];
		char hAtmLogicalGroup[ 17 ];
		char hAtmId[ 17 ];
		char hStatus[ 11 ];
		char hSendCommand;
		char hCommand[ 21 ];
		char hSendResponse;
		char hTxnCode[ 7 ];
		char hRespCode[ 4 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR hInstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hStatus IS STRING(11); */ 

	/* EXEC SQL VAR hCommand IS STRING(21); */ 

	/* EXEC SQL VAR hTxnCode IS STRING(7); */ 

	/* EXEC SQL VAR hRespCode IS STRING(4); */ 

	
	/* EXEC SQL DECLARE ezatmactionproperty_cur CURSOR FOR
    SELECT
    	RECORDID,
    	RTRIM(INSTTERMINALGROUP),
		RTRIM(LOGICALGROUPID),
		RTRIM(ATMID),
		RTRIM(STATUS),
		SENDCOMMAND,
		RTRIM(COMMAND),
		SENDRESPONSE,
		RTRIM(TXNCODE),
		RESPCODE
	FROM EZATMACTIONPROPERTY; */ 

		
	/* EXEC SQL OPEN ezatmactionproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0012;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )468;
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
		memset( hInstTerminalGroup, 0, sizeof( hInstTerminalGroup ) );
		memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
		memset( hAtmId, 0, sizeof( hAtmId ) );
		memset( hStatus, 0, sizeof( hStatus ) );
		memset( hCommand, 0, sizeof( hCommand ) );
		memset( hTxnCode, 0, sizeof( hTxnCode ) );
		memset( hRespCode, 0, sizeof( hRespCode ) );

		/* EXEC SQL FETCH ezatmactionproperty_cur INTO
			:hRecordId,
			:hInstTerminalGroup,
			:hAtmLogicalGroup,
			:hAtmId,
			:hStatus,
			:hSendCommand,
			:hCommand,
			:hSendResponse,
			:hTxnCode,
			:hRespCode; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )483;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&hRecordId;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)hInstTerminalGroup;
  sqlstm.sqhstl[1] = (unsigned int  )17;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)hAtmLogicalGroup;
  sqlstm.sqhstl[2] = (unsigned int  )17;
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
  sqlstm.sqhstv[4] = (         void  *)hStatus;
  sqlstm.sqhstl[4] = (unsigned int  )11;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&hSendCommand;
  sqlstm.sqhstl[5] = (unsigned int  )1;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)hCommand;
  sqlstm.sqhstl[6] = (unsigned int  )21;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)&hSendResponse;
  sqlstm.sqhstl[7] = (unsigned int  )1;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         void  *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned int  )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (         void  *)hTxnCode;
  sqlstm.sqhstl[8] = (unsigned int  )7;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         void  *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned int  )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (         void  *)hRespCode;
  sqlstm.sqhstl[9] = (unsigned int  )4;
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


		
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        
		memset( ( ezatmactionproperty_ptr + i ), 0, sizeof( struct EzAtmActionProperty ) );
		( ezatmactionproperty_ptr + i )->RecordId = hRecordId;
		strcpy( ( ezatmactionproperty_ptr + i )->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ( ezatmactionproperty_ptr + i )->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ( ezatmactionproperty_ptr + i )->AtmId, hAtmId );
		strcpy( ( ezatmactionproperty_ptr + i )->Status, hStatus );
		( ezatmactionproperty_ptr + i )->SendCommand = hSendCommand;
		strcpy( ( ezatmactionproperty_ptr + i )->Command, hCommand );
		( ezatmactionproperty_ptr + i )->SendResponse = hSendResponse;
		strcpy( ( ezatmactionproperty_ptr + i )->TxnCode, hTxnCode );
		strcpy( ( ezatmactionproperty_ptr + i )->RespCode, hRespCode );
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezatmactionproperty_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )538;
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

int LoadAtmStatusTable( struct EzAtmStatus *ezatmstatus_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hStatusCode[ 11 ];
		char hStatusFlag;
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR hStatusCode IS STRING(11); */ 

	
	/* EXEC SQL DECLARE ezatmstatus_cur CURSOR FOR
    SELECT
    	RTRIM(STATUSCODE),
		STATUSFLAG
	FROM EZATMSTATUSDESC; */ 

		
	/* EXEC SQL OPEN ezatmstatus_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0013;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )553;
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
		memset( hStatusCode, 0, sizeof( hStatusCode ) );
		
		/* EXEC SQL FETCH ezatmstatus_cur INTO
			:hStatusCode,
			:hStatusFlag; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )568;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)hStatusCode;
  sqlstm.sqhstl[0] = (unsigned int  )11;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&hStatusFlag;
  sqlstm.sqhstl[1] = (unsigned int  )1;
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
        
		memset( ( ezatmstatus_ptr + i ), 0, sizeof( struct EzAtmStatus ) );
		strcpy( ( ezatmstatus_ptr + i )->StatusCode, hStatusCode );
		( ezatmstatus_ptr + i )->StatusFlag = hStatusFlag;
		i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezatmstatus_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )591;
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

int LoadAtmStaticCode( const char *AtmId, char *StaticCode )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];  
		char hStaticCode[ 101 ];
		char hDynamicCode[ 101 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hStaticCode IS STRING( 101 ); */ 

	/* EXEC SQL VAR hDynamicCode IS STRING( 101 ); */ 


	memset( hAtmId, 0, sizeof( hAtmId ) );
	strcpy( hAtmId, AtmId );
	
	memset( hStaticCode, 0, sizeof( hStaticCode ) );
	
	/* EXEC SQL SELECT  
		STATICCODE
	INTO
		:hStaticCode
	FROM EZATMSTATUS WHERE TRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select STATICCODE into :b0  from EZATMSTATUS where trim(ATMI\
D)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )606;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hStaticCode;
 sqlstm.sqhstl[0] = (unsigned int  )101;
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

 
	
	if ( sqlca.sqlcode == 1403 )
	{
		memset( hStaticCode, 0, sizeof( hStaticCode ) );
		memset( hDynamicCode, 0, sizeof( hDynamicCode ) );	
		strcpy( hStaticCode, "NONE" );
		strcpy( hDynamicCode, "NONE" );
		strcpy( StaticCode, hStaticCode );
		
		/* EXEC SQL INSERT INTO EZATMSTATUS
		( 
			ATMID, 
			STATICCODE,
			DYNAMICCODE, 
			LOGDATE, 
			LOGTIME 
		)
		VALUES
		( 
			:hAtmId, 
			:hStaticCode,
			:hDynamicCode, 
			sysdate,
			0 
		); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "insert into EZATMSTATUS (ATMID,STATICCODE,DYNAMICCODE,LOGDA\
TE,LOGTIME) values (:b0,:b1,:b2,sysdate,0)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )629;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)hAtmId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)hStaticCode;
  sqlstm.sqhstl[1] = (unsigned int  )101;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)hDynamicCode;
  sqlstm.sqhstl[2] = (unsigned int  )101;
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


		if ( sqlca.sqlcode != 0 )
    		return ( sqlca.sqlcode );
		else
		{
			/* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )656;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
			return ( sqlca.sqlcode );
		} 
	}
	else if ( sqlca.sqlcode != 0 )
    	return ( sqlca.sqlcode );
	else
	{
		strcpy( StaticCode, hStaticCode );
		return 0;
	}
}

int GetTraceNum( char *AtmId, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

        char hAtmId[ 17 ];
		int hTraceNum;
		char hBatchId[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hBatchId IS STRING(13); */ 

		
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hBatchId, 0, sizeof( hBatchId ) );
	
	strcpy( hAtmId, AtmId );
	
	/* EXEC SQL SELECT
		TRACENUM
	INTO
		:hTraceNum
	FROM EZATMDATAINFO WHERE RTRIM(ATMID) = :hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select TRACENUM into :b0  from EZATMDATAINFO where RTRIM(ATM\
ID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )671;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&hTraceNum;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


	
	if( sqlca.sqlcode == 1403 )
	{
		hTraceNum = 1;
		strcpy( hBatchId, "123456789000" );
		/* EXEC SQL INSERT INTO EZATMDATAINFO
		( 
			ATMID, 
			TRACENUM,	
			BATCHID 
		)
		VALUES
		( 
			:hAtmId, 
			:hTraceNum,
			:hBatchId 
		); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "insert into EZATMDATAINFO (ATMID,TRACENUM,BATCHID) values (\
:b0,:b1,:b2)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )694;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)hAtmId;
  sqlstm.sqhstl[0] = (unsigned int  )17;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&hTraceNum;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)hBatchId;
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


		
		if( sqlca.sqlcode != 0 )
		{
			*SqlErr = sqlca.sqlcode;
			return -1;
		}
		else
		{
			*SqlErr = 0;
			/* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )721;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


			if( sqlca.sqlcode != 0 )
            {
            	*SqlErr = sqlca.sqlcode;
                return -1;
            }
            else
            {
            	*SqlErr = 0;
                return hTraceNum;
            }
		}
	}
	else if( sqlca.sqlcode != 0 )
    {
    	*SqlErr = sqlca.sqlcode;
    	return -1;
    }
    else
    {
    	*SqlErr = 0;
        return hTraceNum;
    }
}

int LoadAtmBatchId( char *AtmId, char *BatchId )
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
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(BATCHID) into :b0  from EZATMDATAINFO where RTR\
IM(ATMID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )736;
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

int LoadAtmDenom( const char *AtmId, struct DenomInfo *denominfoptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hAtmId[ 17 ];
		char hDenomId;
		int  hCassPosition;
		int  hCurrencyValue;
		int  hCurrencyCode;
		char hStatus;
	/* EXEC SQL END DECLARE SECTION; */ 

	int retval = -1;
	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	strcpy( hAtmId, AtmId );
	hDenomId = denominfoptr->DenomId;
	
	
	switch( hDenomId )
	{
		case 'A':
			/* EXEC SQL SELECT	DENOMASTATUS, DENOMAVALUE, DENOMACURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMASTATUS ,DENOMAVALUE ,DENOMACURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )759;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;
			
		case 'B':
			/* EXEC SQL SELECT	DENOMBSTATUS, DENOMBVALUE, DENOMBCURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMBSTATUS ,DENOMBVALUE ,DENOMBCURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )790;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		

		case 'C':
			/* EXEC SQL SELECT	DENOMCSTATUS, DENOMCVALUE, DENOMCCURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMCSTATUS ,DENOMCVALUE ,DENOMCCURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )821;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		

		case 'D':
			/* EXEC SQL SELECT	DENOMDSTATUS, DENOMDVALUE, DENOMDCURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMDSTATUS ,DENOMDVALUE ,DENOMDCURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )852;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		

		case 'E':
			/* EXEC SQL SELECT	DENOMESTATUS, DENOMEVALUE, DENOMECURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMESTATUS ,DENOMEVALUE ,DENOMECURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )883;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		

		case 'F':
			/* EXEC SQL SELECT	DENOMFSTATUS, DENOMFVALUE, DENOMFCURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMFSTATUS ,DENOMFVALUE ,DENOMFCURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )914;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		

		case 'G':
			/* EXEC SQL SELECT	DENOMGSTATUS, DENOMGVALUE, DENOMGCURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMGSTATUS ,DENOMGVALUE ,DENOMGCURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )945;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		

		case 'H':
			/* EXEC SQL SELECT	DENOMHSTATUS, DENOMHVALUE, DENOMHCURRCODE INTO :hStatus, :hCurrencyValue, :hCurrencyCode FROM EZATMINFO WHERE RTRIM(ATMID) =: hAtmId; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.stmt = "select DENOMHSTATUS ,DENOMHVALUE ,DENOMHCURRCODE into :b0,\
:b1,:b2  from EZATMINFO where RTRIM(ATMID)=:b3";
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )976;
   sqlstm.selerr = (unsigned short)1;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlstm.sqhstv[0] = (         void  *)&hStatus;
   sqlstm.sqhstl[0] = (unsigned int  )1;
   sqlstm.sqhsts[0] = (         int  )0;
   sqlstm.sqindv[0] = (         void  *)0;
   sqlstm.sqinds[0] = (         int  )0;
   sqlstm.sqharm[0] = (unsigned int  )0;
   sqlstm.sqadto[0] = (unsigned short )0;
   sqlstm.sqtdso[0] = (unsigned short )0;
   sqlstm.sqhstv[1] = (         void  *)&hCurrencyValue;
   sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
   sqlstm.sqhsts[1] = (         int  )0;
   sqlstm.sqindv[1] = (         void  *)0;
   sqlstm.sqinds[1] = (         int  )0;
   sqlstm.sqharm[1] = (unsigned int  )0;
   sqlstm.sqadto[1] = (unsigned short )0;
   sqlstm.sqtdso[1] = (unsigned short )0;
   sqlstm.sqhstv[2] = (         void  *)&hCurrencyCode;
   sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
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


			break;		
			
		Default:
			break;		
	}
	   
	if( sqlca.sqlcode == 0 )
	{
		denominfoptr->CurrencyValue = hCurrencyValue;
		denominfoptr->CurrencyCode = hCurrencyCode;
		denominfoptr->Status = hStatus;
		retval = sqlca.sqlcode;
	}
	else
	   retval = sqlca.sqlcode;
	   
	return retval; 
}


int AddAtmFit( struct AtmFit *Atmfit_ptr, struct AtmFitMsg *Atmfitmsg )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char InstId[ 13 ];
		char AtmLogicalGroup[ 17 ];
		char AtmId[ 17 ];
		char SecurityId[ 11 ];
		char FitRecord[ 11 ];
		char IndirectState;
		char hInstId[ 11 ];
		char hAtmLogicalGroup[ 17 ];
		char hAtmId[ 17 ];
		char hFitRecord[ 11 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;

	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR AtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR AtmId IS STRING(17); */ 

	/* EXEC SQL VAR SecurityId IS STRING(11); */ 

	/* EXEC SQL VAR FitRecord IS STRING(11); */ 

	/* EXEC SQL VAR hInstId IS STRING(11); */ 

	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hFitRecord IS STRING(11); */ 


	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( AtmId, 0, sizeof( AtmId ) );
	memset( FitRecord, 0, sizeof( FitRecord ) );
	
	memset( hInstId, 0, sizeof( hInstId ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hFitRecord, 0, sizeof( hFitRecord ) );
	
	strcpy( hInstId, Atmfitmsg->InstId );
	strcpy( hFitRecord, Atmfitmsg->FitRecord );
	
			
	/* EXEC SQL SELECT
			RTRIM(RECORDID),
           	RTRIM(INSTID),
			RTRIM(AtmLogicalGroup),
			RTRIM(ATMID),
			RTRIM(SECURITYID),
			INDIRECTSTATE
	INTO
			:RecordId,
			:InstId,
			:AtmLogicalGroup,
			:AtmId,
			:SecurityId,
			:IndirectState
	FROM EZATMFIT WHERE ( RTRIM(INSTID)=:hInstId AND RTRIM(FITRECORD)=:hFitRecord ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(INSTID) ,RTRIM(AtmLogicalGroup\
) ,RTRIM(ATMID) ,RTRIM(SECURITYID) ,INDIRECTSTATE into :b0,:b1,:b2,:b3,:b4,:b5\
  from EZATMFIT where (RTRIM(INSTID)=:b6 and RTRIM(FITRECORD)=:b7)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1007;
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
 sqlstm.sqhstv[4] = (         void  *)SecurityId;
 sqlstm.sqhstl[4] = (unsigned int  )11;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&IndirectState;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)hInstId;
 sqlstm.sqhstl[6] = (unsigned int  )11;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)hFitRecord;
 sqlstm.sqhstl[7] = (unsigned int  )11;
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
    {
	  	return sqlca.sqlcode;
    }
    else
    {
		strcpy( Atmfit_ptr->RecordId, RecordId );
	   	strcpy( Atmfit_ptr->InstId, InstId );
    	strcpy( Atmfit_ptr->AtmLogicalGroup, AtmLogicalGroup );
    	strcpy( Atmfit_ptr->AtmId, AtmId );
    	strcpy( Atmfit_ptr->FitRecord, hFitRecord );
    	strcpy( Atmfit_ptr->SecurityId, SecurityId );
    	Atmfit_ptr->IndirectState = IndirectState; 
        return sqlca.sqlcode;
    }
}

int InsertATMStatus( char *StaticCode, char *DynamicCode, char *AtmId, char *Date, char *Time )
{	
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];  
		char hDate[ 7 ];  
		char hTime[ 7 ];  
		char hDynamicCode[ 101 ];
		char hStaticCode[ 101 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hTime IS STRING( 7 ); */ 

	/* EXEC SQL VAR hDynamicCode IS STRING( 101 ); */ 

	/* EXEC SQL VAR hStaticCode IS STRING( 101 ); */ 


	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hDate, 0, sizeof( hDate ) );
	memset( hTime, 0, sizeof( hTime ) );
	memset( hStaticCode, 0, sizeof( hStaticCode ) );
	memset( hDynamicCode, 0, sizeof( hDynamicCode ) );
	
	strcpy( hAtmId, AtmId );
	strcpy( hDate, Date );
	strcpy( hTime, Time );
	strcpy( hDynamicCode, DynamicCode );
	if( strlen( StaticCode ) != 0 )
		strcpy( hStaticCode, StaticCode );
	else
		strcpy( hStaticCode, "NONE" );

	/* EXEC SQL INSERT INTO EZATMSTATUSHIST
	( 
		ATMID, 
		STATICCODE,
		DYNAMICCODE, 
		LOGDATE, 
		LOGTIME 
	)
	VALUES
	( 
		:hAtmId, 
		:hStaticCode,
		:hDynamicCode, 
		to_date( :hDate, 'dd-mm-yy' ),
		:hTime 
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMSTATUSHIST (ATMID,STATICCODE,DYNAMICCODE,LO\
GDATE,LOGTIME) values (:b0,:b1,:b2,to_date(:b3,'dd-mm-yy'),:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1054;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hAtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hStaticCode;
 sqlstm.sqhstl[1] = (unsigned int  )101;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hDynamicCode;
 sqlstm.sqhstl[2] = (unsigned int  )101;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)hDate;
 sqlstm.sqhstl[3] = (unsigned int  )7;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)hTime;
 sqlstm.sqhstl[4] = (unsigned int  )7;
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
    	return ( sqlca.sqlcode );
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1089;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
		return ( sqlca.sqlcode );
	}	
}

int UpdateATMStatus( char *StaticCode, char *DynamicCode, char *AtmId, char *Date, char *Time )
{	
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];  
		char hDate[ 7 ];  
		char hTime[ 7 ];
		char hDynamicCode[ 101 ];  
		char hStaticCode[ 101 ];
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hTime IS STRING( 7 ); */ 

	/* EXEC SQL VAR hStaticCode IS STRING( 101 ); */ 

	/* EXEC SQL VAR hDynamicCode IS STRING( 101 ); */ 


	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hDate, 0, sizeof( hDate ) );
	memset( hTime, 0, sizeof( hTime ) );
	memset( hStaticCode, 0, sizeof( hStaticCode ) );
	memset( hDynamicCode, 0, sizeof( hDynamicCode ) );
	
	strcpy( hAtmId, AtmId );
	strcpy( hDate, Date );
	strcpy( hTime, Time );
	strcpy( hStaticCode, StaticCode );
	strcpy( hDynamicCode, DynamicCode );

	/* EXEC SQL UPDATE EZATMSTATUS SET 
		DYNAMICCODE=:hDynamicCode,
		LOGDATE=to_date( :hDate, 'dd-mm-yy' ), 
		LOGTIME=:hTime 
	WHERE TRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMSTATUS  set DYNAMICCODE=:b0,LOGDATE=to_date(:b1,\
'dd-mm-yy'),LOGTIME=:b2 where trim(ATMID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1104;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hDynamicCode;
 sqlstm.sqhstl[0] = (unsigned int  )101;
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
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1135;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		if ( sqlca.sqlcode != 0 )
        	return ( sqlca.sqlcode );
	}
	
	if( strlen( hStaticCode ) != 0 )
	{
		/* EXEC SQL UPDATE EZATMSTATUS SET 
			STATICCODE=:hStaticCode
		WHERE TRIM(ATMID)=:hAtmId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "update EZATMSTATUS  set STATICCODE=:b0 where trim(ATMID)=:b\
1";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1150;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)hStaticCode;
  sqlstm.sqhstl[0] = (unsigned int  )101;
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


		
		if ( sqlca.sqlcode != 0 )
        	return ( sqlca.sqlcode );
		else
		{
			/* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 19;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )1173;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


			return ( sqlca.sqlcode );
		}
	} 	
}

int InsertAtmLog( struct LogDetails *logdetails )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];
		char hAtmMsg[ 1024 ];
		char hDate[ 7 ];  
		char hTime[ 7 ];  
		char hFlag;
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hTime IS STRING( 10 ); */ 

	/* EXEC SQL VAR hAtmMsg IS STRING( 1024 ); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hDate, 0, sizeof( hDate ) );
	memset( hTime, 0, sizeof( hTime ) );
	memset( hAtmMsg, 0, sizeof( hAtmMsg ) );
	
	strcpy( hAtmId, logdetails->AtmId );
	strcpy( hDate, logdetails->Date );
	strcpy( hTime, logdetails->Time );
	strcpy( hAtmMsg, logdetails->AtmMsg );
	hFlag = logdetails->Flag;

	/* EXEC SQL INSERT INTO EZATMLOG
	( 
		ATMID ,
		ATMMSG ,
		LOGDATE ,
		LOGTIME ,
		FLAG 
	)
	VALUES 
	( 
		:hAtmId,
		:hAtmMsg,
		to_date( :hDate, 'dd-mm-yy' ),
		:hTime,
		:hFlag
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMLOG (ATMID,ATMMSG,LOGDATE,LOGTIME,FLAG) val\
ues (:b0,:b1,to_date(:b2,'dd-mm-yy'),:b3,:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1188;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hAtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hAtmMsg;
 sqlstm.sqhstl[1] = (unsigned int  )1024;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hDate;
 sqlstm.sqhstl[2] = (unsigned int  )7;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)hTime;
 sqlstm.sqhstl[3] = (unsigned int  )10;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&hFlag;
 sqlstm.sqhstl[4] = (unsigned int  )1;
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
    	return ( sqlca.sqlcode );
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1223;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

 
		return ( sqlca.sqlcode );
	}	
}

int InsertAtmDenomHist( struct AtmDenomStatusMsg *atmdenomstatus_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];
		char hBatchId[ 13 ];
		char hRefNum[ 13 ];  
		int hDenom_A_Disp;
		int hDenom_B_Disp;
		int hDenom_C_Disp;
		int hDenom_D_Disp;
		int hDenom_E_Disp;
		int hDenom_F_Disp;
		int hDenom_G_Disp;
		int hDenom_H_Disp;   
	    char hResetDate[ 7 ];  
		char hResetTime[ 7 ];  
		int i, j;
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hBatchId IS STRING( 13 ); */ 

	/* EXEC SQL VAR hRefNum IS STRING( 13 ); */ 

	/* EXEC SQL VAR hResetDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hResetTime IS STRING( 7 ); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hBatchId, 0, sizeof( hBatchId ) );
	memset( hRefNum, 0, sizeof( hRefNum ) );
	memset( hResetDate, 0, sizeof( hResetDate ) );
	memset( hResetTime, 0, sizeof( hResetTime ) );
	
	strcpy( hAtmId, atmdenomstatus_ptr->AtmId );
	strcpy( hBatchId, atmdenomstatus_ptr->BatchId );
	strcpy( hRefNum, atmdenomstatus_ptr->RefNum );
	strcpy( hResetDate, atmdenomstatus_ptr->ResetDate );
	strcpy( hResetTime, atmdenomstatus_ptr->ResetTime );

	hDenom_A_Disp = atmdenomstatus_ptr->Denom_A_Disp;
	hDenom_B_Disp = atmdenomstatus_ptr->Denom_B_Disp;
	hDenom_C_Disp = atmdenomstatus_ptr->Denom_C_Disp;
	hDenom_D_Disp = atmdenomstatus_ptr->Denom_D_Disp;
	hDenom_E_Disp = atmdenomstatus_ptr->Denom_E_Disp;
	hDenom_F_Disp = atmdenomstatus_ptr->Denom_F_Disp;
	hDenom_G_Disp = atmdenomstatus_ptr->Denom_G_Disp;
	hDenom_H_Disp = atmdenomstatus_ptr->Denom_H_Disp;
	
	/* EXEC SQL INSERT INTO EZATMDENOMHIST
	( 
		ATMID,
		BATCHID,
		REFNUM,
		DENOM_A_NOTESDISP,
		DENOM_B_NOTESDISP,
		DENOM_C_NOTESDISP,
		DENOM_D_NOTESDISP,
		DENOM_E_NOTESDISP,
		DENOM_F_NOTESDISP,
		DENOM_G_NOTESDISP,
		DENOM_H_NOTESDISP,
		LASTRESETDATE,
		LASTRESETTIME
	)
	VALUES 
	( 
		:hAtmId,
		:hBatchId,
		:hRefNum,
		:hDenom_A_Disp,
		:hDenom_B_Disp,
		:hDenom_C_Disp,
		:hDenom_D_Disp,
		:hDenom_E_Disp,
		:hDenom_F_Disp,
		:hDenom_G_Disp,
		:hDenom_H_Disp,
		to_date( :hResetDate, 'dd-mm-yy' ),
		:hResetTime
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMDENOMHIST (ATMID,BATCHID,REFNUM,DENOM_A_NOT\
ESDISP,DENOM_B_NOTESDISP,DENOM_C_NOTESDISP,DENOM_D_NOTESDISP,DENOM_E_NOTESDISP\
,DENOM_F_NOTESDISP,DENOM_G_NOTESDISP,DENOM_H_NOTESDISP,LASTRESETDATE,LASTRESET\
TIME) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,to_date(:b11,'dd-mm\
-yy'),:b12)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1238;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hAtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hBatchId;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hRefNum;
 sqlstm.sqhstl[2] = (unsigned int  )13;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&hDenom_A_Disp;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&hDenom_B_Disp;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&hDenom_C_Disp;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&hDenom_D_Disp;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&hDenom_E_Disp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&hDenom_F_Disp;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&hDenom_G_Disp;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&hDenom_H_Disp;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)hResetDate;
 sqlstm.sqhstl[11] = (unsigned int  )7;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)hResetTime;
 sqlstm.sqhstl[12] = (unsigned int  )7;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
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
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1305;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		return ( sqlca.sqlcode );
	} 
}

int UpdateAtmDenomStatus( struct AtmDenomStatusMsg *atmdenomstatus_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];
		char hBatchId[ 13 ];
		char hRefNum[ 13 ];  
		int hDenom_A_Disp;
		int hDenom_B_Disp;
		int hDenom_C_Disp;
		int hDenom_D_Disp;
		int hDenom_E_Disp;
		int hDenom_F_Disp;
		int hDenom_G_Disp;
		int hDenom_H_Disp;   
	    char hResetDate[ 7 ];  
		char hResetTime[ 7 ];  
		int i, j;
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hBatchId IS STRING( 13 ); */ 

	/* EXEC SQL VAR hRefNum IS STRING( 13 ); */ 

	/* EXEC SQL VAR hResetDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hResetTime IS STRING( 7 ); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hBatchId, 0, sizeof( hBatchId ) );
	memset( hRefNum, 0, sizeof( hRefNum ) );
	memset( hResetDate, 0, sizeof( hResetDate ) );
	memset( hResetTime, 0, sizeof( hResetTime ) );
	
	strcpy( hAtmId, atmdenomstatus_ptr->AtmId );
	strcpy( hBatchId, atmdenomstatus_ptr->BatchId );
	strcpy( hRefNum, atmdenomstatus_ptr->RefNum );
	strcpy( hResetDate, atmdenomstatus_ptr->ResetDate );
	strcpy( hResetTime, atmdenomstatus_ptr->ResetTime );

	hDenom_A_Disp = hDenom_B_Disp = hDenom_C_Disp = hDenom_D_Disp = hDenom_E_Disp = hDenom_F_Disp = hDenom_G_Disp = hDenom_H_Disp = 0; 
		
	/* EXEC SQL SELECT 
		DENOM_A_NOTESDISP,
		DENOM_B_NOTESDISP,
		DENOM_C_NOTESDISP,
		DENOM_D_NOTESDISP,
		DENOM_E_NOTESDISP,
		DENOM_F_NOTESDISP,
		DENOM_G_NOTESDISP,
		DENOM_H_NOTESDISP
	INTO 
		:hDenom_A_Disp,
		:hDenom_B_Disp,
		:hDenom_C_Disp,
		:hDenom_D_Disp,
		:hDenom_E_Disp,
		:hDenom_F_Disp,
		:hDenom_G_Disp,
		:hDenom_H_Disp
	FROM EZATMDENOMSTATUS WHERE TRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select DENOM_A_NOTESDISP ,DENOM_B_NOTESDISP ,DENOM_C_NOTESDI\
SP ,DENOM_D_NOTESDISP ,DENOM_E_NOTESDISP ,DENOM_F_NOTESDISP ,DENOM_G_NOTESDISP\
 ,DENOM_H_NOTESDISP into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7  from EZATMDENOMSTATU\
S where trim(ATMID)=:b8";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1320;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&hDenom_A_Disp;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&hDenom_B_Disp;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&hDenom_C_Disp;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&hDenom_D_Disp;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&hDenom_E_Disp;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&hDenom_F_Disp;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&hDenom_G_Disp;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&hDenom_H_Disp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)hAtmId;
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


	
	hDenom_A_Disp += atmdenomstatus_ptr->Denom_A_Disp;
	hDenom_B_Disp += atmdenomstatus_ptr->Denom_B_Disp;
	hDenom_C_Disp += atmdenomstatus_ptr->Denom_C_Disp;
	hDenom_D_Disp += atmdenomstatus_ptr->Denom_D_Disp;
	hDenom_E_Disp += atmdenomstatus_ptr->Denom_E_Disp;
	hDenom_F_Disp += atmdenomstatus_ptr->Denom_F_Disp;
	hDenom_G_Disp += atmdenomstatus_ptr->Denom_G_Disp;
	hDenom_H_Disp += atmdenomstatus_ptr->Denom_H_Disp;
	
	/* EXEC SQL UPDATE EZATMDENOMSTATUS SET 
		DENOM_A_NOTESDISP=:hDenom_A_Disp,
		DENOM_B_NOTESDISP=:hDenom_B_Disp,
		DENOM_C_NOTESDISP=:hDenom_C_Disp,
		DENOM_D_NOTESDISP=:hDenom_D_Disp,
		DENOM_E_NOTESDISP=:hDenom_E_Disp,
		DENOM_F_NOTESDISP=:hDenom_F_Disp,
		DENOM_G_NOTESDISP=:hDenom_G_Disp,
		DENOM_H_NOTESDISP=:hDenom_H_Disp, 
		LASTRESETDATE=to_date( :hResetDate, 'dd-mm-yy' ),	
		LASTRESETTIME=:hResetTime	
	WHERE TRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMDENOMSTATUS  set DENOM_A_NOTESDISP=:b0,DENOM_B_N\
OTESDISP=:b1,DENOM_C_NOTESDISP=:b2,DENOM_D_NOTESDISP=:b3,DENOM_E_NOTESDISP=:b4\
,DENOM_F_NOTESDISP=:b5,DENOM_G_NOTESDISP=:b6,DENOM_H_NOTESDISP=:b7,LASTRESETDA\
TE=to_date(:b8,'dd-mm-yy'),LASTRESETTIME=:b9 where trim(ATMID)=:b10";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1371;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&hDenom_A_Disp;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&hDenom_B_Disp;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&hDenom_C_Disp;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&hDenom_D_Disp;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&hDenom_E_Disp;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&hDenom_F_Disp;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&hDenom_G_Disp;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&hDenom_H_Disp;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)hResetDate;
 sqlstm.sqhstl[8] = (unsigned int  )7;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)hResetTime;
 sqlstm.sqhstl[9] = (unsigned int  )7;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)hAtmId;
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
    	return ( sqlca.sqlcode );
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
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

 
		return ( sqlca.sqlcode );
	}	
}

int TruncateAtmLog()
{
	/* EXEC SQL TRUNCATE TABLE AtmLOG; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "truncate TABLE AtmLOG";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1445;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}

int TruncateAtmConnectionHist()
{
	/* EXEC SQL TRUNCATE TABLE AtmCONNECTIVITYHIST; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "truncate TABLE AtmCONNECTIVITYHIST";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1460;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}

int TruncateAtmStatusHist()
{
	/* EXEC SQL TRUNCATE TABLE EZATMSTATUSHIST; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "truncate TABLE EZATMSTATUSHIST";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1475;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}


int UpdateAtmTraceNo( struct AtmTraceNumMsg *devtraceno )
{	
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];  
		int	 hTraceNum;	 
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	
	strcpy( hAtmId, devtraceno->AtmId );
	hTraceNum = devtraceno->AtmTraceNo;
		
	/* EXEC SQL UPDATE EZATMDATAINFO SET 
		TRACENUM=:hTraceNum
	WHERE TRIM(ATMID)=:hAtmId ; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMDATAINFO  set TRACENUM=:b0 where trim(ATMID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1490;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&hTraceNum;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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


	if ( sqlca.sqlcode != 0 )
    	return ( sqlca.sqlcode );
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1513;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		return ( sqlca.sqlcode );
	} 	
}

int InsertAtmTraceNo( struct AtmTraceNumMsg *devtraceno )
{	
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];
		char hBatchId[ 13 ];  
		int	 hTraceNum;	 
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hBatchId IS STRING( 17 ); */ 

	
	memset( hAtmId, 0, sizeof( hAtmId ) );
	strcpy( hAtmId, devtraceno->AtmId );
	memset( hBatchId, 0, sizeof( hBatchId ) );
	strcpy( hBatchId, "123456789123" );
	
	hTraceNum = devtraceno->AtmTraceNo;
	
	/* EXEC SQL INSERT INTO EZATMDATAINFO
	( 
		ATMID, 
		TRACENUM,	
		BATCHID 
	)
	VALUES
	( 
		:hAtmId, 
		:hTraceNum,
		:hBatchId 
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZATMDATAINFO (ATMID,TRACENUM,BATCHID) values (:\
b0,:b1,:b2)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1528;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hAtmId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&hTraceNum;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hBatchId;
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
	else
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1555;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	   return ( sqlca.sqlcode );
	}
}


int updateTritonStatusLog( char *AtmId, struct TritonStatusMsg *StatusMsg )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char Input_AtmId[ 9 ];
		char hStatusDate[ 7 ];
		char hStatusTime[ 7 ];
	    char hPgmVersionNo[ 11 ];
	    char hTabVersionNo[ 11 ];
	    char hFirmVersionNo[ 11 ];
	    char hAlarmChestDoor;
	    char hAlarmTopDoor;
	    char hAlarmSupervisor;
	    char hRPPaper;
	    char hRPRibbon;
	    char hJPPaper;
	    char hJPRibbon;
	    char hDispNote;
	    char hRPStatus;
	    char hJPStatus;
	    char hDispStatus;
	    char hCommSystem;
	    char hCardReader;
	    char hCardsRetained[ 4 ];
	    char hErrCode[ 4 ];
	    char hCassADenom[ 4 ];
	    char hCassALoaded[ 5 ];
	    char hCassAMin[ 5 ];
	    char hCassADisp[ 5 ];
	    char hCassAReject[ 4 ];
	    char hCassANotes[ 5 ];
	    char hCassACash[ 13 ];
	    char hCassBDenom[ 4 ];
	    char hCassBLoaded[ 5 ];
	    char hCassBMin[ 5 ];
	    char hCassBDisp[ 5 ];
	    char hCassBReject[ 4 ];
	    char hCassBNotes[ 5 ];
	    char hCassBCash[ 13 ];
	    char hCassCDenom[ 4 ];
	    char hCassCLoaded[ 5 ];
	    char hCassCMin[ 5 ];
	    char hCassCDisp[ 5 ];
	    char hCassCReject[ 4 ];
	    char hCassCNotes[ 5 ];
	    char hCassCCash[ 13 ];
	    char hCassDDenom[ 4 ];
	    char hCassDLoaded[ 5 ];
	    char hCassDMin[ 5 ];
	    char hCassDDisp[ 5 ];
	    char hCassDReject[ 4 ];
		char hCassDNotes[ 5 ];
		char hCassDCash[ 13 ];
		char hTotCash[ 13 ];
	    char hTotNotesPurged[ 4 ];
	/* EXEC SQL END DECLARE SECTION; */ 
	
	
	/* EXEC SQL VAR Input_AtmId IS STRING(9); */ 

	/* EXEC SQL VAR hStatusDate IS STRING(7); */ 

	/* EXEC SQL VAR hStatusTime IS STRING(7); */ 

    /* EXEC SQL VAR hPgmVersionNo IS STRING(11); */ 

    /* EXEC SQL VAR hTabVersionNo IS STRING(11); */ 

    /* EXEC SQL VAR hFirmVersionNo IS STRING(11); */ 

    /* EXEC SQL VAR hCardsRetained IS STRING(4); */ 

    /* EXEC SQL VAR hErrCode IS STRING(4); */ 

    /* EXEC SQL VAR hCassADenom IS STRING(4); */ 

    /* EXEC SQL VAR hCassALoaded IS STRING(5); */ 

    /* EXEC SQL VAR hCassAMin IS STRING(5); */ 

    /* EXEC SQL VAR hCassADisp IS STRING(5); */ 

    /* EXEC SQL VAR hCassAReject IS STRING(4); */ 

    /* EXEC SQL VAR hCassANotes IS STRING(5); */ 

    /* EXEC SQL VAR hCassACash IS STRING(13); */ 

    /* EXEC SQL VAR hCassBDenom IS STRING(4); */ 

    /* EXEC SQL VAR hCassBLoaded IS STRING(5); */ 

    /* EXEC SQL VAR hCassBMin IS STRING(5); */ 

    /* EXEC SQL VAR hCassBDisp IS STRING(5); */ 

    /* EXEC SQL VAR hCassBReject IS STRING(4); */ 

    /* EXEC SQL VAR hCassBNotes IS STRING(5); */ 

    /* EXEC SQL VAR hCassBCash IS STRING(13); */ 

    /* EXEC SQL VAR hCassCDenom IS STRING(4); */ 

    /* EXEC SQL VAR hCassCLoaded IS STRING(5); */ 

    /* EXEC SQL VAR hCassCMin IS STRING(5); */ 

    /* EXEC SQL VAR hCassCDisp IS STRING(5); */ 

    /* EXEC SQL VAR hCassCReject IS STRING(4); */ 

    /* EXEC SQL VAR hCassCNotes IS STRING(5); */ 

    /* EXEC SQL VAR hCassCCash IS STRING(13); */ 

    /* EXEC SQL VAR hCassDDenom IS STRING(4); */ 

    /* EXEC SQL VAR hCassDLoaded IS STRING(5); */ 

    /* EXEC SQL VAR hCassDMin IS STRING(5); */ 

    /* EXEC SQL VAR hCassDDisp IS STRING(5); */ 

    /* EXEC SQL VAR hCassDReject IS STRING(4); */ 

	/* EXEC SQL VAR hCassDNotes IS STRING(5); */ 

	/* EXEC SQL VAR hCassDCash IS STRING(13); */ 

	/* EXEC SQL VAR hTotCash IS STRING(13); */ 

    /* EXEC SQL VAR hTotNotesPurged IS STRING(4); */ 



	memset( Input_AtmId, 0, sizeof( Input_AtmId ) );
	memset( hStatusDate, 0, sizeof( hStatusDate ) );
	memset( hStatusTime, 0, sizeof( hStatusTime ) );
    memset( hPgmVersionNo, 0, sizeof( hPgmVersionNo ) );
    memset( hTabVersionNo, 0, sizeof( hTabVersionNo ) );
    memset( hFirmVersionNo, 0, sizeof( hFirmVersionNo ) );
    memset( hCardsRetained, 0, sizeof( hCardsRetained ) );
    memset( hErrCode, 0, sizeof( hErrCode ) );
    memset( hCassADenom, 0, sizeof( hCassADenom ) );
    memset( hCassALoaded, 0, sizeof( hCassALoaded ) );
    memset( hCassAMin, 0, sizeof( hCassAMin ) );
    memset( hCassADisp, 0, sizeof( hCassADisp ) );
    memset( hCassAReject, 0, sizeof( hCassAReject ) );
    memset( hCassANotes, 0, sizeof( hCassANotes ) );
    memset( hCassACash, 0, sizeof( hCassACash ) );
    memset( hCassBDenom, 0, sizeof( hCassBDenom ) );
    memset( hCassBLoaded, 0, sizeof( hCassBLoaded ) );
    memset( hCassBMin, 0, sizeof( hCassBMin ) );
    memset( hCassBDisp, 0, sizeof( hCassBDisp ) );
    memset( hCassBReject, 0, sizeof( hCassBReject ) );
    memset( hCassBNotes, 0, sizeof( hCassBNotes ) );
    memset( hCassBCash, 0, sizeof( hCassBCash ) );
    memset( hCassCDenom, 0, sizeof( hCassCDenom ) );
    memset( hCassCLoaded, 0, sizeof( hCassCLoaded ) );
    memset( hCassCMin, 0, sizeof( hCassCMin ) );
    memset( hCassCDisp, 0, sizeof( hCassCDisp ) );
    memset( hCassCReject, 0, sizeof( hCassCReject ) );
    memset( hCassCNotes, 0, sizeof( hCassCNotes ) );
    memset( hCassCCash, 0, sizeof( hCassCCash ) );
    memset( hCassDDenom, 0, sizeof( hCassDDenom ) );
    memset( hCassDLoaded, 0, sizeof( hCassDLoaded ) );
    memset( hCassDMin, 0, sizeof( hCassDMin ) );
    memset( hCassDDisp, 0, sizeof( hCassDDisp ) );
    memset( hCassDReject, 0, sizeof( hCassDReject ) );
	memset( hCassDNotes, 0, sizeof( hCassDNotes ) );
	memset( hCassDCash, 0, sizeof( hCassDCash ) );
	memset( hTotCash, 0, sizeof( hTotCash ) );
    memset( hTotNotesPurged, 0, sizeof( hTotNotesPurged ) );
	
	strcpy( Input_AtmId, AtmId );
	strcpy( hStatusDate, StatusMsg->StatusDate );
	strcpy( hStatusTime, StatusMsg->StatusTime );
    strcpy( hPgmVersionNo, StatusMsg->PgmVersionNo );
    strcpy( hTabVersionNo, StatusMsg->TabVersionNo );
    strcpy( hFirmVersionNo, StatusMsg->FirmVersionNo );
    strcpy( hCardsRetained, StatusMsg->CardsRetained );
    strcpy( hErrCode, StatusMsg->ErrCode );
    strcpy( hCassADenom, StatusMsg->CassADenom );
    strcpy( hCassALoaded, StatusMsg->CassALoaded );
    strcpy( hCassAMin, StatusMsg->CassAMin );
    strcpy( hCassADisp, StatusMsg->CassADisp );
    strcpy( hCassAReject, StatusMsg->CassAReject );
    strcpy( hCassANotes, StatusMsg->CassANotes );
    strcpy( hCassACash, StatusMsg->CassACash );
    strcpy( hCassBDenom, StatusMsg->CassBDenom );
    strcpy( hCassBLoaded, StatusMsg->CassBLoaded );
    strcpy( hCassBMin, StatusMsg->CassBMin );
    strcpy( hCassBDisp, StatusMsg->CassBDisp );
    strcpy( hCassBReject, StatusMsg->CassBReject );
    strcpy( hCassBNotes, StatusMsg->CassBNotes );
    strcpy( hCassBCash, StatusMsg->CassBCash );
    strcpy( hCassCDenom, StatusMsg->CassCDenom );
    strcpy( hCassCLoaded, StatusMsg->CassCLoaded );
    strcpy( hCassCMin, StatusMsg->CassCMin );
    strcpy( hCassCDisp, StatusMsg->CassCDisp );
    strcpy( hCassCReject, StatusMsg->CassCReject );
    strcpy( hCassCNotes, StatusMsg->CassCNotes );
    strcpy( hCassCCash, StatusMsg->CassCCash );
    strcpy( hCassDDenom, StatusMsg->CassDDenom );
    strcpy( hCassDLoaded, StatusMsg->CassDLoaded );
    strcpy( hCassDMin, StatusMsg->CassDMin );
    strcpy( hCassDDisp, StatusMsg->CassDDisp );
    strcpy( hCassDReject, StatusMsg->CassDReject );
	strcpy( hCassDNotes, StatusMsg->CassDNotes );
	strcpy( hCassDCash, StatusMsg->CassDCash );
	strcpy( hTotCash, StatusMsg->TotCash );
    strcpy( hTotNotesPurged, StatusMsg->TotNotesPurged );
    hAlarmChestDoor = StatusMsg->AlarmChestDoor;
    hAlarmTopDoor = StatusMsg->AlarmTopDoor;
    hAlarmSupervisor = StatusMsg->AlarmTopDoor;
    hRPPaper = StatusMsg->RPPaper;
    hRPRibbon = StatusMsg->RPRibbon;
    hJPPaper = StatusMsg->JPPaper;
    hJPRibbon = StatusMsg->JPRibbon;
    hDispNote = StatusMsg->DispNote;
    hRPStatus = StatusMsg->RPStatus;
    hJPStatus = StatusMsg->JPStatus;
    hDispStatus = StatusMsg->DispStatus;
    hCommSystem = StatusMsg->CommSystem;
    hCardReader = StatusMsg->CardReader;
    
    
	/* EXEC SQL UPDATE TRITONSTATUSLOG SET 
	PGMVERSIONNO=:hPgmVersionNo, 
	TABVERSIONNO=:hTabVersionNo,
	FIRMVERSIONNO=:hFirmVersionNo, 
	ALARMCHESTDOOR=:hAlarmChestDoor,
	ALARMTOPDOOR=:hAlarmTopDoor,
	ALARMSUPERVISOR=:hAlarmSupervisor,
	RPPAPER=:hRPPaper, 
	RPRIBBON=:hRPRibbon,
	JPPAPER=:hJPPaper,
	JPRIBBON=:hJPRibbon,
	DISPNOTE=:hDispNote,
	RPSTATUS=:hRPStatus,
	JPSTATUS=:hJPStatus,
	DISPSTATUS=:hDispStatus,
	COMMSYSTEM=:hCommSystem,
	CARDREADER=:hCardReader,
	CARDSRETAINED=:hCardsRetained,
	ERRCODE=:hErrCode,
	CASSADENOM=:hCassADenom,
	CASSALOADED=:hCassALoaded,
	CASSAMIN=:hCassAMin,
	CASSADISP=:hCassADisp,
	CASSAREJECT=:hCassAReject, 
	CASSANOTES=:hCassANotes,
	CASSACASH=:hCassACash,	
	CASSBDENOM=:hCassBDenom,
	CASSBLOADED=:hCassBLoaded,
	CASSBMIN=:hCassBMin,
	CASSBDISP=:hCassBDisp, 
	CASSBREJECT=:hCassBReject,
	CASSBNOTES=:hCassBNotes,
	CASSBCASH=:hCassBCash,	
	CASSCDENOM=:hCassCDenom,
	CASSCLOADED=:hCassCLoaded,
	CASSCMIN=:hCassCMin,
	CASSCDISP=:hCassCDisp,
	CASSCREJECT=:hCassCReject,
	CASSCNOTES=:hCassCNotes,
	CASSCCASH=:hCassCCash,	
	CASSDDENOM=:hCassDDenom,
	CASSDLOADED=:hCassDLoaded,
	CASSDMIN=:hCassDMin,
	CASSDDISP=:hCassDDisp,
	CASSDREJECT=:hCassDReject,
	CASSDNOTES=:hCassDNotes,
	CASSDCASH=:hCassDCash,	
	TOTCASH=:hTotCash,	
	TOTNOTESPURGED=:hTotNotesPurged,
	LOGDATE=to_date( :hStatusDate, 'dd-mm-yy' ),
	LOGTIME=:hStatusTime
	WHERE RTRIM(AtmID)=:Input_AtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 51;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update TRITONSTATUSLOG  set PGMVERSIONNO=:b0,TABVERSIONNO=:b\
1,FIRMVERSIONNO=:b2,ALARMCHESTDOOR=:b3,ALARMTOPDOOR=:b4,ALARMSUPERVISOR=:b5,RP\
PAPER=:b6,RPRIBBON=:b7,JPPAPER=:b8,JPRIBBON=:b9,DISPNOTE=:b10,RPSTATUS=:b11,JP\
STATUS=:b12,DISPSTATUS=:b13,COMMSYSTEM=:b14,CARDREADER=:b15,CARDSRETAINED=:b16\
,ERRCODE=:b17,CASSADENOM=:b18,CASSALOADED=:b19,CASSAMIN=:b20,CASSADISP=:b21,CA\
SSAREJECT=:b22,CASSANOTES=:b23,CASSACASH=:b24,CASSBDENOM=:b25,CASSBLOADED=:b26\
,CASSBMIN=:b27,CASSBDISP=:b28,CASSBREJECT=:b29,CASSBNOTES=:b30,CASSBCASH=:b31,\
CASSCDENOM=:b32,CASSCLOADED=:b33,CASSCMIN=:b34,CASSCDISP=:b35,CASSCREJECT=:b36\
,CASSCNOTES=:b37,CASSCCASH=:b38,CASSDDENOM=:b39,CASSDLOADED=:b40,CASSDMIN=:b41\
,CASSDDISP=:b42,CASSDREJECT=:b43,CASSDNOTES=:b44,CASSDCASH=:b45,TOTCASH=:b46,T\
OTNOTESPURGED=:b47,LOGDATE=to_date(:b48,'dd-mm-yy'),LOGTIME=:b49 where RTRIM(A\
tmID)=:b50";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1570;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hPgmVersionNo;
 sqlstm.sqhstl[0] = (unsigned int  )11;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hTabVersionNo;
 sqlstm.sqhstl[1] = (unsigned int  )11;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hFirmVersionNo;
 sqlstm.sqhstl[2] = (unsigned int  )11;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&hAlarmChestDoor;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&hAlarmTopDoor;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&hAlarmSupervisor;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&hRPPaper;
 sqlstm.sqhstl[6] = (unsigned int  )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&hRPRibbon;
 sqlstm.sqhstl[7] = (unsigned int  )1;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&hJPPaper;
 sqlstm.sqhstl[8] = (unsigned int  )1;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&hJPRibbon;
 sqlstm.sqhstl[9] = (unsigned int  )1;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&hDispNote;
 sqlstm.sqhstl[10] = (unsigned int  )1;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&hRPStatus;
 sqlstm.sqhstl[11] = (unsigned int  )1;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&hJPStatus;
 sqlstm.sqhstl[12] = (unsigned int  )1;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&hDispStatus;
 sqlstm.sqhstl[13] = (unsigned int  )1;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&hCommSystem;
 sqlstm.sqhstl[14] = (unsigned int  )1;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&hCardReader;
 sqlstm.sqhstl[15] = (unsigned int  )1;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)hCardsRetained;
 sqlstm.sqhstl[16] = (unsigned int  )4;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)hErrCode;
 sqlstm.sqhstl[17] = (unsigned int  )4;
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)hCassADenom;
 sqlstm.sqhstl[18] = (unsigned int  )4;
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)hCassALoaded;
 sqlstm.sqhstl[19] = (unsigned int  )5;
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)hCassAMin;
 sqlstm.sqhstl[20] = (unsigned int  )5;
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)hCassADisp;
 sqlstm.sqhstl[21] = (unsigned int  )5;
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)hCassAReject;
 sqlstm.sqhstl[22] = (unsigned int  )4;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)hCassANotes;
 sqlstm.sqhstl[23] = (unsigned int  )5;
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)hCassACash;
 sqlstm.sqhstl[24] = (unsigned int  )13;
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)hCassBDenom;
 sqlstm.sqhstl[25] = (unsigned int  )4;
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)hCassBLoaded;
 sqlstm.sqhstl[26] = (unsigned int  )5;
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)hCassBMin;
 sqlstm.sqhstl[27] = (unsigned int  )5;
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)0;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)hCassBDisp;
 sqlstm.sqhstl[28] = (unsigned int  )5;
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)hCassBReject;
 sqlstm.sqhstl[29] = (unsigned int  )4;
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)0;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)hCassBNotes;
 sqlstm.sqhstl[30] = (unsigned int  )5;
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)0;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)hCassBCash;
 sqlstm.sqhstl[31] = (unsigned int  )13;
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)0;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)hCassCDenom;
 sqlstm.sqhstl[32] = (unsigned int  )4;
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)0;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)hCassCLoaded;
 sqlstm.sqhstl[33] = (unsigned int  )5;
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)hCassCMin;
 sqlstm.sqhstl[34] = (unsigned int  )5;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)hCassCDisp;
 sqlstm.sqhstl[35] = (unsigned int  )5;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)hCassCReject;
 sqlstm.sqhstl[36] = (unsigned int  )4;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)0;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)hCassCNotes;
 sqlstm.sqhstl[37] = (unsigned int  )5;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)0;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)hCassCCash;
 sqlstm.sqhstl[38] = (unsigned int  )13;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)0;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)hCassDDenom;
 sqlstm.sqhstl[39] = (unsigned int  )4;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)0;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)hCassDLoaded;
 sqlstm.sqhstl[40] = (unsigned int  )5;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)0;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)hCassDMin;
 sqlstm.sqhstl[41] = (unsigned int  )5;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)0;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)hCassDDisp;
 sqlstm.sqhstl[42] = (unsigned int  )5;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)0;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)hCassDReject;
 sqlstm.sqhstl[43] = (unsigned int  )4;
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)0;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)hCassDNotes;
 sqlstm.sqhstl[44] = (unsigned int  )5;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)0;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)hCassDCash;
 sqlstm.sqhstl[45] = (unsigned int  )13;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)0;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)hTotCash;
 sqlstm.sqhstl[46] = (unsigned int  )13;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)0;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)hTotNotesPurged;
 sqlstm.sqhstl[47] = (unsigned int  )4;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)0;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)hStatusDate;
 sqlstm.sqhstl[48] = (unsigned int  )7;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)0;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)hStatusTime;
 sqlstm.sqhstl[49] = (unsigned int  )7;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)0;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)Input_AtmId;
 sqlstm.sqhstl[50] = (unsigned int  )9;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)0;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
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


//	printf("sqlcode[%d]\n", sqlca.sqlcode );
//	printf("test1\n");
	if( sqlca.sqlcode == 1403 )
	{
		/* EXEC SQL INSERT INTO TRITONSTATUSLOG VALUES (
		:Input_AtmId, 
		:hPgmVersionNo, 
		:hTabVersionNo,
		:hFirmVersionNo,
		:hAlarmChestDoor,
		:hAlarmTopDoor,
		:hAlarmSupervisor,
		:hRPPaper, 
		:hRPRibbon,
		:hJPPaper,
		:hJPRibbon,
		:hDispNote,
		:hRPStatus,
		:hJPStatus,
		:hDispStatus,
		:hCommSystem,
		:hCardReader,
		:hCardsRetained,
		:hErrCode,
		:hCassADenom,
		:hCassALoaded,
		:hCassAMin,
		:hCassADisp,
		:hCassAReject,
		:hCassANotes,
		:hCassACash,
		:hCassBDenom,
		:hCassBLoaded,
		:hCassBMin,
		:hCassBDisp,
		:hCassBReject,
		:hCassBNotes,
		:hCassBCash,
		:hCassCDenom,
		:hCassCLoaded,
		:hCassCMin,
		:hCassCDisp,
		:hCassCReject,
		:hCassCNotes,
		:hCassCCash,
		:hCassDDenom,
		:hCassDLoaded,
		:hCassDMin,
		:hCassDDisp,
		:hCassDReject,
		:hCassDNotes,
		:hCassDCash,
		:hTotCash,
		:hTotNotesPurged,
		to_date( :hStatusDate, 'dd-mm-yy' ),
		:hStatusTime
 		); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 51;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "insert into TRITONSTATUSLOG  values (:b0,:b1,:b2,:b3,:b4,:b\
5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21,\
:b22,:b23,:b24,:b25,:b26,:b27,:b28,:b29,:b30,:b31,:b32,:b33,:b34,:b35,:b36,:b3\
7,:b38,:b39,:b40,:b41,:b42,:b43,:b44,:b45,:b46,:b47,:b48,to_date(:b49,'dd-mm-y\
y'),:b50)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1789;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)Input_AtmId;
  sqlstm.sqhstl[0] = (unsigned int  )9;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)hPgmVersionNo;
  sqlstm.sqhstl[1] = (unsigned int  )11;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)hTabVersionNo;
  sqlstm.sqhstl[2] = (unsigned int  )11;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)hFirmVersionNo;
  sqlstm.sqhstl[3] = (unsigned int  )11;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)&hAlarmChestDoor;
  sqlstm.sqhstl[4] = (unsigned int  )1;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&hAlarmTopDoor;
  sqlstm.sqhstl[5] = (unsigned int  )1;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&hAlarmSupervisor;
  sqlstm.sqhstl[6] = (unsigned int  )1;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)&hRPPaper;
  sqlstm.sqhstl[7] = (unsigned int  )1;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         void  *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned int  )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (         void  *)&hRPRibbon;
  sqlstm.sqhstl[8] = (unsigned int  )1;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         void  *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned int  )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (         void  *)&hJPPaper;
  sqlstm.sqhstl[9] = (unsigned int  )1;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         void  *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned int  )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (         void  *)&hJPRibbon;
  sqlstm.sqhstl[10] = (unsigned int  )1;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         void  *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned int  )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (         void  *)&hDispNote;
  sqlstm.sqhstl[11] = (unsigned int  )1;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         void  *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned int  )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (         void  *)&hRPStatus;
  sqlstm.sqhstl[12] = (unsigned int  )1;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         void  *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned int  )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (         void  *)&hJPStatus;
  sqlstm.sqhstl[13] = (unsigned int  )1;
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         void  *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned int  )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (         void  *)&hDispStatus;
  sqlstm.sqhstl[14] = (unsigned int  )1;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         void  *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned int  )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (         void  *)&hCommSystem;
  sqlstm.sqhstl[15] = (unsigned int  )1;
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         void  *)0;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned int  )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (         void  *)&hCardReader;
  sqlstm.sqhstl[16] = (unsigned int  )1;
  sqlstm.sqhsts[16] = (         int  )0;
  sqlstm.sqindv[16] = (         void  *)0;
  sqlstm.sqinds[16] = (         int  )0;
  sqlstm.sqharm[16] = (unsigned int  )0;
  sqlstm.sqadto[16] = (unsigned short )0;
  sqlstm.sqtdso[16] = (unsigned short )0;
  sqlstm.sqhstv[17] = (         void  *)hCardsRetained;
  sqlstm.sqhstl[17] = (unsigned int  )4;
  sqlstm.sqhsts[17] = (         int  )0;
  sqlstm.sqindv[17] = (         void  *)0;
  sqlstm.sqinds[17] = (         int  )0;
  sqlstm.sqharm[17] = (unsigned int  )0;
  sqlstm.sqadto[17] = (unsigned short )0;
  sqlstm.sqtdso[17] = (unsigned short )0;
  sqlstm.sqhstv[18] = (         void  *)hErrCode;
  sqlstm.sqhstl[18] = (unsigned int  )4;
  sqlstm.sqhsts[18] = (         int  )0;
  sqlstm.sqindv[18] = (         void  *)0;
  sqlstm.sqinds[18] = (         int  )0;
  sqlstm.sqharm[18] = (unsigned int  )0;
  sqlstm.sqadto[18] = (unsigned short )0;
  sqlstm.sqtdso[18] = (unsigned short )0;
  sqlstm.sqhstv[19] = (         void  *)hCassADenom;
  sqlstm.sqhstl[19] = (unsigned int  )4;
  sqlstm.sqhsts[19] = (         int  )0;
  sqlstm.sqindv[19] = (         void  *)0;
  sqlstm.sqinds[19] = (         int  )0;
  sqlstm.sqharm[19] = (unsigned int  )0;
  sqlstm.sqadto[19] = (unsigned short )0;
  sqlstm.sqtdso[19] = (unsigned short )0;
  sqlstm.sqhstv[20] = (         void  *)hCassALoaded;
  sqlstm.sqhstl[20] = (unsigned int  )5;
  sqlstm.sqhsts[20] = (         int  )0;
  sqlstm.sqindv[20] = (         void  *)0;
  sqlstm.sqinds[20] = (         int  )0;
  sqlstm.sqharm[20] = (unsigned int  )0;
  sqlstm.sqadto[20] = (unsigned short )0;
  sqlstm.sqtdso[20] = (unsigned short )0;
  sqlstm.sqhstv[21] = (         void  *)hCassAMin;
  sqlstm.sqhstl[21] = (unsigned int  )5;
  sqlstm.sqhsts[21] = (         int  )0;
  sqlstm.sqindv[21] = (         void  *)0;
  sqlstm.sqinds[21] = (         int  )0;
  sqlstm.sqharm[21] = (unsigned int  )0;
  sqlstm.sqadto[21] = (unsigned short )0;
  sqlstm.sqtdso[21] = (unsigned short )0;
  sqlstm.sqhstv[22] = (         void  *)hCassADisp;
  sqlstm.sqhstl[22] = (unsigned int  )5;
  sqlstm.sqhsts[22] = (         int  )0;
  sqlstm.sqindv[22] = (         void  *)0;
  sqlstm.sqinds[22] = (         int  )0;
  sqlstm.sqharm[22] = (unsigned int  )0;
  sqlstm.sqadto[22] = (unsigned short )0;
  sqlstm.sqtdso[22] = (unsigned short )0;
  sqlstm.sqhstv[23] = (         void  *)hCassAReject;
  sqlstm.sqhstl[23] = (unsigned int  )4;
  sqlstm.sqhsts[23] = (         int  )0;
  sqlstm.sqindv[23] = (         void  *)0;
  sqlstm.sqinds[23] = (         int  )0;
  sqlstm.sqharm[23] = (unsigned int  )0;
  sqlstm.sqadto[23] = (unsigned short )0;
  sqlstm.sqtdso[23] = (unsigned short )0;
  sqlstm.sqhstv[24] = (         void  *)hCassANotes;
  sqlstm.sqhstl[24] = (unsigned int  )5;
  sqlstm.sqhsts[24] = (         int  )0;
  sqlstm.sqindv[24] = (         void  *)0;
  sqlstm.sqinds[24] = (         int  )0;
  sqlstm.sqharm[24] = (unsigned int  )0;
  sqlstm.sqadto[24] = (unsigned short )0;
  sqlstm.sqtdso[24] = (unsigned short )0;
  sqlstm.sqhstv[25] = (         void  *)hCassACash;
  sqlstm.sqhstl[25] = (unsigned int  )13;
  sqlstm.sqhsts[25] = (         int  )0;
  sqlstm.sqindv[25] = (         void  *)0;
  sqlstm.sqinds[25] = (         int  )0;
  sqlstm.sqharm[25] = (unsigned int  )0;
  sqlstm.sqadto[25] = (unsigned short )0;
  sqlstm.sqtdso[25] = (unsigned short )0;
  sqlstm.sqhstv[26] = (         void  *)hCassBDenom;
  sqlstm.sqhstl[26] = (unsigned int  )4;
  sqlstm.sqhsts[26] = (         int  )0;
  sqlstm.sqindv[26] = (         void  *)0;
  sqlstm.sqinds[26] = (         int  )0;
  sqlstm.sqharm[26] = (unsigned int  )0;
  sqlstm.sqadto[26] = (unsigned short )0;
  sqlstm.sqtdso[26] = (unsigned short )0;
  sqlstm.sqhstv[27] = (         void  *)hCassBLoaded;
  sqlstm.sqhstl[27] = (unsigned int  )5;
  sqlstm.sqhsts[27] = (         int  )0;
  sqlstm.sqindv[27] = (         void  *)0;
  sqlstm.sqinds[27] = (         int  )0;
  sqlstm.sqharm[27] = (unsigned int  )0;
  sqlstm.sqadto[27] = (unsigned short )0;
  sqlstm.sqtdso[27] = (unsigned short )0;
  sqlstm.sqhstv[28] = (         void  *)hCassBMin;
  sqlstm.sqhstl[28] = (unsigned int  )5;
  sqlstm.sqhsts[28] = (         int  )0;
  sqlstm.sqindv[28] = (         void  *)0;
  sqlstm.sqinds[28] = (         int  )0;
  sqlstm.sqharm[28] = (unsigned int  )0;
  sqlstm.sqadto[28] = (unsigned short )0;
  sqlstm.sqtdso[28] = (unsigned short )0;
  sqlstm.sqhstv[29] = (         void  *)hCassBDisp;
  sqlstm.sqhstl[29] = (unsigned int  )5;
  sqlstm.sqhsts[29] = (         int  )0;
  sqlstm.sqindv[29] = (         void  *)0;
  sqlstm.sqinds[29] = (         int  )0;
  sqlstm.sqharm[29] = (unsigned int  )0;
  sqlstm.sqadto[29] = (unsigned short )0;
  sqlstm.sqtdso[29] = (unsigned short )0;
  sqlstm.sqhstv[30] = (         void  *)hCassBReject;
  sqlstm.sqhstl[30] = (unsigned int  )4;
  sqlstm.sqhsts[30] = (         int  )0;
  sqlstm.sqindv[30] = (         void  *)0;
  sqlstm.sqinds[30] = (         int  )0;
  sqlstm.sqharm[30] = (unsigned int  )0;
  sqlstm.sqadto[30] = (unsigned short )0;
  sqlstm.sqtdso[30] = (unsigned short )0;
  sqlstm.sqhstv[31] = (         void  *)hCassBNotes;
  sqlstm.sqhstl[31] = (unsigned int  )5;
  sqlstm.sqhsts[31] = (         int  )0;
  sqlstm.sqindv[31] = (         void  *)0;
  sqlstm.sqinds[31] = (         int  )0;
  sqlstm.sqharm[31] = (unsigned int  )0;
  sqlstm.sqadto[31] = (unsigned short )0;
  sqlstm.sqtdso[31] = (unsigned short )0;
  sqlstm.sqhstv[32] = (         void  *)hCassBCash;
  sqlstm.sqhstl[32] = (unsigned int  )13;
  sqlstm.sqhsts[32] = (         int  )0;
  sqlstm.sqindv[32] = (         void  *)0;
  sqlstm.sqinds[32] = (         int  )0;
  sqlstm.sqharm[32] = (unsigned int  )0;
  sqlstm.sqadto[32] = (unsigned short )0;
  sqlstm.sqtdso[32] = (unsigned short )0;
  sqlstm.sqhstv[33] = (         void  *)hCassCDenom;
  sqlstm.sqhstl[33] = (unsigned int  )4;
  sqlstm.sqhsts[33] = (         int  )0;
  sqlstm.sqindv[33] = (         void  *)0;
  sqlstm.sqinds[33] = (         int  )0;
  sqlstm.sqharm[33] = (unsigned int  )0;
  sqlstm.sqadto[33] = (unsigned short )0;
  sqlstm.sqtdso[33] = (unsigned short )0;
  sqlstm.sqhstv[34] = (         void  *)hCassCLoaded;
  sqlstm.sqhstl[34] = (unsigned int  )5;
  sqlstm.sqhsts[34] = (         int  )0;
  sqlstm.sqindv[34] = (         void  *)0;
  sqlstm.sqinds[34] = (         int  )0;
  sqlstm.sqharm[34] = (unsigned int  )0;
  sqlstm.sqadto[34] = (unsigned short )0;
  sqlstm.sqtdso[34] = (unsigned short )0;
  sqlstm.sqhstv[35] = (         void  *)hCassCMin;
  sqlstm.sqhstl[35] = (unsigned int  )5;
  sqlstm.sqhsts[35] = (         int  )0;
  sqlstm.sqindv[35] = (         void  *)0;
  sqlstm.sqinds[35] = (         int  )0;
  sqlstm.sqharm[35] = (unsigned int  )0;
  sqlstm.sqadto[35] = (unsigned short )0;
  sqlstm.sqtdso[35] = (unsigned short )0;
  sqlstm.sqhstv[36] = (         void  *)hCassCDisp;
  sqlstm.sqhstl[36] = (unsigned int  )5;
  sqlstm.sqhsts[36] = (         int  )0;
  sqlstm.sqindv[36] = (         void  *)0;
  sqlstm.sqinds[36] = (         int  )0;
  sqlstm.sqharm[36] = (unsigned int  )0;
  sqlstm.sqadto[36] = (unsigned short )0;
  sqlstm.sqtdso[36] = (unsigned short )0;
  sqlstm.sqhstv[37] = (         void  *)hCassCReject;
  sqlstm.sqhstl[37] = (unsigned int  )4;
  sqlstm.sqhsts[37] = (         int  )0;
  sqlstm.sqindv[37] = (         void  *)0;
  sqlstm.sqinds[37] = (         int  )0;
  sqlstm.sqharm[37] = (unsigned int  )0;
  sqlstm.sqadto[37] = (unsigned short )0;
  sqlstm.sqtdso[37] = (unsigned short )0;
  sqlstm.sqhstv[38] = (         void  *)hCassCNotes;
  sqlstm.sqhstl[38] = (unsigned int  )5;
  sqlstm.sqhsts[38] = (         int  )0;
  sqlstm.sqindv[38] = (         void  *)0;
  sqlstm.sqinds[38] = (         int  )0;
  sqlstm.sqharm[38] = (unsigned int  )0;
  sqlstm.sqadto[38] = (unsigned short )0;
  sqlstm.sqtdso[38] = (unsigned short )0;
  sqlstm.sqhstv[39] = (         void  *)hCassCCash;
  sqlstm.sqhstl[39] = (unsigned int  )13;
  sqlstm.sqhsts[39] = (         int  )0;
  sqlstm.sqindv[39] = (         void  *)0;
  sqlstm.sqinds[39] = (         int  )0;
  sqlstm.sqharm[39] = (unsigned int  )0;
  sqlstm.sqadto[39] = (unsigned short )0;
  sqlstm.sqtdso[39] = (unsigned short )0;
  sqlstm.sqhstv[40] = (         void  *)hCassDDenom;
  sqlstm.sqhstl[40] = (unsigned int  )4;
  sqlstm.sqhsts[40] = (         int  )0;
  sqlstm.sqindv[40] = (         void  *)0;
  sqlstm.sqinds[40] = (         int  )0;
  sqlstm.sqharm[40] = (unsigned int  )0;
  sqlstm.sqadto[40] = (unsigned short )0;
  sqlstm.sqtdso[40] = (unsigned short )0;
  sqlstm.sqhstv[41] = (         void  *)hCassDLoaded;
  sqlstm.sqhstl[41] = (unsigned int  )5;
  sqlstm.sqhsts[41] = (         int  )0;
  sqlstm.sqindv[41] = (         void  *)0;
  sqlstm.sqinds[41] = (         int  )0;
  sqlstm.sqharm[41] = (unsigned int  )0;
  sqlstm.sqadto[41] = (unsigned short )0;
  sqlstm.sqtdso[41] = (unsigned short )0;
  sqlstm.sqhstv[42] = (         void  *)hCassDMin;
  sqlstm.sqhstl[42] = (unsigned int  )5;
  sqlstm.sqhsts[42] = (         int  )0;
  sqlstm.sqindv[42] = (         void  *)0;
  sqlstm.sqinds[42] = (         int  )0;
  sqlstm.sqharm[42] = (unsigned int  )0;
  sqlstm.sqadto[42] = (unsigned short )0;
  sqlstm.sqtdso[42] = (unsigned short )0;
  sqlstm.sqhstv[43] = (         void  *)hCassDDisp;
  sqlstm.sqhstl[43] = (unsigned int  )5;
  sqlstm.sqhsts[43] = (         int  )0;
  sqlstm.sqindv[43] = (         void  *)0;
  sqlstm.sqinds[43] = (         int  )0;
  sqlstm.sqharm[43] = (unsigned int  )0;
  sqlstm.sqadto[43] = (unsigned short )0;
  sqlstm.sqtdso[43] = (unsigned short )0;
  sqlstm.sqhstv[44] = (         void  *)hCassDReject;
  sqlstm.sqhstl[44] = (unsigned int  )4;
  sqlstm.sqhsts[44] = (         int  )0;
  sqlstm.sqindv[44] = (         void  *)0;
  sqlstm.sqinds[44] = (         int  )0;
  sqlstm.sqharm[44] = (unsigned int  )0;
  sqlstm.sqadto[44] = (unsigned short )0;
  sqlstm.sqtdso[44] = (unsigned short )0;
  sqlstm.sqhstv[45] = (         void  *)hCassDNotes;
  sqlstm.sqhstl[45] = (unsigned int  )5;
  sqlstm.sqhsts[45] = (         int  )0;
  sqlstm.sqindv[45] = (         void  *)0;
  sqlstm.sqinds[45] = (         int  )0;
  sqlstm.sqharm[45] = (unsigned int  )0;
  sqlstm.sqadto[45] = (unsigned short )0;
  sqlstm.sqtdso[45] = (unsigned short )0;
  sqlstm.sqhstv[46] = (         void  *)hCassDCash;
  sqlstm.sqhstl[46] = (unsigned int  )13;
  sqlstm.sqhsts[46] = (         int  )0;
  sqlstm.sqindv[46] = (         void  *)0;
  sqlstm.sqinds[46] = (         int  )0;
  sqlstm.sqharm[46] = (unsigned int  )0;
  sqlstm.sqadto[46] = (unsigned short )0;
  sqlstm.sqtdso[46] = (unsigned short )0;
  sqlstm.sqhstv[47] = (         void  *)hTotCash;
  sqlstm.sqhstl[47] = (unsigned int  )13;
  sqlstm.sqhsts[47] = (         int  )0;
  sqlstm.sqindv[47] = (         void  *)0;
  sqlstm.sqinds[47] = (         int  )0;
  sqlstm.sqharm[47] = (unsigned int  )0;
  sqlstm.sqadto[47] = (unsigned short )0;
  sqlstm.sqtdso[47] = (unsigned short )0;
  sqlstm.sqhstv[48] = (         void  *)hTotNotesPurged;
  sqlstm.sqhstl[48] = (unsigned int  )4;
  sqlstm.sqhsts[48] = (         int  )0;
  sqlstm.sqindv[48] = (         void  *)0;
  sqlstm.sqinds[48] = (         int  )0;
  sqlstm.sqharm[48] = (unsigned int  )0;
  sqlstm.sqadto[48] = (unsigned short )0;
  sqlstm.sqtdso[48] = (unsigned short )0;
  sqlstm.sqhstv[49] = (         void  *)hStatusDate;
  sqlstm.sqhstl[49] = (unsigned int  )7;
  sqlstm.sqhsts[49] = (         int  )0;
  sqlstm.sqindv[49] = (         void  *)0;
  sqlstm.sqinds[49] = (         int  )0;
  sqlstm.sqharm[49] = (unsigned int  )0;
  sqlstm.sqadto[49] = (unsigned short )0;
  sqlstm.sqtdso[49] = (unsigned short )0;
  sqlstm.sqhstv[50] = (         void  *)hStatusTime;
  sqlstm.sqhstl[50] = (unsigned int  )7;
  sqlstm.sqhsts[50] = (         int  )0;
  sqlstm.sqindv[50] = (         void  *)0;
  sqlstm.sqinds[50] = (         int  )0;
  sqlstm.sqharm[50] = (unsigned int  )0;
  sqlstm.sqadto[50] = (unsigned short )0;
  sqlstm.sqtdso[50] = (unsigned short )0;
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
			/* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 51;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )2008;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	}
	else
	{
		if( sqlca.sqlcode == 0 )
			/* EXEC SQL COMMIT; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 12;
   sqlstm.arrsiz = 51;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )2023;
   sqlstm.cud = sqlcud0;
   sqlstm.sqlest = (unsigned char  *)&sqlca;
   sqlstm.sqlety = (unsigned short)4352;
   sqlstm.occurs = (unsigned int  )0;
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	}
	return sqlca.sqlcode;
}

int LoadAtmEjDetails( const char *AtmId, struct ATMEjBuffer *atmej_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hInstId[ INST_SIZE + 1 ];
		char hAtmId[ ATM_ID_SIZE + 1 ];
		char hAtmTypeId[ ATM_ID_SIZE + 1 ];
		char hAtmLogicalGroup[ ATM_ID_SIZE + 1 ];
		char hAtmStatus;
		char hAtmEjPortName[ ATM_ID_SIZE + 1 ];
		char hCurrentFile[ 26 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR hInstId IS STRING(12); */ 

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hAtmTypeId IS STRING(17); */ 

	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmEjPortName IS STRING(17); */ 

	/* EXEC SQL VAR hCurrentFile IS STRING(26); */ 

	
	memset( hInstId, 0, sizeof( hInstId ) );
	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hAtmTypeId, 0, sizeof( hAtmTypeId ) );
	memset( hAtmLogicalGroup, 0, sizeof( hAtmLogicalGroup ) );
	memset( hAtmEjPortName, 0, sizeof( hAtmEjPortName ) );
	memset( hCurrentFile, 0, sizeof( hCurrentFile ) );
	
	strcpy( hAtmId, AtmId );
		
		
	/* EXEC SQL SELECT
			RTRIM(INSTID),
			RTRIM(ATMTYPEID),
			RTRIM(LOGICALGROUP),
			ATMSTATUS,
			RTRIM(EJPORTNAME),
			RTRIM(LASTFILENAME)
	INTO
			:hInstId,
			:hAtmTypeId,
			:hAtmLogicalGroup,
			:hAtmStatus,
			:hAtmEjPortName,
			:hCurrentFile
	FROM EZATMEJINFO WHERE RTRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 51;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(ATMTYPEID) ,RTRIM(LOGICALGROUP) \
,ATMSTATUS ,RTRIM(EJPORTNAME) ,RTRIM(LASTFILENAME) into :b0,:b1,:b2,:b3,:b4,:b\
5  from EZATMEJINFO where RTRIM(ATMID)=:b6";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2038;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hInstId;
 sqlstm.sqhstl[0] = (unsigned int  )12;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hAtmTypeId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)hAtmLogicalGroup;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&hAtmStatus;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)hAtmEjPortName;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)hCurrentFile;
 sqlstm.sqhstl[5] = (unsigned int  )26;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)hAtmId;
 sqlstm.sqhstl[6] = (unsigned int  )17;
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

		
	
	
	if ( sqlca.sqlcode < 0 )
    {
		return sqlca.sqlcode;
    }
    else
    {
    	memset( atmej_ptr, 0, sizeof( struct ATMEjBuffer ) );
       	strcpy( atmej_ptr->InstId, hInstId );
    	strcpy( atmej_ptr->AtmId, hAtmId );
		strcpy( atmej_ptr->AtmTypeId, hAtmTypeId );
		strcpy( atmej_ptr->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( atmej_ptr->AtmEjPortName, hAtmEjPortName );
		atmej_ptr->AtmStatus = hAtmStatus;
		strcpy( atmej_ptr->CurrentFile, hCurrentFile );
		return sqlca.sqlcode;
    }
}


int ReadAtmPropertyTable( struct EzAtmProperty *ezatmproperty_ptr, int RecordId )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int	 hRecordId;
		char hInstTerminalGroup[ 17 ];
		char hAtmLogicalGroup[ 17 ];
		char hAtmId[ 17 ];
		char hDownloadCheckReq;
		char hFingerPrintCheckReq;
		char hFingerPrintCheckChannel[ 33 ];
		char hJournalPrinterReq;
		char hPassbookPrinterReq;
		char hStatementPrinterReq;
		char hPartialReversalReq;
		char hCardReaderModel;
		char hTxnCode[ 7 ];
		char hRespCode[ 4 ];
		char hDecimalPointCheckReq;
		int  hCurrencyCode;
		char hDecimalMultiplier;
 		int  hCounterRefresh;
 		int  hKeyRefresh;
 	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR hInstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hFingerPrintCheckChannel IS STRING(33); */ 

	/* EXEC SQL VAR hTxnCode IS STRING(7); */ 

	/* EXEC SQL VAR hRespCode IS STRING(4); */ 

	
	hRecordId = RecordId;
		
    /* EXEC SQL SELECT 
    	RTRIM(INSTTERMINALGROUP),
		RTRIM(ATMLOGICALGROUP),
		RTRIM(ATMID),
		RTRIM(TXNCODE),
		RESPCODE,
		DOWNLOADCHECKREQ,
		FINGERPRINTCHECKREQ,
		RTRIM(FINGERPRINTCHECKCHANNEL),
		JOURNALPRINTERREQ,
		PASSBOOKPRINTERREQ,
		STATEMENTPRINTERREQ,
		PARTIALREVERSALREQ,
		CARDREADERMODEL,
		DECIMALPOINTCHECKREQ,
		CURRENCYCODE,
		DECIMALMULTIPLIER,
		COUNTERREFERSH,
		KEYREFERSH
	INTO
		:hInstTerminalGroup,
		:hAtmLogicalGroup,
		:hAtmId,
		:hTxnCode,
		:hRespCode,
		:hDownloadCheckReq,
		:hFingerPrintCheckReq,
		:hFingerPrintCheckChannel,
		:hJournalPrinterReq,
		:hPassbookPrinterReq,
		:hStatementPrinterReq,
		:hPartialReversalReq,
		:hCardReaderModel,
		:hDecimalPointCheckReq,
		:hCurrencyCode,
		:hDecimalMultiplier,
		:hCounterRefresh,
		:hKeyRefresh
	FROM EZATMPROPERTY WHERE RECORDID=:hRecordId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 51;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(INSTTERMINALGROUP) ,RTRIM(ATMLOGICALGROUP) ,\
RTRIM(ATMID) ,RTRIM(TXNCODE) ,RESPCODE ,DOWNLOADCHECKREQ ,FINGERPRINTCHECKREQ \
,RTRIM(FINGERPRINTCHECKCHANNEL) ,JOURNALPRINTERREQ ,PASSBOOKPRINTERREQ ,STATEM\
ENTPRINTERREQ ,PARTIALREVERSALREQ ,CARDREADERMODEL ,DECIMALPOINTCHECKREQ ,CURR\
ENCYCODE ,DECIMALMULTIPLIER ,COUNTERREFERSH ,KEYREFERSH into :b0,:b1,:b2,:b3,:\
b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,:b16,:b17  from EZATMPROP\
ERTY where RECORDID=:b18";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )2081;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)hInstTerminalGroup;
    sqlstm.sqhstl[0] = (unsigned int  )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)hAtmLogicalGroup;
    sqlstm.sqhstl[1] = (unsigned int  )17;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void  *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)hAtmId;
    sqlstm.sqhstl[2] = (unsigned int  )17;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void  *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void  *)hTxnCode;
    sqlstm.sqhstl[3] = (unsigned int  )7;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void  *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void  *)hRespCode;
    sqlstm.sqhstl[4] = (unsigned int  )4;
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         void  *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (         void  *)&hDownloadCheckReq;
    sqlstm.sqhstl[5] = (unsigned int  )1;
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         void  *)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned int  )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqhstv[6] = (         void  *)&hFingerPrintCheckReq;
    sqlstm.sqhstl[6] = (unsigned int  )1;
    sqlstm.sqhsts[6] = (         int  )0;
    sqlstm.sqindv[6] = (         void  *)0;
    sqlstm.sqinds[6] = (         int  )0;
    sqlstm.sqharm[6] = (unsigned int  )0;
    sqlstm.sqadto[6] = (unsigned short )0;
    sqlstm.sqtdso[6] = (unsigned short )0;
    sqlstm.sqhstv[7] = (         void  *)hFingerPrintCheckChannel;
    sqlstm.sqhstl[7] = (unsigned int  )33;
    sqlstm.sqhsts[7] = (         int  )0;
    sqlstm.sqindv[7] = (         void  *)0;
    sqlstm.sqinds[7] = (         int  )0;
    sqlstm.sqharm[7] = (unsigned int  )0;
    sqlstm.sqadto[7] = (unsigned short )0;
    sqlstm.sqtdso[7] = (unsigned short )0;
    sqlstm.sqhstv[8] = (         void  *)&hJournalPrinterReq;
    sqlstm.sqhstl[8] = (unsigned int  )1;
    sqlstm.sqhsts[8] = (         int  )0;
    sqlstm.sqindv[8] = (         void  *)0;
    sqlstm.sqinds[8] = (         int  )0;
    sqlstm.sqharm[8] = (unsigned int  )0;
    sqlstm.sqadto[8] = (unsigned short )0;
    sqlstm.sqtdso[8] = (unsigned short )0;
    sqlstm.sqhstv[9] = (         void  *)&hPassbookPrinterReq;
    sqlstm.sqhstl[9] = (unsigned int  )1;
    sqlstm.sqhsts[9] = (         int  )0;
    sqlstm.sqindv[9] = (         void  *)0;
    sqlstm.sqinds[9] = (         int  )0;
    sqlstm.sqharm[9] = (unsigned int  )0;
    sqlstm.sqadto[9] = (unsigned short )0;
    sqlstm.sqtdso[9] = (unsigned short )0;
    sqlstm.sqhstv[10] = (         void  *)&hStatementPrinterReq;
    sqlstm.sqhstl[10] = (unsigned int  )1;
    sqlstm.sqhsts[10] = (         int  )0;
    sqlstm.sqindv[10] = (         void  *)0;
    sqlstm.sqinds[10] = (         int  )0;
    sqlstm.sqharm[10] = (unsigned int  )0;
    sqlstm.sqadto[10] = (unsigned short )0;
    sqlstm.sqtdso[10] = (unsigned short )0;
    sqlstm.sqhstv[11] = (         void  *)&hPartialReversalReq;
    sqlstm.sqhstl[11] = (unsigned int  )1;
    sqlstm.sqhsts[11] = (         int  )0;
    sqlstm.sqindv[11] = (         void  *)0;
    sqlstm.sqinds[11] = (         int  )0;
    sqlstm.sqharm[11] = (unsigned int  )0;
    sqlstm.sqadto[11] = (unsigned short )0;
    sqlstm.sqtdso[11] = (unsigned short )0;
    sqlstm.sqhstv[12] = (         void  *)&hCardReaderModel;
    sqlstm.sqhstl[12] = (unsigned int  )1;
    sqlstm.sqhsts[12] = (         int  )0;
    sqlstm.sqindv[12] = (         void  *)0;
    sqlstm.sqinds[12] = (         int  )0;
    sqlstm.sqharm[12] = (unsigned int  )0;
    sqlstm.sqadto[12] = (unsigned short )0;
    sqlstm.sqtdso[12] = (unsigned short )0;
    sqlstm.sqhstv[13] = (         void  *)&hDecimalPointCheckReq;
    sqlstm.sqhstl[13] = (unsigned int  )1;
    sqlstm.sqhsts[13] = (         int  )0;
    sqlstm.sqindv[13] = (         void  *)0;
    sqlstm.sqinds[13] = (         int  )0;
    sqlstm.sqharm[13] = (unsigned int  )0;
    sqlstm.sqadto[13] = (unsigned short )0;
    sqlstm.sqtdso[13] = (unsigned short )0;
    sqlstm.sqhstv[14] = (         void  *)&hCurrencyCode;
    sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[14] = (         int  )0;
    sqlstm.sqindv[14] = (         void  *)0;
    sqlstm.sqinds[14] = (         int  )0;
    sqlstm.sqharm[14] = (unsigned int  )0;
    sqlstm.sqadto[14] = (unsigned short )0;
    sqlstm.sqtdso[14] = (unsigned short )0;
    sqlstm.sqhstv[15] = (         void  *)&hDecimalMultiplier;
    sqlstm.sqhstl[15] = (unsigned int  )1;
    sqlstm.sqhsts[15] = (         int  )0;
    sqlstm.sqindv[15] = (         void  *)0;
    sqlstm.sqinds[15] = (         int  )0;
    sqlstm.sqharm[15] = (unsigned int  )0;
    sqlstm.sqadto[15] = (unsigned short )0;
    sqlstm.sqtdso[15] = (unsigned short )0;
    sqlstm.sqhstv[16] = (         void  *)&hCounterRefresh;
    sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[16] = (         int  )0;
    sqlstm.sqindv[16] = (         void  *)0;
    sqlstm.sqinds[16] = (         int  )0;
    sqlstm.sqharm[16] = (unsigned int  )0;
    sqlstm.sqadto[16] = (unsigned short )0;
    sqlstm.sqtdso[16] = (unsigned short )0;
    sqlstm.sqhstv[17] = (         void  *)&hKeyRefresh;
    sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[17] = (         int  )0;
    sqlstm.sqindv[17] = (         void  *)0;
    sqlstm.sqinds[17] = (         int  )0;
    sqlstm.sqharm[17] = (unsigned int  )0;
    sqlstm.sqadto[17] = (unsigned short )0;
    sqlstm.sqtdso[17] = (unsigned short )0;
    sqlstm.sqhstv[18] = (         void  *)&hRecordId;
    sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
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


		
	if ( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {    
		memset( ezatmproperty_ptr, 0, sizeof( struct EzAtmProperty ) );
		ezatmproperty_ptr->RecordId = hRecordId;
		strcpy( ezatmproperty_ptr->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ezatmproperty_ptr->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ezatmproperty_ptr->AtmId, hAtmId );
		strcpy( ezatmproperty_ptr->TxnCode, hTxnCode );
		strcpy( ezatmproperty_ptr->RespCode, hRespCode );
		ezatmproperty_ptr->DownloadCheckReq = hDownloadCheckReq;
		ezatmproperty_ptr->FingerPrintCheckReq = hFingerPrintCheckReq;
		strcpy( ezatmproperty_ptr->FingerPrintCheckChannel, hFingerPrintCheckChannel );
		ezatmproperty_ptr->JournalPrinterReq = hJournalPrinterReq;
		ezatmproperty_ptr->PassbookPrinterReq = hPassbookPrinterReq;
		ezatmproperty_ptr->StatementPrinterReq = hStatementPrinterReq;
		ezatmproperty_ptr->PartialReversalReq = hPartialReversalReq;
		ezatmproperty_ptr->CardReaderModel = hCardReaderModel;
		ezatmproperty_ptr->DecimalPointCheckReq = hDecimalPointCheckReq;
		ezatmproperty_ptr->CurrencyCode = hCurrencyCode;
		ezatmproperty_ptr->DecimalMultiplier = hDecimalMultiplier;
		ezatmproperty_ptr->CounterRefresh = hCounterRefresh;
		ezatmproperty_ptr->KeyRefresh = hKeyRefresh;
		return sqlca.sqlcode;
	}
}

int ReadAtmActionPropertyTable( struct EzAtmActionProperty *ezatmactionproperty_ptr, int RecordId )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int  hRecordId;
		char hInstTerminalGroup[ 17 ];
		char hAtmLogicalGroup[ 17 ];
		char hAtmId[ 17 ];
		char hStatus[ 11 ];
		char hSendCommand;
		char hCommand[ 21 ];
		char hSendResponse;
		char hTxnCode[ 7 ];
		char hRespCode[ 4 ];
    /* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR hInstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR hAtmId IS STRING(17); */ 

	/* EXEC SQL VAR hStatus IS STRING(11); */ 

	/* EXEC SQL VAR hCommand IS STRING(21); */ 

	/* EXEC SQL VAR hTxnCode IS STRING(7); */ 

	/* EXEC SQL VAR hRespCode IS STRING(4); */ 

	
	hRecordId = RecordId;
	
    /* EXEC SQL SELECT
       	RTRIM(INSTTERMINALGROUP),
		RTRIM(LOGICALGROUPID),
		RTRIM(ATMID),
		RTRIM(STATUS),
		SENDCOMMAND,
		RTRIM(COMMAND),
		SENDRESPONSE,
		RTRIM(TXNCODE),
		RESPCODE
	INTO
		:hInstTerminalGroup,
		:hAtmLogicalGroup,
		:hAtmId,
		:hStatus,
		:hSendCommand,
		:hCommand,
		:hSendResponse,
		:hTxnCode,
		:hRespCode
	FROM EZATMACTIONPROPERTY WHERE RECORDID=:hRecordId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 51;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(INSTTERMINALGROUP) ,RTRIM(LOGICALGROUPID) ,R\
TRIM(ATMID) ,RTRIM(STATUS) ,SENDCOMMAND ,RTRIM(COMMAND) ,SENDRESPONSE ,RTRIM(T\
XNCODE) ,RESPCODE into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8  from EZATMACTIONPR\
OPERTY where RECORDID=:b9";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )2172;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)hInstTerminalGroup;
    sqlstm.sqhstl[0] = (unsigned int  )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)hAtmLogicalGroup;
    sqlstm.sqhstl[1] = (unsigned int  )17;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void  *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)hAtmId;
    sqlstm.sqhstl[2] = (unsigned int  )17;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         void  *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned int  )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (         void  *)hStatus;
    sqlstm.sqhstl[3] = (unsigned int  )11;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         void  *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned int  )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (         void  *)&hSendCommand;
    sqlstm.sqhstl[4] = (unsigned int  )1;
    sqlstm.sqhsts[4] = (         int  )0;
    sqlstm.sqindv[4] = (         void  *)0;
    sqlstm.sqinds[4] = (         int  )0;
    sqlstm.sqharm[4] = (unsigned int  )0;
    sqlstm.sqadto[4] = (unsigned short )0;
    sqlstm.sqtdso[4] = (unsigned short )0;
    sqlstm.sqhstv[5] = (         void  *)hCommand;
    sqlstm.sqhstl[5] = (unsigned int  )21;
    sqlstm.sqhsts[5] = (         int  )0;
    sqlstm.sqindv[5] = (         void  *)0;
    sqlstm.sqinds[5] = (         int  )0;
    sqlstm.sqharm[5] = (unsigned int  )0;
    sqlstm.sqadto[5] = (unsigned short )0;
    sqlstm.sqtdso[5] = (unsigned short )0;
    sqlstm.sqhstv[6] = (         void  *)&hSendResponse;
    sqlstm.sqhstl[6] = (unsigned int  )1;
    sqlstm.sqhsts[6] = (         int  )0;
    sqlstm.sqindv[6] = (         void  *)0;
    sqlstm.sqinds[6] = (         int  )0;
    sqlstm.sqharm[6] = (unsigned int  )0;
    sqlstm.sqadto[6] = (unsigned short )0;
    sqlstm.sqtdso[6] = (unsigned short )0;
    sqlstm.sqhstv[7] = (         void  *)hTxnCode;
    sqlstm.sqhstl[7] = (unsigned int  )7;
    sqlstm.sqhsts[7] = (         int  )0;
    sqlstm.sqindv[7] = (         void  *)0;
    sqlstm.sqinds[7] = (         int  )0;
    sqlstm.sqharm[7] = (unsigned int  )0;
    sqlstm.sqadto[7] = (unsigned short )0;
    sqlstm.sqtdso[7] = (unsigned short )0;
    sqlstm.sqhstv[8] = (         void  *)hRespCode;
    sqlstm.sqhstl[8] = (unsigned int  )4;
    sqlstm.sqhsts[8] = (         int  )0;
    sqlstm.sqindv[8] = (         void  *)0;
    sqlstm.sqinds[8] = (         int  )0;
    sqlstm.sqharm[8] = (unsigned int  )0;
    sqlstm.sqadto[8] = (unsigned short )0;
    sqlstm.sqtdso[8] = (unsigned short )0;
    sqlstm.sqhstv[9] = (         void  *)&hRecordId;
    sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
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
    else
    {    
		memset( ezatmactionproperty_ptr, 0, sizeof( struct EzAtmActionProperty ) );
		ezatmactionproperty_ptr->RecordId = hRecordId;
		strcpy( ezatmactionproperty_ptr->InstTerminalGroup , hInstTerminalGroup );
		strcpy( ezatmactionproperty_ptr->AtmLogicalGroup, hAtmLogicalGroup );
		strcpy( ezatmactionproperty_ptr->AtmId, hAtmId );
		strcpy( ezatmactionproperty_ptr->Status, hStatus );
		ezatmactionproperty_ptr->SendCommand = hSendCommand;
		strcpy( ezatmactionproperty_ptr->Command, hCommand );
		ezatmactionproperty_ptr->SendResponse = hSendResponse;
		strcpy( ezatmactionproperty_ptr->TxnCode, hTxnCode );
		strcpy( ezatmactionproperty_ptr->RespCode, hRespCode );
		return sqlca.sqlcode;
	}
}

int ReadAtmStatusTable( struct EzAtmStatus *ezatmstatus_ptr, const char *StatusCode )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char hStatusCode[ 11 ];
		char hStatusFlag;
    /* EXEC SQL END DECLARE SECTION; */ 


	memset( hStatusCode, 0, sizeof( hStatusCode ) );
	strcpy( hStatusCode, StatusCode );
	
	/* EXEC SQL SELECT
       	STATUSFLAG
	INTO
		:hStatusFlag
	FROM EZATMSTATUSDESC WHERE STATUSCODE=:hStatusCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 51;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select STATUSFLAG into :b0  from EZATMSTATUSDESC where STATU\
SCODE=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2227;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&hStatusFlag;
 sqlstm.sqhstl[0] = (unsigned int  )1;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)hStatusCode;
 sqlstm.sqhstl[1] = (unsigned int  )11;
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
    else
    {    
		memset( ezatmstatus_ptr, 0, sizeof( struct EzAtmStatus ) );
		strcpy( ezatmstatus_ptr->StatusCode, hStatusCode );
		ezatmstatus_ptr->StatusFlag = hStatusFlag;
		return sqlca.sqlcode;
	}
}
