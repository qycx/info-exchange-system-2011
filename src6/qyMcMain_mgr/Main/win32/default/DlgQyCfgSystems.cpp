// DlgQyCfgSystems.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQyCfgSystems.h"
#include	"DlgQyCfgSystem.h"
#include	<tchar.h>
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCfgSystems dialog


CDlgQyCfgSystems::CDlgQyCfgSystems(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQyCfgSystems::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQyCfgSystems)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.nItemSelected  =  -1;

}


void CDlgQyCfgSystems::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQyCfgSystems)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQyCfgSystems, CDialog)
	//{{AFX_MSG_MAP(CDlgQyCfgSystems)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCfgSystems message handlers




 int  listProcedObjs(  CListCtrl  *  pListCtrl,  int  idSelected,  int  * pnItemSelected  )
{
	 QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	 int				i;
	 QY_OBJ_DB		*	pObj;
	 char				buf[256];
	 int				cnt				=	0;
	 int				index;
	 int				tmpnItem		=	-1;
	 
	 pListCtrl->DeleteAllItems(  );

	 for  (  i  =  0;  i  <  mycountof(  pQyMc->procedObjDbs  );  i  ++  )  {
		  pObj  =  &pQyMc->procedObjDbs[i];
		  if  (  !pObj->ucbUsed  )  continue;

		  index  =  0;
		  pListCtrl->InsertItem(  cnt,  CString(  ltoa(  pObj->iDsnIndex,  buf,  10  )  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  pObj->cfg.sysName  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qySystemIdTable  ),  pObj->cfg.iSystemId  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  qyGetDesByType1(  CONST_dbTypeTable,  pObj->cfg.iDbType  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  pObj->cfg.ucbDsnless  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  CString(  pObj->cfg.dbServIp  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  CString(  pObj->cfg.dbName  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  CString(  pObj->cfg.uid  )  );
		  index  ++  ;
		  pListCtrl->SetItemText(  cnt,  index,  pObj->ucbLoaded  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_loaded  )  :  _T(  ""  )  );
		  index  ++  ;


		  if  (  idSelected  ==  pObj->iDsnIndex  )  tmpnItem  =  cnt;

		  cnt  ++  ;
		  
	 }

	 	
	 if  (  tmpnItem  >=  0  )  {
		
			pListCtrl->SetItemState(  tmpnItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			pListCtrl->Update(  tmpnItem  );

	 }

	 
	 if  (  pnItemSelected  )  *pnItemSelected  =  tmpnItem;


	 return  0;
}

BOOL CDlgQyCfgSystems::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	CListCtrl				*	pListCtrl	=	NULL;
	
	m_var.idcList  =  IDC_LIST1;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	//  GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	m_var.pColumns  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_qyCfgSystemsColumns  );	

	//  _sntprintf(  m_var.sqlBuf,  mycountof(  m_var.sqlBuf  ),  _T(  "select id,uiLangId,objName0,cusName0,objName1,cusName1,objName2,cusName2,objname3,cusName3,objName4,cusName4,objName5,cusName5,objName6,cusName6,objName7,cusName7 from qyCusNameTab where iType=%d order by objName0,objName1,objName2,objName3,objName4"  ),  CONST_cusNameType_pcRegInfo  );
	
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
	
	listProcedObjs(  pListCtrl,  -1,  0  );

	bRefreshButtons(  );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 BOOL  CDlgQyCfgSystems::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;
}

void CDlgQyCfgSystems::OnAdd() 
{
	// TODO: Add your control notification handler code here
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CDlgQyCfgSystem			dlg;
	int						id;
	QY_OBJ_DB			*	pObj;

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		id  =  dlg.m_var.obj.iDsnIndex;
		if  (  id  <  0  ||  id  >=  mycountof(  pQyMc->procedObjDbs  )  )  goto  errLabel;
		pObj  =  &pQyMc->procedObjDbs[id];
		if  (  pObj->ucbUsed  )  goto  errLabel;
		memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		pObj->iDsnIndex  =  id;
		memcpy(  &pObj->cfg,  &dlg.m_var.obj.cfg,  sizeof(  pObj->cfg  )  );
		pObj->ucbUsed  =  TRUE;
		listProcedObjs(  (  CListCtrl  *  )GetDlgItem(  m_var.idcList  ),  dlg.m_var.obj.iDsnIndex,  &m_var.nItemSelected  );
	}	
	
	bRefreshButtons(  );

errLabel:
	return;
}

void CDlgQyCfgSystems::OnModify() 
{
	// TODO: Add your control notification handler code here
	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 int			id;
	 CString		str;
	 TCHAR		*	pT;
	 
	 CListCtrl  *  pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	 if  (  m_var.nItemSelected  <  0  )  return;
	 str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );
	 id  =  _tcstol(  str,  &pT,  10  );
	 
	 if  (  pQyMc->procedObjDbs[id].ucbLoaded  )  {
		 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotModifyIfLoaded  )  );  return;
	 }

	 CDlgQyCfgSystem		dlg;

	 dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  id  );
	 dlg.DoModal(  );
	 if  (  dlg.m_var.ucbChanged  )  {
		 memcpy(  &pQyMc->procedObjDbs[id],  &dlg.m_var.obj,  sizeof(  QNM_DB_CFG  )  );
	 	 listProcedObjs(  (  CListCtrl  *  )GetDlgItem(  m_var.idcList  ),  dlg.m_var.obj.iDsnIndex,  &m_var.nItemSelected    );
	 }
	

	 bRefreshButtons(  );

}

 void CDlgQyCfgSystems::OnDel() 
{
	 QY_MC		*	pQyMc			=		QY_GET_GBUF(  );
	 int			id;
	 CString		str;
	 TCHAR		*	pT;
	 char			regValName[256];
	 
	 CListCtrl  *  pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	 if  (  m_var.nItemSelected  <  0  )  return;
	 str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );
	 id  =  _tcstol(  str,  &pT,  10  );

	 if  (  pQyMc->procedObjDbs[id].ucbLoaded  )  {
		 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotDeleteIfLoaded  )  );  return;
	 }

	 if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDelete  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	 _snprintf(  regValName,  sizeof(  regValName  ),  "%s%d",  CONST_regValName_procedSysStr,  id  );
	 qyDelRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CString(  regValName  )  );
	 
	 memset(  &pQyMc->procedObjDbs[id],  0,  sizeof(  pQyMc->procedObjDbs[id]  )  );
	 
	 listProcedObjs(  (  CListCtrl  *  )GetDlgItem(  m_var.idcList  ),  id  -  1,  &m_var.nItemSelected    );


	 bRefreshButtons(  );

	 return;
	
}

void CDlgQyCfgSystems::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	
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



void CDlgQyCfgSystems::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	 QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	 int			id;
	 CString		str;
	 TCHAR		*	pT;
	 
	 CListCtrl  *  pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	 if  (  m_var.nItemSelected  <  0  )  return;
	 str  =  pListCtrl->GetItemText(  m_var.nItemSelected,  0  );
	 id  =  _tcstol(  str,  &pT,  10  );

	 if  (  pQyMc->procedObjDbs[id].ucbLoaded  )  {
		 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotModifyIfLoaded  )  );  return;
	 }

	 CDlgQyCfgSystem		dlg;

	 dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  id  );
	 dlg.DoModal(  );
	 if  (  dlg.m_var.ucbChanged  )  {
		 memcpy(  &pQyMc->procedObjDbs[id],  &dlg.m_var.obj,  sizeof(  QNM_DB_CFG  )  );
	 	 listProcedObjs(  (  CListCtrl  *  )GetDlgItem(  m_var.idcList  ),  dlg.m_var.obj.iDsnIndex,  &m_var.nItemSelected    );
	 }


	 bRefreshButtons(  );

	*pResult = 0;
}
