// MainClient.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qyGuiCommonEx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"MainClient.h"
#include	"qyMcDlgBarCfg.h"
//  #include	"qyDialogbar.h"
#include	"mainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainClient

CMainClient::CMainClient()
{
}

CMainClient::~CMainClient()
{
}


BEGIN_MESSAGE_MAP(CMainClient, CWnd)
	//{{AFX_MSG_MAP(CMainClient)
	ON_WM_PARENTNOTIFY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainClient message handlers

LRESULT CMainClient::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	LRESULT  lRet  =  CWnd::DefWindowProc(message, wParam, lParam);
	if  (  message  ==  WM_MDISETMENU  )  {
		CMainFrame	*	pFrame;

		pFrame	=	(  CMainFrame  *  )AfxGetMainWnd(  );
		if  (  pFrame  && ::IsWindow(  pFrame->m_hWnd  )  )
			pFrame->bSwitchToolbar( );
	}
	
	return  lRet;

}

void CMainClient::OnParentNotify(UINT message, LPARAM lParam) 
{
	CWnd::OnParentNotify(message, lParam);
	
	// TODO: Add your message handler code here
	CMainFrame	*	pFrame;
	CWnd		*	pWnd;
		
	pWnd		=	AfxGetMainWnd(  );
	if  (  !pWnd  )	return;
	if  (  !pWnd->IsKindOf(  RUNTIME_CLASS(  CMainFrame  )  )  )  return;

	pFrame  =  (  CMainFrame  *  )AfxGetMainWnd(  );
	
	switch  (  LOWORD(  message  )  )  {
		case	WM_CREATE:
			break;
		case WM_DESTROY:
			pFrame->bSwitchToolbar(  );
			break;
		default:
			break;
	}

}


