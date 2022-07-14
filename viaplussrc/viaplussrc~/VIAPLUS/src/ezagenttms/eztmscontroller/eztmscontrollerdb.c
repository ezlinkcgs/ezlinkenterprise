
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
           char  filnam[21];
};
static struct sqlcxp sqlfpn =
{
    20,
    "eztmscontrollerdb.pc"
};


static unsigned int sqlctx = 80943979;


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
   unsigned char  *sqhstv[7];
   unsigned long  sqhstl[7];
            int   sqhsts[7];
            short *sqindv[7];
            int   sqinds[7];
   unsigned long  sqharm[7];
   unsigned long  *sqharc[7];
   unsigned short  sqadto[7];
   unsigned short  sqtdso[7];
} sqlstm = {12,7};

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

 static char *sq0008 = 
"select trim(USERNAME)  from EZMMS_TERMINALUSER where (((USERMASTERCODE='2' a\
nd trim(MACHINEID)=:b0) and TERMINALID=:b1) and trim(INST_ID)=:b2)           ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,75,0,5,22,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
28,0,0,2,0,0,29,28,0,0,0,0,0,1,0,
43,0,0,3,80,0,5,49,0,0,2,2,0,1,0,1,5,0,0,1,5,0,0,
66,0,0,4,0,0,29,57,0,0,0,0,0,1,0,
81,0,0,5,73,0,4,79,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
104,0,0,6,108,0,4,111,0,0,3,2,0,1,0,2,5,0,0,1,5,0,0,1,5,0,0,
131,0,0,7,191,0,4,156,0,0,7,3,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,
174,0,0,8,153,0,9,208,0,0,3,3,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,
201,0,0,8,0,0,13,214,0,0,1,0,0,1,0,2,5,0,0,
220,0,0,8,0,0,15,236,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int updateNewConfigId( const char *I_MachineId, const char *I_ConfigId )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char MachineId[ 33 ];  
		char ConfigId[ 13 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR MachineId IS STRING( 33 ); */ 

	/* EXEC SQL VAR ConfigId IS STRING( 13 ); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( ConfigId, 0, sizeof( ConfigId ) );
	
	strcpy( MachineId, I_MachineId );
	strcpy( ConfigId, I_ConfigId );
	
	/* EXEC SQL UPDATE EZMMS_TERMINALPROFILE SET CONFIG_ID=:ConfigId WHERE RTRIM(MACHINE_ID)=:MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZMMS_TERMINALPROFILE  set CONFIG_ID=:b0 where RTRIM(\
MACHINE_ID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)ConfigId;
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
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )28;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


		return ( sqlca.sqlcode );
	}
}

int updateTermMasterKeyinTable( const char *I_MachineId, const char *I_TermMasterKey )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char MachineId[ 33 ];  
		char TermMasterKey[ 65 ];  
	/* EXEC SQL END DECLARE SECTION ; */ 


	/* EXEC SQL VAR MachineId IS STRING( 33 ); */ 

	/* EXEC SQL VAR TermMasterKey IS STRING( 65 ); */ 

	
	memset( MachineId, 0, sizeof( MachineId ) );
	memset( TermMasterKey, 0, sizeof( TermMasterKey ) );
	
	strcpy( MachineId, I_MachineId );
	strcpy( TermMasterKey, I_TermMasterKey );
	
	/* EXEC SQL UPDATE EZMMS_TERMINALPROFILE SET 
		TERM_MASTER_KEY=:TermMasterKey
	WHERE TRIM(MACHINE_ID)=:MachineId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZMMS_TERMINALPROFILE  set TERM_MASTER_KEY=:b0 where \
trim(MACHINE_ID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )43;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)TermMasterKey;
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
  sqlstm.arrsiz = 2;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )66;
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

int readInstName( const char *I_InstId, const char *I_InstName )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

    	char InstId[ 13 ];
		char InstName[ 33 ];
		short ind_var;
    /* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstName IS STRING(33); */ 

        
	memset( InstId, 0, sizeof( InstId ) );
	memset( InstName, 0, sizeof( InstName ) );
	
	strcpy( InstId, I_InstId );  
    	
	/* EXEC SQL SELECT 
		TRIM(INSTNAME)
	INTO 
		:InstName
	FROM EZINSTPROFILE WHERE TRIM(INSTID)=:InstId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select trim(INSTNAME) into :b0  from EZINSTPROFILE where tri\
m(INSTID)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )81;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)InstName;
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
    strcpy( I_InstName, InstName );
  	return sqlca.sqlcode ;
}

int readMerchantAddr( const char *I_InstId, const char *I_MerchantId, char *I_MerchantName )
{
	 /* EXEC SQL BEGIN DECLARE SECTION ; */ 

    	char InstId[ 13 ];
		char MerchantId[ 16 ];
		char MerchantName[ 33 ];
		short ind_var;
    /* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR MerchantName IS STRING(33); */ 

        
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( MerchantName, 0, sizeof( MerchantName ) );
	
	strcpy( InstId, I_InstId );  
    strcpy( MerchantId, I_MerchantId );
	
	/* EXEC SQL SELECT 
		TRIM(MERCHANTNAME)
	INTO 
		:MerchantName
	FROM EZMMSMERCHANTADDR WHERE TRIM(INSTID)=:InstId AND TRIM(MERCHANTID)=:MerchantId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 3;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select trim(MERCHANTNAME) into :b0  from EZMMSMERCHANTADDR w\
here (trim(INSTID)=:b1 and trim(MERCHANTID)=:b2)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )104;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)MerchantName;
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
    strcpy( I_MerchantName, MerchantName );
  	return sqlca.sqlcode ;
}

int readStoreAddr( const char *I_InstId, const char *I_MerchantId, const char *I_StoreId, char *I_StoreName, char *I_StoreLocation, char *I_CityName, char *I_CityCode )
{
	 /* EXEC SQL BEGIN DECLARE SECTION ; */ 

    	char InstId[ 13 ];
		char MerchantId[ 16 ];
		char StoreId[ 33 ];
		char StoreName[ 33 ];
		char StoreLocation[ 65 ];
		char CityName[ 33 ];
		char CityCode[ 17 ];
		short ind_var;
    /* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MerchantId IS STRING(16); */ 

	/* EXEC SQL VAR StoreId IS STRING(33); */ 

	/* EXEC SQL VAR StoreName IS STRING(33); */ 

	/* EXEC SQL VAR StoreLocation IS STRING(33); */ 

	/* EXEC SQL VAR CityName IS STRING(33); */ 

	/* EXEC SQL VAR CityCode IS STRING(33); */ 

	        
	memset( InstId, 0, sizeof( InstId ) );
	memset( MerchantId, 0, sizeof( MerchantId ) );
	memset( StoreId, 0, sizeof( StoreId ) );
	memset( StoreName, 0, sizeof( StoreName ) );
	memset( StoreLocation, 0, sizeof( StoreLocation ) );
	memset( CityName, 0, sizeof( CityName ) );
	memset( CityCode, 0, sizeof( CityCode ) );
	
	strcpy( InstId, I_InstId );  
    strcpy( MerchantId, I_MerchantId );
	strcpy( StoreId, I_StoreId );
	
	/* EXEC SQL SELECT 
		TRIM(STORENAME),
		TRIM(STORELOCATION),
		TRIM(CITYNAME),
		TRIM(CITYCODE)
	INTO 
		:StoreName,
		:StoreLocation,
		:CityName,
		:CityCode
	FROM EZMMSSTOREADDR WHERE TRIM(INSTID)=:InstId AND TRIM(MERCHANTID)=:MerchantId AND TRIM(STOREID)=:StoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 7;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select trim(STORENAME) ,trim(STORELOCATION) ,trim(CITYNAME) \
,trim(CITYCODE) into :b0,:b1,:b2,:b3  from EZMMSSTOREADDR where ((trim(INSTID)\
=:b4 and trim(MERCHANTID)=:b5) and trim(STOREID)=:b6)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )131;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)StoreName;
 sqlstm.sqhstl[0] = (unsigned long )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (unsigned char  *)StoreLocation;
 sqlstm.sqhstl[1] = (unsigned long )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         short *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned long )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (unsigned char  *)CityName;
 sqlstm.sqhstl[2] = (unsigned long )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         short *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned long )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (unsigned char  *)CityCode;
 sqlstm.sqhstl[3] = (unsigned long )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         short *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned long )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (unsigned char  *)InstId;
 sqlstm.sqhstl[4] = (unsigned long )13;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         short *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned long )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (unsigned char  *)MerchantId;
 sqlstm.sqhstl[5] = (unsigned long )16;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         short *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned long )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (unsigned char  *)StoreId;
 sqlstm.sqhstl[6] = (unsigned long )33;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         short *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned long )0;
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
            
    strcpy( I_StoreName, StoreName );
    strcpy( I_StoreLocation, StoreLocation );
    strcpy( I_CityName, CityName );
    strcpy( I_CityCode, CityCode );
  	return sqlca.sqlcode ;
}

int readOperatorInfo( const char *I_InstId, const char *I_MachineId, const char *I_TerminalId, char *OperatorInfo )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char MachineId[ 33 ];
		char TerminalId[ 9 ];
		char UserName[ 33 ];
		char OperatorList[ 254 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING( 13 ); */ 

	/* EXEC SQL VAR MachineId IS STRING(33); */ 

	/* EXEC SQL VAR TerminalId IS STRING(9); */ 

	/* EXEC SQL VAR OperatorList IS STRING( 254 ); */ 

	/* EXEC SQL VAR UserName IS STRING( 33 ); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	strcpy( InstId, I_InstId );
	memset( MachineId, 0, sizeof( MachineId ) );
	strcpy( MachineId, I_MachineId );
	memset( TerminalId, 0, sizeof( TerminalId ) );
	strcpy( TerminalId, I_TerminalId );
	
	memset( OperatorList, 0, sizeof( OperatorList ) );
	
	/* EXEC SQL DECLARE operatorinfo_cur CURSOR FOR
    SELECT
    	TRIM(USERNAME)
    FROM EZMMS_TERMINALUSER WHERE USERMASTERCODE='2' AND TRIM( MACHINEID)=:MachineId AND (TERMINALID)=:TerminalId AND TRIM(INST_ID)=:InstId; */ 

    
    /* EXEC SQL OPEN operatorinfo_cur; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 7;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0008;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )174;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqcmod = (unsigned int )0;
    sqlstm.sqhstv[0] = (unsigned char  *)MachineId;
    sqlstm.sqhstl[0] = (unsigned long )33;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)TerminalId;
    sqlstm.sqhstl[1] = (unsigned long )9;
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
    	memset( UserName, 0, sizeof( UserName ) );
    	
    	/* EXEC SQL FETCH operatorinfo_cur INTO
    		:UserName; */ 

{
     struct sqlexd sqlstm;
     sqlstm.sqlvsn = 12;
     sqlstm.arrsiz = 7;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )201;
     sqlstm.selerr = (unsigned short)1;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlstm.sqfoff = (         int )0;
     sqlstm.sqfmod = (unsigned int )2;
     sqlstm.sqhstv[0] = (unsigned char  *)UserName;
     sqlstm.sqhstl[0] = (unsigned long )33;
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


    	
    	if ( sqlca.sqlcode == 1403 )
        	break;
		
		if ( sqlca.sqlcode != 0 )
        	break;
    	
    	if( strlen( OperatorList ) > 1 )
    	{
    		strcat( OperatorList, "\x1c" );
    		strcat( OperatorList, UserName );
    	}
    	else
    	{
    		strcpy( OperatorList, UserName );
    	}
    	
    	
    }
	
	/* EXEC SQL CLOSE operatorinfo_cur; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 7;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )220;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	
	strcpy( OperatorInfo, OperatorList );
	return sqlca.sqlcode; 

}
