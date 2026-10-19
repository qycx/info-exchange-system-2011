

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//  #include	"resource.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"


 int  chkInternet(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo			=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool				=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 int							i;
	 int							cnt				=	0;
	 QY_DMITEM					*	pItem			=	CONST_wellKnownSiteTable;
  	 QNM_WMBUF_SHOWSECCHKEVENT		wmBuf;

	 
	 traceLogA(  "chkInternet enters."  );
	 
	 //	试图找到足够的连通网站数以证明连通外网了	 
	 for  (  i  =  0;  i  <  3;  i  ++,  pItem  ++  )  {			//  试图找到一个连通的 
		  if  (  canConnectWebSite(  pSubThreadInfo->pTo,  pItem  )  )  cnt  ++;
		  if  (  cnt  >=  CONST_minConnectedSites  )  break;
		  if  (  pRegTool->bQuit  )  {
			  iErr  =  CONST_qyRet_quit;  goto  errLabel;					//  探测退出条件，以提高响应速度
		  }
	 }
  	 
	 if  (  cnt  >=  CONST_minConnectedSites  )  {
		 
		 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
		 wmBuf.event.lEventType  =  CONST_qyEventType_nm_onInternet;
		 safeStrnCpy(  pRegTool->curUsrName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
		 getCurTime(  wmBuf.event.localEventTime  );
		 _snprintf(  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  ),  "该主机能够访问Internet"  );

		 if  (  addEventToCache(  pSubThreadInfo,  &wmBuf.event,  pRegTool  )  )  goto  errLabel;
		 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
		
	 }
	 
	 iErr  =  0;

errLabel:

	 traceLogA(  "chkInternet leaves."  );
	 
	 return  iErr;

}

