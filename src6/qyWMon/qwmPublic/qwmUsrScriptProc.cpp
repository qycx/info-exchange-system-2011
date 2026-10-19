
#include	<windows.h>
#include	<stdlib.h>
//
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
#include	"qwmHideProcessCommProc.h"

#include	<tchar.h>

#include	"qySyncCommProc.h"
#include	"qwmFunc.h"
#include	"qyTCharCommProc.h"


 BOOL  bSetPermitted(  )
{
	BOOL	bRet	=	FALSE;
	TCHAR			dirName[512]		=	_T(  ""  );
	TCHAR			finalName[512]		=	_T(  ""  );
	TCHAR			systemDir[512]		=	_T(  ""  );
	TCHAR		*	pDebugDir			=	_T(  "d:\\qycx4\\Develop6\\debug\\bin"  );

	if  (  getModuleDirAndFinalName(  dirName,  mycountof(  dirName  ),  finalName,  mycountof(  finalName  )  )  )  goto  errLabel;
	
	traceLog(  _T(  "bSetPermitted: dirName is %s, finalName is %s"  ),  dirName,  finalName  );

	GetSystemDirectory(  systemDir,  mycountof(  systemDir  )  );
	if  (  _tcsnicmp(  dirName,  systemDir,  lstrlen(  systemDir  )  )
		#ifdef  __DEBUG__
				&&  _tcsnicmp(  dirName,  pDebugDir,  lstrlen(  pDebugDir  )  )
		#endif
			)		
	{
		traceLogA(  "bSetPermitted false, not correct directory"  );
		goto  errLabel;
	}

	if  (  lstrcmpi(  finalName,  _T(  "qwmsvr.exe"  )  )  
		#ifdef  __DEBUG__
				&&  lstrcmpi(  finalName,  _T(  "qyWMonSvr2k.exe"  )  )   
		#endif
			) 
	{
		traceLogA(  "bSetPermitted false: not correct finalName"  );
		goto  errLabel;
	}

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 extern  "C"  __declspec( dllexport )  int  setQwmUsrScriptQuit(  BOOL  bQuit  )
{
	int				iErr				=	-1;
	TCHAR			buf[128]			=	_T(  ""  );

	if  (  !bSetPermitted(  )  )  goto  errLabel;

	if  (  bQuit  )  qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_cmdQuit_usrScript  ),  _T(  "1"  )  );
	else  if  (  !qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_cmdQuit_usrScript ),  (  char  *  )buf,  sizeof(  buf  )  )
				&&  _ttol(  buf  )  )  
	{
			  qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_cmdQuit_usrScript  ),  _T(  ""  )  );
			  //  qyDelRegCfg(  CONST_qyKey_qwm,  CONST_regValName_cmdQuit_usrScript  );
	}

	traceLogA(  "setQwmQuit:  bQuit_usrScript is %s",  bQuit  ?  "TRUE"  :  "FALSE"  );
	
	iErr  =  0;
errLabel:
	 return  iErr;
}

 extern  "C"  __declspec( dllexport )  BOOL  bQwmUsrScriptQuit(  )
{
	 TCHAR				buf[128]				=	_T(  ""  );
	 unsigned  char		ucbStopMon_usrScript	=	FALSE;
	
	 if  (  !qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_cmdQuit_usrScript  ),  (  char  *  )buf,  sizeof(  buf  )  )  
		 &&  _ttol(  buf  )  )
	 {	
		 ucbStopMon_usrScript  =  TRUE;
	 }
	
	 return  ucbStopMon_usrScript;
}


