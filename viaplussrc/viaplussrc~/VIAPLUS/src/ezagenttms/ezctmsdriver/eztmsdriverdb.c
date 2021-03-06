
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
    "eztmsdriverdb.pc"
};


static unsigned int sqlctx = 5059435;


static struct sqlexd {
   unsigned long  sqlvsn;
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
   unsigned char  **sqphsv;
   unsigned long  *sqphsl;
            int   *sqphss;
            short **sqpind;
            int   *sqpins;
   unsigned long  *sqparm;
   unsigned long  **sqparc;
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
   unsigned char  *sqhstv[24];
   unsigned long  sqhstl[24];
            int   sqhsts[24];
            short *sqindv[24];
            int   sqinds[24];
   unsigned long  sqharm[24];
   unsigned long  *sqharc[24];
   unsigned short  sqadto[24];
   unsigned short  sqtdso[24];
} sqlstm = {12,24};

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
5,0,0,1,166,0,5,61,0,0,5,5,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
40,0,0,2,194,0,5,69,0,0,5,5,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
75,0,0,3,241,0,3,79,0,0,10,10,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
130,0,0,4,0,0,29,111,0,0,0,0,0,1,0,
145,0,0,5,0,0,29,116,0,0,0,0,0,1,0,
160,0,0,6,77,0,5,137,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
183,0,0,7,0,0,29,145,0,0,0,0,0,1,0,
198,0,0,8,124,0,5,177,0,0,5,5,0,1,0,1,5,0,0,1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
233,0,0,9,0,0,29,187,0,0,0,0,0,1,0,
248,0,0,10,346,0,4,228,0,0,14,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,3,0,0,2,1,0,0,2,3,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,3,0,0,2,4,0,0,1,5,0,0,
319,0,0,11,396,0,3,363,0,0,24,24,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,
0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,1,0,0,1,5,0,0,
430,0,0,12,0,0,29,422,0,0,0,0,0,1,0,
445,0,0,13,131,0,4,452,0,0,4,2,0,1,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
};


#include <eztms/eztmsdbtypes.h>
#include <ezmms/ezmmsdbtypes.h>
#include <eztms/eztmsdef.h>
#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezlink/ezlnkmsg.h>

int updateTerminalStatus( struct EzMMSTerminalStatus *status_ptr, char UpdateFlag  )
{
	int ErrCode;
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

   		char InstId[ 13 ];
   		char MachineId[ 33 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char TerminalId[ 9 ];
		char LastRcvDate[ 7 ];
		char LastRcvTime[ 7 ];
		char LastTxnDate[ 7 ];
		char LastTxnTime[ 7 ];
		char Version[ 16 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR TerminalId IS STRING(9); */ 

	/* EXEC SQL VAR LastRcvDate IS STRING(7); */ 

	/* EXEC SQL VAR LastRcvTime IS STRING(7); */ 

	/* EXEC SQL VAR LastTxnDate IS STRING(7); */ 

	/* EXEC SQL VAR LastTxnTime IS STRING(7); */ 

	/* EXEC SQL VAR Version IS STRING(16); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( LastRcvDate, 0, sizeof( LastRcvDate ) );
	memset( LastRcvTime, 0, sizeof( LastRcvTime ) );
	memset( LastTxnDate, 0, sizeof( LastTxnDate ) );
	memset( LastTxnTime, 0, sizeof( LastTxnTime ) );
	memset( Version, 0, sizeof( Version ) );
	
	strcpy( InstId, status_ptr->InstId );
	strcpy( MachineId, status_ptr->MachineId );
	strcpy( MerchantId, status_ptr->MerchantId );
	strcpy( StoreId, status_ptr->StoreId );
	strcpy( TerminalId, status_ptr->TerminalId );
	strcpy( LastRcvDate, status_ptr->LastRcvDate );
	strcpy( LastRcvTime, status_ptr->LastRcvTime );
	strcpy( LastTxnDate, status_ptr->LastTxnDate );
	strcpy( LastTxnTime, status_ptr->LastTxnTime );
	strcpy( Version, status_ptr->Version );
	
	if( UpdateFlag == TERMINAL_STATUSID_ECHO )
	{
		/* EXEC SQL UPDATE EZMMS_TERMINALSTATUS SET
			LAST_RCVD_DATE = SYSDATE,
			LAST_RCVD_TIME = :LastRcvTime,
			VERSION = :Version
		WHERE TRIM(INST_ID) = :InstId AND TRIM(MERCHANT_ID) = :MerchantId AND TRIM(TERMINAL_ID) = :TerminalId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 5;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "update EZMMS_TERMINALSTATUS  set LAST_RCVD_DATE=SYSDATE,LAS\
T_RCVD_TIME=:b0,VERSION=:b1 where ((trim(INST_ID)=:b2 and trim(MERCHANT_ID)=:b\
3) and trim(TERMINAL_ID)=:b4)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)LastRcvTime;
  sqlstm.sqhstl[0] = (unsigned long )7;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)Version;
  sqlstm.sqhstl[1] = (unsigned long )16;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)InstId;
  sqlstm.sqhstl[2] = (unsigned long )13;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)MerchantId;
  sqlstm.sqhstl[3] = (unsigned long )16;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)TerminalId;
  sqlstm.sqhstl[4] = (unsigned long )9;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
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


	}
	else
	{
		/* EXEC SQL UPDATE EZMMS_TERMINALSTATUS SET
			LAST_RCVD_DATE = SYSDATE,
			LAST_RCVD_TIME = :LastRcvTime,
			LAST_TXN_DATE = SYSDATE,
			LAST_TXN_TIME = :LastTxnTime
		WHERE TRIM(INST_ID) = :InstId AND TRIM(MERCHANT_ID) = :MerchantId AND TRIM(TERMINAL_ID) = :TerminalId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 5;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "update EZMMS_TERMINALSTATUS  set LAST_RCVD_DATE=SYSDATE,LAS\
T_RCVD_TIME=:b0,LAST_TXN_DATE=SYSDATE,LAST_TXN_TIME=:b1 where ((trim(INST_ID)=\
:b2 and trim(MERCHANT_ID)=:b3) and trim(TERMINAL_ID)=:b4)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )40;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)LastRcvTime;
  sqlstm.sqhstl[0] = (unsigned long )7;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)LastTxnTime;
  sqlstm.sqhstl[1] = (unsigned long )7;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)InstId;
  sqlstm.sqhstl[2] = (unsigned long )13;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)MerchantId;
  sqlstm.sqhstl[3] = (unsigned long )16;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)TerminalId;
  sqlstm.sqhstl[4] = (unsigned long )9;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
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


	}
	
	if( sqlca.sqlcode == 1403 )
	{
		/* EXEC SQL INSERT INTO EZMMS_TERMINALSTATUS
		(
			INST_ID,
			MACHINE_ID,
			MERCHANT_ID,
			STORE_ID,
			TERMINAL_ID,
			LAST_RCVD_DATE,
			LAST_RCVD_TIME,
			LAST_TXN_DATE,
			LAST_TXN_TIME,
			VERSION
		)
		VALUES
		(
			:InstId,
			:MachineId,
			:MerchantId,
			:StoreId,
			:TerminalId,
			to_date( :LastRcvDate, 'dd-mm-yy' ),
			:LastRcvTime,
			to_date( :LastTxnDate, 'dd-mm-yy' ),
			:LastTxnTime,
			:Version
		); */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 10;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "insert into EZMMS_TERMINALSTATUS (INST_ID,MACHINE_ID,MERCHA\
NT_ID,STORE_ID,TERMINAL_ID,LAST_RCVD_DATE,LAST_RCVD_TIME,LAST_TXN_DATE,LAST_TX\
N_TIME,VERSION) values (:b0,:b1,:b2,:b3,:b4,to_date(:b5,'dd-mm-yy'),:b6,to_dat\
e(:b7,'dd-mm-yy'),:b8,:b9)";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )75;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)InstId;
  sqlstm.sqhstl[0] = (unsigned long )13;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)MachineId;
  sqlstm.sqhstl[1] = (unsigned long )33;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)MerchantId;
  sqlstm.sqhstl[2] = (unsigned long )16;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)StoreId;
  sqlstm.sqhstl[3] = (unsigned long )33;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)TerminalId;
  sqlstm.sqhstl[4] = (unsigned long )9;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (unsigned char  *)LastRcvDate;
  sqlstm.sqhstl[5] = (unsigned long )7;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         short *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned long )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (unsigned char  *)LastRcvTime;
  sqlstm.sqhstl[6] = (unsigned long )7;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         short *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned long )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (unsigned char  *)LastTxnDate;
  sqlstm.sqhstl[7] = (unsigned long )7;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         short *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned long )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (unsigned char  *)LastTxnTime;
  sqlstm.sqhstl[8] = (unsigned long )7;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         short *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned long )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (unsigned char  *)Version;
  sqlstm.sqhstl[9] = (unsigned long )16;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         short *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned long )0;
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


	}
	
	ErrCode = sqlca.sqlcode;
		
	if ( sqlca.sqlcode != 0 )
	{
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 10;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )130;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	    return ( ErrCode );
	}
    else
    {
    	/* EXEC SQL COMMIT; */ 

{
     struct sqlexd sqlstm;
     sqlstm.sqlvsn = 12;
     sqlstm.arrsiz = 10;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )145;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return ( sqlca.sqlcode );
    }     
}

int updateTermPINKeyinTable( const char *I_MachineId, const char *I_TermPINKey )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char MachineId[ 33 ];  
		char TermPINKey[ 65 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR MachineId IS STRING( 33 ); */ 

	/* EXEC SQL VAR TermPINKey IS STRING( 65 ); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( TermPINKey, 0, sizeof( TermPINKey ) );
	
	strcpy( MachineId, I_MachineId );
	strcpy( TermPINKey, I_TermPINKey );
	
	/* EXEC SQL UPDATE EZMMS_TERMINALPROFILE SET 
		TERM_PIN_KEY=:TermPINKey
	WHERE TRIM(MACHINE_ID)=:MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 10;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZMMS_TERMINALPROFILE  set TERM_PIN_KEY=:b0 where tri\
m(MACHINE_ID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )160;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)TermPINKey;
 sqlstm.sqhstl[0] = (unsigned long )65;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)MachineId;
 sqlstm.sqhstl[1] = (unsigned long )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
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
  sqlstm.arrsiz = 10;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )183;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		if ( sqlca.sqlcode != 0 )
        	return ( sqlca.sqlcode );
	}
}

int updateTerminalBatchTxnInfo( const char *I_MachineId, const char *I_TMSTxnRefNum, const char *I_Amount, char I_MatchFlag, const char *I_MatchDesc )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MachineId[ 33 ];
		char TMSTxnRefNum[ 151 ];
		char TermAmount[ 21 ];
		char MatchFlag;
		char MatchDesc[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR TMSTxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR TermAmount IS STRING(21); */ 

	/* EXEC SQL VAR MatchDesc IS STRING(33); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
	memset( TermAmount, 0, sizeof( TermAmount ) );
	memset( MatchDesc, 0, sizeof( MatchDesc ) );
	
	strcpy( MachineId, I_MachineId );
	strcpy( TMSTxnRefNum, I_TMSTxnRefNum );
	strcpy( TermAmount, I_Amount );
	MatchFlag = I_MatchFlag;
	strcpy( MatchDesc, I_MatchDesc );
	
	/* EXEC SQL UPDATE EZMMSBATCHTXNINFO SET 
    	TERMAMOUNT = :TermAmount,
    	MATCHFLAG = :MatchFlag,
    	MATCHDESC = :MatchDesc
    WHERE TRIM(MACHINEID) = :MachineId AND TRIM(TXNREFNUM) = :TMSTxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 10;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZMMSBATCHTXNINFO  set TERMAMOUNT=:b0,MATCHFLAG=:b1,M\
ATCHDESC=:b2 where (trim(MACHINEID)=:b3 and trim(TXNREFNUM)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )198;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)TermAmount;
 sqlstm.sqhstl[0] = (unsigned long )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)&MatchFlag;
 sqlstm.sqhstl[1] = (unsigned long )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)MatchDesc;
 sqlstm.sqhstl[2] = (unsigned long )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)MachineId;
 sqlstm.sqhstl[3] = (unsigned long )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)TMSTxnRefNum;
 sqlstm.sqhstl[4] = (unsigned long )151;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
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
    else
    {
    	/* EXEC SQL COMMIT; */ 

{
     struct sqlexd sqlstm;
     sqlstm.sqlvsn = 12;
     sqlstm.arrsiz = 10;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )233;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int readTerminalBatchInfo( const char *I_MachineId, struct EzTerminalBatchInfo *termbatchinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char BatchId[ 13 ];
		char InstId[ 13 ];
		char MachineId[ 33 ];
		char Termid[ 9 ];
		char MerchantId[ 16 ];
		char OpenDate[ 7 ];
		int OpenTime;
		char Source;
		int SaleCount;
		double SaleAmount;
		int VoidCount;
		double VoidAmount;
		int AuthCount;
		double AuthAmount;
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR Termid IS STRING(9); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR OpenDate IS STRING(7); */ 

	
	memset( BatchId, 0, sizeof( BatchId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( Termid, 0, sizeof( Termid ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( OpenDate, 0, sizeof( OpenDate ) );
	
	strcpy( MachineId, I_MachineId );
	
	/* EXEC SQL SELECT 
		RTRIM(INSTID),
		RTRIM(BATCHID),
		RTRIM(TERMID),
		RTRIM(MERCHANTID),
		TO_CHAR(OPENDATE, 'DDMMYY' ),
		OPENTIME,
		SOURCE,
		SALECOUNT,
		SALEAMOUNT,
		VOIDCOUNT,
		VOIDAMOUNT,
		AUTHCOUNT,
		AUTHAMOUNT
	INTO 
		:InstId:ind_var,
		:BatchId:ind_var,
		:Termid: ind_var,
		:MerchantId:ind_var,
		:OpenDate:ind_var,
		:OpenTime:ind_var,
		:Source:ind_var,
		:SaleCount:ind_var,
		:SaleAmount:ind_var,
		:VoidCount:ind_var,
		:VoidAmount:ind_var,
		:AuthCount:ind_var,
		:AuthAmount:ind_var
	FROM EZMMSBATCHINFO WHERE RTRIM(MACHINEID) =:MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 14;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(BATCHID) ,RTRIM(TERMID) ,RTRIM(M\
ERCHANTID) ,TO_CHAR(OPENDATE,'DDMMYY') ,OPENTIME ,SOURCE ,SALECOUNT ,SALEAMOUN\
T ,VOIDCOUNT ,VOIDAMOUNT ,AUTHCOUNT ,AUTHAMOUNT into :b0:b1,:b2:b3,:b4:b5,:b6:\
b7,:b8:b9,:b10:b11,:b12:b13,:b14:b15,:b16:b17,:b18:b19,:b20:b21,:b22:b23,:b24:\
b25  from EZMMSBATCHINFO where RTRIM(MACHINEID)=:b26";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )248;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)InstId;
 sqlstm.sqhstl[0] = (unsigned long )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)BatchId;
 sqlstm.sqhstl[1] = (unsigned long )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)Termid;
 sqlstm.sqhstl[2] = (unsigned long )9;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[3] = (unsigned long )16;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)OpenDate;
 sqlstm.sqhstl[4] = (unsigned long )7;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)&OpenTime;
 sqlstm.sqhstl[5] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)&ind_var;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)&Source;
 sqlstm.sqhstl[6] = (unsigned long )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)&ind_var;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)&SaleCount;
 sqlstm.sqhstl[7] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)&ind_var;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)&SaleAmount;
 sqlstm.sqhstl[8] = (unsigned long )sizeof(double);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)&ind_var;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)&VoidCount;
 sqlstm.sqhstl[9] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)&ind_var;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)&VoidAmount;
 sqlstm.sqhstl[10] = (unsigned long )sizeof(double);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)&ind_var;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)&AuthCount;
 sqlstm.sqhstl[11] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)&ind_var;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)&AuthAmount;
 sqlstm.sqhstl[12] = (unsigned long )sizeof(double);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)&ind_var;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)MachineId;
 sqlstm.sqhstl[13] = (unsigned long )33;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
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

 
	
	if( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( termbatchinfo_rec->InstId, InstId );
	strcpy( termbatchinfo_rec->MachineId, MachineId );
	strcpy( termbatchinfo_rec->BatchId, BatchId );
	strcpy( termbatchinfo_rec->Termid, Termid );
	strcpy( termbatchinfo_rec->MerchantId, MerchantId );
	strcpy( termbatchinfo_rec->OpenDate, OpenDate );
	termbatchinfo_rec->OpenTime = OpenTime;
	termbatchinfo_rec->Source = Source;
	termbatchinfo_rec->SaleCount = SaleCount;
	termbatchinfo_rec->SaleAmount = SaleAmount;
	termbatchinfo_rec->VoidCount = VoidCount;
	termbatchinfo_rec->VoidAmount = VoidAmount;
	termbatchinfo_rec->AuthCount = AuthCount;
	termbatchinfo_rec->AuthAmount = AuthAmount;
	return sqlca.sqlcode;
}

int insertTerminalBatchUpload( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum, char I_MatchFlag, const char *I_MatchDesc )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MachineId[ 33 ];
		char TermId[ 9 ];
		char MerchantId[ 16 ];
		char BatchId[ 13 ];
		char TMSTxnRefNum[ 151 ];
		int MsgType;
		int TxnCode;
		char chn[ 20 ];
		char TermLoc[ 65 ];
		int TraceNo;
		char AuthNum[ 13 ];
		char RefNum[ 13 ];
		char TranDate[ 7 ];
		int TranTime;
		char LocalDate[ 7 ];
		int LocalTime;
		int RespCode;
		int AuthCode;
		int CurrencyCode;
		int MCC;
		char TxnAmount[ 21 ];
		char MatchFlag;
		char MatchDesc[ 33 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR TermId IS STRING(9); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	/* EXEC SQL VAR TMSTxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR chn IS STRING(20); */ 

	/* EXEC SQL VAR TermLoc IS STRING(65); */ 

	/* EXEC SQL VAR AuthNum IS STRING(13); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR TranDate IS STRING(7); */ 

	/* EXEC SQL VAR LocalDate IS STRING(7); */ 

	/* EXEC SQL VAR TxnAmount IS STRING(21); */ 

	/* EXEC SQL VAR MatchDesc IS STRING(33); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( TermId, 0, sizeof( TermId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( BatchId, 0, sizeof( BatchId ) );
	memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
	memset( chn, 0, sizeof( chn ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( AuthNum, 0, sizeof( AuthNum ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( LocalDate, 0, sizeof( LocalDate ) );
	memset( TxnAmount, 0, sizeof( TxnAmount ) );
	memset( MatchDesc, 0, sizeof( MatchDesc ) );
	
	strcpy( InstId, txnmsg->AcquirerInst );
	strcpy( MachineId, I_MachineId );
	strcpy( TermId, txnmsg->TerminalId );
	strcpy( MerchantId, txnmsg->AcceptorId );
	strcpy( BatchId, txnmsg->BatchId );
	strcpy( TMSTxnRefNum, I_TMSTxnRefNum );
	MsgType = txnmsg->MsgType;
	TxnCode = txnmsg->TxnCode;
	strcpy( chn, txnmsg->chn );
	strcpy( TermLoc, txnmsg->TerminalLocation );
	TraceNo = txnmsg->TraceNo;
	strcpy( AuthNum, txnmsg->AuthNum );
	strcpy( RefNum, txnmsg->RefNum );
	sprintf( TranDate, "%06d", txnmsg->TranDate );
	TranTime = txnmsg->TranTime;
	sprintf( LocalDate, "%06d", txnmsg->LocalDate );
	LocalTime = txnmsg->LocalTime;
	RespCode = txnmsg->RespCode;
	AuthCode = txnmsg->AuthCode;
	CurrencyCode = txnmsg->AcqCurrencyCode;
	MCC = txnmsg->MerchantType;
	strcpy( TxnAmount, txnmsg->Amount );
	MatchFlag = I_MatchFlag;
	strcpy( MatchDesc, I_MatchDesc );
	
	/* EXEC SQL INSERT INTO EZMMSBATCHUPLOAD
	(
		INSTID,
		MACHINEID,	
		TERMID,
		MERCHANTID,
		BATCHID,
		TXNREFNUM,
		MSGTYPE,
		TXNCODE,
		CHN,
		TERMLOC,
		TRACENO,
		AUTHNUM,
		REFNUM,
		TRANDATE,
		TRANTIME,
		LOCALDATE,
		LOCALTIME,
		RESPCODE,
		AUTHCODE,
		CURRENCYCODE,
		MCC,
		TXNAMOUNT,
		MATCHFLAG,
		MATCHDESC
	)
	VALUES
	(
		:InstId,
		:MachineId,
		:TermId,
        :MerchantId,
        :BatchId,
        :TMSTxnRefNum,
        :MsgType,
        :TxnCode,
        :chn,
        :TermLoc,
        :TraceNo,
        :AuthNum,
        :RefNum,
        to_date( :TranDate, 'dd-mm-yy' ),
        :TranTime,
        to_date( :LocalDate, 'dd-mm-yy' ),
        :LocalTime,
        :RespCode,
        :AuthCode,
        :CurrencyCode,
        :MCC,
        :TxnAmount,
        :MatchFlag,
        :MatchDesc
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMMSBATCHUPLOAD (INSTID,MACHINEID,TERMID,MERCHA\
NTID,BATCHID,TXNREFNUM,MSGTYPE,TXNCODE,CHN,TERMLOC,TRACENO,AUTHNUM,REFNUM,TRAN\
DATE,TRANTIME,LOCALDATE,LOCALTIME,RESPCODE,AUTHCODE,CURRENCYCODE,MCC,TXNAMOUNT\
,MATCHFLAG,MATCHDESC) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b1\
1,:b12,to_date(:b13,'dd-mm-yy'),:b14,to_date(:b15,'dd-mm-yy'),:b16,:b17,:b18,:\
b19,:b20,:b21,:b22,:b23)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )319;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)InstId;
 sqlstm.sqhstl[0] = (unsigned long )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)MachineId;
 sqlstm.sqhstl[1] = (unsigned long )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)TermId;
 sqlstm.sqhstl[2] = (unsigned long )9;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[3] = (unsigned long )16;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)BatchId;
 sqlstm.sqhstl[4] = (unsigned long )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)TMSTxnRefNum;
 sqlstm.sqhstl[5] = (unsigned long )151;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)&MsgType;
 sqlstm.sqhstl[6] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)&TxnCode;
 sqlstm.sqhstl[7] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)chn;
 sqlstm.sqhstl[8] = (unsigned long )20;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)TermLoc;
 sqlstm.sqhstl[9] = (unsigned long )65;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)&TraceNo;
 sqlstm.sqhstl[10] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)AuthNum;
 sqlstm.sqhstl[11] = (unsigned long )13;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)RefNum;
 sqlstm.sqhstl[12] = (unsigned long )13;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)TranDate;
 sqlstm.sqhstl[13] = (unsigned long )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)&TranTime;
 sqlstm.sqhstl[14] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)LocalDate;
 sqlstm.sqhstl[15] = (unsigned long )7;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (unsigned char  *)&LocalTime;
 sqlstm.sqhstl[16] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         short *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned long )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (unsigned char  *)&RespCode;
 sqlstm.sqhstl[17] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         short *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned long )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (unsigned char  *)&AuthCode;
 sqlstm.sqhstl[18] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         short *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned long )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (unsigned char  *)&CurrencyCode;
 sqlstm.sqhstl[19] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         short *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned long )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (unsigned char  *)&MCC;
 sqlstm.sqhstl[20] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         short *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned long )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (unsigned char  *)TxnAmount;
 sqlstm.sqhstl[21] = (unsigned long )21;
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         short *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned long )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (unsigned char  *)&MatchFlag;
 sqlstm.sqhstl[22] = (unsigned long )1;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         short *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned long )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (unsigned char  *)MatchDesc;
 sqlstm.sqhstl[23] = (unsigned long )33;
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         short *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned long )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
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
            sqlstm.arrsiz = 24;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )430;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return sqlca.sqlcode;
    }
}


int readTxnAllowed( const char *I_InstId, const char *I_TerminalType, char *I_BinList, char *I_TxnList )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char BinList[ 129 ];
		char TxnList[ 129 ];
		char TerminalType[ 17 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR BinList IS STRING(129); */ 

	/* EXEC SQL VAR TerminalType IS STRING( 17 ); */ 

	/* EXEC SQL VAR TxnList IS STRING(129); */ 
	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	
	memset( TerminalType, 0, sizeof( TerminalType ) );
	strcpy( TerminalType, I_TerminalType );
	memset( BinList, 0, sizeof( BinList ) );
	memset( TxnList, 0, sizeof( TxnList ) );
	
	/* EXEC SQL SELECT 
		TRIM(BINLIST),
		TRIM(TXNLIST)
	INTO 
		:BinList,
		:TxnList
	FROM EZMMS_TERMINAL_RESTRICT WHERE TRIM(INST_ID) = :InstId AND TRIM(TERMINALTYPE) = :TerminalType; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select trim(BINLIST) ,trim(TXNLIST) into :b0,:b1  from EZMMS\
_TERMINAL_RESTRICT where (trim(INST_ID)=:b2 and trim(TERMINALTYPE)=:b3)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )445;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)BinList;
 sqlstm.sqhstl[0] = (unsigned long )129;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)TxnList;
 sqlstm.sqhstl[1] = (unsigned long )129;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)InstId;
 sqlstm.sqhstl[2] = (unsigned long )13;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)TerminalType;
 sqlstm.sqhstl[3] = (unsigned long )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
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
   	strcpy( I_BinList, BinList );
   	strcpy( I_TxnList, TxnList );
   	return sqlca.sqlcode;
}

