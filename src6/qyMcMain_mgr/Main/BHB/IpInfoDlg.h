#if !defined(AFX_IPINFODLG_H__FBDB1729_85CF_441E_B45A_FE5A68362215__INCLUDED_)
#define AFX_IPINFODLG_H__FBDB1729_85CF_441E_B45A_FE5A68362215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IpInfoDlg.h : header file
//
extern COMPUTER_IP_INFO m_stuComputerInfo;
extern COMPUTER_IP_INFO m_stuNewComputerInfo;

/////////////////////////////////////////////////////////////////////////////
// CIpInfoDlg dialog

class CIpInfoDlg : public CDialog
{
// Construction
public:
	CIpInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIpInfoDlg)
	enum { IDD = IDD_DLG_INFOR };
	CListCtrl	m_cListIpInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIpInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InsertSingleInfo(int nIndex,COMPUTER_IP_INFO objComputerInfo);
	void FillIpListDlg();
	int GetRegCfg( char *cfgVal, int size );
	int DetectLegalIp(DWORD dwIpAddress);

	// Generated message map functions
	//{{AFX_MSG(CIpInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonDel();
	afx_msg void OnDblclkListIpinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPINFODLG_H__FBDB1729_85CF_441E_B45A_FE5A68362215__INCLUDED_)
