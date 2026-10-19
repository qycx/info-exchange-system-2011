#if !defined(AFX_DLGPOLICYIMAUTHCOND_H__081A0C48_08AB_43FD_ACC7_07A0A6A3A248__INCLUDED_)
#define AFX_DLGPOLICYIMAUTHCOND_H__081A0C48_08AB_43FD_ACC7_07A0A6A3A248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPolicyImAuthCond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyImAuthCond dialog

class CDlgPolicyImAuthCond : public CDialog
{
// Construction
public:
	CDlgPolicyImAuthCond(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPolicyImAuthCond)
	enum { IDD = IDD_policy_imAuthCond };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct						{
		POLICY_imAuthCond		policy;
	}							m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPolicyImAuthCond)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPolicyImAuthCond)
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

#endif // !defined(AFX_DLGPOLICYIMAUTHCOND_H__081A0C48_08AB_43FD_ACC7_07A0A6A3A248__INCLUDED_)
