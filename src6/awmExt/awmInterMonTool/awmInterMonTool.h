// awmInterMonTool.h : main header file for the AWMINTERMONTOOL application
//

#if !defined(AFX_AWMINTERMONTOOL_H__1281BCE3_E247_4BD5_9B1A_BD4B2703FAF1__INCLUDED_)
#define AFX_AWMINTERMONTOOL_H__1281BCE3_E247_4BD5_9B1A_BD4B2703FAF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAwmInterMonToolApp:
// See awmInterMonTool.cpp for the implementation of this class
//

class CAwmInterMonToolApp : public CWinApp
{
public:
	CAwmInterMonToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwmInterMonToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAwmInterMonToolApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWMINTERMONTOOL_H__1281BCE3_E247_4BD5_9B1A_BD4B2703FAF1__INCLUDED_)
