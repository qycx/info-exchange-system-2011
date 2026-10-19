#if !defined(AFX_DLGCFGPCPROCESSRULE_H__63DB1F4C_8317_4DAA_B032_2BF097C43905__INCLUDED_)
#define AFX_DLGCFGPCPROCESSRULE_H__63DB1F4C_8317_4DAA_B032_2BF097C43905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgPcProcessRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcProcessRule dialog

class CDlgCfgPcProcessRule : public CDialog
{
// Construction
public:
	CDlgCfgPcProcessRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgPcProcessRule)
	enum { IDD = IDD_cfgPcProcessRule };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct					{
		QY_OBJ_DB		*	pObjDb;
		char				mac0[CONST_qyMacLen  +  1];
		char				name[255  +  1];
	}						m_var;

	BOOL		bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  mac  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgPcProcessRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgPcProcessRule)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGPCPROCESSRULE_H__63DB1F4C_8317_4DAA_B032_2BF097C43905__INCLUDED_)
