// awmChkSecurityDoc.cpp : implementation of the CAwmChkSecurityDoc class
//

#include "stdafx.h"
#include "awmChkSecurity.h"

#include "awmChkSecurityDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityDoc

IMPLEMENT_DYNCREATE(CAwmChkSecurityDoc, CDocument)

BEGIN_MESSAGE_MAP(CAwmChkSecurityDoc, CDocument)
	//{{AFX_MSG_MAP(CAwmChkSecurityDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityDoc construction/destruction

CAwmChkSecurityDoc::CAwmChkSecurityDoc()
{
	// TODO: add one-time construction code here

}

CAwmChkSecurityDoc::~CAwmChkSecurityDoc()
{
}

BOOL CAwmChkSecurityDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityDoc serialization

void CAwmChkSecurityDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityDoc diagnostics

#ifdef _DEBUG
void CAwmChkSecurityDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAwmChkSecurityDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityDoc commands
