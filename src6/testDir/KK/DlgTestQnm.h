#if !defined(AFX_DLGTESTQNM_H__CE3A99CC_8D2E_47D6_BC2B_BA51FA34696B__INCLUDED_)
#define AFX_DLGTESTQNM_H__CE3A99CC_8D2E_47D6_BC2B_BA51FA34696B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTestQnm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTestQnm dialog

class CDlgTestQnm : public CDialog
{
// Construction
public:
	CDlgTestQnm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTestQnm)
	enum { IDD = IDD_testQnm };
	CString	m_qwmSendTimes;
	CString	m_qwmServerIp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestQnm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTestQnm)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTESTQNM_H__CE3A99CC_8D2E_47D6_BC2B_BA51FA34696B__INCLUDED_)
