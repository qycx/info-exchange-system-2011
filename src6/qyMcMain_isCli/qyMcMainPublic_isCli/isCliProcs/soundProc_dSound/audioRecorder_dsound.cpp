
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qyPlaySound_wave.h"
#include	"QyRecordSound_wave.h"
#include	"module_qisCamCap.h"

//
int aec_snd_StartRecording(  int  samplesPerSec,  int  stereo,  int  semaIndex,  LPGUID  lpGuid_recorder  );
int aec_snd_StopRecording(  void );


 //  int  startLocalAudioRecorder(  unsigned  int  uiRecordType,  void  *  pGuid,  LPCTSTR  capDevDesc,  int  iIndex_sharedObj,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bTestLocalAv  )
 int  startLocalAudioRecorder(  unsigned  int  uiRecordType,  void  *  pGuid,  LPCTSTR  capDevDesc,  int  iIndex_sharedObj,  AUDIO_COMPRESSOR_CFG  *  pCompressor  ) 
{
	int						iErr					=		-1;
	QY_MC				*	pQyMc					=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo				=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	DWORD					dwThreadDaemonId		=		0;
	BOOL					bAudioCompressInited	=		FALSE;

	traceLogA(  (  "startLocalAudio enters.\n"  )  );

	if  (  !pCompressor  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "startLocalAudioRecorder failed, pCompressor is null"  )  );
#endif
		return  -1;
	}

	if  (  !pProcInfo->ucb_doInitRecordSound  )  {
		MODULE_camCap	*	pCamCap	=	(  MODULE_camCap  *  )getCusModule(  pQyMc,  CONST_moduleType_camCap  );
		if  (  pCamCap  
			&&  pCamCap->pf_doInitRecordSound
			&&  pCamCap->pf_doExitRecordSound  )
		{
			pCamCap->pf_doInitRecordSound(  );
		}
		pProcInfo->ucb_doInitRecordSound  =  TRUE;
	}

	//
	waitForQThread(  &pProcInfo->av.localAv.recordSoundProcInfo.thread, 0  );
	if  (  bQThreadExists(  pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  {
		traceLogA(  "startLocalAudioRecorder: thread already active. "  );
		goto  errLabel;
	}

	//
	QY_SHARED_OBJ	*	pSharedObj;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObj->bSoundRecorder  =  TRUE;


	//  2013/03/18
	if  (  pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  )  goto  errLabel;
	
	//
	pProcInfo->av.localAv.recordSoundProcInfo.uiType  =  CONST_capType_av;
	pProcInfo->av.localAv.recordSoundProcInfo.iIndex_sharedObj  =  iIndex_sharedObj;
	pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  =  uiRecordType;
	//
	pProcInfo->av.localAv.recordSoundProcInfo.capDevDesc[0]  =  0;
	pProcInfo->av.localAv.recordSoundProcInfo.aec_rendDevDesc[0]  =  0;
	safeTcsnCpy(  capDevDesc,  pProcInfo->av.localAv.recordSoundProcInfo.capDevDesc,  mycountof(  pProcInfo->av.localAv.recordSoundProcInfo.capDevDesc  )  );


	//  2009/05/24
	//  if  (  !pCompressor  )  pCompressor  =  &pProcInfo->cfg.policy.taskAv_pc.avCompressor.audio;

	WAVEFORMATEX  *  pWf_input  =  NULL;
	//  2013/03/18
	switch  (  uiRecordType  )  {
			case  CONST_recordType_directX:
				  TCHAR  *  pDisplayName;
				  pDisplayName  =  (  TCHAR  *  )pGuid;
				  if  (  initAudioCapDev_dx(  NULL,  pDisplayName,  NULL,  pCompressor,  FALSE,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev  )  )  goto  errLabel;
				  pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  =  TRUE;

				  if  (  !bGetCapturePara_audioCapdev(  (  MC_VAR_common  *  )pProcInfo,  pSharedObj->iIndex_capAudio,  sizeof(  MIS_MSGU  ),  pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev,  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org,  NULL  )  )  goto  errLabel;
				  pWf_input  =  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org;
				  break;
			default:
					break;
	}
	if  (  !pWf_input  )  {
		memcpy(  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org,  &pCompressor->wf_decompress_default,  sizeof(  pProcInfo->av.localAv.recordSoundProcInfo.wf_org  )  );
		pWf_input  =  &pProcInfo->av.localAv.recordSoundProcInfo.wf_org;
	}

	//
	if  (  initCompressAudio(  pProcInfo,  pWf_input,  pCompressor,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio  )  )  goto  errLabel;
	bAudioCompressInited  =  TRUE;
	

	//
	switch  (  uiRecordType  )  {
			case  CONST_recordType_dSound:  {	
				  pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_recordSound,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				  if  (  !pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  )  goto  errLabel;
				  //
				  if  (  pGuid  )  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  =  *(  GUID  *  )pGuid;		//  2011/10/24
				  else  memset(  &pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice,  0,  sizeof(  pProcInfo->av.localAv.recordSoundProcInfo.guid_aDevice  )  );
				  //
				  pProcInfo->av.localAv.recordSoundProcInfo.thread.dwThreadId  =  dwThreadDaemonId;
				  if  (  ResumeThread(  pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  )  ==  -1  )  goto  errLabel;
				  }
				  break;
			case  CONST_recordType_aec:		//  2013/05/22

				  if  (  aec_snd_StartRecording(  pCompressor->wf_decompress_default.nSamplesPerSec,  pCompressor->wf_decompress_default.nChannels  >  1,  0,  (  GUID  *  )pGuid  )  )  goto  errLabel;

				  break;
			case  CONST_recordType_waveform:  {

				  if  (  startQThread(  NULL,  0,  new  CQyRecordSound,  &pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  goto  errLabel;
				
				  }
				  break;
			case  CONST_recordType_directX:		//  2013/03/18

				  if  (  startAudioCapDev_dx(  pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev  )  )  goto  errLabel;

				  break;
			case  CONST_recordType_custom:
				  traceLog(  _T(  "Not finished"  )  );
				  goto  errLabel;
				  break;
			default:
					traceLog(  _T(  "unknown uiRecordType %d"  ),  uiRecordType  );
					goto  errLabel;
	}

	//  2013/05/24
#if  0
	if  (  bTestLocalAv  )  {
		startLocalAudioPlayer(  );
	}
#endif

	//  2013/05/24. 在aec的情况下,需要自动启动一个player, 以便recorder能建立对render和capture的关联.
	if  (  uiRecordType  ==  CONST_recordType_aec  )  {
		startLocalAudioPlayer(  );
	}


	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		stopLocalAudioRecorder(  iIndex_sharedObj,  1  );
	}

	traceLogA(  (  "startLocalAudio leaves.\n"  )  );
	
	return  iErr;

}


  int  stopLocalAudioRecorder(  int  index_sharedObj,  int  nTries  )
{
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	traceLog(  _T(  "stopLocalAudioRecorder enters."  )  );

	if  (  !nTries  )  nTries  =  10;

	int  i;
	for  (  i  =  0;  i  <  nTries;  i  ++  )  {
		 if  (  !bQThreadExists(  pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  break;
		
		 pProcInfo->av.localAv.recordSoundProcInfo.thread.bQuit  =  TRUE;
		 if  (  pProcInfo->av.localAv.recordSoundProcInfo.hEvents[0]  )  SetEvent(  pProcInfo->av.localAv.recordSoundProcInfo.hEvents[0]  );
		 if  (  pProcInfo->cfg.policy.audio.uiRecordType  ==  CONST_recordType_waveform  )  PostThreadMessage(  pProcInfo->av.localAv.recordSoundProcInfo.thread.dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_endThread,  0  );

		 waitForQThread(  &pProcInfo->av.localAv.recordSoundProcInfo.thread,  1000  );
	}

	//  2013/03/19
	switch  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  )  {
			case  CONST_recordType_aec:		//  2013/05/22
				  aec_snd_StopRecording(  );
				  break;
			case  CONST_recordType_directX:  
				  exitAudioCapDev_dx(  &pProcInfo->av.localAv.recordSoundProcInfo.u.dx.pAudioCapDev  );
				  pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  =  FALSE;
				  break;
			default:
					break;
	}

	//
	if  (  !bQThreadExists(  pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  {
		exitCompressAudio(  pProcInfo,  &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio  );
	}

	//  2013/05/24
	stopLocalAudioPlayer(  10  );

	//
	traceLog(  _T(  "stopLocalAudioRecorder leaves."  )  );

	return  0;
}


    int  resumeLocalAudioRecorder(  int  iIndex_sharedObj  )
{
	int						iErr					=		-1;
	QY_MC				*	pQyMc					=		QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo				=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	DWORD					dwThreadDaemonId		=		0;
	BOOL					bAudioCompressInited	=		FALSE;

	traceLogA(  (  "resumeLocalAudio enters.\n"  )  );

	QY_SHARED_OBJ		*	pSharedObj				=		getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	if  (  pSharedObj->uiType  ==  CONST_sharedObjType_mediaFile  )  return  -1;
	if  (  pSharedObj->uiType  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "resumeLocalAudioRecorder: not used, sharedObjType %d"  ),  pSharedObj->uiType  );
		#endif
		return  -1;
	}

	if  (  !pProcInfo->av.localAv.recordSoundProcInfo.compressAudio.bCompressInited  )  return  0;

	if  (  !pProcInfo->av.localAv.recordSoundProcInfo.thread.bRunning  )  {
		waitForQThread(  &pProcInfo->av.localAv.recordSoundProcInfo.thread,  0  );
	}
	
	if  (  !bQThreadExists(  pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  {
		//
		switch  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  )  {
				case  CONST_recordType_dSound:
					  pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_recordSound,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
					  if  (  !pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  )  goto  errLabel;
					  pProcInfo->av.localAv.recordSoundProcInfo.thread.dwThreadId  =  dwThreadDaemonId;
					  if  (  ResumeThread(  pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  )  ==  -1  )  goto  errLabel;
					  break;
				case  CONST_recordType_waveform:  {

					  if  (  startQThread(  NULL,  0,  new  CQyRecordSound,  &pProcInfo->av.localAv.recordSoundProcInfo.thread  )  )  goto  errLabel;
					
					  }
					  break;
				case  CONST_recordType_directX:
					  break;
				default:
					    traceLog(  _T(  "resumeLocalAudioRecorder: unknown uiRecordType"  )  );
						break;
		}
	}
	
	//  2013/05/26
#if  0
	switch  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  )  {
			case  CONST_recordType_aec:
				  if  (  pProcInfo->av.localAv.recordSoundProcInfo.bInputErr_aec  )  {					  
					  startLocalAudioPlayer(  );		
				  }
				  break;
			default:
					break;
	}
#endif

	iErr  =  0;

errLabel:

	traceLogA(  (  "resumeLocalAudio leaves.\n"  )  );
	
	return  iErr;

}

