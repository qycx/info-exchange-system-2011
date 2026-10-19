#if !defined(AFX_DLGNUM_H__5BC89E8E_E618_4296_A1CC_8D907670593E__INCLUDED_)
#define AFX_DLGNUM_H__5BC89E8E_E618_4296_A1CC_8D907670593E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNum dialog

class CDlgNum : public CDialog
{
// Construction
public:
	CDlgNum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNum)
	enum { IDD = IDD_num };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		int				type;
		HWND			hParent;
		TCHAR			title[256  +  1];
		TCHAR			hint[128  +  1];
		TCHAR			okName[64  +  1];
		TCHAR			cancelName[64  +  1];
		unsigned  int	maxBytes;

		int				iMinVal,  iMaxVal;		//  最大最小
		unsigned  char	ucbMin,  ucbMax;		//  是否有上下限
		unsigned  char	ucbValSet;				//  是否已赋值

		int				n;						//  输出

	}					m_var;

	BOOL			bSetDlgInfo(  int  type,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  hint,  LPCTSTR  okName,  LPCTSTR  cancelName,  unsigned  int  maxBytes  );
	BOOL			bSetMax(  int  iMaxVal  );
	BOOL			bSetMin(  int  iMinVal  );
	BOOL			bSetVal(  int  n  );

	CQyRestrictEdit		m_edits[4];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNum)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNUM_H__5BC89E8E_E618_4296_A1CC_8D907670593E__INCLUDED_)
