
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
           char  filnam[19];
};
static struct sqlcxp sqlfpn =
{
    18,
    "ezsecuritycmddb.pc"
};


static unsigned int sqlctx = 20015659;


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
            void  *sqhstv[12];
   unsigned int   sqhstl[12];
            int   sqhsts[12];
            void  *sqindv[12];
            int   sqinds[12];
   unsigned int   sqharm[12];
   unsigned int   *sqharc[12];
   unsigned short  sqadto[12];
   unsigned short  sqtdso[12];
} sqlstm = {12,12};

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
5,0,0,1,130,0,4,33,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,1,5,0,0,
40,0,0,2,147,0,4,78,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,1,5,0,0,
75,0,0,3,203,0,4,127,0,0,7,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,1,
0,0,1,5,0,0,
118,0,0,4,289,0,4,188,0,0,12,1,0,1,0,2,5,0,0,2,1,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,
1,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,3,0,0,1,5,0,0,
181,0,0,5,185,0,4,257,0,0,6,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,1,
5,0,0,
220,0,0,6,264,0,4,316,0,0,12,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,
3,0,0,2,5,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,1,5,0,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <ezbusiness/ezatmkey.h>
#include <ezdb/ezdevicekey.h>
#include <ezdb/eznetworkkey.h>
#include <ezdb/ezsecurity.h>
#include <ezdb/ezhsminfo.h>
#include <ezdb/ezsecurityproperty.h>

int readEzATMKeyTable( const char *I_ATMId, struct EzATMKey *atmkey_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char ATMId[ 33 ];
		char Input_ATMId[ 33 ];
		char ATMMasterKey[ 65 ];
		char ATMCommKey[ 65 ];
		int ATMKeyLen;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR ATMId IS STRING(33); */ 

	/* EXEC SQL VAR Input_ATMId IS STRING(33); */ 

	/* EXEC SQL VAR ATMMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR ATMCommKey IS STRING(65); */ 

	
	memset( ATMId, 0, sizeof( ATMId ) );
	memset( Input_ATMId, 0, sizeof( Input_ATMId ) );
	memset( ATMMasterKey, 0, sizeof( ATMMasterKey ) );
	memset( ATMCommKey, 0, sizeof( ATMCommKey ) );
	
	strcpy( Input_ATMId, I_ATMId );
	
	/* EXEC SQL SELECT
		RTRIM(ATMID),
		RTRIM(ATMMASTERKEY),
		RTRIM(ATMCOMMKEY),
		ATMKEYLEN
	INTO
		:ATMId,
		:ATMMasterKey,
		:ATMCommKey,
		:ATMKeyLen
	FROM EZATMINFO WHERE RTRIM(ATMID)=:Input_ATMId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(ATMID) ,RTRIM(ATMMASTERKEY) ,RTRIM(ATMCOMMKEY) \
,ATMKEYLEN into :b0,:b1,:b2,:b3  from EZATMINFO where RTRIM(ATMID)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)ATMId;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)ATMMasterKey;
 sqlstm.sqhstl[1] = (unsigned int  )65;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)ATMCommKey;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&ATMKeyLen;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_ATMId;
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

	strcpy( atmkey_rec->ATMId, ATMId );
	strcpy( atmkey_rec->ATMMasterKey, ATMMasterKey );
	strcpy( atmkey_rec->ATMCommKey, ATMCommKey );
	atmkey_rec->ATMKeyLen = ATMKeyLen; 
	
	return sqlca.sqlcode;
}

int readDeviceKeyTable( const char *I_DeviceId, struct DeviceKey *devicekey_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char DeviceId[ 33 ];
		char Input_DeviceId[ 33 ];
		char DeviceMasterKey[ 65 ];
		char DeviceCommKey[ 65 ];
		int DeviceKeyLen;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR DeviceId IS STRING(33); */ 

	/* EXEC SQL VAR Input_DeviceId IS STRING(33); */ 

	/* EXEC SQL VAR DeviceMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR DeviceCommKey IS STRING(65); */ 

	
	memset( DeviceId, 0, sizeof( DeviceId ) );
	memset( Input_DeviceId, 0, sizeof( Input_DeviceId ) );
	memset( DeviceMasterKey, 0, sizeof( DeviceMasterKey ) );
	memset( DeviceCommKey, 0, sizeof( DeviceCommKey ) );
	
	strcpy( Input_DeviceId, I_DeviceId );
	
	/* EXEC SQL SELECT
		RTRIM(DEVICEID),
		RTRIM(DEVICEMASTERKEY),
		RTRIM(DEVICECOMMKEY),
		DEVICEKEYLEN
	INTO
		:DeviceId,
		:DeviceMasterKey,
		:DeviceCommKey,
		:DeviceKeyLen
	FROM EZDEVICEKEY WHERE RTRIM(DEVICEID)=:Input_DeviceId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DEVICEID) ,RTRIM(DEVICEMASTERKEY) ,RTRIM(DEVICE\
COMMKEY) ,DEVICEKEYLEN into :b0,:b1,:b2,:b3  from EZDEVICEKEY where RTRIM(DEVI\
CEID)=:b4";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )40;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)DeviceId;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)DeviceMasterKey;
 sqlstm.sqhstl[1] = (unsigned int  )65;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)DeviceCommKey;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&DeviceKeyLen;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)Input_DeviceId;
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

	strcpy( devicekey_rec->DeviceId, DeviceId );
	strcpy( devicekey_rec->DeviceMasterKey, DeviceMasterKey );
	strcpy( devicekey_rec->DeviceCommKey, DeviceCommKey );
	devicekey_rec->DeviceKeyLen = DeviceKeyLen; 
	
	return sqlca.sqlcode;
}

int readEzNetworkKeyTable( const char *I_NetworkId, struct EzNetworkKey *ntwkkey_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char NetworkId[ 17 ];
		char Input_NetworkId[ 17 ];
		char NetworkMasterKey[ 65 ];
		char NetworkAcqCommKey[ 65 ];
		char NetworkIssCommKey[ 65 ];
		int NetworkKeyLen;
		char KeyProperty;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR NetworkMasterKey IS STRING(65); */ 

	/* EXEC SQL VAR NetworkAcqCommKey IS STRING(65); */ 

	/* EXEC SQL VAR NetworkIssCommKey IS STRING(65); */ 

	
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
	memset( NetworkMasterKey, 0, sizeof( NetworkMasterKey ) );
	memset( NetworkAcqCommKey, 0, sizeof( NetworkAcqCommKey ) );
	memset( NetworkIssCommKey, 0, sizeof( NetworkIssCommKey ) );
	
	strcpy( Input_NetworkId, I_NetworkId );
	
	/* EXEC SQL SELECT
		RTRIM(NETWORKID),
		RTRIM(NETWORKMASTERKEY),
		RTRIM(NETWORKACQCOMMKEY),
		RTRIM(NETWORKISSCOMMKEY),
		NETWORKKEYLEN,
		KEYPROPERTY
	INTO
		:NetworkId,
		:NetworkMasterKey,
		:NetworkAcqCommKey,
		:NetworkIssCommKey,
		:NetworkKeyLen,
		:KeyProperty
	FROM EZNETWORKKEY WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 7;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(NETWORKID) ,RTRIM(NETWORKMASTERKEY) ,RTRIM(NETW\
ORKACQCOMMKEY) ,RTRIM(NETWORKISSCOMMKEY) ,NETWORKKEYLEN ,KEYPROPERTY into :b0,\
:b1,:b2,:b3,:b4,:b5  from EZNETWORKKEY where RTRIM(NETWORKID)=:b6";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )75;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)NetworkId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)NetworkMasterKey;
 sqlstm.sqhstl[1] = (unsigned int  )65;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)NetworkAcqCommKey;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)NetworkIssCommKey;
 sqlstm.sqhstl[3] = (unsigned int  )65;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&NetworkKeyLen;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&KeyProperty;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)Input_NetworkId;
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

	strcpy( ntwkkey_rec->NetworkId, NetworkId );
	strcpy( ntwkkey_rec->NetworkMasterKey, NetworkMasterKey );
	strcpy( ntwkkey_rec->NetworkAcqCommKey, NetworkAcqCommKey );
	strcpy( ntwkkey_rec->NetworkIssCommKey, NetworkIssCommKey );
	ntwkkey_rec->NetworkKeyLen = NetworkKeyLen; 
	ntwkkey_rec->KeyProperty = KeyProperty;
	
	return sqlca.sqlcode;
}


int readEzSecurityTable( const char *I_SecurityId, struct EzSecurity *ezsecurity_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SecurityId[ 11 ];
		char Input_SecurityId[ 11 ];
		char PINVerificationMethod;
		char EPVK[ 65 ];
		char DecimilizationTable[ 17 ];
		char PINPadChar;
		char PANPadChar;
		short PINLen;
		short PANLen;
		short PANValidationOffset;
		char PINBlockFormat[ 3 ];
		short PANValidationLength;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR SecurityId IS STRING(11); */ 

	/* EXEC SQL VAR Input_SecurityId IS STRING(11); */ 

	/* EXEC SQL VAR EPVK IS STRING(65); */ 

	/* EXEC SQL VAR DecimilizationTable IS STRING(17); */ 

	/* EXEC SQL VAR PINBlockFormat IS STRING(3); */ 

	
	memset( SecurityId, 0, sizeof( SecurityId ) );
	memset( Input_SecurityId, 0, sizeof( Input_SecurityId ) );
	memset( EPVK, 0, sizeof( EPVK ) );
	memset( DecimilizationTable, 0, sizeof( DecimilizationTable ) );
	memset( PINBlockFormat, 0, sizeof( PINBlockFormat ) );
	
	strcpy( Input_SecurityId, I_SecurityId );
	
	/* EXEC SQL SELECT
		RTRIM(SECURITYID),
        PINVERIFICATIONMETHOD,
        RTRIM(EPVK),
        RTRIM(DECIMILIZATIONTABLE),
        PINPADCHAR,
		PANPADCHAR,
		PINLEN,
		PANLEN,
		PANVALIDATIONOFFSET,
		RTRIM(PINBLOCKFORMAT),
		PANVALIDATIONLENGTH
	INTO
		:SecurityId,
		:PINVerificationMethod,
		:EPVK,
		:DecimilizationTable,
		:PINPadChar,
		:PANPadChar,
		:PINLen,
		:PANLen,
		:PANValidationOffset,
		:PINBlockFormat,
		:PANValidationLength
	FROM EZSECURITY WHERE RTRIM(SECURITYID)=:Input_SecurityId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(SECURITYID) ,PINVERIFICATIONMETHOD ,RTRIM(EPVK)\
 ,RTRIM(DECIMILIZATIONTABLE) ,PINPADCHAR ,PANPADCHAR ,PINLEN ,PANLEN ,PANVALID\
ATIONOFFSET ,RTRIM(PINBLOCKFORMAT) ,PANVALIDATIONLENGTH into :b0,:b1,:b2,:b3,:\
b4,:b5,:b6,:b7,:b8,:b9,:b10  from EZSECURITY where RTRIM(SECURITYID)=:b11";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )118;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SecurityId;
 sqlstm.sqhstl[0] = (unsigned int  )11;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&PINVerificationMethod;
 sqlstm.sqhstl[1] = (unsigned int  )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)EPVK;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)DecimilizationTable;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&PINPadChar;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&PANPadChar;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&PINLen;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&PANLen;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&PANValidationOffset;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)PINBlockFormat;
 sqlstm.sqhstl[9] = (unsigned int  )3;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&PANValidationLength;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(short);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)Input_SecurityId;
 sqlstm.sqhstl[11] = (unsigned int  )11;
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

	strcpy( ezsecurity_rec->SecurityId, SecurityId );
	ezsecurity_rec->PINVerificationMethod = PINVerificationMethod;
	strcpy( ezsecurity_rec->EPVK, EPVK );
	strcpy( ezsecurity_rec->DecimilizationTable, DecimilizationTable );
	ezsecurity_rec->PINPadChar = PINPadChar;
	ezsecurity_rec->PANPadChar = PANPadChar;
	ezsecurity_rec->PINLen = PINLen;
	ezsecurity_rec->PANLen = PANLen;
	ezsecurity_rec->PANValidationOffset = PANValidationOffset;
	strcpy( ezsecurity_rec->PINBlockFormat, PINBlockFormat );
	ezsecurity_rec->PANValidationLength = PANValidationLength;
	
	return sqlca.sqlcode;
}

int readEzSecurityPropertyTable( const char *I_RecordId, struct EzSecurityProperty *securityproperty_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 11 ];
		char Input_RecordId[ 11 ];
		char InstSecurityGroupId[ 17 ];
		char SecurityProtocol[ 17 ];
		char SecurityChannel[ 33 ];
		int Priority;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(11); */ 

	/* EXEC SQL VAR Input_RecordId IS STRING(11); */ 

	/* EXEC SQL VAR InstSecurityGroupId IS STRING(17); */ 

	/* EXEC SQL VAR SecurityProtocol IS STRING(17); */ 

	/* EXEC SQL VAR SecurityChannel IS STRING(33); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( Input_RecordId, 0, sizeof( Input_RecordId ) );
	memset( InstSecurityGroupId, 0, sizeof( InstSecurityGroupId ) );
	memset( SecurityProtocol, 0, sizeof( SecurityProtocol ) );
	memset( SecurityChannel, 0, sizeof( SecurityChannel ) );
	
	strcpy( Input_RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(RECORDID),
        RTRIM(INSTSECURITYGROUPID),
        RTRIM(SECURITYPROTOCOL),
        RTRIM(SECURITYCHANNEL),
        PRIORITY
	INTO
		:RecordId,
        :InstSecurityGroupId,
        :SecurityProtocol,
        :SecurityChannel,
        :Priority
	FROM EZSECURITYPROPERTY WHERE RTRIM(RECORDID)=:Input_RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(RECORDID) ,RTRIM(INSTSECURITYGROUPID) ,RTRIM(SE\
CURITYPROTOCOL) ,RTRIM(SECURITYCHANNEL) ,PRIORITY into :b0,:b1,:b2,:b3,:b4  fr\
om EZSECURITYPROPERTY where RTRIM(RECORDID)=:b5";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )181;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)RecordId;
 sqlstm.sqhstl[0] = (unsigned int  )11;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)InstSecurityGroupId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)SecurityProtocol;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)SecurityChannel;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&Priority;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)Input_RecordId;
 sqlstm.sqhstl[5] = (unsigned int  )11;
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
		
	strcpy( securityproperty_rec->RecordId, RecordId );
	strcpy( securityproperty_rec->InstSecurityGroupId, InstSecurityGroupId );
	strcpy( securityproperty_rec->SecurityProtocol, SecurityProtocol );
	strcpy( securityproperty_rec->SecurityChannel, SecurityChannel );
	securityproperty_rec->Priority = Priority;
	
	return sqlca.sqlcode;
}

int readEzHSMInfoTable( const char *I_HSMName, struct EzHSMInfo *hsminfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char HSMName[ 33 ];
		char Input_HSMName[ 33 ];
		char HSMProtocol[ 17 ];
		char HSMType[ 17 ];
		char HSMAddress[ 33 ];
		int HSMPortNo;
		int HeaderLen;
		char HeaderType[ 9 ];
		int HSMHeaderLen;
		int HSMTimeOut;
		int ConnectionInterval;
		int HSMStatus;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR HSMName IS STRING(33); */ 

	/* EXEC SQL VAR Input_HSMName IS STRING(33); */ 

	/* EXEC SQL VAR HSMProtocol IS STRING(17); */ 

	/* EXEC SQL VAR HSMType IS STRING(17); */ 

	/* EXEC SQL VAR HSMAddress IS STRING(33); */ 

	/* EXEC SQL VAR HeaderType IS STRING(9); */ 

	
	memset( HSMName, 0, sizeof( HSMName ) );
	memset( Input_HSMName, 0, sizeof( Input_HSMName ) );
	memset( HSMProtocol, 0, sizeof( HSMProtocol ) );
	memset( HSMType, 0, sizeof( HSMType ) );
	memset( HSMAddress, 0, sizeof( HSMAddress ) );
	memset( HeaderType, 0, sizeof( HeaderType ) );
	
	strcpy( Input_HSMName, I_HSMName );
	
	/* EXEC SQL SELECT
		RTRIM(HSMNAME),
        RTRIM(HSMPROTOCOL),
        RTRIM(HSMTYPE),
        RTRIM(HSMADDRESS),
        HSMPORT,
        HEADERLEN,
		RTRIM(HEADERTYPE),
		HSMHEADERLEN,
		HSMTIMEOUT,
		CONNECTIONINTERVAL,
		HSMSTATUS
	INTO
		:HSMName,
        :HSMProtocol,
        :HSMType,
        :HSMAddress,
        :HSMPortNo,
        :HeaderLen,
        :HeaderType,
        :HSMHeaderLen,
        :HSMTimeOut,
        :ConnectionInterval,
        :HSMStatus
	FROM EZHSMINFO WHERE RTRIM(HSMNAME)=:Input_HSMName; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 12;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(HSMNAME) ,RTRIM(HSMPROTOCOL) ,RTRIM(HSMTYPE) ,R\
TRIM(HSMADDRESS) ,HSMPORT ,HEADERLEN ,RTRIM(HEADERTYPE) ,HSMHEADERLEN ,HSMTIME\
OUT ,CONNECTIONINTERVAL ,HSMSTATUS into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,:b\
9,:b10  from EZHSMINFO where RTRIM(HSMNAME)=:b11";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )220;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)HSMName;
 sqlstm.sqhstl[0] = (unsigned int  )33;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)HSMProtocol;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)HSMType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)HSMAddress;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&HSMPortNo;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&HeaderLen;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)HeaderType;
 sqlstm.sqhstl[6] = (unsigned int  )9;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&HSMHeaderLen;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&HSMTimeOut;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&ConnectionInterval;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&HSMStatus;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)Input_HSMName;
 sqlstm.sqhstl[11] = (unsigned int  )33;
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

	strcpy( hsminfo_rec->HSMName, HSMName );
    strcpy( hsminfo_rec->HSMProtocol, HSMProtocol );
    strcpy( hsminfo_rec->HSMType, HSMType );
    strcpy( hsminfo_rec->HSMAddress, HSMAddress );
    hsminfo_rec->HSMPortNo = HSMPortNo;
    hsminfo_rec->HeaderLen = HeaderLen;
    strcpy( hsminfo_rec->HeaderType, HeaderType );
    hsminfo_rec->HSMHeaderLen = HSMHeaderLen;
    hsminfo_rec->HSMTimeOut = HSMTimeOut;
    hsminfo_rec->ConnectionInterval = ConnectionInterval;
    hsminfo_rec->HSMStatus = HSMStatus;
	
	return sqlca.sqlcode;
}

