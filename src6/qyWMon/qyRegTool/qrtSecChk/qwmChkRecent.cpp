


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



int  chkUsrRecent(  void  *  pSubThreadInfo,  TCHAR  *  rootDir,  TCHAR  *  subDirName  );

 //  检查最近使用文件
 //  完成时pRegTool->iProgress应等于CONST_qrtStep_chkRecent
 int  chkRecent(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 int						iErr			=	-1;
	 MT_SUBTHREADINFO		*	pSubThreadInfo	=  (  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL			*	pRegTool		=  (  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 
	 if  (  !pRegTool->env.ucbWinNt  )  {
		 iErr  =  chkUsrRecent(  pSubThreadInfo,  pRegTool->winDir,  NULL  );
		 goto  errLabel;
	 }

	 if  (  qwmEnumUsrRootDir(  &pRegTool->env,  pRegTool->usrsRootDir,  (  PF_commonHandler  )chkUsrRecent,  pSubThreadInfo,  pRegTool->usrsRootDir  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	 return  iErr;
}

 //  检查usrsRootDir\subDirName下的recent目录
 //  允许subDirName为NULL, 则检查usrsRootDir下的recent目录
 //		 返回		1	表示需终止枚举
 //					0	表成功
 //					-1	表失败
 int  chkUsrRecent(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  )
{
	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo  =	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 //  char						recentDir[CONST_qyMaxPathLen  +  1];
     HANDLE							fh				=	NULL;
	 TCHAR							scanName[CONST_qyMaxPathLen  +  1];
	 WIN32_FIND_DATA				FindData;
	 FILETIME						localFileTime;
	 SYSTEMTIME						systemTime;
	 TCHAR						*	p				=	NULL;
	 QNM_WMBUF_SHOWSECCHKEVENT		wmBuf;
	 char							buf[256];

	 if  (  !subDirName  )  subDirName  =  _T(  ""  );

	 //  检查可略去的目录
	 if  (  bSkippedSubDir(  subDirName  )  )  {
		 traceLog(  _T(  "chkUsrRecent: %s skipped"  ),  subDirName  );
		 iErr  =  0;  goto  errLabel;
	 }
	 traceLog(  _T(  "chkUsrRecent %s"  ),  subDirName  );

	 switch  (  pRegTool->env.iPlatformId  )  {
			 case  CONST_qyPlatform_win98:
			 case  CONST_qyPlatform_winme:
			 case  CONST_qyPlatform_nt:
			 case  CONST_qyPlatform_win2k:
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
				   if  (  tQyStrCat(  rootDir,  subDirName,  scanName,  mycountof(  scanName  )  )  )  goto  errLabel;
				   break;
			 default:
				    if  (  tQyStrCat(  rootDir,  subDirName,  scanName,  mycountof(  scanName  )  )  )  goto  errLabel;
					if  (  trailDir(  scanName,  mycountof(  scanName  )  )  )  goto  errLabel;
					_sntprintf(  scanName,  mycountof(  scanName  ),  _T(  "%s%s"  ),  scanName,  _T(  "AppData\\Roaming\\Microsoft\\Windows"  )  );
					break;
	 }

	 if  (  _tcschr(  _T(  "/\\"  ),  *(  scanName  +  lstrlen(  scanName  )  -  1  )  )  ==  NULL  )  p  =  _T(  "\\recent\\*"  );
     else  p  =  _T(  "recent\\*"  );	
	 if  (  tQyStrCat(  scanName,  p,  scanName,  mycountof(  scanName  )  )  )  goto  errLabel;

     fh  =  FindFirstFile(  scanName,  &FindData  );
	 if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 do  {

		 if  (  pRegTool->bQuit  )  {						//  系统总退出令
			 traceLogA(  "chkUsrRecent: 得到退出令"  );  
			 iErr  =  CONST_qyRet_quit;		 goto  errLabel;
		 }

         tTrim(  FindData.cFileName  );
		 traceLogA(  "chkUsrRecent: 搜索到%s",  FindData.cFileName  ); 
		 
		 if  (  !lstrcmpi(  FindData.cFileName,  _T(  "."  )  )  
			 ||  !lstrcmpi(  FindData.cFileName,  _T(  ".."  )  )  
				||  !lstrcmpi(  FindData.cFileName,  _T(  "desktop.ini"  )  )  )  
		 {
			 continue;
		 }

		 //  
		 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
		 wmBuf.event.lEventType  =  CONST_qyEventType_secChk_recent;
		 if  (  !FileTimeToLocalFileTime(  &FindData.ftLastWriteTime,  &localFileTime  )  )  continue;
		 if  (  !FileTimeToSystemTime(  &localFileTime,  &systemTime  )  )  continue;
		 //  _snprintf(  wmBuf.event.localEventTime,  sizeof(  wmBuf.event.localEventTime  ),
		 sprintf(  buf,  
				"%04d%02d%02d%02d%02d%02d", 
					systemTime.wYear,  
						systemTime.wMonth,  
							systemTime.wDay,  
								systemTime.wHour,  
									systemTime.wMinute,  
										systemTime.wSecond  );
		 safeStrnCpy(  buf,  wmBuf.event.localEventTime,  sizeof(  wmBuf.event.localEventTime  )  );
		 myTChar2Utf8(  subDirName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
		 myTChar2Utf8(  FindData.cFileName,  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  )  );
		 
		 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  break;
		 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
		 
	}  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );
 
	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  fh  )  )  FindClose(  fh  );
	 
	 traceLogA(  "chkUsrRecent returns %d",  iErr  );

	 return  iErr;

}

 /*

 int  addEventToCache(  QNM_SECCHK_EVENT  *  pEvent,  QY_REG_TOOL  *  pRegTool  )
{
	 if  (  pRegTool->uiSecChkEventCnt  >=  pRegTool->uiMaxSecChkEventCnt  )  {
		 traceLogA(  "secChkEventCache已满,  不再接收事件"  );  return  -1;
	 }
	 memcpy(  &pRegTool->pSecChkEventCache[sizeof(  QNM_SECCHK_EVENT  )  *  pRegTool->uiSecChkEventCnt],  pEvent,  sizeof(  QNM_SECCHK_EVENT  )  );
	 pRegTool->uiSecChkEventCnt  ++  ;

	 return  0;
}

  */


 /*
  int  qwmEnumUsrRootDir(  QY_ENV  *  pEnv,  char  *  usrsRootDir,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  )
{	
	int							iErr		=		-1;
    char						scanName[PATHLEN];
    WIN32_FIND_DATA				FindData;
    HANDLE						fh			=		NULL;
	DWORD						dwFileAttributes;
	char				*		p			=		NULL;

	if  (  (  dwFileAttributes  =  GetFileAttributes(  usrsRootDir  )  )  !=  -1
		&&  !(  dwFileAttributes  &  FILE_ATTRIBUTE_DIRECTORY  )  )
	{
		traceLogA(  "非目录"  );  goto  errLabel;
	}
        
    if  (  safeStrCpy(  usrsRootDir,  scanName,  sizeof(  scanName  )  )  )  goto  errLabel;

    if  (  strchr(  "/\\",  *(  scanName  +  strlen(  scanName  )  -  1  )  )  ==  NULL  )  p  =  "\\*";
    else  p  =  "*";
	if  (  qyStrCat(  scanName,  p,  scanName,  sizeof(  scanName  )  )  )  goto  errLabel;

    fh  =  FindFirstFile(  scanName,  &FindData  );
    if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
    
	do  {
        trim(  FindData.cFileName  );
		//  traceLogA(  "搜索到%s",  FindData.cFileName  );  
		if  (  pF  )  pF(  p0,  p1,  FindData.cFileName  );	 	  
	}  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );

	iErr  =  0;

errLabel:
	
	if  (  isHandleValid(  fh  )  )  FindClose(  fh  );
	 
	return  iErr;

}
*/

