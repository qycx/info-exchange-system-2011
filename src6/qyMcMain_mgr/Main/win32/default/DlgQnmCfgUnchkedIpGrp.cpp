// DlgQnmCfgUnchkedIpGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmCfgUnchkedIpGrp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgUnchkedIpGrp dialog


CDlgQnmCfgUnchkedIpGrp::CDlgQnmCfgUnchkedIpGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgUnchkedIpGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgUnchkedIpGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


void CDlgQnmCfgUnchkedIpGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgUnchkedIpGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}




 BOOL  CDlgQnmCfgUnchkedIpGrp::bSetDlgInfo(  int  type,  HWND  hParent,  char  *  title,  char  *  okName,  char  *  cancelName,  QY_DMITEM  *  pDesTable  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 if  (  title  )  _snprintf(  m_var.title,  sizeof(  m_var.title  ),  "%s",  title  );
	 if  (  okName  )  _snprintf(  m_var.okName,  sizeof(  m_var.okName  ),  "%s",  okName  );
	 if  (  cancelName  )  _snprintf(  m_var.cancelName,  sizeof(  m_var.cancelName  ),  "%s",  cancelName  );
	 if  (  pDesTable  )  m_var.pDesTable  =  pDesTable;
	 
	 return  TRUE;
}

BEGIN_MESSAGE_MAP(CDlgQnmCfgUnchkedIpGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgUnchkedIpGrp)
	ON_CBN_SELCHANGE(IDC_COMBO_des, OnSelchangeCOMBOdes)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgQnmCfgUnchkedIpGrp::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgUnchkedIpGrp message handlers

 BOOL CDlgQnmCfgUnchkedIpGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC		*  pQyMc	=  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	if  (  m_var.title[0]  )  SetWindowText(  CString(  m_var.title  )  );
	if  (  m_var.okName[0]  )  SetDlgItemText(  IDOK,  CString(  m_var.okName  )  );
	if  (  m_var.cancelName[0]  )  SetDlgItemText(  IDCANCEL,  CString(  m_var.cancelName  )  );
	if  (  m_var.pDesTable  )  {
		for  (  QY_DMITEM	*	pItem	=	m_var.pDesTable;  pItem->type  !=  -1;  pItem  ++   )  
			 GetDlgItem(  IDC_COMBO_des  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )pItem->des  );
		if  (  m_var.pDesTable[0].type  !=  -1  )  GetDlgItem(  IDC_COMBO_des  )->SendMessage(  CB_SETCURSEL,  0,  0  );
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgQnmCfgUnchkedIpGrp::OnSelchangeCOMBOdes() 
{
	CComboBox  *	pCombo  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_des  );
	int				iCurSel;

	if  (  !pCombo  )  return;
	iCurSel  =  pCombo->GetCurSel(  );
	if  (  iCurSel  ==  CB_ERR  )  return;
	GetDlgItem(  IDC_endIp  )->EnableWindow(  !iCurSel  );
	
}


 void  CDlgQnmCfgUnchkedIpGrp::OnOK() 
{
	struct  in_addr		tmpInAddr;
	unsigned  long		hStartIp,  hEndIp;
	int					iCurSel;
	CComboBox		*	pCombo		=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_des  );
	CString				str;

	MACRO_qyAssert(  pCombo,  _T(  "UnchkedIpGrp::OnOK"  )  );
	iCurSel  =  pCombo->GetCurSel(  );
	if  (  iCurSel  ==  CB_ERR  )  return;
	
	if  (  4  !=  ::SendMessage(  GetDlgItem(  IDC_startIp  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&hStartIp  )  )  {
		 qyShowHint(  _T(  "起始IP输入无效"  )  );
		 GetDlgItem(  IDC_startIp  )->SetFocus(  );
		 return;
	 }
	 tmpInAddr.s_addr  =  qyhtonl(  hStartIp  );
	 _snprintf(  m_var.startIpBuf,  sizeof(  m_var.startIpBuf  ),  "%s",  inet_ntoa(  tmpInAddr  )  );

	 hEndIp  =  hStartIp;
	 if  (  !iCurSel  )  {
		 if  (  4  ==  ::SendMessage(  GetDlgItem(  IDC_endIp  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&hEndIp  )  )  {
			 if  (  hEndIp  <  hStartIp  )  {
				 qyShowHint(  _T(  "结束IP应不小于起始IP"  )  );
				 GetDlgItem(  IDC_endIp  )->SetFocus(  );
				 return;
			 }
		 }
	 }
	 if  (  hEndIp  <  hStartIp  )  hEndIp  =  hStartIp;
	 tmpInAddr.s_addr  =  qyhtonl(  hEndIp  );
	 _snprintf(  m_var.endIpBuf,  sizeof(  m_var.endIpBuf  ),  "%s",  inet_ntoa(  tmpInAddr  )  );
			
	 if  (  m_var.type  ==  CONST_qyDlgType_continuousAdd  )  {
		QY_WMBUF_ADDIP		tmpComm;

		memset(  &tmpComm,  0,  sizeof(  tmpComm  )  );
		tmpComm.uiType  =  CONST_qyWmParam_addIp;
		_snprintf(  tmpComm.startIpBuf,  sizeof(  tmpComm.startIpBuf  ),  "%s",  m_var.startIpBuf  );
		_snprintf(  tmpComm.endIpBuf,  sizeof(  tmpComm.endIpBuf  ),  "%s",  m_var.endIpBuf  );
		GetDlgItemText(  IDC_COMBO_des,  str  );  lstrcpyn(  tmpComm.desBuf,  str,  mycountof(  tmpComm.desBuf  )  );
		if  (  ::SendMessage(  m_var.hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&tmpComm  )  !=  CONST_qyWmRc_ok  
			&&  tmpComm.errBuf[0]  )  
		{
			qyShowHint(  CString(  tmpComm.errBuf  )  );
		}
		GetDlgItem(  IDC_startIp  )->SendMessage(  IPM_CLEARADDRESS,  0,  0  );
		GetDlgItem(  IDC_endIp  )->SendMessage(  IPM_CLEARADDRESS,  0,  0  );
		GetDlgItem(  IDC_startIp  )->SendMessage(  IPM_SETFOCUS,  0,  0  );
		return;
	}


	CDialog::OnOK();

}



 void CDlgQnmCfgUnchkedIpGrp::OnBnClickedOk()
 {
	 // TODO: Add your control notification handler code here
	 OnOK();
 }
