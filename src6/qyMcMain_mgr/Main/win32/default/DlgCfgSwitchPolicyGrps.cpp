// DlgCfgSwitchPolicyGrps.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgSwitchPolicyGrps.h"
#include	"DlgCfgSwitchPolicyGrp.h"
#include	"DlgCfgSwitchDefaultPolicyGrp.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchPolicyGrps dialog



CDlgCfgSwitchPolicyGrps::CDlgCfgSwitchPolicyGrps(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgSwitchPolicyGrps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgSwitchPolicyGrps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.nItemSelected  =  -1;
}


void CDlgCfgSwitchPolicyGrps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgSwitchPolicyGrps)
	DDX_Control(pDX, IDC_LIST_switchPolicyGrp, m_lv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgSwitchPolicyGrps, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgSwitchPolicyGrps)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_switchPolicyGrp, OnItemchangedLISTswitchPolicyGrp)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_switchPolicyGrp, OnDblclkLISTswitchPolicyGrp)
	ON_BN_CLICKED(IDC_modifyDefSnmpPolicy, OnmodifyDefSnmpPolicy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchPolicyGrps message handlers

BOOL CDlgCfgSwitchPolicyGrps::OnInitDialog() 
{
	CDialog::OnInitDialog(  );
	TCHAR						tBuf[256];
	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QY_SNMPOBJPOLICY_RCD		policy;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	memset(  &policy,  0,  sizeof(  policy  )  );
	bGetDefSnmpPolicy(  0,  &pQyMc->encCtx,  &policy  );    
		
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_theMeaningOfCfgSnmpGrpPolicy  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_defaultPolicy  ),  CString(  policy.snmpVer  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_onlyReadCommunity  ),  CString(  policy.getCommunity  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_writeCommunity  ),  CString(  policy.setCommunity  )  );
	SetDlgItemText(  IDC_STATIC_snmpPolicyHint,  CString(  tBuf  )  );

	m_lv.SetExtendedStyle(  LVS_EX_FULLROWSELECT  );
	m_var.idcList  =  IDC_LIST_switchPolicyGrp;	
	m_var.pColumns  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_qnmCfgSwitchPolicyGrpsColumns  );

	int  i;
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for  (  i  =  0;  m_var.pColumns[i].type  !=  -1;  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	m_var.pColumns[i].label;
		   lvc.cx			=	m_var.pColumns[i].width;
		   lvc.fmt			=	m_var.pColumns[i].fmt;
		   m_lv.InsertColumn(  i,  &lvc  );
	}
	m_var.nFields  =  i;
	_snprintf(  m_var.sqlBuf,  sizeof(  m_var.sqlBuf  ),  "select name,snmpVer,getCommunity,setCommunity,usmName,securityLevel from qySnmpPolicyGrpTab order by name"  );

	listGrps(  );

	bRefreshButtons(  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 void  CDlgCfgSwitchPolicyGrps::listGrps(  )
{
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pQyMc->gui.pDb  );
	CListCtrl				*	pListCtrl	=	NULL;
	int							nFields;
	CDBVariant					varVal[10];
	//  char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem,  nSubItem;
	CString						tmpCStr;
	char						buf[128];
	unsigned  char				ucbV3		=	FALSE;
	char						tmpBuf[128];
	TCHAR					*	pStopString;
	TCHAR						tBuf[1024];
	
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	pListCtrl->DeleteAllItems(  );
	
	try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  CString(  m_var.sqlBuf  )  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 if  (  nFields  >  sizeof(  varVal  )  /  sizeof(  varVal[0]  )  )  {
			 traceLogA(  "%s: varVal is too small.",  __FILE__  );
			 goto  errLabel;
		 }
		 //  MACRO_qyAssert(  nFields  ==  m_var.nFields,  "CDlgQnmCfgPcGrps字段数不匹配"  );

		 for  (  nItem  =  0;  !rs.IsEOF(  );  rs.MoveNext(  ),  nItem  ++  )  {

			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVal[index]  );
			  			  
			  ucbV3  =  FALSE;
			  
			  for  (  nSubItem  =  0;  nSubItem  <  m_var.nFields;  nSubItem  ++  )  {
				   //  tmpPtr  =  "";
				   tmpCStr  =  CString(  ""  );
				   switch  (  m_var.pColumns[nSubItem].type  )  {
						   case  CONST_qyColumnDisplayType_ip12:  
							     MACRO_sqlStr(  varVal[nSubItem],  tBuf,  mycountof(  tBuf  )  );
							     if  (  lstrlen(  tBuf  )  ==  12  )  {
					     			 myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );
						 			 tmpCStr  =  CString(  qyIp12ToStd(  tmpBuf,  buf  )  );						 
			  					 }
								 break;
						   case  CONST_qyColumnDisplayType_bool:
							     MACRO_sqlStr(  varVal[nSubItem],  tBuf,  mycountof(  tBuf  )  );
							     if  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  )
									 tmpCStr  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  );
								 break;
						   default:
							       MACRO_sqlStr(  varVal[nSubItem],  tBuf,  mycountof(  tBuf  )  );
								   tmpCStr  =  tBuf;							      
								   break;
				   }

				   switch  (  nSubItem  )  {
						   case  0:			//  name  
								   pListCtrl->InsertItem(  nItem,  tmpCStr  );
								   break;
						   case  1:			//  snmpVer
							       pListCtrl->SetItemText(  nItem,  nSubItem,  tmpCStr  );
								   if  (  !lstrcmpi(  tmpCStr,  _T(  "v3"  )  )  )  ucbV3  =  TRUE;
								   break;
						   case  2:			//  getCommunity
						   case  3:			//  setCommunity
								   pListCtrl->SetItemText(  nItem,  nSubItem,  tmpCStr  );
								   break;
						   case  4:			//  usmName
							       if  (  ucbV3  )  pListCtrl->SetItemText(  nItem,  nSubItem,  tmpCStr  );
								   break;
						   case  5:			//  securityLevel
								   if  (  ucbV3  )  pListCtrl->SetItemText(  nItem,  nSubItem,  CString(  "noAuthPriv"  )  );
								   break;
						   default:
									break;

			  }
			  
		 }
		}
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgCfgSwitchPolicyGrps::listGrps failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
}

 BOOL  CDlgCfgSwitchPolicyGrps::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;
}

void CDlgCfgSwitchPolicyGrps::OnItemchangedLISTswitchPolicyGrp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if  (  pNMListView->iItem  >= 0 
		&&  pNMListView->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		m_var.nItemSelected  =  pNMListView->iItem;
		}
	else  {
		  m_var.nItemSelected  =  -1;
	}

	bRefreshButtons(  );

	*pResult = 0;
}

void CDlgCfgSwitchPolicyGrps::OnAdd() 
{
	CDlgCfgSwitchPolicyGrp	dlg;

	dlg.bSetDlgInfo(  CONST_qyDlgType_add,  this,  NULL  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		listGrps(  );
	}
}

 void CDlgCfgSwitchPolicyGrps::OnModify() 
{
	QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	char					buf[128]	=  "";
	LVITEM					lvItem;
	BOOL					bRet;
	CDlgCfgSwitchPolicyGrp	dlg;
	TCHAR					tBuf[128];

	if  (  m_var.nItemSelected  <  0  )  goto  errLabel;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT;
	lvItem.iItem  =  m_var.nItemSelected;
	lvItem.iSubItem  =  0;			//  显示的列位置
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );

	if  (  !(  bRet  =  ::SendMessage(  m_lv.m_hWnd,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  )  goto  errLabel;
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	trim(  buf  );

	dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  this,  buf  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	if  (  dlg.m_var.ucbChanged  )  listGrps(  );

errLabel:
	return;
	
}


void CDlgCfgSwitchPolicyGrps::OnDel() 
{
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	char			buf[128]	=  "";
	char			sqlBuf[1024  +  1];
	LVITEM			lvItem;
	BOOL			bRet;
	TCHAR			tBuf[256];

	if  (  m_var.nItemSelected  <  0  )  goto  errLabel;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT;
	lvItem.iItem  =  m_var.nItemSelected;
	lvItem.iSubItem  =  0;			//  显示的列位置
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );

	if  (  !(  bRet  =  ::SendMessage(  m_lv.m_hWnd,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  )  goto  errLabel;
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	trim(  buf  );

	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qySnmpObjPolicyTab where grpName='%s'",  buf  );
	if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  traceLogA(  "sql failed: [%s]",  sqlBuf  );
	
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qySnmpPolicyGrpTab where name='%s'",  buf  );
	if  (  bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  listGrps(  );
	

errLabel:
	return;
	
}


void CDlgCfgSwitchPolicyGrps::OnDblclkLISTswitchPolicyGrp(NMHDR* pNMHDR, LRESULT* pResult) 
{

	QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	char					buf[128]	=  "";
	LVITEM					lvItem;
	BOOL					bRet;
	CDlgCfgSwitchPolicyGrp	dlg;
	TCHAR					tBuf[256];

	if  (  m_var.nItemSelected  <  0  )  goto  errLabel;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT;
	lvItem.iItem  =  m_var.nItemSelected;
	lvItem.iSubItem  =  0;			//  显示的列位置
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );

	if  (  !(  bRet  =  ::SendMessage(  m_lv.m_hWnd,  LVM_GETITEM,  0,  (  LPARAM  )&lvItem  )  )  )  goto  errLabel;
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	trim(  buf  );

	dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  this,  buf  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	if  (  dlg.m_var.ucbChanged  )  listGrps(  );
	
errLabel:	

	*pResult = 0;
}

void CDlgCfgSwitchPolicyGrps::OnmodifyDefSnmpPolicy() 
{
	// TODO: Add your control notification handler code here
	CDlgCfgSwitchDefaultPolicyGrp		dlg;
	QY_MC							*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR								tBuf[256];
	QY_SNMPOBJPOLICY_RCD				policy;

	dlg.DoModal(  );

	bGetDefSnmpPolicy(  0,  &pQyMc->encCtx,  &policy  );    

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_theMeaningOfCfgSnmpGrpPolicy  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_defaultPolicy  ),  CString(  policy.snmpVer  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_onlyReadCommunity  ),  CString(  policy.getCommunity  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_writeCommunity  ),  CString(  policy.setCommunity  )  );
	SetDlgItemText(  IDC_STATIC_snmpPolicyHint,  CString(  tBuf  )  );
	
}
