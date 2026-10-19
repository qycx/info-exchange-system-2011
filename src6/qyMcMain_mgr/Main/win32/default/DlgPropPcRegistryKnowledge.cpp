// DlgPropPcRegistryKnowledge.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPropPcRegistryKnowledge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcRegistryKnowledge dialog


CDlgPropPcRegistryKnowledge::CDlgPropPcRegistryKnowledge(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropPcRegistryKnowledge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropPcRegistryKnowledge)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgPropPcRegistryKnowledge::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  iRootKey,  LPCTSTR  subKey,  LPCTSTR  cfgName,  int  id  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;
 
	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;
	 m_var.iRootKey  =  iRootKey;
	 if  (  subKey  )  lstrcpyn(  m_var.subKey,  subKey,  mycountof(  m_var.subKey  )  );
	 tTrim(  m_var.subKey  );
	 if  (  cfgName  )  lstrcpyn(  m_var.cfgName,  cfgName,  mycountof(  m_var.cfgName  )  );
	 tTrim(  m_var.cfgName  );


	 if  (  !bGetPcRegistryKnowledgeBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.iRootKey,  m_var.subKey,  m_var.cfgName,  id,  &m_var.knowledge  )  )  {
		 memset(  &m_var.knowledge,  0,  sizeof(  m_var.knowledge  )  );
		 m_var.knowledge.iRootKey  =  m_var.iRootKey;
		 if  (  m_var.subKey[0]  )  lstrcpyn(  m_var.knowledge.subKey,  m_var.subKey,  mycountof(  m_var.knowledge.subKey  )  );
		 if  (  m_var.cfgName[0]  )  lstrcpyn(  m_var.knowledge.cfgName,  m_var.cfgName,  mycountof(  m_var.knowledge.cfgName  )  );

	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


void CDlgPropPcRegistryKnowledge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropPcRegistryKnowledge)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropPcRegistryKnowledge, CDialog)
	//{{AFX_MSG_MAP(CDlgPropPcRegistryKnowledge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcRegistryKnowledge message handlers

BOOL CDlgPropPcRegistryKnowledge::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );
	TCHAR			tBuf[1024];
	char			displayBuf[256];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s\\%s"  ),  qyGetDesByType1(  CONST_iRootKeyTable,  m_var.knowledge.iRootKey  ),  m_var.knowledge.subKey,  m_var.knowledge.cfgName  );

	SetDlgItemText(  IDC_EDIT_fileName_prop,  tBuf  );
	SetDlgItemText(  IDC_STATIC_suggestedValVal,  m_var.knowledge.suggestedVal  );
	SetDlgItemText(  IDC_EDIT_name_prop,  m_var.knowledge.name  );
	SetDlgItemText(  IDC_EDIT_des0_prop,  m_var.knowledge.des0  );
	SetDlgItemText(  IDC_EDIT_company_prop,  m_var.knowledge.company  );
	SetDlgItemText(  IDC_EDIT_product_prop,  m_var.knowledge.product  );
	GetDlgItem(  IDC_CHECK_ucbSys  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbSys  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbDaemon  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbDaemon  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbUseNet  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbUseNet    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbHardware  )->SendMessage(  BM_SETCHECK,  	m_var.knowledge.ucbHardware    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_commonErr_prop,  m_var.knowledge.commonErr  );
	SetDlgItemInt(  IDC_EDIT_securityLevel_prop,  m_var.knowledge.securityLevel  );
	GetDlgItem(  IDC_CHECK_ucbSpy  )->SendMessage(  BM_SETCHECK,  	m_var.knowledge.ucbSpy  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbAdvertisement    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbVirus  )->SendMessage(  BM_SETCHECK,  m_var.knowledge.ucbVirus  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbBackDoor  )->SendMessage(  BM_SETCHECK,  	m_var.knowledge.ucbBackDoor   ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_providerName_prop,  m_var.knowledge.provider  );
	SetDlgItemText(  IDC_EDIT_providerAddr_prop,  m_var.knowledge.providerAddr  );
	SetDlgItemText(  IDC_EDIT_providerTime_prop,  m_var.knowledge.providerTime  );
	SetDlgItemText(  IDC_STATIC_auditTime,  CString(  qyDisplayTime(  m_var.knowledge.auditTime,  displayBuf,  sizeof(  displayBuf  )  )  )  );



	GetDlgItem(  IDC_CHECK_ucbSys  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbDaemon  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbUseNet  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbHardware  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbSpy  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbVirus  )->EnableWindow(  FALSE  );
	GetDlgItem(  IDC_CHECK_ucbBackDoor  )->EnableWindow(  FALSE  );




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
