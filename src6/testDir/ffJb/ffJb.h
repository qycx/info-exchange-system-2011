// ffJb.h : main header file for the FFJB application
//

#if !defined(AFX_FFJB_H__BA9A6196_11D7_4E25_823B_A3EAA435722F__INCLUDED_)
#define AFX_FFJB_H__BA9A6196_11D7_4E25_823B_A3EAA435722F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFfJbApp:
// See ffJb.cpp for the implementation of this class
//

class CFfJbApp : public CWinApp
{
public:
	CFfJbApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFfJbApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFfJbApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFJB_H__BA9A6196_11D7_4E25_823B_A3EAA435722F__INCLUDED_)
