

#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"
//
#include	"dlgTalkProc.h"

#include "qyMessenger_ts_noMfc.h"


 int  qisChkWalls(  )
 {
	 return  -1;
 }


 int  qnmLogOpEvent(  int  iServiceId,  QY_OBJ_DB  *  pObjDb,  int  iEventType,  LPCTSTR  des  )		//  2007/01/02
 {
	 return  -1;
 }
 int  qnmLogOpEvent(  int  iServiceId,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  dsnName,  LPCTSTR  des  )
 {
	 return  -1;
 }
 int  qnmLogOpEvent(  int  iServiceId,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  des  )
{
	 return  -1;
 }

  int  getSize_moduleExt(  )
{
	traceLog(  _T(  "getSize_moduleExt,  test_touchscreen"  )  );
	return  -1;
}

 BOOL  initModuleExt(  )
{
	traceLog(  _T(  "initModuleExt,  test_touchscreen"  )  );
	return  FALSE;
}

 void  exitModuleExt(  )
{
	traceLog(  _T(  "exitModuleExt,  test_touchscreen"  )  );
	return;
}

 BOOL  bQyMcNewQueryView(  QY_MC_SEL  *  pSel  )
 {
	 return  FALSE;
 }
 int  is_procEvent_new(  void  *  pQyMcParam,  void  *  pm_docStruct,  void  *  pEventInfoParam  )
{
	   return  -1;
}
 int  netMc_procEvent(  void  *  pQyMcParam,  void  *  pDoc,  void  *  pEventInfoParam  )
{
		return  -1;
}
  int  getLvColContent(  HWND  hParent,  HWND  hList,  int  curnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  )
{
	  return  -1;
}
int  enumLvSelEventFunc(  QY_EVENTINFO  *  pEventInfo,  PF_procLvEventFunc  pf,  void  *  pObjDb,  int  iLvType,  void  *  pParam  )
{
	  return  -1;
}

BOOL  bQyOpenMcView(  QY_MCVIEW_SEL  *  pParam,  void  *  p1,  void  *  p2  )
{
	return  FALSE;
}
void  qyMcView_delAllColumns(  void  *  pView,  void  *  p1,  void  *  p2  )
{
	  return;
}
BOOL  qyMcView_bAddColumns(  void  *  pView,  QY_COLUMNINFO * pColumns,  void  *  p2  )
{
	return  FALSE;
}

int  initVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	  return  -1;
}
int  exitVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	  return  -1;
}


 extern "C" DWORD WINAPI mcThreadProc( LPVOID lpParameter )
{
	  return  0;
}
 extern "C" DWORD WINAPI mcThreadProc_isMgr( LPVOID lpParameter )
{
	  return  0;
}
   //
 unsigned  int  getVarSize_netMc(  void  *  pQyMc  )
   {
	   return  -1;
   }
 int  initVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  )
   {
	   return  -1;
   }
 int  exitVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  )
   {
	   return  -1;
   }

  int  getCustomComm(  QNM_CUSTOM_COMM  *  pCustom  )
{
return  -1;
}
int  viewDlgShareDynBmps_isCli(  BOOL  bNeed_shareWebcamInConference  )
{
	traceLog(  _T(  "shareDynBmps_isClient not supported"  )  );
	return  -1;
}


int  viewWallsMenu(  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  BOOL  bNoDelayToView,  RECT  *  pRect_zone,  void  *  pVwRuleU  )
{
#ifdef  __DEBUG__
	traceLog(  _T(  "viewWallsMenu: not supported"  )  );
#endif
	return  0;
}

int  netMc_procTreeEvent(  void  *  pQyMcParam,  void  *  pSel,  void  *  pEventInfoParam  )
  {
	  traceLog(  _T(  "Not supported: netMc_procTreeEvent"  )  );
	  return  -1;
  }

	    BOOL  bGetPhoneGuestRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  int  id,  PHONE_GUEST_RCD  *  pRcd  )
{
	return  FALSE;
}
 void  clearShiftKeys()
{
	traceLog(  _T(  "clearShiftKeys,  test_touchscreen"  )  );
	return;
}
   QYMC_HOTKEY	gHotKeys_main[] = 
{
	//  {  ID_HKF5, 0, VK_F5, 0  },		//  不要热键了，不方便, 容易和别的软件冲突
	//  {  ID_HKF6, 0, VK_F6, 0  },
	//  {  ID_HKF7, 0, VK_F7, 0  },
	{	-1,					},
};
  BOOL  bViewImObjView_isCli_sdi(  QY_OBJ_DB  *  pObjDb  )
  {
	  return  FALSE;
  }
 int  closeOtherWnds_isMgr(  BOOL  *  pbOtherWndExists  )
{
	traceLog(  _T(  "closeOtherWnds_isMgr,  test_touchscreen"  )  );
	return  -1;
}
   BOOL  bViewImTaskListFunc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart,  BOOL  bHisTab  )
   { 
	   return  FALSE;
   }

////////////////////////
int  dlgShareDynBmps_refreshShareStatus_gps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
return  -1;
}

int  dlgShareDynBmps_refreshShareStatus(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  )
{
return  -1;
}

//  SHARE_dynBmps	*	dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  )
void  *	 dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  )
{
return  NULL;
}

LRESULT  dlgShareDynBmps_OnQyComm( HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam )
{
return  -1;
}

LRESULT  dlgShareDynBmps_OnQyPostComm( HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam )
{
return  -1;
}

int  dlgShareDynBmps_chkSharedObj(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  iIndex_sharedObj  )
{
return  -1;
}
int  dlgShareDynBmps_toShareWebcam(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  index  )
{
return  -1;
}
int  dlgShareDynBmps_toShareGps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var)
{
return  -1;
}
int  dlgShareDynBmps_closeTaskAv(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index  )
{
return  -1;
}
int  dlgShareDynBmps_chkShareGps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
return  -1;
}


//////////////////////////