#if !defined(AFX_DLGPROPPCREGISTRYKNOWLEDGE_H__1427A406_A8E8_49C2_9909_4579E6A37510__INCLUDED_)
#define AFX_DLGPROPPCREGISTRYKNOWLEDGE_H__1427A406_A8E8_49C2_9909_4579E6A37510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropPcRegistryKnowledge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcRegistryKnowledge dialog

class CDlgPropPcRegistryKnowledge : public CDialog
{
// Construction
public:
	CDlgPropPcRegistryKnowledge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropPcRegistryKnowledge)
	enum { IDD = IDD_prop_pcRegistryKnowledge };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{

		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		int							id;
		int							iRootKey;
		TCHAR						subKey[MAX_PATH  +  1];
		TCHAR						cfgName[MAX_PATH  +  1];

		QY_PCREGISTRYKNOWLEDGE_RCD	knowledge;


	}								m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  iRootKey,  LPCTSTR  subKey,  LPCTSTR  cfgName,  int  id  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropPcRegistryKnowledge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropPcRegistryKnowledge)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPPCREGISTRYKNOWLEDGE_H__1427A406_A8E8_49C2_9909_4579E6A37510__INCLUDED_)
