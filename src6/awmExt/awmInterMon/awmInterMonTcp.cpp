
#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"aeHelpFunc.h"
#include	"awmExt.h"

typedef  struct  __interMonThreadBuf_t  {
				 unsigned  long			ulPeerIp;
}		 INTERMON_THREADBUF;


 extern  "C"  int  doInterMonServWork(  int  sockFd,  void  *  pp  )
{
	 int						iErr			=	-1;
	 MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO  *  )pp;
	 AWM_EXT				*	pAE				=	(  AWM_EXT  *  )pSubThreadInfo->pParentParam;
	 //  char						buf[CONST_qyBufSize_upnp  + 1];
	 int						numBytes		=	0;
	 AWM_MON_PROC_INFO			ampi;

	 traceLogA(  "doInterMonServWork .. .  "  );

	 memset(  &ampi,  0,  sizeof(  ampi  )  );
	 if  (  (  numBytes  =  recv(  sockFd,  ampi.dataBuf,  sizeof(  ampi.dataBuf  ),  0  )  )  ==  -1   )   return  -1;
	 
	 if  (  numBytes  >=  sizeof(  ampi.dataBuf  )  )  {
		 traceLogA(  "doInterMonServWork: 数据包太大了"  );  goto  errLabel;
	 }
	 ampi.dataBuf[numBytes]  =  '\0'; 
	 ampi.nRecvd  =  numBytes;
	 getRemoteIpBySocket(  sockFd,  ampi.recvdIp  );
	 traceLogA(  "Receved.[%s]\n",  ampi.dataBuf  ); 

	 if  (  strstr(  ampi.dataBuf,  CONST_qyMagic_interMon  )  )  {
		 if  (  processAwmMonPcInfo(  pAE,  pp,  &ampi  )  )  goto  errLabel;
		}
	 else  {
		   if  (  processAwmUpnpInfo(  pAE,  pp,  &ampi  )  )  goto  errLabel;
	 }

	 iErr   =   0;

errLabel:

	 return  iErr;

}


 //  added by 2004/10/18
 extern  "C"  int processAwmMonPcInfo(  AWM_EXT  *  pAE,  void  *  pp,  AWM_MON_PROC_INFO  *  pAmpi  )
{	 
	int								iErr			=  -1;
	MT_SOCK_SUBTHREADINFO		*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO  *  )pp;
	long							len;
	char						*	ptr				=  NULL;
	char							dataBuf[2048  +  1];
	AWM_MON_DATAEx					amd;
	QWM_WARNTOINTERMON_INFO			warnInfo;
	unsigned  int					decLen;
	INTER_MON_THREAD_PROC_INFO		iMTPI;
	struct  in_addr					tmpIn;
		
	ptr  =  strstr(  pAmpi->dataBuf,  CONST_qyMagic_interMon  );
	if  (  !ptr  )  return  -1;
	ptr  +=  strlen(  CONST_qyMagic_interMon  );
	if  (  qyXStr2L(  ptr,  &len  )  )  return  -1;
	if  (  ptr  +  8  +  2  *  len  >  pAmpi->dataBuf  +  pAmpi->nRecvd  )  return  -1;
	ptr  +=  8;

	if  (  !qyX2Buf(  ptr,  dataBuf,  len  )  )  goto  errLabel;

	decLen  =  sizeof(  warnInfo  );
	if  (  qnmDecData(  &pAE->qnmUpdateCtx,  dataBuf,  len,  (  char  *  )&warnInfo,  &decLen  )  )  goto  errLabel;

	memset(  &amd,  0,  sizeof(  amd  )  );
	memcpy(  amd.magic,  AWM_MON_MAGIC,  min(  sizeof(  amd.magic  ),  strlen(  AWM_MON_MAGIC  )  )  );
	if  (  (  tmpIn.s_addr  =  inet_addr(  pAmpi->recvdIp  )  )  ==  INADDR_NONE  )  goto  errLabel;
	memcpy(  amd.ucIp,  &tmpIn.s_addr,  sizeof(  tmpIn.s_addr  )  );
	safeStrnCpy(  warnInfo.mac0,  amd.mac,  sizeof(  amd.mac  )  );
	safeStrnCpy(  warnInfo.pcName,  amd.compName,  sizeof(  amd.compName  )  );

	_snprintf(  amd.hint,  sizeof(  amd.hint  ),  "%s",  "上网警报"  );		//  2004/10/19
	memset(  &iMTPI,  0,  sizeof(  iMTPI  )  );
	iMTPI.hMutex   =   pSubThreadInfo->hMutex;
	if  (  processAwmExtData(  pAE,  (  char  *  )&amd,  sizeof(  amd  ),  NULL,  &iMTPI  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:

	return  iErr;

  
}


 //  extern  "C"  int processAwmUpnpInfo(  AWM_EXT  *  pAE,  char  *  data,  size_t  dataLen,  void  *  pp  )
 extern  "C"  int processAwmUpnpInfo(  AWM_EXT  *  pAE,  void  *  pp,  AWM_MON_PROC_INFO  *  pAmpi  )
{
	int								iErr			=  -1;
	MT_SOCK_SUBTHREADINFO		*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO  *  )pp;
	char						*	data			=	pAmpi->dataBuf;
	size_t							dataLen			=	pAmpi->nRecvd;
	long							len;
	char						*	ptr				=  NULL;
	char							dataBuf[CONST_qyDataMaxLen  +  1];
	//  char							decBuf[CONST_qyDataMaxLen  +  1];
	AWM_MON_DATAEx					amd;
	unsigned  int					decLen;
	INTER_MON_THREAD_PROC_INFO		iMTPI;
	
	/*
#ifdef		__NEW_AESWK__
	//  这一校验舍弃，是因为此版本不需要校验数据包从何而来
#else
	goto  errLabel;		//  此版本不收xp的UPNP数据包
#endif
	*/

	//  2004/05/25修改
	if  (  pAE->cfg.u.interMon.ucbStopPermitNat  )  {		//  将上面的数据过滤由宏定义改为变量控制
		goto  errLabel;
	}

	ptr  =  strstr(  data,  CONST_qyMagic_upnp  );
	if  (  !ptr  )  return  -1;
	ptr  +=  strlen(  CONST_qyMagic_upnp  );
	if  (  qyXStr2L(  ptr,  &len  )  )  return  -1;
	if  (  ptr  +  8  +  2  *  len  >  data  +  dataLen  )  return  -1;
	ptr  +=  8;

	if  (  !qyX2Buf(  ptr,  dataBuf,  len  )  )  goto  errLabel;

	decLen  =  sizeof(  amd  );
	if  (  qyDec(  pAE->pEncCtx,  dataBuf,  len,  (  char  *  )&amd,  &decLen  )  )  goto  errLabel;
	memset(  (  (  char  *  )&amd  )  +  decLen,  0,  sizeof(  amd  )  -  decLen  );
	
	_snprintf(  amd.hint,  sizeof(  amd.hint  ),  "%s",  "upnp"  );		//  2004/05/24

	memset(  &iMTPI,  0,  sizeof(  iMTPI  )  );
	iMTPI.hMutex   =   pSubThreadInfo->hMutex;
	if  (  processAwmExtData(  pAE,  (  char  *  )&amd,  sizeof(  amd  ),  NULL,  &iMTPI  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:

	return  iErr;

}


 extern  "C"  int  processAwmExtData(  AWM_EXT  *  pAE,  char  *  data,  unsigned  int  dataLen,  AWM_MON_PROC_INFO  *  pAMPI,  INTER_MON_THREAD_PROC_INFO  *  pIMTPI  )
{
	char						buf[1024];
	AWM_MON_DATAEx			*	pAMD		=  (  AWM_MON_DATAEx  *  )data;
	BOOL						bWaited		=  FALSE;
	DWORD						dwRet;
	//  SCANNING_LOG_TAB_RCD		sLTR;
	struct  in_addr				tmpInAddr;

	if  (  dataLen  <  sizeof(  AWM_MON_DATAEx  )  )  {
		MACRO_qyAssert(  0,  "processAwmExtData here"  );
		traceLogA(  "接收到的数据包不完整"  );  goto  errLabel;
	}

	if  (  memcmp(  pAMD->magic,  AWM_MON_MAGIC,  sizeof(  pAMD->magic  )  )  )  {
		OutputDebugString(  "Not our data.\n"  );  goto  errLabel;
	}

	_snprintf(  buf,  sizeof(  buf  ),  "processAwmExtData( ): len is %d\n",  pAMD->len  );
	traceLogA(  "%s",  buf  );
	_snprintf(  buf,  sizeof(  buf  ),  "processAwmExtData( ): officeName is %s\n",  pAMD->officeName  );
	traceLogA(  "%s",  buf  );
	_snprintf(  buf,  sizeof(  buf  ),  "processAwmExtData( ): subOfficeName is %s\n",  pAMD->subOfficeName  );
	traceLogA(  "%s",  buf  );
	memcpy( ( char * )&tmpInAddr.S_un.S_addr, pAMD->ucIp, sizeof( unsigned long ) );
	_snprintf(  buf,  sizeof(  buf  ),  "processAwmExtData( ): inet_ntoa( ucIp ) is %s\n",  inet_ntoa(  tmpInAddr  )  );
	traceLogA(  "%s",  buf  );
	_snprintf(  buf,  sizeof(  buf  ),  "processAwmExtData( ): comment is %s\n",  pAMD->comment  );
	traceLogA(  "%s",  buf  );

	//  注意这里取收到的时间，2004/05/23
	getCurTime(  pAMD->recvdTime  );

	/*
#ifdef		__NEW_AESWK__
	//  这一校验舍弃，是因为此版本不需要校验数据包从何而来
#else
	if  (  NULL  ==  pAMPI  )  goto  errLabel;
	if  (  inet_addr(  pAMPI->recvdIp  )  !=  tmpInAddr.S_un.S_addr  )  {
		traceLogA( "Captured ip is not ucIp, so discarded." );  goto errLabel;
	}
#endif
	*/
	if  (  pAE->cfg.u.interMon.ucbStopPermitNat  )  {		//  将上面的数据过滤由宏定义改为变量控制
		if  (  NULL  ==  pAMPI  )  goto  errLabel;
		if  (  inet_addr(  pAMPI->recvdIp  )  !=  tmpInAddr.S_un.S_addr  )  {
			traceLogA( "Captured ip [%s] is not 扫描Ip [%s], so discarded.",  pAMPI->recvdIp,  inet_ntoa(  tmpInAddr  )  );  goto errLabel;
  		    #ifdef  __DEBUG__
					qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAE->cfg.showWho,  "",  "",  "收到[%s]的%s, 非扫描[%s], 因此放弃",  pAMPI->recvdIp,  pAMD->hint,  inet_ntoa(  tmpInAddr  )  );
			#endif		
		}
	}
	
	dwRet = WaitForSingleObject( pIMTPI->hMutex, pAE->cfg.waitTimeoutVal );
	if ( dwRet == WAIT_FAILED || dwRet == WAIT_TIMEOUT ) goto errLabel;
	bWaited = TRUE;
	// OutputDebugString( buf );
	// 在这里将时间和数据放入队列，由另一线程从中取出来,并入库。另一线程取时不要忘了使用Mutex作同步。
	if  (  pAE->monDataQ.nQNoes < MAX_AWM_MON_QUEUE_NODES  )  postMsg(  &pAE->monDataQ,  pAMD,  sizeof(  pAMD[0]  )  );
	else  traceLogA( "Too many nodes in monDataQ: nQNodes is %d", pAE->monDataQ.nQNoes );
	
	ReleaseMutex( pIMTPI->hMutex ); bWaited = FALSE;

errLabel:
	
	if ( bWaited ) ReleaseMutex( pIMTPI->hMutex );
	
	return 0;

}

