// captureView.h : interface of the CCaptureView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPTUREVIEW_H__110CA6BD_4192_11D4_8E0E_00E04C190D59__INCLUDED_)
#define AFX_CAPTUREVIEW_H__110CA6BD_4192_11D4_8E0E_00E04C190D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCaptureView : public CView
{
protected: // create from serialization only
	CCaptureView();
	DECLARE_DYNCREATE(CCaptureView)

// Attributes
public:
	CCaptureDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureView)
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
	virtual ~CCaptureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCaptureView)
	afx_msg void OnWzd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in captureView.cpp
inline CCaptureDoc* CCaptureView::GetDocument()
   { return (CCaptureDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREVIEW_H__110CA6BD_4192_11D4_8E0E_00E04C190D59__INCLUDED_)
