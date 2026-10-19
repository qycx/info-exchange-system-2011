// PpQnmStatOthers.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"PpQnmStatOthers.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatOthers property page

IMPLEMENT_DYNCREATE(CPpQnmStatOthers, CPropertyPage)

CPpQnmStatOthers::CPpQnmStatOthers() : CPropertyPage(CPpQnmStatOthers::IDD)
{
	//{{AFX_DATA_INIT(CPpQnmStatOthers)
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CPpQnmStatOthers::~CPpQnmStatOthers()
{
}

void CPpQnmStatOthers::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQnmStatOthers)
	DDX_Control(pDX, IDC_STARTTIME, m_startTimeCtrl);
	DDX_Control(pDX, IDC_STARTDATE, m_startDateCtrl);
	DDX_Control(pDX, IDC_ENDTIME, m_endTimeCtrl);
	DDX_Control(pDX, IDC_ENDDATE, m_endDateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQnmStatOthers, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQnmStatOthers)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatOthers message handlers

 void CPpQnmStatOthers::OnOK() 
{
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	QY_IDCITEM		*	pTable0			=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatOthersTable0  );
	char				buf[1024];
	TCHAR				buf1[CONST_qyMaxSqlClauseLen  +  1];
	QY_IDCITEM		*	pItem			=	NULL;
	int					iCurSel			=	-1;
	int					nCols			=	0;
	int					iState			=	0;
	BOOL				bMszjjrStated	=  FALSE,  bZysjStated  =  FALSE;
	int					iEventType;
	int					i;
	TCHAR				iifBuf[128];
	CString				str;
	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return;

	if  (  (  (  CPropertySheet  *  )GetParent(  )  )->GetActivePage(  )  !=  this  )  return;
	
	UpdateData(  TRUE  );
		
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
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s or %s is null"  ),  CString(  m_var.wherePart  ),  CString(  buf1  ),  CString(  pItem->sqlColName  )  );
				 continue;
			 }
			 //  以下是普通的combo处理
			 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
			 trim(  buf  );
			 if  (  buf[0]  )  {
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
			 }
			 continue;			
		 }
	 
		 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
		 trim(  buf  );
		 if  (  buf[0]  )  {
			 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
			 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
		 }
	}

	char	tStartBuf[256],  tEndBuf[256];
	
	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  tStartBuf,  sizeof(  tStartBuf  ),  tEndBuf,  sizeof(  tEndBuf  )  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_timeErr2  )  );  return;
	}
	
	if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
	_sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s qyPcEventTab.cntEventTime>'%s' and qyPcEventTab.cntEventTime<'%s'"  ),  CString(  m_var.wherePart  ),  CString(  tStartBuf  ),  CString(  tEndBuf  )  );
 

	//
	char										dbTypeName[32  +  1];	//  2006/12/18
	myTChar2Str(  qyGetDesByType1(  CONST_dbTypeTable,  m_var.pObjDb->cfg.iDbType  ),  dbTypeName,  mycountof(  dbTypeName  )  );


	//  if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_mszjjr  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bMszjjrStated  =  TRUE;
	bZysjStated  =  TRUE;		//  强制统计主要事件
	
	if  (  !bMszjjrStated  &&  !bZysjStated  )  {
		MACRO_qyAssert(  0,  _T(  "请选择统计内容"  )  );  goto  errLabel;
	}
		
	if  (  bMszjjrStated  )  {
		iEventType  =  CONST_qyEventType_nm_strangePc;
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_i(  dbTypeName,  _T(  "qyPcEventTab.eventType"  ),  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  iEventType  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;		
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
	}

	if  (  bZysjStated  )  {
		QY_IDCITEM		*	pItem;
		QY_DMITEM		*	pEventTable;

		pItem  =  qyGetIdcItemByIdc(  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpNetDevEventListSearchTable0  ),  IDC_COMBO_eventType  );
		MACRO_qyAssert(  pItem,  _T(  "事件列表应加上"  )  );
		pEventTable  =  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  );
		MACRO_qyAssert(  pEventTable,  _T(  "事件列表不对"  )  );

		for  (  i  =  0;  pEventTable[i].type  !=  -1;  i  ++  )  {
			 iEventType  =  pEventTable[i].type;
			 _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_i(  dbTypeName,  _T(  "qyPcEventTab.eventType"  ),  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
			 qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  qyGetDesByType1(  pEventTable,  iEventType  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
			 nCols  ++  ;		
			 if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
		}		
	}

	qnmFillColInfo(  -1,	 _T(  ""  ),								0,			0,								_T(  ""  ),			0,	 &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
	nCols  ++  ;
	
	m_var.bOk  =  TRUE;

errLabel:

	CPropertyPage::OnOK();

}


BOOL CPpQnmStatOthers::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatOthersTable0  ),  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatOthersTable0  )  );

	CTime	t  =  CTime::GetCurrentTime( );
	CTimeSpan	ts(  1,  0,  0,  0  );
	CTimeSpan	ts1(  0,  1,  0,  0  ); 
	CTime	tStart(  t  -  ts  ),  tEnd(  t  +  ts1  );

	this->m_startDateCtrl.SetTime(  &tStart  );
	this->m_startTimeCtrl.SetTime(  &tStart  );
	this->m_endDateCtrl.SetTime(  &tEnd  );
	this->m_endTimeCtrl.SetTime(  &tEnd  );



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 LRESULT  CPpQnmStatOthers::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	int					iState;
	
	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  NULL,  0,  NULL,  0  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes, CONST_resId_timeErr2  )  );  goto  errLabel;
	}

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_chkPage:
				  if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_mszjjr  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  )  {
					  qyShowHint( getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askForContentOfStat  )  );
					  goto  errLabel;
				  }
				  pComm->u.chkPage.IDD  =  CPpQnmStatOthers::IDD;
				  pComm->u.chkPage.bOk  =  TRUE;
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}

