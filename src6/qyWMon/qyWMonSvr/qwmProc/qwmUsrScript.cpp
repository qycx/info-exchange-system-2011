

#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	"qyRegToolProc.h"
#include	<tchar.h>
#include	"qySyncCommProc.h"

int  getQwmCommonStatus(  QY_W_MON  *  pQwm,  QWM_COMMON_STATUS  *  pCommonStatus  );
BOOL  bUsrInAdminGrp(  QY_ENV  *  pEnv,  LPCWSTR  wUsrName,  LPCWSTR  wDomainName  );

 //  bIpLocal(

 int  initAsrWMon_usrScript(  QWM_THREADINFO  *  pThreadInfo  )
{
	int				iErr					=		-1;
	QY_W_MON	*	pQwm					=		(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	DWORD			dwThreadId;	
	int				i						=		0;
	char		*	remoteProcessName		=		CONST_remoteProcessName_usr;
	WCHAR			wBuf[256];
	char			buf[256];

	// 取得MAC地址
	getQwmMacs(  &pQwm->env,  &pQwm->macsInfo  );  

	if  (  getQwmCfg(  pQwm,  TRUE  )  )  goto  errLabel;

	_snwprintf(  wBuf,  mycountof(  wBuf  ),  L"%s@%s",  pQwm->wUsrName,  pQwm->wDomainName  );
	if  (  !myWChar2Utf8(  wBuf,  buf,  mycountof(  buf  )  )  )  buf[0]  =  0;
	if  (  bUsrInAdminGrp(  &pQwm->env,  pQwm->wUsrName,  pQwm->wDomainName  )  )  pQwm->status.ulbUsrInAdminGrp  =  TRUE;

	if  (  pQwm->status.ulbUsrInAdminGrp  )  {
		if  (  pQwm->cfg.pcRules.os.ucAdminCmd  ==  CONST_devCmd_prohibited  )  {
			traceLogA(  "此用户属于admin组, 将按要求被注销"  );
			qwmLogGeneralEvent(  pThreadInfo,  CONST_qyEventType_nm_usrMgr,  buf,  " Logon is not permitted!",  0,  TRUE  );
			ExitWindowsEx(  EWX_LOGOFF  |  EWX_FORCE,  0  );
			goto  errLabel;
		}
	}
	qwmLogGeneralEvent(  pThreadInfo,  CONST_qyEventType_nm_usrMgr,  buf,  " Logon",  0,  TRUE  );
		

	traceLogA(  "2005/07/28增加对远程保护线程的生成"  );

	//  这里设置qwmHelp2.dll的版本是否正确的标志位, 2005/07/28
	//  if  (  !pQwm->pure2DllName[0]  )  _snprintf(  pQwm->pure2DllName,  sizeof(  pQwm->pure2DllName  ),  "%s",  CONST_qwmHelp2Dll  );  
	if  (  bMyHideSupportedOs(  pQwm->env.iPlatformId,  0,  0  )
		&&  bMyQwmHelpDllVerRight(  pQwm->env.iPlatformId,  pQwm->pure2DllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )
			&&  pQwm->cfg.ucbNetMc2  )  //  注意：只有内网管理才在这里启动保护线程
	{
		pQwm->status.ulbQwmHelp2VerRight  =  TRUE;  
	}
	if  (  gQyWMon.status.ulbQwmHelp2VerRight  )  {
		//  2007/01/15, 装载qwmHelp2.dll
		loadQwmHelp2Dll(  pQwm,  pQwm->pure2DllName  );
	}

	//  启动保护线程.  2007/02/28, 对用户进程的管理变为由后台直接启动，故暂时不需要保护线程了	
	//  myProcQwmHelp2(  &gQyWMon,  pQwm->env.iPlatformId,  pQwm->pure2DllName,  remoteProcessName  );
	
	
	// 下面采用进程隐藏来防杀
	//  2007/02/20, 仅在服务进程那里做进程隐藏
	if  (  pQwm->cfg.ucbHideQwm  )  {
		if  (  !myHideProcess(  pQwm->env.iPlatformId,  pQwm->pureDllName  )  )  pQwm->status.ulbProcessHiden  =  TRUE;
	}	

	
	i  =  0;

	/*
	if  (  !(  pQwm->hThreads[0]  =  CreateThread(  NULL,  0,  qwmThreadProcFastCmd,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
	*/
	/*	 
    if  (  pQwm->cfg.ulbQwmThreadProcCmd  )  {
		if  (  !(  pQwm->hThreads[1]  =  CreateThread(  NULL,  0,  qwmThreadProcCmd,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
	}
	if  (  pQwm->cfg.ulbQwmThreadPrinterMgr  )  {
		if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadPrinterMgr,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
		i  ++  ;
	}
	if  (  pQwm->cfg.ulbQwmThreadFileMon  )  {
		if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadFileMon,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
		i  ++  ;
	}
	*/

	if  (  pQwm->cfg.ulbQwmThreadPcMon  )  {	//  2006/03/05
		if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadPcMon,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
		i  ++  ;
	}

	MACRO_qyAssert(  i  <  sizeof(  pQwm->hThreads  )  /  sizeof(  pQwm->hThreads[0]  ),  _T(  ""  )  );

	//

#ifdef  __DEBUG__
	testInitQwmHook(  );   
#endif

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		
		exitAsrWMon_usrScript(  pThreadInfo  );
		
	}
	traceLogA(  "initAsrWMon_usrScript( ) leaves, with iErr is %d.",  iErr  );

	 return  iErr;
}

 void  exitAsrWMon_usrScript(  QWM_THREADINFO  *  pThreadInfo  )
{
	QY_W_MON	*	pQwm					=		(  QY_W_MON  *  )pThreadInfo->pParaentParam;

	exitAsrWMon(  pQwm  );
}

 void  commandHandlerLoop_usrScript(  void  )
{
	int						iErr					=	-1;
	QY_W_MON			*	pQwm					=	&gAsrWMon;
	BOOL					bInited					=	FALSE;
	int						loopCtrl				=	0;
	
	QWM_THREADINFO			threadInfo;
	QWM_THREAD_CFG			threadCfg;

	memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	threadInfo.pParaentParam  =  &gQyWMon;
	threadInfo.pCfg  =  &threadCfg;

	traceLogA(  "CommandHandlerLoop_usrScript enters"  );

	if  (  initAsrWMon_usrScript(  &threadInfo  )  )  goto  errLabel;
	bInited  =  TRUE;

	for  (  loopCtrl  =  CONST_qwmConnectIntervalLoops;  ;  loopCtrl  ++  )  {

		 Sleep(  1000  );

		 if  (  !(  loopCtrl  %  2  )  )  {
			 getQwmCfg(  pQwm,  TRUE  );
			 if  (  pQwm->cfg.ucbStopMon_usrScript  )  {
				 traceLogA(  "得到了退出指令"  );  goto  errLabel;
			 }
		 }

		 if  (  !(  loopCtrl  %  10  )  )  {
			 QWM_COMMON_STATUS		commonStatus;
			 if  (  !getQwmCommonStatus(  pQwm,  &commonStatus  )  )  {
				 if  (  memcmp(  &pQwm->status.common,  &commonStatus,  sizeof(  pQwm->status.common  )  )  )
					 memcpy(  &pQwm->status.common,  &commonStatus,  sizeof(  pQwm->status.common  )  );
			 }
		 }
		 
		 /*
		 */


		 
		 //  traceLogA(  "commandHandlerLoop_usrScript: loopCtrl is %d",  loopCtrl  );

	}


	iErr  =  0;

errLabel:

	if  (  bInited  )  exitAsrWMon_usrScript(  &threadInfo  );
	
	traceLogA(  "CommandHandlerLoop_usrScript leaves"  );
	
	return;

}
