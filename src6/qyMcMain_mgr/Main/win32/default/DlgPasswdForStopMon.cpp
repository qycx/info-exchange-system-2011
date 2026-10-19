// DlgPasswdForStopMon.cpp : implementation file
//

#include	"stdafx.h"
#include	"qymcMainCommon.h"
#include	"myresource.h"
#include	"DlgPasswdForStopMon.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswdForStopMon dialog


CDlgPasswdForStopMon::CDlgPasswdForStopMon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswdForStopMon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPasswdForStopMon)
	m_passwd = _T("");
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

BOOL  CDlgPasswdForStopMon::bSetDlgInfo(  char  *  hint  )
{
	_snprintf(  m_var.hint,  sizeof(  m_var.hint  ),  "%s",  hint  );

	return  TRUE;
}


void CDlgPasswdForStopMon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPasswdForStopMon)
	DDX_Text(pDX, IDC_EDIT_passwdForStopMon, m_passwd);
	DDV_MaxChars(pDX, m_passwd, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPasswdForStopMon, CDialog)
	//{{AFX_MSG_MAP(CDlgPasswdForStopMon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswdForStopMon message handlers

void CDlgPasswdForStopMon::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(  TRUE  );
	
	CDialog::OnOK();
}

BOOL CDlgPasswdForStopMon::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC	*		pQyMc		=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	SetDlgItemText(  IDC_STATIC_passwdForStopMon,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_passwdForStopMon  )  );
	SetDlgItemText(  IDOK,  getResStr(  0,  &pQyMc->cusRes,  IDOK  )  );  
	SetDlgItemText(  IDCANCEL,  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  )  );  

	
	// TODO: Add extra initialization here
	SetDlgItemText(  IDC_STATIC_hint,  CString(  m_var.hint  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
