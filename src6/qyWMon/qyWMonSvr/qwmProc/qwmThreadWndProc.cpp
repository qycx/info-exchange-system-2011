

#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<WtsApi32.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	"showPcProcess.h"

#ifndef		WM_WTSSESSION_CHANGE				   //  2007/02/27, 因在studio 6中没有定义，故在这里手工定义	
	#define		WM_WTSSESSION_CHANGE			   0x02B1
	//
		#define WTS_CONSOLE_CONNECT                0x1
		#define WTS_CONSOLE_DISCONNECT             0x2
		#define WTS_REMOTE_CONNECT                 0x3
		#define WTS_REMOTE_DISCONNECT              0x4
		#define WTS_SESSION_LOGON                  0x5
		#define WTS_SESSION_LOGOFF                 0x6
		#define WTS_SESSION_LOCK                   0x7
		#define WTS_SESSION_UNLOCK                 0x8
		#define WTS_SESSION_REMOTE_CONTROL         0x9

	#define NOTIFY_FOR_ALL_SESSIONS					1

#endif


#define		CONST_IDT_TIMER0						1

#define		CONST_maxExplorers						64
typedef  struct  __qwmWndProcInfo_usrScript_t		{
				 HANDLE								hProcess_usrScript;
				 //  DWORD								dwPid_usrScript;
				 DWORD								dwPid_Explorer;				 
				 //  unsigned  int						uiTickCnt_refreshed;
}		 QWM_WND_PROCINFO_usrScript;
typedef  struct  __qwmWndProcInfo_t					{
				 QWM_WND_PROCINFO_usrScript			mems[CONST_maxExplorers];
				 WCHAR								wAppName[MAX_PATH  +  1];
				 WCHAR								wCmdLine[32];
}		 QWM_WND_PROCINFO;

 BOOL  bmyRunProcessAsToken(  QY_ENV  *  pEnv,  HANDLE  hToken,  LPCWSTR  appName,  LPWSTR  cmdLine,  HANDLE  *  phProcess  )
{
	 BOOL					bResult			=  FALSE;
	 QWM_DYN_LIB		*	pDynLib			=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
	 STARTUPINFOW			si;
	 PROCESS_INFORMATION	pi;
	 PVOID					lpEnvironment	=	NULL;
	 
	 if  (  !pDynLib->pCreateEnvironmentBlock  
		 ||  !pDynLib->pDestroyEnvironmentBlock
			||  !pDynLib->pCreateProcessAsUserW  )  return  FALSE;

	 if  (  !appName  )  return  FALSE;

	 memset(  &pi,  0,  sizeof(  pi  )  );
	 memset(  &si,  0,  sizeof(  si  )  );
	 si.cb  =  sizeof(  si  );
	 si.lpDesktop  =  L"winsta0\\default";

	 if  (  pDynLib->pCreateEnvironmentBlock(  &lpEnvironment,    hToken,  FALSE  )  )  {

	 	 bResult  =  pDynLib->pCreateProcessAsUserW(  hToken,  appName,  cmdLine,  0,  0,  FALSE,  CREATE_UNICODE_ENVIRONMENT  |  DETACHED_PROCESS,  lpEnvironment,  NULL,  &si,  &pi  );

		 if  (  lpEnvironment  )  pDynLib->pDestroyEnvironmentBlock(  lpEnvironment  );	 
	 }

//  errLabel:

	 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
	 if  (  bResult  &&  phProcess  )  {  *phProcess  =  pi.hProcess;  }
	 else  {
		   if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }

	 return  bResult;

}

 BOOL  bmyRunProcess(  QY_ENV  *  pEnv,  DWORD  dwPid,  WCHAR  *  wBuf,  WCHAR  *  cmdLine,  HANDLE  *  phProcess  )
{
	 BOOL				bRet	=	FALSE;
	 QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
	  
	 HANDLE				hProcess		=	0;
	
	 hProcess  =  OpenProcess(  PROCESS_QUERY_INFORMATION,  FALSE,  dwPid  );
	 if  (  isHandleValid(  hProcess  )  )  {
		 HANDLE				hToken			=	0;
		 if  (  pDynLib->pOpenProcessToken(  hProcess,  TOKEN_ALL_ACCESS,  &hToken  )  )  {
			 HANDLE	hTokenUser	=	NULL;
			 BOOL  bResult  =  pDynLib->pDuplicateTokenEx(  hToken,  0,  0,  SecurityImpersonation,  TokenPrimary,  &hTokenUser  );
			 if  (  bResult  )  {
	 
				 bRet  =  bmyRunProcessAsToken(  pEnv,  hTokenUser,  wBuf,  cmdLine,  phProcess  );
	
				 CloseHandle(  hTokenUser  );

			 }
			 CloseHandle(  hToken  );
		 }
		 CloseHandle(  hProcess  );
	 }

	return  bRet;
}

 int  myGetWindowsDirectory(  QY_ENV  *  pEnv,  TCHAR  *  dir,  unsigned  int  uiCnt  )
{
	 TCHAR		buf[MAX_PATH  +  1]	=	_T(  ""  );
	 //  char	*	p;

	 /*
	 GetSystemDirectory(  buf,  sizeof(  buf  )  );
	 p  =  strstr(  buf,  "system"  );
	 if  (  p  )  *p  =  0;
	 */
	 GetWindowsDirectory(  buf,  mycountof(  buf  )  );		//  2007/03/03, 上面的strstr有错，因为可能会遇到System或system等各种情况．暂时先用GetWindowsDirectory(  ), 此函数被服务调用时，应该没问题

	 safeTcsnCpy(  buf,  dir,  uiCnt  );

	 return  0;
}



 BOOL  doMonAllUsrs(  QWM_THREADINFO  *  pThreadInfo,  QWM_WND_PROCINFO  *  pWndProcInfo,  BOOL  bSearchAllUsrs  )
{
	 BOOL				bRet							=  FALSE;
	 QY_W_MON		*	pQwm							=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_DYN_LIB	*	pDynLib							=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 HANDLE				hProcessSnap					=	NULL;
	 PROCESSENTRY32		pe32							=	{	0	};
	 TCHAR			*	lpName							=	_T(  "Explorer.exe"  );
	 WCHAR				wProcessName[MAX_PATH  +  1];
	 TCHAR				winDir[MAX_PATH  +  1]			=	_T(  ""  );
	 WCHAR				wPath[MAX_PATH  +  1];
	 
	 if  (  !pDynLib->pCreateToolhelp32Snapshot  )  return  FALSE;

	 traceLogA(  "doMonAllUsr(  ) enters"  );

	 myGetWindowsDirectory(  &pQwm->env,  winDir,  mycountof(  winDir  )  );
	 trailDir(  winDir,  mycountof(  winDir  )  );
	 _snwprintf(  wPath,  mycountof(  wPath  ),  L"%s%s",  winDir, lpName  );

	 hProcessSnap  =  pDynLib->pCreateToolhelp32Snapshot(  TH32CS_SNAPPROCESS,  0  );
	 if  (  !isHandleValid(  hProcessSnap  )  )  goto  errLabel;

	 pe32.dwSize  =  sizeof(  PROCESSENTRY32  );
	 if  (  !pDynLib->pProcess32First(  hProcessSnap,  &pe32  )  )  goto  errLabel;
	
	 do  {  
		 //  traceLog(  _T(  "pe32.szExeFile %s"  ),  pe32.szExeFile  );
		 //  OutputDebugString(  pe32.szExeFile  );  OutputDebugString(  _T(  "\n"  )  );

		 if  (  !lstrcmpi(  pe32.szExeFile,  lpName  )  &&  !getProcessNameById(  &pQwm->env,  pe32.th32ProcessID,  wProcessName,  mycountof(  wProcessName  ),  0,  0  )  )  {
			 //  因为担心路径两头可能被双引号括住，所以用查找匹配串的方式来确认。由于目录表示法的特殊性，所以这是没有问题的
			 if  (  !wcsicmp(  wProcessName,  wPath  )  )   {	
				 HANDLE				hProcess		=	0;
				 int				i;
				 BOOL				bInProcessInfo	=	FALSE;

				 //  先看此pid是否在wndProcInfo中了
				 for  (  i  =  0;  i  <  mycountof(  pWndProcInfo->mems  );  i  ++  )  {
					  if  (  pWndProcInfo->mems[i].dwPid_Explorer  ==  pe32.th32ProcessID  )  {
						  break;
					  }
				 }
				 if  (  i  ==  mycountof(  pWndProcInfo->mems  )  )  {	//  没被处理
				 
					 //  在找一个procInfo中的一个空馀
					 for  (  i  =  0;  i  <  mycountof(  pWndProcInfo->mems  );  i  ++  )  {
						  if  (  !pWndProcInfo->mems[i].dwPid_Explorer  )  break;
					 }
					 if  (  i  <  mycountof(  pWndProcInfo->mems  )  )  {

						 pWndProcInfo->mems[i].dwPid_Explorer  =  pe32.th32ProcessID;	//  将dwPid_explorer赋上

						 if  (  bmyRunProcess(  &pQwm->env,  pe32.th32ProcessID,  pWndProcInfo->wAppName,  pWndProcInfo->wCmdLine,  &hProcess  )  )  {
							 traceLog(  _T(  "pid_explorer usrScript"  ),  pWndProcInfo->mems[i].dwPid_Explorer  );
							 pWndProcInfo->mems[i].hProcess_usrScript  =  hProcess;	//  这里表明启动起来了
						 }

					 }

				 }

			 }			 
		 }
	
	 }	while  (  pDynLib->pProcess32Next(  hProcessSnap,  &pe32  )  );
	 

	 bRet  =  TRUE;

errLabel:
	 
	 if  (  isHandleValid(  hProcessSnap  )  )  CloseHandle(  hProcessSnap  );

	 return  bRet;
}


 int  doWaitForUsrScripts(  QWM_THREADINFO  *  pThreadInfo,  QWM_WND_PROCINFO  *  pWndProcInfo,  BOOL  bRecover  )
{
	 int							i;
	 QY_W_MON					*	pQwm							=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_DYN_LIB				*	pDynLib							=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 QWM_WND_PROCINFO_usrScript	*	p;
	 DWORD							dwRet;
	 WCHAR							wProcName[MAX_PATH  +  1];
	 WCHAR							wCmdLine[MAX_PATH  +  1];

	 traceLogA(  "doWaitForUsrScripts(  ) enters"  );

	 for  (  i  =  0;  i  <  mycountof(  pWndProcInfo->mems  );  i  ++  )  {
		  p  =  &pWndProcInfo->mems[i];
		  if  (  !p->dwPid_Explorer  )  continue;

		  if  (  p->hProcess_usrScript  )  {
			  dwRet  =   WaitForSingleObject(  p->hProcess_usrScript,  0  );
			  if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
				  traceLogA(  "pid_explorer is %d 的qwmSvr_usrScript退出来了",  p->dwPid_Explorer  ); 
				  CloseHandle(  p->hProcess_usrScript  );  p->hProcess_usrScript  =  0;
			  }
		  }

		  if  (  !p->hProcess_usrScript  )  {	//  如果usrScript退出来了，那么看explorer还在吗
			  if  (  getProcessNameById(  &pQwm->env,  p->dwPid_Explorer,  wProcName,  mycountof(  wProcName  ),  wCmdLine,  mycountof(  wCmdLine  )  )  )  {
				  traceLogA(  "pid_explorer is %d 的qwmSvr_usrScript退出来了",  p->dwPid_Explorer  );
				  p->dwPid_Explorer  =  0;
			  }				  
		  }

		  if  (  bRecover  )  {
		  	  if  (  p->dwPid_Explorer  &&  !p->hProcess_usrScript  )  {
				  HANDLE	hProcess	=	0;
				  if  (  bmyRunProcess(  &pQwm->env,  p->dwPid_Explorer,  pWndProcInfo->wAppName,  pWndProcInfo->wCmdLine,  &hProcess  )  )  {
					  traceLogA(  "恢复了pid_explorer为%d的usrScript",  pWndProcInfo->mems[i].dwPid_Explorer  );
					  pWndProcInfo->mems[i].hProcess_usrScript  =  hProcess;	//  这里表明启动起来了
				  }

		  	  }
		  }

	 }

	 return  0;
 }

 //  long  APIENTRY  myWndProc(  HWND  hWnd,  UINT  msg,  UINT  wParam,  LONG  lParam  )
 LRESULT CALLBACK myWndProc(  HWND  hWnd, UINT  msg,  WPARAM wParam, LPARAM  lParam  )
{
	char			*	p											=	"";
	static  DWORD		dwTickCnt_usrChanged						=	0;
	static  DWORD		dwTickCnt_usrChangeProced					=	0;
	static  DWORD		dwTickCnt_findAnyUsrNotMoned				=	0;
	static  DWORD		dwTickCnt_waitForUsrScripts					=	0;
	static  DWORD		dwTickCnt_WTSRegisterSessionNotification	=	0;
	
	switch  (  msg  )  {
			case  WM_DESTROY:
				  PostQuitMessage(  0  );
			  	  break;
			case  WM_TIMER:  {
				  COMMON_PARAM		*	pCommonParam					=	(  COMMON_PARAM  *  )GetWindowLong(  hWnd,  GWLP_USERDATA  );
				  QWM_THREADINFO	*	pThreadInfo						=	(  QWM_THREADINFO  *  )pCommonParam->p0;
				  QWM_WND_PROCINFO	*	pWndProcInfo					=	(  QWM_WND_PROCINFO  *  )pCommonParam->p1;
				  QY_W_MON			*	pQwm							=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
				  QWM_DYN_LIB		*	pDynLib							=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

				  traceLogA(  "myWndProc timer"  );

				  if  (  pQwm->bQuit  )  {
					  if  (  pQwm->status.ulbTimerSet  )  {
						  KillTimer(  hWnd,  CONST_IDT_TIMER0  );  pQwm->status.ulbTimerSet  =  FALSE;
					  }
					  if  (  pQwm->status.ulbWTSSessionNotificationRegistered  )  {
						  if  (  pDynLib->pWTSUnRegisterSessionNotification  )  pDynLib->pWTSUnRegisterSessionNotification(  hWnd  );
						  pQwm->status.ulbWTSSessionNotificationRegistered  =  FALSE;
					  }
					  DestroyWindow(  hWnd  );
					  break;
				  }
				  DWORD		dwTickCnt;
				  BOOL		bSearchAllUsrs;
				  //
				  dwTickCnt  =	GetTickCount(  );
				  bSearchAllUsrs	=	TRUE;
				  if  (  dwTickCnt  -  dwTickCnt_usrChangeProced  >  120  *  1000  )  {	//  每2分钟必遍历所有的用户处理一次
					  dwTickCnt_usrChangeProced  =  dwTickCnt;
					  doMonAllUsrs(  pThreadInfo,  pWndProcInfo,  bSearchAllUsrs  );
					  break;
				  }
				  if  (  dwTickCnt  >  dwTickCnt_usrChanged  +  5000  &&  dwTickCnt_usrChangeProced  <  dwTickCnt_usrChanged +  5000  )  {	//  当用户登陆等情况变化时必处理一次
					  dwTickCnt_usrChangeProced  =  dwTickCnt;
					  doMonAllUsrs(  pThreadInfo,  pWndProcInfo,  bSearchAllUsrs  );
					  break;
				  }
				  if  (  dwTickCnt  -  dwTickCnt_waitForUsrScripts  >  5000  )  {
					  dwTickCnt_waitForUsrScripts  =  dwTickCnt;
					  doWaitForUsrScripts(  pThreadInfo,  pWndProcInfo,  TRUE  );
					  break;
				  }
				  if  (  !pQwm->status.ulbWTSSessionNotificationRegistered  )  {		//  2007/02/28
					  if  (  dwTickCnt  -  dwTickCnt_WTSRegisterSessionNotification  >  10000  )  {
						  dwTickCnt_WTSRegisterSessionNotification  =  dwTickCnt;
                          if  (  pDynLib->pWTSRegisterSessionNotification  )  {
                         	  if  (  pDynLib->pWTSRegisterSessionNotification(  hWnd,  NOTIFY_FOR_ALL_SESSIONS  )  )  {	
								  traceLogA(  "WTSRegisterSessionNotification ok"  );
								  pQwm->status.ulbWTSSessionNotificationRegistered  =  TRUE;
							  }	 
						  }
					  }
				  }

				  //
					}
				  break;
			case  WM_WTSSESSION_CHANGE:
				  switch  (  wParam  )  {
						  case  WTS_CONSOLE_CONNECT:		p  =  "A session was connected to the console session";  break;
					 	  case  WTS_CONSOLE_DISCONNECT:		p  =  "A session was disconnected from the console session";  break;
						  case  WTS_REMOTE_CONNECT:			{
							    p  =  "A session was connected to the remote session. ";  
								dwTickCnt_usrChanged  =  GetTickCount(  );
								}
							    break;
					 	  case  WTS_REMOTE_DISCONNECT:		p  =  "A session was disconnected from the remote session. ";  break;
						  case  WTS_SESSION_LOGON:			{
								p  =  "A user has logged on to the session. ";  
								dwTickCnt_usrChanged  =  GetTickCount(  );
								}								
							    break;
					 	  case  WTS_SESSION_LOGOFF:			p  =  "A user has logged off the session. ";  break;
					 	  case  WTS_SESSION_LOCK:			p  =  "A session has been locked. ";  break;
					 	  case  WTS_SESSION_UNLOCK:			p  =  "A session has been unlocked. ";  break;
					 	  case  WTS_SESSION_REMOTE_CONTROL: p  =  "A session has changed its remote controlled status. To determine the status, call GetSystemMetrics and check the SM_REMOTECONTROL metric. ";  break;
					 	  default:
								  break;			
				  }
				  break;
		default:
				return  DefWindowProc(  hWnd,  msg,  wParam,  lParam  );
	
	}

	return  0;

}

 DWORD  WINAPI  qwmThreadWndProc(  LPVOID  lpParameter  )
{
	 int								iErr					=	-1;
	 QWM_THREADINFO						threadInfo;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG						threadCfg;
	 unsigned  int						loopCtrl				=	0;
	 HWND								hWnd					=	0;
	 QWM_DYN_LIB					*	pDynLib					=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 COMMON_PARAM						commonParam;
	 QWM_WND_PROCINFO					wndProcInfo;
	 TCHAR								tmpFileName[MAX_PATH  +  1];

	 switch  (  pQwm->env.iPlatformId  )  {
			 case  CONST_qyPlatform_win98:
			 case  CONST_qyPlatform_winme:
			 case  CONST_qyPlatform_nt:
				   return  -1;					//  注意这里要return -1;
			 default:
		   			 break;	 
	 }

	 traceLogA(  "qwmThreadWndProc enters"  );

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;

	 memset(  &wndProcInfo,  0,  sizeof(  wndProcInfo  )  );

	 GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
	 safeTcsnCpy(  tmpFileName,  wndProcInfo.wAppName,  mycountof(  wndProcInfo.wAppName  )  );
	 wcsncpy(  wndProcInfo.wCmdLine,  L"-rUsr",  mycountof(  wndProcInfo.wCmdLine  )  );

	 hWnd  =  CreateWindow( 
        			_T(  "WSCLAS"  ),        // name of window class 
       				_T(  ""  ),            // title-bar string 
       				WS_OVERLAPPEDWINDOW, // top-level window 
       				0,       // default horizontal position 
       				0,       // default vertical position 
       				0,       // default width 
       				0,       // default height 
       				(HWND) NULL,         // no owner window 
       				(HMENU) NULL,        // use class menu 
       				g_module,           // handle to application instance 
       				(LPVOID) NULL  );      // no window-creation data 
 
	 if  (  !hWnd  ) {
		 traceLogA(  "qwmThreadWndProc(  ):  CreateWindow(  ) failed"  );
		 goto  errLabel;
	 }
 
	 MACRO_makeCommonParam3(  (  void  *  )&threadInfo,  &wndProcInfo,  0,  commonParam  );
	 SetWindowLong(  hWnd,  GWLP_USERDATA,  (  long  )&commonParam  );

	 MSG	msg;

	 if  (  !SetTimer(  hWnd,  CONST_IDT_TIMER0,  1000,  0  )  )  {
		 traceLogA(  "SetTimer(  ) failed"  );  goto  errLabel;
	 }
	 pQwm->status.ulbTimerSet  =  TRUE;


	 while  (  GetMessage(  &msg,  (  HWND  )NULL,  0,  0  )  )  { 
        	TranslateMessage(&msg); 
        	DispatchMessage(&msg); 
     } 

	 hWnd  =  0;		//  这里应该hWnd已经被释放了

	 iErr  =  0;

errLabel:

	Sleep(  1000  );
	doWaitForUsrScripts(  &threadInfo,  &wndProcInfo,  0  );
	for  (  int  i  =  0;  i  <  mycountof(  wndProcInfo.mems  );  i  ++  )  {
		 if  (  wndProcInfo.mems[i].hProcess_usrScript  )  TerminateProcess(  wndProcInfo.mems[i].hProcess_usrScript,  0  );
	}
	Sleep(  1000  );
	doWaitForUsrScripts(  &threadInfo,  &wndProcInfo,  0  );

	if  (  hWnd  )  {
		if  (  pQwm->status.ulbTimerSet  )  {
			KillTimer(  hWnd,  CONST_IDT_TIMER0  );  pQwm->status.ulbTimerSet  =  FALSE;
		}
		if  (  pQwm->status.ulbWTSSessionNotificationRegistered  )  {
			if  (  pDynLib->pWTSUnRegisterSessionNotification  )  pDynLib->pWTSUnRegisterSessionNotification(  hWnd  );
			pQwm->status.ulbWTSSessionNotificationRegistered  =  FALSE;
		}
		DestroyWindow(  hWnd  );
	}

	traceLogA(  "qwmThreadWndProc leaves"  );

	return  iErr;
}