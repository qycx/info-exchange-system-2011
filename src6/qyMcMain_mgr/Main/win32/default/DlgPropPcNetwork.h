#if !defined(AFX_DLGPROPPCNETWORK_H__0EED760C_B587_4062_88AB_6FD7797E1C02__INCLUDED_)
#define AFX_DLGPROPPCNETWORK_H__0EED760C_B587_4062_88AB_6FD7797E1C02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropPcNetwork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcNetwork dialog

class CDlgPropPcNetwork : public CDialog
{
// Construction
public:
	CDlgPropPcNetwork(CWnd* pParent = NULL);   // standard constructor

	struct				{
		QY_OBJ_DB	*	pObjDb;
		int				id;
	}					m_var;

	BOOL	bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );

// Dialog Data
	//{{AFX_DATA(CDlgPropPcNetwork)
	enum { IDD = IDD_prop_pcNetwork };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropPcNetwork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropPcNetwork)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPPCNETWORK_H__0EED760C_B587_4062_88AB_6FD7797E1C02__INCLUDED_)
