// DlgVerifyPhoneList.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgVerifyPhoneList.h"
#include	".\dlgverifyphonelist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVerifyPhoneList dialog


CDlgVerifyPhoneList::CDlgVerifyPhoneList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVerifyPhoneList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVerifyPhoneList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgVerifyPhoneList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVerifyPhoneList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVerifyPhoneList, CDialog)
	//{{AFX_MSG_MAP(CDlgVerifyPhoneList)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_deny, OnBnClickedButtondeny)
	ON_BN_CLICKED(IDC_BUTTON_refresh, OnBnClickedButtonrefresh)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVerifyPhoneList message handlers

 QY_COLUMNINFO  CONST_phoneListColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "Phone number"  ),			SQL_CHAR,	LVCFMT_LEFT,	150,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Name"  ),				SQL_CHAR,	LVCFMT_LEFT,	180,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Messenger ID"  ),		SQL_CHAR,	LVCFMT_LEFT,	180,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};


BOOL CDlgVerifyPhoneList::OnInitDialog()
{
	CDialog::OnInitDialog();

	int							iErr		=	-1;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CListCtrl				*	pListCtrl	=	NULL;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	QY_SERVICEGUI_INFO	*	pSci				=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  goto  errLabel;
	m_var.pProcInfo		=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !m_var.pProcInfo  )  goto  errLabel;

	//  
	m_var.idcList  =  IDC_LIST_phone;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	//  GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	m_var.pColumns  =  CONST_phoneListColumns;
	

	
	int  i;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for  (  i  =  0;  m_var.pColumns[i].type  !=  -1;  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	m_var.pColumns[i].label;
		   lvc.cx			=	m_var.pColumns[i].width;
		   lvc.fmt			=	m_var.pColumns[i].fmt;
		   pListCtrl->InsertColumn(  i,  &lvc  );
	}
	m_var.nFields  =  i;


	// TODO:  在此添加额外的初始化
	SetTimer(  1,  1000,  NULL  );

	GetDlgItem(  IDOK  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_BUTTON_deny  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_BUTTON_refresh  )->EnableWindow(  FALSE  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgVerifyPhoneList::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return;
	MC_VAR_isCli			*	pProcInfo		=	(  MC_VAR_isCli  *  )pSci->pVar;
	TCHAR					tStatus[256]	=	_T(  "Status: "  );
	CListCtrl			*	pListCtrl		=	NULL;

	pListCtrl  =  (  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	if  (  pProcInfo->bPhoneMsgrListNeedRefreshed  )  {
		_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "Wait for re-downloading"  )  );
		SetDlgItemText(  IDC_STATIC_status,  tStatus  );
		return;
	}

	if  (  !pProcInfo->bPhoneModuleLoaded  )  {
		_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "%s sm module unloaded"  ),  tStatus  );
		SetDlgItemText(  IDC_STATIC_status,  tStatus  );
		return;
	}

	if  (  !pProcInfo->bPhoneMsgrListDownloaded  )  {
		_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "%s trust phone numbers have not yet downloaded , just [ %d ] downloaded"  ),  tStatus,  pProcInfo->phoneMsgrQ.uiQNodes  );
		SetDlgItemText(  IDC_STATIC_status,  tStatus  );
		//
		return;
	}

	if  (  !m_var.bListLoaded  )  {
		CQySyncObj					syncObj;
		int							i;
		int							nItem;
		RETRIEVE_PHONE_MSGR		*	pElem;
		int							index;
		TCHAR						tBuf[255  +  1];

		if  (  syncObj.sync(  pProcInfo->phoneMsgrQ.cfg.mutexName_prefix  )  )  goto  errLabel;

		for  (  i  =  0;  i  <  (  int  )pProcInfo->phoneMsgrQ.uiQNodes;  i  ++  )  {
			 pElem  =  (  (  RETRIEVE_PHONE_MSGR  **  )pProcInfo->ppPhoneMsgrs_sortedByDevIdStr  )[i];
			
			 nItem  =  i;  index  =  0;
			 pListCtrl->InsertItem(  nItem,  pElem->wDevIdStr  );			 
			 index  ++  ;  pListCtrl->SetItemText(  nItem,  index,  pElem->displayName  );		
			 index  ++  ;  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pElem->idInfo.ui64Id  );  pListCtrl->SetItemText(  nItem,  index,  tBuf  );  
		}

		m_var.bListLoaded  =  TRUE;
	}


	if  (  pProcInfo->bPhoneMsgrListVerified  )  {
		if  (  pProcInfo->bPhoneMsgrListAccepted  )  _sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "%s the following phone numbers are verified"  ),  tStatus  );
		else  _sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "%s the following phone numbers are refused"  ),  tStatus  );
		SetDlgItemText(  IDC_STATIC_status,  tStatus  );
		//
		GetDlgItem(  IDC_BUTTON_refresh  )->EnableWindow(  FALSE  );
		//
		return;
	}

	_sntprintf(  tStatus,  mycountof(  tStatus  ),  _T(  "%s the following phone numbers need to verify"  ),  tStatus  );
	SetDlgItemText(  IDC_STATIC_status,  tStatus  );

	GetDlgItem(  IDOK  )->EnableWindow(  TRUE  );
	GetDlgItem(  IDC_BUTTON_deny  )->EnableWindow(  TRUE  );
	GetDlgItem(  IDC_BUTTON_refresh  )->EnableWindow(  TRUE  );


errLabel:

	CDialog::OnTimer(nIDEvent);
}








void CDlgVerifyPhoneList::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if  (  AfxMessageBox(  _T(  "Are you sure to verify these phone numbers?"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	if  (  m_var.pProcInfo  )  {
		m_var.pProcInfo->bPhoneMsgrListVerified  =  TRUE;
		m_var.pProcInfo->bPhoneMsgrListAccepted  =  TRUE;
		// 给各模块都通知一下已下载完毕，并确认的话。


	}

	OnOK();
}

void CDlgVerifyPhoneList::OnBnClickedButtondeny()
{	
	// TODO: 在此添加控件通知处理程序代码
	if  (  AfxMessageBox(  _T(  "Are you sure to refuse these phone numbers?"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	if  (  m_var.pProcInfo  )  {
		m_var.pProcInfo->bPhoneMsgrListVerified  =  TRUE;
	}

	OnOK();
}

 void CDlgVerifyPhoneList::OnBnClickedButtonrefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	if  (  m_var.pProcInfo->bPhoneMsgrListVerified  )  {
		qyShowHint(  _T(  "Cannot refresh because these phose numbers have already been verified"  )  );  return;	//  已经确认后，就不能再刷新了
	}
	if  (  !m_var.pProcInfo->bPhoneMsgrListDownloaded  )  {
		qyShowHint(  _T(  "Cannot refresh because the phone numbers have not yet been downloaded"  )  );  return;	//  已经确认后，就不能再刷新了
	}

	//  先清空显示。
	CListCtrl			*	pListCtrl		=	NULL;

	pListCtrl  =  (  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	pListCtrl->DeleteAllItems(  );
	m_var.bListLoaded  =  FALSE;

	//  这就表明，又需要下载了
	m_var.pProcInfo->bPhoneMsgrListNeedRefreshed  =  TRUE;

	//
	GetDlgItem(  IDOK  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_BUTTON_deny  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_BUTTON_refresh  )->EnableWindow(  FALSE  );
	  

}


