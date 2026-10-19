#if !defined(AFX_DLGMCLOGON_H__B325BCB3_C213_11D6_9154_00E04C5009C2__INCLUDED_)
#define AFX_DLGMCLOGON_H__B325BCB3_C213_11D6_9154_00E04C5009C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMcLogon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMcLogon dialog

class CDlgMcLogon : public CDialog
{
// Construction
public:
	CDlgMcLogon(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMcLogon)
	enum { IDD = IDD_MC_LOGON };
	CString	m_name;
	CString	m_passwd;
	//}}AFX_DATA

	struct				{
		int				nTries;
	}					m_var;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMcLogon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMcLogon)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCLOGON_H__B325BCB3_C213_11D6_9154_00E04C5009C2__INCLUDED_)
