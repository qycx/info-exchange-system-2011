
#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qyLangCommProc.h"
#include	"ceMenuBar.h"

#if  TBIF_BYINDEX
	#define  _MBIF(  x  )  (  (  x  )  |  TBIF_BYINDEX  )
	#define	 _MBID(  x  )  (  x  )
#else
	#define  _MBIF(  x  )  (  x  )
	#define	 _MBID(  x  )  (  IDC_LSK  +  (  x  )  )
#endif


CCeMenuBar::CCeMenuBar(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CCeMenuBar::~CCeMenuBar(  )
{
	if  (  IsWindow(  m_var.hWndMenuBar  )  )  {
		DestroyWindow(  m_var.hWndMenuBar  );
		m_var.hWndMenuBar  =  NULL;
	}
	return;
}

 HWND	CCeMenuBar::getMenuBar(  )
{
	return  m_var.hWndMenuBar;
}


BOOL  CCeMenuBar::bCreate(  HWND  hParent,  UINT  uBarRes,  HINSTANCE  hInst,  DWORD  dwFlags  )
{
	BOOL			bRet	=	FALSE;
	SHMENUBARINFO	mbi;

#if  0
	ZeroMemory(&mbi, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hParent;
	mbi.nToolBarId = uBarRes;
	mbi.hInstRes   = hInst;	//  AfxGetResourceHandle(  );

	if  (  !SHCreateMenuBar(&mbi)  )  goto  errLabel;
           
	m_var.hWndMenuBar  =  mbi.hwndMB;

	bRet  =  TRUE;
#endif

errLabel:
	return  bRet;
}


 DWORD  OverrideKey(  HWND  hWnd_menuBar,  WPARAM  wParam  )
{
	return  SendMessage(  hWnd_menuBar,  SHCMBM_OVERRIDEKEY,  wParam,  MAKELPARAM(  SHMBOF_NODEFAULT  |  SHMBOF_NOTIFY,  SHMBOF_NODEFAULT  |  SHMBOF_NOTIFY  )  );
}

 BOOL  GetButtonText(  HWND  hWnd_menuBar,  PTSTR  ptzStr,  unsigned  int  cnt,  BOOL  bRight  )
{
	TBBUTTONINFO	tb;
	memset(  &tb,  0,  sizeof(  tb  )  );
	tb.cbSize  =  sizeof(  tb  );
	tb.dwMask  =  _MBIF(  TBIF_TEXT  );
	tb.pszText  =  ptzStr;
	tb.cchText  =  cnt;
	return  SendMessage(  hWnd_menuBar,  TB_GETBUTTONINFO,  _MBID(  bRight  ),  (  LPARAM  )&tb  );
}

BOOL  SetButtonText(  HWND  hWnd_menuBar,  LPCTSTR  ptzStr,  BOOL  bRight  )
{
	TBBUTTONINFO	tb;
	memset(  &tb,  0,  sizeof(  tb  )  );
	tb.cbSize  =  sizeof(  tb  );
	tb.dwMask  =  _MBIF(  TBIF_TEXT  );
	tb.pszText  =  (  PTSTR  )ptzStr;
	return  SendMessage(  hWnd_menuBar,  TB_SETBUTTONINFO,  _MBID(  bRight  ),  (  LPARAM  )&tb  );
}

BYTE  GetButtonState(  HWND  hWnd_menuBar,  BOOL  bRight  )
{
	TBBUTTONINFO	tb;
	memset(  &tb,  0,  sizeof(  tb  )  );
	tb.cbSize  =  sizeof(  tb  );
	tb.dwMask  =  _MBIF(  TBIF_STATE  );
	SendMessage(  hWnd_menuBar,  TB_GETBUTTONINFO,  _MBID(  bRight  ),  (  LPARAM  )&tb  );
	return  tb.fsState;
}

BOOL  SetButtonState(  HWND  hWnd_menuBar,  BYTE  bState,  BOOL  bRight  )
{
	TBBUTTONINFO	tb;
	memset(  &tb,  0,  sizeof(  tb  )  );
	tb.cbSize  =  sizeof(  tb  );
	tb.dwMask  =  _MBIF(  TBIF_STATE  );
	tb.fsState  =  bState;
	return  SendMessage(  hWnd_menuBar,  TB_SETBUTTONINFO,  _MBID(  bRight  ),  (  LPARAM  )&tb  );
}

 BOOL  EnableButton(  HWND  hWnd_menuBar,  BOOL  bEnable,  BOOL  bRight  )
{
	return  SetButtonState(  hWnd_menuBar,  bEnable  ?  TBSTATE_ENABLED  :  0,  bRight  );
}

 BOOL  HideButton(  HWND  hWnd_menuBar,  BOOL  bHide,  BOOL  bRight  )
{
	return  SetButtonState(  hWnd_menuBar,  bHide  ?  TBSTATE_HIDDEN  :  0,  bRight  );
}


 int  ce_popupMenu(  void  *  pCusResParam,  HWND  hWnd_menuBar,  int  iResId, int  nPos,  BOOL  bRight  )
{
	int					iErr	=	-1;
	unsigned  int		uCmd	=	0;
	QNM_CUSRES_INFO  *  pCusRes	=	(  QNM_CUSRES_INFO  *  )pCusResParam;

	BYTE  bState  =  GetButtonState(  hWnd_menuBar,  bRight  );

#if  0
	if  (  bState  &  TBSTATE_PRESSED  )  {
		keybd_event(  VK_ESCAPE,  0,  KEYEVENTF_SILENT,  0  );
		keybd_event(  VK_ESCAPE,  0,  KEYEVENTF_SILENT  |  KEYEVENTF_KEYUP,  0  );
	}
	else  {
		  RECT  rt;
		  GetWindowRect(  hWnd_menuBar,  &rt  );
		  SetButtonState(  hWnd_menuBar,  bState  |  TBSTATE_PRESSED,  bRight  );
		  BOOL	bRet	=	0;

		  CMenu	tmpMenu;
		  QY_DMITEM	*	pItem;

		  if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
		  if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pCusRes->pCusMenuTable,  iResId  )  )  )  goto  errLabel;
		  if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
		  if  (	 makeDynaMenu(  pCusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  NULL,  NULL  )  )  goto  errLabel;

		  uCmd  =  TrackPopupMenuEx(  tmpMenu.m_hMenu,  bRight  ?  (  TPM_RETURNCMD  |  TPM_RIGHTALIGN  |  TPM_BOTTOMALIGN  )  :  (  TPM_RETURNCMD  |  TPM_LEFTALIGN  |  TPM_BOTTOMALIGN  ),
			  bRight  ?  rt.right  :  rt.left,  rt.top,  GetParent(  hWnd_menuBar  ),  NULL  );
		  if  (  !uCmd  )  {
			  //  qyDisplayLastError(  "kk"  );
			  goto  errLabel;
		  }
	}
#endif

	iErr  =  0;

errLabel:
	SetButtonState(  hWnd_menuBar,  bState  &  ~TBSTATE_PRESSED,  bRight  );	
	return  iErr  ?  iErr  :  uCmd;
}
