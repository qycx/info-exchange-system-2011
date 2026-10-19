

#include	"stdafx.h"
#include	<time.h>
#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture.h"

#include	"qyOpenShellCommon.h"

#ifdef  __SUPPORT_HTMLEDIT__
//	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"myresource.h"

#ifndef  __WINCE__
//		 #include	"DlgVideos.h"
		 //  #include	"DlgCfgVideoConference.h"
		 //  #include	"DlgPolicyIsClient.h"
		 //#include	"DlgInstantAssistant.h"
#endif
#include	<assert.h>
#ifndef  __WINCE__
		 //  #include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
		 #include	"qmcConferenceWall.h"
		 //  #include	"dlgProgress.h"
		 //  #include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"




 int  tmpHandler_refreshTaskAv_videoConferenceStarter(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsgElem  )
{
	int								iErr									=	-1;
	HWND							hDlgTalk								=	(  HWND  )p1;
	DLG_TALK_var				&	m_var									=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	int								i;
	unsigned  int					uiTranNo_lastModified_pMems_from		=	0;
	PROC_TASK_AV				*	pTask									=	NULL;
	DLG_TALK_videoConference	*	pVc;	
	
	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		IM_CONTENTU  *  pContent  =  (  IM_CONTENTU  *  )pMsgElem->task.data.buf;

		if  (  pMsgElem->task.pMisCnt  !=  m_var.pMisCnt  )  {
			iErr  =  0;  goto  errLabel;
		}
	
		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:
					  pTask  =  &pContent->transferAvInfo.myTask;
					  pVc  =  &m_var.videoConference;
					  if  (  pMsgElem->task.iTaskId  !=  m_var.av.taskInfo.iTaskId  )  break;

					  if  (  pTask->usCntLimit_mems_from  !=  pVc->usCntLimit_mems_from  )  {
						  traceLogA(  "tmpHandler_refreshTaskAv failed. task.usCntLimit_mems_from %d != vc.* %d",  pTask->usCntLimit_mems_from,  pVc->usCntLimit_mems_from  );
						  goto  errLabel;
					  }
					  if  (  pTask->usCntLimit_activeMems_from  !=  pVc->usCntLimit_activeMems_from  )  {
						  traceLogA(  "tmpHandler_refreshTaskAv failed. task.usCntLimit_activeMems_from %d != vc.* %d",  pTask->usCntLimit_activeMems_from,  pVc->usCntLimit_activeMems_from  );
						  goto  errLabel;
					  }
					  
					  uiTranNo_lastModified_pMems_from  =  pTask->uiTranNo_lastModified_pMems_from;
					  if  (  uiTranNo_lastModified_pMems_from  !=  pVc->uiTranNo_lastModified_pMems_from  )  {
						  for  (  i  =  0;  i  <  pTask->usCntLimit_mems_from;  i  ++  )  {
							   if  (  !pTask->pMems_from[i].idInfo.ui64Id  )  break;
							   pVc->pMems_from[i].idInfo.ui64Id  =  pTask->pMems_from[i].idInfo.ui64Id;
						  }
						  pVc->uiTranNo_lastModified_pMems_from  =  uiTranNo_lastModified_pMems_from;
					  }

					  if  (  pVc->bNeedRefresh_activeMems_from  )  {
						  for  (  i  =  0;  i  <  pTask->usCntLimit_activeMems_from;  i  ++  )  {
							   DLG_TALK_videoConferenceActiveMemFrom  *  pDlgActiveFrom		=	&pVc->activeMems_from[i];
							   BOOL										bFromModified		=	FALSE;

							   if  (  memcmp(  &pTask->activeMems_from[i],  &pVc->activeMems_from[i].mem,  sizeof(  pTask->activeMems_from[i]  )  )  )  {
								   traceLogA(  "tmpHandler_refreshTaskAv: activeMems_from[%d] modified",  i  );
								   memcpy(  &pTask->activeMems_from[i],  &pVc->activeMems_from[i].mem,  sizeof(  pTask->activeMems_from[i]  )  );
								   bFromModified  =  TRUE;
							   }
							   //
							   unsigned  short  usIndex_pMems_from  =  pDlgActiveFrom->mem.usIndex_pMems_from;
							   if  (  usIndex_pMems_from  <  0  ||  usIndex_pMems_from  >=  pTask->usCntLimit_mems_from  )  goto  errLabel;
							   TASK_AV_FROM	*	pFrom  =  &pTask->pMems_from[usIndex_pMems_from];
							   if  (  bFromModified
								   ||  pFrom->audio.uiTranNo_openAvDev  !=  pDlgActiveFrom->tranInfo.audio.uiTranNo_openAvDev
										||  pFrom->video.uiTranNo_openAvDev  !=  pDlgActiveFrom->tranInfo.video.uiTranNo_openAvDev  )
							   {
								   memset(  &pDlgActiveFrom->tranInfo,  0,  sizeof(  pDlgActiveFrom->tranInfo  )  );
								   
								   pDlgActiveFrom->tranInfo.audio.uiTranNo_openAvDev  =  pFrom->audio.uiTranNo_openAvDev;
								   #if  0	//  2011/12/24
										pDlgActiveFrom->tranInfo.audio.compressor.ucCompressors  =  pFrom->audio.compressor.ucCompressors;
								   #else
										memcpy(  &pDlgActiveFrom->tranInfo.audio.compressor,  &pFrom->audio.compressor,  sizeof(  pDlgActiveFrom->tranInfo.audio.compressor  )  );
								   #endif
								   memcpy(  &pDlgActiveFrom->tranInfo.audio.ah_decompress,  &pFrom->audio.ah_decompress_recvd,  sizeof(  pDlgActiveFrom->tranInfo.audio.ah_decompress  )  );
								   memcpy(  &pDlgActiveFrom->tranInfo.audio.ah_compress,  &pFrom->audio.ah_compress_recvd,  sizeof(  pDlgActiveFrom->tranInfo.audio.ah_compress  )  );

								   pDlgActiveFrom->tranInfo.video.uiTranNo_openAvDev  =  pFrom->video.uiTranNo_openAvDev;
								   //  pDlgActiveFrom->tranInfo.video.compressor.ucCompressors  =  pFrom->video.compressor.ucCompressors;
								   memcpy(  &pDlgActiveFrom->tranInfo.video.compressor,  &pFrom->video.compressor,  sizeof(  pDlgActiveFrom->tranInfo.video.compressor  )  );
								   memcpy(  &pDlgActiveFrom->tranInfo.video.vh_decompress,  &pFrom->video.vh_decompress_recvd,  sizeof(  pDlgActiveFrom->tranInfo.video.vh_decompress  )  );
								   memcpy(  &pDlgActiveFrom->tranInfo.video.vh_compress,  &pFrom->video.vh_compress_recvd,  sizeof(  pDlgActiveFrom->tranInfo.video.vh_compress  )  );
							   }								   
						  }						  
						  pVc->bNeedRefresh_activeMems_from  =  FALSE;
					  }

					  iErr  =  1;  goto  errLabel;
					  break;
				default:
						break;	
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  refreshTaskAv_videoConferenceStarter(  HWND    hDlgTalk  )
{
	DLG_TALK_var	&	m_var	=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  0;
	//  if  (  !m_var.av.taskInfo.ucbVideoConferenceStarter  )  return  0;
	if  (  !m_var.av.taskInfo.ucbStarter  )  return  0;

	return	pProcInfo->processQ_media.qTraverse(  (  PF_commonHandler  )tmpHandler_refreshTaskAv_videoConferenceStarter,  0,  (  void  *  )hDlgTalk  );

}



  int  tmpHandler_refreshTaskAv_videoConferenceOthers(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsgElem  )
{
	int								iErr									=	-1;
	HWND							hDlgTalk								=	(  HWND  )p1;
	DLG_TALK_var				&	m_var									=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	int								i;
	unsigned  int					uiTranNo_lastModified_pMems_from		=	0;
	PROC_TASK_AV				*	pTask									=	NULL;
	DLG_TALK_videoConference	*	pVc;	
	TCHAR							mutexName[128];
	MC_VAR_isCli					*	pProcInfo								=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	
	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		IM_CONTENTU  *  pContent  =  (  IM_CONTENTU  *  )pMsgElem->task.data.buf;

		if  (  pMsgElem->task.pMisCnt  !=  m_var.pMisCnt  )  {
			iErr  =  0;  goto  errLabel;
		}
	
		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvReplyInfo:
					  pTask  =  &pContent->transferAvReplyInfo.myTask;
					  pVc  =  &m_var.videoConference;
					  if  (  pMsgElem->task.iTaskId  !=  m_var.av.taskInfo.iTaskId  )  break;
					  
					  for  (  i  =  0;  i  <  pTask->usCntLimit_activeMems_from;  i  ++  )  {
						   DLG_TALK_videoConferenceActiveMemFrom  *  pDlgActiveFrom		=	&pVc->activeMems_from[i];

						   if  (  memcmp(  &pTask->activeMems_from[i],  &pVc->activeMems_from[i].mem,  sizeof(  pTask->activeMems_from[i]  )  )  )  {
							   traceLogA(  "tmpHandler_refreshTaskAv: activeMems_from[%d] modified",  i  );
							   memcpy(  &pTask->activeMems_from[i],  &pVc->activeMems_from[i].mem,  sizeof(  pTask->activeMems_from[i]  )  );
						   }
						   
						   //
						   if  (  !pDlgActiveFrom->mem.idInfo.ui64Id  )  continue;

						   unsigned  short  usIndex_pMems_from  =  pDlgActiveFrom->mem.usIndex_pMems_from;
						   if  (  usIndex_pMems_from  <  0  ||  usIndex_pMems_from  >=  pTask->usCntLimit_mems_from  )  goto  errLabel;
						   TASK_AV_FROM	*	pFrom  =  &pTask->pMems_from[usIndex_pMems_from];
						   if  (  pFrom->idInfo.ui64Id  !=  pDlgActiveFrom->mem.idInfo.ui64Id
							   ||  pFrom->audio.uiTranNo_openAvDev  !=  pDlgActiveFrom->tranInfo.audio.uiTranNo_openAvDev
									||  pFrom->video.uiTranNo_openAvDev  !=  pDlgActiveFrom->tranInfo.video.uiTranNo_openAvDev  )
						   {
							   CQySyncObj	syncObj;

							   _sntprintf(  mutexName,  mycountof(  mutexName  ),  _T(  "%s%d%d"  ),  pProcInfo->cfg.mutexName_syncActiveMem_prefix,  pMsgElem->task.iTaskId,  usIndex_pMems_from  );
							   if  (  syncObj.sync(  mutexName,  1000  )  )  goto  errLabel;

							   traceLogA(  "tmpHandler_refreshTaskAv: froms[%d] modified. %I64u  -> %I64u",  usIndex_pMems_from,  pFrom->idInfo.ui64Id,  pDlgActiveFrom->mem.idInfo.ui64Id  );

							   pFrom->idInfo.ui64Id  =  pDlgActiveFrom->mem.idInfo.ui64Id;
							   pFrom->audio.uiTranNo_openAvDev  =  pDlgActiveFrom->tranInfo.audio.uiTranNo_openAvDev;
							   #if  0   
									pFrom->audio.compressor.ucCompressors  =  pDlgActiveFrom->tranInfo.audio.compressor.ucCompressors;
							   #else
									memcpy(  &pFrom->audio.compressor,  &pDlgActiveFrom->tranInfo.audio.compressor,  sizeof(  pFrom->audio.compressor  )  );					
							   #endif								   
							   memcpy(  &pFrom->audio.ah_decompress_recvd,  &pDlgActiveFrom->tranInfo.audio.ah_decompress,  sizeof(  pFrom->audio.ah_decompress_recvd  )  );
							   memcpy(  &pFrom->audio.ah_compress_recvd,  &pDlgActiveFrom->tranInfo.audio.ah_compress,  sizeof(  pFrom->audio.ah_compress_recvd  )  );

							   pFrom->video.uiTranNo_openAvDev  =  pDlgActiveFrom->tranInfo.video.uiTranNo_openAvDev;
							   //  pFrom->video.compressor.ucCompressors  =  pDlgActiveFrom->tranInfo.video.compressor.ucCompressors;    
							   memcpy(  &pFrom->video.compressor,  &pDlgActiveFrom->tranInfo.video.compressor,  sizeof(  pFrom->video.compressor  )  );

							   memcpy(  &pFrom->video.vh_decompress_recvd,  &pDlgActiveFrom->tranInfo.video.vh_decompress,  sizeof(  pFrom->video.vh_decompress_recvd  )  );
							   memcpy(  &pFrom->video.vh_compress_recvd,  &pDlgActiveFrom->tranInfo.video.vh_compress,  sizeof(  pFrom->video.vh_compress_recvd  )  );
						   }								   
					  }						  
					  
					  iErr  =  1;  goto  errLabel;
					  break;
				default:
						break;	
		}
	}
	

	iErr  =  0;
errLabel:
	return  iErr;
}


 //  2009/05/31
 int  refreshTaskAv_videoConferenceOthers(  HWND  hDlg  )
{
	DLG_TALK_var	&	m_var	=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlg  );
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  0;
	//  if  (  m_var.av.taskInfo.ucbVideoConferenceStarter  )  return  0;
	if  (  m_var.av.taskInfo.ucbStarter  )  return  0;

	return  pProcInfo->processQ_media.qTraverse(  (  PF_commonHandler  )tmpHandler_refreshTaskAv_videoConferenceOthers,  0,  (  void  *  )hDlg  );
}


#ifdef  __DEBUG__
 int  printDlgTalkVideoConference(  DLG_TALK_videoConference  *  p  )
{
	int		i;
	
	traceLogA(  "printDlgTalkVideoConferenct starts"  );

	for  (  i  =  0;  i  <  p->usCntLimit_mems_from;  i  ++  )  {
		 if  (  p->pMems_from[i].idInfo.ui64Id  )  {		 
			 traceLogA(  "\tmems_from[%d].idInfo %I64u",  i,  p->pMems_from[i].idInfo.ui64Id  );
		 }
	}
	unsigned  short  usCntLimit_activeMems_from  =  p->usCntLimit_activeMems_from;
	if  (  !usCntLimit_activeMems_from  )  usCntLimit_activeMems_from  =  mycountof(  p->activeMems_from  );
	for  (  i  =  0;  i  <  usCntLimit_activeMems_from;  i  ++  )  {
		 if  (  p->activeMems_from[i].mem.idInfo.ui64Id  )  {
			 traceLogA(  "\tactiveMems[%d].idInfo %I64u, desc %S,  usIndex_mems_from %d",  i,  p->activeMems_from[i].mem.idInfo.ui64Id,  p->activeMems_from[i].desc,  p->activeMems_from[i].mem.usIndex_pMems_from  );
		 }
	}

	traceLogA(  "printDlgTalkVideoConferenct ends"  );

	return  0;
}
#endif


 BOOL  isMemFromRequesting(  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo_from  )
{
	int		i;

	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		 if  (  pIdInfo_from->ui64Id  ==  pVc->requestingMems_from[i].idInfo.ui64Id  )  break;
	}
	if  (  i  ==  mycountof(  pVc->requestingMems_from  )  )  return  FALSE;

	return  TRUE;
}

  int  addTo_requestingMems_from(  MIS_CNT  *  pMisCnt,  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int		i;

	if  (  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	if  (  isMemFromRequesting(  pVc,  pIdInfo  )  )  return  0;
	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		 if  (  !pVc->requestingMems_from[i].idInfo.ui64Id  )  break;
	}
	if  (  i  ==  mycountof(  pVc->requestingMems_from  )  )  return  -1;
	
	pVc->requestingMems_from[i].idInfo.ui64Id  =  pIdInfo->ui64Id;
	//  getTalkerDesc(  pMisCnt,  pIdInfo,  pVc->requestingMems_from[i].desc,  mycountof(  pVc->requestingMems_from[i].desc  ),  0,  0  );
	M_getActiveMemDesc(  pMisCnt,  pIdInfo,  pVc->requestingMems_from[i].desc,  mycountof(  pVc->requestingMems_from[i].desc  )  );

	return  0;
}

 int  removeFrom_requestingMems_from(  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		if  (  pVc->requestingMems_from[i].idInfo.ui64Id  ==  pIdInfo->ui64Id  )  {
			memset(  &pVc->requestingMems_from[i],  0,  sizeof(  pVc->requestingMems_from[i]  )  );
			break;			
		}
	}

	return  0;
}




 int  requestToSpeak_videoConferenceStarter(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  BOOL  bRequestToSpeak  )
{
	int								iErr								=	-1;
	DLG_TALK_var				&	m_var								=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli					*	pProcInfo							=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	DLG_TALK_videoConference	*	pVc									=	&m_var.videoConference;;
	int								i;
	int								index_activeMems_from;
	BOOL							bNeedRefresh_requestingMems_from	=	FALSE;
	BOOL							bNeedRefresh_display				=	FALSE;

	if  (  !pIdInfo->ui64Id  )  return  -1;

	if  (  refreshTaskAv_videoConferenceStarter(  hDlgTalk  )  <  0  )  return  -1;

	#ifdef  __DEBUG__
			printDlgTalkVideoConference(  &m_var.videoConference  );
	#endif

	if  (  bRequestToSpeak  )  {

		if  (  !isMemFromActive(  pVc,  pIdInfo,  NULL  )  )  {				
			for  (  i  =  0;  i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
				 if  (  !pVc->activeMems_from[i].mem.idInfo.ui64Id  )  break;			
			}
			if  (  i  ==  pVc->usCntLimit_activeMems_from  )  {
				traceLogA(  "ativeMems_from is full, try to add to requestingMems"  );  
				//
				if  (  !isMemFromRequesting(  pVc,  pIdInfo  )  )  {
					if  (  !addTo_requestingMems_from(  m_var.pMisCnt,  pVc,  pIdInfo  )  )  bNeedRefresh_requestingMems_from  =  TRUE;
				}
				}
			else  {
				    index_activeMems_from  =  i;

					for  (  i  =  0;  i  <  pVc->usCntLimit_mems_from;  i  ++  )  {
						 if  (  pVc->pMems_from[i].idInfo.ui64Id  ==  pIdInfo->ui64Id  )  break;
					}
					if  (  i  ==  pVc->usCntLimit_mems_from  )  {
						traceLogA(  "Not a permitted messenger."  );
						qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "requestToSpeak failed, %I64u not a permitted messenger. not in fromList"  ),  pIdInfo->ui64Id  );
						}
					else  {
						  pVc->activeMems_from[index_activeMems_from].mem.idInfo.ui64Id  =  pVc->pMems_from[i].idInfo.ui64Id;
						  pVc->activeMems_from[index_activeMems_from].mem.usIndex_pMems_from  =  i;
						  //  getTalkerDesc(  m_var.pMisCnt,  &pVc->activeMems_from[index_activeMems_from].mem.idInfo,  pVc->activeMems_from[index_activeMems_from].desc,  mycountof(  pVc->activeMems_from[index_activeMems_from].desc  ),  NULL,  0  );
						  M_getActiveMemDesc(  m_var.pMisCnt,  &pVc->activeMems_from[index_activeMems_from].mem.idInfo,  pVc->activeMems_from[index_activeMems_from].desc,  mycountof(  pVc->activeMems_from[index_activeMems_from].desc  )  );
						  //
						  pVc->bNeedRefresh_activeMems_from  =  TRUE;

						  traceLogA(  "alloc activeMems_from[%d] for %I64u, %d",  index_activeMems_from,  pIdInfo->ui64Id,  i  );	

						  if  (  isMemFromRequesting(  pVc,  pIdInfo  )  )  {
							  removeFrom_requestingMems_from(  pVc,  pIdInfo  );  
							  bNeedRefresh_requestingMems_from  =  TRUE;
						  }
					}
					
			  }
		}
		}
	else  {  //  stop speaking
		  for  (  i  =  0;  i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
			   if  (  pVc->activeMems_from[i].mem.idInfo.ui64Id  ==  pIdInfo->ui64Id  )  break;
		  }
		  if  (  i  <  pVc->usCntLimit_activeMems_from  )  {
			  memset(  &pVc->activeMems_from[i],  0,  sizeof(  pVc->activeMems_from[i]  )  );
			  //
			  pVc->bNeedRefresh_activeMems_from  =  TRUE;
		  }
		  //
		  if  (  isMemFromRequesting(  pVc,  pIdInfo  )  )  {
			  removeFrom_requestingMems_from(  pVc,  pIdInfo  );
			  bNeedRefresh_requestingMems_from  =  TRUE;
		  }
	}

	if  (  pVc->bNeedRefresh_activeMems_from  )  {
		if  (  refreshTaskAv_videoConferenceStarter(  hDlgTalk  )  <  0  )  goto  errLabel;
		bNeedRefresh_display  =  TRUE;
		
		//  2010/09/12
		if  (  !bRequestToSpeak  )  {
#if  0
			CAP_IMAGES	*	pImgs  =  &m_var.av.peerImages;
			freeCapImageBySth(  hDlgTalk,  0,  m_var.av.taskInfo.iTaskId,  pIdInfo,  pImgs  );
			//
			if  (  m_var.av.taskInfo.hWnd_remoteAv  )  {
				QY_WMBUF_COMM	wmBuf;
				memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				wmBuf.uiType  =  CONST_qyWmParam_freeCapImage;
				wmBuf.u.freeCapImage.iTaskId  =  m_var.av.taskInfo.iTaskId;
				wmBuf.u.freeCapImage.idInfo.ui64Id  =  pIdInfo->ui64Id;
				SendMessage(  m_var.av.taskInfo.hWnd_remoteAv,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
			}
#endif
			dlgTalk_freeCapImageBySth_mgr(  hDlgTalk,  m_var.av.taskInfo.iTaskId,  pIdInfo  );	//  2010/09/12
		}
	}
	if  (  bNeedRefresh_requestingMems_from  )  bNeedRefresh_display  =  TRUE;

	if  (  pIdInfo->ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  {	//  It is me
		QY_SHARED_OBJ	*	pSharedObj		=  NULL;
		SHARED_OBJ_USR	*	pSharedObjUsr	=	NULL;
		unsigned  char		ucbNotSendData	=	!isMemFromActive(  pVc,  pIdInfo,  NULL  );

	    #ifdef  __DEBUG__
				traceLogA(  "requestToSpeak: iIndex_sharedObj %d",  m_var.av.iIndex_sharedObj_localAv  );
		#endif

		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  );
		if  (  !pSharedObjUsr  )  goto  errLabel;

		if  (  pSharedObjUsr->ucbNotSendData  !=  ucbNotSendData  )  {
			pSharedObjUsr->ucbNotSendData  =  ucbNotSendData;
			bNeedRefresh_display  =  TRUE;
		}
		//
		if  (  !ucbNotSendData  )  {

			//  2009/05/30			
			isMemFromActive(  pVc,  pIdInfo,  &pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter  );

			//
			if  (  pSharedObj->iIndex_curUsr  ==  m_var.av.iIndex_usr_localAv  )  {
				//
				if  (  !m_var.av.taskInfo.ucbVideoConference  )  {
					#ifdef  __DEBUG__
							if  (  !pSharedObj->route_sendLocalAv.route.idInfo_to.ui64Id  )  {
								traceLog(  _T(  "requestToSpeak_videoConferenceStarter: inInfo_to error"  )  );				
							}
					#endif
					}
				else  {
					  if  (  !pSharedObj->route_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {				
						  if  (  addToMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &m_var.addr.idInfo,  TRUE,  pSharedObj  )  )  {
							traceLogA(  "requestToSpeak_videoConferenceStarter: addToMsgrs_sendLocalAv failed."  );		//  对视频会议的情况，如果已经有了，就不能再加进去了。但是不妨碍其他人参与视频会议。所以不能退出。
							goto  errLabel;					
						  }				
					  }	
				}
			
				//
				resumeLocalAudioRecorder(  m_var.av.iIndex_sharedObj_localAv  );
			}
		}

	}

	if  (  bNeedRefresh_display  )  SendMessage(  m_var.hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  requestToSpeak_videoConferenceOthers(  HWND  hDlgTalk,  BOOL  bRequestToSpeak  )
{
	int						iErr				=		-1;
	DLG_TALK_var		&	m_var				=		*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli			*	pProcInfo			=		(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
	
	if  (  bRequestToSpeak  )  {
		QY_SHARED_OBJ	*	pSharedObj		=  NULL;

		if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;

		if  (  pSharedObj->iIndex_curUsr  ==  m_var.av.iIndex_usr_localAv  )  {
			if  (  !pSharedObj->route_sendLocalAv.route.idInfo_to.ui64Id  )  {
				traceLog(  _T(  "Warning: requestToSpeak_videoConferenceOthers: idInfo_to is 0"  )  );
				if  (  addToMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &m_var.av.taskInfo.idInfo_starter,  FALSE,  pSharedObj  )  )  {
					traceLogA(  "requestToSpeak_videoConferenceOthers: addToMsgrs_sendLocalAv failed."  );		//  对视频会议的情况，如果已经有了，就不能再加进去了。但是不妨碍其他人参与视频会议。所以不能退出。
					goto  errLabel;
				}
			}

			//
			resumeLocalAudioRecorder(  m_var.av.iIndex_sharedObj_localAv  );

		}
	}

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	req.usOp  =  bRequestToSpeak  ?  CONST_imOp_requestToSpeak  :  CONST_imOp_stopSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	if  (  m_var.av.taskInfo.ucbVideoConference  )  req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &m_var.av.taskInfo.idInfo_starter,  0,  NULL,  FALSE  )  )  goto  errLabel;

	//
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  bRequestToSpeak  ?  _T(  "Request to speak"  )  :  _T(  "Request to stop speaking"  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  requestToRefreshActiveMems_videoConferenceOthers(  HWND  hDlgTalk  )
{
	int						iErr				=		-1;
	DLG_TALK_var		&	m_var				=		*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli			*	pProcInfo			=		(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
		

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	//  req.usOp  =  bRequestToSpeak  ?  CONST_imOp_requestToSpeak  :  CONST_imOp_stopSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &m_var.av.taskInfo.idInfo_starter,  0,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "requestToRefreshActiveMems %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	return  iErr;
}



 int  sendVideoConferenceStatus(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo_to  )
{
	int								iErr		=		-1;
	DLG_TALK_var				&	m_var		=		*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli				*	pProcInfo	=		(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	DLG_TALK_videoConference	*	pVc			=		&m_var.videoConference;
	VIDEO_CONFERENCE_STATUS			status;
	int								i;
	int								lenInBytes;

	if  (  !pIdInfo_to  ||  !pIdInfo_to->ui64Id  )  return  -1;

	if  (  pVc->bNeedRefresh_activeMems_from  )  return  -1;
	


	//
	memset(  &status,  0,  sizeof(  status  )  );
	status.uiType  =  CONST_imCommType_videoConferenceStatus;
	if  (  m_var.av.taskInfo.ucbVideoConference  )  status.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;

	//  2010/12/29
	if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.ucbStarter  )  {
		status.usLayoutType_starter  =  dlgTalk_get_usLayoutType_local(  hDlgTalk  );	//  m_var.av.usLayoutType_local;
	}

	//
	for  (  i  =  0;  i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
		 if  (  !pVc->activeMems_from[i].mem.idInfo.ui64Id  )  continue;
		 //  status.mems[status.usCnt].idInfo.ui64Id  =  pVc->activeMems_from[i].mem.idInfo.ui64Id;
		 memcpy(  &status.mems[status.usCnt].mem,  &pVc->activeMems_from[i].mem,  sizeof(  status.mems[status.usCnt].mem  )  );
		 status.mems[status.usCnt].ucbActive  =  TRUE;
		 memcpy(  &status.mems[status.usCnt].tranInfo,  &pVc->activeMems_from[i].tranInfo,  sizeof(  status.mems[status.usCnt].tranInfo  )  );	//  2009/05/31
		 status.usCnt  ++  ;
	}
	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		 if  (  !pVc->requestingMems_from[i].idInfo.ui64Id  )  continue;
		 status.mems[status.usCnt].mem.idInfo.ui64Id  =  pVc->requestingMems_from[i].idInfo.ui64Id;
		 status.usCnt  ++  ;
	}
	
	lenInBytes  =  sizeof(  status  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&status,  lenInBytes,  NULL,  NULL,  NULL,  pIdInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}






 //  VIDEO_CONFERNECE_LAYOUT

 int  sendVideoConferenceLayout(  unsigned  short  usLayoutType,  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo_to  )
{
	int								iErr		=		-1;
	DLG_TALK_var				&	m_var		=		*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli					*	pProcInfo	=		(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	VIDEO_CONFERENCE_LAYOUT			layout;
	int								i;
	int								lenInBytes;

	if  (  !pIdInfo_to  ||  !pIdInfo_to->ui64Id  )  return  -1;
	
	memset(  &layout,  0,  sizeof(  layout  )  );
	layout.uiType  =  CONST_imCommType_videoConferenceLayout;
	if  (  m_var.av.taskInfo.ucbVideoConference  )  layout.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;

	layout.usLayoutType  =  usLayoutType;
	
	lenInBytes  =  sizeof(  layout  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&layout,  lenInBytes,  NULL,  NULL,  NULL,  pIdInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  dlgTalk_requestToSpeak(  HWND  hDlgTalk,  BOOL  bEnable  )
{
	DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;

	if  (  !pDlgTalkVar->av.taskInfo.bTaskExists  )  return  -1;

	//  2010/12/19
	pDlgTalkVar->av.taskInfo.bEnableToSpeak  =  bEnable;

	//
	//  BOOL							bEnableState	=	m_var.canSpeak;
	BOOL								bEnableState	=	dlgTalk_canSpeak(  hDlgTalk  );


	if  (  pDlgTalkVar->av.taskInfo.ucbStarter  )  {
		requestToSpeak_videoConferenceStarter(  hDlgTalk,  &pDlgTalkVar->pMisCnt->idInfo,  bEnable  );
		if  (  (  bEnable  &&  !bEnableState  )  ||  (  !bEnable  &&  bEnableState  )  )  {
			sendVideoConferenceStatus(  hDlgTalk,  &pDlgTalkVar->addr.idInfo  );
		}
		}	
	else  {
		  //  if  (  (  bEnable  &&  !bEnableState  )  ||  (  !bEnable  &&  bEnableState  )  )  
		  {
			  requestToSpeak_videoConferenceOthers(  hDlgTalk,  bEnable  );
		  }
	}

	return  0;
}
