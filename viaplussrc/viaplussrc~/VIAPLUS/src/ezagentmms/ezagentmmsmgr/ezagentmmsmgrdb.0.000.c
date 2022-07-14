
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
           char  filnam[25];
};
static struct sqlcxp sqlfpn =
{
    24,
    "ezagentmmsmgrdb.0.000.pc"
};


static unsigned int sqlctx = 1244844443;


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
   unsigned char  *sqhstv[26];
   unsigned long  sqhstl[26];
            int   sqhsts[26];
            short *sqindv[26];
            int   sqinds[26];
   unsigned long  sqharm[26];
   unsigned long  *sqharc[26];
   unsigned short  sqadto[26];
   unsigned short  sqtdso[26];
} sqlstm = {12,26};

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
"select RTRIM(INST_ID) ,RTRIM(BIN) ,RTRIM(NVL(SCHEME_NAME,'BPESA')) ,RTRIM(NV\
L(SCHEME_DESC,'BPESA'))  from EZMMS_SCHEMEMASTER            ";

 static char *sq0004 = 
"select RTRIM(INST_ID) ,RTRIM(MERCH_ID) ,RTRIM(NVL(MCC_LIST,'NA')) ,RTRIM(NVL\
(MERCH_TYPE_ID,'NA')) ,RTRIM(NVL(PARENT_MERCH_ID,'NA')) ,RTRIM(NVL(MERCH_NAME,\
'NA')) ,RTRIM(NVL(PRIM_MAIL_ADDR,'NA')) ,RTRIM(NVL(SEC_MAIL_ADDR,'NA')) ,NVL(S\
TATUS,'0') ,RTRIM(NVL(TO_CHAR(DOB,'DD-MM-YY'),'NA')) ,RTRIM(NVL(PRIM_MOBILE_NO\
,'NA')) ,RTRIM(NVL(SEC_MOBILE_NO,'NA')) ,RTRIM(NVL(PRIM_EMAIL_ID,'NA')) ,RTRIM\
(NVL(SEC_EMAIL_ID,'NA')) ,RTRIM(NVL(SETT_CURR_CODE,'NA')) ,RTRIM(NVL(CURR_LIST\
,'NA')) ,NVL(CARD_ISSUED_FLAG,'N') ,RTRIM(NVL(SETTLEMENT_ACCTNO,'NA')) ,RTRIM(\
NVL(ACQBIN,'NA'))  from EZMMS_MERCHANTPROFILE            ";

 static char *sq0006 = 
"select RTRIM(INST_ID) ,RTRIM(MERCH_ID) ,RTRIM(STORE_ID) ,NVL(STORE_STATUS,'0\
') ,RTRIM(NVL(STORE_NAME,'NA')) ,RTRIM(NVL(STORE_LOCATION,'NA')) ,RTRIM(NVL(CI\
TY_NAME,'NA')) ,RTRIM(NVL(CITY_CODE,'NA')) ,RTRIM(NVL(STATE_NAME,'NA')) ,RTRIM\
(NVL(COUNTRY_NAME,'NA')) ,RTRIM(NVL(PRIM_LAND_LINE_NO,'NA')) ,RTRIM(NVL(SEC_LA\
ND_LINE_NO,'NA')) ,RTRIM(NVL(PRIM_MOBILE_NUM,'NA')) ,RTRIM(NVL(SEC_MOBILE_NUM,\
'NA')) ,NVL(WORKING_HRS,'24') ,RTRIM(NVL(OPENING_TIME,'000000')) ,RTRIM(NVL(CL\
OSING_TIME,'235959'))  from EZMMS_STOREPROFILE            ";

 static char *sq0008 = 
"select RTRIM(MACHINE_ID) ,RTRIM(INST_ID) ,RTRIM(MERCH_ID) ,RTRIM(STORE_ID) ,\
RTRIM(TERMINAL_ID) ,RTRIM(TERMINAL_TYPE) ,RTRIM(NVL(TERMINAL_NAME,'NA')) ,RTRI\
M(NVL(TERMINAL_LOCATION,'NA')) ,NVL(TERMINAL_STATUS,'0') ,NVL(WORKING_HRS,'24'\
) ,RTRIM(NVL(OPENING_TIME,'000000')) ,RTRIM(NVL(CLOSING_TIME,'235959')) ,RTRIM\
(NVL(COUNTRY_CODE,'971')) ,RTRIM(NVL(CURR_CODE,'971')) ,NVL(CHIP_ENABLED,'N') \
,RTRIM(TERM_MASTER_KEY) ,RTRIM(NVL(TERM_PIN_KEY,'1111111111111111')) ,RTRIM(NV\
L(TERM_MAC_KEY,'1111111111111111')) ,KEY_INTVL ,ECHO_INTVL ,TXN_KEY_INTVL ,MCC\
_CODE ,RTRIM(NVL(BATCHID,'NOTDEFINED')) ,RTRIM(NVL(CONFIG_ID,'NOTDEFINED')) ,R\
TRIM(NVL(USERNAME,'NOTDEFINED')) ,RTRIM(NVL(USERMASTERCODE,'NOTDEFINED'))  fro\
m EZMMS_TERMINALPROFILE            ";

 static char *sq0009 = 
"select RTRIM(RECORDID) ,RTRIM(INSTID) ,RTRIM(MERCHANTTYPE) ,RTRIM(MERCHANTID\
) ,RTRIM(TERMINALID) ,RTRIM(FITRECORD) ,INDIRECTSTATE ,LOCALPINVERFLAG ,LOCALF\
INGERVERFLAG ,MAXPINLEN ,MINPINLEN  from EZMMS_FITPROFILE            ";

 static char *sq0012 = 
"select RTRIM(RECORDID) ,RTRIM(INST_ID) ,RTRIM(TXNCODE) ,RTRIM(SHORTDESC) ,RT\
RIM(LONGDESC) ,RTRIM(TXNTYPE)  from EZMMS_TXNCODEDESC            ";

 static char *sq0014 = 
"select RTRIM(RECORDID) ,RTRIM(INST_ID) ,RTRIM(DEVICETYPE) ,RTRIM(TXNCODE) ,R\
TRIM(TXNDESC)  from EZMMS_TRANSACTIONDESC            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,51,0,4,13,0,0,1,0,0,1,0,2,3,0,0,
24,0,0,2,136,0,9,43,0,0,0,0,0,1,0,
39,0,0,2,0,0,13,52,0,0,4,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
70,0,0,2,0,0,15,72,0,0,0,0,0,1,0,
85,0,0,3,54,0,4,86,0,0,1,0,0,1,0,2,3,0,0,
104,0,0,4,601,0,9,159,0,0,0,0,0,1,0,
119,0,0,4,0,0,13,182,0,0,19,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,
210,0,0,4,0,0,15,233,0,0,0,0,0,1,0,
225,0,0,5,51,0,4,247,0,0,1,0,0,1,0,2,3,0,0,
244,0,0,6,524,0,9,314,0,0,0,0,0,1,0,
259,0,0,6,0,0,13,334,0,0,17,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,
2,5,0,0,2,5,0,0,
342,0,0,6,0,0,15,380,0,0,0,0,0,1,0,
357,0,0,7,54,0,4,394,0,0,1,0,0,1,0,2,3,0,0,
376,0,0,8,735,0,9,483,0,0,0,0,0,1,0,
391,0,0,8,0,0,13,507,0,0,26,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,5,0,0,
510,0,0,8,0,0,15,571,0,0,0,0,0,1,0,
525,0,0,9,223,0,9,618,0,0,0,0,0,1,0,
540,0,0,9,0,0,13,628,0,0,11,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,2,1,0,0,2,1,0,0,2,3,0,0,2,3,0,0,
599,0,0,9,0,0,15,661,0,0,0,0,0,1,0,
614,0,0,10,49,0,4,674,0,0,1,0,0,1,0,2,3,0,0,
633,0,0,11,50,0,4,686,0,0,1,0,0,1,0,2,3,0,0,
652,0,0,12,141,0,9,722,0,0,0,0,0,1,0,
667,0,0,12,0,0,13,733,0,0,6,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,
706,0,0,12,0,0,15,757,0,0,0,0,0,1,0,
721,0,0,13,54,0,4,771,0,0,1,0,0,1,0,2,3,0,0,
740,0,0,14,129,0,9,804,0,0,0,0,0,1,0,
755,0,0,14,0,0,13,814,0,0,5,0,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
790,0,0,14,0,0,15,836,0,0,0,0,0,1,0,
};


#include <ezagentmms/ezagentmmsdbtypes.h>
#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getEzMerchantSchemeCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_SCHEMEMASTER; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_SCHEMEMASTER ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )5;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int LoadEzMerchantScheme( struct EzMMSMerchantScheme *merchantscheme_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char BIN[ 13 ];
		char SchemeName[ 17 ];
		char SchemeDesc[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR SchemeName IS STRING(17); */ 

	/* EXEC SQL VAR SchemeDesc IS STRING(17); */ 

	
	/* EXEC SQL DECLARE ezmmsmerchantscheme_cur CURSOR FOR
    SELECT
    	RTRIM(INST_ID),
    	RTRIM(BIN),
    	RTRIM( NVL( SCHEME_NAME, 'BPESA' ) ),
    	RTRIM( NVL( SCHEME_DESC, 'BPESA' ) )
    FROM EZMMS_SCHEMEMASTER; */ 

		
	/* EXEC SQL OPEN ezmmsmerchantscheme_cur; */ 

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
		memset( InstId, 0, sizeof( InstId ) );
		memset( BIN, 0, sizeof( BIN ) );
		memset( SchemeName, 0, sizeof( SchemeName ) );
		memset( SchemeDesc, 0, sizeof( SchemeDesc ) );
			
		/* EXEC SQL FETCH ezmmsmerchantscheme_cur INTO
			:InstId,
			:BIN,
			:SchemeName,
			:SchemeDesc; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )39;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (unsigned char  *)InstId;
  sqlstm.sqhstl[0] = (unsigned long )13;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)BIN;
  sqlstm.sqhstl[1] = (unsigned long )13;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)SchemeName;
  sqlstm.sqhstl[2] = (unsigned long )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)SchemeDesc;
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


							
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        memset( merchantscheme_ptr + i, 0, sizeof( struct EzMMSMerchantScheme ) );
        strcpy( ( merchantscheme_ptr + i )->InstId, InstId );
        strcpy( ( merchantscheme_ptr + i )->BIN, BIN );
        strcpy( ( merchantscheme_ptr + i )->SchemeName, SchemeName );
        strcpy( ( merchantscheme_ptr + i )->SchemeDesc, SchemeDesc );
        i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmsmerchantscheme_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )70;
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

int getEzMerchantProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_MERCHANTPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_MERCHANTPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )85;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int LoadEzMerchantProfile( struct EzMMSMerchantProfile *merchantprofile_ptr, int *SqlErr )
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
		char MerchantAcctNo[ 68 ]; 
		char AcquirerBIN[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
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

	/* EXEC SQL VAR MerchantAcctNo IS STRING(68); */ 

	/* EXEC SQL VAR AcquirerBIN IS STRING(17); */ 

		
	/* EXEC SQL DECLARE ezmmsmerchantprofile_cur CURSOR FOR
    SELECT
    	RTRIM(INST_ID),
    	RTRIM(MERCH_ID),
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
    	NVL( CARD_ISSUED_FLAG, 'N' ),
    	RTRIM( NVL( SETTLEMENT_ACCTNO, 'NA' ) ),
    	RTRIM( NVL( ACQBIN, 'NA' ) )
    FROM EZMMS_MERCHANTPROFILE; */ 

		
	/* EXEC SQL OPEN ezmmsmerchantprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0004;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )104;
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
		memset( MerchantAcctNo, 0, sizeof( MerchantAcctNo ) );
		memset( AcquirerBIN, 0, sizeof( AcquirerBIN ) );
		
		/* EXEC SQL FETCH ezmmsmerchantprofile_cur INTO
			:InstId,
			:MerchantId,
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
			:CardIssuanceFlag,
			:MerchantAcctNo,
			:AcquirerBIN; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )119;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
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
  sqlstm.sqhstv[2] = (unsigned char  *)MCCList;
  sqlstm.sqhstl[2] = (unsigned long )33;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)MerchantTypeId;
  sqlstm.sqhstl[3] = (unsigned long )17;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)ParentMerchantId;
  sqlstm.sqhstl[4] = (unsigned long )16;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (unsigned char  *)MerchantName;
  sqlstm.sqhstl[5] = (unsigned long )33;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         short *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned long )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (unsigned char  *)Addr1;
  sqlstm.sqhstl[6] = (unsigned long )65;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         short *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned long )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (unsigned char  *)Addr2;
  sqlstm.sqhstl[7] = (unsigned long )65;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         short *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned long )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (unsigned char  *)&Status;
  sqlstm.sqhstl[8] = (unsigned long )1;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         short *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned long )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (unsigned char  *)DOB;
  sqlstm.sqhstl[9] = (unsigned long )11;
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
  sqlstm.sqhstv[12] = (unsigned char  *)PMailAddr;
  sqlstm.sqhstl[12] = (unsigned long )33;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         short *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned long )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (unsigned char  *)SMailAddr;
  sqlstm.sqhstl[13] = (unsigned long )33;
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         short *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned long )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (unsigned char  *)SettCurrCode;
  sqlstm.sqhstl[14] = (unsigned long )5;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         short *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned long )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (unsigned char  *)CurrList;
  sqlstm.sqhstl[15] = (unsigned long )33;
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         short *)0;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned long )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (unsigned char  *)&CardIssuanceFlag;
  sqlstm.sqhstl[16] = (unsigned long )1;
  sqlstm.sqhsts[16] = (         int  )0;
  sqlstm.sqindv[16] = (         short *)0;
  sqlstm.sqinds[16] = (         int  )0;
  sqlstm.sqharm[16] = (unsigned long )0;
  sqlstm.sqadto[16] = (unsigned short )0;
  sqlstm.sqtdso[16] = (unsigned short )0;
  sqlstm.sqhstv[17] = (unsigned char  *)MerchantAcctNo;
  sqlstm.sqhstl[17] = (unsigned long )68;
  sqlstm.sqhsts[17] = (         int  )0;
  sqlstm.sqindv[17] = (         short *)0;
  sqlstm.sqinds[17] = (         int  )0;
  sqlstm.sqharm[17] = (unsigned long )0;
  sqlstm.sqadto[17] = (unsigned short )0;
  sqlstm.sqtdso[17] = (unsigned short )0;
  sqlstm.sqhstv[18] = (unsigned char  *)AcquirerBIN;
  sqlstm.sqhstl[18] = (unsigned long )17;
  sqlstm.sqhsts[18] = (         int  )0;
  sqlstm.sqindv[18] = (         short *)0;
  sqlstm.sqinds[18] = (         int  )0;
  sqlstm.sqharm[18] = (unsigned long )0;
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
        	
        memset( merchantprofile_ptr + i, 0, sizeof( struct EzMMSMerchantProfile ) );
        strcpy( ( merchantprofile_ptr + i )->InstId, InstId );
        strcpy( ( merchantprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( merchantprofile_ptr + i )->MCCList, MCCList );
        strcpy( ( merchantprofile_ptr + i )->MerchantTypeId, MerchantTypeId );
        strcpy( ( merchantprofile_ptr + i )->ParentMerchantId, ParentMerchantId );
      	strcpy( ( merchantprofile_ptr + i )->MerchantName, MerchantName );
      	strcpy( ( merchantprofile_ptr + i )->Addr1, Addr1 );
      	strcpy( ( merchantprofile_ptr + i )->Addr2, Addr2 );
      	( merchantprofile_ptr + i )->Status = Status;
      	strcpy( ( merchantprofile_ptr + i )->DOB, DOB );
      	strcpy( ( merchantprofile_ptr + i )->PMobileNo, PMobileNo );
      	strcpy( ( merchantprofile_ptr + i )->SMobileNo, SMobileNo );
      	strcpy( ( merchantprofile_ptr + i )->PMailAddr, PMailAddr );
      	strcpy( ( merchantprofile_ptr + i )->SMailAddr, SMailAddr );
      	strcpy( ( merchantprofile_ptr + i )->SettCurrCode, SettCurrCode );
      	strcpy( ( merchantprofile_ptr + i )->CurrList, CurrList );
      	( merchantprofile_ptr + i )->CardIssuanceFlag = CardIssuanceFlag;
      	strcpy( ( merchantprofile_ptr + i )->MerchantAcctNo, MerchantAcctNo );
      	strcpy( ( merchantprofile_ptr + i )->AcquirerBIN, AcquirerBIN );
       	i++;
	}
	
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmsmerchantprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )210;
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

int getEzStoreProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_STOREPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 19;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_STOREPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )225;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int LoadEzStoreProfile( struct EzMMSStoreProfile *storeprofile_ptr, int *SqlErr )
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


	int i = 0;
	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR StoreName IS STRING(33); */ 

	/* EXEC SQL VAR StoreLocation IS STRING(65); */ 

	/* EXEC SQL VAR CityName IS STRING(33); */ 

	/* EXEC SQL VAR CityCode IS STRING(17); */ 

	/* EXEC SQL VAR StateName IS STRING(33); */ 

	/* EXEC SQL VAR CountryName IS STRING(33); */ 

	/* EXEC SQL VAR LandLine1 IS STRING(17); */ 

	/* EXEC SQL VAR LandLine2 IS STRING(17); */ 

	/* EXEC SQL VAR PMobileNo IS STRING(17); */ 

	/* EXEC SQL VAR SMobileNo IS STRING(17); */ 

	/* EXEC SQL VAR OpeningTime IS STRING(7); */ 

	/* EXEC SQL VAR ClosingTime IS STRING(7); */ 

	
	/* EXEC SQL DECLARE ezmmsstoreprofile_cur CURSOR FOR
    SELECT
    	RTRIM(INST_ID),
    	RTRIM(MERCH_ID),
    	RTRIM(STORE_ID),
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
    FROM EZMMS_STOREPROFILE; */ 

		
	/* EXEC SQL OPEN ezmmsstoreprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0006;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )244;
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
		
		/* EXEC SQL FETCH ezmmsstoreprofile_cur INTO
			:InstId,
			:MerchantId,
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
			:ClosingTime; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 19;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )259;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
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
  sqlstm.sqhstv[3] = (unsigned char  *)&Status;
  sqlstm.sqhstl[3] = (unsigned long )1;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)StoreName;
  sqlstm.sqhstl[4] = (unsigned long )33;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (unsigned char  *)StoreLocation;
  sqlstm.sqhstl[5] = (unsigned long )65;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         short *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned long )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (unsigned char  *)CityName;
  sqlstm.sqhstl[6] = (unsigned long )33;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         short *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned long )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (unsigned char  *)CityCode;
  sqlstm.sqhstl[7] = (unsigned long )17;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         short *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned long )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (unsigned char  *)StateName;
  sqlstm.sqhstl[8] = (unsigned long )33;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         short *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned long )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (unsigned char  *)CountryName;
  sqlstm.sqhstl[9] = (unsigned long )33;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         short *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned long )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (unsigned char  *)LandLine1;
  sqlstm.sqhstl[10] = (unsigned long )17;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         short *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned long )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (unsigned char  *)LandLine2;
  sqlstm.sqhstl[11] = (unsigned long )17;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         short *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned long )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (unsigned char  *)PMobileNo;
  sqlstm.sqhstl[12] = (unsigned long )17;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         short *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned long )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (unsigned char  *)SMobileNo;
  sqlstm.sqhstl[13] = (unsigned long )17;
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         short *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned long )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (unsigned char  *)&WorkingHrs;
  sqlstm.sqhstl[14] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         short *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned long )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (unsigned char  *)OpeningTime;
  sqlstm.sqhstl[15] = (unsigned long )7;
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         short *)0;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned long )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (unsigned char  *)ClosingTime;
  sqlstm.sqhstl[16] = (unsigned long )7;
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


							
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        memset( storeprofile_ptr + i, 0, sizeof( struct EzMMSStoreProfile ) );
        strcpy( ( storeprofile_ptr + i )->InstId, InstId );
        strcpy( ( storeprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( storeprofile_ptr + i )->StoreId, StoreId );
        ( storeprofile_ptr + i )->Status = Status;
        strcpy( ( storeprofile_ptr + i )->StoreName, StoreName );
        strcpy( ( storeprofile_ptr + i )->StoreLocation, StoreLocation );
        strcpy( ( storeprofile_ptr + i )->CityName, CityName );
        strcpy( ( storeprofile_ptr + i )->CityCode, CityCode );
        strcpy( ( storeprofile_ptr + i )->StateName, StateName );
        strcpy( ( storeprofile_ptr + i )->CountryName, CountryName );
        strcpy( ( storeprofile_ptr + i )->LandLine1, LandLine1 );
        strcpy( ( storeprofile_ptr + i )->LandLine2, LandLine2 );
        strcpy( ( storeprofile_ptr + i )->PMobileNo, PMobileNo );
        strcpy( ( storeprofile_ptr + i )->SMobileNo, SMobileNo );
        ( storeprofile_ptr + i )->WorkingHrs = WorkingHrs;
        strcpy( ( storeprofile_ptr + i )->OpeningTime, OpeningTime );
        strcpy( ( storeprofile_ptr + i )->ClosingTime, ClosingTime );
       	i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmsstoreprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )342;
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

int getEzTerminalProfileCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_TERMINALPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 19;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_TERMINALPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )357;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int LoadEzTerminalProfile( struct EzMMSTerminalProfile *terminalprofile_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MachineId[ 33 ];
		char InstId[ 13 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char TerminalId[ 9 ];
		char TerminalType[ 17 ];
		char TerminalName[ 33 ];
		char TermLocation[ 65 ];
		char TerminalStatus;
		int WorkingHrs;
		char OpeningTime[ 7 ];
		char ClosingTime[ 7 ];
		char CountryCode[ 5 ];
		char CurrCode[ 5 ];
		char TermMasterKey[ 65 ];
		char TermPINKey[ 65 ];
		char ChipEnabled;
		char TermMACKey[ 65 ];
		char BatchId[ 13 ];
		char ConfigId[ 13 ];
		int KeyIntvl;
		int TxnKeyIntvl;
		int EchoIntvl;
		int mcc;
		char TermUser[ 33 ];
		char CatCode[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR TerminalId IS STRING(9); */ 

	/* EXEC SQL VAR TerminalType IS STRING(17); */ 

	/* EXEC SQL VAR TerminalName IS STRING(33); */ 

	/* EXEC SQL VAR TermLocation IS STRING(65); */ 

	/* EXEC SQL VAR OpeningTime IS STRING(7); */ 

	/* EXEC SQL VAR ClosingTime IS STRING(7); */ 

	/* EXEC SQL VAR CountryCode IS STRING(5); */ 

	/* EXEC SQL VAR CurrCode IS STRING(5); */ 

	/* EXEC SQL VAR TermMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR TermPINKey IS STRING(65); */ 

	/* EXEC SQL VAR TermMACKey IS STRING(65); */ 

	/* EXEC SQL VAR BatchId IS STRING(13); */ 

	/* EXEC SQL VAR ConfigId IS STRING(13); */ 

	/* EXEC SQL VAR TermUser IS STRING(33); */ 

	/* EXEC SQL VAR CatCode IS STRING(17); */ 

	
	/* EXEC SQL DECLARE ezmmsterminalprofile_cur CURSOR FOR
    SELECT
    	RTRIM(MACHINE_ID),
    	RTRIM(INST_ID),
    	RTRIM(MERCH_ID),
    	RTRIM(STORE_ID),
		RTRIM(TERMINAL_ID),
		RTRIM(TERMINAL_TYPE),
    	RTRIM( NVL( TERMINAL_NAME, 'NA' ) ),
    	RTRIM( NVL( TERMINAL_LOCATION, 'NA' ) ),
    	NVL( TERMINAL_STATUS, '0' ),
    	NVL( WORKING_HRS, '24' ),
    	RTRIM( NVL( OPENING_TIME, '000000' ) ),
    	RTRIM( NVL( CLOSING_TIME, '235959' ) ),
    	RTRIM( NVL(COUNTRY_CODE,'971')),
    	RTRIM( NVL(CURR_CODE,'971')),
    	NVL( CHIP_ENABLED, 'N' ),
    	RTRIM( TERM_MASTER_KEY ),
    	RTRIM( NVL( TERM_PIN_KEY, '1111111111111111' ) ),
    	RTRIM( NVL( TERM_MAC_KEY, '1111111111111111' ) ),
		KEY_INTVL,
		ECHO_INTVL,
		TXN_KEY_INTVL,
		MCC_CODE,
		RTRIM( NVL( BATCHID, 'NOTDEFINED' ) ),
		RTRIM( NVL( CONFIG_ID, 'NOTDEFINED' ) ),
		RTRIM( NVL( USERNAME, 'NOTDEFINED' ) ),
		RTRIM( NVL( USERMASTERCODE, 'NOTDEFINED' ) )
    FROM EZMMS_TERMINALPROFILE; */ 

		
	/* EXEC SQL OPEN ezmmsterminalprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 19;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0008;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )376;
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
		memset( MachineId, 0, sizeof( MachineId ) );
		memset( InstId, 0, sizeof( InstId ) );
		memset( MerchantId, 0, sizeof( MerchantId ) );
		memset( StoreId, 0, sizeof( StoreId ) );
		memset( TerminalId, 0, sizeof( TerminalId ) );
		memset( TerminalType, 0, sizeof( TerminalType ) );
		memset( TerminalName, 0, sizeof( TerminalName ) );
		memset( TermLocation, 0, sizeof( TermLocation ) );
		memset( OpeningTime, 0, sizeof( OpeningTime ) );
		memset( ClosingTime, 0, sizeof( ClosingTime ) );
		memset( CountryCode, 0, sizeof( CountryCode ) );
		memset( CurrCode, 0, sizeof( CurrCode ) );
		memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
		memset( TermPINKey, 0, sizeof( TermPINKey ) );
		memset( TermMACKey, 0, sizeof( TermMACKey ) );
		memset( BatchId, 0, sizeof( BatchId ) );
		memset( ConfigId, 0, sizeof( ConfigId ) );
		memset( TermUser, 0, sizeof( TermUser ) );
		memset( CatCode, 0, sizeof( CatCode ) );
		
		/* EXEC SQL FETCH ezmmsterminalprofile_cur INTO
			:MachineId,
			:InstId,
			:MerchantId,
			:StoreId,
			:TerminalId,
			:TerminalType,
			:TerminalName,
			:TermLocation,
			:TerminalStatus,
			:WorkingHrs,
			:OpeningTime,
			:ClosingTime,
			:CountryCode,
			:CurrCode,
			:ChipEnabled,
			:TermMasterKey,
			:TermPINKey,
			:TermMACKey,
			:KeyIntvl,	
			:EchoIntvl,
			:TxnKeyIntvl,
			:mcc,
			:BatchId,
			:ConfigId,
			:TermUser,
			:CatCode; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 26;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )391;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (unsigned char  *)MachineId;
  sqlstm.sqhstl[0] = (unsigned long )33;
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
  sqlstm.sqhstv[5] = (unsigned char  *)TerminalType;
  sqlstm.sqhstl[5] = (unsigned long )17;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         short *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned long )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (unsigned char  *)TerminalName;
  sqlstm.sqhstl[6] = (unsigned long )33;
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         short *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned long )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (unsigned char  *)TermLocation;
  sqlstm.sqhstl[7] = (unsigned long )65;
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         short *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned long )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (unsigned char  *)&TerminalStatus;
  sqlstm.sqhstl[8] = (unsigned long )1;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         short *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned long )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (unsigned char  *)&WorkingHrs;
  sqlstm.sqhstl[9] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         short *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned long )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (unsigned char  *)OpeningTime;
  sqlstm.sqhstl[10] = (unsigned long )7;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         short *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned long )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (unsigned char  *)ClosingTime;
  sqlstm.sqhstl[11] = (unsigned long )7;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         short *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned long )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (unsigned char  *)CountryCode;
  sqlstm.sqhstl[12] = (unsigned long )5;
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         short *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned long )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (unsigned char  *)CurrCode;
  sqlstm.sqhstl[13] = (unsigned long )5;
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         short *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned long )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (unsigned char  *)&ChipEnabled;
  sqlstm.sqhstl[14] = (unsigned long )1;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         short *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned long )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (unsigned char  *)TermMasterKey;
  sqlstm.sqhstl[15] = (unsigned long )65;
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         short *)0;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned long )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (unsigned char  *)TermPINKey;
  sqlstm.sqhstl[16] = (unsigned long )65;
  sqlstm.sqhsts[16] = (         int  )0;
  sqlstm.sqindv[16] = (         short *)0;
  sqlstm.sqinds[16] = (         int  )0;
  sqlstm.sqharm[16] = (unsigned long )0;
  sqlstm.sqadto[16] = (unsigned short )0;
  sqlstm.sqtdso[16] = (unsigned short )0;
  sqlstm.sqhstv[17] = (unsigned char  *)TermMACKey;
  sqlstm.sqhstl[17] = (unsigned long )65;
  sqlstm.sqhsts[17] = (         int  )0;
  sqlstm.sqindv[17] = (         short *)0;
  sqlstm.sqinds[17] = (         int  )0;
  sqlstm.sqharm[17] = (unsigned long )0;
  sqlstm.sqadto[17] = (unsigned short )0;
  sqlstm.sqtdso[17] = (unsigned short )0;
  sqlstm.sqhstv[18] = (unsigned char  *)&KeyIntvl;
  sqlstm.sqhstl[18] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[18] = (         int  )0;
  sqlstm.sqindv[18] = (         short *)0;
  sqlstm.sqinds[18] = (         int  )0;
  sqlstm.sqharm[18] = (unsigned long )0;
  sqlstm.sqadto[18] = (unsigned short )0;
  sqlstm.sqtdso[18] = (unsigned short )0;
  sqlstm.sqhstv[19] = (unsigned char  *)&EchoIntvl;
  sqlstm.sqhstl[19] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[19] = (         int  )0;
  sqlstm.sqindv[19] = (         short *)0;
  sqlstm.sqinds[19] = (         int  )0;
  sqlstm.sqharm[19] = (unsigned long )0;
  sqlstm.sqadto[19] = (unsigned short )0;
  sqlstm.sqtdso[19] = (unsigned short )0;
  sqlstm.sqhstv[20] = (unsigned char  *)&TxnKeyIntvl;
  sqlstm.sqhstl[20] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[20] = (         int  )0;
  sqlstm.sqindv[20] = (         short *)0;
  sqlstm.sqinds[20] = (         int  )0;
  sqlstm.sqharm[20] = (unsigned long )0;
  sqlstm.sqadto[20] = (unsigned short )0;
  sqlstm.sqtdso[20] = (unsigned short )0;
  sqlstm.sqhstv[21] = (unsigned char  *)&mcc;
  sqlstm.sqhstl[21] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[21] = (         int  )0;
  sqlstm.sqindv[21] = (         short *)0;
  sqlstm.sqinds[21] = (         int  )0;
  sqlstm.sqharm[21] = (unsigned long )0;
  sqlstm.sqadto[21] = (unsigned short )0;
  sqlstm.sqtdso[21] = (unsigned short )0;
  sqlstm.sqhstv[22] = (unsigned char  *)BatchId;
  sqlstm.sqhstl[22] = (unsigned long )13;
  sqlstm.sqhsts[22] = (         int  )0;
  sqlstm.sqindv[22] = (         short *)0;
  sqlstm.sqinds[22] = (         int  )0;
  sqlstm.sqharm[22] = (unsigned long )0;
  sqlstm.sqadto[22] = (unsigned short )0;
  sqlstm.sqtdso[22] = (unsigned short )0;
  sqlstm.sqhstv[23] = (unsigned char  *)ConfigId;
  sqlstm.sqhstl[23] = (unsigned long )13;
  sqlstm.sqhsts[23] = (         int  )0;
  sqlstm.sqindv[23] = (         short *)0;
  sqlstm.sqinds[23] = (         int  )0;
  sqlstm.sqharm[23] = (unsigned long )0;
  sqlstm.sqadto[23] = (unsigned short )0;
  sqlstm.sqtdso[23] = (unsigned short )0;
  sqlstm.sqhstv[24] = (unsigned char  *)TermUser;
  sqlstm.sqhstl[24] = (unsigned long )33;
  sqlstm.sqhsts[24] = (         int  )0;
  sqlstm.sqindv[24] = (         short *)0;
  sqlstm.sqinds[24] = (         int  )0;
  sqlstm.sqharm[24] = (unsigned long )0;
  sqlstm.sqadto[24] = (unsigned short )0;
  sqlstm.sqtdso[24] = (unsigned short )0;
  sqlstm.sqhstv[25] = (unsigned char  *)CatCode;
  sqlstm.sqhstl[25] = (unsigned long )17;
  sqlstm.sqhsts[25] = (         int  )0;
  sqlstm.sqindv[25] = (         short *)0;
  sqlstm.sqinds[25] = (         int  )0;
  sqlstm.sqharm[25] = (unsigned long )0;
  sqlstm.sqadto[25] = (unsigned short )0;
  sqlstm.sqtdso[25] = (unsigned short )0;
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
        	
        memset( terminalprofile_ptr + i, 0, sizeof( struct EzMMSTerminalProfile ) );
        strcpy( ( terminalprofile_ptr + i )->MachineId, MachineId );
        strcpy( ( terminalprofile_ptr + i )->InstId, InstId );
        strcpy( ( terminalprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( terminalprofile_ptr + i )->StoreId, StoreId );
        strcpy( ( terminalprofile_ptr + i )->TerminalId, TerminalId );
        strcpy( ( terminalprofile_ptr + i )->TerminalName, TerminalName );
        strcpy( ( terminalprofile_ptr + i )->TerminalType, TerminalType );
        strcpy( ( terminalprofile_ptr + i )->TerminalLocation, TermLocation );
       	( terminalprofile_ptr + i )->TerminalStatus = TerminalStatus;
       	( terminalprofile_ptr + i )->WorkingHrs = WorkingHrs;
       	strcpy( ( terminalprofile_ptr + i )->OpeningTime, OpeningTime );
        strcpy( ( terminalprofile_ptr + i )->ClosingTime, ClosingTime );
        ( terminalprofile_ptr + i )->ChipEnabled = ChipEnabled;
        strcpy( ( terminalprofile_ptr + i )->CountryCode, CountryCode );
        strcpy( ( terminalprofile_ptr + i )->CurrCode, CurrCode );
        strcpy( ( terminalprofile_ptr + i )->TermMasterKey, TermMasterKey );
        strcpy( ( terminalprofile_ptr + i )->TermPINKey, TermPINKey );
        strcpy( ( terminalprofile_ptr + i )->TermMACKey, TermMACKey );
		( terminalprofile_ptr + i )->KeyIntvl = KeyIntvl;
	 	( terminalprofile_ptr + i )->EchoIntvl = EchoIntvl;
	 	( terminalprofile_ptr + i )->TxnKeyIntvl = TxnKeyIntvl;
		( terminalprofile_ptr + i )->Mcc =  mcc ;
		strcpy( ( terminalprofile_ptr + i )->BatchId, BatchId );
		strcpy( ( terminalprofile_ptr + i )->ConfigId, ConfigId );
		strcpy( ( terminalprofile_ptr + i )->TermUser, TermUser );
		strcpy( ( terminalprofile_ptr + i )->CatCode, CatCode );
        i++;
    }
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmsterminalprofile_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 26;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )510;
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

int LoadMMSFITProfile( struct EzMMSFITProfile *ezmmsfitprofile_ptr, int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char RecordId[ 17 ];
        char InstId[ 13 ];
        char MerchantType[ 17 ];
        char MerchantId[ 16 ];
        char TerminalId[ 9 ];
        char FITRecord[ 13 ];
        char IndirectState;
        char LocalPINVerFlag;
        char LocalFingerPrintFlag;
        short MaxPINLen;
        short MinPINLen;
    /* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

    /* EXEC SQL VAR RecordId IS STRING(17); */ 

    /* EXEC SQL VAR InstId IS STRING(13); */ 

    /* EXEC SQL VAR MerchantType IS STRING(17); */ 

    /* EXEC SQL VAR MerchantId IS STRING(16); */ 

    /* EXEC SQL VAR TerminalId IS STRING(9); */ 

    /* EXEC SQL VAR FITRecord IS STRING(13); */ 


	/* EXEC SQL DECLARE ezmmsfitprofile_cur CURSOR FOR
    SELECT
        RTRIM(RECORDID),
        RTRIM(INSTID),
        RTRIM(MERCHANTTYPE),
        RTRIM(MERCHANTID),
        RTRIM(TERMINALID),
        RTRIM(FITRECORD),
        INDIRECTSTATE,
        LOCALPINVERFLAG,
        LOCALFINGERVERFLAG,
        MAXPINLEN,
        MINPINLEN
    FROM EZMMS_FITPROFILE; */ 


    /* EXEC SQL OPEN ezmmsfitprofile_cur; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 26;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0009;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )525;
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
        memset( MerchantType, 0, sizeof( MerchantType ) );
        memset( MerchantId, 0, sizeof( MerchantId ) );
        memset( TerminalId, 0, sizeof( TerminalId ) );
        memset( FITRecord, 0, sizeof( FITRecord ) );

        /* EXEC SQL FETCH ezmmsfitprofile_cur INTO
        :RecordId,
        :InstId,
        :MerchantType,
        :MerchantId,
        :TerminalId,
        :FITRecord,
        :IndirectState,
        :LocalPINVerFlag,
        :LocalFingerPrintFlag,
        :MaxPINLen,
        :MinPINLen; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 26;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )540;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqfoff = (         int )0;
        sqlstm.sqfmod = (unsigned int )2;
        sqlstm.sqhstv[0] = (unsigned char  *)RecordId;
        sqlstm.sqhstl[0] = (unsigned long )17;
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
        sqlstm.sqhstv[2] = (unsigned char  *)MerchantType;
        sqlstm.sqhstl[2] = (unsigned long )17;
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
        sqlstm.sqhstv[5] = (unsigned char  *)FITRecord;
        sqlstm.sqhstl[5] = (unsigned long )13;
        sqlstm.sqhsts[5] = (         int  )0;
        sqlstm.sqindv[5] = (         short *)0;
        sqlstm.sqinds[5] = (         int  )0;
        sqlstm.sqharm[5] = (unsigned long )0;
        sqlstm.sqadto[5] = (unsigned short )0;
        sqlstm.sqtdso[5] = (unsigned short )0;
        sqlstm.sqhstv[6] = (unsigned char  *)&IndirectState;
        sqlstm.sqhstl[6] = (unsigned long )1;
        sqlstm.sqhsts[6] = (         int  )0;
        sqlstm.sqindv[6] = (         short *)0;
        sqlstm.sqinds[6] = (         int  )0;
        sqlstm.sqharm[6] = (unsigned long )0;
        sqlstm.sqadto[6] = (unsigned short )0;
        sqlstm.sqtdso[6] = (unsigned short )0;
        sqlstm.sqhstv[7] = (unsigned char  *)&LocalPINVerFlag;
        sqlstm.sqhstl[7] = (unsigned long )1;
        sqlstm.sqhsts[7] = (         int  )0;
        sqlstm.sqindv[7] = (         short *)0;
        sqlstm.sqinds[7] = (         int  )0;
        sqlstm.sqharm[7] = (unsigned long )0;
        sqlstm.sqadto[7] = (unsigned short )0;
        sqlstm.sqtdso[7] = (unsigned short )0;
        sqlstm.sqhstv[8] = (unsigned char  *)&LocalFingerPrintFlag;
        sqlstm.sqhstl[8] = (unsigned long )1;
        sqlstm.sqhsts[8] = (         int  )0;
        sqlstm.sqindv[8] = (         short *)0;
        sqlstm.sqinds[8] = (         int  )0;
        sqlstm.sqharm[8] = (unsigned long )0;
        sqlstm.sqadto[8] = (unsigned short )0;
        sqlstm.sqtdso[8] = (unsigned short )0;
        sqlstm.sqhstv[9] = (unsigned char  *)&MaxPINLen;
        sqlstm.sqhstl[9] = (unsigned long )sizeof(short);
        sqlstm.sqhsts[9] = (         int  )0;
        sqlstm.sqindv[9] = (         short *)0;
        sqlstm.sqinds[9] = (         int  )0;
        sqlstm.sqharm[9] = (unsigned long )0;
        sqlstm.sqadto[9] = (unsigned short )0;
        sqlstm.sqtdso[9] = (unsigned short )0;
        sqlstm.sqhstv[10] = (unsigned char  *)&MinPINLen;
        sqlstm.sqhstl[10] = (unsigned long )sizeof(short);
        sqlstm.sqhsts[10] = (         int  )0;
        sqlstm.sqindv[10] = (         short *)0;
        sqlstm.sqinds[10] = (         int  )0;
        sqlstm.sqharm[10] = (unsigned long )0;
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
		memset( ezmmsfitprofile_ptr + i, 0, sizeof( struct EzMMSFITProfile ) );
        strcpy( ( ezmmsfitprofile_ptr + i )->RecordId, RecordId );
        strcpy( ( ezmmsfitprofile_ptr + i )->InstId, InstId );
        strcpy( ( ezmmsfitprofile_ptr + i )->MerchantId, MerchantId );
        strcpy( ( ezmmsfitprofile_ptr + i )->MerchantType, MerchantType );
        strcpy( ( ezmmsfitprofile_ptr + i )->TerminalId, TerminalId );
        strcpy( ( ezmmsfitprofile_ptr + i )->FITRecord, FITRecord );
        ( ezmmsfitprofile_ptr + i )->IndirectState = IndirectState;
        ( ezmmsfitprofile_ptr + i )->LocalPINVerFlag = LocalPINVerFlag;
        ( ezmmsfitprofile_ptr + i )->LocalFingerPrintFlag = LocalFingerPrintFlag;
        ( ezmmsfitprofile_ptr + i )->MaxPINLen = MaxPINLen;
        ( ezmmsfitprofile_ptr + i )->MinPINLen = MinPINLen;
        i++;
	}
    *SqlErr = sqlca.sqlcode;
    /* EXEC SQL CLOSE ezmmsfitprofile_cur; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 26;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )599;
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

int getMMSFITProfileCount( int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

    	int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_FITPROFILE; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 26;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_FITPROFILE ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )614;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int getMMSTxnCodeDescCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_TXNCODEDESC; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 26;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_TXNCODEDESC ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )633;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int LoadMMSTxnCodeDescTable( struct EzMMSTxnCodeDesc *txncodedesc_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 33 ];
		char InstId[ 13 ];
		char TxnCode[ 7 ];
		char ShortDesc[ 17 ];
		char LongDesc[ 33 ];
		char TxnType[ 3 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(33); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR ShortDesc IS STRING(17); */ 

	/* EXEC SQL VAR LongDesc IS STRING(33); */ 

	/* EXEC SQL VAR TxnType IS STRING(3); */ 

			
	/* EXEC SQL DECLARE ezmmstxncodedesc_cur CURSOR FOR
    SELECT
    	RTRIM(RECORDID),
    	RTRIM(INST_ID),
    	RTRIM(TXNCODE),
    	RTRIM(SHORTDESC),
    	RTRIM(LONGDESC),
    	RTRIM(TXNTYPE)
    FROM EZMMS_TXNCODEDESC; */ 

		
	/* EXEC SQL OPEN ezmmstxncodedesc_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 26;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0012;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )652;
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
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( ShortDesc, 0, sizeof( ShortDesc ) );
		memset( LongDesc, 0, sizeof( LongDesc ) );
		memset( TxnType, 0, sizeof( TxnType ) );
						
		/* EXEC SQL FETCH ezmmstxncodedesc_cur INTO
			:RecordId,
			:InstId,
			:TxnCode,
			:ShortDesc,
			:LongDesc,
			:TxnType; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 26;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )667;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (unsigned char  *)RecordId;
  sqlstm.sqhstl[0] = (unsigned long )33;
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
  sqlstm.sqhstv[2] = (unsigned char  *)TxnCode;
  sqlstm.sqhstl[2] = (unsigned long )7;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)ShortDesc;
  sqlstm.sqhstl[3] = (unsigned long )17;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)LongDesc;
  sqlstm.sqhstl[4] = (unsigned long )33;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (unsigned char  *)TxnType;
  sqlstm.sqhstl[5] = (unsigned long )3;
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


							
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        memset( txncodedesc_ptr + i, 0, sizeof( struct EzMMSTxnCodeDesc ) );
        strcpy( ( txncodedesc_ptr + i )->RecordId, RecordId );
        strcpy( ( txncodedesc_ptr + i )->InstId, InstId );
        strcpy( ( txncodedesc_ptr + i )->TxnCode, TxnCode );
        strcpy( ( txncodedesc_ptr + i )->ShortDesc, ShortDesc );
        strcpy( ( txncodedesc_ptr + i )->LongDesc, LongDesc );
        strcpy( ( txncodedesc_ptr + i )->TxnType, TxnType );
       	i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmstxncodedesc_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 26;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )706;
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

int getMMSTransactionDescCount( int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	    int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZMMS_TRANSACTIONDESC; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 26;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZMMS_TRANSACTIONDESC ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )721;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)&reccount;
    sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
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

int LoadMMSTransactionDescTable( struct EzMMSTransactionDesc *transactiondesc_ptr, int *SqlErr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 33 ];
		char InstId[ 13 ];
		char DeviceType[ 17 ];
		char TxnCode[ 7 ];
		char TxnDesc[ 129 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	int i = 0;
	
	/* EXEC SQL VAR RecordId IS STRING(33); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR TxnDesc IS STRING(129); */ 

			
	/* EXEC SQL DECLARE ezmmstransactiondesc_cur CURSOR FOR
    SELECT
    	RTRIM(RECORDID),
    	RTRIM(INST_ID),
    	RTRIM(DEVICETYPE),
    	RTRIM(TXNCODE),
    	RTRIM(TXNDESC)
    FROM EZMMS_TRANSACTIONDESC; */ 

		
	/* EXEC SQL OPEN ezmmstransactiondesc_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 26;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = sq0014;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )740;
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
		memset( DeviceType, 0, sizeof( DeviceType ) );
		memset( TxnCode, 0, sizeof( TxnCode ) );
		memset( TxnDesc, 0, sizeof( TxnDesc ) );
						
		/* EXEC SQL FETCH ezmmstransactiondesc_cur INTO
			:RecordId,
			:InstId,
			:DeviceType,
			:TxnCode,
			:TxnDesc; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 26;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )755;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (         int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (unsigned char  *)RecordId;
  sqlstm.sqhstl[0] = (unsigned long )33;
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
  sqlstm.sqhstv[2] = (unsigned char  *)DeviceType;
  sqlstm.sqhstl[2] = (unsigned long )17;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)TxnCode;
  sqlstm.sqhstl[3] = (unsigned long )7;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)TxnDesc;
  sqlstm.sqhstl[4] = (unsigned long )129;
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


										
		if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
        	
        memset( transactiondesc_ptr + i, 0, sizeof( struct EzMMSTransactionDesc ) );
        strcpy( ( transactiondesc_ptr + i )->RecordId, RecordId );
        strcpy( ( transactiondesc_ptr + i )->InstId, InstId );
        strcpy( ( transactiondesc_ptr + i )->DeviceType, DeviceType );
        strcpy( ( transactiondesc_ptr + i )->TxnCode, TxnCode );
        strcpy( ( transactiondesc_ptr + i )->TxnDesc, TxnDesc );
       	i++;
	}
	*SqlErr = sqlca.sqlcode;
	/* EXEC SQL CLOSE ezmmstransactiondesc_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 26;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )790;
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


