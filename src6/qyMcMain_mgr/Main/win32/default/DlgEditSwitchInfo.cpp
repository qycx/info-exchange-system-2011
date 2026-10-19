// DlgEditSwitchInfo.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgEditSwitchInfo.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditSwitchInfo dialog


CDlgEditSwitchInfo::CDlgEditSwitchInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditSwitchInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditSwitchInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


void CDlgEditSwitchInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditSwitchInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditSwitchInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgEditSwitchInfo)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgEditSwitchInfo::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditSwitchInfo message handlers

 BOOL  CDlgEditSwitchInfo::bSetDlgInfo(  int  type,  QY_OBJ_DB  *  pObjDb,  HWND  hParent,  long  lHelpId,  unsigned  char  ucbAuditSwitchAndAllConns  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	m_var.type		=  type;
	m_var.pObjDb	=  pObjDb;
	m_var.hParent	=  hParent;
	m_var.lHelpId	=  lHelpId;
	m_var.ucbAuditSwitchAndAllConns  =  ucbAuditSwitchAndAllConns;

	return  TRUE;
}

 BOOL CDlgEditSwitchInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int					iErr	=	-1;
	QY_MC			*	pQyMc  =  QY_GET_GBUF(  );
	QY_OBJINDEX_RCD		objIndex;
	char				timeBuf[32];
	char				switchMac[CONST_qyMacLen  +  1];
	
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  this->m_cusNameEdit.setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitAll,  NULL  );
	//  this->m_cusNameEdit.SubclassDlgItem(  IDC_EDIT_cusName,  this  );
	
	if  (  g_dbFuncs.pf_getObjIndex(  m_var.pObjDb,  m_var.lHelpId,  &objIndex  )  
		||  !myTChar2Str(  objIndex.objIdStr0,  switchMac,  sizeof(  switchMac  )  )
			||  !bGetSnmpObjHeadInfoBySth(  m_var.pObjDb->pDb,  switchMac,  NULL,  &m_var.objHead  )  )  
	{
		goto  errLabel;
	}

	if  (  !m_var.ucbAuditSwitchAndAllConns  )  SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_IDD_editSwitchInfo_only  )/*  _T(  "仅编辑审核网络设备"  )  */  );
	else  SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_IDD_editSwitchInfo  )/*_T(  "编辑审核网络设备(及端口联接)"  )*/  );
	
	SetDlgItemText(  IDC_EDIT_cusName,  CString(  m_var.objHead.cusName  )  );
	GetDlgItem(  IDC_EDIT_cusName  )->SendMessage(  EM_SETLIMITTEXT,  sizeof(  m_var.objHead.cusName  ),  0  );
	SetDlgItemText(  IDC_EDIT_place,  CString(  m_var.objHead.place  )  );
	GetDlgItem(  IDC_EDIT_place  )->SendMessage(  EM_SETLIMITTEXT,  sizeof(  m_var.objHead.place  ),  0  );
	SetDlgItemText(  IDC_STATIC_auditTime,  CString(  qyDisplayTime(  m_var.objHead.auditTime,  timeBuf,  sizeof(  timeBuf  )  )  )  );
	
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}
	return  TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 void  CDlgEditSwitchInfo::OnOK() 
{
	QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	QY_SNMPOBJ_HEAD		objHead;
	TCHAR				sqlBuf[1024];
	char				ip12[12  +  1]						=	"";
	char				timeBuf[CONST_qyTimeLen  +  1]		=	"";
	CString				str;

	memset(  &objHead,  0,  sizeof(  objHead  )  );
	GetDlgItemText(  IDC_EDIT_place,  str  );  lstrcpyn(  objHead.place,  str,  mycountof(  objHead.place  )  );
	tTrim(  objHead.place  );
	GetDlgItemText(  IDC_EDIT_cusName,  str  );  lstrcpyn(  objHead.cusName,  str,  mycountof(  objHead.cusName  )  );
	tTrim(  objHead.cusName  );
	
	getCurTime(  timeBuf  );

	//  对本交换机审核
	if  (  !m_var.objHead.auditTime[0]
		||  lstrcmp(  m_var.objHead.cusName,  objHead.cusName  )
			||  lstrcmp(  m_var.objHead.place,  objHead.place  )  )
	{
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qySnmpObjTab set cusName='%s',place='%s',auditTime='%s' where mac='%s'"  ),  objHead.cusName,  objHead.place,  CString(  timeBuf  ),  CString(  m_var.objHead.mac  )  );
		if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  traceLogA(  "sql failed: sql is [%s]",  sqlBuf  );
		m_var.ucbChanged  =  TRUE;
	}

	//  对本交换机的各端口的mac的联接进行审核
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qySwitchConnectedPcTab set auditTime='%s' where connectedMac in (select portIfPhysAddress from qySwitchPortTab where switchMac='%s')"  ),  CString(  timeBuf  ),  CString(  m_var.objHead.mac  )  );
	if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  traceLogA(  "sql failed: sql is [%s]",  sqlBuf  );
	m_var.ucbChanged  =  TRUE;

	if  (  m_var.ucbAuditSwitchAndAllConns  )  {  //  对联接表中的联接进行审核
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qySwitchConnectedPcTab set auditTime='%s' where switchMac='%s'"  ),  CString(  timeBuf  ),  CString(  m_var.objHead.mac  )  );
		if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  traceLogA(  "sql failed: sql is [%s]",  sqlBuf  );
		m_var.ucbChanged  =  TRUE;
	}

	//  下面是更换一下策略表中的别名，为方便显示
	qyStdToIp12(  m_var.objHead.ip,  ip12  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qySnmpObjPolicyTab set cusName='%s' where ip='%s'"  ),  objHead.cusName,  CString(  ip12  )  );
	if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  traceLogA(  "sql failed: sql is [%s]",  sqlBuf  );
	
	CDialog::OnOK();

}



 void CDlgEditSwitchInfo::OnBnClickedOk()
 {
	 // TODO: Add your control notification handler code here
	 OnOK();
 }
