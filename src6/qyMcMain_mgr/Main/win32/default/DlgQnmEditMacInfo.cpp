// DlgQnmEditMacInfo.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmEditMacInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEditMacInfo dialog


CDlgQnmEditMacInfo::CDlgQnmEditMacInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmEditMacInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmEditMacInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmEditMacInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmEditMacInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmEditMacInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmEditMacInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEditMacInfo message handlers


 BOOL  CDlgQnmEditMacInfo::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  switchMac,  char  *  mac  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMacValid(  switchMac  )  ||  !bMacValid(  mac  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	safeStrnCpy(  switchMac,  m_var.switchMac,  sizeof(  m_var.switchMac  )  );
	safeStrnCpy(  mac,  m_var.mac,  sizeof(  m_var.mac  )  );

	return  TRUE;
}




BOOL CDlgQnmEditMacInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	QY_MC						*		pQyMc		=	QY_GET_GBUF(  );
	HWND								hWnd		=	this->m_hWnd;
	BOOL								bRet		=	FALSE;
	QY_SNMPOBJ_HEAD						snmpObjHead;
	TCHAR								buf[1024];
	char								timeBuf[128  +  1];
	
	memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  {
		EndDialog(  -1  );  goto  errLabel;
	}

	
	if  (  !bGetConnectedPcInfoBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  m_var.mac,  NULL,  &m_var.connInfo,  NULL  )
		||  !bGetSnmpObjHeadInfoBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  NULL,  &snmpObjHead  )  )  
	{
		traceLogA(  "bGetSnmpObjHeadInfoBySth failed."  );
		EndDialog(  -1  );  goto  errLabel;
	}
	_sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s(%s)"  ),  snmpObjHead.productName,  CString(  snmpObjHead.ip  )  );
	SetDlgItemText(  IDC_STATIC_switch,  CString(  buf  )  );
	_sntprintf(  buf,  mycountof(  buf  ),  _T(  "%d"  ),  m_var.connInfo.iPortIfIndex  );  
	SetDlgItemText(  IDC_STATIC_switchPort,  CString(  buf  )  );	
	SetDlgItemText(  IDC_STATIC_mac,  CString(  m_var.mac  )  );
	if  (  getDesOfMac(  m_var.pObjDb,  m_var.mac,  m_var.des0,  sizeof(  m_var.des0  ),  &m_var.ucbDesMunually  )  )  m_var.des0[0]  =  0;
	SetDlgItemText(  IDC_EDIT_devType,  CString(  m_var.des0  )  );
	if  (  !m_var.ucbDesMunually  &&  m_var.des0[0]  )  GetDlgItem(  IDC_EDIT_devType  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbDirectConn  )->SendMessage(  BM_SETCHECK,  m_var.connInfo.ucbDirectConn  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_STATIC_auditTime,  CString(  qyDisplayTime(  m_var.connInfo.auditTime,  timeBuf,  sizeof(  timeBuf  )  )  )  );
		
errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 void CDlgQnmEditMacInfo::OnOK() 
{
	 QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	 unsigned  char		ucbDirectConn	=	FALSE;
	 char				buf[1024]		=	"";
	 TCHAR				des0[sizeof(  m_var.des0  )];
	 CString			sqlStr;
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 CString			str;

	 ucbDirectConn  =  (  GetDlgItem(  IDC_CHECK_ucbDirectConn  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  TRUE  :  FALSE;
	 GetDlgItemText(  IDC_EDIT_devType,  des0,  mycountof(  des0  )  );
	 getCurTime(  timeBuf  );
	 
	 if  (  lstrcmp(  des0,  m_var.des0  )  )  {
		 if  (  !m_var.des0[0]  )  {
			 sqlStr  =  CString(  "insert into qnmMacDesTab(mac,devType,des0) "  )
						+  " values('"  +  m_var.mac  +  "','','"  +  des0  +  "')";
			 if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  traceLogA(  "sql failed:%s",  sqlStr.GetBuffer(  0  )  );
			}
		 else  if  (  m_var.ucbDesMunually  )  {
				   sqlStr  =  CString(  "update qnmMacDesTab "  )
							  +  "set des0='"  +  des0  +  "'"
							  +  " where mac='"  +  m_var.mac  +  "'";
				   if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  traceLogA(  "sql failed:%s",  sqlStr.GetBuffer(  0  )  );
		 }
		 m_var.ucbChanged  =  TRUE;
	 }

	 if  (  m_var.connInfo.ucbDirectConn  !=  ucbDirectConn
			||  !m_var.connInfo.auditTime[0]  )
	 {
		 //  审核并设置接入设置
		 sqlStr  =  CString(  "update qySwitchConnectedPcTab "  )
					+  "set ucbDirectConn='"  +  (  ucbDirectConn  ?  "1"  :  ""  )  +  "'"
					+  ",auditTime='"  +  timeBuf  +  "'"
					+  " where switchMac='"  +  m_var.switchMac  +  "' and connectedMac='"  +  m_var.mac  +  "'";		
		 if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  traceLogA(  "sql failed:%s",  sqlStr.GetBuffer(  0  )  );

		 //  将其他的网络设备和此mac的联接都审核但去除接入设置
		 sqlStr  =  CString(  "update qySwitchConnectedPcTab "  )
					+  "set ucbDirectConn=''"
					+  ",auditTime='"  +  timeBuf  +  "'"
					+  " where switchMac<>'"  +  m_var.switchMac  +  "' and connectedMac='"  +  m_var.mac  +  "'";		
		 if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlStr.GetBuffer(  0  )  )  )  traceLogA(  "sql failed:%s",  sqlStr.GetBuffer(  0  )  );

		 
		 m_var.ucbChanged  =  TRUE;
	 }
	
	CDialog::OnOK();
}
