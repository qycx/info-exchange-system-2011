// kkView.h : interface of the CKkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KKVIEW_H__8168DFD2_ECB7_454B_935D_C798972E3E04__INCLUDED_)
#define AFX_KKVIEW_H__8168DFD2_ECB7_454B_935D_C798972E3E04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKkView : public CView
{
protected: // create from serialization only
	CKkView();
	DECLARE_DYNCREATE(CKkView)

// Attributes
public:
	CKkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKkView)
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
	virtual ~CKkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKkView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in kkView.cpp
inline CKkDoc* CKkView::GetDocument()
   { return (CKkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KKVIEW_H__8168DFD2_ECB7_454B_935D_C798972E3E04__INCLUDED_)
