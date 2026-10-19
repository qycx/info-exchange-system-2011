#if !defined(AFX_DLGQNMCFGPCNETWORKRULE_H__CD73B96F_2064_4DE9_B220_746162D53738__INCLUDED_)
#define AFX_DLGQNMCFGPCNETWORKRULE_H__CD73B96F_2064_4DE9_B220_746162D53738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcNetworkRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcNetworkRule dialog

class CDlgQnmCfgPcNetworkRule : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcNetworkRule(CWnd* pParent = NULL);   // standard constructor

	struct							{
		unsigned  char				ucbChanged;

		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		char						mac0[CONST_qyMacLen  +  1];
		unsigned  int				uiType;
		char						devIdStr[255  +  1];
		int							devIndex;
		char						mac[CONST_qyMacLen  +  1];
		int							id;

		QY_PCADAPTER_RCD			pcAdapterRcd;
		char						firstDns[CONST_qyMaxIpLen  +  1];
		char						secondaryDns[CONST_qyMaxIpLen  +  1];

		unsigned  char				ucbRuleExists;

	}								m_var;


	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  mac0,  unsigned  int  uiPcNetworkPropType,  char  *  devIdStr,  int  devIndex,  char  *  mac,  int  id  );


// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcNetworkRule)
	enum { IDD = IDD_qnmCfgPcNetworkRule };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcNetworkRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcNetworkRule)
	virtual BOOL OnInitDialog();
	afx_msg void OnRADIOucbDhcpEnabled();
	afx_msg void OnRADIOstaticIp();
	afx_msg void OnRADIOautoDns();
	afx_msg void OnRADIOstaticDns();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCNETWORKRULE_H__CD73B96F_2064_4DE9_B220_746162D53738__INCLUDED_)
