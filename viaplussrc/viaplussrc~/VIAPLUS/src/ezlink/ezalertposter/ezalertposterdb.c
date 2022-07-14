
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
    "ezalertposterdb.pc"
};


static unsigned int sqlctx = 19553899;


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
5,0,0,1,347,0,4,37,0,0,6,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,
0,
44,0,0,2,432,0,4,101,0,0,9,1,0,1,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,
0,0,2,5,0,0,2,5,0,0,1,5,0,0,
95,0,0,3,60,0,5,146,0,0,2,2,0,1,0,1,1,0,0,1,5,0,0,
118,0,0,4,0,0,29,152,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <ezlink/ezlnkmsg.h>
#include <ezlink/ezalertdbtypes.h>

int readSMSBufferInfoTable( const char *I_InstId, struct EzSMSBufferInfo *smsinfo_rec )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SMSSeqNo[ 25 ];
		char InstId[ 13 ];
		char SMSDate[ 10 ];
		char SMSTime[ 10 ];
		char MobileList[ 255 ];
		char MsgBuffer[ 4097 ];
		short ind_var;
    /* EXEC SQL END DECLARE SECTION; */ 

				
	/* EXEC SQL VAR SMSSeqNo IS STRING(25); */ 

	/* EXEC SQL VAR InstId IS STRING(13); */ 

	/* EXEC SQL VAR SMSDate IS STRING(10); */ 

	/* EXEC SQL VAR SMSTime IS STRING(10); */ 

	/* EXEC SQL VAR MobileList IS STRING(255); */ 

	/* EXEC SQL VAR MsgBuffer IS STRING(4097); */ 

	
	memset( SMSSeqNo, 0, sizeof( SMSSeqNo ) );
	memset( InstId, 0, sizeof( InstId ) );
	memset( SMSDate, 0, sizeof( SMSDate	) );
	memset( SMSTime, 0, sizeof( SMSTime ) );
	memset( MobileList, 0, sizeof( MobileList ) );
	memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
	
	
	strcpy( InstId, I_InstId );

	/* EXEC SQL SELECT
		RTRIM(SMSSEQNO),
		RTRIM(SMSDATE),
		RTRIM(SMSTIME),
		RTRIM(MOBILELIST),
		RTRIM(MSGBUFFER)
	INTO
		:SMSSeqNo:ind_var,
		:SMSDate:ind_var,
		:SMSTime:ind_var,
		:MobileList:ind_var,
		:MsgBuffer:ind_var
    FROM EZSMSBUFFERINFO WHERE RTRIM(SMSSEQNO) || RTRIM(SMSDATE) || RTRIM(SMSTIME) IN (SELECT MIN(RTRIM(SMSSEQNO)||RTRIM(SMSDATE)||RTRIM(SMSTIME)) FROM EZSMSBUFFERINFO WHERE RTRIM(INSTID)=:InstId AND SMSSTATUS = 'P' ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 6;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(SMSSEQNO) ,RTRIM(SMSDATE) ,RTRIM(SMSTIME) ,RTRI\
M(MOBILELIST) ,RTRIM(MSGBUFFER) into :b0:b1,:b2:b3,:b4:b5,:b6:b7,:b8:b9  from \
EZSMSBUFFERINFO where ((RTRIM(SMSSEQNO)||RTRIM(SMSDATE))||RTRIM(SMSTIME)) in (\
select min(((RTRIM(SMSSEQNO)||RTRIM(SMSDATE))||RTRIM(SMSTIME)))  from EZSMSBUF\
FERINFO where (RTRIM(INSTID)=:b10 and SMSSTATUS='P'))";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SMSSeqNo;
 sqlstm.sqhstl[0] = (unsigned int  )25;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)SMSDate;
 sqlstm.sqhstl[1] = (unsigned int  )10;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)SMSTime;
 sqlstm.sqhstl[2] = (unsigned int  )10;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)MobileList;
 sqlstm.sqhstl[3] = (unsigned int  )255;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)MsgBuffer;
 sqlstm.sqhstl[4] = (unsigned int  )4097;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)InstId;
 sqlstm.sqhstl[5] = (unsigned int  )13;
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



	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;

	strcpy( smsinfo_rec->SMSSeqNo, SMSSeqNo );
	strcpy( smsinfo_rec->InstId, InstId );
	strcpy( smsinfo_rec->SMSDate, SMSDate );
	strcpy( smsinfo_rec->SMSTime, SMSTime );
	strcpy( smsinfo_rec->MobileList, MobileList );
	strcpy( smsinfo_rec->MsgBuffer, MsgBuffer );
	return sqlca.sqlcode;
}

int readMailBufferInfoTable( const char *I_InstId, struct EzMailBufferInfo *mailinfo_rec )
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
		short ind_var;
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
	memset( MailDate, 0, sizeof( MailDate	) );
	memset( MailTime, 0, sizeof( MailTime ) );
	memset( FromAddress, 0, sizeof( FromAddress ) );
	memset( ToList, 0, sizeof( ToList ) );
	memset( CCList, 0, sizeof( CCList ) );
	memset( Subject, 0, sizeof( Subject ) );
	memset( MsgBuffer, 0, sizeof( MsgBuffer ) );
		
	strcpy( InstId, I_InstId );

	/* EXEC SQL SELECT
		RTRIM(MAILSEQNO),
		RTRIM(MAILDATE),
		RTRIM(MAILTIME),
		RRIM(FROMADDRESS),
		RTRIM(TOLIST),
		RTRIM(CCLIST),
		RTRIM(SUBJECT),
		RTRIM(MSGBUFFER)
	INTO
		:MailSeqNo:ind_var,
		:MailDate:ind_var,
		:MailTime:ind_var,
		:FromAddress:ind_var,
		:ToList:ind_var,
		:CCList:ind_var,
		:Subject:ind_var,
		:MsgBuffer:ind_var
    FROM EZMAILBUFFERINFO WHERE RTRIM(MAILSEQNO) || RTRIM(MAILDATE) || RTRIM(MAILTIME) IN (SELECT MIN(RTRIM(MAILSEQNO)||RTRIM(MAILDATE)||RTRIM(MAILTIME)) FROM EZMAILBUFFERINFO WHERE RTRIM(INSTID)=:InstId AND MAILSTATUS = 'P' ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(MAILSEQNO) ,RTRIM(MAILDATE) ,RTRIM(MAILTIME) ,R\
RIM(FROMADDRESS) ,RTRIM(TOLIST) ,RTRIM(CCLIST) ,RTRIM(SUBJECT) ,RTRIM(MSGBUFFE\
R) into :b0:b1,:b2:b3,:b4:b5,:b6:b7,:b8:b9,:b10:b11,:b12:b13,:b14:b15  from EZ\
MAILBUFFERINFO where ((RTRIM(MAILSEQNO)||RTRIM(MAILDATE))||RTRIM(MAILTIME)) in\
 (select min(((RTRIM(MAILSEQNO)||RTRIM(MAILDATE))||RTRIM(MAILTIME)))  from EZM\
AILBUFFERINFO where (RTRIM(INSTID)=:b16 and MAILSTATUS='P'))";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )44;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)MailSeqNo;
 sqlstm.sqhstl[0] = (unsigned int  )25;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)MailDate;
 sqlstm.sqhstl[1] = (unsigned int  )10;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)MailTime;
 sqlstm.sqhstl[2] = (unsigned int  )10;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)FromAddress;
 sqlstm.sqhstl[3] = (unsigned int  )65;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)ToList;
 sqlstm.sqhstl[4] = (unsigned int  )255;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)CCList;
 sqlstm.sqhstl[5] = (unsigned int  )255;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)&ind_var;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)Subject;
 sqlstm.sqhstl[6] = (unsigned int  )129;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)&ind_var;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)MsgBuffer;
 sqlstm.sqhstl[7] = (unsigned int  )4097;
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)&ind_var;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)InstId;
 sqlstm.sqhstl[8] = (unsigned int  )13;
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



	if( sqlca.sqlcode != 0 )
    	return sqlca.sqlcode;

	strcpy( mailinfo_rec->MailSeqNo, MailSeqNo );
	strcpy( mailinfo_rec->InstId, InstId );
	strcpy( mailinfo_rec->MailDate, MailDate );
	strcpy( mailinfo_rec->MailTime, MailTime );
	strcpy( mailinfo_rec->FromAddress, FromAddress );
	strcpy( mailinfo_rec->ToList, ToList );
	strcpy( mailinfo_rec->CCList, CCList );
	strcpy( mailinfo_rec->Subject, Subject );
	strcpy( mailinfo_rec->MsgBuffer, MsgBuffer );
	return sqlca.sqlcode;
}

int updateSMSStatus( struct EzSMSBufferInfo *smsinfo_rec, char SMSStatus )
{
	/* EXEC SQL BEGIN DECLARE SECTION ; */ 

		char SeqNo[ 25 ];
	/* EXEC SQL END DECLARE SECTION ; */ 

	
	/* EXEC SQL VAR SeqNo IS STRING(25); */ 

	memset( SeqNo, 0, sizeof( SeqNo ) );
	strcpy( SeqNo, smsinfo_rec->SMSSeqNo );

	/* EXEC SQL UPDATE EZSMSBUFFERINFO SET SMSSTATUS=:SMSStatus WHERE SMSSEQNO=:SeqNo; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 9;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "update EZSMSBUFFERINFO  set SMSSTATUS=:b0 where SMSSEQNO=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )95;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&SMSStatus;
 sqlstm.sqhstl[0] = (unsigned int  )1;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)SeqNo;
 sqlstm.sqhstl[1] = (unsigned int  )25;
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
            return sqlca.sqlcode ;
    else
    {
            /* EXEC SQL COMMIT; */ 

{
            struct sqlexd sqlstm;
            sqlstm.sqlvsn = 12;
            sqlstm.arrsiz = 9;
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


            return sqlca.sqlcode ;
    }

}

int updateMailStatus( struct EzMailBufferInfo *mailinfo_rec, char MailStatus )
{
	
}


