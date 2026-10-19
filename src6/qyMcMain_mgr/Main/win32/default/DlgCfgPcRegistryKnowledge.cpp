// DlgCfgPcRegistryKnowledge.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgPcRegistryKnowledge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistryKnowledge dialog


CDlgCfgPcRegistryKnowledge::CDlgCfgPcRegistryKnowledge(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgPcRegistryKnowledge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgPcRegistryKnowledge)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgCfgPcRegistryKnowledge::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  iRootKey,  LPCTSTR  subKey,  LPCTSTR  cfgName,  int  id  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
 
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;
	 if  (  iRootKey  &&  subKey  &&  cfgName  )  {
		 m_var.iRootKey  =  iRootKey;
		 lstrcpyn(  m_var.subKey,  subKey,  mycountof(  m_var.subKey  )  );
		 tTrim(  m_var.subKey  );
		 lstrcpyn(  m_var.cfgName,  cfgName,  mycountof(  m_var.cfgName  )  );
		 tTrim(  m_var.cfgName  );
	 }

	 
	 if  (  !bGetPcRegistryKnowledgeBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.iRootKey,  m_var.subKey,  m_var.cfgName,  id,  &m_var.knowledge  )  )  {
		 memset(  &m_var.knowledge,  0,  sizeof(  m_var.knowledge  )  );
		 if  (  m_var.iRootKey  &&  m_var.subKey[0]  &&  m_var.cfgName[0]  )  {
			 m_var.knowledge.iRootKey  =  m_var.iRootKey;
			 lstrcpyn(  m_var.knowledge.subKey,  m_var.subKey,  mycountof(  m_var.knowledge.subKey  )  );
			 lstrcpyn(  m_var.knowledge.cfgName,  m_var.cfgName,  mycountof(  m_var.knowledge.cfgName  )  );
		 }
	 }
	 

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

void CDlgCfgPcRegistryKnowledge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgPcRegistryKnowledge)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgPcRegistryKnowledge, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgPcRegistryKnowledge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistryKnowledge message handlers


BOOL CDlgCfgPcRegistryKnowledge::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );
	char			displayBuf[256];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	bQnmFillCol0FromTable(  CONST_iRootKeyTable,  GetDlgItem(  IDC_COMBO_iRootKey  )->m_hWnd,  0  );


	if  (  !m_var.knowledge.iRootKey  )  {

		GetDlgItem(  IDC_STATIC_iRootKeyVal  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_subKeyVal  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_cfgNameVal  )->ShowWindow(  SW_HIDE  );

		GetDlgItem(  IDC_COMBO_iRootKey  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  CONST_iRootKeyTable,  CONST_iRootKeyTable[0].type  )  );

		}
	else  {
		  GetDlgItem(  IDC_COMBO_iRootKey  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_EDIT_subKey  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_EDIT_cfgName  )->ShowWindow(  SW_HIDE  );

		  SetDlgItemText(  IDC_STATIC_iRootKeyVal,  qyGetDesByType1(  CONST_iRootKeyTable,  m_var.knowledge.iRootKey  )  );
		  SetDlgItemText(  IDC_STATIC_subKeyVal,  m_var.knowledge.subKey  );
		  SetDlgItemText(  IDC_STATIC_cfgNameVal,  m_var.knowledge.cfgName  );
		  
	}

	SetDlgItemText(  IDC_EDIT_suggestedVal,  m_var.knowledge.suggestedVal  );

	SetDlgItemText(  IDC_EDIT_name,  m_var.knowledge.name  );
	SetDlgItemText(  IDC_EDIT_des0,  m_var.knowledge.des0  );
	SetDlgItemText(  IDC_EDIT_company,  m_var.knowledge.company  );
	SetDlgItemText(  IDC_EDIT_product,  m_var.knowledge.product  );
	GetDlgItem(  IDC_CHECK_ucbSys  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbSys  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbDaemon  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbDaemon  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbUseNet  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbUseNet    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbHardware  )->SendMessage(  BM_SETCHECK,  	m_var.knowledge.ucbHardware    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_commonErr,  m_var.knowledge.commonErr  );
	SetDlgItemInt(  IDC_EDIT_securityLevel,  m_var.knowledge.securityLevel  );
	GetDlgItem(  IDC_CHECK_ucbSpy  )->SendMessage(  BM_SETCHECK,  	m_var.knowledge.ucbSpy  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbAdvertisement    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbVirus  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbVirus  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbBackDoor  )->SendMessage(  BM_SETCHECK,  	m_var.knowledge.ucbBackDoor   ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_providerName,  m_var.knowledge.provider  );
	SetDlgItemText(  IDC_EDIT_providerAddr,  m_var.knowledge.providerAddr  );
	SetDlgItemText(  IDC_EDIT_providerTime,  m_var.knowledge.providerTime  );
	SetDlgItemText(  IDC_STATIC_auditTime,  CString(  qyDisplayTime(  m_var.knowledge.auditTime,  displayBuf,  sizeof(  displayBuf  )  )  )  );




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgCfgPcRegistryKnowledge::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC						*	pQyMc	=	QY_GET_GBUF(  );
	QY_PCREGISTRYKNOWLEDGE_RCD		rcd;
	TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1];
	char							timeBuf[CONST_qyTimeLen  +  1];
	TCHAR							tBuf[256];

	memset(  &rcd,  0,  sizeof(  rcd  )  );

	if  (  m_var.knowledge.iRootKey  )  {
		rcd.iRootKey  =  m_var.knowledge.iRootKey;
		lstrcpyn(  rcd.subKey,  m_var.knowledge.subKey,  mycountof(  rcd.subKey  )  );
		lstrcpyn(  rcd.cfgName,  m_var.knowledge.cfgName,  mycountof(  rcd.cfgName  )  );
		}
	else  {
		  GetDlgItemText(  IDC_COMBO_iRootKey,  tBuf,  mycountof(  tBuf  )  );
		  rcd.iRootKey  =  qyGetTypeByDes(  CONST_iRootKeyTable,  tBuf  );
		  GetDlgItemText(  IDC_EDIT_subKey,  rcd.subKey,  mycountof(  rcd.subKey  )  );  
		  tTrim(  rcd.subKey  );
		  GetDlgItemText(  IDC_EDIT_cfgName,  rcd.cfgName,  mycountof(  rcd.cfgName  )  );  
		  tTrim(  rcd.cfgName  );
	}
	
	if  (  !rcd.iRootKey  ||  !rcd.subKey[0]  )  {
		qyShowHint(  _T(  "根键和子键不能为空"  )  );  return;
	}

	GetDlgItemText(  IDC_EDIT_suggestedVal,  rcd.suggestedVal,  mycountof(  rcd.suggestedVal  )  );
	//
    GetDlgItemText(  IDC_EDIT_name,  rcd.name,  mycountof(  rcd.name  )  );
	GetDlgItemText(  IDC_EDIT_des0,  rcd.des0,  mycountof(  rcd.des0  )  );
	GetDlgItemText(  IDC_EDIT_company,  rcd.company,  mycountof(  rcd.company  )  );
	GetDlgItemText(  IDC_EDIT_product,  rcd.product,  mycountof(  rcd.product  )  );
	rcd.ucbSys  =  GetDlgItem(  IDC_CHECK_ucbSys  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbDaemon  =  GetDlgItem(  IDC_CHECK_ucbDaemon  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbUseNet  =  GetDlgItem(  IDC_CHECK_ucbUseNet  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbHardware  =  GetDlgItem(  IDC_CHECK_ucbHardware  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	GetDlgItemText(  IDC_EDIT_commonErr,  rcd.commonErr,  mycountof(  rcd.commonErr  )  );
	rcd.securityLevel  =  GetDlgItemInt(  IDC_EDIT_securityLevel  );
	rcd.ucbSpy  =  GetDlgItem(  IDC_CHECK_ucbSpy  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbAdvertisement  =  GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbVirus  =  GetDlgItem(  IDC_CHECK_ucbVirus  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbBackDoor  =  GetDlgItem(  IDC_CHECK_ucbBackDoor  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	GetDlgItemText(  IDC_EDIT_providerName,  rcd.provider,  mycountof(  rcd.provider  )  );
	GetDlgItemText(  IDC_EDIT_providerAddr,  rcd.providerAddr,  mycountof(  rcd.providerAddr  )  );
	GetDlgItemText(  IDC_EDIT_providerTime,  rcd.providerTime,  mycountof(  rcd.providerTime  )  );

	rcd.id  =  m_var.knowledge.id;
	safeStrnCpy(  m_var.knowledge.firstTime,  rcd.firstTime,  sizeof(  rcd.firstTime  )  );
	safeStrnCpy(  m_var.knowledge.lastTime,  rcd.lastTime,  sizeof(  rcd.lastTime  )  );
	safeStrnCpy(  m_var.knowledge.auditTime,  rcd.auditTime,  sizeof(  rcd.auditTime  )  );
	rcd.iStatus  =  m_var.knowledge.iStatus;

	getCurTime(  timeBuf  );
	if  (  !bQyTimeValid(  m_var.knowledge.auditTime  )  ||  memcmp(  &rcd,  &m_var.knowledge,  sizeof(  rcd  )  )  )  {
		safeStrnCpy(  timeBuf,  rcd.auditTime,  sizeof(  rcd.auditTime  )  );
		safeStrnCpy(  timeBuf,  rcd.firstTime,  sizeof(  rcd.firstTime  )  );
		safeStrnCpy(  timeBuf,  rcd.lastTime,  sizeof(  rcd.lastTime  )  );
			
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from qyPcRegistryKnowledgeTab where iRootKey=%d and subKey=%s and cfgName=%s"  ),  rcd.iRootKey,  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.subKey  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.cfgName  )  );
		if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcRegistryKnowledgeTab(uiType,iRootKey,subKey,cfgName,suggestedVal,name,des0,company,product,ucbSys,ucbDaemon,ucbUseNet,ucbHardware,commonErr,securityLevel,ucbSpy,ucbAdvertisement,ucbVirus,ucbBackDoor,provider,providerAddr,providerTime,auditTime,firstTime,lastTime,iStatus)"  )
																						_T(  " Values(%d,%d,%s,%s,%s,%s,%s,%s,%s,'%s','%s','%s','%s',%s,%d,'%s','%s','%s','%s',%s,%s,%s,'%s','%s','%s',%d)"  ),
																						CONST_pcCommType_pcRegistryKnowledge,
																						rcd.iRootKey,
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.subKey  ), 
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.cfgName  ), 
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.suggestedVal  ), 
																						//
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  CONST_iDataType_cusName,  rcd.name  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.des0  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.company  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.product  ),  
																						MACRO_ucbStr(  rcd.ucbSys  ),  MACRO_ucbStr(  rcd.ucbDaemon  ),  MACRO_ucbStr(  rcd.ucbUseNet  ),  MACRO_ucbStr(  rcd.ucbHardware  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.commonErr  ),  
																						rcd.securityLevel,  
																						MACRO_ucbStr(  rcd.ucbSpy  ),  MACRO_ucbStr(  rcd.ucbAdvertisement  ),  MACRO_ucbStr(  rcd.ucbVirus  ),  MACRO_ucbStr(  rcd.ucbBackDoor  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.provider  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.providerAddr  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.providerTime  ),  
																						CString(  rcd.auditTime  ),  CString(  rcd.firstTime  ),  CString(  rcd.lastTime  ),  rcd.iStatus  );
			traceLogA(  "sql is %S",  sqlBuf  );
			if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;			
					
			}
		else  {

			  safeStrnCpy(  timeBuf,  rcd.auditTime,  sizeof(  rcd.auditTime  )  );
			  safeStrnCpy(  timeBuf,  rcd.lastTime,  sizeof(  rcd.lastTime  )  );

			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyPcRegistryKnowledgeTab set suggestedVal=%s,name=%s,des0=%s,company=%s,product=%s,ucbSys='%s',ucbDaemon='%s',ucbUseNet='%s',ucbHardware='%s',commonErr=%s,securityLevel=%d,ucbSpy='%s',ucbAdvertisement='%s',ucbVirus='%s',ucbBackDoor='%s',provider=%s,providerAddr=%s,providerTime=%s,auditTime='%s',lastTime='%s',iStatus=%d where iRootKey=%d and subKey=%s and cfgName=%s"  ),
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.suggestedVal  ),
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.name  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.des0  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.company  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.product  ),  
																						MACRO_ucbStr(  rcd.ucbSys  ),  MACRO_ucbStr(  rcd.ucbDaemon  ),  MACRO_ucbStr(  rcd.ucbUseNet  ),  MACRO_ucbStr(  rcd.ucbHardware  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.commonErr  ),  
																						rcd.securityLevel,
																						MACRO_ucbStr(  rcd.ucbSpy  ),  MACRO_ucbStr(  rcd.ucbAdvertisement  ),  MACRO_ucbStr(  rcd.ucbVirus  ),  MACRO_ucbStr(  rcd.ucbBackDoor  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.provider  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.providerAddr  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.providerTime  ),  
																						CString(  rcd.auditTime  ),  CString(  rcd.lastTime  ),  rcd.iStatus,  
																						rcd.iRootKey,  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.subKey  ),
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.cfgName  )  );
			traceLogA(  "sql is %S",  sqlBuf  );
			if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;			

		}

		

	}

errLabel:
	
	CDialog::OnOK();
}


