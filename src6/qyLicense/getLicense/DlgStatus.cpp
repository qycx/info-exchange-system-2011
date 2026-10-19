// DlgStatus.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "DlgStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStatus dialog


CDlgStatus::CDlgStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgStatus)
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStatus message handlers

BOOL CDlgStatus::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	 COPYDATASTRUCT	*	pCopyData  =  (  COPYDATASTRUCT  *  )pCopyDataStruct;
	 int				len;
	 

	 len  =  min(  sizeof(  m_var.buf  )  -  1,  pCopyData->cbData  );
	 memcpy(  m_var.buf, pCopyData->lpData, len  );
	 m_var.buf[len]  =  0;	 
	 //  m_wndStatusBar.SetPaneText(  0,  m_hintFromCopyData,  TRUE  );
	 SetDlgItemText(  IDC_STATIC_status,  m_var.buf  );

	 return  0;

}
