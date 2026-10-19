#if !defined(AFX_DLGCFGPCREGISTRYS_H__AA3BB778_90E8_44AD_AF25_59D2B1989174__INCLUDED_)
#define AFX_DLGCFGPCREGISTRYS_H__AA3BB778_90E8_44AD_AF25_59D2B1989174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgPcRegistrys.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgPcRegistrys dialog

class CDlgCfgPcRegistrys : public CDialog
{
// Construction
public:
	CDlgCfgPcRegistrys(CWnd* pParent = NULL);   // standard constructor


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


	int  listPcRegistrys(  );
	BOOL  bRefreshButtons(  );


// Dialog Data
	//{{AFX_DATA(CDlgCfgPcRegistrys)
	enum { IDD = IDD_cfgPcRegistrys };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgPcRegistrys)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgPcRegistrys)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDel();
	afx_msg void OnItemchangedLISTpcRegistry(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkLISTpcRegistry(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGPCREGISTRYS_H__AA3BB778_90E8_44AD_AF25_59D2B1989174__INCLUDED_)
