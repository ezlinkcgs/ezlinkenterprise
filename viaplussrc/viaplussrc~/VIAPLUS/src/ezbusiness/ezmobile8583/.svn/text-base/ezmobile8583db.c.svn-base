
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
           char  filnam[18];
};
static struct sqlcxp sqlfpn =
{
    17,
    "ezmobile8583db.pc"
};


static unsigned int sqlctx = 9941195;


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
5,0,0,0,0,0,27,19,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,10,0,0,1,10,0,0,
36,0,0,2,74,0,4,44,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
59,0,0,3,429,0,4,104,0,0,18,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
1,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,1,0,0,
2,3,0,0,2,3,0,0,1,5,0,0,
146,0,0,4,139,0,4,163,0,0,5,3,0,1,0,2,5,0,0,2,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
181,0,0,5,130,0,4,207,0,0,4,2,0,1,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
212,0,0,6,74,0,4,319,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
235,0,0,7,86,0,4,343,0,0,3,1,0,1,0,2,3,0,0,2,5,0,0,1,5,0,0,
262,0,0,8,156,0,4,362,0,0,2,1,0,1,0,2,3,0,0,1,5,0,0,
285,0,0,9,57,0,2,366,0,0,1,1,0,1,0,1,5,0,0,
304,0,0,10,0,0,29,367,0,0,0,0,0,1,0,
319,0,0,11,52,0,3,367,0,0,1,1,0,1,0,1,5,0,0,
338,0,0,12,0,0,29,367,0,0,0,0,0,1,0,
353,0,0,13,73,0,5,370,0,0,2,2,0,1,0,1,3,0,0,1,5,0,0,
376,0,0,14,0,0,29,371,0,0,0,0,0,1,0,
};


# include <sqlca.h>
# include <string.h>
# include <stdlib.h>
#include <ezdb/ezcardinfo.h>


int ConnectDB( char * username, char * passwd , char * db )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hUserName [32];
		char hPassword [32];
	/* EXEC SQL END DECLARE SECTION ; */ 


	strcpy( hUserName, username );
	strcat( hUserName, "@" );
	strcat( hUserName, db );
	strcpy( hPassword, passwd );

	/* EXEC SQL CONNECT :hUserName IDENTIFIED BY :hPassword ; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )10;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)hUserName;
 sqlstm.sqhstl[0] = (unsigned long )32;
 sqlstm.sqhsts[0] = (         int  )32;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)hPassword;
 sqlstm.sqhstl[1] = (unsigned long )32;
 sqlstm.sqhsts[1] = (         int  )32;
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
 sqlstm.sqlcmax = (unsigned int )100;
 sqlstm.sqlcmin = (unsigned int )2;
 sqlstm.sqlcincr = (unsigned int )1;
 sqlstm.sqlctimeout = (unsigned int )0;
 sqlstm.sqlcnowait = (unsigned int )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}



	if ( sqlca.sqlcode != 0 )
		return (sqlca.sqlcode);
	else 
		return 0 ;
}

int GetChn( char * MobileNo, char * CHN )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hMobileNum[17];
		char hChn[20];
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hMobileNum IS STRING(17); */ 

	/* EXEC SQL VAR hChn IS STRING(20); */ 

	

	memset( hMobileNum, 0, sizeof( hMobileNum ) );
	strcpy( hMobileNum, MobileNo );
	memset( hChn, 0, sizeof( hChn ) );
	


	/* EXEC SQL SELECT RTRIM(CHN) INTO :hChn FROM EZMOBILEINFO WHERE RTRIM(MOBILENUMER) = :hMobileNum ; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(CHN) into :b0  from EZMOBILEINFO where RTRIM(MO\
BILENUMER)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )36;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)hChn;
 sqlstm.sqhstl[0] = (unsigned long )20;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)hMobileNum;
 sqlstm.sqhstl[1] = (unsigned long )17;
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

	
	if ( ( sqlca.sqlcode == 1403 ) || ( sqlca.sqlcode < 0 ) )
		return -1;


	strcpy( CHN, hChn );
	return 0;
	
}



int ReadEzCardInfo( const char *cardnumber , struct EzCardInfo *cinfo )
{
        /* EXEC SQL BEGIN DECLARE SECTION ; */ 

        	char instid[11];
			char chn[ 20 ];
			char input_chn[ 20 ];
			char cardtype[ 11 ];
			char custid[ 11 ];
			char txngroupid[5];
			char limitflag;
			long expirydate;
			int status;
    		char pinoffset[ 5 ];
    		char oldpinoffset[ 5 ];
    		char tpinoffset[ 5 ];
    		char oldtpinoffset[ 5 ];
    		int  pinretrycount;
    		int  tpinretrycount;
    		char pvki;
    		long lasttxndate;
    		long lasttxntime;
    		short ind_var;
        /* EXEC SQL END DECLARE SECTION; */ 

		
		/* EXEC SQL VAR instid IS STRING(11); */ 

		/* EXEC SQL VAR chn IS STRING(20); */ 

		/* EXEC SQL VAR input_chn IS STRING(20); */ 

		/* EXEC SQL VAR cardtype IS STRING(11); */ 

        /* EXEC SQL VAR custid IS STRING(11); */ 

        /* EXEC SQL VAR txngroupid IS STRING(5); */ 

        /* EXEC SQL VAR pinoffset IS STRING(5); */ 

        /* EXEC SQL VAR oldpinoffset IS STRING(5); */ 

        /* EXEC SQL VAR tpinoffset IS STRING(5); */ 

        /* EXEC SQL VAR oldtpinoffset IS STRING(5); */ 

        
		memset( instid, 0, sizeof( instid ) );
        memset( chn, 0, sizeof( chn ) );
        memset( input_chn, 0, sizeof( input_chn ) );
        memset( cardtype, 0, sizeof( cardtype ) );
        memset( custid, 0, sizeof( custid ) );
        memset( txngroupid, 0, sizeof( txngroupid ) );
        memset( pinoffset, 0, sizeof( pinoffset ) );
        memset( oldpinoffset, 0, sizeof( oldpinoffset ) );
        memset( tpinoffset, 0, sizeof( tpinoffset ) );
        memset( oldtpinoffset, 0, sizeof( oldtpinoffset ) );
        
        strcpy( input_chn, cardnumber );
		
		/* EXEC SQL SELECT TRIM(INSTID), TRIM(CHN), TRIM(CARDTYPE), TRIM(CUSTID), TRIM(TXNGROUPID), LIMITFLG, TO_NUMBER(TO_CHAR(EXPIRYDATE,'MMYY')), STATUS, TRIM(PINOFFSET), TRIM(OLDPINOFFSET), TRIM(TPINOFFSET), TRIM(OLDTPINOFFSET), PINRETRYCOUNT, TPINRETRYCOUNT, PVKI, TO_NUMBER(TO_CHAR(LASTTXNDATE, 'DDMMYY')), LASTTXNTIME  INTO :instid, :chn, :cardtype, :custid, :txngroupid, :limitflag, :expirydate, :status, :pinoffset, :oldpinoffset, :tpinoffset, :oldtpinoffset, :pinretrycount, :tpinretrycount, :pvki, :lasttxndate:ind_var, :lasttxntime:ind_var FROM EZCARDINFO WHERE TRIM(CHN)=:input_chn; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 12;
  sqlstm.arrsiz = 18;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "select trim(INSTID) ,trim(CHN) ,trim(CARDTYPE) ,trim(CUSTID\
) ,trim(TXNGROUPID) ,LIMITFLG ,TO_NUMBER(TO_CHAR(EXPIRYDATE,'MMYY')) ,STATUS ,\
trim(PINOFFSET) ,trim(OLDPINOFFSET) ,trim(TPINOFFSET) ,trim(OLDTPINOFFSET) ,PI\
NRETRYCOUNT ,TPINRETRYCOUNT ,PVKI ,TO_NUMBER(TO_CHAR(LASTTXNDATE,'DDMMYY')) ,L\
ASTTXNTIME into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b\
14,:b15:b16,:b17:b18  from EZCARDINFO where trim(CHN)=:b19";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )59;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (unsigned char  *)instid;
  sqlstm.sqhstl[0] = (unsigned long )11;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         short *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned long )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (unsigned char  *)chn;
  sqlstm.sqhstl[1] = (unsigned long )20;
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         short *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned long )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (unsigned char  *)cardtype;
  sqlstm.sqhstl[2] = (unsigned long )11;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         short *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned long )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (unsigned char  *)custid;
  sqlstm.sqhstl[3] = (unsigned long )11;
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         short *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned long )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (unsigned char  *)txngroupid;
  sqlstm.sqhstl[4] = (unsigned long )5;
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         short *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned long )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (unsigned char  *)&limitflag;
  sqlstm.sqhstl[5] = (unsigned long )1;
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         short *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned long )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (unsigned char  *)&expirydate;
  sqlstm.sqhstl[6] = (unsigned long )sizeof(long);
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         short *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned long )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (unsigned char  *)&status;
  sqlstm.sqhstl[7] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         short *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned long )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (unsigned char  *)pinoffset;
  sqlstm.sqhstl[8] = (unsigned long )5;
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         short *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned long )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqhstv[9] = (unsigned char  *)oldpinoffset;
  sqlstm.sqhstl[9] = (unsigned long )5;
  sqlstm.sqhsts[9] = (         int  )0;
  sqlstm.sqindv[9] = (         short *)0;
  sqlstm.sqinds[9] = (         int  )0;
  sqlstm.sqharm[9] = (unsigned long )0;
  sqlstm.sqadto[9] = (unsigned short )0;
  sqlstm.sqtdso[9] = (unsigned short )0;
  sqlstm.sqhstv[10] = (unsigned char  *)tpinoffset;
  sqlstm.sqhstl[10] = (unsigned long )5;
  sqlstm.sqhsts[10] = (         int  )0;
  sqlstm.sqindv[10] = (         short *)0;
  sqlstm.sqinds[10] = (         int  )0;
  sqlstm.sqharm[10] = (unsigned long )0;
  sqlstm.sqadto[10] = (unsigned short )0;
  sqlstm.sqtdso[10] = (unsigned short )0;
  sqlstm.sqhstv[11] = (unsigned char  *)oldtpinoffset;
  sqlstm.sqhstl[11] = (unsigned long )5;
  sqlstm.sqhsts[11] = (         int  )0;
  sqlstm.sqindv[11] = (         short *)0;
  sqlstm.sqinds[11] = (         int  )0;
  sqlstm.sqharm[11] = (unsigned long )0;
  sqlstm.sqadto[11] = (unsigned short )0;
  sqlstm.sqtdso[11] = (unsigned short )0;
  sqlstm.sqhstv[12] = (unsigned char  *)&pinretrycount;
  sqlstm.sqhstl[12] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[12] = (         int  )0;
  sqlstm.sqindv[12] = (         short *)0;
  sqlstm.sqinds[12] = (         int  )0;
  sqlstm.sqharm[12] = (unsigned long )0;
  sqlstm.sqadto[12] = (unsigned short )0;
  sqlstm.sqtdso[12] = (unsigned short )0;
  sqlstm.sqhstv[13] = (unsigned char  *)&tpinretrycount;
  sqlstm.sqhstl[13] = (unsigned long )sizeof(int);
  sqlstm.sqhsts[13] = (         int  )0;
  sqlstm.sqindv[13] = (         short *)0;
  sqlstm.sqinds[13] = (         int  )0;
  sqlstm.sqharm[13] = (unsigned long )0;
  sqlstm.sqadto[13] = (unsigned short )0;
  sqlstm.sqtdso[13] = (unsigned short )0;
  sqlstm.sqhstv[14] = (unsigned char  *)&pvki;
  sqlstm.sqhstl[14] = (unsigned long )1;
  sqlstm.sqhsts[14] = (         int  )0;
  sqlstm.sqindv[14] = (         short *)0;
  sqlstm.sqinds[14] = (         int  )0;
  sqlstm.sqharm[14] = (unsigned long )0;
  sqlstm.sqadto[14] = (unsigned short )0;
  sqlstm.sqtdso[14] = (unsigned short )0;
  sqlstm.sqhstv[15] = (unsigned char  *)&lasttxndate;
  sqlstm.sqhstl[15] = (unsigned long )sizeof(long);
  sqlstm.sqhsts[15] = (         int  )0;
  sqlstm.sqindv[15] = (         short *)&ind_var;
  sqlstm.sqinds[15] = (         int  )0;
  sqlstm.sqharm[15] = (unsigned long )0;
  sqlstm.sqadto[15] = (unsigned short )0;
  sqlstm.sqtdso[15] = (unsigned short )0;
  sqlstm.sqhstv[16] = (unsigned char  *)&lasttxntime;
  sqlstm.sqhstl[16] = (unsigned long )sizeof(long);
  sqlstm.sqhsts[16] = (         int  )0;
  sqlstm.sqindv[16] = (         short *)&ind_var;
  sqlstm.sqinds[16] = (         int  )0;
  sqlstm.sqharm[16] = (unsigned long )0;
  sqlstm.sqadto[16] = (unsigned short )0;
  sqlstm.sqtdso[16] = (unsigned short )0;
  sqlstm.sqhstv[17] = (unsigned char  *)input_chn;
  sqlstm.sqhstl[17] = (unsigned long )20;
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
                return sqlca.sqlcode ;
                
		strcpy( cinfo->instid, instid );
		strcpy( cinfo->chn, chn );
        strcpy( cinfo->cardtype, cardtype );
        strcpy( cinfo->custid, custid );
        strcpy( cinfo->txngroupid, txngroupid );
        cinfo->limitflag = limitflag;
        cinfo->expirydate = expirydate;
        cinfo->status = status;
        strcpy( cinfo->pinoffset, pinoffset );
        strcpy( cinfo->oldpinoffset, oldpinoffset );
		strcpy( cinfo->tpinoffset, tpinoffset );
		strcpy( cinfo->oldtpinoffset, oldtpinoffset );
        cinfo->pinretrycount = pinretrycount;
        cinfo->tpinretrycount = tpinretrycount;
        cinfo->pvki = pvki;
        cinfo->lasttxndate = lasttxndate;
        cinfo->lasttxntime = lasttxntime;
        
        return sqlca.sqlcode ;

}
int ReadFirstAccount( const char *InstId, const char *CardNo, const char *AccountType, char *AccountNo, int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

                char instid[ 11 ];
                char input_instid[ 11 ];
                char chn[ 20 ];
                char input_chn[ 20 ];
                char acct_no[ 33 ];
                char input_acct_type[ 11 ];
                int acct_priority;
        /* EXEC SQL END DECLARE SECTION ; */ 


        char TempAccountNo[ 33 ];
        int AccountPriority = 9999;

        /* EXEC SQL VAR instid IS STRING(11); */ 

        /* EXEC SQL VAR input_instid IS STRING(11); */ 

        /* EXEC SQL VAR chn IS STRING(20); */ 

        /* EXEC SQL VAR input_chn IS STRING(20); */ 

        /* EXEC SQL VAR acct_no IS STRING(33); */ 

        /* EXEC SQL VAR input_acct_type IS STRING(11); */ 


        memset( instid, 0, sizeof( instid ) );
        memset( input_instid, 0, sizeof( input_instid ) );
        memset( chn, 0, sizeof( chn ) );
        memset( input_chn, 0, sizeof( input_chn ) );
        memset( acct_no, 0, sizeof( acct_no ) );
        memset( input_acct_type, 0, sizeof( input_acct_type ) );

        strcpy( input_instid, InstId );
        strcpy( input_chn, CardNo );
        strcpy( input_acct_type, AccountType );

        /* EXEC SQL SELECT TRIM(ACCOUNTNO), ACCOUNTPRIORITY INTO :acct_no, :acct_priority FROM EZAUTHREL WHERE TRIM(INSTID)=:input_instid AND TRIM(CHN)=:input_chn AND TRIM(ACCOUNTTYPE)=:input_acct_type; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 18;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select trim(ACCOUNTNO) ,ACCOUNTPRIORITY into :b0,:b1 \
 from EZAUTHREL where ((trim(INSTID)=:b2 and trim(CHN)=:b3) and trim(ACCOUNTTY\
PE)=:b4)";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )146;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)acct_no;
        sqlstm.sqhstl[0] = (unsigned long )33;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&acct_priority;
        sqlstm.sqhstl[1] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)input_instid;
        sqlstm.sqhstl[2] = (unsigned long )11;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)input_chn;
        sqlstm.sqhstl[3] = (unsigned long )20;
        sqlstm.sqhsts[3] = (         int  )0;
        sqlstm.sqindv[3] = (         short *)0;
        sqlstm.sqinds[3] = (         int  )0;
        sqlstm.sqharm[3] = (unsigned long )0;
        sqlstm.sqadto[3] = (unsigned short )0;
        sqlstm.sqtdso[3] = (unsigned short )0;
        sqlstm.sqhstv[4] = (unsigned char  *)input_acct_type;
        sqlstm.sqhstl[4] = (unsigned long )11;
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


       	if( acct_priority < AccountPriority )
        {
       	        AccountPriority = acct_priority;
               	memset( AccountNo, 0, sizeof( AccountNo ) );
                strcpy( AccountNo, acct_no );
       	}

        *SqlErr = sqlca.sqlcode;
        if( *SqlErr != 0 )
                return -1;
	else
	        return 1;
}

int SearchEzAccountInfo( const char *InstId, const char *AccountNo, char *BranchCode, char *ProductCode )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

        char instid[ 11 ];
        char input_instid[ 11 ];
        char accountno[ 33 ];
        char input_accountno[ 33 ];
        short ind_var;
        char branchcode[ 13 ];
	char productcode[ 11 ];
    	/* EXEC SQL END DECLARE SECTION ; */ 

    	
	/* EXEC SQL VAR instid IS STRING(11); */ 

	/* EXEC SQL VAR input_instid IS STRING(11); */ 

	/* EXEC SQL VAR accountno IS STRING(33); */ 

	/* EXEC SQL VAR input_accountno IS STRING(33); */ 

    	/* EXEC SQL VAR branchcode IS STRING(13); */ 

        /* EXEC SQL VAR productcode IS STRING(11); */ 

	
	memset( instid, 0, sizeof( instid ) );
	memset( input_instid, 0, sizeof( input_instid ) );
	memset( accountno, 0, sizeof( accountno ) );
	memset( input_accountno, 0, sizeof( input_accountno ) );
    	memset( branchcode, 0, sizeof( branchcode ) );
	memset( productcode, 0, sizeof( productcode ) );

	strcpy( input_instid, InstId );
	strcpy( input_accountno, AccountNo );
	
	/* EXEC SQL SELECT TRIM(BRANCHCODE), TRIM(PRODUCTCODE) INTO :branchcode:ind_var, :productcode:ind_var FROM EZACCOUNTINFO WHERE TRIM(INSTID)=:input_instid AND TRIM(ACCOUNTNO)=:input_accountno; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 18;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select trim(BRANCHCODE) ,trim(PRODUCTCODE) into :b0:b1,:b2:b\
3  from EZACCOUNTINFO where (trim(INSTID)=:b4 and trim(ACCOUNTNO)=:b5)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )181;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)branchcode;
 sqlstm.sqhstl[0] = (unsigned long )13;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)productcode;
 sqlstm.sqhstl[1] = (unsigned long )11;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)input_instid;
 sqlstm.sqhstl[2] = (unsigned long )11;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)input_accountno;
 sqlstm.sqhstl[3] = (unsigned long )33;
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



    	if ( sqlca.sqlcode != 0 )
            return sqlca.sqlcode ;
       
	    strcpy( BranchCode, branchcode );
	    strcpy( ProductCode, productcode );
    
    	return sqlca.sqlcode ;
}

/*
int readPrimaryAccount( const char *instNo, const char *customerID, const char *acctType, struct ezcustomer *cust )
{
	EXEC SQL BEGIN DECLARE SECTION ;
		char iin[ 11 ];
		char input_iin[ 11 ];
		char custid[ 11 ];
		char input_custid[ 11 ];
		char name[ 51 ];
		char address[ 101 ];
		char pflag;
		char pcustid[ 11 ];
		char branch_id[ 11 ];
		char acct_type[ 3 ];
		char input_acct_type[ 3 ];
		char acct_subtype[ 11 ];
		char acct_no[ 33 ];
		char acct_flag;
		char default_acct_flag;
		short ind_var;
	EXEC SQL END DECLARE SECTION ;

	EXEC SQL VAR iin IS STRING(11);
	EXEC SQL VAR input_iin IS STRING(11);
	EXEC SQL VAR custid IS STRING(11);
	EXEC SQL VAR input_custid IS STRING(11);
	EXEC SQL VAR name IS STRING(51);
	EXEC SQL VAR address IS STRING(101);
	EXEC SQL VAR pcustid IS STRING(11);
	EXEC SQL VAR branch_id IS STRING(11);
	EXEC SQL VAR acct_type IS STRING(3);
	EXEC SQL VAR input_acct_type IS STRING(3);
	EXEC SQL VAR acct_subtype IS STRING(11);
	EXEC SQL VAR acct_no IS STRING(33);

	memset( iin, 0, sizeof( iin ) );
	memset( input_iin, 0, sizeof( iin ) );
	memset( custid, 0, sizeof( custid ) );
	memset( input_custid, 0, sizeof( input_custid ) );
	memset( name, 0, sizeof( name ) );
	memset( address, 0, sizeof( address ) );
	memset( pcustid, 0, sizeof( pcustid ) );
	memset( branch_id, 0, sizeof( branch_id ) );
	memset( acct_type, 0, sizeof( acct_type ) );
	memset( input_acct_type, 0, sizeof( input_acct_type ) );
	memset( acct_subtype, 0, sizeof( acct_subtype ) );
	memset( acct_no, 0, sizeof( acct_no ) );

	strcpy( input_iin, instNo );
	strcpy( input_custid, customerID );
	strcpy( input_acct_type, acctType );

	if( !strcmp( acctType, "00" ) )
		EXEC SQL SELECT TRIM(IIN), TRIM(CUSTID), TRIM(NAME), TRIM(ADDRESS), PFLAG, TRIM(PCUSTID), TRIM(BRANCH_ID), TRIM(ACCT_TYPE), TRIM(ACCT_SUBTYPE), TRIM(ACCT_NO), ACCT_FLAG, DEFAULT_ACCT_FLAG INTO :iin, :custid, :name:ind_var, :address:ind_var, :pflag:ind_var, :pcustid:ind_var, :branch_id, :acct_type, :acct_subtype, :acct_no, :acct_flag, default_acct_flag FROM EZCUSTOMER WHERE TRIM(IIN)=:input_iin AND TRIM(CUSTID)=:input_custid AND DEFAULT_ACCT_FLAG='1';
	else
		EXEC SQL SELECT TRIM(IIN), TRIM(CUSTID), TRIM(NAME), TRIM(ADDRESS), PFLAG, TRIM(PCUSTID), TRIM(BRANCH_ID), TRIM(ACCT_TYPE), TRIM(ACCT_SUBTYPE), TRIM(ACCT_NO), ACCT_FLAG, DEFAULT_ACCT_FLAG INTO :iin, :custid, :name:ind_var, :address:ind_var, :pflag:ind_var, :pcustid:ind_var, :branch_id, :acct_type, :acct_subtype, :acct_no, :acct_flag, default_acct_flag:ind_var FROM EZCUSTOMER WHERE TRIM(IIN)=:input_iin AND TRIM(CUSTID)=:input_custid AND TRIM(ACCT_TYPE)=:input_acct_type AND ACCT_FLAG='1';

	if( sqlca.sqlcode == 1403 )
	{
		if( !strcmp( acctType, "00" ) )
			EXEC SQL SELECT TRIM(IIN), TRIM(CUSTID), TRIM(NAME), TRIM(ADDRESS), PFLAG, TRIM(PCUSTID), TRIM(BRANCH_ID), TRIM(ACCT_TYPE), TRIM(ACCT_SUBTYPE), TRIM(ACCT_NO), ACCT_FLAG, DEFAULT_ACCT_FLAG INTO :iin, :custid, :name:ind_var, :address:ind_var, :pflag:ind_var, :pcustid:ind_var, :branch_id, :acct_type, :acct_subtype, :acct_no, :acct_flag, default_acct_flag FROM EZCUSTOMER WHERE TRIM(IIN)=:input_iin AND TRIM(CUSTID)=:input_custid AND DEFAULT_ACCT_FLAG='2';
		else
			EXEC SQL SELECT TRIM(IIN), TRIM(CUSTID), TRIM(NAME), TRIM(ADDRESS), PFLAG, TRIM(PCUSTID), TRIM(BRANCH_ID), TRIM(ACCT_TYPE), TRIM(ACCT_SUBTYPE), TRIM(ACCT_NO), ACCT_FLAG, DEFAULT_ACCT_FLAG INTO :iin, :custid, :name:ind_var, :address:ind_var, :pflag:ind_var, :pcustid:ind_var, :branch_id, :acct_type, :acct_subtype, :acct_no, :acct_flag, default_acct_flag:ind_var FROM EZCUSTOMER WHERE TRIM(IIN)=:input_iin AND TRIM(CUSTID)=:input_custid AND TRIM(ACCT_TYPE)=:input_acct_type AND ACCT_FLAG='2';
	}

	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode ;
	
	strcpy( cust->iin, iin );
	strcpy( cust->custid, custid );
	strcpy( cust->name, name );
	strcpy( cust->address, address );
	cust->pflag = pflag;
	strcpy( cust->pcustid, pcustid );
	strcpy( cust->branch_id, branch_id );
	strcpy( cust->acct_type, acct_type );
	strcpy( cust->acct_subtype, acct_subtype );
	strcpy( cust->acct_no, acct_no );
	cust->acct_flag = acct_flag;
	cust->default_acct_flag = default_acct_flag;
	
	return sqlca.sqlcode ;

}
*/
int GetMobileFileInfo( char *ApplCode, char *FileName )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hApplCode[17];
		char hFileName[31];
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hApplCode IS STRING(17); */ 

	/* EXEC SQL VAR hFileName IS STRING(31); */ 

	

	memset( hApplCode, 0, sizeof( hApplCode ) );
	memset( hFileName, 0, sizeof( hFileName ) );

	strcpy( hApplCode, ApplCode );

	/* EXEC SQL SELECT FILENAME INTO :hFileName FROM EZMOBILEFILEINFO WHERE TRIM(MOBILECODE) =:hApplCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 18;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select FILENAME into :b0  from EZMOBILEFILEINFO where trim(M\
OBILECODE)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )212;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)hFileName;
 sqlstm.sqhstl[0] = (unsigned long )31;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)hApplCode;
 sqlstm.sqhstl[1] = (unsigned long )17;
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

	
	if ( ( sqlca.sqlcode == 1403 ) || ( sqlca.sqlcode < 0 ) )
		return sqlca.sqlcode;

	strcpy( FileName, hFileName );
	return 0;
}
	
int GetMobileTranInfo( char * ApplCode, int *Pcode, char * Act_Type )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hApplCode[17];
		int  hPcode;
		char hAct_Type[3];
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hApplCode IS STRING(17); */ 

	/* EXEC SQL VAR hAct_Type IS STRING(3); */ 

	
	memset( hApplCode, 0, sizeof( hApplCode ) );
	strcpy( hApplCode, ApplCode );
	memset( hAct_Type, 0, sizeof( hAct_Type ) );


	/* EXEC SQL SELECT PCODE , ACT_TYPE INTO :hPcode , :hAct_Type FROM EZMOBILETRANSINFO WHERE TRIM(MOBILECODE) = :hApplCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 18;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select PCODE ,ACT_TYPE into :b0,:b1  from EZMOBILETRANSINFO \
where trim(MOBILECODE)=:b2";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )235;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)&hPcode;
 sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)hAct_Type;
 sqlstm.sqhstl[1] = (unsigned long )3;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)hApplCode;
 sqlstm.sqhstl[2] = (unsigned long )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
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

	
	if ( ( sqlca.sqlcode == 1403 ) || ( sqlca.sqlcode < 0 ) )
		sqlca.sqlcode;

	*Pcode = hPcode;
	strcpy( Act_Type, hAct_Type );
	
	return 0;
}

int GenerateDeviceTraceNum( char * DeviceId )
{
        /* EXEC SQL BEGIN DECLARE SECTION ; */ 
                                                                                                     char hDeviceId[9];
                int hTraceNum ;                                                                                                      /* EXEC SQL END DECLARE SECTION ; */ 
                                                                                       

        /* EXEC SQL VAR hDeviceId IS STRING(9); */ 


        memset( hDeviceId, 0, sizeof( hDeviceId ) );
                                                                                                                                     strcpy( hDeviceId, DeviceId );                                                                                       
        /* EXEC SQL SELECT TRACE_NUM INTO :hTraceNum FROM DEVICE_TRACE_NUM WHERE RTRIM( DEVICE_ID ) = :hDeviceId AND TO_CHAR(TRACE_DATE,'DD-MM-YYYY') =TO_CHAR(SYSDATE, 'DD-MM-YYYY') FOR UPDATE ; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 18;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "select TRACE_NUM into :b0  from DEVICE_TRACE_NUM wher\
e (RTRIM(DEVICE_ID)=:b1 and TO_CHAR(TRACE_DATE,'DD-MM-YYYY')=TO_CHAR(SYSDATE,'\
DD-MM-YYYY')) for update ";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )262;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)&hTraceNum;
        sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)hDeviceId;
        sqlstm.sqhstl[1] = (unsigned long )9;
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
        {
                /* EXEC SQL DELETE FROM DEVICE_TRACE_NUM WHERE RTRIM( DEVICE_ID ) = :hDeviceId ; */ 

{
                struct sqlexd sqlstm;
                sqlstm.sqlvsn = 12;
                sqlstm.arrsiz = 18;
                sqlstm.sqladtp = &sqladt;
                sqlstm.sqltdsp = &sqltds;
                sqlstm.stmt = "delete  from DEVICE_TRACE_NUM  where RTRIM(DE\
VICE_ID)=:b0";
                sqlstm.iters = (unsigned int  )1;
                sqlstm.offset = (unsigned int  )285;
                sqlstm.cud = sqlcud0;
                sqlstm.sqlest = (unsigned char  *)&sqlca;
                sqlstm.sqlety = (unsigned short)4352;
                sqlstm.occurs = (unsigned int  )0;
                sqlstm.sqhstv[0] = (unsigned char  *)hDeviceId;
                sqlstm.sqhstl[0] = (unsigned long )9;
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


                /* EXEC SQL COMMIT; */ 

{
                struct sqlexd sqlstm;
                sqlstm.sqlvsn = 12;
                sqlstm.arrsiz = 18;
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

                                                                                                             /* EXEC SQL INSERT INTO DEVICE_TRACE_NUM VALUES ( :hDeviceId, 1, SYSDATE ); */ 

{
                                                                                                                                             struct sqlexd sqlstm;
                                                                                                                                             sqlstm.sqlvsn = 12;
                                                                                                                                             sqlstm.arrsiz = 18;
                                                                                                                                             sqlstm.sqladtp = &sqladt;
                                                                                                                                             sqlstm.sqltdsp = &sqltds;
                                                                                                                                             sqlstm.stmt = "\
insert into DEVICE_TRACE_NUM  values (:b0,1,SYSDATE)";
                                                                                                                                             sqlstm.iters = (unsigned int  )1;
                                                                                                                                             sqlstm.offset = (unsigned int  )319;
                                                                                                                                             sqlstm.cud = sqlcud0;
                                                                                                                                             sqlstm.sqlest = (unsigned char  *)&sqlca;
                                                                                                                                             sqlstm.sqlety = (unsigned short)4352;
                                                                                                                                             sqlstm.occurs = (unsigned int  )0;
                                                                                                                                             sqlstm.sqhstv[0] = (unsigned char  *)hDeviceId;
                                                                                                                                             sqlstm.sqhstl[0] = (unsigned long )9;
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

                                                     /* EXEC SQL COMMIT; */ 

{
                                                                                                                                                                                                                                                                          struct sqlexd sqlstm;
                                                                                                                                                                                                                                                                          sqlstm.sqlvsn = 12;
                                                                                                                                                                                                                                                                          sqlstm.arrsiz = 18;
                                                                                                                                                                                                                                                                          sqlstm.sqladtp = &sqladt;
                                                                                                                                                                                                                                                                          sqlstm.sqltdsp = &sqltds;
                                                                                                                                                                                                                                                                          sqlstm.iters = (unsigned int  )1;
                                                                                                                                                                                                                                                                          sqlstm.offset = (unsigned int  )338;
                                                                                                                                                                                                                                                                          sqlstm.cud = sqlcud0;
                                                                                                                                                                                                                                                                          sqlstm.sqlest = (unsigned char  *)&sqlca;
                                                                                                                                                                                                                                                                          sqlstm.sqlety = (unsigned short)4352;
                                                                                                                                                                                                                                                                          sqlstm.occurs = (unsigned int  )0;
                                                                                                                                                                                                                                                                          sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


                hTraceNum = 1 ;                                                                                                              return hTraceNum;
        }                                                                                                                            else
        {                                                                                                                                    /* EXEC SQL UPDATE DEVICE_TRACE_NUM SET TRACE_NUM = :hTraceNum+1 WHERE RTRIM( DEVICE_ID ) = :hDeviceId ; */ 

{
                                                                                                                                             struct sqlexd sqlstm;
                                                                                                                                             sqlstm.sqlvsn = 12;
                                                                                                                                             sqlstm.arrsiz = 18;
                                                                                                                                             sqlstm.sqladtp = &sqladt;
                                                                                                                                             sqlstm.sqltdsp = &sqltds;
                                                                                                                                             sqlstm.stmt = "\
update DEVICE_TRACE_NUM  set TRACE_NUM=(:b0+1) where RTRIM(DEVICE_ID)=:b1";
                                                                                                                                             sqlstm.iters = (unsigned int  )1;
                                                                                                                                             sqlstm.offset = (unsigned int  )353;
                                                                                                                                             sqlstm.cud = sqlcud0;
                                                                                                                                             sqlstm.sqlest = (unsigned char  *)&sqlca;
                                                                                                                                             sqlstm.sqlety = (unsigned short)4352;
                                                                                                                                             sqlstm.occurs = (unsigned int  )0;
                                                                                                                                             sqlstm.sqhstv[0] = (unsigned char  *)&hTraceNum;
                                                                                                                                             sqlstm.sqhstl[0] = (unsigned long )sizeof(int);
                                                                                                                                             sqlstm.sqhsts[0] = (         int  )0;
                                                                                                                                             sqlstm.sqindv[0] = (         short *)0;
                                                                                                                                             sqlstm.sqinds[0] = (         int  )0;
                                                                                                                                             sqlstm.sqharm[0] = (unsigned long )0;
                                                                                                                                             sqlstm.sqadto[0] = (unsigned short )0;
                                                                                                                                             sqlstm.sqtdso[0] = (unsigned short )0;
                                                                                                                                             sqlstm.sqhstv[1] = (unsigned char  *)hDeviceId;
                                                                                                                                             sqlstm.sqhstl[1] = (unsigned long )9;
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
                        return -1;                                                                                                           /* EXEC SQL COMMIT; */ 

{
                                                                                                                                             struct sqlexd sqlstm;
                                                                                                                                             sqlstm.sqlvsn = 12;
                                                                                                                                             sqlstm.arrsiz = 18;
                                                                                                                                             sqlstm.sqladtp = &sqladt;
                                                                                                                                             sqlstm.sqltdsp = &sqltds;
                                                                                                                                             sqlstm.iters = (unsigned int  )1;
                                                                                                                                             sqlstm.offset = (unsigned int  )376;
                                                                                                                                             sqlstm.cud = sqlcud0;
                                                                                                                                             sqlstm.sqlest = (unsigned char  *)&sqlca;
                                                                                                                                             sqlstm.sqlety = (unsigned short)4352;
                                                                                                                                             sqlstm.occurs = (unsigned int  )0;
                                                                                                                                             sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}

                                                                                                             return hTraceNum+1 ;
        }
}

