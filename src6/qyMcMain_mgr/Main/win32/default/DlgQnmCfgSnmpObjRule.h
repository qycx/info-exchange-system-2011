#if !defined(AFX_DLGQNMCFGSNMPOBJRULE_H__00324174_F611_4BEA_BE66_AEACD27CA86B__INCLUDED_)
#define AFX_DLGQNMCFGSNMPOBJRULE_H__00324174_F611_4BEA_BE66_AEACD27CA86B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgSnmpObjRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgSnmpObjRule dialog

class CDlgQnmCfgSnmpObjRule : public CDialog
{
// Construction
public:
	CDlgQnmCfgSnmpObjRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgSnmpObjRule)
	enum { IDD = IDD_qnmCfgSnmpObjRule };
	//}}AFX_DATA

	struct						{
		int						iDlgType;
		QY_OBJ_DB		*		pObjDb;
		char					switchMac[CONST_qyMacLen  +  1];
		int						iPortIfIndex;

		int						ibDownPortIfMacChanged_sys;
		int						ibDownPortIfWarnSpeed_sys;				//  2006/05/29
		int						iType;
		QY_SNMPOBJRULE_RCD		snmpObjRule;
		QY_SNMPOBJRULE_RCD		switchPortRule;
	}							m_var;
	
	BOOL		bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  switchMac,  int  iPortIfIndex  );		
	BOOL		bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgSnmpObjRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgSnmpObjRule)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGSNMPOBJRULE_H__00324174_F611_4BEA_BE66_AEACD27CA86B__INCLUDED_)
