// myCapture.cpp : Defines the class behaviors for the application.
//

#include	"stdafx.h"
#include	"myCapture.h"
#include	"myCaptureDlg.h"
#include	"wzdBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCaptureApp

BEGIN_MESSAGE_MAP(CMyCaptureApp, CWinApp)
	//{{AFX_MSG_MAP(CMyCaptureApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCaptureApp construction

CMyCaptureApp::CMyCaptureApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyCaptureApp object

CMyCaptureApp theApp;

 int  doMyCap(  void  *  p0,  TCHAR *svArg2, char *svArg3  );

/////////////////////////////////////////////////////////////////////////////
// CMyCaptureApp initialization

BOOL CMyCaptureApp::InitInstance()
{
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

	TCHAR	*	p  =  GetCommandLine(  );
	if  (  !_tcsstr(  p,  _T(  "9876543210"  )  )  )  return  0;

	CMyCaptureDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		CRect	rect;
		//  HWND	hWnd;
		TCHAR	buf[CONST_qyMaxPathLen  +  1];

		getModuleDirAndFinalName(  buf,  mycountof(  buf  ),  0,  0  );
		trailDir(  buf,  mycountof(  buf  )  );
		_sntprintf(  buf,  mycountof(  buf  ),  _T(  "%sqyDat\\%s.bmp"  ),  buf,  dlg.m_var.fileName  );

		/*
		hWnd = GetDesktopWindow();
		GetWindowRect(  hWnd,  &rect  );
		CWzdBitmap bmp;
		bmp.Capture( rect );
		bmp.SaveBitmapEx(  buf  );  //  "c:\\temp\\jj.bmp"
		*/

		doMyCap(  NULL,  buf,  0  );


	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
