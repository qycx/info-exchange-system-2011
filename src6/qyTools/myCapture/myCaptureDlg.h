// myCaptureDlg.h : header file
//

#if !defined(AFX_MYCAPTUREDLG_H__ABCBE1B8_E201_4552_BC53_4088A7A6DC24__INCLUDED_)
#define AFX_MYCAPTUREDLG_H__ABCBE1B8_E201_4552_BC53_4088A7A6DC24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyCaptureDlg dialog

class CMyCaptureDlg : public CDialog
{
// Construction
public:
	CMyCaptureDlg(CWnd* pParent = NULL);	// standard constructor

	struct		{
		TCHAR	fileName[128];
	}			m_var;

	CQyRestrictEdit		m_edits[10];


// Dialog Data
	//{{AFX_DATA(CMyCaptureDlg)
	enum { IDD = IDD_MYCAPTURE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCaptureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyCaptureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCAPTUREDLG_H__ABCBE1B8_E201_4552_BC53_4088A7A6DC24__INCLUDED_)
