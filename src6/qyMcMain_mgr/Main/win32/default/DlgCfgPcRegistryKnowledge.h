#if !defined(AFX_DLGCFGPCREGISTRYKNOWLEDGE_H__9A555487_A3B0_498C_9489_2F3D7BDD2E25__INCLUDED_)
#define AFX_DLGCFGPCREGISTRYKNOWLEDGE_H__9A555487_A3B0_498C_9489_2F3D7BDD2E25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgPcRegistryKnowledge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistryKnowledge dialog

class CDlgCfgPcRegistryKnowledge : public CDialog
{
// Construction
public:
	CDlgCfgPcRegistryKnowledge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgPcRegistryKnowledge)
	enum { IDD = IDD_cfgPcRegistryKnowledge };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		int							id;
		int							iRootKey;
		TCHAR						subKey[MAX_PATH  +  1];
		TCHAR						cfgName[MAX_PATH  +  1];
		//
		QY_PCREGISTRYKNOWLEDGE_RCD	knowledge;
	}								m_var;


	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  iRootKey,  LPCTSTR  subKey,  LPCTSTR  cfgName,  int  id  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgPcRegistryKnowledge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgPcRegistryKnowledge)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGPCREGISTRYKNOWLEDGE_H__9A555487_A3B0_498C_9489_2F3D7BDD2E25__INCLUDED_)
