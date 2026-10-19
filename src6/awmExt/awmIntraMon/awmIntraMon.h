// awmIntraMon.h : main header file for the AWMINTRAMON application
//

#if !defined(AFX_AWMINTRAMON_H__41F56FA9_09F5_4754_B46B_0BC0D6FAA7DE__INCLUDED_)
#define AFX_AWMINTRAMON_H__41F56FA9_09F5_4754_B46B_0BC0D6FAA7DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAwmIntraMonApp:
// See awmIntraMon.cpp for the implementation of this class
//

class CAwmIntraMonApp : public CWinApp
{
public:
	CAwmIntraMonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwmIntraMonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAwmIntraMonApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWMINTRAMON_H__41F56FA9_09F5_4754_B46B_0BC0D6FAA7DE__INCLUDED_)
