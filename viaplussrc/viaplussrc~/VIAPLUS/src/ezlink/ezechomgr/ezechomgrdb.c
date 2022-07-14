
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
           char  filnam[15];
};
static struct sqlcxp sqlfpn =
{
    14,
    "ezechomgrdb.pc"
};


static unsigned int sqlctx = 1219947;


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
   unsigned char  *sqhstv[5];
   unsigned long  sqhstl[5];
            int   sqhsts[5];
            short *sqindv[5];
            int   sqinds[5];
   unsigned long  sqharm[5];
   unsigned long  *sqharc[5];
   unsigned short  sqadto[5];
   unsigned short  sqtdso[5];
} sqlstm = {12,5};

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

 static char *sq0003 = 
"select RTRIM(NETWORKID) ,RTRIM(ECHOPROPERTYID) ,ECHOPROPERTY ,LOGONREQ  from\
 EZNETWORKECHO            ";

 static char *sq0004 = 
"select RTRIM(ECHOPROPERTYID) ,ECHOINTERVAL  from EZECHOPROPERTY            ";

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,1,0,0,
5,0,0,1,46,0,4,14,0,0,1,0,0,1,0,2,3,0,0,
24,0,0,2,47,0,4,26,0,0,1,0,0,1,0,2,3,0,0,
43,0,0,3,102,0,9,54,0,0,0,0,0,1,0,
58,0,0,3,0,0,13,61,0,0,4,0,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,2,1,0,0,
89,0,0,3,0,0,15,81,0,0,0,0,0,1,0,
104,0,0,4,75,0,9,106,0,0,0,0,0,1,0,
119,0,0,4,0,0,13,112,0,0,2,0,0,1,0,2,5,0,0,2,3,0,0,
142,0,0,4,0,0,15,128,0,0,0,0,0,1,0,
157,0,0,5,138,0,4,158,0,0,5,1,0,1,0,2,5,0,0,2,5,0,0,2,1,0,0,2,1,0,0,1,5,0,0,
192,0,0,6,115,0,4,199,0,0,3,1,0,1,0,2,5,0,0,2,3,0,0,1,5,0,0,
};


#include <ezdb/eznetworkecho.h>
#include <ezdb/ezechoproperty.h>
#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getEzNetworkEchoCount( int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

    	int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZNETWORKECHO; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZNETWORKECHO ";
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

int getEzEchoPropertyCount( int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

    	int reccount;
    /* EXEC SQL END DECLARE SECTION; */ 


    /* EXEC SQL SELECT COUNT(*) INTO :reccount FROM EZECHOPROPERTY; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select count(*)  into :b0  from EZECHOPROPERTY ";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )24;
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

int LoadEzNetworkEcho( struct EzNetworkEcho *eznetworkecho_ptr, int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char NetworkId[ 17 ];
        char EchoPropertyId[ 17 ];
        char EchoProperty;
        char LogOnReq;
    /* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR EchoPropertyId IS STRING(17); */ 


	/* EXEC SQL DECLARE eznetworkecho_cur CURSOR FOR
    SELECT
            RTRIM(NETWORKID),
            RTRIM(ECHOPROPERTYID),
            ECHOPROPERTY,
            LOGONREQ
    FROM EZNETWORKECHO; */ 


    /* EXEC SQL OPEN eznetworkecho_cur; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = sq0003;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )43;
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
        memset( NetworkId, 0, sizeof( NetworkId ) );
        memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );

        /* EXEC SQL FETCH eznetworkecho_cur INTO
        :NetworkId,
        :EchoPropertyId,
        :EchoProperty,
        :LogOnReq; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 4;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )58;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqfoff = (         int )0;
        sqlstm.sqfmod = (unsigned int )2;
        sqlstm.sqhstv[0] = (unsigned char  *)NetworkId;
        sqlstm.sqhstl[0] = (unsigned long )17;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)EchoPropertyId;
        sqlstm.sqhstl[1] = (unsigned long )17;
        sqlstm.sqhsts[1] = (         int  )0;
        sqlstm.sqindv[1] = (         short *)0;
        sqlstm.sqinds[1] = (         int  )0;
        sqlstm.sqharm[1] = (unsigned long )0;
        sqlstm.sqadto[1] = (unsigned short )0;
        sqlstm.sqtdso[1] = (unsigned short )0;
        sqlstm.sqhstv[2] = (unsigned char  *)&EchoProperty;
        sqlstm.sqhstl[2] = (unsigned long )1;
        sqlstm.sqhsts[2] = (         int  )0;
        sqlstm.sqindv[2] = (         short *)0;
        sqlstm.sqinds[2] = (         int  )0;
        sqlstm.sqharm[2] = (unsigned long )0;
        sqlstm.sqadto[2] = (unsigned short )0;
        sqlstm.sqtdso[2] = (unsigned short )0;
        sqlstm.sqhstv[3] = (unsigned char  *)&LogOnReq;
        sqlstm.sqhstl[3] = (unsigned long )1;
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

        memset( ( eznetworkecho_ptr + i ), 0, sizeof( struct EzNetworkEcho ) );
        strcpy( ( eznetworkecho_ptr + i )->NetworkId, NetworkId );
        strcpy( ( eznetworkecho_ptr + i )->EchoPropertyId, EchoPropertyId );
        ( eznetworkecho_ptr + i )->EchoProperty = EchoProperty;
        ( eznetworkecho_ptr + i )->LogOnReq = LogOnReq;
        i++;
	}
    *SqlErr = sqlca.sqlcode;
    /* EXEC SQL CLOSE eznetworkecho_cur; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )89;
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

int LoadEzEchoProperty( struct EzEchoProperty *ezechoproperty_ptr, int *SqlErr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char EchoPropertyId[ 17 ];
        int EchoInterval;
    /* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

    /* EXEC SQL VAR EchoPropertyId IS STRING(17); */ 


	/* EXEC SQL DECLARE ezechoproperty_cur CURSOR FOR
    SELECT
        RTRIM(ECHOPROPERTYID),
        ECHOINTERVAL
    FROM EZECHOPROPERTY; */ 


    /* EXEC SQL OPEN ezechoproperty_cur; */ 

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
        memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );

        /* EXEC SQL FETCH ezechoproperty_cur INTO
        :EchoPropertyId,
        :EchoInterval; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 4;
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
        sqlstm.sqhstv[0] = (unsigned char  *)EchoPropertyId;
        sqlstm.sqhstl[0] = (unsigned long )17;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqhstv[1] = (unsigned char  *)&EchoInterval;
        sqlstm.sqhstl[1] = (unsigned long )sizeof(int);
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


            
        if ( sqlca.sqlcode == 1403 )
        break;

        if ( sqlca.sqlcode != 0 )
        break;

        memset( ( ezechoproperty_ptr + i ), 0, sizeof( struct EzEchoProperty ) );
        strcpy( ( ezechoproperty_ptr + i )->EchoPropertyId, EchoPropertyId );
        ( ezechoproperty_ptr + i )->EchoInterval = EchoInterval;
        i++;
    }
    *SqlErr = sqlca.sqlcode;
    /* EXEC SQL CLOSE ezechoproperty_cur; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )142;
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

int readEzNetworkEcho( const char *I_NetworkId, struct EzNetworkEcho *eznetworkecho_ptr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char NetworkId[ 17 ];
        char Input_NetworkId[ 17 ];
        char EchoPropertyId[ 17 ];
        char EchoProperty;
        char LogOnReq;
    /* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

    /* EXEC SQL VAR NetworkId IS STRING(17); */ 

    /* EXEC SQL VAR Input_NetworkId IS STRING(17); */ 

    /* EXEC SQL VAR EchoPropertyId IS STRING(17); */ 


    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( Input_NetworkId, 0, sizeof( Input_NetworkId ) );
    memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );

    strcpy( Input_NetworkId, I_NetworkId );

    /* EXEC SQL SELECT
        RTRIM(NETWORKID),
        RTRIM(ECHOPROPERTYID),
        ECHOPROPERTY,
        LOGONREQ
    INTO
        :NetworkId,
        :EchoPropertyId,
        :EchoProperty,
        :LogOnReq
	FROM EZNETWORKECHO WHERE RTRIM(NETWORKID)=:Input_NetworkId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 5;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(NETWORKID) ,RTRIM(ECHOPROPERTYID) ,ECHOPROPE\
RTY ,LOGONREQ into :b0,:b1,:b2,:b3  from EZNETWORKECHO where RTRIM(NETWORKID)=\
:b4";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )157;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)NetworkId;
    sqlstm.sqhstl[0] = (unsigned long )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)EchoPropertyId;
    sqlstm.sqhstl[1] = (unsigned long )17;
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)&EchoProperty;
    sqlstm.sqhstl[2] = (unsigned long )1;
    sqlstm.sqhsts[2] = (         int  )0;
    sqlstm.sqindv[2] = (         short *)0;
    sqlstm.sqinds[2] = (         int  )0;
    sqlstm.sqharm[2] = (unsigned long )0;
    sqlstm.sqadto[2] = (unsigned short )0;
    sqlstm.sqtdso[2] = (unsigned short )0;
    sqlstm.sqhstv[3] = (unsigned char  *)&LogOnReq;
    sqlstm.sqhstl[3] = (unsigned long )1;
    sqlstm.sqhsts[3] = (         int  )0;
    sqlstm.sqindv[3] = (         short *)0;
    sqlstm.sqinds[3] = (         int  )0;
    sqlstm.sqharm[3] = (unsigned long )0;
    sqlstm.sqadto[3] = (unsigned short )0;
    sqlstm.sqtdso[3] = (unsigned short )0;
    sqlstm.sqhstv[4] = (unsigned char  *)Input_NetworkId;
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



    if( sqlca.sqlcode != 0 )
            return sqlca.sqlcode;

    strcpy( eznetworkecho_ptr->NetworkId, NetworkId );
    strcpy( eznetworkecho_ptr->EchoPropertyId, EchoPropertyId );
    eznetworkecho_ptr->EchoProperty = EchoProperty;
	eznetworkecho_ptr->LogOnReq = LogOnReq;
    return 0;

}
                                                                                       
int readEzEchoProperty( const char *I_EchoPropertyId, struct EzEchoProperty *ezechoproperty_ptr )
{
    /* EXEC SQL BEGIN DECLARE SECTION; */ 

        char EchoPropertyId[ 17 ];
        char Input_EchoPropertyId[ 17 ];
        int EchoInterval;
    /* EXEC SQL END DECLARE SECTION; */ 


    int i = 0;

    /* EXEC SQL VAR EchoPropertyId IS STRING(17); */ 

    /* EXEC SQL VAR Input_EchoPropertyId IS STRING(17); */ 

    
    memset( EchoPropertyId, 0, sizeof( EchoPropertyId ) );
    memset( Input_EchoPropertyId, 0, sizeof( Input_EchoPropertyId ) );
   
    strcpy( Input_EchoPropertyId, I_EchoPropertyId );

    /* EXEC SQL SELECT
        RTRIM(ECHOPROPERTYID),
        RTRIM(ECHOINTERVAL)
    INTO
        :EchoPropertyId,
        :EchoInterval
	FROM EZECHOPROPERTY WHERE RTRIM(ECHOPROPERTYID)=:Input_EchoPropertyId; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 5;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.stmt = "select RTRIM(ECHOPROPERTYID) ,RTRIM(ECHOINTERVAL) into :b\
0,:b1  from EZECHOPROPERTY where RTRIM(ECHOPROPERTYID)=:b2";
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )192;
    sqlstm.selerr = (unsigned short)1;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)EchoPropertyId;
    sqlstm.sqhstl[0] = (unsigned long )17;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqhstv[1] = (unsigned char  *)&EchoInterval;
    sqlstm.sqhstl[1] = (unsigned long )sizeof(int);
    sqlstm.sqhsts[1] = (         int  )0;
    sqlstm.sqindv[1] = (         short *)0;
    sqlstm.sqinds[1] = (         int  )0;
    sqlstm.sqharm[1] = (unsigned long )0;
    sqlstm.sqadto[1] = (unsigned short )0;
    sqlstm.sqtdso[1] = (unsigned short )0;
    sqlstm.sqhstv[2] = (unsigned char  *)Input_EchoPropertyId;
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



    if( sqlca.sqlcode != 0 )
            return sqlca.sqlcode;

    strcpy( ezechoproperty_ptr->EchoPropertyId, EchoPropertyId );
    ezechoproperty_ptr->EchoInterval = EchoInterval;

    return 0;

}

