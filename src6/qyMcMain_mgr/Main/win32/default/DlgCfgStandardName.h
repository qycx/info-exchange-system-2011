#if !defined(AFX_DLGCFGSTANDARDNAME_H__5FB8847F_2B5B_49A6_A4A7_6E3940FCB184__INCLUDED_)
#define AFX_DLGCFGSTANDARDNAME_H__5FB8847F_2B5B_49A6_A4A7_6E3940FCB184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgStandardName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgStandardName dialog

class CDlgCfgStandardName : public CDialog
{
// Construction
public:
	CDlgCfgStandardName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgStandardName)
	enum { IDD = IDD_cfgStandardName };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct					{
		QY_OBJ_DB		*	pObjDb;

		char				mac0[CONST_qyMacLen  +  1];
		
		TCHAR				misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID		idInfo;
		
		int					id;
		//

		QY_CUSNAME_RCD		oldCusName;
		QY_CUSNAME_RCD		cusName;

	}				m_var;

	BOOL	bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  mac0,  int  id  );
	BOOL	bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  id  );

	int  procCheck(  int  idcCheck,  int  idcEdit,  int  idcEdit_standard  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgStandardName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgStandardName)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCHECKzb();
	afx_msg void OnCHECKbb();
	afx_msg void OnCHECKdw();
	afx_msg void OnCHECKbm();
	afx_msg void OnCHECKsyr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSTANDARDNAME_H__5FB8847F_2B5B_49A6_A4A7_6E3940FCB184__INCLUDED_)
