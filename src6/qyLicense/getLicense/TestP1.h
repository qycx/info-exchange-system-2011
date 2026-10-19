#if !defined(AFX_TESTP1_H__9DCF5444_9CFD_4C6B_B791_6D3B189DB8BD__INCLUDED_)
#define AFX_TESTP1_H__9DCF5444_9CFD_4C6B_B791_6D3B189DB8BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestP1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestP1 dialog

class CTestP1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestP1)

// Construction
public:
	CTestP1();
	~CTestP1();

// Dialog Data
	//{{AFX_DATA(CTestP1)
	enum { IDD = IDD_P1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestP1)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestP1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnButton1();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTP1_H__9DCF5444_9CFD_4C6B_B791_6D3B189DB8BD__INCLUDED_)
