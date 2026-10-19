#if !defined(AFX_DLGQNMCFGPCGRPS_H__5206BE71_A214_4A99_86BC_4E9293911FC3__INCLUDED_)
#define AFX_DLGQNMCFGPCGRPS_H__5206BE71_A214_4A99_86BC_4E9293911FC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcGrps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcGrps dialog

class CDlgQnmCfgPcGrps : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcGrps(CWnd* pParent = NULL);   // standard constructor

	struct		{
			
			int								nItemSelected;
			BOOL							bChanged;
			
			int								idcList;
			QY_COLUMNINFO			*		pColumns;
			int								nFields;
			char							sqlBuf[CONST_qyMaxSqlBufLen  +  1];
			
			BOOL							bNotAllAllowed;

	}										m_var;

	void									refreshAll(  );
	BOOL									bRefreshButtons(  );
	int										getItemContent(  int nItem,  QY_ITEMCONTENT * pItemContent );



// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcGrps)
	enum { IDD = IDD_qnmCfgPcGrps };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcGrps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcGrps)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnItemchangedpcGrpList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCHECKbNotAllAllowed();
	afx_msg void OnModify();
	afx_msg void OnDblclkpcGrpList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCGRPS_H__5206BE71_A214_4A99_86BC_4E9293911FC3__INCLUDED_)
