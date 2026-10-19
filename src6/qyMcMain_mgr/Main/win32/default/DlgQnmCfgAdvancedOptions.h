#if !defined(AFX_DLGQNMCFGADVANCEDOPTIONS_H__A465DBEA_197B_458D_B024_B0E2D5FD689C__INCLUDED_)
#define AFX_DLGQNMCFGADVANCEDOPTIONS_H__A465DBEA_197B_458D_B024_B0E2D5FD689C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgAdvancedOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgAdvancedOptions dialog

class CDlgQnmCfgAdvancedOptions : public CDialog
{
// Construction
public:
	CDlgQnmCfgAdvancedOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgAdvancedOptions)
	enum { IDD = IDD_qnmCfgAdvancedOptions };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct			{
		//  BOOL		bDefault;
		//  char		dbTypeName[32  +  1];
		//  char		uid[64  +  1];
		//  char		pwd[64  +  1];
		//  char		connectStr[1024  +  1];
		QNM_DB_CFG	dbCfg;
	}				m_var;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgAdvancedOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgAdvancedOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCOMBOdbTypeName();
	afx_msg void OnCHECKdefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGADVANCEDOPTIONS_H__A465DBEA_197B_458D_B024_B0E2D5FD689C__INCLUDED_)
