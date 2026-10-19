

#ifndef  __CEMENUBAR_H__
#define  __CEMENUBAR_H__	//  {

#ifndef  WIN32_PLATFORM_QMSP
		#include	<tpcshell.h> 
#endif

class  CCeMenuBar		{

private:
	struct				{
		HWND			hWndMenuBar;
	}					m_var;

public:
	CCeMenuBar(  );
	~CCeMenuBar(  );

	HWND	getMenuBar(  );
	BOOL	bCreate(  HWND  hParent,  UINT  uBarRes,  HINSTANCE  hInst,  DWORD  dwFlags  =  0  );

};



#ifndef  SHCMBM_OVERRIDEKEY
		 #define SHCMBM_OVERRIDEKEY  (WM_USER + 403)

		#define SHMBOF_NODEFAULT    0x00000001 // do not do default handling of this key
		#define SHMBOF_NOTIFY       0x00000002 // send us the WM_* messages for this key

		#define VK_TBACK    VK_ESCAPE           // Back       

		#define EM_SETINPUTMODE       0x00DE    // Sets default input mode when control gets focus. lParam should be be EIM_*|EIMMF_*.

		#define EIM_SPELL                   IM_SPELL                // Spell input mode                        

		#define IM_SPELL           0

		//
		#define		IDC_LSK		IDOK
		#define		IDC_RSK		IDCANCEL

		//
		void SHSendBackToFocusWindow(  UINT uMsg,  WPARAM wp,  LPARAM lp  );

#endif

#ifdef  __DEBUG__

#endif


 DWORD  OverrideKey(  HWND  hWnd_menuBar,  WPARAM  wParam  =  VK_TBACK  );
 BOOL  GetButtonText(  HWND  hWnd_menuBar,  PTSTR  ptzStr,  unsigned  int  cnt,  BOOL  bRight  =  TRUE  );
 BOOL  SetButtonText(  HWND  hWnd_menuBar,  LPCTSTR  ptzStr,  BOOL  bRight  =  TRUE  );
 BYTE  GetButtonState(  HWND  hWnd_menuBar,  BOOL  bRight  =  TRUE  );
 BOOL  SetButtonState(  HWND  hWnd_menuBar,  BYTE  bState  =  TBSTATE_ENABLED,  BOOL  bRight  =  TRUE  );
 BOOL  EnableButton(  HWND  hWnd_menuBar,  BOOL  bEnable  =  TRUE,  BOOL  bRight  =  TRUE  );
 BOOL  HideButton(  HWND  hWnd_menuBar,  BOOL  bHide  =  TRUE,  BOOL  bRight  =  TRUE  );
 int  ce_popupMenu(  void  *  pCusResParam,  HWND  hWnd_menuBar,  int  iResId, int  nPos,  BOOL  bRight  );

 //
 
#endif  //  }


