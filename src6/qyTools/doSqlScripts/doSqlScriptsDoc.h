// doSqlScriptsDoc.h : interface of the CDoSqlScriptsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOSQLSCRIPTSDOC_H__F2779A5A_1123_4C93_AFBB_6A8C5ECB7BE1__INCLUDED_)
#define AFX_DOSQLSCRIPTSDOC_H__F2779A5A_1123_4C93_AFBB_6A8C5ECB7BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDoSqlScriptsDoc : public CDocument
{
protected: // create from serialization only
	CDoSqlScriptsDoc();
	DECLARE_DYNCREATE(CDoSqlScriptsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoSqlScriptsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDoSqlScriptsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDoSqlScriptsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSQLSCRIPTSDOC_H__F2779A5A_1123_4C93_AFBB_6A8C5ECB7BE1__INCLUDED_)
