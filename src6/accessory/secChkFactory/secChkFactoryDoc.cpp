// secChkFactoryDoc.cpp : implementation of the CSecChkFactoryDoc class
//

#include "stdafx.h"
#include "secChkFactory.h"

#include "secChkFactoryDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryDoc

IMPLEMENT_DYNCREATE(CSecChkFactoryDoc, CDocument)

BEGIN_MESSAGE_MAP(CSecChkFactoryDoc, CDocument)
	//{{AFX_MSG_MAP(CSecChkFactoryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryDoc construction/destruction

CSecChkFactoryDoc::CSecChkFactoryDoc()
{
	// TODO: add one-time construction code here

}

CSecChkFactoryDoc::~CSecChkFactoryDoc()
{
}

BOOL CSecChkFactoryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryDoc serialization

void CSecChkFactoryDoc::Serialize(CArchive& ar)
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
// CSecChkFactoryDoc diagnostics

#ifdef _DEBUG
void CSecChkFactoryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSecChkFactoryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecChkFactoryDoc commands
