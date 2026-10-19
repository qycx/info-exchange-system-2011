// DlgAddSwitchToGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qymc.h"
#include	"DlgAddSwitchToGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddSwitchToGrp dialog


CDlgAddSwitchToGrp::CDlgAddSwitchToGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddSwitchToGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddSwitchToGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgAddSwitchToGrp::bSetDlgInfo(  int  type,  HWND  hParent,  char  *  title,  char  *  okName,  char  *  cancelName  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 if  (  title  )  _snprintf(  m_var.title,  sizeof(  m_var.title  ),  "%s",  title  );
	 if  (  okName  )  _snprintf(  m_var.okName,  sizeof(  m_var.okName  ),  "%s",  okName  );
	 if  (  cancelName  )  _snprintf(  m_var.cancelName,  sizeof(  m_var.cancelName  ),  "%s",  cancelName  );
	 
	 return  TRUE;
}


 void  CDlgAddSwitchToGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddSwitchToGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddSwitchToGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgAddSwitchToGrp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddSwitchToGrp message handlers

BOOL CDlgAddSwitchToGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.title[0]  )  SetWindowText(  CString(  m_var.title  )  );
	if  (  m_var.okName[0]  )  SetDlgItemText(  IDOK,  CString(  m_var.okName  )  );
	if  (  m_var.cancelName[0]  )  SetDlgItemText(  IDCANCEL,  CString(  m_var.cancelName  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



 void  CDlgAddSwitchToGrp::OnOK() 
{
	struct  in_addr			tmpInAddr;
	long					hStartIp;
	QY_SNMPOBJPOLICY_RCD	snmpObjPolicy;
	TCHAR					tBuf[1024];
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	

	memset(  &snmpObjPolicy,  0,  sizeof(  snmpObjPolicy  )  );
	if  (  4  !=  ::SendMessage(  GetDlgItem(  IDC_IP  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&hStartIp  )  )  {
		 AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipWrong  )  );
		 GetDlgItem(  IDC_IP  )->SetFocus(  );
		 return;
	 }
	 tmpInAddr.s_addr  =  qyhtonl(  hStartIp  );
	 _snprintf(  m_var.ipBuf,  sizeof(  m_var.ipBuf  ),  "%s",  inet_ntoa(  tmpInAddr  )  );
	 GetDlgItemText(  IDC_EDIT_cusName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 lstrcpyn(  snmpObjPolicy.cusName,  tBuf,  mycountof(  snmpObjPolicy.cusName  )  );
	
	if  (  m_var.type  ==  CONST_qyDlgType_continuousAdd  )  {
		QY_WMBUF_ADDIP		tmpComm;

		memset(  &tmpComm,  0,  sizeof(  tmpComm  )  );
		tmpComm.uiType  =  CONST_qyWmParam_addIp;
		_snprintf(  tmpComm.ipBuf,  sizeof(  tmpComm.ipBuf  ),  "%s",  m_var.ipBuf  );
		lstrcpyn(  tmpComm.desBuf,  snmpObjPolicy.cusName,  mycountof(  tmpComm.desBuf  )  );
		::SendMessage(  m_var.hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&tmpComm  );
		GetDlgItem(  IDC_IP  )->SendMessage(  IPM_CLEARADDRESS,  0,  0  );
		GetDlgItem(  IDC_IP  )->SendMessage(  IPM_SETFOCUS,  0,  0  );
		SetDlgItemText(  IDC_EDIT_cusName,  _T(  ""  )  );
		return;
	}

	CDialog::OnOK();
}





