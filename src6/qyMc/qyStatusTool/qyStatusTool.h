// qyStatusTool.h : main header file for the QYSTATUSTOOL application
//

#if !defined(AFX_QYSTATUSTOOL_H__344D5BDC_1F3C_4D46_B91E_710D33DE48AD__INCLUDED_)
#define AFX_QYSTATUSTOOL_H__344D5BDC_1F3C_4D46_B91E_710D33DE48AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQyStatusToolApp:
// See qyStatusTool.cpp for the implementation of this class
//



class CQyStatusToolApp : public CWinApp
{
public:
	CQyStatusToolApp();

	//  QY_STATUS_STRUCT	m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyStatusToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQyStatusToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYSTATUSTOOL_H__344D5BDC_1F3C_4D46_B91E_710D33DE48AD__INCLUDED_)
