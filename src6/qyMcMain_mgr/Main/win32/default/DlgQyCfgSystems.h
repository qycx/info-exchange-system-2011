#if !defined(AFX_DLGQYCFGSYSTEMS_H__C61BB8F5_ED31_4C0B_B90C_0E8A1B624B55__INCLUDED_)
#define AFX_DLGQYCFGSYSTEMS_H__C61BB8F5_ED31_4C0B_B90C_0E8A1B624B55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQyCfgSystems.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCfgSystems dialog

class CDlgQyCfgSystems : public CDialog
{
// Construction
public:
	CDlgQyCfgSystems(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQyCfgSystems)
	enum { IDD = IDD_qyCfgSystems };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct						{
		BOOL					bNeedRefreshAll;
		
		int						idcList;
		TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
		int						nFields;
		QY_COLUMNINFO		*	pColumns;
		int						nItemSelected;
		int						idSelected;
		unsigned  char			ucbIdSeletedValid;
		
	}							m_var;


	//  int  listCfgStandardNames(  );
	BOOL  bRefreshButtons(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQyCfgSystems)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQyCfgSystems)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDel();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQYCFGSYSTEMS_H__C61BB8F5_ED31_4C0B_B90C_0E8A1B624B55__INCLUDED_)
