// DlgCfgWarn.cpp : implementation file
//

#include "stdafx.h"
#include "qyMcMainCommon.h"
#include "qymc.h"
#include "DlgCfgWarn.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgWarn dialog


CDlgCfgWarn::CDlgCfgWarn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgWarn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgWarn)
	m_nMaxWarnElapse = 0;
	m_bWarnOn = FALSE;
	m_bWarnUntilUsrStopIt = FALSE;
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgWarn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgWarn)
	DDX_Text(pDX, IDC_MAXWARNELAPSE, m_nMaxWarnElapse);
	DDX_Check(pDX, IDC_WARNON, m_bWarnOn);
	DDX_Check(pDX, IDC_WARNUNTILUSRSTOPIT, m_bWarnUntilUsrStopIt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgWarn, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgWarn)
	ON_BN_CLICKED(IDC_WARNON, OnWarnon)
	ON_BN_CLICKED(IDC_WARNUNTILUSRSTOPIT, OnWarnuntilusrstopit)
	ON_BN_CLICKED(IDC_CHECK_popupToWarn, OnCHECKpopupToWarn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgCfgWarn::OnBnClickedOk)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgCfgWarn message handlers

void CDlgCfgWarn::OnWarnon() 
{
	 UpdateData(  TRUE  );
		
	if  (  !m_bWarnOn  )  {
		GetDlgItem(  IDC_WARNUNTILUSRSTOPIT  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  FALSE  );
		}
	else  {
		  GetDlgItem(  IDC_WARNUNTILUSRSTOPIT  )->EnableWindow(  TRUE  );
		  m_bWarnUntilUsrStopIt  =  GetDlgItemInt(  IDC_WARNUNTILUSRSTOPIT,  NULL,  FALSE  );
		  GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  !m_bWarnUntilUsrStopIt  );
		/*
		if  (  m_bWarnUntilUsrStopIt  )  {
			GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  FALSE  );
			return;
		}
	
		GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  TRUE  );
		*/


	}
	
}

void CDlgCfgWarn::OnWarnuntilusrstopit() 
{
	 if( !UpdateData(  TRUE  )  )  return;
	 
	 if  (  !m_bWarnUntilUsrStopIt  )  {
		 GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  TRUE  );
		}
	 else  {
		 GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  FALSE  );
		
	 }	
	
}

void CDlgCfgWarn::OnOK() 
{
	if  (  !UpdateData(  TRUE  )  )  return;
	
	char  buf[128];

	qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_warnOn  ),  m_bWarnOn  ?  _T(  "1"  )  :  _T(  "0"  )  );
	qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_warnUntilUsrStopIt  ),  m_bWarnUntilUsrStopIt  ?  _T(  "1"  )  :  _T(  "0"  )  );
	sprintf(  buf,  "%d",  m_nMaxWarnElapse  );
	qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_maxWarnElapseInSecond  ),  CString(  buf  )  );

	if  (  strcmpi(  m_var.new_popupToWarnStartTime,  m_var.popupToWarnStartTime  )  )  {
		if  (  !m_var.new_popupToWarnStartTime[0]  )  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_popupToWarnStartTime  )  );
		else  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_popupToWarnStartTime  ),  CString(  m_var.new_popupToWarnStartTime  )  );
	}

	CDialog::OnOK();
}



BOOL CDlgCfgWarn::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	
	TCHAR	tmpBuf[1024];
	
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_warnOn  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )
		&&  tmpBuf[0]  ==  '1'  )
	{
		m_bWarnOn  =  TRUE;
		if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_warnUntilUsrStopIt  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  
			&&  tmpBuf[0]  == '1'  )  
		{
			m_bWarnUntilUsrStopIt  =  TRUE;
			}
		else  {
			m_bWarnUntilUsrStopIt  =  FALSE;
		}
		
		}
	else   
		m_bWarnOn  =  FALSE;			
	
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_maxWarnElapseInSecond  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )
		&&  _ttol(  tmpBuf  )  >  5  )
	{
		m_nMaxWarnElapse   =  _ttol(  tmpBuf  );
		}
	else
		m_nMaxWarnElapse  =  5;

	if  (  !m_bWarnOn  )  {
		GetDlgItem(  IDC_WARNUNTILUSRSTOPIT  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  FALSE  );
		}
	else  if  (  m_bWarnUntilUsrStopIt  )  {
		GetDlgItem(  IDC_MAXWARNELAPSE  )->EnableWindow(  FALSE  );
	}

	if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_popupToWarnStartTime  ),  (  char  *  )tmpBuf,  mycountof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
	myTChar2Utf8(  tmpBuf,  m_var.popupToWarnStartTime,  sizeof(  m_var.popupToWarnStartTime  )  );
	trim(  m_var.popupToWarnStartTime  );
	if  (  m_var.popupToWarnStartTime[0]  )  {
		char	displayBuf[256]	=	"";
		if  (  !qyDisplayTime(  m_var.popupToWarnStartTime,  displayBuf,  sizeof(  displayBuf  )  )  )  safeStrnCpy(  "Error!",  displayBuf,  sizeof(  displayBuf  )  );
		GetDlgItem(  IDC_CHECK_popupToWarn  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
		SetDlgItemText(  IDC_STATIC_popupToWarnStartTimeVal,  CString(  displayBuf  )  );
	}
	//
	safeStrnCpy(  m_var.popupToWarnStartTime,  m_var.new_popupToWarnStartTime,  sizeof(  m_var.new_popupToWarnStartTime  )  );

	UpdateData(  FALSE  );
	
#if  0		//  2010/05/23
	GetDlgItem(  IDC_CHECK_popupToWarn  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_popupToWarnStartTime  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_popupToWarnStartTimeVal  )->ShowWindow(  SW_HIDE  );
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCfgWarn::OnCHECKpopupToWarn() 
{
	// TODO: Add your control notification handler code here
	unsigned  char	ucbChecked							=	FALSE;
	char			displayBuf[256  +  1]				=	"";

	ucbChecked  =  GetDlgItem(  IDC_CHECK_popupToWarn  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	if  (  ucbChecked  )  {
		getCurTime(  m_var.new_popupToWarnStartTime  );
		SetDlgItemText(  IDC_STATIC_popupToWarnStartTimeVal,  CString(  qyDisplayTime(  m_var.new_popupToWarnStartTime,  displayBuf,  sizeof(  displayBuf  )  )  )  );
		}
	else  {
		  m_var.new_popupToWarnStartTime[0]  =  0;
		  SetDlgItemText(  IDC_STATIC_popupToWarnStartTimeVal,  _T(  ""  )  );
	}			
	
}

void CDlgCfgWarn::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
