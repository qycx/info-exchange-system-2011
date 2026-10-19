
#ifndef  __QYSNMPHELPPROCCOMMON_H__
#define  __QYSNMPHELPPROCCOMMON_H__	/*  {  */

/*

#include	"qyCommonEx.h"
#include	"qyDbCommon.h"


#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmProxyCommProc.h"
#include	"qyImcCommProc.h"

#include	"qyImcComm.h"
#include	"qyImcCommoncfg.h"
#include	"qyImcLogFunc.h"
#include	"qyImcSndObjs.h"
#include	"qyImcPublic.h"

#include	"qnmPrecomp.h"

#include	"qnmCustom.h"
#include	"qnmCustomComm.h"

  */
#include	<vfw.h>
#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qySnmpHelpProc.h"
#include	"qmSnmpProc.h"


typedef  union  _qySnmpHelpOpCmdU_t				{
				struct							{
		 			int							ifAdminStatus;							//  阻断值, 1为允许接通, 2为阻断，其他值无效
		 		}								block;
		 		char							buf[1024];
}		 QY_SNMPHELP_OPCMDU;


typedef  struct  __qySnmpCfg_t					{

				 int							iNmsOp;									//  功能选择项

				 unsigned  char					ucbForeground;							//  是否前台运行
				 unsigned  char					ucbQuitIfErr;							//  是否有错立即退出
				 NMS_SCAN_STRUCT				scanStruct;
				 int							ifPortIndex;							//  端口索引
				 char							processedMac[CONST_qyMacLen  +  1];		//  须处理的MAC
				 char							processedIp[CONST_qyMaxIpLen  +  1];	//  须处理的IP
				 int							iSnmpOpCmd;
				 QY_SNMPHELP_OPCMDU				opCmdU;
				 
				 QNM_DB_CFG						db;										//  2008/02/24

				 char							startIp[15  +  1];
				 char							endIp[15  +  1];

				 unsigned  char					ucbStopWatchMac;						//  停止监视mac变化，常值为FALSE
				 unsigned  char					ucbStopWatchIp;							//  停止监视ip变化，缺省为FALSE
				 unsigned  char					ucbStartRegScan;						//  
				 //  unsigned  char					ucbStartRegScanIp;
				 unsigned  char					ucbStartRespForUnreg;
				 
				 unsigned  long					ulbNotRefreshSwitchInfo:1;				//  不需要刷新交换机信息
				 unsigned  long					ulbNotRefreshPortStatus:1;				//  不需要刷新端口状态
				 unsigned  long					ulbNotRefreshCdp:1;						//  不需要刷新cdp信息
				 unsigned  long					ulbNotRefreshInOutOctets:1;				//  不需要刷新流量
				 unsigned  long					ulbNotRefreshMac:1;						//  不需要刷新mac
				 unsigned  long					ulbNotRefreshSecureInfo:1;				//  不需要刷新安全信息
				 
}		 QY_SNMP_HELPPROC_CFG;


#define		CONST_maxSnmpHelpProcThreads		10

typedef  struct  __qySnmpHelpProcInfo_t			{
	
				 MACRO_qyAppCommonMems

				 QY_ENV							env;								//  2007/01/21

				 QY_SNMP_HELPPROC_CFG			cfg;

				 QY_ENC_CTX						encCtx;  
				 unsigned  char					ucbEncInited;

				 QY_LICENSE_CTX					licenseCtx;

				 HANDLE							hThreads[CONST_maxSnmpHelpProcThreads];	
				 QY_THREADPROC					threadProcs[CONST_maxSnmpHelpProcThreads];
				 void						*	pThreadParams[CONST_maxSnmpHelpProcThreads];
				 	
				 time_t							tStartToScanInSecond;		//  开始扫描一台设备的时间
				 unsigned  char					ucbScanFinished;
				 int							iQuitCode;					//  2004/06/20加
				 
}		 QY_SNMP_HELPPROCINFO;



#include	"QySnmpHelpProcDaemon.h"



#endif  /*  }  */


