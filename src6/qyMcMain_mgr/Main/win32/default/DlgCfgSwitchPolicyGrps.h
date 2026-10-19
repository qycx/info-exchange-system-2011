#if !defined(AFX_DLGCFGSWITCHPOLICYGRPS_H__1E871A59_FBE0_4015_BF24_F032F915D077__INCLUDED_)
#define AFX_DLGCFGSWITCHPOLICYGRPS_H__1E871A59_FBE0_4015_BF24_F032F915D077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgSwitchPolicyGrps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSwitchPolicyGrps dialog

class CDlgCfgSwitchPolicyGrps : public CDialog
{
// Construction
public:
	CDlgCfgSwitchPolicyGrps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgSwitchPolicyGrps)
	enum { IDD = IDD_cfgSwitchPolicyGrps };
	CListCtrl	m_lv;
	//}}AFX_DATA

	struct								{
		int								idcList;
		char							sqlBuf[1024  +  1];
		QY_COLUMNINFO			*		pColumns;
		int								nFields;
		int								nItemSelected;
	}									m_var;

	void  listGrps(  );
	BOOL  bRefreshButtons(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgSwitchPolicyGrps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgSwitchPolicyGrps)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedLISTswitchPolicyGrp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnModify();
	afx_msg void OnDblclkLISTswitchPolicyGrp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnmodifyDefSnmpPolicy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSWITCHPOLICYGRPS_H__1E871A59_FBE0_4015_BF24_F032F915D077__INCLUDED_)
