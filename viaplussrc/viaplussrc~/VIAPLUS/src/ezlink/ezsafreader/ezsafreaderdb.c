
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
    "ezsafreaderdb.pc"
};


static unsigned int sqlctx = 4978795;


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
            void  *sqhstv[5];
   unsigned int   sqhstl[5];
            int   sqhsts[5];
            void  *sqindv[5];
            int   sqinds[5];
   unsigned int   sqharm[5];
   unsigned int   *sqharc[5];
   unsigned short  sqadto[5];
   unsigned short  sqtdso[5];
} sqlstm = {12,5};

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
5,0,0,1,333,0,4,32,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,1,5,0,0,
40,0,0,2,99,0,4,73,0,0,3,2,0,1,0,2,3,0,0,1,5,0,0,1,5,0,0,
67,0,0,3,90,0,5,106,0,0,3,3,0,1,0,1,3,0,0,1,5,0,0,1,5,0,0,
94,0,0,4,0,0,29,112,0,0,0,0,0,1,0,
109,0,0,5,96,0,5,135,0,0,3,3,0,1,0,1,1,0,0,1,5,0,0,1,5,0,0,
136,0,0,6,0,0,29,141,0,0,0,0,0,1,0,
151,0,0,7,101,0,5,163,0,0,4,4,0,1,0,1,1,0,0,1,1,0,0,1,3,0,0,1,5,0,0,
182,0,0,8,0,0,29,169,0,0,0,0,0,1,0,
};


#include <ezdb/eznetworkreplay.h>
#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <ezlink/ezlnkmsg.h>
#include <ezlink/ezsaftypes.h>

int getNextPendingRecord( const char *I_NetworkId, struct EzSafDBInfo *safdbinfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SafRecordNo[ 21 ];
		char NetworkId[ 17 ];
		char TxnRefNum[ 151 ];
		char SAFDetailRec[ 2049 ];
		char SafRepeatIndicator;
        short ind_var;
    /* EXEC SQL END DECLARE SECTION; */ 

				
	/* EXEC SQL VAR SafRecordNo IS STRING(21); */ 

	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR SAFDetailRec IS STRING(2049); */ 

	
	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum	) );
	memset( SAFDetailRec, 0, sizeof( SAFDetailRec ) );
	
	strcpy( NetworkId, I_NetworkId );

	/* EXEC SQL SELECT
		RTRIM(SAFRECORDNO),
		RTRIM(TXNREFNUM),
		RTRIM(SAFDETREC),
		RTRIM(SAFREPEATINDICATOR)
	INTO
		:SafRecordNo:ind_var,
		:TxnRefNum:ind_var,
		:SAFDetailRec:ind_var,
		:SafRepeatIndicator:ind_var
    FROM EZSAFDB WHERE RTRIM(SAFRECORDNO) || RTRIM(TRANDATE) || RTRIM(TRANTIME) IN (SELECT MIN(RTRIM(SAFRECORDNO)||RTRIM(TRANDATE)||RTRIM(TRANTIME)) FROM EZSAFDB WHERE RTRIM(NETWORKID)=:NetworkId AND SAFSTATUS = 'P' ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(SAFRECORDNO) ,RTRIM(TXNREFNUM) ,RTRIM(SAFDETREC\
) ,RTRIM(SAFREPEATINDICATOR) into :b0:b1,:b2:b3,:b4:b5,:b6:b7  from EZSAFDB wh\
ere ((RTRIM(SAFRECORDNO)||RTRIM(TRANDATE))||RTRIM(TRANTIME)) in (select min(((\
RTRIM(SAFRECORDNO)||RTRIM(TRANDATE))||RTRIM(TRANTIME)))  from EZSAFDB where (R\
TRIM(NETWORKID)=:b8 and SAFSTATUS='P'))";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
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
 sqlstm.sqhstv[1] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[1] = (unsigned int  )151;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)SAFDetailRec;
 sqlstm.sqhstl[2] = (unsigned int  )2049;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&SafRepeatIndicator;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)NetworkId;
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

	strcpy( safdbinfo_ptr->SafRecordNo, SafRecordNo );
	strcpy( safdbinfo_ptr->TxnRefNum, TxnRefNum );
	strcpy( safdbinfo_ptr->SAFDetailRec, SAFDetailRec );
	strcpy( safdbinfo_ptr->NetworkId, NetworkId );
	safdbinfo_ptr->SafRepeatIndicator = SafRepeatIndicator;
	return 0;
}

int readTimeOutCount( const char *I_NetworkId, const char *I_TxnRefNum, int *I_TimeOutCount )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char TxnRefNum[ 151 ];
		int TimeOutCount;
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	
	strcpy( NetworkId, I_NetworkId );
	strcpy( TxnRefNum, I_TxnRefNum );
	
	/* EXEC SQL SELECT
		TIMEOUTCOUNT
	INTO
		:TimeOutCount:ind_var
	FROM EZSAFDB WHERE RTRIM(TXNREFNUM)=:TxnRefNum AND RTRIM(NETWORKID)=:NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select TIMEOUTCOUNT into :b0:b1  from EZSAFDB where (RTRIM(T\
XNREFNUM)=:b2 and RTRIM(NETWORKID)=:b3)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )40;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&TimeOutCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
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
    	
    *I_TimeOutCount = TimeOutCount;
    
    return sqlca.sqlcode;
}

int updateTimeOutCount( const char *I_NetworkId, const char *I_TxnRefNum, int I_TimeOutCount )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char TxnRefNum[ 151 ];
		int TimeOutCount;
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	
	strcpy( NetworkId, I_NetworkId );
	strcpy( TxnRefNum, I_TxnRefNum );
	TimeOutCount = I_TimeOutCount;
	
	/* EXEC SQL UPDATE EZSAFDB SET TIMEOUTCOUNT = :TimeOutCount WHERE RTRIM(TXNREFNUM)=:TxnRefNum AND RTRIM(NETWORKID)=:NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSAFDB  set TIMEOUTCOUNT=:b0 where (RTRIM(TXNREFNUM)\
=:b1 and RTRIM(NETWORKID)=:b2)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )67;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&TimeOutCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
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
        sqlstm.arrsiz = 5;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )94;
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
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSAFDB  set SAFREPEATINDICATOR=:b0 where (RTRIM(TXNR\
EFNUM)=:b1 and RTRIM(NETWORKID)=:b2)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )109;
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
        sqlstm.arrsiz = 5;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )136;
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
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSAFDB  set SAFSTATUS=:b0,SAFRESPONSEINDICATOR=:b1,S\
AFRESPONSE=:b2 where RTRIM(TXNREFNUM)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )151;
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
        sqlstm.arrsiz = 5;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )182;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


       return sqlca.sqlcode;
    }
}



