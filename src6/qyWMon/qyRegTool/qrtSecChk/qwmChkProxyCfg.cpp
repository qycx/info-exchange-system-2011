

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"asrWMon.h"
#include	"qyRegToolProc.h"



 int  chkProxyCfg(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{	 
	 int							iErr					=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo			=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool				=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 QWM_USR_INFO					usrInfo;
	 QY_REG							reg;
	 DWORD							dwProxyEnable			=	FALSE;
	 QNM_WMBUF_SHOWSECCHKEVENT		wmBuf;
	 TCHAR							tBuf[256];

	 //  下面取代理配置,	2003/09/14
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyRootKey_internetSettings  ),  mycountof(  reg.rootKey  )  );
	 
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyServer  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 myTChar2Utf8(  tBuf,  usrInfo.proxyServer,  mycountof(  usrInfo.proxyServer  )  );
	 trim(  usrInfo.proxyServer  );
	 if  (  !usrInfo.proxyServer[0]  )  {
		 traceLogA(  "当前用户没有代理设置"  );
		 iErr  =  0;  goto  errLabel;
	 }	 	
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyEnable  ),  (  char  *  )&dwProxyEnable,  sizeof(  dwProxyEnable  )  )  )  dwProxyEnable  =  FALSE;
	 	 
	 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
	 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
	 wmBuf.event.lEventType  =  CONST_qyEventType_secChk_proxyCfg;
	 safeStrnCpy(  pRegTool->curUsrName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
	 getCurTime(  wmBuf.event.localEventTime  );
	 _snprintf(  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  ),  "%s: %s",  dwProxyEnable  ?  "激活"  :  "失效",  usrInfo.proxyServer  );

	 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  goto  errLabel;
	 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
  	 
	 iErr  =  0;

errLabel:

	 return  iErr;

}
