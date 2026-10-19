#if !defined(AFX_DLGPROPPCPROXYCFG_H__02D8B042_CAE9_4900_8D84_C6F3D2FF15A0__INCLUDED_)
#define AFX_DLGPROPPCPROXYCFG_H__02D8B042_CAE9_4900_8D84_C6F3D2FF15A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropPcProxyCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropPcProxyCfg dialog

class CDlgPropPcProxyCfg : public CDialog
{
// Construction
public:
	CDlgPropPcProxyCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropPcProxyCfg)
	enum { IDD = IDD_prop_pcProxyCfg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
		unsigned  char				ucbChanged;

		int							iDlgType;
		QY_OBJ_DB			*		pObjDb;
		char						mac0[CONST_qyMacLen  +  1];
		unsigned  int				uiType;
		int							id;

		QY_PCADAPTER_RCD			pcAdapterRcd;

		unsigned  char				ucbRuleExists;

	}					m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropPcProxyCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropPcProxyCfg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPPCPROXYCFG_H__02D8B042_CAE9_4900_8D84_C6F3D2FF15A0__INCLUDED_)
