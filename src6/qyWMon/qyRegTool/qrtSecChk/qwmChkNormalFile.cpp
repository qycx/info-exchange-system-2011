

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"asrWMon.h"
#include	"qnmAssetsCommProc.h"
#include	"qyRegToolProc.h"
#include	"qwmAllHints.h"
#include	"qwmSvrChkCommProc.h"

#define  CONST_ProgramFiles					"Program Files"  
#define	 CONST_SystemVolumeInformation		"System Volume Information"
#define  CONST_dir_DocumentsandSettings		"Documents and Settings/"
#define  CONST_AllUsers						"All Users"
#define  CONST_DefaultUser					"Default User"
#define  CONST_Cookies						"Cookies"
#define	 CONST_winNt						"WinNT"
#define	 CONST_windows						"Windows"
#define	 CONST_i386							"I386"
#define	 CONST_inetpub						"Inetpub"

 BOOL  bSkippedDir_normalFile(  TCHAR  *  pathBuf,  TCHAR  *  subName  )
{
	 BOOL  bSkippedDir  =  TRUE;
	 TCHAR	buf[MAX_PATH  +  1];

	 if  (  !lstrcmp(  subName,  _T(  "."  )  )  ||  !lstrcmp(  subName,  _T(  ".."  )  )  )  goto  errLabel;
	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s"  ),  pathBuf  );
	 if  (  !lstrcmpi(  subName,  _T(  CONST_winNt  )  )  ||  !lstrcmpi(  subName,  _T(  CONST_windows  )  )  )  {
		 trailDir(  buf,  mycountof(  buf  )  );
		 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%ssystem32"  ),  buf  );
		 if  (  bDir(  buf  )  )  {
			 traceLogA(  "%s是系统目录, 不再进行检查",  pathBuf  );  
			 goto  errLabel;
		 }
	 }
	 if  (  !lstrcmpi(  subName,  _T(  CONST_ProgramFiles  )  )
		 ||  !lstrcmpi(  subName,  _T(  CONST_SystemVolumeInformation  )  )
			||  !lstrcmpi(  subName,  _T(  CONST_inetpub  )  )
				||  !lstrcmpi(  subName,  _T(  CONST_AllUsers  )  )
					||  !lstrcmpi(  subName, _T(  CONST_DefaultUser  )  )  )  
	 {
		 traceLogA(  "%s是程序目录，不再进行检查",  pathBuf  );
		 goto  errLabel;
 	 }
	 if  (  !lstrcmpi(  subName,  _T(  CONST_i386  )  )  )
	 {
		 traceLogA(  "%s是安装目录，不再进行检查",  pathBuf  );
		 goto  errLabel;
	 }
	 	
	 bSkippedDir  =  FALSE;
errLabel:
	 return  bSkippedDir;
}

 QY_DMITEM  CONST_skippedSubFixTable[]  =
{
	{	0,		(  TCHAR  *  )_T(  "exe"  ),			},
	{	1,		(  TCHAR  *  )_T(  "sys"  ),			},
	{	2,		(  TCHAR  *  )_T(  "vxd"  ),			},
	{	3,		(  TCHAR  *  )_T(  "dll"  ),			},
	{	4,		(  TCHAR  *  )_T(  "lib"  ),			},
	{	5,		(  TCHAR  *  )_T(  "bin"  ),			},
	{	6,		(  TCHAR  *  )_T(  "com"  ),			},
	{	7,		(  TCHAR  *  )_T(  "obj"  ),			},
	{	8,		(  TCHAR  *  )_T(  "sbr"  ),			},
	{	9,		(  TCHAR  *  )_T(  "cab"  ),			},
	{	10,		(  TCHAR  *  )_T(  "gif"  ),			},
	//
	{	-1,	NULL,	},
 };


 //  2005/08/15
 QY_DMITEM  CONST_procedSubFixTable[]  =
{
	{	0,		(  TCHAR  *  )_T(  "ppt"  ),			},
	{	0,		(  TCHAR  *  )_T(  "doc"  ),			},
	{	0,		(  TCHAR  *  )_T(  "xls"  ),			},
	{	0,		(  TCHAR  *  )_T(  "eml"  ),			},
	{	0,		(  TCHAR  *  )_T(  "zip"  ),			},
	{	0,		(  TCHAR  *  )_T(  "txt"  ),			},
	{	0,		(  TCHAR  *  )_T(  "pdf"  ),			},
	{	0,		(  TCHAR  *  )_T(  "lnk"  ),			},
	//  {	0,	(  TCHAR  *  )_T(  "chm"  ),			},
	//	{,	0,	(  TCHAR  *  )_T(  "log"  ),			},
	{	0,		(  TCHAR  *  )_T(  "htm"  ),			},
	{	0,		(  TCHAR  *  )_T(  "html"  ),			},
	{	-1,		NULL,			},
};


 int  myChkProc(  void   *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 int					iErr					=	0;
	 MT_SUBTHREADINFO	*	pSubThreadInfo			=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_REG_TOOL		*	pRegTool				=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	 TCHAR				*	parentPath				=	(  TCHAR  *  )p1Reserved;
	 WIN32_FIND_DATA	*	pFindData				=	(  WIN32_FIND_DATA  *  )p2Reserved;
	 TCHAR				*	subName					=	pFindData->cFileName;
	 TCHAR					pathBuf[MAX_PATH  +  1]	=	_T(  ""  );
	 char				*	p						=	NULL;
	 QY_DMITEM			*	pItem					=	NULL;
	 FILETIME				localFileTime;
	 SYSTEMTIME				systemTime;
	 char					buf[128];
	 TCHAR				*	pT;

	 if  (  !parentPath  ||  !subName  )  return  0;
	 if  (  bQrtQuit(  )  )  {
		 iErr  =  CONST_qyRet_quit;	goto  errLabel;
	 }

	 safeTcsnCpy(  parentPath,  pathBuf,  mycountof(  pathBuf  )  );
	 trailDir(  pathBuf,  mycountof(  pathBuf  )  );
	 _sntprintf(  pathBuf,  mycountof(  pathBuf  ),  _T(  "%s%s"  ),  pathBuf,  subName  );

	 bSetQrtProgressTxt1(  pathBuf  );
	 //  traceLogA(  "准备处理：%s",  pathBuf  );

	 if  (  bDir(  pathBuf  )  )  {
		 if  (  bSkippedDir_normalFile(  pathBuf,  subName  )  )  {
			 iErr  =  0;  goto  errLabel;
		 }
		 qwmEnumUsrDir(  &pRegTool->env,  pathBuf,  myChkProc,  pSubThreadInfoParam,  pathBuf  );
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  (  pT  =  _tcsrchr(  subName,  _T(  '.'  )  )  )  )  {
		 pT  ++  ;
		 for  (  pItem  =  CONST_skippedSubFixTable;  pItem->type  !=  -1;  pItem  ++  )  {
			  if  (  !lstrcmpi(  pT,  pItem->des  )  )  {
				  traceLogA(  "%s will be skipped",  pathBuf  );
			 	  iErr  =  0;  goto  errLabel;
		 	  }
		 }			  
	 }	 

	 //  2005/08/15, 为了减少数据量，故再做如下的过滤
	 if  (  !(  pT  =  _tcsrchr(  subName,  _T(  '.'  )  )  )  )  {
		 traceLogA(  "新的过滤条件：%s will be skipped",  pathBuf  );
		 iErr  =  0;  goto  errLabel;
	 }
	 pT  ++  ;
	 for  (  pItem  =  CONST_procedSubFixTable;  pItem->type  !=  -1;  pItem  ++  )  {
		  if  (  !lstrcmpi(  pT,  pItem->des  )  )  break;
	 }
	 if  (  pItem->type  ==  -1  )  {
		 traceLogA(  "新的过滤条件：%s will be skipped",  pathBuf  );
		 iErr  =  0;  goto  errLabel;
	 }

	 
	 //  这里为了防止出现过多的事件，先采用创建时间
	 if  (  FileTimeToLocalFileTime(  &pFindData->ftCreationTime,  &localFileTime  )  
		 &&  FileTimeToSystemTime(  &localFileTime,  &systemTime  )  )  
	 {
		 sprintf(  buf,  
				"%04d%02d%02d%02d%02d%02d", 
					systemTime.wYear,  
						systemTime.wMonth,  
							systemTime.wDay,  
								systemTime.wHour,  
									systemTime.wMinute,  
										systemTime.wSecond  );

		 char  buf1[MAX_PATH];
		 myTChar2Utf8(  pathBuf,  buf1,  mycountof(  buf1  )  );
	 	 displayChkDiskEvent(  pSubThreadInfo,  CONST_qyEventType_secChk_diskFile,  buf,  "",  buf1,  "",  ""  );
	 	 traceLogA(  "就是一个文件拉：%s",  pathBuf  );
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;		//  这里必须返回0，否则处理一个文件出错后，就不再继续
}

 
 int  chkNormalDiskDrvFile(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	int						iErr				=	-1;
	MT_SUBTHREADINFO	*	pSubThreadInfo		=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_REG_TOOL			*	pRegTool			=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	CHK_DISK_STRUCT			disks;
	int						i;
	TCHAR					drvName[32];

	if  (  pRegTool->cfg.ucbSecChkQuickly  )  {
		traceLogA(  "快速安检时，不检查普通磁盘文件"  ); 
		iErr  =  0;  goto  errLabel;
	}
	
	memset(  &disks,  0,  sizeof(  disks  )  );
	if  (  getDiskDrvInfo(  &disks  )  )  goto  errLabel;

	for  (  i = 0;  i <  disks.iDiskNum;  i ++  )  {
		 _snprintf(  disks.curDrvName,  sizeof(  disks.curDrvName  ),  "%c",  disks.diskDrvs[i].ucVolName  );
		 _sntprintf(  drvName,  mycountof(  drvName  ),  _T(  "%c:"  ),  disks.diskDrvs[i].ucVolName  );
		 if  (  qwmEnumUsrDir(  &pRegTool->env,  drvName,  (  PF_commonHandler  )myChkProc,  pSubThreadInfo,  drvName  )  )  goto  errLabel;
	}
	

	iErr  =  0;
errLabel:

	return  iErr;
}
