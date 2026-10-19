

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"showPcProcess.h"



 int  showPcProcess(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int						iErr			=	-1;
	 QY_W_MON				*	pQwm			=	NULL;
	 myPROCESSINFO			*	ppi				=	NULL;  
	 myPROCESSINFO			*	tmpppi			=	NULL;
	 QY_PC_COMMU				pcCommU;
	 int						i;
	 QY_PROCESS_PROP		*	pProcess		=	NULL;
	 int						len;
	 QWM_SESSION				session;
	 QY_SOCK					sock;
	 BOOL						bSessionOpen	=	FALSE;
	 char						buf[1024]		=	"";
	 QY_COMM_RESP				tmpResp;


	 if  (  !pThreadInfo  )  return  -1;
	 pQwm  =  (  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 if  (  pQwm->env.iPlatformId  ==  CONST_qyPlatform_winnt  )  return  -1;
	 QWM_DYN_LIB			*	pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 traceLogA(  "showPcProcess enters"  );

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
		}
	 }

	 if  (  !(  ppi  =  CreateProcListSnapshot(  &pQwm->env,  NULL  )  )  )  goto  errLabel;

	 //  printProcessInfo(  ppi  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

#define		CONST_maxSndProcesses						10

	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_process,  pQwm,  pcCommU  );
	 //
	 for  (  i  =  0,  tmpppi  =  ppi;  tmpppi  &&  i  <  sizeof(  pcCommU.processesInfo.mems  )  /  sizeof(  pcCommU.processesInfo.mems[0]  );  tmpppi  =  tmpppi->next  )  {
		  pProcess  =  &pcCommU.processesInfo.mems[i];
		  pProcess->dwPid  =  tmpppi->dwProcID;
		  myTChar2Utf8(  tmpppi->svApp,  pProcess->appPath,  sizeof(  pProcess->appPath  )  );
		  myTChar2Utf8(  tmpppi->cmdLine,  pProcess->cmdLine,  sizeof(  pProcess->cmdLine  )  );
		  //  traceLogA(  "未完成：这里需要再填充一些进程信息"  );
		  //
		  i  ++  ;
		  //
		  if  (  i  <  CONST_maxSndProcesses  )  continue;
		  //	
		  pcCommU.processesInfo.cnt  =  i;
		  if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
		  if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcProcess,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
		  if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		  //
		  i  =  0;
		  memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );		  
		  MACRO_makePcCommHead(  CONST_pcCommType_process,  pQwm,  pcCommU  );
	 }

	 if  (  i  )  {
		 pcCommU.processesInfo.cnt  =  i;
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcProcess,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );		  
		 MACRO_makePcCommHead(  CONST_pcCommType_process,  pQwm,  pcCommU  );
	 }

	 //  发结束符
	 pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcProcess,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 QY_PC_PROCESSRULES		rules;
	 memset(  &rules,  0,  sizeof(  rules  )  );
	 memcpy(  &rules,  buf,  min(  sizeof(  rules  ),  tmpResp.head.len  )  );
	 MACRO_ntohl(  rules.cnt  );
	 for  (  i  =  0;  i  <  (  int  )rules.cnt;  i  ++  )  MACRO_ntohl(  rules.mems[i].dwPid  );
	 //
	 HANDLE		hProcess;  BOOL  bTerminated;
	 for  (  i  =  0;  i  <  (  int  )rules.cnt;  i ++  )  {
		  for  (  tmpppi  =  ppi;  tmpppi;  tmpppi  =  tmpppi->next  )  if  (  rules.mems[i].dwPid  ==  tmpppi->dwProcID  )  break;
		  if  (  !tmpppi  )  {  traceLogA(  "严重错误：居然没找到进程的名称"  );  continue;  }
		  bTerminated  =  FALSE;
		  if  (  rules.mems[i].dwPid  !=  GetCurrentProcessId(  )  )  {	//  要确保不会杀掉自己，呵呵
			  if  (  !(  hProcess  =  OpenProcess(  PROCESS_TERMINATE,  FALSE,  rules.mems[i].dwPid  )  )  )  qyDisplayLastError(  "OpenProcess"  );
			  else  {
				    bTerminated  =  TerminateProcess(  hProcess,  0  );
			    	CloseHandle(  hProcess  );			
		  	  }
		  }
		  TCHAR	tBuf[256]	=	_T(  ""  );
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Killing process %s( %d ) %s"  ),  tmpppi->svApp,  rules.mems[i].dwPid,  bTerminated  ?  _T(  "OK!"  )  :  _T(  "Failed."  )  );
		  myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		  qwmLogGeneralEvent(  pThreadInfo,  CONST_qyEventType_nm_processMgr,  "",  buf,  "",  TRUE  );

	 }

	 
	 iErr  =  0;

errLabel:
	
	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 if  (  ppi  )  DestroyProcListSnapshot(  &pQwm->env,  ppi  );

	 if  (  g_bIsWinNT  )  {
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

	 traceLogA(  "showPcProcess leaves"  );

	 return  iErr;
}


 //  2006/04/14
 int	 showPcProcessModules(  QWM_THREADINFO  *  pThreadInfo  )
{
	int							iErr			=	-1;
	QY_W_MON				*	pQwm			=	NULL;
    DWORD						aProcesses[1024], cbNeeded, cProcesses;
    unsigned int				i, j, k;
	DWORD						processId;
	QY_PC_COMMU					pcCommU;
	QY_PCPROCESSMODULE_PROP	*	pModule			=	NULL;
	int							len;
	QWM_SESSION					session;
	QY_SOCK						sock;
	BOOL						bSessionOpen	=	FALSE;
	char						buf[1024]		=	"";
	QY_COMM_RESP				tmpResp;

	pQwm  =  (  QY_W_MON  *  )pThreadInfo->pParaentParam;	
	if  (  pQwm->env.iPlatformId  ==  CONST_qyPlatform_winnt  )  return  -1;
	QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	if  (  !pDynLib->pEnumProcesses  ||  !pDynLib->pEnumProcessModules  ||  !pDynLib->pGetModuleFileNameExW  )  return  0;

	traceLogA(  "showPcProcessModules enters"  );
	
    if  (  !pDynLib->pEnumProcesses(  aProcesses,  sizeof(  aProcesses  ),  &cbNeeded  )  )  goto  errLabel;


	clearQySock(  &sock  );
	memset(  &session,  0,  sizeof(  session  )  );

	if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	bSessionOpen		=		TRUE;
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	MACRO_makePcCommHead(  CONST_pcCommType_processModule,  pQwm,  pcCommU  );

#define		CONST_maxSndModules							32
#if  CONST_maxProcesses  <=  CONST_maxSndModules
	 #error	"CONST_maxProcesses  can't be <=  CONST_maxSndModules
#endif

    // Calculate how many process identifiers were returned.
    cProcesses  =  cbNeeded  /  sizeof(  DWORD  );

    // Print the name of the modules for each process.

	i  =  0;
    for  (  j  =  0;  j  <  cProcesses;  j  ++  )  {
		 processId  =  aProcesses[j];

		 {
			 HMODULE		hMods[1024];
    		 HANDLE			hProcess;
    		 DWORD			cbNeeded;

       
			 // Get a list of all the modules in this process.
			 hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION  |  PROCESS_VM_READ,  FALSE,  processId  );
			 if  (  hProcess  )  {
				 if  (  pDynLib->pEnumProcessModules(  hProcess,  hMods,  sizeof(  hMods  ),  &cbNeeded  )  )  {
					 for  (  k  =  0;  k  <  (  cbNeeded  /  sizeof(  HMODULE  )  );  k  ++  )  {
						  WCHAR  wzModName[MAX_PATH];
						  // Get the full path to the module's file.

						  if  (  pDynLib->pGetModuleFileNameExW(  hProcess,  hMods[k],  wzModName,  mycountof(  wzModName  )  )  )  {
							  // Print the module name and handle value.
							  //  printf("\t%S (0x%08X)\n", wzModName, hMods[k] );


							  pModule  =  &pcCommU.processModulesInfo.mems[i];
							  pModule->dwPid  =  processId;
							  myWChar2Utf8(  wzModName,  pModule->modulePath,  sizeof(  pModule->modulePath  )  );
							  //  traceLogA(  "未完成：这里需要再填充一些进程信息"  );
							  //
							  i  ++  ;
							  //
							  if  (  i  <  CONST_maxSndModules  )  continue;
							  //	
							  pcCommU.processModulesInfo.cnt  =  i;
							  if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
		  					  if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcProcessModule,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
		  					  if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		  					  //		  							  
							  i  =  0;
		  					  memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );		  
		  					  MACRO_makePcCommHead(  CONST_pcCommType_processModule,  pQwm,  pcCommU  );


    					  }
    				 }
    			 }
   
				 CloseHandle( hProcess );

			 }
	
		 }
	}


	if  (  i  )  {
		 pcCommU.processesInfo.cnt  =  i;
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcProcessModule,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );		  
		 MACRO_makePcCommHead(  CONST_pcCommType_processModule,  pQwm,  pcCommU  );
	 }

	 //  发结束符
	 pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcProcessModule,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;


	iErr  =  0;

errLabel:

	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	traceLogA(  "showPcProcessModules leaves"  );

	return  iErr;
}



 int  printProcessInfo(  myPROCESSINFO  *  ppi  )
{
#ifndef  __DEBUG__
	     return  0;
#else
	 myPROCESSINFO	*	tmpppi	=	NULL;

	 for  (  tmpppi  =  ppi;  tmpppi;  tmpppi  =  tmpppi->next  )  {
		  traceLogA(  "app is %s, pid is %d",  tmpppi->svApp,  tmpppi->dwProcID  );
	 }

	 return  0;
#endif
}








