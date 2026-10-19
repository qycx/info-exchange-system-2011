// qyMcDaemon.h : main header file for the QYMCDAEMON application
//

#if !defined(AFX_QYMCDAEMON_H__190C8986_989C_43D5_9749_015F22D6F931__INCLUDED_)
#define AFX_QYMCDAEMON_H__190C8986_989C_43D5_9749_015F22D6F931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CQyMcDaemonApp:
// See qyMcDaemon.cpp for the implementation of this class
//

class CQyMcDaemonApp : public CWinApp
{
public:
	CQyMcDaemonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyMcDaemonApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CQyMcDaemonApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYMCDAEMON_H__190C8986_989C_43D5_9749_015F22D6F931__INCLUDED_)
