// awmChkSecurity.h : main header file for the AWMCHKSECURITY application
//

#if !defined(AFX_AWMCHKSECURITY_H__548382E5_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_)
#define AFX_AWMCHKSECURITY_H__548382E5_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAwmChkSecurityApp:
// See awmChkSecurity.cpp for the implementation of this class
//

class CAwmChkSecurityApp : public CWinApp
{
public:
	CAwmChkSecurityApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwmChkSecurityApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAwmChkSecurityApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWMCHKSECURITY_H__548382E5_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_)
