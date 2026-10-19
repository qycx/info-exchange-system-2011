// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__DC9C7BA4_5346_45EA_BCC2_CE9EEDC94252__INCLUDED_)
#define AFX_CHILDFRM_H__DC9C7BA4_5346_45EA_BCC2_CE9EEDC94252__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "qyMcMainCommon.h"

class CLeftView;
class CQyMcView;
// class CHistoryView;


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
	CSplitterWnd				m_wndSplitter;
	// CSplitterWnd				m_wndSplitter2;
	
	// #define  CCHILDFRAME_VIEW_CNT	3	// 注意：暂时不设历史窗口，故定义改为2
	#define  CCHILDFRAME_VIEW_CNT		2
	struct  {

		UINT					m_uCfgTimerId;		// 配置值
		UINT					m_uTimerId;		// SetTimer( )的返回值
		BOOL					m_bInTimer;		// 在WM_TIMER消息处理函数里

		QY_MC_MGRVIEWSTRUCT  mgrLeft;
		QY_MC_MGRVIEWSTRUCT  mgrRight;
		// QY_MC_MGR_VIEW_STRUCT  mgrBottom;

		BOOL					m_bToBeDestroyed;	
		BOOL					m_bToBeClosed;
		
	}  var;
public:

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CMDIFrameWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
public:
	CQyMcView		*			GetRightPane();
	// CHistoryView	*			getHistoryView( );
	// CQyMcView		*			getQyMcView( );
	CQyMcView		*			getLeftView( );
	CQyMcView		*			getRightView( );
	// CHistoryView	*			getBottomView( );


	
// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg LRESULT OnQyComm(WPARAM, LPARAM);
	afx_msg	LRESULT OnQyPutData( WPARAM, LPARAM );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__DC9C7BA4_5346_45EA_BCC2_CE9EEDC94252__INCLUDED_)
