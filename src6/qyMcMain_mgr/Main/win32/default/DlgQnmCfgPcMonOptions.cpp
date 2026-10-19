// DlgQnmCfgPcMonOptions.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmCfgPcMonOptions.h"
#include	"DlgCfgFileMonFilter.h"
#include	"DlgCfgPcRegistrys.h"
#include ".\dlgqnmcfgpcmonoptions.h"
#include	"qyCusResTemp.h"
#include	"qyPs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcMonOptions dialog


CDlgQnmCfgPcMonOptions::CDlgQnmCfgPcMonOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgPcMonOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgPcMonOptions)
	m_capScreenInterval = 10;
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmCfgPcMonOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgPcMonOptions)
	DDX_Text(pDX, IDC_EDIT_capScreenInterval, m_capScreenInterval);
	DDV_MinMaxUInt(pDX, m_capScreenInterval, 5, 43200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgPcMonOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgPcMonOptions)
	ON_BN_CLICKED(IDC_BUTTON_browseDir, OnBUTTONbrowseDir)
	ON_BN_CLICKED(IDC_BUTTON_cfgFileMonFilter, OnBUTTONcfgFileMonFilter)
	ON_BN_CLICKED(IDC_BUTTON_cfgPcRegistry, OnBUTTONcfgPcRegistry)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcMonOptions message handlers



BOOL CDlgQnmCfgPcMonOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR				buf[256];
	unsigned  char		ucRasCmd	=	CONST_rasCmd_prohibited;
	CComboBox		*	pCb			=	NULL;
	CListBox		*	pLb			=	NULL;
	int					nCurSel		=	0;
	int					idc			=	0;
	QY_DMITEM		*	pTable		=	NULL;
	QY_DMITEM		*	pItem		=	NULL;
	TCHAR			*	pRegVal		=	NULL;
	unsigned  char		ucCmd		=	0;
	QNM_PC_RULES	*	pPcRules	=	&m_var.pcRules;


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  下面设置屏幕拷贝策略
	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable  );
	idc			=	IDC_COMBO_capScreenCmd;
	pRegVal		=	_T(  CONST_regValName_capScreenCmd  );
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	ucCmd		=	DEFAULT_capScreenCmd;

	pCb->ResetContent(  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CString(  pItem->des  )  );
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  )  )  
		&&  qyGetDesByType(  pTable,  _ttol(  buf  )  )  )
	{
		ucCmd  =  (  unsigned  char  )_ttol(  buf  );
	}
	pCb->SelectString(  -1,  CString(  qyGetDesByType(  pTable,  ucCmd  )  )  );  
	pPcRules->pcMon.ucCapScreenCmd  =  ucCmd;	//  2005/06/25


	//  屏幕拷贝存储目录
	idc  =  IDC_EDIT_capScreenDir;
	pRegVal  =  _T(  CONST_regValName_capScreenDir  );
	if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  pRegVal,  (  char  *  )m_var.capScreenDir,  sizeof(  m_var.capScreenDir  )  )  )  m_var.capScreenDir[0]  =  0;
	tTrim(  m_var.capScreenDir  );
	SetDlgItemText(  idc,  CString(  m_var.capScreenDir  )  );
	
	//  屏幕拷贝间隔
	idc  =  IDC_EDIT_capScreenInterval;
	pRegVal  =  _T(  CONST_regValName_capScreenInterval  );
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		tTrim(  buf  );
		m_var.pcRules.pcMon.usCapScreenInterval  =  (  unsigned  short  )_ttol(  buf  );
	}
	if  (  m_var.pcRules.pcMon.usCapScreenInterval  <  CONST_minInterval  ||  m_var.pcRules.pcMon.usCapScreenInterval  >  CONST_maxInterval  )  m_var.pcRules.pcMon.usCapScreenInterval  =  DEFAULT_capScreenInterval;
	SetDlgItemInt(  idc,  m_var.pcRules.pcMon.usCapScreenInterval  );

	//  存储格式
	idc  =  IDC_CHECK_ucbSaveAsGif;
	pRegVal  =  _T(  CONST_regValName_ucbSaveAsGif  );
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		tTrim(  buf  );
		m_var.ucbSaveAsGif  =  _ttol(  buf  )  ?  TRUE  :  FALSE;
	}
	if  (  m_var.ucbSaveAsGif  )  (  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  BST_CHECKED  );
	//
	
	getMonPicsCfg(  &m_var.usCnt_monPics_row,  &m_var.usCnt_monPics_col  );
	SetDlgItemInt(  IDC_EDIT_monPics_row,  m_var.usCnt_monPics_row  );
	SetDlgItemInt(  IDC_EDIT_monPics_col,  m_var.usCnt_monPics_col  );


	if  (  !pQyMc->cfg.ucbPcMonSupported  )  {
		GetDlgItem(  IDC_STATIC_GROUP_capScreen  )->ShowWindow(  SW_HIDE  );
       GetDlgItem(  IDC_STATIC_capScreenCmd  )->ShowWindow(  SW_HIDE  );
	   GetDlgItem(  IDC_COMBO_capScreenCmd  )->ShowWindow(  SW_HIDE  );
       GetDlgItem(  IDC_STATIC_staticCapScreenDir  )->ShowWindow(  SW_HIDE  );
	   GetDlgItem(  IDC_EDIT_capScreenDir  )->ShowWindow(  SW_HIDE  );
       GetDlgItem(  IDC_BUTTON_browseDir  )->ShowWindow(  SW_HIDE  );
       GetDlgItem(  IDC_STATIC_capScreenInterval  )->ShowWindow(  SW_HIDE  );
	   GetDlgItem(  IDC_EDIT_capScreenInterval  )->ShowWindow(  SW_HIDE  );
	}

	if  (  !pQyMc->cfg.ucbFileMonSupported  )  {
        //  GetDlgItem(  IDC_STATIC_fileMon  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_BUTTON_cfgFileMonFilter  )->ShowWindow(  SW_HIDE  );
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQnmCfgPcMonOptions::OnOK() 
{
	// TODO: Add extra validation here
	int					idc			=	0;
	char			*	pRegVal		=	0;
	CComboBox		*	pCb			=	NULL;
	QY_DMITEM		*	pTable		=	NULL;
	unsigned  char		ucCmd		=	0;
	CString				tmpCStr;
	char				buf1[128];
	TCHAR				tBuf[1024];
	//  QNM_PC_RULES		pcRules;
	unsigned  char		ucbAsked	=	FALSE;
	QY_MC			*   pQyMc		=   QY_GET_GBUF(  );
	//
	unsigned  short		usCnt_monPics_row	=	0;
	unsigned  short		usCnt_monPics_col	=	0;
    

	if  (  !UpdateData(  TRUE  )  )  return;

	usCnt_monPics_row  =  GetDlgItemInt(  IDC_EDIT_monPics_row  );
	usCnt_monPics_col  =  GetDlgItemInt(  IDC_EDIT_monPics_col  );
	if  (  !usCnt_monPics_row  ||  !usCnt_monPics_col  )  {
		qyShowHint(  _T(  "0 is invalid"  )  );  return;
	}
	if  (  usCnt_monPics_row  *  usCnt_monPics_col  >  CONST_maxMonedDesktops  )  {
		qyShowHint(  _T(  "%d is invalid"  ),  CONST_maxMonedDesktops  );  return;
	}

	//  memset(  &pcRules,  0,  sizeof(  pcRules  )  );

	//  屏幕拷贝
	idc			=	IDC_COMBO_capScreenCmd;
	pRegVal		=	CONST_regValName_capScreenCmd;
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable  );
	ucCmd		=	DEFAULT_capScreenCmd;
	//		
	pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
	ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
	if  (  ucCmd  !=  m_var.pcRules.pcMon.ucCapScreenCmd  )  {
		if  (  !ucbAsked  &&  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  CString(  ltoa(  ucCmd,  buf1,  10  )  )  );

		//  2005/10/01,  by  wqh
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s:%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_changeCapScreenPolicy  ),  tmpCStr.GetBuffer(  0  )  );
		qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_pzcz,  CString(  pQyMc->curUsrInfo.name  ),  tBuf  );

	}

	idc  =  IDC_EDIT_capScreenDir;
	pRegVal		=	CONST_regValName_capScreenDir;
	//
	GetDlgItemText(  idc,  tmpCStr  );
	MACRO_CStringTrim(  tmpCStr  );
	if  (  tmpCStr.GetLength(  )  &&  !bDir(  tmpCStr  )  )  {		//  2006/04/19
		AfxMessageBox(  _T(  "The folder don't exist"  )  );  GetDlgItem(  idc  )->SetFocus(  );  return;
	}
	if  (  lstrcmpi(  tmpCStr,  m_var.capScreenDir  )  )  {
		if  (  !ucbAsked  &&  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  tmpCStr  );

		//  2005/10/01,  by  wqh
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s:%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_changeCapScreenDir  ),  tmpCStr  );
		qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_pzcz,  CString(  pQyMc->curUsrInfo.name  ),  tBuf  );
	}

	idc  =  IDC_EDIT_capScreenInterval;
	pRegVal  =  CONST_regValName_capScreenInterval;
	unsigned  short	 usInterval;
	//
	GetDlgItemText(  idc,  tmpCStr  );
	MACRO_CStringTrim(  tmpCStr  );
	myTChar2Str(  tmpCStr,  buf1,  mycountof(  buf1  )  );
	usInterval  =  (  unsigned  short  )atol(  buf1  );
	if  (  usInterval  !=  m_var.pcRules.pcMon.usCapScreenInterval  )  {
		if  (  !ucbAsked  &&  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  CString(  buf1  )  );

		//  2005/10/01,  by  wqh
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s:%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_changeCapScreenInterval  ),  tmpCStr  );
		qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_pzcz,  CString(  pQyMc->curUsrInfo.name  ),  tBuf  );
	}
	
	idc  =  IDC_CHECK_ucbSaveAsGif;
	pRegVal  =  CONST_regValName_ucbSaveAsGif;
	unsigned  char  ucbSaveAsGif  =  FALSE;  
	//
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ucbSaveAsGif  =  TRUE;
	//
	if  (  ucbSaveAsGif  !=  m_var.ucbSaveAsGif  )  {
		if  (  !ucbAsked  &&  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  ucbSaveAsGif  ?  _T(  "1"  )  :  _T(  ""  )  );
	}

	//
	if  (  usCnt_monPics_row  !=  m_var.usCnt_monPics_row  ||  usCnt_monPics_col  !=  m_var.usCnt_monPics_col  )  {
		if  (  !ucbAsked  &&  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		pRegVal  =  CONST_regValName_monPics_row;
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  CString(  ltoa(  usCnt_monPics_row,  buf1,  10  )  )  );
		pRegVal  =  CONST_regValName_monPics_col;
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  CString(  ltoa(  usCnt_monPics_col,  buf1,  10  )  )  );
		//
	}


	CDialog::OnOK();
}


void CDlgQnmCfgPcMonOptions::OnBUTTONbrowseDir() 
{
	// TODO: Add your control notification handler code here
	CString	path;
	CQyString	pathStr;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	int		idc		=	IDC_EDIT_capScreenDir;

	GetDlgItemText(  idc,  path  );
	if  (  qyBrowseForDir(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFolder  ),  path,  pathStr  )  )  return;
	
	SetDlgItemText(  idc,  pathStr.GetBuffer(  0  )  );
	
}


void CDlgQnmCfgPcMonOptions::OnBUTTONcfgFileMonFilter() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CDlgCfgFileMonFilter		dlg;

	dlg.DoModal(  );
	
}

void CDlgQnmCfgPcMonOptions::OnBUTTONcfgPcRegistry() 
{
	// TODO: Add your control notification handler code here
	CDlgCfgPcRegistrys			dlg;

	dlg.DoModal(  );
	if  (  dlg.m_var.bNeedRefreshAll  )  m_var.bNeedRefreshAll  =  TRUE;

	
}

void CDlgQnmCfgPcMonOptions::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
