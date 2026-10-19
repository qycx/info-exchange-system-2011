// licenseToolView.cpp : implementation of the CLicenseToolView class
//

#include "stdafx.h"
#include "licenseTool.h"

#include "licenseToolDoc.h"
#include "licenseToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolView

IMPLEMENT_DYNCREATE(CLicenseToolView, CView)

BEGIN_MESSAGE_MAP(CLicenseToolView, CView)
	//{{AFX_MSG_MAP(CLicenseToolView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolView construction/destruction

CLicenseToolView::CLicenseToolView()
{
	// TODO: add construction code here

}

CLicenseToolView::~CLicenseToolView()
{
}

BOOL CLicenseToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolView drawing

void CLicenseToolView::OnDraw(CDC* pDC)
{
	CLicenseToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolView printing

BOOL CLicenseToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLicenseToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLicenseToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolView diagnostics

#ifdef _DEBUG
void CLicenseToolView::AssertValid() const
{
	CView::AssertValid();
}

void CLicenseToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLicenseToolDoc* CLicenseToolView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLicenseToolDoc)));
	return (CLicenseToolDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolView message handlers
