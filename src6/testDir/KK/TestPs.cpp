// TestPs.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "TestPs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPs

IMPLEMENT_DYNAMIC(CTestPs, CPropertySheet)

CTestPs::CTestPs(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CTestPs::CTestPs(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CTestPs::~CTestPs()
{
}


BEGIN_MESSAGE_MAP(CTestPs, CPropertySheet)
	//{{AFX_MSG_MAP(CTestPs)
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPs message handlers

BOOL CTestPs::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	 COPYDATASTRUCT	*	pCopyData  =  (  COPYDATASTRUCT  *  )pCopyDataStruct;
	 int				len;
	 

	 len  =  min(  sizeof(  m_var.buf  )  -  1,  pCopyData->cbData  );
	 memcpy(  m_var.buf, pCopyData->lpData, len  );
	 m_var.buf[len]  =  0;	 
	 //  m_wndStatusBar.SetPaneText(  0,  m_hintFromCopyData,  TRUE  );
	 //  SetDlgItemText(  IDC_STATIC_status,  m_var.buf  );
	 GetActivePage(  )->SetDlgItemText(  IDC_STATIC_status,  m_var.buf  );
	
	return CPropertySheet::OnCopyData(pWnd, pCopyDataStruct);
}
