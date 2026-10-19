#if !defined(AFX_DLGADDSWITCHTOGRP_H__8D3E8E71_BAE2_413E_94E3_562A735518B1__INCLUDED_)
#define AFX_DLGADDSWITCHTOGRP_H__8D3E8E71_BAE2_413E_94E3_562A735518B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddSwitchToGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddSwitchToGrp dialog

class CDlgAddSwitchToGrp : public CDialog
{
// Construction
public:
	CDlgAddSwitchToGrp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddSwitchToGrp)
	enum { IDD = IDD_addSwitchToGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		int				type;
		HWND			hParent;
		char			title[256  +  1];
		char			okName[64  +  1];
		char			cancelName[64  +  1];
		char			ipBuf[CONST_qyMaxIpLen  +  1];
	}					m_var;

	BOOL			bSetDlgInfo(  int  type,  HWND  hParent,  char  *  title,  char  *  okName,  char  *  cancelName  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddSwitchToGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddSwitchToGrp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDSWITCHTOGRP_H__8D3E8E71_BAE2_413E_94E3_562A735518B1__INCLUDED_)
