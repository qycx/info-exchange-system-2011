#if !defined(AFX_DLGQNMPCSPLISTSEARCH_H__65C797EA_5EE3_4878_8D44_D0EE8049A0C4__INCLUDED_)
#define AFX_DLGQNMPCSPLISTSEARCH_H__65C797EA_5EE3_4878_8D44_D0EE8049A0C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmPcSpListSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcSpListSearch dialog

class CDlgQnmPcSpListSearch : public CDialog
{
// Construction
public:
	CDlgQnmPcSpListSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmPcSpListSearch)
	enum { IDD = IDD_qnmPcSpListSearch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		QY_OBJ_DB	*	pObjDb;
		char			osName[64  +  1];
		char			spName[32  +  1];
	}					m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmPcSpListSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmPcSpListSearch)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCOMBOosName();
	afx_msg void OnSelchangeCOMBOspName();
	afx_msg void OnSelchangeCOMBOcusName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMPCSPLISTSEARCH_H__65C797EA_5EE3_4878_8D44_D0EE8049A0C4__INCLUDED_)
