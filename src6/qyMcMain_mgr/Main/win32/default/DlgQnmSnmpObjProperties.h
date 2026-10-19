#if !defined(AFX_DLGQNMSNMPOBJPROPERTIES_H__B48150CC_BAF9_45B3_9B75_75CDF65CA2A6__INCLUDED_)
#define AFX_DLGQNMSNMPOBJPROPERTIES_H__B48150CC_BAF9_45B3_9B75_75CDF65CA2A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmSnmpObjProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSnmpObjProperties dialog

class CDlgQnmSnmpObjProperties : public CDialog
{
// Construction
public:
	CDlgQnmSnmpObjProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmSnmpObjProperties)
	enum { IDD = IDD_qnmSnmpObjProperties };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct					{
		QY_OBJ_DB		*	pObjDb;
		char				mac[CONST_qyMacLen  +  1];
		int					iPortIfIndex;
	}						m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac,  int  iPortIfIndex  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmSnmpObjProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmSnmpObjProperties)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMSNMPOBJPROPERTIES_H__B48150CC_BAF9_45B3_9B75_75CDF65CA2A6__INCLUDED_)
