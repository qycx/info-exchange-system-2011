#if !defined(AFX_DLGCFGPHONEMESSENGER_H__ACFD0326_A31A_4353_A306_3412606789EB__INCLUDED_)
#define AFX_DLGCFGPHONEMESSENGER_H__ACFD0326_A31A_4353_A306_3412606789EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgPhoneMessenger.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPhoneMessenger dialog

class CDlgCfgPhoneMessenger : public CDialog
{
// Construction
public:
	CDlgCfgPhoneMessenger(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgPhoneMessenger)
	enum { IDD = IDD_cfgPhoneMessenger };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		TCHAR						misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID				idInfo;
		int							id;
		//
		BOOL						bGuest;
		//
		MC_VAR_isCli				*	pProcInfo;
		//
		WCHAR						wDevIdStr[256];

	}								m_var;


	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  BOOL  bGuest,  QY_MESSENGER_ID  *  pIdInfo,  int  id  );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgPhoneMessenger)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgPhoneMessenger)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGPHONEMESSENGER_H__ACFD0326_A31A_4353_A306_3412606789EB__INCLUDED_)
