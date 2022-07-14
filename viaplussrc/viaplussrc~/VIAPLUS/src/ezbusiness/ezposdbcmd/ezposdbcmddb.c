
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
           char  filnam[16];
};
static struct sqlcxp sqlfpn =
{
    15,
    "ezposdbcmddb.pc"
};


static unsigned int sqlctx = 2511659;


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
            void  *sqhstv[17];
   unsigned int   sqhstl[17];
            int   sqhsts[17];
            void  *sqindv[17];
            int   sqinds[17];
   unsigned int   sqharm[17];
   unsigned int   *sqharc[17];
   unsigned short  sqadto[17];
   unsigned short  sqtdso[17];
} sqlstm = {12,17};

/* SQLLIB Prototypes */
extern sqlcxt (/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlcx2t(/*_ void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * _*/);
extern sqlbuft(/*_ void **, char * _*/);
extern sqlgs2t(/*_ void **, char * _*/);
extern sqlorat(/*_ void **, unsigned int *, void * _*/);

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem(/*_ char *, int * _*/);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,67,0,4,19,0,0,2,1,0,1,0,2,5,0,0,1,3,0,0,
28,0,0,2,92,0,4,48,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
51,0,0,3,194,0,4,88,0,0,7,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,1,5,0,0,
94,0,0,4,147,0,4,137,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
125,0,0,5,400,0,4,207,0,0,17,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,3,0,0,
2,5,0,0,1,5,0,0,
208,0,0,6,120,0,4,287,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
239,0,0,7,85,0,4,323,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
262,0,0,8,119,0,4,355,0,0,4,1,0,1,0,2,5,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
293,0,0,9,136,0,4,396,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,2,1,0,0,1,5,0,0,
328,0,0,10,128,0,4,439,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,1,5,0,0,
359,0,0,11,92,0,4,475,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
382,0,0,12,321,0,4,532,0,0,13,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,3,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,1,0,0,1,5,0,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezbusiness/ezposdbtypes.h>

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
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DESCRIPTION) into :b0  from EZPOSMCCINFO where \
MCC=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DESCRIPTION) into :b0  from EZPOSMERCHANTTYPEIN\
FO where RTRIM(MERCHANTTYPE)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )28;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 7;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(MERCHANTID) ,RTRIM(MERCHANTTYPE)\
 ,RTRIM(MERCHANTNAME) ,RTRIM(MCCLIST) ,RTRIM(TXNLIST) into :b0,:b1,:b2,:b3,:b4\
,:b5  from EZPOSMERCHANTINFO where RTRIM(MERCHANTID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )51;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 7;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DESCRIPTION) ,RTRIM(TXNCODEGROUPID) ,RTRIM(RESP\
CODEGROUPID) into :b0,:b1,:b2  from EZPOSTERMINALTYPEINFO where RTRIM(TERMINAL\
TYPE)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )94;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(TERMINALID) ,RTRIM(MERCHANTID) ,\
MCC ,RTRIM(TERMMASTERKEY) ,RTRIM(TERMPINKEY) ,RTRIM(TERMMACKEY) ,RTRIM(TERMINA\
LLOCATION) ,RTRIM(TERMINALTYPE) ,TERMINALSTATUS ,RTRIM(STOREID) ,RTRIM(ACQUIRE\
RCODE) ,CURRENCYCODE ,COUNTRYCODE ,PINCAPCODE ,RTRIM(BATCHID) into :b0,:b1,:b2\
,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15  from EZPOSTERMINAL\
INFO where RTRIM(POSID)=:b16";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )125;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(MERCHANTID) ,RTRIM(STORENAME) in\
to :b0,:b1,:b2  from EZPOSSTOREINFO where RTRIM(STOREID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )208;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TXNCODELIST) into :b0  from EZPOSTXNINFO where \
RTRIM(TXNCODEGROUPID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )239;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RESPCODEGROUPID) ,RESPCODE ,POSRESPCODE into :b\
0,:b1,:b2  from EZPOSRESPCODEINFO where RTRIM(RECORDID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )262;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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

int readEzPOSInBoundProperty( const char *I_RecordId, struct EzPOSInBoundProperty *posinboundproperty_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char MsgFlag;
		char MsgProcessFlag;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
		
	strcpy( RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(MSGTYPE),
		RTRIM(TXNCODE),
		MSGFLAG,
		MSGPROCESSFLAG
	INTO
		:MsgType,
		:TxnCode,
		:MsgFlag,
		:MsgProcessFlag
	FROM EZPOSINBOUNDPROPERTY WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(MSGTYPE) ,RTRIM(TXNCODE) ,MSGFLAG ,MSGPROCESSFL\
AG into :b0,:b1,:b2,:b3  from EZPOSINBOUNDPROPERTY where RTRIM(RECORDID)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )293;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)MsgType;
 sqlstm.sqhstl[0] = (unsigned int  )5;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnCode;
 sqlstm.sqhstl[1] = (unsigned int  )7;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&MsgFlag;
 sqlstm.sqhstl[2] = (unsigned int  )1;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&MsgProcessFlag;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)RecordId;
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

	strcpy( posinboundproperty_rec->RecordId, RecordId );
	strcpy( posinboundproperty_rec->MsgType, MsgType );
	strcpy( posinboundproperty_rec->TxnCode, TxnCode );
	posinboundproperty_rec->MsgFlag = MsgFlag;
	posinboundproperty_rec->MsgProcessFlag = MsgProcessFlag;
	
	return sqlca.sqlcode;
}

int readEzPOSRouteSelect( const char *I_RouteSelectId, struct EzPOSRouteSelect *posrouteselect_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RouteSelectId[ 17 ];
		char ChannelName[ 33 ];
		char MsgTranslateId[ 17 ];
		char LogFlag;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RouteSelectId IS STRING(17); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR MsgTranslateId IS STRING(17); */ 

	
	memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
		
	strcpy( RouteSelectId, I_RouteSelectId );
	
	/* EXEC SQL SELECT
		RTRIM(CHANNELNAME),
		RTRIM(MSGTRANSLATEID),
		LOGFLAG
	INTO
		:ChannelName,
		:MsgTranslateId,
		:LogFlag
	FROM EZPOSROUTESELECT WHERE RTRIM(ROUTESELECTID)=:RouteSelectId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(CHANNELNAME) ,RTRIM(MSGTRANSLATEID) ,LOGFLAG in\
to :b0,:b1,:b2  from EZPOSROUTESELECT where RTRIM(ROUTESELECTID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )328;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)ChannelName;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)MsgTranslateId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&LogFlag;
 sqlstm.sqhstl[2] = (unsigned int  )1;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)RouteSelectId;
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

	strcpy( posrouteselect_rec->RouteSelectId, RouteSelectId );
	strcpy( posrouteselect_rec->ChannelName, ChannelName );
	strcpy( posrouteselect_rec->MsgTranslateId, MsgTranslateId );
	posrouteselect_rec->LogFlag = LogFlag;
	
	return sqlca.sqlcode;
}

int readEzPOSMsgTranslate( const char *I_MsgTranslateId, struct EzPOSMsgTranslate *posmsgtranslate_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MsgTranslateId[ 17 ];
		char TranslateDesc[ 256 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MsgTranslateId IS STRING(17); */ 

	/* EXEC SQL VAR TranslateDesc IS STRING(256); */ 

		
	memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
	memset( TranslateDesc, 0, sizeof( TranslateDesc ) );
			
	strcpy( MsgTranslateId, I_MsgTranslateId );
	
	/* EXEC SQL SELECT
		RTRIM(TRANSLATEDESC)
	INTO
		:TranslateDesc
	FROM EZPOSMSGTRANSLATE WHERE RTRIM(MSGTRANSLATEID)=:MsgTranslateId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TRANSLATEDESC) into :b0  from EZPOSMSGTRANSLATE\
 where RTRIM(MSGTRANSLATEID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )359;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)TranslateDesc;
 sqlstm.sqhstl[0] = (unsigned int  )256;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)MsgTranslateId;
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

	strcpy( posmsgtranslate_rec->MsgTranslateId, MsgTranslateId );
	strcpy( posmsgtranslate_rec->TranslateDesc, TranslateDesc );
	
	return sqlca.sqlcode;
}

int readEzPOSRouteInfo( const char *I_RecordId, struct EzPOSRouteInfo *posrouteinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 129 ];
		char InstId[ 13 ];
		char TerminalType[ 17 ];
		char MsgType[ 65 ];
		char TxnCode[ 129 ];
		char RespCode[ 65 ];
		char RouteExp1[ 129 ];
		int RouteExpPriority1;
		char RouteExp2[ 129 ];
		int RouteExpPriority2;
		char ChannelName[ 65 ];
		char RouteSelectList[ 129 ];
		char DebugFlag;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(129); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR TerminalType IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(65); */ 

	/* EXEC SQL VAR TxnCode IS STRING(129); */ 

	/* EXEC SQL VAR RespCode IS STRING(65); */ 

	/* EXEC SQL VAR RouteExp1 IS STRING(129); */ 

	/* EXEC SQL VAR RouteExp2 IS STRING(129); */ 

	/* EXEC SQL VAR ChannelName IS STRING(65); */ 

	/* EXEC SQL VAR RouteSelectList IS STRING(129); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( TerminalType, 0, sizeof( TerminalType ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	memset( RouteExp1, 0, sizeof( RouteExp1 ) );
	memset( RouteExp2, 0, sizeof( RouteExp2 ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
		
	strcpy( RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(TERMINALTYPE),
		RTRIM(MSGTYPE),
		RTRIM(TXNCODE),
		RTRIM(RESPCODE),
		RTRIM(ROUTEEXP1),
		ROUTEEXPPRIORITY1,
		RTRIM(ROUTEEXP2),
		ROUTEEXPPRIORITY2,
		RTRIM(CHANNELNAME),
		RTRIM(ROUTESELECTLIST)
		DEBUGFLAG
	INTO
		:InstId,
		:TerminalType,
		:MsgType,
		:TxnCode,
		:RespCode,
		:RouteExp1,
		:RouteExpPriority1,
		:RouteExp2,
		:RouteExpPriority2,
		:ChannelName,
		:RouteSelectList,
		:DebugFlag
	FROM EZPOSROUTEINFO WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(TERMINALTYPE) ,RTRIM(MSGTYPE) ,R\
TRIM(TXNCODE) ,RTRIM(RESPCODE) ,RTRIM(ROUTEEXP1) ,ROUTEEXPPRIORITY1 ,RTRIM(ROU\
TEEXP2) ,ROUTEEXPPRIORITY2 ,RTRIM(CHANNELNAME) ,RTRIM(ROUTESELECTLIST) DEBUGFL\
AG into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11  from EZPOSROUTEINFO\
 where RTRIM(RECORDID)=:b12";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )382;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TerminalType;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MsgType;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TxnCode;
 sqlstm.sqhstl[3] = (unsigned int  )129;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)RespCode;
 sqlstm.sqhstl[4] = (unsigned int  )65;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)RouteExp1;
 sqlstm.sqhstl[5] = (unsigned int  )129;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&RouteExpPriority1;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)RouteExp2;
 sqlstm.sqhstl[7] = (unsigned int  )129;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&RouteExpPriority2;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)ChannelName;
 sqlstm.sqhstl[9] = (unsigned int  )65;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)RouteSelectList;
 sqlstm.sqhstl[10] = (unsigned int  )129;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&DebugFlag;
 sqlstm.sqhstl[11] = (unsigned int  )1;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)RecordId;
 sqlstm.sqhstl[12] = (unsigned int  )129;
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
		return sqlca.sqlcode;

	strcpy( posrouteinfo_rec->RecordId, RecordId );
	strcpy( posrouteinfo_rec->InstId, InstId );
	strcpy( posrouteinfo_rec->TerminalType, TerminalType );
	strcpy( posrouteinfo_rec->MsgType, MsgType );
	strcpy( posrouteinfo_rec->TxnCode, TxnCode );
	strcpy( posrouteinfo_rec->RespCode, RespCode );
	strcpy( posrouteinfo_rec->RouteExp1, RouteExp1 );
	posrouteinfo_rec->RouteExpPriority1 = RouteExpPriority1;
	strcpy( posrouteinfo_rec->RouteExp2, RouteExp2 );
	posrouteinfo_rec->RouteExpPriority2 = RouteExpPriority2;
	strcpy( posrouteinfo_rec->ChannelName, ChannelName );
	strcpy( posrouteinfo_rec->RouteSelectList, RouteSelectList );
	posrouteinfo_rec->DebugFlag = DebugFlag;
		
	return sqlca.sqlcode;
}




