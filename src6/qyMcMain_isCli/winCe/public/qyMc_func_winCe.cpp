
#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"
#ifndef  __WINCE__
#include	"dlgVideos.h"
#endif
#include	"dlgTalkProc.h"

#if  0
#ifndef  __TEST__
 extern  "C"  int * _errno(void)
{
	static  int  iErrNo	=	0;

	return  &iErrNo;
}
#endif
#endif


  QYMC_HOTKEY	gHotKeys_main[] = 
{
	//  {  ID_HKF5, 0, VK_F5, 0  },		//  不要热键了，不方便, 容易和别的软件冲突
	//  {  ID_HKF6, 0, VK_F6, 0  },
	//  {  ID_HKF7, 0, VK_F7, 0  },
	{	-1,					},
};


unsigned  int	qnmMaxPcs(  QY_LICENSE_CTX  *  pCtx  )
{
	return  0;
}

unsigned  int	qnmMaxMessengers(  QY_LICENSE_CTX  *  pCtx  )
{
	return  0;
}

 int  getPcStatusInfo(  void  *  pDb,  char  *  mac0,  QY_DMITEM  *  pFieldIdTable,  PC_STATUS_INFO  *  pInfo  )
{
	return  0;
}


#ifndef  __TEST__
 //
 BOOL DrawDibEnd(  HDRAWDIB hdd  )
 {
	 return  FALSE;
 }

 BOOL DrawDibClose(  HDRAWDIB hdd  )
 {
	 return  FALSE;
 }

 HDRAWDIB DrawDibOpen(VOID)
 {
	 return  NULL;
 }

 BOOL DrawDibBegin(  HDRAWDIB hdd,  HDC hdc,  int dxDest,  int dyDest,  LPBITMAPINFOHEADER lpbi,  int dxSrc, int dySrc, UINT wFlags )
 {
	 return  FALSE;
 }

 BOOL DrawDibDraw(  HDRAWDIB hdd,  HDC hdc,  int xDst, int yDst,  int dxDst,  int dyDst,  LPBITMAPINFOHEADER lpbi, LPVOID lpBits, int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags  )
{
	 return  FALSE;
}


 //
 LRESULT ICClose(  HIC hic  )
{
	return  -1;
}

#if  0
HIC ICOpen(  DWORD fccType,  DWORD fccHandler, UINT wMode  )
{
	return  NULL;
}

HIC ICLocate(  DWORD fccType,  DWORD fccHandler, LPBITMAPINFOHEADER lpbiIn, LPBITMAPINFOHEADER lpbiOut, WORD wFlags  )
{
	return  NULL;
}

LRESULT ICGetInfo( HIC hic, ICINFO * lpicinfo, DWORD cb )
{
	return  -1;
}
#endif

#if  0
LRESULT ICSendMessage(  HIC hic, UINT wMsg, DWORD dw1, DWORD dw2  )
{
	return  -1;
}

DWORD ICDecompress(  HIC hic, DWORD dwFlags, LPBITMAPINFOHEADER lpbiFormat, LPVOID lpData, LPBITMAPINFOHEADER lpbi, LPVOID lpBits  )
{
	return  -1;
}

DWORD ICCompress(  HIC hic, DWORD dwFlags, LPBITMAPINFOHEADER lpbiOutput, LPVOID lpData, LPBITMAPINFOHEADER lpbiInput, LPVOID lpBits, LPDWORD lpckid, LPDWORD lpdwFlags, LONG lFrameNum, DWORD dwFrameSize, DWORD dwQuality, LPBITMAPINFOHEADER lpbiPrev, LPVOID lpPrev  )
{
	return  -1;
}
#endif

HWND capCreateCaptureWindow(  LPCTSTR lpszWindowName,  DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWnd, int nID  )
{
	return  NULL;
}

BOOL capGetDriverDescription( WORD wDriverIndex,  LPTSTR lpszName,  INT cbName, LPTSTR lpszVer, INT cbVer  )
{
	return  FALSE;
}


SHORT VkKeyScan(  TCHAR ch  )
{
	return  -1;
}

#endif

int  viewMediaControl(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  )
{
	return  -1;
}


 int  viewMediaControl_qmCmd(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  )
{
	return  -1;
}

 #if  0

 int  handleGraphEvent(  void  *  pShareMediaFile,  BOOL  bMediaFile,  BOOL  bLooping,  BOOL  bPlayThrough  )
{
	return  -1;
}

  int  initShareMediaFile(  LPCTSTR  tFile,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaFileParam  )
  {
	  return  -1;
  }

   int  exitShareMediaFile(  void  **  ppShareMediaFileParam  )
{
	 return  -1;
}

  int  runShareMediaFile(  void  *  pShareMediaFileParam  )
{
		return  -1;
}

   int  getShareMediaFileState(  void  *  pShareMediaFileParam  )
   {
	   return  -1;
   }

 BOOL  bNoAudio(  void  *  pSharedMediaFileParam  )
 {
	 return  FALSE;
 }
 BOOL  bAudioOnly(  void  *  pSharedMediaFileParam  )
 {
	 return  FALSE;
 }

 BOOL  bGetCapturePara_shareMediaFile(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaFile,  QY_VIDEO_HEADER  *  pVh_org,  WAVEFORMATEX  *  pWf_org,  SAMPLE_grabberCb_cache  *  pCache  )
{
	return  FALSE;
 }
#endif



 BOOL  LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette )
 {
	 return  FALSE;
 }

  int  netMc_procTreeEvent(  void  *  pQyMcParam,  void  *  pSel,  void  *  pEventInfoParam  )
  {
	  return  -1;
  }

  int  qyBrowseForFile(  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CQyString  &  fileStr  )
 {
	 traceLog(  _T(  "qyBrowseForfile not correct"  )  );

	 return  -1;
 }

 int  qyBrowseForDir(  LPCTSTR  title,  LPCTSTR  initialDir,  CQyString  &  dirStr  )
{
	return  -1;
}

	 BOOL  bGetMessengerRegInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
	 {
		 return  FALSE;
	 }


  extern  "C"  BOOL  bQyExecSql(  void  *  pDbParam,  LPCTSTR  sqlStr  )
{
	  return  FALSE;
}

#ifndef  __TEST__

   void  *  CAP_STUFF_new(  )  
   {
	   return  NULL;
   }
    void  CAP_STUFF_free(  void  *  p  )
	{
		return;
	}


   void  enumAvDevices(  void  *  pCapParam,  HWND  hWnd,  LPCTSTR  devicePath,  IMoniker  **  ppM  )
{
	traceLogA(  "enumAvDevices not ported"  );
	return;
 }

    void  addDevicesToMenu(  void  *  pCapParam,  HWND  hWnd  )
	{
		return;
	}

	 void  *  getMoniker(  void  *  pCapParam,  int  iMenuId  )
	 {
		 return  NULL;
	 }

#endif


  BOOL  bGetMessengerInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  )
  {
	  return  FALSE;
  }
 BOOL  bObjDbAvail(  QY_OBJ_DB  *  pObj  )
 {
	 return  FALSE;
 }
 extern "C" DWORD WINAPI mcThreadProc( LPVOID lpParameter )
 {
	 traceLogA(  "Not finished: mcThreadProc"  );
	 return  -1;
 }
 int  getCustomComm(  QNM_CUSTOM_COMM  *  pCustom  )
 {
	 return  -1;
 }
 extern  "C"  int  initRnbDog(  QY_LICENSE_CTX  *  pCtx  )
 {
	 return  -1;
 }
 extern  "C"  BOOL bQnmHardwareLicenseOk(  void  *  pEnvParam  )
{
	 return  FALSE;
 }
  int  updateFileMonRules(  void  *  pDb,  char  *  mac0,  PC_FILEMON_RULES  *  pInfo  )
  {
	  return  -1;
  }
int  resetDefaultFileMonRules(  void  *  pDb,  unsigned  int  uiOldChangesId,  unsigned  char  ucbMonAll,  PC_FILEMON_RULES  *  pInfo  )
{
	return  -1;
}
BOOL  bGetDefaultFileMonRules(  void  *  pDb,  PC_FILEMON_RULES  *  pInfo  )
{
	return  FALSE;
}
 extern  "C"  int  getQwmSeqNo(  char  *  seqNo,  unsigned  int  size  )
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




#ifndef  __WINCE__
 CString  getDbValStr(  int  iDbType,  int  iDataType,  LPCTSTR  val  )
{
	return  CString(  ""  );
 }
#endif


 int  recoverMessenger(  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLog,  GENERIC_Q  *  pLogQ  )
{
	return  -1;
 }

 int  logEvent_is(  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pMessengerInfo,  QIS_EVENT  *  pEvent  )
 {
	 return  -1;
 }


  void  chooseAvDevice(  void  *  pCapParam,  HWND  hWnd,  HWND  hWndStatus,  int  iMenuId  )
{
}

   BOOL  bGetImGrpInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  )
 {
	   return  FALSE;
 }

 void SHSendBackToFocusWindow(  UINT uMsg,  WPARAM wp,  LPARAM lp  )
 {
	 traceLog(  _T(  "SHSendBackToFocusWindow is not correct"  )  );
	 return;
 }

 HWND WINAPI SHFindMenuBar(  HWND hwnd )
 {
	 traceLog(  _T(  "SHFindMenuBar is not correct"  )  );
	 return  NULL;
 }


#ifndef  __WINCE__
#ifndef  __TEST__
 WINSHELLAPI BOOL  SHCreateMenuBar(SHMENUBARINFO *pmbi)
 {
	 traceLog(  _T(  "SHCreateMenuBar is not correct"  )  );
	 return  FALSE;
 }
#endif
#endif

 void WINAPI SHNavigateBack()
 {
	 traceLog(  _T(  "SHNavigateBack is not correct"  )  );
	 return;
 }

 int  showEnlargedWnd(  HWND  hDlgParent,  BOOL  bDlgTalk,  DLG_VIDEO_PARAMS  *  p,  CAP_subWnds  *  pSubWnds  )
 {
	 traceLog(  _T(  "showEnlargeWnd is not correct."  )  );
	 return  -1;
 }


#ifndef  __WINCE__
   int  getTaskItem(  CListCtrl  *  pListCtrl,  int  iTaskId  )
   {
	   traceLog(  _T(  "getTaskItem is not correct"  )  );
	   return  -1;
   }

    int  activateImTask(  CWnd  *  pDlg,  DLG_TALK_var  &  m_var,  int  iTaskId_activated  )
	{
		traceLog(  _T(  "activateImTask is not correct"  )  );
		return  -1;
	}
#endif


 void  clearShiftKeys()
 {
	 traceLog(  _T(  "clearShiftKeys not supported"  )  );
	 return;
 }

int  popupNotificationWnd(  )
{
	return  -1;
}
int  removeNotification(  QY_MESSENGER_ID  *  pIdInfo_logicalPeer  )
{
	return  -1;
}

 int  viewConferenceResources(  HWND  hDlgTalk,  BOOL  bFreeCapImages  )
{
	traceLog(  _T(  "viewConferenceResources,  test_wince"  )  );
	return  -1;
}

int  viewConference(  HWND  hParent,  HWND  hDlgTalk,  BOOL  bFreeCapImages  )
{
	traceLog(  _T(  "viewConference,  test_wince"  )  );
	return  -1;
}

 extern "C" DWORD WINAPI mcThreadProc_isMgr( LPVOID lpParameter )
{
	traceLog(  _T(  "mcThreadProc_isMgr,  test_wince"  )  );
	return  -1;
}

  int  getSize_moduleExt(  )
{
	traceLog(  _T(  "getSize_moduleExt,  test_wince"  )  );
	return  -1;
}


// 2010/10/02
 BOOL  initModuleExt(  )
{
	traceLog(  _T(  "initModuleExt,  test_wince"  )  );
	return  FALSE;
}

 void  exitModuleExt(  )
{
	traceLog(  _T(  "exitModuleExt,  test_wince"  )  );
	return;
}

 int  initVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	traceLog(  _T(  "initVar_isGui_mgr,  test_wince"  )  );
	return  -1;
}


 int  exitVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	traceLog(  _T(  "exitVar_isGui_mgr,  test_wince"  )  );
	return  -1;
}

   int  closeOtherWnds_isMgr(  )
{
	traceLog(  _T(  "closeOtherWnds_isMgr,  test_wince"  )  );
	return  -1;
}

 int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  )
{
#ifdef  __DEBUG__
		traceLog(  _T(  "myMessageBox,  test_wince"  )  );
#endif
	return  MessageBox(  hWnd ,  lpText,  lpCaption,  uType  );
}

  int  parseDbParams(  LPCTSTR  connectInput,  QNM_DB_CFG  *  pDb  )
{
	return  -1;
}

   int  viewLocalAv_dlgTalk(  HWND  hDlgTalk,  BOOL  bFreeCapImages  )
   {
	   return  -1;
   }