// secChkFactoryDoc.h : interface of the CSecChkFactoryDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECCHKFACTORYDOC_H__4DD11DAA_7BDC_42C7_8E8C_4CFBE13DCA93__INCLUDED_)
#define AFX_SECCHKFACTORYDOC_H__4DD11DAA_7BDC_42C7_8E8C_4CFBE13DCA93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSecChkFactoryDoc : public CDocument
{
protected: // create from serialization only
	CSecChkFactoryDoc();
	DECLARE_DYNCREATE(CSecChkFactoryDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecChkFactoryDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSecChkFactoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSecChkFactoryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECCHKFACTORYDOC_H__4DD11DAA_7BDC_42C7_8E8C_4CFBE13DCA93__INCLUDED_)
