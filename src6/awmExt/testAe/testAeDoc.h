// testAeDoc.h : interface of the CTestAeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTAEDOC_H__5A207B4D_E5EF_487E_9B69_A0896E03526F__INCLUDED_)
#define AFX_TESTAEDOC_H__5A207B4D_E5EF_487E_9B69_A0896E03526F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestAeDoc : public CDocument
{
protected: // create from serialization only
	CTestAeDoc();
	DECLARE_DYNCREATE(CTestAeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestAeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestAeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAEDOC_H__5A207B4D_E5EF_487E_9B69_A0896E03526F__INCLUDED_)
