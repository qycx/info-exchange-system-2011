
#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"osAuditProc.h"
#include	<time.h>

 int  ReadLog(  QY_ENV  *  pEnv,  void  *  pEventLogInfoParam,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  );

QY_DMITEM		CONST_srcTypeName[]	=
{
	{	0,		_T(  "System"  ),			},
	{	0,		_T(  "Application"  ),		},
	{	0,		_T(  "Security"  ),			},
	{	-1,										},

};

/*
#define		CONST_srcTypeName_system		"System"
#define		CONST_srcTypeName_application	"Application"
#define		CONST_srcTypeName_sec			"Security"
*/


 int  tmpHandler_eventLog(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr			=	-1;
	 COMMON_PARAM			*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	 QWM_THREADINFO			*	pThreadInfo		=	(  QWM_THREADINFO  *  )pCommonParam->p0;
	 QY_W_MON				*	pQwm			=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_SESSION			*	pSession		=	(  QWM_SESSION  *  )pCommonParam->p1;
	 QY_SOCK				*	pSock			=	(  QY_SOCK  *  )pCommonParam->p2;
	 QWM_EVENTLOG_PROCINFO	*	pProcInfo		=	(  QWM_EVENTLOG_PROCINFO  *  )p1;
	 QY_EVENTLOG_PROP		*	pEventLog		=	(  QY_EVENTLOG_PROP  *  )p2;
	 unsigned  int				len;
	 QY_COMM_RESP				tmpResp;
	 char						buf[1024];


	 //  printEventLogProp(  pEventLog  );
	 if  (  pProcInfo->pcCommU.head.cnt  >=  sizeof(  pProcInfo->pcCommU.eventLogsInfo.mems  )  /  sizeof(  pProcInfo->pcCommU.eventLogsInfo.mems[0]  )  )  {
		 traceLogA(  "tmpHandler_eventLog: 出现了编程错误"  );  goto  errLabel;
	 }
	 memcpy(  &pProcInfo->pcCommU.eventLogsInfo.mems[pProcInfo->pcCommU.eventLogsInfo.cnt],  pEventLog,  sizeof(  QY_EVENTLOG_PROP  )  );
	 pProcInfo->pcCommU.eventLogsInfo.cnt  ++  ;

	 if  (  pProcInfo->pcCommU.eventLogsInfo.cnt  ==  sizeof(  pProcInfo->pcCommU.eventLogsInfo.mems  )  /  sizeof(  pProcInfo->pcCommU.eventLogsInfo.mems[0]  )  )  {
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pProcInfo->pcCommU  )  )  ==  -1  )  goto  errLabel;
		 if  (  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndEventLog,  (  char  *  )&pProcInfo->pcCommU,  len  )  )  goto  errLabel;
		 if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

		 //  这里开始复位
		 memset(  &pProcInfo->pcCommU,  0,  sizeof(  pProcInfo->pcCommU  )  );
		 MACRO_makePcCommHead(  CONST_pcCommType_eventLog,  pQwm,  pProcInfo->pcCommU  );
		 
	 }
	 iErr  =  0;

errLabel:

	 if  (  iErr  )  pProcInfo->ucbErr  =  TRUE;
	 return  iErr  ?  CONST_qyRet_quit  :  0;

}

 int  sndEventLog(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int							iErr				=	-1;
	 QY_W_MON					*	pQwm				=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_EVENTLOG_PROCINFO			eventLogProcInfo;
	 COMMON_PARAM					commonParam;
	 QWM_SESSION					session;
	 QY_SOCK						sock;
	 BOOL							bSessionOpen		=	FALSE;
	 QY_COMM_RESP					tmpResp;
	 char							buf[1024];
	 int							len;
	 QY_DMITEM					*	pItem				=	CONST_srcTypeName;

	 if  (  !g_bIsWinNT  )  return  0;
	 traceLogA(  "sndEventLog enters"  );

	 for  (  ;  pItem->type  !=  -1;  pItem  ++  )  {
		  memset(  &session,  0,  sizeof(  session  )  );
		  clearQySock(  &sock  );

		  memset(  &eventLogProcInfo,  0,  sizeof(  eventLogProcInfo  )  );
		  _sntprintf(  eventLogProcInfo.sourceTypeName,  mycountof(  eventLogProcInfo.sourceTypeName  ),  _T(  "%s"  ),  pItem->des  );
		  MACRO_makePcCommHead(  CONST_pcCommType_eventLog,  pQwm,  eventLogProcInfo.pcCommU  );
	 

		  if  (  !bSessionOpen  )  {
			  if  (  qwmOpenSession(  pThreadInfo->pParaentParam,  &session,  &sock  )  )  goto  errLabel;
			  bSessionOpen  =  TRUE;
		  }
	 
		  MACRO_makeCommonParam3(  pThreadInfo,  &session,  &sock,  commonParam  );
	 	  ReadLog(  &pQwm->env,  &eventLogProcInfo,  tmpHandler_eventLog,  &commonParam,  &eventLogProcInfo  );
		  if  (  eventLogProcInfo.ucbErr  )  {
			  if  (  bSessionOpen  )  qwmCloseSession(  pThreadInfo->pParaentParam,  &session,  &sock  );
			  bSessionOpen  =  FALSE;
			  continue;
		  }


		  //  在tmpHandler_eventLog中没发送完的在这里发送
	 		  traceLogA(  "发送剩下的%d条事件",  eventLogProcInfo.pcCommU.head.cnt  );
	 		  if  (  (  len  =  qyhtonQyPcCommU(  0,  &eventLogProcInfo.pcCommU  )  )  ==  -1  )  goto  errLabel;
	 		  if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndEventLog,  (  char  *  )&eventLogProcInfo.pcCommU,  len  )  )  goto  errLabel;
	 		  if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

			  if  (  bSessionOpen  )  qwmCloseSession(  pThreadInfo->pParaentParam,  &session,  &sock  );
			  bSessionOpen  =  FALSE;

	 }



	 iErr  =  0;

errLabel:


	 traceLogA(  "sndEventLog leaves"  );
	 return  iErr;
}

 char  **  GetArgs(  const  EVENTLOGRECORD  *  pBuf  )
{
	char	*	cp;
	WORD		ArgCount;
	char	**	Args		=	NULL;

	if  (  pBuf->NumStrings  ==  0  )  return  NULL;

	Args  =  (  char  **  )GlobalAlloc(  GMEM_FIXED,  sizeof(  char  *  )  *  pBuf->NumStrings  );
	cp  =  (  char  *  )pBuf  +  (  pBuf->StringOffset  );

	for  (  ArgCount  =  0;  ArgCount  <  pBuf->NumStrings;  ArgCount  ++  )  {
		 Args[ArgCount]  =  cp;
		 cp  +=  strlen(  cp  )  +  1;
	}
	return  Args;
}

 BOOL  GetModuleNameFromSourceName(  TCHAR  *  srcTypeName,  const  TCHAR  *  SourceName,  const  char  *  EntryName,  TCHAR  *  ExpandedName,  unsigned  int  uiExpandedNameSize  )
{
	DWORD		lResult;
	DWORD		ModuleNameSize;
	TCHAR		ModuleName[1000];
	HKEY		hAppKey				=	NULL;
	HKEY		hSourceKey			=	NULL;
	BOOL		bReturn				=	FALSE;

	_sntprintf(  ModuleName,  mycountof(  ModuleName  ),  _T(  "SYSTEM\\CurrentControlSet\\Services\\EventLog\\%s"  ),  srcTypeName  );
	lResult  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  ModuleName,  0,  KEY_READ,  &hAppKey  );
	if  (  lResult  !=  ERROR_SUCCESS  )  goto  Exit;
	
	lResult = RegOpenKeyEx(  hAppKey,  SourceName,  0,  KEY_READ,  &hSourceKey  );
	if  (  lResult  !=  ERROR_SUCCESS  )  goto  Exit;

	ModuleNameSize  =  sizeof(  ModuleName  );
	lResult  =  RegQueryValueEx(  hSourceKey,  _T(  "EventMessageFile"  ),  NULL,  NULL,  (  unsigned  char  *  )ModuleName,  &ModuleNameSize  );
	if  (  lResult  !=  ERROR_SUCCESS  )  goto  Exit;

	ExpandEnvironmentStrings(  ModuleName,  ExpandedName, uiExpandedNameSize  );
	
	bReturn = TRUE;

Exit: 
	if  (  hSourceKey  !=  NULL  )  RegCloseKey(  hSourceKey  );
	if  (  hAppKey  !=  NULL  )  RegCloseKey(  hAppKey  );

	return  bReturn;
}


 BOOL  bDispMessage(  TCHAR  *  srcTypeName,  const  TCHAR  *  SourceName,  const  char  *  EntryName,  const  char  **  Args,  DWORD  MessageId,  TCHAR  *  descBuf,  unsigned  int  descBufSize  )
{
	BOOL		bResult;
	BOOL		bReturn					=	FALSE;
	HANDLE		hSourceModule			=	NULL;
	TCHAR		SourceModuleName[1000];
	TCHAR	*	pMessage				=	NULL;

	bResult  =  GetModuleNameFromSourceName(  srcTypeName,  SourceName,  EntryName,  SourceModuleName,  mycountof(  SourceModuleName  )  );
	if  (  !bResult  )  goto  Exit;

	hSourceModule  =  LoadLibraryEx(  SourceModuleName,  NULL,  DONT_RESOLVE_DLL_REFERENCES | LOAD_LIBRARY_AS_DATAFILE  );
	if  (  hSourceModule  ==  NULL  )  goto  Exit;

	FormatMessage(  FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ARGUMENT_ARRAY,
					hSourceModule,
					MessageId,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPWSTR)&pMessage,
					0,
					(va_list *)Args  );

	if  (  descBuf  )  _sntprintf(  descBuf,  descBufSize,  _T(  "%s"  ),  pMessage  ?  pMessage  :  _T(  ""  )  );

	bReturn  =  TRUE;

Exit: 

	if  (  pMessage  !=  NULL  )  printf(  "%s",  pMessage  );
	else  printf(  "(%d)\n",  MessageId  );
	
	if  (  hSourceModule  ) FreeLibrary(  (  HMODULE  )hSourceModule  );
	if  (  pMessage  )  LocalFree(  pMessage  );

	return  bReturn;
}



 char  *  getTimeByl(  time_t  l,  char  *  timeBuf,  unsigned  int  size  )
{
	 struct  tm	*	pTm	=	NULL;
	 if  (  !timeBuf  ||  size  <  CONST_qyTimeLen  )  return  NULL;
	 if  (  !(  pTm  =  localtime(  &l  )  )  )  return  NULL;
	 _snprintf(  timeBuf,  size,  "%04d%02d%02d%02d%02d%02d",  pTm->tm_year  +  1900,  pTm->tm_mon  +  1,  pTm->tm_mday,  pTm->tm_hour,  pTm->tm_min,  pTm->tm_sec  );
	 return  timeBuf;
}

 int  ReadLog(  QY_ENV  *  pEnv,  void  *  pEventLogInfoParam,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
	int							iErr			=	-1;
	QWM_EVENTLOG_PROCINFO	*	pEventLogInfo	=	(  QWM_EVENTLOG_PROCINFO  *  )pEventLogInfoParam;	
	DWORD						BufSize;
	DWORD						ReadBytes;
	DWORD						NextSize;
	BOOL						bResult;
	//  DWORD					i;
	char					*	cp;
	TCHAR					*	pSourceName		=	NULL;
	TCHAR					*	pComputerName	=	NULL;
	HANDLE						hEventLog		=	NULL;
	EVENTLOGRECORD			*	pBuf			=	NULL;
	char					**	Args			=	NULL;
	TCHAR						buf[1024];
	QY_EVENTLOG_PROP			eventLog;
	QWM_DYN_LIB				*	pDynLib			=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !(  hEventLog  =  pDynLib->pOpenEventLog(  NULL,  pEventLogInfo->sourceTypeName  )  )  )  {
		traceLogA(  "event log can not open.\n"  );  goto  errLabel;
	}

	for  (  ;  ;  )  {
		 /* 僀儀儞僩儘僌偺僒僀僘庢摼 */
		 BufSize  =  1;
		 if  (  !(  pBuf = (  EVENTLOGRECORD  *  )GlobalAlloc(  GMEM_FIXED,  BufSize  )  )  )  goto  errLabel;
		 bResult  =  pDynLib->pReadEventLog(  hEventLog,
									EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
									0,
									pBuf,
									BufSize,
									&ReadBytes,
									&NextSize  );

		if  (  !bResult  &&  GetLastError()  !=  ERROR_INSUFFICIENT_BUFFER  )  break;
		GlobalFree(  pBuf  );  pBuf = NULL;

		/* 僶僢僼傽妱傝摉偰 */
		BufSize  =  NextSize;
		if  (  !(  pBuf = (  EVENTLOGRECORD  *  )GlobalAlloc(  GMEM_FIXED,  BufSize  )  )  )  goto  errLabel;

		/* 僀儀儞僩儘僌偺撉傒庢傝 */
		bResult  =  pDynLib->pReadEventLog(  hEventLog,
									EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
									0,
									pBuf,
									BufSize,
									&ReadBytes,
									&NextSize);
		if  (  !bResult  )  break;

		memset(  &eventLog,  0,  sizeof(  eventLog  )  );
		eventLog.dwRecordNumber  =  pBuf->RecordNumber;
		//  traceLogA(  "TimeGenerated: %s",  ctime(  (  const  long  *  )&pBuf->TimeGenerated  )  );
		//  traceLogA(  "TimeWritten: %s",  ctime(  (  const  long  *  )&pBuf->TimeWritten  )  );
		//  traceLogA(  "EventID: %d\n",  pBuf->EventID  &  0xffff  );
		//  traceLogA(  "类型: %s",  qyGetDesByType1(  CONST_eventLogTypeTable,  pBuf->EventType  )  );
		getTimeByl(  pBuf->TimeGenerated,  eventLog.timeGeneratedBuf,  sizeof(  eventLog.timeGeneratedBuf  )  );
		eventLog.dwEventID  =  pBuf->EventID;
		eventLog.wEventType  =  pBuf->EventType;
		
		cp  =  (  char  *  )pBuf;
		cp  +=  sizeof(  EVENTLOGRECORD  );

		pSourceName  =  (  TCHAR  *  )cp;
		cp  +=  (  lstrlen(  pSourceName  )  +  1  )  *  sizeof(  TCHAR  );

		pComputerName  =  (  TCHAR  *  )cp;
		cp  +=  (  lstrlen(  pComputerName  )  +  1  )  *  sizeof(  TCHAR  );

		#if  0
			 traceLog(  _T(  "SourceName: %s"  ),  pSourceName  );
			 traceLog(  _T(  "ComputerName: %s"  ),  pComputerName  );
		#endif
		//  _snprintf(  eventLog.sourceName,  sizeof(  eventLog.sourceName  ),  "%s",  pSourceName  );
		//  _snprintf(  eventLog.computerName,  sizeof(  eventLog.computerName  ),  "%s",  pComputerName  );
		myTChar2Utf8(  pSourceName,  eventLog.sourceName,  mycountof(  eventLog.sourceName  )  );
		myTChar2Utf8(  pComputerName,  eventLog.computerName,  mycountof(  eventLog.computerName  )  );

		//  traceLogA(  "EventCategory: %d",  pBuf->EventCategory  );
		if  (  !bDispMessage(  pEventLogInfo->sourceTypeName,  pSourceName,  "CategoryMessageFile",  NULL,  pBuf->EventCategory,  buf,  mycountof(  buf  )  )  )  buf[0]  =  0;
		//  traceLogA(  "EventCategory描述 is %s",  buf  );
		eventLog.wEventCategory  =  pBuf->EventCategory;

		
		Args  =  GetArgs(  pBuf  );
		if  (  !bDispMessage(  pEventLogInfo->sourceTypeName,  pSourceName,  "EventMessageFile", (  const  char  **  )Args,  pBuf->EventID,  buf,  mycountof(  buf  )  )  )  buf[0]  =  0;
		if  (  Args  ) {  GlobalFree(  Args  );  Args = NULL;  }

		#if  0
			 traceLog(  _T(  ": %s"  ),  buf  );
		#endif
		//  _snprintf(  eventLog.eventLogDesc,  sizeof(  eventLog.eventLogDesc  ),  "%s",  buf  );
	    myTChar2Utf8(  buf,  eventLog.eventLogDesc,  mycountof(  eventLog.eventLogDesc  )  );

		/*
		if  (  pBuf->DataLength  >  0  )  {
			traceLogA(  "开始dump eventLog的数据: "  );
			for  (  i  =  0;  i  <  pBuf->DataLength;  i  ++  )  printf(  "%02x ", *(  (  (  unsigned  char  *  )pBuf  )  +  (  pBuf->DataOffset  )  +  i  )  );
			traceLogA(  "dump 结束"  );
		}
		*/

		/* 僶僢僼傽夝曻 */
		GlobalFree(  pBuf  );  pBuf = NULL;

		if  (  pf  &&  pf(  p0,  p1,  &eventLog  )  ==  CONST_qyRet_quit  )  goto  errLabel;

	}

	iErr  =  0;
errLabel:

	if  (  pBuf  )  GlobalFree(  pBuf  );
	if  (  Args  )  GlobalFree(  Args  );
	if  (  isHandleValid(  hEventLog  )  ) CloseEventLog(  hEventLog  );
	return  iErr;
}


