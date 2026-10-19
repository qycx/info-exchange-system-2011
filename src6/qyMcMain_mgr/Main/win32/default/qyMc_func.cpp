
#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"
//
#include	"dlgTalkProc.h"

#include "qyMc.h"

#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

//	#include	"DlgSelectAvDev.h"

//  #include	"DlgShareDynBmps.h"

/*
#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

#include	"DlgProgress.h"
#include	"tmpCeLib.h"
*/

#include	"qmcCmdProc.h"
#include	"LeftView.h"
#include	"qyMcView.h"
#include	"qyComPortEx.h"

int  viewMediaControl(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  )
{
	  return  -1;
}

int  viewMediaControl_qmCmd(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  )
{
	  return  -1;
}

int  viewWallsBar(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  BOOL  bNoDelayToView  )
{
	  return  -1;
}
int  setWallsBarPos(  HWND  hDlgWalls,  HWND  hBar  )
{
	  return  -1;
}

__declspec(dllexport) void ChooseDevices(AV_capStuff  &  gcap,IMoniker *pmVideo, IMoniker *pmAudio)
{
	return;
}
__declspec(dllexport)  int   cfgCaptureFilter(  void  *  pAvCapStuff,  HWND  hwndParent  )
{
	  return  -1;
}
 __declspec(dllexport)  int   cfgCapturePin(  void  *  pAvCapStuff,  HWND  hwndParent  )
{
	  return  -1;
}
 __declspec(dllexport)  int   cfgCrossBar(  void  *  pAvCapStuff,  HWND  hwndParent  )
{
	  return  -1;
}
__declspec(dllexport)  void  *  get_ICaptureGraphBuilder(  void  *  pBuilderParam  )
{
	  return  NULL;
}
__declspec(dllexport) BOOL InitCapFilters(  AV_capStuff  &  gcap  )
{
	  return  FALSE;
}
__declspec(dllexport) void FreeCapFilters(  AV_capStuff  &  gcap  )
{
	  return;
}
__declspec(dllexport) void TearDownGraph(  AV_capStuff  &  gcap )
{
	  return;
}
__declspec(dllexport) BOOL StopPreview(  AV_capStuff  &  gcap  )
{
	  return FALSE;
}
__declspec(dllexport) void IMonRelease(IMoniker *&pm)
{
	  return;
}
__declspec(dllexport) BOOL StopCapture(AV_capStuff  &  gcap)
{
	  return FALSE;
}

extern  "C"  __declspec(dllexport)  BOOL InstallMyHook(HWND hWnd, UINT msg)
{
	  return FALSE;
}
extern  "C"  __declspec(dllexport)  BOOL UninstallMyHook(HWND hWnd)
{
	  return FALSE;
}


int  setPasswd_isClient(  HWND  hParent  )
{
	  return  -1;
}


MIS_CNT  *  getMisCntByName(  void  *  pQyMcParam,  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  misServName  )
{
	  return  NULL;
}

CAP_procInfo_bmpU  *  getCapBmpBySth(  MC_VAR_isCli  *  pProcInfo,  int  index,  unsigned  int  uiCapType  )
{
	  return  NULL;
}

int  getMessengerImages(  QY_MC  *  pQyMc,  unsigned  short  usRunningStatus,  int  *  pnImage,  int  *  pnSelectedImage  )
{
	  return  -1;
}

BOOL  bRefreshMeStatus_wnd(  MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  )
{
	  return  FALSE;
}
BOOL  bRefreshContactsStatus_wnd(  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  )
{
	  return  FALSE;
}
#if  0
  void  exitMcCtxDisplayedWnd(  HWND  hWnd,  MC_CTX_DISPLAYEDWND  *  pCtx )
{
	  return;
}
  int  initMcCtxDisplayedWnd(  HWND  hWnd,  LPCTSTR  wndName,  MC_CTX_DISPLAYEDWND  *  pCtx  )
{
	  return  -1;
}
#endif
 int  handleGraphEvent_mediaFile(  void  *  pShareMediaFile,  BOOL  bMediaFile,  BOOL  bLooping,  BOOL  bPlayThrough  )
{
	  return  -1;
}
 QY_SHARED_OBJ  *  getSharedObjByIndex(  MC_VAR_isCli  *  pProcInfo,  int  index  )
{
	  return  NULL;
}
 int  handleGraphEvent_videoCapDev_dx(  void  *  pVideoCapDevParam  )
{
	  return  -1;
}
   int  handleGraphEvent_mediaDevice(  void  *  pShareMediaDeviceParam  )
{
	  return  -1;
}

int  dlgTalk_qPostMsg(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
{
	  return  -1;
}

int  doApplyForPlayer(  HWND  hMainWnd,  MIS_MSGU  *  pMsg  )
{
	  return  -1;
}

int  qisApplyForChkingTasks_gui(  )
{
	  return  -1;
}

DLG_TALK_var  *  getDlgTalkVar(  HWND  hDlgTalk  )
{
	  return  NULL;
}

 int  getTalkerDesc(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  TCHAR  *  talkerDesc,  unsigned  int  talkerDescCnt,  TCHAR  *  shortName,  unsigned  int  shortNameCnt  )
{
	  return  -1;
}

  char  *  displayShortTime(  time_t  t,  char  *  timeBuf,  unsigned  int  len  )
{
	  return  NULL;
}

QM_SHM_CMD  *  getShmCmdByIndex(  QM_SHM_CMDS  *  pCmds,  int  iIndex  )
{
	  return  NULL;
}
BOOL  bViewImMsgToday(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}

BOOL  bViewRealTimeImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}
BOOL  bViewMessengerStatusList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}
BOOL  bViewImNetStatList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}
BOOL  bViewPlayerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )	
{
	  return  FALSE;
}
BOOL  	bViewSharingObjectList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}
BOOL  bViewTalkerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}
BOOL  bViewWallList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	  return  FALSE;
}

int  tryToTalkToMessenger(  MSGR_ADDR  *  pAddr,  BOOL  bActivateWnd,  HWND	*	phWnd  )
{
	  return  -1;
}
int  tryToTalkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bActivateWnd,  HWND	*	phWnd  )
{
	  return  -1;
}
#if  0
 int  viewDynBmp(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  LPCTSTR  cusName  )
{
	  return  -1;
}
#endif

 int  sndRetrieveDynBmpsReq_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bRetrieveAll  )
{
	  return  -1;
}
  int  is_procLvEventFunc_new(  void  *  pQyMcParam,  void  *  pm_docStructParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
{
	  return  -1;
}
 BOOL  bViewImObjView_isCli_mdi(  QY_OBJ_DB  *  pObjDb  )
{
	  return  FALSE;
}
#if  0
int  displayListContent_imObjs(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	  return  -1;
}
 int  displayListContent_allTopCols(  QY_OBJ_DB  *  pObjDb,  CQyMcView  *  pMcView,  QY_MC_DISPLAYCFG	*	pCfgParam,  LPCTSTR  tabName_regInfo  )
{
	  return  -1;
}
 int  displayListContent_bz(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	  return  -1;
}
#endif
 int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  HTREEITEM  hItem  )
{
	  return  -1;
}
int  showInfo_open(  void  *  p0,  void  *  p1,  LPCTSTR  hint  )
{
	  return  -1;
}
 int  showNotification_open(  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	  return  -1;
}
 int  postReq2Mgr_mc_open(  void  *  pQyVDevParam,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  pVDevReqParam,  unsigned  int  dataLen  )
{
	  return  -1;
}
 int  postStr2Mgr_mc_open(  void  *  pQyVDevParam,  unsigned  int  uiObjType_from,  unsigned  int  uiDevType_from,  WCHAR  *  devId_from,  WCHAR  *  wReversePath,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  char  *  idStr_to,  unsigned  int  uiChannelType  )
{
	  return  -1;
}
 int  postHint2Mgr_mc_open(  void  *  pQyVDevParam,  WCHAR  *  who,  time_t  tStartTime,  unsigned  int  uiTranNo,  LPCTSTR  str  )
{
	  return  -1;
}
 BOOL  bGetLongProperty_open(  void  *  p0,  void  *  propertyIdParam,  void  *  plVal  )
{
	  return  -1;
}
 char  *  iFourcc2Str(  int  fourcc,  char  *  fourccStr,  unsigned  int  size  )
{
	  return  NULL;
}
 
int  testDmoCompressAudioInit(  ) 
{
	  return  -1;
}
 int  showAcm(  ) 
{
	  return  -1;
}
 int  testDx(  )
{
	  return  -1;
}
 int  testGpsFunc(  )
{
	  return  -1;
}
int  doQmCmdMain(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	  return  -1;
}
int  tmpHandler_broadcastMsg(  void  *  p0,  void  *  p1,  void  *  pQElem  )
{
	  return  -1;
}
int  myGetPeer(  LPCTSTR  misServName,  MSG_ROUTE  *  pRoute,  MSGR_ADDR  *  pAddr_logicalPeer,  MSGR_ADDR  *  pPeer  )
{
	  return  -1;
}
BOOL bDlgTalkAbove(  HWND hWnd  )
{
	  return  FALSE;
}
int  notifyPanicToApp(  int  iErr,  LPCTSTR  hint  )
{
	  return  -1;
}
int  chkPlayers(  MC_VAR_isCli  *  pProcInfo  )
{
	  return  -1;
}
int  broadcastMsg(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  BOOL  bActivateWnd,  MIS_MSGU  *  pMsg,  unsigned  int  uiMsgLen  )
{
	  return  -1;
}
BOOL  bMessengerOnline(  QY_MC  *  pQyMc  )
{
	  return  FALSE;
}
BOOL  bChkMessengerChannelsReady(  QY_MC  *  pQyMc  )
{
	  return  FALSE;
}
int  initTestGps(  )
{
	  return  -1;
}
void  exitTestGps(  )
{
	  return;
}
int  closeOtherWnds_isCli(  BOOL  *  pbOtherWndExists  )
{
	  return  -1;
}
int  closeAllConversations(  LPVOID  pQyMcParameter,  BOOL  *  pbConversationExists  )
{
	  return  -1;
}
int  addNotification(  MIS_MSG_taskStatus  *  pStatus  )
{
	  return  -1;
}
int  popupNotificationWnd(  )
{
	  return  -1;
}
__declspec(  dllexport  )  void  *  newQyWnd(  int  iWndContentType  )
{
	  return  NULL;
}
__declspec(  dllexport  )  void  freeQyWnd(  void  *  pWnd  )
{
	  return;
}
__declspec(  dllexport  )  void  *  qyWnd_getGuiData(  void  *  pDlg  )
{
	  return  NULL;
}
__declspec(  dllexport  )  INT_PTR CALLBACK dlgProc_instantAssistant(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	  return  NULL;
}
int  showDlgQnmCfgOptionsIsClient(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiData_qnmCfgOptionsIsClient  *  pParam  )
{
	  return  -1;
}
int  gGuiData_init(  G_guiData_qyMc  *  pGuiData  )
{
	if  (  pGuiData->bInited  )  return  -1;
	
	pGuiData->bInited  =  TRUE;

	return  0;
}

int  gGuiData_exit(  G_guiData_qyMc  *  pGuiData  )
{
	if  (  !pGuiData->bInited  )  return  0;
	

	//  2013/01/15
	pGuiData->bInited  =  FALSE;

	return  0;
}
int  showDlgMcClientLogon(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  p2  )
{
	  return  -1;
}
int  showDlgObjs(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiDataParam_objs  *  pParam  )
{
	  return  -1;
}
int parseGpsStr(  CComPortEx  *  pPort,  char  *  str  )
{
	  return  -1;
}
int  dlgLayout_objs(  HWND  hDlg,  DLG_guiData_objs  *  p  )
{
	  return  -1;
}
 int  shareDynBmps_isClient(  BOOL  bNeed_shareWebcamInConference  )
{
	  return  -1;
}
int  testLocalAv(  HWND  hParent  )
{
	  return  -1;
}
int viewGpsVWall(QY_OBJ_DB * pObjDb, LPCTSTR misServName) 
{
	
	  return  -1;
}
int viewGlobalVWall(QY_OBJ_DB * pObjDb, LPCTSTR misServName)
{
	
	  return  -1;
}
int viewGlobalGpsVWall(QY_OBJ_DB * pObjDb, LPCTSTR misServName)
{
	
	  return  -1;
}
int viewVWall(QY_OBJ_DB * pObjDb, LPCTSTR misServName, int iSubType, BOOL bNewVirtualWall, HWND * phWnd)
{
	
	  return  -1;
}
int viewStatusCli(  int  iWndContentType  )
{
	
	  return  -1;
}
int getSharedObjIndex_localAv()
{
	  return  -1;
}
HWND  findSubWnd(  CAP_subWnds  *  p,  int  iWndContentType,  int  iWndContentSubType  )
{
	  return  NULL;
}
extern "C" DWORD WINAPI mcThreadProc_isCli( LPVOID lpParameter )
{
	  return  -1;
}

int  getPolicyIsClient(  MC_VAR_isCli  *  pProcInfo,  POLICY_isClient  * p   )
{
	  return  -1;
}
int  initPolicyAvParams(  )
{
	  return  -1;
}
BOOL CALLBACK myEnumWindowsProc_singleInstance(  HWND hwnd,  LPARAM lParam  )
{
	  return  NULL;
}
int initAvRecordMgr(HINSTANCE g_hInst)
{
	  return  -1;
}
void exitAvRecordMgr()
{
	  return;
}
void exitDxSurfaceMgr()
{
	  return;
}
void exitDSoundToPlay(void * pDynLib_dx, void * p1, void * p2)
{
	  return;
}
int  closeOtherPlayers(  )
{
	  return  -1;
}
int sizeAllControls_dlgTalk(HWND hDlg, DLG_TALK_var & m_var)
{
	  return  -1;
}
//  MIS_MSG_TASK * findTaskInProcessQ(DLG_TALK_var & m_var, int iTaskId, BOOL bNextAv = FALSE, BOOL bToShareScreen = FALSE)
MIS_MSG_TASK  *  findTaskInProcessQ(  DLG_TALK_var  &m_var,  int  iTaskId,  BOOL  bNextAv,  BOOL  bToShareScreen  )
{
	  return  NULL;
}
int qisChkTasks_gui()
{
	  return  -1;
}
BOOL bNoSharedObjExists()
{
	  return  FALSE;
}
int  findTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused,  HWND  *  phWnd  )
{
	  return  -1;
}

  int  postMsgTask2Mgr_mc(  MIS_CNT  *  pMisCnt,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	  return  -1;
}

int  postMsg2MgrFunc_mc(  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  
						QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  
						QY_MESSENGER_ID	 *  pIdInfo_taskSender,					
						QY_MESSENGER_ID	 *  pIdInfo_taskReceiver,				
						QY_MESSENGER_ID  *  pIdInfo_dst,  
						unsigned  int  uiChannelType,
						MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
   {
	   return  -1;
   }


int tryToFreeSharedObjs()
{
	  return  -1;
}
int  sizeAllControls_dlgObjs(  HWND  hDlg,  DLG_guiData_objs  *  p  )
{
	  return  -1;
}
void stopAll_avRecord()
{
	  return;
}
void stopAll_sharedObjs()
{
	  return;
}

 BOOL  bViewImTaskList_unproced_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
 BOOL  bViewImTaskList_cur_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
 BOOL  bViewImTaskList_his_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
 
	__declspec(  dllexport  )  BOOL  bSelectImGrpMem_dlgTalk_OnInitDialog_odbc(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam  )

 {
	 return  FALSE;
 }
BOOL  bGetImTaskRcdBySth_odbc(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  )
 {
	 return  FALSE;
 }
BOOL  bClearupDeletedImObjs_isClient_odbc(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
 {
	 return  FALSE;
 }
BOOL  bMoveTask2His_odbc(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
 {
	 return  FALSE;
 }
BOOL  bSelectImTask_storeTaskInDb_odbc(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
 {
	 return  FALSE;
 }
BOOL	bNeedRetrieveImGrpMems_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName  )
 {
	 return  FALSE;
 }
int  updateTaskStatus_odbc(  void  *  pDb,  int  iStatus,  int  iTaskId  )
{
	  return  -1;
}
int  insertImTask_storeTaskInDb_odbc(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	  return  -1;
}
int  selectImTask_dlgTalk_loadTasks_odbc(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  )
{
	  return  -1;
}
int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam,  QY_MESSENGER_ID	  *  pIdInfo_related  )
{
	  return  -1;
}
int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam  )
{
	  return  -1;
}
int  mcProcResp_refreshContacts_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_CONTACTLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	  return  -1;
}
int  mcProcResp_refreshContacts_end_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_CONTACTLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	  return  -1;
}
int  mcProcResp_refreshImGrpMems_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	  return  -1;
}
int  mcProcResp_refreshImGrpMems_end_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	  return  -1;
}
int  mcProcResp_refreshImGrps_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	  return  -1;
}
int  mcProcResp_refreshImGrps_end_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	  return  -1;
}
void  fillImObjs_msgr_odbc(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	  return;
}
void  fillImObjs_grp_odbc(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	  return;
}

__declspec(  dllexport  )  int  listObjs_dlgMsgList_odbc(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{
	return  -1;
}

BOOL  bInsertPhoneGuest_procMsgTalk_work_odbc(  void  *  pDb,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  )
 {
	 return  FALSE;
 }
BOOL  bUpdateImTask_bChkQyMcEnv_mis_odbc(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  )
 {
	 return  FALSE;
 }
int  deleteDynBmp_tmpHandler_delOld_dynBmpQ_odbc(  void  *  pDb,  int  id  )
{
	return  -1;
}
int  iSelectDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pCtxParam  )
{
	return  -1;
}
BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pMisCntParam,  QIS_DYN_BMP  *  pMem,  char  *  pTimeParam  )
 {
	 return  FALSE;
 }
BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pMemParam,  int  rcdId  )
 {
	 return  FALSE;
 }
BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_odbc(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  )
 {
	 return  FALSE;
 }
BOOL  bViewImGrpMemList_isClient_odbc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
#if  0
BOOL  bViewImMsgListFunc_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
#endif
 BOOL  bStatImTasks_odbc(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bStatImTasks_odbc"  )  );
#endif
	  return  FALSE;
}

int  postRecentFriend(  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo,  int  iOp  )
{
	return  -1;
}
BOOL  bDeleteFromTabById_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  int  id  )
{
	return  FALSE;
}
BOOL  bDeleteFromTabByIdInfo_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	return  FALSE;
}
BOOL  bDeleteImOtherRegInfoByAddr_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  )
{
	return  FALSE;
}


int  iSelectImGrpMem_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  )
{
	return  -1;
}


int  iSelectImObj_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}

#if  0
int  iSelectImObjAuth2_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd,  void  *  pVarVals,  int  iVarValSize  )
{
	return  -1;
}
#endif

int  iSelectDynBmp_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}

 __declspec(dllexport)  int   set_g_pQyMc_isCliHelp(  void  *  pQyMc  )
{
	return  0;
}


   __declspec(dllexport)  int   set_g_dbPool_isCliHelp(  void  *  pPool,  int  cnt  )
   {
	   return  0;
   }


   int  setModalWnd(  HWND  hDlg  )
   {
#ifdef  __DEBUG__
	    traceLog(  _T(  "unused: setModalWnd"  )  );
#endif

	   return  0;
   }




 BOOL  bSupported_gps(  )
 {
	 return  FALSE;
 }

// int  tryToTalkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bActivateWnd,  HWND	*	phWnd  )
	 int  tryToTalkToMessenger(  void  *  pMSGR_ADDR,  BOOL  bActivateWnd,  HWND	*	phWnd  )

 {
	 return  -1;
 }


 int  updateImGrpMem_refreshImGrpMems_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
 {
	 return  -1;
 }

int  updateImObj_refreshContacts_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
{
	return  -1;
}

int  updateImObj_refreshImGrps_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  )
{
	return  -1;
}

BOOL  bViewImMsgListFunc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}



