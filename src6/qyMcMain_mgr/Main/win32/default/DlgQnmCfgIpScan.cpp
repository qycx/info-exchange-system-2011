// DlgQnmCfgIpScan.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgQnmCfgIpScan.h"
#include	"dlgQnmCfgIpGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgIpScan dialog


CDlgQnmCfgIpScan::CDlgQnmCfgIpScan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgIpScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgIpScan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgQnmCfgIpScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgIpScan)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgIpScan, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgIpScan)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ipGrpList, OnItemchangedipGrpList)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgIpScan message handlers

BOOL CDlgQnmCfgIpScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	char					*	tmpPtr		=	NULL;
	CListCtrl				*	pListCtrl	=	NULL;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	m_var.idcList  =  IDC_ipGrpList;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
	m_var.pColumns	=  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_qnmCfgIpScanColumns  );
	
	int i;

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

	_snprintf(  m_var.sqlBuf,  sizeof(  m_var.sqlBuf  ),  "select startIp,endIp,officeName,subOfficeName from qnmIpScanTab order by startIp"  );

	refreshAll(  );
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 void  CDlgQnmCfgIpScan::refreshAll(  )
{	 
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pQyMc->gui.pDb  );
	CListCtrl				*	pListCtrl	=	NULL;
	int							nFields;
	CDBVariant					varVal[CONST_qyMaxLvCols];
	//  char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem,  nSubItem;
	CString						str;
	char						buf[128];
	char						tmpBuf[128];
	TCHAR					*	pStopString;
	TCHAR						tBuf[256];
		

	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	pListCtrl->DeleteAllItems(  );

	try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  CString(  m_var.sqlBuf  )  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 if  (  nFields  >  sizeof(  varVal  )  /  sizeof(  varVal[0]  )  )  {
			 traceLogA(  "%s: varVal is too small.",  __FILE__  );
			 goto  errLabel;
		 }
		 if  (  nFields  !=  m_var.nFields  )  {
			 MACRO_qyAssert(  FALSE,  _T(  "CDlgQnmCfgIpScan nFields != m_var.nFields"  )  );
			 goto  errLabel;
		 }
		 
		 for  (  nItem  =  0;  !rs.IsEOF(  );  rs.MoveNext(  ),  nItem  ++  )  {

			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVal[index]  );
			  
			  for  (  nSubItem  =  0;  nSubItem  <  m_var.nFields;  nSubItem  ++  )  {
				   MACRO_sqlStr(  varVal[nSubItem],  tBuf,  mycountof(  tBuf  )  );
				   //
				   str  =  CString(  ""  );				   				 
				   switch  (  m_var.pColumns[nSubItem].type  )  {
						   case  CONST_qyColumnDisplayType_ip12:  
							     if  (  lstrlen(  tBuf  )  ==  12  )  {
					     			 myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );
						 			 if  (  qyIp12ToStd(  tmpBuf,  buf  )  )  str  =  CString(  buf  );						 
			  					 }
								 break;
						   case  CONST_qyColumnDisplayType_bool:
							     if  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  )  str  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  );
								 break;
						   default:
							       str  =  tBuf;
								   break;
				   }

				   if  (  !nSubItem  )  pListCtrl->InsertItem(  nItem,  str  );
				   else  pListCtrl->SetItemText(  nItem,  nSubItem,  str  );
			  }

		 }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgQnmCfgIpScan::refreshAll failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
}


 BOOL  CDlgQnmCfgIpScan::bRefreshButtons(  )
{
	GetDlgItem(  IDC_MODIFY  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemSelected  >=  0  );
	return  TRUE;
}

 int  CDlgQnmCfgIpScan::getItemContent(  int  nItem,  QY_ITEMCONTENT  *  pItemContent  )
{
	 CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	 CString			str;
	 
	 if  (  nItem  <  0  )  return  -1;
	 
	 for  (  int  i  =  0;  i  <  m_var.nFields;  i  ++  )  {
		  str  =  pListCtrl->GetItemText(  nItem,  i  );  myTChar2Str(  str,  pItemContent->u.cols[i],  sizeof(  pItemContent->u.cols[i]  )  );
	 }
	 
	 return  0;	 

}




void CDlgQnmCfgIpScan::OnAdd() 
{

	CDlgQnmCfgIpGrp		dlg;

	dlg.bSetDlgInfo(  CONST_qyDlgType_add,  this  );
	dlg.DoModal(  );
	if  (  dlg.m_var.bChanged  )  refreshAll(  );

}

void CDlgQnmCfgIpScan::OnItemchangedipGrpList(NMHDR* pNMHDR, LRESULT* pResult) 
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



void CDlgQnmCfgIpScan::OnDel() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	char		ip12[128];

	if  (  m_var.nItemSelected  >=  0  )  {
		int	tmpnItem	=	m_var.nItemSelected;
		QY_ITEMCONTENT		tmpItem;
		char				sqlBuf[QY_SQLBUFLEN  +  1];
		CListCtrl		*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

		if  (  getItemContent(  tmpnItem,  &tmpItem  )  )  return;

		if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  MB_YESNO  )  !=  IDYES  )  return;
	
		qyStdToIp12(  tmpItem.u.cols[0],  ip12  );
		sprintf(  sqlBuf,  "delete from  qnmIpScanTab where startIp='%s'",  ip12  );
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


