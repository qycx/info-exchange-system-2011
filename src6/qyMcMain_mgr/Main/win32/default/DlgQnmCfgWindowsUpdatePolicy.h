#if !defined(AFX_DLGQNMCFGWINDOWSUPDATEPOLICY_H__F53EA1A4_3C77_47D2_B226_BE3D882F09B8__INCLUDED_)
#define AFX_DLGQNMCFGWINDOWSUPDATEPOLICY_H__F53EA1A4_3C77_47D2_B226_BE3D882F09B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgWindowsUpdatePolicy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgWindowsUpdatePolicy dialog

class CDlgQnmCfgWindowsUpdatePolicy : public CDialog
{
// Construction
public:
	CDlgQnmCfgWindowsUpdatePolicy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgWindowsUpdatePolicy)
	enum { IDD = IDD_qnmCfgWindowsUpdatePolicy };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct						{
		QY_OBJ_DB			*	pObjDb;
		char					mac0[CONST_qyMacLen  +  1];
		int						id;
		//
		unsigned  int			uiType;
		QY_PCADAPTER_RCD		pcAdapterRcd;

		unsigned  char			ucbRuleExists;
		unsigned  char			ucbChanged;
	}							m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  mac0,  int  id  );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgWindowsUpdatePolicy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgWindowsUpdatePolicy)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonDel();
	afx_msg void OnBUTTONimport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGWINDOWSUPDATEPOLICY_H__F53EA1A4_3C77_47D2_B226_BE3D882F09B8__INCLUDED_)
