#if !defined(AFX_DLGQNMCFGRASOPTIONS_H__BE7D6A71_EA7F_4B17_B831_DD2BEACCE81C__INCLUDED_)
#define AFX_DLGQNMCFGRASOPTIONS_H__BE7D6A71_EA7F_4B17_B831_DD2BEACCE81C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgRasOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgRasOptions dialog

class CDlgQnmCfgRasOptions : public CDialog
{
// Construction
public:
	CDlgQnmCfgRasOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgRasOptions)
	enum { IDD = IDD_qnmCfgRasOptions };
	CIPAddressCtrl	m_monIp;
	//}}AFX_DATA

	struct				{
		QNM_PC_RULES	pcRules;

		//  unsigned  char	ucRasCmd;
		//  char			permittedPhoneNums[CONST_maxPermittedPhoneNums][CONST_phoneNumBytes  +  1];
		
		DWORD			dwMonIp;					//  2005/01/04
		unsigned  short	usMonPort;					//  2005/01/04

	}					m_var;

	BOOL				bRefreshDisplay(  );
	int					setSomeOptions(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgRasOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgRasOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnSelchangeCOMBOrasCmd();
	afx_msg void OnDel();
	afx_msg void OnSelchangeCOMBOfloppyCmd();
	afx_msg void OnSelchangeCOMBOcdromCmd();
	afx_msg void OnSelchangeCOMBOusbCmd();
	virtual void OnOK();
	afx_msg void OnCHECKbNotChkOnInternet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGRASOPTIONS_H__BE7D6A71_EA7F_4B17_B831_DD2BEACCE81C__INCLUDED_)
