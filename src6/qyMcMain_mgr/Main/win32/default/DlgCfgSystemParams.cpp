// DlgCfgSystemParams.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"QyRestrictEdit.h"
#include	"qymc.h"
#include	"DlgCfgSystemParams.h"
#include ".\dlgcfgsystemparams.h"
#include	"qyCusResTemp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSystemParams dialog


CDlgCfgSystemParams::CDlgCfgSystemParams(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgSystemParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgSystemParams)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCfgSystemParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgSystemParams)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgSystemParams, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgSystemParams)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSystemParams message handlers
 
BOOL CDlgCfgSystemParams::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int				idc;
	int				cnt			=  0;
	unsigned  int	maxBytes	=  6;
	TCHAR			buf[128];
	QY_MC	*		pQyMc		=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	//
	////////////////////////////

	idc  =  IDC_EDIT_getCfgInterval;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_queryCfgsInterval;		//  2006/08/15
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_getOpCmdInterval;		//  2006/03/23
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showPcNetworkPropInterval;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_sndEventLogInterval;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_sndUsrInfoInterval;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_sndNetStatInterval;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showProcessInterval;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showModulesInterval;	//  2006/04/14
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showNetFlowInterval;	//  2006/09/12
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showWindowsUpdatePolicyInterval;	//  2006/05/24
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_sndPrintersInterval;	//  2006/12/10
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showPcNetShareInterval;	//  2007/02/20
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_showPcArpInterval;	//  2007/02/20
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_nProcessQmObjQInterval;	//  2006/12/10
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_nRefreshQmObjQLastCommTime;	//  2006/12/10
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	idc  =  IDC_EDIT_maxLogs;
	maxBytes  =  8;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;


	//  2006/08/18
	idc  =  IDC_EDIT_nMaxConns;
	maxBytes  =  3;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  maxBytes,  0  );
	cnt  ++  ;

	_sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%d%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_nMaxConns  ),  getnMaxConns_netMc(  &pQyMc->licenseCtx  ),  _T(  "):"  )  );
	SetDlgItemText(  IDC_STATIC_nMaxConns,  buf  );

	//
	
	bGetQnmIntervalParams(  &m_var.intervalParams  );
	//
	m_var.nProcessQmObjQInterval  =  CONST_QMD_nProcessQmObjQIntervalLoops;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nProcessQmObjQInterval  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		m_var.nProcessQmObjQInterval  =  _ttol(  buf  );
	}
	m_var.nRefreshQmObjQStatusInDb  =  CONST_QMD_nRefreshQmObjQStatusInDbLoops;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nRefreshQmObjQStatusInDb  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		m_var.nRefreshQmObjQStatusInDb  =  _ttol(  buf  );
	}
	//
	m_var.uiMaxLogs					=  DEFAULT_maxLogs;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_maxLogs  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		m_var.uiMaxLogs  =  _ttol(  buf  );
	}
	m_var.nMaxConns					=  getQnmnConns(  &pQyMc->licenseCtx,  pQyMc->iServiceId  );

	
	SetDlgItemInt(  IDC_EDIT_getCfgInterval,  m_var.intervalParams.usGetCfgInterval  );
	SetDlgItemInt(  IDC_EDIT_queryCfgsInterval,	 m_var.intervalParams.usQueryCfgsInterval  );	//  2006/08/15
	SetDlgItemInt(  IDC_EDIT_getOpCmdInterval,  m_var.intervalParams.usGetOpCmdInterval  );
	SetDlgItemInt(  IDC_EDIT_showPcNetworkPropInterval,  m_var.intervalParams.usShowPcNetworkInterval  );
	SetDlgItemInt(  IDC_EDIT_sndEventLogInterval,  m_var.intervalParams.usSndEventLogInterval  );
	SetDlgItemInt(  IDC_EDIT_sndUsrInfoInterval,  m_var.intervalParams.usSndUsrInfoInterval  );
	SetDlgItemInt(  IDC_EDIT_sndNetStatInterval,  m_var.intervalParams.usSndNetStatInterval  );
	SetDlgItemInt(  IDC_EDIT_showProcessInterval,  m_var.intervalParams.usShowProcessInterval  );
	SetDlgItemInt(  IDC_EDIT_showModulesInterval,  m_var.intervalParams.usShowModulesInterval  );
	SetDlgItemInt(  IDC_EDIT_showNetFlowInterval,  m_var.intervalParams.usShowNetFlowInterval  );
	SetDlgItemInt(  IDC_EDIT_showWindowsUpdatePolicyInterval,	m_var.intervalParams.usShowWindowsUpdatePolicyInterval  );	//  2006/05/24
	SetDlgItemInt(  IDC_EDIT_sndPrintersInterval,  m_var.intervalParams.usSndPrintersInterval  );							//  2006/12/10
	SetDlgItemInt(  IDC_EDIT_showPcNetShareInterval,  m_var.intervalParams.usShowPcNetShareInterval  );						//  2007/02/20
	SetDlgItemInt(  IDC_EDIT_showPcArpInterval,  m_var.intervalParams.usShowPcArpInterval  );						//  2007/02/20

	//
	SetDlgItemInt(  IDC_EDIT_nProcessQmObjQInterval,  m_var.nProcessQmObjQInterval  );
	SetDlgItemInt(  IDC_EDIT_nRefreshQmObjQLastCommTime,  m_var.nRefreshQmObjQStatusInDb  );
	SetDlgItemInt(  IDC_EDIT_maxLogs,  m_var.uiMaxLogs  );
	SetDlgItemInt(  IDC_EDIT_nMaxConns,	m_var.nMaxConns  );
	
	if  (  1  )  {
		GetDlgItem(  IDC_STATIC_showPcArpInterval  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_EDIT_showPcArpInterval  )->ShowWindow(  SW_HIDE  );
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 

void CDlgCfgSystemParams::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC			*	pQyMc							=	QY_GET_GBUF(  );
	char				buf[128];
	int					idc;
	unsigned  int		uiGetCfgInterval;
	unsigned  int		uiQueryCfgsInterval;
	unsigned  int		uiGetOpCmdInterval;
	unsigned  int		uiShowPcNetworkInterval;
	unsigned  int		uiSndEventLogInterval;
	unsigned  int		uiSndUsrInfoInterval;
	unsigned  int		uiSndNetStatInterval;
	unsigned  int		uiShowProcessInterval;
	unsigned  int		uiShowModulesInterval;
	unsigned  int		uiShowNetFlowInterval;				//  2006/09/12
	unsigned  int		uiShowWindowsUpdatePolicyInterval;	//  2006/05/24
	unsigned  int		uiSndPrintersInterval;				//  2006/12/10
	unsigned  int		uiShowPcNetShareInterval;			//  2007/02/20
	unsigned  int		uiShowPcArpInterval;				//  2007/02/20

	//
	unsigned  int		nProcessQmObjQInterval;				//  2006/12/10
	unsigned  int		nRefreshQmObjQStatusInDb;			//  2006/12/10
	unsigned  int		uiMaxLogs;
	unsigned  int		nMaxConns;							//  2006/08/18
	CString				str;
	//	TCHAR				tBuf[128];

	idc  =  IDC_EDIT_getCfgInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiGetCfgInterval  =  atol(  buf  );
	//
	if  (  uiGetCfgInterval  <  CONST_minInterval  ||  uiGetCfgInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	//
	idc  =  IDC_EDIT_queryCfgsInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiQueryCfgsInterval  =  atol(  buf  );
	//
	if  (  uiQueryCfgsInterval  <  CONST_minInterval  ||  uiGetCfgInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_getOpCmdInterval;		//  2006/03/23
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiGetOpCmdInterval  =  atol(  buf  );
	//
	if  (  uiGetOpCmdInterval  <  CONST_minInterval  ||  uiGetOpCmdInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}	

	idc  =  IDC_EDIT_showPcNetworkPropInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowPcNetworkInterval  =  atol(  buf  );
	//
	if  (  uiShowPcNetworkInterval  <  CONST_minInterval  ||  uiShowPcNetworkInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_sndEventLogInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiSndEventLogInterval  =  atol(  buf  );
	//
	if  (  uiSndEventLogInterval  <  CONST_minInterval  ||  uiSndEventLogInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_sndUsrInfoInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiSndUsrInfoInterval  =  atol(  buf  );
	//
	if  (  uiSndUsrInfoInterval  <  CONST_minInterval  ||  uiSndUsrInfoInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_sndNetStatInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiSndNetStatInterval  =  atol(  buf  );
	//
	if  (  uiSndNetStatInterval  <  CONST_minInterval  ||  uiSndNetStatInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_showProcessInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowProcessInterval  =  atol(  buf  );
	//
	if  (  uiShowProcessInterval  <  CONST_minInterval  ||  uiShowProcessInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_showModulesInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowModulesInterval  =  atol(  buf  );
	//
	if  (  uiShowModulesInterval  <  CONST_minInterval  ||  uiShowModulesInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	//
	idc  =  IDC_EDIT_showNetFlowInterval;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowNetFlowInterval  =  atol(  buf  );
	//
	if  (  uiShowNetFlowInterval  <  CONST_minInterval  ||  uiShowNetFlowInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}


	idc  =  IDC_EDIT_showWindowsUpdatePolicyInterval;		//  2006/05/24
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowWindowsUpdatePolicyInterval  =  atol(  buf  );
	//
	if  (  uiShowWindowsUpdatePolicyInterval  <  CONST_minInterval  ||  uiShowWindowsUpdatePolicyInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_sndPrintersInterval;				//  2006/12/10
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiSndPrintersInterval  =  atol(  buf  );
	//
	if  (  uiSndPrintersInterval  <  CONST_minInterval  ||  uiSndPrintersInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_showPcNetShareInterval;				//  2007/02/20
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowPcNetShareInterval  =  atol(  buf  );
	//
	if  (  uiShowPcNetShareInterval  <  CONST_minInterval  ||  uiShowPcNetShareInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_showPcArpInterval;				//  2007/02/20
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiShowPcArpInterval  =  atol(  buf  );
	//
	if  (  uiShowPcArpInterval  <  CONST_minInterval  ||  uiShowPcArpInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_nProcessQmObjQInterval;			//  2006/12/10
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	nProcessQmObjQInterval  =  atol(  buf  );
	//
	if  (  nProcessQmObjQInterval  <  CONST_minInterval  ||  nProcessQmObjQInterval  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_nRefreshQmObjQLastCommTime;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	nRefreshQmObjQStatusInDb  =  atol(  buf  );
	//
	if  (  nRefreshQmObjQStatusInDb  <  CONST_minInterval  ||  nRefreshQmObjQStatusInDb  >  CONST_maxInterval  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_minInterval,  CONST_maxInterval  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	idc  =  IDC_EDIT_maxLogs;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	uiMaxLogs  =  atol(  buf  );

	//  2006/08/18
	idc  =  IDC_EDIT_nMaxConns;			//  2006/08/18
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	nMaxConns  =  atol(  buf  );
	//
	if  (  (  int  )nMaxConns  <=  0  ||  (  int  )nMaxConns  >  getnMaxConns_netMc(  &pQyMc->licenseCtx  )  )  {
		qyShowHint(  _T(  "%s : [ %d ~ %d]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  1,  getnMaxConns_netMc(  &pQyMc->licenseCtx  )  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}


	if  (  m_var.intervalParams.usGetCfgInterval  !=  uiGetCfgInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_getCfgInterval  ),  CString(  ltoa(  uiGetCfgInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usQueryCfgsInterval  !=  uiQueryCfgsInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_queryCfgsInterval  ),  CString(  ltoa(  uiQueryCfgsInterval,  buf,  10  )  )  );	//  2006/08/15
	if  (  m_var.intervalParams.usGetOpCmdInterval  !=  uiGetOpCmdInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_getOpCmdInterval  ),  CString(  ltoa(  uiGetOpCmdInterval,  buf,  10  )  )  );		//  2006/03/23
	if  (  m_var.intervalParams.usShowPcNetworkInterval  !=  uiShowPcNetworkInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showPcNetworkInterval  ),  CString(  ltoa(  uiShowPcNetworkInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usSndEventLogInterval  !=  uiSndEventLogInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_sndEventLogInterval  ),  CString(  ltoa(  uiSndEventLogInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usSndUsrInfoInterval  !=  uiSndUsrInfoInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_sndUsrInfoInterval  ),  CString(  ltoa(  uiSndUsrInfoInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usSndNetStatInterval  !=  uiSndNetStatInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_sndNetStatInterval  ),  CString(  ltoa(  uiSndNetStatInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usShowProcessInterval  !=  uiShowProcessInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showProcessInterval  ),  CString(  ltoa(  uiShowProcessInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usShowModulesInterval  !=  uiShowModulesInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showModulesInterval  ),  CString(  ltoa(  uiShowModulesInterval,  buf,  10  )  )  );
	if  (  m_var.intervalParams.usShowNetFlowInterval  !=  uiShowNetFlowInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showNetFlowInterval  ),  CString(  ltoa(  uiShowNetFlowInterval,  buf,  10  )  )  );	//  2006/09/12
	if  (  m_var.intervalParams.usShowWindowsUpdatePolicyInterval  !=  uiShowWindowsUpdatePolicyInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showWindowsUpdatePolicyInterval  ),  CString(  ltoa(  uiShowWindowsUpdatePolicyInterval,  buf,  10  )  )  );	//  2006/05/24
	if  (  m_var.intervalParams.usSndPrintersInterval  !=  uiSndPrintersInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_sndPrintersInterval  ),  CString(  ltoa(  uiSndPrintersInterval,  buf,  10  )  )  );	//  2006/12/10
	if  (  m_var.intervalParams.usShowPcNetShareInterval  !=  uiShowPcNetShareInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showPcNetShareInterval  ),  CString(  ltoa(  uiShowPcNetShareInterval,  buf,  10  )  )  );	//  2007/02/20
	if  (  m_var.intervalParams.usShowPcArpInterval  !=  uiShowPcArpInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_showPcArpInterval  ),  CString(  ltoa(  uiShowPcArpInterval,  buf,  10  )  )  );	//  2007/02/20
	//
	if  (  m_var.nProcessQmObjQInterval  !=  nProcessQmObjQInterval  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nProcessQmObjQInterval  ),  CString(  ltoa(  nProcessQmObjQInterval,  buf,  10  )  )  );	//  2006/12/10
	if  (  m_var.nRefreshQmObjQStatusInDb  !=  nRefreshQmObjQStatusInDb  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nRefreshQmObjQStatusInDb  ),  CString(  ltoa(  nRefreshQmObjQStatusInDb,  buf,  10  )  )  );	//  2006/12/10
	if  (  m_var.uiMaxLogs  !=  uiMaxLogs  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_maxLogs  ),  CString(  ltoa(  uiMaxLogs,  buf,  10  )  )  );
	if  (  m_var.nMaxConns  !=  nMaxConns  )  qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nMaxConns  ),  CString(  ltoa(  nMaxConns,  buf,  10  )  )  );

	
	CDialog::OnOK();
}



void CDlgCfgSystemParams::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
