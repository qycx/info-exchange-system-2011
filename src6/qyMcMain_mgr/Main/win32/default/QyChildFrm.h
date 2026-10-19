#if !defined(AFX_QYCHILDFRM_H__D8B1818B_646C_4F00_A9AC_0D86BB0ACB03__INCLUDED_)
#define AFX_QYCHILDFRM_H__D8B1818B_646C_4F00_A9AC_0D86BB0ACB03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyChildFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQyChildFrm frame

class CQyChildFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CQyChildFrm)
protected:
	CQyChildFrm();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyChildFrm)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CMDIFrameWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQyChildFrm();

	// Generated message map functions
	//{{AFX_MSG(CQyChildFrm)
	//}}AFX_MSG
	afx_msg  LRESULT  OnQyComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyPostComm( WPARAM, LPARAM );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYCHILDFRM_H__D8B1818B_646C_4F00_A9AC_0D86BB0ACB03__INCLUDED_)
