// DlgQnmPcSpListSearch.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"DlgQnmPcSpListSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcSpListSearch dialog


CDlgQnmPcSpListSearch::CDlgQnmPcSpListSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmPcSpListSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmPcSpListSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmPcSpListSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmPcSpListSearch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmPcSpListSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmPcSpListSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_osName, OnSelchangeCOMBOosName)
	ON_CBN_SELCHANGE(IDC_COMBO_spName, OnSelchangeCOMBOspName)
	ON_CBN_SELCHANGE(IDC_COMBO_cusName, OnSelchangeCOMBOcusName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcSpListSearch message handlers

BOOL CDlgQnmPcSpListSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int					idc;
	char				sqlBuf[1024];
	QY_MC			*	pQyMc	=  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	m_var.pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	idc  =  IDC_COMBO_osName;
	if  (  !bQnmFillCol0(  m_var.pObjDb,  _T(  "select distinct osName from qyPcTab order by osName"  ),  GetDlgItem(  idc  )->m_hWnd,  TRUE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  0  );

	idc  =  IDC_COMBO_spName;
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select distinct spName from qyPcSpTab where spName<>'%s' order by spName",  CONST_qnmNullPcSp  );
	if  (  !bQnmFillCol0(  m_var.pObjDb,  CString(  sqlBuf  ),  GetDlgItem(  idc  )->m_hWnd,  TRUE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  0  );

	idc  =  IDC_COMBO_cusName;
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select distinct qyCusNameTab.cusName0 from qyCusNameTab where qyCusNameTab.iType=%d order by qyCusNameTab.cusName0",  CONST_cusNameType_pcSp  );
	if  (  !bQnmFillCol0(  m_var.pObjDb,  CString(  sqlBuf  ),  GetDlgItem(  idc  )->m_hWnd,  TRUE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  0  );

	
errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgQnmPcSpListSearch::OnSelchangeCOMBOosName() 
{
	char	osName[128];
	char	sqlBuf[1024];
	int		idc;
	CString	str;

	GetDlgItemText(  IDC_COMBO_osName,  str  );  myTChar2Str(  str,  osName,  sizeof(  osName  )  );
		
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select distinct qyPcSpTab.spName from qyPcSpTab left join qyPcTab on qyPcSpTab.mac0=qyPcTab.mac0"  );
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s where qyPcSpTab.spName<>'%s'",  sqlBuf,  CONST_qnmNullPcSp  );
	if  (  osName[0]  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qyPcSpTab.osName='%s'",  sqlBuf,  osName  );
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s order by qyPcspTab.spName ",  sqlBuf  );

	idc  =  IDC_COMBO_spName;
	if  (  !bQnmFillCol0(  m_var.pObjDb,  CString(  sqlBuf  ),  GetDlgItem(  idc  )->m_hWnd,  TRUE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  0  );

	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select distinct qyCusNameTab.cusName0 from qyCusNameTab  where qyCusNameTab.iType=%d",  CONST_cusNameType_pcSp  );
	if (  osName[0]  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qyCusNameTab.objName0 in (select qyPcSptab.spName from qyPcSpTab left join qyPcTab on qyPcSpTab.mac0=qyPctab.mac0 where qyPcTab.osName='%s') ",  sqlBuf,  osName  );
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s order by qyCusNameTab.cusName0 ",  sqlBuf  );

	idc  =  IDC_COMBO_cusName;
	if  (  !bQnmFillCol0(  m_var.pObjDb,  CString(  sqlBuf  ),  GetDlgItem(  idc  )->m_hWnd,  TRUE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  0  );


errLabel:
	return;
}



void CDlgQnmPcSpListSearch::OnSelchangeCOMBOspName() 
{
	char	buf[128];
	char	sqlBuf[1024];
	int		idc;
	char	osName[32];
	CString	str;

	GetDlgItemText(  IDC_COMBO_osName,  str  );  myTChar2Str(  str,  osName,  sizeof(  osName  )  );
	GetDlgItemText(  IDC_COMBO_spName,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
		
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select distinct qyCusNameTab.cusName0 from qyCusNameTab  where qyCusNameTab.iType=%d",  CONST_cusNameType_pcSp  );
	if  (  buf[0]  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qyCusNameTab.objName0='%s'",  sqlBuf,  buf  );
	if (  osName[0]  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qyCusNameTab.objName0 in (select qyPcSptab.spName from qyPcSpTab left join qyPcTab on qyPcSpTab.mac0=qyPctab.mac0 where qyPcTab.osName='%s') ",  sqlBuf,  osName  );
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s order by qyCusNameTab.cusName0 ",  sqlBuf  );

	idc  =  IDC_COMBO_cusName;
	if  (  !bQnmFillCol0(  m_var.pObjDb,  CString(  sqlBuf  ),  GetDlgItem(  idc  )->m_hWnd,  buf[0]  ?  FALSE  :  TRUE  )  )  goto  errLabel;
	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SetCurSel(  0  );

errLabel:
	return;
	
}

void CDlgQnmPcSpListSearch::OnSelchangeCOMBOcusName() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR		sqlBuf[1024];
	CDBVariant	varVals[3];
	int			idc		=	IDC_COMBO_spName;
	CString		str;
	TCHAR		tBuf[256];

	GetDlgItemText(  IDC_COMBO_cusName,  str  );  MACRO_CStringTrim(  str  );

	if  (  !str.GetLength(  )  )  return;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyPcSpTab.spName from qyPcSpTab,qyCusNameTab where qyCusNameTab.iType=%d and qyPcSpTab.spName=qyCusNameTab.objName0 and qyCusNameTab.cusName0='%s'"  ),  CONST_cusNameType_pcSp,  str  );
	traceLogA(  "sqlBuf is %s",  sqlBuf  );
	if  (  bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  tBuf  );
	}
	
}


void CDlgQnmPcSpListSearch::OnOK() 
{
	CString	str;

	GetDlgItemText(  IDC_COMBO_osName,  str  );  myTChar2Str(  str,  m_var.osName,  sizeof(  m_var.osName  )  );
	GetDlgItemText(  IDC_COMBO_spName,  str  );  myTChar2Str(  str,  m_var.spName,  sizeof(  m_var.spName  )  );

	
	CDialog::OnOK();
}

