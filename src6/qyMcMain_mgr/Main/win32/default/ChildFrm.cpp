// ChildFrm.cpp : implementation of the CChildFrame class
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyCommCommon.h"
#include	"qyMc.h"
#include	"ChildFrm.h"
#include	"LeftView.h"
#include	"historyView.h"
#include	"qyMcView.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_MESSAGE(QY_WM_COMM, OnQyComm)
	ON_MESSAGE(QY_WM_PUTDATA, OnQyPutData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	memset(  &this->var, 0, sizeof(  this->var  )  );
	this->var.m_uCfgTimerId = DEFAULT_QY_MC_CHILD_FRM_TIMER_ID;
  	
}

CChildFrame::~CChildFrame()
{
}
 
/*
BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	// 
	// create splitter window
	// if (!m_wndSplitter.CreateStatic(this, 1, 2))
	// 	return FALSE;
	//
	// if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(100, 100), pContext) ||
	//	!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CQyMcView), CSize(100, 100), pContext))
	// {
	//	m_wndSplitter.DestroyWindow();
	//	return FALSE;
	// }
	// 

	// 建立对子窗口的管理
	this->var.mgrLeft.iViewType			=		QY_VIEWTYPE_MCBARLEFT;
	this->var.mgrRight.iViewType		=		QY_VIEWTYPE_MCBARRIGHT;
	this->var.mgrBottom.iViewType		=		QY_VIEWTYPE_MCBARHISTORY;


	
	// create splitter window
	if ( !m_wndSplitter.CreateStatic( this, 2, 1, WS_CHILD ) )
		return FALSE;

	
	if ( !m_wndSplitter2.CreateStatic( &m_wndSplitter, //原来的m_wndSplitter是父指针，m_wndSplitter2是子指针 
		1, 2,  //窗口分为两行，一列 
		WS_CHILD|WS_VISIBLE|WS_BORDER, m_wndSplitter.IdFromRowCol( 0, 0 ) ) )
	{ 
		TRACE0( "Failed to create nested splitter\n" );
		return FALSE; 
	} 

	//增加两个视图，并调整视图大小 
	if ( !m_wndSplitter2.CreateView( 0, 0, RUNTIME_CLASS( CQyMcBarView ),
		CSize( 100, 175 ), pContext ) )
	{ 
		TRACE0( "Failed to create second pane\n" );
		return FALSE; 
	} 

	if ( !m_wndSplitter2.CreateView( 0, 1, pContext->m_pNewViewClass, // RUNTIME_CLASS( CQyMcView ), 
		CSize( 0, 0 ),pContext ) )
	{ 
		TRACE0( "Failed to create third pane\n" );
		return FALSE; 
	}

	if ( !m_wndSplitter.CreateView( 1, 0, RUNTIME_CLASS( CHistoryView ), CSize( 0, 0 ), pContext ) ) { 
		TRACE0( "Failed to create first pane\n" ); 
		return FALSE; 
	}

	if ( !bPrepareForDaemonRefresh( ) ) {
		PostMessage( WM_CLOSE );
		goto errLabel;
	}

	
	int cyCur, cyMin;

	m_wndSplitter.GetRowInfo( 0, cyCur, cyMin );
	m_wndSplitter.GetRowInfo( 1, cyCur, cyMin );
	m_wndSplitter.SetRowInfo( 0, 150, 0 );
	// m_wndSplitter.SetRowInfo( 1, 180, 0 );
	m_wndSplitter2.SetColumnInfo(  0,  150,  0  );
	// m_wndSplitter2.SetColumnInfo(  1,  180,  0  );

	// getBottomView( )->ShowWindow(  SW_HIDE  );
	
	m_wndSplitter.ShowWindow( SW_SHOWNORMAL );
	m_wndSplitter.UpdateWindow( );

	SetActiveView( getLeftView( ) );


errLabel:

	return TRUE;

}
*/


BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{

	// 建立对子窗口的管理
	CQyMcDoc  * pDoc  =  (  CQyMcDoc  *  )pContext->m_pCurrentDoc;
	if  (  !pDoc  )	return FALSE;
	if  (  !pDoc->bDocAvail(  )  )  return  FALSE;
	switch  (  pDoc->m_docStruct.iDocType  )  {
			case  QY_DOCTYPE_MCSITE:
				  this->var.mgrLeft.iViewType	=		QY_VIEWTYPE_MCSITELEFT;
				  this->var.mgrRight.iViewType	=		QY_VIEWTYPE_MCSITERIGHT;
				  break;
			default:
					return  FALSE;

	}

	
	// create splitter window
	if ( !m_wndSplitter.CreateStatic( this, 1, 2, WS_CHILD ) )
		return FALSE;

	
		//增加两个视图，并调整视图大小 
	if ( !m_wndSplitter.CreateView( 0, 0, pContext->m_pNewViewClass,
		CSize( 100, 175 ), pContext ) )
	{ 
		TRACE0( "Failed to create second pane\n" );
		return FALSE; 
	} 

	if ( !m_wndSplitter.CreateView( 0, 1, RUNTIME_CLASS( CQyMcView ), // RUNTIME_CLASS( CQyMcView ), 
		CSize( 0, 0 ),pContext ) )
	{ 
		TRACE0( "Failed to create third pane\n" );
		return FALSE; 
	}

	m_wndSplitter.SetColumnInfo(  0,  150,  0  );
	
	m_wndSplitter.ShowWindow( SW_SHOWNORMAL );
	m_wndSplitter.UpdateWindow( );

	SetActiveView( getLeftView( ) );
	
//  errLabel:

	return TRUE;

}




BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}




  LRESULT CChildFrame::OnQyPutData( WPARAM wParam, LPARAM lParam )
{
	 if ( wParam == ( UINT )this->getLeftView( )->m_hWnd ) {
		 return this->getRightView( )->SendMessage( QY_WM_PUTDATA, wParam, lParam );
	 }
	 return -1;
}


 LRESULT  CChildFrame::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	 LONG				lRet			=					-1;
	 QY_MC			*	pQyMc			=					QY_GET_GBUF(  );
	 QY_WMBUF_COMM  *	pComm			=					(  QY_WMBUF_COMM  *  )lParam;

	 switch  (  pComm->uiType  )  {
		case  QY_WMPARAM_GETVIEWTYPE:
			if  (  (  HWND  )wParam  ==  this->getLeftView(  )->m_hWnd  )
				pComm->u.getViewType.iViewType		=			this->var.mgrLeft.iViewType;
			else  if  (  (  (  HWND  )wParam  ==  this->getRightView(  )->m_hWnd  )  )
				pComm->u.getViewType.iViewType		=			this->var.mgrRight.iViewType;
			// else  if  (  (  (  HWND  )wParam  ==  this->getBottomView(  )->m_hWnd  )  )
			//	pComm->u.getViewType.iViewType		=			this->var.mgrBottom.iViewType;
			else
				goto  errLabel;
			break;
		
		default:
			goto  errLabel;			
	 }

	 lRet		=			QY_RC_WMOK;

errLabel:

	 return			lRet;
	 


}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

CQyMcView* CChildFrame::GetRightPane()
{
	CQyMcView* pView = NULL;
	return pView;
}

/*
CQyMcView *CChildFrame::getQyMcView( )
{
	CQyMcView *pView = DYNAMIC_DOWNCAST( CQyMcView, m_wndSplitter2.GetPane( 0, 1 ) );
	return pView;
}
*/

CQyMcView *CChildFrame::getLeftView( )
{
	CQyMcView *pView = DYNAMIC_DOWNCAST( CQyMcView, m_wndSplitter.GetPane( 0, 0 ) );
	return pView;

}

 
/*
 CHistoryView *CChildFrame::getHistoryView( )
{
	 CHistoryView *pView = DYNAMIC_DOWNCAST( CHistoryView, m_wndSplitter.GetPane( 1, 0 ) );
	 ASSERT( pView );
	 
	 return pView;
}
*/

 CQyMcView *CChildFrame::getRightView( )
{
	CQyMcView *pView = DYNAMIC_DOWNCAST( CQyMcView, m_wndSplitter.GetPane( 0, 1 ) );
	return pView;

}

/*
 CHistoryView *CChildFrame::getBottomView( )
{
	 CHistoryView *pView = DYNAMIC_DOWNCAST( CHistoryView, m_wndSplitter.GetPane( 1, 0 ) );
	 ASSERT( pView );
	 
	 return pView;
}
*/

void CChildFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	int i = 0;

	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CQyMcView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}

}


void CChildFrame::OnViewStyle(UINT nCommandID)
{
	int i = 0;
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CQyMcView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CQyMcView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}

}






void CChildFrame::OnTimer(UINT_PTR nIDEvent) 
{
	 
	 OutputDebugString( _T(  "CChildFrame(  )::OnTimer( ) enters.\n"  )  );
	
	 if  (  this->var.m_uTimerId != nIDEvent || !this->var.m_uTimerId ) {
		 qyDebugHint(  _T(  "Error: m_uTimerId is not equal to nIDEvent."  )  );
		 return;
	 }
	 
	 
	return;

}


BOOL CChildFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	m_hMenuShared  =  pQyMc->gui.hMenuChildFrm;
	
	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}
