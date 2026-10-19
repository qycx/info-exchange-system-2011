

#include "stdafx.h"
#include "resource.h"
#include "qtCommon.h"


UINT	uReloadPrefsMsg			= 0;

 static VOID sRemoveHotKeys (HWND hwnd)
{
	// UnregisterHotKey (hwnd, kEncryptSignCurrentWindow);
}


 static BOOL sSetSingleHotKey( HWND hwnd, UINT uID, unsigned int uKey )
{
	if ( uKey & QY_HOTKEY_ENABLED ) {
		UINT	uMod	= 0;

		if ( uKey & QY_HOTKEY_ALTMODIFIER )
			uMod |= MOD_ALT;
		if ( uKey & QY_HOTKEY_CTRLMODIFIER )
			uMod |= MOD_CONTROL;
		if ( uKey & QY_HOTKEY_SHIFTMODIFIER )
			uMod |= MOD_SHIFT;

		return RegisterHotKey (hwnd, uID, uMod, (uKey & 0xFF));
	}
	else
		return TRUE;
}


 static VOID sSetHotKeys( HINSTANCE hInst, HWND hwnd )
{
	int				ids			= 0;
	QY_HOTKEYS		hotkeys;
		
	memcpy( &hotkeys, &sDefaultHotKeys, sizeof( hotkeys ) );

	// ◊¢“‚’‚¿Ô:
	// get hotKeys cfg and set ths hotkeys
	
	if ( !sSetSingleHotKey( hwnd, QT_PURGE_PASSPHRASECACHE, 
			hotkeys.hotkeyPurgePassphraseCache ) )
	{
		hotkeys.hotkeyPurgePassphraseCache &= ~QY_HOTKEY_ENABLED;
		ids = IDS_CANNOTSETPURGEHOTKEY;
		goto done;
	}

	if ( !sSetSingleHotKey( hwnd, QT_ENCRYPT_CURRENTWINDOW, 
			hotkeys.hotkeyEncrypt ) )
	{
		hotkeys.hotkeyEncrypt &= ~QY_HOTKEY_ENABLED;
		ids = IDS_CANNOTSETENCRYPTHOTKEY;
		goto done;
	}
	
	
	if (!sSetSingleHotKey (hwnd, QT_DECRYPT_CURRENTWINDOW, 
			hotkeys.hotkeyDecrypt))
	{
		hotkeys.hotkeyDecrypt &= ~QY_HOTKEY_ENABLED;
		ids = IDS_CANNOTSETDECRYPTHOTKEY;
		goto done;
	}


done:
	if ( ids ) {
		qyMessageBox( hInst, hwnd, IDS_CAPTION, ids, MB_ICONEXCLAMATION|MB_OK);
	}

}


 VOID PTHotKeyInit (void)
{
	uReloadPrefsMsg = RegisterWindowMessage (RELOADPREFSMSG);
}


 VOID qtCheckForHotKeyPrefsMsg( HINSTANCE hInst, HWND hwnd, UINT	msg )
{
	if (msg == uReloadPrefsMsg)
	{
		sRemoveHotKeys (hwnd);
		sSetHotKeys( hInst, hwnd);
	}
	else if (msg == PGPTRAY_M_DISABLEHOTKEYS)
	{
		sRemoveHotKeys (hwnd);
	}
}


 VOID QTLoadAndSetHotKeys( HINSTANCE hInst, HWND hwnd )
{
	sSetHotKeys( hInst, hwnd );
}


 VOID qtProcessHotKey( HWND	hwnd, WPARAM wParam )
{
	switch (wParam) {
		case QT_PURGE_PASSPHRASECACHE :
			break;

		case QT_ENCRYPT_CURRENTWINDOW :
			// SendMessage (hwnd, WM_COMMAND, ID_ENCRYPTWINDOW, 0);
			break;

		case QT_SIGN_CURRENTWINDOW :
			// SendMessage (hwnd, WM_COMMAND, ID_SIGNWINDOW, 0);
			break;
		
		case QT_DECRYPT_CURRENTWINDOW :
			// SendMessage (hwnd, WM_COMMAND, ID_DECRYPTVERIFYWINDOW, 0);
			break;

	}
}


 VOID PTRemoveHotKeys( HWND hwnd )
{
	sRemoveHotKeys (hwnd);
}



