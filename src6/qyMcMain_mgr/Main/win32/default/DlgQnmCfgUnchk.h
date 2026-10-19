#if !defined(AFX_DLGQNMCFGUNCHK_H__9B72D104_780D_487F_A205_CCDB9755FE60__INCLUDED_)
#define AFX_DLGQNMCFGUNCHK_H__9B72D104_780D_487F_A205_CCDB9755FE60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgUnchk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgUnchk dialog

class CDlgQnmCfgUnchk : public CDialog
{
// Construction
public:
	CDlgQnmCfgUnchk(CWnd* pParent = NULL);   // standard constructor

	struct		{
		int		idcList;
		int		nItemUnchkedIpSelected;
		int		nItemTmpUnchkedIpSelected;
	}			m_var;

	void	refreshAll(  );
	BOOL	bRefreshButtons(  );

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgUnchk)
	enum { IDD = IDD_qnmCfgUnchk };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgUnchk)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgUnchk)
	afx_msg void OnAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedLISTtmpUnchkedIp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedLISTunchkedIp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDel();
	afx_msg void OnSetfocusLISTtmpUnchkedIp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusLISTunchkedIp(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGUNCHK_H__9B72D104_780D_487F_A205_CCDB9755FE60__INCLUDED_)
