#if !defined(AFX_DLGMGRSWITCHPOLICYGRPS_H__872E53EE_9F83_41A1_9011_82758E2D8F3B__INCLUDED_)
#define AFX_DLGMGRSWITCHPOLICYGRPS_H__872E53EE_9F83_41A1_9011_82758E2D8F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMgrSwitchPolicyGrps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrSwitchPolicyGrps dialog

class CDlgMgrSwitchPolicyGrps : public CDialog
{
// Construction
public:
	CDlgMgrSwitchPolicyGrps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMgrSwitchPolicyGrps)
	enum { IDD = IDD_mgrSwitchPolicyGrps };
	CListCtrl	m_lv;
	//}}AFX_DATA

	struct								{
		QY_OBJ_DB				*		pObjDb;

		int								idcCb;
		int								idcList;
		char							sqlBuf[1024  +  1];
		QY_COLUMNINFO			*		pColumns;
		int								nFields;
		int								nItemSelected;
		char							grpName[255  +  1];
	}									m_var;

	BOOL				bRefreshButtons(  );
	void				listIps(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMgrSwitchPolicyGrps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMgrSwitchPolicyGrps)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnItemchangedLISTip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCOMBOsnmpPolicyGrp();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMGRSWITCHPOLICYGRPS_H__872E53EE_9F83_41A1_9011_82758E2D8F3B__INCLUDED_)
