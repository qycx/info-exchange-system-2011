// awmChkSecurityView.h : interface of the CAwmChkSecurityView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AWMCHKSECURITYVIEW_H__548382ED_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_)
#define AFX_AWMCHKSECURITYVIEW_H__548382ED_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAwmChkSecurityView : public CView
{
protected: // create from serialization only
	CAwmChkSecurityView();
	DECLARE_DYNCREATE(CAwmChkSecurityView)

// Attributes
public:
	CAwmChkSecurityDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwmChkSecurityView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAwmChkSecurityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAwmChkSecurityView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in awmChkSecurityView.cpp
inline CAwmChkSecurityDoc* CAwmChkSecurityView::GetDocument()
   { return (CAwmChkSecurityDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWMCHKSECURITYVIEW_H__548382ED_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_)
