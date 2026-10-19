

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture.h"
#include	"tmpCeLib.h"




 int  showDebugInfo(  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  hint,  MIS_MSG_INPUT  *  pMsgInput  )
{
	char	timeBuf[CONST_qyTimeLen  +  1];

	if  (  !hint  )  hint  =  _T(  ""  );

	 	if  (  pMsgInput->data.route.debugInfo.tTime_start  )  {

			pMsgInput->data.route.debugInfo.usElapsed_resp_end  =  (  unsigned  short  )(  GetTickCount(  )  -  pMsgInput->data.route.debugInfo.dwTickCnt_resp_recved  );
		
			time_t	tNow;	mytime(  &tNow  );
			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.tTime_start,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 0: tn %d, start %s, toSend %u"  ), 
				hint,
				pMsgInput->uiTranNo,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.usElapsed_toSend  );

			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.req.tTime_serv_startToRecv,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 1:  s_t_startToRecv %s, s_toProcess %u, s_toFindDst %u, s_toBeSwitched %u, s_toSend %u"  ), 
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_startToProcess,
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_toFindDst,
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_toBeSwitched,
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_toSend  );

			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.tTime_peer_recved,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 2:  p_t_recved %s, p_resp_toSend %u"  ), 
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.usElapsed_peer_resp_toSend  );

			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.resp.tTime_serv_startToRecv,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 3: s_r_t_startToRecv %s, s_r_toProcess %u, s_r_toFindDst %u, s_r_toBeSwitched %u, s_r_toSend %u"  ),
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_startToProcess,
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_toFindDst,
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_toBeSwitched,
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_toSend  );
			
			getTimelStr(  tNow,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 4: resp_recved %s, resp_end %u"  ),
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.usElapsed_resp_end  );

				
	}

	 return  0;
 }









 int  procTaskVideoDataResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_VIDEO_dataResp  *  pResp,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
{															 
	int						iErr									=		-1;
	char					timeBuf[32]								=		"";
	TCHAR					tHintBuf[255  +  1]						=		_T(  "VideoDataResp: "  );
	unsigned  short			usFrames_perSecond_cli					=		pResp->usFrames_perSecond;
	//
	unsigned  char			ucTimeoutInS_showFrameInfoResp			=		0;
	unsigned  short			usFrames_perSecond_expected				=		0;
	time_t					tSelectTime								=		0;
	unsigned  int			uiCnt_pkts_fromSelect					=		0;
	int						i;
	//  unsigned  short			usDelay									=		0;
	TASK_AV_TO			*	pTo										=		NULL;
	//  int						iDiff_uiCnt_pkts_fromSelect				=		0;  

	QY_SHARED_OBJ		*	pSharedObj								=		getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );		//  这里应该用index来获取
	if  (  !pSharedObj  )  return  -1;
	COMPRESS_VIDEO		*	pCompressVideo							=		NULL;

	//  if  (  pSharedObj->bCapDev  )  pCompressVideo  =  &pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo;
	//  else  
	{
		  CAP_procInfo_bmpU  *  pCapProcInfo  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );		
		  if  (  !pCapProcInfo  )  return  -1;
		  pCompressVideo  =  &pCapProcInfo->common.compressVideo;
	}
	if  (  !pCompressVideo  )  return  -1;

	//  showDebugInfo(  pProcInfo,  _T(  "VideoResp"  ),  pMsgInput  );

	{
		//  CQySyncObj	syncObj;
		//  syncObj.sync(  pProcInfo->cfg.mutexName_syncAv  );

		ucTimeoutInS_showFrameInfoResp			=		pCompressVideo->ucTimeoutInS_showFrameInfoResp;
		usFrames_perSecond_expected				=		pCompressVideo->usFrames_perSecond_expected;
		tSelectTime								=		pCompressVideo->tSelectTime;
		uiCnt_pkts_fromSelect					=		pCompressVideo->uiCnt_pkts_fromSelect;
	}

	getTimelStr(  pMsgInput->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );

	//	
	if  (  pMsgInput->tRecvTime  <  pMsgInput->tStartTime  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: error: recvTime < startTime [%s], skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;
	}

	if  (  pMsgInput->tStartTime  <  tSelectTime  )  {
	
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: startTime [%s] < selectTime, skipped"  ),  CQyString(  timeBuf  )  );

		}
	else  {

		  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "VideoDataResp: %I64u, time-consuming %ds, fps %d/s, recvd pkts %d, diff %d. "  ),  pMsgInput->data.route.idInfo_from.ui64Id,  (  int  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  ),  (  long  )pResp->usFrames_perSecond,  (  long  )pResp->usCnt_pkts,  (  long  )pResp->usDiff_pkts    );
				
		  for  (  i  =  0;  i  <  pTask->resp.video.usCnt_to;  i  ++  )  {
			   if  (  pTask->resp.video.mems_to[i].idInfo.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id  )  break;
		  }
		  if  (  i  ==  pTask->resp.video.usCnt_to  )  {

			  //  没找到则找个空位置
			  for  (  ;  i  <  mycountof(  pTask->resp.video.mems_to  );  i  ++  )  {
				   if  (  !pTask->resp.video.mems_to[i].idInfo.ui64Id  )  break;
			  }
			  if  (  i  ==  mycountof(  pTask->resp.video.mems_to  )  )  {
				  qyShowInfo(  CONST_qyShowType_debug,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: mems_to[] is full. skipped."  )  );  
				  iErr  =  0;  goto  errLabel;
			  }
			  pTask->resp.video.mems_to[i].idInfo.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;
		
			  pTask->resp.video.usCnt_to  ++  ;

		  }

		  if  (  pTask->resp.video.tSelectTime  !=  tSelectTime  )  {
			  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: selectTime changed"  ),  pCompressVideo->usFrames_perSecond_expected  );

			  memset(  &pTask->resp.video,  0,  sizeof(  pTask->resp.video  )  );
			  //
			  pTask->resp.video.tSelectTime  =  tSelectTime;
			  }
		  else  {

			    pTo  =  &pTask->resp.video.mems_to[i];
				pTo->uiCnt_pkts_fromSelect  =  pResp->usCnt_pkts;

				//  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "VideoDataResp: %I64u, time-consuming %ds, fps %d/s, recvd pkts %d, diff %d. "  ),  pMsgInput->data.route.idInfo_from.ui64Id,  (  int  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  ),  (  long  )pResp->usFrames_perSecond,  (  long  )pResp->usCnt_pkts,  (  long  )pResp->usDiff_pkts    );
				
				if  (  !isRcOk(  pMsgInput->usCode  )  )  {
					pCompressVideo->usTimes_failure  ++  ;
					qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: rc %d not ok, startTime [%s], error"  ),  pMsgInput->usCode,  CQyString(  timeBuf  )  );
					}
				else  if  (  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  >  ucTimeoutInS_showFrameInfoResp  )  {	//  
					      pCompressVideo->usTimes_failure  ++  ;
						  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: time-consuming %d > ucTimeoutInS %d, error"  ),  (  int  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  ),  (  int  )ucTimeoutInS_showFrameInfoResp  );
						  }
				else  if  (  pResp->usDiff_pkts  >  pTo->iDiff_pkts_fromSelect  )  {
						  pCompressVideo->usTimes_failure  ++  ;
						  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoDataResp: diff increases, startTime %s, error"  ),  CQyString(  timeBuf  )  );
		 				  }
				else  {
					  pCompressVideo->usTimes_ok  ++  ;					
				}		
				
				pTo->iDiff_pkts_fromSelect  =  pResp->usDiff_pkts;	
				pTo->usDelay  =  pMsgInput->tRecvTime  -  pMsgInput->tStartTime;		//  2009/09/11
				pTo->tRecvTime_lastResp  =  pMsgInput->tRecvTime;						//  2009/09/11
				
				//  2009/09/11
				if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
					ROUTE_sendLocalAv	*	pRoute  =  &pSharedObj->curRoute_sendLocalAv;
					if  (  pRoute->route.idInfo_to.ui64Id  ==  pTo->idInfo.ui64Id  )  pSharedObj->routeInfo.tRecvTime_lastResp  =  pMsgInput->tRecvTime;
					else  {
						  for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
							   if  (  !pRoute->route.mems_to[i].idInfo.ui64Id  )  continue;
							   if  (  pRoute->route.mems_to[i].idInfo.ui64Id  ==  pTo->idInfo.ui64Id  )  {
								   pSharedObj->routeInfo.mems[i].tRecvTime_lastResp  =  pMsgInput->tRecvTime;
								   break;
							   }
						  }
					}
				}
		  }
	}
	
	//
	pCompressVideo->ucTimeoutInS_showFrameInfoResp  =  (  ucTimeoutInS_showFrameInfoResp  +  (  unsigned  char  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  )  +  3  )  /  2;	
	//
	pCompressVideo->tRecvTime_resp_fromCli  =  pMsgInput->tRecvTime;	//  
	
	iErr  =  0;

errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return  iErr;

}


 int  procTaskAudioDataResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_AUDIO_dataResp  *  pResp,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
{															 
	int					iErr									=		-1;
	char				timeBuf[32]								=		"";
	TCHAR				tHintBuf[255  +  1]						=		_T(  "AudioDataResp:"  );
	//
	time_t				tSelectTime								=		0;
	int					i;
	unsigned  short		usDelay									=		0;

	QY_SHARED_OBJ		*	pSharedObj							=		getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );		//  这里应该用index来获取
	if  (  !pSharedObj  )  return  -1;
	COMPRESS_AUDIO		*	pCompressAudio						=		NULL;

	if  (  pSharedObj->bSoundRecorder  )  pCompressAudio  =  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio;
	else  {
		  CAP_procInfo_audioU  *  pCapProcInfo  =  getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );		
		  if  (  !pCapProcInfo  )  {
			  traceLogA(  "AudioDataResp failed: getCapAudioByIndex( %d ) return NULL.",  pSharedObj->iIndex_capAudio  );
			  return  -1;
		  }
		  pCompressAudio  =  &pCapProcInfo->common.compressAudio;
	}
	if  (  !pCompressAudio  )  return  -1;

	//
	tSelectTime  =  pCompressAudio->tSelectTime;

	//  showDebugInfo(  pProcInfo,  _T(  "AudioResp"  ),  pMsgInput  );

	if  (  pTask->resp.audio.tSelectTime  !=  tSelectTime  )  {
		memset(  &pTask->resp.audio,  0,  sizeof(  pTask->resp.audio  )  );
		//
		pTask->resp.audio.tSelectTime  =  tSelectTime;
	}

	getTimelStr(  pMsgInput->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );

	//	
	if  (  pMsgInput->tRecvTime  <  pMsgInput->tStartTime  )  {
		qyShowInfo(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudioDataResp: recvTime < startTime [%s], skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;
	}
	if  (  pMsgInput->tStartTime  <  tSelectTime  )  {
		pProcInfo->av.localAv.recordSoundProcInfo.usTimes_failure  ++  ;
		qyShowInfo(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudioDataResp: startTime [%s] < selectTime, skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;		
	}
	
	_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "AudioDataResp: %I64u, time-consuming %ds, usCnt_pkts %d"  ),  pMsgInput->data.route.idInfo_from.ui64Id,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime,  pResp->usCnt_pkts  );
	//  traceLogA(  (  "Audio: tn %d, time-consuming %ds, usCnt_pkts %d"  ),  pResp->uiTranNo_openAvDev,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime,  pResp->usCnt_pkts  );


	if  (  !isRcOk(  pMsgInput->usCode  )  )  {
			  pProcInfo->av.localAv.recordSoundProcInfo.usTimes_failure  ++  ;
			  qyShowInfo(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioDataResp: rc %d not ok, startTime [%s], error"  ),  pMsgInput->usCode,  CQyString(  timeBuf  )  );
			}
	else  {
	
		  usDelay  =  (  unsigned  short  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  );

		  //  video里用帧速。这里除了收到的时间差，没有其他可以来分析了。看来还需要增加一个时间差评估参数。
		  //  可以建一个最多10个messenger的响应评估数组。每个messenger的时间差记录下来。比较时间差是否增长。要是变长（》1秒）就表明ucTimes_failure  ++
		  //  对video同样可做
		  //  struct  {
		  //		struct  {
		  //				QY_MESSENGER_ID		idInfo;
		  //				unsigned  short		usTimeDiff;		//  usTimeDiff  =  pMsgInput->tRecvTime  -  pMsgInput->tStartTime
		  //		}		mems[10];
		  //	}
		  //

		  for  (  i  =  0;  i  <  pTask->resp.audio.usCnt_to;  i  ++  )  {
			   if  (  pTask->resp.audio.mems_to[i].idInfo.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id  )  break;
		  }
		  if  (  i  ==  pTask->resp.audio.usCnt_to  )  {

			  //  没找到则找个空位置
			  for  (  ;  i  <  mycountof(  pTask->resp.audio.mems_to  );  i  ++  )  {
				   if  (  !pTask->resp.audio.mems_to[i].idInfo.ui64Id  )  break;
			  }
			  if  (  i  ==  mycountof(  pTask->resp.audio.mems_to  )  )  {
				  OutputDebugString(  _T(  "AudioDataResp: mems_to[] is full. skipped.\n"  )  );  
				  iErr  =  0;  goto  errLabel;
			  }
			  pTask->resp.audio.mems_to[i].idInfo.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;
		
			  pTask->resp.audio.usCnt_to  ++  ;
		
		  }

		  if  (  usDelay  !=  pTask->resp.audio.mems_to[i].usDelay  )  {
			  if  (  pTask->resp.audio.mems_to[i].usDelay  
				  &&  usDelay  >  pTask->resp.audio.mems_to[i].usDelay  +  1  )  
			  {
				  pProcInfo->av.localAv.recordSoundProcInfo.usTimes_failure  ++  ;

				  qyShowInfo(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioDataResp: time-consuming [%d] increases, error"  ),  usDelay  );
			  }
		
			  pTask->resp.audio.mems_to[i].usDelay  =  usDelay;
		  }
	}

	pCompressAudio->ucTimeoutInS_showFrameInfoResp  =  (  pCompressAudio->ucTimeoutInS_showFrameInfoResp  +  (  unsigned  char  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  )  +  3  )  /  2;	
	//
	pCompressAudio->tRecvTime_resp_fromCli  =  pMsgInput->tRecvTime;
	
	iErr  =  0;
errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return  iErr;

}




/*
 int  procTaskAvResp_orgReqMissed(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  IM_SIMPLE_RESP  *  pResp,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
{															 
	int					iErr									=		-1;
	char				timeBuf[32]								=		"";
	TCHAR				tHintBuf[255  +  1]						=		_T(  "TaskAvResp_orgReqMissed:"  );
	//
	time_t				tSelectTime								=		0;
	int					i;
	unsigned  short		usDelay									=		0;

	QY_SHARED_OBJ		*	pSharedObj							=		getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );		//  这里应该用index来获取
	if  (  !pSharedObj  )  return  -1;
	
	//  pTask->hWnd_task


	iErr  =  0;
errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return   iErr;

 }
*/


 int  procTaskGpsDataResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_GPS_dataResp  *  pResp,  void  *  pTranInfo,  PROC_TASK_GPS  *  pTask  )
{															 
	int					iErr									=		-1;
	char				timeBuf[32]								=		"";
	TCHAR				tHintBuf[255  +  1]						=		_T(  "AudioDataResp:"  );
	//
	time_t				tSelectTime								=		0;
	int					i;
	unsigned  short		usDelay									=		0;

	QY_SHARED_OBJ		*	pSharedObj							=		getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );		//  这里应该用index来获取
	if  (  !pSharedObj  )  return  -1;


	getTimelStr(  pMsgInput->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );

	//	
	if  (  pMsgInput->tRecvTime  <  pMsgInput->tStartTime  )  {
		qyShowInfo(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudioDataResp: recvTime < startTime [%s], skipped"  ),  CQyString(  timeBuf  )  );
		iErr  =  0;  goto  errLabel;
	}
	
	_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "gpsDataResp: %I64u, time-consuming %ds"  ),  pMsgInput->data.route.idInfo_from.ui64Id,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  );
	//  traceLogA(  (  "Audio: tn %d, time-consuming %ds, usCnt_pkts %d"  ),  pResp->uiTranNo_openAvDev,  pMsgInput->tRecvTime  -  pMsgInput->tStartTime,  pResp->usCnt_pkts  );


	if  (  !isRcOk(  pMsgInput->usCode  )  )  {
			  qyShowInfo(  CONST_qyShowType_debug,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioDataResp: rc %d not ok, startTime [%s], error"  ),  pMsgInput->usCode,  CQyString(  timeBuf  )  );
			}
	else  {
	
		  usDelay  =  (  unsigned  short  )(  pMsgInput->tRecvTime  -  pMsgInput->tStartTime  );

	}

	//  2009/09/11
	if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
		ROUTE_sendLocalAv	*	pRoute  =  &pSharedObj->curRoute_sendLocalAv;
		if  (  pRoute->route.idInfo_to.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id  )  pSharedObj->routeInfo.tRecvTime_lastResp  =  pMsgInput->tRecvTime;
		else  {
			  for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
				   if  (  !pRoute->route.mems_to[i].idInfo.ui64Id  )  continue;				
				   if  (  pRoute->route.mems_to[i].idInfo.ui64Id  ==  pMsgInput->data.route.idInfo_from.ui64Id  )  {
					   pSharedObj->routeInfo.mems[i].tRecvTime_lastResp  =  pMsgInput->tRecvTime;
					   break;
				   }
			  }
		}
	}

	
	iErr  =  0;
errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return  iErr;

}
