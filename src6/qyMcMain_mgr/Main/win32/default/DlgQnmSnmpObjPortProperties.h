#if !defined(AFX_DLGQNMSNMPOBJPORTPROPERTIES_H__78BF4800_7F5B_4F5A_B9C4_9671837CB449__INCLUDED_)
#define AFX_DLGQNMSNMPOBJPORTPROPERTIES_H__78BF4800_7F5B_4F5A_B9C4_9671837CB449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmSnmpObjPortProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSnmpObjPortProperties dialog

class CDlgQnmSnmpObjPortProperties : public CDialog
{
// Construction
public:
	CDlgQnmSnmpObjPortProperties(CWnd* pParent = NULL);   // standard constructor

	struct		{
				QY_OBJ_DB					*	pObjDb;
				char							switchMac[CONST_qyMacLen  +  1];
				int								iPortIfIndex;
				QY_SWITCHPORT_RCD				portInfo;
				QY_SWITCHIFPORTSECURITY_RCD		portSecurityInfo;
	}			m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac,  int  iPortIfIndex  );

// Dialog Data
	//{{AFX_DATA(CDlgQnmSnmpObjPortProperties)
	enum { IDD = IDD_qnmSnmpObjPortProperties };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmSnmpObjPortProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmSnmpObjPortProperties)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMSNMPOBJPORTPROPERTIES_H__78BF4800_7F5B_4F5A_B9C4_9671837CB449__INCLUDED_)
