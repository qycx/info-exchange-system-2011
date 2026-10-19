// qyTray.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>

#include "qtCommon.h"



MENUINFO miNet,miDisk,miTools,miKeys;

 INT qyMessageBox( HINSTANCE hInst, HWND hwnd, INT iCaption, INT iText, UINT	uStyle )
{
	CHAR	szCaption[64];
	CHAR	szText[256];

	LoadString( hInst, iCaption, szCaption, sizeof( szCaption ) );
	LoadString( hInst, iText, szText, sizeof( szText ) );

	return ( MessageBox( hwnd, szText, szCaption, uStyle ) );
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	QY_TRAY qyTray;
	// HWND hwnd;
	MSG msg;
	OSVERSIONINFO osid;
	BOOL bIsNT;

	osid.dwOSVersionInfoSize = sizeof (osid);
	GetVersionEx (&osid);   
	bIsNT=(osid.dwPlatformId == VER_PLATFORM_WIN32_NT);

	memset( &qyTray, 0, sizeof( qyTray ) );
	qyTray.ghInst = hInstance;

	LoadString( qyTray.ghInst, IDS_APP_TITLE, qyTray.szApp, sizeof( qyTray.szApp ) );

	if ( FindWindow( QY_TRAY_WINDOW_NAME, QY_TRAY_WINDOW_NAME ) ) {
		return 0;
	}

	qyTray.hwndTray=TrayWindow( &qyTray );

	qyTray.hIconKey = LoadIcon( qyTray.ghInst, MAKEINTRESOURCE(IDI_TRAYICON));
	TaskbarAddIcon( qyTray.hwndTray, TASKBAR_TRAY_ID, qyTray.hIconKey, "QYCX", 
			WM_TASKAREA_MESSAGE);

	PTHotKeyInit ();

	qySetHook( ); // Our CBT hook for current focus

	bIsNT=FALSE;

	/*
	if(!bIsNT)
	{
		g_hwnd=hwndTray;
		InitializeWipeOnDelete(hwndTray);
	}
	*/

	while( GetMessage( &msg, NULL, 0, 0 ) )            
	{
		if( IsDialogMessage( qyTray.hwndTray, &msg ) )     
					//  Process Tab messages and such
			continue;

		TranslateMessage( &msg );                      
		DispatchMessage( &msg );
	}

	/*
	if(!bIsNT)
	{
		UninitializeWipeOnDelete();
	}
	*/

	qyDeleteHook(); // Our CBT hook for current focus

	TaskbarDeleteIcon( qyTray.hwndTray, TASKBAR_TRAY_ID);

	return 0;
 	
}

 HWND TrayWindow( QY_TRAY *pQT )
{
	HWND hwnd;
	WNDCLASS wc;

	// Register the Server Window Class

	wc.style			= 0;
	wc.lpfnWndProc		= qyTrayProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= pQT->ghInst;
	wc.hIcon			= 0;
	wc.hCursor			= 0;
	wc.hbrBackground	= 0;
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= QY_TRAY_WINDOW_NAME;

	RegisterClass( &wc );

	hwnd = CreateWindow(
		QY_TRAY_WINDOW_NAME, QY_TRAY_WINDOW_NAME, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL, pQT->ghInst, NULL );

	ShowWindow( hwnd, SW_HIDE );
	UpdateWindow( hwnd );

	return hwnd;
}

 void PGPtrayCreateImageList( HINSTANCE hInst, HIMAGELIST *phIml )
{
	int iNumBits;
	HDC hDC;
	HBITMAP hBmp;

	// ImageList Init

	hDC = GetDC (NULL);		// DC for desktop
	iNumBits = GetDeviceCaps (hDC, BITSPIXEL) * GetDeviceCaps (hDC, PLANES);
	ReleaseDC (NULL, hDC);

	if (iNumBits <= 8) {
		*phIml =	ImageList_Create (16, 16, ILC_COLOR|ILC_MASK, 
							NUM_BITMAPS, 0); 
		hBmp = LoadBitmap( hInst, MAKEINTRESOURCE( IDB_EXEBITMAP4BIT ) );
		ImageList_AddMasked (*phIml, hBmp, RGB(255, 0, 255));
		DeleteObject (hBmp);
	}
	else {
		*phIml =	ImageList_Create (16, 16, ILC_COLOR24|ILC_MASK, 
							NUM_BITMAPS, 0); 
		hBmp = LoadBitmap( hInst, MAKEINTRESOURCE( IDB_EXEBITMAP24BIT ) );
		ImageList_AddMasked (*phIml, hBmp, RGB(255, 0, 255));
		DeleteObject (hBmp);
	}
}

void MeasureMenuItem(LPMEASUREITEMSTRUCT mi)
{
    // create the font we will use for the title
    HFONT hfont,oldhfont;
	HDC hdc;
	SIZE size;
	PMENUINFO pmi;
	
	pmi=(PMENUINFO)mi->itemData;
	hfont = ( HFONT )GetStockObject(ANSI_VAR_FONT);
	hdc=GetDC(NULL);
	oldhfont = ( HFONT )SelectObject(hdc,hfont);
	GetTextExtentPoint32(hdc,pmi->szString,strlen(pmi->szString),&size);
	SelectObject(hdc,oldhfont);
	DeleteObject(hfont);

	// add in the left margin for the menu item
	size.cx += GetSystemMetrics(SM_CXMENUCHECK)+8;

	// return the width and height
	mi->itemWidth = size.cx;
	mi->itemHeight = size.cy+6;
}

void DrawMenuItem(HIMAGELIST hIml, LPDRAWITEMSTRUCT di)
{
    // create the font we will use for the title
    HFONT hfont,oldhfont;
	HBRUSH hbgb;
	int mode;
	COLORREF text,back;
	PMENUINFO pmi;
	
	pmi=(PMENUINFO)di->itemData;

	hfont = ( HFONT )GetStockObject(ANSI_VAR_FONT);

	if((BOOL)(di->itemState & ODS_SELECTED))
	{
		hbgb = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		FillRect(di->hDC, &di->rcItem, hbgb);
		DeleteObject(hbgb);

        // Set the text background and foreground colors
        text=SetTextColor(di->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        back=SetBkColor(di->hDC, GetSysColor(COLOR_HIGHLIGHT));
   	}
	else
	{
		hbgb = CreateSolidBrush(GetSysColor(COLOR_MENU));
		FillRect(di->hDC, &di->rcItem, hbgb);
		DeleteObject(hbgb);

        // Set the text background and foreground colors to the 
        // standard window colors
        text=SetTextColor(di->hDC, GetSysColor(COLOR_MENUTEXT));
        back=SetBkColor(di->hDC, GetSysColor(COLOR_MENU));
	}

	if((BOOL)(di->itemState & ODS_DISABLED))
	{
		SetTextColor(di->hDC, GetSysColor(COLOR_GRAYTEXT));
	}

	mode = SetBkMode(di->hDC, TRANSPARENT);

	ImageList_Draw(hIml,pmi->uIcon,
			di->hDC,
			di->rcItem.left,
			di->rcItem.top+1,
			ILD_TRANSPARENT);

	// add the menu margin offset
	di->rcItem.left += GetSystemMetrics(SM_CXMENUCHECK)+8;

	oldhfont = (HFONT)SelectObject(di->hDC, hfont);

	// draw the text left aligned and vertically centered
	DrawText(di->hDC,pmi->szString, -1, &di->rcItem, DT_SINGLELINE|DT_VCENTER|DT_LEFT);

	SelectObject(di->hDC, oldhfont);
	SetBkMode(di->hDC, mode);
	SetTextColor(di->hDC, text);
	SetBkColor(di->hDC, back);
}

typedef struct __qyTrayProcBuf_t {
	HINSTANCE hInst;
	HIMAGELIST hIml;
} QY_TRAY_PROC_BUF;

 LRESULT CALLBACK qyTrayProc( HWND hwnd, UINT msg, 
							  WPARAM wParam, LPARAM lParam )
{
	static QY_TRAY_PROC_BUF sProcBuf;
	static char HelpFile[MAX_PATH + 1] = "\0";
	static BOOL InPGPOperation = FALSE;
	static HWND hwndFocus;
	static BOOL sbCreated = FALSE;
		

	// check for hotkey-related messages
	// if ( sbCreated ) qtCheckForHotKeyPrefsMsg( sProcBuf.hInst, hwnd, msg );
	
	switch(msg)
	{
		case WM_CREATE:
		{
			debugLog( "qyTrayProc( ) WM_CREATE." );

			memset( &sProcBuf, 0, sizeof( sProcBuf ) );
			CREATESTRUCT *pCS = ( LPCREATESTRUCT )lParam;
			sProcBuf.hInst = pCS->hInstance;

			InitCommonControls();

			miKeys.uIcon=0;
			miTools.uIcon=1;
			miDisk.uIcon=2;
			miNet.uIcon=3;

			PGPtrayCreateImageList( sProcBuf.hInst, &sProcBuf.hIml );

			QTLoadAndSetHotKeys( sProcBuf.hInst, hwnd );
			
			// start timer that periodically queries PGPnet service for status
			// if (PGPnetExists) {
			//	SetTimer(hwnd, PGPNET_TIMER_ID, PGPNET_TIMER_MS, NULL);
			//	PostMessage (hwnd, WM_TIMER, 0, 0);
			// }

			sbCreated = TRUE;
			
			return 0;

		}

		case WM_HOTKEY:
		{
			debugLog( "qyTrayProc( ) WM_HOTKEY." );

			qtProcessHotKey(hwnd, wParam);

			return TRUE;
		}

		case WM_TIMER :
		{
			debugLog( "qyTrayProc( ) WM_TIMER." );

			qtUpdateTrayIconAndText( sProcBuf.hInst, hwnd );

			return 0;
		}

		case WM_DRAWITEM: 
        {
			debugLog( "qyTrayProc( ) WM_DRAWITME." );

	        DrawMenuItem( sProcBuf.hIml, (LPDRAWITEMSTRUCT) lParam );

            return TRUE;
        }

        case WM_MEASUREITEM:
		{
			debugLog( "qyTrayProc( ) WM_MEASUREITEM." );

	        MeasureMenuItem((LPMEASUREITEMSTRUCT)lParam);

            return TRUE;
		}

		case WM_QUERYOPEN:
		{
			debugLog( "qyTrayProc( ) WM_QUERYOPEN." );

			return 0;
		}

		case WM_TASKAREA_MESSAGE:
		{
			debugLog( "qyTrayProc( ) WM_TASKAREA_MESSAGE." );

			UINT uID = (UINT) wParam;
			UINT uMouseMsg = (UINT) lParam;

			if(uMouseMsg == WM_RBUTTONDOWN)
			{
				switch(uID)
				{
					case 1:
					{
						PopupTaskbarMenu( sProcBuf.hInst, hwnd, InPGPOperation );
						return 0;
					}
				}
			}
			else if(uMouseMsg == WM_LBUTTONDOWN)
			{
				switch(uID)
				{
					case 1:
					{
						PopupTaskbarMenu( sProcBuf.hInst, hwnd, InPGPOperation );
						return 0;
					}
				}
			}
			break;
		}

		case WM_COMMAND:
		{
			debugLog( "qyTrayProc( ) WM_COMMAND." );

			// Menu is greyed, but just in case hot keys are sending 
			// messages
			if(InPGPOperation)
				break;

			switch(wParam)
			{
				
				/*
				case ID_WIPECLIP:
				{
					InPGPOperation = TRUE;
					ClipboardWipe(hwnd,PGPsc);
					InPGPOperation = FALSE;
					break;
				}
				*/
				
				/*
				
				case ID_PGPNETHOSTS:
				{
					InPGPOperation = TRUE;
					PTNetLaunch(hwnd, PGPNET_HOSTPAGE);
					InPGPOperation = FALSE;
					break;
				}
				*/
				
				/*
								
				case ID_PGPNETLOGOFF:
				{
					InPGPOperation = TRUE;
					PTSendLogOnOffMessage (hwnd, LOGOFF);
					InPGPOperation = FALSE;
					break;
				}
				*/

								
				case ID_HELP_TOPICS:
				{
					InPGPOperation = TRUE;
					// PGPpath(HelpFile);
					strcat(HelpFile,"PGP.hlp");
					// WinHelp(hwnd, HelpFile, HELP_FINDER, 0);
					MessageBox( NULL, "help!", "qycx", MB_OK );
					InPGPOperation = FALSE;
					break;
				}
								
			}
			break;
		}
		
		case WM_ENDSESSION :
		{
			debugLog( "qyTrayProc( ) WM_ENDSESSION." );

			break;
		}

		case WM_CLOSE:
		{	
			debugLog( "qyTrayProc( ) WM_CLOSE." );

			// KillTimer(hwnd, nLaunchKeysTimer);
			PTRemoveHotKeys(hwnd);
			PostQuitMessage(0);	
			return 0;
		}

	}
	
	debugLog( "qyTrayProc( ) DefWindowProc( )." );

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

