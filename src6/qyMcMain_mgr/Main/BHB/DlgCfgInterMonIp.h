#if !defined(AFX_DLGCFGINTERMONIP_H__4825284B_6687_4897_A118_67AAB75EBBD5__INCLUDED_)
#define AFX_DLGCFGINTERMONIP_H__4825284B_6687_4897_A118_67AAB75EBBD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgInterMonIp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgInterMonIp dialog

class CDlgCfgInterMonIp : public CDialog
{
// Construction
public:
	CDlgCfgInterMonIp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgInterMonIp)
	enum { IDD = IDD_cfgInterMonIp };
	CIPAddressCtrl	m_interMonIp1;
	CIPAddressCtrl	m_interMonIp0;
	//}}AFX_DATA

	struct				{
		unsigned  long	ulInterMonIp0;
		unsigned  long	ulInterMonIp1;
	}					m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgInterMonIp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgInterMonIp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGINTERMONIP_H__4825284B_6687_4897_A118_67AAB75EBBD5__INCLUDED_)
