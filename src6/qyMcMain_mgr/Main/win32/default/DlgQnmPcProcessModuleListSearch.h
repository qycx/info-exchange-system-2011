#if !defined(AFX_DLGQNMPCPROCESSMODULELISTSEARCH_H__41A3F054_89C8_4375_B9BA_52185AD9E072__INCLUDED_)
#define AFX_DLGQNMPCPROCESSMODULELISTSEARCH_H__41A3F054_89C8_4375_B9BA_52185AD9E072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmPcProcessModuleListSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcProcessModuleListSearch dialog

class CDlgQnmPcProcessModuleListSearch : public CDialog
{
// Construction
public:
	CDlgQnmPcProcessModuleListSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmPcProcessModuleListSearch)
	enum { IDD = IDD_qnmPcProcessModuleListSearch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct			{
		TCHAR		title[256];
		TCHAR		hint[256];
		TCHAR		moduleName[MAX_PATH  +  1];
	}				m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  LPCTSTR  title,  LPCTSTR  hint  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmPcProcessModuleListSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmPcProcessModuleListSearch)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMPCPROCESSMODULELISTSEARCH_H__41A3F054_89C8_4375_B9BA_52185AD9E072__INCLUDED_)
