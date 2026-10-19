

#ifndef		__ASRWMON_H__
#define		__ASRWMON_H__	/*  {  */

#include	"qyCommon.h"
#include	"qyCommon\\asrObjs.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qnmSysCustom.h"
#include	"asrWMonPrecomp.h"

#include	"qyCommon\\asrLog.h"
#include	"qyCommon\\asrComm.h"

#include	"qyCommon\\awmComm.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyGuiCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmPcComm.h"
//  #include	"qnmProxyCommProc.h"
#include	"qnmGuiCommProc.h"
#include	"qnmAssetsCommProc.h"
#include	"qwmHideProcessCommProc.h"
#include	"qnmDevCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qwmDjCommProc.h"
#include	"qyTCharCommProc.h"

#include	"traceLog.h"

#include	"qnmCustom.h"

#include	"asrWMonCfg.h"
#include	"qwmFunc.h"
#include	"qnmCustomGui.h"
#include	"qwmRegistryFunc.h"
//  #include	"myNtQueryInformationProcess.h"			
#include	"qwmDynFunc.h"				

#include	"qyMtSock.h"

typedef  struct  __qwmPrinterMgrProcInfo_t  {
				 DWORD						nPrinters;
				 struct						{
					 //  char					name[255  +  1];
					 TCHAR					name[255  +  1];
					 HANDLE					hPrinter;
					 HANDLE					hNotify;
				 }							printers[CONST_maxPrinters];
}		 QWM_PRINTERMGR_PROCINFO;


typedef  struct  __qwmCfg_t							{
				 
				 QWM_DYN_CFG						dynCfg;										//  2006/07/01
				 //
				 QY_LOGICAL_SERVER					cnt;
				 //  
				 char								seqNo[64  +  1];
				 int								iSystemId_wanted;							//  为确保系统生成的正确性，加入了对iSystemId的核对

				 TCHAR								rootKey[CONST_qyMaxRegKeyLen  +  1];

				 //  程序运行控制变量
				 TCHAR								mutexName[256];
				 TCHAR						*		svTarget;
				 TCHAR						*		serviceName;
				 TCHAR						*		legacyServiceName;							//  2006/08/31

				 unsigned  char						ucbStopMon;									//  卸载受控端软件的指令
				 unsigned  char						ucbQuitForUpdate;							//  退出以使升级
				 #ifdef  __DEBUG__
					unsigned  char					ucbPh;										//  测试用的破坏指令
				 #endif
				 unsigned  char						ucbStopMon_usrScript;						//  服务进程设置可使服务进程外的其他用户进程（还有保护线程都随之退出）

			
				 //  为代理功能的运行控制变量
				 //  unsigned  char						ucbStartProxy;							//  是否启用有限的代理功能

				 //  2007/02/16, 为网络共享的管理设置几个同步参数
				 TCHAR								mutexName_syncNetShare[32];
				 unsigned  long						ulMilliSeconds_syncNetShare;
				 //  2007/02/18, 为将日志记录到本地，设置一个同步参数
				 TCHAR								mutexName_syncLogEvent[32];						
				 unsigned  long						ulMilliSeconds_syncLogEvent;
				 

				 //  功能的开关量
				 unsigned  long						ulbQwmThreadProcCmd:1;						//  是否启动线程qwmThreadProcCmd
				 unsigned  long						ulbQwmThreadPrinterMgr:1;					//  是否启动打印管理线程, 2005/09/10
				 unsigned  long						ulbQwmThreadFileMon:1;						//  是否启动文件监视线程, 2005/09/13
				 unsigned  long						ulbQwmThreadPcMon:1;						//  是否启动监控线程，2006/03/05
				 unsigned  long						ulbQwmThreadCollectUsrLog:1;				//  是否启动线程来收集用户日志，2007/02/18
				 unsigned  long						ulbQwmThreadWndProc:1;						//  是否接受有窗口的线程, 2007/02/27
				 //
				 unsigned  long						ulbRetrieveQwmGlCntIp:1;					//  是否查询管理中心IP以便分组管理
				 unsigned  long						ulbRetrieveQwmCfg:1;						//  是否从管理中心读取配置信息
				 unsigned  long						ulbCommWithGlCnt:1;							//  是否向管理中心通报本机信息
				 unsigned  long						ulbSndSavedTmpLog:1;						//  是否发送临时保存的日志
				 unsigned  long						ulbRetrieveQnmProxyCfg:1;					//  是否从管理中心读取代理配置
				 unsigned  long						ulbShowPcProcess:1;
				 unsigned  long						ulbShowPcModules:1;					
				 unsigned  long						ulbSndNetStat:1;							//  是否上传连接信息, 2005/09/17
				 unsigned  long						ulbQueryAutoLogon:1;						//  是否查询自动登录，2006/01/07
				 
				 //
				 unsigned  char						ucbNetMc2;									//  是否管理非法外联, 2004/11/15加
				 unsigned  char						ucbGetPcAsset;								//  是否进行资产管理，2004/11/15加
				 unsigned  char						ucbSecChk;									//  是否进行安检，2005/05/02加
				 
				 //  管理策略
				 //  QNM_RAS_RULE						rasRule;
				 QY_LOGICAL_SERVER					interMon;
				 //  QNM_DEV_RULE						devRule;
				 //  QNM_OS_RULE						osRule;										//  2005/06/25
				 //  QNM_SECCHK_RULE					secChkRule;
				 //  QNM_OSAUDIT_RULE					osAuditRule;								//  2005/08/30
				 QNM_PCOP_RULE						opRule;										//  2006/02/10
				 //  QNM_PCMON_RULE						pcMonRule;									//  2006/03/05
				 //  QNM_PCNETFLOW_RULE					pcNetFlowRule;								//  2006/09/10
				 //
				 QNM_PC_RULES						pcRules;									//  2007/01/27, 将上面的策略统一起来
				 unsigned  char						ucbHideQwm;									//  2007/02/20, 进程隐藏不是完全根据策略来的，而是要根据策略和有关要素一起来决定。所以，要单独有个变量来协调
				 //
				 PC_FILEMON_RULES					pcFileMonRules;								//  2006/03/22			

				 
				 QWM_PRINTERMGR_PROCINFO			printersProcInfo;							//  2005/09/19

				 //  网络配置策略，2005/05/26
				 QY_PCNETWORK_PROPU					newPcNetworkProp;
				 QY_PCNETWORK_INFOU					curPcNetworkInfo;
				 unsigned  char						ucbPcNetworkPropWillChange;


				 //  自动登录策略，2006/01/08
				 QNM_CMDPARAM_queryAutoLogon		queryAutoLogon;

				 //  实时操作命令, 2006/02/11
				 QNM_CMDPARAM_getOpCmd				getOpCmd;

				 //
				 unsigned  short					usFindCntIntervalLoops;						//  搜索服务器以改变管理端的循环间隔，2006/07/01
				 unsigned  short					usConnectIntervalLoops;						//  联系服务器取得配置参数的循环间隔次数
				 unsigned  short					usQueryGlCntIpIntervalLoops;				//  联系服务器取得glCntIp的循环间隔次数
				 unsigned  short					usQueryCfgsIntervalLoops;					//  取其他配置的间隔次数，		2006/08/15
				 unsigned  short					usCommWithGlCntIntervalLoops;				//  联系服务器交流信息的循环间隔次数 
				 unsigned  short					usShowPcNetworkPropIntervalLoops;			//  发送网络状态的循环间隔,		2005/05/23
				 unsigned  short					usShowPcWindowsUpdatePolicyIntervalLoops;	//  发送补丁配置信息，			2006/05/21
				 unsigned  short					usShowPcNetFlowIntervalLoops;				//  发送流量信息，				2006/09/10
				 unsigned  short					usShowProcessIntervalLoops;					//  发送进程信息,				2005/07/03
				 unsigned  short					usSndEventLogIntervalLoops;					//  发送系统日志				2005/08/30
				 unsigned  short					usSndUsrInfoIntervalLoops;					//  发送帐户信息，				2005/09/04
				 unsigned  short					usSndNetStatIntervalLoops;					//  发送连接信息，				2005/09/17
				 unsigned  short					usSndPrintersIntervalLoops;					//  发送打印机信息，			2005/09/18
				 unsigned  short					usQueryAutoLogonIntervalLoops;				//  查询自动登录，				2006/01/07
				 unsigned  short					usGetOpCmdIntervalLoops;					//  实时操作时的取配置间隔，	2006/02/11
				 unsigned  short					usShowModulesIntervalLoops;					//  发送模块信息,				2006/04/14
				 unsigned  short					usShowPcNetShareIntervalLoops;				//  发送网络共享				2007/02/14
				 unsigned  short					usShowPcArpIntervalLoops;					//  发送ARP信息					2007/02/14
				 //
				 unsigned  short					usSndLogIntervalLoops;						//  发送临时日志的循环间隔次数
				 unsigned  int						nInterval_qwmThreadProcCmd;					//  命令线程的休息间隔
				 unsigned  short					usGetRandIntervalLoops;						//  命令线程设置任意数种子的循环间隔次数
				 unsigned  int						nInterval_qwmThreadProcFastCmd;				//  连接线程的休息间隔
				 unsigned  int						nInterval_CommandHandlerLoop;				//  CommandHandlerLoop的休息间隔
				 //  unsigned  int						nInterval_qwmThreadProcIpScan;				//  ip扫描线程的休息间隔
				 //  unsigned  int						nInterval_qwmThreadProcRegScan;				//  注册检查线程的休息间隔
				 unsigned  int						maxCommWithGlCntTime;						//  联系服务器发送日志和取得决策信息的循环间隔
				 unsigned  int						maxWaitPcCommTime;							//  检查服务器指定机器列表的时间间隔

				 SOCK_TIMEOUT						to;

}			QWM_CFG;


typedef  struct  __qwmThreadCfg_t					{
	
				 char								threadName[32];
				 QNM_RAS_RULE						rasRule;
				 unsigned   int						nInterval;

}		 QWM_THREAD_CFG;


typedef  struct  __qwmCommonStatus_t				{
	     		 unsigned  char						ucbServerOnline;							//  2006/03/06
}		 QWM_COMMON_STATUS;

typedef  struct  __qwmNetShareStatus_t				{
				 unsigned  long						ulbUsrNetShareExists:1;						//  2007/02/16
				 unsigned  long						ulbSysNetShareExists:1;						//  2007/02/16
}		 QWM_NETSHARE_STATUS;


//  2010/05/20
typedef  struct  __wLanAdapter_t					{
				 BOOL								bLogged;
}		 WLAN_ADAPTER;

#define		CONST_maxWLanAdapters					5
typedef  struct  __wLanAdapters_t					{
				 WLAN_ADAPTER						mems[CONST_maxWLanAdapters];
}		 WLAN_ADAPTERS;


typedef  struct  __qyWMon_t							{

				 MACRO_qyAppCommonMems
				 //  int								iAppType;									//  应用类型
				 //  int								iAppId;									//  应用标适
				 //  int								iCustomId;									//  定制化标识
				 //  int								serviceId;									//  通信协议
				 //  char								ver[CONST_qyMaxVerLen  +  1];				//  版本号

				 QY_ENV								env;

				 QWM_CFG							cfg;
		
				 struct								{
						unsigned  long				ulbRecoveredByQwmHelp2:1;					//  是否是qwmHelp2启动起来的, 2005/07/30
						unsigned  long				ulbRegOnly:1;
						//  unsigned  long				ulbChild:1;									//  是否是子进程
						unsigned  long				ulbDoSecChk:1;								//  2005/05/02
						unsigned  long				ulbDoReboot:1;								//  2005/05/31
						unsigned  long				ulbDoRemoveUsb:1;							//  2005/10/08
						unsigned  long				ulbViewRemoteDesktop:1;						//  2006/02/12
						unsigned  long				ulbCapScreen:1;								//  2006/03/06
						unsigned  long				ulbMonDesktop:1;							//  2006/03/06
						unsigned  long				ulbMonIe:1;									//  2006/03/07
						unsigned  long				ulbNetFlowWarn:1;							//  2006/09/11
						unsigned  long				ulbUsrScript:1;								//  2007/01/11
						unsigned  long				ulbStartProtectingThread_sys:1;				//  2007/01/31
						unsigned  long				ulbStartProtectingThread_usr:1;				//  2007/01/31
						//
						unsigned  long				ulProcessId_remoteProcess;					//  2007/01/15
						//
						unsigned  char				ucbDownNetworkCard;							//  是否阻断网卡
						unsigned  short				usTotalProgress;							//  对话框持续时间									
						//
						TCHAR						respOkStr[16  +  1];						//  2005/05/04
				 }									cmd;										//  命令行描述

				 struct								{

					    int							nInstall;									//  安装级别

						unsigned  long				ulRandOfStartup;							//  标识启动的随机数

						QWM_COMMON_STATUS			common;
						//  unsigned  char				ucbServerOnline;							//  2006/03/06

						//
						unsigned  long				ulbEncInited:1;
						unsigned  long				ulbProcessHiden:1;
						unsigned  long				ulbQwmHelp2VerRight:1;						//  2005/07/28
						unsigned  long				ulbQwmHelp2Started:1;						//  2005/07/28
						unsigned  long				ulbUsrInAdminGrp:1;							//  2007/02/27
						
						//
						unsigned  long				ulbWTSSessionNotificationRegistered:1;		//  2007/02/27
						unsigned  long				ulbTimerSet:1;								//  2007/02/27

						//
						unsigned  long				ulbUsbStorExists:1;							//  2005/10/06

						QWM_NETSHARE_STATUS			netShare;									//  2007/02/16
						
				 }									status;

				 QY_LOGICAL_SERVER					server;										//  实际使用的管理端

				 DWORD								curThreadId;
				 BOOL								bQuit;										//  退出标志

				 unsigned  char						ucbOnInternet;
				 unsigned  char						ucbOnInternetLogged;
				 DWORD								dwDetectInternetLastTickCnt;
				 DWORD								dwOnInternetLastTickCnt;
				 char								onInternetLastTimeBuf[CONST_qyTimeLen  +  1];
				 //  BOOL							bRasOn;				 
				 //  int							iStatus;
				 DWORD								dwDetectRasLastTickCnt;						//  2005/01/07
				 DWORD								dwDetectProxyServerLastTickCnt;
				 DWORD								dwProcDevRuleLastTickCnt;					// 
				 DWORD								dwProcSafeModeLastTickCnt;					//  2005/06/25
				 DWORD								dwProcAutorunLastTickCnt;					//  2007/02/12
				 DWORD								dwProcNetShareLastTickCnt;					//  2007/02/12
			 

				 //  2005/01/06
				 PROC_DEV_STRUCT					procDevStruct;								//  处理的全局结构

				 //  2006/09/10, 检测流量的数据结构
				 struct								{
				 	 DWORD							dwNumEntries;
				 	 QY_PCNETFLOW_PROP				netFlowProps[CONST_maxDetectNetFlows];
				 	 DWORD							dwDetectNetFlowLastTickCnt;		
					 unsigned  char					ucbWarn;
				 }									procStruct_netFlow;

				 unsigned  int						uiRegUsrIndex;								//  注册表中下一个被枚举的用户的顺序号,  2003/09/13
				 QWM_USR_INFO						usrInfos[CONST_maxDetectedUsrs];
				 
				 WLAN_ADAPTERS						wLanAdapters;								//  2010/05/20

				 char								localIp[16];								//  pc的属性描述				 
				 char								hostname[256];
				 char								pcName[MAX_COMPUTERNAME_LENGTH + 1];
				 QWM_MACS_INFO						macsInfo;
				 WCHAR								wWinDir[MAX_PATH  +  1];
				 WCHAR								wSystemDir[MAX_PATH  +  1];					//  2006/03/17
				 WCHAR								wUsrName[64];								//  2007/02/03
				 WCHAR								wDomainName[64];							//  2007/02/03
				 //
				 DWORD								dwCurSessionId,  dwActiveSessionId;			//  2007/02/04

				 
				 unsigned  long						ulRand;												//  加密用
				 QY_ENC_CTX							encCtx,  updateEncCtx,  quitEncCtx,  commEncCtx;	//  2004/01/03添加commEncCtx
				 QY_LOG_CTX							logCtx;


				 TCHAR								pureDllName[32  +  1];		//  2005/06/06
				 TCHAR								pure2DllName[32  +  1];		//  2005/07/26
				 TCHAR								pureRdDllName[32  +  1];	//  2006/02/13
				 TCHAR								pure3DllName[32  +  1];		//  2006/02/13
				 TCHAR								pureRdHelpDllName[32  +  1];//  2006/02/13

				 //
				 DWORD								dwRemoteProcId;				//  qwmHelp2.dll依附的进程号
				 HANDLE								hRemoteModule;				//  qwmHelp2.dll的句柄
				 HANDLE								hMutexForRemote;			//  和远程线程进行同步，2005/07/29	

				 HINSTANCE							hDll_help2;					//  2007/01/15, qwmHelp2里存放了一些函数可以利用，要装起来利用
				 //  PF_getQwmGBuf						pf_getQwmGBuf;
				 //  PF_setGBufSth						pf_setGBufSth;
				 
				 HANDLE								hMutex;										
				 ASR_LOG_CONTEXT					logContext;									//  log上下文描述，暂时不用
				 //  void						*		pRegScanStruct;

				 HANDLE								hThreads[2  +  CONST_qwmMaxThreads];		//  线程0用于qwmCmdThreadProc
																								//  线程1用于qwmFastCmdThreadProc
																								//  其余用于指定用途
													

				 HANDLE								hFile;										//  Modified last.
				 BOOL								bLocked;									//  Modified last.
				 HANDLE								hCfgFile;									//  2006/3/22

				 BOOL								bKeyUpdate;
				 int								nCount;										//  for RAS_OFF_LINE

}		QY_W_MON;


typedef  BOOL  (  *PF_bThreadPause  )(  void  *  p0  );


typedef  struct  __qwmThreadInfo_t					{
				 void				*				pParaentParam;
				 QWM_THREAD_CFG		*				pCfg;
				 PF_bThreadPause					pfbThreadPause;
				 QY_LOG_CTX							logCtx;
				 DWORD								dwLoopCtrl;					//  2004/10/25加
}		 QWM_THREADINFO;



typedef  struct  __qwmSession_t						{
				 QY_COMM_SESSION					comm;	
				 char								servSeqNo[128  +  1];
}		 QWM_SESSION;


typedef  struct  __qwmSessionBuf_t					{
				 union								{
					 struct							{
						char						fileName[CONST_qyMaxPathLen  +  1];
						char						digest[CONST_qyMd5Len  +  1];
						unsigned  int				digestLen;
					 }								getFile;
				 }									u;
}		 QWM_SESSION_BUF;




#define		ASR_W_MON								QY_W_MON
#define		gAsrWMon								gQyWMon

#define		CONST_svTarget							"qwmSvr.EXE"		//  2010/05/07
#define		CONST_hostProcessName					"EXPLORER"			
#define		CONST_serviceName_NT					"Qycx Network Agent"


#include	"qyCommon\\asrTemp.h"
#include	"asrWMonRas.h"
#include	"rasConn.h"
#include	"qwmDynFunc.h"


extern  QY_W_MON		gQyWMon;
extern  BOOL			g_bBO2KFinished;
extern  BOOL			g_bRestart;
extern	BOOL			gbRasManExists;


extern  "C"  int  Encrypt(  char  *  pSource,  int  iSourceLen,  char  *  pDestcode  );
int  qwmParseCfgs(  QY_W_MON  *  pWMon  );
extern  "C"  int  qyGetMacAddrs(  unsigned  char  *  macAddrs[],  unsigned  int  * pMaxMacs  );
extern  "C"  int  qwmOpenSession(  void  *  pQwmParam,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock  );
extern  "C"  void  qwmCloseSession(  void  *  pQwmParam,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock  );
BOOL  bSeqNoCorrect(  void  *  p0,  char  *  servSeqNo,  char  *  qwmSeqNo  );
//
int  cfgQwmServIp(  QY_W_MON  *  pQwm,  QY_LOGICAL_SERVER  *  pCnt  );
int  getQwmServIpCfg(  QY_W_MON  *  pQwm,  QY_LOGICAL_SERVER  *  pCnt  );
//
//  int  cfgQwmItem(  QY_W_MON  *  pQwm,  QY_CFGITEM  *  pItem  );
int  cfgQwmItem(  QY_W_MON  *  pQwm,  QY_CFGITEM_ntoh_U  *  pItem  );

int  requestQwmToQuit(  QY_W_MON  *  pQwm  );
int  loadQwmHelp2Dll(  QY_W_MON  *  pQwm,  TCHAR  *  pure2DllName  );
int  initAsrWMon( ASR_W_MON *pAWM );
void  exitAsrWMon( ASR_W_MON *pAWM );
int  initAsrWMon_usrScript( QWM_THREADINFO  *  pThreadInfo );
void  exitAsrWMon_usrScript(  QWM_THREADINFO  *  pThreadInfo  );
int  chkAndRepairQwmService(  void  *  pQwmParam  );
int  chkAndStartQwmLegacyService(  void  *  pQwmParam  );
int  chkAndRepairQwmUsrScript(  void  *  pQwmParam  );		//  2007/01/16
int  delHelpFile(  TCHAR  *  pureDllName  );


//  extern  "C"  BOOL  bMyHideSupportedOs(  int  iPlatformId  );
extern  "C"  BOOL  bMyHideSupportedOs(  int  iPlatformId,  void  *  p1,  void  *  p2  );	//  2006/02/14
//  extern  "C"  BOOL  bMyQwmHelpDllVerRight(  int  iPlatformId,  char  *  pureDllName  );
extern  "C"  BOOL  bMyQwmHelpDllVerRight(  int  iPlatformId,  TCHAR  *  pureDllName,  PF_bCommonHandler  pfbSupportedOs  );


extern  "C"  int  myHideProcess(  int  iPlatformId,  TCHAR  *  pureDllName  );
extern  "C"  void  myShowProcess(  int  iPlatformId,  TCHAR  *  pureDllName  );

//  unsigned  long  getTargetProcessIdFromProcname(  QY_ENV  *  pEnv,  char  *  procName,  LPCWSTR  wAccountName,  LPCWSTR  wDomainName  );
unsigned  long  getTargetProcessIdFromProcname(  QY_ENV  *  pEnv,  TCHAR  *  procName,  LPCWSTR  wAccountName,  LPCWSTR  wDomainName  );
//  int  myProcQwmHelp2(  void  *  pQwmParam,	int  iPlatformId,  char  *  pure2DllName,  char  *  remoteProcessName  );
int  myProcQwmHelp2(  void  *  pQwmParam,	int  iPlatformId,  TCHAR  *  pure2DllName,  TCHAR  *  remoteProcessName  );
void  myClearQwmHelp2(  void  *  pQwmParam  );  

//  int  initWMState( AWM_CONTROL_CLIENT_INFO *pACCI );
//  void  checkAsrWMonNO( AWM_CONTROL_CLIENT_INFO *pACCI );
//  void  awmGetFileAttribute( char svTargetName[MAX_PATH], AWM_CONTROL_CLIENT_INFO *pACCI );
//  BOOL  bSaveFileAttribute(  char  *  svTargetName  );
//  void  checkAsrWMonRunService( char *svRunRegKey, AWM_CONTROL_CLIENT_INFO *pACCI );
//  BOOL  checkAsrWMonInvalid( AWM_CONTROL_CLIENT_INFO *pACCI );
int  retrieveQwmGlCntIp(  QY_W_MON  *  pAWM  );
//  int  retrieveAsrWMonDownCfg( char *serverIp, AWM_CONTROL_CLIENT_INFO *pACCI );
int  retrieveQwmCfg( ASR_W_MON *pAWM );
int  retrieveQnmProxyCfg( ASR_W_MON *pAWM );
int  queryCfgs(  QY_W_MON  *  pQwm  );
int  commWithGlCnt(  QY_W_MON  *  pQwm  );
int  showPcNetworkProp(  QY_W_MON  *  pQwm,  unsigned   int  uiType  );
int  showPcNetworkPropStatus(  QY_W_MON  *  pQwm,  QY_PCNETWORK_PROPU  *  pCur,  unsigned  char  ucFlg  );
int  getUsrProxyInfo(  QWM_USR_INFO  *  pUsrInfo  );
int  showPcAdapters(  void  *  p0,  void  *  p1,  void  *  p2  );
int  showProxyCfg(  void  *  p0,  void  *  p1,  void  *  p2  );
//  int	 showComputerProp(  void  *  p0,  void  *  p1,  void  *  p2  );
int	 showPcWindowsUpdatePolicy(  void  *  p0,  void  *  p1,  void  *  p2  );
int  detectNetFlow(  QWM_THREADINFO  *  pThreadInfo,  unsigned  char  ucbDetectNetFlow,  unsigned  char  *  pucbShowNetFlow  );
int	 showPcNetFlow(  QWM_THREADINFO  *  pThreadInfo  );
int  procNetFlowWarn(  QWM_THREADINFO  *  pThreadInfo  );
int  showPcProcess(  QWM_THREADINFO  *  threadInfo  );
int	 showPcProcessModules(  QWM_THREADINFO  *  threadInfo  );
//
int  sndEventLog(  QWM_THREADINFO  *  pThreadInfo  );
int	 sndUsrInfo(  QWM_THREADINFO  *  pThreadInfo  );
int  getPrinters(  QWM_THREADINFO  *  pThreadInfo,  QWM_PRINTERMGR_PROCINFO  *  pProcInfo  );
int  sndPrintersInfo(  QWM_THREADINFO  *  pThreadInfo,  QWM_PRINTERMGR_PROCINFO  *  pProcInfo  );
int  sndNetStat(  QWM_THREADINFO  *  pThreadInfo  );
int	 enumPcNetShares(  QY_ENV  *  pEnv,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  );
int	 showPcNetShare(  QWM_THREADINFO  *  pThreadInfo  );
int	 showPcArp(  QWM_THREADINFO  *  pThreadInfo  );
//
int  queryAutoLogon(  QWM_THREADINFO  *  pThreadInfo  );
int  procAutoLogon(  QWM_THREADINFO  *  pThreadInfo  );
int  retrieveOpCmd(  QWM_THREADINFO  *  pThreadInfo  );  
int  saveFileMonRules(  QY_W_MON  *  pQwm  );
int  getFileMonRules(  QY_W_MON  *  pQwm  );
//
int  sndRegistryVals(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QY_SOCK  *  pSock,  QY_PC_REGISTRYRULES  *  pRules  );

//
//
int	 showQwmQuit(  QY_W_MON  *  pQwm  );

int  getQwmInitialCfg(  QY_W_MON  *  pQwm  );
int  getQwmCfg(  QY_W_MON  *  pQwm,  BOOL  bGetServIpCfg  );

int  qwmCapScreen(  QWM_THREADINFO  *  pThreadInfo,  char *svArg2, BOOL  b256  );

//
extern  "C"  int  proc98RegUsr(  int  iPlatformId,  void  *  p0,  void  *  p1,  PF_commonHandler  pf  );
extern  "C"  int  enumRegUsrs(  int  iPlatformId,  void  *  p0,  void  *  p1,  PF_commonHandler  pf  );
extern  "C"  int  qwmCreateRegProcess(  char  *  cmdLine  );


extern  "C"  int  qwmLogRasEvent(  void  *  pSubThreadInfoParam,  int  eventType,  RAS_CONN_INFO  *  pRasConnInfo  );
extern  "C"  int  qwmLogOnInternetEvent(  void  *  pSubThreadInfoParam,  int  eventType,  char  *  timeBuf  );
extern  "C"  int  qwmLogProxyServerEvent(  void  *  pSubThreadInfoParam,  int  eventType,  char  *  curUsrName,  char  *  proxyServer  );
extern  "C"  int  qwmLogDevEvent(  void  *  pSubThreadInfoParam,  int  eventType,  QWM_DEV_INFO  *  pDiskInfo  );		//  2005/01/07
extern  "C"  int  qwmLogGeneralEvent(  void  *  pSubThreadInfoParam,  int  eventType,  char  *  curUsrName,  char  *  comment0,  char  *  comment1,  unsigned  char  ucbUtf8  );	//  2005/09/11

extern  "C"  int  getKeyValsCnt(  HKEY  hKeyRoot,  TCHAR  *  RegPath  );
extern  "C"  int  getKeyInfo(  HKEY  hKeyRoot,  TCHAR  *  RegPath,  DWORD  *  pdwcSubKeys,  DWORD  *  pdwcValues  );
extern  "C"  int  qwmLogEvent(  void  *  pSubThreadInfoParam,  QWM_EVENT  *  pEvent  );
//  extern  "C"  int  qwmLogEventToServ(  void  *  pQwm,  QWM_EVENT  *  pEvent  );
extern  "C"  int  qwmLogEventInReg(  void  *  pQwm,  QWM_EVENT  *  pEvent  );


extern  "C"  int  qwmOutputFileHead(  void  *  pQrt  );
extern  "C"  int  qwmModifyFile(  void  *  pQrtParam  );


#ifdef  __DEBUG__
  extern  "C"  void  printQyWMon(  void  *  pQWM  );
  extern  "C"  int  printQwmEvent(  TCHAR  *  hint,  QWM_EVENT  *  pEvent  );
  int  printRegLogs(  );
#endif


#endif  /*  }  */


