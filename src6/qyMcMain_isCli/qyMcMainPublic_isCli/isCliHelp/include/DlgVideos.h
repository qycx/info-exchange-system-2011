// DlgVideos.h: interface for the CDlgVideos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGVIDEOS_H__27CADE8D_85C6_48D4_9F73_71DF11F835D5__INCLUDED_)
#define AFX_DLGVIDEOS_H__27CADE8D_85C6_48D4_9F73_71DF11F835D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgDesktopsMon.h"

#include	"dlgVideosProc.h"

class CDlgVideos : public CDlgDesktopsMon  
{
public:
	CDlgVideos(  CWnd* pParent = NULL  );
	virtual ~CDlgVideos();

#if  0
	struct								{

		MIS_CNT						*	pMisCnt;

		BOOL							bClosed;							//  关闭标志位

		BOOL							bUseDirectX;						//  2009/08/06

		TCHAR							title[128  +  1];

		HWND							hDlgTalk;							//  
		int								iTaskId;
		//  
		QY_MESSENGER_ID					idInfo_sender;
		unsigned  int					uiTranNo_openAvDev;
				
		unsigned  char					ucbLocalAv;							//  
		BOOL							bVideoConference;					//  2010/08/30
		BOOL							bRemoteAssist;

		unsigned  int					nElapseInMs;						//  2009/10/14

		BOOL							bSwapMouse;							//  2008/11/16

		struct							{
			BOOL						bInited;							//  2011/03/25
		}								guiData;

		int								idc;
		HDC								hDc;
		CAP_IMAGES						images;
		

		//  2012/05/05
		unsigned  short					usCnt_zoneParams;
		ZONE_PARAM				*		pZoneParams;

		//
		DWORD							dwTickCnt_sendLastMouseMove;		//  200811/22
		unsigned  int					uiEventId_lastRecvd;				//  

		//  
		struct							{		 
			int							x;
			int							y;
			UINT						nFlags;
			BOOL						bMouseMove;
		}								lastMouseEvent;
		BOOL							bNeedSend_lastMouseEvent;			//  是否需要发送

		BOOL							bInstantAssistant;					//  2010/12/24

		BOOL							bMediaControl;						//  2009/04/29
		int								iIndex_capBmp;
		int								iIndex_capAudio;
		HWND							hWnd_mediaControl;	
		DWORD							dwTickCnt_lastViewMediaControl;		//  200811/22

		MIS_MSGU				*		pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08

	}									m_var;
#endif
	DLG_videos_var						m_var;

	//  BOOL			bSetDlgInfo(  int  iWndContentType,  LPCTSTR  title,  int  iResId_menu,  HWND  hDlgTalk,  int  iTaskId,  int  iIndex_capImage,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic,  unsigned  char  ucbLocalAv  );
	BOOL			bSetDlgInfo(  int  iWndContentType,  LPCTSTR  title,  int  iResId_menu,  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiTranNo_openAvDev,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic,  unsigned  char  ucbLocalAv,  unsigned  int  nElapseInMs  );

	BOOL			bEnableRemoteAssist(  BOOL  bRemoteAssist  );

	virtual  int	sizeAllControls(  RECT  rcParam  );

	int				processPointerEvent(  int  x,  int  y,  UINT  nFlags,  BOOL  bMouseMove  =  FALSE,  BOOL  bSendForce  =  FALSE  );
	int				sendKeyEvent(  unsigned  int  key, unsigned  char  ucbDown  );
	virtual  int	processKeyEvent(  UINT  nChar, DWORD  keyData  );
	int				resetKeyEvent(  );

	//  virtual  int	getCapImageInfo(  QY_WMBUF_COMM  *  pComm  );
	//  virtual  int	chkTask(  QY_WMBUF_COMM  *  pComm  );

	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm( WPARAM, LPARAM );

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};




#endif // !defined(AFX_DLGVIDEOS_H__27CADE8D_85C6_48D4_9F73_71DF11F835D5__INCLUDED_)
