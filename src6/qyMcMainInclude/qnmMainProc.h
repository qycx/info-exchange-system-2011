

#ifndef  __QNMMAINPROC_H__
#define	 __QNMMAINPROC_H__	/*  {  */


int  getMenuStatus(  void  *  p0,  void  *  p1,  void  *  piStatus  );




BOOL  bBhbViewLogFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bBhbViewOfflineLogFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bNetMcViewScannedIpListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bNetMcViewPcAssetListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcSpListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bNetMcViewPcSpSpecialListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  osName,  LPCTSTR  spName  );
BOOL  bNetMcViewNetDevConnListFunc(  QY_OBJ_DB  *  pObjDb,  int  iQueryType,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bNetMcViewNetDevConnListFunc_unusedConn(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bNetMcViewSearchListFunc(  QY_OBJ_DB  *  pObjDb,  int  iQueryType,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bViewOpEventListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bViewPcEventListFunc_netMc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
BOOL  bNetMcViewNetDevEventListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause );
BOOL  bNetMcViewRasEventListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause );

BOOL  bNetMcStatScannedIpFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  );
BOOL  bNetMcStatPcInfoFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  );
BOOL  bNetMcStatUsrInfoFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  );
BOOL  bNetMcStatGeneralFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  );
BOOL  bNetMcStatOthersFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  );
//
BOOL  bStatMessengerInfoFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause,  LPCTSTR  groupClause,  LPCTSTR  havingClause,  QNM_QUERY_STRUCT  *  pQueryStruct  );


BOOL  bNetMcViewScannedIpList(  QY_OBJ_DB  *  pObjDb  );
//
BOOL  bNetMcViewPcView(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewPcList(  QY_OBJ_DB  *  pObjDb  );
//
BOOL  bNetMcViewPcSpList(  QY_OBJ_DB  *  pObjDb  );
//
BOOL  bViewObjRegInfoList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewObjRegInfoInTab1List(  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewClientList_netMc(  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewClientList_is(  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewClientList(  QY_OBJ_DB  *  pObjDb  );

BOOL  bViewImObjRuleList_is(  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewEventListFunc_is(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause );
BOOL  bViewOpEventListFunc_is(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause );
//
BOOL  bNetMcViewPcRuleList(  QY_OBJ_DB  *  pObjDb,  int  pcListIndex  );
//
BOOL  bNetMcViewPcSecChkEventList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
//
//  BOOL  bNetMcViewUnchkedPcList(  );
//  BOOL  bNetMcViewWillAttackPcList(  );
BOOL  bNetMcViewPcNetworkPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcNetworkRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcProxyCfgPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcProxyCfgRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//  BOOL  bNetMcViewPcComputerPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//  BOOL  bNetMcViewPcComputerRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcWindowsUpdatePolicyPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcWindowsUpdatePolicyRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//
BOOL  bNetMcViewPcPrinterPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//
BOOL  bNetMcViewPcRegistryPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );;
BOOL  bNetMcViewPcRegistryRuleStatusList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//
BOOL  bNetMcViewPcEventLogList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcOsUsrList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcNetStatList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcProcessPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcProcessModulePropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcProcessRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcNetFlowPropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcNetFlowPropList_ethernet(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bNetMcViewPcNetSharePropList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//  BOOL  bNetMcViewPcAutoLogonList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
//
BOOL  bViewAllOpEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bViewAllEventList(  QY_OBJ_DB  *  pObjDb  );

//
BOOL  bViewAllPcEventList_netMc(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewAllNetDevEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewRasEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewDevChangedEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewQwmDelEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewIntraConnEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewOnInternetEventList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewProxyServerEventList(  QY_OBJ_DB  *  pObjDb  );

BOOL  bNetMcViewNetwork(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewUsrConnection(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewSwitchFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart,  char  *  selectedSwitchMac,  char  *  selectedMac  );
BOOL  bNetMcViewNetworkSpeed(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewSnmpObjRuleList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewConflictConnList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewDirectConnList(  QY_OBJ_DB  *  pObjDb  );
BOOL  bNetMcViewAssets(  QY_OBJ_DB  *  pObjDb  );	
//
int  showCfgView(  void  *  p0,  void  *  p1,  void  *  pbStop  );
//  BOOL  bNetMcCfgSp(  );
BOOL  bNetMcCfgPcProcessKnowledge(  LPCTSTR  wherePart  );
BOOL  bNetMcCfgPcRegistryKnowledge(  LPCTSTR  wherePart  );
	

BOOL  bImportKnowledge(  unsigned  int  uiType  );
BOOL  bExportKnowledge(  unsigned  int  uiType  );
BOOL  bClearupKnowledge(  unsigned  int  uiType  );


__declspec(  dllexport  )  BOOL  bClearupScannedIp_netMc(  QY_CLEARUPINFO  *  pClearupInfo  );				  
__declspec(  dllexport  )  BOOL  bClearupEvent(  QY_CLEARUPINFO  *  pClearupInfo  );
//  BOOL  bClearupImMsg(  QY_CLEARUPINFO  *  pClearupInfo  );
//  BOOL  bClearupImHisTask(  QY_CLEARUPINFO  *  pClearupInfo  );
//  BOOL  bClearupImMsg(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  );

int  setQueryColumns(  void  *  p0,  QNM_QUERY_STRUCT  *  pQueryStruct,  QY_MC_QUERY  *  pQuery  );
__declspec(  dllexport  )  void  *  displayQnmElement(  void * pVoid,  void  *  pQueryParam,  void  *  pQyRcdset,  int  nSubItem,  TCHAR * output,  unsigned  int  cchSize  );


BOOL  bViewAllProcedObjs(  QY_MC  *  pQyMc,  void  *  p1,  void  *  p2  );	//  2006/12/24
BOOL  bNetMcMonIfFlow(  QY_MC  *  pQyMc,  char  *  switchMac,  int  iPortIfIndex  );


int  getLvSelColContent(  HWND  hWnd,  int  *  pCurnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  );
int  delAllPcInfo(  void  *  pDb,  LPCTSTR  hint,  char  *  mac0  );

int  netMc_procEvent(  void  *  pQyMc,  void  *  pDoc,  void  *  pEventInfoParam  );
int  is_procEvent_new(  void  *  pQyMcParam,  void  *  pm_docStruct,  void  *  pEventInfoParam  );

int  netMc_procMcViewEvent(  void  *  pQyMc,  void  *  pSel,  void  *  pEventInfoParam  );
int  netMc_procTreeEvent(  void  *  pQyMc,  void  *  pSel,  void  *  pEventInfoParam  );
int  netMc_procTreeSel(  void  *  pQyMcParam,  void  *  p0,  void  *  p1  );
int  netMc_procLvDblClick(  void  *  pQyMcParam,  void  *  pCurSelParam,  void  *  pEventInfoParam  );

int  netMc_procLvEventFunc(  void  *  pQyMcParam,  void  *  pDocParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  );
int  is_procLvEventFunc_new(  void  *  pQyMcParam,  void  *  pm_DocStructParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  );

int  mc_procTvEventFunc(  void  *  pQyMcParam,  void  *  pDocParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  );
//
int  guiDoSnmpOpCmd(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  char  *  switchMac,  int  iPortIfIndex,  char  *  mac,  char  *  ip,  int  iSnmpOpCmd,  char  *  param  );
int  dblClickToOpenItem(  void  *  pQyMcParam,  void  *  pCurSelParam,  void  *  pEventInfoParam  );

//  int  getLvTypeFromSth(  void  *  pDocParam,  void  *  pSelParam,  TCHAR  *  colName,  unsigned  int  colNameCnt,  PF_commonHandler  *  ppfProcCmd  );
int  getLvTypeFromSth_new(  void  *  pm_DocStructParam,  void  *  pSelParam,  TCHAR  *  colName,  unsigned  int  colNameCnt,  PF_commonHandler  *  ppfProcCmd  );
//
int  enumLvSelEventFunc(  QY_EVENTINFO  *  pEventInfo,  PF_procLvEventFunc  pf,  void  *  pObjDb,  int  iLvType,  void  *  pParam  );
int  getLvColContent(  HWND  hParent,  HWND  hList,  int  curnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  );
int  getKeyNameByLvType(  int  iLvType,  TCHAR  *  colName,  unsigned  int  colNameCnt  );


QY_OBJ_DB  *  getObjDbFromSel(  QY_MC_SEL  *  pSel  );
int  getSelIdFromLv(  HWND  hParent,  int  *  pId  );


BOOL  bQnmFillCol0(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  sqlStr,  HWND  hCombo,  BOOL  bFillAny  );
BOOL  bQnmFillCol0FromTable(  QY_DMITEM  *  pTable,  HWND  hCombo,  BOOL  bFillAny  );	//  2005/01/28
extern  "C"  int  qnmFillColInfo(  int  iType,  LPCTSTR  sqlColName,  int  iSqlDataType,  int  iDisplayType,  LPCTSTR  displayColName,  int  nWidth,  QY_COLUMNINFO  *  pSqlCol,  QY_COLUMNINFO  *  pDisplayCol  );
int  myMakeTime(  SYSTEMTIME  *  pDate,  SYSTEMTIME  *  pTime,  SYSTEMTIME  *  pT  );
BOOL  bMyTimeInOrder(  SYSTEMTIME  *  pStart,  SYSTEMTIME  *  pEnd  );
#ifndef  __noMfc__
#ifdef  __isCli__
		__declspec(  dllexport  )  int  qnmGetInputTime(  CWnd  *  pWndStartDate,  CWnd  *  pWndStartTime,  CWnd  *  pWndEndDate,  CWnd  *  pWndEndTime,  char  *  startBuf,  unsigned  int  startBufSize,  char  *  endBuf,  unsigned  int  endBufSize  );

#else
		 int  qnmGetInputTime(  CWnd  *  pWndStartDate,  CWnd  *  pWndStartTime,  CWnd  *  pWndEndDate,  CWnd  *  pWndEndTime,  char  *  startBuf,  unsigned  int  startBufSize,  char  *  endBuf,  unsigned  int  endBufSize  );
#endif
#endif
BOOL  bSetCusName(  void  *  pDb,  int  iDbType,  int  id,  QY_CUSNAME_RCD  *  pCusName,  BOOL  *  pbChanged  );
BOOL  bSetStandardRegInfo(  void  *  pDb,  int  iDbType,  QY_CUSNAME_RCD  *  pCusName  );


int  getSnmpObjImages(  QY_MC  *  pQyMc,  QY_SNMPOBJ_HEAD  *  pObj,  int  *  pnImage,  int  *  pnSelectedImage  );
int  getSnmpPortImages(  QY_MC  *  pQyMc,  QY_SWITCHPORT_RCD  *  pPort,  int  *  pnImage,  int  *  pnSelectedImage  );

TCHAR  *  getIifStr_i(  char  *  dbTypeName,  TCHAR  *  colName,  int  iWhenVal,  int  iTrueVal,  int  iFalseVal,  TCHAR  *  output,  unsigned  int  size  );
TCHAR  *  getIifStr_s(  char  *  dbTypeName,  TCHAR  *  cond,  TCHAR  *  trueVal,  TCHAR  *  falseVal,  TCHAR  *  output,  unsigned  int  size  );

BOOL  bGetMacDesByMac(  void  *  pDbParam,  char  *  mac,  QNM_MACDES_RCD  *  pMacDes  );

 typedef  struct			{	
				int			iDbType;
				TCHAR		tBuf[4096];
				//  CString		str_notused;
}							MY_DB_BUF;
int  resetMyDbBufs(  MY_DB_BUF  *  pBufs,  unsigned  int  cnt  );
#define		CONST_maxMyDbBufs		10		//  包含各种支持的数据库

void  doQnmSearch(  int  iQueryType  );
int  doQnmSearchPcSp(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  osName,  LPCTSTR  spName  );
int  doQnmSearchIp(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  tIp  );
int  doQnmSearchMac(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  tMac  );
int  doQnmSearchConnectionByMac(  QY_OBJ_DB  *  pObjDb,  char  *  mac  );


BOOL  bNetMcViewPcAssetReport(  QY_OBJ_DB  *  pObjDb,  unsigned  int  uiLangId,  unsigned  char  ucbByMac  );


__declspec(  dllexport  )  int  getObjId(  QY_OBJ_DB  *  pObjDb,  int  iUsageType,  LPCTSTR  servName,  int  iObjType,  void  *  pObjParam  );
//  int  getObjIndex(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  );


//  2005/01/23加入对tv显示的标准化
typedef  BOOL  (  *PF_bTvItemExists  )(  void  *  pDb,  void  *  pLeftView,  HANDLE  htItem  );
int  myTrimTree(  void  *  pDb,  void  *  pLeftView,  HANDLE  htItem,  PF_bTvItemExists  pfbTvItemExists  );
//
int  myAddOrRefreshTreeItem(  void  *  pLeftViewParam,  HANDLE  htItemParam,  int  iObjId,  TCHAR  *  displayName,  int  nImage,  int  nSelectedImage,  void  *  qmObjQParam  );
int  myAddOrRefreshTreeItem(  void  *  pLeftViewParam,  HANDLE  htItemParam,  int  iObjId,  TCHAR  *  displayName,  int  nImage,  int  nSelectedImage  );
//
BOOL  bRefreshMeStatus_wnd(  MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  );
BOOL  bRefreshContactsStatus_wnd(  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  );



BOOL  bGetTopParams(  int  *piTopFieldId,  int  *piTopObjType  );
BOOL  mybSetColumns(  int  iObjType,  QY_COLUMNINFO  *  pColumns,  unsigned  int  maxCnt  );

//
int  displayContent_assets(  void  *  p0,  void  *  p1,  void  *  p2  );
int  refreshItem_assets(  void  *  p0,  void  *  p1,  void  *  p2  );
int  displayListContent_assets(  void  *  p0,  void  *  p1,  void  *  p2  );




int  displayContent_cfgSp(  void  *  p0,  void  *  p1,  void  *  p2  );
int  refreshItem_cfgSp(  void  *  p0,  void  *  p1,  void  *  p2  );
int  displayListContent_cfgSp(  void  *  p0,  void  *  p1,  void  *  p2  );

int  loadProcedObj(  void  *  p0,  void  *  p1,  void  *  p2  );

 
__declspec(  dllexport  )  int  delPcSth(  void  *  pDb,  LPCTSTR  hint,  LPCTSTR  tabName,  LPCTSTR  whereClause  );
__declspec(  dllexport  )  int  delImObj(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
int  modifyImObjId(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_old,  QY_MESSENGER_ID  *  pIdInfo_new  );

__declspec(  dllexport  )  BOOL  bPcOnline(  char  *  lastCommTime  );

int  fillQyMcQuery(  QY_OBJ_DB  *  pObjDb,  int  type,  void  *  pParam,  LPCTSTR  wherePart,  QY_MC_QUERY  *  pQuery  );

extern  QY_DMITEM  CONST_fillRegInfoTable[];


#endif  /*  }  */


