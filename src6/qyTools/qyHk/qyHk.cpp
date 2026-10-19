// qyHk.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"


HINSTANCE g_hinst;


#pragma data_seg(".SHARDAT")
static HHOOK  g_hCBTHook   = NULL ;
static DWORD  TrayProcessID = 0   ;
static HWND   hwndShell_TrayWnd = 0   ;
static HWND   hwndReBarWindow32 = 0   ;
static HWND   hwndMSTaskSwWClass = 0   ;
static HWND   hwndSysTabControl32 = 0   ;
static HWND   CurrentFocus = NULL ; // SetFocus window
#pragma data_seg()

// void (*AttachOutlookExpressPlugin)(HWND);

int mystrlen(char *string)
{
	int len;

	len=0;

	while(string[len]!=0)
	{
		len++;
	}

	return len;
}

int mystrcmp(char *string1,char *string2)
{
	int index,len1,len2;

	len1=mystrlen(string1);
	len2=mystrlen(string2);

	if(len1!=len2)
		return 1;

	for(index=0;index<len1;index++)
	{
		if(string1[index]!=string2[index])
		{
			return 1;
		}
	}

	return 0; // They are equal
}

 extern "C" LRESULT WINAPI qyCBTProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		switch (nCode)
        {
			case HCBT_SETFOCUS:
			{
				HWND hwndCurrent;
				DWORD ThreadID;
				DWORD ProcessID;

				hwndCurrent=(HWND)wParam;

				ThreadID=GetWindowThreadProcessId(hwndCurrent,&ProcessID);
				if((ProcessID!=TrayProcessID)&&(CurrentFocus!=hwndCurrent)&&
					(hwndCurrent!=NULL)&&
					// These have to be checked for because of brain
					// dead Windows2000 (tm)
					(hwndCurrent!=hwndSysTabControl32)&&
					(hwndCurrent!=hwndMSTaskSwWClass)&&
					(hwndCurrent!=hwndReBarWindow32)&&
					(hwndCurrent!=hwndShell_TrayWnd))
				{
					CurrentFocus=hwndCurrent;
				}
				break;
			}	
			
			case HCBT_CREATEWND:
			case HCBT_ACTIVATE:
			{
				/*				
				char szWndClass[32];
				HANDLE hPGPoe;
				DLGPROC lpOldProc;
				HKEY hkey;

				// Don't try loading Outlook Express plug-in if
				//	it wasn't installed 

				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, OE_REG_KEY, 0, 
						KEY_ALL_ACCESS, &hkey) != ERROR_SUCCESS)
					break;

				GetClassName((HWND) wParam, szWndClass, sizeof(szWndClass)-1);

				if (!mystrcmp(szWndClass, "ThorBrowserWndClass") || 
					!mystrcmp(szWndClass, "ATH_Note") ||
					!mystrcmp(szWndClass, "Outlook Express Browser Class"))
				{
					// Check to make sure we haven't already attached

					lpOldProc = (DLGPROC)GetProp((HWND) wParam, "oldproc");
					if (lpOldProc != NULL)
					{
						RegCloseKey(hkey);
						break;
					}

					// Attempt to load the Outlook Express plug-in DLL 

					hPGPoe = LoadLibrary("PGPoe.dll");
					if (hPGPoe == NULL)
					{
						char szMsg[255];
						char szTitle[255];

						RegDeleteKey(hkey, "OutlookExpress");
						RegCloseKey(hkey);
						RegDeleteKey(HKEY_LOCAL_MACHINE, OE_REG_KEY);

						LoadString(g_hinst, IDS_NOPLUGIN, szMsg, 254);
						LoadString(g_hinst, IDS_TITLE, szTitle, 254);
						MessageBox(NULL, szMsg, szTitle, MB_ICONEXCLAMATION);
					}
					else
					{
						AttachOutlookExpressPlugin = (void (*)(HWND)) 
							GetProcAddress(hPGPoe, 
								"AttachOutlookExpressPlugin");

						AttachOutlookExpressPlugin((HWND) wParam);
						RegCloseKey(hkey);
					}
				}
				else
					RegCloseKey(hkey);
				*/
				break;
			}	
		}			
	}

	return CallNextHookEx (g_hCBTHook, nCode, wParam, lParam);
}


 extern "C" HWND qyReadCurrentFocus(void)
{
	return CurrentFocus;
}

 extern "C" void qySetHook(void)
{
	TrayProcessID=GetCurrentProcessId();

	// These have to be checked for because of brain
	// dead Windows2000 (tm)
	hwndShell_TrayWnd=FindWindowEx(NULL,
		NULL,"Shell_TrayWnd",NULL);
	hwndReBarWindow32=FindWindowEx(hwndShell_TrayWnd,
		NULL,"ReBarWindow32",NULL);
	hwndMSTaskSwWClass=FindWindowEx(hwndReBarWindow32,
		NULL,"MSTaskSwWClass",NULL);
	hwndSysTabControl32=FindWindowEx(hwndMSTaskSwWClass,
		NULL,"SysTabControl32",NULL);

	g_hCBTHook=SetWindowsHookEx(WH_CBT, 
		(HOOKPROC)qyCBTProc,
		g_hinst,
		0);
}

 extern "C" void qyDeleteHook(void)
{
	UnhookWindowsHookEx(g_hCBTHook);

	hwndShell_TrayWnd=0;
	hwndMSTaskSwWClass=0;
	hwndSysTabControl32=0;
	hwndReBarWindow32=0;
}
		
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason,LPVOID lpvReserved)
{
   switch (fdwReason) {
      case DLL_PROCESS_ATTACH:
         g_hinst = hinstDll;
		 //vErrorOut(fg_white,"DLL_PROCESS_ATTACH\n");
         break;
      case DLL_THREAD_ATTACH:
		  //vErrorOut(fg_white,"DLL_THREAD_ATTACH\n");
         break;
      case DLL_THREAD_DETACH:
		  //vErrorOut(fg_red,"DLL_THREAD_DETACH\n");
		break;
      case DLL_PROCESS_DETACH:
		  //vErrorOut(fg_red,"DLL_PROCESS_DETACH\n");
         break;
   }
   return(TRUE);
}


