
#ifndef  __isCliHelpPublic_h__
#define  __isCliHelpPublic_h__		//  {


#include	"qyGuiHelpPublic.h"


  __declspec(dllexport)  int   set_g_pQyMc_isCliHelp(  void  *  pQyMc  );
  __declspec(dllexport)  int   set_g_dbPool_isCliHelp(  void  *  pPool,  int  cnt  );
  __declspec(  dllexport  )  BOOL  dll_PreTranslateMessage_isCliHelp(  MSG  *  pMsg  );

  __declspec(dllexport)  int  showDlgProgress(  HWND  hParent,  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo  =  0,  BOOL  canUsrOk  =  FALSE,  PF_commonHandler  pf_doProgress  =  NULL  );
  __declspec(  dllexport  )  int  showDlgImObjRule(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );

  __declspec(  dllexport  )  int  showDlgSubtitleSelect(  HWND  hParent,  void  *  pSUBTITLE_cfg  );
 

  __declspec(  dllexport  )  int  showDlgPtzSettings(  HWND  hParent  );
  __declspec(  dllexport  )  int  getPtzSettings(  void  *  pCOM_PORT_cfg  );


  __declspec(  dllexport  )  SUBTITLES_cfg  *  getCurSubtitlesCfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  );
  __declspec(  dllexport  )  int  deleteSubtitlesCfg(  int  iCapType,  int  iCapSubType  );
   __declspec(  dllexport  )  int  subtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  SUBTITLES_cfg  *  pCur  );
   __declspec(  dllexport  )  int  getSubtitlesCfg(  int  iCapType,  int  iCapSubType,  SUBTITLES_cfg  *  pSubtitlesCfg  );

   __declspec(  dllexport  )  int  viewDlgSubtitles(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  HWND  hParent  );
  __declspec(  dllexport  )  int  viewDlgSubtitles_talk(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  HWND  hParent,  HWND  hCurTalk,  void  *  pCurVarParam,  void  *  pMgrVarParam  );

  __declspec(  dllexport  ) void  exitPtz(  );
  __declspec(  dllexport  )  int doRemotePtzCmd(  char  *  buf,  unsigned  int  iLen  );
  __declspec(  dllexport  ) BOOL  isActive_comPort_ptz(  );
  __declspec(  dllexport  ) int  viewRemotePtzControl(  HWND  hParent,  HWND  hCurTalk,  void  *  pCurVarParam,  void  *  pMgrVarParam  );
  __declspec(  dllexport  ) int  viewLocalPtzControl(  HWND  hParent  );

  __declspec(  dllexport  )  int  showDlgCfgVideoConference(  HWND  pParent  );

  __declspec(  dllexport  )  int  showDlgCfgWmv(  HWND  hParent  );
  
  __declspec(  dllexport  )  int  showDlgVideoCompressors(  HWND  hParent,  AV_COMPRESSOR_CFG  *  pAvCompressor,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_o  );

  __declspec(  dllexport  )  int  showDlgPolicyAv(  HWND  hParent,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bReply  );

  __declspec(  dllexport  )  int  showDlgPolicyIsClient(  HWND  hParent  );
  __declspec(  dllexport  ) int  getPolicyIsClient(  MC_VAR_isCli  *  pProcInfo,  POLICY_isClient  * p   );
  __declspec(  dllexport  ) int  initPolicyAvParams(  );
  __declspec(  dllexport  ) int  myGetAvCompressorCfg(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bReply,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  );
  __declspec(  dllexport  ) int  getVideoConferenceCfg(  HKEY  hKeyRoot0,  LPCTSTR  pRootKey_qnmScheduler,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  VIDEO_CONFERENCE_CFG  *  pCfg  );
  __declspec(  dllexport  ) int  refreshWebCamSettings(  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorCfg,  CAP_procInfo_video  *  pVc  );
  __declspec(  dllexport  ) int  getCamCapType_default(  );
  __declspec(  dllexport  ) int  fixPlayCfg(  MC_VAR_isCli  *  pProcInfo,  AUDIO_PLAY_CFG  *  pPlayCfg  );

  __declspec(  dllexport  )  int  showDlgSelect_isCli(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1,  void  *  pDlgSelect_isCli_o_U  );


   __declspec(  dllexport  )  int  viewWallsBar(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  void  *  pDLG_wall_var,  BOOL  bNoDelayToView  );
   __declspec(  dllexport  )  int  setWallsBarPos(  HWND  hDlgWalls,  void  *  pDLG_wall_var,  HWND  hBar  );

   __declspec(  dllexport  )  int  showDlgMsgList(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );

   __declspec(  dllexport  )  int  showDlgObjs(  HINSTANCE  g_hInst,  HWND  hParent,  void  *  pDLG_guiDataParam_objs  );

   __declspec(  dllexport  )  int  showMenu_wallsBar(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );

   __declspec(  dllexport  )  int  viewMediaControl(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  );
   __declspec(  dllexport  )  int  viewMediaControl_qmCmd(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  );


 __declspec(  dllexport  )  void  *  getDlgDesktopsMonVar(  HWND  hDlgDesktopsMon  );

  __declspec(  dllexport  )  void  *  getDlgVideosVar(  HWND  hDlgVideos  );

 //
 __declspec(  dllexport  )  void  *  getDlgDynBmpsVar(  HWND  hDlgDynBmps  );
 __declspec(  dllexport  )  int  showEnlargedWnd(  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pDLG_VIDEO_PARAMS,  CAP_subWnds  *  pSubWnds  );
 __declspec(  dllexport  ) int  viewDynBmp(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  LPCTSTR  cusName  );
 __declspec(  dllexport  )  int  addToWallGpsMgr(  HWND  hDlgTalk,  int  iIndex_shadow,  void  *  pmyGPS_POSITION,  HWND  hDlgWall  );
  __declspec(  dllexport  )  LRESULT  myGuiSendMessage(  HWND hWnd,  int  iWndContentType,  UINT uMsg,  WPARAM wParam,  LPARAM lParam);
  
  __declspec(  dllexport  ) int  myGetProps_vw(  char  *  buf,  void  *  pQY_props  );

  __declspec(  dllexport  )  void  *  getDlgWallsVar_dynBmps(  HWND  hDlgWalls,  int  iWndContentType  );
  __declspec(  dllexport  )  int  getRect_talkers_default(  HWND  hDlgWalls,  RECT  *  pRc  );
  __declspec(  dllexport  )  BOOL  bFullScreen_walls_default(  HWND  hDlgWalls,  int  iWndContentType  );

  __declspec(  dllexport  )  int  popupNotificationWnd(  );
  __declspec(  dllexport  )  int  addNotification(  MIS_MSG_taskStatus  *  pStatus  );
  __declspec(  dllexport  )  int  removeNotification(  QY_MESSENGER_ID  *  pIdInfo_logicalPeer  );
  __declspec(  dllexport  )  int  clearNotification(  );
  __declspec(  dllexport  )  int  viewVWall(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iWndContentType,  int  iSubType,  BOOL  bNewVirtualWall,  HWND  *  phWnd  );

  __declspec(  dllexport  )  int  showDlgSelectAvDev(  HWND  hParent,  void  *  pCapStuff  );


   __declspec(  dllexport  )  int  dlgTalk_OnQyPostComm_idcInited(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  );
   __declspec(  dllexport  )  int  dlgTalk_OnInitDialog_createHtmlEdits(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );
   __declspec(  dllexport  ) int  dlgTalk_OnQyComm_getDropTarget(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  );
    __declspec(  dllexport  )  int  doDoc_doTable_byRowId_param(  void  *  pDLG_TALK_var,  void  *  pPARAM_PROC_ROW  );

#ifdef  __DEBUG__
 __declspec(  dllexport  )	int  printHtmlEdit(  void  *  pCMyHtmlEditCtrl  );
#endif
 __declspec(  dllexport  )  int  parseQmInternalUrl(  LPCTSTR  url,  int  *  piTaskId,  TCHAR  *  rowIdStr,  unsigned  int  rowIdStrCnt,  unsigned  short  *  pusOp,  TCHAR  *  paramStr,  unsigned  int  paramStrCnt  );

   __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused,  HWND  *  phWnd  );
   __declspec(  dllexport  ) void  *  getDlgTalkVar(  HWND  hDlgTalk  );
   __declspec(  dllexport  )  BOOL  bTaskExists_recvdResource(  void  *  pDLG_TALK_var,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  piW_screen,  int  *  piH_screen  );
   __declspec(  dllexport  )  int  closeInstantAssistant(  HWND  hDlgTalk  );
   __declspec(  dllexport  )  int  sizeAllControls_dlgTalk(  HWND  hDlg,  void  *  pDLG_TALK_var,  RECT  *  pRect  );
   __declspec(  dllexport  )  int  activateRowByRowId(  HWND  hDlg,  void  *  pDLG_TALK_var,  LPCTSTR  rowIdStr  );
   __declspec(  dllexport  )  unsigned  short  dlgTalk_get_usLayoutType_local(  HWND  hDlgTalk  );
   __declspec(  dllexport  )  int  activateImTask(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  iTaskId_activated  );
   __declspec(  dllexport  )  int  dlgTalk_doLayout(  HWND  hDlgTalk  );
   __declspec(  dllexport  )  int  dlgTalk_SetPicRect(  HWND  hDlgTalk,  int  w,  int  h,  BOOL  bMoveWindow  );
   __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo,  HWND  *  phWnd  );
   __declspec(  dllexport  )  int  removeTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused  );
   __declspec(  dllexport  )  int  addToRecentMsg(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  long  lRowIndex,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo_talker,  LPCTSTR  talkerDesc,  unsigned  short  usOp,  int  iStatus,  char  *  timeBuf,  LPCTSTR  rowIdStr,  LPCTSTR  content,  BOOL  bFollowingRows,  BOOL  bScrollIntoView,  TCHAR  *  txtBuf,  unsigned  int  uiTxtBufCnt  );
   __declspec(  dllexport  )  int  modifyRow(  void  *  p0,  void  *  pPARAM_PROC_ROW,  void  *  pIHTMLTableRow  );
   //  __declspec(  dllexport  )  int  getTaskItem(  CListCtrl  *  pListCtrl,  int  iTaskId  );
   __declspec(  dllexport  )  int  getTaskItem(  HWND  hListCtrl,  int  iTaskId  );
   __declspec(  dllexport  )  int  getTalkerShadow(  HWND  hParent,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  int  iTalkerSubType,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
   __declspec(  dllexport  )  BOOL  isMemFromActive(  void  *  pDLG_TALK_videoConference,  QY_MESSENGER_ID  *  pIdInfo_from,  int  *  pIndex_activeMems_from  );
   __declspec(  dllexport  )  int  getlRowIndex(  void  *  p0,  void  *  pPARAM_PROC_ROW,  void  *  pIHTMLTableRow  );
   __declspec(  dllexport  )  BOOL  dlgTalk_bEnableScrollBar(  HWND  hDlgTalk,  BOOL  bEnable  );
   __declspec(  dllexport  )  int  viewInstantAssistant(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgTalk,  BOOL  bNoDelayToView  );
   __declspec(  dllexport  )  int  talkToMessenger(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );

   __declspec(  dllexport  )  int viewStatusCli(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfDisplayListContent  );

    __declspec(  dllexport  )  int  testLocalAv(  HWND  hParent  );
	__declspec(  dllexport  )  int  tmpHandler_bRemoveMsgInProcessQ(  void  *  p0,  void  *  p1, void  *  pMsgParam  );
	
	__declspec(  dllexport  )  int mainWnd_OnQyTrayNotify(  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  );
	__declspec(  dllexport  )  void mainFrm_OnqyClearUp(  HWND  hMainWnd  );

	__declspec(  dllexport  )  int  showDlgPropImGrp(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
	__declspec(  dllexport  )  int  showDlgPropImMsg(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  id  );
	__declspec(  dllexport  )  int  showDlgPropMessenger(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo  );
	__declspec(  dllexport  )  int  showDlgPropMessenger(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr  );

	//
__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr,  int  id,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  );
__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  );
__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  );

__declspec(  dllexport  )  int  showDlgPropImTask(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  BOOL  bHisTab,  int  id  );

__declspec(  dllexport  )  int  showDlgQnmSearch(  HWND  hParent,  int  *  iType  );
__declspec(  dllexport  )  int  showDlgImMsgSearch(  HWND  hParent,  MY_DB_BUF  *  pDbBufs,  int  iQueryType  );
#endif  //  }



