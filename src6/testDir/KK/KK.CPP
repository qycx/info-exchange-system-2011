// kk.cpp : Defines the class behaviors for the application.
//

#include	"stdafx.h"
#include	<lm.h>
#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"kk.h"

#include	"testFile.h"

#include	"MainFrm.h"
#include	"kkDoc.h"
#include	"kkView.h"

#include	"qyLicense.h"
#include	"testCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKkApp

BEGIN_MESSAGE_MAP(CKkApp, CWinApp)
	//{{AFX_MSG_MAP(CKkApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKkApp construction

CKkApp::CKkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKkApp object

CKkApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKkApp initialization
 
#define  CONST_kk	0
// #undef  CONST_kk

char gszOptions[]=			CONST_qyCfgSym_regTool"Startup\0"
							"S[8]:Init Cmd Net Type=TCPIO\0\0\0\0"
						    "S[48]:Init Cmd Bind Str=\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
						    "S[8]:Init Cmd Encryption=XOR\0\0\0\0\0\0"
						    "S[8]:Init Cmd Auth=NULLAUTH\0"
						    "N[0,5000000]:Idle Timeout (ms)=60000\0\0";



class CJj {
public:
	struct  {
		int  i;
	}  var;
};


class  CDd:public CJj  {
public:
	struct  {
		int  j;
	}  var1;
};

int compare( const void *arg1, const void *arg2 )
{
   /* Compare all of both strings: */
   return _stricmp( * ( char** ) arg1, * ( char** ) arg2 );
}

void  testDb(  );


class  Ck  {
public:
	Ck(  );
	virtual  void  init(  );
	int			   runAsApp(  );
};

Ck::Ck(  )  
{
}

int  Ck::runAsApp(  )
{
	Ck::init(  );
	init(  );
	return  0;

}

 void  Ck::init(  )
{
	 AfxMessageBox(  "Ck::init.  "  );
}

class  CkEx:public  Ck
{
public:
	CkEx(  );
	void  init(  );
};

CkEx::CkEx(  )
{
}
void  CkEx::init(  )
{
	AfxMessageBox(  "CkEx::init.  "  );
}

typedef  struct  __bufSize_t  {
				 unsigned  int  len;
}		 BUF_SIZE;


 VOID  qyDisplayKeyInfo(  HANDLE hKeyRoot,  CHAR *RegPath  )   
{   
	HKEY   hKey;   
	//  CHAR   Buf[LINE_LEN];   
	//  CHAR   ValueName[MAX_VALUE_NAME];   
	//  DWORD  cbValueName = MAX_VALUE_NAME;   
	DWORD  retCode;   
	CHAR   ClassName[MAX_PATH];   
	DWORD  dwcClassLen = MAX_PATH;   
	DWORD  dwcSubKeys;   
	DWORD  dwcMaxSubKey;   
	DWORD  dwcMaxClass;   
	DWORD  dwcValues;   
	DWORD  dwcMaxValueName;   
	DWORD  dwcMaxValueData;   
	DWORD  dwcSecDesc;   
	FILETIME  ftLastWriteTime;     
	 
	retCode  =  RegOpenKeyEx(	(  HKEY  )hKeyRoot,    // Key handle at root level.                           
								RegPath,     // Path name of child key.                           
								0,           // Reserved.                           
								KEY_EXECUTE, // Requesting read access.                           
								&hKey  );      // Address of key to be returned.    
	if (retCode)     {     
		traceLogA(  "RegOpenKeyEx failed."  );
		return;     
	}  
	// ADD A QUERY AND ALLOCATE A BUFFER FOR BDATA.    
	retCode =   RegQueryInfoKey (	hKey,              // Key handle.     
		
					ClassName,         // Buffer for class name.                    
					&dwcClassLen,      // Length of class string.                    
					NULL,              // Reserved.                    
					&dwcSubKeys,       // Number of sub keys.                    
					&dwcMaxSubKey,     // Longest sub key size.                    
					&dwcMaxClass,      // Longest class string.                    
					&dwcValues,        // Number of values for this key.                    
					&dwcMaxValueName,  // Longest Value name.                    
					&dwcMaxValueData,  // Longest Value data.                    
					&dwcSecDesc,       // Security descriptor.                    
					&ftLastWriteTime); // Last write time.     
	if (retCode)     {     
		traceLogA(  "RegQueryInfoKey failed."  );
		return;
	}
	
	return;
	
}


 int  testGetFile(  )
{
	 int			iErr  =  -1;
	 FILE		*	fpIn  =  NULL,  *	fpOut  =  NULL;
	 char			fileName[256]	=	"c:\\temp\\notepad.exe";
	 char			fileName1[256]  =	"c:\\temp\\1.exe";
	 unsigned  int  len;
	 char			dataBuf[4096];
	 int			fileSize;
 
	 fileSize  =  qyGetFileSize(  fileName  );
	 if  (  fileSize  <  0  )  goto  errLabel;

 	 if  (  !(  fpIn  =  fopen(  fileName,  "rb"  )  )  )  {
		 traceLogA(  "fopen failed."  );
		 goto  errLabel;
	 }
	 fpOut  =  fopen(  fileName1,  "wb"  );
	 if  (  !fpOut  )  goto  errLabel;

	 for  (  ;  fileSize  >  0;  )  {
		  len  =  sizeof(  dataBuf  );
		  if  (  fileSize  <  (  int  )len  )  len  =  fileSize;		
		  if  (  fread(  dataBuf,  len,  1,  fpIn  )  !=  1  )  goto  errLabel;
		  if  (  fwrite(  dataBuf,  len,  1,  fpOut  )  !=  1  )  goto  errLabel;		  
		  fileSize  -=  len;
	 }

	 iErr  =  0;

errLabel:

	 if  (  fpIn  )  fclose(  fpIn  );
	 if  (  fpOut  )  fclose(  fpOut  );
	 return  iErr;
}

 CDatabase	gDb;


BOOL CKkApp::InitInstance()
{

	char  buf[1024]  =  "err";

	
//  errLabel:
	
	//  CkEx  tmpObj;

	//  tmpObj.runAsApp(  );

	/*
	int  i;
	char  *  buf0  =  "123";
	char  *  buf1  =  "012";
	char  *argv[]  =  {  buf0,  buf1  };
	int  argc  =  2;
	
	qsort( (void *)argv, (size_t)argc, sizeof( char * ), compare );

   // Output sorted list:
   for( i = 0; i < argc; ++i )
      printf( "%s ", argv[i] );
   printf( "\n" );
   */

	//  testDb(  );
	


	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	if  ( qyInitSnmp(  &ghDll_InetMib1  )  )  goto errLabel;
	
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

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CKkDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CKkView));
	AddDocTemplate(pDocTemplate);

	{
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	}

	memset(  &gBuf,  0,  sizeof(  gBuf  )  );
	/*
	if  (  gDb.Open(  "testDsn"  )  )  {
		gBuf.pDb  =  &gDb;
		gBuf.bDbOpen  =  TRUE;
	}
	*/

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();


errLabel:
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CKkApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CKkApp message handlers


void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CAboutDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
}

int CKkApp::ExitInstance() 
{

	if  (  gBuf.bDbOpen  )  {
		gDb.Close(  );  gBuf.bDbOpen  =  FALSE;
	}
	memset(  &gBuf,  0,  sizeof(  gBuf  )  );

	if  (  ghDll_InetMib1  )  qyExitSnmp(  &ghDll_InetMib1  );

	return CWinApp::ExitInstance();
}
