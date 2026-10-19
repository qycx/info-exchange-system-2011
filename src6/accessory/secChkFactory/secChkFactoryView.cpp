// secChkFactoryView.cpp : implementation of the CSecChkFactoryView class
//

#include "stdafx.h"
#include "secChkFactory.h"

#include "secChkFactoryDoc.h"
#include "secChkFactoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryView

IMPLEMENT_DYNCREATE(CSecChkFactoryView, CView)

BEGIN_MESSAGE_MAP(CSecChkFactoryView, CView)
	//{{AFX_MSG_MAP(CSecChkFactoryView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryView construction/destruction

CSecChkFactoryView::CSecChkFactoryView()
{
	// TODO: add construction code here

}

CSecChkFactoryView::~CSecChkFactoryView()
{
}

BOOL CSecChkFactoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryView drawing

void CSecChkFactoryView::OnDraw(CDC* pDC)
{
	CSecChkFactoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryView printing

BOOL CSecChkFactoryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSecChkFactoryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSecChkFactoryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryView diagnostics

#ifdef _DEBUG
void CSecChkFactoryView::AssertValid() const
{
	CView::AssertValid();
}

void CSecChkFactoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSecChkFactoryDoc* CSecChkFactoryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSecChkFactoryDoc)));
	return (CSecChkFactoryDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryView message handlers
