// DlgCfgSystemParams_is.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgSystemParams_is.h"
#include ".\dlgcfgsystemparams_is.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSystemParams_is dialog


CDlgCfgSystemParams_is::CDlgCfgSystemParams_is(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgSystemParams_is::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgSystemParams_is)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgSystemParams_is::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgSystemParams_is)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgSystemParams_is, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgSystemParams_is)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSystemParams_is message handlers

BOOL CDlgCfgSystemParams_is::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	QY_MC	*		pQyMc		=	QY_GET_GBUF(  );
	TCHAR			tBuf[256];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%d%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_nMaxConns  ),  getnMaxConns_is(  &pQyMc->licenseCtx  ),  _T(  "):"  )  );
	//	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "允许通信并发数(1-%d):"  ),  getnMaxConns_is(  &pQyMc->licenseCtx  )  );
	SetDlgItemText(  IDC_STATIC_nMaxConns,  tBuf  );

	//
	bGetQisIntervalParams(  HKEY_LOCAL_MACHINE,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  &m_var.intervalParams  );

	m_var.nMaxConns					=  getQnmnConns(  &pQyMc->licenseCtx,  pQyMc->iServiceId  );


	SetDlgItemInt(  IDC_EDIT_usIntervalInS_refreshRecentFriends,  m_var.intervalParams.usIntervalInS_refreshRecentFriends  );
	SetDlgItemInt(  IDC_EDIT_usIntervalInS_refreshContactList,  m_var.intervalParams.usIntervalInS_refreshContactList  );

	SetDlgItemInt(  IDC_EDIT_nMaxConns,	m_var.nMaxConns  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCfgSystemParams_is::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );
	int							idc;
	CString						str;
	char						buf[128];
	QIS_INTERVAL_PARAMS			intervalParams;
	unsigned  int				uiIntervalInS;
	unsigned  int				nMaxConns;							//  2006/08/18
	//	TCHAR						tBuf[128];

	memset(  &intervalParams,  0,  sizeof(  intervalParams  )  );

	idc  =  IDC_EDIT_usIntervalInS_refreshRecentFriends;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiIntervalInS  =  atol(  buf  );
	//
	if  (  uiIntervalInS  <  CONST_minInterval  ||  uiIntervalInS  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	intervalParams.usIntervalInS_refreshRecentFriends  =  uiIntervalInS;

	idc  =  IDC_EDIT_usIntervalInS_refreshContactList;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiIntervalInS  =  atol(  buf  );
	//
	if  (  uiIntervalInS  <  CONST_minInterval  ||  uiIntervalInS  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	intervalParams.usIntervalInS_refreshContactList  =  uiIntervalInS;

	//  2006/08/18
	idc  =  IDC_EDIT_nMaxConns;			//  2006/08/18
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	nMaxConns  =  atol(  buf  );
	//
	if  (  (  int  )nMaxConns  <=  0  ||  (  int  )nMaxConns  >  getnMaxConns_is(  &pQyMc->licenseCtx  )  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  1,  getnMaxConns_is(  &pQyMc->licenseCtx  )  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}


	if  (  m_var.intervalParams.usIntervalInS_refreshRecentFriends  !=  intervalParams.usIntervalInS_refreshRecentFriends  )  qySetRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_usIntervalInS_refreshRecentFriends  ),  CString(  ltoa(  intervalParams.usIntervalInS_refreshRecentFriends,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usIntervalInS_refreshContactList  !=  intervalParams.usIntervalInS_refreshContactList  )  qySetRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_usIntervalInS_refreshContactList  ),  CString(  ltoa(  intervalParams.usIntervalInS_refreshContactList,  buf,  10  )  )  );
	//
	if  (  m_var.nMaxConns  !=  nMaxConns  )  qySetRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_nMaxConns  ),  CString(  ltoa(  nMaxConns,  buf,  10  )  )  );


	CDialog::OnOK();
}

void CDlgCfgSystemParams_is::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
