// PpStatus.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "PpStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpStatus property page

IMPLEMENT_DYNCREATE(CPpStatus, CPropertyPage)

CPpStatus::CPpStatus() : CPropertyPage(CPpStatus::IDD)
{
	//{{AFX_DATA_INIT(CPpStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpStatus::~CPpStatus()
{
}

void CPpStatus::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpStatus, CPropertyPage)
	//{{AFX_MSG_MAP(CPpStatus)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpStatus message handlers
