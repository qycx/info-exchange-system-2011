// MainFrm.cpp : implementation of the CMainFrame class
//
#include    "windows.h"
#include	"stdafx.h"
#include	<LMCONS.H>
#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
//  #include	"qyCommProcPublic.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCustom.h"
#include	"qyLicense.h"

#include	"qyEncCommon.h"




#include	"kk.h"
#include	"MainFrm.h"
#include	"dlgTest.h"
#include	"ps.h"
#include	"testp1.h"
#include	"testP2.h"
#include	"testP3.h"
#include	"testPs.h"
#include	"ppStatus.h"
#include	"dlgTestQnm.h"
#include	"dlgPassword.h"

#include	"ras.h"
#include	<raserror.h> 

//  加密狗 
// #include "stdafx.h" 
#include "spromeps.h" // rainbow API的头文件
#include <stdio.h>



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
	ON_COMMAND(IDC_phbk, Onphbk)
	ON_COMMAND(ID_dog, Ondog)
	ON_COMMAND(ID_testLicense, OntestLicense)
	ON_COMMAND(ID_testProductId, OntestProductId)
	ON_COMMAND(ID_calcChkNum, OnCalcChkNum)
	ON_COMMAND(ID_setChkNum, OnsetChkNum)
	ON_COMMAND(ID_checkLicense, OncheckLicense)
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


 BOOL testPhoneBk(  )
{
	BOOL  bRet    =  FALSE;
    LPRASENTRYNAME lpRasEntry;
    LPRASENTRYNAME lpTemp;
    DWORD cbBuf;
    DWORD cEntry;
    DWORD dwRet;
    UINT  ndx;
    char  szMessage[256];

    cbBuf = sizeof(RASENTRYNAME);

    if  (  (  lpRasEntry  =  (  LPRASENTRYNAME  )malloc(  (  UINT  )cbBuf  )  )  ==  NULL  )  goto  errLabel;

	lpRasEntry->dwSize = sizeof(RASENTRYNAME);
    dwRet = RasEnumEntries( NULL, NULL, lpRasEntry, &cbBuf, &cEntry );
    if ( dwRet == ERROR_BUFFER_TOO_SMALL )
    {
		if (  (  lpTemp  =  (  LPRASENTRYNAME  ) malloc(  (  UINT  )cbBuf  )  )  !=  NULL  )  {
			lpRasEntry = lpTemp;
			dwRet = RasEnumEntries( NULL, NULL, lpRasEntry, &cbBuf, &cEntry );
			free(  lpTemp  );
		}
        else
        {        
			dwRet = ERROR_NOT_ENOUGH_MEMORY;
        }

    }
    else if ( dwRet != 0 ) // other error
    {
        if ( RasGetErrorString( (UINT)dwRet, szMessage, 256 ) != 0 )
			wsprintf( (LPSTR)szMessage, "Undefined RasEnumEntries Error." );

            //  MessageBox(hdlg, (LPSTR)szMessage, szAppName, MB_OK | MB_ICONSTOP );
    }

    if ( dwRet == 0 )  // No errors
    {
        for ( ndx = 0; ndx < cEntry; ndx++ ) 
            //  SendDlgItemMessage( hdlg,
            //                      IDL_ENTRY,
            //                      LB_ADDSTRING,
            //                      0,
            //                      (LPARAM)(LPCSTR) lpRasEntry[ndx].szEntryName);
		
		traceLogA(  "  the lpRasEntry[%d].szEntryName  is  %s  ",  ndx,  lpRasEntry[ndx].szEntryName  );  


        //  if ( ndx > 0 ) // at least one item was added
        //  {
        //      SendDlgItemMessage( hdlg, IDL_ENTRY, LB_SETCURSEL, 0, 1L );
        //      EnableWindow( GetDlgItem( hdlg, IDB_DIAL ), TRUE );
        //  }
    }

	bRet = TRUE; 

errLabel:
	if  (  lpRasEntry  )  free(  lpRasEntry  );

	return bRet; 
}

void CMainFrame::Onphbk() 
{
	// TODO: Add your command handler code here
	testPhoneBk(  );
	AfxMessageBox(  "Ok"  );	
}

//Rainbow 公司 SuperPro 加密锁示范例程

//  #include "stdafx.h" 
//  #include "spromeps.h" // rainbow API的头文件
//  #include <stdio.h>

int APIENTRY iiWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{	
	SP_STATUS	spStatus;
	RB_SPRO_APIPACKET     ApiPacket;//Rainbow 所定义的数据结构
	static   RB_DWORD  qResult32;	
	spStatus = RNBOsproFormatPacket( ApiPacket, sizeof(ApiPacket) );//初始化数据结构（仅Win32程序使用） 
	spStatus = RNBOsproInitialize( ApiPacket );//初始化函数
	RB_WORD  developerID=0xF278;//开发者ID号
	//注：这里所提到的ID号均为16进制数	
	spStatus = RNBOsproFindFirstUnit( ApiPacket,developerID );//找到Developer ID指定加密锁
	//									         ▲▲▲ 
	//									       加密琐的ID号 

	if ( spStatus != 0 )//Findfirst返回值为0，代表找到加密锁，其他代表未找到加密锁，详细信息请参阅API手册
                   {
		   MessageBox( NULL,"找不到加密锁",
                                   "加密锁",
                                   MB_ICONINFORMATION | MB_TASKMODAL );
                       
                       return( FALSE );//未发现加密锁，非法用户，退出
                   }
                   else
                   {
                       MessageBox( NULL,
                                   "找到加密锁",
                                   "加密锁",
                                   MB_ICONINFORMATION | MB_TASKMODAL );
                       
                   }//找到加密锁，合法用户，程序继续运行

//"B1A8E011"(查询串),  "C7C1312A"(响应串)   Rainbow Wizard所生成的数据 
	unsigned char queryData[]={0xB1,0xA8,0xE0,0x11};//欲查询数据	
	unsigned char cmpqueryData[]={0xC6,0x6C,0xF4,0xE5};//响应数据
	unsigned char response[]={0,0,0,0};				
	int cellAddress =0x12;//设置查询单元号
	int queryLength	=4;//设置查询数据长度
	spStatus = RNBOsproQuery( ApiPacket,     //Apipacket为 Rainbow公司保留数据结构
                             cellAddress,    //查询单元号
                             &queryData,     //查询数据(输入加密锁的数据)
                             &response,      //响应数据(经加密锁计算返回数据)
                             &qResult32,     //qResult32为 Rainbow公司保留数据结构
                             queryLength );  //查询数据长度

	spStatus= memcmp( response, cmpqueryData, 4 );	//比较响应数据和预知数据

	if ( spStatus != 0 )//比较后返回值为0，代表查询响应正确，其他代表不正确，详细信息请参阅API手册
                   {
		   MessageBox( NULL,"查询不成功",
                                   "查询结果",
                                   MB_ICONINFORMATION | MB_TASKMODAL );
                       
                       return( FALSE );//查询响应不正确，非法用户，程序退出
                   }
                   else
                   {					   
                       MessageBox( NULL,
                                   "查询成功",
                                   "查询结果",
                                   MB_ICONINFORMATION | MB_TASKMODAL );                       					   					
                   }//查询响应正确, 合法用户,程序继续运行
	return 0;
}





 int  initRnbDog(  );
 BOOL  bQyDogOk(  );
 int  flg;

BOOL CMainFrame::Ondog() 
{
	// TODO: Add your command handler code here
	int		i	=	0;
	
	if  (  initRnbDog(  )  )  {
		AfxMessageBox(  "初始化失败"  );  goto  errLabel;

	}

	for  (  i  =  0;  i  <  10000;  i  ++  )  {
		 if  (  !bQyDogOk(  )  )  {
			 AfxMessageBox(  "需要软件狗"  );  goto  errLabel;
		 }
		 traceLogA(  "第%d次校验成功",  i  +  1  );
	}
	AfxMessageBox(  "共%d次校验成功",  i  );

errLabel:
	return  0;
}


 RB_SPRO_APIPACKET		ApiPacket;		//  Rainbow 所定义的数据结构
 BOOL					bRnbDogInited	=	FALSE;

 int  initRnbDog(  )
{

	 if  (  bRnbDogInited  )  return  0;

	 if  (  RNBOsproFormatPacket(  ApiPacket,  sizeof(  ApiPacket  )  )	//  初始化数据结构（仅Win32程序使用） 
		 ||  RNBOsproInitialize(  ApiPacket  )  )						//  初始化函数
	 {
		 return  -1;
	 }
	 bRnbDogInited  =  TRUE;
	 return  0;
}

  BOOL  bQyDogOk(  )
{
	BOOL					bRet		=		TRUE;
	SP_STATUS				spStatus;
	static   RB_DWORD		qResult32;	
	RB_WORD					developerID;	

	if  (  !bRnbDogInited  )  goto  errLabel;
	developerID  =  0xF278;		//  开发者ID号
	//  注：这里所提到的ID号均为16进制数	
	spStatus  =  RNBOsproFindFirstUnit(  ApiPacket,  developerID  );	//  找到Developer ID指定加密锁
	//									         ▲▲▲ 
	//									       加密琐的ID号 
	//  Findfirst返回值为0，代表找到加密锁，其他代表未找到加密锁，详细信息请参阅API手册
	if  (  spStatus  )  {
		traceLogA(  "找不到加密锁"  );  goto  errLabel;
	}
	{
	//  "B1A8E011"(查询串),  "35F0F874"(响应串)   Rainbow Wizard所生成的数据 
	unsigned  char  queryData[]  =  {  0xB1,  0xA8,  0xE0,  0x11  };	//  欲查询数据	
	unsigned  char  cmpqueryData[]  =  { 0x35, 0xF0, 0xF8, 0x74 } ;	//  响应数据
	unsigned  char  response[]  =  {  0,  0,  0,  0  };				
	int  cellAddress  =  0x3A;	//  设置查询单元号
	int  queryLength  =  sizeof(  queryData  );		//  设置查询数据长度
	if  (  queryLength  !=  sizeof(  cmpqueryData  )  ||  queryLength  !=  sizeof(  response  )  )  {
		traceLogA(  "校验错误：	queryData、cmpqueryData、response的长度没有相等"  );  goto  errLabel;
	}
	spStatus  =  RNBOsproQuery(  ApiPacket,		//  Apipacket为 Rainbow公司保留数据结构
								 cellAddress,	//  查询单元号
                             	 &queryData,	//  查询数据(输入加密锁的数据)
							     &response,     //  响应数据(经加密锁计算返回数据)
                             	 &qResult32,	//  qResult32为 Rainbow公司保留数据结构
								 queryLength  );//  查询数据长度
	spStatus  =  memcmp(  response,  cmpqueryData,  queryLength  );	//  比较响应数据和预知数据
	if  (  spStatus  !=  0  )  {							//  比较后返回值为0，代表查询响应正确，其他代表不正确，详细信息请参阅API手册
		traceLogA(  "查询不成功"  );  goto  errLabel;
	}
	}

	bRet  =  TRUE;
errLabel:

	return  bRet;

}

 static  CString  qyBrowserForFile(  BOOL bOpen,  char  *  lpszDefExt,  DWORD  dwFlags,  char  *  lpszFilter,  char  *  title  )
{	 
	 CString		pathCStr;
	 CFileDialog	dlg(  bOpen,  lpszDefExt  ?  lpszDefExt  :  "html",  "",  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT,  lpszFilter  ?  lpszFilter  :  "Html 格式(*.html)|*.html|Excel 格式(*.xls)|*.xls||",  NULL  );

	 dlg.m_ofn.lpstrTitle  =  title  ?  title  :  "选择导出的数据文件名和格式";

	 if  (  IDOK  ==  dlg.DoModal(  )  )  {
		 pathCStr  =  dlg.GetPathName(  );
	 }
	
	 return  pathCStr;
}


BOOL CMainFrame::OntestLicense() 
{
	QY_LICENSE_CTX		*	pCtx		=	NULL;
	unsigned  int			nLicenses	=	0;

	if (  bQnmLicenseOk(  pCtx,  &nLicenses  )  )  traceLogA(  "ok, the value is %d",  nLicenses  );
	return   TRUE;

}

void CMainFrame::OntestProductId() 
{

	/*
	int  i;
	for  (  i = 0; i< 10000; i ++  )  {
		bGetHardwareIdOk(  );  
	}
	*/
	flg		=  1;
	CString   pathCStr;

	if  (  flg  ==  1  )  {
		AfxMessageBox(  "本工具用来生成软件许可证的种子文件。"  );	
		pathCStr  =  qyBrowserForFile(  FALSE,  "sed",  0,  "LicenseSeed 格式(*.sed)|*.sed||",  NULL  );
		if  (  pathCStr  ==  ""  )  goto  errLabel;	
		if  (  !bGetHardwareIdOk(  pathCStr.GetBuffer(  0  )  )  )  {  AfxMessageBox(  "    您的硬件环境不符合产品要求,请根据用户手册的规定，重新调整硬件安装环境！"  );  goto  errLabel;  }
		AfxMessageBox(  "生成软件许可证的种子文件 Ok!"  );  
	}
errLabel:
	return;
}

void CMainFrame::OnCalcChkNum() 
{
//	int  i;
//	for  (  i = 0; i < 10000; i ++  )  {
//		bCalcChkNumOk( );
//	}

	flg  =  2;
	CDlgPassword  dlg;
	dlg.DoModal(  );
}

void CMainFrame::OnsetChkNum() 
{
//	int  i;
//	for  (  i = 0; i < 10000; i ++  ) {
//		bSetChkNumOk(  );
//	}
	CString		pathCStr;
	
	flg  =  3;
	if  (  flg  ==  3  )  {
		AfxMessageBox(  "        本工具用来导入软件许可证。"  );
		pathCStr  =  qyBrowserForFile(  TRUE,  "lcs",  OFN_FILEMUSTEXIST,  "License 格式(*.lcs)|*.lcs||",  "选择导入的数据文件名和格式"  );
		if  (  pathCStr  ==  ""  )  goto  errLabel;	
		if  (  !bSetChkNumOk(  pathCStr.GetBuffer(  0  )  )  )   {  AfxMessageBox(  "    对不起，无法读取注册表！  "  );  goto  errLabel;  } 
		AfxMessageBox(  "导入软件许可证 Ok!"  );
	}

errLabel:
	return;
}

void CMainFrame::OncheckLicense() 
{
/*	int  i;
	char	buf[128]  =  "";

	for  ( i = 0; i < 10000; i ++  )  {
		if  (  bHardwareLicenseOk(  )  )  {
			_snprintf(  buf,  sizeof(  buf  ),  "%d次校验成功",  i  );
			this->m_wndStatusBar.SetPaneText(  0,  buf, TRUE );
			}
		else
			AfxMessageBox(  "校验失败"  );

		}
*/
	flg   =   4;
	CDlgPassword  dlg;
	dlg.DoModal(  );
}
