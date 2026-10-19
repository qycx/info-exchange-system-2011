
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"myresource.h"

#include	"qyCusResTemp.h"
#include	"qmcVideoCapture.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
#include	"dlgDynBmpsProc.h"
//  #include	"dlgTalk.h"
#include	"dlgtalkproc.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
//  #include	"DlgQnmEditPcUsrInfo.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"


__declspec(  dllexport  )  int  doCmd_test(  int  iMenuId  )
{
	QY_MC  *  pQyMc	=	QY_GET_GBUF(  );
	QM_dbFuncs  &  g_dbFuncs  =  *QY_GET_qmDbFuncs(  );
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );

	switch  (  iMenuId  )  {
				  //
 			case  ID_qyRealTimeTaskList:
				  bViewRealTimeImTaskList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_sharingObjectList:
				  bViewSharingObjectList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_playerList:
				  bViewPlayerList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_wallList:
				  bViewWallList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_imNetStatList:
				  bViewImNetStatList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_talkerList:
				  bViewTalkerList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_messengerStatusList:
				  bViewMessengerStatusList(  pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_qList:
				  viewStatusCli(  CONST_qyWndContentType_qList,  0,  _T(  "qList"  ),  CONST_resId_qListColumns,  NULL    );
				  break;
				  //
			case  ID_myDbStatus:  //  2013/02/22
				  viewStatusCli(  CONST_qyLvType_myDbStatus,  0,  _T(  "MyDb status"  ),  CONST_resId_qListColumns,  NULL  );				  
				  break;
				  //
			case  ID_imTaskList_unproced_test:
				  g_dbFuncs.pf_bViewImTaskList_unproced(   pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;
			case  ID_imTaskList_cur_test:
				  g_dbFuncs.pf_bViewImTaskList_cur(   pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  ),  _T(  ""  )  );
				  break;
			default:
					break;
	}

	return  0;
}

#if  0  //  2013/02/17
 BOOL  bViewUnprocedNewImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet										=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	TCHAR					whereClause[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );

	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "(T.iStatus in(%d,%d,%d,%d,%d,%d,%d,%d))"  ), 
															CONST_imTaskStatus_req,
															CONST_imTaskStatus_resp,
															CONST_imTaskStatus_applyToSend,
															CONST_imTaskStatus_waitToSend,
															CONST_imTaskStatus_applyToRecv,
															CONST_imTaskStatus_waitToRecv,
															CONST_imTaskStatus_sending,
															CONST_imTaskStatus_receiving
															);
	if  (  wherePart  &&  wherePart[0]  )  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and (%s)"  ),  whereClause,  wherePart  );

	bRet  =  bViewImTaskListFunc(  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  whereClause,  FALSE  );

	return  bRet;
}
#endif

 
__declspec(  dllexport  )   void myListCtrl_delAllColumns(  HWND  hListCtrl  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )CListCtrl::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return;

	 for ( ; ; )  {
		 if  (  !pListCtrl->DeleteColumn( 0  )  )  break;
	 }
}

   __declspec(  dllexport  )  BOOL myListCtrl_bAddColumns(  HWND  hListCtrl,  QY_COLUMNINFO * pColumns  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )CListCtrl::FromHandle(  hListCtrl  );

	 if  (  !pListCtrl  )  return  FALSE;
	 if  (  !pColumns  )  return  TRUE;
	 
	 int		i;
	 LV_COLUMN	lvc;

	 lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	 for  (  i  =  0;  pColumns[i].type  !=  -1  &&  pColumns[i].label[0];  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	pColumns[i].label;
		   lvc.cx			=	pColumns[i].width;
		   lvc.fmt			=	pColumns[i].fmt;
		   pListCtrl->InsertColumn(  i,  &lvc  );
	  }
	
	 return  TRUE;
}

//	int InsertItem(_In_ const LVITEM* pItem);
//  int InsertItem(_In_ int nItem, _In_z_ LPCTSTR lpszItem);

__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->InsertItem(  nItem, lpszItem  );
}


__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem, int nImage  )
{

	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->InsertItem(  nItem, lpszItem, nImage );
}


__declspec(  dllexport  )  BOOL myListCtrl_SetItemText(  HWND  hListCtrl,  int nItem, int nSubItem, LPCTSTR lpszText)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItemText(  nItem, nSubItem, lpszText);
}


__declspec(  dllexport  )  BOOL myListCtrl_SetItemData(  HWND  hListCtrl,  int nItem, DWORD_PTR dwData  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItemData(  nItem, dwData  );
}


__declspec(  dllexport  )  BOOL  myListCtrl_DeleteAllItems(  HWND  hListCtrl  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->DeleteAllItems(  );
}

__declspec(  dllexport  )  int  myListCtrl_GetItemCount(  HWND  hListCtrl  )
{

	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->GetItemCount(   );
}

__declspec(  dllexport  )  BOOL myListCtrl_SetItemState(  HWND  hListCtrl,  int nItem, UINT nState, UINT nMask  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItemState(  nItem,  nState,  nMask  );
}

__declspec(  dllexport  )  BOOL myListCtrl_Update(  HWND  hListCtrl,  int nItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->Update(  nItem  );
}

__declspec(  dllexport  )  int  myListCtrl_GetItemText(  HWND  hListCtrl,  int nItem,  int nSubItem,  LPTSTR lpszText,  int nLen  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->GetItemText(  nItem,  nSubItem,  lpszText,  nLen  );
}

__declspec(  dllexport  )  BOOL myListCtrl_ModifyStyle(  HWND  hListCtrl,  DWORD dwRemove,   DWORD dwAdd,   UINT nFlags )
{
	//  if  (  !::IsWindow(hListCtrl)  )  return  FALSE;

	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->ModifyStyle(  dwRemove, dwAdd, nFlags  );
}

__declspec(  dllexport  )  DWORD myListCtrl_SetExtendedStyle(  HWND  hListCtrl,  DWORD dwNewStyle)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->SetExtendedStyle(  dwNewStyle  );
}

__declspec(  dllexport  )  void  *  myListCtrl_SetImageList(  HWND  hListCtrl,  void  * pImageList,  int nImageList)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  NULL;

	return  pListCtrl->SetImageList(  (  CImageList  *  )pImageList,  nImageList  );
}

__declspec(  dllexport  )  int  myListCtrl_InsertColumn(  HWND  hListCtrl,  int nCol,  const LVCOLUMN* pColumn)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->InsertColumn(  nCol,  pColumn  );
}
__declspec(  dllexport  )  BOOL myListCtrl_GetColumn(  HWND  hListCtrl,  int nCol, LVCOLUMN* pColumn  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->GetColumn(  nCol,  pColumn  );
}

__declspec(  dllexport  )  int  myListCtrl_FindItem(  HWND  hListCtrl,  LVFINDINFO* pFindInfo, int nStart  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->FindItem(  pFindInfo,  nStart  );
}

__declspec(  dllexport  )  BOOL myListCtrl_GetItem(  HWND  hListCtrl,  LVITEM* pItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->GetItem(  pItem  );
}
__declspec(  dllexport  )  BOOL myListCtrl_SetItem(  HWND  hListCtrl,  LVITEM* pItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItem(  pItem  );
}



///////////////////////////////////////////////////
__declspec(  dllexport  )  BOOL myImageList_Create(  void  *  pImageList,  UINT nBitmapID, int cx, int nGrow, COLORREF crMask  )
{
	if  (  !pImageList  )  return  FALSE;

	return  (  (  CImageList  *  )pImageList  )->Create( nBitmapID,  cx,  nGrow,  crMask );
}

__declspec(  dllexport  )  BOOL myImageList_DeleteImageList(  void  *  pImageList  )
{
	if  (  !pImageList  )  return  FALSE;

	return  (  (  CImageList  *  )pImageList  )->DeleteImageList(  );
}

//////////////////////////////////////////////////

    int  snprintRoute(  ROUTE_sendLocalAv  *  pRoute,  TCHAR  *  tOutput,  unsigned  int  cnt  )
{						  
	int		j;
	TCHAR	tBuf[512]	=	_T(  ""  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Destination:"  )  );
	if  (  pRoute->videoConference_idInfo_to.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s group %I64u"  ),  tBuf,  pRoute->videoConference_idInfo_to.ui64Id  );
	else  {
		   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRoute->route.idInfo_to.ui64Id  );
		   if  (  pRoute->route.idInfo_to.ui64Id  )  {
			   for  (  j  =  0;  j  <  mycountof(  pRoute->route.mems_to  )  &&  pRoute->route.mems_to[j].idInfo.ui64Id;  j  ++  )  {
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %I64u"  ),  tBuf,  pRoute->route.mems_to[j].idInfo.ui64Id  );												 					
			   }
		   }
	}
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. routeId %d"  ),  tBuf,  pRoute->route.uiMsgRouteId  );

	if  (  tOutput  )  lstrcpyn(  tOutput,  tBuf,  cnt );
	return  0;
}

   
 int  tmpHandler_displayRealTimeTasks(  CListCtrl  *  pListCtrl,  int  *  piCnt,  MIS_MSGU  *  pMsgElem  )
{
	TCHAR		tBuf[512]							=	_T(  ""  );
	int			index;
	int			i									=	0;
	char		timeBuf[CONST_qyTimeLen  +  1]		=	"";
	char		displayBuf[255  +  1]				=	"";
	int			j;
	QY_MC	*	pQyMc								=	QY_GET_GBUF(  );

	if  (  !pListCtrl  ||  !piCnt  ||  !pMsgElem  )  return  -1;

	index  =  *piCnt;


	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		IM_CONTENTU		*	pContent		=	(  IM_CONTENTU  *  )pMsgElem->task.data.buf;
		MIS_CNT			*	pMisCnt			=  (  MIS_CNT  *  )pMsgElem->task.pMisCnt;
		MC_VAR_isCli		*	pProcInfo			=	NULL;
		if  (  pMisCnt  )  pProcInfo		=  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;

		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:  
				case  CONST_imCommType_transferAvReplyInfo:  {
  					  AV_TRAN_INFO  *  pAvTran  =  NULL;
					  PROC_TASK_AV  *  pTask  =  NULL;
					  QY_SHARED_OBJ	*	pSharedObj		=	NULL;		

					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  pAvTran  =  &pContent->transferAvInfo.tranInfo;
						  pTask  =  &pContent->transferAvInfo.myTask;
						  }
					  else  {
						    pAvTran  =  &pContent->transferAvReplyInfo.tranInfo;					  					  
							pTask  =  &pContent->transferAvReplyInfo.myTask;							
					  }
					  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );

					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
					  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
					  tBuf[0]  =  0;
					  if  (  pMsgElem->task.uiTaskType  )  {
						  if  (  pContent->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%sReply: "  ),  tBuf  );
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%stn_org %d."  ),  tBuf,  pContent->transferAvReplyInfo.uiTranNo_org  );
							  }
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgElem->task.uiTaskType  )  );
						  }
					  else  {
						    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );  							
					  }
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  tBuf[0]  =  0;
					  if  (  pTask->bTaskInvalid  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "INVALID!"  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s a %d, v %d"  ),  tBuf,  pAvTran->audio.uiTranNo_openAvDev,  pAvTran->video.uiTranNo_openAvDev  );
					  char	fourccStr[16];
					  //  iFourcc2Str(  pAvTran->video.vh_compress.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
					  safeStrnCpy(  pAvTran->video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pAvTran->audio.uiTranNo_openAvDev,  pAvTran->audio.ah_compress.wfx.wFormatTag,  pAvTran->audio.ah_compress.wfx.nChannels,  pAvTran->audio.ah_compress.wfx.nSamplesPerSec,  pAvTran->audio.ah_compress.wfx.wBitsPerSample,  pAvTran->audio.ah_compress.wfx.nAvgBytesPerSec  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %s, %d * %d )"  ),  tBuf,  pAvTran->video.uiTranNo_openAvDev,  CString(  fourccStr  ),   pAvTran->video.vh_compress.bih.biWidth,  pAvTran->video.vh_compress.bih.biHeight  ); 				  
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  switch  (  pMsgElem->task.uiTaskType  )  {
								  case  CONST_imTaskType_shareDynBmp:
								  case  CONST_imTaskType_viewDynBmp:
									    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, [%s, %d]"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pContent->transferAvInfo.viewDynBmp.uiObjType  ),  pContent->transferAvInfo.viewDynBmp.usIndex  );
										break;
							  default:
									  break;
						  }
					  }
					  if  (  pTask->video.usMaxFps_toShareBmp_videoConference  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, maxFps %d"  ),  tBuf,  (  int  )pTask->video.usMaxFps_toShareBmp_videoConference  );
					  }
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  audio player:"  ),  tBuf  );
					  //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, minPlaying %dms, maxPlaying %dms, notify %dms"  ),  tBuf,  pTask->audio.playCfg.uiMinTimeInMsOfAudioDataPlaying,  pTask->audio.playCfg.uiAudioDataAddedToPlayEveryTime,  pTask->audio.playCfg.uiNotifyIntervalInMs_needMoreAudioData  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pTask->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pTask->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pTask->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
					  //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, maxToPlay %dms, toBeRemoved %dms"  ),  tBuf,  pTask->audio.playCfg.uiMaxTimeInMsToPlay,  pTask->audio.playCfg.uiMaxTimeInMsToBeRemoved  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pTask->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pTask->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pTask->audio.playCfg.usMaxTimeInMsToBeRemoved  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ;	

					  getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
					  qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

					  //  2009/09/10
					  if  (  pMisCnt  &&  pProcInfo  &&  pSharedObj  )  {
						  index  ++  ;

						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
						  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						  i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						  i  ++  ;	
						  i  ++  ;	
						  /*
						  ROUTE_sendLocalAv  *  pRoute  =  &pSharedObj->curRoute_sendLocalAv;
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Destination:"  )  );
						  if  (  pRoute->videoConference_idInfo_to.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s group %I64u"  ),  tBuf,  pRoute->videoConference_idInfo_to.ui64Id  );
						  else  {
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRoute->route.idInfo_to.ui64Id  );
								if  (  pRoute->route.idInfo_to.ui64Id  )  {
									for  (  j  =  0;  j  <  mycountof(  pRoute->route.mems_to  )  &&  pRoute->route.mems_to[j].idInfo.ui64Id;  j  ++  )  {
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %I64u"  ),  tBuf,  pRoute->route.mems_to[j].idInfo.ui64Id  );												 					
									}
								}
						  }
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. routeId %d"  ),  tBuf,  pRoute->route.uiMsgRouteId  );
						  */
						  snprintRoute(  &pSharedObj->curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );
						  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  }

					  index  ++  ;
					  //
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  {
						  TASK_AV_FROM  *  pFrom  =  &pTask->mem0_from;
						  						   
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Request from: %I64u"  ),  pFrom->idInfo.ui64Id  );
						   char	fourccStr[16];
						   //  iFourcc2Str(  pFrom->video.vh_compress_recvd.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						   safeStrnCpy(  pFrom->video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pFrom->audio.uiTranNo_openAvDev,  pFrom->audio.ah_compress_recvd.wfx.wFormatTag,  pFrom->audio.ah_compress_recvd.wfx.nChannels,  pFrom->audio.ah_compress_recvd.wfx.nSamplesPerSec,  pFrom->audio.ah_compress_recvd.wfx.wBitsPerSample,  pFrom->audio.ah_compress_recvd.wfx.nAvgBytesPerSec  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %s, %d * %d, %s )"  ),  tBuf,  pFrom->video.uiTranNo_openAvDev,  CString(  fourccStr  ),   pFrom->video.vh_compress_recvd.bih.biWidth,  pFrom->video.vh_compress_recvd.bih.biHeight,  (  pFrom->video.compressor.common.ucbOutputFlippedImg  ?  _T(  "flip"  )  :  _T(  ""  )  )  ); 
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;
					  }


					  //
					  #if	1
					  for  (  j  =  0;  j  <  pTask->usCntLimit_activeMems_from;  j  ++  )  {
						   ACTIVE_taskAvFrom  *  pFrom  =  &pTask->activeMems_from[j];

						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "active %d:"  ),  j  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, from %d"  ),  tBuf,  pFrom->idInfo.ui64Id,  (  int  )pFrom->usIndex_pMems_from  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   i  ++  ;	

						   index  ++  ;
					  }


					  #endif

					  //
					  for  (  j  =  0;  j  <  pTask->usCntLimit_transforms;  j  ++  )  {
						   QY_TRANSFORM  *  pTransform  =  &pTask->pTransforms[j];

						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "trans %d:"  ),  j  );
						   if  (  pTransform->audio.bRunning  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d,%d, from %d )"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pTransform->audio.q2  ),  getQ2Nodes_toPostMsg(  &pTransform->audio.q2  ),  pTransform->audio.index_pMems_from  );
						   if  (  pTransform->video.bRunning  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d,%d, from %d )"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pTransform->video.q2  ),  getQ2Nodes_toPostMsg(  &pTransform->video.q2  ),  pTransform->video.index_pMems_from  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  a: nStep %d, elapse %dms"  ),  tBuf,  pTransform->audio.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->audio.debugStep.dwTickCnt_step_debug  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  v_pre: nStep %d, elapse %dms, iErr %d"  ),  tBuf,  pTransform->v_preTransThread.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->v_preTransThread.debugStep.dwTickCnt_step_debug,  pTransform->v_preTransThread.debugStep.iErr_thread  );	//  2012/09/07
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  v: nStep %d, elapse %dms"  ),  tBuf,  pTransform->video.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->video.debugStep.dwTickCnt_step_debug  );
						   if  (  pTransform->video.debugStep.fg.FillBuffer.nStep_debug  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, nStep_fg %d, elapse %dms"  ),  tBuf,  pTransform->video.debugStep.fg.FillBuffer.nStep_debug,  GetTickCount(  )  -  pTransform->video.debugStep.fg.FillBuffer.dwTickCnt_step_debug  );
						   }
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  errs: notAccept %d, Input %d, output %d, index %d"  ),  tBuf,  pTransform->video.debugStep.uiCnt_DMO_E_NOTACCEPTING,  pTransform->video.debugStep.nErrs_ProcessInput,  pTransform->video.debugStep.nErrs_ProcessOutput,  pTransform->video.debugStep.nErrs_pOutputBuffers_index  ); 
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   i  ++  ;	

						   index  ++  ;
					  }

					  for  (  j  =  0;  j  <  pTask->usCntLimit_mems_from;  j  ++  )  {  
						   TASK_AV_FROM  *  pFrom  =  &pTask->pMems_from[j];

						   if  (  !pTask->pMems_from[j].idInfo.ui64Id  )  continue;

						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "from %d: %I64u"  ),  j,  pFrom->idInfo.ui64Id  );
						   char	fourccStr[16];
						   //  iFourcc2Str(  pFrom->video.vh_compress_recvd.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						   safeStrnCpy(  pFrom->video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pFrom->audio.uiTranNo_openAvDev,  (  int  )pFrom->audio.compressor.ucCompressors,  pFrom->audio.ah_compress_recvd.wfx.wFormatTag,  pFrom->audio.ah_compress_recvd.wfx.nChannels,  pFrom->audio.ah_compress_recvd.wfx.nSamplesPerSec,  pFrom->audio.ah_compress_recvd.wfx.wBitsPerSample,  pFrom->audio.ah_compress_recvd.wfx.nAvgBytesPerSec  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %d, %s, %d * %d, %s )"  ),  tBuf,  pFrom->video.uiTranNo_openAvDev,  (  int  )pFrom->video.compressor.common.ucCompressors,  CString(  fourccStr  ),   pFrom->video.vh_compress_recvd.bih.biWidth,  pFrom->video.vh_compress_recvd.bih.biHeight,  (  pFrom->video.compressor.common.ucbOutputFlippedImg  ?  _T(  "flip"  )  :  _T(  ""  )  )  ); 
						   //  2011/12/24
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  audio player:"  ),  tBuf  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pFrom->audio.compressor.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pFrom->audio.compressor.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pFrom->audio.compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pFrom->audio.compressor.playCfg.usMinTimeInMsToPlay,  (  int  )pFrom->audio.compressor.playCfg.usMaxTimeInMsToPlay,  (  int  )pFrom->audio.compressor.playCfg.usMaxTimeInMsToBeRemoved  );
						   //
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;

					  }

					  //  2009/09/11
					  if  (  pSharedObj  )  {
						  if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id
							  &&  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
							  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
							  i  ++  ;	
							  i  ++  ;	

							  time_t	t;	time(  &t  );
							  tBuf[0]  =  0;
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Last resp:"  )  );
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id,  (  int  )(  t  -  pSharedObj->routeInfo.tRecvTime_lastResp  )  );
							  for  (  j  =  0;  j  <  mycountof(  pSharedObj->curRoute_sendLocalAv.route.mems_to  );  j  ++  )  {
								   if  (  !pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  )  continue;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id,  (  int  )(  t  -  pSharedObj->routeInfo.mems[j].tRecvTime_lastResp  )  );  
							  }

							  i  ++  ;  pListCtrl->SetItemText(  index,  i,  tBuf  );

							  index  ++  ;
						  }
					  }

					  }
					  break;
					  
				case  CONST_imCommType_transferGpsInfo:  {
					  QY_SHARED_OBJ	*	pSharedObj	=	NULL;			

					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
					  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	

					  tBuf[0]  =  0;				
					  if  (  pMsgElem->task.uiTaskType  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgElem->task.uiTaskType  )  );
						  }
					  else  {
						    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );  													
					  }
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
			
					  tBuf[0]  =  0;							
					  if  (  pContent->transferGpsInfo.myTask.iIndex_sharedObj  )  {									
						  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pContent->transferGpsInfo.myTask.iIndex_sharedObj  );									 
					  }	
					  if  (  pSharedObj  )  {
						  snprintRoute(  &pSharedObj->curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );						
					  }									 
									 
					  //
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ;	

					  getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
					  qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

					  index  ++  ;

					  if  (  pSharedObj  )  {
						  if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id
							  &&  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
							  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
							  i  ++  ;	
							  i  ++  ;	

							  time_t	t;	time(  &t  );
							  tBuf[0]  =  0;
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Last resp:"  )  );
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id,  (  int  )(  t  -  pSharedObj->routeInfo.tRecvTime_lastResp  )  );
							  for  (  j  =  0;  j  <  mycountof(  pSharedObj->curRoute_sendLocalAv.route.mems_to  );  j  ++  )  {
								   if  (  !pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  )  continue;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id,  (  int  )(  t  -  pSharedObj->routeInfo.mems[j].tRecvTime_lastResp  )  );  
							  }

							  i  ++  ;  pListCtrl->SetItemText(  index,  i,  tBuf  );

							  index  ++  ;
						  }
					  }


					  }
					  break;

				default:
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	

						   tBuf[0]  =  0;				
						   if  (  pMsgElem->task.uiTaskType  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgElem->task.uiTaskType  )  );
							  }
						   else  {
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );  							
						   }
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   tBuf[0]  =  0;
						   if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s fileLen %I64u"  ),  tBuf,  pContent->transferFileReq.ui64FileLen  );
						   else  if  (  pContent->uiType  ==  CONST_imCommType_transferFileReplyReq  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s fileLen %I64u"  ),  tBuf,  pContent->transferFileReplyReq.ui64FileLen  );
						   else  {
							     ;								 
						   }
						   //
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;

						   break;
		}

	}

	(  *piCnt  )  =  index  ;

	return  0;
}

//


  //  BOOL  bDisplayMcViewContent_realTimeImTasks(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
BOOL  bDisplayMcViewContent_realTimeImTasks(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 //  CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 if  (  !pListCtrl  )  return  FALSE;
	 CListCtrl						&	ListCtrl				=			*pListCtrl;

	 //  int								i;
	 //  QY_OBJ_DB						*	pObj;
	 //  char								buf[256];
	 int								cnt						=			0;


	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_realTimeImTaskViewTable  )  )  )  goto  errLabel;

	 ListCtrl.DeleteAllItems(  );

	 pProcInfo->processQ_media.qTraverse(  (  PF_commonHandler  )tmpHandler_displayRealTimeTasks,  &ListCtrl,  &cnt  );
	 pProcInfo->processQ_robot.qTraverse(  (  PF_commonHandler  )tmpHandler_displayRealTimeTasks,  &ListCtrl,  &cnt  );


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

  BOOL  bViewRealTimeImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewRealTimeImTaskList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_realTimeImTasks;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyRealTimeTaskList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_realTimeImTaskList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyRealTimeTaskList  ),  CONST_resId_realTimeImTaskViewTable,  (  PF_commonHandler  )bDisplayMcViewContent_realTimeImTasks  );    

	traceLogA(  "bViewRealTimeImTaskList leaves."  );

	return  bRet;
}

     //  BOOL  bDisplayMcViewContent_sharingObjects(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
 BOOL  bDisplayMcViewContent_sharingObjects(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
 {
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i,  j;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_sharingObjectListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		  QY_SHARED_OBJ				*	pSharedObj	=	&pProcInfo->pSharedObjs[i];

		  if  (  !i  )  {
			  if  (  !pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  &&  !pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  )  continue;
			  }
		  else  {
			    if  (  !pSharedObj->bUsed  )  continue;
		  }

		  for  (  j  =  0;  j  <  mycountof(  pSharedObj->usrs  );  j  ++  )  {
			   SHARED_OBJ_USR	*	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  j  );

			   if  (  j  )  {
				   if  (  !IsWindow(  pSharedObjUsr->hWnd_starter  )  )  continue;
			   }

			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, %d"  ),  i,  j  );
			   index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pSharedObjUsr->iTaskId  );
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   if  (  j  ==  pSharedObj->iIndex_curUsr  )  {
				   snprintRoute(  &pSharedObj->route_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );
				   if  (  memcmp(  &pSharedObj->route_sendLocalAv,  &pSharedObj->curRoute_sendLocalAv,  sizeof(  pSharedObj->route_sendLocalAv  )  )  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | "  ),  tBuf  );
					   snprintRoute(  &pSharedObj->curRoute_sendLocalAv,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
				   }
				   }
			   else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Destination: %I64u"  ),  pSharedObjUsr->idInfo_to.ui64Id  );
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   //  if  (  j  ==  pSharedObj->iIndex_curUsr  )  
			   {
				   CAP_procInfo_audioU	*	pCapAudio  =  getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
				   if  (  pCapAudio  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s a: %d."  ),  tBuf,  pSharedObjUsr->uiTranNo_openAvDev_a  );
				   }
				   CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
				   if  (  pCapBmp  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s v: %d, fps: max %d, min %d, cur %d. input %d, toSend %d, sending %.2f."  ),  tBuf,  pSharedObjUsr->uiTranNo_openAvDev_v,  pCapBmp->common.compressVideo.compressor.common.usMaxFps_toShareBmp,  pCapBmp->common.compressVideo.compressor.common.usMinFps_toShareBmp,  pCapBmp->common.compressVideo.usFrames_perSecond_expected,  (  int  )pCapBmp->common.compressVideo.input.usFps,  (  int  )pCapBmp->common.compressVideo.usFps_toSend,  pCapBmp->common.compressVideo.fFps_sending  );
					   if  (  pCapBmp->common.compressVideo.compressor.common.ucSeconds_perFrame  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s spf: %ds."  ),  tBuf,  (  int  )pCapBmp->common.compressVideo.compressor.common.ucSeconds_perFrame  );
				   }
			   }
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   if  (  j  ==  pSharedObj->iIndex_curUsr  )  {
				   if  (  !pSharedObjUsr->ucbNotSendData  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sending"  )  );
			   }
			   //  2010/12/28			   				 
			   CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
			   if  (  pCapBmp  )  {
				   char  timeBuf[32];
				   getTimelStr(  pCapBmp->common.compressVideo.debugInfo.tStart,  timeBuf,  mycountof(  timeBuf  )  );
				   getTimelStr(  pCapBmp->common.compressVideo.input.tStartTran,  timeBuf,  mycountof(  timeBuf  )  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, tLast_vCap %s"  ),  tBuf,  CString(  timeBuf  )  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, nStep %d"  ),  tBuf,  pCapBmp->common.compressVideo.debugInfo.nStep  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, nStep_progress %d"  ),  tBuf,  pProcInfo->debugInfo.nStep_progress  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, tStart %s"  ),  tBuf,  CString(  timeBuf  )  );
			   }
			   //
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   QM_SHM_CMD	*	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
			   if  (  pShmCmd  )  {
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pShmCmd->path  );
			   }
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );


			   cnt  ++  ;
		  }

	 }
	 bRet  =  TRUE;

errLabel:
	 return  bRet;
 }

  BOOL  	bViewSharingObjectList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewSharingObjectList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_sharingObjects;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharingObjectList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_sharingObjectList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharingObjectList  ),  CONST_resId_sharingObjectListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_sharingObjects  );     

	traceLogA(  "bViewSharingObjectList leaves."  );

	return  bRet;

}

    //  BOOL  bDisplayMcViewContent_players(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
  BOOL  bDisplayMcViewContent_players(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 if  (  !pListCtrl  )  return  FALSE;
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );
	 int								nWaitingInMs			=			0;

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_playerListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );


	 //
	 DWORD	dwTickCnt_now  =  GetTickCount(  );

	 //
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  QY_PLAYER				*	pPlayer	=	&pProcInfo->av.pPlayers[i];

		  if  (  !pPlayer->idInfo_recorder.ui64Id  &&  !pPlayer->audio.uiTranNo  &&  !pPlayer->video.uiTranNo  )  continue;
		  if  (  !pPlayer->audio.bRunning  &&  !pPlayer->video.bRunning  )  continue;

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );
		 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pPlayer->iTaskId  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pPlayer->idInfo_recorder.ui64Id  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 pFuncs->pf_getTalkerDesc(  pMisCnt,  &pPlayer->idInfo_recorder,  tBuf,  mycountof(  tBuf  ),  NULL,  0  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d"  ),  pPlayer->audio.uiTranNo,  pPlayer->video.uiTranNo  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 tBuf[0]  =  0;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( %d,%d,%d )"  ),  tBuf,  (  int  )pPlayer->audio.ah.wfx.nChannels,  pPlayer->audio.ah.wfx.nSamplesPerSec,  (  int  )pPlayer->audio.ah.wfx.wBitsPerSample  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( %d,%d,%d, %s )"  ),  tBuf,  pPlayer->video.vh.bih.biWidth,  pPlayer->video.vh.bih.biHeight,  pPlayer->video.vh.bih.biSizeImage,  pPlayer->video.ucbFlippedImg  ?  _T(  "flip"  )  :  _T(  ""  )  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );


		 //
		 tBuf[0]  =  0;
		 if  (  pPlayer->audio.bRunning  )  {
			 nWaitingInMs  =  MACRO_getnWaitingInMs_audio_syncRecv(  pPlayer->audio,  dwTickCnt_now  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "audio playing: "  )  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  ),  getQ2Nodes_toPostMsg(  &pPlayer->audio.q2  )  );  
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms"  ),  tBuf,  pPlayer->audio.m_var.uiSampleTimeInMs  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms waiting."  ),  tBuf,  nWaitingInMs  );		 
		 }
		 if  (  pPlayer->video.bRunning  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, video playing: "  ),  tBuf  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pPlayer->video.q2  ),  getQ2Nodes_toPostMsg(  &pPlayer->video.q2  )  );		 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms"  ),  tBuf,  pPlayer->video.m_var.uiSampleTimeInMs  );	 
		 }
		 if  (  pPlayer->audio.bRunning  )  {
			 #if  0
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | minPlaying %dms, addedEveryTime %dms, notify %dms"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pPlayer->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, minToPlay %dms, maxToPlay %dms, toBeRemoved %dms"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
			 #endif
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pPlayer->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );				
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %s"  ),  tBuf,  pPlayer->audio.playbackDevDesc  );
		 }
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		 
		 cnt  ++  ;

	 }

	 PLAY_AUDIO_procInfo  *  p  =  &pProcInfo->av.localAv.player.audio;
	 QY_PLAYER				*	pPlayer  =  &pProcInfo->av.localAv.player;

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 lstrcpyn(  tBuf,  _T(  "Local player"  ),  mycountof(  tBuf  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  p->uiTranNo  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d,%d"  ),  (  int  )p->ah.wfx.nChannels,  p->ah.wfx.nSamplesPerSec,  (  int  )p->ah.wfx.wBitsPerSample  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 tBuf[0]  =  0;
	 if  (  p->bRunning  )  {
		 nWaitingInMs  =  MACRO_getnWaitingInMs_audio_syncRecv(  pPlayer->audio,  dwTickCnt_now  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "audio playing: "  )  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  ),  getQ2Nodes_toPostMsg(  &pPlayer->audio.q2  )  );  
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms"  ),  tBuf,  pPlayer->audio.m_var.uiSampleTimeInMs  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms waiting."  ),  tBuf,  nWaitingInMs  );		 
	 }
#if  0
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, video: %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pQyMc->gui.guiQ2  ),  getQ2Nodes_toPostMsg(  &pQyMc->gui.guiQ2  )  );
#endif
	 if  (  p->bRunning  )  {			
		 //
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pPlayer->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );				
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %s"  ),  tBuf,  pPlayer->audio.playbackDevDesc  );
	 }
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		 
	 cnt  ++  ;

	 //
	 {
		 CAP_procInfo_video  *  p  =  &pProcInfo->av.localAv.videoCaptureProcInfo;

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 lstrcpyn(  tBuf,  _T(  "Local video capture"  ),  mycountof(  tBuf  )  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  p->compressVideo.uiTranNo_openAvDev_org  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "maxFps %d, minFps %d, curFps %d"  ),  p->compressVideo.compressor.common.usMaxFps_toShareBmp,  p->compressVideo.compressor.common.usMinFps_toShareBmp,  p->compressVideo.usFrames_perSecond_expected  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  p->bCaptureStarted  ?  _T(  "Capturing"  )  :  _T(  ""  )  );
		 
		 cnt  ++  ;

	 }


	 CAP_procInfo_recordSound  *  pRecordSoundProcInfo  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 lstrcpyn(  tBuf,  _T(  "Local sound recorder"  ),  mycountof(  tBuf  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pRecordSoundProcInfo->compressAudio.uiTranNo_openAvDev_org  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d,%d | %d  -- %d"  ),  (  int  )pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nChannels,  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nSamplesPerSec,  (  int  )pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.wBitsPerSample,  pRecordSoundProcInfo->compressAudio.compressor.uiBytesRecorded_perBlockAlign,  (  int  )pRecordSoundProcInfo->usErrors_processInput  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
	 
	 tBuf[0]  =  0;
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pRecordSoundProcInfo->capDevDesc  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pRecordSoundProcInfo->thread.bRunning  ?  _T(  "Recording"  )  :  _T(  ""  )  );
	 TCHAR  *  pT  =  _T(  ""  );
	 switch  (  pRecordSoundProcInfo->uiRecordType  )  {
			 case  CONST_recordType_dSound:
				   pT  =  _T(  "dSound"  );
				   break;
			 case  CONST_recordType_aec:
				   pT  =  _T(  "AEC"  );
				   break;
			 default:
				    pT  =  _T(  "unknown recordType"  );
					break;
	 }
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pT  );
	 if  (  pRecordSoundProcInfo->uiRecordType  ==  CONST_recordType_aec  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. (%s)"  ),  tBuf,  pRecordSoundProcInfo->aec_rendDevDesc  );
	 }
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		 
	 cnt  ++  ;





	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



  BOOL  bViewPlayerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewAudioPlayerList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_players;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_playerList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_playerList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_playerList  ),  CONST_resId_playerListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_players  );

	traceLogA(  "bViewAudioPlayerList leaves."  );

	return  bRet;
}

  
//  BOOL  bDisplayMcViewContent_walls(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
  BOOL  bDisplayMcViewContent_walls(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );
	 int								nWaitingInMs			=			0;

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_wallListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
	 
	 if  (  !pMisCnt->subWnds.usMaxCnt  ||  !pMisCnt->subWnds.pMems  )  {
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pMisCnt->subWnds.usMaxCnt;  i  ++  )  {
		  if  (  !IsWindow(  pMisCnt->subWnds.pMems[i].hWnd  )  )  continue;
		  if  (  pMisCnt->subWnds.pMems[i].iWndContentType  !=  CONST_qyWndContentType_vWall  )  continue;
		  
#if  0
		  CDlgDynBmps	*	pDlg	=	(  CDlgDynBmps  *  )CDialoglgDynBmps::FromHandle(  pMisCnt->subWnds.pMems[i].hWnd  );
		  if  (  !pDlg  )  continue;
#endif
		  HWND					hDlg  =  pMisCnt->subWnds.pMems[i].hWnd;
		  DLG_dynBmps_var	*	pVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hDlg  );
		  if  (  !pVar  )  continue;
		  DLG_dynBmps_var  &  m_var  =  *pVar;


		  //  pDlg->GetWindowText(  tBuf,  mycountof(  tBuf  )  );
		  GetWindowText(  hDlg,  tBuf,  mycountof(  tBuf  )  );
		  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

		  cnt  ++  ;

		  int  j,  k, l;
		  for  (  j  =  0;  j  <  m_var.pWall->m_var.usCnt;  j  ++  )  {
			   SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  j  );

			   Q_NODE	*	pQNode;
			   for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
				    VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;
					
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
					index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Rule"  )  );
					index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pRule->common.uiTranNo_spObj  );
					index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

					switch  (  pRule->common.uiType  )  {
							case  CONST_vwRuleType_dynBmp:

								  tBuf[0]  =  0;
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u,%s,%d"  ),  pRule->dynBmp.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pRule->dynBmp.dynBmp.uiObjType  ),  pRule->dynBmp.dynBmp.usIndex  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  break;
							case  CONST_vwRuleType_conference_imGrp:

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pRule->conference_imGrp.idInfo.ui64Id  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  break;
							case  CONST_vwRuleType_conference_imGrpMem:

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pRule->conference_imGrpMem.idInfo.ui64Id  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  break;
							default:
								    traceLogA(  "bDisplayMcViewContent_walls: unknown ruleType %d",  pRule->common.uiType  );
									break;
					}

					cnt  ++  ;
			   }

			   for  (  k  =  0;  k  <  pSubWall->usCnt;  k  ++  )  {

				    if  (  !pSubWall->mems[k].images.usCnt  )  {

						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
						 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Zone"  )  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: %d,%d"  ),  pSubWall->mems[k].uiTranNo_spObj,  j,  k  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 cnt  ++  ;
						 continue;
					}

				    for  (  l  =  0;  l  <  mycountof(  pSubWall->mems[k].images.mems  );  l  ++  )  {
						 CAP_IMAGE	*	pImg	=	&pSubWall->mems[k].images.mems[l];

						 if  (  !pImg->iW_org  &&  !pImg->iH_org  )  continue;

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
						 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Zone"  )  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

		
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: %d,%d, %d"  ),  pSubWall->mems[k].uiTranNo_spObj,  j,  k,  l  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pImg->iTaskId  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u,%d,%d"  ),  pImg->idInfo_sender.ui64Id,  pImg->uiTranNo_openAvDev,  pImg->usIndex  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 cnt  ++  ;
					}
			   }
		  }

	 }
	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

  BOOL  bViewWallList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewWallList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_walls;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_redId_wallList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_wallList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_redId_wallList  ),  CONST_resId_wallListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_walls  );

	traceLogA(  "bViewWallList leaves."  );

	return  bRet;
}




//    BOOL  bDisplayMcViewContent_imNetStatList(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
  BOOL  bDisplayMcViewContent_imNetStatList(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imNetStatListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 for  (  i  =  0;  i  <  mycountof(  pMisCnt->channels  );  i  ++  )  {
		  MIS_CHANNEL  *  pChannel  =  &pMisCnt->channels[i];

		  if  (  !pChannel->uiType  )  continue;

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );				
		  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u bytes"  ),  pChannel->status.netStat.ui64MsgDataLenRecvd  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u bytes"  ),  pChannel->status.netStat.ui64MsgDataLenSent  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%dkbps"  ),  pChannel->status.netStat.uiInSpeedInKbps  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%dkbps"  ),  pChannel->status.netStat.uiOutSpeedInKbps  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  cnt  ++  ;

	 }


	 
	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 BOOL  bViewImNetStatList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewImNetStatList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_imNetStatList;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_redId_imNetStatList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_imNetStatList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_redId_imNetStatList  ),  CONST_resId_imNetStatListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_imNetStatList  );

	traceLogA(  "bViewImNetStatList leaves."  );

	return  bRet;
}


  int  tmpHandler_displayTalker(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  )
{
	 int					iErr				=	-1;
	 //  p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )pCommonParam1Param;
	 MIS_CNT			*	pMisCnt				=	(  MIS_CNT  *  )pCommonParam1->p0;
	 CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )pCommonParam1->p1;
	 int				*	piCnt				=	(  int  *  )pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 int					index;
	 TCHAR								tBuf[256];

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 HWND			hDlgTalk  =  pMsg->talkingFriend_qmc.hWnd;
		 //  CDlgTalk	*	pDlg	=	(  CDlgTalk  *  )CWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
		 DLG_talk_var  *  pDlgTalkVar  =  (  DLG_talk_var  *  )getDlgTalkVar(  hDlgTalk  );
		 if  (  !pDlgTalkVar  )  goto  errLabel;
		 DLG_talk_var  &  m_var  =  *pDlgTalkVar;


		 printQ_mis(  m_var.m_pProcessQ,  FALSE  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, tn_shadow %d"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  );
		 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	

		 index  ++  ;
		 index  ++  ;
		 GetWindowText(  hDlgTalk,  tBuf,  mycountof(  tBuf  )  );
		 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
		 tBuf[0]  =  0;
		 if  (  m_var.ucbTmpMsgr  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Tmp."  )  );
		 if  (  m_var.m_pProcessQ  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s qNodes %d."  ),  tBuf,  m_var.m_pProcessQ->uiQNodes  );
		 }
		 if  (  m_var.vwRuleCmd.ucbViewScreen  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewScreen"  ),  tBuf  );					//  2012/04/25
		 if  (  m_var.vwRuleCmd.ucbViewWebcam0  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewWebcam0"  ),  tBuf  );					//  2012/04/25
		 if  (  m_var.vwRuleCmd.ucbViewWebcam1  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewWebcam1"  ),  tBuf  );					//  2012/04/25
		 if  (  m_var.vwRuleCmd.ucbViewWebcam2  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewWebcam2"  ),  tBuf  );					//  2012/04/25
		 if  (  m_var.vwRuleCmd.ucbViewGps  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewGps"  ),  tBuf  );					//  2012/04/25
		 if  (  !IsWindowVisible(  hDlgTalk  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s invisible"  ),  tBuf  );

		 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

		 (  *piCnt  )  ++  ;

		 //  2012/05/06
		 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			 if  (  pShadowMgr  &&  m_var.vwRuleCmd.ucbViewGps  )  {
				 tBuf[0]  =  0;		
				 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
				 index  ++  ;
				 index  ++  ;
				 index  ++  ;
				 gps_DisplayStr(  &pShadowMgr->viewGps.gpsPos,  tBuf,  mycountof(  tBuf  )  );
				 if  (  pShadowMgr->viewGps.dwTickCnt_lastRecvd  )  {
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. -%dms"  ),  tBuf,  GetTickCount(  )  -  pShadowMgr->viewGps.dwTickCnt_lastRecvd  );
				 }
				 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

				 (  *piCnt  )  ++  ;
			 }
			 }			 
		 else  {
			   TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
			   if  (  pShadow  )  {
				   if  (  pShadow->viewGps.dwTickCnt_lastRefreshed  )  {
				   
					   tBuf[0]  =  0;		
					   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   tBuf[0]  =  0;
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "gps -> (%d,%d) -> (%d,%d). -%dms"  ),  pShadow->viewGps.point_xy.x,  pShadow->viewGps.point_xy.y,  pShadow->viewGps.point.x,  pShadow->viewGps.point.y,  GetTickCount(  )  -  pShadow->viewGps.dwTickCnt_lastRefreshed  );  
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   (  *piCnt  )  ++  ;
				   }				   			   
			   }
		 }

		 if  (  m_var.m_pProcessQ  )  {
			 Q_NODE	*	pQNode;
			 for  (  pQNode  =  m_var.m_pProcessQ->front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {			 
				   pMsg	=  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;

				   tBuf[0]  =  0;		
				   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	

				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
				   index  ++  ;  pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

				   switch  (  pMsg->uiType  )  {
						   case  CONST_misMsgType_task:
						
							     _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pMsg->task.iTaskId  );
								 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

								 index  ++  ;

								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsg->task.iStatus  )  );
								 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

								 break;
						   default:
								  break;			  
				   }

				   (  *piCnt  )  ++  ;
				   continue;
			 } 
		 }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


//   BOOL  bDisplayMcViewContent_talkerList(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
   BOOL  bDisplayMcViewContent_talkerList(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 int								cnt						=			0;
	 //  int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_talkerListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 COMMON_PARAM	commonParam;
	 MACRO_makeCommonParam3(  pMisCnt,  pListCtrl,  &cnt,  commonParam  );
	 qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_displayTalker,  0,  &commonParam  );
 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 BOOL  bViewTalkerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewTalkerList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_talkerList;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_talkerList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_talkerList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_talkerList  ),  CONST_resId_talkerListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_talkerList  );

	traceLogA(  "bViewTalkerList leaves."  );

	return  bRet;
}



 int  tmpHandler_displayMessengerStatus(  int  *  pCnt,  CListCtrl  *  pListCtrl,  QM_OBJQ_MEM	*	pQMem  )
{
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	TCHAR						tBuf[256];
	int							index;

	QMEM_MESSENGER_CLI		*	pQMemObj	=  (  QMEM_MESSENGER_CLI  *  )pQMem->pQMemObj;
	int						&	cnt			=	*pCnt;

	QY_DMITEM				*	pTable		=  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d?%s, %I64u"  ),  cnt, qyGetDesByType1(  pTable,  pQMemObj->uiType  ),  pQMemObj->idInfo.ui64Id  );
	index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

	tBuf[0]  =  0;

	if  (  pQMemObj->uiType  ==  CONST_objType_me  )  {
		MIS_CNT	*	pMisCnt  =  getMisCntByName(  0,  0,  _T(  ""  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, wall: %I64u, %d, %d"  ),  tBuf,  pMisCnt->imRules.conferenceId_shareWebcam.ui64Id,  (  int  )pMisCnt->imRules.ucbNoLocalVideoInThisConference,  (  int  )pMisCnt->imRules.ucbDistinguishSharedWebcams  ); 
	}

	//
	if  (  pQMemObj->rules.uiCmd_autoAnswer_av  )  {
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, av: %s"  ),  tBuf,  qyGetDesByType1(  pTable,  pQMemObj->rules.uiCmd_autoAnswer_av  )  );
	}
	if  (  pQMemObj->rules.uiCmd_autoAnswer_screen  )  {
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, screen: %s"  ),  tBuf,  qyGetDesByType1(  pTable,  pQMemObj->rules.uiCmd_autoAnswer_screen  )  );
	}
	if  (  pQMemObj->rules.uiCmd_autoAnswer_mediaFile  )  {
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, mediaFile: %s"  ),  tBuf,  qyGetDesByType1(  pTable,  pQMemObj->rules.uiCmd_autoAnswer_mediaFile  )  );
	}

	index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
	 
	cnt  ++  ;

	return  0;
 }

//  BOOL  bDisplayMcViewContent_messengerStatus(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
   BOOL  bDisplayMcViewContent_messengerStatus(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  int								i;
	 //  QY_OBJ_DB						*	pObj;
	 //  char								buf[256];
	 int								cnt						=			0;


	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_messengerStatusColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 MIS_CNT	*	pMisCnt	=	getMisCntByName(  0,  0,  _T(  ""  )  );
	 
	 qmObjQTraverse(  pSgi,  pMisCnt->pObjQ,  (  PF_commonHandler  )tmpHandler_displayMessengerStatus,  &cnt,  pListCtrl  );


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 BOOL  bViewMessengerStatusList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewMessengerStatusList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_anyObjList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_messengerStatus;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_messengerStatusList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_messengerStatusList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_messengerStatusList  ),  CONST_resId_messengerStatusColumns,  (  PF_commonHandler  )bDisplayMcViewContent_messengerStatus  );


	traceLogA(  "bViewMessengerStatusList leaves."  );

	return  bRet;
}


