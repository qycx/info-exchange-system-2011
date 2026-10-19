
// DlgQnmCfgAdvancedOptions.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmCfgAdvancedOptions.h"
#include	"qyCusResTemp.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgAdvancedOptions dialog


CDlgQnmCfgAdvancedOptions::CDlgQnmCfgAdvancedOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgAdvancedOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgAdvancedOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmCfgAdvancedOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgAdvancedOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgAdvancedOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgAdvancedOptions)
	ON_CBN_SELCHANGE(IDC_COMBO_dbTypeName, OnSelchangeCOMBOdbTypeName)
	ON_BN_CLICKED(IDC_CHECK_default, OnCHECKdefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgAdvancedOptions message handlers



 BOOL CDlgQnmCfgAdvancedOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC			*	pQyMc					=	QY_GET_GBUF(  );
	int					iErr					=	-1;
	QY_REG				reg;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CString(  CONST_dbTypeName_access  ).GetBuffer(  0  )  );
	//  GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CONST_dbTypeName_oracle  );
	GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CString(  CONST_dbTypeName_sqlServer  ).GetBuffer(  0  )  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	//  if  (  safeStrCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
	lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	reg.pEncCtx  =  &pQyMc->encCtx;
	if  (  getQnmDbParams(  &reg,  pQyMc->iSystemId,  pQyMc->cfg.ucbDsnless,  pQyMc->cfg.defaultDbName,  &m_var.dbCfg  )  )  goto  errLabel;
	GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_SELECTSTRING,  0,  (  LPARAM  )CString(  qyGetDesByType1(  CONST_dbTypeTable,  m_var.dbCfg.iDbType  )  ).GetBuffer(  0  )  );
	SetDlgItemText(  IDC_EDIT_dbServIp,  CString(  m_var.dbCfg.dbServIp  )  );
	SetDlgItemText(  IDC_EDIT_dbName,  CString(  m_var.dbCfg.dbName  )  );
	SetDlgItemText(  IDC_EDIT_uid,  CString(  m_var.dbCfg.uid  )  );
	SetDlgItemText(  IDC_EDIT_pwd,  CString(  m_var.dbCfg.pwd  )  );
		
	GetDlgItem(  IDC_EDIT_dbServIp  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_EDIT_dbName  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_EDIT_uid  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_EDIT_pwd  )->EnableWindow(  FALSE  );
		
	(  (  CButton  *  )GetDlgItem(  IDC_CHECK_default  )  )->SetCheck(  m_var.dbCfg.bDefault  ?  1  :  0  );
	
	iErr  =  0;
	
errLabel:

	if  (  iErr  )  EndDialog(  -1  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



 void CDlgQnmCfgAdvancedOptions::OnSelchangeCOMBOdbTypeName() 
{	 
	 // TODO: Add your control notification handler code here
	QY_MC	*	pQyMc						=	QY_GET_GBUF(  );
	 char		dbTypeName[128  +  1];  
	 CString	str;

	 (  (  CButton  *  )GetDlgItem(  IDC_CHECK_default  )  )->SetCheck(  0  );
	 GetDlgItemText(  IDC_COMBO_dbTypeName,  str  );  myTChar2Str(  str,  dbTypeName,  sizeof(  dbTypeName  )  );
	 if  (  !strcmpi(  dbTypeName,  CONST_dbTypeName_sqlServer  )  )  {
		 SetDlgItemText(  IDC_EDIT_dbServIp,	CString(  DEFAULT_qnmDbServIp  )  );
		 //
		 if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {
			 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  SetDlgItemText(  IDC_EDIT_dbName,  CString(  DEFAULT_qisClientDbName  )  );
			 else  SetDlgItemText(  IDC_EDIT_dbName,  CString(  DEFAULT_qisDbName  )  );
			}
		 else  SetDlgItemText(  IDC_EDIT_dbName,		CString(  DEFAULT_qnmDbName  )  );
		 //
		 SetDlgItemText(  IDC_EDIT_uid,			CString(  DEFAULT_qnmDbUid  )  );
		 SetDlgItemText(  IDC_EDIT_pwd,			CString(  DEFAULT_qnmDbPwd  )  );

		 GetDlgItem(  IDC_EDIT_dbServIp  )->EnableWindow(  TRUE  );
		 GetDlgItem(  IDC_EDIT_dbName  )->EnableWindow(  TRUE  );
		 GetDlgItem(  IDC_EDIT_uid  )->EnableWindow(  FALSE  );
		 GetDlgItem(  IDC_EDIT_pwd  )->EnableWindow(  TRUE  );
		}
	 else  {

			SetDlgItemText(  IDC_EDIT_dbServIp,	 _T(  ""  )  );
			SetDlgItemText(  IDC_EDIT_dbName,  _T(  ""  )  );
			SetDlgItemText(  IDC_EDIT_uid,  _T(  ""  )  );
			SetDlgItemText(  IDC_EDIT_pwd,  _T(  ""  )  );
		   
			GetDlgItem(  IDC_EDIT_dbServIp  )->EnableWindow(  FALSE  );
			GetDlgItem(  IDC_EDIT_dbName  )->EnableWindow(  FALSE  );
			GetDlgItem(  IDC_EDIT_uid  )->EnableWindow(  FALSE  );
			GetDlgItem(  IDC_EDIT_pwd  )->EnableWindow(  FALSE  );
	 }

	 
}
 

  void CDlgQnmCfgAdvancedOptions::OnCHECKdefault() 
{
	// TODO: Add your control notification handler code here
	BOOL		bDefault				=	FALSE;
	char		dbTypeName[32  +  1]	=	"";
	CString		str;
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );

	bDefault  =  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_default  )  )->GetCheck(  )  ?  TRUE  :  FALSE;
	if  (  !bDefault  )  {
		GetDlgItemText(  IDC_COMBO_dbTypeName,  str  );  myTChar2Str(  str,  dbTypeName,  sizeof(  dbTypeName  )  );
		if  (  !strcmpi(  dbTypeName,  CONST_dbTypeName_oracle  )  )  {
			GetDlgItem(  IDC_EDIT_uid  )->EnableWindow(  FALSE  );
			GetDlgItem(  IDC_EDIT_pwd  )->EnableWindow(  TRUE  );
			}
		else  {
			  GetDlgItem(  IDC_EDIT_uid  )->EnableWindow(  FALSE  );
			  GetDlgItem(  IDC_EDIT_pwd  )->EnableWindow(  FALSE  );
		}
		goto  errLabel;
	}

	if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_restoreAccess  ),  MB_YESNO  |  MB_DEFBUTTON2   )  !=  IDYES  )  {
		(  (  CButton  *  )GetDlgItem(  IDC_CHECK_default  )  )->SetCheck(  0  );
		goto  errLabel;
	}
	
	/*
	GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_SELECTSTRING,  0,  (  LPARAM  )CONST_dbTypeName_oracle  );
	SetDlgItemText(  IDC_EDIT_uid,  CONST_qnmDb_uid  );
	SetDlgItemText(  IDC_EDIT_pwd,  CONST_qnmDb_pwd  );
	*/


	GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_SELECTSTRING,  0,  (  LPARAM  )CString(  CONST_dbTypeName_access  ).GetBuffer(  0  )  );
	SetDlgItemText(  IDC_EDIT_dbServIp,  _T(  ""  )  );
	SetDlgItemText(  IDC_EDIT_dbName,	_T(  ""  )  );	//  2007/01/07
	SetDlgItemText(  IDC_EDIT_uid,  _T(  ""  )  );
	SetDlgItemText(  IDC_EDIT_pwd,  _T(  ""  )  );
	GetDlgItem(  IDC_EDIT_uid  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_EDIT_pwd  )->EnableWindow(  FALSE  );
	
	
errLabel:
	
	return;

}



 void  CDlgQnmCfgAdvancedOptions::OnOK() 
{
	 QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	 WCHAR		dbTypeName[32  +  1]	=	L"";
	 int		iDbType					=	0;
	 int		iDbConnType				=	0;
	 char		dbServIp[64  +  1]		=	"";
	 WCHAR		dbName[64  +  1]		=	L"";
	 WCHAR		uid[128  +  1]			=	L"";
	 WCHAR		pwd[128  +  1]			=	L"";
	 BOOL		bDefault				=  FALSE;
	 WCHAR		connectStr[256  +  1]	=	L"";
	 QY_REG		reg;
	 CString	str;
	 
	 bDefault  =  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_default  )  )->GetCheck(  )  ?  TRUE  :  FALSE;
	 GetDlgItemText(  IDC_COMBO_dbTypeName,  str  );  myTChar2WChar(  str,  dbTypeName,  mycountof(  dbTypeName  )  );
	 iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  str  );
	 GetDlgItemText(  IDC_EDIT_dbServIp,  str  );  myTChar2Str(  str,  dbServIp,  sizeof(  dbServIp  )  );	trim(  dbServIp  );
	 GetDlgItemText(  IDC_EDIT_dbName,  str  );  myTChar2WChar(  str,  dbName,  mycountof(  dbName  )  );	tTrim(  dbName  );
	 GetDlgItemText(  IDC_EDIT_uid,  str  );  myTChar2WChar(  str,  uid,  mycountof(  uid  )  );			tTrim(  uid  );
	 GetDlgItemText(  IDC_EDIT_pwd,  str  );  myTChar2WChar(  str,  pwd,  mycountof(  pwd  )  );			tTrim(  pwd  );
	 //
	 if  (  iDbType  ==  CONST_dbType_access  )  {
		 traceLogA(  "对ACCESS数据库，都采用缺省配置"  );
		 bDefault  =  TRUE;
		 lstrcpyn(  dbName,  pQyMc->cfg.defaultDbName,  mycountof(  dbName  )  );
	 }
	 //  2012/07/12
	 iDbConnType  =  getDbConnType(  iDbType  );
	 //
	 if  (  constructDbConnectStr(  iDbType,  iDbConnType,  pQyMc->cfg.ucbDsnless,  dbServIp,  dbName,  uid,  pwd,  connectStr,  mycountof(  connectStr  )  )  )  {
		 traceLogA(  "connectStrQnmConnectStr failed."  );  return;
	 }

	 if  (  bDefault  ==  m_var.dbCfg.bDefault  &&  !lstrcmp(  connectStr,  m_var.dbCfg.connectStr  )  )  goto  errLabel;

	 if  (  AfxMessageBox(  getResStr(  0, &pQyMc->cusRes,  CONST_resId_ifChangeDb  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	 if  (  !wcsicmp(  dbTypeName,  _T(  CONST_dbTypeName_sqlServer  )  )  )  {
		 CWaitCursor	cursor;

		 if  (  !bDbConnected_netMc(  CString(  CONST_dbTypeName_sqlServer  ),  dbServIp,  uid,  pwd,  dbName  )  )  {
			 qyShowHint(  getResStr(  0, &pQyMc->cusRes,  CONST_resId_cannotConnectToDb  )  );  goto  errLabel;
		 }
		 if  (  !bDbInstalled_netMc(  CString(  CONST_dbTypeName_sqlServer  ),  dbServIp,  uid,  pwd,  dbName  )  )  {
			 traceLogA(  "先建数据库"  );
			 if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {
				 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
					 if  (  makeDb_isClient(  CString(  CONST_dbTypeName_sqlServer  ),  dbServIp,  uid,  pwd,  dbName,  pQyMc->iServiceId,  pQyMc->iSystemId,  pQyMc->iAppType,  qnmDbVerStr(  pQyMc->iServiceId  )  )  )  {
						 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_buildDbErr  )  );  goto  errLabel;
					 }
					}
				 else  {
					   if  (  makeDb_isMgr(  CString(  CONST_dbTypeName_sqlServer  ),  dbServIp,  uid,  pwd,  dbName,  pQyMc->iServiceId,  0,  0,  qnmDbVerStr(  pQyMc->iServiceId  )  )  )  {
						   qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_buildDbErr  )  );  goto  errLabel;
					   }
				 }
				 //
				 }
			 else  {
			 	   if  (  makeDb_netMc(  CString(  CONST_dbTypeName_sqlServer  ),  dbServIp,  uid,  pwd,  dbName,  pQyMc->iServiceId,  qnmDbVerStr(  pQyMc->iServiceId  )  )  )  {
				 	   qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_buildDbErr  )  );  goto  errLabel;
			 	   }
			 }
		 }		 
	 }

	 if  (  bDefault  )  {
		 qyDelRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CString(  CONST_regValName_dbTypeName  )  );
		 qyDelRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  CString(  CONST_regValName_connectStr  )  );
		}
	 else  {
		   char		buf[2048];
		   TCHAR	tBuf[2048];
	 
		   memset(  &reg,  0,  sizeof(  reg  )  );	
		   //  if  (  safeStrCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
		   lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
		   reg.pEncCtx  =  &pQyMc->encCtx;

		   qySetRegCfg(  reg.rootKey,  CString(  CONST_regValName_dbTypeName  ),  dbTypeName  );
		   /*
		   myWChar2Utf8(  connectStr,  buf,  mycountof(  buf  )  );
		   qySetRegDataEx(  &reg,  CONST_regValName_connectStr,  buf,  strlen(  buf  )  );
		   */
		   myWChar2TChar(  connectStr,  tBuf,  mycountof(  tBuf  )  );
		   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s=%s;%s=%s;%s=%d;"  ),  tBuf,  CString(  CONST_qyCfgName_dbType  ),  qyGetDesByType1(  CONST_dbTypeTable,  iDbType  ),  CString(  CONST_qyCfgName_sysName  ),  _T(  ""  ),  CString(  CONST_qyCfgName_systemId  ),  pQyMc->iSystemId  );
		   buf[0]  =  0;
		   myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		   qySetRegDataEx(  &reg,  CString(  CONST_regValName_connectStr  ),  buf,  strlen(  buf  )  );
		   
	 }
	 
	 AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_restart  )  );
	 	 
errLabel:	

	CDialog::OnOK();

}





