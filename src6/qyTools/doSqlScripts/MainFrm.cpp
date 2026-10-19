// MainFrm.cpp : implementation of the CMainFrame class
//

#include	"stdafx.h"
#include	"doSqlScripts.h"
#include	"MainFrm.h"

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyString.h"
#include	"qySqlFunc.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 BOOL WINAPI myIsWow64Process(  QY_ENV  *  pEnv,  HANDLE hProcess,  PBOOL Wow64Process  )
 {
	 return  FALSE;
 }

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_testIpScan, OntestIpScan)
	ON_COMMAND(ID_testSql, OntestSql)
	ON_COMMAND(ID_makeNetMcDb, OnmakeNetMcDb)
	ON_UPDATE_COMMAND_UI(ID_makeNetMcDb, OnUpdatemakeNetMcDb)
	ON_COMMAND(ID_makeNetMcTestData, OnmakeNetMcTestData)
	ON_UPDATE_COMMAND_UI(ID_makeNetMcTestData, OnUpdatemakeNetMcTestData)
	ON_COMMAND(ID_makeMsgDb, OnmakeMsgDb)
	ON_COMMAND(ID_makeMsgMgrDb, OnmakeMsgMgrDb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
 void  CMainFrame::OnmakeNetMcDb() 
{
 
int  makeDb_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  char  *  dbVer  );
extern  char	*  CONST_dsn_netMc;


	 char	*	dbTypeName  =  CONST_dbTypeName_access;
	 //  char	*	dbTypeName  =  CONST_dbTypeName_sqlServer;
	 char	*	servIp		=	"127.0.0.1";
	 char	*	uid			=	"";
	 char	*	pwd			=	"";
	 char	*	dbName		=	CONST_dsn_netMc;
	 int		iServiceId	=	CONST_qyServiceId_qwm;
	 
	 makeDb_netMc(  CString(  dbTypeName  ),  servIp,  CString(  uid  ),  CString(  pwd  ),  CString(  dbName  ),  iServiceId,  qnmDbVerStr(  iServiceId  )  );


}

 void CMainFrame::OnmakeMsgDb() 
{
	// TODO: Add your command handler code here
int  makeDb_isClient(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  int  iSystemId,  int  iAppType,  char  *  dbVer  );
extern  char	*  CONST_dsn_misClient;


	 char	*	dbTypeName  =  CONST_dbTypeName_access;
	 //  char	*	dbTypeName  =  CONST_dbTypeName_sqlServer;
	 char	*	servIp		=	"127.0.0.1";
	 char	*	uid			=	"";
	 char	*	pwd			=	"";
	 char	*	dbName		=	CONST_dsn_misClient;
	 int		iServiceId	=	CONST_qyServiceId_mis;
	 int		iSystemId	=	CONST_qySystemId_messenger;
	 int		iAppType	=	CONST_qyAppType_client;
	 
	 makeDb_isClient(  CString(  dbTypeName  ),  servIp,  CString(  uid  ),  CString(  pwd  ),  CString(  dbName  ),  iServiceId,  iSystemId,  iAppType,  qnmDbVerStr(  iServiceId  )  );
	
}

void CMainFrame::OnmakeMsgMgrDb() 
{
	// TODO: Add your command handler code here
int  makeDb_isMgr(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  int  iSystemId,  int  iAppType,  char  *  dbVer  );
extern  char	*  CONST_dsn_mis;


	 char	*	dbTypeName  =  CONST_dbTypeName_access;
	 //  char	*	dbTypeName  =  CONST_dbTypeName_sqlServer;
	 char	*	servIp		=	"127.0.0.1";
	 char	*	uid			=	"";
	 char	*	pwd			=	"";
	 char	*	dbName		=	CONST_dsn_mis;
	 int		iServiceId	=	CONST_qyServiceId_mis;
	 
	 makeDb_isMgr(  CString(  dbTypeName  ),  servIp,  CString(  uid  ),  CString(  pwd  ),  CString(  dbName  ),  iServiceId,  0,  0,  qnmDbVerStr(  iServiceId  )  );
	
}


 void CMainFrame::OnmakeNetMcTestData()
{
	  int  makeTestData_netMc(  );

	  makeTestData_netMc(  );

}





 void CMainFrame::OntestIpScan() 
{
}


void CMainFrame::OnUpdatemakeNetMcDb(CCmdUI* pCmdUI) 
{
	//  pCmdUI->Enable(  FALSE  );
}

void CMainFrame::OnUpdatemakeNetMcTestData(CCmdUI* pCmdUI) 
{
	//  pCmdUI->Enable(  FALSE  );
}

void CMainFrame::OntestSql() 
{
	// TODO: Add your command handler code here
	
}


