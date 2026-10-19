#if !defined(AFX_DLGCFGGSMMODEM_H__3B42D50A_8D75_4C14_B3EF_AD45E7284DD1__INCLUDED_)
#define AFX_DLGCFGGSMMODEM_H__3B42D50A_8D75_4C14_B3EF_AD45E7284DD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgGsmModem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgGsmModem dialog

class CDlgCfgGsmModem : public CDialog
{
// Construction
public:
	CDlgCfgGsmModem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgGsmModem)
	enum { IDD = IDD_cfgGsmModem };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{

		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		TCHAR						misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID				idInfo;
		WCHAR						wDevIdStr[128  +  1];
		unsigned  char				ucbDefaultSmServer;
		int							id;

		QY_SMCONTACT_RCD			smContact;

	}								m_var;


	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  unsigned  char  ucbDefaultSmServer,  int  id  );




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgGsmModem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgGsmModem)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGGSMMODEM_H__3B42D50A_8D75_4C14_B3EF_AD45E7284DD1__INCLUDED_)
