// DlgQnmSnmpObjProperties.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmSnmpObjProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSnmpObjProperties dialog


CDlgQnmSnmpObjProperties::CDlgQnmSnmpObjProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmSnmpObjProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmSnmpObjProperties)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.iPortIfIndex  =  -1;
}


void CDlgQnmSnmpObjProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmSnmpObjProperties)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmSnmpObjProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmSnmpObjProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSnmpObjProperties message handlers

 //  iPortIfIndex为-1时，查看所有信息 
 BOOL  CDlgQnmSnmpObjProperties::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac,  int  iPortIfIndex  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMacValid(  mac  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	safeStrnCpy(  mac,  m_var.mac,  sizeof(  m_var.mac  )  );
	m_var.iPortIfIndex  =  iPortIfIndex;

	return  TRUE;
}



BOOL CDlgQnmSnmpObjProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	QY_SNMPOBJ_HEAD			snmpObjHead;
	QY_SWITCHPORT_RCD		portInfo;
	char					buf[256];

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return  FALSE;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
	memset(  &portInfo,  0,  sizeof(  portInfo  )  );
	if  (  !bGetSnmpObjHeadInfoBySth(  m_var.pObjDb->pDb,  m_var.mac,  NULL,  &snmpObjHead  )  )  memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
	if  (  !bGetPortInfoBySth(  m_var.pObjDb->pDb,  snmpObjHead.mac,  m_var.iPortIfIndex,  0,  NULL,  &portInfo,  NULL  )  )  memset(  &portInfo,  0,  sizeof(  portInfo  )  );

	SetDlgItemText(  IDC_STATIC_productName,  CString(  snmpObjHead.productName  )  );
	SetDlgItemText(  IDC_STATIC_ip,  CString(  snmpObjHead.ip  )  );
	SetDlgItemText(  IDC_STATIC_cusName,  CString(  snmpObjHead.cusName  )  );
	SetDlgItemText(  IDC_STATIC_place,  CString(  snmpObjHead.place  )  );
	SetDlgItemText(  IDC_STATIC_numPorts,  CString(  _ltoa(  snmpObjHead.uiIfNumber,  buf,  10  )  )  );
	SetDlgItemText(  IDC_STATIC_sysDescr,  CString(  snmpObjHead.sysDescr  )  );	
	if  (  !snmpObjHead.ucbCpsGlobalPortSecurityEnable  )  {
		SetDlgItemText(  IDC_STATIC_iCpsGlobalMaxSecureAddress,  CString(  ""  )  );
		SetDlgItemText(  IDC_STATIC_iCpsGlobalTotalSecureAddress,  CString(  ""  )  );
		}
	else  {
		  SetDlgItemInt(  IDC_STATIC_iCpsGlobalMaxSecureAddress,  snmpObjHead.iCpsGlobalMaxSecureAddress  );
		  SetDlgItemInt(  IDC_STATIC_iCpsGlobalTotalSecureAddress,  snmpObjHead.iCpsGlobalTotalSecureAddress  );
	}

	if  (  !portInfo.portIfDescr[0]  )  {
		GetDlgItem(  IDC_STATIC_prePortIfIndex  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_portIfIndex  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_prePortIfDescr  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_portIfDescr  )->ShowWindow(  SW_HIDE  );
		}
	else  {
		  SetDlgItemText(  IDC_STATIC_portIfIndex,  CString(  _ltoa(  portInfo.iPortIfIndex,  buf,  10  )  )  );
		  SetDlgItemText(  IDC_STATIC_portIfDescr,  CString(  portInfo.portIfDescr  )  );
	}
	
//  errLabel:
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
