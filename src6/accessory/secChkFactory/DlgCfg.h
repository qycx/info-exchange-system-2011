#if !defined(AFX_DLGCFG_H__828234AE_BB9B_4570_9FF5_3718144C0F03__INCLUDED_)
#define AFX_DLGCFG_H__828234AE_BB9B_4570_9FF5_3718144C0F03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfg dialog

class CDlgCfg : public CDialog
{
// Construction
public:
	CDlgCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfg)
	enum { IDD = IDD_cfg };
	CString	m_qyRegToolDir;
	//}}AFX_DATA

	struct  {
		char		qyRegToolDir[MAX_PATH  +  1];
	}				m_var;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFG_H__828234AE_BB9B_4570_9FF5_3718144C0F03__INCLUDED_)
