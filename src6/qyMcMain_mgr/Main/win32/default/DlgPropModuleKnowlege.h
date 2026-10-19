#if !defined(AFX_DLGPROPMODULEKNOWLEGE_H__35F66E68_154E_466B_B05E_D544DC5B6018__INCLUDED_)
#define AFX_DLGPROPMODULEKNOWLEGE_H__35F66E68_154E_466B_B05E_D544DC5B6018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropModuleKnowlege.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropModuleKnowlege dialog

class CDlgPropModuleKnowlege : public CDialog
{
// Construction
public:
	CDlgPropModuleKnowlege(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropModuleKnowlege)
	enum { IDD = IDD_prop_moduleKnowlege };
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
	//{{AFX_VIRTUAL(CDlgPropModuleKnowlege)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropModuleKnowlege)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPMODULEKNOWLEGE_H__35F66E68_154E_466B_B05E_D544DC5B6018__INCLUDED_)
