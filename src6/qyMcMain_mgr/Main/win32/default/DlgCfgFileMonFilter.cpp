// DlgCfgFileMonFilter.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qymc.h"
#include	"DlgCfgFileMonFilter.h"
#include	"qyCusResTemp.h"
#include	"DlgAddFileMonRule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgFileMonFilter dialog

 int  myGetRule(  LPCTSTR  pStr,  unsigned  char  *  pucFlg,  TCHAR  **  ppBuf  )
{
	 int		iErr	=	-1;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 TCHAR	*	p0;
	 TCHAR  *	p;
	 
	 if  (  !(  p0  =  (  TCHAR  *  )_tcschr(  pStr,  _T(  ' '  )  )  )  )  goto  errLabel;
	 p0  ++  ;

	 p  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_suffix  );
	 if  (  !_tcsnicmp(  p0,  p,  lstrlen(  p  )  )  )  {  
		 *pucFlg  =  CONST_fileMonFlg_suffix;  (  *  ppBuf  )  =  (  TCHAR  *  )(  p0  +  lstrlen(  p  )  +  2  );
		}
	 else  {
		   p  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_str  );
		   *pucFlg  =  CONST_fileMonFlg_str;  (  *  ppBuf  )  =  (  TCHAR  *  )(  p0  +  lstrlen(  p  )  +  1  );
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}

 CString  myDisplayStr(  int  i,  unsigned  char  ucFlg,  LPCTSTR  str  )
{
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 TCHAR		tBuf[256];

	 if  (  ucFlg  &  CONST_fileMonFlg_suffix  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%02d %s .%s"  ),  i,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_suffix  ), str  );
	 else  if  (  ucFlg  &  CONST_fileMonFlg_str  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%02d %s %s"  ),  i,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_str  ), str  );
	 else  tBuf[0]  =  0;

	 return  CString(  tBuf  );
}


CDlgCfgFileMonFilter::CDlgCfgFileMonFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgFileMonFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgFileMonFilter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgFileMonFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgFileMonFilter)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgFileMonFilter, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgFileMonFilter)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_reset, Onreset)
	ON_CBN_SELCHANGE(IDC_COMBO_bMonAll, OnSelchangeCOMBObMonAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgFileMonFilter message handlers







  QY_DMITEM  CONST_skippedFileTable[]  =
{
	{	0,			_T(  "qyNetMc.mdb"  ), 					},
	{	0,			_T(  "Catalog.LiveSubscribe"  ),		},			//  norton
	{	0,			_T(  "QQlog"  ),						},			//  qq
	{	-1,			NULL,					},
};


 QY_DMITEM  CONST_onlyMonSuffixTable_fileMon[]  =
{
	{	0,			_T(  "txt"  ),					},
	{	0,			_T(  "doc"  ),					},
	{	0,			_T(  "xls"  ),					},
	{	0,			_T(  "ppt"  ),					},
	{	-1,											},
};


 QY_DMITEM  CONST_skippedSuffixTable_fileMon[]  =
{
	{	0,		    _T(  "tmp"  ),					},
	{	0,			_T(  "dat"  ),					},
	{	0,			_T(  "log"  ),					},
	{	0,			_T(  "job"  ),					},
	{	0,			_T(  "ldb"  ),					},
	{	0,			_T(  "ini"  ),					},
	{	0,			_T(  "ver"  ),					},				//  nod32
	{	0,			_T(  "pf"  ),					},
	{	0,			_T(  "dll"  ),					},
	{	0,			_T(  "dbl"  ),					},
	{	0,			_T(  "bak"  ),					},
	{	0,			_T(  "inf"  ),					},
	{	0,			_T(  "rul"  ),					},
	{	0,			_T(  "cab"  ),					},
	{	0,			_T(  "cfg"  ),					},
	{	0,			_T(  "db"  ),					},				//  qq
	{	0,			_T(  "dbx"  ),					},				//  outlook
	{	0,			_T(  "rs"  ),					},				//  rising
	{	0,			_T(  "down"  ),					},				//  rising
	{	0,			_T(  "def"  ),					},				//  rising	
	{	0,			_T(  "acs"  ),					},				//  rising	
	{	0,			_T(  "vxd"  ),					},				//  rising	
	{	0,			_T(  "exe"  ),					},				//  test,by wqh
	//
	{	0,			_T(  "xml"  ),					},			
	//
	{	-1,									},
};


 int  resetDefaultFileMonRules(  void  *  pDb,  unsigned  int  uiOldChangesId,  unsigned  char  ucbMonAll,  PC_FILEMON_RULES  *  pInfo  )
{
	 QY_DMITEM					*	pItem;

	 memset(  pInfo,  0,  sizeof(  pInfo[0]  )  );
	 pInfo->uiType  =  CONST_ruleType_pcFileMon;
	 pInfo->uiChangesId  =  uiOldChangesId  ?  (  uiOldChangesId  +  1  )  :  DEFAULT_fileMonFilter_changesId;
	 pInfo->ucbFilterSysDir		=  TRUE;
	 pInfo->ucbFilterWinDir		=  TRUE;
	 pInfo->ucbFilterWinTmpDir	=  TRUE;
	 pInfo->ucbFilterUsrTmpDir	=  TRUE;
	 pInfo->ucbFilterRename		=  FALSE;
	 pInfo->ucbFilterModify		=  FALSE;
	 pInfo->ucbMonAll			=  ucbMonAll;
	 
	 if  (  ucbMonAll  )  {
		 for  (  pItem  =  CONST_skippedSuffixTable_fileMon;  pInfo->ucCnt  <  CONST_maxFileMonRules  &&  pItem->type  !=  -1;  pItem  ++  )  {
			  pInfo->ucFlgs[pInfo->ucCnt]  =  CONST_fileMonFlg_suffix;
			  _sntprintf(  (  TCHAR  *  )pInfo->bufs[pInfo->ucCnt],  sizeof(  pInfo->bufs[pInfo->ucCnt]  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  pItem->des  );
			  pInfo->ucCnt  ++  ;		  
		 }
		 
		 for  (  pItem  =  CONST_skippedFileTable;  pInfo->ucCnt  <  CONST_maxFileMonRules  &&  pItem->type  !=  -1;  pItem  ++  )  {
			  pInfo->ucFlgs[pInfo->ucCnt]  =  CONST_fileMonFlg_str;
			  _sntprintf(  (  TCHAR  *  )pInfo->bufs[pInfo->ucCnt],  sizeof(  pInfo->bufs[pInfo->ucCnt]  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  pItem->des  );
			  pInfo->ucCnt  ++  ;		  
		 }
		}
	 else  {
		   for  (  pItem  =  CONST_onlyMonSuffixTable_fileMon;  pInfo->ucCnt  <  CONST_maxFileMonRules  &&  pItem->type  !=  -1;  pItem  ++  )  {
			    pInfo->ucFlgs[pInfo->ucCnt]  =  CONST_fileMonFlg_suffix;
			    _sntprintf(  (  TCHAR  *  )pInfo->bufs[pInfo->ucCnt],  sizeof(  pInfo->bufs[pInfo->ucCnt]  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  pItem->des  );
			    pInfo->ucCnt  ++  ;		  
		   }
	 }

	 

	 return  0;

}


 int  updateFileMonRules(  void  *  pDb,  char  *  mac0,  PC_FILEMON_RULES  *  pInfo  )
{
	 int		iErr		=		-1;
	 TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1];
	 int		i			=		0;
	 

	 if  (  !mac0  )  mac0  =  CONST_qyNullMac;
	 

	 //  最后更新uiChangesId
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyPcFileMonRuleTab"  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	 
	 for  (  i  =  0;  i  <  pInfo->ucCnt;  i  ++  )  {
		  if  (  pInfo->ucFlgs[i]  &  CONST_fileMonFlg_suffix  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_suffix,  pInfo->bufs[i]  );
		  else  if  (  pInfo->ucFlgs[i]  &  CONST_fileMonFlg_str  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_str,  pInfo->bufs[i]  );
		  else  continue;
		  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	 }

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_bMonAll,  MACRO_ucbStr(  pInfo->ucbMonAll  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_filterSysDir,  MACRO_ucbStr(  pInfo->ucbFilterSysDir  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_filterWinDir,  MACRO_ucbStr(  pInfo->ucbFilterWinDir  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_filterWinTmpDir,  MACRO_ucbStr(  pInfo->ucbFilterWinTmpDir  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_filterUsrTmpDir,  MACRO_ucbStr(  pInfo->ucbFilterUsrTmpDir  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_filterRename,  MACRO_ucbStr(  pInfo->ucbFilterRename  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,col0) values('%s',%d,'%s')"  ),  CString(  mac0  ),  CONST_fileMonRuleType_filterModify,  MACRO_ucbStr(  pInfo->ucbFilterModify  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcFileMonRuleTab(mac0,uiType,iCol0) values('%s',%d,%d)"  ),  CString(  mac0  ),  CONST_fileMonRuleType_changesId,  pInfo->uiChangesId  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 return  iErr;
}




 void  CDlgCfgFileMonFilter::listRules(  PC_FILEMON_RULES  *  pRules  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	int			i;
	TCHAR		tBuf[256];

	GetDlgItem(  IDC_CHECK_filterSysDir  )->SendMessage(  BM_SETCHECK,  pRules->ucbFilterSysDir  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_filterWinDir  )->SendMessage(  BM_SETCHECK,  pRules->ucbFilterWinDir  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_filterWinTmpDir  )->SendMessage(  BM_SETCHECK,  pRules->ucbFilterWinTmpDir  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_filterUsrTmpDir  )->SendMessage(  BM_SETCHECK,  pRules->ucbFilterUsrTmpDir  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );

	GetDlgItem(  IDC_CHECK_filterRename  )->SendMessage(  BM_SETCHECK,  pRules->ucbFilterRename  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_filterModify  )->SendMessage(  BM_SETCHECK,  pRules->ucbFilterModify  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );

	if  (  pRules->ucbMonAll  )  GetDlgItem(  IDC_COMBO_bMonAll  )->SendMessage(  CB_SELECTSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_bMonAll  )  );
	else  GetDlgItem(  IDC_COMBO_bMonAll  )->SendMessage(  CB_SELECTSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_monOnly  )  );

	(  (  CListBox  *  )GetDlgItem(  IDC_LIST_rules  )  )->ResetContent(  );

	for  (  i  =  0;  i  <  pRules->ucCnt;  i  ++  )  {
		 lstrcpyn(  tBuf,  myDisplayStr(  i,  pRules->ucFlgs[i],  (  TCHAR  *  )pRules->bufs[i]  ),  mycountof(  tBuf  )  );
		 if  (  !tBuf[0]  )  continue;
		 GetDlgItem(  IDC_LIST_rules  )->SendMessage(  LB_ADDSTRING,  0,  (  LPARAM  )tBuf  );
	}

	return;
}

BOOL CDlgCfgFileMonFilter::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC						*	pQyMc			=	QY_GET_GBUF(  );
	CWaitCursor						cur;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !bGetDefaultFileMonRules(  pQyMc->gui.pDb,  &m_var.oldRules  )  )  memset(  &m_var.oldRules,  0,  sizeof(  m_var.oldRules  )  );

	GetDlgItem(  IDC_COMBO_bMonAll  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_bMonAll  )  );
	GetDlgItem(  IDC_COMBO_bMonAll  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_monOnly  )  );

	listRules(  &m_var.oldRules  );

	memcpy(  &m_var.newRules,  &m_var.oldRules,  sizeof(  m_var.newRules  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgFileMonFilter::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CListBox	*	pLb		=	(  CListBox  *  )GetDlgItem(  IDC_LIST_rules  );
	TCHAR			tBuf[256];

	if  (  m_var.newRules.ucCnt  >=  CONST_maxFileMonRules  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "The max number of rules is less than : [ %d ]"  ),  CONST_maxFileMonRules  );
		AfxMessageBox(  tBuf  );  return;
	}

	CDlgAddFileMonRule		dlg;

	dlg.bSetDlgInfo(  &m_var.newRules  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		//  加入队列
		m_var.newRules.ucFlgs[m_var.newRules.ucCnt]  =  dlg.m_var.ucFlg;
		lstrcpyn(  (  TCHAR  *  )m_var.newRules.bufs[m_var.newRules.ucCnt],  (  TCHAR  *  )dlg.m_var.buf,  sizeof(  m_var.newRules.bufs[m_var.newRules.ucCnt]  )  /  sizeof(  TCHAR  )  );
		//
		pLb->InsertString(  -1,  myDisplayStr(  m_var.newRules.ucCnt,  m_var.newRules.ucFlgs[m_var.newRules.ucCnt],  (  TCHAR  *  )m_var.newRules.bufs[m_var.newRules.ucCnt]  )  );
		//
		pLb->SetCurSel(  pLb->GetCount(  )  -  1  );

		m_var.newRules.ucCnt  ++  ;
		
	}
	
}


void CDlgCfgFileMonFilter::OnDel() 
{
	// TODO: Add your control notification handler code here
	CListBox	*		pLb		=	(  CListBox  *  )GetDlgItem(  IDC_LIST_rules  );
	int					iCurSel;
	CString				str;
	TCHAR		*		p;
	unsigned  char		ucFlg;
	int					i;


	iCurSel  =  GetDlgItem(  IDC_LIST_rules  )->SendMessage(  LB_GETCURSEL,  0,  0  );
	if  (  iCurSel  ==  LB_ERR  )  return;
	pLb->GetText(  iCurSel,  str  );
	if  (  myGetRule(  str,  &ucFlg,  &p  )  )  {
		traceLogA(  "myGetRule failed"  );  return;
	}
	for  (  i  =  0;  i  <  m_var.newRules.ucCnt;  i  ++  )  {
		if  (  ucFlg  ==  m_var.newRules.ucFlgs[i]  &&  !lstrcmpi(  p,  (  TCHAR  *  )m_var.newRules.bufs[i]  )  )  {
			m_var.newRules.ucFlgs[i]  =  0;  m_var.newRules.bufs[i][0]  =  0;
		}
	}

	pLb->DeleteString(  iCurSel  );

	if  (  pLb->GetCount(  )  ==  iCurSel  )  iCurSel  --  ;
	if  (  iCurSel  >=  0  )  pLb->SetCurSel(  iCurSel  );

}

void CDlgCfgFileMonFilter::Onreset() 
{
	// TODO: Add your control notification handler code here
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	resetDefaultFileMonRules(  pQyMc->gui.pDb,  m_var.oldRules.uiChangesId,  TRUE,  &m_var.newRules  );
	
	listRules(  &m_var.newRules  );

	
}

void CDlgCfgFileMonFilter::OnOK() 
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CString			str;
	CWaitCursor		cur;

	// TODO: Add extra validation here
	m_var.newRules.ucbFilterSysDir  =  GetDlgItem(  IDC_CHECK_filterSysDir  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.newRules.ucbFilterWinDir  =  GetDlgItem(  IDC_CHECK_filterWinDir  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.newRules.ucbFilterWinTmpDir  =  GetDlgItem(  IDC_CHECK_filterWinTmpDir  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.newRules.ucbFilterUsrTmpDir  =  GetDlgItem(  IDC_CHECK_filterUsrTmpDir  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.newRules.ucbFilterRename  =  GetDlgItem(  IDC_CHECK_filterRename  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	m_var.newRules.ucbFilterModify  =  GetDlgItem(  IDC_CHECK_filterModify  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;

	GetDlgItemText(  IDC_COMBO_bMonAll,  str  );
	if  (  !lstrcmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_bMonAll  )  )  )  m_var.newRules.ucbMonAll  =  TRUE;
	else  m_var.newRules.ucbMonAll  =  FALSE;


	if  (  memcmp(  &m_var.newRules,  &m_var.oldRules,  sizeof(  m_var.newRules  )  )  )  {
		if  (  AfxMessageBox(  _T(  "Are you sure to change the rules?"  ),  MB_YESNO  )  !=  IDYES  )  return;
		m_var.newRules.uiChangesId  =  m_var.newRules.uiChangesId  +  1;
		updateFileMonRules(  pQyMc->gui.pDb,  CONST_qyNullMac,  &m_var.newRules  );  
	}
	
	CDialog::OnOK();
}

 void CDlgCfgFileMonFilter::OnSelchangeCOMBObMonAll() 
{
	// TODO: Add your control notification handler code here
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CString			str;
	unsigned  char	ucbMonAll	=	FALSE;

	GetDlgItemText(  IDC_COMBO_bMonAll,  str  );
	if  (  !lstrcmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fileMon_bMonAll  )  )  )  ucbMonAll  =  TRUE;

	resetDefaultFileMonRules(  pQyMc->gui.pDb,  0,  ucbMonAll,  &m_var.newRules  );
	m_var.newRules.uiChangesId  =  m_var.oldRules.uiChangesId;
	
	listRules(  &m_var.newRules  );


	
}
