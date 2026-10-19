// LogQuery.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"bhbSrc1CommProc.h"
#include	"myresource.h"
#include	"LogQuery.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogQuery dialog


CLogQuery::CLogQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CLogQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogQuery)
	m_Dateb = 0;
	m_Datee = 0;
	m_Timeb = 0;
	m_Timee = 0;
	m_csUnit = _T("");
	m_csDepart = _T("");
	//}}AFX_DATA_INIT
}


void CLogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogQuery)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cLogType);
	DDX_Control(pDX, IDC_IPLOG, m_cIpAddress);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Dateb);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_Datee);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_Timeb);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_Timee);
	DDX_Text(pDX, IDC_GROUPNAME, m_csUnit);
	DDX_Text(pDX, IDC_GROUPNAME2, m_csDepart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogQuery, CDialog)
	//{{AFX_MSG_MAP(CLogQuery)
	ON_BN_CLICKED(IDC_SHOWLOG, OnShowlog)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogQuery message handlers

void CLogQuery::OnShowlog() 
{
	ONLINE_COMPUTER_TAB_RCD		m_stuComputerLogInfo;
	char						sqlClause[CONST_qyMaxSqlClauseLen  +  1]	=	"";
	char						buf[2048];

	UpdateData( TRUE );	
	
	CString csDateB = m_Dateb.Format( "%Y%m%d" );
	CString csDateE = m_Datee.Format( "%Y%m%d" );
	CString csTimeB = m_Timeb.Format( "%H%M%S" );
	CString csTimeE = m_Timee.Format( "%H%M%S" );

	if  (  csDateB  >  csDateB  )  {
		MessageBox(  _T(  "请选择合理的查询时间"  ), _T(  "提示"  ), MB_OK );
		return;
	}
	if  (  csDateB  ==  csDateE  )  {
		if  (  csTimeB  >=  csTimeE  )  {
			MessageBox(  _T(  "请选择合理的查询时间"  ),  _T(  "提示"  ), MB_OK );
			return;
		}
	}

	memset(  &m_stuComputerLogInfo,  0,  sizeof(  m_stuComputerLogInfo  )  );
	myTChar2Str(  csDateB.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );  safeStrnCpy(  buf,  m_stuComputerLogInfo.firstRecvdTime,  sizeof(  m_stuComputerLogInfo.firstRecvdTime  )  );
	myTChar2Str(  csTimeB.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );  safeStrnCpy(  buf,  m_stuComputerLogInfo.firstRecvdTime  +  csDateB.GetLength(),  sizeof(  m_stuComputerLogInfo.firstRecvdTime  )  -  csDateB.GetLength(  )  );
	myTChar2Str(  csDateE.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );  safeStrnCpy(  buf,  m_stuComputerLogInfo.lastRecvdTime,  sizeof(  m_stuComputerLogInfo.lastRecvdTime  )  );
	myTChar2Str(  csTimeE.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );  safeStrnCpy(  buf,  m_stuComputerLogInfo.lastRecvdTime  +  csDateE.GetLength(),  sizeof(  m_stuComputerLogInfo.lastRecvdTime  )  -  csDateE.GetLength(  )  );

	_snprintf(  sqlClause,  sizeof(  sqlClause  ),  "firstRecvdTime>='%s' and firstRecvdTime<='%s'",  m_stuComputerLogInfo.firstRecvdTime,  m_stuComputerLogInfo.lastRecvdTime  );
	
	DWORD				dwIpAddress;
	m_cIpAddress.GetAddress(  dwIpAddress  );
	dwIpAddress = ::htonl(dwIpAddress);
	if  (  bulIpValid(  dwIpAddress  )  )  _snprintf(  sqlClause,  sizeof(  sqlClause  ),  "%s and ip='%s'",  sqlClause,  inet_ntoa(  *(  in_addr  *  )&dwIpAddress  )  );

	_snprintf(  m_stuComputerLogInfo.officeName,  sizeof(  m_stuComputerLogInfo.officeName  ),  "%s",  m_csUnit  );
	trim(  m_stuComputerLogInfo.officeName  );
	if  (  m_stuComputerLogInfo.officeName[0]  )  _snprintf(  sqlClause,  sizeof(  sqlClause  ),  "%s and officeName='%s'",  sqlClause,  m_stuComputerLogInfo.officeName  );
	_snprintf(  m_stuComputerLogInfo.subOfficeName,  sizeof(  m_stuComputerLogInfo.subOfficeName  ),  "%s",  m_csDepart  );
	trim(  m_stuComputerLogInfo.subOfficeName  );
	if  (  m_stuComputerLogInfo.subOfficeName[0]  )  _snprintf(  sqlClause,  sizeof(  sqlClause  ),  "%s and subOfficeName='%s'",  sqlClause,  m_stuComputerLogInfo.subOfficeName  );

	TCHAR	tBuf[128];
	m_cLogType.GetWindowText(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	if  (  !strcmp(  buf,  "正在上网"  )  )  bBhbViewLogFunc(  getProcedObjDb(  0,  g_pQyMc->iDsnIndex_mainSys  ),  _T(  "查询"  ),  CString(  sqlClause  )  );
	else  bBhbViewOfflineLogFunc(  getProcedObjDb(  0,  g_pQyMc->iDsnIndex_mainSys  ),  _T(  "查询"  ),  CString(  sqlClause  )  );

	CDialog::OnOK();
	
}

BOOL CLogQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nHour;

	CTime t = CTime::GetCurrentTime( );
	if(t.GetDay() != 1)
		m_Dateb = CTime( t.GetYear(), t.GetMonth(), t.GetDay()-1,
						 t.GetHour(), t.GetMinute(), t.GetSecond(), -1 );
	else
		m_Dateb = CTime( t.GetYear(), t.GetMonth(), t.GetDay(),
						 t.GetHour(), t.GetMinute(), t.GetSecond(), -1 ); 

	m_Datee = CTime::GetCurrentTime( );

	m_Timeb = CTime::GetCurrentTime( );

	nHour = t.GetHour( );
	if( nHour < 23 )
		nHour ++;

	m_Timee = CTime( t.GetYear(), t.GetMonth(), t.GetDay(),
				 nHour , t.GetMinute(), t.GetSecond(), -1 );
	
	m_cLogType.SelectString(  -1,  _T(  "正在上网"  )  );

	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogQuery::OnExit() 
{
	CDialog::OnOK();
}
