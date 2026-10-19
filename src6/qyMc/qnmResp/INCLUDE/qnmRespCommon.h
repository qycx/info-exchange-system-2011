
#ifndef		__QNMRESPCOMMON_H__
#define		__QNMRESPCOMMON_H__	/*  {  */

#include	<vfw.h>
#include	"qmCommon.h"
#include	"qyDbCommon.h"

#include	"qnmRespCfg.h"
#include	"qyPing.h"





typedef  struct  {

				 SOCK_TIMEOUT			to;

				 //  模块的装载配置
				 //  MACRO_qnmModulesLoadedInfo
				 QNM_MODULES_LOADEDINFO	modulesLoadedInfo;
				 
				 //  控制运行的配置
				 unsigned  char			ucbStartIpScan;
				 unsigned  char			ucbStartRegScan;
				 unsigned  char			ucbStartRespForUnreg;

				 unsigned  int			maxPcLastCommInterval;				//		判断受控端软件是否正常的最大通信时间间隔
				 unsigned  int			maxWaitPcCommTime;					//		等待PC启动的时间
				 
				 //  unsigned  int			minInvalidChkedIpTime;				//	    判断一台机器在tmpTab中多久没有处理，将被放弃
																			//	仅对非本网段的数据有用

		
}		 QNMRESP_DAEMON_CFG;


typedef  struct  {
	
				MACRO_qyAppCommonMems
		 
				QY_ENV					env;								//  2007/01/21

				QNMRESP_DAEMON_CFG		cfg;
						
				QWM_MACS_INFO			macsInfo;

				HANDLE					hThreads[CONST_qnmRespMaxThreads];	
				QY_THREADPROC			threadProcs[CONST_qnmRespMaxThreads];
				
				QY_ENC_CTX				encCtx;  
				unsigned  char			ucbEncInited;

				QY_LICENSE_CTX			licenseCtx;
				
				HANDLE					hMutex;  
				void			*		pDb_netMc;

				struct					{
					unsigned  long		ulbTcpStarted:1;
				}						status;

}		 QNMRESP_DAEMON;



typedef  struct  __qnmRespSubThreadInfo_t	{
				 int						iServiceId;
				 HANDLE						hMutex;
				 void					*	pDb;
				 void					*	pDb1;
				 unsigned  long				cnt;
				 SOCK_TIMEOUT			*	pTo;
				 void					*	pParentParam;

				 DWORD						dwLastProcedTickCnt;

}		 QNMRESP_SUBTHREADINFO;



typedef  struct  __qnmChkingStruct_t		{
				 char						unused;
}		 QNM_CHKING_STRUCT;



#include	"qnmRespDaemon.h"


int  qnmRespMain(  );
DWORD  WINAPI  qnmIpScanProc(  LPVOID lp  );
DWORD  WINAPI  qnmRespProc(  LPVOID lpParameter  );
DWORD  WINAPI  qnmRespProc_netMc2(  LPVOID lpParameter  );

extern  "C"  BOOL  bQyHostOnline(  LPCSTR  pstrHost,  SOCK_TIMEOUT  *  pTo  );
int  qnmRespLogPcEvent(  void  *  pSubThreadInfoParam,  int  iEventType,  int  iCustomId,  char  *  mac,  char  *  ip,  char  *  localEventTime,  QNM_PC_EVENT  *  pEvent  );

BOOL  bQnmRespIpReged(  void  *  pDb,  char  *  ip  );



int  testHook(  LPVOID  lp  );

#endif  /*  }  */



