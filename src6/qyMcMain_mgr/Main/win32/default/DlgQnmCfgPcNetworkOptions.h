#if !defined(AFX_DLGQNMCFGPCNETWORKOPTIONS_H__49FB6B4D_B56C_4078_90CD_033F98E62E1B__INCLUDED_)
#define AFX_DLGQNMCFGPCNETWORKOPTIONS_H__49FB6B4D_B56C_4078_90CD_033F98E62E1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcNetworkOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcNetworkOptions dialog

class CDlgQnmCfgPcNetworkOptions : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcNetworkOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcNetworkOptions)
	enum { IDD = IDD_qnmCfgPcNetworkOptions };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct					{
		QNM_PC_RULES		pcRules;
	}						m_var;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcNetworkOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcNetworkOptions)
	afx_msg void OnBUTTONbindPcNetworkOptions();
	afx_msg void OnBUTTONcancelPcNetworkOptionsBindings();
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONcfgWindowsUpdatePolicy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCNETWORKOPTIONS_H__49FB6B4D_B56C_4078_90CD_033F98E62E1B__INCLUDED_)
