#if !defined(AFX_DLGADDFILEMONRULE_H__C710E6E9_31FC_44C9_B4D9_501F7EE2280D__INCLUDED_)
#define AFX_DLGADDFILEMONRULE_H__C710E6E9_31FC_44C9_B4D9_501F7EE2280D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddFileMonRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFileMonRule dialog

class CDlgAddFileMonRule : public CDialog
{
// Construction
public:
	CDlgAddFileMonRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddFileMonRule)
	enum { IDD = IDD_addFileMonRule };
	//}}AFX_DATA

	struct						{
		char					buf[CONST_maxFileMonRuleBufSize];
		unsigned  char			ucFlg;
		PC_FILEMON_RULES	*	pRules;
	}							m_var;

	BOOL	bSetDlgInfo(  void  *  pRules  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddFileMonRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddFileMonRule)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDFILEMONRULE_H__C710E6E9_31FC_44C9_B4D9_501F7EE2280D__INCLUDED_)
