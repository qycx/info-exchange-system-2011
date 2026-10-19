// DlgWwwQmContact.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgWwwQmContact.h"
#include	".\dlgwwwqmcontact.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWwwQmContact dialog


CDlgWwwQmContact::CDlgWwwQmContact(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWwwQmContact::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWwwQmContact)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgWwwQmContact::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  id  )
{
	 BOOL						bRet	=	FALSE;
	 QY_MC					*	pQyMc	=	QY_GET_GBUF(  );

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 m_var.pObjDb  =  pObjDb;	//  2007/01/02

	 if  (  misServName  &&  pIdInfo  )  {
		 
		 lstrcpyn(  m_var.misServName,  misServName,  mycountof(  m_var.misServName  )  );
		 m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;

		 if  (  !bGetWebContactRcdBySth(  m_var.pObjDb->pDb,  pObjDb->cfg.iDbType,  misServName,  pIdInfo,  0,  &m_var.oldWebContact  )  )  memset(  &m_var.oldWebContact,  0,  sizeof(  m_var.oldWebContact  )  );

		}
	 else  {
		   m_var.id  =  id;
		 
		   if  (  !bGetWebContactRcdBySth(  m_var.pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  id,  &m_var.oldWebContact  )  )  goto  errLabel;
		   
	 }

	 bRet	=	TRUE;
errLabel:
	 return  bRet;
}


void CDlgWwwQmContact::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWwwQmContact)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWwwQmContact, CDialog)
	//{{AFX_MSG_MAP(CDlgWwwQmContact)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWwwQmContact message handlers

BOOL CDlgWwwQmContact::OnInitDialog()
{
	CDialog::OnInitDialog();
	QY_MC					*	pQyMc										=	QY_GET_GBUF(  );
	TCHAR						tBuf[255  +  1];
	TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	// TODO:  在此添加额外的初始化
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.idInfo.ui64Id  );
	SetDlgItemText(  IDC_STATIC_messengerId,  tBuf  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from qyWebContactTab where id=%d"  ),  m_var.oldWebContact.id  );  
	if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {	//  没有记录，则取缺省
		GetDlgItem(  IDC_CHECK_ucbPublic  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );	//  缺省为公开
		SetDlgItemText(  IDC_EDIT_grpDisplayName,  _T(  "Group"  )  );
		}
	else  {
		  if  (  m_var.oldWebContact.ucbPublic  )  GetDlgItem(  IDC_CHECK_ucbPublic  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
		  SetDlgItemText(  IDC_EDIT_grpDisplayName,  m_var.oldWebContact.grpDisplayName  );
		  SetDlgItemText(  IDC_EDIT_displayName,  m_var.oldWebContact.displayName  );
		  if  (  m_var.oldWebContact.ucbImSwitchable  )  GetDlgItem(  IDC_CHECK_ucbImSwitchable  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );

	}

	//  2008/03/02
	GetDlgItem(  IDC_EDIT_wAdvertisement  )->SendMessage(  EM_LIMITTEXT,  mycountof(  m_var.wAdvertisement  ),  0  ); 
	if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_wAdvertisement  ),  (  char  *  )m_var.wAdvertisement,  sizeof(  m_var.wAdvertisement  ),  0  )  )  m_var.wAdvertisement[0]  =  0;
	tTrim(  m_var.wAdvertisement  );
	if  (  !m_var.wAdvertisement[0]  )  _sntprintf(  m_var.wAdvertisement,  mycountof(  m_var.wAdvertisement  ),  _T(  "%s"  ),  DEFAULT_str_wAdvertisement  );
	SetDlgItemText(  IDC_EDIT_wAdvertisement,  CString(  m_var.wAdvertisement  )  );

	//
	GetDlgItem(  IDC_EDIT_grpDisplayName  )->EnableWindow(  FALSE  );

	traceLogA(  ""  );
	GetDlgItem(  IDC_CHECK_ucbImSwitchable  )->ShowWindow(  SW_HIDE  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgWwwQmContact::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	QY_MC				*		pQyMc										=	QY_GET_GBUF(  );
	int							idc;
	TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	memset(  &m_var.webContact,  0,  sizeof(  m_var.webContact  )  );

	if  (  GetDlgItem(  IDC_CHECK_ucbPublic  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  m_var.webContact.ucbPublic  =  TRUE;

	idc  =  IDC_EDIT_grpDisplayName;
	GetDlgItemText(  idc,  m_var.webContact.grpDisplayName,  mycountof(  m_var.webContact.grpDisplayName  )  );
	tTrim(  m_var.webContact.grpDisplayName  );
	if  (  !m_var.webContact.grpDisplayName[0]  )  {
		qyShowHint(  _T(  "%s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  IDC_STATIC_grpDisplayName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotBeEmpty  )  );  GetDlgItem(  idc  )->SetFocus(  );  return;
	}

	idc  =  IDC_EDIT_displayName;
	GetDlgItemText(  idc,  m_var.webContact.displayName,  mycountof(  m_var.webContact.displayName  )  );
	tTrim(  m_var.webContact.displayName  );
	if  (  !m_var.webContact.displayName[0]  )  {
		qyShowHint(  _T(  "%s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  IDC_STATIC_displayName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotBeEmpty  )  );  GetDlgItem(  idc  )->SetFocus(  );  return;
	}
	
	idc  =  IDC_CHECK_ucbImSwitchable;
	if  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  m_var.webContact.ucbImSwitchable  =  TRUE;

	if  (  memcmp(  &m_var.webContact,  &m_var.oldWebContact,  sizeof(  m_var.webContact  )  )  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from qyWebContactTab where id=%d"  ),  m_var.oldWebContact.id  );  
		if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {	//  没有记录，则取缺省
			idInfo2Str(  &m_var.idInfo,  idStr,  mycountof(  idStr  )  );
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyWebContactTab(misServName,idStr,ucbPublic,grpDisplayName,displayName,ucbImSwitchable,iStatus) values(%s,'%s','%s',%s,%s,'%s',0)"  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  CString(  idStr  ),  m_var.webContact.ucbPublic  ?  "1"  :  "",  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  m_var.webContact.grpDisplayName  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  m_var.webContact.displayName  ),  m_var.webContact.ucbImSwitchable  ?  "1"  :  ""  );
			bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
			}
		else  {
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyWebContactTab set ucbPublic='%s',grpDisplayName=%s,displayName=%s,ucbImSwitchable='%s' where id=%d"  ),  m_var.webContact.ucbPublic  ?  "1"  :  "",  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  m_var.webContact.grpDisplayName  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  m_var.webContact.displayName  ),  m_var.webContact.ucbImSwitchable  ?  "1"  :  "",  m_var.oldWebContact.id  );
			  bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
		}

	}

	//  2008/03/02
	GetDlgItemText(  IDC_EDIT_wAdvertisement,  sqlBuf,  mycountof(  sqlBuf  )  );
	tTrim(  sqlBuf  );
	if  (  sqlBuf[0]  )  qySetRegCfgT(  HKEY_LOCAL_MACHINE,  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_wAdvertisement  ),  sqlBuf  );
	else  qyDelRegCfgT(  HKEY_LOCAL_MACHINE,  _T(  CONST_qyRootKey_qnmScheduler_mis  ),  _T(  CONST_regValName_wAdvertisement  )  );


	CDialog::OnOK();

}





void CDlgWwwQmContact::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
