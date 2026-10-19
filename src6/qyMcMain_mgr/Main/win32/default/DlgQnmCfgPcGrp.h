#if !defined(AFX_DLGQNMCFGPCGRP_H__16DB5CCF_C19A_47D2_AC87_F347D2017D31__INCLUDED_)
#define AFX_DLGQNMCFGPCGRP_H__16DB5CCF_C19A_47D2_AC87_F347D2017D31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgPcGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcGrp dialog

class CDlgQnmCfgPcGrp : public CDialog
{
// Construction
public:
	CDlgQnmCfgPcGrp(CWnd* pParent = NULL);   // standard constructor

	struct  {
			int							type;
			CWnd					*	pSrcWnd;
			char						startIp[15  +  1];
			//  QY_ITEMCONTENT				procingItemContent;
			//  QY_ITEMCONTENT				procedItemContent;
			QNM_PCGRP_RCD				procingPcGrp;
			QNM_PCGRP_RCD				procedPcGrp;

			BOOL						bChanged;
	}									m_var;

	BOOL  bSetDlgInfo(  int  type,  CWnd * pSrcWnd,  char  *  startIp  );

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgPcGrp)
	enum { IDD = IDD_qnmCfgPcGrp };
	CIPAddressCtrl	m_startIp;
	CIPAddressCtrl	m_endIp;
	CString	m_officeName;
	CString	m_subOfficeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmCfgPcGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmCfgPcGrp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMCFGPCGRP_H__16DB5CCF_C19A_47D2_AC87_F347D2017D31__INCLUDED_)
