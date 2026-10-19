#if !defined(AFX_DLGQNMCFGIPGRP_H__2F8F4031_A175_42A2_AA96_BBCFB98F9083__INCLUDED_)
#define AFX_DLGQNMCFGIPGRP_H__2F8F4031_A175_42A2_AA96_BBCFB98F9083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgIpGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgIpGrp dialog
 
class CDlgQnmCfgIpGrp : public CDialog
{
// Construction
public:
	CDlgQnmCfgIpGrp(CWnd* pParent = NULL);   // standard constructor

	struct  {
			int							type;
			CWnd					*	pSrcWnd;
			QY_ITEMCONTENT				procingItemContent;
			QY_ITEMCONTENT				procedItemContent;
			BOOL						bChanged;
	}									m_var;

	CQyRestrictEdit		m_edits[10];

	BOOL  bSetDlgInfo(  int  type,  CWnd  *  pSrcWnd  );


// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgIpGrp)
	enum { IDD = IDD_qnmCfgIpGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgIpGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgIpGrp)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGIPGRP_H__2F8F4031_A175_42A2_AA96_BBCFB98F9083__INCLUDED_)
