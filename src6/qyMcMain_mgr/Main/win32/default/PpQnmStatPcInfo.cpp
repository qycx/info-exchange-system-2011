// PpQnmStatPcInfo.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"PpQnmStatPcInfo.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatPcInfo property page

IMPLEMENT_DYNCREATE(CPpQnmStatPcInfo, CPropertyPage)

CPpQnmStatPcInfo::CPpQnmStatPcInfo() : CPropertyPage(CPpQnmStatPcInfo::IDD)
{
	//{{AFX_DATA_INIT(CPpQnmStatPcInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CPpQnmStatPcInfo::~CPpQnmStatPcInfo()
{
}

void CPpQnmStatPcInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQnmStatPcInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQnmStatPcInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQnmStatPcInfo)
	ON_CBN_SELCHANGE(IDC_COMBO0, OnSelchangeCombo0)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatPcInfo message handlers

BOOL CPpQnmStatPcInfo::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QY_IDCITEM		*	pTable0		=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatPcInfoTable0  );
	QY_IDCITEM		**	ppTables	=	(  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatPcInfoCb0Tables  );
	int					nTables		=	getnTables(  ppTables  );
	int					iCurSel		=	0;
	QY_IDCITEM		*	pCurTable	=	NULL;

	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pTable0  );
	
	if  (  iCurSel  <  nTables  
		&&  (  pCurTable  =  ppTables[iCurSel]  )  )
	{
		qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );
	}

	
	return  TRUE;  // return TRUE unless you set the focus to a control
	               // EXCEPTION: OCX Property Pages should return FALSE
}

void CPpQnmStatPcInfo::OnSelchangeCombo0() 
{	 
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 QY_IDCITEM		*	pTable0		=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatPcInfoTable0  );
	 QY_IDCITEM		**	ppTables	=	(  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatPcInfoCb0Tables  );
	 int				nTables		=	getnTables(  ppTables  );
	 int				iCurSel		=	-1;
	 QY_IDCITEM		*	pCurTable	=	NULL;
	 
	 if  (  (  iCurSel  =  GetDlgItem(  IDC_COMBO0  )->SendMessage(  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return;
	 if  (  iCurSel  >=  nTables  )  return;
	 pCurTable  =  ppTables[iCurSel];
	 if  (  !pCurTable  )  return;
	
	 qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );

}


 LRESULT  CPpQnmStatPcInfo::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	int					iState;
	
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_chkPage:
				  if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_pc  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  
					  &&  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_os  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  
						&&  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_mac  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  )  
				  {
					  qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askForContentOfStat  )  );
					  goto  errLabel;
				  }
				  pComm->u.chkPage.IDD  =  CPpQnmStatPcInfo::IDD;
				  pComm->u.chkPage.bOk  =  TRUE;
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}


void CPpQnmStatPcInfo::OnOK() 
{
	QY_MC			*	pQyMc  =  QY_GET_GBUF(  );
	char				buf[1024];
	TCHAR				buf1[CONST_qyMaxSqlClauseLen  +  1];
	QY_IDCITEM		*	pTable0			=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatPcInfoTable0  );
	QY_IDCITEM		*	pItem			=	NULL;
	char				itemBuf[256];
	int					iCurSel			=	-1;
	int					i;
	int					iRet;
	int					nCols			=	0;
	int					iState;
	BOOL				bPcStated	=	FALSE,  bOsStated  =  FALSE,  bMacStated  =  FALSE;
	TCHAR				iifBuf[1024];
	TCHAR				condBuf[2048];
	CString				str;

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return;	//  2007/01/03

	if  (  (  (  CPropertySheet  *  )GetParent(  )  )->GetActivePage(  )  !=  this  )  {
		traceLogA(  "The active page is not pcInfo, so returns."  );  return;
	}

	UpdateData(  TRUE  );

	for  (  pItem  =  pTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  continue;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_comboDesc  )  break;
	}
	if  (  pItem->idc  ==  -1  )  {
		MACRO_qyAssert(  0,  _T(  "统计缺少分组项CONST_qyIdcType_comboDesc"  )  );
		return;
	}
	iCurSel  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETCURSEL,  0,  0  );
	if  (  iCurSel  !=  CB_ERR  )  {
		for  (  i  =  0;  i  <=  iCurSel;  i  ++  )  {
			 iRet  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETLBTEXT,  i,  (  LPARAM  )itemBuf  );
		 	 MACRO_qyAssert(  iRet  !=  CB_ERR  &&  iRet  <  sizeof(  itemBuf  ),  _T(  "CPpQnmStatGeneral越界"  )  );
		 	 qnmFillColInfo(  nCols,  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData,  SQL_CHAR,  CONST_qyColumnDisplayType_str,  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].des,  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		 	 nCols  ++  ;
		 	 if  (  !m_var.groupPart[0]  )  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
		 	 else  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  CString(  m_var.groupPart  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
		}
	}
	
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
				 tmpInAddr.s_addr  =  qyhtonl(  dwIp  );
				 sprintf(  buf,  inet_ntoa(  tmpInAddr  )  );
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
			 }
			 continue;	
		 }
		 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  )  {
		     iCurSel  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETCURSEL,  0,  0  );
			 if  (  iCurSel  ==  CB_ERR  )  continue;
			 if  (  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[iCurSel].type  ==  CONST_qyStatType_all  )  {
			     MACRO_qyAssert(  0,  _T(  "CONST_qyStatType_all not supported now."  )  );
				 continue;
			 }
			 if  (  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[iCurSel].type  ==  CONST_qyStatType_others  )  {
			     buf1[0]  =  0;
				 for  (  QY_DMITEM  *  p1  =  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  );  p1->type  !=  -1;  p1  ++  )  {
				      if  (  p1->type  ==  CONST_qyStatType_others  ||  p1->type  ==  CONST_qyStatType_all  )  continue;
					  if  (  !buf1[0]  )  _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "not (%s='%s'"  ),  pItem->sqlColName,  p1->des  );
					  else  _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "%s or %s='%s'"  ),  buf1,  pItem->sqlColName,  p1->des  );
				 }
				 if  (  buf1[0]  )  _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "%s)"  ),  buf1  );
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s or %s is null"  ),  m_var.wherePart,  CString(  buf1  ),  pItem->sqlColName  );
				 continue;
			 }
			 //  以下是普通的combo处理
			 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
			 trim(  buf  );
			 if  (  buf[0]  )  {
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  m_var.wherePart,  pItem->sqlColName,  CString(  buf  )  );
			 }
			 continue;			
		 }
	 
		 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
		 trim(  buf  );
		 if  (  buf[0]  )  {
			 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
			 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
		 }
	}
	

	//
	char										dbTypeName[32  +  1];	//  2006/12/18
	myTChar2Str(  qyGetDesByType1(  CONST_dbTypeTable,  m_var.pObjDb->cfg.iDbType  ),  dbTypeName,  mycountof(  dbTypeName  )  );


	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_pc  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bPcStated  =  TRUE;
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_os  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bOsStated  =  TRUE;
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_mac  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bMacStated  =  TRUE;
	if  (  !bPcStated  &&  !bOsStated  &&  !bMacStated  )  {
		MACRO_qyAssert(  0,  _T(  "请选择统计内容"  )  );
		return;
	}
	if  (  bPcStated  )  {
		qnmFillColInfo(  nCols,  _T(  "count(qyPcTab.mac0)"  ),		SQL_INTEGER,	CONST_qyColumnDisplayType_long,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  ),	80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;		
	}
	if  (  bOsStated  )  {
		QY_DMITEM	*	tmppTable		=	CONST_qyPlatformTable;
		QY_DMITEM	*	p1				=	NULL;

		MACRO_qyAssert(  tmppTable[0].type  !=  -1,  _T(  "tmppTable为空"  )  );
		for  (  p1  =  tmppTable;  p1->type  !=  -1;  p1  ++  )  {
			 //  _snprintf(  buf1,  sizeof(  buf1  ),  "sum(IIF(qyPcTab.osName like '%s',1,0))",  p1->des  );
			_sntprintf(  condBuf,  sizeof(  condBuf  )  /  sizeof(  TCHAR  ),  _T(  "qyPcTab.osName like '%s'"  ),  p1->des  );
			_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_s(  dbTypeName,  condBuf,  _T(  "1"  ),  _T(  "0"  ),  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
			 qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  p1->des,  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
			 nCols  ++  ;
			 if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
		}
		buf1[0]  =  0;  condBuf[0]  =  0;
		for  (  p1  =  tmppTable;  p1->type  !=  -1;  p1  ++  )  {
			 //  if  (  !buf1[0]  )  _snprintf(  buf1,  sizeof(  buf1  ),  "sum(IIF(not(qyPcTab.osName like '%s'",  p1->des  );  
			 //  else  _snprintf(  buf1,  sizeof(  buf1  ),  "%s or qyPcTab.osName like '%s'",  buf1,  p1->des  );
			 if  (  !condBuf[0]  )  _sntprintf(  condBuf,  sizeof(  condBuf  )  /  sizeof(  TCHAR  ),  _T(  "not(qyPcTab.osName like '%s'"  ),  p1->des  );  //  2004/03/18
			 else  _sntprintf(  condBuf,  sizeof(  condBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s or qyPcTab.osName like '%s'"  ),  condBuf,  p1->des  );
		}
		//  _snprintf(  buf1,  sizeof(  buf1  ),  "%s ) or qyPcTab.osName is null,1,0))",  buf1  );
		_sntprintf(  condBuf,  sizeof(  condBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s ) or qyPcTab.osName is null"  ),  condBuf  );
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_s(  dbTypeName,  condBuf,  _T(  "1"  ),  _T(  "0"  ),  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_otherOs  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
	}
	if  (  bMacStated  )  {
		//  _snprintf(  buf1,  sizeof(  buf1  ),  "sum(IIF(qyPcTab.nMacs='1',1,0))"  );
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_s(  dbTypeName,  _T(  "qyPcTab.nMacs='1'"  ),  _T(  "1"  ),  _T(  "0"  ),  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_networkCard  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
		//  _snprintf(  buf1,  sizeof(  buf1  ),  "sum(IIF(qyPcTab.nMacs<>'1',1,0))"  );
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_s(  dbTypeName,  _T(  "qyPcTab.nMacs<>'1'"  ),  _T(  "1"  ),  _T(  "0"  ),  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ), SQL_INTEGER,  CONST_qyColumnDisplayType_long,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_multiNetworkCard  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
	}
	qnmFillColInfo(  -1,	 _T(  ""  ),								0,			0,								_T(  ""  ),			0,	 &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
	nCols  ++  ;

	m_var.bOk  =  TRUE;

	CPropertyPage::OnOK();
}


