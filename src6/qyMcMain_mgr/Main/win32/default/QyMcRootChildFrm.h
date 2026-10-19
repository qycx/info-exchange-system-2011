#if !defined(AFX_QYMCROOTCHILDFRM_H__FAFB676C_F82F_4F57_97EF_D0ACB66BB2F1__INCLUDED_)
#define AFX_QYMCROOTCHILDFRM_H__FAFB676C_F82F_4F57_97EF_D0ACB66BB2F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyMcRootChildFrm.h : header file
//

/*
#include "qyMcDoc.h"
#include "qyMcView.h"
#include "leftView.h"
*/

/////////////////////////////////////////////////////////////////////////////
// CQyMcRootChildFrm frame

class CQyMcRootChildFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CQyMcRootChildFrm)
protected:
	CQyMcRootChildFrm();           // protected constructor used by dynamic creation

// Attributes
public:
	CSplitterWnd			m_wndSplitter;
	struct {
		UINT					m_uCfgTimerId;		// 配置值
		UINT					m_uTimerId;			// SetTimer( )的返回值
		BOOL					m_bInTimer;			// 在WM_TIMER消息处理函数里
		
		QY_MC_MGRVIEWSTRUCT		mgrLeft;			//  CLeftView
		QY_MC_MGRVIEWSTRUCT		mgrRight;			//  CQyMcView

		BOOL					m_bToBeDestroyed;	
		BOOL					m_bToBeClosed;

		QY_WMBUF_FOCUSONITEM	wmBuf;				//  当双击右边的节点时，需要在leftView那里变焦，参数用这个wmBuf来暂存，以后应改为队列
		
	} var;
	
// Operations
public:
	CQyMcView		*			GetRightPane( );
	CQyMcView		*			getQyMcView( );
	CLeftView		*			getLeftView( );
	CQyMcView		*			getRightView(  );
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyMcRootChildFrm)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CMDIFrameWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQyMcRootChildFrm();

	// Generated message map functions
	//{{AFX_MSG(CQyMcRootChildFrm)
	afx_msg void OnUpdateWindowNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	afx_msg LRESULT OnQyPutData( WPARAM, LPARAM );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYMCROOTCHILDFRM_H__FAFB676C_F82F_4F57_97EF_D0ACB66BB2F1__INCLUDED_)
