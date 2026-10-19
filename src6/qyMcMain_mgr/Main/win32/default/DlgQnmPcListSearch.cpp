// DlgQnmPcListSearch.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgQnmPcListSearch.h"
#include	"qyLangCommProc.h"
//
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcListSearch dialog


CDlgQnmPcListSearch::CDlgQnmPcListSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmPcListSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmPcListSearch)
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmPcListSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmPcListSearch)
	DDX_Control(pDX, IDC_IP, m_ip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmPcListSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmPcListSearch)
	ON_CBN_SELCHANGE(IDC_COMBO0, OnSelchangeCombo0)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcListSearch message handlers


 void  qnmSizeSearchControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  	 QY_IDCITEM  *  pTable0,	QY_IDCITEM		*	pCurTable  )
{
	HDWP			hdwp; 
	HWND			hWnd,  prevhWnd		=  NULL;
	int				cnt					=	0;
	QY_IDCITEM	*	pItem				=	NULL;
	QY_IDCITEM  *	tmppItem			=	NULL;
	
	if  (  !pCurTable  )  return;

	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {
		 cnt  ++  ;
	}
	// size the tree control accordingly
	hdwp  =  BeginDeferWindowPos(  cnt  ); 
	
	for  (  pItem  =  pCurTable;  pItem->idc  !=  -1;  pItem  ++  )  {

		 hWnd = ::GetDlgItem(  hDlg,  pItem->idc  );             
		 //  MACRO_qyAssert(  hWnd,  (  CString(  pItem->name  ?  pItem->name  :  "Î´ÃüÃû¿Ø¼þ"  )  +  " is not a controls"  ).GetBuffer(  0  )  );
		 if  (  !hWnd  )  continue;

		 if  (  pCurTable  !=  pTable0  )  {
		 	 tmppItem  =  qyGetIdcItemByIdc(  pTable0,  pItem->idc  );
		 	 if  (  tmppItem  )  tmppItem->flg  =  pItem->flg;
		 }
				 
		 ::DeferWindowPos(  hdwp, 
							hWnd,  prevhWnd  ?  prevhWnd  :  HWND_TOP, 
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->x  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->y  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->w  ),  
							(  int  )(  CONST_factorOfDlgUnit  *  pItem->h  ),  
							(  pItem->flg  &  CONST_qyIdcFlgHide  )  ?  SWP_HIDEWINDOW  :  SWP_SHOWWINDOW  );  
		 prevhWnd  =  hWnd;

		 switch  (  pItem->idcType  )  {
				 case  CONST_qyIdcType_static:
		 			   if  (  pItem->des  )  SetWindowText(  hWnd,  CString(  pItem->des  )  );
					   break;
				 case  CONST_qyIdcType_combo:
			 	 case  CONST_qyIdcType_comboDesc:
					   if  (  pItem->iResIdTable  )  {
					   	   QY_DMITEM	*	pDm  =  NULL;
					   
						   SendMessage(  hWnd,  CB_RESETCONTENT,  0,  0  );
						   if  (  pItem->flg  &  CONST_qyIdcFlgAddNullItem  )  SendMessage(  hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )_T(  ""  )  );
					   	   for  (  pDm  =  getResTable(  0,  (  QNM_CUSRES_INFO  *  )pCusRes,   pItem->iResIdTable  );  pDm->type  !=  -1;  pDm  ++  )  {
							    SendMessage(  hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )pDm->des  );								    
					   	   }							   
						   //  if  (  pItem->des  &&  pItem->des[0]  )  SendMessage(  hWnd,  CB_SELECTSTRING,  -1,  (  LPARAM  )pItem->des  );
						   SendMessage(  hWnd,  CB_SETCURSEL,  0,  (  LPARAM  )0  );
				   	   }
				   	   break;
				 case  CONST_qyIdcType_chk:
					   if  (  pItem->des  )  SetWindowText(  hWnd,  CString(  pItem->des  )  );
					   SendMessage(  hWnd,  BM_SETCHECK,  pItem->maxBytes  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
					   break;
			 	 default:
						 break;

		 }
		 EnableWindow(  hWnd,  !(  pItem->flg  &  CONST_qyIdcFlgDisabled  )  );
	}
		
	EndDeferWindowPos(  hdwp  );

	return;

}



BOOL CDlgQnmPcListSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchTable0  ),  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchTable0  )  );
	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_nms  )  {
		GetDlgItem(  IDC_EDIT_nDays  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_nDays  )->ShowWindow(  SW_HIDE  );
	}

	QY_IDCITEM  *	pItem  =  NULL;
	int				cnt  =  0;

	for  (  pItem  =  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchTable0  );  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  ==  CONST_qyIdcType_edit  )  {
			 m_edits[cnt].setType(  CONST_qyEditType_custom,  pItem->flg,  NULL  );
			 m_edits[cnt].SubclassDlgItem(  pItem->idc,  this  );
			 GetDlgItem(  pItem->idc  )->SendMessage(  EM_SETLIMITTEXT,  pItem->maxBytes,  0  );
			 cnt  ++  ;
		 }
	}
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 


void CDlgQnmPcListSearch::OnOK() 
{
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				i;

	if  (  !m_var.pDbBufs  )  return;

	UpdateData(  TRUE  );

	for  (  i  =  0;  ;  i  ++  )  {
		 if  (  m_var.pDbBufs[i].iDbType  ==  -1  )  break;

		 m_var.wherePart[0]  =  0;
		 if  (  getWherePart(  m_var.pDbBufs[i].iDbType  )  )  continue;

		 lstrcpyn(  m_var.pDbBufs[i].tBuf,  m_var.wherePart,  mycountof(  m_var.pDbBufs[i].tBuf  )  );

	}


	_sntprintf(  m_var.col0,  sizeof(  m_var.col0  )  /  sizeof(  TCHAR  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qySearch  )  );
	
	CDialog::OnOK();


}
 int CDlgQnmPcListSearch::getWherePart(  int  iDbType  ) 
{
	QY_MC		*	pQyMc			=	QY_GET_GBUF(  );
	char			buf[1024];
	QY_IDCITEM	*	pTable0			=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchTable0  );
	QY_IDCITEM	*	pItem			=	NULL;
	CString			str;
	

	for  (  pItem  =  pTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  
			 &&  pItem->idcType  !=  CONST_qyIdcType_edit  
				&&  pItem->idcType  !=  CONST_qyIdcType_ip  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  continue;
		 if  (  !pItem->sqlColName  ||  !pItem->sqlColName[0]  )  continue;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_ip  )  {
			 DWORD					dwIp;
			 struct  in_addr		tmpInAddr;

			 if  (  4  ==  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&dwIp  )  )  {
				 char			ip12Buf[128]	=	"";
				 //
				 tmpInAddr.s_addr  =  qyhtonl(  dwIp  );
				 sprintf(  buf,  inet_ntoa(  tmpInAddr  )  );
				 qyStdToIp12(  buf,  ip12Buf  );
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  m_var.wherePart,  pItem->sqlColName,  CString(  ip12Buf  )  );
			 }
			}
		 else  {
				GetDlgItemText(  pItem->idc,  str  );  MACRO_CStringTrim(  str  );
				if  (  str.GetLength(  )  )  {
					if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
					_sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s=%s"  ),  m_var.wherePart,  pItem->sqlColName,  getDbValStr(  iDbType,  pItem->uiCommSeqNo,  str  )  );
				}
		 }
		 		 
	}

	GetDlgItemText(  IDC_EDIT_mac,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	trim(  buf  );
	if  (  buf[0]  )  {
		if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
        _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s (qyPcTab.mac0='%s' or qyPcTab.mac1='%s' or qyPcTab.mac2='%s')"  ), m_var.wherePart,  CString(  buf  ),  CString(  buf  ),  CString(  buf  )  );
	}

	int		nDays;
	GetDlgItemText(  IDC_EDIT_nDays,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	nDays  =  atol(  buf  );
	if  (  nDays  >  0  )  {
		CTime	t;
		CTimeSpan  ts(  nDays,  0,  0,  0  );
		t  =  CTime::GetCurrentTime(  );
		t  -=  ts;

		sprintf(  buf,  "qyPcTab.lastCommTime<'%04d%02d%02d%02d%02d%02d'",  t.GetYear(  ),  t.GetMonth(  ),  t.GetDay(  ),  t.GetHour(  ),  t.GetMinute(  ),  t.GetSecond(  )  );
		if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
		_sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s"  ),  m_var.wherePart,  CString(  buf  )  );
	}

	traceLogA(  "wherePart is [%s]",  m_var.wherePart  );
	return  0;
}



void CDlgQnmPcListSearch::OnSelchangeCombo0() 
{
	// TODO: Add your control notification handler code here
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 int				iCurSel		=  -1;
	 int				nTables		=  getnTables(  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchCb0Tables  )  );
	 QY_IDCITEM		*	pCurTable	=	NULL;
	 
	 if  (  (  iCurSel  =  GetDlgItem(  IDC_COMBO0  )->SendMessage(  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return;
	 if  (  iCurSel  >=  nTables  )  return;
	 pCurTable  =  (  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchCb0Tables  )  )[iCurSel];
	 if  (  !pCurTable  )  return;
	
	 qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchTable0  ),  pCurTable  );
	 
}

void CDlgQnmPcListSearch::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 int				iCurSel		=  -1;
	 int				nTables		=  getnTables(  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchCb1Tables  )  );
	 QY_IDCITEM		*	pCurTable	=	NULL;

	 
	 if  (  (  iCurSel  =  GetDlgItem(  IDC_COMBO1  )->SendMessage(  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return;
	 if  (  iCurSel  >=  nTables  )  return;
	 pCurTable  =  (  (  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchCb1Tables  )  )[iCurSel];
	 if  (  !pCurTable  )  return;
	
	 qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpPcListSearchTable0  ),  pCurTable  );
	
}


