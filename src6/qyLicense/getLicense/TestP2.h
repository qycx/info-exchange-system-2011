#if !defined(AFX_TESTP2_H__C3A1DEB4_7D3F_4F94_A998_D472A1378FE1__INCLUDED_)
#define AFX_TESTP2_H__C3A1DEB4_7D3F_4F94_A998_D472A1378FE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestP2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestP2 dialog

class CTestP2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestP2)

// Construction
public:
	CTestP2();
	~CTestP2();

// Dialog Data
	//{{AFX_DATA(CTestP2)
	enum { IDD = IDD_P2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestP2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestP2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTP2_H__C3A1DEB4_7D3F_4F94_A998_D472A1378FE1__INCLUDED_)
