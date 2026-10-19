

#ifndef  __QYMCDAEMONMAIN_H__
#define  __QYMCDAEMONMAIN_H__	/*  {  */


typedef  struct  __qyMcDaemonCfg_t				{

				 char							sn[CONST_qySnSize  +  1];
				 unsigned  char					ucbDebugVer;							//  Debug
				 unsigned  long					ulMaxPcs;								//  
				 unsigned  long					ulMaxMessengers;						//  2007/08/14
				 unsigned  long					ulMaxImGrps;							//  2011/10/05
				 unsigned  short				usMaxVideoConferenceMems;				//  2009/11/05
				 unsigned  short				usMaxDynBmpMessengers;					//  2009/11/05
				 unsigned  long					ulMaxPhoneMessengers;					//  2008/01/30
				 PF_commonHandler				pfDoServWork;


				 //  本地服务配置参数
				 //  QY_LOGICAL_SERVER			cntServ;								//  管理中心
				 
				 SOCK_TIMEOUT					to;
				 
				 //  模块的装载配置
				 //  MACRO_qnmModulesLoadedInfo
				 QNM_MODULES_LOADEDINFO			modulesLoadedInfo;

				 //
				 unsigned  char					ucbAdvancedVer;							//  2005/08/30

				 //  运行配置
				 unsigned  int					nQueryStopInterval;
				 unsigned  int					nSenderInterval;
				 unsigned  int					nSenderRequestInterval;
				 unsigned  int					nProcessingInterval;
				 //
				 unsigned  int					nProcessQmObjQIntervalLoops_netMc;		//  2006/12/09
				 unsigned  int					nRefreshQmObjQStatusInDbLoops_netMc;	//  2006/12/10
				 //
				 unsigned  int					nRefreshQmObjQStatusInDbLoops_is;		//  2006/12/10
				 unsigned  int					nGetDaemonStatusLoops_is;				//  2010/01/10
				 
				 //				
				 unsigned  short				usIntervalAheadInS_refreshTime_forDb;	//  2007/08/05
																						//  因为数据库经常完全入库需要一点时间。所以，以时间为标准刷新增量数据时，往往要遗漏在刷新点前的一点数据。为了确保得到这些数据，要往前一个小提前量。建议为1分钟
				 unsigned  short				usIntervalAheadInS_refreshTime_forMem;	//  对内存的操作也提供一个简单的提前量，建议为5秒


				 //
				 QNM_INTERVAL_PARAMS			intervalParams;						//  2005/06/10
				 unsigned  int					uiMaxLogs;							//  2005/10/01, 最大的日志存储条数

				 //
				 char							qwmFullFileName[CONST_qyMaxPathLen  +  1];
				 char							qwmDigest[CONST_qyMd5Len  +  1];
				 unsigned  int					qwmDigestLen;
				 char							qrtFullFileName[CONST_qyMaxPathLen  +  1];
				 char							qrtDigest[CONST_qyMd5Len  +  1];
				 unsigned  int					qrtDigestLen;

				 //
				 unsigned  char					ucbStopMon;							//  停止管理并卸载所有受控端软件,  （慎用）

				 //  如下是预编译开关量
				 unsigned  char					ucbPermitBjProxy;					//  是否允许本机代理
				 unsigned  char					ucbPermitBwdProxy;					//  是否允许本网段代理
				 unsigned  char					ucbAccessDenied;					//  是否禁止服务, 在功能定义时，该标志可用于将daemon的功能关掉，2003/11/17

				 //  如下是总体管理策略
				 unsigned  char					ucbNotAllAllowed;					//  是否拒绝不在指定IP列表中的PC接受此管理中心管理
				 unsigned  char					ucbStopAutoReg;
				 unsigned  char					ucbStartRespForUnreg;				//  是否对未审核机实行自动响应（阻断）
				 unsigned  char					ucbStopFileMon;						//  2006/03/23
				 unsigned  char					ucbStopModuleMon;					//  2006/04/17
				 unsigned  char					ucbStopPcRegistryMon;				//  2006/08/15
				 unsigned  char					ucbStartUpdate;						//  是否启动重新注册								2003/09/13				 				 
				 QNM_RAS_RULE					rasRule;							//  拨号
				 QNM_DEV_RULE					devRule;							//  外设
				 QNM_MGRPROXY_RULE				mgrProxyRule;
				 QNM_OS_RULE					osRule;											//  2005/06/25
				 QNM_OSAUDIT_RULE				osAuditRule;									//  2005/09/18
				 QNM_PCMON_RULE					pcMonRule;										//  2006/03/05
				 TCHAR							capScreenDir[CONST_qyMaxPathLen  +  1];			//  2006/03/06
				 unsigned  char					ucbSaveAsGif;									//  2008/02/18
				 SKIPPED_MACS					skippedMacs;									//  2008/02/19

				 //  2007/08/29

				 //  QNM_PCNETFLOW_RULE				pcNetFlowRule;									//  2006/09/11
				 QNM_PC_RULES					pcRules;										//  2006/09/11
	

				 //  如下是配置数据文件			//  2003/09/19
				 WCHAR							cfgFullFileName[CONST_qyMaxPathLen  +  1];		//  配置文件绝对路径

				 //

				 union							{
					 struct						{
						 char					subKey[512  +  1];
					 }							httpSvr;
					 struct						{									//  该结构于2003/09/19添加
						 char					qyRegToolTitle[48  +  1];						 
					 }							qwm;								//  终端策略管理系统的配置信息
				 }								u;

				 QNM_WARN_CFG					warn;

				 HANDLE							hThreadCfgWarn;


}		 QY_MCDAEMON_CFG;

#define		QMD_THREAD_CFG						QY_MCDAEMON_CFG

typedef  struct  __qyMcDaemon_t					{

			     MACRO_qyAppCommonMems
				 
				 QY_ENV							env;								//  2007/01/21

				 QY_MCDAEMON_CFG				cfg;
				
				 HANDLE							hThreads[CONST_qmdMaxThreads];	
				 QY_THREADPROC					threadProcs[CONST_qmdMaxThreads];

				 QY_ENC_CTX						encCtx,  commEncCtx;  
				 unsigned  char					ucbEncInited;
				 
				 QY_LICENSE_CTX					licenseCtx;
				 int							nDays_left;
				 
				 QWM_MACS_INFO					macsInfo;							//  2005/02/01
				 				 
				 //
				 GENERIC_Q						logQ;
				 BOOL							bLogQInited;				
				 
				 //
				 struct							{
					 unsigned  long				ulRandOfStartup;					//  标识启动的随机数
					 unsigned  int				nPcs;								//  当前计算机列表中的计算机数
					 unsigned  int				nMessengers;						//  qyMessengerTab中的数量(不包含群)
					 unsigned  int				nPhoneMessengers;					//  
					 unsigned  int				nImGrps;					 
					 unsigned  int				nLogs;								//  当前日志条数
					 //
					 unsigned  char				ucbNeedRefreshQmObjQInfo;			//  2008/02/17， 用来设置标志位，以通知qmd来将实时策略从库里刷新到内存队列里。
					 //
					 unsigned  char				ucbWarnMsgExists;					//  2006/06/03, 是否报警信息存在
					 //

				 }								status;

}		 QY_MCDAEMON;


int qyMcDaemonMain(  );


#endif	/*  }  */


