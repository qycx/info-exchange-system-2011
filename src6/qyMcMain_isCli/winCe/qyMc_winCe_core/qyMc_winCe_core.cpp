// qyMc_winCe_core.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "qyMc_winCe_core.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
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

// This is an example of an exported variable
QYMC_WINCE_CORE_API int nqyMc_winCe_core=0;

// This is an example of an exported function.
QYMC_WINCE_CORE_API int fnqyMc_winCe_core(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see qyMc_winCe_core.h for the class definition
CqyMc_winCe_core::CqyMc_winCe_core()
{ 
	return; 
}
