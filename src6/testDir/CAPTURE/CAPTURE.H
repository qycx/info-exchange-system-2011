// capture.h : main header file for the CAPTURE application
//

#if !defined(AFX_CAPTURE_H__110CA6B5_4192_11D4_8E0E_00E04C190D59__INCLUDED_)
#define AFX_CAPTURE_H__110CA6B5_4192_11D4_8E0E_00E04C190D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCaptureApp:
// See capture.cpp for the implementation of this class
//

class CCaptureApp : public CWinApp
{
public:
	CCaptureApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCaptureApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTURE_H__110CA6B5_4192_11D4_8E0E_00E04C190D59__INCLUDED_)
