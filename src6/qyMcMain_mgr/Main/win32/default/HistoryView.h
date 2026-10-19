#if !defined(AFX_HISTORYVIEW_H__A5CBD45C_11AE_4F68_963D_7571B0FA589D__INCLUDED_)
#define AFX_HISTORYVIEW_H__A5CBD45C_11AE_4F68_963D_7571B0FA589D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistoryView view

class CHistoryView : public CView
{
protected:
	CHistoryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHistoryView)

// Attributes
public:
	int m_tmpi;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHistoryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYVIEW_H__A5CBD45C_11AE_4F68_963D_7571B0FA589D__INCLUDED_)
