// PpQnmStatGeneral.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"PpQnmStatGeneral.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatGeneral property page

IMPLEMENT_DYNCREATE(CPpQnmStatGeneral, CPropertyPage)

CPpQnmStatGeneral::CPpQnmStatGeneral() : CPropertyPage(CPpQnmStatGeneral::IDD)
{
	//{{AFX_DATA_INIT(CPpQnmStatGeneral)
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CPpQnmStatGeneral::~CPpQnmStatGeneral()
{	
}

void CPpQnmStatGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQnmStatGeneral)
	DDX_Control(pDX, IDC_STARTTIME, m_startTimeCtrl);
	DDX_Control(pDX, IDC_STARTDATE, m_startDateCtrl);
	DDX_Control(pDX, IDC_ENDTIME, m_endTimeCtrl);
	DDX_Control(pDX, IDC_ENDDATE, m_endDateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQnmStatGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQnmStatGeneral)
	ON_CBN_SELCHANGE(IDC_COMBO0, OnSelchangeCombo0)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatGeneral message handlers

BOOL CPpQnmStatGeneral::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	QY_IDCITEM		*	pTable0			=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatGeneralTable0  );
	QY_IDCITEM		**	ppTables		=	(  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatGeneralCb0Tables  );
	int					nTables			=	getnTables(  ppTables  );
	int					iCurSel			=	0;
	QY_IDCITEM		*	pCurTable		=	NULL;
	unsigned  char		ucbBhxwShow		=	FALSE;	//  因为主要事件能包含计算机变动，故不需要专门的选项，2003/12/08
	unsigned  char		ucbJsjbdShow	=	FALSE;	//  因为主要事件能包含计算机变动，故不需要专门的选项，2003/12/08

	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pTable0  );
	if  (  iCurSel  <  nTables
		&&  (  pCurTable  =  ppTables[iCurSel]  )  )
	{
		qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );
	}

	switch  (  qyGetSystemId(  )  )  {
			case  CONST_qySystemId_nms:
				  ucbBhxwShow  =  FALSE;
				  GetDlgItem(  IDC_CHECK_zysj  )->ShowWindow(  SW_HIDE  );
				  break;
			case  CONST_qySystemId_secChk:
				  ucbBhxwShow  =  FALSE;
				  ucbJsjbdShow  =  FALSE;
				  break;
			default:
					break;
	}
	if  (  !ucbBhxwShow  )  {
		GetDlgItem(  IDC_CHECK_bhxw  )->SendMessage(  BM_SETCHECK,  BST_UNCHECKED,  0  );
		GetDlgItem(  IDC_CHECK_bhxw  )->ShowWindow(  SW_HIDE  );
	}
	if  (  !ucbJsjbdShow  )  {
		GetDlgItem(  IDC_CHECK_jsjbd  )->SendMessage(  BM_SETCHECK,  BST_UNCHECKED,  0  );
		GetDlgItem(  IDC_CHECK_jsjbd  )->ShowWindow(  SW_HIDE  );
	}				  


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

void CPpQnmStatGeneral::OnSelchangeCombo0() 
{
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 QY_IDCITEM		*	pTable0		=	(  QY_IDCITEM  *  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_gpStatGeneralTable0  );
	 QY_IDCITEM		**	ppTables	=	(  QY_IDCITEM  **  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_gpStatGeneralCb0Tables  );
	 int				nTables		=	getnTables(  ppTables  );
	 int				iCurSel		=	-1;
	 QY_IDCITEM		*	pCurTable	=	NULL;
	 
	 if  (  (  iCurSel  =  GetDlgItem(  IDC_COMBO0  )->SendMessage(  CB_GETCURSEL,  0,  0  )  )  ==  CB_ERR  )  return;
	 if  (  iCurSel  >=  nTables  )  return;
	 pCurTable  =  ppTables[iCurSel];
	 if  (  !pCurTable  )  return;
	
	 qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );
	
}

 int  myMakeTime(  SYSTEMTIME  *  pDate,  SYSTEMTIME  *  pTime,  SYSTEMTIME  *  pT  )
{
	 pT->wYear  =  pDate->wYear;
	 pT->wMonth  =  pDate->wMonth;
	 pT->wDay  =  pDate->wDay;
	 pT->wHour  =  pTime->wHour;
	 pT->wMinute  =  pTime->wMinute;
	 pT->wSecond  =  pTime->wSecond;
	 pT->wMilliseconds  =  pTime->wMilliseconds;
	 
	 return  0;
}

 BOOL  bMyTimeInOrder(  SYSTEMTIME  *  pStart,  SYSTEMTIME  *  pEnd  )
{
	 if  (  pStart->wYear  <  pEnd->wYear  )  return  TRUE;
	 if  (  pStart->wYear  >  pEnd->wYear  )  return  FALSE;
	 if  (  pStart->wMonth  <  pEnd->wMonth  )  return  TRUE;
	 if  (  pStart->wMonth  >  pEnd->wMonth  )  return  FALSE;
	 if  (  pStart->wDay  <  pEnd->wDay  )  return  TRUE;
	 if  (  pStart->wDay  >  pEnd->wDay  )  return  FALSE;
	 if  (  pStart->wHour  <  pEnd->wHour  )  return  TRUE;
	 if  (  pStart->wHour  >  pEnd->wHour  )  return  FALSE;
	 if  (  pStart->wMinute  <  pEnd->wMinute  )  return  TRUE;
	 if  (  pStart->wSecond  >  pEnd->wSecond  )  return  FALSE;
	 if  (  pStart->wMilliseconds  <  pEnd->wMilliseconds  )  return  TRUE;
	 if  (  pStart->wMilliseconds  >  pEnd->wMilliseconds  )  return  FALSE;

	 return  TRUE;		//  一样的时刻认为是顺序的

}

/*
 int  qnmGetInputTime(  CWnd  *  pWndStartDate,  CWnd  *  pWndStartTime,  CWnd  *  pWndEndDate,  CWnd  *  pWndEndTime,  
						char  *  startBuf,  unsigned  int  startBufSize,  char  *  endBuf,  unsigned  int  endBufSize  )
{
	int					iErr			=	-1;
 	SYSTEMTIME			stStartDate,  stStartTime,  stEndDate,  stEndTime;
	SYSTEMTIME			ltStart,  ltEnd;
	SYSTEMTIME			stStart,  stEnd;
	CDateTimeCtrl	*	pStartDateCtrl	=	(  CDateTimeCtrl  *  )pWndStartDate;
	CDateTimeCtrl	*	pStartTimeCtrl	=	(  CDateTimeCtrl  *  )pWndStartTime;
	CDateTimeCtrl	*	pEndDateCtrl	=	(  CDateTimeCtrl  *  )pWndEndDate;
	CDateTimeCtrl	*	pEndTimeCtrl	=	(  CDateTimeCtrl  *  )pWndEndTime;

	if  (  !pStartDateCtrl  ||  !pStartTimeCtrl  ||  !pEndDateCtrl  ||  !pEndTimeCtrl  )  goto  errLabel;

	pStartDateCtrl->GetTime(  &stStartDate  );
	pStartTimeCtrl->GetTime(  &stStartTime  );
	pEndDateCtrl->GetTime(  &stEndDate  );
	pEndTimeCtrl->GetTime(  &stEndTime  );

	myMakeTime(  &stStartDate,  &stStartTime,  &ltStart  );
	myMakeTime(  &stEndDate,  &stEndTime,  &ltEnd  );
	
	if  (  !bMyTimeInOrder(  &ltStart,  &ltEnd  )  )  goto  errLabel;
	
	TIME_ZONE_INFORMATION	tzi;
	if  (  TIME_ZONE_ID_INVALID  ==  GetTimeZoneInformation(  &tzi  )  )  goto  errLabel;

	if  (  !TzSpecificLocalTimeToSystemTime(  &tzi,  &ltStart,  &stStart  )  )  goto  errLabel;
	if  (  !TzSpecificLocalTimeToSystemTime(  &tzi,  &ltEnd,  &stEnd  )  )  goto  errLabel;

	if  (  startBuf  )  _snprintf(  startBuf,  startBufSize,  CONST_qyTimeFormat,  stStart.wYear,  stStart.wMonth,  stStart.wDay,  stStart.wHour,  stStart.wMinute,  stStart.wSecond  );
	if  (  endBuf  )  _snprintf(  endBuf,  endBufSize,  CONST_qyTimeFormat,  stEnd.wYear,  stEnd.wMonth,  stEnd.wDay,  stEnd.wHour,  stEnd.wMinute,  stEnd.wSecond  );

	iErr  =  0;

errLabel:

	return  iErr;

}
*/

 int  qnmGetInputTime(  CWnd  *  pWndStartDate,  CWnd  *  pWndStartTime,  CWnd  *  pWndEndDate,  CWnd  *  pWndEndTime,  
						char  *  startBuf,  unsigned  int  startBufSize,  char  *  endBuf,  unsigned  int  endBufSize  )
{
	int					iErr			=	-1;
 	CTime				ltStartDate,  ltStartTime,  ltEndDate,  ltEndTime;
	CTime				ltStart,  ltEnd;
	CTime				stStart,  stEnd;
	CDateTimeCtrl	*	pStartDateCtrl	=	(  CDateTimeCtrl  *  )pWndStartDate;
	CDateTimeCtrl	*	pStartTimeCtrl	=	(  CDateTimeCtrl  *  )pWndStartTime;
	CDateTimeCtrl	*	pEndDateCtrl	=	(  CDateTimeCtrl  *  )pWndEndDate;
	CDateTimeCtrl	*	pEndTimeCtrl	=	(  CDateTimeCtrl  *  )pWndEndTime;
	time_t				t;

	if  (  !pStartDateCtrl  ||  !pStartTimeCtrl  ||  !pEndDateCtrl  ||  !pEndTimeCtrl  )  goto  errLabel;

	pStartDateCtrl->GetTime(  ltStartDate  );  
	pStartTimeCtrl->GetTime(  ltStartTime  );
	pEndDateCtrl->GetTime(  ltEndDate  );
	pEndTimeCtrl->GetTime(  ltEndTime  );

	traceLogA(  "stStartDate is %S",  ltStartDate.Format(  _T(  "%Y:%m:%d, %H:%M:%S"  )  )  );
	traceLogA(  "stStartTime is %S",  ltStartTime.Format(  _T(  "%Y:%m:%d, %H:%M:%S"  )  )  );

	//  myMakeTime(  &stStartDate,  &stStartTime,  &ltStart  );
	//  myMakeTime(  &stEndDate,  &stEndTime,  &ltEnd  );

	ltStart  =  CTime(  ltStartDate.GetYear(  ),  ltStartDate.GetMonth(  ),  ltStartDate.GetDay(  ),  0,  0,  0  )  +  CTimeSpan(  0,  ltStartTime.GetHour(  ),  ltStartTime.GetMinute(  ),  ltStartTime.GetSecond(  )  );
	ltEnd  =  CTime(  ltEndDate.GetYear(  ),  ltEndDate.GetMonth(  ),  ltEndDate.GetDay(  ),  0,  0,  0  )  +  CTimeSpan(  0,  ltEndTime.GetHour(  ),  ltEndTime.GetMinute(  ),  ltEndTime.GetSecond(  )  );

	traceLogA(  "ltStart is %S",  ltStart.Format(  _T(  "%Y:%m:%d, %H:%M:%S"  )  )  );
	traceLogA(  "ltEnd is %S",  ltEnd.Format(  _T(  "%Y:%m:%d, %H:%M:%S"  )  )  );

	
	//  if  (  !bMyTimeInOrder(  &ltStart,  &ltEnd  )  )  goto  errLabel;
	if  (  ltEnd  <  ltStart  )  goto  errLabel;
	
	TIME_ZONE_INFORMATION	tzi;
	if  (  TIME_ZONE_ID_INVALID  ==  GetTimeZoneInformation(  &tzi  )  )  goto  errLabel;

	//  if  (  !TzSpecificLocalTimeToSystemTime(  &tzi,  &ltStart,  &stStart  )  )  goto  errLabel;
	//  if  (  !TzSpecificLocalTimeToSystemTime(  &tzi,  &ltEnd,  &stEnd  )  )  goto  errLabel;

	/*
	if  (  startBuf  )  _snprintf(  startBuf,  startBufSize,  CONST_qyTimeFormat,  stStart.wYear,  stStart.wMonth,  stStart.wDay,  stStart.wHour,  stStart.wMinute,  stStart.wSecond  );
	if  (  endBuf  )  _snprintf(  endBuf,  endBufSize,  CONST_qyTimeFormat,  stEnd.wYear,  stEnd.wMonth,  stEnd.wDay,  stEnd.wHour,  stEnd.wMinute,  stEnd.wSecond  );
	*/
	t  =  (  time_t  )ltStart.GetTime(  );
	if  (  startBuf  )  getTimeStr(  t,  startBuf,  startBufSize  );
	
	t  =  (  time_t  )ltEnd.GetTime(  );
	if  (  endBuf  )  getTimeStr(  t,  endBuf,  endBufSize  );


	iErr  =  0;

errLabel:

	return  iErr;

}



 LRESULT CPpQnmStatGeneral::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	int					iState;

	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  NULL,  0,  NULL,  0  )  )  {
		qyShowHint(  _T(  "截止时间应晚于起始时间"  )  );  goto  errLabel;
	}
	
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_chkPage:
				  
				  if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_jsjbd  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  
//					  &&  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_yhzc  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1		//  by 2003/8/28
						&&  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_bhxw  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  
							&&  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_zysj  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  )  
				  {
					  qyShowHint( getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askForContentOfStat  )  );
					  goto  errLabel;
				  }	

				  pComm->u.chkPage.IDD  =  CPpQnmStatGeneral::IDD;				  
				  pComm->u.chkPage.bOk  =  TRUE;
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;
}


 TCHAR  *  getIifStr_i(  char  *  dbTypeName,  TCHAR  *  colName,  int  iWhenVal,  int  iTrueVal,  int  iFalseVal,  TCHAR  *  output,  unsigned  int  size  )
{
	 if  (  !strcmpi(  dbTypeName,  CONST_dbTypeName_access  )  )  {
		 _sntprintf(  output,  size,  _T(  " IIF(%s=%d,%d,%d) "  ),  colName,  iWhenVal,  iTrueVal,  iFalseVal  );
		}
	 else  if  (  !strcmpi(  dbTypeName,  CONST_dbTypeName_sqlServer  )  )  {
			   _sntprintf(  output,  size,  _T(  " case  when %s=%d then %d else %d end "  ),  colName,  iWhenVal,  iTrueVal,  iFalseVal  );
		}
	 else  output[0]  =  0;
	 return  output;
}

 TCHAR  *  getIifStr_s(  char  *  dbTypeName,  TCHAR  *  cond,  TCHAR  *  trueVal,  TCHAR  *  falseVal,  TCHAR  *  output,  unsigned  int  size  )
{
	 if  (  !strcmpi(  dbTypeName,  CONST_dbTypeName_access  )  )  {
		 _sntprintf(  output,  size,  _T(  " IIF(%s,%s,%s) "  ),  cond,  trueVal,  falseVal  );
		}
	 else  if  (  !strcmpi(  dbTypeName,  CONST_dbTypeName_sqlServer  )  )  {
			   _sntprintf(  output,  size,  _T(  " case  when %s then %s else %s end "  ),  cond,  trueVal,  falseVal  );
		}
	 else  output[0]  =  0;
	 return  output;
}


 void CPpQnmStatGeneral::OnOK() 
{
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	char				buf[1024];
	TCHAR				buf1[CONST_qyMaxSqlClauseLen  +  1];
	QY_IDCITEM		*	pTable0			=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatGeneralTable0  );
	QY_IDCITEM		*	pItem			=	NULL;
	char				itemBuf[256];
	int					iCurSel			=	-1;
	int					i;
	int					iRet;
	int					nCols			=	0;
	int					iState;
	BOOL				bYhzcStated	 =	FALSE,  bJsjbdStated  =  FALSE,  bBhxwStated  =  FALSE,  bZysjStated  =  FALSE;
	int					iEventType;
	TCHAR				iifBuf[128];
	CString				str;
	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return;

	if  (  (  (  CPropertySheet  *  )GetParent(  )  )->GetActivePage(  )  !=  this  )  return;
		
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
			 if  (  !m_var.groupPart[0]  )  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  m_var.groupPart[0]  ),  _T(  "%s"  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
			 else  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  m_var.groupPart[0]  ),  _T(  "%s,%s"  ),  CString(  m_var.groupPart  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
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
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  m_var.wherePart[0]  ),  _T(  "%s and ")  ,  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  / sizeof(  m_var.wherePart[0]  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
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
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  m_var.wherePart[0]  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  m_var.wherePart[0]  ),  _T(  "%s %s or %s is null"  ),  CString(  m_var.wherePart  ),  CString(  buf1  ),  CString(  pItem->sqlColName  )  );
				 continue;
			 }
			 //  以下是普通的combo处理
			 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
			 trim(  buf  );
			 if  (  buf[0]  )  {
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  m_var.wherePart[0]  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  m_var.wherePart[0]  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
			 }
			 continue;			
		 }
	 
		 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
		 trim(  buf  );
		 if  (  buf[0]  )  {
			 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  m_var.wherePart[0]  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
			 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
		 }
	}

	char	tStartBuf[256],  tEndBuf[256];

	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  tStartBuf,  sizeof(  tStartBuf  ),  tEndBuf,  sizeof(  tEndBuf  )  )  )  {
		qyShowHint(  _T(  "截止时间应晚于起始时间"  )  );  goto  errLabel;
	}

	if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
	_sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s qyPcEventTab.cntEventTime>'%s' and qyPcEventTab.cntEventTime<'%s'"  ),  CString(  m_var.wherePart  ),  CString(  tStartBuf  ),  CString(  tEndBuf  )  );


	//
	char										dbTypeName[32  +  1];	//  2006/12/18
	myTChar2Str(  qyGetDesByType1(  CONST_dbTypeTable,  m_var.pObjDb->cfg.iDbType  ),  dbTypeName,  mycountof(  dbTypeName  )  );

	
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_yhzc  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bYhzcStated  =  TRUE;
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_jsjbd  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bJsjbdStated  =  TRUE;
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_bhxw  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bBhxwStated  =  TRUE;
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_zysj  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bZysjStated  =  TRUE;

	/*  //  用户注册事件不再统计	2003/08/25
	if  (  bYhzcStated  )  {
		iEventType  =  CONST_qyEventType_nm_newReg;
		_snprintf(  buf1,  sizeof(  buf1  ),  "sum(%s)",  getIifStr_i(  pQyMc->cfg.dbTypeName,  "qyPcEventTab.eventType",  iEventType,  1, 0,  iifBuf,  sizeof(  iifBuf  )  )  );
		qnmFillColInfo(  nCols,  buf1,  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  qyGetDesByType1(  CONST_qnmEventTypeTable0,  iEventType  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;		
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null",  buf1  );
		iEventType  =  CONST_qyEventType_nm_reReg;
		_snprintf(  buf1,  sizeof(  buf1  ),  "sum(%s)",  getIifStr_i(  pQyMc->cfg.dbTypeName,  "qyPcEventTab.eventType",  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  )  );
		qnmFillColInfo(  nCols,  buf1,	SQL_INTEGER,	CONST_qyColumnDisplayType_long,  qyGetDesByType1(  CONST_qnmEventTypeTable0,  iEventType  ),	80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CSting(  buf1  )  );
	}
	*/
	if  (  bJsjbdStated  )  {
		iEventType  =  CONST_qyEventType_nm_newPc;
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_i(  dbTypeName,  _T(  "qyPcEventTab.eventType"  ),  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  iEventType  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;		
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
		iEventType  =  CONST_qyEventType_nm_macsModified;
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_i(  dbTypeName,  _T(  "qyPcEventTab.eventType"  ),  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),	SQL_INTEGER,	CONST_qyColumnDisplayType_long,  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  iEventType  ),	80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
	}
	if  (  bBhxwStated  )  {
		iEventType  =  CONST_qyEventType_nm_rasStart;
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_i(  dbTypeName,  _T(  "qyPcEventTab.eventType"  ),  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),  SQL_INTEGER,  CONST_qyColumnDisplayType_long,  _T(  "拨号允许"  ),  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;		
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
		iEventType  =  CONST_qyEventType_nm_rasProhibited;
		_sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "sum(%s)"  ),  getIifStr_i(  dbTypeName,  _T(  "qyPcEventTab.eventType"  ),  iEventType,  1,  0,  iifBuf,  sizeof(  iifBuf  )  /  sizeof(  TCHAR  )  )  );
		qnmFillColInfo(  nCols,  CString(  buf1  ),	SQL_INTEGER,	CONST_qyColumnDisplayType_long,  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  iEventType  ),	80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;			
		if  (  !m_var.havingPart[0]  )  _sntprintf(  m_var.havingPart,  sizeof(  m_var.havingPart  )  /  sizeof(  TCHAR  ),  _T(  "%s is not null"  ),  CString(  buf1  )  );
	}
	if  (  bZysjStated  )  {
		QY_IDCITEM		*	pItem;
		QY_DMITEM		*	pEventTable;

		pItem  =  qyGetIdcItemByIdc(  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpEventListSearchTable0  ),  IDC_COMBO_eventType  );
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


