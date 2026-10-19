#if !defined(AFX_TESTP_H__41461648_194C_488B_8840_0E8EF376E7A6__INCLUDED_)
#define AFX_TESTP_H__41461648_194C_488B_8840_0E8EF376E7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestP dialog

class CTestP : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestP)

// Construction
public:
	CTestP();
	~CTestP();

// Dialog Data
	//{{AFX_DATA(CTestP)
	enum { IDD = IDD_testP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestP)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTP_H__41461648_194C_488B_8840_0E8EF376E7A6__INCLUDED_)
