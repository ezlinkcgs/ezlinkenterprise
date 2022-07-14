
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
    "ezatmcmddb.pc"
};


static unsigned int sqlctx = 613931;


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
            void  *sqhstv[8];
   unsigned int   sqhstl[8];
            int   sqhsts[8];
            void  *sqindv[8];
            int   sqinds[8];
   unsigned int   sqharm[8];
   unsigned int   *sqharc[8];
   unsigned short  sqadto[8];
   unsigned short  sqtdso[8];
} sqlstm = {12,8};

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
5,0,0,1,104,0,5,32,0,0,4,4,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
36,0,0,2,0,0,29,41,0,0,0,0,0,1,0,
51,0,0,3,201,0,4,77,0,0,8,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,1,0,0,1,5,0,0,
};


# include <sqlca.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ezbusiness/ezbusinesstypes.h>

int ClearATMStaticStatus( char *StaticStatusCode, const char *AtmId, char *Date, char *Time )
{	
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char hAtmId[ 17 ];  
		char hDate[ 7 ];  
		char hTime[ 7 ];  
		char hStaticStatusCode[ 11 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR hAtmId IS STRING( 17 ); */ 

	/* EXEC SQL VAR hDate IS STRING( 7 ); */ 

	/* EXEC SQL VAR hTime IS STRING( 7 ); */ 

	/* EXEC SQL VAR hStaticStatusCode IS STRING( 11 ); */ 


	memset( hAtmId, 0, sizeof( hAtmId ) );
	memset( hDate, 0, sizeof( hDate ) );
	memset( hTime, 0, sizeof( hTime ) );
	memset( hStaticStatusCode, 0, sizeof( hStaticStatusCode ) );
	
	strcpy( hAtmId, AtmId );
	strcpy( hDate, Date );
	strcpy( hTime, Time );
	strcpy( hStaticStatusCode, StaticStatusCode );

	
	/* EXEC SQL UPDATE EZATMSTATUS SET 
		STATICCODE=:hStaticStatusCode,
		LOGDATE=to_date( :hDate, 'dd-mm-yy' ), 
		LOGTIME=:hTime 
	WHERE TRIM(ATMID)=:hAtmId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZATMSTATUS  set STATICCODE=:b0,LOGDATE=to_date(:b1,'\
dd-mm-yy'),LOGTIME=:b2 where trim(ATMID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)hStaticStatusCode;
 sqlstm.sqhstl[0] = (unsigned int  )11;
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
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )36;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		return ( sqlca.sqlcode );
	}
}

int readEzAtmFit( const char *I_RecordId, struct AtmFit *atmfit_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char InstId[ 13 ];
		char AtmLogicalGroup[ 17 ];
		char AtmId[ 17 ];
		char FitRecord[ 11 ];
		char SecurityId[ 11 ];
		char IndirectState;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR FitRecord IS STRING(13); */ 

	/* EXEC SQL VAR AtmLogicalGroup IS STRING(17); */ 

	/* EXEC SQL VAR AtmId IS STRING(17); */ 

	/* EXEC SQL VAR SecurityId IS STRING(11); */ 


	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( FitRecord, 0, sizeof( FitRecord ) );
	memset( AtmLogicalGroup, 0, sizeof( AtmLogicalGroup ) );
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( AtmId, 0, sizeof( AtmId ) );
	
	strcpy( Input_RecordId, I_RecordId );
				
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(INSTID),
        RTRIM(ATMLOGICALGROUP),
		RTRIM(ATMID),
		RTRIM(FITRECORD),
		RTRIM(SECURITYID),
		INDIRECTSTATE
	INTO
		:RecordId,
		:InstId,
		:AtmLogicalGroup,
		:AtmId,
		:FitRecord,
		:SecurityId,
		:IndirectState
	FROM EZATMFIT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 8;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(INSTID) ,RTRIM(ATMLOGICALGROUP\
) ,RTRIM(ATMID) ,RTRIM(FITRECORD) ,RTRIM(SECURITYID) ,INDIRECTSTATE into :b0,:\
b1,:b2,:b3,:b4,:b5,:b6  from EZATMFIT where RTRIM(RECORDID)=:b7";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )51;
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
 sqlstm.sqhstv[4] = (         void  *)FitRecord;
 sqlstm.sqhstl[4] = (unsigned int  )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)SecurityId;
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
 sqlstm.sqhstv[7] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[7] = (unsigned int  )17;
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
    	return sqlca.sqlcode;
    	
    strcpy( atmfit_ptr->RecordId, RecordId );	
   	strcpy( atmfit_ptr->InstId, InstId );
	strcpy( atmfit_ptr->AtmLogicalGroup, AtmLogicalGroup );
	strcpy( atmfit_ptr->AtmId, AtmId );
	strcpy( atmfit_ptr->FitRecord, FitRecord );
	strcpy( atmfit_ptr->SecurityId, SecurityId );
	atmfit_ptr->IndirectState = IndirectState;
	return sqlca.sqlcode;
}

