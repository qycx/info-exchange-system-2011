

#include	"stdafx.h"
#include	"qmdCommon.h"
#include	"qyMcDaemonObj.h"







 int  qnmProcCmd_policyChanged(  void  *  pSubThreadInfoParam,  void  *  pSessionParam,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_COMM_REQ  *  pReq,  char  *  reqData,  unsigned  int  reqDataLen  )
{
	 int								iErr			=	-1;
	 MT_SOCK_SUBTHREADINFO			*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 CQyMcDaemon					*	pDaemon			=	(  CQyMcDaemon  *  )pSubThreadInfo->pParentParam;
	 QMD_SESSION					*	pSession		=	(  QMD_SESSION  *  )pSessionParam;
	 QNM_PC_INFO					*	pPcInfo			=	(  QNM_PC_INFO  *  )pSession->pClient ;
	 myREFRESHED_PCOPCMD				tmpPcOpCmd;

	 traceLogA(  "qnmProcCmd_policyChanged enters"  );

	 pDaemon->var.status.ulRandOfStartup  =  time(  NULL  );

	 memset(  &tmpPcOpCmd,  0,  sizeof(  tmpPcOpCmd  )  );
	 memcpy(  &tmpPcOpCmd,  reqData,  min(  sizeof(  tmpPcOpCmd  ),  reqDataLen  )  );
	 if  (  !bMacValid(  tmpPcOpCmd.mac  )  )  goto  errLabel;

	 if  (  qySendResp(  &pSession->comm,  pSock,  pSubThreadInfo->pTo,  CONST_qyRc_ok,  NULL,  0  )  )  goto  errLabel;

	 if  (  refreshObjQMemPolicy(  pSubThreadInfo->pDb,  (  QM_OBJQ  *  )pSession->pServiceInfo->pObjQ,  tmpPcOpCmd.mac,  &tmpPcOpCmd.getOpCmd,  0,  pSession->cmdDesc,  mycountof(  pSession->cmdDesc  )  )  )  {
		 traceLogA(  "refreshObjQMemPolicy( ) failed"  );
	 }


	 iErr  =  0;

errLabel:

	 traceLogA(  "qnmProcCmd_policyChanged leaves, %s",  iErr  ?  "Ê§°Ü"  :  "³É¹¦"  );

	 return  iErr;
}


