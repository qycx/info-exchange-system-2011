// DlgCfgStandardNames.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgStandardNames.h"
#include	"DlgCfgStandardName.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgStandardNames dialog


CDlgCfgStandardNames::CDlgCfgStandardNames(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgStandardNames::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgStandardNames)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );	//  2006/12/17
	m_var.nItemSelected  =  -1;

}


 int  CDlgCfgStandardNames::listCfgStandardNames(  )
{
 
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )m_var.pObjDb->pDb  );
	CListCtrl				*	pListCtrl	=	NULL;
	int							nFields;
	CDBVariant					varVals[30];
	char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem;
	QY_CUSNAME_RCD				rcd;
	TCHAR						tBuf[256];
	int							i;
		

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
			  			  
			  memset(  &rcd,  0,  sizeof(  rcd  )  );

			  
			  index  =  0;	MACRO_sqlLong(  varVals[index],  rcd.id  );
			  index  ++  ;	MACRO_sqlLong(  varVals[index],  rcd.uiLangId  );
			  for  (  i  =  0;  i  <  mycountof(  rcd.objNames  );  i  ++  )  {
				   index  ++  ;	MACRO_sqlStr(  varVals[index],  rcd.objNames[i],  mycountof(  rcd.objNames[i]  )  );
				   index  ++  ;	MACRO_sqlStr(  varVals[index],  rcd.cusNames[i],  mycountof(  rcd.cusNames[i]  )  );
			  }				  
	
			  index  =  0;
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  rcd.id  );
			  pListCtrl->InsertItem(  nItem,  tBuf  );
			  for  (  i  =  0;  i  <  5;  i  ++  )  {
				   index  ++  ;  pListCtrl->SetItemText(  nItem,  index,  rcd.objNames[i]  );
			  }
			  for  (  i  =  0;  i  <  5;  i  ++  )  {
				   index  ++  ;  pListCtrl->SetItemText(  nItem,  index,  rcd.cusNames[i]  );
			  }
		
			  if  (  m_var.ucbIdSeletedValid  &&  m_var.idSelected  ==  rcd.id  )  m_var.nItemSelected  =  nItem;
			  
		 }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgCfgStandardNames::listCfgStandardNames failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  0;
}	 
	
 BOOL  CDlgCfgStandardNames::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;
}


void CDlgCfgStandardNames::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgStandardNames)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgStandardNames, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgStandardNames)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_cfgStandardName, OnItemchangedLISTcfgStandardName)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_cfgStandardName, OnDblclkLISTcfgStandardName)
	ON_BN_CLICKED(IDC_BUTTON_cfgStandardNames, OnBUTTONcfgStandardNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgStandardNames message handlers
/*
 QY_COLUMNINFO  CONST_cfgStandardNameColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),				SQL_CHAR,	LVCFMT_LEFT,	0,			1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "总部"  ),				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "本部"  ),				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "单位"  ),				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "部门"  ),				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "使用人"  ),			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "规范总部"  ),			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "规范本部"  ),			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "规范单位"  ),			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "规范部门"  ),			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "规范使用人"  ),		SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};
*/

BOOL CDlgCfgStandardNames::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CListCtrl				*	pListCtrl	=	NULL;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	m_var.pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );

		//  下面显示配置网段列表
	m_var.idcList  =  IDC_LIST_cfgStandardName;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	//  GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	m_var.pColumns  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0, &pQyMc->cusRes,  CONST_resId_cfgStandardNameColumns  );
	

	_sntprintf(  m_var.sqlBuf,  mycountof(  m_var.sqlBuf  ),  _T(  "select id,uiLangId,objName0,cusName0,objName1,cusName1,objName2,cusName2,objname3,cusName3,objName4,cusName4,objName5,cusName5,objName6,cusName6,objName7,cusName7 from qyCusNameTab where iType=%d order by objName0,objName1,objName2,objName3,objName4"  ),  CONST_cusNameType_pcRegInfo  );
	
	traceLogA(  "%S",  m_var.sqlBuf  );

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
	
	listCfgStandardNames(  );
	bRefreshButtons(  );

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgStandardNames::OnItemchangedLISTcfgStandardName(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgCfgStandardNames::OnAdd() 
{
	// TODO: Add your control notification handler code here
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CDlgCfgStandardName		dlg;
	QY_CUSNAME_RCD	rcd;
	int						tmpnItem;
	CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	dlg.bSetDlgInfo(  0,  m_var.pObjDb,  0,  0  );
	dlg.DoModal(  );
	if  (  dlg.m_var.cusName.iType  )  {
		if  (  !bGetCusNameBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  &dlg.m_var.cusName,  0,  &rcd  )  )  memset(  &rcd,  0,  sizeof(  rcd  )  );
		m_var.idSelected  =  rcd.id;
		m_var.ucbIdSeletedValid  =  TRUE;
		listCfgStandardNames(  );
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

void CDlgCfgStandardNames::OnModify() 
{
	// TODO: Add your control notification handler code here
	CDlgCfgStandardName	dlg;
	CString				str;
	CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	TCHAR			*	pStop;

	if  (  m_var.nItemSelected  <  0  )  return;

	str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );

	dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  m_var.pObjDb,  0,  _tcstol(  str,  &pStop,  10  )  );

	dlg.DoModal(  );

	if  (  dlg.m_var.cusName.iType  )  {
	
		m_var.ucbIdSeletedValid  =  TRUE;
		m_var.idSelected  =  _tcstol(  str,  &pStop,  10  );
		//	 
		this->listCfgStandardNames(  );	
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

void CDlgCfgStandardNames::OnDel() 
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

	if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from  qyCusNameTab where id=%s"  ),  str  );
	if  (  !bQyExecSql(  (  CDatabase  *  )m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  return;
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

void CDlgCfgStandardNames::OnDblclkLISTcfgStandardName(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		if  (  m_var.nItemSelected  >=  0  )  {
		 int	tmpnItem	=	m_var.nItemSelected;
		 CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
		 CString			str;
		 TCHAR			*	pStop;
		 CDlgCfgStandardName	dlg;

		 str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );
				 
		 dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  m_var.pObjDb,  0,  _tcstol(  str,  &pStop,  10  )  );
		 dlg.DoModal(  );

		 if  (  dlg.m_var.cusName.iType  )  {
			 
			 m_var.ucbIdSeletedValid  =  TRUE;
			 m_var.idSelected  =  _tcstol(  str,  &pStop,  10  );
			 //
			 this->listCfgStandardNames(  );	
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

 BOOL  tmpHandler_bCfgStandardNames(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	 //  p1
	 CDBVariant			*	varVals			=	(  CDBVariant  *  )p2;
	 void				*	pDb				=	pCommonParam->p0;
	 int					iDbType			=	(  int  )pCommonParam->p1;
	 QY_CUSNAME_RCD			rcd;
	 QY_CUSNAME_RCD		*	pCusName		=	&rcd;
	 int					index;
	 int					i;

	 memset(  pCusName,  0,  sizeof(  pCusName[0]  )  );

	 index  =  0;	MACRO_sqlLong(  varVals[index],  pCusName->id  );
	 index  ++  ;	MACRO_sqlLong(  varVals[index],  pCusName->iType  );
	 index  ++  ;	MACRO_sqlLong(  varVals[index],  pCusName->uiLangId  );
	 for  (  i  =  0;  i  <  mycountof(  pCusName->objNames  );  i  ++  )  {
	 	  index  ++  ;	MACRO_sqlStr(  varVals[index],  pCusName->objNames[i],  mycountof(  pCusName->objNames[i]  )  );
	 	  index  ++  ;	MACRO_sqlStr(  varVals[index],  pCusName->cusNames[i],  mycountof(  pCusName->cusNames[i]  )  );
	 }

	 bSetStandardRegInfo(  pDb,  iDbType,  pCusName  );  

	 return  TRUE;
}

void CDlgCfgStandardNames::OnBUTTONcfgStandardNames() 
{
	// TODO: Add your control notification handler code here
	QY_MC		*	pQyMc							=		QY_GET_GBUF(  );
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[30];
	BOOL			bRet;
	COMMON_PARAM	commonParam;
	
	if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifStandard  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,iType,uiLangId,objName0,cusName0,objName1,cusName1,objName2,cusName2,objName3,cusName3,objName4,cusName4,objName5,cusName5,objName6,cusName6,objName7,cusName7 from qyCusNameTab where iType=%d"  ),  CONST_cusNameType_pcRegInfo  );

	MACRO_makeCommonParam3(  m_var.pObjDb->pDb,  (  void  *  )m_var.pObjDb->cfg.iDbType,  0,  commonParam  );
	bRet  =  bEnumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_bCfgStandardNames,  &commonParam,  0,  varVals,  mycountof(  varVals  )  );

	qyShowHint(  bRet  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_standardFinished  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_standardFailed  )  );
	
}
