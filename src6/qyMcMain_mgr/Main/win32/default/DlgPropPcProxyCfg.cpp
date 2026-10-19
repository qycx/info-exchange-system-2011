// DlgPropPcProxyCfg.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPropPcProxyCfg.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcProxyCfg dialog


CDlgPropPcProxyCfg::CDlgPropPcProxyCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropPcProxyCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropPcProxyCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgPropPcProxyCfg::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;

	 return  TRUE;
}


void CDlgPropPcProxyCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropPcProxyCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropPcProxyCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPropPcProxyCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcProxyCfg message handlers

BOOL CDlgPropPcProxyCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int							iErr		=	-1;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	QWM_USR_INFO				usrInfo;
	char					*	p			=	NULL;
	char						buf[128];
	int							cnt			=  0;
	unsigned  int				maxBytes	=  6;
	QNM_PC_INFO					pcInfo;
	QNM_REG_INFO				regInfo;
	int							idc;
	int							fieldId;
	QY_DMITEM				*	pItem		=	NULL;
	CString						str;

	
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	/*	//  2006/11/25
	SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  this->IDD  )  );
	SetDlgItemText(  IDC_STATIC_staticDw,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticDw  )  );
	SetDlgItemText(  IDC_STATIC_staticBm,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticBm  )  );
	SetDlgItemText(  IDC_STATIC_staticSyr,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticSyr  )  );
	SetDlgItemText(  IDC_STATIC_staticIp,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticIp  )  );
	SetDlgItemText(  IDC_STATIC_staticType,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticType  )  );
	SetDlgItemText(  IDC_STATIC_dialSetting,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_dialSetting  )  );
	SetDlgItemText(  IDC_RADIO_ucbEnableAutodial,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_RADIO_ucbEnableAutodial  )  );
	SetDlgItemText(  IDC_RADIO_ucbNoNetAutodial,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_RADIO_ucbNoNetAutodial  )  );
	SetDlgItemText(  IDC_RADIO_defaultDial,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_RADIO_defaultDial  )  );
	SetDlgItemText(  IDC_STATIC_lanSetting,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_lanSetting  )  );
	SetDlgItemText(  IDC_CHECK_autoDetect,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_CHECK_autoDetect  )  );
	SetDlgItemText(  IDC_CHECK_enableProxy,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_CHECK_enableProxy  )  );
	SetDlgItemText(  IDC_STATIC_staticIpAddress,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticIpAddress  )  );
	SetDlgItemText(  IDC_STATIC_staticPort,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_staticPort  )  );
	SetDlgItemText(  IDC_CHECK_proxyOverride,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_CHECK_proxyOverride  )  );
	SetDlgItemText(  IDOK,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ok  )  );  
	SetDlgItemText(  IDCANCEL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cancel  )  );  
	*/


	
	if  (  !bGetPcAdapterRcdBySth(  m_var.pObjDb->pDb,  FALSE,  m_var.uiType,  m_var.mac0,  0,  0,  0,  NULL,  m_var.id,  &m_var.pcAdapterRcd  )  )  memset(  &m_var.pcAdapterRcd,  0,  sizeof(  m_var.pcAdapterRcd  )  );    

	GetWindowText(  str  );
	if  (  !m_var.pcAdapterRcd.ucbRule  )  SetWindowText(  str  +  _T(  " - ×´Ì¬"  )  );
	else  SetWindowText(  str  +  _T(  " - ²ßÂÔ"  )  );

	memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );
	memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	if  (  !g_dbFuncs.pf_bGetPcInfoByMac(  m_var.pObjDb->pDb,  m_var.pcAdapterRcd.mac0,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	//
	for  (  pItem  =  CONST_fillRegInfoTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 idc  =  pItem->type;  fieldId  =  (  int  )pItem->des;	
		 SetDlgItemText(  idc,  CString(  (  TCHAR  *  )regInfo.u.cols[getRegIndexByFieldId(  fieldId  )]  )  );
	}
	SetDlgItemText(  IDC_STATIC_ip,  CString(  pcInfo.ip  )  );
	SetDlgItemText(  IDC_STATIC_pcNetworkPropType,  CString(  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  ),  m_var.pcAdapterRcd.uiType  )  )  );


	memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
	pcNetworkRcd2Prop(  &m_var.pcAdapterRcd,  (  QY_PCNETWORK_PROPU  *  )&usrInfo  );
	if  (  !usrInfo.ucbEnableAutodial  )  GetDlgItem(  IDC_RADIO_ucbEnableAutodial  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 
	else  if  (  usrInfo.ucbNoNetAutodial  )  GetDlgItem(  IDC_RADIO_ucbNoNetAutodial  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 
	else  GetDlgItem(  IDC_RADIO_defaultDial  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 

	if  (  usrInfo.ucbAutoDetectSettings  )  GetDlgItem(  IDC_CHECK_autoDetect  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 
	if  (  usrInfo.autoConfigUrl[0]  )  {	//  2006/11/25
		GetDlgItem(  IDC_CHECK_autoConfigUrl  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
		SetDlgItemText(  IDC_STATIC_autoConfigUrlVal,  CString(  usrInfo.autoConfigUrl  )  );
	}
	if  (  usrInfo.ucbProxyEnable  )  GetDlgItem(  IDC_CHECK_enableProxy  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 

	safeStrnCpy(  usrInfo.proxyServer,  buf,  sizeof(  buf  )  );
	if  (  (  p  =  strrchr(  buf,  ':'  )  )  )  {
		p[0]  =  0;  p  ++  ;
	}
	SetDlgItemText(  IDC_STATIC_proxyServer,  CString(  buf  )  );
	SetDlgItemText(  IDC_STATIC_port,  CString(  p  ?  p  :  ""  )  );	

	if  (  !strcmpi(  usrInfo.proxyOverride,  "<local>"  )  )  GetDlgItem(  IDC_CHECK_proxyOverride  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );					 


	GetDlgItem(  IDC_RADIO_ucbEnableAutodial  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_RADIO_ucbNoNetAutodial  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_RADIO_defaultDial  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_autoDetect  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_autoConfigUrl  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_enableProxy  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_proxyOverride  )->EnableWindow(  FALSE  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


