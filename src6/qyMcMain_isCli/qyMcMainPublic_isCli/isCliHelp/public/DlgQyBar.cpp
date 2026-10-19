// DlgQyBar.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
//  #include	"qmShell_open.h"

#include	"tmpCeLib.h"

#include	"DlgWalls.h"

//  #include	"DlgMenuIsCli.h"
#include	"myresource.h"

#include	"qyCusResTemp.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"


#include	"DlgQyBar.h"
#include	"wallTalkers.h"
#include	"isCliHelpPublic.h"


#if  1  //  def  __APP_qyMc__
 //  int  viewWallsBar(  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  BOOL  bNoDelayToView  )
 __declspec(  dllexport  )  int  viewWallsBar(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  void  *  pDLG_wall_var,  BOOL  bNoDelayToView  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//
	//  if  (  pProcInfo->g_hVWall  !=  hDlgWalls  )  return  -1;

	//  DLG_wall_var	*	pVar	=	(  DLG_wall_var  *  )getDlgWallsVar(  hDlgWalls  );
	if  (  !pDLG_wall_var  )  return  -1;
	DLG_wall_var	&	m_var	=	*(  DLG_wall_var  *  )pDLG_wall_var;

	//
	m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );


	CDlgQyBar				*		pDlg					=	NULL;
	int								iIDD					=	-1;
	int								iStatus_ia				=	0;
	BOOL							bMin					=	FALSE;

	//  traceLogA(  "viewInstantAssistant enters"  );

#ifdef  __DEBUG__
		int  i  =  sizeof(  int  );
		//  traceLog(  _T(  "viewIa, xPos %d, yPos %d"  ),  xPos,  yPos  );
		//  goto  errLabel;
#endif


#if  10

	if  (  !bNoDelayToView  )  {	
		if  (  xPos_screen  ==  m_var.param_viewBar.xPos_screen  &&  yPos_screen  ==  m_var.param_viewBar.yPos_screen  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "viewInstantAssistant: mouse pos has not changed, skipped"  )  );
			#endif
			iErr  =  0;  goto  errLabel;
		}
		//  2011/03/26. 这里的防delay似乎没意义，原来是担心在窗口关闭后，又莫名其妙的被触发了一个mousemove事件，现在看来，是xPos_screen, yPos_screen没有过滤造成的。
		//  
#if 0
		if  (  GetTickCount(  )  -  sdwTickCnt_close_instantAssistant  <  pQyMc->cfg.usDelayInMsToViewToolbar  )  {
			iErr  =  0;  goto  errLabel;
		}
#endif
	}
	m_var.param_viewBar.xPos_screen  =  xPos_screen;
	m_var.param_viewBar.yPos_screen  =  yPos_screen;
#endif


	if  (  IsWindow(  m_var.hBar  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	m_var.hBar  =  NULL;


//

		 //  2010/12/18
		 HWND	hFore	=	GetForegroundWindow(  );
		 HWND	hAbove  =	NULL;	//  findWndAbove(  hParent  );

		 //
		 RECT							rect;

		 HWND	hParent  =  hWndEvent;	//  hDlgWalls;
		 pDlg  =  new  CDlgQyBar(  hParent  );
		 if  (  !pDlg  )  goto  errLabel;

		 pDlg->m_var.guiData.hDlgWalls  =  hDlgWalls;		//  2012/05/24

		 //
		 if  (  !pDlg->Create(  rect  )  )  goto  errLabel;

		 //
		 setWallsBarPos(  hDlgWalls,  pDLG_wall_var,  pDlg->m_hWnd  );

		 //	ShowWindow(  pDlg->m_hWnd,  SW_SHOW  );
		 // 
		 #ifdef  __APP_qyMc_touchscreen__
				 //  traceLog(  _T(  "before AnimateWindow"  )  );
				 DWORD  dwTimeInMs  =  300;
				 DWORD	dwFlags  =  AW_SLIDE  |  AW_VER_NEGATIVE;
				 if  (  !AnimateWindow(  pDlg->m_hWnd,  dwTimeInMs,  dwFlags  )  )  {		
					 traceLog(  _T(  "AnimateWindow failed"  )  );
				 }
				 //  traceLog(  _T(  "after AnimateWindow"  )  );
		 #endif
			
		 int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;
		 SetWindowPos(  pDlg->m_hWnd,  hAbove,  0,  0,  0,  0,  flg  );
		 //
		 #ifndef  __APP_qyMc_touchscreen__
				  if  (  IsWindow(  hFore  )  )  SetForegroundWindow(  hFore  );
		 #endif


	 //
	 pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );

	//  
	m_var.hBar  =  pDlg->m_hWnd;
	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewInstantAssistant leaves, iErr is %d",  iErr  );

	return  iErr;
}


__declspec(  dllexport  )  int  setWallsBarPos(  HWND  hDlgWalls,  void  *  pDLG_wall_var,  HWND  hBar  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int			iErr	=	-1;

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//  DLG_wall_var	*	pVar	=	(  DLG_wall_var  *  )getDlgWallsVar(  hDlgWalls  );
	if  (  !pDLG_wall_var  )  return  -1;
	DLG_wall_var	&	m_var	=	*(  DLG_wall_var  *  )pDLG_wall_var;
	
	if  (  !hBar  )  hBar  =  m_var.hBar;
	if  (  !IsWindow(  hBar  )  )  return  -1;


	int	iH_dlg;
	int  iX,  iY,  iW,  iH;

	RECT	rc;
	GetClientRect(  hDlgWalls,  &rc  );
	MapWindowPoints(  hDlgWalls,  NULL,  (  LPPOINT  )&rc,  2  );

	iH_dlg  =  rc.bottom  -  rc.top;

//  #define		CONST_miH_bar	70
//  #define		CONST_miH_bar	30
#ifdef   __DEBUG__
		 #define	CONST_miH_bar	30
#else
		 #define	CONST_miH_bar	60
#endif

	{

		  iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		  iH  =  0.25  *  iH;
		  iH  =  min(  CONST_miH_bar,  iH  );
		  iY  +=  iH_dlg  -  iH;
	}

	SetWindowPos(  hBar,  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  );

	iErr  =  0;

	return  iErr;

}


#endif


// CDlgQyBar dialog

IMPLEMENT_DYNAMIC(CDlgQyBar, CDialog)

CDlgQyBar::CDlgQyBar(HWND  hParent /*=NULL*/)
		: CDialog(CDlgQyBar::IDD, CWnd::FromHandle(  hParent  ))
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.guiData.hParent  =  hParent;

}

CDlgQyBar::~CDlgQyBar()
{
}


 BOOL CDlgQyBar::Create(const RECT& rect) 
{
	BOOL	bRet	=	FALSE;

	if  (  !CDialog::Create(  this->IDD,  CWnd::FromHandle(  m_var.guiData.hParent  )  )  )  goto  errLabel;

	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

 BOOL  CDlgQyBar::bQuitDlg(  )
{
	traceLogA(  "CDlgQyBar(  )::bQuitDlg enters"  );


	//
	DestroyWindow(  );


	//
	traceLogA(  "CDlgQyBar(  )::bQuitDlg leaves"  );

	return  TRUE;
}



void CDlgQyBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgQyBar, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_menu, &CDlgQyBar::OnBnClickedButtonmenu)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgQyBar message handlers

void CDlgQyBar::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	if  (  m_var.bCreated  )  {
		traceLogA(  "CDlgQyBar::PostNcDestroy, delete this"  );
		delete  this;
	}
}

BOOL CDlgQyBar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	HWND	hDlg  =  m_hWnd;

	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	//  2010/08/29
	m_var.wTimerID  =  ::SetTimer(  hDlg,  1,  1000,  NULL  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQyBar::OnBnClickedButtonmenu()
{
	// TODO: Add your control notification handler code here

	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	::PostMessage(  m_var.guiData.hDlgWalls,  WM_COMMAND,  MAKEWPARAM(  ID_showMenu_wallsBar,  0  ),  0  );
}

int  sizeAllControls_qyBar(  HWND  hDlg  )
{
	HDWP			hDwp;

	int				idc;
	int				x, y, iW, iH;

	RECT			rc;
	GetClientRect(  hDlg,  &rc  );

	iW  =  rc.right  -  rc.left;
	iH  =  rc.bottom  -  rc.top;

	hDwp  =  BeginDeferWindowPos(  1  );
	if  (  hDwp  )  {		 

		idc  =  IDC_BUTTON_menu;
		x  =  0;
		y  =  0;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
		EndDeferWindowPos(  hDwp  );
	}

	return  0;
}

void CDlgQyBar::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeAllControls_qyBar(  m_hWnd  );
}

void CDlgQyBar::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	HWND	hDlg  =  m_hWnd;

	if  (  GetTickCount(  )  -  m_var.dwTickCnt_lastMouseMove  >  10000  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgQyBar: OnTimer: before close"  )  );
		#endif		
		::SendMessage(  hDlg,  WM_CLOSE,  0,  0  );
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgQyBar: OnTimer: after close"  )  );
		#endif
		return;
	}


	CDialog::OnTimer(nIDEvent);
}

void CDlgQyBar::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgQyBar::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();
	bQuitDlg(  );
}
