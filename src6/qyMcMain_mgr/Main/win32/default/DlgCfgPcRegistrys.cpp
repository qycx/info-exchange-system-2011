// DlgCfgPcRegistrys.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgPcRegistrys.h"
#include	"dlgCfgPcRegistry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistrys dialog


CDlgCfgPcRegistrys::CDlgCfgPcRegistrys(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgPcRegistrys::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgPcRegistrys)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.nItemSelected  =  -1;
}


void CDlgCfgPcRegistrys::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgPcRegistrys)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgPcRegistrys, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgPcRegistrys)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_pcRegistry, OnItemchangedLISTpcRegistry)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_pcRegistry, OnDblclkLISTpcRegistry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistrys message handlers
/*
 QY_COLUMNINFO  CONST_pcRegistryColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),				SQL_CHAR,	LVCFMT_LEFT,	0,			1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "根键"  ),				SQL_CHAR,	LVCFMT_LEFT,	200,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "键路径"  ),			SQL_CHAR,	LVCFMT_LEFT,	380,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "名称"  ),				SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		CONST_qyColumnDisplayType_long,	_T(  "检测周期数"  ),		SQL_CHAR,	LVCFMT_LEFT,	80,			1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};
*/

typedef  struct  __qnmPcRegistry_t			{
				 int						iRootKey;
				 char						subKey[512];				 
}		 QNM_PCREGISTRY;



extern  QY_DMITEM  CONST_iRootKeyTable[];

 int  CDlgCfgPcRegistrys::listPcRegistrys(  )
{	 
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pQyMc->gui.pDb  );
	CListCtrl				*	pListCtrl	=	NULL;
	int							nFields;
	CDBVariant					varVals[10];
	char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem;
	QY_PCREGISTRYRULE_RCD		pcRegistryInfo;
	TCHAR						tBuf[256];
		

	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	pListCtrl->DeleteAllItems(  );
	
	try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  CString(  m_var.sqlBuf  )  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  {
			 traceLogA(  "%s: varVal is too small.",  __FILE__  );
			 goto  errLabel;
		 }
		 //  MACRO_qyAssert(  nFields  ==  m_var.nFields,  "CDlgQnmCfgPcGrps字段数不匹配"  );

		 for  (  nItem  =  0;  !rs.IsEOF(  );  rs.MoveNext(  ),  nItem  ++  )  {

			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			  			  
			  memset(  &pcRegistryInfo,  0,  sizeof(  pcRegistryInfo  )  );

			  
			  index  =  0;	//  id
			  MACRO_sqlLong(  varVals[index],  pcRegistryInfo.id  );
			  index  ++  ;	//  iRootKey
			  MACRO_sqlLong(  varVals[index],  pcRegistryInfo.iRootKey  );
			  index  ++  ;	//  subKey
			  MACRO_sqlStr(  varVals[index],  pcRegistryInfo.subKey,  mycountof(  pcRegistryInfo.subKey  )  );
			  index  ++  ;	//  cfgName
			  MACRO_sqlStr(  varVals[index],  pcRegistryInfo.cfgName,  mycountof(  pcRegistryInfo.cfgName  )  );
			  index  ++  ;	//  nIntervals
			  MACRO_sqlLong(  varVals[index],  pcRegistryInfo.nIntervals  );
			  index  ++  ;
				  
	
			  index  =  0;
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pcRegistryInfo.id  );
			  pListCtrl->InsertItem(  nItem,  tBuf  );
			  index  ++  ;
			  pListCtrl->SetItemText(  nItem,  index,  qyGetDesByType1(  CONST_iRootKeyTable,  pcRegistryInfo.iRootKey  )  );
			  index  ++  ;
			  pListCtrl->SetItemText(  nItem,  index,  pcRegistryInfo.subKey  );
			  index  ++  ;
			  pListCtrl->SetItemText(  nItem,  index,  pcRegistryInfo.cfgName  );
			  index  ++  ;
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pcRegistryInfo.nIntervals  );
			  pListCtrl->SetItemText(  nItem,  index,  tBuf  );
		
			  if  (  m_var.ucbIdSeletedValid  &&  m_var.idSelected  ==  pcRegistryInfo.id  )  m_var.nItemSelected  =  nItem;
			  
		 }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgCfgPcRegistrys::listPcRegistrys failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  0;
}

  BOOL  CDlgCfgPcRegistrys::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;
}


BOOL CDlgCfgPcRegistrys::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	char					*	tmpPtr		=	NULL;
	CListCtrl				*	pListCtrl	=	NULL;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	//  下面显示配置网段列表
	m_var.idcList  =  IDC_LIST_pcRegistry;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	//  GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	m_var.pColumns  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_pcRegistryColumns  );
	

	_sntprintf(  m_var.sqlBuf,  mycountof(  m_var.sqlBuf  ),  _T(  "select id,iRootKey,subKey,cfgName,nIntervals from qyPcRegistryRuleTab where mac0='%s' order by iRootKey,subKey,cfgName"  ),  CString(  CONST_qyNullMac  )  );
	
	int  i;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for  (  i  =  0;  m_var.pColumns[i].type  !=  -1;  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	m_var.pColumns[i].label;
		   lvc.cx			=	m_var.pColumns[i].width;
		   lvc.fmt			=	m_var.pColumns[i].fmt;
		   pListCtrl->InsertColumn(  i,  &lvc  );
	}
	m_var.nFields  =  i;
	
	listPcRegistrys(  );
	bRefreshButtons(  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCfgPcRegistrys::OnAdd() 
{
	// TODO: Add your control notification handler code here
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CDlgCfgPcRegistry		dlg;
	QY_PCREGISTRYRULE_RCD	rcd;
	int						tmpnItem;
	CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	dlg.DoModal(  );
	if  (  dlg.m_var.ucbChanged  )  {
		if  (  !bGetPcRegistryRuleBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  dlg.m_var.iRootKey,  dlg.m_var.subKey,  0,  &rcd  )  )  memset(  &rcd,  0,  sizeof(  rcd  )  );
		m_var.idSelected  =  rcd.id;
		m_var.ucbIdSeletedValid  =  TRUE;
		listPcRegistrys(  );
		m_var.ucbIdSeletedValid  =  FALSE;

		tmpnItem  =  m_var.nItemSelected;

		if  (  tmpnItem  >=  0  )  {
		
			pListCtrl->SetItemState(  tmpnItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			pListCtrl->Update(  tmpnItem  );

		}

	}

	bRefreshButtons(  );

	return;
}

void CDlgCfgPcRegistrys::OnModify() 
{
	// TODO: Add your control notification handler code here
	CDlgCfgPcRegistry	dlg;
	CString				str;
	CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	TCHAR			*	pStop;

	if  (  m_var.nItemSelected  <  0  )  return;

	str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );

	dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  _tcstol(  str,  &pStop,  10  )  );

	dlg.DoModal(  );

	if  (  dlg.m_var.ucbChanged  )  {
	
		m_var.ucbIdSeletedValid  =  TRUE;
		m_var.idSelected  =  _tcstol(  str,  &pStop,  10  );
		//	 
		this->listPcRegistrys(  );	
		//
		m_var.ucbIdSeletedValid  =  FALSE;
		
		int  tmpnItem  =  m_var.nItemSelected;
		
		if  (  tmpnItem  >=  0  )  {
		
			pListCtrl->SetItemState(  tmpnItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			pListCtrl->Update(  tmpnItem  );

		}


	}


	
	bRefreshButtons(  );

	
}

void CDlgCfgPcRegistrys::OnDel() 
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CString			str;
	CString			sqlStr;

	if  (  m_var.nItemSelected  <  0  )  return;

	int	tmpnItem	=	m_var.nItemSelected;
	TCHAR				sqlBuf[QY_SQLBUFLEN  +  1];
	CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	//  if  (  getItemContent(  tmpnItem,  &tmpItem  )  )  return;
	str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );

	if  (  AfxMessageBox(  _T(  "由此规则得到的所有注册表项也将同时被删除。确实要删除吗?"  ),  MB_YESNO  )  !=  IDYES  )  return;
	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyPcRegistryValTab where iRuleId=%s"  ),  str  );
	if  (  !bQyExecSql(  (  CDatabase  *  )pQyMc->gui.pDb,  sqlBuf  )  )  return;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from  qyPcRegistryRuleTab where id=%s"  ),  str  );
	if  (  !bQyExecSql(  (  CDatabase  *  )pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  return;
	pListCtrl->DeleteItem(  tmpnItem  );
	if  (  pListCtrl->GetItemCount(  ) <= tmpnItem  )  tmpnItem  --;
	
	if  (  tmpnItem  >=  0  )  {

		pListCtrl->SetItemState(  tmpnItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
		pListCtrl->Update(  tmpnItem  );
		m_var.nItemSelected  =  tmpnItem;
		}
	else
			m_var.nItemSelected  =  -1;
		
	m_var.bNeedRefreshAll  =  TRUE;
		
	bRefreshButtons(  );


}

void CDlgCfgPcRegistrys::OnItemchangedLISTpcRegistry(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if  (  pNMListView->iItem  >= 0 
		&&  (  pNMListView->uNewState  &  (  LVIS_SELECTED | LVIS_FOCUSED  )  )  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		m_var.nItemSelected  =  pNMListView->iItem;
		}
	else  {
		  m_var.nItemSelected  =  -1;
	}

	bRefreshButtons(  );

	
	*pResult = 0;
}



void CDlgCfgPcRegistrys::OnDblclkLISTpcRegistry(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		if  (  m_var.nItemSelected  >=  0  )  {
		 int	tmpnItem	=	m_var.nItemSelected;
		 CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
		 CString			str;
		 TCHAR			*	pStop;
		 CDlgCfgPcRegistry	dlg;

		 str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );
				 
		 dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  _tcstol(  str,  &pStop,  10  )  );
		 dlg.DoModal(  );

		 if  (  dlg.m_var.ucbChanged  )  {
			 
			 m_var.ucbIdSeletedValid  =  TRUE;
			 m_var.idSelected  =  _tcstol(  str,  &pStop,  10  );
			 //
			 this->listPcRegistrys(  );	
			 //
			 m_var.ucbIdSeletedValid  =  FALSE;

			 int  tmpnItem  =  m_var.nItemSelected;

			 if  (  tmpnItem  >=  0  )  {
		
				 pListCtrl->SetItemState(  tmpnItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
				 pListCtrl->Update(  tmpnItem  );

			 }


		 }

		 bRefreshButtons(  );

	 }


	*pResult = 0;
}
