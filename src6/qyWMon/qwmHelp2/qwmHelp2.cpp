// qwmHelp2.cpp : Defines the entry point for the DLL application.
//

#include	"stdafx.h"
#include	<stdlib.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//
#include	"qyCommon\\asrCommon.h"
#include	"qyCommon.h"
#include	"qyCommon\\asrObjs.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qnmSysCustom.h"
#include	"asrWMonPrecomp.h"
#include	"qyCommon\\asrLog.h"
#include	"qyCommon\\asrComm.h"
#include	"asrWMon.h"

#include	"qyCommon\\awmComm.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyGuiCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qwmHideProcessCommProc.h"

BOOL		gbEnd		=  FALSE;
BOOL		gbQuit		=  FALSE;

 BOOL  bRemoteProcessName_usr(  )
{
	 BOOL			bRet				=	FALSE;
	 TCHAR			finalName[512]		=	_T(  ""  );

	 if  (  getModuleDirAndFinalName(  0,  0,  finalName,  mycountof(  finalName  )  )  )  goto  errLabel;
	 if  (  _tcsicmp(  finalName,  _T(  CONST_remoteProcessName_usr  )  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 int  tmpgetProcessUsrAndDomain(  QY_ENV  *  pEnv,  DWORD  processId,  WCHAR  *  wAccountNameBuf,  unsigned  int  uiAccountNameBufSize,  WCHAR  *  wDomainNameBuf,  unsigned  int  uiDomainNameBufSize  )
{
	 int			iErr				=	-1;
	 HANDLE			hProcess			=	NULL;
	 HANDLE			hAccessToken		=	NULL;
	 WCHAR			wDomainName[200]	=	L"",  wAccountName[200]  =  L"";
	 DWORD			dwAccountSize		=	0,  dwDomainSize  =  0;
	 PTOKEN_USER	ptiUser				=	NULL;
   	 DWORD			cbti				=	0;
   	 SID_NAME_USE	snu;
	 BOOL			bTokenOpen			=	FALSE;

	 if  (  pEnv  )  {
		 traceLogA(  "pEnv needs to be null"  );  goto  errLabel;
	 }

	 hProcess  =  OpenProcess(  PROCESS_QUERY_INFORMATION,  FALSE,  processId  );
	 if  (  !hProcess  )  goto  errLabel;

	 if  (  !OpenProcessToken(  hProcess,  TOKEN_QUERY,  &hAccessToken  )  )  goto  errLabel;
	 bTokenOpen  =  TRUE;

	 if  (  GetTokenInformation(  hAccessToken,  TokenUser,  0,  0,  &cbti  )  )  {
		 traceLogA(  "Call should have failed due to zero-length buffer"  );  goto  errLabel;
	 }
	 if  (  GetLastError(  )  !=  ERROR_INSUFFICIENT_BUFFER  )  goto  errLabel;

	 if  (  !(  ptiUser  =  (  PTOKEN_USER  )malloc(  cbti  )  )  )  goto  errLabel;

	 if  (  !GetTokenInformation(  hAccessToken,  TokenUser,  ptiUser,  cbti,  &cbti  )  )  goto  errLabel;

	 dwAccountSize		=	mycountof(  wDomainName  ),  dwDomainSize  =  mycountof(  wAccountName  );
	 if  (  !LookupAccountSidW(  0,  ptiUser->User.Sid,  wAccountName,  &dwAccountSize,  wDomainName,  &dwDomainSize,  &snu  )  )  goto  errLabel;
	 
	 iErr  =  0;

errLabel:

	 if  (  ptiUser  )  free(  ptiUser  );
	 if  (  bTokenOpen  )  CloseHandle(  hAccessToken  );
	 if  (  hProcess  )  CloseHandle(  hProcess  );

	 if  (  iErr  )  traceLogA(  "getProcessSthById: can't get userName of %d(  pid  )",  processId  );
	 else  traceLogA(  "getProcessSthById: pid is %d, %S@%S",  processId,  wAccountName,  wDomainName  );

	 if  (  !iErr  )  {
		 if  (  wAccountNameBuf  )  wcsncpy(  wAccountNameBuf,  wAccountName,  uiAccountNameBufSize  );
		 if  (  wDomainNameBuf  )  wcsncpy(  wDomainNameBuf,  wDomainName,  uiDomainNameBufSize  );
	 }

	 return  iErr;

}


 DWORD  WINAPI  qwmHelp2ThreadProc(  LPVOID  p  )
{
	 HANDLE							hMutex				=	NULL;
	 HANDLE							hMutexForRemote		=	NULL;
	 HANDLE							hMutexOfQwmSvr		=	NULL;
	 TCHAR							qwmSvrPath[MAX_PATH  +  1];
	 STARTUPINFO					si;
	 PROCESS_INFORMATION			pi;
	 int							iWait;
	 HANDLE							hFile				=	NULL;
	 unsigned  char					ucbQwmSvrExists		=	FALSE;
	 TCHAR							buf[1024];
	 BOOL							bUsrEnv				=	bRemoteProcessName_usr(  );
	 WCHAR							usrName[128]		=	L"";
	 WCHAR							domainName[128]		=	L"";
	 TCHAR							logFileName[128]	=	_T(  ""  );
	 	
	 //
	 if  (  tmpgetProcessUsrAndDomain(  0,  GetCurrentProcessId(  ),  usrName,  mycountof(  usrName  ),  domainName,  mycountof(  domainName  )  )  )  goto  errLabel;
	
	 _sntprintf(  logFileName,  mycountof(  logFileName  ),  _T(  "%s.%s.log"  ),  _T(  "qwmSvr"  ),  usrName  );
	 //
	 setDebugLogFileName(  logFileName  );	//  2007/01/16

	 traceLogA(  "qwmHelp2ThreadProc enters"  );

	 GetSystemDirectory(  qwmSvrPath,  mycountof(  qwmSvrPath  )  );
	 trailDir(  qwmSvrPath,  mycountof(  qwmSvrPath  )  );
	 _sntprintf(  qwmSvrPath,  mycountof(  qwmSvrPath  ),  _T(  "%s%s"  ),  qwmSvrPath,  _T(  CONST_processName_qwmSvr  )  );
	 //  if  (  qyQuoteFileName(  qwmSvrPath,  sizeof(  qwmSvrPath  )  )  )  goto  errLabel;

	 traceLogA(  "下面建立保证单实例的mutex"  );
	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%u"  ),  _T(  CONST_mutexNameForQwmHelp2  ),  GetCurrentProcessId(  )  );
	 hMutex  =  CreateMutex(  NULL,  FALSE,  buf  );
	 if  (  !hMutex  ||  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
		 traceLogA(  "qwmHelp2ThreadProc:已有线程运行，将退出"  );  goto  errLabel;
	 }

	 
	 hFile  =  CreateFile( qwmSvrPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	 if  (  !isHandleValid(  hFile  )  )  qyDisplayLastError(  "CreateFile failed"  );
	 traceLogA(  "Locking file %s %s",  qwmSvrPath,  hFile  ==  INVALID_HANDLE_VALUE  ?  "failed"  :  "succeeded"  );


	 traceLogA(  "下面建立远程同步的mutex"  );
	 if  (  !bUsrEnv  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s"  ),  _T(  CONST_mutexNameForRemote  )  );
	 else  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%u"  ),  _T(  CONST_mutexNameForRemote  ),  GetCurrentProcessId(  )  ); 
	 //
	 hMutexForRemote = CreateMutex(  NULL,  FALSE,  buf  );
	 if  (  !hMutexForRemote  )  {
		traceLogA(  "myProcQwmHelp2( ): CreateMutex( ) failed. "  );  goto  errLabel;
	 }


	 traceLogA(  "to loop"  );
	 for  (  ;  !gbQuit;  )  {

		  traceLogA(  "to wait for mutex"  );
		  iWait  =  WaitForSingleObject(  hMutexForRemote,  7000  );
		  if  (  iWait  ==  WAIT_FAILED  )  {
		 	  traceLogA(  "myProcQwmHelp2: WaitForSingleObject failed"  );  goto  errLabel;
	 	  }
		  if  (  iWait  ==  WAIT_TIMEOUT  )  {
			  traceLogA(  "qwmHelp2ThreadProc wait timeout"  );
			  continue;
		  }

		  traceLogA(  "qwmHelp2ThreadProc: mutex waited"  );
		  ReleaseMutex(  hMutexForRemote  );

		  traceLogA(  "qwmHelp2ThreadProc: After Release MutexForRemote"  );
	 
		  if  (  bQwmUsrScriptQuit(  )  )  {		//  这里判断一下是否整个qwm需要卸载, 2007/01/15
			  traceLogA(  "需要dll退出"  );  goto  errLabel;
		  }

		  Sleep(  2500  );
		  SetLastError(  0  );
			
		  traceLogA(  "sleep & setLastError"  );

		  
		  traceLogA(  "to recover qwmSvr.exe"  );
	  
		  memset(  &pi,  0,  sizeof(  pi  )  );
		  memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
		  si.cb  =  sizeof(  STARTUPINFO  );
		  si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;

		  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s"  ),  qwmSvrPath  );
		  if  (  qyQuoteFileName(  buf,  mycountof(  buf  )  )  )  goto  errLabel;
		  if  (  !bUsrEnv  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %s%u"  ),  buf,  _T(  CONST_qwmCmdLine_recoveredByQwmHelp2  ),  GetCurrentProcessId(  )  );
		  else  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %s%u"  ),  buf,  _T(  CONST_qwmCmdLine_usrScript  ),  GetCurrentProcessId(  )  ); 
		  //
		  if  (  !CreateProcess(  NULL,  buf,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;

		  if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		  if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
#ifdef  __DEBUG__
		  traceLog(  _T(  "create process %s"  ),  buf  );
#endif

		  Sleep(  10000  );

		  traceLogA(  "升级0108"  );

	 }

errLabel:

	 if  (  isHandleValid(  hMutexForRemote  )  )  {
		 ReleaseMutex(  hMutexForRemote  );  CloseHandle(  hMutexForRemote  );
	 }
	 if  (  isHandleValid(  hFile  )  )  CloseHandle(  hFile  );
	 //
	 if  (  isHandleValid(  hMutex  )  )  CloseHandle(  hMutex  );


	 traceLogA(  "qwmHelp2ThreadProc leaves"  );

	 gbEnd  =  TRUE;

	 return  0;
}

 extern  "C"  __declspec(  dllexport  )  int _cdecl  getVer(  char  *  ver,  unsigned  long  size  )
{
	 strncpy(  ver,  CONST_qwmHelp2DllVer,  size  );
	 return  0;
}

 BOOL  bRemoteProcessName(  TCHAR  *  finalName  )
{
	 if  (  !_tcsicmp(  finalName,  _T(  CONST_remoteProcessName_sys  )  )  )  return  TRUE;
	 if  (  !_tcsicmp(  finalName,  _T(  CONST_remoteProcessName_usr  )  )  )  return  TRUE;
	 return  FALSE;
}



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	DWORD			dwThreadId;
	HANDLE			hThread				=	NULL;
	TCHAR			dirName[512]		=	_T(  ""  );
	TCHAR			finalName[512]		=	_T(  ""  );
	int				i;

	setDebugLogFileName(  _T(  "qwmHelp2.txt"  )  );
	setTraceLogToFile(  TRUE  );

	if  (  getModuleDirAndFinalName(  dirName,  mycountof(  dirName  ),  finalName,  mycountof(  finalName  )  )  )  goto  errLabel;

	traceLog(  _T(  "qwmHelp2 loaded by %s"  ),  finalName  );

	switch  (  ul_reason_for_call  )  {
			case  DLL_PROCESS_ATTACH:
				  if  (  !bRemoteProcessName(  finalName  )  )  break;

				  hThread  =  CreateThread(  NULL,  0,  qwmHelp2ThreadProc,  0,  0,  &dwThreadId  );
				  if  (  hThread  )  CloseHandle(  hThread  );	//  这里不赶紧关掉的话，会引起dll无法卸载
				  traceLogA(  "启动线程%s",  hThread  ?  "完毕"  :  "失败"  );
				  break;
			case  DLL_PROCESS_DETACH:
				  if  (  !bRemoteProcessName(  finalName  )  )  break;

				  traceLogA(  "需要卸载拉"  );
				  gbQuit  =  TRUE;
				  for  (  i  =  0;  i  <  20  &&  !gbEnd;  )  Sleep(  1000  );
				  Sleep(  100  );
				  traceLogA(  "处理线程完毕"  );
				  break;
			default:
					break;
	}

errLabel:
    return TRUE;
}

