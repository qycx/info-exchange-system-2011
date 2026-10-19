
#include	<windows.h>
#include	<tlhelp32.h>
#include	<ras.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
//  #include	<nt_pviewer.h>
#include	"showPcProcess.h"

/*
 int  tmpGetCmdLine(  QY_ENV  *  pEnv,  HANDLE  hProcess,  WCHAR  *  wzCmdLine,  unsigned  int  cmdLineCnt  )
{
	int					iErr						=		-1;
	HANDLE				hThread						=		NULL;
	WCHAR				wBuf[512]					=		L"";		
	unsigned  long		len							=		0;
	WCHAR			*	pW;
	unsigned  char		ucbCmdLineExists			=		FALSE;
	unsigned  char		ucbSymExists				=		FALSE;		//  指双引号是否存在
	QWM_DYN_LIB		*	pDynLib						=		(  QWM_DYN_LIB  *  )pEnv->pDynLib;
	DWORD				dwRet;

	hThread  =  pDynLib->pCreateRemoteThread(  hProcess,  0,  0,  (  LPTHREAD_START_ROUTINE  )pDynLib->pGetCommandLineW,  0,  0,  0  );
	if  (  !isHandleValid(  hThread  )  )  goto  errLabel;
	dwRet  =  WaitForSingleObject(  hThread,  3000  );	//  INFINITE,  2007/02/10，将永久等待改为限时等待，以防止死锁
	if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
	if  (  !GetExitCodeThread( hThread, (  DWORD  *  )&pW )  )  goto  errLabel;
	if  (  !ReadProcessMemory(  hProcess,  pW,  wBuf,  sizeof(  wBuf  ),  &len  )  )  goto  errLabel;
	if  (  len  !=  sizeof(  wBuf  )  )  goto  errLabel;
	wBuf[mycountof(  wBuf  )  -  1]  =  0;

	for  (  pW  =  wBuf;  *pW;  pW  ++  )  {	//  先把最前面的空格的拿去
		 if  (  !iswspace(  *pW  )  )  break;
	}
	if  (  !*pW  )  goto  errLabel;		//  这是异常，因为什么都没得到
	
	if  (  *pW  ==  L'"'  )  {
		ucbSymExists  =  TRUE;  pW  ++  ;  
	}
	if  (  !ucbSymExists  )  {
		for  (  ;  *pW  &&  !iswspace(  *pW  );  pW  ++  );		//  找第一个空格并将其置为0
		}
	else  {
		  for  (  ;  *pW  &&  *pW  !=  L'"';  pW  ++  );		//  找第2个双引号
		  if  (  *pW  ==  L'"'  )  pW  ++  ;					//  找到了
	}

	for  (  ;  *pW;  pW  ++  )  {	//  先把最前面的空格的拿去
		 if  (  !iswspace(  *pW  )  )  break;
	}
		  	  
	safeWcsnCpy(  *pW  ?  pW  :  L"",  wzCmdLine,  cmdLineCnt  );

	iErr  =  0;

errLabel:
	
	if  (  isHandleValid(  hThread  )  )  CloseHandle(  hThread  );

	return  iErr;
}
*/

 int  getProcessNameById(  QY_ENV  *  pEnv,  DWORD  processID,  WCHAR  *  wzProcessName,  unsigned  int  processNameCnt,  WCHAR  *  wzCmdLine,  unsigned  int  cmdLineCnt  )
{
	int					iErr						=		-1;
    HMODULE				hMod;
    DWORD				cbNeeded;
    HANDLE				hProcess					=		NULL;
	QWM_DYN_LIB		*	pDynLib						=		(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

    // Get a handle to the process.

	if  (  !pDynLib->pEnumProcessModules  
		||  !pDynLib->pGetModuleFileNameExW  
			||  !pDynLib->pCreateRemoteThread
				||  !pDynLib->pGetCommandLineW  )  
	{
		goto  errLabel;
	}
	
	//  hProcess  =  OpenProcess(  PROCESS_CREATE_THREAD  |  PROCESS_VM_OPERATION  |  PROCESS_QUERY_INFORMATION  |  PROCESS_VM_READ,  FALSE,  processID  );
	hProcess  =  OpenProcess(  PROCESS_QUERY_INFORMATION  |  PROCESS_VM_READ,  FALSE,  processID  );
	if (  !hProcess )  goto  errLabel;
    		
    if  (  !pDynLib->pEnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )  goto  errLabel;
	if  (  !pDynLib->pGetModuleFileNameExW(  hProcess,  hMod,  wzProcessName,  processNameCnt  )  )  goto  errLabel;
	
	//  if  (  tmpGetCmdLine(  pEnv,  hProcess,  wzCmdLine,  cmdLineCnt  )  )  safeWcsnCpy(  L"",  wzCmdLine,  cmdLineCnt  );
    safeWcsnCpy(  L"",  wzCmdLine,  cmdLineCnt  );

	iErr  =  0;
errLabel:
	
	if  (  hProcess  )  CloseHandle(  hProcess  );
	
	return  iErr;

}

		
 myPROCESSINFO  *  CreateProcListSnapshot(  QY_ENV  *  pEnv,  char  *  svName  )
{
	int						iErr		=	-1;
	HANDLE					hSnap		=	NULL;
	myPROCESSINFO		*	pProcCur	=	NULL;
	myTHREADINFO		*	pThreadCur	=	NULL;
	myPROCESSINFO			phd;
	PROCESSENTRY32			pe;
	THREADENTRY32			te;
	char				*	p			=	NULL;
	QWM_DYN_LIB			*	pDynLib		=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !pDynLib->pCreateToolhelp32Snapshot  )  return  NULL;

	memset(  &phd,  0,  sizeof(  phd  )  );

	if  (  svName  !=  NULL  )  {
		if  (  svName[0]  ==  '\0'  )  svName  =  NULL;
	}
	

	/*
	if  (  iPlatformId  ==  CONST_qyPlatform_winnt  )  {
		traceLogA(  "Nt的工作不支持CreateToolhelp32Snapshot"  );  goto  errLabel;
    }	
	*/
	{

		// Create Toolhelp Snapshot
		hSnap  =  pDynLib->pCreateToolhelp32Snapshot(  TH32CS_SNAPPROCESS  |  TH32CS_SNAPTHREAD,  0  );
		if  (  hSnap  ==  INVALID_HANDLE_VALUE  )  return  NULL;

		phd.next  =  NULL;

		// -------------------------- Get Process Information
		pe.dwSize  =  sizeof(  PROCESSENTRY32  );
		pDynLib->pProcess32First(  hSnap,  &pe  );
		pProcCur  =  &phd;
		do  {
			// Insert process into process list
			if  (  !(  pProcCur->next  =  (  myPROCESSINFO  *  )malloc(  sizeof(  myPROCESSINFO  )  )  )  )  goto  errLabel;
			memset(  pProcCur->next,  0,  sizeof(  myPROCESSINFO  )  );
			pProcCur  =  pProcCur->next;


			// Fill in information
			pProcCur->dwProcID  =  pe.th32ProcessID;  
			{
				WCHAR	wProcessName[MAX_PATH  +  1]	=	L"";
				WCHAR	wCmdLine[256]					=	L"";
				if  (  getProcessNameById(  pEnv,  pProcCur->dwProcID,  wProcessName,  mycountof(  wProcessName  ),  wCmdLine,  mycountof(  wCmdLine  )  )  )  {
					lstrcpyn(  pProcCur->svApp,  pe.szExeFile,  sizeof(  pProcCur->svApp  )  );
					pProcCur->cmdLine[0]  =  0;
					}
				else  {
					  myWChar2TChar(  wProcessName,  pProcCur->svApp,  mycountof(  pProcCur->svApp  )  );
					  myWChar2TChar(  wCmdLine,  pProcCur->cmdLine,  mycountof(  pProcCur->cmdLine  )  );
				}
			}
			//  char  *  dot;
			//  dot  =  strrchr(  pProcCur->svApp,  '.'  );
			//  if  (  dot  !=  NULL  ) *dot  =  '\0';

			pProcCur->pThread  =  NULL;
						
		}  while  (  pDynLib->pProcess32Next(  hSnap,  &pe  )  );

		pProcCur->next  =  NULL;

		// -------------------------- Get Thread Information
		te.dwSize  =  sizeof(  THREADENTRY32  );
		pDynLib->pThread32First(  hSnap,  &te  );
		do  {
			// Find process that owns this thread
			pProcCur  =  phd.next;
			while  (  pProcCur  !=  NULL  )  {
				   if  (  pProcCur->dwProcID  ==  te.th32OwnerProcessID  )  break;
				   pProcCur  =  pProcCur->next;
			}
			if  (  pProcCur  !=  NULL  )  {
				// Add thread to thread list
				if  (  !(  pThreadCur  =  (  myTHREADINFO  *  )malloc(  sizeof(  myTHREADINFO  )  )  )  )  goto  errLabel;
				memset(  pThreadCur,  0,  sizeof(  myTHREADINFO  )  );
				pThreadCur->next  =  pProcCur->pThread;
				pProcCur->pThread  =  pThreadCur;

				// Fill in information
				pThreadCur->dwThreadID  =  te.th32ThreadID;
			}
		}  while  (  pDynLib->pThread32Next(  hSnap,  &te  )  );

	}

	iErr  =  0;

errLabel:

	if  (  isHandleValid(  hSnap  )  )  CloseHandle(  hSnap  );
	if  (  iErr  )  DestroyProcListSnapshot(  pEnv,  phd.next  );

	return  iErr  ?  NULL  :  phd.next;
}


 void  DestroyProcListSnapshot(  QY_ENV  *  pEnv,  myPROCESSINFO  *  pSS  )
{
	myPROCESSINFO  *  pi,  *  ptmp;
	myTHREADINFO  *  ti,  *  ttmp;

	pi  =  pSS;
	while  (  pi  !=  NULL  )  {
		   ti  =  pi->pThread;
		   while  (  ti  !=  NULL  ) {
				  ttmp  =  ti->next;
				  free(  ti  );
				  ti  =  ttmp;
		   }
		   ptmp  =  pi->next;
		   free(  pi  );
		   pi  =  ptmp;
	}
}
