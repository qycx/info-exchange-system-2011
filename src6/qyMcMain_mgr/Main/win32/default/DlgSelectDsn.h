#if !defined(AFX_DLGSELECTDSN_H__5E12CE88_A175_4377_B94C_17D29EF2C49C__INCLUDED_)
#define AFX_DLGSELECTDSN_H__5E12CE88_A175_4377_B94C_17D29EF2C49C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectDsn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectDsn dialog

class CDlgSelectDsn : public CDialog
{
// Construction
public:
	CDlgSelectDsn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelectDsn)
	enum { IDD = IDD_selectDsn };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct		{
		int		iDsnIndex;
	}			m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectDsn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectDsn)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTDSN_H__5E12CE88_A175_4377_B94C_17D29EF2C49C__INCLUDED_)
