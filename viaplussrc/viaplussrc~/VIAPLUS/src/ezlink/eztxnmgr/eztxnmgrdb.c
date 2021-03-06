
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
    "eztxnmgrdb.pc"
};


static unsigned int sqlctx = 637035;


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
            void  *sqhstv[73];
   unsigned int   sqhstl[73];
            int   sqhsts[73];
            void  *sqindv[73];
            int   sqinds[73];
   unsigned int   sqharm[73];
   unsigned int   *sqharc[73];
   unsigned short  sqadto[73];
   unsigned short  sqtdso[73];
} sqlstm = {12,73};

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
5,0,0,1,1745,0,4,166,0,0,73,7,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,
3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,
2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,
0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,1,0,0,2,5,0,0,2,5,
0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,
5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,3,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,
2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,0,2,5,0,
0,2,5,0,0,2,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
312,0,0,2,1277,0,3,611,0,0,66,66,0,1,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,
1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,1,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,
0,0,1,5,0,0,1,5,0,0,
591,0,0,3,0,0,29,751,0,0,0,0,0,1,0,
606,0,0,4,1160,0,5,962,0,0,66,66,0,1,0,1,3,0,0,1,3,0,0,1,5,0,0,1,3,0,0,1,3,0,0,
1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,5,
0,0,1,3,0,0,1,3,0,0,
885,0,0,5,0,0,29,1029,0,0,0,0,0,1,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <ezlink/ezlnkmsg.h>

int LocateEzTxnLog( struct EzTxnMsg *txnmsg, const char *IndxName )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int MsgType;
		int OrgMsgType;
		int TxnCode;
		char TerminalId[ 17 ];
		char TermLoc[ 65 ];
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
		char CHN[ 20 ];
		char AcqBranchCode[ 11 ];
		char IssBranchCode[ 11 ];
		char ForwardBranchCode[ 11 ];
		char FromAcctType[ 11 ];
		char FromAcctSubType[ 11 ];
		char ToAcctType[ 11 ];
		char ToAcctSubType[ 11 ];
		char AvailBalance[ 15 ];
		char LedgerBalance[ 15 ];
		char Amount[ 15 ];
		char TxnFee[ 15 ];
		char DispAmount[ 15 ];
		char FromAccount[ 33 ];
		char ToAccount[ 33 ];
		char RefNum[ 13 ];
		int AuthCode;
		char AcceptorName[ 41 ];
		char AcquirerInst[ 11 ];
		char IssuerInst[ 11 ];
		char ForwardInst[ 11 ];
		char AcquirerBin[ 11 ];
		char IssuerBin[ 11 ];
		char ForwardBin[ 11 ];
		char Track2[ 40 ];
		char RsvFld1[ 50 ];
		char RsvFld2[ 50 ];
		char RsvFld3[ 50 ];
		char RsvFld4[ 50 ];
		char RsvFld5[ 50 ];
		char RsvFld6[ 50 ];
		char OrgChannel[ 33 ];
		char OrgPort[ 33 ];
		char Input_InstId[ 11 ];
		char Input_chn[ 20 ];
		int Input_TraceNo;
		int Input_LocalDate;
		int Input_LocalTime;
		char Input_TerminalId[ 17 ];
		int Input_TxnCode;
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

	/* EXEC SQL VAR TermLoc IS STRING(65); */ 

	/* EXEC SQL VAR CHN IS STRING(20); */ 

	/* EXEC SQL VAR AcqBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR IssBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR ForwardBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR FromAcctType IS STRING(11); */ 

	/* EXEC SQL VAR FromAcctSubType IS STRING(11); */ 

	/* EXEC SQL VAR ToAcctType IS STRING(11); */ 

	/* EXEC SQL VAR ToAcctSubType IS STRING(11); */ 

	/* EXEC SQL VAR AvailBalance IS STRING(11); */ 

	/* EXEC SQL VAR LedgerBalance IS STRING(11); */ 

	/* EXEC SQL VAR Amount IS STRING(15); */ 

	/* EXEC SQL VAR TxnFee IS STRING(15); */ 

	/* EXEC SQL VAR DispAmount IS STRING(15); */ 

	/* EXEC SQL VAR FromAccount IS STRING(33); */ 

	/* EXEC SQL VAR ToAccount IS STRING(33); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR AcceptorName IS STRING(41); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR AcquirerInst IS STRING(11); */ 

	/* EXEC SQL VAR IssuerInst IS STRING(11); */ 

	/* EXEC SQL VAR ForwardInst IS STRING(11); */ 

	/* EXEC SQL VAR AcquirerBin IS STRING(11); */ 

	/* EXEC SQL VAR IssuerBin IS STRING(11); */ 

	/* EXEC SQL VAR ForwardBin IS STRING(11); */ 

	/* EXEC SQL VAR Track2 IS STRING(40); */ 

	/* EXEC SQL VAR RsvFld1 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld2 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld3 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld4 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld5 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld6 IS STRING(50); */ 

	/* EXEC SQL VAR OrgChannel IS STRING(33); */ 

	/* EXEC SQL VAR OrgPort IS STRING(33); */ 

	/* EXEC SQL VAR Input_InstId IS STRING(11); */ 

	/* EXEC SQL VAR Input_chn IS STRING(20); */ 

	/* EXEC SQL VAR Input_TerminalId IS STRING(17); */ 


	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( CHN, 0, sizeof( CHN ) );
	memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
	memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
	memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
	memset( FromAcctType, 0, sizeof( FromAcctType ) );
	memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
	memset( ToAcctType, 0, sizeof( ToAcctType ) );
	memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
	memset( Amount, 0, sizeof( Amount ) );
	memset( DispAmount, 0, sizeof( DispAmount ) );
	memset( FromAccount, 0, sizeof( FromAccount ) );
	memset( ToAccount, 0, sizeof( ToAccount ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
	memset( IssuerInst, 0, sizeof( IssuerInst ) );
	memset( ForwardInst, 0, sizeof( ForwardInst ) );
	memset( AcquirerBin, 0, sizeof( AcquirerBin ) );
	memset( IssuerBin, 0, sizeof( IssuerBin ) );
	memset( ForwardBin, 0, sizeof( ForwardBin ) );
	memset( Track2, 0, sizeof( Track2 ) );
	memset( RsvFld1, 0, sizeof( RsvFld1 ) );
	memset( RsvFld2, 0, sizeof( RsvFld2 ) );
	memset( RsvFld3, 0, sizeof( RsvFld3 ) );
	memset( RsvFld4, 0, sizeof( RsvFld4 ) );
	memset( RsvFld5, 0, sizeof( RsvFld5 ) );
	memset( RsvFld6, 0, sizeof( RsvFld6 ) );
	memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	memset( Input_InstId, 0, sizeof( Input_InstId ) );
	memset( Input_chn, 0, sizeof( Input_chn ) );
	memset( Input_TerminalId, 0, sizeof( Input_TerminalId ) );

	strcpy( Input_InstId, txnmsg->IssuerInst );
	strcpy( Input_TerminalId, txnmsg->TerminalId );
	strcpy( Input_chn, txnmsg->chn );
	Input_LocalDate = txnmsg->LocalDate;
	Input_LocalTime = txnmsg->LocalTime;
	Input_TraceNo = txnmsg->TraceNo;
	Input_TxnCode = txnmsg->TraceNo;

	/* EXEC SQL SELECT
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
		RTRIM(FORWARDBRANCHCODE),
		RTRIM(FROMACCTTYPE),
		RTRIM(FROMACCTSUBTYPE),
		RTRIM(TOACCTTYPE),
		RTRIM(TOACCTSUBTYPE),
		RTRIM(AVAILBALANCE),
		RTRIM(LEDGERBALANCE),
		RTRIM(AMOUNT),
		RTRIM(TXNFEE),
		RTRIM(DISPAMOUNT),
		RTRIM(FROMACCOUNT),
		RTRIM(TOACCOUNT),
		RTRIM(REFNUM),
		RTRIM(AUTHCODE),
		RTRIM(ACCEPTORNAME),
		RTRIM(ACQUIRERINST),
		RTRIM(ISSUERINST),
		RTRIM(FORWARDINST),
		RTRIM(ACQUIRERBIN),
		RTRIM(ISSUERBIN),
		RTRIM(FORWARDBIN),
		RTRIM(TRACK2),
		RTRIM(RSVFLD1),
		RTRIM(RSVFLD2),
		RTRIM(RSVFLD3),
		RTRIM(RSVFLD4),
		RTRIM(RSVFLD5),
		RTRIM(RSVFLD6),
		RTRIM(ORGCHANNEL),
		RTRIM(ORGPORT)
		INTO
		:MsgType,
		:OrgMsgType:ind_var,
		:TxnCode,
		:TerminalId,
		:TermLoc:ind_var,
		:TraceNo,
		:OrgTraceNo:ind_var,
		:TranDate,
		:TranTime,
		:OrgTranDate:ind_var,
		:OrgTranTime:ind_var,
		:LocalDate,
		:LocalTime,
		:RespCode,
		:RevCode:ind_var,
		:ReasonCode:ind_var,
		:CaptureDate:ind_var,
		:CaptureTime:ind_var,
		:SettlementDate:ind_var,
		:AcqCurrencyCode,
		:AcqConvRate:ind_var,
		:AcqConvDate:ind_var,
		:IssCurrencyCode,
		:IssConvRate:ind_var,
		:IssConvDate:ind_var,
		:SettCurrencyCode:ind_var,
		:SettConvRate:ind_var,
		:SettConvDate:ind_var,
		:MerchantType,
		:PosEntryCode:ind_var,
		:PosConditionCode:ind_var,
		:PosCapCode:ind_var,
		:PosPinCapCode:ind_var,
		:CHN,
		:AcqBranchCode,
		:IssBranchCode,
		:ForwardBranchCode:ind_var,
		:FromAcctType:ind_var,
		:FromAcctSubType:ind_var,
		:ToAcctType:ind_var,
		:ToAcctSubType:ind_var,
		:AvailBalance:ind_var,
		:LedgerBalance:ind_var,
		:Amount:ind_var,
		:TxnFee:ind_var,
		:DispAmount:ind_var,
		:FromAccount:ind_var,
		:ToAccount:ind_var,
		:RefNum:ind_var,
		:AuthCode:ind_var,
		:AcceptorName:ind_var,
		:AcquirerInst,
		:IssuerInst,
		:ForwardInst:ind_var,
		:AcquirerBin,
		:IssuerBin,
		:ForwardBin:ind_var,
		:Track2:ind_var,
		:RsvFld1:ind_var,
		:RsvFld2:ind_var,
		:RsvFld3:ind_var,
		:RsvFld4:ind_var,
		:RsvFld5:ind_var,
		:RsvFld6:ind_var,
		:OrgChannel,
		:OrgPort
	FROM EZTXNLOG WHERE RTRIM(ISSUERINST)=:Input_InstId AND RTRIM(CHN)=:Input_chn AND TRACENO=:Input_TraceNo AND RTRIM(TERMID)=:Input_TerminalId AND LOCALDATE= :Input_LocalDate AND LOCALTIME= :Input_LocalTime AND TXNCODE= :Input_TxnCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 73;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "select MSGTYPE ,ORGMSGTYPE ,TXNCODE ,RTRIM(TERMINALID) ,RTRIM(TERMLOC) ,\
TRACENO ,ORGTRACENO ,TRANDATE ,TRANTIME ,ORGTRANDATE ,ORGTRANTIME ,LOCALDATE\
 ,LOCALTIME ,RESPCODE ,REVCODE ,REASONCODE ,CAPTUREDATE ,CAPTURETIME ,SETTLE\
MENTDATE ,ACQCURRENCYCODE ,ACQCONVRATE ,ACQCONVDATE ,ISSCURRENCYCODE ,ISSCON\
VRATE ,ISSCONVDATE ,SETTCURRENCYCODE ,SETTCONVRATE ,SETTCONVDATE ,MERCHANTTY\
PE ,POSENTRYCODE ,POSCONDITIONCODE ,POSCAPCODE ,POSPINCAPCODE ,RTRIM(CHN) ,R\
TRIM(ACQBRANCHCODE) ,RTRIM(ISSBRANCHCODE) ,RTRIM(FORWARDBRANCHCODE) ,RTRIM(F\
ROMACCTTYPE) ,RTRIM(FROMACCTSUBTYPE) ,RTRIM(TOACCTTYPE) ,RTRIM(TOACCTSUBTYPE\
) ,RTRIM(AVAILBALANCE) ,RTRIM(LEDGERBALANCE) ,RTRIM(AMOUNT) ,RTRIM(TXNFEE) ,\
RTRIM(DISPAMOUNT) ,RTRIM(FROMACCOUNT) ,RTRIM(TOACCOUNT) ,RTRIM(REFNUM) ,RTRI\
M(AUTHCODE) ,RTRIM(ACCEPTORNAME) ,RTRIM(ACQUIRERINST) ,RTRIM(ISSUERINST) ,RT\
RIM(FORWARDINST) ,RTRIM(ACQUIRERBIN) ,RTRIM(ISSUERBIN) ,RTRIM(FORWARDBIN) ,R\
TRIM(TRACK2) ,RTRIM(RSVFLD1) ,RTRIM(RSVFLD2) ,RTRIM(RSVFLD3) ,RTRIM(RSVFLD4)\
 ,RTRIM(RSVFLD5) ,RTRIM(RSVFLD6) ,RTRIM(");
 sqlstm.stmt = "ORGCHANNEL) ,RTRIM(ORGPORT) into :b0,:b1:b2,:b3,:b4,:b5:b6,:\
b7,:b8:b9,:b10,:b11,:b12:b13,:b14:b15,:b16,:b17,:b18,:b19:b20,:b21:b22,:b23:b2\
4,:b25:b26,:b27:b28,:b29,:b30:b31,:b32:b33,:b34,:b35:b36,:b37:b38,:b39:b40,:b4\
1:b42,:b43:b44,:b45,:b46:b47,:b48:b49,:b50:b51,:b52:b53,:b54,:b55,:b56,:b57:b5\
8,:b59:b60,:b61:b62,:b63:b64,:b65:b66,:b67:b68,:b69:b70,:b71:b72,:b73:b74,:b75\
:b76,:b77:b78,:b79:b80,:b81:b82,:b83:b84,:b85:b86,:b87,:b88,:b89:b90,:b91,:b92\
,:b93:b94,:b95:b96,:b97:b98,:b99:b100,:b101:b102,:b103:b104,:b105:b106,:b107:b\
108,:b109,:b110  from EZTXNLOG where ((((((RTRIM(ISSUERINST)=:b111 and RTRIM(C\
HN)=:b112) and TRACENO=:b113) and RTRIM(TERMID)=:b114) and LOCALDATE=:b115) an\
d LOCALTIME=:b116) and TXNCODE=:b117)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&MsgType;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
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
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TerminalId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TermLoc;
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
 sqlstm.sqindv[5] = (         void  *)0;
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
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&TranTime;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
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
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&LocalTime;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&RespCode;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
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
 sqlstm.sqhstv[16] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)&ind_var;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)&ind_var;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)&ind_var;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)&ind_var;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)&ind_var;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)&ind_var;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)&ind_var;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)&ind_var;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)&ind_var;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)&ind_var;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)&MerchantType;
 sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)&ind_var;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)&ind_var;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[31] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)&ind_var;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[32] = (unsigned int  )1;
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)&ind_var;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)CHN;
 sqlstm.sqhstl[33] = (unsigned int  )20;
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[34] = (unsigned int  )11;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[35] = (unsigned int  )11;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[36] = (unsigned int  )11;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)&ind_var;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)FromAcctType;
 sqlstm.sqhstl[37] = (unsigned int  )11;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)&ind_var;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[38] = (unsigned int  )11;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)&ind_var;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)ToAcctType;
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
 sqlstm.sqhstl[41] = (unsigned int  )11;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)&ind_var;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[42] = (unsigned int  )11;
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
 sqlstm.sqhstv[49] = (         void  *)&AuthCode;
 sqlstm.sqhstl[49] = (unsigned int  )sizeof(int);
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
 sqlstm.sqhstl[51] = (unsigned int  )11;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)0;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)IssuerInst;
 sqlstm.sqhstl[52] = (unsigned int  )11;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)0;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)ForwardInst;
 sqlstm.sqhstl[53] = (unsigned int  )11;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)&ind_var;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)AcquirerBin;
 sqlstm.sqhstl[54] = (unsigned int  )11;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)0;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)IssuerBin;
 sqlstm.sqhstl[55] = (unsigned int  )11;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)0;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)ForwardBin;
 sqlstm.sqhstl[56] = (unsigned int  )11;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)&ind_var;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)Track2;
 sqlstm.sqhstl[57] = (unsigned int  )40;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)&ind_var;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)RsvFld1;
 sqlstm.sqhstl[58] = (unsigned int  )50;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)&ind_var;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)RsvFld2;
 sqlstm.sqhstl[59] = (unsigned int  )50;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)&ind_var;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)RsvFld3;
 sqlstm.sqhstl[60] = (unsigned int  )50;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)&ind_var;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)RsvFld4;
 sqlstm.sqhstl[61] = (unsigned int  )50;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)&ind_var;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)RsvFld5;
 sqlstm.sqhstl[62] = (unsigned int  )50;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)&ind_var;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)RsvFld6;
 sqlstm.sqhstl[63] = (unsigned int  )50;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)&ind_var;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)OrgChannel;
 sqlstm.sqhstl[64] = (unsigned int  )33;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)0;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)OrgPort;
 sqlstm.sqhstl[65] = (unsigned int  )33;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)0;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
 sqlstm.sqhstv[66] = (         void  *)Input_InstId;
 sqlstm.sqhstl[66] = (unsigned int  )11;
 sqlstm.sqhsts[66] = (         int  )0;
 sqlstm.sqindv[66] = (         void  *)0;
 sqlstm.sqinds[66] = (         int  )0;
 sqlstm.sqharm[66] = (unsigned int  )0;
 sqlstm.sqadto[66] = (unsigned short )0;
 sqlstm.sqtdso[66] = (unsigned short )0;
 sqlstm.sqhstv[67] = (         void  *)Input_chn;
 sqlstm.sqhstl[67] = (unsigned int  )20;
 sqlstm.sqhsts[67] = (         int  )0;
 sqlstm.sqindv[67] = (         void  *)0;
 sqlstm.sqinds[67] = (         int  )0;
 sqlstm.sqharm[67] = (unsigned int  )0;
 sqlstm.sqadto[67] = (unsigned short )0;
 sqlstm.sqtdso[67] = (unsigned short )0;
 sqlstm.sqhstv[68] = (         void  *)&Input_TraceNo;
 sqlstm.sqhstl[68] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[68] = (         int  )0;
 sqlstm.sqindv[68] = (         void  *)0;
 sqlstm.sqinds[68] = (         int  )0;
 sqlstm.sqharm[68] = (unsigned int  )0;
 sqlstm.sqadto[68] = (unsigned short )0;
 sqlstm.sqtdso[68] = (unsigned short )0;
 sqlstm.sqhstv[69] = (         void  *)Input_TerminalId;
 sqlstm.sqhstl[69] = (unsigned int  )17;
 sqlstm.sqhsts[69] = (         int  )0;
 sqlstm.sqindv[69] = (         void  *)0;
 sqlstm.sqinds[69] = (         int  )0;
 sqlstm.sqharm[69] = (unsigned int  )0;
 sqlstm.sqadto[69] = (unsigned short )0;
 sqlstm.sqtdso[69] = (unsigned short )0;
 sqlstm.sqhstv[70] = (         void  *)&Input_LocalDate;
 sqlstm.sqhstl[70] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[70] = (         int  )0;
 sqlstm.sqindv[70] = (         void  *)0;
 sqlstm.sqinds[70] = (         int  )0;
 sqlstm.sqharm[70] = (unsigned int  )0;
 sqlstm.sqadto[70] = (unsigned short )0;
 sqlstm.sqtdso[70] = (unsigned short )0;
 sqlstm.sqhstv[71] = (         void  *)&Input_LocalTime;
 sqlstm.sqhstl[71] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[71] = (         int  )0;
 sqlstm.sqindv[71] = (         void  *)0;
 sqlstm.sqinds[71] = (         int  )0;
 sqlstm.sqharm[71] = (unsigned int  )0;
 sqlstm.sqadto[71] = (unsigned short )0;
 sqlstm.sqtdso[71] = (unsigned short )0;
 sqlstm.sqhstv[72] = (         void  *)&Input_TxnCode;
 sqlstm.sqhstl[72] = (unsigned int  )sizeof(int);
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
	memset( txnmsg->TerminalLocation, 0, sizeof( txnmsg->TerminalLocation ) );
	strcpy( txnmsg->TerminalLocation, TermLoc );
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
	memset( txnmsg->ForwardBranchCode, 0, sizeof( txnmsg->ForwardBranchCode ) );
	strcpy( txnmsg->ForwardBranchCode,ForwardBranchCode );
	memset( txnmsg->FromAcctType, 0, sizeof( txnmsg->FromAcctType ) );
	strcpy( txnmsg->FromAcctType, FromAcctType );
	memset( txnmsg->FromAcctSubType, 0, sizeof( txnmsg->FromAcctSubType ) );
	strcpy( txnmsg->FromAcctSubType, FromAcctSubType );
	memset( txnmsg->ToAcctType, 0, sizeof( txnmsg->ToAcctType ) );
	strcpy( txnmsg->ToAcctType, ToAcctType );
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
	txnmsg->AuthCode = AuthCode;
	memset( txnmsg->AcceptorName, 0, sizeof( txnmsg->AcceptorName ) );
	strcpy( txnmsg->AcceptorName, AcceptorName );
	memset( txnmsg->AcquirerInst, 0, sizeof( txnmsg->AcquirerInst ) );
	strcpy( txnmsg->AcquirerInst, AcquirerInst );
	memset( txnmsg->IssuerInst, 0, sizeof( txnmsg->IssuerInst ) );
	strcpy( txnmsg->IssuerInst, IssuerInst );
	memset( txnmsg->ForwardInst, 0, sizeof( txnmsg->ForwardInst ) );
	strcpy( txnmsg->ForwardInst, ForwardInst );
	memset( txnmsg->AcquirerBin, 0, sizeof( txnmsg->AcquirerBin ) );
	strcpy( txnmsg->AcquirerBin, AcquirerBin );
	memset( txnmsg->IssuerBin, 0, sizeof( txnmsg->IssuerBin ) );
	strcpy( txnmsg->IssuerBin, IssuerBin );
	memset( txnmsg->ForwardBin, 0, sizeof( txnmsg->ForwardBin ) );
	strcpy( txnmsg->ForwardBin, ForwardBin );
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

	return 0;
}

int InsertEzTxnLog( struct EzTxnMsg *txnmsg )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int MsgType;
		int OrgMsgType;
		int TxnCode;
		char TerminalId[ 17 ];
		char TermLoc[ 65 ];
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
		char CHN[ 20 ];
		char AcqBranchCode[ 11 ];
		char IssBranchCode[ 11 ];
		char ForwardBranchCode[ 11 ];
		char FromAcctType[ 11 ];
		char FromAcctSubType[ 11 ];
		char ToAcctType[ 11 ];
		char ToAcctSubType[ 11 ];
		char AvailBalance[ 15 ];
		char LedgerBalance[ 15 ];
		char Amount[ 15 ];
		char TxnFee[ 15 ];
		char DispAmount[ 15 ];
		char FromAccount[ 33 ];
		char ToAccount[ 33 ];
		char RefNum[ 13 ];
		int  AuthCode;
		char AcceptorName[ 41 ];
		char AcquirerInst[ 11 ];
		char IssuerInst[ 11 ];
		char ForwardInst[ 11 ];
		char AcquirerBin[ 11 ];
		char IssuerBin[ 11 ];
		char ForwardBin[ 11 ];
		char Track2[ 40 ];
		char RsvFld1[ 50 ];
		char RsvFld2[ 50 ];
		char RsvFld3[ 50 ];
		char RsvFld4[ 50 ];
		char RsvFld5[ 50 ];
		char RsvFld6[ 50 ];
		char OrgChannel[ 33 ];
		char OrgPort[ 33 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

	/* EXEC SQL VAR TermLoc IS STRING(65); */ 

	/* EXEC SQL VAR CHN IS STRING(20); */ 

	/* EXEC SQL VAR AcqBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR IssBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR ForwardBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR FromAcctType IS STRING(11); */ 

	/* EXEC SQL VAR FromAcctSubType IS STRING(11); */ 

	/* EXEC SQL VAR ToAcctType IS STRING(11); */ 

	/* EXEC SQL VAR ToAcctSubType IS STRING(11); */ 

	/* EXEC SQL VAR AvailBalance IS STRING(11); */ 

	/* EXEC SQL VAR LedgerBalance IS STRING(11); */ 

	/* EXEC SQL VAR Amount IS STRING(15); */ 

	/* EXEC SQL VAR TxnFee IS STRING(15); */ 

	/* EXEC SQL VAR DispAmount IS STRING(15); */ 

	/* EXEC SQL VAR FromAccount IS STRING(33); */ 

	/* EXEC SQL VAR ToAccount IS STRING(33); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR AcceptorName IS STRING(41); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR AcquirerInst IS STRING(11); */ 

	/* EXEC SQL VAR IssuerInst IS STRING(11); */ 

	/* EXEC SQL VAR ForwardInst IS STRING(11); */ 

	/* EXEC SQL VAR AcquirerBin IS STRING(11); */ 

	/* EXEC SQL VAR IssuerBin IS STRING(11); */ 

	/* EXEC SQL VAR ForwardBin IS STRING(11); */ 

	/* EXEC SQL VAR Track2 IS STRING(40); */ 

	/* EXEC SQL VAR RsvFld1 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld2 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld3 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld4 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld5 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld6 IS STRING(50); */ 

	/* EXEC SQL VAR OrgChannel IS STRING(33); */ 

	/* EXEC SQL VAR OrgPort IS STRING(33); */ 


	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( CHN, 0, sizeof( CHN ) );
	memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
	memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
	memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
	memset( FromAcctType, 0, sizeof( FromAcctType ) );
	memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
	memset( ToAcctType, 0, sizeof( ToAcctType ) );
	memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
	memset( Amount, 0, sizeof( Amount ) );
	memset( DispAmount, 0, sizeof( DispAmount ) );
	memset( FromAccount, 0, sizeof( FromAccount ) );
	memset( ToAccount, 0, sizeof( ToAccount ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
	memset( IssuerInst, 0, sizeof( IssuerInst ) );
	memset( ForwardInst, 0, sizeof( ForwardInst ) );
	memset( AcquirerBin, 0, sizeof( AcquirerBin ) );
	memset( IssuerBin, 0, sizeof( IssuerBin ) );
	memset( ForwardBin, 0, sizeof( ForwardBin ) );
	memset( Track2, 0, sizeof( Track2 ) );
	memset( RsvFld1, 0, sizeof( RsvFld1 ) );
	memset( RsvFld2, 0, sizeof( RsvFld2 ) );
	memset( RsvFld3, 0, sizeof( RsvFld3 ) );
	memset( RsvFld4, 0, sizeof( RsvFld4 ) );
	memset( RsvFld5, 0, sizeof( RsvFld5 ) );
	memset( RsvFld6, 0, sizeof( RsvFld6 ) );
	memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	
	MsgType = txnmsg->MsgType;
	OrgMsgType = txnmsg->OrgMsgType;
	TxnCode = txnmsg->TxnCode;
	strcpy( TerminalId, txnmsg->TerminalId);
	strcpy( TermLoc, txnmsg->TerminalLocation );
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
	CaptureDate = txnmsg->CaptureDate;
	CaptureTime = txnmsg->CaptureTime;
	SettlementDate = txnmsg->SettlementDate;
	AcqCurrencyCode = txnmsg->AcqCurrencyCode;
	IssCurrencyCode = txnmsg->IssCurrencyCode;
	SettCurrencyCode = txnmsg->SettCurrencyCode;
	AcqConvRate = txnmsg->AcqConvRate;
	AcqConvDate = txnmsg->AcqConvDate;
	IssConvRate = txnmsg->IssConvRate;
	IssConvDate = txnmsg->IssConvDate;
	SettConvRate = txnmsg->SettConvRate;
	SettConvDate = txnmsg->SettConvDate;
	MerchantType = txnmsg->MerchantType;
	PosEntryCode = txnmsg->PosEntryCode;
	PosConditionCode = txnmsg->PosConditionCode;
	PosCapCode = txnmsg->PosCapCode;
	PosPinCapCode = txnmsg->PosPinCapCode;
	strcpy( CHN, txnmsg->chn );
	strcpy( AcqBranchCode, txnmsg->AcqBranchCode );
	strcpy( IssBranchCode, txnmsg->IssBranchCode );
	strcpy( ForwardBranchCode, txnmsg->ForwardBranchCode );
	strcpy( FromAcctType, txnmsg->FromAcctType );
	strcpy( FromAcctSubType, txnmsg->FromAcctSubType );
	strcpy( ToAcctType, txnmsg->ToAcctType );
	strcpy( ToAcctSubType, txnmsg->ToAcctSubType );
	strcpy( AvailBalance, txnmsg->AvailBalance );
	strcpy( LedgerBalance, txnmsg->LedgerBalance );
	strcpy( Amount, txnmsg->Amount );
	strcpy( TxnFee, txnmsg->TxnFee );
	strcpy( DispAmount, txnmsg->DispAmount );
	strcpy( FromAccount, txnmsg->FromAccount );
	strcpy( ToAccount, txnmsg->ToAccount );
	strcpy( RefNum, txnmsg->RefNum );
	AuthCode = txnmsg->AuthCode;
	strcpy( AcceptorName, txnmsg->AcceptorName );
	strcpy( AcquirerInst, txnmsg->AcquirerInst );
	strcpy( IssuerInst, txnmsg->IssuerInst );
	strcpy( ForwardInst, txnmsg->ForwardInst );
	strcpy( AcquirerBin, txnmsg->AcquirerBin );
	strcpy( IssuerBin, txnmsg->IssuerBin );
	strcpy( ForwardBin, txnmsg->ForwardBin );
	strcpy( Track2, txnmsg->Track2 );
	strcpy( RsvFld1, txnmsg->RsvFld1 );
	strcpy( RsvFld2, txnmsg->RsvFld2 );
	strcpy( RsvFld3, txnmsg->RsvFld3 );
	strcpy( RsvFld4, txnmsg->RsvFld4 );
	strcpy( RsvFld5, txnmsg->RsvFld5 );
	strcpy( RsvFld6, txnmsg->RsvFld6 );
	strcpy( OrgChannel, txnmsg->OrgChannel );
	strcpy( OrgPort, txnmsg->OrgPort );

	/* EXEC SQL INSERT INTO EZTXNLOG (
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
		CHN,
		ACQBRANCHCODE,
		ISSBRANCHCODE,
		FORWARDBRANCHCODE,
		FROMACCTTYPE,
		FROMACCTSUBTYPE,
		TOACCTTYPE,
		TOACCTSUBTYPE,
		AVAILBALANCE,
		LEDGERBALANCE,
		AMOUNT,
		TXNFEE,
		DISPAMOUNT,
		FROMACCOUNT,
		TOACCOUNT,
		REFNUM,
		AUTHCODE,
		ACCEPTORNAME,
		ACQUIRERINST,
		ISSUERINST,
		FORWARDINST,
		ACQUIRERBIN,
		ISSUERBIN,
		FORWARDBIN,
		TRACK2,
		RSVFLD1,
		RSVFLD2,
		RSVFLD3,
		RSVFLD4,
		RSVFLD5,
		RSVFLD6,
		ORGCHANNEL,
		ORGPORT
		)
		VALUES(
		:MsgType,
		:OrgMsgType:ind_var,
		:TxnCode,
		:TerminalId,
		:TermLoc:ind_var,
		:TraceNo,
		:OrgTraceNo:ind_var,
		:TranDate,
		:TranTime,
		:OrgTranDate:ind_var,
		:OrgTranTime:ind_var,
		:LocalDate,
		:LocalTime,
		:RespCode,
		:RevCode:ind_var,
		:ReasonCode:ind_var,
		:CaptureDate:ind_var,
		:CaptureTime:ind_var,
		:SettlementDate:ind_var,
		:AcqCurrencyCode,
		:AcqConvRate:ind_var,
		:AcqConvDate:ind_var,
		:IssCurrencyCode,
		:IssConvRate:ind_var,
		:IssConvDate:ind_var,
		:SettCurrencyCode:ind_var,
		:SettConvRate:ind_var,
		:SettConvDate:ind_var,
		:MerchantType,
		:PosEntryCode:ind_var,
		:PosConditionCode:ind_var,
		:PosCapCode:ind_var,
		:PosPinCapCode:ind_var,
		:CHN,
		:AcqBranchCode,
		:IssBranchCode,
		:ForwardBranchCode:ind_var,
		:FromAcctType:ind_var,
		:FromAcctSubType:ind_var,
		:ToAcctType:ind_var,
		:ToAcctSubType:ind_var,
		:AvailBalance:ind_var,
		:LedgerBalance:ind_var,
		:Amount:ind_var,
		:TxnFee:ind_var,
		:DispAmount:ind_var,
		:FromAccount:ind_var,
		:ToAccount:ind_var,
		:RefNum:ind_var,
		:AuthCode:ind_var,
		:AcceptorName:ind_var,
		:AcquirerInst,
		:IssuerInst,
		:ForwardInst:ind_var,
		:AcquirerBin,
		:IssuerBin,
		:ForwardBin:ind_var,
		:Track2:ind_var,
		:RsvFld1:ind_var,
		:RsvFld2:ind_var,
		:RsvFld3:ind_var,
		:RsvFld4:ind_var,
		:RsvFld5:ind_var,
		:RsvFld6:ind_var,
		:OrgChannel,
		:OrgPort
		); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 73;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "insert into EZTXNLOG (MSGTYPE,ORGMSGTYPE,TXNCODE,TERMINALID,TERMLOC,TRAC\
ENO,ORGTRACENO,TRANDATE,TRANTIME,ORGTRANDATE,ORGTRANTIME,LOCALDATE,LOCALTIME\
,RESPCODE,REVCODE,REASONCODE,CAPTUREDATE,CAPTURETIME,SETTLEMENTDATE,ACQCURRE\
NCYCODE,ACQCONVRATE,ACQCONVDATE,ISSCURRENCYCODE,ISSCONVRATE,ISSCONVDATE,SETT\
CURRENCYCODE,SETTCONVRATE,SETTCONVDATE,MERCHANTTYPE,POSENTRYCODE,POSCONDITIO\
NCODE,POSCAPCODE,POSPINCAPCODE,CHN,ACQBRANCHCODE,ISSBRANCHCODE,FORWARDBRANCH\
CODE,FROMACCTTYPE,FROMACCTSUBTYPE,TOACCTTYPE,TOACCTSUBTYPE,AVAILBALANCE,LEDG\
ERBALANCE,AMOUNT,TXNFEE,DISPAMOUNT,FROMACCOUNT,TOACCOUNT,REFNUM,AUTHCODE,ACC\
EPTORNAME,ACQUIRERINST,ISSUERINST,FORWARDINST,ACQUIRERBIN,ISSUERBIN,FORWARDB\
IN,TRACK2,RSVFLD1,RSVFLD2,RSVFLD3,RSVFLD4,RSVFLD5,RSVFLD6,ORGCHANNEL,ORGPORT\
) values (:b0,:b1:b2,:b3,:b4,:b5:b6,:b7,:b8:b9,:b10,:b11,:b12:b13,:b14:b15,:\
b16,:b17,:b18,:b19:b20,:b21:b22,:b23:b24,:b25:b26,:b27:b28,:b29,:b30:b31,:b3\
2:b33,:b34,:b35:b36,:b37:b38,:b39:b40,:b41:b42,:b43:b44,:b45,:b46:b47,:b48:b\
49,:b50:b51,:b52:b53,:b54,:b55,:b56,:b57");
 sqlstm.stmt = ":b58,:b59:b60,:b61:b62,:b63:b64,:b65:b66,:b67:b68,:b69:b70,:\
b71:b72,:b73:b74,:b75:b76,:b77:b78,:b79:b80,:b81:b82,:b83:b84,:b85:b86,:b87,:b\
88,:b89:b90,:b91,:b92,:b93:b94,:b95:b96,:b97:b98,:b99:b100,:b101:b102,:b103:b1\
04,:b105:b106,:b107:b108,:b109,:b110)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )312;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&MsgType;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
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
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)TerminalId;
 sqlstm.sqhstl[3] = (unsigned int  )17;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)TermLoc;
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
 sqlstm.sqindv[5] = (         void  *)0;
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
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&TranTime;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
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
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&LocalTime;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&RespCode;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
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
 sqlstm.sqhstv[16] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)&ind_var;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)&ind_var;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)&ind_var;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)&ind_var;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)&ind_var;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)&ind_var;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)&ind_var;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)&ind_var;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)&ind_var;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)&ind_var;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)&MerchantType;
 sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)&ind_var;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)&ind_var;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[31] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)&ind_var;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[32] = (unsigned int  )1;
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)&ind_var;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)CHN;
 sqlstm.sqhstl[33] = (unsigned int  )20;
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[34] = (unsigned int  )11;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[35] = (unsigned int  )11;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[36] = (unsigned int  )11;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)&ind_var;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)FromAcctType;
 sqlstm.sqhstl[37] = (unsigned int  )11;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)&ind_var;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[38] = (unsigned int  )11;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)&ind_var;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)ToAcctType;
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
 sqlstm.sqhstl[41] = (unsigned int  )11;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)&ind_var;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[42] = (unsigned int  )11;
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
 sqlstm.sqhstv[49] = (         void  *)&AuthCode;
 sqlstm.sqhstl[49] = (unsigned int  )sizeof(int);
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
 sqlstm.sqhstl[51] = (unsigned int  )11;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)0;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)IssuerInst;
 sqlstm.sqhstl[52] = (unsigned int  )11;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)0;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)ForwardInst;
 sqlstm.sqhstl[53] = (unsigned int  )11;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)&ind_var;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)AcquirerBin;
 sqlstm.sqhstl[54] = (unsigned int  )11;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)0;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)IssuerBin;
 sqlstm.sqhstl[55] = (unsigned int  )11;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)0;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)ForwardBin;
 sqlstm.sqhstl[56] = (unsigned int  )11;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)&ind_var;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)Track2;
 sqlstm.sqhstl[57] = (unsigned int  )40;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)&ind_var;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)RsvFld1;
 sqlstm.sqhstl[58] = (unsigned int  )50;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)&ind_var;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)RsvFld2;
 sqlstm.sqhstl[59] = (unsigned int  )50;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)&ind_var;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)RsvFld3;
 sqlstm.sqhstl[60] = (unsigned int  )50;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)&ind_var;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)RsvFld4;
 sqlstm.sqhstl[61] = (unsigned int  )50;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)&ind_var;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)RsvFld5;
 sqlstm.sqhstl[62] = (unsigned int  )50;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)&ind_var;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)RsvFld6;
 sqlstm.sqhstl[63] = (unsigned int  )50;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)&ind_var;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)OrgChannel;
 sqlstm.sqhstl[64] = (unsigned int  )33;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)0;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)OrgPort;
 sqlstm.sqhstl[65] = (unsigned int  )33;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)0;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
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
  sqlstm.arrsiz = 73;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )591;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	        return 0;
	}
}

int UpdateEzTxnLog( struct EzTxnMsg *txnmsg, const char *IndxName )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		int MsgType;
		int OrgMsgType;
		int TxnCode;
		char TerminalId[ 17 ];
		char TermLoc[ 65 ];
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
		char CHN[ 20 ];
		char AcqBranchCode[ 11 ];
		char IssBranchCode[ 11 ];
		char ForwardBranchCode[ 11 ];
		char FromAcctType[ 11 ];
		char FromAcctSubType[ 11 ];
		char ToAcctType[ 11 ];
		char ToAcctSubType[ 11 ];
		char AvailBalance[ 15 ];
		char LedgerBalance[ 15 ];
		char Amount[ 15 ];
		char TxnFee[ 15 ];
		char DispAmount[ 15 ];
		char FromAccount[ 33 ];
		char ToAccount[ 33 ];
		char RefNum[ 13 ];
		int AuthCode;
		char AcceptorName[ 41 ];
		char AcquirerInst[ 11 ];
		char IssuerInst[ 11 ];
		char ForwardInst[ 11 ];
		char AcquirerBin[ 11 ];
		char IssuerBin[ 11 ];
		char ForwardBin[ 11 ];
		char Track2[ 40 ];
		char RsvFld1[ 50 ];
		char RsvFld2[ 50 ];
		char RsvFld3[ 50 ];
		char RsvFld4[ 50 ];
		char RsvFld5[ 50 ];
		char RsvFld6[ 50 ];
		char OrgChannel[ 33 ];
		char OrgPort[ 33 ];
		short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 

	
	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

	/* EXEC SQL VAR TermLoc IS STRING(65); */ 

	/* EXEC SQL VAR CHN IS STRING(20); */ 

	/* EXEC SQL VAR AcqBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR IssBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR ForwardBranchCode IS STRING(11); */ 

	/* EXEC SQL VAR FromAcctType IS STRING(11); */ 

	/* EXEC SQL VAR FromAcctSubType IS STRING(11); */ 

	/* EXEC SQL VAR ToAcctType IS STRING(11); */ 

	/* EXEC SQL VAR ToAcctSubType IS STRING(11); */ 

	/* EXEC SQL VAR AvailBalance IS STRING(11); */ 

	/* EXEC SQL VAR LedgerBalance IS STRING(11); */ 

	/* EXEC SQL VAR Amount IS STRING(15); */ 

	/* EXEC SQL VAR TxnFee IS STRING(15); */ 

	/* EXEC SQL VAR DispAmount IS STRING(15); */ 

	/* EXEC SQL VAR FromAccount IS STRING(33); */ 

	/* EXEC SQL VAR ToAccount IS STRING(33); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR AcceptorName IS STRING(41); */ 

	/* EXEC SQL VAR RefNum IS STRING(13); */ 

	/* EXEC SQL VAR AcquirerInst IS STRING(11); */ 

	/* EXEC SQL VAR IssuerInst IS STRING(11); */ 

	/* EXEC SQL VAR ForwardInst IS STRING(11); */ 

	/* EXEC SQL VAR AcquirerBin IS STRING(11); */ 

	/* EXEC SQL VAR IssuerBin IS STRING(11); */ 

	/* EXEC SQL VAR ForwardBin IS STRING(11); */ 

	/* EXEC SQL VAR Track2 IS STRING(40); */ 

	/* EXEC SQL VAR RsvFld1 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld2 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld3 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld4 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld5 IS STRING(50); */ 

	/* EXEC SQL VAR RsvFld6 IS STRING(50); */ 

	/* EXEC SQL VAR OrgChannel IS STRING(33); */ 

	/* EXEC SQL VAR OrgPort IS STRING(33); */ 


	memset( TerminalId, 0, sizeof( TerminalId ) );
	memset( TermLoc, 0, sizeof( TermLoc ) );
	memset( CHN, 0, sizeof( CHN ) );
	memset( AcqBranchCode, 0, sizeof( AcqBranchCode ) );
	memset( IssBranchCode, 0, sizeof( IssBranchCode ) );
	memset( ForwardBranchCode, 0, sizeof( ForwardBranchCode ) );
	memset( FromAcctType, 0, sizeof( FromAcctType ) );
	memset( FromAcctSubType, 0, sizeof( FromAcctSubType ) );
	memset( ToAcctType, 0, sizeof( ToAcctType ) );
	memset( ToAcctSubType, 0, sizeof( ToAcctSubType ) );
	memset( Amount, 0, sizeof( Amount ) );
	memset( DispAmount, 0, sizeof( DispAmount ) );
	memset( FromAccount, 0, sizeof( FromAccount ) );
	memset( ToAccount, 0, sizeof( ToAccount ) );
	memset( RefNum, 0, sizeof( RefNum ) );
	memset( AcquirerInst, 0, sizeof( AcquirerInst ) );
	memset( IssuerInst, 0, sizeof( IssuerInst ) );
	memset( ForwardInst, 0, sizeof( ForwardInst ) );
	memset( AcquirerBin, 0, sizeof( AcquirerBin ) );
	memset( IssuerBin, 0, sizeof( IssuerBin ) );
	memset( ForwardBin, 0, sizeof( ForwardBin ) );
	memset( Track2, 0, sizeof( Track2 ) );
	memset( RsvFld1, 0, sizeof( RsvFld1 ) );
	memset( RsvFld2, 0, sizeof( RsvFld2 ) );
	memset( RsvFld3, 0, sizeof( RsvFld3 ) );
	memset( RsvFld4, 0, sizeof( RsvFld4 ) );
	memset( RsvFld5, 0, sizeof( RsvFld5 ) );
	memset( RsvFld6, 0, sizeof( RsvFld6 ) );
	memset( OrgChannel, 0, sizeof( OrgChannel ) );
	memset( OrgPort, 0, sizeof( OrgPort ) );
	
	MsgType = txnmsg->MsgType;
	OrgMsgType = txnmsg->OrgMsgType;
	TxnCode = txnmsg->TxnCode;
	strcpy( TerminalId, txnmsg->TerminalId);
	strcpy( TermLoc, txnmsg->TerminalLocation );
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
	CaptureDate = txnmsg->CaptureDate;
	CaptureTime = txnmsg->CaptureTime;
	SettlementDate = txnmsg->SettlementDate;
	AcqCurrencyCode = txnmsg->AcqCurrencyCode;
	IssCurrencyCode = txnmsg->IssCurrencyCode;
	SettCurrencyCode = txnmsg->SettCurrencyCode;
	AcqConvRate = txnmsg->AcqConvRate;
	AcqConvDate = txnmsg->AcqConvDate;
	IssConvRate = txnmsg->IssConvRate;
	IssConvDate = txnmsg->IssConvDate;
	SettConvRate = txnmsg->SettConvRate;
	SettConvDate = txnmsg->SettConvDate;
	MerchantType = txnmsg->MerchantType;
	PosEntryCode = txnmsg->PosEntryCode;
	PosConditionCode = txnmsg->PosConditionCode;
	PosCapCode = txnmsg->PosCapCode;
	PosPinCapCode = txnmsg->PosPinCapCode;
	strcpy( CHN, txnmsg->chn);
	strcpy( AcqBranchCode, txnmsg->AcqBranchCode);
	strcpy( IssBranchCode, txnmsg->IssBranchCode);
	strcpy( ForwardBranchCode, txnmsg->ForwardBranchCode);
	strcpy( FromAcctType, txnmsg->FromAcctType);
	strcpy( FromAcctSubType, txnmsg->FromAcctSubType);
	strcpy( ToAcctType, txnmsg->ToAcctType);
	strcpy( ToAcctSubType, txnmsg->ToAcctSubType);
	strcpy( AvailBalance, txnmsg->AvailBalance);
	strcpy( LedgerBalance, txnmsg->LedgerBalance);
	strcpy( Amount, txnmsg->Amount);
	strcpy( TxnFee, txnmsg->TxnFee);
	strcpy( DispAmount, txnmsg->DispAmount);
	strcpy( FromAccount, txnmsg->FromAccount);
	strcpy( ToAccount, txnmsg->ToAccount);
	strcpy( RefNum, txnmsg->RefNum);
	AuthCode = txnmsg->AuthCode;
	strcpy( AcceptorName, txnmsg->AcceptorName);
	strcpy( AcquirerInst, txnmsg->AcquirerInst);
	strcpy( IssuerInst, txnmsg->IssuerInst);
	strcpy( ForwardInst, txnmsg->ForwardInst);
	strcpy( AcquirerBin, txnmsg->AcquirerBin);
	strcpy( IssuerBin, txnmsg->IssuerBin);
	strcpy( ForwardBin, txnmsg->ForwardBin);
	strcpy( Track2, txnmsg->Track2);
	strcpy( RsvFld1, txnmsg->RsvFld1);
	strcpy( RsvFld2, txnmsg->RsvFld2);
	strcpy( RsvFld3, txnmsg->RsvFld3);
	strcpy( RsvFld4, txnmsg->RsvFld4);
	strcpy( RsvFld5, txnmsg->RsvFld5);
	strcpy( RsvFld6, txnmsg->RsvFld6);
	strcpy( OrgChannel, txnmsg->OrgChannel );
	strcpy( OrgPort, txnmsg->OrgPort );

	/* EXEC SQL UPDATE INTO EZTXNLOG SET
		MSGTYPE = :MsgType,
		ORGMSGTYPE = :OrgMsgType,
		TERMLOC = :TermLoc,
		ORGTRACENO = :OrgTraceNo,
		TRANDATE = :TranDate,
		TRANTIME = :TranTime,
		ORGTRANDATE = :OrgTranDate,
		ORGTRANTIME = :OrgTranTime,
		RESPCODE = :RespCode,
		REVCODE = :RevCode,
		REASONCODE = :ReasonCode,
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
		ACQBRANCHCODE = :AcqBranchCode,
		ISSBRANCHCODE = :IssBranchCode,
		FORWARDBRANCHCODE = :ForwardBranchCode,
		FROMACCTTYPE = :FromAcctType,
		FROMACCTSUBTYPE = :FromAcctSubType,
		TOACCTTYPE = :ToAcctType,
		TOACCTSUBTYPE = :ToAcctSubType,
		AVAILBALANCE = :AvailBalance,
		LEDGERBALANCE = :LedgerBalance,
		AMOUNT = :Amount,
		TXNFEE = :TxnFee,
		DISPAMOUNT = :DispAmount,
		FROMACCOUNT = :FromAccount,
		TOACCOUNT = :ToAccount,
		REFNUM = :RefNum,
		AUTHCODE = :AuthCode,
		ACCEPTORNAME = :AcceptorName,
		ACQUIRERINST = :AcquirerInst,
		ISSUERINST = :IssuerInst,
		FORWARDINST = :ForwardInst,
		ACQUIRERBIN = :AcquirerBin,
		ISSUERBIN = :IssuerBin,
		FORWARDBIN = :ForwardBin,
		TRACK2 = :Track2,
		RSVFLD1 = :RsvFld1,
		RSVFLD2 = :RsvFld2,
		RSVFLD3 = :RsvFld3,
		RSVFLD4 = :RsvFld4,
		RSVFLD5 = :RsvFld5,
		RSVFLD6 = :RsvFld6,
		ORGCHANNEL = :OrgChannel,
		ORGPORT = :OrgPort
	WHERE RTRIM(ISSUERINST)=:IssuerInst AND RTRIM(CHN)=:CHN AND TRACENO=:TraceNo AND RTRIM(TERMID)=:TerminalId AND LOCALDATE=:LocalDate AND LOCALTIME=LocalTime AND TXNCODE=:TxnCode; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 73;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "update INTO EZTXNLOG  set MSGTYPE=:b0,ORGMSGTYPE=:b1,TERMLOC=:b2,ORGTRAC\
ENO=:b3,TRANDATE=:b4,TRANTIME=:b5,ORGTRANDATE=:b6,ORGTRANTIME=:b7,RESPCODE=:\
b8,REVCODE=:b9,REASONCODE=:b10,CAPTUREDATE=:b11,CAPTURETIME=:b12,SETTLEMENTD\
ATE=:b13,ACQCURRENCYCODE=:b14,ACQCONVRATE=:b15,ACQCONVDATE=:b16,ISSCURRENCYC\
ODE=:b17,ISSCONVRATE=:b18,ISSCONVDATE=:b19,SETTCURRENCYCODE=:b20,SETTCONVRAT\
E=:b21,SETTCONVDATE=:b22,MERCHANTTYPE=:b23,POSENTRYCODE=:b24,POSCONDITIONCOD\
E=:b25,POSCAPCODE=:b26,POSPINCAPCODE=:b27,ACQBRANCHCODE=:b28,ISSBRANCHCODE=:\
b29,FORWARDBRANCHCODE=:b30,FROMACCTTYPE=:b31,FROMACCTSUBTYPE=:b32,TOACCTTYPE\
=:b33,TOACCTSUBTYPE=:b34,AVAILBALANCE=:b35,LEDGERBALANCE=:b36,AMOUNT=:b37,TX\
NFEE=:b38,DISPAMOUNT=:b39,FROMACCOUNT=:b40,TOACCOUNT=:b41,REFNUM=:b42,AUTHCO\
DE=:b43,ACCEPTORNAME=:b44,ACQUIRERINST=:b45,ISSUERINST=:b46,FORWARDINST=:b47\
,ACQUIRERBIN=:b48,ISSUERBIN=:b49,FORWARDBIN=:b50,TRACK2=:b51,RSVFLD1=:b52,RS\
VFLD2=:b53,RSVFLD3=:b54,RSVFLD4=:b55,RSVFLD5=:b56,RSVFLD6=:b57,ORGCHANNEL=:b\
58,ORGPORT=:b59 where ((((((RTRIM(ISSUER");
 sqlstm.stmt = "INST)=:b46 and RTRIM(CHN)=:b61) and TRACENO=:b62) and RTRIM(\
TERMID)=:b63) and LOCALDATE=:b64) and LOCALTIME=LocalTime) and TXNCODE=:b65)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )606;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&MsgType;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&OrgMsgType;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)TermLoc;
 sqlstm.sqhstl[2] = (unsigned int  )65;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&OrgTraceNo;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&TranDate;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&TranTime;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&OrgTranDate;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&OrgTranTime;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&RespCode;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&RevCode;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&ReasonCode;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)0;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[13] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[14] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)0;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)0;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)0;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)0;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)0;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&MerchantType;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)0;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)0;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)0;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)0;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[27] = (unsigned int  )1;
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)0;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[28] = (unsigned int  )11;
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)0;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[29] = (unsigned int  )11;
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)0;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[30] = (unsigned int  )11;
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)0;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)FromAcctType;
 sqlstm.sqhstl[31] = (unsigned int  )11;
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)0;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[32] = (unsigned int  )11;
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)0;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)ToAcctType;
 sqlstm.sqhstl[33] = (unsigned int  )11;
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)0;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)ToAcctSubType;
 sqlstm.sqhstl[34] = (unsigned int  )11;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)0;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)AvailBalance;
 sqlstm.sqhstl[35] = (unsigned int  )11;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[36] = (unsigned int  )11;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)0;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)Amount;
 sqlstm.sqhstl[37] = (unsigned int  )15;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)0;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)TxnFee;
 sqlstm.sqhstl[38] = (unsigned int  )15;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)0;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)DispAmount;
 sqlstm.sqhstl[39] = (unsigned int  )15;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)0;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)FromAccount;
 sqlstm.sqhstl[40] = (unsigned int  )33;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)0;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)ToAccount;
 sqlstm.sqhstl[41] = (unsigned int  )33;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)0;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)RefNum;
 sqlstm.sqhstl[42] = (unsigned int  )13;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)0;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)&AuthCode;
 sqlstm.sqhstl[43] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)0;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)AcceptorName;
 sqlstm.sqhstl[44] = (unsigned int  )41;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)0;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)AcquirerInst;
 sqlstm.sqhstl[45] = (unsigned int  )11;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)0;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)IssuerInst;
 sqlstm.sqhstl[46] = (unsigned int  )11;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)0;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)ForwardInst;
 sqlstm.sqhstl[47] = (unsigned int  )11;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)0;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)AcquirerBin;
 sqlstm.sqhstl[48] = (unsigned int  )11;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)0;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)IssuerBin;
 sqlstm.sqhstl[49] = (unsigned int  )11;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)0;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)ForwardBin;
 sqlstm.sqhstl[50] = (unsigned int  )11;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)0;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
 sqlstm.sqhstv[51] = (         void  *)Track2;
 sqlstm.sqhstl[51] = (unsigned int  )40;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)0;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)RsvFld1;
 sqlstm.sqhstl[52] = (unsigned int  )50;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)0;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)RsvFld2;
 sqlstm.sqhstl[53] = (unsigned int  )50;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)0;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)RsvFld3;
 sqlstm.sqhstl[54] = (unsigned int  )50;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)0;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)RsvFld4;
 sqlstm.sqhstl[55] = (unsigned int  )50;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)0;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)RsvFld5;
 sqlstm.sqhstl[56] = (unsigned int  )50;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)0;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)RsvFld6;
 sqlstm.sqhstl[57] = (unsigned int  )50;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)0;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)OrgChannel;
 sqlstm.sqhstl[58] = (unsigned int  )33;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)0;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)OrgPort;
 sqlstm.sqhstl[59] = (unsigned int  )33;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)0;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)IssuerInst;
 sqlstm.sqhstl[60] = (unsigned int  )11;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)0;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)CHN;
 sqlstm.sqhstl[61] = (unsigned int  )20;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)0;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)&TraceNo;
 sqlstm.sqhstl[62] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)0;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)TerminalId;
 sqlstm.sqhstl[63] = (unsigned int  )17;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)0;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)&LocalDate;
 sqlstm.sqhstl[64] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)0;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)&TxnCode;
 sqlstm.sqhstl[65] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)0;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
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
  sqlstm.arrsiz = 73;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )885;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)256;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	        return 0;
	}
}

