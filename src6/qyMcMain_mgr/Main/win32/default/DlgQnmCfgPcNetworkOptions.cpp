// DlgQnmCfgPcNetworkOptions.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmCfgPcNetworkOptions.h"
#include	"DlgPcNetworkOptionsSel.h"
#include	"DlgQnmCfgWindowsUpdatePolicy.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcNetworkOptions dialog


CDlgQnmCfgPcNetworkOptions::CDlgQnmCfgPcNetworkOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgPcNetworkOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgPcNetworkOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmCfgPcNetworkOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgPcNetworkOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgPcNetworkOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgPcNetworkOptions)
	ON_BN_CLICKED(IDC_BUTTON_bindPcNetworkOptions, OnBUTTONbindPcNetworkOptions)
	ON_BN_CLICKED(IDC_BUTTON_cancelPcNetworkOptionsBindings, OnBUTTONcancelPcNetworkOptionsBindings)
	ON_BN_CLICKED(IDC_BUTTON_cfgWindowsUpdatePolicy, OnBUTTONcfgWindowsUpdatePolicy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcNetworkOptions message handlers





 BOOL  bBindPcNetworkOption(  void  *  p0,  void  *  p1,  void  *  pVarValsParam  )
{
	BOOL					bRet			=	FALSE;
	COMMON_PARAM	*		pCommonParam	=	(  COMMON_PARAM  *  )p0;
	CDBVariant		*		pVarVals		=	(  CDBVariant  *  )pVarValsParam;
	int						id;
	QY_PCADAPTER_RCD		rcd,  *p		=	&rcd;
	void			*		pDb				=	pCommonParam->p0;
	char			*		pTimeBuf		=	(  char  *  )pCommonParam->p1;
	QY_PCNETWORK_PROPU		prop;
	
	if  (  pVarVals[0].m_dwType  !=  DBVT_LONG  )  goto  errLabel;
	id			=	pVarVals[0].m_lVal;
 
	if  (  !bGetPcAdapterRcdBySth(  pCommonParam->p0,  0,  NULL,  0,  NULL,  0,  NULL,  NULL,  id,  &rcd  )  )  goto  errLabel;
	memset(  &prop,  0,  sizeof(  prop  )  );
	switch  (  rcd.uiType  )  {
			case  CONST_pcNetworkPropType_adapter:
				  rcd.ucbRule  =  TRUE;
				  if  (  rcd.ucbDhcpEnabled  )  {
					  rcd.ipBuf[0]  =  0;  rcd.ipMaskBuf[0]  =  0;  rcd.gatewayBuf[0]  =  0;
					  rcd.dhcpServerIp[0]  =  0;
				  }
				  if  (  rcd.ucbAutoDns  )  rcd.dnsBuf[0]  =  0;	//  2005/06/29
				  safeStrnCpy(  pTimeBuf,  p->firstTime,  sizeof(  p->firstTime  )  );
				  safeStrnCpy(  pTimeBuf,  p->lastTime,  sizeof(  p->lastTime  )  );
				  //  if  (  !bMacValid(  p->mac  )  )  goto  errLabel;	//  只绑定2000以上的，有MAC, //  2005/11/27, 开放对98修改IP的功能
				  if  (  bGetPcAdapterRcdBySth(  pDb,  TRUE,  rcd.uiType,  rcd.mac0,  0,  0,  rcd.mac,  NULL,  0,  &rcd  )  )  {
					  bRet  =  TRUE;  goto  errLabel;
				  }
				  break;
			case  CONST_pcNetworkPropType_proxy:
				  pcNetworkRcd2Prop(  &rcd,  &prop  );
				  pcNetworkProp2Rcd(  &prop,  TRUE,  &rcd  );
				  if  (  bGetPcAdapterRcdBySth(  pDb,  0,  0,  0,  0,  0,  0,  &rcd ,  0,  &rcd  )  )  {
					  bRet  =  TRUE;  goto  errLabel;
				  }
				  break;

			case  CONST_pcNetworkPropType_computer:
				  pcNetworkRcd2Prop(  &rcd,  &prop  );
				  pcNetworkProp2Rcd(  &prop,  TRUE,  &rcd  );
				  if  (  bGetPcAdapterRcdBySth(  pDb,  0,  0,  0,  0,  0,   0,  &rcd,  0,  &rcd  )  )  {
					  bRet  =  TRUE;  goto  errLabel;
				  }
				  break;
			default:
					goto  errLabel;
	}

	if  (  !bAddPcAdapterRcd(  pDb,  p  )  )  goto  errLabel;
	traceLogA(  "新增了%s的网络配置",  p->mac0  );
	
	bRet  =  TRUE;
errLabel:
	return  TRUE;	
}

void CDlgQnmCfgPcNetworkOptions::OnBUTTONbindPcNetworkOptions() 
{
	// TODO: Add your control notification handler code here
	if  (  AfxMessageBox(  _T(  "Whether to bind ip address with mac and bing proxy server settings and bind windows update settings?"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	int					iErr								=	-1;
	QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	char				sqlBuf[CONST_maxSqlBufLen  +  1];
	CQnmDb				myDb;
	char				timeBuf[CONST_qyTimeLen  +  1];
	COMMON_PARAM		commonParam;
	unsigned  int		uiType								=	CONST_pcNetworkPropType_adapter;
	CDBVariant			varVals[30];

	getCurTime(  timeBuf  );
	MACRO_makeCommonParam3(  myDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  ),  timeBuf,  0,  commonParam  );


	uiType								=	CONST_pcNetworkPropType_adapter;
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qyPcAdapterTab.id from qyPcAdapterTab where qyPcAdapterTab.ucbRule<>'1' and qyPcAdapterTab.uiType in (%d,%d)",  CONST_pcCommType_adapter,  CONST_pcCommType_proxy  );
	if  (  !bEnumSqlQuery(  pQyMc->gui.pDb,  CString(  sqlBuf  ),  bBindPcNetworkOption,  &commonParam,  NULL,  varVals,  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  )  goto  errLabel;

	iErr  =  0;

errLabel:
	
	AfxMessageBox(  iErr  ?  _T(  "Failed to bind"  )  :  _T(  "binded successfully"  )  );

	return;
}

void CDlgQnmCfgPcNetworkOptions::OnBUTTONcancelPcNetworkOptionsBindings() 
{
	CDlgPcNetworkOptionsSel	dlg;

	if  (  dlg.DoModal(  )  !=  IDOK  )  return;
	if  (  !dlg.m_var.ucbPcAdapter  
		&&  !dlg.m_var.ucbProxy  
			&&  !dlg.m_var.ucbComputer  
				&&  !dlg.m_var.ucbWindowsUpdatePolicy  )  
	{
		return;
	}


	int					iErr								=	-1;
	QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	char				sqlBuf[CONST_maxSqlBufLen  +  1];
	CQnmDb				myDb;
	char				timeBuf[CONST_qyTimeLen  +  1];
	unsigned  char		ucbFirst							=	FALSE;

	getCurTime(  timeBuf  );
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qyPcAdapterTab where ucbRule='1' and uiType in ("  );
	if  (  dlg.m_var.ucbPcAdapter  )  {  
		ucbFirst  =  TRUE;  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s%d",  sqlBuf,  CONST_pcCommType_adapter  );  
	}
	if  (  dlg.m_var.ucbProxy  )  {
		if  (  ucbFirst  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s,",  sqlBuf  );
		ucbFirst  =  TRUE;
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s%d",  sqlBuf,  CONST_pcCommType_proxy  );  
	}
	if  (  dlg.m_var.ucbComputer  )  {
		if  (  ucbFirst  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s,",  sqlBuf  );
		ucbFirst  =  TRUE;
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s%d",  sqlBuf,  CONST_pcCommType_computer  );  
	}
	if  (  dlg.m_var.ucbWindowsUpdatePolicy  )  {
		if  (  ucbFirst  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s,",  sqlBuf  );
		ucbFirst  =  TRUE;
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s%d",  sqlBuf,  CONST_pcCommType_windowsUpdatePolicy  );  
	}
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s)",  sqlBuf  );
	//
	if  (  !bQyExecSql(  pQyMc->gui.pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	AfxMessageBox(  iErr  ?  _T(  "Failed to unbind"  )  :  _T(  "Unbinded successfully"  )  );

}

 //  2006/09/11
 int  initDevCmd(  QY_DMITEM  *  pTable,  HWND  hDlg,  int  idc,  char  *  pRegVal,  unsigned  char  ucDefaultCmd,  unsigned  char  *  pucCmd  )
{
	char				buf[256];
	HWND				hCb			=	NULL;
	int					nCurSel		=	0;
	int					i			=	0;
	QY_DMITEM		*	pItem		=	NULL;
	unsigned  char		ucCmd		=	0;

	hCb			=	GetDlgItem(  hDlg,  idc  );
	ucCmd		=	ucDefaultCmd;

	SendMessage(  hCb,  CB_RESETCONTENT,  0,  0  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  SendMessage(  hCb,  CB_ADDSTRING,  0,  (  LPARAM  )pItem->des  );
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  buf,  sizeof(  buf  )  )  
		&&  qyGetDesByType(  pTable,  atol(  buf  )  )  )
	{
		ucCmd  =  (  unsigned  char  )atol(  buf  );
	}
	SendMessage(  hCb,  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType(  pTable,  ucCmd  )  );  
	if  (  pucCmd  )  *pucCmd  =  ucCmd;		//  2005/06/25

	return  0;
 }


 int  getDevCmdFromDlg(  QY_DMITEM  *  pTable,  HWND  hDlg,  int  idc,  unsigned  char  ucDefaultCmd,  unsigned  char  *  pucCmd  )  
{
	int					iErr		=	-1;
	unsigned  char		ucCmd		=	ucDefaultCmd;
	HWND				hCb			=	NULL;
	TCHAR				tCmdBuf[1024];
	int					nCurSel		=	0;
	
	hCb			=	GetDlgItem(  hDlg,  idc  );
	ucCmd		=	ucDefaultCmd;

	nCurSel  =  SendMessage(  hCb,  CB_GETCURSEL,  0,  0  );
	SendMessage(  hCb,  CB_GETLBTEXT,  nCurSel,  (  LPARAM  )tCmdBuf  );
	ucCmd  =  qyGetTypeByDes(  pTable,  tCmdBuf  );

	iErr  =  0;
//  errLabel:
	if  (  !iErr  )  {
		if  (  pucCmd  )  *pucCmd  =  ucCmd;
	}
	return  iErr;
	
}


BOOL CDlgQnmCfgPcNetworkOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR		tBuf[128];


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	if  (  !bGetDefaultPcRule(  pQyMc->cfg.ucbAdvancedVer,  pQyMc->gui.pDb,  &m_var.pcRules  )  )  memset(  &m_var.pcRules,  0,  sizeof(  m_var.pcRules  )  );

	QNM_PCNETFLOW_RULE  *  pNetFlow  =  &m_var.pcRules.pcNetFlow;

	if  (  pNetFlow->uiWarnPercentOfBandWithFactor  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.3f"  ),  pNetFlow->uiWarnPercentOfBandWithFactor  /  (  float  )CONST_fakedFactor_percentOfBand  );
		SetDlgItemText(  IDC_EDIT_uiWarnPercent,  tBuf  );
	}
	//  下面设置告警网卡策略
	initDevCmd(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable  ),  this->m_hWnd,  IDC_COMBO_ucWarnedNetworkCardCmd,  CONST_regValName_ucWarnedNetworkCardCmd,  DEFAULT_ucWarnedNetworkCardCmd,  &pNetFlow->ucWarnedNetworkCardCmd  );
	//
	if  (  pNetFlow->ucDetectTimesBeforeWarn  )  SetDlgItemInt(  IDC_EDIT_ucDetectTimesBeforeWarn,  pNetFlow->ucDetectTimesBeforeWarn  );
	GetDlgItem(  IDC_CHECK_ucbPopupToWarn  )->SendMessage(  BM_SETCHECK,  pNetFlow->ucbPopupToWarn  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemInt(  IDC_EDIT_stopNetworkCardTime,  pNetFlow->usStopNetworkCardTimeInSecond  );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQnmCfgPcNetworkOptions::OnBUTTONcfgWindowsUpdatePolicy() 
{
	// TODO: Add your control notification handler code here
	CDlgQnmCfgWindowsUpdatePolicy	dlg;

	dlg.bSetDlgInfo(  CONST_qyDlgType_show,  getProcedObjDb(  0,  g_pQyMc->iDsnIndex_mainSys  ),  CONST_qyNullMac,  0  );
	dlg.DoModal(  );
	
}

void CDlgQnmCfgPcNetworkOptions::OnOK() 
{
	TCHAR					tBuf[128];
	char					buf[128];
	QNM_PC_RULES			pcRules;
	QNM_PCNETFLOW_RULE  *	pNetFlow	=	  &pcRules.pcNetFlow;
	QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
		int						idc;
	int						iVal;

	memset(  &pcRules,  0, sizeof(  pcRules  )  );
	//
	idc  =  IDC_EDIT_uiWarnPercent;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
	if  (  atof(  buf  )  <  0  ||  atof(  buf  )  >  100  )  {
		qyShowHint(  _T(  "%s %s : [ %0.3f ~ %0.3f ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_baoJingLiuLiang  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0.000,  99.999  );  GetDlgItem(  idc  )->SetFocus(  );  return;
	}
	pNetFlow->uiWarnPercentOfBandWithFactor  =  (  unsigned  int  )(  atof(  buf  )  *  CONST_fakedFactor_percentOfBand  );
	//
	getDevCmdFromDlg(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable  ),  this->m_hWnd,  IDC_COMBO_ucWarnedNetworkCardCmd,  DEFAULT_ucWarnedNetworkCardCmd,  &pcRules.pcNetFlow.ucWarnedNetworkCardCmd  );
	//
	idc  =  IDC_EDIT_ucDetectTimesBeforeWarn;
	iVal  =  GetDlgItemInt(  idc  );
	if  (  iVal  <  1  ||  iVal  >  255  )  {
		qyShowHint(  _T(  "%s %s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_detectionFrequency  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  1,  255  );  GetDlgItem(  idc  )->SetFocus(  );  return;
	}
	pNetFlow->ucDetectTimesBeforeWarn  =  (  unsigned  char  )iVal;
	//	
	pNetFlow->ucbPopupToWarn  =  GetDlgItem(  IDC_CHECK_ucbPopupToWarn  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED;
	//
	idc  =  IDC_EDIT_stopNetworkCardTime;
	iVal  =  GetDlgItemInt(  idc  );
	if  (  iVal  <  MIN_usStopNetworkCardTimeInSecond  
		||  iVal  >  MAX_usStopNetworkCardTimeInSecond  )
	{
		qyShowHint(  _T(  "%s %s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_disable  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  MIN_usStopNetworkCardTimeInSecond,  MAX_usStopNetworkCardTimeInSecond  );
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}
	pNetFlow->usStopNetworkCardTimeInSecond  =  (  unsigned  short  )iVal;	

	if  (  memcmp(  &m_var.pcRules.pcNetFlow,  &pcRules.pcNetFlow,  sizeof(  pcRules.pcNetFlow  )  )  )  {

		if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  MB_YESNO | MB_DEFBUTTON2  )  !=  IDYES  )  return;
		
		if  (  pNetFlow->ucWarnedNetworkCardCmd  ==  CONST_devCmd_prohibited  &&  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_liuLiangBaoJingShiShiFouZuDuan  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

		_snprintf(  buf,  mycountof(  buf  ),  "%d",  pNetFlow->uiWarnPercentOfBandWithFactor  );
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_uiWarnPercentOfBandWithFactor_pc  ),  CString(  buf  )  );
		//
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_ucWarnedNetworkCardCmd  ),  CString(  ltoa(  pNetFlow->ucWarnedNetworkCardCmd,  buf,  10  )  )  );
		//
		_snprintf(  buf,  mycountof(  buf  ),  "%d",  pNetFlow->ucDetectTimesBeforeWarn  );
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_ucDetectTimesBeforeWarn  ),  CString(  buf  )  );
		//
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbNotPopupToWarn  ),  pNetFlow->ucbPopupToWarn  ?  _T(  ""  )  :  _T(  "1"  )  );
		//
		_snprintf(  buf,  mycountof(  buf  ),  "%d",  pNetFlow->usStopNetworkCardTimeInSecond  );
		qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_usStopNetworkCardTimeInSecond  ),  CString(  buf  )  );

	}



	
	CDialog::OnOK();
}
