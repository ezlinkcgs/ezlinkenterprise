
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
    "ezalertmgrdb.pc"
};


static unsigned int sqlctx = 2442859;


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
            void  *sqhstv[10];
   unsigned int   sqhstl[10];
            int   sqhsts[10];
            void  *sqindv[10];
            int   sqinds[10];
   unsigned int   sqharm[10];
   unsigned int   *sqharc[10];
   unsigned short  sqadto[10];
   unsigned short  sqtdso[10];
} sqlstm = {12,10};

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
5,0,0,1,129,0,3,40,0,0,7,7,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,5,0,
0,1,5,0,0,
48,0,0,2,0,0,29,65,0,0,0,0,0,1,0,
63,0,0,3,169,0,3,115,0,0,10,10,0,1,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,1,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
118,0,0,4,0,0,29,146,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int insertSMSBufferInfoTable( const char *I_SMSSeqNo, const char *I_InstId, const char *I_SMSDate, const char *I_SMSTime, char I_SMSStatus, const char *I_MobileList, const char *I_MsgBuffer )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SMSSeqNo[ 25 ];
		char InstId[ 13 ];
		char SMSDate[ 10 ];
		char SMSTime[ 10 ];
		char SMSStatus;
		char MobileList[ 255 ];
		char MsgBuffer[ 4097 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR SMSSeqNo IS STRING(25); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR SMSDate IS STRING(10); */ 

	/* EXEC SQL VAR SMSTime IS STRING(10); */ 

	/* EXEC SQL VAR MobileList IS STRING(255); */ 

	/* EXEC SQL VAR MsgBuffer IS STRING(4097); */ 

	
	memset( SMSSeqNo, 0, sizeof( SMSSeqNo ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( SMSDate, 0, sizeof( SMSDate ) );
	memset( SMSTime, 0, sizeof( SMSTime ) );
	memset( MobileList, 0, sizeof( MobileList ) );
	memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
	
	strcpy( SMSSeqNo, I_SMSSeqNo );
	strcpy( InstId, I_InstId );
	strcpy( SMSDate, I_SMSDate );
	strcpy( SMSTime, I_SMSTime );
	SMSStatus = I_SMSStatus;
	strcpy( MobileList, I_MobileList );	
	strcpy( MsgBuffer, I_MsgBuffer );
	
	/* EXEC SQL INSERT INTO EZSMSBUFFERINFO
	(
		SMSSEQNO,
		INSTID,
		SMSDATE,
		SMSTIME,
		SMSSTATUS,
		MOBILELIST,
		MSGBUFFER
	)
	VALUES
	(
		:SMSSeqNo,
		:InstId,
		:SMSDate,
		:SMSTime,
		:SMSStatus,
		:MobileList,
		:MsgBuffer
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 7;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZSMSBUFFERINFO (SMSSEQNO,INSTID,SMSDATE,SMSTIME\
,SMSSTATUS,MOBILELIST,MSGBUFFER) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SMSSeqNo;
 sqlstm.sqhstl[0] = (unsigned int  )25;
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
 sqlstm.sqhstv[2] = (         void  *)SMSDate;
 sqlstm.sqhstl[2] = (unsigned int  )10;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)SMSTime;
 sqlstm.sqhstl[3] = (unsigned int  )10;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SMSStatus;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)MobileList;
 sqlstm.sqhstl[5] = (unsigned int  )255;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)MsgBuffer;
 sqlstm.sqhstl[6] = (unsigned int  )4097;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {
            /* EXEC SQL COMMIT; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 7;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )48;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return sqlca.sqlcode;
    }
}

int insertMailBufferInfoTable( const char *I_MailSeqNo, const char *I_InstId, const char *I_MailDate, const char *I_MailTime, char I_MailStatus, const char *I_FromAddress, const char *I_ToList, const char *I_CCList, const char *I_Subject, const char *I_MsgBuffer )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char MailSeqNo[ 25 ];
		char InstId[ 13 ];
		char MailDate[ 10 ];
		char MailTime[ 10 ];
		char MailStatus;
		char FromAddress[ 65 ];
		char ToList[ 255 ];
		char CCList[ 255 ];
		char Subject[ 129 ];
		char MsgBuffer[ 4097 ];
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR MailSeqNo IS STRING(25); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR MailDate IS STRING(10); */ 

	/* EXEC SQL VAR MailTime IS STRING(10); */ 

	/* EXEC SQL VAR FromAddress IS STRING(65); */ 

	/* EXEC SQL VAR ToList IS STRING(255); */ 

	/* EXEC SQL VAR CCList IS STRING(255); */ 

	/* EXEC SQL VAR Subject IS STRING(129); */ 

	/* EXEC SQL VAR MsgBuffer IS STRING(4097); */ 

	
	memset( MailSeqNo, 0, sizeof( MailSeqNo ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( MailDate, 0, sizeof( MailDate ) );
	memset( MailTime, 0, sizeof( MailTime ) );
	memset( FromAddress, 0, sizeof( FromAddress ) );
	memset( ToList, 0, sizeof( ToList ) );
	memset( CCList, 0, sizeof( CCList ) );
	memset( Subject, 0, sizeof( Subject ) );
	memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
	
	strcpy( MailSeqNo, I_MailSeqNo );
	strcpy( InstId, I_InstId );
	strcpy( MailDate, I_MailDate );
	strcpy( MailTime, I_MailTime );
	strcpy( FromAddress, I_FromAddress );
	strcpy( ToList, I_ToList );
	strcpy( CCList, I_CCList );
	strcpy( Subject, I_Subject );
	strcpy( MsgBuffer, I_MsgBuffer );
	
	/* EXEC SQL INSERT INTO EZMAILBUFFERINFO
	(
		MAILSEQNO,
		INSTID,
		MAILDATE,
		MAILTIME,
		MAILSTATUS,
		FROMADDRESS,
		TOLIST,
		CCLIST,
		SUBJECT,
		MSGBUFFER
	)
	VALUES
	(
		:MailSeqNo,
		:InstId,
		:MailDate,
		:MailTime,
		:MailStatus,
		:FromAddress,
		:ToList,
		:CCList,
		:Subject,
		:MsgBuffer
	); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 10;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "insert into EZMAILBUFFERINFO (MAILSEQNO,INSTID,MAILDATE,MAIL\
TIME,MAILSTATUS,FROMADDRESS,TOLIST,CCLIST,SUBJECT,MSGBUFFER) values (:b0,:b1,:\
b2,:b3,:b4,:b5,:b6,:b7,:b8,:b9)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )63;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)MailSeqNo;
 sqlstm.sqhstl[0] = (unsigned int  )25;
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
 sqlstm.sqhstv[2] = (         void  *)MailDate;
 sqlstm.sqhstl[2] = (unsigned int  )10;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MailTime;
 sqlstm.sqhstl[3] = (unsigned int  )10;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&MailStatus;
 sqlstm.sqhstl[4] = (unsigned int  )1;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)FromAddress;
 sqlstm.sqhstl[5] = (unsigned int  )65;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)ToList;
 sqlstm.sqhstl[6] = (unsigned int  )255;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)CCList;
 sqlstm.sqhstl[7] = (unsigned int  )255;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)Subject;
 sqlstm.sqhstl[8] = (unsigned int  )129;
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)MsgBuffer;
 sqlstm.sqhstl[9] = (unsigned int  )4097;
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


	
	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;
    else
    {
            /* EXEC SQL COMMIT; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 10;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )118;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return sqlca.sqlcode;
    }
};
