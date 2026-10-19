#if !defined(AFX_DLGCFGSWITCHPOLICYGRP_H__D1FD3338_168D_4031_AE19_0933FAFE95D7__INCLUDED_)
#define AFX_DLGCFGSWITCHPOLICYGRP_H__D1FD3338_168D_4031_AE19_0933FAFE95D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgSwitchPolicyGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchPolicyGrp dialog

class CDlgCfgSwitchPolicyGrp : public CDialog
{
// Construction
public:
	CDlgCfgSwitchPolicyGrp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgSwitchPolicyGrp)
	enum { IDD = IDD_cfgSwitchPolicyGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		int							type;
		CWnd					*	pSrcWnd;
		char						policyGrpName[32];
		QY_SNMPPOLICYGRP_RCD		snmpPolicy;
		unsigned  char				ucbChanged;
	}								m_var;


	BOOL bSetDlgInfo(  int  type,  CWnd  *  pSrcWnd,  char  *  policyGrpName  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgSwitchPolicyGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgSwitchPolicyGrp)
	afx_msg void OnSelchangeCOMBOsnmpVer();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSWITCHPOLICYGRP_H__D1FD3338_168D_4031_AE19_0933FAFE95D7__INCLUDED_)
