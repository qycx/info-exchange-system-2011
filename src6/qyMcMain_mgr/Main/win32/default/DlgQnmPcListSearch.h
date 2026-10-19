#if !defined(AFX_DLGQNMPCLISTSEARCH_H__9116D842_7D90_4F17_8EEE_06DA30DF6370__INCLUDED_)
#define AFX_DLGQNMPCLISTSEARCH_H__9116D842_7D90_4F17_8EEE_06DA30DF6370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmPcListSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcListSearch dialog

class CDlgQnmPcListSearch : public CDialog
{
// Construction
public:
	CDlgQnmPcListSearch(CWnd* pParent = NULL);   // standard constructor

	CQyRestrictEdit		m_edits[CONST_qnmMaxSearchFields];

// Dialog Data
	//{{AFX_DATA(CDlgQnmPcListSearch)
	enum { IDD = IDD_qnmPcListSearch };
	CIPAddressCtrl	m_ip;
	//}}AFX_DATA

	struct		{
				MY_DB_BUF	*	pDbBufs;

				TCHAR			col0[256];
				TCHAR			wherePart[CONST_qyMaxSqlClauseLen  +  1];	
				TCHAR			sortPart[CONST_qyMaxSqlClauseLen  +  1];

	}			m_var;

	BOOL  bSetDlgInfo(  MY_DB_BUF  *  pDbBufs  )  {  m_var.pDbBufs  =  pDbBufs;  return  TRUE; };
   int getWherePart(  int  iDbType  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmPcListSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmPcListSearch)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo0();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMPCLISTSEARCH_H__9116D842_7D90_4F17_8EEE_06DA30DF6370__INCLUDED_)
