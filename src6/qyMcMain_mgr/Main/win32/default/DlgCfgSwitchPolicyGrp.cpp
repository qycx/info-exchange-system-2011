// DlgCfgSwitchPolicyGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgSwitchPolicyGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchPolicyGrp dialog


CDlgCfgSwitchPolicyGrp::CDlgCfgSwitchPolicyGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgSwitchPolicyGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgSwitchPolicyGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgSwitchPolicyGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgSwitchPolicyGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgSwitchPolicyGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgSwitchPolicyGrp)
	ON_CBN_SELCHANGE(IDC_COMBO_snmpVer, OnSelchangeCOMBOsnmpVer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchPolicyGrp message handlers

 BOOL  CDlgCfgSwitchPolicyGrp::bSetDlgInfo(  int  type,  CWnd * pSrcWnd,  char  *  policyGrpName  )
{
	m_var.type  =  type;
	m_var.pSrcWnd  =  pSrcWnd;
	if  (  policyGrpName  )  safeStrnCpy(  policyGrpName,  m_var.policyGrpName,  sizeof(  m_var.policyGrpName  )  );
	return  TRUE;
}



void CDlgCfgSwitchPolicyGrp::OnSelchangeCOMBOsnmpVer() 
{
	char  snmpVer[128  +  1]  =  "";
	CString	str;

	GetDlgItemText(  IDC_COMBO_snmpVer,  str  );
	myTChar2Str(  str.GetBuffer(  0  ),  snmpVer,  sizeof(  snmpVer  )  );
	if  (  !strcmpi(  snmpVer,  "v1"  )  ||  !strcmpi(  snmpVer,  "v2c"  )  )  {
		SetDlgItemText(  IDC_EDIT_usmName,  _T(  ""  )  );
		GetDlgItem(  IDC_EDIT_usmName  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_COMBO_securityLevel  )->EnableWindow(  FALSE  );
		}
	else  {
		  GetDlgItem(  IDC_EDIT_usmName  )->EnableWindow(  TRUE  );
		  GetDlgItem(  IDC_COMBO_securityLevel  )->EnableWindow(  TRUE  );		  
	}
	
}

 BOOL  bGetSnmpPolicyGrpInfoByName(  void  *  pDb,  char  *  policyGrpName,  QY_SNMPPOLICYGRP_RCD  *  pPolicy  )
{
	 BOOL				bRet				=	FALSE;
	 char				sqlBuf[1024  +  1];
	 CDBVariant			varVals[30];
	 int				index				=	0;
	 TCHAR				tBuf[1024];

	 if  (  !policyGrpName  ||  !policyGrpName[0]  )  goto  errLabel;
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySnmpPolicyGrpTab.snmpVer,qySnmpPolicyGrpTab.getCommunity,qySnmpPolicyGrpTab.setCommunity,qySnmpPolicyGrpTab.usmName,qySnmpPolicyGrpTab.securityLevel,qySnmpPolicyGrpTab.authMethod,qySnmpPolicyGrpTab.authStr,qySnmpPolicyGrpTab.privMethod,qySnmpPolicyGrpTab.privStr,qySnmpPolicyGrpTab.engineId from qySnmpPolicyGrpTab where qySnmpPolicyGrpTab.name='%s'",  policyGrpName  );
	 if  (  !bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 safeStrnCpy(  policyGrpName,  pPolicy->name,  sizeof(  pPolicy->name  )  );
	 
	 index  =  0;		//  qySnmpPolicyGrpTab.snmpVer
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->snmpVer,  sizeof(  pPolicy->snmpVer  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.getCommunity
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.setCommunity
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.usmName
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->usmName,  sizeof(  pPolicy->usmName  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.securityLevel
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->securityLevel,  sizeof(  pPolicy->securityLevel  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.authMethod
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->authMethod,  sizeof(  pPolicy->authMethod  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.authStr
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->authStr,  sizeof(  pPolicy->authStr  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.privMethod
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->privMethod,  sizeof(  pPolicy->privMethod  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.privStr
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->privStr,  sizeof(  pPolicy->privStr  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.engineId 
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->engineId,  sizeof(  pPolicy->engineId  )  );  
	 index  ++  ;

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

BOOL CDlgCfgSwitchPolicyGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	char		buf[32];
	TCHAR		tBuf[32];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.type  ==  CONST_qyDlgType_add  )  {
		(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_snmpVer  )  )->SetCurSel(  0  );
		SetDlgItemText(  IDC_EDIT_getCommunity,  _T(  "public"  )  );
		SetDlgItemText(  IDC_EDIT_setCommunity,  _T(  "private"  )  );
		}
	else  if  (  m_var.type  ==  CONST_qyDlgType_modify  )  {
			
			  GetDlgItem(  IDC_EDIT_grpName  )->EnableWindow(  FALSE  );

		      if  (  bGetSnmpPolicyGrpInfoByName(  pQyMc->gui.pDb,  m_var.policyGrpName,  &m_var.snmpPolicy  )  )  {
				  SetDlgItemText(  IDC_EDIT_grpName,  CString(  m_var.snmpPolicy.name  )  );
				  (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_snmpVer  )  )->SelectString(  -1,  CString(  m_var.snmpPolicy.snmpVer  )  );
				  SetDlgItemText(  IDC_EDIT_getCommunity,  CString(  m_var.snmpPolicy.getCommunity  )  );
				  SetDlgItemText(  IDC_EDIT_setCommunity,  CString(  m_var.snmpPolicy.setCommunity  )  );
				  SetDlgItemText(  IDC_EDIT_usmName,  CString(  m_var.snmpPolicy.usmName  )  );
			  }				
	}


	GetDlgItemText(  IDC_COMBO_snmpVer,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	trim(  buf  );
	if  (  strcmpi(  buf,  "v3"  )  )  {
		GetDlgItem(  IDC_EDIT_usmName  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_COMBO_securityLevel  )->EnableWindow(  FALSE  );
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgCfgSwitchPolicyGrp::OnOK() 
{
	QY_MC					*	pQyMc				=	QY_GET_GBUF(  );
	char						sqlBuf[1024  +  1];
	QY_SNMPPOLICYGRP_RCD		snmpPolicy;
	CDBVariant					varVals[5];
	//  char						securityLevelDisplayBuf[128  +  1];
	TCHAR						tBuf[256];

	memset(  &snmpPolicy,  0,  sizeof(  snmpPolicy  )  );
	GetDlgItemText(  IDC_EDIT_grpName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  snmpPolicy.name,  sizeof(  snmpPolicy.name  )  );
	GetDlgItemText(  IDC_COMBO_snmpVer,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  snmpPolicy.snmpVer,  sizeof(  snmpPolicy.snmpVer  )  );
	GetDlgItemText(  IDC_EDIT_getCommunity,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  snmpPolicy.getCommunity,  sizeof(  snmpPolicy.getCommunity  )  );
	GetDlgItemText(  IDC_EDIT_setCommunity,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  snmpPolicy.setCommunity,  sizeof(  snmpPolicy.setCommunity  )  );
	GetDlgItemText(  IDC_EDIT_usmName,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  snmpPolicy.usmName,  sizeof(  snmpPolicy.usmName  )  );
	//  GetDlgItemText(  IDC_COMBO_securityLevel,  securityLevel,  sizeof(  snmpPolicy.securityLevel  )  );
	safeStrnCpy(  "0",	snmpPolicy.securityLevel,  sizeof(  snmpPolicy.securityLevel  )  );
	trim(  snmpPolicy.name  );
	trim(  snmpPolicy.getCommunity  );
	trim(  snmpPolicy.setCommunity  );
	trim(  snmpPolicy.usmName  );
	if  (  !snmpPolicy.name[0]  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_grpNameCannotEmpty )  );  return;
	}


	if  (  m_var.type  ==  CONST_qyDlgType_add  )  {
		//  检查是否有同名组存在
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select name from qySnmpPolicyGrpTab where name='%s'",  snmpPolicy.name  );
		if  (  bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
			AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fieldCannotSame  )  );  return;
		}
		
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "insert into qySnmpPolicyGrpTab(name,snmpVer,getCommunity,setCommunity,usmName,securityLevel,authMethod,authStr,privMethod,privStr,engineId)"
												  " values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",
												  snmpPolicy.name,  snmpPolicy.snmpVer,  snmpPolicy.getCommunity,  snmpPolicy.setCommunity,  snmpPolicy.usmName,  
												  snmpPolicy.securityLevel,  snmpPolicy.authMethod,  snmpPolicy.authStr,  snmpPolicy.privMethod,  snmpPolicy.privStr,  snmpPolicy.engineId  );
		if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
			traceLogA(  "执行失败"  );  goto  errLabel;
		}
		}
	else  if  (  m_var.type  ==  CONST_qyDlgType_modify  )  {
		      if  (  !memcmp(  &m_var.snmpPolicy,  &snmpPolicy,  sizeof(  snmpPolicy  )  )  )  goto  errLabel;
			  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "update qySnmpPolicyGrpTab set snmpVer='%s',getCommunity='%s',setCommunity='%s',usmName='%s',securityLevel='%s',authMethod='%s',authStr='%s',privMethod='%s',privStr='%s',engineId='%s' where name='%s'",
												  snmpPolicy.snmpVer,  snmpPolicy.getCommunity,  snmpPolicy.setCommunity,  snmpPolicy.usmName,  
												  snmpPolicy.securityLevel,  snmpPolicy.authMethod,  snmpPolicy.authStr,  snmpPolicy.privMethod,  snmpPolicy.privStr,  snmpPolicy.engineId,
												  snmpPolicy.name  );
		if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
			traceLogA(  "执行失败"  );  goto  errLabel;
		}

	}

	m_var.ucbChanged  =  TRUE;

	
errLabel:

	CDialog::OnOK();
}
