// DlgCfgSwitchDefaultPolicyGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgSwitchDefaultPolicyGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchDefaultPolicyGrp dialog


CDlgCfgSwitchDefaultPolicyGrp::CDlgCfgSwitchDefaultPolicyGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgSwitchDefaultPolicyGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgSwitchDefaultPolicyGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgSwitchDefaultPolicyGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgSwitchDefaultPolicyGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgSwitchDefaultPolicyGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgSwitchDefaultPolicyGrp)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgCfgSwitchDefaultPolicyGrp::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchDefaultPolicyGrp message handlers



 BOOL CDlgCfgSwitchDefaultPolicyGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	bGetDefSnmpPolicy(  NULL,  &pQyMc->encCtx,  &m_var.policy  );

	SetDlgItemText(  IDC_STATIC_snmpVer,  CString(  m_var.policy.snmpVer  )  );
	SetDlgItemText(  IDC_EDIT_getCommunity,  CString(  m_var.policy.getCommunity  )  );
	SetDlgItemText(  IDC_EDIT_setCommunity,  CString(  m_var.policy.setCommunity  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgSwitchDefaultPolicyGrp::OnOK() 
{
	// TODO: Add extra validation here
	QY_SNMPOBJPOLICY_RCD	policy,  *  pPolicy  =  &policy;
	QY_MC	*	pQyMc	=  QY_GET_GBUF(  );
	TCHAR					tBuf[1024];

	memset(  &policy,  0,  sizeof(  policy  )  );
	GetDlgItemText(  IDC_STATIC_snmpVer,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  policy.snmpVer,  sizeof(  policy.snmpVer  )  );
	GetDlgItemText(  IDC_EDIT_getCommunity,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  policy.getCommunity,  sizeof(  policy.getCommunity  )  );
	GetDlgItemText(  IDC_EDIT_setCommunity,    tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  policy.setCommunity,  sizeof(  policy.setCommunity  )  );

	trim(  pPolicy->snmpVer  );
	trim(  pPolicy->getCommunity  );
	trim(  pPolicy->setCommunity  );

	if  (  !pPolicy->getCommunity[0]  )  _snprintf(  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  ),  CONST_defCommunityRo  );
	if  (  !pPolicy->setCommunity[0]  )  _snprintf(  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  ),  CONST_defCommunityRw  );

	if  (  memcmp(  pPolicy,  &m_var.policy,  sizeof(  m_var.policy  )  )  )  {
		if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifModifyDefaultSnmpPolicy  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;
		bSetDefSnmpPolicy(  NULL,  &pQyMc->encCtx,  pPolicy  );
	}
	
	CDialog::OnOK();
}

void CDlgCfgSwitchDefaultPolicyGrp::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
