// qyWarningToolDlg.h : header file
//

#if !defined(AFX_QYWARNINGTOOLDLG_H__F7451C58_0279_42D8_9E67_5F37A24312E2__INCLUDED_)
#define AFX_QYWARNINGTOOLDLG_H__F7451C58_0279_42D8_9E67_5F37A24312E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQyWarningToolDlg dialog

class CQyWarningToolDlg : public CDialog
{
// Construction
public:
	CQyWarningToolDlg(CWnd* pParent = NULL);	// standard constructor

	struct					{
		int					idcList;
		QY_COLUMNINFO	*	pColumns;
		int					nFields;
		QY_WARNING_INFO	*	pGBuf;
		int					id_selected;
	}						m_var;

// Dialog Data
	//{{AFX_DATA(CQyWarningToolDlg)
	enum { IDD = IDD_QYWARNINGTOOL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA



	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyWarningToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


	int  init(  );
	int  refreshAll(  );


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQyWarningToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnItemchangedLISTmsgs(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYWARNINGTOOLDLG_H__F7451C58_0279_42D8_9E67_5F37A24312E2__INCLUDED_)
