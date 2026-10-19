// awmInterMon.h : main header file for the AWMINTERMON application
//

#if !defined(AFX_AWMINTERMON_H__92015B84_74AE_40C1_994B_058D65EB34BB__INCLUDED_)
#define AFX_AWMINTERMON_H__92015B84_74AE_40C1_994B_058D65EB34BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAwmInterMonApp:
// See awmInterMon.cpp for the implementation of this class
//

class CAwmInterMonApp : public CWinApp
{
public:
	CAwmInterMonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwmInterMonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAwmInterMonApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWMINTERMON_H__92015B84_74AE_40C1_994B_058D65EB34BB__INCLUDED_)
