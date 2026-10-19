#if !defined(AFX_DLGCFGUSR_H__3C02B373_CF36_441A_8B4A_50865444236B__INCLUDED_)
#define AFX_DLGCFGUSR_H__3C02B373_CF36_441A_8B4A_50865444236B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgUsr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgUsr dialog

class CDlgCfgUsr : public CDialog
{
// Construction
public:
	CDlgCfgUsr(CWnd* pParent = NULL);   // standard constructor

	struct  {
		int			type;
		CWnd	*	pSrcWnd;	
		BOOL		bChanged;

		char		curGrpNameBuf[256];


	}				var;

	BOOL  bSetDlgInfo(  int  type,  CWnd * pSrcWnd  );

// Dialog Data
	//{{AFX_DATA(CDlgCfgUsr)
	enum { IDD = IDD_CFGUSR };
	CString	m_name;
	CString	m_passwd0;
	CString	m_passwd1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgUsr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgUsr)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGUSR_H__3C02B373_CF36_441A_8B4A_50865444236B__INCLUDED_)
