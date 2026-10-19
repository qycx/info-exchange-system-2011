// DlgQnmCfgPcProxyCfg.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmCfgPcProxyCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcProxyCfg dialog


CDlgQnmCfgPcProxyCfg::CDlgQnmCfgPcProxyCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgPcProxyCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgPcProxyCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgQnmCfgPcProxyCfg::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	 m_var.iDlgType  =  iDlgType;
	 m_var.id  =  id;

	 return  TRUE;
}


void CDlgQnmCfgPcProxyCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgPcProxyCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgPcProxyCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgPcProxyCfg)
	ON_BN_CLICKED(IDC_CHECK_autoConfigUrl, OnCHECKautoConfigUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcProxyCfg message handlers

BOOL CDlgQnmCfgPcProxyCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	BOOL				bRet		=	FALSE;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QWM_USR_INFO		usrInfo;
	char			*	p			=	NULL;
	char				buf[128];
	int					idc;
	int					cnt			=  0;
	unsigned  int		maxBytes	=  6;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	idc  =  IDC_EDIT_port;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  ),  GetDlgItem(  IDC_COMBO_pcNetworkPropType  )->m_hWnd,  0  );

	if  (  !bGetPcAdapterRcdBySth(  m_var.pObjDb->pDb,  0,  0,  0,  0,  0,  0,  NULL,  m_var.id,  &m_var.pcAdapterRcd  )  )  goto  errLabel;
	if  (  m_var.pcAdapterRcd.ucbRule  )  m_var.ucbRuleExists  =  TRUE;
	else  {
		  memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
		  pcNetworkRcd2Prop(  &m_var.pcAdapterRcd,  (  QY_PCNETWORK_PROPU  *  )&usrInfo  );
		  usrInfo.name[0]  =  0;
		  pcNetworkProp2Rcd(  (  QY_PCNETWORK_PROPU  *  )&usrInfo,  TRUE,  &m_var.pcAdapterRcd  );
		  if  (  bGetPcAdapterRcdBySth(  m_var.pObjDb->pDb,  0,  0,  0,  0,  0,  0,  &m_var.pcAdapterRcd,  0,  &m_var.pcAdapterRcd  )  )  m_var.ucbRuleExists  =  TRUE;
	}

	GetDlgItem(  IDC_COMBO_pcNetworkPropType  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )CString(  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  ),  m_var.pcAdapterRcd.uiType  )  ).GetBuffer(  0  )  );
	GetDlgItem(  IDC_COMBO_pcNetworkPropType  )->EnableWindow(  FALSE  );

	memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
	pcNetworkRcd2Prop(  &m_var.pcAdapterRcd,  (  QY_PCNETWORK_PROPU  *  )&usrInfo  );
	if  (  !usrInfo.ucbEnableAutodial  )  GetDlgItem(  IDC_RADIO_ucbEnableAutodial  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 
	else  if  (  usrInfo.ucbNoNetAutodial  )  GetDlgItem(  IDC_RADIO_ucbNoNetAutodial  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 
	else  GetDlgItem(  IDC_RADIO_defaultDial  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 

	if  (  usrInfo.ucbAutoDetectSettings  )  GetDlgItem(  IDC_CHECK_autoDetect  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 
	//
	if  (  usrInfo.autoConfigUrl[0]  )  {	//  2006/11/25
		GetDlgItem(  IDC_CHECK_autoConfigUrl  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
		SetDlgItemText(  IDC_EDIT_autoConfigUrl,  CString(  usrInfo.autoConfigUrl  )  );
		}
	else  {
		  GetDlgItem(  IDC_EDIT_autoConfigUrl  )->EnableWindow(  FALSE  );
	}
	//	
	if  (  usrInfo.ucbProxyEnable  )  GetDlgItem(  IDC_CHECK_enableProxy  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 

	safeStrnCpy(  usrInfo.proxyServer,  buf,  sizeof(  buf  )  );
	if  (  (  p  =  strrchr(  buf,  ':'  )  )  )  {
		p[0]  =  0;  p  ++  ;
	}
	SetDlgItemText(  IDC_EDIT_proxyServer,  CString(  buf  )  );
	if  (  p  )  SetDlgItemText(  IDC_EDIT_port,  CString(  p  )  );	

	if  (  !strcmpi(  usrInfo.proxyOverride,  "<local>"  )  )  GetDlgItem(  IDC_CHECK_proxyOverride  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 


	bRet  =  TRUE;
errLabel:

	if  (  !bRet  )  EndDialog(  -1  );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQnmCfgPcProxyCfg::OnCHECKautoConfigUrl() 
{
	// TODO: Add your control notification handler code here
	int	idc  =  IDC_CHECK_autoConfigUrl;
	int	idcEdit	=	IDC_EDIT_autoConfigUrl;
	if  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		GetDlgItem(  idcEdit  )->EnableWindow(  TRUE  );
		}
	else  	GetDlgItem(  idcEdit  )->EnableWindow(  FALSE  );

	
}

void CDlgQnmCfgPcProxyCfg::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	QWM_USR_INFO			usrInfo;
	int						idc;
	unsigned  short			usPort;
	QY_PCADAPTER_RCD		tmpRcd;
	char					timeBuf[CONST_qyTimeLen  +  1];
	CString					str;
	
	getCurTime(  timeBuf  );

	memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
	usrInfo.uiType  =  CONST_pcNetworkPropType_proxy;

	//
	idc  =  IDC_RADIO_ucbEnableAutodial;
	usrInfo.ucbEnableAutodial  =  !(  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  );
	idc  =  IDC_RADIO_ucbNoNetAutodial;
	usrInfo.ucbNoNetAutodial  =  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  );

	idc  =  IDC_CHECK_autoDetect;
	usrInfo.ucbAutoDetectSettings  =  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  );
	//
	idc  =  IDC_CHECK_autoConfigUrl;	//  2006/11/25
	if  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		GetDlgItemText(  IDC_EDIT_autoConfigUrl,  str  );  myTChar2Str(  str,  usrInfo.autoConfigUrl,  sizeof(  usrInfo.autoConfigUrl  )  );
	}
	//
	idc  =  IDC_CHECK_enableProxy;
	usrInfo.ucbProxyEnable  =  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  );
	GetDlgItemText(  IDC_EDIT_proxyServer,  str  );  myTChar2Str(  str,  usrInfo.proxyServer,  sizeof(  usrInfo.proxyServer  )  );
	trim(  usrInfo.proxyServer  );
	usPort  =  GetDlgItemInt(  IDC_EDIT_port,  NULL,  FALSE  );
	if  (  usPort  )  _snprintf(  usrInfo.proxyServer,  sizeof(  usrInfo.proxyServer  ),  "%s:%d",  usrInfo.proxyServer,  usPort  );
	idc  =  IDC_CHECK_proxyOverride;
	if  (  GetDlgItem(  idc  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		_snprintf(  usrInfo.proxyOverride,  sizeof(  usrInfo.proxyOverride  ), "<local>"  );
		}
	else  usrInfo.proxyOverride[0]  =  0;

	//  下面考虑更新数据
	m_var.ucbChanged  =  TRUE;

	memset( &tmpRcd,  0,  sizeof(  tmpRcd  )  );
	safeStrnCpy(  m_var.pcAdapterRcd.mac0,  tmpRcd.mac0,  sizeof(  tmpRcd.mac0  )  );
	pcNetworkProp2Rcd(  (  QY_PCNETWORK_PROPU  *  )&usrInfo,  TRUE,  &tmpRcd  );
	if  (  !m_var.ucbRuleExists  )  {
		tmpRcd.ucbRule  =  TRUE;
		safeStrnCpy(  timeBuf,  tmpRcd.firstTime,  sizeof(  tmpRcd.firstTime  )  );
		safeStrnCpy(  timeBuf,  tmpRcd.lastTime,  sizeof(  tmpRcd.lastTime  )  );
		if  (  !bAddPcAdapterRcd(  m_var.pObjDb->pDb,  &tmpRcd  )  )  qyShowHint(  _T(  "添加规则失败"  )  );
		}
	else  if  (  !bPcAdapterRuleSame(  &tmpRcd,  &m_var.pcAdapterRcd  )  )  {
			  safeStrnCpy(  timeBuf,  tmpRcd.lastTime,  sizeof(  tmpRcd.lastTime  )  );
			  if  (  !bUpdatePcAdapterRcdBySth(  m_var.pObjDb->pDb,  &tmpRcd,  m_var.pcAdapterRcd.id  )  )  qyShowHint(  _T(  "更新规则失败"  )  ); 	 
			  }
	else  m_var.ucbChanged  =  FALSE;
	
	CDialog::OnOK();
}

