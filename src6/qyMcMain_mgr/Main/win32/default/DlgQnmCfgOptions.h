#if !defined(AFX_DLGQNMCFGOPTIONS_H__6EFA8EBA_3BD7_4DF2_8023_DEAF94296B80__INCLUDED_)
#define AFX_DLGQNMCFGOPTIONS_H__6EFA8EBA_3BD7_4DF2_8023_DEAF94296B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgOptions dialog


class CDlgQnmCfgOptions : public CDialog
{
// Construction
public:
	CDlgQnmCfgOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgOptions)
	enum { IDD = IDD_qnmCfgOptions };
	CString	m_qyRegToolDir;
	//}}AFX_DATA

	struct  {
			int						iTask;

			//  DWORD					dwDomainSvrIp;
			//
			QNM_CNT_CFG				cntCfg;
			//
			TCHAR					qyRegToolDir[MAX_PATH  +  1];
			//  char					hint[64  +  1];
	}								m_var;

	CQyRestrictEdit					m_edits[10];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnHelp();
	afx_msg void OnBUTTONbrowseDir();
	afx_msg void OnCHECKcntIp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGOPTIONS_H__6EFA8EBA_3BD7_4DF2_8023_DEAF94296B80__INCLUDED_)
