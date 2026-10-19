// DlgCfgUsrs.cpp : implementation file
//

#include "stdafx.h"
#include "qyMcMainCommon.h"
#include "qymc.h"
#include "DlgCfgUsrs.h"
#include "dlgCfgUsr.h"
#include "qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TCHAR  *  CONST_grpsHint[3]  =	{};





/////////////////////////////////////////////////////////////////////////////
// CDlgCfgUsrs dialog


CDlgCfgUsrs::CDlgCfgUsrs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgUsrs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgUsrs)
	//}}AFX_DATA_INIT

	memset(  &var,  0,  sizeof(  var  )  );
	var.nItemSelected  =  -1;

}


void CDlgCfgUsrs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgUsrs)
	DDX_Control(pDX, IDC_GRPLIST, m_grpList);
	DDX_Control(pDX, IDC_USRLIST, m_LV);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgCfgUsrs, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgUsrs)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(NM_DBLCLK, IDC_USRLIST, OnDblclkUsrlist)
	ON_CBN_SELCHANGE(IDC_GRPLIST, OnSelchangeGrplist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_USRLIST, OnItemchangedUsrlist)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgCfgUsrs::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgUsrs message handlers
 int  getQyMcLogonCfg(  QY_MC  *  pQyMc,  QY_MC_logonCfg  *  );

 int  CDlgCfgUsrs::getLogonCfgFromDlg(  )
{
	int				iErr	=	-1;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	int				lVal;
	int				idc;
	QY_MC_logonCfg	cfg;
	TCHAR			tBuf[128];
	
	memset(  &cfg,  0,  sizeof(  cfg  )  );

	idc  =  IDC_EDIT_minPasswdLen;
	lVal  =  GetDlgItemInt(  idc,  NULL,  FALSE  );
	if  (  lVal  <  MIN_qyMc_passwdLen  )  {
		qyShowHint(  _T(  "Minimum password length is %d"  ),  MIN_qyMc_passwdLen  );
		GetDlgItem(  idc  )->SetFocus(  );
		goto  errLabel;
	}
	cfg.usMinPasswdLen  =  lVal;

	idc  =  IDC_EDIT_maxInvalidLogonAttempts;
	lVal  =  GetDlgItemInt(  idc,  NULL,  FALSE  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_qyMc_invalidLogonAttempts  )  {
		qyShowHint(  _T(  "Maximum invalid logon attempts shall be >  0 and  <=  %d"  ),  MAX_qyMc_invalidLogonAttempts  );
		GetDlgItem(  idc  )->SetFocus(  );
		goto  errLabel;
	}
	cfg.usMaxInvalidLogonAttempts  =  lVal;

	if  (  memcmp(  &cfg,  &pQyMc->cfg.logon,  sizeof(  cfg  )  )  )  {
		qySetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_minPasswdLen  ),  _ltot(  cfg.usMinPasswdLen,  tBuf,  10  )  );
		qySetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_maxInvalidLogonAttempts  ),  _ltot(  cfg.usMaxInvalidLogonAttempts,  tBuf,  10  )  );

		getQyMcLogonCfg(  pQyMc,  &pQyMc->cfg.logon  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

  
 int CDlgCfgUsrs::listUsrs(  )
{
	
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	int				iErr					=	-1;
	//  char			buf[256];
	TCHAR			grpNameBuf[256];
	TCHAR			sqlBuf[2048];
	CRecordset		ls(  (  CDatabase *  )pQyMc->gui.pDb );
	CDBVariant		varVals[10];
	LV_ITEM			lvi;
	int				i;
	QY_DMITEM	*	pItem					=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );
	CString			str;
	TCHAR			tBuf[256];
	int				nFields					=	0;
	int				index;
	CString			zbStr,  bbStr,  dwStr,  bmStr;

	m_LV.DeleteAllItems(  );

	lvi.mask		=	LVIF_TEXT;
	lvi.iSubItem	=	0;

	GetDlgItemText(  IDC_GRPLIST,  str  );  
	for  (  pItem;  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->pData,  str  )  )  break;
	if  (  pItem->type  ==  -1  )  return  -1;
	//  myTChar2Str(  pItem->des,  grpNameBuf,  sizeof(  grpNameBuf  )  );
	lstrcpyn(  grpNameBuf,  pItem->des,  mycountof(  grpNameBuf  )  );
	
	try  {
	
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select A.usrName,B.zbStr,B.bbStr,B.dwStr,B.bmStr from qyGrpUsrRelationTab as A left join qyUsrTab as B on (A.usrName=B.name) where A.grpName='%s'"  ),  grpNameBuf  );
		if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and B.zbStr=%s and B.bbStr=%s and B.dwStr=%s and B.bmStr=%s"  ),  sqlBuf,  
				getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.zbStr  ),
				getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.bbStr  ),
				getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.dwStr  ),
				getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  pQyMc->curUsrInfo.scope.bmStr  )  );
		}

		if  (  !ls.Open(  CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
			MessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotConnectToDb  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_err  ), MB_OK|MB_ICONERROR );
			goto  errLabel;
		}	
		nFields  =  ls.GetODBCFieldCount(  );
	
		for  (  i  =  0;  !ls.IsEOF(  );  i  ++,  ls.MoveNext(  )  )  {
			 
			 for  (  index  =  0;  index  <  nFields;  index  ++  )  ls.GetFieldValue(  index,  varVals[index]  );
					 
			 index  =  0;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	m_LV.InsertItem(  i,  tBuf  );
			 index  ++  ;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	zbStr  =  CString(  tBuf  );
			 index  ++  ;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	bbStr  =  CString(  tBuf  );
			 index  ++  ;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	dwStr  =  CString(  tBuf  );
			 index  ++  ;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	bmStr  =  CString(  tBuf  );

			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - %s - %s - %s"  ),  zbStr,  bbStr,  dwStr,  bmStr  );
			 m_LV.SetItemText(  i,  1,  tBuf  );

		}
		
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgCfgUsrs::listUsrs failed."  )  );
		   goto  errLabel;
	}
	
	iErr  =  0;

errLabel:

	if  (  ls.IsOpen(  )  )  ls.Close(  );

	var.nItemSelected  =  -1;
	
	bRefreshButtons(  );

	return  iErr;

}



void CDlgCfgUsrs::OnAdd() 
{
	CDlgCfgUsr	dlg;

	//
	if  (  getLogonCfgFromDlg(  )  )  return;

	//
	dlg.bSetDlgInfo(  CONST_qyDlgType_add,  this  );
	dlg.DoModal(  );

	if  (  dlg.var.bChanged  )  {
		listUsrs(  );
	}
	
}

void CDlgCfgUsrs::OnModify() 
{	
	bModifyItem(  );	
}

 BOOL  CDlgCfgUsrs::bModifyItem(  )
{
	CDlgCfgUsr  dlg;

	if  (  getLogonCfgFromDlg(  )  )  return  FALSE;

	dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  this  );
	dlg.DoModal(  );

	if  (  dlg.var.bChanged  )  {
		listUsrs(  );
	}
	
	return  TRUE;

}

void CDlgCfgUsrs::OnDel() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	char			sqlBuf[2048];
	char			usrNameBuf[256];
	char			grpNameBuf[256];
	char			buf[256];
	QY_DMITEM	*	pItem	=	NULL;
	CString			str;
	
	if  (  var.nItemSelected  <  0  )  return;
	
	GetDlgItemText(  IDC_GRPLIST,  str  );  //  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->pData,  str  )  )  break;
	if  (  pItem->type  ==  -1  )  return;
	myTChar2Str(  pItem->des,  grpNameBuf,  sizeof(  grpNameBuf  )  );
	//
	str  =  m_LV.GetItemText(  var.nItemSelected,  0  );  myTChar2Str(  str,  usrNameBuf,  sizeof(  usrNameBuf  )  );

	sprintf(  sqlBuf,  "delete from qyGrpUsrRelationTab where usrName='%s' and grpName='%s'",  usrNameBuf,  grpNameBuf  );
	if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErrorResultCannotDelete  )  );  return;
	}

	sprintf(  sqlBuf,  "select count(*) from qyGrpUsrRelationTab where usrName='%s'",  usrNameBuf  );
	if  (  !bSqlObjExists(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
		sprintf(  sqlBuf,  "delete from qyUsrTab where name='%s'",  usrNameBuf  );
		if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
			OutputDebugString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErrorResultCannotDelete  )  );  return;
		}
	}

	TCHAR  des[128]	=	_T(  ""  );
	_sntprintf(  des,  mycountof(  des  ),  _T(  "%s [ %s ]/[ %s ] ?"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDelete  ),  CString(  buf  ),  CString(  usrNameBuf  )  );
	qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_delUsr,  CString(  pQyMc->curUsrInfo.name  ),  CString(  des  )  );

	listUsrs(  );

	return;

}

void CDlgCfgUsrs::OnDblclkUsrlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if  (  var.nItemSelected  >=  0  )  {
		bModifyItem(  );
	}
	
	*pResult = 0;
}




BOOL CDlgCfgUsrs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	CONST_grpsHint[0]  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_desOfAdminGrp  );
	CONST_grpsHint[1]  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_desOfCfgGrp  );
	CONST_grpsHint[2]  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_desOfLogGrp  );

	m_LV.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	m_LV.InsertColumn( 0, getResStr(  0, &pQyMc->cusRes,  CONST_resId_logon_staticUsrName  ),			LVCFMT_LEFT,	121  );	
	m_LV.InsertColumn( 1, getResStr(  0, &pQyMc->cusRes,  CONST_resId_scope  ),		LVCFMT_LEFT,	141  );	

	CComboBox	*	pGrpList	=  (  CComboBox  *  )GetDlgItem(  IDC_GRPLIST  );
	QY_DMITEM	*	pItem		=	NULL;

	if  (  pQyMc->curUsrInfo.right.bAdmin  )  for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  pGrpList->AddString(  CString(  pItem->pData  )  );
	else  {
		  if  (  pQyMc->curUsrInfo.right.bXtpzAdmin  )  for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->des,  _T(  CONST_grpName_xtpz  )  )  )  pGrpList->AddString(  CString(  pItem->pData  )  );
		  if  (  pQyMc->curUsrInfo.right.bRzsjAdmin  )  for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->des,  _T(  CONST_grpName_rzsj  )  )  )  pGrpList->AddString(  CString(  pItem->pData  )  );
	}

	pGrpList->SetCurSel(  0  );
	SetDlgItemText(  IDC_HINT,  CString(  CONST_grpsHint[0]  )  );
	
	listUsrs(  );

	//
	SetDlgItemInt(  IDC_EDIT_minPasswdLen,  pQyMc->cfg.logon.usMinPasswdLen  );
	SetDlgItemInt(  IDC_EDIT_maxInvalidLogonAttempts,  pQyMc->cfg.logon.usMaxInvalidLogonAttempts  );
	//
	if  (  !pQyMc->curUsrInfo.right.bAdmin  &&  !pQyMc->curUsrInfo.right.bXtpz  )  {
		GetDlgItem(  IDC_EDIT_minPasswdLen  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_maxInvalidLogonAttempts  )->EnableWindow(  FALSE  );
	}

	//
	bRefreshButtons(  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 BOOL  CDlgCfgUsrs::bRefreshButtons(  )
{
	BOOL			bRet				=	FALSE;
	char			usrNameBuf[256]		=	"";
	char			grpNameBuf[256]		=	"";
	char			buf[256];
	QY_DMITEM	*	pItem				=	NULL;
	BOOL			bAdmin				=	FALSE;
	CString			str;
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );

	/*
	if  (  var.nItemSelected  >=  0  )  {
		GetDlgItemText(  IDC_GRPLIST,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
		for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->pData,  CString(  buf  )  )  )  break;
		if  (  pItem->type  ==  -1  )  goto  errLabel;
		myTChar2Str(  pItem->des,  grpNameBuf,  sizeof(  grpNameBuf  )  );
		//
		str  =  m_LV.GetItemText(  var.nItemSelected,  0  );  myTChar2Str(  str,  usrNameBuf,  sizeof(  usrNameBuf  )  );
	}

	if  (  (  !strcmpi( grpNameBuf,  CONST_grpName_admin  )  &&  !strcmpi( usrNameBuf,  CONST_usrName_admin  )  )
		||  (  !strcmpi(  grpNameBuf,  CONST_grpName_xtpz  )  &&  !strcmpi(  usrNameBuf,  CONST_usrName_sysAdmin  )  )
			||  (  !strcmpi(  grpNameBuf,  CONST_grpName_rzsj  )  &&  !strcmpi(  usrNameBuf,  CONST_usrName_logAdmin  )  )  )
	{
		bAdmin  =  TRUE;
	}
	*/
	if  (  var.nItemSelected  >=  0  )  {
		GetDlgItemText(  IDC_GRPLIST,  str  );  
		for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->pData,  str  )  )  break;
		if  (  pItem->type  ==  -1  )  goto  errLabel;
		myTChar2Str(  pItem->des,  grpNameBuf,  sizeof(  grpNameBuf  )  );
		//
		str  =  m_LV.GetItemText(  var.nItemSelected,  0  );  myTChar2Str(  str,  usrNameBuf,  sizeof(  usrNameBuf  )  );
	}

	if  (  (  !strcmpi( grpNameBuf,  CONST_grpName_admin  )  &&  !strcmpi( usrNameBuf,  CONST_usrName_admin  )  )
		||  (  !strcmpi(  grpNameBuf,  CONST_grpName_xtpz  )  &&  !strcmpi(  usrNameBuf,  CONST_usrName_sysAdmin  )  )
			||  (  !strcmpi(  grpNameBuf,  CONST_grpName_rzsj  )  &&  !strcmpi(  usrNameBuf,  CONST_usrName_logAdmin  )  )  )
	{
		bAdmin  =  TRUE;
	}

	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  var.nItemSelected  >=  0  &&  !bAdmin  );
			
	bRet  =  TRUE;
errLabel:
	return  bRet;
}

void CDlgCfgUsrs::OnSelchangeGrplist() 
{
	int		iCurSel	=	m_grpList.GetCurSel(  );
	
	if  (  iCurSel  ==  CB_ERR  )  return;

	SetDlgItemText(  IDC_HINT,  CString(  CONST_grpsHint[iCurSel]  )  );
	listUsrs(  );
	
}

void CDlgCfgUsrs::OnItemchangedUsrlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	char	buf[1024];

	sprintf(  buf,  "%d\n",  pNMListView->iItem  );

	if  (  pNMListView->iItem >= 0 
		&&  pNMListView->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		var.nItemSelected  =  pNMListView->iItem;
		}
	else  {
		var.nItemSelected  =  -1;
	}

	bRefreshButtons(  );

	OutputDebugString(  CString(  buf  )  );	
	
	*pResult = 0;
}

//void CDlgCfgUsrs::OnCancel()
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	CDialog::OnCancel();
//}

void CDlgCfgUsrs::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if  (  getLogonCfgFromDlg(  )  )  return;

	OnOK();
}
