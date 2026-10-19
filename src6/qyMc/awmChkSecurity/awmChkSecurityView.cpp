// awmChkSecurityView.cpp : implementation of the CAwmChkSecurityView class
//

#include "stdafx.h"
#include "awmChkSecurity.h"

#include "awmChkSecurityDoc.h"
#include "awmChkSecurityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityView

IMPLEMENT_DYNCREATE(CAwmChkSecurityView, CView)

BEGIN_MESSAGE_MAP(CAwmChkSecurityView, CView)
	//{{AFX_MSG_MAP(CAwmChkSecurityView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityView construction/destruction

CAwmChkSecurityView::CAwmChkSecurityView()
{
	// TODO: add construction code here

}

CAwmChkSecurityView::~CAwmChkSecurityView()
{
}

BOOL CAwmChkSecurityView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityView drawing

void CAwmChkSecurityView::OnDraw(CDC* pDC)
{
	CAwmChkSecurityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityView diagnostics

#ifdef _DEBUG
void CAwmChkSecurityView::AssertValid() const
{
	CView::AssertValid();
}

void CAwmChkSecurityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAwmChkSecurityDoc* CAwmChkSecurityView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAwmChkSecurityDoc)));
	return (CAwmChkSecurityDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityView message handlers
