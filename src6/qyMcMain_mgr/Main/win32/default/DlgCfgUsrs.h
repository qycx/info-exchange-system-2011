#if !defined(AFX_DLGCFGUSRS_H__09CDC45E_75FE_4260_9DB2_BDC00F1876B0__INCLUDED_)
#define AFX_DLGCFGUSRS_H__09CDC45E_75FE_4260_9DB2_BDC00F1876B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgUsrs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgUsrs dialog

class CDlgCfgUsrs : public CDialog
{
// Construction
public:
	CDlgCfgUsrs( CWnd* pParent = NULL );   // standard constructor

	int		getLogonCfgFromDlg(  );
	int		listUsrs(  );
	BOOL	bRefreshButtons(  );
	BOOL	bModifyItem(  );


	struct				{
		int				nItemSelected;
	}					var;


// Dialog Data
	//{{AFX_DATA(CDlgCfgUsrs)
	enum { IDD = IDD_CFGUSRS };
	CComboBox	m_grpList;
	CListCtrl	m_LV;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgUsrs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgUsrs)
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDel();
	afx_msg void OnDblclkUsrlist(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGrplist();
	afx_msg void OnItemchangedUsrlist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	virtual void OnCancel();
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGUSRS_H__09CDC45E_75FE_4260_9DB2_BDC00F1876B0__INCLUDED_)
