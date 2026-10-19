#if !defined(AFX_DLGCFGIPKNOWLEDGE_H__39A53270_B7EB_492F_A04C_2F7CFDE88C2B__INCLUDED_)
#define AFX_DLGCFGIPKNOWLEDGE_H__39A53270_B7EB_492F_A04C_2F7CFDE88C2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgIpKnowledge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgIpKnowledge dialog

class CDlgCfgIpKnowledge : public CDialog
{
// Construction
public:
	CDlgCfgIpKnowledge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgIpKnowledge)
	enum { IDD = IDD_cfgIpKnowledge };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct							{
		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		int							id;
		//
		IP_KNOWLEDGE_RCD			knowledge;
	}								m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgIpKnowledge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgIpKnowledge)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGIPKNOWLEDGE_H__39A53270_B7EB_492F_A04C_2F7CFDE88C2B__INCLUDED_)
