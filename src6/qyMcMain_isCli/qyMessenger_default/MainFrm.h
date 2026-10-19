// MainFrm.h : interface of the CMainFrame class
//


#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

	QY_MC_mainWndVar			var;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual void GetMessageString(UINT nID, CString& rMessage) const;

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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHelp();
	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);
	afx_msg void OnViewDebugStatus(  UINT nID  );
 	afx_msg void OnUpdateViewDebugStatus(CCmdUI *pCmdUI);
	afx_msg void OnqyClearUp();
	afx_msg void OnUpdateqyClearUp(CCmdUI* pCmdUI);
	afx_msg  LRESULT  OnQyHotKey( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyPostComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyTrayNotify( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyGraphNotify_mediaFile( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyGraphNotify_mediaDevice( WPARAM, LPARAM );

	afx_msg void Onqyrefresh();
	afx_msg void Onqysearch();
};


