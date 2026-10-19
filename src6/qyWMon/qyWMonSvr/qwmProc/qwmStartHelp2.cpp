
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
#include	"qwmHideProcessCommProc.h"





 //  需要找到指定wAccountName和指定wDomainName的procName
 unsigned  long  getTargetProcessIdFromProcname(  QY_ENV  *  pEnv,  TCHAR  *  procName,  LPCWSTR  wAccountName,  LPCWSTR  wDomainName  )
{
   PROCESSENTRY32	pe;
   HANDLE			thSnapshot				=	NULL;
   BOOL				retval,  ProcFound		=	false;
   WCHAR			tmpwAccountName[256]	=	L"";
   WCHAR			tmpwDomainName[256]		=	L"";
   QWM_DYN_LIB	*	pDynLib					=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

   thSnapshot  =  pDynLib->pCreateToolhelp32Snapshot(  TH32CS_SNAPPROCESS,  0  );
   if  (  thSnapshot  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;

   pe.dwSize  =  sizeof(  PROCESSENTRY32  );

   retval  =  pDynLib->pProcess32First(  thSnapshot,  &pe  );
   while  (  retval  )  {
	      if  (  !lstrcmpi(  pe.szExeFile,  procName  )  )  {
			  if  (  !getProcessUsrAndDomain(  pEnv,  pe.th32ProcessID,  tmpwAccountName,  mycountof(  tmpwAccountName  ),  tmpwDomainName,  mycountof(  tmpwDomainName  )  )  )  {
				  BOOL  bCmped  =  TRUE;
				  if  (  wAccountName  &&  wAccountName[0]  &&  wcsicmp(  tmpwAccountName,  wAccountName  )  )  bCmped  =  FALSE;
				  if  (  wDomainName  &&  wDomainName[0]  &&  wcsicmp(  tmpwDomainName,  wDomainName  )  )  bCmped  =  FALSE;
				  //
				  if  (  bCmped  )  {
					  ProcFound  =  true;
         	  		  break;
				  }
			  }
      	  }

		  retval  =  pDynLib->pProcess32Next(  thSnapshot,  &pe  );
      	  pe.dwSize  =  sizeof(  PROCESSENTRY32  );
   }
errLabel:
   if  (  isHandleValid(  thSnapshot  )  )  CloseHandle(  thSnapshot  );
   return ProcFound  ?  pe.th32ProcessID  :  0;
}


 int  myStartProtectingThread(  void  *  pQwmParam,	int  iPlatformId,  TCHAR  *  pure2DllName,  TCHAR  *  remoteProcessName  )  
{
	 int			iErr						=	-1;
	 QY_W_MON	*	pQwm						=	(  QY_W_MON  *  )pQwmParam;
	 BOOL			bTokenAdjusted				=	FALSE;	
	 HANDLE			hProcess					=	NULL;
	 LPVOID			RemoteString				=	NULL, LoadLibAddy  =  NULL;
	 int			nRemoteString				=	0;
	 DWORD			dwProcId					=	0;
	 HANDLE			hThread						=	NULL;
	 void		*	pDataRemote					=	NULL;
	 HANDLE			hLibModule					=	NULL;
	 TCHAR			dllPath[MAX_PATH  +  1];
	 QWM_DYN_LIB	*	pDynLib					=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 if  (  bMyHideSupportedOs(  gQyWMon.env.iPlatformId,  0,  0  )
		&&  bMyQwmHelpDllVerRight(  gQyWMon.env.iPlatformId,  gQyWMon.pure2DllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )
			&&  gQyWMon.cfg.ucbNetMc2  )  //  注意：只有内网管理才在这里启动保护线程
	{
		gQyWMon.status.ulbQwmHelp2VerRight  =  TRUE;  
	}

	 if  (  !pQwm->status.ulbQwmHelp2VerRight  )  return  -1;

	 //
	 traceLogA(  "myStartProtectingThread enters"  );
	 
	 if  (  g_bIsWinNT  )  {
		HANDLE tok;
		if  (  pDynLib->pOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&tok)  )  {
			LUID luid;
			TOKEN_PRIVILEGES tp;
			
			pDynLib->pLookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid);
			tp.PrivilegeCount=1;
			tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid=luid;
			pDynLib->pAdjustTokenPrivileges(tok,FALSE,&tp,NULL,NULL,NULL);
			
			CloseHandle(tok);

			bTokenAdjusted  =  TRUE;

		}
	 }

	 dwProcId  =  pQwm->cmd.ulProcessId_remoteProcess;

	 {
	 
		   traceLogA(  "to open remote"  );
		   if  (  !(  hProcess  =  OpenProcess(  PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,  FALSE, dwProcId  )  )  )  {
			   traceLogA(  "OpenProcess() failed: %d", GetLastError(  )  );  goto  errLabel;
		   }
	 
		   GetSystemDirectory(  dllPath,  mycountof(  dllPath  )  );
		   trailDir(  dllPath,  mycountof(  dllPath  )  );
		   _sntprintf(  dllPath,   mycountof(  dllPath  ),  _T(  "%s%s"  ),  dllPath,  pQwm->pure2DllName  );
		   nRemoteString   =  (  lstrlen(  dllPath  )  +  1  )  *  sizeof(  TCHAR  ); 

		   traceLogA(  "to write memory"  );
		   if  (  !(  RemoteString  =  (  LPVOID  )pDynLib->pVirtualAllocEx(  hProcess,  NULL,  nRemoteString,  MEM_COMMIT,  PAGE_READWRITE  )  )  )  goto  errLabel;
		   if  (  !WriteProcessMemory(  hProcess,  (  LPVOID  )RemoteString,  dllPath,  nRemoteString,  NULL  )  )  goto errLabel;

		   traceLogA(  "to load remote"  );
		   pDataRemote  =  RemoteString;
		   //  LoadLibAddy = (LPVOID)GetProcAddress(  GetModuleHandle(  _T(  "kernel32.dll"  )  ),  "LoadLibraryA"  );
		   LoadLibAddy = (LPVOID)GetProcAddress(  GetModuleHandle(  _T(  "kernel32.dll"  )  ),  "LoadLibraryW"  );
		   if  (  !(  hThread  =  pDynLib->pCreateRemoteThread(  hProcess,  NULL,  NULL,  (  LPTHREAD_START_ROUTINE  )LoadLibAddy,  (  LPVOID  )RemoteString,  NULL,  NULL  )  )  )  goto  errLabel;
		   ::WaitForSingleObject(  hThread,  INFINITE  );

		   #ifdef  __DEBUG__
				   traceLogA(  "to get exit code thread"  );
		   #endif
		   if  (  !::GetExitCodeThread( hThread, (  DWORD  *  )&hLibModule )  )  goto  errLabel;

	 }

#ifdef  __DEBUG__
	 traceLogA(  "start protecting thread ok"  );
#endif
	 pQwm->hRemoteModule  =  hLibModule;
	 pQwm->dwRemoteProcId  =  dwProcId;

	 iErr  =  0;

errLabel:

	 //  扫尾工作
	 if  (  hThread  )  ::CloseHandle(  hThread  );
	 if  (  RemoteString  )  pDynLib->pVirtualFreeEx(  hProcess,  RemoteString,  nRemoteString,  MEM_RELEASE  );
	 if  (  hProcess  )  CloseHandle(  hProcess  );

	 if  (  g_bIsWinNT  &&  bTokenAdjusted  )  {
		HANDLE tok;
		if  (  pDynLib->pOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&tok)  )  {
			LUID luid;
			TOKEN_PRIVILEGES tp;
			
			pDynLib->pLookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid);
			tp.PrivilegeCount=1;
			tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid=luid;
			pDynLib->pAdjustTokenPrivileges(tok,TRUE,&tp,NULL,NULL,NULL);
			
			CloseHandle(tok);
		}
	 }

	 traceLog(  _T(  "myStartProtectingThread leaves %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	 return  iErr;		
}


 int  myProcQwmHelp2(  void  *  pQwmParam,	int  iPlatformId,  TCHAR  *  pure2DllName,  TCHAR  *  remoteProcessName  )  
{
	 int				iErr						=	-1;
	 QY_W_MON		*	pQwm						=	(  QY_W_MON  *  )pQwmParam;
	 QWM_DYN_LIB	*	pDynLib						=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 DWORD				dwProcId					=	0;
	 HANDLE				hMutexForRemote				=	NULL;
	 BOOL				bMutexForRemoteExists		=	FALSE;
	 TCHAR				buf[512];
	 WCHAR				wAccountName[256]			=	L"";
	 WCHAR				wDomainName[256]			=	L"";

	 if  (  !pQwm->status.ulbQwmHelp2VerRight  )  return  -1;

	 if  (  isHandleValid(  pQwm->hRemoteModule  )  )  return  0;

	 if  (  pQwm->cmd.ulbUsrScript  )  {
		 if  (  getProcessUsrAndDomain(  &pQwm->env,  GetCurrentProcessId(  ),  wAccountName,  mycountof(  wAccountName  ),  wDomainName,  mycountof(  wDomainName  )  )  )  goto  errLabel;
		}
	 else  {	//  对qwmSvr, 应该找用户名是System的进程来做为保护场所, wDomainName[0]设为0表不区分域
		   wcsncpy(  wAccountName,  L"System",  mycountof(  wAccountName  )  );
		   wDomainName[0]  =  0;
	 }

	 //  先等待remoteProcess启动完毕
	 if  (  bMyHideSupportedOs(  pQwm->env.iPlatformId,  0,  0  )  )  {
		 traceLog(  _T(  "wait for %s"  ),  remoteProcessName  );
		 for  (  ;  ;  )  {
			 if  (  getTargetProcessIdFromProcname(  &pQwm->env,  remoteProcessName,  wAccountName,  wDomainName  )  )  break;
			 Sleep(  1000  );
		 }
		 traceLog(  _T(  "%s on"  ),  remoteProcessName  );		 
	 }

	 if  (  !(  dwProcId  =  getTargetProcessIdFromProcname(  &pQwm->env,  remoteProcessName,  wAccountName,  wDomainName  )  )  )  goto  errLabel;

	 traceLogA(  "下面建立远程同步的mutex"  );
	 if  (  !pQwm->cmd.ulbUsrScript  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s"  ),  _T(  CONST_mutexNameForRemote  )  );
	 else  {
		   if  (  pQwm->cmd.ulProcessId_remoteProcess  )  dwProcId  =  pQwm->cmd.ulProcessId_remoteProcess;
		   //
		   _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%u"  ),  _T(  CONST_mutexNameForRemote  ),  dwProcId  );
	 }

	 hMutexForRemote = CreateMutex(  NULL,  FALSE,  buf  );
	 if  (  !hMutexForRemote  )  {
		traceLogA(  "myProcQwmHelp2( ): CreateMutex( ) failed. "  );  goto  errLabel;
	 }
	 if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  bMutexForRemoteExists  =  TRUE;
	 if  (  WaitForSingleObject(  hMutexForRemote,  INFINITE  )  ==  WAIT_FAILED  )  {
		 traceLogA(  "myProcQwmHelp2: WaitForSingleObject failed"  );  goto  errLabel;
	 }

	 if  (  !pQwm->cmd.ulProcessId_remoteProcess  &&  !bMutexForRemoteExists  )  {
		 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%u"  ),  dwProcId  );
		 if  (  qwmCmdBySubProcess(  0,  pQwm->cmd.ulbUsrScript  ?  _T(  CONST_qwmCmdLine_startProtectingThread_usr  )  :  _T(  CONST_qwmCmdLine_startProtectingThread_sys  ),  buf,  NULL  )  )  goto  errLabel;
		}
	 else  {
		   traceLogA(  "ulProcessId_remoteProcess is %d,  bMutexForRemoteExists is %s,  不用启动保护线程",  pQwm->cmd.ulProcessId_remoteProcess,  bMutexForRemoteExists  ?  "True"  :  "False"  );
	 }

	 pQwm->hMutexForRemote  =  hMutexForRemote;  hMutexForRemote  =  NULL;

	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  hMutexForRemote  )  )  {
		 ReleaseMutex(  hMutexForRemote  );  CloseHandle(  hMutexForRemote  );
	 }

	 return  iErr;
}


 void  myClearQwmHelp2(  void  *  pQwmParam  )
{
	 int			iErr			=	-1;
	 QY_W_MON	*	pQwm			=  (  QY_W_MON  *  )pQwmParam;
	 BOOL			bTokenAdjusted	=	FALSE;	
	 HANDLE			hProcess		=	NULL;
	 HANDLE			hThread			=	NULL;
	 int			i;
	 HANDLE			hMutexForClear	=	NULL;
	 //  char			buf[512];
	 QWM_DYN_LIB	*	pDynLib		=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 traceLogA(  "myClearQwmHelp2 enters"  );

	 //  先关掉同步远程线程的mutex
	 if  (  isHandleValid(  pQwm->hMutexForRemote  )  )  {
		 ReleaseMutex(  pQwm->hMutexForRemote  );  CloseHandle(  pQwm->hMutexForRemote  );  pQwm->hMutexForRemote  =  NULL;
	 }

	 if  (  pQwm->cmd.ulbUsrScript  )  {
		 traceLogA(  "用户脚本不用清理qwmHelp2, 所以直接退出"  );
		 iErr  =  0;  goto  errLabel;
	 }

	 traceLogA(  "这里等待qwmHelp2退出"  );

	 for  (  i  =  0;  i  <  10;  i  ++  )  {
		  Sleep(  1000  );
		  traceLogA(  "myClearQwmHelp2: wait %d seconds for qwmHelp2 to quit",  i  ); 
	 }

	 /*  //  2007/01/31, 因为现在不在主进程中启动线程，因为似乎explorer.exe要出错，所以呢，就不再在主进程中卸载远程线程
	 if  (  isHandleValid(  pQwm->hRemoteModule  )  )  {

		 if  (  g_bIsWinNT  )  {
			 HANDLE tok;
			 if  (  pDynLib->pOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&tok)  )  {
				 LUID luid;
				 TOKEN_PRIVILEGES tp;
			
				 pDynLib->pLookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid);
				 tp.PrivilegeCount=1;
				 tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
				 tp.Privileges[0].Luid=luid;
				 pDynLib->pAdjustTokenPrivileges(tok,FALSE,&tp,NULL,NULL,NULL);
				
				 CloseHandle(tok);
			
				 bTokenAdjusted  =  TRUE;

			 }
		 }


		 //  下面将准备卸载qwmHelp2.dll
		 if  (  !(  hProcess  =  OpenProcess(  PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,  FALSE,  pQwm->dwRemoteProcId  )  )  )  {
			 traceLogA(  "OpenProcess() failed: %d", GetLastError(  )  );  goto  errLabel;
		 }

		 traceLogA(  "卸载qwmHelp2.dll"  );
		 // (通过 CreateRemoteThread & FreeLibrary)
		 hThread  = pDynLib->pCreateRemoteThread(  hProcess,  NULL,  0,
										(  LPTHREAD_START_ROUTINE  )::GetProcAddress(  GetModuleHandle(  "kernel32.dll"  ),  "FreeLibrary" ),     
										(void*)pQwm->hRemoteModule,  0,  NULL  );
		 if  (  !isHandleValid(  hThread  )  )  goto  errLabel;
		 ::WaitForSingleObject(  hThread,  20000  );

		 pQwm->hRemoteModule  =  NULL;

	 }
	 */

	iErr  =  0;

errLabel:

	 //  扫尾工作
	 if  (  hThread  )  ::CloseHandle(  hThread  );
	 if  (  hProcess  )  CloseHandle(  hProcess  );
	 if  (  hMutexForClear  )  CloseHandle(  hMutexForClear  );
	 if  (  g_bIsWinNT  &&  bTokenAdjusted  )  {
		HANDLE tok;
		if  (  pDynLib->pOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&tok)  )  {
			LUID luid;
			TOKEN_PRIVILEGES tp;
			
			pDynLib->pLookupPrivilegeValue(NULL,SE_DEBUG_NAME,&luid);
			tp.PrivilegeCount=1;
			tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid=luid;
			pDynLib->pAdjustTokenPrivileges(tok,TRUE,&tp,NULL,NULL,NULL);
			
			CloseHandle(tok);
		}
	 }

	 traceLogA(  "myClearQwmHelp2 leaves"  );
	 return;
}


