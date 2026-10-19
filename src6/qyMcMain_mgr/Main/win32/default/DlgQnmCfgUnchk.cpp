// DlgQnmCfgUnchk.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmCfgUnchk.h"
//  #include	"dlgIpEx.h"
#include	"dlgQnmCfgUnchkedIpGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgUnchk dialog

 QY_DMITEM  CONST_qnmUnchkedIpDesTable[]  =
{
	{	0,		_T(  "永久性免检"  ),	},
	{	1,		_T(  "临时性免检"  ),	},
	{	-1,		NULL,			},
};

#define		CONST_qnmTempUnchkedIpDes		CONST_qnmUnchkedIpDesTable[1].des


CDlgQnmCfgUnchk::CDlgQnmCfgUnchk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgUnchk::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgUnchk)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmCfgUnchk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgUnchk)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgUnchk, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgUnchk)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_tmpUnchkedIp, OnItemchangedLISTtmpUnchkedIp)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_unchkedIp, OnItemchangedLISTunchkedIp)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_tmpUnchkedIp, OnSetfocusLISTtmpUnchkedIp)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_unchkedIp, OnSetfocusLISTunchkedIp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgUnchk message handlers

 LRESULT  CDlgQnmCfgUnchk::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{	
	long					lRet				=					-1;
	QY_WMBUF_COMMHEAD	*	pCommHead			=					( QY_WMBUF_COMMHEAD * )lParam;
	QY_MC				*	pQyMc				=					QY_GET_GBUF(  );

	if  (  !pCommHead  )  goto  errLabel;

	switch  (  pCommHead->uiType  )  {
			case  CONST_qyWmParam_addIp:  {
				  QY_WMBUF_ADDIP  *		pAddIp  =  (  QY_WMBUF_ADDIP  *  )pCommHead;
				  BOOL					bTmp;
				  CString				sqlStr;
				  CDBVariant			varVal[3];
				  char					timeBuf[CONST_qyTimeLen  +  1];
				  char					startIp12[32  +  1],  endIp12[32  +  1];

				  if  (  !pAddIp->startIpBuf[0]  ||  !pAddIp->endIpBuf[0]  ||  !pAddIp->desBuf[0]  )  goto  errLabel;
				  qyStdToIp12(  pAddIp->startIpBuf,  startIp12  );
				  qyStdToIp12(  pAddIp->endIpBuf,  endIp12  );
				  bTmp  =  (  lstrcmp(  CString(  pAddIp->desBuf  ),  CONST_qnmTempUnchkedIpDes  )  ==  0  );
				  sqlStr  =  CString(  ""  )  +  "select startIp from qnmUnchkedIpTab where startIp='"  +  startIp12  +  "'";
				  if  (  bQyGetRcdBySql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  ),  1,  varVal  )  )  {
					  _snprintf(  pAddIp->errBuf,  sizeof(  pAddIp->errBuf  ),  "IP已在列表中"  );
					  goto  errLabel;
				  }
				  getCurTime(  timeBuf  );
				  sqlStr  =  CString(  ""  )  +  "insert into qnmUnchkedIpTab(startIp,endIp,bTmp,startTime) values('"  +  startIp12  +  "','"  +  endIp12  +  "','"  +  (  bTmp  ?  "1"  :  "0"  )  +  "','"  +  timeBuf  +  "')";
				  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

				  refreshAll(  );
				  
				}
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}


 void  CDlgQnmCfgUnchk::refreshAll(  )
{	 
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pQyMc->gui.pDb  );
	int							nFields;
	CDBVariant					varVal[CONST_qyMaxLvCols];
	char					*	tmpPtr			=	NULL;
	CString						sqlStr;	
	int							index;
	CListCtrl				*	pLvUnchkedIp	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_unchkedIp  );
	CListCtrl				*	pLvTmpUnchkedIp	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_tmpUnchkedIp  );
	int							nUnchkedIps		=	0;
	int							nTmpUnchkedIps	=	0;
	char						ip12Buf[12  +  1];
	struct						{
		char					startIpBuf[CONST_qyMaxIpLen  +  1];
		char					endIpBuf[CONST_qyMaxIpLen  +  1];
		unsigned  char			ucbTmp;
		char					timeBuf[CONST_qyTimeLen  +  1];
		char					displayBuf[256];
	}							unchkedIpStruct;
	TCHAR					*	pStopString;
	TCHAR						tBuf[256];

	
	pLvUnchkedIp->DeleteAllItems(  );
	pLvTmpUnchkedIp->DeleteAllItems(  );
	
	sqlStr  =  CString(  "select startIp,endIp,bTmp,startTime from qnmUnchkedIpTab order by startIp"  );

	try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  sqlStr  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 if  (  nFields  >  sizeof(  varVal  )  /  sizeof(  varVal[0]  )  )  {
			 traceLogA(  "%s: varVal is too small.",  __FILE__  );
			 goto  errLabel;
		 }
		 
		 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVal[index]  );
			  
			  memset(  &unchkedIpStruct,  0,  sizeof(  unchkedIpStruct  )  );
			  index  =  0;  MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  unchkedIpStruct.startIpBuf  );
			  index  =  1;  MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  unchkedIpStruct.endIpBuf  );
			  index  =  2;  MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  unchkedIpStruct.ucbTmp  =  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  );
			  index  =  3;  MACRO_sqlStr(  varVal[index],  tBuf,  mycountof(  tBuf  )  );  if  (  lstrlen(  tBuf  )  ==  CONST_qyTimeLen  )  {  myTChar2Str(  tBuf,  unchkedIpStruct.timeBuf,  sizeof(  unchkedIpStruct.timeBuf  )  );
																								qyDisplayTime(  unchkedIpStruct.timeBuf,  unchkedIpStruct.displayBuf,  sizeof(  unchkedIpStruct.displayBuf  )  );
                                                                                           }
			  if  (  unchkedIpStruct.ucbTmp  )  {
				  pLvTmpUnchkedIp->InsertItem(  nTmpUnchkedIps,  CString(  unchkedIpStruct.startIpBuf  )  );
				  pLvTmpUnchkedIp->SetItemText(  nTmpUnchkedIps,  1,  CString(  unchkedIpStruct.displayBuf  )  );
				  nTmpUnchkedIps  ++  ;				  
				}
			  else  {
					pLvUnchkedIp->InsertItem(  nUnchkedIps,  CString(  unchkedIpStruct.startIpBuf  )  );
					pLvUnchkedIp->SetItemText(  nUnchkedIps,  1,  CString(  unchkedIpStruct.endIpBuf  )  );
					nUnchkedIps  ++  ;
			  }
				  		  
		 }
		 
		 rs.Close(  );

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgQnmCfgUnchk::refreshAll failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	 
}

 void CDlgQnmCfgUnchk::OnAdd() 
{	
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	CListBox		*	pLb		=	(  CListBox  *  )GetDlgItem(  IDC_LIST_unchkedIp  );
		
	//  CDlgIpEx			dlg;
	CDlgQnmCfgUnchkedIpGrp	dlg;

	dlg.bSetDlgInfo(  CONST_qyDlgType_continuousAdd,  this->m_hWnd,  "添加免检查的IP",  "添加",  NULL,  CONST_qnmUnchkedIpDesTable  );
	dlg.DoModal(  );	
	
}



BOOL CDlgQnmCfgUnchk::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC		*  pQyMc	=  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	// TODO: Add extra initialization here
	CListCtrl	*	pLvUnchkedIp	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_unchkedIp  );
	CListCtrl	*	pLvTmpUnchkedIp	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_tmpUnchkedIp  );
	
	pLvUnchkedIp->ModifyStyle(  LVS_TYPEMASK,  LVS_REPORT | LVS_SINGLESEL  );
	pLvUnchkedIp->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
	pLvTmpUnchkedIp->ModifyStyle(  LVS_TYPEMASK,  LVS_REPORT | LVS_SINGLESEL  );
	pLvTmpUnchkedIp->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
	
	LV_COLUMN	lvc;
	lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.cx			=	120;
	lvc.fmt			=	LVCFMT_LEFT;
	lvc.iSubItem	=	0;
	lvc.pszText		=	_T(  "起始IP"  );
	pLvUnchkedIp->InsertColumn(  0,  &lvc  );
	lvc.iSubItem	=	1;
	lvc.pszText		=	_T(  "结束IP"  );
	pLvUnchkedIp->InsertColumn(  1,  &lvc  );


	lvc.iSubItem	=	0;
	lvc.pszText		=	_T(  "IP"  );
	pLvTmpUnchkedIp->InsertColumn(  0,  &lvc  );
	lvc.iSubItem	=	1;
	lvc.cx			=	130;
	lvc.pszText		=	_T(  "起始时间"  );
	pLvTmpUnchkedIp->InsertColumn(  1,  &lvc  );
	
	
	m_var.nItemTmpUnchkedIpSelected  =  m_var.nItemUnchkedIpSelected  =  -1;
	refreshAll(  );
	bRefreshButtons(  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgQnmCfgUnchk::OnItemchangedLISTtmpUnchkedIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW  *  pNMListView  =  (NM_LISTVIEW*)pNMHDR;
	
	if  (  pNMListView->iItem  >= 0 
		&&  pNMListView->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		m_var.nItemTmpUnchkedIpSelected  =  pNMListView->iItem;
		}
	else  {
		  m_var.nItemTmpUnchkedIpSelected  =  -1;
	}
	
	traceLogA(  "tmpUnchkedIp changed"  );
	bRefreshButtons(  );
		
	*pResult = 0;
}
	

void CDlgQnmCfgUnchk::OnItemchangedLISTunchkedIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if  (  pNMListView->iItem  >= 0 
		&&  pNMListView->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		m_var.nItemUnchkedIpSelected  =  pNMListView->iItem;
		}
	else  {
		  m_var.nItemUnchkedIpSelected  =  -1;
	}
	
	bRefreshButtons(  );
	
	traceLogA(  "unchkedIp changed"  );
	
	*pResult = 0;
}

BOOL  CDlgQnmCfgUnchk::bRefreshButtons(  )
{
	GetDlgItem(  IDC_DEL  )->EnableWindow(  m_var.nItemTmpUnchkedIpSelected  !=  -1  ||  m_var.nItemUnchkedIpSelected  !=  -1  );

	return  TRUE;
}

void CDlgQnmCfgUnchk::OnDel() 
{
	QY_MC		*	pQyMc			=	QY_GET_GBUF(  );
	CListCtrl	*	pLvUnchkedIp	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_unchkedIp  );
	CListCtrl	*	pLvTmpUnchkedIp	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_tmpUnchkedIp  );
	char			buf[256]		=	"";
	char			startIp12[12  +  1];
	CString			str;

	if  (  m_var.nItemTmpUnchkedIpSelected  >=  0  )  {
		str  =  pLvTmpUnchkedIp->GetItemText(  m_var.nItemTmpUnchkedIpSelected,  0  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
		}
	else  {  
		  str  =  pLvUnchkedIp->GetItemText(  m_var.nItemUnchkedIpSelected,  0  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	}

	if  (  !buf[0]  )  {
		MACRO_qyAssert(  0,  _T(  "DlgQnmCfgUnchk::OnDel"  )  ); 
		return;
	}

	if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  MB_YESNO  )  !=  IDYES  )  return;

	CString		sqlStr;

	qyStdToIp12(  buf,  startIp12  );
	sqlStr  =  CString(  "delete from qnmUnchkedIpTab where startIp='"  )  +  startIp12  +  "'";
	bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

	m_var.nItemTmpUnchkedIpSelected  =  m_var.nItemUnchkedIpSelected  =  -1;
	refreshAll(  );
	bRefreshButtons(  );
	
}


void CDlgQnmCfgUnchk::OnSetfocusLISTtmpUnchkedIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl	*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_unchkedIp  );
	int				tmpnItem;

	if  (  m_var.nItemUnchkedIpSelected  !=  -1  )  {
		tmpnItem  =  m_var.nItemUnchkedIpSelected;
		pListCtrl->SetItemState(  tmpnItem,  0,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
		pListCtrl->Update(  tmpnItem  );
		m_var.nItemUnchkedIpSelected  =  -1;
		bRefreshButtons(  );
	}


	*pResult = 0;
}

void CDlgQnmCfgUnchk::OnSetfocusLISTunchkedIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl	*	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  IDC_LIST_tmpUnchkedIp  );
	int				tmpnItem;

	if  (  m_var.nItemTmpUnchkedIpSelected  !=  -1  )  {
		tmpnItem  =  m_var.nItemTmpUnchkedIpSelected;
		pListCtrl->SetItemState(  tmpnItem,  0,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
		pListCtrl->Update(  tmpnItem  );
		m_var.nItemTmpUnchkedIpSelected  =  -1;
		bRefreshButtons(  );
	}
	
	*pResult = 0;
}
