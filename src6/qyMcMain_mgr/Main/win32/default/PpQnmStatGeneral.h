#if !defined(AFX_PPQNMSTATGENERAL_H__A7044786_F49B_48DE_84ED_A0E6D9CC1388__INCLUDED_)
#define AFX_PPQNMSTATGENERAL_H__A7044786_F49B_48DE_84ED_A0E6D9CC1388__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQnmStatGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatGeneral dialog

class CPpQnmStatGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQnmStatGeneral)

// Construction
public:
	CPpQnmStatGeneral();
	~CPpQnmStatGeneral();

	struct								{
		QY_OBJ_DB				*		pObjDb;				//  2007/01/03

		BOOL							bOk;
		TCHAR							wherePart[CONST_qyMaxSqlClauseLen  +  1];
		TCHAR							groupPart[CONST_qyMaxSqlClauseLen  +  1];
		TCHAR							havingPart[CONST_qyMaxSqlClauseLen  +  1];
		QY_COLUMNINFO					sqlCols[CONST_qnmMaxStatCols  +  1];
		QY_COLUMNINFO					displayCols[CONST_qnmMaxStatCols  +  1];
	}									m_var;


// Dialog Data
	//{{AFX_DATA(CPpQnmStatGeneral)
	enum { IDD = IDD_qnmStatGeneral };
	CDateTimeCtrl	m_startTimeCtrl;
	CDateTimeCtrl	m_startDateCtrl;
	CDateTimeCtrl	m_endTimeCtrl;
	CDateTimeCtrl	m_endDateCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQnmStatGeneral)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQnmStatGeneral)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo0();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQNMSTATGENERAL_H__A7044786_F49B_48DE_84ED_A0E6D9CC1388__INCLUDED_)
