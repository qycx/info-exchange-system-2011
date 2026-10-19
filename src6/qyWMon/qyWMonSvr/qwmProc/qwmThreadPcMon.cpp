
#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<tchar.h>
#include	<iphlpapi.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"




 DWORD  WINAPI  qwmThreadPcMon(  LPVOID  lpParameter  )
{
	 QWM_THREADINFO						threadInfo;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG						threadCfg;
	 QY_REG								reg;
	 //  int								loopCtrl;
	 unsigned  int						uiTickCnt				=	0;
	 unsigned  int						uiTickCnt_capScreenCmd	=	0;
	 unsigned  char						ucbCapScreen			=	FALSE;
	 //  DWORD								dwRet;
	 unsigned  int						loopCtrl				=	0;
	 int								iRet;
	 DWORD								dwCurSessId				=	-1;
	 DWORD								dwActiveSessId			=	-1;
	 HANDLE								hRdProcess			=	NULL;
	 DWORD								dwRet;



	 traceLogA(  "qwmThreadPcMon enters"  );

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;
	 lstrcpy(  reg.rootKey,  _T(  ROOT_KEY_AWM  )  );  
	 reg.pEncCtx  =  &pQwm->encCtx;

	 //
	 for  (  ;  !pQwm->bQuit ;  Sleep(  2000  ),  loopCtrl  ++  )  {

		  uiTickCnt  =  GetTickCount(  );


		  //  2007/02/04, 先取活跃sessionId和当前sessionId		
		  if  (  !getWtsSessionId(  &pQwm->env,  &dwCurSessId,  &dwActiveSessId  )  )  {
			  if  (  dwCurSessId  !=  pQwm->dwCurSessionId  )  pQwm->dwCurSessionId  =  dwCurSessId;
			  if  (  dwActiveSessId  !=  pQwm->dwActiveSessionId  )  pQwm->dwActiveSessionId  =  dwActiveSessId;
		  }


		  if  (  pQwm->cfg.ucbNetMc2  )  {

			  ucbCapScreen  =  FALSE;
			  if  (  pQwm->status.common.ucbServerOnline  )  {
				  if  (  pQwm->cfg.pcRules.pcMon.ucCapScreenCmd  ==  CONST_devCmd_permitted  ||  pQwm->cfg.getOpCmd.ucbMonDesktop  )  ucbCapScreen  =  TRUE;
			  }
			  //

			  if  (  ucbCapScreen  )  {
				  unsigned  short	usCapScreenIntervalInS  =  pQwm->cfg.pcRules.pcMon.usCapScreenInterval;
				  if  (  pQwm->cfg.getOpCmd.ucbMonDesktop  )  usCapScreenIntervalInS  =  min(  usCapScreenIntervalInS,  pQwm->cfg.getOpCmd.ucbMonDesktop  );
				  usCapScreenIntervalInS  =  max(  usCapScreenIntervalInS,  2  );	//  确保不要太小
		  
				  if  (  uiTickCnt  -  uiTickCnt_capScreenCmd  >  (  unsigned  int  )usCapScreenIntervalInS  *  1000  )  {
					  iRet  =  qwmCapScreen(  &threadInfo,  0,  pQwm->cfg.getOpCmd.ucbMonDesktop  );
					  if  (  iRet  >  0  )  showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_capScreenNotSupported,  0  );
					  if  (  iRet  )  traceLogA(  "qwmCapScreen如果抓屏不成功或者发送不成功"  );
					  uiTickCnt_capScreenCmd  =  uiTickCnt;
				  }

			  }


			  if  (  g_bIsWinNT  &&  pQwm->env.iPlatformId  !=  CONST_qyPlatform_winnt  )  {
			  	  //  2007/02/04, 处理远程桌面
			  	  //
			  	  if  (  !hRdProcess  )  {
					  if  (  dwCurSessId  ==  dwActiveSessId  &&   dwActiveSessId  )  {		//  dwActiveSessId为0时只能由服务启动远程桌面
						  if  (  pQwm->cfg.getOpCmd.ucbViewRemoteDesktop  )  {	//  启动远程桌面				  
							  qwmCmdBySubProcess(  0,  _T(  CONST_qwmCmdLine_viewRemoteDesktop  ),  0,  &hRdProcess  );								
						  }
						  //  else  if  (  pQwm->cfg.getOpCmd.ucbMonDesktop  )  {		//  2006/03/06, 处理实时屏幕监控
						  //			qwmCmdBySubProcess(  0,  CONST_qwmCmdLine_monDesktop,  0,  &hRdProcess  );
						  //  }
					  }
				  }
			
				  if  (  hRdProcess  )  {		//  取消远程桌面
					  //  if  (  dwCurSessId  !=  dwActiveSessId  ||  !dwActiveSessId  ||  (  !pQwm->cfg.getOpCmd.ucbViewRemoteDesktop  &&  !pQwm->cfg.getOpCmd.ucbMonDesktop  )  )  
					  if  (  dwCurSessId  !=  dwActiveSessId  ||  !dwActiveSessId  ||  (  !pQwm->cfg.getOpCmd.ucbViewRemoteDesktop  )  )  {		//  
						  const  TCHAR  *	MENU_CLASS_NAME = _T(  "WinVNC Tray Icon"  );
						  HWND				hWnd			=	NULL;

						  if  (  (  hWnd  =  FindWindow(  MENU_CLASS_NAME,  NULL  )  )  )  {	//  看看能不能关掉vnc
							  PostMessage(  hWnd, WM_CLOSE, 0, 0  );
						  }
					  }
				  }
				  if  (  hRdProcess  )  {
					  dwRet  =  ::WaitForSingleObject(  hRdProcess,  200  );
					  if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {		//  进程退出则回收资源
						  CloseHandle(  hRdProcess  );  hRdProcess  =  NULL;
					  }
				  }

			  }
	  
			  if  (  g_bIsWinNT  )  {
			  	  if  (  pQwm->status.ulbUsrInAdminGrp  )  {
					  if  (  pQwm->cfg.pcRules.os.ucAdminCmd  ==  CONST_devCmd_prohibited  )  {
						  char	buf[256];
						  WCHAR	wBuf[256];
						  //					  	
						  _snwprintf(  wBuf,  mycountof(  wBuf  ),  L"%s@%s",  pQwm->wUsrName,  pQwm->wDomainName  );
						  if  (  !myWChar2Utf8(  wBuf,  buf,  mycountof(  buf  )  )  )  buf[0]  =  0;
						  //
						  traceLogA(  "此用户属于admin组, 将按要求被注销"  );
						  qwmLogGeneralEvent(  &threadInfo,  CONST_qyEventType_nm_usrMgr,  buf,  " Logon is not permitted!",  0,  TRUE  );
						  ExitWindowsEx(  EWX_LOGOFF  |  EWX_FORCE,  0  );
						  goto  errLabel;
					  }
				  }
			  }

		  }

	 }


errLabel:


	 if  (  isHandleValid(  hRdProcess  )  )  {	//  2006/02/12
		 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_terminateChd,  0  );
		 traceLogA(  "远程桌面子进程尚未退出，强制终止其运行"  );
		 TerminateProcess(  hRdProcess,  1  );
		 CloseHandle(  hRdProcess  );  hRdProcess  =  NULL;  
	 }


	 traceLogA(  "qwmThreadPcMon leaves"  );

	 return  0;
}


