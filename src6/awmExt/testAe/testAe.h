// testAe.h : main header file for the TESTAE application
//

#if !defined(AFX_TESTAE_H__5DB2EE47_D39F_499B_95CE_6A113D0A32E5__INCLUDED_)
#define AFX_TESTAE_H__5DB2EE47_D39F_499B_95CE_6A113D0A32E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestAeApp:
// See testAe.cpp for the implementation of this class
//

class CTestAeApp : public CWinApp
{
public:
	CTestAeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestAeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAE_H__5DB2EE47_D39F_499B_95CE_6A113D0A32E5__INCLUDED_)
