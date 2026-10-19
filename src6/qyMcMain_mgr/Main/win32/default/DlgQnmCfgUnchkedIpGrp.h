#if !defined(AFX_DLGQNMCFGUNCHKEDIPGRP_H__74635649_EC2F_4E4E_946E_9FCDE109C6AA__INCLUDED_)
#define AFX_DLGQNMCFGUNCHKEDIPGRP_H__74635649_EC2F_4E4E_946E_9FCDE109C6AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgUnchkedIpGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgUnchkedIpGrp dialog

class CDlgQnmCfgUnchkedIpGrp : public CDialog
{
// Construction
public:
	CDlgQnmCfgUnchkedIpGrp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgUnchkedIpGrp)
	enum { IDD = IDD_qnmCfgUnchkedIpGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct				{
		int				type;
		HWND			hParent;
		char			title[256  +  1];
		char			okName[64  +  1];
		char			cancelName[64  +  1];
		char			startIpBuf[CONST_qyMaxIpLen  +  1],  endIpBuf[CONST_qyMaxIpLen  +  1];
		char			ipBuf[CONST_qyMaxIpLen  +  1];
		QY_DMITEM	*	pDesTable;
	}					m_var;

	BOOL			bSetDlgInfo(  int  type,  HWND  hParent,  char  *  title,  char  *  okName,  char  *  cancelName,  QY_DMITEM  *  pTypeTable  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgUnchkedIpGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgUnchkedIpGrp)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOdes();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGUNCHKEDIPGRP_H__74635649_EC2F_4E4E_946E_9FCDE109C6AA__INCLUDED_)
