// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__39815A64_F446_470F_ABCA_DDCB09A95603__INCLUDED_)
#define AFX_MAINFRM_H__39815A64_F446_470F_ABCA_DDCB09A95603__INCLUDED_

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
	afx_msg void OntestIpScan();
	afx_msg void OntestSql();
	afx_msg void OnmakeNetMcDb();
	afx_msg void OnUpdatemakeNetMcDb(CCmdUI* pCmdUI);
	afx_msg void OnmakeNetMcTestData();
	afx_msg void OnUpdatemakeNetMcTestData(CCmdUI* pCmdUI);
	afx_msg void OnmakeMsgDb();
	afx_msg void OnmakeMsgMgrDb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__39815A64_F446_470F_ABCA_DDCB09A95603__INCLUDED_)
