
#ifndef __QTCOMMON_H__
#define __QTCOMMON_H__	/* { */

#include <shellapi.h>

#include "qyCommon.h"
#include "qyHotKeys.h"
#include "qtHotKeys.h"
#include "qyHk.h"

#define MAX_LOADSTRING 100
#define NUM_BITMAPS 4

#define RELOADPREFSMSG	("PGPM_RELOADPREFS")

#define PGPTRAY_M_DISABLEHOTKEYS			WM_APP+100

// These are values passed from service to app as return value to 
// PGPNET_QUERYDRIVERSTATUS message (see below).
#define PGPNET_SERVICENOTRESPONDING	0
#define PGPNET_SERVICENOTAVAILABLE	1
#define PGPNET_DRIVERENABLED		2
#define PGPNET_DRIVERDISABLED		3
#define PGPNET_DRIVERNOTAVAILABLE	4

#define TASKBAR_TRAY_ID			1
#define WM_TASKAREA_MESSAGE		WM_USER + 1


typedef struct {
	char szString[20];
	UINT uIcon;
} MENUINFO, *PMENUINFO;


typedef struct __qyTray_t {
	HINSTANCE	ghInst;
	HICON		hIconKey;
	HWND		hwndTray;
	char		szApp[100];
} QY_TRAY;


VOID QTLoadAndSetHotKeys( HINSTANCE hInst, HWND hwnd );
VOID qtProcessHotKey( HWND	hwnd, WPARAM wParam );
BOOL qtUpdateTrayIconAndText( HINSTANCE hInst, HWND	hwnd );
BOOL PopupTaskbarMenu( HINSTANCE hInst, HWND hwndTarget, BOOL InPGPOperation);
INT qyMessageBox( HINSTANCE hInst, HWND hwnd, INT iCaption, INT iText, UINT	uStyle );
VOID PTRemoveHotKeys( HWND hwnd );
VOID qtCheckForHotKeyPrefsMsg( HINSTANCE hInst, HWND hwnd, UINT	msg );
BOOL TaskbarAddIcon( HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip, UINT cbMsg );
BOOL TaskbarDeleteIcon(HWND hwnd, UINT uID);
VOID PTHotKeyInit (void);
HWND TrayWindow( QY_TRAY *pQT );
LRESULT CALLBACK qyTrayProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );



#endif /* } */


