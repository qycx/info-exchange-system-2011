// captureDoc.h : interface of the CCaptureDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPTUREDOC_H__110CA6BB_4192_11D4_8E0E_00E04C190D59__INCLUDED_)
#define AFX_CAPTUREDOC_H__110CA6BB_4192_11D4_8E0E_00E04C190D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCaptureDoc : public CDocument
{
protected: // create from serialization only
	CCaptureDoc();
	DECLARE_DYNCREATE(CCaptureDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCaptureDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCaptureDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREDOC_H__110CA6BB_4192_11D4_8E0E_00E04C190D59__INCLUDED_)
