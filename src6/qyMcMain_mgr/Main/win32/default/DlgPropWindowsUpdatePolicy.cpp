// DlgPropWindowsUpdatePolicy.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPropWindowsUpdatePolicy.h"
#include	"myDb.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPropWindowsUpdatePolicy dialog


CDlgPropWindowsUpdatePolicy::CDlgPropWindowsUpdatePolicy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropWindowsUpdatePolicy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropWindowsUpdatePolicy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgPropWindowsUpdatePolicy::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;
	 return  TRUE;
 }


void CDlgPropWindowsUpdatePolicy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropWindowsUpdatePolicy)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropWindowsUpdatePolicy, CDialog)
	//{{AFX_MSG_MAP(CDlgPropWindowsUpdatePolicy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropWindowsUpdatePolicy message handlers

//	extern  QY_DMITEM  CONST_AUOptionsTable[];
extern  QY_DMITEM  CONST_ScheduledInstallDayTable[];
extern  QY_DMITEM  CONST_ScheduledInstallTimeTable[];
//	extern  QY_DMITEM  CONST_NoAutoUpdateTable[];
extern  QY_DMITEM  CONST_UseWUServerTable[];
//	extern  QY_DMITEM  CONST_RescheduleWaitTimeEnabledTable[];
//	extern  QY_DMITEM  CONST_NoAutoRebootWithLoggedOnUsersTable[];
//	extern  QY_DMITEM  CONST_DetectionFrequencyEnabledTable[];
//	extern  QY_DMITEM  CONST_ElevateNonAdminsTable[];
//	extern  QY_DMITEM  CONST_TargetGroupEnabledTable[];
/*

*/

BOOL CDlgPropWindowsUpdatePolicy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int							iErr	=	-1;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	QY_PCADAPTER_RCD			rcd;
	QNM_PC_INFO					pcInfo;
	QNM_REG_INFO				regInfo;
	QY_PCNETWORK_PROPU			prop;
	CString						str;


	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	
	memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );
	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	if  (  !bGetPcAdapterRcdBySth(  m_var.pObjDb->pDb,  0,  0,  NULL,  NULL,  0,  NULL,  NULL,  m_var.id,  &rcd  )  )  memset(  &rcd,  0,  sizeof(  rcd  )  );
	if  (  !g_dbFuncs.pf_bGetPcInfoByMac(  m_var.pObjDb->pDb,  rcd.mac0,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	GetWindowText(  str  );
	if  (  !rcd.ucbRule  )  SetWindowText(  str  +  _T(  " - ×´Ì¬"  )  );
	else  SetWindowText(  str  +  _T(  " - ²ßÂÔ"  )  );
	
	memset(  &prop,  0,  sizeof(  prop  )  );
	pcNetworkRcd2Prop(  &rcd,  &prop  );

	/*

	for  (  pItem  =  CONST_fillRegInfoTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 idc  =  pItem->type;  fieldId  =  (  int  )pItem->des;	
		 SetDlgItemText(  idc,  CString(  (  TCHAR  *  )regInfo.u.cols[getRegIndexByFieldId(  fieldId  )]  )  );
	}
	SetDlgItemText(  IDC_STATIC_ip,  CString(  pcInfo.ip  )  );
	SetDlgItemText(  IDC_STATIC_pcNetworkPropType,  CString(  qyGetDesByType1(  CONST_pcCommTypeTable,  rcd.uiType  )  )  );
	SetDlgItemText(  IDC_STATIC_des,  CString(  rcd.deses[0]  )  );
	SetDlgItemText(  IDC_STATIC_devDesc,  CString(  rcd.devDesc  )  );
	SetDlgItemText(  IDC_STATIC_mac,  CString(  rcd.mac  )  );

	*/

	if  (  prop.windowsUpdatePolicy.AutoUpdate_AUOptions  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_AUOptions_autoUpdate,	qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_AUOptionsTable  ),  prop.windowsUpdatePolicy.AutoUpdate_AUOptions  )  );
	if  (  prop.windowsUpdatePolicy.AutoUpdate_ScheduledInstallDay  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_ScheduledInstallDay_autoUpdate,	qyGetDesByType1(  CONST_ScheduledInstallDayTable,  prop.windowsUpdatePolicy.AutoUpdate_ScheduledInstallDay  )  );
	if  (  prop.windowsUpdatePolicy.AutoUpdate_ScheduledInstallTime  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_ScheduledInstallTime_autoUpdate,	qyGetDesByType1(  CONST_ScheduledInstallTimeTable,  prop.windowsUpdatePolicy.AutoUpdate_ScheduledInstallTime  )  );
	//
	GetDlgItem(  IDC_RADIO_ucbWSusPolicyExists  )->SendMessage(  BM_SETCHECK,  prop.windowsUpdatePolicy.AUOptions  !=  CONST_dwRegVal_invalid  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	if  (  prop.windowsUpdatePolicy.NoAutoUpdate  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_NoAutoUpdate,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_NoAutoUpdateTable  ),  prop.windowsUpdatePolicy.NoAutoUpdate  )  );
	if  (  prop.windowsUpdatePolicy.AUOptions  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_AUOptions,		qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_AUOptionsTable  ),  prop.windowsUpdatePolicy.AUOptions  )  );
	if  (  prop.windowsUpdatePolicy.ScheduledInstallDay  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_ScheduledInstallDay,		qyGetDesByType1(  CONST_ScheduledInstallDayTable,  prop.windowsUpdatePolicy.ScheduledInstallDay  )  );
	if  (  prop.windowsUpdatePolicy.ScheduledInstallTime  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_ScheduledInstallTime,	qyGetDesByType1(  CONST_ScheduledInstallTimeTable,  prop.windowsUpdatePolicy.ScheduledInstallTime  )  );
	if  (  prop.windowsUpdatePolicy.UseWUServer  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_UseWUServer,		qyGetDesByType1(  CONST_UseWUServerTable,  prop.windowsUpdatePolicy.UseWUServer  )  );
	SetDlgItemText(  IDC_STATIC_WUServer,						CString(  prop.windowsUpdatePolicy.WUServer  )  );
	SetDlgItemText(  IDC_STATIC_WUStatusServer,					CString(  prop.windowsUpdatePolicy.WUStatusServer  )  );
	if  (  prop.windowsUpdatePolicy.RescheduleWaitTimeEnabled  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_RescheduleWaitTimeEnabled,		qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_RescheduleWaitTimeEnabledTable  ),  prop.windowsUpdatePolicy.RescheduleWaitTimeEnabled  )  );
	if  (  prop.windowsUpdatePolicy.RescheduleWaitTime  !=  CONST_dwRegVal_invalid  )  SetDlgItemInt(  IDC_STATIC_RescheduleWaitTime,				prop.windowsUpdatePolicy.RescheduleWaitTime  );
	if  (  prop.windowsUpdatePolicy.NoAutoRebootWithLoggedOnUsers  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_NoAutoRebootWithLoggedOnUsers,	qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_NoAutoRebootWithLoggedOnUsersTable  ),  prop.windowsUpdatePolicy.NoAutoRebootWithLoggedOnUsers  )  );
	if  (  prop.windowsUpdatePolicy.DetectionFrequencyEnabled  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_DetectionFrequencyEnabled,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_DetectionFrequencyEnabledTable  ),  prop.windowsUpdatePolicy.DetectionFrequencyEnabled  )  );
	if  (  prop.windowsUpdatePolicy.DetectionFrequency  !=  CONST_dwRegVal_invalid  )  SetDlgItemInt(  IDC_STATIC_DetectionFrequency,  prop.windowsUpdatePolicy.DetectionFrequency  );
	if  (  prop.windowsUpdatePolicy.ElevateNonAdmins  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_ElevateNonAdmins,			qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ElevateNonAdminsTable  ),  prop.windowsUpdatePolicy.ElevateNonAdmins  )  );
	if  (  prop.windowsUpdatePolicy.TargetGroupEnabled  !=  CONST_dwRegVal_invalid  )  SetDlgItemText(  IDC_STATIC_TargetGroupEnabled,		qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_TargetGroupEnabledTable  ),	prop.windowsUpdatePolicy.TargetGroupEnabled  )  );
	SetDlgItemText(  IDC_STATIC_TargetGroup,					CString(  prop.windowsUpdatePolicy.TargetGroup  )  );
	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
