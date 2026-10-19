
#include	"stdafx.h"
#include	"qmdCommon.h"
 

#define		CONST_qyAppName_qnmHttpSvr		_T(  "qnmHttpSvr.exe"  )

 
 int qyMcDaemonMain(  )
{
	 int			iErr							=	-1;
	 CQyMcDaemon	mcDaemon;
	 BOOL			bInited							=	FALSE;
	 TCHAR		*	pCmdLine;
	 TCHAR			moduleFileName[MAX_PATH  +  1];
	 TCHAR			pathBuf[MAX_PATH  +  1];
	 TCHAR		*	filePart						=	NULL;
	 void		*	pDynLib							=	NULL;
	 BOOL			bDynLibInited					=	FALSE;
	 BOOL			bShowInfoInited					=	FALSE;
	 TCHAR		*	pT;
	 int			iServiceId						=	CONST_qyServiceId_netMc;
	 CString		errHintWndCls;

	 setDebugLogFileModuleName(  );

	 if  (  initDynLib(  &pDynLib  )  )  goto  errLabel;
	 bDynLibInited  =  TRUE;

	 if  (  getQyEnv(  pDynLib,  &mcDaemon.var.env  )  )  goto  errLabel;
	 //  mcDaemon.var.env.pDynLibs  =  pDynLib;

	 errHintWndCls  =  CONST_qnmStatusToolWndClass;
	 if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_qmd"  ),  errHintWndCls,  TRUE  )  )  goto  errLabel;
	 bShowInfoInited  =  TRUE;

	 traceLogA(  ""  );
	 traceLogA(  "Daemon starts..."  );

	 GetModuleFileName(  NULL,  moduleFileName,  sizeof(  moduleFileName  )  /  sizeof(  moduleFileName[0]  )  );
	 GetFullPathName(  moduleFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  );
	 pCmdLine  =  GetCommandLine(  );

	 //  这里要分析一下参数，2007/06/13
	 if  (  (  pT  =  _tcschr(  pCmdLine,  _T(  '-'  )  )  )  )  {
		 pT  ++  ;
		 switch  (  *pT  )  {
				 case  _T(  's'  ):
				 case  _T(  'S'  ):
					   pT  ++  ;
					   if  (  !_tcsnicmp(  pT,  _T(  "mis"  ),  _tcslen(  _T(  "mis"  )  )  )  )  {
						   iServiceId  =  CONST_qyServiceId_mis;
						   break;
					   }
					   break;
				 default:
						break;
		 }
	 }

	 mcDaemon.var.iServiceId  =  iServiceId;	//  2003/06/13, 通过命令行区分了serviceId
	 //
	 //  mcDaemon.var.iSystemId  =  qyGetSystemId(  );				//  2003/11/30取消了daemon的systemId, 因为daemon作为载体，不能限于某一个system
	 if  (  iServiceId  ==  CONST_qyServiceId_mis  )  mcDaemon.var.iAppType  =  CONST_qyAppType_null;
	 else  mcDaemon.var.iAppType  =  qyGetAppType(  mcDaemon.var.iSystemId,  _T(  CONST_qyRootKey_mcGui_netMc  )  );
	 mcDaemon.var.iCustomId  =  qyGetCustomId(  );
	 //  2004/05/25在这里不再判断appType,
	 mcDaemon.var.iAppId  =  CONST_qyAppId_mcDaemon;

	 switch  (  mcDaemon.var.iServiceId  )  {
			 case  CONST_qyServiceId_netMc:
				   if  (  mcDaemon.preInit(  &mcDaemon.var.env,  CONST_qyRootKey_qmd_netMc,  5000,  "Daemon for NetMc"  )  )  goto  errLabel;
				   break;
			 case  CONST_qyServiceId_mis:
				   if  (  mcDaemon.preInit(  &mcDaemon.var.env,  CONST_qyRootKey_qmd_mis,  5000,  "Daemon for Mis"  )  )  goto  errLabel;
				   break;
			 default:
					goto  errLabel;
	 }

	 mcDaemon.var.status.ulRandOfStartup  =  time(  NULL  );

	 if  (  mcDaemon.runAsApp(  )  )  goto  errLabel;

	 iErr   =  0;

errLabel:

	 if  (  bShowInfoInited  )  exitShowInfo(  0  );

	 if  (  bDynLibInited  )  exitDynLib(  &pDynLib  );

	 traceLogA(  "Daemon ends."  );

	 return  iErr;

}


