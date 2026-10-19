

#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"asrWMon.h"
#include	"qyTCharCommProc.h"
#include	"config.h"
#include	"main.h"
#include	"qyRegToolProc.h"


/*
 //      为缩短通信会话时间，在getFile会话里不作本地校验，而是从服务器上将收到的校验值放在sessionBuf里，
 //  在其他的函数里尽可能在结束会话后再作判断
 int  qwmCmdGetFile(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QWM_SESSION_BUF  *  pSessionBuf,  QY_SOCK  *  pSock  )
{
	 int							iErr		=		-1;
	 QY_COMM_SESSION		*		pComm		=		&pSession->comm;
	 char							buf[4096];
	 QY_COMM_BUFSIZE				bufSize;
	 QY_COMM_RESP					resp;
	 char							tmpPath[MAX_PATH  +  1];
	 char							tmpFileName[MAX_PATH  +  1];
	 HANDLE							hFile		=		NULL;
	 DWORD							dwWritten;

	 traceLogA(  "qwmCmdGetFile enters"  );

	 if  (  !GetTempPath(  sizeof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
	 if  (  !GetTempFileName(  tmpPath,  "wrd",  0,  tmpFileName  )  )  goto  errLabel;
	 hFile  =  CreateFile(  tmpFileName,  GENERIC_WRITE,  0,  NULL,  CREATE_ALWAYS,  FILE_ATTRIBUTE_NORMAL,  NULL  );
	 if  (  !isHandleValid(  hFile  )  )  goto  errLabel;
	 traceLogA(  "qwmCmdGetFile将使用%s为临时文件",  tmpFileName  );
	 
	 memset(  &bufSize,  0,  sizeof(  bufSize  )  );
	 bufSize.len  =  qyhtonl(  sizeof(  buf  )  );
	 for  (  ;  ;  )  {
		  if  (  qySendReq(  pComm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_getFile,  (  char  *  )&bufSize,  sizeof(  bufSize  )  )  )  goto  errLabel;
		  if  (  qyRecvResp(  pComm,  pSock,  &pQwm->cfg.to,  &resp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		  if  (  !isRcOk(  resp.head.usCode  )  )  goto  errLabel;
		  if  (  !resp.head.len  )  break;		//  文件接收完毕		  
		  if  (  !WriteFile(  hFile,  buf,  resp.head.len,  &dwWritten,  0  )  )  goto  errLabel;
	 }

	 CloseHandle(  hFile  );  hFile  =  NULL;
	 
	 traceLogA(  "qwmCmdGetFile will get 重复信息"  );

	 if  (  qySendReq(  pComm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_getDigest,  (  char  *  )&bufSize,  sizeof(  bufSize  )  )  )  goto  errLabel;
	 if  (  qyRecvResp(  pComm,  pSock,  &pQwm->cfg.to,  &resp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 if  (  !isRcOk(  resp.head.usCode  )  )  goto  errLabel;

	 traceLogA(  "qwmCmdGetFile will 校验信息"  );

	 pSessionBuf->u.getFile.digestLen  =  resp.head.len;
	 if  (  pSessionBuf->u.getFile.digestLen  >  sizeof(  pSessionBuf->u.getFile.digest  )  )  goto  errLabel;
	 memcpy(  pSessionBuf->u.getFile.digest,  buf,  pSessionBuf->u.getFile.digestLen  );
	 if  (  safeStrCpy(  tmpFileName,  pSessionBuf->u.getFile.fileName,  sizeof(  pSessionBuf->u.getFile.fileName  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  hFile  )  )  CloseHandle(  hFile  );

	 traceLogA(  "qwmCmdGetFile leaves. iErr is %s",  qyGetDesByType1(  CONST_qyRetTable,  iErr  )  );

	 return  iErr;
}
 

 int  qwmCmdUpdate(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QWM_SESSION_BUF  *  pSessionBuf,  QY_SOCK  *  pSock  )
{
	 int							iErr		=		-1;
	 QY_COMM_SESSION		*		pComm		=		&pSession->comm;
	 QY_COMM_RESP					tmpResp;
	 char							buf[4096];
	 QY_COMM_BUFSIZE				bufSize;
	 QY_COMM_RESP					resp;
	 char							tmpPath[MAX_PATH  +  1];
	 char							tmpFileName[MAX_PATH  +  1];
	 HANDLE							hFile		=		NULL;
	 DWORD							dwWritten;
	 char							tmpDigest[CONST_qyMd5Len  +  1];
	 unsigned  int					digestLen,  len;
	 STARTUPINFO					si;
	 PROCESS_INFORMATION			pi;

	 traceLogA(  "qwmCmdUpdate enters"  );
	 
	 if  (  qySendReq(  pComm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_update,  NULL,  0  )  )  goto  errLabel;
	 if  (  qyRecvResp(  pComm,  pSock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;

	 if  (  !GetTempPath(  sizeof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
	 if  (  !GetTempFileName(  tmpPath,  "wrd",  0,  tmpFileName  )  )  goto  errLabel;
	 hFile  =  CreateFile(  tmpFileName,  GENERIC_WRITE,  0,  NULL,  CREATE_ALWAYS,  FILE_ATTRIBUTE_NORMAL,  NULL  );
	 if  (  !isHandleValid(  hFile  )  )  goto  errLabel;
	 
	 memset(  &bufSize,  0,  sizeof(  bufSize  )  );
	 bufSize.len  =  qyhtonl(  sizeof(  buf  )  );
	 for  (  ;  ;  )  {
		  if  (  qySendReq(  pComm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_getFile,  (  char  *  )&bufSize,  sizeof(  bufSize  )  )  )  goto  errLabel;
		  if  (  qyRecvResp(  pComm,  pSock,  &pQwm->cfg.to,  &resp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		  if  (  !isRcOk(  resp.head.usCode  )  )  goto  errLabel;
		  if  (  !resp.head.len  )  break;		//  文件接收完毕		  
		  if  (  !WriteFile(  hFile,  buf,  resp.head.len,  &dwWritten,  0  )  )  goto  errLabel;
	 }

	 CloseHandle(  hFile  );  hFile  =  NULL;
	 if  (  qySendReq(  pComm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_getDigest,  (  char  *  )&bufSize,  sizeof(  bufSize  )  )  )  goto  errLabel;
	 if  (  qyRecvResp(  pComm,  pSock,  &pQwm->cfg.to,  &resp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 if  (  !isRcOk(  resp.head.usCode  )  )  goto  errLabel;
	 digestLen  =  resp.head.len;

	 if  (  qySendReq(  pComm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_end,  0,  0  )  )  goto  errLabel;
	 qyRecvResp(  pComm,  pSock,  &pQwm->cfg.to,  &resp,  0,  0  );
	 
	 len  =  sizeof(  tmpDigest  );
	 if  (  !bQwmGetFileMd5(  tmpFileName,  tmpDigest,  &len  )  )  goto  errLabel;
	 if  (  len  !=  digestLen  ||  memcmp(  tmpDigest,  buf,  len  )  )  goto  errLabel;
	 traceLogA(  "This is a right update file."  );

	 traceLogA(  "Now run the update file."  ); 

	 memset(  &pi,  0,  sizeof(  pi  )  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	 si.cb  =  sizeof(  STARTUPINFO  );
	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
			
	 if  (  qyQuoteFileName(  tmpFileName,  sizeof(  tmpFileName  )  )  )  goto  errLabel;
	 if  (  !CreateProcess(  NULL,  tmpFileName,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
	 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
	 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 				
	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  pi.hThread  )  )  CloseHandle(  pi.hThread  );
	 if  (  isHandleValid(  pi.hProcess  )  )  CloseHandle(  pi.hProcess  );	 
	 if  (  isHandleValid(  hFile  )  )  CloseHandle(  hFile  );

	 traceLogA(  "qwmCmdUpdate leaves"  );

	 
	 return  iErr;

}
*/


 //  2005/05/01
 extern  "C"  int  qwmCmdBySubProcess(  void  *  p0,  LPCTSTR  cmdStr,  LPCTSTR  cmdParam,  HANDLE  *  phProcess  )
{
	 int							iErr		=		-1;
	 TCHAR							buf[1024];
	 STARTUPINFO					si;
	 PROCESS_INFORMATION			pi;
	 TCHAR							tmpFileName[MAX_PATH  +  1];

	 if  (  !cmdStr  )  return  -1;

	 memset(  &pi,  0,  sizeof(  pi  )  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	 si.cb  =  sizeof(  STARTUPINFO  );
	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;

	 GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
	 if  (  qyQuoteFileName(  tmpFileName,  mycountof(  tmpFileName  )  )  )  goto  errLabel;

	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %s"  ),  tmpFileName,  cmdStr  );
	 if  (  cmdParam  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%s"  ),  buf,  cmdParam  );
	 if  (  !CreateProcess(  NULL,  buf,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
	 if  (  iErr  )  {
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }

	 if  (  !iErr  )  {
		 if  (  phProcess  )  *phProcess  =  pi.hProcess;
		 else  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }	//  2005/10/08，增加这一句，以方便在不需要传出句柄时，将句柄清除
	 }


	 traceLogA(  "qwmCmdBySubProcess, pid is %d",  pi.dwProcessId  );  

	 return  iErr;
}







/*
 int  initWMState(  AWM_CONTROL_CLIENT_INFO  *  pACCI  )
{
	pACCI->bFileDel  =  FALSE;
	pACCI->bModified  =  FALSE;
	pACCI->bNODel  =  FALSE;
	pACCI->bRunDel  =  FALSE;
	wsprintf(  pACCI->lastWriteTime,  "%s",  "00000000000000"  );

	return 0;
}

 void  checkAsrWMonNO(  AWM_CONTROL_CLIENT_INFO  *  pACCI  )
{	
	HKEY hKey = NULL;
	char buf[128];
	DWORD type;
	long cb;

	if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  ROOT_KEY_AWM,  &hKey  )  !=  ERROR_SUCCESS  )  {
		pACCI->bNODel  =  TRUE;	
		goto  errLabel;
	}

	cb  =  sizeof(  buf  );
	memset(  buf,  0,  sizeof(  buf  )  );
	if  (  RegQueryValueEx(  hKey,  AWM_MODIFIED_TIME_KEY,  0,  &type,  (  unsigned  char  *  )buf,  (  unsigned  long  *  )&cb  )  !=  ERROR_SUCCESS  )  {
		pACCI->bModified  =  TRUE;
		goto  errLabel;
	}
	
	wsprintf(  pACCI->lastWriteTime,  "%s",  buf  );

errLabel:
	
	if  (  hKey  )  RegCloseKey(  hKey  );

	return;
}


 void awmGetFileAttribute( char svTargetName[MAX_PATH], AWM_CONTROL_CLIENT_INFO *pACCI )
{
	WIN32_FIND_DATA fd;
	FILETIME ft;
	SYSTEMTIME st;
	char modifiedTime[15];
	HANDLE hFind = NULL;
	HKEY hKey = NULL;

	hFind = FindFirstFile( svTargetName, &fd );
	if( hFind == INVALID_HANDLE_VALUE ) goto errLabel;

	if( !FileTimeToLocalFileTime( &fd.ftLastWriteTime, &ft ) ) goto errLabel;
	if( !FileTimeToSystemTime( &ft, &st ) ) goto errLabel;
	memset( modifiedTime, 0, sizeof( modifiedTime ) );
	wsprintf( modifiedTime, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );
	if( lstrcmp( modifiedTime, pACCI->lastWriteTime ) )
		pACCI->bModified = TRUE;

errLabel:
	FindClose( hFind );
	return;
}

 BOOL  bSaveFileAttribute(  char  *  svTargetName  )
{
	BOOL				bRet				=	FALSE;
	WIN32_FIND_DATA		fd;
	FILETIME			ft;
	SYSTEMTIME			st;
	char				modifiedTime[15];
	HANDLE				hFind				=	NULL;
	HKEY				hKey				=	NULL;

	hFind  =  FindFirstFile(  svTargetName,  &fd  );
	if  (  !FileTimeToLocalFileTime(  &fd.ftLastWriteTime,  &ft  )  )  goto  errLabel;
	if  (  !FileTimeToSystemTime(  &ft,  &st  )  )  goto  errLabel;
	wsprintf( modifiedTime, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );

	if  (  RegCreateKeyEx( HKEY_LOCAL_MACHINE, ROOT_KEY_AWM, 0, "", 0, KEY_ALL_ACCESS, NULL, &hKey, NULL ) != ERROR_SUCCESS  )  {
		goto  errLabel;
	}
	
	if  (  RegSetValueEx( hKey, AWM_MODIFIED_TIME_KEY, 0, REG_SZ, ( const unsigned char *)modifiedTime, lstrlen( modifiedTime) ) != ERROR_SUCCESS  )  {
		goto  errLabel;
	}
	bRet  =  TRUE;

errLabel:

	if  (  hKey  )  RegCloseKey(  hKey  );

	traceLogA(  "bSaveFileAttribute  %s",  bRet  ?  "succeeded."  :  "failed."  );

	return  bRet;

}

 
 BOOL checkAsrWMonInvalid( AWM_CONTROL_CLIENT_INFO *pACCI )
{
	BOOL bRet = FALSE;

	if( pACCI->bFileDel || pACCI->bModified || pACCI->bNODel || pACCI->bRunDel )
		bRet = TRUE;

	return bRet;
}

*/ 









 

extern   QY_DMITEM	CONST_qwmSvrSecChkTaskTable[];


 BOOL  bServiceSupportRd(  int  iPlatformId  )
{
	 switch  (  iPlatformId  )  {
			 case  CONST_qyPlatform_win2k:
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
				   return  TRUE;
			 default:
					break;
	 }
	 return  FALSE;
}

//  下面线程处理函数专门用于执行管理策略
 DWORD  WINAPI  qwmThreadProcCmd(  LPVOID  lpParameter  )
{
	 QWM_THREADINFO			threadInfo;
	 QY_W_MON			*	pQwm				=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG			threadCfg;
	 QY_REG					reg;
	 int					loopCtrl;
	 HANDLE					hSecChkProcess		=	NULL;
	 TCHAR					buf[256];
	 TCHAR					chdRespOkStr[16]	=	_T(  "yngboa"  );
	 HANDLE					hRdProcess			=	NULL;
	 DWORD					dwRet;
	 DWORD					dwActiveSessId		=	-1;
	 DWORD					dwCurSessId			=	-1;
	 HRESULT				hr					=	S_OK;
	 	 

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;
	 lstrcpy(  reg.rootKey,  _T(  ROOT_KEY_AWM  )  );  
	 reg.pEncCtx  =  &pQwm->encCtx;

	 //  2011/08/20
	 hr  =  CoInitialize(  0  );

	 //
	 initRasConn(  &gRasConn  );
	 
	 for  (  loopCtrl  =  0;  !pQwm->bQuit;  loopCtrl  ++  )  {
		  
		  traceLogA(  "qwmCmdThreadProc loops."  );
		  threadInfo.pCfg->nInterval  =  pQwm->cfg.nInterval_qwmThreadProcCmd;
		  memcpy(  &threadInfo.pCfg->rasRule,  &pQwm->cfg.pcRules.ras,  sizeof(  QNM_RAS_RULE  )  );
		  threadInfo.dwLoopCtrl  =  loopCtrl;

		  if  (  pQwm->cfg.ucbNetMc2  )  {
			  
		  	  detectRasConn(  &threadInfo  );
		  	  detectProxyServer(  &threadInfo  );
			  if  (  !pQwm->cfg.ucbPcNetworkPropWillChange  )  {	//  2005/06/11, 当网络配置修改时，不要做下面的报警
				  if  (  !pQwm->cfg.pcRules.ras.ucbNotChkOnInternet  )  detectInvalidInternet(  &threadInfo  );
		  		  if  (  pQwm->cfg.pcRules.ras.ucWarnToInternetCmd  ==  CONST_devCmd_permitted  )  detectAndWarnToInterMon(  &threadInfo  );			//  2004/10/25, 上网报警
			  }
			  procDevRule(  &threadInfo  );							//  2005/01/05
			  procOsRule(  &threadInfo  );							//  2005/06/25

			  //  2004/10/24,  处理检测结果
		  	  procDetectionResult(  &threadInfo  );
		  
			  //  2006/02/12, 处理远程桌面
			  //  2007/02/04, 先取活跃sessionId和当前sessionId
			  getWtsSessionId(  &pQwm->env,  &dwCurSessId,  &dwActiveSessId  );
			  //
			  if  (  !hRdProcess  )  {
				  if  (  dwCurSessId  ==  dwActiveSessId  &&   bServiceSupportRd(  pQwm->env.iPlatformId  )  )  {
				  	  if  (  pQwm->cfg.getOpCmd.ucbViewRemoteDesktop  )  {	//  启动远程桌面				  
						  qwmCmdBySubProcess(  0,  _T(  CONST_qwmCmdLine_viewRemoteDesktop  ),  0,  &hRdProcess  );
							}
					  //  else  if  (  pQwm->cfg.getOpCmd.ucbMonDesktop  )  {		//  2006/03/06, 处理实时屏幕监控
			  		  //			qwmCmdBySubProcess(  0,  CONST_qwmCmdLine_monDesktop,  0,  &hRdProcess  );
					  //  }
				  }
			  }

			  if  (  hRdProcess  )  {		//  取消远程桌面
				  if  (  dwCurSessId  !=  dwActiveSessId  ||  (  !pQwm->cfg.getOpCmd.ucbViewRemoteDesktop  )  )  {		//  
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

		  //  if  (  pQwm->cfg.ucbSecChk  )  //  由于在内网管理中也需要检查上网网址等工作，故在这里就不能用这个开关量了，2006/03/07
		  {					//  2005/05/02
			  if  (  hSecChkProcess  )  {
				  
				  dwRet = ::WaitForSingleObject(  hSecChkProcess,  200  );
				  if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
					  CloseHandle(  hSecChkProcess  );  hSecChkProcess  =  NULL;
					  //
					  if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdRespOk  ),  (  char  *  )buf,  sizeof(  buf  )  )  ||  lstrcmpi(  buf,  chdRespOkStr  )  )  {
						  traceLogA(  "表明子进程没有正常退出"  );
						}
					  else  {
						    traceLogA(  "这里表明这个子进程的任务完成了，并且没有意外"  );
						    showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_secChkFinished,  0  );
					  }
					  //  
					  pQwm->cfg.pcRules.secChk.ucbDoSecChk  =  FALSE;  	 //  工作完成后须将安检指令复位
						}
				  else  if  (  dwRet  ==  WAIT_TIMEOUT  )  {				//  这里表明子进程仍然在活跃中
							if  (  !pQwm->cfg.pcRules.secChk.ucbDoSecChk  )  {	//  表明系统管理员希望终止安检
								TCHAR	buf[128];
								if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdShallQuit  ),  (  char  *  )buf,  sizeof(  buf  )  )  ||  lstrcmpi(  buf,  _T(  CONST_qwmCfgVal_chdShallQuit  )  )  )  {
									showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_chdShallQuit,  0  );
									qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdShallQuit  ),  _T(  CONST_qwmCfgVal_chdShallQuit  )  );
								}
							}
				  }
			  }
			  if  (  pQwm->cfg.pcRules.secChk.ucbDoSecChk  &&  !hSecChkProcess  )  {
				  showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_doSecChk,  0  );

				  //  doSecChk(  &threadInfo,  CONST_qwmSvrSecChkTaskTable  );
				  qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdRespOk  )  );
				  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%s"  ),  _T(  CONST_qwmCmdLine_chdRespOk  ),  chdRespOkStr  );
				  qwmCmdBySubProcess(  0,  pQwm->cfg.ucbSecChk  ?  _T(  CONST_qwmCmdLine_doSecChk  )  :  _T(  CONST_qwmCmdLine_monIe  ),  buf,  &hSecChkProcess  );
				  
			  }
		  }
		  
		  Sleep(  threadInfo.pCfg->nInterval  );
		  
	 }


//  errLabel:

	 traceLogA(  "qwmThreadProcCmd 将退出运行"  );

	 if  (  isHandleValid(  hSecChkProcess  )  )  {		//  2005/05/02
		 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_terminateChd,  0  );
		 traceLogA(  "安检子进程尚未退出，强制终止其运行"  );
		 TerminateProcess(  hSecChkProcess,  1  );
		 CloseHandle(  hSecChkProcess  );  hSecChkProcess  =  NULL;  
	 }
	 if  (  isHandleValid(  hRdProcess  )  )  {	//  2006/02/12
		 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_terminateChd,  0  );
		 traceLogA(  "远程桌面子进程尚未退出，强制终止其运行"  );
		 TerminateProcess(  hRdProcess,  1  );
		 CloseHandle(  hRdProcess  );  hRdProcess  =  NULL;  
	 }

	 //  2011/08/20
	 CoUninitialize(  );

	 traceLogA(  "qwmThreadProcCmd 将退出完毕"  );

	 return  0;

}










 int  getRasPhoneNum(  void  *  pDynLibParam,  LPCTSTR  szEntryName,  RAS_CONN_INFO  *  pRasConnInfo  )
{
	int					iErr		=		-1;
	DWORD				dwRet		=		0;
	RASENTRY		*	lpRasEntry	=		NULL;
	char			*	errbuf		=		NULL;
	unsigned  long		lEntrySize	=		0;						//  sizeof( RASENTRY );
	QWM_DYN_LIB		*	pDynLib		=		(  QWM_DYN_LIB  *  )pDynLibParam;
	
	lpRasEntry  =  (  RASENTRY  *  )malloc(  sizeof(  RASENTRY  )  );
	if  (  !lpRasEntry  )  goto  errLabel;

	memset( lpRasEntry, 0, sizeof( RASENTRY ) );
	lpRasEntry->dwSize = sizeof( RASENTRY );
	lpRasEntry->dwfOptions = RASEO_UseCountryAndAreaCodes;
	dwRet = pDynLib->pRasGetEntryProperties( NULL, szEntryName, NULL, &lEntrySize, NULL, NULL );
	if  (  dwRet  ==  ERROR_BUFFER_TOO_SMALL  )  {
        free( lpRasEntry );
		lpRasEntry = ( RASENTRY * )malloc( lEntrySize );
		if  (  !lpRasEntry  )  goto  errLabel;
		memset( lpRasEntry, 0, lEntrySize );
		lpRasEntry->dwSize = sizeof( RASENTRY );
		lpRasEntry->dwfOptions = RASEO_UseCountryAndAreaCodes;
		dwRet = pDynLib->pRasGetEntryProperties( NULL, szEntryName, lpRasEntry, &lEntrySize, NULL, NULL );
	}
	if  (  dwRet  )	 goto errLabel;
		
	//  wsprintf( sPhoneNum, "%3d%4s%13s", lpRasEntry->dwCountryCode, lpRasEntry->szAreaCode, lpRasEntry->szLocalPhoneNumber );
	pRasConnInfo->dwCountryCode  =  lpRasEntry->dwCountryCode;
	safeTcsnCpy(  lpRasEntry->szAreaCode,  pRasConnInfo->szAreaCode,  mycountof(  pRasConnInfo->szAreaCode  )  );
	tTrim(  pRasConnInfo->szAreaCode  );	
	safeTcsnCpy(  lpRasEntry->szLocalPhoneNumber,  pRasConnInfo->szLocalPhoneNumber,  mycountof(  pRasConnInfo->szLocalPhoneNumber  )  );
	tTrim(  pRasConnInfo->szLocalPhoneNumber  );

	iErr  =  0;

errLabel:

	if  (  lpRasEntry  )  free(  lpRasEntry  );		//  2004/10/30增加了对lpRasEntry的非空判断
	return  iErr;
}


#if  0
 int  saveLogToReg(  unsigned  char  *  telcode  )
{
	int iRet = -1;
	char timebuf[14 + 1];
	char decodeBuf[128];
	char buf1[128];
	char buf2[128];
	int rcdNum, curPos;
	BOOL bKeyOpen = FALSE;
	HKEY hKey;
	DWORD cb1, cb2, type1, type2;

	if  (  RegOpenKey( HKEY_LOCAL_MACHINE, _T(  ROOT_KEY_AWM  ), &hKey ) != ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen = TRUE;

	cb1 = sizeof( buf1 );
	cb2 = sizeof( buf2 );
	memset( buf1, 0, sizeof( buf1 ) );
	memset( buf2, 0, sizeof( buf2 ) );
	if( RegQueryValueEx( hKey, _T(  AWM_SINGLE_CUR_POS_KEY  ), 0, &type2, ( unsigned char * )&buf2, ( unsigned long * )&cb2 ) != ERROR_SUCCESS ||
		RegQueryValueEx( hKey, _T(  AWM_SINGLE_RCD_NUM_KEY  ), 0, &type1, ( unsigned char * )&buf1, ( unsigned long * )&cb1 ) != ERROR_SUCCESS 
	  )
	{
		rcdNum = 0;
		curPos = 0;
	}
	else{
		rcdNum = atol( buf1 );
		curPos = atol( buf2 );
		if( rcdNum < 0 || rcdNum > 5 || curPos < 0 || curPos > 5 ) {
			rcdNum = 0;
			curPos = 0;
		}
	}

	if( rcdNum < 5 ) {
		rcdNum ++;
		curPos ++;		
	}
	else{
		if( curPos == 5 )
			curPos = 1;
		else
			curPos ++;
	}
	
	memset( timebuf, 0, sizeof( timebuf ) );
	getCurTime( timebuf );
	wsprintf( buf1, "l%d", curPos );
	wsprintf( buf2, "$%s$%s$", telcode, timebuf );	
	Encrypt( buf2, lstrlen( buf2 ), decodeBuf );
	decodeBuf[lstrlen( buf2 )] = 0;
		
	if ( RegSetValueEx( hKey, buf1, 0, REG_SZ, ( const unsigned char * )decodeBuf, lstrlen( decodeBuf ) ) != ERROR_SUCCESS )
		goto errLabel;

	wsprintf( buf1, "%d", rcdNum );
	wsprintf( buf2, "%d", curPos );
	if( RegSetValueEx( hKey, AWM_SINGLE_RCD_NUM_KEY, 0, REG_SZ, ( const unsigned char * )buf1, lstrlen( buf1 ) ) != ERROR_SUCCESS )
		goto errLabel;
	if( RegSetValueEx( hKey, AWM_SINGLE_CUR_POS_KEY, 0, REG_SZ, ( const unsigned char * )buf2, lstrlen( buf2 ) ) != ERROR_SUCCESS )
		goto errLabel;

	iRet = 0;

errLabel:

	if( bKeyOpen ) RegCloseKey( hKey );

	return iRet;

}
#endif

 int  detectRasConn(  QWM_THREADINFO  *  pThreadInfo  )
{
	int						iErr			=	-1;
	QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
    LPRASCONN				lpRasConn		=	NULL;
    DWORD					cbBuf			=	0;
    DWORD					cConn			=	0;
    DWORD					dwRet			=	0;
	int						i,  j;
    TCHAR					szMessage[256];
	BOOL					bOffline		=	FALSE;
	QWM_DYN_LIB			*	pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	
	//  setTraceLogOpen(  TRUE  );
	traceLogA(  "detectRasConn( ) enters"  );

	//  2005/01/07加入了对detectRasConn的处理间隔的判断
	if  (  GetTickCount(  )  -  pQwm->dwDetectRasLastTickCnt  <  CONST_minDetectRasInterval  )  {
		 //  traceLogA(  "detectRas时间未到"  );
		 iErr  =  0;  goto  errLabel;	
	}
	pQwm->dwDetectRasLastTickCnt  =  GetTickCount(  );

	if  (  !pDynLib->ghDll_RasApi32  )  {
		
		TCHAR	svLibName[MAX_PATH  +  1];
		BOOL	bRasManExists  =  FALSE;
			
		if  (  g_bIsWinNT  )  {
			TCHAR  buf[256];
		
			if  (  !qyGetRegCfg(  _T(  "System\\CurrentControlSet\\Services\\RasMan"  ),  _T(  "ObjectName"  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
				bRasManExists  =  TRUE;
			}

			traceLogA(  "bRasManExists is %s",  bRasManExists  ?  "true"  :  "false"  );
		}

		if  (  !g_bIsWinNT  ||  bRasManExists  )  {
		
			//  pDynLib->ghDll_RasApi32 = LoadLibrary( "rasapi32.dll" );
			if  (  qyFullLibName(  _T(  "rasapi32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
			traceLogA(  "Before load %s",  svLibName  );
			pDynLib->ghDll_RasApi32  =  LoadLibrary(  svLibName  );
			traceLogA(  "after load %s",  svLibName  );
			if  (  pDynLib->ghDll_RasApi32  )  {
				pDynLib->pRasEnumConnections = ( RASENUMCONNECTIONS )GetProcAddress( pDynLib->ghDll_RasApi32, "RasEnumConnectionsW" );
				pDynLib->pRasHangUp = ( RASHANGUP )GetProcAddress( pDynLib->ghDll_RasApi32, "RasHangUpW" );
				pDynLib->pRasGetErrorString = ( RASGETERRORSTRING )GetProcAddress( pDynLib->ghDll_RasApi32, "RasGetErrorStringW" );
				pDynLib->pRasGetConnectStatus = ( RASGETCONNECTSTATUS )GetProcAddress( pDynLib->ghDll_RasApi32, "RasGetConnectStatusW" );
				pDynLib->pRasGetEntryProperties = ( RASGETENTRYPROPERTIES )GetProcAddress( pDynLib->ghDll_RasApi32, "RasGetEntryPropertiesW" );
				// pDynLib->pRasGetEntryDialParams = ( RASGETENTRYDIALPARAMS )GetProcAddress( pDynLib->ghDll_RasApi32, "RasGetEntryDialParamsA" );
			}
		}

		traceLogA(  "detectRasConn: %s",  pDynLib->ghDll_RasApi32  ?  "rasapi32 loaded successfully."  :  "rasapi32 not loaded."  );
	
		if  (  !pDynLib->ghDll_RasApi32  )  goto  errLabel;	
		
	}
	
	// enumerate connections
    cbBuf  =  sizeof(  RASCONN  );
    if  (  (  lpRasConn  =  (  LPRASCONN  )malloc(  (  UINT  )cbBuf  )  )  ==  NULL  )  goto  errLabel;
	lpRasConn->dwSize  =  sizeof(  RASCONN  );                      
    dwRet  =  pDynLib->pRasEnumConnections(  lpRasConn,  &cbBuf,  &cConn  );		
    if  (  dwRet  ==  ERROR_BUFFER_TOO_SMALL  )  {
		free(  lpRasConn  );  lpRasConn  =  NULL;
        if  (  (  lpRasConn  =  (  LPRASCONN  )malloc(  (  UINT  )cbBuf  )  )  ==  NULL  )  goto  errLabel;
		lpRasConn->dwSize  =  sizeof(  RASCONN  );
		dwRet  =  pDynLib->pRasEnumConnections(  lpRasConn,  &cbBuf,  &cConn  );		
	}
	if  (  dwRet  )  {
		if  (  pDynLib->pRasGetErrorString(  (  UINT  )dwRet,  szMessage,  mycountof(  szMessage  )  )  !=  0  )  {
			traceLogA(  "RasGetErrorString failed."  );
		}
		goto  errLabel;	
	}
    	
	traceLogA(  "begin detect..."  );

	for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
		if  (  gRasConn.rCI[i].bRasOn  )  {
			for  (  j  =  0;  j  <  (  int  )cConn;  j  ++  )  {
				 if  (  !lstrcmpi(  gRasConn.rCI[i].szEntryName,  lpRasConn[j].szEntryName  )  )  break;
			}
			if  (  j  ==  (  int  )cConn  )  {
				//  生成一条日志,  表拨号挂断
				qwmLogRasEvent(  pThreadInfo,  CONST_qyEventType_nm_rasEnd,  &gRasConn.rCI[i]  );
				gRasConn.rCI[i].bRasOn  =  FALSE;
			}
		}
	}

	if  (  !cConn  )  {							//  如果没有连接，则直接退出
		iErr  =  0;  goto  errLabel;
	}

	//  将连接加入gRasConn进行管理
	for  (  j  =  0;  j  <  (  int  )cConn;  j  ++  )  {
		 for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
			  if  (  !gRasConn.rCI[i].bRasOn  )  continue;
			  if  (  !lstrcmpi(  gRasConn.rCI[i].szEntryName,  lpRasConn[j].szEntryName  )  )  break;
		 }
		 if  (  i  <  CONST_maxRasConns  )  {	//  原来已有的连接
			 gRasConn.rCI[i].hRasConn  =  lpRasConn[j].hrasconn;
			 continue;
		 }
		 //  下面为新增加的连接，需要加入gRasConn中
		 for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
			  if  (  !gRasConn.rCI[i].bRasOn  )  break;
		 }
		 if  (  i  ==  CONST_maxRasConns  )  {
			 traceLogA(  "连接太多了，没有空间存放该连接。"  );
			 break;
		 }
		
		 memset(  &gRasConn.rCI[i],  0,  sizeof(  gRasConn.rCI[i]  )  );
		 lstrcpyn(  gRasConn.rCI[i].szEntryName,  lpRasConn[j].szEntryName,  mycountof(  gRasConn.rCI[i].szEntryName  )  );
		 //  if  (  getRasPhoneNum(  (  const  char  *  )gRasConn.rCI[i].szEntryName,  &gRasConn.rCI[i]  )  )  break;
		 getRasPhoneNum(  pDynLib,  gRasConn.rCI[i].szEntryName,  &gRasConn.rCI[i]  );	//  鉴于有时此函数会因为内存意外等情况失效，为确保禁止策略执行，去掉上面的break;  2003/08/22
		 gRasConn.rCI[i].ucRasCmd  =  CONST_rasCmd_permitted;		//  缺省为允许
		 gRasConn.rCI[i].hRasConn  =  lpRasConn[j].hrasconn;
		 gRasConn.rCI[i].bRasOn  =  TRUE;			 
		 
	}

	//  允许权限在这里处理
	if  (  pThreadInfo->pCfg->rasRule.ucRasCmd  ==  CONST_rasCmd_permitted  )  {
		for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
			 if  (  !gRasConn.rCI[i].bRasOn  )  continue;
			 if  (  !gRasConn.rCI[i].bLogged  )  {
				 //  生成一条日志,  表拨号开始
				 qwmLogRasEvent(  pThreadInfo,  CONST_qyEventType_nm_rasStart,  &gRasConn.rCI[i]  );
				 gRasConn.rCI[i].bLogged  =  TRUE;
			 }
		}
		iErr  =  0;  goto  errLabel;
	}

	//  检查是否离线
	bOffline  =  TRUE;
	
	QY_SOCK		tmpSock;
	clearQySock(  &tmpSock  );
	if  (  !qyConnect(  pQwm->server.ip,  pQwm->server.port,  &tmpSock,  pQwm->cfg.to.iConnect  )  )  {
		bOffline  =  FALSE;
		qyDisconnect(  &tmpSock  );
	}

	//  为Debug的需要，可以打开下面的语句，使模拟离线的情况。
	//  bOffline  =  TRUE;

	//  生成离线日志
	if  (  pThreadInfo->pCfg->rasRule.ucRasCmd  ==  CONST_rasCmd_offlinePermitted  
		&&   bOffline  )  
	{
		for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
			 if  (  !gRasConn.rCI[i].bRasOn  )  continue;
			 if  (  gRasConn.rCI[i].bLogged  )  continue;
			 gRasConn.rCI[i].ucRasCmd  =  CONST_rasCmd_offlinePermitted;
			 qwmLogRasEvent(  pThreadInfo,  CONST_qyEventType_nm_rasStart,  &gRasConn.rCI[i]  );
			 gRasConn.rCI[i].bLogged  =  TRUE;
		}
		iErr  =  0;  goto  errLabel;
	}
	
	//  除特许号码外全部禁止，在下面处理
	for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
		 if  (  !gRasConn.rCI[i].bRasOn  )  continue;
		 for  (  j  =  0;  j  <  CONST_maxPermittedPhoneNums;  j  ++  )  {
			  if  (  !pThreadInfo->pCfg->rasRule.permittedPhoneNums[j][0]  )  continue;
			  if  (  !mystricmp(  pThreadInfo->pCfg->rasRule.permittedPhoneNums[j],  gRasConn.rCI[i].szLocalPhoneNumber  )  )  break;
		 }
		 if  (  j  <  CONST_maxPermittedPhoneNums  )  {		//  指定号码允许
			 if  (  !gRasConn.rCI[i].bLogged  )  {
				 //  生成一条日志, 表拨号开始
				 gRasConn.rCI[i].ucRasCmd  =  CONST_rasCmd_zdhmyx;
				 qwmLogRasEvent(  pThreadInfo,  CONST_qyEventType_nm_rasStart,  &gRasConn.rCI[i]  );
				 gRasConn.rCI[i].bLogged  =  TRUE;
			 }
			 continue;
		 }

		 gRasConn.rCI[i].ucRasCmd  =  CONST_rasCmd_prohibited;
		 //  禁止该连接
		 RASCONNSTATUS  rasStatus; 
		 int			iRet;
           
		 rasStatus.dwSize = sizeof( RASCONNSTATUS );
		 dwRet = pDynLib->pRasGetConnectStatus(  gRasConn.rCI[i].hRasConn,  &rasStatus  );
		 if  (  !dwRet  &&  !rasStatus.dwError  &&  rasStatus.rasconnstate  ==  RASCS_Connected  )  {
			 iRet  =  pDynLib->pRasHangUp(  gRasConn.rCI[i].hRasConn  );
			 if  (  !iRet  )  {
				 //  生成一条日志, 表拨号禁止
				 qwmLogRasEvent(  pThreadInfo,  CONST_qyEventType_nm_rasProhibited,  &gRasConn.rCI[i]  );
				 gRasConn.rCI[i].bRasOn  =  FALSE;
			 }
		 }			
	}


	iErr  =  0;
    

errLabel:

	if  (  lpRasConn  )  free(  lpRasConn  );

	traceLogA(  "leave detectRasConn( )"  );
	//  setTraceLogOpen(  FALSE  );

    return  0;

}


 //  2005/05/23, 由于超时时间调长了，为了使检测非法外联不过于占时间，做了下面的函数
 int setSockShortTimeout( SOCK_TIMEOUT *p )
{
	 setSockTimeout(  p  );
	 p->iRead		=  3000;
	 p->iSelect		=  3000;
	 return		0;
}


 //  注：这里的网站似乎应该从服务器上下载最好。
 int  detectInvalidInternet(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 return  0;		//  2007/02/28, 暂时关掉此功能，因为norton发出了一个怪警报，不知有没有可能有冲突
	 /*
	 int					iErr			=	-1;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 int					i;
	 int					cnt				=	0;
	 QY_DMITEM			*	pItem			=	CONST_wellKnownSiteTable;
	 SOCK_TIMEOUT			to;
	 
	 //  traceLogA(  "detectInvalidInternet enters."  );

	 setSockShortTimeout(  &to  );		//  2005/05/23

	 //  如果有拨号，则不管外联的情况
	 for  (  i  =  0;  i  <  CONST_maxRasConns;  i  ++  )  {
		  if  (  gRasConn.rCI[i].bRasOn  )  break;
	 }
	 if  (  i  !=  CONST_maxRasConns  )  {
		 pQwm->ucbOnInternet  =  FALSE;								//  有拨号则由拨号处理程序处理  
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  GetTickCount(  )  -  pQwm->dwDetectInternetLastTickCnt  <  CONST_minDetectOnInternetInterval  )  {
		 //  traceLogA(  "detechInvalidInternet时间未到"  );
		 iErr  =  0;  goto  errLabel;
	 }
	 pQwm->dwDetectInternetLastTickCnt  =  GetTickCount(  );
	 
	 traceLogA(  "detectInvalidInternet enters."  );

	 for  (  i  =  0;  !cnt  &&  i  <  3;  i  ++,  pItem  ++  )  {			//  试图找到一个连通的 
		  if  (  canConnectWebSite(  &to,  pItem  )  )  cnt  ++;
		  if  (  pQwm->bQuit  )  goto  errLabel;					//  探测退出条件，以提高响应速度
	 }

 	 if  (  !pQwm->ucbOnInternet  )  {
		 if  (  !cnt  )  {											//  没有上过网
			 iErr  =  0;  goto  errLabel;
		 }
	 	 pQwm->ucbOnInternet  =  TRUE;	 							//  重新查一下拨号
		 pQwm->ucbOnInternetLogged  =  FALSE;
		 pQwm->dwOnInternetLastTickCnt  =  GetTickCount(  );
		 
		 iErr  =  0;  goto  errLabel;

	 }

  	 //	试图找到足够的连通网站数以证明连通外网了
	 for  (  ;  cnt  <  CONST_minConnectedSites  &&  pItem->type  !=  -1;  pItem  ++  )  {
		  if  (  canConnectWebSite(  &to,  pItem  )  )  cnt  ++;
		  if  (  pQwm->bQuit  )  goto  errLabel;					//  探测退出条件，以提高响应速度
	 }

	 if  (  cnt  >=  CONST_minConnectedSites  )  {
		 if  (  !pQwm->ucbOnInternetLogged  )  {
			 qwmLogOnInternetEvent(  pSubThreadInfo,  CONST_qyEventType_nm_onInternet,  NULL  );
			 pQwm->ucbOnInternetLogged  =  TRUE;
		 }
		 pQwm->dwOnInternetLastTickCnt  =  GetTickCount(  );
		 getCurTime(  pQwm->onInternetLastTimeBuf  );
		 }
	 else  if  (  cnt  <  CONST_minConnectedSites  &&  (  GetTickCount(  )  -  pQwm->dwOnInternetLastTickCnt  )  >=  CONST_maxDisconnectInterval  )  {
			   traceLogA(  "GetTickCount is %d,  lastTickCnt is %d,  最后一次连通时间 is %s",  GetTickCount(  ),  pQwm->dwOnInternetLastTickCnt,  pQwm->onInternetLastTimeBuf  );
 			   pQwm->ucbOnInternet  =  FALSE;
			   if  (  pQwm->ucbOnInternetLogged  )  {
				   qwmLogOnInternetEvent(  pSubThreadInfo,  CONST_qyEventType_nm_offInternet,  pQwm->onInternetLastTimeBuf  );
				   pQwm->ucbOnInternetLogged  =  FALSE;
			   }
	 }

	 //  原来采用的外联判断
	 //
	 
	 traceLogA(  "detectInvalidInternet leaves."  );
	 iErr  =  0;

errLabel:

	 //  traceLogA(  "detectInvalidInternet leaves."  );
	 
	 return  iErr;

  */
}


 int  detectProxyServer(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr					=	-1;
	 QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 QWM_USR_INFO			usrInfo;
	 QY_REG					reg;
	 DWORD					dwProxyEnable;
	 DWORD					len;
	 DWORD					dwRtn, dwSubKeyLength;
	 int					i;

	 if  (  !pQwm->uiRegUsrIndex  )  {
	 	 //  判断检查间隔, 在所有用户处理一遍之后，将作一休整
	 	 if  (  GetTickCount(  )  -  pQwm->dwDetectProxyServerLastTickCnt  <  CONST_minDetectProxyServerInterval  )  {
			 //  traceLogA(  "detectProxyServer时间未到"  );
			 iErr  =  0;  goto  errLabel;
		 }
		 pQwm->dwDetectProxyServerLastTickCnt  =  GetTickCount(  );
	 }
	 	 
	 TCHAR	tBuf[256]	=	_T(  ""  );
	 //  dwSubKeyLength  =  sizeof(  usrInfo.szSubKey  );
	 dwSubKeyLength  =  mycountof(  tBuf  );
     //  dwRtn  =  RegEnumKeyEx(  HKEY_USERS,  pQwm->uiRegUsrIndex,  usrInfo.szSubKey,  &dwSubKeyLength,  NULL,  NULL,  NULL,  NULL  );
	 dwRtn  =  RegEnumKeyEx(  HKEY_USERS,  pQwm->uiRegUsrIndex,  tBuf,  &dwSubKeyLength,  NULL,  NULL,  NULL,  NULL  );
	 if  (  dwRtn  !=  ERROR_SUCCESS  )  {
		 pQwm->uiRegUsrIndex  =  0;							//  所有的用户检查完毕，等待下一轮检查
		 iErr  =  0;  goto  errLabel;
	 }
	 pQwm->uiRegUsrIndex  ++  ;
	 myTChar2Str(  tBuf,  usrInfo.szSubKey,  mycountof(  usrInfo.szSubKey  )  );

	 //
	 //  现在开始处理刚被枚举的用户

	 if  (  !usrInfo.szSubKey[0]  )  goto  errLabel;		//  校验

	 //  下面取代理配置,	2003/09/14
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_USERS;
	 //  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
	 myStr2TChar(  usrInfo.szSubKey,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 len  =  lstrlen(  reg.rootKey  );
	 lstrcpyn(  reg.rootKey  +  len,  _T(  "\\"  ),  mycountof(  reg.rootKey  )  -  len  );
	 len  =  lstrlen(  reg.rootKey  );
	 lstrcpyn(  reg.rootKey  +  len,  _T(  CONST_qyRootKey_internetSettings  ),  mycountof(  reg.rootKey  )  -  len  );
	 
	 if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyEnable  ),  (  char  *  )&dwProxyEnable,  sizeof(  dwProxyEnable  )  ) 
		 &&  dwProxyEnable  
			//  &&  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyServer  ),  usrInfo.proxyServer,  sizeof(  usrInfo.proxyServer  )  )  ) 
			&&  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyServer  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  ) 
	 {
		 myTChar2Str(  tBuf,  usrInfo.proxyServer,  mycountof(  usrInfo.proxyServer  )  );
		 trim(  usrInfo.proxyServer  );
		}
	 else  usrInfo.proxyServer[0]  =  0;
	 
	 //  下面取用户名,  对NT, 除缺省外，统一为未知用户。
	 if  (  !_strcmpi(  usrInfo.szSubKey,  ".Default"  )  )  safeStrnCpy(  "(Default)",  usrInfo.name,  sizeof(  usrInfo.name  )  );
	 else  {
		   if  (  pQwm->env.iPlatformId  ==  PLATFORM_NT  )  {
			   safeStrnCpy(  "()",  usrInfo.name,  sizeof(  usrInfo.name  )  );
				}
		   else  {
			     //  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
			     myStr2TChar(  usrInfo.szSubKey,  reg.rootKey,  mycountof(  reg.rootKey  )  );
		   		 len  =  lstrlen(  reg.rootKey  );
		   		 lstrcpyn(  reg.rootKey  +  len,  _T(  "\\"  ),  mycountof(  reg.rootKey  )  -  len  );
	  	   		 len  =  lstrlen(  reg.rootKey  );
	 	   		 lstrcpyn(  reg.rootKey  +  len,  _T(  CONST_qyRootKey_explorer  ),  mycountof(  reg.rootKey  )  -  len  );
		   		 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_logonUsrName  ),  usrInfo.name,  sizeof(  usrInfo.name  )  )  )  
					 usrInfo.name[0]  =  0;
		   }
	 }
	 
	 traceLogA(  "detectProxyServer检查到subKey is [%s], usrName is [%s], proxyServer is [%s], index is %d",  usrInfo.szSubKey,  usrInfo.name,  usrInfo.proxyServer,  pQwm->uiRegUsrIndex  -  1  );

	 //  将usrName和proxyserver在pQwm->usrNames[]和proxyServers[]中遍历
	 //  对找到匹配的作相应的处理；否则作另外的处理。
	 for  (  i  =  0;  i  <  CONST_maxDetectedUsrs;  i  ++  )  {
		  if  (  !_strcmpi(  pQwm->usrInfos[i].szSubKey,  usrInfo.szSubKey  )  )  break;
	 }
	 
	 if  (  i  <  CONST_maxDetectedUsrs  )  {				//  找到了
		 if  (  !_strcmpi(  usrInfo.proxyServer,  pQwm->usrInfos[i].proxyServer  )  )  {
			 iErr  =  0;  goto  errLabel;					//  没有变化  
		 }
		 if  (  usrInfo.proxyServer[0]  )  {				//  作设置变化处理
			 //  lstrcpyn(  pQwm->usrInfos[i].proxyServer,  usrInfo.proxyServer,  sizeof(  pQwm->usrInfos[i].proxyServer  )  );
			 safeStrnCpy(  usrInfo.proxyServer,  pQwm->usrInfos[i].proxyServer,  mycountof(  pQwm->usrInfos[i].proxyServer  )  );
			 qwmLogProxyServerEvent(  pSubThreadInfo,  CONST_qyEventType_nm_proxyServerSet,  pQwm->usrInfos[i].name,  pQwm->usrInfos[i].proxyServer  );
			 iErr  =  0;  goto  errLabel;
		 }

		 //  作清除处理
		 pQwm->usrInfos[i].szSubKey[0]  =  0;
		 qwmLogProxyServerEvent(  pSubThreadInfo,  CONST_qyEventType_nm_proxyServerClear,  pQwm->usrInfos[i].name,  pQwm->usrInfos[i].proxyServer  );
		 iErr  =  0;  goto  errLabel;
		
	 }
	
	 //  没有找到该用户的匹配
	 
	 if  (  !usrInfo.name[0]  ||  !usrInfo.proxyServer[0]  )  {		//  没有在使用的
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 //  新的用户设置加入全局存储中
	 for  (  i  =  0;  i  <  CONST_maxDetectedUsrs;  i  ++  )  {
		  if  (  !pQwm->usrInfos[i].szSubKey[0]  )  break;
	 }

	 if  (  i  ==  CONST_maxDetectedUsrs  )  {				//  没有地方可以存放了
		 traceLogA(  "pQwm->usrInfos[]已存满了"  );
		 iErr  =  0;  goto  errLabel;								  
	 }

	 //  存放
	 memcpy(  &pQwm->usrInfos[i],  &usrInfo,  sizeof(  usrInfo  )  );
	 qwmLogProxyServerEvent(  pSubThreadInfo,  CONST_qyEventType_nm_proxyServerSet,  usrInfo.name,  usrInfo.proxyServer  );
	 
	 iErr  =  0;

errLabel:

	 return  iErr;

}


 QY_DMITEM  CONST_qwmSvrSecChkTaskTable[]  =
{
	{	CONST_qrtStep_chkPcInfo,				(  TCHAR  *  )chkPcInfo,			_T(  "chkPcInfo"  ),	},
	{	CONST_qrtStep_chkRecent,				(  TCHAR  *  )chkRecent,			_T(  "chkRecent"  ),	},
	{	CONST_qrtStep_chkIe,					(  TCHAR  *  )chkIe,				_T(  "chkIe"  ),		},
	{	CONST_qrtStep_chkRas,					(  TCHAR  *  )chkRas,				_T(  "chkRas"  ),		},
	{	CONST_qrtStep_chkProxyCfg,				(  TCHAR  *  )chkProxyCfg,			_T(  "chkProxyCfg"  ),	},
	//  {	CONST_qrtStep_chkOsInfo,			(  char  *  )chkOsInfo,				"检查多操作系统完成",	},
	{	CONST_qrtStep_chkShare,					(  TCHAR  *  )chkShare,				_T(  "chkShare"  ),		},
	//  {	CONST_qrtStep_chkSoftwareInstalled,	(  char  *  )chkSoftwareInstalled,	"检查安装的软件完成",	},
	//  {	CONST_qrtStep_chkRecycler,			(  char  *  )chkRecycler,			"检查回收站完成",		},
	//  {	CONST_qrtStep_chkRemovableStorage,	(  char  *  )chkRemovableStorage,	"检查曾使用移动存储完成",	},
	//  {	CONST_qrtStep_chkUsrInfo,			(  char  *  )chkUsrInfo,			"检查用户信息完成",		},
	{	CONST_qrtStep_chkDiskDrvFile,			(  TCHAR  *  )chkDiskDrvFile,		_T(  "chkDiskDrvFile"  ),	},
	{	CONST_qrtStep_chkNormalDiskDrvFile,		(  TCHAR  *  )chkNormalDiskDrvFile,	_T(  "chkNormalDiskDrvFile"  ),	},			//  检查普通文件，测试时先放在前面，2005/05/09
	/*
	{	CONST_qrtStep_chkInternet,				(  char  *  )chkInternet,			"检查非法外联完成",		},
	*/
	{	-1,										NULL,											},
};

 QY_DMITEM  CONST_qwmSvrMonIeTaskTable[]  =
{
	{	CONST_qrtStep_chkShare,					(  TCHAR  *  )chkShare,				_T(  "chkShare"  ),		},
	{	CONST_qrtStep_chkIe,					(  TCHAR  *  )chkIe,				_T(  "chkIe"  ),		},
	{	-1,										NULL,											},
};


int  myStartProtectingThread(  void  *  pQwmParam,	int  iPlatformId,  TCHAR  *  pure2DllName,  TCHAR  *  remoteProcessName  );


 int  doQwmCmd(  void  *  lpParameter,  void  *  p1,  void  *  p2  )
{
	 int					iErr			=	-1;
	 QWM_THREADINFO			threadInfo;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG			threadCfg;
	 QY_REG					reg;
	 int					loopCtrl		=	0;

	 // 取得MAC地址,  2007/02/17
	 getQwmMacs(  &pQwm->env,  &pQwm->macsInfo  );  
	 if  (  getQwmCfg(  pQwm,  TRUE  )  )  goto  errLabel;

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;
	 lstrcpyn(  reg.rootKey,  _T(  ROOT_KEY_AWM  ),  mycountof(  reg.rootKey  )  );  
	 reg.pEncCtx  =  &pQwm->encCtx;
	
	 threadInfo.pCfg->nInterval  =  pQwm->cfg.nInterval_qwmThreadProcCmd;
	 memcpy(  &threadInfo.pCfg->rasRule,  &pQwm->cfg.pcRules.ras,  sizeof(  QNM_RAS_RULE  )  );
	 threadInfo.dwLoopCtrl  =  loopCtrl;

	 if  (  pQwm->cmd.ulbDoSecChk  )  {
		 //  这里开始执行安检
		 if  (  doSecChk(  &threadInfo,  CONST_qwmSvrSecChkTaskTable  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbMonIe  )  {	//  2006/03/07
		 if  (  doSecChk(  &threadInfo,  CONST_qwmSvrMonIeTaskTable  )  )  goto  errLabel;
	 }
#if  0	//  2011/08/28
	 if  (  pQwm->cmd.ulbDoReboot  )  {
		 if  (  doReboot(  &threadInfo,  0,  0,  0  )  )  goto  errLabel;
	 }
#endif
	 if  (  pQwm->cmd.ulbDoRemoveUsb  )  {			//  2005/10/08
		 if  (  doRemoveUsb(  &threadInfo,  0,  0  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbViewRemoteDesktop  )  {	//  2006/02/12
		 if  (  showRemoteDesktop(  &threadInfo,  0,  0,  0  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbCapScreen  )  {			//  2006/03/06
		 if  (  doCapScreen(  &threadInfo,  0,  0  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbMonDesktop  )  {			//  2006/03/06
		 if  (  showRemoteDesktop(  &threadInfo,  0,  0,  TRUE  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbNetFlowWarn  )  {			//  2006/09/12
		 if  (  showNetFlowWarn(  &threadInfo,  0,  0  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbStartProtectingThread_sys  )  {
		 if  (  myStartProtectingThread(  pQwm,  pQwm->env.iPlatformId,  pQwm->pure2DllName,  _T(  CONST_remoteProcessName_sys  )  )  )  goto  errLabel;
	 }
	 if  (  pQwm->cmd.ulbStartProtectingThread_usr  )  {
		 if  (  myStartProtectingThread(  pQwm,  pQwm->env.iPlatformId,  pQwm->pure2DllName,  _T(  CONST_remoteProcessName_usr  )  )  )  goto  errLabel;
	 }


	 iErr  =  0;

errLabel:

	 if  (  !iErr  &&  pQwm->cmd.respOkStr[0]  )  {
		 traceLogA(  "给出运行正常的响应"  );
		 qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdRespOk  ),  pQwm->cmd.respOkStr  );
	 }
	 traceLogA(  "doQwmCmd: 执行任务%s",  !iErr  ?  "OK"  :  "Failed"  );

	 return  iErr;
}




 int  doSecChk(  QWM_THREADINFO  *  pSubThreadInfo,  QY_DMITEM  *  pSecChkTaskTable  )
{
	 int					iErr			=	-1;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 TCHAR					buf[128];

	 traceLogA(  "doSecChk enters"  );

	 SetThreadPriority(  GetCurrentThread(  ),  THREAD_PRIORITY_IDLE  );

	 memset(  &gQyRegTool,  0,  sizeof(  gQyRegTool  )  );

	 getQyEnv(  pQwm->env.pDynLibs,  &gQyRegTool.env  );
	 //  gQyRegTool.env.pDynLibs  =  pQwm->env.pDynLibs;
	 //
	 if  (  gQyRegTool.env.iPlatformId  ==  CONST_qyPlatform_win32  ||  gQyRegTool.env.iPlatformId  ==  CONST_qyPlatform_win95  )  goto  errLabel;

	 gQyRegTool.iSystemId  =  pQwm->iSystemId;	//  qyGetSystemId(  );
	 gQyRegTool.iCustomId  =  pQwm->iCustomId;	//  qyGetCustomId(  );
	 gQyRegTool.iServiceId  =  CONST_qyServiceId_qwm;
	 memcpy(  gQyRegTool.ver,  qnmVerStr(  gQyRegTool.iServiceId  ),  sizeof(  gQyRegTool.ver  )  -  1  );


	 //  取得MAC地址
	 getQwmMacs(  &gQyRegTool.env,  &gQyRegTool.macsInfo  );
	 if  (  qwmGetPcName(  gQyRegTool.pcName,  sizeof(  gQyRegTool.pcName  )  )  )  gQyRegTool.pcName[0]  =  0;
	 
	 setSockTimeout(  &gQyRegTool.cfg.to  );
	 gQyRegTool.cfg.nInterval_chkIndexDatFile  =  200;
	 gQyRegTool.cfg.usTries_connect  =  3;
	 gQyRegTool.cfg.usTries_waitSndFinished  =  3;
	 memcpy(  &gQyRegTool.cfg.cnt,  &pQwm->cfg.cnt,  sizeof(  QY_LOGICAL_SERVER  )  );
	 gQyRegTool.cfg.ucbGetPcAsset  =  pQwm->cfg.ucbGetPcAsset;		//  2004/11/15添加

	 if  (  initSecChk(  pSecChkTaskTable  )  )  goto  errLabel;

	 //  删除退出键以防止误操作
	 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdShallQuit  )  );

	 if  (  !pSecChkTaskTable  )  {
		 traceLogA(  "无检查任务时作资产管理"  );
		 MT_SUBTHREADINFO			subThreadInfo;							//  2004/05/14

		 memset(  &subThreadInfo,  0,  sizeof(  subThreadInfo  )  );		//  2004/05/14添加
		 subThreadInfo.pParentParam  =  &gQyRegTool;
		 subThreadInfo.pTo  =  &gQyRegTool.cfg.to;
	
		 if  (  chkPcInfo(  &subThreadInfo,  NULL,  NULL  )  )  goto  errLabel;

		}
	 else  {
		   traceLogA(  "有检查任务则等待任务完成"  );	//  下面加上了对严重错误的判断，2005/05/04
	 	   for  (  ;  !pQwm->bQuit;  )  {
			    if  (  gQyRegTool.ucbSeriousErr  )  {
					traceLogA(  "doSecChk: 有严重错误出现，将紧急退出"  );  goto  errLabel;
				}
				if  (  !qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_chdShallQuit  ),  (  char  *  )buf,  sizeof(  buf  )  )  &&  !lstrcmpi(  buf,  _T(  CONST_qwmCfgVal_chdShallQuit  )  )  )  {	//  2005/05/09
					traceLogA(  "得到了检查工作应停止的指令"  );  break;
				}

		 	    Sleep(  1000  );
		 		if  (  !gQyRegTool.bInProgress  &&  !gQyRegTool.ucbInSnd  )  break;
	 	   }
		   traceLogA(  "检查任务完成"  );
	 }

	 iErr  =  0;
		 
errLabel:

	 gQyRegTool.bQuit  =  TRUE;

	 exitSecChk(  );
	 	
	 SetThreadPriority(  GetCurrentThread(  ),  THREAD_PRIORITY_NORMAL  );
	 
	 traceLogA(  "doSecChk leaves"  );
	 return  0;
}



