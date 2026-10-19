

#ifndef  __QYVEDIOCAPTURE_H__
#define  __QYVEDIOCAPTURE_H__	//  {

//


//
#define		CONST_videoCompressors_null								0
#define		CONST_videoCompressors_vcm								1	//  "vcm"
#define		CONST_videoCompressors_dmo								2	//  "dmo"
#define		CONST_audioCompressors_acm								3	//  "acm"					//  2009/05/16
#define		CONST_audioCompressors_dmo								4	//  "dmo"					//  2009/05/16
#define		CONST_videoCompressors_custom							5	//  "custom"				//  2010/04/28
#define		CONST_audioCompressors_custom							6	//  "custom"				//  2010/04/28
//
#define		CONST_audioCompressors_ipp								7	//
#define		CONST_videoCompressors_ipp								8	//	"h264"					//  2011/07/30
//
#define		CONST_audioCompressors_mediaSdk							9	//
#define		CONST_videoCompressors_mediaSdk							10	//	"h264"					//  2011/11/25
//
#define		CONST_audioCompressors_cuda								11	//
#define		CONST_videoCompressors_cuda								12	//	"h264"					//  2012/06/17



#define		DEFAULT_fourccStr_vcm									"msvc"							//  2008/06/01
#define		DEFAULT_fourccStr_dmo_video								"WMV3"							//  2009/04/02
//  #define		DEFAULT_fourccStr_dmo_screen						"MSS2"							//  2009/04/02
#define		DEFAULT_fourccStr_dmo_screen							"WMV3"							//  2009/12/31
#define		DEFAULT_fourccStr_ipp									"h264"							//  2011/08/01
#define		DEFAULT_fourccStr_mediaSdk								"h264"							//  2011/11/25
#define		DEFAULT_fourccStr_cuda									"h264"							//  2012/06/17




//  2011/07/31
typedef enum {
		 H264_PROFILE_CAVLC444				=	44,
		 H264_PROFILE_BASELINE				=	66,
		 H264_PROFILE_MAIN					=	77,
		 H264_PROFILE_SCALABLE_BASELINE		=	83,		// ANNEX G
		 H264_PROFILE_SCALABLE_HIGN			=	86,		// ANNEX G
		 H264_PROFILE_EXTENDED				=	88,		
		 H264_PROFILE_HIGH					=	100,	
		 H264_PROFILE_HIGH10				=	110,
		 H264_PROFILE_MULTIVIEW_HIGH		=	118,	// ANNEX H		
		 H264_PROFILE_HIGH422				=	122,	
		 H264_PROFILE_SREREO_HIGH			=	128,	// ANNEX H		
		 H264_PROFILE_HIGH444				=	144,
		 H264_PROFILE_HIGH444_PRED			=	244,

}	 H264_PROFILE_IDC;


//
//
#define		MIN_taskTimeoutInS										15								//  2008/06/21


//  int  openLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  displayName,  unsigned  int  uiCamCapType,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressor,  VIDEO_CONFERENCE_CFG  *pVideoConferenceCfg,  int  iIndex_sharedObj,  CAP_procInfo_video  *  pVc  );
int  openLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  LPCTSTR  displayName,  void  **ppCapStuff,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressor,  VIDEO_CONFERENCE_CFG  *pVideoConferenceCfg,  int  iIndex_sharedObj,  CAP_procInfo_video  *  pVc  );
int  closeLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj,  CAP_procInfo_video  *  pVc  );


int  initCompressVideo(  void  *  pProcInfoParam,  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  short  usCapDriverIndex,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  );
int  exitCompressVideo(  void  *  pProcInfo,  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  );

//
SHARED_OBJ_USR  *  getSharedObjUsr(  QY_SHARED_OBJ  *  pSharedObj,  int  iIndex_usr  );

int  getSharedObjIndex_localAv(  );
int  newSharedObjUsr_localAv(  HWND  hWnd,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  );
int  freeSharedObjUsr_localAv(  int  index,  HWND  hWnd  );
int  setCurSharedObjUsr_localAv(  int  index_sharedObj,  HWND  hWnd  );
int  resetCurSharedObjUsr_localAv(  int  index_sharedObj  );

//
int  newSharedObjIndex(  HWND  hWnd,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  );
int  setCurSharedObjUsr(  int  index_sharedObj,  HWND  hWnd  );


int  freeSharedObjByIndex(  int  index  );
QY_SHARED_OBJ  *  getSharedObjByIndex(  MC_VAR_isCli  *  pProcInfo,  int  index  );
BOOL  bSharedObjActive(  MC_VAR_isCli  *  pProcInfo,  int  index  );
int  tryToFreeSharedObjs(  );
BOOL  bNoSharedObjExists(  );
void  askSharedObjToStop(  MC_VAR_isCli  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj,  HWND  hWnd_notifyEnd  );
void  stopAll_sharedObjs(  );

BOOL  canShareScreen(  );
__declspec(  dllexport  )  BOOL  canShareScreen_dx(  );
BOOL  canRemoteAssist(  );
BOOL  canRemotePtzControl(  );


int  newCapProcInfoBmpIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  );
int  newCapProcInfoAudioIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  );

CAP_procInfo_bmpU  *  getCapBmpBySth(  MC_VAR_isCli  *  pProcInfo,  int  index,  unsigned  int  uiCapType  );
CAP_procInfo_audioU  *  getCapAudioBySth(  MC_VAR_isCli  *  pProcInfo,  int  index,  unsigned  int  uiCapType  );

QY_PLAYER  *  getPlayerByIndex(  MC_VAR_isCli  *  pProcInfo,  int  index  );


int  startCapture(  CAP_procInfo_video  *  pVc  );
int  stopCapture(  CAP_procInfo_video  *  pVc  );

//
#define		CONST_fourcc_YUY2	MAKEFOURCC(  'Y',  'U',  'Y',  '2'  )		//  2010/05/31
#define		CONST_fourcc_YV12	MAKEFOURCC(  'Y',  'V',  '1',  '2'  )		//  2010/07/11
#define		CONST_fourcc_I420	MAKEFOURCC(  'I',  '4',  '2',  '0'  )		//  2010/07/11
#define		CONST_fourcc_HDYC	MAKEFOURCC(  'H',  'D',  'Y',  'C'  )		//  2012/01/03
//
#define		CONST_fourcc_v210	MAKEFOURCC(  'v',  '2',  '1',  '0'  )		//  2012/02/23

char  *  iFourcc2Str(  int  fourcc,  char  *  fourccStr,  unsigned  int  size  );
int  fourccStr2i(  const  char  *  fourccStr  );

//
int  makeBmpInfoHeader_rgb(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  );
int  makeBmpInfoHeader_yuy2(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  );
int  makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  * p  );


//  2011/12/17
#define		M_lineBytes_rgb(  bits,  biWidth  )				(  (  biWidth  )  *  (  bits  )  +  31  )  /  32  *  4;


//  2011/12/05
#define		M_sizeImage(  bits,  biWidth,  biHeight  )		(  (  (  biWidth  )  *  (  bits  )  +  31  )  /  32  *  4  *  (  biHeight  )  )
//  #define		M_rgb24SizeImage(  biWidth,  biHeight  )	  (  (  (  biWidth  )  *  24  +  31  )  /  32  *  4  *  (  biHeight  )  )
#define		M_rgb24SizeImage(  biWidth,  biHeight  )		M_sizeImage(  24,  biWidth,  biHeight  )



//
BITMAPINFO  *  newBitmapInfo(  UINT bits,  unsigned  int  bmWidth,  unsigned  int  bmHeight  );

int  setROUTE_sendLocalAv(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbVideoConferenceStarter,  QY_SHARED_OBJ  *  pSharedObj  );
int  addToMsgrs_sendLocalAv(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbVideoConferenceStarter,  QY_SHARED_OBJ  *  pSharedObj  );
int  removeFromMsgrs_sendLocalAv(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  QY_SHARED_OBJ  *  pSharedObj  );


int  yuy2ToRgb24(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  rgb24ToYuy2(  unsigned  char  *  rgb,  unsigned  char  *  yuy2,  int  width,  int  height  );

int  hdycToRgb24(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );	//  2012/01/03
int  v210ToRgb24(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );	//  2012/02/23


int  i420ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height  );
int  yv12ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  rgb24ToYv12(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );  //  2011/06/24

int  rgb565ToRgb24(  unsigned  char  *  src,  unsigned  char  *  rgb,  int  width,  int  height  );

//  2011/12/05
int  yuy2ToYv12(  char  *  inBuff,  char  *  outBuff,  int  width,  int  height  );

int  initOrg2RgbBuf(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  );
void  exitOrg2RgbBuf(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  );
//
int  org2Rgb(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc,  BYTE  *  pInput,  char  *  pOrg2RgbBuf  );
int  rotateRgb2Pic(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc,  BYTE  *  pInput,  char  *  pPicBuf  );


//  2013/03/10
typedef  struct  __ctx_addTxt_t										{
				 SUBTITLES_cfg										subtitlesCfg;
				 //
				 struct												{
				 
					 HFONT											hFont;
					 //
					 SIZE											size_GetTextExtentPoint32;
					 //
					 //  2011/12/16. 为添加文字的专用img的buf
					 BITMAPINFOHEADER								bih_txt;
					 int											iTxtBufSize;
					 char									*		pTxtBuf;

					 //
					 SUBTITLE_cfg_tickCnts							tickCnts;

				 }													mems[MAX_subtitlesCfg_mems];

				 //
				 TCHAR												subtitle0_defaultTag[128];
				 char												timeBuf[CONST_qyTimeLen  +  1];


}		 CTX_addTxt;

int  setPktInputInfo(  void  *  pCAP_procInfo_bmpCommon,  void  *  pmyDRAW_VIDEO_DATA  );
void  CTX_addTxt_free(  void  *  pCTX_addTxt  );

//
int  addTxtToPic(  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  LPCTSTR  videoHint,  DWORD  dwTickCnt_start,  QY_SHARED_OBJ  *  pSharedObj,  COMPRESS_VIDEO  *  pCompressVideo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf  );
int  addTxtToPic_screen(  void  *  pCTX_addTxt,  unsigned  char  ucbDaemonDemo,  int  iW_pic,  int  iH_pic,  HDC  hMemDC  );

//
int  postToDraw(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  unsigned  short  usIndex,  BITMAPINFO  *  pBmpInfo_input,  myDRAW_VIDEO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiEventId_lastRecvd,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  HWND  hWnd_task,  int  index_player  );

int  tmpGetMaxAudioPlayCfg(  AUDIO_PLAY_CFG  *  pSrc0,  AUDIO_PLAY_CFG  *  pSrc1,  AUDIO_PLAY_CFG  *  pDst  );

//  int  chkFromPlayerIndex_v(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  unsigned  short  usIndex,  BITMAPINFO  *  pBmpInfo_input,  int  iSampleTimeInMs,  int  iSampleTimeInMs_org,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiEventId_lastRecvd,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  TASK_AV_FROM  *  pFrom,  PROC_TASK_AV  *  pTask  );
int  chkFromPlayerIndex_v(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  unsigned  short  usIndex,  BITMAPINFO  *  pBmpInfo_input,  int  iSampleTimeInMs,  int  iSampleTimeInMs_org,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiEventId_lastRecvd,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  QY_TRANSFORM  *  pTransform,  PROC_TASK_AV  *  pTask  );
//  int  drawVideoData(  MC_VAR_isCli  *  pProcInfo,  int  iSampleTimeInMs,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  );
int  drawVideoData(  MC_VAR_isCli  *  pProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  int  iIndex_player  );
//
int  drawLocalVideoData(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA	*	pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  MIS_CNT  *  pMisCnt  =  NULL,  QY_MESSENGER_ID  *  pIdInfo_peer  =  NULL  );


DWORD WINAPI mcThreadProc_toShareAudio( LPVOID lpParameter );
DWORD WINAPI mcThreadProc_toShareBmp( LPVOID lpParameter );
//  
//  int  toShareBmp(  MC_VAR_isCli  *	pProcInfo1,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  BITMAPINFO  *  pBmpInfo_input,  myDRAW_VIDEO_DATA  *  pPkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  =  NULL  );
int  toShareBmp(  void  *	pProcInfoParam,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pPkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );

//
DWORD WINAPI mcThreadProc_vpp( LPVOID lpParameter );
DWORD WINAPI mcThreadProc_encVideo( LPVOID lpParameter );
DWORD WINAPI mcThreadProc_toShareVideo_post( LPVOID lpParameter );


//
int  notifyCapEnd(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  HWND  hWnd  );


//  BOOL  bRobotTaskExists(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_applyForChkChannels_qmc  *  pMsg  );
BOOL  bMediaTaskExists(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId  );

int  qisApplyForChkingTasks_gui(  );	//  2009/09/10
int  qisChkTasks_gui(  );			//  2009/09/10
int  qisApplyForChkingTasks(  unsigned  int  uiChannelType  );	//  2009/09/10
int  qisChkTasks(  unsigned  int  uiChannelType  );			//  2009/09/10

int  startQThreadToShareAv(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj,  BOOL  bAudio  );	//  2011/07/29


int  startTransformThreads(  unsigned  int  uiTaskType,  PROC_TASK_AV  *  pTask  );
int  stopTransformThreads(  PROC_TASK_AV  *  pTask  );

int  procTaskAvReply(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  AV_TRAN_INFO  *  pAvTran,  PROC_TASK_AV  *  pTask  );

int  procTaskVideoDataResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_VIDEO_dataResp  *  pTransferVideoDataResp,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  );

int  mySendAvResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  MIS_MSGU  *  pMsgBuf  );


//  int  chkFromPlayerIndex_a(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  int  iTaskId,  PROC_TASK_AV  *  pTask,  WAVEFORMATEX  *  pWf,  myPLAY_AUDIO_DATA  *  p,  TASK_AV_FROM  *  pFrom  );
int  chkFromPlayerIndex_a(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  int  iTaskId,  PROC_TASK_AV  *  pTask,  WAVEFORMATEX  *  pWf,  myPLAY_AUDIO_DATA  *  p,  QY_TRANSFORM  *  pTransform  );
int  playAudioData(  MC_VAR_isCli  *  pProcInfo,  int  iSampleTimeInMs,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  );
//
int  playLocalAudioData(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId,  unsigned  int  uiTranNo,  WAVEFORMATEX  *  pWf,  myPLAY_AUDIO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capAudio  );

int  procTaskAudioDataResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_AUDIO_dataResp  *  pTransferAudioDataResp,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  );

int  procTaskRemoteAssist(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  REMOTE_ASSIST_REQ  *  pRemoteAssistReq,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  int  index_mems_from  );


//  int  viewMediaControl_qmCmd(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  );
//  int  viewMediaControl(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  );

//  int  closeInstantAssistant(  HWND  hDlgTalk  );
//  int  viewInstantAssistant(  HWND  hParent,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgTalk,  BOOL  bNoDelayToView  );
//  int  viewInstantAssistant(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgTalk,  BOOL  bNoDelayToView  );
int  getIDD_instantAssistant(  HWND  hDlgTalk,  int  *  piStatus_instantAssistant,  BOOL  *  pbMin  );

int  sizeAllControls_dlgInstantAssistant(  HWND  hDlgIa  );

#define		CONST_iaStatus_null					0
#define		CONST_iaStatus_start				1
#define		CONST_iaStatus_start_wait			2
#if  0		//  2013/04/06
	#define		CONST_iaStatus_resource				3
	#define		CONST_iaStatus_resource_wait		4
#endif
#define		CONST_iaStatus_av					5

void  *  getMoniker_v(  void  *  pCapParam,  int  iMenuId  );
int  getMonikerProp(  void  *  pMonikerParam,  LPCTSTR  propName,  TCHAR  *  propVal,  int  propValCnt  ); 

#endif  //  }



