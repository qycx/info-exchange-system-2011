#if !defined(AFX_DLGCFGMODULEKNOWLEGE_H__8C06ACB2_173F_4B12_9B8C_6F7A38872537__INCLUDED_)
#define AFX_DLGCFGMODULEKNOWLEGE_H__8C06ACB2_173F_4B12_9B8C_6F7A38872537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgModuleKnowlege.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgModuleKnowlege dialog

class CDlgCfgModuleKnowlege : public CDialog
{
// Construction
public:
	CDlgCfgModuleKnowlege(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgModuleKnowlege)
	enum { IDD = IDD_cfgModuleKnowlege };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		int							id;
		TCHAR						fileName[MAX_PATH  +  1];
		TCHAR						cmdLine[255  +  1];
		QY_PCMODULEKNOWLEDGE_RCD	moduleKnowlege;
	}								m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  fileName,  LPCTSTR  cmdLine,  int  id  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgModuleKnowlege)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgModuleKnowlege)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCHECKbCmdLineGiven();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGMODULEKNOWLEGE_H__8C06ACB2_173F_4B12_9B8C_6F7A38872537__INCLUDED_)
