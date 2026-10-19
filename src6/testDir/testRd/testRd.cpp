// testRd.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

 
 typedef int (  *PF_myDllMain  )(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow,  HMODULE  hDll,  void  *  pEnv,  void  *  p1  );

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.

	HINSTANCE		hDll	=	NULL;
	PF_myDllMain	pf	=	NULL;
	char			cmdBuf[1024]	=	"-connect 192.168.1.18";

	hDll  =  LoadLibrary(  ".\\qwmRd.dll"  );
	if  (  hDll  )  {
		pf  =  (  PF_myDllMain  )GetProcAddress(  hDll,  "myDllMain"  );
		lpCmdLine  =  cmdBuf;
		if  (  pf  )  pf(   hInstance, hPrevInstance, lpCmdLine, nCmdShow,  hDll,  0,  0  );
		FreeLibrary(  hDll  );
	}
	


	 //  myWinMain(  hInstance, hPrevInstance, lpCmdLine, nCmdShow  );



	return 0;
}



