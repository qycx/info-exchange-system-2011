// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include	<tchar.h>
#include	"qyMcMainCommon.h"


HINSTANCE	g_hInst  =  NULL;


//  2013/06/10
 HINSTANCE  get_my_hInst(  )
{
	return  g_hInst;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if  (  !g_hInst  )  g_hInst  =  hModule;
	MACRO_qyAssert(  g_hInst  ==  hModule,  _T(  "isCliD3d: g_hInst err"  )  );

	//
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


#if  0
ATOM MyRegisterClass_test(HINSTANCE hInstance);
int  MyUnregisterClass_test(  HINSTANCE  hInst  );
#endif


__declspec(  dllexport  )  int  dllInit_d3d_isCli(  )	
{
	int				iErr	=	-1;

#if  0
	ATOM	a;
	a  =  MyRegisterClass_test(  g_hInst  );
	if  (  !a  )  goto  errLabel;
#endif


	iErr  =  0;
errLabel:



	return  iErr;
}

__declspec(  dllexport  )  int  dllExit_d3d_isCli(  )
{
#if  0
	MyUnregisterClass_test(  g_hInst  );
#endif

	return  0;
}
