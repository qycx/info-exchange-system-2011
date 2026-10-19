#if !defined(AFX_DLGQNMEDITMACINFO_H__1AE8E581_32DE_4409_A231_00AE7F54C3DD__INCLUDED_)
#define AFX_DLGQNMEDITMACINFO_H__1AE8E581_32DE_4409_A231_00AE7F54C3DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmEditMacInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEditMacInfo dialog

class CDlgQnmEditMacInfo : public CDialog
{
// Construction
public:
	CDlgQnmEditMacInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmEditMacInfo)
	enum { IDD = IDD_qnmEditMacInfo };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		unsigned  char				ucbChanged;		
		
		QY_OBJ_DB				*	pObjDb;
		char						switchMac[CONST_qyMacLen  +  1];
		char						mac[CONST_qyMacLen  +  1];

		TCHAR						des0[256];
		QY_SWITCHCONNECTEDPC_RCD	connInfo;
		unsigned  char				ucbDesMunually;
		
	}								m_var;


	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  switchMac,  char  *  mac  );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmEditMacInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmEditMacInfo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMEDITMACINFO_H__1AE8E581_32DE_4409_A231_00AE7F54C3DD__INCLUDED_)
