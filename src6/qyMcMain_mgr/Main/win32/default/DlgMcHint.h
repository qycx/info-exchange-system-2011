#if !defined(AFX_DLGMCHINT_H__4A1AF736_1812_40BF_A82B_B7E0526FE1F8__INCLUDED_)
#define AFX_DLGMCHINT_H__4A1AF736_1812_40BF_A82B_B7E0526FE1F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMcHint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMcHint dialog

class CDlgMcHint : public CDialog
{
// Construction
public:
	CDlgMcHint(CWnd* pParent = NULL);   // standard constructor

	struct  {
		int		x,	y;
		char	hintBuf[256];
	}								var;

	int	setDlgInfo(  int x, int y, char * hint  );

// Dialog Data
	//{{AFX_DATA(CDlgMcHint)
	enum { IDD = IDD_MC_HINT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMcHint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMcHint)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCHINT_H__4A1AF736_1812_40BF_A82B_B7E0526FE1F8__INCLUDED_)
