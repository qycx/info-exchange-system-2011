// qyMc.cpp : Defines the class behaviors for the application.
//
 
#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyMc.h"
#include	"qyMcDoc.h"
#include	"leftView.h"
//  #include	"qyDialogBar.h"
#include	"mainClient.h"
#include	"MainFrm.h"
#include	"ChildFrm.h"
#include	"qyMcRootChildFrm.h"
#include	"qyChildFrm.h"
//  #include	"webBrowser2.h"
#include	"qyMcView.h"
#include	"qyBrowseView.h"
#include	"qyVirtualListView.h"
#include	"dlgMcLogon.h"
#include	"splash.h"
//
#include	"qyCusResTemp.h"

#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
	extern  IDispatch		*	gpDispOM;
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyMcApp

BEGIN_MESSAGE_MAP(CQyMcApp, CWinApp)
	//{{AFX_MSG_MAP(CQyMcApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyMcApp construction

CQyMcApp::CQyMcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	memset( &this->var, 0, sizeof( this->var ) );
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQyMcApp object

CQyMcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CQyMcApp initialization



BOOL CQyMcApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.

	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxOleInit(  );					//  2007/05/24
	
	InitCommonControls();			// added by wxr on 2002/08/15

	#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
	CCustomOccManager  *  pMgr  =  new  CCustomOccManager;	
	gpDispOM  =  new  CImpIDispatch;

	AfxEnableControlContainer(  pMgr  );
	#endif
	
	HINSTANCE	g_hInst	=	NULL;
	g_hInst  =  AfxGetInstanceHandle(  );


	if  (  initQyMc(  g_hInst  )  )   return  FALSE;
   
	//  2013/01/15
	if  (  bAppClient(  g_pQyMc->iAppType  )  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "failed: iAppType is client"  )  );
		#endif
		return  FALSE;
	}


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

	CMultiDocTemplate * pRootListDocTemplate = NULL;
	pRootListDocTemplate = new CMultiDocTemplate( 
		IDR_DOCTYPE_QYMC,
		RUNTIME_CLASS( CQyMcDoc ),
		RUNTIME_CLASS( CQyMcRootChildFrm ),
		RUNTIME_CLASS( CLeftView ) );
	this->var.m_pMcRootListTemplate = pRootListDocTemplate;

	CMultiDocTemplate * p2ViewDocTemplate = NULL;
	p2ViewDocTemplate = new CMultiDocTemplate(
		IDR_DOCTYPE_QYMC,
		RUNTIME_CLASS( CQyMcDoc ),
		RUNTIME_CLASS( CChildFrame ),			//  custom MDI child frame
		RUNTIME_CLASS( CQyMcView ) );		
	this->var.m_pMc2ViewTemplate = p2ViewDocTemplate;
	
	CMultiDocTemplate  *  pTreeDocTemplate	=	NULL;	//  2007/09/14
	pTreeDocTemplate  =  new  CMultiDocTemplate(
		IDR_DOCTYPE_QYMC,
		RUNTIME_CLASS( CQyMcDoc ),
		RUNTIME_CLASS( CQyChildFrm ),
		RUNTIME_CLASS( CLeftView ) );
	this->var.m_pMcTreeTemplate = pTreeDocTemplate;

	CMultiDocTemplate * pDocTemplate = NULL;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DOCTYPE_QYMC,
		RUNTIME_CLASS( CQyMcDoc ),
		RUNTIME_CLASS( CQyChildFrm ),			
		RUNTIME_CLASS( CQyMcView ) );		
	AddDocTemplate( pDocTemplate );
	this->var.m_pMcTemplate = pDocTemplate;
		
	CMultiDocTemplate * pWebDocTemplate = NULL;
	pWebDocTemplate = new CMultiDocTemplate(
		IDR_DOCTYPE_QYMC,
		RUNTIME_CLASS( CQyMcDoc ),
		RUNTIME_CLASS( CQyChildFrm ),
		RUNTIME_CLASS( CQyBrowseView ) );
	this->var.m_pMcWebTemplate = pWebDocTemplate;

	CMultiDocTemplate * pDbDocTemplate = NULL;
	pDbDocTemplate = new CMultiDocTemplate(
		IDR_DOCTYPE_QYMC,
		RUNTIME_CLASS( CQyMcDoc ),
		RUNTIME_CLASS( CQyChildFrm ),
		RUNTIME_CLASS( CQyVirtualListView ) );
	this->var.m_pMcDbTemplate = pDbDocTemplate;

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//
	if ( CCommandLineInfo::FileNew == cmdInfo.m_nShellCommand )
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//  if  (  !this->bInitApperance(  )  )  return  FALSE;

	if  (  g_pQyMc->gui.ucbNotSplashed  )  {	//  2005/11/06
		
		//  if  (  !bQyMcLogon(  &gQyMc  )  )  return  FALSE;

		//  pMainFrame->CenterWindow(  );
		//  pMainFrame->ShowWindow(m_nCmdShow);
		//  pMainFrame->UpdateWindow();

		if  (  qyShowMainWnd(  pMainFrame->m_hWnd,  &pMainFrame->var  )  )  return  FALSE;

	}

	//  int				iRet	=	-1;
	//  CDlgMcLogon		dlg;

	//  if  (  pQyMc->gui.bLogon  )  {
	// 		if  (  !bOpenRootDoc(  )  )  return FALSE;
	//	}
	
	// The main window has been initialized, so show and update it.
	//  pMainFrame->CenterWindow(  );
	//  pMainFrame->ShowWindow(m_nCmdShow);
	//  pMainFrame->UpdateWindow();

	return TRUE;

}



 int CQyMcApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	 debugLog( "ExitInstance( ) enters." );


	 if  (  var.m_pMcDbTemplate  )  {  delete  var.m_pMcDbTemplate;  var.m_pMcDbTemplate  =  NULL;  }
	 if  (  var.m_pMcWebTemplate )  {  delete  var.m_pMcWebTemplate;   var.m_pMcWebTemplate = NULL;  }
	 if  (  var.m_pMcTreeTemplate  )  {  delete  var.m_pMcTreeTemplate;  var.m_pMcTreeTemplate  =  NULL;  }
	 if  (  var.m_pMc2ViewTemplate  )  {  delete  var.m_pMc2ViewTemplate;  var.m_pMc2ViewTemplate  =  NULL;  }
	 if  (  var.m_pMcRootListTemplate  )  {  delete  var.m_pMcRootListTemplate;  var.m_pMcRootListTemplate = NULL;  }


	 //
	exitQyMc( );

	#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
	if  (  	gpDispOM  )  {
		delete  gpDispOM;  gpDispOM  =  NULL;
	}
	#endif
	debugLog( "ExitInstance( ) leaves." );

	return CWinApp::ExitInstance();
}






/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg(CWnd* pParent = NULL);

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
public:
//	afx_msg void Onstartsharescreen();
//	afx_msg void OnUpdatestartsharescreen(CCmdUI *pCmdUI);
	afx_msg void OnStnClickedStaticqycxcopyright();
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg(CWnd* pParent /*= NULL*/) : CDialog(CAboutDlg::IDD,pParent)
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
//	ON_COMMAND(ID_startShareScreen, Onstartsharescreen)
//	ON_UPDATE_COMMAND_UI(ID_startShareScreen, OnUpdatestartsharescreen)
ON_STN_CLICKED(IDC_STATIC_qycxCopyRight, OnStnClickedStaticqycxcopyright)
ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

int  myOnAppAbout(  HWND  hParent  )
{
	CWnd  *  pParent  =  CWnd::FromHandle(  hParent  );

	CAboutDlg aboutDlg(  pParent  );
	aboutDlg.DoModal();

	return  0;
}

// App command to run the dialog
void CQyMcApp::OnAppAbout()
{
	myOnAppAbout(  NULL  );
}

/////////////////////////////////////////////////////////////////////////////
// CQyMcApp message handlers

//  菜单执行命令


 BOOL  CQyMcApp::bOpenRootDoc(  )
{
	 traceLogA(  "bOpenRootDoc 未实现"  );
	 return  FALSE;
}

 // 判断管理是否打开	
 int CQyMcApp::enumAllDocs(  PF_commonHandler  pf,  COMMON_PARAM  *  p0,  BOOL  *  pbStop  )
{	 
	 CMultiDocTemplate	*	pDocTemplate  =  NULL;
	 
	 if  (  !pf  )  return  -1;

	 for  (  int  i  =  0;  ;  i  ++  )  {
		  switch  (  i  )  {
				  case  0:  pDocTemplate  =  var.m_pMcRootListTemplate;  break;
				  case  1:  pDocTemplate  =  var.m_pMcDbTemplate;  break;
				  case  2:  pDocTemplate  =  var.m_pMcTemplate;  break;
				  case  3:  pDocTemplate  =  var.m_pMcWebTemplate;  break;
				  case  4:  pDocTemplate  =  var.m_pMcTreeTemplate;  break;
				  default:  goto  errLabel;
		  }
			  
		  POSITION  docPos  =  pDocTemplate->GetFirstDocPosition( );
		  while  (  docPos !=  NULL )  {
				 CQyMcDoc	*	pDoc  =  (  CQyMcDoc *  )pDocTemplate->GetNextDoc(  docPos  );
				 if  (  pf  )  pf(  p0,  pDoc,  pbStop  );
				 if  (  pbStop  &&  *pbStop  )  goto  errLabel;
	 	  }
	 }
		
errLabel:
	 return  0;
		 
}

 
 //  注意：这里的错误清除工作可能不正确
 BOOL CQyMcApp::bNewMcView(  void  *  pSelParam  )
{
	BOOL					bRet			=	FALSE;
	QY_MC_SEL			*	pSel			=	(  QY_MC_SEL  *  )pSelParam;
	CQyMcDoc			*	tmppDoc			=	NULL;
	CFrameWnd			*	tmppFrame		=	NULL;
	CMultiDocTemplate	*	pDocTemplate	=	NULL;
	//
	QY_MC				*	pQyMc			=			QY_GET_GBUF(  );

	if  (  !pSel  ||  pSel->type  !=  CONST_qySelType_mcView  )  goto  errLabel;
	
	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		traceLogA(  "这里，暂时采用放大主界面的方式，来打开查询框，因为查询框在缩小时。不好看。等有时间改进。2007/07/31"  );
		AfxGetMainWnd(  )->ShowWindow(  SW_SHOWMAXIMIZED  );
	}

	pDocTemplate  =  this->var.m_pMcTemplate;
	tmppDoc = ( CQyMcDoc * )pDocTemplate->CreateNewDocument( );
	if ( !tmppDoc )		goto errLabel;
	if  (  !tmppDoc->bSetQyMcDoc(  pSel  )  )	goto  errLabel;
	
	tmppFrame = pDocTemplate->CreateNewFrame( tmppDoc, NULL );
	if ( !tmppFrame )	goto errLabel;
	tmppFrame->SetWindowText(  tmppDoc->GetTitle(  )  );
	pDocTemplate->InitialUpdateFrame( tmppFrame, tmppDoc );
	
	bRet	=	TRUE;

errLabel:

	if  (  !bRet  )  {
		if  (  tmppFrame  )  tmppFrame->PostMessage(  WM_CLOSE  );
		else  if  (  tmppDoc  )  {
				  pDocTemplate->RemoveDocument(  tmppDoc  );
				  delete  tmppDoc;
		}
	}

	return	bRet;
	
}



 BOOL CQyMcApp::bNewWebView( void * pSelParam )
{
	BOOL					bRet			=			FALSE;
	QY_MC_SEL			*	pSel			=			(  QY_MC_SEL  *  )pSelParam;
	QY_MC_DOCINFO			tmpDocInfo;
	CQyMcDoc			*	tmppDoc			=			NULL;
	CFrameWnd			*	tmppFrame		=			NULL;
	CMultiDocTemplate	*	pDocTemplate	=			this->var.m_pMcWebTemplate;

	memset(  &tmpDocInfo,  0,  sizeof(  tmpDocInfo  )  );

	if  (  pSel->type  ==  QY_SELTYPE_MCBARLOG  )  {
		if  (  !strlen(  pSel->u.barLog.url  )  )  goto  errLabel;
		tmpDocInfo.iDocType			=		QY_DOCTYPE_MCWEB;
		safeStrNCpy( pSel->u.barLog.url, tmpDocInfo.u.web.url, sizeof( tmpDocInfo.u.web.url ) );
		}
	else
			goto  errLabel;
	

	tmppDoc = ( CQyMcDoc * )pDocTemplate->CreateNewDocument( );
	if  (  !tmppDoc )			goto  errLabel;
	if  (  !tmppDoc->bSetQyMcDoc(  &tmpDocInfo  )  )	goto  errLabel;
			
	tmppFrame = pDocTemplate->CreateNewFrame( tmppDoc, NULL );
	if ( !tmppFrame )			goto errLabel;
	tmppFrame->SetWindowText(  tmppDoc->GetTitle(  )  );
	pDocTemplate->InitialUpdateFrame( tmppFrame, tmppDoc );

	bRet  =  TRUE;

errLabel:

	if  (  !bRet  )  {
		if ( tmppFrame )  tmppFrame->PostMessage( WM_CLOSE );
		else if ( tmppDoc  )  {
			pDocTemplate->RemoveDocument( tmppDoc );
			delete  tmppDoc;
		}
	}

	return  bRet;

}

  BOOL CQyMcApp::bNewQueryView( void * pSelParam )
{
	BOOL					bRet			=			FALSE;
	QY_MC_SEL			*	pSel			=			(  QY_MC_SEL  *  )pSelParam;
	CQyMcDoc			*	tmppDoc			=			NULL;
	CFrameWnd			*	tmppFrame		=			NULL;
	CMultiDocTemplate	*	pDocTemplate	=			this->var.m_pMcDbTemplate;
	//
	QY_MC				*	pQyMc			=			QY_GET_GBUF(  );
	
	if  (  !pSel  )  goto  errLabel;
	if  (  pSel->type  !=  CONST_qySelType_mcQuery  )  goto  errLabel;
	if  (  !pSel->u.query.selectPart[0]  ||  !pSel->u.query.fromPart  )  goto  errLabel;

	
	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		traceLogA(  "这里，暂时采用放大主界面的方式，来打开查询框，因为查询框在缩小时。不好看。等有时间改进。2007/07/31"  );
		AfxGetMainWnd(  )->ShowWindow(  SW_SHOWMAXIMIZED  );
	}

	tmppDoc = ( CQyMcDoc * )pDocTemplate->CreateNewDocument( );
	if  (  !tmppDoc )			goto  errLabel;
	if  (  !tmppDoc->bSetQyMcDoc(  pSel  )  )	goto  errLabel;
			
	tmppFrame = pDocTemplate->CreateNewFrame( tmppDoc, NULL );
	if ( !tmppFrame )			goto errLabel;
	tmppFrame->SetWindowText(  tmppDoc->GetTitle(  )  );
	pDocTemplate->InitialUpdateFrame( tmppFrame, tmppDoc );

	pSel->u.query.hFrame  =  tmppFrame->m_hWnd;		//  2009/09/03

	bRet  =  TRUE;

errLabel:

	if  (  !bRet  )  {
		if  (  tmppFrame  )  tmppFrame->PostMessage( WM_CLOSE );
		else  if  (  tmppDoc  )  {
				  pDocTemplate->RemoveDocument( tmppDoc );
				  delete  tmppDoc;
		}
	}

	return  bRet;

}


 BOOL  CQyMcApp::bNewTreeView(  void  *  pSelParam  )
{
	BOOL					bRet			=	FALSE;
	QY_MC_SEL			*	pSel			=	(  QY_MC_SEL  *  )pSelParam;
	CQyMcDoc			*	tmppDoc			=	NULL;
	CFrameWnd			*	tmppFrame		=	NULL;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	CMultiDocTemplate	*	pDocTemplate	=	this->var.m_pMcTreeTemplate;
	TCHAR					titleBuf[256]	=	_T(  ""  );
	CWaitCursor				waitCursor;
	QY_OBJ_DB			*	pObjDb			=	NULL;

	if  (  !pSel  )  goto  errLabel;
	if  (  pSel->type  !=  QY_SELTYPE_MCROOTTREE  )  goto  errLabel;
	pObjDb  =  getProcedObjDb(  0,  pSel->u.rootTree.iDsnIndex  );
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	tmppDoc  =  (  CQyMcDoc  *  )pDocTemplate->CreateNewDocument(  );
	if  (  !tmppDoc  )		goto errLabel;
	if  (  !tmppDoc->bSetQyMcDoc(  pSel  )  )	goto  errLabel;
	
	_sntprintf(  titleBuf,  mycountof(  titleBuf  ),  _T(  "%s%s%s%s%s"  ),  pObjDb->cfg.sysName,  pObjDb->cfg.sysName[0]  ?  _T(  " : "  )  :  _T(  ""  ),  pSel->u.rootTree.preDocName,  pSel->u.rootTree.docName,  pSel->u.rootTree.postDocName  );
	tmppDoc->SetTitle(  CString(  titleBuf  )  );
	tmppFrame  =  pDocTemplate->CreateNewFrame(  tmppDoc,  NULL  );
	if  (  !tmppFrame  )  goto  errLabel;
	tmppFrame->SetWindowText(  CString(  titleBuf  )  );
	pDocTemplate->InitialUpdateFrame(  tmppFrame,  tmppDoc  );
			
	bRet	=	TRUE;

errLabel:

	if  (  !bRet  )  {
		if  (  tmppFrame  )  {
			tmppFrame->PostMessage(  WM_CLOSE  );
		}
		else  if  (  tmppDoc  )  {
				  pDocTemplate->RemoveDocument(  tmppDoc  );
				  delete  tmppDoc;
		}
	}

	return	bRet;
	
}



 BOOL  CQyMcApp::bNewTreeListView(  void  *  pSelParam  )
{
	BOOL					bRet			=	FALSE;
	QY_MC_SEL			*	pSel			=	(  QY_MC_SEL  *  )pSelParam;
	CQyMcDoc			*	tmppDoc			=	NULL;
	CFrameWnd			*	tmppFrame		=	NULL;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	CMultiDocTemplate	*	pDocTemplate	=	this->var.m_pMcRootListTemplate;
	TCHAR					titleBuf[256]	=	_T(  ""  );
	CWaitCursor				waitCursor;
	QY_OBJ_DB			*	pObjDb			=	NULL;

	if  (  !pSel  )  goto  errLabel;
	if  (  pSel->type  !=  QY_SELTYPE_MCROOTTREE  )  goto  errLabel;
	pObjDb  =  getProcedObjDb(  0,  pSel->u.rootTree.iDsnIndex  );
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	tmppDoc  =  (  CQyMcDoc  *  )pDocTemplate->CreateNewDocument(  );
	if  (  !tmppDoc  )		goto errLabel;
	if  (  !tmppDoc->bSetQyMcDoc(  pSel  )  )	goto  errLabel;
	
	_sntprintf(  titleBuf,  mycountof(  titleBuf  ),  _T(  "%s%s%s%s%s"  ),  pObjDb->cfg.sysName,  pObjDb->cfg.sysName[0]  ?  _T(  " : "  )  :  _T(  ""  ),  pSel->u.rootTree.preDocName,  pSel->u.rootTree.docName,  pSel->u.rootTree.postDocName  );
	tmppDoc->SetTitle(  CString(  titleBuf  )  );
	tmppFrame  =  pDocTemplate->CreateNewFrame(  tmppDoc,  NULL  );
	if  (  !tmppFrame  )  goto  errLabel;
	tmppFrame->SetWindowText(  CString(  titleBuf  )  );
	pDocTemplate->InitialUpdateFrame(  tmppFrame,  tmppDoc  );
	if  (  pSel->u.rootTree.ucbSetFocusOnRightView  )  {
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_setFocusOnRightView;
		tmppFrame->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
	}
			
	bRet	=	TRUE;

errLabel:

	if  (  !bRet  )  {
		if  (  tmppFrame  )  {
			tmppFrame->PostMessage(  WM_CLOSE  );
		}
		else  if  (  tmppDoc  )  {
				  pDocTemplate->RemoveDocument(  tmppDoc  );
				  delete  tmppDoc;
		}
	}

	return	bRet;
	
}


 BOOL  bQyMcNewMcView(  QY_MC_SEL  *  pSel  )
{
	 CQyMcApp	*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );

	 return  pApp->bNewMcView(  pSel  );
}

 BOOL  bQyMcNewWebView(  QY_MC_SEL  *  pSel  )
{
	CQyMcApp	*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	
	return  pApp->bNewWebView(  pSel  );
}

// 这里返回的tmphInst不知要不要用CloseHandle关闭
 BOOL  bQyMcNewIe(  QY_MC_SEL  *  pSel  )
{
	BOOL		bRet		=	FALSE;
	HINSTANCE	tmphInst	=	NULL;
	CString		urlCStr;
	char		httpHintBuf[16]	=	"http://";


	if  (  pSel->type !=  QY_SELTYPE_MCBARLOG  )   goto  errLabel;
	if  (  !pSel->u.barLog.url[0]  )			goto  errLabel;
	if  (  _strnicmp( pSel->u.barLog.url,  httpHintBuf,  strlen(  httpHintBuf  )  )  )
		urlCStr	=	CString(  "http://"  )  + pSel->u.barLog.url;
	else
		urlCStr =   CString( pSel->u.barLog.url );
	tmphInst = ShellExecute(  NULL,  _T(  "Open"  ), urlCStr,  _T(  ""  ),  _T(  ""  ), 1  );
	if ( tmphInst <= ( HINSTANCE )32 ) {
		debugLog(  "bQyMcNewIe(  ):  ShellExecute(  ) returns eror: %d.", tmphInst  );
	}
	bRet	=	TRUE;

errLabel:

	return  TRUE;

}

 BOOL  bQyMcNewQueryView(  QY_MC_SEL  *  pSel  )
{
	CQyMcApp	*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	
	return  pApp->bNewQueryView(  pSel  );
}

 BOOL  bQyMcNewTreeView(  QY_MC_SEL  *  pSel  )
{
	 CQyMcApp  *  pApp  =  (  CQyMcApp  *  )AfxGetApp(  );
	 return  pApp->bNewTreeView(  pSel  );
}

 BOOL  bQyMcNewTreeListView(  QY_MC_SEL  *  pSel  )
{
	 CQyMcApp  *  pApp  =  (  CQyMcApp  *  )AfxGetApp(  );
	 return  pApp->bNewTreeListView(  pSel  );
}

 int  enumAllDocs(  PF_commonHandler  pf,  COMMON_PARAM  *  p0,  BOOL  *  pbStop  )
{
	 CQyMcApp  *  pApp  =  (  CQyMcApp  *  )AfxGetApp(  );
	 return  pApp->enumAllDocs(  pf,  p0,  pbStop  );
}

 void  CQyMcApp::refreshDocTemplate(  void  *  pDocTemplateParam  )
{
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 CMultiDocTemplate	*	pDocTemplate	=			(  CMultiDocTemplate  *  )pDocTemplateParam;


	 POSITION docPos = pDocTemplate->GetFirstDocPosition( );
	 while  (  docPos !=  NULL )  {
			CQyMcDoc	*	pDoc  =  (  CQyMcDoc *  )pDocTemplate->GetNextDoc(  docPos  );
			pDoc->bRefreshData(  );
			pDoc->UpdateAllViews(  NULL  );			
	 }
		
}

 void  CQyMcApp::refreshAll(  )
{
	 CWaitCursor  waitCursor;

	 refreshDocTemplate(  this->var.m_pMcRootListTemplate  );
	 //  refreshDocTemplate(  var.m_pMc2ViewTemplate  );
	 refreshDocTemplate(  var.m_pMcTreeTemplate  );
	 refreshDocTemplate(  this->var.m_pMcTemplate  );
	 refreshDocTemplate(  this->var.m_pMcWebTemplate  );
	 refreshDocTemplate(  this->var.m_pMcDbTemplate  );


}


 void  qyMcRefreshAll(  )
{
 	CQyMcApp	*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	
	pApp->refreshAll(  );
	return;
}
 
 



BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	dlgAbout_OnInitDialog_qyMc(  m_hWnd,  this->IDD  );

	return  TRUE;
}

#include "Splash.h"
BOOL CQyMcApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

//void CAboutDlg::Onstartsharescreen()
//{
//	// TODO: 在此添加命令处理程序代码
//}

//void CAboutDlg::OnUpdatestartsharescreen(CCmdUI *pCmdUI)
//{
//	// TODO: 在此添加命令更新用户界面处理程序代码
//}

void CAboutDlg::OnStnClickedStaticqycxcopyright()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
