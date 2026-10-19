#if !defined(AFX_PS_H__3F05AC8D_8BD4_48D7_A85F_6126FC991B2A__INCLUDED_)
#define AFX_PS_H__3F05AC8D_8BD4_48D7_A85F_6126FC991B2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPs

class CPs : public CPropertySheet
{
	DECLARE_DYNAMIC(CPs)

// Construction
public:
	CPs(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPs(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPs)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPs();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPs)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnOK(  );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PS_H__3F05AC8D_8BD4_48D7_A85F_6126FC991B2A__INCLUDED_)
