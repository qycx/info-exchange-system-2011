// DlgModuleKnowlegeOptions.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"myresource.h"
#include	"DlgModuleKnowlegeOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgModuleKnowlegeOptions dialog


CDlgModuleKnowlegeOptions::CDlgModuleKnowlegeOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModuleKnowlegeOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgModuleKnowlegeOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


BOOL  CDlgModuleKnowlegeOptions::bSetDlgInfo(  int  iDlgType,  LPCTSTR  unAuditedHint,  LPCTSTR  auditedHint  )
{
	if  (  unAuditedHint  )  lstrcpyn(  m_var.unAuditedHint,  unAuditedHint,  mycountof(  m_var.unAuditedHint  )  );
	if  (  auditedHint  )  lstrcpyn(  m_var.auditedHint,  auditedHint,  mycountof(  m_var.auditedHint  )  );

	return  TRUE;
}


void CDlgModuleKnowlegeOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgModuleKnowlegeOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgModuleKnowlegeOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgModuleKnowlegeOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgModuleKnowlegeOptions message handlers

BOOL CDlgModuleKnowlegeOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.unAuditedHint[0]  )  SetDlgItemText(  IDC_RADIO_unAudited,  m_var.unAuditedHint  );
	if  (  m_var.auditedHint[0]  )  SetDlgItemText(  IDC_RADIO_audited,  m_var.auditedHint  );

	GetDlgItem(  IDC_RADIO_unAudited  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgModuleKnowlegeOptions::OnOK() 
{
	// TODO: Add extra validation here

	if  (  GetDlgItem(  IDC_RADIO_audited  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  m_var.ucbAudited  =  TRUE;
		
	CDialog::OnOK();
}
