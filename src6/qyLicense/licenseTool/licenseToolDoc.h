// licenseToolDoc.h : interface of the CLicenseToolDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICENSETOOLDOC_H__C794AA82_2B7B_46DF_88DA_1CC71B946DBF__INCLUDED_)
#define AFX_LICENSETOOLDOC_H__C794AA82_2B7B_46DF_88DA_1CC71B946DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLicenseToolDoc : public CDocument
{
protected: // create from serialization only
	CLicenseToolDoc();
	DECLARE_DYNCREATE(CLicenseToolDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseToolDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLicenseToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLicenseToolDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENSETOOLDOC_H__C794AA82_2B7B_46DF_88DA_1CC71B946DBF__INCLUDED_)
