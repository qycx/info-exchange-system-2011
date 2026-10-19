#if !defined(AFX_DLGCFGPCREGISTRY_H__1FBD706A_32FF_4395_AAD4_E5F7A85C9BC0__INCLUDED_)
#define AFX_DLGCFGPCREGISTRY_H__1FBD706A_32FF_4395_AAD4_E5F7A85C9BC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgPcRegistry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistry dialog

#define		CONST_maxRegSubKeySize		255


class CDlgCfgPcRegistry : public CDialog
{
// Construction
public:
	CDlgCfgPcRegistry(CWnd* pParent = NULL);   // standard constructor

	struct						{
		int						iDlgType;
		int						id;
		//
		int						iRootKey;
		TCHAR					subKey[CONST_maxRegSubKeySize  +  1];
		TCHAR					cfgName[255  +  1];
		unsigned  int			nIntervals;
		//
		unsigned  char							ucbUnsupport98;
		unsigned  char							ucbUnsupportMe;
		unsigned  char							ucbUnsupportNt;
		unsigned  char							ucbUnsupport2k;
		unsigned  char							ucbUnsupportXp;
		unsigned  char							ucbUnsupport2003;
		unsigned  char							ucbUnsupportVista;
		//
		unsigned  char							ucbNotLogAdd;
		unsigned  char							ucbNotLogDel;
		unsigned  char							ucbNotLogModify;
		//
		QY_PCREGISTRYRULE_RCD		oldRcd;
		//
		unsigned  char			ucbChanged;
	}							m_var;

	BOOL						bSetDlgInfo(  int  iDlgType,  int  id  );

// Dialog Data
	//{{AFX_DATA(CDlgCfgPcRegistry)
	enum { IDD = IDD_cfgPcRegistry };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgPcRegistry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgPcRegistry)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGPCREGISTRY_H__1FBD706A_32FF_4395_AAD4_E5F7A85C9BC0__INCLUDED_)
