// DlgPropIpKnowledge.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPropIpKnowledge.h"
#include	".\dlgpropipknowledge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPropIpKnowledge dialog


CDlgPropIpKnowledge::CDlgPropIpKnowledge(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropIpKnowledge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropIpKnowledge)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0, sizeof(  m_var  )  );
}

BOOL  CDlgPropIpKnowledge::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	m_var.pObjDb  =  pObjDb;
	m_var.id  =  id;
	return  TRUE;

}


void CDlgPropIpKnowledge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropIpKnowledge)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropIpKnowledge, CDialog)
	//{{AFX_MSG_MAP(CDlgPropIpKnowledge)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropIpKnowledge message handlers

BOOL CDlgPropIpKnowledge::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !m_var.pObjDb  )  {
		EndDialog(  -1  );  return  FALSE;
	}

	// TODO:  在此添加额外的初始化
	if  (  !bGetIpKnowledgeBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  m_var.id,  &m_var.knowledge  )  )  memset(  &m_var.knowledge,  0,  sizeof(  m_var.knowledge  )  );

	SetDlgItemText(  IDC_STATIC_startIpVal,  CString(  m_var.knowledge.startIp  )  );
	SetDlgItemText(  IDC_STATIC_endIpVal,  CString(  m_var.knowledge.endIp  )  );
	SetDlgItemText(  IDC_STATIC_wLocationVal,  CString(  m_var.knowledge.wLocation  )  );
	SetDlgItemInt(  IDC_STATIC_iWeightVal,  m_var.knowledge.iWeight  );




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
