#if !defined(AFX_DLGCFGFILEMONFILTER_H__907F363D_73C6_4992_BCA1_F27CC139AA0A__INCLUDED_)
#define AFX_DLGCFGFILEMONFILTER_H__907F363D_73C6_4992_BCA1_F27CC139AA0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgFileMonFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgFileMonFilter dialog

class CDlgCfgFileMonFilter : public CDialog
{
// Construction
public:
	CDlgCfgFileMonFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgFileMonFilter)
	enum { IDD = IDD_cfgFileMonFilter };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct			{
		PC_FILEMON_RULES				oldRules;
		PC_FILEMON_RULES				newRules;
	}				m_var;

	void  listRules(  PC_FILEMON_RULES  *  p  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgFileMonFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgFileMonFilter)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void Onreset();
	virtual void OnOK();
	afx_msg void OnSelchangeCOMBObMonAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGFILEMONFILTER_H__907F363D_73C6_4992_BCA1_F27CC139AA0A__INCLUDED_)
