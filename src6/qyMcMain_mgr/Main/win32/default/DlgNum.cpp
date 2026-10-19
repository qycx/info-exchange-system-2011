// DlgNum.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"QyRestrictEdit.h"
#include	"qymc.h"
#include	"DlgNum.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNum dialog


CDlgNum::CDlgNum(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.maxBytes  =  3;
}


void CDlgNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNum)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNum, CDialog)
	//{{AFX_MSG_MAP(CDlgNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNum message handlers

 BOOL  CDlgNum::bSetDlgInfo(  int  type,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  hint,  LPCTSTR  okName,  LPCTSTR  cancelName,  unsigned  int  maxBytes  )
{
	 m_var.type  =  type;
	 m_var.hParent  =  hParent;
	 if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	 if  (  hint  )  lstrcpyn(  m_var.hint,  hint,  mycountof(  m_var.hint  )  );
	 if  (  okName  )  lstrcpyn(  m_var.okName,  okName,  mycountof(  m_var.okName  )  );
	 if  (  cancelName  )  lstrcpyn(  m_var.cancelName,  cancelName,  mycountof(  m_var.cancelName  )  );
	 if  (  maxBytes  )  m_var.maxBytes  =  maxBytes;
	 
	 return  TRUE;
}

 BOOL  CDlgNum::bSetVal(  int  n  )
{
	 m_var.n  =  n;
	 m_var.ucbValSet  =  TRUE;
	 return  0;
}

 BOOL  CDlgNum::bSetMax(  int  iMaxVal  )
{
	 m_var.iMaxVal  =  iMaxVal;
	 m_var.ucbMax  =  TRUE;
	 return  TRUE;
}

 BOOL  CDlgNum::bSetMin(  int  iMinVal  )
{
	 m_var.iMinVal  =  iMinVal;
	 m_var.ucbMin  =  TRUE;
	 return  TRUE;
}

BOOL CDlgNum::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(  CString(  m_var.title  )  );
	SetDlgItemText(  IDC_STATIC_hint,  CString(  m_var.hint  )  );
	SetDlgItemText(  IDOK,  CString(  m_var.okName  )  );
	SetDlgItemText(  IDCANCEL,  CString(  m_var.cancelName  )  );
	
	int		idc;
	int		cnt			=	0;
	
	idc  =  IDC_EDIT_num;
	m_edits[cnt].setType(  CONST_qyEditType_custom,  CONST_qyIdcFlgPermitDigit,  NULL  );
	m_edits[cnt].SubclassDlgItem(  idc,  this  );
	GetDlgItem(  idc  )->SendMessage(  EM_SETLIMITTEXT,  m_var.maxBytes,  0  );
	if  (  m_var.ucbValSet  )  SetDlgItemInt(  idc,  m_var.n  );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNum::OnOK() 
{
	// TODO: Add extra validation here
	char		buf[32];
	CString		str;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	GetDlgItemText(  IDC_EDIT_num,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );
	m_var.n  =  atol(  buf  );

	if  (  m_var.ucbMax  &&  m_var.n  >  m_var.iMaxVal  )  {
		qyShowHint(  _T(  "%s : [ maximum is %d ]"  ),  getResStr(  0, &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  m_var.iMaxVal  );  return;
	}
	if  (  m_var.ucbMin  &&  m_var.n  <  m_var.iMinVal  )  {
		qyShowHint(  _T(  "%s : [ minimum is %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  m_var.iMinVal  );  return;
	}
	
	CDialog::OnOK();
}

