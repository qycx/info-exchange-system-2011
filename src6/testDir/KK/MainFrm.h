// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__39639BAF_7E25_4FD9_915F_23342B462D8F__INCLUDED_)
#define AFX_MAINFRM_H__39639BAF_7E25_4FD9_915F_23342B462D8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void Ontest();
	afx_msg void OntestWiz();
	afx_msg void OntestPs();
	afx_msg void OntestStatusDlg();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OntestUsr();
	afx_msg void OntestFor();
	afx_msg void OntestQwmSend();
	afx_msg void OntestHttp();
	afx_msg void OntestMfcHttp();
	afx_msg void Ontestqqq();
	afx_msg void OntestPrintf();
	afx_msg void OntestNh();
	afx_msg void Onphbk();
	afx_msg BOOL Ondog();
	afx_msg BOOL OntestLicense();
	afx_msg void OntestInsert();
	afx_msg void OntestDelete();
	afx_msg void OntestSelect();
	afx_msg void OntestHideProcess();
	afx_msg void OntestShowProcess();
	afx_msg void Oncpu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__39639BAF_7E25_4FD9_915F_23342B462D8F__INCLUDED_)
