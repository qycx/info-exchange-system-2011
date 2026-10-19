// DlgPcAssetProperties.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPcAssetProperties.h"
#include	"myDb.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPcAssetProperties dialog


CDlgPcAssetProperties::CDlgPcAssetProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPcAssetProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPcAssetProperties)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgPcAssetProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPcAssetProperties)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPcAssetProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgPcAssetProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPcAssetProperties message handlers

 BOOL  CDlgPcAssetProperties::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	
	m_var.pObjDb  =  pObjDb;
	m_var.id  =  id;
	if  (  !bGetPcAssetInfoById(  m_var.pObjDb->pDb,  m_var.id,  &m_var.pcAsset  )  )  return  FALSE;
	return  TRUE;
}


BOOL CDlgPcAssetProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	TCHAR		tBuf[256];
	char		buf[256];

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return  FALSE;	//  2007/01/03


	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	
	if  (  !g_dbFuncs.pf_bGetPcInfoByMac(  m_var.pObjDb->pDb,  m_var.pcAsset.mac0,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &m_var.pcInfo,  &m_var.regInfo  )  )  {
		memset(  &m_var.pcInfo,  0,  sizeof(  m_var.pcInfo  )  );
		memset(  &m_var.regInfo,  0,  sizeof(  m_var.regInfo  )  );
	}
		
	SetDlgItemText(  IDC_STATIC_col2,	CString(  (  TCHAR  *  )m_var.regInfo.u.cols[2]  )  );
	SetDlgItemText(  IDC_STATIC_col3,	CString(  (  TCHAR  *  )m_var.regInfo.u.cols[3]  )  );
	SetDlgItemText(  IDC_STATIC_col4,	CString(  (  TCHAR  *  )m_var.regInfo.u.cols[4]  )  );
	SetDlgItemText(  IDC_STATIC_ip,		CString(  m_var.pcInfo.ip  )  );
	SetDlgItemText(  IDC_STATIC_mac0,	CString(  m_var.pcAsset.mac0  )  );
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s(%s)"  ),  qyGetDesByType1(  CONST_qyPlatformTable,  m_var.pcAsset.iPlatformId  ),  CString(  m_var.pcAsset.winDir  )  );
	SetDlgItemText(  IDC_STATIC_env,  CString(  tBuf  )  );

	SetDlgItemText(  IDC_STATIC_assetType,  CString(  qyGetDesByType1(  CONST_assetTypeTable,  m_var.pcAsset.uiType  )  )  );
	SetDlgItemText(  IDC_STATIC_name,  CString(  m_var.pcAsset.name  )  );
	SetDlgItemText(  IDC_STATIC_des0,  CString(  m_var.pcAsset.deses[0]  )  );
	SetDlgItemText(  IDC_STATIC_startTime,  CString(  qyDisplayTime(  m_var.pcAsset.startTime,  buf,  sizeof(  buf  )  )  )  );
	SetDlgItemText(  IDC_STATIC_endTime,  CString(  qyDisplayTime(  m_var.pcAsset.endTime,  buf,  sizeof(  buf  )  )  )  );
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
