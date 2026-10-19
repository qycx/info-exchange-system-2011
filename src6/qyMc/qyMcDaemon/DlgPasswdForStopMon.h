#if !defined(AFX_DLGPASSWDFORSTOPMON_H__B126BC1D_03EF_438C_9ABF_0E477E113640__INCLUDED_)
#define AFX_DLGPASSWDFORSTOPMON_H__B126BC1D_03EF_438C_9ABF_0E477E113640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPasswdForStopMon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswdForStopMon dialog

class CDlgPasswdForStopMon : public CDialog
{
// Construction
public:
	CDlgPasswdForStopMon(CWnd* pParent = NULL);   // standard constructor
	BOOL  bSetDlgInfo(  char  *  hint  );

	struct		{
		char	hint[256];
	}			m_var;

// Dialog Data
	//{{AFX_DATA(CDlgPasswdForStopMon)
	enum { IDD = IDD_passwdForStopMon };
	CString	m_passwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPasswdForStopMon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPasswdForStopMon)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSWDFORSTOPMON_H__B126BC1D_03EF_438C_9ABF_0E477E113640__INCLUDED_)
