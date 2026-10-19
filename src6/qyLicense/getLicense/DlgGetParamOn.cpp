// DlgGetParamOn.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "DlgGetParamOn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetParamOn dialog


CDlgGetParamOn::CDlgGetParamOn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetParamOn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetParamOn)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgGetParamOn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetParamOn)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetParamOn, CDialog)
	//{{AFX_MSG_MAP(CDlgGetParamOn)
	ON_BN_CLICKED(IDC_BUTTON_on, OnBUTTONon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetParamOn message handlers

void CDlgGetParamOn::OnBUTTONon() 
{
	// TODO: Add your control notification handler code here
	
}
