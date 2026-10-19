// DlgQnmCfgPcGrps.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgQnmCfgPcGrps.h"
#include	"dlgQnmCfgPcGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	extern  QY_COLUMNINFO  CONST_qnmCfgPcGrpsColumns[];
//	extern  QY_COLUMNINFO  CONST_qnmCfgPcGrpsColumns_nms[];

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcGrps dialog


CDlgQnmCfgPcGrps::CDlgQnmCfgPcGrps(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgPcGrps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgPcGrps)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmCfgPcGrps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgPcGrps)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgPcGrps, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgPcGrps)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_pcGrpList, OnItemchangedpcGrpList)
	ON_BN_CLICKED(IDC_CHECK_bNotAllAllowed, OnCHECKbNotAllAllowed)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_NOTIFY(NM_DBLCLK, IDC_pcGrpList, OnDblclkpcGrpList)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcGrps message handlers

 BOOL CDlgQnmCfgPcGrps::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	char					*	tmpPtr		=	NULL;
	CListCtrl				*	pListCtrl	=	NULL;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  if  (  pQyMc->iSystemId  !=  CONST_qySystemId_netMc2  )  GetDlgItem(  IDC_CHECK_bNotAllAllowed  )->ShowWindow(  SW_HIDE  );
	if  (  !pQyMc->cfg.pGuiCfg->ucbCfgNotAllAllowed  )  GetDlgItem(  IDC_CHECK_bNotAllAllowed  )->EnableWindow(  FALSE  );

	//  下面显示配置网段列表
	m_var.idcList  =  IDC_pcGrpList;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_nms  )  m_var.pColumns	 =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_qnmCfgPcGrpsColumns_nms  );
	else  m_var.pColumns  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_qnmCfgPcGrpsColumns  );
	
	_snprintf(  m_var.sqlBuf,  sizeof(  m_var.sqlBuf  ),  "select startIp,endIp,officeName,subOfficeName,ucbStopMacScan,ucbStopSnmpScan from qnmPcGrpTab order by startIp"  );
	
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
	
	refreshAll(  );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 
 LRESULT  CDlgQnmCfgPcGrps::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_getSelInfo:  {
				  QY_WMBUF_GETSELINFO	*	pGetSelInfo  =  (  QY_WMBUF_GETSELINFO  *  )pComm;

				  if  (  m_var.nItemSelected  <  0  )  goto  errLabel;
				  pGetSelInfo->iSel  =  m_var.nItemSelected;
				  getItemContent(  m_var.nItemSelected,  &pGetSelInfo->itemContent  );

				}
				  break;	
			default:
					goto  errLabel;
	}

	lRet  =  CONST_qyWmRc_ok;

errLabel:

	 return  lRet;
}


 void  CDlgQnmCfgPcGrps::refreshAll(  )
{
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pQyMc->gui.pDb  );
	CListCtrl				*	pListCtrl	=	NULL;
	int							nFields;
	CDBVariant					varVals[10];
	char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem;
	char						buf[128];
	QNM_PCGRP_RCD				pcGrpInfo;
	char						tmpBuf[256];
	TCHAR					*	pStopString;
	TCHAR						tBuf[256];

	m_var.bNotAllAllowed  =  FALSE;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),   _T(  CONST_regValName_bNotAllAllowed  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  m_var.bNotAllAllowed  =  TRUE;		
	}
	(  (  CButton  *  )GetDlgItem(  IDC_CHECK_bNotAllAllowed  )  )->SetCheck(  !m_var.bNotAllAllowed  ?  0  :  1  );
		

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
			  			  
			  memset(  &pcGrpInfo,  0,  sizeof(  pcGrpInfo  )  );

			  index  =  0;	//  startIp
			  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
			  if  (  lstrlen(  tBuf  )  >=  12  )  {
				  myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );  qyIp12ToStd(  tmpBuf,  pcGrpInfo.startIp  );  
			  }
			  index  ++  ;	//  endIp
			  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
			  if  (  lstrlen(  tBuf  )  >=  12  )  {
				  myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );  qyIp12ToStd(  tmpBuf,  pcGrpInfo.endIp  );
			  }
			  index  ++  ;	//  officeName
			  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
			  myTChar2Str(  tBuf,  pcGrpInfo.officeName,  sizeof(  pcGrpInfo.officeName  )  );
			  index  ++  ;	//  subOfficeName
			  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
			  myTChar2Str(  tBuf,  pcGrpInfo.subOfficeName,  sizeof(  pcGrpInfo.subOfficeName  )  );
			  index  ++  ;	//  ucbStopMacScan
			  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
			  if  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  )  pcGrpInfo.ucbStopMacScan  =  TRUE;
			  index  ++  ;	//  ucbStopSnmpScan
			  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
			  if  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  )  pcGrpInfo.ucbStopSnmpScan  =  TRUE;
			  index  ++  ;
	
			  pListCtrl->InsertItem(  nItem,  CString(  pcGrpInfo.startIp  )  );
			  pListCtrl->SetItemText(  nItem,  1,  CString(  pcGrpInfo.endIp  )  );
			  pListCtrl->SetItemText(  nItem,  2,  CString(  pcGrpInfo.officeName  )  );
			  pListCtrl->SetItemText(  nItem,  3,  CString(  pcGrpInfo.subOfficeName  )  );
			  pListCtrl->SetItemText(  nItem,  4,  CString(  pcGrpInfo.ucbStopMacScan  ?  _T(  ""  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  )  );
			  if  (  pQyMc->iSystemId  ==  CONST_qySystemId_nms  )  {
				  pListCtrl->SetItemText(  nItem,  5,  CString(  pcGrpInfo.ucbStopSnmpScan  ?  _T(  ""  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  )  );
			  }
			  
		 }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgQnmCfgPcGrps::refreshAll failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
}

void CDlgQnmCfgPcGrps::OnAdd() 
{
	CDlgQnmCfgPcGrp	 dlg;

	dlg.bSetDlgInfo(  CONST_qyDlgType_add,  this,  NULL  );
	dlg.DoModal(  );
	if  (  dlg.m_var.bChanged  )  refreshAll(  );
	
}

 //  指定管理代理
 void CDlgQnmCfgPcGrps::OnModify() 
{
	 CDlgQnmCfgPcGrp	dlg;

	 if  (  m_var.nItemSelected  >=  0  )  {
		 int	tmpnItem	=	m_var.nItemSelected;
		 QY_ITEMCONTENT		tmpItem;
		 CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
		
		 if  (  getItemContent(  tmpnItem,  &tmpItem  )  )  return;
				 
		 dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  this,  tmpItem.u.cols[0]  );
		 dlg.DoModal(  );

	 	 if  (  dlg.m_var.bChanged  )  refreshAll(  );	

	 }
}


 void CDlgQnmCfgPcGrps::OnDblclkpcGrpList(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	 CDlgQnmCfgPcGrp	dlg;

	 if  (  m_var.nItemSelected  >=  0  )  {
		 int	tmpnItem	=	m_var.nItemSelected;
		 QY_ITEMCONTENT		tmpItem;
		 CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
		
		 if  (  getItemContent(  tmpnItem,  &tmpItem  )  )  return;
				 
		 dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  this,  tmpItem.u.cols[0]  );
		 dlg.DoModal(  );

	 	 if  (  dlg.m_var.bChanged  )  refreshAll(  );	
	 
	 }


	 
	*pResult = 0;
}


 BOOL  CDlgQnmCfgPcGrps::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;
}


 int  CDlgQnmCfgPcGrps::getItemContent(  int nItem,  QY_ITEMCONTENT * pItemContent )
{
	 CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	 CString			str;
	 
	 if  (  nItem  <  0  )  return  -1;
	 
	 for  (  int  i  =  0;  i  <  m_var.nFields;  i  ++  )  {
		  str  =  pListCtrl->GetItemText(  nItem,  i  );  myTChar2Str(  str,  pItemContent->u.cols[i],  sizeof(  pItemContent->u.cols[i]  )  );
	 }
	 
	 return  0;	 

}


 void CDlgQnmCfgPcGrps::OnDel() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	CDBVariant	varVal[1];
	char		ip12[128];

	if  (  m_var.nItemSelected  >=  0  )  {
		int	tmpnItem	=	m_var.nItemSelected;
		QY_ITEMCONTENT		tmpItem;
		char				sqlBuf[QY_SQLBUFLEN  +  1];
		CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
		CString				str;
		
		if  (  getItemContent(  tmpnItem,  &tmpItem  )  )  return;

		str  =  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifDeleteNetworkSegment  )  )  +  tmpItem.u.cols[0]  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifDeleteNetworkSegmentSuffix  );
		if  (  AfxMessageBox(  str,  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;
		
		qyStdToIp12(  tmpItem.u.cols[0],  ip12  );
		sprintf(  sqlBuf,  "delete from  qnmPcGrpTab where startIp='%s'",  ip12  );
		if  (  !bQyExecSql(  (  CDatabase  *  )pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  return;
		pListCtrl->DeleteItem(  tmpnItem  );
		if  (  pListCtrl->GetItemCount(  ) >= tmpnItem  )  {
			tmpnItem  --;
		}
		if  (  tmpnItem  >=  0  )  {

			pListCtrl->SetItemState(  tmpnItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			pListCtrl->Update(  tmpnItem  );
			m_var.nItemSelected  =  tmpnItem;
			}
		else
			m_var.nItemSelected  =  -1;
				
		bRefreshButtons(  );
	
		m_var.bChanged  =  TRUE;	

		
	}
	
}


void CDlgQnmCfgPcGrps::OnItemchangedpcGrpList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW  *  pNMListView  =  (NM_LISTVIEW*)pNMHDR;
	
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

void CDlgQnmCfgPcGrps::OnCHECKbNotAllAllowed() 
{
	int		iRet;

	iRet  =  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_bNotAllAllowed  )  )->GetCheck(  );
	qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_bNotAllAllowed  ),  (  iRet  ==  1  )  ?  _T(  "1"  )  :  _T(  "0"  )  );
			
}


