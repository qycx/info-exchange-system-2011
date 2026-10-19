// DlgMessenger.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgMessenger.h"
#include	"qyCusResTemp.h"

#include	"myDb.h"			//  2013/02/19

// CDlgMessenger dialog

IMPLEMENT_DYNAMIC(CDlgMessenger, CDialog)

CDlgMessenger::CDlgMessenger(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMessenger::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMessenger::~CDlgMessenger()
{
}

BOOL  CDlgMessenger::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{  
	if  (  !pObjDb  ||  !misServName  ||  !pIdInfo  )  return  FALSE;

	m_var.iDlgType  =  iDlgType; 
	m_var.pObjDb  =  pObjDb;  
	lstrcpyn(  m_var.misServName,  misServName,  mycountof(  m_var.misServName  )  );  
	m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;

	return  TRUE;
}

void CDlgMessenger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMessenger, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgMessenger::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMessenger message handlers


BOOL CDlgMessenger::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int					iErr				=	-1;
	QY_MC	*			pQyMc				=	QY_GET_GBUF(  );
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );


	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
		SetDlgItemText(  IDC_STATIC_hint1,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_newMessenger  )  );
		}	
	else  {
		  SetDlgItemText(  IDC_STATIC_hint1,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_renameMessenger  )  );

#if  10
		  if  (  !g_dbFuncs.pf_bGetImAmRcdBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.misServName,  &m_var.idInfo,  NULL,  0,  &m_var.rcd  )  )  {
			   memset(  &m_var.rcd,  0,  sizeof(  m_var.rcd  )  );
			   lstrcpyn(  m_var.rcd.misServName,  m_var.misServName,  mycountof(  m_var.rcd.misServName  )  );
			   m_var.rcd.idInfo.ui64Id  =  m_var.idInfo.ui64Id;		   
		  }

		  SetDlgItemText(  IDC_EDIT_name,  m_var.rcd.messengerName  );

		  GetDlgItem(  IDC_EDIT_name  )->EnableWindow(  FALSE  );
#endif
		  
	}

	GetDlgItem(  IDC_EDIT_name  )->SendMessage(  EM_SETLIMITTEXT,  MAX_messengerNameLen,  0  );
	GetDlgItem(  IDC_EDIT_passwd0  )->SendMessage(  EM_SETLIMITTEXT,  MAX_messengerPasswdLen,  0  );
	GetDlgItem(  IDC_EDIT_passwd1  )->SendMessage(  EM_SETLIMITTEXT,  MAX_messengerPasswdLen,  0  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



 int  getRndStr(  char  *  buf,  unsigned  int  size  )
{
	char  *  cs  =  "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int		len	=	strlen(  cs  );
	int		i;
	unsigned  int		j;
	
	if  (  !size  )  return  -1;

	for  (  i  =  0;  i  <  size  -  1;  i  ++  )  {
		 j  =  (  unsigned  int  )rand(  );
		 j  =  j  %  len;
		 buf[i]  =  cs[j];
	}
	buf[i]  =  0;

	return  0;
}

void CDlgMessenger::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int						iErr									=	-1;
	QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	CString					nameStr;
	static  BOOL			bFirstPrompted							=	FALSE;
	CString					passwd0,  passwd1;
	int						idc;


	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	idc  =  IDC_EDIT_name;
	GetDlgItemText(  idc,  nameStr  );
	MACRO_CStringTrim(  nameStr  );
	if  (  !nameStr.GetLength(  )  )  {
		myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_messengerNameCannotEmpty  ),  _T(  ""  ),  MB_OK  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_EDIT_passwd0;
	GetDlgItemText(  idc,  passwd0  );
	MACRO_CStringTrim(  passwd0  );
	if  (  !passwd0.GetLength(  )  )  {
		myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwdCannotEmpty  ),  _T(  ""  ),  MB_OK  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_EDIT_passwd1;
	GetDlgItemText(  idc,  passwd1  );
	MACRO_CStringTrim(  passwd1  );
	if  (  !passwd1.GetLength(  )  )  {
		myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwdCannotEmpty  ),  _T(  ""  ),  MB_OK  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_EDIT_passwd0;
	if  (  passwd0  !=  passwd1  )  {
		myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwdNotConfirmed  ),  _T(  ""  ),  MB_OK  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	QY_MESSENGER_ID				lastIdInfo;
	memset(  &lastIdInfo,  0,  sizeof(  lastIdInfo  )  );

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
		idc  =  IDC_EDIT_name;
		if  (  g_dbFuncs.pf_bGetImAmRcdBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  NULL,  nameStr,  0,  NULL  )  )  {
			myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_nameExists  ),  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );
			return;
		}

		QY_MESSENGERAUTHTMP_RCD		rcd;

		memset(  &rcd,  0,  sizeof(  rcd  )  );
		rcd.uiType  =  CONST_objType_messenger;
		if  (  g_dbFuncs.pf_auditNewMessenger(  NULL,  &lastIdInfo,  &pQyMc->licenseCtx,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  NULL,  &rcd  )  )  {
			qyShowHint(  _T(  "Create new messenger failed"  )  );
			return;
		}
	}

	QY_imAm_RCD					imAm;
	TCHAR	sqlBuf[CONST_maxSqlBufLen  +  1];
	int		iDbType	=	pQyMc->cfg.db.iDbType;
	char	idStr[CONST_qyMessengerIdStrLen  +  1];
	memset(  &imAm,  0,  sizeof(  imAm  )  );

	char	buf[256]		=	"";
	char	passwd_enc[256]	=	"";
	CQyString	str;

	unsigned  int	len;
	if  (  !myTChar2Utf8(  passwd0,  buf,  mycountof(  buf  )  )  )  goto  errLabel;
	len  =  mycountof(  passwd_enc  );
	if  (  !bQyGetStrMd5_x(  buf,  passwd_enc,  &len  )  )  goto  errLabel;	

	lstrcpyn(  imAm.messengerName,  nameStr,  mycountof(  imAm.messengerName  )  );
	imAm.iPasswdType  =  CONST_passwdType_md5;
	getRndStr(  imAm.salt,  mycountof(  imAm.salt  )  );
	str  =  CQyString(  ""  )  +  CQyString(  imAm.messengerName  )  +  CQyString(  imAm.salt  );
	len  =  strlen(  passwd_enc  );
	if  (  !myTChar2Utf8(  str,  passwd_enc  +  len,  mycountof(  passwd_enc  )  -  len  )  )  goto  errLabel;
	len  =  mycountof(  imAm.messengerPasswd  );
	if  (  !bQyGetStrMd5_x(  passwd_enc,  imAm.messengerPasswd,  &len  )  )  goto  errLabel;
	getCurTime(  imAm.tLastModifiedTime  );

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
		idInfo2Str(  &lastIdInfo,  idStr,  mycountof(  idStr  )  );
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T( "insert into %s(misServName,idStr,messengerName,messengerPasswd,iPasswdType,salt,tLastModifiedTime)"  )
													_T(  " Values(%s,'%s',%s,'%s',%d,'%s','%s')"  ),
													CONST_tabName_qyImAmTab,
													getDbValStr(  iDbType,  CONST_iDataType_misServName,  imAm.misServName  ),
													CString(  idStr  ),
													getDbValStr(  iDbType,  CONST_iDataType_name,  imAm.messengerName  ),
													CString(  imAm.messengerPasswd  ),
													imAm.iPasswdType,
													CString(  imAm.salt  ),
													CString(  imAm.tLastModifiedTime  )  );
		if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlBuf  )  )  {
			qyShowHint(  _T(  "Create new messenger failed"  )  );
			return;
		}													
		}
	else  {
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set messengerPasswd='%s',iPasswdType=%d,salt='%s',tLastModifiedTime='%s' where id=%d"  ),
															CONST_tabName_qyImAmTab,
															CString(  imAm.messengerPasswd  ),  
															imAm.iPasswdType,
															CString(  imAm.salt  ),
															CString(  imAm.tLastModifiedTime  ),
															m_var.rcd.id  );
		  if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlBuf  )  )  {
			  qyShowHint(  _T(  "Set password failed"  )  );
			  return;
		  }
	}													

	iErr  =  0;

errLabel:

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
		TCHAR	tBuf[256]	=	_T(  ""  );
		if  (  !iErr  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sameMessenger  )  );
		}
		SetDlgItemText(  IDC_STATIC_hint1,  tBuf  );
		SetDlgItemText(  IDC_EDIT_name,  _T(  ""  )  );
		SetDlgItemText(  IDC_EDIT_passwd0,  _T(  ""  )  );
		SetDlgItemText(  IDC_EDIT_passwd1,  _T(  ""  )  );
		idc  =  IDC_EDIT_name;
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	OnOK();
}
