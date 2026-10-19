// kk.h : main header file for the KK application
//

#if !defined(AFX_KK_H__8E63A601_EB8E_4ED2_8EAC_AA368FD1F3EB__INCLUDED_)
#define AFX_KK_H__8E63A601_EB8E_4ED2_8EAC_AA368FD1F3EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CKkApp:
// See kk.cpp for the implementation of this class
//

class CKkApp : public CWinApp
{
public:
	CKkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKkApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CKkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KK_H__8E63A601_EB8E_4ED2_8EAC_AA368FD1F3EB__INCLUDED_)
