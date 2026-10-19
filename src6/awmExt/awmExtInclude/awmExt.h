
#ifndef  __AWMEXT_H__
#define  __AWMEXT_H__	/*  {  */

#include  <crtDbg.h>


#ifdef  __cplusplus
 extern  "C"  {
#endif


#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"

#include	"asrWMonCfg.h"
#include	"awmExtCfg.h"
#include	"awmPing.h"
#include	"qyBuildPkt.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmWarnCommProc.h"
#include	"qyNbtScanCommProc.h"
#include	"bhbSrc1CommProc.h"
#include	"aeNbtScan.h"


//  注：当__NEW_AESWK__定义时，为标准斑；注释掉后，则仅测拨号和双网卡，但不测过代理和防火墙的。

#define		__NEW_AESWK__		//  双网卡版	(  注：     此一版本为广东省厅的双网卡要求而作。
								//					        增加了对监视端的ip设置数，使能同时发送
								//						往公安厅外网的监视端和互联网的监视端的探测包，
								//						同时也能将数据发往额外的监视端，为省厅与分局同时监视
								//						提供可能。
								//						    去除了监视端的ip配置，监视端同时接收任何方向的探测包，
								//						为将外网的监视端和互联网的监视端合一提供可能。

typedef  struct  __awm_ext_cfg_t						{
				 char									dsnName[64];
				 int									waitTimeoutVal;			// 仅为interMon使用
				 char									interMonIp[MAX_IP_ADDR_LEN + 1];

				 unsigned  short						interMonTcpPort;		//  监视用的tcp端口
				 unsigned  short						interMonUdpPort;		//  监视用的udp端口, 2004/05/23加

				 char									showWho[32];			//  2004/05/26添加

				 union  __awmExtCfgU_t					{
						struct							{
										int				i;
										unsigned  int	nScanInterval;									//  扫描间歇
										unsigned  int	nScanIntervalPerCNetSeg;						//  网段间隔
										unsigned  int	nScanIntervalPerPc;								//  主机间隔，2004/05/24			
										char			newInterMonIps[4][MAX_IP_ADDR_LEN  +  1];		//  added by ywm on 2002/10/09
						}								intraMon;
						struct			{
										int				i;
										char			newInterMonIps[2][MAX_IP_ADDR_LEN  +  1];		//  added by ywm on 2002/10/12
										QNM_WARN_CFG	warn;
										unsigned  char	ucbStopPermitNat;
										
						}								interMon;
				 }										u;
	
}														AWM_EXT_CFG;

typedef  struct  __awm_ext_t  {
	
				 //  unsigned  int						progId;
				 AWM_EXT_CFG							cfg;
	
				 BOOL									bQuit;
	
				 HANDLE									hThreadIntraMons[MAX_AWM_INTRA_MON_THREADS];	//  仅为intraMon使用
				 HANDLE									hThreadInterMons[CONST_maxAwmInterMonThreads];	//  仅为interMon使用 
				 unsigned  short						usThreads;										//  2004/05/23加
				 HANDLE									hThreadInterMonDaemon;							//  仅为interMon使用
				 HANDLE									hThreadInterMonWarn;							//  仅为interMon使用
	
				 void							*		pLckFile;
				 BOOL									bWsaStartuped;
				 BOOL									bMtSockInited;
				 BOOL									bUdpSockInited;				//  2004/05/23加
				 void							*		pEncCtx;
				 BOOL									bEncCtxInited;
				 QY_ENC_CTX								qnmEncCtx,  qnmUpdateCtx;	//  2004/10/19加
				 BOOL									bQnmEncCtxInited;

				 GENERIC_Q								monDataQ;					//  仅为interMon使用
				 HANDLE									hMutex;						//  仅为interMon使用
			
}														AWM_EXT;

typedef  struct  __awm_mon_proc_info_t					{
	
				 char									dataBuf[CONST_qyBufSize_upnp  +  1];			//  接收的数据包, 2004/05/23加,  2004/10/24由1024扩大了
				 int									nRecvd;											//  接收的包大小
				 char									recvdIp[MAX_IP_ADDR_LEN + 1];

}														AWM_MON_PROC_INFO;

typedef  struct  __intraMonThreadInfo_t					{
	
				 void							*		pDb;

}														INTRA_MON_THREAD_INFO;

typedef  struct  __scannedIpTabRcd_t					{
	
				 char									interMonIp[15 + 1];
				 char									officeName[MAX_AWM_MON_OFFICE_NAME_LEN + 1];
				 char									subOfficeName[MAX_AWM_MON_OFFICE_NAME_LEN + 1];
				 char									startIp[15 + 1];
				 char									endIp[15 + 1];	

}														SCANNED_IP_TAB_RCD;

/*
typedef  struct  __scanningLogTabRcd_t					{

				 unsigned  long							index;
				 char									officeName[MAX_AWM_MON_OFFICE_NAME_LEN + 1];
				 char									subOfficeName[MAX_AWM_MON_OFFICE_NAME_LEN + 1];
				 char									scannedIp[15 + 1];
				 char									recvdTime[14 + 1];	
				 char									mac[CONST_qyMacLen  +  1];	//  2004/05/22
				 char									compName[16  +  1];			//  2004/05/23
				 char									usrName[16  +  1];			//  2004/05/23
				 unsigned  char							is_server;					//  2004/05/23

}														SCANNING_LOG_TAB_RCD;
*/

#define		CONST_aeComputerInfoBufLen		(  MAX_AWM_MON_OFFICE_NAME_LEN  +  MAX_AWM_MON_SUB_OFFICE_NAME_LEN  +  MAX_IP_ADDR_LEN  +  CONST_qyMacLen  +  CONST_maxAwmMonCompNameLen  +  CONST_maxAwmMonUsrNameLen	 +  CONST_maxAwmMonIsServerLen  )

typedef  struct  __originalLogTabRcd_t					{

				 unsigned  long							index;
				 char									recvdTime[14 + 1];
				 char									computerInfoBuf[CONST_aeComputerInfoBufLen  +  1];

}														ORIGINAL_LOG_TAB_RCD;


typedef  struct  __awmInterMonLogProcInfo_t				{

				 int									procedIndex;
				 char									procedTime[14 + 1];

}														AWM_INTER_MON_LOG_PROC_INFO;


typedef  struct  __interMonThreadProcInfo_t				{

				 HANDLE									hMutex;
				 SOCKADDR_IN							sa;		//  Modified by ywm on 2002/11/05

}														INTER_MON_THREAD_PROC_INFO;

typedef  struct  __interMonDaemonThreadProcInfo_t		{

				 HANDLE									hMutex;
				 void								*	pDb;

}														INTER_MON_DAEMON_THREAD_PROC_INFO;

void  awmExtScan(  AWM_EXT  *  pAE,  int rawSockFd,  int  dGramSockFd,  char  *  srcIp,  char  *  dstIp,  char  *  data,  unsigned  int  dataSize  );
void  icmp_echo(  int  s,  unsigned  long  int  src,  unsigned  long  int  dest,  int  id,  int  seq,  char  *  data,  unsigned  int  datasize  );
void  awmIcmpEcho(  int  s,  char  *  srcIp,  char  *  dstIp,  char  *  data,  unsigned  int  dataSize  );

// What happened?
void  ReportError(  LPCSTR  pWhere  );
void  awmOutputStr(  char  *  str,  AWM_EXT  *  pAE  );
DWORD  WINAPI  intraMonThreadProc(  LPVOID  lpParameter  );
DWORD  WINAPI  interMonThreadProc0(  LPVOID  lpParam  );			//	用于绑定第0个地址
DWORD  WINAPI  interMonThreadProc1(  LPVOID  lpParam  );			//  用于绑定第1个地址
DWORD  WINAPI  interMonUdpThreadProc(  LPVOID  lpParam  );			//  用于绑定第1个地址
DWORD  WINAPI  interMonDaemonThreadProc(  LPVOID  lpParam  );
DWORD  WINAPI  interMonWarnThreadProc(  LPVOID  lpParam  );

int  initAwmInterMon(  AWM_EXT  *  pAE  );
void  exitAwmInterMon(  AWM_EXT  *  pAE  );
int  awmInterMonRun(  AWM_EXT  *  pAE  );
int  asrShowRegErr(  char  *  rootKey,  char  *  errStr  );
int  asrShowRegStatus(  char  *  rootKey,  char  *  statusStr  );
int  asrSetRegCfg(  char  *  rootKey,  char  *  cfgName,  char  *  cfgValue  );
int  setErrLogFile(  char  *  fileName  );
int  setErrLogHint(  char  *  hint  );
int  setErrHintWndTitle(  char  *  title  );
int  errLog(  char  *  fmt,  ...  );
int  truncFileHead(  int  nTruncated,  char  *  fileName  );

int  doInterMonServWork(  int  sockFd,  void  *  pp  );


int  processAwmUpnpInfo(  AWM_EXT  *  pAE, void  *  pp,  AWM_MON_PROC_INFO  *  pAmpi  );
int  processAwmMonPcInfo(  AWM_EXT  *  pAE,  void  *  pp,  AWM_MON_PROC_INFO  *  pAmpi  );
//
int  processAwmExtData(  AWM_EXT  *  pAE,  char  *  data,  size_t  dataLen,  AWM_MON_PROC_INFO  *  pAMPI,  INTER_MON_THREAD_PROC_INFO  *  pIMTPI  );





#ifdef  __cplusplus
 }
#endif

#endif	/*  }  */

