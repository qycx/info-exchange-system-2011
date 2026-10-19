// DlgQnmCfgSnmpObjRule.cpp : implementation file
//

#include	"stdafx.h"
#include	"qymcMainCommon.h"
#include	"myresource.h"
#include	"DlgQnmCfgSnmpObjRule.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgSnmpObjRule dialog


CDlgQnmCfgSnmpObjRule::CDlgQnmCfgSnmpObjRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgSnmpObjRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgSnmpObjRule)
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgQnmCfgSnmpObjRule::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  switchMac,  int  iPortIfIndex  )
{
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	 if  (  !bMacValid(  switchMac  )  )  return  FALSE;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 safeStrnCpy(  switchMac,  m_var.switchMac,  sizeof(  m_var.switchMac  )  );
	 m_var.iPortIfIndex  =  iPortIfIndex;

	 return  TRUE;
}


 BOOL  CDlgQnmCfgSnmpObjRule::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	 BOOL						bRet		=	FALSE;
	 QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	 QY_SNMPOBJRULE_RCD			snmpObjRule;

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 m_var.pObjDb  =  pObjDb;
	 if  (  !bGetSnmpObjRuleBySth(  m_var.pObjDb->pDb,  NULL,  0,  id,  &snmpObjRule  )  )  goto  errLabel;
	 if  (  !bSetDlgInfo(  iDlgType,  m_var.pObjDb,  snmpObjRule.switchMac,  snmpObjRule.iPortIfIndex  )  )  goto  errLabel;
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

void CDlgQnmCfgSnmpObjRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgSnmpObjRule)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmCfgSnmpObjRule, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgSnmpObjRule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgSnmpObjRule message handlers


BOOL CDlgQnmCfgSnmpObjRule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	BOOL				bRet		=	FALSE;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QY_SNMPOBJ_HEAD		snmpObjHead;
	unsigned  char		ucbStopped	=	FALSE;
	TCHAR				tBuf[256];


	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  GetDlgItem(  IDC_COMBO_ibDownPortIfMacNew  )->m_hWnd,  TRUE  );
	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  GetDlgItem(  IDC_COMBO_ibDownPortIfMacChangePort  )->m_hWnd,  TRUE  );
	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  GetDlgItem(  IDC_COMBO_ibNotLogIfMacChanged  )->m_hWnd,  TRUE  );
	bQnmFillCol0FromTable(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  GetDlgItem(  IDC_COMBO_ibDownPortIfWarnSpeed  )->m_hWnd,  TRUE  );


	//  总体策略
	qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_stopDownPortIfMacChanged  ),  &ucbStopped  );
	m_var.ibDownPortIfMacChanged_sys  =  ucbStopped  ?  CONST_snmpFalse  :  CONST_snmpTrue;
	qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_stopDownPortIfWarnSpeed  ),  &ucbStopped  );	//  2006/05/29
	m_var.ibDownPortIfWarnSpeed_sys  =  ucbStopped  ?  CONST_snmpFalse  :  CONST_snmpTrue;

	//
	m_var.iType  =  bIfIndexValid(  m_var.iPortIfIndex  )  ?  CONST_ruleType_switchPort  :  CONST_ruleType_switch;
	SetDlgItemText(  IDC_STATIC_ruleType,  CString(  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleTypeTable  ),  m_var.iType  )  )  );

	//  设备策略
	memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
	if  (  !bGetSnmpObjHeadInfoBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  0,  &snmpObjHead  )  )  goto  errLabel;
	SetDlgItemText(  IDC_STATIC_productName,  CString(  snmpObjHead.productName  )  );
	if  (  !bGetSnmpObjRuleBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  0,  0,  &m_var.snmpObjRule  )  )  memset(  &m_var.snmpObjRule,  0,  sizeof(  m_var.snmpObjRule  )  );
	if  (  m_var.snmpObjRule.ibDirectConn  ==  CONST_snmpTrue  )  GetDlgItem(  IDC_CHECK_ibDirectConn  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
	
	if  (  m_var.iType  ==  CONST_ruleType_switch  )  {
		GetDlgItem(  IDC_STATIC_portIfDescrHint  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_STATIC_portIfDescr  )->ShowWindow(  SW_HIDE  );
		}
	else  {
		  QY_SWITCHPORT_RCD		portInfo;
		  if  (  !bGetPortInfoBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  m_var.iPortIfIndex,  0,  0,  &portInfo,  0  )  )  goto  errLabel;
		  SetDlgItemText(  IDC_STATIC_portIfDescr,  CString(  portInfo.portIfDescr  )  );

		  GetDlgItem(  IDC_CHECK_ibDirectConn  )->EnableWindow(  FALSE  );

	}

#define		CONST_str_invalidPolicy							_T(  "系统策略: 无效"  )
#define		CONST_snmpObjRuleStr							_T(  "设备策略: "  )

	SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacNewStatus,  _T(  ""  )  );
	
	if  (  m_var.iType  ==  CONST_ruleType_switch  )  {
		GetDlgItem(  IDC_COMBO_ibDownPortIfMacNew  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibDownPortIfMacNew  )  );
		GetDlgItem(  IDC_COMBO_ibDownPortIfMacChangePort  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibDownPortIfMacChangePort  )  );
		GetDlgItem(  IDC_COMBO_ibNotLogIfMacChanged  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibNotLogIfMacChanged  )  );
		if  (  m_var.snmpObjRule.warnPercentOfBandWithFactor  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.3f"  ),  (  float  )m_var.snmpObjRule.warnPercentOfBandWithFactor  /  CONST_fakedFactor_percentOfBand  );
			SetDlgItemText(  IDC_EDIT_warnPercentOfBand,  tBuf  );	//  2006/05/29
		}
		GetDlgItem(  IDC_COMBO_ibDownPortIfWarnSpeed  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibDownPortIfWarnSpeed  )  );

		if  (  m_var.ibDownPortIfMacChanged_sys  !=  CONST_snmpTrue  )  SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacNewStatus,  CString(  CONST_str_invalidPolicy  )  );
		if  (  m_var.ibDownPortIfMacChanged_sys  !=  CONST_snmpTrue  )  SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacChangePortStatus,  CString(  CONST_str_invalidPolicy  )  );
		if  (  m_var.ibDownPortIfWarnSpeed_sys  !=  CONST_snmpTrue  )  SetDlgItemText(  IDC_STATIC_ibDownPortIfWarnSpeedStatus,  CString(  CONST_str_invalidPolicy  )  );		//  2006/05/29

		}
	else  {
		  if  (  !bGetSnmpObjRuleBySth(  m_var.pObjDb->pDb,  m_var.switchMac,  m_var.iPortIfIndex,  0,  &m_var.switchPortRule  )  )  memset(  &m_var.switchPortRule,  0,  sizeof(  m_var.switchPortRule  )  );
		  GetDlgItem(  IDC_COMBO_ibDownPortIfMacNew  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.switchPortRule.ibDownPortIfMacNew  )  );
		  GetDlgItem(  IDC_COMBO_ibDownPortIfMacChangePort  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.switchPortRule.ibDownPortIfMacChangePort  )  );
		  GetDlgItem(  IDC_COMBO_ibNotLogIfMacChanged  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.switchPortRule.ibNotLogIfMacChanged  )  );
		  if  (  m_var.switchPortRule.warnPercentOfBandWithFactor  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%.3f"  ),  (  float  )m_var.switchPortRule.warnPercentOfBandWithFactor  /  CONST_fakedFactor_percentOfBand  );
			  SetDlgItemText(  IDC_EDIT_warnPercentOfBand,  tBuf  );	//  2006/05/29
		  }
		  GetDlgItem(  IDC_COMBO_ibDownPortIfWarnSpeed  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.switchPortRule.ibDownPortIfWarnSpeed  )  );
		  		  
		  if  (  m_var.ibDownPortIfMacChanged_sys  !=  CONST_snmpTrue  )  SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacNewStatus,  CString(  CONST_str_invalidPolicy  )  );
		  else  if  (  !m_var.switchPortRule.ibDownPortIfMacNew  &&  m_var.snmpObjRule.ibDownPortIfMacNew  )  SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacNewStatus,  CString(  CONST_snmpObjRuleStr  )  +  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibDownPortIfMacNew  )  );
		  if  (  m_var.ibDownPortIfMacChanged_sys  !=  CONST_snmpTrue  )  SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacChangePortStatus,  CString(  CONST_str_invalidPolicy  )  );
		  else  if  (  !m_var.switchPortRule.ibDownPortIfMacChangePort  &&  m_var.snmpObjRule.ibDownPortIfMacChangePort  )  SetDlgItemText(  IDC_STATIC_ucbDownPortIfMacChangePortStatus,  CString(  CONST_snmpObjRuleStr  )  +  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibDownPortIfMacChangePort  )  );
		  if  (  !m_var.switchPortRule.ibNotLogIfMacChanged  &&  m_var.snmpObjRule.ibNotLogIfMacChanged  )  SetDlgItemText(  IDC_STATIC_ibNotLogIfMacChangedStatus,  CString(  CONST_snmpObjRuleStr  )  +  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibNotLogIfMacChanged  )  ); 
		  //
		  if  (  !m_var.switchPortRule.warnPercentOfBandWithFactor  &&  m_var.snmpObjRule.warnPercentOfBandWithFactor  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %.3f%%"  ),  CString(  CONST_snmpObjRuleStr  ),  (  float  )m_var.snmpObjRule.warnPercentOfBandWithFactor  /  CONST_fakedFactor_percentOfBand  );
			  SetDlgItemText(  IDC_STATIC_warnPercentOfBandStatus,  tBuf  );
		  }
		  if  (  !m_var.switchPortRule.ibDownPortIfWarnSpeed  &&  m_var.snmpObjRule.ibDownPortIfWarnSpeed  )  SetDlgItemText(  IDC_STATIC_ibDownPortIfWarnSpeedStatus,  CString(  CONST_snmpObjRuleStr  )  +  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  m_var.snmpObjRule.ibDownPortIfWarnSpeed  )  ); 

	}
	

	bRet  =  TRUE;
errLabel:
	if  (  !bRet  )  EndDialog(  FALSE  );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 void CDlgQnmCfgSnmpObjRule::OnOK() 
{
	// TODO: Add extra validation here
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );
	QY_SNMPOBJRULE_RCD			snmpObjRule,	*	pOldRule	=	NULL;
	char						sqlBuf[CONST_maxSqlBufLen  +  1];
	CString						str;
	char						buf[512];

	memset(  &snmpObjRule,  0,  sizeof(  snmpObjRule  )  );
	snmpObjRule.ibDirectConn  =  (  GetDlgItem(  IDC_CHECK_ibDirectConn  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ?  CONST_snmpTrue  :  CONST_snmpFalse;
	GetDlgItemText(  IDC_COMBO_ibDownPortIfMacNew,  str  );  MACRO_CStringTrim(  str  );  if  (  str.GetLength(  )  )  snmpObjRule.ibDownPortIfMacNew  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  str  );
	GetDlgItemText(  IDC_COMBO_ibDownPortIfMacChangePort,  str  );  MACRO_CStringTrim(  str  );  if  (  str.GetLength(  )  )  snmpObjRule.ibDownPortIfMacChangePort  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  str  );
	GetDlgItemText(  IDC_COMBO_ibNotLogIfMacChanged,  str  );  MACRO_CStringTrim(  str  );  if  (  str.GetLength(  )  )  snmpObjRule.ibNotLogIfMacChanged  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  str  );
	GetDlgItemText(  IDC_EDIT_warnPercentOfBand,  str  );  MACRO_CStringTrim(  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );  snmpObjRule.warnPercentOfBandWithFactor  =  (  unsigned  long  )(  atof(  buf  )  *  CONST_fakedFactor_percentOfBand  );	//  2006/05/30
	GetDlgItemText(  IDC_COMBO_ibDownPortIfWarnSpeed,  str  );  MACRO_CStringTrim(  str  );  if  (  str.GetLength(  )  )  snmpObjRule.ibDownPortIfWarnSpeed  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  str  );

	if  (  snmpObjRule.warnPercentOfBandWithFactor  <  0  ||  snmpObjRule.warnPercentOfBandWithFactor  >  100  *  CONST_fakedFactor_percentOfBand  )  {
		AfxMessageBox(  _T(  "报警流量输入无效"  )  );  GetDlgItem(  IDC_EDIT_warnPercentOfBand  )->SetFocus(  );  return;
	}
	
	if  (  m_var.iType  ==  CONST_ruleType_switch  )  {
		pOldRule  =  &m_var.snmpObjRule;
		if  (  (  (  snmpObjRule.ibDirectConn  ==  CONST_snmpTrue  )  ==  (  pOldRule->ibDirectConn  ==  CONST_snmpTrue  )  )  
			&&  snmpObjRule.ibDownPortIfMacNew  ==  pOldRule->ibDownPortIfMacNew
				&&  snmpObjRule.ibDownPortIfMacChangePort  ==  pOldRule->ibDownPortIfMacChangePort 
					&&  snmpObjRule.ibNotLogIfMacChanged  ==  pOldRule->ibNotLogIfMacChanged 
						&&  snmpObjRule.warnPercentOfBandWithFactor  ==  pOldRule->warnPercentOfBandWithFactor
							&&  snmpObjRule.ibDownPortIfWarnSpeed  ==  pOldRule->ibDownPortIfWarnSpeed  )  
		{	//  这里表明策略没变化
			bRet  =  TRUE;  goto  errLabel;
		}
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select count(iType) from qySnmpObjRuleTab where iType=%d and switchMac='%s'",  m_var.iType,  m_var.switchMac  );
		if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "insert into qySnmpObjRuleTab(iType,switchMac,ibDirectConn,ibDownPortIfMacChanged,ibDownPortIfMacChangePort,ibNotLogIfMacChanged,warnPercentOfBand,iProcType) values(%d,'%s',%d,%d,%d,%d,%d,%d)",  m_var.iType,  m_var.switchMac,  snmpObjRule.ibDirectConn,  snmpObjRule.ibDownPortIfMacNew,  snmpObjRule.ibDownPortIfMacChangePort,  snmpObjRule.ibNotLogIfMacChanged,  snmpObjRule.warnPercentOfBandWithFactor,  snmpObjRule.ibDownPortIfWarnSpeed  );
		else  if  (  snmpObjRule.ibDirectConn  !=  CONST_snmpTrue  &&  !snmpObjRule.ibDownPortIfMacNew  &&  !snmpObjRule.ibDownPortIfMacChangePort  &&  !snmpObjRule.ibNotLogIfMacChanged  &&  !snmpObjRule.warnPercentOfBandWithFactor  &&  !snmpObjRule.ibDownPortIfWarnSpeed  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qySnmpObjRuleTab where id=%d",  pOldRule->id  );
		else  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "update qySnmpObjRuleTab set ibDirectConn=%d,ibDownPortIfMacChanged=%d,ibDownPortIfMacChangePort=%d,ibNotLogIfMacChanged=%d,warnPercentOfBand=%d,iProcType=%d where id=%d",  snmpObjRule.ibDirectConn,  snmpObjRule.ibDownPortIfMacNew,  snmpObjRule.ibDownPortIfMacChangePort,  snmpObjRule.ibNotLogIfMacChanged,  snmpObjRule.warnPercentOfBandWithFactor,  snmpObjRule.ibDownPortIfWarnSpeed,  pOldRule->id  );
		if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;

		//  2005/03/10加入如果改为阻断策略时，应删除绑定表中的项; 2006/04/28, 换端口时用
		if  (  snmpObjRule.ibDownPortIfMacChangePort  ==  CONST_snmpTrue  )  {
			_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qnmConflictConnTab where qnmConflictConnTab.switchMac='%s'",  m_var.switchMac  );
			traceLogA(  "%s",  sqlBuf  );
			if (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;
		}

		bRet  =  TRUE;  goto  errLabel;
	}
	if  (  m_var.iType  ==  CONST_ruleType_switchPort  )  {
		pOldRule  =  &m_var.switchPortRule;
		if  (  snmpObjRule.ibDownPortIfMacNew  ==  pOldRule->ibDownPortIfMacNew
			&&  snmpObjRule.ibDownPortIfMacChangePort  ==  pOldRule->ibDownPortIfMacChangePort
				&&  snmpObjRule.ibNotLogIfMacChanged  ==  pOldRule->ibNotLogIfMacChanged
					&&  snmpObjRule.warnPercentOfBandWithFactor  ==  pOldRule->warnPercentOfBandWithFactor
						&&  snmpObjRule.ibDownPortIfWarnSpeed  ==  pOldRule->ibDownPortIfWarnSpeed  )  
		{	//  表明策略没变化
			bRet  =  TRUE;  goto  errLabel;
		}
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select count(iType) from qySnmpObjRuleTab where iType=%d and switchMac='%s' and portIfIndex=%d",  m_var.iType,  m_var.switchMac,  m_var.iPortIfIndex  );
		if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "insert into qySnmpObjRuleTab(iType,switchMac,portIfIndex,ibDownPortIfMacChanged,ibDownPortIfMacChangePort,ibNotLogIfMacChanged,warnPercentOfBand,iProcType) values(%d,'%s',%d,%d,%d,%d,%d,%d)",  m_var.iType,  m_var.switchMac,  m_var.iPortIfIndex,  snmpObjRule.ibDownPortIfMacNew,  snmpObjRule.ibDownPortIfMacChangePort,  snmpObjRule.ibNotLogIfMacChanged,  snmpObjRule.warnPercentOfBandWithFactor,  snmpObjRule.ibDownPortIfWarnSpeed  );
		else  if  (  !snmpObjRule.ibDownPortIfMacNew  &&  !snmpObjRule.ibDownPortIfMacChangePort  &&  !snmpObjRule.ibNotLogIfMacChanged  &&  !snmpObjRule.warnPercentOfBandWithFactor  &&  !snmpObjRule.ibDownPortIfWarnSpeed  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf ),  "delete from qySnmpObjRuleTab where id=%d",  pOldRule->id  );
		else  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "update qySnmpObjRuleTab set ibDownPortIfMacChanged=%d,ibDownPortIfMacChangePort=%d,ibNotLogIfMacChanged=%d,warnPercentOfBand=%d,iProcType=%d where id=%d",  snmpObjRule.ibDownPortIfMacNew,  snmpObjRule.ibDownPortIfMacChangePort,  snmpObjRule.ibNotLogIfMacChanged,  snmpObjRule.warnPercentOfBandWithFactor,  snmpObjRule.ibDownPortIfWarnSpeed,  pOldRule->id  );
		if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;

		//  2005/03/10加入如果改为阻断策略时，应删除绑定表中的项
		if  (  snmpObjRule.ibDownPortIfMacChangePort  ==  CONST_snmpTrue  )  {
			_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qnmConflictConnTab where qnmConflictConnTab.switchMac='%s' and qnmConflictConnTab.portIfIndex=%d",  m_var.switchMac,  m_var.iPortIfIndex  );
			if  (  !bQyExecSql(  m_var.pObjDb->pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;
		}

		bRet  =  TRUE;  goto  errLabel;
	}
	

	bRet  =  TRUE;

errLabel:	
	CDialog::OnOK();

}

