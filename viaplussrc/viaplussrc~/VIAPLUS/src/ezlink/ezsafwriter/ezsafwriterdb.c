
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
           char  filnam[17];
};
static struct sqlcxp sqlfpn =
{
    16,
    "ezsafwriterdb.pc"
};


static unsigned int sqlctx = 4994667;


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
            void  *sqhstv[12];
   unsigned int   sqhstl[12];
            int   sqhsts[12];
            void  *sqindv[12];
            int   sqinds[12];
   unsigned int   sqharm[12];
   unsigned int   *sqharc[12];
   unsigned short  sqadto[12];
   unsigned short  sqtdso[12];
} sqlstm = {12,12};

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
5,0,0,1,228,0,3,53,0,0,12,12,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,1,
0,0,1,1,0,0,1,1,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,
68,0,0,2,0,0,29,88,0,0,0,0,0,1,0,
83,0,0,3,191,0,3,134,0,0,10,10,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,
1,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,
138,0,0,4,0,0,29,165,0,0,0,0,0,1,0,
153,0,0,5,128,0,4,193,0,0,4,2,0,1,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
184,0,0,6,325,0,4,241,0,0,12,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,
1,0,0,2,1,0,0,2,1,0,0,2,3,0,0,2,3,0,0,2,5,0,0,1,5,0,0,
247,0,0,7,48,0,2,296,0,0,1,1,0,1,0,1,5,0,0,
266,0,0,8,0,0,29,302,0,0,0,0,0,1,0,
281,0,0,9,87,0,5,322,0,0,3,3,0,1,0,1,1,0,0,1,3,0,0,1,5,0,0,
308,0,0,10,0,0,29,328,0,0,0,0,0,1,0,
323,0,0,11,101,0,5,350,0,0,4,4,0,1,0,1,1,0,0,1,1,0,0,1,3,0,0,1,5,0,0,
354,0,0,12,0,0,29,356,0,0,0,0,0,1,0,
369,0,0,13,96,0,5,379,0,0,3,3,0,1,0,1,1,0,0,1,5,0,0,1,5,0,0,
396,0,0,14,0,0,29,385,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ezlink/ezlnkmsg.h>
#include <ezlink/ezsaftypes.h>

int insertSafRecord( struct EzSafDBInfo safdbinfo )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SafRecordNo[ 21 ];
		char TranDate[ 7 ];
		char TranTime[ 7 ];
		char NetworkId[ 17 ];
		char SafStatus;
		char SafIndicator;
		char SafResponseIndicator;
		char SafRepeatIndicator;
		int SafResponse;
		int TimeOutCount;
		char TxnRefNum[ 151 ];
		char SAFDetailRec[ 2049 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR SafRecordNo IS STRING(21); */ 

	/* EXEC SQL VAR TranDate IS STRING(7); */ 

	/* EXEC SQL VAR TranTime IS STRING(7); */ 

	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR SAFDetailRec IS STRING(2049); */ 

	
	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( TranTime, 0, sizeof( TranTime ) );
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( SAFDetailRec, 0, sizeof( SAFDetailRec ) );
	
	strcpy( SafRecordNo, safdbinfo.SafRecordNo );
	strcpy( TranDate, safdbinfo.TranDate );
	strcpy( TranTime, safdbinfo.TranTime );
	strcpy( NetworkId, safdbinfo.NetworkId );
	strcpy( TxnRefNum, safdbinfo.TxnRefNum );
	SafIndicator = safdbinfo.SafIndicator;
	SafStatus = safdbinfo.SafStatus;
	SafResponseIndicator = safdbinfo.SafResponseIndicator;
	SafRepeatIndicator = safdbinfo.SafRepeatIndicator;
	TimeOutCount = safdbinfo.TimeOutCount;
	SafResponse = safdbinfo.SafResponse;
	strcpy( SAFDetailRec, safdbinfo.SAFDetailRec );
	
	/* EXEC SQL INSERT INTO EZSAFDB
	(
		SAFRECORDNO,
		TRANDATE,
		TRANTIME,
		NETWORKID,
		SAFSTATUS,
		SAFINDICATOR,
		SAFRESPONSEINDICATOR,
		SAFREPEATINDICATOR,
		SAFRESPONSE,
		TIMEOUTCOUNT,
		TXNREFNUM,
		SAFDETREC
	)
	VALUES 
	(
		:SafRecordNo,
		:TranDate,
		:TranTime,
		:NetworkId,
		:SafStatus,
		:SafIndicator,
		:SafResponseIndicator,
		:SafRepeatIndicator,
		:SafResponse,
		:TimeOutCount,
		:TxnRefNum,
		:SAFDetailRec
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZSAFDB (SAFRECORDNO,TRANDATE,TRANTIME,NETWORKID\
,SAFSTATUS,SAFINDICATOR,SAFRESPONSEINDICATOR,SAFREPEATINDICATOR,SAFRESPONSE,TI\
MEOUTCOUNT,TXNREFNUM,SAFDETREC) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b\
9,:b10,:b11)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SafRecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TranDate;
 sqlstm.sqhstl[1] = (unsigned int  )7;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TranTime;
 sqlstm.sqhstl[2] = (unsigned int  )7;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)NetworkId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SafStatus;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&SafIndicator;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&SafResponseIndicator;
 sqlstm.sqhstl[6] = (unsigned int  )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&SafRepeatIndicator;
 sqlstm.sqhstl[7] = (unsigned int  )1;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&SafResponse;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&TimeOutCount;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[10] = (unsigned int  )151;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)SAFDetailRec;
 sqlstm.sqhstl[11] = (unsigned int  )2049;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
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
        sqlstm.arrsiz = 12;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )68;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int insertEzSafHist( struct EzSafDBInfo safdbinfo )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SafRecordNo[ 21 ];
		char TranDate[ 7 ];
		char TranTime[ 7 ];
		char NetworkId[ 17 ];
		char SafIndicator;
		char SafResponseIndicator;
		int SafResponse;
		int TimeOutCount;
		char TxnRefNum[ 151 ];
		char SAFDetailRec[ 2049 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR SafRecordNo IS STRING(21); */ 

	/* EXEC SQL VAR TranDate IS STRING(7); */ 

	/* EXEC SQL VAR TranTime IS STRING(7); */ 

	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR SAFDetailRec IS STRING(2049); */ 

	
	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( TranTime, 0, sizeof( TranTime ) );
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( SAFDetailRec, 0, sizeof( SAFDetailRec ) );
	
	strcpy( SafRecordNo, safdbinfo.SafRecordNo );
	strcpy( TranDate, safdbinfo.TranDate );
	strcpy( TranTime, safdbinfo.TranTime );
	strcpy( NetworkId, safdbinfo.NetworkId );
	strcpy( TxnRefNum, safdbinfo.TxnRefNum );
	SafIndicator = safdbinfo.SafIndicator;
	SafResponseIndicator = safdbinfo.SafResponseIndicator;
	TimeOutCount = safdbinfo.TimeOutCount;
	SafResponse = safdbinfo.SafResponse;
	strcpy( SAFDetailRec, safdbinfo.SAFDetailRec );
	
	/* EXEC SQL INSERT INTO EZSAFHIST
	(
		SAFRECORDNO,
		TRANDATE,
		TRANTIME,
		NETWORKID,
		SAFINDICATOR,
		SAFRESPONSEINDICATOR,
		SAFRESPONSE,
		TIMEOUTCOUNT,
		TXNREFNUM,
		SAFDETREC
	)
	VALUES 
	(
		:SafRecordNo,
		:TranDate,
		:TranTime,
		:NetworkId,
		:SafIndicator,
		:SafResponseIndicator,
		:SafResponse,
		:TimeOutCount,
		:TxnRefNum,
		:SAFDetailRec
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZSAFHIST (SAFRECORDNO,TRANDATE,TRANTIME,NETWORK\
ID,SAFINDICATOR,SAFRESPONSEINDICATOR,SAFRESPONSE,TIMEOUTCOUNT,TXNREFNUM,SAFDET\
REC) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )83;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SafRecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TranDate;
 sqlstm.sqhstl[1] = (unsigned int  )7;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TranTime;
 sqlstm.sqhstl[2] = (unsigned int  )7;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)NetworkId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SafIndicator;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&SafResponseIndicator;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&SafResponse;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&TimeOutCount;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[8] = (unsigned int  )151;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)SAFDetailRec;
 sqlstm.sqhstl[9] = (unsigned int  )2049;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {
        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 12;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )138;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int readTxnRefNum( const char *I_TxnRefNum, const char *I_NetworkId )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char Input_NetworkId[ 17 ];
		char TxnRefNum[ 151 ];
		char Input_TxnRefNum[ 151 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR Input_TxnRefNum IS STRING(151); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( Input_TxnRefNum, 0, sizeof( Input_TxnRefNum ) );
		
	strcpy( Input_TxnRefNum, I_TxnRefNum );
	strcpy( Input_NetworkId, I_NetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(NETWORKID),
		RTRIM(TXNREFNUM)
	INTO
		:NetworkId:ind_var,
		:TxnRefNum:ind_var
    FROM EZSAFDB WHERE RTRIM(TXNREFNUM)=:Input_TxnRefNum AND RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NETWORKID) ,RTRIM(TXNREFNUM) into :b0:b1,:b2:b3\
  from EZSAFDB where (RTRIM(TXNREFNUM)=:b4 and RTRIM(NETWORKID)=:b5)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )153;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)NetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[1] = (unsigned int  )151;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)Input_TxnRefNum;
 sqlstm.sqhstl[2] = (unsigned int  )151;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_NetworkId;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    	
    return 0;
}

int readSafDBInfo( const char *I_TxnRefNum, struct EzSafDBInfo *safdbinfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SafRecordNo[ 21 ];
		char TranDate[ 7 ];
		char TranTime[ 7 ];
		char NetworkId[ 17 ];
		char SafStatus;
		char SafIndicator;
		char SafResponseIndicator;
		char SafRepeatIndicator;
		int SafResponse;
		int TimeOutCount;
		char TxnRefNum[ 151 ];
		char SAFDetailRec[ 2049 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR SafRecordNo IS STRING(21); */ 

	/* EXEC SQL VAR TranDate IS STRING(7); */ 

	/* EXEC SQL VAR TranTime IS STRING(7); */ 

	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR SAFDetailRec IS STRING(2049); */ 

	
	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( TranTime, 0, sizeof( TranTime ) );
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( SAFDetailRec, 0, sizeof( SAFDetailRec ) );
		
	strcpy( TxnRefNum, I_TxnRefNum );
	
	/* EXEC SQL SELECT
		RTRIM(SAFRECORDNO),
		RTRIM(TRANDATE),
		RTRIM(TRANTIME),
		RTRIM(NETWORKID),
		SAFSTATUS,
		SAFINDICATOR,
		SAFRESPONSEINDICATOR,
		SAFREPEATINDICATOR,
		SAFRESPONSE,
		TIMEOUTCOUNT,
		RTRIM(SAFDETREC)
	INTO
		:SafRecordNo:ind_var,
		:TranDate:ind_var,
		:TranTime:ind_var,
		:NetworkId:ind_var,
		:SafStatus:ind_var,
		:SafIndicator:ind_var,
		:SafResponseIndicator:ind_var,
		:SafRepeatIndicator:ind_var,
		:SafResponse:ind_var,
		:TimeOutCount:ind_var,
		:SAFDetailRec:ind_var
    FROM EZSAFDB WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(SAFRECORDNO) ,RTRIM(TRANDATE) ,RTRIM(TRANTIME) \
,RTRIM(NETWORKID) ,SAFSTATUS ,SAFINDICATOR ,SAFRESPONSEINDICATOR ,SAFREPEATIND\
ICATOR ,SAFRESPONSE ,TIMEOUTCOUNT ,RTRIM(SAFDETREC) into :b0:b1,:b2:b3,:b4:b5,\
:b6:b7,:b8:b9,:b10:b11,:b12:b13,:b14:b15,:b16:b17,:b18:b19,:b20:b21  from EZSA\
FDB where RTRIM(TXNREFNUM)=:b22";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )184;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SafRecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TranDate;
 sqlstm.sqhstl[1] = (unsigned int  )7;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TranTime;
 sqlstm.sqhstl[2] = (unsigned int  )7;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)NetworkId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SafStatus;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&SafIndicator;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)&ind_var;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&SafResponseIndicator;
 sqlstm.sqhstl[6] = (unsigned int  )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)&ind_var;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&SafRepeatIndicator;
 sqlstm.sqhstl[7] = (unsigned int  )1;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)&ind_var;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&SafResponse;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)&ind_var;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&TimeOutCount;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)&ind_var;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)SAFDetailRec;
 sqlstm.sqhstl[10] = (unsigned int  )2049;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)&ind_var;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[11] = (unsigned int  )151;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
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
    
    strcpy( safdbinfo_ptr->SafRecordNo, SafRecordNo );
    strcpy( safdbinfo_ptr->TranDate, TranDate );
    strcpy( safdbinfo_ptr->TranTime, TranTime );
    strcpy( safdbinfo_ptr->NetworkId, NetworkId );
    safdbinfo_ptr->SafStatus = SafStatus;
   	safdbinfo_ptr->SafIndicator = SafIndicator;
   	safdbinfo_ptr->SafResponseIndicator = SafResponseIndicator;
   	safdbinfo_ptr->SafRepeatIndicator = SafRepeatIndicator;
   	safdbinfo_ptr->SafResponse = SafResponse;
   	safdbinfo_ptr->TimeOutCount = TimeOutCount;
   	strcpy( safdbinfo_ptr->SAFDetailRec, SAFDetailRec );
    
	return 0;
}

int deleteEzSafDB( const char *I_TxnRefNum )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	strcpy( TxnRefNum, I_TxnRefNum );
	
	/* EXEC SQL DELETE FROM EZSAFDB WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "delete  from EZSAFDB  where RTRIM(TXNREFNUM)=:b0";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )247;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned int  )151;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {
        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 12;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )266;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


       return sqlca.sqlcode;
    }
}

int updateSafResponse( const char *I_TxnRefNum, char I_SafResponseFlag, int I_SafResponse )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char SafResponseFlag;
		int SafResponse;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	strcpy( TxnRefNum, I_TxnRefNum );
	SafResponseFlag = I_SafResponseFlag;
	SafResponse = I_SafResponse;
	
	/* EXEC SQL UPDATE EZSAFDB SET SAFRESPONSEINDICATOR = :SafResponseFlag, SAFRESPONSE = :SafResponse WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSAFDB  set SAFRESPONSEINDICATOR=:b0,SAFRESPONSE=:b1\
 where RTRIM(TXNREFNUM)=:b2";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )281;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&SafResponseFlag;
 sqlstm.sqhstl[0] = (unsigned int  )1;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&SafResponse;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[2] = (unsigned int  )151;
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
        sqlstm.arrsiz = 12;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )308;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int updateSafStatus( const char *I_TxnRefNum, char I_SafStatus, char I_SafResponseFlag, int I_SafResponse )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char SafStatus;
		char SafResponseFlag;
		int SafResponse;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	strcpy( TxnRefNum, I_TxnRefNum );
	SafStatus = I_SafStatus;
	SafResponseFlag = I_SafResponseFlag;
	SafResponse = I_SafResponse;
	
	/* EXEC SQL UPDATE EZSAFDB SET SAFSTATUS = :SafStatus, SAFRESPONSEINDICATOR = :SafResponseFlag, SAFRESPONSE = :SafResponse WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSAFDB  set SAFSTATUS=:b0,SAFRESPONSEINDICATOR=:b1,S\
AFRESPONSE=:b2 where RTRIM(TXNREFNUM)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )323;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&SafStatus;
 sqlstm.sqhstl[0] = (unsigned int  )1;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&SafResponseFlag;
 sqlstm.sqhstl[1] = (unsigned int  )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&SafResponse;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[3] = (unsigned int  )151;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {
        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 12;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )354;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int updateSafRepeatIndicator( const char *I_NetworkId, const char *I_TxnRefNum, char I_SafRepeatIndicator )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char TxnRefNum[ 151 ];
		char SafRepeatIndicator;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	
	strcpy( NetworkId, I_NetworkId );
	strcpy( TxnRefNum, I_TxnRefNum );
	SafRepeatIndicator = I_SafRepeatIndicator;
		
	/* EXEC SQL UPDATE EZSAFDB SET SAFREPEATINDICATOR = :SafRepeatIndicator WHERE RTRIM(TXNREFNUM)=:TxnRefNum AND RTRIM(NETWORKID)=:NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSAFDB  set SAFREPEATINDICATOR=:b0 where (RTRIM(TXNR\
EFNUM)=:b1 and RTRIM(NETWORKID)=:b2)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )369;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&SafRepeatIndicator;
 sqlstm.sqhstl[0] = (unsigned int  )1;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[1] = (unsigned int  )151;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)NetworkId;
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
        sqlstm.arrsiz = 12;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )396;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}
