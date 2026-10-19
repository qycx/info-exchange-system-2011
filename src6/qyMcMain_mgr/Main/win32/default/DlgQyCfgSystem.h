#if !defined(AFX_DLGQYCFGSYSTEM_H__512DE6C5_E4DD_4E6D_B7F0_CBC7EAA129CA__INCLUDED_)
#define AFX_DLGQYCFGSYSTEM_H__512DE6C5_E4DD_4E6D_B7F0_CBC7EAA129CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQyCfgSystem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCfgSystem dialog

class CDlgQyCfgSystem : public CDialog
{
// Construction
public:
	CDlgQyCfgSystem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQyCfgSystem)
	enum { IDD = IDD_qyCfgSystem };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct							{
				int					iDlgType;
				int					id;
				QY_OBJ_DB			obj;
				unsigned  char		ucbChanged;
	}								m_var;

	BOOL		bSetDlgInfo(  int  iDlgType,  int  id  )  {
							m_var.iDlgType  =  iDlgType;
							m_var.id  =  id;
							return  TRUE;
	}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQyCfgSystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQyCfgSystem)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCOMBOucbDsnless();
	afx_msg void OnBUTTONbrowseDir();
	afx_msg void OnSelchangeCOMBOdbTypeName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQYCFGSYSTEM_H__512DE6C5_E4DD_4E6D_B7F0_CBC7EAA129CA__INCLUDED_)
