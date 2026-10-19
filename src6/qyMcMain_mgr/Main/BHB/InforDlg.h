#if !defined(AFX_INFORDLG_H__E41810D6_8AD8_4A41_915E_24F629FE0689__INCLUDED_)
#define AFX_INFORDLG_H__E41810D6_8AD8_4A41_915E_24F629FE0689__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InforDlg.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CInforDlg dialog

class CInforDlg : public CDialog
{
// Construction
public:
	CInforDlg(int iType,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInforDlg)
	enum { IDD = IDD_DLG_INFORMATION };
	CIPAddressCtrl	m_cIntraStartIp;
	CIPAddressCtrl	m_cIntraEndIp;
	CString	m_csComInfo;
	CString	m_csDepart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInforDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iFlag;
	int DetectLegalIp(DWORD dwIpAddress);
	DWORD m_dwIntraEndIp;
	DWORD m_dwIntraStartIp;

	// Generated message map functions
	//{{AFX_MSG(CInforDlg)
	virtual void OnOK();
	afx_msg void OnButtonAddIp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFORDLG_H__E41810D6_8AD8_4A41_915E_24F629FE0689__INCLUDED_)
