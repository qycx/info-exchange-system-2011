#if !defined(AFX_DLGEDITSWITCHINFO_H__D9FD66A2_65C9_41A9_ABEF_F52A1180393B__INCLUDED_)
#define AFX_DLGEDITSWITCHINFO_H__D9FD66A2_65C9_41A9_ABEF_F52A1180393B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEditSwitchInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditSwitchInfo dialog

class CDlgEditSwitchInfo : public CDialog
{
// Construction
public:
	CDlgEditSwitchInfo(CWnd* pParent = NULL);   // standard constructor

	struct					{
		int					type;
		QY_OBJ_DB		*	pObjDb;
		HWND				hParent;
		long				lHelpId;
		unsigned  char		ucbAuditSwitchAndAllConns;
		unsigned  char		ucbChanged;
		QY_SNMPOBJ_HEAD		objHead;
	}						m_var;
	//  CQyRestrictEdit			m_cusNameEdit;

	BOOL  bSetDlgInfo(  int  type,  QY_OBJ_DB  *  pObjDb,  HWND  hParent,  long  lHelpId,  unsigned  char  ucbAuditSwitchAndAllConns  );

// Dialog Data
	//{{AFX_DATA(CDlgEditSwitchInfo)
	enum { IDD = IDD_editSwitchInfo };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditSwitchInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditSwitchInfo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITSWITCHINFO_H__D9FD66A2_65C9_41A9_ABEF_F52A1180393B__INCLUDED_)
