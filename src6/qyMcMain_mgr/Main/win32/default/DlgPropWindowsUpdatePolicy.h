#if !defined(AFX_DLGPROPWINDOWSUPDATEPOLICY_H__B9103B77_D4D8_42DC_BBD5_C33C5184FFD0__INCLUDED_)
#define AFX_DLGPROPWINDOWSUPDATEPOLICY_H__B9103B77_D4D8_42DC_BBD5_C33C5184FFD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropWindowsUpdatePolicy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropWindowsUpdatePolicy dialog

class CDlgPropWindowsUpdatePolicy : public CDialog
{
// Construction
public:
	CDlgPropWindowsUpdatePolicy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropWindowsUpdatePolicy)
	enum { IDD = IDD_prop_windowsUpdatePolicy };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		QY_OBJ_DB	*	pObjDb;
		int				id;
	}					m_var;
	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropWindowsUpdatePolicy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropWindowsUpdatePolicy)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPWINDOWSUPDATEPOLICY_H__B9103B77_D4D8_42DC_BBD5_C33C5184FFD0__INCLUDED_)
