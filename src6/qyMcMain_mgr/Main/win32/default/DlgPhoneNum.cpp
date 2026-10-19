// DlgPhoneNum.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgPhoneNum.h"
#include	"DlgQnmCfgRasOptions.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPhoneNum dialog


CDlgPhoneNum::CDlgPhoneNum(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPhoneNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPhoneNum)
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


void CDlgPhoneNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPhoneNum)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPhoneNum, CDialog)
	//{{AFX_MSG_MAP(CDlgPhoneNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPhoneNum message handlers

BOOL  CDlgPhoneNum::bSetDlgInfo(  CWnd  *  pParent  )
{
	m_var.pParent  =  pParent;
	return  0;
}

void CDlgPhoneNum::OnOK() 
{
	int			i;
	char		buf[256]  =  "";
	CString		str;
	QY_MC	*	pQyMc		=	QY_GET_GBUF(  );
	
	GetDlgItemText(  IDC_EDIT_phoneNum,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	qyTrim(  buf  );
	if  (  !buf[0]  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotBeEmpty  )  );
		return;
	}
	if  (  strlen(  buf  )  >  CONST_phoneNumBytes  )  {
		qyShowHint(  _T(  "%s : [ 1 - %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  CONST_phoneNumBytes  );
		return;
	}
	for  (  i  =  0;  i  <  (  int  )strlen(  buf  );  i  ++  )  {
		 if  (  !qyIsDigit(  buf[i]  )  &&  !qyIsSpace(  buf[i]  )  &&  buf[i]  !=  ','  )  {
			 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_numberIsWrong  )  );
			 return;
		 }
	}
	
	if  (  m_var.pParent  )  {
		CDlgQnmCfgRasOptions	*	pDlg	=	(  CDlgQnmCfgRasOptions  *  )m_var.pParent;
		CListBox				*	pLb		=	(  CListBox  *  )pDlg->GetDlgItem(  IDC_LIST_permittedPhoneNums  );
		CString						tmpCStr;
		
		for  (  i  =  0;  i  <  pLb->GetCount(  );  i  ++  )  {
			 pLb->GetText(  i,  tmpCStr  );
			 if  (  !tmpCStr.Compare(  CString(  buf  )  )  )  break;
		}
		if  (  i  <  pLb->GetCount(  )  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfReinput  )  );
			return;
		}
	}

	safeStrnCpy(  buf,  m_var.phoneNum,  sizeof(  m_var.phoneNum  )  );
	
	CDialog::OnOK();
}

BOOL CDlgPhoneNum::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	QY_MC	*		pQyMc		=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	SetDlgItemText(  IDC_STATIC_phoneNum,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_phoneNum  )  );
	SetDlgItemText(  IDOK,  getResStr(  0,  &pQyMc->cusRes,  IDOK  )  );  
	SetDlgItemText(  IDCANCEL,  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  )  );  

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
