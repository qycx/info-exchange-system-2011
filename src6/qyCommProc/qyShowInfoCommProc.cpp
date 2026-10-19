
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdlib.h>
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"
#include	"tmpCeLib.h"




static  struct						{
				BOOL				bInited;
				//
				TCHAR				errHintWndCls[512];
				PF_qyShowInfo0		errHintPf;
				//
				DWORD				dwThreadId;
				HANDLE				hThread;
				BOOL				bQuit;
				//
				BOOL				bShowMore;
				//
				TCHAR				mutexName_syncQ[32];
				//
				BOOL				bUsePipe;			//  2012/02/03
				//
				BOOL				bQInited;
				//
				RW_lock_param		rwLockParam;		//  2009/05/14
	 
				//  GENERIC_Q		q;
				QY_Q2				q2;
				//
}		sShowInfoStruct  =	{		FALSE,
									//
									_T(  ""  ),
									NULL,
									//
									0,
									NULL,
									FALSE,
									//
									FALSE,
									//
									_T(  "syncQ_showInfo"  ),
									//
									FALSE,	
									//
									FALSE,
									
							};


  
 extern  "C"  int  setErrHintWndCls(  LPCTSTR  title  )
{
	 if  (  lstrlen(  title  )  >=  mycountof(  sShowInfoStruct.errHintWndCls  )  )  return  -1;

	 lstrcpyn(  sShowInfoStruct.errHintWndCls,  title,  mycountof(  sShowInfoStruct.errHintWndCls  )  );
	 return  0;
}


 extern  "C"  int  setErrHintPf(  PF_qyShowInfo0  pf  )
{
	 sShowInfoStruct.errHintPf  =  pf;

	 return  0;
}

 extern  "C"  int  setShowMoreOn(  BOOL  bShowMore  )
{
	 sShowInfoStruct.bShowMore  =  bShowMore;

	 return  0;
}

 extern  "C"  int  bShowMore(  )
{
	 return  sShowInfoStruct.bShowMore;
}

  extern  "C"  void  exitShowInfo(  void  *  p0  )
{
	 CQySyncObj		syncObj;
	 
	 sShowInfoStruct.bQuit  =  TRUE;
	 MACRO_qyNullThread(  sShowInfoStruct.hThread  );

	 if  (  sShowInfoStruct.bQInited  )  {
		 exitQyQ2(  &sShowInfoStruct.q2  );  sShowInfoStruct.bQInited  =  FALSE;
	 }

	 sShowInfoStruct.bInited  =  FALSE;
}

 DWORD  WINAPI  showInfoThreadProc(  LPVOID  lpParameter  );

 extern  "C"  int  initShowInfo(  void  *  p0,  LPCTSTR  mutexName_syncQ,  LPCTSTR  errHintWndCls,  BOOL  bUsePipe  )
{
	 int	iErr  =  -1;
	 DWORD	dwThreadDaemonId;

	 if  (  sShowInfoStruct.bInited  )  return  -1;
	 //
	 if  (  !mutexName_syncQ  ||  !mutexName_syncQ[0]  )  return  -1;
	 if  (  !errHintWndCls  ||  !errHintWndCls[0]  )  return  -1;

	 lstrcpyn(  sShowInfoStruct.mutexName_syncQ,  mutexName_syncQ,  mycountof(  sShowInfoStruct.mutexName_syncQ  )  );
	 if  (  setErrHintWndCls(  errHintWndCls  )  )  goto  errLabel;
	 sShowInfoStruct.bUsePipe  =  bUsePipe;

	 //
	 GENERIC_Q_CFG	qCfg;
	 memset(  &qCfg,  0,  sizeof(  qCfg  )  );
	 _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "%s"  ),  _T(  "showInfoQ"  )  );
	 _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "%s"  ),  sShowInfoStruct.mutexName_syncQ  );
	 //  qCfg.uiMaxCnt_semaTrigger  =  CONST_maxCnt_sema_showInfoQ_is;
	 qCfg.uiMaxQNodes  =  CONST_uiMaxQNodes_showInfoQ_is;

	 //  memset(  &rwLockParam,  0,  sizeof(  rwLockParam  )  );
	 sShowInfoStruct.rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;
	 sShowInfoStruct.rwLockParam.uiInitCnt_sema			=	sShowInfoStruct.rwLockParam.uiMaxCnt_sema  -  1;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_sema_r	=	10000;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_mutex_w	=	10000;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_sema_w	=	10000;



	 //  if  (  initGenericQ(  _T(  "showInfoQ"  ),  sShowInfoStruct.mutexName_syncQ,  CONST_maxCnt_sema_showInfoQ_is,  CONST_uiMaxQNodes_showInfoQ_is,  malloc,  free,  &sShowInfoStruct.q  )  )  goto  errLabel;
	 if  (  initQyQ2(  &qCfg,  &sShowInfoStruct.rwLockParam,  1,  NULL,  mallocMemory,  malloc,  0,  0,  freeMemory,  free,  NULL,  &sShowInfoStruct.q2  )  )  goto  errLabel;
	 sShowInfoStruct.bQInited  =  TRUE;

	 sShowInfoStruct.hThread  =  CreateThread(  NULL,  0,  showInfoThreadProc,  (  LPVOID  )0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !sShowInfoStruct.hThread  )  goto  errLabel;
	 sShowInfoStruct.dwThreadId  =  dwThreadDaemonId;	//  2007/03/29, 为了引入这个标记，以便mtCliSockThreadProc能够在pMtSock里找到存放的物理位置，故要先挂起一下，然后再恢复
	 if  (  ResumeThread(  sShowInfoStruct.hThread  )  ==  -1  )  goto  errLabel;
 
	 sShowInfoStruct.bInited  =  TRUE;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {

		 exitShowInfo(  p0  );
		 
	 }

	 return  iErr;
}


 DWORD  WINAPI  showInfoThreadProc(  LPVOID  lpParameter  )
{
	 DWORD				dwRet;
	 QY_SHOW_STRUCT		showStruct;
	 unsigned  int		len;
	 HWND				firstWnd			=		NULL;
	 BOOL				bUsePipe			=		sShowInfoStruct.bUsePipe;
	 HANDLE				hPipe				=		NULL;
	 LPTSTR				lpszPipename		=		CONST_statusPipeName;
	 BOOL				fSuccess			=		FALSE; 
	 DWORD				cbRead  =  0, cbWritten  =  0, dwMode  =  0; 

	 GENERIC_Q		*	pShowInfoQ			=		NULL;
	 
	 traceLogA(  "showInfoThreadProc starts"  );
	 
	 while  (  !sShowInfoStruct.bQuit  )  {

		   //  2006/06/03
		   dwRet  =  WaitForSingleObject(  sShowInfoStruct.q2.hEvents[0],  5000  );
		   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		   //  超时也要接着处理，以getMsg为准
		   
		   for  (  ;  !sShowInfoStruct.bQuit;  )  {

			    q2AvoidTriggerTooHigh(  0,  &sShowInfoStruct.q2  );

			    len  =  sizeof(  showStruct  );
				if  (  !pShowInfoQ  ||  isQEmpty(  pShowInfoQ  )  )  {
					CQyQ2Help		q2Help;
					pShowInfoQ  =  q2Help.getQ_toGetMsg(  &sShowInfoStruct.q2  );
				}				
				if  (  qGetMsg(  pShowInfoQ,  &showStruct,  &len  )  )  break;
				
				if  (  bUsePipe  )  {

			#ifdef  __WINCE__
					traceLogA(  "pipe is not supported in ce"  );
			#else

					if  (  !isHandleValid(  hPipe  )  )  {
						hPipe = CreateFile( 
							lpszPipename,   // pipe name 
							GENERIC_READ |  // read and write access 
							GENERIC_WRITE, 
							0,              // no sharing 
							NULL,           // default security attributes
							OPEN_EXISTING,  // opens existing pipe 
							0,              // default attributes 
							NULL);          // no template file   
						if (  hPipe == INVALID_HANDLE_VALUE  )  continue; 
						
						traceLogA(  "showInfoThreadProc: pipe created"  );

						dwMode = PIPE_READMODE_MESSAGE; 
						fSuccess = SetNamedPipeHandleState( 
							hPipe,    // pipe handle 
							&dwMode,  // new pipe mode 
							NULL,     // don't set maximum bytes 
							NULL);    // don't set maximum time 
						if (!fSuccess)  {
							qyDisplayLastError(  "SetNamedPipeHandleState failed"  ); 
							CloseHandle(  hPipe  );  hPipe  =  NULL;
							continue;
						} 
					}

					fSuccess = WriteFile( 
						hPipe,                  // pipe handle 
						&showStruct,             // message 
						sizeof(  showStruct  ), // message length 
						&cbWritten,             // bytes written 
						NULL);                  // not overlapped 
					if  (  !fSuccess  )  {
						traceLogA("WriteFile failed"); 
						CloseHandle(  hPipe  );  hPipe  =  NULL;
						continue;
					}

			#endif

					continue;
				}

				if  (  sShowInfoStruct.errHintWndCls[0]  )  {

					if  (  !IsWindow(  firstWnd  )  )  {
						firstWnd  =  FindWindow(  sShowInfoStruct.errHintWndCls,  NULL  );
					}
					if  (  firstWnd  )  {
						COPYDATASTRUCT	tmpCopyData;
						LRESULT			lRet			=	0;
			
						tmpCopyData.lpData  =  &showStruct;
						tmpCopyData.cbData  =  sizeof(  showStruct  );
						lRet  =  SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );

						//  traceLogA(  "lRet is %d",  lRet  );
						//  OutputDebugString(  _T(  "kk\n"   )  );
					}

					//  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

				}
						   
		   
		   }
	
		   
	}
  
errLabel:

	if  (  isHandleValid(  hPipe  )  )  {
		CloseHandle(  hPipe  );  hPipe  =  NULL;
	}

	traceLogA(  "showInfoThreadProc ends"  );

	return  0;
}

 /*

*/


 extern  "C"  int  qyShowInfo(  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  )
{
#ifdef  __WINCE__
		return  0;
#endif

	va_list			args;
#ifndef  __WINCE__
	int				errnoBuf;
#endif
	HWND			firstWnd			=		NULL;
	QY_SHOW_STRUCT	showStruct;
	//  char			fileNameBuf[257];
	//  char			timeBuf[CONST_qyTimeLen  +  1];
	FILE		*	fperr				=		NULL;
	int				fileLen				=		0;
	
	
	#ifndef  __DEBUG__
			if  (  iShowType  ==  CONST_qyShowType_debug  )  return  0;
	#endif

#ifndef  __WINCE__
	errnoBuf  =  errno;
#endif

	va_start(  args,  fmt  );

	memset(  &showStruct,  0,  sizeof(  showStruct  )  );
	showStruct.iType  =  iShowType;
	if  (  clientIp  &&  clientIp[0]  )  showStruct.ulClientIp  =  inet_addr(  clientIp  );
	if  (  who_from  )  {
		_snwprintf(  showStruct.who_from,  mycountof(  showStruct.who_from  ),  L"%s",  who_from  );
	}
	if  (  who_to  )  {
		_snwprintf(  showStruct.who_to,  mycountof(  showStruct.who_to  ),  L"%s",  who_to  );
	}
	if  (  where  )  {
		_snwprintf(  showStruct.whereBuf,  mycountof(  showStruct.whereBuf  ),  L"%s",  where  );
	}
	//  when
	GetLocalTime(  &showStruct.when  );	//  2007/06/01
	if  (  puiStep  )  {				//  2008/04/28
		(  *puiStep  )  ++  ;
		showStruct.uiStep  =  *puiStep;
	}
	if  (  doStr  )  {
		_snwprintf(  showStruct.doStr,  mycountof(  showStruct.doStr  ),  L"%s",  doStr  );
	}
	_vsnwprintf(  showStruct.what,  mycountof(  showStruct.what  )  -  1,  fmt,  args  );  

	//  调用显示信息用的汇调函数
	if  (  sShowInfoStruct.errHintPf  )  sShowInfoStruct.errHintPf(  &showStruct,  0  );

	if  (  sShowInfoStruct.bInited  )  {
		if  (  !isQ2Warning(  &sShowInfoStruct.q2,  100  )  )  {		
			CQyQ2Help	q2Help;
			q2Help.qPostMsgAndTrigger(  &showStruct,  sizeof(  showStruct  ),  &sShowInfoStruct.q2  );
		}
		}
	else  {

		  if  (  sShowInfoStruct.errHintWndCls[0]  )  {

			  firstWnd  =  FindWindow(  sShowInfoStruct.errHintWndCls,  NULL  );
			  if  (  firstWnd  )  {
				  COPYDATASTRUCT	tmpCopyData;
			
				  tmpCopyData.lpData  =  &showStruct;
				  tmpCopyData.cbData  =  sizeof(  showStruct  );
				  SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
			  }

			  //  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

		  }
	}

	/*
	*/

	va_end(  args  );

#ifndef  __WINCE__
	errno  =  errnoBuf;
#endif

	return  0;
}


   extern  "C"  int  errLog(  char *  fmt,  ...  )
{		 
	va_list		args;
	//  char		filenamebuf[257];
	//  char		timebuf[50];
	FILE	*	fperr				=		NULL;
	int			fileLen				=		0;
#ifndef  __WINCE__
	int			errnoBuf;
#endif
	char		buf[256];
	HWND		firstWnd			=		NULL;

#ifndef  __WINCE__
	errnoBuf  =  errno;
#endif

	va_start(  args,  fmt  );

	_vsnprintf(  buf,  sizeof(  buf  )  -  1,  fmt,  args  );
	buf[sizeof(  buf  )  -  1]  =  0;

	if  (  sShowInfoStruct.errHintWndCls[0]  )  {
	
		firstWnd  =  FindWindow(  sShowInfoStruct.errHintWndCls,  NULL  );
		if  (  firstWnd  )  {
			COPYDATASTRUCT	tmpCopyData;
			
			tmpCopyData.lpData  =  buf;
			tmpCopyData.cbData  =  sizeof(  buf  )  -  1;
			SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		}
	}

	traceLogA(  "errLog: %s, %s",  buf,  !sShowInfoStruct.errHintWndCls[0]  ?  ""  :  (  firstWnd  ?  ""  :  "status window is not active"  )  );


	/*
	if  (  sErrLogFile[0]  ) {

		#ifdef  WIN32
			sprintf(  filenamebuf,  "%s",  sErrLogFile  );
		#else
			sprintf(  filenamebuf,  "%s/%s%d",  LOGDIR,  COMMONERRLOGFILE,  getpid(  )  );
		#endif

		getcurtime(  timebuf  );

		if  (  !(  fperr  =  fopen(  filenamebuf,  "a"  )  )  )  {
			traceLogA(  "Can't open a file to show error info."  );
			}
		else  {
			  fprintf(  fperr,  "%s|%s: ",  timebuf,  sErrLogHint  );
			  vfprintf(  fperr,  fmt,  args  );
			  fprintf(  fperr,  "\n"  );
			  fflush(  fperr  );
			  fclose(  fperr  );
		}

		fileLen  =  getFileLen(  filenamebuf  );
		if  (   fileLen  >  MAX_ERR_LOG_FILE_LEN  )  {
			traceLogA(  "%s is too long, so is to be truncated.",  filenamebuf  );
			if  (  !truncFileHead(  fileLen  -  MAX_ERR_LOG_FILE_LEN / 2,  filenamebuf  )  )  {
				traceLogA(  "%s is truncated.",  filenamebuf  );
				}
			else  {
				  traceLogA(  "%s can't be truncated, is to be deleted.",  filenamebuf  );
				  DeleteFile( filenamebuf );
			}
		}

	}
	*/
	
	va_end(  args  );

#ifndef  __WINCE__
	errno  =  errnoBuf;
#endif

	return  0;

}



