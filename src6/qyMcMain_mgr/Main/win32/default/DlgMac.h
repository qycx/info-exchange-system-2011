#if !defined(AFX_DLGMAC_H__545522A3_2994_4A41_ADCA_E6906726F713__INCLUDED_)
#define AFX_DLGMAC_H__545522A3_2994_4A41_ADCA_E6906726F713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMac.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMac dialog

class CDlgMac : public CDialog
{
// Construction
public:
	CDlgMac(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMac)
	enum { IDD = IDD_mac };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct		{
		int				type;
		HWND			hParent;
		TCHAR			title[256  +  1];
		TCHAR			okName[64  +  1];
		TCHAR			cancelName[64  +  1];
		//
		char	mac[CONST_qyMacLen  +  1];
	}			m_var;
	CQyRestrictEdit		m_edits[4];


	BOOL  bSetDlgInfo(  int  type,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  okName,  LPCTSTR  cancelName  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMac)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMac)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAC_H__545522A3_2994_4A41_ADCA_E6906726F713__INCLUDED_)
