#if !defined(AFX_PPQNMSTATUSRINFO_H__5E888010_717C_4A2B_AF2E_3C1333D7201D__INCLUDED_)
#define AFX_PPQNMSTATUSRINFO_H__5E888010_717C_4A2B_AF2E_3C1333D7201D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQnmStatUsrInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatUsrInfo dialog

class CPpQnmStatUsrInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQnmStatUsrInfo)

// Construction
public:
	CPpQnmStatUsrInfo();
	~CPpQnmStatUsrInfo();

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
	//{{AFX_DATA(CPpQnmStatUsrInfo)
	enum { IDD = IDD_qnmStatUsrInfo };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQnmStatUsrInfo)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQnmStatUsrInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo0();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQNMSTATUSRINFO_H__5E888010_717C_4A2B_AF2E_3C1333D7201D__INCLUDED_)
