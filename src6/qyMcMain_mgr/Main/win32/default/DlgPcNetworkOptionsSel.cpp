// DlgPcNetworkOptionsSel.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPcNetworkOptionsSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPcNetworkOptionsSel dialog


CDlgPcNetworkOptionsSel::CDlgPcNetworkOptionsSel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPcNetworkOptionsSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPcNetworkOptionsSel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgPcNetworkOptionsSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPcNetworkOptionsSel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPcNetworkOptionsSel, CDialog)
	//{{AFX_MSG_MAP(CDlgPcNetworkOptionsSel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPcNetworkOptionsSel message handlers

BOOL CDlgPcNetworkOptionsSel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	QY_MC	*		pQyMc		=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPcNetworkOptionsSel::OnOK() 
{
	// TODO: Add extra validation here
	
	m_var.ucbPcAdapter  =  GetDlgItem(  IDC_CHECK_pcAdapter  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.ucbProxy  =  GetDlgItem(  IDC_CHECK_proxy  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.ucbComputer  =  GetDlgItem(  IDC_CHECK_computer  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.ucbWindowsUpdatePolicy  =  GetDlgItem(  IDC_CHECK_windowsUpdatePolicy  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;


	CDialog::OnOK();
}
