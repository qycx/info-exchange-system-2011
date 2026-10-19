#if !defined(AFX_DLGPHONENUM_H__12876506_4D7B_45F0_A033_9EE23836515D__INCLUDED_)
#define AFX_DLGPHONENUM_H__12876506_4D7B_45F0_A033_9EE23836515D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPhoneNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPhoneNum dialog

class CDlgPhoneNum : public CDialog
{
// Construction
public:
	CDlgPhoneNum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPhoneNum)
	enum { IDD = IDD_phoneNum };
	//}}AFX_DATA

	struct			{
		CWnd	*	pParent;
		char		phoneNum[CONST_phoneNumBytes  +  1];
	}				m_var;

	BOOL	bSetDlgInfo(  CWnd  *  pParent  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPhoneNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPhoneNum)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPHONENUM_H__12876506_4D7B_45F0_A033_9EE23836515D__INCLUDED_)
