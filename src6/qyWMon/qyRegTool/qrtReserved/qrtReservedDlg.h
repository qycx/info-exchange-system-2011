// qrtReservedDlg.h : header file
//

#if !defined(AFX_QRTRESERVEDDLG_H__D0DA2A81_B038_4EBC_A225_CE8B1218030D__INCLUDED_)
#define AFX_QRTRESERVEDDLG_H__D0DA2A81_B038_4EBC_A225_CE8B1218030D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQrtReservedDlg dialog

class CQrtReservedDlg : public CDialog
{
// Construction
public:
	CQrtReservedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQrtReservedDlg)
	enum { IDD = IDD_QRTRESERVED_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQrtReservedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQrtReservedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QRTRESERVEDDLG_H__D0DA2A81_B038_4EBC_A225_CE8B1218030D__INCLUDED_)
