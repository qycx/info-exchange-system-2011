// DlgSelectDsn.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgSelectDsn.h"
#include ".\dlgselectdsn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectDsn dialog


CDlgSelectDsn::CDlgSelectDsn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectDsn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectDsn)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgSelectDsn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectDsn)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectDsn, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectDsn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectDsn message handlers

BOOL CDlgSelectDsn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	QY_OBJ_DB	*	pObjDb				=	NULL;
	int				i;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	for  (  i  =  0;  i  <  (  int  )getProcedObjDbsMaxCnt(  );  i  ++  )  {
		 pObjDb  =  getProcedObjDb(  0,  i  );
		 if  (  !bObjDbAvail(  pObjDb  )  )  continue;
		 (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_dsn  )  )->InsertString(  -1,  pObjDb->cfg.sysName  );
	}

	pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );
	if  (  bObjDbAvail(  pObjDb  )  )  (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_dsn  )  )->SelectString(  -1,  pObjDb->cfg.sysName  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectDsn::OnOK() 
{
	// TODO: Add extra validation here
	CString			str;
	int				i;
	QY_OBJ_DB	*	pObjDb	=	NULL;

	GetDlgItemText(  IDC_COMBO_dsn,  str  );
	for  (  i  =  0;  i  <  (  int  )getProcedObjDbsMaxCnt(  );  i  ++  )  {
		 pObjDb  =  getProcedObjDb(  0,  i  );
		 if  (  !bObjDbAvail(  pObjDb  )  )  continue;
		 if  (  str  !=  CString(  pObjDb->cfg.sysName  )  )  continue;
		 break;
	}
	if  (  i  ==  (  int  )getProcedObjDbsMaxCnt(  )  )  {
		qyShowHint(  _T(  "请选择一个数据源以进行下面的操作"  )  ) ;
		return;
	}

	m_var.iDsnIndex  =  pObjDb->iDsnIndex;
	
	CDialog::OnOK();
}

void CDlgSelectDsn::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
