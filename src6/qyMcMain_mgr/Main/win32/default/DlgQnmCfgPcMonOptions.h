#if !defined(AFX_DLGQNMCFGPCMONOPTIONS_H__D078F190_764A_4493_BDC8_F7427BDA2E87__INCLUDED_)
#define AFX_DLGQNMCFGPCMONOPTIONS_H__D078F190_764A_4493_BDC8_F7427BDA2E87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcMonOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcMonOptions dialog

class CDlgQnmCfgPcMonOptions : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcMonOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcMonOptions)
	enum { IDD = IDD_qnmCfgPcMonOptions };
	UINT	m_capScreenInterval;
	//}}AFX_DATA

	struct				{
		BOOL			bNeedRefreshAll;

		QNM_PC_RULES	pcRules;
		TCHAR			capScreenDir[MAX_PATH  +  1];
		unsigned  char	ucbSaveAsGif;
		unsigned  short	usCnt_monPics_row;
		unsigned  short	usCnt_monPics_col;
	}					m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcMonOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcMonOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBUTTONbrowseDir();
	afx_msg void OnBUTTONcfgFileMonFilter();
	afx_msg void OnBUTTONcfgPcRegistry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCMONOPTIONS_H__D078F190_764A_4493_BDC8_F7427BDA2E87__INCLUDED_)
