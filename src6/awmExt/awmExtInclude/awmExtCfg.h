
#ifndef  __AWMEXTCFG_H__
#define  __AWMEXTCFG_H__	/* { */

//  #define		ROOT_AWM_INTRA_MON_KEY					"Software\\Asr\\Awm\\intraMon"
  #define	CONST_regValName_scanIntervalInSecond	"scanIntervalInSecond"			//  added by ywm on 2002/11/01
  #define		CONST_regValName_scanIntervalPerCNetSegInSecond			"scanIntervalPerCNetSegInSecond"			//  added by ywm on 2002/11/01
  #define	CONST_regValName_newInterMonIp0			"newInterMonIp0"				//  added by ywm on 2002/10/09
  #define	CONST_regValName_newInterMonIp1			"newInterMonIp1"				//  added by ywm on 2002/10/09
  #define	CONST_regValName_newInterMonIp2			"newInterMonIp2"				//  added by ywm on 2002/10/09
  #define	CONST_regValName_newInterMonIp3			"newInterMonIp3"				//  added by ywm on 2002/10/09
#define		ROOT_AWM_INTER_MON_KEY					"Software\\Asr\\Awm\\interMon"
  #define	AWM_INTER_MON_IP_KEY					"interMonIp"
  #define	ASR_START_FLG							"startFlg"
  //  #define	CONST_regValName_warnOn					"warnOn"
  //  #define	CONST_regValName_warnUntilUsrStopIt		"warnUntilUsrStopIt"
  //  #define	CONST_regValName_maxWarnElapseInSecond	"maxWarnElapse"					//  这个名字暂时不改，应加InSecond
  //  #define   CONST_regValName_emergencyTime			"emergencyTime"
  //  #define   CONST_regValName_newEmergency			"newEmergency"
#define		ROOT_AWM_INTER_MON_TOOL_KEY				"Software\\Asr\\Awm\\interMonTool"

#define AWM_INTRA_MON_LCK_FILE						"awmIntraMon.lck"
#define AWM_INTER_MON_LCK_FILE						"awmInterMon.lck"
#define AWM_INTER_MON_TOOL_LCK_FILE					"awmInterMonTool.lck"

#define AWM_INTER_MON_ERR_LOG_FILE					"awmInterMon.log"
#define AWM_INTER_MON_ERR_LOG_HINT					"awmInterMon"
#define AWM_INTRA_MON_ERR_LOG_FILE					"awmIntraMon.log"
#define AWM_INTRA_MON_ERR_LOG_HINT					"awmIntraMon"


#define DEFAULT_INTER_MON_MUTEX						"awmInterMonMutex"

#define MAX_AWM_INTRA_MON_THREADS					5
#define	CONST_maxAwmInterMonThreads					5	//  2004/05/23加

#define		DEFAULT_AWM_DSN_NAME					"asrDdmDsn"
//  #define		DEFAULT_AWM_EXT_DSN_NAME				"awmExtDsn"
#define		CONST_qyDsn_netMc						"qyNetMcDsn"		//  2003/11/25加
#define		DEFAULT_AWM_EXT_DSN_NAME				CONST_qyDsn_netMc	//  2003/11/25为实现安检系统的融合，作此修改


//  从src3中取得2003/11/25
//  #define		CONST_qnmStatusWndTitle						"管理中心 - 状态显示"

//  #define		CONST_qyShowType_bhbScanningNetworkSegment			9
//  #define		CONST_qyShowType_bhbScanningIp						10


//  #define		CONST_awmExtInterMonTcpPort				7369
#define		CONST_awmExtInterMonTcpPort				80			//  2004/11/12
#define		CONST_max_nScanIntervalInSecond			86400
#define		CONST_min_nScanIntervalInSecond			5

#define		CONST_max_nScanIntervalPerCNetSegInSecond				3600
#define		CONST_min_nScanIntervalPerCNetSegInSecond				5
#define		DEFAULT_nScanIntervalPerCNetSegInSecond					10


#define		CONST_qyMagic_upnp						"StatusOk"
#define		CONST_qyBufSize_upnp					4096
#define		CONST_qyPort_upnp						1900 
#define		CONST_qyDataMaxLen						1024


#define DEFAULT_AWM_WAIT_TIMEOUT_VAL				5000

#define MAX_AWM_MON_QUEUE_NODES						100000

#define DEFAULT_AWM_WAIT_FOR_THREAD_TIMEOUT			3000


//  #define		CONST_interMonWndTitle					"清扬创新拨号上网监管系统(检测版) - 监视端"
//  #define		CONST_interMonWndTitle					"清扬网络综合管理系统-拨号和非法外联检测-监视端"	//  2003/12/06修改
//  #define		CONST_intraMonWndTitle					"清扬创新拨号上网监管系统(检测版) - 探测端"

#define		CONST_interMonWndTitle					CONST_qnmStatusWndTitle		//  2004/05/24
#define		CONST_intraMonWndTitle					CONST_qnmStatusWndTitle		//  2004/05/24
	

#endif	/* } */

