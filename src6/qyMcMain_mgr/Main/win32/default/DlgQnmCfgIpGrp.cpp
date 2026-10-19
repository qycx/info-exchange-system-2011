// DlgQnmCfgIpGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"QyRestrictEdit.h"
#include	"qyMc.h"
#include	"DlgQnmCfgIpGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgIpGrp dialog

//
//
//
//
//
//


CDlgQnmCfgIpGrp::CDlgQnmCfgIpGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgIpGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgIpGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgQnmCfgIpGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgIpGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgIpGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgIpGrp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgIpGrp message handlers

BOOL  CDlgQnmCfgIpGrp::bSetDlgInfo(  int  type, CWnd  *  pSrcWnd  )
{
	m_var.type			=  type;
	m_var.pSrcWnd		=  pSrcWnd;
	return  TRUE;
}


void CDlgQnmCfgIpGrp::OnOK() 
{
	 QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	 DWORD					hStartIp  =  0,  hEndIp  =  0,  dwIp  =  0;
	 struct  in_addr		tmpInAddr;
	 char					startIpBuf[256]  =  "",  endIpBuf[256]  =  "";
	 char					startIp12[128],  endIp12[128];
	 char					sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 char					officeName[64  +  1],  subOfficeName[64  +  1];
	 CString				str;

	 if  (  4  !=  ::SendMessage(  GetDlgItem(  IDC_startIp  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&hStartIp  )  )  {
		 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qnmHint_startIp0  )  );
		 GetDlgItem(  IDC_startIp  )->SetFocus(  );
		 return;
	 }
	 tmpInAddr.s_addr  =  qyhtonl(  hStartIp  );
	 sprintf(  startIpBuf,  inet_ntoa(  tmpInAddr  )  );
	
	 if  (  4  !=  ::SendMessage(  GetDlgItem(  IDC_endIp  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&hEndIp  )  )  {
		 hEndIp  =  hStartIp;
	 }
	 tmpInAddr.s_addr  =  qyhtonl(  hEndIp  );
	 sprintf(  endIpBuf,  inet_ntoa(  tmpInAddr  )  );
	 
	 if  (  hStartIp  >  hEndIp  )  {
		 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qnmHint_endIpLtStartIp  )  );
		 return;
	 }

	 qyStdToIp12(  startIpBuf,  startIp12  );
	 qyStdToIp12(  endIpBuf,  endIp12  );
	 GetDlgItemText(  IDC_officeName,  str  );  myTChar2Str(  str,  officeName,  sizeof(  officeName  )  );
	 GetDlgItemText(  IDC_subOfficeName,  str  );  myTChar2Str(  str,  subOfficeName,  sizeof(  subOfficeName  )  );

	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "insert into qnmIpScanTab(startIp,endIp,officeName,subOfficeName,flg) values('%s','%s','%s','%s','')",  startIp12,  endIp12, officeName,  subOfficeName  );

	 if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
		 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfRetype  )  );
		 return;
	 }	 

	 m_var.bChanged  =  TRUE;
	
	 CDialog::OnOK();
}



BOOL CDlgQnmCfgIpGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int		idc;
	int		cnt		=	0;
	int		maxBytes  =  64;
	QY_MC		*	pQyMc	=  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	idc  =  IDC_officeName;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitAll,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );

	cnt  ++  ;
	idc  =  IDC_subOfficeName;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitAll,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
