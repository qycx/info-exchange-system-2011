
#ifndef  __QYAVRECORDPUBLIC_H__
#define  __QYAVRECORDPUBLIC_H__		//  {

//  #define		IMonRelease(  x  )	MACRO_safeRelease(  x  )


 __declspec(  dllexport  )  int  initAvRecordMgr(  HINSTANCE  g_hInst  );
 __declspec(  dllexport  )  void  exitAvRecordMgr(  );


 BOOL  bDSoundToPlayInited(  );
 int initDSoundToPlay( void  *  pDynLib_dx,  LPCGUID lpcGUID,  HWND  hWnd,  void  *  p2  );
 void  exitDSoundToPlay(  void  *  pDynLib_dx,  void  *  p1,  void  *  p2  );


__declspec(  dllexport  ) int  toSelectRegion(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  iParam  =  -1  );	
__declspec(  dllexport  ) int  toSelectRegion1(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  level,  int  iParam  =  -1  );

 __declspec(  dllexport  )  RECT  getSelectedRect(  );
 //  int  setSelectedRect(  int  biWidth,  int  biHeight  );
 __declspec(  dllexport  )  BOOL  bRemoteAssist_avRecord(  );
 __declspec(  dllexport  )  BOOL  bDirectX_avRecord(  );
 __declspec(  dllexport  )  int  getLevel_avRecord(  );
 __declspec(  dllexport  )  int  getiParam_avRecord(  );


#ifdef  __DEBUG__
		int  getBmpInfo_avRecord(  int  left,  int  top,  int  width,  int  height,  BITMAPINFO  *  pBmpInfo  );
#endif


 int  chkRectSizePos(  );
 __declspec(  dllexport  )  int  startAvRecord(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_screenCapProcInfo,  HWND  hWnd_notifyEnd  );
 __declspec(  dllexport  )  void  exitAvRecord(  void  *  pCOMPRESS_VIDEO  );

 __declspec(  dllexport  )  int  setFps_capScreen(  int  fps  );

__declspec(  dllexport  ) void  stopAll_avRecord(  );

__declspec(  dllexport  )  int  getSize_qyAvRecord(  );


//
void  *  CAP_STUFF_new(  );
void  CAP_STUFF_free(  void  *  pCap  );
void  CAP_STUFF_exit(  void  *  pCap  );

 BOOL  CAP_STUFF_bAudio(  void  *  p  );
 BOOL  CAP_STUFF_bVideo(  void  *  p  );

 //
 void  myChooseDevices(  void  *  p_gcap,void  *  pIMoniker_v, void  *  pIMoniker_a  );

 //
void  *  getADeviceGuid(  void  *  pCapParam,  int  iMenuId,  TCHAR  *  devDesc,  int  devDescCnt  );		//  2011/10/24
void  *  getMoniker_a(  void  *  pCapParam,  int  iMenuId  );


#define		MAX_monikerDisplayNameLen		256

#define		CONST_moniker_DevicePath		_T(  "DevicePath"  )
#define		CONST_moniker_FriendlyName		_T(  "FriendlyName"  )

int  getMonikerDisplayName(  void  *  pMonikerParam,  TCHAR  *  displayName,  int  displayNameCnt  );
int  getMonikerByDisplayName(  LPCTSTR  displayName,  void  **  ppMoniker  );

//  #define  getMonikerDevicePath(  pMonikerParam,  devicePath,  devicePathCnt  )	getMonikerProp(  pMonikerParam,  CONST_moniker_DevicePath,  devicePath,  devicePathCnt  )
#define  getMonikerFriendlyName(  pMonikerParam,  friendlyName,  friendlyNameCnt  )	getMonikerProp(  pMonikerParam,  CONST_moniker_FriendlyName,  friendlyName,  friendlyNameCnt  )

//
int  getADevFriendlyName(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId,  TCHAR  *  name,  int  cnt  );


BOOL  bRecorderUsing(  MC_VAR_isCli  *  pProcInfo,  void  *  pMoniker_a,  int  *  piIndex_capAudio,  int  *  piIndex_sharedObj_a  );
BOOL  bWebcamUsing(  MC_VAR_isCli  *  pProcInfo,  void  *  pMoniker_v,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj_v  );

void  addDevicesToMenu(  void  *  pCap,  BOOL  bIncludeAudio,  HWND  hWnd  );
void  addDevicesToMenu_shadow(  void  *  pCapParam,  BOOL  bIncludeAudio,  HWND  hWnd  );

//  
void  chooseAvDevice(  void  *  pCap,  BOOL  bIncludeAudio,  HWND  hWnd,  HWND  hWndStatus,  int  iMenuId  );
void  chooseAvDevice_shadow(  void  *  pCapParam_mgr,  BOOL  bIncludeAudio,  HWND  hShadow,  HWND  hWndStatus,  int  iMenuId  );


int  saveChosenDevice(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId  );
int  getChosenDevice(  TCHAR  *  recorder_selected,  unsigned  int  uiCnt_recorder_selected,  TCHAR  *  webcam_selected,  unsigned  int  uiCnt_webcam_selected,
						void  *  pCapParam,  BOOL  bIncludeAudio,  int  *  piMenuId_selectedAudio,  int  *  piMenuId_selectedVideo  );

//
HRESULT  BufferCB_av(  void  *  pProcInfoParam,  int  iIndex_capProcInfo,  void  *  pSampleGrabberCbVar,  int  iSampleTimeInMs,  BYTE  *  pBuffer,  long  BufferLen  );

//
int  processInput_post(  void  *  pProcInfoParam,  int  nAvgBytesPerSec,  BYTE  *  pbInput1,  unsigned  int  dwNumBytes,  MIS_MSGU  *  pMsgBuf  );


//  2013/03/19
int  initAudioCapDev_dx(  QM_APP_PARAMS  *  pTask_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppAudioCapDevParam  );
int  exitAudioCapDev_dx(  void  **  ppAudioCapDevParam  );
BOOL  bGetCapturePara_audioCapdev(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pAudioCapDevParam,  WAVEFORMATEX  *  pWf_org,  SAMPLE_grabberCb_cache  *  pCache  );
int  startAudioCapDev_dx(  void  *  pAudioCapDevParam  );
int  stopAudioCapDev_dx(  void  *  pAudioCapDevParam  );


//  
int  initVideoCapDev_dx(  QM_APP_PARAMS  *  pTask_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppVideoCapDevParam  );
int  exitVideoCapDev_dx(  void  **  ppVideoCapDevParam  );
BOOL  bGetCapturePara_dx(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  );
int  startCapture_dx(  void  *  pVideoCapDev  );
int  stopCapture_dx(  void  *  pVideoCapDev  );

BOOL  bAudioOnly(  void  *  pSharedMediaFileParam  );
BOOL  bNoAudio(  void  *  pSharedMediaFileParam  );


//
BOOL  bGetCapturePara_shareMediaObj(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiCapType,  
			int  iIndex_capAudio,  unsigned  int  uiBufSize_pMsgBuf_a,  void  *  pSampleGrabberInfo_a,  WAVEFORMATEX  *  pWf_org,  
			int  iIndex_capBmp,  unsigned  int  uiBufSize_pMsgBuf_v,  void  *  pSampleGrabberInfo_v,  QY_VIDEO_HEADER  *  pVh_org,  
			SAMPLE_grabberCb_cache  *  pCache_unused  );


//
int  initShareMediaFile(  LPCTSTR  tFile,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaFileParam  );
int  exitShareMediaFile(  void  **  ppShareMediaFileParam  );

//
BOOL  bGetCapturePara_shareMediaFile(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaFile,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache  );

int  runShareMediaFile(  void  *  pShareMediaFileParam  );
int  stopShareMediaFile(  void  *  pShareMediaFileParam  );
int  pauseShareMediaFile(  void  *  pShareMediaFileParam  );
int  getShareMediaFileState(  void  *  pShareMediaFileParam  );

//  int  resumeAudio(  void  *  pShareMediaFileParam  );
//  int  muteAudio(  void  *  pShareMediaFileParam  );

//
//  int  initShareMediaDevice(  void  **  ppCapStuff,  WAVEFORMATEX  *  pWf_suggested,  BITMAPINFOHEADER  *  pBih_suggested,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaDeviceParam  );
int  initShareMediaDevice(  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor,  BITMAPINFOHEADER  *  pBih_suggested,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaDeviceParam  );
int  exitShareMediaDevice(  void  **  ppShareMediaDeviceParam  );

BOOL  bGetCapturePara_shareMediaDevice(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaDevice,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache  );

int  runShareMediaDevice(  void  *  pShareMediaDeviceParam  );
int  stopShareMediaDevice(  void  *  pShareMediaDeviceParam  );


//
int  handleGraphEvent_mediaFile(  void  *  pShareMediaFile,  BOOL  bMediaFile,  BOOL  bLooping,  BOOL  bPlayThrough  );
int  handleGraphEvent_mediaDevice(  void  *  pShareMediaDevice  );
int  handleGraphEvent_videoCapDev_dx(  void  *  pVideoCapDevParam  );
int  handleGraphEvent_audioCapDev_dx(  void  *  pAudioDevCapParam  );


//
//  int  fixPlayCfg(  MC_VAR_isCli  *  pProcInfo,  AUDIO_PLAY_CFG  *  pPlayCfg  );
//  BOOL  tmpHandler_bOldAudio(  void  *  p0,  QY_PLAYER  *  pPlayer,  myPLAY_AUDIO_DATA  *  pPkt  );
BOOL  tmpHandler_bOldAudio(  DWORD  dwTickCnt_now,  QY_PLAYER  *  pPlayer,  myPLAY_AUDIO_DATA  *  pPkt  );



extern "C" DWORD WINAPI mcThreadProc_recordSound( LPVOID lpParameter );

extern "C" DWORD WINAPI mcThreadProc_playAudio( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_playVideo( LPVOID lpParameter );

//
extern "C" DWORD WINAPI mcThreadProc_transformAudio( LPVOID lpParameter );


extern "C" DWORD WINAPI mcThreadProc_preTransformVideo( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_decVideo( LPVOID lpParameter );
//  2012/03/25, 单线程解码. 专用于查看远程现场
extern "C" DWORD WINAPI mcThreadProc_transformVideo( LPVOID lpParameter );

extern "C" DWORD WINAPI mcThreadProc_dispatchAudio( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_dispatchVideo( LPVOID lpParameter );




#endif  //  }


