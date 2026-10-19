#if !defined(AFX_DLGPCASSETPROPERTIES_H__B899684E_CF19_463E_BE19_45D1C3DF0C0D__INCLUDED_)
#define AFX_DLGPCASSETPROPERTIES_H__B899684E_CF19_463E_BE19_45D1C3DF0C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPcAssetProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPcAssetProperties dialog

class CDlgPcAssetProperties : public CDialog
{
// Construction
public:
	CDlgPcAssetProperties(CWnd* pParent = NULL);   // standard constructor

	struct							{
		QY_OBJ_DB				*	pObjDb;
		int							id;
		QY_PCASSET_RCD				pcAsset;
		QNM_PC_INFO					pcInfo;
		QNM_REG_INFO				regInfo;
	}								m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  id  );


// Dialog Data
	//{{AFX_DATA(CDlgPcAssetProperties)
	enum { IDD = IDD_pcAssetProperties };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPcAssetProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPcAssetProperties)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPCASSETPROPERTIES_H__B899684E_CF19_463E_BE19_45D1C3DF0C0D__INCLUDED_)
