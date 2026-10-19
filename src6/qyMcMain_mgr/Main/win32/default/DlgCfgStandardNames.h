#if !defined(AFX_DLGCFGSTANDARDNAMES_H__AC9D735E_E829_4821_B8D3_57E3FDAC1E81__INCLUDED_)
#define AFX_DLGCFGSTANDARDNAMES_H__AC9D735E_E829_4821_B8D3_57E3FDAC1E81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgStandardNames.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgStandardNames dialog

class CDlgCfgStandardNames : public CDialog
{
// Construction
public:
	CDlgCfgStandardNames(CWnd* pParent = NULL);   // standard constructor

	struct						{
		BOOL					bNeedRefreshAll;
		
		QY_OBJ_DB			*	pObjDb;

		int						idcList;
		TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
		int						nFields;
		QY_COLUMNINFO		*	pColumns;
		int						nItemSelected;
		int						idSelected;
		unsigned  char			ucbIdSeletedValid;
		
	}							m_var;


	int  listCfgStandardNames(  );
	BOOL  bRefreshButtons(  );

// Dialog Data
	//{{AFX_DATA(CDlgCfgStandardNames)
	enum { IDD = IDD_cfgStandardNames };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgStandardNames)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgStandardNames)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedLISTcfgStandardName(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDel();
	afx_msg void OnDblclkLISTcfgStandardName(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBUTTONcfgStandardNames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGSTANDARDNAMES_H__AC9D735E_E829_4821_B8D3_57E3FDAC1E81__INCLUDED_)
