// DlgQnmSnmpObjPortProperties.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmSnmpObjPortProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSnmpObjPortProperties dialog


CDlgQnmSnmpObjPortProperties::CDlgQnmSnmpObjPortProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmSnmpObjPortProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmSnmpObjPortProperties)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmSnmpObjPortProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmSnmpObjPortProperties)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmSnmpObjPortProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmSnmpObjPortProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSnmpObjPortProperties message handlers

 //  iPortIfIndex为-1时，查看所有信息 
 BOOL  CDlgQnmSnmpObjPortProperties::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac,  int  iPortIfIndex  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMacValid(  mac  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	safeStrnCpy(  mac,  m_var.switchMac,  sizeof(  m_var.switchMac  )  );
	m_var.iPortIfIndex  =  iPortIfIndex;

	return  TRUE;
}


BOOL CDlgQnmSnmpObjPortProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return  FALSE;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	// TODO: Add extra initialization here
	if  (  bGetPortInfoBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  m_var.iPortIfIndex,  0,  NULL,  &m_var.portInfo,  &m_var.portSecurityInfo  )  )  {
		SetDlgItemText(  IDC_STATIC_portIfDescr,  CString(  m_var.portInfo.portIfDescr  )  );
		SetDlgItemInt(  IDC_STATIC_portIfIndex,  m_var.portInfo.iPortIfIndex  );
		SetDlgItemInt(  IDC_STATIC_vlanId,  m_var.portInfo.lVlanId  );

		if  (  !m_var.portSecurityInfo.ucbCpsIfPortSecurityEnable  )  {
			SetDlgItemText(  IDC_STATIC_iCpsIfMaxSecureMacAddr,  _T(  ""  )  );
			SetDlgItemText(  IDC_STATIC_iCpsIfCurrentSecureMacAddrCount,  _T(  ""  )  );
			SetDlgItemText(  IDC_STATIC_iCpsIfViolationAction,  _T(  ""  )  );
			SetDlgItemText(  IDC_STATIC_iCpsIfPortSecurityStatus,  _T(  ""  )  );
			}
		else  {
			  SetDlgItemInt(  IDC_STATIC_iCpsIfMaxSecureMacAddr,  m_var.portSecurityInfo.iCpsIfMaxSecureMacAddr  );
			  SetDlgItemInt(  IDC_STATIC_iCpsIfCurrentSecureMacAddrCount,  m_var.portSecurityInfo.iCpsIfCurrentSecureMacAddrCount  );
			  SetDlgItemText(  IDC_STATIC_iCpsIfViolationAction,  CString(  qyGetDesByType1(  CONST_iCpsIfViolationActionTable,  m_var.portSecurityInfo.iCpsIfViolationAction  )  )  );
			  SetDlgItemText(  IDC_STATIC_iCpsIfPortSecurityStatus,  CString(  qyGetDesByType1(  CONST_iCpsIfPortSecurityStatusTable,  m_var.portSecurityInfo.iCpsIfPortSecurityStatus  )  )  );
		}

		}
	else  {

		  SetDlgItemText(  IDC_STATIC_portIfDescr,  _T(  ""  )  );
		  SetDlgItemText(  IDC_STATIC_portIfIndex,  _T(  ""  )  );
		  SetDlgItemText(  IDC_STATIC_vlanId,  _T(  ""  )  );
			
		  SetDlgItemText(  IDC_STATIC_iCpsIfMaxSecureMacAddr,  _T(  ""  )  );
		  SetDlgItemText(  IDC_STATIC_iCpsIfCurrentSecureMacAddrCount,  _T(  ""  )  );
		  SetDlgItemText(  IDC_STATIC_iCpsIfViolationAction,  _T(  ""  )  );
		  SetDlgItemText(  IDC_STATIC_iCpsIfPortSecurityStatus,  _T(  ""  )  );

	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

