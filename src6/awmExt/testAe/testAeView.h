// testAeView.h : interface of the CTestAeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTAEVIEW_H__6FFED791_521D_4313_A626_2702D23B21F2__INCLUDED_)
#define AFX_TESTAEVIEW_H__6FFED791_521D_4313_A626_2702D23B21F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestAeView : public CView
{
protected: // create from serialization only
	CTestAeView();
	DECLARE_DYNCREATE(CTestAeView)

// Attributes
public:
	CTestAeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAeView)
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
	virtual ~CTestAeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestAeView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in testAeView.cpp
inline CTestAeDoc* CTestAeView::GetDocument()
   { return (CTestAeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAEVIEW_H__6FFED791_521D_4313_A626_2702D23B21F2__INCLUDED_)
