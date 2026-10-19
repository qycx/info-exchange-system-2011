#if !defined(AFX_DLGQNMCFGPCRULE_H__FCF67622_0000_418B_9E5E_A97242773638__INCLUDED_)
#define AFX_DLGQNMCFGPCRULE_H__FCF67622_0000_418B_9E5E_A97242773638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcRule dialog

class CDlgQnmCfgPcRule : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcRule(CWnd* pParent = NULL);   // standard constructor

	struct  {
			QY_OBJ_DB	*		pObjDb;
			char				mac0[12  +  1];
			unsigned  char		ucRasCmd;
	}							m_var;
	//
	CQyRestrictEdit		m_edits[CONST_qnmMaxSearchFields];


	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac0  );

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcRule)
	enum { IDD = IDD_qnmCfgPcRule };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcRule)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCHECKbMonAllDisks();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCRULE_H__FCF67622_0000_418B_9E5E_A97242773638__INCLUDED_)
