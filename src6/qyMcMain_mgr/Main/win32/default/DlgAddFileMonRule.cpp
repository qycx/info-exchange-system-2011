// DlgAddFileMonRule.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qymc.h"
#include	"DlgAddFileMonRule.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFileMonRule dialog


CDlgAddFileMonRule::CDlgAddFileMonRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddFileMonRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddFileMonRule)
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgAddFileMonRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddFileMonRule)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddFileMonRule, CDialog)
	//{{AFX_MSG_MAP(CDlgAddFileMonRule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFileMonRule message handlers

 BOOL  CDlgAddFileMonRule::bSetDlgInfo(  void  *  pRules  )
{
	m_var.pRules  =  (  PC_FILEMON_RULES  *  )pRules;
	return  TRUE;
}


BOOL CDlgAddFileMonRule::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	

	GetDlgItem(  IDC_COMBO_fileMonRuleType  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_suffix  )  );
	GetDlgItem(  IDC_COMBO_fileMonRuleType  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_str  )  );

	GetDlgItem(  IDC_COMBO_fileMonRuleType  )->SendMessage(  CB_SELECTSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_suffix  )  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAddFileMonRule::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	CString				str;
	unsigned  char		ucFlg;
	int					i;
	TCHAR				tBuf[256];

	GetDlgItemText(  IDC_COMBO_fileMonRuleType,  str  );
	if  (  !lstrcmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_suffix  )  )  )  ucFlg  =  CONST_fileMonFlg_suffix;
	else  ucFlg  =  CONST_fileMonFlg_str;

	GetDlgItemText(  IDC_EDIT_name,  str  );
	MACRO_CStringTrim(  str  );
	if  (  !str.GetLength(  )  )  return;
	if  (  str.GetLength(  )  >=  CONST_maxFileMonRuleBufSize /  sizeof(  TCHAR  )  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "The max length is less than : [ %d ]"  ),  CONST_maxFileMonRuleBufSize  /  sizeof(  TCHAR  )  -  1  );  
		AfxMessageBox(  tBuf  );  return;
	}

	for  (  i  =  0;  i  <  m_var.pRules->ucCnt;  i  ++  )  {
		 if  (  m_var.pRules->ucFlgs[i]  ==  ucFlg  &&  !lstrcmp(  str,  (  TCHAR  *  )m_var.pRules->bufs[i]  )  )  {
			 AfxMessageBox(  _T(  "The rule exists!"  )  );  return;
		 }
	}

	m_var.ucFlg  =  ucFlg;
	lstrcpyn(  (  TCHAR  *  )m_var.buf,  str,  sizeof(  m_var.buf  )  /  sizeof(  TCHAR  )  );
	
	
	CDialog::OnOK();
}


