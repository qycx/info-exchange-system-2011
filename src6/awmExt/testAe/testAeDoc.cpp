// testAeDoc.cpp : implementation of the CTestAeDoc class
//

#include "stdafx.h"
#include "testAe.h"

#include "testAeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAeDoc

IMPLEMENT_DYNCREATE(CTestAeDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestAeDoc, CDocument)
	//{{AFX_MSG_MAP(CTestAeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAeDoc construction/destruction

CTestAeDoc::CTestAeDoc()
{
	// TODO: add one-time construction code here

}

CTestAeDoc::~CTestAeDoc()
{
}

BOOL CTestAeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestAeDoc serialization

void CTestAeDoc::Serialize(CArchive& ar)
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
// CTestAeDoc diagnostics

#ifdef _DEBUG
void CTestAeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestAeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestAeDoc commands
