
#include	<windows.h>
#include	<ras.h>
#include	<raserror.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	<commnet.h>
#include	<commandloop.h>
#include	<config.h>
#include	"resource.h"
#include	"asrWMon.h"
#include	"rasConn.h"
#include	"main.h"

extern BOOL g_bIsWinNT;

// ---------------- Global variables ----------------
//  CIOHandler *g_pIOHandler;
// CEncryptionHandler *g_pEncryptionHandler;
// CAuthHandler *g_pAuthHandler;

// CAuthSocket *g_pCommSock[MAX_COMMAND_SOCKETS];
// CAuthSocket *g_pConnSock[MAX_COMMAND_CONNECTIONS];
// int g_nCommCount, g_nConnCount;


#ifdef NDEBUG
char g_szStartupOptions[]=	"<**CFG**>Startup\0"
							"S[8]:Init Cmd Net Type=TCPIO\0\0\0\0"
						    "S[48]:Init Cmd Bind Str=\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
						    "S[8]:Init Cmd Encryption=XOR\0\0\0\0\0\0"
						    "S[8]:Init Cmd Auth=NULLAUTH\0"
						    "N[0,5000000]:Idle Timeout (ms)=60000\0\0";
#else
char g_szStartupOptions[]=	"<**CFG**>Startup\0"
							"S[8]:Init Cmd Net Type=TCPIO\0\0\0\0"
						    "S[48]:Init Cmd Bind Str=54320\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
						    "S[8]:Init Cmd Encryption=XOR\0\0\0\0\0\0"
						    "S[8]:Init Cmd Auth=NULLAUTH\0"
						    "N[0,5000000]:Idle Timeout (ms)=60000\0\0";
#endif

BOOL g_bBO2KFinished;		// Set this to -TRUE- when you want to exit BO2K

// ---------------- Function implementations --------------------



 //  2007/02/10, 由系统进程来将管理端是否连通入注册表，由各用户进程来读取
 int  getQwmCommonStatus(  QY_W_MON  *  pQwm,  QWM_COMMON_STATUS  *  pCommonStatus  )
{
	int					iErr		=	-1;
	QY_REG				reg;
	DWORD				len;

	if  (  !pCommonStatus  )  goto  errLabel;

	memset(  &reg,  0,  sizeof(  reg  )  );
	lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  reg.rootKey  )  );
	reg.pEncCtx  =  &pQwm->encCtx;

	memset(  pCommonStatus,  0,  sizeof(  pCommonStatus[0]  )  );
	len  =  sizeof(  pCommonStatus[0]  );
	if  (  qyGetRegDataEx(  &reg,  _T(  CONST_regValName_qwmCommonStatus  ),  (  char  *  )pCommonStatus,  &len  )  )  memset(  pCommonStatus,  0,  sizeof(  pCommonStatus[0]  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}
 

 int  setQwmCommonStatus(  QY_W_MON  *  pQwm  )  
{
	int					iErr	=	-1;
	QY_REG				reg;
	QWM_COMMON_STATUS	commonStatus;

	if  (  getQwmCommonStatus(  pQwm,  &commonStatus  )  )  goto  errLabel;
	if  (  !memcmp(  &pQwm->status.common,  &commonStatus,  sizeof(  pQwm->status.common  )  )  )  {
		iErr  =  0;  goto  errLabel;
	}
	 
	memset(  &reg,  0,  sizeof(  reg  )  );
	lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  reg.rootKey  )  );
	reg.pEncCtx  =  &pQwm->encCtx;

	if  (  qySetRegDataEx(  &reg,  _T(  CONST_regValName_qwmCommonStatus  ),  (  char  *  )&pQwm->status.common,  sizeof(  pQwm->status.common  )  )  )  goto  errLabel;
	iErr  =  0;
errLabel:
	return  iErr;
}


 //  下面处理函数用于与服务器同步策略、发送日志等,  以及，对程序运行作出决策。
 void  commandHandlerLoop(  void  )
{
	DWORD					dwLastTime,  dwTimeout;
	BOOL					bIdle;
	int						loopCtrl				=	0;
	int						i  =  0,  iRet  =  0;
	DWORD					dwThreadId  =  0;
	unsigned  char			ucbCfgRetrieved			=	FALSE;
	//
	QWM_THREADINFO			threadInfo;
	QWM_THREAD_CFG			threadCfg;
	unsigned  char			ucbPcChked				=	FALSE;
	unsigned  char			ucbProcessJustSnt		=	FALSE;
	QY_LOGICAL_SERVER		tmpCnt;

	traceLogA(  "CommandHandlerLoop( ) enter."  );

	memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	threadInfo.pParaentParam  =  &gQyWMon;
	threadInfo.pCfg  =  &threadCfg;


	if  (  initAsrWMon(  &gQyWMon  )  )  {  
		traceLogA(  "initAsrWMon( ) failed."  );
		return;
	}
	
	// Lower Thread Priority
	SetThreadPriority(  GetCurrentThread(  ),  THREAD_PRIORITY_NORMAL  );

	// Command handler loop
	g_bBO2KFinished  =  FALSE;
	dwLastTime  =  GetTickCount(  );
	dwTimeout  =  CONST_qnmProxy_idleTimeout;
	bIdle  =  FALSE;
	

	//检测注册表是否可写,没用	
	{
		HKEY  hKey  =  NULL;
		long  lRet;
		lRet  =  RegOpenKey(  HKEY_LOCAL_MACHINE,  _T(  ROOT_KEY_AWM  ),  &hKey  );
		if  (  lRet  ==  ERROR_SUCCESS  )  {
			if  (  RegSetValueEx(  hKey,  _T(  "bu"  ),  0,  REG_SZ,  (  unsigned  char  *  )_T(  "1"  ),  sizeof(  TCHAR  )  )  ==  ERROR_SUCCESS  )
				gQyWMon.bKeyUpdate  =  TRUE;
			RegCloseKey(  hKey  );  hKey  =  NULL;
		}
		if (  !gQyWMon.bKeyUpdate  )  traceLogA(  "CommandHandlerLoop() write reg failed."  );
	}

	
	#ifdef  __TEST__
		testQwmHook(  );  goto  errLabel;
	#endif

	
	//  2006/04/14, 这里把loopCtrl从CONST_qwmConnectIntervalLoops开始，可以避免在loopCtrl为0时，触发所有的上传事件
	//  同时，也一开始就触发retrieveQwmCfg的动作
	for  (  loopCtrl  =  CONST_qwmConnectIntervalLoops;  !g_bBO2KFinished;  loopCtrl  ++  )  {
	 		 
		 if  (  dwTimeout  !=  0  )  {
			 if  (  !bIdle  &&  (  (  GetTickCount(  )  -  dwLastTime  )  >  dwTimeout  )  )  {
				 SetPriorityClass(  GetCurrentProcess(  ),  IDLE_PRIORITY_CLASS  );
				 SetThreadPriority(  GetCurrentThread(  ),  THREAD_PRIORITY_IDLE  );
				 bIdle  =  TRUE;
			 }
		 }

		 Sleep(  gQyWMon.cfg.nInterval_CommandHandlerLoop  );


		 if  (  loopCtrl  >  20  &&  !ucbPcChked  )  {		//  检查一次pc信息, 包括补丁信息, 2004/11/15
			  doSecChk(  &threadInfo,  NULL  );  ucbPcChked  =  TRUE;
		 }
		 
		 ucbCfgRetrieved	=	FALSE;

		 //  2006/07/01, 定期检查管理端，看是否管理端的IP需要重新调整
		 if  (  (  !gQyWMon.status.common.ucbServerOnline  &&  !(  loopCtrl  %  gQyWMon.cfg.usFindCntIntervalLoops  )  )
			||  (  gQyWMon.status.common.ucbServerOnline  &&  !(  loopCtrl  %  1000  )  )  )
		 {		
			 if  (  !getCorrectCnt(  &gQyWMon.env,  &gQyWMon.cfg.dynCfg,  bServConnected,  0,  gQyWMon.iServiceId,  gQyWMon.ver,  &gQyWMon.commEncCtx,  &gQyWMon.cfg.to,  &tmpCnt  )  )  {
				 if  (  memcmp(  &tmpCnt,  &gQyWMon.cfg.cnt,  sizeof(  gQyWMon.cfg.cnt  )  )  )  {
					 memcpy(  &gQyWMon.cfg.cnt,  &tmpCnt,  sizeof(  gQyWMon.cfg.cnt  )  );
					 traceLogA(  "管理端IP又发生了变化，指向了%s:%d",  gQyWMon.cfg.cnt.ip,  gQyWMon.cfg.cnt.port  );
					 //
					 cfgQwmServIp(  &gQyWMon,  &gQyWMon.cfg.cnt  );
					 memcpy(  &gQyWMon.server,  &gQyWMon.cfg.cnt,  sizeof(  gQyWMon.server  )  );
				 }
			 }
			 ucbCfgRetrieved  =  TRUE;
		 }

		 if  (  !(  loopCtrl  %  30  )  )  {	//  2007/02/21, 检查注册表中信息，以防止被他人篡改注册表的服务器设置
			 memcpy(  &tmpCnt,  &gQyWMon.cfg.cnt,  sizeof(  tmpCnt  )  );
			 if  (  getQwmServIpCfg(  &gQyWMon,  &tmpCnt  )  )  memset(  &tmpCnt,  0,  sizeof(  &tmpCnt  )  );
			 if  (  memcmp(  &tmpCnt,  &gQyWMon.cfg.cnt,  sizeof(  tmpCnt  )  )  )  {
				 traceLogA(  "Warning: cnt Ip is changed unexpectedly."  );
				 cfgQwmServIp(  &gQyWMon,  &gQyWMon.cfg.cnt  );
			 }
		 }

		 if  (  gQyWMon.cfg.ulbRetrieveQwmGlCntIp  &&  !(  loopCtrl  %  gQyWMon.cfg.usQueryGlCntIpIntervalLoops  )  )  {
		  	 retrieveQwmGlCntIp(  &gQyWMon  );		ucbCfgRetrieved  =  TRUE;
		  	 getQwmCfg(  &gQyWMon,  0  );
		 }

		 if  (  gQyWMon.cfg.ulbRetrieveQwmCfg  &&  !(  loopCtrl  %  gQyWMon.cfg.usConnectIntervalLoops  )  )  {
		  	 retrieveQwmCfg(  &gQyWMon  );			ucbCfgRetrieved  =  TRUE;
		  	 getQwmCfg(  &gQyWMon,  0  );				//  含有检测四个月2002-04-12 00：00：00到期作废			 
			 //			 
		 }

		 traceLogA(  "ulbRetrieveQnmProxyCfg is %d,  loopCtrl is %d,  usConnectIntervalLoops is %d",  gQyWMon.cfg.ulbRetrieveQnmProxyCfg,  loopCtrl,  gQyWMon.cfg.usConnectIntervalLoops  );

		 if  (  gQyWMon.cfg.ulbRetrieveQnmProxyCfg  &&  !(  loopCtrl  %  gQyWMon.cfg.usConnectIntervalLoops  )  )  {
		 	 retrieveQnmProxyCfg(  &gQyWMon  );		ucbCfgRetrieved  =  TRUE;
		  	 getQwmCfg(  &gQyWMon,  0  );				//  含有检测四个月2002-04-12 00：00：00到期作废			 
		 }

		 //  2006/03/22
		 if  (  gQyWMon.cfg.ulbQwmThreadFileMon  &&  !(  loopCtrl  %  gQyWMon.cfg.usQueryCfgsIntervalLoops  )  )  {
			 //  retrieveQwmOtherCfgs(  &gQyWMon  );		//  2006/08/15, 将函数名换了一下
			 queryCfgs(  &gQyWMon  );
		 }

		 #ifdef  __DEBUG__
				 if  (  ucbCfgRetrieved  )  printQyWMon(  &gQyWMon  );
		 #endif

		 if  (  !(  loopCtrl  %  10  )  )  {
			 setQwmCommonStatus(  &gQyWMon  );	//  2007/02/10
		 }

		 if  (  gQyWMon.cfg.ulbCommWithGlCnt  &&  !(  loopCtrl  %  gQyWMon.cfg.usCommWithGlCntIntervalLoops  )  )
		  	 commWithGlCnt(  &gQyWMon  );

		 //  2005/05/23
		 if  (  gQyWMon.cfg.ucbNetMc2  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowPcNetworkPropIntervalLoops  )  )
			 showPcNetworkProp(  &gQyWMon,  0  );

		 //  2006/05/21
		 if  (  gQyWMon.cfg.ucbNetMc2  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowPcWindowsUpdatePolicyIntervalLoops  )  )
			 showPcNetworkProp(  &gQyWMon,  CONST_pcCommType_windowsUpdatePolicy  );

		 //  这个函数完成处理网络配置修改的所有的细节，包括清理和判断各种条件//  2005/05/26
		 procPcNetworkPropChange(  &gQyWMon  );

		 if  (  !gQyWMon.cfg.ucbPcNetworkPropWillChange  )  {		//  2006/09/10, 注意，这个ucbPcNetworkPropWillChange是很重要的同步标志位

			 unsigned  char			ucbDetectNetFlow		=	FALSE;
			 unsigned  char			ucbShowNetFlow			=	FALSE;

		 	 if  (  gQyWMon.cfg.ucbNetMc2  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowPcNetFlowIntervalLoops  )  )  ucbDetectNetFlow  =  TRUE;
			 if  (  gQyWMon.procStruct_netFlow.ucbWarn  )  {
				 ucbDetectNetFlow  =  TRUE;		//  当前面有报警时，将持续检测
				 gQyWMon.procStruct_netFlow.ucbWarn  =  FALSE;
			 }
		 
		 	 if  (  detectNetFlow(  &threadInfo,  ucbDetectNetFlow,  &ucbShowNetFlow  )  )  ucbShowNetFlow  =  FALSE;

		 	 if  (  ucbShowNetFlow  )  showPcNetFlow(  &threadInfo  );

			 if  (  gQyWMon.procStruct_netFlow.ucbWarn  )  procNetFlowWarn(  &threadInfo  );			 

		 }

		 
		 //  2005/07/03
		 ucbProcessJustSnt  =  FALSE;
		 if  (  gQyWMon.cfg.ulbShowPcProcess  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowProcessIntervalLoops  )  )  {
			 showPcProcess(  &threadInfo  );  ucbProcessJustSnt  =  TRUE;
		 }

		 //  2006/04/14
		 if  (  gQyWMon.cfg.ulbShowPcModules  &&  (  gQyWMon.cfg.pcRules.osAudit.ucSndModuleInfoCmd  ==  CONST_devCmd_permitted  )  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowModulesIntervalLoops  )  )  {
			 if  (  !ucbProcessJustSnt  )  showPcProcess(  &threadInfo  );		//  确保进程信息和模块信息同步
			 showPcProcessModules(  &threadInfo  );
		 }

		 //  2006/07/14

		 //  2005/08/30
		 if  (  gQyWMon.cfg.pcRules.osAudit.ucSndEventLogCmd  ==  CONST_devCmd_permitted  &&  !(  loopCtrl  %  gQyWMon.cfg.usSndEventLogIntervalLoops  )  )
			 sndEventLog(  &threadInfo  );
		 if  (  gQyWMon.cfg.pcRules.osAudit.ucSndUsrInfoCmd  ==  CONST_devCmd_permitted  &&  !(  loopCtrl  %  gQyWMon.cfg.usSndUsrInfoIntervalLoops  )  )
			 sndUsrInfo(  &threadInfo  );
		 if  (  gQyWMon.cfg.ucbNetMc2  &&  !(  loopCtrl  %  gQyWMon.cfg.usSndPrintersIntervalLoops  )  )  {
			 getPrinters(  &threadInfo,  &gQyWMon.cfg.printersProcInfo  );
			 sndPrintersInfo(  &threadInfo,  &gQyWMon.cfg.printersProcInfo  );
		 }
		 if  (  gQyWMon.cfg.pcRules.osAudit.ucSndNetStatCmd  ==  CONST_devCmd_permitted  &&  !(  loopCtrl  %  gQyWMon.cfg.usSndNetStatIntervalLoops  )  )
			 sndNetStat(  &threadInfo  );

		 //  2007/02/14
		 if  (  gQyWMon.cfg.ucbNetMc2  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowPcNetShareIntervalLoops  )  )  
			 showPcNetShare(  &threadInfo  );
		 if  (  gQyWMon.cfg.ucbNetMc2  &&  !(  loopCtrl  %  gQyWMon.cfg.usShowPcArpIntervalLoops  )  )
			 showPcArp(  &threadInfo  );


		 //  查询是否自动登录
		 if  (  gQyWMon.cfg.ulbQueryAutoLogon  &&  !(  loopCtrl  %  gQyWMon.cfg.usQueryAutoLogonIntervalLoops  )  )  {
			 queryAutoLogon(  &threadInfo  );
		 }
		 if  (  gQyWMon.cfg.ulbQueryAutoLogon  )  procAutoLogon(  &threadInfo  );

		 //  在需要实时操作时，建立快速的命令查询
		 if  (  (  gQyWMon.cfg.getOpCmd.ucbOped  &&  !(  loopCtrl  %  DEFAULT_getOpCmdInterval_realTime  )  )
			 ||  (  !gQyWMon.cfg.getOpCmd.ucbOped  &&  !(  loopCtrl  %  gQyWMon.cfg.usGetOpCmdIntervalLoops  )  )  )  
		 {
			 retrieveOpCmd(  &threadInfo  );		
		 }
		 //  if  (  !gQyWMon.cfg.getOpCmd.ucbOped  )  memset(  &gQyWMon.cfg.getOpCmd,  0,  sizeof(  gQyWMon.cfg.getOpCmd  )  );
		 //  上面这句话移到getOpCmd中了, 2007/02/04


		 //  下面为发送日志
		 if  (  gQyWMon.cfg.ulbSndSavedTmpLog  &&  !(  loopCtrl  %  gQyWMon.cfg.usSndLogIntervalLoops  )  )
		  	 sndSavedTmpLog(  &gQyWMon.logContext,  ""  );

		 
		 // 下一段代码从版本更新后移到这里。
		 if  (  gQyWMon.cfg.ucbStopMon  )  {
			 traceLogA(  "now CommandHandlerLoop( ) is to stopMon."  );
			 
			 gQyWMon.bQuit		=  TRUE;

			 #ifdef  __DEBUG__
					 qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_tc  ),  _T(  "0"  )  );
			 #endif
			 g_bEradicate		=  TRUE;
			 g_bRestart			=  FALSE;
			 g_bBO2KFinished	=  TRUE;
			 continue;

		 }	 

		 if  (  gQyWMon.cfg.ucbQuitForUpdate  )  {
			 traceLogA(  "now CommandHandlerLoop(  ) is quitForUpdate"  );

			 gQyWMon.bQuit		=  TRUE;

			 g_bEradicate		=  FALSE;
			 g_bRestart			=  FALSE;
			 g_bBO2KFinished	=  TRUE;
			 continue;
		 }

		 #ifdef  __DEBUG__
				 if  (  gQyWMon.cfg.ucbPh  )  {
					 traceLogA(  "now CommandHandlerLoop(  ) is ph."  );
			
				 	 gQyWMon.bQuit		=  TRUE;

					 qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ph  ),  _T(  "0"  )  );
					 g_bEradicate		=  FALSE;
					 g_bRestart			=  FALSE;
					 g_bBO2KFinished	=  TRUE;
					 continue;
				 }
		 #endif

	}

#ifdef  __TEST__
errLabel:
#endif

	// Terminate command handlers

	exitAsrWMon(  &gQyWMon  );		// added by asr.

	traceLogA(  "CommandHandlerLoop( ) leave."  );

}





