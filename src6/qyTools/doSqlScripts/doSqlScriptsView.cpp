// doSqlScriptsView.cpp : implementation of the CDoSqlScriptsView class
//

#include "stdafx.h"
#include "doSqlScripts.h"

#include "doSqlScriptsDoc.h"
#include "doSqlScriptsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsView

IMPLEMENT_DYNCREATE(CDoSqlScriptsView, CView)

BEGIN_MESSAGE_MAP(CDoSqlScriptsView, CView)
	//{{AFX_MSG_MAP(CDoSqlScriptsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsView construction/destruction

CDoSqlScriptsView::CDoSqlScriptsView()
{
	// TODO: add construction code here

}

CDoSqlScriptsView::~CDoSqlScriptsView()
{
}

BOOL CDoSqlScriptsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsView drawing

void CDoSqlScriptsView::OnDraw(CDC* pDC)
{
	CDoSqlScriptsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsView printing

BOOL CDoSqlScriptsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDoSqlScriptsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDoSqlScriptsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsView diagnostics

#ifdef _DEBUG
void CDoSqlScriptsView::AssertValid() const
{
	CView::AssertValid();
}

void CDoSqlScriptsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDoSqlScriptsDoc* CDoSqlScriptsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoSqlScriptsDoc)));
	return (CDoSqlScriptsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsView message handlers
