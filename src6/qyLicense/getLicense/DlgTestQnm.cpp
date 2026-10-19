// DlgTestQnm.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "DlgTestQnm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestQnm dialog


CDlgTestQnm::CDlgTestQnm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestQnm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTestQnm)
	m_qwmSendTimes = _T("");
	m_qwmServerIp = _T("");
	//}}AFX_DATA_INIT
}


void CDlgTestQnm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTestQnm)
	DDX_Text(pDX, IDC_EDIT_qwmSendTimes, m_qwmSendTimes);
	DDX_Text(pDX, IDC_EDIT_qwmServerIp, m_qwmServerIp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTestQnm, CDialog)
	//{{AFX_MSG_MAP(CDlgTestQnm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTestQnm message handlers
