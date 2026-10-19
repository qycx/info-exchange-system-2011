// DlgCfgModuleKnowlege.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgModuleKnowlege.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgModuleKnowlege dialog


CDlgCfgModuleKnowlege::CDlgCfgModuleKnowlege(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgModuleKnowlege::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgModuleKnowlege)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgCfgModuleKnowlege::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  fileName,  LPCTSTR  cmdLine,  int  id  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
 
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;
	 if  (  fileName  )  lstrcpyn(  m_var.fileName,  fileName,  mycountof(  m_var.fileName  )  );
	 tTrim(  m_var.fileName  );
	 if  (  cmdLine  )  lstrcpyn(  m_var.cmdLine,  cmdLine,  mycountof(  m_var.cmdLine  )  );
	 tTrim(  m_var.cmdLine  );

	 if  (  !bGetPcModuleKnowledgeBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.fileName,  m_var.cmdLine,  id,  &m_var.moduleKnowlege  )  )  {
		 memset(  &m_var.moduleKnowlege,  0,  sizeof(  m_var.moduleKnowlege  )  );
		 if  (  m_var.fileName[0]  )  lstrcpyn(  m_var.moduleKnowlege.fileName,  m_var.fileName,  mycountof(  m_var.moduleKnowlege.fileName  )  );
		 if  (  m_var.cmdLine[0]  )  lstrcpyn(  m_var.moduleKnowlege.cmdLine,  m_var.cmdLine,  mycountof(  m_var.moduleKnowlege.cmdLine  )  );
		}
	 else  if  (  !fileName  )  {	//  表明是用ID的
			   lstrcpyn(  m_var.fileName,  m_var.moduleKnowlege.fileName,  mycountof(  m_var.fileName  )  );
			   lstrcpyn(  m_var.cmdLine,  m_var.moduleKnowlege.cmdLine,  mycountof(  m_var.cmdLine  )  );
	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


void CDlgCfgModuleKnowlege::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgModuleKnowlege)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgModuleKnowlege, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgModuleKnowlege)
	ON_BN_CLICKED(IDC_CHECK_bCmdLineGiven, OnCHECKbCmdLineGiven)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgModuleKnowlege message handlers

BOOL CDlgCfgModuleKnowlege::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );
	char			displayBuf[256];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	if  (  m_var.moduleKnowlege.fileName[0]  )  {
		GetDlgItem(  IDC_EDIT_fileName  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_EDIT_cmdLine  )->ShowWindow(  SW_HIDE  );
		SetDlgItemText(  IDC_STATIC_fileName,  m_var.moduleKnowlege.fileName  );
		SetDlgItemText(  IDC_STATIC_cmdLine,  m_var.cmdLine  );
		if  (  m_var.moduleKnowlege.cmdLine[0]  )  GetDlgItem(  IDC_CHECK_bCmdLineGiven  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
		
		}
	else  {
		  GetDlgItem(  IDC_STATIC_fileName  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_STATIC_cmdLine  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_CHECK_bCmdLineGiven  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	}


	SetDlgItemText(  IDC_EDIT_name,  m_var.moduleKnowlege.name  );
	SetDlgItemText(  IDC_EDIT_des0,  m_var.moduleKnowlege.des0  );
	SetDlgItemText(  IDC_EDIT_company,  m_var.moduleKnowlege.company  );
	SetDlgItemText(  IDC_EDIT_product,  m_var.moduleKnowlege.product  );
	GetDlgItem(  IDC_CHECK_ucbSys  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbSys  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbDaemon  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbDaemon  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbUseNet  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbUseNet    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbHardware  )->SendMessage(  BM_SETCHECK,  	m_var.moduleKnowlege.ucbHardware    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_commonErr,  m_var.moduleKnowlege.commonErr  );
	SetDlgItemText(  IDC_EDIT_memInfo,  m_var.moduleKnowlege.memInfo  );
	SetDlgItemInt(  IDC_EDIT_securityLevel,  m_var.moduleKnowlege.securityLevel  );
	GetDlgItem(  IDC_CHECK_ucbSpy  )->SendMessage(  BM_SETCHECK,  	m_var.moduleKnowlege.ucbSpy  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbAdvertisement    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbVirus  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbVirus  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbBackDoor  )->SendMessage(  BM_SETCHECK,  	m_var.moduleKnowlege.ucbBackDoor   ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_providerName,  m_var.moduleKnowlege.provider  );
	SetDlgItemText(  IDC_EDIT_providerAddr,  m_var.moduleKnowlege.providerAddr  );
	SetDlgItemText(  IDC_EDIT_providerTime,  m_var.moduleKnowlege.providerTime  );
	SetDlgItemText(  IDC_STATIC_auditTime,  CString(  qyDisplayTime(  m_var.moduleKnowlege.auditTime,  displayBuf,  sizeof(  displayBuf  )  )  )  );


	//  2008/04/05
	GetDlgItem(  IDC_EDIT_cmdLine  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_CHECK_bCmdLineGiven  )->ShowWindow(  SW_HIDE  );



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgCfgModuleKnowlege::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC						*	pQyMc	=	QY_GET_GBUF(  );
	QY_PCMODULEKNOWLEDGE_RCD		rcd;
	TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1];
	char							timeBuf[CONST_qyTimeLen  +  1];
	int								iDbType	=	m_var.pObjDb->cfg.iDbType;

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  m_var.moduleKnowlege.fileName[0]  )  {
		lstrcpyn(  rcd.fileName,  m_var.moduleKnowlege.fileName,  mycountof(  rcd.fileName  )  );
		if  (  GetDlgItem(  IDC_CHECK_bCmdLineGiven  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  ) GetDlgItemText(  IDC_STATIC_cmdLine,  rcd.cmdLine,  mycountof(  rcd.cmdLine  )  );
		}
	else  {
		  GetDlgItemText(  IDC_EDIT_fileName,  rcd.fileName,  mycountof(  rcd.fileName  )  );
		  GetDlgItemText(  IDC_EDIT_cmdLine,  rcd.cmdLine,  mycountof(  rcd.cmdLine  )  );
	}
	
    GetDlgItemText(  IDC_EDIT_name,  rcd.name,  mycountof(  rcd.name  )  );
	GetDlgItemText(  IDC_EDIT_des0,  rcd.des0,  mycountof(  rcd.des0  )  );
	GetDlgItemText(  IDC_EDIT_company,  rcd.company,  mycountof(  rcd.company  )  );
	GetDlgItemText(  IDC_EDIT_product,  rcd.product,  mycountof(  rcd.product  )  );
	rcd.ucbSys  =  GetDlgItem(  IDC_CHECK_ucbSys  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbDaemon  =  GetDlgItem(  IDC_CHECK_ucbDaemon  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbUseNet  =  GetDlgItem(  IDC_CHECK_ucbUseNet  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbHardware  =  GetDlgItem(  IDC_CHECK_ucbHardware  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	GetDlgItemText(  IDC_EDIT_commonErr,  rcd.commonErr,  mycountof(  rcd.commonErr  )  );
	GetDlgItemText(  IDC_EDIT_memInfo,  rcd.memInfo,  mycountof(  rcd.memInfo  )  );
	rcd.securityLevel  =  GetDlgItemInt(  IDC_EDIT_securityLevel  );
	rcd.ucbSpy  =  GetDlgItem(  IDC_CHECK_ucbSpy  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbAdvertisement  =  GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbVirus  =  GetDlgItem(  IDC_CHECK_ucbVirus  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	rcd.ucbBackDoor  =  GetDlgItem(  IDC_CHECK_ucbBackDoor  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	GetDlgItemText(  IDC_EDIT_providerName,  rcd.provider,  mycountof(  rcd.provider  )  );
	GetDlgItemText(  IDC_EDIT_providerAddr,  rcd.providerAddr,  mycountof(  rcd.providerAddr  )  );
	GetDlgItemText(  IDC_EDIT_providerTime,  rcd.providerTime,  mycountof(  rcd.providerTime  )  );

	rcd.id  =  m_var.moduleKnowlege.id;
	safeStrnCpy(  m_var.moduleKnowlege.firstTime,  rcd.firstTime,  sizeof(  rcd.firstTime  )  );
	safeStrnCpy(  m_var.moduleKnowlege.lastTime,  rcd.lastTime,  sizeof(  rcd.lastTime  )  );
	safeStrnCpy(  m_var.moduleKnowlege.auditTime,  rcd.auditTime,  sizeof(  rcd.auditTime  )  );
	rcd.iStatus  =  m_var.moduleKnowlege.iStatus;

	getCurTime(  timeBuf  );
	if  (  !bQyTimeValid(  m_var.moduleKnowlege.auditTime  )  ||  memcmp(  &rcd,  &m_var.moduleKnowlege,  sizeof(  rcd  )  )  )  {
		safeStrnCpy(  timeBuf,  rcd.auditTime,  sizeof(  rcd.auditTime  )  );
		safeStrnCpy(  timeBuf,  rcd.firstTime,  sizeof(  rcd.firstTime  )  );
		safeStrnCpy(  timeBuf,  rcd.lastTime,  sizeof(  rcd.lastTime  )  );
		
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from qyPcProcessKnowledgeTab where fileName=%s and cmdLine=%s"  ),  getDbValStr(  iDbType,  SQL_WVARCHAR,  rcd.fileName  ),  getDbValStr(  iDbType,  SQL_WVARCHAR,  rcd.cmdLine  )  );
		if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcProcessKnowledgeTab(uiType,fileName,cmdLine,name,des0,company,product,ucbSys,ucbDaemon,ucbUseNet,ucbHardware,commonErr,memInfo,securityLevel,ucbSpy,ucbAdvertisement,ucbVirus,ucbBackDoor,provider,providerAddr,providerTime,auditTime,firstTime,lastTime,iStatus)"  )
																						_T(  " Values(%d,%s,%s,%s,%s,%s,%s,'%s','%s','%s','%s',%s,%s,%d,'%s','%s','%s','%s',%s,%s,%s,'%s','%s','%s',%d)"  ),
																						CONST_pcCommType_pcProcessKnowledge,
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  CONST_iDataType_moduleName,  rcd.fileName  ),  
																						getDbValStr(  iDbType,  CONST_iDataType_cmdLine,  rcd.cmdLine  ),
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  CONST_iDataType_cusName,  rcd.name  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.des0  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.company  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.product  ),  
																						MACRO_ucbStr(  rcd.ucbSys  ),  MACRO_ucbStr(  rcd.ucbDaemon  ),  MACRO_ucbStr(  rcd.ucbUseNet  ),  MACRO_ucbStr(  rcd.ucbHardware  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.commonErr  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.memInfo  ),  
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

			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyPcProcessKnowledgeTab set name=%s,des0=%s,company=%s,product=%s,ucbSys='%s',ucbDaemon='%s',ucbUseNet='%s',ucbHardware='%s',commonErr=%s,memInfo=%s,securityLevel=%d,ucbSpy='%s',ucbAdvertisement='%s',ucbVirus='%s',ucbBackDoor='%s',provider=%s,providerAddr=%s,providerTime=%s,auditTime='%s',lastTime='%s',iStatus=%d where fileName=%s and cmdLine=%s"  ),
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.name  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.des0  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.company  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.product  ),  
																						MACRO_ucbStr(  rcd.ucbSys  ),  MACRO_ucbStr(  rcd.ucbDaemon  ),  MACRO_ucbStr(  rcd.ucbUseNet  ),  MACRO_ucbStr(  rcd.ucbHardware  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.commonErr  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.memInfo  ),  
																						rcd.securityLevel,
																						MACRO_ucbStr(  rcd.ucbSpy  ),  MACRO_ucbStr(  rcd.ucbAdvertisement  ),  MACRO_ucbStr(  rcd.ucbVirus  ),  MACRO_ucbStr(  rcd.ucbBackDoor  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.provider  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.providerAddr  ),  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.providerTime  ),  
																						CString(  rcd.auditTime  ),  CString(  rcd.lastTime  ),  rcd.iStatus,  
																						getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.fileName  ),
																						getDbValStr(  iDbType,  CONST_iDataType_cmdLine,  rcd.cmdLine  )
																						);
			traceLogA(  "sql is %S",  sqlBuf  );
			if  (  !bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;			

		}

	}

errLabel:
	
	CDialog::OnOK();
}

void CDlgCfgModuleKnowlege::OnCHECKbCmdLineGiven() 
{
	// TODO: Add your control notification handler code here
	if  (  GetDlgItem(  IDC_CHECK_bCmdLineGiven  )->SendMessage(  BM_GETCHECK,  0,  0  )  !=  BST_CHECKED  )  {
	    SetDlgItemText(  IDC_EDIT_cmdLine,  _T(  ""  )  );
	}

	
}
