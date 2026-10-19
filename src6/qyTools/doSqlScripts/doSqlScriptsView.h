// doSqlScriptsView.h : interface of the CDoSqlScriptsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOSQLSCRIPTSVIEW_H__79AA3B9E_F7EC_4091_921C_4D4C17AA5FAC__INCLUDED_)
#define AFX_DOSQLSCRIPTSVIEW_H__79AA3B9E_F7EC_4091_921C_4D4C17AA5FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDoSqlScriptsView : public CView
{
protected: // create from serialization only
	CDoSqlScriptsView();
	DECLARE_DYNCREATE(CDoSqlScriptsView)

// Attributes
public:
	CDoSqlScriptsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoSqlScriptsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDoSqlScriptsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDoSqlScriptsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in doSqlScriptsView.cpp
inline CDoSqlScriptsDoc* CDoSqlScriptsView::GetDocument()
   { return (CDoSqlScriptsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSQLSCRIPTSVIEW_H__79AA3B9E_F7EC_4091_921C_4D4C17AA5FAC__INCLUDED_)
