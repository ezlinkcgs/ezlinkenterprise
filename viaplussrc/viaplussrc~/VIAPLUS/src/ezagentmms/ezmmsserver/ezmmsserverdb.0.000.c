
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
    "ezmmsserverdb.pc"
};


static unsigned int sqlctx = 5013099;


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
   unsigned char  *sqhstv[39];
   unsigned long  sqhstl[39];
            int   sqhsts[39];
            short *sqindv[39];
            int   sqinds[39];
   unsigned long  sqharm[39];
   unsigned long  *sqharc[39];
   unsigned short  sqadto[39];
   unsigned short  sqtdso[39];
} sqlstm = {12,39};

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

 static char *sq0004 = 
"select RTRIM(ACCT_NO) ,RTRIM(CURR_CODE) ,STATUS ,PRIORITY  from EZMMS_RELATI\
ON where (RTRIM(INST_ID)=:b0 and RTRIM(MERCH_ID)=:b1)           ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,617,0,4,65,0,0,17,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,1,
5,0,0,1,5,0,0,
88,0,0,2,607,0,4,179,0,0,17,3,0,1,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,97,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,
171,0,0,3,547,0,4,293,0,0,16,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
1,5,0,0,
250,0,0,4,140,0,9,381,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
273,0,0,4,0,0,13,388,0,0,4,0,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,2,3,0,0,
304,0,0,4,0,0,15,408,0,0,0,0,0,1,0,
319,0,0,5,134,0,4,438,0,0,5,2,0,1,0,2,5,0,0,2,1,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
354,0,0,6,158,0,4,482,0,0,5,2,0,1,0,2,5,0,0,2,1,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
389,0,0,7,177,0,4,526,0,0,5,2,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,1,5,0,0,1,5,0,0,
424,0,0,8,185,0,4,573,0,0,5,3,0,1,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
459,0,0,9,721,0,3,751,0,0,39,39,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,
0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
630,0,0,10,0,0,29,840,0,0,0,0,0,1,0,
645,0,0,11,393,0,3,937,0,0,23,23,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,5,0,0,
752,0,0,12,0,0,29,994,0,0,0,0,0,1,0,
767,0,0,13,219,0,5,1029,0,0,6,6,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,
806,0,0,14,217,0,5,1037,0,0,6,6,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,
845,0,0,15,0,0,29,1048,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezmms/ezmmsdbtypes.h>
#include <ezlink/ezlnkmsg.h>

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
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select NVL(STORE_STATUS,'0') ,RTRIM(NVL(STORE_NAME,'NA')) ,R\
TRIM(NVL(STORE_LOCATION,'NA')) ,RTRIM(NVL(CITY_NAME,'NA')) ,RTRIM(NVL(CITY_COD\
E,'NA')) ,RTRIM(NVL(STATE_NAME,'NA')) ,RTRIM(NVL(COUNTRY_NAME,'NA')) ,RTRIM(NV\
L(PRIM_LAND_LINE_NO,'NA')) ,RTRIM(NVL(SEC_LAND_LINE_NO,'NA')) ,RTRIM(NVL(PRIM_\
MOBILE_NUM,'NA')) ,RTRIM(NVL(SEC_MOBILE_NUM,'NA')) ,NVL(WORKING_HRS,'24') ,RTR\
IM(NVL(OPENING_TIME,'000000')) ,RTRIM(NVL(CLOSING_TIME,'235959')) into :b0,:b1\
,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13  from EZMMS_STOREPROFILE \
where ((RTRIM(INST_ID)=:b14 and RTRIM(MERCH_ID)=:b15) and RTRIM(STORE_ID)=:b16\
)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )88;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)&Status;
 sqlstm.sqhstl[0] = (unsigned long )1;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)StoreName;
 sqlstm.sqhstl[1] = (unsigned long )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)StoreLocation;
 sqlstm.sqhstl[2] = (unsigned long )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)CityName;
 sqlstm.sqhstl[3] = (unsigned long )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)CityCode;
 sqlstm.sqhstl[4] = (unsigned long )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)StateName;
 sqlstm.sqhstl[5] = (unsigned long )33;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)CountryName;
 sqlstm.sqhstl[6] = (unsigned long )33;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)LandLine1;
 sqlstm.sqhstl[7] = (unsigned long )17;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)LandLine2;
 sqlstm.sqhstl[8] = (unsigned long )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)PMobileNo;
 sqlstm.sqhstl[9] = (unsigned long )17;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)SMobileNo;
 sqlstm.sqhstl[10] = (unsigned long )17;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)&WorkingHrs;
 sqlstm.sqhstl[11] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)OpeningTime;
 sqlstm.sqhstl[12] = (unsigned long )7;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)ClosingTime;
 sqlstm.sqhstl[13] = (unsigned long )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)InstId;
 sqlstm.sqhstl[14] = (unsigned long )13;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[15] = (unsigned long )16;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (unsigned char  *)StoreId;
 sqlstm.sqhstl[16] = (unsigned long )33;
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

int readEzMMSTerminalProfile( const char *I_InstId, const char *I_MerchantId, const char *I_TerminalId, struct EzMMSTerminalProfile *terminalprofile_ptr )
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
	
	strcpy( InstId, I_InstId );
	strcpy( MerchantId, I_MerchantId );
	strcpy( TerminalId, I_TerminalId );
	
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
 sqlstm.arrsiz = 17;
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
 sqlstm.offset = (unsigned int  )171;
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

int readEzMMSMerchantRelation( const char *I_InstId, const char *I_MerchantId, struct EzMMSAccountProfile *acctlist, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char AccountNo[ 33 ];
		char CurrCode[ 5 ];
		char AccountStatus;
		short AccountPriority;
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR AccountNo IS STRING(33); */ 

	/* EXEC SQL VAR CurrCode IS STRING(5); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	strcpy( MerchantId, I_MerchantId );	
		
	/* EXEC SQL DECLARE ezmmsrelation_cur CURSOR FOR
    SELECT
    	RTRIM(ACCT_NO),
    	RTRIM(CURR_CODE),
    	STATUS,
    	PRIORITY
    FROM EZMMS_RELATION WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID) = :MerchantId; */ 
 
		
	/* EXEC SQL OPEN ezmmsrelation_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0004;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )250;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
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



	while( 1 )
	{
		memset( AccountNo, 0, sizeof( AccountNo ) );
		memset( CurrCode, 0, sizeof( CurrCode ) );
		
		/* EXEC SQL FETCH ezmmsrelation_cur INTO
			:AccountNo,
			:CurrCode,
			:AccountStatus,
			:AccountPriority; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 17;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )273;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (unsigned char  *)AccountNo;
  sqlstm.sqhstl[0] = (unsigned long )33;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)CurrCode;
  sqlstm.sqhstl[1] = (unsigned long )5;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)&AccountStatus;
  sqlstm.sqhstl[2] = (unsigned long )1;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)&AccountPriority;
  sqlstm.sqhstl[3] = (unsigned long )sizeof(short);
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


							
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        strcpy( ( acctlist + i )->InstId, InstId );
        strcpy( ( acctlist + i )->AccountNo, AccountNo );
        strcpy( ( acctlist + i )->CurrCode, CurrCode );
        ( acctlist + i )->AccountStatus = AccountStatus;
        ( acctlist + i )->AccountPriority = AccountPriority;
        i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmsrelation_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )304;
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

int readEzMMSFeeInfo( const char *I_InstId, const char *I_FeeCode, struct EzMMSFeeInfo *feeinfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char FeeCode[ 17 ];
		char FeeMode;
		char FeeAmt[ 21 ];
		char CurrCode[ 5 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR FeeCode IS STRING(17); */ 

	/* EXEC SQL VAR FeeAmt IS STRING(21); */ 

	/* EXEC SQL VAR CurrCode IS STRING(5); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	memset( FeeCode, 0, sizeof( FeeCode ) );
	strcpy( FeeCode, I_FeeCode );
	
	memset( FeeAmt, 0, sizeof( FeeAmt ) );
	memset( CurrCode, 0, sizeof( CurrCode ) );
	
	/* EXEC SQL SELECT
		RTRIM(FEEAMT),
    	FEEMODE,
    	RTRIM(CURR_CODE)
    INTO
		:FeeAmt,
		:FeeMode,
		:CurrCode
	FROM EZMMS_FEEINFO WHERE RTRIM(INST_ID) = :InstId AND RTRIM(FEECODE) = :FeeCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(FEEAMT) ,FEEMODE ,RTRIM(CURR_CODE) into :b0,:b1\
,:b2  from EZMMS_FEEINFO where (RTRIM(INST_ID)=:b3 and RTRIM(FEECODE)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )319;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)FeeAmt;
 sqlstm.sqhstl[0] = (unsigned long )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)&FeeMode;
 sqlstm.sqhstl[1] = (unsigned long )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)CurrCode;
 sqlstm.sqhstl[2] = (unsigned long )5;
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
 sqlstm.sqhstv[4] = (unsigned char  *)FeeCode;
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
	
	strcpy( feeinfo_ptr->InstId, InstId );
	strcpy( feeinfo_ptr->FeeCode, FeeCode );
	strcpy( feeinfo_ptr->FeeAmt, FeeAmt );
	strcpy( feeinfo_ptr->CurrCode, CurrCode );
	feeinfo_ptr->FeeMode = FeeMode;
	return sqlca.sqlcode;
}

int readEzMMSCommissionInfo( const char *I_InstId, const char *I_CommissionCode, struct EzMMSCommissionInfo *commisioninfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char CommissionCode[ 17 ];
		char CommissionMode;
		char CommissionAmt[ 21 ];
		char CurrCode[ 5 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR CommissionCode IS STRING(17); */ 

	/* EXEC SQL VAR CommissionAmt IS STRING(21); */ 

	/* EXEC SQL VAR CurrCode IS STRING(5); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	memset( CommissionCode, 0, sizeof( CommissionCode ) );
	strcpy( CommissionCode, I_CommissionCode );
	
	memset( CommissionAmt, 0, sizeof( CommissionAmt ) );
	memset( CurrCode, 0, sizeof( CurrCode ) );
	
	/* EXEC SQL SELECT
		RTRIM(COMISSIONAMT),
    	COMISSIONMODE,
    	RTRIM(CURR_CODE)
    INTO
		:CommissionAmt,
		:CommissionMode,
		:CurrCode
	FROM EZMMS_COMISSIONINFO WHERE RTRIM(INST_ID) = :InstId AND RTRIM(COMISSIONCODE) = :CommissionCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(COMISSIONAMT) ,COMISSIONMODE ,RTRIM(CURR_CODE) \
into :b0,:b1,:b2  from EZMMS_COMISSIONINFO where (RTRIM(INST_ID)=:b3 and RTRIM\
(COMISSIONCODE)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )354;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)CommissionAmt;
 sqlstm.sqhstl[0] = (unsigned long )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)&CommissionMode;
 sqlstm.sqhstl[1] = (unsigned long )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)CurrCode;
 sqlstm.sqhstl[2] = (unsigned long )5;
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
 sqlstm.sqhstv[4] = (unsigned char  *)CommissionCode;
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
	
	strcpy( commisioninfo_ptr->InstId, InstId );
	strcpy( commisioninfo_ptr->CommissionCode, CommissionCode );
	strcpy( commisioninfo_ptr->CommissionAmt, CommissionAmt );
	strcpy( commisioninfo_ptr->CurrCode, CurrCode );
	commisioninfo_ptr->CommissionMode = CommissionMode;
	return sqlca.sqlcode;
}

int readEzMMSCurrencyRate( const char *I_InstId, int I_CurrencyCode, struct EzMMSCurrencyRate *curr_rate_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char CurrCode[ 5 ];
		char SellingRate[ 21 ];
		char BuyingRate[ 21 ];
		char CurrencyMode;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR CurrCode IS STRING(5); */ 

	/* EXEC SQL VAR SellingRate IS STRING(21); */ 

	/* EXEC SQL VAR BuyingRate IS STRING(21); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	memset( CurrCode, 0, sizeof( CurrCode ) );
	sprintf( CurrCode, "%d", I_CurrencyCode );
	
	memset( SellingRate, 0, sizeof( SellingRate ) );
	memset( BuyingRate, 0, sizeof( BuyingRate ) );
	
	/* EXEC SQL SELECT
		RTRIM(TO_CHAR(SELLING_RATE)),
    	RTRIM(TO_CHAR(BUYING_RATE)),
    	CURRENCY_MODE
    INTO
		:SellingRate,
		:BuyingRate,
		:CurrencyMode
	FROM EZMMS_CURRENCYRATE WHERE RTRIM(INST_ID) = :InstId AND RTRIM(CURRENCY_CODE) = :CurrCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TO_CHAR(SELLING_RATE)) ,RTRIM(TO_CHAR(BUYING_RA\
TE)) ,CURRENCY_MODE into :b0,:b1,:b2  from EZMMS_CURRENCYRATE where (RTRIM(INS\
T_ID)=:b3 and RTRIM(CURRENCY_CODE)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )389;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)SellingRate;
 sqlstm.sqhstl[0] = (unsigned long )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)BuyingRate;
 sqlstm.sqhstl[1] = (unsigned long )21;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)&CurrencyMode;
 sqlstm.sqhstl[2] = (unsigned long )1;
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
 sqlstm.sqhstv[4] = (unsigned char  *)CurrCode;
 sqlstm.sqhstl[4] = (unsigned long )5;
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
	
	strcpy( curr_rate_ptr->InstId, InstId );
	strcpy( curr_rate_ptr->CurrCode, CurrCode );
	strcpy( curr_rate_ptr->SellingRate, SellingRate );
	strcpy( curr_rate_ptr->BuyingRate, BuyingRate );
	curr_rate_ptr->CurrencyMode = CurrencyMode;
	return sqlca.sqlcode;
}

int readEzMMSAccountInfo( const char *I_InstId, const char *I_MerchantId, const char *I_AccountNo, struct EzMMSAccountProfile *acctprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char AccountNo[ 33 ]; 
		char AvailableBalance[ 20 ];
		char LedgerBalance[ 20 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR AccountNo IS STRING(33); */ 

	/* EXEC SQL VAR AvailableBalance IS STRING(20); */ 

	/* EXEC SQL VAR LedgerBalance IS STRING(20); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	strcpy( MerchantId, I_MerchantId );
	memset( AccountNo, 0, sizeof( AccountNo ) );
	strcpy( AccountNo, I_AccountNo );
	
	memset( AvailableBalance, 0, sizeof( AvailableBalance ) );
	memset( LedgerBalance, 0, sizeof( LedgerBalance ) );
	
	/* EXEC SQL SELECT
		RTRIM(TO_CHAR(AVAILABLE_BALANCE)),
    	RTRIM(TO_CHAR(LEDGER_BALANCE))
    INTO
		:AvailableBalance,
		:LedgerBalance
	FROM EZMMS_ACCOUNTINFO WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID) = :MerchantId AND RTRIM(ACCT_NO) = :AccountNo; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 17;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TO_CHAR(AVAILABLE_BALANCE)) ,RTRIM(TO_CHAR(LEDG\
ER_BALANCE)) into :b0,:b1  from EZMMS_ACCOUNTINFO where ((RTRIM(INST_ID)=:b2 a\
nd RTRIM(MERCH_ID)=:b3) and RTRIM(ACCT_NO)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )424;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)AvailableBalance;
 sqlstm.sqhstl[0] = (unsigned long )20;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)LedgerBalance;
 sqlstm.sqhstl[1] = (unsigned long )20;
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
 sqlstm.sqhstv[4] = (unsigned char  *)AccountNo;
 sqlstm.sqhstl[4] = (unsigned long )33;
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
	
	strcpy( acctprofile_ptr->AvailableBalance, AvailableBalance );
	strcpy( acctprofile_ptr->LedgerBalance, LedgerBalance );
	return sqlca.sqlcode;
}

int insertMMSTransactionInfo( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char TerminalId[ 9 ];
		char BatchId[ 13 ];
		short MCC;
		char CHN[ 20 ];
		char TxnCode[ 7 ];
		char TermLoc[ 65 ];
		int TraceNo;
		char RefNum[ 13 ];
		char TranDate[ 7 ];
		char TranTime[ 7 ];
		char LocalDate[ 7 ];
		char LocalTime[ 7 ];
		int RespCode;
		int RevCode;
		int ReasonCode;
		int AuthCode;
		char AuthNum[ 13 ];
		char BusDate[ 7 ];
		int AcqCurrCode;
		char AcqConvRate[ 20 ];
		char AcqConvDate[ 7 ];
		int IssCurrCode;
		char IssConvRate[ 20 ];
		char IssConvDate[ 7 ];
		int SettCurrCode;
		char SettConvRate[ 20 ];
		char SettConvDate[ 7 ];
		char TxnType[ 3 ];
		char TxnDesc[ 65 ];
		char TxnAmount[ 20 ];
		char FeeAmount[ 20 ];
		char CommissionAmount[ 20 ];
		char NetAmount[ 20 ];
		char AccountNo[ 33 ];
		char TxnSrc[ 33 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

    /* EXEC SQL VAR TerminalId IS STRING(9); */ 

    /* EXEC SQL VAR BatchId IS STRING(13); */ 

    /* EXEC SQL VAR CHN IS STRING(19); */ 

    /* EXEC SQL VAR TxnCode IS STRING(7); */ 

    /* EXEC SQL VAR TermLoc IS STRING(65); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR TranDate IS STRING(7); */ 

    /* EXEC SQL VAR TranTime IS STRING(7); */ 

    /* EXEC SQL VAR LocalDate IS STRING(7); */ 

    /* EXEC SQL VAR LocalTime IS STRING(7); */ 

    /* EXEC SQL VAR AuthNum IS STRING(13); */ 

    /* EXEC SQL VAR BusDate IS STRING(7); */ 

    /* EXEC SQL VAR AcqConvRate IS STRING(20); */ 

    /* EXEC SQL VAR AcqConvDate IS STRING(7); */ 

    /* EXEC SQL VAR IssConvRate IS STRING(20); */ 

    /* EXEC SQL VAR IssConvDate IS STRING(7); */ 

    /* EXEC SQL VAR SettConvRate IS STRING(20); */ 

    /* EXEC SQL VAR SettConvDate IS STRING(7); */ 

    /* EXEC SQL VAR TxnType IS STRING(3); */ 

    /* EXEC SQL VAR TxnDesc IS STRING(65); */ 

    /* EXEC SQL VAR TxnAmount IS STRING(20); */ 

    /* EXEC SQL VAR FeeAmount IS STRING(20); */ 

    /* EXEC SQL VAR CommissionAmount IS STRING(20); */ 

    /* EXEC SQL VAR NetAmount IS STRING(20); */ 

    /* EXEC SQL VAR AccountNo IS STRING(33); */ 

    /* EXEC SQL VAR TxnSrc IS STRING(33); */ 

    
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
    memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( BatchId, 0, sizeof( BatchId ) );
    memset( CHN, 0, sizeof( CHN ) );
    memset( TxnCode, 0, sizeof( TxnCode ) );
    memset( TermLoc, 0, sizeof( TermLoc ) );
    memset( RefNum, 0, sizeof( RefNum ) );
    memset( TranDate, 0, sizeof( TranDate ) );
    memset( TranTime, 0, sizeof( TranTime ) );
    memset( LocalDate, 0, sizeof( LocalDate ) );
    memset( LocalTime, 0, sizeof( LocalTime ) );
    memset( AuthNum, 0, sizeof( AuthNum ) );
    memset( BusDate, 0, sizeof( BusDate ) );
    memset( AcqConvRate, 0, sizeof( AcqConvRate ) );
    memset( AcqConvDate, 0, sizeof( AcqConvDate ) );
    memset( IssConvRate, 0, sizeof( IssConvRate ) );
    memset( IssConvDate, 0, sizeof( IssConvDate ) );
    memset( SettConvRate, 0, sizeof( SettConvRate ) );
    memset( SettConvDate, 0, sizeof( SettConvDate ) );
    memset( TxnType, 0, sizeof( TxnType ) );
    memset( TxnDesc, 0, sizeof( TxnDesc ) );
    memset( TxnAmount, 0, sizeof( TxnAmount ) );
    memset( FeeAmount, 0, sizeof( FeeAmount ) );
    memset( CommissionAmount, 0, sizeof( CommissionAmount ) );
    memset( NetAmount, 0, sizeof( NetAmount ) );
    memset( AccountNo, 0, sizeof( AccountNo ) );
    memset( TxnSrc, 0, sizeof( TxnSrc ) );
    
	strcpy( TxnRefNum, txninfo_ptr->TxnRefNum );
	strcpy( InstId, txnmsg->ProcessInst );
	strcpy( MerchantId, txnmsg->AcceptorId );
	strcpy( StoreId, txnmsg->StoreId );
	strcpy( TerminalId, txnmsg->TerminalId );
	strcpy( BatchId, txnmsg->BatchId );
	MCC = txnmsg->MerchantType;
	strcpy( CHN, txnmsg->chn );
	sprintf( TxnCode, "%06d", txnmsg->TxnCode );
	strcpy( TermLoc, txnmsg->TerminalLocation );
	TraceNo = txnmsg->TraceNo;
	strcpy( RefNum, txnmsg->RefNum );
	sprintf( TranDate, "%06d", txnmsg->TranDate );
	sprintf( TranTime, "%06d", txnmsg->TranTime );
	if( !txnmsg->LocalDate )
		sprintf( LocalDate, "%06d", txnmsg->TranDate );
	else
		sprintf( LocalDate, "%06d", txnmsg->LocalDate );
	sprintf( LocalTime, "%06d", txnmsg->LocalTime );
	RespCode = txnmsg->RespCode;
	RevCode = txnmsg->RevCode;
	ReasonCode = txnmsg->ReasonCode;
	AuthCode = txnmsg->AuthCode;
	strcpy( AuthNum, txnmsg->AuthNum );
	if( !txnmsg->BusinessDate )
		sprintf( BusDate, "%06d", txnmsg->TranDate );
	else
		sprintf( BusDate, "%06d", txnmsg->BusinessDate );
	AcqCurrCode = txnmsg->AcqCurrencyCode;
	strcpy( AcqConvRate, txnmsg->AcqConvRate );
	if( !txnmsg->AcqConvDate )
		sprintf( AcqConvDate, "%06d", txnmsg->TranDate );
	else
		sprintf( AcqConvDate, "%06d", txnmsg->AcqConvDate );
	IssCurrCode = txnmsg->IssCurrencyCode;
	strcpy( IssConvRate, txnmsg->IssConvRate );
	if( !txnmsg->IssConvDate )
		sprintf( IssConvDate, "%06d", txnmsg->TranDate );
	else
		sprintf( IssConvDate, "%06d", txnmsg->IssConvDate );
	SettCurrCode = txnmsg->SettCurrencyCode;
	strcpy( SettConvRate, txnmsg->SettConvRate );
	if( !txnmsg->SettConvDate )
		sprintf( SettConvDate, "%06d", txnmsg->TranDate );
	else
		sprintf( SettConvDate, "%06d", txnmsg->SettConvDate );
	strcpy( TxnType, txninfo_ptr->TxnType );
	strcpy( TxnDesc, txninfo_ptr->TxnDesc );
	strcpy( TxnAmount, txnmsg->Amount );
	strcpy( FeeAmount, txninfo_ptr->FeeAmount );
	strcpy( CommissionAmount, txninfo_ptr->CommissionAmount );
	strcpy( NetAmount, txninfo_ptr->NetAmount );
	strcpy( AccountNo, txninfo_ptr->AccountNo );
	strcpy( TxnSrc, txnmsg->OrgChannel );
	
	/* EXEC SQL INSERT INTO EZMMS_TRANSACTION
	(
		TXNREFNUM,
        INSTID,
        MERCHANTID,
        STOREID,
        TERMINALID,
        BATCHID,
        MCC,
        CHN,
        TXNCODE,
        TERMLOC,
        TRACENO,
        REFNUM,
        TRANDATE,
        TRANTIME,
        LOCALDATE,
        LOCALTIME,
        RESPCODE,
        REVCODE,
        REASONCODE,
        AUTHCODE,
        AUTHNUM,
        BUSDATE,
        ACQCURRCODE,
        ACQCONVRATE,
        ACQCONVDATE,
        ISSCURRCODE,
        ISSCONVRATE,
        ISSCONVDATE,      
        SETTCURRCODE,
        SETTCONVRATE,
        SETTCONVDATE,
        TXNTYPE,
        TXNDESC,
        TXNAMOUNT,
        FEEAMOUNT,
        COMMISSIONAMOUNT,
        NETAMOUNT,
        ACCOUNTNO,
        TXNSRC
	)
	VALUES
	(
		:TxnRefNum,
		:InstId,
		:MerchantId,
		:StoreId,
        :TerminalId,
        :BatchId,
        :MCC,
        :CHN,
        :TxnCode,
        :TermLoc,
        :TraceNo,
        :RefNum,
        to_date( :TranDate, 'dd-mm-yy' ),
        :TranTime,
        to_date( :LocalDate, 'dd-mm-yy' ),
        :LocalTime,
        :RespCode,
        :RevCode,
        :ReasonCode,
        :AuthCode,
        :AuthNum,
        to_date( :BusDate, 'dd-mm-yy' ),
        :AcqCurrCode,
        :AcqConvRate,
        to_date( :AcqConvDate, 'dd-mm-yy' ),
        :IssCurrCode,
        :IssConvRate,
        to_date( :IssConvDate, 'dd-mm-yy' ),
        :SettCurrCode,
        :SettConvRate,
        to_date( :SettConvDate, 'dd-mm-yy' ),
        :TxnType,
        :TxnDesc,
        :TxnAmount,
        :FeeAmount,
        :CommissionAmount,
        :NetAmount,
        :AccountNo,
        :TxnSrc
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 39;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMMS_TRANSACTION (TXNREFNUM,INSTID,MERCHANTID,S\
TOREID,TERMINALID,BATCHID,MCC,CHN,TXNCODE,TERMLOC,TRACENO,REFNUM,TRANDATE,TRAN\
TIME,LOCALDATE,LOCALTIME,RESPCODE,REVCODE,REASONCODE,AUTHCODE,AUTHNUM,BUSDATE,\
ACQCURRCODE,ACQCONVRATE,ACQCONVDATE,ISSCURRCODE,ISSCONVRATE,ISSCONVDATE,SETTCU\
RRCODE,SETTCONVRATE,SETTCONVDATE,TXNTYPE,TXNDESC,TXNAMOUNT,FEEAMOUNT,COMMISSIO\
NAMOUNT,NETAMOUNT,ACCOUNTNO,TXNSRC) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b\
8,:b9,:b10,:b11,to_date(:b12,'dd-mm-yy'),:b13,to_date(:b14,'dd-mm-yy'),:b15,:b\
16,:b17,:b18,:b19,:b20,to_date(:b21,'dd-mm-yy'),:b22,:b23,to_date(:b24,'dd-mm-\
yy'),:b25,:b26,to_date(:b27,'dd-mm-yy'),:b28,:b29,to_date(:b30,'dd-mm-yy'),:b3\
1,:b32,:b33,:b34,:b35,:b36,:b37,:b38)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )459;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned long )151;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)InstId;
 sqlstm.sqhstl[1] = (unsigned long )13;
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
 sqlstm.sqhstv[5] = (unsigned char  *)BatchId;
 sqlstm.sqhstl[5] = (unsigned long )13;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)&MCC;
 sqlstm.sqhstl[6] = (unsigned long )sizeof(short);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)CHN;
 sqlstm.sqhstl[7] = (unsigned long )19;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)TxnCode;
 sqlstm.sqhstl[8] = (unsigned long )7;
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
 sqlstm.sqhstv[11] = (unsigned char  *)RefNum;
 sqlstm.sqhstl[11] = (unsigned long )13;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)TranDate;
 sqlstm.sqhstl[12] = (unsigned long )7;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)TranTime;
 sqlstm.sqhstl[13] = (unsigned long )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)LocalDate;
 sqlstm.sqhstl[14] = (unsigned long )7;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)LocalTime;
 sqlstm.sqhstl[15] = (unsigned long )7;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (unsigned char  *)&RespCode;
 sqlstm.sqhstl[16] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         short *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned long )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (unsigned char  *)&RevCode;
 sqlstm.sqhstl[17] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         short *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned long )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (unsigned char  *)&ReasonCode;
 sqlstm.sqhstl[18] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         short *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned long )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (unsigned char  *)&AuthCode;
 sqlstm.sqhstl[19] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         short *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned long )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (unsigned char  *)AuthNum;
 sqlstm.sqhstl[20] = (unsigned long )13;
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         short *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned long )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (unsigned char  *)BusDate;
 sqlstm.sqhstl[21] = (unsigned long )7;
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         short *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned long )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (unsigned char  *)&AcqCurrCode;
 sqlstm.sqhstl[22] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         short *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned long )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (unsigned char  *)AcqConvRate;
 sqlstm.sqhstl[23] = (unsigned long )20;
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         short *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned long )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (unsigned char  *)AcqConvDate;
 sqlstm.sqhstl[24] = (unsigned long )7;
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         short *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned long )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (unsigned char  *)&IssCurrCode;
 sqlstm.sqhstl[25] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         short *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned long )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (unsigned char  *)IssConvRate;
 sqlstm.sqhstl[26] = (unsigned long )20;
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         short *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned long )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (unsigned char  *)IssConvDate;
 sqlstm.sqhstl[27] = (unsigned long )7;
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         short *)0;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned long )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (unsigned char  *)&SettCurrCode;
 sqlstm.sqhstl[28] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         short *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned long )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (unsigned char  *)SettConvRate;
 sqlstm.sqhstl[29] = (unsigned long )20;
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         short *)0;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned long )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (unsigned char  *)SettConvDate;
 sqlstm.sqhstl[30] = (unsigned long )7;
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         short *)0;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned long )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (unsigned char  *)TxnType;
 sqlstm.sqhstl[31] = (unsigned long )3;
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         short *)0;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned long )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (unsigned char  *)TxnDesc;
 sqlstm.sqhstl[32] = (unsigned long )65;
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         short *)0;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned long )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (unsigned char  *)TxnAmount;
 sqlstm.sqhstl[33] = (unsigned long )20;
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         short *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned long )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (unsigned char  *)FeeAmount;
 sqlstm.sqhstl[34] = (unsigned long )20;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         short *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned long )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (unsigned char  *)CommissionAmount;
 sqlstm.sqhstl[35] = (unsigned long )20;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         short *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned long )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (unsigned char  *)NetAmount;
 sqlstm.sqhstl[36] = (unsigned long )20;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         short *)0;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned long )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (unsigned char  *)AccountNo;
 sqlstm.sqhstl[37] = (unsigned long )33;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         short *)0;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned long )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (unsigned char  *)TxnSrc;
 sqlstm.sqhstl[38] = (unsigned long )33;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         short *)0;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned long )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
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
        sqlstm.arrsiz = 39;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )630;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int insertMMSTermBatchTxn( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char TerminalId[ 9 ];
		char BatchId[ 13 ];
		short MCC;
		char CHN[ 20 ];
		char TxnCode[ 7 ];
		int TraceNo;
		char RefNum[ 13 ];
		char TranDate[ 7 ];
		char TranTime[ 7 ];
		char LocalDate[ 7 ];
		char LocalTime[ 7 ];
		int RespCode;
		int AuthCode;
		char AuthNum[ 13 ];
		short CurrencyCode;
		char TxnAmount[ 20 ];
		char TermAmount[ 20 ];
		char MatchFlag;
		char MatchDesc[ 33 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

    /* EXEC SQL VAR TerminalId IS STRING(9); */ 

    /* EXEC SQL VAR BatchId IS STRING(13); */ 

    /* EXEC SQL VAR CHN IS STRING(19); */ 

    /* EXEC SQL VAR TxnCode IS STRING(7); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR TranDate IS STRING(7); */ 

    /* EXEC SQL VAR TranTime IS STRING(7); */ 

    /* EXEC SQL VAR LocalDate IS STRING(7); */ 

    /* EXEC SQL VAR LocalTime IS STRING(7); */ 

    /* EXEC SQL VAR AuthNum IS STRING(13); */ 

    /* EXEC SQL VAR TxnAmount IS STRING(20); */ 

    /* EXEC SQL VAR TermAmount IS STRING(20); */ 

    /* EXEC SQL VAR MatchDesc IS STRING(33); */ 

    
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
    memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( BatchId, 0, sizeof( BatchId ) );
    memset( CHN, 0, sizeof( CHN ) );
    memset( TxnCode, 0, sizeof( TxnCode ) );
    memset( RefNum, 0, sizeof( RefNum ) );
    memset( TranDate, 0, sizeof( TranDate ) );
    memset( TranTime, 0, sizeof( TranTime ) );
    memset( LocalDate, 0, sizeof( LocalDate ) );
    memset( LocalTime, 0, sizeof( LocalTime ) );
    memset( AuthNum, 0, sizeof( AuthNum ) );
    memset( TxnAmount, 0, sizeof( TxnAmount ) );
    memset( TermAmount, 0, sizeof( TermAmount ) );
    memset( MatchDesc, 0, sizeof( MatchDesc ) );
    
	strcpy( TxnRefNum, txninfo_ptr->TxnRefNum );
	strcpy( InstId, txnmsg->ProcessInst );
	strcpy( MerchantId, txnmsg->AcceptorId );
	strcpy( StoreId, txnmsg->StoreId );
	strcpy( TerminalId, txnmsg->TerminalId );
	strcpy( BatchId, txnmsg->BatchId );
	MCC = txnmsg->MerchantType;
	strcpy( CHN, txnmsg->chn );
	sprintf( TxnCode, "%06d", txnmsg->TxnCode );
	TraceNo = txnmsg->TraceNo;
	strcpy( RefNum, txnmsg->RefNum );
	sprintf( TranDate, "%06d", txnmsg->TranDate );
	sprintf( TranTime, "%06d", txnmsg->TranTime );
	if( !txnmsg->LocalDate )
		sprintf( LocalDate, "%06d", txnmsg->TranDate );
	else
		sprintf( LocalDate, "%06d", txnmsg->LocalDate );
	sprintf( LocalTime, "%06d", txnmsg->LocalTime );
	RespCode = txnmsg->RespCode;
	AuthCode = txnmsg->AuthCode;
	CurrencyCode = txnmsg->AcqCurrencyCode;
	strcpy( AuthNum, txnmsg->AuthNum );
	strcpy( TxnAmount, txnmsg->Amount );
	strcpy( TermAmount, txnmsg->Amount );
	MatchFlag = 'M';
	strcpy( MatchDesc, "MATCHED" );
	
	/* EXEC SQL INSERT INTO EZMMS_TERM_BATCH_TXN
	(
		TXNREFNUM,
        INSTID,
        MERCHANTID,
        STOREID,
        TERMINALID,
        BATCH_ID,
        MCC,
        CHN,
        TXNCODE,
        TRACENO,
        REFNUM,
        TRANDATE,
        TRANTIME,
        LOCALDATE,
        LOCALTIME,
        RESPCODE,
        AUTHCODE,
        AUTHNUM,
        CURRENCYCODE,
        TXNAMOUNT,
        TERMAMOUNT,
        MATCHFLAG,
        MATCHDESC
	)
	VALUES
	(
		:TxnRefNum,
		:InstId,
		:MerchantId,
		:StoreId,
        :TerminalId,
        :BatchId,
        :MCC,
        :CHN,
        :TxnCode,
        :TraceNo,
        :RefNum,
        to_date( :TranDate, 'dd-mm-yy' ),
        :TranTime,
        to_date( :LocalDate, 'dd-mm-yy' ),
        :LocalTime,
        :RespCode,
        :AuthCode,
        :AuthNum,
        :CurrencyCode,
        :TxnAmount,
        :TermAmount,
        :MatchFlag,
        :MatchDesc
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 39;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMMS_TERM_BATCH_TXN (TXNREFNUM,INSTID,MERCHANTI\
D,STOREID,TERMINALID,BATCH_ID,MCC,CHN,TXNCODE,TRACENO,REFNUM,TRANDATE,TRANTIME\
,LOCALDATE,LOCALTIME,RESPCODE,AUTHCODE,AUTHNUM,CURRENCYCODE,TXNAMOUNT,TERMAMOU\
NT,MATCHFLAG,MATCHDESC) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,t\
o_date(:b11,'dd-mm-yy'),:b12,to_date(:b13,'dd-mm-yy'),:b14,:b15,:b16,:b17,:b18\
,:b19,:b20,:b21,:b22)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )645;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned long )151;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)InstId;
 sqlstm.sqhstl[1] = (unsigned long )13;
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
 sqlstm.sqhstv[5] = (unsigned char  *)BatchId;
 sqlstm.sqhstl[5] = (unsigned long )13;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)&MCC;
 sqlstm.sqhstl[6] = (unsigned long )sizeof(short);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (unsigned char  *)CHN;
 sqlstm.sqhstl[7] = (unsigned long )19;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         short *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned long )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (unsigned char  *)TxnCode;
 sqlstm.sqhstl[8] = (unsigned long )7;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         short *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned long )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (unsigned char  *)&TraceNo;
 sqlstm.sqhstl[9] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         short *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned long )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (unsigned char  *)RefNum;
 sqlstm.sqhstl[10] = (unsigned long )13;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         short *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned long )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (unsigned char  *)TranDate;
 sqlstm.sqhstl[11] = (unsigned long )7;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         short *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned long )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (unsigned char  *)TranTime;
 sqlstm.sqhstl[12] = (unsigned long )7;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         short *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned long )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (unsigned char  *)LocalDate;
 sqlstm.sqhstl[13] = (unsigned long )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         short *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned long )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (unsigned char  *)LocalTime;
 sqlstm.sqhstl[14] = (unsigned long )7;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         short *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned long )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (unsigned char  *)&RespCode;
 sqlstm.sqhstl[15] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         short *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned long )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (unsigned char  *)&AuthCode;
 sqlstm.sqhstl[16] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         short *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned long )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (unsigned char  *)AuthNum;
 sqlstm.sqhstl[17] = (unsigned long )13;
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         short *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned long )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (unsigned char  *)&CurrencyCode;
 sqlstm.sqhstl[18] = (unsigned long )sizeof(short);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         short *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned long )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (unsigned char  *)TxnAmount;
 sqlstm.sqhstl[19] = (unsigned long )20;
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         short *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned long )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (unsigned char  *)TermAmount;
 sqlstm.sqhstl[20] = (unsigned long )20;
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         short *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned long )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (unsigned char  *)&MatchFlag;
 sqlstm.sqhstl[21] = (unsigned long )1;
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         short *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned long )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (unsigned char  *)MatchDesc;
 sqlstm.sqhstl[22] = (unsigned long )33;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         short *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned long )0;
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
        sqlstm.arrsiz = 39;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )752;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}

int updateMMSMerchantBalance( struct EzTxnMsg *txnmsg, struct EzMMSTxnInfo *txninfo_ptr )
{
    /* EXEC SQL BEGIN DECLARE SECTION ; */ 

    	char InstId[ 13 ];
		char MerchantId[ 16 ];
		char AccountNo[ 33 ]; 
		char NetAmount[ 20 ];
		char TxnType[ 3 ];
    /* EXEC SQL END DECLARE SECTION ; */ 


    /* EXEC SQL VAR InstId IS STRING(13); */ 

    /* EXEC SQL VAR MerchantId IS STRING(16); */ 

    /* EXEC SQL VAR AccountNo IS STRING(33); */ 

    /* EXEC SQL VAR NetAmount IS STRING(20); */ 

    /* EXEC SQL VAR TxnType IS STRING(3); */ 


   	memset( InstId, 0, sizeof( InstId ) );
   	memset( MerchantId, 0, sizeof( MerchantId ) );
   	memset( AccountNo, 0, sizeof( AccountNo ) );
   	memset( NetAmount, 0, sizeof( NetAmount ) );
   	memset( TxnType, 0, sizeof( TxnType ) );
   	
    strcpy( InstId, txnmsg->ProcessInst );
    strcpy( MerchantId, txnmsg->AcceptorId );
    strcpy( AccountNo, txninfo_ptr->AccountNo );
    strcpy( NetAmount, txninfo_ptr->NetAmount );
    strcpy( TxnType, txninfo_ptr->TxnType );

	if( !strcmp( TxnType, "CR" ) )
	{
    	/* EXEC SQL UPDATE EZMMS_ACCOUNTINFO SET
    		AVAILABLE_BALANCE = AVAILABLE_BALANCE + :NetAmount, 
    		LEDGER_BALANCE = LEDGER_BALANCE + :NetAmount, 
    		CREDIT_BALANCE = CREDIT_BALANCE + :NetAmount
    	WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID) = :MerchantId AND RTRIM(ACCT_NO) = :AccountNo; */ 

{
     struct sqlexd sqlstm;
     sqlstm.sqlvsn = 12;
     sqlstm.arrsiz = 39;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.stmt = "update EZMMS_ACCOUNTINFO  set AVAILABLE_BALANCE=(AVAILAB\
LE_BALANCE+:b0),LEDGER_BALANCE=(LEDGER_BALANCE+:b0),CREDIT_BALANCE=(CREDIT_BAL\
ANCE+:b0) where ((RTRIM(INST_ID)=:b3 and RTRIM(MERCH_ID)=:b4) and RTRIM(ACCT_N\
O)=:b5)";
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )767;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlstm.sqhstv[0] = (unsigned char  *)NetAmount;
     sqlstm.sqhstl[0] = (unsigned long )20;
     sqlstm.sqhsts[0] = (         int  )0;
     sqlstm.sqindv[0] = (         short *)0;
     sqlstm.sqinds[0] = (         int  )0;
     sqlstm.sqharm[0] = (unsigned long )0;
     sqlstm.sqadto[0] = (unsigned short )0;
     sqlstm.sqtdso[0] = (unsigned short )0;
     sqlstm.sqhstv[1] = (unsigned char  *)NetAmount;
     sqlstm.sqhstl[1] = (unsigned long )20;
     sqlstm.sqhsts[1] = (         int  )0;
     sqlstm.sqindv[1] = (         short *)0;
     sqlstm.sqinds[1] = (         int  )0;
     sqlstm.sqharm[1] = (unsigned long )0;
     sqlstm.sqadto[1] = (unsigned short )0;
     sqlstm.sqtdso[1] = (unsigned short )0;
     sqlstm.sqhstv[2] = (unsigned char  *)NetAmount;
     sqlstm.sqhstl[2] = (unsigned long )20;
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


    }
    else
    {
    	/* EXEC SQL UPDATE EZMMS_ACCOUNTINFO SET
    		AVAILABLE_BALANCE = AVAILABLE_BALANCE - :NetAmount, 
    		LEDGER_BALANCE = LEDGER_BALANCE - :NetAmount, 
    		DEBIT_BALANCE = DEBIT_BALANCE + :NetAmount
    	WHERE RTRIM(INST_ID) = :InstId AND RTRIM(MERCH_ID) = :MerchantId AND RTRIM(ACCT_NO) = :AccountNo; */ 

{
     struct sqlexd sqlstm;
     sqlstm.sqlvsn = 12;
     sqlstm.arrsiz = 39;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.stmt = "update EZMMS_ACCOUNTINFO  set AVAILABLE_BALANCE=(AVAILAB\
LE_BALANCE-:b0),LEDGER_BALANCE=(LEDGER_BALANCE-:b0),DEBIT_BALANCE=(DEBIT_BALAN\
CE+:b0) where ((RTRIM(INST_ID)=:b3 and RTRIM(MERCH_ID)=:b4) and RTRIM(ACCT_NO)\
=:b5)";
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )806;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlstm.sqhstv[0] = (unsigned char  *)NetAmount;
     sqlstm.sqhstl[0] = (unsigned long )20;
     sqlstm.sqhsts[0] = (         int  )0;
     sqlstm.sqindv[0] = (         short *)0;
     sqlstm.sqinds[0] = (         int  )0;
     sqlstm.sqharm[0] = (unsigned long )0;
     sqlstm.sqadto[0] = (unsigned short )0;
     sqlstm.sqtdso[0] = (unsigned short )0;
     sqlstm.sqhstv[1] = (unsigned char  *)NetAmount;
     sqlstm.sqhstl[1] = (unsigned long )20;
     sqlstm.sqhsts[1] = (         int  )0;
     sqlstm.sqindv[1] = (         short *)0;
     sqlstm.sqinds[1] = (         int  )0;
     sqlstm.sqharm[1] = (unsigned long )0;
     sqlstm.sqadto[1] = (unsigned short )0;
     sqlstm.sqtdso[1] = (unsigned short )0;
     sqlstm.sqhstv[2] = (unsigned char  *)NetAmount;
     sqlstm.sqhstl[2] = (unsigned long )20;
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


    }

    if ( sqlca.sqlcode != 0 )
        return sqlca.sqlcode;
    else
    {
        /* EXEC SQL COMMIT; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 39;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )845;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return sqlca.sqlcode;
    }
}
