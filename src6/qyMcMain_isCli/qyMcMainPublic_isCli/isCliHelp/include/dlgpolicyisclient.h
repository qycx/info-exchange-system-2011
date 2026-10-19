#if !defined(AFX_DLGPOLICYISCLIENT_H__DA593431_2F24_4872_A8FE_A49738F56E36__INCLUDED_)
#define AFX_DLGPOLICYISCLIENT_H__DA593431_2F24_4872_A8FE_A49738F56E36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPolicyIsClient.h : header file
//

#ifndef  __WINCE__

/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyIsClient dialog
class CDlgPolicyIsClient : public CDialog
{
// Construction
public:
	CDlgPolicyIsClient(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPolicyIsClient)
	enum { IDD = IDD_policy_isClient };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		MC_VAR_isCli				*	pProcInfo;
		POLICY_isClient				policy;
		//
	}								m_var;

	BOOL  bShowPolicy(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPolicyIsClient)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPolicyIsClient)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonbrowsedir();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonrestoredefaultsettings();
#if  0
	afx_msg void OnBnClickedButtonsetLdsettings();
	afx_msg void OnBnClickedButtonsetSdsettings();
	afx_msg void OnBnClickedButtonsetSd1settings();
	afx_msg void OnBnClickedButtonsetHdsettings();
	afx_msg void OnBnClickedButtonsetHd1settings();
	afx_msg void OnBnClickedButtonsethd2settings();
	afx_msg void OnBnClickedButtonsetFullhdsettings();
	afx_msg void OnBnClickedButtonsetFullhd1settings();
	afx_msg void OnBnClickedButtonsetfullhd2settings();
#endif
	afx_msg void OnBnClickedButtonavcompressorreq();
	afx_msg void OnBnClickedButtonavcompressorreply();
	afx_msg void OnBnClickedButtonscreencompressor();
	afx_msg void OnBnClickedButtonmediafilecompressor();
	afx_msg void OnBnClickedButtonmediadevicecompressor();
	afx_msg void OnBnClickedButtonwebcamcompressor();

	#ifdef  __isCli__
			afx_msg void OnBnClickedButtonptzsettings();
	#endif
			afx_msg void OnBnClickedButtonvideoconferencecfg();
			//  afx_msg void OnBnClickedButtonvideotagcfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif



#endif // !defined(AFX_DLGPOLICYISCLIENT_H__DA593431_2F24_4872_A8FE_A49738F56E36__INCLUDED_)
