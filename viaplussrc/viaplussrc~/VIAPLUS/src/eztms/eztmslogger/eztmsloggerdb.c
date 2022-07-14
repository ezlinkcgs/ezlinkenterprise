
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
    "eztmsloggerdb.pc"
};


static unsigned int sqlctx = 5063659;


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
            void  *sqhstv[28];
   unsigned int   sqhstl[28];
            int   sqhsts[28];
            void  *sqindv[28];
            int   sqinds[28];
   unsigned int   sqharm[28];
   unsigned int   *sqharc[28];
   unsigned short  sqadto[28];
   unsigned short  sqtdso[28];
} sqlstm = {12,28};

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
5,0,0,1,480,0,3,112,0,0,28,28,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,3,0,0,1,5,0,0,1,1,0,0,
132,0,0,2,0,0,29,179,0,0,0,0,0,1,0,
147,0,0,3,386,0,3,272,0,0,23,23,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,
254,0,0,4,0,0,29,329,0,0,0,0,0,1,0,
269,0,0,5,413,0,3,423,0,0,25,25,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,
0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,5,
0,0,
384,0,0,6,0,0,29,484,0,0,0,0,0,1,0,
399,0,0,7,329,0,4,525,0,0,13,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
3,0,0,2,3,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,3,0,0,2,4,0,0,1,97,0,0,
466,0,0,8,82,0,5,586,0,0,3,3,0,1,0,1,3,0,0,1,4,0,0,1,5,0,0,
493,0,0,9,0,0,29,592,0,0,0,0,0,1,0,
508,0,0,10,82,0,5,613,0,0,3,3,0,1,0,1,3,0,0,1,4,0,0,1,5,0,0,
535,0,0,11,0,0,29,619,0,0,0,0,0,1,0,
};


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlca.h>
#include <ezlink/ezlnkmsg.h>
#include <eztms/eztmsdbtypes.h>

int insertTerminalMaster( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum, const char *I_OpType )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MachineId[ 33 ];
		char TermId[ 9 ];
		char DeviceType[ 17 ];
		char MerchantId[ 16 ];
		char BatchId[ 13 ];
		char CardScheme[ 13 ];
		char TMSTxnRefNum[ 151 ];
		int MsgType;
		char TxnCode[ 7 ];
		char OpType[ 3 ];
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
		char TxnCurrency[ 5 ];
		char AcqConvRate[ 33 ];
		char AcqConvDate[ 7 ];
		int MCC;
		char TxnAmount[ 33 ];
		char TxnStatus;
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR TermId IS STRING(9); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	/* EXEC SQL VAR CardScheme IS STRING(13); */ 

	/* EXEC SQL VAR TMSTxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR OpType IS STRING(3); */ 

	/* EXEC SQL VAR chn IS STRING(20); */ 

	/* EXEC SQL VAR TermLoc IS STRING(65); */ 

	/* EXEC SQL VAR AuthNum IS STRING(13); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR TranDate IS STRING(7); */ 

	/* EXEC SQL VAR LocalDate IS STRING(7); */ 

	/* EXEC SQL VAR TxnCurrency IS STRING(5); */ 

	/* EXEC SQL VAR AcqConvRate IS STRING(33); */ 

	/* EXEC SQL VAR AcqConvDate IS STRING(7); */ 

	/* EXEC SQL VAR TxnAmount IS STRING(33); */ 

	
	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( TermId, 0, sizeof( TermId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( BatchId, 0, sizeof( BatchId ) );
	memset( CardScheme, 0, sizeof( CardScheme ) );
	memset( TMSTxnRefNum, 0, sizeof( TMSTxnRefNum ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( OpType, 0, sizeof( OpType ) );
	memset( chn, 0, sizeof( chn ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( AuthNum, 0, sizeof( AuthNum ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( LocalDate, 0, sizeof( LocalDate ) );
	memset( TxnCurrency, 0, sizeof( TxnCurrency ) );
	memset( TxnAmount, 0, sizeof( TxnAmount ) );
	
	strcpy( InstId, txnmsg->AcquirerInst );
	strcpy( MachineId, I_MachineId );
	strcpy( TermId, txnmsg->TerminalId );
	strcpy( MerchantId, txnmsg->AcceptorId );
	strcpy( DeviceType, txnmsg->DeviceType );
	strcpy( BatchId, txnmsg->BatchId );
	strcpy( CardScheme, "BPESA" );
	strcpy( TMSTxnRefNum, I_TMSTxnRefNum );
	MsgType = txnmsg->MsgType;
	sprintf( TxnCode, "%06d", txnmsg->TxnCode );
	strcpy( OpType, I_OpType );
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
	sprintf( TxnCurrency, "%03d", txnmsg->AcqCurrencyCode );
	strcpy( AcqConvRate, "1.0" );
	sprintf( AcqConvDate, "%06d", txnmsg->TranDate );
	MCC = txnmsg->MerchantType;
	strcpy( TxnAmount, txnmsg->Amount );
	TxnStatus = 'T';
	
	/* EXEC SQL INSERT INTO EZMMS_TRANSACTION
	(
		INSTID,
		MACHINEID,
		TERMID,
		MERCHANTID,
		DEVICETYPE,
		BATCHID,
		CARDSCHEME,
		TXNREFNUM,
		MSGTYPE,
		TXNCODE,
		TXNTYPE,
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
		TXNCURRENCY,
		TXNCONVRATE,
		TXNCONVDATE,
		MCC,
		TXNAMOUNT,
		TXNSTATUS
	)
	VALUES
	(
		:InstId,
		:MachineId,
		:TermId,
        :MerchantId,
        :DeviceType,
        :BatchId,
        :CardScheme,
        :TMSTxnRefNum,
        :MsgType,
        :TxnCode,
        :OpType,
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
        :TxnCurrency,
        :AcqConvRate,
        to_date( :AcqConvDate, 'dd-mm-yy' ),
        :MCC,
        :TxnAmount,
        :TxnStatus
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 28;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMMS_TRANSACTION (INSTID,MACHINEID,TERMID,MERCH\
ANTID,DEVICETYPE,BATCHID,CARDSCHEME,TXNREFNUM,MSGTYPE,TXNCODE,TXNTYPE,CHN,TERM\
LOC,TRACENO,AUTHNUM,REFNUM,TRANDATE,TRANTIME,LOCALDATE,LOCALTIME,RESPCODE,AUTH\
CODE,TXNCURRENCY,TXNCONVRATE,TXNCONVDATE,MCC,TXNAMOUNT,TXNSTATUS) values (:b0,\
:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,to_date(:b16\
,'dd-mm-yy'),:b17,to_date(:b18,'dd-mm-yy'),:b19,:b20,:b21,:b22,:b23,to_date(:b\
24,'dd-mm-yy'),:b25,:b26,:b27)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
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
 sqlstm.sqhstv[1] = (         void  *)MachineId;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TermId;
 sqlstm.sqhstl[2] = (unsigned int  )9;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MerchantId;
 sqlstm.sqhstl[3] = (unsigned int  )16;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)DeviceType;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)BatchId;
 sqlstm.sqhstl[5] = (unsigned int  )13;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)CardScheme;
 sqlstm.sqhstl[6] = (unsigned int  )13;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)TMSTxnRefNum;
 sqlstm.sqhstl[7] = (unsigned int  )151;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&MsgType;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)TxnCode;
 sqlstm.sqhstl[9] = (unsigned int  )7;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)OpType;
 sqlstm.sqhstl[10] = (unsigned int  )3;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)chn;
 sqlstm.sqhstl[11] = (unsigned int  )20;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)TermLoc;
 sqlstm.sqhstl[12] = (unsigned int  )65;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&TraceNo;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)AuthNum;
 sqlstm.sqhstl[14] = (unsigned int  )13;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)RefNum;
 sqlstm.sqhstl[15] = (unsigned int  )13;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)TranDate;
 sqlstm.sqhstl[16] = (unsigned int  )7;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&TranTime;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)LocalDate;
 sqlstm.sqhstl[18] = (unsigned int  )7;
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&LocalTime;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&RespCode;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&AuthCode;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)TxnCurrency;
 sqlstm.sqhstl[22] = (unsigned int  )5;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)AcqConvRate;
 sqlstm.sqhstl[23] = (unsigned int  )33;
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)AcqConvDate;
 sqlstm.sqhstl[24] = (unsigned int  )7;
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&MCC;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)TxnAmount;
 sqlstm.sqhstl[26] = (unsigned int  )33;
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&TxnStatus;
 sqlstm.sqhstl[27] = (unsigned int  )1;
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)0;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
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
        sqlstm.arrsiz = 28;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )132;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int insertTerminalTxnLog( const char *I_MachineId, struct EzTxnMsg *txnmsg )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MachineId[ 33 ];
		char TermId[ 9 ];
		char DeviceType[ 17 ];
		char MerchantId[ 16 ];
		char BatchId[ 13 ];
		char CardScheme[ 13 ];
		int MsgType;
		char TxnCode[ 7 ];
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
		char TxnCurrency[ 5 ];
		int MCC;
		char TxnAmount[ 33 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR TermId IS STRING(9); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	/* EXEC SQL VAR CardScheme IS STRING(13); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR chn IS STRING(20); */ 

	/* EXEC SQL VAR TermLoc IS STRING(65); */ 

	/* EXEC SQL VAR AuthNum IS STRING(13); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR TranDate IS STRING(7); */ 

	/* EXEC SQL VAR LocalDate IS STRING(7); */ 

	/* EXEC SQL VAR TxnCurrency IS STRING(5); */ 

	/* EXEC SQL VAR TxnAmount IS STRING(33); */ 

	
	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( TermId, 0, sizeof( TermId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( BatchId, 0, sizeof( BatchId ) );
	memset( CardScheme, 0, sizeof( CardScheme ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( chn, 0, sizeof( chn ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( AuthNum, 0, sizeof( AuthNum ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( TranDate, 0, sizeof( TranDate ) );
	memset( LocalDate, 0, sizeof( LocalDate ) );
	memset( TxnCurrency, 0, sizeof( TxnCurrency ) );
	memset( TxnAmount, 0, sizeof( TxnAmount ) );
	
	strcpy( InstId, txnmsg->AcquirerInst );
	strcpy( MachineId, I_MachineId );
	strcpy( TermId, txnmsg->TerminalId );
	strcpy( MerchantId, txnmsg->AcceptorId );
	strcpy( DeviceType, txnmsg->DeviceType );
	strcpy( BatchId, txnmsg->BatchId );
	strcpy( CardScheme, "BPESA" );
	MsgType = txnmsg->MsgType;
	sprintf( TxnCode, "%06d", txnmsg->TxnCode );
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
	sprintf( TxnCurrency, "%03d", txnmsg->AcqCurrencyCode );
	MCC = txnmsg->MerchantType;
	strcpy( TxnAmount, txnmsg->Amount );
	
	/* EXEC SQL INSERT INTO EZMMS_TRANSACTIONLOG
	(
		INSTID,
		MACHINEID,
		TERMID,
		MERCHANTID,
		DEVICETYPE,
		BATCHID,
		CARDSCHEME,
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
		TXNCURRENCY,
		MCC,
		TXNAMOUNT
	)
	VALUES
	(
		:InstId,
		:MachineId,
		:TermId,
        :MerchantId,
        :DeviceType,
        :BatchId,
        :CardScheme,
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
        :TxnCurrency,
        :MCC,
        :TxnAmount
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 28;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMMS_TRANSACTIONLOG (INSTID,MACHINEID,TERMID,ME\
RCHANTID,DEVICETYPE,BATCHID,CARDSCHEME,MSGTYPE,TXNCODE,CHN,TERMLOC,TRACENO,AUT\
HNUM,REFNUM,TRANDATE,TRANTIME,LOCALDATE,LOCALTIME,RESPCODE,AUTHCODE,TXNCURRENC\
Y,MCC,TXNAMOUNT) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b1\
2,:b13,to_date(:b14,'dd-mm-yy'),:b15,to_date(:b16,'dd-mm-yy'),:b17,:b18,:b19,:\
b20,:b21,:b22)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )147;
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
 sqlstm.sqhstv[1] = (         void  *)MachineId;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TermId;
 sqlstm.sqhstl[2] = (unsigned int  )9;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MerchantId;
 sqlstm.sqhstl[3] = (unsigned int  )16;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)DeviceType;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)BatchId;
 sqlstm.sqhstl[5] = (unsigned int  )13;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)CardScheme;
 sqlstm.sqhstl[6] = (unsigned int  )13;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&MsgType;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)TxnCode;
 sqlstm.sqhstl[8] = (unsigned int  )7;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)chn;
 sqlstm.sqhstl[9] = (unsigned int  )20;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)TermLoc;
 sqlstm.sqhstl[10] = (unsigned int  )65;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&TraceNo;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)AuthNum;
 sqlstm.sqhstl[12] = (unsigned int  )13;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)RefNum;
 sqlstm.sqhstl[13] = (unsigned int  )13;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)TranDate;
 sqlstm.sqhstl[14] = (unsigned int  )7;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&TranTime;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)LocalDate;
 sqlstm.sqhstl[16] = (unsigned int  )7;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&LocalTime;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&RespCode;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&AuthCode;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)TxnCurrency;
 sqlstm.sqhstl[20] = (unsigned int  )5;
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&MCC;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)TxnAmount;
 sqlstm.sqhstl[22] = (unsigned int  )33;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {
        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 28;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )254;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int insertTerminalBatchTxnInfo( const char *I_MachineId, struct EzTxnMsg *txnmsg, const char *I_TMSTxnRefNum )
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
		char TermAmount[ 21 ];
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

	/* EXEC SQL VAR TermAmount IS STRING(21); */ 

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
	memset( TermAmount, 0, sizeof( TermAmount ) );
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
	strcpy( TermAmount, txnmsg->Amount );
	MatchFlag = 'M';
	strcpy( MatchDesc, "MATCHED" );
	
	/* EXEC SQL INSERT INTO EZMMSBATCHTXNINFO
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
		TERMAMOUNT,
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
        :TermAmount,
        :MatchFlag,
        :MatchDesc
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 28;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMMSBATCHTXNINFO (INSTID,MACHINEID,TERMID,MERCH\
ANTID,BATCHID,TXNREFNUM,MSGTYPE,TXNCODE,CHN,TERMLOC,TRACENO,AUTHNUM,REFNUM,TRA\
NDATE,TRANTIME,LOCALDATE,LOCALTIME,RESPCODE,AUTHCODE,CURRENCYCODE,MCC,TXNAMOUN\
T,TERMAMOUNT,MATCHFLAG,MATCHDESC) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,\
:b9,:b10,:b11,:b12,to_date(:b13,'dd-mm-yy'),:b14,to_date(:b15,'dd-mm-yy'),:b16\
,:b17,:b18,:b19,:b20,:b21,:b22,:b23,:b24)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )269;
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
 sqlstm.sqhstv[1] = (         void  *)MachineId;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TermId;
 sqlstm.sqhstl[2] = (unsigned int  )9;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MerchantId;
 sqlstm.sqhstl[3] = (unsigned int  )16;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)BatchId;
 sqlstm.sqhstl[4] = (unsigned int  )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)TMSTxnRefNum;
 sqlstm.sqhstl[5] = (unsigned int  )151;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&MsgType;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&TxnCode;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)chn;
 sqlstm.sqhstl[8] = (unsigned int  )20;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)TermLoc;
 sqlstm.sqhstl[9] = (unsigned int  )65;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&TraceNo;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)AuthNum;
 sqlstm.sqhstl[11] = (unsigned int  )13;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)RefNum;
 sqlstm.sqhstl[12] = (unsigned int  )13;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)TranDate;
 sqlstm.sqhstl[13] = (unsigned int  )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&TranTime;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)LocalDate;
 sqlstm.sqhstl[15] = (unsigned int  )7;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&LocalTime;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&RespCode;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&AuthCode;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&CurrencyCode;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&MCC;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)TxnAmount;
 sqlstm.sqhstl[21] = (unsigned int  )21;
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)TermAmount;
 sqlstm.sqhstl[22] = (unsigned int  )21;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&MatchFlag;
 sqlstm.sqhstl[23] = (unsigned int  )1;
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)MatchDesc;
 sqlstm.sqhstl[24] = (unsigned int  )33;
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
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
            sqlstm.arrsiz = 28;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )384;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return sqlca.sqlcode;
    }
}

int readTerminalBatchInfo( const char *I_MachineId, struct EzTerminalBatchInfo *terminalbatchinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char BatchId[ 13 ];
		char InstId[ 13 ];
		char MachineId[ 33 ];
		char Termid[ 9 ];
		char MerchantId[ 16 ];
		char OpenDate[ 7 ];
		int OpenTime;
		char OpenSource;
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
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( OpenDate, 0, sizeof( OpenDate ) );
	
	strcpy( MachineId, I_MachineId );
	
	/* EXEC SQL SELECT 
		RTRIM(INSTID),
		RTRIM(BATCHID),
		RTRIM(TERMID),
		RTRIM(MERCHANTID),
		TO_CHAR(OPENDATE, 'DDMMYY' ),
		OPENTIME,
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
		:SaleCount:ind_var,
		:SaleAmount:ind_var,
		:VoidCount:ind_var,
		:VoidAmount:ind_var,
		:AuthCount:ind_var,
		:AuthAmount:ind_var
	FROM EZMMSBATCHINFO WHERE RTRIM(MACHINEID) =:I_MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 28;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(BATCHID) ,RTRIM(TERMID) ,RTRIM(M\
ERCHANTID) ,TO_CHAR(OPENDATE,'DDMMYY') ,OPENTIME ,SALECOUNT ,SALEAMOUNT ,VOIDC\
OUNT ,VOIDAMOUNT ,AUTHCOUNT ,AUTHAMOUNT into :b0:b1,:b2:b3,:b4:b5,:b6:b7,:b8:b\
9,:b10:b11,:b12:b13,:b14:b15,:b16:b17,:b18:b19,:b20:b21,:b22:b23  from EZMMSBA\
TCHINFO where RTRIM(MACHINEID)=:b24";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )399;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)BatchId;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)Termid;
 sqlstm.sqhstl[2] = (unsigned int  )9;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MerchantId;
 sqlstm.sqhstl[3] = (unsigned int  )16;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)OpenDate;
 sqlstm.sqhstl[4] = (unsigned int  )7;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&OpenTime;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)&ind_var;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&SaleCount;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)&ind_var;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&SaleAmount;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)&ind_var;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&VoidCount;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)&ind_var;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&VoidAmount;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)&ind_var;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&AuthCount;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)&ind_var;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&AuthAmount;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)&ind_var;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)I_MachineId;
 sqlstm.sqhstl[12] = (unsigned int  )0;
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

 
	
	if( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( terminalbatchinfo_rec->MachineId, MachineId );
	strcpy( terminalbatchinfo_rec->BatchId, BatchId );
	strcpy( terminalbatchinfo_rec->Termid, Termid );
	strcpy( terminalbatchinfo_rec->MerchantId, MerchantId );
	strcpy( terminalbatchinfo_rec->OpenDate, OpenDate );
	terminalbatchinfo_rec->OpenTime = OpenTime;
	terminalbatchinfo_rec->SaleCount = SaleCount;
	terminalbatchinfo_rec->SaleAmount = SaleAmount;
	terminalbatchinfo_rec->VoidCount = VoidCount;
	terminalbatchinfo_rec->VoidAmount = VoidAmount;
	terminalbatchinfo_rec->AuthCount = AuthCount;
	terminalbatchinfo_rec->AuthAmount = AuthAmount;
	return sqlca.sqlcode;
}

int updateSaleTxn( const char *I_MachineId, double I_TxnAmount, int I_TxnCount )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MachineId[ 33 ];
		double TxnAmount;
		int TxnCount;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	strcpy( MachineId, I_MachineId );
	TxnAmount = I_TxnAmount;
	TxnCount = I_TxnCount;
	
	/* EXEC SQL UPDATE EZMMSBATCHINFO SET SALECOUNT = :TxnCount, SALEAMOUNT = :TxnAmount WHERE RTRIM(MACHINEID) = :MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 28;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZMMSBATCHINFO  set SALECOUNT=:b0,SALEAMOUNT=:b1 wher\
e RTRIM(MACHINEID)=:b2";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )466;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&TxnCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&TxnAmount;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MachineId;
 sqlstm.sqhstl[2] = (unsigned int  )33;
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
     sqlstm.arrsiz = 28;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )493;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        if( sqlca.sqlcode != 0 )
	   		return sqlca.sqlcode;
	}
}

int updateVoidTxn( const char *I_MachineId, double I_TxnAmount, int I_TxnCount )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MachineId[ 33 ];
		double TxnAmount;
		int TxnCount;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	strcpy( MachineId, I_MachineId );
	TxnAmount = I_TxnAmount;
	TxnCount = I_TxnCount;
	
	/* EXEC SQL UPDATE EZMMSBATCHINFO SET VOIDCOUNT = :TxnCount, VOIDAMOUNT = :TxnAmount WHERE RTRIM(MACHINEID) = :MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 28;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZMMSBATCHINFO  set VOIDCOUNT=:b0,VOIDAMOUNT=:b1 wher\
e RTRIM(MACHINEID)=:b2";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )508;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&TxnCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&TxnAmount;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MachineId;
 sqlstm.sqhstl[2] = (unsigned int  )33;
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
     sqlstm.arrsiz = 28;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )535;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        if( sqlca.sqlcode != 0 )
	   		return sqlca.sqlcode;
	}
}
