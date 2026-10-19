
#ifndef  __ASRWMONRAS_H__
#define  __ASRWMONRAS_H__	/* { */



//  #define		MAX_DETETCT_COUNT						10
#define		CONST_maxRasConns						5
#define		MAX_RAS_CONNS							CONST_maxRasConns


typedef  struct  __rasConnInfo_t					{
				 
				 //  char								szEntryName[128];		//  2004/10/30æ¿’˝¡À…œ ˆ¥ÌŒÛ
				 TCHAR								szEntryName[ RAS_MaxEntryName + 1 ];

				 DWORD								dwCountryCode;

    			 //  char					        szAreaCode[4  +  1];
				 //  char							szLocalPhoneNumber[13  +  1];
				 TCHAR								szAreaCode[ RAS_MaxAreaCode + 1 ];
    			 TCHAR								szLocalPhoneNumber[ RAS_MaxPhoneNumber + 1 ];

				 BOOL								bRasOn;
				 BOOL								bLogged;
				 unsigned  char						ucRasCmd;
				 HRASCONN							hRasConn;
				 
}		 RAS_CONN_INFO;


typedef  struct  __asr_ras_conn_grp_t				{
				 RAS_CONN_INFO						rCI[MAX_RAS_CONNS];				 
}		 ASR_RAS_CONN_GRP;

extern  ASR_RAS_CONN_GRP  gRasConn;


//
int  initRasConn(  ASR_RAS_CONN_GRP  *  gRasConn  );
//  int  saveLogToReg(  unsigned char *telcode );
int  detectRasConn(  QWM_THREADINFO  *  pThreadInfo  );
int  detectInvalidInternet(  QWM_THREADINFO  *  pThreadInfo  );
int	 detectProxyServer(  QWM_THREADINFO  *  pThreadInfo  );
int  detectAndWarnToInterMon(  QWM_THREADINFO  *  pSubThreadInfo  );
int  procDevRule(  QWM_THREADINFO  *  pSubThreadInfo  );
int  procOsRule(  QWM_THREADINFO  *  pSubThreadInfo  );
//  int  willReboot(  QY_W_MON  *  pQwm  );

//
int  procPcNetworkPropChangeAtStart(  QY_W_MON  *  pQwm  );
int  procPcNetworkPropChange(  void  *  lpParameter  );

//
int  procDetectionResult(  QWM_THREADINFO  *  pSubThreadInfo  );
int  doSecChk(  QWM_THREADINFO  *  pSubThreadInfo,  QY_DMITEM  *  pSecChkTaskTable  );
//  int  doReboot(  QWM_THREADINFO  *  pThreadInfo,  unsigned  char  ucbNoDlg,  unsigned  char  cantCancel,  unsigned  char  ucbForce  );
int  doReboot(  QWM_THREADINFO  *  pThreadInfo,  unsigned  char  ucbNoDlg,  unsigned  int  uiSteps,  unsigned  char  ucbForce  );
int  doRemoveUsb(  QWM_THREADINFO  *  pThreadInfo,  void  *  p1,  void  *  p2  );
int  showRemoteDesktop(  QWM_THREADINFO  *  pThreadInfo,  void  *  p1,  void  *  p2,  unsigned  char  ucbMonDesktop  );
int  doCapScreen(  QWM_THREADINFO  *  pThreadInfo,  void  *  p1,  void  *  p2  );
int  showNetFlowWarn(  QWM_THREADINFO  *  pThreadInfo,  void  *  p1,  void  *  p2  );

//
//  int  setQwmReg777(  void  );
extern  "C"  int  qwmGetProcessGrps(  QY_ENV  *  pEnv,  int  *  pFlg  );
//  extern  "C"  int  qwmDelService(  QWM_DYN_LIB  *  pDynLib,  char  *  serviceName  );
extern  "C"  int  qwmDelService(  QWM_DYN_LIB  *  pDynLib,  TCHAR  *  serviceName  );

int	 doQwmCmd(  void  *  lpParameter,  void  *  p1,  void  *  p2  );	//  2005/05/02

DWORD  WINAPI  qwmThreadProcFastCmd(  LPVOID  lpParameter  );
DWORD  WINAPI  qwmThreadProcCmd(  LPVOID  lpParameter  );
DWORD  WINAPI  qwmThreadPrinterMgr(  LPVOID  lpParameter  );
DWORD  WINAPI  qwmThreadFileMon(  LPVOID  lpParameter  );
DWORD  WINAPI  qwmThreadPcMon(  LPVOID  lpParameter  );
DWORD  WINAPI  qwmThreadCollectUsrLog(  LPVOID  lpParameter  );
DWORD  WINAPI  qwmThreadWndProc(  LPVOID  lpParameter  );





int  qwmCmdUpdate(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QWM_SESSION_BUF  *  pSessionBuf,  QY_SOCK  *  pSock  );
int  qwmCmdGetFile(  QY_W_MON  *  pQwm,  QWM_SESSION  *  pSession,  QWM_SESSION_BUF  *  pSessionBuf,  QY_SOCK  *  pSock  );

extern  "C"  int  qwmCmdBySubProcess(  void  *  p0,  LPCTSTR  cmdStr,  LPCTSTR  cmdParam,  HANDLE  *  phProcess  );


int  getRasPhoneNum(  void  *  pDynLibParam,  LPCTSTR  szEntryName,  RAS_CONN_INFO  *  pRasConnInfo  );
int  getWtsSessionId(  QY_ENV  *  pEnv,  DWORD  *  pCurSessionId,  DWORD  *  pActiveSessionId  );




#endif /* } */

