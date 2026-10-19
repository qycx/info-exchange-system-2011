#if !defined(AFX_DLGSTATUS_H__51C5F068_BAB3_4587_B1CB_F729B31A4874__INCLUDED_)
#define AFX_DLGSTATUS_H__51C5F068_BAB3_4587_B1CB_F729B31A4874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStatus dialog

class CDlgStatus : public CDialog
{
// Construction
public:
	CDlgStatus(CWnd* pParent = NULL);   // standard constructor

	struct  {
		char	buf[1024];
	}		m_var;

// Dialog Data
	//{{AFX_DATA(CDlgStatus)
	enum { IDD = IDD_status };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStatus)
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTATUS_H__51C5F068_BAB3_4587_B1CB_F729B31A4874__INCLUDED_)
