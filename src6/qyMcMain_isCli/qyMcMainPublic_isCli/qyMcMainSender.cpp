

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture.h"
#include	"qmcAcm.h"
#include	"qyVk.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"
#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"

#include	"isCliHelpPublic.h"

  //  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressor_conference,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor_conference,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  QIS_DYN_BMP  *  pDynBmp,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  )
int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressor_conference,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor_conference,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  TALKER_ruleU  *  pRuleU,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  )
{
	int					iErr					=	-1;
	MC_VAR_isCli		*	pProcInfo				=	NULL;  
	QY_MC			*	pQyMc					=	NULL;
	TCHAR				tBuf[256]				=	_T(  ""  );
	CQyMalloc			mallocObj;
	QY_SHARED_OBJ  *	pSharedObj				=	NULL;
	//  int				iIndex_sharedObjUsr		=	0;
	SHARED_OBJ_USR	*	pSharedObjUsr			=	NULL;

	BOOL				ucbSendLocalAv			=	FALSE;

	//  2013/02/11
	BOOL				bReSend_viewDynBmp		=	FALSE;
	QIS_DYN_BMP		*	pDynBmp					=	NULL;

	#ifdef  __DEBUG__
			traceLog(  _T(  "procSendAvInfo called"  )  );	
	#endif

	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMcParam;
	if  (  !pQyMc  )  return  -1;

	//  2013/02/11
	if  (  pRuleU  )  {
		if  (  pRuleU->uiType  ==  CONST_vwRuleType_dynBmp  )  {
			pDynBmp  =  &pRuleU->dynBmp.dynBmp;
			//
			if  (  pRuleU->dynBmp.taskInfo.iTaskId  )  {
				if  (  uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
					bReSend_viewDynBmp  =  TRUE;
				}
			}
		}
	}


	//
	switch  (  uiTaskType  )  {
		    case  CONST_imTaskType_transferAvInfo:
				  ucbSendLocalAv  =  TRUE;
				  break;
			default:
					break;
	}


	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  {
		if  (  uiTaskType  !=  CONST_imTaskType_viewDynBmp  )  goto  errLabel;
		}
	else  {		//  2010/09/04
		  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
		  if  (  !pSharedObjUsr  )  goto  errLabel;
		  //
		  if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			  pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
		  if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  
			  pSharedObjUsr->uiTranNo_openAvDev_v  =  pCompressVideo->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
	}

	//  tStartTime, uiTranNo
	MACRO_prepareForTran(  );

	//  2013/02/13
	if  (  bReSend_viewDynBmp  )  {
		tStartTran  =  pRuleU->dynBmp.taskInfo.tStartTran;
		uiTranNo  =  pRuleU->dynBmp.taskInfo.uiTranNo;
	}

	//  
	MIS_MSG_TASK				*	pMsg;
	if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.malloc(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;
	TRANSFER_AV_INFO			*	pContent;
	unsigned  int					lenInBytes;
	IM_TASK_RCD						rcd;
	//
	MACRO_memset_misMsgTask(  pMsg  );
	pMsg->uiType  =  CONST_misMsgType_task;
	//
	pMsg->pMisCnt  =  pMisCnt;
	//
	pMsg->ucFlg  =  CONST_commFlg_talkData;
	//
	pMsg->usCode  =  CONST_qyCmd_sendMedia;
	pMsg->tStartTime  =  tStartTran;
	pMsg->uiTranNo  =  uiTranNo;
	//
	pContent  =  (  TRANSFER_AV_INFO  *  )pMsg->data.buf;
	memset(  pContent,  0,  sizeof(  pContent[0]  )  );
	pContent->uiType  =  CONST_imCommType_transferAvInfo;
	pContent->uiTaskType  =  uiTaskType;

	pContent->myTask.ucbSendLocalAv  =  ucbSendLocalAv;									//  2008/06/12
	pContent->myTask.iIndex_sharedObj  =  iIndex_sharedObj;

	pContent->myTask.ucbStarter  =  TRUE;												//  2010/08/31
	if  (  !pVideoConferenceCfg  )  {
		switch  (  uiTaskType  )  {
			    case  CONST_imTaskType_transferAvInfo:
					  pContent->myTask.usCntLimit_mems_from  =  2;						//  2010/08/31
					  pContent->myTask.usCntLimit_activeMems_from  =  2;

					  break;
				default:
						pContent->myTask.usCntLimit_mems_from  =  2;					//  2010/09/03
						break;
		}
		}
	else  {
		  memcpy(  &pContent->myTask.videoConferenceCfg,  pVideoConferenceCfg,  sizeof(  pVideoConferenceCfg[0]  )  );
		  pContent->myTask.usCntLimit_mems_from  =  pContent->myTask.videoConferenceCfg.iRows  *  pContent->myTask.videoConferenceCfg.iCols;
		  pContent->myTask.usCntLimit_activeMems_from  =  pContent->myTask.videoConferenceCfg.usCntLimit_activeMems_from;
		  pContent->myTask.ucbVideoConference  =  TRUE;					//  2009/05/30
		  pContent->myTask.ucbVideoConferenceStarter  =  TRUE;
	}
	if  (  !pContent->myTask.usCntLimit_mems_from  ||  pContent->myTask.usCntLimit_mems_from  >  MAX_mems_taskAv  )  goto  errLabel;

	//
	if  (  pAddr  )  {
		if  (  pAddr->uiObjType  ==  CONST_objType_imGrp  )  {									   
			pContent->bGrpTask  =  TRUE; //  2007/09/05, ¸³ÉÏ×é±êÊ¶									   
		}
	}


	// audio
	if  (  !pContent->myTask.ucbVideoConferenceStarter  )  {
		if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  ×Ô¼ºÃ»ÓÐÉãÏàÍ¶Ê±£¬ÕâÀïÊÇÓÃÀ´ÇëÇó¿´Ô¶³ÌµÄÊÓÆµÍ·
			if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent->tranInfo.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
			pContent->tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;

			//
			pContent->tranInfo.video.usCapDriverIndex  =  pCompressVideo->usCapDriverIndex;
			//			
			//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  pContent->tranInfo.video.fourccStr,  mycountof(  pContent->tranInfo.video.fourccStr  )  );
			memcpy(  &pContent->tranInfo.video.compressor,  &pCompressVideo->compressor,  sizeof(  pContent->tranInfo.video.compressor  )  );

			memcpy(  &pContent->tranInfo.video.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  pContent->tranInfo.video.vh_compress  )  );
			memcpy(  &pContent->tranInfo.video.vh_decompress,  &pCompressVideo->vh_decompress,  sizeof(  pContent->tranInfo.video.vh_decompress  )  );
		}

		if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent->tranInfo.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
			pContent->tranInfo.audio.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;
			//
			//  memcpy(  &pContent->tranInfo.audio.wf_compress,  &pCompressAudio->policy.compressor.wf_compress,  sizeof(  pContent->tranInfo.audio.wf_compress  )  );
			//  memcpy(  &pContent->tranInfo.audio.wf_decompress,  &pCompressAudio->waveFormatEx,  sizeof(  pContent->tranInfo.audio.wf_decompress  )  );	//  2009/04/27
			memcpy(  &pContent->tranInfo.audio.compressor,  &pCompressAudio->compressor,  sizeof(  pContent->tranInfo.audio.compressor  )  );
			memcpy(  &pContent->tranInfo.audio.ah_compress,  &pCompressAudio->ah_compress,  sizeof(  pContent->tranInfo.audio.ah_compress  )  );
			memcpy(  &pContent->tranInfo.audio.ah_decompress,  &pCompressAudio->ah_decompress,  sizeof(  pContent->tranInfo.audio.ah_decompress  )  );
		}

		if  (  pDynBmp  )  {		//  2009/09/07
			pContent->viewDynBmp.uiObjType  =  pDynBmp->uiObjType;
			pContent->viewDynBmp.usIndex  =  pDynBmp->usIndex;
		}

		}
	else  {
		  if  (  !pVideoCompressor_conference  ||  !pAudioCompressor_conference  )  {
			  traceLogA(  "procSendAvInfo: pVideoConferenceCompressor can't be null for a conference starter"  );
			  goto  errLabel;
		  }

		  pContent->tranInfo.usCntLimit_mems_from  =  pContent->myTask.usCntLimit_mems_from;				//  2009/05/30
		  pContent->tranInfo.usCntLimit_activeMems_from  =  pContent->myTask.usCntLimit_activeMems_from;	//  2010/06/31

		  pContent->tranInfo.video.uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );		  
		  //  2009/04/19
		  pContent->tranInfo.video.usMaxFps_toShareBmp_videoConference  =  pVideoCompressor_conference->common.usMaxFps_toShareBmp;	//  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;
		  //
		  memcpy(  &pContent->tranInfo.video.compressor,  pVideoCompressor_conference,  sizeof(  pContent->tranInfo.video.compressor  )  );

		  //
		  pContent->tranInfo.audio.uiTranNo_openAvDev  =  pContent->tranInfo.video.uiTranNo_openAvDev;
		  //
		  memcpy(  &pContent->tranInfo.audio.compressor,  pAudioCompressor_conference,  sizeof(  pContent->tranInfo.audio.compressor  )  );
		  //
		  memcpy(  &pContent->tranInfo.audio.ah_compress.wfx,  &pAudioCompressor_conference->wf_compress,  sizeof(  pContent->tranInfo.audio.ah_compress.wfx  )  );
		  memcpy(  &pContent->tranInfo.audio.ah_decompress.wfx,  &pAudioCompressor_conference->wf_decompress_default,  sizeof(  pContent->tranInfo.audio.ah_decompress.wfx  )  );		  

		  //  2009/06/03
#if  0
		  memcpy(  &pContent->tranInfo.audio.playCfg,  &pAudioCompressor_conference->playCfg,  sizeof(  pContent->tranInfo.audio.playCfg  )  );
#endif


		  //  2009/05/30
		  #if  0
				if  (  pSharedObj  )  pSharedObj->uiTranNo_videoConferenceStarter  =  pContent->tranInfo.video.uiTranNo_openAvDev;
		  #endif

	}
	//  2011/12/10
#if  0
	if  (  pCompressVideo  )  {
		pContent->tranInfo.video.ucbFlipped  =  pCompressVideo->ucbOutputFlippedImg;
	}
#endif


	//  
	pContent->myTask.mem0_from.idInfo.ui64Id  =  pMisCnt->idInfo.ui64Id;		
	pContent->myTask.mem0_from.tStartTime_task  =  tStartTran;
	//
	if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {
			//													 
		    if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent->myTask.mem0_from.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;						//  
			pContent->myTask.mem0_from.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;												//  
			//
			pContent->myTask.mem0_from.video.usCapDriverIndex  =  pCompressVideo->usCapDriverIndex;

			//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  pContent->myTask.mem0_from.video.fourccStr,  mycountof(  pContent->myTask.mem0_from.video.fourccStr  )  );
			memcpy(  &pContent->myTask.mem0_from.video.compressor,  &pCompressVideo->compressor,  sizeof(  pContent->myTask.mem0_from.video.compressor  )  );
			
			memcpy(  &pContent->myTask.mem0_from.video.vh_compress_recvd,  &pCompressVideo->vh_compress,  sizeof(  pContent->myTask.mem0_from.video.vh_compress_recvd  )  );
			//  memcpy(  &pContent->myTask.mem0_from.video.vh_decompress_recvd.bih,  (  pDlg->m_var.pProcInfo->av.localAv.videoCaptureProcInfo.bOrg2RgbBufInited  ?  &pDlg->m_var.pProcInfo->av.localAv.videoCaptureProcInfo.vh_rgb.bih  :  &pDlg->m_var.pProcInfo->av.localAv.videoCaptureProcInfo.vh_org.bih  ),  sizeof(  pContent->myTask.mem0_from.video.vh_decompress_recvd.bih  )  );
			memcpy(  &pContent->myTask.mem0_from.video.vh_decompress_recvd.bih,  &pCompressVideo->vh_decompress,  sizeof(  pContent->myTask.mem0_from.video.vh_decompress_recvd.bih  )  );
	}
	//	
	if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			if  (  !pSharedObjUsr  )  goto  errLabel;
			//  pContent->myTask.mem0_from.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
			pContent->myTask.mem0_from.audio.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;
			//		
			//  memcpy(  &pContent->myTask.mem0_from.audio.wf_compress_recvd,  &pCompressAudio->policy.compressor.wf_compress,  sizeof(  pContent->myTask.mem0_from.audio.wf_compress_recvd  )  );
			//  memcpy(  &pContent->myTask.mem0_from.audio.wf_decompress_recvd,  &pCompressAudio->waveFormatEx,  sizeof(  pContent->myTask.mem0_from.audio.wf_decompress_recvd  )  );
			memcpy(  &pContent->myTask.mem0_from.audio.compressor,  &pCompressAudio->compressor,  sizeof(  pContent->myTask.mem0_from.audio.compressor  )  );
			memcpy(  &pContent->myTask.mem0_from.audio.ah_compress_recvd,  &pCompressAudio->ah_compress,  sizeof(  pContent->myTask.mem0_from.audio.ah_compress_recvd  )  );
			memcpy(  &pContent->myTask.mem0_from.audio.ah_decompress_recvd,  &pCompressAudio->ah_decompress,  sizeof(  pContent->myTask.mem0_from.audio.ah_decompress_recvd  )  );
	}
	
	if  (  !pContent->myTask.ucbVideoConferenceStarter  )  {

#if  0
		//  2011/08/08
		POLICY_av	policyAv;
		if  (  getPolicyAv(  FALSE,  0,  &policyAv  )  )  goto  errLabel;

		//
		memcpy(  &pContent->myTask.audio.playCfg,  (  uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  ?  &policyAv.avCompressor.audio.playCfg  :  &policyAv.mediaFileCompressor.audio.playCfg,  sizeof(  pContent->myTask.audio.playCfg  )  );
#endif
		//  2012/01/27
		memcpy(  &pContent->myTask.audio.playCfg,  &pContent->tranInfo.audio.compressor.playCfg,  sizeof(  pContent->myTask.audio.playCfg  )  );

		}
	else  {

		  //  2009/06/03		
		  memcpy(  &pContent->myTask.audio.playCfg,  &pContent->tranInfo.audio.compressor.playCfg,  sizeof(  pContent->myTask.audio.playCfg  )  );

		  //  2009/06/04
		  pContent->myTask.video.usMaxFps_toShareBmp_videoConference  =  pContent->tranInfo.video.usMaxFps_toShareBmp_videoConference;
	}
	pContent->myTask.hWnd_task  =  hWnd_task;	//  2009/09/09

	//  2007/07/18
	pMsg->uiTaskType  =  uiTaskType;
	//
	pMsg->idInfo_taskSender.ui64Id  =  pMisCnt->idInfo.ui64Id;
	if  (  pAddr  )  {
		pMsg->idInfo_taskReceiver.ui64Id  =  pAddr->idInfo.ui64Id;
		pMsg->addr_logicalPeer.idInfo.ui64Id  =  pAddr->idInfo.ui64Id;
	}
	//
	pMsg->iStatus  =  CONST_imTaskStatus_req;


	//  ÕâÀïµÄ¸³ÖµËÆºõÓ¦ÔÚ·¢ËÍÊ±Ê¹ÓÃ, 2007/07/24
	pMsg->data.route.idInfo_from.ui64Id  =  pMsg->idInfo_taskSender.ui64Id;
	pMsg->data.route.idInfo_to.ui64Id  =  pMsg->idInfo_taskReceiver.ui64Id;
	//

	lenInBytes  =  sizeof(  pContent[0]  );
	pMsg->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  lenInBytes;

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !msg2TaskRcd(  pMisCnt,  pMsg,  CONST_qyRc_unknown,  &rcd  )  )  goto  errLabel;
	
	{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif
		//
		if  (  storeTaskInDb(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  &rcd,  FALSE  )  <  0  )  goto  errLabel;
	}

	//  2013/02/13
	if  (  bReSend_viewDynBmp  )  {
		if  (  rcd.id  !=  pRuleU->dynBmp.taskInfo.iTaskId  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "procSendAvInfo: reSend_viewDynBmp failed, rcd.id != taskInfo.iTaskId"  )  );
			#endif
			goto  errLabel;
		}
	}
	if  (  uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
		if  (  pRuleU  &&  pRuleU->uiType  ==  CONST_vwRuleType_dynBmp  )  {
			if  (  pRuleU->dynBmp.taskInfo.bNeedProgress  )  {
				startProgress(  uiTranNo  );
			}
		}
	}
	
	//
	pMsg->iTaskId  =  rcd.id;
	pMsg->uiTaskMode_unused  =  rcd.uiMode;
	pMsg->uiChannelType  =  CONST_channelType_media;		//  2009/10/17

	if  (  bDlgTalk  )  {
		DLG_TALK_var	&	m_var	=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hWnd_task  );

		PARAM_PROC_ROW  param;
		memset(  &param,  0,  sizeof(  param  )  );
		param.bScrollIntoView  =  TRUE;
		if  (  tmpHandler_showMsg(  hWnd_task,  &param,  pMsg  )  )  goto  errLabel;

		//
		if  (  dlgTalk_qPostMsg(  hWnd_task,  pMsg,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->lenInBytes  )  )  goto  errLabel;
	}

	///////////////
	//
#if  0	//  2010/09/09
	if  (  pAddr  &&  pSharedObj  &&  pSharedObjUsr  )  {
		pSharedObjUsr->ucbNotSendData  =  (  ucbSendLocalAv  &&  pAddr->uiObjType  ==  CONST_objType_imGrp  );
		if  (  setROUTE_sendLocalAv(  pProcInfo,  pMisCnt,  &pAddr->idInfo,  pContent->myTask.ucbVideoConferenceStarter,  pSharedObj  )  )  {
			traceLogA(  "Onstartavcall: setROUTE_sendLocalAv failed."  );		//  
		}
	}
#endif

	//  2009/04/28
	if  (  pSharedObj  )  {
		if  (  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->iTaskId  =  rcd.id;
		//
		if  (  pAddr  )  {
			pSharedObjUsr->idInfo_to.ui64Id  =  pAddr->idInfo.ui64Id;			//  2010/09/02
			pSharedObjUsr->ucbVideoConferenceStarter  =  pContent->myTask.ucbVideoConferenceStarter;
			//
			pSharedObjUsr->ucbNotSendData  =  (  ucbSendLocalAv  &&  pAddr->uiObjType  ==  CONST_objType_imGrp  );
		}
	}
	if  (  piTaskId  )  *piTaskId  =  rcd.id;

	//
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )pContent,  lenInBytes,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

	//  2009/02/20
	if  (  bDlgTalk  )  {
		DLG_TALK_var	&	m_var	=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hWnd_task  );

		if  (  uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
			assert(  !m_var.av.taskInfo.bTaskExists  );
			memset(  &m_var.av.taskInfo,  0,  sizeof(  m_var.av.taskInfo  )  );
			m_var.av.taskInfo.bTaskExists  =  TRUE;
			m_var.av.taskInfo.iTaskId  =  rcd.id;
			//  m_var.av.taskInfo.iIndex_sharedObj  =  iIndex_sharedObj;
			m_var.av.taskInfo.idInfo_starter.ui64Id  =  rcd.idInfo_send.ui64Id;
		
			m_var.av.taskInfo.tStartTime_org  =  rcd.tSendTime;
			m_var.av.taskInfo.uiTranNo_org  =  rcd.uiTranNo;
			m_var.av.taskInfo.uiContentType_org  =  rcd.uiContentType;

			m_var.av.taskInfo.ucbStarter  =  pContent->myTask.ucbStarter;									//  2010/08/31
			m_var.av.taskInfo.ucbVideoConference  =  pContent->myTask.ucbVideoConference;					//  2010/08/31
			//  m_var.av.taskInfo.ucbVideoConferenceStarter  =  pContent->myTask.ucbVideoConferenceStarter;

			//
			m_var.av.taskInfo.uiInitW  =  pContent->tranInfo.video.vh_decompress.bih.biWidth;
			m_var.av.taskInfo.uiInitH  =  pContent->tranInfo.video.vh_decompress.bih.biHeight;

			//  2010/08/31
			if  (  !m_var.av.taskInfo.ucbVideoConference  )  {
				//  m_var.av.taskInfo.bNeedAutoRequestToSpeak  =  TRUE;
			}

			//
			assert(  !m_var.videoConference.pMems_from  );
			memset(  &m_var.videoConference,  0,  sizeof(  m_var.videoConference  )  );
			//  				
			if  (  !m_var.av.taskInfo.ucbVideoConference  )  {		//  2013/04/09. 在一对一时,自动将自己加入话筒列表,以便显示.				
				DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  NULL;

				m_var.videoConference.activeMems_from[0].mem.idInfo.ui64Id  =  pMisCnt->idInfo.ui64Id;
				_sntprintf(  m_var.videoConference.activeMems_from[0].desc,  mycountof(  m_var.videoConference.activeMems_from[0].desc  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
				#ifdef  __DEBUG__
						traceLog(  _T(  "Note: 	在一对一时,自动将自己加入话筒列表,以便显示."  )  );
				#endif
				//  2013/04/10
				if  (  pAddr  )  {
					pActiveMem_from  =  &m_var.videoConference.activeMems_from[1];
					pActiveMem_from->mem.idInfo.ui64Id  =  pAddr->idInfo.ui64Id;
					_sntprintf(  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  ),  _T(  "%s(%I64u)"  ),  _T(  ""  ),  pAddr->idInfo.ui64Id  );
				}
			}

			//
			//  if  (  pContent->myTask.ucbVideoConferenceStarter  )  
			{
				//
				m_var.videoConference.usCntLimit_mems_from  =  pContent->myTask.usCntLimit_mems_from;
				m_var.videoConference.usCntLimit_activeMems_from  =  pContent->myTask.usCntLimit_activeMems_from;
				lenInBytes  =  m_var.videoConference.usCntLimit_mems_from  *  sizeof(  DLG_TALK_videoConferenceMemFrom  );
				if  (  lenInBytes  )  {
					m_var.videoConference.pMems_from  =  (  DLG_TALK_videoConferenceMemFrom  *  )malloc(  lenInBytes  );
					if  (  !m_var.videoConference.pMems_from  )  goto  errLabel;
					memset(  m_var.videoConference.pMems_from,  0,  lenInBytes  );
				}
			}
		}
	}

	//  2013/02/13
	if  (  uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
		if  (  pRuleU  &&  pRuleU->uiType  ==  CONST_vwRuleType_dynBmp  )  {
			if  (  !bReSend_viewDynBmp  )  {  //  新任务才需要设置
				pRuleU->dynBmp.taskInfo.iTaskId  =  rcd.id;
				pRuleU->dynBmp.taskInfo.tStartTran  =  tStartTran;
				pRuleU->dynBmp.taskInfo.uiTranNo  =  uiTranNo;
			}
		}
	}

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Start AV:"  )  );
	if  (  pCompressVideo  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s video %d, maxFps %d, minFps %d."  ),  tBuf,  pCompressVideo->uiTranNo_openAvDev_org,  (  int  )pCompressVideo->compressor.common.usMaxFps_toShareBmp,  (  int  )pCompressVideo->compressor.common.usMinFps_toShareBmp  );
	if  (  pCompressAudio  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s audio %d"  ),  tBuf,  pCompressAudio->uiTranNo_openAvDev_org  );
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	
	iErr  =  0;
errLabel:

	//  2013/02/13
	if  (  iErr  )  {
		if  (  bReSend_viewDynBmp  )  {  //  重发viewDynBmp如果失败
		}
	}

	return  iErr;
}


 //  int  procSendAvInfo(  MIS_CNT  *  pMisCnt,  unsigned  int  uiTaskType,  VIDEO_CONFERENCE_CFG  *  pVideoConferenceCfg,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressor_conference,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor_conference,  COMPRESS_VIDEO  *  pCompressVideo,  COMPRESS_AUDIO  *  pCompressAudio,  int  iIndex_sharedObj,  QIS_DYN_BMP  *  pDynBmp,  MSGR_ADDR  *  pAddr  )
 int  procSendAvReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  MSGR_ADDR  *  pAddr  )
{
	int								iErr								=	-1;
	MC_VAR_isCli					*	pProcInfo							=	NULL;
	QY_MC						*	pQyMc								=	NULL;
	IM_CONTENTU					*	pContent							=	NULL;	
	
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMcParam;
	if  (  !pQyMc  )  return  -1;

	pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

	TRANSFER_AV_replyInfo	transferAvReplyInfo;
	int						lenInBytes						=	0;
	QY_SHARED_OBJ		*	pSharedObj						=	NULL;
	SHARED_OBJ_USR		*	pSharedObjUsr					=	NULL;
					  		
	pSharedObj  =	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  ucbSendLocalAv  )  {
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		if  (  !pSharedObjUsr  )  goto  errLabel;
	}
									
	//  ·¢ËÍ½ÓÊÕÔÊÐí¸ø¶Ô·½
	memset(  &transferAvReplyInfo,  0,  sizeof(  transferAvReplyInfo  )  );
	transferAvReplyInfo.uiType  =  CONST_imCommType_transferAvReplyInfo;
	transferAvReplyInfo.usOp  =  CONST_imOp_recv_accept;
	transferAvReplyInfo.tStartTime_org  =  pMsgTask->tStartTime;
	transferAvReplyInfo.uiTranNo_org  =  pMsgTask->uiTranNo;
	//
	if  (  ucbSendLocalAv  )  {	//  ±¾µØÊÓÆµÒ²ÔÊÐí·¢ËÍµÄÇé¿öÏÂ£¬Ò²·¢ËÍ¸ø¶Ô·½¡£
		CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		CAP_procInfo_audioU	*	pCapAudio	=	getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
		COMPRESS_VIDEO	*	pCompressVideo  =  NULL;	//  &pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo;
		COMPRESS_AUDIO  *	pCompressAudio  =  NULL;	//  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio;

		if  (  pCapBmp  )  pCompressVideo  =  &pCapBmp->common.compressVideo;
		if  (  pCapAudio  )  pCompressAudio  =  &pCapAudio->common.compressAudio;

		if  (  pCompressVideo  )  {
			//  2009/04/19
			if  (  pContent->transferAvInfo.tranInfo.video.usMaxFps_toShareBmp_videoConference  )  {
				//  pCompressVideo->usMaxFps_toShareBmp  =  min(  pContent->transferAvInfo.tranInfo.video.usMaxFps_toShareBmp_videoConference,  pCompressVideo->usMaxFps_toShareBmp  );    
				//  2009/06/04
				transferAvReplyInfo.myTask.video.usMaxFps_toShareBmp_videoConference  =  pCompressVideo->compressor.common.usMaxFps_toShareBmp;
			}

			//
			//  transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
			transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;
			//
			transferAvReplyInfo.tranInfo.video.usCapDriverIndex  =  pCompressVideo->usCapDriverIndex;
			//  safeStrnCpy(  pCompressVideo->compressor.fourccStr,  transferAvReplyInfo.tranInfo.video.fourccStr,  mycountof(  transferAvReplyInfo.tranInfo.video.fourccStr  )  );
			memcpy(  &transferAvReplyInfo.tranInfo.video.compressor,  &pCompressVideo->compressor,  sizeof(  transferAvReplyInfo.tranInfo.video.compressor  )  );
			memcpy(  &transferAvReplyInfo.tranInfo.video.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  transferAvReplyInfo.tranInfo.video.vh_compress  )  );
			//  memcpy(  &transferAvReplyInfo.tranInfo.video.vh_decompress.bih,  pProcInfo->av.localAv.videoCaptureProcInfo.bOrg2RgbBufInited  ?  &pProcInfo->av.localAv.videoCaptureProcInfo.vh_rgb.bih  :  &pProcInfo->av.localAv.videoCaptureProcInfo.vh_org.bih,  sizeof(  transferAvReplyInfo.tranInfo.video.vh_decompress.bih  )  );
			memcpy(  &transferAvReplyInfo.tranInfo.video.vh_decompress.bih,  &pCompressVideo->vh_decompress.bih,  sizeof(  transferAvReplyInfo.tranInfo.video.vh_decompress.bih  )  );

			//  
			
		}
		if  (  pCompressAudio  )  {
			//
			//  transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  =  pCompressAudio->uiTranNo_openAvDev;
			transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;
			//  memcpy(  &transferAvReplyInfo.tranInfo.audio.wf_compress,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.policy.compressor.wf_compress,  sizeof(  transferAvReplyInfo.tranInfo.audio.wf_compress  )  );
			//  memcpy(  &transferAvReplyInfo.tranInfo.audio.wf_decompress,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.waveFormatEx,  sizeof(  transferAvReplyInfo.tranInfo.audio.wf_decompress  )  );
			memcpy(  &transferAvReplyInfo.tranInfo.audio.compressor,  &pCompressAudio->compressor,  sizeof(  transferAvReplyInfo.tranInfo.audio.compressor  )  );
			memcpy(  &transferAvReplyInfo.tranInfo.audio.ah_compress,  &pCompressAudio->ah_compress,  sizeof(  transferAvReplyInfo.tranInfo.audio.ah_compress  )  );
			memcpy(  &transferAvReplyInfo.tranInfo.audio.ah_decompress,  &pCompressAudio->ah_decompress,  sizeof(  transferAvReplyInfo.tranInfo.audio.ah_decompress  )  );
		}
		//
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AvReply: maxFps %d, video %d, audio %d"  ),  (  pCompressVideo  ?  (  int  )pCompressVideo->compressor.common.usMaxFps_toShareBmp  :  0  ),  transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev,  transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  );
	}

	//  2008/06/12
	transferAvReplyInfo.myTask.ucbSendLocalAv  =  ucbSendLocalAv;
	transferAvReplyInfo.myTask.iIndex_sharedObj  =  iIndex_sharedObj;		//  ²»·¢±¾µØÊÓÆµµÄ£¬²»ÐèÒªÓÃsharedObj¿Õ¼ä
								
	//  ½«·¢¹ýÀ´µÄÑ¹ËõÐÅÏ¢´æÈëcontentµÄinternalÀï£¬ÓÃÔÚ½âÑ¹ËõÊ±
	//  int  index;  index  =  0;
	//
	transferAvReplyInfo.myTask.mem0_from.idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
	transferAvReplyInfo.myTask.mem0_from.tStartTime_task  =  pMsgTask->tStartTime;
	//
	if  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {							//  2009/06/01
		if  (  pAddr->uiObjType  ==  CONST_objType_imGrp  )  {									
			transferAvReplyInfo.myTask.ucbVideoConference  =  TRUE;							//  2009/05/30									
			transferAvReplyInfo.myTask.mem0_from.ucbVideoConferenceStarter  =  TRUE;		//  2009/04/02
		}
	}
	//
	transferAvReplyInfo.myTask.mem0_from.video.uiTranNo_openAvDev  =  pContent->transferAvInfo.tranInfo.video.uiTranNo_openAvDev;
	transferAvReplyInfo.myTask.mem0_from.video.usCapDriverIndex  =  pContent->transferAvInfo.tranInfo.video.usCapDriverIndex;

	//  safeStrnCpy(  pContent->transferAvInfo.tranInfo.video.fourccStr,  transferAvReplyInfo.myTask.mem0_from.video.fourccStr,  mycountof(  transferAvReplyInfo.myTask.mem0_from.video.fourccStr  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.compressor,  &pContent->transferAvInfo.tranInfo.video.compressor,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.compressor  )  );

	memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.vh_compress_recvd,  &pContent->transferAvInfo.tranInfo.video.vh_compress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.vh_compress_recvd  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.video.vh_decompress_recvd,  &pContent->transferAvInfo.tranInfo.video.vh_decompress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.video.vh_decompress_recvd  )  );
	//
	transferAvReplyInfo.myTask.mem0_from.audio.uiTranNo_openAvDev  =  pContent->transferAvInfo.tranInfo.audio.uiTranNo_openAvDev;
	//  memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.wf_compress_recvd,  &pContent->transferAvInfo.tranInfo.audio.wf_compress,  sizeof(  WAVEFORMATEX  )  );
	//  memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.wf_decompress_recvd,  &pContent->transferAvInfo.tranInfo.audio.wf_decompress,  sizeof(  WAVEFORMATEX  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.compressor,  &pContent->transferAvInfo.tranInfo.audio.compressor,  sizeof(  transferAvReplyInfo.myTask.mem0_from.audio.compressor  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.ah_compress_recvd,  &pContent->transferAvInfo.tranInfo.audio.ah_compress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.audio.ah_compress_recvd  )  );
	memcpy(  &transferAvReplyInfo.myTask.mem0_from.audio.ah_decompress_recvd,  &pContent->transferAvInfo.tranInfo.audio.ah_decompress,  sizeof(  transferAvReplyInfo.myTask.mem0_from.audio.ah_decompress_recvd  )  );
	//

	if  (  transferAvReplyInfo.myTask.ucbVideoConference  )  transferAvReplyInfo.myTask.usCntLimit_mems_from  =  min(  pContent->transferAvInfo.tranInfo.usCntLimit_mems_from,  MAX_mems_taskAv  );
	if  (  !transferAvReplyInfo.myTask.usCntLimit_mems_from  )  transferAvReplyInfo.myTask.usCntLimit_mems_from  =  1;	//  index  +  1;

	if  (  !transferAvReplyInfo.myTask.ucbVideoConference  )  {
		//  2011/08/08
		#if  0
			POLICY_av	policyAv;
			if  (  getPolicyAv(  TRUE,  0,  &policyAv  )  )  goto  errLabel;
		#endif
		AV_COMPRESSOR_CFG	tmpAvCompressor;
		if  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
			if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  TRUE,  0,  &tmpAvCompressor  )  )  goto  errLabel;
			}
		else  {
			  if  (  myGetAvCompressorCfg(  CONST_capType_mediaFile,  0,  0,  0,  &tmpAvCompressor  )  )  goto  errLabel;
		}

		//
		//  memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  ?  &policyAv.avCompressor.audio.playCfg  :  &policyAv.mediaFileCompressor.audio.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
		memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  &tmpAvCompressor.audio.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
		}
	else  {	//  2009/05/31
		  transferAvReplyInfo.myTask.usCntLimit_activeMems_from  =  pContent->transferAvInfo.tranInfo.usCntLimit_activeMems_from;
		  if  (  !transferAvReplyInfo.myTask.usCntLimit_activeMems_from  )  transferAvReplyInfo.myTask.usCntLimit_activeMems_from  =  min(  transferAvReplyInfo.myTask.usCntLimit_mems_from,  mycountof(  transferAvReplyInfo.myTask.activeMems_from  )  );
										
		  //  2009/06/03					
		  memcpy(  &transferAvReplyInfo.myTask.audio.playCfg,  &pContent->transferAvInfo.tranInfo.audio.compressor.playCfg,  sizeof(  transferAvReplyInfo.myTask.audio.playCfg  )  );
	}
	transferAvReplyInfo.myTask.hWnd_task  =  hWnd_task;		//  2009/09/09

	//
	lenInBytes  =  sizeof(  transferAvReplyInfo  );

	MACRO_prepareForTran(  );
	//
	//  if  (  postMsg2TaskQ_mc(  pQyMc,  pDlg->m_var.pSci,  pDlg->m_var.pMisCnt,  NULL,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pDlg->m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media  )  )  goto  errLabel;  
	//
	if  (  ucbSendLocalAv  )  {	
		if  (  !pSharedObj  ||  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->ucbNotSendData  =  (  pAddr->uiObjType  ==  CONST_objType_imGrp  );

		if  (  addToMsgrs_sendLocalAv(  pProcInfo,  pMisCnt,  &pMsgTask->idInfo_taskSender,  FALSE,  pSharedObj  )  )  goto  errLabel;
	}
	//  2012/04/01
	//  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;								
}


 //  int  procSendAvReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  MSGR_ADDR  *  pAddr  )
 int  procSendTaskProcReq(  MIS_CNT  *  pMisCnt,  unsigned  short  usCode,  unsigned  short  usOp,  time_t  tStartTime_org,  unsigned  int  uiTranNo_org,  unsigned  int  uiContentType_org,  int  iTaskId,  unsigned  int  uiTaskType,  QIS_DYN_BMP  *  pDynBmp,  unsigned  int  uiChannelType,  MSGR_ADDR  *  pAddr  )
{
	int					iErr		=	-1;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	TASK_PROC_REQ		taskProcReq;
	int					lenInBytes;

	memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
	taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
	taskProcReq.usOp  =  usOp;
	taskProcReq.tStartTime_org  =  tStartTime_org;
	taskProcReq.uiTranNo_org  =  uiTranNo_org;
	//  taskProcReq.uiSerialNo_org  =  uiSerialNo_org;
	taskProcReq.uiContentType_org  =  uiContentType_org;
	//
	taskProcReq.uiTaskType  =  uiTaskType;
	if  (  pDynBmp  )  {
		taskProcReq.viewDynBmp.uiObjType  =  pDynBmp->uiObjType;
		taskProcReq.viewDynBmp.usIndex  =  pDynBmp->usIndex;
	}
	//
	lenInBytes  =  sizeof(  taskProcReq  );			
	//					
	MACRO_prepareForTran(  );						
	//
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  usCode,  tStartTran,  uiTranNo,  0,  iTaskId,  uiTaskType,  (  char  *  )&taskProcReq,  lenInBytes,  &pAddr->idInfo,  NULL,  NULL,  &pAddr->idInfo,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}




 ////////////////////////////////////////////////////
 //  2012/04/19
  int  procSendGpsInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  BOOL  bDlgTalk,  unsigned  int  uiTaskType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr,  void  *  pReserved,  int  *  piTaskId,  MSGR_ADDR  *  pAddr  )
 {
	int					iErr					=	-1;
	MC_VAR_isCli		*	pProcInfo				=	NULL;  
	QY_MC			*	pQyMc					=	NULL;
	TCHAR				tBuf[256]				=	_T(  ""  );
	CQyMalloc			mallocObj;
	QY_SHARED_OBJ  *	pSharedObj				=	NULL;
	//  int				iIndex_sharedObjUsr		=	0;
	SHARED_OBJ_USR	*	pSharedObjUsr			=	NULL;

	#ifdef  __DEBUG__
			traceLog(  _T(  "procSendGpsInfo called"  )  );	
	#endif

	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMcParam;
	if  (  !pQyMc  )  return  -1;



	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  {
		if  (  uiTaskType  !=  CONST_imTaskType_viewGps  )  goto  errLabel;
		}
	else  {		//  2010/09/04
		  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
		  if  (  !pSharedObjUsr  )  goto  errLabel;
		  //
	}

	//  tStartTime, uiTranNo
	MACRO_prepareForTran(  );

	//  
	MIS_MSG_TASK				*	pMsg;
	if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.malloc(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;
	TRANSFER_GPS_INFO			*	pContent;
	unsigned  int					lenInBytes;
	IM_TASK_RCD						rcd;
	//
	MACRO_memset_misMsgTask(  pMsg  );
	pMsg->uiType  =  CONST_misMsgType_task;
	//
	pMsg->pMisCnt  =  pMisCnt;
	//
	pMsg->ucFlg  =  CONST_commFlg_talkData;
	//
	pMsg->usCode  =  CONST_qyCmd_sendMedia;
	pMsg->tStartTime  =  tStartTran;
	pMsg->uiTranNo  =  uiTranNo;
	//
	pContent  =  (  TRANSFER_GPS_INFO  *  )pMsg->data.buf;
	memset(  pContent,  0,  sizeof(  pContent[0]  )  );
	pContent->uiType  =  CONST_imCommType_transferGpsInfo;
	pContent->uiTaskType  =  uiTaskType;

	//
	pContent->myTask.iIndex_sharedObj  =  iIndex_sharedObj;
	//
	pContent->myTask.hWnd_task  =  hWnd_task;	//  2009/09/09

	//  2007/07/18
	pMsg->uiTaskType  =  uiTaskType;
	//
	pMsg->idInfo_taskSender.ui64Id  =  pMisCnt->idInfo.ui64Id;
	if  (  pAddr  )  {
		pMsg->idInfo_taskReceiver.ui64Id  =  pAddr->idInfo.ui64Id;
		pMsg->addr_logicalPeer.idInfo.ui64Id  =  pAddr->idInfo.ui64Id;
	}
	//
	pMsg->iStatus  =  CONST_imTaskStatus_req;


	//  ÕâÀïµÄ¸³ÖµËÆºõÓ¦ÔÚ·¢ËÍÊ±Ê¹ÓÃ, 2007/07/24
	pMsg->data.route.idInfo_from.ui64Id  =  pMsg->idInfo_taskSender.ui64Id;
	pMsg->data.route.idInfo_to.ui64Id  =  pMsg->idInfo_taskReceiver.ui64Id;
	//

	lenInBytes  =  sizeof(  pContent[0]  );
	pMsg->lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  lenInBytes;

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !msg2TaskRcd(  pMisCnt,  pMsg,  CONST_qyRc_unknown,  &rcd  )  )  goto  errLabel;
	
	{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif
		//
		if  (  storeTaskInDb(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  &rcd,  FALSE  )  <  0  )  goto  errLabel;
	}
		
	pMsg->iTaskId  =  rcd.id;
	pMsg->uiTaskMode_unused  =  rcd.uiMode;
	pMsg->uiChannelType  =  CONST_channelType_media;		//  2009/10/17


	///////////////
	//
#if  0	//  2010/09/09
	if  (  pAddr  &&  pSharedObj  &&  pSharedObjUsr  )  {
		pSharedObjUsr->ucbNotSendData  =  (  ucbSendLocalAv  &&  pAddr->uiObjType  ==  CONST_objType_imGrp  );
		if  (  setROUTE_sendLocalAv(  pProcInfo,  pMisCnt,  &pAddr->idInfo,  pContent->myTask.ucbVideoConferenceStarter,  pSharedObj  )  )  {
			traceLogA(  "Onstartavcall: setROUTE_sendLocalAv failed."  );		//  
		}
	}
#endif

	//  2009/04/28
	if  (  pSharedObj  )  {
		if  (  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->iTaskId  =  rcd.id;
		//
		if  (  pAddr  )  {
			pSharedObjUsr->idInfo_to.ui64Id  =  pAddr->idInfo.ui64Id;			//  2010/09/02
			//
		}
	}
	if  (  piTaskId  )  *piTaskId  =  rcd.id;

	//
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )pContent,  lenInBytes,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

	//  2009/02/20

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Start GPS:"  )  );
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	
	iErr  =  0;
errLabel:
	return  iErr;
}


 int  procSendGpsReplyInfo(  MIS_CNT  *  pMisCnt,  HWND  hWnd_task,  MIS_MSG_TASK  *  pMsgTask,  unsigned  char  ucbSendLocalAv,  int  iIndex_sharedObj,  MSGR_ADDR  *  pAddr  )
{
	int								iErr								=	-1;
	MC_VAR_isCli					*	pProcInfo							=	NULL;
	QY_MC						*	pQyMc								=	NULL;
	IM_CONTENTU					*	pContent							=	NULL;	
	
	if  (  !pMisCnt  )  return  -1;
	pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMcParam;
	if  (  !pQyMc  )  return  -1;

	pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

	TRANSFER_GPS_replyInfo	replyInfo;
	int						lenInBytes						=	0;
	QY_SHARED_OBJ		*	pSharedObj						=	NULL;
	SHARED_OBJ_USR		*	pSharedObjUsr					=	NULL;
					  		
	pSharedObj  =	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  ucbSendLocalAv  )  {
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		if  (  !pSharedObjUsr  )  goto  errLabel;
	}
									
	//  ·¢ËÍ½ÓÊÕÔÊÐí¸ø¶Ô·½
	memset(  &replyInfo,  0,  sizeof(  replyInfo  )  );
	replyInfo.uiType  =  CONST_imCommType_transferGpsReplyInfo;
	replyInfo.usOp  =  CONST_imOp_recv_accept;
	replyInfo.tStartTime_org  =  pMsgTask->tStartTime;
	replyInfo.uiTranNo_org  =  pMsgTask->uiTranNo;
	//

	//  2008/06/12
	//  replyInfo.myTask.ucbSendLocalAv  =  ucbSendLocalAv;
	replyInfo.myTask.iIndex_sharedObj  =  iIndex_sharedObj;		//  ²»·¢±¾µØÊÓÆµµÄ£¬²»ÐèÒªÓÃsharedObj¿Õ¼ä
								
	//  ½«·¢¹ýÀ´µÄÑ¹ËõÐÅÏ¢´æÈëcontentµÄinternalÀï£¬ÓÃÔÚ½âÑ¹ËõÊ±
	//  int  index;  index  =  0;
	//
	//
	if  (  pMsgTask->uiTaskType  ==  CONST_imTaskType_viewGps  )  {							//  2009/06/01
	}
	//


	replyInfo.myTask.hWnd_task  =  hWnd_task;		//  2009/09/09

	//
	lenInBytes  =  sizeof(  replyInfo  );

	MACRO_prepareForTran(  );
	//
	//  if  (  postMsg2TaskQ_mc(  pQyMc,  pDlg->m_var.pSci,  pDlg->m_var.pMisCnt,  NULL,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&replyInfo,  lenInBytes,  &pDlg->m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media  )  )  goto  errLabel;  
	//
	if  (  ucbSendLocalAv  )  {	
		if  (  !pSharedObj  ||  !pSharedObjUsr  )  goto  errLabel;

		pSharedObjUsr->ucbNotSendData  =  (  pAddr->uiObjType  ==  CONST_objType_imGrp  );

		if  (  addToMsgrs_sendLocalAv(  pProcInfo,  pMisCnt,  &pMsgTask->idInfo_taskSender,  FALSE,  pSharedObj  )  )  goto  errLabel;
	}
	//  2012/04/01
	//  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&replyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&replyInfo,  lenInBytes,  &pAddr->idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;								
}



