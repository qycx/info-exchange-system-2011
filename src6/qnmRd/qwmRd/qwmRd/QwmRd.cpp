// QwmRd.cpp: implementation of the CQwmRd class.
//
//////////////////////////////////////////////////////////////////////


#include	"rdMenu.h"
#include	"vncInstHandler.h"

#include	<windows.h>
#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"QwmRd.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQwmRd::CQwmRd()
{

}

CQwmRd::~CQwmRd()
{

}

 BOOL  PostToRd(  UINT message,  WPARAM wParam,  LPARAM lParam  )
{
	// Locate the hidden WinVNC menu window
	HWND hservwnd = FindWindow(MENU_CLASS_NAME, NULL);
	if (hservwnd == NULL)
		return FALSE;

	// Post the message to WinVNC
	PostMessage(hservwnd, message, wParam, lParam);
	return TRUE;
}


 BOOL  CQwmRd::PostAddNewClient(unsigned long ipaddress)
{
	// Post to the WinVNC menu window
	if (!PostToRd(MENU_ADD_CLIENT_MSG, 0, ipaddress))
	{
		myLog.Print(  LL_STATE,  "Failed Rd"  );
		return FALSE;
	}

	return TRUE;
}



 extern  "C"  __declspec( dllexport )  int  myDllMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow,  HMODULE  hDll,  void  *  pEnv,  void  *  p1  )
{
	int		iErr	=	-1;

	memset(  &gQnmRdStruct,  0,  sizeof(  gQnmRdStruct  )  );
	gQnmRdStruct.pEnv  =  pEnv;
	hInstance  =  hDll;	//  切记；这里，用dll的句柄来替代应用句柄，因为资源都放在dll里了

	if  (  !bMyPermittedProcess(  )  )  {
		traceLogA(  "非授权调用qwmRd.dll"  );  return  -1;		//  2007/02/09, 加入了对调用程序的限制，不再允许任意程序调用了
	}

	setbuf(stderr, 0);

	// Configure the log file, in case one is required
#ifdef  __DEBUG__
	    myLog.SetFile("c:\\tempbbb\\qwmRd.log", false);
	    myLog.SetMode(  CONST_qyLog_toFile  );  
#endif

#ifdef _DEBUG
	{
		// Get current flag
		int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

		// Turn on leak-checking bit
		tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

		// Set flag to the new value
		_CrtSetDbgFlag( tmpFlag );
	}
#endif

	// Save the application instance and main thread id
	hAppInstance = hInstance;
	mainthreadId = GetCurrentThreadId();

	// Initialise the CQySock system
	VSocketSystem socksys;
	if (!socksys.Initialised())
	{
		myLog.Print(  LL_INTERR,  MACRO_log(  "Failed to initialise the socket system"  )  );
		goto  errLabel;
	}
	vnclog.Print(LL_STATE, MACRO_log("sockets initialised"));

	// Make the command-line lowercase and parse it
	int i;
	for (i = 0; i < strlen(szCmdLine); i++)
	{
		szCmdLine[i] = tolower(szCmdLine[i]);
	}

	BOOL argfound;
	//
	argfound = FALSE;

	for (i = 0; i < strlen(szCmdLine); i++)
	{
		if (szCmdLine[i] <= ' ')
			continue;
		argfound = TRUE;


		//  2006/03/06
		if (strnicmp(&szCmdLine[i], CONST_qwmCmdLine_monDesktop, strlen(  CONST_qwmCmdLine_monDesktop  )) == 0)  gQnmRdStruct.ucbMonDesktop  =  TRUE;


		if (strncmp(&szCmdLine[i], CONST_qwmCmdLine_rdAddNewClient, strlen(CONST_qwmCmdLine_rdAddNewClient)) == 0)
		{
			// Add a new client to an existing copy of winvnc
			i+=strlen(CONST_qwmCmdLine_rdAddNewClient);

			// First, we have to parse the command line to get the filename to use
			int start, end;
			start=i;
			while (szCmdLine[start] <= ' ' && szCmdLine[start] != 0) start++;
			end = start;
			while (szCmdLine[end] > ' ') end++;

			// Was there a filename given?
			if (end-start > 0) {
				char *name = new char[end-start+1];
				if (name) {
					strncpy(name, &(szCmdLine[start]), end-start);
					name[end-start] = 0;
					VCard32 address = CQySock::Resolve(name);
					if (address != 0) {
						// Post the IP address to the server
						gQnmRdStruct.ulCntIp  =  address;  
						//  vncService::PostAddNewClient(address);	//  2006/02/09, 这里将PostAddNewClient的动作放在窗口出来后面
					} else {
						   myLog.Print(  LL_INTERR,  "Unable to resolve host name, Add New Client Error"  );
					}
					delete [] name;
				}
				i=end;

			} 
			
			continue;
		}

		// Either the user gave the -help option or there is something odd on the cmd-line!

		break;
	};

	if  (  gQnmRdStruct.ulCntIp  )  qwmRdMain(  );	//  这里专门处理连接IP的情况，2006/02/09

	vnclog.Print(LL_STATE, "myDllMain will end, iErr is %d\n",  gQnmRdStruct.iErr  );

	iErr  =  0;

errLabel:
	
	return  iErr  ?  iErr  :  gQnmRdStruct.iErr;

}


 int qwmRdMain()
{
	int				iErr	=	-1;
	CRdMenu		*	menu	=	NULL;
	CRdAgent		server;

	// Set this process to be the last application to be shut down.
	SetProcessShutdownParameters(0x100, 0);
	
	// Check for previous instances of WinVNC!
  	vncInstHandler instancehan;
  	if (!instancehan.Init())
  	{
  		// We don't allow multiple instances!
		myLog.Print(  LL_STATE,  "Another instance is already running"  );
		goto  errLabel;
  	}

	// Set the name and port number
	server.SetName(szAppName);
	vnclog.Print(LL_STATE, VNCLOG("server created ok\n"));

	// Create tray icon & menu if we're running as an app
	menu  = new CRdMenu(&server);
	if (menu == NULL)
	{
		vnclog.Print(LL_INTERR, VNCLOG("failed to create tray menu\n"));
		PostQuitMessage(0);
		goto  errLabel;
	}


	//  2006/02/09, added by wxr
	if  (  gQnmRdStruct.ulCntIp  )  {
		CQwmRd::PostAddNewClient(  gQnmRdStruct.ulCntIp  );	//  2006/02/09, 这里将PostAddNewClient的动作放在窗口出来后面
		gQnmRdStruct.ucbStopSockReloaded  =  TRUE;
	}



	// Now enter the message handling loop until told to quit!
	MSG msg;
	while (GetMessage(&msg, NULL, 0,0) ) {
		vnclog.Print(LL_INTINFO, VNCLOG("message %d recieved\n"), msg.message);

		TranslateMessage(&msg);  // convert key ups and downs to chars
		DispatchMessage(&msg);
	}

	vnclog.Print(LL_STATE, VNCLOG("shutting down server\n"));

errLabel:

	if (menu != NULL)  delete menu;

	return  iErr  ?  iErr  :  msg.wParam;
}



