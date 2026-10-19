
#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<tchar.h>
#include	<iphlpapi.h>
#include	"qyCommon.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"

#if  0
 extern  "C"  char  *  getDelSelfSym(  )
{
	 return  CONST_qnmSym_delSelf;
}
#endif


   int  delSelf(  )
{
	 int					iErr									=  -1;
	 TCHAR					origPath[CONST_qyMaxPathLen  +  1];
	 TCHAR					clonePath[CONST_qyMaxPathLen  +  1];
	 HANDLE					hFile									=	NULL;
	 TCHAR					cmdLine[2048]							=	_T(  ""  );
	 STARTUPINFO			si;
	 PROCESS_INFORMATION	pi;
	 BOOL					bProcessCreated							=	FALSE;

	 traceLogA(  "delSelf enters,  自删除程序"  );

	 memset(  &si,  0,  sizeof(  si  )  );
	 memset(  &pi,  0,  sizeof(  pi  )  );

	 GetModuleFileName(  NULL,  origPath,  mycountof(  origPath  )  );
	 GetTempPath(  mycountof(  clonePath  ),  clonePath  );
	 GetTempFileName(  clonePath,  _T(  "del"  ),  0,  clonePath  );
	 if  (  !CopyFile(  origPath,  clonePath,  FALSE  )  )  {
		 traceLogA(  "CopyFile %s to %s failed",  origPath,  clonePath  );
		 goto  errLabel;
	 }

	 hFile  =  CreateFile(  clonePath,  0,  FILE_SHARE_READ,  NULL,  OPEN_EXISTING,  FILE_FLAG_DELETE_ON_CLOSE,  NULL  );
	 
	 _sntprintf(  cmdLine,  mycountof(  cmdLine  ),  _T(  "\"%s\" %s \"%s\""  ),  clonePath,  CONST_qnmSym_delSelf,  origPath  );
	 
	 si.cb  =  sizeof(  si  );
	 if  (  !CreateProcess(  NULL,  cmdLine,  NULL,  NULL,  TRUE,  0,  NULL,  NULL,  &si,  &pi  )  )  {
		 traceLogA(  "运行%s失败",  cmdLine  );
		 goto  errLabel;
	 }
	 bProcessCreated  =  TRUE;
	 traceLogA(  "运行成功, %s",  cmdLine  );

	 Sleep(  1000  );
	 traceLogA(  "这里等待一秒种，以让操作系统有充足的时间来启动上述进程"  );

	 iErr  =   0;

errLabel:

	 if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  CloseHandle(  pi.hThread  );
		 if  (  pi.hProcess  )  CloseHandle(  pi.hProcess  );
	 }
	 if  (  isHandleValid(  hFile  )  )  CloseHandle(  hFile  );  


	 traceLogA(  "delSelf leaves"  );

	 return  iErr;
}


  int  procDelSelf(  TCHAR  *  fileToDelParam  )
{
	  int		i;
	  int		fileToDelSize							=	0;
	  int		myFileSize								=	0;
	  TCHAR		fileName[CONST_qyMaxPathLen  +  1]		=	_T(  ""  );
	  TCHAR		fileToDel[CONST_qyMaxPathLen  +  1]		=	_T(  ""  );

	  traceLogA(  "procDelSel enters"  );

	  lstrcpyn(  fileToDelParam,  fileToDel,  mycountof(  fileToDel  )  );
	  tTrim(  fileToDel  );
	  if  (  fileToDel[lstrlen(  fileToDel  )  -  1]  =  '\"'  )  fileToDel[  lstrlen(  fileToDel  )  -  1]  =  ' ';
	  if  (  fileToDel[0]  ==  '\"'  )  fileToDel[0]  =  ' ';
	  tTrim(  fileToDel  );
	  fileToDelSize  =  qyGetFileSize(  fileToDel  );
	  GetModuleFileName(  NULL,  fileName,  mycountof(  fileName  )  );
	  myFileSize  =  qyGetFileSize(  fileName  );
	  
	  traceLogA(  "myFileSize is %d, and fileToDelSize  is %d",  myFileSize,  fileToDelSize  );
	  if  (  !myFileSize  ||  myFileSize  !=  fileToDelSize  )  {
		  traceLogA(  "文件大小校验不对"  );  goto  errLabel;
	  }

	  Sleep(  2000  );
	  for  (  i  =  0;  i  <  10;  i  ++  )  {
		   if  (  DeleteFile(  fileToDel  )  )  break;
		   Sleep(  1000  );
	  }

	  traceLogA(  "删除 %s 共%d次，%s",  fileToDel,  i,  (  i  ==  10  )  ?  "失败"  :  "成功"  );
	
errLabel:
	  	  
	  traceLogA(  "procDelSel leaves"  );
	  return  0;
}

 int  doMyCapture(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr							=	-1;
	 STARTUPINFO			si;
	 PROCESS_INFORMATION	pi;
	 TCHAR					buf[CONST_qyMaxPathLen  +  1];
	 BOOL					bProcessCreated					=	FALSE;

	 memset(  &pi,  0,  sizeof(  pi  )  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	 si.cb  =  sizeof(  STARTUPINFO  );
	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	
	 getModuleDirAndFinalName(  buf,  mycountof(  buf  ),  NULL,  0  );
	 trailDir(  buf,  mycountof(  buf  )  );
	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%s"  ),  buf,  _T(  "myCapture.exe"  )  );
	 if  (  qyQuoteFileName(  buf,  mycountof(  buf  )  )  )  goto  errLabel;
	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %s"  ),  buf,  _T(  "9876543210"  )  );
	 if  (  !CreateProcess(  NULL,  buf,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
	 bProcessCreated  =  TRUE;

	 iErr  =  0;

errLabel:
	
	 if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }
	 return  iErr;

}


