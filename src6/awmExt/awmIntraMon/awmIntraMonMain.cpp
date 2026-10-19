
#include	"stdafx.h"
#include	"awmExt.h"




 int  getAwmIntraMonCfg(  AWM_EXT_CFG  *  pCfg  )
{
	char	buf[256];
	int		nScanIntervalInSecond				=  CONST_min_nScanIntervalInSecond;
	int		nScanIntervalPerCNetSegInSecond		=  CONST_min_nScanIntervalPerCNetSegInSecond;
	int		nScanIntervalPerPcInMilliSecond		=  0;


	//  strcpy(  pCfg->dsnName,  DEFAULT_AWM_EXT_DSN_NAME  );  //  2003/11/25为实现安检系统的融合，将dsnName的宏定义作了修改
	_snprintf(  pCfg->dsnName,  sizeof(  pCfg->dsnName  ),  "%s",  DEFAULT_AWM_EXT_DSN_NAME  );
	pCfg->interMonTcpPort  =  CONST_awmExtInterMonTcpPort;

	if  (  !asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_scanIntervalInSecond,  buf,  sizeof(  buf  )  )  )  {
		nScanIntervalInSecond  =  atol(  buf  );
	}
	if  (  nScanIntervalInSecond  >  CONST_max_nScanIntervalInSecond  ||  nScanIntervalInSecond  <  CONST_min_nScanIntervalInSecond  )  {
		nScanIntervalInSecond  =  CONST_min_nScanIntervalInSecond;
	}
	pCfg->u.intraMon.nScanInterval  =  (  nScanIntervalInSecond  *  1000  );

	if  (  !asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_scanIntervalPerCNetSegInSecond,  buf,  sizeof(  buf  )  )  )  {
		nScanIntervalPerCNetSegInSecond  =  atol(  buf  );
	}
	if  (  nScanIntervalPerCNetSegInSecond  >  CONST_max_nScanIntervalPerCNetSegInSecond  ||  nScanIntervalPerCNetSegInSecond  <  CONST_min_nScanIntervalPerCNetSegInSecond  )  {
		nScanIntervalPerCNetSegInSecond  =  DEFAULT_nScanIntervalPerCNetSegInSecond;
	}
	pCfg->u.intraMon.nScanIntervalPerCNetSeg  =  (  nScanIntervalPerCNetSegInSecond  *  1000  );

	//  扫描主机间歇
	if  (  !qyGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_scanIntervalPerPcInMilliSecond,  buf,  sizeof(  buf  )  )  )  {
		nScanIntervalPerPcInMilliSecond  =  atol(  buf  );
	}
	if  (  nScanIntervalPerPcInMilliSecond  >  CONST_max_nScanIntervalPerPcInMilliSecond  )  pCfg->u.intraMon.nScanIntervalPerPc  =  CONST_max_nScanIntervalPerPcInMilliSecond;
	else  pCfg->u.intraMon.nScanIntervalPerPc  =  nScanIntervalPerPcInMilliSecond;

	//  外网IP
	if  (  asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_newInterMonIp0,  pCfg->u.intraMon.newInterMonIps[0],  sizeof(  pCfg->u.intraMon.newInterMonIps[0]  )  )  )  {
		pCfg->u.intraMon.newInterMonIps[0][0]  =  0;
	}
	if  (  asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_newInterMonIp1,  pCfg->u.intraMon.newInterMonIps[1],  sizeof(  pCfg->u.intraMon.newInterMonIps[1]  )  )  )  {
		pCfg->u.intraMon.newInterMonIps[1][0]  =  0;
	}
	if  (  asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_newInterMonIp2,  pCfg->u.intraMon.newInterMonIps[2],  sizeof(  pCfg->u.intraMon.newInterMonIps[2]  )  )  )  {
		pCfg->u.intraMon.newInterMonIps[2][0]  =  0;
	}
	if  (  asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  CONST_regValName_newInterMonIp3,  pCfg->u.intraMon.newInterMonIps[3],  sizeof(  pCfg->u.intraMon.newInterMonIps[3]  )  )  )  {
		pCfg->u.intraMon.newInterMonIps[3][0]  =  0;
	}
 
	return  0;

}
	

 int  initAwmIntraMon(  AWM_EXT  *  pAE  )
{
	int			iErr = -1;
	WORD		wVersionRequested;
	WSADATA		wsaData;       
    char		buf[1024];
	CString		errLogCStr;
	CString		lckCStr;
	CFile	*	pLckFile = NULL;
	DWORD		dwThreadDaemonId;
	int			i;

	setErrHintWndTitle(  CONST_qnmStatusWndTitle  );
	_snprintf(  pAE->cfg.showWho,  sizeof(  pAE->cfg.showWho  ),  "%s",  CONST_showWho_intraMon  );

	// wVersionRequested = MAKEWORD(1, 1);      
	wVersionRequested = MAKEWORD(2, 1);      
	if(WSAStartup(wVersionRequested, &wsaData) == SOCKET_ERROR) {
		goto errLabel;
	}      
	pAE->bWsaStartuped = TRUE;

	if  (  asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  ASR_INSTALL_PATH_KEY,  buf,  sizeof(  buf  )  )  )  {
		return -1;		 
	}

	//  lckCStr = CString( buf ) + CString( "\\temp\\" ) + AWM_INTRA_MON_LCK_FILE;
	lckCStr = CString( buf ) + CString( "\\work\\" ) + AWM_INTRA_MON_LCK_FILE;
	pLckFile = new CFile( );
	if  (  !pLckFile  )  goto  errLabel;
	if  (  !pLckFile->Open(  lckCStr,  CFile::modeCreate | CFile::shareExclusive  )  )  {
		traceLogA(  "无法取得文件锁，有其他实例在运行"  );  goto errLabel;
	}
	pAE->pLckFile = pLckFile; pLckFile = NULL;

	errLogCStr = CString( buf ) + CString( "\\temp\\" ) + AWM_INTRA_MON_ERR_LOG_FILE;
	setErrLogFile( ( char * )( LPCTSTR )errLogCStr );
	setErrLogHint( AWM_INTRA_MON_ERR_LOG_HINT );
	
	qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "启动拨号检测扫描服务",  ""  );
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "启动拨号检测扫描服务",  ""  );


	while ( 1 ) {
		char buf[128] = "999";

		if ( !asrGetRegCfg( ROOT_AWM_INTRA_MON_KEY, ASR_QUIT_KEY, buf, sizeof( buf ) ) ) {
			debugLog( "initAwmIntraMon( ) get quit key value is [%s]", buf );
			if  ( atol( buf ) == ASR_QUIT_VAL )  {
				qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "拨号检测扫描服务将退出",  ""  );
				qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "服务将退出",  ""  );
				goto errLabel;
			}
		}
		if ( !asrGetRegCfg( ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, buf, sizeof( buf ) ) ) {
			debugLog( "initAwmIntraMon( ) get stop key value is [%s]", buf );
			if ( atol( buf ) == ASR_STOP_VAL ) {
				qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "拨号检测扫描服务已停止",  ""  );
				qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "服务已停止",  ""  );
				Sleep( 3000 );
				continue;
			}
		}
		
		break;
	}

	if  (  getAwmIntraMonCfg(  &pAE->cfg  )  )  goto  errLabel;

	if  (  initQyEnc(  pAE->pEncCtx  )  )  goto  errLabel;
	pAE->bEncCtxInited			=	TRUE;

	pAE->hThreadIntraMons[0]	=	CreateThread( NULL, 0,  intraMonThreadProc, pAE, 0, &dwThreadDaemonId );
	
	qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "服务已启动",  ""  );

	iErr = 0;

errLabel:

	if  (  iErr  )  {

		pAE->bQuit = TRUE;

		for ( i = 0; i < sizeof( pAE->hThreadIntraMons ) / sizeof( HANDLE ); i ++ ) {
			if ( pAE->hThreadIntraMons[i] ) {
				::WaitForSingleObject( pAE->hThreadIntraMons[i], INFINITE );
				CloseHandle( pAE->hThreadIntraMons[i] );
				pAE->hThreadIntraMons[i] = NULL;
			}
		}

		if  (  pAE->bEncCtxInited  )  {
			exitQyEnc(  pAE->pEncCtx  );  pAE->bEncCtxInited  =  FALSE;
		}

		if  (  pAE->pLckFile  )  {
			pLckFile = ( CFile * )pAE->pLckFile;  
			pLckFile->Close(  );
			pAE->pLckFile  =  NULL;
		}
		if  (  pLckFile  )  delete pLckFile;
		
		if  (  pAE->bWsaStartuped  )  {
			WSACleanup( ); pAE->bWsaStartuped = FALSE;
		}
	
	}
	
	return iErr;

}


 void exitAwmIntraMon( AWM_EXT *pAE )
{
	CFile *pLckFile = NULL;
	int i;
	DWORD dwRet;

	debugLog( "exitAwmIntraMon( ): enters." );

	pAE->bQuit = TRUE;
	for ( i = 0; i < sizeof( pAE->hThreadIntraMons ) / sizeof( HANDLE ); i ++ ) {
		if ( pAE->hThreadIntraMons[i] ) {
			// ::WaitForSingleObject( pAE->hThreadIntraMons[i], INFINITE );
			dwRet = ::WaitForSingleObject( pAE->hThreadIntraMons[i], DEFAULT_AWM_WAIT_FOR_THREAD_TIMEOUT );
			if ( dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT ) {
				CloseHandle( pAE->hThreadIntraMons[i] );	pAE->hThreadIntraMons[i] = NULL;
			}
		}
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

	debugLog( "exitAwmIntraMon( ): leaves." );
	errLog( "服务结束." );
	qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "拨号检测服务结束",  ""  );


	return;
}


 int awmIntraMonRun( AWM_EXT *pAE )
{
	char			buf[256];
	unsigned  long  curnScanInterval  =  pAE->cfg.u.intraMon.nScanInterval;
	char			curNewInterMonIps[4][MAX_IP_ADDR_LEN  +  1];		
	int				i;
	
	for  (  i  =  0;  i  <  4;  i  ++  )  {
		 strcpy(  curNewInterMonIps[i],  pAE->cfg.u.intraMon.newInterMonIps[i]  );
	}
	
	while  (  TRUE  )  {

		   if  (  !asrGetRegCfg(  ROOT_AWM_INTRA_MON_KEY,  ASR_QUIT_KEY,  buf,  sizeof(  buf  )  )  )  {
			   //  debugLog(  "awmIntraMonRun(  ) get quit key value is [%s]",  buf  );
			   if  (  atol(  buf  )  ==  ASR_QUIT_VAL  )  break;
		   }
		   if  (  !asrGetRegCfg(  ROOT_AWM_KEY,  ASR_RAS_STOP_MONITOR_KEY,  buf,  sizeof(  buf  )  )  )  {
			   //  debugLog(  "awmIntraMonRun(  ) get stop key value is [%s]",  buf  );
			   if  (  atol(  buf  )  ==  ASR_STOP_VAL  )  break;
		   }

		   if  (  getAwmIntraMonCfg(  &pAE->cfg  )  )  {
			   debugLog(  "awmIntraMonRun( ): getAwmIntraMonCfg( ) failed."  );
			   break;
		   }
		   if  (  curnScanInterval  !=  pAE->cfg.u.intraMon.nScanInterval  )  {
			   OutputDebugString(  "nScanInterval is changed."  );
			   break;
		   }
		   for  (  i  =  0;  i  <  4;  i  ++   )  {
			   if  (  strcmp(  curNewInterMonIps[i],  pAE->cfg.u.intraMon.newInterMonIps[i]  )  )  {
				   break;
			   }
		   }
		   if  (  i  <  4   )  {
			   OutputDebugString(  "interMonIp changed."  );
			   break;
		   }
			
		   // debugLog( "awmProxyRun" );
		   Sleep( 3000 );

	}

	return   0;

}


 DWORD  WINAPI  intraMonThreadProc(  LPVOID  lpParameter  )
{
	AWM_EXT						*		pAE				=	(  AWM_EXT  *  )lpParameter;
	INTRA_MON_THREAD_INFO				iMTI;
	CDatabase							tmpDb;
	unsigned  int						loopCtrl		=	0;
	BOOL								bFirst			=	TRUE;
	SCANNED_IP_TAB_RCD					tmpSITR;
	char								buf[1024];
	SOCKET								rawSocket		=	-1;
	SOCKET								dGramSockFd		=	-1;   
	BOOL								bOpt;
	AWM_MON_DATA						tmpAMD;
	//  int									i;
	char  *  startPtr  =  NULL,  *  endPtr  =  NULL;
	char								scannedIp[15 + 1];
	//  int		 startN,  endN;
	char								tmpInterMonIp[MAX_IP_ADDR_LEN  +  1];

	rawSocket = socket( AF_INET, SOCK_RAW, IPPROTO_RAW );
	if ( rawSocket == SOCKET_ERROR ) {
		asrShowRegErr( ROOT_AWM_INTRA_MON_KEY, "Creating a raw socket failed." );
		goto  errLabel;
	}
	if  (  (  dGramSockFd  =  socket(  AF_INET,  SOCK_DGRAM,  0  )  )  ==  -1  )  { 
		goto  errLabel;
	} 
	
	bOpt = TRUE;
	if ( setsockopt( rawSocket, IPPROTO_IP, IP_HDRINCL, ( char * )&bOpt, sizeof( bOpt ) ) ) {
		asrShowRegErr( ROOT_AWM_INTRA_MON_KEY, "setsockopt failed." );
		goto errLabel;
	}

	TRY {
		if ( !tmpDb.Open( pAE->cfg.dsnName ) ) {
			asrShowRegErr( ROOT_AWM_INTRA_MON_KEY, "db.Open failed." );
			goto errLabel;
		}
		}
	CATCH ( CDBException, e ) {
		debugLog( "intraMonThreadProc( ) the caught err is:[%s]", e->m_strError );
		goto errLabel;
	}
	END_CATCH

	memset( &iMTI, 0, sizeof( iMTI ) );
	iMTI.pDb = ( void * )&tmpDb;

	while  (  !pAE->bQuit  )  {

		debugLog(  "intraMonThreadProc( ) starts a new loop...\n"  );
		//  errLog(  "等待扫描..."  );
		qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "等待拨号检测扫描",  ""  );

		
		if  (  !pAE->cfg.u.intraMon.newInterMonIps[0][0]
			&&  !pAE->cfg.u.intraMon.newInterMonIps[1][0]
				&&  !pAE->cfg.u.intraMon.newInterMonIps[2][0]
					&&  !pAE->cfg.u.intraMon.newInterMonIps[3][0]  )  
		{
			Sleep(  3000  );
			continue;
		}

		if  (  bFirst  )  bFirst  =  FALSE;
		else  {

			int  k  =  pAE->cfg.u.intraMon.nScanInterval  /  1000;
			
			for  (  ;  k;  k  --  )  {
				 if  (  pAE->bQuit  )  goto  errLabel;
				 //  errLog(  "等待扫描..."  );
				 qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "等待扫描...",  ""  );
				 Sleep(  1000  );
			}
			// Sleep(  pAE->cfg.u.intraMon.nScanInterval  );
		}
		
				
		{
			CDBVariant varValue;
			CRecordset ls( &tmpDb );
	
			TRY {
				if( !ls.Open( CRecordset::forwardOnly, _T( "SELECT interMonIp, officeName, subOfficeName, startIp, endIp FROM scannedIpTab" ) ) ) {
					debugLog( "CRecord.Open( \"Select * from scannedIpTab\" ) failed." );
					continue;
				}
				}	
			CATCH ( CDBException, e ) {
				debugLog( "CRecord.Open( \"Select * from scannedIpTab\" ) failed:[%s]", e->m_strError );
				goto errLabel;
				}
			END_CATCH
	
			TRY {
				
				for  (  ;  !ls.IsEOF(  );  ls.MoveNext(  )  )  {
				// while( !ls.IsEOF( ) ){
				
					memset(  &tmpSITR,  0,  sizeof(  tmpSITR  )  );
					ls.GetFieldValue( ( short )0, varValue );
					wsprintf( tmpSITR.interMonIp, varValue.m_pstring->GetBuffer( 0 ) );
					ls.GetFieldValue( ( short )1, varValue );
					wsprintf( tmpSITR.officeName, "%s", varValue.m_pstring->GetBuffer( 0 ) );
					ls.GetFieldValue( ( short )2, varValue );
					if ( varValue.m_dwType != DBVT_STRING ) 
						wsprintf( tmpSITR.subOfficeName, "" );
					else
						wsprintf( tmpSITR.subOfficeName, "%s", varValue.m_pstring->GetBuffer( 0 ) );
					ls.GetFieldValue( ( short )3, varValue );
					wsprintf( tmpSITR.startIp, "%s", varValue.m_pstring->GetBuffer( 0 ) );
					ls.GetFieldValue( ( short )4, varValue );
					if ( varValue.m_dwType != DBVT_STRING )
						wsprintf( tmpSITR.endIp, tmpSITR.startIp );
					else
						wsprintf( tmpSITR.endIp, "%s", varValue.m_pstring->GetBuffer( 0 ) );
					sprintf( buf, "scanned interMonIp is [%s], officeName is [%s], subOfficeName is [%s], startIp is [%s], endIp is [%s]", 
						tmpSITR.interMonIp, tmpSITR.officeName, tmpSITR.subOfficeName, tmpSITR.startIp, tmpSITR.endIp );
					debugLog( "Starting to scan: %s", buf );
					strcat( buf, "\n" );
					OutputDebugString( buf );

					qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "现在开始扫描",  " %s %s %s - %s",  tmpSITR.officeName,  tmpSITR.subOfficeName,  tmpSITR.startIp,  tmpSITR.endIp  );
					Sleep(  1000  );

					memset( &tmpAMD, 0, sizeof( tmpAMD ) );
					memcpy( tmpAMD.magic, AWM_MON_MAGIC, sizeof( tmpAMD.magic ) );
					tmpAMD.len = 34;
					memcpy( tmpAMD.officeName, tmpSITR.officeName, sizeof( tmpAMD.officeName ) );
					memcpy( tmpAMD.subOfficeName, tmpSITR.subOfficeName, sizeof( tmpAMD.subOfficeName ) );

					/*
					startPtr = strrchr( tmpSITR.startIp, '.' );
					endPtr = strrchr( tmpSITR.endIp, '.' );
					if ( !startPtr || !endPtr ) {
						debugLog( "Invalid Ip." );
						}
					else {
						*startPtr = 0; 
						startPtr ++; endPtr ++;
						startN = atol( startPtr ); endN = atol( endPtr );
						if ( startN < 0 || startN > 255 || endN < 0 || endN > 255 || startN > endN )  {
							debugLog( "Invalid Ip." );
						}
						else {
							if ( startN == 0 ) startN = 1;
							for ( i = startN; i <= endN; i ++ ) {
								unsigned long ulIp;
								sprintf( scannedIp, "%s.%d", tmpSITR.startIp, i );
								debugLog( "Now scanning [%s][%s][%s]", tmpAMD.officeName, tmpAMD.subOfficeName, scannedIp );
								ulIp = inet_addr( scannedIp );
								memcpy( tmpAMD.ucIp, ( char * )&ulIp, sizeof( tmpAMD.ucIp ) );
								//  awmIcmpEcho( rawSocket, ( char * )tmpSITR.interMonIp, ( char * )scannedIp, ( char * )&tmpAMD, AWM_MON_DATA_SIZE );

								for  (  int  tmpIndex  =  0;   tmpIndex  <  sizeof(  pAE->cfg.u.intraMon.newInterMonIps  )  /  sizeof(  pAE->cfg.u.intraMon.newInterMonIps[0]  );  tmpIndex  ++  )  {
									 memcpy(  tmpInterMonIp,  pAE->cfg.u.intraMon.newInterMonIps[tmpIndex],  sizeof(  tmpInterMonIp  )  -  1  );  
									 tmpInterMonIp[sizeof(  tmpInterMonIp  )  -  1]  =  0;
									 if  (  tmpInterMonIp[0]  )  {
										 //  errLog(  "Now to scan %s,  newInterMonIp is %s",  scannedIp,  pAE->cfg.u.intraMon.newInterMonIps[tmpIndex]  );
										 awmExtScan(  pAE,  rawSocket,  dGramSockFd,  (  char  *  )tmpInterMonIp,  (  char  *  )scannedIp,  (  char  *  )&tmpAMD,  AWM_MON_DATA_SIZE  );
										 // awmIcmpEcho( rawSocket, ( char * )pAE->cfg.u.intraMon.newInterMonIps[tmpIndex], ( char * )scannedIp, ( char * )&tmpAMD, AWM_MON_DATA_SIZE );
									 }
								}
							}
						}
					}
					*/

					{
						char				*	startIp				=  tmpSITR.startIp;
						char				*	endIp				=  tmpSITR.endIp;
						
						int						i					=		0;
	 					unsigned  long			ulStartIp,  ulEndIp,  ulCurIp;
	 					unsigned  long			hulStartIp,  hulEndIp,  hulCurIp;
	 					unsigned  char		*	p;
	 					struct  in_addr			tmpInAddr;
	 					unsigned  char		*	p3;
						unsigned  long			f2  =  555;		  
	 
	 					ulStartIp  =  inet_addr(  startIp  );
	 					ulEndIp  =  inet_addr(  endIp  );

	 					if  (  ulStartIp  ==  INADDR_NONE  ||  ulEndIp  ==  INADDR_NONE  )  continue;

	 					hulStartIp  =  ntohl(  ulStartIp  );
	 					hulEndIp  =  ntohl(  ulEndIp  );
	 
	 					for  (  hulCurIp  =  hulStartIp;  hulCurIp  <=  hulEndIp;  hulCurIp  ++  )  {

							 if  (  pAE->bQuit  )  goto  errLabel;			//  扫描中随时检验bQuit值，使能随时退出。

							 ulCurIp  =  htonl(  hulCurIp  );
		  					 p3  =  (  unsigned  char  *  )&ulCurIp;
		  					 if  (  p3[3]  <=  0  ||  p3[3]  >=  255  )  continue;
							 if  (  f2  !=  p3[2]  )  {
							 	 f2  =  p3[2];
								 Sleep(  pAE->cfg.u.intraMon.nScanIntervalPerCNetSeg  );
							 	 //  qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "现在扫描: [ %s ] [ %s ] %d.%d.%d.* 网段",  tmpSITR.officeName,  tmpSITR.subOfficeName,  p3[0],  p3[1],  p3[2]  );
							 }
		  
		  					 tmpInAddr.S_un.S_addr  =  ulCurIp;
		  					 p  =  (  unsigned  char  *  )inet_ntoa(  tmpInAddr  );
							 if  (  !p  )  continue;
							 		  
		  					 qyShowInfo(  CONST_qyShowType_bhbScanningNetworkSegment,  "",  "",  "",  "扫描: ",  "[ %s ] [ %s ] %s",  tmpSITR.officeName,  tmpSITR.subOfficeName,  p  );


							 if  (  pAE->cfg.u.intraMon.nScanIntervalPerPc  )  Sleep(  pAE->cfg.u.intraMon.nScanIntervalPerPc  );
							 
							 {
								unsigned long ulIp;
								sprintf( scannedIp, "%s", p );
								debugLog( "Now scanning [%s][%s][%s]", tmpAMD.officeName, tmpAMD.subOfficeName, scannedIp );
								ulIp = inet_addr( scannedIp );
								memcpy( tmpAMD.ucIp, ( char * )&ulIp, sizeof( tmpAMD.ucIp ) );
								//  awmIcmpEcho( rawSocket, ( char * )tmpSITR.interMonIp, ( char * )scannedIp, ( char * )&tmpAMD, AWM_MON_DATA_SIZE );

								for  (  int  tmpIndex  =  0;   tmpIndex  <  sizeof(  pAE->cfg.u.intraMon.newInterMonIps  )  /  sizeof(  pAE->cfg.u.intraMon.newInterMonIps[0]  );  tmpIndex  ++  )  {
									 memcpy(  tmpInterMonIp,  pAE->cfg.u.intraMon.newInterMonIps[tmpIndex],  sizeof(  tmpInterMonIp  )  -  1  );  
									 tmpInterMonIp[sizeof(  tmpInterMonIp  )  -  1]  =  0;
									 if  (  tmpInterMonIp[0]  )  {
										 //  errLog(  "Now to scan %s,  newInterMonIp is %s",  scannedIp,  pAE->cfg.u.intraMon.newInterMonIps[tmpIndex]  );
										 awmExtScan(  pAE,  rawSocket,  dGramSockFd,  (  char  *  )tmpInterMonIp,  (  char  *  )scannedIp,  (  char  *  )&tmpAMD,  AWM_MON_DATA_SIZE  );
										 // awmIcmpEcho( rawSocket, ( char * )pAE->cfg.u.intraMon.newInterMonIps[tmpIndex], ( char * )scannedIp, ( char * )&tmpAMD, AWM_MON_DATA_SIZE );
									 }
								}
							}
		  
	 					}
	 
					}

					//	ls.MoveNext( );	 }	//  这一句话由于 while  (  ) 结构改为 for  (  ;  ;  ) 结构而移至上面
				}
				
				}
		 	CATCH( CDBException, e ){
					debugLog( "asrSendRule() caught err is:[%s]", e->m_strError );						
			}
			END_CATCH
		
			if ( ls.IsOpen( ) ) ls.Close( );
	 
		}
	}

errLabel:

	if  (  tmpDb.IsOpen(  )  )  tmpDb.Close( );
	if  (  dGramSockFd  >=  0  )  closesocket(  dGramSockFd  );
	if  (  rawSocket  >=  0  )  closesocket(  rawSocket  );

	return 0;

}
 


 void awmIntraMonMain( )
{
	// void Ping(LPCSTR pstrHost)
	// LPCTSTR pstrHost = "192.168.103.130";
	// LPCTSTR pstrHost = "192.168.103.4";
	// LPCTSTR pstrHost = "wxr";

	// LPCTSTR pSpoofIp = "210.78.155.147";
	// LPCTSTR pTargetIp = NULL;
	// SOCKET	  rawSocket;
	// LPHOSTENT lpHost;
	// struct    sockaddr_in saDest;
	//	struct    sockaddr_in saSrc;
	//	DWORD	  dwTimeSent;
	//	DWORD	  dwElapsed;
	//	u_char    cTTL;
	// int       nLoop;
	// int       nRet;
	// char dataBuf[16] = "How are you?";
	// unsigned int dataSize = strlen( dataBuf );
	// BOOL bOpt;
	AWM_EXT aE;

	if  (  REQ_DATASIZE  !=  AWM_MON_DATA_SIZE  )  {
		int		tmpi;

		tmpi  =  REQ_DATASIZE;
		tmpi  =  AWM_MON_DATA_SIZE;
		OutputDebugString(  "REQ_DATASIZE应等于AWM_MON_DATA_SIZE\n"  );
		return;
	}

	setDebugLogFileName( "errIntra.log" );
	debugLog( "awmIntraMonMain( ) starts..." );

	asrShowRegStatus( ROOT_AWM_INTRA_MON_KEY, "starts..." );

	memset( &aE, 0, sizeof( aE ) );
	if ( initAwmIntraMon( &aE ) ) {
		asrShowRegStatus( ROOT_AWM_INTRA_MON_KEY, "init failed." );
		return;
	}

	awmIntraMonRun( &aE );

	// Create a Raw socket
	// rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	// rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	// if (rawSocket == SOCKET_ERROR) 	{
	//		return;
	// }
	
	// bOpt = TRUE;
	// if ( setsockopt( rawSocket, IPPROTO_IP, IP_HDRINCL, ( char * )&bOpt, sizeof( bOpt ) ) ) {
	//		goto errLabel;
	// }

	// Lookup host
	// lpHost = gethostbyname(pstrHost);
	// if (lpHost == NULL)	{
	//	fprintf(stderr,"\nHost not found: %s\n", pstrHost);
	//	return;
	// }
		
	// Setup destination socket address
	// saDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
	// saDest.sin_family = AF_INET;
	// saDest.sin_port = 0;

	// pTargetIp = inet_ntoa( *( struct in_addr * )&saDest.sin_addr.s_addr );

	// Tell the user what we're doing
	// printf("\nPinging %s [%s] with %d bytes of data:\n",
	//			pstrHost,
	//			inet_ntoa(saDest.sin_addr),
	//			REQ_DATASIZE);

	// Ping multiple times
	// for (nLoop = 0; nLoop < 400; nLoop++) {
	//		awmIcmpEcho( rawSocket, ( char * )pSpoofIp, ( char * )pTargetIp, dataBuf, dataSize );
	//
	//		Sleep( 1000 );
	// }

// errLabel:
	// nRet = closesocket(rawSocket);
	// if (nRet == SOCKET_ERROR)
	//	debugLog( "closesocket()" );

	exitAwmIntraMon( &aE );

	asrShowRegStatus( ROOT_AWM_INTRA_MON_KEY, "ends." );


	debugLog( "awmIntraMonMain( ) ends..." );

	return;
}

extern  "C"  int  qyUpnpScan(  char  *  interMonIp,  unsigned  short  interMonPort,  char  *  scannedIp,  unsigned  short  upnpPort,  char  *  sndDataParam,  unsigned  int  sndLen,  int  sockFd  );
extern  "C"  void  qyTcpScan(  int  s,  char  *  srcIp,  char  *  dstIp,  char  *  data,  unsigned  int  dataSize  );
extern  "C"  void  aeNbtScan(  int  s,  char  *  srcIp,  char  *  dstIp,  char  *  data,  unsigned  int  dataSize  );


 extern  "C"  void  awmExtScan(  AWM_EXT  *  pAE,  int  rawSockFd,  int  dGramSockFd,  char  *  interMonIp,  char  *  scannedIp, char  *  dataParam,  unsigned  int  dataSizeParam  )
{

	 char			data[CONST_qyDataMaxLen  +  1];
	 unsigned  int	dataSize;
	
	 dataSize  =  sizeof(  data  )  -  1;
	 if  (  qyEnc(  pAE->pEncCtx,  dataParam,  dataSizeParam,  data,  &dataSize  )  )  return;


	 /*
	 {
		 char			decBuf[CONST_qyDataMaxLen  +  1];
	 	 unsigned  int  decLen;

	 	 decLen  =  sizeof(  decBuf  );
	 	 qyDec(  pAE->pEncCtx,  data,  dataSize,  decBuf,  &decLen  );
	 	 if  (  memcmp(  decBuf,  dataParam,  decLen  )  )  {
			 OutputDebugString(  "enc failed.\n"  );
	 }
	 */

	 awmIcmpEcho(  rawSockFd,  interMonIp,  scannedIp,  data,  dataSize  );
#ifdef  __NEW_AESWK__
	 qyUpnpScan(  interMonIp,  pAE->cfg.interMonTcpPort,  scannedIp,  CONST_qyPort_upnp,  data,  dataSize,  dGramSockFd  );
#endif

	 qyTcpScan(  rawSockFd,  interMonIp,  scannedIp,  dataParam,  dataSizeParam  );

	 //  2004/05/22添加
	 aeNbtScan(  rawSockFd,  interMonIp,  scannedIp,  data,  dataSize  );


}
