
#ifndef __INC_MAIN_H
#define __INC_MAIN_H

#include<windows.h>

extern DWORD WINAPI EntryPoint(LPVOID lpParameter);

extern HMODULE g_module;
extern HANDLE g_hfm;
extern char g_svStealthOptions[];
extern BOOL g_bRestart;
extern char g_svRestartProcess[64];
extern BOOL g_bEradicate;

#endif