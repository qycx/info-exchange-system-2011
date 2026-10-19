// TestP1.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "TestP1.h"
#include	"testp3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestP1 property page

IMPLEMENT_DYNCREATE(CTestP1, CPropertyPage)

CTestP1::CTestP1() : CPropertyPage(CTestP1::IDD)
{
	//{{AFX_DATA_INIT(CTestP1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTestP1::~CTestP1()
{
}

void CTestP1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestP1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestP1, CPropertyPage)
	//{{AFX_MSG_MAP(CTestP1)
		// NOTE: the ClassWizard will add message map macros here
		ON_BN_CLICKED(IDOK, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestP1 message handlers

BOOL CTestP1::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class

	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);
	//  ((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);
	//  ((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_FINISH);


	return CPropertyPage::OnSetActive();
}

void CTestP1::OnOK() 
{

	return;
	
	CPropertyPage::OnOK();
}


void  CTestP1::OnButton1( )
{
	//  int	i;
	AfxMessageBox(  "kk"  );

}

LRESULT CTestP1::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class

	
	return  CTestP3::IDD;
	//  return CPropertyPage::OnWizardNext();
}
