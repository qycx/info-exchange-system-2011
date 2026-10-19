// captureDoc.cpp : implementation of the CCaptureDoc class
//

#include "stdafx.h"
#include "capture.h"

#include "captureDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureDoc

IMPLEMENT_DYNCREATE(CCaptureDoc, CDocument)

BEGIN_MESSAGE_MAP(CCaptureDoc, CDocument)
	//{{AFX_MSG_MAP(CCaptureDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureDoc construction/destruction

CCaptureDoc::CCaptureDoc()
{
	// TODO: add one-time construction code here

}

CCaptureDoc::~CCaptureDoc()
{
}

BOOL CCaptureDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCaptureDoc serialization

void CCaptureDoc::Serialize(CArchive& ar)
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
// CCaptureDoc diagnostics

#ifdef _DEBUG
void CCaptureDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCaptureDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaptureDoc commands
