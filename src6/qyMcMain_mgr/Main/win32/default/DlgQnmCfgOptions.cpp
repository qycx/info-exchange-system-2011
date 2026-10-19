// DlgQnmCfgOptions.cpp : implementation file
//

#include	"stdafx.h"
#include	"htmlHelp.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgQnmCfgOptions.h"
#include	"tmplib.h"
#include	<tchar.h>
#include	"qyCusResTemp.h"
#include	"qyPs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgOptions dialog


CDlgQnmCfgOptions::CDlgQnmCfgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgOptions)
	m_qyRegToolDir = _T("");
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmCfgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgOptions)
	DDX_Text(pDX, IDC_qyRegToolDir, m_qyRegToolDir);
	DDV_MaxChars(pDX, m_qyRegToolDir, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgOptions)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_BUTTON_browseDir, OnBUTTONbrowseDir)
	ON_BN_CLICKED(IDC_CHECK_cntIp, OnCHECKcntIp)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgQnmCfgOptions::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgOptions message handlers


CString	getClientSrcDir(  int  iTask  )
{
	QY_MC	*	pQyMc					=	QY_GET_GBUF(  );
	TCHAR		tBuf[MAX_PATH  +  1]	=	_T(  ""  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  pQyMc->cfg.installDir,  _T(  CONST_qyClientSubDir  )  );
	switch  (  iTask  )  {			
			case  CONST_qyPsTask_exportClient_default:
				  //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  _T(  "default\\"  )   );		
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  CQyString(  qyGetDesByType1(  CONST_qyAppAvLevelTable_en,  qyGetAppAvLevel_qyMc(  )  )  )  +  _T(  "\\"  )  );		
				  break;
			case  CONST_qyPsTask_exportClient_ts_logon:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  _T(  "ts_logon\\"  )   );					  
				  break;
			case  CONST_qyPsTask_exportClient_ts_dev:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  _T(  "ts_dev\\"  )   );					  
				  break;
			default:
					break;	
	}

	return  CString(  tBuf  );
}


BOOL CDlgQnmCfgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	char		ip[CONST_qyMaxIpLen  +  1];		
	TCHAR		tBuf[MAX_PATH];
	BOOL		bStopped  =  FALSE;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  2006/06/29, 
	//  
	int		idc;
	int		cnt			=	0;
	int		maxBytes	=	CONST_maxCntAddrLen;
	
	idc  =  IDC_EDIT_cntAddr1;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitDot  |  CONST_qyIdcFlgPermitMinus,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;
	idc  =  IDC_EDIT_cntAddr2;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitDot  |  CONST_qyIdcFlgPermitMinus,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	//  2011/03/25
	if  (  m_var.iTask  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Source: "  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  getClientSrcDir(  m_var.iTask  )  );

		SetDlgItemText(  IDC_STATIC_hint,  tBuf  );
	}

	//  
	getQnmCntCfg(  0,  TRUE,  pQyMc->iServiceId,  HKEY_LOCAL_MACHINE,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  &m_var.cntCfg  );
	if  (  !m_var.cntCfg.usCntPort  )  m_var.cntCfg.usCntPort  =  qnmCntPort(  pQyMc->iServiceId  );
	
	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {
		GetDlgItem(  IDC_CHECK_cntIp  )->SendMessage(  BM_SETCHECK,  m_var.cntCfg.ucbAutoCntIp  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
		//
		if  (  m_var.cntCfg.ucbAutoCntIp  )  SetDlgItemText(  IDC_cntIp,  CString(  m_var.cntCfg.cntIp  )  );
		else  SetDlgItemText(  IDC_cntIp,  _T(  ""  )  );
		}
	else  {
		  GetDlgItem(  IDC_CHECK_cntIp  )->SendMessage(  BM_SETCHECK,  BST_UNCHECKED,  0  );
		  //		
		  SetDlgItemText(  IDC_cntIp,  _T(  ""  )  );		  
	}
	//
	SetDlgItemText(  IDC_EDIT_cntAddr1,  CString(  m_var.cntCfg.cntAddrs[0]  )  );
	SetDlgItemText(  IDC_EDIT_cntAddr2,  CString(  m_var.cntCfg.cntAddrs[1]  )  );
	//
	SetDlgItemInt(  IDC_cntPort,  m_var.cntCfg.usCntPort  );
	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {
		GetDlgItem(  IDC_cntPort  )->EnableWindow(  FALSE  );
	}

	//  
	if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_regToolDir  ),  (  char  *  )m_var.qyRegToolDir,  sizeof(  m_var.qyRegToolDir  ),  0  )  )  m_var.qyRegToolDir[0]  =  0;
	this->m_qyRegToolDir  =  m_var.qyRegToolDir;
	
	

	UpdateData(  FALSE  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgQnmCfgOptions::OnOK() 
{
	QY_MC			*	pQyMc			=		QY_GET_GBUF(  );
	DWORD				dwDomainSvrIp	=		0;
	DWORD				dwIp			=		0;
	//  char				hintBuf[sizeof(  m_var.hint  )];
	char				buf[1024];
	unsigned  char		ucbAutoCntIp	=		TRUE;
	CString				str;
	int					index;
	TCHAR			*	pRegValName		=		NULL;
	int					idc;

	UpdateData(  TRUE  );

	//  
	if  (  GetDlgItem(  IDC_CHECK_cntIp  )->SendMessage(  BM_GETCHECK,  0,  0  )  !=  BST_CHECKED  )  ucbAutoCntIp  =  FALSE;
	
	//  
	MACRO_CStringTrim(  this->m_qyRegToolDir  );	
	if  (  m_qyRegToolDir.GetLength(  )  )  {
		DWORD  kk;

		kk  =  GetFileAttributes(  m_qyRegToolDir.GetBuffer(  0  )  );
		if  (  kk  ==  0xFFFFFFFF  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_folderDoesNotExist  )  );  return;
		}
		if  (  !(  kk  &  FILE_ATTRIBUTE_DIRECTORY  )  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pathIsNotAFolder  )  );  return;
		}
	}


	//	
	if  (  m_var.cntCfg.ucbAutoCntIp  !=  ucbAutoCntIp  )  {
		if  (  !ucbAutoCntIp  )  qySetRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_bNotAutoCntIp  ),  _T(  "1"  )  );
		else  qyDelRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_bNotAutoCntIp  )  );
	}
	qyDelRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_cntIp  )  );	//  2006/06/29, 不再使用这个注册项

	index  =  0;  pRegValName  =  _T(  CONST_regValName_cntAddr1  );  idc  =  IDC_EDIT_cntAddr1;
	GetDlgItemText(  idc,  str  );
	myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
	if  (  strcmpi(  m_var.cntCfg.cntAddrs[index],  buf  )  )  {
		if  (  buf[0]  )  qySetRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pRegValName,  CString(  buf  )  );
		else  qyDelRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pRegValName  );
	}
	//
	index  ++  ;  pRegValName  =  _T(  CONST_regValName_cntAddr2  );  idc  =  IDC_EDIT_cntAddr2;
	GetDlgItemText(  idc,  str  );
	myTChar2Str(  str,  buf,  sizeof(  buf  )  );  trim(  buf  );
	if  (  strcmpi(  m_var.cntCfg.cntAddrs[index],  buf  )  )  {
		if  (  buf[0]  )  qySetRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pRegValName,  CString(  buf  )  );
		else  qyDelRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pRegValName  );
	}
	//  2010/09/23
	unsigned  short  usPort  =  0;
	pRegValName  =  _T(  CONST_regValName_cntPort  );	idc  =  IDC_cntPort;
	usPort  =  GetDlgItemInt(  idc  );
	if  (  m_var.cntCfg.usCntPort  !=  usPort  )  {
		if  (  !usPort  ||  usPort  ==  qnmCntPort(  pQyMc->iServiceId  )  )  qyDelRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pRegValName  );
		else  qySetRegCfg(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pRegValName,  CString(  _ltoa(  usPort,  buf,  10  )  )  );
	}

	//
	getQnmCntCfg(  0,  TRUE,  pQyMc->iServiceId,  HKEY_LOCAL_MACHINE,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  &m_var.cntCfg  );

	//
	if  (  lstrcmpi(  m_var.qyRegToolDir,  this->m_qyRegToolDir  )  )  {
		lstrcpyn(  m_var.qyRegToolDir,  m_qyRegToolDir,  mycountof(  m_var.qyRegToolDir  )  );
		qySetRegCfgT(  HKEY_LOCAL_MACHINE,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  _T(  CONST_regValName_regToolDir  ),  this->m_qyRegToolDir  );
	}

	
	CDialog::OnOK();

}




void CDlgQnmCfgOptions::OnHelp() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR		rootKey[1024];
	TCHAR		installDir[MAX_PATH  +  1];
	TCHAR		helpFileName[MAX_PATH  +  1];
	
	safeTcsnCpy(  pQyMc->cfg.pSysCfg->rootKey_mcGui,  rootKey,  mycountof(  rootKey  )  );
	if  (  qyGetRegCfg(  CString(  rootKey  ),  CString(  QY_INSTALLDIR_VALNAME  ),  (  char  *  )installDir,  sizeof(  installDir  )  )  )  goto  errLabel;
	if  (  trailDir(  installDir,  mycountof(  installDir  )  )  )  goto  errLabel;
		
	_sntprintf(  helpFileName,  mycountof(  helpFileName  ),  _T(  "%s%s%s"  ),  installDir,  CString(  CONST_qyHelpSubDir  ),  _T(  "qnm.chm::/html/目录.html"  )  );

	// 	helpFile += "Help\\Dect.chm::/目录.htm";
	
	::HtmlHelp(  NULL,  CString(  helpFileName  ),  HH_DISPLAY_TOPIC,  0  );	

errLabel:

	return;
}


void CDlgQnmCfgOptions::OnBUTTONbrowseDir() 
{
	CString		path;
	CQyString	pathStr;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );	
	int			idc		=	IDC_qyRegToolDir;

	GetDlgItemText(  idc,  path  );
	if  (  qyBrowseForDir(  this->m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFolder  ),  path,  pathStr  )  )  return;
		
	SetDlgItemText(  idc,  pathStr.GetBuffer(  0  )  );
	

}

void CDlgQnmCfgOptions::OnCHECKcntIp() 
{
	// TODO: Add your control notification handler code here
	unsigned  char  ucbChecked  =  FALSE;
	if  (  GetDlgItem(  IDC_CHECK_cntIp  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ucbChecked  =  TRUE;

	char	ip[CONST_qyMaxIpLen  +  1];
	if  (  ucbChecked  )  {
		if  (  !qnmCntIp(  ip,  sizeof(  ip  )  )  )  ip[0]  =  0;
		SetDlgItemText(  IDC_cntIp,  CString(  ip  )  );
		//
		}
	else  {
		  SetDlgItemText(  IDC_cntIp,  _T(  ""  )  );
		  //
	}
	
}

void CDlgQnmCfgOptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
