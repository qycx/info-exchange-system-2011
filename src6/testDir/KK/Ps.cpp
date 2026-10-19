// Ps.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "Ps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPs

IMPLEMENT_DYNAMIC(CPs, CPropertySheet)

CPs::CPs(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPs::CPs(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPs::~CPs()
{
}


BEGIN_MESSAGE_MAP(CPs, CPropertySheet)
	//{{AFX_MSG_MAP(CPs)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPs message handlers


void  CPs::OnOK( )
{

	CPs::EndDialog(  IDD_P1  );
	return;
}