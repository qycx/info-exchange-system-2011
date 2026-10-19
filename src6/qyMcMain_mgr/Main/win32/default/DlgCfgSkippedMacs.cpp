// DlgCfgSkippedMacs.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgSkippedMacs.h"
#include	".\dlgcfgskippedmacs.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSkippedMacs dialog


CDlgCfgSkippedMacs::CDlgCfgSkippedMacs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgSkippedMacs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgSkippedMacs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgSkippedMacs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgSkippedMacs)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgSkippedMacs, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgSkippedMacs)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSkippedMacs message handlers

BOOL CDlgCfgSkippedMacs::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	QY_MC	*		pQyMc		=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	getSkippedMacs(  &m_var.skippedMacs  );

	SetDlgItemText(  IDC_EDIT_mac0,  CString(  m_var.skippedMacs.macs[0]  )  );
	SetDlgItemText(  IDC_EDIT_mac1,  CString(  m_var.skippedMacs.macs[1]  )  );
	SetDlgItemText(  IDC_EDIT_mac2,  CString(  m_var.skippedMacs.macs[2]  )  );
	SetDlgItemText(  IDC_EDIT_mac3,  CString(  m_var.skippedMacs.macs[3]  )  );
	SetDlgItemText(  IDC_EDIT_mac4,  CString(  m_var.skippedMacs.macs[4]  )  );



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCfgSkippedMacs::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	SKIPPED_MACS		skippedMacs;
	CString				str;
	char				buf[128];
	int					idc;
	int					i;
	char			*	pRegValName;

	memset(  &skippedMacs,  0,  sizeof(  skippedMacs  )  );

	i  =  0;  idc  =  IDC_EDIT_mac0;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  mycountof(  buf  )  );
	if  (  bMacValid(  buf  )  )  safeStrnCpy(  buf,  skippedMacs.macs[i],  mycountof(  skippedMacs.macs[i]  )  );
	//
	i  ++  ;  idc  =  IDC_EDIT_mac1;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  mycountof(  buf  )  );
	if  (  bMacValid(  buf  )  )  safeStrnCpy(  buf,  skippedMacs.macs[i],  mycountof(  skippedMacs.macs[i]  )  );
	//
	i  ++  ;  idc  =  IDC_EDIT_mac2;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  mycountof(  buf  )  );
	if  (  bMacValid(  buf  )  )  safeStrnCpy(  buf,  skippedMacs.macs[i],  mycountof(  skippedMacs.macs[i]  )  );
	//
	i  ++  ;  idc  =  IDC_EDIT_mac3;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  mycountof(  buf  )  );
	if  (  bMacValid(  buf  )  )  safeStrnCpy(  buf,  skippedMacs.macs[i],  mycountof(  skippedMacs.macs[i]  )  );
	//
	i  ++  ;  idc  =  IDC_EDIT_mac4;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  mycountof(  buf  )  );
	if  (  bMacValid(  buf  )  )  safeStrnCpy(  buf,  skippedMacs.macs[i],  mycountof(  skippedMacs.macs[i]  )  );

	if  (  memcmp(  &skippedMacs,  &m_var.skippedMacs,  sizeof(  m_var.skippedMacs  )  )  )  {
		if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;
		//
		i  =  0;  pRegValName =   CONST_regValName_skippedMac0;
		if  (  skippedMacs.macs[i][0]  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  ),  CString(  skippedMacs.macs[i]  )  );
		else  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  )  );
		//
		i  ++  ;  pRegValName =   CONST_regValName_skippedMac1;
		if  (  skippedMacs.macs[i][0]  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  ),  CString(  skippedMacs.macs[i]  )  );
		else  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  )  );
		//
		i  ++  ;  pRegValName =   CONST_regValName_skippedMac2;
		if  (  skippedMacs.macs[i][0]  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  ),  CString(  skippedMacs.macs[i]  )  );
		else  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  )  );
		//
		i  ++  ;  pRegValName =   CONST_regValName_skippedMac3;
		if  (  skippedMacs.macs[i][0]  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  ),  CString(  skippedMacs.macs[i]  )  );
		else  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  )  );
		//
		i  ++  ;  pRegValName =   CONST_regValName_skippedMac4;
		if  (  skippedMacs.macs[i][0]  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  ),  CString(  skippedMacs.macs[i]  )  );
		else  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegValName  )  );
		//
	}


	OnOK();
}
