// MainFrm.cpp : implementation of the CMainFrame class
//

#include	"stdafx.h"
#include	"testAe.h"
#include	"qyCommon.h"
#include	"awmExtCfg.h"
#include	"MainFrm.h"
#include	"dlgInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TESTINTERMON, OnTestintermon)
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



void CMainFrame::OnTestintermon() 
{

	
	char	buf[128];

	CDatabase tmpDb;
	//  SCANNING_LOG_TAB_RCD sLTR;
	CString sqlCStr;
	// char computerInfoBuf[MAX_AWM_MON_OFFICE_NAME_LEN + MAX_AWM_MON_SUB_OFFICE_NAME_LEN + MAX_IP_ADDR_LEN + 1];
	int i = 0;
	char	timeBuf[14  +  1];
	CDlgInput	dlg;
	int			total;

	if  (  dlg.DoModal(  )  !=  IDOK  )  return;
	total  =  dlg.m_num;


	TRY {
		if ( !tmpDb.Open( DEFAULT_AWM_EXT_DSN_NAME ) ) goto errLabel;

		for  (  i  =  0;  i  <  total;  i  ++  )  {

		
			/*
			memset( &sLTR, 0, sizeof( sLTR ) );
			sprintf( sLTR.officeName, "off%03d", i % 100 );
			sprintf( sLTR.scannedIp, "203.186.10.%d", i % 100 );

			memset( computerInfoBuf, ' ', sizeof( computerInfoBuf ) - 1 );
			computerInfoBuf[sizeof( computerInfoBuf ) - 1] = 0;
			memcpy( computerInfoBuf, sLTR.officeName, strlen( sLTR.officeName ) );
			memcpy( computerInfoBuf + MAX_AWM_MON_OFFICE_NAME_LEN, sLTR.subOfficeName, strlen( sLTR.subOfficeName ) );
			memcpy( computerInfoBuf + MAX_AWM_MON_OFFICE_NAME_LEN + MAX_AWM_MON_SUB_OFFICE_NAME_LEN, sLTR.scannedIp, strlen( sLTR.scannedIp ) );
		
			*/

			_snprintf(  buf,  8,  "%d",  i  );
			getCurTime(  timeBuf  );
			sqlCStr = CString( "insert into offlineComputerLogTab( officeName, subOfficeName,ip,firstRecvdTime,lastRecvdTime )" )  
				+  " values( 'office','"  +  buf  +  "','192.192.192.192','"  +  timeBuf  +  "','"  +  timeBuf  +  "')";

			tmpDb.ExecuteSQL( sqlCStr );
			
			sprintf(  buf,  "%d records inserted.",  i + 1 );
			m_wndStatusBar.SetPaneText(  0,  buf,  TRUE  );

		}

		}
	CATCH ( CDBException, e ) {
		// debugLog(  e->m_strError.GetBuffer(  0  )  );
	}
	END_CATCH

errLabel:
	
	if  (  tmpDb.IsOpen(  )  )  tmpDb.Close( );

	return;


	

}
