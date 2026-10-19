// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__6DEFB18F_1CFD_42D7_B9A3_5C617EE4DD6F__INCLUDED_)
#define AFX_LEFTVIEW_H__6DEFB18F_1CFD_42D7_B9A3_5C617EE4DD6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "qyMcMainCommon.h"

class CQyMcDoc;




class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CTreeCtrl	*	m_TreeCtrl;
	CImageList		m_ImageList;

	CQyMcDoc* GetDocument();

	struct						{
			
		HTREEITEM				htMyRootItem;
		TCHAR					misServName[32  +  1];			//  这个值应该跟htMyRootItem关联。因为以后将有多个服务器，一个服务器相当与一个顶节点。服务器以misServName为键值，还可以定义各种显示名;
																//  服务器目前只有一个，并且为""值
		TCHAR					misServDisplayName[64  +  1];
		//
		BOOL					bInitialized;
		HTREEITEM				htInitialItem;
		
		QY_MC_DISPLAYCFG		m_displayCfg;

		////
		//
		
		/*
		GENERIC_Q				displayedObjQ;					//  2007/06/09
		BOOL					bQInited;
		void			**		ppDisplayedObjs_sortedByKey;	//  动态分配，用messengerId来排序						
		//  void			**		ppSorted_byHandle;			//  动态分配，用hItem来排序, 此变量暂时不用。实际应该是有用的
		*/
		MC_CTX_DISPLAYEDWND		displayCtx;
		BOOL					bDisplayCtxInited;

	}							m_var;

#ifdef  __DEBUG__
	void  showItem(  HTREEITEM  htItem  );
#endif

private:
	CWnd	*	getMgrWnd( );

// Operations
public:
	BOOL	bInitialDisplay(  );
	BOOL	bDisplayContent(  );
	BOOL	bRefreshItem(  HTREEITEM  hItem  );
	virtual HTREEITEM GetLastItem( HTREEITEM hItem );
	virtual HTREEITEM GetNextItem( HTREEITEM hItem );
	virtual HTREEITEM GetPrevItem( HTREEITEM hItem );
	virtual HTREEITEM FindItem( CString &sSearch, BOOL bCaseSensitive = FALSE, BOOL bDownDir = TRUE, BOOL bWholeWord = FALSE, HTREEITEM hItem = NULL );
	virtual HTREEITEM FindItemData( DWORD lParam, BOOL bDownDir = TRUE, HTREEITEM hItem = NULL );
protected:
	virtual BOOL IsFindValid( HTREEITEM );
	BOOL bGetNodePath( HTREEITEM h, char *path, unsigned int size );
	BOOL bRootTreeGetSel(  CTreeCtrl &	treeCtrl,  HTREEITEM  hRoot,  HTREEITEM  hCur,  QY_MC_SEL  *pCurSel  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM, LPARAM  );
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CQyMcDoc* CLeftView::GetDocument()
   { return (CQyMcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__6DEFB18F_1CFD_42D7_B9A3_5C617EE4DD6F__INCLUDED_)
