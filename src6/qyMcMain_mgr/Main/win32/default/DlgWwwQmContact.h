#if !defined(AFX_DLGWWWQMCONTACT_H__8498D273_EA89_4561_979E_C4D3E2145031__INCLUDED_)
#define AFX_DLGWWWQMCONTACT_H__8498D273_EA89_4561_979E_C4D3E2145031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWwwQmContact.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWwwQmContact dialog

class CDlgWwwQmContact : public CDialog
{
// Construction
public:
	CDlgWwwQmContact(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWwwQmContact)
	enum { IDD = IDD_wwwQmCfg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct					{
		QY_OBJ_DB		*	pObjDb;
		
		TCHAR				misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID		idInfo;
		
		int					id;
		//

		WEB_CONTACT_RCD		oldWebContact;
		WEB_CONTACT_RCD		webContact;
		WCHAR				wAdvertisement[510  +  1];

	}				m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  id  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWwwQmContact)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWwwQmContact)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWWWQMCONTACT_H__8498D273_EA89_4561_979E_C4D3E2145031__INCLUDED_)
