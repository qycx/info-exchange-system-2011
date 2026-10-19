#if !defined(AFX_DLGQNMOTHERMACINFO_H__EA6EF690_B99A_4441_8032_E14EBD152B6D__INCLUDED_)
#define AFX_DLGQNMOTHERMACINFO_H__EA6EF690_B99A_4441_8032_E14EBD152B6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmOtherMacInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmOtherMacInfo dialog

class CDlgQnmOtherMacInfo : public CDialog
{
// Construction
public:
	CDlgQnmOtherMacInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmOtherMacInfo)
	enum { IDD = IDD_qnmOtherMacInfo };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		QY_OBJ_DB	*	pObjDb;
		char			mac[CONST_qyMacLen  +  1];
	}					m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmOtherMacInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmOtherMacInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMOTHERMACINFO_H__EA6EF690_B99A_4441_8032_E14EBD152B6D__INCLUDED_)
