
#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"resource.h"
#include	"qnmAssetsCommProc.h"
#include	"qyRegToolProc.h"


/*
int Cmd_FileXfer_Init(void)
{
	return 0;
}

int Cmd_FileXfer_Kill(void)
{
	return 0;
}

int Cmd_Buttplugs_Init( void ) 
{
	return 0;
}

int Cmd_Buttplugs_Kill( void )
{
	return 0;
}

 void Cmd_Tcpip_Init( void )
{
}

 void Cmd_Tcpip_Kill( void )
{
}
*/


 //  2005/01/25加
 void  setProgressTxt(  QY_REG_TOOL  *  pRegTool,  BOOL  bFailed  )
{
	 return;
}

 //  2005/05/03
 extern  "C"  BOOL  bSetQrtProgressTxt1(  TCHAR  *  txt  )
{
	 return  TRUE;
}



#ifdef  __DEBUG__

 #ifdef UNICODE 
 
#define atoi    atoiW 
 
//  atoiW() - Unicode version of atoi. 

INT atoiW (LPTSTR s) 
{ 	
	INT i = 0; 
	
	while (iswdigit (*s)) { 
		i = i*10 + (BYTE)*s - L'0'; 
        s++; 
	} 
	
    return i; 
} 
 
#endif 

  BOOL  myControlDisk(  int  nIndex,  int  nStatus  );
 BOOL  bTmpGetMyVer(  TCHAR  *  hideProcessDll,  char  *  ver0,  unsigned  int  size  );

	
 //  此函数将改造成最终的注册函数。在调用此函数前，如由下载软件生成qwm并弹出界面，
 //  为确保安装成功，应在下载软件里判断用户是否属于Administrators组，参见qyRegTool



 extern "C" int testInitQwmHookInMain( )
{	
	 //  int  i;
//  errLabel:
	 QWM_THREADINFO		threadInfo;


	 traceLogA(  "testInitQwmHookInMain enters"  );

	 int  i;
	 i  =  sizeof(  GUID  );
	 i  =  sizeof(  QWM_DEV_INFO  );

	 TCHAR	tBuf[256];
	 qwmGetSystemDirectory(  &gQyWMon.env,  tBuf,  mycountof(  tBuf  )  );

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 threadInfo.pParaentParam  =  &gQyWMon;
	 
	 QY_REG	reg;
	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 lstrcpy(  reg.rootKey,  _T(  CONST_qyKey_qwm  )  );  

	 reg.pEncCtx  =  &gQyWMon.encCtx;

	 int  ii  =  sizeof  (  QWM_EVENT  );

#if  10
	 char  *  pCfgVal_utf8  =  CONST_qwmCfgVal_isOkRes;
	 
	 if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_qwmCfgName_isOkRes  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  ) 
	 {
		 int  i;
		 i  =  8;

	 }

	 //  qySetRegCfgEx(  &reg,  _T(  "kk"  ),  _T(  CONST_qwmCfgVal_isOkRes  )  );
#endif

	 QY_LOGICAL_SERVER	cnt;
	 getQwmServIpCfg(  &gQyWMon,  &cnt  );

	 unsigned  long	ulRand  =  0;
	 int  len  =  sizeof(  ulRand  );
	 qyGetRegDataEx(  &reg,  _T(  CONST_qwmCfgName_rand  ),  (  char  *  )&ulRand,  (  unsigned  long  *  )&len  );

	 //  qySetRegDataEx(  &reg,  _T(  "mm1"  ),  (  char  *  )&ulRand,  sizeof(  ulRand  )  );

errLabel:

	 traceLogA(  "testInitQwmHookInMain leaves"  );

	 
	 return  0;
}






////////////////////////////////////////////////////////////////  















 extern "C" int testInitQwmHook( )
{
	
	return 0;
}



#endif

#ifdef  __TEST__
 extern "C" int testQwmHook( )
{
	 QY_W_MON			tmpQwm;
	 unsigned  int				i,  j;
	 //  typedef  struct  __qwmMacsInfo_t  {
	 //			 unsigned  char				macs[3][12  +  1];
	 //			 unsigned  char				nMacs;
	 //  }		 QWM_MACS_INFO;
	 QWM_MACS_INFO		macsInfo;
	 char				buf[128];
	 unsigned  int		nSendTimes;

	 memcpy(  &tmpQwm,  &gQyWMon,  sizeof(  QY_W_MON  )  );

	 if  (  qyGetRegCfg(  CONST_qyRootKey_test,  CONST_regValName_testQwmCntIp,  tmpQwm.server.ip,  sizeof(  tmpQwm.server.ip  )  )  )  {
		 safeStrnCpy(  "127.0.0.1",  tmpQwm.server.ip,  sizeof(  tmpQwm.server.ip  )  );
	 }
	 tmpQwm.server.port  =  8766;
	 if  (  !qyGetRegCfg(  CONST_qyRootKey_test,  CONST_regValName_testQwmSendTimes,  buf,  sizeof(  buf  )  )  )  {
		 nSendTimes  =  atol(  buf  );
		}
	 else  nSendTimes  =  (  unsigned  int  )-1;
		
	 traceLogA(  "qwmSvr.exe测试发送数据 %u次 到 %s:%d",  nSendTimes,  tmpQwm.server.ip,  tmpQwm.server.port  );

	 for  (  i  =  0,  j  =  0;  i  <  nSendTimes;  i  ++  ,  j  ++  )  {
		  macsInfo.nMacs  =  (  j  %  2  )  +  1;
		  wsprintf(  (  char  *  )macsInfo.macs[0],  "%010dAA",  i  );
		  wsprintf(  (  char  *  )macsInfo.macs[1],  "%010dBB",  i  );
		  wsprintf(  (  char  *  )macsInfo.macs[2],  "%010dCC",  i  );
		  memcpy(  &tmpQwm.macsInfo,  &macsInfo,  sizeof(  QWM_MACS_INFO  )  );

		  testQwmRetrieveCfg(  &tmpQwm  );

	 }
	 
	 return  0;

}

 int  testQwmRetrieveCfg(  QY_W_MON  *  pQwm  )
{
	int						iErr		=		-1;
	ASR_SOCK				aS;
	int						i			=		0;
	char					ip[16];
	QNM_COMM_AUTHINFO		authInfo;
	QWM_SESSION				session;
	QY_COMM_RESP			tmpResp;
	char					cfgsBuf[8192];
	//  unsigned  int			len;
	//  unsigned  int			size;
	//  QY_CFGITEM			*	pItem;
	//  char				*	ptr;
	
	traceLogA(  "enter retrieveQwmCfg."  );

	//  取得MAC地址
	if  (  !pQwm->macsInfo.nMacs  &&  ghDll_NetApi32  )  {
		getQwmMacs(  &pQwm->macsInfo  );
	}

	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
		
	if  (  asrConnect(  pQwm->server.ip,  pQwm->server.port,  pQwm->cfg.to.iConnect,  &aS  )  )  goto  errLabel;
	if  (  getLocalIpBySocket(  aS.sockFd,  ip  )  )  goto  errLabel;
	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	if  (  makeQwmAuthInfo(  pQwm->ver,  &pQwm->macsInfo,  &authInfo  )  )  goto  errLabel;
	memcpy(  authInfo.ip,  ip,  sizeof(  authInfo.ip  )  );

	if  (  qyTellService(  pQwm->serviceId,  pQwm->ver,  (  char  *  )&authInfo,  sizeof(  authInfo  ),  &aS,  &pQwm->cfg.to,  &session.comm  )  )  goto  errLabel;
	if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;

	if  (  isRcQuit(  tmpResp.head.usCode  )  )  {
		pQwm->bQuit  =  TRUE;  goto  errLabel;		//  程序退出，删除执行路径run , runservices
	}

	if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;
	
	if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_getCfgs,  NULL,  0  )  )  goto  errLabel;
	if  (  qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	
	if  (  qySendReq(  &session.comm,  &aS,  &pQwm->cfg.to,  CONST_qyCmd_end,  NULL,  0  )  )  goto  errLabel;
	qyRecvResp(  &session.comm,  &aS,  &pQwm->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  );
	
	iErr = 0;
	
errLabel:

	if  (  bQySockOpen(  &aS  )  )  qyDisconnect(  &aS  );

	traceLogA(  "leave retrieveQwmCfg."  );

	return  iErr;

}

#endif


#ifndef  __WITHOUT_DEBUG_LOG__	//  {

 extern  "C"  void  printQyWMon(  void  *  pQwmParam  )
{
	static  int	i		=	0;  i  ++  ;  if  (  (  i  %  5  )   )  return;  
	
	QY_W_MON  *  pQwm  =  (  QY_W_MON  *  )pQwmParam;
	
	traceLog(  _T(  "Start to print qyWMon ..."  )  );
	//  traceLogA(  "	platformId is %d",  pQwm->env.iPlatformId  );
	//  traceLogA(  "	cntIp is [%s], cntPort is [%d]",  pQwm->cfg.cnt.ip,  pQwm->cfg.cnt.port  );
	//  traceLogA(  "	tmpCntIp is [%s], tmpCntPort is [%d]",  pQwm->cfg.tmpCnt.ip,  pQwm->cfg.tmpCnt.port  );
#if  10
	traceLog(  _T(  "	floppy is %s, cdrom is %s, usb is %s"  ),  
		qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucFloppyCmd  ),   
		qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucCdromCmd  ),    
		qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucUsbStorCmd  )  );
	traceLog(  _T(  "	wLanAdapter %s"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucWLanAdapterCmd  )  );
	traceLog(  _T(  "	blue tooth %s"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucBlueToothCmd  )  );
	traceLog(  _T(  "	infrared %s"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucInfraredCmd  )  );
	traceLog(  _T(  "	1394 %s"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.uc1394Cmd  )  );

	traceLog(  _T(  "	usbNetworkCard %s"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.dev.ucUsbNetworkCardCmd  )  );

	//  traceLogA(  "	timeout:  iConnect is %d, iAccept is %d, iRead is %d, iWrite is %d",  pQwm->cfg.to.iConnect,  pQwm->cfg.to.iAccept,  pQwm->cfg.to.iRead,  pQwm->cfg.to.iWrite  );
	//  traceLogA(  "	rasCmd is  [%s], %s 检测非法外联",  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmRasCmdTable  ),  pQwm->cfg.pcRules.ras.ucRasCmd  ),  (  pQwm->cfg.pcRules.ras.ucbNotChkOnInternet  ?  "不"  :  ""  )  );
	//  traceLogA(  "	远程上网报警 is [%s], interMon ip is [%s], port is %d",  qyGetDesByType1(  CONST_qnmDevCmdTable0,  pQwm->cfg.pcRules.ras.ucWarnToInternetCmd  ),  pQwm->cfg.interMon.ip,  pQwm->cfg.interMon.port  );
	traceLog(  _T(  "	%s"  ),  pQwm->cfg.pcRules.secChk.ucbDoSecChk  ?  _T(  "DoSecChk"  )  :  _T(  ""  )  );

	traceLog(  _T(  "	%s autorun"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.os.ucAutorunCmd  )  );  
	traceLog(  _T(  "	%s netShareCmd"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.os.ucNetShareCmd  )  );  
	traceLog(  _T(  "	%s safeMode"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.os.ucSafeModeCmd  )  );  
	traceLog(  _T(  "	%s adminCmd"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.os.ucAdminCmd  )  );  
	
	traceLog(  _T(  "	%s sndEventLog"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.osAudit.ucSndEventLogCmd  )  );
	traceLog(  _T(  "	%s sndUsrInfo"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.osAudit.ucSndUsrInfoCmd  )  );
	traceLog(  _T(  "	%s watchPrinter"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.osAudit.ucWatchPrinterCmd  )  );
	traceLog(  _T(  "	%s sndNetStat"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.osAudit.ucSndNetStatCmd  )  );
	traceLog(  _T(  "	%s sndModuleInfo"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.osAudit.ucSndModuleInfoCmd  )  );
	traceLog(  _T(  "	%s capScreen, interval is %d"  ),  qyGetDesByType1(  CONST_qnmDevCmdTable0_en,  pQwm->cfg.pcRules.pcMon.ucCapScreenCmd  ),  pQwm->cfg.pcRules.pcMon.usCapScreenInterval  );  
	traceLog(  _T(  "	opCmd: bOped is %d, bRd is %d, bMon is %d"  ),  pQwm->cfg.getOpCmd.ucbOped,  pQwm->cfg.getOpCmd.ucbViewRemoteDesktop,  pQwm->cfg.getOpCmd.ucbMonDesktop  );
#endif

	//
	traceLog(  _T(  "	server ip is [%S], port is %d, seqNo [%s]"  ),  pQwm->server.ip,  pQwm->server.port,  pQwm->cfg.seqNo  );
	traceLog(  _T(  "	bQuit %s, ucbStopMon is %d"  ),  pQwm->bQuit  ?  _T(  "true"  ) :  _T(  "false"  ),  pQwm->cfg.ucbStopMon  );
	
	//
	traceLog(  _T(  "	server is %s"  ),  pQwm->status.common.ucbServerOnline  ?  _T(  "online"  )  :  _T(  "offline"  )  );

	traceLog(  _T(  "End printing qyWMon."  )  );
	
	return;

}

 extern  "C"  int  printQwmEvent(  TCHAR  *  hint,  QWM_EVENT  *  pEvent  )
{
	 char	displayBuf[256];

	 if  (  !hint  )  hint  =  _T(  ""  );

	 qyDisplayTime(  pEvent->localEventTime,  displayBuf,  sizeof(  displayBuf  )  );
	 switch  (  pEvent->eventType  )  {
			 case  CONST_qyEventType_nm_rasStart:
			 case  CONST_qyEventType_nm_rasEnd:
			 case  CONST_qyEventType_nm_rasProhibited:
				   //  traceLogA(  "qwmEvent %s %d %s %s %s %s",  hint,  pEvent->eventType,  pEvent->usrName,  displayBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmRasCmdTable  ),  pEvent->u.ras.ucRasCmd  ),  pEvent->u.ras.fullPhoneNum  );
				   break;
			 default:
					traceLogA(  "qwmEvent %s %d %s %s %s %s",  hint,  pEvent->eventType,  pEvent->usrName,  displayBuf,  pEvent->u.comments[0],  pEvent->u.comments[1]  );
					break;
					
	 }

	 return  0;
}

 int  printRegLogs(  )
{
	 int			iErr			=		-1;
	 QY_REG			tmpReg;
	 DWORD			dwcVals			=		0;
	 DWORD			dwcPtrs			=		0;
	 char			buf[128];
	 HKEY			hKey			=		NULL;
	 BOOL			bKeyOpen		=		FALSE;
	 DWORD			j;   
	 DWORD			retValue;   
	 DWORD			dwcValueName;
	 TCHAR			valueName[256];
	 char			data[2048];
	 DWORD			cbData;
	 QWM_EVENT		event;

	 traceLogA(  "showRegLogs enters"  );
	 
	 memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
	 lstrcpyn(  tmpReg.rootKey,  _T(  CONST_qyKey_qwmLog  ),  mycountof(  tmpReg.rootKey  )  );
	 tmpReg.pEncCtx  =  &gQyWMon.encCtx;
	 
	 dwcVals  =  getKeyValsCnt(  HKEY_LOCAL_MACHINE,  tmpReg.rootKey  );
	 
	 if  (  !qyGetRegCfg(  tmpReg.rootKey,  _T(  CONST_qwmLogPtr  ),  buf,  sizeof(  buf  )  )  )  {
		 dwcPtrs  ++  ;
	 }
	 if  (  dwcVals  <=  dwcPtrs  )  {  
		 iErr  =  0;  goto  errLabel;  
	 }
	 
	 if  (  ERROR_SUCCESS  !=  RegOpenKey(  HKEY_LOCAL_MACHINE,  tmpReg.rootKey,  &hKey  )  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 for  (  j  =  0;  j  <  dwcVals ;  j  ++  )  {
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
		  
		  if  (  !lstrcmpi(  valueName,  _T(  CONST_qwmLogPtr  )  )  )  continue;
		  if  (  qyGetRegDataEx(  &tmpReg,  valueName,  data,  &cbData  )  )  {
			  traceLogA(  "showRegLogs, qyGetRegDataEx failed, 一条错误日志"  );
			  continue;
		  }

		  memset(  &event,  0,  sizeof(  event  )  );
		  memcpy(  &event,  data,  min(  sizeof(  event  ),  cbData  )  );
		  printQwmEvent( valueName,  &event  );		  
		  
	 }

	 iErr  =  0;

errLabel:
	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 traceLogA(  "showRegLogs leaves"  );

	 return  0;

}



#endif	//  }  生效 if __WITHOUT_DEBUG_LOG__ not defined
//  将临时为Debug用的函数放在上面


