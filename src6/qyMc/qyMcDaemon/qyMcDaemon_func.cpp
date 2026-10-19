
#include	"stdafx.h"
#include	"qmdCommon.h"
#include	"qyMcDaemon.h"
#include	"QyMcDaemonObj.h"
#include	"DlgPasswdForStopMon.h"

#include	"qmStr.h"
#include	"qmStatusShmProc.h"
#include	"myDb.h"

BOOL  bSelectImGrpMem_dlgTalk_OnInitDialog_odbc(  void  *  pDlgTalkParam,  void  *  pDbParam,  void  *  pParam  )
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

int  listObjs_dlgMsgList_odbc(  void  *  pDbParam,  void  *  pQueryParam,  void  *  pListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{
	return  -1;
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
 BOOL  bClearupImMsg_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
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
BOOL  bViewImMsgListFunc_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
BOOL  bStatImTasks_odbc(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
 {
	 return  FALSE;
 }
BOOL  bClearupImMsg_isCli_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
BOOL  bClearupEvent_is_odbc(  QY_CLEARUPINFO  *  pClearupInfo  )
 {
	 return  FALSE;
 }
BOOL  bClearupImMsg_odbc(  QY_CLEARUPINFO  *  pClearupInfo  )
 {
	 return  FALSE;
 }
BOOL  bClearupImHisTask_odbc(  QY_CLEARUPINFO  *  pClearupInfo  )
 {
	 return  FALSE;
 }
BOOL  bViewImObjListFunc_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
BOOL  bViewMessengerRegInfoList_odbc(  QY_OBJ_DB  *  pObjDb  )
 {
	 return  FALSE;
 }
BOOL  bViewImGrpList_odbc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
 {
	 return  FALSE;
 }
BOOL  bViewImObjRuleList_is_odbc(  QY_OBJ_DB  *  pObjDb  )
 {
	 return  FALSE;
 }
BOOL  bViewEventListFunc_is_odbc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
 {
	 return  FALSE;
 }
BOOL  bViewOpEventListFunc_is_odbc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause )
 {
	 return  FALSE;
 }

 int  getObjIndex_odbc(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  )
 {
	 return  -1;
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

//  2013/06/25
__declspec(  dllexport  )  int  listObjs_dlgMsgList_odbc(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{
	return  -1;
}

__declspec(  dllexport  )  BOOL  bSelectImGrpMem_dlgTalk_OnInitDialog_odbc(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam  )
{
	return  -1;
}

int  updateImObj_refreshImGrps_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  )
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



