// qyMc.h : main header file for the QYMC application
//

#if !defined(AFX_QYMC_H__62A29CCA_C5D9_47D6_824A_A29264C479D2__INCLUDED_)
#define AFX_QYMC_H__62A29CCA_C5D9_47D6_824A_A29264C479D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include	"qyCommon.h"
#include	"qyCommProc.h"
//
#include	"myresource.h"       // main symbols
#include	"QyRestrictEdit.h"

#include	"qyRcdset.h"
#include	"qyMcDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CQyMcApp:
// See qyMc.cpp for the implementation of this class
//


class CQyMcApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CQyMcApp();

	struct						{
		
		//  void				*	m_pgQyMc;
		
		CMultiDocTemplate	*	m_pMcRootListTemplate;
		CMultiDocTemplate	*	m_pMc2ViewTemplate;
		CMultiDocTemplate	*	m_pMcTreeTemplate;
		CMultiDocTemplate	*	m_pMcTemplate;
		CMultiDocTemplate	*	m_pMcWebTemplate;
		CMultiDocTemplate	*	m_pMcDbTemplate;
		
	}							var;


	BOOL		bOpenRootDoc(  );
	int			enumAllDocs(  PF_commonHandler  pf,  COMMON_PARAM  *  p0,  BOOL  *  pbStop  );
	BOOL		bNewMcView(  void  *  pSel  );
	BOOL		bNewWebView(	void  *  pSel  );
	BOOL		bNewQueryView(	void  *  pSel  );
	BOOL		bNewTreeView(  void  *  pSel  );
	BOOL		bNewTreeListView(  void  *  pSel  );
	void		refreshAll(  );
	void		refreshDocTemplate(  void  *  pDocTemplate  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyMcApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CQyMcApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYMC_H__62A29CCA_C5D9_47D6_824A_A29264C479D2__INCLUDED_)
