// licenseToolDoc.cpp : implementation of the CLicenseToolDoc class
//

#include "stdafx.h"
#include "licenseTool.h"

#include "licenseToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolDoc

IMPLEMENT_DYNCREATE(CLicenseToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CLicenseToolDoc, CDocument)
	//{{AFX_MSG_MAP(CLicenseToolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolDoc construction/destruction

CLicenseToolDoc::CLicenseToolDoc()
{
	// TODO: add one-time construction code here

}

CLicenseToolDoc::~CLicenseToolDoc()
{
}

BOOL CLicenseToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLicenseToolDoc serialization

void CLicenseToolDoc::Serialize(CArchive& ar)
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
// CLicenseToolDoc diagnostics

#ifdef _DEBUG
void CLicenseToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLicenseToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLicenseToolDoc commands
