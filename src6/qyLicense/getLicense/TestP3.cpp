// TestP3.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "TestP3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestP3 property page

IMPLEMENT_DYNCREATE(CTestP3, CPropertyPage)

CTestP3::CTestP3() : CPropertyPage(CTestP3::IDD)
{
	//{{AFX_DATA_INIT(CTestP3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTestP3::~CTestP3()
{
}

void CTestP3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestP3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestP3, CPropertyPage)
	//{{AFX_MSG_MAP(CTestP3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestP3 message handlers
