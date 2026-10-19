// kkDoc.cpp : implementation of the CKkDoc class
//

#include "stdafx.h"
#include "kk.h"

#include "kkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKkDoc

IMPLEMENT_DYNCREATE(CKkDoc, CDocument)

BEGIN_MESSAGE_MAP(CKkDoc, CDocument)
	//{{AFX_MSG_MAP(CKkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKkDoc construction/destruction

CKkDoc::CKkDoc()
{
	// TODO: add one-time construction code here

}

CKkDoc::~CKkDoc()
{
}

BOOL CKkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKkDoc serialization

void CKkDoc::Serialize(CArchive& ar)
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
// CKkDoc diagnostics

#ifdef _DEBUG
void CKkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKkDoc commands
