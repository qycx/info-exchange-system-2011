#if !defined(AFX_TESTPS_H__085C988D_A77F_420A_8E72_338D69A5AD39__INCLUDED_)
#define AFX_TESTPS_H__085C988D_A77F_420A_8E72_338D69A5AD39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestPs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestPs

class CTestPs : public CPropertySheet
{
	DECLARE_DYNAMIC(CTestPs)

// Construction
public:
	CTestPs(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTestPs(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	struct		{
		char	buf[1024];
	}			m_var;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPs)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestPs();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestPs)
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPS_H__085C988D_A77F_420A_8E72_338D69A5AD39__INCLUDED_)
