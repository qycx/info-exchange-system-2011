
#ifndef  __QWMFUNC_H__
#define  __QWMFUNC_H__	/*  {  */


#define	CONST_qyKey_qnmProxy						"Software\\Microsoft\\SharedData7"
#ifdef  __QNMPROXY__
		#define		CONST_qyKey_qwm					CONST_qyKey_qnmProxy				//  代理的注册表项
#else
		#define		CONST_qyKey_qwm					"Software\\Microsoft\\SharedTran"
#endif

#define		ROOT_KEY_AWM							CONST_qyKey_qwm
	#define		CONST_qwmCfgName_cntIp					"rt"
	#define		CONST_qwmCfgName_cntPort				"rt1"
	#define		AWM_SERVER_IP_KEY						"cnt"
	#define		AWM_LEVEL_KEY							CONST_regValName_rasCmd
	#define		CONST_regValName_rasRule				"rinshnnr"
	#define		CONST_regValName_interMon				"qb82n9"
	#define		CONST_regValName_devRule				"qamnxin"		//  2005/01/04
	#define		CONST_regValName_osRule					"qbynlin"		//  2005/06/25
	#define		CONST_regValName_osAuditRule			"qcynmin"		//  2005/09/14
	#define		CONST_regValName_pcMonRule				"qpyinami"		//  2006/03/06
	//
	#define		CONST_regValName_cmdQuit_usrScript		"qqumseniment"	//  2007/01/27
	#define		CONST_regValName_opCmd					"qqvmeinsen"	//  2007/02/04
	//
	#define		CONST_regValName_qwmCommonStatus		"qqymsine"		//  2007/02/10
	//
	#define		AWM_UPDATE_TIME_KEY						"ut"
	#define		AWM_MODIFIED_TIME_KEY					"lwt"
	#define		AWM_PROVIDER_KEY						"Net Office Provider"
	#define		CONST_regValName_tc						"tc"
	#define		CONST_regValName_ph						"ph"
	#define		CONST_qwmCfgName_rand					"c782nb"
	#define		CONST_qwmCfgName_cmdQuit				"yb328x"
	#define		CONST_qwmCfgName_qwmSeqNo				"ynaixm"	//  2005/06/24
	#define		CONST_qyCfgName_ver						"inwk8"
	#define		CONST_qwmCfgName_isOk					"gwbywmk"
	#define		CONST_qwmCfgName_isOkRes				"yuwnes"	
	#define		CONST_regValName_chdRespOk				"snynl"		//  2005/05/04
	#define		CONST_regValName_chdShallQuit			"szyml"		//  2005/05/09
	#define		CONST_qwmCfgName_doRemoveUsb			"remoobs"	//  2005/10/08
	#define		CONST_qwmCfgVal_askToRemoveUsb			"sybwl"		//  2005/10/08
	#define		CONST_qwmCfgVal_readyToRemoveUsb		"ywnm"		//  2005/10/08


//	
#define		CONST_regValName_qwmUsrScript				"qyApp"		//  2007/01/16

#define		CONST_qyKey_qwmLog						"Software\\Classes\\SEO.SEOMemWaLog"
	#define		CONST_qwmLogPtr							"point"
	#define		CONST_qwmLogPrefix						"mem"
#define		CONST_qyKey_qwmLog_usr					"Software\\qycx\\qwm\\tmpLog"	//  2007/02/17

#define		CONST_regValName_autoReg				"qyAutoReg"

#define		CONST_qwmCfgVal_cmdQuit					"7nejy3"
#define		CONST_qwmCfgVal_isOk					"knwun"
#define		CONST_qwmCfgVal_isOkRes					"hwnyu"					
//
#define		CONST_qwmCfgVal_chdShallQuit			"mmyna"			//  2005/05/09
//

#define		SINGLE_FLAG								"0.0.0.0"
#define		AWM_SINGLE_RCD_NUM_KEY					"rcdNum"
#define		AWM_SINGLE_CUR_POS_KEY					"curPos"



#define		CONST_minConnectedSites					2							//  用来判断最少的网站连通数
#define		CONST_minDetectOnInternetInterval		(  37  *  1000  )			//  检查与互联网联通的间隔
#define		CONST_maxDisconnectInterval				(  120  *  1000  )			//  用来判断从互联网上断开的时间，超过了即断开  
#define		CONST_httpFlag							"HTTP/"
#define		CONST_minDetectProxyServerInterval		(  180  *  1000  )
#define		CONST_loopCtrl_detectAndWarnToInterMon	140
#define		CONST_minProcDevRuleInterval			(  10  *  1000  )			//  2005/01/05
#define		CONST_minProcSafeModeInterval			(  10  *  1000  )			//  2005/06/25
#define		CONST_minProcAutorunInterval			(  60  *  1000  )			//  2007/02/12
#define		CONST_minProcNetShareInterval			(  60  *  1000  )			//  2007/02/12
#define		CONST_minDetectRasInterval				(  5  *  1000  )			//  2005/01/07


extern  QY_DMITEM  CONST_wellKnownSiteTable[];


BOOL  canConnectWebSite(  SOCK_TIMEOUT  *  pTo,  QY_DMITEM  *  pItem  );
extern  "C"  int getQwmMacsByNetbios(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  );



int  chkRecent(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkNormalDiskDrvFile(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  );
int  chkDiskDrvFile(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  );
int  chkIe(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkRas(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkProxyCfg(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkInternet(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkShare(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkPcInfo(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkSoftwareInstalled(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkRecycler(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkRemovableStorage(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkUsrInfo(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );
int  chkOsInfo(  void  *  pSubThreadInfo,  void  *  p1,  void  *  p2  );



#endif  /*  }  */

