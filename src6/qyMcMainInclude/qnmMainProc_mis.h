 
#ifndef  __QNMMAINPROCMIS_H__
#define  __QNMMAINPROCMIS_H__  //  {


typedef  struct  __param_applyForServWork_t				{
				 unsigned  int							uiType;		//  对组来说，通常指CONST_imCommType_refreshImGrp
				 //
				 void								*	p0;
				 void								*	p1;
				 void								*	p2;		
				 //
}		 PARAM_applyForServWork;


typedef  struct  __param_procLvEventFunc_is_t			{		
				 TCHAR									misServName[CONST_maxMisServNameLen  +  1];
				 time_t									t;
				 //
				 QY_MESSENGER_ID						idInfo;				//  2009/09/17
				 //
				 QY_MESSENGER_ID						idInfo_grp;
				 //
				 PARAM_applyForServWork					param_applyForServWork;

				 //  这个Q是为了形成临时组用的
				 GENERIC_Q								tmpGrpMemQ;
				 BOOL									bTmpQInited;
				 //
}		 PARAM_procLvEventFunc_is;


int  getScreenXy(  int  *  pScreenX,  int  *  pScreenY  );

MIS_CHANNEL  *  getChannelByType(  MIS_CNT  *  pMisCnt,  unsigned  int  uiChannelType  );
BOOL  bChannelOk(  QY_MC  *  pQyMc,  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel  );
//
BOOL  bMisCntOnline(  QY_MC  *  pQyMc,  MIS_CNT  *  pMisCnt  );
//
BOOL  bMessengerOnline(  QY_MC  *  pQyMc  );
BOOL  bMessengerTalking(  QY_MC  *  pQyMc  );
BOOL  bChkMessengerChannelsReady(  QY_MC  *  pQyMc  );

int  getMessengerImages(  QY_MC  *  pQyMc,  unsigned  short  usRunningStatus,  int  *  pnImage,  int  *  pnSelectedImage  );



int  getSthForObjs(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex,  int  *  pIndexDisplayed,  int  *  pIndexToDisplay,  int  *  piObjTypeToDisplay,  TCHAR  *  whereClause,  unsigned  int  size  );


//
BOOL  bViewImMsgToday(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bViewImMsgListFunc_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImMsgListFunc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

BOOL  bViewImObjView(   QY_OBJ_DB  *  pObjDb  );

//
BOOL  bViewImObjView_isCli_sdi(  QY_OBJ_DB  *  pObjDb  );
BOOL  bRefreshImObjView_isCli_sdi(  QY_OBJ_DB  *  pObjDb  );

//
BOOL  bViewImObjAuthList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImObjAuthNeedAuditedList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImAmList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

BOOL  bViewPhoneMessengerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );


int  applyForServWork(  unsigned  int  uiContentType,  void  *  p0,  void  *  p1,  void  *  p2  );	//  申请服务器做一些工作

BOOL  bNewMessenger(  );
BOOL  bNewImGrp(  );
BOOL  bViewImGrpAuthList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//
BOOL  bViewImObjListFunc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//
BOOL  bViewMessengerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewMessengerRegInfoList(  QY_OBJ_DB  *  pObjDb  );
//
BOOL  bViewImGrpList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//  BOOL  bViewImGrpMemList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImGrpMemList_isClient(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//
BOOL  bViewCustomerServiceOfficerList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  );
BOOL  bViewWebContactList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewIpKnowledgeList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  );
//
BOOL  bViewPhoneGuestList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  );

BOOL  bViewGsmModemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewSmContactList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );



BOOL  bViewImTaskListFunc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart,  BOOL  bHisTab  );
//
//  BOOL  bViewUnprocedNewImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewRealTimeImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewSharingObjectList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewPlayerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewWallList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImNetStatList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewTalkerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewMessengerStatusList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//  BOOL  bViewQList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

//  int viewStatusCli(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfDisplayListContent  );
int viewStatusDaemon(  int  index  );
int viewQnmStaus(  );
int popupToWarn(  );

#ifdef  __SUPPORT_dlgWalls__
		//  int  viewWalls(  );		//  2011/02/28. touchscreen
		//  int  qisChkWalls(  );
#endif


//  BOOL  bViewEventListFunc_is(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause );

BOOL  bViewSharedDynBmpList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bViewSharedDynBmpList_isClient(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );

BOOL  bViewSharedDynBmpRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );


typedef  struct  __qmObjQParamMisClient_t		{
				 unsigned  int					uiType;
				 QY_SERVICEGUI_INFO			*	pSci;
				 MIS_CNT					*	pMisCnt;
				 void						*	pDb;
				 int							iDbType;
				 int							iObjType;
				 QY_MESSENGER_INFO			*	pClient;
}		 QMOBJQ_PARAM_MISCLIENT;


int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  HTREEITEM  hItem  );
int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  int  iObjId  );


__declspec(  dllexport  )  int  postRecentFriend(  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo,  int  iOp  );


//  int  procMsgTalk_mc_mgr(  QY_MC  *  pQyMc,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TALK  *  pMsg,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtx  );
int  procMsgTask2Output_mc(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  MIS_CHANNEL  *  pChannel  );


//  int  getIdInfo_logicalPeer(  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MSG_SIMPLE_ROUTE  *  pAddr,  QY_MESSENGER_ID  *  pIdInfo_virtualPeer  );
int  getIdInfo_logicalPeer(  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pAddr,  MSGR_ADDR  *  pAddr_virtualPeer  );
int  myGetPeer(  LPCTSTR  misServName,  MSG_ROUTE  *  pRoute,  MSGR_ADDR  *  pAddr_logicalPeer,  MSGR_ADDR  *  pPeer  );

int  testLocalAv_openLocalVideo(  HWND  hWnd_testWebcam,  void  *  pADeviceGuid,  LPCTSTR  capDevDesc,  void  *  pMoniker,  BOOL  *  pbGot_sharedObjIndex_localAv,  int  *  piIndex_sharedObj  );
__declspec(  dllexport  )  int  doCmd_test(  int  iMenuId  );
//
__declspec(  dllexport  )  void myListCtrl_delAllColumns(  HWND  hListCtrl  );
__declspec(  dllexport  )  BOOL myListCtrl_bAddColumns(  HWND  hListCtrl,  QY_COLUMNINFO * pColumns  );
//
__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem  );
__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem, int nImage  );
__declspec(  dllexport  )  BOOL myListCtrl_SetItemText(  HWND  hListCtrl,  int nItem, int nSubItem, LPCTSTR lpszText);
__declspec(  dllexport  )  BOOL myListCtrl_SetItemData(  HWND  hListCtrl,  int nItem, DWORD_PTR dwData  );
__declspec(  dllexport  )  BOOL myListCtrl_DeleteAllItems(  HWND  hListCtrl  );
__declspec(  dllexport  )  int  myListCtrl_GetItemCount(  HWND  hListCtrl  );
__declspec(  dllexport  )  BOOL myListCtrl_SetItemState(  HWND  hListCtrl,  int nItem, UINT nState, UINT nMask  );
__declspec(  dllexport  )  int  myListCtrl_GetItemText(  HWND  hListCtrl,  int nItem,  int nSubItem,  LPTSTR lpszText,  int nLen  );
__declspec(  dllexport  )  int  myListCtrl_InsertColumn(  HWND  hListCtrl,  int nCol,  const LVCOLUMN* pColumn);
__declspec(  dllexport  )  BOOL myListCtrl_GetColumn(  HWND  hListCtrl,  int nCol, LVCOLUMN* pColumn  );
__declspec(  dllexport  )  int  myListCtrl_FindItem(  HWND  hListCtrl,  LVFINDINFO* pFindInfo, int nStart  );
__declspec(  dllexport  )  BOOL myListCtrl_GetItem(  HWND  hListCtrl,  LVITEM* pItem  );
__declspec(  dllexport  )  BOOL myListCtrl_SetItem(  HWND  hListCtrl,  LVITEM* pItem  );
__declspec(  dllexport  )  BOOL myListCtrl_Update(  HWND  hListCtrl,  int nItem  );
__declspec(  dllexport  )  BOOL myListCtrl_ModifyStyle(  HWND  hListCtrl,  DWORD dwRemove,   DWORD dwAdd,   UINT nFlags );
__declspec(  dllexport  )  DWORD myListCtrl_SetExtendedStyle(  HWND  hListCtrl,  DWORD dwNewStyle);
__declspec(  dllexport  )  void  *  myListCtrl_SetImageList(  HWND  hListCtrl,  void  * pImageList,  int nImageList);
//
__declspec(  dllexport  )  BOOL myImageList_Create(  void  *  pImageList,  UINT nBitmapID, int cx, int nGrow, COLORREF crMask  );
__declspec(  dllexport  )  BOOL myImageList_DeleteImageList(  void  *  pImageList  );

//
//  int  viewLocalPtzControl(  HWND  hParent  );
#ifdef  __isCli__
		//  int  viewRemotePtzControl(  HWND  hParent,  HWND  hCurTalk  );
#endif

#ifdef  __isCli__			//
int  initPtz(  );
//  void  exitPtz(  );
//  BOOL  isActive_comPort_ptz(  );
//  int doRemotePtzCmd(  char  *  buf,  unsigned  int  iLen  );
//
#endif


//
int  startLocalAudioPlayer(  );
int  stopLocalAudioPlayer(  int  nTries  );
int  startLocalAudioPlaying(  );
int  stopLocalAudioPlaying(  );

//
int  startLocalAudioRecorder(  unsigned  int  uiRecordType,  void  *  pGuid,  LPCTSTR  capDevDesc,  int  iIndex_sharedObj,  AUDIO_COMPRESSOR_CFG  *  pCompressor  );
int  stopLocalAudioRecorder(  int  iIndex_sharedObj,  int  nTries  );
int  resumeLocalAudioRecorder(  int  iIndex_sharedObj  );

int  closeOtherPlayers(  );

int  chkPlayers(  MC_VAR_isCli  *  pProcInfo  );

int  exitDSoundToPlayIfNoPlayer(  );


#endif  //  }


