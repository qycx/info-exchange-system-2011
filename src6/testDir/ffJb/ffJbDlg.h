// ffJbDlg.h : header file
//

#if !defined(AFX_FFJBDLG_H__4210A765_CE10_438B_B945_FF86806FBD98__INCLUDED_)
#define AFX_FFJBDLG_H__4210A765_CE10_438B_B945_FF86806FBD98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFfJbDlg dialog

class CFfJbDlg : public CDialog
{
// Construction
public:
	CFfJbDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFfJbDlg)
	enum { IDD = IDD_FFJB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFfJbDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFfJbDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFJBDLG_H__4210A765_CE10_438B_B945_FF86806FBD98__INCLUDED_)
