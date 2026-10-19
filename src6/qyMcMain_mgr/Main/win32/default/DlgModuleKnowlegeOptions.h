#if !defined(AFX_DLGMODULEKNOWLEGEOPTIONS_H__78FE70FA_3852_4E37_9F4A_499A3B13B24C__INCLUDED_)
#define AFX_DLGMODULEKNOWLEGEOPTIONS_H__78FE70FA_3852_4E37_9F4A_499A3B13B24C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgModuleKnowlegeOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgModuleKnowlegeOptions dialog

class CDlgModuleKnowlegeOptions : public CDialog
{
// Construction
public:
	CDlgModuleKnowlegeOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgModuleKnowlegeOptions)
	enum { IDD = IDD_moduleKnowlegeOptions };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct					{
		unsigned  char		ucbAudited;
		TCHAR				unAuditedHint[128];
		TCHAR				auditedHint[128];
	}						m_var;

	BOOL	bSetDlgInfo(  int  iDlgType,  LPCTSTR  unAuditedHint,  LPCTSTR  auditedHint  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgModuleKnowlegeOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgModuleKnowlegeOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODULEKNOWLEGEOPTIONS_H__78FE70FA_3852_4E37_9F4A_499A3B13B24C__INCLUDED_)
