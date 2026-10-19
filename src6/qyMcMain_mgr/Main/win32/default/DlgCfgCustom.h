#if !defined(AFX_DLGCFGCUSTOM_H__F5FA3036_9D1F_4C31_BC81_21D083D610F8__INCLUDED_)
#define AFX_DLGCFGCUSTOM_H__F5FA3036_9D1F_4C31_BC81_21D083D610F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgCustom.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgCustom dialog

class CDlgCfgCustom : public CDialog
{
// Construction
public:
	CDlgCfgCustom(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgCustom)
	enum { IDD = IDD_cfgCustom };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct							{
			unsigned  char			ucbChanged;
			QNM_CUSTOM_COMM			custom;
			TCHAR					qrtTitle[CONST_maxQrtTitleLen  +  1];		//  2005/07/27Ìí¼Ó
			TCHAR					qrtHint[CONST_maxQrtHintLen  +  1];
	}		m_var;
	CQyRestrictEdit		m_edits[10];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgCustom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgCustom)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGCUSTOM_H__F5FA3036_9D1F_4C31_BC81_21D083D610F8__INCLUDED_)
