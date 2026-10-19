

#ifndef  __funcsForIsCliHelp_h__
#define  __funcsForIsCliHelp_h__	//  {


typedef  int  (  *PF_addTxtToPic_screen  )(  void  *  pCtx,  unsigned  char  ucbDaemonDemo,  int  iW_pic,  int  iH_pic,  HDC  hMemDC  );
typedef  int  (  *PF_setPktInputInfo  )(  void  *  pCAP_procInfo_bmpCommon,  void  *  pmyDRAW_VIDEO_DATA  );
typedef  void  (  *PF_CTX_addTxt_free  )(  void  *  pCTX_addTxt  );


typedef  int  (  *PF_askToRefreshLayout_mgr  )(  HWND  hDlgTalk  );
typedef  BOOL  (  *PF_bMainWndAbove  )(  HWND  hWnd  );
typedef  BOOL  (  *PF_bMessengerOnline  )(  QY_MC  *  pQyMc  );
typedef  BOOL  (  *PF_bQisExportVWall  )(  void  *  pCQyVWall,  void  *  pQY_IMEXPORTINFO  );
typedef  BOOL  (  *PF_bQisImportVWall  )(  void  *  pQY_IMEXPORTINFO,  void  *  pCQyVWall  );
typedef  BOOL  (  *PF_bQnmExportCurQuery  )(  QY_IMEXPORTINFO  *  pExportInfo  );
typedef  BOOL  (  *PF_bWebcamUsing  )(  MC_VAR_isCli  *  pProcInfo,  void  *  pMoniker_v,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  );
typedef  BOOL  (  *PF_bRecorderUsing  )(  MC_VAR_isCli  *  pProcInfo,  void  *  pMoniker_a,  int  *  piIndex_capAudio,  int  *  piIndex_sharedObj  );
typedef  BOOL  (  *PF_bViewImTaskListFunc  )(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart,  BOOL  bHisTab  );

typedef  BOOL  (  *PF_canRemotePtzControl  )(  );
typedef  BOOL  (  *PF_canShareScreen_dx  )(  );
typedef  void  (  *PF_CAP_STUFF_free  )(  void  *  p  );
typedef  void  *  (  *PF_CAP_STUFF_new  )(  );

typedef  int   (  *  PF_getChosenDevice  )(  TCHAR  *  recorder_selected,  unsigned  int  uiCnt_recorder_selected,  TCHAR  *  webcam_selected,  unsigned  int  uiCnt_webcam_selected,
						void  *  pCapParam,  BOOL  bIncludeAudio,  int  *  piMenuId_selectedAudio,  int  *  piMenuId_selectedVideo  );

typedef  void  (  *PF_myChooseDevices  )(  void  *  p_gcap,void  *  pIMoniker_v, void  *  pIMoniker_a  );
typedef  void  (  *PF_chooseAvDevice_mgr  )(  void  *  pCapParam,  HWND  hDlgTalk,  HWND  hWndStatus,  int  iMenuId  );
typedef  int   (  *PF_cfgCaptureFilter  )(  void  *  pAvCapStuff,  HWND  hwndParent  );
typedef  int   (  *PF_cfgCapturePin  )(  void  *  pAvCapStuff,  HWND  hwndParent  );
typedef  int  (  *PF_cfgCrossBar  )(  void  *  pAvCapStuff,  HWND  hwndParent  );
typedef  int  (  *PF_chkTalkerRules  )(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );
typedef  int  (  *PF_chkToViewDynBmp  )(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  unsigned  int  uiObjType,  unsigned  short  usIndex_dynBmp,  int  talkerRuleIndex,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted  );

typedef  int  (  *PF_delImObj  )(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );

typedef  int  (  *PF_displayNotification_talk_ts  )(  HWND  hDlg,  void  *  pGuiDataParam,  LPCTSTR  hint  );
typedef  int  (  *PF_dlgDynBmps_getZoneParam  )(  HWND  hDlgDynBmps,  MIS_MSG_procVideo_qmc  *  pMsg,  ZONE_PARAM  *  pParam  );
typedef   BOOL (  *PF_bDlgTalkAbove  )(  HWND hWnd  );
typedef  int  (  *PF_dlgTalk_cancelTasks  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  iTaskId  );
typedef  int  (  *PF_dlgTalk_OnDestroy  )(  HWND  hDlg,  void  *  pDLG_TALK_var  );
typedef  int  (  *PF_dlgTalk_OnInitDialog  )(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );
typedef  int  (  *PF_dlgTalk_OnQyComm  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  );
typedef  int  (  *PF_dlgTalk_OnQyPostComm  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  );
typedef  int  (  *PF_dlgTalk_qPostMsg  )(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  );
typedef  int  (  *PF_dlgTalk_requestToSpeak  )(  HWND  hDlgTalk,  BOOL  bEnable  );
typedef  int  (  *PF_dlgTalk_procTask1  )(  HWND  hCurDlgTalk,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf  );
typedef  int  (  *PF_dlgTalk_procTask_htmlEdit  )(  HWND  hDlgTalk,  LPCTSTR  url  );
typedef  int  (  *PF_tmpHandler_chkVWallRule_dlgDynBmps  )(  void  *  p0,  void  *  p1,  void  *  p2  );
typedef  int  (  *PF_dlgVideos_procVideo  )(  HWND  m_hWnd,  void  *  pDLG_desktopsMon_var,  void  *  pDlgVideosVar,  MIS_MSG_procVideo_qmc  *	pMsg    );
typedef  int  (  *PF_doCmd_startAvCall  )(  HWND  hDlg,  int  level,  void  *  pDLG_TALK_var  );
typedef  int  (  *PF_doCmd_startShareMediaDevice  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  level,  void  **  ppCapStuff  );
typedef  int  (  *PF_doCmd_startShareMediaFile  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  level,  LPCTSTR  pathCStr  );

typedef  int  (  *PF_enumDmoIoTypes  )(  const  GUID  *  clsid,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  BOOL  *  pbInputSupported,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  BOOL  *  pbOutputSupported,  HWND  hComboBox  );
typedef  int  (  *PF_enumDmos  )(  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  HWND  hComboBox  );

typedef  int  (  *PF_exitShareMediaFile  )(  void  **  ppShareMediaFileParam  );

typedef  int  (  *PF_fillQyMcQuery  )(  QY_OBJ_DB  *  pObjDb,  int  type,  void  *  pParam,  LPCTSTR  wherePart,  QY_MC_QUERY  *  pQuery  );
typedef  int  (  *PF_findQMemByKey  )(  void  *  p0,  void  *  pQParam,  void  *  pKeyInfo,  QM_OBJQ_MEM  *  pMemParam  );
typedef  int  (  *PF_findTalker  )(  void  *  pQyMcParam,  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  HWND  *  phWnd  );
typedef  MIS_MSG_TASK  *  (  *PF_findTaskInProcessQ  )(  void  *  pDLG_TALK_var,  int  iTaskId,  BOOL  bNextAv,  BOOL  bToShareScreen  );

typedef  CUS_MODULE_U  *  (  *PF_getCusModule  )(  void  *  pQyMcParam,  unsigned  int  uiModuleType,  unsigned  int  uiVDevId,  unsigned  int  uiDevType,  WCHAR  *  wDevIdStr  );

typedef  void  *  (  *PF_getDlgWallsVar  )(  HWND  hDlgWalls,  int  iWndContentType  );

typedef	 int  (  *PF_getDmoInfoBySth  )(  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  LPCTSTR  dmoName,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  GUID  *  pDmoClsid,  void  *  pCompressor  );

typedef  QY_OBJ_DB  *  (  *PF_getProcedObjDb  )(  void  *  p0,  int  iDsnIndex  );
typedef  G_guiData_qyMc  *  (  *PF_get_g_guiData  )(  );

typedef MIS_CNT  *  (  *PF_getMisCntByName  )(  void  *  pQyMcParam,  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  misServName  );

//
typedef  void  (  *PF_addDevicesToMenu  )(  void  *  pCapParam,  BOOL  bIncludeAudio,  HWND  hWnd  );

typedef  int  (  *PF_getMenuStatus  )(  void  *  p0,  void  *  p1,  void  *  piStatusParam  );
typedef  void  *  (  *PF_getMoniker_a  )(  void  *  pCapParam,  int  iMenuId  );
typedef  void  *  (  *PF_getMoniker_v  )(  void  *  pCapParam,  int  iMenuId  );
typedef  int  (  *PF_getMonikerProp  )(  void  *  pMonikerParam,  LPCTSTR  propName,  TCHAR  *  propVal,  int  propValCnt  );
typedef  int  (  *PF_getMonikerDisplayName  )(  void  *  pMonikerParam,  TCHAR  *  displayName,  int  displayNameCnt  );

typedef  int  (  *PF_getADevFriendlyName  )(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId,  TCHAR  *  name,  int  cnt  );
typedef  void  *  (  *PF_getADeviceGuid  )(  void  *  pCapParam,  int  iMenuId,  TCHAR  *  devDesc,  int  devDescCnt  );


typedef  int  (  *PF_getRect_talkers  )(  HWND  hDlgWalls,  RECT  *  pRc  );

typedef  int  (  *PF_getShareMediaFileState  )(  void  *  pShareMediaFileParam  );

typedef	 int  (  *PF_getTalkerDesc  )(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  TCHAR  *  talkerDesc,  unsigned  int  talkerDescCnt,  TCHAR  *  shortName,  unsigned  int  shortNameCnt  );

typedef  int  (  *PF_imObjRulesReq2ImRules  )(  REFRESH_imObjRules_req  *  pReq,  QY_im_rules  *  pRules  );
typedef  int  (  *PF_imObjRulesReq2Rules  )(  REFRESH_imObjRules_req  *  pReq,  QY_MESSENGER_ID  *  pIdInfo_related,  QY_imObj_rules  *  pRules  );

typedef  int  (  *PF_initShareMediaFile  )(  LPCTSTR  tFile,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaFileParam  );

typedef  int  (  *PF_netMc_procTreeEvent  )(  void  *  pQyMcParam,  void  *  pSel,  void  *  pEventInfoParam  );

typedef  IM_TASK_RCD  *  (  *PF_msg2TaskRcd  )(  void  *  pMisCntParam,  MIS_MSG_TASK  *  pMsg,  unsigned  short  usRespCode,  IM_TASK_RCD  *  pRcd  );

typedef  int  (  *PF_pauseShareMediaFile  )(  void  *  pShareMediaFileParam  );

typedef  int  (  *PF_postMsg2Mgr_mc  )(  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  );
typedef  int  (  *PF_postMsgTask2Mgr_mc  )(  MIS_CNT  *  pMisCnt,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  );


//  typedef  int  (  *PF_requestToSpeak_videoConferenceOthers  )(  HWND  hDlgTalk,  BOOL  bRequestToSpeak  );
typedef  int  (  *PF_requestToSpeak_videoConferenceStarter  )(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  BOOL  bRequestToSpeak  );
typedef  int  (  *PF_runShareMediaFile  )(  void  *  pShareMediaFileParam  );


typedef  int  (  *PF_saveChosenDevice  )(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId  );
typedef  int  (  *PF_sendVideoConferenceLayout  )(  unsigned  short  usLayoutType,  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo_to  );
typedef  int  (  *PF_sendVideoConferenceStatus  )(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo_to  );
typedef  int  (  *PF_setCurSharedObjUsr_localAv  )(  int  index_sharedObj,  HWND  hWnd  );
typedef  int  (  *PF_resetCurSharedObjUsr_localAv  )(  int  index_sharedObj  );
typedef   void  (  *PF_setEncodingDefaults_video  )(  unsigned  int  uiCapType,  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  );

//  typedef  int  (  *PF_setModalWnd  )(  HWND  hDlg  );
typedef  int  (  *PF_startProgress  )(  unsigned  int  uiTranNo  );

typedef  void  (  *PF_stopAll_avRecord  )(  );
typedef  int  (  *PF_stopShareMediaFile  )(  void  *  pShareMediaFileParam  );
typedef  int  (  *PF_storeTaskInDb  )(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
typedef  int  (  *PF_toShareBmp  )(  void  *	pProcInfo,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pPkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );
typedef  int  (  *PF_toShareGps  )(  MC_VAR_isCli  *  pProcInfo,  void  *  pComPortEx,  int  iSampleTimeInMs,  void  *  pmyGPS_POSITION,  QY_SHARED_OBJ  *  pSharedObj,  BOOL  *  pbHaveMsgrs_sendLocalAv,  MIS_MSGU  *  pMsgBuf  );

typedef  int  (  *PF_talkerShadow_procGps  )(  void  *  pProcInfoParam,  HWND  hDlgTalk,  BOOL  bForceRefreshPos,  int  index_shadow,  HWND  hDlgDynBmps_param,  void  *  pDlgDynBmpsVar_param,  int  index_wallGpsMgrMem  );
typedef  void  (  *PF_TALKER_shadow_free  )(  BOOL  bMgr,  void  *  pShadowInfo  );
typedef  int  (  *PF_talkToMessenger  )(  unsigned  __int64  ui64Id,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
typedef  int  (  *PF_testLocalAv  )(  HWND  hParent  );
typedef  int  (  *PF_tmpHandler_showMsg  )(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  );
typedef  int  (  *PF_toSelectRegion  )(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  iParam  );
typedef  int  (  *PF_toSelectRegion1  )(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  level,  int  iParam  );
typedef  int  (  *PF_tryToTalkToMessenger  )(  unsigned  __int64  ui64Id,  BOOL  bActivateWnd,  HWND	*	phWnd  );
typedef  int  (  *PF_doSth_afterInitDlgTalk  )(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );

//
typedef  int  (  *PF_tryToTalkToMessenger_wallD3d  )(  void  *  p0,  QY_MESSENGER_ID  *  pIdInfo  );
 

//
typedef  int  (  *PF_updateMeDisplayInfo  )(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  talkerDesc,  LPCTSTR  displayName  );

typedef  int  (  *PF_viewInstantAssistant  )(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgTalk,  BOOL  bNoDelayToView  );
typedef  int  (  *PF_viewWallsBar_ts  )(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  int  iWndContentType_hDlgWalls,  BOOL  bNoDelayToView  );
typedef  BOOL  (  *PF_bFullScreen_walls  )(  HWND  hDlgWalls,  int  iWndContentType  );

typedef void * (  *PF_vw_getCurSp  )(  void  *  pCQyVWall  );

typedef  int  (  *PF_testLocalAv_openLocalVideo  )(  HWND  hWnd_testWebcam,  void  *  pADeviceGuid,  LPCTSTR  capDevDesc,  void  *  pMoniker,  BOOL  *  pbGot_sharedObjIndex_localAv,  int  *  piIndex_sharedObj  );
typedef  int  (  *PF_doCmd_test  )(  int  iMenuId  );

typedef  int  (  *PF_stopLocalAudioPlaying  )(  );
typedef  int  (  *PF_freeSharedObjUsr_localAv  )(  int  index,  HWND  hWnd  );

//
typedef  int  (  *PF_dlgShareDynBmps_refreshShareStatus  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  );
typedef  void	*	(  *PF_dlgShareDynBmps_getShareDynBmpsBySth  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  );
typedef  int  (  *PF_dlgShareDynBmps_refreshShareStatus_gps  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );
typedef  LRESULT  (  *PF_dlgShareDynBmps_OnQyComm  )( HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam );
typedef  LRESULT  (  *PF_dlgShareDynBmps_OnQyPostComm  )( HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam );
typedef  int  (  *PF_dlgShareDynBmps_chkSharedObj  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  iIndex_sharedObj  );
typedef  int  (  *PF_dlgShareDynBmps_toShareWebcam  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  index  );
typedef  int  (  *PF_dlgShareDynBmps_toShareGps  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var);
typedef  int  (  *PF_dlgShareDynBmps_closeTaskAv  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index  );
typedef  int  (  *PF_dlgShareDynBmps_chkShareGps  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );


typedef  struct  {


			PF_addTxtToPic_screen				pf_addTxtToPic_screen;
			PF_setPktInputInfo					pf_setPktInputInfo;
			PF_CTX_addTxt_free					pf_CTX_addTxt_free;

			//
			PF_askToRefreshLayout_mgr			pf_askToRefreshLayout_mgr;
			PF_bFullScreen_walls				pf_bFullScreen_walls;
			PF_bMainWndAbove					pf_bMainWndAbove;
			PF_bMessengerOnline					pf_bMessengerOnline;

			PF_bQisExportVWall					pf_bQisExportVWall;
			PF_bQisImportVWall					pf_bQisImportVWall;

			PF_bQnmExportCurQuery				pf_bQnmExportCurQuery;
			PF_bWebcamUsing						pf_bWebcamUsing;
			PF_bRecorderUsing					pf_bRecorderUsing;

			PF_bViewImTaskListFunc				pf_bViewImTaskListFunc;

			PF_canRemotePtzControl				pf_canRemotePtzControl;
			PF_canShareScreen_dx				pf_canShareScreen_dx;
			PF_CAP_STUFF_free					pf_CAP_STUFF_free;
			PF_CAP_STUFF_new					pf_CAP_STUFF_new;
			PF_getChosenDevice					pf_getChosenDevice;
			PF_myChooseDevices					pf_myChooseDevices;
			PF_chooseAvDevice_mgr				pf_chooseAvDevice_mgr;
			PF_cfgCaptureFilter					pf_cfgCaptureFilter;
			PF_cfgCapturePin					pf_cfgCapturePin;
			PF_cfgCrossBar						pf_cfgCrossBar;
			PF_chkTalkerRules					pf_chkTalkerRules;
			PF_chkToViewDynBmp					pf_chkToViewDynBmp;

			PF_delImObj							pf_delImObj;
			PF_displayNotification_talk_ts		pf_displayNotification_talk_ts;
			PF_dlgDynBmps_getZoneParam			pf_dlgDynBmps_getZoneParam;
			PF_bDlgTalkAbove					pf_bDlgTalkAbove;
			PF_dlgTalk_cancelTasks				pf_dlgTalk_cancelTasks;
			PF_dlgTalk_OnDestroy				pf_dlgTalk_OnDestroy;
			PF_dlgTalk_OnInitDialog				pf_dlgTalk_OnInitDialog;
			PF_dlgTalk_OnQyComm					pf_dlgTalk_OnQyComm;
			PF_dlgTalk_OnQyPostComm				pf_dlgTalk_OnQyPostComm;
			PF_dlgTalk_qPostMsg					pf_dlgTalk_qPostMsg;
			PF_dlgTalk_requestToSpeak			pf_dlgTalk_requestToSpeak;
			PF_dlgTalk_procTask1				pf_dlgTalk_procTask1;
			PF_dlgTalk_procTask_htmlEdit		pf_dlgTalk_procTask_htmlEdit;
			PF_tmpHandler_chkVWallRule_dlgDynBmps	pf_tmpHandler_chkVWallRule_dlgDynBmps;
			PF_dlgVideos_procVideo				pf_dlgVideos_procVideo;
			PF_doCmd_startAvCall				pf_doCmd_startAvCall;
			PF_stopAll_avRecord					pf_stopAll_avRecord;
			PF_doCmd_startShareMediaDevice		pf_doCmd_startShareMediaDevice;
			PF_doCmd_startShareMediaFile		pf_doCmd_startShareMediaFile;

			PF_enumDmoIoTypes					pf_enumDmoIoTypes;
			PF_enumDmos							pf_enumDmos;

			PF_exitShareMediaFile				pf_exitShareMediaFile;

			PF_fillQyMcQuery					pf_fillQyMcQuery;
			PF_findQMemByKey					pf_findQMemByKey;
			PF_findTalker						pf_findTalker;
			PF_findTaskInProcessQ				pf_findTaskInProcessQ;

			PF_getCusModule						pf_getCusModule;

			PF_getDlgWallsVar					pf_getDlgWallsVar;

			PF_getDmoInfoBySth					pf_getDmoInfoBySth;

			PF_get_g_guiData					pf_get_g_guiData;
			PF_getMenuStatus					pf_getMenuStatus;
			PF_getMisCntByName					pf_getMisCntByName;
			struct								{
				PF_addDevicesToMenu				pf_addDevicesToMenu;

				PF_getMoniker_a					pf_getMoniker_a;
				PF_getMoniker_v					pf_getMoniker_v;
				PF_getMonikerDisplayName		pf_getMonikerDisplayName;
				PF_getMonikerProp				pf_getMonikerProp;

				PF_getADevFriendlyName			pf_getADevFriendlyName;
				PF_getADeviceGuid				pf_getADeviceGuid;
			}									moniker;

			PF_getProcedObjDb					pf_getProcedObjDb;

			PF_getRect_talkers					pf_getRect_talkers;

			PF_getShareMediaFileState			pf_getShareMediaFileState;

			PF_getTalkerDesc					pf_getTalkerDesc;

			struct								{
				PF_toShareGps					pf_toShareGps;
			}									gps;

			PF_imObjRulesReq2ImRules			pf_imObjRulesReq2ImRules;
			PF_imObjRulesReq2Rules				pf_imObjRulesReq2Rules;

			PF_initShareMediaFile				pf_initShareMediaFile;

			PF_netMc_procTreeEvent				pf_netMc_procTreeEvent;

			PF_msg2TaskRcd						pf_msg2TaskRcd;

			PF_pauseShareMediaFile				pf_pauseShareMediaFile;
			PF_postMsg2Mgr_mc					pf_postMsg2Mgr_mc;
			PF_postMsgTask2Mgr_mc				pf_postMsgTask2Mgr_mc;

			//  PF_requestToSpeak_videoConferenceOthers	pf_requestToSpeak_videoConferenceOthers;
			PF_requestToSpeak_videoConferenceStarter pf_requestToSpeak_videoConferenceStarter;

			PF_runShareMediaFile				pf_runShareMediaFile;

			PF_saveChosenDevice					pf_saveChosenDevice;
			PF_sendVideoConferenceLayout		pf_sendVideoConferenceLayout;
			PF_sendVideoConferenceStatus		pf_sendVideoConferenceStatus;
			PF_setCurSharedObjUsr_localAv		pf_setCurSharedObjUsr_localAv;
			PF_resetCurSharedObjUsr_localAv		pf_resetCurSharedObjUsr_localAv;
			PF_setEncodingDefaults_video		pf_setEncodingDefaults_video;

			//  PF_setModalWnd						pf_setModalWnd;

			PF_startProgress					pf_startProgress;

			PF_stopShareMediaFile				pf_stopShareMediaFile;
			PF_storeTaskInDb					pf_storeTaskInDb;
			PF_toShareBmp						pf_toShareBmp;

			PF_talkerShadow_procGps				pf_talkerShadow_procGps;
			PF_TALKER_shadow_free				pf_TALKER_shadow_free;
			PF_talkToMessenger					pf_talkToMessenger;
			PF_testLocalAv						pf_testLocalAv;
			PF_tmpHandler_showMsg				pf_tmpHandler_showMsg;
			PF_toSelectRegion					pf_toSelectRegion;
			PF_toSelectRegion1					pf_toSelectRegion1;
			PF_tryToTalkToMessenger				pf_tryToTalkToMessenger;
			PF_doSth_afterInitDlgTalk			pf_doSth_afterInitDlgTalk;

			//
			PF_tryToTalkToMessenger_wallD3d		pf_tryToTalkToMessenger_wallD3d;

			//
			PF_updateMeDisplayInfo				pf_updateMeDisplayInfo;
			//
			PF_viewInstantAssistant				pf_viewInstantAssistant;
			PF_viewWallsBar_ts					pf_viewWallsBar_ts;
			PF_vw_getCurSp						pf_vw_getCurSp;

			//
			PF_testLocalAv_openLocalVideo		pf_testLocalAv_openLocalVideo;
			PF_doCmd_test						pf_doCmd_test;

			//
			PF_stopLocalAudioPlaying			pf_stopLocalAudioPlaying;
			PF_freeSharedObjUsr_localAv			pf_freeSharedObjUsr_localAv;

			//
			struct											{
				PF_dlgShareDynBmps_refreshShareStatus		pf_dlgShareDynBmps_refreshShareStatus;
				PF_dlgShareDynBmps_getShareDynBmpsBySth		pf_dlgShareDynBmps_getShareDynBmpsBySth;
				PF_dlgShareDynBmps_refreshShareStatus_gps	pf_dlgShareDynBmps_refreshShareStatus_gps;
				PF_dlgShareDynBmps_OnQyComm					pf_dlgShareDynBmps_OnQyComm;
				PF_dlgShareDynBmps_OnQyPostComm				pf_dlgShareDynBmps_OnQyPostComm;
				PF_dlgShareDynBmps_chkSharedObj				pf_dlgShareDynBmps_chkSharedObj;
				PF_dlgShareDynBmps_toShareWebcam			pf_dlgShareDynBmps_toShareWebcam;
				PF_dlgShareDynBmps_toShareGps				pf_dlgShareDynBmps_toShareGps;
				PF_dlgShareDynBmps_closeTaskAv				pf_dlgShareDynBmps_closeTaskAv;
				PF_dlgShareDynBmps_chkShareGps				pf_dlgShareDynBmps_chkShareGps;
			}												shareDynBmps;

}		 FUNCS_for_isCliHelp;


//  2013/06/08
void  *  FUNCS_for_isCliHelp_new(  );
void  FUNCS_for_isCliHelp_free(  void  **  ppFuncs  );


#endif  //  }

