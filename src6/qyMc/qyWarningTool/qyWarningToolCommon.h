
#ifndef  __QYWARNINGTOOLCOMMON_H__
#define	 __QYWARNINGTOOLCOMMON_H__	//  {

#include	"qyCommon.h"
#include	"qyGuiCommon.h"

#include	"qyCommonEx.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"						//  2005/01/24
#include	"qnmCommProc.h"
#include	"qnmFwCommProc.h"						//  2004/08/13
#include	"qnmPcComm.h"
#include	"qnmWarnCommProc.h"

#include	"qnmCommProc1.h"

#include	"qyImcCommProc.h"
#include	"qySnmpCommProc.h"

#include	"qnmsCommProc.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qnmPcComm.h"
#include	"qyDaemonPublic.h"
#include	"qyTCharCommProc.h"
#include	"qnmWarnCommProc.h"

#include	"qyCusResPublic.h"


typedef  struct  __qyWarningInfo_t		{

				 QY_ENV					env;

				 struct					{
					char				cntIp[15  +  1];
					unsigned  short		usCntPort;
					SOCK_TIMEOUT		to;
				 }						cfg;
				 QY_ENC_CTX				encCtx,  commEncCtx;
				 unsigned  short		usLangId;
				 QNM_CUSRES_INFO		cusRes;
				 unsigned  char			ucbCusResInited;

				 QNM_WARNING_MSGS		msgs;
				 unsigned  int			uiLastDisplayedEventId;
				 HANDLE					hThread;
				 BOOL					bQuit;
				 TCHAR					statusBuf[128];

				 unsigned  int			cnt_processed;		//  2011/02/16

}		 QY_WARNING_INFO;

extern  QY_WARNING_INFO		gBuf;

int  initWarningTool(  QY_WARNING_INFO  *  p  );
void  exitWarningTool(  QY_WARNING_INFO  *  p  );

int  retrieveWarningMsgs(  QY_WARNING_INFO  *  p  );
int  submitWarningMsgs(  QY_WARNING_INFO  *  p  );

#endif





