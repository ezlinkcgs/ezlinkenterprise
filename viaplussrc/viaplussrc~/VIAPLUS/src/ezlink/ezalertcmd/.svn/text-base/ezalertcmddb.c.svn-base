
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
    "ezalertcmddb.pc"
};


static unsigned int sqlctx = 2441515;


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
            void  *sqhstv[9];
   unsigned int   sqhstl[9];
            int   sqhsts[9];
            void  *sqindv[9];
            int   sqinds[9];
   unsigned int   sqharm[9];
   unsigned int   *sqharc[9];
   unsigned short  sqadto[9];
   unsigned short  sqtdso[9];
} sqlstm = {12,9};

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
5,0,0,1,223,0,4,39,0,0,9,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,1,0,0,2,1,0,
0,2,5,0,0,2,5,0,0,1,5,0,0,
56,0,0,2,133,0,4,95,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
87,0,0,3,174,0,4,143,0,0,6,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,
0,0,
126,0,0,4,145,0,4,192,0,0,6,1,0,1,0,2,5,0,0,2,1,0,0,2,1,0,0,2,5,0,0,2,5,0,0,1,
5,0,0,
165,0,0,5,123,0,4,239,0,0,4,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ezlink/ezalertdbtypes.h>

int readEzStatusAlert( const char *I_RecordId, struct EzStatusAlertMemory *statusalert_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[17];
		char InstId[17];
		char DeviceId[ 33 ];
		char AlertType[ 17 ];
		char StatusList[ 129 ];
		char SMSReq;
		char MailReq;
		char SMSAlertGroupId[ 17 ];
		char MailAlertGroupId[ 17 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceId IS STRING(33); */ 

	/* EXEC SQL VAR AlertType IS STRING(17); */ 

	/* EXEC SQL VAR StatusList IS STRING(129); */ 

	/* EXEC SQL VAR SMSAlertGroupId IS STRING(17); */ 

	/* EXEC SQL VAR MailAlertGroupId IS STRING(17); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( DeviceId, 0, sizeof( DeviceId ) );
	memset( AlertType, 0, sizeof( AlertType ) );
	memset( StatusList, 0, sizeof( StatusList ) );
	memset( SMSAlertGroupId, 0, sizeof( SMSAlertGroupId ) );
	memset( MailAlertGroupId, 0, sizeof( MailAlertGroupId ) );
	
	strcpy( RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		RTRIM(DEVICEID),
		RTRIM(ALERTTYPE),
		RTRIM(STATUSLIST),
		SMSREQ,
		MAILREQ,
		RTRIM(SMSALERTGROUPID),
		RTRIM(MAILALERTGROUPID)
	INTO
		:InstId,
		:DeviceId,
		:AlertType,
		:StatusList,
		:SMSReq,
		:MailReq,
		:SMSAlertGroupId,
		:MailAlertGroupId
	FROM EZSTATUSALERT WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,RTRIM(DEVICEID) ,RTRIM(ALERTTYPE) ,RTR\
IM(STATUSLIST) ,SMSREQ ,MAILREQ ,RTRIM(SMSALERTGROUPID) ,RTRIM(MAILALERTGROUPI\
D) into :b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7  from EZSTATUSALERT where RTRIM(RECORD\
ID)=:b8";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)DeviceId;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)AlertType;
 sqlstm.sqhstl[2] = (unsigned int  )17;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)StatusList;
 sqlstm.sqhstl[3] = (unsigned int  )129;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SMSReq;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&MailReq;
 sqlstm.sqhstl[5] = (unsigned int  )1;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)SMSAlertGroupId;
 sqlstm.sqhstl[6] = (unsigned int  )17;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)MailAlertGroupId;
 sqlstm.sqhstl[7] = (unsigned int  )17;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)RecordId;
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
		
	strcpy( statusalert_rec->RecordId, RecordId );
	strcpy( statusalert_rec->InstId, InstId );
	strcpy( statusalert_rec->DeviceId, DeviceId );
	strcpy( statusalert_rec->AlertType, AlertType );
	strcpy( statusalert_rec->StatusList, StatusList );
	statusalert_rec->SMSReq = SMSReq;
	statusalert_rec->MailReq = MailReq;
	strcpy( statusalert_rec->SMSAlertGroupId, SMSAlertGroupId );
	strcpy( statusalert_rec->MailAlertGroupId, MailAlertGroupId );
	return sqlca.sqlcode;
}

int readEzSMSAlertGroup( const char *I_SMSAlertGroupId, struct EzSMSAlertGroupMemory *smsalertgroup_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SMSAlertGroupId[17];
		char MobileList[ 255 ];
		char TemplateFile[ 33 ];
		char GSMPort[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR SMSAlertGroupId IS STRING(17); */ 

	/* EXEC SQL VAR MobileList IS STRING(255); */ 

	/* EXEC SQL VAR TemplateFile IS STRING(33); */ 

	/* EXEC SQL VAR GSMPort IS STRING(33); */ 

	
	memset( SMSAlertGroupId, 0, sizeof( SMSAlertGroupId ) );
	memset( MobileList, 0, sizeof( MobileList ) );
	memset( TemplateFile, 0, sizeof( TemplateFile ) );
	memset( GSMPort, 0, sizeof( GSMPort ) );
	
	strcpy( SMSAlertGroupId, I_SMSAlertGroupId );
	
	/* EXEC SQL SELECT
		RTRIM(MOBILELIST),
		RTRIM(TEMPLATEFILE),
		RTRIM(GSMPORT)
	INTO
		:MobileList,
		:TemplateFile,
		:GSMPort
	FROM EZSMSALERTGROUP WHERE RTRIM(SMSALERTGROUPID)=:SMSAlertGroupId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(MOBILELIST) ,RTRIM(TEMPLATEFILE) ,RTRIM(GSMPORT\
) into :b0,:b1,:b2  from EZSMSALERTGROUP where RTRIM(SMSALERTGROUPID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )56;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)MobileList;
 sqlstm.sqhstl[0] = (unsigned int  )255;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TemplateFile;
 sqlstm.sqhstl[1] = (unsigned int  )33;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)GSMPort;
 sqlstm.sqhstl[2] = (unsigned int  )33;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)SMSAlertGroupId;
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
	
	strcpy( smsalertgroup_rec->SMSAlertGroupId, SMSAlertGroupId );
	strcpy( smsalertgroup_rec->MobileList, MobileList );
	strcpy( smsalertgroup_rec->TemplateFile, TemplateFile );
	strcpy( smsalertgroup_rec->GSMPort, GSMPort );
	
	return sqlca.sqlcode;
}

int readEzMailAlertGroup( const char *I_MailAlertGroupId, struct EzMailAlertGroupMemory *mailalertgroup_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MailAlertGroupId[17];
		char FromAddress[ 65 ];
		char ToList[ 255 ];
		char CCList[ 255 ];
		char Subject[ 129 ];
		char TemplateFile[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MailAlertGroupId IS STRING(17); */ 

	/* EXEC SQL VAR FromAddress IS STRING(65); */ 

	/* EXEC SQL VAR ToList IS STRING(255); */ 

	/* EXEC SQL VAR CCList IS STRING(255); */ 

	/* EXEC SQL VAR Subject IS STRING(129); */ 

	/* EXEC SQL VAR TemplateFile IS STRING(33); */ 

	
	memset( MailAlertGroupId, 0, sizeof( MailAlertGroupId ) );
	memset( FromAddress, 0, sizeof( FromAddress ) );
	memset( ToList, 0, sizeof( ToList ) );
	memset( CCList, 0, sizeof( CCList ) );
	memset( Subject, 0, sizeof( Subject ) );
	memset( TemplateFile, 0, sizeof( TemplateFile ) );
	
	strcpy( MailAlertGroupId, I_MailAlertGroupId );
	
	/* EXEC SQL SELECT
		RTRIM(FROMADDRESS),
		RTRIM(TOLIST),
		RTRIM(CCLIST),
		RTRIM(SUBJECT),
		RTRIM(TEMPLATEFILE)
	INTO
		:FromAddress,
		:ToList,
		:CCList,
		:Subject,
		:TemplateFile
	FROM EZMAILALERTGROUP WHERE RTRIM(MAILALERTGROUPID)=:MailAlertGroupId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(FROMADDRESS) ,RTRIM(TOLIST) ,RTRIM(CCLIST) ,RTR\
IM(SUBJECT) ,RTRIM(TEMPLATEFILE) into :b0,:b1,:b2,:b3,:b4  from EZMAILALERTGRO\
UP where RTRIM(MAILALERTGROUPID)=:b5";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )87;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)FromAddress;
 sqlstm.sqhstl[0] = (unsigned int  )65;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)ToList;
 sqlstm.sqhstl[1] = (unsigned int  )255;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)CCList;
 sqlstm.sqhstl[2] = (unsigned int  )255;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)Subject;
 sqlstm.sqhstl[3] = (unsigned int  )129;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TemplateFile;
 sqlstm.sqhstl[4] = (unsigned int  )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)MailAlertGroupId;
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
	
	strcpy( mailalertgroup_rec->MailAlertGroupId, MailAlertGroupId );
	strcpy( mailalertgroup_rec->ToList, ToList );
	strcpy( mailalertgroup_rec->CCList, CCList );
	strcpy( mailalertgroup_rec->Subject, Subject );
	strcpy( mailalertgroup_rec->TemplateFile, TemplateFile );
	
	return sqlca.sqlcode;
}

int readEzAlertInfo( const char *I_RecordId, struct EzAlertInfoMemory *alertinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[17];
		char InstId[17];
		char SMSReq;
		char MailReq;
		char SMSChannel[ 33 ];
		char MailChannel[ 33 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR InstId IS STRING(17); */ 

	/* EXEC SQL VAR SMSChannel IS STRING(33); */ 

	/* EXEC SQL VAR MailChannel IS STRING(33); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( SMSChannel, 0, sizeof( SMSChannel ) );
	memset( MailChannel, 0, sizeof( MailChannel ) );
	
	strcpy( RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(INSTID),
		SMSREQ,
		MAILREQ,
		RTRIM(SMSCHANNEL),
		RTRIM(MAILCHANNEL)
	INTO
		:InstId,
		:SMSReq,
		:MailReq,
		:SMSChannel,
		:MailChannel
	FROM EZALERTINFO WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(INSTID) ,SMSREQ ,MAILREQ ,RTRIM(SMSCHANNEL) ,RT\
RIM(MAILCHANNEL) into :b0,:b1,:b2,:b3,:b4  from EZALERTINFO where RTRIM(RECORD\
ID)=:b5";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )126;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)InstId;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&SMSReq;
 sqlstm.sqhstl[1] = (unsigned int  )1;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&MailReq;
 sqlstm.sqhstl[2] = (unsigned int  )1;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)SMSChannel;
 sqlstm.sqhstl[3] = (unsigned int  )33;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)MailChannel;
 sqlstm.sqhstl[4] = (unsigned int  )33;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)RecordId;
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
	
	strcpy( alertinfo_rec->RecordId, RecordId );
	strcpy( alertinfo_rec->InstId, InstId );
	alertinfo_rec->SMSReq = SMSReq;
	alertinfo_rec->MailReq = MailReq;
	strcpy( alertinfo_rec->SMSChannel, SMSChannel );
	strcpy( alertinfo_rec->MailChannel, MailChannel );
	return sqlca.sqlcode;
}

int readEzAlertDesc( const char *I_RecordId, struct EzAlertDescMemory *alertdesc_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char RecordId[ 17 ];
		char DeviceType[ 17 ];
		char StatusCode[ 10 ];
		char StatusDesc[ 65 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR RecordId IS STRING(17); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR StatusCode IS STRING(10); */ 

	/* EXEC SQL VAR StatusDesc IS STRING(65); */ 

	
	memset( RecordId, 0, sizeof( RecordId ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( StatusCode, 0, sizeof( StatusCode ) );
	memset( StatusDesc, 0, sizeof( StatusDesc ) );
	
	strcpy( RecordId, I_RecordId );
	
	/* EXEC SQL SELECT
		RTRIM(DEVICETYPE),
		RTRIM(STATUSCODE),
		RTRIM(STATUSDESC)
	INTO
		:DeviceType,
		:StatusCode,
		:StatusDesc
	FROM EZALERTDESC WHERE RTRIM(RECORDID)=:RecordId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(DEVICETYPE) ,RTRIM(STATUSCODE) ,RTRIM(STATUSDES\
C) into :b0,:b1,:b2  from EZALERTDESC where RTRIM(RECORDID)=:b3";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )165;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)DeviceType;
 sqlstm.sqhstl[0] = (unsigned int  )17;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)StatusCode;
 sqlstm.sqhstl[1] = (unsigned int  )10;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)StatusDesc;
 sqlstm.sqhstl[2] = (unsigned int  )65;
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
	
	strcpy( alertdesc_rec->RecordId, RecordId );
	strcpy( alertdesc_rec->DeviceType, DeviceType );
	strcpy( alertdesc_rec->StatusCode, StatusCode );
	strcpy( alertdesc_rec->StatusDesc, StatusDesc );
	return sqlca.sqlcode;
}
