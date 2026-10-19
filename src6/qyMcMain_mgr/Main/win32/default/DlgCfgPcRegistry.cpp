// DlgCfgPcRegistry.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgPcRegistry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistry dialog


CDlgCfgPcRegistry::CDlgCfgPcRegistry(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgPcRegistry::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgPcRegistry)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgCfgPcRegistry::bSetDlgInfo(  int  iDlgType,  int  id  )
{
	 m_var.iDlgType  =  iDlgType;
	 m_var.id  =  id;

	return  TRUE;
}


void CDlgCfgPcRegistry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgPcRegistry)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgPcRegistry, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgPcRegistry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistry message handlers






BOOL CDlgCfgPcRegistry::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	char					*	tmpPtr		=	NULL;
	CListCtrl				*	pListCtrl	=	NULL;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	bQnmFillCol0FromTable(  CONST_iRootKeyTable,  GetDlgItem(  IDC_COMBO_iRootKey  )->m_hWnd,  0  );

	if  (  m_var.iDlgType  ==  CONST_qyDlgType_modify  )  {
		if  (  !bGetPcRegistryRuleBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  0,  0,  m_var.id,  &m_var.oldRcd  )  )  memset(  &m_var.oldRcd,  0,  sizeof(  m_var.oldRcd  )  );

		GetDlgItem(  IDC_COMBO_iRootKey  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  CONST_iRootKeyTable,  m_var.oldRcd.iRootKey  )  );
		SetDlgItemText(  IDC_EDIT_subKey,  m_var.oldRcd.subKey  );
		SetDlgItemText(  IDC_EDIT_cfgName,  m_var.oldRcd.cfgName  );
		SetDlgItemInt(  IDC_EDIT_nIntervals,  m_var.oldRcd.nIntervals  );

		//  因为qyPcRegistryValTab依赖于qyPcRegistryRuleTab，所以不能把subKey中的值修改了
		GetDlgItem(  IDC_COMBO_iRootKey  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_subKey  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_cfgName  )->EnableWindow(  FALSE  );


		}
	else  {
		  GetDlgItem(  IDC_COMBO_iRootKey  )->SendMessage(  CB_SETCURSEL,  0,  0  );
		  SetDlgItemInt(  IDC_EDIT_nIntervals,  1  );
	}

	//  2006/07/18, 暂时要求不支持98，ME
	m_var.oldRcd.ucbUnsupport98  =  TRUE;
	m_var.oldRcd.ucbUnsupportMe  =	TRUE;
	//
	GetDlgItem(  IDC_CHECK_unsupport98  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_unsupportMe  )->EnableWindow(  FALSE  );


	if  (  m_var.oldRcd.ucbUnsupport98  )  GetDlgItem(  IDC_CHECK_unsupport98  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
  	if  (  m_var.oldRcd.ucbUnsupportMe  )  GetDlgItem(  IDC_CHECK_unsupportMe  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
  	if  (  m_var.oldRcd.ucbUnsupport2k  )  GetDlgItem(  IDC_CHECK_unsupport2000  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
  	if  (  m_var.oldRcd.ucbUnsupportXp  )  GetDlgItem(  IDC_CHECK_unsupportXp  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
  	if  (  m_var.oldRcd.ucbUnsupport2003  )  GetDlgItem(  IDC_CHECK_unsupport2003  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	//
	if  (  m_var.oldRcd.ucbNotLogAdd  )  GetDlgItem(  IDC_CHECK_ucbNotLogAdd  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	if  (  m_var.oldRcd.ucbNotLogDel  )  GetDlgItem(  IDC_CHECK_ucbNotLogDel  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	if  (  m_var.oldRcd.ucbNotLogModify  )  GetDlgItem(  IDC_CHECK_ucbNotLogModify  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

extern  QY_DMITEM  CONST_iRootKeyTable_full[];

void CDlgCfgPcRegistry::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC		*	pQyMc		=		QY_GET_GBUF(  );
	CString			str;
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];

	GetDlgItemText(  IDC_COMBO_iRootKey,  str  );
	m_var.iRootKey  =  qyGetTypeByDes(  CONST_iRootKeyTable,  str  );
	GetDlgItemText(  IDC_EDIT_subKey,  str  );
	lstrcpyn(  m_var.subKey,  str,  mycountof(  m_var.subKey  )  );
	tTrim(  m_var.subKey  );
	GetDlgItemText(  IDC_EDIT_cfgName,  m_var.cfgName,  mycountof(  m_var.cfgName  )  );
	m_var.nIntervals  =  GetDlgItemInt(  IDC_EDIT_nIntervals  );

	QY_DMITEM  *  pItem;
	for  (  pItem  =  CONST_iRootKeyTable_full;  pItem->type  !=  -1;  pItem  ++  )  {
		if  (  _tcsncicmp(  m_var.subKey,  pItem->des,  lstrlen(  pItem->des  )  )  )  continue;

		if  (  pItem->type  ==  (  long  )HKEY_CURRENT_USER  ) m_var.iRootKey  =  (  long  )HKEY_USERS;
		else  m_var.iRootKey  =  pItem->type;
		str  =  (  m_var.subKey  +  lstrlen(  pItem->des  )  );
		if  (  !str.GetLength(  )  )  m_var.subKey[0]  =  0;
		else  if  (  str.GetAt(  0  )  !=  _T(  '\\'  )  )  m_var.subKey[0]  =  0;
		else  {
			  lstrcpyn(  m_var.subKey,  str.GetBuffer(  0  )  +  1,  mycountof(  m_var.subKey  )  );
			  tTrim(  m_var.subKey  );
		}
		break;
		
	}
	


	m_var.ucbUnsupport98  =  (  GetDlgItem(  IDC_CHECK_unsupport98  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbUnsupportMe  =  (  GetDlgItem(  IDC_CHECK_unsupportMe  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbUnsupportNt  =  FALSE;
	m_var.ucbUnsupport2k  =  (  GetDlgItem(  IDC_CHECK_unsupport2000  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbUnsupportXp  =  (  GetDlgItem(  IDC_CHECK_unsupportXp  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbUnsupport2003  =  (  GetDlgItem(  IDC_CHECK_unsupport2003  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbUnsupportVista  =  FALSE;

	//  
	m_var.ucbNotLogAdd  =  (  GetDlgItem(  IDC_CHECK_ucbNotLogAdd  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbNotLogDel  =  (  GetDlgItem(  IDC_CHECK_ucbNotLogDel  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	m_var.ucbNotLogModify  =  (  GetDlgItem(  IDC_CHECK_ucbNotLogModify  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;

	if  (  m_var.iRootKey  ==  -1  )  {
		qyShowHint(  _T(  "请选择根键"  )  );  return;
	}
	if  (  !m_var.subKey[0]  )  {
		qyShowHint(  _T(  "请输入子键"  )  );  return;
	}
	if  (  m_var.subKey[0]  ==  _T(  '\\'  )  )  {
		qyShowHint(  _T(  "子键不能以\\开头"  )  );  return;
	}


	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from qyPcRegistryRuleTab where uiType=%d and iRootKey=%d and subKey=%s and cfgName=%s"  ),  CONST_pcCommType_registryRule,  m_var.iRootKey,  getDbValStr(  pQyMc->cfg.db.iDbType,  SQL_WVARCHAR,  m_var.subKey  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  SQL_WVARCHAR,  m_var.cfgName  )  );
	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
		if  (  bSqlObjExists(  pQyMc->gui.pDb,  sqlBuf  )  )  {
			qyShowHint(  _T(  "该注册表项已存在"  )  );  return;
		}
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcRegistryRuleTab(uiType,mac0,uiLangId,iPlatformId,winDir,iRootKey,subKey,cfgName,nIntervals,unsupport98,unsupportMe,unsupportNt,unsupport2k,unsupportXp,unsupport2003,unsupportVista,ucbNotLogAdd,ucbNotLogDel,ucbNotLogModify) values(%d,'%s',0,0,'',%d,%s,%s,%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"  ),  CONST_pcCommType_registryRule,  CString(CONST_qyNullMac),  m_var.iRootKey,  getDbValStr(  pQyMc->cfg.db.iDbType,  SQL_WVARCHAR,  m_var.subKey  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  SQL_WVARCHAR,  m_var.cfgName  ),  m_var.nIntervals,  
																					MACRO_ucbStr(  m_var.ucbUnsupport98  ),    
																					MACRO_ucbStr(  m_var.ucbUnsupportMe  ),    
																					MACRO_ucbStr(  m_var.ucbUnsupportNt  ),    
																					MACRO_ucbStr(  m_var.ucbUnsupport2k  ),    
																					MACRO_ucbStr(  m_var.ucbUnsupportXp  ),    
																					MACRO_ucbStr(  m_var.ucbUnsupport2003  ),
																					MACRO_ucbStr(  m_var.ucbUnsupportVista  ),
																					MACRO_ucbStr(  m_var.ucbNotLogAdd  ),  
																					MACRO_ucbStr(  m_var.ucbNotLogDel  ),  
																					MACRO_ucbStr(  m_var.ucbNotLogModify  )
																					);

		traceLogA(  "sqlBuf is [%S]",  sqlBuf  );
		bQyExecSql(  pQyMc->gui.pDb,  sqlBuf  );
		}
	else  {
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and id<>%d"  ),  sqlBuf,  m_var.id  );
		  if  (  bSqlObjExists(  pQyMc->gui.pDb,  sqlBuf  )  )  {
			  qyShowHint(  _T(  "该注册表项已存在"  )  );  return;
		  }
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyPcRegistryRuleTab set iRootKey=%d,subKey=%s,cfgName=%s,nIntervals=%d,unsupport98='%s',unsupportMe='%s',unsupportNt='%s',unsupport2k='%s',unsupportXp='%s',unsupport2003='%s',unsupportVista='%s',ucbNotLogAdd='%s',ucbNotLogDel='%s',ucbNotLogModify='%s' where id=%d"  ),  m_var.iRootKey,  getDbValStr(  pQyMc->cfg.db.iDbType,  SQL_WVARCHAR,  m_var.subKey  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  SQL_WVARCHAR,  m_var.cfgName  ),  m_var.nIntervals,  MACRO_ucbStr(  m_var.ucbUnsupport98  ),  MACRO_ucbStr(  m_var.ucbUnsupportMe  ),  MACRO_ucbStr(  m_var.ucbUnsupportNt  ),  MACRO_ucbStr(  m_var.ucbUnsupport2k  ),  MACRO_ucbStr(  m_var.ucbUnsupportXp  ),  MACRO_ucbStr(  m_var.ucbUnsupport2003  ),  MACRO_ucbStr(  m_var.ucbUnsupportVista  ),  MACRO_ucbStr(  m_var.ucbNotLogAdd  ),  MACRO_ucbStr(  m_var.ucbNotLogDel  ),  MACRO_ucbStr(  m_var.ucbNotLogModify  ),  m_var.id  );
		  traceLogA(  "sqlBuf is [%S]",  sqlBuf  );
		  bQyExecSql(  pQyMc->gui.pDb,  sqlBuf  );
	}


	m_var.ucbChanged  =  TRUE;
	
	CDialog::OnOK();
}
