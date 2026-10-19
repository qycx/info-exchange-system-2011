

#include	<winsock2.h>
#include	<mswsock.h>
#include	<windows.h>
#include	"qyCommon.h"
#include	<tchar.h>
#include	<vfw.h>

#include	"qyTCharCommProc.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"						//  2005/01/24

#include	"qyMsgFunc.h"
#include	"mtSock_iOCP.h"

#include	"qnmCommProc.h"
#include	"qySyncCommProc.h"

#include	"qmOpenCommon.h"

#include	"qnmCommProc_mis.h"


 TCHAR  *  getWhereBuf_showInfoFromSession(  void  *  pSessionParam,  unsigned  int  *puiBufCnt  );
 //
 void  *  getQMemObjFromSession(  void  *  pSessionParam  );
 int  detachCliIndexFromQMemObj(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex,  void  *  pQMemObj  );
 void  exitCrypt_qmd(  void  *  pQmdSession  );
 //
 int  procMsgFromMgr(  MT_SOCK_IOCP  *  pMtSock,  unsigned  uiMsgType,  unsigned  int  uiCliIndex  );


 extern  "C"  DWORD  WINAPI  mtServSockThreadProc_iocp(  LPVOID  lpParameter  );
 extern  "C"  DWORD  WINAPI  mtCliSockThreadProc_iocp(  LPVOID  lpParameter  );
 BOOL  closeClient(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  index,  BOOL  bGraceful  );


// Allocate a socket context for the new connection.  
//
 PER_SOCKET_CONTEXT  *  perSocketContextNew(  )
{
	int						iErr				=	-1;
    PER_SOCKET_CONTEXT  *	lpPerSocketContext  =  NULL;

    lpPerSocketContext  =  (  PER_SOCKET_CONTEXT  *  )malloc(  sizeof(  PER_SOCKET_CONTEXT  )  );
	if  (  !lpPerSocketContext  )  goto  errLabel;
	memset(  lpPerSocketContext,  0,  sizeof(  PER_SOCKET_CONTEXT  )  );
	
	lpPerSocketContext->inputContext.wsaBuf.buf  =  (  char  *  )lpPerSocketContext->inputContext.buf;
	lpPerSocketContext->inputContext.wsaBuf.len  =  sizeof(  lpPerSocketContext->inputContext.buf  );
	//
	lpPerSocketContext->outputContext.wsaBuf.buf  =  (  char  *  )lpPerSocketContext->outputContext.buf;
	lpPerSocketContext->outputContext.wsaBuf.len  =  sizeof(  lpPerSocketContext->outputContext.buf  );

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  lpPerSocketContext  )  {
			free(  lpPerSocketContext  );
		}
	}
    return  iErr  ?  NULL  :  lpPerSocketContext;
}

 void  perSocketContextFree(   PER_SOCKET_CONTEXT  *  lpPerSocketContext  )
{
	 if  (  lpPerSocketContext  )  {
		 free(  lpPerSocketContext  );
	 }

	 return;
}


 
 int initQyMtSock_iocp( char *servIp, unsigned short port, MT_SERVWORK * pServWork, void * pParentParam,  void  **  ppMtSock  )
{
	int									iErr						=	-1;
	int									i;
	MT_SOCK_IOCP					*	pMtSock						=	0;
	DWORD								dwThreadDaemonId;
	GUID								GuidAcceptEx				=	WSAID_ACCEPTEX;
	GUID								GuidGetAcceptExSockAddrs	=	WSAID_GETACCEPTEXSOCKADDRS;
	DWORD								dwBytes;
	 
	
	if  (  !pServWork  )  return  -1;
	if  (  pServWork->usMaxConns  >  MAX_CONNS  )  {
		traceLogA(  "参数过大：MT_SERVWORK中的并发连接数不能大于%d",  MAX_CONNS  );
		return  -1;
	}
	if  (  !ppMtSock  ||  *ppMtSock  )  return  -1;	//  此*ppMtSock为了将指针传出去

	if  (  !(  pMtSock  =  (  MT_SOCK_IOCP  *  )malloc(  sizeof(  MT_SOCK_IOCP  )  )  )  )  goto  errLabel;
	memset(  pMtSock,  0,  sizeof(  pMtSock[0]  )  );
	
	pMtSock->servSockFd = -1;	
	for ( i = 0; i < MAX_CONNS; i ++ )	pMtSock->cliInfos[i].cliSockFd = -1;

	pMtSock->pParentParam		=	pParentParam;

	if  (  servIp  &&  strlen( servIp ) <= MAX_IP_ADDR_LEN  ) strcpy( pMtSock->servIp, servIp );
	else  { 
			traceLogA(  "initQyMtSock: servIp is null or too long string, 因此将绑定本机上任意IP"  );
			strcpy( pMtSock->servIp, ""  );
	}
	pMtSock->port				=	port;

	memcpy(  &pMtSock->servWork,  pServWork,  sizeof(  MT_SERVWORK  )  );
	if  (  lstrlen(  pMtSock->servWork.mutexName  )  >=  mycountof(  pMtSock->servWork.mutexName  )  )  goto  errLabel;
	if  (  !pMtSock->servWork.sT.iAccept  ||  !pMtSock->servWork.sT.iRead  )  {
		traceLogA(  "没有赋超时参数，将取缺省超时值"  );
		setSockTimeout(  &pMtSock->servWork.sT  );
	}
	if  (  !pMtSock->servWork.usMaxConns  )  pMtSock->servWork.usMaxConns  =  MAX_CONNS;
	if  (  !pMtSock->servWork.usMaxProcThreads  )  pMtSock->servWork.usMaxProcThreads  =  mycountof(  pMtSock->hCliThreads  );
	if  (  pMtSock->servWork.usMaxProcThreads  >  mycountof(  pMtSock->hCliThreads  )  )  goto  errLabel;
	if  (  pMtSock->servWork.usSessionSize  <  sizeof(  QY_COMM_SESSION  )  )  pMtSock->servWork.usSessionSize  =  sizeof(  QY_COMM_SESSION  );
	
	pMtSock->iWaitTimeout								=	5000;
	pMtSock->uiMilliSeconds_mutex_syncCli				=	10000;
	//
	pMtSock->uiMilliSeconds_mutex_syncPerSocketContext	=	30000;
	//
	pMtSock->uiMaxCnt_sema					=	CONST_uiMaxCnt_sema_syncSessionOnOff;
	pMtSock->uiInitCnt_sema					=	pMtSock->uiMaxCnt_sema  -  1;
	pMtSock->uiMilliSeconds_mutex_r			=	10000;
	pMtSock->uiMilliSeconds_sema_r			=	10000;
	pMtSock->uiMilliSeconds_mutex_w			=	10000;
	pMtSock->uiMilliSeconds_sema_w			=	10000;

	//
	_sntprintf(  pMtSock->mutexName_syncModifyingObjInfo,  mycountof(  pMtSock->mutexName_syncModifyingObjInfo  ),  _T(  "syncModifyObj"  )  );
	//

	qyShowInfo(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  "Begin to "  ),  _T(  "initialize session memory"  )  ); ///*初始化会话存储空间*/

	traceLog(  _T(  ""  )  );
	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
		 MT_SOCK_CLIINFO_IOCP  *  pCliInfo	=	&pMtSock->cliInfos[i];
		 if  (  !(  pMtSock->pPerSocketContexts[i]  =  perSocketContextNew(  )  )  )  goto  errLabel;
		 if  (  !(  pMtSock->pSessions[i]  =  malloc(  pMtSock->servWork.usSessionSize  )  )  )  goto  errLabel;
		 memset(  pMtSock->pSessions[i],  0,  pMtSock->servWork.usSessionSize  );
		 _sntprintf(  pCliInfo->mutexName_syncPerSocketContext,  mycountof(  pCliInfo->mutexName_syncPerSocketContext  ),  _T(  "syncPerSock%d"  ),  i   );
		 //
#if  0
		 _sntprintf(  pCliInfo->mutexName_syncSessionOnOff,  mycountof(  pCliInfo->mutexName_syncSessionOnOff  ),  _T(  "syncSessData%d"  ),  i   );
		 pCliInfo->hSema_syncSessionOnOff  =  CreateSemaphore(  0,  pMtSock->uiInitCnt_sema,  pMtSock->uiMaxCnt_sema,  NULL  );
		 if  (  !pCliInfo->hSema_syncSessionOnOff  )  goto  errLabel;		 
#else
		 pCliInfo->pRw_syncSessionOnOff  =  new  CMutexRW(  );
		 if  (  !pCliInfo->pRw_syncSessionOnOff  )  goto  errLabel;
#endif
		 //
		 if  (  initGenericQ(  pCliInfo->mutexName_syncPerSocketContext,  pCliInfo->mutexName_syncPerSocketContext,  0,  CONST_uiMaxQNodes_perSocketContextOutputQ,  malloc,  free,  &pCliInfo->outputQ  )  )  goto  errLabel;
		 pCliInfo->bOutputQInited  =  TRUE;

	}

	qyShowInfo(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  "End to "  ),  _T(  "initialize session memory"  )  ); //初始化会话存储空间

	pMtSock->hIocp  =  CreateIoCompletionPort(  INVALID_HANDLE_VALUE,  NULL,  0,  pMtSock->servWork.usMaxProcThreads  );
    if  (  !pMtSock->hIocp  )  goto  errLabel;

	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxProcThreads;  i  ++  )  {
		 //  
		 pMtSock->hCliThreads[i]  =  CreateThread(  NULL,  0,  mtCliSockThreadProc_iocp,  (  LPVOID  )pMtSock,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
		 if  (  !pMtSock->hCliThreads[i]  )  goto  errLabel;
		 pMtSock->dwThreadIds[i]  =  dwThreadDaemonId;	//  2007/03/29, 为了引入这个标记，以便mtCliSockThreadProc能够在pMtSock里找到存放的物理位置，故要先挂起一下，然后再恢复
		 if  (  ResumeThread(  pMtSock->hCliThreads[i]  )  ==  -1  )  goto  errLabel;
		 traceLogA(  "initMtSock( ): CreateThread(  ) [%lu] runs ...",  dwThreadDaemonId  );		 
	}

	if  (  asrListen(  pMtSock->port,  &pMtSock->servSockFd  )  )  {
		pMtSock->bListenFailed  =  TRUE;
		traceLogA(  "不能监听端口%d",  pMtSock->port  );
		goto  errLabel;
	}

	PER_SOCKET_CONTEXT	*	lpPerSocketContext;
	lpPerSocketContext  =  perSocketContextNew(  );
	if  (  !lpPerSocketContext  )  goto  errLabel;
				   
	//  lpPerSocketContext->sockFd  =  pMtSock->servSockFd;
	pMtSock->pPerSocketContexts_serv  =  lpPerSocketContext;
	lpPerSocketContext->inputContext.ioOperation  =  CONST_io_accept;

	HANDLE	hIOCP;

	hIOCP  =  CreateIoCompletionPort(  (  HANDLE  )pMtSock->servSockFd,  pMtSock->hIocp,  (  DWORD  )lpPerSocketContext,  0  );
	if  (  !hIOCP  )  goto  errLabel;

	if  (  WSAIoctl(  pMtSock->servSockFd,  SIO_GET_EXTENSION_FUNCTION_POINTER,  &GuidAcceptEx,  sizeof(  GuidAcceptEx  ),  &pMtSock->lpfnAcceptEx,  sizeof(  pMtSock->lpfnAcceptEx  ),  &dwBytes,  NULL,  NULL  )  )  {
		traceLogA(  "WSAIoctl failed"  );  goto  errLabel;
	}
	if  (  WSAIoctl(  pMtSock->servSockFd,  SIO_GET_EXTENSION_FUNCTION_POINTER,  &GuidGetAcceptExSockAddrs,  sizeof(  GuidGetAcceptExSockAddrs  ),  &pMtSock->lpfnGetAcceptExSockAddrs,  sizeof(  pMtSock->lpfnGetAcceptExSockAddrs  ),  &dwBytes,  NULL,  NULL  )  )  {
		traceLogA(  "WSAIoctl failed"  );  goto  errLabel;
	}

	traceLogA(  "监听端口%d",  pMtSock->port  );
	qyShowInfo(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  "Listen on "  ),  _T(  "%u"  ),  pMtSock->port  ); 

	pMtSock->bQuit = FALSE;
	
	pMtSock->hEventAccept  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );
	if  (  !pMtSock->hEventAccept  )  goto  errLabel;

	pMtSock->hServThread = CreateThread( NULL, 0, mtServSockThreadProc_iocp, pMtSock, 0, &dwThreadDaemonId );
	if ( !pMtSock->hServThread ) goto errLabel;
	traceLogA(  "initMtSock: CreateThread(  ) [%lu] runs ...",  dwThreadDaemonId  );
	
	if  (  !SetEvent(  pMtSock->hEventAccept  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pMtSock  )  exitQyMtSock_iocp(  pMtSock  );
					
	}

	if  (  !iErr  )  {
		*ppMtSock  =  pMtSock;
	}

    

	return iErr;

}


 void  exitQyMtSock_iocp(  void  *  pMtSockParam  )
{
	MT_SOCK_IOCP	*	pMtSock  =  (  MT_SOCK_IOCP  *  )pMtSockParam;
	int								i;
	
	if  (  !pMtSock  )  return;

	pMtSock->bQuit = TRUE;

	//  将servThread先退出是因为不能让servThread继续接受请求并改变cliThread
	if  (  pMtSock->hServThread  )  {
		MACRO_qyNullThread(  pMtSock->hServThread  );
	}

	if  (  pMtSock->hEventAccept  )  {
		CloseHandle(  pMtSock->hEventAccept  );  pMtSock->hEventAccept  =  NULL;
	}		

	if  (  pMtSock->servSockFd  >=  0  )  {  closesocket(  pMtSock->servSockFd  );  pMtSock->servSockFd  =  -1;  }

	if  (  pMtSock->hIocp  )  {
		for  (  i = 0; i < pMtSock->servWork.usMaxProcThreads;  i  ++  )  {
			 PostQueuedCompletionStatus(  pMtSock->hIocp,  0,  0,  NULL  );
		}        
    }

	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxProcThreads;  i  ++  )  {
		
		if  (  pMtSock->hCliThreads[i]  )  {
			debugLog( "exitMtSock( ): before WaitFor thread[%d]", i );
			::WaitForSingleObject( pMtSock->hCliThreads[i], INFINITE );
			if ( CloseHandle( pMtSock->hCliThreads[i] ) ) {
				debugLog( "exitMtSock( ): CloseHandle( hCliThread[%d] ) succeeded", i );
			}
			else debugLog(  "exitMtSock( ): CloseHandle( hCliThread[%d] ) failed.", i );
			pMtSock->hCliThreads[i] = NULL;
		}		
	}

	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
		 if  (  pMtSock->cliInfos[i].bUsed  )  closeClient(  pMtSock,  i,  FALSE  );		
	}


	if  (  pMtSock->hIocp  )  {  CloseHandle(  pMtSock->hIocp  );  pMtSock->hIocp  =  0;  }

	if  (  pMtSock->pPerSocketContexts_serv  )  {
		perSocketContextFree(  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts_serv  );
		pMtSock->pPerSocketContexts_serv  =  NULL;
	}

	traceLogA(  "这里需要把所有的socketContext都释放"  );
	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
		 MT_SOCK_CLIINFO_IOCP  *  pCliInfo	=	&pMtSock->cliInfos[i];

		 if  (  pCliInfo->bOutputQInited  )  {	//  2007/08/15
			 exitGenericQ(  &pCliInfo->outputQ  );  pCliInfo->bOutputQInited  =  FALSE;
		 }

		 if  (  pMtSock->pSessions[i]  )  free(  pMtSock->pSessions[i]  );
		 if  (  pMtSock->pPerSocketContexts[i]  )  perSocketContextFree(  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[i]  );
		 //
#if  0
		 if  (  pCliInfo->hSema_syncSessionOnOff  )  CloseHandle(  pCliInfo->hSema_syncSessionOnOff  );
#else
		 MACRO_safeDelete(  pCliInfo->pRw_syncSessionOnOff  );
#endif
	}


	free(  pMtSock  );		//  这里要释放，不要忘了

	return;
	
}



//  Allocate a context structures for the socket and add the socket to the IOCP.  
//  Additionally, add the context structure to the global list of context structures.
// 

 int  addToIocp(  unsigned  int  uiCliIndex,  MT_SOCK_IOCP  *  pMtSock  )
{
	int									iErr				=	-1;
	MT_SOCK_CLIINFO_IOCP			*	pCliInfo			=	NULL;
	PER_SOCKET_CONTEXT				*	pPerSocketContext	=	NULL;
	void							*	pSession			=	NULL;
	HANDLE								hIOCP				=	NULL;
	DWORD								dwRecvNumBytes		=	0;     
    DWORD								dwFlags				=	0;    
	BOOL								bRet				=	FALSE;
	DWORD								dwBytes				=	0;
	
	if  (  !bCliIndexValid(  pMtSock,  uiCliIndex  )  )  return  -1;
	
	pCliInfo  =  &pMtSock->cliInfos[uiCliIndex];
	pPerSocketContext  =  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[uiCliIndex];
	pSession  =  pMtSock->pSessions[uiCliIndex];
	if  (  !pPerSocketContext  ||  !pSession  )  {
		traceLogA(  "addToIocp 遇到了严重问题：lpPerSocketContext is null or pSession is null"  );
		goto  errLabel;
	}

	//  这里要同步一下。防止胡乱操作perSocketContext和session中的内容

	{
		CQySyncObj	syncObj;

		if  (  syncObj.sync(  pCliInfo->mutexName_syncPerSocketContext,  pMtSock->uiMilliSeconds_mutex_syncPerSocketContext  )  )  goto  errLabel;
	
		memset(  pPerSocketContext,  0,  sizeof(  PER_SOCKET_CONTEXT  )  );
		//
		if  (  pMtSock->servWork.uiBufSize_msgInput  )  {
            
			//  if  (  !(  pPerSocketContext->pMsgInput_cache  = (  char  *  ) malloc(  pMtSock->servWork.uiBufSize_msgInput  )  )  )  goto  errLabel;
			//  这个缓存可以在 qmdServWork_mis 中动态生成.这样可以节约内存占用

			
			GENERIC_Q_CFG	tmpqCfg;					//  2008/05/25
			
			memset(  &tmpqCfg,  0,  sizeof(  tmpqCfg  )  );
			_sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "qmdInCacheQ%d"  ),  uiCliIndex  );
			tmpqCfg.uiMaxQNodes  =  CONST_uiMaxQNodes_perSocketContextInCacheQ;
			if  (  initGenericQ(  &tmpqCfg,  malloc,  0,  0,  free,  NULL,  &pPerSocketContext->inCacheQ  )  )  goto  errLabel;
			pPerSocketContext->bInCacheQInited  =  TRUE;

			memset(  &tmpqCfg,  0,  sizeof(  tmpqCfg  )  );
			_sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "qmdOutCacheQ%d"  ),  uiCliIndex  );
			tmpqCfg.uiMaxQNodes  =  CONST_uiMaxQNodes_perSocketContextOutCacheQ;
			if  (  initGenericQ(  &tmpqCfg,  malloc,  0,  0,  free,  NULL,  &pPerSocketContext->outCacheQ  )  )  goto  errLabel;
			pPerSocketContext->bOutCacheQInited  =  TRUE;

		}
	}

	//  2012/02/25
	pPerSocketContext->sockFd  =  pCliInfo->cliSockFd;
	//
	pPerSocketContext->uiCliIndex  =  uiCliIndex;
	pPerSocketContext->uiSessionId  =  getNextSessionId(  );
	
	memset(  pSession,  0,  pMtSock->servWork.usSessionSize  );
	

	TCHAR			*	pWhereBuf;
	unsigned  int		uiBufCnt;

	if  (  (  pWhereBuf  =  getWhereBuf_showInfoFromSession(  pSession,  &uiBufCnt  )  )  )  {
		_sntprintf(  pWhereBuf,  uiBufCnt,  _T(  "%d: "  ),  pPerSocketContext->uiSessionId  );
	}


	emptyGenericQ(  &pCliInfo->outputQ  );	//  2007/08/16, 这里需要把outputQ给清空，以便为新的工作做准备。注意一下。

	//	
	hIOCP  =  CreateIoCompletionPort(  (  HANDLE  )pCliInfo->cliSockFd,  pMtSock->hIocp,  (  DWORD  )pPerSocketContext,  0  );
	if  (  !hIOCP  )  goto  errLabel;
	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {		
	}
	return  iErr;
}


 int  myAccept(  unsigned  int  uiCliIndex,  MT_SOCK_IOCP  *  pMtSock  )
{
	int									iErr				=	-1;
	PER_SOCKET_CONTEXT				*	lpPerSocketContext	=	NULL;
	DWORD								dwRecvNumBytes		=	0;     
    DWORD								dwFlags				=	0;    
	BOOL								bRet				=	FALSE;
	DWORD								dwBytes				=	0;
	
	if  (  uiCliIndex  >=  mycountof(  pMtSock->cliInfos  )  )  return  -1;
	
	lpPerSocketContext  =  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts_serv;
	if  (  !lpPerSocketContext  )  goto  errLabel;
				   
	lpPerSocketContext->uiCliIndex  =  uiCliIndex;
	lpPerSocketContext->inputContext.ioOperation  =  CONST_io_accept;
	memset(  &lpPerSocketContext->inputContext.overlapped,  0,  sizeof(  lpPerSocketContext->inputContext.overlapped  )  );
	
	bRet  =  pMtSock->lpfnAcceptEx(  pMtSock->servSockFd,  pMtSock->cliInfos[uiCliIndex].cliSockFd,  lpPerSocketContext->inputContext.wsaBuf.buf,  0,  sizeof(  SOCKADDR_IN  )  +  16,  sizeof(  SOCKADDR_IN  )  +  16,  &dwBytes,  &lpPerSocketContext->inputContext.overlapped  );
	if  (  bRet  )  {
		traceLogA(  "这里可以将接收到的信息再发到iocp队列里去"  );
		qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "updateIoCompletionPort:"  ),  _T(  "未进入overlapped模式，会话被关闭"  )  ); 
		goto  errLabel;
	}
	if  (  !bRet  &&  WSAGetLastError(  )  !=  ERROR_IO_PENDING  )  {
		qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "updateIoCompletionPort:"  ),  _T(  "accept failed"  )  ); 
		goto  errLabel;
	}
	
	iErr  =  0;

errLabel:

	qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  "myAccept:"  ),  _T(  "index is %u, %s"  ),  uiCliIndex,  (  iErr  ?  _T(  "failed"  ):  _T(  "OK"  )  )  ); 

	if  (  iErr  )  {
	}
	return  iErr;
}


 extern  "C"  DWORD  WINAPI  mtServSockThreadProc_iocp(  LPVOID  lpParameter  )
{
	int									iErr				=	-1;
	MT_SOCK_IOCP					*	pMtSock				=	(  MT_SOCK_IOCP  *  )lpParameter;
	int									i;
	int									iRet;
	SOCKET								iAcceptSockFd		=	-1;
	PER_SOCKET_CONTEXT				*	lpPerSocketContext	=	NULL;


	traceLogA(  "mtServSockThreadProc enters"  );

	while  (  !pMtSock->bQuit  )  {

		   while  (  !pMtSock->bQuit  )  {
				  for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
					   if  (  !pMtSock->cliInfos[i].bUsed  )  break;
				  }
				  if  (  i  <  pMtSock->servWork.usMaxConns  )  break;

				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  "无可用socket，需等待其他线程释放空闲的socket"  ),  _T(  ""  )  );

				  Sleep( 1500 );
				  //  OutputDebugString( "no availabel socket, wait.\n" );			
		   }

		   
		   //		   
		   iRet  =  ::WaitForSingleObject(  pMtSock->hEventAccept,  pMtSock->iWaitTimeout  );
		   if  (  iRet  ==  WAIT_FAILED  )  goto errLabel;
		   if  (  iRet  ==  WAIT_TIMEOUT  )  {

			   if  (  bShowMore(  )  )  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "(Server)"  ),  NULL,  _T(  "mtSockServer:"  ),  _T(  "等待下一个有效连接"  ),  _T(  ""  )  ); 

			   continue;
		   }

		   //
		   if  (  pMtSock->bQuit  )  break;

	
		   iAcceptSockFd  =  socket(  AF_INET,  SOCK_STREAM,  IPPROTO_TCP  );
		   if  (  iAcceptSockFd  ==  INVALID_SOCKET  )  goto  errLabel;  
		   
		   pMtSock->cliInfos[i].cliSockFd  =  iAcceptSockFd;
		   pMtSock->cliInfos[i].bUsed  =  TRUE;		
			
		   //  qyShowInfo(  CONST_qyShowType_debug,  _T(  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "mtServSockThreadProc:"  ),  _T(  "before update"  )  ); 

		   if  (  myAccept(  i,  pMtSock  )  )  {
			   traceLogA(  "myAccept failed"  );
			   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "myAccept failed: 不能进行Accept：index为%u"  ),  i  ); 
			   //
			   pMtSock->cliInfos[i].bUsed  =  FALSE;	
			   closesocket(  pMtSock->cliInfos[i].cliSockFd  );  pMtSock->cliInfos[i].cliSockFd  =  -1;

			   //  因为这里失败了，所以要自己启动一个event, 来重新发起accept连接
			   if  (  !SetEvent(  pMtSock->hEventAccept  )  )  goto errLabel;

		   }

		   //  注意，myAccept返回成功，才是一个新连接成功了
		   InterlockedIncrement(  &pMtSock->nBusyConns  );		//  2007/08/14

		   continue;

	}

	iErr  =  0;

errLabel:

	if  (  iErr  )  pMtSock->bErr  =  TRUE;
	
	traceLogA(  "mtServSockThreadProc leaves"  );

	return  iErr;

}

  BOOL  bCliIndexValid(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex  )
{
	 return  (  uiCliIndex  <  mycountof(  pMtSock->cliInfos  )  );
}




 //  closeClient(  )返回false表明是严重的问题，
 BOOL  closeClient(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex,  BOOL  bGraceful  )
{
	 BOOL						bRet				=	FALSE;
	 MT_SOCK_CLIINFO_IOCP	*	pCliInfo			=	NULL;
	 PER_SOCKET_CONTEXT		*	pPerSocketContext	=	NULL;
	 void					*	pSession			=	NULL;
	 unsigned  int				uiSessionId			=	0;
	 TCHAR						whereBuf[32]		=	_T(  ""  );
		 	
	 if  (  !bCliIndexValid(  pMtSock,  uiCliIndex  )  )  return  FALSE;
	 
	 pCliInfo  =  &pMtSock->cliInfos[uiCliIndex];
	 pPerSocketContext  =  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[uiCliIndex];
	 pSession  =  pMtSock->pSessions[uiCliIndex];

	 uiSessionId  =  pPerSocketContext->uiSessionId;
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%d: "  ),  uiSessionId  );
	 
	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  pPerSocketContext->clientIp,  _T(  "Server"  ),  0,  whereBuf,  _T(  ""  ),  _T(  "close sockets[%d]"  ),  uiCliIndex  ); 

	 if  (  pCliInfo->bUsed  &&  pCliInfo->cliSockFd  >=  0  )  {
			
		 traceLogA(  "closeClient:  index %u",  uiCliIndex  );

		 if  (  !bGraceful  )  {
			 // force the subsequent closesocket to be abortative.
			 LINGER  lingerStruct;

			 lingerStruct.l_onoff = 1;
			 lingerStruct.l_linger = 0;
			 setsockopt(  pCliInfo->cliSockFd,  SOL_SOCKET,  SO_LINGER,  (  char  *  )&lingerStruct,  sizeof(  lingerStruct  )  );
		 }

		 setIoTime(  pPerSocketContext,  CONST_io_null,  0  );
		 closesocket(  pCliInfo->cliSockFd  );
		 pCliInfo->cliSockFd  =  -1;
			 

		 if  (  pSession  )  {

			 detachCliIndexFromQMemObj(  pMtSock,  uiCliIndex,  getQMemObjFromSession(  pSession  )  );
		
			 exitCrypt_qmd(  pSession  );

			 memset(  pSession,  0,  pMtSock->servWork.usSessionSize  );
		 }	

		 if  (  pPerSocketContext  )  {
			 CQySyncObj		syncObj;
			 if  (  syncObj.sync(  pCliInfo->mutexName_syncPerSocketContext,  pMtSock->uiMilliSeconds_mutex_syncPerSocketContext  )  )  goto  errLabel;

			 //  2008/05/25
			 if  (  pPerSocketContext->bInCacheQInited  )  exitGenericQ(  &pPerSocketContext->inCacheQ  );
			 if  (  pPerSocketContext->bOutCacheQInited  )  exitGenericQ(  &pPerSocketContext->outCacheQ  );
			 if  (  pPerSocketContext->pMsgInput_cache  )  free(  pPerSocketContext->pMsgInput_cache  );

			 memset(  pPerSocketContext,  0,  sizeof(  pPerSocketContext[0]  )  );
		 }

		 pCliInfo->bUsed  =  FALSE;		InterlockedDecrement(  &pMtSock->nBusyConns  );	//  2007/08/14		
	
	 }		 
	
	 bRet  =  TRUE;
	 
errLabel:

	 if  (  !bRet  )  {
		 qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  whereBuf,  _T(  ""  ),  _T(  "Serious error: closeClient failed: index is %d"  ),  uiCliIndex  ); 
	 }

	 return  bRet;    
} 


 int  procIocpAccept(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex,  char  *  clientIp  )
{
	 int		iErr	=	-1;
	
	 if  (  !bCliIndexValid(  pMtSock,  uiCliIndex  )  )  return  -1;
	 if  (  !clientIp  )  return  -1;
	 		
	 if  (  setsockopt(  pMtSock->cliInfos[uiCliIndex].cliSockFd,  SOL_SOCKET,  SO_UPDATE_ACCEPT_CONTEXT,  (  char  *  )&pMtSock->servSockFd,  sizeof(  pMtSock->servSockFd  )  )  ==  SOCKET_ERROR  )  goto  errLabel;
	 
	 //  addToIOCP servSockFd
	 if  (  addToIocp(  uiCliIndex,  pMtSock  )  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  clientIp,  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "accept connection: addToIocp failed"  )  ); 
		 goto  errLabel;
	 }


	 //						
	 PPER_SOCKET_CONTEXT				tmppPerSocketContext;
	 	
	 tmppPerSocketContext  =  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[uiCliIndex];
	 safeStrnCpy(  clientIp,  tmppPerSocketContext->clientIp,  mycountof(  tmppPerSocketContext->clientIp  )  );
	 //  
	 tmppPerSocketContext->status.accept.dwTickCnt_accepted  =  GetTickCount(  );		//  2011/01/29
							
	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  clientIp,  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "accept connection, index is %d, sessionId is %d"  ),  uiCliIndex,  tmppPerSocketContext->uiSessionId  ); 

	 //
	 PPER_IO_CONTEXT					tmppIoContext; 

	 tmppIoContext  =  &tmppPerSocketContext->inputContext;

	 // post initial receive on this socket
	 memset(  tmppIoContext,  0,  sizeof(  tmppIoContext[0]  )  );
	 if  (  qyRecvMsg_iocp(  pMtSock,  tmppPerSocketContext,  tmppIoContext,  NULL  )  )  goto  errLabel;

	 iErr  =  0;


errLabel:

	 return  iErr;
}


 int  getMutexName_syncCli(  unsigned  int  uiCliIndex,  char  io,  TCHAR  *  mutexName_syncCli,  unsigned  int  size  )
{
	TCHAR	*		CONST_mutexName_syncCli_iocp	=	_T(  "syncCliIocp"  );

	switch  (  io  )  {
			case  'r':
					  _sntprintf(  mutexName_syncCli,  size,  _T(  "%s%u-r"  ),  CONST_mutexName_syncCli_iocp,  uiCliIndex  );
					  break;
			case  'w':
					  _sntprintf(  mutexName_syncCli,  size,  _T(  "%s%u-w"  ),  CONST_mutexName_syncCli_iocp,  uiCliIndex  );
					  break;
			default:
					return  -1;
	}
	return  0;
}


 extern  "C"  DWORD  WINAPI  mtCliSockThreadProc_iocp(  LPVOID  lpParameter  )
{
	int								iErr				=	-1;
	MT_SOCK_IOCP				*	pMtSock				=	(  MT_SOCK_IOCP  *  )lpParameter;
	DWORD							dwThreadId			=	GetCurrentThreadId(  );
	//  int								i;
	//  
	MT_SOCK_SUBTHREADINFO			subThreadInfo;
	BOOL							bServWorkInited		=	FALSE;
	BOOL							bSuccess			=	FALSE;
	MT_SOCK_CLIINFO_IOCP		*	pCliInfo			=	NULL;
	PPER_SOCKET_CONTEXT				pPerSocketContext	=	NULL;
    PPER_IO_CONTEXT					pIoContext			=	NULL; 
    DWORD							dwFlags				=	0;
    DWORD							dwIoBytes;


	traceLogA(  "mtCliSockThreadProc enters"  );

	memset( ( char * )&subThreadInfo, 0, sizeof( subThreadInfo ) );

	subThreadInfo.iServiceId  =  pMtSock->servWork.iServiceId;		//  2007/03/12
	if  (  pMtSock->servWork.mutexName[0]  )  {
		subThreadInfo.hMutex = CreateMutex(  NULL,  FALSE,  pMtSock->servWork.mutexName  );
		if  (  !subThreadInfo.hMutex  )  {
			qyDisplayLastError(  "mtCliSockThreadProc: CreateMutex( ) failed"  );		
			goto  errLabel;
		}
	}
	subThreadInfo.pTo				=	&pMtSock->servWork.sT;
	subThreadInfo.pParentParam		=	pMtSock->pParentParam;

	if  (  pMtSock->servWork.pfInitServWork  &&  pMtSock->servWork.pfInitServWork(  &subThreadInfo, 0  )  )  {
		traceLogA(  "mtCliSockThreadProc(  ): pfInitServWork(  ) failed."  );
		goto  errLabel;
	}
	bServWorkInited					=	TRUE;

	while  (  !pMtSock->bQuit  )  {

		   bSuccess  =  GetQueuedCompletionStatus(  pMtSock->hIocp,  &dwIoBytes,  (  PDWORD  )&pPerSocketContext,  (  LPOVERLAPPED  *  )&pIoContext,  pMtSock->iWaitTimeout  );

		   if  (  !bSuccess  &&  GetLastError(  )  ==  WAIT_TIMEOUT  )  {
			   //  traceLogA(  "GetQueuedCompletionStatus: timeout"  );  
			   continue;
		   }

		   if  (  !bSuccess  )  qyDisplayLastError(  "GetQueuedCompletionStatus"  );
		   
		   if  (  pPerSocketContext  ==  NULL  )  {
			   unsigned  int	uiMsgType	=	dwIoBytes;
			   unsigned  int	uiCliIndex  =  (  unsigned  int  )pIoContext;

			   if  (  !bCliIndexValid(  pMtSock,  uiCliIndex  )  )  {
				   traceLogA(  "从postMsg2Iocp那里得到一个越界的index, %d",  uiCliIndex  );  
				   goto  errLabel;
			   }
			   pCliInfo  =  &pMtSock->cliInfos[uiCliIndex];


			   //  这2个是要退出的msgType
			   if  (  uiMsgType  ==  CONST_misMsgType_null  ||  uiMsgType  ==  CONST_misMsgType_quit  )  {
				   // PostQueuedCompletionStatus post an I/O packet with
		    	   // a NULL CompletionKey (or if we get one for any reason).  It is time to exit.
				   traceLogA(  "procMsgFromMgr:  得到了退出指令"  );
				   qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "Exit instruction has received "/*得到一个退出的消息*/  )  ); 
				   iErr  =  0;  goto  errLabel;
			   }

			   //  2007/12/20
			   if  (  uiMsgType  ==  CONST_misMsgType_closeChannel  )  {
				   CQyRWLock		lockObj;

				   traceLogA(  "mtCliSockThreadProc_iocp: msgType_closeChannel"  );

#if  0
				   if  (  lockObj.wLock(  pCliInfo->mutexName_syncSessionOnOff,  pMtSock->uiMilliSeconds_mutex_w,  pCliInfo->hSema_syncSessionOnOff,  pMtSock->uiMilliSeconds_sema_w,  pMtSock->uiInitCnt_sema  )  )  
#else
				   if  (  lockObj.wLock(  pCliInfo->pRw_syncSessionOnOff,  pMtSock->uiMilliSeconds_sema_w  )  )  
#endif
				   {
					   traceLogA(  "加写锁失败"  );
					   qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "wLock %d failed"  ),  uiCliIndex  ); 
					   continue;
				   }
				   closeClient(  pMtSock,  uiCliIndex,  TRUE  );
				   continue;
			   }
			   
			   //  下面为普通消息
			   if  (  procMsgFromMgr(  pMtSock,  uiMsgType,  uiCliIndex  )  )  {
				   qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "procMsgFromMgr %d failed"  ),  uiCliIndex  ); 
				   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  					   
				   continue;
			   }				   

			   continue;

		   }

		   unsigned  int					uiCliIndex;

		   uiCliIndex  =  pPerSocketContext->uiCliIndex;
		   if  (  !bCliIndexValid(  pMtSock,  uiCliIndex  )  )  {
			   qyShowInfo(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "得到一个越界的index: %d"  ),  uiCliIndex  ); 
			   goto  errLabel;
		   }
		   pCliInfo  =  &pMtSock->cliInfos[uiCliIndex];


		   if  (  pIoContext->ioOperation  ==  CONST_io_accept  )  {	//  accept最需要的就是一定要触发一个event
			   char			clientIp[CONST_qyMaxIpLen  +  1]	=	"";
			   CQyRWLock	lockObj;
			
			   if  (  !bSuccess  )  {
				   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  
				   if  (  !SetEvent(  pMtSock->hEventAccept  )  )  goto  errLabel;
				   continue;
			   }

#if  0
			   if  (  lockObj.wLock(  pCliInfo->mutexName_syncSessionOnOff,  pMtSock->uiMilliSeconds_mutex_w,  pCliInfo->hSema_syncSessionOnOff,  pMtSock->uiMilliSeconds_sema_w,  pMtSock->uiInitCnt_sema  )  )  
#else
			   if  (  lockObj.wLock(  pCliInfo->pRw_syncSessionOnOff,  pMtSock->uiMilliSeconds_sema_w  )  )  
#endif
			   {
				   qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "wLock %d failed"  ),  uiCliIndex  ); 						   
				   //
				   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  
				   if  (  !SetEvent(  pMtSock->hEventAccept  )  )  goto  errLabel;
				   continue;					   
			   }

			   pIoContext->dwIoBytes  =  dwIoBytes;
			   getRemoteIpBySocket_iocp(  pMtSock,  pIoContext,  clientIp,  mycountof(  clientIp  )  );

			   if  (  !SetEvent(  pMtSock->hEventAccept  )  )  goto  errLabel;

			   if  (  procIocpAccept(  pMtSock,  uiCliIndex,  clientIp  )  )  {
				   qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "procAccept %d failed"  ),  uiCliIndex  ); 
				   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  					   
			   }

			   continue;
		   }
			   

		   //  注意：这里的 dwIoBytes  ==  0 只能在读写操作中可以作为socket被关闭的条件。所以，必须放在accept处理之后。2008/05/21
		   if  (  !bSuccess  ||  (  bSuccess  &&  (  0  ==  dwIoBytes  )  )  )  {
			   // client connection dropped, continue to service remaining (and possibly 
			   // new) client connections
			   //
			   traceLogA(  "client connection dropped"  );

			   if  (  !uiCliIndex  &&  pPerSocketContext  !=  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[0]  )  {
				   qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "client connection dropped, uiCliIndex %d"  ),  uiCliIndex  ); 
				   continue;
			   }

			   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  					   
			   continue;           
		   }

		   pIoContext->dwIoBytes  =  dwIoBytes;

		   switch  (  pIoContext->ioOperation  )  {

				   case  CONST_io_accept:					     
					     traceLogA(  "得到一个accept消息, 应该在procIocpAccept(  )中处理了啊，到这里就是出错了"  );
						 goto  errLabel;
						 break;

				   case  CONST_io_read:
					     //  traceLogA(  "得到一个read消息, dwIoSize is %d, buf is [%s]",  dwIoBytes,  pIoContext->buf  );
						 break;
				   case  CONST_io_write:
				         //  traceLogA(  "得到一个write消息, dwIoSize is %d, buf is [%s]",  dwIoBytes,  pIoContext->buf  );    
						 break;
				   default:
				           qyShowInfo(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "得到一个错误的ioOperation: %d"  ),  pIoContext->ioOperation  ); 
						   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  					   
						   continue;
						   break;
		   }

		   if  (  pMtSock->servWork.pfDoServWork  )  {
			   int  tmpiRet  =  pMtSock->servWork.pfDoServWork(  (  void  *  )&subThreadInfo,  pPerSocketContext,  pIoContext  );
			   if  (  tmpiRet  )  {
				   if  (  tmpiRet  <  0  )  qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "qmdServWork_mis %d failed"  ),  uiCliIndex  ); 
			   	   if  (  !PostQueuedCompletionStatus(  pMtSock->hIocp,  CONST_misMsgType_closeChannel,  0,  (  LPOVERLAPPED  )uiCliIndex  )  )  qyDisplayLastError(  "postMsg2Iocp failed"  );  					   
			   }
			   continue;
		   }
	
		   continue;
	}
	
	iErr  =  0;

errLabel:

	if  (  bServWorkInited && pMtSock->servWork.pfExitServWork  )  pMtSock->servWork.pfExitServWork(  &subThreadInfo, 0  );

	if  (  subThreadInfo.hMutex  )  {
		ReleaseMutex(  subThreadInfo.hMutex  );		//  为确保所有的Mutex都释放，故在这里强制调用一下ReleaseMutex
		::CloseHandle(  subThreadInfo.hMutex  );	
	}
	
	if  (  iErr  )  pMtSock->bErr  =  TRUE;

	traceLogA(  "mtCliSockThreadProc leaves"  );

	return iErr;

}



 extern  "C"  int  getQyMtSockState(  void  *  pMtSockParam,  MT_SOCK_STATE  *  pState  )
{
	 MT_SOCK_COMMON		*	pMtSock	=	(  MT_SOCK_COMMON  *  )pMtSockParam;
	 //  MT_SOCK  *		pMtSock  =  (  MT_SOCK  *  )pMtSockParam;
	 int			i;

	 if  (  !pMtSock  ||  !pState  )  return  -1;

	 memset(  pState,  0,  sizeof(  pState[0]  )  );						//  2007/03/16
	 pState->nTotalConns  =  pMtSock->servWork.usMaxConns;
	 pState->nBusyConns  =  0;
	 switch  (  pMtSock->servWork.iType  )  {
			 case  CONST_mtSockType_iocp:  
				   pState->nBusyConns  =  (  (  MT_SOCK_IOCP  *  )pMtSock  )->nBusyConns;
				   break;
			 default:
				     for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
						  if  (  (  (  MT_SOCK  *  )pMtSock  )->bUseds[i]  )  pState->nBusyConns  ++  ;
					 }
					 break;
	 }
	 pState->nTotalCliThreads  =  pMtSock->servWork.usMaxProcThreads;
	 if  (  pMtSock->bListenFailed  )  pState->bListenFailed  =  TRUE;	//  2007/03/16
	 if  (  pMtSock->bErr  )  pState->bErr  =  TRUE;
	 return  0;
}


