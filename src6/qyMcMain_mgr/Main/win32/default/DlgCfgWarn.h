#if !defined(AFX_DLGCFGWARN_H__0ABAA849_297F_4C4B_A5F3_F78CBEF75D8B__INCLUDED_)
#define AFX_DLGCFGWARN_H__0ABAA849_297F_4C4B_A5F3_F78CBEF75D8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgWarn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgWarn dialog

class CDlgCfgWarn : public CDialog
{
// Construction
public:
	CDlgCfgWarn(CWnd* pParent = NULL);   // standard constructor


	struct		{
		char	popupToWarnStartTime[CONST_qyTimeLen  +  1];
		char	new_popupToWarnStartTime[CONST_qyTimeLen  +  1];
	}			m_var;

// Dialog Data
	//{{AFX_DATA(CDlgCfgWarn)
	enum { IDD = IDD_CFGWARN };
	UINT	m_nMaxWarnElapse;
	BOOL	m_bWarnOn;
	BOOL	m_bWarnUntilUsrStopIt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgWarn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgWarn)
	afx_msg void OnWarnon();
	afx_msg void OnWarnuntilusrstopit();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKpopupToWarn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGWARN_H__0ABAA849_297F_4C4B_A5F3_F78CBEF75D8B__INCLUDED_)
