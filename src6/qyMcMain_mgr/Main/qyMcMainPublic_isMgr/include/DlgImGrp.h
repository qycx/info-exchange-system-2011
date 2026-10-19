#if !defined(AFX_DLGIMGRP_H__85EB20E3_055A_4FAA_939B_EDF12902D46B__INCLUDED_)
#define AFX_DLGIMGRP_H__85EB20E3_055A_4FAA_939B_EDF12902D46B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImGrp dialog

class CDlgImGrp : public CDialog
{
// Construction
public:
	CDlgImGrp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImGrp)
	enum { IDD = IDD_imGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
		int				iDlgType;
		QY_OBJ_DB	*	pObjDb;
		TCHAR			misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID	idInfo;
		int				id;

		IM_GRP_INFO		rcd;
	}					m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImGrp)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMGRP_H__85EB20E3_055A_4FAA_939B_EDF12902D46B__INCLUDED_)
