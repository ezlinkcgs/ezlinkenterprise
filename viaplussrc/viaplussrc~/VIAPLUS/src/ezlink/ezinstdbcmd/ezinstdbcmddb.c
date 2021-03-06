
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
    "ezinstdbcmddb.pc"
};


static unsigned int sqlctx = 4978475;


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
            void  *sqhstv[24];
   unsigned int   sqhstl[24];
            int   sqhsts[24];
            void  *sqindv[24];
            int   sqinds[24];
   unsigned int   sqharm[24];
   unsigned int   *sqharc[24];
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
5,0,0,1,89,0,4,21,0,0,2,1,0,1,0,2,5,0,0,1,97,0,0,
28,0,0,2,319,0,4,73,0,0,12,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,1,0,0,1,5,0,0,
91,0,0,3,240,0,4,153,0,0,10,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
146,0,0,4,141,0,4,214,0,0,6,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,3,0,0,1,
5,0,0,
185,0,0,5,202,0,4,272,0,0,8,1,0,1,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,1,5,0,0,
232,0,0,6,129,0,4,328,0,0,5,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
267,0,0,7,152,0,4,372,0,0,5,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
302,0,0,8,184,0,4,422,0,0,7,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,1,5,0,0,
345,0,0,9,154,0,4,475,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
380,0,0,10,109,0,4,510,0,0,4,1,0,1,0,2,3,0,0,2,1,0,0,2,1,0,0,1,3,0,0,
411,0,0,11,211,0,4,560,0,0,9,1,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,1,0,0,2,3,0,0,1,5,0,0,
462,0,0,12,116,0,4,614,0,0,3,1,0,1,0,2,5,0,0,2,5,0,0,1,5,0,0,
489,0,0,13,198,0,4,662,0,0,8,1,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,1,5,0,0,
536,0,0,14,650,0,4,765,0,0,24,1,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,
0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,3,0,0,2,5,0,0,1,5,0,0,
647,0,0,15,154,0,4,867,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,1,5,0,0,
682,0,0,16,212,0,4,918,0,0,9,1,0,1,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
1,0,0,2,1,0,0,2,1,0,0,1,5,0,0,
733,0,0,17,109,0,4,968,0,0,3,1,0,1,0,2,5,0,0,2,3,0,0,1,5,0,0,
760,0,0,18,198,0,4,1017,0,0,8,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,3,0,0,1,5,0,0,
807,0,0,19,243,0,4,1086,0,0,9,2,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,
858,0,0,20,478,0,4,1176,0,0,16,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,1,5,0,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezlink/ezinstdbtypes.h>

int readEzInstRouteType( const char *I_InstRouteType, struct EzInstRouteTypeMemory *instroutetype_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstRouteType[ 17 ];
		char Input_InstRouteType[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstRouteType IS STRING(17); */ 

	
	memset( InstRouteType, 0, sizeof( InstRouteType ) );
	memset( Input_InstRouteType, 0, sizeof( Input_InstRouteType ) );
	
	strcpy( Input_InstRouteType, I_InstRouteType );
	
	/* EXEC SQL SELECT
		RTRIM(INSTROUTETYPE)
	INTO
		:InstRouteType
	FROM EZINSTROUTETYPE WHERE RTRIM(INSTROUTETYPE)=:Input_InstRouteType; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 2;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTROUTETYPE) into :b0  from EZINSTROUTETYPE w\
here RTRIM(INSTROUTETYPE)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstRouteType;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)Input_InstRouteType;
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

	strcpy( instroutetype_ptr->InstRouteType, InstRouteType );
	return sqlca.sqlcode;
}

int readEzInstProfile( const char *I_InstId, struct EzInstProfileMemory *instprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ];
		char InstRouteType[ 17 ];
		char InstType[ 17 ];
		char InstSecurityGroup[ 17 ];
        char InstTerminalGroup[ 17 ];
        char InstAuthGroup[ 17 ];
        char InstCurrencyCode[ 6 ];
        int MaxATMPINCount;
        int MaxTelePINCount;
        char PrimaryBin[ 13 ];
        char PADSSEnabled;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR InstType IS STRING(17); */ 

	/* EXEC SQL VAR InstSecurityGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstTerminalGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstAuthGroup IS STRING(17); */ 

	/* EXEC SQL VAR InstCurrencyCode IS STRING(17); */ 

	/* EXEC SQL VAR PrimaryBin IS STRING(13); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( InstRouteType, 0, sizeof( InstRouteType ) );
	memset( InstType, 0, sizeof( InstType ) );
	memset( InstSecurityGroup, 0, sizeof( InstSecurityGroup ) );
	memset( InstTerminalGroup, 0, sizeof( InstTerminalGroup ) );
	memset( InstAuthGroup, 0, sizeof( InstAuthGroup) );
	memset( InstCurrencyCode, 0, sizeof( InstCurrencyCode ) );
	memset( PrimaryBin, 0, sizeof( PrimaryBin ) );
	
	strcpy( Input_InstId, I_InstId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(INSTROUTETYPE),
		RTRIM(INSTTYPE),
		RTRIM(INSTSECURITYGROUP),
		RTRIM(INSTTERMINALGROUP),
		RTRIM(INSTAUTHGROUP),
		RTRIM(INSTCURRENCYCODE),
		MAXATMPINCOUNT,
		MAXTELEPINCOUNT,
		RTRIM(PRIMARYBIN),
		PADSSENABLED
	INTO
		:InstId,
		:InstRouteType,
		:InstType,
		:InstSecurityGroup,
		:InstTerminalGroup,
		:InstAuthGroup,
		:InstCurrencyCode,
		:MaxATMPINCount,
		:MaxTelePINCount,
		:PrimaryBin,
		:PADSSEnabled
	FROM EZINSTPROFILE WHERE RTRIM(INSTID)=:Input_InstId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(INSTROUTETYPE) ,RTRIM(INSTTYPE) \
,RTRIM(INSTSECURITYGROUP) ,RTRIM(INSTTERMINALGROUP) ,RTRIM(INSTAUTHGROUP) ,RTR\
IM(INSTCURRENCYCODE) ,MAXATMPINCOUNT ,MAXTELEPINCOUNT ,RTRIM(PRIMARYBIN) ,PADS\
SENABLED into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10  from EZINSTPROFILE\
 where RTRIM(INSTID)=:b11";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )28;
 sqlstm.selerr = (unsigned short)1;
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
 sqlstm.sqhstv[1] = (         void  *)InstRouteType;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)InstType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)InstSecurityGroup;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)InstTerminalGroup;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)InstAuthGroup;
 sqlstm.sqhstl[5] = (unsigned int  )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)InstCurrencyCode;
 sqlstm.sqhstl[6] = (unsigned int  )17;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&MaxATMPINCount;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&MaxTelePINCount;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)PrimaryBin;
 sqlstm.sqhstl[9] = (unsigned int  )13;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&PADSSEnabled;
 sqlstm.sqhstl[10] = (unsigned int  )1;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)Input_InstId;
 sqlstm.sqhstl[11] = (unsigned int  )13;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
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

	strcpy( instprofile_ptr->InstId, InstId );
	strcpy( instprofile_ptr->InstRouteType, InstRouteType );
	strcpy( instprofile_ptr->InstType, InstType );
	strcpy( instprofile_ptr->InstSecurityGroup, InstSecurityGroup );
	strcpy( instprofile_ptr->InstTerminalGroup, InstTerminalGroup );
	strcpy( instprofile_ptr->InstAuthGroup, InstAuthGroup );
	strcpy( instprofile_ptr->InstCurrencyCode, InstCurrencyCode );
	instprofile_ptr->MaxATMPINCount = MaxATMPINCount ;
	instprofile_ptr->MaxTelePINCount = MaxTelePINCount;
	strcpy( instprofile_ptr->PrimaryBin, PrimaryBin );
	instprofile_ptr->PADSSEnabled = PADSSEnabled;
	return sqlca.sqlcode;
}

int readEzInstSelect( const char *I_RecordNo, struct EzInstSelectMemory *instselect_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char DeviceType[ 17 ];
		char FieldType[ 65 ];
		char FromOffset[ 17 ];
		char ToOffset[ 17 ];
		char FieldVal[ 129 ];
		int Priority;
		char InstId[ 13 ];
		char InstType[ 11 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR FieldType IS STRING(65); */ 

	/* EXEC SQL VAR FromOffset IS STRING(17); */ 

	/* EXEC SQL VAR ToOffset IS STRING(17); */ 

	/* EXEC SQL VAR FieldVal IS STRING(129); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR InstType IS STRING(11); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( FieldType, 0, sizeof( FieldType ) );
	memset( FromOffset, 0, sizeof( FromOffset ) );
	memset( ToOffset, 0, sizeof( ToOffset ) );
	memset( FieldVal, 0, sizeof( FieldVal ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( InstType, 0, sizeof( InstType ) );
	
	strcpy( Input_RecordId, I_RecordNo );
	
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(DEVICETYPE),
		RTRIM(FIELDTYPE),
		RTRIM(FROMOFFSET),
		RTRIM(TOOFFSET),
		RTRIM(FIELDVAL),
		PRIORITY,
		RTRIM(INSTID),
		RTRIM(INSTTYPE)
	INTO
		:RecordId,
		:DeviceType,
		:FieldType,
		:FromOffset,
		:ToOffset,
		:FieldVal,
		:Priority,
		:InstId,
		:InstType
	FROM EZINSTSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(DEVICETYPE) ,RTRIM(FIELDTYPE) \
,RTRIM(FROMOFFSET) ,RTRIM(TOOFFSET) ,RTRIM(FIELDVAL) ,PRIORITY ,RTRIM(INSTID) \
,RTRIM(INSTTYPE) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8  from EZINSTSELECT w\
here RTRIM(RECORDID)=:b9";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )91;
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
 sqlstm.sqhstv[1] = (         void  *)DeviceType;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)FieldType;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)FromOffset;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)ToOffset;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)FieldVal;
 sqlstm.sqhstl[5] = (unsigned int  )129;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&Priority;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)InstId;
 sqlstm.sqhstl[7] = (unsigned int  )13;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)InstType;
 sqlstm.sqhstl[8] = (unsigned int  )11;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[9] = (unsigned int  )17;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
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


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;

	strcpy( instselect_ptr->RecordId, RecordId );
	strcpy( instselect_ptr->DeviceType, DeviceType );
	strcpy( instselect_ptr->FieldType, FieldType );
	strcpy( instselect_ptr->FromOffset, FromOffset );
	strcpy( instselect_ptr->ToOffset, ToOffset );
	instselect_ptr->Priority = Priority;
	strcpy( instselect_ptr->FieldVal, FieldVal );
	strcpy( instselect_ptr->InstId, InstId );
	strcpy( instselect_ptr->InstType, InstType );
	
	return sqlca.sqlcode;
}

int readEzBINSelect( const char *I_RecordNo, struct EzBINSelectMemory *binselect_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char BIN[ 13 ];
		char InstId[ 13 ];
		char BINRangeReq;
		short Priority;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( BIN, 0, sizeof( BIN ) );
	memset( InstId, 0, sizeof( InstId ) );
	
	strcpy( Input_RecordId, I_RecordNo );
	
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
    	RTRIM(BIN),
    	RTRIM(INSTID),
		BINRANGEREQ,
		PRIORITY
	INTO
		:RecordId,
		:BIN,
		:InstId,
		:BINRangeReq,
		:Priority
	FROM EZBINSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(BIN) ,RTRIM(INSTID) ,BINRANGER\
EQ ,PRIORITY into :b0,:b1,:b2,:b3,:b4  from EZBINSELECT where RTRIM(RECORDID)=\
:b5";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )146;
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
 sqlstm.sqhstv[1] = (         void  *)BIN;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)InstId;
 sqlstm.sqhstl[2] = (unsigned int  )13;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&BINRangeReq;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&Priority;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[5] = (unsigned int  )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
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

	strcpy( binselect_ptr->RecordId, RecordId );
	strcpy( binselect_ptr->BIN, BIN );
	strcpy( binselect_ptr->InstId, InstId );
	binselect_ptr->BINRangeReq = BINRangeReq;
	binselect_ptr->Priority = Priority;
	
	return sqlca.sqlcode;
}


int readEzNetworkSelect( const char *I_RecordNo, struct EzNetworkSelectMemory *networkselect_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char InstId[ 13 ];
		int Priority;
		char NetworkType[ 11 ];
		char FieldType[ 65 ];
		char FromOffset[ 33 ];
		char ToOffset[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR NetworkType IS STRING(11); */ 

	/* EXEC SQL VAR FieldType IS STRING(65); */ 

	/* EXEC SQL VAR FromOffset IS STRING(33); */ 

	/* EXEC SQL VAR ToOffset IS STRING(33); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( NetworkType, 0, sizeof( NetworkType ) );
	memset( FieldType, 0, sizeof( FieldType ) );
	memset( FromOffset, 0, sizeof( FromOffset ) );
	memset( ToOffset, 0, sizeof( ToOffset ) );

	strcpy( Input_RecordId, I_RecordNo );

	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(INSTID),
		PRIORITY,
		RTRIM(NETWORKTYPE),
		RTRIM(FIELDTYPE),
		RTRIM(FROMOFFSET),
		RTRIM(TOOFFSET)
	INTO
		:RecordId,
		:InstId,
		:Priority,
		:NetworkType,
		:FieldType,
		:FromOffset,
		:ToOffset
	FROM EZNETWORKSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(INSTID) ,PRIORITY ,RTRIM(NETWO\
RKTYPE) ,RTRIM(FIELDTYPE) ,RTRIM(FROMOFFSET) ,RTRIM(TOOFFSET) into :b0,:b1,:b2\
,:b3,:b4,:b5,:b6  from EZNETWORKSELECT where RTRIM(RECORDID)=:b7";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )185;
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
 sqlstm.sqhstv[2] = (         void  *)&Priority;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)NetworkType;
 sqlstm.sqhstl[3] = (unsigned int  )11;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)FieldType;
 sqlstm.sqhstl[4] = (unsigned int  )65;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)FromOffset;
 sqlstm.sqhstl[5] = (unsigned int  )33;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)ToOffset;
 sqlstm.sqhstl[6] = (unsigned int  )33;
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
	
	strcpy( networkselect_ptr->RecordId, RecordId );
	strcpy( networkselect_ptr->InstId, InstId );
	networkselect_ptr->Priority = Priority;
	strcpy( networkselect_ptr->NetworkType, NetworkType );
	strcpy( networkselect_ptr->FieldType, FieldType );
	strcpy( networkselect_ptr->FromOffset, FromOffset );
	strcpy( networkselect_ptr->ToOffset, ToOffset );
	return sqlca.sqlcode;
}

int readEzBINProfile( const char *I_InstId, const char *I_BIN, struct EzBINProfileMemory *binprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ];
		char BIN[ 13 ];
		char Input_BIN[ 13 ];
		char TxnList[ 65 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR BIN IS STRING(13); */ 

	/* EXEC SQL VAR Input_BIN IS STRING(13); */ 

	/* EXEC SQL VAR TxnList IS STRING(65); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( BIN, 0, sizeof( BIN ) );
	memset( Input_BIN, 0, sizeof( Input_BIN ) );
	memset( TxnList, 0, sizeof( TxnList ) );
	
	strcpy( Input_InstId, I_InstId );
	strcpy( Input_BIN, I_BIN );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(BIN),
		RTRIM(TXNLIST)
	INTO
		:InstId,
		:BIN,
		:TxnList
	FROM EZBINPROFILE WHERE RTRIM(INSTID)=:Input_InstId AND RTRIM(BIN)=:Input_BIN; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(BIN) ,RTRIM(TXNLIST) into :b0,:b\
1,:b2  from EZBINPROFILE where (RTRIM(INSTID)=:b3 and RTRIM(BIN)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )232;
 sqlstm.selerr = (unsigned short)1;
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
 sqlstm.sqhstv[1] = (         void  *)BIN;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TxnList;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_InstId;
 sqlstm.sqhstl[3] = (unsigned int  )13;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_BIN;
 sqlstm.sqhstl[4] = (unsigned int  )13;
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
		
	strcpy( binprofile_ptr->InstId, InstId );
	strcpy( binprofile_ptr->BIN, BIN );
	strcpy( binprofile_ptr->TxnList, TxnList );
	return sqlca.sqlcode;
}

int readEzBranchProfile( const char *I_InstId, const char *I_BranchCode, struct EzBranchProfileMemory *branchprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ];
		char BranchCode[ 13 ];
		char Input_BranchCode[ 13 ];
		char BranchMapCode[ 13 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR BranchCode IS STRING(13); */ 

	/* EXEC SQL VAR Input_BranchCode IS STRING(13); */ 

	/* EXEC SQL VAR BranchMapCode IS STRING(13); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( BranchCode, 0, sizeof( BranchCode ) );
	memset( Input_BranchCode, 0, sizeof( Input_BranchCode ) );
	memset( BranchMapCode, 0, sizeof( BranchMapCode ) );
	
	strcpy( Input_InstId, I_InstId );
	strcpy( Input_BranchCode, I_BranchCode );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(BRANCHCODE),
		RTRIM(BRANCHMAPCODE)
	INTO
		:InstId,
		:BranchCode,
		:BranchMapCode
	FROM EZBRANCHPROFILE WHERE RTRIM(INSTID)=:Input_InstId AND RTRIM(BRANCHCODE)=:Input_BranchCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(BRANCHCODE) ,RTRIM(BRANCHMAPCODE\
) into :b0,:b1,:b2  from EZBRANCHPROFILE where (RTRIM(INSTID)=:b3 and RTRIM(BR\
ANCHCODE)=:b4)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )267;
 sqlstm.selerr = (unsigned short)1;
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
 sqlstm.sqhstv[1] = (         void  *)BranchCode;
 sqlstm.sqhstl[1] = (unsigned int  )13;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)BranchMapCode;
 sqlstm.sqhstl[2] = (unsigned int  )13;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Input_InstId;
 sqlstm.sqhstl[3] = (unsigned int  )13;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_BranchCode;
 sqlstm.sqhstl[4] = (unsigned int  )13;
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
	
	strcpy( branchprofile_ptr->InstId, InstId );
	strcpy( branchprofile_ptr->BranchCode, BranchCode );
	strcpy( branchprofile_ptr->BranchMapCode, BranchMapCode );
		
	return sqlca.sqlcode;
}

int readEzAuthProperty( const char *I_RecordNo, struct EzAuthPropertyMemory *ezauthproperty_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char AuthGroupId[ 17 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		char AuthList[ 256 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR AuthGroupId IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	/* EXEC SQL VAR AuthList IS STRING(256); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( AuthGroupId, 0, sizeof( AuthGroupId ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	memset( AuthList, 0, sizeof( AuthList ) );
	
	strcpy( Input_RecordId, I_RecordNo );
		
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
        RTRIM(AUTHGROUPID),
        RTRIM(MSGTYPE),
        RTRIM(TXNCODE),
        RTRIM(RESPCODE),
        RTRIM(AUTHLIST)
	INTO
		:RecordId,
		:AuthGroupId,
		:MsgType,
		:TxnCode,
		:RespCode,
		:AuthList
	FROM EZAUTHPROPERTY WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(AUTHGROUPID) ,RTRIM(MSGTYPE) ,\
RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,RTRIM(AUTHLIST) into :b0,:b1,:b2,:b3,:b4,:b5 \
 from EZAUTHPROPERTY where RTRIM(RECORDID)=:b6";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )302;
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
 sqlstm.sqhstv[1] = (         void  *)AuthGroupId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MsgType;
 sqlstm.sqhstl[2] = (unsigned int  )5;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TxnCode;
 sqlstm.sqhstl[3] = (unsigned int  )7;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)RespCode;
 sqlstm.sqhstl[4] = (unsigned int  )4;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)AuthList;
 sqlstm.sqhstl[5] = (unsigned int  )256;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[6] = (unsigned int  )17;
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
	
	strcpy( ezauthproperty_ptr->RecordId, RecordId );
	strcpy( ezauthproperty_ptr->AuthGroupId, AuthGroupId );
	strcpy( ezauthproperty_ptr->MsgType, MsgType );
	strcpy( ezauthproperty_ptr->TxnCode, TxnCode );
	strcpy( ezauthproperty_ptr->RespCode, RespCode );
	strcpy( ezauthproperty_ptr->AuthList, AuthList );
		
	return sqlca.sqlcode;
}

int readEzChannelProperty( const char *I_ChannelName, struct EzChannelPropertyMemory *ezchannelproperty_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char ChannelName[ 33 ];
		char Input_ChannelName[ 33 ];
		char ChannelType[ 11 ];
		char DeviceType[ 17 ];
		char LayerId[ 11 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR Input_ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR ChannelType IS STRING(11); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR LayerId IS STRING(11); */ 


	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( Input_ChannelName, 0, sizeof( Input_ChannelName ) );
	memset( ChannelType, 0, sizeof( ChannelType ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( LayerId, 0, sizeof( LayerId ) );
	
	strcpy( Input_ChannelName, I_ChannelName );
	
	/* EXEC SQL SELECT
		RTRIM(CHANNELNAME),
		RTRIM(CHANNELTYPE),
		RTRIM(DEVICETYPE),
		RTRIM(LAYERID)
	INTO
		:ChannelName,
		:ChannelType,
		:DeviceType,
		:LayerId
	FROM EZCHANNELPROPERTY WHERE RTRIM(CHANNELNAME)=:Input_ChannelName; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(CHANNELNAME) ,RTRIM(CHANNELTYPE) ,RTRIM(DEVICET\
YPE) ,RTRIM(LAYERID) into :b0,:b1,:b2,:b3  from EZCHANNELPROPERTY where RTRIM(\
CHANNELNAME)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )345;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)ChannelName;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)ChannelType;
 sqlstm.sqhstl[1] = (unsigned int  )11;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)DeviceType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)LayerId;
 sqlstm.sqhstl[3] = (unsigned int  )11;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_ChannelName;
 sqlstm.sqhstl[4] = (unsigned int  )33;
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
		
	strcpy( ezchannelproperty_ptr->ChannelName, ChannelName );
	strcpy( ezchannelproperty_ptr->ChannelType, ChannelType );
	strcpy( ezchannelproperty_ptr->DeviceType, DeviceType );
	strcpy( ezchannelproperty_ptr->LayerId, LayerId );

	return sqlca.sqlcode;
}

int readEzMsgTypePropertyTable( int I_MsgType, struct EzMsgTypePropertyMemory *ezmsgtypeproperty_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int MsgType;
		int Input_MsgType;
		char MsgProperty;
		char LookUpProperty;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	
	Input_MsgType = I_MsgType;
	
	/* EXEC SQL SELECT
		MSGTYPE,
        MSGPROPERTY,
        LOOKUPPROPERTY
	INTO
		:MsgType,
		:MsgProperty,
		:LookUpProperty
	FROM EZMSGTYPEPROPERTY WHERE RTRIM(MSGTYPE)=:Input_MsgType; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select MSGTYPE ,MSGPROPERTY ,LOOKUPPROPERTY into :b0,:b1,:b2\
  from EZMSGTYPEPROPERTY where RTRIM(MSGTYPE)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )380;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&MsgType;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&MsgProperty;
 sqlstm.sqhstl[1] = (unsigned int  )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&LookUpProperty;
 sqlstm.sqhstl[2] = (unsigned int  )1;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&Input_MsgType;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
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
		
	ezmsgtypeproperty_ptr->MsgType = MsgType;
	ezmsgtypeproperty_ptr->MsgProperty = MsgProperty;
	ezmsgtypeproperty_ptr->LookUpProperty = LookUpProperty;

	return sqlca.sqlcode;
}

int readEzEventProperty( const char *I_RecordId, struct EzEventPropertyMemory *ezeventproperty_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char ChannelName[ 33 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		char EventFlag;
		int EventTimeOut;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );

	strcpy( Input_RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RECORDNO,
		RTRIM(RECORDID),
		RTRIM(CHANNELNAME),
		RTRIM(MSGTYPE),
		RTRIM(TXNCODE),
		RTRIM(RESPCODE),
        EVENTFLAG,
        EVENTTIMEOUT
	INTO
		:RecordNo,
		:RecordId,
		:ChannelName,
		:MsgType,
		:TxnCode,
		:RespCode,
		:EventFlag,
		:EventTimeOut
	FROM EZEVENTPROPERTY WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RECORDNO ,RTRIM(RECORDID) ,RTRIM(CHANNELNAME) ,RTRIM(\
MSGTYPE) ,RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,EVENTFLAG ,EVENTTIMEOUT into :b0,:b\
1,:b2,:b3,:b4,:b5,:b6,:b7  from EZEVENTPROPERTY where RTRIM(RECORDID)=:b8";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )411;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&RecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)RecordId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)ChannelName;
 sqlstm.sqhstl[2] = (unsigned int  )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MsgType;
 sqlstm.sqhstl[3] = (unsigned int  )5;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TxnCode;
 sqlstm.sqhstl[4] = (unsigned int  )7;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)RespCode;
 sqlstm.sqhstl[5] = (unsigned int  )4;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&EventFlag;
 sqlstm.sqhstl[6] = (unsigned int  )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&EventTimeOut;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[8] = (unsigned int  )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
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
	
	ezeventproperty_ptr->RecordNo = RecordNo;
	strcpy( ezeventproperty_ptr->RecordId, RecordId );
	strcpy( ezeventproperty_ptr->ChannelName, ChannelName );
	strcpy( ezeventproperty_ptr->MsgType, MsgType );
	strcpy( ezeventproperty_ptr->TxnCode, TxnCode );
	strcpy( ezeventproperty_ptr->RespCode, RespCode );
	ezeventproperty_ptr->EventFlag = EventFlag;
	ezeventproperty_ptr->EventTimeOut = EventTimeOut;
	
	return sqlca.sqlcode;
}


int readEzMsgTranslate( const char *I_MsgTranslateId, struct EzMsgTranslateMemory *ezmsgtranslate_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MsgTranslateId[ 17 ];
		char Input_MsgTranslateId[ 17 ];
		char TranslateDesc[ 256 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MsgTranslateId IS STRING(17); */ 

	/* EXEC SQL VAR Input_MsgTranslateId IS STRING(17); */ 

	/* EXEC SQL VAR TranslateDesc IS STRING(256); */ 

	
	memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );
	memset( Input_MsgTranslateId, 0, sizeof( Input_MsgTranslateId ) );
	memset( TranslateDesc, 0, sizeof( TranslateDesc ) );
	
	strcpy( Input_MsgTranslateId, I_MsgTranslateId );
	
	/* EXEC SQL SELECT
		RTRIM(MSGTRANSLATEID),
		RTRIM(TRANSLATEDESC)
	INTO
		:MsgTranslateId,
		:TranslateDesc
	FROM EZMSGTRANSLATE WHERE RTRIM(MSGTRANSLATEID)=:Input_MsgTranslateId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(MSGTRANSLATEID) ,RTRIM(TRANSLATEDESC) into :b0,\
:b1  from EZMSGTRANSLATE where RTRIM(MSGTRANSLATEID)=:b2";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )462;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)MsgTranslateId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TranslateDesc;
 sqlstm.sqhstl[1] = (unsigned int  )256;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)Input_MsgTranslateId;
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


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	strcpy( ezmsgtranslate_ptr->MsgTranslateId, MsgTranslateId );
	strcpy( ezmsgtranslate_ptr->TranslateDesc, TranslateDesc );
	
	return sqlca.sqlcode;
}

int readEzTxnRefSelect( const char *I_RecordId, struct EzTxnRefSelectMemory *eztxnrefselect_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char DeviceType[ 17 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		char KeyFields[ 151 ]; 
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	/* EXEC SQL VAR KeyFields IS STRING(151); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	memset( KeyFields, 0, sizeof( KeyFields ) );
		
	strcpy( Input_RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RECORDNO,
		RTRIM(RECORDID),
		RTRIM(DEVICETYPE),
		RTRIM(MSGTYPE),
        RTRIM(TXNCODE),
        RTRIM(RESPCODE),
        RTRIM(KEYFIELDS)
	INTO
		:RecordNo,
		:RecordId,
		:DeviceType,
		:MsgType,
		:TxnCode,
		:RespCode,
		:KeyFields
	FROM EZTXNREFSELECT WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RECORDNO ,RTRIM(RECORDID) ,RTRIM(DEVICETYPE) ,RTRIM(M\
SGTYPE) ,RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,RTRIM(KEYFIELDS) into :b0,:b1,:b2,:b\
3,:b4,:b5,:b6  from EZTXNREFSELECT where RTRIM(RECORDID)=:b7";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )489;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&RecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)RecordId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)DeviceType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MsgType;
 sqlstm.sqhstl[3] = (unsigned int  )5;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TxnCode;
 sqlstm.sqhstl[4] = (unsigned int  )7;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)RespCode;
 sqlstm.sqhstl[5] = (unsigned int  )4;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)KeyFields;
 sqlstm.sqhstl[6] = (unsigned int  )151;
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
	
	eztxnrefselect_ptr->RecordNo = RecordNo;
	strcpy( eztxnrefselect_ptr->RecordId, RecordId );
	strcpy( eztxnrefselect_ptr->DeviceType, DeviceType );
	strcpy( eztxnrefselect_ptr->MsgType, MsgType );
	strcpy( eztxnrefselect_ptr->TxnCode, TxnCode );
	strcpy( eztxnrefselect_ptr->RespCode, RespCode );
	strcpy( eztxnrefselect_ptr->KeyFields, KeyFields );
		
	return sqlca.sqlcode;
}

int readEzTxnRouteInfo( const char *I_RecordId, struct EzTxnRouteInfoMemory *eztxnrouteinfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 129 ];
		char Input_RecordId[ 129 ];
		char IssuerInstRouteType[ 17 ];
		char AcquirerInstRouteType[ 17 ];
		char TxfInstRouteType[ 17 ];
		char SettInstRouteType[ 17 ];
		char FwdInstRouteType[ 17 ];
		char DeviceType[ 65 ];
		char DeviceSubType[ 65 ];
		char MsgType[ 65 ];
		char TxnCode[ 129 ];
		char RespCode[ 65 ];
		char RouteExp1[ 129 ];
		int RouteExpPriority1;
		char RouteExp2[ 129 ];
		int RouteExpPriority2;		
		char ChannelName[ 65 ];
		char NetworkTypeList[ 65 ];
		char NetworkStatusList[ 65 ];
		int NetworkListPriority;
		char RouteCondition[ 129 ];
		int RouteConditionPriority;
		char RouteSelectList[ 129 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(129); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(129); */ 

	/* EXEC SQL VAR IssuerInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR AcquirerInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR TxfInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR SettInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR FwdInstRouteType IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(65); */ 

	/* EXEC SQL VAR DeviceSubType IS STRING(65); */ 

	/* EXEC SQL VAR MsgType IS STRING(65); */ 

	/* EXEC SQL VAR TxnCode IS STRING(129); */ 

	/* EXEC SQL VAR RespCode IS STRING(65); */ 

	/* EXEC SQL VAR RouteExp1 IS STRING(129); */ 

	/* EXEC SQL VAR RouteExp2 IS STRING(129); */ 

	/* EXEC SQL VAR ChannelName IS STRING(65); */ 

	/* EXEC SQL VAR NetworkTypeList IS STRING(65); */ 

	/* EXEC SQL VAR NetworkStatusList IS STRING(65); */ 

	/* EXEC SQL VAR RouteCondition IS STRING(129); */ 

	/* EXEC SQL VAR RouteSelectList IS STRING(129); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( IssuerInstRouteType, 0, sizeof( IssuerInstRouteType ) );
	memset( AcquirerInstRouteType, 0, sizeof( AcquirerInstRouteType ) );
	memset( TxfInstRouteType, 0, sizeof( TxfInstRouteType ) );
	memset( SettInstRouteType, 0, sizeof( SettInstRouteType ) );
	memset( FwdInstRouteType, 0, sizeof( FwdInstRouteType ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( DeviceSubType, 0, sizeof( DeviceSubType ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	memset( RouteExp1, 0, sizeof( RouteExp1 ) );
	memset( RouteExp2, 0, sizeof( RouteExp2 ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( NetworkTypeList, 0, sizeof( NetworkTypeList ) );
	memset( NetworkStatusList, 0, sizeof( NetworkStatusList ) );
	memset( RouteCondition, 0, sizeof( RouteCondition ) );
	memset( RouteSelectList, 0, sizeof( RouteSelectList ) );
		
	strcpy( Input_RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RECORDNO,
		RTRIM(RECORDID),
	 	RTRIM(ISSUERINSTROUTETYPE),	
	 	RTRIM(ACQUIRERINSTROUTETYPE),
	 	RTRIM(TXFINSTROUTETYPE),
	 	RTRIM(SETTINSTROUTETYPE),
	 	RTRIM(FWDINSTROUTETYPE),
	 	RTRIM(DEVICETYPE),
	 	RTRIM(DEVICESUBTYPE),
	 	RTRIM(MSGTYPE),
	 	RTRIM(TXNCODE),
	 	RTRIM(RESPCODE),
	 	RTRIM(ROUTEEXP1),
	 	ROUTEEXPPRIORITY1,
	 	RTRIM(ROUTEEXP2),
	 	ROUTEEXPPRIORITY2,
	 	RTRIM(CHANNELNAME),
	 	RTRIM(NETWORKTYPELIST),
	 	RTRIM(NETWORKSTATUSLIST),
	 	NETWORKLISTPRIORITY,
	 	RTRIM(ROUTECONDITION),
	 	ROUTECONDITIONPRIORITY,
	 	RTRIM(ROUTESELECTLIST)
	INTO
		:RecordNo,
		:RecordId,
		:IssuerInstRouteType,
		:AcquirerInstRouteType,
		:TxfInstRouteType,
		:SettInstRouteType,
		:FwdInstRouteType,
		:DeviceType,
		:DeviceSubType,
		:MsgType,
		:TxnCode,
		:RespCode,
		:RouteExp1,
		:RouteExpPriority1,
		:RouteExp2,
		:RouteExpPriority2,
		:ChannelName,
		:NetworkTypeList,
		:NetworkStatusList,
		:NetworkListPriority,
		:RouteCondition,
		:RouteConditionPriority,
		:RouteSelectList
	FROM EZTXNROUTEINFO WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RECORDNO ,RTRIM(RECORDID) ,RTRIM(ISSUERINSTROUTETYPE)\
 ,RTRIM(ACQUIRERINSTROUTETYPE) ,RTRIM(TXFINSTROUTETYPE) ,RTRIM(SETTINSTROUTETY\
PE) ,RTRIM(FWDINSTROUTETYPE) ,RTRIM(DEVICETYPE) ,RTRIM(DEVICESUBTYPE) ,RTRIM(M\
SGTYPE) ,RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,RTRIM(ROUTEEXP1) ,ROUTEEXPPRIORITY1 \
,RTRIM(ROUTEEXP2) ,ROUTEEXPPRIORITY2 ,RTRIM(CHANNELNAME) ,RTRIM(NETWORKTYPELIS\
T) ,RTRIM(NETWORKSTATUSLIST) ,NETWORKLISTPRIORITY ,RTRIM(ROUTECONDITION) ,ROUT\
ECONDITIONPRIORITY ,RTRIM(ROUTESELECTLIST) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b\
7,:b8,:b9,:b10,:b11,:b12,:b13,:b14,:b15,:b16,:b17,:b18,:b19,:b20,:b21,:b22  fr\
om EZTXNROUTEINFO where RTRIM(RECORDID)=:b23";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )536;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&RecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)RecordId;
 sqlstm.sqhstl[1] = (unsigned int  )129;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)IssuerInstRouteType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)AcquirerInstRouteType;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TxfInstRouteType;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)SettInstRouteType;
 sqlstm.sqhstl[5] = (unsigned int  )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)FwdInstRouteType;
 sqlstm.sqhstl[6] = (unsigned int  )17;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)DeviceType;
 sqlstm.sqhstl[7] = (unsigned int  )65;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)DeviceSubType;
 sqlstm.sqhstl[8] = (unsigned int  )65;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)MsgType;
 sqlstm.sqhstl[9] = (unsigned int  )65;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)TxnCode;
 sqlstm.sqhstl[10] = (unsigned int  )129;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)RespCode;
 sqlstm.sqhstl[11] = (unsigned int  )65;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)RouteExp1;
 sqlstm.sqhstl[12] = (unsigned int  )129;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&RouteExpPriority1;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)RouteExp2;
 sqlstm.sqhstl[14] = (unsigned int  )129;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&RouteExpPriority2;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)ChannelName;
 sqlstm.sqhstl[16] = (unsigned int  )65;
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)NetworkTypeList;
 sqlstm.sqhstl[17] = (unsigned int  )65;
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)NetworkStatusList;
 sqlstm.sqhstl[18] = (unsigned int  )65;
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&NetworkListPriority;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)RouteCondition;
 sqlstm.sqhstl[20] = (unsigned int  )129;
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&RouteConditionPriority;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)RouteSelectList;
 sqlstm.sqhstl[22] = (unsigned int  )129;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[23] = (unsigned int  )129;
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
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


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	eztxnrouteinfo_ptr->RecordNo = RecordNo;
	strcpy( eztxnrouteinfo_ptr->RecordId, RecordId );
    strcpy( eztxnrouteinfo_ptr->IssuerInstRouteType, IssuerInstRouteType );
    strcpy( eztxnrouteinfo_ptr->AcquirerInstRouteType, AcquirerInstRouteType );
    strcpy( eztxnrouteinfo_ptr->TxfInstRouteType, TxfInstRouteType );
    strcpy( eztxnrouteinfo_ptr->SettInstRouteType, SettInstRouteType );
    strcpy( eztxnrouteinfo_ptr->FwdInstRouteType, FwdInstRouteType );
    strcpy( eztxnrouteinfo_ptr->DeviceType, DeviceType );
    strcpy( eztxnrouteinfo_ptr->DeviceSubType, DeviceSubType );
    strcpy( eztxnrouteinfo_ptr->MsgType, MsgType );
    strcpy( eztxnrouteinfo_ptr->TxnCode, TxnCode );
    strcpy( eztxnrouteinfo_ptr->RespCode, RespCode );
    strcpy( eztxnrouteinfo_ptr->RouteExp1, RouteExp1 );
    strcpy( eztxnrouteinfo_ptr->RouteExp2, RouteExp2 );
    eztxnrouteinfo_ptr->RouteExpPriority1 = RouteExpPriority1;
    eztxnrouteinfo_ptr->RouteExpPriority2 = RouteExpPriority2;
    strcpy( eztxnrouteinfo_ptr->ChannelName, ChannelName );
    strcpy( eztxnrouteinfo_ptr->NetworkTypeList, NetworkTypeList );
    strcpy( eztxnrouteinfo_ptr->NetworkStatusList, NetworkStatusList );
    eztxnrouteinfo_ptr->NetworkListPriority = NetworkListPriority;
    strcpy( eztxnrouteinfo_ptr->RouteCondition, RouteCondition );
    eztxnrouteinfo_ptr->RouteConditionPriority = RouteConditionPriority;
    strcpy( eztxnrouteinfo_ptr->RouteSelectList, RouteSelectList );
	
	return sqlca.sqlcode;
}

int readEzTxnRouteSelect( const char *I_RouteSelectId, struct EzTxnRouteSelectMemory *eztxnrouteinfo_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RouteSelectId[ 17 ];
		char Input_RouteSelectId[ 17 ];
		char ChannelName[ 33 ];
		char MsgTranslateId[ 17 ];
		char LogFlag;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RouteSelectId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RouteSelectId IS STRING(17); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	/* EXEC SQL VAR MsgTranslateId IS STRING(17); */ 

	
	memset( RouteSelectId, 0, sizeof( RouteSelectId ) );
	memset( Input_RouteSelectId, 0, sizeof( Input_RouteSelectId ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	memset( MsgTranslateId, 0, sizeof( MsgTranslateId ) );	
	
	strcpy( Input_RouteSelectId, I_RouteSelectId );
	
	/* EXEC SQL SELECT
		RTRIM(ROUTESELECTID),
        RTRIM(CHANNELNAME),
        RTRIM(MSGTRANSLATEID),
        LOGFLAG
	INTO
		:RouteSelectId,
		:ChannelName,
		:MsgTranslateId,
		:LogFlag
	FROM EZTXNROUTESELECT WHERE RTRIM(ROUTESELECTID)=:Input_RouteSelectId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(ROUTESELECTID) ,RTRIM(CHANNELNAME) ,RTRIM(MSGTR\
ANSLATEID) ,LOGFLAG into :b0,:b1,:b2,:b3  from EZTXNROUTESELECT where RTRIM(RO\
UTESELECTID)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )647;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)RouteSelectId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)ChannelName;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MsgTranslateId;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&LogFlag;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_RouteSelectId;
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
	
	strcpy( eztxnrouteinfo_ptr->RouteSelectId, RouteSelectId );
	strcpy( eztxnrouteinfo_ptr->ChannelName, ChannelName );
	strcpy( eztxnrouteinfo_ptr->MsgTranslateId, MsgTranslateId );
	eztxnrouteinfo_ptr->LogFlag = LogFlag;
	
	return sqlca.sqlcode;
}

int readEzInBoundMsgProperty( const char *I_RecordId, struct EzInBoundMsgPropertyMemory *ezinboundmsgproperty_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int RecordNo;
		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char MsgType[ 5 ];
		char ChannelType[ 11 ];
		char ChannelName[ 33 ];
		char MsgFlag;
		char LogFlag;
		char MsgProcessFlag;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR ChannelType IS STRING(11); */ 

	/* EXEC SQL VAR ChannelName IS STRING(33); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( ChannelType, 0, sizeof( ChannelType ) );
	memset( ChannelName, 0, sizeof( ChannelName ) );
	
	strcpy(Input_RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RECORDNO,
		RTRIM(RECORDID),
		RTRIM(MSGTYPE),
		RTRIM(CHANNELTYPE),
        RTRIM(CHANNELNAME),
        MSGFLAG,
        LOGFLAG,
        MSGPROCESSFLAG
	INTO
		:RecordNo,
		:RecordId,
		:MsgType,
		:ChannelType,
		:ChannelName,
		:MsgFlag,
		:LogFlag,
		:MsgProcessFlag
	FROM EZINBOUNDMSGPROPERTY WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RECORDNO ,RTRIM(RECORDID) ,RTRIM(MSGTYPE) ,RTRIM(CHAN\
NELTYPE) ,RTRIM(CHANNELNAME) ,MSGFLAG ,LOGFLAG ,MSGPROCESSFLAG into :b0,:b1,:b\
2,:b3,:b4,:b5,:b6,:b7  from EZINBOUNDMSGPROPERTY where RTRIM(RECORDID)=:b8";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )682;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&RecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)RecordId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MsgType;
 sqlstm.sqhstl[2] = (unsigned int  )5;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)ChannelType;
 sqlstm.sqhstl[3] = (unsigned int  )11;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)ChannelName;
 sqlstm.sqhstl[4] = (unsigned int  )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&MsgFlag;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&LogFlag;
 sqlstm.sqhstl[6] = (unsigned int  )1;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&MsgProcessFlag;
 sqlstm.sqhstl[7] = (unsigned int  )1;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[8] = (unsigned int  )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
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
		
	ezinboundmsgproperty_ptr->RecordNo = RecordNo;
	strcpy( ezinboundmsgproperty_ptr->RecordId, RecordId );
	strcpy( ezinboundmsgproperty_ptr->MsgType, MsgType );
	strcpy( ezinboundmsgproperty_ptr->ChannelType, ChannelType );
	strcpy( ezinboundmsgproperty_ptr->ChannelName, ChannelName );
	ezinboundmsgproperty_ptr->MsgFlag = MsgFlag;
	ezinboundmsgproperty_ptr->LogFlag = LogFlag;
	ezinboundmsgproperty_ptr->MsgProcessFlag = MsgProcessFlag;
	return sqlca.sqlcode;
}

int readEzDeviceTypeMap( const char *I_DeviceGroupId, struct EzDeviceTypeMapMemory *ezdevicetypemap_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char DeviceGroupId[ 17 ];
		char Input_DeviceGroupId[ 17 ];
		int DeviceGroupVal;
    /* EXEC SQL END DECLARE SECTION; */ 

    
    /* EXEC SQL VAR DeviceGroupId IS STRING(17); */ 

    /* EXEC SQL VAR Input_DeviceGroupId IS STRING(17); */ 

    
    memset( DeviceGroupId, 0, sizeof( DeviceGroupId ) );
    memset( Input_DeviceGroupId, 0, sizeof( Input_DeviceGroupId ) );
    
    strcpy( Input_DeviceGroupId, I_DeviceGroupId );
    
    /* EXEC SQL SELECT
		RTRIM(DEVICEGROUPID),
		DEVICEGROUPVAL
	INTO
		:DeviceGroupId,
		:DeviceGroupVal
	FROM EZDEVICETYPEMAP WHERE RTRIM(DEVICEGROUPID)=:Input_DeviceGroupId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 24;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(DEVICEGROUPID) ,DEVICEGROUPVAL into :b0,:b1 \
 from EZDEVICETYPEMAP where RTRIM(DEVICEGROUPID)=:b2";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )733;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (         void  *)DeviceGroupId;
    sqlstm.sqhstl[0] = (unsigned int  )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         void  *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned int  )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (         void  *)&DeviceGroupVal;
    sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         void  *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned int  )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (         void  *)Input_DeviceGroupId;
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


	
	if ( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
		
    strcpy( ezdevicetypemap_ptr->DeviceGroupId, DeviceGroupId );
    ezdevicetypemap_ptr->DeviceGroupVal = DeviceGroupVal;

	return sqlca.sqlcode;
}

int readEzTxnMsgOrder( const char *I_RecordId, struct EzTxnMsgOrderMemory *eztxnmsgorder_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char Input_RecordId[ 17 ];
		char SrcChannel[ 33 ];
		char DestChannel[ 33 ];
		char MsgType[ 5 ];
		char TxnCode[ 7 ];
		char RespCode[ 4 ];
		short OrderNo;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(17); */ 

	/* EXEC SQL VAR SrcChannel IS STRING(33); */ 

	/* EXEC SQL VAR DestChannel IS STRING(33); */ 

	/* EXEC SQL VAR MsgType IS STRING(5); */ 

	/* EXEC SQL VAR TxnCode IS STRING(7); */ 

	/* EXEC SQL VAR RespCode IS STRING(4); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( SrcChannel, 0, sizeof( SrcChannel ) );
	memset( DestChannel, 0, sizeof( DestChannel ) );
	memset( MsgType, 0, sizeof( MsgType ) );
	memset( TxnCode, 0, sizeof( TxnCode ) );
	memset( RespCode, 0, sizeof( RespCode ) );
	
	
	strcpy( Input_RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
		RTRIM(SRCCHANNEL),
		RTRIM(DESTCHANNEL),
		RTRIM(MSGTYPE),
		RTRIM(TXNCODE),
		RTRIM(RESPCODE),
       	ORDERNO
	INTO
		:RecordId,
		:SrcChannel,
		:DestChannel,
		:MsgType,
		:TxnCode,
		:RespCode,
		:OrderNo
	FROM EZTXNMSGORDER WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(SRCCHANNEL) ,RTRIM(DESTCHANNEL\
) ,RTRIM(MSGTYPE) ,RTRIM(TXNCODE) ,RTRIM(RESPCODE) ,ORDERNO into :b0,:b1,:b2,:\
b3,:b4,:b5,:b6  from EZTXNMSGORDER where RTRIM(RECORDID)=:b7";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )760;
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
 sqlstm.sqhstv[1] = (         void  *)SrcChannel;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)DestChannel;
 sqlstm.sqhstl[2] = (unsigned int  )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MsgType;
 sqlstm.sqhstl[3] = (unsigned int  )5;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TxnCode;
 sqlstm.sqhstl[4] = (unsigned int  )7;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)RespCode;
 sqlstm.sqhstl[5] = (unsigned int  )4;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&OrderNo;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(short);
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
	
	strcpy( eztxnmsgorder_ptr->RecordId, RecordId );
	strcpy( eztxnmsgorder_ptr->SrcChannel, SrcChannel );
	strcpy( eztxnmsgorder_ptr->DestChannel, DestChannel );
	strcpy( eztxnmsgorder_ptr->MsgType, MsgType );
	strcpy( eztxnmsgorder_ptr->TxnCode, TxnCode );
	strcpy( eztxnmsgorder_ptr->RespCode, RespCode );
	eztxnmsgorder_ptr->OrderNo = OrderNo;
	
	return sqlca.sqlcode;
}

int readEzInstExtNtwkProfile( const char *I_InstId, const char *I_ExtNetworkId, struct EzInstExtNtwkProfileMemory *ezinstextntwkprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char InstId[ 13 ];
		char Input_InstId[ 13 ]; 
		char ExtNetworkId[ 17 ];
		char Input_ExtNetworkId[ 17 ];
		char AcqInstCode[ 17 ];
		char TxnCodeList[ 65 ];
		char AddFee1[ 129 ];
		char AddFee2[ 129 ];
		char AddFee3[ 129 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(13); */ 

	/* EXEC SQL VAR ExtNetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_ExtNetworkId IS STRING(17); */ 

	/* EXEC SQL VAR AcqInstCode IS STRING(17); */ 

	/* EXEC SQL VAR TxnCodeList IS STRING(65); */ 

	/* EXEC SQL VAR AddFee1 IS STRING(129); */ 

	/* EXEC SQL VAR AddFee2 IS STRING(129); */ 

	/* EXEC SQL VAR AddFee3 IS STRING(129); */ 

	
	memset( InstId, 0, sizeof( InstId ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
	memset( Input_ExtNetworkId, 0, sizeof( Input_ExtNetworkId ) );
	memset( AcqInstCode, 0, sizeof( AcqInstCode ) );
	memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
	memset( AddFee1, 0, sizeof( AddFee1 ) );
	memset( AddFee2, 0, sizeof( AddFee2 ) );
	memset( AddFee3, 0, sizeof( AddFee3 ) );
		
	strcpy( Input_InstId, I_InstId );
	strcpy( Input_ExtNetworkId, I_ExtNetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(EXTNETWORKID),
		RTRIM(ACQINSTCODE),
		RTRIM(TXNCODELIST),
		RTRIM(ADDFEE1),
		RTRIM(ADDFEE2),
        RTRIM(ADDFEE3)
    INTO
		:InstId,
		:ExtNetworkId,
		:AcqInstCode,
		:TxnCodeList,
		:AddFee1,
		:AddFee2,
		:AddFee3
	FROM EZINSTEXTNTWKPROFILE WHERE RTRIM(INSTID)=:Input_InstId AND RTRIM(EXTNETWORKID)=:Input_ExtNetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(EXTNETWORKID) ,RTRIM(ACQINSTCODE\
) ,RTRIM(TXNCODELIST) ,RTRIM(ADDFEE1) ,RTRIM(ADDFEE2) ,RTRIM(ADDFEE3) into :b0\
,:b1,:b2,:b3,:b4,:b5,:b6  from EZINSTEXTNTWKPROFILE where (RTRIM(INSTID)=:b7 a\
nd RTRIM(EXTNETWORKID)=:b8)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )807;
 sqlstm.selerr = (unsigned short)1;
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
 sqlstm.sqhstv[1] = (         void  *)ExtNetworkId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)AcqInstCode;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TxnCodeList;
 sqlstm.sqhstl[3] = (unsigned int  )65;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)AddFee1;
 sqlstm.sqhstl[4] = (unsigned int  )129;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)AddFee2;
 sqlstm.sqhstl[5] = (unsigned int  )129;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)AddFee3;
 sqlstm.sqhstl[6] = (unsigned int  )129;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)Input_InstId;
 sqlstm.sqhstl[7] = (unsigned int  )13;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)Input_ExtNetworkId;
 sqlstm.sqhstl[8] = (unsigned int  )17;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
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
	
	strcpy( ezinstextntwkprofile_ptr->InstId, InstId );
	strcpy( ezinstextntwkprofile_ptr->ExtNetworkId, ExtNetworkId );
	strcpy( ezinstextntwkprofile_ptr->AcqInstCode, AcqInstCode );
	strcpy( ezinstextntwkprofile_ptr->TxnCodeList, TxnCodeList );
	strcpy( ezinstextntwkprofile_ptr->AddFee1, AddFee1 );
	strcpy( ezinstextntwkprofile_ptr->AddFee2, AddFee2 );
	strcpy( ezinstextntwkprofile_ptr->AddFee3, AddFee3 );
	
	return sqlca.sqlcode;
}

int readEzExtNtwkProfile( const char *I_ExtNetworkId, struct EzExtNtwkProfileMemory *ezextntwkprofile_ptr )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char ExtNetworkId[ 17 ];
		char Input_ExtNetworkId[ 17 ];
		char TxnCodeList[ 65 ];
		char TxnCountCheckReq[ 33 ];
		char TxnAmountCheckReq[ 33 ];
		char MaxAmountPerTxn[ 129 ];
		char MaxAmount[ 129 ];
		char MaxAmountInterval[ 129 ];
		char MaxAmountIntervalType[ 33 ];
		char MaxAmountAction[ 33 ];
		char MaxAmountFee[ 129 ];
		char MaxCount[ 129 ];
		char MaxCountInterval[ 129 ];
		char MaxCountIntervalType[ 33 ];
		char MaxCountAction[ 33 ];
		char MaxCountFee[ 129 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR ExtNetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_ExtNetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnCodeList IS STRING(65); */ 

	/* EXEC SQL VAR TxnCountCheckReq IS STRING(33); */ 

	/* EXEC SQL VAR TxnAmountCheckReq IS STRING(33); */ 

	/* EXEC SQL VAR MaxAmountPerTxn IS STRING(129); */ 

	/* EXEC SQL VAR MaxAmount IS STRING(129); */ 

	/* EXEC SQL VAR MaxAmountInterval IS STRING(129); */ 

	/* EXEC SQL VAR MaxAmountIntervalType IS STRING(33); */ 

	/* EXEC SQL VAR MaxAmountAction IS STRING(33); */ 

	/* EXEC SQL VAR MaxAmountFee IS STRING(129); */ 

	/* EXEC SQL VAR MaxCount IS STRING(129); */ 

	/* EXEC SQL VAR MaxCountInterval IS STRING(129); */ 

	/* EXEC SQL VAR MaxCountIntervalType IS STRING(33); */ 

	/* EXEC SQL VAR MaxCountAction IS STRING(33); */ 

	/* EXEC SQL VAR MaxCountFee IS STRING(129); */ 

	
	
	memset( ExtNetworkId, 0, sizeof( ExtNetworkId ) );
	memset( Input_ExtNetworkId, 0, sizeof( Input_ExtNetworkId ) );
	memset( TxnCodeList, 0, sizeof( TxnCodeList ) );
	memset( TxnCountCheckReq, 0, sizeof( TxnCountCheckReq ) ); 
	memset( TxnAmountCheckReq, 0, sizeof( TxnAmountCheckReq ) );
	memset( MaxAmountPerTxn, 0, sizeof( MaxAmountPerTxn ) );
	memset( MaxAmount, 0, sizeof( MaxAmount ) );
	memset( MaxAmountInterval, 0, sizeof( MaxAmountInterval ) ); 
	memset( MaxAmountIntervalType, 0, sizeof( MaxAmountIntervalType ) ); 
	memset( MaxAmountAction, 0, sizeof( MaxAmountAction ) );
	memset( MaxAmountFee, 0, sizeof( MaxAmountFee ) );
	memset( MaxCount, 0, sizeof( MaxCount ) );
	memset( MaxCountInterval, 0, sizeof( MaxCountInterval ) ); 
	memset( MaxCountIntervalType, 0, sizeof( MaxCountIntervalType ) ); 
	memset( MaxCountAction, 0, sizeof( MaxCountAction ) );
	memset( MaxCountFee, 0, sizeof( MaxCountFee ) );
	
	strcpy( Input_ExtNetworkId, I_ExtNetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(EXTNETWORKID),
		RTRIM(TXNCODELIST),
		RTRIM(TXNCOUNTCHECKREQ),
		RTRIM(TXNAMOUNTCHECKREQ),
        RTRIM(MAXAMOUNTPERTXN),
        RTRIM(MAXAMOUNT),
        RTRIM(MAXAMOUNTINTERVAL),
        RTRIM(MAXAMOUNTINTERVALTYPE),
        RTRIM(MAXAMOUNTACTION),
        RTRIM(MAXAMOUNTFEE),
        RTRIM(MAXCOUNT),
        RTRIM(MAXCOUNTINTERVAL),
        RTRIM(MAXCOUNTINTERVALTYPE),
        RTRIM(MAXCOUNTACTION),
        RTRIM(MAXCOUNTFEE)
    INTO
		:ExtNetworkId,
		:TxnCodeList,
		:TxnCountCheckReq,
		:TxnAmountCheckReq,
		:MaxAmountPerTxn,
		:MaxAmount,
		:MaxAmountInterval,
		:MaxAmountIntervalType,
		:MaxAmountAction,
		:MaxAmountFee,
		:MaxCount,
		:MaxCountInterval,
		:MaxCountIntervalType,
		:MaxCountAction,
		:MaxCountFee
	FROM EZEXTNTWKPROFILE WHERE RTRIM(EXTNETWORKID)=:Input_ExtNetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 24;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(EXTNETWORKID) ,RTRIM(TXNCODELIST) ,RTRIM(TXNCOU\
NTCHECKREQ) ,RTRIM(TXNAMOUNTCHECKREQ) ,RTRIM(MAXAMOUNTPERTXN) ,RTRIM(MAXAMOUNT\
) ,RTRIM(MAXAMOUNTINTERVAL) ,RTRIM(MAXAMOUNTINTERVALTYPE) ,RTRIM(MAXAMOUNTACTI\
ON) ,RTRIM(MAXAMOUNTFEE) ,RTRIM(MAXCOUNT) ,RTRIM(MAXCOUNTINTERVAL) ,RTRIM(MAXC\
OUNTINTERVALTYPE) ,RTRIM(MAXCOUNTACTION) ,RTRIM(MAXCOUNTFEE) into :b0,:b1,:b2,\
:b3,:b4,:b5,:b6,:b7,:b8,:b9,:b10,:b11,:b12,:b13,:b14  from EZEXTNTWKPROFILE wh\
ere RTRIM(EXTNETWORKID)=:b15";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )858;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)ExtNetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnCodeList;
 sqlstm.sqhstl[1] = (unsigned int  )65;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TxnCountCheckReq;
 sqlstm.sqhstl[2] = (unsigned int  )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TxnAmountCheckReq;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)MaxAmountPerTxn;
 sqlstm.sqhstl[4] = (unsigned int  )129;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)MaxAmount;
 sqlstm.sqhstl[5] = (unsigned int  )129;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)MaxAmountInterval;
 sqlstm.sqhstl[6] = (unsigned int  )129;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)MaxAmountIntervalType;
 sqlstm.sqhstl[7] = (unsigned int  )33;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)MaxAmountAction;
 sqlstm.sqhstl[8] = (unsigned int  )33;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)MaxAmountFee;
 sqlstm.sqhstl[9] = (unsigned int  )129;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)MaxCount;
 sqlstm.sqhstl[10] = (unsigned int  )129;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)MaxCountInterval;
 sqlstm.sqhstl[11] = (unsigned int  )129;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)MaxCountIntervalType;
 sqlstm.sqhstl[12] = (unsigned int  )33;
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)MaxCountAction;
 sqlstm.sqhstl[13] = (unsigned int  )33;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)MaxCountFee;
 sqlstm.sqhstl[14] = (unsigned int  )129;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)Input_ExtNetworkId;
 sqlstm.sqhstl[15] = (unsigned int  )17;
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
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
	
	strcpy( ezextntwkprofile_ptr->ExtNetworkId, ExtNetworkId );
	strcpy( ezextntwkprofile_ptr->TxnCodeList, TxnCodeList );
	strcpy( ezextntwkprofile_ptr->TxnCountCheckReq, TxnCountCheckReq );
	strcpy( ezextntwkprofile_ptr->TxnAmountCheckReq, TxnAmountCheckReq );
	strcpy( ezextntwkprofile_ptr->MaxAmountPerTxn, MaxAmountPerTxn );
	strcpy( ezextntwkprofile_ptr->MaxAmount, MaxAmount );
	strcpy( ezextntwkprofile_ptr->MaxAmountInterval, MaxAmountInterval );
	strcpy( ezextntwkprofile_ptr->MaxAmountIntervalType, MaxAmountIntervalType );
	strcpy( ezextntwkprofile_ptr->MaxAmountAction, MaxAmountAction );
	strcpy( ezextntwkprofile_ptr->MaxAmountFee, MaxAmountFee );
	strcpy( ezextntwkprofile_ptr->MaxCount, MaxCount );
	strcpy( ezextntwkprofile_ptr->MaxCountInterval, MaxCountInterval );
	strcpy( ezextntwkprofile_ptr->MaxCountIntervalType, MaxCountIntervalType );
	strcpy( ezextntwkprofile_ptr->MaxCountAction, MaxCountAction );
	strcpy( ezextntwkprofile_ptr->MaxCountFee, MaxCountFee );
		
	return sqlca.sqlcode;
}




