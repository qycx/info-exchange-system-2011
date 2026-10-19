// kkDoc.h : interface of the CKkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KKDOC_H__33985537_1AE8_4BB1_B49E_5CCEAC5DE188__INCLUDED_)
#define AFX_KKDOC_H__33985537_1AE8_4BB1_B49E_5CCEAC5DE188__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKkDoc : public CDocument
{
protected: // create from serialization only
	CKkDoc();
	DECLARE_DYNCREATE(CKkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KKDOC_H__33985537_1AE8_4BB1_B49E_5CCEAC5DE188__INCLUDED_)
