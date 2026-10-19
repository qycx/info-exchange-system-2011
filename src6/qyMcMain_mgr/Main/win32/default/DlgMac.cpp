// DlgMac.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"QyRestrictEdit.h"
#include	"qymc.h"
#include	"DlgMac.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMac dialog


CDlgMac::CDlgMac(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMac::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMac)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgMac::bSetDlgInfo(  int  type,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  okName,  LPCTSTR  cancelName  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 if  (  title  )  _sntprintf(  m_var.title,  mycountof(  m_var.title  ),  _T(  "%s"  ),  title  );
	 if  (  okName  )  lstrcpyn(  m_var.okName,  okName,  mycountof(  m_var.okName  )  );
	 if  (  cancelName  )  lstrcpyn(  m_var.cancelName,  cancelName,  mycountof(  m_var.cancelName  )  );
	 
	 return  TRUE;
}


void CDlgMac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMac)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMac, CDialog)
	//{{AFX_MSG_MAP(CDlgMac)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMac message handlers

BOOL CDlgMac::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int		idc;
	int		cnt		=	0;
	int		maxBytes  =  12;

	idc  =  IDC_EDIT_mac;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitXdigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );

	if  (  m_var.title[0]  )  SetWindowText(  CString(  m_var.title  )  );
	if  (  m_var.okName[0]  )  SetDlgItemText(  IDOK,  CString(  m_var.okName  )  );
	if  (  m_var.cancelName[0]  )  SetDlgItemText(  IDCANCEL,  CString(  m_var.cancelName  )  );
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMac::OnOK() 
{
	CString		str;
	
	GetDlgItemText(  IDC_EDIT_mac,  str  );  myTChar2Str(  str,  m_var.mac,  sizeof(  m_var.mac  )  );
	if  (  !bMacValid(  m_var.mac  )  )  {
		AfxMessageBox(  _T(  "MAC输入不正确, 格式如：001122334455"  )  );  return;
	}
	
	CDialog::OnOK();
}
