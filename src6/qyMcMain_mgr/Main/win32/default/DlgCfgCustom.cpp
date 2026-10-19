// DlgCfgCustom.cpp : implementation file
//

#include	"stdafx.h"
#include	"qymcMainCommon.h"
#include	"myresource.h"
#include	"QyRestrictEdit.h"
#include	"DlgCfgCustom.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgCustom dialog


CDlgCfgCustom::CDlgCfgCustom(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgCustom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgCustom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgCustom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgCustom)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgCustom, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgCustom)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgCfgCustom::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgCustom message handlers




BOOL CDlgCfgCustom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int						idc,  maxBytes;
	int						cnt				=		0;
	char					buf[2  *  sizeof(  m_var.qrtHint  )  +  1];
	QY_MC			*		pQyMc			=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	//
	////////////////////////////


	
	idc  =  IDC_EDIT_nDwLevels;  maxBytes  =  1;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;
	idc  =  IDC_EDIT_nZcbhs;  maxBytes  =  1;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	getCustomComm(  &m_var.custom  );

	SetDlgItemText(  IDC_EDIT_nDwLevels,  CString(  ltoa(  m_var.custom.nDwLevels,  buf,  10  )  )  );
	SetDlgItemText(  IDC_EDIT_nZcbhs,  CString(  ltoa(  m_var.custom.nZcbhs,  buf,  10  )  )  );

	QY_REG			reg;
	unsigned  int	len;
	memset(  &reg,  0,  sizeof(  reg  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_mcGui_netMc  )  );

	//  2005/07/27
	//  设置题头
	GetDlgItem(  IDC_EDIT_qrtTitle  )->SendMessage(  EM_SETLIMITTEXT,  sizeof(  m_var.qrtTitle  )  -  1,  0  );
	len  =  sizeof(  buf  );
	if  (  !tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_qrtTitle  ),  buf,  &len  )  )  myUtf82TChar(  buf,  m_var.qrtTitle,  mycountof(  m_var.qrtTitle  )  );
	else  lstrcpyn(  m_var.qrtTitle, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_default_qrtTitle  ),  mycountof(  m_var.qrtTitle  )  );
	SetDlgItemText(  IDC_EDIT_qrtTitle,  CString(  m_var.qrtTitle  )  );
	//
	//  设置提示
	GetDlgItem(  IDC_EDIT_hint  )->SendMessage(  EM_SETLIMITTEXT,  sizeof(  m_var.qrtHint  )  -  1,  0  );
	len  =  sizeof(  buf  );
	if  (  !tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_qrtHint  ),  buf,  &len  )  )  myUtf82TChar(  buf,  m_var.qrtHint,  sizeof(  m_var.qrtHint  )  );
	else  lstrcpyn(  m_var.qrtHint,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_default_qrtHint  ),  mycountof(  m_var.qrtHint  )  );
	SetDlgItemText(  IDC_EDIT_hint,  CString(  m_var.qrtHint  )  );
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgCustom::OnOK() 
{
	// TODO: Add extra validation here
	unsigned  char			nDwLevels,  nZcbhs;
	char					buf[sizeof(  m_var.qrtHint  )  *  2  +  1];
	TCHAR					tBuf[1024];
	QY_REG					reg;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );

	GetDlgItemText(  IDC_EDIT_nDwLevels,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	if  (  atol(  buf  )  <  CONST_minnDwLevels  ||  atol(  buf  )  >  CONST_maxnDwLevels  )  {
		qyShowHint(  _T(  "%s: %d ~ %d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfCorporateStructureLevel  ),  CONST_minnDwLevels,  CONST_maxnDwLevels  );
		return;
	}
	nDwLevels  =  (  unsigned  char  )atol(  buf  );
	GetDlgItemText(  IDC_EDIT_nZcbhs,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	if  (  atol(  buf  )  <  CONST_minnZcbhs  ||  atol(  buf  )  >  CONST_maxnZcbhs  )  {
		qyShowHint(  _T(  "%s: %d ~ %d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfAssetNoNumber  ),  CONST_minnZcbhs,  CONST_maxnZcbhs  );
		return;
	}
	nZcbhs  =  (  unsigned  char  )atol(  buf  );

	if  (  m_var.custom.nDwLevels  !=  nDwLevels  )  {
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nDwLevels  ),  CString(  ltoa(  nDwLevels,  buf,  10  )  )  );
		m_var.custom.nDwLevels  =  nDwLevels;
		m_var.ucbChanged  =  TRUE;
	}
	if  (  m_var.custom.nZcbhs  !=  nZcbhs  )  {
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nZcbhs  ),  CString(  ltoa(  nZcbhs,  buf,  10  )  )  );
		m_var.custom.nZcbhs  =  nZcbhs;
		m_var.ucbChanged  =  TRUE;
	}

	memset(  &reg,  0,  sizeof(  reg  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_mcGui_netMc  )  );
	reg.uiType  =  REG_BINARY;

	//  2005/07/27
	//  设置qrtTitle
	GetDlgItemText(  IDC_EDIT_qrtTitle,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	if  (  lstrcmp(  tBuf,  m_var.qrtTitle  )  )  {
		myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
		tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_qrtTitle  ),  buf,  strlen(  buf  )  +  1  );
	}
	//  设置qrtHint
	GetDlgItemText(  IDC_EDIT_hint,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	if  (  lstrcmp(  tBuf,  m_var.qrtHint  )  )  {
		myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
		tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_qrtHint  ),  buf,  strlen(  buf  )  +  1  );
	}
	

	CDialog::OnOK();
}



void CDlgCfgCustom::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
