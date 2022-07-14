
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
    "ezmmscmddb.pc"
};


static unsigned int sqlctx = 624171;


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
   unsigned char  *sqhstv[18];
   unsigned long  sqhstl[18];
            int   sqhsts[18];
            short *sqindv[18];
            int   sqinds[18];
   unsigned long  sqharm[18];
   unsigned long  *sqharc[18];
   unsigned short  sqadto[18];
   unsigned short  sqtdso[18];
} sqlstm = {12,18};

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
5,0,0,1,617,0,4,64,0,0,17,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,1,
5,0,0,1,5,0,0,
88,0,0,2,192,0,4,142,0,0,5,2,0,1,0,2,5,0,0,2,1,0,0,2,3,0,0,1,5,0,0,1,5,0,0,
123,0,0,3,611,0,4,220,0,0,18,3,0,1,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
97,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,
210,0,0,4,547,0,4,333,0,0,16,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
1,5,0,0,
289,0,0,5,155,0,4,415,0,0,6,3,0,1,0,2,5,0,0,2,1,0,0,2,3,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezmms/ezmmsdbtypes.h>

int readEzMMSMerchantProfile( const char *I_InstId, const char *I_MerchantId, struct EzMMSMerchantProfile *merchantprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char MCCList[ 33 ];
		char MerchantTypeId[ 17 ];
		char ParentMerchantId[ 16 ];
		char MerchantName[ 33 ];
		char Addr1[ 65 ];
		char Addr2[ 65 ];
		char Status;
		char DOB[ 11 ];
		char PMobileNo[ 17 ];
		char SMobileNo[ 17 ];
		char PMailAddr[ 33 ];
		char SMailAddr[ 33 ];
		char SettCurrCode[ 5 ];
		char CurrList[ 33 ];
		char CardIssuanceFlag;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR MCCList IS STRING(33); */ 

	/* EXEC SQL VAR MerchantTypeId IS STRING(17); */ 

	/* EXEC SQL VAR ParentMerchantId IS STRING(16); */ 

	/* EXEC SQL VAR MerchantName IS STRING(33); */ 

	/* EXEC SQL VAR Addr1 IS STRING(65); */ 

	/* EXEC SQL VAR Addr2 IS STRING(65); */ 

	/* EXEC SQL VAR DOB IS STRING(11); */ 

	/* EXEC SQL VAR PMobileNo IS STRING(17); */ 

	/* EXEC SQL VAR SMobileNo IS STRING(17); */ 

	/* EXEC SQL VAR PMailAddr IS STRING(33); */ 

	/* EXEC SQL VAR SMailAddr IS STRING(33); */ 

	/* EXEC SQL VAR SettCurrCode IS STRING(5); */ 

	/* EXEC SQL VAR CurrList IS STRING(33); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( MCCList, 0, sizeof( MCCList ) );
	memset( MerchantTypeId, 0, sizeof( MerchantTypeId ) );
	memset( ParentMerchantId, 0, sizeof( ParentMerchantId ) );
	memset( MerchantName, 0, sizeof( MerchantName ) );
	memset( Addr1, 0, sizeof( Addr1 ) );
	memset( Addr2, 0, sizeof( Addr2 ) );
	memset( DOB, 0, sizeof( DOB ) );
	memset( PMobileNo, 0, sizeof( PMobileNo ) );
	memset( SMobileNo, 0, sizeof( SMobileNo ) );
	memset( PMailAddr, 0, sizeof( PMailAddr ) );
	memset( SMailAddr, 0, sizeof( SMailAddr ) );
	memset( SettCurrCode, 0, sizeof( SettCurrCode ) );
	memset( CurrList, 0, sizeof( CurrList ) );
	
	strcpy( InstId, I_InstId );
	strcpy( MerchantId, I_MerchantId );
	
	/* EXEC SQL SELECT
		RTRIM( NVL( MCC_LIST, 'NA' ) ),
    	RTRIM( NVL( MERCH_TYPE_ID, 'NA' ) ),
    	RTRIM( NVL( PARENT_MERCH_ID, 'NA' ) ),
    	RTRIM( NVL( MERCH_NAME, 'NA' ) ),
    	RTRIM( NVL( PRIM_MAIL_ADDR, 'NA' ) ),
    	RTRIM( NVL( SEC_MAIL_ADDR, 'NA' ) ),
    	NVL( STATUS, '0' ),
    	RTRIM( NVL( TO_CHAR(DOB, 'DD-MM-YY' ), 'NA' ) ),
    	RTRIM( NVL( PRIM_MOBILE_NO, 'NA' ) ),
    	RTRIM( NVL( SEC_MOBILE_NO, 'NA' ) ),
    	RTRIM( NVL( PRIM_EMAIL_ID, 'NA' ) ),
    	RTRIM( NVL( SEC_EMAIL_ID, 'NA' ) ),
    	RTRIM( NVL( SETT_CURR_CODE, 'NA' ) ),
    	RTRIM( NVL( CURR_LIST, 'NA' ) ),
    	NVL( CARD_ISSUED_FLAG, 'N' )
	INTO
		:MCCList,
		:MerchantTypeId,
		:ParentMerchantId,
		:MerchantName,
		:Addr1,
		:Addr2,
		:Status,
		:DOB,
		:PMobileNo,
		:SMobileNo,
		:PMailAddr,
		:SMailAddr,
		:SettCurrCode,
		:CurrList,
		:CardIssuanceFlag
	FROM EZMMSMERCHANTPROFILE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID)=:MerchantId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NVL(MCC_LIST,'NA')) ,RTRIM(NVL(MERCH_TYPE_ID,'N\
A')) ,RTRIM(NVL(PARENT_MERCH_ID,'NA')) ,RTRIM(NVL(MERCH_NAME,'NA')) ,RTRIM(NVL\
(PRIM_MAIL_ADDR,'NA')) ,RTRIM(NVL(SEC_MAIL_ADDR,'NA')) ,NVL(STATUS,'0') ,RTRIM\
(NVL(TO_CHAR(DOB,'DD-MM-YY'),'NA')) ,RTRIM(NVL(PRIM_MOBILE_NO,'NA')) ,RTRIM(NV\
L(SEC_MOBILE_NO,'NA')) ,RTRIM(NVL(PRIM_EMAIL_ID,'NA')) ,RTRIM(NVL(SEC_EMAIL_ID\
,'NA')) ,RTRIM(NVL(SETT_CURR_CODE,'NA')) ,RTRIM(NVL(CURR_LIST,'NA')) ,NVL(CARD\
_ISSUED_FLAG,'N') into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,\
:b13,:b14  from EZMMSMERCHANTPROFILE where (RTRIM(INST_ID)=:b15 and RTRIM(MERC\
H_ID)=:b16)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)MCCList;
 sqlstm.sqhstl[0] = (unsigned long )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)MerchantTypeId;
 sqlstm.sqhstl[1] = (unsigned long )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)ParentMerchantId;
 sqlstm.sqhstl[2] = (unsigned long )16;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)MerchantName;
 sqlstm.sqhstl[3] = (unsigned long )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)Addr1;
 sqlstm.sqhstl[4] = (unsigned long )65;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)Addr2;
 sqlstm.sqhstl[5] = (unsigned long )65;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)&Status;
 sqlstm.sqhstl[6] = (unsigned long )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)DOB;
 sqlstm.sqhstl[7] = (unsigned long )11;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)PMobileNo;
 sqlstm.sqhstl[8] = (unsigned long )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)SMobileNo;
 sqlstm.sqhstl[9] = (unsigned long )17;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)PMailAddr;
 sqlstm.sqhstl[10] = (unsigned long )33;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)SMailAddr;
 sqlstm.sqhstl[11] = (unsigned long )33;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)SettCurrCode;
 sqlstm.sqhstl[12] = (unsigned long )5;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)CurrList;
 sqlstm.sqhstl[13] = (unsigned long )33;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)&CardIssuanceFlag;
 sqlstm.sqhstl[14] = (unsigned long )1;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)InstId;
 sqlstm.sqhstl[15] = (unsigned long )13;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[16] = (unsigned long )16;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         short *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned long )0;
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
	
	strcpy( merchantprofile_ptr->InstId, InstId );
    strcpy( merchantprofile_ptr->MerchantId, MerchantId );
    strcpy( merchantprofile_ptr->MCCList, MCCList );
    strcpy( merchantprofile_ptr->MerchantTypeId, MerchantTypeId );
    strcpy( merchantprofile_ptr->ParentMerchantId, ParentMerchantId );
  	strcpy( merchantprofile_ptr->MerchantName, MerchantName );
  	strcpy( merchantprofile_ptr->Addr1, Addr1 );
  	strcpy( merchantprofile_ptr->Addr2, Addr2 );
  	merchantprofile_ptr->Status = Status;
  	strcpy( merchantprofile_ptr->DOB, DOB );
  	strcpy( merchantprofile_ptr->PMobileNo, PMobileNo );
  	strcpy( merchantprofile_ptr->SMobileNo, SMobileNo );
  	strcpy( merchantprofile_ptr->PMailAddr, PMailAddr );
  	strcpy( merchantprofile_ptr->SMailAddr, SMailAddr );
  	strcpy( merchantprofile_ptr->SettCurrCode, SettCurrCode );
  	strcpy( merchantprofile_ptr->CurrList, CurrList );
  	merchantprofile_ptr->CardIssuanceFlag = CardIssuanceFlag;
	return sqlca.sqlcode;
}

int readEzMMSMerchantType( const char *I_InstId, const char *I_MerchantTypeId, struct EzMMSMerchantType *merchanttype_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantTypeId[ 17 ];
		char TxnAllowed[ 65 ];
		char LoyaltyReq;
		int MaxPINRetryCount;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantTypeId IS STRING(17); */ 

	/* EXEC SQL VAR TxnAllowed IS STRING(65); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantTypeId, 0, sizeof( MerchantTypeId ) );
	memset( TxnAllowed, 0, sizeof( TxnAllowed ) );
	
	strcpy( InstId, I_InstId );
	strcpy( MerchantTypeId, I_MerchantTypeId );
	
	/* EXEC SQL SELECT
		RTRIM( NVL( TXN_ALLOWED, 'NA' ) ),
    	NVL( LOYALTY_PGM_REQ, 'N' ),
    	NVL( MAX_PIN_RETRY_COUNT, '3' )
	INTO
		:TxnAllowed,
		:LoyaltyReq,
		:MaxPINRetryCount
	FROM EZMMS_MERCHANTTYPE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCHANT_TYPE_ID)=:MerchantTypeId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NVL(TXN_ALLOWED,'NA')) ,NVL(LOYALTY_PGM_REQ,'N'\
) ,NVL(MAX_PIN_RETRY_COUNT,'3') into :b0,:b1,:b2  from EZMMS_MERCHANTTYPE wher\
e (RTRIM(INST_ID)=:b3 and RTRIM(MERCHANT_TYPE_ID)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )88;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)TxnAllowed;
 sqlstm.sqhstl[0] = (unsigned long )65;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)&LoyaltyReq;
 sqlstm.sqhstl[1] = (unsigned long )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)&MaxPINRetryCount;
 sqlstm.sqhstl[2] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)InstId;
 sqlstm.sqhstl[3] = (unsigned long )13;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)MerchantTypeId;
 sqlstm.sqhstl[4] = (unsigned long )17;
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


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( merchanttype_ptr->InstId, InstId );
    strcpy( merchanttype_ptr->MerchantTypeId, MerchantTypeId );
    strcpy( merchanttype_ptr->TxnAllowed, TxnAllowed );
    merchanttype_ptr->LoyaltyReq = LoyaltyReq;
  	merchanttype_ptr->MaxPINRetryCount = MaxPINRetryCount;
	return sqlca.sqlcode;
}

int readEzMMSStoreProfile( const char *I_InstId, const char *I_MerchantId, const char *I_StoreId, struct EzMMSStoreProfile *storeprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char Status;
		char StoreName[ 33 ];
		char StoreLocation[ 65 ];
		char CityName[ 33 ];
		char CityCode[ 17 ];
		char StateName[ 33 ];
		char CountryName[ 33 ];
		char LandLine1[ 17 ];
		char LandLine2[ 17 ];
		char PMobileNo[ 17 ];
		char SMobileNo[ 17 ];
		int WorkingHrs;
		char OpeningTime[ 7 ];
		char ClosingTime[ 7 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR StoreName IS STRING(33); */ 

	/* EXEC SQL VAR StoreLocation IS STRING(65); */ 

	/* EXEC SQL VAR CityName IS STRING(33); */ 

	/* EXEC SQL VAR StateName IS STRING(33); */ 

	/* EXEC SQL VAR CountryName IS STRING(33); */ 

	/* EXEC SQL VAR LandLine1 IS STRING(17); */ 

	/* EXEC SQL VAR LandLine2 IS STRING(17); */ 

	/* EXEC SQL VAR PMobileNo IS STRING(17); */ 

	/* EXEC SQL VAR SMobileNo IS STRING(17); */ 

	/* EXEC SQL VAR OpeningTime IS STRING(7); */ 

	/* EXEC SQL VAR ClosingTime IS STRING(7); */ 

		
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( StoreName, 0, sizeof( StoreName ) );
	memset( StoreLocation, 0, sizeof( StoreLocation ) );
	memset( CityName, 0, sizeof( CityName ) );
	memset( CityCode, 0, sizeof( CityCode ) );
	memset( StateName, 0, sizeof( StateName ) );
	memset( CountryName, 0, sizeof( CountryName ) );
	memset( LandLine1, 0, sizeof( LandLine1 ) );
	memset( LandLine2, 0, sizeof( LandLine2 ) );
	memset( PMobileNo, 0, sizeof( PMobileNo ) );
	memset( SMobileNo, 0, sizeof( SMobileNo ) );
	memset( OpeningTime, 0, sizeof( OpeningTime ) );
	memset( ClosingTime, 0, sizeof( ClosingTime ) );
	
	strcpy( InstId, I_InstId );
	strcpy( MerchantId, I_MerchantId );
	strcpy( StoreId, I_StoreId );
	
	/* EXEC SQL SELECT
		NVL( STORE_STATUS, '0' ),
    	RTRIM( NVL( STORE_NAME, 'NA' ) ),
    	RTRIM( NVL( STORE_LOCATION, 'NA' ) ),
    	RTRIM( NVL( CITY_NAME, 'NA' ) ),
    	RTRIM( NVL( CITY_CODE, 'NA' ) ),
    	RTRIM( NVL( STATE_NAME, 'NA' ) ),
    	RTRIM( NVL( COUNTRY_NAME, 'NA' ) ),
    	RTRIM( NVL( PRIM_LAND_LINE_NO, 'NA' ) ),
    	RTRIM( NVL( SEC_LAND_LINE_NO, 'NA' ) ),
    	RTRIM( NVL( PRIM_MOBILE_NUM, 'NA' ) ),
    	RTRIM( NVL( SEC_MOBILE_NUM, 'NA' ) ),
    	NVL( WORKING_HRS, '24' ),
    	RTRIM( NVL( OPENING_TIME, '000000' ) ),
    	RTRIM( NVL( CLOSING_TIME, '235959' ) )
	INTO
		:StoreId,
		:Status,
		:StoreName,
		:StoreLocation,
		:CityName,
		:CityCode,
		:StateName,
		:CountryName,
		:LandLine1,
		:LandLine2,
		:PMobileNo,
		:SMobileNo,
		:WorkingHrs,
		:OpeningTime,
		:ClosingTime
	FROM EZMMS_STOREPROFILE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID)=:MerchantId AND RTRIM(STORE_ID)=:StoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 18;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select NVL(STORE_STATUS,'0') ,RTRIM(NVL(STORE_NAME,'NA')) ,R\
TRIM(NVL(STORE_LOCATION,'NA')) ,RTRIM(NVL(CITY_NAME,'NA')) ,RTRIM(NVL(CITY_COD\
E,'NA')) ,RTRIM(NVL(STATE_NAME,'NA')) ,RTRIM(NVL(COUNTRY_NAME,'NA')) ,RTRIM(NV\
L(PRIM_LAND_LINE_NO,'NA')) ,RTRIM(NVL(SEC_LAND_LINE_NO,'NA')) ,RTRIM(NVL(PRIM_\
MOBILE_NUM,'NA')) ,RTRIM(NVL(SEC_MOBILE_NUM,'NA')) ,NVL(WORKING_HRS,'24') ,RTR\
IM(NVL(OPENING_TIME,'000000')) ,RTRIM(NVL(CLOSING_TIME,'235959')) into :b0,:b1\
,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14  from EZMMS_STOREPRO\
FILE where ((RTRIM(INST_ID)=:b15 and RTRIM(MERCH_ID)=:b16) and RTRIM(STORE_ID)\
=:b0)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )123;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)StoreId;
 sqlstm.sqhstl[0] = (unsigned long )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)&Status;
 sqlstm.sqhstl[1] = (unsigned long )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)StoreName;
 sqlstm.sqhstl[2] = (unsigned long )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)StoreLocation;
 sqlstm.sqhstl[3] = (unsigned long )65;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)CityName;
 sqlstm.sqhstl[4] = (unsigned long )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)CityCode;
 sqlstm.sqhstl[5] = (unsigned long )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)StateName;
 sqlstm.sqhstl[6] = (unsigned long )33;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)CountryName;
 sqlstm.sqhstl[7] = (unsigned long )33;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)LandLine1;
 sqlstm.sqhstl[8] = (unsigned long )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)LandLine2;
 sqlstm.sqhstl[9] = (unsigned long )17;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)PMobileNo;
 sqlstm.sqhstl[10] = (unsigned long )17;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)SMobileNo;
 sqlstm.sqhstl[11] = (unsigned long )17;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)&WorkingHrs;
 sqlstm.sqhstl[12] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)OpeningTime;
 sqlstm.sqhstl[13] = (unsigned long )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)ClosingTime;
 sqlstm.sqhstl[14] = (unsigned long )7;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)InstId;
 sqlstm.sqhstl[15] = (unsigned long )13;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[16] = (unsigned long )16;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         short *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned long )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (unsigned char  *)StoreId;
 sqlstm.sqhstl[17] = (unsigned long )33;
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         short *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned long )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
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
	
	strcpy( storeprofile_ptr->InstId, InstId );
    strcpy( storeprofile_ptr->MerchantId, MerchantId );
    strcpy( storeprofile_ptr->StoreId, StoreId );
    storeprofile_ptr->Status = Status;
    strcpy( storeprofile_ptr->StoreName, StoreName );
    strcpy( storeprofile_ptr->StoreLocation, StoreLocation );
    strcpy( storeprofile_ptr->CityName, CityName );
    strcpy( storeprofile_ptr->CityCode, CityCode );
    strcpy( storeprofile_ptr->StateName, StateName );
    strcpy( storeprofile_ptr->CountryName, CountryName );
    strcpy( storeprofile_ptr->LandLine1, LandLine1 );
    strcpy( storeprofile_ptr->LandLine2, LandLine2 );
    strcpy( storeprofile_ptr->PMobileNo, PMobileNo );
    strcpy( storeprofile_ptr->SMobileNo, SMobileNo );
    storeprofile_ptr->WorkingHrs = WorkingHrs;
    strcpy( storeprofile_ptr->OpeningTime, OpeningTime );
    strcpy( storeprofile_ptr->ClosingTime, ClosingTime );
	return sqlca.sqlcode;
}

int readEzMMSTerminalProfile( const char *I_MachineId, struct EzMMSTerminalProfile *terminalprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MachineId[ 33 ];
		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char TerminalId[ 9 ];
		char TerminalName[ 33 ];
		char TermLocation[ 65 ];
		char TerminalStatus;
		int WorkingHrs;
		char OpeningTime[ 7 ];
		char ClosingTime[ 7 ];
		char CountryCode[ 5 ];
		char ChipEnabled;
		char TermMasterKey[ 65 ];
		char TermPINKey[ 65 ];
		char TermMACKey[ 65 ];
		char BatchId[ 13 ];
		char TermBatchId[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR TerminalId IS STRING(9); */ 

	/* EXEC SQL VAR TerminalName IS STRING(33); */ 

	/* EXEC SQL VAR TermLocation IS STRING(65); */ 

	/* EXEC SQL VAR OpeningTime IS STRING(7); */ 

	/* EXEC SQL VAR ClosingTime IS STRING(7); */ 

	/* EXEC SQL VAR CountryCode IS STRING(5); */ 

	/* EXEC SQL VAR TermMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR TermPINKey IS STRING(65); */ 

	/* EXEC SQL VAR TermMACKey IS STRING(65); */ 

	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	/* EXEC SQL VAR TermBatchId IS STRING(13); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( TerminalName, 0, sizeof( TerminalName ) );
	memset( TermLocation, 0, sizeof( TermLocation ) );
	memset( OpeningTime, 0, sizeof( OpeningTime ) );
	memset( ClosingTime, 0, sizeof( ClosingTime ) );
	memset( CountryCode, 0, sizeof( CountryCode ) );
	memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
	memset( TermPINKey, 0, sizeof( TermPINKey ) );
	memset( TermMACKey, 0, sizeof( TermMACKey ) );
	memset( BatchId, 0, sizeof( BatchId ) );
	memset( TermBatchId, 0, sizeof( TermBatchId ) );
	
	strcpy( MachineId, I_MachineId );
	
	/* EXEC SQL SELECT
		RTRIM(INST_ID),
    	RTRIM(MERCH_ID),
    	RTRIM(STORE_ID),
    	RTRIM(TERMINAL_ID),
    	RTRIM( NVL( TERMINAL_NAME, 'NA' ) ),
    	RTRIM( NVL( TERMINAL_LOCATION, 'NA' ) ),
    	NVL( TERMINAL_STATUS, '0' ),
    	NVL( WORKING_HRS, '24' ),
    	RTRIM( NVL( OPENING_TIME, '000000' ) ),
    	RTRIM( NVL( CLOSING_TIME, '235959' ) ),
    	RTRIM(COUNTRY_CODE),
    	NVL( CHIP_ENABLED, 'N' ),
    	RTRIM( TERM_MASTER_KEY ),
    	NVL( RTRIM( TERM_PIN_KEY, '1111111111111111' ) ),
    	NVL( RTRIM( TERM_MAC_KEY, '1111111111111111' ) )
    INTO
		:InstId,
		:MerchantId,
		:StoreId,
		:TerminalId,
		:TerminalName,
		:TermLocation,
		:TerminalStatus,
		:WorkingHrs,
		:OpeningTime,
		:ClosingTime,
		:CountryCode,
		:ChipEnabled,
		:TermMasterKey,
		:TermPINKey,
		:TermMACKey
	FROM EZMMS_TERMINALPROFILE WHERE RTRIM(MACHINE_ID) = :MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 18;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INST_ID) ,RTRIM(MERCH_ID) ,RTRIM(STORE_ID) ,RTR\
IM(TERMINAL_ID) ,RTRIM(NVL(TERMINAL_NAME,'NA')) ,RTRIM(NVL(TERMINAL_LOCATION,'\
NA')) ,NVL(TERMINAL_STATUS,'0') ,NVL(WORKING_HRS,'24') ,RTRIM(NVL(OPENING_TIME\
,'000000')) ,RTRIM(NVL(CLOSING_TIME,'235959')) ,RTRIM(COUNTRY_CODE) ,NVL(CHIP_\
ENABLED,'N') ,RTRIM(TERM_MASTER_KEY) ,NVL(RTRIM(TERM_PIN_KEY,'1111111111111111\
')) ,NVL(RTRIM(TERM_MAC_KEY,'1111111111111111')) into :b0,:b1,:b2,:b3,:b4,:b5,\
:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14  from EZMMS_TERMINALPROFILE where RTR\
IM(MACHINE_ID)=:b15";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )210;
 sqlstm.selerr = (unsigned short)1;
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
 sqlstm.sqhstv[1] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[1] = (unsigned long )16;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)StoreId;
 sqlstm.sqhstl[2] = (unsigned long )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)TerminalId;
 sqlstm.sqhstl[3] = (unsigned long )9;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)TerminalName;
 sqlstm.sqhstl[4] = (unsigned long )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)TermLocation;
 sqlstm.sqhstl[5] = (unsigned long )65;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)&TerminalStatus;
 sqlstm.sqhstl[6] = (unsigned long )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)&WorkingHrs;
 sqlstm.sqhstl[7] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)OpeningTime;
 sqlstm.sqhstl[8] = (unsigned long )7;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)ClosingTime;
 sqlstm.sqhstl[9] = (unsigned long )7;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)CountryCode;
 sqlstm.sqhstl[10] = (unsigned long )5;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)&ChipEnabled;
 sqlstm.sqhstl[11] = (unsigned long )1;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)TermMasterKey;
 sqlstm.sqhstl[12] = (unsigned long )65;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)TermPINKey;
 sqlstm.sqhstl[13] = (unsigned long )65;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)TermMACKey;
 sqlstm.sqhstl[14] = (unsigned long )65;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)MachineId;
 sqlstm.sqhstl[15] = (unsigned long )33;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
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
	
	strcpy( terminalprofile_ptr->MachineId, MachineId );
	strcpy( terminalprofile_ptr->InstId, InstId );
    strcpy( terminalprofile_ptr->MerchantId, MerchantId );
    strcpy( terminalprofile_ptr->StoreId, StoreId );
    strcpy( terminalprofile_ptr->TerminalId, TerminalId );
    strcpy( terminalprofile_ptr->TerminalName, TerminalName );
    strcpy( terminalprofile_ptr->TerminalLocation, TermLocation );
    terminalprofile_ptr->TerminalStatus = TerminalStatus;
    terminalprofile_ptr->WorkingHrs = WorkingHrs;
    strcpy( terminalprofile_ptr->OpeningTime, OpeningTime );
    strcpy( terminalprofile_ptr->ClosingTime, ClosingTime );
	strcpy( terminalprofile_ptr->CountryCode, CountryCode );
	terminalprofile_ptr->ChipEnabled = ChipEnabled;
	strcpy( terminalprofile_ptr->TermMasterKey, TermMasterKey );
	strcpy( terminalprofile_ptr->TermPINKey, TermPINKey );
	strcpy( terminalprofile_ptr->TermMACKey, TermMACKey );
	
	return sqlca.sqlcode;
}

int readEzMMSMerchantRelation( const char *I_InstId, const char *I_MerchantId, const char *I_AccountNo, struct EzMMSMerchantRelation *merchantrelation_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char AccountNo[ 33 ];
		char CurrCode[ 5 ];
		char AccountStatus;
		short AccountPriority;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR AccountNo IS STRING(33); */ 

	/* EXEC SQL VAR CurrCode IS STRING(5); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( AccountNo, 0, sizeof( AccountNo ) );
	memset( CurrCode, 0, sizeof( CurrCode ) );
	
	strcpy( InstId, I_InstId );
	strcpy( MerchantId, I_MerchantId );
	strcpy( AccountNo, I_AccountNo );
		
	/* EXEC SQL SELECT
		RTRIM(CURR_CODE),
    	STATUS,
    	PRIORITY
    INTO
		:CurrCode,
		:AccountStatus,
		:AccountPriority
	FROM EZMMS_RELATION WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID) = :MerchantId AND RTRIM(ACCT_NO) = :AccountNo; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 18;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(CURR_CODE) ,STATUS ,PRIORITY into :b0,:b1,:b2  \
from EZMMS_RELATION where ((RTRIM(INST_ID)=:b3 and RTRIM(MERCH_ID)=:b4) and RT\
RIM(ACCT_NO)=:b5)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )289;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)CurrCode;
 sqlstm.sqhstl[0] = (unsigned long )5;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)&AccountStatus;
 sqlstm.sqhstl[1] = (unsigned long )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)&AccountPriority;
 sqlstm.sqhstl[2] = (unsigned long )sizeof(short);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)InstId;
 sqlstm.sqhstl[3] = (unsigned long )13;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[4] = (unsigned long )16;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)AccountNo;
 sqlstm.sqhstl[5] = (unsigned long )33;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
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
	
	strcpy( merchantrelation_ptr->InstId, InstId );
    strcpy( merchantrelation_ptr->MerchantId, MerchantId );
    strcpy( merchantrelation_ptr->AccountNo, AccountNo );
    strcpy( merchantrelation_ptr->CurrCode, CurrCode );
    merchantrelation_ptr->AccountStatus = AccountStatus;
    merchantrelation_ptr->AccountPriority = AccountPriority;
	return sqlca.sqlcode;
}


