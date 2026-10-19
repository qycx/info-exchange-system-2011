
#include	"stdafx.h"
#include	"qyCommonEx.h"
#include	"qyDbCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"awmExt.h"
#include	"awmPing.h"

extern  "C"  BOOL  bQyIpOnline(  unsigned  long  ulAddr  );


 int getAwmInterMonCfg( AWM_EXT_CFG *pCfg )
{
	char	buf[15 + 1];
	//  char	tmpBuf[1024];
		
	strcpy(  pCfg->dsnName,  DEFAULT_AWM_EXT_DSN_NAME  );
 	pCfg->waitTimeoutVal   =  DEFAULT_AWM_WAIT_TIMEOUT_VAL;
	pCfg->interMonTcpPort  =  CONST_awmExtInterMonTcpPort;
	
	/*
	if  (  asrGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  AWM_INTER_MON_IP_KEY, buf, sizeof( buf ) ) ){
		debugLog( "getAwmInterMonCfg( ): asrGetRegCfg( ) failed." );
		errLog( "取awmInterMonIp配置失败." );
		return -1;		 
	}
	if  (  inet_addr(  buf  )  ==  INADDR_NONE  )  {
		errLog( "无效awmInterMonIp." );
		debugLog( "无效intermonIp." );
		return -1;
	}
	memcpy( pCfg->interMonIp, buf, MAX_IP_ADDR_LEN  );	pCfg->interMonIp[MAX_IP_ADDR_LEN]  =  0;
	*/

	if  (  !asrGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_newInterMonIp0,  buf,  sizeof(  buf  )  )  
		&&  inet_addr(  buf  )  !=  INADDR_NONE 
			&&  bQyIpOnline(  inet_addr(  buf  )  )  )  
	{
		memcpy(  pCfg->u.interMon.newInterMonIps[0],  buf,  MAX_IP_ADDR_LEN  );  pCfg->u.interMon.newInterMonIps[0][MAX_IP_ADDR_LEN]  =  0;		
		}
	else
		pCfg->u.interMon.newInterMonIps[0][0]  =  0;

	if  (  !asrGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_newInterMonIp1,  buf,  sizeof(  buf  )  )  
		&&  inet_addr(  buf  )  !=  INADDR_NONE  
			&&  bQyIpOnline(  inet_addr(  buf  )  )  )  
	{
		memcpy(  pCfg->u.interMon.newInterMonIps[1],  buf,  MAX_IP_ADDR_LEN  );  pCfg->u.interMon.newInterMonIps[1][MAX_IP_ADDR_LEN]  =  0;		
		}
	else
		pCfg->u.interMon.newInterMonIps[1][0]  =  0;

	/*
	if  (  !qyGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_warnOn,  tmpBuf,  sizeof(  tmpBuf  )  )
		&&  tmpBuf[0]  ==  '1'  )
	{
		pCfg->u.interMon.bWarnOn  =  TRUE;
		if  (  !qyGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_warnUntilUsrStopIt,  tmpBuf,  sizeof(  tmpBuf  )  )  
			&&  tmpBuf[0]  == '1'  )  
		{
			pCfg->u.interMon.bWarnUntilUsrStopIt  =  TRUE;
			}
		else  {
			pCfg->u.interMon.bWarnUntilUsrStopIt  =  FALSE;

			if  (  !qyGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_maxWarnElapseInSecond,  tmpBuf,  sizeof(  tmpBuf  )  )
				&&  atol(  tmpBuf  )  >  5  )
			{
				pCfg->u.interMon.nMaxWarnElapse   =  atol(  tmpBuf  )  *  1000;
				}
			else
				pCfg->u.interMon.nMaxWarnElapse  =  5000;

		}
		
		}
	else  
		pCfg->u.interMon.bWarnOn  =  FALSE;			
	*/
	getQnmWarnCfg(  NULL,  &pCfg->u.interMon.warn  );
	

	qyRefreshRegCfg_ucb(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_stopPermitNat,  &pCfg->u.interMon.ucbStopPermitNat  );
	//  traceLogA(  "%s",  (  pCfg->u.interMon.ucbStopPermitNat  ?  "拒绝NAT"  :  "接收所有包"  )  );


	return 0;

}

 
 int  initAwmInterMon(  AWM_EXT  *  pAE  )
{
	int						iErr					=	0;
	char					buf[1024];
	WORD					wVersionRequested;
	WSADATA					wsaData;     
	CString					errLogCStr,  lckCStr;
	CFile				*	pLckFile				=	NULL;
	DWORD					dwThreadDaemonId;
	MT_SERVWORK				servWork;

	setErrHintWndTitle(  CONST_interMonWndTitle  );
	_snprintf(  pAE->cfg.showWho,  sizeof(  pAE->cfg.showWho  ),  "%s",  CONST_showWho_interMon  );

	
	if  (  sizeof(  AWM_MON_DATA  )  >  REQ_DATASIZE  )  {
		char buf[256];

		sprintf( buf, "sizeof( AWM_MON_DATA ) is %d and REQ_DATASIZE is %d, AWM_MON_DATA 不能大于REQ_DATASIZE", 
			sizeof( AWM_MON_DATA ), REQ_DATASIZE );
		debugLog( buf );
		goto errLabel;
	}
	
	// wVersionRequested = MAKEWORD(1, 1);      
	wVersionRequested  =  MAKEWORD(2, 1);      
	if(WSAStartup(wVersionRequested, &wsaData) == SOCKET_ERROR) {
		debugLog( "initAwmInterMon( ): WSAStartup( ) failed." );
		goto errLabel;
	}      
	pAE->bWsaStartuped = TRUE;

	if( asrGetRegCfg( ROOT_AWM_INTER_MON_KEY, ASR_INSTALL_PATH_KEY, buf, sizeof( buf ) ) ){
		debugLog( "initAwmInterMon( ): asrGetRegCfg( ) failed." );
		return -1;		 
	}
	
	lckCStr = CString( buf ) + CString( "\\temp\\" ) + AWM_INTER_MON_LCK_FILE;
	pLckFile = new CFile( );
	if ( !pLckFile ) goto errLabel;
	if ( !pLckFile->Open( lckCStr, CFile::modeCreate | CFile::shareExclusive ) ) {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "建立文件锁失败."  );
		goto errLabel;
	}
	pAE->pLckFile = pLckFile; pLckFile = NULL;

	errLogCStr = CString( buf ) + CString( "\\temp\\" ) + AWM_INTER_MON_ERR_LOG_FILE;
	setErrLogFile( ( char * )( LPCTSTR )errLogCStr );
	setErrLogHint( AWM_INTER_MON_ERR_LOG_HINT );

	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "启动服务"  );
	qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  pAE->cfg.showWho,  "",  "",  ""  );


	if ( !asrSetRegCfg( ROOT_AWM_INTER_MON_KEY, ASR_START_FLG, "1" ) )  debugLog( "initAwmInterMon( ): startFlg is set." );
	else  debugLog( "initAwmInterMon( ): setting startFlg failed." );

	while  (  1  )  {

			char buf[128] = "999";

			if  (  !asrGetRegCfg( ROOT_AWM_INTER_MON_KEY, ASR_QUIT_KEY, buf, sizeof( buf ) ) ) {
				debugLog( "initAwmInterMon( ) get quit key value is [%s]", buf );
				if  (  atol( buf ) == ASR_QUIT_VAL ) {
					qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "服务将退出"  );
					goto  errLabel;
				}
			}
		
			if  (  !asrGetRegCfg(  ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, buf, sizeof( buf ) ) ) {
				debugLog( "initAwmInterMon( ) get stop key value is [%s]", buf );
				if ( atol( buf ) == ASR_STOP_VAL ) {
					qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "服务已停止"  );
					Sleep( 3000 );
					continue;
				}
			}
		
			break;

	}

	if  (  getAwmInterMonCfg(  &pAE->cfg  )  )  {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "取配置信息失败"  );
		goto  errLabel;
	}
	if  (  !pAE->cfg.u.interMon.newInterMonIps[0][0]  &&  !pAE->cfg.u.interMon.newInterMonIps[1][0]  )  {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "IP配置无效"  );
		goto  errLabel;
	}

	if  (  initQyEnc(  pAE->pEncCtx  )  )  goto  errLabel;
	pAE->bEncCtxInited  =  TRUE;
	if  (  initQnmEnc(  &pAE->qnmEncCtx,  &pAE->qnmUpdateCtx,  NULL,  NULL  )  )  goto  errLabel;
	pAE->bQnmEncCtxInited  =  TRUE;

	if  (  initGenericQ(  &pAE->monDataQ,  objNew,  objFree  )  )  goto errLabel;
	pAE->hMutex = CreateMutex( NULL, FALSE, DEFAULT_INTER_MON_MUTEX );
	if ( !pAE->hMutex ) {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "建互斥量失败"  );
		debugLog( "initAwmInterMon( ): CreateMutex( ) failed." );  goto errLabel;
	}
	debugLog( "%s%s", DEFAULT_INTER_MON_MUTEX, " has been created." );

	/*
	pAE->hThreadInterMon = CreateThread( NULL, 0,  interMonThreadProc, pAE, 0, &dwThreadDaemonId );
	if ( !pAE->hThreadInterMon ) {
		errLog( "interMonThread不能启动." );
		debugLog( "initAwmInterMon( ): CreateThread( ) failed." );
		goto errLabel;
	}
	*/

	if  (  pAE->cfg.u.interMon.newInterMonIps[0][0]  )  {
		pAE->hThreadInterMons[pAE->usThreads]  =  CreateThread( NULL, 0,  interMonThreadProc0, pAE, 0, &dwThreadDaemonId );
		if  (  !pAE->hThreadInterMons[pAE->usThreads]  )  {
			qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "不能启动对%s的监视.",  pAE->cfg.u.interMon.newInterMonIps[0] );
			debugLog(  "initAwmInterMon( ): CreateThread( ) failed." );  goto errLabel;
		}
		pAE->usThreads  ++  ;
	}
	if  (  pAE->cfg.u.interMon.newInterMonIps[1][0]  )  {
		pAE->hThreadInterMons[pAE->usThreads]  =  CreateThread( NULL, 0,  interMonThreadProc1, pAE, 0, &dwThreadDaemonId );
		if  (  !pAE->hThreadInterMons[pAE->usThreads]  )  {
			qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "不能启动对%s的监视.",  pAE->cfg.u.interMon.newInterMonIps[1] );
			debugLog(  "initAwmInterMon( ): CreateThread( ) failed." );  goto errLabel;
		}
		pAE->usThreads  ++  ;
	}

	//  启动Udp的监视	2004/05/23增加
	pAE->hThreadInterMons[pAE->usThreads]  =  CreateThread( NULL, 0,  interMonUdpThreadProc, pAE, 0, &dwThreadDaemonId );
	if  (  !pAE->hThreadInterMons[pAE->usThreads]  )  {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "不能启动对Udp的监视."  );
		debugLog(  "initAwmInterMon( ): CreateThread( ) failed." );  goto errLabel;
	}
	pAE->usThreads  ++  ;

	//  启动tcp的监视
	memset(  &servWork,  0,  sizeof(  servWork  )  );
	servWork.pfDoServWork		=	doInterMonServWork;
	if  (  strlen(  DEFAULT_INTER_MON_MUTEX  )  >=  sizeof(  servWork.mutexName  )  )  goto  errLabel;
	strcpy(  servWork.mutexName,  DEFAULT_INTER_MON_MUTEX  );
	servWork.usMaxConns  =  4;			//  2004/05/22设置了监视端的并发连接数

	if  (  initQyMtSock(  NULL,  pAE->cfg.interMonTcpPort,  &servWork,  (  LPVOID  )pAE  )  )  {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "interMon不能守侯80端口."  );    //  2004/11/12
		goto  errLabel;
	}
	pAE->bMtSockInited  =  TRUE;
	
	pAE->hThreadInterMonDaemon  =  CreateThread(  NULL,  0,  interMonDaemonThreadProc,  pAE,  0,  &dwThreadDaemonId  );
	if  (  !pAE->hThreadInterMonDaemon  )  {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "interMonDaemon不能启动."  );
		debugLog(  "initAwmInterMonDaemon( ): CreateThread( ) failed."  );  
		goto  errLabel;
	}
	
	pAE->hThreadInterMonWarn  =  CreateThread(  NULL,  0,  interMonWarnThreadProc,  pAE,  0,  &dwThreadDaemonId  );
	if  (  !pAE->hThreadInterMonWarn  )  {
		qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "interMonWarn不能启动."  );  
		goto  errLabel;
	}
	
	iErr = 0;

errLabel:

	if  (  iErr  )  {
		exitAwmInterMon( pAE );		
	}
	
	return iErr;

}


 void exitAwmInterMon( AWM_EXT *pAE )
{
	CFile  *	pLckFile	=	NULL;
	DWORD		dwRet;
	int			i;

	debugLog( "exitAwmInterMon( ): enters." );

	pAE->bQuit = TRUE;

	if ( pAE->hThreadInterMonWarn ) {
		// ::WaitForSingleObject( pAE->hThreadInterMonWarn, INFINITE );
		dwRet = ::WaitForSingleObject( pAE->hThreadInterMonWarn, DEFAULT_AWM_WAIT_FOR_THREAD_TIMEOUT );
		if ( dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT ) {
			CloseHandle( pAE->hThreadInterMonWarn ); pAE->hThreadInterMonWarn = NULL;
		}
	}


	if ( pAE->hThreadInterMonDaemon ) {
		// ::WaitForSingleObject( pAE->hThreadInterMonDaemon, INFINITE );
		dwRet = ::WaitForSingleObject( pAE->hThreadInterMonDaemon, DEFAULT_AWM_WAIT_FOR_THREAD_TIMEOUT );
		if ( dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT ) {
			CloseHandle( pAE->hThreadInterMonDaemon ); pAE->hThreadInterMonDaemon = NULL;
		}
	}

	if  (  pAE->bMtSockInited  )  {
		exitQyMtSock(  );  pAE->bMtSockInited  =  FALSE;
	}

	for  (  i  =  0;  i  <  pAE->usThreads;  i  ++  )  {
		 if  (  pAE->hThreadInterMons[i]  )  {
			 // ::WaitForSingleObject( pAE->hThreadInterMon, INFINITE );
			 dwRet = ::WaitForSingleObject( pAE->hThreadInterMons[i], DEFAULT_AWM_WAIT_FOR_THREAD_TIMEOUT );
			 if  (  dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT ) {
				 CloseHandle( pAE->hThreadInterMons[i] ); pAE->hThreadInterMons[i] = NULL;
			 }
		 }
	}

	if ( pAE->hMutex ) {
		CloseHandle( pAE->hMutex ); pAE->hMutex = NULL; 
	}

	exitGenericQ( &pAE->monDataQ );
	
	if  (  pAE->bQnmEncCtxInited  )  {
		exitQnmEnc(  &pAE->qnmEncCtx,  &pAE->qnmUpdateCtx,  NULL,  NULL  );  pAE->bQnmEncCtxInited  =  FALSE;
	}
	if  (  pAE->bEncCtxInited  )  {
		exitQyEnc(  pAE->pEncCtx  );  pAE->bEncCtxInited  =  FALSE;
	}

	if ( pAE->pLckFile ) pLckFile = ( CFile * )pAE->pLckFile;

	if ( pLckFile ) {
		pLckFile->Close( );
		delete pLckFile;
	}
	
	if ( pAE->bWsaStartuped ) {
		WSACleanup( ); pAE->bWsaStartuped = FALSE;
	}


	debugLog( "exitAwmInterMon( ): leaves." );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "服务结束." );

	return;

}


#define		STATUS_FAILED			0xFFFF	//  定义异常出错代码
#define		MAX_PACK_LEN			65535	//  接收的最大IP报文
#define		MAX_ADDR_LEN			16		//  点分十进制地址的最大长度
#define		MAX_HOSTNAME_LAN		255		//  最大主机名长度
#define		DEFAULT_SNIFF_PORT		9192

 DWORD WINAPI interMonThreadProc0( LPVOID lpParam )
{
	AWM_EXT			*			pAE			=	(  AWM_EXT  *  )lpParam;
	LPCSTR						pstrHost	=	"localhost";
	SOCKET						rawSocket	=	-1;
	struct	sockaddr_in			saSrc;
	DWORD						dwTimeSent;
	DWORD						dwElapsed;
	u_char						cTTL;
	//	int						nLoop;
	int							nRet;
	INTER_MON_THREAD_PROC_INFO	iMTPI;

	debugLog(  "interMonThreadProc( ): starts..."  );
	OutputDebugString(  "interMonThreadProc( ): starts...\n"  );

	memset( &iMTPI, 0, sizeof( iMTPI ) );
	iMTPI.hMutex = CreateMutex( NULL, FALSE, DEFAULT_INTER_MON_MUTEX );
	if ( !iMTPI.hMutex ) {
		debugLog( "CreateMutex( ) failed. mutexName is [%s]", DEFAULT_INTER_MON_MUTEX );
		errLog( "interMonThread: 建互斥量失败." );
		goto errLabel;
	}

	// Create a Raw socket
	//  rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	rawSocket  =  socket(  AF_INET,  SOCK_RAW,  IPPROTO_IP  );//  2004/05/22将上面的语句改为这一句，因为在XP上TCP包收不到
	//rawSocket = socket( AF_INET, SOCK_RAW, IPPROTO_RAW );
	if ( rawSocket == SOCKET_ERROR ) {
		debugLog( "create a raw socket failed." );
		errLog( "interMonThread: 建socket失败." );
		goto errLabel;
	}
	
	char FAR name[MAX_HOSTNAME_LAN];
	if ( gethostname(name, MAX_HOSTNAME_LAN) ) {
		debugLog( "gethostname( ) failed." );
		errLog( "interMonThread: 取主机名失败." );
		goto errLabel;
	}
	struct hostent FAR * pHostent;
	pHostent = gethostbyname(name);
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons( DEFAULT_SNIFF_PORT );
	memcpy(&sa.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
	// sa.sin_addr.S_un.S_addr  =  inet_addr( pAE->cfg.interMonIp );  	 
	sa.sin_addr.S_un.S_addr  =  inet_addr(  pAE->cfg.u.interMon.newInterMonIps[0]  );	

	memcpy(  &iMTPI.sa,  &sa,  sizeof(  SOCKADDR_IN  )  );

	if ( bind(rawSocket, (PSOCKADDR)&sa, sizeof(sa) ) ) {
		debugLog( "bind( ) failed." );
		errLog( "绑定[%s]失败.", inet_ntoa( sa.sin_addr ) );
		goto errLabel;
	}
	//  errLog( "[%s]已绑定", inet_ntoa( sa.sin_addr ) );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "[%s]已绑定",  inet_ntoa(  sa.sin_addr  )  );

	
	//设置SOCK_RAW为SIO_RCVALL，以便接收所有的IP包
	{
		DWORD dwBufferLen[10] ;
		DWORD dwBufferInLen = 1 ;
		DWORD dwBytesReturned = 0 ;
		int iRet;
	
		iRet = WSAIoctl( rawSocket, SIO_RCVALL, &dwBufferInLen, sizeof( dwBufferInLen ),
				&dwBufferLen, sizeof( dwBufferLen ), &dwBytesReturned, NULL, NULL );
		if ( iRet ) {
			debugLog( "ioctl( ) failed." );
			errLog( "interMonThread: 系统调用ioctl失败." );
			goto errLabel;
		}
	}

	debugLog( "interMonThreadProc( ): before loop." );
	//  errLog( "开始监视...%s",  pAE->cfg.u.interMon.newInterMonIps[0]  );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "开始监视...%s",  pAE->cfg.u.interMon.newInterMonIps[0]  );

	
	while ( !pAE->bQuit ) {
		
		//  OutputDebugString( "interMonThreadProc( ): starts a new loop...\n" );
		//  debugLog( "interMonThreadProc( ): starts a new loop..." );
		//  asrShowRegStatus( ROOT_AWM_INTER_MON_KEY, "interMonThreadProc: starts a new loop..." );

		nRet = WaitForEchoReply(rawSocket);
		if (nRet == SOCKET_ERROR) {
			OutputDebugString( "select( ) failed.");
			break;
		}
		if (!nRet) {
			OutputDebugString( "\nTimeOut" );
			continue;
		}

		// Receive reply
		dwTimeSent = RecvEchoReply( pAE, rawSocket, &saSrc, &cTTL, &iMTPI );

		// Calculate elapsed time
		dwElapsed = GetTickCount() - dwTimeSent;
		printf("\nReply from: %s: bytes=%d time=%ldms TTL=%d", 
               inet_ntoa(saSrc.sin_addr), 
			   REQ_DATASIZE,
               dwElapsed,
               cTTL);

		// Sleep( 200 );
	}

errLabel:

	if  (  iMTPI.hMutex  )  {
		CloseHandle(  iMTPI.hMutex  );
	}

	if  (  rawSocket  >=  0  )  {
		nRet = closesocket( rawSocket );
		if ( nRet == SOCKET_ERROR )
			ReportError("closesocket()");
	}

	debugLog( "interMonThreadProc( ) ends." );
	//  errLog( "结束对%s的监视",  pAE->cfg.u.interMon.newInterMonIps[0]  );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "结束对%s的监视",  pAE->cfg.u.interMon.newInterMonIps[0]  );  

	OutputDebugString( "interMonThreadProc( ) ends.\n" );

	return 0;
	
}


 DWORD WINAPI interMonThreadProc1( LPVOID lpParam )
{
	AWM_EXT *pAE = ( AWM_EXT * )lpParam;
	LPCSTR pstrHost = "localhost";
	SOCKET	  rawSocket = -1;
	struct    sockaddr_in saSrc;
	DWORD	  dwTimeSent;
	DWORD	  dwElapsed;
	u_char    cTTL;
	//	int       nLoop;
	int       nRet;
	INTER_MON_THREAD_PROC_INFO iMTPI;

	debugLog( "interMonThreadProc( ): starts..." );
	OutputDebugString( "interMonThreadProc( ): starts...\n" );


	memset( &iMTPI, 0, sizeof( iMTPI ) );
	iMTPI.hMutex = CreateMutex( NULL, FALSE, DEFAULT_INTER_MON_MUTEX );
	if ( !iMTPI.hMutex ) {
		debugLog( "CreateMutex( ) failed. mutexName is [%s]", DEFAULT_INTER_MON_MUTEX );
		errLog( "interMonThread: 建互斥量失败." );
		goto errLabel;
	}

	// Create a Raw socket
	//  rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	rawSocket  =  socket(  AF_INET,  SOCK_RAW,  IPPROTO_IP  );			//  2004/05/22将上面的语句改为这一句，因为在XP上TCP包收不到
	//rawSocket = socket( AF_INET, SOCK_RAW, IPPROTO_RAW );
	if ( rawSocket == SOCKET_ERROR ) {
		debugLog( "create a raw socket failed." );
		errLog( "interMonThread: 建socket失败." );
		goto errLabel;
	}
	
	char FAR name[MAX_HOSTNAME_LAN];
	if ( gethostname(name, MAX_HOSTNAME_LAN) ) {
		debugLog( "gethostname( ) failed." );
		errLog( "interMonThread: 取主机名失败." );
		goto errLabel;
	}
	struct hostent FAR * pHostent;
	pHostent = gethostbyname(name);
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons( DEFAULT_SNIFF_PORT );
	memcpy(&sa.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
	sa.sin_addr.S_un.S_addr  =  inet_addr(  pAE->cfg.u.interMon.newInterMonIps[1]  );	

	memcpy(  &iMTPI.sa,  &sa,  sizeof(  SOCKADDR_IN  )  );																						
																						
	if ( bind(rawSocket, (PSOCKADDR)&sa, sizeof(sa) ) ) {
		debugLog( "bind( ) failed." );
		errLog( "interMonThread: 绑定[%s]失败.", inet_ntoa( sa.sin_addr ) );
		goto errLabel;
	}
	//  errLog( "interMonThread: [%s]已绑定", inet_ntoa( sa.sin_addr ) );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "interMonThread: [%s]已绑定",  inet_ntoa(  sa.sin_addr  )  );  

	
	//设置SOCK_RAW为SIO_RCVALL，以便接收所有的IP包
	{
		DWORD dwBufferLen[10] ;
		DWORD dwBufferInLen = 1 ;
		DWORD dwBytesReturned = 0 ;
		int iRet;
	
		iRet = WSAIoctl( rawSocket, SIO_RCVALL, &dwBufferInLen, sizeof( dwBufferInLen ),
				&dwBufferLen, sizeof( dwBufferLen ), &dwBytesReturned, NULL, NULL );
		if ( iRet ) {
			debugLog( "WSAIoctl( ) failed." );
			errLog( "interMonThread: 系统调用ioctl失败." );
			goto errLabel;
		}
	}

	debugLog( "interMonThreadProc( ): before loop." );
	//  errLog( "开始监视...%s",  pAE->cfg.u.interMon.newInterMonIps[1]  );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "开始监视...%s",  pAE->cfg.u.interMon.newInterMonIps[1]  );  

	
	while ( !pAE->bQuit ) {
		
		//  OutputDebugString( "interMonThreadProc( ): starts a new loop...\n" );
		//  debugLog( "interMonThreadProc( ): starts a new loop..." );
		//  asrShowRegStatus( ROOT_AWM_INTER_MON_KEY, "interMonThreadProc: starts a new loop..." );

		nRet = WaitForEchoReply(rawSocket);
		if (nRet == SOCKET_ERROR) {
			OutputDebugString( "select( ) failed.");
			break;
		}
		if (!nRet) {
			OutputDebugString( "\nTimeOut" );
			continue;
		}

		// Receive reply
		dwTimeSent = RecvEchoReply( pAE, rawSocket, &saSrc, &cTTL, &iMTPI );

		// Calculate elapsed time
		dwElapsed = GetTickCount() - dwTimeSent;
		//  traceLogA(  "\nReply from: %s: bytes=%d time=%ldms TTL=%d",  inet_ntoa(  saSrc.sin_addr  ),  REQ_DATASIZE,  dwElapsed,  cTTL  );

		// Sleep( 200 );
	}

errLabel:

	if ( iMTPI.hMutex ) {
		CloseHandle( iMTPI.hMutex );
	}

	if ( rawSocket >= 0 ) {
		nRet = closesocket( rawSocket );
		if ( nRet == SOCKET_ERROR )
			ReportError("closesocket()");
	}

	debugLog( "interMonThreadProc( ) ends." );
	//  errLog( "结束对%s的监视",  pAE->cfg.u.interMon.newInterMonIps[1]  );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "结束对%s的监视",  pAE->cfg.u.interMon.newInterMonIps[1]  );
	OutputDebugString( "interMonThreadProc( ) ends.\n" );

	return 0;
	
}


 DWORD WINAPI interMonUdpThreadProc( LPVOID lpParam )
{
	AWM_EXT		*				pAE				=	( AWM_EXT * )lpParam;
	LPCSTR						pstrHost		=	"localhost";
	SOCKET						s				=	-1;
	struct  sockaddr_in			saSrc;
	DWORD						dwTimeSent;
	u_char						cTTL;
	//	int						nLoop;
	int							nRet;
	INTER_MON_THREAD_PROC_INFO	iMTPI;

	debugLog( "interMonUdpThreadProc( ): starts..." );
	
	memset( &iMTPI, 0, sizeof( iMTPI ) );
	iMTPI.hMutex = CreateMutex( NULL, FALSE, DEFAULT_INTER_MON_MUTEX );
	if ( !iMTPI.hMutex ) {
		debugLog( "CreateMutex( ) failed. mutexName is [%s]", DEFAULT_INTER_MON_MUTEX );
		errLog( "interMonThread: 建互斥量失败." );  goto errLabel;
	}

	s  =  socket(  AF_INET,  SOCK_DGRAM,  0  );
    if  (  s  ==  INVALID_SOCKET  )  {
        traceLogA(  "socket() failed; %d\n", WSAGetLastError()  );  goto  errLabel;
    }
	SOCKADDR_IN		sa;
	sa.sin_family		=	AF_INET;
	sa.sin_port			=	htons(  DEFAULT_UDP_PORT  );
	sa.sin_addr.s_addr	=	htonl(  INADDR_ANY  );

	memcpy(  &iMTPI.sa,  &sa,  sizeof(  SOCKADDR_IN  )  );																						
																						
	if  (  bind(  s,  (  PSOCKADDR  )&sa,  sizeof(  sa  )  )  )  {
		errLog( "interMonThread: 绑定[%s]失败.", inet_ntoa( sa.sin_addr ) );
		debugLog( "bind( ) failed." );  goto errLabel;
	}
	errLog( "interMonThread: [%s]已绑定", inet_ntoa( sa.sin_addr ) );
		
	while ( !pAE->bQuit ) {
		
		//  OutputDebugString( "interMonThreadProc( ): starts a new loop...\n" );
		//  debugLog( "interMonThreadProc( ): starts a new loop..." );
		//  asrShowRegStatus( ROOT_AWM_INTER_MON_KEY, "interMonThreadProc: starts a new loop..." );

		nRet = WaitForEchoReply(  s  );
		if  (  nRet  ==  SOCKET_ERROR  )  {
			OutputDebugString( "select( ) failed.");
			break;
		}
		if  (  !nRet  )  {
			OutputDebugString( "\nTimeOut" );  continue;
		}

		// Receive reply
		dwTimeSent = RecvUdpReply( pAE, s, &saSrc, &cTTL, &iMTPI );

	}

errLabel:

	if ( iMTPI.hMutex ) {
		CloseHandle( iMTPI.hMutex );
	}

	if  (  s  >=  0  )  {
		nRet  =  closesocket(  s  );
		if  (  nRet  ==  SOCKET_ERROR  )  ReportError("closesocket()");
	}

	debugLog( "interMonUdpThreadProc( ) ends." );
	
	return  0;
	
}


 int processMonDataQ( AWM_EXT *pAE, INTER_MON_DAEMON_THREAD_PROC_INFO *pIMDTPI )
{
	int					iErr		=	-1;
	DWORD				dwRet;
	BOOL				bWaited		=	FALSE;
	AWM_MON_DATAEx		amd;
	//  SCANNING_LOG_TAB_RCD sLTR;
	CString				sqlCStr;
	CDatabase		*	pDb			=	(  CDatabase  *  )pIMDTPI->pDb;
	char				computerInfoBuf[MAX_AWM_MON_OFFICE_NAME_LEN  +  MAX_AWM_MON_SUB_OFFICE_NAME_LEN  +  MAX_IP_ADDR_LEN  +  CONST_qyMacLen  +  CONST_maxAwmMonCompNameLen  +  CONST_maxAwmMonUsrNameLen	 +  CONST_maxAwmMonIsServerLen  +  1];
	char			*	p;
	unsigned  int		fieldSize;
	unsigned  long		ulIp;
	char				isServerBuf[2];
	char			*	pIp;
	char			*	tmpPtr;
	
	while (  pAE->monDataQ.nQNoes  >  0  )  {
		  dwRet  =  WaitForSingleObject(  pIMDTPI->hMutex,  pAE->cfg.waitTimeoutVal  );
		  if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
				
		  bWaited = TRUE;
		  if  (  getMsg(  &pAE->monDataQ,  &amd,  sizeof(  amd  )  )  )  {
			  debugLog( "processMonDataQ( ): getMsg( ) failed." );  goto  errLabel;
		  }
		  ReleaseMutex(  pIMDTPI->hMutex  );  bWaited  =  FALSE;

		  ////////////////////

		  memset(  computerInfoBuf,  ' ',  sizeof(  computerInfoBuf  )  -  1  );
		  computerInfoBuf[sizeof(  computerInfoBuf  )  -  1]  =  0;
		  p  =  computerInfoBuf;  fieldSize  =  MAX_AWM_MON_OFFICE_NAME_LEN;
		  memcpy(  p,  amd.officeName,  min(  fieldSize,  strlen(  (  char  *  )amd.officeName  )  )  );
		  p  +=  fieldSize;  fieldSize  =  MAX_AWM_MON_SUB_OFFICE_NAME_LEN;
		  memcpy(  p,  amd.subOfficeName,  min(  fieldSize,  strlen(  (  char  *  )amd.subOfficeName  )  )  );
		  p  +=  fieldSize;  fieldSize  =  MAX_IP_ADDR_LEN;
		  memcpy(  (  char  *  )&ulIp,  (  char  *  )amd.ucIp,  sizeof(  ulIp  )  );
		  if  (  !(  pIp  =  inet_ntoa(  *(  in_addr  *  )&ulIp  )  )  )  continue;
		  memcpy(  p,  pIp,  min(  fieldSize,  strlen(  pIp  )  )  );
		  p  +=  fieldSize;  fieldSize  =  CONST_qyMacLen;
		  memcpy(  p,  amd.mac,  min(  fieldSize,  strlen(  amd.mac  )  )  );
		  p  +=  fieldSize;  fieldSize  =  CONST_maxAwmMonCompNameLen;
		  //  处理一下计算机名，过滤掉~
		  if  (  (  tmpPtr  =  strchr(  amd.compName,  '~'  )  )  )  _snprintf(  amd.compName,  sizeof(  amd.compName  ),  "%s",  tmpPtr  +  1  );
		  memcpy(  p,  amd.compName,  min(  fieldSize,  strlen(  amd.compName  )  )  );
		  p  +=  fieldSize;  fieldSize  =  CONST_maxAwmMonUsrNameLen;
		  //  处理一下用户名，过滤掉乱码
		  for  (  tmpPtr  =  amd.usrName;  *tmpPtr  &&  tmpPtr  <  amd.usrName  +  sizeof(  amd.usrName  );  tmpPtr  ++  )  {
			   if  (  !isascii(  *tmpPtr  )  )  continue;	//  中文
			   if  (  qyIsDigit(  *tmpPtr  )  )  continue;
			   if  (  qyIsAlpha(  *tmpPtr  )  )  continue;
			   if  (  qyIsSpace(  *tmpPtr  )  )  continue;
			   if  (  *tmpPtr  ==  '.'  )  continue;
			   *tmpPtr  =  0;  break;						//  截掉了
		  }
		  memcpy(  p,  (  char  *  )amd.usrName,  min(  fieldSize,  strlen(  (  char  *  )amd.usrName  )  )  );
		  p  +=  fieldSize;  fieldSize  =  CONST_maxAwmMonIsServerLen;
		  _snprintf(  isServerBuf,  sizeof(  isServerBuf  ),  "%s",  (  amd.is_server  ?  "1"  :  "0"  )  );
		  memcpy(  p,  isServerBuf,  min(  fieldSize,  strlen(  isServerBuf  )  )  );
		  
		  traceLogA(  "computerInfo is [%s]",  computerInfoBuf  );
  		  		  
		  qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "收到 %s 的 %s ",  pIp  ?  pIp  :  "",  amd.hint  );

		  sqlCStr  =  CString( "insert into originalLogTab( computerInfo, recvdTime ) values( " )
					  + "'" + computerInfoBuf + "'"
					  + "," + "'" + amd.recvdTime + "'"
					  + ")";

		  if  (  !bQyExecSql(  pDb,  sqlCStr.GetBuffer(  0  )  )  )  goto  errLabel;
			  
	}

	iErr = 0;

errLabel:
	if  (  bWaited  )  {
		ReleaseMutex(  pIMDTPI->hMutex  );
	}
	return  iErr;

}

  CTime getCTimeByQyTime(  char  *  timeBuf  )
{
	 char	year[5],  month[3],  day[3],  hour[3],  minute[3],  second[3];
	 memcpy(  year,  timeBuf,  4  );  year[4]  =  0;  timeBuf  +=  4;
	 memcpy(  month,  timeBuf,  2  );  month[2]  =  0;  timeBuf  +=  2;
	 memcpy(  day,  timeBuf,  2  );  day[2]  =  0;  timeBuf  +=  2;
	 memcpy(  hour,  timeBuf,  2  );  hour[2]  =  0;  timeBuf  +=  2;
	 memcpy(  minute,  timeBuf,  2  );  minute[2]  =  0;  timeBuf  +=  2;
	 memcpy(  second,  timeBuf,  2  );  second[2]  =  0;  timeBuf  +=  2;

	 CTime  t(  atol(  year  ),  atol(  month  ),  atol(  day  ),  atol(  hour  ),  atol(  minute  ),  atol(  second  )  );

	 return  t;

}

 //  interMonWarnThreadProc ..  提供对告警的处理，告警条件为：
 //							1、bWarnOn标志位打开
 //							&&
 //							2、bNew标志位为'1'
 //							&&
 //							3、( 持续告警标志位打开直到用户使用界面
 //							|| 告警时间已过 )
 DWORD  WINAPI  interMonWarnThreadProc(  LPVOID  lpParam  )
{
	AWM_EXT  *  pAE										=		(  AWM_EXT  *  )lpParam;
	char		timeBuf[CONST_qyTimeLen  +  1];
	char		curTimeBuf[CONST_qyTimeLen  +  1];
	CTime		eventT,  curT;
	CTimeSpan	tDiff;
	BOOL		bNew;
	
	while  (  !pAE->bQuit  )  {

		   if  (  pAE->cfg.u.interMon.warn.bWarnOn  
			   &&  !getQnmWarnInfo(  pAE,  timeBuf,  sizeof(  timeBuf  ),  &bNew  )  
				   &&  bNew  )  
		   {
			   
			   if  (  !pAE->cfg.u.interMon.warn.bWarnUntilUsrStopIt  )  {
				   getCurTime(  curTimeBuf  );
			   	   eventT  =  getCTimeByQyTime(  timeBuf  );
			   	   curT  =  getCTimeByQyTime(  curTimeBuf  );
				   tDiff  =  curT  -  eventT;
				   traceLogA(  "tDiff is %d seconds",   tDiff.GetTotalSeconds(  )  );
				   if  (  curT  <  eventT  
					   ||  (  tDiff.GetTotalSeconds(  )  *  1000  )  >  (  int  )pAE->cfg.u.interMon.warn.nMaxWarnElapse  )
				   {
					   clearQnmWarnFlg(  pAE  );
					   bNew  =  FALSE;
				   }				   
			   }

			   if  (  bNew  )  MessageBeep(  MB_OK  );
						   
			   Sleep(  1000  );
			   continue;

		   }

		   Sleep(  5000  );		   

	}
  
	return  0;
}

 DWORD WINAPI interMonDaemonThreadProc( LPVOID lpParam )
{
	AWM_EXT *pAE = ( AWM_EXT * )lpParam;
	INTER_MON_DAEMON_THREAD_PROC_INFO iMDTPI;
	BOOL bWaited = FALSE;
	CDatabase tmpDb;

	debugLog( "interMonDaemonThreadProc( ) starts..." );
	OutputDebugString( "interMonDaemonThreadProc( ) starts...\n" );

	TRY {
		if ( !tmpDb.Open( pAE->cfg.dsnName ) ) {
			debugLog( "db.Open( ) failed." );
			asrShowRegErr( ROOT_AWM_INTER_MON_KEY, "db.Open failed." );
			goto errLabel;
		}
		}
	CATCH ( CDBException, e ) {
		asrShowRegErr( ROOT_AWM_INTER_MON_KEY, "db.Open failed." );
		debugLog( "interMonThreadProc( ) the caught err is:[%s]", e->m_strError );
		goto errLabel;
		}
	END_CATCH

	debugLog( "db is Opened." );

	memset( &iMDTPI, 0, sizeof( iMDTPI ) );
	iMDTPI.hMutex = CreateMutex( NULL, FALSE, DEFAULT_INTER_MON_MUTEX );
	if ( !iMDTPI.hMutex ) {
		goto errLabel;
	}

	iMDTPI.pDb = ( void * )&tmpDb;

	while  (  !pAE->bQuit  )  {

		   OutputDebugString( "interMonDaemonThreadProc( ): starts a new loop...\n" );
		   if  (  pAE->monDataQ.nQNoes  <=  0  )  {
			   Sleep( 3000 );  continue;
		   }
	
		   processMonDataQ( pAE, &iMDTPI );

		   Sleep( 5000 );

	}

errLabel:
	
	if ( iMDTPI.hMutex ) {
		CloseHandle( iMDTPI.hMutex ); 
	}

	if ( tmpDb.IsOpen( ) ) tmpDb.Close( );

	debugLog( "interMonDaemonThreadProc( ) ends." );
	OutputDebugString( "interMonDaemonThreadProc( ) ends.\n" );

	return 0;

}

 void awmInterMonMain( )
{
	// char buf[1024];
	// void Ping(LPCSTR pstrHost)
	// LPCSTR pstrHost = "localhost";
	// SOCKET	  rawSocket = -1;
	// struct    sockaddr_in saSrc;
	// DWORD	  dwTimeSent;
	// DWORD	  dwElapsed;
	// u_char    cTTL;
	// int       nLoop;
	// int       nRet;
	AWM_EXT		awmExt;
	//  _CrtMemState s1, s2, s3;

	setDebugLogFileName( "errInter.log" );
	
	//  _CrtMemCheckpoint( &s1 );
	debugLog( "awmInterMonMain( ): starts..." );
	asrShowRegStatus( ROOT_AWM_INTER_MON_KEY, "starts..." );
	
	memset( &awmExt, 0, sizeof( awmExt ) );
	if ( initAwmInterMon( &awmExt ) ) return;

	awmInterMonRun( &awmExt );

	// Create a Raw socket
	// rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	// rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	//rawSocket = socket( AF_INET, SOCK_RAW, IPPROTO_RAW );
	// if ( rawSocket == SOCKET_ERROR ) {
	//	ReportError("socket()");
	//	goto errLabel;
	// }
	
	// char FAR name[MAX_HOSTNAME_LAN];
	// if ( gethostname(name, MAX_HOSTNAME_LAN) ) goto errLabel;
	// struct hostent FAR * pHostent;
	// pHostent = gethostbyname(name);
	// SOCKADDR_IN sa;
	// sa.sin_family = AF_INET;
	// sa.sin_port = htons( DEFAULT_SNIFF_PORT );
	// memcpy(&sa.sin_addr.S_un.S_addr, pHostent->h_addr_list[0], pHostent->h_length);
	// if ( bind(rawSocket, (PSOCKADDR)&sa, sizeof(sa) ) ) goto errLabel;
	//设置SOCK_RAW为SIO_RCVALL，以便接收所有的IP包
	// {
	// 	DWORD dwBufferLen[10] ;
	// 	DWORD dwBufferInLen = 1 ;
	// 	DWORD dwBytesReturned = 0 ;
	// 	int iRet;
	
	//	iRet = WSAIoctl( rawSocket, SIO_RCVALL, &dwBufferInLen, sizeof( dwBufferInLen ),
	//			&dwBufferLen, sizeof( dwBufferLen ), &dwBytesReturned, NULL, NULL );
	//	if ( iRet ) goto errLabel;
	// }
	
	// Ping multiple times
	// for ( nLoop = 0; ; nLoop++ ) {
		// Send ICMP echo request
		// SendEchoRequest(rawSocket, &saDest);

		// Use select() to wait for data to be received
	//	nRet = WaitForEchoReply(rawSocket);
	//	if (nRet == SOCKET_ERROR) {
	//		OutputDebugString( "select( ) failed.");
	//		break;
	//	}
	//	if (!nRet) {
	//		OutputDebugString( "\nTimeOut" );
	//		continue;
	//	}

		// Receive reply
	//	dwTimeSent = RecvEchoReply( &awmExt, rawSocket, &saSrc, &cTTL );

		// Calculate elapsed time
	//	dwElapsed = GetTickCount() - dwTimeSent;
	//	printf("\nReply from: %s: bytes=%d time=%ldms TTL=%d", 
    //           inet_ntoa(saSrc.sin_addr), 
	//		   REQ_DATASIZE,
    //           dwElapsed,
    //           cTTL);
	// }
	// printf("\n");
	
// errLabel:

	// if ( rawSocket >= 0 ) {
	//	nRet = closesocket(rawSocket);
	//	if (nRet == SOCKET_ERROR)
	//		ReportError("closesocket()");
	// }


	exitAwmInterMon( &awmExt );

	debugLog( "awmInterMonMain( ): ends." );
	asrShowRegStatus( ROOT_AWM_INTER_MON_KEY, "ends." );
	
	//  _CrtMemCheckpoint( &s2 );

	//  if ( _CrtMemDifference( &s3, &s1, &s2 ) )  _CrtMemDumpStatistics( &s3 );

	//  _CrtDumpMemoryLeaks( );

	return;
}

 int awmInterMonRun( AWM_EXT *pAE )
{
	char	buf[256];
	DWORD	dwRet;
	char	interMonIpBuf[sizeof(  pAE->cfg.interMonIp  )];
	char	interMonIps[2][MAX_IP_ADDR_LEN  +  1];
	int		tmpI	=	0;

	memcpy(  interMonIpBuf,  pAE->cfg.interMonIp,  sizeof(  interMonIpBuf  )  -  1  );
	interMonIpBuf[sizeof(  interMonIpBuf  )  -  1]  =  0;
	strcpy(  interMonIps[0],  pAE->cfg.u.interMon.newInterMonIps[0]  );
	strcpy(  interMonIps[1],  pAE->cfg.u.interMon.newInterMonIps[1]  );

	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  CONST_showWho_interMon,  "",  "",  "监视...%s  %s",  pAE->cfg.u.interMon.newInterMonIps[0],  pAE->cfg.u.interMon.newInterMonIps[1]  );

	while ( TRUE ) {

		if  (  tmpI  >  5  )  {
			qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  pAE->cfg.showWho,  "",  "",  "  监视...%s  %s",  pAE->cfg.u.interMon.newInterMonIps[0],  pAE->cfg.u.interMon.newInterMonIps[1]  );
		}
		tmpI  ++  ;
		
		if  (  !asrGetRegCfg( ROOT_AWM_INTER_MON_KEY, ASR_QUIT_KEY, buf, sizeof( buf ) ) ) {
			//  debugLog( "awmInterMonRun( ) get quit key value is [%s]", buf );
			if  (  atol(  buf  )  ==  ASR_QUIT_VAL  )  break;
		}
		if  (  !asrGetRegCfg( ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, buf, sizeof( buf ) ) ) {
			//  debugLog( "awmInterMonRun( ) get stop key value is [%s]", buf );
			if  (  atol( buf ) == ASR_STOP_VAL )  break;
		}
		if  (  getAwmInterMonCfg(  &pAE->cfg  )  )  {
			debugLog(  "awmIntraMonRun( ): getAwmIntraMonCfg( ) failed." );
			break;
		}
		if  (  strcmp(  pAE->cfg.interMonIp,  interMonIpBuf  )  )  {
			debugLog(  "awmInterMonRun(  ):  interMonIp has been changed."  );
			break;
		}
		if  (  strcmp(  pAE->cfg.u.interMon.newInterMonIps[0],  interMonIps[0]  )  
			||  strcmp(  pAE->cfg.u.interMon.newInterMonIps[1],  interMonIps[1]  )  )
		{
			qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  pAE->cfg.showWho,  "",  "",  "  IP配置已改变."    );
			break;
		}
		for  (  int  i  =  0;  i  <  pAE->usThreads;  i  ++  )  {
			 if  (  pAE->hThreadInterMons[i]  )  {
				 dwRet = ::WaitForSingleObject( pAE->hThreadInterMons[i], 1000 );
				 if ( dwRet != WAIT_TIMEOUT ) {
					 debugLog( "hThreadInterMon failed." );
					 break;
				 }
			 }
		}

		dwRet = ::WaitForSingleObject( pAE->hThreadInterMonDaemon, 1000 );
		if ( dwRet != WAIT_TIMEOUT ) {
			debugLog( "hThreadInterMonDaemon failed." );
			break;
		}
		debugLog( "awmInterMonRun( )" );
		Sleep( 1000 );
	
	}

	return 0;

}



