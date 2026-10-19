#if !defined(AFX_MAINCLIENT_H__F901090C_ED8C_4915_9336_BECCCBF3E826__INCLUDED_)
#define AFX_MAINCLIENT_H__F901090C_ED8C_4915_9336_BECCCBF3E826__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainClient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainClient window

class CMainClient : public CWnd
{
// Construction
public:
	CMainClient();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainClient)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainClient();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainClient)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINCLIENT_H__F901090C_ED8C_4915_9336_BECCCBF3E826__INCLUDED_)
