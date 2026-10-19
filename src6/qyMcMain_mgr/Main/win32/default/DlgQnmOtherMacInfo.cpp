// DlgQnmOtherMacInfo.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgQnmOtherMacInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmOtherMacInfo dialog


CDlgQnmOtherMacInfo::CDlgQnmOtherMacInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmOtherMacInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmOtherMacInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgQnmOtherMacInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmOtherMacInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmOtherMacInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmOtherMacInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmOtherMacInfo message handlers

 BOOL  CDlgQnmOtherMacInfo::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMacValid(  mac  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	safeStrnCpy(  mac,  m_var.mac,  sizeof(  m_var.mac  )  );
	return  TRUE;
}


BOOL CDlgQnmOtherMacInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	QNM_MACDES_RCD			macDes;
	char					buf[256];
	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return  FALSE;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	// TODO: Add extra initialization here
	memset(  &macDes,  0,  sizeof(  macDes  )  );
	if  (  !bGetMacDesByMac(  m_var.pObjDb->pDb,  m_var.mac,  &macDes  )  )  memset(  &macDes,  0,  sizeof(  macDes  )  ); 
	_snprintf(  buf,  sizeof(  buf  ),  "%s %s",  macDes.devType,  macDes.des0  );
	SetDlgItemText(  IDC_STATIC_netDevType,  CString(  buf  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
