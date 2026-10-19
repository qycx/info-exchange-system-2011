// QyBrowseView.cpp : implementation file
//

#include "stdafx.h"
#include "qyMcMainCommon.h"
#include "qyMc.h"
#include "qyMcDoc.h"
#include "QyBrowseView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyBrowseView

IMPLEMENT_DYNCREATE(CQyBrowseView, CView)

CQyBrowseView::CQyBrowseView()
{
	this->m_pBrowser = NULL;
}

CQyBrowseView::~CQyBrowseView()
{
}


BEGIN_MESSAGE_MAP(CQyBrowseView, CView)
	//{{AFX_MSG_MAP(CQyBrowseView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyBrowseView drawing

void CQyBrowseView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CQyBrowseView diagnostics

#ifdef _DEBUG
void CQyBrowseView::AssertValid() const
{
	CView::AssertValid();
}

void CQyBrowseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

 CQyMcDoc* CQyBrowseView::GetDocument() 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQyMcDoc)));
	return (CQyMcDoc*)m_pDocument;
}


/////////////////////////////////////////////////////////////////////////////
// CQyBrowseView message handlers

int CQyBrowseView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect  rect;
	GetClientRect( &rect );
	m_pBrowser = new CWebBrowser2;
	ASSERT( m_pBrowser );
	if  (  !m_pBrowser->Create(  NULL, NULL, WS_VISIBLE, rect, this, IDC_QYWBC  )  )  {
		debugLog(  "failed to create a browser."  );
		delete m_pBrowser;
		m_pBrowser  =  NULL;
		return 0;
	}
		
	return 0;
}

void CQyBrowseView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if ( m_pBrowser )  {
		m_pBrowser->SetWidth(  cx  );
		m_pBrowser->SetHeight(  cy  );
	}

	return;
	
}


void CQyBrowseView::OnDestroy() 
{
	if ( this->m_pBrowser ) {
		m_pBrowser->Stop( );
		m_pBrowser->DestroyWindow( );
		delete m_pBrowser; m_pBrowser = NULL;
	}

	CView::OnDestroy();
	// TODO: Add your message handler code here
	
}


void CQyBrowseView::OnInitialUpdate() 
{
	int				iErr	=	-1;
	CQyMcDoc	*	pDoc	=	GetDocument(  );
	char		*	pUrl	=	NULL;
	COleVariant noArg;


	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	if  (  !pDoc->bDocAvail( )  )  goto  errLabel;

	pUrl	=	pDoc->m_docStruct.m_pMcObj->getMcWeb( )->url;
	m_pBrowser->Navigate( CString(  pUrl  ), &noArg, &noArg, &noArg, &noArg );

	iErr  =  0;
	
errLabel:

	if  (  iErr  )  {
		GetParentFrame( )->PostMessage( WM_CLOSE );
	}
	
}


