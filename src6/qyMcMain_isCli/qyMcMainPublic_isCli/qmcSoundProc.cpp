
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include	<mmreg.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcAcm.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"



#if  0
 //  2010/08/02
 void  fillIn_wfx_mp3(  unsigned  int  cbwfx,  unsigned  int  bitRate,  WAVEFORMATEX  *  pWfx  )
 {
	 MPEGLAYER3WAVEFORMAT  *  pMp3  =  (  MPEGLAYER3WAVEFORMAT  *  )pWfx;

	 pWfx->nAvgBytesPerSec  =  bitRate  /  8;
	 if  (  cbwfx  >=  sizeof(  WAVEFORMATEX  )  )  pWfx->cbSize  =  sizeof(  MPEGLAYER3WAVEFORMAT  )  -  sizeof(  WAVEFORMATEX  );
	 if  (  cbwfx >=  sizeof(  MPEGLAYER3WAVEFORMAT  )  )  {
		 pMp3->wID  =  MPEGLAYER3_ID_MPEG;
		 pMp3->fdwFlags  =  MPEGLAYER3_FLAG_PADDING_OFF;
		 pMp3->nBlockSize  =  bitRate  *  144  /  pWfx->nSamplesPerSec;
		 pMp3->nFramesPerBlock  =  1;
		 pMp3->nCodecDelay  =  0x0571;
	 }

	 return;
 }
#endif

 //



 // int  initCompressVideo(  void  *  pProcInfoParam,  BITMAPINFO  *  pBmpInfo_input,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  short  usCapDriverIndex,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  )
 int  initCompressAudio(  MC_VAR_isCli  *  pProcInfo,  WAVEFORMATEX  *  pWf_input,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  COMPRESS_AUDIO  *  p  )
{
	int							iErr				=	-1;
	//
	QY_MC					*	pQyMc				=	QY_GET_GBUF(  );
	//
	WAVEFORMATEX			*	pWfDst				=	NULL;
	WAVEFORMATEX			*	pWfPcm				=	NULL;

	HACMDRIVERID				hadid				=	NULL;

	MMRESULT					mmr					=	0;
	HACMDRIVER					had					=	NULL;
	HACMSTREAM					hstr1				=	NULL;
	HACMSTREAM					hstr2				=	NULL;


	if  (  !pWf_input  )  return  -1;
	if  (  p->bCompressInited  )  return  0;

	traceLogA(  "initAudioCompress  enters"  );
	
	//  if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncAv  )  )  goto  errLabel;

	//
	p->ucTimeoutInS_showFrameInfoResp	=	MAX_ucTimeoutInS_showFrameInfoResp;
	//  p->uiBytesRecorded_perBlockAlign_expected  =  pWf_input->nSamplesPerSec  /  5;
	//  初始化控制参数
	p->ucTimeoutInS_showFrameInfoResp	=	MAX_ucTimeoutInS_showFrameInfoResp;

	//
	//  makeWaveFormat_pcm(  DEFAULT_audio_nChannels,  DEFAULT_audio_iHertz,  DEFAULT_audio_wBitsPerSample,  &p->waveFormatEx  );
	memcpy(  &p->ah_decompress.wfx,  pWf_input,  sizeof(  p->ah_decompress.wfx  )  );

	//  作一点校验
	if  (  MAX_uiBytesRecorded_perBlockAlign  *  p->ah_decompress.wfx.nBlockAlign  >  CONST_bufSize_transferAudioData  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bufSize_transferAudioData %d too small, should be >= %d"  ),  CONST_bufSize_transferAudioData,  MAX_uiBytesRecorded_perBlockAlign  *  p->ah_decompress.wfx.nBlockAlign  );					
		goto  errLabel;
	}	
	if  (  !p->ah_decompress.wfx.nAvgBytesPerSec  )  goto  errLabel;


	/*
	unsigned  int  uiBytesRecorded_perBlockAlign;	uiBytesRecorded_perBlockAlign  =  pProcInfo->cfg.policy.audio.uiBytesRecorded_perBlockAlign;
	if  (  uiBytesRecorded_perBlockAlign  >=  MIN_uiBytesRecorded_perBlockAlign  &&  uiBytesRecorded_perBlockAlign  <=  MAX_uiBytesRecorded_perBlockAlign  )  {
		p->uiBytesRecorded_perBlockAlign_expected  =  uiBytesRecorded_perBlockAlign;
	}
	*/

	//  
	memcpy(  &p->compressor,  pCompressor,  sizeof(  p->compressor  )  );

#if  0
	p->uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );
#endif
	p->uiTranNo_openAvDev_org  =  getuiNextTranNo(  0,  MAX_sharedObjUsrs,  0  );	//  2010/09/04

	//
	if  (  p->compressor.ucCompressors  ==  CONST_audioCompressors_acm  )  {

#ifndef  __WINCE__

		//
		hadid  =  find_driver(  p->compressor.wf_compress.wFormatTag,  p->compressor.wf_compress.nChannels,  p->compressor.wf_compress.nSamplesPerSec,  p->compressor.wf_compress.wBitsPerSample  );
		if  (  hadid  ==  NULL  )  {
			traceLogA(  "initAudioCompress failed. No driver found."  );
			goto  errLabel;
		}
		traceLogA(  "Driver found ( hadid: %4.4lxh)\n",  hadid  );

		//  找到给定标签的对应的格式	
		pWfDst	=	get_driver_format(  hadid,  p->compressor.wf_compress.wFormatTag,  p->compressor.wf_compress.nChannels,  p->compressor.wf_compress.nSamplesPerSec,  p->compressor.wf_compress.wBitsPerSample  );
		if  (  !pWfDst  )  goto  errLabel;
		traceLogA(  "Driver format:%u bits,  %lu samples ps, %d channels\n ",  pWfDst->wBitsPerSample,  pWfDst->nSamplesPerSec,  pWfDst->nChannels  );

		if  (  pWfDst->cbSize  >  sizeof(  p->ah_compress.bExtraData  )  )  {
			traceLogA(  "initCompressAudio failed: pWfDst->cbSize %d > sizeof(  bExtraData  ) %d",  pWfDst->cbSize,  sizeof(  p->ah_compress.bExtraData  )  );
			goto  errLabel;
		}
		memcpy(  &p->ah_compress.wfx,  pWfDst,  sizeof(  p->ah_compress.wfx  )  +  pWfDst->cbSize  );

		//  找到给定标签对应的驱动
		pWfPcm	=	get_driver_suggestedFormat(  hadid,	pWfDst,  WAVE_FORMAT_PCM,  p->compressor.wf_compress.nChannels,  p->compressor.wf_compress.nSamplesPerSec,  p->compressor.wf_compress.wBitsPerSample  );
		if  (  !pWfPcm	)  goto  errLabel;
		traceLogA(  "PCM  format: %u bits,  %lu samples ps, %d channels\n",  pWfPcm->wBitsPerSample,  pWfPcm->nSamplesPerSec,  pWfPcm->nChannels  );
		
		if  (  pWfPcm->cbSize  >  sizeof(  p->ah_pcm.bExtraData  )  )  {
			traceLogA(  "initCompressAudio failed: pWfPcm->cbSize %d >  sizeof(  bExtraData  ) %d",  pWfPcm->cbSize,  sizeof(  p->ah_pcm.bExtraData  )  );
			goto  errLabel;
		}
		memcpy(  &p->ah_pcm.wfx,  pWfPcm,  sizeof(  p->ah_pcm.wfx  )  +  pWfPcm->cbSize  );

		//  2009/07/14
		try  {
			 mmr	=  acmStreamOpen(  &hstr1,  had,  &p->ah_decompress.wfx,  &p->ah_pcm.wfx,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
			}
#ifndef  __noMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   mmr  =  -1;
		}
#endif
		catch  (  ...  )  {
			   mmr  =  -1;
		}
		if  (  mmr  )  {
			hstr1  =  NULL;  goto  errLabel;
		}			
		try  {
			 mmr	=  acmStreamOpen(  &hstr2,  had,  &p->ah_pcm.wfx,  &p->ah_compress.wfx,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
			}
#ifndef  __noMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   mmr  =  -1;
		}
#endif
		catch  (  ...  )  {
			   mmr  =  -1;
		}
		if  (  mmr  )  {
			hstr2  =  NULL;  goto  errLabel;
		}

		p->u.acm.hadid  =  hadid;
		p->u.acm.hstr1  =  hstr1;	hstr1  =  NULL;
		p->u.acm.hstr2  =  hstr2;	hstr2  =  NULL;

#else

		switch  (  p->compressor.wf_compress.wFormatTag  )  {
				case  WAVE_FORMAT_GSM610:  {
					  GSM610WAVEFORMAT	wfDst;
					  memset(  &wfDst,  0,  sizeof(  wfDst  )  );
					  wfDst.wfx.wFormatTag  =  WAVE_FORMAT_GSM610;
					  wfDst.wfx.nChannels  =  1;
					  wfDst.wfx.nSamplesPerSec  =  8000;
					  wfDst.wfx.nAvgBytesPerSec  =  1625;
					  wfDst.wfx.nBlockAlign  =  65;
					  wfDst.wfx.wBitsPerSample  =  0;
					  wfDst.wfx.cbSize  =  2;
					  wfDst.wSamplesPerBlock  =  320;

					  memcpy(  &p->ah_compress.wfx,  &wfDst,  sizeof(  p->ah_compress.wfx  )  +  wfDst.wfx.cbSize  );			
					  }
					  break;
					#if  0
						case  WAVE_FORMAT_MPEGLAYER3:  {
							  MPEGLAYER3WAVEFORMAT	wfDst;
							  memset(  &wfDst,  0,  sizeof(  wfDst  )  );
							  wfDst.wfx.wFormatTag  =  WAVE_FORMAT_MPEGLAYER3;
							  wfDst.wfx.nChannels  =  1;
							  wfDst.wfx.nSamplesPerSec  =  8000;
							  //  wfDst.wfx.nAvgBytesPerSec  =  ;
							  wfDst.wfx.nBlockAlign  =  1;
							  wfDst.wfx.wBitsPerSample  =  0;
							  //  wfDst.wfx.cbSize  =  ;

							  fillIn_wfx_mp3(  sizeof(  wfDst  ),  192000,  (  WAVEFORMATEX  *  )&wfDst  );  

							  memcpy(  &p->ah_compress.wfx,  &wfDst,  sizeof(  p->ah_compress.wfx  )  +  wfDst.wfx.cbSize  );			

							  }
							  break;				
					#endif
				default:
					   traceLog(  _T(  "initCompressAudio failed: wFormatTag not supported"  )  );
					   goto  errLabel;
		}
		if  (  !p->ah_compress.wfx.wFormatTag  )  {
			traceLog(  _T(  "initCompressAudio failed, ah_compress not filled"  )  );
			goto  errLabel;
		}
			
#endif

		}
	else  if  (  p->compressor.ucCompressors  ==  CONST_audioCompressors_dmo  )  {

			  if  (  initCompressAudio_dmo(  &p->compressor,  &p->ah_decompress,  &p->ah_compress,  &p->u.dmo  )  )  goto  errLabel;

			  }
	else  {
		   CUS_MODULE_U	*	pModule	=	NULL;

		   switch  (  p->compressor.ucCompressors  )  {
				   case  CONST_audioCompressors_ipp:
					     pModule	=	pQyMc->cusModules.pIpp;			
						 break;					
				   case  CONST_audioCompressors_custom:
					     pModule	=	getCusModule(  pProcInfo->pQyMcParam,  CONST_moduleType_compress  );
						 break;
				   default:
						#ifdef  __DEBUG__
								traceLogA(  "initCompressAudio: ucCompressors err: %d",  p->compressor.ucCompressors  );
						#endif
						qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressAudio: ucCompressors err: %d"  ),  p->compressor.ucCompressors  );
						goto  errLabel;
						break;
		   }

		   if  (  !pModule  ||  !pModule->compress.pf_qdcInitCompressAudio  )  goto  errLabel;
		   if  (  pModule->compress.pf_qdcInitCompressAudio(  &p->compressor,  &p->ah_decompress,  &p->ah_compress,  &p->u.custom  )  )  goto  errLabel;

	}
#if  0
	else  if  (  p->compressor.ucCompressors  ==  CONST_audioCompressors_custom  )  {
			  CUS_MODULE_U	*	pModule	=	getCusModule(  pProcInfo->pQyMcParam,  CONST_moduleType_compress  );
			  if  (  !pModule  ||  !pModule->compress.pf_qdcInitCompressAudio  )  goto  errLabel;
			  if  (  pModule->compress.pf_qdcInitCompressAudio(  &p->compressor,  &p->ah_decompress,  &p->ah_compress,  &p->u.custom  )  )  goto  errLabel;
			  }
	else  {
		  traceLogA(  "initCompressAudio failed: unprocessed ucCompressors %d",  p->compressor.ucCompressors  );
		  goto  errLabel;
	}
#endif

	//
	p->pReqCache  =  (  TRANSFER_AUDIO_DATA  *  )malloc(  sizeof(  TRANSFER_AUDIO_DATA  )  );
	if  (  !p->pReqCache  )  goto  errLabel;

	p->bCompressInited  =  TRUE;

	iErr  =  0;

errLabel:

	if  (  hstr1  )  {
		acmStreamClose(  hstr1,  0  );	hstr1	=	NULL;
	}
	if  (  hstr2  )  {
		acmStreamClose(  hstr2,  0  );	hstr2	=	NULL;
	}	

	if  (  pWfDst  )  free(  pWfDst  );
	if  (  pWfPcm  )  free(  pWfPcm  );

	if  (  iErr  )  {
		exitCompressAudio(  pProcInfo,  p  );
	}

	traceLogA(  "initAudioCompress  leaves %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}

 int  exitCompressAudio(  MC_VAR_isCli  *  pProcInfo,  COMPRESS_AUDIO  *  pCompressAudio  )
{
	int		iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	//  CQySyncObj			syncObj;

	traceLogA(  "exitAudioCompress  enters"  );

	//  if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncAv  )  )  goto  errLabel;

	if  (  !pCompressAudio->compressor.ucCompressors  )  ;
	else  if  (  pCompressAudio->compressor.ucCompressors  ==  CONST_audioCompressors_acm  )  {

			  #ifndef  __WINCE__
					   if  (  pCompressAudio->u.acm.hstr1  )  {
						   acmStreamClose(  pCompressAudio->u.acm.hstr1,  0  );	pCompressAudio->u.acm.hstr1	=	NULL;
					   }
					   if  (  pCompressAudio->u.acm.hstr2  )  {
						   acmStreamClose(  pCompressAudio->u.acm.hstr2,  0  );	pCompressAudio->u.acm.hstr2	=	NULL;	
					   }
			  #endif

			  }
	else  if  (  pCompressAudio->compressor.ucCompressors  ==  CONST_audioCompressors_dmo  )  {
			  exitCompressAudio_dmo(  &pCompressAudio->u.dmo  );
			  }
	else  {
		   CUS_MODULE_U	*	pModule  =  NULL;
		   switch  (  pCompressAudio->compressor.ucCompressors  )  {
				   case  CONST_audioCompressors_ipp:
					     pModule  =  pQyMc->cusModules.pIpp;
						 break;
				   case  CONST_audioCompressors_custom:
					     pModule  =  getCusModule(  pProcInfo->pQyMcParam,  CONST_moduleType_compress  );
					     break;
				   default:
				   		  traceLogA(  "exitCompressAudio: ucCompressors err: %d",  pCompressAudio->compressor.ucCompressors  );
						  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitCompressAudio: ucCompressors err: %d"  ),  pCompressAudio->compressor.ucCompressors  );
						  break;
		   }

		   if  (  pModule  &&  pModule->compress.pf_qdcExitCompressAudio  )  {
			   pModule->compress.pf_qdcExitCompressAudio(  &pCompressAudio->u.custom  );
		   }
		  
	}
#if  0
	else  if  (  pCompressAudio->compressor.ucCompressors  ==  CONST_audioCompressors_custom  )  {
		      CUS_MODULE_U	*	pModule  =  getCusModule(  pProcInfo->pQyMcParam,  CONST_moduleType_compress  );
			  if  (  pModule  &&  pModule->compress.pf_qdcExitCompressAudio  )  {
				  pModule->compress.pf_qdcExitCompressAudio(  &pCompressAudio->u.custom  );
			  }
			  }
	else  {
		  traceLogA(  "exitCompressAudio: ucCompressors err: %d",  pCompressAudio->compressor.ucCompressors  );
		  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitCompressAudio: ucCompressors err: %d"  ),  pCompressAudio->compressor.ucCompressors  );
	}
#endif

	if  (  pCompressAudio->pReqCache  )  {	//  2009/02/11
		free(  pCompressAudio->pReqCache  );  pCompressAudio->pReqCache  =  NULL;
	}

	if  (  pCompressAudio->pDstBuf  )  {
		free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
	}
	if  (  pCompressAudio->pPcmBuf  )  {
		free(  pCompressAudio->pPcmBuf  );  pCompressAudio->pPcmBuf  =  NULL;
	}

	//  if  (  p->pWfDst  )  {
	//  	free(  p->pWfDst  );  p->pWfDst  =  NULL;
	//  }
	//  if  (  p->pWfPcm  )  {
	//  	free(  p->pWfPcm  );  p->pWfPcm  =  NULL;
	//  }

	pCompressAudio->bCompressInited  =  FALSE;
	memset(  pCompressAudio,  0,  sizeof(  pCompressAudio[0]  )  );

	iErr  =  0;

//  errLabel:

	traceLogA(  "exitAudioCompress  leaves %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}


 int  toShareAudio(  MC_VAR_isCli  *  pProcInfo1,  CAP_procInfo_audioU  *  pRecordSoundProcInfo1,  int  iSampleTimeInMs,  BYTE	*	pInput,  unsigned  int  dwBytesRecorded,  COMPRESS_AUDIO  *  pCompressAudio,  QY_SHARED_OBJ  *  pSharedObj,  BOOL  *  pbHaveMsgrs_sendLocalAv,  MIS_MSGU  *  pMsgBuf  )
{
	 int						iErr						=	-1;
	 QY_MC				*		pQyMc						=	QY_GET_GBUF(  );
	 //
	 DWORD						dwBytes_input				=	dwBytesRecorded;
	 MACRO_prepareForTran(  );
	 unsigned  char				ucFlg						=	CONST_commFlg_routeTalkData;	//  0;
	 int						lenInBytes					=	0;
	 //
	 unsigned  int				uiChannelType				=	CONST_channelType_realTimeMedia;
	 unsigned  char				ucbNeedShowFrameInfo		=	FALSE;
	 int						i;
	 //  2010/09/04
	 SHARED_OBJ_USR			*	pSharedObjUsr				=	NULL;

	 //
	 if  (  !pSharedObj  )  goto  errLabel;
	 pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	 if  (  !pSharedObjUsr  )  goto  errLabel;

	 
	 if  (  pCompressAudio->tLastTime_sendAudio  !=  tStartTran  )  {		//  表明是一秒的开始
		 pCompressAudio->tLastTime_sendAudio  =  tStartTran;

		 //  定期向客户端下发帧速信息		
		 if  (  (  int  )(  tStartTran  -  pCompressAudio->tLastTime_showFrameInfo  )  >  pProcInfo1->cfg.usNeedShowFrameInfoIntervalInS  )  {
			 //
			 ucbNeedShowFrameInfo  =  TRUE;
		 }
		 #ifdef  __DEBUG__	//  for test
				 //  ucbNeedShowFrameInfo  =  TRUE;						
		 #endif
		
		 //  2008/05/13, 不用调整了，用固定设置值
		 /*
		 unsigned  int  uiBytesRecorded_perBlockAlign;	uiBytesRecorded_perBlockAlign  =  pProcInfo1->cfg.policy.audio.uiBytesRecorded_perBlockAlign;
		 if  (  uiBytesRecorded_perBlockAlign  >=  MIN_uiBytesRecorded_perBlockAlign  &&  uiBytesRecorded_perBlockAlign  <=  MAX_uiBytesRecorded_perBlockAlign  )  {
			 pCompressAudio->uiBytesRecorded_perBlockAlign_expected  =  uiBytesRecorded_perBlockAlign;
		 }
		 */
	 }
		
	 BOOL  bQWarning  =  isQ2Warning(  &pProcInfo1->realTimeMediaQ2,  pProcInfo1->cfg.envVar.usQNodes_warningInterval_rtMediaQ  );
	 if  (  bQWarning  )  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning:  realTimeMediaQ too many nodes. audio data will be lossed"  )  );					
	
	 if  (  !pProcInfo1->av.bRealtimeMediaChannelReady  )  {
		 static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		 //  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRecordSoundProcInfo->iIndex_sharedObj  );
	
		 //
		 if  (  pSharedObj
			 &&  !pSharedObjUsr->ucbNotSendData
				&&  (  pSharedObj->route_sendLocalAv.videoConference_idInfo_to.ui64Id
					  ||  pSharedObj->route_sendLocalAv.route.idInfo_to.ui64Id  )  )
		 {
			 MIS_CNT							*	pMisCnt		=	NULL;
			 MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
			 int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
			 int									i;
			 CQyQ2Help								q2Help;

			 if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
				 for  (  i  =  0;  i  <  mycountof(  pProcInfo1->misCnts  );  i  ++  )  {
					  pMisCnt  =  &pProcInfo1->misCnts[i];				
					  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

					  traceLogA(  "toShareAudio: applyForChkChannels"  );
					  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio: rtMedia Channel not Ready, applyForChkChannels"  )  );

					  //
					  memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
					  msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
					  msg_applyForChkChannels.pMisCnt  =  pMisCnt;
					  //
					  //  qPostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo1->realTimeMediaQ  );
					  q2Help.qPostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo1->realTimeMediaQ2  );
				 }
				 sdwTickCnt_applyForChkChannels  =  dwTickCnt;
			 }
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 
	 //
	 TRANSFER_AUDIO_DATA  *  pReq  =  (  TRANSFER_AUDIO_DATA  *  )pCompressAudio->pReqCache;
	 if  (  pReq  &&  !bQWarning  )  {
		 memset(  pReq,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
		 pReq->uiType  =  CONST_imCommType_transferAudioData;
		 pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;	//  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;					

#if  0	//  2010/09/12
		 pCompressAudio->usCnt_pkts  ++  ;
		 if  (  ucbNeedShowFrameInfo  )  {
			 ucFlg  |=  CONST_commFlg_routeTalkData;
			 if  (  pCompressAudio->tRecvTime_resp_fromCli  >=  pCompressAudio->tFirstTime_showFrameInfo_withoutResp  )  {	//  这是为了超时
				 pCompressAudio->tFirstTime_showFrameInfo_withoutResp  =  tStartTran;							  
			 }
			 pReq->tLastTime_showFrameInfo_020534  =  pCompressAudio->tLastTime_showFrameInfo;								//  设置标记						
			 pReq->usCnt_pkts  =  pCompressAudio->usCnt_pkts;
			 //
			 pCompressAudio->tLastTime_showFrameInfo  =  tStartTran;												
			 pCompressAudio->usCnt_pkts  =  0;
			 //
			 //  qyShowInfo(  CONST_qyShowType_debug,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %d bytes audio data. %s"  ),  uiTranNo,  dwBytesRecorded,  ucbNeedShowFrameInfo  ?  _T(  "含音频取样信息"  )  :  _T(  ""  )  );					
		 }
#endif

		 #ifdef  __DEBUG__
				 if  (  dwBytes_input  >  sizeof(  pReq->buf  )  )  {
					 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sizeof(  audioBuf  ) %d too small, should be >= %d"  ),  sizeof(  pReq->buf  ),  dwBytesRecorded  );					
				 }
		 #endif


		 if  (  pCompressAudio->bCompressInited  )  {
			 if  (  pCompressAudio->compressor.ucCompressors  ==  CONST_audioCompressors_acm  )  {

				 #ifndef  __WINCE__

						 if  (  !pCompressAudio->ah_decompress.wfx.nAvgBytesPerSec  ||  !pCompressAudio->ah_pcm.wfx.nAvgBytesPerSec  ||  !pCompressAudio->ah_compress.wfx.nAvgBytesPerSec  )  goto  errLabel;
						 DWORD	dwPcmBytes		=	(  DWORD  )(  dwBytes_input  *  pCompressAudio->ah_pcm.wfx.nAvgBytesPerSec  *  1.  /  (  pCompressAudio->ah_decompress.wfx.nAvgBytesPerSec  )  );
						 if  (  !pCompressAudio->pPcmBuf  ||  dwPcmBytes  >=  pCompressAudio->dwPcmBufSize  )  {
							 if  (  pCompressAudio->pPcmBuf  )  {
								 free(  pCompressAudio->pPcmBuf  );  pCompressAudio->pPcmBuf  =  NULL;
							 }
							 pCompressAudio->dwPcmBufSize  =  dwPcmBytes  *  3  /  2  +  256;
							 pCompressAudio->pPcmBuf  =  (  char  *  )malloc(  pCompressAudio->dwPcmBufSize  );
							 if  (  !pCompressAudio->pPcmBuf  )  goto  errLabel;
						 }
						 DWORD	dwDstBytes		=	pCompressAudio->ah_compress.wfx.nAvgBytesPerSec  *  dwPcmBytes  /  (  pCompressAudio->ah_pcm.wfx.nAvgBytesPerSec  );
						 if  (  !pCompressAudio->pDstBuf  ||  dwDstBytes  >=  pCompressAudio->dwDstBufSize  )  {
							 if  (  pCompressAudio->pDstBuf  )  {
								 free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
							 }
							 pCompressAudio->dwDstBufSize  =  dwDstBytes  *  3  /  2  +  256;
							 pCompressAudio->pDstBuf  =  (  char  *  )malloc(  pCompressAudio->dwDstBufSize  );
							 if  (  !pCompressAudio->pDstBuf  )  goto  errLabel;
						 }
						 //

						 dwDstBytes  =  pCompressAudio->dwDstBufSize;
						 if  (  convertAudio(  pCompressAudio->u.acm.hstr1,  pCompressAudio->u.acm.hstr2,  &pCompressAudio->ah_decompress.wfx,  (  BYTE  *  )pInput,  dwBytes_input,  &pCompressAudio->ah_pcm.wfx,  (  BYTE  *  )pCompressAudio->pPcmBuf,  pCompressAudio->dwPcmBufSize,  &pCompressAudio->ah_compress.wfx,  (  BYTE  *  )pCompressAudio->pDstBuf,  &dwDstBytes  )  )  {
							 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "convertAudio failed"  )  );					
							 goto  errLabel;
						 }

						 pInput  =  (  BYTE  *  )pCompressAudio->pDstBuf;
						 dwBytes_input  =  dwDstBytes;

				 #endif

				 //
				 pReq->uiLen  =  min(  sizeof(  pReq->buf  ),  dwBytes_input  );
				 memcpy(  pReq->buf,  pInput,  pReq->uiLen  );		 				 
				
				 pReq->mems[0].uiSampleTimeInMs  =  iSampleTimeInMs;
				 pReq->mems[0].uiLen  =  pReq->uiLen;
				 pReq->usCnt  =  1;			  

				}
			 else  if  (  pCompressAudio->compressor.ucCompressors  ==  CONST_audioCompressors_dmo  )  {

					   DWORD	dwDstBytes  =  pCompressAudio->u.dmo.cbOutputBuffer;
					   if  (  !pCompressAudio->pDstBuf  ||  dwDstBytes  >=  pCompressAudio->dwDstBufSize  )  {
						   if  (  pCompressAudio->pDstBuf  )  {
							   free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
						   }
						   pCompressAudio->dwDstBufSize  =  dwDstBytes  *  3  /  2  +  256;
						   pCompressAudio->pDstBuf  =  (  char  *  )malloc(  pCompressAudio->dwDstBufSize  );
						   if  (  !pCompressAudio->pDstBuf  )  goto  errLabel;
					   }

					   dwDstBytes  =  pCompressAudio->dwDstBufSize;
					   if  (  compressAudio_dmo(  &pCompressAudio->u.dmo,  &pCompressAudio->ah_decompress,  pInput,  dwBytes_input,  iSampleTimeInMs  )  )  goto  errLabel;

					   if  (  pSharedObj  &&  pSharedObj->iDiffInMs_tStartAudio  !=  pCompressAudio->u.dmo.iDiffInMs_tStartStream  )  pSharedObj->iDiffInMs_tStartAudio  =  pCompressAudio->u.dmo.iDiffInMs_tStartStream;

					   /*
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {
						    memset(  &pReq->mems[i],  0,  offsetof(  TRANSFER_AUDIO_dataMem,  buf  )  );
							pReq->mems[i].uiLen  =  sizeof(  pReq->mems[i].buf  );
							if  (  getDmoOutputByIndex(  &pCompressAudio->u.dmo,  i,  (  BYTE  *  )pReq->mems[i].buf,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs  )  )  break;
							pReq->usCnt  ++  ;
					   }
					   */
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {		//  2009/05/20
						    if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
								traceLogA(  "toShareAudio: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
								goto  errLabel;
							}
						    pReq->mems[i].uiLen  =  sizeof(  pReq->buf  )  -  pReq->uiLen;
							if  (  getDmoOutputByIndex(  &pCompressAudio->u.dmo,  i,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs,  &pReq->mems[i].ui_rtTimeLen  )  )  break;
							pReq->uiLen  +=  pReq->mems[i].uiLen;
							pReq->usCnt  ++  ;
					   }

					   }
			 else  {
				   CUS_MODULE_U		*	pModule  =  NULL;

				   switch  (  pCompressAudio->compressor.ucCompressors  )  {
						   case  CONST_audioCompressors_ipp:
							     pModule  =  pQyMc->cusModules.pIpp;
							     break;
					       case  CONST_audioCompressors_custom:
							     pModule	=	getCusModule(  pProcInfo1->pQyMcParam,  CONST_moduleType_compress  );
								 break;
						   default:

							      traceLogA(  "toShareAudio failed: unprocessed ucCompressors %d",  pCompressAudio->compressor.ucCompressors  );			   
								  qyShowInfo(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio failed: unprocessed ucCompressors %d"  ),  pCompressAudio->compressor.ucCompressors  );
								  goto  errLabel;				   
								  break;
				   }

				   //
					   if  (  !pModule
						   ||  !pModule->compress.pf_qdcCompressAudio
							||  !pModule->compress.pf_qdcGetOutputByIndex  )  goto  errLabel;

					   DWORD	dwDstBytes  =  pCompressAudio->u.custom.cbOutputBuffer;
					   if  (  !pCompressAudio->pDstBuf  ||  dwDstBytes  >=  pCompressAudio->dwDstBufSize  )  {
						   if  (  pCompressAudio->pDstBuf  )  {
							   free(  pCompressAudio->pDstBuf  );  pCompressAudio->pDstBuf  =  NULL;
						   }
						   pCompressAudio->dwDstBufSize  =  dwDstBytes  *  3  /  2  +  256;
						   pCompressAudio->pDstBuf  =  (  char  *  )malloc(  pCompressAudio->dwDstBufSize  );
						   if  (  !pCompressAudio->pDstBuf  )  goto  errLabel;
					   }

					   dwDstBytes  =  pCompressAudio->dwDstBufSize;
					   if  (  pModule->compress.pf_qdcCompressAudio(  &pCompressAudio->u.custom,  &pCompressAudio->ah_decompress,  pInput,  dwBytes_input,  iSampleTimeInMs  )  )  goto  errLabel;

					   if  (  pSharedObj  &&  pSharedObj->iDiffInMs_tStartAudio  !=  pCompressAudio->u.custom.iDiffInMs_tStartAudio  )  pSharedObj->iDiffInMs_tStartAudio  =  pCompressAudio->u.custom.iDiffInMs_tStartAudio;

					   /*
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {
						    memset(  &pReq->mems[i],  0,  offsetof(  TRANSFER_AUDIO_dataMem,  buf  )  );
							pReq->mems[i].uiLen  =  sizeof(  pReq->mems[i].buf  );
							if  (  getDmoOutputByIndex(  &pCompressAudio->u.dmo,  i,  (  BYTE  *  )pReq->mems[i].buf,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs  )  )  break;
							pReq->usCnt  ++  ;
					   }
					   */
					   for  (  i  =  0;  i  <  mycountof(  pReq->mems  );  i  ++  )  {		//  2009/05/20
						    if  (  sizeof(  pReq->buf  )  <=  pReq->uiLen  )  {
								traceLogA(  "toShareAudio: sizeof(  pReq->buf  ) %d  <=  pReq->len %d",  sizeof(  pReq->buf  ),  pReq->uiLen  );
								goto  errLabel;
							}
						    pReq->mems[i].uiLen  =  sizeof(  pReq->buf  )  -  pReq->uiLen;
							if  (  pModule->compress.pf_qdcGetOutputByIndex(  &pCompressAudio->u.custom,  i,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[i].uiLen,  &pReq->mems[i].uiSampleTimeInMs,  &pReq->mems[i].ui_rtTimeLen  )  )  break;
							pReq->uiLen  +=  pReq->mems[i].uiLen;
							pReq->usCnt  ++  ;
					   }

					   
			 }
#if  0

			 else  {
				   traceLogA(  "toShareAudio failed: unprocessed ucCompressors %d",  pCompressAudio->compressor.ucCompressors  );			   
				   qyShowInfo(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareAudio failed: unprocessed ucCompressors %d"  ),  pCompressAudio->compressor.ucCompressors  );
				   goto  errLabel;				   
			 }		
#endif
	 
		 }

		 //  2010/09/12				  
		 if  (  !pReq->usCnt  )  {	
			 //  traceLog(  _T(  "toShareAudio failed: req.usCnt is 0"  )  );
			 goto  errLabel;
		 }

		 //  2010/09/12
		 pCompressAudio->usCnt_pkts  ++  ;
		 if  (  ucbNeedShowFrameInfo  )  {
			 ucFlg  |=  CONST_commFlg_routeTalkData;
			 if  (  pCompressAudio->tRecvTime_resp_fromCli  >=  pCompressAudio->tFirstTime_showFrameInfo_withoutResp  )  {	//  这是为了超时
				 pCompressAudio->tFirstTime_showFrameInfo_withoutResp  =  tStartTran;							  
			 }
			 pReq->tLastTime_showFrameInfo_020534  =  pCompressAudio->tLastTime_showFrameInfo;								//  设置标记						
			 pReq->usCnt_pkts  =  pCompressAudio->usCnt_pkts;
			 //
			 pCompressAudio->tLastTime_showFrameInfo  =  tStartTran;												
			 pCompressAudio->usCnt_pkts  =  0;
			 //
			 //  qyShowInfo(  CONST_qyShowType_debug,  0,  "",  pProcInfo1->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %d bytes audio data. %s"  ),  uiTranNo,  dwBytesRecorded,  ucbNeedShowFrameInfo  ?  _T(  "含音频取样信息"  )  :  _T(  ""  )  );					
		 }


		 #ifdef  __DEBUG__
				 if  (  pProcInfo1->cfg.debugStatusInfo.ucbPrint_a_out  )  {				
					 traceLogA(  "toShareAudio: tn %d, req.usCnt %d, len %d, mems[0].uiSampleTimeInMs %d, iSampleTimeInMs %d",  uiTranNo,  pReq->usCnt,  pReq->uiLen,  pReq->mems[0].uiSampleTimeInMs,  iSampleTimeInMs  );
					 //  qyShowInfo(  CONST_qyShowType_debug,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "will send tn [%d]"  ),  uiTranNo  );
				 }
		 #endif

		 //  
		 lenInBytes  =  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  +  pReq->uiLen;
		 //			
		 BOOL					bHaveMsgrs_sendLocalAv		=	FALSE;
		 //  QY_SHARED_OBJ		*	pSharedObj					=	NULL;	
		 MIS_CNT			*	pMisCnt						=	NULL;		

		 //  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRecordSoundProcInfo->iIndex_sharedObj  );
		 if  (  pSharedObj  )  {

			 pMisCnt  =  getMisCntByIndex(  0,  pProcInfo1,  pSharedObj->curRoute_sendLocalAv.iIndex_misCnt  );
			 if  (  pMisCnt  &&  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
											   
				 //  这里的将配置换成当前的方式不好，应该将curRoute_sendLocalAv放在m_var里。这样，就用同步可以确保数据一致性了.暂时不改
				 if  (  pSharedObj->curRoute_sendLocalAv.route.uiMsgRouteId  !=  pSharedObj->route_sendLocalAv.route.uiMsgRouteId  )  {			
					 CQySyncObj	syncObj;
					 if  (  !syncObj.sync(  pProcInfo1->cfg.mutexName_syncSendAv,  0  )  )  {
						 memcpy(  &pSharedObj->curRoute_sendLocalAv,  &pSharedObj->route_sendLocalAv,  sizeof(  pSharedObj->curRoute_sendLocalAv  )  );									   
						 #ifdef  __DEBUG__
								 traceLog(  _T(  "toShareAudio: curRoute_sendLocalAv refreshed"  )  );
						 #endif
					 }
				 }							   					
				
				 //							   
				 #ifdef  __DEBUG__
						 //  test为了测试
						 //  if  (  (  uiTranNo  %  30  )  )  break;
				 #endif
				
				 if  (  !pSharedObjUsr->ucbNotSendData  )  {

					 pSharedObj->curRoute_sendLocalAv.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );
					 if  (  ucbNeedShowFrameInfo  )  {	//  2008/05/16									 
						 time_t		tNow;	mytime(  &tNow  );	pSharedObj->curRoute_sendLocalAv.route.debugInfo.tTime_start  =  tNow;
					 }

					 if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {	//  
						 #if  0
							 if  (  postMsg2Mgr_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_task,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
								 traceLogA(  "CQyRecordSound::OnSoundData: postMsg2Mgr_mc to videoConference failed"  );		//  
							 }
						 #else		//  2011/01/30
							 if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
								 traceLogA(  "CQyRecordSound::OnSoundData: postMsg2MgrFunc_mc to videoConference failed"  );		//  
							 }
						 #endif
						 }
					 else  {
						   if  (  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
							   #if  0
									if  (  postMsg2Mgr_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )pReq,  lenInBytes,  0,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
										traceLogA(  "CQyRecordSound::OnSoundData: postMsg2Mgr_mc failed"  );		//  
									}
							   #else	//  2011/01/27
									if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  {
										traceLogA(  "CQyRecordSound::OnSoundData: postMsg2MgrFunc_mc failed"  );		//  
									}
							   #endif
						   }
					 }

				 }
				 #ifdef  __DEBUG__
						 if  (  pSharedObjUsr->ucbNotSendData  )  {					
							 //  traceLogA(  "toShareAudio: not send data"  );
						 }
				 #endif

				 //
				 if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  ||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  bHaveMsgrs_sendLocalAv  =  TRUE;

			 }
		 }

		 //
		 //
		 //

		 if  (  pbHaveMsgrs_sendLocalAv  )  *pbHaveMsgrs_sendLocalAv  =  bHaveMsgrs_sendLocalAv;

	}

	iErr  =  0;
errLabel:
	return  iErr;
}


