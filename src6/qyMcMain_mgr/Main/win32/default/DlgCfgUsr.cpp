// DlgCfgUsr.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgUsr.h"
#include	"dlgCfgUsrs.h"
#include	"qyMcMainObj.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgUsr dialog
 int  encPasswd(  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );


CDlgCfgUsr::CDlgCfgUsr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgUsr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgUsr)
	m_name = _T("");
	m_passwd0 = _T("");
	m_passwd1 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCfgUsr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgUsr)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PASSWD0, m_passwd0);
	DDX_Text(pDX, IDC_PASSWD1, m_passwd1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgUsr, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgUsr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgUsr message handlers

 BOOL CDlgCfgUsr::bSetDlgInfo(  int  type,  CWnd * pSrcWnd  )
{
	var.type		=  type;
	var.pSrcWnd		=  pSrcWnd;
	return  TRUE;
}



/*
 int  encPasswd(  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 for  (  int  i  =  0;  i  <  (  int  )inputSize;  i  ++  )  {
		  if  (  input[i]  & 0x80  )  output[i]  =  input[i]  &  0x7f;
		  else  output[i]  =  input[i]  +  0x80;
	 }
	 *pOutputSize  =  inputSize;
	 return  0;
}
*/
//	extern  QY_DMITEM  CONST_grpNameTable[];
BOOL CDlgCfgUsr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//  char			buf[256];
	QY_DMITEM	*	pItem	=	NULL;
	CString			str;

	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	CDlgCfgUsrs  *	pParent  =  (  CDlgCfgUsrs  *  )var.pSrcWnd;			
	if  (  !pParent  )  {
		EndDialog(  -1  );  return  FALSE;
	}

	pParent->GetDlgItemText(  IDC_GRPLIST,  str  );  
	for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_grpNameTable  );  pItem->type  !=  -1;  pItem  ++  )  if  (  !lstrcmpi(  pItem->pData,  str  )  )  break;
	if  (  pItem->type  ==  -1  )  {
		EndDialog(  -1  );  return  FALSE;
	}
	myTChar2Str(  pItem->des,  var.curGrpNameBuf,  sizeof(  var.curGrpNameBuf  )  );
	
	if  (  var.type  ==  CONST_qyDlgType_modify  )  {
			char			usrNameBuf[1024];
			QY_USR_RCD		usrInfo;

			str  =  pParent->m_LV.GetItemText(  pParent->var.nItemSelected,  0  );  myTChar2Str(  str,  usrNameBuf,  sizeof(  usrNameBuf  )  );
			if  (  usrNameBuf[0]  )  {
				SetDlgItemText(  IDC_NAME,  CString(  usrNameBuf  ) );	

				if  (  !bGetQyUsrInfoBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  usrNameBuf,  &usrInfo  )  )  memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );

				SetDlgItemText(  IDC_EDIT_zb,  usrInfo.zbStr  );
				SetDlgItemText(  IDC_EDIT_bb,  usrInfo.bbStr  );
				SetDlgItemText(  IDC_EDIT_dw,  usrInfo.dwStr  );
				SetDlgItemText(  IDC_EDIT_bm,  usrInfo.bmStr  );

			}	
		GetDlgItem(  IDC_NAME  )->EnableWindow(  FALSE  );

		GetDlgItem(  IDC_EDIT_zb  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_bb  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_dw  )->EnableWindow(  FALSE  );
		GetDlgItem(  IDC_EDIT_bm  )->EnableWindow(  FALSE  );

		}
	else  if  (  var.type  ==  CONST_qyDlgType_add  )  {

			  if  (  pQyMc->curUsrInfo.scope.zbStr[0]  
				  ||  pQyMc->curUsrInfo.scope.bbStr[0]
					||  pQyMc->curUsrInfo.scope.dwStr[0]
						||  pQyMc->curUsrInfo.scope.bmStr[0]  )						
			  {
				  SetDlgItemText(  IDC_EDIT_zb,  pQyMc->curUsrInfo.scope.zbStr  );
				  SetDlgItemText(  IDC_EDIT_bb,  pQyMc->curUsrInfo.scope.bbStr  );
				  SetDlgItemText(  IDC_EDIT_dw,  pQyMc->curUsrInfo.scope.dwStr  );
				  SetDlgItemText(  IDC_EDIT_bm,  pQyMc->curUsrInfo.scope.bmStr  );

				  GetDlgItem(  IDC_EDIT_zb  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_EDIT_bb  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_EDIT_dw  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_EDIT_bm  )->EnableWindow(  FALSE  );
			  }
	}

	GetDlgItem(  IDC_NAME  )->SendMessage(  EM_SETLIMITTEXT,  16,  0  );
	GetDlgItem(  IDC_PASSWD0  )->SendMessage(  EM_SETLIMITTEXT,  16,  0  );
	GetDlgItem(  IDC_PASSWD1  )->SendMessage(  EM_SETLIMITTEXT,  16,  0  );
	
	GetDlgItem(  IDC_EDIT_zb  )->SendMessage(  EM_SETLIMITTEXT,  64,  0  );
	GetDlgItem(  IDC_EDIT_bb  )->SendMessage(  EM_SETLIMITTEXT,  64,  0  );
	GetDlgItem(  IDC_EDIT_dw  )->SendMessage(  EM_SETLIMITTEXT,  64,  0  );
	GetDlgItem(  IDC_EDIT_bm  )->SendMessage(  EM_SETLIMITTEXT,  64,  0  );


	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_netMc  )  {		//  2008/09/04
		GetDlgItem(  IDC_STATIC_scope  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_zb  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_EDIT_zb  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_bb  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_EDIT_bb  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_dw  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_EDIT_dw  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_bm  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_EDIT_bm  )->ShowWindow(  SW_HIDE  );

	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgUsr::OnOK() 
{
	char			*	p			=	NULL;
	unsigned  char		ucbHaveNum  =  FALSE,  ucbHaveAlpha  =  FALSE;
	char				buf[256];
	char				tmpBuf[256];
	CString				zbStr,  bbStr,  dwStr,  bmStr;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );

	UpdateData(  TRUE );
	
	m_name.TrimLeft(  );  m_name.TrimRight(  );
	if  (  !m_name.GetLength(  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_userEmpty  )  );  return;
	}
	m_passwd0.TrimLeft(  );  m_passwd0.TrimRight(  );
	m_passwd1.TrimLeft(  );  m_passwd1.TrimRight(  );

	//  2005/09/22, 加强密码的长度和强度
	if  (  m_passwd0.GetLength(  )  <  pQyMc->cfg.logon.usMinPasswdLen  )  {
		AfxMessageBox(  CString(  ""  )  +  getResStr(  0, &pQyMc->cusRes,  CONST_resId_passwordLength  )  +  ltoa(  pQyMc->cfg.logon.usMinPasswdLen,  tmpBuf,  10  )  );  return;
	}	
	myTChar2Str(  m_passwd0,  buf,  sizeof(  buf  )  );
	for  (  p  =  buf;  *p;  p  ++  )  {
		 if  (  isdigit(  *p  )  )  ucbHaveNum  =  TRUE;
		 if  (  isalpha(  *p  )  )  ucbHaveAlpha  =  TRUE;
	}
	if  (  !(  ucbHaveNum  &&  ucbHaveAlpha  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwordComposed  )  );  return;
	}

	GetDlgItemText(  IDC_EDIT_zb,  zbStr  );	MACRO_CStringTrim(  zbStr  );
	GetDlgItemText(  IDC_EDIT_bb,  bbStr  );	MACRO_CStringTrim(  bbStr  );
	GetDlgItemText(  IDC_EDIT_dw,  dwStr  );	MACRO_CStringTrim(  dwStr  );
	GetDlgItemText(  IDC_EDIT_bm,  bmStr  );	MACRO_CStringTrim(  bmStr  );



	TCHAR				sqlBuf[2048];
	char				passwdBuf[2048];
	char				passwdXBuf[4096];
	unsigned  int		len;
	TCHAR				logDes[128];



	if  (  var.type  ==  CONST_qyDlgType_add  )  {
		_sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select count(*) from qyUsrTab where name='%s'"  ),  m_name.GetBuffer(  0  )  );
		if  (  bSqlObjExists( pQyMc->gui.pDb, CString(  sqlBuf  )  )  )  {
			_sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select count(*) from qyGrpUsrRelationTab where usrName='%s' and grpName='%s'"  ),  m_name.GetBuffer(  0  ),  CString(  var.curGrpNameBuf  )  );
			if  (  bSqlObjExists(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
				AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_userExisted  )  );  return;
			}
			if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_userBelongToOtherGroup  ),  MB_YESNO  ) !=  IDYES )  return;
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyGrpUsrRelationTab(usrName,grpName) values('%s','%s')"  ),  m_name.GetBuffer(  0  ),  CString(  var.curGrpNameBuf  )  );
			if  ( !bQyExecSql(  pQyMc->gui.pDb, CString(  sqlBuf  ) )  )  return;
			}
		else  {			
			if  (  m_passwd0  !=  m_passwd1  )  {
				AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwordCannotMatch  )  );  return;
			}
			if  (  !m_passwd0.GetLength(  )  )  {
				AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwordEmpty  )  );  return;
			}
			myTChar2Str(  m_passwd0,  tmpBuf,  sizeof(  tmpBuf  )  );
			encPasswd(  tmpBuf,  strlen(  tmpBuf  ),  passwdBuf,  &len  );
			qyBuf2X( passwdBuf,  len,  passwdXBuf  );
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyUsrTab(name,passwd,zbStr,bbStr,dwStr,bmStr) values('%s','%s',%s,%s,%s,%s)"  ),  m_name.GetBuffer(  0  ),  CString(  passwdXBuf  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  zbStr  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  bbStr  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  dwStr  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_name,  bmStr  )  );
			if  ( !bQyExecSql(  pQyMc->gui.pDb, CString(  sqlBuf  )  )  )  {
				AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErr  )  );  return;
			}			
			_sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "insert into qyGrpUsrRelationTab(usrName,grpName) values('%s','%s')"  ),  m_name.GetBuffer(  0  ),  CString(  var.curGrpNameBuf  )  );
			if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
				OutputDebugString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErr  )  );  return;
			}
		}

		//  作操作日志
		_sntprintf(  logDes,  sizeof(  logDes  )  /  sizeof(  logDes[0]  ),  _T(  "%s: %s: %s"  ),  CString(  var.curGrpNameBuf  ),  getResStr(  0,  &pQyMc->cusRes, CONST_resId_addNewUser  ),  m_name.GetBuffer(  0  )  );
		qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_addUsr,  CString(  pQyMc->curUsrInfo.name  ),  CString(  logDes  )  );

		}
	else  {
		
		if  (  m_passwd0  !=  m_passwd1  )  {
			AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwordCannotMatch  )  );  return;
		}
		if  (  !m_passwd0.GetLength(  )  )  {  
			AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwordEmpty  )  );  return;
		}			
		if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwordSaved  ),  MB_YESNO  ) !=  IDYES  )  return;

		char	buf[2048],  xBuf[4096];
		unsigned  int		len;

		myTChar2Str(  m_passwd0,  tmpBuf,  sizeof(  tmpBuf  )  );
		encPasswd(  tmpBuf,  strlen(  tmpBuf  ),  buf,  &len  );
		qyBuf2X(  buf, m_passwd0.GetLength(  ),  xBuf  );
		
		_sntprintf(  sqlBuf, sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "update qyUsrTab set passwd='%s' where name='%s'"  ),  CString(  xBuf  ),  m_name.GetBuffer(  0  )  );
		if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  {
			OutputDebugString(  _T(  "update failed."  )  );				
		}

		//  作操作日志
		_sntprintf(  logDes,  sizeof(  logDes  )  /  sizeof(  logDes[0]  ),  _T(  "User %s : password modified"  ),  m_name.GetBuffer(  0  )  );
		qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_modifyUsr,  CString(  pQyMc->curUsrInfo.name  ),  CString(  logDes  )  );

	}

	var.bChanged  =  TRUE;
	
	CDialog::OnOK();
}
