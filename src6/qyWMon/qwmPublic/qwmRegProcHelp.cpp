

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<tchar.h>
#include	<iphlpapi.h>
//  #include	"resource.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"
#include	"qwmAllHints.h"
#include	"qnmHotKeys.h"


 DWORD  WINAPI  doRegProc(  LPVOID  lpParameter  )
{	 
	 int						iErr		=  -1;
	 QY_REG_TOOL	*			pRegTool	=  (  QY_REG_TOOL  *  )lpParameter;
	 BOOL						bEncInited  =  FALSE;
	 QY_ENC_CTX					encCtx,  commEncCtx;
	 MT_SUBTHREADINFO			subThreadInfo;							//  2004/05/14
	 QY_REG						tmpReg;
	 int						i;
	 TCHAR						tmpPath[MAX_PATH  +  1];
	 TCHAR						tmpFileName[MAX_PATH  +  1];
	 TCHAR						tmpExeName[MAX_PATH  +  1];
	 STARTUPINFO				si;
	 PROCESS_INFORMATION		pi;

	 memset(  &subThreadInfo,  0,  sizeof(  subThreadInfo  )  );		//  2004/05/14添加
	 subThreadInfo.pParentParam  =  pRegTool;
	 subThreadInfo.pTo  =  &pRegTool->cfg.to;

	 memset(  &si,  0,  sizeof(  si  )  );
	 memset(  &pi,  0,  sizeof(  pi  )  );

	 pRegTool->bInProgress  =  TRUE;
	 pRegTool->iProgress  =  0;
	 setProgressTxt(  pRegTool,  0  );

	 memset(  &encCtx,  0,  sizeof(  encCtx  )  );
	 memset(  &commEncCtx,  0,  sizeof(  commEncCtx  )  );
	 if  (  initQnmEnc(  &encCtx,  NULL,  NULL,  &commEncCtx  )  )  goto  errLabel;
	 bEncInited  =  TRUE;
	 
	 memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
	 tmpReg.pEncCtx  =  &encCtx;
	 lstrcpyn(  tmpReg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  tmpReg.rootKey  )  );
	 
	 traceLogA(  "本注册程序将%s",  pRegTool->cfg.ucbInstall  ?  "安装客户端软件"  :  "不安装客户端软件"  );
	 if  (  pRegTool->cfg.ucbInstall  )  {
	 	 
		 if  (  !GetTempPath(  mycountof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
		 if  (  !GetTempFileName(  tmpPath,  _T(  "wrd"  ),  0,  tmpFileName  )  )  goto  errLabel;
		 if  (  qyOutputResourceFile(  pRegTool->cfg.idrData,  tmpFileName  )  )  goto  errLabel;  //  生成并启动受控端程序

		 qyDelRegCfg(  tmpReg.rootKey,  _T(  CONST_qwmCfgName_isOk  )  );
		 qyDelRegCfg(  tmpReg.rootKey,  _T(  CONST_qwmCfgName_isOkRes  )  );
		 
		 traceLogA(  "Now start qwm "  );
		 si.cb  =  sizeof(  STARTUPINFO  );
		 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;

		 lstrcpyn(  tmpExeName,  tmpFileName,  mycountof(  tmpExeName  )  );
		 if  (  qyQuoteFileName(  tmpExeName,  mycountof(  tmpExeName  )  )  )  goto  errLabel;
		 if  (  !CreateProcess(  NULL,  tmpExeName,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
		 traceLogA(  "CreateProcess %s succeeded.",  tmpExeName  );

		 TCHAR						buf[128]	=  _T(  "HI"  );
		 for  (  i  =  0;  i  <  CONST_qrtStep_waitForQwm;  i  ++  )  {
			  if  (  pRegTool->bQuit  )  goto  errLabel;

		  	  if  (  !qyGetRegCfgEx(  &tmpReg,  _T(  CONST_qwmCfgName_isOkRes  ),  (  char  *  )buf,  sizeof(  buf  )  )  
				  &&  !lstrcmpi(  buf,  _T(  CONST_qwmCfgVal_isOkRes  )  )  )  
			  {
				  break;
			  }
			  pRegTool->iProgress  =  i;
			  Sleep(  1000  );
	 	 }
	 	 if  (  i  ==  CONST_qrtStep_waitForQwm  )  {
			 setProgressTxt(  pRegTool,  TRUE  );
			 goto  errLabel;
		 }
	 }
	 pRegTool->iProgress  =  CONST_qrtStep_waitForQwm;

	 if  (  !pRegTool->cfg.ucbReged  )  {
	 	 //  send all 注册信息到管理中心。 
	 	 traceLogA(  "准备send 注册信息到管理中心"  );
	 	 if  (  qrtRegToServ(  pRegTool  )  )  goto  errLabel;
		 traceLogA(  "发送注册信息成功"  );
	 }
	 
	 traceLogA(  "对已注册主机检查补丁信息"  );		//  2004/05/14
	 chkPcInfo(  &subThreadInfo,  NULL,  NULL  );	 
	 pRegTool->iProgress  =  CONST_qrtStep_regOk;

	 //  在这里等待发送线程将数据发送完毕
	 for  (  i  =  0;  i  <  pRegTool->cfg.usTries_waitSndFinished  &&  !pRegTool->ucbSndFinished;  i  ++  )  {
		  Sleep(  1000  );
	 }
	 if  (  i  ==  pRegTool->cfg.usTries_waitSndFinished  )  {
		 setProgressTxt(  pRegTool,  TRUE  );  goto  errLabel;
	 }
	 pRegTool->iProgress  =  CONST_qrtStep_waitSndFinished;
	 
	 /*  //  2005/07/30, 自动注册项早就取消了，所以这里就不用了
	 char	*		svRunKey_autoReg;
	 
	 svRunKey_autoReg	=		g_bIsWinNT  ?  CONST_qyCfgName_ntRunKey  :  CONST_qyCfgName_runOnceKey;
	 traceLogA(  "try to del %s\\%s",  svRunKey_autoReg,  CONST_regValName_autoReg  );
	 if  (  !qyDelRegCfg(  svRunKey_autoReg,  CONST_regValName_autoReg  )  )  {
		 traceLogA(  "删除自动注册项"  );
	 }
	 */
	 
	 traceLogA(  "注册完毕"  );

	 setProgressTxt(  pRegTool,  0  );
	 for  (  ;  pRegTool->iProgress  <  CONST_qrtStep_finished  &&  !pRegTool->bQuit;  pRegTool->iProgress  ++  )  {
		  Sleep(  1000  );
	 }

	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  pi.hThread  )  )  CloseHandle(  pi.hThread  );
	 if  (  isHandleValid(  pi.hProcess  )  )  CloseHandle(  pi.hProcess  );	 

	 if  (  bEncInited  )  exitQnmEnc(  &encCtx,  NULL,  NULL,  &commEncCtx  );

	 if  (  iErr  )  {
		 setProgressTxt(  pRegTool,  TRUE  );
	 }

	 if  (  !iErr  )  pRegTool->ucbRegFinished  =  TRUE;
	 pRegTool->bInProgress  =  FALSE;

	 return  iErr;

}

 int  qrtRegToServ(  QY_REG_TOOL  *  pQrt  )
{
	int						iErr			=	-1;
	ASR_SOCK				aS;
	int						i				=	0;
	char					ip[16];
	QNM_COMM_AUTHINFO		authInfo;
	QY_COMM_SESSION			session;
	QY_COMM_RESP			tmpResp;
	char					cfgsBuf[4096];
	
	traceLogA(  "qrtRegToServ enters."  );
		
	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
	
	//  2005/08/18
	if  (  pQrt->cfg.ucbDj  &&  pQrt->iSystemId  ==  CONST_qySystemId_secChk  )  {
		qwmModifyFile(  pQrt  );
		iErr  =  0;  goto  errLabel;
	}


	traceLogA(  "连接服务器 %s : %d",  pQrt->cfg.cnt.ip,  pQrt->cfg.cnt.port  );
	setProgressTxt(  pQrt,  0  );
	for  (  i  =  0;  i  <  pQrt->cfg.usTries_connect;  i  ++  )  {
		 if  (  !qyConnect(  pQrt->cfg.cnt.ip,  pQrt->cfg.cnt.port,  &aS,  pQrt->cfg.to.iConnect  )  )  {
			 break;		
		 }
		 Sleep(  1000  );
		 pQrt->iProgress  ++  ;
	}
	if  (  i  ==  pQrt->cfg.usTries_connect  )  {
		traceLogA(  "连接服务器失败。"  );
		setProgressTxt(  pQrt,  TRUE  );  goto  errLabel;
	}
	MACRO_qyAssert(  pQrt->iProgress  <=  CONST_qrtStep_connected,  _T(  "CONST_qrtStep_connected"  )  );
	pQrt->iProgress  =  CONST_qrtStep_connected;
	
	if  (  getLocalIpBySocket(  aS.sockFd,  ip  )  )  goto  errLabel;
	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	if  (  makeQwmAuthInfo(  pQrt->ver,  &pQrt->macsInfo,  &authInfo  )  )  goto  errLabel;
	memcpy(  authInfo.ip,  ip,  sizeof(  authInfo.ip  )  );
	
	session.encCtx.type  =  CONST_qyEncType_qnm;

	if  (  qyTellService(  pQrt->iServiceId,  pQrt->ver,  &pQrt->commEncCtx,  (  char  *  )&authInfo,  sizeof(  authInfo  ),  &aS,  &pQrt->cfg.to,  &session  )  )  goto  errLabel;
	traceLogA(  "qyTellService ok."  );
	if  (  qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	traceLogA(  "get respCode %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );

	if  (  isRcQuit(  tmpResp.head.usCode  )  )  {
		setProgressTxt(  pQrt,  TRUE  );  goto  errLabel;
	}
	pQrt->iProgress  =  CONST_qrtStep_canReg;

	if  (  isRcUpdate(  tmpResp.head.usCode  )  )  {
		setProgressTxt(  pQrt,  TRUE  );  goto  errLabel;
	}
	pQrt->iProgress  =  CONST_qrtStep_chkQwmVer;

	if  (  !isRcRedirect(  tmpResp.head.usCode  )  &&  !isRcOk(  tmpResp.head.usCode  )  )  {
		setProgressTxt(  pQrt,  TRUE  );  goto  errLabel;
	}
	
	if  (  isRcRedirect(  tmpResp.head.usCode  )  )  {
		traceLogA(  "错误：现在的版本不支持重定向"  );
		setProgressTxt(  pQrt,  TRUE  );  goto  errLabel;	//  2004/05/18
	}

	pQrt->iProgress  =  CONST_qrtStep_readyToSndRegInfo;

	traceLogA(  "发送注册信息"  );
	setProgressTxt(  pQrt,  0  );
	pQrt->regInfo.iCustomId  =  qyhtonl(  pQrt->regInfo.iCustomId  );
	//  2005/01/18对注册信息转换成UTF编码
	for  (  i  =  0;  i  <  sizeof(  pQrt->regInfo.u.cols  )  /  sizeof(  pQrt->regInfo.u.cols[0]  );  i  ++  )  {
		 MACRO_htonl(  pQrt->regInfo.uiFieldIds[i]  );  //  myStr2Utf8(  pQrt->regInfo.u.cols[i],  sizeof(  pQrt->regInfo.u.cols[i]  )  );
	}
	if  (  qySendReq(  &session,  &aS,  &pQrt->cfg.to,  CONST_qyCmd_reg,  (  char  *  )&pQrt->regInfo,  sizeof(  pQrt->regInfo  )  )  )  goto  errLabel;
	pQrt->iProgress  ++  ;
	pQrt->regInfo.iCustomId  =  qyntohl(  pQrt->regInfo.iCustomId  );	//  注意将iCustomId从网络字节顺序还原为主机字节顺序
	if  (  qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;
	pQrt->iProgress  ++  ;
	
	if  (  qySendReq(  &session,  &aS,  &pQrt->cfg.to,  CONST_qyCmd_end,  NULL,  0  )  )  goto  errLabel;
	qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  );
	
	iErr  =  0;
	
errLabel:

	if  (  bQySockOpen(  &aS  )  )  qyDisconnect(  &aS  );
	
	traceLogA(  "regToServ leaves with %s.",  iErr  ?  "失败"  :  "成功"  );

	return  iErr;

}

