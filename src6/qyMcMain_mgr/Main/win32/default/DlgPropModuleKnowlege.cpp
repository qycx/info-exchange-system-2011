// DlgPropModuleKnowlege.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgPropModuleKnowlege.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPropModuleKnowlege dialog


CDlgPropModuleKnowlege::CDlgPropModuleKnowlege(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropModuleKnowlege::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropModuleKnowlege)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgPropModuleKnowlege::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  fileName,  LPCTSTR  cmdLine,  int  id  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
 
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;
	 if  (  fileName  )  lstrcpyn(  m_var.fileName,  fileName,  mycountof(  m_var.fileName  )  );
	 tTrim(  m_var.fileName  );
	 if  (  cmdLine  )  lstrcpyn(  m_var.cmdLine,  cmdLine,  mycountof(  m_var.cmdLine  )  );
	 tTrim(  m_var.cmdLine  );

	 if  (  !bGetPcModuleKnowledgeBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.fileName,  m_var.cmdLine,  id,  &m_var.moduleKnowlege  )  )  {
		 memset(  &m_var.moduleKnowlege,  0,  sizeof(  m_var.moduleKnowlege  )  );
		 if  (  m_var.fileName[0]  )  lstrcpyn(  m_var.moduleKnowlege.fileName,  m_var.fileName,  mycountof(  m_var.moduleKnowlege.fileName  )  );
		 if  (  m_var.cmdLine[0]  )  lstrcpyn(  m_var.moduleKnowlege.cmdLine,  m_var.cmdLine,  mycountof(  m_var.cmdLine  )  );
	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


void CDlgPropModuleKnowlege::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropModuleKnowlege)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropModuleKnowlege, CDialog)
	//{{AFX_MSG_MAP(CDlgPropModuleKnowlege)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropModuleKnowlege message handlers

BOOL CDlgPropModuleKnowlege::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );
	char			displayBuf[256];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	

	SetDlgItemText(  IDC_EDIT_fileName_prop,  m_var.moduleKnowlege.fileName  );
	SetDlgItemText(  IDC_EDIT_cmdLine_prop,  m_var.moduleKnowlege.cmdLine  );
	SetDlgItemText(  IDC_EDIT_name_prop,  m_var.moduleKnowlege.name  );
	SetDlgItemText(  IDC_EDIT_des0_prop,  m_var.moduleKnowlege.des0  );
	SetDlgItemText(  IDC_EDIT_company_prop,  m_var.moduleKnowlege.company  );
	SetDlgItemText(  IDC_EDIT_product_prop,  m_var.moduleKnowlege.product  );
	GetDlgItem(  IDC_CHECK_ucbSys  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbSys  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbDaemon  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbDaemon  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbUseNet  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbUseNet    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbHardware  )->SendMessage(  BM_SETCHECK,  	m_var.moduleKnowlege.ucbHardware    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_commonErr_prop,  m_var.moduleKnowlege.commonErr  );
	SetDlgItemText(  IDC_EDIT_memInfo_prop,  m_var.moduleKnowlege.memInfo  );
	SetDlgItemInt(  IDC_EDIT_securityLevel_prop,  m_var.moduleKnowlege.securityLevel  );
	GetDlgItem(  IDC_CHECK_ucbSpy  )->SendMessage(  BM_SETCHECK,  	m_var.moduleKnowlege.ucbSpy  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbAdvertisement  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbAdvertisement    ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbVirus  )->SendMessage(  BM_SETCHECK,  m_var.moduleKnowlege.ucbVirus  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	GetDlgItem(  IDC_CHECK_ucbBackDoor  )->SendMessage(  BM_SETCHECK,  	m_var.moduleKnowlege.ucbBackDoor   ?  BST_CHECKED  :  BST_UNCHECKED,  0  );
	SetDlgItemText(  IDC_EDIT_providerName_prop,  m_var.moduleKnowlege.provider  );
	SetDlgItemText(  IDC_EDIT_providerAddr_prop,  m_var.moduleKnowlege.providerAddr  );
	SetDlgItemText(  IDC_EDIT_providerTime_prop,  m_var.moduleKnowlege.providerTime  );
	SetDlgItemText(  IDC_STATIC_auditTime,  CString(  qyDisplayTime(  m_var.moduleKnowlege.auditTime,  displayBuf,  sizeof(  displayBuf  )  )  )  );



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
	
