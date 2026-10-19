#if !defined(AFX_DLGPCNETWORKOPTIONSSEL_H__4D0A2976_52BB_4FFD_ADD8_E0F363B44DDC__INCLUDED_)
#define AFX_DLGPCNETWORKOPTIONSSEL_H__4D0A2976_52BB_4FFD_ADD8_E0F363B44DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPcNetworkOptionsSel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPcNetworkOptionsSel dialog

class CDlgPcNetworkOptionsSel : public CDialog
{
// Construction
public:
	CDlgPcNetworkOptionsSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPcNetworkOptionsSel)
	enum { IDD = IDD_pcNetworkOptions_sel };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		unsigned  char	ucbPcAdapter;
		unsigned  char	ucbProxy;
		unsigned  char	ucbComputer;
		unsigned  char	ucbWindowsUpdatePolicy;
	}					m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPcNetworkOptionsSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPcNetworkOptionsSel)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPCNETWORKOPTIONSSEL_H__4D0A2976_52BB_4FFD_ADD8_E0F363B44DDC__INCLUDED_)
