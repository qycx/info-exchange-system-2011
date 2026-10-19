

#include "stdafx.h"
#include "qmdCommon.h"


int		doNetMcMgr(  void  * pSubThreadInfoParam,  void  *  pSession,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo  );


 extern  "C"  int  qmdServWork(  void  *  pp,  int  sockFd,  void  *  p2  )
{
	int							iErr								=	-1;
	MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo						=	(  MT_SOCK_SUBTHREADINFO  *  )pp;
	CQyMcDaemon				*	pDaemon								=  (  CQyMcDaemon  *  )pSubThreadInfo->pParentParam;
	QMD_SESSION					tmpSession;
	QY_SOCK						tmpSock;
	QY_SERVICE_INFO			*	pServiceInfo						=	0;
	char						timeBuf[CONST_qyTimeLen  +  1]		=	"";
	
	traceLogA(  "qmdServWork( ) enters."  );
			
	clearQySock(  &tmpSock  );
	tmpSock.sockFd  =  sockFd;

	memset(  &tmpSession,  0,  sizeof(  tmpSession  )  );
	getCurTime(  timeBuf  );
	if  (  qyAcceptService(  &tmpSock,  pSubThreadInfo->pTo,  timeBuf,  &tmpSession.comm  )  )  {
		traceLogA(  "qmdServWork(  ): failed to qyAcceptService(  )."  );  goto  errLabel;
	}
	if  (  tmpSession.comm.service.encType  ==  CONST_qyEncType_qwm  )  {
		memcpy(  &tmpSession.comm.commEncCtx,  &pDaemon->var.commEncCtx,  sizeof(  QY_ENC_CTX  )  );
	}

	//  sessionId的取得已放入qyAcceptService中了
	//  if  (  !(  tmpSession.comm.uiSessionId  =  getSessionId(  )  )  )  goto  errLabel;

	pServiceInfo  =  (  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )tmpSession.comm.service.serviceId,  0  );
	if  (  !pServiceInfo  )  goto  errLabel;
	tmpSession.pServiceInfo  =  pServiceInfo;
	//
	if  (  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbQmObjQInited  )  goto  errLabel;
	//
	if  (  pServiceInfo->cfg.uiVarSize  )  {
		if  (  !pServiceInfo->pVar  ||  !pServiceInfo->ucbVarInited  )  goto  errLabel;
	}


	switch  (  tmpSession.comm.service.serviceId  )  {
			case  CONST_qyServiceId_qwm:
				  doNetMcMgr(  pSubThreadInfo,  (  void  *  )&tmpSession,  &tmpSock,  pSubThreadInfo->pTo  );
				  break;
			//  case  CONST_qyServiceId_mis:
			//  	  doMisMgr(  pSubThreadInfo,  (  void  *  )&tmpSession,  &tmpSock,  pSubThreadInfo->pTo  );
			//  	  break;
			default:
					qySendResp(  &tmpSession.comm,  &tmpSock,  pSubThreadInfo->pTo,  CONST_qyRc_err,  NULL,  0  );
					break;				
	}
	
	iErr  =  0;
	
errLabel:
		
	traceLogA(  "qmdServWork( ) leaves." );
  
	return iErr;

}




