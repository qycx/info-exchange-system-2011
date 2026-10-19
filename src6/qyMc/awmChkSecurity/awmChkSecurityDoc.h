// awmChkSecurityDoc.h : interface of the CAwmChkSecurityDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AWMCHKSECURITYDOC_H__548382EB_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_)
#define AFX_AWMCHKSECURITYDOC_H__548382EB_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAwmChkSecurityDoc : public CDocument
{
protected: // create from serialization only
	CAwmChkSecurityDoc();
	DECLARE_DYNCREATE(CAwmChkSecurityDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAwmChkSecurityDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAwmChkSecurityDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAwmChkSecurityDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AWMCHKSECURITYDOC_H__548382EB_EC5F_11D5_BD4B_00C0DFC4F67E__INCLUDED_)
