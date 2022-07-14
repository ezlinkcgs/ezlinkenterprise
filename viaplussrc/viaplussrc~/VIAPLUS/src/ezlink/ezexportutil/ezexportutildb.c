
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
           char  filnam[18];
};
static struct sqlcxp sqlfpn =
{
    17,
    "ezexportutildb.pc"
};


static unsigned int sqlctx = 9980587;


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
            void  *sqhstv[76];
   unsigned int   sqhstl[76];
            int   sqhsts[76];
            void  *sqindv[76];
            int   sqinds[76];
   unsigned int   sqharm[76];
   unsigned int   *sqharc[76];
   unsigned short  sqadto[76];
   unsigned short  sqtdso[76];
} sqlstm = {12,76};

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
5,0,0,1,1464,0,3,240,0,0,72,72,0,1,0,1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,
5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,
1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,1,
0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
308,0,0,2,0,0,29,395,0,0,0,0,0,1,0,
323,0,0,3,74,0,4,414,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
346,0,0,4,1534,0,3,670,0,0,76,76,0,1,0,1,5,0,0,1,5,0,0,1,1,0,0,1,1,0,0,1,3,0,0,
1,5,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,0,1,3,0,0,1,3,0,0,1,5,0,0,1,5,0,
0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,
0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,
3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,3,0,0,1,1,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,
1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,
0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,
0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,5,0,0,1,
5,0,0,1,5,0,0,1,5,0,0,
665,0,0,5,0,0,29,833,0,0,0,0,0,1,0,
680,0,0,6,73,0,4,852,0,0,2,1,0,1,0,2,5,0,0,1,5,0,0,
};


#include <sqlca.h>
#include <stdlib.h>
#include <string.h>
#include <ezlink/ezlnkmsg.h>

int insertEzTxnLog( struct EzTxnMsg *txnmsg, const char *I_TxnRefNum )
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

	/* EXEC SQL INSERT INTO EZTXNLOG
	(
		TXNREFNUM,
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
	VALUES
	(
		:TxnRefNum,
		:MsgType,
        :OrgMsgType:ind_var,
        :TxnCode,
        :TerminalId,
        :TerminalLocation:ind_var,
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
        :MerchantType,
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
        :OrgPort:ind_var
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 72;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "insert into EZTXNLOG (TXNREFNUM,MSGTYPE,ORGMSGTYPE,TXNCODE,TERMINALID,TE\
RMLOC,TRACENO,ORGTRACENO,TRANDATE,TRANTIME,ORGTRANDATE,ORGTRANTIME,LOCALDATE\
,LOCALTIME,RESPCODE,REVCODE,REASONCODE,AUTHCODE,CAPTUREDATE,CAPTURETIME,SETT\
LEMENTDATE,ACQCURRENCYCODE,ACQCONVRATE,ACQCONVDATE,ISSCURRENCYCODE,ISSCONVRA\
TE,ISSCONVDATE,SETTCURRENCYCODE,SETTCONVRATE,SETTCONVDATE,MERCHANTTYPE,POSEN\
TRYCODE,POSCONDITIONCODE,POSCAPCODE,POSPINCAPCODE,CHN,ACQBRANCHCODE,ISSBRANC\
HCODE,TXFBRANCHCODE,FORWARDBRANCHCODE,FROMACCTSUBTYPE,TOACCTSUBTYPE,AVAILBAL\
ANCE,LEDGERBALANCE,AMOUNT,TXNFEE,DISPAMOUNT,FROMACCOUNT,TOACCOUNT,REFNUM,AUT\
HNUM,ACCEPTORNAME,ACQUIRERINST,ISSUERINST,FORWARDINST,TXFINST,SETTINST,NETWO\
RKID,ACQNETWORKID,ISSUERNETWORKID,FWDNETWORKID,TXFNETWORKID,SETTNETWORKID,TR\
ACK2,RSVFLD1,RSVFLD2,RSVFLD3,RSVFLD4,RSVFLD5,RSVFLD6,ORGCHANNEL,ORGPORT) val\
ues (:b0,:b1,:b2:b3,:b4,:b5,:b6:b7,:b8,:b9:b10,:b11,:b12,:b13:b14,:b15:b16,:\
b17,:b18,:b19,:b20:b21,:b22:b23,:b24:b25,:b26:b27,:b28:b29,:b30:b31,:b32:b33\
,:b34:b35,:b36:b37,:b38:b39,:b40:b41,:b4");
 sqlstm.stmt = "2:b43,:b44:b45,:b46:b47,:b48:b49,:b50,:b51:b52,:b53:b54,:b55\
:b56,:b57:b58,:b59:b60,:b61:b62,:b63:b64,:b65:b66,:b67:b68,:b69:b70,:b71:b72,:\
b73:b74,:b75:b76,:b77:b78,:b79:b80,:b81:b82,:b83:b84,:b85:b86,:b87:b88,:b89:b9\
0,:b91:b92,:b93:b94,:b95:b96,:b97:b98,:b99:b100,:b101:b102,:b103:b104,:b105:b1\
06,:b107:b108,:b109:b110,:b111:b112,:b113:b114,:b115:b116,:b117:b118,:b119:b12\
0,:b121:b122,:b123:b124,:b125:b126,:b127:b128,:b129:b130,:b131:b132)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
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
 sqlstm.sqhstv[2] = (         void  *)&OrgMsgType;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)&ind_var;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&TxnCode;
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
 sqlstm.sqindv[5] = (         void  *)&ind_var;
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
 sqlstm.sqindv[7] = (         void  *)&ind_var;
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
 sqlstm.sqindv[10] = (         void  *)&ind_var;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&OrgTranTime;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)&ind_var;
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
 sqlstm.sqindv[15] = (         void  *)&ind_var;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&ReasonCode;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)&ind_var;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&AuthCode;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)&ind_var;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)&ind_var;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)&ind_var;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)&ind_var;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)&ind_var;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)&ind_var;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)&ind_var;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)&ind_var;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)&ind_var;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)&ind_var;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)&ind_var;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)&ind_var;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)&ind_var;
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
 sqlstm.sqindv[31] = (         void  *)&ind_var;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[32] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)&ind_var;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[33] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)&ind_var;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[34] = (unsigned int  )1;
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)&ind_var;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)chn;
 sqlstm.sqhstl[35] = (unsigned int  )20;
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)&ind_var;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[36] = (unsigned int  )11;
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)&ind_var;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[37] = (unsigned int  )11;
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)&ind_var;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)TxfBranchCode;
 sqlstm.sqhstl[38] = (unsigned int  )11;
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)&ind_var;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[39] = (unsigned int  )11;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)&ind_var;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[40] = (unsigned int  )11;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)&ind_var;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)ToAcctSubType;
 sqlstm.sqhstl[41] = (unsigned int  )11;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)&ind_var;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)AvailBalance;
 sqlstm.sqhstl[42] = (unsigned int  )15;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)&ind_var;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[43] = (unsigned int  )15;
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)&ind_var;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)Amount;
 sqlstm.sqhstl[44] = (unsigned int  )15;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)&ind_var;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)TxnFee;
 sqlstm.sqhstl[45] = (unsigned int  )15;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)&ind_var;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)DispAmount;
 sqlstm.sqhstl[46] = (unsigned int  )15;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)&ind_var;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)FromAccount;
 sqlstm.sqhstl[47] = (unsigned int  )33;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)&ind_var;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)ToAccount;
 sqlstm.sqhstl[48] = (unsigned int  )33;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)&ind_var;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)RefNum;
 sqlstm.sqhstl[49] = (unsigned int  )13;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)&ind_var;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)AuthNum;
 sqlstm.sqhstl[50] = (unsigned int  )13;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)&ind_var;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
 sqlstm.sqhstv[51] = (         void  *)AcceptorName;
 sqlstm.sqhstl[51] = (unsigned int  )41;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)&ind_var;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)AcquirerInst;
 sqlstm.sqhstl[52] = (unsigned int  )13;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)&ind_var;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)IssuerInst;
 sqlstm.sqhstl[53] = (unsigned int  )13;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)&ind_var;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)ForwardInst;
 sqlstm.sqhstl[54] = (unsigned int  )13;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)&ind_var;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)TxfInst;
 sqlstm.sqhstl[55] = (unsigned int  )13;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)&ind_var;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)SettInst;
 sqlstm.sqhstl[56] = (unsigned int  )13;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)&ind_var;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)NetworkId;
 sqlstm.sqhstl[57] = (unsigned int  )17;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)&ind_var;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)AcqNetworkId;
 sqlstm.sqhstl[58] = (unsigned int  )17;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)&ind_var;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)IssuerNetworkId;
 sqlstm.sqhstl[59] = (unsigned int  )17;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)&ind_var;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)FwdNetworkId;
 sqlstm.sqhstl[60] = (unsigned int  )17;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)&ind_var;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)TxfNetworkId;
 sqlstm.sqhstl[61] = (unsigned int  )17;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)&ind_var;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)SettNetworkId;
 sqlstm.sqhstl[62] = (unsigned int  )17;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)&ind_var;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)Track2;
 sqlstm.sqhstl[63] = (unsigned int  )40;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)&ind_var;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)RsvFld1;
 sqlstm.sqhstl[64] = (unsigned int  )513;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)&ind_var;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)RsvFld2;
 sqlstm.sqhstl[65] = (unsigned int  )513;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)&ind_var;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
 sqlstm.sqhstv[66] = (         void  *)RsvFld3;
 sqlstm.sqhstl[66] = (unsigned int  )51;
 sqlstm.sqhsts[66] = (         int  )0;
 sqlstm.sqindv[66] = (         void  *)&ind_var;
 sqlstm.sqinds[66] = (         int  )0;
 sqlstm.sqharm[66] = (unsigned int  )0;
 sqlstm.sqadto[66] = (unsigned short )0;
 sqlstm.sqtdso[66] = (unsigned short )0;
 sqlstm.sqhstv[67] = (         void  *)RsvFld4;
 sqlstm.sqhstl[67] = (unsigned int  )51;
 sqlstm.sqhsts[67] = (         int  )0;
 sqlstm.sqindv[67] = (         void  *)&ind_var;
 sqlstm.sqinds[67] = (         int  )0;
 sqlstm.sqharm[67] = (unsigned int  )0;
 sqlstm.sqadto[67] = (unsigned short )0;
 sqlstm.sqtdso[67] = (unsigned short )0;
 sqlstm.sqhstv[68] = (         void  *)RsvFld5;
 sqlstm.sqhstl[68] = (unsigned int  )51;
 sqlstm.sqhsts[68] = (         int  )0;
 sqlstm.sqindv[68] = (         void  *)&ind_var;
 sqlstm.sqinds[68] = (         int  )0;
 sqlstm.sqharm[68] = (unsigned int  )0;
 sqlstm.sqadto[68] = (unsigned short )0;
 sqlstm.sqtdso[68] = (unsigned short )0;
 sqlstm.sqhstv[69] = (         void  *)RsvFld6;
 sqlstm.sqhstl[69] = (unsigned int  )51;
 sqlstm.sqhsts[69] = (         int  )0;
 sqlstm.sqindv[69] = (         void  *)&ind_var;
 sqlstm.sqinds[69] = (         int  )0;
 sqlstm.sqharm[69] = (unsigned int  )0;
 sqlstm.sqadto[69] = (unsigned short )0;
 sqlstm.sqtdso[69] = (unsigned short )0;
 sqlstm.sqhstv[70] = (         void  *)OrgChannel;
 sqlstm.sqhstl[70] = (unsigned int  )33;
 sqlstm.sqhsts[70] = (         int  )0;
 sqlstm.sqindv[70] = (         void  *)&ind_var;
 sqlstm.sqinds[70] = (         int  )0;
 sqlstm.sqharm[70] = (unsigned int  )0;
 sqlstm.sqadto[70] = (unsigned short )0;
 sqlstm.sqtdso[70] = (unsigned short )0;
 sqlstm.sqhstv[71] = (         void  *)OrgPort;
 sqlstm.sqhstl[71] = (unsigned int  )33;
 sqlstm.sqhsts[71] = (         int  )0;
 sqlstm.sqindv[71] = (         void  *)&ind_var;
 sqlstm.sqinds[71] = (         int  )0;
 sqlstm.sqharm[71] = (unsigned int  )0;
 sqlstm.sqadto[71] = (unsigned short )0;
 sqlstm.sqtdso[71] = (unsigned short )0;
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
            sqlstm.arrsiz = 72;
            sqlstm.sqladtp = &sqladt;
            sqlstm.sqltdsp = &sqltds;
            sqlstm.iters = (unsigned int  )1;
            sqlstm.offset = (unsigned int  )308;
            sqlstm.cud = sqlcud0;
            sqlstm.sqlest = (unsigned char  *)&sqlca;
            sqlstm.sqlety = (unsigned short)256;
            sqlstm.occurs = (unsigned int  )0;
            sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


            return 0;
    }
}

int selectEzTxnLog( const char *I_TxnRefNum )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char Input_TxnRefNum[ 151 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR Input_TxnRefNum IS STRING(151); */ 

	
	memset( Input_TxnRefNum, 0, sizeof( Input_TxnRefNum ) );
 	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	strcpy( TxnRefNum, I_TxnRefNum );
	
	/* EXEC SQL SELECT RTRIM(TXNREFNUM) INTO :Input_TxnRefNum FROM EZTXNLOG WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 72;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TXNREFNUM) into :b0  from EZTXNLOG where RTRIM(\
TXNREFNUM)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )323;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned int  )151;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[1] = (unsigned int  )151;
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



	if( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	return 0;
}

int insertSafRecord( const char *I_SafRecordNo, const char *I_NetworkId, const char *I_TxnRefNum, struct EzTxnMsg *txnmsg, char I_SafIndicator, char I_SafStatus )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char SafRecordNo[ 21 ];
		char NetworkId[ 17 ];
		char SafStatus;
		char SafIndicator;
		int SafResponse;
		char TxnRefNum[ 151 ];
		int MsgType;
        int OrgMsgType;
        int TxnCode;
        char TerminalId[ 17 ];
        char TerminalLocation[ 65 ];
        int TraceNo;
        int OrgTraceNo;
        char Input_TranDate[ 7 ];
        char Input_TranTime[ 7 ];
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
        char AcqNetworkId[ 17 ];
		char IssuerNetworkId[ 17 ];
		char FwdNetworkId[ 17 ];
		char TxfNetworkId[ 17 ];
		char SettNetworkId[ 17 ];
        char Track2[ 40 ];
        char RsvFld1[ 201 ];
        char RsvFld2[ 201 ];
        char RsvFld3[ 51 ];
        char RsvFld4[ 51 ];
        char RsvFld5[ 51 ];
        char RsvFld6[ 51 ];
        char OrgChannel[ 33 ];
        char OrgPort[ 33 ];
       	short ind_var;
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR SafRecordNo IS STRING(21); */ 

	/* EXEC SQL VAR NetworkId IS STRING(17); */ 

	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR TerminalId IS STRING(17); */ 

    /* EXEC SQL VAR TerminalLocation IS STRING(65); */ 

    /* EXEC SQL VAR Input_TranDate IS STRING(7); */ 

    /* EXEC SQL VAR Input_TranTime IS STRING(7); */ 

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

    /* EXEC SQL VAR AcqNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR IssuerNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR FwdNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR TxfNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR SettNetworkId IS STRING(17); */ 

    /* EXEC SQL VAR Track2 IS STRING(40); */ 

    /* EXEC SQL VAR RsvFld1 IS STRING(251); */ 

    /* EXEC SQL VAR RsvFld2 IS STRING(251); */ 

    /* EXEC SQL VAR RsvFld3 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld4 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld5 IS STRING(51); */ 

    /* EXEC SQL VAR RsvFld6 IS STRING(51); */ 

    /* EXEC SQL VAR OrgChannel IS STRING(33); */ 

	/* EXEC SQL VAR OrgPort IS STRING(33); */ 

	
 	memset( SafRecordNo, 0, sizeof( SafRecordNo ) );
	memset( NetworkId, 0, sizeof( NetworkId ) );
	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	memset( TerminalId, 0, sizeof( TerminalId ) );
    memset( TerminalLocation, 0, sizeof( TerminalLocation ) );
    memset( Input_TranDate, 0, sizeof( Input_TranDate ) );
    memset( Input_TranTime, 0, sizeof( Input_TranTime ) );
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
 	
	strcpy( NetworkId, I_NetworkId );
	strcpy( SafRecordNo, I_SafRecordNo );
	SafStatus = I_SafStatus;
	SafIndicator = I_SafIndicator;
	SafResponse = 0;
	strcpy( TxnRefNum, I_TxnRefNum );
	MsgType = txnmsg->MsgType;
    OrgMsgType = txnmsg->OrgMsgType;
    TxnCode = txnmsg->TxnCode;
    strcpy( TerminalId, txnmsg->TerminalId );
    strcpy( TerminalLocation, txnmsg->TerminalLocation );
    TraceNo = txnmsg->TraceNo;
    OrgTraceNo = txnmsg->OrgTraceNo;
    sprintf( Input_TranDate, "%06d", txnmsg->TranDate );
    sprintf( Input_TranTime, "%06d", txnmsg->TranTime );
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
		
	/* EXEC SQL INSERT INTO EZSAFDB
	(
		SAFRECORDNO,
		NETWORKID,
		SAFSTATUS,
		SAFINDICATOR,
		SAFRESPONSE,
		TXNREFNUM,
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
		ACCEPTORNAME,
		ACQUIRERINST,
		ISSUERINST,
		FORWARDINST,
		TXFINST,
		SETTINST,
		ACQNETWORKID,
		ISSUERNETWORKID,
		FWDNETWORKID,
		TXFNETWORKID,
		SETTNETWORKID,
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
	VALUES 
	(
		:SafRecordNo,
		:NetworkId,
		:SafStatus,
		:SafIndicator,
		:SafResponse:ind_var,
		:TxnRefNum,
		:MsgType,
        :OrgMsgType:ind_var,
        :TxnCode,
        :TerminalId,
        :TerminalLocation:ind_var,
        :TraceNo,
        :OrgTraceNo:ind_var,
        :Input_TranDate,
        :Input_TranTime,
        :OrgTranDate:ind_var,
        :OrgTranTime:ind_var,
        :LocalDate,
        :LocalTime,
        :RespCode,
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
        :MerchantType,
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
        :OrgPort:ind_var
    ); */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 76;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlbuft((void **)0, 
   "insert into EZSAFDB (SAFRECORDNO,NETWORKID,SAFSTATUS,SAFINDICATOR,SAFRES\
PONSE,TXNREFNUM,MSGTYPE,ORGMSGTYPE,TXNCODE,TERMINALID,TERMLOC,TRACENO,ORGTRA\
CENO,TRANDATE,TRANTIME,ORGTRANDATE,ORGTRANTIME,LOCALDATE,LOCALTIME,RESPCODE,\
REVCODE,REASONCODE,AUTHCODE,CAPTUREDATE,CAPTURETIME,SETTLEMENTDATE,ACQCURREN\
CYCODE,ACQCONVRATE,ACQCONVDATE,ISSCURRENCYCODE,ISSCONVRATE,ISSCONVDATE,SETTC\
URRENCYCODE,SETTCONVRATE,SETTCONVDATE,MERCHANTTYPE,POSENTRYCODE,POSCONDITION\
CODE,POSCAPCODE,POSPINCAPCODE,CHN,ACQBRANCHCODE,ISSBRANCHCODE,TXFBRANCHCODE,\
FORWARDBRANCHCODE,FROMACCTSUBTYPE,TOACCTSUBTYPE,AVAILBALANCE,LEDGERBALANCE,A\
MOUNT,TXNFEE,DISPAMOUNT,FROMACCOUNT,TOACCOUNT,REFNUM,AUTHNUM,ACCEPTORNAME,AC\
QUIRERINST,ISSUERINST,FORWARDINST,TXFINST,SETTINST,ACQNETWORKID,ISSUERNETWOR\
KID,FWDNETWORKID,TXFNETWORKID,SETTNETWORKID,TRACK2,RSVFLD1,RSVFLD2,RSVFLD3,R\
SVFLD4,RSVFLD5,RSVFLD6,ORGCHANNEL,ORGPORT) values (:b0,:b1,:b2,:b3,:b4:b5,:b\
6,:b7,:b8:b9,:b10,:b11,:b12:b13,:b14,:b15:b16,:b17,:b18,:b19:b20,:b21:b22,:b\
23,:b24,:b25,:b26:b27,:b28:b29,:b30:b31,");
 sqlstm.stmt = ":b32:b33,:b34:b35,:b36:b37,:b38:b39,:b40:b41,:b42:b43,:b44:b\
45,:b46:b47,:b48:b49,:b50:b51,:b52:b53,:b54:b55,:b56,:b57:b58,:b59:b60,:b61:b6\
2,:b63:b64,:b65:b66,:b67:b68,:b69:b70,:b71:b72,:b73:b74,:b75:b76,:b77:b78,:b79\
:b80,:b81:b82,:b83:b84,:b85:b86,:b87:b88,:b89:b90,:b91:b92,:b93:b94,:b95:b96,:\
b97:b98,:b99:b100,:b101:b102,:b103:b104,:b105:b106,:b107:b108,:b109:b110,:b111\
:b112,:b113:b114,:b115:b116,:b117:b118,:b119:b120,:b121:b122,:b123:b124,:b125:\
b126,:b127:b128,:b129:b130,:b131:b132,:b133:b134,:b135:b136)";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )346;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SafRecordNo;
 sqlstm.sqhstl[0] = (unsigned int  )21;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)NetworkId;
 sqlstm.sqhstl[1] = (unsigned int  )17;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&SafStatus;
 sqlstm.sqhstl[2] = (unsigned int  )1;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&SafIndicator;
 sqlstm.sqhstl[3] = (unsigned int  )1;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&SafResponse;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)&ind_var;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[5] = (unsigned int  )151;
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&MsgType;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&OrgMsgType;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)&ind_var;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&TxnCode;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)TerminalId;
 sqlstm.sqhstl[9] = (unsigned int  )17;
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)TerminalLocation;
 sqlstm.sqhstl[10] = (unsigned int  )65;
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)&ind_var;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqhstv[11] = (         void  *)&TraceNo;
 sqlstm.sqhstl[11] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[11] = (         int  )0;
 sqlstm.sqindv[11] = (         void  *)0;
 sqlstm.sqinds[11] = (         int  )0;
 sqlstm.sqharm[11] = (unsigned int  )0;
 sqlstm.sqadto[11] = (unsigned short )0;
 sqlstm.sqtdso[11] = (unsigned short )0;
 sqlstm.sqhstv[12] = (         void  *)&OrgTraceNo;
 sqlstm.sqhstl[12] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[12] = (         int  )0;
 sqlstm.sqindv[12] = (         void  *)&ind_var;
 sqlstm.sqinds[12] = (         int  )0;
 sqlstm.sqharm[12] = (unsigned int  )0;
 sqlstm.sqadto[12] = (unsigned short )0;
 sqlstm.sqtdso[12] = (unsigned short )0;
 sqlstm.sqhstv[13] = (         void  *)Input_TranDate;
 sqlstm.sqhstl[13] = (unsigned int  )7;
 sqlstm.sqhsts[13] = (         int  )0;
 sqlstm.sqindv[13] = (         void  *)0;
 sqlstm.sqinds[13] = (         int  )0;
 sqlstm.sqharm[13] = (unsigned int  )0;
 sqlstm.sqadto[13] = (unsigned short )0;
 sqlstm.sqtdso[13] = (unsigned short )0;
 sqlstm.sqhstv[14] = (         void  *)Input_TranTime;
 sqlstm.sqhstl[14] = (unsigned int  )7;
 sqlstm.sqhsts[14] = (         int  )0;
 sqlstm.sqindv[14] = (         void  *)0;
 sqlstm.sqinds[14] = (         int  )0;
 sqlstm.sqharm[14] = (unsigned int  )0;
 sqlstm.sqadto[14] = (unsigned short )0;
 sqlstm.sqtdso[14] = (unsigned short )0;
 sqlstm.sqhstv[15] = (         void  *)&OrgTranDate;
 sqlstm.sqhstl[15] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[15] = (         int  )0;
 sqlstm.sqindv[15] = (         void  *)&ind_var;
 sqlstm.sqinds[15] = (         int  )0;
 sqlstm.sqharm[15] = (unsigned int  )0;
 sqlstm.sqadto[15] = (unsigned short )0;
 sqlstm.sqtdso[15] = (unsigned short )0;
 sqlstm.sqhstv[16] = (         void  *)&OrgTranTime;
 sqlstm.sqhstl[16] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[16] = (         int  )0;
 sqlstm.sqindv[16] = (         void  *)&ind_var;
 sqlstm.sqinds[16] = (         int  )0;
 sqlstm.sqharm[16] = (unsigned int  )0;
 sqlstm.sqadto[16] = (unsigned short )0;
 sqlstm.sqtdso[16] = (unsigned short )0;
 sqlstm.sqhstv[17] = (         void  *)&LocalDate;
 sqlstm.sqhstl[17] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[17] = (         int  )0;
 sqlstm.sqindv[17] = (         void  *)0;
 sqlstm.sqinds[17] = (         int  )0;
 sqlstm.sqharm[17] = (unsigned int  )0;
 sqlstm.sqadto[17] = (unsigned short )0;
 sqlstm.sqtdso[17] = (unsigned short )0;
 sqlstm.sqhstv[18] = (         void  *)&LocalTime;
 sqlstm.sqhstl[18] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[18] = (         int  )0;
 sqlstm.sqindv[18] = (         void  *)0;
 sqlstm.sqinds[18] = (         int  )0;
 sqlstm.sqharm[18] = (unsigned int  )0;
 sqlstm.sqadto[18] = (unsigned short )0;
 sqlstm.sqtdso[18] = (unsigned short )0;
 sqlstm.sqhstv[19] = (         void  *)&RespCode;
 sqlstm.sqhstl[19] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[19] = (         int  )0;
 sqlstm.sqindv[19] = (         void  *)0;
 sqlstm.sqinds[19] = (         int  )0;
 sqlstm.sqharm[19] = (unsigned int  )0;
 sqlstm.sqadto[19] = (unsigned short )0;
 sqlstm.sqtdso[19] = (unsigned short )0;
 sqlstm.sqhstv[20] = (         void  *)&RevCode;
 sqlstm.sqhstl[20] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[20] = (         int  )0;
 sqlstm.sqindv[20] = (         void  *)&ind_var;
 sqlstm.sqinds[20] = (         int  )0;
 sqlstm.sqharm[20] = (unsigned int  )0;
 sqlstm.sqadto[20] = (unsigned short )0;
 sqlstm.sqtdso[20] = (unsigned short )0;
 sqlstm.sqhstv[21] = (         void  *)&ReasonCode;
 sqlstm.sqhstl[21] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[21] = (         int  )0;
 sqlstm.sqindv[21] = (         void  *)&ind_var;
 sqlstm.sqinds[21] = (         int  )0;
 sqlstm.sqharm[21] = (unsigned int  )0;
 sqlstm.sqadto[21] = (unsigned short )0;
 sqlstm.sqtdso[21] = (unsigned short )0;
 sqlstm.sqhstv[22] = (         void  *)&AuthCode;
 sqlstm.sqhstl[22] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[22] = (         int  )0;
 sqlstm.sqindv[22] = (         void  *)&ind_var;
 sqlstm.sqinds[22] = (         int  )0;
 sqlstm.sqharm[22] = (unsigned int  )0;
 sqlstm.sqadto[22] = (unsigned short )0;
 sqlstm.sqtdso[22] = (unsigned short )0;
 sqlstm.sqhstv[23] = (         void  *)&CaptureDate;
 sqlstm.sqhstl[23] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[23] = (         int  )0;
 sqlstm.sqindv[23] = (         void  *)&ind_var;
 sqlstm.sqinds[23] = (         int  )0;
 sqlstm.sqharm[23] = (unsigned int  )0;
 sqlstm.sqadto[23] = (unsigned short )0;
 sqlstm.sqtdso[23] = (unsigned short )0;
 sqlstm.sqhstv[24] = (         void  *)&CaptureTime;
 sqlstm.sqhstl[24] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[24] = (         int  )0;
 sqlstm.sqindv[24] = (         void  *)&ind_var;
 sqlstm.sqinds[24] = (         int  )0;
 sqlstm.sqharm[24] = (unsigned int  )0;
 sqlstm.sqadto[24] = (unsigned short )0;
 sqlstm.sqtdso[24] = (unsigned short )0;
 sqlstm.sqhstv[25] = (         void  *)&SettlementDate;
 sqlstm.sqhstl[25] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[25] = (         int  )0;
 sqlstm.sqindv[25] = (         void  *)&ind_var;
 sqlstm.sqinds[25] = (         int  )0;
 sqlstm.sqharm[25] = (unsigned int  )0;
 sqlstm.sqadto[25] = (unsigned short )0;
 sqlstm.sqtdso[25] = (unsigned short )0;
 sqlstm.sqhstv[26] = (         void  *)&AcqCurrencyCode;
 sqlstm.sqhstl[26] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[26] = (         int  )0;
 sqlstm.sqindv[26] = (         void  *)&ind_var;
 sqlstm.sqinds[26] = (         int  )0;
 sqlstm.sqharm[26] = (unsigned int  )0;
 sqlstm.sqadto[26] = (unsigned short )0;
 sqlstm.sqtdso[26] = (unsigned short )0;
 sqlstm.sqhstv[27] = (         void  *)&AcqConvRate;
 sqlstm.sqhstl[27] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[27] = (         int  )0;
 sqlstm.sqindv[27] = (         void  *)&ind_var;
 sqlstm.sqinds[27] = (         int  )0;
 sqlstm.sqharm[27] = (unsigned int  )0;
 sqlstm.sqadto[27] = (unsigned short )0;
 sqlstm.sqtdso[27] = (unsigned short )0;
 sqlstm.sqhstv[28] = (         void  *)&AcqConvDate;
 sqlstm.sqhstl[28] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[28] = (         int  )0;
 sqlstm.sqindv[28] = (         void  *)&ind_var;
 sqlstm.sqinds[28] = (         int  )0;
 sqlstm.sqharm[28] = (unsigned int  )0;
 sqlstm.sqadto[28] = (unsigned short )0;
 sqlstm.sqtdso[28] = (unsigned short )0;
 sqlstm.sqhstv[29] = (         void  *)&IssCurrencyCode;
 sqlstm.sqhstl[29] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[29] = (         int  )0;
 sqlstm.sqindv[29] = (         void  *)&ind_var;
 sqlstm.sqinds[29] = (         int  )0;
 sqlstm.sqharm[29] = (unsigned int  )0;
 sqlstm.sqadto[29] = (unsigned short )0;
 sqlstm.sqtdso[29] = (unsigned short )0;
 sqlstm.sqhstv[30] = (         void  *)&IssConvRate;
 sqlstm.sqhstl[30] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[30] = (         int  )0;
 sqlstm.sqindv[30] = (         void  *)&ind_var;
 sqlstm.sqinds[30] = (         int  )0;
 sqlstm.sqharm[30] = (unsigned int  )0;
 sqlstm.sqadto[30] = (unsigned short )0;
 sqlstm.sqtdso[30] = (unsigned short )0;
 sqlstm.sqhstv[31] = (         void  *)&IssConvDate;
 sqlstm.sqhstl[31] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[31] = (         int  )0;
 sqlstm.sqindv[31] = (         void  *)&ind_var;
 sqlstm.sqinds[31] = (         int  )0;
 sqlstm.sqharm[31] = (unsigned int  )0;
 sqlstm.sqadto[31] = (unsigned short )0;
 sqlstm.sqtdso[31] = (unsigned short )0;
 sqlstm.sqhstv[32] = (         void  *)&SettCurrencyCode;
 sqlstm.sqhstl[32] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[32] = (         int  )0;
 sqlstm.sqindv[32] = (         void  *)&ind_var;
 sqlstm.sqinds[32] = (         int  )0;
 sqlstm.sqharm[32] = (unsigned int  )0;
 sqlstm.sqadto[32] = (unsigned short )0;
 sqlstm.sqtdso[32] = (unsigned short )0;
 sqlstm.sqhstv[33] = (         void  *)&SettConvRate;
 sqlstm.sqhstl[33] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[33] = (         int  )0;
 sqlstm.sqindv[33] = (         void  *)&ind_var;
 sqlstm.sqinds[33] = (         int  )0;
 sqlstm.sqharm[33] = (unsigned int  )0;
 sqlstm.sqadto[33] = (unsigned short )0;
 sqlstm.sqtdso[33] = (unsigned short )0;
 sqlstm.sqhstv[34] = (         void  *)&SettConvDate;
 sqlstm.sqhstl[34] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[34] = (         int  )0;
 sqlstm.sqindv[34] = (         void  *)&ind_var;
 sqlstm.sqinds[34] = (         int  )0;
 sqlstm.sqharm[34] = (unsigned int  )0;
 sqlstm.sqadto[34] = (unsigned short )0;
 sqlstm.sqtdso[34] = (unsigned short )0;
 sqlstm.sqhstv[35] = (         void  *)&MerchantType;
 sqlstm.sqhstl[35] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[35] = (         int  )0;
 sqlstm.sqindv[35] = (         void  *)0;
 sqlstm.sqinds[35] = (         int  )0;
 sqlstm.sqharm[35] = (unsigned int  )0;
 sqlstm.sqadto[35] = (unsigned short )0;
 sqlstm.sqtdso[35] = (unsigned short )0;
 sqlstm.sqhstv[36] = (         void  *)&PosEntryCode;
 sqlstm.sqhstl[36] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[36] = (         int  )0;
 sqlstm.sqindv[36] = (         void  *)&ind_var;
 sqlstm.sqinds[36] = (         int  )0;
 sqlstm.sqharm[36] = (unsigned int  )0;
 sqlstm.sqadto[36] = (unsigned short )0;
 sqlstm.sqtdso[36] = (unsigned short )0;
 sqlstm.sqhstv[37] = (         void  *)&PosConditionCode;
 sqlstm.sqhstl[37] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[37] = (         int  )0;
 sqlstm.sqindv[37] = (         void  *)&ind_var;
 sqlstm.sqinds[37] = (         int  )0;
 sqlstm.sqharm[37] = (unsigned int  )0;
 sqlstm.sqadto[37] = (unsigned short )0;
 sqlstm.sqtdso[37] = (unsigned short )0;
 sqlstm.sqhstv[38] = (         void  *)&PosCapCode;
 sqlstm.sqhstl[38] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[38] = (         int  )0;
 sqlstm.sqindv[38] = (         void  *)&ind_var;
 sqlstm.sqinds[38] = (         int  )0;
 sqlstm.sqharm[38] = (unsigned int  )0;
 sqlstm.sqadto[38] = (unsigned short )0;
 sqlstm.sqtdso[38] = (unsigned short )0;
 sqlstm.sqhstv[39] = (         void  *)&PosPinCapCode;
 sqlstm.sqhstl[39] = (unsigned int  )1;
 sqlstm.sqhsts[39] = (         int  )0;
 sqlstm.sqindv[39] = (         void  *)&ind_var;
 sqlstm.sqinds[39] = (         int  )0;
 sqlstm.sqharm[39] = (unsigned int  )0;
 sqlstm.sqadto[39] = (unsigned short )0;
 sqlstm.sqtdso[39] = (unsigned short )0;
 sqlstm.sqhstv[40] = (         void  *)chn;
 sqlstm.sqhstl[40] = (unsigned int  )20;
 sqlstm.sqhsts[40] = (         int  )0;
 sqlstm.sqindv[40] = (         void  *)&ind_var;
 sqlstm.sqinds[40] = (         int  )0;
 sqlstm.sqharm[40] = (unsigned int  )0;
 sqlstm.sqadto[40] = (unsigned short )0;
 sqlstm.sqtdso[40] = (unsigned short )0;
 sqlstm.sqhstv[41] = (         void  *)AcqBranchCode;
 sqlstm.sqhstl[41] = (unsigned int  )11;
 sqlstm.sqhsts[41] = (         int  )0;
 sqlstm.sqindv[41] = (         void  *)&ind_var;
 sqlstm.sqinds[41] = (         int  )0;
 sqlstm.sqharm[41] = (unsigned int  )0;
 sqlstm.sqadto[41] = (unsigned short )0;
 sqlstm.sqtdso[41] = (unsigned short )0;
 sqlstm.sqhstv[42] = (         void  *)IssBranchCode;
 sqlstm.sqhstl[42] = (unsigned int  )11;
 sqlstm.sqhsts[42] = (         int  )0;
 sqlstm.sqindv[42] = (         void  *)&ind_var;
 sqlstm.sqinds[42] = (         int  )0;
 sqlstm.sqharm[42] = (unsigned int  )0;
 sqlstm.sqadto[42] = (unsigned short )0;
 sqlstm.sqtdso[42] = (unsigned short )0;
 sqlstm.sqhstv[43] = (         void  *)TxfBranchCode;
 sqlstm.sqhstl[43] = (unsigned int  )11;
 sqlstm.sqhsts[43] = (         int  )0;
 sqlstm.sqindv[43] = (         void  *)&ind_var;
 sqlstm.sqinds[43] = (         int  )0;
 sqlstm.sqharm[43] = (unsigned int  )0;
 sqlstm.sqadto[43] = (unsigned short )0;
 sqlstm.sqtdso[43] = (unsigned short )0;
 sqlstm.sqhstv[44] = (         void  *)ForwardBranchCode;
 sqlstm.sqhstl[44] = (unsigned int  )11;
 sqlstm.sqhsts[44] = (         int  )0;
 sqlstm.sqindv[44] = (         void  *)&ind_var;
 sqlstm.sqinds[44] = (         int  )0;
 sqlstm.sqharm[44] = (unsigned int  )0;
 sqlstm.sqadto[44] = (unsigned short )0;
 sqlstm.sqtdso[44] = (unsigned short )0;
 sqlstm.sqhstv[45] = (         void  *)FromAcctSubType;
 sqlstm.sqhstl[45] = (unsigned int  )11;
 sqlstm.sqhsts[45] = (         int  )0;
 sqlstm.sqindv[45] = (         void  *)&ind_var;
 sqlstm.sqinds[45] = (         int  )0;
 sqlstm.sqharm[45] = (unsigned int  )0;
 sqlstm.sqadto[45] = (unsigned short )0;
 sqlstm.sqtdso[45] = (unsigned short )0;
 sqlstm.sqhstv[46] = (         void  *)ToAcctSubType;
 sqlstm.sqhstl[46] = (unsigned int  )11;
 sqlstm.sqhsts[46] = (         int  )0;
 sqlstm.sqindv[46] = (         void  *)&ind_var;
 sqlstm.sqinds[46] = (         int  )0;
 sqlstm.sqharm[46] = (unsigned int  )0;
 sqlstm.sqadto[46] = (unsigned short )0;
 sqlstm.sqtdso[46] = (unsigned short )0;
 sqlstm.sqhstv[47] = (         void  *)AvailBalance;
 sqlstm.sqhstl[47] = (unsigned int  )15;
 sqlstm.sqhsts[47] = (         int  )0;
 sqlstm.sqindv[47] = (         void  *)&ind_var;
 sqlstm.sqinds[47] = (         int  )0;
 sqlstm.sqharm[47] = (unsigned int  )0;
 sqlstm.sqadto[47] = (unsigned short )0;
 sqlstm.sqtdso[47] = (unsigned short )0;
 sqlstm.sqhstv[48] = (         void  *)LedgerBalance;
 sqlstm.sqhstl[48] = (unsigned int  )15;
 sqlstm.sqhsts[48] = (         int  )0;
 sqlstm.sqindv[48] = (         void  *)&ind_var;
 sqlstm.sqinds[48] = (         int  )0;
 sqlstm.sqharm[48] = (unsigned int  )0;
 sqlstm.sqadto[48] = (unsigned short )0;
 sqlstm.sqtdso[48] = (unsigned short )0;
 sqlstm.sqhstv[49] = (         void  *)Amount;
 sqlstm.sqhstl[49] = (unsigned int  )15;
 sqlstm.sqhsts[49] = (         int  )0;
 sqlstm.sqindv[49] = (         void  *)&ind_var;
 sqlstm.sqinds[49] = (         int  )0;
 sqlstm.sqharm[49] = (unsigned int  )0;
 sqlstm.sqadto[49] = (unsigned short )0;
 sqlstm.sqtdso[49] = (unsigned short )0;
 sqlstm.sqhstv[50] = (         void  *)TxnFee;
 sqlstm.sqhstl[50] = (unsigned int  )15;
 sqlstm.sqhsts[50] = (         int  )0;
 sqlstm.sqindv[50] = (         void  *)&ind_var;
 sqlstm.sqinds[50] = (         int  )0;
 sqlstm.sqharm[50] = (unsigned int  )0;
 sqlstm.sqadto[50] = (unsigned short )0;
 sqlstm.sqtdso[50] = (unsigned short )0;
 sqlstm.sqhstv[51] = (         void  *)DispAmount;
 sqlstm.sqhstl[51] = (unsigned int  )15;
 sqlstm.sqhsts[51] = (         int  )0;
 sqlstm.sqindv[51] = (         void  *)&ind_var;
 sqlstm.sqinds[51] = (         int  )0;
 sqlstm.sqharm[51] = (unsigned int  )0;
 sqlstm.sqadto[51] = (unsigned short )0;
 sqlstm.sqtdso[51] = (unsigned short )0;
 sqlstm.sqhstv[52] = (         void  *)FromAccount;
 sqlstm.sqhstl[52] = (unsigned int  )33;
 sqlstm.sqhsts[52] = (         int  )0;
 sqlstm.sqindv[52] = (         void  *)&ind_var;
 sqlstm.sqinds[52] = (         int  )0;
 sqlstm.sqharm[52] = (unsigned int  )0;
 sqlstm.sqadto[52] = (unsigned short )0;
 sqlstm.sqtdso[52] = (unsigned short )0;
 sqlstm.sqhstv[53] = (         void  *)ToAccount;
 sqlstm.sqhstl[53] = (unsigned int  )33;
 sqlstm.sqhsts[53] = (         int  )0;
 sqlstm.sqindv[53] = (         void  *)&ind_var;
 sqlstm.sqinds[53] = (         int  )0;
 sqlstm.sqharm[53] = (unsigned int  )0;
 sqlstm.sqadto[53] = (unsigned short )0;
 sqlstm.sqtdso[53] = (unsigned short )0;
 sqlstm.sqhstv[54] = (         void  *)RefNum;
 sqlstm.sqhstl[54] = (unsigned int  )13;
 sqlstm.sqhsts[54] = (         int  )0;
 sqlstm.sqindv[54] = (         void  *)&ind_var;
 sqlstm.sqinds[54] = (         int  )0;
 sqlstm.sqharm[54] = (unsigned int  )0;
 sqlstm.sqadto[54] = (unsigned short )0;
 sqlstm.sqtdso[54] = (unsigned short )0;
 sqlstm.sqhstv[55] = (         void  *)AuthNum;
 sqlstm.sqhstl[55] = (unsigned int  )13;
 sqlstm.sqhsts[55] = (         int  )0;
 sqlstm.sqindv[55] = (         void  *)&ind_var;
 sqlstm.sqinds[55] = (         int  )0;
 sqlstm.sqharm[55] = (unsigned int  )0;
 sqlstm.sqadto[55] = (unsigned short )0;
 sqlstm.sqtdso[55] = (unsigned short )0;
 sqlstm.sqhstv[56] = (         void  *)AcceptorName;
 sqlstm.sqhstl[56] = (unsigned int  )41;
 sqlstm.sqhsts[56] = (         int  )0;
 sqlstm.sqindv[56] = (         void  *)&ind_var;
 sqlstm.sqinds[56] = (         int  )0;
 sqlstm.sqharm[56] = (unsigned int  )0;
 sqlstm.sqadto[56] = (unsigned short )0;
 sqlstm.sqtdso[56] = (unsigned short )0;
 sqlstm.sqhstv[57] = (         void  *)AcquirerInst;
 sqlstm.sqhstl[57] = (unsigned int  )13;
 sqlstm.sqhsts[57] = (         int  )0;
 sqlstm.sqindv[57] = (         void  *)&ind_var;
 sqlstm.sqinds[57] = (         int  )0;
 sqlstm.sqharm[57] = (unsigned int  )0;
 sqlstm.sqadto[57] = (unsigned short )0;
 sqlstm.sqtdso[57] = (unsigned short )0;
 sqlstm.sqhstv[58] = (         void  *)IssuerInst;
 sqlstm.sqhstl[58] = (unsigned int  )13;
 sqlstm.sqhsts[58] = (         int  )0;
 sqlstm.sqindv[58] = (         void  *)&ind_var;
 sqlstm.sqinds[58] = (         int  )0;
 sqlstm.sqharm[58] = (unsigned int  )0;
 sqlstm.sqadto[58] = (unsigned short )0;
 sqlstm.sqtdso[58] = (unsigned short )0;
 sqlstm.sqhstv[59] = (         void  *)ForwardInst;
 sqlstm.sqhstl[59] = (unsigned int  )13;
 sqlstm.sqhsts[59] = (         int  )0;
 sqlstm.sqindv[59] = (         void  *)&ind_var;
 sqlstm.sqinds[59] = (         int  )0;
 sqlstm.sqharm[59] = (unsigned int  )0;
 sqlstm.sqadto[59] = (unsigned short )0;
 sqlstm.sqtdso[59] = (unsigned short )0;
 sqlstm.sqhstv[60] = (         void  *)TxfInst;
 sqlstm.sqhstl[60] = (unsigned int  )13;
 sqlstm.sqhsts[60] = (         int  )0;
 sqlstm.sqindv[60] = (         void  *)&ind_var;
 sqlstm.sqinds[60] = (         int  )0;
 sqlstm.sqharm[60] = (unsigned int  )0;
 sqlstm.sqadto[60] = (unsigned short )0;
 sqlstm.sqtdso[60] = (unsigned short )0;
 sqlstm.sqhstv[61] = (         void  *)SettInst;
 sqlstm.sqhstl[61] = (unsigned int  )13;
 sqlstm.sqhsts[61] = (         int  )0;
 sqlstm.sqindv[61] = (         void  *)&ind_var;
 sqlstm.sqinds[61] = (         int  )0;
 sqlstm.sqharm[61] = (unsigned int  )0;
 sqlstm.sqadto[61] = (unsigned short )0;
 sqlstm.sqtdso[61] = (unsigned short )0;
 sqlstm.sqhstv[62] = (         void  *)AcqNetworkId;
 sqlstm.sqhstl[62] = (unsigned int  )17;
 sqlstm.sqhsts[62] = (         int  )0;
 sqlstm.sqindv[62] = (         void  *)&ind_var;
 sqlstm.sqinds[62] = (         int  )0;
 sqlstm.sqharm[62] = (unsigned int  )0;
 sqlstm.sqadto[62] = (unsigned short )0;
 sqlstm.sqtdso[62] = (unsigned short )0;
 sqlstm.sqhstv[63] = (         void  *)IssuerNetworkId;
 sqlstm.sqhstl[63] = (unsigned int  )17;
 sqlstm.sqhsts[63] = (         int  )0;
 sqlstm.sqindv[63] = (         void  *)&ind_var;
 sqlstm.sqinds[63] = (         int  )0;
 sqlstm.sqharm[63] = (unsigned int  )0;
 sqlstm.sqadto[63] = (unsigned short )0;
 sqlstm.sqtdso[63] = (unsigned short )0;
 sqlstm.sqhstv[64] = (         void  *)FwdNetworkId;
 sqlstm.sqhstl[64] = (unsigned int  )17;
 sqlstm.sqhsts[64] = (         int  )0;
 sqlstm.sqindv[64] = (         void  *)&ind_var;
 sqlstm.sqinds[64] = (         int  )0;
 sqlstm.sqharm[64] = (unsigned int  )0;
 sqlstm.sqadto[64] = (unsigned short )0;
 sqlstm.sqtdso[64] = (unsigned short )0;
 sqlstm.sqhstv[65] = (         void  *)TxfNetworkId;
 sqlstm.sqhstl[65] = (unsigned int  )17;
 sqlstm.sqhsts[65] = (         int  )0;
 sqlstm.sqindv[65] = (         void  *)&ind_var;
 sqlstm.sqinds[65] = (         int  )0;
 sqlstm.sqharm[65] = (unsigned int  )0;
 sqlstm.sqadto[65] = (unsigned short )0;
 sqlstm.sqtdso[65] = (unsigned short )0;
 sqlstm.sqhstv[66] = (         void  *)SettNetworkId;
 sqlstm.sqhstl[66] = (unsigned int  )17;
 sqlstm.sqhsts[66] = (         int  )0;
 sqlstm.sqindv[66] = (         void  *)&ind_var;
 sqlstm.sqinds[66] = (         int  )0;
 sqlstm.sqharm[66] = (unsigned int  )0;
 sqlstm.sqadto[66] = (unsigned short )0;
 sqlstm.sqtdso[66] = (unsigned short )0;
 sqlstm.sqhstv[67] = (         void  *)Track2;
 sqlstm.sqhstl[67] = (unsigned int  )40;
 sqlstm.sqhsts[67] = (         int  )0;
 sqlstm.sqindv[67] = (         void  *)&ind_var;
 sqlstm.sqinds[67] = (         int  )0;
 sqlstm.sqharm[67] = (unsigned int  )0;
 sqlstm.sqadto[67] = (unsigned short )0;
 sqlstm.sqtdso[67] = (unsigned short )0;
 sqlstm.sqhstv[68] = (         void  *)RsvFld1;
 sqlstm.sqhstl[68] = (unsigned int  )251;
 sqlstm.sqhsts[68] = (         int  )0;
 sqlstm.sqindv[68] = (         void  *)&ind_var;
 sqlstm.sqinds[68] = (         int  )0;
 sqlstm.sqharm[68] = (unsigned int  )0;
 sqlstm.sqadto[68] = (unsigned short )0;
 sqlstm.sqtdso[68] = (unsigned short )0;
 sqlstm.sqhstv[69] = (         void  *)RsvFld2;
 sqlstm.sqhstl[69] = (unsigned int  )251;
 sqlstm.sqhsts[69] = (         int  )0;
 sqlstm.sqindv[69] = (         void  *)&ind_var;
 sqlstm.sqinds[69] = (         int  )0;
 sqlstm.sqharm[69] = (unsigned int  )0;
 sqlstm.sqadto[69] = (unsigned short )0;
 sqlstm.sqtdso[69] = (unsigned short )0;
 sqlstm.sqhstv[70] = (         void  *)RsvFld3;
 sqlstm.sqhstl[70] = (unsigned int  )51;
 sqlstm.sqhsts[70] = (         int  )0;
 sqlstm.sqindv[70] = (         void  *)&ind_var;
 sqlstm.sqinds[70] = (         int  )0;
 sqlstm.sqharm[70] = (unsigned int  )0;
 sqlstm.sqadto[70] = (unsigned short )0;
 sqlstm.sqtdso[70] = (unsigned short )0;
 sqlstm.sqhstv[71] = (         void  *)RsvFld4;
 sqlstm.sqhstl[71] = (unsigned int  )51;
 sqlstm.sqhsts[71] = (         int  )0;
 sqlstm.sqindv[71] = (         void  *)&ind_var;
 sqlstm.sqinds[71] = (         int  )0;
 sqlstm.sqharm[71] = (unsigned int  )0;
 sqlstm.sqadto[71] = (unsigned short )0;
 sqlstm.sqtdso[71] = (unsigned short )0;
 sqlstm.sqhstv[72] = (         void  *)RsvFld5;
 sqlstm.sqhstl[72] = (unsigned int  )51;
 sqlstm.sqhsts[72] = (         int  )0;
 sqlstm.sqindv[72] = (         void  *)&ind_var;
 sqlstm.sqinds[72] = (         int  )0;
 sqlstm.sqharm[72] = (unsigned int  )0;
 sqlstm.sqadto[72] = (unsigned short )0;
 sqlstm.sqtdso[72] = (unsigned short )0;
 sqlstm.sqhstv[73] = (         void  *)RsvFld6;
 sqlstm.sqhstl[73] = (unsigned int  )51;
 sqlstm.sqhsts[73] = (         int  )0;
 sqlstm.sqindv[73] = (         void  *)&ind_var;
 sqlstm.sqinds[73] = (         int  )0;
 sqlstm.sqharm[73] = (unsigned int  )0;
 sqlstm.sqadto[73] = (unsigned short )0;
 sqlstm.sqtdso[73] = (unsigned short )0;
 sqlstm.sqhstv[74] = (         void  *)OrgChannel;
 sqlstm.sqhstl[74] = (unsigned int  )33;
 sqlstm.sqhsts[74] = (         int  )0;
 sqlstm.sqindv[74] = (         void  *)&ind_var;
 sqlstm.sqinds[74] = (         int  )0;
 sqlstm.sqharm[74] = (unsigned int  )0;
 sqlstm.sqadto[74] = (unsigned short )0;
 sqlstm.sqtdso[74] = (unsigned short )0;
 sqlstm.sqhstv[75] = (         void  *)OrgPort;
 sqlstm.sqhstl[75] = (unsigned int  )33;
 sqlstm.sqhsts[75] = (         int  )0;
 sqlstm.sqindv[75] = (         void  *)&ind_var;
 sqlstm.sqinds[75] = (         int  )0;
 sqlstm.sqharm[75] = (unsigned int  )0;
 sqlstm.sqadto[75] = (unsigned short )0;
 sqlstm.sqtdso[75] = (unsigned short )0;
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
        sqlstm.arrsiz = 76;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )665;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)256;
        sqlstm.occurs = (unsigned int  )0;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        return 0;
    }
}

int selectEzSafDB( const char *I_TxnRefNum )
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

		char TxnRefNum[ 151 ];
		char Input_TxnRefNum[ 151 ];
	/* EXEC SQL END DECLARE SECTION; */ 


	/* EXEC SQL VAR TxnRefNum IS STRING(151); */ 

	/* EXEC SQL VAR Input_TxnRefNum IS STRING(151); */ 

	
	memset( Input_TxnRefNum, 0, sizeof( Input_TxnRefNum ) );
 	memset( TxnRefNum, 0, sizeof( TxnRefNum ) );
	strcpy( TxnRefNum, I_TxnRefNum );
	
	/* EXEC SQL SELECT RTRIM(TXNREFNUM) INTO :Input_TxnRefNum FROM EZSAFDB WHERE RTRIM(TXNREFNUM)=:TxnRefNum; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 76;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "select RTRIM(TXNREFNUM) into :b0  from EZSAFDB where RTRIM(T\
XNREFNUM)=:b1";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )680;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)256;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)Input_TxnRefNum;
 sqlstm.sqhstl[0] = (unsigned int  )151;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)TxnRefNum;
 sqlstm.sqhstl[1] = (unsigned int  )151;
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



	if( sqlca.sqlcode != 0 )
		return sqlca.sqlcode;
	
	return 0;
}


