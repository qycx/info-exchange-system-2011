// testAeView.cpp : implementation of the CTestAeView class
//

#include	"stdafx.h"
#include	"testAe.h"
#include	"testAeDoc.h"
#include	"testAeView.h"
#include	"qyCommon.h"
#include	"awmExtCfg.h"
#include	"dlgInput.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAeView

IMPLEMENT_DYNCREATE(CTestAeView, CView)

BEGIN_MESSAGE_MAP(CTestAeView, CView)
	//{{AFX_MSG_MAP(CTestAeView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAeView construction/destruction

CTestAeView::CTestAeView()
{
	// TODO: add construction code here

}

CTestAeView::~CTestAeView()
{
}

BOOL CTestAeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestAeView drawing

void CTestAeView::OnDraw(CDC* pDC)
{
	CTestAeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestAeView printing

BOOL CTestAeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestAeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestAeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestAeView diagnostics

#ifdef _DEBUG
void CTestAeView::AssertValid() const
{
	CView::AssertValid();
}

void CTestAeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestAeDoc* CTestAeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestAeDoc)));
	return (CTestAeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestAeView message handlers


