// qrtReserved.h : main header file for the QRTRESERVED application
//

#if !defined(AFX_QRTRESERVED_H__01A7E5B0_D1FD_4D53_9E69_E62487CDCB0E__INCLUDED_)
#define AFX_QRTRESERVED_H__01A7E5B0_D1FD_4D53_9E69_E62487CDCB0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQrtReservedApp:
// See qrtReserved.cpp for the implementation of this class
//

class CQrtReservedApp : public CWinApp
{
public:
	CQrtReservedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQrtReservedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQrtReservedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QRTRESERVED_H__01A7E5B0_D1FD_4D53_9E69_E62487CDCB0E__INCLUDED_)
