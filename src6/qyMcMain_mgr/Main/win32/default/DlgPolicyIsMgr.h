#if !defined(AFX_DLGPOLICYISMGR_H__F40C2370_BC9A_4474_B7BE_C08809FB4F1A__INCLUDED_)
#define AFX_DLGPOLICYISMGR_H__F40C2370_BC9A_4474_B7BE_C08809FB4F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPolicyIsMgr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyIsMgr dialog

class CDlgPolicyIsMgr : public CDialog
{
// Construction
public:
	CDlgPolicyIsMgr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPolicyIsMgr)
	enum { IDD = IDD_policy_isMgr };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct					{
		POLICY_isMgr		policy;
	}						m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPolicyIsMgr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPolicyIsMgr)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOLICYISMGR_H__F40C2370_BC9A_4474_B7BE_C08809FB4F1A__INCLUDED_)
