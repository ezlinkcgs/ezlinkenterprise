#ifndef EZHSMSIM_H_
#define EZHSMSIM_H_

#include "ezdebugutil.h"
#include "ezcfg_util.h"

enum HSMTypeDef
{
	HSM_TYPE_ERACOM = 1,
	HSM_TYPE_RACAL
};

enum HeaderTypeDef
{
	HEADER_TYPE_HEX = 1,
	HEADER_TYPE_ASCII
};

enum HSMCommandTypeDef
{
	HSM_TERMINAL_KEY_GEN_REQ = 1,
	HSM_NETWORK_KEY_GEN_REQ,
	HSM_PIN_TRNSLATE_REQ,
	HSM_TERMINAL_PIN_VERIFICATION_REQ,
	HSM_NETWORK_PIN_VERIFICATION_REQ
};

struct EzHSMParam
{
	char HSMId[ 33 ];
	int HSMPortNo;
	int HSMType;
	int HeaderLen;
	int HeaderType;
	int MsgHeaderLen;
	int MaxClients;
};

class EzHSMSim : public EzDebugUtil
{
	private:

		struct EzHSMParam hsmparam;
		int CommandType, *desc_list_ptr;

	public:

		int checkInteger( const char *IntStr, int IntLen );
		int initHSMSim( const char *TaskName, const char *PortNoStr, const char *CfgFile );
		int identifyCommandType( const char *tcpipmsg );
		int writeHSMSocket( int ConnectionId, const char *HSMRespMsg, int MsgLen );
		void processHSMRequest( int ConnectionId, const char *tcpipmsg, int MsgSize );
		int createServerSocket();
		int allocateDescriptorList();
		int serviceRequest();

};

#endif /* EZHSMSIM_H_ */

