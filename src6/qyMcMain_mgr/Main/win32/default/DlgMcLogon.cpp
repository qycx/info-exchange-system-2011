// DlgMcLogon.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgMcLogon.h"
#include	"qyMcMainObj.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMcLogon dialog


CDlgMcLogon::CDlgMcLogon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMcLogon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMcLogon)
	m_name = _T("");
	m_passwd = _T("");
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgMcLogon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMcLogon)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PASSWD, m_passwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMcLogon, CDialog)
	//{{AFX_MSG_MAP(CDlgMcLogon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMcLogon message handlers

int		encPasswd(  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  );
extern	QY_MC				 gQyMc;


 int  encPasswd(  char  *  input,  unsigned  int  inputSize,  char  *  output,  unsigned  int  *  pOutputSize  )
{
	 for  (  int  i  =  0;  i  <  (  int  )inputSize;  i  ++  )  {
		  if  (  input[i]  & 0x80  )  output[i]  =  input[i]  &  0x7f;
		  else  output[i]  =  input[i]  +  0x80;
	 }
	 *pOutputSize  =  inputSize;
	 return  0;
}

 void CDlgMcLogon::OnOK() 
{
	int						iErr					=	-1;
	QY_MC			*		pQyMc					=  QY_GET_GBUF(  );
	char					sqlBuf[1024];
	char					passwdEncBuf[4096];
	char					passwdXBuf[4096];
	unsigned  int			len1;
	CDBVariant				varVal[1];
	//  char					tmpBuf[256];
	char					nameBuf[512],  passwdBuf[512];

	UpdateData(  TRUE  );

	m_name.TrimRight(  );  m_name.TrimLeft(  );
	m_passwd.TrimRight(  );  m_passwd.TrimLeft(  );

	//

	m_var.nTries  ++  ;

	if  (  !m_name.GetLength(  )  ||  !m_passwd.GetLength(  )  )  goto  errLabel;
	
	if  (  !myTChar2Str(  m_name,  nameBuf,  sizeof(  nameBuf  )  )  
		||  !myTChar2Str(  m_passwd,  passwdBuf,  sizeof(  passwdBuf  )  )  )
	{
		goto  errLabel;
	}

	encPasswd(  passwdBuf,  strlen(  passwdBuf  ),  passwdEncBuf,  &len1  );
	memset(  passwdXBuf,  0,  sizeof(  passwdXBuf  )  );
	qyBuf2X(  passwdEncBuf,  len1,  passwdXBuf  ); 
	sprintf(  sqlBuf,  "select count(*) from qyUsrTab where name='%s' and passwd='%s'",  nameBuf,  passwdXBuf  );
	if  (  !bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  1,  varVal  )  
		||  varVal[0].m_dwType  !=  DBVT_LONG
			||  !varVal[0].m_lVal  )
	{
		if  (  m_name.Compare(  CString(  CONST_usrName_admin  )  )  
			||  m_passwd.Compare(  CString(  CONST_adminInitialPasswd  )  )  )
		{
			goto  errLabel;
		}

		sprintf(  sqlBuf,  "select count(*) from qyUsrTab where name='%s' and passwd='%s'",  CONST_usrName_admin,  CONST_adminInitialEncXPasswd  );
		if  (  !bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  1,  varVal  )  
			||  varVal[0].m_dwType  !=  DBVT_LONG
				||  !varVal[0].m_lVal  )
		{
			goto  errLabel;
		}
		
	}

	memset(  &pQyMc->curUsrInfo,  0,  sizeof(  pQyMc->curUsrInfo  )  );


	sprintf(  sqlBuf,  "select count(*) from qyGrpUsrRelationTab where usrName='%s' and grpName='%s'",  nameBuf,  CONST_grpName_admin  );
	if  (  bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  1,  varVal  )  
			&&  varVal[0].m_dwType  ==  DBVT_LONG
				&&  varVal[0].m_lVal  ) 
	{
		pQyMc->curUsrInfo.right.bAdmin  =  TRUE;
			
		}
	else  {
		sprintf(  sqlBuf,  "select count(*) from qyGrpUsrRelationTab where usrName='%s' and grpName='%s'",  nameBuf,  CONST_grpName_xtpz  );
		if  (  bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  1,  varVal  )  
			&&  varVal[0].m_dwType  ==  DBVT_LONG
				&&  varVal[0].m_lVal  ) 
		{
			pQyMc->curUsrInfo.right.bXtpz  =  TRUE;		//  2005/09/30, 加入一个组内管理员
			if  (  !strcmpi(  nameBuf,  CONST_usrName_sysAdmin  )  )  pQyMc->curUsrInfo.right.bXtpzAdmin  =  TRUE;
		}

		sprintf(  sqlBuf,  "select count(*) from qyGrpUsrRelationTab where usrName='%s' and grpName='%s'",  nameBuf,  CONST_grpName_rzsj  );
		if  (  bQyGetRcdBySql(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  1,  varVal  )  
			&&  varVal[0].m_dwType  ==  DBVT_LONG
				&&  varVal[0].m_lVal  ) 
		{
			pQyMc->curUsrInfo.right.bRzsj  =  TRUE;		//  2005/09/30, 加入一个组内管理员
			if  (  !strcmpi(  nameBuf,  CONST_usrName_logAdmin  )  )  pQyMc->curUsrInfo.right.bRzsjAdmin  =  TRUE;
		}

	}

	if  (  pQyMc->cfg.ucbBhqj  )  {	//  2005/09/30, 保密局要求不能有完全权限的管理员组
		if  (  pQyMc->curUsrInfo.right.bAdmin  )  goto  errLabel;
	}
	
	safeStrnCpy(  nameBuf,  pQyMc->curUsrInfo.name,  sizeof(  pQyMc->curUsrInfo.name  )  );

	//  2008/09/04
	QY_USR_RCD	usrInfo;
	if  (  !bGetQyUsrInfoBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  nameBuf,  &usrInfo  )  )  memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
	lstrcpyn(  pQyMc->curUsrInfo.scope.zbStr,  usrInfo.zbStr,  mycountof(  pQyMc->curUsrInfo.scope.zbStr  )  );
	lstrcpyn(  pQyMc->curUsrInfo.scope.bbStr,  usrInfo.bbStr,  mycountof(  pQyMc->curUsrInfo.scope.bbStr  )  );
	lstrcpyn(  pQyMc->curUsrInfo.scope.dwStr,  usrInfo.dwStr,  mycountof(  pQyMc->curUsrInfo.scope.dwStr  )  );
	lstrcpyn(  pQyMc->curUsrInfo.scope.bmStr,  usrInfo.bmStr,  mycountof(  pQyMc->curUsrInfo.scope.bmStr  )  );
	if  (  pQyMc->curUsrInfo.scope.zbStr[0]
		||  pQyMc->curUsrInfo.scope.bbStr[0]
			||  pQyMc->curUsrInfo.scope.dwStr[0]
				||  pQyMc->curUsrInfo.scope.bmStr[0]  )				
	{
		pQyMc->curUsrInfo.scope.bRestricted  =  TRUE;
	}


	if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
		if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_netMc  )  goto  errLabel;
		switch  (  pQyMc->iSystemId  )  {
				case  CONST_qySystemId_netMc2:
				case  CONST_qySystemId_assetMgr:
				case  CONST_qySystemId_nms:
					  break;
				default:
					    AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_limitedUserAccountCannotLogon  )  );
						goto  errLabel;
		}
	}

	//  2011/01/07
	if  (  isIsMgr(  )  )  {
		MC_VAR_isMgr			*	pProcInfo			=	QY_GET_procInfo_isMgr(  );
		//
		QY_COMM_AUTHINFO_MIS	&	authInfo  =  pProcInfo->authInfo;

		myStr2TChar(  pQyMc->curUsrInfo.name,  authInfo.messengerName,  mycountof(  authInfo.messengerName  )  );
	}


	//
	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		//  2006/02/25
		qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_logonFailed,  m_name,  _T(  ""  )  );
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_incorrectUserOrPwd  )  );
		if  (  m_var.nTries  >=  pQyMc->cfg.logon.usMaxInvalidLogonAttempts  )  EndDialog(  -  1  );
		return;
	}
	
	CDialog::OnOK();

}

BOOL CDlgMcLogon::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC		*		pQyMc		=		QY_GET_GBUF(  );
	CString				titleCStr;
	TCHAR				buf[128]	=	_T(  ""  );
	int					nDays_left	=	0;
	TCHAR				tmpBuf[128]	=	_T(  ""  );

	::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );

	titleCStr  =  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logon_wndTitle  )  );
	char  infoBuf[128]  =  "";
	if  (  bQnmLicenseTimeout_gui(  &nDays_left,  infoBuf,  mycountof(  infoBuf  )  )  )  {
		pQyMc->bQnmLicenseTimeout  =  TRUE;
		//
		if  (  qyGetRegCfg(  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  _T(  CONST_regValName_installDate_show  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
		char  timeBuf[128];
		unsigned  int  uiDay,  uiMonth,  uiYear;

		 //  memcpy(  timeBuf,  tmpBuf,  8  );
		 myTChar2Utf8(  tmpBuf,  timeBuf,  mycountof(  timeBuf  )  );
		 timeBuf[8]  =  0;
		 timeBuf[8]  =  0;  uiDay  =  atol(  timeBuf  +  6  );
		 timeBuf[6]  =  0;  uiMonth  =  atol(  timeBuf  +  4  );
		 timeBuf[4]  =  0;  uiYear  =  atol(  timeBuf  );

		 _snprintf(  timeBuf,  mycountof(  timeBuf  ),  "%04d/%02d/%02d",  uiYear,  uiMonth,  uiDay  );
		qyShowHint(  _T(  "%s %s! %d left, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_licenseTimeout  ),  CString(  timeBuf  ),  nDays_left,  CString(  infoBuf  )  );
		
		//
		EndDialog(  -1  );  return  FALSE;
	}
	if  (  bQnmDemo(  )  ) _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %d %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_trialPeriod  ),  nDays_left,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_days  )  );
	titleCStr  +=  CString(  buf  );
	SetWindowText(  titleCStr  );  
	SetDlgItemText(  IDC_STATIC_usrName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logon_staticUsrName  )  );
	SetDlgItemText(  IDC_STATIC_passwd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logon_staticPasswd  )  );
	SetDlgItemText(  IDOK,  getResStr(  0,  &pQyMc->cusRes,  IDOK  )  );
	SetDlgItemText(  IDCANCEL,  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  )  );
	
	
	//

	
	GetDlgItem(  IDC_NAME  )->SendMessage(  EM_SETLIMITTEXT,  16,  0  );
	GetDlgItem(  IDC_PASSWD  )->SendMessage(  EM_SETLIMITTEXT,  16,  0  );
	
	SetFocus(  );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

