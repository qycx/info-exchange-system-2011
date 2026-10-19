// DlgCfgGsmModem.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qymc.h"
#include	"DlgCfgGsmModem.h"
#include	".\dlgcfggsmmodem.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgGsmModem dialog


CDlgCfgGsmModem::CDlgCfgGsmModem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgGsmModem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgGsmModem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgCfgGsmModem::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  unsigned  char  ucbDefaultSmServer,  int  id  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
 
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 if  (  misServName  )  lstrcpyn(  m_var.misServName,  misServName,  mycountof(  m_var.misServName  )  );
	 if  (  pIdInfo  )  m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;
	 safeWcsnCpy(  wDevIdStr,  m_var.wDevIdStr,  mycountof(  m_var.wDevIdStr  )  );
	 m_var.ucbDefaultSmServer  =  ucbDefaultSmServer;
	 m_var.id  =  id;
	 //

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


void CDlgCfgGsmModem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgGsmModem)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgGsmModem, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgGsmModem)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgGsmModem message handlers

BOOL CDlgCfgGsmModem::OnInitDialog()
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	// TODO:  在此添加额外的初始化
	QY_VDEVCOM_RCD		rcd;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	//
	memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !bGetQyVDevComRcdBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.misServName,  &m_var.idInfo,  m_var.wDevIdStr,  0,  &rcd  )  )  memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !bGetQySmContactRcdBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.misServName,  &m_var.idInfo,  m_var.wDevIdStr,  m_var.ucbDefaultSmServer,  0,  &m_var.smContact  )  )  memset(  &m_var.smContact,  0,  sizeof(  m_var.smContact  )  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.idInfo.ui64Id  );
	SetDlgItemText(  IDC_STATIC_idStr_vDevVal,  tBuf  );
	SetDlgItemText(  IDC_STATIC_wDevIdStrVal,  m_var.wDevIdStr  );
	SetDlgItemText(  IDC_STATIC_nameVal,  rcd.name  );
	if  (  m_var.ucbDefaultSmServer  )  GetDlgItem(  IDC_CHECK_ucbDefaultSmServer  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );

	SetDlgItemText(  IDC_EDIT_cusName,  m_var.smContact.cusName  );
	
	if  (  m_var.smContact.ucbPublic  )  GetDlgItem(  IDC_CHECK_ucbPublic  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	
	if  (  !m_var.ucbDefaultSmServer  )  {
	
		if  (  m_var.smContact.ucbDefault  ||  !m_var.wDevIdStr[0]  )  GetDlgItem(  IDC_CHECK_ucbDefault  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );

		if  (  m_var.smContact.idInfo_contact.ui64Id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.smContact.idInfo_contact.ui64Id  );
			SetDlgItemText(  IDC_EDIT_idStr_contact,  tBuf  );
		}

		SetDlgItemText(  IDC_EDIT_displayName,  m_var.smContact.displayName  );
	}

	if  (  m_var.ucbDefaultSmServer  )  {
		GetDlgItem(  IDC_EDIT_idStr_contact  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_displayName  )->EnableWindow(  FALSE  );
	}

	//  
	if  (  !m_var.smContact.id  )  {
		GetDlgItem(  IDC_CHECK_ucbPublic  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	}		

	GetDlgItem(  IDC_CHECK_ucbDefaultSmServer  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbDefault  )->EnableWindow(  FALSE  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgCfgGsmModem::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	QY_MC			*	pQyMc											=	QY_GET_GBUF(  );
	TCHAR				tBuf[255  +  1];
	char				buf[255  +  1];
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]				=	_T(  ""  );
	char				timeBuf[CONST_qyTimeLen  +  1]					=	"";
	int					iDbType											=	m_var.pObjDb->cfg.iDbType;
	char				idStr[CONST_qyMessengerIdStrLen  +  1]			=	"";
	char				idStr_contact[CONST_qyMessengerIdStrLen  +  1]	=	"";
	QY_SMCONTACT_RCD	rcd;
	int					idc;

	memset(  &rcd,  0,  sizeof(  rcd  )  );

	getCurTime(  timeBuf  );

	if  (  GetDlgItem(  IDC_CHECK_ucbDefaultSmServer  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  rcd.ucbDefaultSmServer  =  TRUE;
	
	GetDlgItemText(  IDC_EDIT_cusName,  rcd.cusName,  mycountof(  rcd.cusName  )  );
	tTrim(  rcd.cusName  );
	
	if  (  GetDlgItem(  IDC_CHECK_ucbPublic  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  rcd.ucbPublic  =  TRUE;
	
	if  (  !m_var.ucbDefaultSmServer  )  {

		if  (  GetDlgItem(  IDC_CHECK_ucbDefault  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  rcd.ucbDefault  =  TRUE;

		idc  =  IDC_EDIT_idStr_contact;
		GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
		tTrim(  tBuf  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
		if  (  !idStr2Info(  buf,  &rcd.idInfo_contact  )  ||  !rcd.idInfo_contact.ui64Id  )  {
			qyShowHint(  _T(  "Messenger ID %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotBeEmpty  )  );  GetDlgItem(  idc  )->SetFocus(  );
			return;
		}

		GetDlgItemText(  IDC_EDIT_displayName,  rcd.displayName,  mycountof(  rcd.displayName  )  );
		tTrim(  rcd.displayName  );
	}

	idInfo2Str(  &m_var.idInfo,  idStr,  mycountof(  idStr  )  );
	idInfo2Str(  &rcd.idInfo_contact,  idStr_contact,  mycountof(  idStr_contact  )  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from %s where misServName=%s and idStr='%s' and wDevIdStr=%s and ucbDefaultSmServer='%s'"  ),  CONST_tabName_qySmContactTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  CString(  idStr  ),  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  m_var.wDevIdStr  ),  CString(  m_var.ucbDefaultSmServer  ?  "1"  :  ""  )  );
	if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,wDevIdStr,ucbDefaultSmServer,cusName,ucbPublic,ucbDefault,idStr_contact,displayName,ucbImSwitchable,iStatus,startTime,endTime)"  )
													              _T(  "values(%s,'%s',%s,'%s',%s,'%s','%s','%s',%s,'%s',%d,'%s','%s')"  ),
																	CONST_tabName_qySmContactTab,  
																	getDbValStr(  iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  
																	CString(  idStr  ),  
																	getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  m_var.wDevIdStr  ),  
																	CString(  rcd.ucbDefaultSmServer  ?  "1"  :  ""  ),
																	getDbValStr(  iDbType,  CONST_iDataType_name,  rcd.cusName  ),
																	CString(  rcd.ucbPublic  ?  "1"  :  ""  ),
																	CString(  rcd.ucbDefault  ?  "1"  :  ""  ),																	
																	CString(  idStr_contact  ),
																	getDbValStr(  iDbType,  CONST_iDataType_name,  rcd.displayName  ),
																	CString(  rcd.ucbImSwitchable  ?  "1"  :  ""  ),
																	rcd.iStatus,
																	CString(  timeBuf  ),
																	CString(  timeBuf  )  );
		bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
		}
	else  {
		  rcd.id  =  m_var.smContact.id;
		  //		 
		  lstrcpyn(  rcd.misServName,  m_var.misServName,  mycountof(  rcd.misServName  )  );
		  rcd.idInfo.ui64Id  =  m_var.idInfo.ui64Id;
		  safeWcsnCpy(  m_var.wDevIdStr,  rcd.wDevIdStr,  mycountof(  rcd.wDevIdStr  )  );
		  //
		  safeStrnCpy(  m_var.smContact.startTime,  rcd.startTime,  mycountof(  rcd.startTime  )  );
		  safeStrnCpy(  m_var.smContact.endTime,  rcd.endTime,  mycountof(  rcd.endTime  )  );
		  //
		  if  (  memcmp(  &m_var.smContact,  &rcd,  sizeof(  m_var.smContact  )  )  )  {
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set cusName=%s,ucbPublic='%s',ucbDefault='%s',idStr_contact='%s',displayName=%s,ucbImSwitchable='%s',iStatus=%d,endTime='%s' where misServName=%s and idStr='%s' and wDevIdStr=%s and ucbDefaultSmServer='%s'"  ),  
				  CONST_tabName_qySmContactTab,
				  getDbValStr(  iDbType,  CONST_iDataType_name,  rcd.cusName  ),
				  CString(  rcd.ucbPublic  ?  "1"  :  ""  ),
				  CString(  rcd.ucbDefault  ?  "1"  :  ""  ),
				  CString(  idStr_contact  ),
				  getDbValStr(  iDbType,  CONST_iDataType_name,  rcd.displayName  ),
				  CString(  rcd.ucbImSwitchable  ?  "1"  :  ""  ),
				  rcd.iStatus,
				  CString(  timeBuf  ),
				  getDbValStr(  iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  CString(  idStr  ),  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  m_var.wDevIdStr  ),  CString(  rcd.ucbDefaultSmServer  ?  "1"  :  ""  )  );
			  bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );				  
		  }		  
	}

	if  (  rcd.ucbDefaultSmServer  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr<>'%s' and ucbDefaultSmServer='1'"  ),  CONST_tabName_qySmContactTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  rcd.misServName  ),  CString(  idStr  )  );
		bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
	}


	OnOK();
}
