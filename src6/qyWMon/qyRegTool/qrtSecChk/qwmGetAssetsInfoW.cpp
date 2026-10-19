
#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//  #include	"resource.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"

#define		_UNICODE			//  这里显示的定义unicode, 因为这个项目是ansi的
#define		UNICODE

#include	<tchar.h>







 int	 myGetSoftwareInfoNt(  QY_ENV  *  pEnv,  LPCTSTR  pSoftwareInstalledKey,  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr										=	-1;
	 int						iRet										=  0;
	 WCHAR						softwareRegKey[255 + 1]						=  L"";
 	 WCHAR						tSubKey[MAX_PATH  +  1]						=  L"";   
	 //  WCHAR					*	pSoftwareInstalledKey						=  NULL;
	 HKEY						hKey										=  NULL;
	 WCHAR						displayNameValue[255]						=  L"";
	 DWORD						dwSystemComponentValue						=  0;
	 WCHAR						uninstallStringValue[255]					=  L"";
	 int						i  =  0, cnt  =  0;
	 BOOL						bKeyOpen									=	FALSE;
	 QWM_COMPONENT_INFO		*	pComponent									=	NULL;
	 char						buf[1024];
	 
	 
	 if  (  !pAssetsInfo  )  return  -1;

#if  0
	 switch  (  pAssetsInfo->iPlatformId  )  {
			  
			 case  CONST_qyPlatform_win98:
			 case  CONST_qyPlatform_nt:
			 case  CONST_qyPlatform_win2k:
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 default:  
				 pSoftwareInstalledKey  =  _T(  CONST_qyRootKey_softwareInstalled  );
					break;
	 }
#endif
 
	 //  if  (  (  iRet  =  myRegOpenKeyEx(  pEnv,  HKEY_LOCAL_MACHINE,  pSoftwareInstalledKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  (  TCHAR  *  )pSoftwareInstalledKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0;  ;  i++ )  {
		  //  iRet  =  myRegEnumKey(  pEnv,  hKey,  i,  tSubKey,  mycountof(  tSubKey  )  );
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  mycountof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _snwprintf(  softwareRegKey,  mycountof(  softwareRegKey  ),  L"%s\\%s",  pSoftwareInstalledKey,  tSubKey  );
		  
		  if  (  qyGetRegCfg(  softwareRegKey,  _T(  CONST_regValName_displayName  ),  (  char  *  )displayNameValue,  sizeof(  displayNameValue  )  )  
			  ||  qyGetRegCfg(  softwareRegKey,  _T(  CONST_regValName_uninstallString  ),  (  char  *  )uninstallStringValue,  sizeof(  uninstallStringValue  )  )  )  
		  {
			  traceLogA(  "myGetSoftware: get %d displayName failed",  i  );	  continue;
		  }
		  if  (  !qyGetRegCfg(  softwareRegKey,  _T(  CONST_regValName_systemComponent  ),  (  char  *  )&dwSystemComponentValue,  sizeof(  dwSystemComponentValue  )  )  &&  dwSystemComponentValue  ==  1  )  {
			  traceLog(  _T(  "%s get systemComponentValue failed"  ),  displayNameValue  );  continue;
		  }

		  if  (  !myWChar2Utf8(  displayNameValue,  buf,  sizeof(  buf  )  )  )  {
			  traceLogA(  "Error: buf is too small to contain the software displayName!"  );  continue;
		  }
		  trim(  buf  );
		  if  (  !buf[0]  )  continue;
		  
		  if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
	 	  pComponent->uiType  =  CONST_assetType_software;
		  _snprintf(  pComponent->u.software.displayName,  sizeof(  pAssetsInfo->components[pAssetsInfo->cnt].u.software.displayName  ),  "%s",  buf  );
		  traceLogA(  (  "get %s ok"  ),  pComponent->u.software.displayName  );
		  cnt  ++  ;
		  submitComponent(  pAssetsInfo,  CP_UTF8  );
	 }

	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 
	 traceLogA(  "total %d software",  cnt  );

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 return  iErr;
}



