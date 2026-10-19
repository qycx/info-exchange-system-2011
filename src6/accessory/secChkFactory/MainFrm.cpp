// MainFrm.cpp : implementation of the CMainFrame class
//

#include	"stdafx.h"
#include	"secChkFactory.h"
#include	"MainFrm.h"
#include	"resource.h"
#include	"secChkFactoryCommon.h"
#include	"dlgCfg.h"


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
	ON_COMMAND(ID_make, Onmake)
	ON_COMMAND(ID_qyOptions, OnqyOptions)
	ON_UPDATE_COMMAND_UI(ID_make, OnUpdatemake)
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

 int  qnmGetUpdateDataEx(  char  *  ip,  unsigned  short  port,  int  iSystemId,  char  *  mac,  char  *  data,  unsigned  int  size  )
{
	 _snprintf(  data,  size,  "%s=%s %s=%d %s=%d %s=%s                                ",  
				 			   CONST_qyCfgName_cntIp,  ip,
							   CONST_qyCfgName_cntPort,  port,
							   CONST_qyCfgName_systemId,  iSystemId,
							   CONST_qyCfgName_mac,	mac  );										
	 return  0;
} 


 int  outputSecChkTool(  char  *  tmpFileName  )
{
	 int	iErr							=  -1;
	 char	buf[128];
	 char	data[CONST_qySize_cfgs  +  1]	=	"";
	 char	xBuf[2048  +  1];
	 char	encBuf[1024  + 1];
	 unsigned  int	len;
	 unsigned  long	dataLen;


	 if  (  qyOutputResourceFile(  IDR_DATA_qrtForSecChk,  tmpFileName  )  )  goto  errLabel;

#ifndef  _DEBUG
//  #error  "must check md5 of qyRegTool"
#endif

	 _snprintf(  buf,  sizeof(  buf  ),  "%s",  "djjc"  );
	 getCurTime(  buf  +  strlen(  buf  )  );
	 dataLen  =  strlen(  buf  );	 
	 
	 len  =  sizeof(  encBuf  );
	 if  (  qnmEncData(  &gSecChkFactory.encCtx,  data,  dataLen,  encBuf,  &len  )  )  goto  errLabel;
	 qybuf2x(  encBuf,  len,  xBuf  );
	 len  =  2  *  len;
	 xBuf[len]  =  0;

	 if  (  qnmGetUpdateDataEx(  DEFAULT_qyCfgVal_cntIp,  10,  CONST_qySystemId_secChk,  xBuf,  data,  sizeof(  data  )  )  )  goto  errLabel;	 
	 if  (  !bQyUpdateImageData(  tmpFileName,  CONST_qyCfgSym_regTool,  data,  strlen(  data  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 return  iErr;

}



void CMainFrame::Onmake() 
{
	// TODO: Add your command handler code here
	char  qyRegToolDir[256]  =  "";
	
	if  (  qyGetRegCfg(   CONST_qyRootKey_qnmScheduler,  CONST_regValName_secChkFactoryDir,  qyRegToolDir,  sizeof(  qyRegToolDir  )  )  )  {
		qyRegToolDir[0]  =  0;
	}

	trim(  qyRegToolDir  );
	if  (  !qyRegToolDir[0]  )  return;
	if  (  trailDir(  qyRegToolDir,  sizeof(  qyRegToolDir  )  )  )  return;
	if  (  qyStrCat(  qyRegToolDir,  "anJian.exe",  qyRegToolDir,  sizeof(  qyRegToolDir  )  )  )  return;
	
	if  (  outputSecChkTool(  qyRegToolDir  )  )  AfxMessageBox(  "生产不成功"  );


	
}


void CMainFrame::OnqyOptions() 
{

	CDlgCfg	dlg;

	dlg.DoModal(  );
}

void CMainFrame::OnUpdatemake(CCmdUI* pCmdUI) 
{
	char  qyRegToolDir[256]  =  "";
	BOOL  bEnabled  =  FALSE;

	if  (  qyGetRegCfg(   CONST_qyRootKey_qnmScheduler,  CONST_regValName_secChkFactoryDir,  qyRegToolDir,  sizeof(  qyRegToolDir  )  )  )  {
		qyRegToolDir[0]  =  0;
	}

	trim(  qyRegToolDir  );
	if  (  qyRegToolDir[0]  )  {
		DWORD  kk;

		kk  =  GetFileAttributes(  qyRegToolDir  );
		if  (  kk  ==  0xFFFFFFFF  )  {
			traceLogA(  "配置的文件夹不存在。"  );
			goto  errLabel;			
		}
		if  (  !(  kk  &  FILE_ATTRIBUTE_DIRECTORY  )  )  {
			goto  errLabel;
		}
		bEnabled  =  TRUE;
	}


errLabel:
	pCmdUI->Enable(  bEnabled  );
}
