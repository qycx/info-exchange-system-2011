// DlgCfgInterMonIp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"bhbSrc1CommProc.h"
#include	"qymc.h"
#include	"DlgCfgInterMonIp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgInterMonIp dialog


CDlgCfgInterMonIp::CDlgCfgInterMonIp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgInterMonIp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgInterMonIp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgInterMonIp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgInterMonIp)
	DDX_Control(pDX, IDC_IPADDRESS_INTER1, m_interMonIp1);
	DDX_Control(pDX, IDC_IPADDRESS_INTER0, m_interMonIp0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgInterMonIp, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgInterMonIp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgInterMonIp message handlers

BOOL CDlgCfgInterMonIp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char	buf[128];
	
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTERMON_KEY  ),  _T(  CONST_regValName_newInterMonIp0  ),  buf,  sizeof(  buf  )  )  )  {
		m_var.ulInterMonIp0  =  inet_addr(  buf  );
	}
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTERMON_KEY  ),  _T(  CONST_regValName_newInterMonIp1  ),  buf,  sizeof(  buf  )  )  )  {
		m_var.ulInterMonIp1  =  inet_addr(  buf  );
	}

	if  (  bulIpValid(  m_var.ulInterMonIp0  )  )  this->m_interMonIp0.SetAddress(  qyntohl(  m_var.ulInterMonIp0  )  );
	if  (  bulIpValid(  m_var.ulInterMonIp1  )  )  this->m_interMonIp1.SetAddress(  qyntohl(  m_var.ulInterMonIp1  )  );

	
	return  TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgInterMonIp::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	unsigned  long  ulInterMonIp0,  ulInterMonIp1;

	this->m_interMonIp0.GetAddress(  ulInterMonIp0  );  ulInterMonIp0  =  qyhtonl(  ulInterMonIp0  );
	this->m_interMonIp1.GetAddress(  ulInterMonIp1  );  ulInterMonIp1  =  qyhtonl(  ulInterMonIp1  );

	if  (  ulInterMonIp0  !=  m_var.ulInterMonIp0  )  {
		if  (  ulInterMonIp0  &&  !bulIpValid(  ulInterMonIp0  )  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipWrong  )  );  
			this->m_interMonIp0.SetFocus(  );
			return;
		}
	}
	if  (  ulInterMonIp1  !=  m_var.ulInterMonIp1  )  {
		if  (  ulInterMonIp1  &&  !bulIpValid(  ulInterMonIp1  )  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipWrong  )  );  
			this->m_interMonIp1.SetFocus(  );
			return;
		}
	}

	if  (  ulInterMonIp0  !=  m_var.ulInterMonIp0  )  {
		if  (  !ulInterMonIp0  )  qyDelRegCfg(  _T(  ROOT_AWM_INTERMON_KEY  ),  _T(  CONST_regValName_newInterMonIp0  )  );
		else  qySetRegCfg(  _T(  ROOT_AWM_INTERMON_KEY  ),  _T(  CONST_regValName_newInterMonIp0  ),  CString(  inet_ntoa(  *(  in_addr  *  )&ulInterMonIp0  )  )  );
	}

	if  (  ulInterMonIp1  !=  m_var.ulInterMonIp1  )  {
		if  (  !ulInterMonIp1  )  qyDelRegCfg(  _T(  ROOT_AWM_INTERMON_KEY  ),  _T(  CONST_regValName_newInterMonIp1  )  );
		else  qySetRegCfg(  _T(  ROOT_AWM_INTERMON_KEY  ),  _T(  CONST_regValName_newInterMonIp1  ),  CString(  inet_ntoa(  *(  in_addr  *  )&ulInterMonIp1  )  )  );
	}


	

	
	CDialog::OnOK();
}



