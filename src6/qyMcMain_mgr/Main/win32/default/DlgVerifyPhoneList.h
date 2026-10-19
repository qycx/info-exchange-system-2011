#if !defined(AFX_DLGVERIFYPHONELIST_H__AA8F2269_1111_4EB7_87CE_6620AB0FD5DB__INCLUDED_)
#define AFX_DLGVERIFYPHONELIST_H__AA8F2269_1111_4EB7_87CE_6620AB0FD5DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVerifyPhoneList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVerifyPhoneList dialog

class CDlgVerifyPhoneList : public CDialog
{
// Construction
public:
	CDlgVerifyPhoneList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVerifyPhoneList)
	enum { IDD = IDD_verifyPhoneList };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct						{
		int						idcList;
		int						nFields;
		QY_COLUMNINFO		*	pColumns;
		MC_VAR_isCli			*	pProcInfo;
		//
		BOOL					bListLoaded;

	}							m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVerifyPhoneList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVerifyPhoneList)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtondeny();
	afx_msg void OnBnClickedButtonrefresh();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVERIFYPHONELIST_H__AA8F2269_1111_4EB7_87CE_6620AB0FD5DB__INCLUDED_)
