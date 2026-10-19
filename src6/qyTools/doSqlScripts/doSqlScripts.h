// doSqlScripts.h : main header file for the DOSQLSCRIPTS application
//

#if !defined(AFX_DOSQLSCRIPTS_H__ED7FEEE1_C44B_4A20_9EB4_746B80C6271B__INCLUDED_)
#define AFX_DOSQLSCRIPTS_H__ED7FEEE1_C44B_4A20_9EB4_746B80C6271B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDoSqlScriptsApp:
// See doSqlScripts.cpp for the implementation of this class
//

class CDoSqlScriptsApp : public CWinApp
{
public:
	CDoSqlScriptsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoSqlScriptsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDoSqlScriptsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSQLSCRIPTS_H__ED7FEEE1_C44B_4A20_9EB4_746B80C6271B__INCLUDED_)
