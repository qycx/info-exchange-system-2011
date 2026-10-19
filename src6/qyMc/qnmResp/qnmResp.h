// qnmResp.h : main header file for the QNMRESP application
//

#if !defined(AFX_QNMRESP_H__744A275A_D381_4BC3_AB42_7FD873E31757__INCLUDED_)
#define AFX_QNMRESP_H__744A275A_D381_4BC3_AB42_7FD873E31757__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CQnmRespApp:
// See qnmResp.cpp for the implementation of this class
//

class CQnmRespApp : public CWinApp
{
public:
	CQnmRespApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQnmRespApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CQnmRespApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QNMRESP_H__744A275A_D381_4BC3_AB42_7FD873E31757__INCLUDED_)
