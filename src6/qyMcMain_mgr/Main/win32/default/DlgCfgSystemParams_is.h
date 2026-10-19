#if !defined(AFX_DLGCFGSYSTEMPARAMS_IS_H__20172F8B_2382_431D_A19D_E03FBCEB531F__INCLUDED_)
#define AFX_DLGCFGSYSTEMPARAMS_IS_H__20172F8B_2382_431D_A19D_E03FBCEB531F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgSystemParams_is.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSystemParams_is dialog

class CDlgCfgSystemParams_is : public CDialog
{
// Construction
public:
	CDlgCfgSystemParams_is(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgSystemParams_is)
	enum { IDD = IDD_cfgSystemParams_is };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgSystemParams_is)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	struct						{
		QIS_INTERVAL_PARAMS		intervalParams;
		//
		unsigned  int			nMaxConns;

	}							m_var;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgSystemParams_is)
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

#endif // !defined(AFX_DLGCFGSYSTEMPARAMS_IS_H__20172F8B_2382_431D_A19D_E03FBCEB531F__INCLUDED_)
