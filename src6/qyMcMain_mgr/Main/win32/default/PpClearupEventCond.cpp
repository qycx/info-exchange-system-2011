// PpClearupEventCond.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"qyPs.h"
#include	"PpClearupEventCond.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpClearupEventCond property page

IMPLEMENT_DYNCREATE(CPpClearupEventCond, CPropertyPage)

CPpClearupEventCond::CPpClearupEventCond() : CPropertyPage(CPpClearupEventCond::IDD)
{
	//{{AFX_DATA_INIT(CPpClearupEventCond)
	//}}AFX_DATA_INIT
}

CPpClearupEventCond::~CPpClearupEventCond()
{
}

void CPpClearupEventCond::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpClearupEventCond)
	DDX_Control(pDX, IDC_STARTTIME, m_startTimeCtrl);
	DDX_Control(pDX, IDC_STARTDATE, m_startDateCtrl);
	DDX_Control(pDX, IDC_ENDTIME, m_endTimeCtrl);
	DDX_Control(pDX, IDC_ENDDATE, m_endDateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpClearupEventCond, CPropertyPage)
	//{{AFX_MSG_MAP(CPpClearupEventCond)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpClearupEventCond message handlers

BOOL CPpClearupEventCond::OnSetActive() 
{
	CQyPs	*	pPs  =  (  CQyPs  *  )GetParent(  );

	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  |  PSWIZB_BACK  );

	CTime	t  =  CTime::GetCurrentTime( );
	CTimeSpan	ts(  0,  0,  0,  0  );
	CTimeSpan	ts1(  0,  0,  0,  0  ); 

	CTime	tStart(  t  -  ts  ),  tEnd(  t  +  ts1  );

	//set this style
	this->m_startDateCtrl.ModifyStyle(0,DTS_SHORTDATEFORMAT,SWP_NOSIZE);
	this->m_startTimeCtrl.ModifyStyle(0,DTS_TIMEFORMAT,SWP_NOSIZE);
	this->m_endDateCtrl.ModifyStyle(0,DTS_SHORTDATEFORMAT,SWP_NOSIZE);
	this->m_endTimeCtrl.ModifyStyle(0,DTS_TIMEFORMAT,SWP_NOSIZE);
	

	this->m_startDateCtrl.SetTime(  &tStart  );
	this->m_startTimeCtrl.SetTime(  &tStart  );
	this->m_endDateCtrl.SetTime(  &tEnd  );
	this->m_endTimeCtrl.SetTime(  &tEnd  );

	if  (  !UpdateData(  FALSE  )  )  traceLogA(  "UpdateData(  FALSE  ) failed"  );
	
	return CPropertyPage::OnSetActive();
}

BOOL CPpClearupEventCond::OnWizardFinish() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	CQyPs	*	pPs		=	(  CQyPs  *  )GetParent(  );

	UpdateData(  TRUE  );

	char	tStartBuf[256],  tEndBuf[256];
	
	if  (  qnmGetInputTime(  &this->m_startDateCtrl,  &this->m_startTimeCtrl,  &this->m_endDateCtrl,  &this->m_endTimeCtrl,  tStartBuf,  sizeof(  tStartBuf  ),  tEndBuf,  sizeof(  tEndBuf  )  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_timeErr  )  );  return  FALSE;
	}
	
	if  (  AfxMessageBox(  getResStr(  0, &pQyMc->cusRes,  CONST_resId_clearVerify  ),  MB_YESNO  )  !=  IDYES  )  return  FALSE;
		
	_snprintf(  pPs->m_var.u.clearupInfo.fromTimeBuf,  sizeof(  pPs->m_var.u.clearupInfo.fromTimeBuf  ),  "%s",  tStartBuf  );
	_snprintf(  pPs->m_var.u.clearupInfo.toTimeBuf,  sizeof(  pPs->m_var.u.clearupInfo.toTimeBuf  ),  "%s",  tEndBuf  );
	
	return  CPropertyPage::OnWizardFinish();
}


