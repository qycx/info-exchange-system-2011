

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

#define		CONST_ieIndexDatId						"Client UrlCache MMF Ver"
#define		CONST_ieUrlTag							"URL"
#define		CONST_ieIndexBlockSize					128		//  0x80
#define		CONST_ieMm256BlockSize					256		//  0x100
//#define		CONST_ieMm2048BlockSize					2048	//  0x800
#define		CONST_ieMm2048BlockSize					0x800

#define		CONST_nPosForIe4						0x38
#define		CONST_nPosForIe5						0x34

#define		CONST_ieMmDatOffset_totalOfBlocks		0x24		//  the number of blocks available in the file
#define		CONST_ieMmDatOffset_totalOfEntries		0x28		//  the number of valid entries in the file

//  #define		CONST_ieMmDatOffset_startData			1024	    //  0x400		//  the header
#define		CONST_ieMmDatOffset_startData			0x400		//  the header
#define		CONST_ieMmDatOffset_startURL			0x14		//  the offset  to  start of URL 
#define		CONST_ieMmDatOffset_writtenTime			0x30		//	QUADWORD time,  win32 time  file written to cache		需要
#define		CONST_ieMmDatOffset_startContent		0x44		//  offset to start of content 
#define		COSNT_ieMmDatOffset_endContent			0x48		//  length of content data region above

//  对非index.dat文件略过，（注：这里应加入对ie3,ie4等索引文件
#define		MACRO_bIndexDatFile(  pureFileName  )		(  !_tcsicmp(  (  pureFileName  ),  _T(  CONST_winFile_indexDat  )  )  ||  !_tcsicmp(  (  pureFileName  ),  _T(  CONST_winFile_mm256Dat  )  )  ||  !_tcsicmp(  (  pureFileName  ),  _T(  CONST_winFile_mm2048Dat  )  )  )


int  chkUsrCookie(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  );
int  chkUsrIeHistory(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  );
int  chkUsrIeTif(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  );

int  chkIeFile(  void  *  pSubThreadInfoParam,  TCHAR  *  usrName,  TCHAR  *  sth  );
int  chkIeIndexDat(  void  *  pSubThreadInfoParam,  TCHAR  *  usrName,  TCHAR  *  indexDatFile  );
int  chkIeMm256Mm2048Dat(  void  *  pSubThreadInfoParam,  TCHAR  *  usrName,  TCHAR  *  indexDatFile  );




 //  检查Ie
 int  chkIe(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 int					iErr			  =  -1;
	 MT_SUBTHREADINFO	*	pSubThreadInfo  =  (  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL		*	pRegTool  =  (  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 QY_REG					reg;
	 TCHAR					cacheDir[CONST_qyMaxPathLen  +  1];
	 TCHAR	tBuf[128];
	 
	 #ifdef  __DEBUG__
			 //  for test
	 		 //  chkIeMm256Mm2048Dat(  pSubThreadInfo,  "",  "c:\\temp\\mm2048.dat"  );
	 		 //  goto  errLabel;
	 		 //
	 #endif

	 //  对98,me和WinNt(ie3)处理在这里
	 if  (  !pRegTool->env.ucbWinNt  ||  pRegTool->env.iPlatformId  ==  CONST_qyPlatform_nt  )  {		//  对98
		 chkUsrCookie(  pSubThreadInfo,  pRegTool->winDir,  NULL  );
		 chkUsrIeHistory(  pSubThreadInfo,  pRegTool->winDir,  NULL  );
		 chkUsrIeTif(  pSubThreadInfo,  pRegTool->winDir,  NULL  );
	 }

	 if  (  pRegTool->env.ucbWinNt  )  {	//  下面处理nt系列的多用户的模式，//  对win2k后的版本处理在这里
		 //  检查Cookie
		 if  (  qwmEnumUsrRootDir(  &pRegTool->env,  pRegTool->usrsRootDir,  (  PF_commonHandler  )chkUsrCookie,  pSubThreadInfo,  pRegTool->usrsRootDir  )  )  goto  errLabel;
		 //  检查History
		 if  (  qwmEnumUsrRootDir(  &pRegTool->env,  pRegTool->usrsRootDir,  (  PF_commonHandler  )chkUsrIeHistory,  pSubThreadInfo,  pRegTool->usrsRootDir  )  )  goto  errLabel;
		 //  检查Tif
		 if  (  qwmEnumUsrRootDir(  &pRegTool->env,  pRegTool->usrsRootDir,  (  PF_commonHandler  )chkUsrIeTif,  pSubThreadInfo,  pRegTool->usrsRootDir  )  )  goto  errLabel;
	 }

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_LOCAL_MACHINE;
	 //  if  (  !pRegTool->env.ucbWinNt  )  {	//  98,me的临时目录变更
	 //		 lstrcpyn(  reg.rootKey,  CONST_qyRootKey_cacheContent,  sizeof(  reg.rootKey  )  );	 
	 //		 if  (  !qyGetRegCfgEx(  &reg,  CONST_regValName_cachePath,  cacheDir,  sizeof(  cacheDir  )  )  )  {
	 //			 chkIeFile(  pSubThreadInfo,  pRegTool->curUsrName,  cacheDir  );
	 //		}
	 //		}
	 //  else  
	 {	//  NT的ie3的临时目录变更
		   lstrcpyn(  reg.rootKey,  _T(  CONST_qyRootKey_cachePaths  ),  mycountof(  reg.rootKey  )  );
		   if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_directory  ),  (  char  *  )cacheDir,  sizeof(  cacheDir  )  )  )  {
			   myStr2TChar(  pRegTool->curUsrName,  tBuf,  mycountof(  tBuf  )  );
			   chkIeFile(  pSubThreadInfo,  tBuf,  cacheDir  );
		   } 
	 }

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyRootKey_shellFolders  ),  mycountof(  reg.rootKey  )  );	 
	 if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_cache  ),  (  char  *  )cacheDir,  sizeof(  cacheDir  )  )  )  {
		 myStr2TChar(  pRegTool->curUsrName,  tBuf,  mycountof(  tBuf  )  );
		 chkIeFile(  pSubThreadInfo,  tBuf,  cacheDir  );
	 }
	 
	 iErr     =      0;

errLabel:
	 return  iErr;
}


 //  检查usrsRootDir\subDirName下的Cookies目录
 //  允许subDirName为NULL, 则检查usrsRootDir下的Cookies目录
 //  该函数可返回1以表示需终止枚举
 //					0	表成功
 //					-1	表失败
 int  chkUsrCookie(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  )
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

	 if  (  bSkippedSubDir(  subDirName  )  )  {
		 traceLogA(  "chkUsrCookie: %s被略过处理",  subDirName  );
		 iErr  =  0;  goto  errLabel;
	 }
	 traceLogA(  "chkUsrCookie现在处理%s",  subDirName  );
	 
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


	 if  (  _tcschr(  _T(  "/\\"  ),  *(  scanName  +  lstrlen(  scanName  )  -  1  )  )  ==  NULL  )  p  =  _T(  "\\Cookies\\*"  );
     else  p  =  _T(  "Cookies\\*"  );	
	 if  (  tQyStrCat(  scanName,  p,  scanName,  mycountof(  scanName  )  )  )  goto  errLabel;

     fh  =  FindFirstFile(  scanName,  &FindData  );
	 if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 do  {

		 if  (  pRegTool->bQuit  )  {				//  系统总退出令
			 traceLogA(  "chkUsrCookie: 得到退出令"  );  
			 iErr  =  CONST_qyRet_quit;				goto  errLabel;
		 }

         tTrim(  FindData.cFileName  );
		 traceLogA(  "chkUsrCookie: 搜索到%s",  FindData.cFileName  ); 
		 
		 if  (  !_tcsicmp(  FindData.cFileName,  _T(  "."  )  ) 
			 ||  !_tcsicmp(  FindData.cFileName,  _T(  ".."  )  )
				||  MACRO_bIndexDatFile(  FindData.cFileName  )  )  
		 {
			 continue;
		 }
		 
		 //  
		 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
		 wmBuf.event.lEventType  =  CONST_qyEventType_secChk_cookie;
		 if  (  !FileTimeToLocalFileTime(  &FindData.ftLastWriteTime,  &localFileTime  )  )  continue;
		 if  (  !FileTimeToSystemTime(  &localFileTime,  &systemTime  )  )  continue;
		 _snprintf(  buf,  sizeof(  buf  ),  
				"%04d%02d%02d%02d%02d%02d", 
					systemTime.wYear,  
						systemTime.wMonth,  
							systemTime.wDay,  
								systemTime.wHour,  
									systemTime.wMinute,  
										systemTime.wSecond  );
		 strncpy(  wmBuf.event.localEventTime,  buf,  sizeof(  wmBuf.event.localEventTime  )  );
		 myTChar2Utf8(  subDirName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
		 myTChar2Utf8(  FindData.cFileName,  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  )  );
		 
		 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  break;
		 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
		 
	}  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );
 
	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  fh  )  )  FindClose(  fh  );

	 traceLogA(  "chkUsrCookie returns %d",  iErr  );

	 return  iErr;

}


 //  检查usrsRootDir\subDirName下的history目录
 //  允许subDirName为NULL, 则检查usrsRootDir下的history目录
 //  该函数可返回1以表示需终止枚举
 //					0	表成功
 //					-1	表失败
 int  chkUsrIeHistory(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  )
{
	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo  =	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
     TCHAR							scanDir[CONST_qyMaxPathLen  +  1];
	 //  char						*	ieHistorySubDir	=	(  !pRegTool->env.ucbWinNt  ||  pRegTool->env.iPlatformId  ==  CONST_qyPlatform_nt  )  ?  "History\\"  :  "Local Settings\\History\\";			
	 TCHAR						*	ieHistorySubDir	=	_T(  ""  );
	 
	 if  (  !pRegTool->env.ucbWinNt  ||  pRegTool->env.iPlatformId  ==  CONST_qyPlatform_nt  )  ieHistorySubDir  =  _T(  "History\\"  );
	 else  {
		   switch  (  pRegTool->env.iPlatformId  )  {
				   case  CONST_qyPlatform_win2k:
				   case  CONST_qyPlatform_winxp:
				   case  CONST_qyPlatform_win2003:
					     ieHistorySubDir  =  _T(  "Local Settings\\History\\"  );			
						 break;
				   default:
					       ieHistorySubDir  =  _T(  "AppData\\Local\\Microsoft\\Windows\\History\\"  );			
					       break;
		   }
	 }
	 
	 if  (  !subDirName  )  subDirName  =  _T(  ""  );

	 if  (  bSkippedSubDir(  subDirName  )  )  {
		 traceLogA(  "chkUsrIeHistory: %s被略过处理",  subDirName  );
		 iErr  =  0;  goto  errLabel;
	 }
	 traceLog(  _T(  "chkUsrIeHistory %s"  ),  subDirName  );
	 
	 if  (  tQyStrCat(  rootDir,  subDirName,  scanDir,  mycountof(  scanDir  )  )  )  goto  errLabel;
	 if  (  trailDir(  scanDir,  mycountof(  scanDir  )  )  )  goto  errLabel;
	 if  (  tQyStrCat(  scanDir,  ieHistorySubDir,  scanDir,  mycountof(  scanDir  )  )  )  goto  errLabel;
	 
	 if  (  chkIeFile(  pSubThreadInfo,  subDirName,  scanDir  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	 return  iErr;
}



 //  该函数可返回1以表示需终止枚举
 //					0	表成功
 //					-1	表失败
 int  chkUsrIeTif(  void  *  pSubThreadInfoParam,  TCHAR  *  rootDir,  TCHAR  *  subDirName  )
{
	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo  =	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
     TCHAR							scanDir[CONST_qyMaxPathLen  +  1];
	 TCHAR						*	ieTifSubDir		=	_T(  ""  );
	 
	 if  (  !pRegTool->env.ucbWinNt  ||  pRegTool->env.iPlatformId  ==  CONST_qyPlatform_nt  )  ieTifSubDir  =  _T(  "Temporary Internet Files\\"  );
	 else  {
		   switch  (  pRegTool->env.iPlatformId  )  {
			       case  CONST_qyPlatform_win2k:
				   case  CONST_qyPlatform_winxp:
				   case  CONST_qyPlatform_win2003:
					     ieTifSubDir  =  _T(  "Local Settings\\Temporary Internet Files\\"  );			
						 break;
				   default:
						   ieTifSubDir  =  _T(  "AppData\\Local\\Microsoft\\Windows\\Temporary Internet Files\\"  );			
						   break;		  
		   }
	 }
	 //

	 if  (  !subDirName  )  subDirName  =  _T(  ""  );

	 if  (  bSkippedSubDir(  subDirName  )  )  {
		 traceLogA(  "chkUsrIeTif: %s被略过处理",  subDirName  );
		 iErr  =  0;  goto  errLabel;
	 }
	 traceLog(  _T(  "chkUsrIeTif %s"  ),  subDirName  );
	 
	 if  (  tQyStrCat(  rootDir,  subDirName,  scanDir,  mycountof(  scanDir  )  )  )  goto  errLabel;
	 if  (  trailDir(  scanDir,  mycountof(  scanDir  )  )  )  goto  errLabel;
	 if  (  tQyStrCat(  scanDir,  ieTifSubDir,  scanDir,  mycountof(  scanDir  )  )  )  goto  errLabel;
	 
	 if  (  chkIeFile(  pSubThreadInfo,  subDirName,  scanDir  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	 return  iErr;
}





 //  该函数处理一个文件或枚举一个目录中的index.dat文件等
 //  该函数可返回1以表示需终止枚举
 //					0	表成功
 //					-1	表失败
 int  chkIeFile(  void  *  pSubThreadInfoParam,  TCHAR  *  usrName,  TCHAR  *  fileName  )
{
	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo  =	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
     HANDLE							fh				=	NULL;
	 TCHAR							scanDir[CONST_qyMaxPathLen  +  1];
	 TCHAR							scanName[CONST_qyMaxPathLen  +  1];
	 TCHAR							scanedFile[CONST_qyMaxPathLen  +  1];
	 WIN32_FIND_DATA				FindData;

	 if  (  !bDir(  fileName  )  )  {
		 return  chkIeIndexDat(  pSubThreadInfoParam,  usrName,  fileName  );		 
	 }

	 traceLog(  _T(  "chkIeFile: %s"  ),  fileName  );

	 //  _snprintf(  scanDir,  sizeof(  scanDir  ),  "%s",  fileName  );
	 lstrcpyn(  scanDir,  fileName,  mycountof(  scanDir  )  );
	 trailDir(  scanDir,  mycountof(  scanDir  )  );
	 //  _snprintf(  scanName,  sizeof(  scanName  ),  "%s*",  scanDir  );	 
	 lstrcpyn(  scanName,  scanDir,  mycountof(  scanName  )  );
	 lstrcpyn(  scanName  +  lstrlen(  scanName  ),  _T(  "*"  ),  mycountof(  scanName  )  -  lstrlen(  scanName  )  );

     fh  =  FindFirstFile(  scanName,  &FindData  );
	 if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 do  {

		 if  (  pRegTool->bQuit  )  {				//  系统总退出令
			 traceLogA(  "chkIeFile: 得到退出令"  );  
			 iErr  =  CONST_qyRet_quit;				goto  errLabel;
		 }

         tTrim(  FindData.cFileName  );
		 traceLog(  _T(  "chkIeFile: %s"  ),  FindData.cFileName  ); 

		 //  略过一些不处理的文件
 		 if  (  !lstrcmpi(  FindData.cFileName,  _T(  "."  )  )  
			 ||  !lstrcmpi(  FindData.cFileName,  _T(  ".."  )  )  
				||  !lstrcmpi(  FindData.cFileName,  _T(  CONST_winFile_desktopIni  )  )  )  
		 {
			 continue;
		 }
		
		 //  _snprintf(  scanedFile,  sizeof(  scanedFile  ),  "%s%s",  scanDir,  FindData.cFileName  );
		 lstrcpyn(  scanedFile,  scanDir,  mycountof(  scanDir  )  );
		 lstrcpyn(  scanedFile  +  lstrlen(  scanedFile  ),  FindData.cFileName,  mycountof(  scanedFile  )  -  lstrlen(  scanedFile  )  );
		
		 //  对目录采用递归的处理方式
		 if  (  bDir(  scanedFile  )  )  {
			 chkIeFile(  pSubThreadInfoParam,  usrName,  scanedFile  );
			 continue;
		 }
		 
		 //  对非index.dat文件略过处理
		 if  (  !MACRO_bIndexDatFile(  FindData.cFileName  )  )  continue;

		 chkIeIndexDat(  pSubThreadInfo,  usrName,  scanedFile  );				
			 
	 }  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );
 
	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  fh  )  )  FindClose(  fh  );

	 traceLogA(  "chkIeFile: 枚举%s结束, %s",  fileName,  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;

}

typedef  struct  __ieIndexBlockHead_t  {
				 char				tag[4];
				 unsigned  long		nBlocks;
				 char				lastModifiedTime[8];
				 char				lastAccessedTime[8];
				 char				expiredTime[8];

}		 IE_INDEXBLOCK_HEAD;

typedef  struct  __ieMm2048BlockHead_t  {
				 long					len;
				 char					reserved1[16];
				 unsigned  long			offsetToStartUrl;
				 char					reserved2[16];
				 char					lastModifiedTime[8];
				 char					lastAccessedTime[8];
				 char					expiredTime[8];
}		 IE_MM2048BLOCK_HEAD;

#define		CONST_urlPrefix_file			"file"

 QY_DMITEM		CONST_urlPrefixTable[]	=
{
	{	0,		(  TCHAR  *  )(  "http"  ),			},
	{	1,		(  TCHAR  *  )(  "https"  ),		},
	{	2,		(  TCHAR  *  )(  "ftp"  ),			},
	{	3,		(  TCHAR  *  )(  "mail"  ),			},
	{	-1,		NULL,			},
};


 //  检查index.dat文件
 int  chkIeIndexDat(  void  *  pSubThreadInfoParam,  TCHAR  *  usrName,  TCHAR  *  indexDatFile  )
{
	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo  =	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 char							tmpBuf[4096  +  2  +  1];
	 unsigned  int					nRead			=	0;		//  表明tmpBuf中已有的数据长度
	 unsigned  int					nProcessed		=	0;		//  表明tmpBuf中已处理的数据长度
	 //  FILE						*   tmpStream       =   NULL;
	 HANDLE							tmpStream		=	NULL;
	 int							numRead, total  =   0;
	 unsigned  int					len;
	 unsigned  int					urlTagLen		=	strlen(  CONST_ieUrlTag  );
	 long							lIndexDatVer	=	0;
	 int							i;
	 unsigned  int					uiBlockSize		=	CONST_ieIndexBlockSize;
	 IE_INDEXBLOCK_HEAD			*	pBlockHead		=	NULL;
	 //  FILETIME						ftLastModifiedTime;
	 FILETIME						ftLastAccessTime;
	 FILETIME						localFileTime;
	 SYSTEMTIME						systemTime;
	 QNM_WMBUF_SHOWSECCHKEVENT		wmBuf;
	 int							nPos;					//  存放offsetStartUrl的位置
	 unsigned  int					offsetToStartUrl;
	 char						*	pUrl			=	NULL;
	 char						*	p				=	NULL;
	 long							lEventType;
	 char							buf[256];
	 DWORD							dwRead;
	 BOOL							bFeof			=	FALSE;
	 	 
	 traceLog(  _T(  "chkIeIndexDat: %s"  ),  indexDatFile  ); 

	 memset(  tmpBuf,  0,  sizeof(  tmpBuf  )  );
	 
	 //  文件操作
	 if  (  !(  tmpStream  =  CreateFile(  indexDatFile,  GENERIC_READ,  FILE_SHARE_READ  |  FILE_SHARE_WRITE  |  FILE_SHARE_DELETE,  NULL,  OPEN_EXISTING,  0,  0  )  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //  先读取文件头以确定文件类型与版本
	 len  =  strlen(  CONST_ieIndexDatId  );	 
	 numRead  =  len  +  32;
	 //  if  (  1  !=  fread(  tmpBuf,  numRead,  1,  tmpStream  )  
	 if  (  !ReadFile(  tmpStream,  tmpBuf,  numRead,  &dwRead,  NULL  )
		 ||  dwRead  !=  (  DWORD  )numRead
			||  strnicmp(  tmpBuf,  CONST_ieIndexDatId,  len  )  )  
	 {
		 traceLogA(  "非index.dat文件格式"  );  
		 iErr  =  0;  goto  errLabel;
	 }
	 lIndexDatVer  =  atol(  tmpBuf  +  len  );
	 nProcessed  =  len;
	 nRead  =  numRead;
	 
	 traceLogA(  "lIndexDatVer is:   %d,  ver is %s",  lIndexDatVer,  tmpBuf  +  len  );
	 
	 if  (  lIndexDatVer  ==  3  )  {		//  如果是ie3, 则专门处理
		 CloseHandle(  tmpStream  );  tmpStream  =  NULL;
		 iErr  =  chkIeMm256Mm2048Dat(  pSubThreadInfo,  usrName,  indexDatFile  );
		 goto  errLabel;
	 }

	 //  这里根据fIndexDatVer来确定nPos
	 if  (  lIndexDatVer  ==  4  )  nPos  =  CONST_nPosForIe4;		//  0x38;
	 else  nPos  =  CONST_nPosForIe5;
	 traceLogA(  "------nPos  =  0x%x  ",  nPos  );

	 /* Cycle until end of file reached: */
	 while  (  !bFeof  )  {
		 
			/* Attempt to read in 4096 : */
		    if  (  nProcessed  )  {		//  将nProcessed的已处理长度清理
				memcpy(  tmpBuf,  tmpBuf  +  nProcessed,  nRead  -  nProcessed  );
				nRead  -=  nProcessed;  nProcessed  =  0;
			}

		    numRead  =  sizeof(  tmpBuf  )  -  1  -  nRead;
			if  (  numRead  ==  0  )  {
				traceLogA(  "程序设计有问题，numRead不应为0"  );  goto  errLabel;
			}
			//  if  (  1  !=  fread(  tmpBuf  +  nRead,  numRead,  1,  tmpStream  )  )  {
			//	if  (  (  numRead  =  fread(  tmpBuf  +  nRead,  1,  numRead,  tmpStream  )  )  <=  0  )  {
			if  (  !ReadFile(  tmpStream,  tmpBuf  +  nRead,  numRead,  &dwRead,  NULL  )
				||  dwRead  ==  0  )
			{
				//  无法再读取数据了
				iErr  =  0;  goto  errLabel;								
			}
			numRead  =  dwRead;
			nRead  +=  numRead;
			tmpBuf[nRead]  =  0;

			if  (  nRead  <  uiBlockSize  )  {
				traceLogA(  "缓冲中的数据不足以构成一个indexBlock, 认为处理完毕"  );
				iErr  =  0;  goto  errLabel;
			}
			
			for  (  ;  ;  )  {		//  扫描缓冲中所有的url
				 
				 if  (  pRegTool->bQuit  )  {
					 iErr  =  CONST_qyRet_quit;  goto  errLabel;
				 }

				 for  (  i  =  nProcessed;  i  <  (  int  )nRead;  i  ++  )  {
				 	  if  (  !strnicmp(  tmpBuf  +  i,  CONST_ieUrlTag,  urlTagLen  )  )  break;
				 }
				 if  (  i  ==  (  int  )nRead  )  {
					 //  没有在缓冲中查到"URL", 需要继续寻找
					 if  (  nRead  <  urlTagLen  )  {
						 MACRO_qyAssert(  0,  _T(  "奇怪：nRead  <  urlTagLen"  )  );  goto  errLabel;
					 }
					 nProcessed  =  nRead  -  urlTagLen;  break;
				 }
		 		 nProcessed  =  i;

				 //  i  <  nRead则表明已找到了URL
				 if  (  nRead  -  nProcessed  <  uiBlockSize  )  break;  //  如果缓冲中数据不够则须继续读取数据					 
				 pBlockHead  =  (  IE_INDEXBLOCK_HEAD  *  )(  tmpBuf  +  nProcessed  );
				 if  (  pBlockHead->nBlocks  *  uiBlockSize  >  nRead  -  nProcessed  )  break;  //  如果缓冲中数据不够则须继续读取数据
				
				 //  这里先将nProcessed移到此记录后，因为下面肯定处理该记录了
				 nProcessed  +=  pBlockHead->nBlocks  *  uiBlockSize;

				 offsetToStartUrl  =  *(  (  char  *  )pBlockHead  +  nPos  );
				 if  (  offsetToStartUrl  >  pBlockHead->nBlocks  *  uiBlockSize  )  {
					 traceLogA(  "offsetToStartUrl太大了, %d",  offsetToStartUrl  );  goto  errLabel;
				 }				 
				 pUrl  =  (  char  *  )pBlockHead  +  offsetToStartUrl; 

				 traceLogA(  " 得到URL为：[%s]  ",  pUrl  );
				 if  (  (  p  =  strchr(  pUrl,  '@'  )  )  )  {
					 p  ++  ;	pUrl  =  p;
				 }

				 //  traceLogA(  "这里应加入校验url的代码，以避免出现判断错误的情况"  );
				 for  (  i  =  0;  CONST_urlPrefixTable[i].type  !=  -1;  i  ++  )  {
					  if  (  !strnicmp(  pUrl,  (  char  *  )CONST_urlPrefixTable[i].des,  strlen(  (  char  *  )CONST_urlPrefixTable[i].des  )  )  )  break;
				 }
				 if  (  CONST_urlPrefixTable[i].type  !=  -1  )  lEventType  =  CONST_qyEventType_secChk_ieHistory;
				 else  {
					 if  (  strnicmp(  pUrl,  CONST_urlPrefix_file,  strlen(  CONST_urlPrefix_file  )  )  )  continue;
					 lEventType  =  CONST_qyEventType_secChk_fileHistory;
				 }
				 
				 //  
				 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
				 wmBuf.event.lEventType  =  lEventType;
				 //  memcpy(  (  char  *  )&ftLastModifiedTime,  pBlockHead->lastModifiedTime,  sizeof(  ftLastModifiedTime  )  );
				 //  if  (  !FileTimeToLocalFileTime(  &ftLastModifiedTime,  &localFileTime  )  )  continue;

				 memcpy(  (  char  *  )&ftLastAccessTime,  pBlockHead->lastAccessedTime,  sizeof(  ftLastAccessTime  )  );
				 if  (  !FileTimeToLocalFileTime(  &ftLastAccessTime,  &localFileTime  )  )  continue;

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
			 	 myTChar2Utf8(  usrName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
			 	 safeStrnCpy(  pUrl,  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  )  );

			 	 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  break;
			 	 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
			 
			}			 
	
	 }

	 iErr  =  0;

errLabel:
	 
	 if  (  tmpStream  )  CloseHandle(  tmpStream  );
	 traceLogA(  "chkUsrIeIndexdat returns %d",  iErr  );
	 return  iErr;
}

typedef  struct  __mmDatFileHead_t  {
				 char				id[36];
				 long				nBlocks;
				 long				nEntries;
}		 MMDAT_FILE_HEAD;



 int  chkIeMm256Mm2048Dat(  void  *  pSubThreadInfoParam,  TCHAR  *  usrName,  TCHAR  *  indexDatFile  )
{
 	 int							iErr			=	-1;
	 MT_SUBTHREADINFO			*	pSubThreadInfo  =	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL				*	pRegTool		=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 char							tmpBuf[4096  +  2  +  1];
	 unsigned  int					nRead			=	0;		//  表明tmpBuf中已有的数据长度
	 unsigned  int					nProcessed		=	0;		//  表明tmpBuf中已处理的数据长度
	 HANDLE							tmpStream       =   NULL;
	 int							numRead, total  =   0;
	 unsigned  int					len;
	 unsigned  int					urlTagLen		=	strlen(  CONST_ieUrlTag  );
	 long							lIndexDatVer	=	0;
	 int							i;
	 IE_MM2048BLOCK_HEAD		*	pBlockHead		=	NULL;
	 //  FILETIME						ftLastModifiedTime;
	 FILETIME						ftLastAccessTime;
	 FILETIME						localFileTime;
	 SYSTEMTIME						systemTime;
	 QNM_WMBUF_SHOWSECCHKEVENT		wmBuf;
	 //  unsigned  int					offsetToStartUrl;
	 char						*	pUrl			=	NULL;
	 char						*	p				=	NULL;
	 long							lEventType;
//	 int							dataLen;
	 int							nBlocks,nEntries;
	 unsigned  int					uiBlockSize		=	0;
	 char							buf[256];
	 DWORD							dwRead;
	 BOOL							bFeof			=	FALSE;
	 TCHAR						*	pT;
	 
	 traceLogA(  "chkIeMm256Mm2048Dat: 处理%s",  indexDatFile  ); 
	 //  先判断block的大小
	 if  (  !(  pT  =  _tcsrchr(  indexDatFile,  _T(  '\\'  )  )  )  )  goto  errLabel;
	 pT  ++  ;
	 if  (  !lstrcmpi(  pT,  _T(  CONST_winFile_mm256Dat  )  )  )  uiBlockSize  =  256;
	 else  if  (  !lstrcmpi(  pT,  _T(  CONST_winFile_mm2048Dat  )  )  )  uiBlockSize  =  2048;
	 else  goto  errLabel;


	 memset(  tmpBuf,  0,  sizeof(  tmpBuf  )  );
	 
	 //  文件操作
	 if  (  !(  tmpStream  =  CreateFile(  indexDatFile,  GENERIC_READ,  FILE_SHARE_READ  |  FILE_SHARE_WRITE  |  FILE_SHARE_DELETE,  NULL,  OPEN_EXISTING,  0,  0  )  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }


	 //  1  分析文件头，需要确定文件长度( nBlocks )或记录数的个数( nEntries )
	 //		记录：nProcessed( 已处理长度 )、numRead( 读取长度 )、nRead( 已有的数据长度 )
	 len  =  strlen(  CONST_ieIndexDatId  );
	 if  (  len  >  sizeof(  MMDAT_FILE_HEAD  )  )  {
		 traceLogA(  "len不能大于MMDAT_FILE_HEAD的大小"  );  goto  errLabel;
	 }
	 //  if  (  1  !=  fread(  tmpBuf,  sizeof(  MMDAT_FILE_HEAD  ),  1,  tmpStream  )  
	 if  (  !ReadFile(  tmpStream,  tmpBuf,  sizeof(  MMDAT_FILE_HEAD  ),  &dwRead,  NULL  )
		 ||  dwRead  !=  sizeof(  MMDAT_FILE_HEAD  )
			||  strnicmp(  tmpBuf,  CONST_ieIndexDatId,  len  )  )  
	 {
		 traceLogA(  "非index.dat,mm256.dat,mm2048.dat文件格式"  );  
		 iErr  =  0;  goto  errLabel;
	 }
	 lIndexDatVer  =  atol(  tmpBuf  +  len  );

	 nBlocks  =  (  (  MMDAT_FILE_HEAD  *  )tmpBuf  )->nBlocks;	
	 nEntries  =  (  (  MMDAT_FILE_HEAD  *  )tmpBuf  )->nEntries;
	 traceLogA(  "nBlocks is %d, nEntries is %d",  nBlocks,  nEntries  );
	 
	 //  略过剩余的文件头，到数据起始处
	 //  if  (  fseek(  tmpStream,  0x400,  SEEK_SET  )  )  goto  errLabel;
	 if  (  SetFilePointer(  tmpStream,  0x400,  NULL,  FILE_BEGIN  )  ==  0xFFFFFFFF  )  goto  errLabel;
	 
	 /* Cycle until end of file reached: */
	 while  (  !bFeof  )  {
			 
			/* Attempt to read in 4096 : */
		    if  (  nProcessed  )  {		//  将nProcessed的已处理长度清理
				memcpy(  tmpBuf,  tmpBuf  +  nProcessed,  nRead  -  nProcessed  );
				nRead  -=  nProcessed;  nProcessed  =  0;
			}

		    numRead  =  sizeof(  tmpBuf  )  -  1  -  nRead;
			//  if  (  1  !=  fread(  tmpBuf  +  nRead,  numRead,  1,  tmpStream  )  )  {
			//		if  (  (  numRead  =  fread(  tmpBuf  +  nRead,  1,  numRead,  tmpStream  )  )  <=  0  )  {
			if  (  !ReadFile(  tmpStream,  tmpBuf  +  nRead,  numRead,  &dwRead,  NULL  )
				||  dwRead  ==  0  )
			{				
				//  无法再读取数据了
				iErr  =  0;  goto  errLabel;								
			}
			numRead  =  dwRead;
			nRead  +=  numRead;
			tmpBuf[nRead]  =  0;

			if  (  nRead  <  uiBlockSize  )  {
				traceLogA(  "缓冲中的数据不足以构成一个block, 认为处理完毕"  );
				iErr  =  0;  goto  errLabel;
			}
			
			for  (  ;  ;  )  {		//  扫描缓冲中所有的url
				 
				 if  (  pRegTool->bQuit  )  {
					 iErr  =  CONST_qyRet_quit;  goto  errLabel;
				 }

				 if  (  nRead  -  nProcessed  <  uiBlockSize  )  break;  //  如果缓冲中数据不够则须继续读取数据					 
				 pBlockHead  =  (  IE_MM2048BLOCK_HEAD  *  )(  tmpBuf  +  nProcessed  );
				 
				 //  这里先将nProcessed移到此记录后，因为下面肯定处理该记录了
				 nProcessed  +=  uiBlockSize;

				 if  (  pBlockHead->offsetToStartUrl  >  uiBlockSize  )  {
					 traceLogA(  "chkIeMm256Mm2048: offsetToStartUrl %d 大于uiBlockSize %d, 略过此结构",  pBlockHead->offsetToStartUrl,  uiBlockSize  );  continue;
				 }

				 pUrl  =  (  (  char  *  )(  pBlockHead  )  )  +  pBlockHead->offsetToStartUrl; 

				 traceLogA(  " 得到URL为：[%s]  ",  pUrl  );
				 if  (  (  p  =  strchr(  pUrl,  '@'  )  )  )  {
					 p  ++  ;	pUrl  =  p;
				 }
				
				 //  traceLogA(  "这里应加入校验url的代码，以避免出现判断错误的情况"  );
				 for  (  i  =  0;  CONST_urlPrefixTable[i].type  !=  -1;  i  ++  )  {
					  if  (  !strnicmp(  pUrl,  (  char  *  )CONST_urlPrefixTable[i].des,  strlen(  (  char  *  )CONST_urlPrefixTable[i].des  )  )  )  break;
				 }
				 if  (  CONST_urlPrefixTable[i].type  !=  -1  )  lEventType  =  CONST_qyEventType_secChk_ieHistory;
				 else  {
					 if  (  strnicmp(  pUrl,  CONST_urlPrefix_file,  strlen(  CONST_urlPrefix_file  )  )  )  continue;
					 lEventType  =  CONST_qyEventType_secChk_fileHistory;
				 }
				 
				 //  
				 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
				 wmBuf.event.lEventType  =  lEventType;
				 //  memcpy(  (  char  *  )&ftLastModifiedTime,  pBlockHead->lastModifiedTime,  sizeof(  ftLastModifiedTime  )  );
				 //  if  (  !FileTimeToLocalFileTime(  &ftLastModifiedTime,  &localFileTime  )  )  continue;

				 memcpy(  (  char  *  )&ftLastAccessTime,  pBlockHead->lastAccessedTime,  sizeof(  ftLastAccessTime  )  );
				 if  (  !FileTimeToLocalFileTime(  &ftLastAccessTime,  &localFileTime  )  )  continue;

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
				 myTChar2Utf8(  usrName,  wmBuf.event.usrName,  sizeof(  wmBuf.event.usrName  )  );
			 	 safeStrnCpy(  pUrl,  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  )  );

				 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  break;
			 	 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
			 
			}	
	 }
	 
	 iErr  =  0;

errLabel:
 
	 if  (  tmpStream  )  CloseHandle(  tmpStream  );
	 traceLogA(  "chkUsrIeMm256Mm2048dat returns %d",  iErr  );
	 return  iErr;
}







