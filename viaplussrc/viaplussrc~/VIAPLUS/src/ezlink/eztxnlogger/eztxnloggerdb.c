
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
    "eztxnloggerdb.pc"
};


static unsigned int sqlctx = 5098475;


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
            void  *sqhstv[81];
   unsigned int   sqhstl[81];
            int   sqhsts[81];
            void  *sqindv[81];
            int   sqinds[81];
   unsigned int   sqharm[81];
   unsigned int   *sqharc[81];
   unsigned short  sqadto[81];
   unsigned short  sqtdso[81];
} sqlstm = {12,81};

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
5,0,0,1,1913,0,4,172,0,0,73,1,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,
3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,
2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,
0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,1,0,0,2,5,
0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,1,5,0,0,
312,0,0,2,1502,0,3,757,0,0,81,81,0,1,0,1,5,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
1,5,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,3,
0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,3,0,0,1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,
0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,
651,0,0,3,0,0,29,930,0,0,0,0,0,1,0,
666,0,0,4,1221,0,5,1173,0,0,74,74,0,1,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,
0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,
0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,
977,0,0,5,0,0,29,1253,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <ezlink/ezlnkmsg.h>

int selectEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum, char *I_ChannelName )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		int MsgType;
        int OrgMsgType;
        int TxnCode;
        char TerminalId[ 17 ];
        char TerminalLocation[ 65 ];
        int TraceNo;
        int OrgTraceNo;
        int TranDate;
        int TranTime;
        int OrgTranDate;
        int OrgTranTime;
        int LocalDate;
        int LocalTime;
        int RespCode;
        int RevCode;
        int ReasonCode;
        int AuthCode;
        int CaptureDate;
        int CaptureTime;
        int SettlementDate;
        int AcqCurrencyCode;
        int AcqConvRate;
        int AcqConvDate;
        int IssCurrencyCode;
        int IssConvRate;
        int IssConvDate;
        int SettCurrencyCode;
        int SettConvRate;
        int SettConvDate;
        int MerchantType;
        int PosEntryCode;
        int PosConditionCode;
        int PosCapCode;
        char PosPinCapCode;
        char chn[ 20 ];
        char AcqBranchCode[ 11 ];
        char IssBranchCode[ 11 ];
        char TxfBranchCode[ 11 ];
        char ForwardBranchCode[ 11 ];
        char FromAcctSubType[ 11 ];
        char ToAcctSubType[ 11 ];
		char AvailBalance[ 15 ];
        char LedgerBalance[ 15 ];
        char Amount[ 15 ];
        char TxnFee[ 15 ];
        char DispAmount[ 15 ];
        char FromAccount[ 33 ];
        char ToAccount[ 33 ];
        char RefNum[ 13 ];
        char AuthNum[ 13 ];
        char AcceptorName[ 41 ];
        char AcquirerInst[ 13 ];
        char IssuerInst[ 13 ];
        char ForwardInst[ 13 ];
        char TxfInst[ 13 ];
        char SettInst[ 13 ];
        char NetworkId[ 17 ];
        char AcqNetworkId[ 17 ];
		char IssuerNetworkId[ 17 ];
		char FwdNetworkId[ 17 ];
		char TxfNetworkId[ 17 ];
		char SettNetworkId[ 17 ];
        char Track2[ 40 ];
        char RsvFld1[ 513 ];
        char RsvFld2[ 513 ];
        char RsvFld3[ 51 ];
        char RsvFld4[ 51 ];
        char RsvFld5[ 51 ];
        char RsvFld6[ 51 ];
        char OrgChannel[ 33 ];
        char OrgPort[ 33 ];
        char SrcChannel[ 33 ];
       	short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

    /* EXEC SQL VAR TerminalLocation IS STRING(65); */ 

    /* EXEC SQL VAR chn IS STRING(20); */ 

    /* EXEC SQL VAR AcqBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR IssBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR TxfBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR ForwardBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR FromAcctSubType IS STRING(11); */ 

    /* EXEC SQL VAR ToAcctSubType IS STRING(11); */ 

    /* EXEC SQL VAR AvailBalance IS STRING(15); */ 

    /* EXEC SQL VAR LedgerBalance IS STRING(15); */ 

    /* EXEC SQL VAR Amount IS STRING(15); */ 

    /* EXEC SQL VAR TxnFee IS STRING(15); */ 

    /* EXEC SQL VAR DispAmount IS STRING(15); */ 

    /* EXEC SQL VAR FromAccount IS STRING(33); */ 

    /* EXEC SQL VAR ToAccount IS STRING(33); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR AuthNum IS STRING(13); */ 

    /* EXEC SQL VAR AcceptorName IS STRING(41); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR AcquirerInst IS STRING(13); */ 

    /* EXEC SQL VAR IssuerInst IS STRING(13); */ 

    /* EXEC SQL VAR ForwardInst IS STRING(13); */ 

    /* EXEC SQL VAR TxfInst IS STRING(13); */ 

    /* EXEC SQL VAR SettInst IS STRING(13); */ 

    /* EXEC SQL VAR NetworkId IS STRING(17); */ 

    /* EXEC SQL VAR AcqNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR IssuerNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR FwdNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR TxfNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR SettNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR Track2 IS STRING(40); */ 

    /* EXEC SQL VAR RsvFld1 IS STRING(513); */ 

    /* EXEC SQL VAR RsvFld2 IS STRING(513); */ 

    /* EXEC SQL VAR RsvFld3 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld4 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld5 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld6 IS STRING(51); */ 

    /* EXEC SQL VAR OrgChannel IS STRING(33); */ 

	/* EXEC SQL VAR OrgPort IS STRING(33); */ 

	/* EXEC SQL VAR SrcChannel IS STRING(33); */ 

	
 	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
    memset( chn, 0, sizeof( chn ) );
    memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
    memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
    memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
    memset( TxfBranchCode, 0, sizeof( TxfBranchCode ) );
    memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
    memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
    memset( AvailBalance, 0, sizeof( AvailBalance ) );
    memset( LedgerBalance, 0, sizeof( LedgerBalance ) );
    memset( Amount, 0, sizeof( Amount ) );
    memset( TxnFee, 0, sizeof( TxnFee ) );
    memset( DispAmount, 0, sizeof( DispAmount ) );
    memset( FromAccount, 0, sizeof( FromAccount ) );
    memset( ToAccount, 0, sizeof( ToAccount ) );
    memset( RefNum, 0, sizeof( RefNum ) );
    memset( AuthNum, 0, sizeof( AuthNum ) );
    memset( AcceptorName, 0, sizeof( AcceptorName ) );
    memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
    memset( IssuerInst, 0, sizeof( IssuerInst ) );
    memset( ForwardInst, 0, sizeof( ForwardInst ) );
    memset( TxfInst, 0, sizeof( TxfInst ) );
    memset( SettInst, 0, sizeof( SettInst ) );
    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( AcqNetworkId, 0, sizeof( AcqNetworkId ) );
    memset( IssuerNetworkId, 0, sizeof( IssuerNetworkId ) );
    memset( FwdNetworkId, 0, sizeof( FwdNetworkId ) );
    memset( TxfNetworkId, 0, sizeof( TxfNetworkId ) );
    memset( SettNetworkId, 0, sizeof( SettNetworkId ) );
    memset( Track2, 0, sizeof( Track2 ) );
    memset( RsvFld1, 0, sizeof( RsvFld1 ) );
    memset( RsvFld2, 0, sizeof( RsvFld2 ) );
    memset( RsvFld3, 0, sizeof( RsvFld3 ) );
    memset( RsvFld4, 0, sizeof( RsvFld4 ) );
    memset( RsvFld5, 0, sizeof( RsvFld5 ) );
    memset( RsvFld6, 0, sizeof( RsvFld6 ) );
    memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	memset( SrcChannel, 0, sizeof( SrcChannel ) );
 	
	strcpy( TxnRefNum, I_TxnRefNum );
		
	/* EXEC SQL SELECT
		RTRIM(TXNREFNUM),
		MSGTYPE,
		ORGMSGTYPE,
		TXNCODE,
		RTRIM(TERMINALID),
		RTRIM(TERMLOC),
		TRACENO,
		ORGTRACENO,
		TRANDATE,
		TRANTIME,
		ORGTRANDATE,
		ORGTRANTIME,
		LOCALDATE,
		LOCALTIME,
		RESPCODE,
		REVCODE,
		REASONCODE,
		AUTHCODE,
		CAPTUREDATE,
		CAPTURETIME,
		SETTLEMENTDATE,
		ACQCURRENCYCODE,
		ACQCONVRATE,
		ACQCONVDATE,
		ISSCURRENCYCODE,
		ISSCONVRATE,
		ISSCONVDATE,
		SETTCURRENCYCODE,
		SETTCONVRATE,
		SETTCONVDATE,
		MERCHANTTYPE,
		POSENTRYCODE,
		POSCONDITIONCODE,
		POSCAPCODE,
		POSPINCAPCODE,
		RTRIM(CHN),
		RTRIM(ACQBRANCHCODE),
		RTRIM(ISSBRANCHCODE),
		RTRIM(TXFBRANCHCODE),
		RTRIM(FORWARDBRANCHCODE),
		RTRIM(FROMACCTSUBTYPE),
		RTRIM(TOACCTSUBTYPE),
		RTRIM(AVAILBALANCE),
		RTRIM(LEDGERBALANCE),
		RTRIM(AMOUNT),
		RTRIM(TXNFEE),
		RTRIM(DISPAMOUNT),
		RTRIM(FROMACCOUNT),
		RTRIM(TOACCOUNT),
		RTRIM(REFNUM),
		RTRIM(AUTHNUM),
		RTRIM(ACCEPTORNAME),
		RTRIM(ACQUIRERINST),
		RTRIM(ISSUERINST),
		RTRIM(FORWARDINST),
		RTRIM(TXFINST),
		RTRIM(SETTINST),
		RTRIM(NETWORKID),
		RTRIM(ACQNETWORKID),
		RTRIM(ISSUERNETWORKID),
		RTRIM(FWDNETWORKID),
		RTRIM(TXFNETWORKID),
		RTRIM(SETTNETWORKID),
		RTRIM(TRACK2),
		RTRIM(RSVFLD1),
		RTRIM(RSVFLD2),
		RTRIM(RSVFLD3),
		RTRIM(RSVFLD4),
		RTRIM(RSVFLD5),
		RTRIM(RSVFLD6),
		RTRIM(ORGCHANNEL),
		RTRIM(ORGPORT),
		RTRIM(SRCCHANNEL)
		INTO
		:MsgType:ind_var,
		:OrgMsgType:ind_var,
		:TxnCode:ind_var,
		:TerminalId:ind_var,
		:TerminalLocation:ind_var,
		:TraceNo:ind_var,
		:OrgTraceNo:ind_var,
		:TranDate:ind_var,
		:TranTime:ind_var,
		:OrgTranDate:ind_var,
		:OrgTranTime:ind_var,
		:LocalDate:ind_var,
		:LocalTime:ind_var,
		:RespCode:ind_var,
		:RevCode:ind_var,
		:ReasonCode:ind_var,
		:AuthCode:ind_var,
		:CaptureDate:ind_var,
		:CaptureTime:ind_var,
		:SettlementDate:ind_var,
		:AcqCurrencyCode:ind_var,
		:AcqConvRate:ind_var,
		:AcqConvDate:ind_var,
		:IssCurrencyCode:ind_var,
		:IssConvRate:ind_var,
		:IssConvDate:ind_var,
		:SettCurrencyCode:ind_var,
		:SettConvRate:ind_var,
		:SettConvDate:ind_var,
		:MerchantType:ind_var,
		:PosEntryCode:ind_var,
		:PosConditionCode:ind_var,
		:PosCapCode:ind_var,
		:PosPinCapCode:ind_var,
		:chn:ind_var,
		:AcqBranchCode:ind_var,
		:IssBranchCode:ind_var,
		:TxfBranchCode:ind_var,
		:ForwardBranchCode:ind_var,
		:FromAcctSubType:ind_var,
		:ToAcctSubType:ind_var,
		:AvailBalance:ind_var,
		:LedgerBalance:ind_var,
		:Amount:ind_var,
		:TxnFee:ind_var,
		:DispAmount:ind_var,
		:FromAccount:ind_var,
		:ToAccount:ind_var,
		:RefNum:ind_var,
		:AuthNum:ind_var,
		:AcceptorName:ind_var,
		:AcquirerInst:ind_var,
		:IssuerInst:ind_var,
		:ForwardInst:ind_var,
		:TxfInst:ind_var,
		:SettInst:ind_var,
		:NetworkId:ind_var,
		:AcqNetworkId:ind_var,
		:IssuerNetworkId:ind_var,
		:FwdNetworkId:ind_var,
		:TxfNetworkId:ind_var,
		:SettNetworkId:ind_var,
		:Track2:ind_var,
		:RsvFld1:ind_var,
		:RsvFld2:ind_var,
		:RsvFld3:ind_var,
		:RsvFld4:ind_var,
		:RsvFld5:ind_var,
		:RsvFld6:ind_var,
		:OrgChannel:ind_var,
		:OrgPort:ind_var,
		:SrcChannel:ind_var
	FROM EZTXNLOG WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 73;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "select RTRIM(TXNREFNUM) ,MSGTYPE ,ORGMSGTYPE ,TXNCODE ,RTRIM(TERMINALID)\
 ,RTRIM(TERMLOC) ,TRACENO ,ORGTRACENO ,TRANDATE ,TRANTIME ,ORGTRANDATE ,ORGT\
RANTIME ,LOCALDATE ,LOCALTIME ,RESPCODE ,REVCODE ,REASONCODE ,AUTHCODE ,CAPT\
UREDATE ,CAPTURETIME ,SETTLEMENTDATE ,ACQCURRENCYCODE ,ACQCONVRATE ,ACQCONVD\
ATE ,ISSCURRENCYCODE ,ISSCONVRATE ,ISSCONVDATE ,SETTCURRENCYCODE ,SETTCONVRA\
TE ,SETTCONVDATE ,MERCHANTTYPE ,POSENTRYCODE ,POSCONDITIONCODE ,POSCAPCODE ,\
POSPINCAPCODE ,RTRIM(CHN) ,RTRIM(ACQBRANCHCODE) ,RTRIM(ISSBRANCHCODE) ,RTRIM\
(TXFBRANCHCODE) ,RTRIM(FORWARDBRANCHCODE) ,RTRIM(FROMACCTSUBTYPE) ,RTRIM(TOA\
CCTSUBTYPE) ,RTRIM(AVAILBALANCE) ,RTRIM(LEDGERBALANCE) ,RTRIM(AMOUNT) ,RTRIM\
(TXNFEE) ,RTRIM(DISPAMOUNT) ,RTRIM(FROMACCOUNT) ,RTRIM(TOACCOUNT) ,RTRIM(REF\
NUM) ,RTRIM(AUTHNUM) ,RTRIM(ACCEPTORNAME) ,RTRIM(ACQUIRERINST) ,RTRIM(ISSUER\
INST) ,RTRIM(FORWARDINST) ,RTRIM(TXFINST) ,RTRIM(SETTINST) ,RTRIM(NETWORKID)\
 ,RTRIM(ACQNETWORKID) ,RTRIM(ISSUERNETWORKID) ,RTRIM(FWDNETWORKID) ,RTRIM(TX\
FNETWORKID) ,RTRIM(SETTNETWORKID) ,RTRIM");
 sqlstm.stmt = "(TRACK2) ,RTRIM(RSVFLD1) ,RTRIM(RSVFLD2) ,RTRIM(RSVFLD3) ,RT\
RIM(RSVFLD4) ,RTRIM(RSVFLD5) ,RTRIM(RSVFLD6) ,RTRIM(ORGCHANNEL) ,RTRIM(ORGPORT\
) ,RTRIM(SRCCHANNEL) into :b0:b1,:b2:b3,:b4:b5,:b6:b7,:b8:b9,:b10:b11,:b12:b13\
,:b14:b15,:b16:b17,:b18:b19,:b20:b21,:b22:b23,:b24:b25,:b26:b27,:b28:b29,:b30:\
b31,:b32:b33,:b34:b35,:b36:b37,:b38:b39,:b40:b41,:b42:b43,:b44:b45,:b46:b47,:b\
48:b49,:b50:b51,:b52:b53,:b54:b55,:b56:b57,:b58:b59,:b60:b61,:b62:b63,:b64:b65\
,:b66:b67,:b68:b69,:b70:b71,:b72:b73,:b74:b75,:b76:b77,:b78:b79,:b80:b81,:b82:\
b83,:b84:b85,:b86:b87,:b88:b89,:b90:b91,:b92:b93,:b94:b95,:b96:b97,:b98:b99,:b\
100:b101,:b102:b103,:b104:b105,:b106:b107,:b108:b109,:b110:b111,:b112:b113,:b1\
14:b115,:b116:b117,:b118:b119,:b120:b121,:b122:b123,:b124:b125,:b126:b127,:b12\
8:b129,:b130:b131,:b132:b133,:b134:b135,:b136:b137,:b138:b139,:b140:b141,:b142\
:b143  from EZTXNLOG where RTRIM(TXNREFNUM)=:b144";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&MsgType;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)&ind_var;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&OrgMsgType;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)&ind_var;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&TxnCode;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TerminalId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)&ind_var;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TerminalLocation;
 sqlstm.sqhstl[4] = (unsigned int  )65;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&TraceNo;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)&ind_var;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&OrgTraceNo;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)&ind_var;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&TranDate;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)&ind_var;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&TranTime;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)&ind_var;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&OrgTranDate;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)&ind_var;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&OrgTranTime;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)&ind_var;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&LocalDate;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)&ind_var;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&LocalTime;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)&ind_var;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&RespCode;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)&ind_var;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&RevCode;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)&ind_var;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&ReasonCode;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)&ind_var;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&AuthCode;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)&ind_var;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)&ind_var;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)&ind_var;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)&ind_var;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)&ind_var;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)&ind_var;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)&ind_var;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)&ind_var;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)&ind_var;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)&ind_var;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)&ind_var;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)&ind_var;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)&ind_var;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&MerchantType;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)&ind_var;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)&ind_var;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[31] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)&ind_var;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[32] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)&ind_var;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[33] = (unsigned int  )1;
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)&ind_var;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)chn;
 sqlstm.sqhstl[34] = (unsigned int  )20;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)&ind_var;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[35] = (unsigned int  )11;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)&ind_var;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[36] = (unsigned int  )11;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)&ind_var;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)TxfBranchCode;
 sqlstm.sqhstl[37] = (unsigned int  )11;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)&ind_var;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[38] = (unsigned int  )11;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)&ind_var;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[39] = (unsigned int  )11;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)&ind_var;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)ToAcctSubType;
 sqlstm.sqhstl[40] = (unsigned int  )11;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)&ind_var;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)AvailBalance;
 sqlstm.sqhstl[41] = (unsigned int  )15;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)&ind_var;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[42] = (unsigned int  )15;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)&ind_var;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)Amount;
 sqlstm.sqhstl[43] = (unsigned int  )15;
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)&ind_var;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)TxnFee;
 sqlstm.sqhstl[44] = (unsigned int  )15;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)&ind_var;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)DispAmount;
 sqlstm.sqhstl[45] = (unsigned int  )15;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)&ind_var;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)FromAccount;
 sqlstm.sqhstl[46] = (unsigned int  )33;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)&ind_var;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)ToAccount;
 sqlstm.sqhstl[47] = (unsigned int  )33;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)&ind_var;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)RefNum;
 sqlstm.sqhstl[48] = (unsigned int  )13;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)&ind_var;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)AuthNum;
 sqlstm.sqhstl[49] = (unsigned int  )13;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)&ind_var;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)AcceptorName;
 sqlstm.sqhstl[50] = (unsigned int  )41;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)&ind_var;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
 sqlstm.sqhstv[51] = (         void  *)AcquirerInst;
 sqlstm.sqhstl[51] = (unsigned int  )13;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)&ind_var;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)IssuerInst;
 sqlstm.sqhstl[52] = (unsigned int  )13;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)&ind_var;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)ForwardInst;
 sqlstm.sqhstl[53] = (unsigned int  )13;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)&ind_var;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)TxfInst;
 sqlstm.sqhstl[54] = (unsigned int  )13;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)&ind_var;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)SettInst;
 sqlstm.sqhstl[55] = (unsigned int  )13;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)&ind_var;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)NetworkId;
 sqlstm.sqhstl[56] = (unsigned int  )17;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)&ind_var;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)AcqNetworkId;
 sqlstm.sqhstl[57] = (unsigned int  )17;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)&ind_var;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)IssuerNetworkId;
 sqlstm.sqhstl[58] = (unsigned int  )17;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)&ind_var;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)FwdNetworkId;
 sqlstm.sqhstl[59] = (unsigned int  )17;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)&ind_var;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)TxfNetworkId;
 sqlstm.sqhstl[60] = (unsigned int  )17;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)&ind_var;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)SettNetworkId;
 sqlstm.sqhstl[61] = (unsigned int  )17;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)&ind_var;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)Track2;
 sqlstm.sqhstl[62] = (unsigned int  )40;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)&ind_var;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)RsvFld1;
 sqlstm.sqhstl[63] = (unsigned int  )513;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)&ind_var;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)RsvFld2;
 sqlstm.sqhstl[64] = (unsigned int  )513;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)&ind_var;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)RsvFld3;
 sqlstm.sqhstl[65] = (unsigned int  )51;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)&ind_var;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
 sqlstm.sqhstv[66] = (         void  *)RsvFld4;
 sqlstm.sqhstl[66] = (unsigned int  )51;
 sqlstm.sqhsts[66] = (         int  )0;
 sqlstm.sqindv[66] = (         void  *)&ind_var;
 sqlstm.sqinds[66] = (         int  )0;
 sqlstm.sqharm[66] = (unsigned int  )0;
 sqlstm.sqadto[66] = (unsigned short )0;
 sqlstm.sqtdso[66] = (unsigned short )0;
 sqlstm.sqhstv[67] = (         void  *)RsvFld5;
 sqlstm.sqhstl[67] = (unsigned int  )51;
 sqlstm.sqhsts[67] = (         int  )0;
 sqlstm.sqindv[67] = (         void  *)&ind_var;
 sqlstm.sqinds[67] = (         int  )0;
 sqlstm.sqharm[67] = (unsigned int  )0;
 sqlstm.sqadto[67] = (unsigned short )0;
 sqlstm.sqtdso[67] = (unsigned short )0;
 sqlstm.sqhstv[68] = (         void  *)RsvFld6;
 sqlstm.sqhstl[68] = (unsigned int  )51;
 sqlstm.sqhsts[68] = (         int  )0;
 sqlstm.sqindv[68] = (         void  *)&ind_var;
 sqlstm.sqinds[68] = (         int  )0;
 sqlstm.sqharm[68] = (unsigned int  )0;
 sqlstm.sqadto[68] = (unsigned short )0;
 sqlstm.sqtdso[68] = (unsigned short )0;
 sqlstm.sqhstv[69] = (         void  *)OrgChannel;
 sqlstm.sqhstl[69] = (unsigned int  )33;
 sqlstm.sqhsts[69] = (         int  )0;
 sqlstm.sqindv[69] = (         void  *)&ind_var;
 sqlstm.sqinds[69] = (         int  )0;
 sqlstm.sqharm[69] = (unsigned int  )0;
 sqlstm.sqadto[69] = (unsigned short )0;
 sqlstm.sqtdso[69] = (unsigned short )0;
 sqlstm.sqhstv[70] = (         void  *)OrgPort;
 sqlstm.sqhstl[70] = (unsigned int  )33;
 sqlstm.sqhsts[70] = (         int  )0;
 sqlstm.sqindv[70] = (         void  *)&ind_var;
 sqlstm.sqinds[70] = (         int  )0;
 sqlstm.sqharm[70] = (unsigned int  )0;
 sqlstm.sqadto[70] = (unsigned short )0;
 sqlstm.sqtdso[70] = (unsigned short )0;
 sqlstm.sqhstv[71] = (         void  *)SrcChannel;
 sqlstm.sqhstl[71] = (unsigned int  )33;
 sqlstm.sqhsts[71] = (         int  )0;
 sqlstm.sqindv[71] = (         void  *)&ind_var;
 sqlstm.sqinds[71] = (         int  )0;
 sqlstm.sqharm[71] = (unsigned int  )0;
 sqlstm.sqadto[71] = (unsigned short )0;
 sqlstm.sqtdso[71] = (unsigned short )0;
 sqlstm.sqhstv[72] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[72] = (unsigned int  )151;
 sqlstm.sqhsts[72] = (         int  )0;
 sqlstm.sqindv[72] = (         void  *)0;
 sqlstm.sqinds[72] = (         int  )0;
 sqlstm.sqharm[72] = (unsigned int  )0;
 sqlstm.sqadto[72] = (unsigned short )0;
 sqlstm.sqtdso[72] = (unsigned short )0;
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
	
	txnmsg->MsgType = MsgType;
	txnmsg->OrgMsgType = OrgMsgType;
	txnmsg->TxnCode = TxnCode;
	memset( txnmsg->TerminalId, 0, sizeof( txnmsg->TerminalId ) );
	strcpy( txnmsg->TerminalId, TerminalId );
	memset( txnmsg->TerminalLocation, 0, sizeof( txnmsg->TerminalLocation ) );
	strcpy( txnmsg->TerminalLocation, TerminalLocation );
	txnmsg->TraceNo = TraceNo;
	txnmsg->OrgTraceNo = OrgTraceNo;
	txnmsg->TranDate = TranDate;	 
	txnmsg->TranTime = TranTime;
	txnmsg->OrgTranDate = OrgTranDate;
	txnmsg->OrgTranTime = OrgTranTime;
	txnmsg->LocalDate = LocalDate;
	txnmsg->LocalTime = LocalTime;
	txnmsg->RespCode = RespCode;
	txnmsg->RevCode = RevCode;
	txnmsg->AuthCode = AuthCode;
	txnmsg->ReasonCode = ReasonCode;
	txnmsg->CaptureDate = CaptureDate;
	txnmsg->CaptureTime = CaptureTime;
	txnmsg->SettlementDate = SettlementDate;
	txnmsg->AcqCurrencyCode = AcqCurrencyCode;
	txnmsg->IssCurrencyCode = IssCurrencyCode;
	txnmsg->SettCurrencyCode = SettCurrencyCode;
	txnmsg->AcqConvRate = AcqConvRate;
	txnmsg->AcqConvDate = AcqConvDate;
	txnmsg->IssConvRate = IssConvRate;
	txnmsg->IssConvDate = IssConvDate;
	txnmsg->SettConvRate = SettConvRate;
	txnmsg->SettConvDate = SettConvDate;
	txnmsg->MerchantType = MerchantType;
	txnmsg->PosEntryCode = PosEntryCode;
	txnmsg->PosConditionCode = PosConditionCode;
	txnmsg->PosCapCode = PosCapCode;
	txnmsg->PosPinCapCode = PosPinCapCode;
	memset( txnmsg->AcqBranchCode, 0, sizeof( txnmsg->AcqBranchCode ) );
	strcpy( txnmsg->AcqBranchCode, AcqBranchCode );
	memset( txnmsg->IssBranchCode, 0, sizeof( txnmsg->IssBranchCode ) );
	strcpy( txnmsg->IssBranchCode, IssBranchCode );
	memset( txnmsg->TxfBranchCode, 0, sizeof( txnmsg->TxfBranchCode ) );
	strcpy( txnmsg->TxfBranchCode, TxfBranchCode );
	memset( txnmsg->ForwardBranchCode, 0, sizeof( txnmsg->ForwardBranchCode ) );
	strcpy( txnmsg->ForwardBranchCode,ForwardBranchCode );
	memset( txnmsg->FromAcctSubType, 0, sizeof( txnmsg->FromAcctSubType ) );
	strcpy( txnmsg->FromAcctSubType, FromAcctSubType );
	memset( txnmsg->ToAcctSubType, 0, sizeof( txnmsg->ToAcctSubType ) );
	strcpy( txnmsg->ToAcctSubType, ToAcctSubType );
	memset( txnmsg->AvailBalance, 0, sizeof( txnmsg->AvailBalance ) );
	strcpy( txnmsg->AvailBalance, AvailBalance );
	memset( txnmsg->LedgerBalance, 0, sizeof( txnmsg->LedgerBalance ) );
	strcpy( txnmsg->LedgerBalance, LedgerBalance );
	memset( txnmsg->Amount, 0, sizeof( txnmsg->Amount ) );
	strcpy( txnmsg->Amount, Amount );
	memset( txnmsg->TxnFee, 0, sizeof( txnmsg->TxnFee ) );
	strcpy( txnmsg->TxnFee, TxnFee );
	memset( txnmsg->DispAmount, 0, sizeof( txnmsg->DispAmount ) );
	strcpy( txnmsg->DispAmount, DispAmount );
	memset( txnmsg->FromAccount, 0, sizeof( txnmsg->FromAccount ) );
	strcpy( txnmsg->FromAccount, FromAccount );
	memset( txnmsg->ToAccount, 0, sizeof( txnmsg->ToAccount ) );
	strcpy( txnmsg->ToAccount, ToAccount );
	memset( txnmsg->RefNum, 0, sizeof( txnmsg->RefNum ) );
	strcpy( txnmsg->RefNum, RefNum );
	memset( txnmsg->AuthNum, 0, sizeof( txnmsg->AuthNum ) );
	strcpy( txnmsg->AuthNum, AuthNum );
	memset( txnmsg->AcceptorName, 0, sizeof( txnmsg->AcceptorName ) );
	strcpy( txnmsg->AcceptorName, AcceptorName );
	memset( txnmsg->AcquirerInst, 0, sizeof( txnmsg->AcquirerInst ) );
	strcpy( txnmsg->AcquirerInst, AcquirerInst );
	memset( txnmsg->IssuerInst, 0, sizeof( txnmsg->IssuerInst ) );
	strcpy( txnmsg->IssuerInst, IssuerInst );
	memset( txnmsg->ForwardInst, 0, sizeof( txnmsg->ForwardInst ) );
	strcpy( txnmsg->ForwardInst, ForwardInst );
	memset( txnmsg->TxfInst, 0, sizeof( txnmsg->TxfInst ) );
	strcpy( txnmsg->TxfInst, TxfInst );
	memset( txnmsg->SettInst, 0, sizeof( txnmsg->SettInst ) );
	strcpy( txnmsg->SettInst, SettInst );
	memset( txnmsg->NetworkId, 0, sizeof( txnmsg->NetworkId ) );
	strcpy( txnmsg->NetworkId, NetworkId );
	memset( txnmsg->AcqNetworkId, 0, sizeof( txnmsg->AcqNetworkId ) );
	strcpy( txnmsg->AcqNetworkId, AcqNetworkId );
	memset( txnmsg->IssuerNetworkId, 0, sizeof( txnmsg->IssuerNetworkId ) );
	strcpy( txnmsg->IssuerNetworkId, IssuerNetworkId );
	memset( txnmsg->FwdNetworkId, 0, sizeof( txnmsg->FwdNetworkId ) );
	strcpy( txnmsg->FwdNetworkId, FwdNetworkId );
	memset( txnmsg->TxfNetworkId, 0, sizeof( txnmsg->TxfNetworkId ) );
	strcpy( txnmsg->TxfNetworkId, TxfNetworkId );
	memset( txnmsg->SettNetworkId, 0, sizeof( txnmsg->SettNetworkId ) );
	strcpy( txnmsg->SettNetworkId, SettNetworkId );
	memset( txnmsg->Track2, 0, sizeof( txnmsg->Track2 ) );
	strcpy( txnmsg->Track2, Track2 );
	memset( txnmsg->RsvFld1, 0, sizeof( txnmsg->RsvFld1 ) );
	strcpy( txnmsg->RsvFld1, RsvFld1 );
	memset( txnmsg->RsvFld2, 0, sizeof( txnmsg->RsvFld2 ) );
	strcpy( txnmsg->RsvFld2, RsvFld2 );
	memset( txnmsg->RsvFld3, 0, sizeof( txnmsg->RsvFld3 ) );
	strcpy( txnmsg->RsvFld3, RsvFld3 );
	memset( txnmsg->RsvFld4, 0, sizeof( txnmsg->RsvFld4 ) );
	strcpy( txnmsg->RsvFld4, RsvFld4 );
	memset( txnmsg->RsvFld5, 0, sizeof( txnmsg->RsvFld5 ) );
	strcpy( txnmsg->RsvFld5, RsvFld5 );
	memset( txnmsg->RsvFld6, 0, sizeof( txnmsg->RsvFld6 ) );
	strcpy( txnmsg->RsvFld6, RsvFld6 );
	memset( txnmsg->OrgChannel, 0, sizeof( txnmsg->OrgChannel ) );
	strcpy( txnmsg->OrgChannel, OrgChannel );
	memset( txnmsg->OrgPort, 0, sizeof( txnmsg->OrgPort ) );
	strcpy( txnmsg->OrgPort, OrgPort );
	strcpy( I_ChannelName, SrcChannel );
	
	return 0;
}

int insertEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum, const char *I_SrcChannelName, const char *I_DestChannelName, short I_RefSeqNo )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char DeviceType[ 17 ];
		int MsgType;
        int OrgMsgType;
        int TxnCode;
        char TerminalId[ 17 ];
        char TerminalLocation[ 65 ];
        int TraceNo;
        int OrgTraceNo;
        char TranDate[ 7 ];
        int TranTime;
        char OrgTranDate[ 7 ];
        int OrgTranTime;
        char LocalDate[ 7 ];
        int LocalTime;
        int RespCode;
        int RevCode;
        int ReasonCode;
        int AuthCode;
        char CaptureDate[ 7 ];
        int CaptureTime;
        char SettlementDate[ 7 ];
        char BusinessDate[ 7 ];
        int AcqCurrencyCode;
        int AcqConvRate;
        char AcqConvDate[ 7 ];
        int IssCurrencyCode;
        int IssConvRate;
        char IssConvDate[ 7 ];
        int SettCurrencyCode;
        int SettConvRate;
        char SettConvDate[ 7 ];
        int MerchantType;
        int PosEntryCode;
        int PosConditionCode;
        int PosCapCode;
        char PosPinCapCode;
        char chn[ 20 ];
        char t_chn[ 129 ];
        char AcqBranchCode[ 11 ];
        char IssBranchCode[ 11 ];
        char TxfBranchCode[ 11 ];
        char ForwardBranchCode[ 11 ];
        char FromAcctSubType[ 11 ];
        char ToAcctSubType[ 11 ];
		char AvailBalance[ 15 ];
        char LedgerBalance[ 15 ];
        char Amount[ 15 ];
        char TxnFee[ 15 ];
        char DispAmount[ 15 ];
        char FromAccount[ 33 ];
        char ToAccount[ 33 ];
        char RefNum[ 13 ];
        char AuthNum[ 13 ];
        char BatchId[ 13 ];
        char AcceptorId[ 33 ];
        char AcceptorName[ 41 ];
        char AcquirerInst[ 13 ];
        char IssuerInst[ 13 ];
        char ForwardInst[ 13 ];
        char TxfInst[ 13 ];
        char SettInst[ 13 ];
        char NetworkId[ 17 ];
        char AcqNetworkId[ 17 ];
		char IssuerNetworkId[ 17 ];
		char FwdNetworkId[ 17 ];
		char TxfNetworkId[ 17 ];
		char SettNetworkId[ 17 ];
        char RsvFld1[ 513 ];
        char RsvFld2[ 513 ];
        char RsvFld3[ 51 ];
        char RsvFld4[ 51 ];
        char RsvFld5[ 51 ];
        char RsvFld6[ 51 ];
        char OrgChannel[ 33 ];
        char OrgPort[ 33 ];
        char SrcChannel[ 33 ];
        char DestChannel[ 33 ];
        char SrcPort[ 33 ];
        char DestPort[ 33 ];
        int RefSeqNo;
       	short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR DeviceType IS STRING(17); */ 

	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

    /* EXEC SQL VAR TerminalLocation IS STRING(65); */ 

    /* EXEC SQL VAR TranDate IS STRING(7); */ 

    /* EXEC SQL VAR OrgTranDate IS STRING(7); */ 

    /* EXEC SQL VAR LocalDate IS STRING(7); */ 

    /* EXEC SQL VAR CaptureDate IS STRING(7); */ 

    /* EXEC SQL VAR SettlementDate IS STRING(7); */ 

    /* EXEC SQL VAR BusinessDate IS STRING(7); */ 

    /* EXEC SQL VAR AcqConvDate IS STRING(7); */ 

    /* EXEC SQL VAR IssConvDate IS STRING(7); */ 

    /* EXEC SQL VAR SettConvDate IS STRING(7); */ 

    /* EXEC SQL VAR chn IS STRING(20); */ 

    /* EXEC SQL VAR t_chn IS STRING(129); */ 

    /* EXEC SQL VAR AcqBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR IssBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR TxfBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR ForwardBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR FromAcctSubType IS STRING(11); */ 

    /* EXEC SQL VAR ToAcctSubType IS STRING(11); */ 

    /* EXEC SQL VAR AvailBalance IS STRING(15); */ 

    /* EXEC SQL VAR LedgerBalance IS STRING(15); */ 

    /* EXEC SQL VAR Amount IS STRING(15); */ 

    /* EXEC SQL VAR TxnFee IS STRING(15); */ 

    /* EXEC SQL VAR DispAmount IS STRING(15); */ 

    /* EXEC SQL VAR FromAccount IS STRING(33); */ 

    /* EXEC SQL VAR ToAccount IS STRING(33); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR AuthNum IS STRING(13); */ 

    /* EXEC SQL VAR BatchId IS STRING(13); */ 

    /* EXEC SQL VAR AcceptorId IS STRING(33); */ 

    /* EXEC SQL VAR AcceptorName IS STRING(41); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR AcquirerInst IS STRING(13); */ 

    /* EXEC SQL VAR IssuerInst IS STRING(13); */ 

    /* EXEC SQL VAR ForwardInst IS STRING(13); */ 

    /* EXEC SQL VAR TxfInst IS STRING(13); */ 

    /* EXEC SQL VAR SettInst IS STRING(13); */ 

    /* EXEC SQL VAR NetworkId IS STRING(17); */ 

    /* EXEC SQL VAR AcqNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR IssuerNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR FwdNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR TxfNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR SettNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR RsvFld1 IS STRING(513); */ 

    /* EXEC SQL VAR RsvFld2 IS STRING(513); */ 

    /* EXEC SQL VAR RsvFld3 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld4 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld5 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld6 IS STRING(51); */ 

    /* EXEC SQL VAR OrgChannel IS STRING(33); */ 

    /* EXEC SQL VAR OrgPort IS STRING(33); */ 

	/* EXEC SQL VAR SrcChannel IS STRING(33); */ 

	/* EXEC SQL VAR DestChannel IS STRING(33); */ 

	/* EXEC SQL VAR SrcPort IS STRING(33); */ 

	/* EXEC SQL VAR DestPort IS STRING(33); */ 

	
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( DeviceType, 0, sizeof( DeviceType ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
    memset( TranDate, 0, sizeof( TranDate ) );
    memset( OrgTranDate, 0, sizeof( OrgTranDate ) );
    memset( LocalDate, 0, sizeof( LocalDate ) ); 
    memset( CaptureDate, 0, sizeof( CaptureDate ) );
    memset( SettlementDate, 0, sizeof( SettlementDate ) );
    memset( BusinessDate, 0, sizeof( BusinessDate ) );
    memset( AcqConvDate, 0, sizeof( AcqConvDate ) );
    memset( IssConvDate, 0, sizeof( IssConvDate ) );
    memset( SettConvDate, 0, sizeof( SettConvDate ) );
    memset( chn, 0, sizeof( chn ) );
    memset( t_chn, 0, sizeof( t_chn ) );
    memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
    memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
    memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
    memset( TxfBranchCode, 0, sizeof( TxfBranchCode ) );
    memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
    memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
    memset( AvailBalance, 0, sizeof( AvailBalance ) );
    memset( LedgerBalance, 0, sizeof( LedgerBalance ) );
    memset( Amount, 0, sizeof( Amount ) );
    memset( TxnFee, 0, sizeof( TxnFee ) );
    memset( DispAmount, 0, sizeof( DispAmount ) );
    memset( FromAccount, 0, sizeof( FromAccount ) );
    memset( ToAccount, 0, sizeof( ToAccount ) );
    memset( RefNum, 0, sizeof( RefNum ) );
    memset( AuthNum, 0, sizeof( AuthNum ) );
    memset( BatchId, 0, sizeof( BatchId ) );
    memset( AcceptorId, 0, sizeof( AcceptorId ) );
    memset( AcceptorName, 0, sizeof( AcceptorName ) );
    memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
    memset( IssuerInst, 0, sizeof( IssuerInst ) );
    memset( ForwardInst, 0, sizeof( ForwardInst ) );
    memset( TxfInst, 0, sizeof( TxfInst ) );
    memset( SettInst, 0, sizeof( SettInst ) );
    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( AcqNetworkId, 0, sizeof( AcqNetworkId ) );
    memset( IssuerNetworkId, 0, sizeof( IssuerNetworkId ) );
    memset( FwdNetworkId, 0, sizeof( FwdNetworkId ) );
    memset( TxfNetworkId, 0, sizeof( TxfNetworkId ) );
    memset( SettNetworkId, 0, sizeof( SettNetworkId ) );
    memset( RsvFld1, 0, sizeof( RsvFld1 ) );
    memset( RsvFld2, 0, sizeof( RsvFld2 ) );
    memset( RsvFld3, 0, sizeof( RsvFld3 ) );
    memset( RsvFld4, 0, sizeof( RsvFld4 ) );
    memset( RsvFld5, 0, sizeof( RsvFld5 ) );
    memset( RsvFld6, 0, sizeof( RsvFld6 ) );
    memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	memset( SrcChannel, 0, sizeof( SrcChannel ) );
	memset( DestChannel, 0, sizeof( DestChannel ) );
	memset( SrcPort, 0, sizeof( SrcPort ) );
	memset( DestPort, 0, sizeof( DestPort ) );
	
	strcpy( TxnRefNum, I_TxnRefNum );
	strcpy( DeviceType, txnmsg->DeviceType );
	MsgType = txnmsg->MsgType;
    OrgMsgType = txnmsg->OrgMsgType;
    TxnCode = txnmsg->TxnCode;
    strcpy( TerminalId, txnmsg->TerminalId );
    strcpy( TerminalLocation, txnmsg->TerminalLocation );
    TraceNo = txnmsg->TraceNo;
    OrgTraceNo = txnmsg->OrgTraceNo;
    sprintf( TranDate, "%06d", txnmsg->TranDate );
    TranTime = txnmsg->TranTime;
    
    if( !txnmsg->OrgTranDate )
    	sprintf( OrgTranDate, "%06d", txnmsg->TranDate );
    else
    	sprintf( OrgTranDate, "%06d", txnmsg->OrgTranDate );
    	
    OrgTranTime = txnmsg->OrgTranTime;
    sprintf( LocalDate, "%06d", txnmsg->LocalDate );
    LocalTime = txnmsg->LocalTime;
    RespCode = txnmsg->RespCode;
    RevCode = txnmsg->RevCode;
    ReasonCode = txnmsg->ReasonCode;
    AuthCode = txnmsg->AuthCode;
    
    if( !txnmsg->CaptureDate )
    	sprintf( CaptureDate, "%06d", txnmsg->LocalDate );
    else
    	sprintf( CaptureDate, "%06d", txnmsg->CaptureDate );
    CaptureTime = txnmsg->CaptureTime;
    if( !txnmsg->SettlementDate )
    	sprintf( SettlementDate, "%06d", txnmsg->LocalDate );
    else
    	sprintf( SettlementDate, "%06d", txnmsg->SettlementDate );
    	
	if( !txnmsg->BusinessDate )
		sprintf( BusinessDate, "%06d", txnmsg->LocalDate );
	else
		sprintf( BusinessDate, "%06d", txnmsg->BusinessDate );
    	
    AcqCurrencyCode = txnmsg->AcqCurrencyCode;
    AcqConvRate = txnmsg->AcqConvRate;
    
    if( !txnmsg->AcqConvDate )
    	sprintf( AcqConvDate, "%06d", txnmsg->LocalDate );
    else
    	sprintf( AcqConvDate, "%06d", txnmsg->AcqConvDate );
    	
    IssCurrencyCode = txnmsg->IssCurrencyCode;
    IssConvRate = txnmsg->IssConvRate;
    
    if( !txnmsg->IssConvDate )
    	sprintf( IssConvDate, "%06d", txnmsg->LocalDate );
    else
    	sprintf( IssConvDate, "%06d", txnmsg->IssConvDate );
    	
    SettCurrencyCode = txnmsg->SettCurrencyCode;
    SettConvRate = txnmsg->SettConvRate;
    
    if( !txnmsg->SettConvDate )
    	sprintf( SettConvDate, "%06d", txnmsg->LocalDate );
    else
    	sprintf( SettConvDate, "%06d", txnmsg->SettConvDate );
    	
    MerchantType = txnmsg->MerchantType;
    PosEntryCode = txnmsg->PosEntryCode;
    PosConditionCode = txnmsg->PosConditionCode;
    PosCapCode = txnmsg->PosCapCode;
    PosPinCapCode = txnmsg->PosPinCapCode;
    strcpy( chn, txnmsg->m_chn );
    if( !strlen( txnmsg->t_chn ) )
    	strcpy( t_chn, txnmsg->m_chn );
    else
    	strcpy( t_chn, txnmsg->t_chn );
    strcpy( AcqBranchCode, txnmsg->AcqBranchCode );
    strcpy( IssBranchCode, txnmsg->IssBranchCode );
    strcpy( ForwardBranchCode, txnmsg->ForwardBranchCode );
    strcpy( TxfBranchCode, txnmsg->TxfBranchCode );
	strcpy( FromAcctSubType, txnmsg->FromAcctSubType );
    strcpy( ToAcctSubType, txnmsg->ToAcctSubType );
    strcpy( AvailBalance, txnmsg->AvailBalance );
    strcpy( LedgerBalance, txnmsg->LedgerBalance );
    strcpy( Amount, txnmsg->Amount );
    strcpy( TxnFee, txnmsg->TxnFee );
    strcpy( DispAmount, txnmsg->DispAmount );
    strcpy( FromAccount, txnmsg->FromAccount );
    strcpy( ToAccount, txnmsg->ToAccount );
    strcpy( RefNum, txnmsg->RefNum );
    strcpy( AuthNum, txnmsg->AuthNum );
    strcpy( BatchId, txnmsg->BatchId );
    strcpy( AcceptorId, txnmsg->AcceptorId );
    strcpy( AcceptorName, txnmsg->AcceptorName );
    strcpy( AcquirerInst, txnmsg->AcquirerInst );
    strcpy( IssuerInst, txnmsg->IssuerInst );
    strcpy( ForwardInst, txnmsg->ForwardInst );
    strcpy( TxfInst, txnmsg->TxfInst );
    strcpy( SettInst, txnmsg->SettInst );
    strcpy( NetworkId, txnmsg->NetworkId );
    strcpy( AcqNetworkId, txnmsg->AcqNetworkId );
    strcpy( IssuerNetworkId, txnmsg->IssuerNetworkId );
    strcpy( FwdNetworkId, txnmsg->FwdNetworkId );
    strcpy( TxfNetworkId, txnmsg->TxfNetworkId );
    strcpy( SettNetworkId, txnmsg->SettNetworkId );
    strcpy( RsvFld1, txnmsg->RsvFld1 );
    strcpy( RsvFld2, txnmsg->RsvFld2 );
    strcpy( RsvFld3, txnmsg->RsvFld3 );
    strcpy( RsvFld4, txnmsg->RsvFld4 );
    strcpy( RsvFld5, txnmsg->RsvFld5 );
    strcpy( RsvFld6, txnmsg->RsvFld6 );
   	strcpy( OrgChannel, txnmsg->OrgChannel );
	strcpy( OrgPort, txnmsg->OrgPort );
	strcpy( SrcChannel, I_SrcChannelName );
	strcpy( DestChannel, I_DestChannelName );
	strcpy( SrcPort, txnmsg->SrcPort );
	strcpy( DestPort, txnmsg->DestPort );
	
	RefSeqNo = I_RefSeqNo;
	
	/* EXEC SQL INSERT INTO EZTXNLOG
	(
		TXNREFNUM,
		DEVICETYPE,
		MSGTYPE,
		ORGMSGTYPE,
		TXNCODE,
		TERMINALID,
		TERMLOC,
		TRACENO,
		ORGTRACENO,
		TRANDATE,
		TRANTIME,
		ORGTRANDATE,
		ORGTRANTIME,
		LOCALDATE,
		LOCALTIME,
		RESPCODE,
		REVCODE,
		REASONCODE,
		AUTHCODE,
		CAPTUREDATE,
		CAPTURETIME,
		SETTLEMENTDATE,
		BUSINESSDATE,
		ACQCURRENCYCODE,
		ACQCONVRATE,
		ACQCONVDATE,
		ISSCURRENCYCODE,
		ISSCONVRATE,
		ISSCONVDATE,
		SETTCURRENCYCODE,
		SETTCONVRATE,
		SETTCONVDATE,
		MERCHANTTYPE,
		POSENTRYCODE,
		POSCONDITIONCODE,
		POSCAPCODE,
		POSPINCAPCODE,
		CHN,
		TCHN,
		ACQBRANCHCODE,
		ISSBRANCHCODE,
		TXFBRANCHCODE,
		FORWARDBRANCHCODE,
		FROMACCTSUBTYPE,
		TOACCTSUBTYPE,
		AVAILBALANCE,
		LEDGERBALANCE,
		AMOUNT,
		TXNFEE,
		DISPAMOUNT,
		FROMACCOUNT,
		TOACCOUNT,
		REFNUM,
		AUTHNUM,
		BATCHID,
		ACCEPTORID,
		ACCEPTORNAME,
		ACQUIRERINST,
		ISSUERINST,
		FORWARDINST,
		TXFINST,
		SETTINST,
		NETWORKID,
		ACQNETWORKID,
		ISSUERNETWORKID,
		FWDNETWORKID,
		TXFNETWORKID,
		SETTNETWORKID,
		RSVFLD1,
		RSVFLD2,
		RSVFLD3,
		RSVFLD4,
		RSVFLD5,
		RSVFLD6,
		ORGCHANNEL,
		ORGPORT,
		SRCCHANNEL,
		DESTCHANNEL,
		SRCPORT,
		DESTPORT,
		REFSEQNO
	)
	VALUES
	(
		:TxnRefNum,
		:DeviceType,
		:MsgType,
        :OrgMsgType,
        :TxnCode,
        :TerminalId,
        :TerminalLocation,
        :TraceNo,
        :OrgTraceNo,
        to_date( :TranDate, 'dd-mm-yy' ),
        :TranTime,
        to_date( :OrgTranDate, 'dd-mm-yy' ),
        :OrgTranTime,
        to_date( :LocalDate, 'dd-mm-yy' ),
        :LocalTime,
        :RespCode,
        :RevCode,
        :ReasonCode,
        :AuthCode,
        to_date( :CaptureDate, 'dd-mm-yy' ),
        :CaptureTime,
        to_date( :SettlementDate, 'dd-mm-yy' ),
        to_date( :BusinessDate, 'dd-mm-yy' ),
        :AcqCurrencyCode,
        :AcqConvRate,
        to_date( :AcqConvDate, 'dd-mm-yy' ),
        :IssCurrencyCode,
        :IssConvRate,
        to_date( :IssConvDate, 'dd-mm-yy' ),
        :SettCurrencyCode,
        :SettConvRate,
        to_date( :SettConvDate, 'dd-mm-yy' ),
        :MerchantType,
        :PosEntryCode,
        :PosConditionCode,
        :PosCapCode,
        :PosPinCapCode,
        :chn,
        :t_chn,
        :AcqBranchCode,
        :IssBranchCode,
        :TxfBranchCode,
        :ForwardBranchCode,
	    :FromAcctSubType,
        :ToAcctSubType,
        :AvailBalance,
        :LedgerBalance,
        :Amount,
        :TxnFee,
        :DispAmount,
        :FromAccount,
        :ToAccount,
        :RefNum,
        :AuthNum,
        :BatchId,
		:AcceptorId,
        :AcceptorName,
        :AcquirerInst,
        :IssuerInst,
        :ForwardInst,
        :TxfInst,
        :SettInst,
        :NetworkId,
        :AcqNetworkId,
        :IssuerNetworkId,
        :FwdNetworkId,
        :TxfNetworkId,
        :SettNetworkId,
        :RsvFld1,
        :RsvFld2,
        :RsvFld3,
        :RsvFld4,
        :RsvFld5,
        :RsvFld6,
        :OrgChannel,
        :OrgPort,
        :SrcChannel,
        :DestChannel,
        :SrcPort,
        :DestPort,
        :RefSeqNo
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 81;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "insert into EZTXNLOG (TXNREFNUM,DEVICETYPE,MSGTYPE,ORGMSGTYPE,TXNCODE,TE\
RMINALID,TERMLOC,TRACENO,ORGTRACENO,TRANDATE,TRANTIME,ORGTRANDATE,ORGTRANTIM\
E,LOCALDATE,LOCALTIME,RESPCODE,REVCODE,REASONCODE,AUTHCODE,CAPTUREDATE,CAPTU\
RETIME,SETTLEMENTDATE,BUSINESSDATE,ACQCURRENCYCODE,ACQCONVRATE,ACQCONVDATE,I\
SSCURRENCYCODE,ISSCONVRATE,ISSCONVDATE,SETTCURRENCYCODE,SETTCONVRATE,SETTCON\
VDATE,MERCHANTTYPE,POSENTRYCODE,POSCONDITIONCODE,POSCAPCODE,POSPINCAPCODE,CH\
N,TCHN,ACQBRANCHCODE,ISSBRANCHCODE,TXFBRANCHCODE,FORWARDBRANCHCODE,FROMACCTS\
UBTYPE,TOACCTSUBTYPE,AVAILBALANCE,LEDGERBALANCE,AMOUNT,TXNFEE,DISPAMOUNT,FRO\
MACCOUNT,TOACCOUNT,REFNUM,AUTHNUM,BATCHID,ACCEPTORID,ACCEPTORNAME,ACQUIRERIN\
ST,ISSUERINST,FORWARDINST,TXFINST,SETTINST,NETWORKID,ACQNETWORKID,ISSUERNETW\
ORKID,FWDNETWORKID,TXFNETWORKID,SETTNETWORKID,RSVFLD1,RSVFLD2,RSVFLD3,RSVFLD\
4,RSVFLD5,RSVFLD6,ORGCHANNEL,ORGPORT,SRCCHANNEL,DESTCHANNEL,SRCPORT,DESTPORT\
,REFSEQNO) values (:b0,:b1,:b2,:b3,:b4,:b5,:b6,:b7,:b8,to_date(:b9,'dd-mm-yy\
'),:b10,to_date(:b11,'dd-mm-yy'),:b12,to");
 sqlstm.stmt = "_date(:b13,'dd-mm-yy'),:b14,:b15,:b16,:b17,:b18,to_date(:b19\
,'dd-mm-yy'),:b20,to_date(:b21,'dd-mm-yy'),to_date(:b22,'dd-mm-yy'),:b23,:b24,\
to_date(:b25,'dd-mm-yy'),:b26,:b27,to_date(:b28,'dd-mm-yy'),:b29,:b30,to_date(\
:b31,'dd-mm-yy'),:b32,:b33,:b34,:b35,:b36,:b37,:b38,:b39,:b40,:b41,:b42,:b43,:\
b44,:b45,:b46,:b47,:b48,:b49,:b50,:b51,:b52,:b53,:b54,:b55,:b56,:b57,:b58,:b59\
,:b60,:b61,:b62,:b63,:b64,:b65,:b66,:b67,:b68,:b69,:b70,:b71,:b72,:b73,:b74,:b\
75,:b76,:b77,:b78,:b79,:b80)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )312;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned int  )151;
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
 sqlstm.sqhstv[2] = (         void  *)&MsgType;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&OrgMsgType;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&TxnCode;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)TerminalId;
 sqlstm.sqhstl[5] = (unsigned int  )17;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)TerminalLocation;
 sqlstm.sqhstl[6] = (unsigned int  )65;
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&TraceNo;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&OrgTraceNo;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)TranDate;
 sqlstm.sqhstl[9] = (unsigned int  )7;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&TranTime;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)OrgTranDate;
 sqlstm.sqhstl[11] = (unsigned int  )7;
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&OrgTranTime;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)LocalDate;
 sqlstm.sqhstl[13] = (unsigned int  )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&LocalTime;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&RespCode;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&RevCode;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&ReasonCode;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&AuthCode;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)CaptureDate;
 sqlstm.sqhstl[19] = (unsigned int  )7;
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)SettlementDate;
 sqlstm.sqhstl[21] = (unsigned int  )7;
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)BusinessDate;
 sqlstm.sqhstl[22] = (unsigned int  )7;
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)AcqConvDate;
 sqlstm.sqhstl[25] = (unsigned int  )7;
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)0;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)IssConvDate;
 sqlstm.sqhstl[28] = (unsigned int  )7;
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)0;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)0;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)SettConvDate;
 sqlstm.sqhstl[31] = (unsigned int  )7;
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)0;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&MerchantType;
 sqlstm.sqhstl[32] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)0;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[33] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[34] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[35] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[36] = (unsigned int  )1;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)0;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)chn;
 sqlstm.sqhstl[37] = (unsigned int  )20;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)0;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)t_chn;
 sqlstm.sqhstl[38] = (unsigned int  )129;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)0;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[39] = (unsigned int  )11;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)0;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[40] = (unsigned int  )11;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)0;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)TxfBranchCode;
 sqlstm.sqhstl[41] = (unsigned int  )11;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)0;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[42] = (unsigned int  )11;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)0;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[43] = (unsigned int  )11;
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)0;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)ToAcctSubType;
 sqlstm.sqhstl[44] = (unsigned int  )11;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)0;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)AvailBalance;
 sqlstm.sqhstl[45] = (unsigned int  )15;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)0;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[46] = (unsigned int  )15;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)0;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)Amount;
 sqlstm.sqhstl[47] = (unsigned int  )15;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)0;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)TxnFee;
 sqlstm.sqhstl[48] = (unsigned int  )15;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)0;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)DispAmount;
 sqlstm.sqhstl[49] = (unsigned int  )15;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)0;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)FromAccount;
 sqlstm.sqhstl[50] = (unsigned int  )33;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)0;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
 sqlstm.sqhstv[51] = (         void  *)ToAccount;
 sqlstm.sqhstl[51] = (unsigned int  )33;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)0;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)RefNum;
 sqlstm.sqhstl[52] = (unsigned int  )13;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)0;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)AuthNum;
 sqlstm.sqhstl[53] = (unsigned int  )13;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)0;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)BatchId;
 sqlstm.sqhstl[54] = (unsigned int  )13;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)0;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)AcceptorId;
 sqlstm.sqhstl[55] = (unsigned int  )33;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)0;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)AcceptorName;
 sqlstm.sqhstl[56] = (unsigned int  )41;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)0;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)AcquirerInst;
 sqlstm.sqhstl[57] = (unsigned int  )13;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)0;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)IssuerInst;
 sqlstm.sqhstl[58] = (unsigned int  )13;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)0;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)ForwardInst;
 sqlstm.sqhstl[59] = (unsigned int  )13;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)0;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)TxfInst;
 sqlstm.sqhstl[60] = (unsigned int  )13;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)0;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)SettInst;
 sqlstm.sqhstl[61] = (unsigned int  )13;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)0;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)NetworkId;
 sqlstm.sqhstl[62] = (unsigned int  )17;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)0;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)AcqNetworkId;
 sqlstm.sqhstl[63] = (unsigned int  )17;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)0;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)IssuerNetworkId;
 sqlstm.sqhstl[64] = (unsigned int  )17;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)0;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)FwdNetworkId;
 sqlstm.sqhstl[65] = (unsigned int  )17;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)0;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
 sqlstm.sqhstv[66] = (         void  *)TxfNetworkId;
 sqlstm.sqhstl[66] = (unsigned int  )17;
 sqlstm.sqhsts[66] = (         int  )0;
 sqlstm.sqindv[66] = (         void  *)0;
 sqlstm.sqinds[66] = (         int  )0;
 sqlstm.sqharm[66] = (unsigned int  )0;
 sqlstm.sqadto[66] = (unsigned short )0;
 sqlstm.sqtdso[66] = (unsigned short )0;
 sqlstm.sqhstv[67] = (         void  *)SettNetworkId;
 sqlstm.sqhstl[67] = (unsigned int  )17;
 sqlstm.sqhsts[67] = (         int  )0;
 sqlstm.sqindv[67] = (         void  *)0;
 sqlstm.sqinds[67] = (         int  )0;
 sqlstm.sqharm[67] = (unsigned int  )0;
 sqlstm.sqadto[67] = (unsigned short )0;
 sqlstm.sqtdso[67] = (unsigned short )0;
 sqlstm.sqhstv[68] = (         void  *)RsvFld1;
 sqlstm.sqhstl[68] = (unsigned int  )513;
 sqlstm.sqhsts[68] = (         int  )0;
 sqlstm.sqindv[68] = (         void  *)0;
 sqlstm.sqinds[68] = (         int  )0;
 sqlstm.sqharm[68] = (unsigned int  )0;
 sqlstm.sqadto[68] = (unsigned short )0;
 sqlstm.sqtdso[68] = (unsigned short )0;
 sqlstm.sqhstv[69] = (         void  *)RsvFld2;
 sqlstm.sqhstl[69] = (unsigned int  )513;
 sqlstm.sqhsts[69] = (         int  )0;
 sqlstm.sqindv[69] = (         void  *)0;
 sqlstm.sqinds[69] = (         int  )0;
 sqlstm.sqharm[69] = (unsigned int  )0;
 sqlstm.sqadto[69] = (unsigned short )0;
 sqlstm.sqtdso[69] = (unsigned short )0;
 sqlstm.sqhstv[70] = (         void  *)RsvFld3;
 sqlstm.sqhstl[70] = (unsigned int  )51;
 sqlstm.sqhsts[70] = (         int  )0;
 sqlstm.sqindv[70] = (         void  *)0;
 sqlstm.sqinds[70] = (         int  )0;
 sqlstm.sqharm[70] = (unsigned int  )0;
 sqlstm.sqadto[70] = (unsigned short )0;
 sqlstm.sqtdso[70] = (unsigned short )0;
 sqlstm.sqhstv[71] = (         void  *)RsvFld4;
 sqlstm.sqhstl[71] = (unsigned int  )51;
 sqlstm.sqhsts[71] = (         int  )0;
 sqlstm.sqindv[71] = (         void  *)0;
 sqlstm.sqinds[71] = (         int  )0;
 sqlstm.sqharm[71] = (unsigned int  )0;
 sqlstm.sqadto[71] = (unsigned short )0;
 sqlstm.sqtdso[71] = (unsigned short )0;
 sqlstm.sqhstv[72] = (         void  *)RsvFld5;
 sqlstm.sqhstl[72] = (unsigned int  )51;
 sqlstm.sqhsts[72] = (         int  )0;
 sqlstm.sqindv[72] = (         void  *)0;
 sqlstm.sqinds[72] = (         int  )0;
 sqlstm.sqharm[72] = (unsigned int  )0;
 sqlstm.sqadto[72] = (unsigned short )0;
 sqlstm.sqtdso[72] = (unsigned short )0;
 sqlstm.sqhstv[73] = (         void  *)RsvFld6;
 sqlstm.sqhstl[73] = (unsigned int  )51;
 sqlstm.sqhsts[73] = (         int  )0;
 sqlstm.sqindv[73] = (         void  *)0;
 sqlstm.sqinds[73] = (         int  )0;
 sqlstm.sqharm[73] = (unsigned int  )0;
 sqlstm.sqadto[73] = (unsigned short )0;
 sqlstm.sqtdso[73] = (unsigned short )0;
 sqlstm.sqhstv[74] = (         void  *)OrgChannel;
 sqlstm.sqhstl[74] = (unsigned int  )33;
 sqlstm.sqhsts[74] = (         int  )0;
 sqlstm.sqindv[74] = (         void  *)0;
 sqlstm.sqinds[74] = (         int  )0;
 sqlstm.sqharm[74] = (unsigned int  )0;
 sqlstm.sqadto[74] = (unsigned short )0;
 sqlstm.sqtdso[74] = (unsigned short )0;
 sqlstm.sqhstv[75] = (         void  *)OrgPort;
 sqlstm.sqhstl[75] = (unsigned int  )33;
 sqlstm.sqhsts[75] = (         int  )0;
 sqlstm.sqindv[75] = (         void  *)0;
 sqlstm.sqinds[75] = (         int  )0;
 sqlstm.sqharm[75] = (unsigned int  )0;
 sqlstm.sqadto[75] = (unsigned short )0;
 sqlstm.sqtdso[75] = (unsigned short )0;
 sqlstm.sqhstv[76] = (         void  *)SrcChannel;
 sqlstm.sqhstl[76] = (unsigned int  )33;
 sqlstm.sqhsts[76] = (         int  )0;
 sqlstm.sqindv[76] = (         void  *)0;
 sqlstm.sqinds[76] = (         int  )0;
 sqlstm.sqharm[76] = (unsigned int  )0;
 sqlstm.sqadto[76] = (unsigned short )0;
 sqlstm.sqtdso[76] = (unsigned short )0;
 sqlstm.sqhstv[77] = (         void  *)DestChannel;
 sqlstm.sqhstl[77] = (unsigned int  )33;
 sqlstm.sqhsts[77] = (         int  )0;
 sqlstm.sqindv[77] = (         void  *)0;
 sqlstm.sqinds[77] = (         int  )0;
 sqlstm.sqharm[77] = (unsigned int  )0;
 sqlstm.sqadto[77] = (unsigned short )0;
 sqlstm.sqtdso[77] = (unsigned short )0;
 sqlstm.sqhstv[78] = (         void  *)SrcPort;
 sqlstm.sqhstl[78] = (unsigned int  )33;
 sqlstm.sqhsts[78] = (         int  )0;
 sqlstm.sqindv[78] = (         void  *)0;
 sqlstm.sqinds[78] = (         int  )0;
 sqlstm.sqharm[78] = (unsigned int  )0;
 sqlstm.sqadto[78] = (unsigned short )0;
 sqlstm.sqtdso[78] = (unsigned short )0;
 sqlstm.sqhstv[79] = (         void  *)DestPort;
 sqlstm.sqhstl[79] = (unsigned int  )33;
 sqlstm.sqhsts[79] = (         int  )0;
 sqlstm.sqindv[79] = (         void  *)0;
 sqlstm.sqinds[79] = (         int  )0;
 sqlstm.sqharm[79] = (unsigned int  )0;
 sqlstm.sqadto[79] = (unsigned short )0;
 sqlstm.sqtdso[79] = (unsigned short )0;
 sqlstm.sqhstv[80] = (         void  *)&RefSeqNo;
 sqlstm.sqhstl[80] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[80] = (         int  )0;
 sqlstm.sqindv[80] = (         void  *)0;
 sqlstm.sqinds[80] = (         int  )0;
 sqlstm.sqharm[80] = (unsigned int  )0;
 sqlstm.sqadto[80] = (unsigned short )0;
 sqlstm.sqtdso[80] = (unsigned short )0;
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
            sqlstm.arrsiz = 81;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )651;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)4352;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return sqlca.sqlcode;
    }
}

int updateEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum, const char *I_ChannelName )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		int MsgType;
        int OrgMsgType;
        int TxnCode;
        char TerminalId[ 17 ];
        char TerminalLocation[ 65 ];
        int TraceNo;
        int OrgTraceNo;
        int TranDate;
        int TranTime;
        int OrgTranDate;
        int OrgTranTime;
        int LocalDate;
        int LocalTime;
        int RespCode;
        int RevCode;
        int ReasonCode;
        int AuthCode;
        int CaptureDate;
        int CaptureTime;
        int SettlementDate;
        int AcqCurrencyCode;
        int AcqConvRate;
        int AcqConvDate;
        int IssCurrencyCode;
        int IssConvRate;
        int IssConvDate;
        int SettCurrencyCode;
        int SettConvRate;
        int SettConvDate;
        int MerchantType;
        int PosEntryCode;
        int PosConditionCode;
        int PosCapCode;
        char PosPinCapCode;
        char chn[ 20 ];
        char AcqBranchCode[ 11 ];
        char IssBranchCode[ 11 ];
        char TxfBranchCode[ 11 ];
        char ForwardBranchCode[ 11 ];
        char FromAcctSubType[ 11 ];
        char ToAcctSubType[ 11 ];
		char AvailBalance[ 15 ];
        char LedgerBalance[ 15 ];
        char Amount[ 15 ];
        char TxnFee[ 15 ];
        char DispAmount[ 15 ];
        char FromAccount[ 33 ];
        char ToAccount[ 33 ];
        char RefNum[ 13 ];
        char AuthNum[ 13 ];
        char AcceptorName[ 41 ];
        char AcquirerInst[ 13 ];
        char IssuerInst[ 13 ];
        char ForwardInst[ 13 ];
        char TxfInst[ 13 ];
        char SettInst[ 13 ];
        char NetworkId[ 17 ];
        char AcqNetworkId[ 17 ];
		char IssuerNetworkId[ 17 ];
		char FwdNetworkId[ 17 ];
		char TxfNetworkId[ 17 ];
		char SettNetworkId[ 17 ];
        char Track2[ 40 ];
        char RsvFld1[ 513 ];
        char RsvFld2[ 513 ];
        char RsvFld3[ 51 ];
        char RsvFld4[ 51 ];
        char RsvFld5[ 51 ];
        char RsvFld6[ 51 ];
        char OrgChannel[ 33 ];
        char OrgPort[ 33 ];
        char SrcChannel[ 33 ];
       	short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

    /* EXEC SQL VAR TerminalLocation IS STRING(65); */ 

    /* EXEC SQL VAR chn IS STRING(20); */ 

    /* EXEC SQL VAR AcqBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR IssBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR TxfBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR ForwardBranchCode IS STRING(11); */ 

    /* EXEC SQL VAR FromAcctSubType IS STRING(11); */ 

    /* EXEC SQL VAR ToAcctSubType IS STRING(11); */ 

    /* EXEC SQL VAR AvailBalance IS STRING(15); */ 

    /* EXEC SQL VAR LedgerBalance IS STRING(15); */ 

    /* EXEC SQL VAR Amount IS STRING(15); */ 

    /* EXEC SQL VAR TxnFee IS STRING(15); */ 

    /* EXEC SQL VAR DispAmount IS STRING(15); */ 

    /* EXEC SQL VAR FromAccount IS STRING(33); */ 

    /* EXEC SQL VAR ToAccount IS STRING(33); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR AuthNum IS STRING(13); */ 

    /* EXEC SQL VAR AcceptorName IS STRING(41); */ 

    /* EXEC SQL VAR RefNum IS STRING(13); */ 

    /* EXEC SQL VAR AcquirerInst IS STRING(13); */ 

    /* EXEC SQL VAR IssuerInst IS STRING(13); */ 

    /* EXEC SQL VAR ForwardInst IS STRING(13); */ 

    /* EXEC SQL VAR TxfInst IS STRING(13); */ 

    /* EXEC SQL VAR SettInst IS STRING(13); */ 

    /* EXEC SQL VAR NetworkId IS STRING(17); */ 

    /* EXEC SQL VAR AcqNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR IssuerNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR FwdNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR TxfNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR SettNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR Track2 IS STRING(40); */ 

    /* EXEC SQL VAR RsvFld1 IS STRING(513); */ 

    /* EXEC SQL VAR RsvFld2 IS STRING(513); */ 

    /* EXEC SQL VAR RsvFld3 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld4 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld5 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld6 IS STRING(51); */ 

    /* EXEC SQL VAR OrgChannel IS STRING(33); */ 

	/* EXEC SQL VAR OrgPort IS STRING(33); */ 

	/* EXEC SQL VAR SrcChannel IS STRING(33); */ 

	
 	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
    memset( chn, 0, sizeof( chn ) );
    memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
    memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
    memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
    memset( TxfBranchCode, 0, sizeof( TxfBranchCode ) );
    memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
    memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
    memset( AvailBalance, 0, sizeof( AvailBalance ) );
    memset( LedgerBalance, 0, sizeof( LedgerBalance ) );
    memset( Amount, 0, sizeof( Amount ) );
    memset( TxnFee, 0, sizeof( TxnFee ) );
    memset( DispAmount, 0, sizeof( DispAmount ) );
    memset( FromAccount, 0, sizeof( FromAccount ) );
    memset( ToAccount, 0, sizeof( ToAccount ) );
    memset( RefNum, 0, sizeof( RefNum ) );
    memset( AuthNum, 0, sizeof( AuthNum ) );
    memset( AcceptorName, 0, sizeof( AcceptorName ) );
    memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
    memset( IssuerInst, 0, sizeof( IssuerInst ) );
    memset( ForwardInst, 0, sizeof( ForwardInst ) );
    memset( TxfInst, 0, sizeof( TxfInst ) );
    memset( SettInst, 0, sizeof( SettInst ) );
    memset( NetworkId, 0, sizeof( NetworkId ) );
    memset( AcqNetworkId, 0, sizeof( AcqNetworkId ) );
    memset( IssuerNetworkId, 0, sizeof( IssuerNetworkId ) );
    memset( FwdNetworkId, 0, sizeof( FwdNetworkId ) );
    memset( TxfNetworkId, 0, sizeof( TxfNetworkId ) );
    memset( SettNetworkId, 0, sizeof( SettNetworkId ) );
    memset( Track2, 0, sizeof( Track2 ) );
    memset( RsvFld1, 0, sizeof( RsvFld1 ) );
    memset( RsvFld2, 0, sizeof( RsvFld2 ) );
    memset( RsvFld3, 0, sizeof( RsvFld3 ) );
    memset( RsvFld4, 0, sizeof( RsvFld4 ) );
    memset( RsvFld5, 0, sizeof( RsvFld5 ) );
    memset( RsvFld6, 0, sizeof( RsvFld6 ) );
    memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	memset( SrcChannel, 0, sizeof( SrcChannel ) );
 	
	strcpy( TxnRefNum, I_TxnRefNum );
	MsgType = txnmsg->MsgType;
    OrgMsgType = txnmsg->OrgMsgType;
    TxnCode = txnmsg->TxnCode;
    strcpy( TerminalId, txnmsg->TerminalId );
    strcpy( TerminalLocation, txnmsg->TerminalLocation );
    TraceNo = txnmsg->TraceNo;
    OrgTraceNo = txnmsg->OrgTraceNo;
    TranDate = txnmsg->TranDate;
    TranTime = txnmsg->TranTime;
    OrgTranDate = txnmsg->OrgTranDate;
    OrgTranTime = txnmsg->OrgTranTime;
    LocalDate = txnmsg->LocalDate;
    LocalTime = txnmsg->LocalTime;
    RespCode = txnmsg->RespCode;
    RevCode = txnmsg->RevCode;
    ReasonCode = txnmsg->ReasonCode;
    AuthCode = txnmsg->AuthCode;
    CaptureDate = txnmsg->CaptureDate;
    CaptureTime = txnmsg->CaptureTime;
    SettlementDate = txnmsg->SettlementDate;
    AcqCurrencyCode = txnmsg->AcqCurrencyCode;
    AcqConvRate = txnmsg->AcqConvRate;
    AcqConvDate = txnmsg->AcqConvDate;
    IssCurrencyCode = txnmsg->IssCurrencyCode;
    IssConvRate = txnmsg->IssConvRate;
    IssConvDate = txnmsg->IssConvDate;
    SettCurrencyCode = txnmsg->SettCurrencyCode;
    SettConvRate = txnmsg->SettConvRate;
    SettConvDate = txnmsg->SettConvDate;
    MerchantType = txnmsg->MerchantType;
    PosEntryCode = txnmsg->PosEntryCode;
    PosConditionCode = txnmsg->PosConditionCode;
    PosCapCode = txnmsg->PosCapCode;
    PosPinCapCode = txnmsg->PosPinCapCode;
    strcpy( chn, txnmsg->chn );
    strcpy( AcqBranchCode, txnmsg->AcqBranchCode );
    strcpy( IssBranchCode, txnmsg->IssBranchCode );
    strcpy( ForwardBranchCode, txnmsg->ForwardBranchCode );
    strcpy( TxfBranchCode, txnmsg->TxfBranchCode );
	strcpy( FromAcctSubType, txnmsg->FromAcctSubType );
    strcpy( ToAcctSubType, txnmsg->ToAcctSubType );
    strcpy( AvailBalance, txnmsg->AvailBalance );
    strcpy( LedgerBalance, txnmsg->LedgerBalance );
    strcpy( Amount, txnmsg->Amount );
    strcpy( TxnFee, txnmsg->TxnFee );
    strcpy( DispAmount, txnmsg->DispAmount );
    strcpy( FromAccount, txnmsg->FromAccount );
    strcpy( ToAccount, txnmsg->ToAccount );
    strcpy( RefNum, txnmsg->RefNum );
    strcpy( AuthNum, txnmsg->AuthNum );
    strcpy( AcceptorName, txnmsg->AcceptorName );
    strcpy( AcquirerInst, txnmsg->AcquirerInst );
    strcpy( IssuerInst, txnmsg->IssuerInst );
    strcpy( ForwardInst, txnmsg->ForwardInst );
    strcpy( TxfInst, txnmsg->TxfInst );
    strcpy( SettInst, txnmsg->SettInst );
    strcpy( NetworkId, txnmsg->NetworkId );
    strcpy( AcqNetworkId, txnmsg->AcqNetworkId );
    strcpy( IssuerNetworkId, txnmsg->IssuerNetworkId );
    strcpy( FwdNetworkId, txnmsg->FwdNetworkId );
    strcpy( TxfNetworkId, txnmsg->TxfNetworkId );
    strcpy( SettNetworkId, txnmsg->SettNetworkId );
    strcpy( Track2, txnmsg->Track2 );
    strcpy( RsvFld1, txnmsg->RsvFld1 );
    strcpy( RsvFld2, txnmsg->RsvFld2 );
    strcpy( RsvFld3, txnmsg->RsvFld3 );
    strcpy( RsvFld4, txnmsg->RsvFld4 );
    strcpy( RsvFld5, txnmsg->RsvFld5 );
    strcpy( RsvFld6, txnmsg->RsvFld6 );
   	strcpy( OrgChannel, txnmsg->OrgChannel );
	strcpy( OrgPort, txnmsg->OrgPort );
	strcpy( SrcChannel, I_ChannelName );

	/* EXEC SQL UPDATE INTO EZTXNLOG SET
		TXNREFNUM = :TxnRefNum,
		MSGTYPE = :MsgType,
		TXNCODE = :TxnCode,
		ORGMSGTYPE = :OrgMsgType,
		TERMINALID = :TerminalId,
		TERMLOC = :TerminalLocation,
		TRACENO = :TraceNo,
		ORGTRACENO = :OrgTraceNo,
		TRANDATE = :TranDate,
		TRANTIME = :TranTime,
		ORGTRANDATE = :OrgTranDate,
		ORGTRANTIME = :OrgTranTime,
		LOCALDATE = :LocalDate,
		LOCALTIME = :LocalTime,
		RESPCODE = :RespCode,
		REVCODE = :RevCode,
		REASONCODE = :ReasonCode,
		AUTHCODE = :AuthCode,
		CAPTUREDATE = :CaptureDate,
		CAPTURETIME = :CaptureTime,
		SETTLEMENTDATE = :SettlementDate,
		ACQCURRENCYCODE = :AcqCurrencyCode,
		ACQCONVRATE = :AcqConvRate,
		ACQCONVDATE = :AcqConvDate,
		ISSCURRENCYCODE = :IssCurrencyCode,
		ISSCONVRATE = :IssConvRate,
		ISSCONVDATE = :IssConvDate,
		SETTCURRENCYCODE = :SettCurrencyCode,
		SETTCONVRATE = :SettConvRate,
		SETTCONVDATE = :SettConvDate,
		MERCHANTTYPE = :MerchantType,
		POSENTRYCODE = :PosEntryCode,
		POSCONDITIONCODE = :PosConditionCode,
		POSCAPCODE = :PosCapCode,
		POSPINCAPCODE = :PosPinCapCode,
		CHN = :chn,
		ACQBRANCHCODE = :AcqBranchCode,
		ISSBRANCHCODE = :IssBranchCode,
		TXFBRANCHCODE = :TxfBranchCode,
		FORWARDBRANCHCODE = :ForwardBranchCode,
		FROMACCTSUBTYPE = :FromAcctSubType,
		TOACCTSUBTYPE = :ToAcctSubType,
		AVAILBALANCE = :AvailBalance,
		LEDGERBALANCE = :LedgerBalance,
		AMOUNT = :Amount,
		TXNFEE = :TxnFee,
		DISPAMOUNT = :DispAmount,
		FROMACCOUNT = :FromAccount,
		TOACCOUNT = :ToAccount,
		REFNUM = :RefNum,
		AUTHNUM = :AuthNum,
		ACCEPTORNAME = :AcceptorName,
		ACQUIRERINST = :AcquirerInst,
		ISSUERINST = :IssuerInst,
		FORWARDINST = :ForwardInst,
		TXFINST = :TxfInst,
		SETTINST = :SettInst,
		NETWORKID = :NetworkId,
		ACQNETWORKID = :AcqNetworkId,
		ISSUERNETWORKID = :IssuerNetworkId,
		FWDNETWORKID = :FwdNetworkId,
		TXFNETWORKID = :TxfNetworkId,
		SETTNETWORKID = :SettNetworkId,
		TRACK2 = :Track2,
		RSVFLD1 = :RsvFld1,
		RSVFLD2 = :RsvFld2,
		RSVFLD3 = :RsvFld3,
		RSVFLD4 = :RsvFld4,
		RSVFLD5 = :RsvFld5,
		RSVFLD6 = :RsvFld6,
		ORGCHANNEL = :OrgChannel,
		ORGPORT = :OrgPort, 
		SRCPORT = :SrcChannel
	WHERE RTRIM(TXNREFNUM) = :TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 81;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "update INTO EZTXNLOG  set TXNREFNUM=:b0,MSGTYPE=:b1,TXNCODE=:b2,ORGMSGTY\
PE=:b3,TERMINALID=:b4,TERMLOC=:b5,TRACENO=:b6,ORGTRACENO=:b7,TRANDATE=:b8,TR\
ANTIME=:b9,ORGTRANDATE=:b10,ORGTRANTIME=:b11,LOCALDATE=:b12,LOCALTIME=:b13,R\
ESPCODE=:b14,REVCODE=:b15,REASONCODE=:b16,AUTHCODE=:b17,CAPTUREDATE=:b18,CAP\
TURETIME=:b19,SETTLEMENTDATE=:b20,ACQCURRENCYCODE=:b21,ACQCONVRATE=:b22,ACQC\
ONVDATE=:b23,ISSCURRENCYCODE=:b24,ISSCONVRATE=:b25,ISSCONVDATE=:b26,SETTCURR\
ENCYCODE=:b27,SETTCONVRATE=:b28,SETTCONVDATE=:b29,MERCHANTTYPE=:b30,POSENTRY\
CODE=:b31,POSCONDITIONCODE=:b32,POSCAPCODE=:b33,POSPINCAPCODE=:b34,CHN=:b35,\
ACQBRANCHCODE=:b36,ISSBRANCHCODE=:b37,TXFBRANCHCODE=:b38,FORWARDBRANCHCODE=:\
b39,FROMACCTSUBTYPE=:b40,TOACCTSUBTYPE=:b41,AVAILBALANCE=:b42,LEDGERBALANCE=\
:b43,AMOUNT=:b44,TXNFEE=:b45,DISPAMOUNT=:b46,FROMACCOUNT=:b47,TOACCOUNT=:b48\
,REFNUM=:b49,AUTHNUM=:b50,ACCEPTORNAME=:b51,ACQUIRERINST=:b52,ISSUERINST=:b5\
3,FORWARDINST=:b54,TXFINST=:b55,SETTINST=:b56,NETWORKID=:b57,ACQNETWORKID=:b\
58,ISSUERNETWORKID=:b59,FWDNETWORKID=:b6");
 sqlstm.stmt = "0,TXFNETWORKID=:b61,SETTNETWORKID=:b62,TRACK2=:b63,RSVFLD1=:\
b64,RSVFLD2=:b65,RSVFLD3=:b66,RSVFLD4=:b67,RSVFLD5=:b68,RSVFLD6=:b69,ORGCHANNE\
L=:b70,ORGPORT=:b71,SRCPORT=:b72 where RTRIM(TXNREFNUM)=:b0";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )666;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned int  )151;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&MsgType;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&TxnCode;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&OrgMsgType;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TerminalId;
 sqlstm.sqhstl[4] = (unsigned int  )17;
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)TerminalLocation;
 sqlstm.sqhstl[5] = (unsigned int  )65;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&TraceNo;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&OrgTraceNo;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&TranDate;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&TranTime;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&OrgTranDate;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&OrgTranTime;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&LocalDate;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&LocalTime;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&RespCode;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&RevCode;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&ReasonCode;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&AuthCode;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)0;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)0;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)&MerchantType;
 sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)0;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[31] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)0;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[32] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)0;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[33] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[34] = (unsigned int  )1;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)chn;
 sqlstm.sqhstl[35] = (unsigned int  )20;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[36] = (unsigned int  )11;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)0;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[37] = (unsigned int  )11;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)0;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)TxfBranchCode;
 sqlstm.sqhstl[38] = (unsigned int  )11;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)0;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[39] = (unsigned int  )11;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)0;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[40] = (unsigned int  )11;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)0;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)ToAcctSubType;
 sqlstm.sqhstl[41] = (unsigned int  )11;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)0;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)AvailBalance;
 sqlstm.sqhstl[42] = (unsigned int  )15;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)0;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[43] = (unsigned int  )15;
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)0;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)Amount;
 sqlstm.sqhstl[44] = (unsigned int  )15;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)0;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)TxnFee;
 sqlstm.sqhstl[45] = (unsigned int  )15;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)0;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)DispAmount;
 sqlstm.sqhstl[46] = (unsigned int  )15;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)0;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)FromAccount;
 sqlstm.sqhstl[47] = (unsigned int  )33;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)0;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)ToAccount;
 sqlstm.sqhstl[48] = (unsigned int  )33;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)0;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)RefNum;
 sqlstm.sqhstl[49] = (unsigned int  )13;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)0;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)AuthNum;
 sqlstm.sqhstl[50] = (unsigned int  )13;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)0;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
 sqlstm.sqhstv[51] = (         void  *)AcceptorName;
 sqlstm.sqhstl[51] = (unsigned int  )41;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)0;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)AcquirerInst;
 sqlstm.sqhstl[52] = (unsigned int  )13;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)0;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)IssuerInst;
 sqlstm.sqhstl[53] = (unsigned int  )13;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)0;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)ForwardInst;
 sqlstm.sqhstl[54] = (unsigned int  )13;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)0;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)TxfInst;
 sqlstm.sqhstl[55] = (unsigned int  )13;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)0;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)SettInst;
 sqlstm.sqhstl[56] = (unsigned int  )13;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)0;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)NetworkId;
 sqlstm.sqhstl[57] = (unsigned int  )17;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)0;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)AcqNetworkId;
 sqlstm.sqhstl[58] = (unsigned int  )17;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)0;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)IssuerNetworkId;
 sqlstm.sqhstl[59] = (unsigned int  )17;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)0;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)FwdNetworkId;
 sqlstm.sqhstl[60] = (unsigned int  )17;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)0;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)TxfNetworkId;
 sqlstm.sqhstl[61] = (unsigned int  )17;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)0;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)SettNetworkId;
 sqlstm.sqhstl[62] = (unsigned int  )17;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)0;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)Track2;
 sqlstm.sqhstl[63] = (unsigned int  )40;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)0;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)RsvFld1;
 sqlstm.sqhstl[64] = (unsigned int  )513;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)0;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)RsvFld2;
 sqlstm.sqhstl[65] = (unsigned int  )513;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)0;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
 sqlstm.sqhstv[66] = (         void  *)RsvFld3;
 sqlstm.sqhstl[66] = (unsigned int  )51;
 sqlstm.sqhsts[66] = (         int  )0;
 sqlstm.sqindv[66] = (         void  *)0;
 sqlstm.sqinds[66] = (         int  )0;
 sqlstm.sqharm[66] = (unsigned int  )0;
 sqlstm.sqadto[66] = (unsigned short )0;
 sqlstm.sqtdso[66] = (unsigned short )0;
 sqlstm.sqhstv[67] = (         void  *)RsvFld4;
 sqlstm.sqhstl[67] = (unsigned int  )51;
 sqlstm.sqhsts[67] = (         int  )0;
 sqlstm.sqindv[67] = (         void  *)0;
 sqlstm.sqinds[67] = (         int  )0;
 sqlstm.sqharm[67] = (unsigned int  )0;
 sqlstm.sqadto[67] = (unsigned short )0;
 sqlstm.sqtdso[67] = (unsigned short )0;
 sqlstm.sqhstv[68] = (         void  *)RsvFld5;
 sqlstm.sqhstl[68] = (unsigned int  )51;
 sqlstm.sqhsts[68] = (         int  )0;
 sqlstm.sqindv[68] = (         void  *)0;
 sqlstm.sqinds[68] = (         int  )0;
 sqlstm.sqharm[68] = (unsigned int  )0;
 sqlstm.sqadto[68] = (unsigned short )0;
 sqlstm.sqtdso[68] = (unsigned short )0;
 sqlstm.sqhstv[69] = (         void  *)RsvFld6;
 sqlstm.sqhstl[69] = (unsigned int  )51;
 sqlstm.sqhsts[69] = (         int  )0;
 sqlstm.sqindv[69] = (         void  *)0;
 sqlstm.sqinds[69] = (         int  )0;
 sqlstm.sqharm[69] = (unsigned int  )0;
 sqlstm.sqadto[69] = (unsigned short )0;
 sqlstm.sqtdso[69] = (unsigned short )0;
 sqlstm.sqhstv[70] = (         void  *)OrgChannel;
 sqlstm.sqhstl[70] = (unsigned int  )33;
 sqlstm.sqhsts[70] = (         int  )0;
 sqlstm.sqindv[70] = (         void  *)0;
 sqlstm.sqinds[70] = (         int  )0;
 sqlstm.sqharm[70] = (unsigned int  )0;
 sqlstm.sqadto[70] = (unsigned short )0;
 sqlstm.sqtdso[70] = (unsigned short )0;
 sqlstm.sqhstv[71] = (         void  *)OrgPort;
 sqlstm.sqhstl[71] = (unsigned int  )33;
 sqlstm.sqhsts[71] = (         int  )0;
 sqlstm.sqindv[71] = (         void  *)0;
 sqlstm.sqinds[71] = (         int  )0;
 sqlstm.sqharm[71] = (unsigned int  )0;
 sqlstm.sqadto[71] = (unsigned short )0;
 sqlstm.sqtdso[71] = (unsigned short )0;
 sqlstm.sqhstv[72] = (         void  *)SrcChannel;
 sqlstm.sqhstl[72] = (unsigned int  )33;
 sqlstm.sqhsts[72] = (         int  )0;
 sqlstm.sqindv[72] = (         void  *)0;
 sqlstm.sqinds[72] = (         int  )0;
 sqlstm.sqharm[72] = (unsigned int  )0;
 sqlstm.sqadto[72] = (unsigned short )0;
 sqlstm.sqtdso[72] = (unsigned short )0;
 sqlstm.sqhstv[73] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[73] = (unsigned int  )151;
 sqlstm.sqhsts[73] = (         int  )0;
 sqlstm.sqindv[73] = (         void  *)0;
 sqlstm.sqinds[73] = (         int  )0;
 sqlstm.sqharm[73] = (unsigned int  )0;
 sqlstm.sqadto[73] = (unsigned short )0;
 sqlstm.sqtdso[73] = (unsigned short )0;
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
  sqlstm.arrsiz = 81;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )977;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	   return sqlca.sqlcode;
	}
}