#if !defined(AFX_LOGQUERY_H__84BE3AD0_CE1B_4E13_80B0_ABFD6725F534__INCLUDED_)
#define AFX_LOGQUERY_H__84BE3AD0_CE1B_4E13_80B0_ABFD6725F534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogQuery dialog

class CLogQuery : public CDialog
{
// Construction
public:
	CLogQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogQuery)
	enum { IDD = IDD_DLG_QUERY };
	CComboBox	m_cLogType;
	CIPAddressCtrl	m_cIpAddress;
	CTime	m_Dateb;
	CTime	m_Datee;
	CTime	m_Timeb;
	CTime	m_Timee;
	CString	m_csUnit;
	CString	m_csDepart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogQuery)
	afx_msg void OnShowlog();
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGQUERY_H__84BE3AD0_CE1B_4E13_80B0_ABFD6725F534__INCLUDED_)
