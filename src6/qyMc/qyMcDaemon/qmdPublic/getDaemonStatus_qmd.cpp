

#include	"stdafx.h"
#include	<iprtrmib.h>
//
#include	"qmdCommon.h"
#include	"qyMcDaemonObj.h"

 int  getChannelStatus(  PER_SOCKET_CONTEXT  *  p,  IM_NET_STAT  *  pStat,  CHANNEL_status_io  *  pIo  )
{
	if  (  pStat  )  memcpy(  pStat,  &p->status.netStat,  sizeof(  pStat[0]  )  );
	if  (  pIo  )  {
		memset(  pIo,  0,  sizeof(  pIo[0]  )  );
		if  (  p->status.recv.dwTickCnt_recv_first  &&  !p->status.recv.dwTickCnt_recvd  )  {
			pIo->ucbReceiveing  =  TRUE;
			pIo->dwTickCnt_recv_first  =  p->status.recv.dwTickCnt_recv_first;
		}
		if  (  p->status.ucbSending  )  {
			pIo->ucbSending  =  TRUE;
			pIo->dwTickCnt_snd_start  =  p->status.snd.dwTickCnt_snd_start;
		}
	}
	return  0;
}

 int  getDaemonStatusMsgrMem(  MT_SOCK_IOCP  *  pMtSock,  QMEM_MESSENGER  *  pQMemObj,  GET_daemonStatus_req  *  pResp  )
{
	int		iErr	=	-1;

	if  (  !pMtSock  ||  !pQMemObj  ||  !pResp  )  return  -1;

	if  (  pResp->usCnt  >=  mycountof(  pResp->u.msgr.mems  )  )  goto  errLabel;

	if  (  pQMemObj->messenger.uiType  !=  CONST_objType_messenger  )  goto  errLabel;

	pResp->u.msgr.mems[pResp->usCnt].idInfo.ui64Id  =  pQMemObj->messenger.idInfo.ui64Id;

	int  i;
	unsigned  int	uiCliIndex;
	for  (  i  =  0;  i  <  mycountof(  pQMemObj->uiCliIndex_useds  );  i  ++  )  {
		 if  (  !bCliIndexValid(  pMtSock,  pQMemObj->uiCliIndex_useds[i]  )  )  continue;
		 uiCliIndex  =  pQMemObj->uiCliIndex_useds[i];

		 PER_SOCKET_CONTEXT  *  p  =  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[uiCliIndex];

		 switch  (  pQMemObj->uiChannelTypes[i]  )  {
				 case  CONST_channelType_talking:
					   getChannelStatus(  p,  &pResp->u.msgr.mems[pResp->usCnt].t.stat,  &pResp->u.msgr.mems[pResp->usCnt].t.io  );
					   break;
				 case  CONST_channelType_robot:
					   getChannelStatus(  p,  &pResp->u.msgr.mems[pResp->usCnt].f.stat,  &pResp->u.msgr.mems[pResp->usCnt].f.io  );
					   break;								
				 case  CONST_channelType_realTimeMedia:
					   getChannelStatus(  p,  &pResp->u.msgr.mems[pResp->usCnt].a.stat,  &pResp->u.msgr.mems[pResp->usCnt].a.io  );
					   break;
				 case  CONST_channelType_media:
					   getChannelStatus(  p,  &pResp->u.msgr.mems[pResp->usCnt].v.stat,  &pResp->u.msgr.mems[pResp->usCnt].v.io  );
					   break;
				 default: 
					     break;					  
		 }
				 
				 
	}

	pResp->usCnt  ++  ;

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  tmpHandler_getMsgrStatus_qmd(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int							iErr			=	-1;
	MT_SOCK_IOCP			*	pMtSock			=	(  MT_SOCK_IOCP  *  )p0;
	GET_daemonStatus_req	*	pResp			=	(  GET_daemonStatus_req  *  )p1;
	IM_GRP_MEM_QMD			*	pGrpMem			=	(  IM_GRP_MEM_QMD  *  )p2;

	getDaemonStatusMsgrMem(  pMtSock,  (  QMEM_MESSENGER  *  )pGrpMem->pQMemMessenger,  pResp  );

	return  0;
}


 ////////////////

  int  getDaemonStatusChannelMem(  MT_SOCK_IOCP  *  pMtSock,  int  iCliIndex,  GET_daemonStatus_req  *  pResp  )
{
	int		iErr	=	-1;

	if  (  !pMtSock  ||  !pResp  )  return  -1;

	MT_SOCK_CLIINFO_IOCP	*	pCliInfo			=	&pMtSock->cliInfos[iCliIndex];
	PER_SOCKET_CONTEXT  *  p  =  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[iCliIndex];
	QMD_SESSION  *  pSession  =  (  QMD_SESSION  *  )pMtSock->pSessions[iCliIndex];

	if  (  !pCliInfo->bUsed  )  return  0;

	if  (  pResp->usCnt  >=  mycountof(  pResp->u.msgr.mems  )  )  goto  errLabel;

	pResp->u.channel.mems[pResp->usCnt].uiCliIndex  =  iCliIndex;
	getChannelStatus(  p,  &pResp->u.channel.mems[pResp->usCnt].status.stat,  &pResp->u.channel.mems[pResp->usCnt].status.io  );
	pResp->u.channel.mems[pResp->usCnt].idInfo.ui64Id  =  pSession->debugInfo.idInfo.ui64Id;
	pResp->u.channel.mems[pResp->usCnt].uiChannelType  =  pSession->uiChannelType;

#ifdef  __DEBUG__
	#if  0
		traceLog(  _T(  "channel[%d].io %dkbps, %dkbps, %I64u, %s"  ),  iCliIndex,  
			pResp->u.channel.mems[pResp->usCnt].status.stat.uiInSpeedInKbps,  
			pResp->u.channel.mems[pResp->usCnt].status.stat.uiInSpeedInKbps,  
			pResp->u.channel.mems[pResp->usCnt].idInfo.ui64Id,
			qyGetDesByType1(  CONST_channelTypeTable,  pResp->u.channel.mems[pResp->usCnt].uiChannelType  )  );		
	#endif
#endif

	pResp->usCnt  ++  ;

	iErr  =  0;
errLabel:
	return  iErr;
  }


 //////////////

 int  getDaemonStatus_qmd(  void  *  pSubThreadInfoParam,  MIS_MSG_INPUT  *  pMsgInput,  QMD_SESSION  *  pSession,  TRAN_INFO_MIS  *  pTranInfo,  GET_daemonStatus_req  *  pResp  )
{
	 int									iErr													=	-1;
	 MT_SOCK_SUBTHREADINFO			*		pSubThreadInfo											=	(  MT_SOCK_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 CQyMcDaemon					*		pDaemon													=	(  CQyMcDaemon  *  )pSubThreadInfo->pParentParam;
	 QY_SERVICE_INFO				*		pServiceInfo											=	(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )pSubThreadInfo->iServiceId,  0  );
	 if  (  !pServiceInfo  )  return  -1;
	 QMD_VAR_MIS					*		pVar													=	(  QMD_VAR_MIS  *  )pServiceInfo->pVar;
	 MT_SOCK_IOCP					*		pMtSock													=	(  MT_SOCK_IOCP  *  )pServiceInfo->pMtSock;
	 if  (  !pMtSock  )  return  -1;
 
	 QMEM_MESSENGER					*		pQMemMessenger											=	(  QMEM_MESSENGER  *  )pSession->pQMemObj;
	 if  (  !pQMemMessenger  )  return  -1;
	 QY_MESSENGER_INFO				*		pMessenger												=	&pQMemMessenger->messenger;
	 //
	 //
	 IM_CONTENTU				*		pContent												=	NULL;

	 pContent  =  (  IM_CONTENTU  *  )&pMsgInput->data;
	 if  (  pContent->uiType  !=  CONST_imCommType_getDaemonStatusReq  )  goto  errLabel;

	 if  (  pContent->getDaemonStatusReq.ucbGetTotal  )  {
		 memcpy(  &pResp->total,  &pVar->status.netStats,  sizeof(  pResp->total  )  );
	 }

	 if  (  pContent->getDaemonStatusReq.iSubType  ==  CONST_iDaemonStatusType_msgr  )  {
		 if  (  pContent->getDaemonStatusReq.idInfo.ui64Id  )  {
			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER			*	pQMemObj;

			 //
			 if  (  !findQMemByKey(  0,  pSession->pServiceInfo->pObjQ,  &pContent->getDaemonStatusReq.idInfo,  &mem  )  )  {

				 if  (  !(  pQMemObj  =  (  QMEM_MESSENGER  *  )mem.pQMemObj  )  )  goto  errLabel;

				 if  (  pQMemObj->messenger.uiType  ==  CONST_objType_messenger  )  {
					 getDaemonStatusMsgrMem(  pMtSock,  pQMemObj,  pResp  );
					 }
				 else  if  (  pQMemObj->messenger.uiType  ==  CONST_objType_imGrp  )  {
						   pQMemObj->talkingFriendQ.qTraverse(  tmpHandler_getMsgrStatus_qmd,  pMtSock,  pResp  );
					       }
				 else  { 
					   traceLog(  _T(  "imGrp: unprocessed"  )  );
				 }
				 }
			 else  {  //  2012/02/19
				   qyShowInfo(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getDaemonStatus_qmd failed, %I64u not loaded"  ),  pContent->getDaemonStatusReq.idInfo.ui64Id  ); ///*初始化会话存储空间*/
			 }
		 }
		 }
	 else  if  (  pContent->getDaemonStatusReq.iSubType  ==  CONST_iDaemonStatusType_channel  )  {
			   int  i;

			   for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
				    getDaemonStatusChannelMem(  pMtSock,  i,  pResp  );
			   }

			   }
	 else
		 goto  errLabel;


	 iErr  =  0;
errLabel:
	 return  iErr;

}