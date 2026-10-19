#if !defined(AFX_PPQYEXPORT_H__A46ED166_B338_45C4_9D1E_E9E7879C0A27__INCLUDED_)
#define AFX_PPQYEXPORT_H__A46ED166_B338_45C4_9D1E_E9E7879C0A27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQyExport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQyExport dialog

class CPpQyExport : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQyExport)

// Construction
public:
	CPpQyExport();
	~CPpQyExport();

// Dialog Data
	//{{AFX_DATA(CPpQyExport)
	enum { IDD = IDD_qyExport };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQyExport)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQyExport)
	afx_msg void OnRADIOexportCurQuery();
	afx_msg void OnRADIOexportRegInfo();
	afx_msg void OnRADIOexportCfg();
	afx_msg void OnRADIOexportBhbCfg();
	afx_msg void OnRADIOexportBakData();
	afx_msg void OnRADIOprocDj();
	afx_msg void OnBnClickedRadioprocdj98();
	afx_msg void OnRADIOprocModuleKnowlege();
	afx_msg void OnRADIOprocRegistryKnowlege();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedRadioprocipknowledge();
	afx_msg void OnBnClickedRadioprocphoneguest();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQYEXPORT_H__A46ED166_B338_45C4_9D1E_E9E7879C0A27__INCLUDED_)
