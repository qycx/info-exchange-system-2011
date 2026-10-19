
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"dlgtalkproc.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDmoPublic.h"

#include	"wallTalkers.h"
#include	"qmcGpsProc.h"
#include	"aecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"


 void  *  getDlgWallsVar(  HWND  hDlgWalls,  int  iWndContentType  )
 {
	 switch  (  iWndContentType  )  {
			 case  CONST_qyWndContentType_vWall:
				   return  getDlgWallsVar_dynBmps(  hDlgWalls,  iWndContentType  );
				   break;
			 case  CONST_qyWndContentType_ts_main:
				   #ifdef  __APP_qyMc_touchscreen__
						   return  getDlgWallsVar_ts(  hDlgWalls,  iWndContentType  );
				   #endif
				   break;
			 case  CONST_qyWndContentType_wallD3d:
				   return  getDlgWallsVar_wallD3d(  hDlgWalls,  iWndContentType  );
				   break;
			 default:
					break;
	 }

	 return  NULL;
 }


void  *  FUNCS_for_isCliHelp_new(  )
{
	int						iErr	=	-1;
	FUNCS_for_isCliHelp	*  pFuncs  =  NULL;
	int						size  =  sizeof(  FUNCS_for_isCliHelp  );
	pFuncs  =  (  FUNCS_for_isCliHelp  *  )malloc(  size  );
	if  (  !pFuncs  )  goto  errLabel;
	memset(  pFuncs,  0,  size  );

	//
	pFuncs->pf_addTxtToPic_screen  =  addTxtToPic_screen;
	pFuncs->pf_setPktInputInfo  =  setPktInputInfo;
	pFuncs->pf_CTX_addTxt_free  =  CTX_addTxt_free;


	//
	pFuncs->pf_askToRefreshLayout_mgr  =  askToRefreshLayout_mgr;
#ifdef  __APP_qyMc__
	pFuncs->pf_bFullScreen_walls  =  bFullScreen_walls_default;
#else
	pFuncs->pf_bFullScreen_walls  =  bFullScreen_walls_ts;
#endif
	pFuncs->pf_bMainWndAbove  =  bMainWndAbove;
	pFuncs->pf_bMessengerOnline  =  bMessengerOnline;
	pFuncs->pf_bQisExportVWall  =  bQisExportVWall;
	pFuncs->pf_bQisImportVWall  =  bQisImportVWall;
	pFuncs->pf_bWebcamUsing  =  bWebcamUsing;
	pFuncs->pf_bRecorderUsing  =  bRecorderUsing;

	pFuncs->pf_bQnmExportCurQuery  =  bQnmExportCurQuery;

	pFuncs->pf_bViewImTaskListFunc  =  bViewImTaskListFunc;

	pFuncs->pf_canRemotePtzControl  =  canRemotePtzControl;
	pFuncs->pf_canShareScreen_dx  =  canShareScreen_dx;
	pFuncs->pf_CAP_STUFF_free  =  CAP_STUFF_free;
	pFuncs->pf_CAP_STUFF_new  =  CAP_STUFF_new;
	pFuncs->pf_getChosenDevice  =  getChosenDevice;
	pFuncs->pf_myChooseDevices  =  myChooseDevices;
	pFuncs->pf_chooseAvDevice_mgr  =  chooseAvDevice_mgr;
	pFuncs->pf_cfgCaptureFilter  =  cfgCaptureFilter;
	pFuncs->pf_cfgCapturePin  =  cfgCapturePin;
	pFuncs->pf_cfgCrossBar  =  cfgCrossBar;
	pFuncs->pf_chkTalkerRules  =  chkTalkerRules;
	pFuncs->pf_chkToViewDynBmp  =  chkToViewDynBmp;

	pFuncs->pf_delImObj  =  delImObj;
	pFuncs->pf_displayNotification_talk_ts  =  displayNotification_talk_ts;
	pFuncs->pf_dlgDynBmps_getZoneParam  =  dlgDynBmps_getZoneParam;
	pFuncs->pf_bDlgTalkAbove  =  bDlgTalkAbove;
	pFuncs->pf_dlgTalk_cancelTasks  =  dlgTalk_cancelTasks;
	pFuncs->pf_dlgTalk_OnDestroy  =  dlgTalk_OnDestroy;
	pFuncs->pf_dlgTalk_OnInitDialog  =  dlgTalk_OnInitDialog;
	pFuncs->pf_dlgTalk_OnQyComm  =  dlgTalk_OnQyComm;
	pFuncs->pf_dlgTalk_OnQyPostComm  =  dlgTalk_OnQyPostComm;
	pFuncs->pf_dlgTalk_qPostMsg  =  dlgTalk_qPostMsg;
	pFuncs->pf_dlgTalk_requestToSpeak  =  dlgTalk_requestToSpeak;
	pFuncs->pf_dlgTalk_procTask1  =  dlgTalk_procTask1;
	pFuncs->pf_dlgTalk_procTask_htmlEdit  =  dlgTalk_procTask_htmlEdit;
	pFuncs->pf_tmpHandler_chkVWallRule_dlgDynBmps  =  tmpHandler_chkVWallRule_dlgDynBmps;
	pFuncs->pf_dlgVideos_procVideo  =  dlgVideos_procVideo;
	pFuncs->pf_doCmd_startAvCall  =  doCmd_startAvCall;
	pFuncs->pf_stopAll_avRecord  =  stopAll_avRecord;
	pFuncs->pf_doCmd_startShareMediaDevice  =  doCmd_startShareMediaDevice;
	pFuncs->pf_doCmd_startShareMediaFile  =  doCmd_startShareMediaFile;


	pFuncs->pf_enumDmoIoTypes	=	enumDmoIoTypes;
	pFuncs->pf_enumDmos  =  enumDmos;

	pFuncs->pf_exitShareMediaFile  =  exitShareMediaFile;

	pFuncs->pf_fillQyMcQuery  =  fillQyMcQuery;
	//
	pFuncs->pf_findQMemByKey  =  findQMemByKey;

	pFuncs->pf_findTalker  =  findTalker;
	pFuncs->pf_findTaskInProcessQ  =  findTaskInProcessQ;
	//
	pFuncs->pf_getCusModule  =  getCusModule;
	pFuncs->pf_getDlgWallsVar  =  getDlgWallsVar;
	//
	pFuncs->pf_getDmoInfoBySth  =  getDmoInfoBySth;
	//
	pFuncs->pf_get_g_guiData  =  get_g_guiData;
	pFuncs->pf_getMenuStatus  =  getMenuStatus;
	pFuncs->pf_getMisCntByName  =  getMisCntByName;

	//
	pFuncs->moniker.pf_addDevicesToMenu  =  addDevicesToMenu;

	pFuncs->moniker.pf_getMoniker_a  =  getMoniker_a;
	pFuncs->moniker.pf_getMoniker_v  =  getMoniker_v;
	pFuncs->moniker.pf_getMonikerDisplayName  =  getMonikerDisplayName;
	pFuncs->moniker.pf_getMonikerProp  =  getMonikerProp;
	
	pFuncs->moniker.pf_getADevFriendlyName  =  getADevFriendlyName;
	pFuncs->moniker.pf_getADeviceGuid  =  getADeviceGuid;

	//
	pFuncs->pf_getProcedObjDb  =  getProcedObjDb;
#ifdef  __APP_qyMc__
	pFuncs->pf_getRect_talkers  =  getRect_talkers_default;
#else
	pFuncs->pf_getRect_talkers  =  getRect_talkers_ts;
#endif

	pFuncs->pf_getShareMediaFileState  =  getShareMediaFileState;

	pFuncs->pf_getTalkerDesc  =  getTalkerDesc;

	pFuncs->gps.pf_toShareGps  =  toShareGps;

	//
	pFuncs->pf_imObjRulesReq2ImRules  =  imObjRulesReq2ImRules;
	pFuncs->pf_imObjRulesReq2Rules  =  imObjRulesReq2Rules;

	pFuncs->pf_initShareMediaFile  =  initShareMediaFile;

	pFuncs->pf_netMc_procTreeEvent  =  netMc_procTreeEvent;

	pFuncs->pf_msg2TaskRcd  =  msg2TaskRcd;

	pFuncs->pf_pauseShareMediaFile  =  pauseShareMediaFile;
	//
	pFuncs->pf_postMsg2Mgr_mc  =  postMsg2Mgr_mc;
	pFuncs->pf_postMsgTask2Mgr_mc  =  postMsgTask2Mgr_mc;
	//
	//  pFuncs->pf_requestToSpeak_videoConferenceOthers  =  requestToSpeak_videoConferenceOthers;
	pFuncs->pf_requestToSpeak_videoConferenceStarter  =  requestToSpeak_videoConferenceStarter;

	pFuncs->pf_runShareMediaFile  =  runShareMediaFile;

	pFuncs->pf_saveChosenDevice  =  saveChosenDevice;
	pFuncs->pf_sendVideoConferenceLayout  =  sendVideoConferenceLayout;
	pFuncs->pf_sendVideoConferenceStatus  =  sendVideoConferenceStatus;
	pFuncs->pf_setCurSharedObjUsr_localAv  =  setCurSharedObjUsr_localAv;
	pFuncs->pf_resetCurSharedObjUsr_localAv  =  resetCurSharedObjUsr_localAv;
	pFuncs->pf_setEncodingDefaults_video  =  setEncodingDefaults_video;

	pFuncs->pf_stopShareMediaFile  =  stopShareMediaFile;
	pFuncs->pf_storeTaskInDb  =  storeTaskInDb;
	pFuncs->pf_toShareBmp  =  toShareBmp;
	//
	pFuncs->pf_startProgress  =  startProgress;

	pFuncs->pf_talkerShadow_procGps  =  talkerShadow_procGps;
	pFuncs->pf_TALKER_shadow_free  =  TALKER_shadow_free;
	pFuncs->pf_talkToMessenger  =  talkToMessenger;
	pFuncs->pf_testLocalAv  =  testLocalAv;
	pFuncs->pf_tmpHandler_showMsg  =  tmpHandler_showMsg;
	pFuncs->pf_toSelectRegion  =  toSelectRegion;
	pFuncs->pf_toSelectRegion1  =  toSelectRegion1;
	pFuncs->pf_tryToTalkToMessenger  =  tryToTalkToMessenger;
	pFuncs->pf_doSth_afterInitDlgTalk  =  doSth_afterInitDlgTalk;

	//
	pFuncs->pf_tryToTalkToMessenger_wallD3d  =  tryToTalkToMessenger_wallD3d;

	//
	pFuncs->pf_updateMeDisplayInfo  =  updateMeDisplayInfo;
	//
	pFuncs->pf_viewInstantAssistant  =  viewInstantAssistant;
#ifdef  __APP_qyMc_touchscreen__
	pFuncs->pf_viewWallsBar_ts  =  viewWallsBar_ts;
#endif
	pFuncs->pf_vw_getCurSp  =  vw_getCurSp;

	//
	pFuncs->pf_testLocalAv_openLocalVideo  =  testLocalAv_openLocalVideo;
	pFuncs->pf_doCmd_test  =  doCmd_test;

	//
	pFuncs->pf_stopLocalAudioPlaying  =  stopLocalAudioPlaying;
	pFuncs->pf_freeSharedObjUsr_localAv  =  freeSharedObjUsr_localAv;

	//  2013/07/01
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus  =  dlgShareDynBmps_refreshShareStatus;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_getShareDynBmpsBySth  =  (  PF_dlgShareDynBmps_getShareDynBmpsBySth  )dlgShareDynBmps_getShareDynBmpsBySth;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus_gps  =  dlgShareDynBmps_refreshShareStatus_gps;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyComm  =  dlgShareDynBmps_OnQyComm;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyPostComm  =  dlgShareDynBmps_OnQyPostComm;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkSharedObj  =  dlgShareDynBmps_chkSharedObj;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareWebcam  =  dlgShareDynBmps_toShareWebcam;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareGps  =  dlgShareDynBmps_toShareGps;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv  =  dlgShareDynBmps_closeTaskAv;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkShareGps  =  dlgShareDynBmps_chkShareGps;

	//
	iErr  =  0;
errLabel:

	return  pFuncs;
}	


void  FUNCS_for_isCliHelp_free(  void  **  ppFuncs  )
{
	if  (  !ppFuncs  )  return;
	if  (  !*ppFuncs  )  return;

	free(  *ppFuncs  );  *ppFuncs  =  NULL;
	return;
}