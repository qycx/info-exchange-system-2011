
#ifndef  __QYMCMAINWNDPROC_H__
#define  __QYMCMAINWNDPROC_H__	//  {



typedef  struct  __qyMcMainWndVar_t							{								//  2010/04/13
				 void						*				pProcInfo;

				 UINT										uiTimerId;
		
				 //
				 MIS_MSGU					*				pMsgBuf_msgArrive;				//  2009/12/10

				 #ifndef  __noMfc__
						  CStatusBar		*				pm_wndStatusBar;
				 #endif

				 WND_guiData_main							guiData;

				 //
				 unsigned  char								ucbVisible;						//  2012/07/17

}		QY_MC_mainWndVar;


int mainWnd_OnQyPostComm(  HWND  hMainWnd,  void  *  pVar,  UINT  wParam,  LONG  lParam  );
LRESULT mainWnd_OnQyGraphNotify_mediaDevice(  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  );
int  mainWnd_OnQyShowMainWnd(  HWND  hMainWnd  );

int  dlgAbout_OnInitDialog_qyMc(  HWND  hDlg,  int  iIDD  );

BOOL  bViewActiveImObjList(  );


#endif


