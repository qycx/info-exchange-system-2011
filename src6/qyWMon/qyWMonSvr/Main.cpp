
#include	<windows.h>
#include	<ras.h>
#include	<raserror.h>
#include	<main.h>

#include	<commandloop.h>
#include	<dll_load.h>
#include	<config.h>
#include	<process_hop.h>
#include	<Iphlpapi.h>

#include	<crtdbg.h>

#include	"asrWMon.h"
#include	"resource.h"
#include	<tchar.h>
#include	"qyTCharCommProc.h"

int _cdecl TCPIO_Insert(void);
int _cdecl TCPIO_Remove(void);

char  gQyCfgs[CONST_qySize_cfgs  +  1]  =  CONST_qyCfgSym
										CONST_qyCfgName_cntIp			"="		DEFAULT_qwmServIp
										" "
										CONST_qyCfgName_cntPort			"="		"8766"
										" "
										CONST_qyCfgName_qwmSeqNo		"="		""
										" "
										CONST_qyCfgName_systemId		"="		"3"
										" "
										CONST_qyCfgName_bGetPcAsset		"="		"1"
										" "
										CONST_qyCfgName_bNetMc2			"="		"1"
										" "
										CONST_qyCfgName_bSecChk			"="		"0"				//  2005/05/01
										"\0";


QY_W_MON				gQyWMon;
ASR_RAS_CONN_GRP		gRasConn;

HMODULE					g_module		=		NULL;
DWORD					g_dwThreadID	=		0;

BOOL					g_bRestart		=		FALSE;
char					g_svRestartProcess[64];
BOOL					g_bEradicate	=		FALSE;


// --------------- Stealth options ----------------
char g_svStealthOptions[]="<**CFG**>Stealth\0"
#ifdef HIDE_COPY
						  "B:Run at startup=1\0"
						  "B:Delete original file=1\0"
						  "B:Insidious mode=0\0"
#else
						  "B:Run at startup=0\0"
						  "B:Delete original file=0\0"
						  "B:Insidious mode=0\0"
#endif
                          //  "S[64]:Runtime pathname=qwmSvr.EXE\0.....................................................\0"
                          // "S[64]:Runtime pathname=UMGR32.EXE\0.....................................................\0"
#ifdef HOOK_PROCESS						  
						  "B:Hide process=1\0"
#else
						  "B:Hide process=0\0"
#endif
						  //  "S[48]:Host process name (NT)=EXPLORER\0.......................................\0"
						  "S[48]:Service Name (NT)=Qycx Network Agent\0..................................\0";


 //  size  ==  0  时，则不对pQyCfgs长度作出限制
 int  qwmParseCfgs(  QY_W_MON  *  pWMon  )
{
	 int				iErr		=	-1;
	 char			*	p			=	NULL;
	 char				buf[1024];
	 char			*	pQyCfgs		=	gQyCfgs;
	 unsigned  int		size		=	sizeof(  gQyCfgs  );

	 traceLogA(  "qwmParseCfgs: pQyCfgs is [%s]",  pQyCfgs  );

	 if  (  size  )  {
		 if  (  strlen(  pQyCfgs  )  >=  (  int  )size   )  return  -1;
	 }

	 //  2010/05/07
	 safeStrnCpy(  DEFAULT_qyCfgVal_cntIp,  pWMon->cfg.cnt.ip,  mycountof(  pWMon->cfg.cnt.ip  )  );	 //  lstrcpy(  pWMon->cfg.cnt.ip,  DEFAULT_qyCfgVal_cntIp  );

	 pWMon->cfg.cnt.port  =  DEFAULT_qyCfgVal_cntPort;
	 pWMon->cfg.iSystemId_wanted  =  DEFAULT_qyCfgVal_systemId;
	 
	 //  try to get cnt
	 if  (  parseQwmDynCfg(  pQyCfgs,  size,  &pWMon->cfg.dynCfg  )  )  goto  errLabel;
	 /*
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_cntIp,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 if  (  inet_addr(  p  )  !=  INADDR_NONE  )  {
			 lstrcpy(  pWMon->cfg.cnt.ip,  buf  );		 
		 }
	 }		 
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_cntPort,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.cnt.port  =  (  unsigned  short  )atol(  buf  );
	 }
	 */
	 if  (  bIpValid(  pWMon->cfg.dynCfg.cnt.cntIp  )  )  safeStrnCpy(  pWMon->cfg.dynCfg.cnt.cntIp,  pWMon->cfg.cnt.ip,  sizeof(  pWMon->cfg.cnt.ip  )  );
	 pWMon->cfg.cnt.port  =  pWMon->cfg.dynCfg.cnt.usCntPort;

	 //  2005/06/24
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_qwmSeqNo,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 safeStrnCpy(  p,  pWMon->cfg.seqNo,  sizeof(  pWMon->cfg.seqNo  )  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_systemId,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.iSystemId_wanted  =  (  unsigned  short  )atol(  buf  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bGetPcAsset,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbGetPcAsset  =  (  atol(  buf  )  ?  TRUE  :  FALSE  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bNetMc2,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbNetMc2  =  (  atol(  buf  )  ?  TRUE  :  FALSE  );
	 }

	 //  2005/05/02
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bSecChk,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbSecChk  =  (  atol(  buf  )  ?  TRUE  :  FALSE  );
	 }

	 iErr  =  0;	  

errLabel:

	 return  iErr;

}


#define		CONST_subKeyName_fdc							"SYSTEM\\CurrentControlSet\\Services\\Fdc"
#define		CONST_subKeyName_cdrom							"SYSTEM\\CurrentControlSet\\Services\\Cdrom"
#define		CONST_subKeyName_rootHub						"Enum\\USB\\ROOT_HUB"

#define		CONST_regValName_start							"Start"
#define		CONST_regValName_csConfigFlags					"CSConfigFlags"

#define		CONST_subKeyName_explorer						"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"
#define		CONST_regValName_noDrives						"NoDrives"




int  proc98DevRule(  QWM_THREADINFO  *  pSubThreadInfo  );
int	 procNtDevRule(  QWM_THREADINFO  *  pSubThreadInfo  );

 void EradicateAgent(void)
{	
	QWM_THREADINFO			threadInfo;
	QWM_THREAD_CFG			threadCfg;
	QY_W_MON			*	pQwm		=	&gQyWMon;
	QWM_DYN_LIB			*	pDynLib		=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	threadInfo.pParaentParam  =  &gQyWMon;
	threadInfo.pCfg  =  &threadCfg;
	
	 ////////////////////////////
	 traceLogA(  "EradicateAgent: recover rule"  );
	 gQyWMon.cfg.pcRules.dev.ucFloppyCmd  =  CONST_devCmd_permitted;
	 gQyWMon.cfg.pcRules.dev.ucCdromCmd  =  CONST_devCmd_permitted;
	 gQyWMon.cfg.pcRules.dev.ucUsbStorCmd  =  CONST_devCmd_permitted;
	 if  (  !g_bIsWinNT  )  proc98DevRule(  &threadInfo  );
	 else  procNtDevRule(  &threadInfo  );
	 /////////////////////////////////////////

	 #ifdef  __DEBUG__
			 qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_tc  ),  _T(  "0"  )  );
			 qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ph  ),  _T(  "0"  )  );
	 #endif


	TCHAR *svRunRegKey;
	TCHAR *tsvTarget		=		_T(  CONST_svTarget  );		//  GetCfgStr(g_svStealthOptions,"Runtime pathname");
	
	// Eradicate from run key
	if  (  g_bIsWinNT  )  {
		svRunRegKey  =  _T(  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"  );
		} 
	else  {
		svRunRegKey  =  _T(  "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"  );
	}

	HKEY key;
	
	RegOpenKey(HKEY_LOCAL_MACHINE,svRunRegKey,&key);
	RegDeleteValue(key,tsvTarget);
	RegCloseKey(key);
	
	if  (  g_bIsWinNT  )  {

		// Eradicate from user reg key
		RegOpenKey(HKEY_CURRENT_USER,_T(  "Software\\Microsoft\\Windows\\CurrentVersion\\Run"  ),&key);
		RegDeleteValue(key,tsvTarget);
		RegCloseKey(key);
		
		// Eradicate from service database
		SC_HANDLE  scm  =  pDynLib->pOpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
		if  (  scm  !=  NULL  )  {
			//  SC_HANDLE  srv  =  pDynLib->pOpenService(scm,GetCfgStr(g_svStealthOptions,"Service Name (NT)"),SERVICE_STOP|DELETE);
			SC_HANDLE  srv  =  pDynLib->pOpenService(scm, _T(  CONST_serviceName_NT  ),SERVICE_STOP|DELETE);
			if  (  srv  !=  NULL  )  {
				pDynLib->pDeleteService(srv);
				pDynLib->pCloseServiceHandle(srv);
			}
			pDynLib->pCloseServiceHandle(scm);
		}

		traceLog(  _T(  "delete %s %s" ),  gQyWMon.env.svRunKey,  _T(  CONST_regValName_qwmUsrScript  )  );
		char					buf[512]		=	"";
		if  (  !qyGetRegCfg(  gQyWMon.env.svRunKey,  _T(  CONST_regValName_qwmUsrScript  ),  buf,  sizeof(  buf  )  )  )  {
			qyDelRegCfg(  gQyWMon.env.svRunKey,  _T(  CONST_regValName_qwmUsrScript  )  );
		}

	}

	/*	//  2005/07/30, 防止瑞星报警
	char	*		svRunKey_autoReg	=		g_bIsWinNT  ?  CONST_qyCfgName_ntRunKey  :  CONST_qyCfgName_runOnceKey;
	 
	traceLogA(  "try to del %s\\%s",  svRunKey_autoReg,  CONST_regValName_autoReg  );
	if  (  !qyDelRegCfg(  svRunKey_autoReg,  CONST_regValName_autoReg  )  )  {
		traceLogA(  "删除自动注册项"  );
	}
	*/



	/*	//  2005/05/01
	*/
	delHelpFile(  _T(  CONST_hideProcessDll0  )  );		//  为了升级方便，采用了2个DLL做切换，故都要去除
	delHelpFile(  _T(  CONST_hideProcessDll1  )  );
	delHelpFile(  _T(  CONST_qwmHelp2Dll  )  );			//  这里也要删除qwmHelp2.dll
	delHelpFile(  _T(  CONST_qwmRdDll  )  );				//  2006/02/14
	delHelpFile(  _T(  CONST_qwmRdHelpDll  )  );			//  2006/02/14
	delHelpFile(  _T(  CONST_qwmHelp3Dll  )  );			//  2006/02/14


}

/*
 int  	recoverFdc()
{
	 int	iErr	=  -1;
  	 char				*	subKeyName		=  NULL;
	 char				*	regValName		=  NULL;
	 QY_REG		reg;
	 DWORD		start;
	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.uiType  =  REG_DWORD;

	 //  fdc:禁用start = 4;允许start =3;
	 subKeyName  =  CONST_subKeyName_fdc;
	 regValName	=  CONST_regValName_start;
	 start		=  3;

	 _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s",  subKeyName  );
	 if  (  tmpSetRegCfgEx(  &reg,  regValName,  (  char  *  )&start,  0  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  	recoverCdrom()
{
	 int	iErr	=  -1;
  	 char				*	subKeyName		=  NULL;
	 char				*	regValName		=  NULL;
	 QY_REG		reg;
	 DWORD		start;
	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.uiType  =  REG_DWORD;

	 //  cdrom:禁用start = 4;允许start =1;
	 subKeyName  =  CONST_subKeyName_cdrom;
	 regValName	=  CONST_regValName_start;
	 start		=  1;

	 _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s",  subKeyName  );
	 if  (  tmpSetRegCfgEx(  &reg,  regValName,  (  char  *  )&start,  0  )  )  goto  errLabel;


	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  	recover98Usb()
{
	 int	iErr	=  -1;
  	 char				*	subKeyName		=  NULL;
	 char				*	regValName		=  NULL;
	 QY_REG		reg;
	 DWORD		start;
	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.uiType  =  REG_DWORD;

	 //  usbFor98:禁用start = 1;允许start =0;
	 subKeyName  =  CONST_subKeyName_rootHub;
	 regValName	=  CONST_regValName_csConfigFlags;
	 start		=  0;

	 _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s",  subKeyName  );
	 if  (  tmpSetRegCfgEx(  &reg,  regValName,  (  char  *  )&start,  0  )  )  goto  errLabel;


	 iErr  =  0;
errLabel:
	 return  iErr;
}
*/

 //  2005/05/01
 int  delHelpFile(  TCHAR  *  CONST_hideProcessDll  )
{
	traceLog(  _T(  "try to MoveFile %s"  ),  CONST_hideProcessDll  ); 
		
	TCHAR		qwmHelpFileName[MAX_PATH  +  1]	=	_T(  ""  );
	TCHAR		tmpFileName[MAX_PATH  +  1]	=	_T(  ""  );

	//  
	GetTempPath(  mycountof(  qwmHelpFileName  ),  qwmHelpFileName  );
	GetTempFileName(  qwmHelpFileName,  _T(  "wrd"  ),  0,  tmpFileName  );
	traceLog(  _T(  "Del %s %s "  ),  tmpFileName,  (  DeleteFile(  tmpFileName  )  ?  _T(  "OK"  )  :  _T(  "Failed"  )  )  );			
	//	
	GetSystemDirectory(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
	trailDir(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
	lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  CONST_hideProcessDll,  mycountof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );
	SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
	traceLog(  _T(  "Move %s to %s %s"  ),  qwmHelpFileName,  tmpFileName,  (  MoveFile(  qwmHelpFileName,  tmpFileName  )  ?  _T(  "OK"  )  :  _T(  "Failed"  )  )  );

	return  0;

}


 LRESULT CALLBACK myWndProc(  HWND  hWnd, UINT  msg,  WPARAM wParam, LPARAM  lParam  );

// 
 DWORD WINAPI EntryPoint(LPVOID lpParameter)
{	
	HANDLE		hMutex				=	NULL;
	//  char		mutexName[256];
	BOOL		bTcpioInserted		=	FALSE;
	//  char		svLibName[MAX_PATH  +  1];
	HINSTANCE	tmph				=	NULL;

	traceLogA(  ""  );
	traceLogA( "EntryPoint( ): start." );
	
startofentrypoint:;

	g_bRestart  =  FALSE;

	g_module  =  (  HMODULE  )lpParameter;

	// Load up other DLLs just to make sure we have them (we're acting as a loader here).	

	/*
	if  (  qyFullLibName(  "kernel32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "user32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "gdi32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "winspool.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "advapi32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "shell32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "ole32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "oleaut32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	if  (  qyFullLibName(  "wsock32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	tmph  =  LoadLibrary(  svLibName  );
	*/


	if  (  TCPIO_Insert(  )  )  {
		traceLogA(  "TCPIO_Insert(  ) failed."  );
		goto  errLabel;
	}
	bTcpioInserted  =  TRUE;
	
	/*	
	if  (  g_bIsWinNT  )  wsprintf( mutexName, "%s%lu", DEFAULT_qwmMutexName,  GetCurrentProcessId(  )  );			
	else  wsprintf(  mutexName,  "%s",  DEFAULT_qwmMutexName  );
	traceLogA(  "EntryPoint(  ) has created mutex: [%s]",  mutexName  );

	hMutex = CreateMutex(  NULL,  TRUE,  mutexName  );
	if  (  !hMutex  ||  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
		traceLogA(  "EntryPoint( ): CreateMutex( ) failed. Maybe another thread has been running, so this thread must be quit."  );
		goto  errLabel;
	}
	traceLogA(  "%s has been created.",  mutexName  );
	 
	*/
	// Create useless window class
	WNDCLASS wndclass;
	wndclass.style = 0;
	//  wndclass.lpfnWndProc = DefWindowProc;
	wndclass.lpfnWndProc  =  myWndProc;			//  2007/02/27
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = g_module;
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = _T(  "WSCLAS"  );
	
	RegisterClass(&wndclass);

	// Determine OS version	
	GetOSVersion(  );

	// Use Dynamic Libraries

	// Enable permissions on Windows NT
	/*
	if  (  g_bIsWinNT  )  {
		HANDLE tok;
		if  (  pOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&tok)  )  {
			LUID luid;
			TOKEN_PRIVILEGES tp;
			pLookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&luid);
			tp.PrivilegeCount=1;
			tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid=luid;
			pAdjustTokenPrivileges(tok,FALSE,&tp,NULL,NULL,NULL);
		
			pLookupPrivilegeValue(NULL,SE_SECURITY_NAME,&luid);
			tp.PrivilegeCount=1;
			tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid=luid;
			pAdjustTokenPrivileges(tok,FALSE,&tp,NULL,NULL,NULL);
			CloseHandle(tok);
		}
	}
	*/

	// Start up Command Dispatcher
	// InitializeCommandDispatcher();

	// Initialize commands
	// InitializeCommands();

	// Do Primary Command Loop
	commandHandlerLoop();
		
	// Kill plugins
	//  TerminateCommands();

	// Kill Command Dispatcher
	//  KillCommandDispatcher();

	// Completely remove BO2K upon request
	if  (  g_bEradicate  )  {
		EradicateAgent(  );
		showQwmQuit(  &gQyWMon  );
	}

errLabel:

	//  //  2005/05/01 当进程退出时，肯定删除那个qwmHelp.dll
	//  delHelpDll(  );

	if ( bTcpioInserted ) TCPIO_Remove( );

	if ( hMutex ) { CloseHandle( hMutex ); hMutex = NULL; }
	
	// Kill Dynamic Libraries
	
	// Restart BO2K if desired	
	if  (  g_bRestart  )  {
		if  (  g_svRestartProcess[0]  ==  '\0'  )  goto  startofentrypoint;

		traceLogA(  "Hello, this will restart..."  );

		if  (  GetCfgBool(  g_svStealthOptions,  "Hide process"  )  &&  g_bIsWinNT  )  {
			if  (  !SpawnBO2KThread(  g_svRestartProcess  )  ) 
				goto  startofentrypoint;
			} 
		else 
			goto  startofentrypoint;
	}

	traceLogA( "EntryPoint( ) leave." );

	return  0;

}


// WinMain: Program Entry Point
extern "C" int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow);

VOID WINAPI Handler( DWORD fdwControl ) 
{
	
}


void WINAPI ServiceMain(DWORD dwArgc,LPTSTR *lpszArgv)
{
	QY_W_MON	*	pQwm	=	&gQyWMon;
	QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	//  SERVICE_STATUS_HANDLE ssh=pDynLib->pRegisterServiceCtrlHandler(GetCfgStr(g_svStealthOptions,"Service Name (NT)"), &Handler);
	SERVICE_STATUS_HANDLE ssh=pDynLib->pRegisterServiceCtrlHandler(  _T(  CONST_serviceName_NT  ), &Handler);

	SERVICE_STATUS ss;
	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;
	ss.dwCurrentState=SERVICE_RUNNING;
	ss.dwControlsAccepted=0;
	ss.dwWin32ExitCode=NO_ERROR;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	pDynLib->pSetServiceStatus(ssh,&ss);

	EntryPoint(GetModuleHandle(NULL));

	ss.dwServiceType=SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;
	ss.dwCurrentState=SERVICE_STOPPED;
	ss.dwControlsAccepted=0;
	ss.dwWin32ExitCode=NO_ERROR;
	ss.dwCheckPoint=0;
	ss.dwWaitHint=0;
	pDynLib->pSetServiceStatus(ssh,&ss);
}
 
#define		CONST_qwmAgentName				"qwmSvr.exe"
//
#define		CONST_qyRootKey_qwmService		"SYSTEM\\CurrentControlSet\\Services\\Qycx Network Agent"
	#define		CONST_regValName_displayName	"DisplayName"		//  REG_SZ
		#define		CONST_regValData_qwmDisplayName		"Qycx Network Agent"
	#define		CONST_regValName_errorControl	"ErrorControl"		//  REG_DWORD
		#define		CONST_regValData_qwmErrorControl	0
	#define		CONST_regValName_imagePath		"ImagePath"			//  REG_EXPAND_SZ
	#define		CONST_regValName_objectName		"ObjectName"		//  REG_SZ
		#define		CONST_regValData_qwmObjectName		"LocalSystem"
	#define		CONST_regValName_start			"Start"				//  REG_DWORD
		#define		CONST_regValData_qwmStart			2
	#define		CONST_regValName_type			"Type"				//	REG_DWORD
		#define		CONST_regValData_qwmType			0x110
 //
 int  chkAndRepairQwmService(  void  *  pQwmParam  )
{
	 QY_W_MON		*	pQwm	=	(  QY_W_MON  *  )pQwmParam;
	 //  char				buf[256];
	 long				lBuf;
	 QY_REG				reg;
	 TCHAR			*	pCfg	=	NULL;
	 TCHAR			*	pData	=	NULL;
	 long				lData;
	 unsigned  int		len;
	 TCHAR				tBuf[MAX_PATH  +  1];
	 TCHAR				imagePath[MAX_PATH  +  1];
	 
	 //  traceLogA(  "chkAndRepairQwmService enters"  );

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 safeTcsnCpy(  _T(  CONST_qyRootKey_qwmService  ),  reg.rootKey,  mycountof(  reg.rootKey  )  );

	 pCfg  =  _T(  CONST_regValName_displayName  );	pData  =  _T(  CONST_regValData_qwmDisplayName  );
	 if  (  qyGetRegCfg(  reg.rootKey,  pCfg,  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 if  (  lstrcmpi(  tBuf,  pData  )  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 
		 qySetRegCfg(  reg.rootKey,  pCfg,  pData  );
	 }
	 //
	 pCfg  =  _T(  CONST_regValName_errorControl  );	lData  =  CONST_regValData_qwmErrorControl;
	 len  =  sizeof(  lData  );
	 if  (  tmpGetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lBuf,  &len  )  )  lBuf  =  -1;
	 if  (  lBuf  !=  lData  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 
		 reg.uiType  =  REG_DWORD;  tmpSetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lData,  sizeof(  lData  )  );
	 }
	 //
	 pCfg  =  _T(  CONST_regValName_imagePath  );  
	 qwmGetSystemDirectory(  &pQwm->env,  imagePath,  mycountof(  imagePath  )  -  1  );
	 trailDir(  imagePath,  mycountof(  imagePath  )  );
	 _sntprintf(  imagePath,  mycountof(  imagePath  ),  _T(  "%s%s"  ),  imagePath,  _T(  CONST_qwmAgentName  )  );
	 if  (  tQyQuoteFileName(  imagePath,  mycountof(  imagePath  )  )  )  goto  errLabel;
	 pData  =  imagePath;
	 //
	 len  =  sizeof(  tBuf  );
	 if  (  tmpGetRegCfgEx(  &reg,  pCfg,  (  char  *  )tBuf,  &len  )  )  tBuf[0]  =  0;
	 if  (  lstrcmpi(  tBuf,  pData  )  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 
		 reg.uiType  =  REG_EXPAND_SZ;  tmpSetRegCfgEx(  &reg,  pCfg,  (  char  *  )pData,  0  );
	 }
	 //
	 pCfg  =  _T(  CONST_regValName_objectName  );	pData  =  _T(  CONST_regValData_qwmObjectName  );
	 if  (  qyGetRegCfg(  reg.rootKey,  pCfg,  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 if  (  lstrcmpi(  tBuf,  pData  )  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 
		 qySetRegCfg(  reg.rootKey,  pCfg,  pData  );
	 }
	 //
	 pCfg  =  _T(  CONST_regValName_start  );	lData  =  CONST_regValData_qwmStart;
	 len  =  sizeof(  lData  );
	 if  (  tmpGetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lBuf,  &len  )  )  lBuf  =  -1;
	 if  (  lBuf  !=  lData  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 
		 reg.uiType  =  REG_DWORD;  tmpSetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lData,  sizeof(  lData  )  );
	 }
	 //
	 pCfg  =  _T(  CONST_regValName_type  );	lData  =  CONST_regValData_qwmType;
	 len  =  sizeof(  lData  );
	 if  (  tmpGetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lBuf,  &len  )  )  lBuf  =  -1;
	 if  (  lBuf  !=  lData  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 
		 reg.uiType  =  REG_DWORD;  tmpSetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lData,  sizeof(  lData  )  );
	 }

errLabel:

	 //  traceLogA(  "chkAndRepairQwmService leaves"  );

	 return  0;
}


#define		CONST_wKey_hardwareProfiles			"SYSTEM\\CurrentControlSet\\Hardware Profiles"
#define		CONST_subKey_legacyService_qwm		"System\\CurrentControlSet\\Enum\\ROOT\\LEGACY_QYCX_NETWORK_AGENT\\0000"
#define		CONST_regValName_CSConfigFlags		"CSConfigFlags"

 int  tmpHandler_chkAndStartQwmLegacyService(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	QY_PC_REGISTRYVAL	*	pVal						=	(  QY_PC_REGISTRYVAL  *  )p2;
	QY_REG					reg;
	DWORD					dwVal;

	if  (  !pVal->ucbKey  )  return  0;

	traceLogA(  "%S",  pVal->wCfgName  );
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_LOCAL_MACHINE;
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s\\%s"  ),  _T(  CONST_wKey_hardwareProfiles  ),  pVal->wCfgName,  _T(  CONST_subKey_legacyService_qwm  )  );
	if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_CSConfigFlags  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  
		&&  dwVal  )
	{
		dwVal  =  0;
		tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_CSConfigFlags  ),  (  char  *  )&dwVal,  0  );
	}

	 return  0;
}

 int  chkAndStartQwmLegacyService(  void  *  pQwmParam  )
{
	QY_W_MON	*	pQwm					=	(  QY_W_MON  *  )pQwmParam;

	enumReg(  &pQwm->env,  0,  HKEY_LOCAL_MACHINE,  _T(  CONST_wKey_hardwareProfiles  ),  tmpHandler_chkAndStartQwmLegacyService,  0,  0  );

	return  0;
}



 int  chkAndRepairQwmUsrScript(  void  *  pQwmParam  )		//  2007/01/16
{
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pQwmParam;	
	 //  QY_REG					reg;
	 //  char			*		pCfg;
	 //  char			*		pData;
	 //  char					dataBuf[512]	=	"";
	 //  char					buf[512]		=	"";

	 return  0;		//  2007/02/28, 暂时不需要run键值了，

	 /*
	 GetSystemDirectory(  dataBuf,  mycountof(  dataBuf  )  );
	 trailDir(  dataBuf,  mycountof(  dataBuf  )  );
	 _snprintf(  dataBuf,  mycountof(  dataBuf  ),  "%s%s %s",  dataBuf,  CONST_processName_qwmSvr,  CONST_qwmCmdLine_usrScript  );

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_LOCAL_MACHINE;
	 _snprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  "%s",  pQwm->env.svRunKey  );
	 	 
	 pCfg  =  CONST_regValName_qwmUsrScript;	pData  =  dataBuf;
	 if  (  qyGetRegCfg(  reg.rootKey,  pCfg,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 if  (  strcmpi(  buf,  pData  )  )  {
		 traceLogA(  "%s的值改了",  pCfg  );	 qySetRegCfg(  reg.rootKey,  pCfg,  pData  );
	 }
	 */

	 return  0;
}
 ////////

 int  distributeDll(  QY_W_MON  *  pQwm,  unsigned  char  ucbMainFileUpdated,  TCHAR  *  pureDllName,  PF_bCommonHandler  pfbSupportedOs,  unsigned  short  usIdrData  )
{	 
	 TCHAR				qwmHelpFileName[MAX_PATH  +  1]		=	_T(  ""  );
	 unsigned  char		ucbQwmHelpFileNotExists				=  TRUE;
	 TCHAR				tmpFileName[MAX_PATH  +  1]			=	_T(  ""  );
	 unsigned  char		ucbDllVerRight						=  FALSE;

	 
	 if  (  ucbMainFileUpdated  ||  !bMyQwmHelpDllVerRight(  pQwm->env.iPlatformId,  pureDllName,  pfbSupportedOs  )  )  {

				ucbDllVerRight						=  FALSE;
				ucbQwmHelpFileNotExists				=  TRUE;

				GetSystemDirectory(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				trailDir(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  pureDllName,  mycountof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );

				//  如果文件存在则先删移除该文件
				if  (  GetFileAttributes(  qwmHelpFileName  )  !=  0xFFFFFFFF  )  {
					SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
					if  (  !DeleteFile(  qwmHelpFileName  )  )  ucbQwmHelpFileNotExists  =  FALSE;
					traceLogA(  "%s文件存在, 删除该文件%s",  qwmHelpFileName,  ucbQwmHelpFileNotExists  ?  "sucessfully"  :  "failed"  );
				}

				if  (  !ucbDllVerRight  )  {
					traceLogA(  "准备生成%s",  pureDllName  );	
					if  (  qyOutputResourceFile(  usIdrData,  qwmHelpFileName  )  )  traceLogA(  "生成%s失败",  qwmHelpFileName  );  
					else  traceLogA(  "生成%s成功",  qwmHelpFileName  );
				}

			
	 }	//  版本不正确的处理  

	 return  0;

}
 //////////

#define		CONST_qnmTmpFilePrefix	_T(  "wrd"  )

 int  tmpHandler_clearQnmTmpFile(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr			=	-1;
	 TCHAR				*	pDir			=	(  TCHAR  *  )p1;
	 WIN32_FIND_DATA	*	pData			=	(  WIN32_FIND_DATA  *  )p2;
	 TCHAR				*	p;
	 unsigned  char			ucbNeedToDel	=	FALSE;
	 TCHAR					tBuf[MAX_PATH  +  1];

	 //  traceLogA(  "得到%s",  pData->cFileName  );
	 if  (  bDir(  pData->cFileName  )  )  return  0;

	 if  (  !_tcsnicmp(  CONST_qnmTmpFilePrefix,  pData->cFileName,  lstrlen(  CONST_qnmTmpFilePrefix  )  )  )  {
		 p  =  _tcschr(  pData->cFileName,  _T(  '.'  )  );
		 if  (  p  )  {
			 p  ++  ;
			 if  (  !_tcsicmp(  p,  _T(  "tmp"  )  )  )  {
				 ucbNeedToDel  =  TRUE;
			 }
		 }
	 } 

	 if  (  ucbNeedToDel  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pDir  );
		 if  (  tTrailDir(  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;	
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  pData->cFileName  );
		 //  DeleteFile(  pData-
		 BOOL  bDel  =  DeleteFile(  tBuf  );
		 traceLog(  _T(  "%s %s"  ),  tBuf,  bDel  ?  _T(  "deleted"  )  :  _T(  "can't be delelted"  )  );
	 }
	 //  else  traceLogA(  "%s is no out tmp file",  pData->cFileName  );

	 iErr  =  0;
errLabel:
	 return  0;		// 这里要防止中途退出，这样将使文件不能顺利清理完毕
}


 //  要注意只能清理"wrd*.tmp"类型的文件，其他都不能动
 int  clearQnmTmpFile(  QY_ENV  *  pEnv  )
{
	 int	iErr						=	-1;
	 TCHAR	tmpPath[MAX_PATH  +  1];
	 
	 traceLogA(  "Now start to clear temporary file ... "  );		//  2006/07/02

	 if  (  !GetTempPath(  mycountof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;

	 if  (  qwmEnumUsrDir(  pEnv,  tmpPath,  tmpHandler_clearQnmTmpFile,  0,  tmpPath  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 traceLogA(  "Clearing temporary file finishes with %s",  iErr  ?  "failed"  :  "ok"  );		//  2006/07/02

	 return  iErr;
}





 int  WINAPI  WinMain(  HINSTANCE  hInst,  HINSTANCE  hPrev,  LPSTR  lpCmdLine,  int  nCmdShow  )
{
	int								iErr					=	-1;
	BOOL							bDynLibInited			=	FALSE;
	BOOL							bHideProcess			=	TRUE;
	BOOL							bRunAtStartup			=	TRUE;
	TCHAR							svFileName[512];
	TCHAR						*	pFinalModuleName		=	NULL;
	TCHAR							tmpPath[MAX_PATH  +  1];
	TCHAR							tmpFileName[MAX_PATH  +  1];
	QY_REG							tmpReg;
	int								iGrpFlg;
	unsigned  char					ucbTcpioInserted		=	FALSE;
	TCHAR						*	tmppCmdLine				=	NULL;
	TCHAR							cmdLineBuf[128]			=	_T(  ""  );
	TCHAR						*	p;
	QWM_DYN_LIB					*	pDynLib					=	NULL;
	QY_W_MON					*	pQwm					=	&gQyWMon;


	g_module  =  GetModuleHandle(  NULL  );
	GetOSVersion(  );
		
	traceLogA(  "     区别"  );
	if  (  initDynLib(  (  void  **  )&pDynLib  )  )  {
		traceLogA(  "InitDynamicLibraries(  ) failed."  );
		goto  errLabel;
	}
	bDynLibInited  =  TRUE;

	if  (  TCPIO_Insert(  )  )  goto  errLabel;					//加载库时需要提前运行该函数
	ucbTcpioInserted  =  TRUE;

	memset(  &gQyWMon,  0,  sizeof(  gQyWMon  )  );
	gQyWMon.iSystemId	=  qyGetSystemId(  );	
	gQyWMon.iAppType	=  CONST_qyAppType_qwmSvr;
	gQyWMon.iCustomId	=  qyGetCustomId(  );
	gQyWMon.iServiceId	=  CONST_qyServiceId_qwm;
	memcpy(  gQyWMon.ver,  qnmVerStr(  gQyWMon.iServiceId  ),  sizeof(  gQyWMon.ver  )  -  1  );
	gQyWMon.env.usLangId  =  GetSystemDefaultLangID(  );
	GetWindowsDirectory(  tmpPath,  mycountof(  tmpPath  )  );  lstrcpyn(  gQyWMon.wWinDir,  tmpPath,  mycountof(  gQyWMon.wWinDir  )  );			//  2006/03/18
	GetSystemDirectory(  tmpPath,  mycountof(  tmpPath  )  );  lstrcpyn(  gQyWMon.wSystemDir,  tmpPath,  mycountof(  gQyWMon.wSystemDir  )  );		//  2006/03/17

	//  2003/09/12将下面函数替换
	//  if  (  !bQyGetSystemVersion( &iPlatformId,  productStr,  sizeof(  productStr  ),  NULL  )  )  goto  errLabel;
	/*if  (  !bQyGetSystemVersionEx( &iPlatformId,  gQyWMon.env.systemBuf,  sizeof(  gQyWMon.env.systemBuf  ),  gQyWMon.env.servicePackBuf,  sizeof(  gQyWMon.env.servicePackBuf  ),  NULL  )  )  goto  errLabel;

	gQyWMon.env.iPlatformId  =  iPlatformId;
	if  (  g_bIsWinNT  )  gQyWMon.env.svRunKey  =  CONST_qyCfgName_ntRunKey;
	else  gQyWMon.env.svRunKey  =  CONST_qyCfgName_98RunKey;
	*/
	getQyEnv(  pDynLib,  &gQyWMon.env  );
	//
	if  (  pQwm->env.iPlatformId  ==  CONST_qyPlatform_unknown  ||  pQwm->env.iPlatformId  ==  CONST_qyPlatform_win32  ||  pQwm->env.iPlatformId  ==  CONST_qyPlatform_win95  )  goto  errLabel;

	if  (  getProcessUsrAndDomain(  &pQwm->env,  GetCurrentProcessId(  ),  pQwm->wUsrName,  mycountof(  pQwm->wUsrName  ),  pQwm->wDomainName,  mycountof(  pQwm->wDomainName  )  )  )  {
		pQwm->wUsrName[0]  =  0;  pQwm->wDomainName[0]  =  0;  
	}

	{
		TCHAR	logFileName[128]	=	_T(  ""  );
		//
		_sntprintf(  logFileName,  mycountof(  logFileName  ),  _T(  "%s.%s.log"  ),  _T(  "qwmSvr"  ),  pQwm->wUsrName  );
		//
		setDebugLogFileName(  logFileName  );	//  2007/01/16
		setTraceLogToFile(  TRUE  );
	}

	//
#ifdef  __DEBUG__
	traceLog(  _T(  "IsWow64Process is %d"  ),  gQyWMon.env.bWow64Process  );
	if  (  pDynLib->pIsWow64Process  )  traceLog(  _T(  "pIsWow64Process is not null"  )  );
#endif

	if  (  initQnmEnc(  &gQyWMon.encCtx,  &gQyWMon.updateEncCtx,  &gQyWMon.quitEncCtx,  &gQyWMon.commEncCtx  )  )  goto  errLabel;
	gQyWMon.status.ulbEncInited  =  TRUE;

	//  以下分析命令行参数
	tmppCmdLine  =  GetCommandLine(  );
	traceLog(  _T(  "cmdLine is %s"  ),  tmppCmdLine  ?  tmppCmdLine  :  _T(  ""  )  );
	if  (  tmppCmdLine  )  safeTcsnCpy(  tmppCmdLine,  cmdLineBuf,  mycountof(  cmdLineBuf  )  );
	tTrim(  cmdLineBuf  );

	for  (  p  =  cmdLineBuf;  *p;  p  ++  )  {
		 TCHAR						*	pCmdOpt		=	NULL;

		 //  traceLogA(  "p is [%s], ri is [%s],  ro is [%s]",  p,  CONST_qwmCmdLine_regAndInstall,  CONST_qwmCmdLine_regOnly  );
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_regOnly  ),  lstrlen(  _T(  CONST_qwmCmdLine_regOnly  )  )  )  )  {
			  traceLogA(  "命令行参数：仅注册"  );
			  gQyWMon.cmd.ulbRegOnly  =  TRUE;
		 }
		 //  if  (  !strnicmp(  p,  CONST_qwmCmdLine_bChild,  lstrlen(  CONST_qwmCmdLine_bChild  )  )  )  {
		 // 	 traceLogA(  "命令行参数：是子进程，需要执行任务"  );
		 // 	 gQyWMon.cmd.ulbChild  =  TRUE;
		 //  }
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_doSecChk  ),  lstrlen(  _T(  CONST_qwmCmdLine_doSecChk  )  )  )  )  {
			 traceLogA(  "命令行参数：需要执行安检任务"  );
			 gQyWMon.cmd.ulbDoSecChk  =  TRUE;
		 }
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_chdRespOk  ),  lstrlen(  _T(  CONST_qwmCmdLine_chdRespOk  )  )  )  )  {
			 traceLogA(  "命令行参数：需要响应字符串"  );
			 _sntprintf(  gQyWMon.cmd.respOkStr,  mycountof(  gQyWMon.cmd.respOkStr  ),  _T(  "%s"  ),  p  +  lstrlen(  _T(  CONST_qwmCmdLine_chdRespOk  )  )  );	//  2005/05/04
		 }
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_doReboot  ),  lstrlen(  _T(  CONST_qwmCmdLine_doReboot  )  )  )  )  {
			 traceLogA(  "命令行参数：需要重起"  );
			 gQyWMon.cmd.ulbDoReboot  =  TRUE;
		 }
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_doRemoveUsb  ),  lstrlen(  _T(  CONST_qwmCmdLine_doRemoveUsb  )  )  )  )  {	//  2005/10/08
			 traceLogA(  "命令行参数：可以用来卸载USB"  );
			 gQyWMon.cmd.ulbDoRemoveUsb  =  TRUE;
		 }

		 #ifndef  __NOTSUPPORT_REMOTEDESKTOP__	//  2009/01/17
				  if  (  !strnicmp(  p,  CONST_qwmCmdLine_viewRemoteDesktop,  lstrlen(  CONST_qwmCmdLine_viewRemoteDesktop  )  )  )  {  //  2006/02/12
					  traceLogA(  "命令行参数：查看远程桌面"  );
					  gQyWMon.cmd.ulbViewRemoteDesktop  =  TRUE;
				  }
				  if  (  !strnicmp(  p,  CONST_qwmCmdLine_monDesktop,  lstrlen(  CONST_qwmCmdLine_monDesktop  )  )  )  {  //  2006/03/06
					  traceLogA(  "命令行参数:  屏幕监控"  );
					  gQyWMon.cmd.ulbMonDesktop  =  TRUE;
				  }
		 #endif

		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_capScreen  ),  lstrlen(  _T(  CONST_qwmCmdLine_capScreen  )  )  )  )  {  //  2006/03/06
			 traceLogA(  "命令行参数:  抓屏"  );
			 gQyWMon.cmd.ulbCapScreen  =  TRUE;
		 }
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_monIe  ),  lstrlen(  _T(  CONST_qwmCmdLine_monIe  )  )  )  )  {  //  2006/03/06
			 traceLogA(  "命令行参数:  IE监控"  );
			 gQyWMon.cmd.ulbMonIe  =  TRUE;
		 }
		 if  (  !_tcsnicmp(  p,  _T(  CONST_qwmCmdLine_netFlowWarn  ),  lstrlen(  _T(  CONST_qwmCmdLine_netFlowWarn  )  )  )  )  {  //  2006/03/06
			 traceLogA(  "命令行参数:  netFlowWarn"  );
			 gQyWMon.cmd.ulbNetFlowWarn  =  TRUE;
			 gQyWMon.cmd.ucbDownNetworkCard  =  (  *(  p  +  lstrlen(  _T(  CONST_qwmCmdLine_netFlowWarn  )  )  )  ==  _T(  '1'  )  )  ?  TRUE  :  FALSE;
			 gQyWMon.cmd.usTotalProgress  =  (  unsigned  short  )_ttol(  p  +  lstrlen(  _T(  CONST_qwmCmdLine_netFlowWarn  )  )  +  1  );
		 }
		 pCmdOpt  =  _T(  CONST_qwmCmdLine_usrScript  );
		 if  (  !_tcsnicmp(  p,  pCmdOpt,  lstrlen(  pCmdOpt  )  )  )  {	//  2007/01/11
			 gQyWMon.cmd.ulbUsrScript  =  TRUE;	
			 gQyWMon.cmd.ulProcessId_remoteProcess  =  (  unsigned  long  )_ttol(  p  +  lstrlen(  pCmdOpt  )  );

			 traceLogA(  "cmdLine: usrScript, ulProcessId_remoteProcess is %u",  gQyWMon.cmd.ulProcessId_remoteProcess  );			 
		 }
		 pCmdOpt  =  _T(  CONST_qwmCmdLine_recoveredByQwmHelp2  );
		 if  (  !_tcsnicmp(  p,  pCmdOpt,  lstrlen(  pCmdOpt  )  )  )  {	//  2005/07/30
			 gQyWMon.cmd.ulbRecoveredByQwmHelp2  =  TRUE;
			 gQyWMon.cmd.ulProcessId_remoteProcess  =  (  unsigned  long  )_ttol(  p  +  lstrlen(  pCmdOpt  )  );

			 traceLogA(  "cmdLine: 被qwmHelp2恢复, ulProcessId_remoteProcess is %u",  gQyWMon.cmd.ulProcessId_remoteProcess  );			 
		 }
		 pCmdOpt  =  _T(  CONST_qwmCmdLine_startProtectingThread_sys  );
		 if  (  !_tcsnicmp(  p,  pCmdOpt,  lstrlen(  pCmdOpt  )  )  )  {	//  2007/01/31
			 gQyWMon.cmd.ulbStartProtectingThread_sys  =  TRUE;
			 gQyWMon.cmd.ulProcessId_remoteProcess  =  (  unsigned  long  )_ttol(  p  +  lstrlen(  pCmdOpt  )  );

			 traceLogA(  "cmdLine: startProctingThread_sys, remoteProcId is %u",  gQyWMon.cmd.ulProcessId_remoteProcess  );			 
		 }
		 pCmdOpt  =  _T(  CONST_qwmCmdLine_startProtectingThread_usr  );
		 if  (  !_tcsnicmp(  p,  pCmdOpt,  lstrlen(  pCmdOpt  )  )  )  {	//  2007/01/31
			 gQyWMon.cmd.ulbStartProtectingThread_usr  =  TRUE;
			 gQyWMon.cmd.ulProcessId_remoteProcess  =  (  unsigned  long  )_ttol(  p  +  lstrlen(  pCmdOpt  )  );

			 traceLogA(  "cmdLine: startProctingThread_usr, remoteProcId is %u",  gQyWMon.cmd.ulProcessId_remoteProcess  );			 
		 }


		 //
	}	

	if  (  qwmParseCfgs(  &gQyWMon  )  )  goto  errLabel;
	
	//  2004/11/15取消对systemId的限制，功能上区分通过开关量来实现
	//  校验systemId
	gQyWMon.iSystemId  =  gQyWMon.cfg.iSystemId_wanted;
	if  (  gQyWMon.iSystemId  !=  CONST_qySystemId_netMc2  )  {
		traceLogA(  "iSystemId错误：正确设置iSystemId后再生产"  );  goto  errLabel;
	}
	
	if  (  getQwmInitialCfg(  &gQyWMon  )  )  goto  errLabel;
	

	//  2007/01/18, 初步赋一些值
	_sntprintf(  pQwm->pureDllName,  mycountof(  pQwm->pureDllName  ),  _T(  "%s"  ),  _T(  CONST_hideProcessDll0  )  );  
	_sntprintf(  pQwm->pure2DllName,  mycountof(  pQwm->pure2DllName  ),  _T(  "%s"  ),  _T(  CONST_qwmHelp2Dll  )  );  
	_sntprintf(  pQwm->pure3DllName,  mycountof(  pQwm->pure3DllName  ),  _T(  "%s"  ),  _T(  CONST_qwmHelp3Dll  )  );
	_sntprintf(  pQwm->pureRdHelpDllName,  mycountof(  pQwm->pureRdHelpDllName  ),  _T(  "%s"  ),  _T(  CONST_qwmRdHelpDll  )  );
	_sntprintf(  pQwm->pureRdDllName,  mycountof(  pQwm->pureRdDllName  ),  _T(  "%s"  ),  _T(  CONST_qwmRdDll  )  );


	// Get current module location
	GetModuleFileName(  g_module,  svFileName,  mycountof(  svFileName  )  );
	for  (  pFinalModuleName  =  svFileName  +  lstrlen(  svFileName  )  -  1;  pFinalModuleName  >  svFileName;  pFinalModuleName  --  )  {
		 if  (  *pFinalModuleName  ==  _T(  '\\'  )  )  {	
			 pFinalModuleName  ++  ;	 break;
		 }
	}
	traceLog(  _T(  "File name is %s,  finalModuleName is %s"  ),  svFileName,  pFinalModuleName  );
	
	// 以下为qywmonsvr.exe而写
	if  (  !lstrcmpi(  pFinalModuleName,  _T(  CONST_qwmLogonScriptName  )  )  )  {
		if  (  pQwm->env.iPlatformId  !=  CONST_qyPlatform_win98  &&  pQwm->env.iPlatformId  !=  CONST_qyPlatform_winme  &&  pQwm->env.iPlatformId  !=  CONST_qyPlatform_nt  )  {
			traceLogA(  "this OSVersion isn't one among win98, winme, nt,  现在登录脚本准备退出..."  );
			goto errLabel;
		}	
	}
	
	//  2006/07/02发现居然临时文件满了，建不动了，故增加下面的处理
	clearQnmTmpFile(  &gQyWMon.env  );

	if  (  !GetTempPath(  mycountof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
	if  (  !GetTempFileName(  tmpPath,  _T(  "wrd"  ),  0,  tmpFileName  )  )  goto  errLabel;
	
	traceLogA(  "qyWMonSvr starts...ver is [%s], developing timestamp is [%s]----------------",  qnmVerStr(  gQyWMon.iServiceId  ),  qnmDevelopTimestamp(  )  );
	
	//  Modified by wht 2002/04/13
	//  memset(  &aCCI,  0,  sizeof(  aCCI  )  );
	//  initWMState(  &aCCI  );
	//  checkAsrWMonNO(  &aCCI  );
	//  Modified by wht 2002/04/13
		
	//  注意：这里暂时将setQwmReg777注释了，因为考虑到对NT已经扩充到系统服务，有足够的权限。
	//  if  (  g_bIsWinNT  )  {
	// 		if  (  setQwmReg777(  )  )  {
	//			traceLogA(  "setQwmReg777(  ) failed."  );
	//			goto  errLabel;
	//		}		
	//  }

	#ifdef  __DEBUG__
			testInitQwmHookInMain(  );
	#endif

	//  对注册程序，注册完毕即退出
	/*  //  受控端不再提供注册功能
	if  (  gQyWMon.cmd.ulbRegOnly  )  {
		QWM_REG_STRUCT		qwmRegStruct;

		traceLogA(  "qyWMonSvr: 现执行注册功能"  );
		memset(  &qwmRegStruct,  0,  sizeof(  qwmRegStruct  )  );
		qwmRegStruct.ucbInstall  =  FALSE;
		qwmRegStruct.pCnt  =  &gQyWMon.cfg.cnt;
		qwmRegStruct.idrData  =  0;
	
		qwmRegProc(  &qwmRegStruct  );
		goto  errLabel;
	}
	*/

	//  2005/10/08, 增加了对卸载USB的命令
	if  (  gQyWMon.cmd.ulbDoSecChk  
		||  gQyWMon.cmd.ulbDoReboot  
			||  gQyWMon.cmd.ulbDoRemoveUsb
				||  gQyWMon.cmd.ulbViewRemoteDesktop
					||  gQyWMon.cmd.ulbCapScreen
						||  gQyWMon.cmd.ulbMonDesktop
							||  gQyWMon.cmd.ulbMonIe
								||  gQyWMon.cmd.ulbNetFlowWarn
									||  gQyWMon.cmd.ulbStartProtectingThread_sys
										||  gQyWMon.cmd.ulbStartProtectingThread_usr  )  
	{													//  2005/05/02增加使安检的功能

		traceLogA(  "to doQwmCmd"  );
		iErr  =  doQwmCmd(  &gQyWMon,  0,  0  );
		traceLogA(  "doQwmCmd finished"  );
		goto  errLabel;
	}

	if  (  gQyWMon.cmd.ulbUsrScript  )  {	//  2007/01/14
		commandHandlerLoop_usrScript(  );
		traceLogA(  "CommandHandlerLoop_usrScript(  ) ends"  );
		iErr  =  0;  
		goto  errLabel;
	}

	//
	//
	//  下面开始了自动安装与恢复过程
//  realStart:

	// Get stealth options
	bHideProcess  =  GetCfgBool(  g_svStealthOptions,  "Hide process"  );
	bRunAtStartup  =  GetCfgBool(  g_svStealthOptions,  "Run at startup"  );

	traceLogA(  bHideProcess  ?  "bHideProcess is true."  :  "bHideProcess is false."  );
	traceLogA(  bRunAtStartup  ?  "bRunAtStartup is true."  :  "bRunAtStartup is false."  );
	
	// Determine how things should run at startup
	if  (  bRunAtStartup  )  {
		// Install levels:
		// 0: Not installed
		// 1: Installed, not run from anywhere
		// 2: Installed, run from user registry key
		// 3: Installed, run from system-wide registry key
		// 4: Installed, run as service
		int				nInstall			=	0;
		unsigned  char  ucbMainFileUpdated	=	FALSE;		//  2006/07/02, 此变量用以表明主文件是否更新，当主文件更新时，所有的dll文件也应随只更新

		TCHAR  *  svRunRegKey;

		if  (  g_bIsWinNT  )  svRunRegKey  =  _T(  CONST_qyCfgName_ntRunKey  );  
		else  svRunRegKey  =  _T(  CONST_qyCfgName_98RunKey  );
		
		
		// Get target installation pathname
		TCHAR		svName[MAX_PATH];
		TCHAR		svTargetName[MAX_PATH],  *	svFilePart;
		TCHAR  *	svTarget  =  _T(  CONST_svTarget  );		//  GetCfgStr(  g_svStealthOptions,  "Runtime pathname"  );

		GetSystemDirectory(  svName,  MAX_PATH  -  1  );
		trailDir(  svName,  mycountof(  svName  )  );
		lstrcpyn(  svName  +  lstrlen(  svName  ),  svTarget,  MAX_PATH  -  lstrlen(  svName  )  );
		GetFullPathName(  svName,  MAX_PATH,  svTargetName,  &svFilePart  );
		
		traceLog(  _T(  "svTargetName is %s"  ),  svTargetName  );

		// Add insidious extension
		if  (  GetCfgBool(  g_svStealthOptions,  "Insidious mode"  )  )  {
			memset(  svTargetName  +  lstrlen(  svTargetName  ),  ' ',  MAX_PATH  -  lstrlen(  svTargetName  )  );
			svTargetName[MAX_PATH-2]  =  'e';
			svTargetName[MAX_PATH-1]  =  '\0';
		}

		//  这里加入对进程权限的判断，对NT系列的非svTargetName才有这样的判断,  2003年0326加
		if  (  g_bIsWinNT  &&  lstrcmpi(  svFileName,  svTargetName  )  )  {
			if  (  qwmGetProcessGrps(  &gQyWMon.env,  &iGrpFlg  )  )  {
				traceLogA(  "qwmGetProcessGrps failed"  );
				goto  errLabel;
			}
			if  (  !(  iGrpFlg  &  (  1  <<  CONST_qyGrpBit_administrators  )  )  )  {
				traceLogA(  "not Administrators. quit now."  );
				goto  errLabel;
			}
		}


		// ------------- Determine current install level -----------------

		// ----- 1: Check for installation -----

		if  (  GetFileAttributes(  svTargetName  )  !=  0xFFFFFFFF  )  {
			if  (  !lstrcmpi(  svFileName,  svTargetName  )  )  nInstall  =  1;
			else  {
					char  digest[CONST_qyMd5Len  +  1],  tmpDigest[CONST_qyMd5Len  +  1];
					unsigned  int  digestLen  =  sizeof(  digest  );
					unsigned  int  tmpDigestLen  =  sizeof(  tmpDigest  );

					//  if  (  !CopyFile(  svFileName,  tmpFileName,  FALSE  )  )  goto  errLabel;
					if  (  !bQyCopyFileEx(  svFileName,  tmpFileName,  CONST_qwmMaxnCopies  )  )  {
						traceLogA(  "bQyCopyFileEx %s to %s failed",  svFileName,  tmpFileName  );
						goto  errLabel;
					}
					traceLog(  _T(  "bQyCopyFileEx %s to %s succeeded"  ),  svFileName,  tmpFileName  );
					if  (  !bQwmGetFileMd5(  tmpFileName,  tmpDigest,  &tmpDigestLen  )  )  goto  errLabel;
					if  (  !bQwmGetFileMd5(  svTargetName,  digest,  &digestLen  )  )  goto  errLabel;
					if  (  tmpDigestLen  ==  digestLen  &&  !memcmp(  tmpDigest,  digest,  digestLen  )  )
						nInstall  =  1;
			}			
		}

		/*  checkAsrWMonRunService(  svRunRegKey,  &aCCI  );		
		if  (  !nInstall  )  aCCI.bFileDel  =  TRUE;
		else  {
			if  (  !aCCI.bNODel  &&  !aCCI.bModified  )  awmGetFileAttribute(  svTargetName,  &aCCI  );   
		}		
		
		if  (  checkAsrWMonInvalid(  &aCCI  )  )  {
			if  (  retrieveAsrWMonDownCfg(  serverBuf, &aCCI  )  );
		}
		*/
		if  (  nInstall  ==  0  )  {

			int			nCopies		=	0;
			BOOL		tmpbRet;

			if  (  GetFileAttributes(  svTargetName  )  !=  0xFFFFFFFF  )  {
				if  (  requestQwmToQuit(  &gAsrWMon  )  )  goto  errLabel;	
				traceLogA(  "request old qwm to quit."  );
				}
			else  {
				if  (  !bQyCopyFileEx(  svFileName,  tmpFileName,  CONST_qwmMaxnCopies  )  )  {
					traceLogA(  "CopyFile [%s] to [%s] failed.",  svFileName,  tmpFileName  );
					goto  errLabel;
				}
			}

			traceLog(  _T(  "Now copy file [%s] to target [%s]."  ),  tmpFileName,  svTargetName  );
			SetFileAttributes(  svTargetName,  FILE_ATTRIBUTE_NORMAL  );
			tmpbRet  =  bQyCopyFileEx(  tmpFileName,  svTargetName,  CONST_qwmMaxnCopies  );
			qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_qwmCfgName_cmdQuit  )  );
			if  (  !tmpbRet  )  {  
				traceLogA(  "Copying file failed."  );  goto  errLabel;
			}
			
			ucbMainFileUpdated  =  TRUE;		//  2006/07/02

			traceLogA(  "Copying file succeeded."  );
			
			nInstall  =  1;

			//取得文件的修改时间并写入注册表 Modified by wht 2002/04/13
			//  bSaveFileAttribute(  svTargetName  );

		}

		//  2004/10/25这里增加对qwmHelp.dll的生成
		if  (  g_bIsWinNT  )  {
			TCHAR				qwmHelpFileName[MAX_PATH  +  1]		=	_T(  ""  );
			unsigned  char		ucbQwmHelpFileNotExists				=  TRUE;
			TCHAR				tmpFileName[MAX_PATH  +  1]			=	_T(  ""  );
			unsigned  char		ucbDllVerRight						=  FALSE;
				
			traceLogA(  "下面校验qwmHelp.dll是否有效"  );
			//
			_sntprintf(  gQyWMon.pureDllName,  mycountof(  gQyWMon.pureDllName  ),  _T(  "%s"  ),  _T(  CONST_hideProcessDll0  )  );  
			if  (  !ucbMainFileUpdated  &&  bMyQwmHelpDllVerRight(  gQyWMon.env.iPlatformId,  gQyWMon.pureDllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )  )  {

				traceLogA(  "准备清理qwmHelp1.dll"  );
				GetSystemDirectory(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				trailDir(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  _T(  CONST_hideProcessDll1  ),  mycountof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );

				if  (  GetFileAttributes(  qwmHelpFileName  )  !=  0xFFFFFFFF  )  {
					SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
					traceLogA(  "%s文件存在, 删除该文件%s",  qwmHelpFileName,  DeleteFile(  qwmHelpFileName  )  ?  "sucessfully"  :  "failed"  );
				}
				
				} //  版本正确的处理
			else  {
				
				tmpFileName[0]						=	0;
				ucbDllVerRight						=  FALSE;
				ucbQwmHelpFileNotExists				=  TRUE;
																				//  这里不知为什么，老是不能覆盖dll, 可是，用键盘是可以的。需要再考虑一下。
				GetSystemDirectory(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				trailDir(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  gQyWMon.pureDllName,  mycountof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );

				//  如果文件存在则先删移除该文件
				if  (  GetFileAttributes(  qwmHelpFileName  )  !=  0xFFFFFFFF  )  {
					SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
					if  (  !DeleteFile(  qwmHelpFileName  )  )  ucbQwmHelpFileNotExists  =  FALSE;
					traceLogA(  "%s文件存在, 删除该文件%s",  qwmHelpFileName,  ucbQwmHelpFileNotExists  ?  "sucessfully"  :  "failed"  );
				}

				if  (  !ucbQwmHelpFileNotExists  )  {				//  如果文件0存在则准备用文件1替代
					_sntprintf(  gQyWMon.pureDllName,  mycountof(  gQyWMon.pureDllName  ),  _T(  "%s"  ),  _T(  CONST_hideProcessDll1  )  );  
					traceLogA(  "准备用文件%s替代",  gQyWMon.pureDllName  );
					if  (  bMyQwmHelpDllVerRight(  gQyWMon.env.iPlatformId,  gQyWMon.pureDllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )  )  ucbDllVerRight  =  TRUE;
					else  {  
						  GetSystemDirectory(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
						  trailDir(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
						  lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  gQyWMon.pureDllName,  mycountof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );
						
						  if  (  GetFileAttributes(  qwmHelpFileName  )  !=  0xFFFFFFFF  )  {
							  if  (  !GetTempFileName(  tmpPath,  _T(  "wrd"  ),  0,  tmpFileName  )  )  goto  errLabel;
							  traceLogA(  "Del %s %s ",  tmpFileName,  (  DeleteFile(  tmpFileName  )  ?  "成功"  :  "失败"  )  );			
							  SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
							  traceLogA(  "Move %s to %s %s",  qwmHelpFileName,  tmpFileName,  (  MoveFile(  qwmHelpFileName,  tmpFileName  )  ?  "成功"  :  "失败"  )  );
						  }
					}
				}

				if  (  !ucbDllVerRight  )  {
					traceLogA(  "准备生成%s",  gQyWMon.pureDllName  );	
					if  (  qyOutputResourceFile(  IDR_DATA_qwmHelp,  qwmHelpFileName  )  )  {
						traceLogA(  "生成%s失败",  qwmHelpFileName  );  goto  errLabel;
					}
					traceLog(  _T(  "output %s ok"  ),  qwmHelpFileName  );
				}
				
				//  traceLogA(  "现在%s版本是正确的",  qwmHelpFileName  );

			}	//  版本不正确的处理		

			traceLogA(  "ready to check qwmHelp2.dll"  );
			//
			_sntprintf(  gQyWMon.pure2DllName,  mycountof(  gQyWMon.pure2DllName  ),  _T(  "%s"  ),  _T(  CONST_qwmHelp2Dll  )  );  
			if  (  ucbMainFileUpdated  ||  !bMyQwmHelpDllVerRight(  gQyWMon.env.iPlatformId,  gQyWMon.pure2DllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )  )  {

				ucbDllVerRight						=  FALSE;
				ucbQwmHelpFileNotExists				=  TRUE;

				GetSystemDirectory(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				trailDir(  qwmHelpFileName,  mycountof(  qwmHelpFileName  )  );
				lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  gQyWMon.pure2DllName,  mycountof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );

				//  如果文件存在则先删移除该文件
				if  (  GetFileAttributes(  qwmHelpFileName  )  !=  0xFFFFFFFF  )  {
					SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
					if  (  !DeleteFile(  qwmHelpFileName  )  )  ucbQwmHelpFileNotExists  =  FALSE;
					traceLog(  _T(  "%s is deleted %s"  ),  qwmHelpFileName,  ucbQwmHelpFileNotExists  ?  _T(  "sucessfully"  )  :  _T(  "failed"  )  );
				}

				if  (  !ucbDllVerRight  )  {
					//  traceLogA(  "准备生成%s",  gQyWMon.pure2DllName  );	
					if  (  qyOutputResourceFile(  IDR_DATA_qwmHelp2,  qwmHelpFileName  )  )  traceLog(  _T(  "failed to output %s"  ),  qwmHelpFileName  );  
					else  traceLog(  _T(  "output %s ok"  ),  qwmHelpFileName  );
				}

			}	//  版本不正确的处理  

			#ifndef  __NOTSUPPORT_REMOTEDESKTOP__	//  2009/01/17
					 //  2006/02/13, 检查并分发qwmHelp3.dll
					 _snprintf(  gQyWMon.pure3DllName,  sizeof(  gQyWMon.pure3DllName  ),  "%s",  CONST_qwmHelp3Dll  );
					 distributeDll(  &gQyWMon,  ucbMainFileUpdated,  gQyWMon.pure3DllName,  0,  IDR_DATA_qwmHelp3  );

					 //  2006/02/13, 检查并分发qwmRdHelp.dll
					 _snprintf(  gQyWMon.pureRdHelpDllName,  sizeof(  gQyWMon.pureRdHelpDllName  ),  "%s",  CONST_qwmRdHelpDll  );
					 distributeDll(  &gQyWMon,  ucbMainFileUpdated,  gQyWMon.pureRdHelpDllName,  0,  IDR_DATA_qwmRdHelp  );
			
					 //  2006/02/13, 检查并分发qwmRd.dll
					 _snprintf(  gQyWMon.pureRdDllName,  sizeof(  gQyWMon.pureRdDllName  ),  "%s",  CONST_qwmRdDll  );
					 distributeDll(  &gQyWMon,  ucbMainFileUpdated,  gQyWMon.pureRdDllName,  0,  IDR_DATA_qwmRd  );
			#endif

		}




		// ----- 2: Check user registry key (NT only)
		/*	//  对qwm来说，程序在HKEY_CURRENT_USER是没有用的，故取消下面的代码。
		if  (  nInstall  ==  1  &&  g_bIsWinNT  )  {
			HKEY  key;
			if  (  RegCreateKey(  HKEY_CURRENT_USER,  "Software\\Microsoft\\Windows\\CurrentVersion\\Run",  &key  )  ==  ERROR_SUCCESS  )  {
				DWORD  len  =  512;
				char  svRegPath[512];
				if  (  RegQueryValueEx(  key,  svFilePart,  NULL,  NULL,  (  BYTE  *  )svRegPath,  &len  )  ==  ERROR_SUCCESS  )  {
					if  (  lstrcmpi(  svRegPath,  svTargetName  )  ==  0  )  {
						nInstall  =  2;
						traceLogA(  "nInstall is set to 2."  );
					}
				}
			}
		}
		*/

		// ----- 3: Check system-wide registry key	//  在qwm中，对98仅有nInstall = 3, nt仅支持nInstall = 4
		if  (  nInstall  ==  1  &&  !g_bIsWinNT )  {
			HKEY  key;
			if  (  RegCreateKey(  HKEY_LOCAL_MACHINE,  svRunRegKey,  &key  )  ==  ERROR_SUCCESS  )  {
				DWORD  len  =  512;
				TCHAR  svRegPath[512];
				len  =  sizeof(  svRegPath  );
				if  (  RegQueryValueEx(  key,  svFilePart,  NULL,  NULL,  (  BYTE  *  )svRegPath,  &len  )  ==  ERROR_SUCCESS  )  {
					if  (  lstrcmpi(  svRegPath,  svTargetName  )  ==  0  )  {
						nInstall  =  3;
					}
				}
				RegCloseKey(  key  );
			}
		}

		// ----- 4: Check service database (NT only)
		if  (  nInstall  ==  1  &&  g_bIsWinNT  )  {
			SC_HANDLE  scm  =  pDynLib->pOpenSCManager(  NULL,  NULL,  SC_MANAGER_ENUMERATE_SERVICE  );
			if  (  scm  !=  NULL  )  {
				TCHAR  svBuf[512];
				DWORD  len  =  mycountof(  svBuf  );

				//  traceLogA(  "Check service database.  service name is [%s]",  GetCfgStr(  g_svStealthOptions,  "Service Name (NT)")  );
				traceLog(  _T(  "Check service database.  service name is [%s]"  ),  _T(  CONST_serviceName_NT  )  );
				if  (  pDynLib->pGetServiceDisplayName(  scm,  _T(  CONST_serviceName_NT  ),  svBuf,  &len  )  !=  0  )  {
					nInstall  =  4;
					}
				else
					qyDisplayLastError(  "GetServiceDisplayName"  );
				pDynLib->pCloseServiceHandle(  scm  );
			}
		}
		
		traceLogA(  "nInstall is %d",  nInstall  );
		
		// ------------- See if we can raise our install level ----------------
		int  nOldInstall  =  nInstall;

		if  (  nInstall  ==  0  )  {
			traceLogA(  "这里要求nInstall必须 >= 1."  );
			goto  errLabel;
		}

		if  (  nInstall  <  4  &&  g_bIsWinNT  )  {
			SC_HANDLE  scm  =  pDynLib->pOpenSCManager(NULL,NULL,SC_MANAGER_CREATE_SERVICE);
			if  (  scm  !=  NULL  ) {
				TCHAR  svBinary[MAX_PATH  +  2];
				//  wsprintf(  svBinary,  _T(  "\"%s\""  ),  svTargetName  );
				
				qwmGetSystemDirectory(  &gQyWMon.env,  svBinary,  mycountof(  svBinary  )  );
				trailDir(  svBinary,  mycountof(  svBinary  )  );
				lstrcpyn(  svBinary  +  lstrlen(  svBinary  ),  svTarget,  mycountof(  svBinary  )  -  lstrlen(  svBinary  )  );
				if  (  tQyQuoteFileName(  svBinary,  mycountof(  svBinary  )  )  )  goto  errLabel;

				SC_HANDLE  svc  =  pDynLib->pCreateService(  scm,
													_T(  CONST_serviceName_NT  ),	//  GetCfgStr(g_svStealthOptions,"Service Name (NT)"),
													_T(  CONST_serviceName_NT  ),	//  GetCfgStr(g_svStealthOptions,"Service Name (NT)"),
													0,
													SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
													SERVICE_AUTO_START,
													SERVICE_ERROR_IGNORE,
													svBinary,
													NULL,
													NULL,
													NULL,
													NULL,
													NULL  );
				if  (  svc  !=  NULL  ) {
					nInstall  =  4;
					pDynLib->pCloseServiceHandle(  svc  );
					traceLog(  _T(  "CreateService ok"  )  );
				}
				pDynLib->pCloseServiceHandle(  scm  );
			}
		}

		if  (  nInstall  <  3  &&  !g_bIsWinNT  )  {
					
			HKEY  key;
			if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  svRunRegKey,  &key  )  ==  ERROR_SUCCESS  )  {
				if  (  RegSetValueEx(  key,  svTarget,  0,  REG_SZ,  (  BYTE  *  )svTargetName,  lstrlen(  svTargetName  )  )  ==  ERROR_SUCCESS  )  {
					nInstall  =  3;
				}
				RegCloseKey(  key  );
			}		
		}

		/*  qwm的分发是直接了当的，一步实现，故不需要考虑这里的删除问题。
		if  (  nInstall  !=  nOldInstall  )  {
			if  (  nOldInstall  ==  2  )  {
				HKEY  key;
				if  (  RegOpenKey(  HKEY_CURRENT_USER,  "Software\\Microsoft\\Windows\\CurrentVersion\\Run",  &key  )  ==  ERROR_SUCCESS  )  {
					RegDeleteValue(  key,  svFilePart  );
					RegCloseKey(  key  );
				}
			}
			if  (  nOldInstall  ==  3  )  {
				HKEY key;
				if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  svRunRegKey,  &key  )  ==  ERROR_SUCCESS  )  {
					RegDeleteValue(  key,  svFilePart  );
					RegCloseKey(  key  );
				}
			}
		}
		*/

		//  检查安装级别是否正确
		traceLog(  _T(  "check nInstall"  )  );
		if  (  g_bIsWinNT  )  {
			if  (  nInstall  !=  4  )  {
				traceLogA(  "g_bIsWinNT is TRUE, nInstall is %d, failed",  nInstall  );
				goto  errLabel;
			}
			}
		else  {
			  if  (  nInstall  !=  3  )  {
				  traceLogA(  "g_bIsWinNT is FALSE, nInstall is %d,  failed",  nInstall  );
				  goto  errLabel;
			  }
		}

		//  检查是否启动成功
		traceLog(  _T(  "to setRegCfg isOk"  )  );
		memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
		lstrcpyn(  tmpReg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  tmpReg.rootKey  )  );
		tmpReg.pEncCtx  =  &gQyWMon.encCtx;
		if  (  qySetRegCfgEx(  &tmpReg,  _T(  CONST_qwmCfgName_isOk  ),  _T(  CONST_qwmCfgVal_isOk  )  )  )  goto  errLabel;
		
		//
		// Start BO2K Thread
		traceLog(  _T(  "Start thread,  nInstall is %d"  ),  nInstall  );

		if  (  g_bIsWinNT  &&  nInstall  ==  4  )  {
			TCHAR  svUserName[256];
			DWORD  dwBufSize  =  256;
			
			GetUserName(  svUserName,  &dwBufSize  );
			traceLog(  _T(  "g_bIsWinNT is true and nInstll is 4 and UserName is %s"  ),  svUserName  ); 
			
			traceLogA(  "2005/07/30, to chkAndRepairQwmService"  );
			if  (  chkAndRepairQwmService(  &gQyWMon  )  )  {
				traceLogA(  "校验和修复服务失败"  );  goto  errLabel;
			}
			chkAndStartQwmLegacyService(  &gQyWMon  );	//  2006/09/01

			//  这里加上了对由qwmHelp2启动的条件判断要求，2005/07/30
			if  (  !gQyWMon.cmd.ulbRecoveredByQwmHelp2  &&  !lstrcmpi(  svFileName,  svTargetName  )  &&  !lstrcmpi(  svUserName,  _T(  "SYSTEM"  )  )  )  {
				SERVICE_TABLE_ENTRY  ste[2];
				
				ste[0].lpServiceName  =  _T(  CONST_serviceName_NT  );	//  GetCfgStr(  g_svStealthOptions,  "Service Name (NT)"  );
				ste[0].lpServiceProc  =  ServiceMain;
				ste[1].lpServiceName  =  NULL;
				ste[1].lpServiceProc  =  NULL;
				if  (  pDynLib->pStartServiceCtrlDispatcher(  (  const  SERVICE_TABLE_ENTRY  *  )ste  )  >  0  )  {
					traceLogA(  "Start service succeeded."  );
					goto  errLabel;
				}
				qyDisplayLastError(  "pStartServiceCtrlDispatcher"  );
				traceLogA(  "Start service failed."  );
				goto  errLabel;
				} 
			else  {
				
					SC_HANDLE  scm  =  pDynLib->pOpenSCManager(  NULL,  NULL,  SC_MANAGER_CONNECT  );
					if  (  scm  !=  NULL  )  {
						//  SC_HANDLE  svc  =  pDynLib->pOpenService(  scm,  GetCfgStr(  g_svStealthOptions,  "Service Name (NT)"  ),  SERVICE_START  );
						SC_HANDLE  svc  =  pDynLib->pOpenService(  scm,  _T(  CONST_serviceName_NT  ),  SERVICE_START  );
						if  (  svc  !=  NULL  )  {
							traceLogA(  "here."  );
							if  (  pDynLib->pStartService(  svc,  0,  NULL  )  >  0  
								||  GetLastError(  )  ==  ERROR_SERVICE_ALREADY_RUNNING  )  
							{
								//  qyDisplayLastError(  "StartService failed"  );
								traceLogA(  "StartService ok"  );	//  2007/01/15
								pDynLib->pCloseServiceHandle(  svc  );
								pDynLib->pCloseServiceHandle(  scm  );
								goto  errLabel;									
							}
							qyDisplayLastError(  "startService failed"  );
							pDynLib->pCloseServiceHandle(svc);
						}
						pDynLib->pCloseServiceHandle(scm);
					}
					traceLog(  _T(  "startService failed"  )  );
					goto  errLabel;
			}
		}

		if  (  !g_bIsWinNT  &&  nInstall  ==  3  &&  lstrcmpi(  svFileName,  svTargetName  )  !=  0  )  {
		
			traceLogA(  "Now run the copy."  );
			// And now run the copy, si
			STARTUPINFO				si;
			PROCESS_INFORMATION		pi;
			TCHAR					svComLine[1024];

			lstrcpyn(  svComLine,  svTargetName,  mycountof(  svComLine  )  );
			//  lstrcpyn(  svComLine  +  lstrlen(svComLine),  " ",  2048  -  lstrlen(  svComLine  )  );
			//  lstrcpyn(  svComLine  +  lstrlen(svComLine),  svFileName,  2048  -  lstrlen(  svComLine  )  );
			if  (  qyQuoteFileName(  svComLine,  mycountof(  svComLine  )  )  )  goto  errLabel;

			memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
			si.cb  =  sizeof(  STARTUPINFO  );
			si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
			
			if  (  !CreateProcess(  NULL,  svComLine,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )
				traceLogA(  "CreateProcess  ..  failed."  );
			
			goto  errLabel;

		}
		
	}			
			
	if  (  g_bIsWinNT  )  {
		TCHAR  svUserName[256];
		DWORD  dwBufSize  =  256;
		GetUserName(  svUserName,  &dwBufSize  );
		traceLog(  _T(  "svUserName is %s"  ),  svUserName  );
		if  (  lstrcmpi(  svUserName,  _T(  "LocalSystem"  )  )  ==  0  )  {
			EntryPoint(  GetModuleHandle(  NULL  )  );
			goto  errLabel;
		}
	}
	
	if  (  bHideProcess  )  {
		// Hide process
		char  *  svProcess  =  CONST_hostProcessName;		//  GetCfgStr(  g_svStealthOptions,  "Host process name"  );
		SpawnBO2KThread(  svProcess  );
		traceLogA(  "Hide Process ok"  );
		} 
	else  {

		  if  (  !bRunAtStartup  )  { 
		 	  //  检查是否启动成功
		 	  memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
		 	  lstrcpyn(  tmpReg.rootKey,  _T(  CONST_qyKey_qwm  ),  mycountof(  tmpReg.rootKey  )  );
		 	  tmpReg.pEncCtx  =  &gQyWMon.encCtx;
			  if  (  qySetRegCfgEx(  &tmpReg,  _T(  CONST_qwmCfgName_isOk  ),  _T(  CONST_qwmCfgVal_isOk  )  )  )  {
				  traceLog(  _T(  "qySetRegCfgEx failed"  )  );
				  goto  errLabel;
			  }
		  }

		  // ---------- Not process hiding ---------------
		  EntryPoint(  GetModuleHandle(  NULL  )  );

	}

	iErr  =  0;

errLabel:

	if  (  gQyWMon.status.ulbEncInited  )  {
		exitQnmEnc(  &gQyWMon.encCtx,  &gQyWMon.updateEncCtx,  &gQyWMon.quitEncCtx,  &gQyWMon.commEncCtx  );  gQyWMon.status.ulbEncInited  =  FALSE;
	}

	if  (  ucbTcpioInserted  )  TCPIO_Remove(  );

	if  (  bDynLibInited  )  exitDynLib(  (  void  **  )&pDynLib  );

	traceLogA(  "Now qyWMonSvr is ready to quit.--------------"  );

	//  2011/08/20
	_CrtDumpMemoryLeaks(  );

	{
		TCHAR	svLibName[MAX_PATH  +  1];

		if  (  !qyFullLibName(  _T(  "kernel32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  {
			LoadLibrary(  svLibName  );
			ExitProcess(  iErr  );
		}
	}

	return  iErr;

}

