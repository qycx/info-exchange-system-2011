// TestP2.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "TestP2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestP2 property page

IMPLEMENT_DYNCREATE(CTestP2, CPropertyPage)

CTestP2::CTestP2() : CPropertyPage(CTestP2::IDD)
{
	//{{AFX_DATA_INIT(CTestP2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTestP2::~CTestP2()
{
}

void CTestP2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestP2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestP2, CPropertyPage)
	//{{AFX_MSG_MAP(CTestP2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestP2 message handlers

BOOL CTestP2::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//  ((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK  |  PSWIZB_FINISH);

	CComboBox  *  pCb  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_select  );

	OutputDebugString(  "OnSetActive\n"  );

	pCb->AddString(  "11"  );
	pCb->AddString(  "22"  );

	pCb->SetCurSel(  1  );

	return CPropertyPage::OnSetActive();
}
