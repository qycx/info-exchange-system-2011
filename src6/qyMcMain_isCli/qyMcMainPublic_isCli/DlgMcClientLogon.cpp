// DlgMcClientLogon.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#ifdef  __WINCE__
	#ifndef  __TEST__
		#include	"ceMenuBar.h"
	#endif
#endif

#include	"myresource.h"

#include	"DlgMcClientLogon.h"
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"qyCusResTemp.h"


extern  "C"  BOOL  bServConnected_mis(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  SOCK_TIMEOUT  *  pTo  );
extern  "C"  int getLogonServerCfg(  QNM_CNT_CFG  *  pCntCfg,  int  index,  unsigned short  *  pSeqNo,  TCHAR  *  pCntName,  unsigned int cntNameSize   );


 int  doMisCntLogon(  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  HWND    hDlg,  DLG_mcClientLogon_var  &  m_var  )
{
	int				iErr			=	-1;
	MC_VAR_isCli	*	pProcInfo		=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	QY_MC		*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMcParam;
	QY_SERVICEGUI_INFO	*	pSci	=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
	BOOL			bCryptInited	=	FALSE;
	int				i;
	TCHAR			tBuf[256];

	memset(  &pChannel->commEncCtx,  0,  sizeof(  pChannel->commEncCtx  )  );
	memcpy(  &pChannel->commEncCtx.common,  &pMisCnt->commEncCtx.common,  sizeof(  pChannel->commEncCtx.common  )  );
	if  (  initCrypt_qmc(  pProcInfo,   pMisCnt,  CONST_cspContainer_qmc,  DEFAULT_cspProvider,  (  pChannel->uiType  ==  CONST_channelType_talking  ),  &pChannel->commEncCtx  )  )  goto  errLabel;
	bCryptInited  =  TRUE;
	//

	_sntprintf(  pChannel->commEncCtx.mutexName_syncCrypt,  mycountof(  pChannel->commEncCtx.mutexName_syncCrypt  ),  _T(  "qmcCrypt%u"  ),  getuiNextTranNo(  0,  0,  0  )  );

	//  2011/02/02
	pProcInfo->authInfo.uiLogonId  =  0;


	//  
	for  (  i  =  0;  i  <  CONST_maxTriesToStartSession_mis;  i  ++  )  {
		 //
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s, %d..."  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_tryToConnect  ),  CQyString(  pMisCnt->server.ip  ),  i  );
		 m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );
		 //
		 if  (  !tryToStartChannel(  pMisCnt,  pChannel,  m_var.respHint,  mycountof(  m_var.respHint  )  )  )  break;		
	}
	if  (  i  ==  CONST_maxTriesToStartSession_mis  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "Logon"  ),  _T(  ""  ),  _T(  "failed"  )  );
		goto  errLabel;
	}	
	pChannel->status.ulbSessionErr  =  FALSE;
	//

	iErr  =  0;

errLabel:

	pChannel->status.ulbSessionErr  =  TRUE;	//  此标志位通知recv和snd两线程退出

	if  (  pChannel->bSessionOpen  )  {
			traceLogA(  "to close session"  );			
			qnmCloseSession_msg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to  );
			pChannel->bSessionOpen  =  FALSE;
			traceLogA(  "session closed"  );	

			qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "Logon"  ),  _T(  ""  ),  _T(  "Session is closed"  )  );

	}
	if  (  bCryptInited  )  exitCrypt_qmc(  pProcInfo,  pMisCnt,  &pChannel->commEncCtx  );
	
	pChannel->status.ulbIoQuit  =  TRUE;

	return  iErr; 
}




#if  0
 __declspec(  dllexport  )  BOOL  myDialogProc_mcClientLogon(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  ) 
{
	CDlgMcClientLogon	*	pDlg	=	(  CDlgMcClientLogon  *  )pDlgParam;	//  (  CDlgMcClientLogon  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  uMsg  ) {

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				 if  ( wID == IDCANCEL  )  {
					 EndDialog(hDlg, LOWORD(wParam));
					 return (INT_PTR)TRUE;
				 }
				 if  (  wID == IDOK  )  {
					 TCHAR	name[64]	=	_T(  ""  );
					 TCHAR	passwd[64]	=	_T(  ""  );
					 //
					 pDlg->m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  pDlg->m_var.guiData.iIDC_NAME,  name,  mycountof(  name  )  );  
					 pDlg->m_var.guiData.pf_GetDlgItemText(  pDlg->m_hWnd,  pDlg->m_var.guiData.iIDC_PASSWD,  passwd,  mycountof(  passwd  )  );  
					 //
					 tTrim(  name  );
					 tTrim(  passwd  );
					 //
					 if  (  !name[0]  )  {
						 SetFocus(  GetDlgItem(  pDlg->m_hWnd,  pDlg->m_var.guiData.iIDC_NAME  )  );
						 return  TRUE;
					 }
					 if  (  !passwd[0]  )  {
						 SetFocus(  GetDlgItem(  pDlg->m_hWnd,  pDlg->m_var.guiData.iIDC_PASSWD  )  );
						 return  TRUE;
					 }

					 dlgMcClientLogon_OnOK(  hDlg,  name,  passwd  );
					 return  TRUE;
				 }
#if  0
				 if  (  wID  ==  pDlg->m_var.guiData.iIDC_BUTTON_option  )  {
					 pDlg->OnBnClickedButtonoption(  );
					 return  TRUE;
				 }
#endif

				 //
				 if  (  wNotifyCode  ==  CBN_SELCHANGE  )  {
					 dlgMcClientLogon_OnCbnSelchangeCombologonserver(  hDlg,  qyWnd_getVar(  pDlg  )  );
					 return  TRUE;
				 }
				 }
				 break;
			case  WM_DESTROY:
				  dlgMcClientLogon_OnDestroy(  hDlg,  qyWnd_getVar(  pDlg  )  );
				  break;

			default:
					break;
	}

	return (INT_PTR)FALSE;
}
#endif

 int dlgMcClientLogon_bNotSeleceted(  HWND  hDlg,  void  *  pVarParam  )
{
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	HKEY		hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR		tQnmSchedulerBuf[256]	=	_T(  ""  );	
	TCHAR		tBuf[16]				=	_T(  ""  );
	int			i						=	0;

	for  (  i = 0; i < CONST_maxOfVideoConferencingServers;  i  ++  )  {
		 if  (  !i  )  
			 _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
		 else 
			 _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  i  );

		 qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_bSelected  )  );
	}
	return  0;
}

 __declspec(  dllexport  )  int	 dlgMcClientLogon_refresh(  HWND  hDlg  )
{
	int							iErr					=	-1;
	CDlgMcClientLogon		*	pDlg					=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	DLG_mcClientLogon_var	&	m_var					=	pDlg->m_var;
	//
	QY_MC					*	pQyMc					=	QY_GET_GBUF(  );
	TCHAR						tBuf[255  +  1]			=	_T(  ""  );
	HKEY						hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR						tQnmSchedulerBuf[256]	=	_T(  ""  );	
	//  char						buf[256]				=	"";
	int							i,j;
	CQyString					str						=  _T(  ""  );
	
	if  (  getLogonServerCfg(  m_var.cntCfg,  0,  m_var.seqNo,  m_var.cntName[0],  mycountof(  m_var.cntName[0]  )  )  >  0  )
		m_var.usItemCount  = 1;
#ifdef  __SUPPORT_MULTILOGON__
	    for (  int serverIndex = 1;  serverIndex <  CONST_maxOfVideoConferencingServers; serverIndex ++  )  {
			if  (  getLogonServerCfg(  m_var.cntCfg,  serverIndex,  m_var.seqNo,  m_var.cntName[serverIndex],  mycountof(  m_var.cntName[0]  )  )  >  0  )
				m_var.usItemCount  ++;
		}

	//  CComboBox m_logonServer;
	HWND	m_logonServer	=	GetDlgItem(  pDlg->m_hWnd,  m_var.guiData.iIDC_COMBO_logonServer  );
	if  (  m_logonServer  )  {
		SendMessage(  m_logonServer,  CB_RESETCONTENT,  0,  0  );

		for  (  i = 0,j = 0;  i <  CONST_maxOfVideoConferencingServers;  i ++  )  {
			if  (  !m_var.usItemCount  )  break;
			if  (  ( !i || m_var.seqNo[i]  )  )  {
				//  str.Format(  _T("%s"),  m_var.cntName[i]  );
				str  =  m_var.cntName[i];
				//  m_logonServer.InsertString(  j,  str  );
				SendMessage(  m_logonServer,  CB_INSERTSTRING,  j,  (  LPARAM  )str.GetBuffer(  )  );
				j ++;
				if (  j > m_var.usItemCount  )  break;
			}
		}
	}

	for  (  i = 0; i < CONST_maxOfVideoConferencingServers;  i ++  )  {
		 if  (  !i  )  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
		 else _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  i  );

		 qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_bSelected  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  );
		 if  (  _ttoi(  tBuf  )  ==  1  )  break;
	}
	if  (  i == CONST_maxOfVideoConferencingServers  )  i  =  0;
	m_var.iSeqNoSelected  =  i;
	//
	qyGetRegCfg1W(  &pQyMc->env, hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  ),  tBuf,  mycountof(  tBuf  ),  0  );
	if  (  m_logonServer  )  {
		i  =  SendMessage(  m_logonServer,  CB_FINDSTRING,  0,  (  LPARAM  )tBuf  );
		SendMessage(  m_logonServer,  CB_SETCURSEL,  i,  0  );
	}
#else
	m_var.iSeqNoSelected  =  0;
#endif
		
	memcpy(  &pQyMc->cfg.dynCfg.cnt,  &m_var.cntCfg[m_var.iSeqNoSelected],  sizeof(  QNM_CNT_CFG  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Server: %s, %s, %s; Port: %d"  ),  
		CQyString(  m_var.cntCfg[m_var.iSeqNoSelected].cntIp  ), 	
		CQyString(  m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0]  ),  
		CQyString(  m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[1]  ),  
		m_var.cntCfg[m_var.iSeqNoSelected].usCntPort  );
	m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );
	//


	iErr  =  0;

errLabel:

	return  iErr;

}



CDlgMcClientLogon::CDlgMcClientLogon(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMcClientLogon::~CDlgMcClientLogon()
{
}

BOOL CALLBACK myEnumWindowsProc_singleInstance(  HWND hwnd,  LPARAM lParam  )
{
	BOOL	bRet	=	TRUE;
	COMMON_PARAM	*	pParam	=	(  COMMON_PARAM  *  )lParam;
	//
	TCHAR	*	lckCStr  =  (  TCHAR  *  )pParam->p1;
	HWND	*	phWnd	=	(  HWND  *  )pParam->p2;


	if  (  GetProp(  hwnd,  lckCStr  )  )  {
		//  myMessageBox(  NULL,  _T(  "Found"  ),  _T(  ""  ),  MB_OK  );
		*phWnd  =  hwnd;
		bRet  =  FALSE;  goto  errLabel;
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


__declspec(  dllexport  )  int dlgMcClientLogon_OnInitDialog(  HWND  hDlg,  void  *  pVarParam  )
{

	// TODO:  Add extra initialization here
	int					iErr					=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_mcClientLogon_var	&	m_var  =  *(  DLG_mcClientLogon_var  *  )pVarParam;

	QY_MC			*	pQyMc					=	QY_GET_GBUF(  );
	CQyString			titleCStr;
	char				buf[128]				=	"Logon"  ;
	cusDlgRes(  0,  &pQyMc->cusRes,  hDlg,  IDD_mcClient_logon  );

	if  (  !m_var.guiData.pf_GetDlgItemText  ||  !m_var.guiData.pf_SetDlgItemText  )  {
		OutputDebugString(  _T(  "logon failed: pf_GetDlgItemText or pf_SetDlgItemText is null\n"  )  );
		goto  errLabel;
	}

	//  2010/07/11
	if  (  pQyMc->cfg.singleInstanceStr[0]  )  {
		CQyString	lckCStr;

		lckCStr = CQyString(  CONST_mutexPrefix_mcClientLogon  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
		m_var.hMutex_singleInstance  =  CreateMutex(  NULL,  FALSE,  lckCStr  );
		if  (  !m_var.hMutex_singleInstance  )  {
			traceLog(  _T(  "singleInstance failed, null."  )  );			
			goto  errLabel;				
		}
		if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
			traceLog(  _T(  "singleInstance failed, already exists."  )  );

			COMMON_PARAM	commonParam;
			HWND	hPrevWnd	=	NULL;

			MACRO_makeCommonParam3(  0,  (  void  *  )lckCStr.GetBuffer(  ),  &hPrevWnd,  commonParam  );
			EnumWindows(  myEnumWindowsProc_singleInstance,  (  LPARAM  )&commonParam  );

			if  (  IsWindow(  hPrevWnd  )  )  {
				//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
				ShowWindow(  hPrevWnd,  SW_SHOWNORMAL  );
			    #if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
								SetForegroundWindow(  hPrevWnd  );
								SetForegroundWindow(  GetLastActivePopup(  hPrevWnd  )  );
				#else
								SetForegroundWindow((HWND)(((ULONG) hPrevWnd) | 0x01) );
				#endif
			}

			goto  errLabel;
		}

		//
		if  (  !IsWindow(  hDlg  )  )  goto  errLabel;
		if  (  !SetProp(  hDlg,  lckCStr,  (  HANDLE  )1  )  )  goto  errLabel;
	}

	//
#ifndef  __APP_qyMc_touchscreen__
		 centerWnd(  hDlg  );
#endif
	::SetWindowPos(  hDlg,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );

	titleCStr  =  CQyString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logon_wndTitle  )  );
	//  titleCStr  +=  CQyString(  getResStr(  0,  &pQyMc->cusRes,  IDD_mcClient_logon  )  );
	SetWindowText(  hDlg,  titleCStr  );  
	//	
	SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_NAME  ),  EM_SETLIMITTEXT,  16,  0  );
	SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_PASSWD  ),  EM_SETLIMITTEXT,  16,  0  );
	
#ifdef  __WINCE__
#ifndef  __TEST__
#if  0
	SendMessage(  GetDlgItem(  this->m_hWnd,  m_var.iIDC_NAME  ),  EM_SETINPUTMODE,  0,  EIM_SPELL  );

	if  (  m_menuBar.bCreate(  this->m_hWnd,  IDR_MENU,  0  )  )  {
		HideButton(  m_menuBar.getMenuBar(  ),  TRUE,  FALSE  );
		HideButton(  m_menuBar.getMenuBar(  ),  TRUE,  TRUE  );

		OverrideKey(  m_menuBar.getMenuBar(  )  );  
	}
#endif

#endif
#endif

	SetFocus(  hDlg  );

	dlgMcClientLogon_refresh(  hDlg  );

#ifdef  __SUPPORT_getUsrPasswdFromIni__

		if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
			    traceLogA(  "Warning: simulate to login"  );
				if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  CONST_regValName_usr,  buf,  sizeof(  buf  )  )  )  {
					trim(  buf  );
					if  (  buf[0]  )  {
						SetDlgItemText(  hDlg,  m_var.guiData.iIDC_NAME,  CQyString(  buf  )  );
					}
				}
				if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  CONST_regValName_passwd,  buf,  sizeof(  buf  )  )  )  {
					trim(  buf  );
					if  (  buf[0]  )  {
						SetDlgItemText(  hDlg,  m_var.guiData.iIDC_PASSWD,  CQyString(  buf  )  );
					}
				}
	 }

#endif
    
	//  2011/03/23
	m_var.uiTimerId  =  SetTimer(  hDlg,  1,  1000,  NULL  );

	if  (  bSupported_devAuth(  )  )  {
		traceLog(  _T(  "trigger IDOK."  )  );
		PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  IDOK,  0  ),  0  );
	}

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		//  EndDialog(  this->m_hWnd,  -1  );
	}

	return iErr;
}

 BOOL  bAnotherInstanceExists(  LPCTSTR  appObjPrefix  )
{
	BOOL		bRet					=	FALSE;		
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	CQyString	lckCStr;
	HANDLE		hMutex_singleInstance	=	NULL;

	if  (  pQyMc->cfg.singleInstanceStr[0]  )  {

		#ifndef  __WINCE__
				 lckCStr = CQyString(  appObjPrefix  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
		#else
				 lckCStr = CQyString(  CONST_mutexPrefix_mcClientLogon  )  +  pQyMc->cfg.singleInstanceStr;
		#endif
				
		hMutex_singleInstance  =  CreateMutex(  NULL,  FALSE,  lckCStr  );
		if  (  !hMutex_singleInstance  )  {				
			traceLog(  _T(  "singleInstance failed, null."  )  );
			goto  errLabel;
		}
		if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
			traceLog(  _T(  "singleInstance failed, already exists."  )  );

			COMMON_PARAM	commonParam;
			HWND	hPrevWnd	=	NULL;

			MACRO_makeCommonParam3(  0,  (  void  *  )lckCStr.GetBuffer(  ),  &hPrevWnd,  commonParam  );
			EnumWindows(  myEnumWindowsProc_singleInstance,  (  LPARAM  )&commonParam  );

			if  (  IsWindow(  hPrevWnd  )  )  {
				//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
				ShowWindow(  hPrevWnd,  SW_SHOWNORMAL  );

				#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
					SetForegroundWindow(  hPrevWnd  );
					SetForegroundWindow(  GetLastActivePopup(  hPrevWnd  )  );
				#else
						SetForegroundWindow((HWND)(((ULONG) hPrevWnd) | 0x01) );
				#endif
			
			}

			bRet  =  TRUE;
			goto  errLabel;
		}

	}

errLabel:

	if  (  hMutex_singleInstance  )  CloseHandle(  hMutex_singleInstance  );

	return  bRet;
}



  void dlgMcClientLogon_OnTimer(  HWND  hDlg,  UINT_PTR nIDEvent)
{
	CDlgMcClientLogon		*	pDlg				=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	DLG_mcClientLogon_var	&	m_var				=	pDlg->m_var;

	if  (  bSupported_devAuth(  )  )  {
		if  (  m_var.bLogonFailed  )  {
			if  (  m_var.nTries_triggerIDOK  >  3  )  {
				SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  _T(  "Logon failed, quit now"  )  );
				PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				return;
			}
			SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  _T(  "Logon failed, try again"  )  );
			m_var.nTries_triggerIDOK  ++  ;
			m_var.bLogonFailed  =  FALSE;
			PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  IDOK,  0  ),  0  );
			return;
		}
	}

	return;
}


__declspec(  dllexport  )  int  dlgMcClientLogon_OnOK(  HWND  hDlg,  LPTSTR  m_name,  LPTSTR  m_passwd  )
{
	int							iErr				=	-1;
	QY_MC					*	pQyMc				=	QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO		*	pSci				=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;

	// TODO: Add your control notification handler code here
	CDlgMcClientLogon		*	pDlg				=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	DLG_mcClientLogon_var	&	m_var				=	pDlg->m_var;
	TCHAR						tBuf[128];

	char						buf[1024]			=	"";
	unsigned  int				len;

	//
	TCHAR						appObjPrefix[16  +  1]	=	_T(  ""  );			//  2010/03/10

#ifdef  __DEBUG__
		traceLog(  _T(  "dlgMcClientLogon_OnOK called"  )  );
#endif

	_sntprintf(  appObjPrefix,  mycountof(  appObjPrefix  ),  _T(  "qm%d"  ),  pDlg->m_var.iSeqNoSelected  );
	#ifndef  __WINCE__
			 if  (  bAnotherInstanceExists(  appObjPrefix  )  )  goto  errLabel;
	#endif

	TCHAR						tPrefix[32]			=	_T(  ""  );
	_sntprintf(  tPrefix,  mycountof(  tPrefix  ),  _T(  "%d: "  ),  m_var.nTries_triggerIDOK  );

	if  (  !bSupported_devAuth(  )  )  {

		if  (  !m_name  ||  !m_name[0]  )  goto  errLabel;
		if  (  !m_passwd  ||  !m_passwd[0]  )  goto  errLabel;

		tTrim(  m_name  );
		tTrim(  m_passwd  );
		//
		if  (  !m_name[0]  )  {
			SetFocus(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_NAME  )  );
			goto  errLabel;
		}
		if  (  !m_passwd[0]  )  {
			SetFocus(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_PASSWD  )  );
			goto  errLabel;
		}
	
		//
		lstrcpyn(  pProcInfo->authInfo.messengerName,  m_name,  mycountof(  pProcInfo->authInfo.messengerName  )  );
		myTChar2Utf8(  m_passwd,  buf,  mycountof(  buf  )  );
		len  =  mycountof(  pProcInfo->authInfo.messengerPasswd  );
		bQyGetStrMd5_x(  buf,  pProcInfo->authInfo.messengerPasswd,  &len  );
	}

	//  CWaitCursor		cur;

	//  2010/01/09
	int  index  =  0;
	memcpy(  &pProcInfo->misCnts[index].cfg.dynCfg,  &pQyMc->cfg.dynCfg,  sizeof(  pProcInfo->misCnts[index].cfg.dynCfg  )  );
	memset(  &pProcInfo->misCnts[index].server,  0,  sizeof(  pProcInfo->misCnts[index].server  )  );

	//
	int								i;
	QY_LOGICAL_SERVER				tmpCnt;

	for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  {
		 MIS_CNT  *  pMisCnt			=  &pProcInfo->misCnts[i];
		 MIS_CHANNEL	*	pChannel	=  getChannelByType(  pMisCnt,  CONST_channelType_talking  );
		 if  (  !pChannel  )  continue;

		 if  (  pChannel->bSessionOpen  )  {
			 qnmCloseSession_msg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to  );  
			 pChannel->bSessionOpen  =  FALSE;
		 }

		 if  (  !pChannel->bSessionOpen  )  {
			 
			 pMisCnt->pAuthInfo  =  &pProcInfo->authInfo;
			 clearQySock(  &pChannel->sock  );

			 //  
			 {					   
				 if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchingServer  )  );
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s, %s, %s; Port: %d"  ),  tBuf,
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntIp  ), 	
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntAddrs[0]  ),  
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntAddrs[1]  ),  
						 pMisCnt->cfg.dynCfg.cnt.usCntPort  );
					 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );
					 if  (  getCorrectCnt(  &pQyMc->env,  &pMisCnt->cfg.dynCfg,  bServConnected_mis,  pMisCnt,  pSci->cfg.iServiceId,  qnmVerStr(  pSci->cfg.iServiceId  ),  &pMisCnt->commEncCtx.common,  &pQyMc->cfg.to,  &tmpCnt  )  )  {
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotFindServer  )  );
						 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );
						 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getCorrectCnt failed"  )  );
						 continue;
						 }
					 else  if  (  memcmp(  &pMisCnt->server,  &tmpCnt,  sizeof(  tmpCnt  )  )  )  {
							   memcpy(  &pMisCnt->server,  &tmpCnt,  sizeof(  pMisCnt->server  )  );
					 }					   
				 }		
			 }
			 if  (  !pMisCnt->commEncCtx.ucbPublicKeyDownloaded  ||  !pMisCnt->commEncCtx.ucbPublicKeyVerified  )  continue;

			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ok"  ),  CQyString(  pMisCnt->server.ip  )  );  
			 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );			 

			 m_var.respHint[0]  =  0;
			 if  (  !doMisCntLogon(  pMisCnt,  pChannel,  pDlg->m_hWnd,  m_var  )  )  break;
		 
		 }

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s: %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_failedToLogon  ),  CQyString(  pMisCnt->server.ip  ),  m_var.respHint  );
		 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );

		 continue;
	}

	if  (  i  ==  mycountof(  pProcInfo->misCnts  )  )  {
		goto  errLabel;
	}

	pQyMc->curUsrInfo.right.bAdmin  =  TRUE;
	myTChar2Str(  m_name,  pQyMc->curUsrInfo.name,  sizeof(  pQyMc->curUsrInfo.name  )  );
	//  _sntprintf(  pQyMc->appObjPrefix,  mycountof(  pQyMc->appObjPrefix  ),  _T(  "qm%d"  ),  pDlg->m_var.iSeqNoSelected  );
	lstrcpyn(  pQyMc->appParams.appObjPrefix,  appObjPrefix,  mycountof(  pQyMc->appParams.appObjPrefix  )  );

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		//  EndDialog(  pDlg->m_hWnd,  IDOK  );
	}
	if  (  iErr  )  {
		m_var.bLogonFailed  =  TRUE;
	}

	return  iErr;
}

 __declspec(  dllexport  )  int dlgMcClientLogon_OnDestroy(  HWND  hDlg,  void  *  pVarParam  )
{
	int				iErr	=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_mcClientLogon_var	&	m_var	=	*(  DLG_mcClientLogon_var  *  )pVarParam;

	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CQyString		lckCStr;
	HANDLE			hRet	=	NULL;

	if  (  m_var.uiTimerId  )  KillTimer(  hDlg,  m_var.uiTimerId  );		//  2007/12/22

	lckCStr = CQyString(  CONST_mutexPrefix_mcClientLogon  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
	hRet  =  RemoveProp(  hDlg,  lckCStr  );

	if  (  m_var.hMutex_singleInstance  )  {
		 CloseHandle(  m_var.hMutex_singleInstance  );
		 m_var.hMutex_singleInstance  =  NULL;
	 }

	iErr  =  0;
	return  iErr;
}

__declspec(  dllexport  )  void dlgMcClientLogon_OnCbnSelchangeCombologonserver(  HWND  hDlg,  void  *  pVarParam  )
{
	if  (  !pVarParam  )  return;
	DLG_mcClientLogon_var	&	m_var	=	*(  DLG_mcClientLogon_var  *  )pVarParam;

	// TODO: Add your control notification handler code here
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	HKEY		hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR		tQnmSchedulerBuf[256]	=	_T(  ""  );	
	TCHAR		tBuf1[256]				=	_T(  ""  );	
	TCHAR		tBuf2[256]				=	_T(  ""  );
	char		buf[256]				=	"";
	int			i						=	0;


	HWND	m_logonServer	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_COMBO_logonServer  );
	if  (  !m_logonServer  )  return;

	if  (  (  i = SendMessage(  m_logonServer,  CB_GETCURSEL,  0,  0  )  )  ==  -1  )  return;

	//  m_logonServer.GetLBText(  i,  tBuf1  );
	SendMessage(  m_logonServer,  CB_GETLBTEXT,  i,  (  LPARAM  )tBuf1  );

	for  (  i = 0; i < CONST_maxOfVideoConferencingServers;  i ++  )  {
		if  (  !i  )  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
		else  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  i  );  

		qyGetRegCfg1W(  &pQyMc->env,  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  ),  tBuf2,  mycountof(  tBuf2  ),  0  );
		if  (  !_tcsncmp(  tBuf1,  tBuf2,  mycountof(  tBuf1  )  )  )  break;
	}
	if  (  i == CONST_maxOfVideoConferencingServers  )  i  =  0;
	m_var.iSeqNoSelected  =  i;
		
	memcpy(  &pQyMc->cfg.dynCfg.cnt,  &m_var.cntCfg[m_var.iSeqNoSelected],  sizeof(  QNM_CNT_CFG  )  );
	_snprintf(  buf,  sizeof(  buf  ),  "Server: %s, %s, %s; Port: %d",  
		m_var.cntCfg[m_var.iSeqNoSelected].cntIp, 	m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0],  m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[1],  m_var.cntCfg[m_var.iSeqNoSelected].usCntPort  );
	SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  buf  )  );
	//
	dlgMcClientLogon_bNotSeleceted(  hDlg,  pVarParam  );
	if  (  !m_var.iSeqNoSelected  )  
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
	else 
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  m_var.iSeqNoSelected  );
	_sntprintf(  tBuf1,  mycountof( tBuf1  ),  _T(  "%d"  ),  1  );
	qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_bSelected  ),  tBuf1  );
}

#if  0
void CDlgMcClientLogon::OnBnClickedButtonoption()
{
	// TODO: Add your control notification handler code here
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

#if  0
	CDlgQnmCfgOptionsIsClient	dlg;

	//  dlg.DoModal(  );
	DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  dlg.IDD  ),  this->m_hWnd,  dlgProc_qnmCfgOptionsIsClient,  (  LPARAM  )&dlg  );
#endif
	PF_commonHandler  pf  =  (  PF_commonHandler  )g_getGuiData(  )->pf_showDlgQnmCfgOptionsIsClient;
	if  (  pf  )  pf(  pQyMc->g_hInst,  this->m_hWnd,  0  );

	dlgMcClientLogon_refresh(  this->m_hWnd  );

}

#endif






