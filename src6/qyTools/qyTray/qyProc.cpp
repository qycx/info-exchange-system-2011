
#include "stdafx.h"
#include "resource.h"
#include "qtCommon.h"

#define IPC_TIMEOUT			2500

BOOL		g_bLogonEnabled		= FALSE;
BOOL		g_bLogoffEnabled	= FALSE;
BOOL		g_bGUIEnabled		= TRUE;

//	________________________
//
//	Launch PGPnet.exe, specifying the start page

 VOID PTNetLaunch( HWND	hwnd, UINT uStartPage )
{
	 /*
	PGPError	err					= kPGPError_OutputBufferTooSmall;
	CHAR		szFile[MAX_PATH];
	CHAR		sz[16];

	err = PGPclGetPGPPath (szFile, sizeof(szFile));

	if (IsntPGPError (err)) 
	{
		if ((lstrlen (szFile) + lstrlen (PGPNET_NETAPP)) <= sizeof(szFile))
		{
			lstrcat (szFile, PGPNET_NETAPP);

			if ((lstrlen (szFile) +4) <= sizeof(szFile))
			{
				wsprintf (sz, " /%i", uStartPage);
				lstrcat (szFile, sz);

				err = WinExec (szFile, SW_SHOW);

				if (err <= 31)
					err = kPGPError_FileNotFound;
				else
					err = kPGPError_NoErr;
			}
		}
	}

	if (IsPGPError (err))
	{
		PTMessageBox (hwnd, IDS_CAPTION, IDS_CANNOTLAUNCHPGPNET,
							MB_OK|MB_ICONSTOP);
	}
	*/
}

//	________________________
//
//	Send message to service, if running

 static BOOL sSendServiceMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	 /*
	HWND	hwnd;
	DWORD	dwResult;

	hwnd = FindWindow (PGPNET_SERVICECOMMWINDOWNAME, 
									PGPNET_SERVICECOMMWINDOWNAME);
	if (hwnd)
	{
		if (SendMessageTimeout (hwnd, uMsg, wParam, lParam, 
							SMTO_NORMAL, IPC_TIMEOUT, &dwResult))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
		*/
	 return FALSE;
}

//	________________________
//
//	Send logon, logoff, or query message to service

 BOOL PTSendLogOnOffMessage( HWND hwnd, UINT uMessage )
{
	BOOL	bReturn		= FALSE;

	/*
	switch (uMessage) {
	case QUERYSERVICE :
		bReturn = TRUE;
		break;

	case QUERYLOGON :
		bReturn = sSendServiceMessage (PGPNET_M_APPMESSAGE, 
							PGPNET_QUERYLOGONSTATUS, (LPARAM)hwnd);
		break;

	case LOGON :
		bReturn = sSendServiceMessage (PGPNET_M_APPMESSAGE, 
							PGPNET_LOGON, (LPARAM)hwnd);
		break;

	case LOGOFF :
		bReturn = sSendServiceMessage (PGPNET_M_APPMESSAGE, 
							PGPNET_LOGOFF, (LPARAM)hwnd);
		break;
	}

	if (!bReturn)
	{
		// service didn't respond
		g_bLogonEnabled = FALSE;
		g_bLogoffEnabled = FALSE;
	}

  */
	return bReturn;
}


//	________________________
//
//	Query service for status

 static UINT sGetServiceStatus( HWND hwnd )
{
	 /*
	HWND	hwndService;
	DWORD	dwResult;

	hwndService = FindWindow (PGPNET_SERVICECOMMWINDOWNAME, 
									PGPNET_SERVICECOMMWINDOWNAME);
	if (hwndService)
	{
		if (SendMessageTimeout (hwndService, PGPNET_M_APPMESSAGE, 
							(WPARAM)PGPNET_QUERYDRIVERSTATUS, (LPARAM)hwnd,
							SMTO_NORMAL, IPC_TIMEOUT, &dwResult))
			return dwResult;
		else 
			return PGPNET_SERVICENOTRESPONDING;
	}
	else
		return PGPNET_SERVICENOTAVAILABLE;
		*/
	 return 0;
}


//	________________________
//
//	Get icon and tooltip text based on driver/service status

 static HICON sGetIconAndText( HINSTANCE hInst, HWND hwnd, LPSTR psz, UINT uLen )
{
	HICON	hicon;

	switch ( sGetServiceStatus( hwnd ) ) {
	
		case PGPNET_SERVICENOTRESPONDING :
			g_bGUIEnabled = TRUE;
			hicon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_SERVICENOTRESPOND ) );
			LoadString( hInst, IDS_SERVICENOTRESPOND, psz, uLen );
			break;

		case PGPNET_SERVICENOTAVAILABLE :
		default :
			g_bGUIEnabled = TRUE;
			hicon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_SERVICENOTAVAIL ) );
			LoadString( hInst, IDS_SERVICENOTAVAIL, psz, uLen);
			break;

	}

	return hicon;
}


//_________________________________________
//
//	update system tray icon

 BOOL qtUpdateTrayIconAndText( HINSTANCE hInst, HWND	hwnd )
{
	BOOL			result;
	NOTIFYICONDATA	nid;
	HICON			hicon;
	CHAR			sz[64];

	hicon = sGetIconAndText( hInst, hwnd, sz, sizeof(sz));

	memset (&nid, 0x00, sizeof(NOTIFYICONDATA));

	nid.cbSize				= sizeof(NOTIFYICONDATA);
	nid.hWnd				= hwnd;
	nid.uID					= TASKBAR_TRAY_ID;
	nid.uFlags				= NIF_ICON | NIF_TIP;
	nid.hIcon				= hicon;
	lstrcpy (nid.szTip, sz);

	result = Shell_NotifyIcon (NIM_MODIFY, &nid);

	return result;
}


//	________________________
//
//	check incoming message for something pertaining to PGPnet

 VOID PTCheckForNetMsg( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	 /*
	switch (msg) 
	{
		case PGPNET_M_APPMESSAGE :
			switch (wParam) {
			case PGPNET_CONFIGUPDATED :
				PTUpdateTrayIconAndText (hwnd);
				break;

			case PGPNET_DISABLEGUI :
				// relenquish the foreground window to the PGPnet service
				SetForegroundWindow ((HWND)lParam);
				g_bGUIEnabled = FALSE;
				break;

			case PGPNET_ENABLEGUI :
				g_bGUIEnabled = TRUE;
				break;
			}
			break;

		case WM_COPYDATA :
		{
			PCOPYDATASTRUCT pcds	= (PCOPYDATASTRUCT)lParam;
			switch (pcds->dwData) {
			case PGPNET_LOGONSTATUS :
				if (pcds->cbData == sizeof(DWORD))
				{
					DWORD*	pdwStatus = (DWORD*)(pcds->lpData);
					switch (*pdwStatus) {
					case PGPNET_LOGGEDOFF :
						g_bLogonEnabled = TRUE;
						g_bLogoffEnabled = FALSE;
						break;

					case PGPNET_LOGGEDON :
						g_bLogonEnabled = FALSE;
						g_bLogoffEnabled = TRUE;
						break;

					default :
						g_bLogonEnabled = FALSE;
						g_bLogoffEnabled = FALSE;
						break;
					}
				}
			}
			break;
		}
	}

  */

}

//	________________________
//
//	query booleans

BOOL
PTNetIsGUIDisabled (void)
{
	return !g_bGUIEnabled;
}

BOOL
PTNetIsLogonDisabled (void)
{
	return !g_bLogonEnabled;
}

BOOL
PTNetIsLogoffDisabled (void)
{
	return !g_bLogoffEnabled;
}


 void InsertOwnerDrawnMenuItem(HMENU hMenu,UINT pos,
							  UINT id,HMENU hSubMenu,PMENUINFO pmi)
{
	MENUITEMINFO mii;
	BOOL result;

	memset(&mii,0x00,sizeof(MENUITEMINFO));

	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_TYPE|MIIM_DATA|MIIM_ID|MIIM_STATE|MIIM_SUBMENU;
	mii.fType=MFT_OWNERDRAW;
	mii.dwItemData=(DWORD)pmi;
	mii.wID=id;
	mii.fState=MFS_ENABLED;
	mii.hSubMenu=hSubMenu;

	result=InsertMenuItem(hMenu, 
		pos, 
		TRUE,  
		&mii); 

}



 BOOL PopupTaskbarMenu( HINSTANCE hInst, HWND hwndTarget, BOOL InPGPOperation)
{
	HMENU hMenu = NULL;
	HMENU hSubMenu = NULL;
	HMENU hMenuNet = NULL;
	HMENU hSubMenuNet = NULL;

	POINT pt;

	debugLog( "PopupTaskbarMenu( ) enters." );

	GetCursorPos( &pt );

	// If the cursor is at the top, we need to reverse the menu
	if(pt.y<200)
	{
		// load up menu
		hMenu = LoadMenu( hInst, MAKEINTRESOURCE(IDM_TASKBARMENUREV));
		hSubMenu = GetSubMenu(hMenu,0);

		// Make these owner drawn so we can get icons
		/*if (PGPnetExists) 
		{
			// load up PGPnets popup menu
			hMenuNet = LoadMenu( hInst, MAKEINTRESOURCE(IDM_PGPNETPOPUP));
			hSubMenuNet = GetSubMenu(hMenuNet,0);

			InsertOwnerDrawnMenuItem(
					hSubMenu,3,ID_LAUNCHPGPNET,hSubMenuNet,&miNet);
		}
		if (PGPtoolsExists)
			InsertOwnerDrawnMenuItem(hSubMenu,3,ID_LAUNCHPGPTOOLS,NULL,&miTools);
		*/
	}
	else
	{
		// load up menu
		hMenu = LoadMenu( hInst, MAKEINTRESOURCE(IDM_TASKBARMENU));
		hSubMenu = GetSubMenu(hMenu,0);

		// Make these owner drawn so we can get icons
		/*
		if (PGPtoolsExists)
			InsertOwnerDrawnMenuItem(hSubMenu,5,ID_LAUNCHPGPTOOLS,NULL,&miTools);
		if (PGPnetExists) 
		{
			// load up PGPnets popup menu
			hMenuNet = LoadMenu( hInst, MAKEINTRESOURCE(IDM_PGPNETPOPUP));
			hSubMenuNet = GetSubMenu(hMenuNet,0);

			InsertOwnerDrawnMenuItem(
					hSubMenu,5,ID_LAUNCHPGPNET,hSubMenuNet,&miNet);
		}
		*/
	}

	if(InPGPOperation || PTNetIsGUIDisabled ())
	{

		/*
		EnableMenuItem(hMenu, 
					   ID_ENCRYPTWINDOW, 
					   MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, 
					   ID_DECRYPTVERIFYWINDOW, 
					   MF_BYCOMMAND | MF_GRAYED);
		*/
		EnableMenuItem(hMenu, 
					   ID_HELP_TOPICS, 
					   MF_BYCOMMAND | MF_GRAYED);
		// PGPnet submenu
		/*
		EnableMenuItem(hMenuNet, 
					   ID_PGPNETSTATUS, 
					   MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenuNet, 
					   ID_PGPNETLOG, 
					   MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenuNet, 
					   ID_PGPNETHOSTS, 
					   MF_BYCOMMAND | MF_GRAYED);
		*/
		/*
		EnableMenuItem(hMenuNet, 
					   ID_PGPNETLOGON, 
					   MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenuNet, 
					   ID_PGPNETLOGOFF, 
					   MF_BYCOMMAND | MF_GRAYED);
		*/
	}
	else
	{
		/*
		if (PTNetIsLogonDisabled ())
		{
			EnableMenuItem(hMenuNet, 
					   ID_PGPNETLOGON, 
					   MF_BYCOMMAND | MF_GRAYED);
		}

		if (PTNetIsLogoffDisabled ())
		{
			EnableMenuItem(hMenuNet, 
					   ID_PGPNETLOGOFF, 
					   MF_BYCOMMAND | MF_GRAYED);
		}
		*/
	}

	//  Calls to SetForegroundWindow and PostMessage to fix a bug
    //  documented in PSS ID Number: Q135788
	SetForegroundWindow(hwndTarget); 
	TrackPopupMenu( hSubMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON, 
					pt.x, pt.y, 0, hwndTarget, NULL);
	PostMessage( hwndTarget, WM_NULL, 0, 0 ) ;
	// Above fixes "three clicks" problem  -wjb

	DestroyMenu(hMenu);

	debugLog( "PopupTaskbarMenu( ) leaves." );

	return TRUE;
}

