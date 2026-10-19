// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "licenseTool.h"
#include "qyLicense.h"

#include "MainFrm.h"

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
	ON_COMMAND(ID_outputHardwareId, OnoutputHardwareId)
	ON_COMMAND(ID_inputLicenseParam, OninputLicenseParam)
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

 int  qwmGetPcName(  char  *  pcName,  unsigned  int  len  )
{
	 int				iErr	=	-1;

	 if  (  !GetComputerName(  pcName,  (  unsigned  long  *  )&len  )  )  goto  errLabel;		 	 
	 iErr  =  0;

errLabel:
	
	 return  iErr;
}

 static  CString  qyBrowserForFile(  BOOL bOpen,  char  *  lpszDefExt,  DWORD  dwFlags,  char  *  lpszFilter,  char  *  title,  char  *  pFileName  )
{	 
	 CString		pathCStr;
	 CFileDialog	dlg(  bOpen,  lpszDefExt  ?  lpszDefExt  :  "html",  pFileName,  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT,  lpszFilter  ?  lpszFilter  :  "Html 格式(*.html)|*.html|Excel 格式(*.xls)|*.xls||",  NULL  );

	 dlg.m_ofn.lpstrTitle  =  title  ?  title  :  "选择导出的数据文件名和格式";

	 if  (  IDOK  ==  dlg.DoModal(  )  )  {
		 pathCStr  =  dlg.GetPathName(  );
	 }
	
	 return  pathCStr;
}


void CMainFrame::OnoutputHardwareId() 
{
	CString		pathCStr;
	CString		hintCStr;
	char		fileNameBuf[32  +  1]	=  "";
	
	AfxMessageBox(  "本工具用来生成软件许可证的种子文件。"  );	

	qwmGetPcName(  fileNameBuf,  sizeof(  fileNameBuf  )  );
	pathCStr  =  qyBrowserForFile(  FALSE,  "sed",  0,  "LicenseSeed 格式(*.sed)|*.sed||",  NULL,  fileNameBuf  );
	if  (  pathCStr  ==  ""  )  goto  errLabel;	
	if  (  !bGetHardwareIdOk(  pathCStr.GetBuffer(  0  )  )  )  {
		AfxMessageBox(  "您的硬件环境不符合产品要求,请根据用户手册的规定，重新调整硬件安装环境！"  );  goto  errLabel;
	}
	hintCStr  =  CString(  "导出文件成功!请把"  )  +  pathCStr  +  "文件用zip压缩后email到经销商，以便取得软件许可证!";
	AfxMessageBox(  hintCStr  );

errLabel:

	return;

}

void CMainFrame::OninputLicenseParam() 
{
	CString		pathCStr;
	char		fileNameBuf[256  +  1]			=  "";

	AfxMessageBox(  "本工具用来导入软件许可证。"  );

	qwmGetPcName(  fileNameBuf,  sizeof(  fileNameBuf  )  );
	pathCStr  =  qyBrowserForFile(  TRUE,  "lcs",  OFN_FILEMUSTEXIST,  "License 格式(*.lcs)|*.lcs||",  "选择导入的数据文件名和格式",  fileNameBuf  );
	if  (  pathCStr  ==  ""  )  goto  errLabel;	
	if  (  !bSetChkNumOk(  pathCStr.GetBuffer(  0  )  )  )  {
		AfxMessageBox(  "导入软件许可证失败！"  );  goto  errLabel;
	}

	AfxMessageBox(  "导入软件许可证成功！"  );

errLabel:
	return;
}
