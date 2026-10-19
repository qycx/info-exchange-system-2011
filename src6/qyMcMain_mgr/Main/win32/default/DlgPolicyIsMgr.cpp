// DlgPolicyIsMgr.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPolicyIsMgr.h"
#include ".\dlgpolicyismgr.h"

#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyIsMgr dialog


CDlgPolicyIsMgr::CDlgPolicyIsMgr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPolicyIsMgr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPolicyIsMgr)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgPolicyIsMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPolicyIsMgr)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPolicyIsMgr, CDialog)
	//{{AFX_MSG_MAP(CDlgPolicyIsMgr)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyIsMgr message handlers

BOOL CDlgPolicyIsMgr::OnInitDialog()
{
	CDialog::OnInitDialog();
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci	=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	if  (  !pSci  )  return  FALSE;

	// TODO:  在此添加额外的初始化
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	SetDlgItemText(  IDC_CHECK_ucbUseDynBmpRule,  getResStr(  0,  &pQyMc->cusRes,  bQnmDemo(  )  ?  CONST_resId_ucbUseDynBmpRule_demo  :  CONST_resId_ucbUseDynBmpRule  )  );

	bGetPolicyIsMgr(  HKEY_LOCAL_MACHINE,  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  &m_var.policy  );

	(  (  CButton  *  )GetDlgItem(  IDC_CHECK_ucbLogImMsg  )  )->SetCheck(  !m_var.policy.ucbLogImMsg  ?  0  :  1  );

	TCHAR	tBuf[255  +  1];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.policy.startTmpMessengerId.ui64Id  );
	SetDlgItemText(  IDC_EDIT_startTmpMessengerId,  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.policy.startTmpMessengerId.ui64Id  +  m_var.policy.uiMaxCnt_tmpMessengers  -  1  );	
	SetDlgItemText(  IDC_EDIT_endTmpMessengerId,  tBuf  );

	GetDlgItem(  IDC_EDIT_startTmpMessengerId  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_EDIT_endTmpMessengerId  )->EnableWindow(  FALSE  );

	SetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch,  m_var.policy.usTimeoutInMsToSwitch  );

	SetDlgItemInt(  IDC_EDIT_usMaxMsgs_allowedToSwitchToTalkChannel_robot,  m_var.policy.usMaxMsgs_allowedToSwitchToTalkChannel_robot  );
	SetDlgItemInt(  IDC_EDIT_usMaxMsgs_allowedToSwitchToTalkChannel_media,  m_var.policy.usMaxMsgs_allowedToSwitchToTalkChannel_media  );

	//  2009/09/17
	(  (  CButton  *  )GetDlgItem(  IDC_CHECK_ucbUseDynBmpRule  )  )->SetCheck(  !m_var.policy.ucbUseDynBmpRule  ?  0  :  1  );
	if  (  !bQnmDemo(  )  )  GetDlgItem(  IDC_CHECK_ucbUseDynBmpRule  )->EnableWindow(  FALSE  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgPolicyIsMgr::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	POLICY_isMgr		policy;
	TCHAR				tBuf[256];
	int					idc;
	TCHAR			*	pRegVal				=	NULL;

	memset(  &policy,  0,  sizeof(  policy  )  );

	if  (   (  (  CButton  *  )GetDlgItem(  IDC_CHECK_ucbLogImMsg  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_ucbLogImMsg  ),  _T(  "1"  )  );
		}
	else  {
		  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_ucbLogImMsg  )  );
	}

	policy.usTimeoutInMsToSwitch  =  GetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch,  NULL,  FALSE  );
	qySetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  CONST_qyRootKey_qnmScheduler_mis  ),  CONST_regValName_usTimeoutInMsToSwitch, _ltot(  policy.usTimeoutInMsToSwitch,  tBuf,  10  )  );
	

	idc  =  IDC_EDIT_usMaxMsgs_allowedToSwitchToTalkChannel_robot;
	policy.usMaxMsgs_allowedToSwitchToTalkChannel_robot  =  GetDlgItemInt(  IDC_EDIT_usMaxMsgs_allowedToSwitchToTalkChannel_robot,  NULL,  FALSE  );
	if  (  !policy.usMaxMsgs_allowedToSwitchToTalkChannel_robot  ||  policy.usMaxMsgs_allowedToSwitchToTalkChannel_robot  >  MAX_usMaxMsgs_allowedToSwitchToTalkChannel  )  {
		qyShowHint(  _T(  "The valid value is between [ 1, %d ]"  ),  MAX_usMaxMsgs_allowedToSwitchToTalkChannel  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_usMaxMsgs_allowedToSwitchToTalkChannel_media;
	policy.usMaxMsgs_allowedToSwitchToTalkChannel_media  =  GetDlgItemInt(  IDC_EDIT_usMaxMsgs_allowedToSwitchToTalkChannel_media,  NULL,  FALSE  );
	if  (  !policy.usMaxMsgs_allowedToSwitchToTalkChannel_media  ||  policy.usMaxMsgs_allowedToSwitchToTalkChannel_media  >  MAX_usMaxMsgs_allowedToSwitchToTalkChannel  )  {
		qyShowHint(  _T(  "The valid value is between [ 1, %d ]"  ),  MAX_usMaxMsgs_allowedToSwitchToTalkChannel  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	pRegVal  =  CONST_regValName_usMaxMsgs_allowedToSwitchToTalkChannel_robot;
	qySetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  CONST_qyRootKey_qnmScheduler_mis  ),  pRegVal, _ltot(  policy.usMaxMsgs_allowedToSwitchToTalkChannel_robot,  tBuf,  10  )  );
	
	pRegVal  =  CONST_regValName_usMaxMsgs_allowedToSwitchToTalkChannel_media;
	qySetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  CONST_qyRootKey_qnmScheduler_mis  ),  pRegVal, _ltot(  policy.usMaxMsgs_allowedToSwitchToTalkChannel_media,  tBuf,  10  )  );

	//  2009/09/17
	if  (   (  (  CButton  *  )GetDlgItem(  IDC_CHECK_ucbUseDynBmpRule  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_ucbUseDynBmpRule  ),  _T(  "1"  )  );
		}
	else  {
		  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_ucbUseDynBmpRule  )  );
	}


	CDialog::OnOK();
}

void CDlgPolicyIsMgr::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
