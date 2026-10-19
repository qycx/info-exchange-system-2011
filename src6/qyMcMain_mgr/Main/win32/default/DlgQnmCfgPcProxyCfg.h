#if !defined(AFX_DLGQNMCFGPCPROXYCFG_H__048FA3C8_0708_409C_8FE5_7E5C6E3C3857__INCLUDED_)
#define AFX_DLGQNMCFGPCPROXYCFG_H__048FA3C8_0708_409C_8FE5_7E5C6E3C3857__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcProxyCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcProxyCfg dialog

class CDlgQnmCfgPcProxyCfg : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcProxyCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcProxyCfg)
	enum { IDD = IDD_qnmCfgPcProxyCfg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		unsigned  char				ucbChanged;

		int							iDlgType;
		QY_OBJ_DB			*		pObjDb;
		char						mac0[CONST_qyMacLen  +  1];
		unsigned  int				uiType;
		int							id;

		QY_PCADAPTER_RCD			pcAdapterRcd;

		unsigned  char				ucbRuleExists;

	}					m_var;
	CQyRestrictEdit		m_edits[CONST_qnmMaxSearchFields];

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcProxyCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcProxyCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKautoConfigUrl();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCPROXYCFG_H__048FA3C8_0708_409C_8FE5_7E5C6E3C3857__INCLUDED_)
