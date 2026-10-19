#if !defined(AFX_DLGDESKTOPSMON_H__8BE1FDE2_2F7E_4742_88D7_83A7F31DA55D__INCLUDED_)
#define AFX_DLGDESKTOPSMON_H__8BE1FDE2_2F7E_4742_88D7_83A7F31DA55D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDesktopsMon.h : header file
//


#define		DEFAULT_uiInitW_pic_dlgDesktopsMon		800
#define		DEFAULT_uiInitH_pic_dlgDesktopsMon		600

#define		DEFAULT_uiInitW_dlgDesktopsMon			1024						//  2012/04/03
#define		DEFAULT_uiInitH_dlgDesktopsMon			768


typedef  struct  __paramLayout_dlgDesktopsMon_t		{
				 int								iEdge_l;					//	=	10;
				 int								iEdge_t;					//	=	10;
				 int								iEdge_r;					//	=	10;
				 int								iEdge_b;					//	=	10;
				 //
				 int								iX_spacing;					//	=	10;			//  两个控件间的横向间隔
				 int								iY_spacing;					//	=	10;
				 //
				 int								iW_btn;						//	=	10;
				 int								iH_btn;						//	=	10;
				 //
				 int								iH_static;					//	=	30;			//  和pic相关的标签的高度，固定
				 //
				 int								iY_spacing_pic_static;		//	=	2;			//  两个控件间的纵向间隔
				 int								iY_spacing_static_pic;		//	=	4;			
				 //
				 int								iY_spacing_static_btn;		//	=	10;

}		 PARAM_layout_dlgDesktopsMon;

/////////////////////////////////////////////////////////////////////////////
// CDlgDesktopsMon dialog

class CDlgDesktopsMon : public CDialog
{
// Construction
public:
	CDlgDesktopsMon(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDesktopsMon)
	enum { IDD = IDD_desktopsMon };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct									{
			CWnd					*		m_pParent;
			int								m_nID;
			//
			int								iWndContentType;			//  2009/09/07
			int								iSubType;					//  2012/04/02
			//
			int								iResId_menu;
			//

			PARAM_layout_dlgDesktopsMon		layoutParam;

			//
			unsigned  short					usCnt_row;					//  水平有几个
			unsigned  short					usCnt_col;					//  纵向有几个窗口
			//
			unsigned  int					uiInitW_pic;
			unsigned  int					uiInitH_pic;

			//
			BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
			BOOL							bDlgInited;					//  

			QY_DMITEM				*		pIdcTable;
			
			//
			RECT							m_rect;
			
			// 2008/11/06. 为提供滚动条
			BOOL							bScrollBarEnabled;
			BOOL							notOnOffScrollBar;			//  2009/10/08

			int								m_nCurWidth;
			int								m_nScrollPos_h;
			int								m_nCurHeight;
			int								m_nScrollPos_v;

			//  2010/08/26
			unsigned  char 					ucbHideStatic_idc;
			unsigned  char 					ucbHideStatic_idcHint;


			//  
			CAP_RECT						mems_org[CONST_maxMonedDesktops];
			CAP_RECT						mems[CONST_maxMonedDesktops];				//  2012/05/04

			//  2009/10/06
			WINDOWPLACEMENT					m_oldWndPlacement;
			struct							{
				HMENU						hOldMenu;								//  2012/07/07
				long						lOldStyle;								//  2012/07/07
			}								m_fullScreenInfo;
			// 
			BOOL							m_bFullScreen;
			RECT							m_fullScreenRect;
			PARAM_layout_dlgDesktopsMon		m_oldLayoutParam;

			//  2010/12/25
			unsigned  char					ucbBkBlack;

			//
			PF_commonHandler				pf_OnMove;	//  HWND  hWnd,  int  x,  int  y
			PF_commonHandler				pf_OnSize;	//  HWND  hWnd,  int  cx,  int  cy

	}		m_var;

	//  
	BOOL			bSetDlgInfo(  int  iWndContentType,  int  iSubType,  int  iResId_menu,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pic,  unsigned  int  uiInitH_pic  );
	int				getWndContentType(  );  
	int				getWndContentSubType(  );
		
	virtual  BOOL  	bQuitDlg(  );
	
	BOOL			Create(const RECT& rect);

	BOOL			bEnableScrollBar(  BOOL  bEnable  );
	int				SetPicRect(  int  w,  int  h,  BOOL  bMoveWindow  );
	int				getPicRect(  int  idc,  RECT  *  pRc  );  

	//
	virtual  int	sizeAllControls(  RECT  rc  );
	void			doLayout(  );

	void			endFullScreen(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDesktopsMon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	virtual void PostNcDestroy();


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDesktopsMon)
		// NOTE: the ClassWizard will add member functions here
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void Onstopscrollbar();
	afx_msg void OnUpdatestopscrollbar(CCmdUI *pCmdUI);
	afx_msg void Onstartscrollbar();
	afx_msg void OnUpdatestartscrollbar(CCmdUI *pCmdUI);
	//}}AFX_MSG
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );
	DECLARE_MESSAGE_MAP()
	afx_msg void Onfullscreen();
	afx_msg void OnUpdatefullscreen(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDESKTOPSMON_H__8BE1FDE2_2F7E_4742_88D7_83A7F31DA55D__INCLUDED_)
