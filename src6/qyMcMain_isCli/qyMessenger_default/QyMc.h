// QyMc_isCli.h : main header file for the QyMc_isCli application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CQyMcApp:
// See QyMc_isCli.cpp for the implementation of this class
//

class CQyMcApp : public CWinApp
{
public:
	CQyMcApp();

	//
	BOOL		bNewMcView(  void  *  pSel  );
	BOOL		bNewQueryView(	void  *  pSel  );


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
};

extern CQyMcApp theApp;