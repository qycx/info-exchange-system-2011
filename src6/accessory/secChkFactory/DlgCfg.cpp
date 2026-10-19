// DlgCfg.cpp : implementation file
//

#include "stdafx.h"
#include "secChkFactory.h"
#include "DlgCfg.h"
#include	"secChkFactoryCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfg dialog


CDlgCfg::CDlgCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfg)
	m_qyRegToolDir = _T("");
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfg)
	DDX_Text(pDX, IDC_EDIT_secChkDir, m_qyRegToolDir);
	DDV_MaxChars(pDX, m_qyRegToolDir, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfg message handlers

void CDlgCfg::OnOK() 
{
	UpdateData(  TRUE  );

	MACRO_CStringTrim(  this->m_qyRegToolDir  );	
	if  (  m_qyRegToolDir.GetLength(  )  )  {
		DWORD  kk;

		kk  =  GetFileAttributes(  m_qyRegToolDir.GetBuffer(  0  )  );
		if  (  kk  ==  0xFFFFFFFF  )  {
			AfxMessageBox(  "配置的文件夹不存在。"  );
			return;
		}
		if  (  !(  kk  &  FILE_ATTRIBUTE_DIRECTORY  )  )  {
			AfxMessageBox(  "设置的注册目录不是一个文件夹"  );
			return;
		}
	}

	if  (  strcmpi(  m_var.qyRegToolDir,  m_qyRegToolDir.GetBuffer(  0  )  )  )  {
		qySetRegCfg(  CONST_qyRootKey_qnmScheduler,  CONST_regValName_secChkFactoryDir,  m_qyRegToolDir.GetBuffer(  0  )  );
	}


	CDialog::OnOK();
}

BOOL CDlgCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if  (  qyGetRegCfg(   CONST_qyRootKey_qnmScheduler,  CONST_regValName_secChkFactoryDir,  m_var.qyRegToolDir,  sizeof(  m_var.qyRegToolDir  )  )  )  {
		m_var.qyRegToolDir[0]  =  0;
	}

	trim(  m_var.qyRegToolDir  );
	m_qyRegToolDir  =  m_var.qyRegToolDir;

	UpdateData(  FALSE  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

