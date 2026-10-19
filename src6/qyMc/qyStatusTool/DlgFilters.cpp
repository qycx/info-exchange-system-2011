// DlgFilters.cpp : implementation file
//

#include	"stdafx.h"
#include	<vfw.h>
#include	"qmCommon.h"
#include	"qystatustool.h"
#include	"qyPs.h"
#include	"PpQwmCommStatus.h"
#include	"dlgFilters.h"
#include	"qyCusResPublic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFilters dialog


CDlgFilters::CDlgFilters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFilters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFilters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgFilters::bSetDlgInfo(  int  type,  HWND  hParent,  unsigned  int  ulIp0,  unsigned  long  ulIp1,  LPCTSTR  filter0,  LPCTSTR  filter1,  LPCTSTR  contentFilter2,  LPCTSTR  contentFilter3  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 //
	 m_var.ulClientIp0  =  ulIp0;
	 m_var.ulClientIp1  =  ulIp1;
	 if  (  filter0  )  lstrcpyn(  m_var.filter0Buf,  filter0,  mycountof(  m_var.filter0Buf  )  );
	 if  (  filter1  )  lstrcpyn(  m_var.filter1Buf,  filter1,  mycountof(  m_var.filter1Buf  )  );
	 if  (  contentFilter2  )  lstrcpyn(  m_var.contentFilter2Buf,  contentFilter2,  mycountof(  m_var.contentFilter2Buf  )  );
	 if  (  contentFilter3  )  lstrcpyn(  m_var.contentFilter3Buf,  contentFilter3,  mycountof(  m_var.contentFilter3Buf  )  );

	 
	 return  TRUE;
}


void CDlgFilters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFilters)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFilters, CDialog)
	//{{AFX_MSG_MAP(CDlgFilters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFilters message handlers

void CDlgFilters::OnOK() 
{
	// TODO: Add extra validation here
	TCHAR	tBuf[255  +  1]		=	_T(  ""  );
	char	buf[255  +  1]		=	"";

	GetDlgItemText(  IDC_EDIT_clientIp0,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  m_var.ulClientIp0  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_clientIp1,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
	if  (  buf[0]  &&  bIpValid(  buf  )  )  m_var.ulClientIp1  =  inet_addr(  buf  );
	//
	GetDlgItemText(  IDC_EDIT_filter0,  this->m_var.filter0Buf,  mycountof(  m_var.filter0Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter1,  this->m_var.filter1Buf,  mycountof(  m_var.filter1Buf  )  );

	GetDlgItemText(  IDC_EDIT_filter2,  this->m_var.contentFilter2Buf,  mycountof(  m_var.contentFilter2Buf  )  );
	GetDlgItemText(  IDC_EDIT_filter3,  this->m_var.contentFilter3Buf,  mycountof(  m_var.contentFilter3Buf  )  );


	CDialog::OnOK();
}

BOOL CDlgFilters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CQyPs  *  pPs  =  (  CQyPs  *  )GetParent(  );
	QY_STATUS_STRUCT	*	pStatusStruct	=  &pPs->m_var.u.showInfo.statusStruct;
	char	ip[15  +  1]	=	"";

	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );

	ip[0]  =  0;
	if  (  m_var.ulClientIp0  &&  !ulIp2Str(  m_var.ulClientIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp0,  CString(  ip  )  );
	//
	ip[0]  =  0;
	if  (  m_var.ulClientIp1  &&  !ulIp2Str(  m_var.ulClientIp1,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
	SetDlgItemText(  IDC_EDIT_clientIp1,  CString(  ip  )  );
	//
	SetDlgItemText(  IDC_EDIT_filter0,  m_var.filter0Buf  );
	SetDlgItemText(  IDC_EDIT_filter1,  m_var.filter1Buf  );


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
