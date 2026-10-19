

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"asrWMon.h"
#include	"qySyncCommProc.h"




 extern  "C"  int  qwmLogEvent(  void  *  pSubThreadInfoParam,  QWM_EVENT  *  pEvent  )
{
	 int	iErr  =  -1;
	 QWM_THREADINFO		*	pThreadInfo		=  (  QWM_THREADINFO  *  )pSubThreadInfoParam;
	 QY_W_MON			*	pQwm			=  (  QY_W_MON  *  )pThreadInfo->pParaentParam;

	 #ifdef  __DEBUG__
			 printQwmEvent(  _T(  ""  ),  pEvent  );
	 #endif


	 //  if  (  qwmLogEventToServ(  pQwm,  pEvent  )  )  
	{
		 if  (  qwmLogEventInReg(  pQwm,  pEvent  )  )  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 extern  "C"  int  getKeyValsCnt(  HKEY  hKeyRoot,  TCHAR  *  RegPath  )
{
	 HKEY   hKey  =  NULL;   
	 DWORD	dwcValues  =  0;
	 
	 if  (  !RegOpenKeyEx(	hKeyRoot,  RegPath,  0,  KEY_EXECUTE,  &hKey  )  )  {
		 if  (  RegQueryInfoKey(	hKey,				//  Key handle.  
									NULL,				//  ClassName,         // Buffer for class name.                    
									NULL,				//	&dwcClassLen,      // Length of class string.                    
									NULL,               //  Reserved.                    
									NULL,				//  &dwcSubKeys,       // Number of sub keys.                    
									NULL,				//  &dwcMaxSubKey,     // Longest sub key size.                    
									NULL,				//  &dwcMaxClass,      // Longest class string.                    
									&dwcValues,         //  Number of values for this key.                    
									NULL,				//  &dwcMaxValueName,  // Longest Value name.                    
									NULL,				//  &dwcMaxValueData,  // Longest Value data.                    
									NULL,				//  &dwcSecDesc,       // Security descriptor.                    
									NULL  )				//  &ftLastWriteTime	// Last write time.     
									)
		 {
			 dwcValues  =  0;
		 }
		 RegCloseKey(  hKey  );
	 }

	 return  dwcValues;

}

 extern  "C"  int  getKeyInfo(  HKEY  hKeyRoot,  TCHAR  *  RegPath,  DWORD  *  pdwcSubKeys,  DWORD  *  pdwcValues  )
{
	 int	iErr		=	-1;
	 HKEY   hKey		=	NULL;   
	 DWORD	dwcSubKeys	=	0;
	 DWORD	dwcValues	=	0;
	 
	 if  (  !RegOpenKeyEx(	hKeyRoot,  RegPath,  0,  KEY_EXECUTE,  &hKey  )  )  {
		 if  (  RegQueryInfoKey(	hKey,				//  Key handle.  
									NULL,				//  ClassName,         // Buffer for class name.                    
									NULL,				//	&dwcClassLen,      // Length of class string.                    
									NULL,               //  Reserved.                    
									&dwcSubKeys,		//  &dwcSubKeys,       // Number of sub keys.                    
									NULL,				//  &dwcMaxSubKey,     // Longest sub key size.                    
									NULL,				//  &dwcMaxClass,      // Longest class string.                    
									&dwcValues,	         //  Number of values for this key.                    
									NULL,				//  &dwcMaxValueName,  // Longest Value name.                    
									NULL,				//  &dwcMaxValueData,  // Longest Value data.                    
									NULL,				//  &dwcSecDesc,       // Security descriptor.                    
									NULL  )				//  &ftLastWriteTime	// Last write time.     
									)
		 {
			 dwcSubKeys  =  0;
			 dwcValues  =  0;
		 }
		 RegCloseKey(  hKey  );
	 }

	 iErr  =  0;

//  errLabel:
	 if  (  !iErr  )  {
		 if  (  pdwcSubKeys  )  *pdwcSubKeys  =  dwcSubKeys;
		 if  (  pdwcValues  )  *pdwcValues  =  dwcValues;
	 }
	 return  iErr;
}

//  #define		CONST_maxQwmRegLogs			100
 #define		CONST_maxQwmRegLogs			256		//  2007/02/18, 将日志容量放大了一些

 /*
 extern  "C"  int  qwmLogEventInReg(  void  *  pQwmParam,  QWM_EVENT  *  pEvent  )
{
	 int					iErr			=  -1;
	 QY_W_MON			*	pQwm			=  (  QY_W_MON  *  )pQwmParam;
	 QY_REG					tmpReg;
	 char					buf[2048];
	 int					pos;
	 HKEY					hKey			=  NULL;
	 int					dwcLogs;
	 
	 traceLogA(  "qwmLogEventInReg  enters."  );
	 
	 lstrcpy(  tmpReg.rootKey,  CONST_qyKey_qwmLog  );
	 tmpReg.pEncCtx  =  &pQwm->encCtx;

	 dwcLogs  =  getKeyValsCnt(  HKEY_LOCAL_MACHINE,  tmpReg.rootKey  );
	 
	 pos  =  0;
	 if  (  !qyGetRegCfg(  tmpReg.rootKey,  CONST_qwmLogPtr,  buf,  sizeof(  buf  )  )  )  {
		 pos  =  atol(  buf  );
		 dwcLogs  --  ;
	 }
	 if  (  pos  >  CONST_maxQwmRegLogs  &&  dwcLogs  <  1  )  {
		 qySetRegCfg(  tmpReg.rootKey,  CONST_qwmLogPtr,  "0"  );
		 pos  =  0;		 
	 }
	 if  (  dwcLogs  >  CONST_maxQwmRegLogs  )  {
		 traceLogA(  "本地存储日志不能超过%d条",  CONST_maxQwmRegLogs  );
		 goto  errLabel;
	 }

	 wsprintf(  buf,  "%s%d",  CONST_qwmLogPrefix,  pos  );
	 if  (  qySetRegDataEx(  &tmpReg,  buf,  (  char  *  )pEvent,  sizeof(  pEvent[0]  )  )  )  goto  errLabel;
	 pos  ++  ;
	 wsprintf(  buf,  "%d",  pos  );
	 if  (  qySetRegCfg(  tmpReg.rootKey,  CONST_qwmLogPtr,  buf  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 traceLogA(  "qwmLogEventInReg leaves, iErr is %s",  qyGetDesByType1(  CONST_qyRetTable,  iErr  )  );

	 return  iErr;

}
*/  

 extern  "C"  int  qwmLogEventInReg(  void  *  pQwmParam,  QWM_EVENT  *  pEvent  )
{
	 int					iErr			=  -1;
	 QY_W_MON			*	pQwm			=  (  QY_W_MON  *  )pQwmParam;
	 QY_REG					tmpReg;
	 TCHAR					buf[1024];
	 int					pos;
	 HKEY					hKey			=  NULL;
	 int					dwcLogs;
	 BOOL					bUsr			=	FALSE;
	 unsigned  int			len;
	 CQySyncObj				syncObj;

	 if  (  syncObj.sync(  pQwm->cfg.mutexName_syncLogEvent,  pQwm->cfg.ulMilliSeconds_syncLogEvent  )  )  goto  errLabel;

	 traceLogA(  "qwmLogEventInReg  enters."  );
	 
	 //  if  (  wcsicmp(  pQwm->wUsrName,  L"System"  )  )  bUsr  =  TRUE;
	 if  (  pQwm->cmd.ulbUsrScript  )  bUsr  =  TRUE;

	 memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
	 //
	 if  (  !bUsr  )  {
		 tmpReg.hKeyRoot0  =  HKEY_LOCAL_MACHINE;
		 lstrcpy(  tmpReg.rootKey,  _T(  CONST_qyKey_qwmLog  )  );
		}
	 else  {
		   tmpReg.hKeyRoot0  =  HKEY_CURRENT_USER;
		   lstrcpy(  tmpReg.rootKey,  _T(  CONST_qyKey_qwmLog_usr  )  );
	 }
	 
	 dwcLogs  =  getKeyValsCnt(  tmpReg.hKeyRoot0,  tmpReg.rootKey  );
	 
	 pos  =  0;
	 len  =  sizeof(  buf  );
	 if  (  !tmpGetRegCfgEx(  &tmpReg,  _T(  CONST_qwmLogPtr  ),  (  char  *  )buf,  &len  )  )  {
		 pos  =  _ttol(  buf  );
		 dwcLogs  --  ;
	 }
	 if  (  pos  >  CONST_maxQwmRegLogs  &&  dwcLogs  <  1  )  {
		 tmpSetRegCfgEx(  &tmpReg,  _T(  CONST_qwmLogPtr  ),  (  char  *  )_T(  "0"  ),  0  );
		 pos  =  0;		 
	 }
	 if  (  dwcLogs  >  CONST_maxQwmRegLogs  )  {
		 traceLogA(  "本地存储日志不能超过%d条",  CONST_maxQwmRegLogs  );
		 goto  errLabel;
	 }

	 tmpReg.pEncCtx  =  &pQwm->encCtx;
	 //
	 wsprintf(  buf,  _T(  "%s%d"  ),  _T(  CONST_qwmLogPrefix  ),  pos  );
	 if  (  qySetRegDataEx(  &tmpReg,  buf,  (  char  *  )pEvent,  sizeof(  pEvent[0]  )  )  )  goto  errLabel;
	 //
	 tmpReg.pEncCtx  =  0;
	 //
	 pos  ++  ;
	 wsprintf(  buf,  _T(  "%d"  ),  pos  );
	 if  (  tmpSetRegCfgEx(  &tmpReg,  _T(  CONST_qwmLogPtr  ),  (  char  *  )buf,  0  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 traceLogA(  "qwmLogEventInReg leaves, iErr is %s",  qyGetDesByType1(  CONST_qyRetTable,  iErr  )  );

	 return  iErr;

}


/*
 extern  "C"  int  qwmLogEventToServ(  void  *  pQwmParam,  QWM_EVENT  *  pEvent  )
{
	int						iErr			=  -1;
	QY_W_MON			*	pQwm			=  (  QY_W_MON  *  )pQwmParam;
	ASR_SOCK				aS;
	QWM_SESSION				session;
	BOOL					bSessionOpen	=	FALSE;
	QY_COMM_RESP			tmpResp;
	unsigned  int			len;
	QWM_EVENT				tmpEvent;
	
	traceLogA(  "qwmLogEventToServ enters. servIp is %s,  servPort is %d",  pQwm->server.ip,  pQwm->server.port  );

	//  取得MAC地址
	if  (  pQwm->macsInfo.nMacs  )  {
		clearQySock(  &aS  );
		memset(  &session,  0,  sizeof(  session  )  );

		if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
		bSessionOpen  =  TRUE;
		if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
		if  (  !bSeqNoCorrect(  pQwm,  session.servSeqNo,  pQwm->cfg.seqNo  )  )  {
			traceLogA(  "管理端序列号不符"  );  goto  errLabel;
		}

		memcpy(  &tmpEvent,  pEvent,  sizeof(  tmpEvent  )  );
		len  =  qyhtonQwmEvent(  &tmpEvent  );
		if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_sndLog,  (  char  *  )&tmpEvent,  len  )  )  goto  errLabel;
		if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  0,  0  )  )  goto  errLabel;

	}

	iErr  =  0;

errLabel:

	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );

	traceLogA(  "qwmLogEventToServ leaves,  iErr is %s",  qyGetDesByType1(  CONST_qyRetTable,  iErr  )  );

	return  iErr;

}
*/

 //  这一函数没有写完, 记得在RegEnumValue里，在RegDeleteValue调用后，位置指针立马发生变化
 //  但现在的程序还没有考虑这一点，需要确认。
 int  sndSavedTmpLog(  ASR_LOG_CONTEXT  *  pNull1,  char  *  pNull2  )
{
	 int					iErr			=		-1;
	 QY_REG					tmpReg;
	 DWORD					dwcVals			=		0;
	 DWORD					dwcPtrs			=		0;
	 TCHAR					buf[128];
	 HKEY					hKey			=		NULL;
	 BOOL					bKeyOpen		=		FALSE;
	 DWORD					j;   
	 DWORD					retValue;   
	 DWORD					dwcValueName;
	 TCHAR					valueName[256];
	 char					data[2048];
	 DWORD					cbData;
	 QWM_EVENT				event;
	 //
	 QY_W_MON			*	pQwm			=  &gQyWMon;
	 ASR_SOCK				aS;
	 QWM_SESSION			session;
	 BOOL					bSessionOpen	=	FALSE;
	 QY_COMM_RESP			tmpResp;
	 unsigned  int			len;
	 int					iSent			=	0;		//  发送日志的计数


	 traceLogA(  "sendSavedTmpLog enters"  );

#ifdef  __DEBUG__
		printRegLogs(  );
#endif
	 
	 memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
	 //
	 lstrcpyn(  tmpReg.rootKey,  _T(  CONST_qyKey_qwmLog  ),  mycountof(  tmpReg.rootKey  )  );
	 tmpReg.pEncCtx  =  &gQyWMon.encCtx;
	 
	 dwcVals  =  getKeyValsCnt(  HKEY_LOCAL_MACHINE,  tmpReg.rootKey  );
	 if  (  !qyGetRegCfg(  tmpReg.rootKey,  _T(  CONST_qwmLogPtr  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		 dwcPtrs  ++  ;
	 }
	 if  (  dwcVals  <=  dwcPtrs  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  !pQwm->macsInfo.nMacs  )  goto  errLabel;
	 clearQySock(  &aS  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
	 bSessionOpen  =  TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	 if  (  !bSeqNoCorrect(  pQwm,  session.servSeqNo,  pQwm->cfg.seqNo  )  )  {
		 traceLogA(  "管理端序列号不符"  );  goto  errLabel;
	 }
	 
	 
	 if  (  ERROR_SUCCESS  !=  RegOpenKey(  HKEY_LOCAL_MACHINE,  tmpReg.rootKey,  &hKey  )  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 //  注意这里，由dwcVals来控制循环次数，而j来指向将读取的记录
	 for  (  j  =  0;  dwcVals ;  dwcVals  --  )  {
		  dwcValueName  =  sizeof(  valueName  );        
		  valueName[0] = '\0';
		  cbData  =  sizeof(  data  );
		  data[0]  =  0;
		  retValue  =  RegEnumValue(  hKey,  j,  valueName,  
									  &dwcValueName,  
									  NULL,  
									  NULL,			//  &dwType,         
			  						  NULL,			//  data, 
									  NULL  );		//  &cbData  );    
		  if  (  retValue  !=  (  DWORD  )ERROR_SUCCESS  )  break;
		  
		  if  (  !lstrcmpi(  valueName,  _T(  CONST_qwmLogPtr  )  )  )  { 
			  j  ++  ;continue;
		  }
		  if  (  qyGetRegDataEx(  &tmpReg,  valueName,  data,  &cbData  )  )  {
			  RegDeleteValue(  hKey,  valueName  );
			  continue;
		  }

		  memset(  &event,  0,  sizeof(  event  )  );
		  memcpy(  &event,  data,  min(  sizeof(  event  ),  cbData  )  );

		  //  2006/03/23, 将event.comments[]转化为utf8,			//  032006起做以下改动
		  switch  (  event.eventType  )  {
			   	  case  CONST_qyEventType_nm_rasStart:
			 	  case  CONST_qyEventType_nm_rasEnd:
			 	  case  CONST_qyEventType_nm_rasProhibited:
					    break;
				  default:
						  if  (  !event.ucbUtf8  )  myStr2Utf8(  event.u.comments[0],  sizeof(  event.u.comments[0]  )  );
						  if  (  !event.ucbUtf8  )  myStr2Utf8(  event.u.comments[1],  sizeof(  event.u.comments[1]  )  );
						  event.ucbUtf8  =  TRUE;
						  break;
		  }


		  //  下面将日志发往管理端
		  //  if  (  qwmLogEventToServ(  &gQyWMon,  &event  )  )  goto  errLabel;
		  len  =  qyhtonQwmEvent(  &event  );
		  if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_sndLog,  (  char  *  )&event,  len  )  )  goto  errLabel;
		  if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  0,  0  )  )  goto  errLabel;

		  //  发完后，将日志清除
		  RegDeleteValue(  hKey,  valueName  );		  

		  iSent  ++  ;  if  (  iSent  >=  50  )  break;		//  2005/10/04,  对一次性发送的日志有限制，以使有时间去下载配置

	 }

	 traceLogA(  "sendSavedTmpLog 发送日志成功"  );

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );

	 traceLogA(  "sendSavedTmpLog leaves"  );

	 return  0;

}



 //////////////////////////////////////////////////////////


 /*
 extern  "C"  int  qwmOpenSession(  void  *  pQwmParam,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock  )
{
	 int					iErr			=  -1;
	 QY_W_MON			*	pQwm			=  (  QY_W_MON  *  )pQwmParam;
	 char					ip[16];
	 QNM_COMM_AUTHINFO		authInfo;
	 QY_COMM_RESP			tmpResp;

	 if  (  !pQwm->macsInfo.nMacs  )  return  -1;
	 if  (  !bQySockOpen(  pSock  )  )  {		//  如果前面已建立连接，则不需要建立新连接
		 if  (  asrConnect(  pQwm->server.ip,  pQwm->server.port,  pQwm->cfg.to.iConnect,  pSock  )  )  goto  errLabel;
	 }
	 if  (  getLocalIpBySocket(  pSock->sockFd,  ip  )  )  goto  errLabel;
	 memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	 if  (  makeQwmAuthInfo(  pQwm->ver,  &pQwm->macsInfo,  &authInfo  )  )  goto  errLabel;
	 memcpy(  authInfo.ip,  ip,  sizeof(  authInfo.ip  )  );

	 if  (  qyTellService(  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  (  char  *  )&authInfo,  sizeof(  authInfo  ),  pSock,  &pQwm->cfg.to,  &pSession->comm  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 //  traceLogA(  "qwmOpenSession: get respCode of qyTellService is %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );
	 if  (  isRcQuit(  tmpResp.head.usCode  )  )  {
		 traceLogA(  "qwmOpenSession:  得到卸载命令"  );
		 pQwm->cfg.ucbStopMon  =  TRUE;  goto  errLabel;		//  程序退出，删除执行路径run , runservices
	 }

	 iErr  =  0;

errLabel:
	 
	 if  (  iErr  )  {
		 if  (  bQySockOpen(  pSock  )  )  qyDisconnect(  pSock  );
	 }

	 return  iErr;
}
*/

 BOOL  bSeqNoCorrect(  void  *  p0,  char  *  servSeqNo,  char  *  qwmSeqNo  )
{
	 return  !strnicmp(  servSeqNo,  qwmSeqNo,  strlen(  qwmSeqNo  )  );
}

 extern  "C"  int  qwmOpenSession(  void  *  pQwmParam,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock  )
{
	 int					iErr			=	-1;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pQwmParam;
	 QY_COMM_SERVICERESP	serviceResp;
	 unsigned  int			len;

	 len  =  sizeof(  serviceResp  );
	 if  (  qnmOpenSession(  pQwm->server.ip,  pQwm->server.port,  &pQwm->macsInfo,  0,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pSession->comm,  pSock,  &pQwm->cfg.to,  (  char  *  )&serviceResp,  &len  )  )  goto  errLabel;
	 qyntohCommServiceResp(  &serviceResp  );
	 if  (  serviceResp.uiType  ==  CONST_serviceRespType_serv  )  {
		 traceLogA(  "得到管理端的序列号为[%s]",  serviceResp.u.serv.seqNo  );
		 safeStrnCpy(  serviceResp.u.serv.seqNo,  pSession->servSeqNo,  sizeof(  pSession->servSeqNo  )  );
	 }
	 if  (  bSeqNoCorrect(  pQwm,  pSession->servSeqNo,  pQwm->cfg.seqNo  )  )  {
		 if  (  isRcQuit(  pSession->comm.usLastRespCode_i  )  )  {
			 traceLogA(  "qwmOpenSession:  得到卸载命令"  );
			 pQwm->cfg.ucbStopMon  =  TRUE;  goto  errLabel;		//  程序退出，删除执行路径run , runservices
		 }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 extern  "C"  void  qwmCloseSession(  void  *  pQwmParam,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock  )
{
	 QY_W_MON			*	pQwm			=  (  QY_W_MON  *  )pQwmParam;

	 qnmCloseSession(  &pSession->comm,  pSock,  &pQwm->cfg.to  );

	 return;
}


 int  cfgQwmServIp(  QY_W_MON  *  pQwm,  QY_LOGICAL_SERVER  *  pCnt  )
{
	int		iRet			=	-1;
	QY_REG	reg;
	TCHAR	tBuf[128];

	if  (  !pQwm  )  goto  errLabel;

	traceLogA(  "cfgAsrWMon( ): server ip is %s",  pCnt->ip  );

	memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
	lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  reg.rootKey  )  );
	reg.pEncCtx  =  &pQwm->encCtx;
	myUtf82TChar(  pCnt->ip,  tBuf,  mycountof(  tBuf  )  );
	if  (  qySetRegCfgEx(  &reg,  _T(  CONST_qwmCfgName_cntIp  ),  tBuf  )  )  goto  errLabel;

	iRet  =  0;
errLabel:
	return  iRet;

}
 
 int  getQwmServIpCfg(  QY_W_MON  *  pQwm,  QY_LOGICAL_SERVER  *  pCnt  )
{
	 int				iErr		=	-1;
	 QY_REG				reg;
	 TCHAR				buf[256]	=	_T(  ""  );

	 if  (  !pCnt  )  return  -1;

	 memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pQwm->encCtx;
	 if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_qwmCfgName_cntIp  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		 char  ipBuf[128];
		 myTChar2Utf8(  buf,  ipBuf,  mycountof(  ipBuf  )  );
		 if  (  stricmp(  pCnt->ip,  ipBuf  )  )  {
			 traceLogA(  "getQwmServIpCfg(  ): Oh, cntIp is changed to [%s]",  ipBuf  );
			 safeStrnCpy(  ipBuf,  pCnt->ip,  sizeof(  pCnt->ip  )  );
		 }
	 }
	 /*
	 if  (  !qyGetRegCfgEx(  &reg,  CONST_qwmCfgName_cntPort,  buf,  sizeof(  buf  )  )  )  {
		 pCnt->port  =  (  unsigned  short  )atol(  buf  );
	 }
	 */

	 iErr  =  0;
//  errLabel:
	 return  iErr;
}


 int  requestQwmToQuit(  QY_W_MON  *  pQwm  )
{
	 int				iErr			=	-1;
	 QY_REG				reg;
	 char				cfgVal[512];
	 unsigned  long		len;
	 unsigned  long		ulRand;

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 lstrcpy(  reg.rootKey,  _T(  CONST_qyKey_qwm  )  );
	 reg.pEncCtx  =  &pQwm->encCtx;

	 len  =  sizeof(  ulRand  );
	 if  (  !qyGetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_rand  ),  (  char  *  )&ulRand,  &len  )  )  {

		 reg.pEncCtx  =  &pQwm->quitEncCtx;
	 	 len  =  sizeof(  cfgVal  );
		 //	
		 memcpy(  cfgVal,  &ulRand,  sizeof(  ulRand  )  );
		 //
		 traceLogA(  "先输出序列号"  );	//  2005/0625
		 safeStrnCpy(  pQwm->cfg.seqNo,  cfgVal  +  sizeof(  ulRand  ),  sizeof(  cfgVal  )  -  sizeof(  ulRand  )  );	//  2005/06/25
		 len  =  sizeof(  ulRand  )  +  strlen(  pQwm->cfg.seqNo  );
		 if  (  qySetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_qwmSeqNo  ),  cfgVal,  len  )  )  goto  errLabel;
		 //
		 strcpy(  cfgVal  +  sizeof(  ulRand  ),  CONST_qwmCfgVal_cmdQuit  );
		 len  =  sizeof(  ulRand  )  +  strlen(  CONST_qwmCfgVal_cmdQuit  );
		 if  (  qySetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_cmdQuit  ),  cfgVal,  len  )  )  goto  errLabel;
		 
	 }


	 traceLogA(  "设置让所有的qwmSvr相关的对象退出的标志位"  );
	 setQwmUsrScriptQuit(  TRUE  );		//  2007/01/15

	 iErr  =  0;

errLabel:

	 return  iErr;
	
}

#if  0
 int  cfgQwmItem(  QY_W_MON  *  pQwm,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int					iErr	=	-1;
	 QY_REG					reg;
	 QY_CFGITEM_LONG	*	pLong	=	NULL;
	 QY_CFGITEM_STR		*	pStr	=	NULL;
	 
	 switch  (  pItem->dataType  )  {
			 case  CONST_qyDataType_long:
				   pLong  =  (  QY_CFGITEM_LONG  *  )pItem;
				   break;
			 case  CONST_qyDataType_str:
				   pStr  =  (  QY_CFGITEM_STR  *  )pItem;
				   break;
			 default:
					goto  errLabel;
	 }

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ), mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pQwm->encCtx;

	 switch  (  pItem->cfgId  )  {
			 case  CONST_qnmCfgId_connectIntervalLoops:
				   MACRO_qyAssert(  pLong,  _T(  "cfgQwmItem"  )  );
				   pQwm->cfg.usConnectIntervalLoops  =  max(  (  unsigned  short  )pLong->ulVal,  3  );		//  2005/05/09, 加上了一个最快的限制，防止过速占带宽
				   break;
			 case  CONST_qnmCfgId_intervals:  {
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   QNM_INTERVAL_PARAMS	*	pIntervalParams  =  (  QNM_INTERVAL_PARAMS  *  )pStr->str;
				   unsigned  short			usLoops;
				   MACRO_ntohs(  pIntervalParams->usGetCfgInterval  );
				   MACRO_ntohs(  pIntervalParams->usShowPcNetworkInterval  );
				   MACRO_ntohs(  pIntervalParams->usSndEventLogInterval  );
				   MACRO_ntohs(  pIntervalParams->usSndUsrInfoInterval  );
				   MACRO_ntohs(  pIntervalParams->usSndNetStatInterval  );
				   MACRO_ntohs(  pIntervalParams->usShowProcessInterval  );
				   MACRO_ntohs(  pIntervalParams->usGetOpCmdInterval  );
				   MACRO_ntohs(  pIntervalParams->usShowModulesInterval  );					//  2006/04/14
				   MACRO_ntohs(  pIntervalParams->usShowWindowsUpdatePolicyInterval  );		//  2006/05/24
				   MACRO_ntohs(  pIntervalParams->usQueryCfgsInterval  );					//  2006/08/15
				   MACRO_ntohs(  pIntervalParams->usShowNetFlowInterval  );					//  2006/09/12
				   MACRO_ntohs(  pIntervalParams->usSndPrintersInterval  );					//  2006/12/10
				   MACRO_ntohs(  pIntervalParams->usShowPcNetShareInterval  );				//  2007/02/14
				   MACRO_ntohs(  pIntervalParams->usShowPcArpInterval  );						//  2007/021/4
				   //
				   usLoops  =  pIntervalParams->usGetCfgInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usConnectIntervalLoops  )  pQwm->cfg.usConnectIntervalLoops  = max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowPcNetworkInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcNetworkPropIntervalLoops  )  pQwm->cfg.usShowPcNetworkPropIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usSndEventLogInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndEventLogIntervalLoops  )  pQwm->cfg.usSndEventLogIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usSndUsrInfoInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndUsrInfoIntervalLoops  )  pQwm->cfg.usSndUsrInfoIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usSndNetStatInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndNetStatIntervalLoops  )  pQwm->cfg.usSndNetStatIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usShowProcessInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowProcessIntervalLoops  )  pQwm->cfg.usShowProcessIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usGetOpCmdInterval  /  2;					//  2006/02/11
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usGetOpCmdIntervalLoops  )  pQwm->cfg.usGetOpCmdIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowModulesInterval  /  2;				//  2006/04/14
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowModulesIntervalLoops  )  pQwm->cfg.usShowModulesIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowWindowsUpdatePolicyInterval  /  2;	//  2006/05/24
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcWindowsUpdatePolicyIntervalLoops  )  pQwm->cfg.usShowPcWindowsUpdatePolicyIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usQueryCfgsInterval  /  2;					//  2006/08/15
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usQueryCfgsIntervalLoops  )  pQwm->cfg.usQueryCfgsIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowNetFlowInterval  /  2;					//  2006/09/12
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcNetFlowIntervalLoops  )  pQwm->cfg.usShowPcNetFlowIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usSndPrintersInterval  /  2;					//  2006/12/10
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndPrintersIntervalLoops  )  pQwm->cfg.usSndPrintersIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowPcNetShareInterval  /  2;					//  2007/02/14
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcNetShareIntervalLoops  )  pQwm->cfg.usShowPcNetShareIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowPcArpInterval  /  2;						//  2007/02/14
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcArpIntervalLoops  )  pQwm->cfg.usShowPcArpIntervalLoops  =  max(  usLoops,  3  );
				   

				   }				   
				   break;
			 //  case  CONST_qnmCfgId_rasCmd:
			 //	   MACRO_qyAssert(  pLong,  "cfgQwmItem"  );
			 //	   
			 //	   if  (  pLong->ulVal  ==  (  unsigned  long  )CONST_rasCmd_permitted  )  
			 //		   qySetRegCfg(  ROOT_KEY_AWM,  AWM_LEVEL_KEY,  ASR_CMD_STR_RAS_PERMITTED  );						
			 //	   else  qySetRegCfg(  ROOT_KEY_AWM,  AWM_LEVEL_KEY,  ASR_CMD_STR_RAS_PROHIBITED  );
			 //	   
			 //	   break;
			 case  CONST_qnmCfgId_rasRule:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {				   
					   QNM_RAS_RULE	*	pRasRule  =  (  QNM_RAS_RULE  *  )pStr->str;
					   
					   if  (  memcmp(  &pQwm->cfg.pcRules.ras,  pRasRule,  sizeof(  pQwm->cfg.pcRules.ras  )  )  )
					   	   qySetRegDataEx(  &reg,  _T(  CONST_regValName_rasRule  ),  (  char  *  )pRasRule,  sizeof(  pRasRule[0]  )  );
				   }
				   break;	
			 case  CONST_qnmCfgId_devRule:		//  2005/01/05
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QNM_DEV_RULE  *  pDevRule  =  (  QNM_DEV_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.pcRules.dev,  pDevRule,  sizeof(  pQwm->cfg.pcRules.dev  )  )  )  
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_devRule  ),  (  char  *  )pDevRule,  sizeof(  pDevRule[0]  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_osRule:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QNM_OS_RULE  *  pOsRule  =  (  QNM_OS_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.pcRules.os,  pOsRule,  sizeof(  pQwm->cfg.pcRules.os  )  )  )
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_osRule  ),  (  char  *  )pOsRule,  sizeof(  pOsRule[0]  )  );
				   }				   
				   break;
			 case  CONST_qnmCfgId_osAuditRule:				//  2005/08/30
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QNM_OSAUDIT_RULE	*	pOsAuditRule  =  (  QNM_OSAUDIT_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.pcRules.osAudit,  pOsAuditRule,  sizeof(  pQwm->cfg.pcRules.osAudit  )  )  )  {
						   //  memcpy(  &pQwm->cfg.pcRules.osAudit,  pOsAuditRule,  sizeof(  pQwm->cfg.pcRules.osAudit  )  );
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_osAuditRule  ),  (  char  *  )pOsAuditRule,  sizeof(  pOsAuditRule[0]  )  );
					   }
				   }
				   break;
			 case  CONST_qnmCfgId_interMon:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QY_LOGICAL_SERVER	*	pInterMon	=	(  QY_LOGICAL_SERVER  *  )pStr->str;
					   MACRO_ntohs(  pInterMon->port  );

					   if  (  memcmp(  &pQwm->cfg.interMon,  pInterMon,  sizeof(  pQwm->cfg.interMon  )  )  )
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_interMon  ),  (  char  *  )pInterMon,  sizeof(  pInterMon[0]  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_stopMon:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_STOPMON_RULE	*	pStopMonRule  =  (  QNM_STOPMON_RULE  *  )pStr->str;

					   if  (  pStopMonRule->ucbStopped   )  {  
						   traceLogA(  "cfgQwmItem:  得到卸载命令"  );
						   pQwm->cfg.ucbStopMon  =  TRUE;
					   }
				   }
				   break;
			 case  CONST_qnmCfgId_secChk:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_SECCHK_RULE  *  pSecChkRule  =  (  QNM_SECCHK_RULE  *  )pStr->str;
				
					   //  if  (  pSecChkRule->ucbDoSecChk  )  {
					   //	   traceLogA(  "cfgQwmItem: 得到安检命令"  );
					   //	   pQwm->cfg.pcRules.secChk.ucbDoSecChk  =  TRUE;
					   //  }

					   //  2005/05/09修改
					   if  (  pQwm->cfg.pcRules.secChk.ucbDoSecChk  !=  pSecChkRule->ucbDoSecChk  )  pQwm->cfg.pcRules.secChk.ucbDoSecChk  =  pSecChkRule->ucbDoSecChk;
				   }
				   break;
			 case  CONST_qnmCfgId_opRule:	//  2006/02/11
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_PCOP_RULE	*	pOpRule  =  (  QNM_PCOP_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.opRule,  pOpRule,  sizeof(  pQwm->cfg.opRule  )  )  )  memcpy(  &pQwm->cfg.opRule,  pOpRule,  sizeof(  pQwm->cfg.opRule  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_pcMon:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_PCMON_RULE	*	pRule  =  (  QNM_PCMON_RULE  *  )pStr->str;
					   MACRO_ntohs(  pRule->usCapScreenInterval  );  if  (  pRule->usCapScreenInterval  <  5  )  pRule->usCapScreenInterval  =  5;
					   if  (  memcmp(  &pQwm->cfg.pcRules.pcMon,  pRule,  sizeof(  pQwm->cfg.pcRules.pcMon  )  )  )  qySetRegDataEx(  &reg,  _T(  CONST_regValName_pcMonRule  ),  (  char  *  )pRule,  sizeof(  pRule[0]  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_pcNetFlow:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );			//  2006/09/11
				   {
					 QNM_PCNETFLOW_RULE	*	pRule  =  (  QNM_PCNETFLOW_RULE  *  )pStr->str;
					 MACRO_ntohl(  pRule->uiWarnPercentOfBandWithFactor  );
					 MACRO_ntohs(  pRule->usStopNetworkCardTimeInSecond  );
					 if  (  pRule->uiWarnPercentOfBandWithFactor  >  99999  )  pRule->uiWarnPercentOfBandWithFactor  =  0;
					 if  (  pRule->usStopNetworkCardTimeInSecond  >  MAX_usStopNetworkCardTimeInSecond  )  pRule->usStopNetworkCardTimeInSecond  =  0;
					 if  (  memcmp(  &pQwm->cfg.pcRules.pcNetFlow,  pRule,  sizeof(  pQwm->cfg.pcRules.pcNetFlow  )  )  )  memcpy(  &pQwm->cfg.pcRules.pcNetFlow,  pRule,  sizeof(  pQwm->cfg.pcRules.pcNetFlow  )  );
				   }
				   break;
			 default:
				     traceLogA(  "cfgQwmItem,  unknown  cfgId %d",  pItem->cfgId  );
				     goto  errLabel;
	 }
	
	 iErr  =  0;

errLabel:

	 return  iErr;

}
#endif

 int  cfgQwmItem(  QY_W_MON  *  pQwm,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int					iErr	=	-1;
	 QY_REG					reg;
	 QY_CFGITEM_LONG	*	pLong	=	NULL;
	 QY_CFGITEM_STR			itemStr;
	 QY_CFGITEM_STR		*	pStr	=	NULL;
	 
	 switch  (  pItem->head.dataType  )  {
			 case  CONST_qyDataType_long:
				   pLong  =  &pItem->l;
				   break;
			 case  CONST_qyDataType_str:
				   //  pStr  =  (  QY_CFGITEM_STR  *  )pItem;
				   memset(  &itemStr,  0,  sizeof(  itemStr  )  );
				   //  safeStrnCpy(  pItem->data.p,  itemStr.str,  mycountof(  itemStr.str  )  );
				   itemStr.cfgId  =  pItem->data.cfgId;
				   itemStr.dataType  =  pItem->data.dataType;
				   itemStr.len  =  min(  sizeof(  itemStr.str  ),  pItem->data.len  );
				   if  (  pItem->data.p  )  memcpy(  itemStr.str,  pItem->data.p,  itemStr.len  );
				   if  (  itemStr.len  <  sizeof(  itemStr.str  )  )  itemStr.str[itemStr.len]  =  0;
				   pStr  =  &itemStr;
				   break;
			 default:
					goto  errLabel;
	 }

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ), mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pQwm->encCtx;

	 switch  (  pItem->head.cfgId  )  {
			 case  CONST_qnmCfgId_connectIntervalLoops:
				   MACRO_qyAssert(  pLong,  _T(  "cfgQwmItem"  )  );
				   pQwm->cfg.usConnectIntervalLoops  =  max(  (  unsigned  short  )pLong->ulVal,  3  );		//  2005/05/09, 加上了一个最快的限制，防止过速占带宽
				   break;
			 case  CONST_qnmCfgId_intervals:  {
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   QNM_INTERVAL_PARAMS	*	pIntervalParams  =  (  QNM_INTERVAL_PARAMS  *  )pStr->str;
				   unsigned  short			usLoops;
				   MACRO_ntohs(  pIntervalParams->usGetCfgInterval  );
				   MACRO_ntohs(  pIntervalParams->usShowPcNetworkInterval  );
				   MACRO_ntohs(  pIntervalParams->usSndEventLogInterval  );
				   MACRO_ntohs(  pIntervalParams->usSndUsrInfoInterval  );
				   MACRO_ntohs(  pIntervalParams->usSndNetStatInterval  );
				   MACRO_ntohs(  pIntervalParams->usShowProcessInterval  );
				   MACRO_ntohs(  pIntervalParams->usGetOpCmdInterval  );
				   MACRO_ntohs(  pIntervalParams->usShowModulesInterval  );					//  2006/04/14
				   MACRO_ntohs(  pIntervalParams->usShowWindowsUpdatePolicyInterval  );		//  2006/05/24
				   MACRO_ntohs(  pIntervalParams->usQueryCfgsInterval  );					//  2006/08/15
				   MACRO_ntohs(  pIntervalParams->usShowNetFlowInterval  );					//  2006/09/12
				   MACRO_ntohs(  pIntervalParams->usSndPrintersInterval  );					//  2006/12/10
				   MACRO_ntohs(  pIntervalParams->usShowPcNetShareInterval  );				//  2007/02/14
				   MACRO_ntohs(  pIntervalParams->usShowPcArpInterval  );						//  2007/021/4
				   //
				   usLoops  =  pIntervalParams->usGetCfgInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usConnectIntervalLoops  )  pQwm->cfg.usConnectIntervalLoops  = max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowPcNetworkInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcNetworkPropIntervalLoops  )  pQwm->cfg.usShowPcNetworkPropIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usSndEventLogInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndEventLogIntervalLoops  )  pQwm->cfg.usSndEventLogIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usSndUsrInfoInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndUsrInfoIntervalLoops  )  pQwm->cfg.usSndUsrInfoIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usSndNetStatInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndNetStatIntervalLoops  )  pQwm->cfg.usSndNetStatIntervalLoops  =  max(  usLoops,  3  );				   
				   usLoops  =  pIntervalParams->usShowProcessInterval  /  2;
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowProcessIntervalLoops  )  pQwm->cfg.usShowProcessIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usGetOpCmdInterval  /  2;					//  2006/02/11
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usGetOpCmdIntervalLoops  )  pQwm->cfg.usGetOpCmdIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowModulesInterval  /  2;				//  2006/04/14
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowModulesIntervalLoops  )  pQwm->cfg.usShowModulesIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowWindowsUpdatePolicyInterval  /  2;	//  2006/05/24
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcWindowsUpdatePolicyIntervalLoops  )  pQwm->cfg.usShowPcWindowsUpdatePolicyIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usQueryCfgsInterval  /  2;					//  2006/08/15
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usQueryCfgsIntervalLoops  )  pQwm->cfg.usQueryCfgsIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowNetFlowInterval  /  2;					//  2006/09/12
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcNetFlowIntervalLoops  )  pQwm->cfg.usShowPcNetFlowIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usSndPrintersInterval  /  2;					//  2006/12/10
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usSndPrintersIntervalLoops  )  pQwm->cfg.usSndPrintersIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowPcNetShareInterval  /  2;					//  2007/02/14
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcNetShareIntervalLoops  )  pQwm->cfg.usShowPcNetShareIntervalLoops  =  max(  usLoops,  3  );
				   usLoops  =  pIntervalParams->usShowPcArpInterval  /  2;						//  2007/02/14
				   if  (  usLoops  &&  usLoops  !=  pQwm->cfg.usShowPcArpIntervalLoops  )  pQwm->cfg.usShowPcArpIntervalLoops  =  max(  usLoops,  3  );
				   

				   }				   
				   break;
			 //  case  CONST_qnmCfgId_rasCmd:
			 //	   MACRO_qyAssert(  pLong,  "cfgQwmItem"  );
			 //	   
			 //	   if  (  pLong->ulVal  ==  (  unsigned  long  )CONST_rasCmd_permitted  )  
			 //		   qySetRegCfg(  ROOT_KEY_AWM,  AWM_LEVEL_KEY,  ASR_CMD_STR_RAS_PERMITTED  );						
			 //	   else  qySetRegCfg(  ROOT_KEY_AWM,  AWM_LEVEL_KEY,  ASR_CMD_STR_RAS_PROHIBITED  );
			 //	   
			 //	   break;
			 case  CONST_qnmCfgId_rasRule:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {				   
					   QNM_RAS_RULE	*	pRasRule  =  (  QNM_RAS_RULE  *  )pStr->str;
					   
					   if  (  memcmp(  &pQwm->cfg.pcRules.ras,  pRasRule,  sizeof(  pQwm->cfg.pcRules.ras  )  )  )
					   	   qySetRegDataEx(  &reg,  _T(  CONST_regValName_rasRule  ),  (  char  *  )pRasRule,  sizeof(  pRasRule[0]  )  );
				   }
				   break;	
			 case  CONST_qnmCfgId_devRule:		//  2005/01/05
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QNM_DEV_RULE  *  pDevRule  =  (  QNM_DEV_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.pcRules.dev,  pDevRule,  sizeof(  pQwm->cfg.pcRules.dev  )  )  )  
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_devRule  ),  (  char  *  )pDevRule,  sizeof(  pDevRule[0]  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_osRule:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QNM_OS_RULE  *  pOsRule  =  (  QNM_OS_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.pcRules.os,  pOsRule,  sizeof(  pQwm->cfg.pcRules.os  )  )  )
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_osRule  ),  (  char  *  )pOsRule,  sizeof(  pOsRule[0]  )  );
				   }				   
				   break;
			 case  CONST_qnmCfgId_osAuditRule:				//  2005/08/30
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QNM_OSAUDIT_RULE	*	pOsAuditRule  =  (  QNM_OSAUDIT_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.pcRules.osAudit,  pOsAuditRule,  sizeof(  pQwm->cfg.pcRules.osAudit  )  )  )  {
						   //  memcpy(  &pQwm->cfg.pcRules.osAudit,  pOsAuditRule,  sizeof(  pQwm->cfg.pcRules.osAudit  )  );
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_osAuditRule  ),  (  char  *  )pOsAuditRule,  sizeof(  pOsAuditRule[0]  )  );
					   }
				   }
				   break;
			 case  CONST_qnmCfgId_interMon:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQnmItem"  )  );
				   {
					   QY_LOGICAL_SERVER	*	pInterMon	=	(  QY_LOGICAL_SERVER  *  )pStr->str;
					   MACRO_ntohs(  pInterMon->port  );

					   if  (  memcmp(  &pQwm->cfg.interMon,  pInterMon,  sizeof(  pQwm->cfg.interMon  )  )  )
						   qySetRegDataEx(  &reg,  _T(  CONST_regValName_interMon  ),  (  char  *  )pInterMon,  sizeof(  pInterMon[0]  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_stopMon:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_STOPMON_RULE	*	pStopMonRule  =  (  QNM_STOPMON_RULE  *  )pStr->str;

					   if  (  pStopMonRule->ucbStopped   )  {  
						   traceLogA(  "cfgQwmItem:  得到卸载命令"  );
						   pQwm->cfg.ucbStopMon  =  TRUE;
					   }
				   }
				   break;
			 case  CONST_qnmCfgId_secChk:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_SECCHK_RULE  *  pSecChkRule  =  (  QNM_SECCHK_RULE  *  )pStr->str;
				
					   //  if  (  pSecChkRule->ucbDoSecChk  )  {
					   //	   traceLogA(  "cfgQwmItem: 得到安检命令"  );
					   //	   pQwm->cfg.pcRules.secChk.ucbDoSecChk  =  TRUE;
					   //  }

					   //  2005/05/09修改
					   if  (  pQwm->cfg.pcRules.secChk.ucbDoSecChk  !=  pSecChkRule->ucbDoSecChk  )  pQwm->cfg.pcRules.secChk.ucbDoSecChk  =  pSecChkRule->ucbDoSecChk;
				   }
				   break;
			 case  CONST_qnmCfgId_opRule:	//  2006/02/11
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_PCOP_RULE	*	pOpRule  =  (  QNM_PCOP_RULE  *  )pStr->str;
					   if  (  memcmp(  &pQwm->cfg.opRule,  pOpRule,  sizeof(  pQwm->cfg.opRule  )  )  )  memcpy(  &pQwm->cfg.opRule,  pOpRule,  sizeof(  pQwm->cfg.opRule  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_pcMon:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );
				   {
					   QNM_PCMON_RULE	*	pRule  =  (  QNM_PCMON_RULE  *  )pStr->str;
					   MACRO_ntohs(  pRule->usCapScreenInterval  );  if  (  pRule->usCapScreenInterval  <  5  )  pRule->usCapScreenInterval  =  5;
					   if  (  memcmp(  &pQwm->cfg.pcRules.pcMon,  pRule,  sizeof(  pQwm->cfg.pcRules.pcMon  )  )  )  qySetRegDataEx(  &reg,  _T(  CONST_regValName_pcMonRule  ),  (  char  *  )pRule,  sizeof(  pRule[0]  )  );
				   }
				   break;
			 case  CONST_qnmCfgId_pcNetFlow:
				   MACRO_qyAssert(  pStr,  _T(  "cfgQwmItem"  )  );			//  2006/09/11
				   {
					 QNM_PCNETFLOW_RULE	*	pRule  =  (  QNM_PCNETFLOW_RULE  *  )pStr->str;
					 MACRO_ntohl(  pRule->uiWarnPercentOfBandWithFactor  );
					 MACRO_ntohs(  pRule->usStopNetworkCardTimeInSecond  );
					 if  (  pRule->uiWarnPercentOfBandWithFactor  >  99999  )  pRule->uiWarnPercentOfBandWithFactor  =  0;
					 if  (  pRule->usStopNetworkCardTimeInSecond  >  MAX_usStopNetworkCardTimeInSecond  )  pRule->usStopNetworkCardTimeInSecond  =  0;
					 if  (  memcmp(  &pQwm->cfg.pcRules.pcNetFlow,  pRule,  sizeof(  pQwm->cfg.pcRules.pcNetFlow  )  )  )  memcpy(  &pQwm->cfg.pcRules.pcNetFlow,  pRule,  sizeof(  pQwm->cfg.pcRules.pcNetFlow  )  );
				   }
				   break;
			 default:
				     traceLogA(  "cfgQwmItem,  unknown  cfgId %d",  pItem->head.cfgId  );
				     goto  errLabel;
	 }
	
	 iErr  =  0;

errLabel:

	 return  iErr;

}



 int  retrieveQwmGlCntIp(  QY_W_MON  *  pQwm  )
{
	int						iErr		=		-1;
	/*
	ASR_SOCK				aS;
	int						i			=		0;
	QWM_SESSION				session;  
	BOOL  					bSessionOpen  =  FALSE;
	char					cfgsBuf[8192];
	QY_LOGICAL_SERVER		realCnt;

	//  traceLogA(  "enter retrieveQwmglCntIp."  );

	//  取得MAC地址
	if  (  !pQwm->macsInfo.nMacs  )  getQwmMacs(  &pQwm->macsInfo  );
	
	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
		
	if  (  !qyConnect(  pQwm->cfg.cnt.ip,  pQwm->cfg.cnt.port,  &aS,  pQwm->cfg.to.iConnect  )  )  {
		memcpy(  &realCnt,  &pQwm->cfg.cnt,  sizeof(  realCnt  )  );
		}
	else
		goto  errLabel;
	

	if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
	bSessionOpen  =  TRUE;
	if  (  isRcRedirect(  session.comm.usLastReqCode  )  )  {
		QY_CFGITEM_STR  *  pItem  =  (  QY_CFGITEM_STR  *  )cfgsBuf;
		
		if  (  !qyntohCfgItem(  (  QY_CFGITEM  *  )pItem  )  )  goto  errLabel;
		traceLogA(  "pItem->str is [%s]",  pItem->str  );
		if  (  lstrlen(  pItem->str  )  >  CONST_qyMaxIpLen  ||  inet_addr(  pItem->str  )  ==  INADDR_NONE  )  goto  errLabel;
		if  (  lstrcmp(  pItem->str,  pQwm->server.ip  )  )  {
			cfgQwmServIp(  pItem->str  );
		}
		iErr  =  0;
		goto  errLabel;
	}
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	if  (  lstrcmp(  pQwm->cfg.cnt.ip,  pQwm->server.ip  )  )	//  本管理区内机器的glCntIp的配置
		cfgQwmServIp(  pQwm->cfg.cnt.ip  );

	iErr  =  0;
	
errLabel:
	
	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );
	
	//  traceLogA(  "leave retrieveQwmGlCntIp."  );

   */

	return  iErr;

}

#if  0
 int  retrieveQwmCfg(  QY_W_MON  *  pQwm  )
{
	int							iErr			=		-1;
	ASR_SOCK					aS;
	int							i				=		0;
	QWM_SESSION					session;
	BOOL						bSessionOpen	=		FALSE;
	QY_COMM_RESP				tmpResp;
	char						cfgsBuf[8192];
	unsigned  int				len;
	unsigned  int				size;
	QY_CFGITEM				*	pItem;
	char					*	ptr;
	QNM_CMDPARAM_getCfgs		cmdParamGetCfgs;
	
	traceLogA(  "enter retrieveQwmCfg."  );

	//  取得MAC地址, 2005/02/23, 为了及时刷新网卡被禁用的情况，将以前的只取一次网卡的做法改为每次都取一下网卡的配置
	//  if  (  !pQwm->macsInfo.nMacs  )  {
	//  	getQwmMacs(  &pQwm->macsInfo  );
	//  }
	QWM_MACS_INFO	tmpMacsInfo;
	memset(  &tmpMacsInfo,  0,  sizeof(  tmpMacsInfo  )  );
	getQwmMacs(  &pQwm->env,  &tmpMacsInfo  );
	if  (  memcmp(  &tmpMacsInfo,  &pQwm->macsInfo,  sizeof(  tmpMacsInfo  )  )  )  {
		memcpy(  &pQwm->macsInfo,  &tmpMacsInfo,  sizeof(  pQwm->macsInfo  )  );
	}
	if  (  !pQwm->macsInfo.nMacs  )  goto  errLabel;
	//

	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
		
	if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
	bSessionOpen  =  TRUE;
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	if  (  !bSeqNoCorrect(  pQwm,  session.servSeqNo,  pQwm->cfg.seqNo  )  )  {
		traceLogA(  "管理端序列号不符, 无法retrieveQwmCfg(  )"  );  goto  errLabel;
	}		
	
	memset(  &cmdParamGetCfgs,  0,  sizeof(  cmdParamGetCfgs  )  );
	cmdParamGetCfgs.ucbStartProxy  =  0;	//  pQwm->cfg.ucbStartProxy;	//  2007/02/16
	if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_getCfgs,  (  char  *  )&cmdParamGetCfgs,  sizeof(  cmdParamGetCfgs  )  )  )  goto  errLabel;
	if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;

	len  =  0;
	size  =  tmpResp.head.len;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
		 pItem  =  (  QY_CFGITEM  *  )ptr;
		 len  =  qyntohCfgItem(  pItem  );
		 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;
		 if  (  pItem->cfgId  ==  CONST_qnmCfgId_null  )  break;
		 cfgQwmItem(  pQwm,  pItem  );
		 ptr  +=  len;  size  -=  len;		 
	}

	iErr = 0;
	
errLabel:

	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );

	//  2006/03/06, 增加了对管理中心的状态判断
	if  (  iErr  &&  pQwm->status.common.ucbServerOnline  )  pQwm->status.common.ucbServerOnline  =  0;
	if  (  !iErr  &&  !pQwm->status.common.ucbServerOnline  )  pQwm->status.common.ucbServerOnline  =  TRUE;

	traceLogA(  "leave retrieveQwmCfg."  );

	return  iErr;

}
#endif

  int  retrieveQwmCfg(  QY_W_MON  *  pQwm  )
{
	int							iErr			=		-1;
	ASR_SOCK					aS;
	int							i				=		0;
	QWM_SESSION					session;
	BOOL						bSessionOpen	=		FALSE;
	QY_COMM_RESP				tmpResp;
	char						cfgsBuf[8192];
	unsigned  int				len;
	unsigned  int				size;
	char					*	ptr;
	QNM_CMDPARAM_getCfgs		cmdParamGetCfgs;
	
	traceLogA(  "enter retrieveQwmCfg."  );

	//  取得MAC地址, 2005/02/23, 为了及时刷新网卡被禁用的情况，将以前的只取一次网卡的做法改为每次都取一下网卡的配置
	//  if  (  !pQwm->macsInfo.nMacs  )  {
	//  	getQwmMacs(  &pQwm->macsInfo  );
	//  }
	QWM_MACS_INFO	tmpMacsInfo;
	memset(  &tmpMacsInfo,  0,  sizeof(  tmpMacsInfo  )  );
	getQwmMacs(  &pQwm->env,  &tmpMacsInfo  );
	if  (  memcmp(  &tmpMacsInfo,  &pQwm->macsInfo,  sizeof(  tmpMacsInfo  )  )  )  {
		memcpy(  &pQwm->macsInfo,  &tmpMacsInfo,  sizeof(  pQwm->macsInfo  )  );
	}
	if  (  !pQwm->macsInfo.nMacs  )  goto  errLabel;
	//

	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
		
	if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
	bSessionOpen  =  TRUE;
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	if  (  !bSeqNoCorrect(  pQwm,  session.servSeqNo,  pQwm->cfg.seqNo  )  )  {
		traceLogA(  "管理端序列号不符, 无法retrieveQwmCfg(  )"  );  goto  errLabel;
	}		
	
	memset(  &cmdParamGetCfgs,  0,  sizeof(  cmdParamGetCfgs  )  );
	cmdParamGetCfgs.ucbStartProxy  =  0;	//  pQwm->cfg.ucbStartProxy;	//  2007/02/16
	if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_getCfgs,  (  char  *  )&cmdParamGetCfgs,  sizeof(  cmdParamGetCfgs  )  )  )  goto  errLabel;
	if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;

	len  =  0;
	size  =  tmpResp.head.len;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
		 QY_CFGITEM_ntoh_U					item_ntoh;
		 QY_CFGITEM_ntoh_U				*	pItem	=	&item_ntoh;
		 //  pItem  =  (  QY_CFGITEM  *  )ptr;
		 len  =  qyntohCfgItem(  ptr,  pItem  );
		 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;
		 if  (  pItem->head.cfgId  ==  CONST_qnmCfgId_null  )  break;
		 cfgQwmItem(  pQwm,  pItem  );
		 ptr  +=  len;  size  -=  len;		 
	}

	iErr = 0;
	
errLabel:

	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );

	//  2006/03/06, 增加了对管理中心的状态判断
	if  (  iErr  &&  pQwm->status.common.ucbServerOnline  )  pQwm->status.common.ucbServerOnline  =  0;
	if  (  !iErr  &&  !pQwm->status.common.ucbServerOnline  )  pQwm->status.common.ucbServerOnline  =  TRUE;

	traceLogA(  "leave retrieveQwmCfg."  );

	return  iErr;

}




 int  retrieveQnmProxyCfg(  QY_W_MON  *  pQwm  )
{
	int							iErr			=		-1;
	ASR_SOCK					aS;
	QWM_SESSION					session;
	BOOL						bSessionOpen	=		FALSE;
	QY_COMM_RESP				tmpResp;
	char						cfgsBuf[8192];
	unsigned  int				len;
	unsigned  int				size;
	//  QY_CFGITEM				*	pItem;
	char					*	ptr;
	QNM_CMDPARAM_getCfgs		cmdParamGetCfgs;
	
	traceLogA(  "enter retrieveQnmProxyCfg."  );

	//  取得MAC地址
	if  (  !pQwm->macsInfo.nMacs  )  {
		getQwmMacs(  &pQwm->env,  &pQwm->macsInfo  );
	}

	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
		
	if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
	bSessionOpen  =  TRUE;
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	memset(  &cmdParamGetCfgs,  0,  sizeof(  cmdParamGetCfgs  )  );
	if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_getProxyCfgs,  (  char  *  )&cmdParamGetCfgs,  sizeof(  cmdParamGetCfgs  )  )  )  goto  errLabel;
	if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	if  (  isRcQuit(  session.comm.usLastRespCode_i  )  )  {
		traceLogA(  "得到了退出命令"  );
		pQwm->cfg.ucbStopMon  =  TRUE;  goto  errLabel;
	}
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	len  =  0;
	size  =  tmpResp.head.len;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
		 //  pItem  =  (  QY_CFGITEM  *  )ptr;
		 QY_CFGITEM_ntoh_U			item_ntoh;
		 QY_CFGITEM_ntoh_U		*	pItem		=	&item_ntoh;
		 len  =  qyntohCfgItem(  ptr,  pItem  );
		 if  (  !len  ||  len  >  size  )  goto  errLabel;
		 if  (  pItem->head.cfgId  ==  CONST_qnmCfgId_null  )  break;
		 cfgQwmItem(  pQwm,  pItem  );
		 ptr  +=  len;  size  -=  len;		 
	}

	iErr = 0;
	
errLabel:

	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );

	traceLogA(  "leave retrieveQnmProxyCfg. %s",  iErr  ?  "失败"  :  "成功"  ); 

	return  iErr;

}

//  2006/07/016, 下面为最大的尝试取策略的次数
#ifdef  __DEBUG__
		#define		CONST_maxRetriveQwmOtherCfgsTimes			3
#else	
		#define		CONST_maxRetriveQwmOtherCfgsTimes			100			//  对注册表，数量可能比较多，所以增加了最大的尝试次数, 2006/07/16
#endif

 int  queryCfgs(  QY_W_MON  *  pQwm  )
{	 

	int							iErr			=		-1;
	ASR_SOCK					aS;
	QWM_SESSION					session;
	BOOL						bSessionOpen	=		FALSE;
	QY_COMM_RESP				tmpResp;
	char						cfgsBuf[max(  8192,  sizeof(  QY_PC_RULESU  )  )];
	QY_PC_COMMU					cmdParam;
	int							iLoopCtrl;
	RULE_COMMON_HEAD		*	pRuleHead;
	QY_PC_RULESU			*	pRulesU			=		NULL;
	char						buf[MAX_PATH  +  1];
	int							j;
	static  unsigned  int		uiQueryTimes	=		1;			//  2006/07/15
	unsigned  int				len;

	//  if  (  !pQwm->cfg.pcRules.osAudit.dirName[0]  &&  pQwm->cfg.pcRules.dev.ucUsbStorCmd  !=  CONST_devCmd_permittedAndMon  )  return  0;
	//  2006/07/15, 这里仅取个配置信息，故将上述条件判断去掉
	//  2006/07/15, 此取配置已扩展为通用获取

	if  (  !g_bIsWinNT  )  return  0;		//  2006/08/06, 这里表明，98不支持文件监视和注册表监控功能

	traceLogA(  "enter retrieveQwmFileMonCfg."  );

	//  取得MAC地址
	if  (  !pQwm->macsInfo.nMacs  )  {
		getQwmMacs(  &pQwm->env,  &pQwm->macsInfo  );
	}

	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
		
	if  (  qwmOpenSession(  pQwm,  &session,  &aS  )  )  goto  errLabel;
	bSessionOpen  =  TRUE;
	if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	uiQueryTimes  ++  ;		//  2007/07/15, 连上服务器后才增加计数

	for  (  iLoopCtrl  =  0;  iLoopCtrl  <  CONST_maxRetriveQwmOtherCfgsTimes  &&  !pQwm->bQuit;  iLoopCtrl  ++  )  {
		 memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
		 MACRO_makePcCommHead(  CONST_pcCommType_queryCfgs,  pQwm,  cmdParam  );
		 cmdParam.queryCfgs.mems[0].uiChangesId_fileMon	=  pQwm->cfg.pcFileMonRules.uiChangesId;
		 cmdParam.queryCfgs.mems[0].uiQueryTimes			=  uiQueryTimes;							//  2006/07/15
		 cmdParam.queryCfgs.cnt  =  1;
		 //
		 //  MACRO_htonl(  cmdParam.uiChangesId_fileMon  );							//  注意：原来只有这个成员
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &cmdParam  )  )  <=  0  )  goto  errLabel;

		 //
		 memset(  cfgsBuf,  0,  sizeof(  cfgsBuf  )  );								//  2006/07/15
		 //
		 if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_queryCfgs,  (  char  *  )&cmdParam,  len  )  )  goto  errLabel;
		 if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
		 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;
		 if  (  tmpResp.head.len  <  sizeof(  RULE_COMMON_HEAD  )  )  break;

		 pRuleHead  =  (  RULE_COMMON_HEAD  *  )cfgsBuf;
		 pRulesU	=	(  QY_PC_RULESU  *  )cfgsBuf;								//  2006/07/16
		 //  
		 switch  (  qyntohl(  pRuleHead->uiType  )  )  {
				 case  CONST_ruleType_pcFileMon:  {
					   PC_FILEMON_RULES	*	pFileMonRules  =  (  PC_FILEMON_RULES  *  )pRuleHead;
					   WCHAR				wBuf[512];
					   
					   traceLogA(  "get pc File Mon Cfg"  ); 
					   _snprintf(  buf,  sizeof(  buf  ),  "%s",  pQwm->cfg.pcRules.osAudit.dirName  );
					   pQwm->cfg.pcRules.osAudit.dirName[0]  =  0;
					   
					   MACRO_ntohl(  pFileMonRules->uiType  );
					   MACRO_ntohl(  pFileMonRules->uiChangesId  );
					   if  (  pFileMonRules->ucCnt  >  mycountof(  pFileMonRules->ucFlgs  )  )  {
						   traceLogA(  "遇到了数据越界的情况"  );  goto  errLabel;
					   }
					   for  (  j  =  0;  j  <  pFileMonRules->ucCnt;  j  ++  )  {
						    myUtf82WChar(  pFileMonRules->bufs[j],  wBuf,  mycountof(  wBuf  )  );  wBuf[mycountof(  wBuf  )  -  1]  =  0;
							_wcslwr(  wBuf  );
							wcsncpy(  (  WCHAR  *  )pFileMonRules->bufs[j],  wBuf,  sizeof(  pFileMonRules->bufs[j]  )  /  sizeof(  WCHAR  )  );
							(  (  WCHAR  *  )pFileMonRules->bufs[j]  )[sizeof(  pFileMonRules->bufs[j]  )  /  sizeof(  WCHAR  )  -  1]  =  0;
					   }
					   // 					   
					   memcpy(  &pQwm->cfg.pcFileMonRules,  (  char  *  )pFileMonRules,  sizeof(  pQwm->cfg.pcFileMonRules  )  );					   
					   //
					   saveFileMonRules(  pQwm  );

					   _snprintf(  pQwm->cfg.pcRules.osAudit.dirName,  sizeof(  pQwm->cfg.pcRules.osAudit.dirName  ),  "%s",  buf  );
						}
					   break;
				 case  CONST_pcCommType_registryRule:  {  

					   QY_PC_REGISTRYRULES  *  pRegistryRules  =  &pRulesU->registryRules;
					   QY_PC_REGISTRYRULE  *  pRule;

					   if  (  qyntohQyPcRulesU(  pRulesU  )  ==  -1  )  goto  errLabel;

					   traceLogA(  "2006/07/19, 严重警告：这里应加入过滤函数，并且要保证字符串不越界，最后要截尾"  );
					   if  (  pRegistryRules->cnt  >  mycountof(  pRegistryRules->mems  )  )  {
						   traceLogA(  "接收的注册表规则结构越界"  );  goto  errLabel;
					   }
					   for  (  j  =  0;  (  unsigned  int  )j  <  pRegistryRules->cnt;  j  ++  )  {	//  这里是截尾，很重要
						    pRule  =  &pRegistryRules->mems[j];
						    pRule->wSubKey[mycountof(  pRule->wSubKey  )  -  1]  =  0;
							pRule->wCfgName[mycountof(  pRule->wCfgName  )  -  1]  =  0;

							traceLogA(  "uiQueryTimes is %d, ruleSubKey is: [%S], cfgName is [%S]",  uiQueryTimes,  pRule->wSubKey,  pRule->wCfgName  );
					   }


					   if  (  sndRegistryVals(  pQwm,  &session,  &aS,  &pRulesU->registryRules  )  )  goto  errLabel;
														
						}
					   break;
				 default:
						 break;
		 }
	}

	iErr = 0;
	
errLabel:

	if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &aS  );

	traceLogA(  "leave retrieveQwmFileMonCfg. %s",  iErr  ?  "失败"  :  "成功"  ); 

	return  iErr;

}


/*
#define		CONST_tooLongSubKey			L"<Too long subKey>"
#define		CONST_tooLongValueName		L"<Too long value name>"
#define		CONST_tooLongValue			L"<Too long value>"
#define		CONST_tooLongValueOrName	L"<Too long value or name>"
*/

 int  getReg(  QY_ENV  *  pEnv,  int  iRuleId,  HKEY  hRootKey,  LPCWSTR keyName,  LPCWSTR  cfgName,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
	int						iErr		=	-1;
	BOOL					bKeyOpen	=	FALSE;
	HKEY					hKey;
	unsigned  char			valueBuf[4096  +  1];
	int						lRet		=	0;
	long					dwValueLenInBytes;
	DWORD					type;
	QY_PC_REGISTRYVAL		regVal;
	int						tmpiRet					=	-1;
			

	memset(  &regVal,  0,  sizeof(  regVal  )  );
	//
	regVal.iRuleId  =  iRuleId;

	lRet  =  RegOpenKey(  hRootKey,  keyName,  & hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;
	
	dwValueLenInBytes  =  sizeof(  valueBuf  );		
	lRet  =  RegQueryValueEx(  hKey,  cfgName,  0,  & type,  (  unsigned  char  *  )valueBuf,  (  unsigned  long  *  )&dwValueLenInBytes  );
	if  (  lRet  ==  ERROR_MORE_DATA  )  {
		regVal.ucbERROR_MORE_DATA  =  TRUE;
		}
	else  if  (  lRet  !=  ERROR_SUCCESS  )  goto errLabel;
	
	if  (  !regVal.ucbERROR_MORE_DATA  )  {
		
		regVal.uiCfgNameLen  =  wcslen(  cfgName  );
	 	safeWcsnCpy(  cfgName,  regVal.wCfgName,  mycountof(  regVal.wCfgName  )  );
		regVal.iValType  =  type;
		regVal.uiValLenInBytes  =  dwValueLenInBytes;
		  	  
		if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
			if  (  dwValueLenInBytes  <  2  )  (  (  WCHAR  *  )valueBuf  )[0]	=	0;
			else  (  (  WCHAR  *  )valueBuf  )[dwValueLenInBytes  /  2  -  1] = 0;
			safeWcsnCpy(  (  WCHAR  *  )valueBuf,  regVal.u.wCfgVal,  mycountof(  regVal.u.wCfgVal  )  );
			}
		else  if  (  type  ==  REG_DWORD  ||  type  ==  REG_DWORD_BIG_ENDIAN  )  {
				  regVal.u.iCfgVal  =  *(  DWORD  *  )valueBuf;
			  
		}
		
	}

	
	if  (  pf  &&  (  tmpiRet  =  pf(  p0,  p1,  &regVal  )  )  )  {
		iErr  =  tmpiRet;  goto  errLabel;
	}

	
	iErr  =  0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	 return  iErr;
}




 int  printPcRegistryVal(  QY_PC_REGISTRYVAL  *  pVal  )
{
	 traceLogA(  "cfgName is [%S],  val is [%s], type is %s",  pVal->wCfgName,  pVal->ucbKey  ?  "Key"  :  "Value",  qyGetDesByType1(  CONST_regTypeTable,  pVal->iValType  )  );
	 switch  (  pVal->iValType  )  {
			 case  REG_SZ:
			 case  REG_EXPAND_SZ:
			 case  REG_MULTI_SZ:
				   traceLogA(  "%S",  pVal->u.wCfgVal  );
				   break;
			 case  REG_DWORD:
			 case  REG_DWORD_BIG_ENDIAN:
				   traceLogA(  "%d",  pVal->u.iCfgVal  );
				   break;
			 default:
					break;
					
	 }

	 return  0;
}


 int  tmpHandler_sndRegistryVals(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr			=	-1;
	 COMMON_PARAM			*	pCommonParam0	=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM			*	pCommonParam1	=	(  COMMON_PARAM  *  )p1;
	 QY_PC_REGISTRYVAL		*	pVal			=	(  QY_PC_REGISTRYVAL  *  )p2;
	 QY_W_MON				*	pQwm			=	(  QY_W_MON  *  )pCommonParam0->p0;
	 QWM_SESSION			*	pSession		=	(  QWM_SESSION  *  )pCommonParam0->p1;
	 QY_SOCK				*	pSock			=	(  QY_SOCK  *  )pCommonParam0->p2;
	 QY_PC_REGISTRYRULE		*	pRule			=	(  QY_PC_REGISTRYRULE  *  )pCommonParam1->p0;
	 //
	 QY_PC_COMMU			*	pPcCommU		=	(  QY_PC_COMMU  *  )pCommonParam1->p2;
	 QY_PC_REGISTRYVALS		*	pRegistryVals	=	(  QY_PC_REGISTRYVALS  *  )&pPcCommU->registryVals;
	 char						cfgsBuf[4196];
	 unsigned  int				len;
	 QY_COMM_RESP				tmpResp;

	 if  (  pQwm->bQuit  ||  pQwm->cfg.pcRules.osAudit.ucSndPcRegistryValCmd  ==  CONST_devCmd_prohibited  )  goto  errLabel;		//  这是为了加快客户端升级的速度

	 printPcRegistryVal(  pVal  );

	 if  (  pRegistryVals->cnt  >=  mycountof(  pRegistryVals->mems  )  )  {
		 //  发送给管理端
		 //
		 char						szSidKey[256  +  1]		=	"";					//  用户子键名, 2006/09/29
		 WCHAR						wUsrName[256]			=	L"";
		 //
		 //  先把usrName给备份下来
		 safeStrnCpy(  pPcCommU->registryVals.szSidKey,  szSidKey,  mycountof(  szSidKey  )  );  //  2006/09/29
		 safeWcsnCpy(  pPcCommU->registryVals.wUsrName,  wUsrName,  mycountof(  wUsrName  )  );
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  pPcCommU  )  )  ==  -1  )  goto  errLabel;
		 //
		 if  (  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndRegistryVals,  (  char  *  )pPcCommU,  len  )  )  goto  errLabel;
		 if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
		 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;

		 memset(  pPcCommU,  0,  sizeof(  pPcCommU[0]  )  );
		 MACRO_makePcCommHead(  CONST_pcCommType_registryVal,  pQwm,  (  *pPcCommU  )  );
		 //  注意把usrName给恢复一下
		 safeStrnCpy(  szSidKey,  pPcCommU->registryVals.szSidKey,  mycountof(  pPcCommU->registryVals.szSidKey  )  );	//  2006/09/29
		 safeWcsnCpy(  wUsrName,  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  )  );

	 }

	 memcpy(  &pRegistryVals->mems[pRegistryVals->cnt],  pVal,  sizeof(  pRegistryVals->mems[pRegistryVals->cnt]  )  );
	 pRegistryVals->cnt  ++  ;

	 iErr  =  0;
errLabel:
	 return  iErr;
}



 int  tmpHandler_enumRegUsrs_sndRegistryVals(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr			=	-1;
	 COMMON_PARAM		*		pCommonParam0	=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM		*		pCommonParam1	=	(  COMMON_PARAM  *  )p1;
	 QWM_USR_INFO		*		pUsrInfo		=	(  QWM_USR_INFO  *  )p2;
	 //
 	 QY_W_MON				*	pQwm			=	(  QY_W_MON  *  )pCommonParam0->p0;
	 QWM_SESSION			*	pSession		=	(  QWM_SESSION  *  )pCommonParam0->p1;
	 QY_SOCK				*	pSock			=	(  QY_SOCK  *  )pCommonParam0->p2;
	 //
	 QY_PC_REGISTRYRULE	*		pRule			=	(  QY_PC_REGISTRYRULE  *  )pCommonParam1->p0;
	 //
	 QY_PC_COMMU		*		pPcCommU		=	(  QY_PC_COMMU  *  )pCommonParam1->p2;
	 //
	 WCHAR						wSubKey[512]	=	L"";
	 int						tmpiRet;
	 char						cfgsBuf[4196];
	 unsigned  int				len;
	 QY_COMM_RESP				tmpResp;
	 WCHAR						wDomainName[128]	=	L"";

	 if  (  pQwm->bQuit  ||  pQwm->cfg.pcRules.osAudit.ucSndPcRegistryValCmd  ==  CONST_devCmd_prohibited  )  goto  errLabel;		//  这是为了加快客户端升级的速度

	 trim(  pUsrInfo->name  );	//  这里要把没有登陆的用户或其他键值给屏蔽掉
	 if  (  !pUsrInfo->name[0]  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //  2006/06/29,增加对登陆域的读取
	 _snwprintf(  wSubKey,  mycountof(  wSubKey  ),  L"%S\\%S",  pUsrInfo->szSubKey,  CONST_subKey_volatileEnvironment  );
	 if  (  qyGetRegCfg1W(  &pQwm->env,  HKEY_USERS,  wSubKey,  CONST_regCfgName_wUSERDNSDOMAIN,  wDomainName,  mycountof(  wDomainName  ),  0  )  )  wDomainName[0]  =  0;

	 //  得出用户子键
	 myStr2WChar(  pUsrInfo->szSubKey,  wSubKey,  mycountof(  wSubKey  ) );
	 _snwprintf(  wSubKey,  mycountof(  wSubKey  ),  L"%s\\%s",  wSubKey,  pRule->wSubKey  );
	 wSubKey[mycountof(  wSubKey  )  -  1]  =  0;

	 memset(  pPcCommU,  0,  sizeof(  pPcCommU[0]  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_registryVal,  pQwm,  (  *pPcCommU  )  );

	 //  填充registryVals里的用户信息，2006/09/29
	 safeStrnCpy(  pUsrInfo->szSubKey,  pPcCommU->registryVals.szSidKey,  mycountof(  pPcCommU->registryVals.szSidKey  )  );	//  2006/09/29
	 myStr2WChar(  pUsrInfo->name,  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  )  );
	 if  (  wDomainName[0]  )  _snwprintf(  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  ),  L"%s@%s",  pPcCommU->registryVals.wUsrName,  wDomainName  );

	 if  (  pRule->wCfgName[0]  )  {	//  取一个特定的值
		 tmpiRet  =  getReg(  &pQwm->env,  pRule->id,  (  HKEY  )pRule->iRootKey,  wSubKey,  pRule->wCfgName,  tmpHandler_sndRegistryVals,  p0,  p1  );
		}
	 else  {	//  枚举一个项下的所有键值
		   tmpiRet  =  enumReg(  &pQwm->env,  pRule->id,  (  HKEY  )pRule->iRootKey,  wSubKey,  tmpHandler_sndRegistryVals,  p0,  p1  );
	 }
	 if  (  !tmpiRet  )  {
		 if  (  pPcCommU->registryVals.cnt  !=  0  )  {	//  要是没有发送完毕，就在这里发送出去
			 if  (  (  len  =  qyhtonQyPcCommU(  0,  pPcCommU  )  )  ==  -1  )  goto  errLabel;
			 //
			 if  (  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndRegistryVals,  (  char  *  )pPcCommU,  len  )  )  goto  errLabel;
			 if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
			 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;

		 }
	 }


	 //  2006/09/28,	传送结束符
	 memset(  pPcCommU,  0,  sizeof(  pPcCommU[0]  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_registryVal,  pQwm,  (  *pPcCommU  )  );
	 //
 	 //  填充registryVals里的用户信息，2006/09/29
	 safeStrnCpy(  pUsrInfo->szSubKey,  pPcCommU->registryVals.szSidKey,  mycountof(  pPcCommU->registryVals.szSidKey  )  );	//  2006/09/29
	 myStr2WChar(  pUsrInfo->name,  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  )  );
	 if  (  wDomainName[0]  )  _snwprintf(  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  ),  L"%s@%s",  pPcCommU->registryVals.wUsrName,  wDomainName  );

	 //
	 QY_PC_REGISTRYVAL  *  pVal;
	 pVal  =  &pPcCommU->registryVals.mems[0];
	 memset(  pVal,  0,  sizeof(  pVal[0]  )  );
	 pVal->iRuleId  =  pRule->id;
	 pVal->ucFlg  =  tmpiRet  ?  CONST_ucFlg_err  :  CONST_ucFlg_end;
	 pPcCommU->registryVals.cnt  =  1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  pPcCommU  )  )  ==  -1  
		 ||  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndRegistryVals,  (  char  *  )pPcCommU,  len  )
			 ||  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  
				 ||  !isRcOk(  tmpResp.head.usCode  )  )
	 {
		 traceLogA(  "sndRegistryVal 传送结束符失败"  );
		 goto  errLabel;
	 }

	 iErr  =  0;

errLabel:
	 
	 return  iErr;
	 
}


 int  sndRegistryVal(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock,  QY_PC_REGISTRYRULES  *  pRules,  QY_PC_REGISTRYRULE	*	pRule  )
{
	 int					iErr							=		-1;
	 QY_PC_COMMU			pcCommU;
	 COMMON_PARAM			commonParam0,  commonParam1;
	 char					cfgsBuf[4196];
	 unsigned  int			len;
	 QY_COMM_RESP			tmpResp;


	 MACRO_makeCommonParam3(  pQwm,  pSession,  pSock,  commonParam0  );
	 MACRO_makeCommonParam3(  pRule,  0,  &pcCommU,  commonParam1  );
	 //
	 if  (  (  HKEY  )pRule->iRootKey  ==  HKEY_USERS  )  {
		 if  (  enumRegUsrs(  pQwm->env.iPlatformId,  &commonParam0,  &commonParam1,  tmpHandler_enumRegUsrs_sndRegistryVals  )  )  goto  errLabel;
		 }
	 else  {
		    memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
			MACRO_makePcCommHead(  CONST_pcCommType_registryVal,  pQwm,  pcCommU  );

		    if  (  pRule->wCfgName[0]  )  {	//  取一个特定的值
		  		if  (  getReg(  &pQwm->env,  pRule->id,  (  HKEY  )pRule->iRootKey,  pRule->wSubKey,  pRule->wCfgName,  tmpHandler_sndRegistryVals,  &commonParam0,  &commonParam1  )  )  goto  errLabel;
				}
	 		else  {	//  枚举一个项下的所有键值
				  if  (  enumReg(  &pQwm->env,  pRule->id,  (  HKEY  )pRule->iRootKey,  pRule->wSubKey,  tmpHandler_sndRegistryVals,  &commonParam0,  &commonParam1  )  )  goto  errLabel;
	  		}
		  
			if  (  pcCommU.registryVals.cnt  !=  0  )  {	//  要是没有发送完毕，就在这里发送出去
				if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
				//
				if  (  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndRegistryVals,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
				if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
				if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;
			}
	
			//  2006/09/28,	传送结束符
			memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
			MACRO_makePcCommHead(  CONST_pcCommType_registryVal,  pQwm,  pcCommU  );
			//
			QY_PC_REGISTRYVAL  *  pVal;
			pVal  =  &pcCommU.registryVals.mems[0];
			memset(  pVal,  0,  sizeof(  pVal[0]  )  );
			pVal->iRuleId  =  pRule->id;
			pVal->ucFlg  =  CONST_ucFlg_end;
			pcCommU.registryVals.cnt  =  1;
			if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  
				||  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndRegistryVals,  (  char  *  )&pcCommU,  len  )
					||  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  
						||  !isRcOk(  tmpResp.head.usCode  )  )
			{
				traceLogA(  "sndRegistryVal 传送结束符失败"  );
				goto  errLabel;
			 }

	 }

	 iErr  =  0;

errLabel:

	 //
	 if  (  iErr  )  {	//  2006/09/28，出错时需要传送相关信息

		 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
		 MACRO_makePcCommHead(  CONST_pcCommType_registryVal,  pQwm,  pcCommU  );
		 //
		 QY_PC_REGISTRYVAL  *  pVal;
		 pVal  =  &pcCommU.registryVals.mems[0];
		 memset(  pVal,  0,  sizeof(  pVal[0]  )  );
		 pVal->iRuleId  =  pRule->id;
		 pVal->ucFlg  =  CONST_ucFlg_err;
		 pcCommU.registryVals.cnt  =  1;
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  
			 ||  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndRegistryVals,  (  char  *  )&pcCommU,  len  )
				||  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  
					||  !isRcOk(  tmpResp.head.usCode  )  )
		 {
			 traceLogA(  "sndRegistryVal 设置规则状态失败"  );
		 }

	 }

	 traceLogA(  "sndRegistryVal leaves with %s",  iErr  ?  "Failed"  :  "Ok"  );

	 return  iErr;
}


 int  sndRegistryVals(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock,  QY_PC_REGISTRYRULES  *  pRules  )
{
	 int					iErr							=		-1;
	 int					index;
	 QY_PC_REGISTRYRULE	*	pRule							=		NULL;

	 //  traceLogA(  "sendRegistryVals: %S",  (  WCHAR  *  )pRules->mems[0].subkey  );
	 if  (  pRules->cnt  !=  1  )  {
		 traceLogA(  "目前仅支持数量为1的注册表规则"  );  goto  errLabel;
	 }
	 for  (  index  =  0;  (  unsigned  int  )index  <  pRules->cnt;  index  ++  )  {
		  pRule  =  &pRules->mems[index];
		  sndRegistryVal(  pQwm,  pSession,  pSock,  pRules,  pRule  );
	 }

	 iErr  =  0;
errLabel:
	 
	 traceLogA(  "sndRegistryVals leaves with %s",  iErr  ?  "Failed"  :  "Ok"  );
	 return  iErr;
}

typedef  struct  __qwmCfgFileHead_t		{
				 char					ver[16];	//  文件版本号，和qwmSvr的版本一致
				 char					reserved[256];
}		 QWM_CFG_FILEHEAD;


 int  saveFileMonRules(  QY_W_MON  *  pQwm  )
{
	 int				iErr		=	-1;
	 QWM_CFG_FILEHEAD	fileHead;
	 DWORD				nBytes;

	 if  (  !isHandleValid(  pQwm->hCfgFile  )  )  goto  errLabel;

	 SetFilePointer(  pQwm->hCfgFile,  0,  0,  FILE_BEGIN  );
	 memset(  &fileHead,  0,  sizeof(  fileHead  )  );
	 safeStrnCpy(  qnmVerStr(  pQwm->iServiceId  ),  fileHead.ver,  sizeof(  fileHead.ver  )  );
	 if  (  !WriteFile(  pQwm->hCfgFile,  &fileHead,  sizeof(  fileHead  ),  &nBytes,  0  )  )  goto  errLabel;
	 if  (  !WriteFile(  pQwm->hCfgFile,  &pQwm->cfg.pcFileMonRules,  sizeof(  pQwm->cfg.pcFileMonRules  ),  &nBytes,  0  )  )  goto  errLabel;
	 if  (  !FlushFileBuffers(  pQwm->hCfgFile  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	 return  iErr;
}

 int  getFileMonRules(  QY_W_MON  *  pQwm  )
{
	 int				iErr		=		-1;
	 QWM_CFG_FILEHEAD	fileHead;
	 DWORD				nBytes;
	 //  int				j;

	 if  (  !isHandleValid(  pQwm->hCfgFile  )  )  goto  errLabel;

	 SetFilePointer(  pQwm->hCfgFile,  0,  0,  FILE_BEGIN  );
	 memset(  &fileHead,  0,  sizeof(  fileHead  )  );
	 if  (  !ReadFile(  pQwm->hCfgFile,  &fileHead,  sizeof(  fileHead  ),  &nBytes,  0  )  )  goto  errLabel;
	 if  (  !ReadFile(  pQwm->hCfgFile,  &pQwm->cfg.pcFileMonRules,  sizeof(  pQwm->cfg.pcFileMonRules  ),  &nBytes,  0  )  )  goto  errLabel;
	 				   
	 iErr  =  0;
errLabel:
	 if  (  iErr  )  memset(  &pQwm->cfg.pcFileMonRules,  0,  sizeof(  pQwm->cfg.pcFileMonRules  )  );
	 return  iErr;
}

 /*  //  旧的函数
 int  commWithGlCnt(  QY_W_MON  *  pQwm  )
{
	 int					iErr				=		-1;
	 QWM_INFO				qwmInfo;
	 QY_SOCK				sock;
	 QWM_SESSION			session;
	 BOOL					bSessionOpen		=		FALSE;
	 QY_COMM_RESP			tmpResp;
	 int					len;

	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	 //  通报本机信息
	 qwmInfo.iPlatformId  =  pQwm->env.iPlatformId;
	 safeStrnCpy(  pQwm->pcName,  qwmInfo.pcName,  sizeof(  qwmInfo.pcName  )  );
	 safeStrnCpy(  pQwm->env.systemBuf,  qwmInfo.systemBuf,  sizeof(  qwmInfo.systemBuf  )  );
	 safeStrnCpy(  pQwm->env.servicePackBuf,  qwmInfo.servicePackBuf,  sizeof(  qwmInfo.servicePackBuf  )  );
	 //  safeStrnCpy(  pQwm->curUsrName,  qwmInfo.curUsrName,  sizeof(  qwmInfo.curUsrName  )  );
	 //  safeStrnCpy(  pQwm->proxyServer,  qwmInfo.proxyServer,  sizeof(  qwmInfo.proxyServer  )  );

	 len  =  qyhtonQwmInfo(  &qwmInfo  );
	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt  pcName is [%s]",  pQwm->pcName  );
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showQwmInfo,  (  char  *  )&qwmInfo,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;

	 	 
	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt leaves %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}
*/

 int  commWithGlCnt(  QY_W_MON  *  pQwm  )
{
	 int						iErr				=		-1;
	 QWM_INFO_EX				qwmInfoEx;
	 QWM_INFO_EX			*	pQwmInfoEx			=		&qwmInfoEx;
	 QY_SOCK					sock;
	 QWM_SESSION				session;
	 BOOL						bSessionOpen		=		FALSE;
	 QY_COMM_RESP				tmpResp;
	 int						len;

	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	 //  通报本机信息
	 memset(  pQwmInfoEx,  0,  sizeof(  QWM_INFO_EX  )  );
	 pQwmInfoEx->type  =  CONST_qwmInfoType_qwmSvr;
	 pQwmInfoEx->u.qwmSvr.qwm.iPlatformId  =  pQwm->env.iPlatformId;
	 safeStrnCpy(  pQwm->pcName,  pQwmInfoEx->u.qwmSvr.qwm.pcName,  sizeof(  pQwmInfoEx->u.qwmSvr.qwm.pcName  )  );
	 //  safeStrnCpy(  pQwm->env.systemBuf,  pQwmInfoEx->u.qwmSvr.qwm.systemBuf,  sizeof(  pQwmInfoEx->u.qwmSvr.qwm.systemBuf  )  );
	 myTChar2Utf8(  pQwm->env.systemBuf,  pQwmInfoEx->u.qwmSvr.qwm.systemBuf,  mycountof(  pQwmInfoEx->u.qwmSvr.qwm.systemBuf  )  );
	 //  safeStrnCpy(  pQwm->env.servicePackBuf,  pQwmInfoEx->u.qwmSvr.qwm.servicePackBuf,  sizeof(  pQwmInfoEx->u.qwmSvr.qwm.servicePackBuf  )  );
	 myTChar2Utf8(  pQwm->env.servicePackBuf,  pQwmInfoEx->u.qwmSvr.qwm.servicePackBuf,  mycountof(  pQwmInfoEx->u.qwmSvr.qwm.servicePackBuf  )  );
	 //  safeStrnCpy(  pQwm->curUsrName,  qwmInfo.curUsrName,  sizeof(  qwmInfo.curUsrName  )  );
	 pQwmInfoEx->u.qwmSvr.qwm.uiLangId  =  pQwm->env.usLangId;													//  2005/01/22
	 TCHAR	tBuf[MAX_PATH];
	 GetWindowsDirectory(  tBuf,  mycountof(  tBuf  )  );
	 myTChar2Utf8(  tBuf,  pQwmInfoEx->u.qwmSvr.qwm.winDir,  sizeof(  pQwmInfoEx->u.qwmSvr.qwm.winDir  )  );		//  2005/01/22
	 //
	 safeStrnCpy(  pQwm->cfg.seqNo,  pQwmInfoEx->u.qwmSvr.seqNo,  sizeof(  pQwmInfoEx->u.qwmSvr.seqNo  )  );

	 len  =  qyhtonQwmInfoEx(  pQwmInfoEx  );
	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt  pcName is [%s]",  pQwm->pcName  );
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showQwmInfoEx,  (  char  *  )pQwmInfoEx,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;

	 	 
	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt leaves %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}



 //  2003/09/12修改
 int  showQwmQuit(  QY_W_MON  *  pQwm  )
{
	 int					iErr				=		-1;
	 QY_SOCK				sock;
	 QWM_SESSION			session;
	 BOOL					bSessionOpen		=		FALSE;
	 QY_COMM_RESP			tmpResp;

	 traceLogA(  "showQwmQuit enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;
	
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_quit,  NULL,  0  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 	 
	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 traceLogA(  "showQwmQuit leaves %s",  iErr  ?  "失败"  :  "成功"  );

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


 int  getQwmInitialCfg(  QY_W_MON  *  pQwm  )
{	 
	 //  QY_REG		reg;
	 //  char		buf[256];

	 pQwm->cfg.ulbCommWithGlCnt			=	TRUE;
	 if  (  pQwm->iAppType  ==  CONST_qyAppType_qwmSvr  )  {
	     pQwm->cfg.ulbQwmThreadProcCmd				=	TRUE;
		 if  (  pQwm->cfg.ucbNetMc2  )  {
			 pQwm->cfg.ulbQwmThreadPrinterMgr		=	TRUE;				//  2005/09/10
			 pQwm->cfg.ulbQwmThreadFileMon			=	TRUE;				//  2005/09/13
			 #ifdef  __SUPPORT_AUTOLOGON__
					 pQwm->cfg.ulbQueryAutoLogon	=	TRUE;			//  2006/01/07
			 #endif
			 pQwm->cfg.ulbQwmThreadPcMon			=	TRUE;		//  2006/03/05
			 pQwm->cfg.ulbQwmThreadCollectUsrLog	=	TRUE;		//  2007/02/18
			 pQwm->cfg.ulbQwmThreadWndProc			=	TRUE;		//  2007/02/27
		 }

		 //
		 //  pQwm->cfg.ulbRetrieveQwmGlCntIp		=	TRUE;								//  取分组管理  //  2003/09/05取消
		 pQwm->cfg.ulbRetrieveQwmCfg			=	TRUE;
		 pQwm->cfg.ulbSndSavedTmpLog			=	TRUE;
		 if  (  pQwm->cfg.ucbNetMc2  )  {
			 pQwm->cfg.ulbShowPcProcess  =  TRUE;				//  应该是TRUE，暂时关掉这项功能，2005/07/30
			 pQwm->cfg.ulbShowPcModules  =  TRUE;				//  2006/04/14
		 }
		 
		 lstrcpyn(  pQwm->cfg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  pQwm->cfg.rootKey  )  );

		 lstrcpyn(  pQwm->cfg.mutexName,  _T(  DEFAULT_qwmMutexName  ),  mycountof(  pQwm->cfg.mutexName  )  );
		 pQwm->cfg.svTarget						=	_T(  CONST_qwmSvr_runtimePathName  );
		 pQwm->cfg.serviceName					=	_T(  CONST_qwmSvr_serviceName  );
		 pQwm->cfg.legacyServiceName			=	_T(  CONST_qwmSvr_legacyServiceName  );				//  2006/08/31
		 
		}
	 else  {
	 		pQwm->cfg.ulbRetrieveQnmProxyCfg		=	TRUE;

			lstrcpyn(  pQwm->cfg.rootKey,  _T(  CONST_qyKey_qnmProxy  ),  mycountof(  pQwm->cfg.rootKey  )  );
			
			lstrcpyn(  pQwm->cfg.mutexName,  _T(  DEFAULT_qnmProxyMutexName  ),  mycountof(  pQwm->cfg.mutexName  )  );
			pQwm->cfg.svTarget						=	_T(  CONST_qnmProxy_runtimePathName  );
			pQwm->cfg.serviceName					=	_T(  CONST_qnmProxy_serviceName  );
			pQwm->cfg.legacyServiceName				=	_T(  ""  );										//  2006/08/31
			
	 }

	 //  2007/02/16
	 myStr2TChar(  DEFAULT_qwmMutexName_syncNetShare,  pQwm->cfg.mutexName_syncNetShare,  mycountof(  pQwm->cfg.mutexName_syncNetShare  )  );
	 pQwm->cfg.ulMilliSeconds_syncNetShare  =  500;
	 //  2007/02/18
	 myStr2TChar(  DEFAULT_qwmMutexName_syncLogEvent,  pQwm->cfg.mutexName_syncLogEvent,  mycountof(  pQwm->cfg.mutexName_syncLogEvent  )  );
	 pQwm->cfg.ulMilliSeconds_syncLogEvent  =  1000;


	 //
	 setSockTimeout(  &pQwm->cfg.to  );
	 getQwmMacs(  &pQwm->env,  &pQwm->macsInfo  );

	 pQwm->cfg.usFindCntIntervalLoops						=  max(  2,  CONST_qwmFindCntIntervalLoops  );						//  2006/07/01
	 pQwm->cfg.usConnectIntervalLoops						=  max(  2,  CONST_qwmConnectIntervalLoops  );
	 pQwm->cfg.usQueryGlCntIpIntervalLoops					=  max(  2,  CONST_qwmQueryGlCntIpIntervalLoops  );
	 pQwm->cfg.usQueryCfgsIntervalLoops						=  max(  2,  CONST_qwmQueryCfgsIntervalLoops  );					//  2006/08/15
	 pQwm->cfg.usShowPcNetworkPropIntervalLoops				=  max(  2,  CONST_qwmShowPcNetworkPropIntervalLoops  );
	 pQwm->cfg.usShowPcWindowsUpdatePolicyIntervalLoops		=  max(  2,  CONST_qwmShowPcWindowsUpdatePolicyIntervalLoops  );	//  2006/05/21		
	 pQwm->cfg.usShowPcNetFlowIntervalLoops					=  max(  2,  CONST_qwmShowPcNetFlowIntervalLoops  );				//  2006/09/10
	 pQwm->cfg.usShowProcessIntervalLoops					=  max(  2,  CONST_qwmShowProcessIntervalLoops  );
	 pQwm->cfg.usSndEventLogIntervalLoops					=  max(  2,  CONST_qwmSndEventLogIntervalLoops  );
	 pQwm->cfg.usSndLogIntervalLoops						=  max(  2,  CONST_qwmSndLogIntervalLoops  );
	 pQwm->cfg.usSndUsrInfoIntervalLoops					=  max(  2,  CONST_qwmSndUsrInfoIntervalLoops  );					//  2005/09/04
	 pQwm->cfg.usSndNetStatIntervalLoops					=  max(  2,	 CONST_qwmSndNetStatIntervalLoops  );
	 pQwm->cfg.usSndPrintersIntervalLoops					=  max(  2,  CONST_qwmSndPrintersIntervalLoops  );
	 pQwm->cfg.usQueryAutoLogonIntervalLoops				=  max(  2,  CONST_queryAutoLogonIntervalLoops  );					//  2006/01/07
	 pQwm->cfg.usGetOpCmdIntervalLoops						=  max(  2,  DEFAULT_getOpCmdInterval  /  2  );						//  2006/02/11
	 pQwm->cfg.usShowModulesIntervalLoops					=  max(  2,  DEFAULT_showModulesInterval  /  2  );					//  2006/04/14
	 pQwm->cfg.usShowPcNetShareIntervalLoops				=  max(  2,  DEFAULT_showNetShareInterval  /  2  );					//  2007/02/14
	 pQwm->cfg.usShowPcArpIntervalLoops						=  max(  2,  DEFAULT_showArpInterval  /  2  );					//  2007/02/14
	 //
	 pQwm->cfg.usGetRandIntervalLoops						=  max(  30,  CONST_qwmGetRandIntervalLoops  );
	 pQwm->cfg.usCommWithGlCntIntervalLoops					=  max(  30,  CONST_qwmCommWithGlCntIntervalLoops  );
	 pQwm->cfg.nInterval_CommandHandlerLoop					=  2000;
	 pQwm->cfg.nInterval_qwmThreadProcCmd					=  2000;
	 pQwm->cfg.nInterval_qwmThreadProcFastCmd				=  2000;
	 //  pQwm->cfg.nInterval_qwmThreadProcIpScan			=  2000;
	 //  pQwm->cfg.nInterval_qwmThreadProcRegScan			=  2000;
	 pQwm->cfg.maxCommWithGlCntTime							=  CONST_qnmMaxCommWithGlCntTime;				
	 pQwm->cfg.maxWaitPcCommTime							=  CONST_qnmMaxWaitPcCommTime;					
	 
	 /*
	 memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
	 lstrcpyn(  reg.rootKey,  CONST_qyKey_qwm,  sizeof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pQwm->encCtx;
	 if  (  !qyGetRegCfgEx(  &reg,  CONST_qwmCfgName_cntIp,  buf,  sizeof(  buf  )  )  )  {
		 lstrcpyn(  pQwm->cfg.cnt.ip,  buf,  sizeof(  pQwm->cfg.cnt.ip  )  );
	 }
	 */
	 /*
	 if  (  !qyGetRegCfgEx(  &reg,  CONST_qwmCfgName_cntPort,  buf,  sizeof(  buf  )  )  )  {
		 pQwm->cfg.cnt.port  =  (  unsigned  short  )atol(  buf  );
	 }
	 */
	 /*	//  在第一步初始化时不设置管理端。用户在getQwmCfg(  )中做就可以了，服务进程靠自己来调节
	 getQwmServIpCfg(  pQwm,  &pQwm->cfg.cnt  );	//  2007/02/21


	 //  2005/07/30, 增加下面的server的赋值
	 memcpy(  &pQwm->server,  &pQwm->cfg.cnt,  sizeof(  pQwm->server  )  );
	 */

	 return  0;

}


 int  getQwmCfg(  QY_W_MON  *  pQwm,  BOOL  bGetServIpCfg  )
{
	int						iRet			=	-1;
	BOOL					bKeyOpen		=	FALSE;
	HKEY					hKey			=	NULL;
	int						lRet			=	0;
	TCHAR					buf[128];
	#ifdef  __DEBUG__
			long					cb;
			DWORD					type;
	#endif
	unsigned  char			ucRasCmd		=	CONST_rasCmd_prohibited;
	QY_REG					reg;
	QNM_RAS_RULE			rasRule;
	QY_LOGICAL_SERVER		interMon;
	QNM_DEV_RULE			devRule;
	QNM_OS_RULE				osRule;
	QNM_OSAUDIT_RULE		osAuditRule;		//  2005/09/14
	QNM_PCMON_RULE			pcMonRule;			//  2006/03/06
	unsigned  long			len;
		
	if  (  bGetServIpCfg  )  {
		getQwmServIpCfg(  pQwm,  &pQwm->cfg.cnt  );
		//  暂时将server.ip仅指向cnt.ip 
		if  (  memcmp(  &pQwm->server,  &pQwm->cfg.cnt,  sizeof(  pQwm->server  )  )  )	 memcpy(  &pQwm->server,  &pQwm->cfg.cnt,  sizeof(  pQwm->server  )  );
	}

	memset(  &reg,  0,  sizeof(  reg  )  );
	lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  reg.rootKey  )  );
	reg.pEncCtx  =  &pQwm->encCtx;
		
	lRet  =  RegOpenKey(  HKEY_LOCAL_MACHINE,  _T(  ROOT_KEY_AWM  ),  &hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;

#ifdef  __DEBUG__
	cb  =  sizeof(  buf  );  	buf[0]  =  0;
	if  (  RegQueryValueEx(  hKey,  _T(  CONST_regValName_tc  ),  0,  &type,  (  unsigned  char  *  )buf,  (  unsigned  long  *  )&cb  )  ==  ERROR_SUCCESS  
		&&  _ttol(  buf  )  ==  1  )  
	{
		pQwm->cfg.ucbStopMon  =  TRUE;			//  调试用，以使之卸载
	}
	cb  =  sizeof(  buf  );  buf[0]  =  0;
	if  (  RegQueryValueEx(  hKey,  _T(  CONST_regValName_ph  ),  0,  &type,  (  unsigned  char  *  )buf,  (  unsigned  long  *  )&cb  )  ==  ERROR_SUCCESS  
		&&  _ttol(  buf  )  ==  1  )  
	{
		pQwm->cfg.ucbPh  =  1;					//  调试用，使程序退出但不卸载
	}

#endif

	//  取拨号和非法外联管理策略
	len  =  sizeof(  rasRule  );
	if  (  !pQwm->bKeyUpdate  
		||  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_rasRule  ),  (  char  *  )&rasRule,  &len  )  )
	{
		memset(  &rasRule,  0,  sizeof(  rasRule  )  );
		//  rasRule.ucRasCmd  =  CONST_rasCmd_prohibited;
		rasRule.ucRasCmd  =  DEFAULT_rasCmd;		//  2005/09/18, 为了适应企业的应用(尤其是外来拨入的情况)，特将策略改为缺省允许
	}
	/*
	if  (  rasRule.ucRasCmd  !=  pQwm->cfg.pcRules.ras.ucRasCmd  )  pQwm->cfg.pcRules.ras.ucRasCmd  =  rasRule.ucRasCmd;
	if  (  memcmp(  rasRule.permittedPhoneNums,  pQwm->cfg.pcRules.ras.permittedPhoneNums,  sizeof(  rasRule.permittedPhoneNums  )  )  )
		memcpy(  pQwm->cfg.pcRules.ras.permittedPhoneNums,  rasRule.permittedPhoneNums, sizeof(  rasRule.permittedPhoneNums  )  );
	if  (  pQwm->cfg.pcRules.ras.ucbNotChkOnInternet  !=  rasRule.ucbNotChkOnInternet  )  pQwm->cfg.pcRules.ras.ucbNotChkOnInternet  =  rasRule.ucbNotChkOnInternet;	//  2005/01/12
	*/
	//  2005/06/25修改
	if  (  memcmp(  &rasRule,  &pQwm->cfg.pcRules.ras,  sizeof(  rasRule  )  )  ) { 
		memcpy(  &pQwm->cfg.pcRules.ras,  &rasRule,  sizeof(  pQwm->cfg.pcRules.ras  )  );
		traceLogA(  "getQwmCfg: rasRule changed"  );
	}

	//  取监视端配置,  2004/10/24
	len  =  sizeof(  interMon  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_interMon  ),  (  char  *  )&interMon,  &len  )  )  memset(  &interMon,  0,  sizeof(  interMon  )  );
	if  (  memcmp(  &pQwm->cfg.interMon,  &interMon,  sizeof(  interMon  )  )  )  { 
		memcpy(  &pQwm->cfg.interMon,  &interMon,  sizeof(  interMon  )  );
		traceLogA(  "getQwmCfg: interMon changed"  );
	}

	//  取外设管理策略, 2005/01/04
	len  =  sizeof(  devRule  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_devRule  ),  (  char  *  )&devRule,  &len  )  )  memset(  &devRule,  0,  sizeof(  devRule  )  );
	if  (  memcmp(  &pQwm->cfg.pcRules.dev,  &devRule,  sizeof(  devRule  )  )  )  {
		memcpy(  &pQwm->cfg.pcRules.dev,  &devRule,  sizeof(  devRule  )  );
		traceLogA(  "getQwmCfg: devRule changed"  );
	}

	//  取安全模式策略，2005/06/25
	len  =  sizeof(  osRule  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_osRule  ),  (  char  *  )&osRule,  &len  )  )  memset(  &osRule,  0,  sizeof(  osRule  )  );
	if  (  memcmp(  &pQwm->cfg.pcRules.os,  &osRule,  sizeof(  osRule  )  )  )  {
		memcpy(  &pQwm->cfg.pcRules.os,  &osRule,  sizeof(  osRule  )  );
		traceLogA(  "getQwmCfg(  ):  osRule changed"  );
	}


	//  取操作系统审计策略, 2005/09/14
	len  =  sizeof(  osAuditRule  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_osAuditRule  ),  (  char  *  )&osAuditRule,  &len  )  )  memset(  &osAuditRule,  0,  sizeof(  osAuditRule  )  );
	if  (  memcmp(  &pQwm->cfg.pcRules.osAudit,  &osAuditRule,  sizeof(  osAuditRule  )  )  )  {
		memcpy(  &pQwm->cfg.pcRules.osAudit,  &osAuditRule,  sizeof(  osAuditRule  )  );
		traceLogA(  "getQwmCfg(  ):  osAuditRule changed"  );	
	}

	//  取监控策略, 2006/03/06
	len  =  sizeof(  pcMonRule  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_pcMonRule  ),  (  char  *  )&pcMonRule,  &len  )  )  memset(  &pcMonRule,  0,  sizeof(  pcMonRule  )  );
	if  (  memcmp(  &pQwm->cfg.pcRules.pcMon,  &pcMonRule,  sizeof(  pcMonRule  )  )  )  {
		memcpy(  &pQwm->cfg.pcRules.pcMon,  &pcMonRule,  sizeof(  pcMonRule  )  );
		traceLogA(  "getQwmCfg(  ):  pcMonRule changed"  );
	}


	//  取qwm退出策略，2007/01/27, 服务进程设置，其他进程读取
	{
		unsigned  char  ucbStopMon_usrScript  =  bQwmUsrScriptQuit(  );
		if  (  pQwm->cfg.ucbStopMon_usrScript  !=  ucbStopMon_usrScript  )  pQwm->cfg.ucbStopMon_usrScript  =  ucbStopMon_usrScript;
	}

	//  
	getHostIp(  pQwm->hostname,  pQwm->localIp  );

	
	//  2007/02/04, 取实时操作指令
    QNM_CMDPARAM_getOpCmd	opCmdBuf;
	len  =  sizeof(  opCmdBuf  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_opCmd  ),  (  char  *  )&opCmdBuf,  &len  )  )  memset(  &opCmdBuf,  0,  sizeof(  opCmdBuf  )  );
	if  (  memcmp(  &pQwm->cfg.getOpCmd,  &opCmdBuf,  sizeof(  opCmdBuf  )  )  )  {
		memcpy(  &pQwm->cfg.getOpCmd,  &opCmdBuf,  sizeof(  opCmdBuf  )  );
		traceLogA(  "getQwmCfgg(  ):  getOpCmd changed"  );
	}

	//  2007/02/20, 目前只有服务进程采用进程隐藏技术
	unsigned  char  ucbHideQwm;
	ucbHideQwm  =  FALSE;
	if  (  !pQwm->cmd.ulbUsrScript  &&  pQwm->cfg.pcRules.os.ucHideQwmCmd  ==  CONST_devCmd_permitted  )  ucbHideQwm  =  TRUE;
	if  (  ucbHideQwm  !=  pQwm->cfg.ucbHideQwm  )  pQwm->cfg.ucbHideQwm  =  ucbHideQwm;


	#ifdef  __DEBUG__
			printQyWMon(  pQwm  );
	#endif


	iRet  =  0;
	
errLabel:

	if  (  bKeyOpen  )  RegCloseKey( hKey );
	   
	//Modified on 02/01/22 军版，全部禁止
	#ifdef  __FOR_ARMY__
			pQwm->cfg.ucRasCmd  =  CONST_rasCmd_prohibited;
	#endif
	
	if  (  iRet  )  traceLogA(  "Some error in getAsrWMonCfg(  )."  );

	//  return  iRet;
	return  0;

}




 int  initRasConn(  ASR_RAS_CONN_GRP  *  gRasConn  )
{
	memset(  gRasConn,  0,  sizeof(  ASR_RAS_CONN_GRP  )  );

	return  0;
}

 
 //  如下线程处理函数专门用于处理升级和保护程序自身等
 DWORD  WINAPI  qwmThreadProcFastCmd(  LPVOID  lpParameter  )
{
	 QWM_THREADINFO			threadInfo;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG			threadCfg;
	 QY_REG					reg;
	 char					cfgVal[1024];
	 TCHAR					tCfgVal[512];
	 FILETIME				ft;
	 int					loopCtrl;
	 unsigned  long			ulCurRand;
	 unsigned  long			len;
	 HKEY					hKey  =  NULL;
	 TCHAR					svName[MAX_PATH];
	 TCHAR					svTargetName[MAX_PATH],  *	svFilePart;
	 unsigned  long			cb;
	 TCHAR					regBuf[256];
	 DWORD					type;
	 	 
	 traceLogA(  "qwmThreadProcFastCmd enters"  );

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;
	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 lstrcpy(  reg.rootKey,  _T(  CONST_qyKey_qwm  )  );  
	 
	 GetSystemDirectory(  svName,  MAX_PATH  -  1  );
	 lstrcat(  svName,  _T(  "\\"  )  );
	 lstrcpyn(  svName  +  lstrlen(  svName  ),  pQwm->cfg.svTarget,  MAX_PATH  -  lstrlen(  svName  )  );
	 GetFullPathName(  svName,  MAX_PATH,  svTargetName,  &svFilePart  );

	 GetSystemTimeAsFileTime(  &ft  );
	 qySrand(  ft.dwLowDateTime  );
	 pQwm->ulRand  =  qyRand(  );

	 for  (  loopCtrl  =  0;  !pQwm->bQuit;  loopCtrl  ++  )  {
		  
		  //  traceLogA(  "qwmFastCmdThreadProc loops."  );

		  threadInfo.pCfg->nInterval  =  pQwm->cfg.nInterval_qwmThreadProcFastCmd;

		  reg.pEncCtx  =  &pQwm->encCtx;

		  if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_qwmCfgName_isOk  ),  (  char  *  )tCfgVal,  sizeof(  tCfgVal  )  )  )  {
			  traceLogA(  "qwmFastCmdThreadProc get CONST_qwmCfgName_isOk, cfgVal is [%s].",  tCfgVal  );
			  if  (  !lstrcmp(  tCfgVal,  _T(  CONST_qwmCfgVal_isOk  )  )  )  {
				  traceLogA(  "qwmFastCmdThreadProc answers,  okRes."  );
				  qySetRegCfgEx(  &reg,  _T(  CONST_qwmCfgName_isOkRes  ),  _T(  CONST_qwmCfgVal_isOkRes  )  );
			  }
			  qyDelRegCfg(  reg.rootKey,  _T(  CONST_qwmCfgName_isOk  )  );
		  }
 
		  if  (  !(  loopCtrl  %  pQwm->cfg.usGetRandIntervalLoops  )  )  {
			  traceLogA(  "qwmThreadProcFastCmd:  重取随机数"  );
			  pQwm->ulRand  =  qyRand(  );
		  }

		  Sleep(  threadInfo.pCfg->nInterval  );

		  reg.pEncCtx  =  &pQwm->encCtx;
		  
		  ulCurRand  =  0;
		  len  =  sizeof(  ulCurRand  );
		  if  (  qyGetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_rand  ),  (  char  *  )&ulCurRand,  &len  )  )  {
			  ulCurRand  =  0;
		  }
		  if  (  ulCurRand  !=  pQwm->ulRand  )  {
			  traceLogA(  "qwmThreadProcFastCmd: ulRand chaned,  ulCurRand is %d,  pQwm->ulRand is %d",  ulCurRand,  pQwm->ulRand  );
			  qySetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_rand  ),  (  char  *  )&pQwm->ulRand,  sizeof(  pQwm->ulRand  )  );
		  }
		 
		  reg.pEncCtx  =  &pQwm->quitEncCtx;
		  len  =  sizeof(  cfgVal  );
		  if  (  !qyGetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_cmdQuit  ),  (  char  *  )cfgVal,  &len  )  )  {
			  char	seqBuf[512  +  1]  =  "";  unsigned  long  seqLen;
			  unsigned  char  ucbSeqCorrect  =  FALSE;
			  //
			  seqLen  =  sizeof(  seqBuf  );
			  if  (  !qyGetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_qwmSeqNo  ),  seqBuf,  &seqLen  )  )  {
				  if  (  seqLen  >  sizeof(  seqBuf  )  -  1  )  seqLen  =  sizeof(  seqBuf  )  -1;
				  seqBuf[seqLen]  =  0;
				  memcpy(  &ulCurRand,  seqBuf,  sizeof(  ulCurRand  )  );
				  if  (  ulCurRand  ==  pQwm->ulRand  &&  !strnicmp(  pQwm->cfg.seqNo,  seqBuf  +  sizeof(  ulCurRand  ),  strlen(  pQwm->cfg.seqNo  )  )  )  {
					  traceLogA(  "序列号校验通过"  );
					  ucbSeqCorrect  =  TRUE;
				  }
			  }
				  
			  if  (   ucbSeqCorrect   )  {
				  traceLogA(  "qwmFastCmdThreadProc  get cmdQuit and seqBuf is %s",  seqBuf  +  sizeof(  ulCurRand  )  );
				  if  (  len  >  sizeof(  cfgVal  )  -  1  )  len  =  sizeof(  cfgVal  )  -  1;
				  cfgVal[len]  =  0;
				  memcpy(  &ulCurRand,  cfgVal,  sizeof(  ulCurRand  )  );
				  traceLogA(  "qwmFastCmdThreadProc pQwm->ul is %d, get ulCur is %d, secret is %s",  pQwm->ulRand,  ulCurRand,  cfgVal  +  sizeof(  ulCurRand  )  );
				  if  (  ulCurRand  ==  pQwm->ulRand  )  {
					  if  (  !memcmp(  cfgVal  +  sizeof(  ulCurRand  ),  CONST_qwmCfgVal_cmdQuit,  strlen(  CONST_qwmCfgVal_cmdQuit  )  )  )  {
						  traceLogA(  "qwm will quit soon."  );
						  pQwm->cfg.ucbQuitForUpdate  =  TRUE;
					  }
				  }
		  	  }

			  qyDelRegCfg(  reg.rootKey,  _T(  CONST_qwmCfgName_cmdQuit  )  );
			  qyDelRegCfg(  reg.rootKey,  _T(  CONST_qwmCfgName_qwmSeqNo  )  );	//  2005/06/25
			  if  (  pQwm->cfg.ucbQuitForUpdate  )  continue;
		  }

		  setQwmUsrScriptQuit(  0  );						//  2007/01/27, 防止有破坏性数据

		  if  (  !g_bIsWinNT  )  {
			  // 这一段代码为防止用户删除注册项.
			  if  (  RegCreateKey(  HKEY_LOCAL_MACHINE,  pQwm->env.svRunKey,  &hKey  )  ==  ERROR_SUCCESS  )  {
			  	  cb  =  sizeof(  regBuf  );
			  	  if  (  !(  RegQueryValueEx(  hKey,  pQwm->cfg.svTarget,  0,  &type,  (  unsigned  char  *  )regBuf,  (  unsigned  long  *  )&cb  )  ==  ERROR_SUCCESS
					  &&  !lstrcmp(  regBuf,  svTargetName  )  )  )
				  {
					  traceLogA(  "注册表被破坏"  );
					  RegSetValueEx(  hKey,  pQwm->cfg.svTarget,  0,  REG_SZ,  (  BYTE  *  )svTargetName,  lstrlen(  svTargetName  )  );
				  }
				  RegCloseKey(  hKey  );		  
		  	  }
			}
		  else  {
				DWORD	l  =  0;
				TCHAR	*  startValName  =  _T(  "Start"  );
			  
				_sntprintf(  regBuf,  mycountof(  regBuf  ),  _T(  "System\\CurrentControlSet\\Services\\%s"  ),  pQwm->cfg.serviceName  );
			  	if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  regBuf,  &hKey  )  ==  ERROR_SUCCESS  )  {
					cb  =  sizeof(  l  );
			    	if  (  RegQueryValueEx(  hKey,  startValName,  0,  &type,  (  unsigned  char  *  )&l,  &cb  )  !=  ERROR_SUCCESS  )  l  =  0;
					if  (  l  !=  2  )  {
						l  =  2;
						RegSetValueEx(  hKey,  startValName,  0,  REG_DWORD,  (  const  unsigned  char  *  )&l,  sizeof(  l  )  );
					}
					RegCloseKey(  hKey  );
				}
				
				if  (  !(  loopCtrl  %  6  )  )  {
					//
					chkAndRepairQwmService(  pQwm  );					//  2005/07/30, 增加对服务的校验修复工作
					//
					chkAndStartQwmLegacyService(  pQwm  );		//  2006/08/31, 增加对硬件配置文件的服务启用工作

				}

				if  (  !(  loopCtrl  %  60  )  )  {
					chkAndRepairQwmUsrScript(  pQwm  );
				}

		  }

		  
	 }

	 traceLogA(  "qwmThreadProcFastCmd leaves"  );

	 return  0;

}

extern  BOOL  g_bEradicate;

 int  loadQwmHelp2Dll(  QY_W_MON  *  pQwm,  TCHAR  *  pure2DllName  )
{
	int				iErr					=	-1;
	TCHAR			dllDir[MAX_PATH  +  1]	=	_T(  ""  );
	
	//  2007/01/15, 装载qwmHelp2.dll
	GetSystemDirectory(  dllDir,  mycountof(  dllDir  )  );
	trailDir(  dllDir,  mycountof(  dllDir  )  );
	lstrcpyn(  dllDir  +  lstrlen(  dllDir  ),  pQwm->pure2DllName,  mycountof(  dllDir  )  -  lstrlen(  pQwm->pure2DllName  )  );

	pQwm->hDll_help2  =  LoadLibrary(  dllDir  );		
	if  (  !pQwm->hDll_help2  )  goto  errLabel;
		
	//  pQwm->pf_getQwmGBuf  =  (  PF_getQwmGBuf  )GetProcAddress(  gQyWMon.hDll_help2,  "getQwmGBuf"  );
	//  pQwm->pf_setGBufSth  =  (  PF_setGBufSth  )GetProcAddress(  gQyWMon.hDll_help2,  "setGBufSth"  );

	iErr  =  0;

errLabel:
 
	traceLogA(  "loadQwmHelp2Dll return %s",  iErr  ?  "failed"  :  "OK"  );

	return  iErr;
}

 int  initAsrWMon(  QY_W_MON  *  pQwm  )
{
	int				iErr					=	-1;
	DWORD			dwThreadId;	
	int				i;
	TCHAR	*		remoteProcessName		=	_T(  CONST_remoteProcessName_sys  );
	QY_LOGICAL_SERVER		tmpCnt;

		
	traceLogA(  "initAsrWMon( ) enter."  );
	
	setTraceLogOpen(  TRUE  );		//  为Debug方便，2003/03/12添加这句话

	// 采用注入Explorer的方式时，曾经采用将Mutex的名字中加入ProcessId，不知当初出于什么考虑
	//  if  (  g_bIsWinNT  )  wsprintf( mutexName, "%s%lu", DEFAULT_qnmProxyMutexName,  GetCurrentProcessId(  )  );			

	pQwm->hMutex = CreateMutex(  NULL,  FALSE,  pQwm->cfg.mutexName  );
	if  (  !pQwm->hMutex  ||  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
		traceLogA(  "EntryPoint( ): CreateMutex( ) failed. Maybe another thread has been running, so this thread must be quit."  );
		goto  errLabel;
	}

	if  (  gethostname(  pQwm->hostname,  sizeof(  pQwm->hostname  )  )  )  pQwm->hostname[0]  =  0;
	if  (  qwmGetPcName(  pQwm->pcName,  sizeof(  pQwm->pcName  )  )  )  pQwm->pcName[0]  =  0;

	pQwm->bQuit  =  FALSE;
	//  pQwm->bRasOn  =  FALSE;
	//  pQwm->iStatus  =  AWM_STATUS_NORMAL;

	pQwm->hFile  =  INVALID_HANDLE_VALUE;
	pQwm->bLocked  =  FALSE;

	pQwm->bKeyUpdate  =  FALSE;
	pQwm->nCount  =  0;

	// 取得MAC地址
	getQwmMacs(  &pQwm->env,  &pQwm->macsInfo  );  

	if  (  !getCorrectCnt(  &gQyWMon.env,  &gQyWMon.cfg.dynCfg,  bServConnected,  0,  gQyWMon.iServiceId,  gQyWMon.ver,  &gQyWMon.commEncCtx,  &gQyWMon.cfg.to,  &tmpCnt  )  )  {
		if  (  memcmp(  &tmpCnt,  &gQyWMon.cfg.cnt,  sizeof(  gQyWMon.cfg.cnt  )  )  )  {
			memcpy(  &gQyWMon.cfg.cnt,  &tmpCnt,  sizeof(  gQyWMon.cfg.cnt  )  );
		}
	}
	//
	cfgQwmServIp(  &gQyWMon,  &gQyWMon.cfg.cnt  );
	memcpy(  &gQyWMon.server,  &gQyWMon.cfg.cnt,  sizeof(  gQyWMon.server  )  );


	//  先和管理端连通一下，看看有什么新的策略要求执行，呵呵, 2005/07/30
	retrieveQwmCfg(  pQwm  );
	if  (  getQwmCfg(  pQwm,  0  )  )  goto  errLabel;

	if  (  pQwm->cfg.ucbStopMon  )  {  //  2005/07/30，增加对这里初始从管理端取策略的处理
		traceLogA(  "一上来就接到了卸载命令，所以将马上卸载"  );
		g_bEradicate  =  TRUE;  goto  errLabel;
	}

	//  这里设置qwmHelp2.dll的版本是否正确的标志位, 2005/07/28
	//  if  (  !gQyWMon.pure2DllName[0]  )  _snprintf(  gQyWMon.pure2DllName,  sizeof(  gQyWMon.pure2DllName  ),  "%s",  CONST_qwmHelp2Dll  );  
	if  (  bMyHideSupportedOs(  gQyWMon.env.iPlatformId,  0,  0  )
		&&  bMyQwmHelpDllVerRight(  gQyWMon.env.iPlatformId,  gQyWMon.pure2DllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )
			&&  gQyWMon.cfg.ucbNetMc2  )  //  注意：只有内网管理才在这里启动保护线程
	{
		gQyWMon.status.ulbQwmHelp2VerRight  =  TRUE;  
	}

	if  (  gQyWMon.status.ulbQwmHelp2VerRight  )  {
		//  2007/01/15, 装载qwmHelp2.dll
		loadQwmHelp2Dll(  pQwm,  pQwm->pure2DllName  );
	}

	if  (  !pQwm->cmd.ulbUsrScript  )  {
		 traceLogA(  "设置让所有的qwmSvr相关的对象正常运行的标志位"  );
		 setQwmUsrScriptQuit(  0  );
	 }

	traceLogA(  "2005/07/28增加对远程保护线程的生成"  );
	//  启动保护线程
	myProcQwmHelp2(  &gQyWMon,  gQyWMon.env.iPlatformId,  gQyWMon.pure2DllName,  remoteProcessName  );
	
	// 下面采用进程隐藏来防杀
	if  (  pQwm->cfg.ucbHideQwm  )  {
		if  (  !myHideProcess(  pQwm->env.iPlatformId,  pQwm->pureDllName  )  )  pQwm->status.ulbProcessHiden  =  TRUE;
	}
	
	//  2005/05/29, 由于有某些工作需要重起，所以对重起前没有结束的工作，在这里继续完成
	procPcNetworkPropChangeAtStart(  pQwm  );


	if  (  g_bIsWinNT  )  {	//  2007/02/27, 3。32。*版曾经引入run键值的qyApp, 后又放弃，故这里做清除
		traceLogA(  "下面删除%s下的%s",  pQwm->env.svRunKey,  CONST_regValName_qwmUsrScript  );	
		char					buf[512]		=	"";
		if  (  !qyGetRegCfg(  gQyWMon.env.svRunKey,  _T(  CONST_regValName_qwmUsrScript  ),  buf,  sizeof(  buf  )  )  )  {
			qyDelRegCfg(  gQyWMon.env.svRunKey,  _T(  CONST_regValName_qwmUsrScript  )  );
		}
	}


	if  (  !(  pQwm->hThreads[0]  =  CreateThread(  NULL,  0,  qwmThreadProcFastCmd,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
	if  (  pQwm->cfg.ulbQwmThreadProcCmd  )  {
		if  (  !(  pQwm->hThreads[1]  =  CreateThread(  NULL,  0,  qwmThreadProcCmd,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
	}
	i  =  2;
	if  (  pQwm->cfg.ulbQwmThreadPrinterMgr  )  {
		if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadPrinterMgr,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
		i  ++  ;
	}
	if  (  pQwm->cfg.ulbQwmThreadFileMon  )  {
		if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadFileMon,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
		i  ++  ;
	}
	if  (  !g_bIsWinNT  )  {	//  2007/01/27, 98才在主控进程里做所有的工作。在NT系列，用户进程来处理屏幕监控等工作
		if  (  pQwm->cfg.ulbQwmThreadPcMon  )  {		//  2006/03/05
			if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadPcMon,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
			i  ++  ;
		}
	}
	if  (  g_bIsWinNT  )  {
		if  (  pQwm->cfg.ulbQwmThreadCollectUsrLog  )  {	//  2007/02/18
			if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadCollectUsrLog,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
			i  ++  ;	
		}
		if  (  pQwm->cfg.ulbQwmThreadWndProc  )  {			//  2007/02/27
			if  (  !(  pQwm->hThreads[i]  =  CreateThread(  NULL,  0,  qwmThreadWndProc,  (  LPVOID  )pQwm,  0,  &dwThreadId  )  )  )  goto  errLabel;
			i  ++  ;	
		}
	}

	MACRO_qyAssert(  i  <  sizeof(  pQwm->hThreads  )  /  sizeof(  pQwm->hThreads[0]  ),  _T(  "initAsrWMon failed"  )  );

	//

#ifdef  __DEBUG__
	testInitQwmHook(  );   
#endif

	//  锁本文件
	if  (  g_bIsWinNT  )  {
		
		TCHAR svName[MAX_PATH];
		TCHAR svTargetName[MAX_PATH],*svFilePart;
		TCHAR *svTarget  =  NULL;
		
		if  (  gQyWMon.iAppType  ==  CONST_qyAppType_qwmSvr  )  svTarget  =  _T(  CONST_qwmSvr_runtimePathName  );
		else  svTarget  =  _T(  CONST_qnmProxy_runtimePathName  );
		
		GetSystemDirectory(svName,MAX_PATH-1);
		lstrcat(svName,_T(  "\\"  )  );
		lstrcpyn(svName+lstrlen(svName),svTarget,MAX_PATH-lstrlen(svName));
		GetFullPathName(svName,MAX_PATH,svTargetName,&svFilePart);		
				
		gQyWMon.hFile  =  CreateFile( svTargetName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
		traceLogA(  "Locking file %s %s",  svTargetName,  gQyWMon.hFile  ==  INVALID_HANDLE_VALUE  ?  "failed"  :  "succeeded"  );
	

		//  锁配置文件防止其他写, 2006/3/22
		_sntprintf(  svName,  mycountof(  svName  ),  _T(  "%s\\%s"  ),  gQyWMon.wSystemDir,  _T(  CONST_qwmCfgFile  )  );
		gQyWMon.hCfgFile  =  CreateFile(  svName,  GENERIC_READ  |  GENERIC_WRITE,  FILE_SHARE_READ,  NULL,  OPEN_ALWAYS,  FILE_ATTRIBUTE_NORMAL,  NULL  );  


		//  2006/03/22
		getFileMonRules(  &gQyWMon  );

	}

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		
		exitAsrWMon(  pQwm  );
		
	}
	traceLogA(  "initAsrWMon( ) leaves, with iErr is %d.",  iErr  );

	return iErr;

}



  void  exitAsrWMon(  QY_W_MON  *  pQwm  )
{
	 int  i;

	 if  (  !pQwm->cmd.ulbUsrScript  )  {
		 traceLogA(  "设置让所有的qwmSvr相关的对象退出的标志位"  );
		 setQwmUsrScriptQuit(  TRUE  );		//  2007/01/15
	 }

	 pQwm->bQuit  =  TRUE;		//  然后让自己也退出

	 for  (  i  =  0;  i  <  sizeof(  pQwm->hThreads  )  /  sizeof(  pQwm->hThreads[0]  );  i  ++  )  {
		  if  (  pQwm->hThreads[i]  )  {
			  WaitForSingleObject(  pQwm->hThreads[i],  INFINITE  );	
			  CloseHandle(  pQwm->hThreads[i]  );  pQwm->hThreads[i]  =  NULL;
		  }
	 }

	 if  (  !pQwm->cmd.ulbUsrScript  )  {	//  再次设置是为了防止有线程在没退出时将标志位改了
		 traceLogA(  "设置让所有的qwmSvr相关的对象退出的标志位"  );
		 setQwmUsrScriptQuit(  TRUE  );		//  2007/01/15
	 }

	 //////////////////////////////

	 if  (  isHandleValid(  pQwm->hCfgFile  )  )  {	//  2006/03/22
		 CloseHandle(  pQwm->hCfgFile  );  pQwm->hCfgFile  =  NULL;
	
		 if  (  !pQwm->cmd.ulbUsrScript  )  {
			 delHelpFile(  _T(  CONST_qwmCfgFile  )  );
		 }
	 }
	 

	 if  (  pQwm->hFile  !=  INVALID_HANDLE_VALUE  &&  pQwm->hFile  )  {
		 if  (  pQwm->bLocked  )  UnlockFile(  pQwm->hFile,  0,  0,  0,  0  );
		 CloseHandle(  pQwm->hFile  ); pQwm->hFile  =  INVALID_HANDLE_VALUE;
	 }
	 
	 if  (  pQwm->status.ulbProcessHiden  )  {	//  2004/10/25
		 myShowProcess(  pQwm->env.iPlatformId,  pQwm->pureDllName  );	 pQwm->status.ulbProcessHiden  =  FALSE;
	 }
	 //  2005/07/28增加对远程线程的处理
	 myClearQwmHelp2(  pQwm  );  

	 if  (  pQwm->hMutex  )  {  CloseHandle(  pQwm->hMutex  );  pQwm->hMutex  =  NULL;  }
	
	 return;

}



