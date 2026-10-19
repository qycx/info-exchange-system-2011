

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

BOOL  bGetNh(  void  *  pSubThreadInfoParam,  char  *  ip  );

 int  chkShare(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 char		ip[CONST_qyMaxIpLen  +  1];

	 if  (  !getHostIp(  NULL,  ip  )  )  {
		 bGetNh(  pSubThreadInfoParam,  ip  );
	 }

	 return  0;
}
 
 LPVOID  MyAllocMem(  DWORD  cb  ) 
{	
	 return  HeapAlloc(  GetProcessHeap(  ),  HEAP_GENERATE_EXCEPTIONS  |  HEAP_ZERO_MEMORY,  cb  ); 
}
 
 BOOL  MyFreeMem(  LPVOID  pMem  ) 
{     
	 return  HeapFree(  GetProcessHeap(  ),  0,  pMem  ); 
}

 BOOL  bGetNh(  void  *  pSubThreadInfoParam,  char  *  ip  )
{
	BOOL						bRet				=	FALSE;
	MT_SUBTHREADINFO		*	pSubThreadInfo		=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_REG_TOOL				*	pRegTool			=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	NETRESOURCE					nr; 
	TCHAR						remoteNameBuf[1024];
	HANDLE						hWNetEnum  =  NULL; //列举的句柄，WNetEnumResource每调用一次，就移到下一个共享资源container
	BOOL						bWNetEnumOpen		=	FALSE;
	DWORD						dwStatus;
	QNM_WMBUF_SHOWSECCHKEVENT	wmBuf;
	QWM_DYN_LIB				*	pDynLib				=	(  QWM_DYN_LIB  *  )pRegTool->env.pDynLibs;


	traceLogA(  "bGetNh enters"  );

	_sntprintf(  remoteNameBuf,  mycountof(  remoteNameBuf  ),  _T(  "\\\\%S"  ),  ip  );
	
	nr.dwScope				=  RESOURCE_GLOBALNET; 
	nr.dwType				=  RESOURCETYPE_ANY; 
	//  nr.dwDisplayType	=  RESOURCEDISPLAYTYPE_SERVER; 
	nr.dwDisplayType		=  RESOURCEDISPLAYTYPE_SHARE;
	nr.dwUsage				=  RESOURCEUSAGE_CONTAINER; 
	nr.lpLocalName			=  NULL; 
	nr.lpRemoteName			=  remoteNameBuf; 
	nr.lpComment			=  NULL; 
	nr.lpProvider			=  NULL; 
	
	LPVOID  pMem  =  HeapAlloc(  GetProcessHeap(),  HEAP_GENERATE_EXCEPTIONS  |  HEAP_ZERO_MEMORY,  16384  ); 
	if  (  !pMem  )  {
		traceLogA(  "Not enough memory to allocate for WNetEnumResource"  );  goto  errLabel;
	} 

	dwStatus  =  pDynLib->pWNetOpenEnum(  RESOURCE_GLOBALNET,  RESOURCETYPE_ANY,  RESOURCEUSAGE_CONNECTABLE,  &nr,  &hWNetEnum  ); 
	if  (  dwStatus  !=  NO_ERROR  )  { 
		qyDisplayLastError(  "WNetOpenEnum failed"  );  goto  errLabel;		
	} 	
	bWNetEnumOpen  =  TRUE;

	do  { 
		DWORD  dwEntries;  DWORD  dwBuffSize; 
		
		dwEntries  =  1; //每次只处理一个共享资源container
		dwBuffSize  =  16384; 
		dwStatus  =  pDynLib->pWNetEnumResource(  hWNetEnum,  &dwEntries,  pMem,  &dwBuffSize  );  //  dwEntries个共享资源container以数组方式存放在pMem中
		if  (  dwStatus  ==  NO_ERROR  )  { 
			traceLogA(  "Resource name is [%s], %s", ((LPNETRESOURCE)pMem)->lpRemoteName,  ((LPNETRESOURCE)pMem)->dwType  ==  RESOURCETYPE_PRINT  ?  "打印机"  :  "共享资源"   );

			//  
			memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
			wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
			wmBuf.event.lEventType  =  ((LPNETRESOURCE)pMem)->dwType  ==  RESOURCETYPE_PRINT  ?  CONST_qyEventType_secChk_sharePrinter  :  CONST_qyEventType_secChk_shareDirectory;
			safeStrnCpy(  CONST_qyNullTime,  wmBuf.event.localEventTime,  sizeof(  wmBuf.event.localEventTime  )  );
			myTChar2Utf8(  ((LPNETRESOURCE)pMem)->lpRemoteName,  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  )  );
			if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  break;
			SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
			 

		} 
	}  while  (  dwStatus  ==  NO_ERROR  ); 
	if  (  dwStatus  !=  ERROR_NO_MORE_ITEMS  )  { 
		traceLogA( "WNetEnumResource failed" ); goto  errLabel;
	} 	
	
	bRet  =  TRUE;
errLabel:

	if  (  bWNetEnumOpen  )  pDynLib->pWNetCloseEnum(  hWNetEnum  );
	if  (  pMem  )  HeapFree(  GetProcessHeap(  ),  0,  pMem  ); 
		
	traceLogA(  "bGetNh leaves"  );

	return  bRet; 
} 





