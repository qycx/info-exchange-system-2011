
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


 int  procDetectionResult(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;


	 iErr  =  0;
//  errLabel:
	 return  iErr;
}


 int  detectAndWarnToInterMon(  QWM_THREADINFO  *  pSubThreadInfo  )	 
{
	 return  0;		//  2007/02/28, 暂时关掉此功能，因为norton发出了怪警报，不知道与此功能有没有冲突
	 /*
	 int							iRet					=	-1;
	 QY_W_MON					*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 QY_LOGICAL_SERVER			*	pInterMon				=	&pQwm->cfg.interMon;
	 QWM_WARNTOINTERMON_INFO		warnInfo;
	 char							encData[128]			=	"";
	 unsigned  int					encLen					=	sizeof(  encData  );

	 char							tmpExeName[512  +  1]	=	"";
	 STARTUPINFO					si;
	 PROCESS_INFORMATION			pi;
	 BOOL							bProcessCreated			=	FALSE;
	 char							buf[32]					=	"";
 	 char							sndBuf[512  +  1]		=	"";
	 int							i;

	 //  拨号禁止才报警
	 //  if  (  pQwm->cfg.rasRule.ucRasCmd  !=  CONST_rasCmd_prohibited  )  return  0;
	 //  当探测在互联网上时，立即报警；不能通过detectInvalidInternet发现时，为避免遗漏，间隔报警
	 //  if  (  !pQwm->ucbOnInternet  &&  (  pSubThreadInfo->dwLoopCtrl  %  CONST_loopCtrl_detectAndWarnToInterMon  )  )  return  0;
	 if  (  pSubThreadInfo->dwLoopCtrl  %  CONST_loopCtrl_detectAndWarnToInterMon  )  return  0;
	 
	 traceLogA(  "detectAndWarnToInterMon enters"  );

	 if  (  !bIpValid(  pInterMon->ip  )  ||  !pInterMon->port  )  {
		 traceLogA(  "interMon ip 没配置或不正确"  );  goto  errLabel;
	 }

	 //  1、初始化
	 //  2、构建原始数据:具有识别该计算机的特征mac,computerName
	 memset(  &warnInfo,  0,  sizeof(  warnInfo  )  );
	 if  (  pQwm->macsInfo.nMacs  )  lstrcpyn(  warnInfo.mac0,  (  char  *  )pQwm->macsInfo.macs[0],  sizeof(  warnInfo.mac0  )  );
	 lstrcpyn(  warnInfo.pcName,  pQwm->pcName,  sizeof(  warnInfo.pcName  )  );

	 //  3、加密
	 if  (  qnmEncData(  &pQwm->updateEncCtx,  (  char  *  )&warnInfo,  sizeof(  warnInfo  ),  encData,  &encLen  )  )  {
		 traceLogA(  "qnmEncData failed."  );  goto  errLabel;
	 }
	 //  4、组装用于传输的数据:校验/长度/加密后数据(需要经过数据转换为ascii才能够在url中发送)
	 {
	 char  *  ptr  =  sndBuf;

	 
	 lstrcpyn(  ptr,  CONST_qyMagic_interMon,  sizeof(  sndBuf  )  );
	 ptr  +=  strlen(  CONST_qyMagic_interMon  );  
	 qyl2x(  encLen,  ptr,  8  );
	 ptr  +=  8;
	 qybuf2x(  encData,  encLen,  ptr  );
	 ptr[2  *  encLen]  =  0;
	 if  (  ptr  +  2  *  encLen  +  1  -  sndBuf  >  sizeof(  sndBuf  )  )  {
		 traceLogA(  "sndBuf is too small."  );  goto  errLabel;
	 }
	 }

	 //  5、发送传输数据
	 memset(  &si,  0,  sizeof(  si  )  );
	 memset(  &pi,  0,  sizeof(  pi  )  );
		 
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
 	 si.cb  =  sizeof(  STARTUPINFO  );
 	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK  |  STARTF_USESHOWWINDOW;
	 si.wShowWindow  =  SW_HIDE;

	 GetWindowsDirectory(  tmpExeName,  sizeof(  tmpExeName  )  );
	 tmpExeName[2] = 0;
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  "\\Program Files\\Internet Explorer\\iexplore.exe",  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 if  (  qyQuoteFileName(  tmpExeName,  sizeof(  tmpExeName  )  )  )  goto  errLabel;
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  " http://",  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  pInterMon->ip,  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  ":",  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 wsprintf(  buf,  "%d",  pInterMon->port  );
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  buf,  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  "/",  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  sndBuf,  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 
	 if  (  !CreateProcess(  NULL,  tmpExeName,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
	 bProcessCreated  =  TRUE;
	 //  traceLogA(  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );
	 traceLogA(  "启动报警 succeeded,  new processId is %d,  new threadId is %d.",  pi.dwProcessId,  pi.dwThreadId  );

	 //  for  (  i  =  0;  i  <  5  &&  !pQwm->bQuit;  i  ++  )  Sleep(  1000  );
	 for  (  i  =  0;  i  <  15  &&  !pQwm->bQuit;  i  ++  )  Sleep(  1000  );			//  2004/11/12 changed, 为了适应共享拨号上网的速率很低的情况。 

	 iRet  =  0;

errLabel:
	 
 	 if  (  bProcessCreated  )  {
		 traceLogA(  "注意：terminateProcess"  );
		 TerminateProcess(  pi.hProcess,  1  );
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }

	 traceLogA(  "detectAndWarnToInterMon leaves"  );

	 return  iRet;
	 */
}


