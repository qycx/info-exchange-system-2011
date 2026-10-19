// qyMessenger_ts_noMfc.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyMessenger_ts_noMfc.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMc_tsDlg_noMfc.h"



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE	g_hInst  =  NULL;							// current instance
//
struct		{
	BOOL	bCoInited;
}			g_status_qmc;
//
TCHAR		szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR		szWindowClass[MAX_LOADSTRING];			// the main window class name

 //  2013/06/10. 每个模块自己定义
 HINSTANCE  get_my_hInst(  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	return  pQyMc->g_hInst;
}

 //  2013/06/15
 BOOL  bQnmDemo(  )
{
	return  FALSE;
}


// Forward declarations of functions included in this code module:
BOOL				InitInstance(HINSTANCE, int);
int					ExitInstance(  HINSTANCE  hInstance  );

//  LRESULT CALLBACK	DialogProc_ts_main(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable  =  NULL;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QYMESSENGER_TS_NOMFC, szWindowClass, MAX_LOADSTRING);

	//
	memset(  &msg,  0,  sizeof(  msg  )  );
	memset(  &g_status_qmc,  0,  sizeof(  g_status_qmc  )  );


	// Perform application initialization:
	if  (  !InitInstance (hInstance, nCmdShow)  )  {
		goto  errLabel;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QYMESSENGER_TS_NOMFC));

	// Main message loop:
	while (  msg.message  !=  WM_QUIT  )  {
		  if  (  PeekMessage(&msg, NULL, 0, 0,PM_REMOVE)  )  {
			  if  (  !TranslateAccelerator(msg.hwnd, hAccelTable, &msg)  )  {

				  if  (  dll_PreTranslateMessage_isCliHelp(  &msg  )  )  continue;
				  
				  //
				  TranslateMessage(&msg);
				  DispatchMessage(&msg);		
			  }
			  }			
		  else  {  //  
			     myRender(  );			
		  }
	}


errLabel:
	//
	ExitInstance(  hInstance  );

	//
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	BOOL	bRet	=	FALSE;
	
	g_hInst = hInstance; // Store instance handle in our global variable
	
	//
   	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//
	DWORD dwCoInit  =  COINIT_APARTMENTTHREADED;	// COINIT_MULTITHREADED. 2013/06/17		
	if  (  !SUCCEEDED(  CoInitializeEx(  NULL,  dwCoInit  )  )  )  {
		return  FALSE;
	}
	g_status_qmc.bCoInited  =  TRUE;
	
	//
	set_cur_iResId_sys(  CONST_resId_sys_isCli_ts  );

	//
	if  (  initQyMc(  g_hInst  )  )   goto  errLabel;



#if  0
		HWND hWnd;

   //
   hWnd = CreateDialog(hInstance,  MAKEINTRESOURCE(IDD_ts_main), NULL,  (DLGPROC)DialogProc_ts_main);
   if (!hWnd)  {
	   goto  errLabel;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
#endif

   	CqyMc_tsDlg  *  pDlg  =  NULL;
	RECT							rect;

	pDlg  =  new  CqyMc_tsDlg;
	if  (  !pDlg->Create(  rect  )  )  return  FALSE;

#if  0
	//
	int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;	
	SetWindowPos(  pDlg->m_hWnd,  NULL,  0,  0,  0,  0,  flg  );
#endif

   bRet  =  TRUE;
errLabel:

   return  bRet;
}

 int ExitInstance(  HINSTANCE  hInstance  )
{
	int		iErr	=	-1;


	//
	exitQyMc( );
	
	//
	if  (  g_status_qmc.bCoInited  )  {
		CoUninitialize(  );  g_status_qmc.bCoInited  =  FALSE;
	}

	//
	iErr  =  0;
errLabel:
	return  iErr;
}

#if  0
LRESULT CALLBACK DialogProc_ts_main(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetWindowPos(hWnd,NULL, 200,200,0,0,SWP_NOSIZE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if  (  LOWORD(  wParam  )  ==  IDC_BUTTON_contact  )  {
			#ifdef  __DEBUG__
					showDlgProgress(  hWnd,  _T(  "Waiting..."  ),  _T(  ""  ),  30,  0,  50  );
			#endif
			return  TRUE;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//  PostQuitMessage(0);
			DestroyWindow(  hWnd  );
			OutputDebugString(  _T(  "kkd\n"  )  );
			
			//
			PostQuitMessage(0);

			return (INT_PTR)TRUE;
		}
		break;
	case  WM_NCDESTROY:
		  OutputDebugString(  _T(  "kk\n"  )  );
		  if  (  IsWindow(  hWnd  )  )  OutputDebugString(  _T(  "wnd\n"  )  );
		  else  OutputDebugString(  _T(  "false\n"  )  );

		  break;
	case WM_DESTROY:
		//  PostQuitMessage(0);
		OutputDebugString(  _T(  "WM_DESTROY\n"  )  );
		break;
	//default:
		//return DefWindowProc(hWnd, uMsg, wParam, lParam);	
	}
	return (INT_PTR)FALSE;
}
#endif



