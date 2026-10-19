// DlgMgrSwitchPolicyGrps.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgMgrSwitchPolicyGrps.h"
#include	"dlgAddSwitchToGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrSwitchPolicyGrps dialog


CDlgMgrSwitchPolicyGrps::CDlgMgrSwitchPolicyGrps(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMgrSwitchPolicyGrps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMgrSwitchPolicyGrps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.nItemSelected  =  -1;

}


void CDlgMgrSwitchPolicyGrps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMgrSwitchPolicyGrps)
	DDX_Control(pDX, IDC_LIST_ip, m_lv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMgrSwitchPolicyGrps, CDialog)
	//{{AFX_MSG_MAP(CDlgMgrSwitchPolicyGrps)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ip, OnItemchangedLISTip)
	ON_CBN_SELCHANGE(IDC_COMBO_snmpPolicyGrp, OnSelchangeCOMBOsnmpPolicyGrp)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrSwitchPolicyGrps message handlers

BOOL CDlgMgrSwitchPolicyGrps::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	char		sqlBuf[1024  +  1];
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	m_var.pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select count(*) from qySnmpPolicyGrpTab"  );
	if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfConfigSnmpFirst  )  );  goto  errLabel;
	}

	m_lv.SetExtendedStyle(  LVS_EX_FULLROWSELECT  );
	m_var.idcCb		=  IDC_COMBO_snmpPolicyGrp;
	m_var.idcList	=  IDC_LIST_ip;	
	m_var.pColumns  =  ( QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_qnmMgrSwitchPolicyColumns  );

	int			i;
	LV_COLUMN	lvc;
	lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for  (  i  =  0;  m_var.pColumns[i].type  !=  -1;  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	m_var.pColumns[i].label;
		   lvc.cx			=	m_var.pColumns[i].width;
		   lvc.fmt			=	m_var.pColumns[i].fmt;
		   m_lv.InsertColumn(  i,  &lvc  );
	}
	m_var.nFields  =  i;
	
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qySnmpObjPolicyTab where not grpName in (select name from qySnmpPolicyGrpTab)"  );
	if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;

	if  (  !bQnmFillCol0(  m_var.pObjDb,  _T(  "select name from qySnmpPolicyGrpTab order by name"  ),  GetDlgItem(  IDC_COMBO_snmpPolicyGrp  )->m_hWnd,  FALSE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_snmpPolicyGrp  )  )->SetCurSel(  0  );

	listIps(  );
	bRefreshButtons(  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );  return  FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 LRESULT  CDlgMgrSwitchPolicyGrps::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	TCHAR				sqlBuf[1024  +  1];
	CDBVariant			varVals[5];
	QY_SNMPOBJ_HEAD		snmpObjHead;
	
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_addIp:  {
				  QY_WMBUF_ADDIP	*	pWmBuf  =  (  QY_WMBUF_ADDIP  *  )pComm;
				  char					ip12[12  +  1];
				  unsigned  char		ucbObjExists		=	FALSE;

				  if  (  !qyStdToIp12(  pWmBuf->ipBuf,  ip12  )  )  goto  errLabel;
				  pWmBuf->desBuf[sizeof(  pWmBuf->desBuf  )  -  1]  =  0;
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select ip from qySnmpObjPolicyTab where ip='%s'"  ),  CString(  ip12  )  );
				  if  (  bQyGetRcdBySql(  m_var.pObjDb->pDb,  CString(  sqlBuf  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
					  MessageBeep(  -1  );  goto  errLabel;
				  }
				  if  (  bGetSnmpObjHeadInfoBySth(  m_var.pObjDb->pDb,  NULL,  ip12,  &snmpObjHead  )  )  ucbObjExists  =  TRUE;
				  if  (  ucbObjExists  &&  !snmpObjHead.cusName[0]  &&  pWmBuf->desBuf[0]  )  {
					  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qySnmpObjTab set cusName='%s' where ip='%s'"  ),  pWmBuf->desBuf,  CString(  ip12  )  );					  
					  bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  );
				  }				  
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qySnmpObjPolicyTab(ip,cusName,grpName) values('%s','%s','%s')"  ),  CString(  ip12  ),  (  ucbObjExists  &&  snmpObjHead.cusName[0]  )  ?  snmpObjHead.cusName  :  CString(  pWmBuf->desBuf  ),  CString(  m_var.grpName  )  );
				  if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;
				  
				  listIps(  );
				}
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}


 void  CDlgMgrSwitchPolicyGrps::listIps(  )
{
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )m_var.pObjDb->pDb  );
	CListCtrl				*	pListCtrl	=	NULL;
	int							nFields;
	CDBVariant					varVal[10];
	//  char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem,  nSubItem;
	CString						tmpCStr;
	char						buf[128];
	CString						str;
	char						tmpBuf[128];
	TCHAR						tBuf[1024];

	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	pListCtrl->DeleteAllItems(  );

	GetDlgItemText(  m_var.idcCb,  str  );  myTChar2Str(  str,  m_var.grpName,  sizeof(  m_var.grpName  )  );
	if  (  !m_var.grpName[0]  )  goto  errLabel;
	_snprintf(  m_var.sqlBuf,  sizeof(  m_var.sqlBuf  ),  "select ip,cusName from qySnmpObjPolicyTab where grpName='%s' order by ip",  m_var.grpName  );

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
                                 myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );
								 if  (  atol(  tmpBuf  )  ==  1  )  tmpCStr  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  );
								 break;
						   default:
								   MACRO_sqlStr(  varVal[nSubItem],  tBuf,  mycountof(  tBuf  )  );
								   tmpCStr  =  tBuf;
								   break;
				   }

				   if  (  !nSubItem  )  pListCtrl->InsertItem(  nItem, tmpCStr  );
				   else  pListCtrl->SetItemText(  nItem,  nSubItem,  tmpCStr  );
			  }
			  
		 }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgMgrSwitchPolicyGrps::listIps failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );

	
}


 void CDlgMgrSwitchPolicyGrps::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CDlgAddSwitchToGrp	dlg;

	dlg.bSetDlgInfo(  CONST_qyDlgType_continuousAdd,  this->m_hWnd,  "将设备添加到管理组中",  "添加",  ""  );
	dlg.DoModal(  );
	
}

 void  CDlgMgrSwitchPolicyGrps::OnDel() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	char	sqlBuf[2048];
	char	ip[256];
	char	ip12[12  +  1];
	CString	str;
	
	if  (  m_var.nItemSelected  <  0  )  return;
	
	str  =  m_lv.GetItemText(  m_var.nItemSelected,  0  );  myTChar2Str(  str,  ip,  sizeof(  ip  )  );
	qyStdToIp12(  ip,  ip12  );
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qySnmpObjPolicyTab where ip='%s' and grpName='%s'",  ip12,  m_var.grpName  );
	if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErrorResultCannotDelete  )  );
		return;
	}
	
	listIps(  );
	m_var.nItemSelected  =  -1;
	bRefreshButtons(  );
	
	return;

}

void CDlgMgrSwitchPolicyGrps::OnItemchangedLISTip(NMHDR* pNMHDR, LRESULT* pResult) 
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


 BOOL  CDlgMgrSwitchPolicyGrps::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;

}




void CDlgMgrSwitchPolicyGrps::OnSelchangeCOMBOsnmpPolicyGrp() 
{
	listIps(  );
}
