// DlgMcHint.cpp : implementation file
//

#include "stdafx.h"
#include "qyMcMainCommon.h"
#include	"myresource.h"
#include "DlgMcHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMcHint dialog


CDlgMcHint::CDlgMcHint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMcHint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMcHint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &var,  0,  sizeof(  var )  );

}

 int  CDlgMcHint::setDlgInfo(  int  x,  int  y,  char  *  hint  )
{
	 int	len	=	min(  strlen( hint ), sizeof(  var.hintBuf  ) - 1  );
	 var.x  =  x;
	 var.y  =  y;
	 memcpy(  var.hintBuf,  hint,  len  );
	 var.hintBuf[len]  =  0;

	 return  0;
}

void CDlgMcHint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMcHint)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMcHint, CDialog)
	//{{AFX_MSG_MAP(CDlgMcHint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMcHint message handlers

BOOL CDlgMcHint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	RECT	rc;

	::GetWindowRect(  this->m_hWnd, &rc  );
	::SetWindowPos(  this->m_hWnd,  HWND_TOPMOST, var.x, var.y, rc.right - rc.left,  rc.bottom - rc.top,  SWP_NOSIZE  );

	SetDlgItemText(  IDC_HINT,  CString(  var.hintBuf  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


