#if !defined(AFX_DLGCFGSWITCHDEFAULTPOLICYGRP_H__E1728F39_38FF_43E0_8F89_16214B318711__INCLUDED_)
#define AFX_DLGCFGSWITCHDEFAULTPOLICYGRP_H__E1728F39_38FF_43E0_8F89_16214B318711__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgSwitchDefaultPolicyGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchDefaultPolicyGrp dialog

class CDlgCfgSwitchDefaultPolicyGrp : public CDialog
{
// Construction
public:
	CDlgCfgSwitchDefaultPolicyGrp(CWnd* pParent = NULL);   // standard constructor

	struct						{
		QY_SNMPOBJPOLICY_RCD	policy;
	}							m_var;

// Dialog Data
	//{{AFX_DATA(CDlgCfgSwitchDefaultPolicyGrp)
	enum { IDD = IDD_cfgSwitchDefaultPolicyGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgSwitchDefaultPolicyGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgSwitchDefaultPolicyGrp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSWITCHDEFAULTPOLICYGRP_H__E1728F39_38FF_43E0_8F89_16214B318711__INCLUDED_)
