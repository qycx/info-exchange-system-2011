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
#include	"qyDbCommon.h"

#include	"qwmHideProcessCommProc.h"


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

#include	"ras.h"
#include	<raserror.h> 

//  加密狗 
// #include "stdafx.h" 
#include "spromeps.h" // rainbow API的头文件
#include <stdio.h>
#include	"testCommon.h"

TEST_GBUF	gBuf;

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
	ON_COMMAND(ID_test, Ontest)
	ON_COMMAND(ID_testWiz, OntestWiz)
	ON_COMMAND(ID_testPs, OntestPs)
	ON_COMMAND(ID_testStatusDlg, OntestStatusDlg)
	ON_WM_TIMER()
	ON_COMMAND(ID_testUsr, OntestUsr)
	ON_COMMAND(ID_testFor, OntestFor)
	ON_COMMAND(ID_testQwmSend, OntestQwmSend)
	ON_COMMAND(ID_testHttp, OntestHttp)
	ON_COMMAND(ID_testMfcHttp, OntestMfcHttp)
	ON_COMMAND(ID_testqqq, Ontestqqq)
	ON_COMMAND(ID_testPrintf, OntestPrintf)
	ON_COMMAND(ID_testNh, OntestNh)
	ON_COMMAND(IDC_phbk, Onphbk)
	ON_COMMAND(ID_dog, Ondog)
	ON_COMMAND(ID_testLicense, OntestLicense)
	ON_COMMAND(ID_testInsert, OntestInsert)
	ON_COMMAND(ID_testDelete, OntestDelete)
	ON_COMMAND(ID_testSelect, OntestSelect)
	ON_COMMAND(ID_testHideProcess, OntestHideProcess)
	ON_COMMAND(ID_testShowProcess, OntestShowProcess)
	ON_COMMAND(ID_cpu, Oncpu)
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


void CMainFrame::Ontest() 
{
	char  buf[1099]  =  "";

	memset(  buf,  '1',  sizeof(  buf  )  );
	buf[sizeof(  buf  )  -  2]  =  '2';
	buf[sizeof(  buf  )  -  1]  =  0;
	traceLogA(  "buf is %s",  buf  );
	
}

void CMainFrame::OntestWiz() 
{
	//  CPs			dlg(  AFX_IDS_APP_TITLE  );
	CPropertySheet	dlg(  AFX_IDS_APP_TITLE  );
	CTestP1		p1;
	CTestP2		p2;
	CTestP3		p3;

	dlg.AddPage(  &p1  );
	dlg.AddPage(  &p2  );
	dlg.AddPage(  &p3  );
	dlg.SetWizardMode(  );
	dlg.DoModal(  );
	
}

void CMainFrame::OntestPs() 
{

	//  CPropertySheet	dlg(  "kkk"  );
	CPs				dlg(  "kkk"  );
	CTestP1			p1;
	CTestP2			p2;
	CTestP3			p3;

	dlg.AddPage(  &p1  );
	dlg.AddPage(  &p2  );
	dlg.AddPage(  &p3  );

	dlg.DoModal(  );

	
}

void CMainFrame::OntestStatusDlg() 
{


	setErrLogFile(  "c:\\temp\\testStatus.log"  );
	setErrHintWndTitle(  "qnmStatus"  );

	SetTimer(  1,  1000,  NULL  );

	//  CDlgStatus	dlg;
	CTestPs			dlg(  "qnmStatus"  );
	CPpStatus		page;

	dlg.AddPage(  &page  );

	dlg.DoModal(  );


	
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{

	static	int	i  =  0;

	errLog(  "%d times",  i  );
	i  ++  ;
	
	CFrameWnd::OnTimer(nIDEvent);
}


#define  MAX_NAME		256

 LPVOID  AllocateTokenInfoBuffer(  HANDLE  hToken,  TOKEN_INFORMATION_CLASS  InfoClass,  DWORD  *  pdwSize  )
{
	 *pdwSize  =  0;

	 GetTokenInformation(  hToken,  InfoClass,  NULL,  *pdwSize,  pdwSize  );
	 return  new  BYTE [*pdwSize];
}

 void  GetAllSids(  HANDLE  hToken,  TOKEN_INFORMATION_CLASS  tic  )
{
	 DWORD  dwSize  =  0;
	 TOKEN_GROUPS  *  pSidInfo  =  (  PTOKEN_GROUPS  )AllocateTokenInfoBuffer(  hToken,  tic,  &dwSize  );
	 if  (  !pSidInfo  )  return;
	 if  (  !GetTokenInformation(  hToken,  tic,  pSidInfo,  dwSize,  &dwSize  )  )
		 traceLogA(  "GetTokenInfomation Error %u\n",  GetLastError(  )  );
	 if  (  !pSidInfo->GroupCount  )  traceLogA(  "\tNone!\n"  );
	 for  (  DWORD  i  =  0;  i  <  pSidInfo->GroupCount;  i  ++  )  {
		  SID_NAME_USE	sidType;
		  char			lpName[MAX_NAME];
		  char			lpDomain[MAX_NAME];
		  DWORD			dwNameSize  =  MAX_NAME;
		  DWORD			dwDomainSize  =  MAX_NAME;
		  DWORD			dwAttr  =  0;

		  if  (  !LookupAccountSid(  NULL,  pSidInfo->Groups[i].Sid,	lpName,  &dwNameSize,  lpDomain,  &dwDomainSize,  &sidType  )  )  {
			  if  (  GetLastError(  )  ==  ERROR_NONE_MAPPED  )  strcpy(  lpName,  "NONE_MAPPED"  );
			  else  traceLogA(  "LoopupAccountSid Error %u\n",  GetLastError(  )  );
			}
		  else  dwAttr  =  pSidInfo->Groups[i].Attributes;

		  traceLogA(  "%12s \\%-20s \t%s\n",  lpDomain,  lpName,  (  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  ?  "[DENY]"  :  ""  );
	 }

	 delete  []  (  LPBYTE  )pSidInfo;

}



 int  getProcessGrps(  int  *  pFlg  )
{
	 int						iErr				=	-1;
	 DWORD						dwSize				=	0;
	 TOKEN_GROUPS	*			pSidInfo			=	NULL;
	 DWORD						i;
	 HANDLE						hToken				=	NULL;
	 unsigned  char				ucbTokenOpen		=	FALSE;
	 TOKEN_INFORMATION_CLASS	tic					=	TokenGroups;  
	 int						iType;
	 int						flg					=	0;				//  先将标志位清空
	 
	 if  (  !OpenProcessToken(  GetCurrentProcess(  ),  TOKEN_QUERY,  &hToken  )  )  goto  errLabel;
	 ucbTokenOpen  =  TRUE;
	 

	 pSidInfo  =  (  PTOKEN_GROUPS  )AllocateTokenInfoBuffer(  hToken,  tic,  &dwSize  );
	 if  (  !pSidInfo  )  goto  errLabel;
	 if  (  !GetTokenInformation(  hToken,  tic,  pSidInfo,  dwSize,  &dwSize  )  )  {
		 traceLogA(  "GetTokenInfomation Error %u\n",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 if  (  !pSidInfo->GroupCount  )  {
		 traceLogA(  "\tNone!\n"  );
		 iErr  =  0;
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pSidInfo->GroupCount;  i  ++  )  {
		  SID_NAME_USE	sidType;
		  char			nameBuf[256];
		  char			domainBuf[256];
		  DWORD			dwNameSize			=  sizeof(  nameBuf  );
		  DWORD			dwDomainSize		=  sizeof(  domainBuf  );
		  DWORD			dwAttr  =  0;

		  if  (  !LookupAccountSid(  NULL,  pSidInfo->Groups[i].Sid,	nameBuf,  &dwNameSize,  domainBuf,  &dwDomainSize,  &sidType  )  )  {
			  if  (  GetLastError(  )  ==  ERROR_NONE_MAPPED  )  strcpy(  nameBuf,  "NONE_MAPPED"  );
			  else  traceLogA(  "LoopupAccountSid Error %u\n",  GetLastError(  )  );
			  continue;
		  }
		
		  dwAttr  =  pSidInfo->Groups[i].Attributes;

		  traceLogA(  "%12s \\%-20s \t%s\n",  domainBuf,  nameBuf,  (  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  ?  "[DENY]"  :  ""  );
		  
		  if  (  !(  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  )  {
			  iType  =  qyGetTypeByDes(  CONST_qyGrpTable,  nameBuf  );
			  if  (  iType  !=  -1  )  flg  |=  1  <<  iType;
		  }
	 }

	 for  (  i  =  0;  CONST_qyGrpTable[i].type  !=  -1;  i  ++  )  {
		  if  (  flg  &  (  1  <<  CONST_qyGrpTable[i].type  )  )
			  traceLogA(  "\tbelongs to %s",  CONST_qyGrpTable[i].des  );
	 }

	 *pFlg  =  flg;
	 iErr  =  0;

errLabel:

	 if  (  pSidInfo  )  delete  []  (  LPBYTE  )pSidInfo;
	 if  (  ucbTokenOpen  &&  hToken  )  CloseHandle(  hToken  );

	 return  iErr;

}


 extern  "C"  int  qyGetProcessGrps(  int  *  pFlg  )
{
	 int							iErr				=	-1;
	 DWORD							dwSize				=	0;
	 TOKEN_GROUPS				*	pSidInfo			=	NULL;
	 DWORD							i;
	 HANDLE							hToken				=	NULL;
	 unsigned  char					ucbTokenOpen		=	FALSE;
	 TOKEN_INFORMATION_CLASS		tic					=	TokenGroups;  
	 int							iType;
	 int							flg					=	0;				//  先将标志位清空
	 
	 if  (  !OpenProcessToken(  GetCurrentProcess(  ),  TOKEN_QUERY,  &hToken  )  )  goto  errLabel;
	 ucbTokenOpen  =  TRUE;

	 dwSize  =  0;
	 GetTokenInformation(  hToken,  tic,  NULL,  dwSize,  &dwSize  );
	 pSidInfo  =  (  PTOKEN_GROUPS  )new  BYTE[dwSize];
	 if  (  !pSidInfo  )  goto  errLabel;
	 if  (  !GetTokenInformation(  hToken,  tic,  pSidInfo,  dwSize,  &dwSize  )  )  {
		 traceLogA(  "GetTokenInfomation Error %u\n",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 if  (  !pSidInfo->GroupCount  )  {
		 traceLogA(  "\tNone!\n"  );
		 iErr  =  0;
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pSidInfo->GroupCount;  i  ++  )  {
		  SID_NAME_USE	sidType;
		  char			nameBuf[256];
		  char			domainBuf[256];
		  DWORD			dwNameSize			=  sizeof(  nameBuf  );
		  DWORD			dwDomainSize		=  sizeof(  domainBuf  );
		  DWORD			dwAttr  =  0;

		  if  (  !LookupAccountSid(  NULL,  pSidInfo->Groups[i].Sid,	nameBuf,  &dwNameSize,  domainBuf,  &dwDomainSize,  &sidType  )  )  {
			  if  (  GetLastError(  )  ==  ERROR_NONE_MAPPED  )  wsprintf(  nameBuf,  "NONE_MAPPED"  );
			  else  traceLogA(  "LoopupAccountSid Error %u\n",  GetLastError(  )  );
			  continue;
		  }
		
		  dwAttr  =  pSidInfo->Groups[i].Attributes;

		  traceLogA(  "%12s \\%-20s \t%s\n",  domainBuf,  nameBuf,  (  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  ?  "[DENY]"  :  ""  );
		  
		  if  (  !(  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  )  {
			  iType  =  qyGetTypeByDes(  CONST_qyGrpTable,  nameBuf  );
			  if  (  iType  !=  -1  )  flg  |=  1  <<  iType;
		  }
	 }

	 for  (  i  =  0;  CONST_qyGrpTable[i].type  !=  -1;  i  ++  )  {
		  if  (  flg  &  (  1  <<  CONST_qyGrpTable[i].type  )  )
			  traceLogA(  "\tbelongs to %s",  CONST_qyGrpTable[i].des  );
	 }

	 *pFlg  =  flg;
	 iErr  =  0;

errLabel:

	 if  (  pSidInfo  )  delete  []  (  LPBYTE  )pSidInfo;
	 if  (  ucbTokenOpen  &&  hToken  )  CloseHandle(  hToken  );

	 return  iErr;

}


void CMainFrame::OntestUsr() 
{

	int		flg;
	
	for  (  int  i  =  1000;  i  --  ;  i  ++  )  {
		 if  (  qyGetProcessGrps(  &flg  )  )
		 	 traceLogA(  "getProcessGrps failed"  );
	}
	


	//  if  (  GetUserName(  buf,  &len  )  )  qyShowHint(  buf  );



	/*
	HANDLE  hToken  =  NULL;

	if  (  !ImpersonateSelf( SecurityImpersonation  )  )  {
		traceLogA(  "ll"  );
		return;
	}
	if  (  !OpenThreadToken(  GetCurrentThread(  ),  TOKEN_QUERY,  FALSE,  &hToken  )  )  {
		return;
	}
	GetAllSids(  hToken,  TokenGroups  );

	CloseHandle(  hToken  );
	RevertToSelf(  );
	*/ 
	
}

void CMainFrame::OntestFor() 
{
	// TODO: Add your command handler code here

	int		i,  j;

	for  (  i  =  0,  j  =  9;  i  <  5  &&  !traceLogA(  "In condition, i is %d",  i  );  i  ++  ,  traceLogA(  "In step"  )  )  {
		 traceLogA(  "In loop, i is %d",  i  );
	}
	
}



void CMainFrame::OntestQwmSend() 
{
	// TODO: Add your command handler code here

	CDlgTestQnm		dlg;

	if  (  dlg.DoModal(  )  !=  IDOK  )  return;

	qySetRegCfg(  CONST_qyRootKey_test,  CONST_regValName_testQwmCntIp,  dlg.m_qwmServerIp.GetBuffer(  0  )  );
	qySetRegCfg(  CONST_qyRootKey_test,  CONST_regValName_testQwmSendTimes,  dlg.m_qwmSendTimes.GetBuffer(  0  )  ); 

	if  (  WinExec(  "testQwm.exe",  SW_SHOW  )  <=  31  )  qyShowHint(  "测试程序testQwm.exe找不着"  );
	
}

char  *  CONST_qnmReq80Str  =  "GET /default.html HTTP/1.1\n"
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*\n"
							"Accept-Language: zh-cn\n"
							"Accept-Encoding: gzip, deflate\n"
							"User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\n"
							"Host: localhost:80\n"
							"Connection: Keep-Alive\n"
							"\n";
char  *  CONST_qnmReq8080Str  =  "GET / HTTP/1.1\n"
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*\n"
							"Accept-Language: zh-cn\n"
							"Accept-Encoding: gzip, deflate\n"
							"User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\n"
							"Host: localhost:8080\n"
							"Connection: Keep-Alive\n"
							"\n";

void CMainFrame::OntestHttp() 
{
	QY_SOCK		sock;
	char		buf[2048];
	int			len;
	char	*	ptr	=  CONST_qnmReq8080Str;

	clearQySock(  &sock  );
	if  (  !qyConnect(  "127.0.0.1",  8080,  &sock,  20000  )  )  {
		if  (  !qySend(  &sock,  ptr,  strlen(  ptr  ),  20000  )  )  {
			len  =  sizeof(  buf  );
			if  (  !qyRecv(  &sock,  buf,  &len,  20000  )  )  {
				buf[len]  =  0;
				traceLogA(  "recvd from 8080 [%s]",  buf  );
			}
		}

		qyDisconnect(  &sock  );
	}

	
}



void CMainFrame::OntestMfcHttp() 
{
	QY_SOCK		sock;
	char		buf[2048];
	int			len;
	char	*	svrIp  =  "192.168.103.30";
	char	*	ptr  =  CONST_qnmReq80Str;

	clearQySock(  &sock  );
	if  (  !qyConnect(  svrIp,  80,  &sock,  20000  )  )  {
		if  (  !qySend(  &sock,  ptr,  strlen(  ptr  ),  20000  )  )  {
			len  =  sizeof(  buf  );
			if  (  !qyRecv(  &sock,  buf,  &len,  20000  )  )  {
				buf[len]  =  0;
				traceLogA(  "recvd from 80 [%s]",  buf  );
			}
		}

		qyDisconnect(  &sock  );
	}

	
}	


int testSock();

void CMainFrame::Ontestqqq() 
{
//	AfxMessageBox(  "wwwqqq"  );


	//  testSock();
	

}

void testreg (  ){

	char					buf[256];
//	int						iRet			=	-1;
	
	qySetRegCfg(  "Software\\Qycx\\Test", "Test111", "shengqi" );

	if (  qyGetRegCfg(  "Software\\Qycx\\Test",  "Test",  buf,  sizeof(  buf  )  )  ){
		AfxMessageBox(  " Failture!"  );
		goto  errLabel;
	}

	if  (  !strcmpi(  buf,  "1"  )  )  AfxMessageBox(  "等于1"  );
	else  {
		AfxMessageBox(  "不等于1"  );
		goto  errLabel;
	}


	qyDelRegCfg(  "Software\\Qycx\\Test",  "Test" );


 

errLabel:
	return ;
}

/*
int testSock()
{
 
	QY_SOCK				sock;
	char				buf[2048];
	int					len;
	char			*	svrIp		=	"192.168.103.133";
	char			*	ptr			=	CONST_qnmReq80Str;
	unsigned  short		usPort		=	8766;
	QY_COMM_SESSION		session;
	QNM_COMM_AUTHINFO	authInfo;
	int					iServiceId  =  CONST_qyServiceId_qwm;
	SOCK_TIMEOUT		to;
	QY_COMM_RESP		tmpResp;
	char				dataBuf[128];
	char				respDataBuf[256];


	QQQ					qqq;
	

	clearQySock(  &sock  );
	memset(  &session,  0,  sizeof(  session  )  );
	setSockTimeout(  &to  );

	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	authInfo.cmd  =  CONST_qnmAuthCmd_guiTalk;

	if  (  qyConnect(  svrIp,  usPort,  &sock,  20000  )  )  goto  errLabel;

	 // 传送字符串到服务器。
	if  (  qyTellService(  iServiceId,  qnmVerStr(  ),  (  char  *  )&authInfo,  sizeof(  authInfo  ),  &sock,  &to,  &session  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session,  &sock,  &to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 traceLogA(  "qwmOpenSession: get respCode of qyTellService is %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );
	 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;	

	 // 第一个talk:
	 _snprintf(  dataBuf,  sizeof(  dataBuf  ),  "%s",  "kk"  );
	 	
	 if  (  qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_testSession,  dataBuf,  strlen(  dataBuf  )  )  )  goto  errLabel;
	 respDataBuf[0]  =  0;
	 if  (  qyRecvResp(  &session,  &sock,  &to,  &tmpResp,  respDataBuf,  sizeof(  respDataBuf  )  )  )  goto  errLabel;
	 if  (  tmpResp.head.len  >=  sizeof(  respDataBuf  )  )  goto  errLabel;
	 respDataBuf[tmpResp.head.len]  =  0;
	 
	 traceLogA(  "respDataBuf  is [%s]",  respDataBuf  );

	 // 第二个talk:// 传送又一个字符串到服务器。
 	 _snprintf(  dataBuf,  sizeof(  dataBuf  ),  "%s",  "other"  );
	 
	 if  (  qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_testSession,  dataBuf,  strlen(  dataBuf  )  )  )  goto  errLabel;
	 respDataBuf[0]  =  0;
	 if  (  qyRecvResp(  &session,  &sock,  &to,  &tmpResp,  respDataBuf,  sizeof(  respDataBuf  )  )  )  goto  errLabel;
	 if  (  tmpResp.head.len  >=  sizeof(  respDataBuf  )  )  goto  errLabel;
	 respDataBuf[tmpResp.head.len]  =  0;
	 
	 traceLogA(  "respDataBuf  is [%s]",  respDataBuf  );


	 // 第三个talk:// 传送一个int变量到服务器。
 	 
	 memset(  &qqq,  0,  sizeof(  qqq  )  );
	 qqq.a		=    256;
	 	 
	 if  (  qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_testStructQqq,  ( char  * )&qqq,  sizeof(  qqq  )  )  )  goto  errLabel;
	 respDataBuf[0]  =  0;
	 if  (  qyRecvResp(  &session,  &sock,  &to,  &tmpResp,  respDataBuf,  sizeof(  respDataBuf  )  )  )  goto  errLabel;
	 if  (  tmpResp.head.len  >=  sizeof(  respDataBuf  )  )  goto  errLabel;
	 respDataBuf[tmpResp.head.len]  =  0;
	 
	 traceLogA(  "respDataBuf  is [%s]",  respDataBuf  );
	 
	 // 第四个talk:// 传送一个结构变量到服务器。
 	 
	 memset(  &qqq,  0,  sizeof(  qqq  )  );
	 qqq.a			=		2;
	 qqq.k			=		22;

 	 _snprintf(  qqq.bb,  sizeof(  qqq.bb  ),  "%s",  "  客户端"  );
	 qqq.c			=		'a';
	 qqq.a		=		qyhtonl(  qqq.a  );
	 qqq.k		=		qyhtons(  qqq.k  );
	 	 
	 if  (  qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_testStructQqq,  ( char  * )&qqq,  sizeof(  qqq  )  )  )  goto  errLabel;
	 respDataBuf[0]  =  0;
	 if  (  qyRecvResp(  &session,  &sock,  &to,  &tmpResp,  respDataBuf,  sizeof(  respDataBuf  )  )  )  goto  errLabel;
	 if  (  tmpResp.head.len  >=  sizeof(  respDataBuf  )  )  goto  errLabel;
	 respDataBuf[tmpResp.head.len]  =  0;
	 
	 traceLogA(  "respDataBuf  is [%s]",  respDataBuf  );
	 
	 // end.

	 if  (  qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_end,  NULL,  0  )  )  goto  errLabel;
	 respDataBuf[0]  =  0;
	 qyRecvResp(  &session,  &sock,  &to,  &tmpResp,  respDataBuf,  sizeof(  respDataBuf  )  );
	 // session end.

	
errLabel:
	
	if  (  bQySockOpen(  &sock  )  )  qyDisconnect(  &sock  );

return 0;
}

*/

void CMainFrame::OntestPrintf() 
{

	//  char  buf[200];
	char  s[]  =  "  test  " ;
	int   i  =100;
	

	_snprintf(   s,  sizeof(  s  ) ,  " 这段是字符串：[%s],这段是整形量：[&d]",  s,  i  );  

	s[sizeof( s  )]  =0;

	traceLogA (  " test printf:   %s",  s  );

	return  ;

}

LPVOID MyAllocMem(     DWORD cb) 
{     
	 return HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, cb); 
}   
 BOOL MyFreeMem(     LPVOID pMem) 
{     
	 return HeapFree(GetProcessHeap(), 0, pMem); 
}

 BOOL testNh( char  *  ip  )
{
	BOOL bRet = FALSE;
	NETRESOURCE nr; 
	char remoteNameBuf[1024];
	//  char	buf[1024];

	traceLogA(  "testNh enters"  );

	sprintf( remoteNameBuf, "\\\\%s", ip );
	
	nr.dwScope = RESOURCE_GLOBALNET; 
	nr.dwType = RESOURCETYPE_ANY; 
	//  nr.dwDisplayType = RESOURCEDISPLAYTYPE_SERVER; 
	nr.dwDisplayType  =  RESOURCEDISPLAYTYPE_SHARE;
	nr.dwUsage = RESOURCEUSAGE_CONTAINER; 
	nr.lpLocalName = NULL; 
	nr.lpRemoteName = remoteNameBuf; 
	nr.lpComment = NULL; 
	nr.lpProvider = NULL; 
	
	LPVOID pMem =  HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, 16384); 
	if (!pMem) { 
		MessageBox( NULL,  "Not enough memory to allocate for WNetEnumResource",  "",  MB_OK  ); 
		return bRet; 
	} 

	HANDLE hWNetEnum=NULL; //列举的句柄，WNetEnumResource每调用一次，就移到下一个共享资源container
	DWORD dwStatus = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY,  RESOURCEUSAGE_CONNECTABLE, &nr, &hWNetEnum); 
	if (dwStatus != NO_ERROR) { 
		//  qyDisplayLastError(  "WNetOpenEnum failed"  );
		DWORD dwErr = GetLastError(); 
		traceLogA( "WNetOpenEnum failed, dwErr is %d",  dwErr ); 
		HeapFree(GetProcessHeap(), 0, pMem); 
		return bRet; 
	} 
	

	do { 
		DWORD dwEntries; DWORD dwBuffSize; 
		
		dwEntries =1; //每次只处理一个共享资源container
		dwBuffSize= 16384; 
		dwStatus = WNetEnumResource(hWNetEnum, &dwEntries, pMem, &dwBuffSize); //dwEntries个共享资源container以数组方式存放在pMem中
		if (dwStatus == NO_ERROR) { 
			traceLogA(  "Resource name is [%s], %s", ((LPNETRESOURCE)pMem)->lpRemoteName,  ((LPNETRESOURCE)pMem)->dwType  ==  RESOURCETYPE_PRINT  ?  "打印机"  :  "共享资源"   );
		} 
	} while (dwStatus == NO_ERROR); 
	if (dwStatus != ERROR_NO_MORE_ITEMS) { 
		traceLogA( "WNetEnumResource failed" ); 
		MyFreeMem(pMem); 
		WNetCloseEnum(hWNetEnum); 

		return bRet; 
	} 
	MyFreeMem(pMem); 
	WNetCloseEnum(hWNetEnum); //we are done with enumerating shares on a file server. 

	traceLogA(  "testNh leaves"  );


	return bRet = TRUE; 
} 




void CMainFrame::OntestNh() 
{
	// TODO: Add your command handler code here
	testNh(  "192.168.103.131"  );
	AfxMessageBox(  "Ok"  );
}

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



BOOL CMainFrame::OntestLicense() 
{

	QY_LICENSE_CTX		*	pCtx  =  NULL;
	char					buf[128];
	unsigned  int			regTimeCount		=  50;

	if (  bQnmLicenseOk(  pCtx,  &regTimeCount  )  )  traceLogA(  "ok, the value is %s",  buf  );
	return   TRUE;

}





void CMainFrame::OntestInsert() 
{
	// TODO: Add your command handler code here

	char  sqlBuf[1024];

	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "insert into testTab1(col1,col2,id) values(1,'1',%u)",  2  *  1024  *  1024  *  1024 -  1  );
	if  (  bQyExecSql(  gBuf.pDb,  sqlBuf  )  )  AfxMessageBox(  "ok"  );
	else  AfxMessageBox(  "failed"  );
	
}

void CMainFrame::OntestDelete() 
{

	char  sqlBuf[1024];

	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from testTab1 where col1=1"  );
	if  (  bQyExecSql(  gBuf.pDb,  sqlBuf  )  )  AfxMessageBox(  "ok"  );
	else  AfxMessageBox(  "failed"  );

	
}

void CMainFrame::OntestSelect() 
{
	char			sqlBuf[1024];
	CRecordset		ls(  (  CDatabase  *  )gBuf.pDb  );
	int				i;
	CDBVariant		varVal[10];
	CListCtrl		m_LV;


		TRY  {
	
		sprintf(  sqlBuf,  "select col1,col2 from testTab1"  );
		if  (  !ls.Open(  CRecordset::forwardOnly,  sqlBuf  )  )  {
			MessageBox( "无法打开数据库", "错误", MB_OK|MB_ICONERROR );
			goto  errLabel;
		}	
	
		for  (  i  =  0;  !ls.IsEOF(  );  i  ++,  ls.MoveNext(  )  )  {
			 
			 ls.GetFieldValue(  i,  varVal[i]  );
			 if  (  varVal[0].m_dwType  ==  DBVT_STRING  )  {
				 m_LV.InsertItem(  i,  varVal[0].m_pstring->GetBuffer(  0  )  );
			 }

		}
		
		}
	CATCH  (  CDBException,  e  )  {
		   OutputDebugString(  e->m_strError  );
		   goto  errLabel;
	}
	END_CATCH

errLabel:

	return;


}


//////////////////
// Use this class to disable task keys, task manager and/or the taskbar.
// Call Disable with flags for items you want to disable; for example:
//
// CTaskMgrKeys::Disable(CTaskMgrKeys::ALL);
// 
class CTaskKeyMgr {
public:
	enum {
		TASKMGR  = 0x01,	// disable task manager (Ctrl+Alt+Del)
		TASKKEYS = 0x02,	// disable task keys (Alt-TAB, etc)
		TASKBAR  = 0x04,	// disable task bar
		TASKLIST  = 0x08,	// disable listing process list
		CTRLALTDEL  = 0x10,	// disable Ctrl+Alt+Del
		ALL=0xFFFF			// disable everything :(
	};
	static void Disable(DWORD dwItem,BOOL bDisable,BOOL bBeep=FALSE);

	static BOOL IsProcessListItemDisabled();

protected:
	static	HINSTANCE	hMyMyNtQuerySystemInformation;
};

BOOL CTaskKeyMgr::IsProcessListItemDisabled(){return hMyMyNtQuerySystemInformation!=NULL;}
HINSTANCE	CTaskKeyMgr::hMyMyNtQuerySystemInformation=NULL;

//////////////////
// Disable task-key related stuff.
// 
// dwFlags  = what to disable
// bDisable = disable (TRUE) or enable (FALSE)
// bBeep    = whether to beep for illegal keys (TASKKEYS only)
//
void CTaskKeyMgr::Disable(DWORD dwFlags, BOOL bDisable, BOOL bBeep)
{
	if (dwFlags & TASKLIST) {
		if(bDisable&&!IsProcessListItemDisabled()){
			//only work for windows 2000
			int (_cdecl *pfnHook)(DWORD);
	
			hMyMyNtQuerySystemInformation= LoadLibrary(_T("HookNTQSI.dll"));
			if(hMyMyNtQuerySystemInformation)
			{
				pfnHook = (int(*)(DWORD))GetProcAddress(hMyMyNtQuerySystemInformation,"Hook");
				pfnHook(GetCurrentProcessId());
			}
			else
			{
				MessageBox(NULL,(_T("Failed to load HookNTQSI.dll.Err =")) ,NULL,MB_OK | MB_APPLMODAL | MB_ICONWARNING);
			}
		}
		if(!bDisable&&IsProcessListItemDisabled()){
			int (_cdecl *pfnUnhook)();
			if(hMyMyNtQuerySystemInformation)
			{
				pfnUnhook = (int(*)())GetProcAddress(hMyMyNtQuerySystemInformation,"Unhook");
				pfnUnhook();
				FreeLibrary(hMyMyNtQuerySystemInformation);
				hMyMyNtQuerySystemInformation=NULL;
			}			
		}
	}

}



void CMainFrame::OntestHideProcess() 
{
	// TODO: Add your command handler code here
		//  CTaskKeyMgr::Disable(CTaskKeyMgr::TASKLIST,		!CTaskKeyMgr::IsProcessListItemDisabled());
	/*
	CTaskKeyMgr::Disable(CTaskKeyMgr::TASKLIST,		TRUE);


	traceLogA(  "del %s",  (  DeleteFile(  "G:\\qycx2\\develop\\debug\\bin\\HookNTQSI.dll"  )  ?  "成功"  :  "失败"  )  );


	CTaskKeyMgr::Disable(CTaskKeyMgr::TASKLIST,		FALSE);
	traceLogA(  "del %s",  (  DeleteFile(  "G:\\qycx2\\develop\\debug\\bin\\HookNTQSI.dll"  )  ?  "成功"  :  "失败"  )  );
	{  //  这里不知为什么，老是不能覆盖dll, 可是，用键盘是可以的。需要再考虑一下。
			char		qwmHelpFileName[MAX_PATH  +  1]	=	"";


			traceLogA(  "准备生成%s",  CONST_hideProcessDll  );			
			GetSystemDirectory(  qwmHelpFileName,  sizeof(  qwmHelpFileName  )  );
			trailDir(  qwmHelpFileName,  sizeof(  qwmHelpFileName  )  );
			lstrcpyn(  qwmHelpFileName  +  lstrlen(  qwmHelpFileName  ),  CONST_hideProcessDll,  sizeof(  qwmHelpFileName  )  -  lstrlen(  qwmHelpFileName  )  );
			SetFileAttributes(  qwmHelpFileName,  FILE_ATTRIBUTE_NORMAL  );
			traceLogA(  "Del %s%s",  qwmHelpFileName,  (  DeleteFile(  qwmHelpFileName  )  ?  "成功"  :  "失败"  )  );
			//  if  (  qyOutputResourceFile(  IDR_DATA_qwmHelp,  qwmHelpFileName  )  )  {
			//	traceLogA(  "生成%s失败",  qwmHelpFileName  );  goto  errLabel;
			//  }
			traceLogA(  "生成%s成功",  qwmHelpFileName  );
		}
	*/


	
}

void CMainFrame::OntestShowProcess() 
{
	// TODO: Add your command handler code here
	CTaskKeyMgr::Disable(CTaskKeyMgr::TASKLIST,		FALSE);
	
}

typedef  struct  __qwmCpusInfo_t		{
				 unsigned  int			cnt;
				 struct					{
						char			processorType[64];
				 }						cpus[1];
}		 QWM_CPUS_INFO;


 int  getCpusInfo(  QWM_CPUS_INFO  *  pCpusInfo  )
{
    OSVERSIONINFO		osinfo;
    SYSTEM_INFO			sysinfo;
    char			*	cpu			=	NULL;
    int					count		=	0;

	//  SetUnhandledExceptionFilter(  myExceptionFilter  );

    osinfo.dwOSVersionInfoSize  =  sizeof(OSVERSIONINFO);
    GetVersionEx(&osinfo);
    
	GetSystemInfo(&sysinfo);
        
    if  (  osinfo.dwPlatformId  ==  VER_PLATFORM_WIN32_NT  )  {   
		switch  (  sysinfo.wProcessorArchitecture  )  {   
				case  PROCESSOR_ARCHITECTURE_INTEL:
                	  switch  (  sysinfo.wProcessorLevel  )  {   
							  case  3:  cpu  =  "Intel 386";     break;
                    		  case  4:  cpu  =  "Intel 486";     break;
                    		  case  5:  
							  case  6:  cpu  =  "Intel Pentium"; break;
                    		  default:  cpu  =  "Unknown Intel"; break;
                	  }
                	  break;

				case  PROCESSOR_ARCHITECTURE_MIPS:
                	  switch  (  sysinfo.wProcessorLevel  )  {   
							  case  1:  cpu = "MIPS R2000";    break;
                    		  case  2: cpu = "MIPS R3000";    break;
                    		  case  3: cpu = "MIPS R6000";    break;
                    		  case  4: cpu = "MIPS R4000";    break;
                    		  case  6: cpu = "MIPS R6000A";   break;
                    		  case  9: cpu = "MIPS R10000";   break;
							  case 10: cpu = "MIPS R4200";    break;
							  case 11: cpu = "MIPS R4300";    break;
							  case 16: cpu = "MIPS R8000";    break;
							  case 32: cpu = "MIPS R4600";    break;
							  case 33: cpu = "MIPS R4700";    break;
							  case 34: cpu = "MIPS R4650";    break;
							  case 35: cpu = "MIPS R5000";    break;
							  default: cpu = "Unknown MIPS";  break;
					  }
					  break;

			    case  PROCESSOR_ARCHITECTURE_ALPHA:
                	  switch  (  sysinfo.wProcessorLevel  )  { 
							  case  21064:  cpu = "Alpha 21064";  break;
                    		  case  21066:  cpu = "Alpha 21066";  break;
                    		  case  21164:  cpu = "Alpha 21164";  break;
                    		  default:		cpu = "Unknown Alpha";    break;
                	  }
                	  break;
			    case  PROCESSOR_ARCHITECTURE_PPC:
                	  switch  (  sysinfo.wProcessorLevel  )  { 
							  case  1:  cpu = "PPC 601";     break;
                    		  case  3:  cpu = "PPC 603";     break;
                    		  case  4:  cpu = "PPC 604";     break;
                    		  case  6:  cpu = "PPC 603+";    break;
                    		  case  9:  cpu = "PPC 604+";    break;
                    		  case 20:  cpu = "PPC 620";     break;
                    		  default:  cpu = "Unknown PPC"; break;
                	  }
                	  break;

                default:
                		cpu  =  "unrecognised";
                		break;
        
			}
		} 
	else   {  /* Windows 95 or Windows98 */
      
	        switch  (  sysinfo.dwProcessorType  )  {
					case (386):   cpu = "Intel 386";       break;
            		case (486):   cpu = "Intel 486";       break;
            		case (586):   cpu = "Intel Pentium";   break;
            		case (860):   cpu = "Intel i860";      break;
            		case (2000):  cpu = "MIPS R2000";      break;
            		case (3000):  cpu = "MIPS R3000";      break;
            		case (4000):  cpu = "MIPS R4000";      break;
            		case (4400):  cpu = "MIPS R4400";      break;
            		case (4600):  cpu = "MIPS R4600";      break;
            		case (5000):  cpu = "MIPS R5000";      break;
            		case (8000):  cpu = "MIPS R8000";      break;
            		case (10000): cpu = "MIPS R10000";     break;
            		case (21064): cpu = "DEC Alpha 21064"; break;
            		case (21066): cpu = "DEC Alpha 21066"; break;
            		case (21164): cpu = "DEC Alpha 21164"; break;
            		default:     cpu = "unrecognised";
        	}
    
	}

	pCpusInfo->cnt  =  sysinfo.dwNumberOfProcessors;
	_snprintf(  pCpusInfo->cpus[0].processorType,  sizeof(  pCpusInfo->cpus[0].processorType  ),  "%s",  cpu  );

//  errLabel:
	return  0;

}






int  testCpu(  );

void CMainFrame::Oncpu() 
{
	// TODO: Add your command handler code here
	testCpu();
}



#define			CONST_regValueName_mHz							"~MHz"			//  REG_DWORD
#define			CONST_regValueName_processorNameString			"ProcessorNameString"
#define			CONST_regValueName_identifier					"Identifier"

int  testCpu(  )
{

	int						iRet			=	-1;
	char					buf[256]		=  "";
	unsigned  long			bufSize;
	HKEY					hKey			=  NULL;
	BOOL					bKeyOpen		=  FALSE;
	char					subKey[2048]	=  "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	unsigned  long			ulType			=  REG_DWORD;
	DWORD					dwMHz;
	DWORD					dwSize;
	char					idBuf[256]		=  "";
	unsigned  long			idSize			=  0;
	int						iErr			=  0;

	QWM_CPUS_INFO			cpuInfo;
	OSVERSIONINFO			osinfo;

    //  GetVersionEx(&osinfo);
    
	if  (  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKey,  NULL,  KEY_QUERY_VALUE,  &hKey  ) !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;
	if  (  RegQueryValueEx(  hKey,  CONST_regValueName_mHz,  NULL,  &ulType,  (unsigned char *)&dwMHz,  &dwSize  )  !=  ERROR_SUCCESS  )  {				
		//  读不出：则为window NT 以前的操作系统：如windows 98等,需要调用getCpuInfo函数读取CPU频率
	}
	if  (  RegQueryValueEx(  hKey,  CONST_regValueName_processorNameString,  NULL,  NULL,  (unsigned  char  *)buf,  &bufSize  )  !=  ERROR_SUCCESS  )  {		//  读不出，则为老式CPU,需要读取identifier,再调用getCpuInfo函数读取CPU名称：
		//  判断操作系统
		//  if  (  osinfo.dwPlatformId  ==  VER_PLATFORM_WIN32_NT  )  {																								//  虽然windows 98读不出x86这种类型的描述,只需要简单的identifier就取到了CPU名称。
		if  (  RegQueryValueEx(  hKey,  CONST_regValueName_identifier,  NULL,  NULL,  (unsigned  char  *)buf,  &bufSize  )  !=  ERROR_SUCCESS  )  goto  errLabel;		//  读不出，则为老式CPU,需要读取identifier,再调用getCpuInfo函数读取CPU名称：
			//  BOOL  bGetCpuName(  int  ChipManufacturer,  int  Type,  int  Family,  int  Model,  int  iRevision,  int  iCache,  int  ExtendedFamily,  BOOL  HasMMX,  BOOL  SupportsMP,  unsigned  int  uiBrandId,  char  *  processorName,  unsigned  int  size  );
		//  }

	}
	trim(  buf  );

	if  (  (  iErr  =  RegQueryValueEx(  hKey,  "99",  NULL,  NULL,  (  unsigned  char  *)buf,  &bufSize  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	




	/*

	if (  qyGetRegCfg(  "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",  "~MHz",  buf,  sizeof(  buf  )  )  ){
		AfxMessageBox(  " Failture!"  );
		goto  errLabel;
	}

	if  (  !strcmpi(  buf,  "1"  )  )  AfxMessageBox(  "等于1"  );
	else  {
		AfxMessageBox(  "不等于1"  );
		goto  errLabel;
	}


	qyDelRegCfg(  "Software\\Qycx\\Test",  "Test" );
	*/

	iRet  =  0;

errLabel:
	if  (  bKeyOpen  )   RegCloseKey(  hKey  );
	return  iRet;

}