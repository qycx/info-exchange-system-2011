// HistoryView.cpp : implementation file
//

#include "stdafx.h"
#include "qyMcMainCommon.h"
#include "qyMc.h"
#include "HistoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryView

IMPLEMENT_DYNCREATE(CHistoryView, CView)

CHistoryView::CHistoryView()
{
}

CHistoryView::~CHistoryView()
{
}


BEGIN_MESSAGE_MAP(CHistoryView, CView)
	//{{AFX_MSG_MAP(CHistoryView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistoryView drawing

void CHistoryView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	char buf[128];
	sprintf( buf, "i is %d.", this->m_tmpi );
	//  pDC->TextOut( 10, 10, buf, strlen( buf ) );

}

/////////////////////////////////////////////////////////////////////////////
// CHistoryView diagnostics

#ifdef _DEBUG
void CHistoryView::AssertValid() const
{
	CView::AssertValid();
}

void CHistoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistoryView message handlers

void CHistoryView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
