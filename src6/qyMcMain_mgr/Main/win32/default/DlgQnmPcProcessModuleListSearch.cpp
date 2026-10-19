// DlgQnmPcProcessModuleListSearch.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmPcProcessModuleListSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcProcessModuleListSearch dialog


CDlgQnmPcProcessModuleListSearch::CDlgQnmPcProcessModuleListSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmPcProcessModuleListSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmPcProcessModuleListSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

BOOL  CDlgQnmPcProcessModuleListSearch::bSetDlgInfo(  int  iDlgType,  LPCTSTR  title,  LPCTSTR  hint  )
{
	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	if  (  hint  )  lstrcpyn(  m_var.hint,  hint,  mycountof(  m_var.hint  )  );

	return  TRUE;
}


void CDlgQnmPcProcessModuleListSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmPcProcessModuleListSearch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmPcProcessModuleListSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmPcProcessModuleListSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcProcessModuleListSearch message handlers

void CDlgQnmPcProcessModuleListSearch::OnOK() 
{
	// TODO: Add extra validation here
	
	GetDlgItemText(  IDC_EDIT_moduleName,  m_var.moduleName,  mycountof(  m_var.moduleName  )  );
	tTrim(  m_var.moduleName  );

	CDialog::OnOK();
}

BOOL CDlgQnmPcProcessModuleListSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.title[0]  )  SetWindowText(  m_var.title  );
	if  (  m_var.hint[0]  )  SetDlgItemText(  IDC_STATIC_qnmPcProcessModuleListSearch,  m_var.hint  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
