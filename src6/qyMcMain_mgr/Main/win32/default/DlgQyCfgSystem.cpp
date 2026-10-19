// DlgQyCfgSystem.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQyCfgSystem.h"
#include ".\dlgqycfgsystem.h"
#include	"qyCusResTemp.h"
#include	"qyPs.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCfgSystem dialog


CDlgQyCfgSystem::CDlgQyCfgSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQyCfgSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQyCfgSystem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQyCfgSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQyCfgSystem)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQyCfgSystem, CDialog)
	//{{AFX_MSG_MAP(CDlgQyCfgSystem)
	ON_CBN_SELCHANGE(IDC_COMBO_ucbDsnless, OnSelchangeCOMBOucbDsnless)
	ON_BN_CLICKED(IDC_BUTTON_browseDir, OnBUTTONbrowseDir)
	ON_CBN_SELCHANGE(IDC_COMBO_dbTypeName, OnSelchangeCOMBOdbTypeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCfgSystem message handlers

BOOL CDlgQyCfgSystem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	QY_OBJ_DB	*	pObj;
	//  TCHAR			tBuf[256];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qySystemIdTable  ),  GetDlgItem(  IDC_COMBO_systemId  )->m_hWnd,  0  );
	bQnmFillCol0FromTable(  CONST_dbTypeTable,  GetDlgItem(  IDC_COMBO_dbTypeName  )->m_hWnd,  0  );
	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  GetDlgItem(  IDC_COMBO_ucbDsnless  )->m_hWnd,  0  );

	// TODO: Add extra initialization here
	if  (  m_var.iDlgType  ==  CONST_qyDlgType_modify  )  {
		if  (  m_var.id  <  mycountof(  pQyMc->procedObjDbs  )  )  {
			pObj  =  &pQyMc->procedObjDbs[m_var.id];
			SetDlgItemText(  IDC_EDIT_systemName,  pObj->cfg.sysName  );
			//  SetDlgItemText(  IDC_COMBO_dbTypeName,  qyGetDesByType1(  CONST_dbTypeTable,  pObj->iDbType  )  );
			GetDlgItem(  IDC_COMBO_systemId  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qySystemIdTable  ),  pObj->cfg.iSystemId  )  );
			GetDlgItem(  IDC_COMBO_dbTypeName  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  CONST_dbTypeTable,  pObj->cfg.iDbType  )  );
			GetDlgItem(  IDC_COMBO_ucbDsnless  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  pObj->cfg.ucbDsnless  )  );
			SetDlgItemText(  IDC_EDIT_dbServIp,  CString(  pObj->cfg.dbServIp  )  );
			SetDlgItemText(  IDC_EDIT_dbName,  CString(  pObj->cfg.dbName  )  );
			SetDlgItemText(  IDC_EDIT_uid,  CString(  pObj->cfg.uid  )  );
			SetDlgItemText(  IDC_EDIT_pwd,  CString(  pObj->cfg.pwd  )  );

			if  (  pObj->cfg.iDbType  ==  CONST_dbType_access  )  GetDlgItem(  IDC_EDIT_dbServIp  )->EnableWindow(  FALSE  );
			if  (  !pObj->cfg.ucbDsnless  )  GetDlgItem(  IDC_BUTTON_browseDir  )->EnableWindow(  FALSE  );

		}
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 void CDlgQyCfgSystem::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	int				i;
	QY_OBJ_DB		obj;
	TCHAR			tBuf[1024];
	int				idc;
	char			buf[256];
	char			regValName[128];
	char			savedConnectStr[1024];
	
	memset(  &obj,  0,  sizeof(  obj  )  );
	idc  =  IDC_EDIT_systemName;
	GetDlgItemText(  idc,  obj.cfg.sysName,  mycountof(  obj.cfg.sysName  )  );
	tTrim(  obj.cfg.sysName  );
	if  (  !obj.cfg.sysName[0]  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotEmpty  )  );  GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	//
	idc  =  IDC_COMBO_systemId;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	obj.cfg.iSystemId  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qySystemIdTable  ),  tBuf  );
	if  (  obj.cfg.iSystemId  <  0  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_systemTypeErr  )  );  GetDlgItem(  idc )->SetFocus(  );
		return;
	}
	//
	idc  =  IDC_COMBO_dbTypeName;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	obj.cfg.iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  tBuf  );
	if  (  obj.cfg.iDbType  <  0  )  {
		qyShowHint(  _T(  "dbType error"  )  );  GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_COMBO_ucbDsnless;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	obj.cfg.ucbDsnless  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  tBuf  );
	//
	idc  =  IDC_EDIT_dbServIp;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	myTChar2Str(  tBuf,  obj.cfg.dbServIp,  mycountof(  obj.cfg.dbServIp  )  );
	//
	idc  =  IDC_EDIT_dbName;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	myTChar2WChar(  tBuf,  obj.cfg.dbName,  mycountof(  obj.cfg.dbName  )  );
	//
	idc  =  IDC_EDIT_uid;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	myTChar2WChar(  tBuf,  obj.cfg.uid,  mycountof(  obj.cfg.uid  )  );
	//
	idc  =  IDC_EDIT_pwd;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	myTChar2WChar(  tBuf,  obj.cfg.pwd,  mycountof(  obj.cfg.pwd  )  );
	
	for  (  i  =  0;  (  unsigned  int  )i  <  mycountof(  pQyMc->procedObjDbs  );  i  ++  )  {
		 if  (  !pQyMc->procedObjDbs[i].ucbUsed  )  continue;
		 if  (  m_var.iDlgType  ==  CONST_qyDlgType_modify  &&  i  ==  m_var.id  )  continue;
		 if  (  !lstrcmpi(  obj.cfg.sysName,  pQyMc->procedObjDbs[i].cfg.sysName  )  )  break;
	}
	if  (  (  unsigned  int  )i  <  mycountof(  pQyMc->procedObjDbs  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_systemNameExisted  )  );  return;
	}

	int		id;

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {

		for  (  i  =  0;  (  unsigned  int  )i  <  mycountof(  pQyMc->procedObjDbs  );  i  ++  )  {
			 if  (  !pQyMc->procedObjDbs[i].ucbUsed  )  break;
		}
		if  (  (  unsigned  int  )i  ==  mycountof(  pQyMc->procedObjDbs  )  )  {
			//	qyShowHint(  _T(  "最多只能有%d个系统可以设置, 无法添加新对象"  ),  mycountof(  pQyMc->procedObjDbs  )  );  return;
			qyShowHint(  _T(  "%s, %s :%d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_addSystemErr  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_maximumNumberOfObject  ),  mycountof(  pQyMc->procedObjDbs  )  );  return;
		}
		id  =  i;
		}
	else  {
		  id  =  m_var.id;
	}

	traceLogA(  "这里先做一些固定的设置，比如把netMc系统的数据库的连接方式都限制为dsn模式。等有空了，再改。可以增加一个是否选择DSN的控件，并且能浏览MDB的控件"  );

	myTChar2Str(  qyGetDesByType1(  CONST_dbTypeTable,  obj.cfg.iDbType  ),  buf,  mycountof(  buf  )  );
	if  (  constructDbConnectStr(  obj.cfg.iDbType,  obj.cfg.iDbConnType,  obj.cfg.ucbDsnless,  obj.cfg.dbServIp,  obj.cfg.dbName,  obj.cfg.uid,  obj.cfg.pwd,  obj.cfg.connectStr,  mycountof(  obj.cfg.connectStr  )  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_systemCfgErr  )  );  return;
	}
	myWChar2TChar(  obj.cfg.connectStr,  tBuf,  mycountof(  tBuf  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s=%s;%s=%s;%s=%d;"  ),  tBuf,  CString(  CONST_qyCfgName_dbType  ),  qyGetDesByType1(  CONST_dbTypeTable,  obj.cfg.iDbType  ),  CString(  CONST_qyCfgName_sysName  ),  obj.cfg.sysName,  CString(  CONST_qyCfgName_systemId  ),  obj.cfg.iSystemId  );
	savedConnectStr[0]  =  0;
	myTChar2Utf8(  tBuf,  savedConnectStr,  mycountof(  savedConnectStr  )  );

	QY_REG	reg;
	memset(  &reg,  0,  sizeof(  reg  )  );	
	//  if  (  safeStrCpy(   pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
	lstrcpyn(  reg.rootKey,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	reg.pEncCtx  =  &pQyMc->encCtx;

	_snprintf(  regValName,  mycountof(  regValName  ),  "%s%d",  CONST_regValName_procedSysStr,  id  );
	qySetRegDataEx(  &reg,  CString(  regValName  ),  savedConnectStr,  strlen(  savedConnectStr  )  );
	
	obj.iDsnIndex  =  id;

	memcpy(  &m_var.obj,  &obj,  sizeof(  m_var.obj  )  );

	m_var.ucbChanged  =  TRUE;

errLabel:

	CDialog::OnOK();
}






void CDlgQyCfgSystem::OnSelchangeCOMBOucbDsnless() 
{
	// TODO: Add your control notification handler code here
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	unsigned  char	ucbDsnless	=	FALSE;
	TCHAR			tBuf[128];
	int				idc			=	IDC_COMBO_ucbDsnless;


	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	ucbDsnless  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  tBuf  );

	GetDlgItem(  IDC_BUTTON_browseDir  )->EnableWindow(  ucbDsnless  ?  TRUE  :  FALSE  );

	
}



void CDlgQyCfgSystem::OnBUTTONbrowseDir() 
{
	QY_MC	  * pQyMc		=	QY_GET_GBUF(  );
	CString		path;
	CQyString	pathStr;
	int			idc			=  IDC_EDIT_dbName;
	LPCTSTR		lpszFilter  =  getResStr(  0, &pQyMc->cusRes,  CONST_resId_databaseformat  );


	GetDlgItemText(  idc,  path  );
	if  (  qyBrowseForFile(  m_hWnd,  TRUE,  _T(  "mdb"  ),  OFN_FILEMUSTEXIST,  lpszFilter,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectDbFile  ),  NULL,  pathStr  )  )  return;
	
	SetDlgItemText(  idc,  pathStr.GetBuffer(  0  )  );
	
}

void CDlgQyCfgSystem::OnSelchangeCOMBOdbTypeName() 
{
	// TODO: Add your control notification handler code here
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	int				iDbType		=	0;
	TCHAR			tBuf[128];
	int				idc			=	IDC_COMBO_dbTypeName;


	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  tBuf  );

	if  (  iDbType  !=  CONST_dbType_access  )  {
		(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_ucbDsnless  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  TRUE  )  );
		GetDlgItem(  IDC_COMBO_ucbDsnless  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_dbServIp  )->EnableWindow(  TRUE  );
		GetDlgItem(  IDC_BUTTON_browseDir  )->EnableWindow(  FALSE  );
		goto  errLabel;
	}

	// TODO: Add your control notification handler code here
	unsigned  char	ucbDsnless	=	FALSE;
	idc			=	IDC_COMBO_ucbDsnless;
	//
	GetDlgItem(  idc  )->EnableWindow(  TRUE  );
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  tTrim(  tBuf  );
	ucbDsnless  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ucbDsnlessTable  ),  tBuf  );
	//
	GetDlgItem(  IDC_BUTTON_browseDir  )->EnableWindow(  ucbDsnless  ?  TRUE  :  FALSE  );

	GetDlgItem(  IDC_EDIT_dbServIp  )->EnableWindow(  FALSE  );


errLabel:
	return;
	
}
