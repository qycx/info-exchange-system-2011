#if !defined(AFX_DLGCFGSYSTEMPARAMS_H__6B2A21A9_030D_46E7_9DF2_B2A4A8C303BF__INCLUDED_)
#define AFX_DLGCFGSYSTEMPARAMS_H__6B2A21A9_030D_46E7_9DF2_B2A4A8C303BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgSystemParams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgSystemParams dialog

class CDlgCfgSystemParams : public CDialog
{
// Construction
public:
	CDlgCfgSystemParams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgSystemParams)
	enum { IDD = IDD_cfgSystemParams };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct						{
		/*
		unsigned  int			uiGetCfgInterval;
		unsigned  int			uiShowPcNetworkInterval;
		unsigned  int			uiSndEventLogInterval;
		unsigned  int			uiSndUsrInfoInterval;
		unsigned  int			uiSndNetStatInterval;
		unsigned  int			uiShowProcessInterval;
		*/
		QNM_INTERVAL_PARAMS		intervalParams;
		//
		unsigned  int			nProcessQmObjQInterval;		
		unsigned  int			nRefreshQmObjQStatusInDb;
		unsigned  int			uiMaxLogs;
		unsigned  int			nMaxConns;

	}							m_var;

	CQyRestrictEdit		m_edits[30];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgSystemParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgSystemParams)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSYSTEMPARAMS_H__6B2A21A9_030D_46E7_9DF2_B2A4A8C303BF__INCLUDED_)
