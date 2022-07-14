#include<ezbusiness/ezposdbmgrutil.h>

void EzPOSDBMgrUtil :: InitEzPOSDBMgrUtil( EzDebugUtil *dptr )
{
	this->dptr = dptr;
	return ;
}

int EzPOSDBMgrUtil :: InsertPosTxnLogTable( const char *TxnRefNum_ptr, struct EzTxnMsg *txnmsg )
{
	int retval;
	retval = InsertPosTxnLog( TxnRefNum_ptr, txnmsg );
	if( retval < 0 )
	{
		dptr->trace("Error In Inserting To EzPosTxnLog Table OraErr[%05d]", retval );
		return -1;
	}
	return 1;
}
int EzPOSDBMgrUtil :: InsertPosTxnLogHistTable( const char *TxnRefNum_ptr, struct EzTxnMsg *txnmsg )
{
	int retval;
	retval = InsertPosTxnHistLog( TxnRefNum_ptr, txnmsg );
	if( retval < 0 )
	{
		dptr->trace("Error In Inserting To EzPosTxnLog Table OraErr[%05d]", retval );
		return -1;
	}
	return 1;
}
int EzPOSDBMgrUtil :: UpdatePosTerminalInfoTable( struct EzPOSTerminalInfo *posterminalinfo )
{
	int retval;
	retval = UpdatePosTerminalInfo( posterminalinfo );
	if( retval < 0 )
	{
		dptr->trace("Error In Updating To EzPosTerminalInfo Table OraErr[%05d]", retval );
		return -1;
	}
	return 1;
}