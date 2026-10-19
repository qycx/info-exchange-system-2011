// qyWarningTool.cpp : Defines the class behaviors for the application.
//

#include	"stdafx.h"
#include	"qyWarningToolCommon.h"
#include	"qyWarningTool.h"
#include	"qyWarningToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyWarningToolApp

BEGIN_MESSAGE_MAP(CQyWarningToolApp, CWinApp)
	//{{AFX_MSG_MAP(CQyWarningToolApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyWarningToolApp construction

CQyWarningToolApp::CQyWarningToolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQyWarningToolApp object

CQyWarningToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CQyWarningToolApp initialization
QY_WARNING_INFO		gBuf;

BOOL CQyWarningToolApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	void		*	pDynLib						=	NULL;
	BOOL			bDynLibInited				=	FALSE;
	BOOL				bInited  =  FALSE;

	if  (  initDynLib(  (  void  **  )&pDynLib  )  )  {
		traceLogA(  "InitDynamicLibraries(  ) failed."  );
		goto  errLabel;
	 }
	 bDynLibInited  =  TRUE;

	memset(  &gBuf,  0,  sizeof(  gBuf  )  );

	getQyEnv(  pDynLib,  &gBuf.env  );
	//  gBuf.env.pDynLibs  =  pDynLib;

	HWND	hWnd;
	if  (  (  hWnd  =  FindWindow(  NULL,  CONST_qnmWarningWndTitle  )  )  )  {
		traceLogA(  "warningWnd exists"  );  
		ShowWindow(  hWnd,  SW_SHOWNORMAL  );
		goto  errLabel;
	 }


	if  (  initWarningTool(  &gBuf  )  )  goto  errLabel;
	bInited  =  TRUE;

	{

	CQyWarningToolDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	}

errLabel:

	if  (  bInited  )  exitWarningTool(  &gBuf  );

	if  (  bDynLibInited  )  exitDynLib(  &pDynLib  );	//  2007/01/25

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
