#if !defined(AFX_DLGCFGSKIPPEDMACS_H__7821083F_E7C8_4A18_83B1_84ED1CB115EA__INCLUDED_)
#define AFX_DLGCFGSKIPPEDMACS_H__7821083F_E7C8_4A18_83B1_84ED1CB115EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgSkippedMacs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSkippedMacs dialog

class CDlgCfgSkippedMacs : public CDialog
{
// Construction
public:
	CDlgCfgSkippedMacs(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgSkippedMacs)
	enum { IDD = IDD_cfgSkippedMacs };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		SKIPPED_MACS	skippedMacs;
	}					m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgSkippedMacs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgSkippedMacs)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSKIPPEDMACS_H__7821083F_E7C8_4A18_83B1_84ED1CB115EA__INCLUDED_)
