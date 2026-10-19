
#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<tchar.h>
#include	<iphlpapi.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	"qyRegToolProc.h"
#include	<tchar.h>
#include	"qySyncCommProc.h"

int  proc98DevRule(  QWM_THREADINFO  *  pSubThreadInfo  );
int  procNtDevRule(  QWM_THREADINFO  *  pSubThreadInfo  );


 int  procDevRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;

	 if  (  GetTickCount(  )  -  pQwm->dwProcDevRuleLastTickCnt  <  CONST_minProcDevRuleInterval  )  {
		 //  traceLogA(  "procDevRule时间未到"  );
		 iErr  =  0;  goto  errLabel;
	 }
	 pQwm->dwProcDevRuleLastTickCnt  =  GetTickCount(  );

	 traceLogA(  "procDevRule: 管理外设"  );

 	 if  (  !g_bIsWinNT  )  proc98DevRule(  pSubThreadInfo  );
	 else  procNtDevRule(  pSubThreadInfo  );


	 iErr  =  0;
errLabel:

	 return  iErr;

}

#define		CONST_qyRootKey_safeBoot	"SYSTEM\\CurrentControlSet\\Control\\SafeBoot"	
#define		CONST_subKey_minimal		"Minimal"
#define		CONST_subKey_network		"Network"
#define		CONST_subKey_myMinimal		"Minimal-"
#define		CONST_subKey_myNetwork		"Network-"

 BOOL  isSafeBootSubKey(  TCHAR  *  subKey,  BOOL  *  pbNetwork  )
{
	 BOOL	bRet		=	FALSE;
	 HKEY	hKey		=	NULL;
	 BOOL	bKeyOpen	=	FALSE;
	 TCHAR	buf[256]	=	_T(  ""  );
	 BOOL	bNetwork	=	FALSE;
	 
	 if  (  !subKey  )  return  FALSE;

	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_safeBoot  ),  subKey  );
	 if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  buf,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 
	 //  校验另一项
	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s\\%s\\File system"  ),  _T(  CONST_qyRootKey_safeBoot  ),  subKey  );
	 if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  buf,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;

	 //  再校验一项
	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s\\%s\\Network"  ),  _T(  CONST_qyRootKey_safeBoot  ),  subKey  );
	 if  (  RegOpenKey(  HKEY_LOCAL_MACHINE,  buf,  &hKey  )  ==  ERROR_SUCCESS  )  {
		 bNetwork  =  TRUE;
		 bKeyOpen  =  TRUE;
		 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 }

	 bRet  =  TRUE;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bRet  )  {
		 if  (  pbNetwork  )  *pbNetwork  =  bNetwork;
	 }

	 return  bRet;
}

 int  procSafeMode(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 BOOL					bNetwork		=	FALSE;
	 TCHAR					buf_minimal[256],	buf_network[256];
	 TCHAR					myBuf_minimal[256],	myBuf_network[256];
	 BOOL					bOk;
	 QWM_DYN_LIB	*		pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 if  (  GetTickCount(  )  -  pQwm->dwProcSafeModeLastTickCnt  <  CONST_minProcSafeModeInterval  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 pQwm->dwProcSafeModeLastTickCnt  =  GetTickCount(  );

	 traceLogA(  "procSafeMode: 管理安全模式"  );

	 //  if  (  !g_bIsWinNT  ||  pQwm->env.iPlatformId  ==  CONST_qyPlatform_nt  )  {
	 //  	 iErr  =  0;  goto  errLabel;
	 //  }

	 switch  (  pQwm->env.iPlatformId  )  {		//  2007/02/12
	 		 //  case  CONST_qyPlatform_win2k:
	 		 case  CONST_qyPlatform_winxp:
	 		 //  case  CONST_qyPlatform_win2003:
				   break;
			 default:
					iErr  =  0;  goto  errLabel;					
	 }

	 if  (  !bShlwApiOk(  (  QWM_DYN_LIB  *  )pQwm->env.pDynLibs  )  )  goto  errLabel;

	 _sntprintf(  myBuf_minimal,  mycountof(  myBuf_minimal  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_safeBoot  ),  _T(  CONST_subKey_myMinimal  )  );
	 _sntprintf(  buf_minimal,  mycountof(  buf_minimal  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_safeBoot  ),  _T(  CONST_subKey_minimal  )  );
	 _sntprintf(  myBuf_network,  mycountof(  myBuf_network  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_safeBoot  ),  _T(  CONST_subKey_myNetwork  )  );
	 _sntprintf(  buf_network,  mycountof(  buf_network  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_safeBoot  ),  _T(  CONST_subKey_network  )  );

	 if  (  pQwm->cfg.pcRules.os.ucSafeModeCmd  ==  CONST_devCmd_permitted  )  {
		 if  (  (  isSafeBootSubKey(  _T(  CONST_subKey_minimal  ),  &bNetwork  )  &&  !bNetwork  )
			 &&  (  isSafeBootSubKey(  _T(  CONST_subKey_network  ),  &bNetwork  )  &&  bNetwork  )  )
		 {
			 //  安全模式是好的
			 iErr  =  0;  goto  errLabel;
		 }
		 if  (  (  isSafeBootSubKey(  _T(  CONST_subKey_myMinimal  ),  &bNetwork  )  &&  !bNetwork  )
			 &&  (  isSafeBootSubKey(  _T(  CONST_subKey_myNetwork  ),  &bNetwork  )  &&  bNetwork  )  )
		 {
			 traceLogA(  "to recover safeMode"  );

			 bOk  =  FALSE;
			 if  (  !bakRegKey(  &pQwm->env,  HKEY_LOCAL_MACHINE,  myBuf_minimal,  buf_minimal  )  
				 &&  !bakRegKey(  &pQwm->env,  HKEY_LOCAL_MACHINE,  myBuf_network,  buf_network  )  
					&&  pDynLib->pSHDeleteKey(  HKEY_LOCAL_MACHINE,  myBuf_minimal  )  ==  ERROR_SUCCESS  
						&&  pDynLib->pSHDeleteKey(  HKEY_LOCAL_MACHINE,  myBuf_network  )  ==  ERROR_SUCCESS  )
			 {
				 bOk  =  TRUE;
			 }
			 qwmLogGeneralEvent(  pSubThreadInfo,  CONST_qyEventType_nm_safeModeOn,  NULL,  (  bOk  ?  ""  :  "Failed"  ),  "",  0  );
		 }
		 iErr  =  0;  goto  errLabel;
		}
	 else  if  (  pQwm->cfg.pcRules.os.ucSafeModeCmd  ==  CONST_devCmd_prohibited  )  {
		       if  (  (  isSafeBootSubKey(  _T(  CONST_subKey_minimal  ),  &bNetwork  )  &&  !bNetwork  )
				   &&  (  isSafeBootSubKey(  _T(  CONST_subKey_network  ),  &bNetwork  )  &&  bNetwork  )  )
			   {
				   traceLogA(  "to prohibit safeMode"  );

				   bOk  =  FALSE;
				   if  (  !bakRegKey(  &pQwm->env,  HKEY_LOCAL_MACHINE,  buf_minimal,  myBuf_minimal  )  
					   &&  !bakRegKey(  &pQwm->env,  HKEY_LOCAL_MACHINE,  buf_network,  myBuf_network  )  
						   &&  pDynLib->pSHDeleteKey(  HKEY_LOCAL_MACHINE,  buf_minimal  )  ==  ERROR_SUCCESS  
							   &&  pDynLib->pSHDeleteKey(  HKEY_LOCAL_MACHINE,  buf_network  )  ==  ERROR_SUCCESS  )
				   {
					   bOk  =  TRUE;
				   }
				   qwmLogGeneralEvent(  pSubThreadInfo,  CONST_qyEventType_nm_safeModeOff,  NULL,  (  bOk  ?  ""  :  "Failed"  ),  "",  0  );

			 	   iErr  =  0;  goto  errLabel;		 
					}
			   else  {
				     //  安全模式已被禁用
				     iErr  =  0;  goto  errLabel;
			   }
		 
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


#define		CONST_qyRootKey_policiesExplorer		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer"
	#define		CONST_regValName_NoDriveTypeAutoRun		"NoDriveTypeAutoRun"
#define		CONST_dwVal_NoDriveTypeAutoRun			0x000000ff
 //
 int  procAutorun(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 BOOL					bNetwork		=	FALSE;
	 QWM_DYN_LIB	*		pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 QY_REG					reg;
	 TCHAR			*		pCfg			=	NULL;
	 long					lData			=	0;
	 unsigned  int			len;
	 long					lBuf;

	 if  (  GetTickCount(  )  -  pQwm->dwProcAutorunLastTickCnt  <  CONST_minProcAutorunInterval  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 pQwm->dwProcAutorunLastTickCnt  =  GetTickCount(  );
		
	 switch  (  pQwm->env.iPlatformId  )  {		//  2007/02/12
			 case  CONST_qyPlatform_win98:		//  这里不知道98的支持不支持
			 case  CONST_qyPlatform_winme:
			 case  CONST_qyPlatform_nt:
				   iErr  =  0;  goto  errLabel;
			 default:
					break;
	 }

	 if  (  pQwm->cfg.pcRules.os.ucAutorunCmd  !=  CONST_devCmd_permitted  
		 &&  pQwm->cfg.pcRules.os.ucAutorunCmd  !=  CONST_devCmd_prohibited  )  
	 {		//  属未配置
		 iErr  =  0;  goto  errLabel;
	 }

	 traceLogA(  "procAutorun: 管理自动播放"  );

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 safeTcsnCpy(  _T(  CONST_qyRootKey_policiesExplorer  ),  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 
	 pCfg  =  _T(  CONST_regValName_NoDriveTypeAutoRun  ); 	
	 if  (  pQwm->cfg.pcRules.os.ucAutorunCmd  !=  CONST_devCmd_prohibited  )  {	//  允许的情况下
		 len  =  sizeof(  lBuf  );
		 if  (  !tmpGetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lBuf,  &len  )  )  {
			 traceLogA(  "%s的值改了",  pCfg  );	 
			 qyDelRegCfg(  reg.rootKey,  pCfg  );
		 }
		}
	 else  {	//  禁止自动播放的情况下
		   lData  =  CONST_dwVal_NoDriveTypeAutoRun;
		   len  =  sizeof(  lBuf  );
		   if  (  tmpGetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lBuf,  &len  )  ||  lBuf  !=  lData  )  {
			   traceLogA(  "%s的值改了",  pCfg  );	 
			   reg.uiType  =  REG_DWORD;  tmpSetRegCfgEx(  &reg,  pCfg,  (  char  *  )&lData,  sizeof(  lData  )  );
		   }
	 }

	 
	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  getsv101_type(  QY_ENV  *  pEnv,  DWORD  *  psv101_type  )
{
   int					iErr			=	-1;
   DWORD				dwLevel			=	101;
   LPSERVER_INFO_101	pBuf			=	NULL;
   NET_API_STATUS		nStatus;
   LPWSTR				pszServerName	=	NULL;
   QWM_DYN_LIB		*	pDynLib			=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
   BOOL					bBufNeedFree	=	FALSE;

   if  (  !pDynLib  ||  !pDynLib->pLMSNetServerGetInfo  ||  !pDynLib->pNetApiBufferFree  )  return  -1;

   // Call the NetServerGetInfo function, specifying level 101.
   nStatus  =  pDynLib->pLMSNetServerGetInfo(  pszServerName,  dwLevel,  (  LPBYTE  *  )&pBuf  );
   if  (  nStatus  !=  NERR_Success  )  goto  errLabel;
   bBufNeedFree  =  TRUE;
 
   /*
   if ((pBuf->sv101_type & SV_TYPE_DOMAIN_CTRL) ||
         (pBuf->sv101_type & SV_TYPE_DOMAIN_BAKCTRL) ||
         (pBuf->sv101_type & SV_TYPE_SERVER_NT))
         printf("This is a server\n");
      else
         printf("This is a workstation\n");
   */

   if  (  psv101_type  )  *psv101_type  =  pBuf->sv101_type;
   
   iErr  =  0;

errLabel:

   if  (  bBufNeedFree  )  if  (  pBuf  !=  NULL  )  pDynLib->pNetApiBufferFree(pBuf);

   return  iErr;

}

#define		MACRO_bServer(  sv101_type  )  (  (  sv101_type & SV_TYPE_DOMAIN_CTRL ) ||  (  sv101_type & SV_TYPE_DOMAIN_BAKCTRL) ||  (  sv101_type & SV_TYPE_SERVER_NT  )  )
 
 int  tmpHandler_procNetShare(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr			=	-1;
	 COMMON_PARAM			*	pCommonParam0	=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM			*	pCommonParam1	=	(  COMMON_PARAM  *  )p1;
	 PSHARE_INFO_502			p				=	(  PSHARE_INFO_502  )p2;
	 QWM_THREADINFO			*	pSubThreadInfo	=	(  QWM_THREADINFO  *  )pCommonParam0->p0;
	 DWORD						sv101_type		=	(  DWORD  )p1;
	 WCHAR					*	pWNetName		=	(  WCHAR  *  )pCommonParam1->p0;
	 WCHAR					*	pWPath			=	(  WCHAR  *  )pCommonParam1->p1;
	 unsigned  int				size			=	(  unsigned  int  )pCommonParam1->p2;

	 switch  (  p->shi502_type  )  {
			 case  STYPE_DISKTREE:
				   if  (  !wcsicmp(  (  WCHAR  *  )p->shi502_netname,  L"print$"  )  )  break;
				   if  (  !wcsicmp(  (  WCHAR  *  )p->shi502_netname,  L"fax$"  )  )  break;
				   if  (  MACRO_bServer(  sv101_type  )  )  {
					   if  (  !wcsicmp(  (  WCHAR  *  )p->shi502_netname,  L"netlogon"  )  )  break;
					   if  (  !wcsicmp(  (  WCHAR  *  )p->shi502_netname,  L"sysvol"  )  )  break;
				   }
				   //  运行到这里表明是一般的文件共享
				   safeWcsnCpy(  (  WCHAR  *  )p->shi502_netname,  pWNetName,  size  );
				   safeWcsnCpy(  (  WCHAR  *  )p->shi502_path,  pWPath,  size  );
				   iErr  =  1;  goto  errLabel;	//  表明找到了
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  procNetShare(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 BOOL					bNetwork		=	FALSE;
	 QWM_DYN_LIB	*		pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 CQySyncObj				syncObj;
	 WCHAR					wNetName[512]	=	L"";
	 WCHAR					wPath[mycountof(  wNetName  )]	=	L"";	//  wPath和wNetName的cnt应该一样
	 WCHAR					wBuf[256];
	 char					buf[256];
	 COMMON_PARAM			commonParam0,  commonParam1;
	 int					tmpiRet			=	-1;
	 int					i;
	 DWORD					sv101_type		=	0;


	 switch  (  pQwm->env.iPlatformId  )  {		//  2007/02/12
			 case  CONST_qyPlatform_win98:		//  这里不知道98的支持不支持
			 case  CONST_qyPlatform_winme:
			 case  CONST_qyPlatform_nt:
				   iErr  =  0;  goto  errLabel;
			 default:
					break;
	 }

	 if  (  pQwm->cfg.pcRules.os.ucNetShareCmd  !=  CONST_devCmd_prohibited  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  GetTickCount(  )  -  pQwm->dwProcNetShareLastTickCnt  <  CONST_minProcNetShareInterval  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //  先要同步一下，以防止和showNetShare(  )冲突
	 if  (  syncObj.sync(  pQwm->cfg.mutexName_syncNetShare,  pQwm->cfg.ulMilliSeconds_syncNetShare  )  )  goto  errLabel;

	 //  下面要处理了，
	 pQwm->dwProcNetShareLastTickCnt  =  GetTickCount(  );
	 
	 if  (  getsv101_type(  &pQwm->env,  &sv101_type  )  )  goto  errLabel;

	 traceLogA(  "procNetShare: 管理网络共享：未完成"  );
	 for  (  i  =  0;  i  <  10;  i  ++  )  {
		  wNetName[0]  =  0;
		  MACRO_makeCommonParam3(  pSubThreadInfo,  (  void  *  )sv101_type,  0,  commonParam0  );
		  MACRO_makeCommonParam3(  wNetName,  (  void  *  )wPath,  (  void  *  )min(  mycountof(  wNetName  ),  mycountof(  wPath  )  ),  commonParam1  );
		  tmpiRet  =  enumPcNetShares(  &pQwm->env,  tmpHandler_procNetShare,  &commonParam0,  &commonParam1  );
		  if  (  tmpiRet  <  0  )  goto  errLabel;
		  if  (  !tmpiRet  )  break;

		  //  这里表明找到了一个需要禁用的共享名
		  traceLogA(  "将禁用%S",  wNetName  );

		  NET_API_STATUS res;

		  res  =  pDynLib->pLMSNetShareDel(  0,  wNetName,  0  );
		  _snwprintf(  wBuf,  mycountof(  wBuf  ),  L"%s(%s)",  wNetName,  wPath  );
		  if  (  !myWChar2Utf8(  wBuf,  buf,  mycountof(  buf  )  )  )  buf[0]  =  0;
		  if  (  res  !=  NERR_Success  )  {
			  qwmLogGeneralEvent(  pSubThreadInfo,  CONST_qyEventType_nm_netShareMgr,  NULL,  buf,  "Deleting net share failed",  TRUE  );
			  goto  errLabel;	
		  }

		  qwmLogGeneralEvent(  pSubThreadInfo,  CONST_qyEventType_nm_netShareMgr,  NULL,  buf,  "Net share deleted",  TRUE  );
		  continue;		  
 	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  procOsRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 procSafeMode(  pSubThreadInfo  );
	 procAutorun(  pSubThreadInfo  );
	 procNetShare(  pSubThreadInfo  );

	 return  0;
}


