#if !defined(AFX_DLGQNMCFGIPSCAN_H__0BDF3FAB_4F64_4FCA_A49F_CA6354DB4347__INCLUDED_)
#define AFX_DLGQNMCFGIPSCAN_H__0BDF3FAB_4F64_4FCA_A49F_CA6354DB4347__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgIpScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgIpScan dialog

class CDlgQnmCfgIpScan : public CDialog
{
// Construction
public:
	CDlgQnmCfgIpScan(CWnd* pParent = NULL);   // standard constructor

	struct		{
		int									nItemSelected;
		BOOL								bChanged;
		int									idcList;
		QY_COLUMNINFO				*		pColumns;
		int									nFields;
		char								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	}										m_var;

	void									refreshAll(  );
	BOOL									bRefreshButtons(  );
	int										getItemContent(  int nItem,  QY_ITEMCONTENT * pItemContent );


// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgIpScan)
	enum { IDD = IDD_qnmCfgIpScan };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgIpScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgIpScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnItemchangedipGrpList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGIPSCAN_H__0BDF3FAB_4F64_4FCA_A49F_CA6354DB4347__INCLUDED_)
