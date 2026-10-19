#pragma once


#ifndef  __WINCE__
#include	"qyStatic.h"
#endif

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"

#if  0

// CDlgTalk_ce dialog

class CDlgTalk_ce : public CDialog
{
	DECLARE_DYNAMIC(CDlgTalk_ce)

public:
	CDlgTalk_ce(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTalk_ce();

// Dialog Data
	enum { IDD = IDD_talk_ce };

	//  CQyStatic								m_static_peerDesc;

	DLG_TALK_var							m_var;
#ifndef  __TEST__
	CCeMenuBar								m_menuBar;
#endif

	//  BOOL		bSetDlgInfo(  int  iDlgType,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  HWND  hFore  );
	BOOL		bSetDlgInfo(  int  iDlgType,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  BOOL  bNeedNotShowWnd,  HWND  hFore  );
	
	int			cancelTasks(  int  iTaskId  );
	BOOL		bQuitDlg(  BOOL  bCancelTasks  );
	
	BOOL Create(const RECT& rect);



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void PostNcDestroy();
	virtual void OnCancel();
public:
	afx_msg void OnDestroy();
	afx_msg LONG OnQyComm(  UINT, LONG  );
	afx_msg LONG OnQyPostComm(  UINT, LONG  );
	afx_msg void OnBnClickedButtonup0();
	afx_msg void OnBnClickedButtondown0();
	afx_msg void OnBnClickedButtonsend();
	afx_msg void Onqyleftkey();
	afx_msg void Onqyrightkey();
	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedButtonstatus();
};


#endif

#include	"qywnd.h"

class CDlgTalk_ce : public CQyWnd
{

public:
	CDlgTalk_ce(  HWND  hpParent = NULL);   // standard constructor
	virtual ~CDlgTalk_ce();

// Dialog Data
	//  enum { IDD = IDD_talk_ce };

	//  CQyStatic								m_static_peerDesc;

	DLG_TALK_var							m_var;
#ifndef  __TEST__
	CCeMenuBar								m_menuBar;
#endif

#if  0
	BOOL		bSetDlgInfo(  int  iDlgType,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  BOOL  bNeedNotShowWnd,  HWND  hFore  );
	BOOL		Create(const RECT& rect);
#endif
	
	//  int			cancelTasks(  int  iTaskId  );
	//  BOOL		bQuitDlg(  BOOL  bCancelTasks  );
	

	//
	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;  }

public:

	virtual void OnOK();

	void OnIsCmd(  UINT nID  );
	//  void OnUpdateIsCmd(CCmdUI *pCmdUI);
	void OnBnClickedButtonstatus();
	void OnBnClickedButtonOp0();
	void OnBnClickedButtonOp1();



};
