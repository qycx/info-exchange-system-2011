#if !defined(AFX_PPSTATMESSENGERINFO_H__607359A0_65E9_4453_810D_DAEAB0BD0500__INCLUDED_)
#define AFX_PPSTATMESSENGERINFO_H__607359A0_65E9_4453_810D_DAEAB0BD0500__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpStatMessengerInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpStatMessengerInfo dialog

class CPpStatMessengerInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpStatMessengerInfo)

// Construction
public:
	CPpStatMessengerInfo();
	~CPpStatMessengerInfo();

// Dialog Data
	//{{AFX_DATA(CPpStatMessengerInfo)
	enum { IDD = IDD_statMessengerInfo };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	struct								{
		QY_OBJ_DB			*			pObjDb;									//  2007/01/03

		unsigned  int					uiType;									//  2007/09/22, 统计类型
		BOOL							bOk;
		TCHAR							wherePart[CONST_qyMaxSqlClauseLen  +  1];
		TCHAR							groupPart[CONST_qyMaxSqlClauseLen  +  1];
		TCHAR							havingPart[CONST_qyMaxSqlClauseLen  +  1];
		QY_COLUMNINFO					sqlCols[CONST_qnmMaxStatCols  +  1];
		QY_COLUMNINFO					displayCols[CONST_qnmMaxStatCols  +  1];
	}									m_var;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpStatMessengerInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpStatMessengerInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPSTATMESSENGERINFO_H__607359A0_65E9_4453_810D_DAEAB0BD0500__INCLUDED_)
