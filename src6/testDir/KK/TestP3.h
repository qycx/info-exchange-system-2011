#if !defined(AFX_TESTP3_H__F2E8ABC3_EFCD_48B7_8337_E5C5FD0EB324__INCLUDED_)
#define AFX_TESTP3_H__F2E8ABC3_EFCD_48B7_8337_E5C5FD0EB324__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestP3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestP3 dialog

class CTestP3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestP3)

// Construction
public:
	CTestP3();
	~CTestP3();

// Dialog Data
	//{{AFX_DATA(CTestP3)
	enum { IDD = IDD_P3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestP3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestP3)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTP3_H__F2E8ABC3_EFCD_48B7_8337_E5C5FD0EB324__INCLUDED_)
