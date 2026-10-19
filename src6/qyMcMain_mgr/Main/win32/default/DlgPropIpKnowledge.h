#if !defined(AFX_DLGPROPIPKNOWLEDGE_H__F01A321D_8BEA_4180_9F8F_9C55B9855C4F__INCLUDED_)
#define AFX_DLGPROPIPKNOWLEDGE_H__F01A321D_8BEA_4180_9F8F_9C55B9855C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropIpKnowledge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropIpKnowledge dialog

class CDlgPropIpKnowledge : public CDialog
{
// Construction
public:
	CDlgPropIpKnowledge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropIpKnowledge)
	enum { IDD = IDD_prop_ipKnowledge };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct							{
		int							iDlgType;
		QY_OBJ_DB				*	pObjDb;
		int							id;
		//
		IP_KNOWLEDGE_RCD			knowledge;
	}								m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropIpKnowledge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropIpKnowledge)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPIPKNOWLEDGE_H__F01A321D_8BEA_4180_9F8F_9C55B9855C4F__INCLUDED_)
