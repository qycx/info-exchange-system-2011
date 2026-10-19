
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"isCmdConst.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDxSurfacePublic.h"

#include	"tmpCeLib.h"

#include	"qnmResDefs.h"
#ifndef  __TEST__
		 #include	"ceMenuBar.h"
#endif

#include	"dlg_qyMc_winCe.h"

CDlg_qyMc_winCe::CDlg_qyMc_winCe(  )
{
	memset(  &var,  0,  sizeof(  var  )  );
}

CDlg_qyMc_winCe::~CDlg_qyMc_winCe(  )
{

}



 __declspec(  dllexport  )BOOL  myDialogProc_qyMc_winCe(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  )
{
	CDlg_qyMc_winCe  *  pDlg  =  (  CDlg_qyMc_winCe  *  )pDlgParam;	//  GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  uMsg  )  {
			case  CONST_qyWm_postComm:
				  mainWnd_OnQyPostComm(  hDlg,  &pDlg->var,  wParam,  lParam  );
				  return  TRUE;
				  break;
			default:
					break;
	}
	return (INT_PTR)FALSE;
}


	


#if  0
BOOL CDlg_qyMc_winCe::OnInitDialog( )
{

#if  0
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
#endif

	// TODO: Add extra initialization here
	int				iErr		=	-1;
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	QY_DMITEM	*	pItem		=	NULL;
	HMENU			hMenu		=	NULL;


	//  
	if  (  initVar_onCreate_mainFrame(  0,  this->m_hWnd,  &this->var  )  )  goto  errLabel;
	

#if  0
#ifndef  __TEST__
	if  (  m_menuBar.bCreate(  this->m_hWnd,  IDR_MENU,  g_hInst  )  )  {
		//
		SetButtonText(  m_menuBar.getMenuBar(  ),  _T(  "Menu"  ),  FALSE  );
		SetButtonText(  m_menuBar.getMenuBar(  ),  _T(  "Cancel"  ),  TRUE  );
	}
#endif
#endif


#if  0
	//
	if  (  qyShowMainWnd(  var  )  )  goto  errLabel;

	//
	SetForegroundWindow(  this->m_hWnd  );

#endif

	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  this->m_hWnd,  -1  );
	}

	return  TRUE;
}
#endif

#if  0
void  CDlg_qyMc_winCe::OnDestroy(  )
{
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );

	debugLog(  "CMainFrame::OnDestroy(  ) enters."  );

#ifndef  __WINCE__
	if  (  pQyMc->cfg.ucbUseTrayIcon  )  sendTrayMsg(  g_hInst,  this->m_hWnd,  pQyMc->cfg.iIDR_TRAY,  NIM_DELETE,  IDR_TRAY_offline,  CONST_qyWm_trayNotify  );
#endif
	
	exitVar_onDestroy_mainFrame(  0,  this->m_hWnd,  &this->var  );

	// SaveBarState( _T( QY_MC_PROFILENAME ) );

	//  traceLogA(  "CMainFrame::OnDestroy(  ): "  );


	// TODO: Add your message handler code here
	debugLog(  "CMainFrame::OnDestroy(  ) leaves."  );

	return;
}
#endif



#if  0
void CDlg_qyMc_winCe::Onqyquitmainwnd()
{
	mainWnd_OnQyQuitMainWnd(  this->m_hWnd,  this->var  );
}
#endif


#ifdef  __TEST__
 int  test_popupMenu(  void  *  pCusResParam,  HWND    hWnd,  int  iResId,  int  nPos  )
 {
	 return  -1;
#if  0
	 int				iErr		=	-1;
	 unsigned  int		uCmd		=	0;
	 QNM_CUSRES_INFO  *  pCusRes	=	(  QNM_CUSRES_INFO  *  )pCusResParam;
	 DWORD dwPos = GetMessagePos();
	 BOOL				bRight		=	FALSE;

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	//  pWnd->ScreenToClient( &spt );


	CMenu	tmpMenu;
	QY_DMITEM	*	pItem;

	if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pCusRes->pCusMenuTable,  iResId  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	if  (	 makeDynaMenu(  pCusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  NULL,  NULL  )  )  goto  errLabel;

	uCmd  =  TrackPopupMenuEx(  tmpMenu.m_hMenu,  bRight  ?  (  TPM_RETURNCMD  |  TPM_RIGHTALIGN  |  TPM_BOTTOMALIGN  )  :  (  TPM_RETURNCMD  |  TPM_LEFTALIGN  |  TPM_BOTTOMALIGN  ),
		spt.x,  spt.y,  pWnd->GetSafeHwnd(  ),  NULL  );
	if  (  !uCmd  )  {
			  //  qyDisplayLastError(  "kk"  );
		goto  errLabel;
	}
	
	iErr  =  0;
errLabel:

	return  iErr  ?  iErr  :  uCmd;
#endif
}
#endif





