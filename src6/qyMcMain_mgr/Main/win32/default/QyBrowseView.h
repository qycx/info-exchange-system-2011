#if !defined(AFX_QYBROWSEVIEW_H__F4E105AE_D9D8_4F98_9CA6_9E23CA3470A7__INCLUDED_)
#define AFX_QYBROWSEVIEW_H__F4E105AE_D9D8_4F98_9CA6_9E23CA3470A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyBrowseView.h : header file
//

#include "webBrowser2.h"

/////////////////////////////////////////////////////////////////////////////
// CQyBrowseView view

class CQyBrowseView : public CView
{
protected:
	CQyBrowseView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQyBrowseView)

// Attributes
public:
	CQyMcDoc * GetDocument(  );

// Operations
public:
	CWebBrowser2 * m_pBrowser;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyBrowseView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQyBrowseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CQyBrowseView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYBROWSEVIEW_H__F4E105AE_D9D8_4F98_9CA6_9E23CA3470A7__INCLUDED_)
