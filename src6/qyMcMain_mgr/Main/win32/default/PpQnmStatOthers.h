#if !defined(AFX_PPQNMSTATOTHERS_H__9458C8D9_432E_4532_A1F9_A4A9AE378F7A__INCLUDED_)
#define AFX_PPQNMSTATOTHERS_H__9458C8D9_432E_4532_A1F9_A4A9AE378F7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQnmStatOthers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatOthers dialog

class CPpQnmStatOthers : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQnmStatOthers)

// Construction
public:
	CPpQnmStatOthers();
	~CPpQnmStatOthers();

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
	//{{AFX_DATA(CPpQnmStatOthers)
	enum { IDD = IDD_qnmStatOthers };
	CDateTimeCtrl	m_startTimeCtrl;
	CDateTimeCtrl	m_startDateCtrl;
	CDateTimeCtrl	m_endTimeCtrl;
	CDateTimeCtrl	m_endDateCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQnmStatOthers)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQnmStatOthers)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQNMSTATOTHERS_H__9458C8D9_432E_4532_A1F9_A4A9AE378F7A__INCLUDED_)
