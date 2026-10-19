#if !defined(AFX_DLGCUSPCSP_H__8D76172F_D193_496E_81E7_EBC2932F9DAC__INCLUDED_)
#define AFX_DLGCUSPCSP_H__8D76172F_D193_496E_81E7_EBC2932F9DAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCusPcSp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCusPcSp dialog

class CDlgCusPcSp : public CDialog
{
// Construction
public:
	CDlgCusPcSp(CWnd* pParent = NULL);   // standard constructor

	struct					{
		QY_OBJ_DB		*	pObjDb;
		QY_CUSNAME_RCD		cusPcSp;
		unsigned  char		ucbChanged;
	}						m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  spName  );


// Dialog Data
	//{{AFX_DATA(CDlgCusPcSp)
	enum { IDD = IDD_cusPcSp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCusPcSp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCusPcSp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCUSPCSP_H__8D76172F_D193_496E_81E7_EBC2932F9DAC__INCLUDED_)
