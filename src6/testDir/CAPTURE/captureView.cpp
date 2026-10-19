// captureView.cpp : implementation of the CCaptureView class
//

#include "stdafx.h"
#include "capture.h"

#include "captureDoc.h"
#include "captureView.h"

#include "WzdBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureView

IMPLEMENT_DYNCREATE(CCaptureView, CView)

BEGIN_MESSAGE_MAP(CCaptureView, CView)
	//{{AFX_MSG_MAP(CCaptureView)
	ON_COMMAND(ID_Wzd, OnWzd)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureView construction/destruction

CCaptureView::CCaptureView()
{
	// TODO: add construction code here

}

CCaptureView::~CCaptureView()
{
}

BOOL CCaptureView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCaptureView drawing

void CCaptureView::OnDraw(CDC* pDC)
{
	CCaptureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCaptureView printing

BOOL CCaptureView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCaptureView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCaptureView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCaptureView diagnostics

#ifdef _DEBUG
void CCaptureView::AssertValid() const
{
	CView::AssertValid();
}

void CCaptureView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCaptureDoc* CCaptureView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCaptureDoc)));
	return (CCaptureDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaptureView message handlers

void CCaptureView::OnWzd() 
{
	// TODO: Add your command handler code here
	
	AfxGetApp()->m_pMainWnd->ShowWindow( SW_MINIMIZE );
	::SetActiveWindow( ::GetWindow( this->m_hWnd, GW_HWNDPREV ) );
	Sleep( 5000 );
	
	
	CClientDC dc( this );

	CRect rect;


	CWnd *pWnd = GetDesktopWindow();
	pWnd->GetWindowRect( &rect );
	CWzdBitmap bmp;
	bmp.Capture( rect );
	bmp.SaveBitmapEx( "c:\\temp\\jj.bmp" );
	
	AfxGetApp()->m_pMainWnd->ShowWindow( SW_RESTORE );

	CPalette *pOldPal = dc.SelectPalette( bmp.GetPalette(), FALSE );
	dc.RealizePalette();

	CDC dcComp;
	dcComp.CreateCompatibleDC( &dc );
	dcComp.SelectObject( &bmp );
	dc.BitBlt( 0, 0, bmp.m_nWidth, bmp.m_nHeight, &dcComp, 0, 0, SRCCOPY );

	dc.SelectPalette( pOldPal, FALSE );


	
}
