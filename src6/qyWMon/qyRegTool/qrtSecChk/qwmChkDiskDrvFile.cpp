


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

 extern  "C"  void					chkDiskDrvMain(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  unsigned  char  ucbSecChkQuickly  );

 //  检查磁盘文件
 //  完成时pRegTool->iProgress应等于CONST_qrtStep_chkDiskDrvFile
 int  chkDiskDrvFile(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 int							iErr			=	-1;
	 char							drvName[128]	=   "";
	 MT_SUBTHREADINFO			*	pSubThreadInfo	=  (  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=  (  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 	 	
	 if  (  !g_bIsWinNT  )  {	//  2004/03/14
		 traceLogA(  "注意：尚未完成对98和Me的处理。"  );
		 goto  errLabel;		//////////////////////
	}

	 chkDiskDrvMain(  pSubThreadInfoParam,  NULL,  pRegTool->cfg.ucbSecChkQuickly  );

	 iErr  =  0;
errLabel:
	 return  iErr;

}

 extern  "C"  int  displayChkDiskEvent(  void  *  pSubThreadInfoParam,  
										 long	  lEventType,
										 char  *  localEventTime,		//  事件的本地时间
										 char  *  usrName,
										 char  *  des0,					//  事件描述
										 char  *  des1,					//  事件描述1, 2004/03/14												
										 char  *  des2			  )		//  事件描述2
{
	 int							iErr			=	-1;
	 char							drvName[128]	=   "";
	 MT_SUBTHREADINFO			*	pSubThreadInfo	=  (  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=  (  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 QNM_WMBUF_SHOWSECCHKEVENT		wmBuf;
	 
	 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
	 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
	 wmBuf.event.lEventType  =  lEventType;		//  CONST_qyEventType_secChk_fileHistory;
	 if  (  usrName  )  safeStrnCpy(  usrName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
	 if  (  localEventTime  )  safeStrnCpy(  localEventTime,  wmBuf.event.localEventTime,  sizeof(  wmBuf.event.localEventTime  )  );
	 	 
	 if  (  des0  )  _snprintf(  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  ),  "%s",  des0  );
	 if  (  des1  )  _snprintf(  wmBuf.event.des1,  sizeof(  wmBuf.event.des1  ),  "%s",  des1  );
	 if  (  des2  )  _snprintf(  wmBuf.event.des2,  sizeof(  wmBuf.event.des2  ),  "%s",  des2  );
	 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  goto  errLabel;
	 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


