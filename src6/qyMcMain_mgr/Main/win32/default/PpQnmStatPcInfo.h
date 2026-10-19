#if !defined(AFX_PPQNMSTATPCINFO_H__CEDD0A70_0AD9_4E11_ACE6_CA430D8232BC__INCLUDED_)
#define AFX_PPQNMSTATPCINFO_H__CEDD0A70_0AD9_4E11_ACE6_CA430D8232BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQnmStatPcInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatPcInfo dialog

class CPpQnmStatPcInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQnmStatPcInfo)

// Construction
public:
	CPpQnmStatPcInfo();
	~CPpQnmStatPcInfo();

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

// Dialog Data
	//{{AFX_DATA(CPpQnmStatPcInfo)
	enum { IDD = IDD_qnmStatPcInfo };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQnmStatPcInfo)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQnmStatPcInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo0();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQNMSTATPCINFO_H__CEDD0A70_0AD9_4E11_ACE6_CA430D8232BC__INCLUDED_)
